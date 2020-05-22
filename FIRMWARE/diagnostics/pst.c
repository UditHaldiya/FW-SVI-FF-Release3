/*
Copyright 2006-2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pst.c
    \brief Partial stroke test implementation

    CPU: Any

    OWNER: Larry Schoonover

    \ingroup PST
*/

#include "mnwrap.h"
#include "errcodes.h"
#include "timer.h"
#include "process.h"
#include "timebase.h"
#include "pst.h"
#include "nvram.h"
#include "faultpublic.h"
#include "valveutils.h"
#include "position.h"
#include "pressures.h"

#include "ctllimits.h"
#include "diagnostics.h"

#include "pstshell.h"
#include "commontime.h"
#include "datahog.h"
#include "selftune.h"

#if 0
//private defines
#define DEFAULT_INTERVAL 30            //2 days
#define DEFAULT_TIME_INTO_INTERVAL 0
#define DEFAULT_TIMEOFDAY 10

#define DEFAULT_NEXT_TIME ((s64)(200 * TB_TICKS_PER_SEC))  //200s

#define DEFAULT_FRICTION_LOW_LIMIT STD_FROM_PSI(0.0)
#define DEFAULT_FRICTION_LIMIT STD_FROM_PSI(5.0)
#define DEFAULT_BREAKOUT_LIMIT STD_FROM_PSI(10.0)
#define DEFAULT_DROOP_LIMIT STD_FROM_PSI(10.0)
#define DEFAULT_FREEZE_DO 1
#define DEFAULT_FREEZE_AO 1
#define DEFAULT_SCHEDULE_PST true
#define DEFAULT_PST_SPRING_RANGE STD_FROM_PSI(15.0)
#define ERROR_SPRING_RANGE -1
#define ERROR_SPEED -1
#define PST_MIN_NUMBER_OF_POINTS 5
#endif //0

#define DEFAULT_DWELL_TIME 4    //seconds

#define DEFAULT_TRAVEL 5.0
#define DEFAULT_RAMP_SPEED  STD_FROM_PERCENT(199.9)
CONST_ASSERT((PST_RAMP_SPEED_LOW <= DEFAULT_RAMP_SPEED) && (DEFAULT_RAMP_SPEED <= PST_RAMP_SPEED_HIGH));
#define DEFAULT_MAX_TIME PST_TIME_LIMIT_LOW
#define LEAD_TIME_LIMIT_DEFAULT 20    //seconds
#define LEAD_TIME_LIMIT_MIN (0*ONE_SECOND)    //! milliseconds
#define LEAD_TIME_LIMIT_MAX (60*ONE_SECOND)    //! milliseconds
CONST_ASSERT((LEAD_TIME_LIMIT_MIN<=LEAD_TIME_LIMIT_DEFAULT) && (LEAD_TIME_LIMIT_MAX >=LEAD_TIME_LIMIT_DEFAULT));

#define PST_STROKE_TIMEOUT_MAX 600000 //! ms
#define PST_SETPOINT_THRESHOLD_LOW 0.0 //! % of range
#define PST_SETPOINT_THRESHOLD_HIGH 10.0 //! % of range
#define PST_SETPOINT_THRESHOLD_DEFAULT (DEFAULT_TRAVEL) //! % of range
CONST_ASSERT((STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_LOW)<=STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_DEFAULT))
             && (STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_HIGH) >= STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_DEFAULT)));


//member data
static PSTConf_t m_PSTConf;

