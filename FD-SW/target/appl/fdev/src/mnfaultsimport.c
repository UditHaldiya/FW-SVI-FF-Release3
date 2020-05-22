/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mnfaultsimport.c
    \brief Mapping APP faults to various FF reporting schemes

    CPU: Any

    OWNER: AK
*/
#include <limits.h>
//Softing headers first
#include <softing_base.h>
#include <ptb.h>
//#include <appl_int.h>

#define MODULE_ID (MOD_APPL_TRN | COMP_PAPP)


//MN FIRMWARE headers second

//Glue headers last
#include "mnfault2alert.h"
#include "ptbcustomsubx.h"

/** \brief A helper function to translate APP faults into FFP parlance
\param p_PTB - a pointer to TB info
\param[in][out] AlertsEtc - a pointer to other diag info to update (must be pre-initialized by caller)
\return forced block error bitmap (from faults directly; before alerts calculation)
*/
u16 mnfaults_Import(const T_FBIF_PTB *p_PTB, MnAlertsEtc_t *AlertsEtc)
{
    //Prime the loop
    //Removed u32 alert_map = AlertsEtc->alert_map; //Softing
    u32 block_alert_map = AlertsEtc->block_alert_map; //Vlad's
    u8 prio = AlertsEtc->priority;
    u8 xd_prio[xdX_total] = {0}; //lint !e943 Too few initializers - MISRA 3 allows it
    u16 recom_action = AlertsEtc->recom_action;
    u32 block_err_desc_1 = AlertsEtc->block_err_desc_1;

    u16 block_err = BLK_ERR_NO_ERROR;
    const u8 *fbyte = (const void *)&p_PTB->complete_status;
    CONST_ASSERT(FAULT_CODE_BYTES_REQUIRED <= sizeof(p_PTB->complete_status));
    u32 i = FAULT_CODE_BYTES_REQUIRED; //counter of fault bytes
    do
    {
        --i;
        if(fbyte[i] != 0) //only then do we go slowly bit by bit
        {
            u8_least fbit;
            //for(fbit = 0; fbit < CHAR_BIT; fbit++)
            for(fbit = 0; (i*CHAR_BIT + fbit) < MAX_FAULT_NUMBER; fbit++)
            {
                if((fbyte[i] & (1U<<fbit)) != 0)
                {
                    //fault bit set: act on it
                    const MnFaultAlarmMap_t *p = &MnFaultAlarmMap[i*CHAR_BIT + fbit];
                    block_err |= p->BlockError; //unconditional block error

                    block_err_desc_1 |= p->block_err_desc_1; //unconditional block_err_desc; may me 0


                    if(p->BlockAlertX != ALERT_NONE) //0 is otherwise reserved so we use it as an indicator of no action
                    {
                        //Need to check if alert is enabled!

                        u32 alert_map_new = block_alert_map | (1U << (p->BlockAlertX - 1));
                        if(alert_map_new > block_alert_map)
                        {
                            //remember new map
                            block_alert_map = alert_map_new;

                        }
                    }
                    if(prio < p->priority) //hoisted outside check for ALERT_NONE etc. to become independent
                    {
                        //Higher prority
                        recom_action = p->recommended_action;
                        if(p->BlockAlertX != ALERT_NONE)
                        {
                            if(p->recommended_action != RECOM_ACT_NONE)
                            {
                                recom_action = p->recommended_action;
                            }
                        }

                        prio = p->priority;
                    }
                    if(p->xd_index != xdX_total) //check if xd_error is defined
                    {
                        if(xd_prio[p->xd_index] < p->priority)
                        {
                            AlertsEtc->xd_error[p->xd_index] = p->xd_error;
                            xd_prio[p->xd_index] = p->priority;
                        }
                    }

                }
            }
        }
    } while(i != 0);

    //Write back
    AlertsEtc->block_err_desc_1 = block_err_desc_1;
    AlertsEtc->block_alert_map = block_alert_map;
    AlertsEtc->recom_action = recom_action;
    AlertsEtc->priority = prio;

    return block_err;
}
