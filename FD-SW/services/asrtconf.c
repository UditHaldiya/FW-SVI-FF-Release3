/*
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file asrtconf.c
    \brief An assert configuration data (FFP flavor)

    \ingroup Assert

    CPU: Any

    OWNER: AK
*/

#include "mnwrap.h"
#include "timebase.h"
#include <base.h>
#include "appl_alert.h"
#include "mnassert.h"

const AssertConf_t AssertConf =
{
    .lifespan = MN_MS2TICKS(30000),
    .hook = Alert_ExpireAssertHook,
};
/* This line marks the end of the source */
