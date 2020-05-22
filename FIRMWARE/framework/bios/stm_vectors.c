/**
Copyright 2011 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file stm_vectors.c

    \brief The ARM Cortex and NVIC vector table for the STM32F10xx CPU

    OWNER:
    CPU: STM32F10xx Cortex

    $Revision:  $
*/
#include "mnwrap.h"
#include "serial.h"
#include "stmcommon.h"
#include "gpio.h"
#include "cortextrap.h"
#include "bsp.h"
#include "stm_systick.h"
#include "stm_vectors.h"

#pragma language=extended
#pragma segment="CSTACK"

#define TRAP1   Cortex_Trap
#define TRAP2   NVIC_Trap

#pragma section=".intvec"
#pragma location=".intvec"

const  vectors_t __vector_table =
{
    .stackPtr = __sfe("CSTACK"),                                   //  0, Initial Stack Pointer
    .Fnct =
    {
        [1-1] = __iar_program_start,                            //  1, PC start value.
        [2-1] = TRAP1,                                          //  2, NMI.
        [3-1] = TRAP1,                                          //  3, Hard Fault.
        [4-1] = TRAP1,                                          //  4, Memory Management.
        [5-1] = TRAP1,                                          //  5, Bus Fault.
        [6-1] = TRAP1,                                          //  6, Usage Fault.
        [7-1] = TRAP1,                                          //  7, Reserved.
        [8-1] = TRAP1,                                          //  8, Reserved.
        [9-1] = TRAP1,                                          //  9, Reserved.
        [10-1] = TRAP1,                                          // 10, Reserved.
        [11-1] = TRAP1,                                          // 11, SVCall.
        [12-1] = TRAP1,                                          // 12, Debug Monitor.
        [13-1] = TRAP1,                                          // 13, Reserved.
        [14-1] = PendSV_Handler,                                 /* 14, PendSV Handler.                                  */
        [15-1] = SysTick_Handler,                                // 15, uC/OS-II Tick ISR Handler.

        // Peripheral (NVIC) interrupts
        [0+15] = TRAP2,                                          // 16, INTISR[  0]  Window Watchdog.
        [1+15] = TRAP2,                                          // 17, INTISR[  1]  PVD through EXTI Line Detection.
        [2+15] = TRAP2,                                          // 18, INTISR[  2]  Tamper Interrupt.
        [3+15] = TRAP2,                                          // 19, INTISR[  3]  RTC Global Interrupt.
        [4+15] = TRAP2,                                          // 20, INTISR[  4]  FLASH Global Interrupt.
        [5+15] = TRAP2,                                          // 21, INTISR[  5]  RCC Global Interrupt.
        [6+15] = TRAP2,                                          // 22, INTISR[  6]  EXTI Line0 Interrupt.
        [7+15] = TRAP2,                                          // 23, INTISR[  7]  EXTI Line1 Interrupt.
        [8+15] = TRAP2,                                          // 24, INTISR[  8]  EXTI Line2 Interrupt.
        [9+15] = TRAP2,                                          // 25, INTISR[  9]  EXTI Line3 Interrupt.
        [10+15] = TRAP2,                                          // 26, INTISR[ 10]  EXTI Line4 Interrupt.
        [11+15] = TRAP2,                                          // 27, INTISR[ 11]  DMA Channel1 Global Interrupt.
        [12+15] = TRAP2,                                          // 28, INTISR[ 12]  DMA Channel2 Global Interrupt.
        [13+15] = TRAP2,                                          // 29, INTISR[ 13]  DMA Channel3 Global Interrupt.
        [14+15] = TRAP2,                                          // 30, INTISR[ 14]  DMA Channel4 Global Interrupt.
        [15+15] = TRAP2,                                          // 31, INTISR[ 15]  DMA Channel5 Global Interrupt.
        [16+15] = TRAP2,                                          // 32, INTISR[ 16]  DMA Channel6 Global Interrupt.
        [17+15] = TRAP2,                                          // 33, INTISR[ 17]  DMA Channel7 Global Interrupt.
        [18+15] = TRAP2,                                          // 34, INTISR[ 18]  ADC1 & ADC2 Global Interrupt.
        [19+15] = TRAP2,                                          // 35, INTISR[ 19]  USB High Prio / CAN TX  Interrupts.
        [20+15] = TRAP2,                                          // 36, INTISR[ 20]  USB Low  Prio / CAN RX0 Interrupts.
        [21+15] = TRAP2,                                          // 37, INTISR[ 21]  CAN RX1 Interrupt.
        [22+15] = TRAP2,                                          // 38, INTISR[ 22]  CAN SCE Interrupt.
        [23+15] = TRAP2,                                          // 39, INTISR[ 23]  EXTI Line[9:5] Interrupt.
        [24+15] = TRAP2,                                          // 40, INTISR[ 24]  TIM1 Break  Interrupt.
        [25+15] = TRAP2,                                          // 41, INTISR[ 25]  TIM1 Update Interrupt.
        [26+15] = TRAP2,                                          // 42, INTISR[ 26]  TIM1 Trig & Commutation Interrupts.
        [27+15] = TRAP2,                                          // 43, INTISR[ 27]  TIM1 Capture Compare Interrupt.
        [28+15] = TRAP2,                                          // 44, INTISR[ 28]  TIM2 Global Interrupt.
        [29+15] = TRAP2,                                          // 45, INTISR[ 29]  TIM3 Global Interrupt.
        [30+15] = TRAP2,                                          // 46, INTISR[ 30]  TIM4 Global Interrupt.
        [31+15] = TRAP2,                                          // 47, INTISR[ 31]  I2C1 Event  Interrupt.
        [32+15] = TRAP2,                                          // 48, INTISR[ 32]  I2C1 Error  Interrupt.
        [33+15] = TRAP2,                                          // 49, INTISR[ 33]  I2C2 Event  Interrupt.
        [34+15] = TRAP2,                                          // 50, INTISR[ 34]  I2C2 Error  Interrupt.
        [35+15] = TRAP2,                                          // 51, INTISR[ 35]  SPI1 Global Interrupt.
        [36+15] = TRAP2,                                          // 52, INTISR[ 36]  SPI2 Global Interrupt.
        [37+15] = UART1_IRQHandler,                               // 53, INTISR[ 37]  USART1 Global Interrupt.
        // Temporalily Set the UART 2 IRQ Handler
        [38+15] = UART2_IRQHandler,                               // 54, INTISR[ 38]  USART2 Global Interrupt.
        [39+15] = TRAP2,                                          // 55, INTISR[ 39]  USART3 Global Interrupt.

        [40+15] = EXTI_IRQHandler,                                // 56, INTISR[ 40]  EXTI Line [15:10] Interrupts.

        [41+15] = TRAP2,                                          // 57, INTISR[ 41]  RTC Alarm EXT Line Interrupt.
        [42+15] = TRAP2,                                          // 58, INTISR[ 42]  USB Wakeup from Suspend EXTI Int.
        [43+15] = TRAP2,                                          // 59, INTISR[ 43]  TIM8 Break Interrupt.
        [44+15] = TRAP2,                                          // 60, INTISR[ 44]  TIM8 Update Interrupt.
        [45+15] = TRAP2,                                          // 61, INTISR[ 45]  TIM8 Trigg/Commutation Interrupts.
        [46+15] = TRAP2,                                          // 62, INTISR[ 46]  TIM8 Capture Compare Interrupt.
        [47+15] = TRAP2,                                          // 63, INTISR[ 47]  ADC3 Global Interrupt.
        [48+15] = TRAP2,                                          // 64, INTISR[ 48]  FSMC Global Interrupt.
        [49+15] = TRAP2,                                          // 65, INTISR[ 49]  SDIO Global Interrupt.
        [50+15] = TRAP2,                                          // 66, INTISR[ 50]  TIM5 Global Interrupt.
        [51+15] = TRAP2,                                          // 67, INTISR[ 51]  SPI3 Global Interrupt.
        [52+15] = TRAP2,                                          // 68, INTISR[ 52]  UART4 Global Interrupt.
        [53+15] = Hart_ISR,                               // 69, INTISR[ 53]  UART5 Global Interrupt.
        [54+15] = TRAP2,                                          // 70, INTISR[ 54]  TIM6 Global Interrupt.
        [55+15] = TRAP2,                                          // 71, INTISR[ 55]  TIM7 Global Interrupt.
        [56+15] = TRAP2,                                          // 72, INTISR[ 56]  DMA2 Channel1 Global Interrupt.
        [57+15] = TRAP2,                                          // 73, INTISR[ 57]  DMA2 Channel2 Global Interrupt.
        [58+15] = TRAP2,                                          // 74, INTISR[ 58]  DMA2 Channel3 Global Interrupt.
        [59+15] = TRAP2                                           // 75, INTISR[ 59]  DMA2 Channel4/5 Global Interrups.
    },
    .crcPtr = &mychecksum,
    .dummyPtr = NULL,
    .ExtraData = &APPExtraData,
};

// end of source
