/**
Copyright 2022 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/

/*
    CPU: Any

    \file opnlpsgn.c
    \brief Performs open loop valve and actuator diagnositcs. Ark's version

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics

*/
#include "mnwrap.h"

#include "timebase.h" //for times
#include "valveutils.h" //for WaitStable...

//Other Module includes -- these CANNOT be order dependent
//#include "timer.h"
#include "pwm.h"
#include "bufferhandler.h"
#include "errcodes.h"
#include "mnassert.h"
#include "process.h"
#include "sysio.h"
#include "ctllimits.h"
#include "pressures.h"

#include "diagnostics.h"

//Algorithm choices
#define USE_PRESSURE_LIMIT 1
#define USE_BIAS_END_LIMIT 0
#define USE_POS_ATLIMIT_CRITERION 1
#define USE_STEP_ADAPTATION 1
#define USE_AUX_BUFFER 0 //required for single loop but needs work with presampling

//Buffer constants
#if USE_AUX_BUFFER
#define WORKING_DIAGBUF DIAGBUF_AUX
#define MAX_NUM_AUX_DSAMPLES(headersz) (((((DIAGNOSTIC_BUFFER_SIZE_AUX-1U)-headersz)/DENTRIES_IN_DSAMPLE)/2U)*2U) //must be even!
#define WORKING_MAX_DSAMPLES NUM_AUX_DSAMPLES(0U)
#define WORKING_HEADERSIZE 0U
#else
#define WORKING_DIAGBUF DIAGBUF_DEFAULT
#define WORKING_MAX_DSAMPLES MAX_NUM_DSAMPLES(EXTDIAG_HEADERSZ)
#define WORKING_HEADERSIZE (EXTDIAG_HEADERSZ)
#endif



//Process progress
//At preparation, for each direction
#define EXTDIAG_AT_START_POINT 2
#define EXTDIAG_RAMPED_FOR_BIAS_RATE 2
#define EXTDIAG_RAMPED_FOR_BIAS_RATE_CATCHUP 2
#define EXTDIAG_COLLECTED_BIAS_RATE 1
//Currently, 7 subtotal
//Within a sweep
#define EXTDIAG_APPROCHED_START 3
#define EXTDIAG_REACHED_START 2
//Currently, 5 subtotal
//The first sweep starts at 7+5=12 for one way, or 2*7+5=19 two ways
#define EXTDIAG_HALFWAY (50+EXTDIAG_AT_START_POINT+EXTDIAG_RAMPED_FOR_BIAS_RATE+EXTDIAG_RAMPED_FOR_BIAS_RATE_CATCHUP+EXTDIAG_COLLECTED_BIAS_RATE)
#define EXTDIAG_FINISHED 100

//Errors
#define DIAG_INTERNAL_ERROR 1
#define DIAG_WRONG_DIRECTION 2
#define DIAG_INIT_ERROR 4
#define DIAG_BIAS_RATE_UNCERTAIN 8

typedef struct prescan_results_t
{
    pos_t pos;
    bias_t pwm;
    //pres_t pres_a;
} prescan_results_t;
CONST_ASSERT(sizeof(prescan_results_t)%sizeof(diag_t)==0U);
//With the above-checked assumptions the following is used
#define BUFINDEX_POS 0
#define BUFINDEX_PWM 1
//structures used internally
typedef struct test_info_t                //! parameters setup by prepare routine to control signature
{
    pos_t SpecifiedStartPosition;           //!< user entered start position
    pos_t SpecifiedEndPosition;             //!< user entered end position
    pos_t PreparationStartPosition;         //!< limited in range start position for preparation
    pos_t PreparationEndPosition;           //!< limited in range end position for preparation
    bool_t bIPIncreasing;                   //!< ip increasing when going from start to end
    bool_t bDirectionIncreasing;            //!< flag for increasing or decreasing position
    prescan_results_t crosspoint;
} test_info_t;


//defines
#define BIAS_STEP_CONTROL_PERIOD ((s32)CTRL_TASK_DIVIDER) //! in ticks - We step the bias in Cycle task
#define BIAS_SCALE_SHIFT 8 //We do want a sensible integer BiasPerStep, but stay in 32-bit world
#define BIAS_PER_MIN ((bias_t)(0.2*BIAS_SCALE_FACTOR)) //at least once every 5 steps
#define BIAS_PER_MAX ((bias_t)(100*BIAS_SCALE_FACTOR))
#define BIAS_SCALE_FACTOR ((s32)(1u<<BIAS_SCALE_SHIFT))

#define PRESSURE_ACT1_LIM_LOW STD_FROM_PSI(1.0) //away from 0
#define PRESSURE_ACT1_LIM_HIGH STD_FROM_PSI(3.0) //away from supply

/* \brief a helper to have a single breakpoint in debugging
*/
static void procfail(procresult_t *procresult)
{
    *procresult = PROCRESULT_FAILED;
}

