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

FILE_NAME          hm.c



FUNCTIONAL_MODULE_DESCRIPTION

This modul contains the code for communication with hart interface.

=========================================================================== */
  #include "keywords.h"   /* keyword defines */
  #define  MODULE_ID      (COMP_HM + MOD_HM)

  #include <string.h>

  #include "base.h"
  #include "osif.h"
  #include "except.h"
  #include "hw_cfg.h"
  #include "hw_if.h"
  #include "hm_cfg.h"
  #include "hm.h"

  #include "stm32f10x.h"
  #include "stm32f10x_usart.h"
  #include "hm_dma.h"
  #include "hccheck.h"
#include <hm_api.h>
#include "crc.h"
#include "nvram.h"
#include "reset.h"


enum T_RCV_MSG { NOTHING, STX, ACK, BACK, OACK, OBACK, ERR };
static void xmt_msg(void);
static void statemachine(enum T_RCV_MSG rcv_msg, USIGN8 cmd, USIGN16 len, BYTE *buf);


/* master_state */
typedef enum mstate_t
{
    WATCHING_STATE,
    ENABLED_STATE,
    USING_STATE
} mstate_t;
static mstate_t master_state = WATCHING_STATE;

/* receive irq states */
#define RX_INACTIVE             0    /* inactive - waiting on first preamble */
#define RX_RECEIVING_DATA       4    /* length received */

/* transmit irq states */
#define TX_INACTIVE             0
#define TX_ACTIVE               1


#include "da_hm.h"
/* We are not shy to say that HART state machine is pre-inititialized.
  That takes care of the order of initialization.
  Additionally, missing volatile qualifier is added as necessary. Without it,
  the code is not guaranteed to work as intended (and is known not to work
  at high optimization)
*/
static volatile T_ASYNC_COMMAND *queue = NULL;
static volatile T_ASYNC_COMMAND *pending = NULL;
static  T_BURST_FUNCTION *volatile burst_indicate = NULL;
static u8 tx_state = TX_INACTIVE, tx_length;
static u8 rx_state = RX_INACTIVE;
STATIC u16 rx_gap = 0;
  STATIC NO_INIT  u32 timeout, count;
static BOOL msg_pending=FALSE, burst;
  STATIC NO_INIT  BYTE header[9];

static APPHeader_t APPHeader; //! Persistent IPC HART header container

const APPHeader_t *hm_GetAPPHeader(APPHeader_t *dst)
{
    return STRUCT_TESTGET(&APPHeader, dst);
}
const APPHeader_t APPHeader_default =
{
    .appheader = {0x82U, 0,},
    .CheckWord = CRC_SEED,
};

ErrorCode_t hm_SetAPPHeader(const APPHeader_t *src)
{
    if(src == NULL)
    {
        src = &APPHeader_default;
    }
    STRUCT_GET(src, &APPHeader);
    memcpy(header, APPHeader.appheader, sizeof(header)); //On a cheap for now
    return ram2nvramAtomic(NVRAMID_APPHeader);
}

/* 38.4 bits/ms / 12 bits/byte = 3.2 bytes/ms
  Relax it by 5% (0.95) UART time discrepancy allowance
  Account for max payload
*/
#define RCV_GAP_TIME (100*100*RSP_MAX_PAYLOAD)/(320*95)

#if INSTRUM_HM_TIMERS == OPTION_ON
#error "No useful content implemented yet"
static const adaptimers_t adaptimers_default =
{
    .rt1 = 56, //RT1 default is too low: Saw 46
    .rcv_gap = RCV_GAP_TIME, //this default may be too low
    .CheckWord = CRC_SEED, //don't care
};

static adaptimers_t adaptimers;

//MN_INLINE
void adaptimers_IncrementRT1(void)
{
    MN_ENTER_CRITICAL();
        u16 rt1 = MIN(adaptimers.rt1 + 1U, adaptimers_default.rt1 + 2U*RT1); //Put a cap on incremented value
        storeMemberInt(&adaptimers, rt1, rt1);
    MN_EXIT_CRITICAL();
}

