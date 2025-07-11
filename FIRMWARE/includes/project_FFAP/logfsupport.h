/*
Copyright 2006-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file logfsupport.h
    \brief A handy wrapper of all project-specific headers needed to compile
    logfdata.c. Similar in purpose to nvramtypes.h

    CPU: Any

    OWNER: AK

    \ingroup logfile
*/
#ifndef LOGFSUPPORT_H_
#define LOGFSUPPORT_H_
#include "diagnostics.h"
#include "bufferhandler.h"
#include "nvramtypes.h" //needed for nvramtable.h
#include "nvramtable.h"

#include "nvdimensions.h"
CONST_ASSERT(NVMEM_MAX_VOLID==0); //sanity check
#define NVRAM_BACKUP_SIZE (NVMEM_REGULAR_SIZE_Vol0/NV_NUMCOPIES)
#endif //LOGFSUPPORT_H_
/* end of source */
