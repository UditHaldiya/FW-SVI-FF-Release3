/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file evertran.h
    \brief API for embedded vertran (NVMEM layout translation)

     CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#ifndef EVERTRAN_H_
#define EVERTRAN_H_
#include "errcodes.h"
#include "verdump_types.h"
#include "vertranpub.h"
#include "nvdimensions.h"
#include "mncbdefs.h"

typedef ErrorCode_t xlateUp_t(const u8 *src, u8 *dst, void (*func)(void));
typedef ErrorCode_t xlateDown_t(u8 *dst, const u8 *src, void (*func)(void));
//lint -esym(768, xlatef_t::*) OK if not referenced
struct xlatef_t
{
    xlateUp_t *xup;
    xlateDown_t *xdown;
    size_t num_entries;
    const nvramDumpMap_t *map; //!< The cumulative volume-agnostic map for in-buffer manipulation
};
typedef struct xlatef_t xlatef_t;

extern const xlatef_t xTable[MNCB_VERSION_NUMBER+1U];

#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST == OPTION_ON
/** \brief Project-specific plugin to populate device id
\param dst - a pointer to destination buffer
\return filled size in bytes
*/
extern size_t nvmem_FillDeviceId(void *dst);
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST

/** \brief Project-specific plugin to decide how to proceed
with NVMEM translation if the build in the opposite flash bank
doesn't supply layout information
\param source_layout - NVMEM layout of the running build
\return an error code
*/
extern ErrorCode_t nvmem_CheckCompatible(u8 source_layout);

MN_DECLARE_API_FUNC(changeVersionId)
struct StartupVersionNumber_t;
extern void changeVersionId(const struct StartupVersionNumber_t *src, struct StartupVersionNumber_t *dst, s8_least dir);

#endif //EVERTRAN_H_
/* This line marks the end of the source */
