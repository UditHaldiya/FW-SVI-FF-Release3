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
#include "stm32f10x.h"
#include "hw_cfg.h"

#define FRAM_I2C_FREQ 0x4u // 4 mhz

//#define PCLK1_FREQ_          (CPU_FREQ)
#define RESET_DURATION      (CPU_FREQ / 100000u)      // duration
#define I2C_PRESCALE        20           // PCLK1 / 2 / I2C_PRESCALE == 100000
#define TRISE_VAL           ((CPU_FREQ / 1000000u) + 1u)

#define     FRAM_I2C I2C2

// FRAM Write Enable and Disable code
#define FRAM_Write_Enable() (GPIOB->ODR &= (u16)~0x1000U) /* set GPIOB Pin12 to 0 */
#define FRAM_Write_Disable() (GPIOB->ODR |= (u16)0x1000U) /* set GPIOB Pin12 to 1 */
#define gpio_I2C_SDAState() ((GPIOB->IDR & (1u << 11)) != 0)

#define I2C_DIAGNOSTIC_OFF          (0u)
#define I2C_DIAGNOSTIC_ON           (1u)
#define I2C_DIAGNOSTIC_STATE        (I2C_DIAGNOSTIC_ON)


/** \brief Change the mode of the I2C1 SDA pin to GPIO or Alternate according to the
    passed parameter.  This is used by the I2C driver to free the controller if it
    was reset during a read operation (e.g. FRAM read).  Note that gpio_PortInit set
    the ODR for pin SDA to 0.  So toggling back and forth between Alternate and GPIO
    will issue I2C clocks unless something is holding the SDA line low.

    \param on - true the pin is set to GPIO, false the pin is set to Alternate mode.
*/
MN_INLINE void gpio_I2C_SetI2cClk(bool_t on)
{
    if(on)
    {
        GPIOB->CRH &= ~(0x8u << 8);                 // put PB10 in GPIO mode
    }
    else
    {
        GPIOB->CRH |=  (0x8u << 8);                 // put PB10 in Alt mode (I2C)
    }
}
/* This line marks the end of the source */
