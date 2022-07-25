/*
Copyright 2004 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file control.c
    \brief Implementation of the control algorithm

     CPU: Any

    OWNER: JS

    \ingroup poscontrol
*/

#include "mnwrap.h"
#include "oswrap.h"
#include "reset.h"
#include "mnassert.h"
#include "errcodes.h"
#include "tempr.h"
#include "devicemode.h"
#include "nvram.h"
#include "timer.h"
#include "pwm.h"           /* WritePwm */
#include "control.h"
#include "faultpublic.h"    /* fault codes */
#include "selftune.h"       /* tune_GetPIDData() */
#include "ctlpriv.h"
#include "process.h"

#include "ctllimits.h"
#include "pneumatics.h"
#include "ext_analysis.h"
#include "sysio.h"
#include "pbypass.h"

//#include "iplimit.h"
#include "sysiolopwr.h"

#include "position.h"
#include "errlimits.h"
#include "cutoff.h"

#define STARTUP_FORCE_JIGGLE_TEST 0  /*TFS:8814 "Remove jiggle test at startup" */
#define USE_VALVE_MOVE_ESTIMATE 1 //or 0 - used for saving bias but looks obsolete, except for jiggle test cancel
#define USE_PILOT_FOR_SUPPLY_THRESHOLD 0 //wasn't working, TFS:37623. If we add it, need to verify pilot tempcomp in existing units
#define USE_BIAS_TEMPR_ADJ_T_LOW_T_HIGH 1 //1 - as in David's initialization, 0 - as in David's save
//Not used because now power limit is evaluated externally: #define USE_OUTPUT_LIMIT 0
#define USE_BORROWED_FROM_SVI1K 1 //Currently, remapping error (and so, tuned poscomp) to full mechanical range
//TFS:8333
#include "pressmon_act_hw.h"
//#include "pressmon_pilot_hw.h"
//END TFS:8333

#if USE_BIAS_TEMPR_ADJ_T_LOW_T_HIGH
#define T_LOW  -20             /* temperature low -20 degree C */
#define T_HIGH  70             /* temperature high 70 degree C */
#endif
#if USE_VALVE_MOVE_ESTIMATE
#define POS_SHIFT   40
#endif
//Checksum protection policy
#define CONTROL_CONTROL_STATE 0x01U //Test the whole control state
#define CONTROL_INCONTROL_TEST 0x02U //Test the jiggle test state
#define CONTROL_INTEGRAL_TEST_INTERLEAVE 0x04U //Interleave across control cycles integral tests with with integral calculations
#define CONTROL_CHECKSUM_PROTECT 0U
//#define CONTROL_CHECKSUM_PROTECT (CONTROL_CONTROL_STATE | CONTROL_INCONTROL_TEST)


#define DETECTOR_AVG_CONST       16            //!< for averaging the error

//#define STD_FROM_PSI(x) ((s16)((PRESSURE_SCALE_RANGE * (x)) / PRESSURE_SCALE_PSI))  //converts psi to counts

#define IN_CONTROL_DETECTOR_ERROR_BAND  INT_PERCENT_OF_RANGE(3.0F) //!< If integral out of this range (+/-) run "in control" detector

/** private defines */

/* -------------------------------------------------------- */
/* variables definition */
typedef struct ControlState_t
{
    u8 i_count;                      /// ep:count since last integral operation
    bool_t isBiasLowerLimited;
    bool_t isBiasUpperLimited;
    Bias_t LastComputedPosComp; //=0;
    pos_t m_n2CSigPos_p;               // m_n2CSigPos delayed 1 cycle for set-point delta
    u16 start_count;    /// ep: startup count 0, 1... 65000;
    bool_t Integral_Previously_Limited; // = false;
    bool_t m_bActuatorAtLim;         // true indicates integral windup to [actuator pressure] limit
    s32 m_n2Erf1; //boosted pos_t filter base
    tick_t Integral_First_Stopped;
    u8 BiasChangeFlag;     /* set to +/-1 if big change of BIAS */ /// AK:Q: This doesn't appear accurate (?) AK:NOTE: Can be enum.
    bool_t isIPLowerLimited; //Could be automatic but used in 1 run delay
    bool_t isIPUpperLimited; //Ditto
    pos_t m_n2Pos_p;

    s8 cBoost;     // boost state is 0 or 1
    u16 nBoostCount;
    ctlmode_t  m_n1ControlMode; //< the mode of the control routine; the previous value used to track change
    bool_t m_bRegularControl;
    bool_t m_bShutZone;

    s32 nErrorCount;         // cumulative count of successive errors for pos err
    u16 CheckWord;
} ControlState_t;

static ControlState_t cstate;

typedef struct IntegralState_t
{
    Bias_t Low_Integral_Limit;
    Bias_t High_Integral_Limit;
    Bias_t m_Integral;             //!< separate integral value until transferred to bias (work point)
    Bias_t BIAS;
    u16 CheckWord;
} IntegralState_t;

static IntegralState_t m_BiasData;

typedef struct InControlTest_t
{
    //Bias_t poscomp; //!< to compute validity of a bias candidate for save
    bool_t m_bSaveBias;         //!<  "in control" detector succeeds - delayed request to save [base]bias in NVM
    bool_t m_bProbeActive;          //!< true when "in control" detector is active
#if STARTUP_FORCE_JIGGLE_TEST
    /*TFS:8814 "Remove jiggle test at startup" */
    bool_t startup; // = true;      //!< true means force "in control" detector regardless of integral magnitude
#endif
    Bias_t BiasAvgAtBase;
    pos_t m_n2SPOffset;               //!< amount to jiggle the valve for "in control" detection
    u16 timeKtr; // = 0;
    u16 cycleKtr;
    pos_t avgErr;                 //!< average error used by "in control" detector
    u16 CheckWord;
} InControlTest_t;

static InControlTest_t ictest;


typedef struct ControlTrace_t
{
    u16 Overshoots;
    u16 JigglesPassed; //= 0;
    //TFS:3520, TFS:3596 -- separate terms P, D and Boost
    s32 m_pTerm;                 //!< P contribution to PWM
    s32 m_dTerm;                 //!< D contribution to PWM
    s32 m_boostTerm;             //!< Boost contribution to PWM
    s32 m_IpCurr;                //!< P * E plus D contribution to PWM
    s16 m_diagCalcPeriod;        //for diagnosics in ext_analysis  // TFS:5746
    u16 Integral_Limit_Status;
    u32 BiasesSaved;
    u16 BiasesRejected;
    bool_t m_bIControl; //flag of integral control enabled
    bool_t Air_Low_Limit;
#if USE_VALVE_MOVE_ESTIMATE
    bool_t m_bValveMove; //estimate of whether the valve is moving - for the intended purpose of saving bias.
#endif
} ControlTrace_t;

static ControlTrace_t ctltrace;

typedef struct ctlExtData_t
{
    const PositionConf_t* m_pPositionStop; /* - a pointer to the position calibration data*/ //AK+
    const PIDData_t*  m_pPID; // - a pointer to the PID data //AK+
    const ComputedPositionConf_t* m_pCPS; //AK+
    /* const DASignalLimits_t* m_pDASignalLimits; */
    const ErrorLimits_t*  m_pComputedErrorLimits; //AK+
    const CtlLimits_t *ControlLimits; //AK: Not needed in the trunk
    const PneumaticParams_t *pPneumaticParams; //AK: all about pneumatic relay and sensors
    u16 OutputLim;
} ctlExtData_t;

static BiasExt_t m_BiasExt; /// AK:NOTE: This config is "never" changed and is NEVER tested.

static BiasData_t m_NVMEMBiasData;   /// AK:NOTE: This is NEVER tested except when saved in FRAM.


//Continuous diagnostice only - not critical
static s32 m_nTravelAccum; //Abs. travel accumulation modulo STANDARD_RANGE
static bool_t m_nDirection;
static s32 m_n4PositionScaled_1;       /* temp for m_n4PositionScaled used in continuous diagnostic */
static ContinuousDiagnostics_t m_ContinuousDiagnostics;
static tick_t nDiagTime;
static u16 lets_save; //count seconds to hour


//================ Self-repairing variables ==================

//Computed every cycle - I/O processing to be moved to sysio layer
static s32 Atomic_ m_n4PositionScaled; /*- n2Position converted to standard position using the position calibrations from find stops */


//Computed every cycle but doesn't need to be owned by control as persistent
static s32 m_n4Setpoint; /* - the setpoint in standard range derived from the signal or from a manual setpoint */


//Computed every control cycle but used next cycle
static s32 PIDOut;          /** TFS:4226 */
static Bias_t m_CtlOutputValue;    /** TFS:4226 Diag Var */

//Updated every control cycle
static PosErr_t m_PosErr;       //*** ATO:  setpoint - position,   ATC: position - setpoint ***

//================ End Self-repairing variables ==================


//To make automatic
static s16 m_n2CSigPos;                 // active, damped and normalized set-point (and perhaps jiggle-test-perturbed)
static bool_t m_bATO;
static u16 m_n2PosRange; /// AK:NOTE: STD range of mechanical travel (is u16 enough?). Can be precomputed
static s16 m_n2Err_p=0;
static pos_t m_n2Deriv; //may need a copy in trace
static u8 m_nPosAtStops = CLOSED_1; /// AK:NOTE: Recomputed every time in control_PID() from scaled pos and computed stops
#if USE_PILOT_FOR_SUPPLY_THRESHOLD
static bool_t Pilot_Low;
#endif

//This is the minimum actuator pressure
//#define ACTUATOR_LOW_PRESS_LIMIT                STD_FROM_PSI(1.0F)


static const ContinuousDiagnostics_t  def_ContinuousDiagnostics =
    {
        .TotalTravelCntr    = 0u,
        .TimeClosedCntr     = 0u,
        .TimeOpenCntr       = 0u,
        .TimeNearCntr       = 0u,
        .CyclesCntr         = 0u,
        CHECKFIELD_CLEAR()
    };

    static const BiasData_t  def_BiasData =
    {
        .BiasSaved          = BIAS_LOW_LIMIT, //instead of BIAS_DEFAULT, based on usage in control_InitControlData
        CHECKFIELD_CLEAR()
    };

/// AK:NOTE: That's the default of Bias computations config voodoo that can only be changed by replacing the whole thing via HART
    static const BiasExt_t  def_BiasExt =
    {
        .uiBiasShift        = 300u,
        .nBiasAdd           = -500,
        .nBiasTempCoef      = 2,
        .nBiasAddAirLoss    = -500,
        .uiMaxHysteresis    = 1000u,
        CHECKFIELD_CLEAR()
    };

/************************************************/
/* private function prototypes */
static void Integral_Control(const ctlExtData_t *data);
static s32 Proportional_Control(const ctlExtData_t *data, bool_t m_bIControl);
static bool_t IsIControl(const ctlExtData_t *data);
static void checkAirPressure(const ctlExtData_t *data);
static void control_SetPositionErrorFlag(const ctlExtData_t *data);


#define ISTEP 100       // default integral range (counts) when PosComp >= COMP_BASE

/** \brief common integral range limit for "in control" detection and integral trimming

    \param e - the value in internal percent of range
    \param Pcomp - the pcomp value from the PID structure
*/
MN_INLINE s32 ErrorRangeToPWMRange(s16 e, s16 Pcomp)
{
    s32 ret;

    if((Pcomp < COMP_BASE) && (Pcomp > 0))
    {
        ret = e / Pcomp;
    }
    else
    {
        ret = ISTEP;
    }
    return ret;
}
/** \brief computes IN_CONTROL_DETECTOR_ERROR_BAND (three percent) of range
    to PWM counts.
    \param Pcomp - the pcomp value from the PID structure
*/
MN_INLINE s32 GetDetectorIntegralLimit(s16 Pcomp)
{
    return ErrorRangeToPWMRange((s16)IN_CONTROL_DETECTOR_ERROR_BAND, Pcomp);
}


/** \brief This function determines the output to D/A to produce analog current to I/P
    by typically calling function bios_WritePwm(PWMvalue).

    Output CtlOutputValue depends on the specific control mode (m_n1ControlMode).
    parameters description
    \param[in] s32 ipcurr:  the input is used to produce the output m_CtlOutputValue
                 in normal or manual mode.
*/

static void IPCurrent_StoreAndOutput(s32 ipcurr, u16 OutputLim)
{
    s32           CtlOutputValue;

    cstate.isIPUpperLimited = false;
    cstate.isIPLowerLimited = false;
	if (cstate.m_n1ControlMode==CONTROL_OFF)
    {
        // if control mode is CONTROL_OFF, don't change - keep the previous output
        //Set by control_SetPWM() NOT m_CtlOutputValue = 0u;              // Set Diag Variable
    }
    else
    {
        enumPWMNORM_t pwmNormalize = PWMSTRAIGHT;         /** TFS:4108 **/
        if ( (OutputLim <= MIN_DA_VALUE) || (cstate.m_n1ControlMode==CONTROL_IPOUT_LOW) )
        {
            // if it is low power or control mode is CONTROL_IPOUT_LOW just set I/P to minimum
            CtlOutputValue = MIN_DA_VALUE;        // set to minimum count
        }
    	else if ((cstate.m_n1ControlMode==CONTROL_IPOUT_HIGH) || (cstate.m_n1ControlMode==CONTROL_IPOUT_HIGH_FACTORY) )
        {
            // if control mode is CONTROL_IPOUT_HIGH or CONTROL_IPOUT_HIGH_FACTORY set the I/P to maximum
            CtlOutputValue = MAX_DA_VALUE;  // set to maximum count TFS:5698
        }
        else
        {
            //in diagnostic IP mode, the I/P follows the input signal
        	if (cstate.m_n1ControlMode==CONTROL_IP_DIAGNOSTIC )
            {
                ipcurr = mode_DirectOutput(cstate.m_n1ControlMode, ipcurr);
            }
            else
            {
                // SAR 8.3
                //   DZ: input ipcurr is offset only - add the bias to it to get the output
	            ipcurr += m_BiasData.BIAS+cstate.LastComputedPosComp;
                PIDOut = ipcurr;
            }

            CtlOutputValue = ipcurr;
            pwmNormalize = PWMNORMALIZED;
        }
        m_CtlOutputValue = CtlOutputValue;      // Set Diag Variable
        //write the value to the I/P
        u8 output_lim = sysio_WritePwm(CtlOutputValue, pwmNormalize);

        /*AK-7/10/13: preserve the previous behavior where integral
        limiting is NOT in effect in open-loop modes
        It may well be a bug
        */
        if(pwmNormalize == PWMNORMALIZED)
        {
            if((output_lim & CTLOUTPUT_LIMITED_LOW) != 0)
            {
                cstate.isIPLowerLimited = true;
            }
            if((output_lim & CTLOUTPUT_LIMITED_HIGH) != 0)
            {
                cstate.isIPUpperLimited = true;
            }
        }
    }//end outer if-else

} // ----- end of IPCurrent_StoreAndOutput() -----

