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

FILE_NAME          hm_task.c



FUNCTIONAL_MODULE_DESCRIPTION

=========================================================================== */

  #include <keywords.h>
  #define  MODULE_ID      (COMP_HM + MOD_HM_TASK)

INCLUDES

#include <base.h>
#include <osif.h>
#include <except.h>
#include <hw_cfg.h>
#include <hw_if.h>
#include <hm_api.h>
#include <hm_if.h>
#include <hm_cfg.h>
#include <hm.h>

#include "faultpublic.h"
#include "mn_flash_selftest.h"

FUNCTION_DECLARATIONS

#define CHECK_HM_STATE 0

#if CHECK_HM_STATE
  FUNCTION GLOBAL USIGN8 appl_check_hm_state();
#else
/*
Softing example shows a pattern
...
    if (appl_check_hm_state() == HM_RUN)
    {
      write_loc.startup_sync = FALSE;
    }
    else
    {
      write_loc.startup_sync = TRUE; //static revision is not incremented
    }
...
for parameters owned by a slave processor but cached in FF processor.
We don't need this pattern because by MN design, configuration parameters
owned by APP are retrieved on request and never cached.
*/
#endif


LOCAL_DEFINES

//  #define ACYCLIC     0x01
//  #define CYCLIC      0x02
//  #define REGULAR     0x03
//  #define NONRELEVANT 0x04

  #define HM_INIT_STATE  0x00
  #define HM_RUN         0x01

  #define ERROR_COUNTER_LIMIT    5
  #define CMD0_BUF_SIZE         32

#if defined (PD30) || defined (KD30)
//  #define HM_TRACE
#endif

  typedef enum {
    HM_IDLE     = 0,
    HM_ACYCLIC,
    HM_CYCLIC,
    HM_REGULAR
  } T_HM_SCHED_STATE;

typedef struct T_HM_SCHEDULER
{
    T_HM_SCHED_STATE    state;
    BOOL                cyc_act;
    BOOL                cyc_start;
    BOOL                cyc_shutdown;
    BOOL                acyc_act;
    BOOL                reg_act;
    BOOL                operation;
    USIGN16             cyc_idx;
    USIGN16             reg_idx;
} T_HM_SCHEDULER;

#define SCHED_DEFAULT \
{\
    .state   = HM_IDLE,\
    .cyc_act = FALSE,\
    .cyc_start = FALSE,\
    .cyc_shutdown = FALSE,\
    .acyc_act = FALSE,\
    .reg_act = TRUE,\
    .operation = FALSE,\
    .reg_idx = 0xFFFF,\
    .cyc_idx = 0xFFFF,\
}\

static void hm_get_ident(T_HM_SCHEDULER *sched);

static void hm_start(T_HM_SCHEDULER *sched);
static void hm_start_new_cmd(T_HM_SCHEDULER *sched);
static void hm_handle_response(T_HM_SCHEDULER *sched);

EXPORT_DATA
#include "da_hm.h"

  NO_INIT HART_CMD_WAIT            HM_acyc;
  u8 HM_acyc_result;
  NO_INIT USIGN8                   HART_result;

IMPORT_DATA

LOCAL_DATA
//lint -estring(457,appl_check_hm_state) Write from a single context enforced
  STATIC NO_INIT  USIGN8            hm_state;
  STATIC NO_INIT  USIGN8 Atomic_           hm_user_task_id; //Set to non-255 on connect once (see hm_connect)
  static  T_ASYNC_COMMAND   hm_command;
  STATIC NO_INIT  USIGN8            send_buff [MAX_HART_TELEGRAMM_LEN];
  STATIC NO_INIT  USIGN8            receive_buff [MAX_HART_TELEGRAMM_LEN];

/* We are not shy to say that HART_db, just like HART_data_base, is
  pre-inititialized and never changed again, i.e. const. That takes care of the
  order of initialization and, incidentally, makes hm_init_db()
  extraneous so it is removed
*/
extern const HART_DB HART_data_base;
static const HART_DB *const HART_db = &HART_data_base;

//  STATIC NO_INIT  USIGN8            hm_timer_id;
static T_HM_SCHEDULER    HM_sched = SCHED_DEFAULT;
  STATIC NO_INIT  USIGN32           HM_hart_dev_id;


#define USE_FIRSTTIME 0
#if USE_FIRSTTIME
  STATIC NO_INIT  BOOL              first_time;
