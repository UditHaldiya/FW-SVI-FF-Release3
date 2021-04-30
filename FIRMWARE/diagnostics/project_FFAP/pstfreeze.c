/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pstfreeze.c
    \brief Implementation of project-specific API for SVI FF/APP flavor of PST

    CPU: Any

    OWNER: AK

    \ingroup PST
*/

#include "mnwrap.h"
#include "pst.h"
#include "ctllimits.h"
#include "selftune.h"

ErrorCode_t pst_Freeze(PstFreeze_t freeze_options)
{
    CtlLimits_t lims;
    ErrorCode_t err = ERR_INVALID_PARAMETER;
    if(ctllim_GetPermLimits(&lims) != NULL)
    {
        pos_t speed = diag_GetPstData(NULL)->ramp_speed;
        if(lims.Protected != 0)
        {
            freeze_options |= PST_FREEZE_SPRATE | PST_FREEZE_SPRANGE | PST_FREEZE_CUTOFF;
        }
        for(s8_least x = Xlow; x < Xends; x++)
        {
            if(((freeze_options & PST_FREEZE_SPRATE) != 0U) && (lims.EnableSetpointRateLimit[x] != 0))
            {
                lims.SetpointRateLimit[x] = MIN(lims.SetpointRateLimit[x], speed);
            }
            else
            {
                if(speed > INT_PERCENT_OF_RANGE(SP_RATE_LIMIT_HIGH))
                {
                    lims.EnableSetpointRateLimit[x] = 0;
                }
                else
                {
                    lims.EnableSetpointRateLimit[x] = 1;
                    lims.SetpointRateLimit[x] = speed;
                }
            }
            if((freeze_options & PST_FREEZE_SPRANGE) == 0U)
            {
                lims.EnableSetpointLimit[x] = 0;
            }
            if((freeze_options & PST_FREEZE_CUTOFF) == 0U)
            {
                lims.EnableTightShutoff[x] = 0;
            }
        }
        err = control_SetTentativeLimits(&lims);
    }
    //New: deadzone
    if(err == ERR_OK)
    {
        if((freeze_options & PST_FREEZE_DEADZONE) == 0U)
        {
            PIDData_t wrk;
            (void)tune_GetWorkinPIDData(&wrk);
            wrk.DeadZone = 0;
            err = tune_SetCurrentPIDData(&wrk);
        }
    }

    return err;
}

/** \brief Undo "damage" done by PST steps
*/
void pst_UnFreeze(PstFreeze_t freeze_options)
{
    UNUSED_OK(freeze_options);
    cnfg_ReEnableLimits();
    (void)tune_SetCurrentPIDData(tune_GetPIDData(posctl_GetCtlset(NULL)->slot, NULL));

}

/* This line marks the end of the source */
