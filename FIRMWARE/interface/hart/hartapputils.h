/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hartapputils.c
    \brief API for HART App layer helper utils

     CPU: Any

    OWNER: AK

    \ingroup HART
*/
#ifndef HARTAPPUTILS_H_
#define HARTAPPUTILS_H_

MN_DECLARE_API_FUNC(hart_IsFactoryCmdEnabled) //may or may not be used in a given project
extern bool_t hart_IsFactoryCmdEnabled(void);
//extern enum DeviceModeEnum_t hart_FormatDevModeToHART(devmode_t mode);
//extern devmode_t hart_FormatDevModeToInternal(u8 hmode);
//extern s8_least hart_CheckMode(u8 ModeFlag);
//extern bool_t hart_IsFactoryOptionKey(const u8 key[2]);

//HART-spawned processes (deprecated)
MN_DECLARE_API_MACRO(hart_SetProcessCommand)
/* Why needed: backward compatibility
   Why macro, not a function: process.h may not be in scope and worse,
        may have different type of the parameter
*/
#define hart_SetProcessCommand(procId) (process_SetProcessCommand(procId) != ERR_OK)

#endif //HARTAPPUTILS_H_
/* This line marks the end of the source */