//MN_INLINE
void adaptimers_IncrementRcvGap(void)
{
    MN_ENTER_CRITICAL();
        u16 rcv_gap = MIN(adaptimers.rcv_gap + 1U, 2*RCV_GAP_TIME); //Put a cap on incremented value
        storeMemberInt(&adaptimers, rcv_gap, rcv_gap);
    MN_EXIT_CRITICAL();
}

void adaptimers_Get(adaptimers_t *dst)
{
    STRUCT_GET(&adaptimers, dst);
}

ErrorCode_t adaptimers_Set(const adaptimers_t *src)
{
    ErrorCode_t err;
    if((src->rt1 < RT1) || (src->rcv_gap < RCV_GAP_TIME))
    {
        err = ERR_LOWERLIM;
    }
    else
    {
        STRUCT_GET(src, &adaptimers);
        err = ERR_OK;
    }
    return err;
}

/** \brief A simple reporting function with reset to firmware defaults
\param dst - a buffer pointer to receive current values
*/
void  adaptimers_ReadAndReset(adaptimers_t *dst)
{
    if(dst != NULL)
    {
        STRUCT_GET(&adaptimers, dst);
    }
    STRUCT_GET(&adaptimers_default, &adaptimers);
}
#endif //INSTRUM_HM_TIMERS


  #define HDR_RESV      16
  #define XMT_PREAMBLES 5
  STATIC NO_INIT  BOOL     payLdFlag;                           // false: receiving header; true: receiving payload
  STATIC NO_INIT  USIGN32  lthBytePosn;                            // computed position of lenght octet in receive message - based on CMD 0 or some other
  STATIC NO_INIT  USIGN8   rcvErrors;

  STATIC NO_INIT  BYTE dmaTransmitBuffer[MAX_HART_TELEGRAMM_LEN+HDR_RESV+XMT_PREAMBLES];
  STATIC BYTE * const transmitBuffer = dmaTransmitBuffer + XMT_PREAMBLES;

  #define RCV_PREAMBLES 5
  #define LENGTH_POS (RCV_PREAMBLES+3)      // preambles, DEL, ADR, CMD .. next is LEN
#define TRACK_ERROR_STATS 0
#if TRACK_ERROR_STATS!=0
  STATIC USIGN16 err_Sum, err_Gap;
  #define TRACK_ERRS   1
  #if TRACK_ERRS
    STATIC USIGN16 err_SR_PE, err_SR_FE, err_SR_ORE;
    #define KT(s) if ((rcvErrors & USART_##s) != 0) {err_##s++;}
    #define COUNT_ERRORS()\
        KT(SR_PE)\
        KT(SR_FE)\
        KT(SR_ORE) (void)0
  #else
    #define COUNT_ERRORS()
  #endif
#else
    #define COUNT_ERRORS()
#endif

  STATIC NO_INIT  BYTE dma_receiveBuffer[MAX_HART_TELEGRAMM_LEN+HDR_RESV+RCV_PREAMBLES];
  STATIC  BYTE * const receiveBuffer = dma_receiveBuffer + RCV_PREAMBLES;
  STATIC NO_INIT  USIGN8 receiving_checksum;
#include "da_def.h"

  static  BOOL initialized = FALSE;


#ifdef _DEBUG
  USIGN32 sent_cnt = 0;
  USIGN32 receive_cnt = 0;
  static BYTE old_cmd;
  USIGN32 xmt_cnt_start = 0, xmt_cnt_end = 0;
  USIGN32 rcv_cnt_start = 0, rcv_cnt_end = 0;
  USIGN8 last_rcv_id = 0;

#ifdef TRACE
typedef struct _TRACE_RECORD
{
       int master_state;
       int timeout;
       int tx_state;
       int rx_state;
}
TRACE_RECORD;

  TRACE_RECORD    trace[100];
  USIGN8 trace_idx = 0;
#endif /* TRACE */

