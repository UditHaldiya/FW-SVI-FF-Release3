/*
Copyright 2004-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup Process framework
*/
/**
    \file process.c
    \brief Process infrastructure framework

    CPU: Any

    OWNER: AK

    \ingroup Process
*/
#include "mnwrap.h"
#include "errcodes.h"
#include "process.h"
#include "devicemode.h"
#include "mncbtypes.h"
#include "faultpublic.h"
#include "timer.h"
#include "watchdog.h"
#include "mnassert.h"
#include "timebase.h"

#include "procpriv.h"
#include "bufferhandler.h"
#include "oswrap.h"
#include "activate.h"

#include "syswd.h"
#include "wprotect.h"

static void process_RunProcedure(void);

//This is not protected since no-one cares about it
static u8 Atomic_ m_ui1PercentComplete = 0;   //- the percent complete of a long process.
                                  //   Must be set by the process running

#define PROC_CURRENT Xlow
#define PROC_PENDING Xhi

typedef struct ProcData_t
{
    volatile ProcId_t ProcessCommand[Xends];    //!< the command id for the long process that must be performed, current [Xlow] and pending [Xhi]
    ProcSource_t reqflag[Xends]; //!< Requestor flag for current [Xlow] and pending [Xhi] processes
    u16 mopup_index; //!< a circular index of the merry-go-round mop-up service, u16 for speed of update
    u16 CheckWord;
} ProcData_t;

static ProcData_t procdata = //!< A collection of important not self-repairing private data
{
    .ProcessCommand = {PROC_NONE, PROC_NONE},
    .reqflag = {ProcSourceDefault, ProcSourceDefault},
    .mopup_index = 0U,
    .CheckWord = CRC_SEED,
};


/** \brief A mandatory initializer
*/
void process_InitData(void)
{
    STRUCT_CLOSE(ProcData_t, &procdata);
    //To optimize: just set CheckWord = CRC_SEED.

    //Does anything else have to be initialized here?
}

/** \brief  This procedure checks for process cancellation
      from buttons, HART, or fatal error
  \return bitmap of cancellation requests
*/
static u8_least process_CheckCancelProcess(void)
{
    u8_least ret = process_CheckSpecific();

    if(procdata.ProcessCommand[PROC_PENDING] != PROC_NONE)
    {
        ret |= CANCELPROC_INTERNALREQ;
        if(procdata.reqflag[PROC_PENDING] == ProcSourceMonitor)
        {
            ret |= CANCELPROC_MONITOR;
        }
        if(procdata.reqflag[PROC_PENDING] == ProcSourceAbort)
        {
            ret |= CANCELPROC_ABORT;
        }
    }
    return ret;
}

CONST_ASSERT(sizeof(procdata.mopup_index)==sizeof(u16)); //to ensure storeMemberU16 is legit.
static void process_MopupSrv(void)
{
    u16 mopupx = procdata.mopup_index+1U;
    if(mopupx >= mopuplist_size)
    {
        mopupx = 0;
    }
    MN_ENTER_CRITICAL();
        storeMemberInt(&procdata, mopup_index, mopupx);
    MN_EXIT_CRITICAL();
    mopuplist[mopupx]();
}

#define PROCESS_DELAY_QUANTUM T0_100

/** \brief Compute new process delay based on remaining delay and last process refresh of watchdog.

    \param[in] nDelay - time remaining from original WaitForTimeExt
`   \param[in] lastContribution - tick time of last Process task watchdog refresh
    \return computed delay
*/
static tick_t ComputeDelay(tick_t nDelay, tick_t lastContribution)
{
    tick_t lDelay;

    // compute local delay relative to last watchdog contribution
    lDelay = timer_GetTicksSince(lastContribution);
    // delay is: quantum - time since last tickle, but not less than 1
    lDelay = (lDelay < PROCESS_DELAY_QUANTUM)
        ? (PROCESS_DELAY_QUANTUM - lDelay)
        : 1;
    // but delay may not be longer than remaining nDelay
    lDelay = MIN(lDelay, nDelay);
    return lDelay;
}

static tick_t Atomic_ actver_timestamp; //!<
static tick_t actver_runlength = 0;


