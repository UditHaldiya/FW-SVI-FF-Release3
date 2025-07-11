/*
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file i2c_drv.h
    \brief  Device-specific particulars of i2c and fram connection

NOTE: May also contain lower-level bios dependencies, including those that don't
really need to be different.

    CPU: Any

    OWNER: AK

    \ingroup bios
*/
#include "gpio.h"
#include "timebase.h"
#include "stm_periph.h"

#define I2C1_BASE               (APB1PERIPH_BASE + 0x5400u)
//#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800u)
#define I2C1                    HARDWARE(I2C_TypeDef *, I2C1_BASE)


#define FRAM_I2C_FREQ 0x2u // 2 mhz

#define RESET_DURATION      (CORE_FREQ / 100000u)      // duration
#define I2C_PRESCALE        10           // PCLK1 / 2 / I2C_PRESCALE == 100000
#define TRISE_VAL           ((PCLK1_FREQ / 1000000u) + 1u)

#define FRAM_I2C I2C1

// if this fails need to reevaluate the timer = 32 in the implementation
CONST_ASSERT ((CORE_FREQ == 2000000u) && (PCLK2_FREQ == 2000000u));

//lint ++flb
typedef struct
{
    IO_REG32(CR1);
    IO_REG32(CR2);
    IO_REG32(OAR1);
    IO_REG32(OAR2);
    IO_REG32(DR);
    IO_REG32(SR1);
    IO_REG32(SR2);
    IO_REG32(CCR);
    IO_REG32(TRISE);
} I2C_TypeDef;
//lint --flb

/* This line marks the end of the source */