FUNCTION PUBLIC VOID Dummy_for_measurement(VOID)
{
  sent_cnt = sent_cnt;
}

#endif /* _DEBUG */


LOCAL VOID set_DMA(BOOL ad)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function is called to set up DMA frame receive after a packet is sent

PARAMETERS:

  ad    A boolean flag indicting whether the expected response has a short
        address (command 0) or long (all others.

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  rcvErrors    = 0;                         // clear cumaltive errors this packet
  payLdFlag    = FALSE;                     // signal receiving header
  lthBytePosn  = ad ?  LENGTH_POS + 4 : LENGTH_POS;
  rx_state     = RX_INACTIVE;//RX_RECEIVING_HEADER;
  rx_gap = 0;
  USART2->CR1 &= ~USART_CR1_RXNEIE;
  USART2->CR3 &= ~USART_CR3_DMAR;           // take out of DMA receive mode
  (void)USART2->SR;                         // clear USART errors
  (void)USART2->DR;                         // discard received char, if any
  (void)USART2->DR;                         // discard received char, should have been no more than 1
  USART2->CR3 |= USART_CR3_DMAR;            // enable DMA receive mode
  DMA_SetUART(DMA_Chan_7, DMA_Chan_6);      // set DMA attributes for RECV and XMIT

  DMA_ConfigUART(dma_receiveBuffer, lthBytePosn + 1, (u32)&USART2->DR, DMA_Chan_6);
}

FUNCTION PUBLIC MN_IRQ VOID HART_DMAR_handler
  (
    IN  VOID
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function is called upon Terninal Count from DMA channel 6 which services
    the receive channel of the IPC USART(2). It is called twice er frame... the first
    after the kengh byte is received. The second after the sumcheck.

PARAMETERS:

  None

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/

{
LOCAL_VARIABLES

FUNCTION_BODY

  ENTER_IRQ();                                          // we are in an interrupt, Mr. OS

  DMA_Clear_int(DMA_Chan_6);

  rcvErrors |= USART2->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE); // | USART_SR_NE

  if (!payLdFlag)                                            // got header (length)
  {
    rx_state  = RX_RECEIVING_DATA;
    USIGN32 x = dma_receiveBuffer[lthBytePosn] + 1;     // fetch length byte, add 1 for sumcheck

    if ((x + lthBytePosn + 1) <= sizeof(dma_receiveBuffer))     // will it fit in buffer ?
    {
      DMA_ConfigUART(dma_receiveBuffer + lthBytePosn + 1, x, (u32)&USART2->DR, DMA_Chan_6);
      payLdFlag = TRUE;                                      // signal receiving payload

    }
  }
  else                                                  // got the payload
  {
    osif_set_event(HM_TASK_ID, HART_RECEIVE_END_EVENT);

  }
  LEAVE_IRQ();                                          // we are leaving the interrupt, Mr. OS
}



LOCAL VOID dmaSend(USIGN32 lth)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function is called to set up DMA frame transmit of a packet.  Note that the
  DMA Terminal Count interrupt is used to signal fram completion rather than USART
  Transmit Complete.  Although this is a little early it does no harm.


PARAMETERS:

  lth    The packet length excluding preambles

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
  USART2->CR1 |= USART_CR1_PS;

  USART2->CR3 |= USART_CR3_DMAT;              // enable DMA receive mode

  DMA_SetUART(DMA_Chan_7, DMA_Chan_6);        // set DMA attributes for RECV and XMIT

  DMA_ConfigUART(dmaTransmitBuffer, lth + XMT_PREAMBLES, (u32)&USART2->DR, DMA_Chan_7);
}


FUNCTION PUBLIC MN_IRQ VOID HART_DMAT_handler
  (
    IN  VOID
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function is called upon Terninal Count from DMA channel 7 which services
    the transmit channel of the IPC USART(2). It is called once per frame...

PARAMETERS:

  None

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
  ENTER_IRQ();                                          // we are in an interrupt, Mr. OS
    tx_state = TX_INACTIVE;
    DMA_Clear_int(DMA_Chan_7);
    set_DMA((transmitBuffer[0] & 0x80) != 0);           // initiate packet recevie
  LEAVE_IRQ();                                          // we are leaving the interrupt, Mr. OS
}