#endif

#include "da_def.h"


/* ------------------------------------------------------------------------ */
/* --- The following variables are used for debugging only ---------------- */
/* ------------------------------------------------------------------------ */

#ifdef HM_TRACE
  typedef struct {
    USIGN32         curr_time;
    USIGN16         diff_time;
    USIGN8          cmd;
    USIGN8          dummy;
  } T_HM_TRACE;

  T_HM_TRACE        TimeTrace[100];         /* use first 50 entries for startup     */
  USIGN16           TimeIdx = 0;            /* next 50 entries as ringbuffer        */
  USIGN32           Trace_num_cmds = 0;
#endif /* HM_TRACE */

const USIGN16       HART_baudrates[] =
                        {1200, 2400, 4800, 9600, 19200, 38400};

#ifdef _DEBUG
  USIGN8    last_hm_command;
  USIGN32   sent_event_cnt = 0;
  USIGN32   receive_event_cnt = 0;
#endif /* _DEBUG */



/******************************************************************************/

FUNCTION PUBLIC VOID hm_connect
  (
    IN USIGN8   task_id
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
    Connects the application task to the HART master. The HART master will
    send all events to the task as specified by 'task_id'

PARAMETERS:
    task_id:        ID of task, the HM shall send events to

GLOBALS_AFFECTED:
    hm_user_task_id

RETURN_VALUES:
    none

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
    hm_user_task_id = task_id;

    return;
} /* FUNCTION hm_connect */

//Enabled by default
static T_HM_ACT cyc_active_req = ACTIVATE;
static T_HM_ACT config_update_active_req = ACTIVATE;

void HART_set_active(T_HM_ACT cyc_active, T_HM_ACT config_update_active)
{
    osif_disable_all_tasks();
    cyc_active_req = cyc_active;
    config_update_active_req = config_update_active;
    osif_set_event(HM_TASK_ID, OS_IF_EVENT_TIMER);   /* wake up HART scheduler to finish processing */
    osif_enable_all_tasks();
}


static void HART_set_active_handler(T_HM_SCHEDULER *sched)
{

    osif_disable_all_tasks();
    T_HM_ACT cyc_active = cyc_active_req;
    cyc_active_req = UNCHANGED;
    T_HM_ACT config_update_active = config_update_active_req;
    config_update_active_req = UNCHANGED;
    osif_enable_all_tasks();

    if ( cyc_active == DEACTIVATE )
    {
        sched->cyc_shutdown = TRUE;
        if ( HART_db->cycl_min_period != 0 )
        {
            //osif_stop_timer (hm_timer_id);
        }
    }
    else if ( cyc_active == ACTIVATE )
    {
        sched->cyc_shutdown = FALSE;                  /* Simulate timer event to activate     */
        //osif_set_event(HM_TASK_ID, OS_IF_EVENT_TIMER);   /* HART scheduler                       */
    }
    else
    {
        /* do nothing */
    }

    if ( config_update_active == DEACTIVATE )
    {
        sched->reg_act = FALSE;
    }
    else if ( config_update_active == ACTIVATE )
    {
        sched->reg_act = TRUE;                        /* Simulate timer event to activate     */
        //osif_set_event(HM_TASK_ID, OS_IF_EVENT_TIMER);   /* HART scheduler                       */
    }
    else
    {
        /* do nothing */
    }
} /* FUNCTION HART_set_active */





FUNCTION GLOBAL USIGN32 HART_get_dev_id (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  The function returns the HART device identifier, which
  was returned by CMD0.

PARAMETERS:

  None

GLOBALS_AFFECTED:

  None

RETURN_VALUES:

  HART device id
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    return (HM_hart_dev_id);

}


static USIGN8 err_counter;
static void hmtask_ProcessErrorEvent(void)
{
    T_HM_SCHEDULER *sched = &HM_sched;
      hm_call_appl_funct.a_of_set_HART_status (NO_HART_COMM);

      sched->operation = FALSE;

      if (sched->state == HM_ACYCLIC)
      {
        if ( hm_user_task_id != 255 )
        {
          HM_acyc_result = HART_result;
          osif_set_event(hm_user_task_id, HART_ACY_CMD_END_EVENT); /* user task should not wait for ever */
        }
      }

      if ( (err_counter < ERROR_COUNTER_LIMIT)
         #if defined (PROTOCOL_FF)
           && (hm_call_appl_funct.a_of_check_restart_flag() == FALSE)
         #endif
         )
      {
        err_counter++;

        /* try with next command */
        hm_start_new_cmd(sched);
      }
    else
    {
        #if defined (PROTOCOL_FF)
        hm_call_appl_funct.a_of_reset_restart_flag ();
        #endif
        osif_set_event(HM_TASK_ID, HART_START_EVENT); //restart the thing
    }
}

