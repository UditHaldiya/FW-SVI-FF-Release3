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

#include "mnassert.h"
#include "uartconfig.h"


#define HM_INIT_STATE  0x00
#define HM_RUN         0x01

#define ERROR_COUNTER_LIMIT    20 //5 must be much greater than the unrolled schedule
//#define CMD0_BUF_SIZE         32

typedef enum
{
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
static void hm_find_new_cmd(T_HM_SCHEDULER *sched, T_ASYNC_COMMAND *hm_command);

typedef struct HART_CMD_WAIT
{
      USIGN8  cmd;
      //USIGN8  result;
      USIGN8  send_length;
      USIGN8 *send_buff;
      USIGN8 *receive_buff;
      OS_TASK *acyc_sender;
} HART_CMD_WAIT;

static HART_CMD_WAIT HM_acyc;
u8 HM_acyc_result;


/** \brief  The function is used to fill the HM_acyc - structure. The function is called
  by function HART_acyc_cmd().
\param cmd               Command to execute.
\param   send_buff         Pointer to the send buffer.
\param   send_length       Length of the data in the send buffer.
\param   receive_buff      Pointer to the receive buffer.
\return a pointer to the caller task
*/
OS_TASK **hm_set_cmd_in_acyc_list(USIGN8 cmd, USIGN8 *send_buff, USIGN8 send_length, USIGN8 *receive_buff)
{
    MN_ASSERT(HM_acyc.acyc_sender == NULL); //or someone snuck behind mutex
    HM_acyc.send_buff = send_buff;
    HM_acyc.send_length = send_length;
    HM_acyc.receive_buff = receive_buff;
    HM_acyc.cmd = cmd;
    HM_acyc.acyc_sender = OS_GetpCurrentTask();
    return &HM_acyc.acyc_sender;
}


IMPORT_DATA

LOCAL_DATA
//lint -estring(457,appl_check_hm_state) Write from a single context enforced
  STATIC NO_INIT  USIGN8            hm_state;
  STATIC NO_INIT  USIGN8            send_buff [MAX_HART_TELEGRAMM_LEN];
  STATIC NO_INIT  USIGN8            receive_buff [MAX_HART_TELEGRAMM_LEN];

/* We are not shy to say that HART_db, just like HART_data_base, is
  pre-inititialized and never changed again, i.e. const. That takes care of the
  order of initialization and, incidentally, makes hm_init_db()
  extraneous so it is removed
*/
extern const HART_DB HART_data_base;
static const HART_DB *const HART_db = &HART_data_base;

static T_HM_SCHEDULER    HM_sched = SCHED_DEFAULT;


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

#ifdef _DEBUG
  USIGN8    last_hm_command;
  USIGN32   sent_event_cnt = 0;
  USIGN32   receive_event_cnt = 0;
#endif /* _DEBUG */



/******************************************************************************/

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

static USIGN8 err_counter;

void hmtask_SysStart(void)
{
    /* Init HART master using slave adress 0 ------------------------------ */
    HART_Init ();

    hm_state   = HM_RUN; //now will try with last known id - was HM_INIT_STATE;
    err_counter = 0;

    T_HM_SCHEDULER *sched = &HM_sched;
    HART_set_active_handler(sched);
    sched->cyc_shutdown = FALSE;    /* enable cyclic traffic by default */
}

void task_hm_base_routine(T_EVENT  event)
{
    T_HM_SCHEDULER *sched = &HM_sched;

    if( (event & OS_IF_EVENT_SYSSTART) != 0)  /* system start event is received */
    {
        // moved content to hmtask_SysStart() to avoid startup priorities conflict
        //hmtask_SysStart();
    }
//    for(;;){
    if( (event & HART_ERROR_EVENT) != 0)  /* communication error event is received */
    {
        ;
    }

    if( (event & HART_RECEIVE_END_EVENT) != 0) /* HART commando is just received */
    {
        ;
    }

    if( (event & OS_IF_EVENT_TIMER) != 0)     /* HART min. time for cyclic period has expired */
    {
        /* AK: This now can be a timer or a simulated timer for (de-activation)
        */
        HART_set_active_handler(sched);

        if ( sched->cyc_shutdown != TRUE )
        {
            sched->cyc_start = TRUE;
        }
    }

    //The order of event processing matters
    if( (event & HART_START_EVENT) != 0)
    {
        //FUTURE (and to move up) hm_init();        /* Initialize HART master                            */
        hm_state   = HM_INIT_STATE;
        hm_get_ident(sched);        /* will now retrigger and return if HART communication is not established */
        //HART_Init (0);
    }

    if( (event & OS_IF_EVENT_REQRES) != 0)   /* Request for acyclic HART communication */
    {
        sched->acyc_act = TRUE;
    }

    T_ASYNC_COMMAND   hm_command;
    /* find and start new command */
    hm_find_new_cmd(sched, &hm_command);
    /* Execute HART command */
    if(sched->operation == FALSE)
    {
        OS_Delay(20*5); //let others run
        event = 0;
    }
    else
    {
        event = hart_TxRx(&hm_command);
        sched->operation = FALSE;
        u8 comm;
        if((event & HART_RECEIVE_END_EVENT) != 0)
        {
            //Success
            comm = HART_COMM_OK;
            err_counter = 0;
        }
        else
        {
            //Error of any kind
            err_counter++;
            comm = NO_HART_COMM;
        }
        hm_call_appl_funct.a_of_set_HART_status (comm);
        //Message handling
        if( (comm == HART_COMM_OK) && (sched->state != HM_ACYCLIC)) /* OK and cyclic or regular command*/
        {
            hm_call_appl_funct.a_of_handle_HART_cmd
                (hm_command.cmd, RECEIVE,
                hm_command.in_buf, (USIGN8 *)&hm_command.in_len, hm_command.out_buf, hm_command.out_len);
        }

        if (sched->state == HM_ACYCLIC) /* last cmd was acyclic */
        {
            if(comm == HART_COMM_OK)
            {
                HM_acyc_result = HART_OK;
            }
            else
            {
                HM_acyc_result = HART_ERROR;
            }
            OS_TASK *sender = HM_acyc.acyc_sender;
            MN_RT_ASSERT ( sender != NULL ); //Caller absolutely must register!
            OS_SignalEvent(HART_ACY_CMD_END_EVENT, sender);
            /*NOTE: We don't need to syswd_NotifyWatchdog() because
            the task which sent the command is already activated and now waiting
            */
        }
        //Scheduler handling
        if(
#if defined (PROTOCOL_FF)
            (hm_call_appl_funct.a_of_check_restart_flag() == TRUE) ||
#endif
                (err_counter >= ERROR_COUNTER_LIMIT)
         )
        {
#if defined (PROTOCOL_FF)
            hm_call_appl_funct.a_of_reset_restart_flag ();
#endif
            event = HART_START_EVENT; //restart the thing
        }

        sched->operation = FALSE;
    }

    /* This operation calls for endless loop but we'll employ
    for now an unused event to retrigger the task
    */
// } //
    event &= ~HART_RECEIVE_END_EVENT;
    if(event == 0)
    {
        event = OS_IF_EVENT_EEPROM; //need an unused to retrigger
    }
    osif_set_event(HM_TASK_ID, event); //re-post
}

/** \brief Attempts to connect to APP and start the schedule on success.
On failure, retriggers HART error event
\param sched - a pointer to the scedule to run
*/
static void hm_get_ident(T_HM_SCHEDULER *sched)
{
    err_counter = 0; //space the calls to this function
    /* HART_db initialization used to be here, but it is too late to be done here.
       Now HART_db is const and doesn't need init
    */

    /* We no longer loop with "while (init_successful == FALSE)"
    Instead, on error we retrigger error event to get here again in due course.
    This fixes blocking of FF link communication (and other tasks) in case of
    HART problems, whether intermittent or intentional (e.g. flash selftest or
    a test case during development).
    */
    u16 result = HART_send_cmd0(); //The only purpose is to "connect" i.e. to get device id

    if (result == HART_OK)
    {
        hm_state   = HM_RUN; //now will try with last known id - was HM_INIT_STATE;

        hm_start(sched);
    }
    else
    {
        //retrigger an error event to repeat in due time
        /*DO NOT! let other pieces run, or other pieces will run unprepared!!!
        OS_Delay(200);
        */
        //rely on the guardian - osif_set_event (HM_TASK_ID, HART_START_EVENT);
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

} /* FUNCTION hm_start */




/* \bried  Find new command. If last command was acyclic, then the next
  command should be cyclic.
\param sched - a pointer to scheduler
*/
static void hm_find_new_cmd(T_HM_SCHEDULER *sched, T_ASYNC_COMMAND *hm_command)
{
    if ( sched->operation == TRUE )
    {
        return;
    }
    sched->operation = TRUE;

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
        else
        {
            /*  keep HM_IDLE */
        }
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
        else
        {
            /*  keep HM_REGULAR */
        }
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
        else
        {
            /*keep HM_CYCLIC */
        }
        break;

    } /* end switch */


    /* HART scheduler actions */
    /*------------------------*/
  HART_InitAsyncCommand(hm_command);
  switch (sched->state)
  {
    case HM_IDLE:
#if 0
        //Nothing to send: Sleep and retrigger
        OS_Delay(50);
        osif_set_event(HM_TASK_ID, OS_IF_EVENT_TIMER);
        return;
#else
            /* No action to be done in IDLE state */
            /*------------------------------------*/
        sched->operation = FALSE;
        break;
#endif
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
        else
        {
            if ( sched->reg_idx >= HART_db->regular_cmd_list_length )
            {
              sched->reg_idx = 0;             /* Last command in list already processed, start with first one again */
            }
        }

        /* fill the HART command */
        hm_command->cmd = HART_db->regular_cmd[sched->reg_idx];
        hm_command->in_buf  = send_buff;
        hm_command->out_buf = receive_buff;
        hm_call_appl_funct.a_of_handle_HART_cmd
            (hm_command->cmd, SEND,
            hm_command->in_buf, (USIGN8 *)&hm_command->in_len, hm_command->out_buf, 0);
        break;

    case HM_ACYCLIC:
        hm_command->cmd     = HM_acyc.cmd;
        hm_command->in_len  = HM_acyc.send_length;
        hm_command->in_buf  = HM_acyc.send_buff;
        hm_command->out_buf = HM_acyc.receive_buff;
        break;

    case HM_CYCLIC:
        sched->cyc_idx++;

            /* Check if cyclic list has been processed completely */
            /*----------------------------------------------------*/
        if ( sched->cyc_idx >= HART_db->cyc_cmd_list_length )
        {
          sched->cyc_idx = 0;             /* continue with start of list */

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
        hm_command->cmd = HART_db->cyc_cmd[sched->cyc_idx];
        hm_command->in_buf  = send_buff;
        hm_command->out_buf = receive_buff;
        hm_call_appl_funct.a_of_handle_HART_cmd
            (hm_command->cmd, SEND,
            hm_command->in_buf, (USIGN8 *)&hm_command->in_len, hm_command->out_buf, 0);
        break;

    } /* end switch */


} /* FUNCTION hm_find_new_cmd */

