/*****************************************************************************
*                                                                            *
*                     SOFTING Industrial Automation GmbH                     *
*                          Richard-Reitzner-Allee 6                          *
*                                D-85540 Haar                                *
*                        Phone: ++49-89-4 56 56-0                            *
*                          Fax: ++49-89-4 56 56-3 99                         *
*                                                                            *
*                            SOFTING CONFIDENTIAL                            *
*                                                                            *
*                     Copyright (C) SOFTING IA GmbH 2012                     *
*                             All Rights Reserved                            *
*                                                                            *
* NOTICE: All information contained herein is, and remains the property of   *
*   SOFTING Industrial Automation GmbH and its suppliers, if any. The intel- *
*   lectual and technical concepts contained herein are proprietary to       *
*   SOFTING Industrial Automation GmbH and its suppliers and may be covered  *
*   by German and Foreign Patents, patents in process, and are protected by  *
*   trade secret or copyright law. Dissemination of this information or      *
*   reproduction of this material is strictly forbidden unless prior         *
*   written permission is obtained from SOFTING Industrial Automation GmbH.  *
******************************************************************************
******************************************************************************
*                                                                            *
* PROJECT_NAME             Softing FF/PA FD 2.42                             *
*                                                                            *
* VERSION                  FF - 2.42                                         *
*                          PA - 2.42 (beta)                                  *
*                                                                            *
* DATE                     16. April 2012                                    *
*                                                                            *
*****************************************************************************/


/* ===========================================================================

FILE_NAME          osif_tsk.c



FUNCTIONAL_MODULE_DESCRIPTION

This modul contains all task managements functions as well as facilities to
exchange events and messages beween tasks.

=========================================================================== */
#include "keywords.h"
#define  MODULE_ID      (COMP_OSIF + MOD_OSIFTSK)

INCLUDES
#include <string.h>
#include <stdlib.h>

#include "base.h"

#define VAR_EXTERN      /* Allocate OSIF global variables                   */

#include "osif.h"
#include "osif_cfg.h"
#include "osif_int.h"

#include "except.h"

#include "crc.h"
#include "oswrap.h"
#include "syswd.h"
#include "mntrapdef.h"

#include "hw_if.h"

LOCAL_DEFINES


#define TASK_SIZE_MSG       sizeof (void FAR_D *)
#define MBUFFER_SIZE        (TASK_SIZE_MSG * MAX_NUM_MSG)

#define CHECK_TASK_VALID(task_id, location)    \
                {                                                           \
                     if(OS_IsTask(&tcb_base[task_id]) == 0)                 \
                     {                                                      \
                         _OS_EXCEPTION(ERR_TASK_NEXIST, task_id, location, 0);   \
                     }                                                      \
                }

#define CHECK_EVENT_VALID(event, task_id, location)    \
                {                                                           \
                     if ( event & ~Task_cfg[task_id].valid_events )             \
                     {                                                      \
                         _OS_EXCEPTION(ERR_INV_EVENT, task_id, location, event);   \
                     }                                                      \
                }

#define CHECK_MSGEVT_VALID(event, task_id, location)    \
                {                                                           \
                     if ( event & ~Task_cfg[task_id].msg_events )               \
                     {                                                      \
                         _OS_EXCEPTION(ERR_INV_MSGEVT, task_id, location, event);  \
                     }                                                      \
                }

#if 0 //not used
#define CHECK_MSG_PTR_VALID(msg_ptr, task_id, location)    \
                {                                                           \
                     if ( !msg_ptr )                                        \
                     {                                                      \
                         _OS_EXCEPTION(ERR_INV_MSG_PTR, task_id, location, msg_ptr);  \
                     }                                                      \
                }
#endif
#if 0 //not used
#define TASK_LOOP_SYSSTART_ALWAYS(task_id)                  \
                OS_ExtendTaskContext(&task_ext);    \
                Task[task_id].main (OS_IF_EVENT_SYSSTART);                  \
                while (TRUE)                                                \
                {                                                           \
                    T_EVENT event;                                          \
                                                                            \
                    event = osif_wait_event (task_id, Task[task_id].await_events);      \
                    Task[task_id].main (event);                             \
                    _ASSERT (OS_RegionCnt == 0);                            \
                    _ASSERT (OS_DICnt == 0);                                \
                } /* end while */

    /* Not supported in standard Softing environment */
