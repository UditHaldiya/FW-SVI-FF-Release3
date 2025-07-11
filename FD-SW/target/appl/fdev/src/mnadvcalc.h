/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mnadvcalc.c
    \brief An API helper for "Advanced" key calculations

    CPU: Any

    OWNER: AK

    \ingroup advkey
*/
#ifndef MNADVCALC_H_
#define MNADVCALC_H_

#include <stdlib.h>

extern u32 mn_CalcAdvanced(size_t advkey_sz, const u8 *advkey, size_t devid_sz, const u8 *dev_id);
#endif //MNADVCALC_H_
/* This line marks the end of the source */
