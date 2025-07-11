/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_rwmemory.c
    \brief Intercepted memory manipulation commands

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include "hartfunc.h"
#include "hartcmd.h"
#include "bufutils.h"
#include "ffhartdef5.h"
#include "fram.h"


s8_least hartcmd_ReadFFPmemory(const u8 *src, u8 *dst)
{
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    const Req_ReadFFPmemory_t *s = (const void *)src;
    Rsp_ReadFFPmemory_t *d = (void *)dst;
    UNUSED_OK(d->FFPMemorySelection); //rely on framework to fill
    UNUSED_OK(d->FFPMemoryaddress); //rely on framework to fill
    FFPMemorySelectionEnum_t memtype = (FFPMemorySelectionEnum_t)util_GetU8(s->FFPMemorySelection[0]);
    u32 addr = util_GetU32(s->FFPMemoryaddress[0]);
    u16 len = sizeof(d->FFPMemoryContent);
    switch(memtype)
    {
        case FFPNVMEM:
        {
            ErrorCode_t err;
            MN_NVMEM_LOCK(len);
                 err = fram_ReadExt(d->FFPMemoryContent[0], (u16)addr, len, 0);
            MN_NVMEM_UNLOCK();
            if(err != ERR_OK)
            {
                ret = TRANSMITTER_SPECIFIC_COMMAND_ERROR;
            }
            break;
        }
        case FFPRAM:
        {
            memcpy(d->FFPMemoryContent[0], HARDWARE(void *, addr), len);
            break;
        }
        default:
        {
            ret = HART_PASSED_PARAMETER_TOO_LARGE;
            break;
        }
    }
    return ret;
}

    //--------- subcommand 4 --------------------
s8_least hartcmd_WriteFFPmemory(const u8 *src, u8 *dst)
{
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    const Req_WriteFFPmemory_t *s = (const void *)src;
    Rsp_WriteFFPmemory_t *d = (void *)dst;
    UNUSED_OK(d->FFPMemorySelection); //rely on framework
    UNUSED_OK(d->FFPMemoryaddress); //rely on framework
    UNUSED_OK(d->FFPMemoryBlockLength); //rely on framework
    UNUSED_OK(d->FFPMemoryContent); //rely on framework
    FFPMemorySelectionEnum_t memtype = (FFPMemorySelectionEnum_t)util_GetU8(s->FFPMemorySelection[0]);
    u32 addr = util_GetU32(s->FFPMemoryaddress[0]);
    u16 len = util_GetU8(s->FFPMemoryBlockLength[0]);
    switch(memtype)
    {
        case FFPNVMEM:
        {
            ErrorCode_t err;
            MN_NVMEM_LOCK(len);
                err = fram_WriteExt(s->FFPMemoryContent[0], (u16)addr, len, 0);
            MN_NVMEM_UNLOCK();
            if(err != ERR_OK)
            {
                ret = TRANSMITTER_SPECIFIC_COMMAND_ERROR;
            }
            break;
        }
        case FFPRAM:
        {
            memcpy(HARDWARE(void *, addr), s->FFPMemoryContent[0], len);
            break;
        }
        default:
        {
            ret = HART_PASSED_PARAMETER_TOO_LARGE;
            break;
        }
    }
    return ret;
}
/* This line marks the end of the source */