#define TASK_LOOP_SYSSTART_ON_COLDSTART(task_id)            \
                if ( Coldstart_flag != FALSE )                              \
                {                                                           \
                    Task[task_id].main (OS_IF_EVENT_SYSSTART);              \
                }                                                           \
                while (TRUE)                                                \
                {                                                           \
                    T_EVENT event;                                          \
                                                                            \
                    event = osif_wait_event (task_id, Task[task_id].await_events);      \
                    Task[task_id].main (event);                             \
                    _ASSERT (OS_RegionCnt == 0);                            \
                    _ASSERT (OS_DICnt == 0);                                \
                } /* end while */
#endif //0

LOCAL_TYPEDEFS
typedef enum T_TASK_STATE
{
    UNINITIALIZED   = 0,
    INITIALIZED,
    CREATED
    //,    DELETED,
    //TSK_IDLE
} T_TASK_STATE;

typedef struct _task_info {
        VOID (FAR_C         *main) (T_EVENT);   /* Task main routine         */
        USIGN8              prio;               /* Task priority             */
        T_EVENT             await_events;       /* expected events for task  */
        T_TASK_STATE        state;              /* current task state        */
        u8 task_id;
        u16 CheckWord;
} TASK_INFO;


FUNCTION_DECLARATIONS
FUNCTION LOCAL USIGN8 osif_event2mb (IN T_EVENT event);
FUNCTION LOCAL VOID idle_loop (VOID *arg);

EXPORT_DATA

IMPORT_DATA

LOCAL_DATA

#include "da_osif.h"                            /* DATA SEGMENT DEFINITION */
static u8  mbuffer_base[MBUFFER_SIZE];
static TASK_INFO   Task[MAX_TASK_NUM];
#include "da_def.h"                             /* DEFAULT DATA SEGMENT */

#include "da_embos.h"                           /* DATA SEGMENT DEFINITION */
static OS_TASK  tcb_base[MAX_TASK_NUM];

static NO_INIT OS_TASK     Idle_tcb;
#include "da_def.h"                             /* DEFAULT DATA SEGMENT */

#include "da_osstk.h"                           /* DATA SEGMENT DEFINITION */
/* recommendation from Segger to use at minimum 256 bytes for Task Stacks */
static NO_INIT USIGN8  Idle_stack[256];
#include "da_def.h"                             /* DEFAULT DATA SEGMENT */

//MN extensions
static void task_SwitchInHook(void *pStack)
{
    //Nothing here yet
    UNUSED_OK(pStack);
}

//Same signature as in APP
#define STK_MAGIC       0xefbeaddeU // stack check magic number - little-endian deadbeef

static void task_SwitchOutHook(const void *pStack)
{
    UNUSED_OK(pStack);
    OS_TASK *t = OS_GetpCurrentTask();
#if defined(OS_LIBMODE_XR) || defined(OS_LIBMODE_R)
    //Our own field for detection
    void *vStackBottom = t->mn_StackBottom;
    u32 *p = vStackBottom;
#else //In general so, but we really care about OS_LIBMODE_S and somewhat about OS_LIBMODE_D
    void *vStackBottom = t->pStackBot;
    u32 *p = vStackBottom;
    --p; //step back to where the signature was planted
#endif
    if(*p != STK_MAGIC)
    {
        mn_assert(p, -TRAPID_STACK_OVFL);
    }
}

static void task_SwitchIdleOutHook(const void *pStack)
{
    UNUSED_OK(pStack);
    u32 *p = (void *)Idle_stack;
    if(*p != STK_MAGIC)
    {
        mn_assert(p, -TRAPID_STACK_OVFL);
    }
}

const OS_EXTEND_TASK_CONTEXT task_ext =
{
    .pfSave = task_SwitchInHook,
    .pfRestore = task_SwitchOutHook,
};
static const OS_EXTEND_TASK_CONTEXT idle_task_ext =
{
    .pfSave = task_SwitchInHook,
    .pfRestore = task_SwitchIdleOutHook,
};