/** \brief Wait for period of time specified by caller.

    As required, the requested time will be chopped into chunks of 100 milliseconds
    or less to accommodate refresh of watchdog.  Time spent in process task, mopup
    and time Process may have been preempted are accounted for.

    \param[in] nDelay - time requested delay time
`   \param[in] brk_mask - a mask of condition bits that may be ignored. Conditions not ignored
                          will cause early termination of the WaitForTimeExt.
    \return code - 0 if full time elapsed otherwise condition(s) that caused early termination
*/
u8_least process_WaitForTimeExt(tick_t nDelay, u8_least brk_mask)
{
    tick_t      lDelay;
    u8_least    brk = 0U;
    static u32  lastContribution = 0;

    tick_t t = timer_GetTicksSince(actver_timestamp);
    if(t > actver_runlength)
    {
        actver_runlength = t;
    }
    while (nDelay != 0)
    {
        Struct_Test(ProcData_t, &procdata);
        process_MopupSrv();

        lDelay = ComputeDelay(nDelay, lastContribution);
        nDelay -= lDelay;
        syswd_TickleWatchdog(TASKID_PROCESS); //TFS:4189
        timer_WaitTicks(lDelay);
        syswd_TickleWatchdog(TASKID_PROCESS);
        lastContribution = timer_GetTicks();

        brk = process_CheckCancelProcess();
        brk &= ~brk_mask;
        if(brk!= 0U)
        {
            break;
        }
    }
    actver_timestamp = timer_GetTicks();
    return brk;
}

/** \brief Wait for period of time specified by caller.

    This is a wrapper that implicity accespts all conditions as early termination

    \param[in] nDelay - time requested delay time
    \return - true if early termination, false if requested time elapsed
*/
bool_t process_WaitForTime(tick_t nDelay)
{
    return (process_WaitForTimeExt(nDelay, 0U) != 0U);
}

/** \brief Returns (and clears) the longest computational overhead of
anything in the process context between calls to process_WaitForTime().
This includes framework overhead and whatever a running process spends.
\return run length of pure overhead in ticks
*/
tick_t process_SampleAndClearOverhead(void)
{
    tick_t t;
    t = actver_runlength;
    actver_runlength = 0;
    return t;
}

/** \brief A "work" function for normal test of activation
Runs a process infrastructure
*/
static void runwork(void)
{
    /*
    process_WaitForTime() is going to return early if there is a process request.
    So, there is no point in waiting for less than a multiple of 100 ms, unless
    we have a critical process that needs to start faster. But we don't: data collection
    now runs in the cycle task context. (INSPECT!)
    The only effect vs. T0_050 delay is that mopup and other goodies will run with
    100 ms interval instead of 50 ms. There's no harm in it. (INSPECT!)
    */
    (void)process_WaitForTime(MN_MS2TICKS(200));
    process_RunProcedure();
}

/** \brief A "work" function for initial test of activation
(Just for watchdog)
*/
static void initwork(void)
{
    (void)process_WaitForTime(1U);
}


/** \brief  This is the main loop of the process task.
    Does not return.
*/
void process_ProcessTaskLoop(void)
{
    actver_timestamp = timer_GetTicks(); //At this point it is probably 0 or close to it but who cares?

    /*
    Verification of activation runs in the beginning, before any process can start
    - to test for repeat offense quickly.
    This provides forgiveness for an accidental mismatch.
    */
    actver_Verify(initwork, actver_ProcTaskInit);
    for (;;)
    {
        actver_Verify(runwork, actver_ProcTaskRun);
        MN_UNIT_TEST_BREAK();              // exit for (;;) for unit testing
    }
}

/** \brief  This returns the running process id (PROC_NONE if none)
    \return Process Id (current)
*/
ProcId_t process_GetProcId(void)
{
    return procdata.ProcessCommand[PROC_CURRENT]; //lint !e453 reading THIS volatile doesn't change it
}

/** \brief  This returns the percent completion of a process
    \return - percentage of completion
*/
u8 process_CheckProcessProgress(void)
{
    return m_ui1PercentComplete;
}

/** \brief  This sets the percent completion of a process
    \param[in] Progress - percentage of completion
*/
void process_SetProcessProgress(u8 Progress)
{
    m_ui1PercentComplete = Progress;
}

