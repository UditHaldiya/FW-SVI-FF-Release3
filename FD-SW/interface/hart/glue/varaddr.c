/*
Copyright 2019 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file varaddr.c
    \brief The table of "variables" sizes and addresses

    CPU: Any

    OWNER: AK

    \ingroup rammap
*/

#include "mnwrap.h"
#include "ffhartdef5.h"
#include "bufutils.h"
#include "hartfunc.h"
#include "nvdimensions.h"

static void var_totalNVM(uintptr_t *offset, size_t *length)
{
    *offset = 0;
    *length = NVRAM_PARTITION_REMAP_SIZE;
}

typedef void varaccess_t(uintptr_t *offset, size_t *length);

static varaccess_t * const vartable[] =
{
    [0] = var_totalNVM,
};

s8_least hartcmd_ReadVarAddress(const u8 *src, u8 *dst)
{
    const Req_ReadVarAddress_t *s = (const void *)src;
    u8 index = util_GetU8(s->VarIndex[0]);

    s8_least ret;
    if(index >= NELEM(vartable))
    {
        ret = HART_INVALID_SELECTION;
    }
    else
    {
        uintptr_t offset;
        size_t length;
        vartable[index](&offset, &length);

        Rsp_ReadVarAddress_t *d = (void *)dst;
        util_PutU32(d->VarAddress[0], offset);
        util_PutU32(d->VarLength[0], length);

        ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    }

    return ret;
}
/* This line marks the end of the source */