FUNCTION GLOBAL VOID osif_init (VOID)
/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to initialize the OS Interface.

possible-return-codes:
- NONE
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

    int      i;
    u32 l;
    USIGN32  mbuf_idx;

FUNCTION_BODY

    Sema_init = FALSE;
    Tim_init  = FALSE;

/* --- init task management ------------------------------------------------ */
    mbuf_idx = 0;
    for (i=0; i<MAX_TASK_NUM; i++)
    {
            /* Check if OS_IF_EVENT_SYSSTART value (0x80) is */
            /* already defined for other task specific event */
            /*-----------------------------------------------*/

        if(Task_cfg[i].stack != NULL) //Use it as an indication of unused task
        {
            _ASSERT (!(Task_cfg[i].valid_events & OS_IF_EVENT_SYSSTART));

            TASK_INFO t;

            t.state        = INITIALIZED;
            t.main         = NULL;
            t.task_id = (u8)i;

            u8_least mb_cnt = 0;
            for (l=0; l<NUM_EVENTS; l++)
            {
                if ( (Task_cfg[i].msg_events & (0x01U<< l)) != 0 )
                {
                    if ( (Task_cfg[i].valid_events & (0x01U<< l)) == 0 )
                    {
                        _OS_EXCEPTION(ERR_INV_MSGEVT, i, FKT_INIT, 0);
                    }

                    mb_cnt++;
                    MN_ASSERT(mb_cnt < Task_cfg[i].num_msg);

                    CREATEMB(&Task_cfg[i].mb[l], TASK_SIZE_MSG, Task_cfg[i].num_msg, mbuffer_base + mbuf_idx);
                    mbuf_idx += TASK_SIZE_MSG * Task_cfg[i].num_msg;
                    if ( mbuf_idx >= MBUFFER_SIZE )
                    {
                        _OS_EXCEPTION(ERR_INSUFF_MBUF, i, FKT_INIT, mbuf_idx);
                    }

                }
            } /* end for l */
            Struct_Copy(TASK_INFO, &Task[i], &t);
        }
    } /* end for i */

        /* create IDLE task */
    OS_CreateTaskEx(
                    &Idle_tcb,
                    "Idle_task",
                    1,
                    idle_loop,
                    Idle_stack+sizeof(USIGN32),
                    sizeof (Idle_stack)-sizeof(USIGN32),
                    2,
                    NULL
                   );
    *(USIGN32 *)Idle_stack = STK_MAGIC;
#if defined(OS_LIBMODE_XR) || defined(OS_LIBMODE_R)
    Idle_tcb.mn_StackBottom = Idle_stack; //not really necessary
#endif
}

//Redirect
void mnfdc_wd_reset_wd_counter(void)
{
    //Nothing here in favor of consistent WD strategy
}
//------------------- end watchdog part ----------------------------

/** \brief Event wait helper
\param tcb - a valid pointer to a task control block
\param event_mask - bitmap of events which are waited for
\return bitmap of unhandled (remaining) events
*/
static T_EVENT osif_wait_event_byTCB(OS_TASK *tcb, T_EVENT event_mask)
{
        /* Receive event from buffer */
    T_EVENT rcv_event = OS_WaitEvent (event_mask);
        /* Check for unexpected (= masked) events */
    if ( (rcv_event & ~event_mask) != 0 )
    {
        OS_SignalEvent ((rcv_event & ~event_mask), tcb);
        rcv_event &= event_mask;
    }
    return rcv_event;
}

/** \brief Common wrapper for Softing-style tasks
\param tptr - a pointer to task definition
*/
static void osif_TaskRunner(void *tptr)
{
    OS_ExtendTaskContext(&task_ext);
    const volatile TASK_INFO *pTask = tptr;
    void (FAR_C *tmain) (T_EVENT);   /* Task main routine         */
    MN_ENTER_CRITICAL();
        Struct_Test(TASK_INFO, (TASK_INFO *)tptr);
        tmain = pTask->main;
    MN_EXIT_CRITICAL();

    syswd_NotifyWatchdog(pTask->task_id);
    tmain(OS_IF_EVENT_SYSSTART);
    osif_TickleWatchdog(pTask->task_id);
    for(;;)
    {
        T_EVENT await_events;
        MN_ENTER_CRITICAL();
            Struct_Test(TASK_INFO, (TASK_INFO *)tptr);
            await_events = pTask->await_events;
            tmain = pTask->main;
        MN_EXIT_CRITICAL();
        T_EVENT event = osif_wait_event_byTCB(tptr, await_events);
        tmain(event);
        osif_TickleWatchdog(pTask->task_id);
        _ASSERT (OS_RegionCnt == 0);
        _ASSERT (OS_DICnt == 0);
    } /* end while */
}