/** \brief  Requests a process cancellation with a specific request source
\param proc - process id to cancel (PROC_NONE means any process)
\param src - cancellation source/identification code
*/
void process_CancelProcessEx(ProcId_t proc, ProcSource_t src)
{
    MN_ENTER_CRITICAL();
        if((proc == procdata.ProcessCommand[Xlow]) || (proc == PROC_NONE))
        {
            process_ForceProcessCommandEx(PROC_CANCEL_PROC, src);
        }
    MN_EXIT_CRITICAL();
}

/** \brief  Requests unconditional process cancellation with default identification
*/
void process_CancelProcess(void)
{
    process_CancelProcessEx(PROC_NONE, ProcSourceDefault);
}

static void process_UpdateProcessIds(ProcId_t thisproc, ProcSource_t thissrc, ProcId_t nextproc, ProcSource_t nextsrc)
{
    MN_ENTER_CRITICAL();
        storeMemberInt(&procdata, ProcessCommand[PROC_CURRENT], thisproc);
        storeMemberInt(&procdata, reqflag[PROC_CURRENT], thissrc);
        storeMemberInt(&procdata, ProcessCommand[PROC_PENDING], nextproc);
        storeMemberInt(&procdata, reqflag[PROC_PENDING], nextsrc);
    MN_EXIT_CRITICAL();
}
/** \brief  A helper function to update the procdata record with the required process ids.
        It doesn't check whether they are legitimate!
    on the next run. If successful, it kills any previous process cancellation request.
  \param[in] thisproc - the command number of the process
  \param[in] nextproc - the command number of the next process
*/
static ErrorCode_t process_UpdateProcessIds1(s8_least id, ProcSource_t thissrc, ProcId_t nextproc, ProcSource_t nextsrc)
{
    u8 flags = proctable[id].flags.initflags;

    ErrorCode_t err;
    if(id < 0)
    {
        err = ERR_INVALID_PARAMETER;
    }
    else if(sysio_ReadWriteProtectInput() && ((flags & PROCINIT_HONORWRITELOCK) != 0U))
    {
        err = ERR_WRITE_PROTECT;
    }
    else
    {
        ProcId_t thisproc = proctable[id].id;
        process_UpdateProcessIds(thisproc, thissrc, nextproc, nextsrc);
        err = ERR_OK;
    }
    return err;
}

/** \brief A helper function to test if the supplied process id is valid
    \param proc - a process id
    \return an index to the process entry or -1 if not found
*/
static s8_least process_FindProcEntry(ProcId_t procId)
{
    s8_least i;

    for(i=proctable_size-1; i>=0; i--)
    {
        if(proctable[i].id == procId)
        {
            if(proctable[i].procf != NULL)
            {
                break;
            }
        }
    }
    return i;
}

/** \brief Force (schedule) a process to run even if there is aready one running

    \param[in] ProcessCommand - id of process to be run
*/
MN_DECLARE_API_FUNC(process_ForceProcessCommand)
void process_ForceProcessCommandEx(ProcId_t ProcessCommand, ProcSource_t source)
{
    ProcId_t procid = procdata.ProcessCommand[PROC_CURRENT];
    s8_least id = process_FindProcEntry(ProcessCommand);
    bool_t ok = false;
    if(id<0)
    {
        //Process not found: Nothing to do;
    }
    else
    {
        ok = (procid != ProcessCommand); //Normally, we don't force the same process
        if(!ok)
        {
            //unless buffer guard passthrough is allowed AND...
            if((proctable[id].flags.initflags & PROCINIT_IGNOREBUFFERGUARD) != 0U)
            {
                //... Guard is actually in effect
                ok = (m_ui1PercentComplete == PERCENT_COMPLETE_KEEPON);
            }
        }
        if(ok)
        {

            MN_ENTER_CRITICAL();
                ErrorCode_t err = process_SetProcessCommandEx(ProcessCommand, source);
                /* If it failed because ProcessCommand is invalid (=cancel request),
                we need to force the cancel. It doesn't matter whether we are
                cancelling an existing process or the one that was set asynchronously.
                If it failed because a process was already running, only a preempting
                call to this function may have changed it, in which case it's OK
                to proceed: the last request wins.
                Therefore, the code snippet here **does not** require a critical
                section around, TFS:4385 is marked fixed without doing anything.
                */
                if(err != ERR_OK)  //failed to set a process legit or not; queue it
                {
                    err = process_UpdateProcessIds1(id, procdata.reqflag[PROC_CURRENT], ProcessCommand, source);
                }
                UNUSED_OK(err);
                process_SetProcessProgress(0);
            MN_EXIT_CRITICAL();
        }
    }
}

