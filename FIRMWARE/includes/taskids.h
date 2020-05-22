/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file taskids.h
    \brief Common task ids

    CPU: Any

    OWNER: AK

    \ingroup OSWrap
*/

#ifndef TASKIDS_H_
#define TASKIDS_H_
typedef enum taskid_t
{
    TASKID_IDLE,
    TASKID_CONTROL,
    TASKID_CYCLE,
    TASKID_HART,
    TASKID_PROCESS,
    TASKID_IPCCOMM,
    TASKID_ISPCOMM,
    TASKID_PROXY
} taskid_t;
#define MAX_TASK_ID TASKID_PROXY

//------------------- watchdog part ----------------------------
//lint -emacro(641, WD_MONITOR_TASKS_ALWAYS, WD_MONITOR_TASKS_NEVER) undeserved - enum on RHS of shift
#define WD_MONITOR_TASKS_ALWAYS ((1U << TASKID_CONTROL) | (1U << TASKID_CYCLE) |  (1U << TASKID_PROCESS))
#define WD_MONITOR_TASKS_NEVER (0U)
//---------------------------------------------------------------


#endif //TASKIDS_H_
/* This line marks the end of the source */
