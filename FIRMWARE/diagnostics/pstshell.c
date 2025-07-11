/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup PST  Partial Stroke Test
\brief Partial stroke test outer shell
*/
/**
    \file pstshell.c
    \brief Wrapper for Partial stroke test (start/cancel monitoring etc.)

    CPU: Any

    OWNER: AK

    \ingroup PST
*/

#include "mnwrap.h"
#include "crc.h"
#include "boolmon.h"
#include "process.h"
#include "mnassert.h"
#include "pst.h"
#include "pstshell.h"
#include "pressures.h"
#include "inpv.h"
#include "key.h"
#include "bufferhandler.h"
#include "taskids.h"
#include "diagnostics.h"
#include "diagrw.h"
#include "commontime.h"

#include "ctllimits.h"
#include "digitalsp.h"
#include "ipcdefs.h"

#include "datahog.h"

#define PST_SAVE_TICKS      (tick_t)((ASSERT_LIFESPAN  * 3) / 4)     // 75 percent
#define DEFAULT_NEXT_TIME ((s64)(200 * TB_TICKS_PER_SEC))  //200s

#define PST_DEFAULT_INTERVAL 30  // days
#define PST_INTERVAL_MAX DAYS_PER_YEAR    //pst interval cant be greater than 1 year
#define PST_INTERVAL_MIN 1

static PSTrigger_t PSTrigger;
static const PSTrigger_t PSTrigger_default =
{
    .PstSchedTrigger = PstSchedDisable,
    .PstUiTrigger = 0U, //All PST features on local UI disabled by default
    .PstCommTrigger = DhogCommEnable,
    .PstDiTrigger = DhogDiDisable,
    .PstPvTrigger = DhogPvDisable,
    .pvthreshold = STD_FROM_MA(12.0), //mA
    .interval = PST_DEFAULT_INTERVAL,
    .CheckWord = 0U, //don't care
};

bool_t pst_IsPSTAllowed(void)
{
    return (PSTrigger.PstDiTrigger != DhogDiDisable)
            || (PSTrigger.PstPvTrigger != DhogPvDisable)
            || (PSTrigger.PstCommTrigger != DhogCommDisable)
            || (PSTrigger.PstPvTrigger != DhogPvDisable)
            || (PSTrigger.PstSchedTrigger != PstSchedDisable)
            || ((PSTrigger.PstUiTrigger & ((1U<<PST_RUN_SETUP)|(1U<<PST_RUN_AUTO_MAN))) != 0U);
}

const PSTrigger_t *pst_GetTriggerInfo(PSTrigger_t *dst)
{
    return STRUCT_TESTGET(&PSTrigger, dst);
}

ErrorCode_t pst_SetTriggerInfo(const PSTrigger_t *src)
{
    if(src == NULL)
    {
        src = &PSTrigger_default;
    }
    ErrorCode_t err = ERR_INVALID_PARAMETER;
    if( ((src->PstSchedTrigger == PstSchedDisable) || (src->PstSchedTrigger == PstSchedEnable))
        //Do not check UI bits in PSTrigger.PstUiTrigger
        && ((src->PstCommTrigger == DhogCommDisable) || (src->PstCommTrigger == DhogCommEnable))
        && ((src->PstDiTrigger == DhogDiDisable) || (src->PstDiTrigger == DhogDiEnableOpen) ||(src->PstDiTrigger == DhogDiEnableClosed))
        && ((src->PstPvTrigger == DhogPvDisable) || (src->PstPvTrigger == DhogPvEnableBelow) ||(src->PstPvTrigger == DhogPvEnableAbove))
        && (src->pvthreshold >= pvthreshold_range[Xlow]) && (src->pvthreshold <= pvthreshold_range[Xhi])
            )
    {
        if((src->interval < PST_INTERVAL_MIN) || (src->interval > PST_INTERVAL_MAX))
        {
            //Wrong interval
        }
        else
        if((src->pvthreshold < pvthreshold_range[Xlow]) || (src->pvthreshold > pvthreshold_range[Xhi]))
        {
            //Wrong AI trigger theshold
        }
        else
        {
            Struct_Copy(PSTrigger_t, &PSTrigger, src);
            err = ram2nvramAtomic(NVRAMID_PSTrigger);
        }
    }
    return err;
}

