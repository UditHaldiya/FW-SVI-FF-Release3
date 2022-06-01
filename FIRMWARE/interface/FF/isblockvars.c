/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file isblockvars.c
    \brief "ipc variables" handler (borrowed from the trunk's nvram.c)

    CPU: Any

    OWNER: AK
    $Archive: /MNCB/Dev/FIRMWARE/interface/FF/isblockvars.c $
    $Date: 08/23/12 11:19a $
    $Revision: 1 $
    $Author: stanley fu $

    \ingroup FF
*/

#include "mnwrap.h"
#include "errcodes.h"
#include "faultpublic.h"
#include "numutils.h"
#include "bufutils.h"
#include "fpconvert.h"
#include "hart.h"
#include "devicemode.h"
#include "ipcdefs.h"
#include "ipcvarids.h"
#include "ff_isblockvars.h"
#include "param.h"
// -------------------------------- "ipc variables" management section ------------------------


// The initial values should be obtained from FFP every time when APP firmware starts
// This is just a temp solution
static IPC_FFISParams_t IPC_FFISParams =
{
    .in1 =
    {
        .value = FLOAT_STRING_INIT,
        .status = 0
    },
    .in2 =
    {
        .value = FLOAT_STRING_INIT,
        .status = 0
    },
    .in3 =
    {
        .value = FLOAT_STRING_INIT,
        .status = 0
    },
    .in4 =
    {
        .value = FLOAT_STRING_INIT,
        .status = 0
    },
    .CheckWord = CRC_SEED, //make valid checksum by C init
};

// get the pointer of IS block variables
const IPC_FFISParams_t* GetIsBlockVar(IPC_FFISParams_t *dst)
{
     return STRUCT_GET(&IPC_FFISParams, dst);
}

ErrorCode_t  IPC_WriteISIN(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    ffDataFloat_t *in;
    switch(VarID)
    {
        case IPC_IS_IN1:
            in = &IPC_FFISParams.in1;
            break;
        case IPC_IS_IN2:
            in = &IPC_FFISParams.in2;
            break;
        case IPC_IS_IN3:
            in = &IPC_FFISParams.in3;
            break;
        case IPC_IS_IN4:
            in = &IPC_FFISParams.in4;
            break;
        default:
            in = NULL;
            break;
    }
    MN_DBG_ASSERT(in != NULL);

    MN_ENTER_CRITICAL();
        util_PutU8Array(in->value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
        in->status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);
        STRUCT_CLOSE(IPC_FFISParams_t, &IPC_FFISParams);
    MN_EXIT_CRITICAL();
    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    return ERR_OK;
}

