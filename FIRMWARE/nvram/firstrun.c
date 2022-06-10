/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file firstrun.c
    \brief Control of NVMEM backup as "factory"

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "mnassert.h"
#include "facdefaults.h"
#include "nvram.h"
#include "crc.h"

static FactoryDefaultState_t fdstate;
static const FactoryDefaultState_t fdstate_default =
{
    .first_time = true, //We allow FFP to reinitialize fresh, so it MUST be 'true', else the log file won't be created
    .fwdl_mode = 0U, //0 -interleaved, !=0 - sequential
    .CheckWord = 0U, //don't care;
};

/** \brief A write accessor (no data check because there's nothing to check)
NOTE: starts a first-time process if so requested
*/
ErrorCode_t facdef_SetState(const FactoryDefaultState_t *src)
{
    if(src == NULL)
    {
        src = &fdstate_default;
    }
    UNUSED_OK(src->fwdl_mode); //doesn't have to (but may) be used in a project
    Struct_Copy(FactoryDefaultState_t, &fdstate, src);
    if(src->first_time) //This may come from NVRAM translation routine
    {
        process_ForceProcessCommand(PROC_FILE_NVMEM);
    }
    return ram2nvramAtomic(NVRAMID_FactoryDefaultState);
}

/** \brief A standard read accessor
*/
const FactoryDefaultState_t *facdef_GetState(FactoryDefaultState_t *dst)
{
    return STRUCT_TESTGET(&fdstate, dst);
}

/** \brief In case of an error, retries factory defaults save.
Hopefully, it will never activate the process
*/
void facdef_Mopup(void)
{
    if(facdef_GetState(NULL)->first_time)
    {
        (void)process_SetProcessCommand(PROC_FILE_NVMEM);
    }
}
/* This line marks the end of the source */