static SchedTime_t m_PSTTimes;
//forward
static bool_t sched_Event_PST(const SchedConf_t *SchedConf);

static u16 lastSavedTicks;

#define GRACE_DEFAULT MINUTES_TO_TICKS(30)
CONST_ASSERT(GRACE_DEFAULT < INT32_MAX);

static const SchedConf_t PSTSchedConf =
{
    .sched_Event = sched_Event_PST,
    .SchedTime = &m_PSTTimes,
    .pTicksAtLastSave = &lastSavedTicks,
    .NVMInterval = PST_SAVE_TICKS,
    .grace = (u32)GRACE_DEFAULT,
    .fcode = FAULT_TMOUT_PST_TEST,
    .AllowedModes = MODE_OPERATE,
    .InhibitingFaults = INHIBITING_FAULTS,
    .ProcessToStart = PROC_DIAG_PARTIAL_STROKE_TEST,
    .NVMid = NVRAMID_PSTSchedTime
};


static bool_t sched_Event_PST(const SchedConf_t *SchedConf)
{
    bool_t ret = (PSTrigger.PstSchedTrigger == PstSchedEnable);
    if(ret)
    {
        /*TODO: Add any specific test (position too close to rail and whatever else
        Should be a function call
        */
        ret = sched_EventCommon(SchedConf);
    }
    return ret;
}

//All patterns are sort of the same and are indexed by a single enum
#define PATTERN_MATCH_START BOOLMON_PATTERN_MATCH
#define PATTERN_MATCH_CANCEL (PATTERN_MATCH_START-1) //grow in the negative direction

/* DI input-in-range monitor array index type */
enum
{
    DI_PST_INIT,
    DI_PST_WAIT_FOR_ACTIVE_EDGE,
    DI_PST_WAIT_FOR_ACTIVE_MINTIME,
    DI_PST_INIT_CANCEL,
    DI_PST_WAIT_FOR_ACTIVE_EDGE_CANCEL,
    DI_PST_WAIT_FOR_ACTIVE_MINTIME_CANCEL
};


/* DI input-in-range monitor state array */
static const boolmon_t DIPstMon[] =
{
    [DI_PST_INIT] = //initial state - wait 1 s inactive
    {
        .timelim = BOOLMON_1S,
        .stateval = false, //inactive
        .mismatch_link = DI_PST_INIT, //start anew
        .timeout_link = DI_PST_WAIT_FOR_ACTIVE_EDGE,
        .reset_link = DI_PST_INIT, //doesn't matter
    },
    [DI_PST_WAIT_FOR_ACTIVE_EDGE] = //post-initial state - wait out optional inactive time
    {
        .timelim = 0, //no limit
        .stateval = false, //inactive
        .mismatch_link = DI_PST_WAIT_FOR_ACTIVE_MINTIME,
        .timeout_link = DI_PST_INIT, //doesn't matter
        .reset_link = DI_PST_INIT, //doesn't matter
    },
    [DI_PST_WAIT_FOR_ACTIVE_MINTIME] = //wait for 10 s active
    {
        .timelim = MN_MS2TICKS(10000),
        .stateval = true, //active
        .mismatch_link = DI_PST_INIT, //reset the scheme
        .timeout_link = PATTERN_MATCH_START, //done,
        .reset_link = DI_PST_INIT_CANCEL,
    },
    [DI_PST_INIT_CANCEL] = //initial state - wait 1 s inactive
    {
        .timelim = BOOLMON_1S,
        .stateval = false, //inactive
        .mismatch_link = DI_PST_INIT_CANCEL,
        .timeout_link = DI_PST_WAIT_FOR_ACTIVE_EDGE_CANCEL,
        .reset_link = DI_PST_INIT, //doesn't matter
    },
    [DI_PST_WAIT_FOR_ACTIVE_EDGE_CANCEL] = //post-initial state - wait out optional inactive time
    {
        .timelim = 0, //no limit
        .stateval = false, //inactive
        .mismatch_link = DI_PST_WAIT_FOR_ACTIVE_MINTIME_CANCEL,
        .timeout_link = DI_PST_INIT, //doesn't matter
        .reset_link = DI_PST_INIT, //doesn't matter
    },
    [DI_PST_WAIT_FOR_ACTIVE_MINTIME_CANCEL] = //wait for 1 s active
    {
        .timelim = BOOLMON_1S,
        .stateval = true, //active
        .mismatch_link = DI_PST_INIT_CANCEL, //continue "cancel" monitoring
        .timeout_link = PATTERN_MATCH_CANCEL, //done,
        .reset_link = DI_PST_INIT, //begin "start" monitoring on match
    },
};

