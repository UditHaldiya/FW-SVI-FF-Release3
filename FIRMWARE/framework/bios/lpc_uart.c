/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup HARTDLL HART data link layer implementation
\brief HART data link layer implementation
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_HART_DataLinkLayer.doc"> Design document </a><br>
<a href="../../../Doc/TestDocs/utplan_BIOS.doc"> Unit Test Report </a><br>
\endhtmlonly
*/
/**
    \file lpc_uart.c
    \brief UART handler for HART communications

    CPU: Philips LPC21x4 (ARM)

    OWNER: Ernie Price

    $Author: Arkkhasin $

    \ingroup HARTDLL
*/
#include "mnwrap.h"
#include "lpc2114io.h"
#include "bios_def.h"
#include "serial.h"
#include "timebase.h"
#include "hart.h"

#define BPS_RATE           1200
#define RATE_DIVISOR (PCLKFREQ / (BPS_RATE * 16u))

#if 0
/* states of the send statemachine */
#define SEND_PREAMBLE       0x10
#define PREAMBLES_SENT      0x11
#define DATA_SENT           0x12
#define LASTBYTE_SENT       0x16
#define TRANSMIT_IDLE       0x17
/*

    LPC2114 UART0 receive behavior with FIFO active and RX threshold set to one.

    OE (Overrun Error) bit accompanies top (first out) character of FIFO.  FIFO has 16
    oldest characters. One or more recent characters have been discarded.

    BI (Break Interrupt) is also accompanied by FE, [PE if ODD PARITY], and DR.  There will be
    a NUL in the receive FIFO which should be discarded.

    If IIR LSIE is set, BI will have a second interrupt immediately following.  There is no DR
    for this event. Note that this interrupt does not wait for the BREAK conditon (line at mark)
    to stop.

    The UART hardware is LEVEL (as opposed to EDGE) sensitive.  Failure to service all outstanding
    interrupts merely causes immediate reentry to the IRQ routine.

    A full-duplex test between an LPC2114 and a PC exhibits no tendency toward lost transmit
    interrupts.

    Below Added 6/5/2005.

    If LSIE is enabed the UART will interrupt twice, once with INTID_LSIE and once
    with INTID_RDA even if the LSIE handler fetches the character.  Without protection,
    i.e checking the LSR for RDR, this results in a character being processed twice.

    In order to keep the Line Status synchronized with the Receive Data, the LSIE has been
    disabled.  All receive processing is done in the Receive Data routine.  The LSR is fetched
    and processed accordingly.

*/
#endif

static const u8 uart2hart[] =           // UART to HART receive error translation table
{
    [0]                        = 0U,
    [LSR_FE]                   = FRAMING,
    [LSR_PE]                   = PARITY_ERR,
    [LSR_OE]                   = OVERRUN,
    [LSR_FE | LSR_PE]          = FRAMING | PARITY_ERR,
    [LSR_FE | LSR_OE]          = FRAMING | OVERRUN,
    [LSR_PE | LSR_OE]          = PARITY_ERR | OVERRUN,
    [LSR_FE | LSR_PE | LSR_OE] = FRAMING | PARITY_ERR | OVERRUN
};

// Transmitter variables
static const u8     *ser_send_ptr;        // pointer to the sendbuffer
#if 0
static u8           pre_cnt,              // counts all transmit Preambles
                    xmt_cksum;
static u8           hart_state_xmt;       // Statemachine
#endif
static u8           chr_cnt;              // number of bytes to send

/** \brief expire gap timer
\param hart_channel - HART channel
\return !0 for NO burst request
*/
static u8 timehandler_irq(u8_least hart_channel)
{
    u8 *pgaptm = serial_GetHartGapTimerPtr(hart_channel);
    *pgaptm >>= 1U; //expire gap timer
    return *pgaptm;
}

/** \brief Does channel-appropriate things for 5-ms processing (by delegating)
\param hart_channel - one of the valid HART channels
\return 0 iff burst on the channel is allowed, !=0 otherwise
*/
u8 HART_timehandler(u8_least hart_channel)
{
    return timehandler_irq(hart_channel);
}


void uart_setup(void)
{
#if 0
    hart_state_xmt = TRANSMIT_IDLE;
#endif
    chr_cnt        = 0;

    uart_t *uart = UART0;
    uart->FCR      = FCRFIFOENA | FCRRSTRX | FCRRSTTX;   /* enable Fifo, every char -> interrupt */
                                                    /* Clear Rx and Tx FIFOs */

    /* Baudrate 1843200 Hz / 96 / 2 = 19200 --> 1200Baud */
    uart->LCR      = LCRDLAB;    /* enable divisor access bit */
    uart->DLL      = RATE_DIVISOR;
    uart->DLM      = 0;
     /* Line control register, data format  */
    uart->LCR      = (LCRLENSEL | LCRPARENA); /* enable odd parity,
                                        select wordlen 8bits,
                                        1 stop bit,
                                        disable divisor access */
    /* Interrupts enable*/
    uart->IER      = (RBRIE | THRIE);        /* Receive- Send interrupt */
}

