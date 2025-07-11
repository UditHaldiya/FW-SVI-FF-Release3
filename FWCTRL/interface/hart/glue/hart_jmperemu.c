/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_activate.c
    \brief HART glue layer for control (position setpoint) limits

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "hartfunc.h"
#include "hartdef5.h"
#include "bufutils.h"
#include "ff_devicevars.h"

s8_least hartcmd_ReadEmulatedFFSimulationJumper(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadEmulatedFFSimulationJumper_t *d = (void *)dst;
    bool_t bsim = ff_GetLocalFFData(NULL)->SimulationActive;
    FFSimulationEnabledflagEnum_t sim;
    if(bsim)
    {
        sim = FFSim_On;
    }
    else
    {
        sim = FFSim_Off;
    }
    util_PutU8(d->FFSimulationEnabledflag[0], (u8)sim);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_EmulateFFSimulationJumper(const u8 *src, u8 *dst)
{
    Rsp_EmulateFFSimulationJumper_t *d = (void *)dst;
    UNUSED_OK(d->FFSimulationEnabledflag[0]); //rely on framework to fill
#if FFIPC_SELECTION_SIMJUMPER_EMU == FFIPC_OPTIONS_SIMJUMPER_EMU_OPTION_SUPPORTED
    const Req_EmulateFFSimulationJumper_t *s = (const void *)src;
    u8 sim = util_GetU8(s->FFSimulationEnabledflag[0]);
    ErrorCode_t err = ERR_INVALID_PARAMETER;
    if( (sim == (u8)FFSim_On) || (sim == (u8)FFSim_Off))
    {
        FFData_t data;
        (void)ff_GetLocalFFData(&data);
        data.SimulationActive = (sim == (u8)FFSim_On);
        err = ff_RepairSetFFData(&data);
    }
    return err2hart(err);
#else
    UNUSED_OK(src);
    return COMMAND_NOT_IMPLEMENTED;
#endif
}

#if FFIPC_SELECTION_WPJUMPER_EMU == FFIPC_OPTIONS_WPJUMPER_EMU_OPTION_SUPPORTED
static tick_t WriteLockEmuTTL = 0U; //configured value
static tick_t WriteLockCaptureTime = 0U; //time of setting

/** \brief Checks and performs expiration of the emulated HW write-lock jumper
\return remaining time to expiration
*/
tick_t wpjemu_Expire(void)
{
    tick_t since = timer_GetTicksSince(WriteLockCaptureTime);
    tick_t ttl = WriteLockEmuTTL;
    if(since > ttl)
    {
        FFData_t ffdata;
        (void)ff_GetLocalFFData(&ffdata);
        if(ffdata.LockEmu != LockEmu_Disabled)
        {
            //reset
            ffdata.LockEmu = LockEmu_Disabled;
            ErrorCode_t err = ff_RepairSetFFData(&ffdata);
            UNUSED_OK(err); //No way to handle an error but will try next time
        }
        since = ttl;
        WriteLockEmuTTL = 0U;
        WriteLockCaptureTime = 0U;
    }
    return ttl - since;
}
#endif

s8_least hartcmd_ReadHWLockEmulationOption(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadHWLockEmulationOption_t *d = (void *)dst;
#if FFIPC_SELECTION_WPJUMPER_EMU == FFIPC_OPTIONS_WPJUMPER_EMU_OPTION_SUPPORTED
    u8 hwlock = 255U;
    switch(ff_GetLocalFFData(NULL)->LockEmu)
    {
        case LockEmu_Off:
            hwlock = (u8)HWLock_Off;
            break;
        case LockEmu_On:
            hwlock = (u8)HWLock_On;
            break;
        case LockEmu_Disabled:
            hwlock = (u8)HWLock_Disabled;
            break;
        default:
            break;
    }
    util_PutU8(d->HardWriteLockEmulation[0], hwlock);
    tick_t ttl = wpjemu_Expire();
    util_PutU32(d->HardWriteLockEmuTTL[0], ttl);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
#else
    UNUSED_OK(dst);
    return COMMAND_NOT_IMPLEMENTED;
#endif
}

s8_least hartcmd_SetHWLockEmulationOption(const u8 *src, u8 *dst)
{
    Rsp_SetHWLockEmulationOption_t *d = (void *)dst;
    UNUSED_OK(d->HardWriteLockEmulation[0]); //rely on framework to fill
    UNUSED_OK(d->HardWriteLockEmuTTL[0]); //rely on framework to fill
#if FFIPC_SELECTION_WPJUMPER_EMU == FFIPC_OPTIONS_WPJUMPER_EMU_OPTION_SUPPORTED
    const Req_SetHWLockEmulationOption_t *s = (const void *)src;
    u8 emu = util_GetU8(s->HardWriteLockEmulation[0]);
    ErrorCode_t err = ERR_OK;
    LockEmu_t hwlock = LockEmu_Off;
    switch(emu)
    {
        case HWLock_Disabled:
            break;
        case HWLock_Off:
            hwlock = LockEmu_Off;
            break;
        case HWLock_On:
            hwlock = LockEmu_On;
            break;
        default:
            err = ERR_INVALID_PARAMETER;
            break;
    }
    if(err == ERR_OK)
    {
        FFData_t data;
        (void)ff_GetLocalFFData(&data);
        data.LockEmu = hwlock;
        err = ff_RepairSetFFData(&data);
    }
    if(err == ERR_OK)
    {
        WriteLockEmuTTL = util_GetU32(s->HardWriteLockEmuTTL[0]);
        WriteLockCaptureTime = timer_GetTicks();
    }
    return err2hart(err);
#else
    UNUSED_OK(src);
    return COMMAND_NOT_IMPLEMENTED;
#endif
}

/* This line marks the end of the source */