/* AI input-in-range monitor array index type */
enum {
    AI_PST_INIT,
    AI_PST_WAIT_FOR_ACTIVE_EDGE,
    AI_PST_WAIT_FOR_ACTIVE_MINTIME,
    AI_PST_INIT_CANCEL
};

/* AI input-in-range monitor state array */
static const boolmon_t AIPstMon[] =
{
    [AI_PST_INIT] = //initial state - wait 1 s inactive
    {
        .timelim = BOOLMON_1S,
        .stateval = false, //inactive
        .mismatch_link = AI_PST_INIT,
        .timeout_link = AI_PST_WAIT_FOR_ACTIVE_EDGE,
        .reset_link = AI_PST_INIT, //doesn't matter
    },
    [AI_PST_WAIT_FOR_ACTIVE_EDGE] = //post-initial state - wait out optional inactive time
    {
        .timelim = 0, //no limit
        .stateval = false, //inactive
        .mismatch_link = AI_PST_WAIT_FOR_ACTIVE_MINTIME,
        .timeout_link = AI_PST_INIT, //doesn't matter
        .reset_link = AI_PST_INIT, //doesn't matter
    },
    [AI_PST_WAIT_FOR_ACTIVE_MINTIME] = //wait for 1 s active
    {
        .timelim = BOOLMON_1S,
        .stateval = true, //active
        .mismatch_link = AI_PST_INIT, //reset the scheme
        .timeout_link = PATTERN_MATCH_START, //done,
        .reset_link = AI_PST_INIT_CANCEL,
    },
    [AI_PST_INIT_CANCEL] =
    {
        .timelim = 0, //forever
        .stateval = true, //active
        .mismatch_link = PATTERN_MATCH_CANCEL, //done if the input changed
        .timeout_link = AI_PST_INIT, //doesn't matter,
        .reset_link = AI_PST_INIT_CANCEL,
    },
};

typedef enum startsrc_t
{
    START_NONE = 0x3c,
    START_FROM_DI = 0x55,
    START_FROM_AI = 0xaa
    //,START_FROM_PV = 0xc3
} startsrc_t;

static startsrc_t started;

static boolmonstate_t dimon_state; //! holder of DI tracking state
static boolmonstate_t aimon_state; //! holder of AI tracking state

/** \brief Initializer of DI Unlatch monitor
*/
static void pstmon_Init(void)
{
    boolmon_init(&dimon_state, DIPstMon);
    boolmon_init(&aimon_state, AIPstMon);
    started = START_NONE;
}

typedef struct monconf_t
{
    const void *allowed; //!< configuration byte ptr indicationg whether PST start from this source is allowed
    startsrc_t from; //!< a tag indicating PST started from this source as such
    const boolmon_t *conf; //!< a pointer to (an array of) input tracking states
} monconf_t; //! The type of a Boolean input source monitoring configuration

