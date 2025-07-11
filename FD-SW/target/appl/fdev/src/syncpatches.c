/*
Copyright 2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file syncpatches.c
    \brief Where block parameters share a member, they must be kept together in
        a single NV object. This file replaces TB-to-NV automation to support objects
        of such unfortunate properties.

    CPU: Any

    OWNER: AK
*/

#include "mnwrap.h"
#include "crc.h"
#include "nvram.h"
#include "syncpatches.h"
#include "ptbcustomsubx.h"
#include <fbif_dcl.h>
#include "appl_alert.h"
#include "oswrap.h"
#include "TBALERTSTRENDS_config.h"

static TravelAlert_t TravelAlert;

#if 0
static u32 saved_accum[NELEM(TravelAlert.travel_alert)];
void travel_SaveAccum(void)
{
    for(size_t n=0; n<NELEM(TravelAlert.travel_alert); n++)
    {
        saved_accum[n] = TravelAlert.travel_alert[n].travel_accumulation;
    }
}
#endif //0

/** \brief A get function with mirroring data in live PTB object
\param dst - destination buffer (may be NULL)
\return a pointer to live TravelAlert_t object
*/
const TravelAlert_t *travel_Get(TravelAlert_t *dst)
{
    return STRUCT_TESTGET(&TravelAlert, dst);
}

//lint -esym(458, travel_SetInRAM) taking address is still atomic
/** \brief A NON-standard set function (RAM only)

Attempts to preserve travel_accumulation on restart defaults
Pre-requisites: travel_SaveAccum() must be called first

\param src - a pointer to source buffer
\return an error code
*/
static void travel_SetInRAM(const TravelAlert_t *src)
{
    TravelAlert_t src_default;
#if 0
    bool_t need_reinit_tb = false;
#endif //0
    if(src == NULL)
    {
        alert_RestartTravelAlert(); //handling restart to defaults
        src_default.travel_alert[0] = c_ptb.travel_accumulation_a_alert;
        src_default.travel_alert[1] = c_ptb.travel_accumulation_a_alert; //Same!
#if 0
        if(oswrap_IsOSRunning())
        {
            //restore accumulated travel
            src_default.travel_alert[0].travel_accumulation = saved_accum[0];
            src_default.travel_alert[1].travel_accumulation = saved_accum[1];
            need_reinit_tb = true;
        }
#endif //0
        src = &src_default;
    }
    //leave range checking for the application

    //leave this for the application, too
    //(void)fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?

    osif_disable_all_tasks();
    STRUCT_GET(src, &TravelAlert);
#if 0
    if(need_reinit_tb)
    {
        alert_RestartTravelAlert();
    }
#endif //0
    osif_enable_all_tasks();
}

/** \brief A NON-standard set function
\param src - a pointer to source buffer
\return an error code
*/
ErrorCode_t travel_Set(const TravelAlert_t *src)
{
    travel_SetInRAM(src);
    return ram2nvramAtomic(NVRAMID_TravelAlert);
}


static CycleCounterAlert_t CycleCounterAlert;

/** \brief A get function with mirroring data in live PTB object
\param dst - destination buffer (may be NULL)
\return a pointer to live TravelAlert_t object
*/
const CycleCounterAlert_t *ccalert_Get(CycleCounterAlert_t *dst)
{
    return STRUCT_TESTGET(&CycleCounterAlert, dst);
}

/** \brief A standard set function
\param src - a pointer to source buffer
\return an error code
*/
ErrorCode_t ccalert_Set(const CycleCounterAlert_t *src)
{
    CycleCounterAlert_t src_default;
    if(src == NULL)
    {
        src_default.ccalert[0] = c_ptb.cycle_counter_a_alert;
        src_default.ccalert[1] = c_ptb.cycle_counter_a_alert; //Same!
        src = &src_default;
    }
    //leave range checking for the application

    //leave this for the application, too
    //(void)fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?

    STRUCT_GET(src, &CycleCounterAlert);

    return ram2nvramAtomic(NVRAMID_CycleCounterAlert);
}

// =================== binding to PTB ==================
//---------- identical scheme for cycle counter and travel alerts ===========

//---------- Cycle Counter Alerts -----------------
static float32 ccacc_FindRequestedDeadband(const T_FBIF_WRITE_DATA* p_write)
{
    float32 deadband = 0.0f;
    switch (p_write->subindex)
    {
        case PTB_SUBX_CYCLE_COUNTER_ALERT___deadband_ab:
        {
            deadband = *((float32*)(void*)p_write->source);
            break;
        }
        case 0:
        {
            _CYCLE_COUNTER_ALERT *pAlert = (void*)p_write->source;
            deadband = pAlert->deadband_ab;
            break;
        }
        default:
        {
            break;
        }
    }
    return deadband;
}

