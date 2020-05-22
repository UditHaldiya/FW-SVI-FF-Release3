/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvffext.c
    \brief Extensions to NVRAM functionality to support Softing data model.

    It is here that the (design) decision on delayed writes vs. inline writes
    is made. For now, while we have large objects, we use delayed writes

    CPU: Any

    OWNER: AK

    \ingroup nvmem
*/
#include "mnwrap.h"
#include "crc.h"
#include "nvffext.h"
#include "nvmempriv.h"

typedef struct nv_req_t
{
    u8 nv_write_req[NVRAM_ENTRIES];
    u16 CheckWord;
} nv_req_t;

static nv_req_t nv_req =
{
    .nv_write_req = {0}, //lint !e943 too few initializers: 0's OK and allowed by MISRA 3
    .CheckWord = CRC_SEED,
};

#ifndef NDEBUG
//lint -esym(551, writes_pending) not accessed
static u8 writes_pending = 0; //for debug only, count pending writes
#endif

static u8 currblock = 0;
static u8 runid = 0;

/** \brief creates a request for an eep block to be written.

For inline writes, this function would map to ram2nvramAtomic,
and nvmem_Mopup would become empty (or removed altogether)
\param id - A block to write
\return an error code
*/
ErrorCode_t nvmem_RequestWrite(nvramId_fast_t id)
{
    return nvmem_RequestWriteExt(id, NV_DEFAULT_DEFER_SIZE);
}

/** \brief creates a request for an eep block to be written.

For inline writes, this function would map to ram2nvramAtomic,
and nvmem_Mopup would become empty (or removed altogether)
\param id - A block to write
\return an error code
*/
ErrorCode_t nvmem_RequestWriteExt(nvramId_fast_t id, u16 threshold)
{
    ErrorCode_t err;
    if(( nvram_map[id].length + nvmem_GetCurrentSize()) < threshold)
    {
        err = ram2nvramAtomicExt(id, NV_ALLCOPIES);
    }
    else
    {
        MN_ENTER_CRITICAL();
            if(nv_req.nv_write_req[id] == 0)
            {
                storeMemberInt(&nv_req, nv_write_req[id], 1);
#ifndef NDEBUG
                writes_pending++;
#endif
            }
        MN_EXIT_CRITICAL();
        err = ERR_OK;
    }
    return err;
}


/** \brief Finds and writes requested NVRAM records (if any) (deferred writes)
*/
void nvmem_Mopup(void)
{
    nvramId_t i;
    for(i=currblock; i<NVRAM_ENTRIES; i++)
    {
        u8 write_req;

        MN_ENTER_CRITICAL();
            write_req = nv_req.nv_write_req[i];
            storeMemberInt(&nv_req, nv_write_req[i], 0);
        MN_EXIT_CRITICAL();
        Struct_Test(nv_req_t, &nv_req);

        if(write_req != 0)
        {
            ErrorCode_t err = ram2nvramAtomicExt(i, NV_ALLCOPIES);
            if(err != ERR_OK)
            {
                MN_ENTER_CRITICAL();
                    storeMemberInt(&nv_req, nv_write_req[i], 1); //will try next time
                MN_EXIT_CRITICAL();
            }
            break;
        }
    }
    if(i < NVRAM_ENTRIES)
    {
        currblock = i+1;
    }
    else
    {
        currblock = 0;
        runid++; //wraparound OK
    }
}

/** \brief Checks if delayed write cycle is completed
\param rid - a pointer to run id [in] captured [out] current
\return true iff complete run cycle is finished
*/
bool_t nvmem_IsDelayedWriteFinished(nvramId_t *rid)
{
    nvramId_t diff = runid - *rid;
    *rid = runid;
    return diff >=2U;
}

/* This line marks the end of the source */