/** Configuration of AI input tracking */
static const monconf_t AIconf =
{
    .allowed = &PSTrigger.PstPvTrigger,
    .from = START_FROM_AI,
    .conf = AIPstMon,
};

/** Configuration of DI input tracking */
static const monconf_t DIconf =
{
    .allowed = &PSTrigger.PstDiTrigger,
    .from = START_FROM_DI,
    .conf = DIPstMon,
};

/**
  \brief  checks the PST_DISABLE_ATC bit and the ATC flag to see if PST can be run
  \return true iff PST can run
*/
static bool_t IsPSTAllowed(const monconf_t *conf)
{
    const u8 *p = conf->allowed;
    return *p != 0; //So, all "disabled" must be zeros
}

/** \brief A helper processing AI and DI patterns in a uniform way
\param state - the [opaque] state of the input tracking
\param val - the current value of the input
\param conf - a pointer to the descriptor of tracking
*/
PRIVATE void pstmon_helper(boolmonstate_t *state, bool_t val, const monconf_t *conf)
{
    if(!IsPSTAllowed(conf))
    {
        boolmon_init(state, conf->conf); //in case changed
        return;
    }
    s8 result = boolmon_run(state, conf->conf, val);

    /* A critical section is needed to plug the hole in a HART command changing
       the process id between us getting it and acting on it.
    */
    MN_ENTER_CRITICAL();
    ProcId_t id = process_GetProcId();
    switch(result)
    {
        case PATTERN_MATCH_START:
            if(id == PROC_DIAG_PARTIAL_STROKE_TEST)
            {
                boolmon_init(state, conf->conf); //begin monitoring for "start" again
            }
            else
            {
                //PST is not running: start it but avoid collision
                if(started == START_NONE)
                {
                    started = conf->from;
                    process_ForceProcessCommandEx(PROC_DIAG_PARTIAL_STROKE_TEST, ProcSourceMonitor);
                    //the monitor already began monitoring for cancel
                }
            }
            break;
        case PATTERN_MATCH_CANCEL:
                if(started == conf->from)
                {
                    if(id == PROC_DIAG_PARTIAL_STROKE_TEST)
                    {
                        process_CancelProcess();
                    }
                    started = START_NONE;
                }
            //the monitor already began monitoring for start
            break;
        default: //a guard
            if(id != PROC_DIAG_PARTIAL_STROKE_TEST)
            {
                started = START_NONE;
            }
            break;
    }
    MN_EXIT_CRITICAL();
}

/** \brief Monitor of starting/canceling PST via AI and DI
*/
static void pst_AIDImon_Run(void)
{
    //Cheap test first
    MN_RT_ASSERT((started==START_NONE) || (started==START_FROM_AI) || (started==START_FROM_DI));

    if(digsp_GetExternalMode() == IPC_MODE_AUTO)
    {
        if(PSTrigger.PstDiTrigger == DhogDiDisable)
        {
            boolmon_init(&dimon_state, DIPstMon);
        }
        else
        {
            bool_t di = !bios_ReadDiState();
            pstmon_helper(&dimon_state, equiv(di, (PSTrigger.PstDiTrigger==DhogDiEnableClosed)), &DIconf); //DI switch is active low
        }
        if(PSTrigger.PstPvTrigger == DhogPvDisable)
        {
            boolmon_init(&aimon_state, AIPstMon);
        }
        else
        {
            sig_least_t signal = inpv_GetPV();
            pstmon_helper(&aimon_state, equiv((signal > PSTrigger.pvthreshold), (PSTrigger.PstPvTrigger == DhogPvEnableAbove)), &AIconf);
        }
    }
    else
    {
        pstmon_Init();
    }
}
typedef struct pst_abort_t //! A type for monitoring PST abort
{
    s32 setpoint;
    pres_t pilot_base;
    pres_t act_base;
    bool_t active;
    u16 CheckWord;
} pst_abort_t;

