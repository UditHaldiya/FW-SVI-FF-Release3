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

FILE_NAME          hm.h


DESCRIPTION       Error codes, status and etc. used by hart interface

=========================================================================== */

#ifndef HM_H_
#define HM_H_

#include <rtos.h>

/*--- HART interace error codes ---*/

#define HART_OK                           0
#define HART_ERROR                        1

extern u8 HM_acyc_result; //move out of HART_CMD_WAIT for thread analysis

enum T_ASYNC_COMMAND_STATE
{
    ASYNC_COMMAND_IDLE,
    ASYNC_COMMAND_EXECUTE,
    ASYNC_COMMAND_DONE,
    ASYNC_COMMAND_FAILED
};

typedef struct T_ASYNC_COMMAND
{
    enum T_ASYNC_COMMAND_STATE state;       /* dont touch this field! */
    USIGN8 cmd;
    USIGN16 in_len;
    USIGN16 out_len;
    BYTE   *in_buf;
    BYTE   *out_buf;
} T_ASYNC_COMMAND;

extern USIGN16 HART_send_cmd0 (void);
extern VOID HART_InitAsyncCommand(T_ASYNC_COMMAND *command);
extern OS_TASK_EVENT hart_TxRx(T_ASYNC_COMMAND *command);
extern OS_TASK **hm_set_cmd_in_acyc_list(USIGN8 cmd, USIGN8 *send_buff, USIGN8 send_length, USIGN8 *receive_buff);


#endif /* HM_H_ */

