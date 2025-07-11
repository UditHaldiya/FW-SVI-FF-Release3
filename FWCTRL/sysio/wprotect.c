/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file wprotect.c
    \brief Device driver write-protect jumper

    CPU: Any

    OWNER: AK

    \ingroup sysio
*/

#include "mnwrap.h"
#include "wprotect.h"
#include "gpio.h"
#include "faultpublic.h"

typedef struct WLock_t
{
    bool_t valid;
    bool_t wlock;
} WLock_t;

static WLock_t WLock =
{
    .valid = false,
    .wlock = false,
};

/** \brief Set external request for write lock
\param wlock - true iff write lock is on
*/
void wprotect_SetExtLock(bool_t wlock)
{
    WLock.wlock = wlock;
    WLock.valid = true;
}

/** \brief Read state of write protect jumper
    \return true = locked, false = unlocked
*/
bool_t sysio_ReadWriteProtectInput(void)
{
    if(error_IsFault(FAULT_IPC_LOST))
    {
        WLock.valid = false;
    }
    bool_t ret;
    if(WLock.valid)
    {
        //The host processor is responsible for deciding
        ret = WLock.wlock;
    }
    else
    {
        ret = gpio_ReadWriteProtectInput();
    }
    return ret;
}

/* End of the source */
