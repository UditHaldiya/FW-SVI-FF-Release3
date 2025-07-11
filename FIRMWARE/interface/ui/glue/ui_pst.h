/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_pst.h
    \brief UI support functions for Partial stroke test

     CPU: Any

    OWNER: AK

    \ingroup UI
*/
#ifndef UI_PST_H_
#define UI_PST_H_

#include "pst.h"
#include "pstshell.h"

extern bool_t ui_pst(const uistate_t *state);
extern bool_t ui_GetPstConf(const uistate_t *state);
extern bool_t ui_SetPstConf(const uistate_t *state);
extern s16 *ui_GetPstConfData(void);
#define UI_PSTINDEX(member) (MN_OFFSETOF(PSTConf_t, member)/sizeof(s16))
extern const void *ui_IsPSTEnabled(void);

#endif //UI_PST_H_
/* This line marks the end of the source */
