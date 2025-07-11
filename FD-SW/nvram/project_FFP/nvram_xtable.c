/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvram_xtable.c
    \brief Master NVMEM layout translation table

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "evertran.h"
#include "nvmempriv.h"
#include MEMMAP_H_
#define NEED_NVMEM_END
#include "mnassert.h"
#include "logfsupport.h"
#include "logfdata.h"

#include "FFP_xlate_1_2.h"
#include "FFP_xlate_2_3.h"

CONST_ASSERT(NVMEM_STD_BANK_SIZE >= NVMEM_REGULAR_SIZE_Vol0); //enough room for normal data in a bank?
CONST_ASSERT( ((NVMEMSTART + NVMEM_STD_BANK_SIZE*(NVMEM_MAX_VOLID+1)*NVMEM_NUMBANKS) /*"Normal" data*/
             + EXTENTS_TOTAL_MEMORY_PROJ) /* log files */
             < NVM_PREWRITE_ADDR /* start of reserved area */
                 );
#ifndef NDEBUG
#ifndef _lint
//For visualizing the numbers in the listing and the debugger
__root const struct
{
    u32 nvstart;
    u32 nvbanksize;
    u32 nvbankfree;
    u32 nvnormal_total;
    u32 logf_total;
    u32 nvend;
    u32 nvfree;
} nvstats =
{
    .nvstart = NVMEMSTART,
    .nvbanksize = NVMEM_STD_BANK_SIZE,
    .nvbankfree = NVMEM_STD_BANK_SIZE - NVMEM_REGULAR_SIZE_Vol0,
    .nvnormal_total = NVMEM_STD_BANK_SIZE*(NVMEM_MAX_VOLID+1)*NVMEM_NUMBANKS,
    .logf_total = EXTENTS_TOTAL_MEMORY_PROJ,
    .nvend = NVM_PREWRITE_ADDR,
    .nvfree = NVM_PREWRITE_ADDR - ((NVMEMSTART + NVMEM_STD_BANK_SIZE*(NVMEM_MAX_VOLID+1)*NVMEM_NUMBANKS) /*"Normal" data*/
             + EXTENTS_TOTAL_MEMORY_PROJ),
};
#endif
#endif


/** \brief NVMEM translation table required by embedded vertan
for live activation of the flash/NVMEM bank opposite to the currently active
*/
const xlatef_t xTable[NVRAM_VERSION+1] =
{
    [NV_LAYOUT_LEGACY] = //We reserve 0'th entry as a placeholder for a non-translatable R2 or R1 layout
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [1] =
    {
        .xup = FFP_xlateup_1_2,
        .xdown = NULL,
        .num_entries = FFP_NVRAM_ENTRIES_VER_1,
        .map = FFP_nvram_map_1,
    },
    [2] =
    {
        .xup = FFP_xlateup_2_3,
        .xdown = FFP_xlatedn_2_1,
        .num_entries = FFP_NVRAM_ENTRIES_VER_2,
        .map = FFP_nvram_map_2,
    },
    [3] =
    {
        .xup = NULL,
        .xdown = FFP_xlatedn_3_2,
        .num_entries = FFP_NVRAM_ENTRIES_VER_3,
        .map = FFP_nvram_map_3,
    },
};

/* This is how "normal" NVMEM entries are organized:

An active logical NVMEM volume must (as of yet) be entirely on a single physical chip (a.k.a. unit).
However, logical NVMEM volumes for different banks may be on different units.
*/

const nvramDumpVolMap_t nvmem_banks[NVMEM_MAX_VOLID+1][NVMEM_NUMBANKS] =
{
    [0] = //logical vol 0
    {
        [0] = //to be used with flash bank 0
        {
            .offset = 0,
            .length = NVMEM_STD_BANK_SIZE,
            .volid = 0, //fram physical volume
        },
        [1] = //to be used with flash bank 1
        {
            .offset = (NVMEM_STD_BANK_SIZE + NVMEM_BANK_GAP),
            .length = NVMEM_STD_BANK_SIZE,
            .volid = 0, //fram physical volume
        },
    },
};

/* This line marks the end of the source */
