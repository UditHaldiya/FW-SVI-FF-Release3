/*
Copyright 2004-2006 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file tasktable.c
    \brief System task creation and startup sequencer

    CPU: Philips LPC21x4 (ARM)

    OWNER: Ernie Price

    $Archive: /MNCB/Dev/FIRMWARE/tasks/tasktable.c $
    $Date: 9/22/09 2:18p $
    $Revision: 11 $
    $Author: Anatoly Podpaly $

    \ingroup MainIdle
*/
#include "mnwrap.h"
#include "oswrap.h"
#include "dimensions.h"
#include "hart.h"
#if defined(COMM_NUM_CHANNELS) && (COMM_NUM_CHANNELS >=3) //will be more discerning when we know which of isp and ipc is more common
#include "ispcomm.h"
#include "mn_flash.h"
#define MORE_COMM_TASKS 1
#else
#define MORE_COMM_TASKS 0
#endif

#define CTRL_TSK_STK_SIZE       175
#define CYCLE_TSK_STK_SIZE      200
#define HART_TSK_STK_SIZE       200
#define PROCESS_TSK_STK_SIZE    300
#define PROXY_TSK_STK_SIZE    150


static MN_NO_INIT  u32  controlTskStk [CTRL_TSK_STK_SIZE];
static MN_NO_INIT  u32  cycleTskStk   [CYCLE_TSK_STK_SIZE];
static MN_NO_INIT  u32  hartTskStk    [HART_TSK_STK_SIZE];
static MN_NO_INIT  u32  procTskStk    [PROCESS_TSK_STK_SIZE];
static MN_NO_INIT  u32  proxyTskStk    [PROXY_TSK_STK_SIZE];

#if MORE_COMM_TASKS != 0
static MN_NO_INIT  u32  IpcTskStk    [HART_TSK_STK_SIZE];
static MN_NO_INIT  u32  IspTskStk    [HART_TSK_STK_SIZE];
#endif

/*lint -esym(765, procStack) -esym(714, procStack) -esym(9075, procStack)
In some systems, e.g. LPC21x4-based, we use our own C environment init and use
process task stack to run it, so it is used in Assembly only, such as in bsp_a.s79.
So, we intentionally omit a prior declaration [MISRA 2012 Rule 8.4, required],
as well as other "unused" lint messages
    notes:
        1. procStack must be 'const' because bsp_a.s79 uses this
           variable before C initialize.
        2. procStack MUST NOT point to a C-initialized area!
        3. See the comments in the header for main_TaskSequencer() below
*/
const u32 * const procStack = (procTskStk + PROCESS_TSK_STK_SIZE);

//lint -sem(main_TaskSequencer, thread_mono) designate it as a task
static void main_TaskSequencer(void *arg); //forward

static os_event_t   ctlTskSem,
                    cycleTskSem,
                    procTskSem,
                    proxyTskSem,
                    TskHartSemaphore
#if MORE_COMM_TASKS != 0
                    ,ipcTaskSem
                    ,ispTaskSem
#endif
                    ;

const taskdef_t taskdef[] =
{
    // The IDLE task is created by the uOS/II - this table entry
    // is not used to create this task.
    [TASKID_IDLE] =
    {
        NULL,
        NULL,
        OSTaskIdleStk,
        0,
        IDLE_TASK_PRIO_NOT_USER_CHANGEABLE
    },
    [TASKID_CONTROL] =
    {
        control_ControlTask,
        &ctlTskSem,
        controlTskStk,
        NELEM(controlTskStk),
        CONTROL_TASK_PRIO
    },
    [TASKID_CYCLE] =
    {
        cycle_CycleTask,
        &cycleTskSem,
        cycleTskStk,
        NELEM(cycleTskStk),
        CYCLE_TASK_PRIO
    },
    [TASKID_PROCESS] =
    {
        process_ProcessTask,
        &procTskSem,
        procTskStk,
        NELEM(procTskStk),
        PROCESS_TASK_PRIO
    },
    [TASKID_PROXY] =
    {
        proxy_ProxyTask,
        &proxyTskSem,
        proxyTskStk,
        NELEM(proxyTskStk),
        PROXY_TASK_PRIO
    },
    [TASKID_HART] =
    {
        main_TaskSequencer,
        &TskHartSemaphore,
        hartTskStk,
        NELEM(hartTskStk),
        HART_TASK_PRIO
    },
#if MORE_COMM_TASKS != 0
    [TASKID_ISPCOMM] =
    {
        isp_CommTask,
        &ispTaskSem,
        IspTskStk,
        NELEM(IspTskStk),
        ISP_TASK_PRIO
    },
    [TASKID_IPCCOMM] =
    {
        ipc_CommTask,
        &ipcTaskSem,
        IpcTskStk,
        NELEM(IpcTskStk),
        IPC_TASK_PRIO
    },
#endif
};

/** \brief Trigger the Cycle and Control tasks in a defined sequence
    this insures correct startup dependency.

    Strategy:

        The first three tasks, Control, Cycle and HART are created before
        starting the OS.  The Process Task is not created in function main()
        because the startup code is using its stack space until multitasking
        begins.

        Control and Cycle will each initialize and run until they wait on their
        respective semaphores at the top of their task loops.

        The HART task, being lowest priority of the first three, will then execute
        starting here at main_TaskSequencer(). The Cycle semaphore and the Control
        semaphore are each posted once here to insure the desired execution order.

        Next the Process task is created after which control passes to the main
        HART task code.  When HART is through with its initialize, the Process
        task will run.  This is where the 5 ms interrupts are started.

  \param arg - the semaphore for the HART task
*/
static void main_TaskSequencer(void *arg)
{
    oswrap_PostTaskSemaphore(TASKID_CYCLE);
    oswrap_PostTaskSemaphore(TASKID_CONTROL);
    oswrap_CreateTask(TASKID_PROCESS);
    hart_TskHart(arg);                  // never returns
}

//May be project-dependent; so Doxygen header is in oswrap.h
void oswrap_OSStart(void)
{
    oswrap_CreateTask(TASKID_CONTROL);
    oswrap_CreateTask(TASKID_CYCLE);
    oswrap_CreateTask(TASKID_HART);
    oswrap_CreateTask(TASKID_PROXY);

    /* Do not create the Process Task here! Startup is using its stack. */
#if MORE_COMM_TASKS != 0
    oswrap_CreateTask(TASKID_IPCCOMM);
    oswrap_CreateTask(TASKID_ISPCOMM);
#endif
    //bsp_StartTicks();                             // Start timer tick
    OSStart();                      // Start uC/OS-II - does not return
}

/* This line marks the end of the source */
