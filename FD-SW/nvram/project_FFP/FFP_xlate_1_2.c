/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFP_xlate_2_3.c
    \brief Trivial translation between layouts 8 (bank 2) and 9 (same but
            in bank 0 or 1 corresponding to the build)

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFP_xlate_1_2.h"
#include "nvram.h"
#include "evertran.h"


typedef struct FWDLInfo_t2
{
	void *phInfo; //This is an absolute address manufactured by Ernie,
                  //as opposed to linker-generated pointer.
                  //So, it's OK to store it in NVMEM
	u16 CheckWord;
} FWDLInfo_t2;

/** \A trivial translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFP_xlateup_1_2(const u8 *src, u8 *dst, void (*func)(void))
{
    //Copy unchanged and unmoved items
    for(u8_least id = 1U; id<FFP_NVRAM_ENTRIES_VER_1; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_2[id].offset, src + FFP_nvram_map_1[id].offset, FFP_nvram_map_1[id].length);
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, cant' we?
        {
            func();
        }
    }

    //Add new record
    FWDLInfo_t2 *ah = (void *)(dst + FFP_nvram_map_2[FFP_NVRAMID_FWDLInfo_2].offset);
    ah->phInfo = NULL;
    STRUCT_CLOSE(FWDLInfo_t2, ah);

    return ERR_OK;
}

ErrorCode_t FFP_xlatedn_2_1(u8 *dst, const u8 *src, void (*func)(void))
{
    //Copy unchanged and unmoved items
    for(u8_least id = 1U; id<FFP_NVRAM_ENTRIES_VER_1; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_1[id].offset, src + FFP_nvram_map_2[id].offset, FFP_nvram_map_2[id].length);
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, cant' we?
        {
            func();
        }
    }

    return ERR_OK;
}

/* This line marks the end of the source */
