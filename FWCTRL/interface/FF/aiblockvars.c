/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file AIblockvars.c
    \brief "ipc variables" handler (borrowed from the trunk's nvram.c)

    CPU: Any

    OWNER: AK
    $Archive: /MNCB/Dev/FIRMWARE/interface/FF/aiblockvars.c $
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
#include "ff_aiblockvars.h"
#include "param.h"
// -------------------------------- "ipc variables" management section ------------------------

// The initial values should be obtained from FFP every time when APP firmware starts
// This is just a temp solution
static IPC_FFAIParams_t IPC_FFAIParams[3] = //We have 3 AI FB
{
    [0] =
    {
        .out =
        {
            .value = FLOAT_STRING_INIT,
            .status =0,
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
    [1] =
    {
        .out =
        {
            .value = FLOAT_STRING_INIT,
            .status =0,
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
    [2] =
    {
        .out =
        {
            .value = FLOAT_STRING_INIT,
            .status =0,
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
};

// Implementation of common accessor
const IPC_FFAIParams_t *GetAiBlockVar(size_t index, IPC_FFAIParams_t *dst)
{
    const IPC_FFAIParams_t *ret;
    if(index >= NELEM(IPC_FFAIParams))
    {
        ret = NULL;
    }
    else
    {
        ret = STRUCT_GET(&IPC_FFAIParams[index], dst);
    }
    return ret;
}

ErrorCode_t IPC_WriteAIOUT(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index = 0;
    switch(VarID)
    {
        case IPC_AI_OUT:
            //already index = 0;
            break;
        case IPC_AI2_OUT:
            index = 1;
            break;
        case IPC_AI3_OUT:
            index = 2;
            break;
        default:
            index = 20;
            break;
    }
    MN_DBG_ASSERT(index < 3);

    IPC_FFAIParams_t newval;
    STRUCT_GET(&IPC_FFAIParams[index], &newval);
	util_PutU8Array(newval.out.value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
	newval.out.status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);
    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    STRUCT_GET(&newval, &IPC_FFAIParams[index]);
    UNUSED_OK(VarID);
    return ERR_OK;
}
