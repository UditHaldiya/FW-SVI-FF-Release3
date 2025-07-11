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

    CPU: Any; for uC/OS-II 2.76 RTOS

    OWNER: Ernie Price

    \ingroup OSWrap
*/
/*
    This file contains duplicates of some of the items defined in ucos_ii.h.
    They are included here to avoid exposing application modules to the full
    structures of the operating system.  It is recognized that duplicate #defines
    and function prototypes are against MISRA standard but the choice here is to
    isolate the operating system.

    This file and ucos_ii.h should be included in os_wrap.c to insure that the
    definitions stay in synch.  This is the ONLY place that both files should be
    included.
*/
#ifndef OSWRAP_H_
#define OSWRAP_H_
#include "mnassert.h"
#include "taskids.h"
#include "mn_instrum.h"

#define OSPORT_EXPOSE_TCB 0


#define  CONTROL_TASK_PRIO     10u                          // highest priority
#define  CYCLE_TASK_PRIO       15u                          // middle priority
#define  FRAM_MUTEX_PRIO       (CYCLE_TASK_PRIO + 1u)       // must not be logically lower than cycle task
#define  IPC_TASK_PRIO         20u                          // lower priority
#define  ISP_TASK_PRIO         25u                          // lower priority
#define  HART_TASK_PRIO        30u                          // lower priority
#define  PROCESS_TASK_PRIO     40u                          // lowest priority except Idle
#define  PROXY_TASK_PRIO     45u                          // between process and comm.


typedef struct os_event * os_event_t;
typedef struct os_tcb   * os_tcb_t;
typedef void    ostask_t(void *arg);

extern void oswrap_CreateTask(taskid_t taskid);
#define  oswrap_GetTaskSemaphorePtr(taskid)  (taskdef[taskid].arg)

extern u16_least oswrap_GetEventCount(const struct os_event *event);


#define OS_IDLE_TASK_PRIO    63
#define OSWRAP_NO_ERR      0U

//---------------------------------------------------------------
// The IDLE task is created by the uOS/II and its priority set to the lowest - 63.
// The definition is used in the task table, it is not intended to be modified by the user.

#define IDLE_TASK_PRIO_NOT_USER_CHANGEABLE  (OS_IDLE_TASK_PRIO)
//---------------------------------------------------------------

extern  os_tcb_t OSTCBCur; //DO NOT use directly; use the wrapper instead

//lint -sem(oswrap_IsContext, pure)
extern  bool_t oswrap_IsContext(taskid_t taskid);

#ifndef NDEBUG
typedef const void * Atomic_ TaskStamp_t;
TaskStamp_t oswrap_GetTaskStamp(void);
#endif

#define oswrap_IsOSRunning() (OSRunning != 0U)
extern      u8  OSRunning;   //DO NOT use directly; use the wrapper instead               //  1 if running; 0 if not
extern      u32 OSTaskIdleStk[];
extern void        OSInit(void);
extern void        OSIntEnter(void);
extern void        OSIntExit(void);

extern os_event_t  OSMutexCreate(u8 prio, u8 *err);
extern void        OSMutexPend(os_event_t pevent, u16 timeout, u8 *err);
extern u8          OSMutexPost(os_event_t  pevent);

extern os_event_t  OSSemCreate(u16 cnt);
extern void        OSSemPend(os_event_t pevent, u16 timeout, u8 *err);
extern u8          OSSemPost(os_event_t pevent);

extern u8          OSTaskCreate(void (*task)(void *pd), void *p_arg, u32 *ptos, u8 prio);
#if 0
extern u8          OSTaskCreateExt(void  (*task)(void *pd),
                              void   *p_arg,
                              u32 *ptos,
                              u8   prio,
                              u16  id,
                              u32 *pbos,
                              u32 stk_size,
                              void   *pext,
                              u16  opt);
#endif
extern void        OSStart(void);

//lint -sem(OSTaskIdleHook, thread_mono) designate it as a task
extern void        OSTaskIdleHook(void);

typedef struct taskdef_t
{
    ostask_t *name;
    os_event_t *arg; //task's semaphore
    u32 *stk;
    u16 stksz;
    u8 prio;
} taskdef_t;
extern const taskdef_t taskdef[];



extern void oswrap_PostTaskSemaphore(taskid_t taskid);

typedef void (*taskchore_t)(void); //! the type of a table entry in a task table for hard real time tasks
typedef struct taskjob_t //!< table definition type for a hard real time task
{
    const taskchore_t  *inittable; //!< a pointer to the table of initialization chores
    const taskchore_t *runtable;  //!< a pointer to the table of periodic chores
    taskid_t wdflag; //!< a watchdog flag to check in on completion
} taskjob_t;

extern void oswrap_task(taskid_t taskid, const taskjob_t *taskjob); //common hard-real-time task frame

/** \brief A required and maybe project-dependent function that creates
all tasks in the required sequence and starts the RTOS
*/
extern void oswrap_OSStart(void);

extern void idle_EstimateTime(void);

//----------- MNCB tasks (may migrate to a separate header if diverge) ------------

//lint -sem(control_ControlTask, thread_mono) designate it as a task
extern void control_ControlTask(void *arg);

//lint -sem(cycle_CycleTask, thread_mono) designate it as a task
extern       void cycle_CycleTask(void *arg);

//lint -sem(process_ProcessTask, thread_mono) designate it as a task
extern void process_ProcessTask(void *arg);

//OSTaskIdleHook and main sequencer are communicated to lint elsewhere

//-----------------------------------------
#ifndef INSTRUM_BEFORE_SEMAPHORE
#define INSTRUM_BEFORE_SEMAPHORE(taskid) /*nothing*/
#endif
#ifndef INSTRUM_AFTER_SEMAPHORE
#define INSTRUM_AFTER_SEMAPHORE(taskid) /*nothing*/
#endif

MN_INLINE void mn_waitforsem(taskid_t taskid)
{
    u8 myErr;
    INSTRUM_BEFORE_SEMAPHORE(taskid);
    OSSemPend(*oswrap_GetTaskSemaphorePtr(taskid), 0, &myErr);
    MN_RT_ASSERT(myErr == OSWRAP_NO_ERR);
    INSTRUM_AFTER_SEMAPHORE(taskid);
}

extern void mn_waitsem(taskid_t taskid);

//-------------------------------------------------------------------
// This is the implementation for the RTOS Interrupt Enter/Exit API

MN_INLINE void oswrap_IntrEnter(void)
{
    OSIntEnter();
}

MN_INLINE void oswrap_IntrExit(void)
{
    OSIntExit();
}

//-------------------------------------------------------------------

//--------- Standalone semaphore ----------------
MN_DECLARE_API_FUNC(oswrap_CreateSem, oswrap_PostSem, oswrap_WaitSem)
extern u16_least oswrap_WaitSem(os_event_t sem);
extern void oswrap_PostSem(os_event_t sem);
extern void oswrap_CreateSem(os_event_t *sem);

#endif // OSWRAP_H_

/* This line marks the end of the source */