/** \brief Compute position compensation (crude feedforward) unconditionally
	\param[in] ctlExtData_t *data: a pointer to the data structure that holds control parameters
*/
static void control_ComputePoscomp(const ctlExtData_t *data)
{
    pos_least_t nFull_delta;
	pos_t scaledSetPoint =
#if USE_BORROWED_FROM_SVI1K //TFS:4011
		(pos_t)intscale32( m_n2CSigPos, data->m_pCPS->n4OpenStopAdj, 0, (u8)STANDARD_NUMBITS );
#else
		m_n2CSigPos;
#endif
    Bias_t SpringCompensation = 0;
    Bias_t HysterisisCompensation = 0;

    //calculate the setpoint change from the last setpoint
    if (m_bATO)
    {
        nFull_delta = (scaledSetPoint  - STANDARD_ZERO);
    }
    else
    {
        nFull_delta = (STANDARD_100 - scaledSetPoint);
    }

    if(data->m_pPID->PosComp != COMP_BASE)
    {
        if(data->m_pPID->PosComp < COMP_BASE)
        {
            //PosComp < COMP_BASE means we need to make an adjustment
            //PosComp is 1/slope so multiply by setpoint step
            SpringCompensation = (Bias_t)(nFull_delta/data->m_pPID->PosComp);
        }
        else if(data->m_pPID->PosComp < COMP_MAX)
        {
            //PosComp is > COMP_BASE - this case is primarily for double acting
            // correction is -SPChange/(2^N) where N =  COMP_MAX - PosComp
            if (nFull_delta >= 0)
            {
                HysterisisCompensation = -(Bias_t)( ((u16)nFull_delta) >> (COMP_MAX-data->m_pPID->PosComp) );
            }
            else
            {
                HysterisisCompensation = -(Bias_t)(( (u16)(-nFull_delta)) >> (COMP_MAX-data->m_pPID->PosComp)) ;
            }
        }
        else
        {
           //will get here only if PosComp >= COMP_MAX
            //Already set SpringCompensation = 0;
            //Already set HysterisisCompensation = 0;
        }
    }

    //Add the position based terms; also good for COMP_BASE (zero)
    cstate.LastComputedPosComp = SpringCompensation + HysterisisCompensation;
    //save the setpoint as the last setpoint
    cstate.m_n2CSigPos_p = m_n2CSigPos;
    // restart the integral timer
    cstate.i_count = 0;
}



/** \brief This function is externally called by atune.c for auto-tuning to manipulate the output to D/A
    to produce analog current to I/P by calling function bios_WritePwm(PWMValue).
    Output m_CtlOutputValue depends on the specific control mode (m_n1ControlMode).
    parameters description
    \param[in] PWMValue:  the input is used to produce the output PWMValue
                 in CONTROL_OFF mode, which is the mode for directly set the output to D/A.
*/
void control_SetPWM(Bias_t PWMValue)
{
    //this should only be called open loop with control off
    if(cstate.m_n1ControlMode == CONTROL_OFF)
    {
        (void)sysio_WritePwm(PWMValue, PWMNORMALIZED);
        m_CtlOutputValue = PWMValue;
    }
}
/* -------------------------------------------------------- */
/* this function is called by the operating system */   //????which function????

/** \brief This function is externally called to get scaled current valve position
    parameters description:
    \param[out] s16 (s16)m_n4PositionScaled:  scaled current valve position cast to s16 to output
*/
s16 control_GetPosition(void)
{
    return (s16)m_n4PositionScaled;
}

/** \brief called to get scaled valve setpoint and current valve position
    last known to control, so it may be a control cycle off.

NOTES:
1. If you need user setpoint before limits, use mode_GetIntendedControlMode
2. setpoint with limits applied is also avaliable via mode_GetEffectiveControlMode (not recommended)
3. position is also available via vpos_GetScaledPosition

    \param[in] s32* pn4Setpoint: a pointer to position setpoint with all limits applied (m_n4Setpoint)
    \param[in] s32* pn4Position: a pointer to scaled current valve position (m_n4PositionScaled)
*/
void control_GetSetpointPosition(s32* pn4Setpoint , s32* pn4Position)
{
    //only return values when non-null pointers are passed
    MN_ENTER_CRITICAL();
        if(pn4Setpoint != NULL)
        {
            *pn4Setpoint = m_n4Setpoint;
        }
        if(pn4Position != NULL)
        {
            *pn4Position = m_n4PositionScaled;
        }
    MN_EXIT_CRITICAL();
}


//Jiggle ("in-control") test parameters
#define MS_PER_MIN                  (60u * 1000u)
#define DETECTOR_AVG_ERROR_THRESH   INT_PERCENT_OF_RANGE(.2F)
#define JIGGLE_TIMEOUT (u16)((MS_PER_MIN * 2u) / (TICK_MS * CTRL_TASK_DIVIDER))
#define JIGGLE_CYCLES   5


//lint -sem(control_IsModeClosedLoop, pure)
/** \brief A simple wrapper for closed-loop control mode
\param ctlmode - control mode to test
\return true iff closed loop
*/
static bool_t control_IsModeClosedLoop(ctlmode_t ctlmode)
{
    return (ctlmode==CONTROL_MANUAL_POS);
}



/** \brief This function is externally called to get current control mode and manual valve position setpoint
    parameters description:
    \param[in] ctlmode_t* pn1ControlMode: a pointer to current control mode m_n1ControlMode
    \param[in] s32* pn4Setpoint: a pointer to manual position setpoint m_n4ManualPos
*/
void control_GetControlMode(ctlmode_t* pn1ControlMode, s32* pn4Setpoint)
{
    //if the pointers are not null, return the control mode and setpoint to the passed addresses
    if(pn1ControlMode != NULL)
    {
        *pn1ControlMode = cstate.m_n1ControlMode;
    }
    if(pn4Setpoint != NULL)
    {
        *pn4Setpoint = m_n4Setpoint;
    }
}

/** \brief This function is externally called to get the current BIAS
    parameters description:
    \param[out] s16 LastComputedPosComp: return the value of current BIAS
*/
Bias_t control_GetBias(void)
{
    return cstate.LastComputedPosComp+m_BiasData.BIAS;
}

/** \brief This function is externally called to get the current BIAS change flag
    \param[out] u8 BiasChangeFlag: return the value of current BIAS change flag
*/
u8 control_GetBiasChangeFlag(void)
{
    return cstate.BiasChangeFlag;
}

/** \brief This function is externally called to reset the current BIAS change flag
    and startup count.
    u8 BiasChangeFlag: flag indicating state of control (at stops, at handwheel, etc.)
    u16 start_count: flag indicating startup state
*/
void control_ResetBiasChangeFlag(void)
{
    MN_ENTER_CRITICAL();
        storeMemberInt(&cstate, BiasChangeFlag, 0);
        storeMemberInt(&cstate, start_count, 0);
#if STARTUP_FORCE_JIGGLE_TEST
        storeMemberBool(&ictest, startup, true);
#endif
    MN_EXIT_CRITICAL();
}


/** \brief Resets rate setpoint rate limit logic
by requesting to set rate limit base to then-current position on the
next calculation of the setpoint
*/
static void control_ResetRateLimitsLogic(void)
{
    ctllim_Reinit(SETPOINT_INVALID);
}

/** \brief Monitors whether it is necessary to reset the setpoint
rate limits base on the basis of
- air loss
- controller wind-up
\param sp - the externally requested setpont
*/
static void control_RateLimitsGuard(void)
{
    bool_t req;

    {
    //2. If low supply, reset rate limits
        req = error_IsFault(FAULT_AIR_SUPPLY_LOW);
        /* No time filtering means we are susceptible to supply droop
        I think it's a good thing that droop causes the valve to slow down.
        */
    }

    if(req)
    {
        control_ResetRateLimitsLogic();
    }
}


/** \brief calculate position setpoint and error.
    The position setpoint is limited to its user configurable upper
    and lower limits if the High/Low Limit flags are set.  The change rates
    of the setpoint are also limited by valve open and close stroking speeds.
    The position error is calculated based on obtained position setpoint and valve
    current position. If valve position is beyond the hand wheel location, hand wheel
    positions are updated and bias change flags will be cleared.

    \param[in] ctlExtData_t *data: a pointer to the data structure that holds user configured
        position limits and rate of change limits
*/

static void calcSP_Err(const ctlExtData_t *data)
{
    //limit the setpoint if limits are on
    s32 sp = m_n4Setpoint;

    //moved control_RateLimitsGuard(sp);

    //This is good until ctllim_ConditionControlMode is able of changing control mode
    //(void)ctllim_ConditionControlMode(m_n1ControlMode, &sp);

    m_n2CSigPos = (pos_t)(sp + ictest.m_n2SPOffset); //Guaranteed no overflow by effective sp limit values

    //move all of the historical errors down
    m_PosErr.err8 = m_PosErr.err7; m_PosErr.err7 = m_PosErr.err6;
    m_PosErr.err6 = m_PosErr.err5; m_PosErr.err5 = m_PosErr.err4;
    m_PosErr.err4 = m_PosErr.err3; m_PosErr.err3 = m_PosErr.err2;
    m_PosErr.err2 = m_PosErr.err1; m_PosErr.err1 = m_PosErr.err;

    //calculate the current position error
    // m_PosErr.err is positive in the fill direction (i.e., need to fill to get to SP)
    pos_least_t errScaled;
    if(m_bATO)   // air to open
    {
        errScaled = m_n2CSigPos - m_n4PositionScaled;
    }
    else
    {
        errScaled = m_n4PositionScaled - m_n2CSigPos;
    }

#if USE_BORROWED_FROM_SVI1K
    /** TFS:4233 */
    //Adjust PID error to the new range, adjusted by open stop to be in full mechanical travel range
    errScaled = intscale32(errScaled, data->m_pCPS->n4OpenStopAdj, 0, (u8)STANDARD_NUMBITS );
#endif
    //limit the error to fit in 16 bits
    errScaled = CLAMP(errScaled, -INT16_MAX, INT16_MAX);

    //get error
    m_PosErr.err = (s16)errScaled;
    //get absolute value of error
    m_PosErr.err_abs = (s16)ABS(errScaled);
}



static void jiggle_Cancel(void)
{
    ictest.m_bProbeActive = false;
    ictest.cycleKtr       = 0;
    ictest.m_n2SPOffset   = 0;
    ictest.timeKtr        = 0;
}

