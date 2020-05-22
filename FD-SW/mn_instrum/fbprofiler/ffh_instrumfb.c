/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_instrumfb.c
    \brief FB profiler instrumentation commands

    CPU: Any

    OWNER: AK
*/
#include "instrumfb.h"
#include <osif.h>
#include "hartfunc.h"
#include "hartcmd.h"
#include "bufutils.h"
#include "ffhartdef5.h"

//--------- subcommand 25 --------------------
s8_least hartcmd_ReadAndClearBlockProfiles(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadAndClearBlockProfiles_t *d = (void *)dst;
    size_t size = MIN(NELEM(mnbprof_times), NELEM(d->BlockExecTimes));
    osif_disable_all_tasks();
    for(size_t i=0; i<size; i++)
    {
        util_PutU16(d->BlockExecTimes[i], mnbprof_times[i]);
        mnbprof_times[i] = 0;
    }
    osif_enable_all_tasks();
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
/* This line marks the end of the source */
