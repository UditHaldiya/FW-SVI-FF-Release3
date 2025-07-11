/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_supply_pressure_alert.c
    \brief functions about parameter SUPPLY_PRESSURE_HI_ALERT,SUPPLY_PRESSURE_LO_ALERT,
    SUPPLY_PRESSURE_LOLO_ALERT

    CPU: Any

    OWNER:
*/
#include <softing_base.h>
#include <ptb.h>

//Glue headers last
#include "mnhart2ff.h"
#include "mn_supply_pressure_alert.h"
#include "pressure_range.h"
#include "numutils.h"
#include "ptbcustomsubx.h"
#include "mnassert.h"

/* \brief write supply_pressure_hi_alert, supply_pressure_lo_alert,
    supply_pressure_lolo_alert parameter
    \param p_block_instance - pointer to function block
    \param p_write - pointer to write resource data

    \return FF error
*/
fferr_t fftbsp_WriteSupplyPressureAlert
(
    T_FBIF_BLOCK_INSTANCE* p_block_instance,
    const T_FBIF_WRITE_DATA *p_write
)
{
    fferr_t fferr = E_OK;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    float32  tempcomp1;
    float32  tempcomp2;

    u16 uCurrent_unit = p_PTB->pressure_range.units;
    //Are the units valid yet?

    u8 index = PresAlertHi;

    switch(p_write->rel_idx)
    {
        case REL_IDX_PTB_SUPPLY_PRESSURE_HI_ALERT:
            break;
        case REL_IDX_PTB_SUPPLY_PRESSURE_LO_ALERT:
            index = PresAlertLo;
            break;
        case REL_IDX_PTB_SUPPLY_PRESSURE_LOLO_ALERT:
            index = PresAlertLoLo;
            break;
        default:
            fferr = E_FB_PARA_CHECK;
            break;
    }

    bool_t st_rev_flag = true;

    if(fferr == E_OK)
    {
        {
            PresAlertConf_t pac; //Alert in internal representation (psi)
            const PresAlertConf_t *p = ffpres_GetAlertConf(index, &pac);
            MN_DBG_ASSERT(p!=NULL);
            if(0 == p_write->subindex)
            {
                _SYSTEM_ALERT* pAlert = (void*)p_write->source;

                float32 new_alert_point = ffpres_Eng2Internal(pAlert->alert_point, uCurrent_unit);
                float32 new_deadband = ffpres_Eng2Internal(pAlert->deadband, uCurrent_unit);

                tempcomp1 = ABS(new_alert_point - pac.alert_point);
                tempcomp2 = ABS(new_deadband - pac.deadband);
                //if only ALERT is changed, manully oprate the ST_REV.
                if ((tempcomp1 < FLOAT_POSITIVE_SMALL_DIFF) && (tempcomp2 < FLOAT_POSITIVE_SMALL_DIFF)
                    && (pAlert->enable == pac.enable))
                {
                    st_rev_flag = false;
                }

                pac.alert_point = new_alert_point;
                pac.deadband = new_deadband;
                pac.enable = pAlert->enable;

            }
            else if (PTB_SUBX_SYSTEM_ALERT___alert_point == p_write->subindex)
            {
                pac.alert_point = ffpres_Eng2Internal(mn_pull_float(&p_write->source[0]), uCurrent_unit);
        #if 0 //to Set function
                //check if the alert_point is out of range or not
                if (mn_pull_float(&p_write->source[0]) > fmax_alert_point ||
                    mn_pull_float(&p_write->source[0]) < PRESSURE_MIN)
                {
                    fferr = E_FB_PARA_LIMIT;
                }
        #endif
            }
            else if (PTB_SUBX_SYSTEM_ALERT___deadband == p_write->subindex)
            {
                pac.deadband = ffpres_Eng2Internal(mn_pull_float(&p_write->source[0]), uCurrent_unit);
        #if 0 //to Set function
                //check if the dead_band is out of range or not
                if (mn_pull_float(&p_write->source[0]) > fmax_dead_band ||
                    mn_pull_float(&p_write->source[0]) < PRESSURE_MIN)
                {
                    fferr = E_FB_PARA_LIMIT;
                }
        #endif
            }
            else if (PTB_SUBX_SYSTEM_ALERT___enable == p_write->subindex)
            {
                pac.enable = p_write->source[0];
            }
            else
            {
                fferr = E_FB_PARA_CHECK;
            }
            if(fferr == E_OK)
            {
                if(st_rev_flag)
                {
                    ErrorCode_t err = ffpres_SetAlertConf(index, &pac);
                    if(err == ERR_OK)
                    {
                        fferr = fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_SUPPLY_PRESSURE_HI_ALERT); //Should be OK for all supply alerts
                    }
                    else
                    {
                        fferr = E_FB_PARA_CHECK;
                    }
                }
            }
        }
    }
    return fferr;
}

/** \brief Read helper for supply pressure alert: rescales pressures to eng. units
\param p_PTB - a pointer to TB instance
\param p_read - a pointer to output stream
\return FF error
*/
fferr_t ffpres_ReadSupplyPressureAlert(T_FBIF_PTB *p_PTB, const T_FBIF_READ_DATA *p_read)
{
    u16 uCurrent_unit = p_PTB->pressure_range.units;
    fferr_t fferr = E_OK;

    //Which alert are we dealing with?
    _SYSTEM_ALERT *aptr = &p_PTB->supply_pressure_hi_alert;
    u8 index = PresAlertHi;

    switch(p_read->rel_idx)
    {
        case REL_IDX_PTB_SUPPLY_PRESSURE_HI_ALERT:
            break;
        case REL_IDX_PTB_SUPPLY_PRESSURE_LO_ALERT:
            aptr = &p_PTB->supply_pressure_lo_alert;
            index = PresAlertLo;
            break;
        case REL_IDX_PTB_SUPPLY_PRESSURE_LOLO_ALERT:
            aptr = &p_PTB->supply_pressure_lolo_alert;
            index = PresAlertLoLo;
            break;
        default:
            fferr = E_FB_PARA_CHECK;
            break;
    }

    const PresAlertConf_t *p = ffpres_GetAlertConf(index, NULL);
    if(fferr == E_OK)
    {
        if(p == NULL)
        {
            //It can only be an invalid index which means no units yet
            fferr = E_FB_TEMP_ERROR;
        }
        else
        {
            aptr->curr_value = ffpres_ReadPressureEngByIndex(pres_supply);
            aptr->alert_point = ffpres_Internal2Eng(p->alert_point, uCurrent_unit);
            aptr->deadband = ffpres_Internal2Eng(p->deadband, uCurrent_unit);
            aptr->enable = (p->enable==0)?0:1;
            //By *current* design, do not read saved historic_alert! It is not persistent.
        }
    }
    return fferr;
}
