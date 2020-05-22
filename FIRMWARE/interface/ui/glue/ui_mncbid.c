/*
Copyright 2014 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_ffid.c

    Hook implementation for viewing the MNCB-style build version

    Owner: AK
    CPU: Any

*/
#include "mnwrap.h"
#include "mncbdefs.h"
#include "ui_mncbid.h"

const s16 *ui_GetMNCBVerNumber(void)
{
    return &VerNumber[0];
}
/* This line marks the end of the source */

