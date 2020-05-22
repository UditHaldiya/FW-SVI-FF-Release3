/*
Copyright 2005-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**

    \file sched.h
    \brief Header for API for generic scheduler

    CPU: Any

    OWNER: LS

    \ingroup Sched
*/
#ifndef SCHED_H_
#define SCHED_H_

#include "nvram.h"
#include "faultpublic.h"
#include "devicemode.h"
#include "process.h"

typedef struct SchedTime_t
{
    s64 TimeSince; //!< time in ticks since last monitored event was scheduled
    s64 Guard; //!< guard time in ticks since the event was actually executed (by whatever means)
    tick_t TicksSinceSpecial; //!< control of special timeout due to things like trip grace period
    u16 LastTickCount;      //!< last system tick count used to update TimeSince (small to damage-control glitches)
    u16 CheckWord;
} SchedTime_t;

typedef struct SchedConf_t
{
    bool_t (*sched_Event)(const struct SchedConf_t *SchedConf); //!< a pointer to the event scheduling action (returns true iff scheduled)
    SchedTime_t *SchedTime; //!< a pointer to schedule to work with
    u16 *pTicksAtLastSave; //!< a pointer to NVM save tracker (may be NULL)
    tick_t NVMInterval; //!< nominal ticks between NVM save
    tick_t grace; //!< timeout alarm grace period after a trip
    faultcode_t fcode; //!< timeout fault to set
    devmode_t AllowedModes; //!< device modes bitmask for scheduling
    attribmask_t InhibitingFaults; //!< fault attibutes preventing event scheduling
    ProcId_t ProcessToStart; //!< a process to launch
    nvramId_t NVMid; //!< NVRAMID_... to save to
} SchedConf_t;

extern bool_t sched_EventCommon(const SchedConf_t *SchedConf);
extern void sched_Updater(const SchedConf_t *SchedConf, const s64 intervals[2]);
extern s32 sched_GetMinutesUntilEvent(const SchedConf_t *SchedConf, s32 PlantInterval);
extern void sched_ResetGuard(const SchedConf_t *SchedConf);
extern void sched_Init(const SchedTime_t *src, const SchedConf_t *SchedConf, s64 InitialTimeSince);


#if 0
typedef struct SystemTime_t
{
    s64 TimeUntilNextPST;   //!< time in ticks until pst is run next
    u32 LastTickCount;      //!< last system tick count used to update the TimeUntilNextPST
    u16 CheckWord;
}SystemTime_t;

typedef struct SchedAndGuard_t
{
    SystemTime_t    sched;
    SystemTime_t    guard;
    u16 CheckWord;
} SchedAndGuard_t;
typedef SchedAndGuard_t PneumaticAndGuard_t;

extern void util_MaintainGuard(SystemTime_t *guardSched, s64 grace, faultcode_t fault);
extern void util_SetSystemTime(SystemTime_t* memberTime, s64 Time);
extern void util_Scheduler(SystemTime_t* pTime, devmode_t AllowedMode, attribmask_t InhibitingFaults, s64 RescheduleTime, ProcId_t ProcessToStart);
#endif

#endif  //SCHED_H_

/* This line marks the end of the source */
