/*
Copyright 2020 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file qsetconf.c
    \brief Implementation of Quick defaults setup

In this simple implementation, the sensible defaults proscribed by ITK test
and denied by FieldComm, are set with a "manufacturer-defined" RB.RESTART=6.
The implementation delegates the gory details to fbs_write_parameter_loc()
and simply iterates over predefined T_FBS_WRITE_PARAM_LOCAL objects.

    CPU: Any

    OWNER: AK
*/

#include "mnwrap.h"
#include <base.h>
#include <fbap.h>
#include <aofb.h>
#include <maifb.h>
#include <ptb.h>
#include <arfb.h>
#include <csfb.h>
#include <isfb.h>
#include <osfb.h>
#include <pidfb.h>
#include <fbs_api.h>
#include <fbif_idx.h>
#include "ptbcustomsubx.h"
#include "mnhart2ff.h"
#include "watchdog.h"
#include "mn_factory_defaults.h"

static const USIGN8 pid_bypass = 1;
static const USIGN8 pid_shed_opt = 1;
static const FLOAT pid_gain = 1.0F;
static const T_FBS_WRITE_PARAM_LOCAL Qset_PID[] =
{
    {
        .rel_idx = REL_IDX_PIDFB_BYPASS,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_PIDFB, bypass),
        .source = (const void *)&pid_bypass,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PIDFB_GAIN,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_PIDFB, gain),
        .source = (const void *)&pid_gain,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PIDFB_SHED_OPT,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_PIDFB, shed_opt),
        .source = (const void *)&pid_shed_opt,
        .startup_sync = FALSE,
    },
};

static const USIGN8 os_lockval = 1;
static const FLOAT os_array[4] = {0.0F, 50.0F, 50.0F, 100.0F};
static const T_FBS_WRITE_PARAM_LOCAL Qset_OS[] =
{
    {
        .rel_idx = REL_IDX_OSFB_LOCKVAL,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_OSFB, lockval),
        .source = (const void *)&os_lockval,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_OSFB_IN_ARRAY,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_OSFB, in_array),
        .source = (const void *)os_array,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_OSFB_OUT_ARRAY,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_OSFB, out_array),
        .source = (const void *)os_array,
        .startup_sync = FALSE,
    },
};

static const USIGN8 is_sel_type = 1;
static const T_FBS_WRITE_PARAM_LOCAL Qset_IS[] =
{
    {
        .rel_idx = REL_IDX_ISFB_SELECT_TYPE,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_ISFB, select_type),
        .source = (const void *)&is_sel_type,
        .startup_sync = FALSE,
    },
};

static const USIGN8 cs_sel_type = 3;
static const T_FBS_WRITE_PARAM_LOCAL Qset_CS[] =
{
    {
        .rel_idx = REL_IDX_CSFB_SEL_TYPE,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_CSFB, sel_type),
        .source = (const void *)&cs_sel_type,
        .startup_sync = FALSE,
    },
};

static const USIGN8 ar_arith_type = 6;
static const T_FBS_WRITE_PARAM_LOCAL Qset_AR[] =
{
    {
        .rel_idx = REL_IDX_ARFB_ARITH_TYPE,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_ARFB, arith_type),
        .source = (const void *)&ar_arith_type,
        .startup_sync = FALSE,
    },
};

static const USIGN16 aochannel = CH_AO_POSITION;
static const USIGN16 ao_io_opts = 0x0040;
static const USIGN8 ao_shed_opts = 1;
static const T_FBS_WRITE_PARAM_LOCAL Qset_AO[] =
{
    {
        .rel_idx = REL_IDX_AOFB_CHANNEL,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_AOFB, channel),
        .source = (const void *)&aochannel,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_AOFB_IO_OPTS,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_AOFB, io_opts),
        .source = (const void *)&ao_io_opts,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_AOFB_SHED_OPT,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_AOFB, shed_opt),
        .source = (const void *)&ao_shed_opts,
        .startup_sync = FALSE,
    },
};

static const USIGN16 maichannel = CH_MAI_CHANNEL1;
static const T_FBS_WRITE_PARAM_LOCAL Qset_MAI[] =
{
    {
        .rel_idx = REL_IDX_MAIFB_CHANNEL,
        .subindex = 0,
        .length = ELEMSIZE(T_FBIF_MAIFB, channel),
        .source = (const void *)&maichannel,
        .startup_sync = FALSE,
    },
};