static pst_abort_t pst_abort; //PST abort monitoring object
static const pst_abort_t pst_abort_default =
{
    .setpoint = SETPOINT_INVALID,
    .pilot_base = 0, //PRESSURE_INVALID,
    .act_base = 0, //PRESSURE_INVALID,
    .active = false,
    .CheckWord = 0, //don't care
};
static void pst_InitAbort(const pst_abort_t *src)
{
    if(src == NULL)
    {
        src = &pst_abort_default;
    }
    Struct_Copy(pst_abort_t, &pst_abort, src);
}
void pst_EnableAbortMon(bool_t enable)
{
    MN_ENTER_CRITICAL();
        storeMemberBool(&pst_abort, active, enable);
    MN_EXIT_CRITICAL();
}

#define PST_INTERVAL DAYS_TO_TICKS(PSTrigger.interval)
#define GUARD_INTERVAL (s64)((PST_INTERVAL * 11) / 10)  // 110 percent.

/**
\brief checks and schedules/aborts a pst
*/
void pst_PSTScheduler(void)
{
    /* First of all, check if we need to cancel a running PST.
    We must do it at the beginning because PST may not have a chance of running
    yet, so the starting sp is not posted yet.
    */

    Struct_Test(PSTrigger_t, &PSTrigger);
    pst_AIDImon_Run();
    if(PSTrigger.PstSchedTrigger == PstSchedEnable)
    {
        /*AK:TODO: Add, as needed, tests for project-specific conditions for scheduling here - like e.g. ESD trips
        A test may decide to clear the guard/grace timer
        */

        const s64 intervals[2] =
        {
            PST_INTERVAL,
            GUARD_INTERVAL,
        };

        // check if time to run PST
        sched_Updater(&PSTSchedConf, intervals);

    }
    else
    {
       //pst is not allowed - so don't have pst timer go off
       error_ClearFault(FAULT_TMOUT_PST_TEST);
    }

    /*Up to this point, we may have started a PST.
    Now, let's see if we need to cancel it.
    */
    Struct_Test(pst_abort_t, &pst_abort);
    s32 pst_sp = pst_abort.setpoint;

    //Now we abort PST on deviations only in AUTO mode
    u8 xmode = digsp_GetExternalMode();
    if( (process_GetProcId() == PROC_DIAG_PARTIAL_STROKE_TEST) && (xmode == IPC_MODE_AUTO))
    {
        const PSTConf_t *conf = diag_GetPstData(NULL);
        bool_t need_cancel = false;
        if(pst_abort.active)
        {
            /* We cancel if the requested setpoint is available
            and walked away from the current (or starting?) PST setpoint.

            Option "UNLESS we are fully in control of the setpoint APP (Manual or Setup)"
            is honored automatically, so no code is required
            */
            s32 sp = digsp_GetData(NULL)->setpoint; //TODO:not a good abstraction level!!!
            pos_t max_diff = diag_GetPstData(NULL)->sp_threshold;
            need_cancel = (mn_abs(sp - pst_sp) > max_diff);

            if(!need_cancel)
            {
                const pres_t *p = pres_GetPressureData()->Pressures;
                need_cancel = (ABS(p[PRESSURE_MAIN_INDEX] - pst_abort.act_base)) > conf->PresAbortActuator;
                if(!need_cancel)
                {
                    need_cancel = (ABS(p[PRESSURE_PILOT_INDEX] - pst_abort.pilot_base)) > conf->PresAbortPilot;
                }
            }
        }
        if(need_cancel)
        {
            process_CancelProcessEx(PROC_DIAG_PARTIAL_STROKE_TEST, ProcSourceAbort);
        }
    }
}


const SchedTime_t *pst_GetPSTTimes(SchedTime_t *dst)
{
    return STRUCT_GET(&m_PSTTimes, dst);
}

//lint -sem(pst_SetInitPSTTimes, no_thread) May be used only for initialization.
ErrorCode_t pst_SetInitPSTTimes(const SchedTime_t *src)
{
    // src == NULL OK
    sched_Init(src, &PSTSchedConf, DAYS_TO_TICKS(PSTrigger.interval) - DEFAULT_NEXT_TIME); //run 1st time in 200 s

    //Since the function is only good for init, stick the other init here
    pstmon_Init();

    pst_InitAbort(NULL);

    return ERR_OK;
}