/**
  \brief  The function sets the process Id (command) for process_RunProcedure() to execute
    on the next run. If successful, it kills any previous process cancellation request.
  \param[in] proc - the command number of the process
  \return ERR_OK on success or an error code (notably, ERR_INVALID_PARAMETER and ERR_PROCESS_START)
*/
ErrorCode_t process_SetProcessCommandEx(ProcId_t proc, ProcSource_t source)
{
    ErrorCode_t retval;
    s8_least id = process_FindProcEntry(proc);

    if(id<0)
    {
        retval = ERR_INVALID_PARAMETER;
    }
    else
    {
        MN_ENTER_CRITICAL();
            if (process_GetProcId() == PROC_NONE)
            {
                retval = process_UpdateProcessIds1(id, source, PROC_NONE, ProcSourceDefault);
                if(retval == ERR_OK)
                {
                    process_SetProcessProgress(0);
                }
            }
            else
            {
                retval = ERR_PROCESS_START;
            }
        MN_EXIT_CRITICAL();
    }
    return retval;
}

/** \brief A common process execution framework.

Intended primarily for normal process execution but also a means for a process to
execute another process (by Id) from within. A process may (and should) delegate some
initialization/cleanup chores to the process configuration table parsed in this
function which means that a wrapping process should only call a subprocess by id.
\param procId - Process Id to run
\return process completion code (or PROCRESULT_CANCELED if invalid id)
*/
procresult_t process_Exec(ProcId_t procId)
{
    s8_least i = process_FindProcEntry(procId);

    /* NOTE: m_CancelProcess must be handled by the requested process itself.
       Some processes may consciously decide to ignore this request, so a blanket
       policy would be wrong here.
    */
    procresult_t result;
    if(i<0)
    {
        result = PROCRESULT_CANCELED;
    }
    else
    {
        //Common initialization chores
        if((proctable[i].flags.initflags & (PROCINIT_CLAIMDIAGBUFFER|PROCINIT_INHERITDIAGBUFFER)) == PROCINIT_CLAIMDIAGBUFFER)
        {
            buffer_InitializeDiagnosticBuffer();
        }

        //Capture the control mode (and setpoint)
        s32 sp;
        ctlmode_t ctlmode = mode_GetIntendedControlMode(&sp);

        s16 procdetails = 0; //a details variable optionally filled by a process
        result = proctable[i].procf(&procdetails);

        error_SetFault(proctable[i].action[result].event);
        if((result != PROCRESULT_CANCELED) && (proctable[i].action[PROCRESULT_FAILED].event != proctable[i].action[PROCRESULT_CANCELED].event))
        {
            error_ClearFault(proctable[i].action[PROCRESULT_CANCELED].event);
        }
        if(result == PROCRESULT_OK)
        {
            error_ClearFault(proctable[i].action[PROCRESULT_FAILED].event);
        }
        //Do not clear proctable[i].action[PROCRESULT_OK].event

        //Restore the control mode (and setpoint)
        //AK:TODO: This emulates ESD 3.1.2 behavior; make it consistent with unexpected changes
        /* A process changes control modes as it feels like; without further regard to the device
           conditions. The control mode manager must therefore account for this behavior using its
           own means. So, blunt restoring of control mode here is in line with what a process might
           do and doesn't need immediate improvement.
           When we do an improvement, it should be here and in every process that changes the control
           mode!
        */
        if((proctable[i].action[result].termflags & PROCTERMFLAG_CTLMODE) != 0U)
        {
            mode_SetControlMode(ctlmode, sp);
        }

	    if((proctable[i].action[result].termflags & PROCTERMFLAG_KEEPON) != 0U)
	    {
	        u8_least cancelreq;
	        do
	        {
	            m_ui1PercentComplete = PERCENT_COMPLETE_KEEPON;
	            cancelreq = process_WaitForTimeExt(MN_MS2TICKS(100U), ~CANCELPROC_INTERNALREQ);
	        } while(cancelreq == 0U);
	    }

        //Notify UI what to show on process termination
        if(procdata.reqflag[PROC_CURRENT] == ProcSourceUI)
        {
            //UI process
            process_NotifyEndUI(proctable[i].action[result].UIplace, procdetails);
        }
        else
        {
            if(procdata.ProcessCommand[PROC_CURRENT] == PROC_NONE)
            {
                //running stealth process - OK
            }
            else
            {
                process_NotifyEnd();
            }
        }
        //Notify UI that no process is started from UI
        process_SetRequestorFlag(0);
    }
    return result;
}