/*****************************************************************************/
/*** Task management                                                       ***/
/*****************************************************************************/

FUNCTION GLOBAL VOID osif_create_task
    (
        IN USIGN8 task_id,
        IN USIGN8 task_prio,
        IN VOID   (FAR_C *task_main_func) (T_EVENT),
        IN T_EVENT event_mask
    )

/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to create a task. In case of any error the global exception
handler is called. If the task already has been created, only the priority is
changed; the main function pointer is ignored.

IN:  task_id                 task-identifier
     task_prio               task priority
     task_rcv_main_func      task main function pointer
     event_mask              events, the task is expecting on wakeup


possible return value:
- NONE

-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    CHECK_DST_TASK_ID(task_id, FKT_CREATE_TASK);
    MN_ASSERT(task_id < NELEM(Task));

    osif_disable_all_tasks ();
    if ( Task[task_id].state == UNINITIALIZED )
    {
        _OS_EXCEPTION(ERR_TASK_NEXIST, task_id, FKT_CREATE_TASK, 0);
    }
    CHECK_EVENT_VALID(event_mask, task_id, FKT_CREATE_TASK);

    if ( task_main_func != NULL )
    {
        //storeMemberPtr doesn't work for function pointers
        Task[task_id].CheckWord +=
            (u16)storeULong((volatile u32*)(void*)&Task[task_id].main, HARDWARE(u32,(task_main_func)));
    }
    else
    {
        if ( Task[task_id].main == NULL )
        {
            _OS_EXCEPTION(ERR_INV_MAINFKT, task_id, FKT_CREATE_TASK, 0);
        }
    }

    if ( task_prio == 0 )
    {
        task_prio = Task_cfg[task_id].prio;
    }
    storeMemberInt(&Task[task_id], prio, task_prio);

    if ( (Task[task_id].state == INITIALIZED) || (event_mask != 0) )
    {
        storeMemberInt(&Task[task_id], await_events, event_mask);
    }

    if ( Task[task_id].state == CREATED )
    {
        OS_SetPriority (&tcb_base[task_id], task_prio);
    }
    else
    {
        storeMemberInt(&Task[task_id], state, CREATED);
        *(USIGN32 *)Task_cfg[task_id].stack = STK_MAGIC;
        OS_CreateTaskEx (
                        &tcb_base[task_id],
                        Task_cfg[task_id].name,
                        task_prio,
                        osif_TaskRunner,
                        (USIGN8 *)Task_cfg[task_id].stack + sizeof(USIGN32),
                        Task_cfg[task_id].stacksize - sizeof(USIGN32),
                        2,
                        &Task[task_id]
                      );
#if defined(OS_LIBMODE_XR) || defined(OS_LIBMODE_R)
        tcb_base[task_id].mn_StackBottom = Task_cfg[task_id].stack;
#endif
    }
    osif_enable_all_tasks ();
}


u8 tcb2index(const OS_TASK *tcb)
{
    u8_least i;
    for (i=0; i<MAX_TASK_NUM; i++)
    {
        if ( &tcb_base[i] == tcb )
        {
            return (u8)i;
        }
    } /* end for i */

    _OS_EXCEPTION(ERR_NO_TASK_ID, 255, FKT_GET_TASK_ID, OS_pCurrentTask);

    return (255);
}

/** \brief Test if the passed taskid matches the running task

    \param taskid - one of the pre-defined task ids
*/
bool_t oswrap_IsContext(taskid_t taskid)
{
    if(OS_pCurrentTask == NULL)
    {
        return false;
    }
    return &tcb_base[taskid] == OS_pCurrentTask;
}


