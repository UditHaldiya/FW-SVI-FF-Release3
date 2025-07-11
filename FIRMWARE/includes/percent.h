/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file percent.h
    \brief Description of percent data type

Valve position (or, for DLT, level) is computed in several steps of which this file
prepresents the last one (and overal organization).
1. Sensor-specific raw data compensation
2. Sensor-specific linearization
3. Application-specific sensor-independent scaling to the range ("stops"), which may need
    to account for stops drift/adjustment

    CPU: Any

    OWNER: AK

    \ingroup sysio
*/
#ifndef PERCENT_H_
#define PERCENT_H_
/* A type representing generic percent must be sufficient to hold 199.99% and withstand
   application-defined scalings without overflow.
   This may (and currently does) impose restrictions on valid scaling factors; the
   numeric values of the constraints ABSOLUTELY must be checked; preferably at
   compile time (second choice is runtime code optimized out by the compiler, last
   resort is error_SetFault()).
*/

typedef s16 percent_t;
typedef s16_least percent_least_t;

#define STANDARD_NUMBITS 14
#define STANDARD_100 ((s16)(1UL<<STANDARD_NUMBITS)) //16384 ~ 100%
#define STANDARD_ZERO 0 //0 ~ 0%
#define STANDARD_RANGE (STANDARD_100 - STANDARD_ZERO) //of course

//Scaling and Presentation parameters
#define H_PERCENT 57
//units for percent of anything
#define H_PUREPERCENT H_PERCENT
//PURE PERCENT (of anything) - happens to format the same way as position percent of range
#define UNITSID_PERCENT_a STANDARD_ZERO
#define UNITSID_PERCENT_b STANDARD_100
#define UNITS_PUREPERCENT_A 0.0
#define UNITS_PUREPERCENT_B 100.0
#define UNITS_PUREPERCENT_N 2

//Somewhat misplaced but no better place found yet

#define STD_FROM_PERCENT(x) (\
        (percent_least_t)\
        (\
            PRE_ROUND((cdouble_t)(UNITSID_PERCENT_b-UNITSID_PERCENT_a)*(x)\
            /(UNITS_PUREPERCENT_B-UNITS_PUREPERCENT_A)))\
                            )  //converts % to counts

#endif //PERCENT_H_
/* This line marks the end of the source */