/** \brief Determines if it is safe to save the bias (workpoint).  It does this
        by jiggling the valve (+/- .08%) and monitoring for zero average error.
    This function supports SAR 11.1 to 11.2
    \param data - pointer to the control variables structure
    \return request to save bias
*/
static bool_t CheckForInControl(const ctlExtData_t *data)
{
    bool_t bOKtoSave = false;


    // compute the average error to see if we can safely transfer the integral
    ictest.avgErr = (s16)(((ictest.avgErr * (DETECTOR_AVG_CONST - 1)) + m_PosErr.err)   / DETECTOR_AVG_CONST);

    /* If David's original conditions (+Ernie's BiasChangeFlag test) for capturing "good" stable bias
       are not met, discard any jiggle test; otherwise proceed with Ernie's logic
    */
    //      in determining valve movement
    if( !(  (m_nPosAtStops==NOT_STOP_0) && (m_PosErr.err_abs < HALF_PCT_82) &&
        (ABS(m_PosErr.err8-m_PosErr.err) < PT3_PCT_49) &&
        (ABS(m_PosErr.err4-m_PosErr.err) < PT3_PCT_49)
      && (cstate.BiasChangeFlag != AIR_LOLO_3) ) )
    {
        jiggle_Cancel(); //David's conditions are not met
    }
    else
    {
        Bias_t nTemp = GetDetectorIntegralLimit(data->m_pPID->PosComp);

	    //Only run the jiggle test if the integral is allowed to run
	    //and we have not indicated airloss
	    // if integral is relatively large and error is relatively small, invoke the detector
	    if (
	          (cstate.BiasChangeFlag != AIR_LOLO_3) &&
	          (!process_CheckProcess()) &&  //lint !e960 process_CheckProcess does not have side effects
	          (
	            (ABS(m_BiasData.m_Integral) > nTemp) &&
	            (ABS((s32)ictest.avgErr) < DETECTOR_AVG_ERROR_THRESH)
	          )
	        )
	    {
	        ictest.m_bProbeActive = true;

	        // if timeout then restart the detector
	        if (++ictest.timeKtr >= JIGGLE_TIMEOUT)
	        {
	            ictest.cycleKtr       = 0;
	            ictest.m_n2SPOffset   = 0;
	            ictest.timeKtr        = 0;
	        }

	        // error must be zero before we jiggle
	        if (ictest.avgErr == 0)
	        {
	            // jiggle the setpoint a little
	            ictest.m_n2SPOffset = (ictest.m_n2SPOffset < 0) ? JIGGLE_AMOUNT : -JIGGLE_AMOUNT;
	            ictest.avgErr     = ictest.m_n2SPOffset;
	            if (++ictest.cycleKtr >= JIGGLE_CYCLES)
	            {
	                bOKtoSave  = true;
	                ictest.cycleKtr     = 0;
	                ictest.m_n2SPOffset = 0;
	                ctltrace.JigglesPassed++;
	            }
	            ictest.timeKtr          = 0;
	        }
	    }
        // integral is small or integral is not allowed to run because of low pressure
        // or when process_CheckProcess stopping during process_CheckProcess is
        // to keep jiggle test from running in some user processes.  Unfortunatly,
        // it does not block running during step test.
        else
        {
            jiggle_Cancel();
        }
    }
    return bOKtoSave;
}
/** \brief Initialize control state variables on entering closed loop mode

    NOTE: can't modify m_PosErr because of the order of its calculations
	\param[in] ctlExtData_t *data: a pointer to the data structure that holds control parameters
*/
static void control_EnterClosedLoop(const ctlExtData_t *data)
{
    //m_BiasData doesn't seem to be affected

    /* Rate limits base to current position (needs to be corrected for tight shutoff)
        varcache.
            m_n2CSigPosRL
            m_n2CSigPos
            m_PosErr.err8
            m_PosErr.err
            m_PosErr.err_abs

    */
    control_ResetRateLimitsLogic();
    //calcSP_Err(data);

    //history control errors. They should stay what they are 'coz sp had been avaliable
#if 0
    m_PosErr.err1 = 0;  m_PosErr.err2 = 0;
    m_PosErr.err3 = 0;  m_PosErr.err4 = 0;  m_PosErr.err5 = 0;
    m_PosErr.err6 = 0;  m_PosErr.err7 = 0;
#endif
#if 0
    m_PosErr.err1 = m_PosErr.err;  m_PosErr.err2 = m_PosErr.err;
    m_PosErr.err3 = m_PosErr.err;  m_PosErr.err4 = m_PosErr.err;  m_PosErr.err5 = m_PosErr.err;
    m_PosErr.err6 = m_PosErr.err;  m_PosErr.err7 = m_PosErr.err;
#endif

    //cstate
    /* Set cstate.
        m_n2CSigPos_p
        i_count
        LastComputedPosComp
    */
    control_ComputePoscomp(data);
    cstate.m_n2Erf1 = 0; //AK: Well, at least not random.

    /*AK: cstate integral-related flags
    are quite something. The good news (REVIEW!) is that they are set outside
    Integral_Control() every control cycle, and have at least I_CALC_LOW/2=5
    control cycles to set properly because i_count is set to 0 above.
    The exception is Integral_Previously_Limited to count time to resetting
    integral. It is only logical to restart saturation window afresh after
    exiting an open-loop mode.
    */
    cstate.Integral_Previously_Limited = false;
    //and the rest
    cstate.isBiasLowerLimited = false;
    cstate.isBiasUpperLimited = false;
    cstate.m_bActuatorAtLim = false;
    cstate.isIPLowerLimited = false;
    cstate.isIPUpperLimited = false;

    /*Makes no sense to continue with any boost existing before an open-loop
    mode which we are leaving
    Perhaps it is possible to play with cBoost and nBoostCount to make a more
    intelligent setting but it's not obvious and not immediately needed
    */
    cstate.cBoost = 0;

    /* Error calculations need not span interruption by a period of open-loop
    mode
    */
    cstate.nErrorCount = 0;

#if USE_VALVE_MOVE_ESTIMATE
    cstate.m_n2Pos_p = (pos_t)m_n4PositionScaled; //need to start somewhere
#endif
    //ictest
    /* Set ictest.
        m_bProbeActive
        cycleKtr
        m_n2SPOffset
        timeKtr
    */
    jiggle_Cancel();
#if STARTUP_FORCE_JIGGLE_TEST
    ictest.startup = true; //Larry, what's your take on ictest.startup?
#endif
    ictest.avgErr = m_PosErr.err;

    //Other
    bios_SetBypassSwitch(false);   // bypass pressure loop switch if false: =loop on!
}


#define TIME_REQUIRED_FOR_INTEGRAL_RESET_MS (u32)20000

/** \brief Check for sign difference between error and integral

    \param data - a pointer to the data structure that holds control parameters
*/
static void CheckForOvershoot(const ctlExtData_t *data)
{
  if (cstate.Integral_Previously_Limited == true)
  {
    tick_t time_stopped = timer_GetTicksSince(cstate.Integral_First_Stopped) * TB_MS_PER_TICK;
    if (time_stopped > TIME_REQUIRED_FOR_INTEGRAL_RESET_MS)
    {
       cstate.m_bActuatorAtLim = true;
      //Set the actuator fault
      error_SetFault(FAULT_ACTUATOR);
    }
    else
    {
      //Do nothing the flag m_bActuatorAtLim is only reset by the code below that checks for overshoot
    }
  }

  if (
         ( (!IsSameSign(m_BiasData.m_Integral, (s32)m_PosErr.err)) || (m_BiasData.m_Integral ==0) ) &&
        !process_CheckProcess())            //lint !e960 process_CheckProcess does not have side effects
    {
        s32 amount = m_BiasData.m_Integral;
        //s32 step;
        if (cstate.m_bActuatorAtLim)
        {
            cstate.m_bActuatorAtLim = false;
            //Note this flag is cleared in two places.  The main place to clear it
            //is in integral control.  Clearing it here is defensive programming
            //in case we put in other features that depend on this flag.  That is
            //once reset we should not be elligible to reset again until the flag
            //has been determined to be valid again
            cstate.Integral_Previously_Limited = false;
            //These have to be reset here.  isOutputAtLimit is called
            //before these flags are updated.  In the case these flags are
            //set true this is not a problem because the logic that sets
            //these true also limits the integral.  Thus, only a status
            //bit is innacurate for a loop.  However, the purpose of this
            //logic is to reset a large integral.  There is no guarantee
            //that the integral control will run right after this reset and
            //thus these flags can be high and the overshoot will be set on.
            //In the case these are cleared in error again the place where they
            //are set limits the integral so there is no system performance issu
            cstate.isBiasLowerLimited = false;
            cstate.isBiasUpperLimited = false;
            ctltrace.Overshoots++;

            storeMemberInt(&m_BiasData, m_Integral, 0);
            storeMemberInt(&m_BiasData, Low_Integral_Limit, 0);
            storeMemberInt(&m_BiasData, High_Integral_Limit, 0);

        }
        UNUSED_OK(data);

        Bias_t newBIAS = m_BiasData.BIAS - (amount - m_BiasData.m_Integral);
        storeMemberInt(&m_BiasData, BIAS, newBIAS);
    }
}


static void testIntegralState(void)
{
    Struct_Test(IntegralState_t, &m_BiasData);
}

#if USE_VALVE_MOVE_ESTIMATE
/** \brief A very rough estimate of whether the valve moved
\return true iff considered moved
*/
static bool_t control_HasValveMoved(void)
{
    bool_t m_bValveMove;
// ep: magic number 15 - fixed in later version
// AK:Q: Should nPosShift be exactly the same as nGap in control_ContinuousDiagnostics()?
// DZ: two different applications. keep both for flexibility.  Highly related.  Exactly the same? ?? possible.
// AK:Q: How is it computed, anyway?
// DZ: Estimate for noise. A rough estimate.

    //compute estimate of noise in position units
    pos_t nPosShift = POS_SHIFT + (pos_t)(15u*(UINT16_MAX/(m_n2PosRange)));

    //compute change in position
    pos_t nPosChange = (pos_t)ABS(m_n4PositionScaled - cstate.m_n2Pos_p);

    if(nPosChange > nPosShift)     /* noise level */
    {
        //position change greater than noise level

        //Set Flag for valve move and reset count
        m_bValveMove = true;

        //save position as previous
        cstate.m_n2Pos_p = (pos_t)m_n4PositionScaled;
    }
    else
    {
        //position change less than noise level

        //reset valve move flag and increment count
        m_bValveMove = false;
    }
    ctltrace.m_bValveMove = m_bValveMove;
    return m_bValveMove;
}
#endif //USE_VALVE_MOVE_ESTIMATE


/** \brief This function is internally called to
    /1) calculate position setpoint change and compensate bias for its change
    2) handle air loss and hand wheels.
    it will analyze data to determine if valve is moving or not. if moving, what direction it is.
    if it found bias is shifted abnormally, it will set bias change flag BiasChangeFlag
    This unction also try to detect handwheel position.
    it also reset bias change flag when meet certain conditions.
    \param[in] ctlExtData_t *data: a pointer to the data structure that holds control parameters
*/


static void airloss_handle(const ctlExtData_t *data)
{
// Air loss, hard stop or handwheel causes position errors, which are unable to be removed.
// That may tend to cause integral windup.  In control, bias is monitered to detect possible windup
// and stop the integral to prevent the windup if detected. Then waits for recovery.

    pos_least_t nSP_delta = m_n2CSigPos - cstate.m_n2CSigPos_p;

    //These are empirical calculations based on trial and error
    //dont need to do anything for very small steps (below 0.3%)
    if (ABS(nSP_delta) > PT3_PCT_49 )
    {
        control_ComputePoscomp(data);
    }

/* BIAS AVERAGE and ANTI WINDUP */

// DZ: PosComp is compensation for bias change vs. position.
// COMP_BASE is the value that there is almost no compensation.
// nOffset is Bias difference


    CheckForOvershoot(data);            // See if overshoot following pneumatic saturation

    bool_t bOKtoSave = CheckForInControl(data);        // Jiggle the actuator if necessary
#if USE_VALVE_MOVE_ESTIMATE
    bool_t m_bValveMove = control_HasValveMoved();
    if(m_bValveMove)
    {
        bOKtoSave = false;
        jiggle_Cancel();
    }
#endif //USE_VALVE_MOVE_ESTIMATE

    if (bOKtoSave)
    {
        storeMemberBool(&ictest, m_bSaveBias, true);

        //Repeated pattern; could be a function
        storeMemberInt(&m_BiasData, m_Integral, 0); //
        storeMemberInt(&m_BiasData, Low_Integral_Limit, 0);
        storeMemberInt(&m_BiasData, High_Integral_Limit, 0);

        cstate.start_count   = START_COUNT_MAX;   //startup mode is done

        cstate.BiasChangeFlag = 0;

        //capture bias average at base, and now let it get rejected if out of range
#if 0
        ictest.BiasAvgAtBase = MAX(m_BiasData.BIAS, BIAS_LOW_LIMIT);
#else
        ictest.BiasAvgAtBase = m_BiasData.BIAS;
#endif
        /* Strictly speaking, we also need to capture temperature
        But we believe it won't change much for the crude compensation
        before we do the compensation at save time.
        */
    }
}

/** \brief This function is main function and internally called to calculate PID
    control by calling multiple functions.
    Assumes we are in closed-loop control
    \param[in] ctlExtData_t *data: a pointer to the data structure that holds control parameters
	\return (normalized) control output
*/
static s32 control_PID(const ctlExtData_t *data)
{
    s32 lVal, lErf;

// AK:NOTE: These booleans can and probably should be precomputed

    //set low cost and single acting flags

    MN_ASSERT((data->m_pPID!=NULL) && (data->m_pPositionStop!=NULL));

    //see if the valve is at either stop
    if (m_n4PositionScaled < data->m_pCPS->ExtraPosLow)
    {   // fully closed
        m_nPosAtStops = CLOSED_1;
    }
    else if (m_n4PositionScaled > data->m_pCPS->ExtraPosHigh)
    {   // fully open
        m_nPosAtStops = OPEN_2;
    }
    else
    {
        m_nPosAtStops = NOT_STOP_0;
    }

    //Prime the recursive variables
    if ((cstate.start_count <= 1) && cstate.m_bRegularControl)
    {
        cstate.m_n2Pos_p = (pos_t)m_n4PositionScaled;
        cstate.start_count++;
    }

    airloss_handle(data);
    if( (mode_GetEffectiveMode(mode_GetMode()) & (MODE_OPERATE|MODE_MANUAL)) !=0U )
    {
        control_SetPositionErrorFlag(data);
    }


    /* D CONTROL */
    /* Exponential forgetting new = (1-b)*old + b*x = old + b*(x-old)
    with b=D_CALC_COEF)/(D_CALC_COEF + data->m_pPID->D)
    */
    lErf =  ( (m_PosErr.err - cstate.m_n2Erf1)*D_CALC_COEF)/(D_CALC_COEF + data->m_pPID->D); /// AK:NOTE: A good application for division by multiplication?
    lErf += cstate.m_n2Erf1;
    cstate.m_n2Erf1 = lErf;
    m_n2Deriv = m_PosErr.err - (pos_t)cstate.m_n2Erf1;
    if( ((ABS(m_n2Deriv)) < 3) && (m_PosErr.err_abs < PT1_PCT_16) ) /// AK:NOTE: The 3 is now .03% (5 counts). AK:Q: How is it determined?
    {
        m_n2Deriv = 0;
    }
    if( (m_nPosAtStops != NOT_STOP_0) && (m_PosErr.err_abs < TWO_PCT_328) )
    {
        m_n2Deriv = 0;
    }

    //I control
    bool_t m_bIControl = IsIControl(data);
    if(m_bIControl)
    {
        if (cstate.start_count < START_COUNT_MAX)
        {
            cstate.start_count++;
        }
        m_n2Deriv = 0;
        Integral_Control(data);
    }
#if (CONTROL_CHECKSUM_PROTECT & CONTROL_INTEGRAL_TEST_INTERLEAVE) != 0
    else
    {
        testIntegralState();
    }
#endif

    //P control
    lVal = Proportional_Control(data, m_bIControl);
    ctltrace.m_IpCurr = lVal;

    return lVal;
} //-----  end of control_PID() ------


