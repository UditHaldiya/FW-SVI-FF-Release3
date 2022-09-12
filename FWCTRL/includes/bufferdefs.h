/*
Copyright 2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file bufferdefs.h
    \brief  Minimally usable pieces extracted from bufferhandler.h for reuse in sister projects

    CPU: Any, with 8-bit bytes

    OWNER: AK

    \ingroup Bufferhandler
*/
#ifndef BUFFERDEFS_H_
#define BUFFERDEFS_H_

#include "dimensions.h" //buffer dimensions

#define DIAGBUF_DEFAULT 0
#define DIAGNOSTIC_BUFFER_SIZE (1U<<DIAG_BUFFER_LOGSIZE)

#if NUM_DIAG_BUFFERS > 1U
#define DIAGBUF_AUX 1
#   ifdef DIAG_BUFFER_LOGSIZE_AUX
#define DIAGNOSTIC_BUFFER_SIZE_AUX (1U<<DIAG_BUFFER_LOGSIZE_AUX)
#   else
#define DIAGNOSTIC_BUFFER_SIZE_AUX DIAGNOSTIC_BUFFER_SIZE
#   endif
#endif

#if DIAGNOSTIC_BUFFER_SIZE < 65536U
typedef u16 bufindex_t;
#else
typedef u32 bufindex_t;
#endif
typedef u32 bufindex_fast_t;

//diagnostic buffer element type
typedef s16 diag_t;

typedef struct dsample_t
{
    diag_t data1;
    diag_t data2;
} dsample_t;

#endif //BUFFERDEFS_H_
/* This line marks the end of the source */
