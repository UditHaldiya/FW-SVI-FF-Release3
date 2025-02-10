/*
Copyright 2004 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file cutoff.c
    \brief Implementation of the full-throttle runs caused by Tight Shutoff,
           Tight Open

     CPU: Any

    \ingroup
*/
/* $History: $

*/
#include "mnwrap.h"
#include "oswrap.h"
#include "faultpublic.h"
#include "devicemode.h"
#include "pwm.h"           /* WritePwm */
#include "sysio.h"
#include "control.h"
#include "ctllimits.h"
//#include "pneumatics.h"
LINT_PURE(pneu_IsSensorInvalid)
#include "position.h"
#include "cutoff.h"


/** private defines */
#define SLOW_APPROACH    FIVE_PCT_819
#define TSO_HYSTERESIS   HALF_PCT_82

typedef struct CutoffConf_t
{
    faultcode_t fcode;
    u16 output[Xends];
} CutoffConf_t;

static const CutoffConf_t CutoffConf[Xends] =
{
    [Xlow] = //cutoff lo
    {
        .fcode = FAULT_POS_CUTOFF_LO,
        .output =
        {
            [0] = MAX_DA_VALUE, //for ATC
            [1] = MIN_DA_VALUE, //for ATO
        },
    },
    [Xhi] = //cutoff hi
    {
        .fcode = FAULT_POS_CUTOFF_HI,
        .output =
        {
            [0] = MIN_DA_VALUE, //for ATC
            [1] = MAX_DA_VALUE, //for ATO
        },
    },
};

/** \brief This function is externally called to determine if the valve is in Full Open/Close
    \parmam[in] void
    \return iff true, valve is in Full Open/Close state
*/
bool_t cutoff_IsActive(void)
{
    return  error_IsFault(CutoffConf[Xlow].fcode) || error_IsFault(CutoffConf[Xhi].fcode);
}


/** \brief Evaluates and executes cutoff (low and high) conditions.
    \param indicator of closed-loop control
    \return  true iff cutoff (either low or high)
*/
static bool_t cutoff_Eval(bool_t closed_loop)
{
    CtlLimits_t         ctlLimits;

    //get control limits (with "Tight" limits)
    (void)control_GetLimits(&ctlLimits);

    //find Setpoint and Position
    s32 Setpoint = ctllim_GetRangeBoundedSetpoint();
    s32 Position = vpos_GetScaledPosition(); //implicit cast is safe (s16 --> s32)
    bool_t bATO = pos_GetPositionConf(NULL)->bATO;

    bool_t ret = false;

    s32 testval1 = Setpoint;
    s32 thresh1 = ctlLimits.TightShutoff[Xlow];
    s32 testval2 = Position;
    s32 thresh2 = thresh1;

    for(u8_least x=Xlow; x<Xends; x++)
    {
        //Cutoff works only in closed-loop mode (where setpoint makes sense)
        if((ctlLimits.EnableTightShutoff[x] == 0) || !closed_loop)
        {
            error_ClearFault(CutoffConf[x].fcode);
        }
        else
        {
            //we are or aren't in tight shutoff - see regardless, out if not in zone
            if( testval1 > (thresh1 + TSO_HYSTERESIS))
            {
                /* Condition tested:
                [Xlo]
                Setpoint > ctlLimits.TightShutoff[Xlow] + TSO_HYSTERESIS
                [Xhi]
                ctlLimits.TightShutoff[Xhi] > Setpoint + TSO_HYSTERESIS, or
                Setpoint < ctlLimits.TightShutoff[Xhi] - TSO_HYSTERESIS
                */
                error_ClearFault(CutoffConf[x].fcode);
            }
            else
            {
                if( (testval1 <= thresh1) && (testval2 <= (thresh2 + SLOW_APPROACH) )  )
                {
                    /* Condition 1 tested:
                    [Xlo]
                    Setpoint <= ctlLimits.TightShutoff[Xlow]
                    [Xhi]
                    ctlLimits.TightShutoff[Xhi] <= Setpoint, or
                    Setpoint >= ctlLimits.TightShutoff[Xhi]
                    */
                    /* Condition 2 tested:
                    [Xlo]
                    Position <= ctlLimits.TightShutoff[Xlow] + SLOW_APPROACH
                    [Xhi]
                    ctlLimits.TightShutoff[Xhi] <= Position + SLOW_APPROACH, or
                    Position >= ctlLimits.TightShutoff[Xhi] - SLOW_APPROACH
                    */
                    error_SetFault(CutoffConf[x].fcode);
                    ret = true;
                }
            }
            if(error_IsFault(CutoffConf[x].fcode))
            {
                u16 CtlOutputValue = CutoffConf[x].output[bool2int(bATO)];
                (void)sysio_WritePwm(CtlOutputValue, PWMSTRAIGHT); //don't care about limiting
            }
        }
        thresh1 = testval1;
        testval1 = ctlLimits.TightShutoff[Xhi];
        thresh2 = testval2;
        testval2 = testval1;
    }
    return ret;
}


/* This line marks the end of the source */
