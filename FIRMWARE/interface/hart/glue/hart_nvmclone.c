/*
Copyright 2013 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_nvmclone.c
    \brief HART glue layer for debug support for NVMEM cloning

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "clonenvram.h"
#include "hartdef.h"
#include "bufutils.h"
#include "hartfunc.h"
#include "bufferhandler.h"
#include "vertranpub.h"

/** \brief Start a non-interruptible process of translating and writing
an appropriate NVMEM image in the opposite (or legacy) bank.
This command can't fail but the launched process can; its results
are in the diagnostic buffer on completion
*/
s8_least hartcmd_CloneNvmemToOppositeBank(const u8 *src, u8 *dst)
{
    const Req_CloneNvmemToOppositeBank_t *s = (const void *)src;
    Rsp_CloneNvmemToOppositeBank_t *d = (void *)dst;
    //Rely on HART framework to fill the fields
    UNUSED_OK(d);
    UNUSED_OK(s);
    process_ForceProcessCommand(PROC_CLONE_NVMEM);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/** \brief Launch a dummy process to disable the buffer writes by outsiders
THIS command may fail
*/
s8_least hartcmd_EnableExternalWritesToDiagnosticBuffer(const u8 *src, u8 *dst)
{
    const Req_EnableExternalWritesToDiagnosticBuffer_t *s = (const void *)src;
    Rsp_EnableExternalWritesToDiagnosticBuffer_t *d = (void *)dst;
    //Rely on HART framework to fill the fields
    UNUSED_OK(d);
    UNUSED_OK(s);
    ErrorCode_t err;
    u8 bufnum = util_GetU8(s->BufferId[0]); //Only first buffer supported
    if(bufnum != DIAGBUF_DEFAULT)
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        err = process_SetProcessCommand(PROC_EMPTY_WRAPPER);
    }
    return err2hart(err);
}

/** \brief Stuff some data into the diagnostic buffer
*/
s8_least hartcmd_ExternalWriteToDiagnosticBuffer(const u8 *src, u8 *dst)
{
    const Req_ExternalWriteToDiagnosticBuffer_t *s = (const void *)src;
    Rsp_ExternalWriteToDiagnosticBuffer_t *d = (void *)dst;
    //Rely on HART framework to fill the fields
    UNUSED_OK(d);
    u8 bufnum = util_GetU8(s->BufferId[0]);
    void *buf = buffer_GetXDiagnosticBuffer(bufnum);

    ErrorCode_t err = ERR_OK;

    if(buf == NULL)
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        u16 DataOffset = util_GetU16(s->DataOffset[0]);
        u16_least DataSampleCount = util_GetU16(s->DataSampleCount[0]);
        if((DataOffset + DataSampleCount) >= (NVCLONE_MAX_IMAGE_LENGTH*sizeof(diag_t)) ) //account for byte to diag_t resize
        {
            err = ERR_UPPERLIM;
        }
        else if(process_GetProcId() != PROC_EMPTY_WRAPPER)
        {
            err = ERR_MODE_CANNOT_CHANGE;
        }
        else
        {
            u8 *ubuf = buf;
            mn_memcpy(ubuf + DataOffset, s->RawDataSamples[0], DataSampleCount);
        }
    }
    return err2hart(err);
}

#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST==OPTION_ON
s8_least hartcmd_CommitNVMEMImageFromDiagnosticBuffer(const u8 *src, u8 *dst)
{
    const Req_CommitNVMEMImageFromDiagnosticBuffer_t *s = (const void *)src;
    Rsp_ExternalWriteToDiagnosticBuffer_t *d = (void *)dst;
    //Rely on HART framework to fill the fields
    UNUSED_OK(d);
    u8 bufnum = util_GetU8(s->BufferId[0]);
    ErrorCode_t err;
    if(bufnum != DIAGBUF_DEFAULT)
    {
        err = ERR_INVALID_PARAMETER; //Only buffer 0 is now supported
    }
    else if((process_GetProcId() != PROC_EMPTY_WRAPPER))
    {
        err = ERR_PROCESS_START; //must directly follow PROC_EMPTY_WRAPPER
    }
    else
    {
        diag_t *hdr = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT); //always valid pointer
        /* This won't pass the signature test:
        hdr[nvindex_thisbank] = util_GetU8(s->NVMEMbank[0]);
        Stuff the value past the data instead, to be retrieved by the process itself
        */
        hdr[NVCLONE_MAX_IMAGE_LENGTH] = util_GetU8(s->NVMEMbank[0]);
        process_ForceProcessCommand(PROC_DOWNLOAD_NVMEM);
        err = ERR_OK;
    }

    return err2hart(err);
}
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST

#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST==OPTION_ON
s8_least hartcmd_ReadNVMEMToDiagnosticBuffer(const u8 *src, u8 *dst)
{
    const Req_ReadNVMEMToDiagnosticBuffer_t *s = (const void *)src;
    Rsp_ReadNVMEMToDiagnosticBuffer_t *d = (void *)dst;
    //Rely on HART framework to fill the fields
    UNUSED_OK(d);
    u8 bufnum = util_GetU8(s->BufferId[0]);
    ErrorCode_t err;
    if(bufnum != DIAGBUF_DEFAULT)
    {
        err = ERR_INVALID_PARAMETER; //Only buffer 0 is now supported
    }
    else
    {
        diag_t *hdr = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT); //always valid pointer
        hdr[nvindex_thisbank] = util_GetU8(s->NVMEMbank[0]);
        err = process_SetProcessCommand(PROC_UPLOAD_NVMEM);
    }

    return err2hart(err);
}
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST
/* This line marks the end of the source */