static const PSTConf_t DEF_PstConf =
{
    .sp_threshold = STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_DEFAULT),
    .travel = STD_FROM_PERCENT(DEFAULT_TRAVEL),
    .maxtime = DEFAULT_MAX_TIME,
    .ramp_speed = DEFAULT_RAMP_SPEED,
    .PresAbortActuator = PST_MAX_PRES_ABORT_ACT,
    .PresAbortPilot = PST_MAX_PRES_ABORT_PILOT,
    .LeadTime = LEAD_TIME_LIMIT_DEFAULT,
    .DwellTime = DEFAULT_DWELL_TIME,
    .StrokeTmout = 0, //will be replaced with auto
    .datamap =
        (1U<<DATAHOG_POSITION)
        | (1U<<DATAHOG_SETPOINT)
        | (1U<<DATAHOG_MAINPRESSURE)
        | (1U<<DATAHOG_PRESSUREB)
        | (1U<<DATAHOG_IPCURRENT)
        | (1U<<DATAHOG_PILOTPRESSURE),
    .skip_count = 0,
    .FreezeOptions = PST_FREEZE_SPRANGE | PST_FREEZE_SPRATE | PST_FREEZE_CUTOFF | PST_FREEZE_DEADZONE,
    .pattern = PST_PATTERN_DUDU,
    CHECKFIELD_CLEAR()
};

#if 0
static PSTFactoryChangeable_t m_PSTFactoryChangeable;
#define DEFAULT_RESP_TEST_TIMEOUT 15000
#define DEFAULT_RESP_TEST_PRES_DIF 8
#define DEFAULT_RESP_TEST_PRES_DIF_END 2
#define DEFAULT_POS_ERROR_ALLOWANCE (2.0)
#define DEFAULT_LOW_POSITION (3.0)
#define DEFAULT_HIGH_POSITION (97.0)
#define DEFAULT_MOVEMENT_DETECTION (1.0)
#define DEFAULT_AI_PST_BAND (0.1)
static const PSTFactoryChangeable_t DEF_PSTFactoryChangeable =
{
    .Resp_Test_Timeout = (MN_MS2TICKS(DEFAULT_RESP_TEST_TIMEOUT)), //15 sec
    .Resp_Test_Pres_Dif = STD_FROM_PSI(DEFAULT_RESP_TEST_PRES_DIF),  //8 psi
    .Resp_Test_Pres_Dif_End = STD_FROM_PSI(DEFAULT_RESP_TEST_PRES_DIF_END),  //2 psi
    .Pos_Error_Allowance = INT_PERCENT_OF_RANGE(DEFAULT_POS_ERROR_ALLOWANCE),
    .Low_Position = INT_PERCENT_OF_RANGE(DEFAULT_LOW_POSITION),
    .High_Position = INT_PERCENT_OF_RANGE(DEFAULT_HIGH_POSITION),
    .Movement_Detection = INT_PERCENT_OF_RANGE(DEFAULT_MOVEMENT_DETECTION),
    .AI_PST_Band  = STD_FROM_MA(DEFAULT_AI_PST_BAND),
    CHECKFIELD_CLEAR()
};

//Assert the required order of initialization
//E.g. CONST_ASSERT(NVRAMID_PSTConf < NVRAMID_PSTSchedTime);


const void *TypeUnsafe_pst_GetFactoryChangeable(void *dst)
{
    return STRUCT_GET(&m_PSTFactoryChangeable, dst);
}
ErrorCode_t TypeUnsafe_pst_SetFactoryChangeable(const void *src)
{
    const PSTFactoryChangeable_t *pFactory = src;
    if(pFactory == NULL)
    {
        pFactory = &DEF_PSTFactoryChangeable;
    }
    //AK:TODO: No data validation yet!
    Struct_Copy(PSTFactoryChangeable_t, &m_PSTFactoryChangeable, pFactory);
    //NB:No save to NVMEM here
    return ERR_OK;
}
#endif //0

/**
\brief returns the pst configuration data

\return const pointer to the data
*/
const PSTConf_t *diag_GetPstData(PSTConf_t *dst)
{
    return STRUCT_TESTGET(&m_PSTConf, dst);
}

