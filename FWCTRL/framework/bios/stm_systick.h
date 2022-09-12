/*
Copyright 2014 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**

    \file stm_systick.h

    \brief SysTick cell driver API

    OWNER:
    CPU: STM32F10xx Cortex

*/
#ifndef STM_SYSTICK_H_
#define STM_SYSTICK_H_

#include "stm_periph.h"

//lint -esym(768,SysTick_t::*) Not accessed member OK for a memory-mapped peripheral (would be 754 if SCB_t were local to a .c file)
typedef struct SysTick_t
{
    IO_REG32(CTRL);                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
#define SysTick_CTRL_CLKSOURCE_Pos          2                                             /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */
#define SysTick_CTRL_TICKINT_Pos            1                                             /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */
#define SysTick_CTRL_ENABLE_Pos             0                                             /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL << SysTick_CTRL_ENABLE_Pos)               /*!< SysTick CTRL: ENABLE Mask */
    IO_REG32(LOAD);                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
#define SysTick_LOAD_RELOAD_Pos             0                                             /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL << SysTick_LOAD_RELOAD_Pos)        /*!< SysTick LOAD: RELOAD Mask */
    IO_REG32(VAL);                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
    IO_REG32(CALIB);                   /*!< Offset: 0x00C (R/)  SysTick Calibration Register        */
} SysTick_t;

#define SysTick             HARDWARE(SysTick_t *, SysTick_BASE)    /*!< SysTick configuration struct      */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address              */

// NVIC API
extern MN_IRQ void SysTick_Handler(void);
extern void systickdly(u32 clocks);
extern void systickdly_with_start(u32 StartTime, u32 clocks);
extern void SysTick_Config(u32 ticks);

#endif //STM_SYSTICK_H_
/* This line marks the end of the source */
