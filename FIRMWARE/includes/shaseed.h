/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file shaseed.h
    \brief Generic API for getting a secret 64-byte hash seed

    CPU: Any

    OWNER: AK

    \ingroup utilities
*/
#ifndef SHASEED_H_
#define SHASEED_H_

/* A pointer to an array is one the murkiest concepts of C.
For clarity, we use a struct instead
*/
typedef struct shakey_t
{
    u8 key[64];
} shakey_t;

extern const shakey_t *util_GetSeedKey(void);

#endif //SHASEED_H_
/* This line marks the end of the source */