/**
\brief returns the number of minutes until the next pst
\return integer minutes until the next pst
*/
s32 pst_GetNextPSTTime(void)
{
    return sched_GetMinutesUntilEvent(&PSTSchedConf, MINUTES_PER_DAY * PSTrigger.interval);
}

/**
\param newminutes - new time into interval
*/
static ErrorCode_t pst_CorrectSchedule(s32 newminutes)
{
    ErrorCode_t err;
    if(PSTrigger.interval > 0)
    {
        //schedule allowed
        s32 minutes_left = pst_GetNextPSTTime();
        newminutes = minutes_left - newminutes;
        s64 ticks_since = MINUTES_TO_TICKS(newminutes);
        MN_ENTER_CRITICAL();
            s64 TimeSince = ticks_since % DAYS_TO_TICKS(PSTrigger.interval);
            CONST_ASSERT(sizeof(TimeSince) == sizeof(m_PSTTimes.TimeSince));
            //Larry's way would be to make it always non-negative
            storeMemberInt(&m_PSTTimes, TimeSince, TimeSince);
        MN_EXIT_CRITICAL();
        err = ram2nvramAtomic(NVRAMID_PSTSchedTime);
    }
    else
    {
        err = ERR_OK;
    }
    return err;
}

/** \brief Sets a new time
*/
ErrorCode_t pst_SetBaseTime(u16 Days, u16 Minutes)
{
    if((Days >= PSTrigger.interval) || (Minutes >= MINUTES_PER_HOUR))
    {
        return ERR_INVALID_PARAMETER;
    }

    //A note on casts below: they are necessary for portability (automatic on e.g. ARM)
    s32 newminutes = ((s32)Days * MINUTES_PER_DAY) + (s32)Minutes;

    return pst_CorrectSchedule(newminutes);
}

void pst_ResetGuard(void)
{
    sched_ResetGuard(&PSTSchedConf);
}

//------------ process part -----------------------------
#define DIAG_PST_VERSION 1

static procresult_t pst_Iterator(s16 *procdetails, const PSTstep_t *pststeps, size_t nsteps, u16 *StepTime)
{
    PSTctl_t ctl; //populated by a pst step function except perhaps the pre-populated `details`
    ctl.details = 0; //AK: TODO: no detals/success - need a symbol
    tick_t start_time = timer_GetTicks();
    procresult_t result = PROCRESULT_FAILED; //need init

    /*Get any data collection out of the way. It must happen on its own because
    PST claims the diagnostic buffe
    */
    (void)process_WaitForTime(MN_MS2TICKS(120));
    //Create configuration
    const PSTConf_t *pstconf = diag_GetPstData(NULL); //will also test
    const DatahogConf_t dhog =
    {
        .datamask = pstconf->datamap,
        .taskid = TASKID_CYCLE,
        .skip_count = pstconf->skip_count,
        .maxsamples = (u16)pst_CountMaxSamples(pstconf),
        .num_presamples = 0,
        .CheckWord = 0, //don't care
    };
    DatahogConf_t dhog_saved;
    (void)datahog_Get(&dhog_saved);
    //Write temprorary configuration
    ErrorCode_t err = datahog_Set(&dhog);
#if 0 //Start data collection here is a waste of buffer entries. See where it's done
    if(err == ERR_OK)
    {
        err = datahog_Control(DatahogForceStart, HogConfTemporary);
    }
#endif
    if(err == ERR_OK)
    {
        s32 current_sp = vpos_GetScaledPosition();
        for(u8_least step = 0; step < nsteps; step++)
        {
            result = pststeps[step](&ctl, current_sp);
            if(result == PROCRESULT_OK)
            {
                u8_least wait_result = process_WaitForTimeExt(ctl.wait_time, 0U);
                if(wait_result != 0U)
                {
                    result = PROCRESULT_CANCELED;
                    if((wait_result & CANCELPROC_ABORT) != 0U)
                    {
                        *procdetails = PSTDETAILS_OVERALL_TIMEOUT;
                    }
                    else
                    {
                        *procdetails = PSTDETAILS_USER_CANCELED;
                    }
                }
            }
            if(result != PROCRESULT_OK)
            {
                break;
            }
            current_sp = ctl.target_sp;
            //Also, collect and store setpoint and time information
            //StepData.speed = ctl.speed;
            //StepData.next_sp = (pos_t)current_sp;
            tick_t step_time = timer_GetTicksSince(start_time);
#if 0
            StepTime[step] = (u16)MIN(step_time, UINT16_MAX);
#else
            UNUSED_OK(StepTime);
#endif
            start_time += step_time;

            /*Oh, and if we timed out on a step, fail the test
            FUTURE: if(StepData[step].step_time == UINT16_MAX) ...
            */

            *procdetails = ctl.details;

        }
#if 0
        buffer_StopSampling(DIAGBUF_DEFAULT);
#else
        if(result == PROCRESULT_OK)
        {
            //A crutch to see if data collection completes
            //(void)process_WaitForTimeExt(MN_MS2TICKS(2000), ~0U); //don't interrupt

            //Stop data collection; can't do much on error which should never happen
            err = datahog_Control(DatahogStop, HogConfTemporary);
            UNUSED_OK(err);
        }
        else
        {
            //leave data collection running
        }
#endif
    }

    (void)datahog_Set(&dhog_saved); //Can't do anything about error here. It is not expected though
    return result;
}

