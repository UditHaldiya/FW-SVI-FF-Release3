/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mnptberrors.c
    \brief MN part of TB errors of all sorts (mostly, aggregation of work done by others)

    CPU: Any

    OWNER: AK
*/
#include <limits.h>
//Softing headers first
#include <softing_base.h>
#include <appl_int.h>
#include <ptb.h>
#include <resb.h> //required to access the RB

#define MODULE_ID (MOD_APPL_TRN | COMP_PAPP)

//MN FIRMWARE headers second

//Glue headers last
#include "mnfault2alert.h"
#include "mnhart2ff.h"
#include "appl_alert.h"
#include "ptbcustomsubx.h"
#include "mntbmspff.h"
#include "mnipcff.h"

#define BLK_ERR_SOFTING_SET (BLK_ERR_LINK_CONFIG_ERR)
#define BLK_ERR_SOFTING_SET1 (BLK_ERR_LOST_STATIC_DATA|BLK_ERR_LOST_NV_DATA)

//Possible values for "alert_action.block_err_map"
#define BLK_ERR_ALERT_MAP_TO_RB mapped_to_rb
#define BLK_ERR_ALERT_IN_TB     stays_in_tb
#define BLK_ERR_ALERT_FF_890    perFF890

static MnAlertsEtc_t AlertsEtcIF =
{
    //Removed .alert_map = 0U,
    .block_alert_map = 0U,
    .recom_action = FD_NO_RECOMM_ACT,
    .priority = 0,
};

#define SAMPLE_ON_CLEAR 0x01U
#define SAMPLE_ON_SET 0x02U

static const u8 AlarmTriggerConf[] =
{
    [alert_silent] = 0,
    [alert_warn] = 0,
    [alert_maint] = 0,
    [alert_failure] = 0,
    [alert_silent_tOff] = SAMPLE_ON_CLEAR,
    [alert_warn_tOff] = SAMPLE_ON_CLEAR,
    [alert_maint_tOff] = SAMPLE_ON_CLEAR,
    [alert_failure_tOff] = SAMPLE_ON_CLEAR,
    [alert_silent_tOn] = SAMPLE_ON_SET,
    [alert_warn_tOn] = SAMPLE_ON_SET,
    [alert_maint_tOn] = SAMPLE_ON_SET,
    [alert_failure_tOn] = SAMPLE_ON_SET,
    [alert_silent_tChange] = SAMPLE_ON_SET|SAMPLE_ON_CLEAR,
    [alert_warn_tChange] = SAMPLE_ON_SET|SAMPLE_ON_CLEAR,
    [alert_maint_tChange] = SAMPLE_ON_SET|SAMPLE_ON_CLEAR,
    [alert_failure_tChange] = SAMPLE_ON_SET|SAMPLE_ON_CLEAR,
};

static const u16 AlarmConfXlate[] =
{
    [alert_silent] = BLK_ERR_NO_ERROR,
    [alert_warn] = BLK_ERR_DEV_NEEDS_MAINT_SOON,
    [alert_maint] = BLK_ERR_DEV_NEEDS_MAINT_NOW,
    [alert_failure] = BLK_ERR_DEV_FAULT_STATE_SET, //or BLK_ERR_OUT_OF_SERVICE? With the new design?
    [alert_silent_tOff] = BLK_ERR_NO_ERROR,
    [alert_warn_tOff] = BLK_ERR_DEV_NEEDS_MAINT_SOON,
    [alert_maint_tOff] = BLK_ERR_DEV_NEEDS_MAINT_NOW,
    [alert_failure_tOff] = BLK_ERR_DEV_FAULT_STATE_SET, //or BLK_ERR_OUT_OF_SERVICE? With the new design?
    [alert_silent_tOn] = BLK_ERR_NO_ERROR,
    [alert_warn_tOn] = BLK_ERR_DEV_NEEDS_MAINT_SOON,
    [alert_maint_tOn] = BLK_ERR_DEV_NEEDS_MAINT_NOW,
    [alert_failure_tOn] = BLK_ERR_DEV_FAULT_STATE_SET, //or BLK_ERR_OUT_OF_SERVICE? With the new design?
    [alert_silent_tChange] = BLK_ERR_NO_ERROR,
    [alert_warn_tChange] = BLK_ERR_DEV_NEEDS_MAINT_SOON,
    [alert_maint_tChange] = BLK_ERR_DEV_NEEDS_MAINT_NOW,
    [alert_failure_tChange] = BLK_ERR_DEV_FAULT_STATE_SET, //or BLK_ERR_OUT_OF_SERVICE? With the new design?
};