/** \brief This function is internally called to check air pressure
    if supply pressure is found too low, it will set  FAULT_AIR_SUPPLY_LOW
    flag to indicate low supply pressure as well as set bias change flag to
    AIR_LOLO_3.  Otherwise it clear FAULT_AIR_SUPPLY_LOW flag and reset bias
    change flag
*/
static void checkAirPressure(const ctlExtData_t *data)
{
    //const BoardPressure_t* BoardPressure;
    //BoardPressure = cycle_GetPressureData();
    //m_bPress_Supply = cnfg_GetOptionConfigFlag(PRESSURE_SUPPLY);
/// AK:NOTE: This invites common expression elimination
    //if we have supply pressure sensor (and it is not faulty)  - check it

    //Note the function checkAirPressure is called continiously in PID
    //This is required to make sure that these flags are not stale
#if USE_PILOT_FOR_SUPPLY_THRESHOLD
    Pilot_Low = false;
#endif

    const BoardPressure_t *pres = pres_GetRawPressureData();

    pres_t m_n2Press_Supply = pres->Pressures[PRESSURE_SUPPLY_INDEX];
    bool_t HaveSupply = m_n2Press_Supply != PRESSURE_INVALID;

    if(HaveSupply)
    {
        pres_t supply_loss_threshold = data->pPneumaticParams->SupplyLossThreshold_Supply;
        if( m_n2Press_Supply < supply_loss_threshold)  // No air
        {
            cstate.BiasChangeFlag = AIR_LOLO_3;      // air loss
            error_SetFault(FAULT_AIR_SUPPLY_LOW);
        }
        else
        {
            if(cstate.BiasChangeFlag == AIR_LOLO_3)
            {
                cstate.BiasChangeFlag = 0;
            }
            error_ClearFault(FAULT_AIR_SUPPLY_LOW);
        }
    }
    // If no supply pressure sensor (or it is faulty), use the pilot pressure sensor which we always have
    // There is no check on the Pilot sensor fault because we would be in faisafe if it were set.
    else
    {
#if 1
        pres_t m_n2Press_IP = pres_GetPressureData()->Pressures[PRESSURE_PILOT_INDEX];

        if( m_n2Press_IP < data->pPneumaticParams->SupplyLossThreshold_Pilot)
        {
            // SAR 3.3 partial
            cstate.BiasChangeFlag = AIR_LOLO_3;                // air loss
            error_SetFault(FAULT_AIR_SUPPLY_LOW);
#if USE_PILOT_FOR_SUPPLY_THRESHOLD
            Pilot_Low = true;
#endif
        }
        else
        {
            if(cstate.BiasChangeFlag == AIR_LOLO_3)
            {
                cstate.BiasChangeFlag = 0;
            }
            error_ClearFault(FAULT_AIR_SUPPLY_LOW);
        }
#else // end of old code
    //Note fault setting moved to mon_checkLowSupplyFromIPandI
    //
        if (mon_checkLowSupplyFromIPandI(data->pPneumaticParams))
        {
            Pilot_Low = true;
            cstate.BiasChangeFlag = AIR_LOLO_3;
        }
        else
        {
            //Note Pilot_Low marked false at top of this fcn
            //So kept this pattern
            if(cstate.BiasChangeFlag == AIR_LOLO_3)
            {
                cstate.BiasChangeFlag = 0;
            }
        }
#endif
    }
}


//TFS:8333#define SUPPLY_FACTOR (STD_FROM_PSI(120.0F) / STD_FROM_PSI(3.0F))   //!< slope as a function of supply
//TFS:8333#define ACTUATOR_DIFFERENTIAL_LIMIT             STD_FROM_PSI(80.0F)
//TFS:8333#define ACTUATOR_TO_SUPPLY_PRESS_TOLERANCE(x)  (STD_FROM_PSI(2.0F) + ((x) / SUPPLY_FACTOR))

#define LIMIT_INACTIVE 0
#define LIMIT_EXHAUST 1
#define LIMIT_FILL 2
#define LIMIT_FILL_BIT_PATTERN 3U
//TFS:8333#define DOUBLE_ACTING_ADJUSTMENT STD_FROM_PSI(0.0F)

/** \brief Initial cheat version per initial requirement.
We don't yet have a clean solution e.g. accounting for air loss, handwheel etc.
When/if we do, we'll replace this function.
\return ERR_OK, ERR_LOWERLIM, or ERR_UPPERLIM
*/
ErrorCode_t control_IsLimited(void)
{
    ErrorCode_t err;
    const ComputedPositionConf_t *pCPS = pos_GetComputedPositionConf(NULL);
    MN_ENTER_CRITICAL();
        if(  ( (m_n4PositionScaled <  pCPS->ExtraPosLow) &&
               (m_n2CSigPos        <= m_n4PositionScaled) ) )
        {
            err = ERR_LOWERLIM;
        }
        else if( ( (m_n4PositionScaled >  pCPS->ExtraPosHigh) &&
               (m_n2CSigPos        >= m_n4PositionScaled) ) )
        {
            err = ERR_UPPERLIM;
        }
        else
        {
            err = ERR_OK;
        }
    MN_EXIT_CRITICAL();
    return err;
}


#define INTEGRAL_SAFETY_MARGIN 200

#define IS_EXHAUSTING() (m_PosErr.err < 0)

/** \brief Test if current I/P output has generated minimum or maximum actuator pressure
    \return false if inside min/max range, true if outside (actuator saturated)
*/
static bool_t isOutputAtLimit(const ctlExtData_t *data)
{
    bool_t  isActuatorFaultPresent;
    bool_t  result;
    s16 diffLimit;

    bool_t  exhausting = IS_EXHAUSTING();       // true if reducing I/P current



    /*Get pointer to pressures (raw_pressures are compensated, but they don't
    include user calibration */

    const pres_t * raw_pressures = pres_GetRawPressureData()->Pressures;

    /* Initilize limits to false */
    result = false;
    //trace only!
    u8 pilot_limit = LIMIT_INACTIVE;
    u8 pressure_limit = LIMIT_INACTIVE;
    u8 count_limit = LIMIT_INACTIVE;

    /*Read Pilot pressure*/
    pres_t pilot = raw_pressures[PRESSURE_PILOT_INDEX];
    /*Check if Pilot pressure is not faulty, note that this test is currently redundant
    as a pilot pressure fault would put the system in
    failsafe */

    pres_least_t pilot_low_limit = data->pPneumaticParams->presLimitsPilot.presLimit[Xlow];
    pres_least_t pilot_high_limit = data->pPneumaticParams->presLimitsPilot.presLimit[Xhi];

    //if (error_IsFault(FAULT_PRESSURE4) == false )
    if (pilot != PRESSURE_INVALID)
    {
        /*Check the exhausting direction */
        if (exhausting)                          // reducing I/P current
        {
             // SAR 4.3, 5.3, 6.1
             // This relies on the fact that for single acting there is a minimum
             // relay input below which  no actuator pressure is generated.  Since
             // this occurs above zero PSI it forms a useful lower limit.  Note
             // for double acting the minimum relay output is ~ 0 psi and is thus
             // not significantly different than looking for minimum bias/IP
             if ( pilot <= pilot_low_limit )
             {
                 result = true;
                 pilot_limit = LIMIT_EXHAUST;
             }
             else
             {
                 /* Limit not active do nothing */
             }
        }
        else
        {
            // In the filling direction we can calculate an equivalent actuator pressure
            // from the pilot pressure.
             // SAR 4.4, 5.4, 6.2
            if ((pilot > pilot_high_limit))
            {
               result = true;
               pilot_limit = LIMIT_FILL;
            }
            else
            {
                 /* Limit not active*/
            }

        }
    }
    else
    {
        /*Can't use pilot pressure as a diagnostic if sensor is faulty*/
    }
    // Establish method for determining saturation.  Use pilot pressure if LowCost
    // or if any of the needed pressure sensors are deemed faulty.

    if(
       (raw_pressures[PRESSURE_SUPPLY_INDEX] == PRESSURE_INVALID) ||
       (raw_pressures[PRESSURE_ACT1_INDEX] == PRESSURE_INVALID) ||
       ((data->pPneumaticParams->SingleActing == 0) &&
            (raw_pressures[PRESSURE_ACT2_INDEX] == PRESSURE_INVALID)
       )
      )
    {
        isActuatorFaultPresent = true;
    }
    else
    {
        isActuatorFaultPresent = false;
    }

    if ( !isActuatorFaultPresent )
    {
        // compare with  cycle_GetSupplyPressure();
        pres_t actuatorLimit  = raw_pressures[PRESSURE_SUPPLY_INDEX];
        actuatorLimit -= ACTUATOR_TO_SUPPLY_PRESS_TOLERANCE(actuatorLimit);
        pres_t mainPressure   = raw_pressures[PRESSURE_MAIN_INDEX];       // ACT1 for SA; ACT1 - ACT2 for DA

        // single acting && sensors OK
        if (data->pPneumaticParams->SingleActing != 0)
        {
            if (exhausting == true)
            {
                if (mainPressure <= (ACTUATOR_LOW_PRESS_LIMIT))
                {
                    //SAR 4.1 1 psi lower limit for single acting and additional counts
                    if (m_BiasData.m_Integral <= (m_BiasData.Low_Integral_Limit - INTEGRAL_SAFETY_MARGIN))
                    {
                        result = true;
                        pressure_limit = LIMIT_EXHAUST;
                    }
                }
                else
                {
                    //SAR 4.1 update the lower integral limit until we cross the 1psi level
                    storeMemberInt(&m_BiasData, Low_Integral_Limit, m_BiasData.m_Integral);
                }
            }
            else
            {
                if (mainPressure >= actuatorLimit)
                {
                    //SAR 4.2 actuator limit plus 200 counts
                    if (m_BiasData.m_Integral >= (m_BiasData.High_Integral_Limit + INTEGRAL_SAFETY_MARGIN))
                    {
                        result = true;
                        pressure_limit = LIMIT_FILL;
                    }
                }
                else
                {
                    //SAR 4.2 update the upper integral limit until we cross the 1psi level
                    storeMemberInt(&m_BiasData, High_Integral_Limit, m_BiasData.m_Integral);
                }
            }
        } /*End single acting*/
        else
        {
            /* For double acting atmospheric pressure cancels out
               However, we now compare the difference of two sensors with a third
               for this we expect a higher average error so we reduce the
               actuatorLimit accordingly
            */
            actuatorLimit = actuatorLimit - DOUBLE_ACTING_ADJUSTMENT;
            diffLimit         = MIN(actuatorLimit, ACTUATOR_DIFFERENTIAL_LIMIT);
            if ( exhausting == true )
            {
                if ((mainPressure <= -diffLimit) && (raw_pressures[PRESSURE_ACT2_INDEX] >= actuatorLimit))
                {
                    //SAR 5.1 lower double acting pressure and integral limit
                    if (m_BiasData.m_Integral <= (m_BiasData.Low_Integral_Limit - INTEGRAL_SAFETY_MARGIN))
                    {
                        result = true;
                        pressure_limit = LIMIT_EXHAUST;
                    }
                }
                else
                {
                    //SAR 5.1 update lower integral limit
                    storeMemberInt(&m_BiasData, Low_Integral_Limit, m_BiasData.m_Integral);
                }
            }
            else
            {
                if ((mainPressure >=  diffLimit) && (raw_pressures[PRESSURE_ACT1_INDEX] >= actuatorLimit))
                {
                    //SAR 5.2 upper double acting pressure and integral limit
                    if (m_BiasData.m_Integral >= (m_BiasData.High_Integral_Limit + INTEGRAL_SAFETY_MARGIN))
                    {
                          result = true;
                          pressure_limit = LIMIT_FILL;
                    }
                }
                else
                {
                    //SAR 5.2 update upper integral limit
                    storeMemberInt(&m_BiasData, High_Integral_Limit, m_BiasData.m_Integral);
                }
            }
        } /*End double acting*/
    }
    /* Both IP and Bias are very conservative measurements of saturation
       using these has three purposes.  First, it ensures that any system
       behavior that results in staturation sets appropriate flags.
       Second, they serve as a backup in the case of sensor failure.
       Third, this allows the integral contribution to be zeroed if the
       sign of the integral and sign of error become opposite
    */
    if ( !exhausting )
    {
        if ((cstate.isIPUpperLimited == true )  ||  (cstate.isBiasUpperLimited == true))
        {
            count_limit = LIMIT_FILL;
            //Note you CANNOT stop the integral if isBiasUpperLimited
            //because you would never be able to clear the integral
            if ( cstate.isIPUpperLimited == true )
            {
                result = true;
            }
            else
            {
                //We can't set this flag based on Bias because the bias
                //flag isBiasUpperLimited is not recalculated when result is true
            }
        }
        else
        {
            /* This test for limit is not active, no need to do anything */
        }
#if USE_PILOT_FOR_SUPPLY_THRESHOLD
        /* Test for low pilot pressure when filling */
        if (Pilot_Low)
        {
            // SAR 3.3 partial
            result = true;
        }
#endif //USE_PILOT_FOR_SUPPLY_THRESHOLD
    }
    else
    {
        if ((cstate.isIPLowerLimited == true )  ||  (cstate.isBiasLowerLimited == true))
        {
            count_limit = LIMIT_EXHAUST;
            //Note you CANNOT stop the integral if isBiasLowerLimited
            //because you would never be able to clear the integral
            if ( cstate.isIPLowerLimited == true )
            {
                result = true;
            }
            else
            {
                //We can't set this flag based on Bias because the bias
                //flag isBiasLowerLimited is not recalculated when result is true
            }
        }
        else
        {
            /* This test for limit is not active, no need to do anything */
        }
    }
    //This code is moved here from IsIControl
    //Implements Version 6.0 SAR3.4 through BiasChangeFlag = 3
    // SAR 3.3 partial
    bool_t Air_Low_Limit = false;
    if (/*m_bIControl &&*/ (cstate.BiasChangeFlag != 0) )
    {
        if (cstate.BiasChangeFlag == AIR_LOLO_3)
        {
            if (!IS_EXHAUSTING())
            {
                //This path handles SAR 3.5
                // SAR 3.3 partial
                Air_Low_Limit = true;
            }
            else
            {
                //Do nothing if we are trying to empty
                //we should not limit the integral just because
                //we have low supply pressure, since the unit
                //can exhaust
            }
        }
        else
        {
             //This branch used to set m_bIControl = false for
             //other BiasChangeFlags there are no other non zero flags
             //so no need for this branch
        }

    }
    ctltrace.Air_Low_Limit = Air_Low_Limit;

    if ( Air_Low_Limit )
    {
         // SAR 3.3 partial
         result = true;
    }

    //TFS:8814 "Remove jiggle test at startup" changed LAST_INTEGRAL_STATUS_BIT from 9 to 8
    ctltrace.Integral_Limit_Status = (u16)
          (( (u8)(result) & 1U )                        <<  0) +
          (( (u8)exhausting & 1U )                                 <<  1) +
          (( (u8)Air_Low_Limit & 1U)                               <<  2) +
          (( (u8)count_limit       & LIMIT_FILL_BIT_PATTERN)      <<  3) +
          (( (u8)pilot_limit    & LIMIT_FILL_BIT_PATTERN)         <<  5) +
          (( (u8)pressure_limit & LIMIT_FILL_BIT_PATTERN)         <<  7);

    return result;
}
#define LAST_INTEGRAL_STATUS_BIT  8