/** \brief sets or increments %complete
\param increment - if <=0, sets -increment, otherwise increments by increment
*/
static void diag_UpdatePercentComplete(s8_least increment)
{
    u8 base;
    if(increment <= 0)
    {
        increment = -increment;
        base = 0U;
    }
    else
    {
        base = process_CheckProcessProgress();
    }
    base += (u8)increment;
    process_SetProcessProgress(base);
}

/** \brief A data sampling function for diagnostic buffer in pruned sampling mode.
Samples valve position and bias.
\param data - a pointer to a pair of data
*/
static void dsampler_SamplePosBias(diag_t data[2])
{
    data[BUFINDEX_POS] = (pos_t)vpos_GetSmoothedScaledPosition();
    //known bad data[BUFINDEX_POS] = control_GetBias();
    data[BUFINDEX_PWM] = (diag_t)pwm_GetValue();
}


#define POS_DELTA  INT_PERCENT_OF_RANGE(6.0) //! ramp amount to detect bias, smallish but seems sufficient
#define VARS_PER_SAMPLE (sizeof(dsample_t)/sizeof(diag_t)) //Could become variable in the future
#define STABILIZE_COUNT (3)
    //Give position CATCHUP_WAIT_TIME_MAX to catch up
#define CATCHUP_WAIT_TIME_MAX (MN_MS2TICKS(10000u))
#define CATCHUP_WAIT_PERIOD T0_050
#define RAMP_RETRIES (CATCHUP_WAIT_TIME_MAX/CATCHUP_WAIT_PERIOD)

/** \brief A helper to set setpoint ramp
\param ctllims_ref - a pointer to reference limits
\param sp_speed - sp ramp speed in %/s
\return process completion code
*/
static procresult_t diag_SetSetpointRamp(const CtlLimits_t *ctllims_ref, pos_least_t sp_speed, s16 *procdetails)
{
    CtlLimits_t ctllims = *ctllims_ref;
    for(u8_least x=Xlow; x<Xends; x++)
    {
        ctllims.EnableSetpointRateLimit[x] = 1;
        ctllims.SetpointRateLimit[x] = (pos_t)sp_speed;
    }
    ErrorCode_t err = control_SetTentativeLimits(&ctllims);
    procresult_t procresult;
    if(err != ERR_OK)
    {
        procfail(&procresult);
        *procdetails += DIAG_INTERNAL_ERROR;
    }
    else
    {
        procresult = PROCRESULT_OK;
    }
    return procresult;
}


