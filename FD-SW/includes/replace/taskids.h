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
typedef u8 taskid_t;
/* EEP task: contains the asynchrounous part of the EEP interface --------- */
#define EEP_TASK_ID              0
/* Application task(s)                                                       */
#define APPL_TASK_ID             1
/* Function Block execution task(s)                                         */
#define FB_TASK_ID               2
/* Highest prior Watchdog task                                            */
#define FDC_WD_TASK_ID        3

#if defined (PROTOCOL_FF)
#if defined (DOWNLOAD_DEVICE) || defined (SW_DOWNLOAD) || defined (HART_MASTER) || defined (MODBUS_MASTER)
#define FIRST_PROT_TASK_ID      (FB_TASK_ID + 3)
#else
#define FIRST_PROT_TASK_ID      (FB_TASK_ID + 2)
#endif /* DOWNLOAD_DEVICE */
  /* FDC task: FAL + FBS -------------------------------------------------- */
  #define FDC_TASK_ID           FIRST_PROT_TASK_ID
  /* Send MVC task: part of FBS ------------------------------------------- */
  #define MVC_TASK_ID           (FIRST_PROT_TASK_ID + 2)
   /* BGD task: background actions ----------------------------------------- */
  #define BGD50_TASK_ID         (FIRST_PROT_TASK_ID + 3)
  #define BGD_TASK_ID           (FIRST_PROT_TASK_ID + 4)
#ifdef LINK_MASTER
  /* LAS task: LAS part of the DLL ---------------------------------------- */
  /* LAS task: LAS part of the DLL ---------------------------------------- */
  /* --- which is not executed on interrupt level ------------------------- */
  #define LAS_TASK_ID           (FIRST_PROT_TASK_ID + 5)
  #define MAX_TASK_ID1           LAS_TASK_ID
#else
  #define MAX_TASK_ID1           BGD_TASK_ID
#endif /* LINK_MASTER */

  /* SUBSCRIBER task: subscriber part of FAL + FBS ------------------------ */
  #define SBSCR_TASK_ID         (FIRST_PROT_TASK_ID + 1)
#endif /* Protocol type */


#if defined (HART_MASTER)
/*--------------------------------------------------------------------------*/
/* HART Master task                                                         */
/*--------------------------------------------------------------------------*/
#define HM_TASK_ID              4
#elif defined (MODBUS_MASTER)
/*--------------------------------------------------------------------------*/
/* MODBUS Master task                                                       */
/*--------------------------------------------------------------------------*/
#define MODB_TASK_ID            4
#endif /* HART_MASTER , MODBUS_MASTER */

#define TASKID_PROCESS (EEP_TASK_ID) //replace
#define MAX_TASK_ID MAX_TASK_ID1

//Compatibility
#define TASKID_CONTROL FB_TASK_ID

//------------------- watchdog part ----------------------------
//lint -emacro(641, WD_MONITOR_TASKS_ALWAYS, WD_MONITOR_TASKS_NEVER) undeserved - enum on RHS of shift
#define WD_MONITOR_TASKS_ALWAYS ((1U << BGD_TASK_ID) | (1U << EEP_TASK_ID))
#define WD_MONITOR_TASKS_NEVER (1U << APPL_TASK_ID)
//---------------------------------------------------------------

#endif //TASKIDS_H_
/* This line marks the end of the source */
