/*
Copyright 2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup boolmon "Digital input" pattern monitor utility
\brief "Digital input" pattern monitor utility
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_DI Utility Module.doc"> Design document </a><br>
\endhtmlonly
*/
/**
    \file boolmon.c
    \brief support for monitoring a specific on-off pattern of a "virtual" digital
            input of any sort.

    CPU: Any

    OWNER: AK

    \ingroup boolmon
*/
#include "mnwrap.h"
#include "boolmon.h"
#include "numutils.h"
#include "crc.h"

static void boolmon_setlink(boolmonstate_t *boolmonstate, const boolmon_t *boolmondef, s8 link)
{
    boolmonstate->timeleft = boolmondef[link].timelim;
    boolmonstate->index = link;
}

void boolmon_init(boolmonstate_t *boolmonstate, const boolmon_t *boolmondef)
{
    boolmon_setlink(boolmonstate, boolmondef, 0);
    boolmonstate->ticks = bios_GetTimer0Ticker();
    STRUCT_CLOSE(boolmonstate_t, boolmonstate);
}

/**
Transition can be caused by state timeout or by input mismatch
Input mismatch (edge) is what's expected in a valid pattern; it causes a function call
    and a transition to the next state.
Timeout simply transitions to the next state and optionally sets a fault/event
If transition causes input mismatch, the monitor is reset
\param input - true actove, false inactive
\return one of:
  BOOLMON_PATTERN_SEARCH - pattern not found; looking
  BOOLMON_PATTERN_MATCH - pattern found; monitor auto-reset
  BOOLMON_PATTERN_FAULT - suspicious pattern found; monitor auto-reset
*/
s8 boolmon_run(boolmonstate_t *boolmonstate, const boolmon_t *boolmondef, bool_t input)
{
    Struct_Test(boolmonstate_t, boolmonstate);
    tick_t t = timer_GetTicks();
    tick_t prev = boolmonstate->ticks;
    boolmonstate->ticks = t; //save the tick mark
    t -= prev; //that many ticks since prev. call
    s8 index = boolmonstate->index;
    s8 ret = 0;
    s8 link;
    if(!equiv(input, boolmondef[index].stateval))
    {
        link = boolmondef[index].mismatch_link;
        if(link <0 )
        {
            ret = link;
            link = 0;
        }
        boolmon_setlink(boolmonstate, boolmondef, link); //reset monitor
    }
    else
    {
        if(boolmonstate->timeleft > t)
        {
            boolmonstate->timeleft -= t; //keep time
        }
        else
        {
            //time expired, but only if it can
            if(boolmondef[index].timelim != 0)
            {
                link = boolmondef[index].timeout_link;
                if(link < 0)
                {
                    ret = link;
                    link = boolmondef[index].reset_link;
                }
                boolmon_setlink(boolmonstate, boolmondef, link); //reset monitor
            }
        }
    }
    STRUCT_CLOSE(boolmonstate_t, boolmonstate);
    return ret;
}
/* This line marks the end of the source */