CONST_ASSERT(NELEM(AlarmTriggerConf)==NELEM(AlarmConfXlate)); //sanity check

const MnAlertsEtc_t *MnAlert_GetAlertsEtc(MnAlertsEtc_t *dst)
{
    if(dst != NULL)
    {
        *dst = AlertsEtcIF;
    }
    return &AlertsEtcIF;
}

#if 0 //future replacement; incomplete
typedef struct FdMap_t
{
    u8 u8 fd_cond; //for RB::FD_SIMULATE.ALERT
    u8 recommen_act; //for RB::FD_RECOMMEN_ACT
    u8 prio; //priority of recommended action, for RB::FD_RECOMMEN_ACT
} FdMap_t;

/** \brief Mapping of alert bit numbers to RB::FD_SIMULATE.ALERT and RB::FD_RECOMMEN_ACT

We take advantage of (and hijack) TB subindices being 1-based bit numbers in alerts
bitmap readily provided.
The value in the array is 1-based bit number in RB. We need 1-based in case there be an empty
slot (initialized therefore to 0).
*/
static const FdMap_t AlertToFdMap[] =
{
    [ALERT_INDEX(deviation_alert)]      = {.fd_cond=FDCOND_DEVIATION_ALERT_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(position_hihi_alert)]  = {.fd_cond=FDCOND_POSITION_LARGE_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(position_hi_alert)]    = {.fd_cond=FDCOND_POSITION_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(position_lo_alert)]    = {.fd_cond=FDCOND_POSITION_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(position_lolo_alert)]  = {.fd_cond=FDCOND_POSITION_LARGE_EXCURSION_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(travel_accumulation_a_alert)]    = {.fd_cond=FDCOND_TRAVEL_A_ALERT_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(travel_accumulation_b_alert)]    = {.fd_cond=FDCOND_TRAVEL_B_ALERT_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(cycle_counter_a_alert)]     = {.fd_cond=FDCOND_TRAVEL_A_ALERT_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(cycle_counter_b_alert)]     = {.fd_cond=FDCOND_TRAVEL_B_ALERT_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(supply_pressure_hi_alert)]    = {.fd_cond=FDCOND_SUPPLY_PRESSURE_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(supply_pressure_lo_alert)]    = {.fd_cond=FDCOND_SUPPLY_PRESSURE_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(supply_pressure_lolo_alert)]  = {.fd_cond=FDCOND_SUPPLY_PRESSURE_LOLO_ALERT_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(temperature_hi_alert)]        = {.fd_cond=FDCOND_TEMPERATURE_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(temperature_lo_alert)]        = {.fd_cond=FDCOND_TEMPERATURE_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(set_point_timeout_alert)]     = {.fd_cond=FDCOND_SETPOINT_TIMEOUT_ALERT_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(ip_drive_current_alert_hi)]       = {.fd_cond=FDCOND_IP_DRIVE_CURRENT_EXCURSION_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(ip_drive_current_alert_lo)]       = {.fd_cond=FDCOND_IP_DRIVE_CURRENT_EXCURSION_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(working_time_alert)]       = {.fd_cond=FDCOND_WORKING_TIME_ALERT_BIT, .recommen_act=, .prio=,},

    [ALERT_INDEX(near_close_alert)]     = {.fd_cond=FDCOND_NEAR_CLOSE_ALERT_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(sensor_failure_alert)]  = {.fd_cond=FDCOND_ENVIRONMENT_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(processor_alert)]      = {.fd_cond=FDCOND_HARDWARE_BIT, .recommen_act=, .prio=,},
    [ALERT_INDEX(valve_control_alert)]  = {.fd_cond=FDCOND_VALVE_CONTROL_ALERT_BIT, .recommen_act=RECOM_ACT_ACTUATOR, .prio=2,},
    [ALERT_INDEX(commissioning_alert)]        = {.fd_cond=FDCOND_ENVIRONMENT_BIT, .recommen_act=RECOM_ACT_STOPS, .prio=3,},
    [ALERT_INDEX(air_supply_alert)]     = {.fd_cond=FDCOND_VALVE_CONTROL_ALERT_BIT, .recommen_act=RECOM_ACT_SUPPLY, .prio=2,},
    [ALERT_INDEX(supporting_hardware_alert)]       = {.fd_cond=FDCOND_HARDWARE_BIT, .recommen_act=, .prio=,},
};
#endif //0 future replacement; incomplete