/** \brief In closed loop, stabilizes the valve and ramps setpoint while collecting position and bias.
Then estimates bias difference at two position points
Stops ramping when needed points are collected.
\param startpos - setpoint to stabilize at
\param increasing - which way to ramp
\param sp_speed - ramp speed in %/s
\param procdetails[out] - a ponter to completion details
\param[out] - a pointer to the holder of position and bias differences
\return completion code
*/
static procresult_t diag_EstimateBiasAtPos(pos_t startpos, bool_t increasing, pos_least_t sp_speed, prescan_results_t *crosspoint, s16 *procdetails)
{
    pos_least_t curpos;
    procresult_t procresult = PROCRESULT_OK;
    CtlLimits_t ctllims_saved;
    (void)control_GetLimits(&ctllims_saved); //we will manipulate sp ramp and restore setiings later

    mode_SetControlMode(CONTROL_MANUAL_POS, startpos);
    //Now, let the valve stabilize at `startpos'
    if(process_WaitForTime(T4_000))
    {
        procresult = PROCRESULT_CANCELED; //canceled
    }
    else
    {
        for(s8_least i=0; i<STABILIZE_COUNT; i++)
        {
            if(!util_WaitForPos(T1_000, STABLE_POS_TEST, true))
            {
                procresult = PROCRESULT_CANCELED; //canceled
                break;
            }
        }
    }
    if(procresult == PROCRESULT_OK)
    {
        //Ramp the setpoint toward `endpos` but stop early. We just want to catch movement
        //Now set the sp ramp speed, just as we do in ramp test
        procresult = diag_SetSetpointRamp(&ctllims_saved, sp_speed, procdetails);
    }
    diag_UpdatePercentComplete(EXTDIAG_AT_START_POINT);

    curpos = vpos_GetScaledPosition();

    /* We will ramp sp from where we found ourselves to at least `mid` and
    unconditionally stop ramping when reached `end`. The code takes care that
    position reaches at least `mid`.
    Then we'll parse the buffer of sampled position and bias to work out details.
    */
    pos_least_t start;
    pos_least_t mid;
    pos_least_t end;
    if(increasing)
    {
        start = curpos + 2*POS_DELTA;
        mid = curpos + 3*POS_DELTA;
        end = curpos + 4*POS_DELTA;
    }
    else
    {
        start = curpos - 2*POS_DELTA;
        mid = curpos - 3*POS_DELTA;
        end = curpos - 4*POS_DELTA;
    }

    if(procresult == PROCRESULT_OK)
    {
        //Ramp sp until position crosses startpos and sample position/bias.
        //No header, AUX buffer
        ErrorCode_t err = buffer_StartSampling(
                 WORKING_DIAGBUF,
                 TASKID_CONTROL, //That's where we are sampling now
                 dsampler_SamplePosBias,
                 WORKING_MAX_DSAMPLES,
                 WORKING_HEADERSIZE/2U,
                 NULL);

        if(err != ERR_OK)
        {
            procfail(&procresult);
            *procdetails += DIAG_INTERNAL_ERROR;
        }
    }

    if(procresult == PROCRESULT_OK)
    {
        mode_SetControlMode(CONTROL_MANUAL_POS, end); //Oh, and launch the ramping
        //Wait for position to reach mid point
        s32 sp;
        do //Guaranteed to end becuase sp is engineered internally. No guard needed.
        {
            (void)mode_GetEffectiveControlMode(&sp);
            curpos = vpos_GetScaledPosition();
            if(process_WaitForTime(T0_050))
            {
                procresult = PROCRESULT_CANCELED;
                break;
            }
        } while ((increasing && (sp<end) && (curpos < mid)) || (!increasing && (sp>end) && (curpos > mid)));
    }
    diag_UpdatePercentComplete(EXTDIAG_RAMPED_FOR_BIAS_RATE);

    //Give position CATCHUP_WAIT_TIME_MAX to catch up
    if(procresult == PROCRESULT_OK)
    {
        for(s8_least n=0; n<RAMP_RETRIES; n++) //account for position delay
        {
            curpos = vpos_GetScaledPosition();
            if((increasing && (curpos >= mid)) || (!increasing && (curpos <= mid))) //could be equiv(increasing, curpos < start) but harder to read
            {
                //We've collected all the data
                //crosspoint->pres_a = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX]; //This is slightly away from what we wanted to capture
                procresult = PROCRESULT_FAILED; //bogus indication to be corrected below the loop
            }
            if(procresult == PROCRESULT_OK)
            {
                //Not caught up yet
                if(process_WaitForTime(CATCHUP_WAIT_PERIOD))
                {
                    procresult = PROCRESULT_CANCELED;
                }
            }
            if(procresult != PROCRESULT_OK)
            {
                break;
            }
        }
        if(procresult == PROCRESULT_FAILED)
        {
            procresult = PROCRESULT_OK; //correct the bogus indication
        }
    }
    diag_UpdatePercentComplete(EXTDIAG_RAMPED_FOR_BIAS_RATE_CATCHUP);

    //Unconditional housekeeping
    buffer_StopSampling(WORKING_DIAGBUF);
    curpos = vpos_GetScaledPosition(); //Not smoothed here!
    mode_SetControlMode(CONTROL_MANUAL_POS, curpos);
    (void)control_SetTentativeLimits(&ctllims_saved);



    //Parse the buffer to find bias matching `mid'
    //We need to do it from the end of the buffer because that's where the ramp is visible
    if(procresult == PROCRESULT_OK)
    {
        diag_t *p = &buffer_GetXDiagnosticBuffer(WORKING_DIAGBUF)[WORKING_HEADERSIZE];
        u16_least num_points = VARS_PER_SAMPLE * buffer_GetSamplerInfo(WORKING_DIAGBUF)->num_points;
        u16_least currpoint;
        if(num_points < 2U*VARS_PER_SAMPLE)
        {
            currpoint=0; //failure
        }
        else
        {
            for(currpoint=num_points-VARS_PER_SAMPLE; currpoint!=0U; currpoint-=VARS_PER_SAMPLE)
            {
                //guard against watchdog
                if((currpoint%32U) == 0U)
                {
                    (void)process_WaitForTime(1U);
                }
                if((increasing && (p[currpoint]<=mid)) || (!increasing && (p[currpoint]>=mid)))
                {
                    //found!
                    crosspoint->pos = p[currpoint+BUFINDEX_POS];
                    crosspoint->pwm = (bias_t)(u16)p[currpoint+BUFINDEX_PWM];
                    break;
                }
            }
            //Continue to deltas by finding `start`
            for(; currpoint!=0U; currpoint-=VARS_PER_SAMPLE)
            {
                //guard against watchdog
                if((currpoint%32U) == 0U)
                {
                    (void)process_WaitForTime(1U);
                }
                if((increasing && (p[currpoint]<=start)) || (!increasing && (p[currpoint]>=start)))
                {
                    //found!
                    crosspoint->pos -= p[currpoint+BUFINDEX_POS];
                    crosspoint->pwm -= (bias_t)(u16)p[currpoint+BUFINDEX_PWM];
                    break;
                }
            }
        }
        if((currpoint==0U) ) //wrong start or not found
        {
            procfail(&procresult);
            *procdetails += DIAG_INIT_ERROR;
        }
    }
    diag_UpdatePercentComplete(EXTDIAG_COLLECTED_BIAS_RATE);

    return procresult;
}

