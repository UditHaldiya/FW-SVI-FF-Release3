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
#define NEED_NVMEM_END
#include "mnwrap.h"
#include "evertran.h"
#include MEMMAP_H_
#include "nvramtypes.h"
#include "nvramtable.h"
#include "FFAP_xlate_8_9.h"
#include "FFAP_xlate_9_10.h"
#include "FFAP_xlate_10_11.h"
#include "FFAP_xlate_11_12.h"

const xlatef_t xTable[] =
{
    [0] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [1] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [2] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [3] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [4] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [5] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [6] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [7] = //not supported
    {
        .xup = NULL,
        .xdown = NULL,
        .num_entries = 0,
        .map = NULL,
    },
    [8] =
    {
        .xup = FFAP_xlateup_8_9, //supported up but no "down" version
        .xdown = NULL,
        .num_entries = FFAP_NVRAM_ENTRIES_VER_8,
        .map = FFAP_nvram_map_8,
    },
    [9] =
    {
        .xup = FFAP_xlateup_9_10,
        .xdown = FFAP_xlatedn_9_8,
        .num_entries = FFAP_NVRAM_ENTRIES_VER_9,
        .map = FFAP_nvram_map_9,
    },
    [10] =
    {
        .xup = FFAP_xlateup_10_11,
        .xdown = FFAP_xlatedn_10_9,
        .num_entries = FFAP_NVRAM_ENTRIES_VER_10,
        .map = FFAP_nvram_map_10,
    },
    [11] =
    {
        .xup = FFAP_xlateup_11_12,
        .xdown = FFAP_xlatedn_11_10,
        .num_entries = FFAP_NVRAM_ENTRIES_VER_11,
        .map = FFAP_nvram_map_11,
    },
    [12] =
    {
        .xup = NULL, //supported up but no "up" version yet
        .xdown = FFAP_xlatedn_12_11,
        .num_entries = FFAP_NVRAM_ENTRIES_VER_12,
        .map = FFAP_nvram_map_12,
    },
};

/* This is how "normal" NVMEM entries are organized:

An active logical NVMEM volume must (as of yet) be entirely on a single physical chip (a.k.a. unit).
However, logical NVMEM volumes for different banks may be on different units.
*/

const nvramDumpVolMap_t nvmem_banks[NVMEM_MAX_VOLID+1][NVMEM_NUMBANKS] =
{
    [0] = //!< Volume 0
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

//This must be per volume
CONST_ASSERT(NVMEM_STD_BANK_SIZE > NVM_TOTAL_DATA_LENGTH);

/* This line marks the end of the source */
