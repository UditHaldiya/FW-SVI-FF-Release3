/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_sp.c
    \brief UI support functions for manual setpoint

     CPU: Any

    OWNER: AK
    \ingroup UI
*/

#ifndef UI_SP_H_
#define UI_SP_H_
#include "uidef.h"
//get/set setpoint
extern uivalvar_t *ui_getManSetpoint(void);
extern void ui_setManSetpoint(void);

extern bool_t ui_IPout_low(const uistate_t *state);
extern bool_t ui_IPout_high(const uistate_t *state);

extern uivalvar_t *ui_GetSetpoint(void);

#endif //UI_SP_H_

/* This line marks the end of the source */
