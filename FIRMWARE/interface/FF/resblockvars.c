/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file resblockvars.c
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
#include "ffdefs.h"
#include "ipcdefs.h"
#include "ipcvarids.h"
#include "ff_resblockvars.h"
// -------------------------------- "ipc variables" management section ------------------------

/** Default data */
static const u8 def_ResBlockTag[FF_TAG_MAX_LEN] = FF_TAG_DEF;


// The initial values should be obtained from FFP every time when APP firmware starts
// This is just a temp solution
static IPC_FFResourceParams_t IPC_FFResourceParams =
{
    .tag = FF_TAG_DEF,
    .ModeActual = 0,
    .BlockErr = 0,
    .CheckWord = CRC_SEED, //make valid checksum by C init, which alas doesn't happen
};

// get the pointer of resource block variables
const IPC_FFResourceParams_t* GetResBlockVar(IPC_FFResourceParams_t* dst)
{
     return STRUCT_GET(&IPC_FFResourceParams, dst);
}


//lint, remove static in the future if need the interface
static ErrorCode_t SetResBlockTag(const void *src)
{
    const u8* pCChanged = src;
    if(pCChanged == NULL)
    {
        pCChanged = def_ResBlockTag;
    }

    util_PutU8Array((u8*)IPC_FFResourceParams.tag, FF_TAG_MAX_LEN, pCChanged);
    STRUCT_CLOSE(IPC_FFResourceParams_t, &IPC_FFResourceParams);

    return ERR_OK;
}

ErrorCode_t IPC_WriteRbTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    ErrorCode_t     retval = ERR_OK;
    u8              DataBlockNumber = pIPC_WritePtrs->IPC_DataBlockNum;
    u8*             pRBTagSegment = IPC_FFResourceParams.tag;
    const u8*       pData = (const u8*)pIPC_WritePtrs->pIPC_VarBuffer;

    if (DataBlockNumber > FF_RB_TAG_WR_MAX_BLOCK_NUM)
    {
        util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_BAD | IPC_BAD_BLOCKNUM));
    }
    else
    {
         pRBTagSegment += DataBlockNumber * IPC_WRITE_ARRAY_DATASIZE;
         if (DataBlockNumber < FF_RB_TAG_WR_MAX_BLOCK_NUM)
         {
            util_PutU8Array(pRBTagSegment, IPC_WRITE_ARRAY_DATASIZE, pData);
         }
         else
         {
            // block number = 2, write 10 characters
            util_PutU8Array(pRBTagSegment, FF_TAG_MAX_LEN - IPC_WRITE_ARRAY_DATASIZE * FF_RB_TAG_WR_MAX_BLOCK_NUM, pData);
         }

         retval = SetResBlockTag(IPC_FFResourceParams.tag);
         util_PutU8(pIPC_ReadPtrs->pVarStatus, (IPC_QUALITY_GOOD | IPC_NO_ERROR));
    }

    UNUSED_OK(VarID);

    return retval;
}

ErrorCode_t  IPC_WriteRbModeActual(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8              ActualMode;

    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        ActualMode  = (u8)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
        storeMemberU8(&IPC_FFResourceParams, ModeActual, ActualMode);
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFResourceParams.ModeActual);
        util_PutU8(pIPC_ReadPtrs->pVarStatus, IPC_QUALITY_GOOD | IPC_NO_ERROR);
    }
    else
    {
        u8  ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
        util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    }

    UNUSED_OK(VarID);
    return ERR_OK;
}

ErrorCode_t  IPC_WriteRbError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs)
{
    u8 varStatus = util_GetU8(pIPC_WritePtrs->pVarStatus);
    if (IsQuality_ACCEPT(varStatus))
    {
        MN_ENTER_CRITICAL();
            u16 BlockErr  = (u16)util_GetU32(pIPC_WritePtrs->pIPC_VarBuffer);
            storeMemberU16(&IPC_FFResourceParams, BlockErr, BlockErr);
            util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, IPC_FFResourceParams.BlockErr);
        MN_EXIT_CRITICAL();
        util_PutU8(pIPC_ReadPtrs->pVarStatus, IPC_QUALITY_GOOD | IPC_NO_ERROR);
    }
    else
    {
        u8  ReturnStatus = *pIPC_WritePtrs->pVarStatus;
        util_PutU32(pIPC_ReadPtrs->pIPC_VarBuffer, 0u);
        util_PutU8(pIPC_ReadPtrs->pVarStatus, ReturnStatus);
    }

    UNUSED_OK(VarID);
    return ERR_OK;
}

/* This line marks the end of the source */
