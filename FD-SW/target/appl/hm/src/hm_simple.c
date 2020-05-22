/*
Copyright 2016-2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hm_simple.c
    \brief Simplified HART messaging.
    This is a derivative work of Softing source whose copyright notice appears below

    CPU: Any ST Cortex-M3/M4, it looks like.

    OWNER: AK

    \ingroup HARTDLL
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

#include <keywords.h>   /* keyword defines */

#include <base.h>
#include <hw_if.h>
#include <hm_cfg.h>
#include <hm.h>

#include <stm32f10x_usart.h>
#include "hm_dma.h"
#include "hccheck.h"
#include <hm_api.h>
#include "crc.h"
#include "nvram.h"

#define USE_ASSERT 1
#if USE_ASSERT
#include "mnassert.h"
#else
#include "reset.h"
#endif

#include "faultpublic.h"

#include "uartconfig.h"

// ------------ Low-level primitives (DMA) Section -----------------------

// -- buffers etc. --
#define HDR_RESV      16
#define LENGTH_POS (RCV_PREAMBLES+3)      // preambles, DEL, ADR, CMD .. next is LEN
#define RCV_PREAMBLES 5
#define XMT_PREAMBLES 5
static MN_NO_INIT  BYTE dma_receiveBuffer[MAX_HART_TELEGRAMM_LEN+HDR_RESV+RCV_PREAMBLES];
static MN_NO_INIT  BYTE dmaTransmitBuffer[MAX_HART_TELEGRAMM_LEN+HDR_RESV+XMT_PREAMBLES];
static BYTE * const transmitBuffer = dmaTransmitBuffer + XMT_PREAMBLES;
static  BYTE * const receiveBuffer = dma_receiveBuffer + RCV_PREAMBLES;


// -- DMA interface --

#if INSTRUM_HM_TIMERS == OPTION_ON
// - Statistics -
static u32 timestamp;
static adaptimers_t current;
static adaptimers_t last;

void adaptimers_ReadAndReset(adaptimers_t *dst)
{
    MN_ENTER_CRITICAL();
        *dst = last;
    MN_EXIT_CRITICAL();
    MN_ENTER_CRITICAL();
        last.time_send = 0;
        last.time_wait = 0;
        last.time_receive = 0;
    MN_EXIT_CRITICAL();
}
#endif

// - DMA Receive -
static MN_NO_INIT  bool_t     payLdFlag;                           // false: receiving header; true: receiving payload
static MN_NO_INIT  USIGN32  lthBytePosn;                            // computed position of lenght octet in receive message - based on CMD 0 or some other
static MN_NO_INIT  USIGN8   rcvErrors;

/** \brief This function is called upon Terninal Count from DMA channel 6 which services
    the receive channel of the IPC USART(2). It is called twice per frame... the first
    after the length byte is received. The second after the sumcheck.
*/
MN_IRQ void HART_DMAR_handler(void)
{
    ENTER_IRQ();                                          // we are in an interrupt, Mr. OS

    DMA_Clear_int(DMA_Chan_6);

    rcvErrors |= USART2->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE); // | USART_SR_NE

    if (!payLdFlag)                                            // got header (length)
    {
        USIGN32 x = dma_receiveBuffer[lthBytePosn] + 1;     // fetch length byte, add 1 for sumcheck

        if ((x + lthBytePosn + 1) <= sizeof(dma_receiveBuffer))     // will it fit in buffer ?
        {
            DMA_ConfigUART(dma_receiveBuffer + lthBytePosn + 1, x, &USART2->DR, DMA_Chan_6);
            payLdFlag = true;                                      // signal receiving payload
#if INSTRUM_HM_TIMERS == OPTION_ON
            u32 t = (u32)OS_GetTime32();
            current.time_wait = (u16)(t - timestamp);
            timestamp = t;
#endif
        }
    }
    else                                                  // got the payload
    {
        osif_set_event(HM_TASK_ID, HART_RECEIVE_END_EVENT);
#if INSTRUM_HM_TIMERS == OPTION_ON
        u32 t = (u32)OS_GetTime32();
        current.time_receive = (u16)(t - timestamp);
        //Only successful transactions register
        last.time_receive = MAX(last.time_receive, current.time_receive);
        last.time_send = MAX(last.time_send, current.time_send);
        last.time_wait = MAX(last.time_wait, current.time_wait);
#endif
    }
    LEAVE_IRQ();                                          // we are leaving the interrupt, Mr. OS
}

