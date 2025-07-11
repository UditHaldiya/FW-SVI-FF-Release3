/*
Copyright 2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file instrum_hm.c
    \brief Minimal "hart master" - Just send a request and receive a response

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/

#include "mnwrap.h"
#include <rtos.h>
#include <keywords.h>
#include <base.h>
#include <hm_api.h>

#if INSTRUM_IPC == OPTION_ON
//Some instrumentation
static bool_t wait177=false; //! Indicator of cmd 177 in progress
static u32 sendtime;
static u32 rcvtime;
static bool_t first_send = true;
static bool_t first_rcv = true;

ipcstat_t Atomic_ ipcstat =
{
    .senddiff = 0,
    .rcvdiff = 0,
    .roundtrip = 0,
    .lost = 0,
    .wild = 0,
    .reinits = 0,
    .total = 0,
};

void instrum_ipc_ReadAndReset(ipcstat_t *dst)
{
    MN_ENTER_CRITICAL();
        if(dst != NULL)
        {
            memcpy(dst, &ipcstat, sizeof(*dst));
        }
    MN_EXIT_CRITICAL();
    MN_ENTER_CRITICAL();
        memset(&ipcstat, 0, sizeof(ipcstat));
    MN_EXIT_CRITICAL();
}

void instrum_ipc_PostReceive(void)
{
    u32 prev = rcvtime;
    rcvtime = (u32)OS_GetTime32();
    if(!first_rcv)
    {
        u32 diff = rcvtime - prev;
        diff = MAX(ipcstat.rcvdiff, diff);
        ipcstat.rcvdiff = (u16)MIN(diff, UINT16_MAX);
    }
    first_rcv = false;
    u32 roundtrip = rcvtime - sendtime;
    roundtrip = MAX(ipcstat.roundtrip, roundtrip);
    ipcstat.roundtrip = (u16)MIN(roundtrip, UINT16_MAX);
    if(!wait177)
    {
        ipcstat.wild++;
    }
    wait177 = false;
}

void instrum_ipc_PreSend(void)
{
     u32 prev = sendtime;
    sendtime = (u32)OS_GetTime32();
    if(!first_send)
    {
        u32 diff = sendtime - prev;
        diff = MAX(ipcstat.senddiff, diff);
        ipcstat.senddiff = (u16)MIN(diff, UINT16_MAX);
    }
    first_send = false;

    if(wait177)
    {
        ipcstat.lost++;
    }
    ipcstat.total++;
    wait177 = true;
}

void instrum_ipc_CountReinits(void)
{
    ipcstat.reinits++;
}

#endif //INSTRUM_IPC == OPTION_ON


/* This line marks the end of the source */