/******************************************************************************/

FUNCTION PUBLIC USIGN16 HART_Init
  (
    IN  USIGN8  short_address
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  The function initialises the HART interface and gets the device ID. The
  function is called from function hm_init() in module hm_if.c. By default
  the short_address is set to 0 (see function hm_init()).

  Note: The function initializes everything!

PARAMETERS:

  short_address          0-63 is interpreted as slave address.

RETURN_VALUES:

  HART_OK                No error.
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    UNUSED_OK(short_address); //AK: Undo somehow
  /* Reset when already initialized */
  HART_Exit();

    MN_ENTER_CRITICAL();
      /* Initialize the HART state machine */
      queue          = NULL;
      pending        = NULL;
      //header[0]      = 0x02;
      //header[1]      = short_address & 0x3F | MASTER_ADDR;
      tx_state       = TX_INACTIVE;
      rx_state       = RX_INACTIVE;
      master_state   = WATCHING_STATE;
      timeout        = RT1;
      msg_pending    = FALSE;
      burst          = FALSE;
      burst_indicate = NULL;
      /*call to hm_init_db() removed along with the removed function itself
      Initialization is now done at compile time
      */
    MN_EXIT_CRITICAL();

  /* Initialize the HM (HART master) hardware */
  hw_hm_init();

  initialized = TRUE;

  return HART_OK;
}/* END of HART_Init */

/******************************************************************************/

FUNCTION PUBLIC USIGN16 HART_send_cmd0
  (
    IN USIGN8 * buffer,
    IN USIGN8 * buf_size
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  The function sends the command 0 to the connected HART slave device,

PARAMETERS:

  buffer           Pointer to the buffer to send.

  buf_size         Pointer to the buffer size.

RETURN_VALUES:

  HART_OK          No error.
  HART_ERROR       HART communication error.
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

  static volatile T_ASYNC_COMMAND  init;
  static BOOL             init_done = FALSE;

FUNCTION_BODY

  if (init_done == FALSE)
  {
    HART_InitAsyncCommand(&init);
    init.cmd = 0;
    init.in_len = 0;
  }

    init.out_len = *buf_size;
    init.out_buf = buffer;
    buffer[0] = 17; //any non-0 to catch missing response

    //We may be stepping here on another command waiting for response in vain.
    //Wait it time out.
    OS_TIME TimeOut = 2*RCV_GAP_TIME + RT1; //ms
    (void)OS_WaitEventTimed(HART_RECEIVE_END_EVENT, TimeOut); //drop the events, if any

    header[0]      = 0x02;
    u8 short_address = 0U;
    header[1]      = (short_address & 0x3FU) | MASTER_ADDR;

    USIGN16 result = HART_Command_non_block(&init);
    if (result == HART_OK)
    {
        OS_TASK_EVENT event = OS_WaitEventTimed(HART_RECEIVE_END_EVENT, TimeOut);
        if((event & (HART_GAPTIMER_EVENT|HART_ERROR_EVENT))!= 0)
        {
            result = HART_ERROR;
        }
        else
        {
            hm_ProcessTimerEvents();
            if((event & HART_RECEIVE_END_EVENT)== 0)
            {
                result = HART_ERROR;
            }
            else
            {
                hm_ProcessPacket();
            }
        }
    }

    //restore the butchered `header'
    header[0] = APPHeader.appheader[0];
    header[1] = APPHeader.appheader[1];
	
  if ((result != HART_OK) || (init.out_len < 14) || (buffer[0] != 0))
  {
    return HART_ERROR;
  }

  //MN_ENTER_CRITICAL();

    if(
      (APPHeader.appheader[1] != ((buffer[3] & 0x3FU) | MASTER_ADDR)) /* manufacturer */
      || (APPHeader.appheader[2] != buffer[4])                      /* device type */
      || (APPHeader.appheader[3] != buffer[11])                     /* device id[2] */
      || (APPHeader.appheader[4] != buffer[12])                     /* device id[1] */
      || (APPHeader.appheader[5] != buffer[13])                     /* device id[0] */
        )
    {
        APPHeader_t a;
        a.appheader[0] = 0x82U;
        a.appheader[1] = (buffer[3] & 0x3FU) | MASTER_ADDR;
        a.appheader[2] = buffer[4];
        a.appheader[3] = buffer[11];
        a.appheader[4] = buffer[12];
        a.appheader[5] = buffer[13];
        ErrorCode_t err = hm_SetAPPHeader(&a);
        UNUSED_OK(err); //Nothing we can do
        reset_Warmstart();
    }

    *buf_size = init.out_len;
  //MN_EXIT_CRITICAL();

  return HART_OK;
} /* FUNCTION hm_send_cmd0 */

