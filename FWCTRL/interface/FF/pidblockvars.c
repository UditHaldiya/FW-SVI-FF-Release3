/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file PIDblockvars.c
    \brief "ipc variables" handler (borrowed from the trunk's nvram.c)

    CPU: Any

    OWNER: AK
    $Archive: /MNCB/Dev/FIRMWARE/interface/FF/PIDblockvars.c $
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
#include "ff_pidblockvars.h"
#include "param.h"
// -------------------------------- "ipc variables" management section ------------------------

// The initial values should be obtained from FFP every time when APP firmware starts
// This is just a temp solution
static IPC_FFPIDParams_t IPC_FFPIDParams[2] = //2 PID blocks
{
    [0] =
    {
        .tag = FF_TAG_DEF,
        .ModeActual = 0,
        .BlockErr = 0,
        .pv =
        {
            .value = FLOAT_STRING_INIT,
            .status = 0
        },
        .sp =
        {
            .value = FLOAT_STRING_INIT,
            .status = 0
        },
        .out =
        {
            .value = FLOAT_STRING_INIT,
            .status = 0
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
    [1] =
    {
        .tag = FF_TAG_DEF,
        .ModeActual = 0,
        .BlockErr = 0,
        .pv =
        {
            .value = FLOAT_STRING_INIT,
            .status = 0
        },
        .sp =
        {
            .value = FLOAT_STRING_INIT,
            .status = 0
        },
        .out =
        {
            .value = FLOAT_STRING_INIT,
            .status = 0
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
};

// get the pointer of PID block variables
const IPC_FFPIDParams_t* GetPidBlockVar(size_t index, IPC_FFPIDParams_t *dst)
{
     return STRUCT_GET(&IPC_FFPIDParams[index], dst);
}

ErrorCode_t  IPC_WritePIDTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_PID_BLOCK_TAG)
    {
        index = 0U;
    }
    else //must be IPC_PID2_BLOCK_TAG
    {
        index = 1U;
    }
    u8              DataBlockNumber = pIPC_WritePtrs->IPC_DataBlockNum;
    const u8*       pData = (const u8*)pIPC_WritePtrs->pIPC_VarBuffer;

    if (DataBlockNumber > FF_PID_TAG_WR_MAX_BLOCK_NUM)
    {
        util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_BAD | IPC_BAD_BLOCKNUM));
    }
    else
    {
        MN_ENTER_CRITICAL();
            u8 *pPIDTagSegment = &IPC_FFPIDParams[index].tag[DataBlockNumber * IPC_WRITE_ARRAY_DATASIZE];
            if (DataBlockNumber < FF_PID_TAG_WR_MAX_BLOCK_NUM)
            {
                util_PutU8Array(pPIDTagSegment, IPC_WRITE_ARRAY_DATASIZE, pData);
            }
            else
            {
                // block number = 2, write 10 characters
                util_PutU8Array(pPIDTagSegment, FF_TAG_MAX_LEN - IPC_WRITE_ARRAY_DATASIZE * FF_PID_TAG_WR_MAX_BLOCK_NUM, pData);
            }

            STRUCT_CLOSE(IPC_FFPIDParams_t, &IPC_FFPIDParams[index]);
         MN_EXIT_CRITICAL();
         util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));
    }

    return ERR_OK;
}

ErrorCode_t  IPC_WritePIDMode(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_PID_BLOCK_ACTUAL_MODE)
    {
        index = 0U;
    }
    else //must be IPC_PID2_BLOCK_ACTUAL_MODE
    {
        index = 1U;
    }
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFPIDParams[index].ModeActual = (u8)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFPIDParams_t, &IPC_FFPIDParams[index]);
        MN_EXIT_CRITICAL();
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFPIDParams[index].ModeActual);
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    return ERR_OK;
}

ErrorCode_t  IPC_WritePIDError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_PID_BLOCK_ERROR)
    {
        index = 0U;
    }
    else //must be IPC_PID2_BLOCK_ERROR
    {
        index = 1U;
    }
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFPIDParams[index].BlockErr = (u16)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFPIDParams_t, &IPC_FFPIDParams[index]);
        MN_EXIT_CRITICAL();
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFPIDParams[index].BlockErr);
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);

    return ERR_OK;
}

ErrorCode_t  IPC_WritePIDPV(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_PID_PV)
    {
        index = 0U;
    }
    else //must be IPC_PID2_PV
    {
        index = 1U;
    }

    MN_ENTER_CRITICAL();
        util_PutU8Array(IPC_FFPIDParams[index].pv.value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
        IPC_FFPIDParams[index].pv.status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);
        STRUCT_CLOSE(IPC_FFPIDParams_t, &IPC_FFPIDParams[index]);
    MN_EXIT_CRITICAL();
    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    return ERR_OK;
}

ErrorCode_t  IPC_WritePIDSP(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_PID_SP)
    {
        index = 0U;
    }
    else //must be IPC_PID2_SP
    {
        index = 1U;
    }

    MN_ENTER_CRITICAL();
        util_PutU8Array(IPC_FFPIDParams[index].sp.value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
        IPC_FFPIDParams[index].sp.status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);
        STRUCT_CLOSE(IPC_FFPIDParams_t, &IPC_FFPIDParams[index]);
    MN_EXIT_CRITICAL();
    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    return ERR_OK;
}

ErrorCode_t  IPC_WritePIDOUT(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_PID_OUT)
    {
        index = 0U;
    }
    else //must be IPC_PID2_OUT
    {
        index = 1U;
    }

    MN_ENTER_CRITICAL();
        util_PutU8Array(IPC_FFPIDParams[index].out.value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
        IPC_FFPIDParams[index].out.status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);
        STRUCT_CLOSE(IPC_FFPIDParams_t, &IPC_FFPIDParams[index]);
    MN_EXIT_CRITICAL();

    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    return ERR_OK;
}

