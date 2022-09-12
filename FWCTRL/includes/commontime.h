/**
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file commontime.h
    \brief Common time-related definitons

     CPU: Any

    OWNER: EP
*/
#ifndef COMMONTIME_H_
#define COMMONTIME_H_
#include "timebase.h"

//lint ++flb Not all values used by individual projects

//Common time-related constants
#define ONE_SECOND      1000u //! seconds in ms counts
#define DAYS_PER_YEAR      365
#define HOURS_PER_DAY       24
#define MINUTES_PER_HOUR    60
#define SECONDS_PER_MINUTE  60
#define MINUTES_PER_DAY (HOURS_PER_DAY * MINUTES_PER_HOUR)
#define SECONDS_PER_DAY (SECONDS_PER_MINUTE * MINUTES_PER_DAY)

//Conversion of time units to/from timer ticks
#if 0
#define DAYS_TO_TICKS(x)    ((x) * (HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * LCL_TICKS_PER_SEC))
#define HOURS_TO_TICKS(x)   ((x) * (                MINUTES_PER_HOUR * SECONDS_PER_MINUTE * LCL_TICKS_PER_SEC))
#define MINUTES_TO_TICKS(x) ((x) * (                                   SECONDS_PER_MINUTE * LCL_TICKS_PER_SEC))
#define SECONDS_TO_TICKS(x) ((x) * (                                                        LCL_TICKS_PER_SEC))
#else
#define DAYS_TO_TICKS(x)    ((x) * (s64)(HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * LCL_TICKS_PER_SEC))
#define HOURS_TO_TICKS(x)   ((x) * (s64)(                MINUTES_PER_HOUR * SECONDS_PER_MINUTE * LCL_TICKS_PER_SEC))
#define MINUTES_TO_TICKS(x) ((x) * (s64)(                                   SECONDS_PER_MINUTE * LCL_TICKS_PER_SEC))
#define SECONDS_TO_TICKS(x) ((x) * (s64)(                                                        LCL_TICKS_PER_SEC))
#endif

#define TICKS_TO_MINUTES(x) ((x) / (LCL_TICKS_PER_SEC * SECONDS_PER_MINUTE))

//lint --flb Not all values used by individual projects

#endif //COMMONTIME_H_
/* This line marks the end of the source */