/******************************************************************************/

FUNCTION PUBLIC VOID HART_Exit (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  The function closes the HART interface.

PARAMETERS:

  None

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    if (initialized)
    {
        MN_ENTER_CRITICAL();

            /* Fail all pending HART commands */
            if (msg_pending)
            {
              pending->out_len = 0;
              pending->state   = ASYNC_COMMAND_FAILED;
            }
            if (queue)
            {
              queue->out_len = 0;
              queue->state   = ASYNC_COMMAND_FAILED;
              queue = NULL;
            }

            /* Initialize HART state machine */
            tx_state     = TX_INACTIVE;
            rx_state     = RX_INACTIVE;
            master_state = WATCHING_STATE;
            msg_pending  = FALSE;
            initialized  = FALSE;

        MN_EXIT_CRITICAL();
  }

  return;
}/* END of HART_Exit */

/******************************************************************************/

FUNCTION PUBLIC VOID HART_SetBurstFunction
  (
    IN  T_BURST_FUNCTION * burst_function
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function sets the burst indication function. The function is
  called whenever a HART burst message is received.

  Note: Call this function after the call of function HART_Init().

PARAMETERS:

  burst_function   Function pointer to the burst function.

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

    MN_ENTER_CRITICAL();
        burst_indicate = burst_function;
    MN_EXIT_CRITICAL();
}

/******************************************************************************/

FUNCTION PUBLIC VOID HART_InitAsyncCommand
  (
    IN  volatile T_ASYNC_COMMAND * command
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function initializes the HART command structure.

PARAMETERS:

  command          Pointer to the command structure.

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  command->state   = ASYNC_COMMAND_IDLE;
  command->cmd     = 0;
  command->prio    = 0;
  command->in_len  = 0;
  command->in_buf  = NULL;
  command->out_len = MAX_HART_TELEGRAMM_LEN;
  command->out_buf = NULL;
}

/******************************************************************************/

FUNCTION PUBLIC USIGN16 HART_Command_non_block
  (
    IN  volatile T_ASYNC_COMMAND * command
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  The function sends a HART command and does not wait for the
  received data.

PARAMETERS:

  command          Pointer to the command structure.

RETURN_VALUES:

  HART_OK          No error.
  HART_ERROR       HART communication error.
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

  if (!initialized || command->state == ASYNC_COMMAND_EXECUTE)
  {
    osif_set_event(HM_TASK_ID, HART_ERROR_EVENT); /* new command was started when a command is pending */
    return HART_ERROR;
  }

  command->state = ASYNC_COMMAND_EXECUTE;

      queue = command;
      statemachine(NOTHING, 0, 0, 0);

  return HART_OK;
}

/******************************************************************************/

LOCAL VOID xmt_msg (VOID)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function is called whenever a packet has to be sent.
  It transmits the "pending" command.

PARAMETERS:

  None

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

  BYTE  crc;
  int   i;

FUNCTION_BODY

#ifdef _DEBUG
  xmt_cnt_start++;
