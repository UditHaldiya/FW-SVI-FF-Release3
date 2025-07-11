/**
Copyright 2004-2005 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file pwm.h
    \brief Header file for BIOS routines for PWM (I to P) output

    CPU: Any (with standard C compiler)

    OWNER: EP
*/

#ifndef PWM_HH_ //PWM_H_ is a symbolic name of the header
#define PWM_HH_

/* This is the range of PWM output, and by its nature, could be unsigned.
However, they are compared to signed quantities which may get negative
(and that's why they turned signed) as a result of output normalization
*/
#define MAX_DA_VALUE   65500
#define MIN_DA_VALUE   35

/* inplace reset parameters
They are empirical; the current calibration methos is this:
1.	measure the time from reset removed to bios_InitPwm. That's the platform-specific boost period.
2.	the boost value is experimentally determined on Varipack at 50% position
*/
#define INPLACE_RESET_PWMBOOST 700 //PWM counts
#define INPLACE_RESET_LENGTH 0.010 //seconds


extern void sysio_InitPwm(void);
extern void bios_InitPwm(void); //not for use outside sysio
extern void bios_WritePwm(u16 value);
extern void pwm_DoWarmstart(void);
extern bool_t pwm_IsWarmstart(void);
extern u16 pwm_GetValue(void);
#endif //PWM_HH_

/* End of the source */