#define PST_HEADER_TIMES_INDEX 14

CONST_ASSERT((PST_HEADER_TIMES_INDEX + PST_MAX_PATTERN_STEPS) <= (DIAGRW_HEADERSZ - DEVID_SIZE));

#if 0 //changed design
/** \brief put extended signature header data into buffer

  put extended signature header data into buffer
  \param[in] none
  \return none
*/
static void pst_FillHeader(pos_t StartPosition, pos_t EndPosition)
{
    const SamplerInfo_t *SamplerInfo = buffer_GetSamplerInfo(DIAGBUF_DEFAULT);
    const PSTConf_t *p = diag_GetPstData(NULL);
    u32 interval = SamplerInfo->prune_scale * CYCLE_TASK_DIVIDER * CTRL_TASK_DIVIDER; //Sampling interval in 5 ms ticks
    //Populate the buffer header
    diag_t PST_Header[PST_HEADER_TIMES_INDEX] =
    {
        [0] = DIAG_PST, //test type
        [1] = DIAG_PST_VERSION, //version
        [2] = (diag_t)(interval>>16); //no longer PST_HEADERSZ, //header size in diag_t entries
        [3] = (diag_t)SamplerInfo->num_points, // #of samples
        [4] = (diag_t)StartPosition,
        [5] = (diag_t)EndPosition,
        [6] = (diag_t)p->ramp_speed, // setpoint rate in %/sec (STANDARD_100 means 100%/s)
        [7] = (diag_t)(interval), //Sampling interval in 5 ms ticks, low halfword
        [8] = (diag_t)p->travel,
        [9] = (diag_t)p->DwellTime,
        [10] = (diag_t)p->StrokeTmout,
        [11] = (diag_t)p->pattern,
        [12] = 0xaaa,
        [13] = 0x55aa,
        //From [14] to [20] is free, and we'll use it for times
    };
    DIAGRW_WriteBufferHEADER(PST_Header);
}
#endif

#define BUFINDEX_PST_ADDON_BASE 8 //! Just past data collection

