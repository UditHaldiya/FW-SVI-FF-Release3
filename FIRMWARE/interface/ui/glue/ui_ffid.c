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

    Hook implementation for viewing the FF build version

    Owner: AK
    CPU: Any

*/
#include "mnwrap.h"
#include "uidef.h"
#include "bufutils.h"
#include "ffids.h"
#include "ui_ffid.h"

/** \brief called by ui variable node
to get the ff ids string value for display
*/
u8 ui_GetFFidString(u8 * str, u8 maxlen)
{
    maxlen = MIN(maxlen, sizeof(UI_FFID)-1U);
	util_GetU8Array(UI_FFID, maxlen, str);
	return maxlen;
}
/* This line marks the end of the source */
