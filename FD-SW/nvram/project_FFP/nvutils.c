/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvutils.c
    \brief A collection of project-specific NVMEM utilities

Project-specific utilities may be required by nvram component
or may be provided for the project-specific use.
In the latter case, prototypes are in nvutils.h.

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "evertran.h"
#include "nvmempriv.h"
#include "watchdog.h"
#include "nvutils.h"
#include <base.h>
#include <fbap.h>
#include "eepshim.h"
#include <swdl_api.h>

#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST == OPTION_ON
//This is a required interface. Doc in header
size_t nvmem_FillDeviceId(void *dst)
{
    UNUSED_OK(dst); //TODO: Replace with APPDeviceID
    return 0;
}
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST

//This is a required interface. Doc in header
/* We assume in the opposite flash bank of FFP
a build with Softing legacy NV management.
We can only deal with it if
1. the error will be returned.
2.    Activation code in FFP should ignore *THIS* error to let the legacy
    build initialize itself
*/
ErrorCode_t nvmem_CheckCompatible(u8 source_layout)
{
    UNUSED_OK(source_layout);
    return ERR_NOT_SUPPORTED;
}

/** \brief A utility to be called on start-up to repair
nvram selected items by flags in their nvram_map entries
\param mask - flags extractor
\param match - to compare against extracted flags bitmap
\return an error code
*/
ErrorCode_t nvmem_FixByFlag(u8 mask, u8 match)
{
    ErrorCode_t err = ERR_OK;
    for(nvramId_fast_t id=0; id < NVRAM_ENTRIES; id++)
    {
        if((nvram_map[id].flags & mask) == match)
        {
            wdog_WatchdogTrigger();
            ErrorCode_t err1 = ram2nvramAtomic(id);
            if(err == ERR_OK)
            {
                err = err1;
            }
        }
    }
    wdog_WatchdogTrigger(); //because Softing objects tend to be large
    return err;
}

const nv_swdl_blk_dwnld_cfg_t swdl_cfg_default =
{
    .data =
    {
        [0] = E_OK,
        [1] = SWDL_DOM_NOT_READY_FOR_DWNLD,
        [2] = 1,
        [3] = 0
    },
    .CheckWord = CRC_SEED //don't care
};
/** \brief Alas, we need to fix SWDL state when converting the
NV image during activation. It is handy to do so at the *source*
image preloaded in diagnostic buffer. See nvmem_LoadImage()
\param src - a pointer to the source image preloaded in the
    diagnostic buffer
*/
void swdl_fix(void *src, u16_least srcVer)
{
    UNUSED_OK(srcVer); //we know it is NVRAM_VERSION
    u8 *bufsrc = src;
    u8 *data = bufsrc + xTable[NVRAM_VERSION].map[NVRAMID_nv_swdl_blk_dwnld_cfg].offset;
    u8 swdl_state = data[1]; //loaded to the buffer from nv_swdl_blk_dwnld_cfg
    if(swdl_state == SWDL_DOM_ACTIVATING)
    {
        src = data;
        Struct_Copy(nv_swdl_blk_dwnld_cfg_t, (nv_swdl_blk_dwnld_cfg_t *)src, &swdl_cfg_default);
    }
}



/* This line marks the end of the source */
