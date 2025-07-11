/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file deviation_alert.c
    \brief functions about parameter DEVIATION_ALERT

    CPU: Any

    OWNER:
    $Date: 07/01/13 11:16p $
    $Revision: 1 $
    $Author: victoria huang $

*/
#include <softing_base.h>
#include <ptb.h>

//Glue headers last
#include "mnhart2ff.h"
#include "numutils.h"
#include "mn_deviation_alert.h"
#include "ptbcustomsubx.h"

#define MAX_DEVIATION_ALERT_TIME  (3600u)
#define MAX_DEVIATION_DEADBAND    (10u)
#define MIN_DEVIATION_DEADBAND    (9.99999977E-3f)   //0.01 in float32
#define MAX_DEVIATION_AlERT_VALUE (250.0f)
#define MIN_DEVIATION_AlERT_VALUE (9.99999977E-2f)   //0.1 in float32

/* \brief write deviation_alert parameter
    param in:
        p_block_instance: pointer to function block
        p_write:  pointer to write resource data

    return:
        FF error
*/
fferr_t ffda_WriteDeviationAlert
(
    T_FBIF_BLOCK_INSTANCE* p_block_instance,
    const T_FBIF_WRITE_DATA *p_write
)
{
    fferr_t fferr = E_OK;
    bool_t st_rev_flag = true;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    if(0 == p_write->subindex)
    {
        _MN_DEVIATION_ALERT* pAlert = (void*)p_write->source;
        float32 tempcomp1 = ABS(pAlert->alert_point - (float32)p_PTB->deviation_alert.alert_point);
        float32 tempcomp2 = ABS(pAlert->__deviation_deadband - (float32)p_PTB->deviation_alert.__deviation_deadband);
        //check if the alert_point is out of range or not
        if (pAlert->alert_point > MAX_DEVIATION_AlERT_VALUE
            || pAlert->alert_point < MIN_DEVIATION_AlERT_VALUE)
        {
            fferr = E_FB_PARA_LIMIT;
        }
        //check if the dead_band is out of range or not
        if (pAlert->__deviation_deadband > MAX_DEVIATION_DEADBAND
            || pAlert->__deviation_deadband < MIN_DEVIATION_DEADBAND)
        {
            fferr = E_FB_PARA_LIMIT;
        }
        if(pAlert->time_threshold > MAX_DEVIATION_ALERT_TIME)
        {
            fferr = E_FB_PARA_LIMIT;
        }
        //if only ALERT is changed, manully oprate the ST_REV.
        if ((tempcomp1 < FLOAT_POSITIVE_SMALL_DIFF) && (tempcomp2 < FLOAT_POSITIVE_SMALL_DIFF)
            &&(pAlert->enable == p_PTB->deviation_alert.enable))
        {
            st_rev_flag = false;
        }
    }
    else if (PTB_SUBX_MN_DEVIATION_ALERT___alert_point == p_write->subindex)
    {
        //check if the alert_point is out of range or not
        if (mn_pull_float(&p_write->source[0]) > MAX_DEVIATION_AlERT_VALUE ||
            mn_pull_float(&p_write->source[0]) < MIN_DEVIATION_AlERT_VALUE)
        {
            fferr = E_FB_PARA_LIMIT;
        }
    }
    else if (PTB_SUBX_MN_DEVIATION_ALERT_____deviation_deadband == p_write->subindex)
    {
        //check if the dead_band is out of range or not
        if (mn_pull_float(&p_write->source[0]) > MAX_DEVIATION_DEADBAND ||
            mn_pull_float(&p_write->source[0]) < MIN_DEVIATION_DEADBAND)
        {
            fferr = E_FB_PARA_LIMIT;
        }
    }
    else if (PTB_SUBX_MN_DEVIATION_ALERT___time_threshold == p_write->subindex)
    {
        u32* p_tmp = (u32*)(void*)p_write->source;
        if(MAX_DEVIATION_ALERT_TIME < *p_tmp)
        {
            fferr = E_FB_PARA_LIMIT;
        }
    }
    else
    {
        //no other case are possible. REVIEW with param definition!
    }

    if(fferr == E_OK)
    {
        if(st_rev_flag)
        {
            fferr = fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_DEVIATION_ALERT);
        }
    }

    return fferr;
}