/** \brief Rescale back to external representation
*/
void ccalert_ReadCycleCounterAlert(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_READ_DATA* p_read)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    u8_least index;
    _CYCLE_COUNTER_ALERT *p;
    if(p_read->rel_idx == REL_IDX_PTB_CYCLE_COUNTER_A_ALERT)
    {
        index = 0U;
        p = &p_PTB->cycle_counter_a_alert;
    }
    else
    {
        index = 1U;
        p = &p_PTB->cycle_counter_b_alert;
    }

#if TBALERTSTRENDS_SELECTION_CYCLE_COUNT == (TBALERTSTRENDS_OPTIONS_CYCLE_COUNT_OPTION_SCALED)
    float32 scale = Travel_ScaleToExternal(p_PTB);
    _CYCLE_COUNTER_ALERT ca = CycleCounterAlert.ccalert[index];
    ca.deadband_ab *= scale;
    *p = ca;
#else
    *p = CycleCounterAlert.ccalert[index];
#endif
}

fferr_t ccalert_TestCycleCounterAlert(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write)
{
    fferr_t fferr = E_OK;


    if(PTB_SUBX_CYCLE_COUNTER_ALERT___deadband_ab == p_write->subindex || 0 == p_write->subindex)
    {
        float32 deadband = ccacc_FindRequestedDeadband(p_write);
#if TBALERTSTRENDS_SELECTION_CYCLE_COUNT == (TBALERTSTRENDS_OPTIONS_CYCLE_COUNT_OPTION_SCALED)
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        float32 scale = Travel_ScaleToInternal(p_PTB);
        deadband *= scale;
#else
        UNUSED_OK(p_block_instance);
#endif
        if(deadband > CYCLE_COUNTER_ALERT_deadband_ab_MAX_VALUE || deadband < CYCLE_COUNTER_ALERT_deadband_ab_MIN_VALUE)
        {
            fferr = E_FB_PARA_CHECK;
        }
    }
    return fferr;
}

static fferr_t alert_CommitCycleCounterAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    //We are setting out to write data to NVMEM; increment ST_REV first
    fferr_t fferr = fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?

    if(fferr == E_OK)
    {
        CycleCounterAlert_t ta = CycleCounterAlert;
        Struct_Test(CycleCounterAlert_t, &CycleCounterAlert);
        ta.ccalert[0] = p_PTB->cycle_counter_a_alert;
#if TBALERTSTRENDS_SELECTION_CYCLE_COUNT == (TBALERTSTRENDS_OPTIONS_CYCLE_COUNT_OPTION_SCALED)
        float32 scale = Travel_ScaleToInternal(p_PTB);
        ta.ccalert[0].deadband_ab *= scale;
#endif
        ta.ccalert[1] = p_PTB->cycle_counter_b_alert;
        //automatic sync
        ta.ccalert[1].deadband_ab = ta.ccalert[0].deadband_ab;

        ErrorCode_t err = ccalert_Set(&ta);
        if(err != ERR_OK)
        {
            //As of now, only NVMEM write can fail
            fferr = E_FB_TEMP_ERROR;
        }
    }
    return fferr;
}


fferr_t ccalert_WriteCycleCounterAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write)
{
    //Take advantage of PTB data being already populated
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    if(p_write->rel_idx == REL_IDX_PTB_CYCLE_COUNTER_B_ALERT)
    {
        p_PTB->cycle_counter_a_alert.deadband_ab = p_PTB->cycle_counter_b_alert.deadband_ab;
    }
    else
    {
        p_PTB->cycle_counter_b_alert.deadband_ab = p_PTB->cycle_counter_a_alert.deadband_ab;
    }
    return alert_CommitCycleCounterAlert(p_block_instance);
}

// -------------- Travel Accumulation Alerts -----------------

/** \brief Rescale back to external representation
*/
void taalert_ReadTravelAccumAlert(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_READ_DATA* p_read)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    u8_least index;
    _TRAVEL_ALERT *p;
    if(p_read->rel_idx == REL_IDX_PTB_TRAVEL_ACCUMULATION_A_ALERT)
    {
        index = 0U;
        p = &p_PTB->travel_accumulation_a_alert;
    }
    else
    {
        index = 1U;
        p = &p_PTB->travel_accumulation_b_alert;
    }

