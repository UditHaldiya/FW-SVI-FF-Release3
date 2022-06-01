/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file DOblockvars.c
    \brief "ipc variables" handler (borrowed from the trunk's nvram.c)

    CPU: Any

    OWNER: AK

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
#include "ff_doblockvars.h"
#include "param.h"
#include "numutils.h"
// -------------------------------- "ipc variables" management section ------------------------

/** Default data */
//static const u8 def_DOBlockTag[FF_DO_TAG_MAX_LEN] = {FF_DO_TAG_DEF};


// The initial values should be obtained from FFP every time when APP firmware starts
// This is just a temp solution
static IPC_FFDOParams_t IPC_FFDOParams[2] = //We have 2 DO blocks
{
    [0] =
    {
        .tag = FF_TAG_DEF,
        .ModeActual = 0,
        .BlockErr = 0,
        .sp_d =
        {
            .value = 0,
            .status = 0,
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
    [1] =
    {
        .tag = FF_TAG_DEF,
        .ModeActual = 0,
        .BlockErr = 0,
        .sp_d =
        {
            .value = 0,
            .status = 0,
        },
        .CheckWord = CRC_SEED, //make valid checksum by C init
    },
};


// Common accessor
const IPC_FFDOParams_t *GetDoBlockVar(size_t index, IPC_FFDOParams_t *dst)
{
    return STRUCT_GET(&IPC_FFDOParams[index], dst);
}

ErrorCode_t  IPC_WriteDOTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_DO_BLOCK_TAG)
    {
        index = 0U;
    }
    else //must be IPC_DO2_BLOCK_TAG
    {
        index = 1U;
    }
    u8              DataBlockNumber = pIPC_WritePtrs->IPC_DataBlockNum;
    u8*             pDOTagSegment = IPC_FFDOParams[index].tag;
    const u8*       pData = (const u8*)pIPC_WritePtrs->pIPC_VarBuffer;

    if (DataBlockNumber > FF_DO_TAG_WR_MAX_BLOCK_NUM)
    {
        util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_BAD | IPC_BAD_BLOCKNUM));
    }
    else
    {
        pDOTagSegment += DataBlockNumber * IPC_WRITE_ARRAY_DATASIZE;
        MN_ENTER_CRITICAL();
            if (DataBlockNumber < FF_DO_TAG_WR_MAX_BLOCK_NUM)
            {
                util_PutU8Array(pDOTagSegment, IPC_WRITE_ARRAY_DATASIZE, pData);
            }
            else
            {
                // block number = 2, write 10 characters
                util_PutU8Array(pDOTagSegment, FF_TAG_MAX_LEN - IPC_WRITE_ARRAY_DATASIZE * FF_DO_TAG_WR_MAX_BLOCK_NUM, pData);
            }

            STRUCT_CLOSE(IPC_FFDOParams_t, &IPC_FFDOParams[index]);
            util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));
        MN_EXIT_CRITICAL();
    }

    return ERR_OK;
}

ErrorCode_t  IPC_WriteDOMode(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_DO_BLOCK_ACTUAL_MODE)
    {
        index = 0U;
    }
    else //must be IPC_DO2_BLOCK_ACTUAL_MODE
    {
        index = 1U;
    }
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFDOParams[index].ModeActual = (u8)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFDOParams_t, &IPC_FFDOParams[index]);
        MN_EXIT_CRITICAL();
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFDOParams[index].ModeActual);
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    return ERR_OK;
}

ErrorCode_t  IPC_WriteDOError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_DO_BLOCK_ERROR)
    {
        index = 0U;
    }
    else //must be IPC_DO2_BLOCK_ERROR
    {
        index = 1U;
    }
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFDOParams[index].BlockErr = (u16)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFDOParams_t, &IPC_FFDOParams[index]);
        MN_EXIT_CRITICAL();
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFDOParams[index].BlockErr);
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);

    return ERR_OK;
}

ErrorCode_t  IPC_WriteDOSPD(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    size_t index;
    if(VarID == IPC_DO_SP_D)
    {
        index = 0U;
    }
    else //must be IPC_DO2_SP_D
    {
        index = 1U;
    }
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        util_PutU8Array(pIPC_ReadPtrs->pIPC_VarBuffer, sizeof(float32), pIPC_WritePtrs->pIPC_VarBuffer);

        /* The actual limits happen to be 0 to 65535*/
        MN_ENTER_CRITICAL();
            IPC_FFDOParams[index].sp_d.value = (s16)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            IPC_FFDOParams[index].sp_d.status = util_GetU8(pIPC_WritePtrs->pVarStatus);
            STRUCT_CLOSE(IPC_FFDOParams_t, &IPC_FFDOParams[index]);
        MN_EXIT_CRITICAL();
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);

    return ERR_OK;
}