/**
  \brief  This function runs a procedure if one has been scheduled.  Otherwise
  it runs a single call to to the FRAM checker.
  This task does not return until the process is canceled, an error occurs,
  or the process finishes.
*/
static void process_RunProcedure(void)
{
    ProcId_t procId;

    m_ui1PercentComplete = 0;

    procId = procdata.ProcessCommand[PROC_CURRENT];

    (void)process_Exec(procId);

    if(procId != PROC_NONE)
    {
        process_EndHook(procId);
        process_UpdateProcessIds(procdata.ProcessCommand[PROC_PENDING], procdata.reqflag[PROC_PENDING], PROC_NONE, ProcSourceDefault);
    }
    /* EXPLANATION is due here.
    If procId != PROC_NONE we are just done running a process (namely, with the id procId).
    Another process (even if only a cancellation request) may now have been queued in PROC_PENDING.
    We clear the cancelation request since the queued process was not canceled

    If, however, procId == PROC_NONE, the process that may have been requested since procId was read
    got straight to m_ui1ProcessCommand, and no action is needed. We even leave a cancel request (if any)
    intact so that a process just requested and THEN canceled will be able to see the cancel request.
    */
}

/** \brief returns the process entry for the currently running process
	\param[in] which action flag
    \return pointer to the entry
*/
u8 process_GetProcessTermFlags(procresult_t Action)
{
    u8 flags;
    ProcId_t procid = procdata.ProcessCommand[PROC_CURRENT];
    s8_least id = process_FindProcEntry(procid);
    if(id < 0)
    {
        flags = 0xFF;
    }
    else
    {
        flags = proctable[id].action[Action].termflags;
    }
    return flags;
}

#define IS_GUARDING_BUFFER() (process_CheckProcessProgress() == PERCENT_COMPLETE_KEEPON)

bool_t process_IsGuardingDiagBuffer(void)
{
    return IS_GUARDING_BUFFER();
}

/** \brief returns the process flags for the currently running process
    \return the flags - see proctable.c
*/
u8 process_GetProcessFlags(void)
{
    ProcId_t procid = procdata.ProcessCommand[PROC_CURRENT];
    s8_least id = process_FindProcEntry(procid);
    u8 flags;
    if(id < 0)
    {
        flags = 0xFFU; //everything whatsoever is allowed
    }
    else if(IS_GUARDING_BUFFER())
    {
        flags = 0xFFU; //everything whatsoever is allowed if placeholder process lingers on
    }
    else
    {
        flags = proctable[id].flags.throughflags;
    }
    return flags;
}

/** \brief returns flags of resources claimed by the running process
    \return the flags - see proctable.c
*/
u8 process_GetResourceFlags(void)
{
    ProcId_t procid = procdata.ProcessCommand[PROC_CURRENT];
    s8_least id = process_FindProcEntry(procid);
    u8 flags;
    if(id < 0)
    {
        flags = 0; //no resource claimed by the process
    }
    else
    {
        flags = proctable[id].flags.initflags;
        if(IS_GUARDING_BUFFER())
        {
            flags &= ~PROCINIT_CLAIMCTLMODE; //allow process sp through
        }
    }
    return flags;
}

/** \brief A helper for a requestor to notify who requested the process.
\param flag - Currently, any non-zero means, UI.
*/
void process_SetRequestorFlag(u16 flag)
{
    MN_ENTER_CRITICAL();
        storeMemberInt(&procdata, reqflag[PROC_CURRENT], flag);
    MN_EXIT_CRITICAL();
}


/* This line marks the end of the source */