#endif

  for (i = 0; i<XMT_PREAMBLES; i++)
  {
    dmaTransmitBuffer[i] = 0xff;
  }

  /* assert(tx_state == 0); */
  tx_state = TX_ACTIVE;
  tx_length = 2+(header[0] >> 5);
  for (i = 0; i<tx_length; i++)
    transmitBuffer[i] = header[i];
  transmitBuffer[tx_length++] = pending->cmd;
#ifdef _DEBUG
  if ((old_cmd !=0) && (pending->cmd == old_cmd))
      old_cmd = old_cmd;       /*_ASSERT(FALSE);   for tests only*/
  old_cmd = pending->cmd;
#endif /* _DEBUG */
  transmitBuffer[tx_length++] = (BYTE)pending->in_len;
  void *p = pending->in_buf;
  memcpy(transmitBuffer+tx_length, p, pending->in_len);
  tx_length += pending->in_len;
  for (i=0, crc=0; i<tx_length; i++)
    crc ^= transmitBuffer[i];
  transmitBuffer[tx_length++] = crc;
  HM_ASSERT_OCD();

  dmaSend(tx_length);

#ifdef _DEBUG
  xmt_cnt_end++;
#endif

}

/** \brief   This function used to be static, named rcv_msg, and was called whenever a packet was received,
right from the interrupt. Now it is called from hm_task context on the receive event posted by the interrupt.

Checks the checksum and call the statemachine to handle the received packet.
*/

void hm_ProcessPacket(void)
{
LOCAL_VARIABLES

  USIGN16   hdr_len = 4 + (receiveBuffer[0] >> 5);
  BOOL      other = (receiveBuffer[1] & 0x80) != MASTER_ADDR;
  USIGN8    cmd = receiveBuffer[hdr_len-2];
  USIGN16   data_len = receiveBuffer[hdr_len-1];
  BYTE    * data = receiveBuffer+hdr_len;
  USIGN16   len = hdr_len+data_len + 1;

FUNCTION_BODY

    USIGN32 ix = RCV_PREAMBLES, lim = dma_receiveBuffer[lthBytePosn] + lthBytePosn + 1;
    BYTE sum = 0;

    while (ix < lim)
    {
      sum ^= dma_receiveBuffer[ix++];                   // compute sumcheck
    }
    receiving_checksum = sum;
    rx_state = RX_INACTIVE;

#ifdef _DEBUG
  rcv_cnt_start++;
#endif

  HM_RELEASE_OCD ();

  // note: len is within buffer range or we would not be here

    if ((receiving_checksum != receiveBuffer[len-1]) || (rcvErrors != 0))
    {
#if TRACK_ERROR_STATS != 0
        if (receiving_checksum != receiveBuffer[len-1])
        {
            err_Sum++;
        }
#endif
        COUNT_ERRORS();
        statemachine(ERR, 0, 0, 0);
    }
    else
    {
        switch(receiveBuffer[0] & 0x07)
        {
          case 1: /* BACK - burst frame */
            statemachine(other ? OBACK : BACK, cmd, data_len, data);
            if (burst_indicate != NULL)
            {
              _ASSERT(FALSE);  /* for tests only */
              burst_indicate (cmd, data_len, data);
            }
            break;

          case 2: /* STX - master to slave */
            _ASSERT(FALSE);  /* for tests only */
            statemachine(STX, cmd, data_len, data);
            break;

          case 6: /* ACK - slave to master */
            statemachine(other ? OACK : ACK, cmd, data_len, data);
            break;

          default:
            statemachine(ERR, 0, 0, 0);
            break;
        }
    }

#ifdef _DEBUG
  rcv_cnt_end++;
#endif

}

