/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_fstate.c
    \brief Implementation of failed state

    CPU: Any

    OWNER: AK
*/


//Softing headers first
#include <softing_base.h>
#include <ptb.h>
#include <dofb.h>
#include <aofb.h>

#define MODULE_ID (MOD_APPL_TRN | COMP_PAPP)

#include <fbif_cfg.h>
#include <appl_int.h>
#include "mn_fstate.h"
#include "time_defs.h"
#include "mnassert.h"
#include "ptbcustomsubx.h"

#include "control.h"

//----------------------------------------------------------------
// XD_FSTATE has UNNAMED components
//
// component_0 - Configuration
// component_1 - Option
// component_2 - Value
// component_3 - Time
//----------------------------------------------------------------

// Mask to separate the status
#define SQ_MASK         (SQ_BAD | SQ_UNCERTAIN | SQ_GOOD_NC | SQ_GOOD_CAS | SQ_GOOD)
#define SUBSTATUS_MASK  (0x0fu * 0x4u)

// Time SHALL BE IN THE 1s to 100000s range
#define FSTAT_TIME_MIN                  (1.0f)
#define FSTAT_TIME_MAX                  (100000.0f)

// SP SHALL BE IN THE -50.0 to not 160.0 but ~199.9 range
#define FSTAT_VALUE_MIN                  ((float32)MIN_EFFECTIVE_SETPOINT_FP) // was (-50.0f)
#define FSTAT_VALUE_MAX                  ((float32)MAX_EFFECTIVE_SETPOINT_FP) //was incorrect (160.0f)

#define FSTATE_VALUE_INDEX 0
#define FSTATE_TIME_INDEX  1
//----------------------------------------------------------------
// Local variables

typedef struct FState_LocalData_t
{
    bool_t ForceActive[2]; //!< externally requested FS for each possible source (DO FB 1, 2)
    bool_t ForceActiveUsr;
    bool_t      Active;         // Flag -- FState is ACTIVE and we are driving the SP from here
    bool_t      LastSP_Set;
    float32     LastSP;
    u64         SP_TimeStamp;
    u16 CheckWord;
} FState_LocalData_t;

static FState_LocalData_t FStateData =
{
    .ForceActive = {false, false},
    .ForceActiveUsr = false,
    .Active           = false,
    .LastSP           = 0.0f,
    .SP_TimeStamp     = 0ULL,
    .LastSP_Set       = false,
    .CheckWord = CRC_SEED,
};

typedef struct FState_Ranges_t
{
    float32     LoLimit;
    float32     HiLimit;
} FState_Ranges_t;

static const FState_Ranges_t FState_Ranges[] =
{
    [FSTATE_VALUE_INDEX] = {FSTAT_VALUE_MIN, FSTAT_VALUE_MAX},
    [FSTATE_TIME_INDEX]  = {FSTAT_TIME_MIN,  FSTAT_TIME_MAX},
};
//----------------------------------------------------------------
// Forward declarations

static u8       ff_fstate_FB_SpSrc(const T_FBIF_BLOCK_INSTANCE *p_block_instance);
static void     ff_fstate_CopyCfg(const T_FBIF_BLOCK_INSTANCE *p_block_instance);

//Read/write accessors
fferr_t fstate_WriteStatus(T_FBIF_BLOCK_INSTANCE *p_block_instance, const T_FBIF_WRITE_DATA *p_write)
{
    UNUSED_OK(p_block_instance);
    fferr_t fferr;
    CONST_ASSERT(PTB_SUBX_TB_FSTATE_STATUS___DO_usr_req == 1); //Alignment issues!
    switch(p_write->subindex)
    {
        case 0: //everything)
        case PTB_SUBX_TB_FSTATE_STATUS___DO_usr_req:
        {
            bool_t req = *p_write->source != 0;
            fstate_ForceFstate(0xffU, req);
            fferr = E_OK;
            break;
        }
        default:
            fferr = E_FB_DATA_NO_WRITE;
            break;
    }
    return fferr;
}

