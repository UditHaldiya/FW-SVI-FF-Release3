/**
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file procspecific.c

    \brief Project-specific implementations for Process component

    OWNER: AK
    CPU: Any

    \ingroup Process
*/
#include "mnwrap.h"
#include "oswrap.h"
#include "watchdog.h"
#include "process.h"
#include "procspecific.h"
#include <keywords.h>
#include <base.h>
#include <osif.h>

void process_NotifyEnd(void)
{
    //Nothing yet
}

void process_NotifyEndUI(s8 uiplace, s16 procdetails)
{
    //Nothing yet
    UNUSED_OK(uiplace);
    UNUSED_OK(procdetails);
}

u8_least process_CheckSpecific(void)
{
    u8_least ret = 0U;
    return ret;
}

//lint -sem(process_embOSTask, thread_mono) designate it as a task
static void process_embOSTask(T_EVENT event)
{

    UNUSED_OK(event);

    wdog_WatchdogTrigger();

    process_ProcessTaskLoop();
}


void proc_Init(void)
{
    process_InitData();
    osif_create_task (TASKID_PROCESS, PROCESS_TASK_PRIO, process_embOSTask, 0);
}

/* This line marks the end of the source */
