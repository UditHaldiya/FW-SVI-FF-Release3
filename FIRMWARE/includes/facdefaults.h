/*
Copyright 2013 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file facdefaults.h
    \brief API for factory defaults read/write

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/

#ifndef FACDEFAULTS_H_
#define FACDEFAULTS_H_
#include "errcodes.h"
#include "process.h"
extern ErrorCode_t nvmem_LaunchFactorySave(void);
extern ErrorCode_t nvmem_LaunchFactoryRestore(u8 volid, u8 mask_flags, u8 match_flags, u8 test_only);
extern procresult_t nvmem_SaveAsFactoryDefaults(s16 *procdetails);
extern procresult_t nvmem_RestoreFactoryDefaults(s16 *procdetails);
extern procresult_t nvmem_RestoreFirmwareDefaults(s16 *procdetails);

typedef struct FactoryDefaultState_t
{
    bool_t first_time;
    u8 fwdl_mode; //!< 1 means classic, 0 - delegate to process, ...
    u16 CheckWord;
} FactoryDefaultState_t;

extern ErrorCode_t facdef_SetState(const FactoryDefaultState_t *src);
//lint -sem(facdef_GetState, pure)
extern const FactoryDefaultState_t *facdef_GetState(FactoryDefaultState_t *dst);
LINT_PURE(facdef_GetState)
extern void facdef_Mopup(void);

UNTYPEACC(facdef_SetState, facdef_GetState);

#endif //FACDEFAULTS_H_
/* This line marks the end of the source */
