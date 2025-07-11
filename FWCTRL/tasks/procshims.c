/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file procshims.c
    \brief Necessary wrappers for legacy or normal mode processes

    CPU: Any

    OWNER: AK

    \ingroup Process
*/
#include "mnwrap.h"
#include "process.h"
#include "procpriv.h"
#include "procshims.h"

#include "control.h"
#include "nvram.h"
#include "selftune.h"
#include "diagnostics.h"
#include "hartfunc.h"
#include "tempcomp.h"

#include "ctllimits.h"

//for bad wrappers
#include "devicemode.h"
#include "oswrap.h"

//------- Good shims - wrappers of bare processes -----------------
//------- Backward compatibility shims - wrappers of old processes ------------------

//One step of NVMEM test
procresult_t nvram_PageTest_SHIM(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    nvram_PageTest();
    return PROCRESULT_OK;
}

procresult_t tune_Run_Selftune_SHIM(s16 *procdetails)
{
    return control_ProcWithNoLimits(tune_Run_Selftune, procdetails);
}

procresult_t diag_Run_StepTest_SHIM(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    diag_Run_StepTest();
    return PROCRESULT_OK;
}

#ifdef OLD_NVRAM
procresult_t hart_procRamCommitNoCal_SHIM(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    hart_procRamCommit(false);
    return PROCRESULT_OK;
}

procresult_t hart_procRamCommitWithCal_SHIM(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    hart_procRamCommit(true);
    return PROCRESULT_OK;
}

procresult_t comp_SaveAllComp_SHIM(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    comp_SaveAllComp(); //NOTE: old OLD_NVRAM  thus needs old tempcomp
    return PROCRESULT_OK;
}

#else
//Real brutal
static bool_t select_Vol0_NonTempcomp(u8 volid, u8 flags)
{
    return(volid==0) && ((flags & NVMFLAG_CALIB1) == 0);
}
static bool_t select_Vol0_Tempcomp(u8 volid, u8 flags)
{
    return(volid==0) && ((flags & NVMFLAG_CALIB1) != 0);
}
static bool_t select_Vol0_All(u8 volid, u8 flags)
{
    UNUSED_OK(flags);
    return(volid==0);
}

procresult_t hart_procRamCommitNoCal_SHIM(s16 *procdetails)
{
    (void)ram_CommitRange(select_Vol0_NonTempcomp);
    UNUSED_OK(procdetails);
    return PROCRESULT_OK;
}

procresult_t hart_procRamCommitWithCal_SHIM(s16 *procdetails)
{
    (void)ram_CommitRange(select_Vol0_All);
    UNUSED_OK(procdetails);
    return PROCRESULT_OK;
}

procresult_t comp_SaveAllComp_SHIM(s16 *procdetails)
{
    (void)ram_CommitRange(select_Vol0_Tempcomp);
    UNUSED_OK(procdetails);
    return PROCRESULT_OK;
}

#endif //OLD_NVRAM


/* This line marks the end of the source */
