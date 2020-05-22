/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_fwdl_hart.c
    \brief functions to pass firmware download commands to the APP CPU

    CPU: Any

    OWNER: EP
    $Date: 11/01/12 11:19a $
    $Revision: 1 $
    $Author: Ernir Price $
*/
#include <softing_base.h>
#include <hw_if.h>
#include "hartnumtypes.h"
#include "hartdef.h"
#include "bufutils.h"
#include "mnhart2ff.h"
#include "mnflashff.h"
#include "process.h"
#include "bufferhandler.h"
#include "vertranpub.h"
#include "syswd.h"
#include "hmsndrcv5.h"

#define BUFFERSIZE_FUDGE 2 //match the original 60
static u8 send_buffer[DATA_OFFSET + MAX_PROG_DATA + BUFFERSIZE_FUDGE];
static u8 recv_buffer[DATA_OFFSET + MAX_PROG_DATA + BUFFERSIZE_FUDGE];


//-----------------------------------------------------------------------------------------

/** \brief Send a PROG_BLOCK command to the APP CPU using hart command 245.
    See mn_flash.h for the list of commands. Also see hart_fwdlxmit.c in the APP CPU.

    \param data - pointer to the block of firmware data.
    \param addr - the starting flash address for the data
    \param len - te length in bytes of the data
    \param flags - bitmap of flags indication update of address and
    \return flash command result if successful; otherwise 0xffffffff
*/
/* async hart command 245 to update flash in the APP CPU */
u32 fwdk_WriteAppCPU(const void *data, u32 addr, u8_least len, u8_least flags)
{

    fwdl_AcquireMutex();
    util_PutU8 (send_buffer + CMD_OFFSET,  PROG_BLOCK);
    util_PutU8 (send_buffer + FLAG_OFFSET, (u8)flags);
    util_PutU32(send_buffer + ADDR_OFFSET, addr);
    memcpy     (send_buffer + DATA_OFFSET, data, len);

    u8 taskid = osif_get_current_task_id();
    osif_TickleWatchdog(taskid);

    u32 ret = ~0U;
    fferr_t fferr = mn_HART_acyc_cmd(245, send_buffer, (u8)(len + DATA_OFFSET), recv_buffer);
    if(fferr == E_OK)
    {
        ret = util_GetU32(recv_buffer + HART_NUM_STATUS_BYTES);
    }
    fwdl_ReleaseMutex();

    return ret;
}

/** \brief Ask the APP CPU about the versions of software in ints flash banks

    \param dst - a pointer to the returned array[2] of FFInfo_t
*/
void fwdk_GetVerInfo(FFInfo_t dst[2])
{
    fferr_t fferr;

    fwdl_AcquireMutex();
    util_PutU8 (send_buffer + CMD_OFFSET, (u8)VER_INFO);
    fferr = mn_HART_acyc_cmd(245, send_buffer, (u8)DATA_OFFSET, recv_buffer);
    if(fferr == E_OK)
    {
        mn_memcpy(dst, recv_buffer + HART_NUM_STATUS_BYTES, 2U*sizeof(FFInfo_t));
    }
    fwdl_ReleaseMutex();
}