// - DMA Send -

/** \brief set up DMA frame transmit of a packet.  Note that the
  DMA Terminal Count interrupt is used to signal frame completion rather than USART
  Transmit Complete.  Although this is a little early it does no harm.
\param  lth - The packet length excluding preambles
*/
static void dmaSend(USIGN32 lth)
{
    //USART2->CR1 |= USART_CR1_PS;
    USART2->CR3 |= USART_CR3_DMAT;              // enable DMA receive mode
    DMA_SetUART(DMA_Chan_7, DMA_Chan_6);        // set DMA attributes for RECV and XMIT
    DMA_ConfigUART(dmaTransmitBuffer, lth + XMT_PREAMBLES, &USART2->DR, DMA_Chan_7);
#if INSTRUM_HM_TIMERS == OPTION_ON
    timestamp = (u32)OS_GetTime32();
#endif
}

/** \brief set up DMA frame receive after a packet is sent
*/
static void set_DMA(bool_t ad)
{
    rcvErrors    = 0;                         // clear cumaltive errors this packet
    payLdFlag    = false;                     // signal receiving header
    lthBytePosn  = ad ?  (LENGTH_POS + 4) : LENGTH_POS;
    USART2->CR1 &= ~USART_CR1_RXNEIE;
    USART2->CR3 &= ~USART_CR3_DMAR;           // take out of DMA receive mode
    (void)USART2->SR;                         // clear USART errors
    (void)USART2->DR;                         // discard received char, if any
    (void)USART2->DR;                         // discard received char, should have been no more than 1
    USART2->CR3 |= USART_CR3_DMAR;            // enable DMA receive mode
    DMA_SetUART(DMA_Chan_7, DMA_Chan_6);      // set DMA attributes for RECV and XMIT

    DMA_ConfigUART(dma_receiveBuffer, lthBytePosn + 1, &USART2->DR, DMA_Chan_6);
}


/** \brief This function is called upon Terminal Count from DMA channel 7 which services
    the transmit channel of the IPC USART(2). It is called once per frame...
*/
MN_IRQ void HART_DMAT_handler(void)
{
  ENTER_IRQ();                                          // we are in an interrupt, Mr. OS
    DMA_Clear_int(DMA_Chan_7);
    set_DMA((transmitBuffer[0] & 0x80U) != 0);           // initiate packet recevie
#if INSTRUM_HM_TIMERS == OPTION_ON
    u32 t = (u32)OS_GetTime32();
    current.time_send = (u16)(t - timestamp);
    timestamp = t;
#endif
  LEAVE_IRQ();                                          // we are leaving the interrupt, Mr. OS
}


// ------------------ Messaging Section ------------------
static MN_NO_INIT u8 header[elemsize(APPHeader_t,appheader)];

// ---- Transmit ----
/** \brief  This function is called whenever a packet has to be sent.
\param command - A pointer to a structure of command to send
*/
static void xmt_msg(const T_ASYNC_COMMAND *command)
{
    u8_least   i;

    for (i = 0; i<XMT_PREAMBLES; i++)
    {
        dmaTransmitBuffer[i] = 0xff;
    }

    u8_least tx_length = 2+(header[0] >> 5);
    for (i = 0; i<tx_length; i++)
    {
        transmitBuffer[i] = header[i];
    }
    transmitBuffer[tx_length++] = command->cmd;
    transmitBuffer[tx_length++] = (BYTE)command->in_len;
    void *p = command->in_buf;
    memcpy(transmitBuffer+tx_length, p, command->in_len);
    tx_length += command->in_len;
    u8  crc=0;
    for (i=0; i<tx_length; i++)
    {
        crc ^= transmitBuffer[i];
    }
    transmitBuffer[tx_length++] = crc;

    dmaSend(tx_length);
}