fferr_t fstate_ReadStatus(T_FBIF_BLOCK_INSTANCE *p_block_instance, T_FBIF_READ_DATA *p_read)
{
    UNUSED_OK(p_read);
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    osif_disable_all_tasks();
    if(FStateData.ForceActiveUsr || FStateData.ForceActive[0] || FStateData.ForceActive[1])
    {
        p_PTB->tb_fstate_status.DO_usr_req = STATE_TRUE;
    }
    else
    {
        p_PTB->tb_fstate_status.DO_usr_req = STATE_FALSE;
    }
    p_PTB->tb_fstate_status.final_value_req = bool2int(FStateData.Active);
    if(FStateData.Active)
    {
        p_PTB->tb_fstate_status.time_to_fstate = 0.0F;
    }
    else
    {
        u64 TimeDiff    = osif_get_long_ms_since(FStateData.SP_TimeStamp);
        u64 TimePassed  = MS_TO_SEC(TimeDiff);
        u64 TempTime    = (u64)p_PTB->xd_fstate.component_3;
        TimeDiff = TempTime - TimePassed;
        p_PTB->tb_fstate_status.time_to_fstate = (float32)TimeDiff;
    }
    osif_enable_all_tasks();
    return E_OK;
} //lint !e818 common prototype

/** \brief A helper for DO FB
\param fbid - block id requesting failed state, or 0xffU for user
\param req - true iff failed state requested
*/
void fstate_ForceFstate(u8 fbid, bool_t req)
{
    u8_least index;
    if(fbid == ID_DOFB_1)
    {
        index = 0;
    }
    else if(fbid == ID_DOFB_2)
    {
        index = 1;
    }
    else
    {
        index = 2;
    }
    if(index < NELEM(FStateData.ForceActive))
    {
        MN_ENTER_CRITICAL();
            storeMemberBool(&FStateData, ForceActive[index], req);
        MN_EXIT_CRITICAL();
    }
    else
    {
        //User request: if true, set user, but if false, clear all
        if(req)
        {
            MN_ENTER_CRITICAL();
                storeMemberBool(&FStateData, ForceActiveUsr, true);
            MN_EXIT_CRITICAL();
        }
        else
        {
            MN_ENTER_CRITICAL();
                storeMemberBool(&FStateData, ForceActive[0], false);
                storeMemberBool(&FStateData, ForceActive[1], false);
                storeMemberBool(&FStateData, ForceActiveUsr, false);
            MN_EXIT_CRITICAL();
        }
    }
}

//---------------------- runtime part ----------------------------

// This function checks the Variable Status to see if the FSTATE should be invoked and activated.
// Returns:
//  FALSE - BAD status, condition for FState activation;
//  TRUE  - No, GOOD status, no reasons to activate FState
static bool_t   ff_fstate_StatusOK(u8 VStatus)
{
    bool_t  result = true;
    u8      VQuality;
    u8      VSubstatus;

    VQuality    = VStatus & SQ_MASK;            // Extract the Quality
    VSubstatus  = VStatus & SUBSTATUS_MASK;     // Extract Sub-status
    switch (VQuality)
    {
        case SQ_BAD :
        case SQ_UNCERTAIN : //APP looks for GOOD status only, so Uncertain must trigger failed state
            // Bad value status -- activate FSTATE!
            result = false;
            break;

        case SQ_GOOD_CAS :
            if (VSubstatus == SUB_IFS)
            {   // GOOD Cascaded status AND IFS! -- activate FSTATE!
                result = false;
            }
            break;

        default :
            // Nothing
            break;
    }

    return result;
}

// This function checks the TimeStamp if the FSTATE should be invoked and activated.
// Returns: TRUE - ACtivate the FSTATE, FALSE - No, no reasons to
static bool_t   ff_fstate_CheckTimeToActivate(const T_FBIF_BLOCK_INSTANCE *p_block_instance)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    bool_t  retval;

    // Check if the Time since last update has expired
    u64     TimeDiff;
    u64     TimePassed;
    u64     TempTime;

    TimeDiff    = osif_get_long_ms_since(FStateData.SP_TimeStamp);
    TimePassed  = MS_TO_SEC(TimeDiff);
    TempTime    = (u64)p_PTB->xd_fstate.component_3;

    retval = (TimePassed > TempTime);

    return retval;
}