typedef struct hm_error_instrum_t
{
    u16 count;
    u8 cmd_expected;
    u8 cmd_received;
} hm_error_instrum_t;

hm_error_instrum_t hm_error_instrum =
{
    .count = 0U,
    .cmd_expected = 255U,
    .cmd_received = 255U,
};

static void hmtask_ProcessMessage(void)
{
    T_HM_SCHEDULER *sched = &HM_sched;
    err_counter = 0;

    hm_call_appl_funct.a_of_set_HART_status (HART_COMM_OK);

    /* first give the FDEV response on last command */
#if 0
    if((received_cmd == hm_command.cmd) && (hm_command.out_buf != NULL))
    {
        /*Did we receive what we asked for? Doesn't cover burst but we don't have it
        With burst, this test must be pushed down!!!
        */
        hm_handle_response(sched);
    }
    else
    {
        /* This error condition may conceivably happen because of subtle timing
        differences between FFP and APP coming out of reset
        */
        hm_error_instrum.count++;
        hm_error_instrum.cmd_expected = hm_command.cmd;
        hm_error_instrum.cmd_received = received_cmd;
    }
#else
        hm_handle_response(sched);
#endif

    #if defined (PROTOCOL_FF)
    if(hm_call_appl_funct.a_of_check_restart_flag () == TRUE)
    {
        hmtask_ProcessErrorEvent();
    }
    else
    #endif
    {
        /* find and start new command */
        hm_start_new_cmd(sched);
    }
}

static USIGN16 hm_SetBaudrate(void)
{
    //In case of flash fault, configure an incorrect speed to guarantee error
    USIGN16  baudrate;
    USIGN16     result = HART_ERROR;
    if(error_IsFault(FAULT_FW_CHECKSUM))
    {
        baudrate = WRONG_HM_BAUDRATE;
    }
    else
    {
        baudrate = HART_baudrates[5];
        result = HART_OK;
    }

    hw_hm_set_baudrate(baudrate);
    return result;
}


void task_hm_base_routine(T_EVENT  event)
{
    T_HM_SCHEDULER *sched = &HM_sched;

    if (event & OS_IF_EVENT_SYSSTART)  /* system start event is received */
    {
        /* Init HART master using slave adress 0 ------------------------------ */
    //MN_ENTER_CRITICAL();
        HART_Init (0);

    //MN_EXIT_CRITICAL();
        hm_state   = HM_RUN; //now will try with last known id - was HM_INIT_STATE;
        err_counter = 0;
        hm_user_task_id = 255;
        sched->cyc_shutdown = FALSE;    /* enable cyclic traffic by default */
#if USE_FIRSTTIME
        first_time = TRUE;
#endif
        (void)hm_SetBaudrate();
    }

    if (event & HART_ERROR_EVENT)  /* communication error event is received */
    {
        hmtask_ProcessErrorEvent();
    }

    if (event & HART_RECEIVE_END_EVENT) /* HART commando is just received */
    {
        //u8 received_cmd = hm_ProcessPacket();
        //hmtask_ProcessMessage(received_cmd);
        hm_ProcessPacket();
        hmtask_ProcessMessage();
        //event &= ~HART_GAPTIMER_EVENT; //don't care how we got the frame
    }

    if(event & HART_GAPTIMER_EVENT)
    {
        hm_ProcessTimerEvents();
    }

    if (event & OS_IF_EVENT_TIMER)     /* HART min. time for cyclic period has expired */
    {
        /* AK: This now can be a timer or a simulated timer for (de-activation)
        */
        HART_set_active_handler(sched);

#ifdef HM_TRACE
        LA_HIGH(4);
#endif /* HM_TRACE */
        if ( sched->cyc_shutdown != TRUE )
        {
            sched->cyc_start = TRUE;
        }
        hm_start_new_cmd(sched);
#ifdef HM_TRACE
        LA_LOW(4);
#endif /* HM_TRACE */
    }

  if (event & OS_IF_EVENT_REQRES)    /* Request for acyclic HART communication */
  {
        sched->acyc_act = TRUE;
        hm_start_new_cmd(sched);
  }

    //The order of event processing matters
    if (event & HART_START_EVENT)
    {
        //FUTURE (and to move up) hm_init();        /* Initialize HART master                            */
        hm_state   = HM_INIT_STATE;
        hm_get_ident(sched);        /* will now retrigger and return if HART communication is not established */
        //HART_Init (0);
        //hm_start_new_cmd(sched);

    }

  /* Event validity used to be assrted here. No longer needed with TaskRunner.
  Besides, this task is happy with any event code now
  */
} /* FUNCTION task_hm_base_routine */

