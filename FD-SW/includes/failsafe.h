/**
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file failsafe.h
    \brief A project-specific incarnation of the path to failsafe

Note that it provides redundant path to failsafe to break communications to APP
which is then responsible for shutting the device down.

This is not more than abstraction layer. In the case of SVI FF FFP,
corrupt communications speed, then try to set a fault.

    CPU: Any

    OWNER: AK
*/
#include "faultpublic.h"
#include "mn_flash_selftest.h"

#define mn_fail ffpflash_Fail

/* This line marks the end of the source */
