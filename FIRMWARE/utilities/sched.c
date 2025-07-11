/*
Copyright 2005-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup Sched PST and Pneumatic scheduler
\brief API and implementation of PST and Pneumatic test scheduler
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_Sched Module.doc"> Design document </a><br>
<a href="../../../Doc/TestDocs/utplan_scheduler.doc"> Unit Test Plan </a><br>
\endhtmlonly
*/
/**

    \file sched.c
    \brief Implementation of a generic scheduler

    CPU: Any

    OWNER: LS

    \ingroup Sched
*/
#include "mnwrap.h"
#include "errcodes.h"
#include "mnassert.h"
#include "process.h"
#include "devicemode.h"
#include "timer.h"
#include "commontime.h"
#include "sched.h"
#include "valveutils.h"
#include "oswrap.h"
#include "nvram.h"

#define SCHED_DEC_TICKS      (tick_t)(SECONDS_TO_TICKS(10))          // decrement guard at startup

bool_t sched_EventCommon(const SchedConf_t *SchedConf)
{
    bool_t ret = false;
    //check the mode - scheduled only in normal/AUTO mode
    if((mode_GetEffectiveMode(mode_GetMode()) & SchedConf->AllowedModes) != 0)
    {
        //check for error(s) which prevent pst
        if(!error_IsAnyFaultWithAttributes(SchedConf->InhibitingFaults))
        {
            if (process_SetProcessCommand(SchedConf->ProcessToStart) == ERR_OK)
            {
                // process will run - set the next schedule time
                ret = true;
            }
        }
    }
    return ret;
}



void sched_Updater(const SchedConf_t *SchedConf, const s64 intervals[2])
{
    //First, maintain the timer
    SchedTime_t *pSchedTime = SchedConf->SchedTime;
    Struct_Test(SchedTime_t, pSchedTime);

    SchedTime_t NewSchedTime;
    NewSchedTime.LastTickCount = (u16)timer_GetTicks(); //Take a short (u16) version
    u16 LastTickCount = pSchedTime->LastTickCount;

    u16 ticks = NewSchedTime.LastTickCount - LastTickCount; //wraparound of short version intended
    NewSchedTime.TimeSince = pSchedTime->TimeSince + ticks;
    NewSchedTime.Guard = pSchedTime->Guard + ticks;
    //paranoia
    NewSchedTime.TimeSince = MIN(NewSchedTime.TimeSince, INT64_MAX-UINT32_MAX);
    NewSchedTime.Guard = MIN(NewSchedTime.Guard, INT64_MAX-UINT32_MAX);

    //Maintain grace timer
    NewSchedTime.TicksSinceSpecial = MIN(pSchedTime->TicksSinceSpecial + ticks, INT32_MAX); //limit to half-range

    //Now do event processing
    if(NewSchedTime.TimeSince > intervals[0])
    {
        if(SchedConf->sched_Event(SchedConf))
        {
            //Event scheduled
            NewSchedTime.TimeSince = 0LL;
            //...but not executed - leave the guard alone
        }
    }

    //Now do event timeout
    if(NewSchedTime.Guard > intervals[1])
    {
        if(NewSchedTime.TicksSinceSpecial > SchedConf->grace)
        {
            error_SetFault(SchedConf->fcode);
        }
    }

    //store it
    //See if we want to send it to NVMEM
    u16 *pAtLastSave = SchedConf->pTicksAtLastSave;
    if((pAtLastSave != NULL) && ((u16)(NewSchedTime.LastTickCount - *pAtLastSave) >= SchedConf->NVMInterval))
    {
        //saving enabled
        *pAtLastSave = NewSchedTime.LastTickCount;
        Struct_Copy(SchedTime_t, pSchedTime, &NewSchedTime);
        (void)ram2nvramAtomic(SchedConf->NVMid); //if failed, will try next time
    }
    else
    {
        //no saving
        Struct_Copy(SchedTime_t, pSchedTime, &NewSchedTime);
    }
}

/** \brief Computes the number of minutes until the next event.
Negative means the event is overdue
\param SchedConf - a pointer to the schedule configuration
\param PlantInterval - in minutes; the schedule is modulo it; must be good to hold a year's worth (366*1440)
\return the minutes remaining (0 means less than a minute - or no schedule)
*/
s32 sched_GetMinutesUntilEvent(const SchedConf_t *SchedConf, s32 PlantInterval)
{
    if(PlantInterval <= 0)
    {
        //no schedule
        return 0; //or whatever
    }
    s64 TicksSince = SchedConf->SchedTime->TimeSince;
    s32 MinutesSince = (s32)(TICKS_TO_MINUTES(TicksSince) % PlantInterval);
    return MinutesSince;
}

void sched_ResetGuard(const SchedConf_t *SchedConf)
{
    SchedTime_t *pSchedTime = SchedConf->SchedTime;
    MN_ENTER_CRITICAL();
        storeMemberInt(pSchedTime, Guard, 0);
    MN_EXIT_CRITICAL();
    error_ClearFault(SchedConf->fcode);
    (void)ram2nvramAtomic(SchedConf->NVMid); //AK:TODO: Is ignoring an error the best we can do?
}

void sched_Init(const SchedTime_t *src, const SchedConf_t *SchedConf, s64 InitialTimeSince)
{
    MN_DBG_ASSERT(!oswrap_IsOSRunning());

    SchedTime_t *pSchedTime = SchedConf->SchedTime;
    if(src == NULL)
    {
        //The NVMEMtable must be configured with NULL defaults; that's an indication of default init
        pSchedTime->TimeSince = InitialTimeSince; //run 1st time in that time into interval
        pSchedTime->Guard = 0LL;
        pSchedTime->TicksSinceSpecial = 0;
    }
    else
    {
        //Normal init from FRAM
        *pSchedTime = *src;
        s64 NewGuard = pSchedTime->Guard + SCHED_DEC_TICKS;
        pSchedTime->Guard = NewGuard;
        /* Ernie's comment formerly for contdiag but aplies equally to PST and the action was missing
            N.B. Even though we are still in startup mode reading (or initializing)
            FRAM, we perform a schedule write to update the guard timer.  This is
            to insure that the guard timer will eventually expire even if we never
            make it to normal schedule updates (every 20 seconds)
        */
    }
    pSchedTime->LastTickCount = (u16)bios_GetTimer0Ticker(); //should be 0 but who knows... - short version
    STRUCT_CLOSE(SchedTime_t, pSchedTime);
    (void)ram2nvram(SchedConf->NVMid); //best we can do
}

/* This line marks the end of the source */