// --- Receive ---

/** \brief  Parses the received frame for integrity.
\return event bitmap to post to hm task
*/

static u8 hm_ProcessPacket(T_ASYNC_COMMAND *command)
{
    u8 event = 0U;
    USIGN16   hdr_len = 4 + (receiveBuffer[0] >> 5);
    //BOOL      other = (receiveBuffer[1] & 0x80) != MASTER_ADDR;
    USIGN8    cmd = receiveBuffer[hdr_len-2];
    USIGN16   data_len = receiveBuffer[hdr_len-1];
    BYTE    * data = receiveBuffer+hdr_len;
    USIGN16   len = hdr_len+data_len + 1;

    USIGN32 ix = RCV_PREAMBLES, lim = dma_receiveBuffer[lthBytePosn] + lthBytePosn + 1;
    BYTE sum = 0;

    while (ix < lim)
    {
        sum ^= dma_receiveBuffer[ix++];                   // compute sumcheck
    }

    // note: len is within buffer range or we would not be here

    if ((sum != receiveBuffer[len-1]) || (rcvErrors != 0))
    {
        event |= HART_ERROR_EVENT;
    }
    else
    {
        switch(receiveBuffer[0] & 0x07U)
        {
            case 6: /* ACK - slave to master */

            /* TRANSMIT.Confirm(success)? */
            if ( (((header[0] ^ receiveBuffer[0]) & 0xE0U) != 0U) ||
                ( (((header[1] ^ receiveBuffer[1]) & 0x3FU) != 0U) ||
                (
                  ((header[0] & 0x80U) != 0U) &&
                    (header[2] != receiveBuffer[2] ||
                     header[3] != receiveBuffer[3] ||
                     header[4] != receiveBuffer[4] ||
                     header[5] != receiveBuffer[5])
                        )
                ) ||
                //DMA receive won't let it happen so out_len is not pre-populated: (command->out_len<len) ||
                (command->cmd != cmd))
            {
                /* Transmission failure */
                command->out_len = 0;

                /* response was failure */
                event |= HART_ERROR_EVENT;
            }
            else
            {
                /* Transmission success */
                command->out_len = len;
                memcpy(command->out_buf, data, data_len);
            }
            break;

            case 2: /* STX - master to slave */
            case 1: /* BACK - burst frame */
            default:
                event |= HART_ERROR_EVENT;
                break;
        }
    }
    return event;
}

// ------------ Persistent HART connection Section ---------------------

static APPHeader_t APPHeader; //! Persistent IPC HART header container

const APPHeader_t *hm_GetAPPHeader(APPHeader_t *dst)
{
    return STRUCT_TESTGET(&APPHeader, dst);
}
const APPHeader_t APPHeader_default =
{
    .appheader = {0x82U, 0,}, //lint !e785 OK with all trailing 0's
    .CheckWord = CRC_SEED,
};

static ErrorCode_t hm_SetAPPHeaderEx(const APPHeader_t *src, bool_t save)
{
    if(src == NULL)
    {
        src = &APPHeader_default;
    }

    MN_ENTER_CRITICAL(); //For lint, really
        STRUCT_GET(src, &APPHeader);
    MN_EXIT_CRITICAL();

    MN_ENTER_CRITICAL(); //For lint, really
        memcpy(header, APPHeader.appheader, sizeof(header)); //On a cheap for now
    MN_EXIT_CRITICAL();

    ErrorCode_t err = ERR_OK;
    if(save)
    {
        err = ram2nvramAtomic(NVRAMID_APPHeader);
    }
    return err;
}