// In this function we get the Final Value ***, both Value and status, and Channel
void ff_fstate_Execute_fromFB(const T_FBIF_BLOCK_INSTANCE *p_block_instance, u16 Channel)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    bool_t      UpdateTimeStamp;

    // Need to update the Time stamp, but!
    // -- If in Manual mode -- update unconditionally.
    // -- If the status is BAD - do not update.
    //
    // Later, the status of the time stamp will be checked and
    // the proper FState will be activated.

    if ((p_PTB->mode_blk.target & MODE_MAN) != 0u)
    {   // In MANUAL mode!
        UpdateTimeStamp = true;
    }
    else if ((p_PTB->mode_blk.target & MODE_OS) != 0)
    {   // OOS mode
        UpdateTimeStamp = true;
    }
    else
    {   // Auto mode
        UpdateTimeStamp = false;
        switch (Channel)
        {
            case CH_AO_POSITION :                      // AO block
                if(p_PTB->setpoint_source == SP_SELECT_AOFB)
                {
                    UpdateTimeStamp = ff_fstate_StatusOK(p_PTB->final_value.status);
                }
                break;

            case CH_DO_POSITION_OPEN_CLOSE :           // DO block BoolSP
                // Get the SP Time Stamp -- to be used later
                if(p_PTB->setpoint_source == SP_SELECT_DOBOOL)
                {
                    UpdateTimeStamp = ff_fstate_StatusOK(p_PTB->final_value_d.status);
                }
                break;

            case CH_DO_POSITION_DISCRETE_POSITION :    // DO block IntSP
                if(p_PTB->setpoint_source == SP_SELECT_DOINT)
                {
                    UpdateTimeStamp = ff_fstate_StatusOK(p_PTB->final_value_dint.status);
                }
                break;

            default :
                break;
        }
    }


    // Here we have a local flag that indicates that we should or should not update the TimeStamp
    if (UpdateTimeStamp)
    {
        u64 stamp = osif_get_long_time_in_ms();
        MN_ENTER_CRITICAL();
            storeMemberInt(&FStateData, SP_TimeStamp, stamp);
        MN_EXIT_CRITICAL();
    }

}


#define STARTUP_WRONG_SP_COUNT 25000 //same as APP wait time

static bool_t sp_may_not_be_ready = true; //! Kludge for Softing bug

static bool_t fstate_TooEarlyToFailSetpoint(void)
{
    if(sp_may_not_be_ready) //short-circuit for efficiency (?)
    {
        if(OS_GetTime32() > STARTUP_WRONG_SP_COUNT)
        {
            sp_may_not_be_ready = false;
        }
    }
    return sp_may_not_be_ready;
}

// In this function we get the Final Value ***, both Value and status, and Channel
void ff_fstate_Background(const T_FBIF_BLOCK_INSTANCE *p_block_instance)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    MN_ENTER_CRITICAL();

        bool_t reset_fstate = ((p_PTB->mode_blk.target & (MODE_OS|MODE_MAN)) != 0u);// In MANUAL or OOS mode!
        if(!reset_fstate)
        {
            reset_fstate = fstate_TooEarlyToFailSetpoint();
        }

        if(reset_fstate)
        {
            u64 stamp = osif_get_long_time_in_ms();
            storeMemberBool(&FStateData, Active, false);
            storeMemberInt(&FStateData, SP_TimeStamp, stamp);
        }
        else
        {
            bool_t fsactive = ff_fstate_CheckTimeToActivate(p_block_instance);
            storeMemberBool(&FStateData, Active, fsactive);
        }
    MN_EXIT_CRITICAL();
}

static void fstate_StoreSp(float32 sp)
{
    MN_ENTER_CRITICAL();
        ieee754_t spbits = float2ieee(sp);
        storeMemberInt(&FStateData, LastSP, spbits);
        // Make a note, that the Last SP has some real life value
        storeMemberBool(&FStateData, LastSP_Set, true);
    MN_EXIT_CRITICAL();
}

// This function stores the SP from the PTB
void ff_fstate_StoreLastSP(const FLOAT_S *sp)
{
    if((sp->status & SQ_GOOD) != 0)
    {
        MN_ENTER_CRITICAL();

            if (!FStateData.Active)
            {   // We store the SP only if the FSTATE is not active
                // Otherswise we are USING the stored SP
                fstate_StoreSp(sp->value);
            }

        MN_EXIT_CRITICAL();
    }
}

