/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file logfproc.c
    \brief API of log files write as a helper for mopup services of process task.

    CPU: Any

    OWNER: AK

    \ingroup logfile
*/
#ifndef LOGFPROC_H_
#define LOGFPROC_H_

#include "errcodes.h"
#include "process.h"
extern void logf_WriteMopup(void);
extern ErrorCode_t logf_SubmitWrite(u8 logId, const void *data, u16 len);
extern procresult_t logf_WriteDeferred(s16 *procdetails);

#endif //LOGFPROC_H_
/* This line marks the end of the source */
