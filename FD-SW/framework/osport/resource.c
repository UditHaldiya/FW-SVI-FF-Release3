/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file resource.c
    \brief resource guardian (mutex handler)

    CPU: Any

    OWNER: AK

    \ingroup Sysio
*/

#include "mnwrap.h"
//#include "errcodes.h"
#include "oswrap.h"
#include "mnassert.h"
#include "resource.h"
#include <base.h>
#include <RTOS.h>

// ------------------------------------------- RTOS abstraction section -------------------------------------
/*lint -esym(457, NvMutex)
because it is embOS API
*/
static OS_RSEMA NvMutex;

//lint -sem(rsrc_Initialize, no_thread)
/** \brief Allocate the FRAM mutex
*/
void rsrc_Initialize(void)
{
    OS_CREATERSEMA(&NvMutex);
}


//lint -sem(rsrc_AcquireMutex, thread_lock)
/**
  \brief  This function acquires the Masoneilan FRAM guardian mutex.
*/
void rsrc_AcquireMutex(void)
{
    if((u8_least)OS_Request(&NvMutex) == 0) //return value 1: Resource was available, now in use by calling task; 0: Resource was not available.
    {
        //Mutex not available
        (void)OS_Use(&NvMutex); //wait; returned value larger than 1 means the resource was already locked by the calling task
    }
} //lint !e456 embOS mutex model uses counting resource semaphore; implementation is per manual


//lint -sem(rsrc_FreeMutex, thread_unlock)
/**
  \brief  This function frees the Masoneilan FRAM guardian mutex.
*/
void rsrc_FreeMutex(void)
{
    OS_Unuse(&NvMutex);
}

#ifndef NDEBUG
/** \brief DEBUG Required implementation prototyped in fram.h
*/
void fram_IsOKtoAccess(void)
{
}
#endif //NDEBUG

/* This line marks the end of the source */
