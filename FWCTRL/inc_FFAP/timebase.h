/*
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file timebase.h
    \brief All time-related definitons

     CPU: Any

    OWNER: EP
*/
#ifndef TIMEBASE_G_
#define TIMEBASE_G_

#include <tmbase_proj.h>
//---------------------------------------------------

#define ASSERT_LIFESPAN     (MN_MS2TICKS(20000u)) //! Time to live for an assert record (now 20 seconds)

//-------------------------------------------------------------------

//-------------------------------------------------------------------

#define ONE_SECOND      1000u
#define TICK_MS         (ONE_SECOND / LCL_TICKS_PER_SEC)
#define CTRL_TASK_DIVIDER 3u        //! number of timer ticks per control task cycle
#define CYCLE_TASK_DIVIDER 4U        //! number of control task cycles per cycle task cycle

#define COMPUTE_COEFF_INTERVAL  1000u // in milliseconds
#define COMPUTE_COEFF_DIVIDER\
    (COMPUTE_COEFF_INTERVAL / ((CTRL_TASK_DIVIDER * CYCLE_TASK_DIVIDER) * TICK_MS))


#define LCL_TICKS_PER_SEC 200u

//lint -esym(755, TB_TICKS_PER_SEC) Lint doesn't see use in os_cfg.h
#define TB_TICKS_PER_SEC ((LCL_TICKS_PER_SEC / CTRL_TASK_DIVIDER) + 1U)

#define TB_MS_PER_TICK     (1000u / LCL_TICKS_PER_SEC)

#ifndef _MSC_VER
//#   define MN_MS2TICKS(t) ((u16)((t) / TB_MS_PER_TICK)) //real target
#   define MN_MS2TICKS(t) ((u16)((t) / TB_MS_PER_TICK)) //real target
#else
#   define MN_MS2TICKS(t) ((u16)((t)* CLOCKS_PER_SEC/1000u)) //PC build; requires <time.h>
#endif

//lint ++flb useful shorthands - not all need be used
#define T0_050   MN_MS2TICKS(    50u)
#define T0_100   MN_MS2TICKS(   100u)
#define T0_150   MN_MS2TICKS(   150u)
#define T0_250   MN_MS2TICKS(   250u)
#define T0_500   MN_MS2TICKS(   500u)
#define T0_750   MN_MS2TICKS(   750u)
#define T1_000   MN_MS2TICKS(  1000u)
#define T1_500   MN_MS2TICKS(  1500u)
#define T2_000   MN_MS2TICKS(  2000u)
#define T2_500   MN_MS2TICKS(  2500u)
#define T3_000   MN_MS2TICKS(  3000u)
#define T4_000   MN_MS2TICKS(  4000u)
#define T5_000   MN_MS2TICKS(  5000u)
#define T20_000  MN_MS2TICKS( 20000u)
#define T100_000 MN_MS2TICKS(100000u)
#define T120_000 MN_MS2TICKS(120000u)
//lint --flb

//By design, output calc occurs when all A/D channels are read, which occurs every control cycle
#define CTRL_CALCULATION_INTERVAL_MS CTRL_TASK_PERIOD //! period of output calc

typedef s16 ctltick_t; //!< count time in control cycles

#if 0 //for compile-time verification
#define CTRL_TASK_PERIOD 15 //! nominal period of control task in ms
CONST_ASSERT(TB_MS_PER_TICK*CTRL_TASK_DIVIDER == CTRL_TASK_PERIOD);
#else
#define CTRL_TASK_PERIOD (TB_MS_PER_TICK*CTRL_TASK_DIVIDER) //! nominal period of control task in ms
#endif

#endif //TIMEBASE_G_

/* This line marks the end of the source */
