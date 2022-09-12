/*
Copyright 2004-2006 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup MainIdle  Main C startup and System Idle task
\brief Main C startup module and System Idle task
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_Main_Module.doc"> Design document </a><br>
<a href="../../../Doc/TestDocs/utplan_main_idle.doc"> Unit Test Report </a><br>
\endhtmlonly
*/
/**
    \file mncbmain1.c
    \brief Main C startup module

    CPU: Any, with MNCB-like electronics

    OWNER: Ernie Price

    \ingroup MainIdle
*/
#include "projectdef.h"
#include "mnwrap.h" //for intrinsic functions used by the OS port
#include "oswrap.h"
//#include "errcodes.h"
#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_LCD
#include "lcd.h"
#endif
#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_SIMPLE
#include "led.h"
#include "quad.h"
#include "digital_pot.h"
#endif

#include PWM_H_
#include "inituc.h"

#if FEATURE_AO == FEATURE_AO_SUPPORTED
#include "da.h"
#endif

#include "ad.h"
#include "fram.h"
#include "i2c.h"
#include "key.h"
#include "watchdog.h"
#include "syswd.h"
#include "spi.h"

#include "bsp.h"
#include "uipublic.h"
#include "reset.h"

#include "faultpublic.h"

#include "mncbdefs.h"
#include "mnassert.h"

#include "facdefaults.h"
#include "nvram.h"


/** \brief Performs all BIOS intitialization by calling the initialize code
    for all relevant drivers.
*/
static void bios_Init(void)
{
#if FEATURE_CPU == FEATURE_CPU_LPC21x4
// This function has to be called for LPC21x4 family of microcontrollers
    bsp_Init();                                 //   bios_InitTimer0();
#endif

    idle_EstimateTime();

    /*
        N.B. The internal watchdog cannot be active during debugging. In a
        release build it is unconditionally enabled, in a debug build it is
        enabled when the date string is valid (!=MNCB_DEFAULT_DATE_STRING[0]).
    */
#if !defined NDEBUG
    if (VerString[0].date_str[0] != (u8)MNCB_DEFAULT_DATE_STRING[0])
#endif
    {
#if USE_INTERNAL_WATCHDOG == OPTION_ON
        wdog_WatchdogInit();
#endif
    }

    i2c_Initialize();
    fram_Initialize();

#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_LCD
    bios_InitKeyboardDriver();
#endif
    spi_Initialize();       // does both SPI controllers

#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_SIMPLE
    DigitalResistor_Initialize();
    bios_InitPushbuttons();
    LED_Initialize();
    quad_Initialize();
#endif

#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_LCD
    bios_InitLcd(true);     // separated from bios_UpdateLcd() below to allow
                            // stabilize time of the follower/booster
#endif

#if FEATURE_AO == FEATURE_AO_SUPPORTED
    bios_InitDa();
#endif

    bios_InitTimer1();

    bios_InitAd();

#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_LCD
    bios_LcdSetContrast(LCD_DEFAULT_CONTRAST, true); //turn the display on
    ui_init();
    bios_UpdateLcd();       //  sysio_UpdateLcd() is not yet ready to run
#else
    ui_init();
#endif
}

/** \brief the main C startup code - enter from bsp_a.s79
*/
void  main (void)
{
    UNUSED_OK(mychecksum);          // get rid of global Lint warning

#if (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
// This function has to be called for STM32F12x devices
// initialize the clocks very early in the reset sequence.
// This function should not be called for LPC devices
    wdog_WatchdogTrigger();         // Tickle external WD - note that GPIOs are already initialized by the function above

    stm_SystemInit();               // Initialization specific for STM microcontroller clock
#endif

    sysio_InitPwm();                 // fast PWM init for in-place reset

    error_PreInit();

    bios_Init();                    // initialize the BIOS

    mn_InitAssert();                // must be as early as possible in case anyone clears the trap record
    syswd_Init(); //Can't be before mn_InitAssert; hopefully, internal watchdog won't kick in in this deterministic part

    OSInit();                       // Initialize uC/OS-II

    /* We modify initiaization policy in the interest of defensive programming.
    If we come out of firmware activation and encounter NVMEM fault, the culprit is
    a bug in NVMEM translation. Instead of rendering the device unusable, we revert
    to the previous firmware thereby failing the activation - on this, side (APP).

    FFP should detect the APP revert and fail the activation
    */
    wdog_WatchdogTrigger();
    //In phase 1, initialize only the stuff needed only to decide if activation failed
    reset_OnReset();
    wdog_WatchdogTrigger();

    //Have we been activating?
    bool_t activating = !error_IsFault(FAULT_NVM_CHECKSUM0);
    if(activating) //Lint's crooked notion of &&; doesn't recognize pure semanicts
    {
        activating = facdef_GetState(NULL)->first_time;
    }
    //Phase 2 init
    ram_InitPass(NVMFLAG_INIT_2, wdog_WatchdogTrigger);

    if(activating && error_IsFault(FAULT_NVM_CHECKSUM0))
    {
        //blame it on NVMEM translation and prepare to revert
        error_SetFault(FAULT_REVERTFW_NV);
    }

    oswrap_OSStart();
}

/* This line marks the end of the source */