/**
     DZ: 8/22/06
    \brief  This function is internally called to determine if integral control should apply.
    If integral control should apply, m_bIControl = true; otherwise m_bIControl = false.

    \param[in] data - a pointer to the data structure that holds position limits
    \return true iff Integral Control is allowed
*/
static bool_t IsIControl(const ctlExtData_t *data)
{
    s16 nTemp2;
    bool_t bMoving_I;

    bool_t m_bIControl; //flag of integral control enabled
    if(  ( (m_n4PositionScaled <  data->m_pCPS->ExtraPosLow) &&
           (m_n2CSigPos        <= m_n4PositionScaled) ) ||
         ( (m_n4PositionScaled >  data->m_pCPS->ExtraPosHigh) &&
           (m_n2CSigPos        >= m_n4PositionScaled) ) )
    {
        m_bIControl = false;
    }
    else
    {
        m_bIControl = true;
    }
    // But reset (turn off integral)  if abs. error is within the deadzone
    // unless the "in control" detector is active
    if(m_bIControl && !ictest.m_bProbeActive && (data->m_pPID->DeadZone > 0) )
    {
        if(m_PosErr.err_abs <= data->m_pPID->DeadZone)
        {
            m_bIControl = false;
        }
    }

    // if integral still allowed and not in [handwheel] recovery
    if(m_bIControl)
    {
        //  determine a suitable noise level based on current and historical position error
        if( (m_PosErr.err_abs > HALF_PCT_82) &&
            ( (ABS((s32)m_PosErr.err4)) > HALF_PCT_82) &&
            ( (ABS((s32)m_PosErr.err8)) > HALF_PCT_82) )
        {
            nTemp2 = PT2_PCT_32 + (s16)(((u16)m_PosErr.err_abs) >> 2);
        }
        // otherwise noise level is .2 percent
        else
        {
            nTemp2 = PT2_PCT_32;  // normal noise: DZ: 11/18
        }
        // noise level is maximum of .6 percent
        nTemp2 = MIN(nTemp2, PT6_PCT_98);

        // default to valve moving
        bMoving_I = true;

        // now use the computed noise level to decide if the valve is not moving
        if( ABS(m_PosErr.err - m_PosErr.err8) < nTemp2 )
        {
            if(ABS(m_PosErr.err-m_PosErr.err4) < nTemp2)
            {
                bMoving_I = false;
            }
        }

        // ep: Could you provide an explanation of these particular percentages?
        // DZ: a potential problem area, which might be unstable.

        // another test: if historical error (err8) is between .3 and 2 percent
        // and current error is greater than err8 + .2 percent, valve is deemed not moving
        if( (m_PosErr.err8 < TWO_PCT_328) &&
            (m_PosErr.err8 > PT3_PCT_49)  &&
            (m_PosErr.err > (m_PosErr.err8 + PT2_PCT_32) ) )
        {
            bMoving_I = false;
        }

        // if the valve is moving or I is small or error is small then
        if( bMoving_I || (data->m_pPID->I < 2) || (m_PosErr.err_abs < 2) )
        {
            // if SA turn off integral
            if (data->pPneumaticParams->SingleActing != 0)
            {
                m_bIControl = false;  // m_bIControl = m_bIControl;  temporay!!! to avoid noise
            }
            // if DA to avoid limit cycling if DA
            else  // double acting
            {
               //this is to avoid limit cycling which sometimes occurs with error in this range
                //REQ 35-6, REQ 35-7, REQ 35-8, REQ 35-9 partially disable integral for double acting
                if( (m_PosErr.err_abs > TWO_PCT_328) ||
                    (m_PosErr.err_abs < ONE_PCT_164) ||
                    (m_PosErr.err_abs < ABS((s32)m_PosErr.err8)) )
                {
                    m_bIControl = false;
                }
            }
        }
    }

    ctltrace.m_bIControl = m_bIControl;
    return m_bIControl;
}

/** \brief Calculate effective P gain w.r.t. beta and direction
*/
static s32 control_ComputePGain(s32 Pcoef, s8_least beta)
{
    s32 lKp; //effective P gain
    /* NON-LINEAR GAIN */
    pos_least_t TempErrorAbs;       //absolute value of error, limited to 20%


    // if Beta is 0, the proportional output is linear with respect to the locally computed error
    // gain factor = 1.0
    if(beta == 0)
    {
        lKp = Pcoef;
    }
    else
    {
        s16_least TempFactor1;        //constant in beta calculation
        s16_least TempFactor2;        //constant in beta calculation
        //use 20% as cutoff for both + and - beta
        if(m_PosErr.err_abs > TWENTY_PCT_3277)
        {
            TempErrorAbs = TWENTY_PCT_3277;
        }
        else
        {
            TempErrorAbs = ABS(m_n2Err_p);
        }

        //equations for + or - beta different by a couple of factors
        //magic numbers still left as magic numbers
        if(beta > 0)
        {
            TempFactor1 = 164;
            TempFactor2 = 95;
        }
        else
        {
            TempFactor1 = 27;
            TempFactor2 = 70;
        }

        s32 lTemp = (  ( (10-beta)*100) + ( (beta*TempErrorAbs)/TempFactor1) );
        lKp = ((Pcoef)*lTemp)/(1000-(TempFactor2*beta));
    }

    // now limit the gain factor to the range P*1.5 .. P/5
    lKp = CLAMP(lKp, Pcoef/5, 3*Pcoef/2);

    // if the actual error is small (< .2 %) and the gain factor is above P_MID_CON
    // set the gain factor to the error times the (gain factor / 32)
    if((m_PosErr.err_abs < PT2_PCT_32) && (lKp > P_MID_CON))    // 200
    {
        lKp = (m_PosErr.err_abs*lKp)/32;
    }
    return lKp;
}
/**
     DZ: 8/22/06
    \brief This function is internally called to calculate proportional control.
     In addition to proportional control, boost parameter is used to add additonal
     output to improve response near the steady state.

    \param[in] data - a pointer to the data structure that holds control parameters
    \return lVal - which is proportional control and boost output.

     Proportional_Control() includes D control via the m_n2Deriv term
*/
static s32 Proportional_Control(const ctlExtData_t *data, bool_t m_bIControl)
{
    s16 nZdead;             // dead area (zdead+offset) where boost is not applied
    u16 nBand;              // working copy of PID->Band which is a function of supply pressure
    s16_least nOffset;      // dead area (zdead+offset) where boost is not applied
                            //   only for double acting
    //s16_least nOffset1;
    s32 lVal;               // output value after computing err*P + K*D and adding boost, if any
    const boostCoeff_t *boostCoeff;

    cstate.nBoostCount++;          // count of control cycles - must be 300 (4.5 seconds)
                            //  or more to apply boost in the fill direction

    /* limit beta and error for P action  */

    // compute local error, m_n2Err_p. It is upper limited to +/- ERR_HIGH_P
    if(m_PosErr.err > ERR_HIGH_P)       /// ep: ERR_HIGH_P == approx 49 percent
    {
        m_n2Err_p = ERR_HIGH_P;
    }
    else if(m_PosErr.err < -ERR_HIGH_P)
    {
        m_n2Err_p = -ERR_HIGH_P;
    }
    // if error is less than .06 percent use 0.
    else if(m_PosErr.err_abs < ERR_S)
    {
        m_n2Err_p = 0 ;
    }
    else
    {
        m_n2Err_p = m_PosErr.err;
    }

    // now compute the working value for nBand
    nBand = data->m_pPID->Band;

    // no deadband if in startup mode
    if(cstate.start_count < START_COUNT_MAX)
    {
        nBand = 0;
    }

    //reduce the boost band in the case that sometimes causes DA limit cycling
    if( (data->pPneumaticParams->SingleActing == 0) &&
        (m_n2CSigPos < (cstate.m_n2CSigPos_p + PT3_PCT_49)) &&
        (m_n2CSigPos > (cstate.m_n2CSigPos_p - PT3_PCT_49) ) )
    {
        if(m_PosErr.err_abs < TWO_PCT_328 /*&& m_PosErr.err_abs > 164*/)
        {
            nBand = (nBand>>1);
        }
    }


    // finalize selected boost coefficients based on configured relay type
    boostCoeff = &data->pPneumaticParams->boostCoeff;
    nOffset = boostCoeff->BoostOffset;
    nZdead = (s16)(boostCoeff->boost[Xhi] * nBand);

    ///////////// This lKp is good for D term and for P term in fill direction

    // make sure cBoost is only 0 or 1 (change to boolean?)
    if(cstate.cBoost > 1 )
    {
        cstate.cBoost = 0;
    }

    s32 PTerm;
    s32 DTerm;
    // if SA filling or  DA (don't boost SA in exhaust direction)
    if( m_PosErr.err >= 0)
    {
        // main proportional output calculation with P and D terms
        s32 lKp = control_ComputePGain(data->m_pPID->P, data->m_pPID->Beta);
    //TFS:3520, TFS:3596 -- separate terms P, D and Boost
        PTerm = (lKp * m_n2Err_p) / P_CALC_SCALE;   /* Kp =100 mean 10%*/
        DTerm = (lKp * m_n2Deriv) / D_CALC_SCALE;
        lVal = PTerm + DTerm;
        ctltrace.m_pTerm = PTerm;
        ctltrace.m_dTerm = DTerm;
        // 1% error: 100*164/250=65

        // now determine boost, if any
        if( /*m_bIControl && */ (m_PosErr.err > (ERR_BOOST_1-(cstate.cBoost*ERR_BOOST_2))) )  //ignoring m_bIcontrol on fill, like in AP
        {
            // if nBand very small, booststate is 0
            if(nBand < 1)
            {
                cstate.cBoost = 0;
            }
            // boost state 0 and boost count low  < 300 ??? Just delete?
            else if ( (cstate.cBoost == 0) && (cstate.nBoostCount < BOOST_COUNT_LOW))
            {   // do nothing
            }

            // if computed output greater than deadband+offset, apply boost 1 and set boost state 1
            else if(lVal > (nZdead+nOffset) )    // +/- 800/(m_pPID->PositionCompensation-5)
            {
                lVal += boostCoeff->boost[Xhi] * nBand;
                cstate.cBoost = 1;
            }

            // if computed output greater than deadband/2, apply boost 2 and set boost state 1
            else if(lVal > (nZdead/2))
            {
                lVal += boostCoeff->boost[Xlow] * nBand;
                cstate.cBoost = 1;
            }
            // otherwise set boost state to 0
            else
            {
                cstate.cBoost = 0;
            }
        }
        // otherwise set boost state to 0
        else
        {
            cstate.cBoost = 0;
        }
    }
    // SA exhausting or DA
    else
    {
        cstate.nBoostCount = BOOST_COUNT_HIGH;

        // main proportional output calculation with P and D terms
        s32 lKp = control_ComputePGain(data->m_pPID->P + data->m_pPID->PAdjust, data->m_pPID->Beta);
    //TFS:3520, TFS:3596 -- separate terms P, D and Boost
        PTerm = (lKp * m_n2Err_p) / P_CALC_SCALE;
        DTerm = (lKp * m_n2Deriv) / D_CALC_SCALE;
        lVal = PTerm + DTerm;
        ctltrace.m_pTerm = PTerm;
        ctltrace.m_dTerm = DTerm;

        // only boost in exhaust direction if DA (not SA)
        if(data->pPneumaticParams->SingleActing==0)
        {   // double acting

            // integral must be active and error within limits to boost
            if(m_bIControl && (m_n2Err_p < -(ERR_BOOST_1-(cstate.cBoost*ERR_BOOST_2) )) )  //  if(m_n2Err_p < -(150-cBoost*50))
            {
                // if computed output < dead + offset apply boost 1 and set boost state 1
                if((lVal < -(nZdead + nOffset)) && (nBand > 0))
                {
                    //lVal -= (boostCoeff->boosthigh * nBand);
                    lVal -= (boostCoeff->boost[Xhi] * nBand);
                    cstate.cBoost = 1;
                }

                // if computed output < dead/2 apply boost 2 and set boost state 1
                else if(lVal < (-nZdead/2))
                {
                    //lVal -= (boostCoeff->boostlow * nBand);
                    lVal -= (boostCoeff->boost[Xlow] * nBand);
                    cstate.cBoost = 1;
                }
                // otherwise set boost state 0 (with no boost applied)
                else
                {
                    cstate.cBoost = 0;
                }
            }
            // otherwise set boost state 0
            else
            {
                cstate.cBoost = 0;
            }
        }
    }

    // if boost state 1, reset the boost counter
    if (cstate.cBoost == 1)
    {
        cstate.nBoostCount = 0;
    }
    //TFS:3520, TFS:3596 -- separate terms P, D and Boost
    ctltrace.m_boostTerm = (lVal - ctltrace.m_pTerm) - ctltrace.m_dTerm; //get Boost term for debug
    return lVal;
}