/** \brief Attempt to adapt APP NVMEM image to the new flash image
*/
fferr_t fwdk_AdaptAppNvmem(void)
{
    fwdl_AcquireMutex();
    void *from = send_buffer;
    void *to = recv_buffer;
    Req_RunaProcess_t *subcmd = from;

    util_PutU8 (subcmd->SubCmdNum[0], 131); //subcommand to clone NVMEM
    u8 len = MN_OFFSETOF(Req_RunaProcess_t, endmark) + MN_OFFSETOF(Req_CloneNvmemToOppositeBank_t, endmark);
    fferr_t fferr = mn_HART_acyc_cmd(190, from, len, to);
    fwdl_ReleaseMutex();

    if(fferr == E_OK)
    {
        //Wait for the process to complete
        u8 percent_complete;
        taskid_t taskid = osif_get_current_task_id();
        do
        {
            OS_Delay(20);
            syswd_TickleWatchdog(taskid);
            fwdl_AcquireMutex();
            fferr = mn_HART_acyc_cmd(251, from, 0, to);
            fwdl_ReleaseMutex();
            const Rsp_CheckProcess_t *dst = (const void *)((u8 *)to + 2);
            //procid = util_GetU8(dst->ProcessId[0]);
            percent_complete = util_GetU8(dst->PercentComplete[0]);
        } while((fferr == E_OK) && (percent_complete<=100U));
    }

    fwdl_AcquireMutex();
    //Read the completion code
    if(fferr == E_OK)
    {
        Req_ReadDataBufferRaw_t *src = from;
        util_PutU8(src->BufferId[0], DIAGBUF_DEFAULT);
        util_PutU8(src->DataOffset[0], 0);
        util_PutU8(src->DataSampleSize[0], sizeof(diag_t)); //does matter for size check
        util_PutU8(src->DataSampleSkipCount[0], 0); //do not change it here
        len = MN_OFFSETOF(Req_ReadDataBufferRaw_t, endmark);
        fferr = mn_HART_acyc_cmd(193, from, len, to);
    }
    if(fferr == E_OK)
    {
        const Rsp_ReadDataBufferRaw_t *dst = (const void *)((u8 *)to + 2);
        const diag_t *buf = (const void *)dst->RawDataSamples[0];
        if( (util_GetU8(dst->DataSampleCount[0]) != NVXLATE_HEADERSZ)
           || (buf[nvindex_buftype] != NVXLATE_DIAGTYPE_XLATE)
           || (buf[nvindex_result1] != buf[nvindex_result2])
           || (buf[nvindex_result1] == (diag_t)PROCRESULT_FAILED)
               )
        {
            fferr = E_ERROR;
        }
    }

    //Unconditionally cancel the process kept on running to preserve buffer
    (void)mn_HART_acyc_cmd(253, from, 0, to);
    fwdl_ReleaseMutex();

    return fferr;
}

/** \brief Send a flash command to the APP CPU usig hart command 245.  See
    mn_flash.h for the list of commands. Also see hart_fwdlxmit.c in the APP CPU.

    \param cmdtype - one of the supported commands. Except PROG_BLOCK which is
                    handled above.
    \param value - a 32-bit command secific paramaeter
    \return the 32-bit result from the flash command execution in the APP CPU;
                0xffffffff if the command failed.
*/
u32 fwdk_WriteAppCPU32(u8_least cmdtype, u32 value)
{
    u32 ret;
    fwdl_AcquireMutex();
    util_PutU8 (send_buffer + CMD_OFFSET, (u8)cmdtype);
    util_PutU8 (send_buffer + FLAG_OFFSET, (u8)0);
    util_PutU32(send_buffer + ADDR_OFFSET, value);

    u8 taskid = osif_get_current_task_id();
    osif_TickleWatchdog(taskid);

    fferr_t fferr = mn_HART_acyc_cmd(245, send_buffer, (u8)DATA_OFFSET, recv_buffer);
    if(fferr == E_OK)
    {
        ret = util_GetU32(recv_buffer + HART_NUM_STATUS_BYTES);
    }
    else
    {
        ret = ~0U;
    }
    fwdl_ReleaseMutex();
    return ret;
}

#define FUDGE_SIZE1 8 //same as FUDGE_SIZE 8 in appl_ptb; must be at least 3 but for the future...
s8_least fwdk_GetAppBank(void)
{
    s8_least ret;
    fwdl_AcquireMutex();
    Req_ReadAPPActiveFlashBank_t *req = (void *)(send_buffer + FUDGE_SIZE1);
    Rsp_ReadAPPActiveFlashBank_t *rsp = (void *)(recv_buffer + FUDGE_SIZE1);
    fferr_t fferr = hmsndrcv5_ReadAPPActiveFlashBank(req, rsp);
    if(fferr == E_OK)
    {
        ret = (s8_least)util_GetU8(rsp->APPFlashBank[0]);
    }
    else
    {
        ret = -1;
    }
    fwdl_ReleaseMutex();
    return ret;
}

// end of source
