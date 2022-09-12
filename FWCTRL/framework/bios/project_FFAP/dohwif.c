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
#include "dohwif.h"
#include "inituc.h"
#include "stm_timer.h"


#define DO_MODE                (OCxM_6 | OCxPE) //same as PWM_MODE; see stm_pwm.c

#define DO_PERIOD           (16u)       //PCLK1_FREQ / 16 == 125 khz
#define DO_ON_VALUE         (DO_PERIOD / 2u)
#define DO_OFF_VALUE        (0u)

/** \brief set the specified digital output to the specified state.

    \param param - selector: DO_1 or DO_2
    \param value - true = enabled (FET on) , false = disabled (FET off)
*/
void bios_SetDigitalOutput(u8 param, bool_t value)
{
    if ((param == DO_1) || (param == DO_2))
    {   // Check the param
        volatile u16 *adr = (param == DO_1) ? &TIM2->CCR1 : &TIM2->CCR2;
        u16           val = (value == true) ? DO_ON_VALUE : DO_OFF_VALUE;
        *adr = val;
    }
}

/** \brief set the specified digital output to the specified state.

    \param param - selector: DO_1 or DO_2
    \return true = enabled (FET on) , false = disabled (FET off)
*/
bool_t  bios_GetDigitalOutput(u8 param)
{
    bool_t  RetVal = false;

    if ((param == DO_1) || (param == DO_2))
    {   // Check the param
        const volatile u16 *adr = (param == DO_1) ? &TIM2->CCR1 : &TIM2->CCR2;
        RetVal = (*adr == DO_ON_VALUE);
    }

    return RetVal;
}

/** \brief configure timer 2 for use as drivers for digital outputs.  Channels 1 and 2 are used
*/
static void set2(void)
{
    TIM2->CR1   = 0;                                // reset command register 1
    TIM2->CR2   = 0;                                // reset command register 2
    TIM2->PSC   = 0;                                // set prescaler
    TIM2->ARR   = DO_PERIOD - 1u;                   // set auto-reload
    TIM2->CCMR1 = ((DO_MODE << CCMR_SFT_1) | (DO_MODE << CCMR_SFT_2));                           //
    TIM2->CCMR2 = 0;
    TIM2->CCER  = ((CCxE << CCER_SFT_1) | (CCxE << CCER_SFT_2));    // set capture/compare enable register
    TIM2->SMCR  = 0;
    TIM2->CR1   = URS_OF | CEN;                 // set command register 1

    TIM2->CR1 |= (u16)CEN;                               // enable timer
}


/** \brief configure timer2 so it can be used to drive the digital outputs
*/
void  bios_InitTimer1(void)
{
    set2();
}




bool_t bios_DOCardPresent(void)
{
    return true; //always present
}

// end of source