#define STRETCH_SCALE (256) //artificial scale for integer calculations
//#define POSITION_INRANGE_SHRINK POSITION_05
#define POSITION_INRANGE_SHRINK POSITION_10
#define BIAS_OUTRANGE_STRETCH STD_FROM_PERCENT(0.2)
//#define BIAS_OUTRANGE_STRETCH STD_FROM_PERCENT(5.0)
#define SETPOINT_FUDGE INT_PERCENT_OF_RANGE(1.0)


/** \brief prepares for an extended signature test by aggregating inital data

  prepares for an extended signature test by gathering bias and bias rate
  \param x - Xlow or Xhi (first or second direction)
  \param[out] bc - structure to hold the parameters determined here
  \param[in] Speed - the speed to scan in position units
  \param startpos - start position
  \param endpos - end position
*/
static void diag_ExtSignaturePrepare(s8_least x, test_info_t* bc, pos_least_t startpos, pos_least_t endpos)
{
    pos_t Ends[Xends];

    if(x == Xhi)
    {
        //For second direction, if any, swap start and end
        pos_least_t pos_temp = startpos;
        startpos = endpos;
        endpos = pos_temp;
    }
    //for preparation we must be between 5 and 95 (5 less than open stop adjusted max)
    bc->bIPIncreasing = pos_GetStopAdjustment(Ends);//pos_GetPositionConf(NULL)->bATO;
    pos_t LowestInRange = Ends[Xlow] + POSITION_INRANGE_SHRINK;
    pos_t HighestInRange = (pos_t)CLAMP((STANDARD_100*STANDARD_100)/(s32)Ends[Xhi],  MIN_ALLOWED_POSITION, MAX_ALLOWED_POSITION);
    HighestInRange -= POSITION_INRANGE_SHRINK;

    bc->SpecifiedStartPosition = (pos_t)startpos;
    bc->PreparationStartPosition = CLAMP(bc->SpecifiedStartPosition, LowestInRange, HighestInRange);
    bc->SpecifiedEndPosition = (pos_t)endpos;
    bc->PreparationEndPosition = CLAMP(bc->SpecifiedEndPosition, LowestInRange, HighestInRange);
    bc->bDirectionIncreasing = (bc->SpecifiedEndPosition > bc->SpecifiedStartPosition);
    if(!bc->bDirectionIncreasing)
    {
        //if direction is decreasing reverse ip increasing flag
        bc->bIPIncreasing = !bc->bIPIncreasing;
    }

    MN_ASSERT(equiv((bc->PreparationEndPosition>bc->PreparationStartPosition), bc->bDirectionIncreasing));
}

typedef struct sample_and_step_t
{
    void (*sample_func)(diag_t data[2]);
    s32 BiasPerStep;
    s32 BiasBoosted;
#if USE_STEP_ADAPTATION
    pos_least_t PosStep; //!< per update period
#endif
    bool_t PosIncreasing;
    size_t run_count;
    u32 pos_atlim_count;
} sample_and_step_t;

static sample_and_step_t sample_and_step;

static void diag_AccelerateBias(void); //forward

/** \brief A data sampler modified to also control bias (PWM output)
based on static-duration sample_and_step setting
*/
static void dsampler_SampleAndStep(diag_t data[2])
{
    sample_and_step.BiasBoosted += sample_and_step.BiasPerStep;
    bias_t bias = sample_and_step.BiasBoosted/BIAS_SCALE_FACTOR;
    MN_ENTER_CRITICAL();
        ErrorCode_t err = sysio_SetForcedCtlOutput(bias, PWMEXACT);
        MN_ASSERT(err == ERR_OK);
        sample_and_step.sample_func(data);
    MN_EXIT_CRITICAL();
    diag_AccelerateBias();
}

#if USE_PRESSURE_LIMIT
static bool_t IsPres1AtLim(bool_t IPIncreasing)
{
    bool_t atlim;
    pres_least_t pres_a =  pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];
    if(!IPIncreasing)
    {
        atlim = (pres_a <= PRESSURE_ACT1_LIM_LOW);
    }
    else
    {
        atlim = (pres_a > pres_GetPressureData()->Pressures[PRESSURE_SUPPLY_INDEX] - PRESSURE_ACT1_LIM_HIGH);
    }
    return atlim;
}
#endif //USE_PRESSURE_LIMIT