//---------------------- runtime part ----------------------------
/** \brief Once the FSTATE is ACTIVE, populate the desired setpoint
\param p_PTB - TB block
\param dst - destination buffer
\return true iff FSTATE_Active (and dst populated)
*/
bool_t ff_fstate_ForceFstate_SP(const T_FBIF_PTB *p_PTB, FLOAT_S *dst)
{
    float32     SPval;
    bool_t      FStateNow;
    u8_least    fstate_option;

    Struct_Test(FState_LocalData_t, &FStateData);
    MN_ENTER_CRITICAL(); //not SOfting osif_... because may be nested

        FStateNow     = FStateData.Active || FStateData.ForceActiveUsr;
        for(u8_least i=0; i<NELEM(FStateData.ForceActive); i++)
        {
            FStateNow = FStateNow || FStateData.ForceActive[i];
        }
        fstate_option = p_PTB->xd_fstate.component_1;

        if (FStateNow)
        {
            switch (fstate_option)               // Option
            {
                case FSTATE_ACTION_FAIL_CLOSED :
                    SPval = FSTAT_VALUE_MIN;
                    break;

                case FSTATE_ACTION_FAIL_OPEN :
                    SPval = FSTAT_VALUE_MAX;
                    break;

                case FSTATE_ACTION_FSTATE_VALUE :
                    SPval = p_PTB->xd_fstate.component_2;                               // Value
                    break;

                case FSTATE_ACTION_HOLD_LAST_VALUE :
                default :
                    if (!FStateData.LastSP_Set)
                    {
                        // If Last SP has not been set YET
                        // Set it to the current POSITION!
                        fstate_StoreSp(p_PTB->actual_position.value);
                    }

                    SPval = FStateData.LastSP;                              // Start from the LAST SP
                    break;
            }

            // Now force the SP to the calculated value
            dst->status = SQ_GOOD;
            dst->value  = SPval;
        }

    MN_EXIT_CRITICAL();

    return FStateNow;
}

#if defined(_lint) || !defined(__IAR_SYSTEMS_ICC__)
#define MN_CONSTRANGE(a, b) /* nothing */
#else
#define MN_CONSTRANGE(a, b) __constrange((a), (b))
#endif

#define NELEM_FState_Ranges NELEM(FState_Ranges)
//lint -sem(ff_fstate_FStateRangeCheck, 1n<NELEM_FState_Ranges)

/** \brief Verify if a parameter of FState is in the valid range
\param index - index of the parameter
\param ToVerify - test input value
\return true - iff in range;
*/
static bool_t   ff_fstate_FStateRangeCheck(u8 MN_CONSTRANGE(0,NELEM(FState_Ranges)-1) index, float32 ToVerify)
{
    bool_t  result;

    if(index >= NELEM(FState_Ranges))
    {
        result = false;
    }
    else if ((ToVerify >= FState_Ranges[index].LoLimit) &&
         (ToVerify <= FState_Ranges[index].HiLimit))
    {   // In the range!
         result = true;
    }
    else
    {   // OUTSIDE of the Range
         result = false;
    }

    return result;
}

// Drop fraction, anybody knows the business needs?
/*
static float32  TruncateFloatValue(float32 TimeValue)
{
    s32     TempValue;

    TempValue = (s32)TimeValue;

    return  (float32)TempValue;
}*/

// Varify if the Time parameter of FState is in the valid range
// AND clamp it to the range ends.
// Returns the verified AND clamped time sub-parameter value
static float32  ff_fstate_CheckAndCorrect(u8 index, float32 ToVerify)
{
    float32 result;

    MN_ASSERT(index < NELEM(FState_Ranges));

    if (ToVerify < FState_Ranges[index].LoLimit)
    {   // BELOW the range
        result = FState_Ranges[index].LoLimit;
    }
    else if (ToVerify > FState_Ranges[index].HiLimit)
    {   // ABOVE the range!
        result = FState_Ranges[index].HiLimit;
    }
    else
    {   // Inside the range
        result = ToVerify;
    }

//    result = TruncateFloatValue(result);

    return result;
}

