/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_vdiag.c
    \brief HART glue layer for valve diagnostics

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "diagnostics.h"
#include "hartdef.h"
#include "hartfunc.h"
#include "hartpriv.h"
#include "bufutils.h"
#include "fpconvert.h"
#include "process.h"
#include "ctllimits.h"



s8_least hartcmd_StepTest(const u8 *src, u8 *dst)
{
    UNUSED_OK(dst);
    const Req_StepTest_t *s = (const void *)src;
    pos_t StartPosition = fpconvert_FloatBufferToInt16Clamped(s->StartPosition[0], UNITSID_POSITION, Position_FullRange);
    pos_t EndPosition = fpconvert_FloatBufferToInt16Clamped(s->EndPosition[0], UNITSID_POSITION, Position_FullRange);
    u16 SamplingTime = util_GetU16(s->SamplingTime[0]);

    ErrorCode_t err = diag_LaunchStepTest(StartPosition, EndPosition, SamplingTime);
    return err2hart(err);
    //return vdiag_common(s, PROC_STEP_TEST, DIAG_STEP);
}

s8_least hartcmd_RampTest(const u8 *src, u8 *dst)
{
    UNUSED_OK(dst);
    const Req_RampTest_t *s = (const void *)src;
    pos_t StartPosition = fpconvert_FloatBufferToInt16Clamped(s->StartPosition[0], UNITSID_POSITION, Position_FullRange);
    pos_t EndPosition = fpconvert_FloatBufferToInt16Clamped(s->EndPosition[0], UNITSID_POSITION, Position_FullRange);
    pos_t SetpointRampSpeed = fpconvert_FloatBufferToInt16Clamped(s->SetpointRampSpeed[0], UNITSID_POSITION, spratelim_range);
    u8 DiagDirection = *s->DiagDirection[0];

    ErrorCode_t err = diag_LaunchRampTest(StartPosition, EndPosition, SetpointRampSpeed, DiagDirection);
    return err2hart(err);
}




/* This line marks the end of the source */
