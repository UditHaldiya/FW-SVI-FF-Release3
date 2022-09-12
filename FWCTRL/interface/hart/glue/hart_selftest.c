/*
Copyright 2020 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_selftest.c
    \brief HART glue layer for selftest

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/

#include "mnwrap.h"
#include "hartfunc.h"
#include "hartdef.h"
#include "bufutils.h"
#include "selftest.h"

s8_least hartcmd_ReadSelftestStats(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadSelftestStats_t *d = (void *)dst;
    const stat_t Atomic_ *p = selftest_GetStat();

    util_PutU8(d->FreeCPUtime[0], (u8)p->percentCpuFree);
    util_PutU32(d->Shortestflashtest[0], p->flashRoundTripTime_min);
    util_PutU32(d->Longestflashtest[0], p->flashRoundTripTime_max);
    util_PutU32(d->ShortestNVMEMtest[0], p->nvmemRoundTripTime_min);
    util_PutU32(d->LongestNVMEMtest[0], p->nvmemRoundTripTime_max);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/* This line marks the end of the source */
