/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file diagrw_min.c
    \brief Minimal support for buffer (header) fill, FFP-style

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/
#include "mnwrap.h"
#include "diagrw.h"
#include "bufferhandler.h"
#include <keywords.h>
#include <base.h>
#include <hm_api.h>

/** \brief A quickie util to populate the buffer header
\param header - the header to copy
\param numentries - number of elements in the header
*/
void diag_WriteBufferHeader(const diag_t header[], size_t numentries)
{
    size_t i;
    diag_t *p = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);

    //Stick in device id at the end of the header;
    //If the content is too long, it may overwrite the id
    u32 hdevid = HART_get_dev_id();
    CONST_ASSERT((DEVID_SIZE*sizeof(*p)) >= sizeof(hdevid));
    CONST_ASSERT(DEVID_SIZE < DIAGRW_HEADERSZ);
    diag_t *devid = p + (DIAGRW_HEADERSZ - DEVID_SIZE);
    mn_memset(devid, 0, DEVID_SIZE*sizeof(*devid));
    mn_memcpy(devid, &hdevid, sizeof(hdevid));

    for(i=0; i < numentries; i++)
    {
        p[i] = header[i];
    }
    for(; i < (DIAGRW_HEADERSZ - DEVID_SIZE); i++)
    {
        p[i] = DIAGRW_HEADER_FILLER; //just fill the space with a pleasing filler
    }
}

/* This line marks the end of the source */
