/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_profiler.c
    \brief HART glue layer for task/crisect profiling

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "oswrap.h"
#include "mn_instrum.h"
#include "hartfunc.h"
#include "hartdef.h"
#include "bufutils.h"
#include "selftest.h"

/**
\brief Read activation data
*/
s8_least hartcmd_ReadProfilingData(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadProfilingData_t *d = (void *)dst;

    u32 profile[(size_t)MAX_TASK_ID+1U];
    profile_ReadAndClear(profile);
    util_PutU32(d->Longestcontroltask[0], profile[TASKID_CONTROL]);
    util_PutU32(d->Longestcycletask[0], profile[TASKID_CYCLE]);
    util_PutU32(d->LongestHARTtask[0], profile[TASKID_HART]);
    util_PutU32(d->LongestISPtask[0], profile[TASKID_ISPCOMM]);
    util_PutU32(d->LongestIPCtask[0], profile[TASKID_IPCCOMM]);
    util_PutU32(d->Longestprocesssegment[0], profile[TASKID_PROCESS]);
    util_PutU32(d->LongestProxytask[0], profile[TASKID_PROXY]);

    MN_ENTER_CRITICAL();
        util_PutU32(d->Addressofcritsect[0], CritSectStat.addr);
        util_PutU32(d->Longestcritsect[0], (u32)CritSectStat.maxlen);
        CritSectStat.maxlen = 0U;
    MN_EXIT_CRITICAL();

    util_PutU8(d->FreeCPUtimeH[0], (u8)selftest_GetStat()->percentCpuFree);

    ProfilerConfiguration_t *d1 = (void *)d->ProfilerConfiguration[0];
    util_PutU8(d1->ProfilerTaskID[0], profiler_task_id);
    util_PutU32(d1->ProfilerExtratimeload[0], profiler_extra_task_load);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_WriteProfilerConfiguration(const u8 *src, u8 *dst)
{
    const Req_WriteProfilerConfiguration_t *s1 = (const void *)src;
    const ProfilerConfiguration_t *s = (const void *)s1->ProfilerConfiguration[0];
    MN_ENTER_CRITICAL();
        profiler_task_id = util_GetU8(s->ProfilerTaskID[0]);
        profiler_extra_task_load = util_GetU32(s->ProfilerExtratimeload[0]);
    MN_EXIT_CRITICAL();
    Rsp_WriteProfilerConfiguration_t *d = (void *)dst;
    UNUSED_OK(d->ProfilerConfiguration); //HART framework fills it out
    return HART_NO_COMMAND_SPECIFIC_ERRORS; //response is copied automatically
}

/* This line marks the end of the source */
