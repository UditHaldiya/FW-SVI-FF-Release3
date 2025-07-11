/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file tbblockvars.c
    \brief "ipc variables" handler

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
#include "ff_tbblockvars.h"
#include "param.h"
// -------------------------------- "ipc variables" management section ------------------------

// The initial values should be obtained from FFP every time when APP firmware starts
// This is just a temp solution
static IPC_FFTBParams_t IPC_FFTBParams =
{
    .tag = FF_TAG_DEF,
    .ModeActual = 0,
    .BlockErr = 0,
    .final_sp =
    {
        .value = FLOAT_STRING_INIT,
        .status =0
    },
    .final_pos =
    {
        .value = FLOAT_STRING_INIT,
        .status =0
    },
    .cust_config_0 = 0, //invalid!
    .cust_config_1 = 0, //invalid!
    .CheckWord = CRC_SEED, //make valid checksum by C init
};

// get the pointer of TB block variables
const IPC_FFTBParams_t* GetTbBlockVar(IPC_FFTBParams_t *dst)
{
     return STRUCT_GET(&IPC_FFTBParams, dst);
}

ErrorCode_t  IPC_WriteTBTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8              DataBlockNumber = pIPC_WritePtrs->IPC_DataBlockNum;
    u8*             pTBTagSegment = IPC_FFTBParams.tag;
    const u8*       pData = (const u8*)pIPC_WritePtrs->pIPC_VarBuffer;

    if (DataBlockNumber > FF_TB_TAG_WR_MAX_BLOCK_NUM)
    {
        util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_BAD | IPC_BAD_BLOCKNUM));
    }
    else
    {
        pTBTagSegment += DataBlockNumber * IPC_WRITE_ARRAY_DATASIZE;
        MN_ENTER_CRITICAL();
            if (DataBlockNumber < FF_TB_TAG_WR_MAX_BLOCK_NUM)
            {
                util_PutU8Array(pTBTagSegment, IPC_WRITE_ARRAY_DATASIZE, pData);
            }
            else
            {
                // block number = 2, write 10 characters
                util_PutU8Array(pTBTagSegment, FF_TAG_MAX_LEN - IPC_WRITE_ARRAY_DATASIZE * FF_TB_TAG_WR_MAX_BLOCK_NUM, pData);
            }
        MN_EXIT_CRITICAL();

         STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
         util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));
    }

    UNUSED_OK(VarID);

    return ERR_OK;
}

ErrorCode_t  IPC_WriteTBMode(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFTBParams.ModeActual = (u8)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
            util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFTBParams.ModeActual);
        MN_EXIT_CRITICAL();
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    UNUSED_OK(VarID);
    return ERR_OK;
}

ErrorCode_t  IPC_WriteTBError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFTBParams.BlockErr = (u16)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
            util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFTBParams.BlockErr);
        MN_EXIT_CRITICAL();
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    UNUSED_OK(VarID);
    return ERR_OK;
}

//This should be removed from IPC in favor of grabbing digital setpoint
ErrorCode_t  IPC_WriteTBFinalSP(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    MN_ENTER_CRITICAL();
        util_PutU8Array(IPC_FFTBParams.final_sp.value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
        IPC_FFTBParams.final_sp.status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);

        STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
    MN_EXIT_CRITICAL();
    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    UNUSED_OK(VarID);
    return ERR_OK;
}

//This should be removed from IPC in favor of inverse characterization of local (working) position
ErrorCode_t  IPC_WriteTBFinalPOS(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    MN_ENTER_CRITICAL();
        util_PutU8Array(IPC_FFTBParams.final_pos.value, FLOAT_STRING_LEN - 1, pIPC_WritePtrs->pIPC_VarBuffer);
        IPC_FFTBParams.final_pos.status = util_GetU8(((const u8*)(pIPC_WritePtrs->pIPC_VarBuffer)) + FLOAT_STRING_LEN - 1);

        STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
    MN_EXIT_CRITICAL();
    util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));

    UNUSED_OK(VarID);
    return ERR_OK;
}

//AK: The following two should be removed from IPC in favor of APP owning UI custom configuration

ErrorCode_t  IPC_WriteTBUICustConfig0(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFTBParams.cust_config_0 = (u8)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
            util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFTBParams.cust_config_0);
        MN_EXIT_CRITICAL();
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    UNUSED_OK(VarID);
    return ERR_OK;
}

ErrorCode_t  IPC_WriteTBUICustConfig1(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8              ReturnStatus = IPC_QUALITY_GOOD | IPC_NO_ERROR;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            IPC_FFTBParams.cust_config_1 = (u8)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            STRUCT_CLOSE(IPC_FFTBParams_t, &IPC_FFTBParams);
            util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFTBParams.cust_config_1);
        MN_EXIT_CRITICAL();
    }
    else
    {
        ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
    }

    util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    UNUSED_OK(VarID);
    return ERR_OK;
}