/** Limits for  PST test time, ms. Arbitrary??*/
static const u32 pstTestTime_range[Xends] =
{
    PST_TIME_LIMIT_LOW,
    PST_TIME_LIMIT_HIGH
};
const pos_t pstTravel_range[Xends] =
{
    PST_TRAVEL_LOW,
    PST_TRAVEL_HIGH
};
const pres_t pstPresActuator_range[Xends] =
{
    [Xlow] = PST_MIN_PRES_ABORT_ACT,
    [Xhi] = PST_MAX_PRES_ABORT_ACT
};
const pres_t pstPresPilot_range[Xends] =
{
    [Xlow] = PST_MIN_PRES_ABORT_PILOT,
    [Xhi] = PST_MAX_PRES_ABORT_PILOT
};
const pos_t pstRampSpeed_range[Xends] =
{
    [Xlow] = PST_RAMP_SPEED_LOW,
    [Xhi] = PST_RAMP_SPEED_HIGH
};
const pos_t pstSpThreshold_range[Xends] =
{
    [Xlow] = STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_LOW),
    [Xhi] = STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_HIGH)
};
static const u16 pstTBreakout_range[Xends] =
{
    [Xlow] = LEAD_TIME_LIMIT_MIN, //s
    [Xhi] = LEAD_TIME_LIMIT_MAX //s
};

//--------- sanity test for constants -----------
CONST_ASSERT(PST_RAMP_SPEED_HIGH > INT_PERCENT_OF_RANGE(SP_RATE_LIMIT_HIGH)); //above SP_RATE_LIMIT_HIGH considered infinite
CONST_ASSERT(PST_RAMP_SPEED_LOW >= INT_PERCENT_OF_RANGE(SP_RATE_LIMIT_LOW)); //make sure we can set this limit

//-----------------------------------------------

static procresult_t pst_Stabilize(PSTctl_t *PSTctl, s32 current_sp)
{
    procresult_t result = PROCRESULT_OK;
    tick_t start = timer_GetTicks();
    tick_t elapsed = 0;

    tick_t setup_time = MN_MS2TICKS(m_PSTConf.LeadTime);
    bool_t is_stable;

    StablePosReq_t stablemon;
    vutil_StableReq_Init(&stablemon, STABLE_POS_TEST, true);
    do
    {
        is_stable= vutil_StableReq_Run(&stablemon);
        if(!is_stable)
        {
            u8_least canceled = process_WaitForTimeExt(T0_050, 0U);
            if(canceled == 0U)
            {
                //Not canceled; check time
                elapsed = timer_GetTicksSince(start);
                if(elapsed > setup_time)
                {
                    if((m_PSTConf.FreezeOptions & PST_FREEZE_STABLE) != 0)
                    {
                        PSTctl->details = PSTDETAILS_STABILIZE_TIMEOUT;
                        result = PROCRESULT_FAILED;
                    }
                    else
                    {
                        is_stable = true; //consider it OK
                    }
                }
            }
            else
            {
                PSTctl->details = PSTDETAILS_USER_CANCELED;
                result = PROCRESULT_CANCELED;
            }
        }
    } while((result == PROCRESULT_OK) && !is_stable);

        //Immdeiately start from current position (TODO: maybe, filtered?)

    if(result == PROCRESULT_OK)
    {
        tick_t wait_time = setup_time - elapsed; //guaranteed >= 0 so unsigned subtraction is OK
        tick_t max_wait = MN_MS2TICKS(1000); //AK: fixme
        PSTctl->wait_time = CLAMP(wait_time, 1U, max_wait);
        PSTctl->speed = STD_FROM_PERCENT(50.0); //don't care

        //we replace current_sp we were primed with - with actual setpoint
        UNUSED_OK(current_sp); //we replaced current_sp we were primed with - with actual setpoint
        PSTctl->target_sp = stablemon.reference;

        const pres_t *p = pres_GetPressureData()->Pressures;
        const pst_abort_t psta =
        {
            .setpoint = PSTctl->target_sp,
            .pilot_base = p[PRESSURE_PILOT_INDEX],
            .act_base = p[PRESSURE_MAIN_INDEX],
            .active = true,
            .CheckWord = 0 //Don't care
        };
        pst_InitAbort(&psta); //Activate PST abort monitoring
    }
    return result;
}

static procresult_t pst_Ramp_common(PSTctl_t *PSTctl, s32 current_sp, tick_t time, s16 speed, s16 sp_delta)
{
    PSTctl->speed = speed;
    PSTctl->target_sp = current_sp + sp_delta;
    PSTctl->wait_time = time + MN_MS2TICKS(m_PSTConf.DwellTime*ONE_SECOND);

    procresult_t result = PROCRESULT_OK;
    mode_SetControlMode(CONTROL_MANUAL_POS, PSTctl->target_sp);
    return result;
}

