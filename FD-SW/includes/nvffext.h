/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvffext.h
    \brief Extensions to NVRAM functionality to support Softing data model.

    CPU: Any

    OWNER: AK

    \ingroup nvmem
*/
#ifndef NVFFEXT_H_
#define NVFFEXT_H_
#include "nvram.h"
extern bool_t nvmem_IsDelayedWriteFinished(nvramId_t *rid);
extern void nvmem_Mopup(void);
extern ErrorCode_t nvmem_RequestWrite(nvramId_fast_t id);
extern ErrorCode_t nvmem_RequestWriteExt(nvramId_fast_t id, u16 threshold);
#define NV_DEFAULT_DEFER_SIZE 200
#endif //NVFFEXT_H_
/* This line marks the end of the source */
