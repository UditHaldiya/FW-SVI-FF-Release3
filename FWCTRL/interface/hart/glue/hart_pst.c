/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_pst.c
    \brief The hart 5 commands used by pst

    CPU: Any

    OWNER: LS

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "errcodes.h"
#include "hartfunc.h"
#include "hartdef5.h"
#include "bufutils.h"
#include "pst.h"
#include "pstshell.h"
#include "faultpublic.h"

#include "fpconvert.h"

s8_least hartcmd_RunPartialStrokeTest(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    s8_least ret;
    //devmode_t mode = mode_GetEffectiveMode(mode_GetMode());
    if(pst_GetTriggerInfo(NULL)->PstCommTrigger == DhogCommDisable)
    {
        ret = HART_DIAG_NOT_ALLOWED;
    }
    else if( error_IsAnyFaultWithAttributes(INHIBITING_FAULTS))
    {
        ret = HART_WRONG_MODE;
    }
    else
    {
        ErrorCode_t err = process_SetProcessCommand(PROC_DIAG_PARTIAL_STROKE_TEST);
        ret = err2hart(err);
    }
    return ret;
}

static s8_least populate_pst_configuration(HPSTConfiguration_t *d)
{
    //convert the data to user format and store in the output buffer
    const PSTConf_t *pPSTConf = diag_GetPstData(NULL);

    (void)fpconvert_IntToFloatBuffer(pPSTConf->sp_threshold, UNITSID_POSITION_ENTRY, d->PSTsetpointChangeThreshold[0]);
    (void)fpconvert_IntToFloatBuffer(pPSTConf->travel, UNITSID_POSITION_ENTRY, d->PSTtravel[0]);
    util_PutU32(d->PSTMaxTime[0], pPSTConf->maxtime);
    (void)fpconvert_IntToFloatBuffer(pPSTConf->ramp_speed, UNITSID_POSITION_ENTRY, d->PSTSetpointRate[0]);
    (void)fpconvert_IntToFloatBuffer(pPSTConf->PresAbortActuator, UNITSID_PRESSURE_ENTRY, d->PSTActuatorPressureThreshold[0]);
    (void)fpconvert_IntToFloatBuffer(pPSTConf->PresAbortPilot, UNITSID_PRESSURE_ENTRY, d->PSTPilotPressureThreshold[0]);
    util_PutU16(d->PSTLeadTime[0], pPSTConf->LeadTime);
    util_PutU16(d->PSTDwellTime[0], pPSTConf->DwellTime);
    util_PutU32(d->PSTStrokeTimeout[0], pPSTConf->StrokeTmout);

    util_PutU16(d->PSTdatamap[0], pPSTConf->datamap);
    util_PutU16(d->PSTSkipCount[0], pPSTConf->skip_count);
    util_PutU16(d->PSTFreezeOptions[0], pPSTConf->FreezeOptions);
    util_PutU8(d->PSTpattern[0], pPSTConf->pattern);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_WritePartialStrokeTestConfiguration(const u8 *src, u8 *dst)
{
    UNUSED_OK(dst);

    PSTConf_t PSTConf;

    (void)diag_GetPstData(&PSTConf);

    //get the data
    const Req_WritePartialStrokeTestConfiguration_t *s1 = (const void *)src;
    const HPSTConfiguration_t *s = (const void *)s1->HPSTConfiguration;

    PSTConf.sp_threshold = fpconvert_FloatBufferToInt16Clamped(s->PSTsetpointChangeThreshold[0], UNITSID_POSITION_ENTRY, pstSpThreshold_range);
    PSTConf.travel = fpconvert_FloatBufferToInt16Clamped(s->PSTtravel[0], UNITSID_POSITION_ENTRY, pstTravel_range);
    PSTConf.maxtime = util_GetU32(s->PSTMaxTime[0]);
    PSTConf.ramp_speed = fpconvert_FloatBufferToInt16Clamped(s->PSTSetpointRate[0], UNITSID_POSITION_ENTRY, pstRampSpeed_range);

    PSTConf.PresAbortActuator = fpconvert_FloatBufferToInt16Clamped(s->PSTActuatorPressureThreshold[0], UNITSID_PRESSURE_ENTRY, pstPresActuator_range);
    PSTConf.PresAbortPilot = fpconvert_FloatBufferToInt16Clamped(s->PSTPilotPressureThreshold[0], UNITSID_PRESSURE_ENTRY, pstPresPilot_range);

    PSTConf.LeadTime = util_GetU16(s->PSTLeadTime[0]);
    PSTConf.DwellTime = util_GetU16(s->PSTDwellTime[0]);
    PSTConf.StrokeTmout = util_GetU32(s->PSTStrokeTimeout[0]);

    PSTConf.datamap = util_GetU16(s->PSTdatamap[0]);
    PSTConf.skip_count = util_GetU16(s->PSTSkipCount[0]);

    PSTConf.FreezeOptions = util_GetU16(s->PSTFreezeOptions[0]);
    PSTConf.pattern = util_GetU8(s->PSTpattern[0]);

    //save the data
    ErrorCode_t err = diag_SetPstData(&PSTConf);
    s8_least ret;
    if(err == ERR_OK)
    {
        Rsp_WritePartialStrokeTestConfiguration_t *d1 = (void *)dst;
        HPSTConfiguration_t *d = (void *)d1->HPSTConfiguration;
        ret = populate_pst_configuration(d);
    }
    else
    {
        ret = err2hart(err);
    }
    return ret;
}

s8_least hartcmd_ReadPartialStrokeTestConfiguration(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);

    Rsp_ReadPartialStrokeTestConfiguration_t *d1 = (void *)dst;
    HPSTConfiguration_t *d = (void *)d1->HPSTConfiguration;
    return populate_pst_configuration(d);
}

/* This line marks the end of the source */