/** \brief Attempts to connect to APP and start the schedule on success.
On failure, retriggers HART error event
\param sched - a pointer to the scedule to run
*/
static void hm_get_ident(T_HM_SCHEDULER *sched)
{
    USIGN8      buf_size;
    USIGN16     result = hm_SetBaudrate();
#if 0
    USIGN8      buf[32];
#else
    /* The original sin is the short buffer. The problem with it (resulting in
    bug 26934) is that when we try to receive, APP may already be something else
    That something can be rather long, resulting in buffer overrun and, it being
    automatic, in stack corruption.
    I made it longer, and, because it is large, static, so stack no longer goes
    bad
    */
    static USIGN8      buf[MAX_HART_TELEGRAMM_LEN];
#endif //0

    /* HART_db initialization used to be here, but it is too late to be done here.
       Now HART_db is const and doesn't need init
    */

    /* We no longer loop with "while (init_successful == FALSE)"
    Instead, on error we retrigger error event to get here again in due course.
    This fixes blocking of FF link communication (and other tasks) in case of
    HART problems, whether intermittent or intentional (e.g. flash selftest or
    a test case during development).

    This changes behavior during start-up. Since start-up waits for a valid
    device id, the remedy is to eliminate FirstTime condition test
    */
    if(result == HART_OK)
    {
        buf_size = sizeof (buf);
        result = HART_send_cmd0 (buf, &buf_size);
    }

    if (result == HART_OK)
    {
            /* Catch pending events */
            /*---------------------*/
        osif_clear_event (HM_TASK_ID, HART_RECEIVE_END_EVENT);
        osif_clear_event (HM_TASK_ID, HART_ERROR_EVENT);

        /* Decode HART device id */
        /*-----------------------*/
        HM_hart_dev_id = buf[13];
        HM_hart_dev_id += ((USIGN32) buf[12]) * 0x100UL;
        HM_hart_dev_id += ((USIGN32) buf[11]) * 0x10000UL;

        if (hm_call_appl_funct.a_of_set_dev_id != NULL)
        {
            hm_call_appl_funct.a_of_set_dev_id (HM_hart_dev_id);
        }
        HART_Init(0);
                hm_state   = HM_RUN; //now will try with last known id - was HM_INIT_STATE;

        hm_start(sched);
    }
    else
    {
        //retrigger an error event to repeat in due time
        /*DO NOT! let other pieces run, or other pieces will run unprepared!!!
        OS_Delay(200);
        */
        osif_set_event (HM_TASK_ID, HART_START_EVENT);
    }
} /* FUNCTION hm_get_ident */


static void hm_start(T_HM_SCHEDULER *sched)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

  To change the priority of hm task.

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY
#ifdef HM_TRACE
  memset (TimeTrace, 0, sizeof(TimeTrace));
  TimeIdx = 0;
#endif /* HM_TRACE */

  //osif_stop_timer(hm_timer_id);
  //osif_clear_event(HM_TASK_ID,OS_IF_EVENT_TIMER);

  *sched = (T_HM_SCHEDULER)SCHED_DEFAULT;

  osif_set_event(HM_TASK_ID,OS_IF_EVENT_TIMER); //nudge it to run
  hm_start_new_cmd(sched);

  return;

} /* FUNCTION hm_start */




static void hm_start_new_cmd(T_HM_SCHEDULER *sched)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

    Find and start new command. If last command was acyclic, then the next
  command should be cyclic.

------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    if ( sched->operation == TRUE )
    {
        return;
    }
    sched->operation = TRUE;

#ifdef HM_TRACE
  TimeTrace[TimeIdx].curr_time = OS_GetTime32();
  TimeTrace[TimeIdx].diff_time = 0;
  TimeTrace[TimeIdx].cmd = (USIGN8) 0x255u;
