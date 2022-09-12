/*
Copyright 2021 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_tuneoptions.c
    \brief HART glue layer for autotune study

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "hartdef.h"
#include "bufutils.h"
#include "selftune.h"

/**
\brief Write tune options
*/
s8_least hartcmd_WriteTuneOptions(const u8 *src, u8 *dst)
{
    Rsp_WriteTuneOptions_t *d1 = (void *)dst;
    TuneOptionsStudy_t *d = (void *)d1->TuneOptionsStudy[0];
    UNUSED_OK(d);
    const Req_WriteTuneOptions_t *s1 = (const void *)src;
    const TuneOptionsStudy_t *s = (const void *)s1->TuneOptionsStudy[0];
    TuneData_t t;
    (void)tune_GetTuneData(&t);
    t.TuneOptions.toption = util_GetU32(s->TuneOptionsBitmap[0]);
    t.TuneOptions.low_overshoot_thresh = (s8)util_GetU8(s->LowOvershootThreshold[0]);
    t.TuneOptions.min_number_of_ramp_points = util_GetU8(s->MinNumberOfRampPoints[0]);
    t.TuneOptions.PAdjust_recalc_scale = (s8)util_GetU8(s->PAdjustRecalcScale[0]);
    t.TuneOptions.PAdjust_recalc_scale2 = (s8)util_GetU8(s->PAdjustRecalcScale2[0]);
    ErrorCode_t err = tune_SetTuneData(&t);
    return err2hart(err); //output buffer filled automatically but we don't care
}

/**
\brief Read tune options
*/
s8_least hartcmd_ReadTuneOptions(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadTuneOptions_t *s1 = (void *)dst;
    TuneOptionsStudy_t *s = (void *)s1->TuneOptionsStudy[0];
    TuneData_t t;
    (void)tune_GetTuneData(&t);
    util_PutU32(s->TuneOptionsBitmap[0], t.TuneOptions.toption);
    util_PutU8(s->LowOvershootThreshold[0], (u8)t.TuneOptions.low_overshoot_thresh);
    util_PutU8(s->MinNumberOfRampPoints[0], t.TuneOptions.min_number_of_ramp_points);
    util_PutU8(s->PAdjustRecalcScale[0], (u8)t.TuneOptions.PAdjust_recalc_scale);
    util_PutU8(s->PAdjustRecalcScale2[0], (u8)t.TuneOptions.PAdjust_recalc_scale2);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/* This line marks the end of the source */