FUNCTION GLOBAL USIGN8 osif_get_current_task_id (VOID)
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Evaluates the ID of the current running task.

possible return value:
- ID of the current running task
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
    u8_least i;

FUNCTION_BODY
    for (i=0; i<MAX_TASK_NUM; i++)
    {
        if ( &tcb_base[i] == OS_pCurrentTask )
        {
            return (USIGN8)i;
        }
    } /* end for i */

    _OS_EXCEPTION(ERR_NO_TASK_ID, 255, FKT_GET_TASK_ID, OS_pCurrentTask);

    return (255);
}


FUNCTION GLOBAL VOID osif_delete_task
    (
        IN USIGN8 task_id
    )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to delete a task. In case of any error the global exception
handler is called.

IN:  task_id                 task-identifier

possible return value:
- NONE
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
    CHECK_DST_TASK_ID(task_id, FKT_DELETE_TASK);
    MN_ASSERT(task_id < NELEM(Task));

    OS_Terminate (&tcb_base[task_id]);

    return;
}


/******************************************************************************/

FUNCTION GLOBAL VOID osif_disable_task
  (
    IN USIGN8   task_id
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
Refrains a certain task from being executed by setting its priority to 0.

PARAMETERS:
task_id:    ID of task to be disabled

GLOBALS_AFFECTED:
none

RETURN_VALUES:
none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
    CHECK_DST_TASK_ID(task_id, FKT_DISABLE_TASK);
    CHECK_TASK_VALID(task_id, FKT_DISABLE_TASK);

    MN_DBG_ASSERT(task_id != osif_get_current_task_id());

    OS_SetPriority (&tcb_base[task_id], 0);

    return;
} /* FUNCTION disable_tread */


/******************************************************************************/

FUNCTION GLOBAL VOID osif_enable_task
  (
    IN USIGN8   task_id
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
Re-enables a previously disables task by restoring its original priority.

PARAMETERS:
task_id:    ID of task to be disabled

GLOBALS_AFFECTED:
none

RETURN_VALUES:
none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
    CHECK_DST_TASK_ID(task_id, FKT_ENABLE_TASK);
    CHECK_TASK_VALID(task_id, FKT_ENABLE_TASK);

    OS_SetPriority (&tcb_base[task_id], Task[task_id].prio);

    return;
} /* FUNCTION disable_tread */


/******************************************************************************/

FUNCTION GLOBAL VOID osif_disable_all_tasks (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
    Refrains the system globally from scheduling tasks. Must be used in pair
    with 'osif_enable_all_tasks ()'.

PARAMETERS:
    none

GLOBALS_AFFECTED:
    none

RETURN_VALUES:
    none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
    OS_EnterRegion ();
    return ;
} /* FUNCTION osif_disable_all_tasks */


/******************************************************************************/

FUNCTION GLOBAL VOID osif_enable_all_tasks (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
    Re-enables the task scheduling. Must be used in pair with
    'osif_disable_all_tasks ()'.

PARAMETERS:
    none

GLOBALS_AFFECTED:
    none

RETURN_VALUES:
    none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
    OS_LeaveRegion ();
    return ;
} /* FUNCTION osif_enable_all_tasks */



/******************************************************************************/

FUNCTION GLOBAL VOID DISABLE_INTERRUPTS (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
    Disables all interrupts. Must be used in pair with 'RESTORE_INTERRUPTS()'.

PARAMETERS:
    none

GLOBALS_AFFECTED:
    none

RETURN_VALUES:
    none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    OS_SDI();
    return;
} /* FUNCTION DISABLE_INTERRUPTS */


/******************************************************************************/

FUNCTION GLOBAL VOID RESTORE_INTERRUPTS (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
    Sets interrupt enable state to state before call to 'DISABLE_INTERRUPTS()'.

PARAMETERS:
    none

GLOBALS_AFFECTED:
    none

RETURN_VALUES:
    none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    OS_RI();
    return;
} /* FUNCTION RESTORE_INTERRUPTS */


/* ------------------------------------------------------------------------- */
/* memory allocation functions                                               */
/* ------------------------------------------------------------------------- */

/******************************************************************************/

FUNCTION GLOBAL VOID * osif_malloc
  (
    IN USIGN16 mem_size
  )

