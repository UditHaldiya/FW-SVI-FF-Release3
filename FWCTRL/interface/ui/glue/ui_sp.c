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

#include "mnwrap.h"
#include "devicemode.h"
#include "uidef.h"
#include "ui_sp.h"
#include "ctllimits.h"

#if 0
/*setpoint limits for local UI - values are artificial;
The absolute limits are {MIN, MAX}_ALLOWED_POSITION
*/
//human(e)-readable limits: define here but don't use
#define SETPOINT_INTENDED_MAX (175.0) //of range from zero
#define SETPOINT_INTENDED_MIN (-5.0) // of range from zero

#define SETPOINT_MAX STD_FROM_PERCENT(SETPOINT_INTENDED_MAX)
#define SETPOINT_MIN STD_FROM_PERCENT(SETPOINT_INTENDED_MIN)
#endif

static uivalvar_t setpoint;
/**  A var node data function
\brief Get manual setpoint for display
\return pointer to a scratchpad location now holding manual setpoint
*/
uivalvar_t *ui_getManSetpoint(void)
{
    s32 sp;
    (void)mode_GetIntendedControlMode(&sp); //ctl mode not used

    //setpoint = (s16)CLAMP(sp, POS_SETPOINT_LOW_INT, POS_SETPOINT_HIGH_INT);
    setpoint = (pos_t)CLAMP(sp, SHRT_MIN, SHRT_MAX);
    return &setpoint;
}


/** A var node function
    \brief Set manual setpoint from UI input
*/
void ui_setManSetpoint(void)
{
    //We don't care if setpoint fails to set:
    //mode_SetControlMode(CONTROL_MANUAL_POS, setpoint);
    mode_SetControlMode(CONTROL_MANUAL_POS, CLAMP(setpoint, POS_SETPOINT_LOW_INT, POS_SETPOINT_HIGH_INT));
}

bool_t ui_IPout_low(const uistate_t *state)
{
    UNUSED_OK(state);
    mode_SetControlMode(CONTROL_IPOUT_LOW, SETPOINT_INVALID);
    return false;
}
bool_t ui_IPout_high(const uistate_t *state)
{
    UNUSED_OK(state);
    mode_SetControlMode(CONTROL_IPOUT_HIGH, SETPOINT_INVALID);
    return false;
}

uivalvar_t *ui_GetSetpoint(void)
{
    s32 sp;
    (void)mode_GetIntendedControlMode(&sp); //ctl mode not used
    //setpoint = (s16)CLAMP(sp, SETPOINT_MIN, SETPOINT_MAX);
    setpoint = (pos_t)CLAMP(sp, SHRT_MIN, SHRT_MAX);
    return &setpoint;
}

/* This line marks the end of the source */