/* Write handler hook -- to verify */
fferr_t     ff_fstate_VerifyWriteConf(const T_FBIF_BLOCK_INSTANCE *p_block_instance, const T_FBIF_WRITE_DATA *p_write)
{
    fferr_t     fferr = E_OK;

    u8          *p_byte;
    float32     *p_fTime, *p_fVal;
    u8           BlockID;

    // Local structure
    _XD_FSTATE   xd_fstate;

    BlockID = ff_fstate_FB_SpSrc(p_block_instance);

    //Populate what we are not changing with the data from TB
    switch (p_write->subindex)
    {
        case 0 : // everything)
            // Note, parsing the WRITE buffer
            xd_fstate.component_0 = *(u8 *)(void *)(p_write->source +  MN_OFFSETOF(_XD_FSTATE, component_0));
            xd_fstate.component_1 = *(u8 *)(void *)(p_write->source +  MN_OFFSETOF(_XD_FSTATE, component_1));

            // Now extract two floats
            p_fVal  = (float32 *)(void *)(p_write->source + MN_OFFSETOF(_XD_FSTATE, component_2) - 2u);
            p_fTime = (float32 *)(void *)(p_write->source + MN_OFFSETOF(_XD_FSTATE, component_3) - 2u);

            if ((xd_fstate.component_0 != FSTATE_CONFIGURATION_LOCALCFG) &&
                (xd_fstate.component_0 != FSTATE_CONFIGURATION_COPYCFG))
            {
                fferr = E_FB_PARA_LIMIT;
            }
            else if (xd_fstate.component_0 == FSTATE_CONFIGURATION_COPYCFG)
            {   // Parameter is OK, can we accept it?
                if ((BlockID != ID_AOFB_1) &&
                    (BlockID != ID_DOFB_1) &&
                    (BlockID != ID_DOFB_2))
                {
                    fferr = E_FB_PARA_LIMIT;
                }
            }
            else if (!ff_fstate_FStateRangeCheck(FSTATE_TIME_INDEX, *p_fTime))
            {
                fferr = E_FB_PARA_LIMIT;
            }
            else if (!ff_fstate_FStateRangeCheck(FSTATE_VALUE_INDEX, *p_fVal))
            {
                fferr = E_FB_PARA_LIMIT;
            }
            else if (xd_fstate.component_1 >= FSTATE_ACTION_RESERVED_1)
            {
                fferr = E_FB_PARA_LIMIT;
            }
            else
            {
                // Nothing
            }

 /*           if (fferr == E_OK)
            {   // Truncate the time, Value
                *p_fTime = TruncateFloatValue(*p_fTime);
                *p_fVal  = TruncateFloatValue(*p_fVal);
            }
*/
            break;

        case 1 : // Configuration
            p_byte = (u8 *)(void *)p_write->source;
            if (*p_byte == FSTATE_CONFIGURATION_LOCALCFG)
            {
                // Parameter value is OK, contimue
            }
            else if (*p_byte == FSTATE_CONFIGURATION_COPYCFG)
            {   // Parameter is OK, can we accept it?
                if ((BlockID != ID_AOFB_1) &&
                    (BlockID != ID_DOFB_1) &&
                    (BlockID != ID_DOFB_2))
                {
                    fferr = E_FB_PARA_LIMIT;
                }
            }
            else
            {   // Parameter range is NOT OK
                fferr = E_FB_PARA_LIMIT;
            }
            break;

        case 2 : // Option
            p_byte = (u8 *)(void *)p_write->source;
            if (*p_byte >= FSTATE_ACTION_RESERVED_1)
            {
                fferr = E_FB_PARA_LIMIT;
            }
            break;

        case 3 : // Val
            p_fVal   = (float32 *)(void *)p_write->source;
            if (!ff_fstate_FStateRangeCheck(FSTATE_VALUE_INDEX, *p_fVal))
            {
                fferr = E_FB_PARA_LIMIT;
            }
/*
            if (fferr == E_OK)
            {
                *p_fVal = TruncateFloatValue(*p_fVal);
            }
*/
            break;

        case 4 : // Time
            p_fTime   = (float32 *)(void *)p_write->source;
            if (!ff_fstate_FStateRangeCheck(FSTATE_TIME_INDEX, *p_fTime))
            {
                fferr = E_FB_PARA_LIMIT;
            }
/*
            if (fferr == E_OK)
            {
                *p_fTime = TruncateFloatValue(*p_fTime);
            }
*/
            break;

        default:
            fferr = E_FB_PARA_CHECK;
            break;
    }

    return fferr;
}

fferr_t     ff_fstate_PostProcessWriteConf(const T_FBIF_BLOCK_INSTANCE *p_block_instance, const T_FBIF_WRITE_DATA *p_write)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    UNUSED_OK(p_write);

    if (p_PTB->xd_fstate.component_0 == FSTATE_CONFIGURATION_COPYCFG)
    {
        ff_fstate_CopyCfg(p_block_instance);
    }

    return E_OK;
}

// --------------------------------------------------------------------------------
// This function returns the ID of the FB which is a driving force for the SP.

