/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFAP_xlate_12_13.h
    \brief Standard layout translation header between layouts 12 and 13
    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#ifndef FFAP_XLATE_12_13_H_
#define FFAP_XLATE_12_13_H_
#include "errcodes.h"
#include "verdump_types.h"
#include "FFAP_verdump_12.h"
#include "FFAP_verdump_13.h"
extern ErrorCode_t FFAP_xlateup_12_13(const u8 *src, u8 *dst, void (*func)(void));
extern ErrorCode_t FFAP_xlatedn_13_12(u8 *dst, const u8 *src, void (*func)(void));
#endif //FFAP_XLATE_11_12_H_
/* This line marks the end of the source */