/** \brief Resumes previously suspended data sampling and, as part of it, bias sweep
\param bc - a pointer to misc. sweep data
\param Speed - Nominal ramp speed in %/s
\param skip - data sampling skip count from a previous suspend
\param[out] pBiasEnd - the final bias we want to reach
\return completion code
*/
static procresult_t diag_LaunchBiasSweep(const test_info_t *bc, s32 Speed, u16 skip, taskid_t taskid, bias_t *pBiasEnd, s16 *procdetails)
{
    procresult_t procresult = PROCRESULT_OK;
    //Extend the  bias ends to specified positions
    s32 stretch = (STRETCH_SCALE*(bc->SpecifiedEndPosition - bc->SpecifiedStartPosition))
         /bc->crosspoint.pos; //guaraneed positive
    //Extend the bias ends further to be dead sure
    stretch += intscale32r(stretch, BIAS_OUTRANGE_STRETCH, stretch, STANDARD_NUMBITS); //2% stretch extra

    bias_t biasdiff = bc->crosspoint.pwm;
    if(!equiv(bc->bIPIncreasing, (biasdiff > 0)))
    {
        //procfail(&procresult);
        *procdetails += DIAG_BIAS_RATE_UNCERTAIN;
        biasdiff = -biasdiff;
    }

    pos_least_t posdiff = bc->crosspoint.pos;

    //diag_UpdatePercentComplete(EXTDIAG_BIAS_AT_STARTPOS);

    if(!equiv(bc->bDirectionIncreasing, (posdiff > 0)))
    {
        //UNLIKELY!!
        procfail(&procresult);
        posdiff = -posdiff;
        *procdetails += DIAG_WRONG_DIRECTION;
    }

    //calculations
    s32 BiasDiffBoosted = BIAS_SCALE_FACTOR*biasdiff;
    s32 step_length = BIAS_STEP_CONTROL_PERIOD; //for TASKID_CONTROL, in ticks
    if(taskid == TASKID_CYCLE)
    {
        step_length *= (s16_least)CYCLE_TASK_DIVIDER; //for TASKID_CYCLE, in ticks
    }

    //s32 BiasPerStep = (Speed * BiasDiffBoosted)/(step_length * posdiff);
    s32 BiasPerStep = (s32)(((s64)Speed * (s64)BiasDiffBoosted * (s64)step_length)/((s64)MN_MS2TICKS(1000U) * (s64)posdiff));
    /* This is integer arithmetic for
                  BiasDiffBoosted        Speed
    BiasPerStep = --------------- * ----------------- * step_length
                      posdiff       MN_MS2TICKS(1000U)
    The first fraction is scaling from position to bias, the second, scaling Speed
    from %/s to %/tick. I (Ark) don't bother to optimize (Yet?)
    */
    if(procresult == PROCRESULT_OK)
    {
        if(!bc->bDirectionIncreasing)
        {
            BiasPerStep = -BiasPerStep;
        }

        if(bc->bIPIncreasing)
        {
            if(BiasPerStep < 0)
            {
                procfail(&procresult);
                *procdetails += DIAG_INTERNAL_ERROR; //Handled separately; shoud not get here
            }
            else
            {
                BiasPerStep = CLAMP(BiasPerStep, BIAS_PER_MIN, BIAS_PER_MAX);
            }
        }
        else
        {
            if(BiasPerStep > 0)
            {
                procfail(&procresult);
                *procdetails += DIAG_INTERNAL_ERROR; //Handled separately; shoud not get here
            }
            else
            {
                BiasPerStep = CLAMP(BiasPerStep, -BIAS_PER_MAX, -BIAS_PER_MIN);
            }
        }
    }

    //Finish initialization of the modified data sampler
    sample_and_step.BiasPerStep = BiasPerStep;
    bias_t pwm = (bias_t)pwm_GetValue(); //start with what we have really output
    sample_and_step.BiasBoosted = pwm * BIAS_SCALE_FACTOR;
    sample_and_step.run_count = 0U;
    sample_and_step.pos_atlim_count = 0U;
    sample_and_step.PosIncreasing = bc->bDirectionIncreasing;
#if USE_STEP_ADAPTATION
    sample_and_step.PosStep = (s32)(((s64)Speed * (s64)BIAS_SCALE_FACTOR * (s64)step_length)/(s64)MN_MS2TICKS(1000U));
    if(!bc->bDirectionIncreasing)
    {
        //Don't
        sample_and_step.PosStep = -sample_and_step.PosStep;
    }
#endif

    //Launch open loop ramp
    if(procresult == PROCRESULT_OK)
    {
        mode_SetControlMode(CONTROL_OFF, 0); //sp don't care
        buffer_ResumeSampling(DIAGBUF_DEFAULT, skip); //This will run sampling AND bias sweep!
    }
    bias_t BiasEnd = pwm + biasdiff * stretch / STRETCH_SCALE;
    //Clamp to useful range
    *pBiasEnd = CLAMP(BiasEnd, MIN_DA_VALUE, MAX_DA_VALUE);

    return procresult;
}

static pos_t poshistory[8];
static u8_least posindex;
/** \brief Relying on position noise, detect if position is
not moving in the expected direction
\param increasing - expected direction
\param[out] step - a pointer to avg. position step size, !=0 if returns true
\return true iff deemed at rail
*/
static bool_t DetectPosAtRail(bool_t increasing, pos_least_t *step)
{
    u8_least n = posindex+1U;
    n %= NELEM(poshistory); //New index; it is also the oldest index
    pos_t curpos = vpos_GetScaledPosition();

    pos_least_t posperstep = (BIAS_SCALE_FACTOR*(curpos - poshistory[n]))/(s32)NELEM(poshistory); //per 60 ms

    bool_t ret = equiv(increasing, (curpos <= poshistory[n]));
    if(ret)
    {
        if(increasing)
        {
            posperstep = 1;
        }
        else
        {
            posperstep = -1;
        }
    }
    *step = posperstep;

    poshistory[n] = curpos;
    posindex = n;
    return ret;
}