static u8  ff_fstate_FB_SpSrc(const T_FBIF_BLOCK_INSTANCE *p_block_instance)
{
    u8  retval = ID_RESB_1;

    const T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    const T_FBIF_BLOCK_INSTANCE *p_DOFB_instance;
    const T_FBIF_DOFB *p_DOFB;

    // Check the SP source
    switch (p_PTB->setpoint_source)
    {
        case SP_SELECT_AOFB :
            // TB is connected to the AO
            retval = ID_AOFB_1;
            break;

        case SP_SELECT_DOINT :
            // TB is connected to one of the DOs
            retval = ID_DOFB_1;
            p_DOFB_instance = fbs_get_block_inst(retval);
            p_DOFB = p_DOFB_instance->p_block_desc->p_block;
            if (p_DOFB->channel != CH_DO_POSITION_OPEN_CLOSE)
            {
                // Match, do nothing
            }
            else
            {
                retval = ID_DOFB_2;
                p_DOFB_instance = fbs_get_block_inst(retval);
                p_DOFB = p_DOFB_instance->p_block_desc->p_block;
                if (p_DOFB->channel != CH_DO_POSITION_OPEN_CLOSE)
                {
                    // Match, do nothing
                }
                else
                {
                    retval = ID_RESB_1;
                }
            }
            break;

        case SP_SELECT_DOBOOL :
            // TB is connected to one of the DOs
            retval = ID_DOFB_1;
            p_DOFB_instance = fbs_get_block_inst(retval);
            p_DOFB = p_DOFB_instance->p_block_desc->p_block;
            if (p_DOFB->channel == CH_DO_POSITION_OPEN_CLOSE)
            {
                // Match, do nothing
            }
            else
            {
                retval = ID_DOFB_2;
                p_DOFB_instance = fbs_get_block_inst(retval);
                p_DOFB = p_DOFB_instance->p_block_desc->p_block;
                if (p_DOFB->channel == CH_DO_POSITION_OPEN_CLOSE)
                {
                    // Match, do nothing
                }
                else
                {
                    retval = ID_RESB_1;
                }
            }
            break;

        default :           // Error
            break;
    }

    return retval;
}

static void    ff_fstate_CopyCfg(const T_FBIF_BLOCK_INSTANCE *p_block_instance)
{
    // Based on the configuration copy the cfg for the Fstate
    const T_FBIF_BLOCK_INSTANCE *p_FB_instance;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    u8  BlockID;

    switch (p_PTB->xd_fstate.component_0)
    {
        case FSTATE_CONFIGURATION_COPYCFG :
            BlockID = ff_fstate_FB_SpSrc(p_block_instance);
            switch (BlockID)
            {
                case ID_DOFB_1 :
                case ID_DOFB_2 :
                    {   // Legit FB
                        const T_FBIF_DOFB *p_DOFB;

                        p_FB_instance = fbs_get_block_inst(BlockID);
                        p_DOFB = p_FB_instance->p_block_desc->p_block;
                        p_PTB->xd_fstate.component_2  = ff_fstate_CheckAndCorrect(FSTATE_VALUE_INDEX, (float32)p_DOFB->fstate_val_d);
                        p_PTB->xd_fstate.component_3  = ff_fstate_CheckAndCorrect(FSTATE_TIME_INDEX, p_DOFB->fstate_time);
                        p_PTB->xd_fstate.component_0  = FSTATE_CONFIGURATION_LOCALCFG;
                    }
                    break;

                case ID_AOFB_1 :
                    {   // Legit FB
                        const T_FBIF_AOFB *p_AOFB;

                        p_FB_instance = fbs_get_block_inst(BlockID);
                        p_AOFB = p_FB_instance->p_block_desc->p_block;
                        p_PTB->xd_fstate.component_2  = ff_fstate_CheckAndCorrect(FSTATE_VALUE_INDEX,p_AOFB->fstate_val);
                        p_PTB->xd_fstate.component_3  = ff_fstate_CheckAndCorrect(FSTATE_TIME_INDEX, p_AOFB->fstate_time);
                        p_PTB->xd_fstate.component_0  = FSTATE_CONFIGURATION_LOCALCFG;
                    }
                    break;

                default :
                    break;
            }
            break;

        case FSTATE_CONFIGURATION_LOCALCFG :
            // Use local config
            break;


        default :
            // Do nothing
            break;
    }
}

/* This line marks the end of the source */