/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
  This function allocates memory in a thread-safe way.

PARAMETERS:
  mem_size => sizeof requested memory

GLOBALS_AFFECTED:
  none

RETURN_VALUES:
  pointer to the new memory block
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  VOID *mem_block;

FUNCTION_BODY

  osif_disable_all_tasks();
  mem_block = malloc(mem_size);
  osif_enable_all_tasks();

  return mem_block;
}


/******************************************************************************/

FUNCTION GLOBAL VOID osif_free
  (
    IN VOID * mem_block
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
  This functio frees memory in a thread-safe way.

PARAMETERS:
  mem_block => pointer to allocated memory

GLOBALS_AFFECTED:
  none

RETURN_VALUES:
  none
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  osif_disable_all_tasks();
  free(mem_block);
  osif_enable_all_tasks();
}


/* ------------------------------------------------------------------------- */
/* event control functions                                                   */
/* ------------------------------------------------------------------------- */

FUNCTION GLOBAL T_EVENT osif_wait_event
    (
        IN  USIGN8 task_id,
        IN  T_EVENT event_mask
    )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to receive an event addressed to the calling task. The
call to 'osif_wait_event' is blocking, i.e. the function does not return, until
an event is received by the task.

IN:     event_mask              -> events which are waited for

possible return value:
- event data
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

        /* Check task identifier */
        /*-----------------------*/
    CHECK_DST_TASK_ID(task_id, FKT_WAIT_EVENT);
    CHECK_TASK_VALID(task_id, FKT_WAIT_EVENT);

        /* Check event mask */
        /*------------------*/
    CHECK_EVENT_VALID(event_mask, task_id, FKT_WAIT_EVENT);

    return osif_wait_event_byTCB(&tcb_base[task_id], event_mask);
}

FUNCTION GLOBAL T_EVENT osif_clear_event
    (
        IN  USIGN8 task_id,
        IN  T_EVENT event_mask
    )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Clears the event area of a task by the events defined by 'event_mask'.
'task_id' must be the ID of the calling task.

The function returns immediately, i.e. if none of the selected events
are active, nothing happens.

IN:     task_id                 -> ID of task, which events are to be cleared
        event_mask              -> events which are to be cleared

possible return value:
- event data
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
        T_EVENT rcv_event;

FUNCTION_BODY


        /* Check task identifier */
        /*-----------------------*/
    CHECK_DST_TASK_ID(task_id, FKT_WAIT_EVENT);
    CHECK_TASK_VALID(task_id, FKT_WAIT_EVENT);
    _ASSERT(task_id == osif_get_current_task_id ());

        /* Check event mask */
        /*------------------*/
    CHECK_EVENT_VALID(event_mask, task_id, FKT_WAIT_EVENT);

        /* Check for currently active events */
        /*-----------------------------------*/
    osif_disable_all_tasks();
    rcv_event = OS_GetEventsOccured (&tcb_base[task_id]);
    rcv_event &= event_mask;

        /* Clear active events by executing WaitEvent */
        /*--------------------------------------------*/
    if ( rcv_event != 0 )
    {
        (void)OS_WaitSingleEvent (rcv_event);
    }


    osif_enable_all_tasks();
    return (rcv_event);
}

FUNCTION GLOBAL VOID  osif_set_event
(
    IN USIGN8 task_id,
    IN USIGN8 event
)
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to send and queue an event message for the task specified
by 'task_id'.

IN:  task_id      ->  task identifer which shall receive the event
IN:  event        ->  event to be signaled

possible return value:
- NONE
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY


        /* Check task identifier */
        /*-----------------------*/
    CHECK_DST_TASK_ID(task_id, FKT_SET_EVENT);
    CHECK_TASK_VALID(task_id, FKT_SET_EVENT);

        /* Check event */
        /*-------------*/
    CHECK_EVENT_VALID(event, task_id, FKT_SET_EVENT);

        /* Send event */
        /*------------*/
    syswd_NotifyWatchdog(task_id);
    OS_SignalEvent (event, &tcb_base[task_id]);

    return;
}


FUNCTION GLOBAL VOID  osif_resume_task
    (
        IN USIGN8 task_id
    )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to resume a task specified by 'task_id'.

