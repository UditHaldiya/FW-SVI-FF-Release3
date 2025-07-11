/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_pstsched.c
    \brief The hart 5 commands used by pst scheduler

    CPU: Any

    OWNER: LS

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "errcodes.h"
#include "hartfunc.h"
//#include "nvram.h"
//#include "logfile.h"
//#include "logfileids.h"

#include "bufutils.h"
#include "fpconvert.h"

#include "hartdef5.h"
#include "pstshell.h"
#include "commontime.h"

//Assert enum values
CONST_ASSERT((s32)DhogCommDisable == (s32)HCT_Disabled);
CONST_ASSERT((s32)DhogCommEnable == (s32)HCT_Enabled);
CONST_ASSERT((s32)DhogPvDisable == (s32)HCTAI_Disabled);
CONST_ASSERT((s32)DhogPvEnableBelow == (s32)HCTAI_EnabledBelow);
CONST_ASSERT((s32)DhogPvEnableAbove == (s32)HCTAI_EnabledAbove);
CONST_ASSERT((s32)DhogDiDisable == (s32)HCTDI_Disabled);
CONST_ASSERT((s32)DhogDiEnableClosed == (s32)HCTDI_EnabledClosed);
CONST_ASSERT((s32)DhogDiEnableOpen == (s32)HCTDI_EnabledOpen);


static void populate_time_until( HPSTTimeUntil_t *d)
{
    s32 TimeToNext = pst_GetNextPSTTime(); //minutes; guarantted non-negative and no greater than 365 days
    s32 Days = TimeToNext / (MINUTES_PER_HOUR * HOURS_PER_DAY); //so the result fits in uint16_t range
    util_PutU16(d->PSTDaysUntilNext[0], (u16)Days); //and so cast is valid
    s32 Minutes = (TimeToNext - (Days * (MINUTES_PER_HOUR * HOURS_PER_DAY))); //remainder is minutes withn a day and fits in uint16_t range
    util_PutU16(d->PSTMinutesUntilNext[0],(u16) Minutes); //so cast is valid
}
/**
\brief sets base time on which pst schedules are made and reads time to next pst

The time sent in this command is the days and minutes since the start
of a plant scheduling cycle and returns the days and minutes until
the next pst
*/
s8_least hartcmd_WritePartialStrokeTestSchedule(const u8 *src, u8 *dst)
{
    const Req_WritePartialStrokeTestSchedule_t *s1 = (const void *)src;
    const HPSTTimeUntil_t *s = (const void *)s1->HPSTTimeUntil[0];
    Rsp_WritePartialStrokeTestSchedule_t *d1 = (void *)dst;
    HPSTTimeUntil_t *d = (void *)d1->HPSTTimeUntil[0];

    //get the data from the request
    u16 Days = util_GetU16(s->PSTDaysUntilNext[0]);
    u16 Minutes = util_GetU16(s->PSTMinutesUntilNext[0]);

    ErrorCode_t err = pst_SetBaseTime(Days, Minutes);

    populate_time_until(d); //OK to call even if error occurred

    return err2hart(err);
}

s8_least hartcmd_ReadPartialStrokeTestSchedule(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadPartialStrokeTestSchedule_t *d1 = (void *)dst;
    HPSTTimeUntil_t *d = (void *)d1->HPSTTimeUntil[0];

    populate_time_until(d); //OK to call even if error occurred

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_ReadPartialStrokeTestStartConfig(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadPartialStrokeTestStartConfig_t *d = (void *)dst;
    const PSTrigger_t *pstrig = pst_GetTriggerInfo(NULL);
    util_PutU8(d->PSTTriggerByUI[0], (u8)pstrig->PstUiTrigger);
    util_PutU8(d->DataCollectionTriggerByHART[0], (u8)pstrig->PstCommTrigger);
    util_PutU8(d->DataCollectionTriggerByDISwitch[0], (u8)pstrig->PstDiTrigger);
    util_PutU8(d->DataCollectionTriggerByAIInput[0], (u8)pstrig->PstPvTrigger);
    (void)fpconvert_IntToFloatBuffer(pstrig->pvthreshold, UNITSID_SIGNAL_ENTRY, d->DataCollectionTriggerAIInputThreshold[0]);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_WritePartialStrokeTestStartConfig(const u8 *src, u8 *dst)
{
    const Req_WritePartialStrokeTestStartConfig_t *s = (const void *)src;

    PSTrigger_t tr;
    (void)pst_GetTriggerInfo(&tr);
    tr.PstUiTrigger = util_GetU8(s->PSTTriggerByUI[0]);
    tr.PstCommTrigger = (DhogCommTrigger_t)util_GetU8(s->DataCollectionTriggerByHART[0]);
    tr.PstDiTrigger = (DhogDiTrigger_t)util_GetU8(s->DataCollectionTriggerByDISwitch[0]);
    tr.PstPvTrigger = (DhogPvTrigger_t)util_GetU8(s->DataCollectionTriggerByAIInput[0]);
    tr.pvthreshold = fpconvert_FloatBufferToInt16Clamped(s->DataCollectionTriggerAIInputThreshold[0], UNITSID_SIGNAL_ENTRY, pvthreshold_range);

    ErrorCode_t err = pst_SetTriggerInfo(&tr);

    s8_least ret;
    if(err == ERR_OK)
    {
        Rsp_WritePartialStrokeTestStartConfig_t *d = (void *)dst;
        UNUSED_OK(d); //rely on read function
        //lint -esym(768, Rsp_WritePartialStrokeTestStartConfig_t::*)
        ret = hartcmd_ReadPartialStrokeTestStartConfig(src, dst);
    }
    else
    {
        ret = err2hart(err);
    }
    return ret;
}
/* This line marks the end of the source */
