/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file oswrap.h
    \brief An RTOS-independent wrapper of common RTOS services

    CPU: Any

    OWNER: AK

    \ingroup OSWrap
*/
#ifndef OSWRAP_H_
#define OSWRAP_H_
#include <rtos.h>
#include "mnassert.h"
#include <taskids.h>
#include "mn_instrum.h"

#define OSWRAP_NO_ERR      0


//lint -sem(oswrap_IsContext, pure)
extern  bool_t oswrap_IsContext(taskid_t taskid);

#define oswrap_IsOSRunning() (OS_Running != 0)

//lint -sem(OSTaskIdleHook, thread_mono) designate it as a task
extern void        OSTaskIdleHook(void);

/** \brief A required and maybe project-dependent function that creates
all tasks in the required sequence and starts the RTOS
*/
extern void oswrap_OSStart(void);

extern void idle_EstimateTime(void);

//----------- MNCB tasks (may migrate to a separate header if diverge) ------------
// not in this project lint -sem(process_ProcessTask, thread_mono) designate it as a task
extern void process_ProcessTask(void *arg);
//-------------------------------------------------------------------

#endif // OSWRAP_H_

/* This line marks the end of the source */
