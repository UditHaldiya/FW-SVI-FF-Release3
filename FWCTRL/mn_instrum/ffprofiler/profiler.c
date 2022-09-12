/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file profiler.c
    \brief MN code instrumentation. OS tasks profilng

    CPU: ARM Cortex M3

    OWNER: AK

    \ingroup OSWrap
*/
#include "mnwrap.h"
#include "oswrap.h"
#include "mn_instrum.h"
#include "mn_coinstrum.h"

typedef struct TaskProfile_t
{
    ccount_t start;
    ccount_t end;
    ccount_t max_duration;
} Atomic_ TaskProfile_t;

static TaskProfile_t TaskProfile[(u32)MAX_TASK_ID+1U];
static bool_t Atomic_ been_there[NELEM(TaskProfile)];

static bool_t Atomic_ need_init=true; //lint !e633 spurious warning because of Atomic_
void profile_TimeStamp(taskid_t taskid)
{
    if(need_init)
    {
        need_init = false;  //lint !e633 spurious warning because of Atomic_
        instrum_EnableCycleCount();
#ifndef NDEBUG
        //Before timer init, any capture of critical sections is useless
        CritSectStat.maxlen = 0;
#endif
    }
    TaskProfile[taskid].start = instrum_GetHighResolutionTimer();
#ifndef NDEBUG
    if((u8)taskid == profiler_task_id)
    {
        ccount_t diff;
        do
        {
            diff = (instrum_GetHighResolutionTimer() - TaskProfile[taskid].start);
        } while(diff < profiler_extra_task_load);
    }
#endif //NDEBUG
}


#ifndef NDEBUG
ccount_t profiler_extra_task_load = 0;
u8 profiler_task_id = 0;
#endif //NDEBUG

void profile_MeasureTime(taskid_t taskid)
{
    ccount_t stamp = instrum_GetHighResolutionTimer();
    if(been_there[taskid])
    {
        ccount_t dur = stamp - TaskProfile[taskid].start;
        //dur &= 0x00FFFFFFU;
        TaskProfile[taskid].end = stamp;
        if(TaskProfile[taskid].max_duration < dur)
        {
            TaskProfile[taskid].max_duration = dur;
        }
    }
    else
    {
        //Initialize
        TaskProfile[taskid].start = stamp;
        been_there[taskid] = true;  //lint !e633 spurious warning because of Atomic_
    }
}

void profile_ReadAndClear(u32 results[])
{
    CONST_ASSERT((u32)TASKID_IDLE==0U);
    MN_ENTER_CRITICAL();
        for(u8_least i=1; i<NELEM(TaskProfile); i++) //skipping idle task
        {
            results[i] = TaskProfile[i].max_duration;
            TaskProfile[i].max_duration = 0U;
        }
    MN_EXIT_CRITICAL();
}

/* This line marks the end of the source */
