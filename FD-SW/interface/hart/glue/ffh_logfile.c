/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_logfile.c
    \brief Intercepted memory manipulation commands

    CPU: Any

    OWNER: AK
*/
#include "mnwrap.h"
//#include "hartfunc.h"
//#include "hartcmd.h"
//#include "bufutils.h"
#include "ffhartdef5.h"
#include "hartdef5.h"

/** \brief A wrapper to resolve name conflict in XML definitions
*/
s8_least hartcmd_ResetFFPLogFileSystem(const u8 *src, u8 *dst)
{
    return hartcmd_ResetLogFileSystem(src, dst);
}

/* This line marks the end of the source */
