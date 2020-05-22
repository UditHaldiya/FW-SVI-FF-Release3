/*
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvdimensions.h
    \brief  Sizes/volumes configurations for NVMEM layout

Must contain plain definitions as decimal numbers (U suffix is allowed) and comment
Anything else won't be visible to Unimal

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#ifndef NVDIMENSIONS_H_
#define NVDIMENSIONS_H_

#define NVRAM_PARTITION_REMAP_SIZE 8192 //! offset per NVMEM bank
#define NVMEM_MAX_VOLID 0 //Valid NVMEM volumes are 0 through 0
#define EXTMEM /*nothing*/

#define NV_LAYOUT_LEGACY 8U //! default NVMEM layout if none other is specified

#endif //NVDIMENSIONS_H_

/* This line marks the end of the source */
