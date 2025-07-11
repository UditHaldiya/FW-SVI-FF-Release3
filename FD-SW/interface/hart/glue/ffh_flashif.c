/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_flashif.c
    \brief Intercepted flash-related commands

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include <eep_if.h>
#include <hw_if.h>
#include "hartfunc.h"
#include "hartcmd.h"
#include "bufutils.h"
#include "ffhartdef5.h"
#include "mnflashff.h"
#include "facdefaults.h"

//--------- subcommand 9 --------------------
s8_least hartcmd_ReadFFPActiveFlashBank(const u8 *src, u8 *dst)
{
	const Req_ReadFFPActiveFlashBank_t *s = (const void *)src;
	UNUSED_OK(s);
	Rsp_ReadFFPActiveFlashBank_t *d = (void *)dst;
	util_PutU8(d->FFPFlashBank[0], flash_GetRunningPartitionID());
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/** \brief A helper for switching flash banks (partitions)
\param src - a pointer to received frame
\param dst - a pointer to resulting frame
\param bankfunc - a function to execute to change banks
\return failure (on success, doesn't return)
*/
static s8_least switch_flash_banks(const u8 *src, u8 *dst, BOOL (*bankfunc)(PARTN_STATE st[2]))
{
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
	const Req_EmulateFirmwareActivation_t *s = (const void *)src;
	Rsp_EmulateFirmwareActivation_t *d = (void *)dst;
	UNUSED_OK(d);

    PARTN_STATE target = ACTIVATE0;
    PARTN_STATE target_app = ACTIVATE0;
    u8 c = util_GetU8(s->FlashPartitionChangeRequest[0]);
    ErrorCode_t err = ERR_OK;
    switch(c)
    {
        case FlashPartition0:
        {
            break;
        }
        case FlashPartition1:
        {
            target = ACTIVATE1;
            target_app = ACTIVATE1;
            break;
        }
        case FlashFlipPartition:
        {
            s8_least app_bank = fwdk_GetAppBank();
            target = (flash_GetRunningPartitionID() == 0) ? ACTIVATE1 : ACTIVATE0;
            target_app = (app_bank == 0) ? ACTIVATE1 : ACTIVATE0;
            if(app_bank < 0)
            {
                err = ERR_INVALID_PARAMETER; //could be better
            }
            break;
        }
        default:
        {
            err = ERR_INVALID_PARAMETER;
            break;
        }
    }
    if(err == ERR_OK)
    {
        PARTN_STATE st[2] =
        {
            [0] = target,
            [1] = target_app
        };

        BOOL x = bankfunc(st);
        //BOOL x = activate_fd_sw_internal(st);
        if(x == FALSE)
        {
            err = ERR_NOT_SUPPORTED;
        }
    }
    if(err == ERR_OK)
    {
        Reset_CPU(); //Make it simple, in a single operation
    }
    else
    {
        ret = HART_INVALID_SELECTION;
    }
    return ret;
}

    //--------- subcommand 10 --------------------
s8_least hartcmd_EmulateFirmwareActivation(const u8 *src, u8 *dst)
{
    return switch_flash_banks(src, dst, activate_fd_sw_internal);
}
    //--------- subcommand 11 --------------------
s8_least hartcmd_ForceFlashPartitionChange(const u8 *src, u8 *dst)
{
    return switch_flash_banks(src, dst, flash_SwitchPartitions);
}

    //--------- subcommand 18 --------------------
s8_least hartcmd_WriteFWDownloadMethod(const u8 *src, u8 *dst)
{
    const Req_WriteFWDownloadMethod_t *s = (const void *)src;
    Rsp_WriteFWDownloadMethod_t *d = (void *)dst;
    UNUSED_OK(d->FWDLMethod);
    u8 dl = util_GetU8(s->FWDLMethod[0]);
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

    //--------- subcommand 17 --------------------
s8_least hartcmd_ReadFWDownloadMethod(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadFWDownloadMethod_t *d = (void *)dst;
    u8 dl = facdef_GetState(NULL)->fwdl_mode;
    if(dl == 0)
    {
        util_PutU8(d->FWDLMethod[0], (u8)InterleaveFWwrite);
    }
    else
    {
        util_PutU8(d->FWDLMethod[0], (u8)InlineFWwrite);
    }
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
\brief Returns the status of long processes.
*/
s8_least hartcmd_CheckFFPProcess(const u8 *src, u8 *dst)
{
    Rsp_CheckFFPProcess_t *d = (void *)dst;
    UNUSED_OK(src);

    util_PutU8(d->FFPProcessId[0], process_GetProcId());
    util_PutU8(d->FFPPercentComplete[0], process_CheckProcessProgress());

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
\brief Cancels a long process.
*/
s8_least hartcmd_CancelFFPProcess(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);

    // cancel the process, no checking required
    process_CancelProcess();

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/* This line marks the end of the source */
