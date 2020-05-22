/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_fedlxmit.c
    \brief Glue functions related to position control HART support

    CPU: Any

    OWNER: AP
    $Archive: /MNCB/Dev/LCX2AP/FIRMWARE/interface/hart/glue/hart_posctl.c $
    $Date: 1/20/12 10:48a $
    $Revision: 10 $
    $Author: Anatoly Podpaly $

    \ingroup HARTapp
*/

#include "mnwrap.h"
#include "hart.h"
#include "hartdef.h"
#include "bufutils.h"
#include "faultpublic.h"
#include "mn_flash.h"
#include "hartfunc.h"
#include "process.h"
#include "facdefaults.h"

typedef         u32 (*flashOp)(u32 value);
static const    u8* hdata;
static          u16 bdata[MAX_PROG_DATA / sizeof(u16)];

static u32 flash_pgm(u32 addr);
static u32 flash_setpartn(u32 ptn);

static u32 flash_OpenPartition1(u32 crc);

// dispatch table for flash update operations
static const flashOp ops[] =
{
    [SET_PARTN]   = flash_setpartn,
    [OPEN_PARTN]  = flash_OpenPartition1,
    [CLOSE_PARTN] = flash_ClosePartition,
    [PROG_BLOCK]  = flash_pgm,
    [PARTN_BASE]  = flash_GetPartitionBaseAddress,
};

/** \brief Set the flash partition built according to the passed value
    (and schedule a reset on the way out.)

NOTE: retries on failure (in FFP) never worked in practice and may
corrupt option bytes in APP (observed). So, a reset is needed here.

    \param ptn - the partition state to set (Bank0/bank1}
*/
static u32 flash_setpartn(u32 ptn)
{
    hart_ResetDeviceOnSend();
    return flash_SetPartition(ptn);
}

static    u8_least len;    // length in bytes from hart buffer
static    u8_least flags;        // flags (update CRC | NOERASE
static u16 flashbuf[(MAX_PROG_DATA + 2 +10)/sizeof(u16)];

typedef struct fwdl_state_t
{
    u32 lastaddr;
    u32 last_result;
    bool_t interleaved; //!< option cached for the duration of download
    bool_t working; //!< deferred request
    u16 CheckWord;
} fwdl_state_t; //! type for collection of long-term items

static fwdl_state_t fwdl_state =
{
    .lastaddr = 0,
    .last_result = 0,
    .interleaved = false,
    .working = false,
    .CheckWord = CRC_SEED,
};

static os_event_t proxy_sem = NULL;

static u32 flash_OpenPartition1(u32 crc)
{
    fwdl_state.last_result = crc;
    fwdl_state.lastaddr = 0;
    fwdl_state.interleaved = (facdef_GetState(NULL)->fwdl_mode == 0);
    fwdl_state.working = false;
    STRUCT_CLOSE(fwdl_state_t, &fwdl_state);
    return flash_OpenPartition(crc);
}


static void fwdl_Mopup(void)
{
    Struct_Test(fwdl_state_t, &fwdl_state);
    if(fwdl_state.working)
    {
        //Only errors reported
        u32 result = flash_ProgramBlock(flashbuf, HARDWARE(u16*, fwdl_state.lastaddr), len, flags & ~UPD_CRC);
        result = (fwdl_state.last_result & 0xffffU)|(result & 0xffff0000U);
        storeMemberInt(&fwdl_state, last_result, result);
    }
}

/** \brief fetch the rest of the program-block params and call the flash program routine
    See mn_flash.h for offsets in the hart paylaod  The rest if the command,
    flags and length are stil in the hart buffer, hdata;

    \param addr - the beginning flash address at which to prgraom the payload data
*/
static u32 flash_pgm(u32 addr)
{

    len   = *(hdata - 1) - DATA_OFFSET;    // length in bytes from hart buffer
    flags = *(hdata + FLAG_OFFSET);        // flags (update CRC | NOERASE

    mn_memcpy(bdata, hdata + DATA_OFFSET, len);        // ensure 16-bit alignment

    if (fwdl_state.lastaddr != addr)
    {
        storeMemberInt(&fwdl_state, lastaddr, addr);
        //Wait as long as needed for cycle task to complete; it will preempt and do the job
        if(fwdl_state.working)
        {
            u16_least event_count = oswrap_WaitSem(proxy_sem);
            UNUSED_OK(event_count); //don't care of how many - always 1 by design
            storeMemberBool(&fwdl_state, working, false);
        }
        u32 result;
        if( ((flags & FWDL_WRITE_INLINE) == 0U) && fwdl_state.interleaved)
        {
            storeMemberBool(&fwdl_state, working, true);
            u16 fCrc = Crc16((const u8 *)bdata, len, fwdl_state.last_result & 0xFFFFU);

            //Delegate the write off_line
            result = (fwdl_state.last_result & 0xffff0000U)|fCrc;
            mn_memcpy(flashbuf, bdata, len);
            oswrap_PostTaskSemaphore(TASKID_PROXY);
        }
        else
        {
            //Need to complete the write inline: there will be no other chance to report result
            result   = flash_ProgramBlock(bdata, HARDWARE(u16*, addr), len, flags);
            if((flags & UPD_CRC) == 0U)
            {
                result = (fwdl_state.last_result & 0xffffU)|(result & 0xffff0000U); //errors only
            }
        }
        storeMemberInt(&fwdl_state, last_result, result);
    }
    return fwdl_state.last_result;
}