#endif /* HM_TRACE */

    /* HART scheduler state machine */
    /*------------------------------*/
  switch (sched->state)
  {
    case HM_IDLE:
        if ( (sched->cyc_act == TRUE) || (sched->cyc_start == TRUE) )
        {
            sched->cyc_act = TRUE;
            sched->state = HM_CYCLIC;
        }
        else if ( sched->acyc_act == TRUE )
        {
            sched->state = HM_ACYCLIC;
            sched->acyc_act = FALSE;
        }
        else if ( sched->reg_act == TRUE )
        {
            sched->state = HM_REGULAR;
        }
        /* else keep HM_IDLE */
        break;

    case HM_REGULAR:
        if ( (sched->cyc_act == TRUE) || (sched->cyc_start == TRUE) )
        {
            sched->cyc_act = TRUE;
            sched->state = HM_CYCLIC;
        }
        else if ( sched->acyc_act == TRUE )
        {
            sched->state = HM_ACYCLIC;
            sched->acyc_act = FALSE;
        }
        else if ( sched->reg_act == FALSE )
        {
            sched->state = HM_IDLE;
        }
        /* else keep HM_REGULAR */
        break;

    case HM_ACYCLIC:
        if ( (sched->cyc_act == TRUE) || (sched->cyc_start == TRUE) )
        {
            sched->cyc_act = TRUE;
            sched->state = HM_CYCLIC;
        }
        else if ( sched->reg_act == TRUE )
        {
            sched->state = HM_REGULAR;
        }
        else if ( sched->acyc_act == TRUE )
        {
            sched->state = HM_ACYCLIC;
            sched->acyc_act = FALSE;
        }
        else
        {
            sched->state = HM_IDLE;
        }
        /* else keep HM_ACYCLIC */
        break;

    case HM_CYCLIC:
        if ( sched->acyc_act == TRUE )
        {
            sched->state = HM_ACYCLIC;
            sched->acyc_act = FALSE;
        }
        else if ( (sched->reg_act == TRUE) && (sched->cyc_idx == (HART_db->cyc_cmd_list_length-1)) )
        {
            sched->state = HM_REGULAR;
        }
        else if ( (sched->cyc_act == FALSE) && (sched->cyc_start == FALSE) )
        {
            sched->state = HM_IDLE;
        }
        /* else keep HM_CYCLIC */
        break;

  } /* end switch */


    /* HART scheduler actions */
    /*------------------------*/
  HART_InitAsyncCommand(&hm_command);
  switch (sched->state)
  {
    case HM_IDLE:
            /* No action to be done in IDLE state */
            /*------------------------------------*/
        sched->operation = FALSE;
        break;

    case HM_REGULAR:
        sched->reg_idx++;

            /* Check for last command in list */
            /*--------------------------------*/
        if ( sched->reg_idx == (HART_db->regular_cmd_list_length-1) )
        {
          /* needed actions to complete the Init phase */
          if ( hm_state == HM_INIT_STATE )
          {
            /* cyclic communication has to be started when cyc_shutdown = FALSE */
            if ( sched->cyc_shutdown != TRUE )
            {
                sched->cyc_act = TRUE;    /* start cyclic traffic */
            }

            hm_state = HM_RUN;              /* HART Master transition to RUN state */
          }

          /* regular list has to be updated cyclically when keep_regular = TRUE */
          if ( HART_db->keep_regular != TRUE )
          {
            sched->reg_act = FALSE;       /* Terminate regular traffic if requested   */
          }
        }
        else if ( sched->reg_idx >= HART_db->regular_cmd_list_length )
        {
          sched->reg_idx = 0;             /* Last command in list already processed, start with first one again */
        }

        /* fill the HART command */
        hm_command.cmd = HART_db->regular_cmd[sched->reg_idx];
        hm_command.in_buf  = send_buff;
        hm_command.out_buf = receive_buff;
        hm_call_appl_funct.a_of_handle_HART_cmd
            (hm_command.cmd, SEND,
            hm_command.in_buf, (USIGN8 *)&hm_command.in_len, hm_command.out_buf, 0);
        break;

    case HM_ACYCLIC:
        hm_command.cmd     = HM_acyc.cmd;
        hm_command.in_len  = HM_acyc.send_length;
        hm_command.in_buf  = HM_acyc.send_buff;
        hm_command.out_buf = HM_acyc.receive_buff;
        break;

    case HM_CYCLIC:
        sched->cyc_idx++;

            /* Check if cyclic list has been processed completely */
            /*----------------------------------------------------*/
        if ( sched->cyc_idx >= HART_db->cyc_cmd_list_length )
        {
          sched->cyc_idx = 0;             /* continue with start of list */

#if USE_FIRSTTIME
/*
EXPLANATION:
1. We don't do anything on DATA_INIT_FINISHED. Instead, we manipulate status of variables
2. We don't use HM_TASK_START_PRIO (a) for simplicity and (b) it may block things if APP is not ready
*/
          /* needed actions to be done only after cold start of device */
          if ( first_time )
          {
            /* Indicate to application that data base is synchronized successfully */
            hm_call_appl_funct.a_of_set_HART_status (DATA_INIT_FINISHED);

            /* Change from startup prio to normal operation prio ---------- */
            osif_create_task (HM_TASK_ID, HM_TASK_PRIO, NULL, 0);

            first_time = FALSE;
          }
#endif
        }

        /* needed actions if a dedicated time period between cyclic command list executions is defined */
        if ( (HART_db->cycl_min_period != 0) || (sched->cyc_shutdown == TRUE) )
        {
          /* needed actions at first element of cyclic command list */
          if ( (sched->cyc_idx == 0) )
          {
            sched->cyc_start = FALSE;

            if ( sched->cyc_shutdown != TRUE )
            {
              /* start time the HART Master has to wait before next execution of cyclic command list */
              //osif_start_timer (hm_timer_id, (USIGN32) HART_db->cycl_min_period, FALSE);
            }

            #ifdef HM_TRACE /* -------------------------------------------- */
            {
              USIGN32 time_diff;
              static USIGN32 prev_time = 0;

              time_diff = TimeTrace[TimeIdx].curr_time - prev_time;
              if (TimeIdx > 20)
              {
              //   _ASSERT(time_diff < 300);
              }
              TimeTrace[TimeIdx].diff_time = (USIGN16) time_diff;
              prev_time = TimeTrace[TimeIdx].curr_time;

            }
            #endif /* HM_TRACE -------------------------------------------- */

          }
          /* needed actions at last element of cyclic command list */
          if ( sched->cyc_idx == (HART_db->cyc_cmd_list_length-1) )
          {
            sched->cyc_act = FALSE;
          }
        }

        /* fill the HART command */
        hm_command.cmd = HART_db->cyc_cmd[sched->cyc_idx];
        hm_command.in_buf  = send_buff;
        hm_command.out_buf = receive_buff;
        hm_call_appl_funct.a_of_handle_HART_cmd
            (hm_command.cmd, SEND,
            hm_command.in_buf, (USIGN8 *)&hm_command.in_len, hm_command.out_buf, 0);
        break;

  } /* end switch */