IN:  task_id      ->  task identifer of the task to resume

possible return value:
- NONE
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    CHECK_DST_TASK_ID(task_id, FKT_RESUME_TASK);
    CHECK_TASK_VALID(task_id, FKT_RESUME_TASK);

    osif_set_event (task_id, (T_EVENT) OS_IF_EVENT_RESUME);

    return;
}

/* ------------------------------------------------------------------------- */
/* message control functions                                                 */
/* ------------------------------------------------------------------------- */
FUNCTION GLOBAL T_OS_MSG_HDR *osif_get_msg
    (
        IN USIGN8 task_id,
        IN T_EVENT event
    )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to get a pointer to the message which has been
indicated by the event OS_IF_EVENT_MESSAGE

IN:  task_id            -> task identifier which want to get the message

possible return value:
- pointer to the received message
- NULL if no message is available
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
        u32 mb_idx;
        T_OS_MSG_HDR * mail = NULL;

FUNCTION_BODY

        /* Check task identifier */
        /*-----------------------*/
    CHECK_DST_TASK_ID(task_id, FKT_GET_MSG);
    CHECK_TASK_VALID(task_id, FKT_GET_MSG);

        /* Check for valid event */
        /*-----------------------*/
    CHECK_MSGEVT_VALID(event, task_id, FKT_GET_MSG);

        /* convert event bit to mailbox index */
        /*------------------------------------*/
    mb_idx = osif_event2mb (event);
    MN_ASSERT(mb_idx < Task_cfg[task_id].num_msg);
    /* Receive mail from mailbox */
    /*---------------------------*/
    if ( OS_GetMailCond (&Task_cfg[task_id].mb[mb_idx], (VOID *) (&mail)) )
    {
        mail = NULL;
    }
    return mail;
}


FUNCTION GLOBAL VOID osif_send_msg
    (
        IN USIGN8 msg_event,
        IN USIGN8 rcv_task_id,
        IN USIGN8 snd_task_id,
        IN T_OS_MSG_HDR FAR_D *msg_ptr
    )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function is used to send a MSG-BLOCKS to 'rcv-task-id' via
operating system. The MSG-BLOCK must start with a T_OS_MSG_HDR.

IN:     msg_event               -> event id, the message shall be connected to
IN:     rcv_task_id             -> receive task id
IN:     snd_task_id             -> send task id
IN:     msg_ptr                 -> pointer to USR-MSG

possible return value:
- NONE
-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
    USIGN8 mb_idx;

FUNCTION_BODY

        /* Check task identifier */
        /*-----------------------*/
    CHECK_DST_TASK_ID(rcv_task_id, FKT_SND_MSG_RCV);
    CHECK_TASK_VALID(rcv_task_id, FKT_SND_MSG_RCV);
    CHECK_TASK_ID(snd_task_id, FKT_SND_MSG_SND);

    CHECK_MSGEVT_VALID(msg_event, rcv_task_id, FKT_SND_MSG_RCV);
    //CHECK_MSG_PTR_VALID(msg_ptr, snd_task_id, FKT_SND_MSG_SND);
    MN_ASSERT(msg_ptr!=NULL); //Guarantee no-return

        /* convert event bit to mailbox index */
        /*------------------------------------*/
    mb_idx = osif_event2mb (msg_event);
    MN_ASSERT(mb_idx < Task_cfg[rcv_task_id].num_msg);
    /* Process message */
    /*-----------------*/
    msg_ptr->message_id  = msg_event;
    msg_ptr->snd_task_id = snd_task_id;

    if ( OS_PutMailCond ( &Task_cfg[rcv_task_id].mb[mb_idx], (VOID *) &msg_ptr) ) {
        _OS_EXCEPTION(ERR_MSG_NOT_PROC, snd_task_id, FKT_SND_MSG_SND, 0);
    }
    osif_set_event (rcv_task_id, msg_event);
}


/*########################  Internal functions  ############################*/

FUNCTION LOCAL USIGN8 osif_event2mb
    (
        IN T_EVENT event
    )
/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Converts a event to the according mailbox index
IN:  event            -> event to be converted

possible return value:
- mailbox index
- 0xFF (255) if more than one events are specified
----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
        USIGN8 mb_idx;

