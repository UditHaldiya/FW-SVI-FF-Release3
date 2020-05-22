/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hmac.h
    \brief HMAC layer API

    See algorithm description e.g. in
    http://en.wikipedia.org/wiki/Hash-based_message_authentication_code

    CPU: Any

    OWNER: AK

    \ingroup utilities
*/
#ifndef HMAC_H_
#define HMAC_H_
#include "sha256.h"

extern void hmac_init(void (*waitf)(void));
extern void hmac_update(const void *data, size_t len, void (*waitf)(void));
extern void hmac_final(u8 buf[SHA256_BLOCK_SIZE], void (*waitf)(void));

#endif //HMAC_H_
/* This line marks the end of the source */