/** \brief This command IS an IPC Firmware Download support.  It dispatches the commands
    from the FF CPU to update the flash image

    \param src - pointer to the payload of the received hart packet
    \param dst - pointer to the payload of the reply hart packet
    \return - the 32-bit result from the requested operation
*/
s8_least hartcmd_IPCFirmwareDownloadDataTransfer(const u8 *src, u8 *dst)
{
    const Req_IPCFirmwareDownloadDataTransfer_t     *s1 = (const void *)src;
    Rsp_IPCFirmwareDownloadDataTransfer_t           *d1 = (void *)dst;
    const u8 *s2 = s1->FWSendDataBlock[0];
          u8 *d2 = d1->FWReceiveDataBlock[0];

    u8_least cmd = util_GetU8 (src + CMD_OFFSET);
    u32     addr = util_GetU32(src + ADDR_OFFSET);
    u32     rslt = 0u;

    UNUSED_OK(s2);
    UNUSED_OK(d2);

    if (cmd < FMAX_OP)
    {
        if (cmd == VER_INFO)
        {
            return -(s8_least)GetFwInfo(dst);
        }
        hdata = src;                        // save a pointer so flash_pgm() can get it
        rslt = ops[cmd](addr);
    }
    util_PutU32(dst, rslt);
    return -(s8_least)sizeof(rslt);
}

s8_least hartcmd_ReadAPPActiveFlashBank(const u8 *src, u8 *dst)
{
	const Req_ReadAPPActiveFlashBank_t *s = (const void *)src;
	UNUSED_OK(s);
	Rsp_ReadAPPActiveFlashBank_t *d = (void *)dst;
	util_PutU8(d->APPFlashBank[0], flash_GetRunningPartitionID());
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

//-------------- options (stolen from FFP) -----------------------
s8_least hartcmd_WriteAPPFWDownloadMethod(const u8 *src, u8 *dst)
{
    const Req_WriteAPPFWDownloadMethod_t *s = (const void *)src;
    Rsp_WriteAPPFWDownloadMethod_t *d = (void *)dst;
    UNUSED_OK(d->APPFWDLMethod);
    u8 dl = util_GetU8(s->APPFWDLMethod[0]);
    FactoryDefaultState_t f;
    (void)facdef_GetState(&f);
    f.fwdl_mode = dl;
    ErrorCode_t err = facdef_SetState(&f);
    s8_least ret;
    if(err == ERR_OK)
    {
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    else
    {
        ret = HART_INVALID_SELECTION;
    }
    return ret;
}

s8_least hartcmd_ReadAPPFWDownloadMethod(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadAPPFWDownloadMethod_t *d = (void *)dst;
    u8 dl = facdef_GetState(NULL)->fwdl_mode;
    if(dl == 0)
    {
        util_PutU8(d->APPFWDLMethod[0], (u8)InterleaveFWwriteAPP);
    }
    else
    {
        util_PutU8(d->APPFWDLMethod[0], (u8)InlineFWwriteAPP);
    }
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

// ------------- proxy task ------------------
void proxy_ProxyTask(void *p_arg)
{
    UNUSED_OK(p_arg);
    oswrap_CreateSem(&proxy_sem);

    for (;;)
    {
        mn_waitforsem(TASKID_PROXY);
        /* EXPLANATION:
        Normal fare is mn_waitsem(TASKID_PROXY);
        However, this task may overrun intentionally, if interleave
        is causing one more chunk to be sent here.
        If it is a retry, it is not a problem: Ernie's code
        handles this gracefully.
        */
        fwdl_Mopup();
        syswd_TickleWatchdog(TASKID_PROXY);

#if PROXY_TASK_PRIO < PROCESS_TASK_PRIO
        /* We may starve the process task, a little but enough to trigger
        watchdog. So we tickle it here on its behalf
        */
        syswd_TickleWatchdog(TASKID_PROCESS);
#endif

        //Notify the command
        oswrap_PostSem(proxy_sem);
    }
}

/* This line marks the end of the source */
