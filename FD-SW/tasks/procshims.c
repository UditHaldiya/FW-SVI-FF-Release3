/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file procshims.c
    \brief Some process wrappers for FFP

    CPU: Any

    OWNER: AK

    \ingroup Process
*/
#include "mnwrap.h"
#include "process.h"
#include "procpriv.h"
#include "procshims.h"

#include "nvram.h"

//------- Good shims - wrappers of bare processes -----------------

//One step of NVMEM test; same as in APP
procresult_t nvram_PageTest_SHIM(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    nvram_PageTest();
    return PROCRESULT_OK;
}


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

/* This line marks the end of the source */
