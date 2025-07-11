/*
Copyright 2004-2006 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup OSWrap  Abstraction of uC/OS-II API
\brief Abstraction of uC/OS-II API on MNCB (ARM7)
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_OS_Port Module.doc"> Design document </a><br>
<a href="../../../Doc/TestDocs/utplan_oswrap.doc"> Unit Test Report </a><br>
\endhtmlonly
*/
/**
    \file oswrap.c
    \brief Wrapper - abstraction of uC/OS-II

    CPU: Any, for uC/OS-II 2.76 RTOS

    OWNER: Ernie Price

    \ingroup OSWrap
*/
#include "mnwrap.h"
#include "oswrap.h"
#include <ucos_ii.h>
#include "process.h"

// N. B. See comment at the beginnimng of oswrap.h.  oswrap.c should be
// the only file that includes both ucos_ii.h and oswrap.h

#include "mnassert.h"
#include "faultpublic.h"

CONST_ASSERT(OS_NO_ERR==OSWRAP_NO_ERR);       // this to keep these defines in sync.  First one in ucos_ii.h
CONST_ASSERT(OS_IDLE_PRIO==OS_IDLE_TASK_PRIO);       // this to keep these defines in sync.  First one in ucos_ii.h

//CONST_ASSERT(IDLE_TASK_PRIO == OS_LOWEST_PRIO);       // this to keep these defines in sync.  First one in ucos_ii.h
//CONST_ASSERT(OS_MAX_TASKS == (OS_LOWEST_PRIO - 1));

#if (OS_TASK_STAT_STK_CHK_EN > 0) && (OSPORT_EXPOSE_TCB)
#   error "Incompatible OS configuration options"
#endif

/** \ brief Check for semaphore already available - it should not be.
    If it is, there has been a scheduling delay or error.
    Wait for the requested semaphore - used by Control and Cycle tasks.

    \param[in] taskid - a predefined task id
*/
void mn_waitsem(taskid_t taskid)
{
    if((*oswrap_GetTaskSemaphorePtr(taskid))->OSEventCnt != 0)
    {
        error_SetFault(FAULT_RTOS_SCHEDULING);
    }
    mn_waitforsem(taskid);
}

/** \brief Test if the passed taskid matches the running task

    \param taskid - one of the pre-defined task ids
*/
bool_t oswrap_IsContext(taskid_t taskid)
{
    if(OSTCBCur == NULL)
    {
        return false;
    }
    return OSTCBCur->OSTCBStkBottom == taskdef[taskid].stk;
}

#ifndef NDEBUG
/** \brief DEBUG-only helper to give an idea of what task is running
\return A unique task stamp (implementation: a pointer to the bottom of its stack)
*/
TaskStamp_t oswrap_GetTaskStamp(void)
{
    MN_DBG_ASSERT(OSTCBCur!=NULL); //may not use before RTOS started
    return OSTCBCur->OSTCBStkBottom;
}
#endif //NDEBUG


//lint -sem( mn_createtask, thread_create(1) )
/** \brief A helper to create a uC/OS-II task with its stack signature
\param[in] name - pointer to a uC/OS-II task implementation (prolog followed by an endless loop)
\param[in] arg - a mandatory argument to a uC/OS-II task (used as a pointer to its semaphore)
\param[in] stk - a pointer to the task's stack
\param prio - task priority (smaller number means higher priority)
\param stksz - stack size in stack units (happen to be u32 for ARM)
*/
static void mn_createtask(ostask_t *name, void *arg, u32 *stk, u8 prio, u32 stksz)
{
    OSPORT_FORMAT_STACKARRAY_EXT(stk, stksz);
    u8 MyErr = OSTaskCreate(name, arg, (void *)&stk[stksz - 1], prio);
    MN_DBG_ASSERT(MyErr == OSWRAP_NO_ERR);
    UNUSED_OK(MyErr); //for Release build
}


/** \brief Creates a task with its enabling semaphore and stack signature
    \param taskid - one of the pre-defined task ids
*/
void    oswrap_CreateTask(taskid_t taskid)
{
    os_event_t sem = OSSemCreate(0);

    *oswrap_GetTaskSemaphorePtr(taskid) = sem;
    mn_createtask(taskdef[taskid].name, *taskdef[taskid].arg, taskdef[taskid].stk, taskdef[taskid].prio, taskdef[taskid].stksz);
}

MN_DECLARE_API_FUNC(oswrap_GetEventCount)
/** \brief A helper for event counting (primary use: semaphores)
    \param event - A pointer to OS event
    \return event count
*/
u16_least oswrap_GetEventCount(const struct os_event *event)
{
    return event->OSEventCnt;
}

/** \brief Post the semaphore assigned to the specified task

    \param[in] taskid - a taskid assigned to the task
*/
void oswrap_PostTaskSemaphore(taskid_t taskid)
{
    os_event_t sem;
    u8 myErr;
    sem = *oswrap_GetTaskSemaphorePtr(taskid);
    myErr = OSSemPost(sem);
    MN_RT_ASSERT(myErr == OSWRAP_NO_ERR);
}


void oswrap_task(taskid_t taskid, const taskjob_t *taskjob)
{
    const taskchore_t * pChore;
    pChore = taskjob->inittable;
    while(*pChore != NULL)
    {
        (*pChore)();
        pChore++;
    }
    for(;;)
    {
        //Suspend task until a task event
        mn_waitsem(taskid);
        for(pChore =taskjob->runtable; *pChore!= NULL; pChore++)
        {
            (*pChore)();
        }
        process_SetWatchdogFlag(taskjob->wdflag);
        MN_UNIT_TEST_BREAK();
    }
}

//--------- Standalone semaphore ----------------
u16_least oswrap_WaitSem(os_event_t sem)
{
    u8 myErr;
    OSSemPend(sem, 0, &myErr);
    MN_RT_ASSERT(myErr == OSWRAP_NO_ERR);
    return sem->OSEventCnt;
}

void oswrap_PostSem(os_event_t sem)
{
    u8 myErr = OSSemPost(sem);
    MN_RT_ASSERT(myErr == OSWRAP_NO_ERR);
}

void oswrap_CreateSem(os_event_t *sem)
{
    *sem = OSSemCreate(0);
    MN_DBG_ASSERT(*sem!=NULL);
}

/* This line marks the end of the source */