procresult_t pstshell(s16 *procdetails, const PSTstep_t *pststeps, size_t nsteps)
{
    u8 bufnum = DIAGBUF_DEFAULT;
    //ui_setNext(UINODEID_PST_RUNNING);
    diag_t *buf = buffer_GetXDiagnosticBuffer(bufnum);

    u16 PSTdata[PST_MAX_STEPS];

    //Initialize PST abort monitor
    const pres_t *pres = pres_GetPressureData()->Pressures;
    const pst_abort_t pst_abt =
    {
        .setpoint = ctllim_GetRangeBoundedSetpoint(),
        .pilot_base = pres[PRESSURE_PILOT_INDEX],
        .act_base = pres[PRESSURE_MAIN_INDEX],
        .active = false, //Do not enable yet
        .CheckWord = 0, //don't care
    };
    pst_InitAbort(&pst_abt);

    pos_t startpos = vpos_GetScaledPosition();

    const PSTConf_t *p = diag_GetPstData(NULL);
    PstFreeze_t FreezeOptions = p->FreezeOptions;
    //freeze = pst_Freeze(freeze);
    procresult_t result;
    PST_FREEZE(FreezeOptions);
        result = pst_Iterator(procdetails, pststeps, nsteps, PSTdata);
    PST_UNFREEZE();

    pst_InitAbort(NULL); //disable abort monitor

    /* We now need to populate the buffer header.
    Data collector already populated header[0-7]; we continue from [8]
    */
    buf[BUFINDEX_PST_ADDON_BASE + 0] = DIAG_PST_VERSION;
    buf[BUFINDEX_PST_ADDON_BASE + 1] = (diag_t)result;
    buf[BUFINDEX_PST_ADDON_BASE + 2] = startpos;
    buf[BUFINDEX_PST_ADDON_BASE + 3] = vpos_GetScaledPosition();
    buf[BUFINDEX_PST_ADDON_BASE + 4] = *procdetails; //Completion code
    buf[BUFINDEX_PST_ADDON_BASE + 5] = (diag_t)p->DwellTime;
    buf[BUFINDEX_PST_ADDON_BASE + 6] = (diag_t)p->travel;
    buf[BUFINDEX_PST_ADDON_BASE + 7] = (diag_t)p->ramp_speed;
    for(u8_least i=BUFINDEX_PST_ADDON_BASE + 8; i < (DIAGRW_HEADERSZ - DEVID_SIZE); i++)
    {
        buf[i] = DIAGRW_HEADER_FILLER;
    }

    if(result != PROCRESULT_CANCELED)
    {
#if 0 //We don't save to a file (yet?)
        //Write to log file
        ErrorCode_t err = diag_PrepareSignatureWrite(DIAGRW_PST, DIAGRW_CURRENT);
#if 0
        /* The original assert below is too cavalier because it has wider implications
        than just PST failure. There are many interactions that may become unaccounted for
        and it is better to limit the damage. Example: we may fail to collect any data on PST
        behalf.
        */
        MN_ASSERT(err == ERR_OK); //An error is a purely coding error
#else
        if(err != ERR_OK)
        {
            result = PROCRESULT_CANCELED;
        }
#endif
    }
    if(result != PROCRESULT_CANCELED)
    {
#if 0
        //Add actual step times
        memcpy(&buf[PST_HEADER_TIMES_INDEX], PSTdata, sizeof(PSTdata[0])*nsteps);
        //TODO: Populate second page of the header here with pst computed results
#endif

        s16 wdetails = 0;
        procresult_t wresult = diag_WriteBufferEx(&wdetails, PST_LOGFILE_MAXSIZE);
        UNUSED_OK(wresult); //we set a fault on failure to write, so we don't propagate
        if(*procdetails == 0)
        {
            *procdetails = wdetails;
        }
#else
        UNUSED_OK(diag_WriteBufferEx); //for lint
        UNUSED_OK(diag_PrepareSignatureWrite); //for lint
        UNUSED_OK(FillExtDiagHeader); //for lint
#endif

        //We ran to completion!
        //error_ClearFault(FAULT_TMOUT_PST_TEST);
        pst_ResetGuard();
    }

    return result;
}