static mstate_t mstate_Watching(mstate_t mstate, enum T_RCV_MSG   rcv_msg)
{
      /* Check for burst mode */
      if (rcv_msg == BACK || rcv_msg == OBACK ||
         (rcv_msg == ACK  || rcv_msg == OACK) && receiveBuffer[1] & 0x40)
      {
        burst = TRUE;
      }

      /* Set timeout */
      if (rcv_msg == STX || rcv_msg == OACK && burst)
      {
        timeout = RT1;
      }

      if (rcv_msg == BACK)
      {
        timeout = RT1;      /* CYCLIC.Indicate */
      }

      /* Message not pending? */
      if (!msg_pending && queue != NULL && queue->state==ASYNC_COMMAND_IDLE)
      {
        count       = 0;
        msg_pending = TRUE;
        pending     = queue;
        queue       = NULL;
        mstate = ENABLED_STATE; //AK added; now needed for new timeout monitor in MaintainTimes
      }

      /* Message pending and does error count exceed the limit? */
      if (msg_pending && (count>=HART_RETRY_LIMIT))
      {
        msg_pending      = FALSE;
        pending->out_len = 0;
        pending->state   = ASYNC_COMMAND_FAILED;
        /* there is no answer from HART device */
        osif_set_event(HM_TASK_ID, HART_ERROR_EVENT); /* there is no answer from HART device */
      }

      /* Check if the timeout time elapsed */
      if (timeout<=0)
      {
        burst = FALSE;
        if (queue != NULL && !msg_pending)
        {
          count        = 0;
          msg_pending  = TRUE;
          pending      = queue;
          queue        = NULL;
          timeout      = HOLD;
          mstate = ENABLED_STATE;

        }
        else if ( msg_pending && (count < HART_RETRY_LIMIT) )
        {
          timeout      = HOLD;
          mstate = ENABLED_STATE;

        }
      }


      if (rcv_msg == OBACK)
      {
        timeout      = HOLD;
        mstate = ENABLED_STATE;                /* CYCLIC.Indicate */

      }

      if (rcv_msg == OACK && !burst)
      {
        timeout      = HOLD;
        mstate = ENABLED_STATE;
      }

    return mstate;
}


static mstate_t mstate_Enabled(mstate_t mstate)
{
    if (rx_state != RX_INACTIVE)
    {
        mstate = WATCHING_STATE;
    }

    /* Check if the timeout time elapsed */
    if (timeout<=0)
    {
        timeout      = 2 * RT1;
        mstate = WATCHING_STATE;
    }

    /* Message not pending and queue not empty? */
    if (queue != NULL && !msg_pending)
    {
        count       = 0;
        msg_pending = TRUE;
        pending     = queue;
        queue       = NULL;
    }

    /* Message pending and error count does not exceed */
    if (msg_pending && count<HART_RETRY_LIMIT && tx_state == TX_INACTIVE)
    {
        xmt_msg();                                 /* Receive message */
        //rcv_msg      = NOTHING;
        /////timeout      = RT1_PRIMARY;
        timeout      = RT1_PRIMARY+2*RCV_GAP_TIME;
        mstate = USING_STATE;
    }

    return mstate;
}

static mstate_t mstate_Using(mstate_t mstate, enum T_RCV_MSG rcv_msg, USIGN8 cmd, USIGN16 len, BYTE *buf)
{
      /* Check if something was received */
      if (rcv_msg == ACK)
      {
        timeout = burst ? RT1 : RT2;
        msg_pending = FALSE;

        /* TRANSMIT.Confirm(success)? */
        if (((header[0] ^ receiveBuffer[0]) & 0xE0) ||
            ((header[1] ^ receiveBuffer[1]) & 0x3F) ||
            (
              (header[0] & 0x80) &&
                (header[2] != receiveBuffer[2] ||
                 header[3] != receiveBuffer[3] ||
                 header[4] != receiveBuffer[4] ||
                 header[5] != receiveBuffer[5])
            ) ||
            (pending->out_len<len) ||
            (pending->cmd != cmd))
        {
          /* Transmission failure */
          pending->out_len = 0;
          pending->state   = ASYNC_COMMAND_FAILED;

          /* response was failure */
          osif_set_event(HM_TASK_ID, HART_ERROR_EVENT);

        }
        else
        {
          /* Transmission success */
          pending->out_len = len;
          memcpy(pending->out_buf, buf, len);
          pending->state = ASYNC_COMMAND_DONE;
#ifdef _DEBUG
          receive_cnt++;
          /* if (receive_cnt != sent_cnt)
          {
            receive_cnt = receive_cnt;
            _ASSERT(FALSE);
          } */
#endif /* _DEBUG */
        }
        mstate = WATCHING_STATE;
      }

      else if (rcv_msg != NOTHING)
      {
        count++;
        timeout = RT1;
        mstate = WATCHING_STATE;
      }

      /* Check if the timeout time elapsed */
      if (timeout<=0)
      {
#ifdef _DEBUG
        Dummy_for_measurement();
#endif /* _DEBUG */
        HM_RELEASE_OCD ();
        count++;
        timeout = burst ? RT1 : RT1-RT1_PRIMARY;
        mstate = WATCHING_STATE;
      }

      return mstate;
    }