#if TBALERTSTRENDS_SELECTION_TRAVEL_ACCUM == (TBALERTSTRENDS_OPTIONS_TRAVEL_ACCUM_OPTION_SCALED)
    float32 scale = Travel_ScaleToExternal(p_PTB);
    _TRAVEL_ALERT ta = TravelAlert.travel_alert[index];
    ta.deadband_ab *= scale;
    float32 f = ta.int_alert_point * scale +0.5F; //include rounding
    ta.int_alert_point = (u32)f;
    *p = ta;
#else
    *p = TravelAlert.travel_alert[index];
#endif
}


static float32 travel_FindRequestedDeadband(const T_FBIF_WRITE_DATA* p_write)
{
    float32 deadband = 0.0f;
    switch (p_write->subindex)
    {
        case PTB_SUBX_TRAVEL_ALERT___deadband_ab:
        {
            deadband = *((float32*)(void*)p_write->source);
            break;
        }
        case 0:
        {
            _TRAVEL_ALERT* pAlert = (void*)p_write->source;
            deadband = pAlert->deadband_ab;
            break;
        }
        default:
        {
            break;
        }
    }
    return deadband;
}


fferr_t travel_TestTravelAccumulationAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write)
{
    fferr_t fferr = E_OK;

    UNUSED_OK(p_block_instance);

    if((PTB_SUBX_TRAVEL_ALERT___deadband_ab == p_write->subindex) || (0 == p_write->subindex))
    {
        float32 deadband = travel_FindRequestedDeadband(p_write);

        if(deadband > TRAVEL_ALERT_deadband_ab_MAX_VALUE || deadband < TRAVEL_ALERT_deadband_ab_MIN_VALUE)
        {
            fferr = E_FB_PARA_CHECK;
        }
    }
    return fferr;
}

fferr_t travel_CommitTravelAccumulationAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    //We are setting out to write data to NVMEM; increment ST_REV first
    fferr_t fferr = fbs_incr_st_rev(p_block_instance, REL_IDX_PTB_ST_REV); //does it matter which?

    if(fferr == E_OK)
    {
        float32 unscale =
#if TBALERTSTRENDS_SELECTION_CYCLE_COUNT == (TBALERTSTRENDS_OPTIONS_CYCLE_COUNT_OPTION_SCALED)
            Travel_ScaleToInternal(p_PTB)
#else
            1.0F
#endif
                ;
        //Sparate calc for MISRA
        float32 acc_a = p_PTB->travel_accumulation_a_alert.travel_accumulation * unscale;
        float32 acc_b = p_PTB->travel_accumulation_b_alert.travel_accumulation * unscale;
        float32 pt_a = p_PTB->travel_accumulation_a_alert.int_alert_point * unscale;
        float32 pt_b = p_PTB->travel_accumulation_b_alert.int_alert_point * unscale;
        const TravelAlert_t ta =
        {
            .travel_alert =
            {
                [0] =
                {
                    .travel_accumulation = (u32)acc_a,
                    .int_alert_point = (u32)pt_a,
                    .deadband_ab = p_PTB->travel_accumulation_a_alert.deadband_ab * unscale,
                    .enable = p_PTB->travel_accumulation_a_alert.enable,
                },
                [1] =
                {
                    .travel_accumulation = (u32)acc_b,
                    .int_alert_point = (u32)pt_b,
                    .deadband_ab = p_PTB->travel_accumulation_a_alert.deadband_ab * unscale, //Yes, still _a_
                    .enable = p_PTB->travel_accumulation_b_alert.enable,
                },
            },
            .CheckWord = 0, //don't care
        };

        ErrorCode_t err = travel_Set(&ta);
        if(err != ERR_OK)
        {
            //As of now, only NVMEM write can fail
            fferr = E_FB_TEMP_ERROR;
        }
    }
    return fferr;
}

fferr_t travel_WriteTravelAccumulationAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    //Take advantage of PTB data being already populated
    if(p_write->rel_idx == REL_IDX_PTB_TRAVEL_ACCUMULATION_B_ALERT)
    {
        p_PTB->travel_accumulation_a_alert.deadband_ab = p_PTB->travel_accumulation_b_alert.deadband_ab;
    }
    else
    {
        p_PTB->travel_accumulation_b_alert.deadband_ab = p_PTB->travel_accumulation_a_alert.deadband_ab;
    }

    return travel_CommitTravelAccumulationAlert(p_block_instance);
}

/* This line marks the end of the source */

