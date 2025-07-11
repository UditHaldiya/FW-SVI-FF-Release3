/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hmac.c
    \brief HMAC layer (on top of SHA256 hash)

    See algorithm description e.g. in
    http://en.wikipedia.org/wiki/Hash-based_message_authentication_code

    The implementation here adds an insertion of a "wait function" whose
    only purpose is to help keep system timing right, e.g. checking into
    the watchdog system.

    CPU: Any

    OWNER: AK

    \ingroup utilities
*/

#include "mnwrap.h"
#include "shaseed.h"
#include "hmac.h"

#define HMAC_IPAD		    0x36U
#define HMAC_OPAD		    0x5cU

/** \brief Common initializer for the two steps of HMAC

Assumes (asserts) the key size is exactly 64 bytes.
Computes I or O key pad and initializes sha256 hash with the key pad included

\param waitf - a pointer to a wait function (e.g. check into watchdog system)
\param padv - one of HMAC_IPAD or HMAC_OPAD
*/
static void hmac_init_keypad(void (*waitf)(void), u8 padv)
{
    sha256_init();
    if(waitf != NULL)
    {
        waitf();
    }
	u32 ix = 0;
    const u8 *key = util_GetSeedKey()->key;

	CONST_ASSERT(sizeof(shakey_t) == BLOCKSZ);
    while (ix < BLOCKSZ)
	{
		u8 tc = key[ix++] ^ padv;
		sha256_update(&tc, 1);
	}
    if(waitf != NULL)
    {
        waitf();
    }
}

/** \brief Public initializer of HMAC layer.
Implements step 1 (i key pad hasing) so the sha state is ready to receive the
"message" stream
\param waitf - a pointer to a wait function
*/
void hmac_init(void (*waitf)(void))
{
    hmac_init_keypad(waitf, HMAC_IPAD);
}

#define SHA_CHUNK 30 //somewhat arbitrary but must be small enough not to interest the watchdog

/** \brief Just a handy wrapper with a wait
\param data - a pointer to data to hash
\param len - the length of data in bytes
\param waitf - a pointer to a wait function
*/
void hmac_update(const void *data, size_t len, void (*waitf)(void))
{
    const u8 *src = data;
    while(len > 0)
    {
        size_t chunk = MIN(SHA_CHUNK, len);
        sha256_update(src, chunk);
        len -= chunk;
        src += chunk;
        if(waitf != NULL)
        {
            waitf();
        }
    }
}

/** \brief Final step of HMAC calculation, including final sha256 step
for the "message" and full Step 2 of HMAC
\param buf[out] - a buffer containing the HMAC hash
\param waitf - a pointer to a wait function
*/
void hmac_final(u8 buf[SHA256_BLOCK_SIZE], void (*waitf)(void))
{

    sha256_final(buf); //end of first pass (with the "message")
    if(waitf != NULL)
    {
        waitf();
    }

    //Now, do the second pass
    hmac_init_keypad(waitf, HMAC_OPAD); //hash the O key pad
    sha256_update(buf, SHA256_BLOCK_SIZE); //append the digest of pass 1
    if(waitf != NULL)
    {
        waitf();
    }
    sha256_final(buf);
    if(waitf != NULL)
    {
        waitf();
    }
}

/* This line marks the end of the source */