#if USE_STEP_ADAPTATION
#define ADAPT_SCALE_BITS (29-BIAS_SCALE_SHIFT)
#define ADAPT_SCALE ((s32)(1UL<<ADAPT_SCALE_BITS))
CONST_ASSERT((BIAS_SCALE_SHIFT + ADAPT_SCALE_BITS)<=29); //max accepted by intscale32

#if defined(NDEBUG) || defined(_lint)
#define alpha_float (1.0/4096.0)
#else
//Make it variable for experimentation in debug
cdouble_t alpha_float = (1.0/4096);
#endif
//lint -esym(960, ALPHA) //Required Rule 10.4, Cast of complex expression from floating point to integer type
#define ALPHA ((s32)(alpha_float*ADAPT_SCALE))
#endif //USE_STEP_ADAPTATION

/** \brief Holy sh*t! It appears to work!

The accelerator can only be called after poshistory is filled
\param increasing - expected direction
*/
static void diag_AccelerateBias(void)
{
    sample_and_step.run_count++;
    if(sample_and_step.run_count >= NELEM(poshistory)) //let the check array fill
    {
        sample_and_step.run_count = NELEM(poshistory);
        //diag_AccelerateBias(bc->bDirectionIncreasing);
        s32 BoostedPosStep;
        bool_t atrail = DetectPosAtRail(sample_and_step.PosIncreasing, &BoostedPosStep);
        if(atrail)
        {
            sample_and_step.BiasBoosted += 10*sample_and_step.BiasPerStep;
            sample_and_step.pos_atlim_count++;
        }
        else
        {
            //Adapt BiasPerStep
            //The actual relative speed difference
#if USE_STEP_ADAPTATION
            bias_t oldstep = sample_and_step.BiasPerStep;
            bias_t refposstep = sample_and_step.PosStep;
            s32 refbiasstep_ratio = (BIAS_SCALE_FACTOR*refposstep)/BoostedPosStep; //boosted by BIAS_SCALE_FACTOR
            s32 newstep_boosted = (refbiasstep_ratio * oldstep);

            bias_t newstep = intscale32r(ALPHA, newstep_boosted-oldstep*BIAS_SCALE_FACTOR, oldstep, ADAPT_SCALE_BITS+BIAS_SCALE_SHIFT);

            if(oldstep>=0) //i.e., I/P increasing
            {
                newstep = CLAMP(newstep, BIAS_PER_MIN, BIAS_PER_MAX);
            }
            else
            {
                newstep = CLAMP(newstep, -BIAS_PER_MAX, -BIAS_PER_MIN);
            }
            sample_and_step.BiasPerStep = newstep;
#endif
        }
    }
}

#define SMALL_WAIT (MN_MS2TICKS(60u))
#if USE_BIAS_END_LIMIT
#define POST_SWEEP_MAX_COUNT (MN_MS2TICKS(30000u)/SMALL_WAIT) //extra 30 s wait
#endif
#if USE_PRESSURE_LIMIT
#define PRES_ATLIM_COUNT (MN_MS2TICKS(4000u)/SMALL_WAIT) //4 s wait for pressure at limit
#endif

#if USE_POS_ATLIMIT_CRITERION
#define POS_COUNT_LIMIT 40 //wait for no movement in the right direction for 60ms*POS_COUNT_LIMIT
#endif

