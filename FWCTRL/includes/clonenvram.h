/*
Copyright 2013 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file clonenvram.h
    \brief API for Copy NVMEM to the opposite bank

    CPU: Any

    OWNER: AK

    \ingroup NVRAM
*/

#ifndef CLONENVRAM_H_
#define CLONENVRAM_H_
#include "errcodes.h"
#include "process.h"
extern procresult_t nvmem_Clone(s16 *procdetails);

#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST == OPTION_ON
extern procresult_t nvmem_PrepareUpload(s16 *procdetails);
extern procresult_t nvmem_WriteImageProc(s16 *procdetails);
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST

extern procresult_t nvram_DummyProcess(s16 *procdetails);

/** \brief max allowed length is half the buffer, in diag_t counts;
On commit, we'll preliminarily stick the target bank at that offset
*/
#define NVCLONE_MAX_IMAGE_LENGTH (DIAGNOSTIC_BUFFER_SIZE/2U)

#endif //CLONENVRAM_H_
/* This line marks the end of the source */