/** \brief Mapping of alert bit numbers to RB::FD_SIMULATE.ALERT and RB::FD_RECOMMEN_ACT

The value in the array is 1-based bit number in RB. We need 1-based in case there be an empty
slot (initialized therefore to 0).
*/
static const u8 AlertToFdMap[] =
{
    [ALERT_INDEX(deviation_alert)]      = FDCOND_DEVIATION_ALERT_BIT + 1U,  //[0]

    [ALERT_INDEX(position_hihi_alert)]  = FDCOND_POSITION_LARGE_EXCURSION_BIT + 1U,  //[1]
    [ALERT_INDEX(position_hi_alert)]    = FDCOND_POSITION_EXCURSION_BIT + 1U,  //[2]
    [ALERT_INDEX(position_lo_alert)]    = FDCOND_POSITION_EXCURSION_BIT + 1U,  //[3]
    [ALERT_INDEX(position_lolo_alert)]  = FDCOND_POSITION_LARGE_EXCURSION_BIT + 1U,  //[4]

    [ALERT_INDEX(travel_accumulation_a_alert)]    = FDCOND_TRAVEL_A_ALERT_BIT + 1U,  //[7]
    [ALERT_INDEX(travel_accumulation_b_alert)]    = FDCOND_TRAVEL_B_ALERT_BIT + 1U,  //[8]

    [ALERT_INDEX(cycle_counter_a_alert)]     = FDCOND_TRAVEL_A_ALERT_BIT + 1U,  //[9]
    [ALERT_INDEX(cycle_counter_b_alert)]     = FDCOND_TRAVEL_B_ALERT_BIT + 1U,  //[10]

    [ALERT_INDEX(supply_pressure_hi_alert)]    = FDCOND_SUPPLY_PRESSURE_EXCURSION_BIT + 1U,  //[12]
    [ALERT_INDEX(supply_pressure_lo_alert)]    = FDCOND_SUPPLY_PRESSURE_EXCURSION_BIT + 1U,  //[13]
    [ALERT_INDEX(supply_pressure_lolo_alert)]  = FDCOND_SUPPLY_PRESSURE_LOLO_ALERT_BIT + 1U,  //[14]
    [ALERT_INDEX(temperature_hi_alert)]        = FDCOND_TEMPERATURE_EXCURSION_BIT + 1U,  //[15]
    [ALERT_INDEX(temperature_lo_alert)]        = FDCOND_TEMPERATURE_EXCURSION_BIT + 1U,  //[16]
    [ALERT_INDEX(setpoint_timeout_alert)]     = FDCOND_SETPOINT_TIMEOUT_ALERT_BIT + 1U,  //[5]

    [ALERT_INDEX(ip_drive_current_alert_hi)]       = FDCOND_IP_DRIVE_CURRENT_EXCURSION_BIT + 1U,  //[17]
    [ALERT_INDEX(ip_drive_current_alert_lo)]       = FDCOND_IP_DRIVE_CURRENT_EXCURSION_BIT + 1U,  //[18]

    [ALERT_INDEX(working_time_alert)]       = FDCOND_WORKING_TIME_ALERT_BIT + 1U,  //[11]

    [ALERT_INDEX(near_close_alert)]     = FDCOND_NEAR_CLOSE_ALERT_BIT + 1U,  //[6]
    [ALERT_INDEX(sensor_failure_alert)]  = FDCOND_ENVIRONMENT_BIT + 1U,  //[19]
    [ALERT_INDEX(processor_alert)]      = FDCOND_HARDWARE_BIT + 1U,  //[]
    [ALERT_INDEX(valve_control_alert)]  = FDCOND_VALVE_CONTROL_ALERT_BIT + 1U,  //[20]
    [ALERT_INDEX(commissioning_alert)]        = FDCOND_ENVIRONMENT_BIT + 1U,  //[21]
    [ALERT_INDEX(air_supply_alert)]     = FDCOND_VALVE_CONTROL_ALERT_BIT + 1U,  //[22]
    [ALERT_INDEX(supporting_hardware_alert)]       = FDCOND_HARDWARE_BIT + 1U,  //[23]
};