static const BOOL generic_enable = TRUE;
static const u8 alert_warning = 1;
static const u8 alert_maint_req = 2;
static const u8 alert_device_failure = 3;
static const T_FBS_WRITE_PARAM_LOCAL Qset_PTB[] =
{
    {
        .rel_idx = REL_IDX_PTB_WORKING_TIME_ALERT,
        .subindex = PTB_SUBX_WORKING_TIME_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, working_time_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_ALERT_ACTION,
        .subindex = PTB_SUBX_ALERT_ACTION___air_supply_alert_act,
        .length = ELEMSIZE(T_FBIF_PTB, alert_action.air_supply_alert_act),
        .source = (const void *)&alert_warning,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_ALERT_ACTION,
        .subindex = PTB_SUBX_ALERT_ACTION___valve_control_alert_act,
        .length = ELEMSIZE(T_FBIF_PTB, alert_action.valve_control_alert_act),
        .source = (const void *)&alert_device_failure,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_ALERT_ACTION,
        .subindex = PTB_SUBX_ALERT_ACTION___ip_drive_current_alert_lo_act,
        .length = ELEMSIZE(T_FBIF_PTB, alert_action.ip_drive_current_alert_lo_act),
        .source = (const void *)&alert_maint_req,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_ALERT_ACTION,
        .subindex = PTB_SUBX_ALERT_ACTION___ip_drive_current_alert_hi_act,
        .length = ELEMSIZE(T_FBIF_PTB, alert_action.ip_drive_current_alert_hi_act),
        .source = (const void *)&alert_maint_req,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_ALERT_ACTION,
        .subindex = PTB_SUBX_ALERT_ACTION___supply_pressure_lolo_alert_act,
        .length = ELEMSIZE(T_FBIF_PTB, alert_action.supply_pressure_lolo_alert_act),
        .source = (const void *)&alert_maint_req,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_ALERT_ACTION,
        .subindex = PTB_SUBX_ALERT_ACTION___supply_pressure_lo_alert_act,
        .length = ELEMSIZE(T_FBIF_PTB, alert_action.supply_pressure_lo_alert_act),
        .source = (const void *)&alert_warning,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_IP_DRIVE_CURRENT_LO_ALERT,
        .subindex = PTB_SUBX_IP_DRIVE_CURRENT_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, ip_drive_current_lo_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_IP_DRIVE_CURRENT_HI_ALERT,
        .subindex = PTB_SUBX_IP_DRIVE_CURRENT_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, ip_drive_current_hi_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_TEMPERATURE_LO_ALERT,
        .subindex = PTB_SUBX_SYSTEM_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, temperature_lo_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_TEMPERATURE_HI_ALERT,
        .subindex = PTB_SUBX_SYSTEM_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, temperature_hi_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_SUPPLY_PRESSURE_LOLO_ALERT,
        .subindex = PTB_SUBX_SYSTEM_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, supply_pressure_lolo_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_SUPPLY_PRESSURE_LO_ALERT,
        .subindex = PTB_SUBX_SYSTEM_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, supply_pressure_lo_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_SUPPLY_PRESSURE_HI_ALERT,
        .subindex = PTB_SUBX_SYSTEM_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, supply_pressure_hi_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_SETPOINT_TIMEOUT_ALERT,
        .subindex = PTB_SUBX_SETPOINT_TIMEOUT_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, setpoint_timeout_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_TRAVEL_ACCUMULATION_B_ALERT,
        .subindex = PTB_SUBX_TRAVEL_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, travel_accumulation_b_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_TRAVEL_ACCUMULATION_A_ALERT,
        .subindex = PTB_SUBX_TRAVEL_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, travel_accumulation_a_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_POSITION_LOLO_ALERT,
        .subindex = PTB_SUBX_POSITION_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, position_lolo_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_POSITION_LO_ALERT,
        .subindex = PTB_SUBX_POSITION_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, position_lo_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_POSITION_HI_ALERT,
        .subindex = PTB_SUBX_POSITION_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, position_hi_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_POSITION_HIHI_ALERT,
        .subindex = PTB_SUBX_POSITION_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, position_hihi_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
    {
        .rel_idx = REL_IDX_PTB_DEVIATION_ALERT,
        .subindex = PTB_SUBX_MN_DEVIATION_ALERT___enable,
        .length = ELEMSIZE(T_FBIF_PTB, deviation_alert.enable),
        .source = (const void *)&generic_enable,
        .startup_sync = FALSE,
    },
};

typedef struct QsetList_t
{
    u8 blockid;
    u16 nelem;
    const T_FBS_WRITE_PARAM_LOCAL *ptr;
} QsetList_t;

#define QSET_ELEM(elem) .nelem = NELEM(elem), elem

static const QsetList_t QsetList[] =
{
    {
        .blockid = ID_AOFB_1,
        QSET_ELEM(Qset_AO),
    },
    {
        .blockid = ID_MAIFB_1,
        QSET_ELEM(Qset_MAI),
    },
    {
        .blockid = ID_PTB_1,
        QSET_ELEM(Qset_PTB),
    },
    {
        .blockid = ID_ARFB_1,
        QSET_ELEM(Qset_AR),
    },
    {
        .blockid = ID_CSFB_1,
        QSET_ELEM(Qset_CS),
    },
    {
        .blockid = ID_ISFB_1,
        QSET_ELEM(Qset_IS),
    },
    {
        .blockid = ID_OSFB_1,
        QSET_ELEM(Qset_OS),
    },
    {
        .blockid = ID_PIDFB_1,
        QSET_ELEM(Qset_PID),
    },
    {
        .blockid = ID_PIDFB_2,
        QSET_ELEM(Qset_PID),
    },
};


/** \brief A rather long function to reinitialize to reasonable defaults of all blocks
\return an error code
*/
fferr_t ffres_QuickSet(void)
{
    fferr_t fferr = E_OK;
    for(size_t n=0; n<NELEM(QsetList); n++)
    {
        size_t nelem = QsetList[n].nelem;
        const T_FBS_WRITE_PARAM_LOCAL *ptr = QsetList[n].ptr;
        T_FBIF_BLOCK_INSTANCE *p_block_instance = fbs_get_block_inst(QsetList[n].blockid);
        for(size_t elem=0; elem<nelem; elem++)
        {
            T_FBS_WRITE_PARAM_LOCAL local = ptr[elem]; //for Softing foolishness with const
            fferr_t fferr1 = fbs_write_param_loc(p_block_instance, &local);
            if(fferr == E_OK)
            {
                fferr = fferr1;
            }
            wdog_WatchdogTrigger();
            /* EXLPANATION:
            We do brutal watchdog tickle, bypassing syswd interface because we
            block low priority tasks. That's necessary because we don't want
            block execution while we are doing this
            */
        }
    }
    return fferr;
}
/* This line marks the end of the source */
