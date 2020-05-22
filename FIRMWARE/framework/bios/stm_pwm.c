/**
Copyright 2011 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file stm_pwm.c

    \brief Driver for timers in the STM32F10xx CPU.  Currently used for
    PWM mode for the D/A I/P output and also for PWM mode control of
    the digital outputs DO_1, DO_2.  Note: the system tick timer is handled
    elsewhere.

    OWNER:
    CPU: STM32F10xx Cortex

    $Revision:  $
*/
#include "mnwrap.h"
#include "pwm.h"
#include "gpio.h"
#include "stm_timer.h"



#define PWM_TEST    0
#if PWM_TEST
 #define PWM_WIDTH (6u)
 #define PWM_MSB_BITS (3u)
#else
 #define PWM_WIDTH (16u)
 #define PWM_MSB_BITS (9u)
#endif
#define PWM_LSB_BITS (PWM_WIDTH - PWM_MSB_BITS)
#define PWM_PERIOD ((1u << PWM_MSB_BITS) - 1u)
//#define PWM_MSB_SHFT PWM_LSB_BITS
#define PWM_LSB_SHFT (PWM_MSB_BITS-PWM_LSB_BITS)
#define PWM_LSB_MASK ((1u << (PWM_LSB_BITS + PWM_LSB_SHFT)) - 1u)



CONST_ASSERT(PWM_MSB_BITS >= PWM_LSB_BITS);
#if !PWM_TEST
CONST_ASSERT(PWM_LSB_SHFT == 2u);
CONST_ASSERT(PWM_LSB_MASK == 0x1ffu);
#else
unsigned long a = PWM_MSB_BITS, b = PWM_LSB_SHFT, c = PWM_LSB_MASK;
#endif

// Set PWM to 1900 Hz(/2) vs. 3800 Hz(/1)
// FF is using Divider 0 (/1). For compatibility with SVI 2AP should be 1 (/2)
// #define TIM3_PSC              (0u)
#define TIM3_PSC              (1u)


#define TIM3_ARR              (PWM_PERIOD - 1u)
#define TIM3_CR1              URS_OF
//#define TIM3_CR2              (0u)
#define TIM3_SMCR             (0u)
#define PWM_MODE                (OCxM_6 | OCxPE)
//#define TIM3_CCMR1            (0u)
#define TIM3_CCMR2            ((PWM_MODE << CCMR_SFT_1) | (PWM_MODE << CCMR_SFT_2))          // 54
#define TIM3_CCER             ((CCxE << CCER_SFT_3) | (CCxE << CCER_SFT_4))
//#define TIM3_DIER             (CC3IE | CC4IE)

//----------------------------------------------------------------------------

/** \brief Write the passed 16 bit value to the main PWM for control of the  I/P.
    The value is broken into two parts and fed to channels 3 and 4 of timer 3.

    \param value - the 16 bit unsigned value to be written to the PWM
*/
static void WritePWM(u16_least val)
{
    TIM3->CCR3  = (u16)(val >> PWM_LSB_BITS);
    val         = val << PWM_LSB_SHFT;
    TIM3->CCR4  = ~val & PWM_LSB_MASK;                            //
}


/** \brief configure timer 3 for use as the main PWM.  Channels 3 and 4 are used
*/
static void set3(void)
{
    TIM3->CR1   = 0;                                    // reset command register 1
    TIM3->CR2   = 0;                                    // reset command register 2

    TIM3->PSC   = TIM3_PSC;                           // set prescaler
    TIM3->ARR   = TIM3_ARR;                           // set auto-reload
    WritePWM(0);
    TIM3->CCMR1 = 0;
    TIM3->CCMR2 = TIM3_CCMR2;                         //
    TIM3->CCER  = TIM3_CCER;                          // set capture/compare enable register
    TIM3->SMCR  = TIM3_SMCR;                          // set slave mode control register
    TIM3->CR1   = TIM3_CR1;                           // set command register 1

    TIM3->CR1 |= (u16)CEN;                                   // enable timer
}




static u16 Atomic_ lastVal;

/** \brief Initialize PWM counter, channel 4,5 of PWM outputs and module
    specific variables. PWM output is set to zero.

    \param none
*/
void bios_InitPwm(void)
{
    set3();
}

/** \brief return the current (most recent) raw PWM value

*/
u16 pwm_GetValue(void)
{
    return lastVal;
}


/** \brief output the specified 16 bit value to the dual PWM

    \param[in] u16 value - the PWM value 0..65535
*/
void bios_WritePwm(u16 value)
{
    bool_t  EnableIP;

    lastVal = value;

    EnableIP = (value > (u16)MIN_DA_VALUE);
    bios_SetEnableIP(EnableIP);

    WritePWM(value);
}

// end of source