typedef struct block_err_report_map_t
{
    u16 rb_mask;
    u16 tb_mask;
} block_err_report_map_t;

static const block_err_report_map_t block_err_report_map[] =
{
    [0] = {0,0},
    [BLK_ERR_ALERT_MAP_TO_RB] =
    {
        .rb_mask = BLK_ERR_DEV_NEEDS_MAINT_SOON | BLK_ERR_DEV_NEEDS_MAINT_NOW\
                                     | BLK_ERR_DEV_FAULT_STATE_SET | BLK_ERR_LOST_NV_DATA | BLK_ERR_MEMORY_FAILURE  \
                                     | BLK_ERR_OUTPUT_FAILURE | BLK_ERR_OTHER \
                                     | BLK_ERR_POWER_UP,
        .tb_mask = 0xFFFFU, //everything
    },
    [BLK_ERR_ALERT_IN_TB] =
    {
        .rb_mask = 0U, //nothing
        .tb_mask = 0xFFFFU, //everything
    },
    [BLK_ERR_ALERT_FF_890] =
    {
        .rb_mask = BLK_ERR_DEV_NEEDS_MAINT_SOON | BLK_ERR_DEV_NEEDS_MAINT_NOW \
                                     | BLK_ERR_LOST_NV_DATA \
                                     | BLK_ERR_DEV_FAULT_STATE_SET | BLK_ERR_LOST_STATIC_DATA | BLK_ERR_MEMORY_FAILURE \
                                     | BLK_ERR_POWER_UP,
        .tb_mask = BLK_ERR_OTHER | BLK_ERR_BLOCK_CONFIG_ERR | BLK_ERR_LOCAL_OVERRIDE \
                                     | BLK_ERR_INPUT_FAILURE | BLK_ERR_OUTPUT_FAILURE \
                                     | BLK_ERR_READBACK_CHECK_FAILED | BLK_ERR_OUT_OF_SERVICE
    },

};

