/**
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file failsafe.h
    \brief A project-specific incarnation of the path to failsafe

Note that it provides redundant path to failsafe (switch and PWM value).

This is not more than abstraction layer. In the case of SVI FF FFAP,
kill PWM output (as the least-code thing), then try to set a fault.

    CPU: Any

    OWNER: AK
*/
#include "pwm.h"
#include "faultpublic.h"
MN_INLINE void mn_fail(void)
{
    /*
    So, the code is bad, and we cannot trust it. Out of paranoia:
    - set I/P to 0
    - set control mode to low ip
    - set OOS failsafe mode
    - set the fault
    The last thing would be sufficient if we trusted the flash
    */
    //AK:TODO: Complete the scheme
    bios_WritePwm(MIN_DA_VALUE);
    error_SetFault(FAULT_FW_CHECKSUM);
}
/* This line marks the end of the source */
