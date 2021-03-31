/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pstshell.h
    \brief header for partial stroke test interface to the code

    CPU: Any

    OWNER: LS

    \ingroup PST
*/
#ifndef PSTSHELL_H_
#define PSTSHELL_H_
#include "sched.h"
#include "process.h"
#include "dhogtrigger.h"

typedef enum DhogCommTrigger_t
{
    DhogCommDisable,
    DhogCommEnable
} DhogCommTrigger_t;

typedef enum DhogPvTrigger_t
{
    DhogPvDisable,
    DhogPvEnableBelow,
    DhogPvEnableAbove
} DhogPvTrigger_t;

typedef enum DhogDiTrigger_t
{
    DhogDiDisable,
    DhogDiEnableOpen,
    DhogDiEnableClosed
} DhogDiTrigger_t;

//This enum must match the one on FFP side (which must be checked in mn_pst.c)
enum
{
    PST_RUN_SETUP = 0,
    PST_RUN_AUTO_MAN = 1,
    PST_CONFIG = 2,
    PST_VIEW_CONFIG = 3
};

typedef enum PstSchedTrigger_t
{
    PstSchedDisable,
    PstSchedEnable
} PstSchedTrigger_t;

typedef struct PSTrigger_t
{
    PstSchedTrigger_t PstSchedTrigger;
    u8 PstUiTrigger; //
    DhogCommTrigger_t PstCommTrigger;
    DhogDiTrigger_t PstDiTrigger;
    DhogPvTrigger_t PstPvTrigger;
    sig_t pvthreshold;
    s16 interval;           //!< Time in days between PST tests
    u16 CheckWord;
} PSTrigger_t;

extern s32 pst_GetNextPSTTime(void);
//extern void pst_CalculateNextPSTTime(s64 CurrentIntervalTime);
extern ErrorCode_t pst_SetBaseTime(u16 Days, u16 Minutes);
extern void pst_PSTScheduler(void);
extern bool_t pst_IsPSTAllowed(void);
MN_DECLARE_API_FUNC(pst_ResetGuard) //fixme
extern void pst_ResetGuard(void);


//Give unique type for NVMEM table interface
typedef struct SchedTime_t PSTSchedTime_t;
extern const SchedTime_t *pst_GetPSTTimes(SchedTime_t *dst);
extern ErrorCode_t pst_SetInitPSTTimes(const SchedTime_t *src);
UNTYPEACC(pst_SetInitPSTTimes, pst_GetPSTTimes);

extern const PSTrigger_t *pst_GetTriggerInfo(PSTrigger_t *dst);
extern ErrorCode_t pst_SetTriggerInfo(const PSTrigger_t *src);
UNTYPEACC(pst_SetTriggerInfo, pst_GetTriggerInfo);

#define INHIBITING_FAULTS (FATTRIB_FAILSAFE | FATTRIB_FAILHIGH | FATTRIB_LOWPWR)

//Log file interface
#define PST_LOGFILE_NUMCOPIES 1U
#define PST_HEADERSZ 48

#define PST_NUMSAMPLES_MAX 8000
#define PST_LOGFILE_MAXSIZE (PST_NUMSAMPLES_MAX+PST_HEADERSZ)

typedef struct PSTctl_t
{
    s32 target_sp;
    tick_t wait_time;
    s16 speed; //in %/s
    s16 details;
} PSTctl_t;

typedef procresult_t (*PSTstep_t)(PSTctl_t *PSTctl, s32 current_sp);


extern procresult_t pstshell(s16 *procdetails, const PSTstep_t *pststeps, size_t nsteps);

#endif //PSTSHELL_H_
/* This line marks the end of the source */

