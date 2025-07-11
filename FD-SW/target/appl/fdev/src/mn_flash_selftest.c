/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_flash_selftest.c
    \brief functions about flash selftest

    CPU: Any

    OWNER:
    $Date: 08/15/14 13:20p $
    $Revision: 1 $
    $Author: Eric Jiang $

*/
#include <limits.h>
#include <softing_base.h>
#include <hw_if.h>
#include "oswrap.h"
#include "faultpublic.h"
#include "selftest.h"
#include "mn_flash_selftest.h"

/* ========== Simplified faults handler for comaptibility with APP ==========
If it needs to grow, it may well move in a separate file
*/

typedef u16 ff_fault_t; //we may need to grow the size
//lint -esym(749, ff_faultbit_t::*) may or may not be referenced
typedef enum ff_faultbit_t
{
    FF_FAULT_NONE,
    FF_FAULT_FW_CHECKSUM,
    FF_FAULT_TMOUT_FLASH_TEST,
    FF_FAULT_NVM_CHECKSUM0,
    FF_FAULT_NVM_WRITE,
    FF_FAULT_NVM_TEST
} ff_faultbit_t;


//lint -estring(641, ff_faultbit_t) shift RHS can be an enum
static const ff_faultbit_t ff_fault[] =
{
    [FAULT_FW_CHECKSUM] = FF_FAULT_FW_CHECKSUM,
    [FAULT_TMOUT_FLASH_TEST] = FF_FAULT_TMOUT_FLASH_TEST,
    [FAULT_NVM_CHECKSUM0] = FF_FAULT_NVM_CHECKSUM0,
    [FAULT_NVM_WRITE] = FF_FAULT_NVM_WRITE,
    [FAULT_NVM_TEST] = FF_FAULT_NVM_TEST,
};

/** \brief Maps Standard APP fault code to a bitmask corresponding to FFP bit
\param ErrorCode - a Standard fault code
\return a single-bit-bitmap (or 0 if out of range)
*/
static ff_fault_t newfault(faultcode_fast_t ErrorCode)
{
    ff_fault_t ret = 0U;
    if((ErrorCode >= NELEM(ff_fault)) || (ErrorCode == FAULT_NONE))
    {
        //nothing to do
    }
    else
    {
        ff_faultbit_t fault = ff_fault[ErrorCode];

        ret = 1U << fault;
    }
    return ret;
}

typedef struct ff_faults_t
{
    ff_fault_t ff_fault;
    u16 CheckWord;
} ff_faults_t; //!< a simplistic fault storage type

static ff_faults_t ff_faults =
{
    .ff_fault = 0U,
    .CheckWord = CRC_SEED,
}; //! a simplistic fault storage

/** \brief A simplified variant of fault set routine
\param ErrorCode - a Standard fault code
*/
void error_SetFault(faultcode_fast_t ErrorCode)
{
    ff_fault_t fault = newfault(ErrorCode);
    if(fault != 0U)
    {
        MN_ENTER_CRITICAL();
            fault |= ff_faults.ff_fault;
            storeMemberInt(&ff_faults, ff_fault, fault);
        MN_EXIT_CRITICAL();
    }
}

//Some stubs:

void error_ClearFault_Private(faultcode_fast_t fbitnum)
{
    error_ClearFault(fbitnum); //No difference in FFP yet
}

void error_Mopup(void)
{
    //Nothing to do in FFP yet
}

/** \brief A simplified variant of fault clear routine
\param ErrorCode - a Standard fault code
*/
void error_ClearFault(faultcode_fast_t ErrorCode)
{
    ff_fault_t fault = newfault(ErrorCode);
    if(fault != 0U)
    {
        MN_ENTER_CRITICAL();
            fault &= ~ff_faults.ff_fault;
            storeMemberInt(&ff_faults, ff_fault, fault);
        MN_EXIT_CRITICAL();
    }
}
/** \brief A simplified variant of test set routine
\param ErrorCode - a Standard fault code
\return true iff fault exists
*/
bool_t error_IsFault(faultcode_fast_t ErrorCode)
{
    bool_t ret = false;
    ff_fault_t fault = newfault(ErrorCode) & ~(1U<<FF_FAULT_NONE); //filter out ignored faults
    if(fault != 0U)
    {
        MN_ENTER_CRITICAL();
            Struct_Test(ff_faults_t, &ff_faults);
            ret = (ff_faults.ff_fault & fault) != 0U;
        MN_EXIT_CRITICAL();
    }
    return ret;
}


/** \brief Action to take when a flash failure is detected
*/
void ffpflash_Fail(void)
{
    hm_kill_uart(); //reconfigure UART to fail IPC communications
    error_SetFault(FAULT_FW_CHECKSUM);
    HART_set_active(DEACTIVATE, DEACTIVATE); //As a secondary defense, disable IPC using Softing API
}

/*This line marks the end of the file*/