static procresult_t pst_Ramp1Dn(PSTctl_t *PSTctl, s32 current_sp)
{
    tick_t time = MN_MS2TICKS(m_PSTConf.StrokeTmout);
    s16 speed = m_PSTConf.ramp_speed; // %/s
    pos_t sp_delta = -m_PSTConf.travel;
    return pst_Ramp_common(PSTctl, current_sp, time, speed, sp_delta);
}

static procresult_t pst_Ramp2Up(PSTctl_t *PSTctl, s32 current_sp)
{
    tick_t time = MN_MS2TICKS(2*m_PSTConf.StrokeTmout);
    s16 speed = m_PSTConf.ramp_speed; // %/s
    pos_t sp_delta = m_PSTConf.travel + m_PSTConf.travel;
    return pst_Ramp_common(PSTctl, current_sp, time, speed, sp_delta);
}

static procresult_t pst_Ramp2Dn(PSTctl_t *PSTctl, s32 current_sp)
{
    tick_t time = MN_MS2TICKS(2*m_PSTConf.StrokeTmout);
    s16 speed = m_PSTConf.ramp_speed; // %/s
    pos_t sp_delta = -(m_PSTConf.travel + m_PSTConf.travel);
    return pst_Ramp_common(PSTctl, current_sp, time, speed, sp_delta);
}

static procresult_t pst_Ramp1Up(PSTctl_t *PSTctl, s32 current_sp)
{
    tick_t time = MN_MS2TICKS(m_PSTConf.StrokeTmout);
    s16 speed = m_PSTConf.ramp_speed; // %/s
    pos_t sp_delta = m_PSTConf.travel;
    return pst_Ramp_common(PSTctl, current_sp, time, speed, sp_delta);
}

//NULL-terminated array of function( pointer)s
static const PSTstep_t PSTsteps_DUDU[] =
{
    pst_Stabilize,
    pst_Ramp1Dn,
    pst_Ramp2Up,
    pst_Ramp2Dn,
    pst_Ramp1Up,
    pst_Stabilize,
};
CONST_ASSERT(NELEM(PSTsteps_DUDU) <= PST_MAX_PATTERN_STEPS);

static const PSTstep_t PSTsteps_DUD[] =
{
    pst_Stabilize,
    pst_Ramp1Dn,
    pst_Ramp2Up,
    pst_Ramp1Dn,
    pst_Stabilize,
};
CONST_ASSERT(NELEM(PSTsteps_DUD) <= PST_MAX_PATTERN_STEPS);

static const PSTstep_t PSTsteps_DU[] =
{
    pst_Stabilize,
    pst_Ramp1Dn,
    pst_Ramp1Up,
    pst_Stabilize,
};
CONST_ASSERT(NELEM(PSTsteps_DU) <= PST_MAX_PATTERN_STEPS);

static const PSTstep_t PSTsteps_UDUD[] =
{
    pst_Stabilize,
    pst_Ramp1Up,
    pst_Ramp2Dn,
    pst_Ramp2Up,
    pst_Ramp1Dn,
    pst_Stabilize,
};
CONST_ASSERT(NELEM(PSTsteps_UDUD) <= PST_MAX_PATTERN_STEPS);

static const PSTstep_t PSTsteps_UDU[] =
{
    pst_Stabilize,
    pst_Ramp1Up,
    pst_Ramp2Dn,
    pst_Ramp1Up,
    pst_Stabilize,
};
CONST_ASSERT(NELEM(PSTsteps_UDU) <= PST_MAX_PATTERN_STEPS);

static const PSTstep_t PSTsteps_UD[] =
{
    pst_Stabilize,
    pst_Ramp1Up,
    pst_Ramp1Dn,
    pst_Stabilize,
};
CONST_ASSERT(NELEM(PSTsteps_UD) <= PST_MAX_PATTERN_STEPS);