/** \brief Centralized collector of errors, xd_errors and what not
\param p_block_instance - a pointer to PTB
*/
void mnptb_ProcErrors(const T_FBIF_BLOCK_INSTANCE *p_block_instance)
{

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    //Pre-initialize AlertsEtc
    MnAlertsEtc_t AlertsEtc =
    {
        .block_err_desc_1 = 0U,
        .block_alert_map = 0U,
        .recom_action = FD_NO_RECOMM_ACT,
        .xd_error = {0}, //lint !e943 This init is allowed by MISRA 3
        .priority = 0,
    };

    //The alerts map to RB fd_simulate.active
    u32 block_alert_map = AlertsEtc.block_alert_map;

    //Begin with block errors
    u16 block_err = 0;

    if(p_PTB->mode_blk.target != MODE_OS)
    {
        block_err = mnfaults_Import(p_PTB, &AlertsEtc); //complete it!
        block_alert_map |= AlertsEtc.block_alert_map;

        /*Add alerts from FFP alerts
        */
        block_alert_map |= Execute_PTB_Alerts(p_block_instance);

        //Now alert map is complete, so we can push it into alerts log
        alert_WriteAlertLog(block_alert_map);
    }

    //Now, go over block alerts bitmap and set TB goodies
    //CONST_ASSERT(sizeof(p_PTB->alert_action.mapped_to_rb) == 1);
    CONST_ASSERT(MN_OFFSETOF(_ALERT_ACTION, block_err_map) == 0);
    const u8 *aconf = (const u8 *)&p_PTB->alert_action + sizeof(p_PTB->alert_action.block_err_map);
    u8 *astate = (u8 *)&p_PTB->alert_state;
    u16 *acount = (u16 *)&p_PTB->alert_counters; //lint !e740 cast of struct ptr to u16 ptr: struct is all u16's

    bool_t trigger_sample = false;

    for(u8_least bit=0; bit < sizeof(p_PTB->alert_state); bit++)
    {
        u8 c = aconf[bit];
        if(c < NELEM(AlarmConfXlate)) //IOW, ignore invalid configuration silently
        {
            if( (block_alert_map & (1U<<bit)) != 0U)
            {
                block_err |= AlarmConfXlate[c]; //block errors from configurable alerts only

                if(astate[bit] == 0)
                {
                    if((AlarmTriggerConf[c] & SAMPLE_ON_SET) != 0U)
                    {
                        trigger_sample = true;
                    }
                    osif_disable_all_tasks();

                    astate[bit] = 1;
                    acount[bit] = MIN(acount[bit]+1, UINT16_MAX);

                    osif_enable_all_tasks();
                }
            }
            else
            {
                if(astate[bit] != 0)
                {
                    if((AlarmTriggerConf[c] & SAMPLE_ON_CLEAR) != 0U)
                    {
                        trigger_sample = true;
                    }

                    astate[bit] = 0;
                }
            }
        }
        else
        {
            astate[bit] = 0;
        }
    }

    if(trigger_sample)
    {
        mnipc_DhogRequest();
    }


    //Mandated block error (FF-890 #4.4.3.6, FF-902 #3.4.5)
    if((AlertsEtc.xd_error[xdX_pos] != 0) || (AlertsEtc.xd_error[xdX_pressure] != 0)
       || (AlertsEtc.xd_error[xdX_temperature] != 0))
    {
        block_err |= BLK_ERR_OTHER;
    }

    //Block errors due to FFP events
    if(p_PTB->mode_blk.actual == MODE_OS)
    {
        block_err |= BLK_ERR_OUT_OF_SERVICE;
    }
    if(p_PTB->mode_blk.actual == MODE_LO)
    {
        block_err |= BLK_ERR_LOCAL_OVERRIDE;
    }


    /* BLK_ERR_SIMULATE_ACTIVE not supported in TB.
    It is reported in RB.
    */

    /* BLK_ERR_DEV_FAULT_STATE_SET not supported in TB.
    It is reported in RB.
    */

    //FD map calculation
    u32 fdmap = appl_dia_check_function();

    /* We are also saying TRANSDUCER_BLOCK_DOES_NOT_WORK_PROPERLY if
    target mode is AUTO and actual is not
    */
    if(ipc_IsModeChangeFailed())
    {
        fdmap |= FDCOND_TRANSDUCER_BLOCK_DOES_NOT_WORK_PROPERLY;
    }

    if((fdmap & FDCOND_TRANSDUCER_BLOCK_DOES_NOT_WORK_PROPERLY) != 0)
    {
        AlertsEtc.recom_action = RECOM_ACT_MODE;
    }
    if( (block_err & BLK_ERR_READBACK_CHECK_FAILED) != 0U)
    {
        fdmap |= 1U << FDCOND_HART_COMMUNICATION_LOST_BIT;
    }

    for(u8_least n=0; n<NELEM(AlertToFdMap); n++)
    {
        if((block_alert_map & (1U<<n)) != 0U) //alert exists?
        {
            u8 fd = AlertToFdMap[n];
            if(fd != 0U) //mapped?
            {
                fdmap |= 1U<<(fd-1U);
            }
        }
    }

    //---------- Updating block error -------------
    osif_disable_all_tasks();

    u16 old_block_err = p_PTB->block_err;
    u16 softing_block_err = (old_block_err & (BLK_ERR_SOFTING_SET|BLK_ERR_SOFTING_SET1)); //preserve Softing bits
    block_err |= softing_block_err;

    //Apportion block_err between TB and RB
    u8_least index = p_PTB->alert_action.block_err_map;
    index = CLAMP(index, 1U, NELEM(block_err_report_map)-1U); //silently fix errors
    AlertsEtc.rb_block_err = block_err & block_err_report_map[index].rb_mask;
    block_err &= block_err_report_map[index].tb_mask;
    p_PTB->block_err = block_err;

    AlertsEtcIF = AlertsEtc;

#if 0
    //Update RB error according to value of "p_PTB->alert_action.block_err_map"
    //get RB block instance by ID
    T_FBIF_BLOCK_INSTANCE *pRB_inst = fbs_get_block_inst(ID_RESB_1);
    if (pRB_inst != NULL)
    {
        T_FBIF_RESB *p_RB = pRB_inst->p_block_desc->p_block;
        if (p_RB != NULL)
        {
            if (p_PTB->alert_action.block_err_map == BLK_ERR_ALERT_MAP_TO_RB)
            {
                //first clear old alerts errors
                p_RB->block_err &= ~(BLK_ERR_DEV_NEEDS_MAINT_SOON | BLK_ERR_DEV_NEEDS_MAINT_NOW \
                                     | BLK_ERR_LOST_NV_DATA | BLK_ERR_LOST_STATIC_DATA \
                                     | BLK_ERR_MEMORY_FAILURE | BLK_ERR_OUTPUT_FAILURE | BLK_ERR_OTHER);

                //set new alerts errors
                p_RB->block_err |= (block_err & (BLK_ERR_DEV_NEEDS_MAINT_SOON | BLK_ERR_DEV_NEEDS_MAINT_NOW\
                                     | BLK_ERR_DEV_FAULT_STATE_SET | BLK_ERR_LOST_NV_DATA \
                                     | BLK_ERR_LOST_STATIC_DATA | BLK_ERR_MEMORY_FAILURE \
                                     | BLK_ERR_OUTPUT_FAILURE | BLK_ERR_OTHER));
            }
        }
    }
#endif

    osif_enable_all_tasks();

    /* update block alarm */
    u16 new_block_err = block_err & ~old_block_err; //clear out previous block errors
    T_APPL_TB_DATA *p_PTB_data = p_block_instance->p_block_data;

    ffbl_update_block_alarm(p_block_instance->p_block_desc->block_id,
                            p_block_instance->p_block_desc->idx_blk_alm,
                            new_block_err,
                            &p_PTB_data->old_block_alarm_bits);

    //---------- Updating diag alerts -------------
    //This replaces appl_dia_update_field_diagnostics() in appl_dia.c
    osif_disable_all_tasks();

    appl_dia_set_all_fd_conditions(fdmap);

    osif_enable_all_tasks();


    /* on to xd errors. They are not affected by FFP events other than
    as emulated when no IPC (flash failure or IPC failure)
    */
    p_PTB->xd_error_pos = AlertsEtc.xd_error[xdX_pos];
    p_PTB->xd_error_pressure = AlertsEtc.xd_error[xdX_pressure];
    p_PTB->xd_error_temperature = AlertsEtc.xd_error[xdX_temperature];

}

/* This line marks the end of the source */
