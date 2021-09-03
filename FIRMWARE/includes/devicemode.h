/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file devicemode.h
    \brief public interfaces of device mode manager

     CPU: Any

    OWNER: AK

    \ingroup Modeman
*/
#ifndef DEVICEMODE_H_
#define DEVICEMODE_H_
#include <limits.h>
#include "errcodes.h"
/*-------------- device mode types ---------------*/
//AK: future lint -strong(AJX, devmode_t)
typedef u8 devmode_t; //! MSByte=mode LSB=submode
typedef u8 devsubmode_t; //! A comatibility alias

#include "posctlmode.h"
#include "faultdef.h" //for users of fwords

typedef enum devmodebit_t
{
    MODEBIT_FAILSAFE,
    MODEBIT_SETUP,
    MODEBIT_MANUAL,
    MODEBIT_OPERATE,
    MODEBIT_TOTAL //must be the last
} devmodebit_t;

#define MODEMAP(modebit) ((devmode_t)(1U<<(u32)(modebit)))

#define MODE_SETUP        MODEMAP(MODEBIT_SETUP)
#define MODE_MANUAL       MODEMAP(MODEBIT_MANUAL)
#define MODE_OPERATE      MODEMAP(MODEBIT_OPERATE)
#define MODE_FAILSAFE     MODEMAP(MODEBIT_FAILSAFE)
#define MODE_INVALID      ((devmode_t)0x00) //! No special meaning

//BIG NOTE: Submode is a bitwise OR of (some of) those flag bits!
#define SUBMODE_NORMAL   ((devsubmode_t)0x0000)
#define SUBMODE_LOWPOWER ((devsubmode_t)0x00010)
#ifdef FAULT_MARGINAL_POWER
  #define SUBMODE_MARGINAL_POWER ((devsubmode_t)0x0080U) //! an artificial indicator of marginal power for ValVue
#endif
#define SUBMODE_FAILED_HIGH ((devsubmode_t)0x0040U) //! an artificial indicator of failhigh faults for ValVue
#ifdef FAULT_ESD_TRIP
  #define SUBMODE_ESD_TRIP ((devsubmode_t)0x0020U) //! an artificial indicator of ESD trip faults for ValVue
#endif
//lint -sem(mode_GetMode, pure)
extern devmode_t mode_GetMode(void);
//lint -sem(mode_GetSubmode, pure)
extern devsubmode_t mode_GetSubmode(void);

extern ErrorCode_t mode_SetModeInterface(devmode_t dmode); //For external interfaces
extern ErrorCode_t mode_SetMode(devmode_t dmode); //discouraged for setting normal mode

MN_DECLARE_API_FUNC(mode_SetModeEx) //Not all projects requre temporary mode change
extern ErrorCode_t mode_SetModeEx(devmode_t dmode, bool_t save);

extern ErrorCode_t mode_SetNormalMode(void);

extern void mode_ClearLowPower(void);

//Implementation is project-dependent so Doxygen header is here at the point of declaration
/** \brief A wrapper function encapsulating actions required on device mode change
MUST be called from within a critical section.
\param newmode - new device mode
\return true iff mode change is allowed
*/
extern bool_t mode_TransitionHook(devmode_t newmode);

typedef struct ModeData_t
{
    devmode_t mode; //!< the mode of the device
    devmode_t tmode; //!< the mode to return to after unusual conditions go away
    u16 CheckWord;
} ModeData_t;

//Target mode save business
SAFEGET(mode_GetModeData, ModeData_t);
//Temporary compatibiilty
#define TypeUnsafe_mode_InitTargetMode TypeUnsafe_mode_SetModeData
#define TypeUnsafe_mode_GetTargetMode TypeUnsafe_mode_GetModeData

//But do not provide safe wrapper for "Set" - it is needed only to "commit" data to NVMEM
extern ErrorCode_t TypeUnsafe_mode_SetModeData(const void *src);

extern void mode_Mopup(void);

/** \brief Returns effective device mode, backward-compatible
\param mode - local device mode
\return effective device mode
*/
extern devmode_t mode_GetEffectiveMode(devmode_t mode);

#endif //DEVICEMODE_H_
/* This line marks the end of the source */