/*
     DZ: 8/22/06
    \brief This function is internally called to set position error flag FAULT_POSITION_ERROR.
     If the option is selected and if position error exceeds user configured limit for
     user specified time T1, the flag will set.  After the flag is set, if position error
     decreases, the flag is reset.

    \param[in] data: a pointer to the data structure that holds position limits

*/
/* -------------------------------------------------------- */
/* This function increments counters and checks valve position */
static void control_SetPositionErrorFlag(const ctlExtData_t *data)
{
    s16 nDiff,                          // additonal error tolerance if at/near stops
        nGap;                           // locally computed/limited position error

    /* determine working positon error as actual error or as limited by stops */
    if(m_n2CSigPos < 0)
    {
        nDiff = (s16)m_n4PositionScaled;
    }
    else if(m_n2CSigPos > (data->m_pCPS->ExtraPosHigh + THREE_PCT_491) )
    {
        nDiff = (s16)( (data->m_pCPS->ExtraPosHigh + THREE_PCT_491) - m_n4PositionScaled);
    }
    else
    {
        nDiff = m_PosErr.err;
    }
    // absolute value of error(limited at/by stops)
    nDiff = (s16)ABS((s32)nDiff);


    // set nGap to min (nDiff,  m_PosErr.err_abs)
    if (nDiff > m_PosErr.err_abs)
    {
        nGap = m_PosErr.err_abs;
    }
    else
    {
        nGap = nDiff;
    }

    // if position near or at stops set nDiff to 1 percent , otherwise 0
    if( (m_n4PositionScaled < (data->m_pCPS->ExtraPosLow+ONE_PCT_164) ) ||
           (m_n4PositionScaled > data->m_pCPS->ExtraPosHigh) )
    {
        nDiff = ONE_PCT_164;
    }
    else
    {
        nDiff = 0;
    }

    // if position is OK, clear the error count, reset the fault and exit
    if( nGap < (data->m_pComputedErrorLimits->PositionErrorBand + nDiff))
    {/*no error*/
        cstate.nErrorCount = 0;
        error_ClearFault(FAULT_POSITION_ERROR);            /*reset warning*/
        return;                                     // early return
    }

    // position error exists, increase the successive error count unless it is at max
    if(cstate.nErrorCount < ERR_COUNT_MAX)
    {
        cstate.nErrorCount += 1;
    }

    // if position error monitoring is enabled ...
    if(data->m_pComputedErrorLimits->bPosErr1Enable == 1)
    {
        // allow more time when valve comes out of seat or from possible fully open situation
        if( (m_n4PositionScaled < (data->m_pCPS->ExtraPosLow+ONE_PCT_164)) ||
            (m_n4PositionScaled > (data->m_pCPS->ExtraPosHigh-ONE_PCT_164)) )
        {
            nDiff = STANDARD_RANGE/(m_PosErr.err_abs+2);
        }
        else
        {
            nDiff = 0;
        }

        // if error count at or above threshold, set the fault
        if(cstate.nErrorCount > (data->m_pComputedErrorLimits->PositionTime1 + nDiff) )
        {

            error_SetFault(FAULT_POSITION_ERROR);          /* set warning fault */
            /*
            if( (data->m_pComputedErrorLimits->bPosErr2Enable == 1) &&
                (nErrorCount > (data->m_pComputedErrorLimits->nPositionTime2+nDiff )) )
            {
                error_SetFault(FAULT_POSITION_ERROR_FAIL);
                nErrorCount = 0;
            } */
        }
    }
}



// end  Stolen from ESD



/**
     DZ: 8/22/06
    \brief This function is internally called to calculate integral control when m_bIControl is set.
     The integral control is nonlinear.  Less integral control for low temperature.
     Note: This function is not called if the valve is considered to be moving

    \param[in] data - a pointer to the data structure that holds Control parameters
*/


static void Integral_Control(const ctlExtData_t *data)
{
   //note:  if error is large or small, don't apply too much integral
   //       in the middle, apply more integral
    s16 nCalcFreq,              //number of cycles to skip until doing integral
        nLimit,
        nTinC;
    s32 lVal, pVal;
    bool_t integral_stopped;
    Bias_t out_I;                  // computed output value added to bias

    cstate.i_count++;                  // count of control cycles since last computed integral

/// AK:Q: Explain the nCalcFreq calculations. Theory? Tricks?
    // DZ: Using varying nCalcFreq to achieve nonlinear integral control.
    // basically, applying more integral on position errors not too small not too large.

    //determine how often to do integral (bias) adjustment
    nCalcFreq = I_CALC_MID;                 // default speed is relatively slow

    // integral relatively slow if error is large (> 3 percent)
    if( m_PosErr.err_abs > THREE_PCT_491)
    {
        nCalcFreq = I_CALC_MID;
    }
    // intgral is faster if error is below 3% but above .3 %
    else if(m_PosErr.err_abs > PT3_PCT_49)
    {
        //increase the rate of integral action in the error range
        //to correct the bias faster
        //filling both single and double acting
        if( (m_PosErr.err8 > PT3_PCT_49) &&
               (m_PosErr.err > (m_PosErr.err8 + PT1_PCT_16) ))
        {
                nCalcFreq = (I_CALC_LOW/2);     // relatively fast
        }
        // double acting only
        else if (data->pPneumaticParams->SingleActing == 0)
        {
           // exhausting
           if( (m_PosErr.err8 < -PT3_PCT_49) &&
                (m_PosErr.err < (m_PosErr.err8 - PT1_PCT_16) ))
           {
                nCalcFreq = (I_CALC_LOW/2);     // relatively fast
           }
        }
        else
        {
            // take the default of I_CALC_MID
        }
    }
    // integral is half of the 3% to .3% speed error is below .3% but above .15%
    else if(((s32)m_PosErr.err_abs > PT15_PCT_24) && (ABS((s32)m_PosErr.err7) > (s32)PT15_PCT_24) )
    {
        nCalcFreq = I_CALC_LOW;     // moderate speed
    }
    else
    {
        // take the default of I_CALC_MID - relatively slow
    }

    // if tight shut/cut off configured and position near a stop, select moderate speed
    //TFS:9578  EXPANDED TO TIGHT OPEN AND FULL OPEN/CLOSE
    if ( (data->ControlLimits->EnableTightShutoff[Xlow] != 0) ||
         (data->ControlLimits->EnableTightShutoff[Xhi] != 0 ) )
    {
        if( m_n4PositionScaled < (data->m_pCPS->ExtraPosLow+TWO_PCT_328))
        {
            nCalcFreq = I_CALC_LOW;
        }
    }
    // otherwise, if at upper or lower stop
    else if( m_nPosAtStops > NOT_STOP_0 )
    {
        nCalcFreq = (I_CALC_LOW*2);     // relatively slow
    }

    // if not tight shutoff or at stop, increase interval (decrease frequency) based on I value
    else if (data->m_pPID->I > I_HIGH_ZONE) // near max I
    {
        nCalcFreq *= 3;
    }
    else if (data->m_pPID->I > I_LOW_ZONE)
    {
        nCalcFreq *= 2;
    }
    else  // for MISRA
    {
        //Don't modify
    }

    // if interval elapsed, calculate integral action
    if (cstate.i_count >= nCalcFreq)
    {
        cstate.i_count = 0;                    // reset for next interval

        // Criterion that set output_limited stop the integral from running
        // and set the m_bActuatorAtLim making a integral reset possible
        integral_stopped = false;
        // treat no I/P current and Pneumatic saturation the same
        if (sysio_CheckIPDisconnect())
        {
            integral_stopped = true;
        }
        /*Note this is split up because isOutputAtLimit has side effects*/
        /*For instance it can return false but set m_bActuatorAtLim*/
        if (isOutputAtLimit(data))
        {
            integral_stopped = true;
        }
        if ((integral_stopped == true) || (cstate.isBiasLowerLimited == true) || (cstate.isBiasUpperLimited == true))
        {
            //Check if we were previously not stopped
            if (!cstate.Integral_Previously_Limited)
            {
              cstate.Integral_First_Stopped = timer_GetTicks();
              cstate.Integral_Previously_Limited = true;
            }
            else
            {
                // Note this would be the natural place to check
                // the elapsed time and calculate the reset flag
                // if this function ran regularly.  Since it does
                // not we should not calculate elapsed time here.
                // This is instead done in the function that performs
                // the reset.  Thus, the timing is guaranteed to be
                // as good as the timing for performing the reset.
            }
        }
        else
        {
            cstate.Integral_Previously_Limited = false;
        }
        // Criterion added here just stop the integral from running
        // They don't enable the reset logic m_bActuatorAtLim
        if (integral_stopped)
        {
            //Don't run the integral
        }
        else
        {
            //Note m_bActuatorAtLim cannot be cleared here since it is only
            //cleared by overshoot
            error_ClearFault(FAULT_ACTUATOR);
            // Base contribution of the integral
            //lVal = (m_n2Err_p*(s16)data->m_pPID->P)/(I_CALC_COEF*(s16)data->m_pPID->I); /// AK:NOTE: The scaler can be precomputed once.
            //3401 Incorporate changes from 3.2.1 -- From RC3 -- TFS 3310
            if (data->m_pPID->I == 0)
            {
                //REQ 35-10 make integral value zero if I is zero
                //this is the behavior of the 4.2 compiler that was changed in 5.4
                lVal = 0;
            }
            else
            {
                s16_least Pcoef = (s16_least)data->m_pPID->P;
                if(IS_EXHAUSTING())
                {
                    Pcoef += data->m_pPID->PAdjust;
                }
                lVal = (m_n2Err_p*Pcoef)/(I_CALC_COEF*(s16)data->m_pPID->I); /// AK:NOTE: The scaler can be precomputed once.
            }

            // Adjustment of the integral contribution: at low temperature less integral control.
            if ( (lVal > 2) || (lVal < -2) )
            {
                 // get the temperature in degrees C
                 nTinC = tempr_GetInstantTempr(TEMPR_MAINBOARD)/100;

                 // if temperature below -22, reduce integral as a function of temperature
                 if(nTinC < (T_LOW-2) )                         // T_LOW is -20 C
                 {
                     lVal /= (T_LOW-nTinC); /// AK:Q: Explanation needed! [Units mismatch, mA vs. mA/DegC]?
                    // DZ: T in C, lVal is std range of 0-65K
                 }
            }
            // if setpoint is at or beyond the stops range, reduce the integral value
            // can this happen?  IsIControl may prevent us from being here??
            if(  (m_n2CSigPos < data->m_pCPS->ExtraPosLow)  ||
                (m_n2CSigPos > data->m_pCPS->ExtraPosHigh) )
            {
                if (lVal < 0)
                {
                    lVal /= 4;
                }
                else
                {
                    lVal /= 2;
                }
            }
            // otherwise, if still in startup mode, double the integral value
            else if( cstate.start_count < (START_COUNT_MAX-2))
            {
                lVal *= 2;
            }
            else
            {
                //Don't modify
            }

            // make sure the integral increment amount is not too big
            // choose limits based on proximity to stops or whether in startup mode
            if( (m_nPosAtStops > NOT_STOP_0) || (cstate.start_count > (START_COUNT_MAX-2) ) )
            {
                nLimit = I_LIMIT_AT_STOP;  // =100
            }
            // not at stop and still in startup mode
            else
            {
                nLimit = I_LIMIT_NOT_STOP;  // 500
            }

            // NLIMIT Calc -- do not remove this comment
            // now limit integral value based on proximity to stops and/or startup mode
            // do NOT change these limits without revisiting the code for
            // marked NLIMIT_DEPENDENT below

            if(lVal > nLimit)
            {
                out_I = nLimit;
            }
            else if(lVal < -nLimit)
            {
                out_I = -nLimit;
            }
            else
            {
                // if any significant lVal, ouput becomes lVal
                if( ABS(lVal) > 1)
                {
                    out_I = (s16)lVal;
                }

                // otherwise, if lVal is -1 .. 1 and PID->I is not large, choose small integral value based on error
                else if(data->m_pPID->I < I_HIGH_ZONE)
                {
                    if((m_PosErr.err > ERR_S) && (m_PosErr.err8 > ERR_S))
                    {
                        out_I = 2;
                    }
                    else if((m_PosErr.err > (ERR_S/2)) && (m_PosErr.err8 > (ERR_S/2)))
                    {
                        out_I = 1;
                    }
                    else if((m_PosErr.err < -ERR_S) && (m_PosErr.err8 < -ERR_S))
                    {
                        out_I = -2;
                    }
                    else if( (m_PosErr.err < -(ERR_S/2)) && (m_PosErr.err8 < -(ERR_S/2)) )
                    {
                        out_I = -1;
                    }
                    else  // for MISRA
                    {
                        out_I = (s16)lVal;
                    }
                }
                else  // for MISRA
                {
                    out_I = 0;
                }
            }

            // if in marginal power, limit out_I - local anti-windup
            if ( (data->OutputLim < MAX_DA_VALUE) && (out_I>0)  ) /// AK:NOTE: The 1st < is testing marginal power condition
            {
                if (sysio_CtlOut2PWMdomain(PIDOut) >= data->OutputLim)    /** TFS:5698 **/
                {
                    out_I = 0;
                }
                else if ( (m_bATO==false) && (out_I > 8) ) /// AK:NOTE: Both "8" are now named OUT_I_LOW
                {
                    out_I /= 8; /// AK:Q: Explain?
                    // DZ: ???
                }
                else
                {
                    //don't adjust
                }
            }

            // out_I is the final contribution of Integral at this moment
            // compute new bias value
            lVal = m_BiasData.BIAS;
            pVal = m_BiasData.BIAS + out_I;
            cstate.isBiasUpperLimited = false;
            cstate.isBiasLowerLimited = false;

            Bias_t newBIAS;
            // limit new bias value
            if(pVal > (BIAS_HIGH_LIMIT - cstate.LastComputedPosComp))
            {
                newBIAS = BIAS_HIGH_LIMIT - cstate.LastComputedPosComp;
                cstate.isBiasUpperLimited = true;
                // this allows us to integrate away from the limit
                if (out_I < 0 )
                {
                    // NLIMIT_DEPENDENT
                    //note abs(out_I )<500 so we don't have to check this against limits
                    //also the code for checking it is remarkably complex however if
                    //change the code marked NLIMIT Calc we must revisit this
                    newBIAS = newBIAS + out_I;
                }
            }
            else if(pVal < (BIAS_LOW_LIMIT - cstate.LastComputedPosComp))
            {
                newBIAS = BIAS_LOW_LIMIT - cstate.LastComputedPosComp;
                cstate.isBiasLowerLimited = true;
                // this allows us to integrate away from the limit
                if (out_I > 0 )
                {
                    // NLIMIT_DEPENDENT
                    //note abs(out_I )<500 so we don't have to check this against limits
                    //also the code for checking it is remarkably complex however if
                    //change the code marked NLIMIT Calc we must revisit this
                    newBIAS = newBIAS + out_I;
                }
            }
            else
            {
                newBIAS = pVal;
               //**** may need to be limited - look in air loss handler to see if it is limited

            }
            storeMemberInt(&m_BiasData, BIAS, newBIAS);
            s32 newIntegral = m_BiasData.m_Integral - (lVal - m_BiasData.BIAS);
            storeMemberInt(&m_BiasData, m_Integral, newIntegral);
        }
    }
#if (CONTROL_CHECKSUM_PROTECT & CONTROL_INTEGRAL_TEST_INTERLEAVE) != 0
    else
    {
        testIntegralState();
    }
#endif
    ctltrace.m_diagCalcPeriod = nCalcFreq;
}

