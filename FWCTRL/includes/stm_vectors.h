/*
Copyright 2014 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**

    \file stm_vectors.h

    \brief NVIC cell driver API

    OWNER:
    CPU: STM32F10xx Cortex

*/
#ifndef STM_VECTORS_H_
#define STM_VECTORS_H_
#include "mncbdefs.h"
#include "errcodes.h"
typedef s32 IRQn_t;
extern void MN_NVIC_EnableIRQ(IRQn_t IRQn);
extern void NVIC_SetVectors(void);


/** Needed in the header for sharing with FFP */
//lint -esym(768,vectors_t::*) No explicit member access OK for a memory-mapped peripheral
typedef struct vectors_t
{
    void           *stackPtr;
    irqf_t *Fnct[75];
    const u16      *crcPtr;
    const u16      *dummyPtr;
    const struct ExtraData_t *ExtraData;
} vectors_t;

extern const vectors_t __vector_table;

extern const struct ExtraData_t APPExtraData;

#endif //STM_VECTORS_H_
/* This line marks the end of the source */
