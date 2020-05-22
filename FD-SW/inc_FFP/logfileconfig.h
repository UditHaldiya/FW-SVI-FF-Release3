/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file logfileconfig.h
    \brief Dimensions etc. for log files support

    CPU: Any

    OWNER: AK

    \ingroup logfile
*/
#ifndef LOGFILECONFIG_H_
#define LOGFILECONFIG_H_
typedef u8 LogfId_t; //the only one currently in use
#define LOGF_IDBITS 4 //Up to 16 event logs
#define LOGF_EXT_COUNT 40 //! Max number of extents we can handle
#endif //LOGFILECONFIG_H_
/* This line marks the end of the source */
