/*
Copyright 2019 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFAP_xlate_10_11.c
    \brief Trivial replacement translation between layouts 10 and 11

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFAP_xlate_10_11.h"

//lint -esym(754, *_t10::*) -esym(754, *_t11::*) Types are for sizes here

CONST_ASSERT(FFAP_NVRAM_ENTRIES_VER_10==FFAP_NVRAM_ENTRIES_VER_11);
CONST_ASSERT(FFAP_NVRAMID_FaultCodeMasks_10==FFAP_NVRAMID_LCDContrasts_11);

#define NUM_FAULT_STORAGE_ATTRIB_10 5
#define FAULT_CODE_BYTES_REQUIRED_10 9
#define BITNUM_FSATTRIB_HIDDEN_10 3

#define BIT_TO_BYTE_SHIFT_10 3u
#define BIT_TO_BYTE_MASK_10  ((1u << BIT_TO_BYTE_SHIFT_10) - 1u)
//bit number within a byte
#define BYTEBITNUM_10(bitnum) ((u8)((bitnum) & BIT_TO_BYTE_MASK_10))

#define BYTEBITMASK_10(bitnum) ((u8)((0x1u << BYTEBITNUM_10(bitnum))))

/** \brief Fault storage attributes table intexed by BITNUM_FSATTRIB_<attrib>
*/
static const u8 faultAttrib_10[NUM_FAULT_STORAGE_ATTRIB_10][FAULT_CODE_BYTES_REQUIRED_10] =
{
    [0] =
    {
        0x00U,
        BYTEBITMASK_10(1U) |
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        BYTEBITMASK_10(4U) |
        0x00U,
        BYTEBITMASK_10(6U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(1U) |
        BYTEBITMASK_10(2U) |
        BYTEBITMASK_10(5U) |
        BYTEBITMASK_10(6U) |
        BYTEBITMASK_10(7U) |
        0x00U,
    },
    [1] =
    {
        0x00U,
        BYTEBITMASK_10(1U) |
        0x00U,
        BYTEBITMASK_10(6U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(2U) |
        BYTEBITMASK_10(7U) |
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        BYTEBITMASK_10(7U) |
        0x00U,
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(6U) |
        0x00U,
    },
    [2] =
    {
        0x00U,
        BYTEBITMASK_10(1U) |
        0x00U,
        BYTEBITMASK_10(6U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(2U) |
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(6U) |
        0x00U,
    },
    [3] =
    {
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
        0x00U,
    },
    [4] =
    {
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(2U) |
        BYTEBITMASK_10(3U) |
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(5U) |
        BYTEBITMASK_10(6U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(2U) |
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(5U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(1U) |
        BYTEBITMASK_10(2U) |
        0x00U,
        BYTEBITMASK_10(1U) |
        BYTEBITMASK_10(3U) |
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(5U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(1U) |
        BYTEBITMASK_10(3U) |
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(5U) |
        BYTEBITMASK_10(6U) |
        BYTEBITMASK_10(7U) |
        0x00U,
        BYTEBITMASK_10(0U) |
        BYTEBITMASK_10(1U) |
        BYTEBITMASK_10(2U) |
        BYTEBITMASK_10(3U) |
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(5U) |
        BYTEBITMASK_10(6U) |
        BYTEBITMASK_10(7U) |
        0x00U,
        BYTEBITMASK_10(3U) |
        BYTEBITMASK_10(5U) |
        BYTEBITMASK_10(6U) |
        0x00U,
        BYTEBITMASK_10(4U) |
        BYTEBITMASK_10(5U) |
        0x00U,
        BYTEBITMASK_10(3U) |
        0x00U,
    },
};

#define FAULT_CODE_BYTES_STORED_10 12 //The # of bytes allocated in NVMEM to store a single copy of faults bitmap
typedef struct FaultCodeMasks_t10
{
    u8 hideInStatusBit[FAULT_CODE_BYTES_STORED_10];
    u8 hideInStatusReport[FAULT_CODE_BYTES_STORED_10];
    u16 CheckWord;
} FaultCodeMasks_t10;

/** \A trivial translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlatedn_11_10(u8 *dst, const u8 *src, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_10; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_FaultCodeMasks_10:
            {
                //default init
                FaultCodeMasks_t10 *FaultCodeMasks = (FaultCodeMasks_t10 *)(void *)(&dst[FFAP_nvram_map_10[id].offset]);
                u32 i;
                for(i=0; i<FAULT_CODE_BYTES_REQUIRED_10; i++)
                {
                    u8 mask = ~faultAttrib_10[BITNUM_FSATTRIB_HIDDEN_10][i];
                    FaultCodeMasks->hideInStatusBit[i] = mask;
                    FaultCodeMasks->hideInStatusReport[i] = mask;
                }
                STRUCT_CLOSE(FaultCodeMasks_t10, FaultCodeMasks);

            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_10[id].offset, src + FFAP_nvram_map_11[id].offset, FFAP_nvram_map_11[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}

typedef struct ContrastCal_t11
{
    s16 temperature;
    u8  contrast;
} ContrastCal_t11;
typedef struct LCDContrasts_t11
{
    ContrastCal_t11 cal[6];
    u8 numpoints;
    u16 CheckWord;
} LCDContrasts_t11;

static const LCDContrasts_t11 contrasts_default_11 =
{
    .cal =
    {
        [0] =
        {
            .temperature = -1500, //STD_FROM_DEGREES_C(-15.0),
            .contrast = 50U,
        },
        [1] =
        {
            .temperature = -1000, //STD_FROM_DEGREES_C(-10.0),
            .contrast = 47U,
        },
        [2] =
        {
            .temperature = 0, //STD_FROM_DEGREES_C(0.0),
            .contrast = 40U,
        },
        [3] =
        {
            .temperature = 8000, //STD_FROM_DEGREES_C(80.0),
            .contrast = 35U,
        },
        //below is don't care
        [4] =
        {
            .temperature = 8000, //STD_FROM_DEGREES_C(80.0),
            .contrast = 35U,
        },
        [5] =
        {
            .temperature = 8000, //STD_FROM_DEGREES_C(80.0),
            .contrast = 35U,
        },
    },
    .numpoints = 4,
    .CheckWord = 0, //don't care
};

/** \A trivial translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlateup_10_11(const u8 *src, u8 *dst, void (*func)(void))
{
    //Common part of layout
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_10; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_LCDContrasts_11:
            {
                STRUCT_GET(&contrasts_default_11, dst + FFAP_nvram_map_11[id].offset);
            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_11[id].offset, src + FFAP_nvram_map_10[id].offset, FFAP_nvram_map_10[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}


/* This line marks the end of the source */
