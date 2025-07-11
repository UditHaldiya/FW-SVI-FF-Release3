/*
Copyright 2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hm_api.h
    \brief High-level API for simplified IPC "HART master".
    This is a derivative work of Softing source whose copyright notice appears below

    CPU: Any

    OWNER: AK

    \ingroup HART
*/
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

#ifndef HM_API_H_
#define HM_API_H_

#include "errcodes.h"

/* --- HART communication state defines --- */

#define HART_COMM_OK                0x00
#define DATA_INIT_FINISHED          0x01       /* only at startup */
#define CONFIG_UPDATE_FINISHED      0x02
#define NO_HART_COMM                0xFF

#define SEND                        0x00
#define RECEIVE                     0xFF

typedef struct HART_DB
{
  const USIGN8 *    cyc_cmd;                    /* List of high prior (cyclic) commands */
  const USIGN8 *    regular_cmd;                /* List of low prior (regular) commands */
  USIGN8            cyc_cmd_list_length;        /* Length of cyc_cmd list     */
  USIGN8            regular_cmd_list_length;    /* Length of regular_cmd list */
  USIGN16           cycl_min_period;            /* Min period for high prior (cyclic) traffic in msec units  */
  USIGN32           startup_timeout;            /* Max time the HART master is waiting for the
                                                   HART device before declaring it as not available
                                                   - in msec units                              */
  BOOL              keep_regular;               /* Keep regular traffic active after init phase */
} HART_DB;

typedef enum T_HM_ACT
{
  DEACTIVATE,
  UNCHANGED,
  ACTIVATE
} T_HM_ACT;


FUNCTION_DECLARATIONS

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*    Application Functions Called by the HART Master                       */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

  typedef struct
  {
    GLOBAL VOID      (* a_of_handle_HART_cmd)   (USIGN8, USIGN8, USIGN8 *, USIGN8 *, USIGN8 *, USIGN16);
    GLOBAL HART_DB * (* a_of_get_HART_database) (USIGN8, USIGN32);
    GLOBAL VOID      (* a_of_set_HART_status)   (USIGN8);
    GLOBAL VOID      (* a_of_set_dev_id)        (USIGN32);
    #if defined (PROTOCOL_FF)
    GLOBAL BOOL     (* a_of_check_restart_flag) (VOID);
    GLOBAL VOID     (* a_of_reset_restart_flag) (VOID);
    #endif /* PROTOCOL_FF */
  }
    T_HM_CALL_APPL_FUNCT;



/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*    HART Master Functions to be called by the Application                  */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

FUNCTION GLOBAL VOID HART_set_active
  (
    IN T_HM_ACT     cyc_active,
    IN T_HM_ACT     config_update_active
  );


FUNCTION GLOBAL USIGN32 HART_get_dev_id (VOID);

#ifdef NDEBUG
#define INSTRUM_HM_TIMERS OPTION_ON //OPTION_ON is optional, could be OPTION_OFF
#else
#define INSTRUM_HM_TIMERS OPTION_ON //OPTION_ON is desirable
#endif

#if INSTRUM_HM_TIMERS == OPTION_ON
typedef struct adaptimers_t
{
    u16 time_send; //!< how long it takes to transmit a message
    u16 time_wait; //!< how long (in systicks) it takes for a response to begin coming
    u16 time_receive; //!< how long (in systicks) it takes for a response to fully arrive
    //u16 CheckWord; //perhaps, future
} adaptimers_t;

#if 0
extern void adaptimers_Get(adaptimers_t *dst);
extern ErrorCode_t adaptimers_Set(const adaptimers_t *src);
#endif

//Instrumentation
extern void adaptimers_ReadAndReset(adaptimers_t *dst);
#endif

#define INSTRUM_IPC OPTION_ON

typedef struct ipcstat_t
{
    u16 senddiff;
    u16 rcvdiff;
    u16 roundtrip;
    u16 wild;
    u16 lost;
    u16 reinits;
    u32 total;
} ipcstat_t;

extern void instrum_ipc_ReadAndReset(ipcstat_t *dst);
#if INSTRUM_IPC == OPTION_ON
extern void instrum_ipc_PostReceive(void);
extern void instrum_ipc_PreSend(void);
extern void instrum_ipc_CountReinits(void);

#else
#define instrum_ipc_PostReceive()
#define instrum_ipc_PreSend()
#define instrum_ipc_CountReinits()
#endif

typedef struct APPHeader_t
{
    u8 appheader[6]; //!< IPC HART header to talk to APP
    u16 CheckWord;
} APPHeader_t;

extern const APPHeader_t *hm_GetAPPHeader(APPHeader_t *dst);
extern ErrorCode_t hm_SetAPPHeader(const APPHeader_t *src);
UNTYPEACC(hm_SetAPPHeader, hm_GetAPPHeader);

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*    Global Variables                                                      */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

  extern const T_HM_CALL_APPL_FUNCT   hm_call_appl_funct;
#include "da_def.h"

#endif /* HM_API_H_ */
