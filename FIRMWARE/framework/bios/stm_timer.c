/**
Copyright 2011 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file stm_timer.c

    \brief Driver for timers in the STM32F10xx CPU.  Currently used for
    PWM mode for the D/A I/P output and also for PWM mode control of
    the digital outputs DO_1, DO_2.  Note: the system tick timer is handled
    elsewhere.

    OWNER:
    CPU: STM32F10xx Cortex

    $Revision:  $
*/
#include "mnwrap.h"
#include "watchdog.h"
#include "stm_timer.h"



//----------------------------------------------------------------------------
// Profiler timer controls

#ifdef TIMER1_NOT_AVAILABLE                 // Profiler

#define PRF_DISABLE_TIMER       (0x00u)
#define PRF_CONFIG_TIMER_OFF    (PRF_DISABLE_TIMER | URS_OF)
#define PRF_START_TIMER         (PRF_CONFIG_TIMER_OFF | CEN)

#endif
//----------------------------------------------------------------------------


#if USE_INTERNAL_WATCHDOG == OPTION_ON
/** \brief use timer 5 to measure the time between four successive ticks of
    the nominal 40 khz RC oscillator.

    \return u32 - the rounded average time for one tick (nominal 50 timer ticks)
*/
static u32 measure40khz(void)
{
    u32 x, y = 0u;
    u32 snap;

    for(x = 0; x < 5; x++)              // count off 5 LSI events
    {
        while ((TIM5->SR & 0x10u) == 0u)  // wait here for an LSI event
        {
        }
        TIM5->SR &= (u16)~0x10u;        // reset event in timer 5
        snap = TIM5->CCR4;              // Capture the timer
        switch (x)
        {
            case 0:
                y = snap;               // get start timer 5 value
                break;
            case 4:
                y = snap - y;           // comput 4 LSI event interval
                break;
            default:
                //Do nothing
                break;
        }
    }
    return (y + 2) / 4;                 // round and divide by 4
}

/** \brief Measure the frequency of the internal Low Speed Oscillator
    \param CPU clock frqeuency, Hz
    \return the low-speed osc. frequency in hertz
*/
u32 tmr_GetLSIFreq(void)
{
    u32 TimeFor1tick;
    u32 LSIFreq;

    TIM5->CR1   = 0;                            // reset command register 1
    TIM5->CR2   = 0;                            // reset command register 2
    TIM5->PSC   = 0;                            // set prescaler
    TIM5->ARR   = 0xffff;                       // set max count interval

    TIM5->CR1  |= (u16)URS_OF;                  //

    TIM5->CCMR1 = 0;
    TIM5->CCMR2 = CCxS_1 << CCMR_SFT_2;         // chan 4 is input, IC1 is mapped on TI1.
    TIM5->CCER  = CCxE << CCER_SFT_4;           // set capture/compare enable register
    TIM5->EGR   = UG;                           // Generate Update
    TIM5->CR1  |= (u16)CEN;                     // enable timer

    TimeFor1tick = measure40khz();
    if (TimeFor1tick != 0u)
    {
        LSIFreq = PCLK1_FREQ / TimeFor1tick;
    }
    else
    {
        LSIFreq = 0u;                           // Will cause an error
    }

    return LSIFreq;
}
#endif


#ifdef TIMER1_NOT_AVAILABLE                 // Profiler
/** \brief Configure Timer TIM4 PROFILER timer.
 *  For profiling purposes!
 Single 16-bit timer: TIM4
 Prescaler is set to 19 (divide by 20)
 2MHz clock / 20 -- 1 tick is 10 us

 Function does not retuirn anything, does not receive parameters.

 The function shall exist but the code could be commented.
*/
void PRF_InitTimer(void)
{

    TIM4->CR1   = PRF_DISABLE_TIMER;        // reset command register 1
    TIM4->CR2   = 0u;

    // Now the timer is disabled!
    // Proceed with Initialization
    TIM4->CCMR1 = 0u;
    TIM4->CCMR2 = 0u;                       // chan 4 is input, IC1 is mapped on TI1.
    TIM4->CCER  = 0u;                       // set capture/compare enable register
    TIM4->SMCR  = 0u;

    TIM4->PSC   = 19u;                      // set prescaler to divide by 20, 10us per tick
    TIM4->ARR   = 0xffffu;                  // set max count interval
    TIM4->CR1   = PRF_CONFIG_TIMER_OFF;     // Event control

    TIM4->EGR   = UG;                       // Generate Update

    TIM4->CR1   = PRF_START_TIMER;          // enable timer

}
#endif                                      // End Profiler --

#ifdef TIMER1_NOT_AVAILABLE                 // Profiler
/** \brief Configure Timer TIM4 as Profiler timer.
 *  For profiling purposes!
    \return u16 - the 16-bit Ticks counter -- TIM4
*/
u16 instrum_GetHighResolutionTimer(void)
{
    u16 TempLO;

    TempLO = TIM4->CNT;
    return TempLO;
}
#endif



// end of source