/** \brief Waits until bias sweep end conditions are met

This helper requires that the sweep be running. That guarantees termination (on bias)
\param bc - a pointer to misc. sweep data
\param BiasEnd - the final bias we want to reach
\return completion code
*/
static procresult_t diag_WaitForEndOfSweep(const test_info_t *bc, bias_t BiasEnd)
{
    procresult_t procresult = PROCRESULT_OK;

#if USE_BIAS_END_LIMIT
    u16_least finish_count = 0U;
#else
    UNUSED_OK(BiasEnd);
#endif

    u16 atlim_count = 0; //for pressure

    bool_t arrived;
    do
    {
        if(process_WaitForTime(SMALL_WAIT))
        {
            procresult = PROCRESULT_CANCELED;
            break;
        }
        bias_t pwm = (bias_t)pwm_GetValue();
        //bias_t BiasEnd = pwm + biasdiff * stretch / STRETCH_SCALE;
        //Clamp to useful range
        //BiasEnd = CLAMP(BiasEnd, MIN_DA_VALUE, MAX_DA_VALUE);

        pos_least_t pos = vpos_GetScaledPosition();
        arrived = (bc->bDirectionIncreasing && (pos > bc->SpecifiedEndPosition))
                   || (!bc->bDirectionIncreasing && (pos < bc->SpecifiedEndPosition));
#if USE_PRESSURE_LIMIT
        if(!arrived)
        {
            bool_t atlim = IsPres1AtLim(bc->bIPIncreasing);
            //can be momentary and undeserved, esp. on DA
            if(atlim)
            {
                atlim_count++;
            }
            else
            {
                atlim_count = 0U;
            }
            if(atlim_count >= PRES_ATLIM_COUNT)
            {
                arrived = true;
            }
        }
#endif
        if(!arrived)
        {
            if( (bc->bDirectionIncreasing && (pos < bc->PreparationEndPosition))
                   || (!bc->bDirectionIncreasing && (pos > bc->PreparationEndPosition)))
            {
                //keep going
                sample_and_step.pos_atlim_count = 0U;
            }
            else
            {
#if USE_BIAS_END_LIMIT // Can be grossly premature because of e.g. a sudden P1 drop on handover to open loop
                //See if we got the bias
                if( ((pwm >= BiasEnd) && bc->bIPIncreasing) || ((pwm <= BiasEnd) && !bc->bIPIncreasing) )
                //if( ((pwm >= BiasEnd) && (biasdiff > 0)) || ((pwm <= BiasEnd) && (biasdiff < 0)) )
                {
                    //give it extra time to finish
                    finish_count++;
                    if(finish_count >= POST_SWEEP_MAX_COUNT)
                    {
                        arrived = true;
                    }
                }
#endif
#if USE_POS_ATLIMIT_CRITERION
                if(sample_and_step.pos_atlim_count >= POS_COUNT_LIMIT)
                {
                    arrived = true;
                }
#endif
            }
        }
        if(!arrived)
        {
            //Not really needed, except to keep the callee used :)
            arrived = !CheckIPLimits(pwm);
        }
    } while(!arrived);
#if 0
    //Just for kicks, give it 4 s more but stop bias increment
    sample_and_step.BiasPerStep = 0;
    if(process_WaitForTime(T4_000))
    {
        procresult = PROCRESULT_CANCELED;
    }
#endif
    return procresult;
}

/** \brief Ramp the valve in closed loop toward the start position on the intended
side of histeresis.

First, move slightly beyond the start position, and then turn
around and ramp to the start position.
It doesn't matter whether it is or isn't inside the range: it is the underlying
bias that we care about.
\param BiasEnd - the final bias we want to reach
\param Speed - ramp speed in %/s
\return completion code
*/
static procresult_t diag_MoveValveToStartPosition(const test_info_t *bc, pos_least_t Speed, s16 *procdetails)
{
    //Now ramp the valve in closed loop toward slightly away from the start position
    CtlLimits_t ctllims_saved;
    (void)control_GetLimits(&ctllims_saved);

    //Move fast part way before slow ramp
#if 1
    mode_SetControlMode(CONTROL_MANUAL_POS, bc->PreparationStartPosition);
    procresult_t procresult = PROCRESULT_OK;
    if(process_WaitForTime(T4_000))
    {
        procresult = PROCRESULT_CANCELED;
    }
#endif
    s32 sp = bc->SpecifiedStartPosition;
    if(bc->bDirectionIncreasing)
    {
        sp += SETPOINT_FUDGE;
    }
    else
    {
        sp -= SETPOINT_FUDGE;
    }

    //Now move slowly
    procresult_t procresult1 = diag_SetSetpointRamp(&ctllims_saved, Speed, procdetails); //unconditionally
    if(procresult == PROCRESULT_OK)
    {
        procresult = procresult1;
    }

    if(procresult == PROCRESULT_OK)
    {
        if(bc->bDirectionIncreasing)
        {
            sp -= SETPOINT_FUDGE;
        }
        else
        {
            sp += SETPOINT_FUDGE;
        }
        //Set ramping in motion
        mode_SetControlMode(CONTROL_MANUAL_POS, sp);
        //Wait for arrival - from the opposite side though
        s32 sp1;
        do
        {
            if(process_WaitForTime(T0_050))
            {
                procresult = PROCRESULT_CANCELED;
                break;
            }
            (void)mode_GetEffectiveControlMode(&sp1); //rate/range limits applied

        } while(sp1!=sp);
        if(!util_WaitForPos(T0_250, NOISE_BAND_STABLE, true))
        {
            procresult = PROCRESULT_CANCELED;
        }
    }
    diag_UpdatePercentComplete(EXTDIAG_APPROCHED_START);

    if(procresult == PROCRESULT_OK)
    {
        //Now, approach to start point from the correct side
        mode_SetControlMode(CONTROL_MANUAL_POS, bc->SpecifiedStartPosition);
        do
        {
            if(process_WaitForTime(T0_050))
            {
                procresult = PROCRESULT_CANCELED;
                break;
            }
            (void)mode_GetIntendedControlMode(&sp);
        } while(sp != bc->SpecifiedStartPosition);
    }

    (void)control_SetTentativeLimits(&ctllims_saved); //restore
    diag_UpdatePercentComplete(EXTDIAG_REACHED_START);
    return procresult;
}

