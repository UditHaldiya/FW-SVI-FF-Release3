/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file shaseed.c
    \brief SVI FF -specific implementation of API for getting
    a secret 64-byte hash seed; relying on existence and conformance
    of a partition manager.

    CPU: Any

    OWNER: AK (Took over from ERP)

    \ingroup utilities
*/
#include "mnwrap.h"
#include "shaseed.h"

#define V_SIG   7 //   7, partition manager signature
//not used #define V_OFFS  8 //   8, offset to firmware
#define V_KEY   9 //   9, address of SHA256 key
#define V_TRAP 10 //  10, Reserved

#define KEYADD  0x0800006aU          // address of key in original Partition Manager


/** \brief Computes a pointer to the signature key
\return A pointer to a 64-byte signature key.
This implementation is specific to FF project (both FFP and APP)
*/
const shakey_t *util_GetSeedKey(void)
{
    const shakey_t *mykey;
    const u32 *vecs    = HARDWARE(const u32*, 0x8000000U);
    // in older versions the key is at an absolute address
    // in newer versions it is pointed to by the V_KEY index in the vector table
    if ((vecs[V_SIG] == 0xdeadbeefU) && (vecs[V_KEY] != vecs[V_TRAP]))
    {
        //newer version
        mykey = HARDWARE(const shakey_t *, vecs[V_KEY]);
    }
    else
    {
        //original version: address of key in original Partition Manager
        mykey = HARDWARE(const shakey_t *, KEYADD);
    }
    return mykey;
}
/* This line marks the end of the source */