static void HART_Transmit(u8 ch)
{
    GPIO1->IOCLR   = GPIO1_HART_RTS;                /* switch modem to send; won't hurt if already on     */
    UART0->THR      = ch;                      /* first Preamble to the sendbuffer */
}


/** \brief  Starts sending of a frame
    Called from task context to initiate frame transmit, the rest of the frame
    will be sent in interrupt context.
*/
void serial_SendFrame(u8 uartNo, u8_least len, const u8 *bufptr)
{
    UNUSED_OK(uartNo); //single channel
        MN_ENTER_CRITICAL();
            ser_send_ptr   = bufptr+1;                        /* Initialize the send buffer */
            chr_cnt        = (u8)len - 1;

            HART_Transmit(*bufptr);
        MN_EXIT_CRITICAL();
}

/** \brief  Handle a receive interrupt from the UART - error bits, if any,
        are fetched here and rcv_exception is called for processing.

    Oddly enough, per HCF_SPEC_81, the device must respond if an error
    occurs in:
    - command
    - data
    - check byte (checksun)
    In fact, the spec talks about parity error.
    Unfortunately, the twisted nature of the receive interface makes it unreasonable
    to implement a block interface between UART and HART layers; the character
    interface is made instead, and this function belongs therefore to HART layer.

    \param[in] uart - a pointer to UART0
*/
static void rcv_complete(uart_t *uart)
{
    u8  lsrval = uart->LSR;

    u8 com_err = lsrval & (LSR_OE | LSR_PE | LSR_FE);
    // if there is an error condition process it now
    if (com_err != 0)
    {
        if ((com_err & LSR_OE) != 0)
        {
            uart->FCR = FCRFIFOENA | FCRRSTRX;         /* discard Rx FIFO content */
        }
        //And notify the state machine
        rcv_exception(uart2hart[com_err], 0); //0 is the only channel number
    }

    // now process the character - rcv_exception() will change the receive
    // state if required
    if ((lsrval & LSR_RDR) != 0)
    {
        rcv_char(uart->RBR, 0, 0); //0 is the only channel number
    }
}

/** \brief  Process a transmitter empty interrupt
    \param[in] uart - a pointer to the uart 0 hardware
*/
static void xmt_complete(uart_t *uart)
{
#if 1
    if(chr_cnt == 0)
    {
        //nothing to send; disable Tx interrupt
        //uart->CR1 &= ~TXEIE;            // if message complete, disable TX interrupts
        GPIO1->IOSET   = GPIO1_HART_RTS;      /* switch modem to receive state  */
        //notify end of transmission
        hart_xmit_ok(TASKID_HART);
    }
    else
    {
        uart->THR  = *ser_send_ptr++;    /* Character to the sendbuffer */
        --chr_cnt;
    }
#else
    switch (hart_state_xmt)
    {
        case SEND_PREAMBLE:
            uart->THR = PREAMBLE;                   /* Preamble to the sendbuffer   */
            if (0  == --pre_cnt)          /* are there any Preambles to send ?  */
            {
                hart_state_xmt = PREAMBLES_SENT;
            }
            break;
        case LASTBYTE_SENT:
            //wrap up the transmission business
            hart_state_xmt = DATA_SENT;
            uart->THR      = PREAMBLE-1U; //"dribble" byte to account for RTS decay time
            break;

        case DATA_SENT:
            hart_state_xmt = TRANSMIT_IDLE;
            GPIO1->IOSET   = GPIO1_HART_RTS;      /* switch modem to receive state  */
            //notify end of transmission
            hart_xmit_ok(TASKID_HART);
            break;

        case PREAMBLES_SENT:
            if (0 == --chr_cnt)          /* all chars sent ?  */
            {
                hart_state_xmt = LASTBYTE_SENT;
                uart->THR      = xmt_cksum;
            	Hart_time_Reinit(); 		/* burst timer retriggers here */
            }
            else
            {
                xmt_cksum ^= *ser_send_ptr;      /* checksum compute */
                uart->THR  = *ser_send_ptr++;    /* Character to the sendbuffer */
            }
            break;

        default:
            break;
    }
#endif
}




MN_IRQ void Hart_ISR(void)
{
    uart_t *uart = UART0;

    switch (uart->IIR & IIP_INTID)
    {
        case INTID_RDA:
            rcv_complete(uart);             /* Receivestatemachine  */
            break;

        case INTID_THRE:                /* Sendinterrupt ?    */
            xmt_complete(uart);         /* Sendstatemachine     */
            break;

        default:
            break;
    }
    VICVectAddr = NULL;             /* update priority hardware (see datasheet) */
}

bool_t serial_CarrierDetect(u8_least hart_channel)
{
    UNUSED_OK(hart_channel);
    bool_t rslt = false;

    if ((GPIO1->IOPIN & GPIO1_HART_CD) != 0u)   // pin is high when CD present
    {
        rslt = true;
    }
    return rslt;
}


