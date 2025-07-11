/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_nvmemif.c
    \brief HART-over-FF glue layer for MN interfaces

    Similar to APP's version

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/

#include "mnwrap.h"
#include "ffhartdef5.h"
#include "hartfunc.h"
#include "bufutils.h"
#include "process.h"

s8_least hartcmd_CommitRAMtoNVMEMinFFP(const u8 *src, u8 *dst)
{
    const Req_CommitRAMtoNVMEMinFFP_t *s = (const void *)src;
    u8 volid = util_GetU8(s->FFNVMEMVolumeId[0]);
    //Only vol 0 supported now
    if(volid != 0)
    {
        return HART_INVALID_SELECTION;
    }

    UNUSED_OK(dst);
    s8_least ret;

    ErrorCode_t err = process_SetProcessCommand(PROC_HART_SUB132_INIT_WITHCAL);
    if(err != ERR_OK)
    {
        ret = HART_BUSY;
    }
    else
    {
        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }
    return ret;
}

/* This line marks the end of the source */
