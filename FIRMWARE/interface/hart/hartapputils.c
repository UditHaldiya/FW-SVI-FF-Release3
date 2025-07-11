/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hartapputils.c
    \brief HART App layer helper utils

     CPU: Any

    \ingroup HART
*/
#include "mnwrap.h"
#include "devicemode.h"
#include "hartcmd.h"
#include "hartdef.h"
#include "faultpublic.h"
#include "hartfunc.h"
#include "hartapputils.h"
#include "bufutils.h"
#include "hartpriv.h"
#include "nvram.h"
#include "hartfuncx.h"
#include "mnhartrsp.h"
#if defined(HART_REV_6) || defined(HART_REV_7)
#include "hartdefx.h"
#endif

static const DeviceModeEnum_t devmode2hart_tab[MODEBIT_TOTAL] =
{
    [MODEBIT_FAILSAFE] = HFailsafe,
    [MODEBIT_SETUP] = HSetup,
    [MODEBIT_MANUAL] = HManual,
    [MODEBIT_OPERATE] = HNormal,
};

static const devmodebit_t hart2devmode_tab[MODEBIT_TOTAL] =
{
    [HFailsafe] = MODEBIT_FAILSAFE,
    [HSetup] = MODEBIT_SETUP,
    [HManual] = MODEBIT_MANUAL,
    [HNormal] = MODEBIT_OPERATE,
};

/** \brief A simple device abstraction wrapper
*/
bool_t hart_IsFactoryCmdEnabled(void)
{
   return error_IsFault(FAULT_FACTORYMODE);
}

/** \brief Convert internal device mode representation to HART device mode representation
*/
u8 hart_FormatDevModeToHART(devmode_t mode)
{
    return devmode2hart_tab[intlog(mode)-1];
}

/** \brief Convert HART device mode representation to internal device mode representation
*/
devmode_t hart_FormatDevModeToInternal(u8 hmode)
{
    if((u32)hmode >= NELEM(hart2devmode_tab))
    {
        return MODE_INVALID;
    }
    return MODEMAP(hart2devmode_tab[hmode]);
}

/**
\brief sets an error if wrong mode
\param ModeFlag - a bitmap OR of (1<<(allowedMode)
ModeAllowed=0 means all modes, ModeAllowed=1 means manual or OOS
*/
s8_least hart_CheckMode(u8 ModeFlag)
{
    devmode_t mode;
    u8 HartError = 0u;

    mode = mode_GetMode();

    if( (HC_MODE_BITMASK(mode) & ModeFlag) == 0U)
    {
        ///not allowed in this mode
        HartError = MNHART5_WRONG_MODE;
    }

    //if factory command, only allow if enabled
    if(!hart_IsFactoryCmdEnabled())
    {
        if( (ModeFlag & HC_FACTORY_COMMAND) != 0)
        {
            ///not allowed in this mode
            HartError = COMMAND_NOT_IMPLEMENTED;
        }
    }

    return HartError;
}

#define FACTORY_OPTIONS_KEY 0xaf0e //! Fixed key to allow factory options write

/** \brief Checks if the attempted factory options write is accompanied
by a valid key
\param key - a 2-byte key
\return true iff the key is valid
*/
bool_t hart_IsFactoryOptionKey(const u8 key[2])
{
    u16 Key = util_GetU16(key);
    return (Key == FACTORY_OPTIONS_KEY);
}

/**
\brief HART component-private wrapper for starting a process
\param procId - a process id
\return A HART return code
*/
s8_least hart_SetProcessCommand(ProcId_t procId)
{
    s8_least ret;
    ErrorCode_t err = process_SetProcessCommand(procId);
    if(err == ERR_OK)
    {
        //no error
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    else if(err == ERR_PROCESS_START)
    {
        ret = HART_BUSY;
    }
    else
    {
        ret = HART_INVALID_SELECTION;
    }
    return ret;
}


/** \brief Retrieves HART request message length by pointer to data.
    It is safer to require that the pointer to data be known to the caller.
    \param rx_data - a pointer to received data in the receive buffer
    \return data length as reported by the receive buffer
*/
u8 hart_GetReqDataLength(const void *rx_data)
{
    u8 len;
    if(rx_data != NULL)
    {
        uintptr_t hdr = (uintptr_t)rx_data - MN_OFFSETOF(receive_hdr_t, data);
        const receive_hdr_t *rx_hdr = (const receive_hdr_t *)hdr;
        len = rx_hdr->bytecount;
    }
    else
    {
        len = 0;
    }
    return len;
}

#if defined(HART_REV_6) || defined(HART_REV_7)
/** \brief determine loop current mode by device mode
*   \param[in]
*   \param[out]
*   \return   loop current mode
*/
u8 hart_GetLoopCurModeByDevMode(void)
{
    u8 loopmode;

     // mode translating
    switch(mode_GetMode())
    {
    case MODE_OPERATE:
        loopmode = (u8)LoopModeEnabled;
        break;
    default:
        loopmode = (u8)LoopModeDisabled;
        break;
    }
    return loopmode;
}

/** \brief determine device mode by loop current mode

NOTE: This version is not good for apps with bumbpless transfer
*   \param[in]  loop current mode
*   \return   error code
*/
ErrorCode_t hart_SetDevModeByLoopCurMode(const u8 loopmode)
{
    ErrorCode_t errcode;

    if ((u8)LoopModeEnabled == loopmode)
    {
        errcode = mode_SetMode(MODE_OPERATE);
    }
    else
    {
        errcode = mode_SetMode(MODE_MANUAL);
    }
    return errcode;
}

#endif //HART 6 or 7
/* This line marks the end of the source */