ErrorCode_t hm_SetAPPHeader(const APPHeader_t *src)
{
    return hm_SetAPPHeaderEx(src, true);
}


static const USART_InitTypeDef USART_InitStructure =
{
    .USART_BaudRate = UART_IPC_BAUDRATE,
    .USART_WordLength = USART_WordLength_9b,
    .USART_StopBits = USART_StopBits_1,
    .USART_Parity = USART_Parity_Odd,
    .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
    .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
};

/** \brief Initialises the HART interface and gets the device ID. The
  function is called from function hm_init() in module hm_if.c. By default
  the short_address is set to 0 (see function hm_init()).

  Note: The function initializes IPC UART
NOTE: Always uses polling address 0
*/
void HART_Init(void)
{
    /*call to hm_init_db() removed along with the removed function itself
    Initialization is now done at compile time
    */

    /* Initialize the HM (HART master) hardware */
    /* Configure USART2 peripheral */
    USART_Init(USART2, &USART_InitStructure);
    /* Enable the USART2 peripheral */
    USART_Cmd(USART2, ENABLE);

}/* END of HART_Init */

/** \brief A case of complete shutdown of communications to APP.
    Realistic use case if flash failure.
May also be used for testing purposes.

Not clear why it fails in #if 0 clause. hm_task is never activated again.
*/
void hm_kill_uart(void)
{
#if 1
    MN_ENTER_CRITICAL();
        //systickdly(200);
        USART2->CR1 &= ~USART_CR1_UE; //In case we return
        USART2->CR1 &= ~(USART_CR1_PS); //paranoia
    MN_EXIT_CRITICAL();
#else
    sysio_ShowCrash(NULL, 0);
#endif
}


// ------------ Application services Section ---------------------

/* 38.4 bits/ms / 12 bits/byte = 3.2 bytes/ms
  Relax it by 5% (0.95) UART time discrepancy allowance
  Account for max payload
*/
#define RCV_GAP_TIME ((100*100*(s32)RSP_MAX_PAYLOAD)/(320*95)) //it's signed for no reason other than RTOS


/** \brief Simple Transmit/Receive function with no regard to
- Secondary Master
- Gap timing
- Burst
\param command - a pointer to a command structure
\return an event bitmap to reprocess
*/
OS_TASK_EVENT hart_TxRx(T_ASYNC_COMMAND *command)
{
    if (command->state == ASYNC_COMMAND_EXECUTE)
    {
        osif_set_event(HM_TASK_ID, HART_ERROR_EVENT); /* new command was started when a command is pending */
        return HART_ERROR;
    }

    command->state = ASYNC_COMMAND_EXECUTE;
    enum T_ASYNC_COMMAND_STATE newstate = ASYNC_COMMAND_FAILED;

    OS_TASK_EVENT event;
    for(s8_least retry=0; retry<HART_RETRY_LIMIT; retry++)
    {
        xmt_msg(command);

        OS_TIME timeout      = RT1+2*RCV_GAP_TIME;
        //We don't want to use OS_SingleEventTimed, so as not to consume other events
        event = OS_WaitSingleEventTimed(HART_RECEIVE_END_EVENT|HART_ERROR_EVENT, timeout);

        if((event & HART_ERROR_EVENT)!= 0)
        {
            ;
        }
        else
        {
            if((event & HART_RECEIVE_END_EVENT)== 0)
            {
                /* There was no response within timeout.
                This is an error; treat it as such
                */
                event |= HART_ERROR_EVENT;
            }
            else
            {
                //txrx_errcount=0;
                u8 event1 = hm_ProcessPacket(command);
                event |= event1;
                if(event1 == 0U)
                {
                    newstate = ASYNC_COMMAND_DONE;
                    break;
                }
            }
        }
    }
    //We are finished with this command
    command->state = newstate;
    return event;
}