FUNCTION_BODY
    switch (event)
    {
        case 0x01:
            mb_idx = 0;
            break;
        case 0x02:
            mb_idx = 1;
            break;
        case 0x04:
            mb_idx = 2;
            break;
        case 0x08:
            mb_idx = 3;
            break;
        case 0x10:
            mb_idx = 4;
            break;
        case 0x20:
            mb_idx = 5;
            break;
        case 0x40:
            mb_idx = 6;
            break;
        case 0x80:
            mb_idx = 7;
            break;
        default:
            mb_idx = 0xff;
    } /* end switch */

    return (mb_idx);
}


/******************************************************************************/

FUNCTION LOCAL VOID idle_loop
  (
    VOID *arg
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
Idle task loop

PARAMETERS:
none

GLOBALS_AFFECTED:
none

RETURN_VALUES:
none

------------------------------------------------------------------------------*/
{
    UNUSED_OK(arg); //Justo to not have simple OS_CreateTask in the build
    OS_ExtendTaskContext(&idle_task_ext);
#if 1   //this code is for the idle time bachground check
    OSTaskIdleHook();
#else   //this code is for the minimal power consumption
    while (TRUE)
    {
        __WFI();
    }
#endif
} /* FUNCTION idle_loop */

#ifndef OS_LIBMODE_R
/*
**************************************************************
*
*             Run-time error reaction  (OS_Error)
*
**************************************************************

 Run-time error reaction

 When this happens, a fatal error has occured and the kernel
 can not continue. In linux, the equivalent would be a
 "kernel panic"

 This routine can be modified to suit your needs ...
 E.g. a red LED could light up. When using an
 emulator, you may set a breakpoint here.
 In the release builds of the library (R), this routine is not required
 (as no checks are performed).
 In the stack check builds (S/SP), only error 120 may occur.
 In the debug builds(D/DP), all of the listed errors may occur.

  The following are the current errorcodes (V2.80) :
  (Please refer to the documentation for more info)

OS_ERR_STACK                          (120)
*** invalid or non-initialized data structures ***
OS_ERR_INV_TASK                       (128)
OS_ERR_INV_TIMER                      (129)
OS_ERR_INV_MAILBOX                    (130)
OS_ERR_INV_CSEMA                      (132)
OS_ERR_INV_RSEMA                      (133)

*** Using GetMail1 or PutMail1 or GetMailCond1 or PutMailCond1 on a non-1 byte mailbox  ***
OS_ERR_MAILBOX_NOT1                   (135)

***internal errors, please contact SEGGER Microcontrollersysteme ***
OS_ERR_MAILBOX_NOT_IN_LIST            (140)
OS_ERR_TASKLIST_CORRUPT               (142)


*** not matching routine calls or macro usage ***
OS_ERR_UNUSE_BEFORE_USE               (150)
OS_ERR_LEAVEREGION_BEFORE_ENTERREGION (151)
OS_ERR_LEAVEINT                       (152)
OS_ERR_DICNT                          (153)
OS_ERR_INTERRUPT_DISABLED             (154)

*** not a legal system call during interrupt ***
OS_ERR_ILLEGAL_IN_ISR                 (160)
*** not a legal system call during timer ***
OS_ERR_ILLEGAL_IN_TIMER               (161)

** double used data structures **
OS_ERR_2USE_TASK                      (170)
OS_ERR_2USE_TIMER                     (171)
OS_ERR_2USE_MAILBOX                   (172)
OS_ERR_2USE_BSEMA                     (173)
OS_ERR_2USE_CSEMA                     (174)
OS_ERR_2USE_RSEMA                     (175)

*/

void OS_Error(s32 ErrCode)
{
    OS_EnterRegion();     /* Avoid further task switches */
    if(ErrCode != OS_ERR_STACK)
    {
        mn_assert((const void *)__get_LR(), ErrCode);
    }
    else
    {
        //we use our own *task* stack checking
        //"system" and interrupt stacks are left at embOS strength
    }
    OS_LeaveRegion();     /* Avoid further task switches */
}
#endif


#ifdef COMPILER_IAR
#pragma function=default
#endif /* COMPILER_IAR */
