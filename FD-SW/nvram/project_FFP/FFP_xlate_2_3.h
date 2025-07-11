/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFP_xlate_2_3.h
    \brief Standard layout translation header between layouts 2 and 3
    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#ifndef FFP_XLATE_2_3_H_
#define FFP_XLATE_2_3_H_
#include "errcodes.h"
#include "verdump_types.h"
#include "FFP_verdump_2.h"
#include "FFP_verdump_3.h"
extern ErrorCode_t FFP_xlateup_2_3(const u8 *src, u8 *dst, void (*func)(void));
extern ErrorCode_t FFP_xlatedn_3_2(u8 *dst, const u8 *src, void (*func)(void));
#endif //FFP_XLATE_2_3_H_
/* This line marks the end of the source */