//lint ++flb
//Stolen from hart.h
typedef struct  short_rsp_hdr_t
{
    u8 delimiter;
    u8 address;
    u8 command;
    u8 bytecount;
    u8 rsp_code_1;
    u8 rsp_code_2;
    u8 response;
} short_xmt_rsp_t;
//lint --flb

#define SHORT_HEADER_LEN sizeof(short_xmt_rsp_t)

/** \brief Sends command 0 to connect to HART slave device,
\return HART_OK  if no error, HART_ERROR otherwise.
*/
USIGN16 HART_send_cmd0(void)
{
    /* Normally, we don't send command 0, so if we do,
    treat it as an error for instrumentation
    */
    instrum_ipc_CountReinits();

    T_ASYNC_COMMAND  init;

    u8 buffer[SHORT_HEADER_LEN + HC0_LENGTH + 8]; // +8 is just a paranoid fudge but 1 for a dribble byte would be necessary

    HART_InitAsyncCommand(&init);
    init.cmd = 0;
    init.in_len = 0;

    init.out_len = sizeof(buffer);
    init.out_buf = buffer;
    buffer[0] = 17; //any non-0 to catch missing response

    //We may be stepping here on another command waiting for response in vain.
    //Wait it time out.
    OS_TIME TimeOut = 2*RCV_GAP_TIME + RT1; //ms
    (void)OS_WaitEventTimed(HART_RECEIVE_END_EVENT, TimeOut); //drop the events, if any

    header[0]      = 0x02;
    u8 short_address = 0U;
    header[1]      = (short_address & 0x3FU) | MASTER_ADDR;

    OS_TASK_EVENT event = hart_TxRx(&init);

    //restore the butchered `header'
    header[0] = APPHeader.appheader[0];
    header[1] = APPHeader.appheader[1];

    if (((event & HART_RECEIVE_END_EVENT) == 0) || (init.out_len < 14) || (buffer[0] != 0))
    {
        return HART_ERROR;
    }

    bool_t need_reset =
      ((APPHeader.appheader[1] != ((buffer[3] & 0x3FU) | MASTER_ADDR)) /* manufacturer */
      || (APPHeader.appheader[2] != buffer[4])                      /* device type */
      || (APPHeader.appheader[3] != buffer[11])                     /* device id[2] */
      || (APPHeader.appheader[4] != buffer[12])                     /* device id[1] */
      || (APPHeader.appheader[5] != buffer[13]))                     /* device id[0] */

      && !error_IsFault(FAULT_NVM_CHECKSUM0)
          /* EXPLANATION:
          If we are reinitializing NVMEM because of failure (e.g. upgrade from R2),
          reset (and saving the id before it) does us no good other than extra panic
          in APP (which is bad)
          We are better off NOT resetting on this occasion, and wait until NVMEM
          is repaired.
          */
        ;

    APPHeader_t a;
    a.appheader[0] = 0x82U;
    a.appheader[1] = (buffer[3] & 0x3FU) | MASTER_ADDR;
    a.appheader[2] = buffer[4];
    a.appheader[3] = buffer[11];
    a.appheader[4] = buffer[12];
    a.appheader[5] = buffer[13];
    ErrorCode_t err = hm_SetAPPHeaderEx(&a, need_reset); //To repair the `header'
    UNUSED_OK(err); //Nothing we can do
#if USE_ASSERT
    MN_RT_ASSERT(!need_reset); //mismatched device id fixed!
#else
    if(need_reset)
    {
        reset_Warmstart(); //mismatched device id fixed!
    }
#endif
    return HART_OK;
} /* FUNCTION hm_send_cmd0 */


/** \brief initializes the HART command structure.
\param[out]  command  - a pointer to the command structure.
*/
void HART_InitAsyncCommand(T_ASYNC_COMMAND *command)
{
    command->state   = ASYNC_COMMAND_IDLE;
    command->cmd     = 0;
    command->in_len  = 0;
    command->in_buf  = NULL;
    command->out_len = 0;
    command->out_buf = NULL;
}



// end of source