/**
     DZ: 8/22/06
    \brief This function is internally called each cycle to prepare for control. This is called before
      control_PID(data) is called
     When the counter start_count == 0, manual setpoint m_n4ManualPos is initialized to valve position.
     Hard stop positions are initialized.
    m_bRegularControl and setpoint m_n4Setpoint are determined in this function.

    \param[in] data: a pointer to the data structure that holds position limits
*/
static bool_t control_Prepare(const ctlExtData_t *data)
{

    if(data->OutputLim <= MIN_DA_VALUE)
    {
        control_ResetRateLimitsLogic();
    }
    control_RateLimitsGuard();

    cstate.m_n1ControlMode = mode_GetEffectiveControlMode(&m_n4Setpoint);
    // if first time after reset, establish some initial conditions
    if (cstate.start_count == 0)
    {
        /* startup */
        cstate.m_n2CSigPos_p = m_bATO ? 0 : (data->m_pCPS->ExtraPosHigh + THREE_PCT_491);
        cstate.start_count++;
    }

    bool_t m_bRegularControl = control_IsModeClosedLoop(cstate.m_n1ControlMode);
    if(m_bRegularControl)
    {
        calcSP_Err(data);
    }
    if(data->OutputLim <= MIN_DA_VALUE)
    {
        m_bRegularControl = false;
    }

    bool_t m_bShutZone = cutoff_Eval(m_bRegularControl); //NOTE: If in cutoff, writes output directly

    if(m_bShutZone)
    {
        m_bRegularControl = false;
    }
    cstate.m_bShutZone = m_bShutZone; //need for output control for now

	if(m_bRegularControl && !cstate.m_bRegularControl)
	{
		//Entering closed-loop for the first time
        control_EnterClosedLoop(data);
	}
    cstate.m_bRegularControl = m_bRegularControl;
    if(!m_bRegularControl)
    {
            cstate.i_count = 0;                    // reset integral interval counter
    }
    return m_bRegularControl;
}

/* -------------------------------------------------------- */

/**
     DZ: 8/22/06
    \brief This function is internally called to update the time counter for Time closed,
     time open, time near closed counters, part of continuous diagnosis data.

    \param[in] nGap - noise estimation used to determine if valve is closed.
*/

static void increments(s32 nGap)
{
    Diagnos_t ValvePosition;
    ContinuousDiagnostics_t cd;

    // incrementation every second  -  ~248 days before counters overflow
    if( timer_GetTicksSince(nDiagTime) >= T1_000)
    {
        nDiagTime += T1_000;
        cd = m_ContinuousDiagnostics;

        // determine position of valve for statistics purposes
        if(m_n4PositionScaled <= (nGap/2))
        {
            ValvePosition = CLOSED;
        }
        else if(m_n4PositionScaled < pos_GetErrorLimits(NULL)->NearPosition)
        {
            ValvePosition = NEAR;
        }
        else
        {
            ValvePosition = OPEN;
        }

        // increment the appropriate counter based on valve position
        if(ValvePosition == CLOSED)
        {
            cd.TimeClosedCntr += TIME_INCREMENT;
        }
        else if(ValvePosition == NEAR)
        {
            cd.TimeNearCntr += TIME_INCREMENT;
            cd.TimeOpenCntr += TIME_INCREMENT;
        }
        else
        {
            cd.TimeOpenCntr += TIME_INCREMENT;
        }
        // compute new guard value for the RAM structure
       STRUCT_CLOSE(ContinuousDiagnostics_t, &cd);

        MN_ENTER_CRITICAL();
            m_ContinuousDiagnostics = cd;
        MN_EXIT_CRITICAL();

        //save the whole thing every hour
        if(++lets_save >= ONE_HOUR_3600)
        {
            ErrorCode_t err = ram2nvramAtomic(NVRAMID_ContinuousDiagnostics);
            if(err == ERR_OK)
            {
                lets_save = 0;
            }
            else
            {
                //try next time
            }
        }
    }
}

/**
     DZ: 8/22/06
    \brief This function is externally called to update valve continuous diagnosis data.
    It accumulates data for valve travel (strokes), cycles, Time closed,
     time open, time near closed counters.

    Also, monitors and clears FAULT_BIAS_OUT_OF_RANGE
*/
void control_ContinuousDiagnostics(void)
{
    pos_least_t ndiff, nGap;

    //first time through, initialize m_n4PositionScaled_1 to the current position
        /* Intermediate Calculations for Counters */

        // change since last movement
    pos_least_t PositionScaled = m_n4PositionScaled; //take a snapshot

    ndiff = ABS(PositionScaled - m_n4PositionScaled_1);

        /// AK:Q: Should nPosShift in airloss_handle() be exactly the same as nGap? (See also questions there)
        // DZ: Not necessary for flexibility for different cases.

        // compute noise threshold to determine if valve has moved
    nGap = (NOISE_RATIO*UINT16_MAX)/m_n2PosRange; //AK: change of order is a better resolution
    nGap = nGap + (NOISE/2);

    // if has moved
    if(ndiff > nGap)     /* noise level */
    {
        /* Travel Accumulator */
        m_nTravelAccum += ndiff;

        /* Valve cycles Counter */
        bool_t direction = m_n4PositionScaled < m_n4PositionScaled_1; //true if down
        if( !equiv(direction, m_nDirection))
        {
            m_ContinuousDiagnostics.CyclesCntr += 1u;
            m_nDirection = direction;
        }

        // new value for last movement
        m_n4PositionScaled_1 = PositionScaled;
    }
    /* Valve Travel */
    // if cumulative travel is full stroke or more, count a stroke
    if(m_nTravelAccum >= STANDARD_RANGE)     /* equal to full close to full opening = 16384 */
    {
        m_ContinuousDiagnostics.TotalTravelCntr += 1u;
        m_nTravelAccum -= STANDARD_RANGE;
    }

    /* Time Counter incrementation (this doesn't rely on m_n4PositionScaled_1) */
    increments(nGap);

    //see if we can clear the bias alarms
    Bias_t steady_state_output = m_BiasData.BIAS + cstate.LastComputedPosComp;
    if( (steady_state_output < BIAS_ALARM_LOW_LIMIT) || (steady_state_output > BIAS_ALARM_HIGH_LIMIT))
    {
        error_SetFault(FAULT_BIAS_OUT_OF_RANGE);
    }
    else
    {
        error_ClearFault(FAULT_BIAS_OUT_OF_RANGE);
    }
}

/**
     DZ: 8/22/06
    \brief This function is externally called to get valve continuous diagnostic data.
    It returns a pointer to the m_ContinuousDiagnostics structure.
     *pContinuousDiagnositcs = m_ContinuousDiagnostics;

*/
const ContinuousDiagnostics_t* posmon_GetContinuousDiagnostics(ContinuousDiagnostics_t *dst)
{
    return STRUCT_GET(&m_ContinuousDiagnostics, dst);
}


/**
    DZ: 8/22/06
    \brief This function is externally called to initialize data for valve continuous diagnosis.
*/
static void control_InitContinuousDiagnostics(void)
{
    m_nDirection = false; //meaning up by default
    /* time_lowpwr = (u16)bios_GetTimer0Ticker(); */
    m_n4PositionScaled_1 = m_n4PositionScaled; //begin new life
}


ErrorCode_t posmon_SetContinuousDiagnostics(const ContinuousDiagnostics_t *src)
{
    if(src == NULL)
    {
        src = &def_ContinuousDiagnostics;
    }
    else
    {
        //we re not supposed to set to something while running
        MN_ASSERT(!oswrap_IsOSRunning());
    }
    MN_ENTER_CRITICAL();
        Struct_Copy(ContinuousDiagnostics_t, &m_ContinuousDiagnostics, src);
        control_InitContinuousDiagnostics();
        nDiagTime = timer_GetTicks(); //but don't reset time_lowpwr!
        m_nTravelAccum = 0; //but don't touch m_nDirection
    MN_EXIT_CRITICAL();

#ifdef OLD_NVRAM
    /* write the data to fram */
    control_SaveContinuousDiagnostics();
    return ERR_OK;
#else
    return ram2nvramAtomic(NVRAMID_ContinuousDiagnostics);
#endif //OLD_NVRAM
}

#ifdef OLD_NVRAM
/**
     DZ: 8/22/06
    \brief This function is externally called to save valve continuous diagnosis data in RAM to NVRAM.
*/
static void  control_SaveContinuousDiagnostics(void)
{
    /** get sole use of FRAM */
    MN_FRAM_ACQUIRE();

        /** write the data to fram and release fram */
        ram2nvram((void*)&m_ContinuousDiagnostics, NVRAMID_ContinuousDiagnostics);

    MN_FRAM_RELEASE();
}
#endif //OLD_NVRAM

/**
     DZ: 8/22/06
    \brief This function is externally called to get valve position errors.
    Used by atune.c
*/
const PosErr_t*  control_GetPosErr(void)
{
    return &m_PosErr;
}

/**
     DZ: 8/22/06
    \breif This function is externally called to check if bias is shifted.
    If bias shift exceeds a predefined limit, bias will be saved in NVRAM.
*/
void control_CheckSaveBias(void)
{
    //In case we need them in the critical section, precompute
    s16_least nTinC = tempr_GetInstantTempr(TEMPR_MAINBOARD)/100;       // compute temperature in degrees C
#if USE_BIAS_TEMPR_ADJ_T_LOW_T_HIGH //as in David's initialization
    // limit the temperature to -20 .. +70 degrees C
    nTinC = CLAMP(nTinC, T_LOW, T_HIGH);
#else //as in David's save
    // if temperature is less than 25 C, scale the bias
    nTinC = MIN(nTinC, T_BASE);
#endif
    s16_least nTemp = (s16_least)(m_BiasExt.nBiasTempCoef*(T_BASE-nTinC));
    Bias_t uiBiasNew = (s32)ictest.BiasAvgAtBase + nTemp;

    Struct_Test(BiasExt_t, &m_BiasExt);

    bool_t save = false; //do we really want to crawl the bias?

    /* We don't care to check valve conditions: All we do is a deferred write of
    previosly captured bias.
    */
    if (ictest.m_bSaveBias)
    {
        // need a time-coherent snapshot - this code runs in Process context
        MN_ENTER_CRITICAL();

            storeMemberBool(&ictest, m_bSaveBias, false);


            // if computed (scaled) bias is significantly different from saved bias,
            //  change bias structure and set the save flag
            if( (m_NVMEMBiasData.BiasSaved > (uiBiasNew + m_BiasExt.uiBiasShift) ) ||
                (m_NVMEMBiasData.BiasSaved < (uiBiasNew - m_BiasExt.uiBiasShift) ) )
            {   /* Test the Bias drift since the last record */

                /* Reject outlandish biases
                */
                //Bias_t steady_state_output = uiBiasNew + ictest.poscomp; //at the time of save
                if( (uiBiasNew < BIAS_LOW_LIMIT) || (uiBiasNew > BIAS_HIGH_LIMIT) )
                {
                    ctltrace.BiasesRejected++;
                }
                else
                {
                    storeMemberInt(&m_NVMEMBiasData, BiasSaved, (u16)uiBiasNew);
                    save = true;
                }
            }
        MN_EXIT_CRITICAL();
    }

    // if the save flag was set above, save the bias to FRAM now
    if(save)
    {
        (void)ram2nvramAtomic(NVRAMID_BiasData);
        ctltrace.BiasesSaved++;
    }
}

/** \brief Completes reset initialization using previous system init
    including NVMEM data and input variables (A/D) which must be prepared (Verify!)
*/
static void control_PostInit(const ctlExtData_t *data)
{
    // Compute the intitial bias based on the value saved in FRAM

    // compute the current board temperature
    tempr_fast_t nTinC = tempr_GetInstantTempr(TEMPR_MAINBOARD)/100;       // compute temperature in degrees C
#if USE_BIAS_TEMPR_ADJ_T_LOW_T_HIGH //as in David's initialization
    // limit the temperature to -20 .. +70 degrees C
    nTinC = CLAMP(nTinC, T_LOW, T_HIGH);
#else //as in David's save
    // if temperature is less than 25 C, scale the bias
    nTinC = MIN(nTinC, T_BASE);
#endif

    // compute bias adjustment from coefficient and limited board temperature
    Bias_t nTemp = (m_BiasExt.nBiasTempCoef*(T_BASE-nTinC));

    /* if not warmstart (in-place reset) deduct [500] from the adjustment
         this is to prevent unwanted opening of the valve on startup.
        The "opening" assumes ATO, else it is closing and we don't what this.
    */
    if (!reset_IsWarmstart())
    {
        if(m_bATO)
        {
            nTemp -= m_BiasExt.nBiasAdd;   //nBiasAdd=-500
        }
    }

    // limit the bias adjustment value
    nTemp = CLAMP(nTemp, BIAS_CHANGE_LO, BIAS_CHANGE_HI);

    Bias_t bias = (Bias_t)m_NVMEMBiasData.BiasSaved;

    // if the saved value is out of range, use the default
    if( (bias < (BIAS_LOW_LIMIT + BIAS_MARGIN_LO)) ||
        (bias > (BIAS_HIGH_LIMIT - BIAS_MARGIN_HI)) )
    {
        bias = BIAS_DEFAULT;
    }

    if( bias > (BIAS_LOW_LIMIT + nTemp) )
    {
        bias = bias - nTemp;
    }
	//TODO: more likely that bias = MAX(BIAS_LOW_LIMIT, bias - nTemp; was intended

    m_BiasData.BIAS = bias;
    ictest.BiasAvgAtBase = bias;
    PIDOut = ictest.BiasAvgAtBase;
    cstate.BiasChangeFlag = 0;
    // finished adjusting the bias

    cstate.start_count = 0;

    STRUCT_CLOSE(ControlState_t, &cstate);
    STRUCT_CLOSE(InControlTest_t, &ictest);
    STRUCT_CLOSE(BiasData_t, &m_NVMEMBiasData);

    STRUCT_CLOSE(IntegralState_t, &m_BiasData);

    /* Here is the stuff that logically doesn't belong here
    but is needed because of criss-cross module interfaces
    */
    m_n4PositionScaled = vpos_GetScaledPosition();
    m_n4Setpoint = m_n4PositionScaled; //init setpoint; OK to overwrite
    cstate.m_n2CSigPos_p = m_bATO ? 0 : (data->m_pCPS->ExtraPosHigh + THREE_PCT_491); //David's value

    control_EnterClosedLoop(data);

    bias += cstate.LastComputedPosComp; //steady-state output init
    PIDOut = (u16)CLAMP(bias, 0, UINT16_MAX);
}


