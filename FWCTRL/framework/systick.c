/*
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file systick.c
    \brief Handler for the System Tick timer

    OWNER:
    CPU: Cortex-M*

*/
#include "mnwrap.h"
#include "stm_systick.h"
#include "timer.h"

/** \brief Systick Interrupt Handler
  SysTick interrupt happens every 5 ms

[Pulled out of stm_nvic.c to avoid collision with FF's version]
*/

MN_IRQ void SysTick_Handler (void)            /* SysTick Interrupt Handler (5ms)   */
{
    timer_ProcessTick();      // do 5 millisecond things
}
/* This line marks the end of the source */

