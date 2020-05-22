/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file posctlmode.h
    \brief public interfaces of device mode manager

     CPU: Any

    OWNER: AK

    \ingroup Modeman
*/
#ifndef POSCTLMODE_H_
#define POSCTLMODE_H_
#include "devicemode.h"

//lint -strong(AJX, ctlmode_t) //DO NOT mix control mode with anything else
typedef enum ctlmode_t
{
    CONTROL_INVALID, //!< a dummy mode that expires immediately and leads to guessing the mode
    CONTROL_IP_DIAGNOSTIC, //!< translates input to output
    CONTROL_MANUAL_POS, //!< normal setpoint control mode (to the however computed setpoint)
    CONTROL_IPOUT_LOW, //!< true zero I/P output (with PWM shut off)
    CONTROL_IPOUT_LOW_FAIL, //!< true zero I/P output (with PWM shut off) caused by fail low failures
    CONTROL_IPOUT_HIGH, //!< max allowed I/P output
    CONTROL_IPOUT_HIGH_FACTORY, //!< max allowed I/P output allowed in factory setting only
    CONTROL_IPOUT_HIGH_FAIL, //!< max allowed I/P output caused by certain (failhigh) failures
    CONTROL_OFF, //!< direct output control mode; requires process context
    CONTROL_IPOUT_LOW_PROC,  //!< zero I/P mode that requires process context
    CONTROL_IPOUT_HIGH_PROC //!< full I/P mode that requires process context
} ctlmode_t;

extern void mode_GuardControlMode(void);
extern void mode_SetControlMode(ctlmode_t ctlmode, s32 setpoint);

extern ctlmode_t mode_GetIntendedControlMode(s32 *sp); //raw
extern ctlmode_t mode_GetEffectiveControlMode(s32 *sp); //cooked

extern const ctlmode_t mode_ControlModeMap[];

/** \brief A project-dependent way of computing the setpoint at device mode change
\param mode - pointer to the device mode
\param ctlmode - control mode
\return the setpoint
*/
extern s32 mode_GuessSetpoint(devmode_t mode, ctlmode_t ctlmode);

/** \brief A project-dependent way of jamming the setpoint to a desired value based on modes
\param mode - pointer to the device mode
\param ctlmode - control mode
\param sp - a preliminary setpoint
\return a possibly modified setpoint
*/
extern s32 mode_GuardSetpoint(devmode_t mode, ctlmode_t ctlmode, s32 sp);

extern s32 mode_DirectOutput(ctlmode_t ctlmode, s32 ctlout); //find a better header

#endif //POSCTLMODE_H_