static u16 diag_PreConfigSampling(void (*sample_func)(diag_t data[2]), taskid_t TaskContext, procresult_t *procresult, s16 *procdetails)
{
    //start and immediately suspend sampling/stepping in x direction
    u16 skip;
    ErrorCode_t err;
    MN_ENTER_CRITICAL();
        sample_and_step.sample_func = sample_func;
        //The rest of sample_and_step is set per direction later
        //That's OK because sampling doesn't actually start until then
        err = buffer_StartSampling(
                     DIAGBUF_DEFAULT,
                     TaskContext, //That's where we are sampling now
                     dsampler_SampleAndStep,
                     DIAG_MAX_SAMPLES, //That's how much we can save in a log file, not MAX_NUM_DSAMPLES(EXTDIAG_HEADERSZ),
                     EXTDIAG_HEADERSZ/2U,
                     NULL);
        skip = buffer_SuspendSampling(DIAGBUF_DEFAULT);
        if(err != ERR_OK)
        {
            procfail(procresult);
            *procdetails += DIAG_INTERNAL_ERROR; //should not get here
        }
    MN_EXIT_CRITICAL();
    return skip;
}

/** \brief do open loop signature

  runs a open loop extended signature test. stores the results in the diagnostic buffer
  \param[in] sample_func - function to gather position and pressure
  \param[in] TaskContext - context to sample the data - cycle task for this routine
  \param[in] StartPosition - starting position for signature - can be -5 to 105
  \param[in] EndPosition - ending position for signature - can be -5 to 105
  \param[in] Speed - %/s ramping speed (in position units)
  \param[in] DiagDirection - one way or both ways flag
  \return a competion code
*/
procresult_t diag_Run_ExtActuatorSignatureOpen_Internal(void (*sample_func)(diag_t data[2]), taskid_t TaskContext,
                     pos_t StartPosition, pos_t EndPosition, pos_least_t Speed, u8_least DiagDirection, s16 *procdetails)
{
    procresult_t procresult = PROCRESULT_OK;
    u16 skip;
#if USE_AUX_BUFFER
    skip = diag_PreConfigSampling(sample_func, TaskContext, &procresult, procdetails);
#endif


    test_info_t test_info[Xends];
    s8_least xend;
    if(DiagDirection == DIAGDIR_UPDOWN)
    {
        //both directions
        xend = Xends;
    }
    else
    {
        //one direction
        xend = Xhi;
    }

    //Prepare for open loop signature by finding bias increment for proper speed
    for(s8_least x=Xlow; x<xend; x++)
    {
        //  Must measure the bias speed in the correct direction of movement to
        //  deal with hysteresis
        if(procresult != PROCRESULT_OK)
        {
            break;
        }

        diag_ExtSignaturePrepare(x, &test_info[x], StartPosition, EndPosition);
        procresult = diag_EstimateBiasAtPos(test_info[x].PreparationStartPosition, test_info[x].bDirectionIncreasing, Speed, &test_info[x].crosspoint, procdetails);
    }

#if !USE_AUX_BUFFER
    skip = diag_PreConfigSampling(sample_func, TaskContext, &procresult, procdetails);
#endif

    for(s8_least x=Xlow; x<xend; x++)
    {
        diag_ExtSignaturePrepare(x, &test_info[x], StartPosition, EndPosition); //do it again, may be needed for Lint
        if(procresult == PROCRESULT_OK)
        {
            //No, we are not ashamed to repeat initialization
            diag_ExtSignaturePrepare(x, &test_info[x], StartPosition, EndPosition);

            procresult = diag_MoveValveToStartPosition(&test_info[x], Speed, procdetails);
        }

        if(procresult == PROCRESULT_OK)
        {
            //Launch open loop ramp until position or bias reach target
            bias_t BiasEnd;
            procresult = diag_LaunchBiasSweep(&test_info[x], Speed, skip, TaskContext, &BiasEnd, procdetails);

            //Wait until bias reached its (extended) end
            if(procresult == PROCRESULT_OK)
            {
                procresult = diag_WaitForEndOfSweep(&test_info[x], BiasEnd);
            }
        }

        //suspend sampling
        skip = buffer_SuspendSampling(DIAGBUF_DEFAULT);
        pos_least_t curpos = vpos_GetScaledPosition();
        mode_SetControlMode(CONTROL_MANUAL_POS, curpos);

        //Save number of points
        if(x == Xlow)
        {
            SetSamplesFirstDirection();  //save the number of points sampled
            *procdetails *= 256; //move error codes to high byte (1st direction)
            diag_UpdatePercentComplete(-EXTDIAG_HALFWAY);
        }
    }

    //stop sampling in all cases
    buffer_StopSampling(DIAGBUF_DEFAULT);
    SetSamplesLastDirection();  //save total number of points
    diag_UpdatePercentComplete(-EXTDIAG_FINISHED);

    if(procresult == PROCRESULT_OK)
    {
        //fill in the data in the header record
        FillExtDiagHeader(procdetails);
    }

    return procresult;
}

/* This line marks the end of the source */