/** \brief Partially re-done to be run from hm_task only (to reduce interrupt load)
*/
static void statemachine
  (
    IN  enum T_RCV_MSG   rcv_msg,
    IN  USIGN8           cmd,
    IN  USIGN16          len,
    IN  BYTE           * buf
  )
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:

  This function is a straight forward implementation of the
  master state machine from the HART Data Link Layer Specification
  (Figure 18, Page 47).

PARAMETERS:

  rcv_msg          What kind of message.

  cmd              Command identifier.

  len              User data length.

  buf              Pointer to the user dat buffer.

RETURN_VALUES:

  None
------------------------------------------------------------------------------*/
{
    mstate_t oldmstate;
    mstate_t new_mstate = master_state;

    do
    {
        oldmstate = new_mstate;
        switch(oldmstate)
        {
            case WATCHING_STATE:
            {
                new_mstate = mstate_Watching(oldmstate, rcv_msg);
                break; /* case WATCHING_STATE: */
            }

            case ENABLED_STATE:
            {
                new_mstate = mstate_Enabled(oldmstate);
                if(new_mstate == USING_STATE)
                {
                    rcv_msg      = NOTHING;
                }
                break; /* case ENABLED_STATE: */
            }
            case USING_STATE:
            {
                new_mstate = mstate_Using(oldmstate, rcv_msg, cmd, len, buf);
                break;
            }
            default:
                break;

        } /* switch */
    } while(new_mstate != oldmstate);

    master_state = new_mstate;

}/* END of statemachine */

/******************************************************************************/
static bool_t flag_rcv_error = false;
static bool_t flag_idle = false;

void hm_ProcessTimerEvents(void)
{
    bool_t rcv_error;
    bool_t idle;
    MN_ENTER_CRITICAL();
        rcv_error = flag_rcv_error;
        flag_rcv_error = false;
        idle = flag_idle;
        flag_idle = false;
    MN_EXIT_CRITICAL();
    if(rcv_error)
    {
        statemachine(ERR, 0, 0, 0);
    }
    if(idle)
    {
        statemachine(NOTHING, 0, 0, 0);
    }
}

/** \brief Replacement for HART_timer_irq to be called from systick handler
*/
void hm_MaintainTime(void)
{
    if (rx_state != RX_INACTIVE)
    {
        if (++rx_gap>RCV_GAP_TIME)
        {
            HM_RELEASE_OCD ();

            //      LA_TRIGGER (6);    // only for debugging!!

#if TRACK_ERROR_STATS!=0
                err_Gap++;
#endif
                rcvErrors |= USART2->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE); // | USART_SR_NE
                COUNT_ERRORS();
                /* RCV_ERROR */
                rx_state = RX_INACTIVE;
                flag_rcv_error = true;
                osif_set_event(HM_TASK_ID, HART_GAPTIMER_EVENT);
        }
    }
    else
    {
        if ((tx_state == TX_INACTIVE) && (timeout > 0) && !flag_idle)
        {
            HM_RELEASE_OCD ();
            if (--timeout == 0 )
            {
                flag_idle = true;
                osif_set_event(HM_TASK_ID, HART_GAPTIMER_EVENT);
            }
        }
    }
}

// end of source
