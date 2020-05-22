/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_ipc.c
    \brief IPC traffic manipulation commands

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include <hm_api.h>
#include "hartfunc.h"
#include "hartcmd.h"
#include "bufutils.h"
#include "ffhartdef5.h"
#include "mnassert.h"
#include <hw_if.h>

s8_least hartcmd_ManipulateIPCtraffic(const u8 *src, u8 *dst)
{
    s8_least rsp = HART_NO_COMMAND_SPECIFIC_ERRORS;
    UNUSED_OK(dst);
    const Req_ManipulateIPCtraffic_t *s = (const void *)src;
    IPC_MangleEnum_t m = (IPC_MangleEnum_t)util_GetU8(s->IPC_Mangle[0]);
    switch(m)
    {
        case DisablePeriodicTraffic: //Disable regular IPC traffic
            HART_set_active(DEACTIVATE, DEACTIVATE);
            break;
        case EnablePeriodicTraffic: //Enable regular IPC traffic
            HART_set_active(ACTIVATE, ACTIVATE);
            break;
        default:
            rsp = HART_INVALID_SELECTION;
            break;
    }
    return rsp;
}

s8_least hartcmd_ReadAndResetIPCtimers(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
#if INSTRUM_HM_TIMERS == OPTION_ON
    adaptimers_t t;
    adaptimers_ReadAndReset(&t);
    Rsp_ReadAndResetIPCtimers_t *d = (void *)dst;
    util_PutU16(d->IPC_TimeSend[0], t.time_send);
    util_PutU16(d->IPC_TimeWait[0], t.time_wait);
    util_PutU16(d->IPC_TimeReceive[0], t.time_receive);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
#else
    UNUSED_OK(dst);
    return COMMAND_NOT_IMPLEMENTED;
#endif
}

s8_least hartcmd_ReadAndResetIPCstatistics(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
#if INSTRUM_IPC == OPTION_ON
    ipcstat_t t;
    instrum_ipc_ReadAndReset(&t);
    Rsp_ReadAndResetIPCstatistics_t *d = (void *)dst;
    util_PutU16(d->IPC_MaxBetweenSends[0], t.senddiff);
    util_PutU16(d->IPC_MaxBetweenReceives[0], t.rcvdiff);
    util_PutU16(d->IPC_MaxRoundtrip[0], t.roundtrip);
    util_PutU16(d->IPC_WildCount[0], t.wild);
    util_PutU16(d->IPC_LostCount[0], t.lost);
    util_PutU16(d->IPC_ReinitsCount[0], t.reinits);
    util_PutU32(d->IPC_SendCount[0], t.total);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
#else
    UNUSED_OK(dst);
    return COMMAND_NOT_IMPLEMENTED;
#endif
}

s8_least hartcmd_ControlIPCUART(const u8 *src, u8 *dst)
{
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    const Req_ControlIPCUART_t *s = (const void *)src;
    UNUSED_OK(dst);
    MN_ENTER_CRITICAL(); //Necessary for the API used
        switch(util_GetU8(s->IPC_UART_Command[0]))
        {
            case DisableIPCComm:
                hm_kill_uart();
                break;
            case EnableIPCComm:
                HART_Init();
                break;
            case IPCPanic:
                sysio_ShowCrash(NULL, 0);
                break;
            default:
                ret = HART_INVALID_SELECTION;
                break;
        }
    MN_EXIT_CRITICAL();
#if 0
    if(ret != HART_INVALID_SELECTION)
    {
        osif_set_event(HM_TASK_ID, HART_START_EVENT); //nudge it
    }
#endif
    return ret;
}

//Top-level command
s8_least hartcmd_FFPInfo(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return -HART_NO_COMMAND_SPECIFIC_ERRORS;
}
/* This line marks the end of the source */

