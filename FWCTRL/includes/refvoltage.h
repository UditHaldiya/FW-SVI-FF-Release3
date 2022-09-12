/*
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file refvoltage.h
    \brief Public interfaces of the reference voltage handling

    CPU: Any

    OWNER: AK

*/
#ifndef REFVOLTAGE_H_
#define REFVOLTAGE_H_

#include "errcodes.h"

typedef struct RefVoltage_t
{
    u32 HiLimit;
    u32 LoLimit;
    u16 CheckWord;
} RefVoltage_t;


/** Public functions
 *
*/
ErrorCode_t refvoltage_SetData(const RefVoltage_t* pRefVoltage);
const RefVoltage_t* refvoltage_GetData(RefVoltage_t *dst);

UNTYPEACC(refvoltage_SetData, refvoltage_GetData);

extern void periodicjob_RefVoltage(void);


#endif // REFVOLTAGE_H_
/* This line marks the end of the source */
