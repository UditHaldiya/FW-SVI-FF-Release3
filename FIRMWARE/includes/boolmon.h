/*
Copyright 2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file boolmon.h
    \brief the API of monitoring a specific on-off pattern of a "virtual" digital
            input of any sort.

    CPU: Any

    OWNER: AK

    \ingroup boolmon
*/
#ifndef BOOLMON_H_
#define BOOLMON_H_

#include "timebase.h"
#include "timer.h"
typedef tick_t boolmontime_t; //! "digital input" time format in control cycle counts

typedef struct boolmon_t
{
    boolmontime_t timelim;
    bool_t stateval;
    s8 mismatch_link;
    s8 timeout_link;
    s8 reset_link; //must be a non-negative valid index
} boolmon_t;

//This type must be opaque to the app who just provides a container
typedef struct boolmonstate_t
{
    tick_t ticks;
    boolmontime_t timeleft;
    s8 index;
    u16 CheckWord;
} boolmonstate_t;

//Suggested/optional states. Another way is to use a typeless enum for states
MN_DECLARE_API_MACRO(BOOLMON_PATTERN_*)
#define BOOLMON_PATTERN_FAULT (-1) //! return code indicating fault in pattern (optional)
#define BOOLMON_PATTERN_MATCH (-2) //! return code indicating match in pattern (mandatory)
#define BOOLMON_PATTERN_SEARCH (0)
//Sample times:
MN_DECLARE_API_MACRO(BOOLMON_*S)
#define BOOLMON_1S MN_MS2TICKS(1000)
#define BOOLMON_2S MN_MS2TICKS(2000)
#define BOOLMON_3S MN_MS2TICKS(3000)
#define BOOLMON_HalfS MN_MS2TICKS(500)
//lint +e755

//extern void boolmon_init(boolmonstate_t *boolmonstate, const boolmon_t *boolmondef);
//extern s8 boolmon_run(boolmonstate_t *boolmonstate, bool_t input);
extern void boolmon_init(boolmonstate_t *boolmonstate, const boolmon_t *boolmondef);
extern s8 boolmon_run(boolmonstate_t *boolmonstate, const boolmon_t *boolmondef, bool_t input);

#endif //BOOLMON_H_
/* This line marks the end of the source */