typedef struct pst_patterns_t
{
    const PSTstep_t *pattern;
    size_t nsteps;
} pst_patterns_t;

#define PST_PATTERN_MAP(name) {.pattern = name, .nsteps = NELEM(name)}


static const pst_patterns_t pst_patterns[] =
{
    [PST_PATTERN_DU] = PST_PATTERN_MAP(PSTsteps_DU),
    [PST_PATTERN_DUD] = PST_PATTERN_MAP(PSTsteps_DUD),
    [PST_PATTERN_DUDU] = PST_PATTERN_MAP(PSTsteps_DUDU),
    [PST_PATTERN_UD] = PST_PATTERN_MAP(PSTsteps_UD),
    [PST_PATTERN_UDU] = PST_PATTERN_MAP(PSTsteps_UDU),
    [PST_PATTERN_UDUD] = PST_PATTERN_MAP(PSTsteps_UDUD),
};

/**
\brief saves the pst configuration data

\param conf - const pointer to the data
\return ERR_OK iff no error
*/
ErrorCode_t diag_SetPstData(const PSTConf_t *src)
{
    const PSTConf_t *conf = src;
    ErrorCode_t err = ERR_OK;

    if(conf == NULL)
    {
         conf = &DEF_PstConf;
    }

    //sp threshold
    if((conf->sp_threshold < pstSpThreshold_range[Xlow]) || (conf->sp_threshold > pstSpThreshold_range[Xhi]))
    {
        err = ERR_INVALID_PARAMETER;
    }
    //travel
    else if( (conf->travel < pstTravel_range[Xlow]) || (conf->travel > pstTravel_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    //maxtime
    else if( (conf->maxtime < pstTestTime_range[Xlow]) || (conf->maxtime > pstTestTime_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    //ramp_speed
    else if( (conf->ramp_speed < pstRampSpeed_range[Xlow]) || (conf->ramp_speed > pstRampSpeed_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    //PresAbort
    else if( (conf->PresAbortActuator < pstPresActuator_range[Xlow]) || (conf->PresAbortActuator > pstPresActuator_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    else if( (conf->PresAbortPilot < pstPresPilot_range[Xlow]) || (conf->PresAbortPilot > pstPresPilot_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    //LeadTime
    else if((conf->LeadTime < pstTBreakout_range[Xlow]) || (conf->LeadTime > pstTBreakout_range[Xhi]))
    {
        err = ERR_INVALID_PARAMETER;
    }
    //DwellTime
    else if( (conf->DwellTime < PST_DWELL_LIMIT_LOW) || (conf->DwellTime > PST_DWELL_LIMIT_HIGH) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    //StrokeTmout
    else if( conf->StrokeTmout > PST_STROKE_TIMEOUT_MAX )
    {
        err = ERR_INVALID_PARAMETER;
    }

#if 0
    else if( (conf->FrictionLowLimit < pstFrictionLimit_range[Xlow]) || (conf->FrictionLowLimit > pstFrictionLimit_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }

    else if( (conf->FrictionLimit < conf->FrictionLowLimit) || (conf->FrictionLimit > pstFrictionLimit_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }

    else if( (conf->BreakoutLimit < pstBreakoutLimit_range[Xlow]) || (conf->BreakoutLimit > pstBreakoutLimit_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }

    else if( (conf->DroopLimit < pstDroopLimit_range[Xlow]) || (conf->DroopLimit > pstDroopLimit_range[Xhi]) )
    {
        err = ERR_INVALID_PARAMETER;
    }
    else if((conf->FreezeDO != 0) && (conf->FreezeDO != 1))
    {
       err = ERR_INVALID_PARAMETER;
    }

    else if((conf->FreezeAO != 0) && (conf->FreezeAO != 1))
    {
        err = ERR_INVALID_PARAMETER;
    }
#endif

    else if((conf->pattern >= NELEM(pst_patterns)) || (pst_patterns[conf->pattern].nsteps == 0))
    {
        err = ERR_INVALID_PARAMETER;
    }
    //skip_count not tested - OK
    //FreezeOptions not tested - OK
    else
    {
        //test datamap
        u8_least numchannels = datahog_TestDataMap(conf->datamap);
        if(numchannels == 0U)
        {
            err = ERR_NOT_SUPPORTED;
        }
        else
        {
            //Test that we have enough room to store PST data
            u32 numsaples = ( conf->maxtime / (CYCLE_TASK_DIVIDER*CTRL_TASK_DIVIDER*TB_MS_PER_TICK) )/(conf->skip_count + 1);
            u32 numdata = numsaples*numchannels;
            //numdata must be small enough to fit in the logfile
            if(numdata > PST_NUMSAMPLES_MAX)
            {
                err = ERR_INVALID_PARAMETER;
            }
        }
    }

    if(err == ERR_OK)
    {
        //Recompute StrokeTmout in ms by stroke speed (with rounding)
        u32 divisor = (u32)(s32)(conf->ramp_speed); //OK because positive
        u32 tmout = ((u32)(s32)(conf->sp_threshold)*ONE_SECOND + divisor/2U)/divisor;
        if(conf->StrokeTmout == 0)
        {
            tmout = CLAMP(tmout, 1U, UINT16_MAX); //paranoia
        }
        else
        {
            tmout = conf->StrokeTmout;
        }
        MN_ENTER_CRITICAL();
            Struct_Copy(PSTConf_t, &m_PSTConf, conf);
            storeMemberInt(&m_PSTConf, StrokeTmout, tmout);
        MN_EXIT_CRITICAL();
        /* write the data to fram */
        err = ram2nvramAtomic(NVRAMID_PSTConf);
    }
    return err; //no error
}



/**
\brief The public wrapper of a pst test.
Guarantees an exit sequence consistent with shutdown monitoring
*/
procresult_t diag_PartialStrokeTest(s16 *procdetails)
{
    procresult_t ret = PROCRESULT_OK;
    //check for faults that would stop us
    if( error_IsAnyFaultWithAttributes(INHIBITING_FAULTS))
    {
        *procdetails = PSTDETAILS_INHIBITING_FAULTS;
        ret = PROCRESULT_CANCELED;
    }
    else if( !pst_IsPSTAllowed() )
    {
        *procdetails = PSTDETAILS_NOT_ALLOWED;
        ret = PROCRESULT_CANCELED;
    }
#if 0
    else
    {
        CtlLimits_t lims;
        if(ctllim_GetPermLimits(&lims) == NULL)
        {
            *procdetails = PSTDETAILS_FAILED_INTERNAL;
            ret = PROCRESULT_FAILED;
        }
        else if(((m_PSTConf.FreezeOptions & PST_FREEZE_CUTOFF) == 0U) && (lims.Protected == 0U))
        {
            s32 current_sp;
            (void)mode_GetIntendedControlMode(&current_sp); //capture the setpoint (before it is limited)
            //Check that during the test PST setpoint is not going to walk outside limits
            if(  ((lims.EnableSetpointLimit[Xlow] != 0) && (current_sp - m_PSTConf.travel < lims.SetpointLimit[Xlow]))
               ||((lims.EnableTightShutoff[Xlow] != 0) && (current_sp - m_PSTConf.travel <= lims.TightShutoff[Xlow]))
               ||((lims.EnableSetpointLimit[Xhi] != 0) && (current_sp + m_PSTConf.travel > lims.SetpointLimit[Xhi]))
               ||((lims.EnableTightShutoff[Xhi] != 0) && (current_sp + m_PSTConf.travel >= lims.TightShutoff[Xhi]))
                   )
            {
                *procdetails = PSTDETAILS_TRAVEL_OUTSIDE_RANGE;
                ret = PROCRESULT_CANCELED;
            }
        }
    }
#else
    else
    {
        //Nothing else to test
    }
#endif

    //Tentative limits will be modified in each step

    //Do the real thing now:
    if(ret == PROCRESULT_OK)
    {
        u16 x = m_PSTConf.pattern;
        ret = pstshell(procdetails, pst_patterns[x].pattern, pst_patterns[x].nsteps);
    }
    else
    {
        //leave data collection running
    }

    return ret;
}


/* This line marks the end of the source */
