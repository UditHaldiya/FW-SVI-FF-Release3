/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hartvers_compat.c
    \brief HART Data Link protocol - replacement of HART dispatchers table for
compatibility with Release1 of SVI FF. We need same FRAM layout number for
upgrade Release1-->Release2 and HART revision index==1 for downgrade
Release2-->Release1. This table is redirected to by the linker --redirect option.
See conf.mak for redirect

    CPU: Any

    OWNER: AK

    \ingroup HARTDLL
*/
#ifndef _lint
#include "mnwrap.h"
#include "hartvers.h"
//NULL-terminated list of supported dispatchers
CONST_ASSERT((HART_REVS_NUMBER-HART_REV_5)==1);
const hartdispfunc_t * const mnhartdisptab[] =
{
    [HART_REV_5] = hart5_Dispatch,
    [HART_REVS_NUMBER] = hart5_Dispatch,
    [HART_REVS_NUMBER+1] = NULL
};
#endif

//This line marks the end of the source
