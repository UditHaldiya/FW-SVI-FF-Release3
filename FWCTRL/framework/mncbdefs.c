/*
Copyright 2005-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \addtogroup proj Project definitions (ESD)
    \brief A collection of project-defining compile-time constants

*/
/**
    \file mncbdefs.c
    \brief Global project-specific defines

    CPU: Any

    OWNER: AK

    \ingroup proj
*/
#include "mnwrap.h"
#include "mncbdefs.h"
#include "nvram.h"
#include "hartvers.h"


//lint -esym(765, VerString)  ident is used by bsp_a.s79
//lint -esym(714, VerString)  ident is used by bsp_a.s79
//lint -esym(754, VerInfo_t::*)  members used by image massage tool

//required interface; doc in mncbdefs.h
const s16 VerNumber[] =
{
    [0] = SW_REV + (10*(TXSPEC_REV + (10*(MNCB_HW_REV)))),
};

const VerInfo_t VerString[HART_REVS_NUMBER] =
{
#ifdef HART_REV_5
    [HART_REV_5] =
    {
        .signature = 4, //a unique identifier of versioned VerString for Ernie's hex massage
        .trans_spec_revision = TXSPEC_REV,
        .sw_revision = SW_REV,
        .hw_revision = MNCB_HW_REV,
        .fw_type = FIRMWARE_TYPE,
        .date_str = MNCB_DEFAULT_DATE_STRING, /*lint !e784 No nul terminator character*/
        .num_nvm_volumes = NVMEM_MAX_VOLID+1,
        .nvram_version = MNCB_VERSIONS_ARRAY,
        .ManufacturerDeviceCode = MNCB_MANUFACTURER_DEVICE_CODE,
    },
#endif
#ifdef HART_REV_6
    [HART_REV_6] =
    {
        .signature = 4, //a unique identifier of versioned VerString for Ernie's hex massage
        .trans_spec_revision = TRANS_SPEC_REV6,
        .sw_revision = SOFT_REV6,
        .hw_revision = HW_REV6,
        .fw_type = FIRMWARE_TYPE,
        .date_str = MNCB_DEFAULT_DATE_STRING, /*lint !e784 No nul terminator character*/
        .num_nvm_volumes = NVMEM_MAX_VOLID+1,
        .nvram_version = MNCB_VERSIONS_ARRAY,
        .ManufacturerDeviceCode = MNCB_MANUFACTURER_DEVICE_CODE,
    },
#endif
#ifdef HART_REV_7
    [HART_REV_7] =
    {
        .signature = 4, //a unique identifier of versioned VerString for Ernie's hex massage
        .trans_spec_revision = TRANS_SPEC_REV7,
        .sw_revision = SOFT_REV7,
        .hw_revision = HW_REV7,
        .fw_type = FIRMWARE_TYPE,
        .date_str = MNCB_DEFAULT_DATE_STRING, /*lint !e784 No nul terminator character*/
        .num_nvm_volumes = NVMEM_MAX_VOLID+1,
        .nvram_version = MNCB_VERSIONS_ARRAY,
        .ManufacturerDeviceCode = MNCB_MANUFACTURER_DEVICE_CODE,
    },
#endif
};

/* End of source */
