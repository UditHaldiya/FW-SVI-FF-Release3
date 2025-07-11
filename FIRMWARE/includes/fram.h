/*
Copyright 1999-2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file fram.h
    \brief FRAM interface API

    CPU: Any

    OWNER: AK

    \ingroup sysio
*/
#ifndef FRAM_H_
#define FRAM_H_
#include "errcodes.h"
extern void fram_Initialize(void);

extern ErrorCode_t fram_ReadExt(u8 *data, u32 addr, u32 length, u8_least unit);
extern ErrorCode_t fram_WriteExt(const u8 *data, u32 addr, u32 length, u8_least unit);

//forward compatibility
MN_INLINE ErrorCode_t fram_Read(void *data, u32 addr, u32 length)
{
    return fram_ReadExt(data, addr, length, 0); //main board FRAM
}
MN_INLINE ErrorCode_t fram_Write(const void *data, u32 addr, u32 length)
{
    return fram_WriteExt(data, addr, length, 0); //main board FRAM
}

#endif //FRAM_H_
