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

    \brief Coretex M3 core peripherals API

    OWNER:
    CPU: STM32F10xx Cortex

*/
#ifndef CM3CORE_H_
#define CM3CORE_H_

#include "stm_periph.h"

#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */

//lint -esym(768,SCB_t::*) Not accessed member OK for a memory-mapped peripheral (would be 754 if SCB_t were local to a .c file)
typedef volatile struct SCB_t
{
    IO_REG32(CPUID);                   /*!< Offset: 0x000 (R/)  CPU ID Base Register                                  */
    IO_REG32(ICSR);                    /*!< Offset: 0x004 (R/W)  Interrupt Control State Register                      */
    const struct vectors_t *volatile VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
    IO_REG32(AIRCR);                   /*!< Offset: 0x00C (R/W)  Application Interrupt / Reset Control Register        */
#if 0
#define SCB_AIRCR_VECTKEY_Pos              16                                             /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */
#define SCB_AIRCR_PRIGROUP_Pos              8                                             /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */
#endif //0
#define SCB_AIRCR_SYSRESETREQ               ((u32)0x00000004)        /*!< Requests chip control logic to generate a reset */

    IO_REG32(SCR);                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
    IO_REG32(CCR);                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
    u8      SHP[12];                   /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    IO_REG32(SHCSR);                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
    IO_REG32(CFSR);                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
    IO_REG32(HFSR);                    /*!< Offset: 0x02C (R/W)  Hard Fault Status Register                            */
    IO_REG32(DFSR);                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
    IO_REG32(MMFAR);                   /*!< Offset: 0x034 (R/W)  Mem Manage Address Register                           */
    IO_REG32(BFAR);                    /*!< Offset: 0x038 (R/W)  Bus Fault Address Register                            */
    IO_REG32(AFSR);                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
    IO_REG32(PFR[2]);                  /*!< Offset: 0x040 (R/)  Processor Feature Register                            */
    IO_REG32(DFR);                     /*!< Offset: 0x048 (R/)  Debug Feature Register                                */
    IO_REG32(ADR);                     /*!< Offset: 0x04C (R/)  Auxiliary Feature Register                            */
    IO_REG32(MMFR[4]);                 /*!< Offset: 0x050 (R/)  Memory Model Feature Register                         */
    IO_REG32(ISAR[5]);                 /*!< Offset: 0x060 (R/)  ISA Feature Register                                  */
} SCB_t;

#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */
#define SCB                 HARDWARE(SCB_t *, SCB_BASE)         /*!< SCB configuration struct          */


#endif //CM3CORE_H_
/* This line marks the end of the source */
