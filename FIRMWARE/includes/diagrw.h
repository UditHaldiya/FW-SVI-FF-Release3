/*
Copyright 2013 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file diagrw.h
    \brief API for valve diagnostic signature read/write

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/

#ifndef DIAGRW_H_
#define DIAGRW_H_
#include "errcodes.h"
#include "process.h"
#include "bufferhandler.h"
extern ErrorCode_t diag_PrepareSignatureWrite(u8 SignatureType, u8 SignatureAssignment);
extern ErrorCode_t diag_LaunchSignatureWrite(u8 SignatureType, u8 SignatureAssignment);
extern ErrorCode_t diag_LaunchSignatureRead(u8 SignatureType, u8 SignatureAssignment, u8 FileVersion, u8 BufferId);
extern procresult_t diag_WriteBuffer(s16 *procdetails);
extern procresult_t diag_WriteBufferEx(s16 *procdetails, s16_least maxlen);
extern procresult_t diag_ReadBuffer(s16 *procdetails);

//Signature types
#define DIAGRW_EXT_SIGNATURE 0
#define DIAGRW_PST 1

//Signature destinations
#if 0
#define DIAGRW_CURRENT 0
#define DIAGRW_BASELINE 1
#define DIAGRW_USER 2
#else
enum
{
    DIAGRW_CURRENT,
    DIAGRW_BASELINE,
    DIAGRW_USER,
    DIAGRW_PST_DATA
};
#endif

#define DEVID_SIZE (1+1+2) //in halfwords; 1 entry for sampling interval high halfword, 1 entry for number, 2 for HART device id)

#define DIAGRW_HEADERSZ 24 //in diag_t entries; a dogmatic number to please FF params
#define DIAGRW_HEADER_FILLER ((diag_t)0x8081) //Filler of unused stuff

extern void diag_WriteBufferHeader(const diag_t header[], size_t numentries);
#define DIAGRW_WriteBufferHEADER(Header) \
    CONST_ASSERT(NELEM(Header) <= DIAGRW_HEADERSZ);\
    diag_WriteBufferHeader(Header, NELEM(Header))

#endif //DIAGRW_H_
/* This line marks the end of the source */
