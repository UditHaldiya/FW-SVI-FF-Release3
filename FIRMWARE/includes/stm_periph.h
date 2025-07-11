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

    \brief STM STM32F10xx peripherals map

    OWNER:
    CPU: STM32F10xx Cortex

*/
#ifndef STM_PERIPH_H_
#define STM_PERIPH_H_

#define PERIPH_BASE           0x40000000u
#define APB1PERIPH_BASE       (PERIPH_BASE + 0u)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000u)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000u)

#define IO_REG16(x)  volatile u16 x; u16 CAT(x,dummy)
#define IO_REG32(x)  volatile u32 x


#endif //STM_PERIPH_H_
/* This line marks the end of the source */