#ifdef HM_TRACE
  LA_HIGH(5);
  Trace_num_cmds++;
  TimeTrace[TimeIdx].cmd = hm_command.cmd;
  if ( ++TimeIdx >= (sizeof (TimeTrace) / sizeof (*TimeTrace)) )
  {
    TimeIdx = 50;
  }
#endif /* HM_TRACE */

    /* Execute HART command */
    /*----------------------*/
    if(sched->operation != FALSE)
    {
        HART_result = HART_Command_non_block(&hm_command);
    }

#ifdef HM_TRACE
  LA_LOW(5);
#endif /* HM_TRACE */

    return;

} /* FUNCTION hm_start_new_cmd */




static void hm_handle_response(T_HM_SCHEDULER *sched)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION



------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES


FUNCTION_BODY

    if (sched->state == HM_ACYCLIC) /* last cmd was acyclic */
    {
        if ( hm_user_task_id != 255 )
        {
          HM_acyc_result = HART_result;
          osif_set_event(hm_user_task_id, HART_ACY_CMD_END_EVENT);
        }
    }
    else
    {
        hm_call_appl_funct.a_of_handle_HART_cmd
            (hm_command.cmd, RECEIVE,
            hm_command.in_buf, (USIGN8 *)&hm_command.in_len, hm_command.out_buf, hm_command.out_len);
    }

    sched->operation = FALSE;
    return;

} /* FUNCTION hm_handle_response */



#if CHECK_HM_STATE
FUNCTION GLOBAL USIGN8 appl_check_hm_state()
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION



------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  return(hm_state);

}
#endif