const BiasData_t *control_GetNVMEMBiasData(BiasData_t* dst)
{
    return STRUCT_GET(&m_NVMEMBiasData, dst);
}

//Was control_SetBiasData removed at ver. 194; resurrecting.
/**
     DZ: 8/22/06
    \brief This function is externally called to set bias data and write to NVRAM.
     parameters description:

    param[in] pBiasData: the pointer to bias data structure
*/
ErrorCode_t control_SetNVMEMBiasData(const BiasData_t* pBiasData)
{
    MN_ASSERT(!oswrap_IsOSRunning()); //Allowed at init only!
    if(pBiasData == NULL)
    {
        pBiasData = &def_BiasData;
    }

#if 0 //control handles it all in RunOnce
    /** validate the input */
    if( (pBiasData->BiasSaved < (u16)BIAS_LOW_LIMIT)  ||
        (pBiasData->BiasSaved > (u16)BIAS_HIGH_LIMIT)  )
    {
        return ERR_INVALID_PARAMETER;
    }
#endif

    Struct_Copy(BiasData_t, &m_NVMEMBiasData, pBiasData);

#ifdef OLD_NVRAM
    /** get sole use of FRAM */
    MN_FRAM_ACQUIRE();
        // write the data to fram and release fram
        ram2nvram((void*)&m_NVMEMBiasData, NVRAMID_BiasData);

    MN_FRAM_RELEASE();
    //*/
    return ERR_OK;
#else
    return ram2nvramAtomic(NVRAMID_BiasData);
#endif //OLD_NVRAM
}

/**
     DZ: 8/22/06
    \brief This function is externally called to return a pointer to m_BiasExt.

    return BiasExt_t * pointer to extra bias data structure
*/
const BiasExt_t* control_GetFillBiasExt(BiasExt_t *dst)
{
    return STRUCT_GET(&m_BiasExt, dst);
}

/*
     DZ: 8/22/06
    \brief This function is externally called to set extra bias data and write it to NVRAM.

    \param[in] BiasExt_t* pBiasExt: the pointer to extra bias data structure
*/
ErrorCode_t control_SetBiasExt(const BiasExt_t* pBiasExt)
{
    if(pBiasExt == NULL)
    {
        pBiasExt = &def_BiasExt;
    }

    /** validate the input */
    if(   (pBiasExt->uiBiasShift > (u16)BIAS_HIGH_LIMIT)  )
    {
        return ERR_INVALID_PARAMETER;
    }

    Struct_Copy(BiasExt_t, &m_BiasExt, pBiasExt);              /** TFS:5698 **/

    return ram2nvramAtomic(NVRAMID_BiasExt);
}


/** \brief Common dumb routine to populate control stuff
Kinda dumb constructor
*/
static const ctlExtData_t *control_PopulateData(ctlExtData_t *data)
{
    data->ControlLimits = control_GetLimits(NULL);
    data->OutputLim = sysio_GetPWMHightLimit();
    data->m_pPID = tune_GetCurrentPIDData(NULL);
    data->m_pPositionStop = pos_GetPositionConf(NULL);
    data->pPneumaticParams = pneu_GetParams(NULL);
    data->m_pCPS = pos_GetComputedPositionConf(NULL);
    data->m_pComputedErrorLimits = pos_GetErrorLimits(NULL);
    return data;
}

/** \brief Finish initialization of all state variables
*/
void control_FirstRun(void)
{
    ctlExtData_t extdata;
    const ctlExtData_t *data = control_PopulateData(&extdata); //quickly for cut-n-paste uniformity

    //pwr_CalcLimits();
    control_PostInit(data);
    control_InitContinuousDiagnostics(); //AK: added
}

/**
     DZ: 8/22/06
    \brief This function is main function and externally called to run control.
     It gets raw data of signal, which is then temperature compensated and converted
    to the standard range.
     The signal level will be identified if it is normal (NORMAL_POWER) or
     low power (LOW_POWER) or marginal power (MARGINAL_POWER)
     Position measurement is read in and processed and converted to the standard range.
     Both signal and position data are smoothed due to its noise
     function control_Prepare(data) and control_PID(data) are called to execute PID control.
*/
void control_Control(void)
{

#if (CONTROL_CHECKSUM_PROTECT & CONTROL_CONTROL_STATE) != 0
    Struct_Test(ControlState_t, &cstate);
#endif
#if (CONTROL_CHECKSUM_PROTECT & CONTROL_INCONTROL_TEST) != 0
    Struct_Test(InControlTest_t, &ictest);
#endif
#if (CONTROL_CHECKSUM_PROTECT & CONTROL_INTEGRAL_TEST_INTERLEAVE) == 0
    testIntegralState();
#endif

    ctlExtData_t extdata;
    const ctlExtData_t *data = control_PopulateData(&extdata); //quickly for cut-n-paste uniformity

    checkAirPressure(data); /// AK:NOTE: Architecturally, this seems to belong to the owner of board pressures. Bias change flag should then look at the faults.

/// AK:NOTE: m_n2PosRange could be computed once on init (or when LowPositionStop changes); m_pPositionStop would not then be needed.
/// AK:NOTE: m_n2PosRange is never used directly; only in a denominator in 2 places; can be precomputed
/// AK:Q: Is u16 a sufficient container? What's the guarantee?
//  DZ: give me a practical example it is not sufficient.

    m_n2PosRange = (u16)mn_abs(data->m_pPositionStop->rangeval[Xhi] - data->m_pPositionStop->rangeval[Xlow]);

    // yet more working data
    m_bATO = data->m_pPositionStop->bATO;

    // get scaled (0 - 100 percent) position
    m_n4PositionScaled = vpos_GetScaledPosition();

    // prepare to call the PID algorithm
    bool_t m_bRegularControl = control_Prepare(data);

    //Call PID algorithm only in closed-loop control
    s32 lVal; //control output
    if ( m_bRegularControl )
    {
        // call the PID algorithm
        lVal = control_PID(data);
    }
    //Ugly!
    else
    {
        lVal = 0; //don't care
    }
    if(!cstate.m_bShutZone)
    {
        IPCurrent_StoreAndOutput(lVal, data->OutputLim);
    }
    else
    {
        /* cutoff_Eval() writes to the output directly. (Verify!)
        The reason is that cutoff doesn't change control mode, so
        IPCurrent_StoreAndOutput won't be able to figure it out
        */
    }

#if (CONTROL_CHECKSUM_PROTECT & CONTROL_CONTROL_STATE) != 0
    STRUCT_CLOSE(ControlState_t, &cstate);
#endif
#if (CONTROL_CHECKSUM_PROTECT & CONTROL_INCONTROL_TEST) != 0
    STRUCT_CLOSE(InControlTest_t, &ictest);
#endif
}


/**
    \brief returns the control output
    Note this would be IDENTICAL to pwm_GetValue in 3.2.1 and before
    but becomes different in SVi1000 with PWM normalization
    \return the control output
*/
Bias_t control_GetControlOutput(void)
{

    //m_CtlOutputValue
    //Set by
    //  IPCurrent_StoreAndOutput
    return(m_CtlOutputValue);
}


/** \brief Creates Bit Pack for use with Hart command

*/
static u16 CreateBitPack(void)
{
    u16 bitpack;
    //The bit pack created by isOutputAtLimit
    //this occupies the first 10(LAST_INTEGRAL_STATUS_BIT) bits
    bitpack = ctltrace.Integral_Limit_Status;
    //Shutoff zone
    bitpack += (((u8)cutoff_IsActive() & 1U)<< (LAST_INTEGRAL_STATUS_BIT+1));
    //IpCurrentLimit
    bitpack += (((u8)sysio_CheckIPDisconnect() & 1U) << (LAST_INTEGRAL_STATUS_BIT+2));
    //Actuator at limit
    bitpack += (((u8)cstate.m_bActuatorAtLim & 1U) << (LAST_INTEGRAL_STATUS_BIT+3));
    //Have we had any integral resets
    bitpack += (((u8)(ctltrace.Overshoots>0)        & 1U) << (LAST_INTEGRAL_STATUS_BIT+4));
    //Has the bias been saved
    bitpack += (((u8)(ctltrace.JigglesPassed>0)     & 1U) << (LAST_INTEGRAL_STATUS_BIT+5));
    return(bitpack);
}


/** \brief Set various control variables in the provided HART buffer
           Standard set 242
    This function is invoked from hart_ext_analysis.c
*/
static bool_t IsJiggling(void)
{
    bool_t retVal = false;

    if ( (ictest.m_n2SPOffset == JIGGLE_AMOUNT) || (ictest.m_n2SPOffset == -JIGGLE_AMOUNT) )
    {
        retVal = true;
    }
    return retVal;
} //-----  end of IsJiggling() ------


static u8 BuildControlByte(void)
{
    const bool_t bJigglningNow = IsJiggling();

    u8 ControlByte;

    ControlByte = (u8)cstate.m_bRegularControl & 0x1U;         //Regular Control
    ControlByte += ((u8)ctltrace.m_bIControl << 1) & 0x2U;       //Integral Control
#if USE_VALVE_MOVE_ESTIMATE
    ControlByte += ((u8)ctltrace.m_bValveMove << 2) & 0x4U;      //Moving
#endif
    ControlByte += ((u8)bJigglningNow << 3) & 0x8U;     //Jiggle On
    ControlByte += ((u8)1 << 4) & 0x10U;                /** TFS:6073 */  //overshooting removed -- always 1.
    return ControlByte;
} //-----  end of BuildControlByte() ------


static void GetMinMaxErr(s16 *pminErr, s16 *pmaxErr)
{
    s16 minErr;
    s16 maxErr;
    s16 errArr[9];

    MN_ENTER_CRITICAL();
        errArr[0] = m_PosErr.err;     errArr[1] = m_PosErr.err1;    errArr[2] = m_PosErr.err2;
        errArr[3] = m_PosErr.err3;    errArr[4] = m_PosErr.err4;    errArr[5] = m_PosErr.err5;
        errArr[6] = m_PosErr.err6;    errArr[7] = m_PosErr.err7;    errArr[8] = m_PosErr.err8;
    MN_EXIT_CRITICAL();

    if ( errArr[0] < errArr[1] )
    {
        minErr = errArr[0];
        maxErr = errArr[1];
    }
    else
    {
        minErr = errArr[1];
        maxErr = errArr[0];
    }

    for (u8_least i = 2U; i < NELEM(errArr); i++ )
    {
        if ( errArr[i] < minErr )
        {
            minErr = errArr[i];
        }
        if ( errArr[i] > maxErr )
        {
            maxErr = errArr[i];
        }
    }
    *pminErr = minErr;
    *pmaxErr = maxErr;
} //-----  end of GetMinMaxErr() ------


/** TFS:4761 */
void control_FillExtAnalysParams(ExtAnalysParams_t *extAnalysPar)
{
    GetMinMaxErr(&extAnalysPar->MinErr, &extAnalysPar->MaxErr); //min/max error of 8 historic errors and current err

    /** TFS:4016 **/  /** TFS:4226 */
    extAnalysPar->CtlOutput = (u16)m_CtlOutputValue;               //u16: Control prog calculated (not normalized) PWM value
    extAnalysPar->AvgErr = ictest.avgErr;                        //s16:
    extAnalysPar->PosComp = (u16)cstate.LastComputedPosComp;     //u16: PosComp
    //TFS:3520, TFS:3596 -- separate terms P, D and Boost
    extAnalysPar->P_term = (s16)ctltrace.m_pTerm;                  //s16: P-term of PID
    extAnalysPar->D_term = (s16)ctltrace.m_dTerm;                  //s16: D-term of PID
    extAnalysPar->Boost_term = (s16)ctltrace.m_boostTerm;          //s16: Boost-component of PID
    extAnalysPar->Fast_terms = (s16)ctltrace.m_IpCurr;             //s16: Total of all fast-acting (not integrating) components of PID
    //end TFS:4761
    extAnalysPar->Integral = (s32)m_BiasData.m_Integral;             //s32: Integral component
    extAnalysPar->Bias = (u16)m_BiasData.BIAS;            //u16: pure Bias (made u16 for LINT, because it is declared as u16)
    extAnalysPar->Overshoots = ctltrace.Overshoots;                //u16: number of overshoots (special meaning)
    extAnalysPar->JigglesPassed = ctltrace.JigglesPassed;          //u16: number of jiggles passed
    extAnalysPar->CalcPeriod = (u16)ctltrace.m_diagCalcPeriod;       //u16: frequency of adding Integral to Bias
    extAnalysPar->IntegalCount = cstate.i_count;                 //u8: cycles since last addition of Integral to Bias
    extAnalysPar->CtrlByte = BuildControlByte();              //u8: 1-byte Bit Pack of control params
    extAnalysPar->BitPack = CreateBitPack();              //u16: 2-byte Bit Pack
} //-----  end of control_FillExtAnalysParams() ------



/* This line marks the end of the source */
