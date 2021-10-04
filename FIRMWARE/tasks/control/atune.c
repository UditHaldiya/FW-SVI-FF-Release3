#define AK_test 0
#define AK_extract 0
/*
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file atune.c
    auto tune functions

    Comments include DZ knowledge [Base: SVI2AP Release1 (3.1.1)]

     CPU: Any

    OWNER: DZ

    \ingroup control
*/
#include "mnwrap.h"
#include "oswrap.h"
#include "mnassert.h"
#include "errcodes.h"
#include "ctllimits.h"
#include "devicemode.h" //for FaultCode
#include "diagnostics.h"
#include "nvram.h"
#include "faultpublic.h"
#include "process.h"
//#include "bios.h" //includes pwm.h as well
//added so we don't need bios and could remove possibility of pwm.h
#include "timer.h"
#include "timebase.h"
#include "control.h"
//#include "faultdef.h" //fault codes
#include "bufferhandler.h"
#include "selftune.h"
#include "numutils.h"
#include "devicemode.h"
#include "configure.h"

#include "valveutils.h"
#include "sysio.h"

//to display what we are doing
#include "uipublic.h"
#include "uistartnodes.h"

#include "pneumatics.h"

/*Note ifdef is allowed only for header guards and
  Including instrumentation include file, it should
  be avoided otherwise.  Instrumentation should define
  a variable or function in an instrumentation only file
  to avoid accidentally including instrumentation if
  the wrong coding pattern is used
*/
#ifdef OPTIONAL_TUNE_DIAG_FLAG
#include "tuneinstrumpriv.h" //should be last include for robustness
#else
#define OPTIONAL_TUNE_DIAG 0
#endif

static s16 Reason=0; //Reason of auto-tune failure

/** \brief An accessor to the completion code that probably
ought to be common across processes
\return tining completion code
*/
s16 tune_GetCompletionCode(void)
{
    return Reason;
}

static const PosErr_t* m_pPosErr;
static const diag_t* m_pDiagBuffer;

/** private defines */
#define BIAS_CHANGE_THRESH 500

#if OPTIONAL_TUNE_DIAG==1
//Arbitrary relaxed limits to allow tuning with non-normal slope and bias
  #define BIAS_LOWER_VALUE 1
  #define BIAS_UPPER_VALUE 55000 /// AK:NOTE:Changed to 40000 in ESD. Is it valid across the board?
#else
//original limits
  #define BIAS_LOWER_VALUE 12000
  #define BIAS_UPPER_VALUE 30000 /// AK:NOTE:Changed to 40000 in ESD. Is it valid across the board?
#endif

#define SPEED_HIHI 2000
#define SPEED_LOLO 200
#define SPEED_LOW 300
#define SPEED_MID 600
#define SPEED_SUBLOW 400
#define SPEED_SUBHIGH 1000
#define SPEED_HIGH 1500
#define SPEED_MIN 100

#define OUT_STEP_HIGH 2000
#define TUNE_MAX_TRIES 10 //was TUNE_TIME_LIMIT
#define TUNE_TRY_INITVAL 5 //was TUNE_TIME_START

// Tune failure "Reasons"
#define TUNE_RUNNING 100
#define FAIL_ACTUATION 31
#define FAIL_NVWRITE 32
#define FAIL_OPEN_LOOP 33
#define FAIL_P_TOO_SMALL 45
#define FAIL_PADJ_TOO_BIG 46
#define BIAS_OUT_RANGE 55
#define OVER_TIME_FILL 66
#define OVER_TIME_EXHA 77
#define PARAM_OUT_OF_RANGE 88

#define POS_STD_4_75 778
#define OUT_INI_SGL 80
#define OUT_INI_DBL 50
#define OUT_INC_L 10
#define OUT_INC_S 4
#define OUT_INC_R1 28
#define OUT_INC_R2 22
#define OUT_INC_R3 32


#define INI_VALUE 99

#define STEP_TIME 7u //seconds - time of the step test (legacy)
#define SAMPLE_RATE 20u //per second - number of samples/s (legacy)
#define FORTY_PCT        ((s32)((PERCENT_TO_SCALED_RANGE * 40.0F) + 0.5F))
#define SIXTY_PCT        ((s32)((PERCENT_TO_SCALED_RANGE * 60.0F) + 0.5F))
#define SIXTY_FOUR_PCT   ((s32)((PERCENT_TO_SCALED_RANGE * 64.0F) + 0.5F))
#define RAMPING_RATE1      ((s32)(PERCENT_TO_SCALED_RANGE/4.0F))
#define RAMPING_RATE2      ((s32)(PERCENT_TO_SCALED_RANGE/6.0F))
#define POS_ONE 40.0F
#define POS_TWO 45.0F
#define STEP_CHANGE_INDEX 13
#define DATA_PTS 100
#define AVERAGE_PTS 10
#define TEST_TIMES_LIMIT 8
#define MAX_TIMES_LIMIT 70
#define STABLE_TRY_NUM 40
#define INDEX1 10
#define INDEX2 30
#define T98_LO_LIMIT 4
#define P_MIN  6
#define P_NOT_LOW  15
CONST_ASSERT(P_NOT_LOW >= P_LOW_LIMIT);
#define P_NOT_HIGH  150
#define P_MID  500
#define I_MIN  10
#define I_BASE  50
#define I_MID  70
#define I_NOT_HIGH 200
#define D_MIN  12
#define D_NOT_LOW  30
#define BOOST_LOW  3
#define BETA_BASE  -4
#define T_RATIO_P  25
#define T_RATIO_TAU  6
#define Y_ADJ_RATE1  10
#define Y_ADJ_RATE2  20
#define OVERSHOOT_HIGH  25
#define OVERSHOOT_MID  8
#define OVERSHOOT_LOW  3
#define DEADTIME_LOW  30
#define DEADTIME_MAX  80 //in nominal 50-ms intervals
#define GAIN_MIN  5
#define GAIN_RATIO  34
#define P_GAIN_RATIO  62000u
#define P_INC_RATIO  10
#define PADJ_GAIN_RATIO  66000
#define PADJ_INC_RATIO  16
#define P_TAU_RATIO  150
#define D_P_RATIO 1200
//#define COMP_CONST 3276 //AK:TODO: (maybe) That's 20% of position range (should be 3277)

#define COUNT_3  3
#define COUNT_10  10
#define COUNT_20  20
#define COUNT_24  24
#define COUNT_30  30
#define COUNT_40  40
#define COUNT_80  80
#define COUNT_100 100

#define FIVE_PCT 5


static s16 nTuneArray[70];         /* buffer for tune calculation*/

static s16 nSCount; //U, nT_90=INI_VALUE, nT_90_p=INI_VALUE;

/** This enum serves several purposes
1. Distinguish between vent and fill
2. Display current case on the LCD
3. (Few states) at a previous run affect current decisions
*/
typedef enum TuneCase_t
{
    MOVE_DIR_LINE = 20,
    vent_slow_largeY = 21,
    vent_fast_largeY = 29,
    vent_notfast_smallY = 24,
    vent_large_negY = 26,
    vent_notslow_smallY = 23,
    vent_large_overshootAgain = 28,
    vent_large_overshoot = 22,
    vent_increased_negOvershoot = 27,
    tunecase_init = 0,
    fill_slow_largeY = 1,
    fill_fast_largeY = 16,
    fill_fast = 4,
    fill_fast_again = 3,
    fill_large_negY = 9,
    fill_largeD = 2,
    fill_large_neg_overshoot = 13,
    fill_large_neg_overshootAgain = 14,
    fill_large_overshoot_largeD = 5,
    fill_same_overshoot = 6,
    fill_overshoot_slow = 7,
    fill_overshoot_notslow = 8,
    fill_neg_overshoot = 10,
    fill_slow = 11,
    fill_slowAgain = 12,
    fill_success = 88,
    //AK: Added more states for completion indication
    tunecase_finished = 89,
    tunecase_failed = 44,
    tunecase_canceled = 90
} TuneCase_t;

static bool_t bLCRelay, bSingleActing;

//Handy shorthands
#define Xfill Xlow
#define Xvent Xhi

static s16 nTau_avg;

/** member data */
static PIDData_t       m_PIDData[NUM_POSCTL_PARAMSETS]; //!< PID parameters

static TuneData_t m_TuneData;

//ranges
#define SUPPLY_PRESSURE_LOW 20.0F
#define SUPPLY_PRESSURE_HIGH 150.0F //was 120.0F

const pres_t SupplyPressure_range[Xends] =
{
    [Xlow] = STD_FROM_PSI(SUPPLY_PRESSURE_LOW),
    [Xhi] = STD_FROM_PSI(SUPPLY_PRESSURE_HIGH),
};

/* -------------------------------------------------------- */
/* function prototypes */
static s32 tune_CloseLoop(u8_least index, PIDData_t *pid);
static s16 StepTest(s8 iDir, s16 nOutInc, u16 nBiasSave, s16 nSpeed[Xends], s16 nGain[Xends], s16 nTau[Xends], s16 poscomp[Xends]);
static s32 tune_Tune_Function(u8_least index, PIDData_t *pid);
static s32 tune_RampingTest(u8_least index, PIDData_t *pid);

typedef struct StepData_t
{
    pos_t Y_last;
    pos_t DY_min; // in %/cycle
    s16 nOvershoot;
    s16 nOvershoot2;
    s16 nOvershoot_p;
    s16 nT_90;
    s16 nT_90_p;
    bool_t bD_Large;
} StepData_t;


static void Data_Processing(const PIDData_t *pid, StepData_t *tune_xchange);
static TuneCase_t Para_Adjust(PIDData_t *pid, StepData_t *tune_xchange, TuneCase_t case_c);
static s8 CheckPosStablize(u8_least index, PIDData_t *pid);
static s8 tune_Stabilize(u8_least index, PIDData_t *pid);
static bool_t CheckStable(u8_least index, PIDData_t *pid);
static void tune_LimitPID(PIDData_t *pid);
static void tune_EstimatePara(PIDData_t *pid, const s16 nGain[Xends], s16 nTau[Xends]);
static s16 Change10Pct(s16 nValue, bool_t bIncrease);
static s16 Change20Pct(s16 nValue, bool_t bIncrease);

    static const PIDData_t  def_PIDData =
    {
        .P                = 100,
        .I                = 160,
        .D                = 20,
        .PAdjust          = 30,
        .Beta             = -2,
        //.Damping          = 0,
        .PosComp          = COMP_BASE, //was 13,  // 14 closed; 12 open
        .DeadZone         = 0,
        .Band             = 4,
        //.NonLin           = 0,
        //.Reserved1        = 0,
        //.Reason           = 0,
        CHECKFIELD_CLEAR()
    };

    static const TuneData_t  def_TuneData =
    {
        .SupplyPres_User  = STD_FROM_PSI(30.0),
        .n1TunePara1      = 0,
        .n1Level          = 0,
        CHECKFIELD_CLEAR()
    };


/** \brief PID parameters accessor
    Performs integrity test of the referenced data struct.
    NOTE: The API does not guarantee non-volatility of data pointed to or
    of the pointer itself (the latter happens to be true in implementation though).
    The user who cares must make a copy in a critical section.
    \return a pointer to const PID parameters
*/
const void *TypeUnsafe_tune_GetPIDData(u8_least index, void *dst)
{
    if(index >= NUM_POSCTL_PARAMSETS)
    {
        return NULL; //nothing to return
    }

    return STRUCT_TESTGET(&m_PIDData[index], dst);
}

/** \brief Sets the working copy of PID data

\param pPIDData - pointer to PID data to make available to the system
*/
static ErrorCode_t tune_SetRamPIDData(const PIDData_t *pPIDData, PIDData_t *dst)
{
    ErrorCode_t err;
    if(pPIDData == NULL)
    {
        pPIDData = &def_PIDData;
    }
    /** validate the input */
    s32 signedP = pPIDData->P; //promotion OK
    if(
       (signedP > P_HIGH_LIMIT) ||
        //(signedP < P_LOW_LIMIT) ||
        (pPIDData->I > I_HIGH_LIMIT) ||
        (pPIDData->D > D_HIGH_LIMIT) ||
        (pPIDData->PAdjust < PADJ_LOW_LIMIT)  ||
        (pPIDData->PAdjust > PADJ_HIGH_LIMIT) ||
        //((signedP + pPIDData->PAdjust) < P_LOW_LIMIT) ||
        ((signedP + pPIDData->PAdjust) < 0) ||
        (pPIDData->Beta < BETA_LOW_LIMIT)  ||
        (pPIDData->Beta > BETA_HIGH_LIMIT) ||
        (pPIDData->PosComp < PCOMP_LOW_LIMIT)  ||
        (pPIDData->PosComp > PCOMP_HIGH_LIMIT) ||
        (pPIDData->Band > BOOST_HIGH_LIMIT) ||
        (pPIDData->DeadZone > DEADZONE_HIGH_LIMIT) || (pPIDData->DeadZone < 0)
      )
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        Struct_Copy(PIDData_t, dst, pPIDData);
        err = ERR_OK;
    }
    return err;
}

/** \brief Validates and sets new PID parameters and recomputes the Computed (Extended) PID paramters.
On success, saves the new set to NVMEM.
\param pPIDData - pointer to const struct of requested PID parameters (maybe, with incorrect checksum)
\return an error code (ERR_OK on success)
*/
ErrorCode_t TypeUnsafe_tune_SetPIDData(u8_least index, const void *src)
{
    ErrorCode_t err;

    if(index >= NUM_POSCTL_PARAMSETS)
    {
        err = ERR_INVALID_PARAMETER; /* Legit. early return: prerequisite test before side effects */
    }
    else
    {
        err = tune_SetRamPIDData(src, &m_PIDData[index]);
    }
    if(err == ERR_OK)
    {
        if(oswrap_IsOSRunning()) //Otherwise slot is not yet initialized
        {
            if(index == posctl_GetCtlset(NULL)->slot)
            {
                //Fix up the working set
                ErrorCode_t e = tune_SetCurrentPIDData(src);
                MN_DBG_ASSERT(e == ERR_OK); //an error is purely a coding error
            }
        }
        err = ram2nvramAtomic(NVRAMID_PIDData+index);
    }

    return err;
}

/** \brief Tests if supplied tune data are acceptable.

\param[in] pTuneData - structure to look at
\return ERR_OK if acceptable, ERR_INVALID_PARAMETER otherwise
*/
static ErrorCode_t tune_TestTuneData(const TuneData_t* pTuneData)
{
    ErrorCode_t ret = ERR_OK;
    if( (pTuneData->n1Level < TUNE_LEVEL_LOW) || (pTuneData->n1Level > TUNE_LEVEL_HIGH) ) //AK:TODO: NULL test
    {
        ret = ERR_INVALID_PARAMETER;
    }
    return ret;
}

/** \brief Returns a pointer to const tune data structure
    Performs integrity test of the referenced data struct.
    NOTE: The API does not guarantee non-volatility of data pointed to or
    of the pointer itself (the latter happens to be true in implementation though).
    The user who cares must make a copy in a critical section.
AK:?(DZ note) currently only needed to update fSupplyPressure when pressure units change
    \return a pointer to the tune data structure
*/
const void *TypeUnsafe_tune_GetTuneData(void *dst)
{
    return STRUCT_TESTGET(&m_TuneData, dst);
}

/** \brief Sets the supplied tune data
\param[in] pTuneData - pointer to a const tune data struct, perhaps without the checksum computed
\return an error code (ERR_OK on success)
*/
ErrorCode_t    TypeUnsafe_tune_SetTuneData(const void *src)
{
    const TuneData_t* pTuneData = src;
    if(pTuneData == NULL)
    {
        pTuneData = &def_TuneData;
    }

    /** validate the input */
    if( tune_TestTuneData(pTuneData) != ERR_OK )
    {
        return ERR_INVALID_PARAMETER;
    }

    Struct_Copy(TuneData_t, &m_TuneData, pTuneData);
    return ram2nvramAtomic(NVRAMID_TuneData);
}

//When we set working PID from active slot, the slot's content must be available
CONST_ASSERT(NVRAMID_CtlSetSlot > NVRAMID_PIDData);
//We need working data in case we want to tentatively change the content, such as disable deadzone
static PIDData_t wrk_ctlset;

const PIDData_t *tune_GetWorkinPIDData(PIDData_t *dst)
{
    return STRUCT_TESTGET(&wrk_ctlset, dst);
}

ErrorCode_t tune_SetCurrentPIDData(const PIDData_t *src)
{
    return tune_SetRamPIDData(src, &wrk_ctlset);
}

/* ------------------------ Here the real thing begins -------------------------------- */

/** \brief A wrapper function for the self-tune process
The outline follows:
- check if it is allowd to run
- save the current PID data from the active slot and tune the active slot
- call tune_Tune_Function() for step 1 and step 2 of the 3-step auto-tuning process
- on success, run step 3 by calling tune_CloseLoop()
- on success of step 3, set new PID parameters in slot 0, restore active slot if it wasn't 0, and clear FAULT_AUTOTUNE_FAILED.
- on any step's or data setting failure, set FAULT_AUTOTUNE_FAILED and restore the original data.
- Finally indicate the process result to the local UI,  and restore the control mode.
NOTE: The function is responsible for cleaning up any mess the called functions create.
NOTE: Steps 1 and 2 (per DZ; I am not so sure of 2 - AK) are executed to provide a good initial guess for
step 3 in order for it to converge faster.
*/
procresult_t tune_Run_Selftune(s16 *procdetails)
{
    PIDData_t workpid; //working copy
#if OPTIONAL_TUNE_DIAG==1
    extDataAutoTune.Times[PID_PHASE_START] = timer_GetTicks();
    /*DIAG INIT*/
    /*Internal counters*/
    extDataAutoTune.gainRuns = 0;
    extDataAutoTune.step = 0;
    extDataAutoTune.RampLoops = 0;
    extDataAutoTune.openLoopTests = 0;
    extDataAutoTune.closedLoops = 0;

    u8 i;
    for (i=0; i<MAX_STEPS; i++)
    {
        /*Arrays*/
        extDataAutoTune.Times[i] = 0;
        extDataAutoTune.DeltaTime[i] = 0;
        extDataAutoTune.Delta[i] = 0;
        extDataAutoTune.Inc[i] = 0;
        extDataAutoTune.gainP[i] = 0;
    }
#endif

    u8_least index = posctl_GetCtlSetIndex();

    (void)tune_GetPIDData(index, &workpid);

#if AK_test
    workpid= def_PIDData;
#endif

    procresult_t nReturn = PROCRESULT_FAILED;

    //signal that we have started
    Reason = TUNE_RUNNING;

    /* Tune function to find BIAS, P, I & D coefficients PRELIMINARILY in Open loop tuning*/
    m_pPosErr = control_GetPosErr();

    ui_setNext(UINODEID_TUNE1);
    s8_least nRet = tune_Tune_Function(index, &workpid);
    if(nRet == 0)
    {
        ui_setNext(UINODEID_TUNE2);
        nRet = tune_RampingTest(index, &workpid);
    }

    if(nRet == 0)
    {   /* close loop test to adjust/fine-tune the parameters */
        ui_setNext(UINODEID_TUNE3);

#if !AK_test
        nRet = tune_CloseLoop(index, &workpid);
        if(nRet == 1)
#else
        UNUSED_OK(tune_CloseLoop);
#endif
        {
            nReturn = PROCRESULT_OK;
        }
    }

    //check for air loss
    bool_t AirFault = error_IsFault(FAULT_ACTUATOR)
        || error_IsFault(FAULT_AIR_SUPPLY_LOW);
    if(AirFault)
    {
        Reason = FAIL_ACTUATION;
        nReturn = PROCRESULT_FAILED; //we don't trust the results
    }

    if (nReturn == PROCRESULT_OK)
    {
        if(index == CTLPARAMSET_AUTOTUNE)
        {
            //Commit to home parameters and NVMEM
            ErrorCode_t e = tune_SetPIDData(index, &wrk_ctlset);
            if(e != ERR_OK)
            {
                if(e == ERR_INVALID_PARAMETER) //see tune_SetPIDData()
                {
                    Reason = PARAM_OUT_OF_RANGE;
                }
                else
                {
                    Reason = FAIL_NVWRITE;
                }
                nReturn = PROCRESULT_FAILED;
            }
        }
        /* If auto_tune failed or cancelled: restore working control set*/
        (void)tune_GetPIDData(index, &wrk_ctlset);
    }

    if( (nReturn != PROCRESULT_OK) || (index != CTLPARAMSET_AUTOTUNE))
    {
        //Restore the starting PID set
        (void)tune_GetPIDData(index, &wrk_ctlset);
    }

#if OPTIONAL_TUNE_DIAG==1
    extDataAutoTune.Times[PID_PHASE_END] = timer_GetTicks();
#endif

    //signal finished
    if(Reason == TUNE_RUNNING)
    {
        Reason = 0;
    }

    *procdetails = Reason;
    return nReturn;
}


static s16 tune_ComputePoscomp(pos_t posdiff, s16_least biasdiff)
{
    s16 poscomp;
    if (biasdiff != 0)
    {
        s16 n2Temp2 =  (s16)((biasdiff));
        poscomp = (s16)( posdiff + ((2*n2Temp2)/3) )/n2Temp2;
        //AK:NOTE n2Temp is COMP_CONST/n2Temp2 or 1+COMP_CONST/n2Temp2, depending on rounding luck
        //AK:TODO: Instead of const COMP_CONST=20%, it may be a better idea to use the difference
        //      of actually attained stable positions.
        //See MAX at the end - poscomp = ABS(poscomp);
    }
    else
    {
        poscomp = COMP_BASE;
    }
    return MAX(poscomp, 4);  //Why 4? What's the magic?
}

static s16 tune_AdjustPoscomp(bool_t SingleActing, s16 poscomp)
{
    if ( !SingleActing )
    {   // double acting
        if (poscomp > COMP_BASE)
        {
            //AK:TODO: Large PosComp is replaced in its function from a divisor to a shift counter (down from COMP_MAX).
            //      This overload is pathetic and needs weeding out ASAP, here and in control.c
            //AK:TODO: This stuff is based on preliminary guess of P (but not, remarkably, of PAdjust)
            //      and is never recomputed again. Does it make sense? What's the math of it? Need to understand.
            poscomp = MIN(poscomp, (COMP_BASE+3));
        }
    }
    else
    {
        poscomp = MIN(poscomp, COMP_BASE);
    }
    return poscomp;
}


/*******************************************************/
/** \brief Executes Step 1 of tuning
Step 1 overview:
- In closed loop, try to stabilize the valve at 40% SP to within 1% but no worse than 5.3%, by manipulating P and I.
- Then, in open loop, find output step sizes (in both directions) such that the valve would move at certain speed
- Estimate PID data based on test results by calling tune_EstimatePara()
NOTE: Open-loop tuning with Damping=0, DeadZone=0.
\return 0 on success, non-zero on failure
*/
//AK:TODO: Reason (of failure) is set not on all failure paths.
static s32 tune_Tune_Function(u8_least index, PIDData_t *pid)
{
    s16 n2Temp;
    s8 i, j;
    s16 nPosScaled;
    m_pDiagBuffer = buffer_GetDiagnosticBuffer();
/// DZ: constant for conversion of stroke time to rate, Yes, related to sampling period
    s16 n4OutInc[Xends], nSpeed[Xends], nGain[Xends];
    s16 nTau[Xends]; //!< open-loop dead time estimate per direction (in nominal 50-ms intervals)
    s16 poscomp[Xends];

#if OPTIONAL_TUNE_DIAG == 1
    extDataAutoTune.Times[PID_PHASE_OPEN_START] = timer_GetTicks();
    extDataAutoTune.gainP[extDataAutoTune.gainRuns] = PID_PHASE_OPEN_START;
    extDataAutoTune.gainRuns++;
    if (extDataAutoTune.gainRuns>=MAX_STEPS)
    {
        extDataAutoTune.gainRuns=MAX_STEPS;
    }
#endif

    pid->DeadZone = 0;
#if AK_test
    pid->PosComp = COMP_BASE; //AK: Experimental
#endif
    tune_LimitPID(pid); //AK:TODO: This seems unnecessary, although it doesn't hurt
    (void)tune_SetCurrentPIDData(pid);

    if (control_GetBiasChangeFlag() > 0) //AK:TODO: Make it !=
    {
        control_ResetBiasChangeFlag(); //AK:TODO: Could be done unconditionally if not for start_count. Need to look closer.
    }

    /*Starting @ 40% SP, try to stabilize the valve to within 1% (by reducing P and increasing I, subject to limits).
    Fail if error is outside 5.3% (per DZ, a  limit believed reasonable)
    */
    mode_SetControlMode(CONTROL_MANUAL_POS, FORTY_PCT);
    if (tune_Stabilize(index, pid) == 1)
    {
        // DEBUG_WRITE_TEXT("Exit");
        return 1;
    }
    if (m_pPosErr->err_abs > FIVE_PT3_PCT_868)
    {
        Reason = FAIL_ACTUATION;
        return 9;    // early exit - can't get to SP
    }

    u16 BIAS = control_GetBias();

    //in phase 2 display the bias at the beginning
    WRITE_NUMBER((s32)BIAS, 0);
    if(process_WaitForTime(T2_500)==true)
    {
        return 1;    // early exit - user cancelled
    }

    //This is presumed to be a steady-state Bias.
    //AK:TODO: The 2.5 s stabilization time may not be reliable: A valve util is called for.
    BIAS = control_GetBias();

    //AK:TODO: Bias limits could/should be narrower since we know where we are (~ 40%)
    if( (BIAS > BIAS_UPPER_VALUE) || (BIAS < BIAS_LOWER_VALUE) )
    {
        Reason = BIAS_OUT_RANGE;
        return 2;
    }


#if OPTIONAL_TUNE_DIAG == 1
    extDataAutoTune.InitBias = BIAS;
#endif
    bSingleActing = pneu_IsSingleActing();
    bLCRelay = (cnfg_GetOptionConfigDashVersion()==LOW_COST_VERSION);

    /* Guess the initial output step sizes, beginning with equal in both directions.
    Per DZ: Low-cost used to be larger capacity.  Double acting tend to be hi supply.
    Hence different guesses depending on configuration
    */
    //AK:TODO: If "used to be", does it still apply to MNCB? Verify.
    if ( bLCRelay || (!bSingleActing) )
    {
        n4OutInc[0] = OUT_INI_DBL;      // 50
    }
    else
    {
        n4OutInc[0] = OUT_INI_SGL;      // 80;
    }
    n4OutInc[1] = n4OutInc[0];

    //open loop gain test
/*Experimentally adjust n4OutInc[] so that estimated nSpeed[] is within [SPEED_LOW, SPEED_HIGH]
For the next iteration, the valve starts off from where it was after the current iteration.
This is intended. But if the valve wanders outside [POS_STAY_LOW,POS_STAY_HIGH], it is brought
back by CheckPosStablize() - which may be called unconditionally.
*/
    i = 0;

    do
    {
        if (i++ > TEST_TIMES_LIMIT)
        {
            Reason = FAIL_OPEN_LOOP;
            return 3;
        }

       for (j=Xlow; j<Xends; j++) //in both directions
       {
            nPosScaled = control_GetPosition();
            if((nPosScaled<POS_STAY_LOW) || (nPosScaled>POS_STAY_HIGH)) ///AK:NOTE: POS_STAY_LOW~15%, POS_STAY_HIGH~80%
            {
                if (CheckPosStablize(index, pid) != 0) //The intent is to stabilize the valve between [POS_STAY_LOW, POS_STAY_HIGH]
                {
                    return 1;
                }
            }
            //BIAS = control_GetControlOutput(); //AK: Refresh added but not populated - need sysio
            n2Temp = n4OutInc[j];
            if (j == Xvent)
            {
                n2Temp = -n2Temp;
            }

            //AK:TODO: StepTest produces a bunch of file-scope variables; we may want to bring some order to it
            //The loop is opened only inside StepTest()
            if (StepTest(j, n2Temp, BIAS, nSpeed, nGain, nTau, poscomp) != 0) ///AK:NOTE: Estimate nSpeed[] and other
            {
                return 5;
            }
        #if OPTIONAL_TUNE_DIAG == 1
            //extDataAutoTune.DeltaTime[extDataAutoTune.step] = extDataAutoTune.dTime;
            extDataAutoTune.Delta[extDataAutoTune.openLoopTests] = nSpeed[j];
            extDataAutoTune.Inc[extDataAutoTune.openLoopTests] = n2Temp;
            extDataAutoTune.step++;
            extDataAutoTune.openLoopTests++;
        #endif
       }

       //check valve speed and adjust open loop step size
       for (j=Xlow; j<Xends; j++)
       {
            if(( (nSpeed[j]>SPEED_HIGH) || (nSpeed[j]<SPEED_LOW)) && (n4OutInc[j]<OUT_STEP_HIGH))
            {
                if(nSpeed[j] >= SPEED_HIHI )
                {
                    n4OutInc[j] /= 2;
                }
                else if(nSpeed[j] > SPEED_LOLO)
                {
                    //AK:TODO: Need to understand this logic
                    //AK:TODO: Is the 16-bit conainer guaranteed sufficient? Need analysis and comment.
                    s32 speed_scale;
                    if(nTau[0+j] < DEADTIME_LOW)
                    {
                        speed_scale = SPEED_MID;
                    }
                    else if(nSpeed[j] < SPEED_MID)
                    {
                        speed_scale = SPEED_SUBLOW;
                    }
                    else
                    {
                        speed_scale = SPEED_SUBHIGH;
                    }
                    n4OutInc[j] = (s16)((n4OutInc[j]*speed_scale)/nSpeed[j]);
                }
                else
                {
                    n4OutInc[j] *= 2; //AK:TODO: We may want to try a smaller number before failing the step size
                }
                /* The adjusted n4OutInc may become >=OUT_STEP_HIGH in which case we fall out of the loop without
                   applying it. So the test in the outer "if" is not needed.
                */
            }
        }
    }while (( (nSpeed[0]>SPEED_HIGH) || (nSpeed[0]<SPEED_LOW) || (nSpeed[1]>SPEED_HIGH) || (nSpeed[1]<SPEED_LOW) )
           && (n4OutInc[0]<OUT_STEP_HIGH) && (n4OutInc[1]<OUT_STEP_HIGH) );
    //AK:TODO: The logic is such that if we got good nSpeed in one direction but not in the other, we'll repeat
    //         the test in both directions regardless (without adjusting the step size for the good direction.
    //         Is that indeed what we want to do?
    //AK:TODO: refactor this loop condition in a comprehensible way, like in #if 0/#endif below:
#if 0
    .............
       //check valve speed and adjust open loop step size
       bool_t finished;
       finished = true;
       for (j=0; j<2; j++)
       {
            if(( (nSpeed[j]>SPEED_HIGH) || (nSpeed[j]<SPEED_LOW)))
            {
                finished = false;
                .................
                if(n4OutInc[j]>=OUT_STEP_HIGH)
                {
                    finished = true;
                    break;
                }
            }
        }
    }while (!finished); //AK:TODO: Not exactly the same condition but may be more sensible
#endif

    if ( (nSpeed[Xfill] < SPEED_MIN) && (nSpeed[Xvent] < SPEED_MIN) )
    {
        Reason = FAIL_OPEN_LOOP;
        return 3;
    }

//AK:TODO: At this point, nSpeed[j]>=SPEED_HIGH is possible. Per DZ, This is not intened, but acceptable. Need to review.


    mode_SetControlMode(CONTROL_MANUAL_POS, SIXTY_FOUR_PCT); //AK:TODO: This belongs to tune_RampingTest(), else may cause valve jerking on failure
#if OPTIONAL_TUNE_DIAG == 1
    extDataAutoTune.gainInit[0]=(u16)nGain[0];
    extDataAutoTune.gainInit[1]=(u16)nGain[1];

        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }


#endif
    //Now that a good nSpeed[] is found, use it to estimate the initial PID parameters
    tune_EstimatePara(pid, nGain, nTau);
    #if OPTIONAL_TUNE_DIAG == 1
        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }
        extDataAutoTune.Times[PID_PHASE_OPEN_END] = timer_GetTicks();
    #endif
    if (pid->P < P_MIN)
    {
        Reason = FAIL_P_TOO_SMALL;
        return 6;
    }
    if (ABS(pid->PAdjust) > PADJ_HIGH_LIMIT)
    {
        Reason = FAIL_PADJ_TOO_BIG;
        return 7;
    }

    //pid->PosComp = tune_AdjustPoscomp(bSingleActing, (poscomp[Xfill]+poscomp[Xvent])/2);

    return 0; //moved up call chain: tune_RampingTest(index, pid); //AK:TODO: Move this to the top-level wrapper (which should also do UI notifications)
}

/** \brief This routine tries to estimate some parameters to use in Step 3.
If it can't get good values it does the best it can and continues
This saves time by limiting the search range in Step 3
The control parameters to be estimated are:
- Proportional gains for both filling and exhausting
- derivative time
- integral time
- Boost
- beta
The estimates are based on dead time, open loop gain as well as supply pressure
nTau_avg is also used in Step 3 for an initial guess.
*/
//AK:TODO: We need to understand why low-cost/double-acting stuff is ALSO prominent in control.c
//      It seems that it should be folded in PID parameters - or, alternatively, completely
//      taken care of in the control algorithm. If there's a good reason why it is as it is, we better
//      understand it.
//AK:TODO: We may want to split this routine into small(er) pieces because/to-the-extent they are independent and
//      deserve their own descriptions.
static void tune_EstimatePara(PIDData_t *pid, const s16 nGain[Xends], s16 nTau[Xends])
{
    s16 n2Temp, n2Temp2;
    pres_t n2Psupply;
    const BoardPressure_t* BoardPressure;

// nTau[] is deadtime in both directions (in nominal 50-ms intervals) is produced by StepTest()
///AK:NOTE: nGain[] (in ?) is produced by StepTest()
    nTau[Xfill] = MIN(nTau[Xfill], DEADTIME_MAX);
    nTau[Xvent] = MIN(nTau[Xvent], DEADTIME_MAX);
    nTau_avg = (nTau[Xfill] + nTau[Xvent])/2; ///AK:NOTE Avg of both directions

    /* If gains in different directions are wildly different -
    one is more than twice as large as the other -
    force them equal (DZ: try not to be tremendously asymetric)
    */
    //AK:TODO: We may perhaps do better by limiting the assymetry around the average
    if( (nGain[0] > (2*nGain[1])) || (nGain[0] < (nGain[1]/2)))
    {
        n2Temp = (nGain[Xfill]+nGain[Xvent])/2;
        n2Temp2 = n2Temp;
    }
    else
    {
        n2Temp = nGain[Xfill];
        n2Temp2 = nGain[Xvent];
    }

    //AK:TODO: Need to understand the math behind this ALL
    n2Temp = MAX(n2Temp, GAIN_MIN);
    pid->P = (u16)( (((s32)P_GAIN_RATIO - ((s16)P_TAU_RATIO*nTau[0]))/n2Temp));
    pid->P  = (u16)( (s32)pid->P + (( (m_TuneData.n1Level-2)*pid->P)/20) );
    n2Temp2 = MAX(n2Temp2, GAIN_MIN);
    n2Temp = (s16)((PADJ_GAIN_RATIO - ((s16)P_TAU_RATIO*nTau[1]))/n2Temp2);

    //AK:TODO: Need to understand this: can anyone explain?
    if ( bLCRelay == true)
    {
        pid->P = (u16)Change20Pct((s16)pid->P, true);
    }
    else if (pid->P < P_NOT_HIGH)
    {
        pid->P = (u16)((3*(s32)pid->P)/4);
    }
    else
    {
    }
    pid->PAdjust = (s16)(n2Temp - pid->P);
    pid->D = (u16)(D_MIN +(D_P_RATIO/(pid->P+n2Temp)) + (nTau_avg/2));
    pid->P = MIN(pid->P, P_HIGH_LIMIT);

    BoardPressure = pres_GetPressureData();
    n2Psupply = BoardPressure->Pressures[PRESSURE_SUPPLY_INDEX];
    if(n2Psupply == PRESSURE_INVALID)
    {
        //not available or failed: replace with user-entered
        n2Psupply = tune_GetTuneData(NULL)->SupplyPres_User;
    }
    /* Per DZ, pressure limits are intentionally narrower than those used in cnfg_SetMeasuredSupplyPressure().
    */
    n2Psupply = CLAMP(n2Psupply, PRES_SUPPLY_LO, PRES_SUPPLY_HI);

    //AK:TODO: We may perhaps do better if we monitor the supply pressure as we go (in StepTest) to account for variability
    //AK:TODO: Need to study what happens in case of supply pressure sensor failure

    /* Band calculation
        Band is the amount of boost needed to overcome the deadband in the relay
    */
    pid->Band = (u16)(n2Psupply/BAND_SUPPLY_RATIO);
    if ( (bSingleActing==false) || (bLCRelay==true))
    {   // double acting or low cost version
        if ((pid->P < P_NOT_HIGH) || (bLCRelay==true))
        {
            pid->Band -= 1;
        }
        if (bLCRelay == true)
        {
            pid->Band -= 1;
        }
    }
    else    // single acting
    {
        if (pid->P < P_NOT_HIGH)
        {
            pid->Band -= 1;
        }
    }
    pid->Band = (u16)((s16)pid->Band + (m_TuneData.n1Level/4)); //want pid->Band += m_TuneData.n1Level/4;
    if (pid->Band < 3)
    {
        pid->Band = BOOST_LOW;
    }


    // Beta calculation (empirical selection)
    if (pid->P <(P_NOT_HIGH/2))
    {
        pid->Beta = BETA_BASE-1;
    }
    else if (pid->P < P_NOT_HIGH)
    {
        pid->Beta = BETA_BASE;
    }
    else
    {
        pid->Beta = BETA_BASE+2;
    }

    // I coef. calculation
    //AK:TODO: Can anyone comment on the math of it?
    pid->I = I_MID + (u16)(nTau_avg/3);
    if (pid->P < (P_NOT_HIGH/2))
    {
        pid->I += (pid->P/8);
    }
    else
    {
        pid->I += (pid->P/16);
    }
    pid->I = (u16)((s16)pid->I -(( (m_TuneData.n1Level-2)*(s16)pid->I)/20));
}




/** \brief Step 2 of tuning to estimate POS_COMP (which gets the valve fast to around the setpoint).
The outline: under closed-loop control,
- Ramp the valve SLOWLY from 64% to 60% position range
- Measure (steady-state) Bias at 60%
- Ramp the valve, fast from 60% to 50%
- Ramp the valve asymptotically slowly from 50% to 40%
- Measure (steady-state) Bias at 40%
- Calculate position compensation parameter and apply it for control.
\return 0 on success; a non-zero on failure
*/
//AK:TODO: Bring going to 64% to this function
//AK:TODO: Using tune_Stabilize() may change PID parameters estimates found in Step 1.
//      Is it a desired effect or should Step 1 results be preserved and restored for Step 3?

//AK:TODO: Most (if not all) setpoint ramping can be done nicely using rampsetpoint utilities
//AK:TODO: We may do better (faster or more reliably) if ramping speeds are not constant but
//      derived from the speeds obtained in Step 1

//AK:TODO: We may do much better numerically if we keep scaled 1/PosComp instead of PosComp:
//      We miss bits in divisions, esp. with small bias differences, such as double-acting valves.

//AK:TODO: BIG QUESTION: Why do we go through all these hoops when we could ramp the output
//      in open loop instead?

static s32 tune_RampingTest(u8_least index, PIDData_t *pid)
{
    s16 n2Temp;
    s8 i;
    s16 nManualPos;
    bool_t bLargerErr;
    #if OPTIONAL_TUNE_DIAG == 1
        extDataAutoTune.Times[PID_PHASE_RAMP_FCN_START]=timer_GetTicks();
        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = PID_PHASE_RAMP_FCN_START;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }
        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }
    #endif
    if (tune_Stabilize(index, pid) == 1) ///AK:Q: This may change current PID parameters. Is this the intention? If so, what's the algorithm?
    {       /// DZ: Intended. Just to make it stable
        return 1;
    }
    (void)tune_SetCurrentPIDData(pid);
    //ramp from 64 to 60
    for(i=COUNT_24; i>=0; i--)
    {
        nManualPos = (SIXTY_PCT + (i*RAMPING_RATE2));
        mode_SetControlMode(CONTROL_MANUAL_POS, nManualPos);
        if(process_WaitForTime(T0_250))
        {
            return 1;    // early exit - user cancelled
        }

///AK:NOTE: Service output
        n2Temp = control_GetPosition();
        // WRITE_NUMBER( (s32)( ((float32)n2Temp*10.F)/PERCENT_TO_SCALED_RANGE), 1);
        WRITE_NUMBER( ( (n2Temp*10)/((s16)PERCENT_TO_SCALED_RANGE)), 1);
    }
    if (tune_Stabilize(index, pid) == 1) ///AK:Q: Same as above. What is the theory behind using tune_Stabilize()?
    {                           /// DZ: Just to make it stable
        return 1;
    }

    /*
        11/1/2007 ERP - Changed from using control_GetBias() to pwm_GetValue() because
        the bias value does not include the P*E contribution which can be significant as
        P increases.  Using only the BIAS made it possible to have a significant error
        in PosComp especially in a DoubleActing system
    */

    u16 nBias50 = control_GetControlOutput(); //control_GetBias();
    u16 BIAS;


    mode_SetControlMode(CONTROL_MANUAL_POS, STD_FROM_PERCENT(60.0));
    (void)process_WaitForTime(T1_000); //stabilize
    pos_t startpos = vpos_GetScaledPosition();


    //ramp from 60 to 40
    for(i=COUNT_80; i>=0; i--)
    {
        nManualPos = (s16)(FORTY_PCT+ (i*RAMPING_RATE1));
        //control_SetPositionSP((s32)nManualPos);
        mode_SetControlMode(CONTROL_MANUAL_POS, nManualPos);
        BIAS = control_GetControlOutput(); //control_GetBias();

///AK:NOTE: Service output
        //toggle display between bias and position
        if ( ((i%6)< 3))
        {
            WRITE_NUMBER((s32)BIAS, 0);
        }
        else
        {
            n2Temp = control_GetPosition();
            WRITE_NUMBER( (s32)( (n2Temp*10)/((s16)PERCENT_TO_SCALED_RANGE)), 1);
        }

///AK:Q: What is this variable wait for?
// DZ: make valve move smooth.
        if (i > COUNT_40)
        {
            // if(process_WaitForTime(T0_250)==true)
            if(process_WaitForTime(T0_150)==true)
            {
                return 1;    // 100
            }
        }
        else
        {
            n2Temp = (s16)T0_750-(i*2);   // T0_750 = 150 ///AK:NOTE: Illegal use of scaler 2 (no timer API)
            if(process_WaitForTime((u16)n2Temp)==true)
            {
                return 1;
            }
        }

        //extra slow "finish" for a double-acting valve
        if( (i < 10) && (bSingleActing==false) )
        {
            // WaitForTimeX(1500u);
            if(process_WaitForTime(T0_750))
            {
                return 1;
            }
        }
    }

    //wait for valve to stabilize within a slightly growing error tube for 30*.5s=15s
    pos_least_t errlim;
    do
    {
        if (process_WaitForTime(T0_500) == true)
        {
            return 1;    // early exit - process cancelled
        }

        errlim = (PT3_PCT_49 + (s16)i); ///AK:NOTE: Illegal scaler for i (1) - No API.
        //AK:NOTE: That's widening the error tube from .3% to .48%

        bLargerErr = ( ABS((s32)m_pPosErr->err7) > errlim );
#if OPTIONAL_TUNE_DIAG == 1
        extDataAutoTune.RampLoops++;
#endif
    } while( ((i++)<COUNT_30) && ( (m_pPosErr->err_abs>errlim) || bLargerErr ) );

#if OPTIONAL_TUNE_DIAG == 1
    extDataAutoTune.BiasHigh = nBias50;
    extDataAutoTune.BiasLow = BIAS;
#endif

    if (m_pPosErr->err_abs > FIVE_PT3_PCT_868)
    {
        return 2;    // early exit - can't get to SP
    }

    (void)process_WaitForTime(T1_000); //stabilize
    pos_t posdiff = vpos_GetScaledPosition() - startpos;
    BIAS = control_GetControlOutput(); //control_GetBias();

    //s16 poscomp = tune_ComputePoscomp(COMP_CONST, BIAS-nBias50);
    s16 poscomp = tune_ComputePoscomp(posdiff, BIAS-nBias50);
    poscomp = tune_AdjustPoscomp(bSingleActing, poscomp);

    if ( !bSingleActing )
    {   // double acting
        if (poscomp > COMP_BASE)
        {
            //AK:TODO: Large PosComp is replaced in its function from a divisor to a shift counter (down from COMP_MAX).
            //      This overload is pathetic and needs weeding out ASAP, here and in control.c
            //AK:TODO: This stuff is based on preliminary guess of P (but not, remarkably, of PAdjust)
            //      and is never recomputed again. Does it make sense? What's the math of it? Need to understand.
            if (pid->P < P_NOT_HIGH)
            {
                poscomp = (COMP_BASE+1);
            }
            else if (pid->P < P_MID)
            {
                poscomp = MIN(poscomp, (COMP_BASE+2));
            }
            else
            {
                //already done: poscomp = MIN(poscomp, (COMP_BASE+3));
            }
        }
    }

    //NOTE: These new parameters are not yet commited to the control, so the trouble is N/A
    pid->PosComp = poscomp;
    pid->I += (u16)(pid->PosComp); //AK:TODO: Need to understand what is done here

    //It is probably happens elsewhere (doesn't it?), but for certainty, do this here at the point of change
    tune_LimitPID(pid);
    (void)tune_SetCurrentPIDData(pid);

#if OPTIONAL_TUNE_DIAG == 1
    extDataAutoTune.Times[PID_PHASE_RAMP_FCN_END]=timer_GetTicks();
    extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
    extDataAutoTune.gainRuns++;
    if (extDataAutoTune.gainRuns>=MAX_STEPS)
    {
        extDataAutoTune.gainRuns=MAX_STEPS;
    }
#endif

    //Show in local UI
    WRITE_NUMBER((s32)pid->PosComp, 0);
    if(process_WaitForTime(T0_500))
    {
        return 1;
    }

    return 0;
}

/*********************************************************************/

#if AK_extract
static
s16 tune_OutputRampTau(s8 iDir, s16 nOutInc, s32 nBiasSave, s16 nTau[Xends], s32 *final_out)
{
    bool_t bNotMoved;
    pos_t nPosIni = control_GetPosition();
    pos_t nPosScaled;
///AK:NOTE: Try to move the valve by .5%
    mode_SetControlMode(CONTROL_OFF, (s32)nPosIni);
    s32 nIPOutput = nBiasSave + nOutInc;
    tick_t start_ticks = timer_GetTicks();
    tick_t spent;

    s16 i = 0;
    do
    {
        (void)sysio_WritePwm(nIPOutput, PWMNORMALIZED);
        if (process_WaitForTime(T0_050))
        {
            return 1;    // early exit - user cancelled
        }
///AK: Why this boost? (Negative on double-acting down). Algorithm?
// DZ: keep ramping valve
        //SHOULD THIS BE AN AND??????????
        if((iDir == Xfill) || !bSingleActing )
        {
            nIPOutput += (OUT_INC_S-1);
        }

        nIPOutput += nOutInc/OUT_INC_R3;
        nPosScaled = control_GetPosition(); ///AK:NOTE: Measured before output


///AK:Q: ABS - is it OK if the valve does move but in a different direction?
/// DZ: hopefully not
        spent = timer_GetTicksSince(start_ticks);
        if ( ABS((nPosScaled-nPosIni)) < HALF_PCT_82)
        {
            bNotMoved = true;
        }
        else
        {
            bNotMoved = false;
        }
    }while( ( (i++<COUNT_100) && bNotMoved  ) || (i<COUNT_10) ); //AP has 7, not 10 ///AK:Q: Where does 7(now,10) come from? and 100, too?
    buffer_InitializeDiagnosticBuffer();            /// DZ: time ranges.
    //nTau[iDir] = i; ///AK:NOTE: The time (in nominal 50 ms intervals) of the valve's starting moving.

///AK:NOTE: bNotMoved not guaranteed
///AK:Q: Is it OK?
/// DZ: Acceptable


    //Remove time accumulation error
    spent /= T0_050;
    nTau[iDir] = (s16)MIN(spent, INT16_MAX); ///AK:NOTE: The time (in nominal 50 ms intervals) of the valve's starting moving.
    *final_out = nIPOutput;
    return 0;
}

static
s16 tune_OutputRampSpeed(s8 iDir, s16 nOutInc, s32 nBiasSave, s16 nSpeed[Xends], s32 *final_out, s16 poscomp[Xends])
{
    s16 i;
    pos_t nPosScaled;
    s32 nIPOutput = *final_out;

    for(i=0; i<3; i++)
    //Assuming the valve is moving
    {   /* buffer is full */
        if (buffer_AddDiagnosticData1(0))
	    {   /* buffer is full */
	        return 2;
	    }
    }
    //automatically i = 3;
    tick_t nTimeCounts = timer_GetTicks();
    pos_t nPosIni = control_GetPosition();
    while(i<31)
    {
        if (process_WaitForTime(1U)) //let process things run FBO Mopup, UI, watchdog
        {
            return 1;    // early exit - user cancelled
        }
        if( timer_GetTicksSince(nTimeCounts) >= T0_050)  /* 50 ms has elapsed - save the position */
        {
            i++;
#if OPTIONAL_TUNE_DIAG==1
            if (i==10)
            {
                startTime = timer_GetTicks();
            }
#endif
            // DEBUG_WRITE_NUMBER(i, 0);  // decimal point 1
            nTimeCounts += T0_050;
            nPosScaled = control_GetPosition();
            // m_pDiagBuffer[i++] = nPosScaled - nPosIni;
            if (buffer_AddDiagnosticData1(nPosScaled - nPosIni))
            {   // buffer is full
                return 2;
            }
            if( iDir == Xfill )
            {
                nIPOutput = (u16)((s32)nIPOutput +  (nOutInc/OUT_INC_R2) ); //want nIPOutput += nOutInc/OUT_INC_R2;
                if (nOutInc >= OUT_INI_SGL)
                {
                    nIPOutput += (OUT_INC_L+2);
                }
                else
                {
                    nIPOutput += (OUT_INC_S+1);
                }
                if( (bLCRelay || !bSingleActing ) && (nIPOutput > (nBiasSave+BIAS_CHANGE_THRESH)) )
                {
///AK:Q: Why this boost and its conditions?
///DZ: Extra boost for its extra dead band
                    nIPOutput += OUT_INC_S;
                }
            }
            else
            {
                nIPOutput = (u16)((s32)nIPOutput +  (nOutInc/OUT_INC_R1) ); //want nIPOutput += nOutInc/OUT_INC_R1;
                if ( !bSingleActing && (nIPOutput < (nBiasSave-BIAS_CHANGE_THRESH)) )
                {
                    nIPOutput -= OUT_INC_L;
                }
                else
                {
                    nIPOutput -= (OUT_INC_S-1);
                }
            }
            control_SetPWM((u32)nIPOutput);
        }
#if OPTIONAL_TUNE_DIAG==1
        extDataAutoTune.dTime = timer_GetTicksSince(startTime);
#endif
    }

    poscomp[iDir] = tune_ComputePoscomp(control_GetPosition() - nPosIni, nIPOutput - nBiasSave);
    nIPOutput = nBiasSave;
    control_SetPWM((u32)nIPOutput);
    if (buffer_AddDiagnosticData1(-1))
    {   /* buffer is full */
        return 2;
    }
    nSpeed[iDir] = m_pDiagBuffer[INDEX2] - m_pDiagBuffer[INDEX1];
    //in phase 2 write speed
    WRITE_NUMBER(nSpeed[iDir], 0);  // decimal point 0
    nSpeed[iDir] = ABS(nSpeed[iDir]);
    if (process_WaitForTime(T2_500))
    {
        return 1;    // early exit - user cancelled
    }
   *final_out = nIPOutput;
    return 0;
}
#endif //AK_Extract

/** \brief open loop test
The test moves the valve by changing output to I/P and record the response in the
(primary) diagnostic buffer. It will also compute statistics for both directions:
- nSpeed[]
- nTau[] and
- nGain[].
PRE-REQUISITE: The valve must be stable in the beginning.
NOTE: This static function does no cleanup of its own (all cleanup is in tune_Run_Selftune),
so any early returns are legitimate.

\param iDir - valve moving direction =0: filling direction; =1: exhaust direction
\param nOutInc - output change (counts); nOutInc is positive (fill) or negative (exhaust)
\param nBiasSave - current (initial) bias
\return 0 on success; a non-zero on failure
*/
#if AK_extract

static s16 StepTest(s8 iDir, s16 nOutInc, u16 nBiasSave, s16 nSpeed[Xends], s16 nGain[Xends], s16 nTau[Xends], s16 poscomp[Xends])
{
    s32 nIPOutput;
#if OPTIONAL_TUNE_DIAG==1
    tick_t startTime=0;
#endif
    WRITE_NUMBER((s32)nOutInc, 0);
    if (nOutInc == 0)
    {
        return -1;
    }

    s16 ret = tune_OutputRampTau(iDir, nOutInc, nBiasSave, nTau, &nIPOutput);
    if(ret != 0)
    {
        return ret;
    }

    ret = tune_OutputRampSpeed(iDir, nOutInc, nBiasSave, nSpeed, &nIPOutput, poscomp);
    if(ret != 0)
    {
        return ret;
    }

///AK:Q: What is GAIN_RATIO(=34) ? What's the algorithm here?
/// DZ: unit conversion.  But not have to be accurate at all.
    nGain[0+iDir] = (s16)((GAIN_RATIO*nSpeed[iDir])/ABS(nOutInc)); /* unit in %-out/(%-in x sec)x100 */
    return 0;
}

#else //AK_extract


static s16 StepTest(s8 iDir, s16 nOutInc, u16 nBiasSave, s16 nSpeed[Xends], s16 nGain[Xends], s16 nTau[Xends], s16 poscomp[Xends])
{
    s16 i,nPosScaled, nPosIni;
    tick_t nTimeCounts;
    u16 nIPOutput;
    bool_t bNotMoved;
#if OPTIONAL_TUNE_DIAG==1
    tick_t startTime=0;
#endif
    WRITE_NUMBER((s32)nOutInc, 0);
    nPosIni = control_GetPosition();
    if (nOutInc == 0)
    {
        return -1;
    }

///AK:NOTE: Try to move the valve by .5%
    mode_SetControlMode(CONTROL_OFF, (s32)nPosIni);
    nIPOutput = (u16)( ((s32)nBiasSave) + ((s32)nOutInc) );
    tick_t start_ticks = timer_GetTicks();
    tick_t spent;

    i = 0;
    do
    {
        control_SetPWM((u32)nIPOutput);
        if (process_WaitForTime(T0_050))
        {
            return 1;    // early exit - user cancelled
        }
///AK: Why this boost? (Negative on double-acting down). Algorithm?
// DZ: keep ramping valve
        //SHOULD THIS BE AN AND??????????
        if((iDir == Xfill) || !bSingleActing )
        {
            nIPOutput += (OUT_INC_S-1);
        }

        nIPOutput = nIPOutput + (u16)(nOutInc/OUT_INC_R3); //want nIPOutput += nOutInc/OUT_INC_R3;
        nPosScaled = control_GetPosition(); ///AK:NOTE: Measured before output


///AK:Q: ABS - is it OK if the valve does move but in a different direction?
/// DZ: hopefully not
        spent = timer_GetTicksSince(start_ticks);
        if ( ABS((nPosScaled-nPosIni)) < HALF_PCT_82)
        {
            bNotMoved = true;
        }
        else
        {
            bNotMoved = false;
        }
    }while( ( (i++<COUNT_100) && bNotMoved  ) || (i<COUNT_10) ); //AP has 7, not 10 ///AK:Q: Where does 7(now,10) come from? and 100, too?
    buffer_InitializeDiagnosticBuffer();            /// DZ: time ranges.
    //nTau[iDir] = i; ///AK:NOTE: The time (in nominal 50 ms intervals) of the valve's starting moving.

    //Remove time accumulation error
    spent /= T0_050;
    nTau[iDir] = (s16)MIN(spent, INT16_MAX); ///AK:NOTE: The time (in nominal 50 ms intervals) of the valve's starting moving.



///AK:NOTE: bNotMoved not guaranteed
///AK:Q: Is it OK?
/// DZ: Acceptable

    for(i=0; i<3; i++)
    //Assuming the valve is moving
    {   /* buffer is full */
        if (buffer_AddDiagnosticData1(0))
	    {   /* buffer is full */
	        return 2;
	    }
    }
    //automatically i = 3;
    nTimeCounts = timer_GetTicks();
    nPosScaled = control_GetPosition();
    nPosIni = nPosScaled;
    while(i<31)
    {
        if (process_WaitForTime((u16)(T0_050/5)) == true)
        {   // also used to reset external watch dog for this 1.5 sec loop
            return 1;    // early exit - user cancelled
        }
        if( timer_GetTicksSince(nTimeCounts) >= (tick_t)T0_050)  /* 50 ms has elapsed - save the position */
        {
            i++;
#if OPTIONAL_TUNE_DIAG==1
            if (i==10)
            {
                startTime = timer_GetTicks();
            }
#endif
            // DEBUG_WRITE_NUMBER(i, 0);  // decimal point 1
            nTimeCounts += T0_050;
            nPosScaled = control_GetPosition();
            // m_pDiagBuffer[i++] = nPosScaled - nPosIni;
            if (buffer_AddDiagnosticData1(nPosScaled - nPosIni))
            {   // buffer is full
                return 2;
            }
            if( iDir == Xfill )
            {
                nIPOutput = (u16)((s32)nIPOutput +  (nOutInc/OUT_INC_R2) ); //want nIPOutput += nOutInc/OUT_INC_R2;
                if (nOutInc >= OUT_INI_SGL)
                {
                    nIPOutput += (OUT_INC_L+2);
                }
                else
                {
                    nIPOutput += (OUT_INC_S+1);
                }
                if( (bLCRelay || !bSingleActing ) && (nIPOutput > (nBiasSave+BIAS_CHANGE_THRESH)) )
                {
///AK:Q: Why this boost and its conditions?
///DZ: Extra boost for its extra dead band
                    nIPOutput += OUT_INC_S;
                }
            }
            else
            {
                nIPOutput = (u16)((s32)nIPOutput +  (nOutInc/OUT_INC_R1) ); //want nIPOutput += nOutInc/OUT_INC_R1;
                if ( !bSingleActing && (nIPOutput < (nBiasSave-BIAS_CHANGE_THRESH)) )
                {
                    nIPOutput -= OUT_INC_L;
                }
                else
                {
                    nIPOutput -= (OUT_INC_S-1);
                }
            }
            control_SetPWM((u32)nIPOutput);
        }
#if OPTIONAL_TUNE_DIAG==1
        extDataAutoTune.dTime = timer_GetTicksSince(startTime);
#endif
    }

    poscomp[iDir] = tune_ComputePoscomp(control_GetPosition() - nPosIni, nIPOutput - nBiasSave);
    nIPOutput = nBiasSave;
    control_SetPWM((u32)nIPOutput);
    if (buffer_AddDiagnosticData1(-1))
    {   /* buffer is full */
        return 2;
    }
    nSpeed[iDir] = m_pDiagBuffer[INDEX2] - m_pDiagBuffer[INDEX1];
    //in phase 2 write speed
    WRITE_NUMBER(nSpeed[iDir], 0);  // decimal point 0
    nSpeed[iDir] = ABS(nSpeed[iDir]);
    if (process_WaitForTime(T2_500))
    {
        return 1;    // early exit - user cancelled
    }

///AK:Q: What is GAIN_RATIO(=34) ? What's the algorithm here?
/// DZ: unit conversion.  But not have to be accurate at all.
    nGain[0+iDir] = (s16)((GAIN_RATIO*nSpeed[iDir])/ABS(nOutInc)); /* unit in %-out/(%-in x sec)x100 */
    return 0;
}
#endif //AK_extract



/*********************************************************************/

/** \brief Runs close loop test.
Closed-loop test is further refinement of control parameters obtained from the
previous steps.  Valve position step change from 40% to 45% and from 45% to 40%
are run and valve position response data are recorded and analyzed.  Control
parameters are adjusted and applied for control based on test data analysis.
Test continues to run until either the dynamic performance becomes acceptable or
time-out with failure.  The step change size is fixed at 5%.  The time to complete
this step varies.  Typically more challenging valve systems take more time to finish.
\return 1 on success; -1 on failure
*/
static s32 tune_CloseLoop(u8_least index, PIDData_t *pid)
{
    ErrorCode_t n;
    s32 nRet, dval;
    pos_t arg2, arg3;
    nSCount = 0;
    UNUSED_OK(index);

    StepData_t step_data =
    {
        .Y_last = 0,
        .DY_min = 0, // in %/cycle
        .nOvershoot = INI_VALUE,
        .nOvershoot2 = INI_VALUE, //?
        .bD_Large = false,
    };


    #if OPTIONAL_TUNE_DIAG == 1
        extDataAutoTune.Times[PID_PHASE_TUNE_CLOSED_START]=timer_GetTicks();
        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = PID_PHASE_TUNE_CLOSED_START;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }
        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }
    #endif
    TuneCase_t case_c = tunecase_init;
    do
    {
        tune_LimitPID(pid);
        (void)tune_SetCurrentPIDData(pid);

        //displays P (direction dependent) and case number (which is a state)
        if((case_c < MOVE_DIR_LINE) || (case_c == fill_success))
        {
            dval = (((s32)pid->P*100)+(s32)case_c);
        }
        else
        {
            dval = (((pid->P+pid->PAdjust)*100)+(s32)case_c);
        }
        WRITE_NUMBER(dval, 0);

        if( !equiv((case_c<MOVE_DIR_LINE), pos_GetPositionConf(NULL)->bATO ) )
        {
            arg2 = INT_PERCENT_OF_RANGE(POS_TWO);
            arg3 = INT_PERCENT_OF_RANGE(POS_ONE);
        }
        else
        {
            arg3 = INT_PERCENT_OF_RANGE(POS_TWO);
            arg2 = INT_PERCENT_OF_RANGE(POS_ONE);
        }
        n = diag_SetDiagnosticParameters(DIAG_STEP, STEP_TIME, arg2, arg3, SAMPLE_RATE);
        if (n != ERR_OK)
        {
            return -1;
        }

        if (!diag_Perform_StepTest())
        {
            return -1;
        }

        Data_Processing(pid, &step_data);
        if (process_WaitForTime(T1_500)) // 1.5 s for LCD tune_xchange display
        {
            return -1;    // early exit - user cancelled
        }
        case_c = Para_Adjust(pid, &step_data, case_c);
        switch(case_c)
        {
            case tunecase_finished:
                nRet = 1;
                break;
            case tunecase_failed:
            case tunecase_canceled:
                nRet = -1;
                break;
            default:
                nRet = 0; //continue on
                break;
        }
        nSCount++;
        if((nSCount > TUNE_MAX_TRIES) && (pid->DeadZone < PT3_PCT_49))
        {
            pid->DeadZone += PT15_PCT_24;
            nSCount = TUNE_TRY_INITVAL; //restrt from here
        }
        if(nSCount > TUNE_MAX_TRIES)         /* overtime and fail */
        {
            if(case_c < MOVE_DIR_LINE)
            {
                Reason = OVER_TIME_FILL;
            }
            else
            {
                Reason = OVER_TIME_EXHA;
            }
            return -1;
        }
        tune_LimitPID(pid); //AK: That was missing
        (void)tune_SetCurrentPIDData(pid); //updated params to control
        #if OPTIONAL_TUNE_DIAG == 1
            extDataAutoTune.closedLoops++;
            extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
            extDataAutoTune.gainRuns++;
            if (extDataAutoTune.gainRuns>=MAX_STEPS)
            {
                extDataAutoTune.gainRuns=MAX_STEPS;
            }
        #endif

    } while (nRet == 0);
    #if OPTIONAL_TUNE_DIAG == 1
        extDataAutoTune.Times[PID_PHASE_TUNE_CLOSED_END]=timer_GetTicks();
        extDataAutoTune.gainP[extDataAutoTune.gainRuns] = pid->P;
        extDataAutoTune.gainRuns++;
        if (extDataAutoTune.gainRuns>=MAX_STEPS)
        {
            extDataAutoTune.gainRuns=MAX_STEPS;
        }
    #endif
    return nRet;   // =1 OK, -1 failed
}

///AK:Q: I completely fail to reverse-engineer this function. Decent description for each case_c and what it is?
/// DZ: case_c is just a number for labeling.
///AK:Q: m_TuneData.n1Level looks like a step size. Should it, ideally, automatically decrease from iteration to iteration?
/// DZ: This is used entered aggressiveness value.
/** \brief Adjusts parameters based on the analysis of the closed loop step response data.
The Control performance criteria would change over time to try match the actual valve system.
Final position, overshoot and response time are key performance data for closed-loop tuning; they
are computed by DataProcessing().
NOTE: The code implements the algorithm flowcharted in "The Theory of Operation"
\param pid - a pointer to parameters to update
\param tune_xchange - a ponter to handover data
\param case_c - tune case per DZ use
\return new tune case, may be terminal (success/failed/canceled)
*/
static TuneCase_t Para_Adjust(PIDData_t *pid, StepData_t *tune_xchange, TuneCase_t case_c)
{
    TuneCase_t case_p = case_c;
    s16_least nTfast, nTslow; //Acceptable upper and lower limits of t90 Response time (in 50-ms sample counts).
    s16_least nILow;
	s16 nDeltaP; //10% of P - amount of adjustment
    pos_least_t nY_last = tune_xchange->Y_last;
    pos_least_t nDY_min = tune_xchange->DY_min;
    if( nY_last < HALF_PCT_82) //AK:TODO: This doesn't seem to have any effect since nY_last is limited from below by TWO_PCT_328 in DataProcessing()
    {
        Reason = FAIL_ACTUATION;
        return tunecase_failed;
    }
    nTslow = T98_LO_LIMIT;  // 4;
    nTslow += ((pid->P/T_RATIO_P) + (nTau_avg/T_RATIO_TAU) );
    nTfast = (nTslow/2) - nSCount;
    if (bSingleActing) // single
    {
        if (pid->P < P_NOT_HIGH)
        {
            nTslow += nSCount;
        }
        else
        {
            nTslow += (3*nSCount);
        }
    }
    else
    {
        nTslow += (2*nSCount);
    }
    nTslow = nTslow - (s16)(( (m_TuneData.n1Level-2)*nTslow)/20); //Per DZ Guaranteed >0 (not only >=)
    nTfast = nTfast - (s16)(( (m_TuneData.n1Level-2)*nTfast)/20);
    nTfast = MAX(nTfast, T98_LO_LIMIT);  // 6
    nILow = (I_BASE + (pid->P/5) + (nTau_avg*4) );
    if (!bSingleActing) // double
    {
        nILow += (I_BASE/2);
    }
    if(case_c >= MOVE_DIR_LINE )
    {
     //exhausting direction
        nDeltaP = (pid->PAdjust+(s16)pid->P)/P_INC_RATIO;
        if(nY_last > (FIVE_PT3_PCT_868+(Y_ADJ_RATE2*nSCount)+(3*pid->DeadZone) ) )
        {
            if(tune_xchange->nT_90 > nTslow)
            {
                pid->PAdjust += nDeltaP;
                case_c = vent_slow_largeY;
            }
            else
            {
                pid->PAdjust -= nDeltaP;
                pid->D = (u16)Change20Pct((s16)pid->D, false);
                case_c = vent_fast_largeY;
            }
            return case_c;
        }
        else if(tune_xchange->nT_90 < nTfast)
        {
            pid->PAdjust -= (pid->PAdjust + (s16)pid->P)/PADJ_INC_RATIO;
            case_c = vent_notfast_smallY;
            return case_c;
        }
        else if( (nY_last < (FOUR_PT7_PCT_770-((2*pid->DeadZone)+(Y_ADJ_RATE1*nSCount))) )
                && (tune_xchange->nOvershoot < OVERSHOOT_LOW) )
        {
            if (pid->I > I_MID)
            {
                pid->I = (u16)Change20Pct((s16)pid->I, false);
            }
            pid->PAdjust += nDeltaP;
            pid->D = (u16)Change20Pct((s16)pid->D, false);
            case_c = vent_large_negY;
            return case_c;
        }
        else if(tune_xchange->nT_90 > nTslow)
        {   /* too slow: 14x340=4760 0.7sec gain 3.4/sec */
            pid->PAdjust += nDeltaP;
            case_c = vent_notslow_smallY;
            return case_c;
        }
        else if(tune_xchange->nOvershoot > (5*nSCount)) //U: THS was (5+nSCount)
        {
            if( (tune_xchange->nOvershoot>tune_xchange->nOvershoot_p) && (case_p==vent_large_overshoot) )
            {
                pid->D = (u16)Change20Pct((s16)pid->D, true);
                case_c = vent_large_overshootAgain;
            }
            else
            {
                pid->PAdjust -= (s16)((tune_xchange->nOvershoot*nDeltaP)/PADJ_INC_RATIO);  //Was: /20 but in a different place, /16
                case_c = vent_large_overshoot;
            }
            return case_c;
        }
        else if( (tune_xchange->nOvershoot2 > tune_xchange->nOvershoot) && (tune_xchange->nOvershoot2 > OVERSHOOT_LOW) )
        {
            case_c = vent_increased_negOvershoot;
            pid->D = (u16)Change20Pct((s16)pid->D, false);
            return case_c;
        }
        else
        {
            if(tune_xchange->nOvershoot > 2)
            {
                pid->PAdjust -= (s16)((tune_xchange->nOvershoot*nDeltaP)/15);
            }
            case_c = tunecase_init;
        }
    }
    else   /* air fill test */
    {
        nDeltaP = ((((s16)pid->P)/10)+2);
        if(nY_last > (FIVE_PT3_PCT_868+(20*nSCount)+(2*pid->DeadZone) ) )   /* from 869 to 887 */
        {
            if(tune_xchange->nT_90 > nTslow)
            {
                if( (tune_xchange->nT_90 > (10+nTslow)) && (bLCRelay) )
                {
                    pid->Beta += 1;
                }
                pid->P = (u16)((s16)pid->P + nDeltaP);
                pid->D = (u16)Change20Pct((s16)pid->D, false);
                case_c = fill_slow_largeY;
                return case_c;
            }
            else
            {
                pid->P = (u16)((s16)pid->P - nDeltaP);
                pid->D = (u16)Change20Pct((s16)pid->D, true);
                case_c = fill_fast_largeY;
                return case_c;
            }
        }
        else if(tune_xchange->nT_90 < nTfast)
        { /* too fast */
            if( (case_p == fill_fast) || (pid->P < P_NOT_LOW) )
            {
                pid->D = (u16)Change20Pct((s16)pid->D, false);
                case_c = fill_fast_again;
            }
            else
            {
                pid->P = (u16)Change20Pct((s16)pid->P, false);
                case_c = fill_fast;
            }
            return case_c;
        }
        else if(nY_last < ((FOUR_PT7_PCT_770-(2*pid->DeadZone))-(10*nSCount)) )
        {
            if (pid->I > nILow)
            {
                pid->I = (u16)Change20Pct((s16)pid->I, false);
            }
            pid->P = (u16)( (s16)pid->P + nDeltaP);
            pid->D = (u16)Change20Pct((s16)pid->D, false);
            case_c = fill_large_negY;
            return case_c;
        }
        else if( (nDY_min < 10) && (tune_xchange->bD_Large) &&
                 (pid->D > 10) && (case_p != fill_largeD) )
        {
            pid->D = (u16)Change20Pct((s16)pid->D, false);
            case_c = fill_largeD;
            return case_c;
        }
        else if( (tune_xchange->nOvershoot2 > tune_xchange->nOvershoot) && (tune_xchange->nOvershoot2 > OVERSHOOT_LOW) )
        {
            if( (nSCount > 1) && (tune_xchange->nOvershoot > tune_xchange->nOvershoot_p) && (case_p == fill_large_neg_overshoot) )
            {
                pid->P = (u16)((s16)pid->P + nDeltaP);
                pid->D = (u16)Change20Pct((s16)pid->D, true);
                case_c = fill_large_neg_overshootAgain;
            }
            else
            {
                pid->D = (u16)Change10Pct((s16)pid->D, false);
                case_c = fill_large_neg_overshoot;
            }
            return case_c;
        }
        else if((tune_xchange->nOvershoot>(4+((3*nSCount)/2))) || (tune_xchange->nOvershoot2>(2+(nSCount/2))))
        {
            if( (tune_xchange->bD_Large) || (pid->D>pid->P) )
            {
                if(tune_xchange->nOvershoot > OVERSHOOT_HIGH)
                {
                    pid->P = (u16)Change20Pct((s16)pid->P, false);
                }
                else
                {
                    pid->P -= (u16)((tune_xchange->nOvershoot*(s32)pid->P)/100);
                }
                case_c = fill_large_overshoot_largeD;
                pid->D = (u16)Change20Pct((s16)pid->D, false);
            }
            else
            {
                if( (nSCount>1) && (tune_xchange->nOvershoot>=tune_xchange->nOvershoot_p) && (case_p==fill_overshoot_notslow))
                {
                    if(tune_xchange->nOvershoot > OVERSHOOT_HIGH)
                    {
                        pid->P = (u16)Change20Pct((s16)pid->P, false);
                    }
                    else
                    {
                        pid->P -= (u16)((tune_xchange->nOvershoot*(s32)pid->P)/100);
                    }
                    case_c = fill_same_overshoot;
                    pid->D = (u16)Change20Pct((s16)pid->D, false);
                }
                else
                {
                    if(tune_xchange->nT_90 > nTslow)
                    {        /* too slow: 14x340=4760 0.7sec gain 3.4/sec */
                        case_c = fill_overshoot_slow;
                        pid->P = (u16)( (s16)pid->P + nDeltaP);
                        pid->D = (u16)Change10Pct((s16)pid->D, false);
                    }
                    else
                    {
                        pid->D = (u16)Change20Pct((s16)pid->D, true);
                        case_c = fill_overshoot_notslow;
                    }
                }
            }
            return case_c;
        }
        else if( (tune_xchange->nOvershoot < 1) && (tune_xchange->nOvershoot2 > OVERSHOOT_LOW))
        {
            if( (tune_xchange->bD_Large) || (pid->D > (3*pid->P) ) )
            {
                pid->D = (u16)Change10Pct((s16)pid->D, false);
            }
            case_c = fill_neg_overshoot;
            pid->P = (u16)( (s16)pid->P + nDeltaP);
            return case_c;
        }
        else if(tune_xchange->nT_90 > nTslow)
        {   /* too slow: 14x340=4760 0.7sec gain 3.4/sec */
            if (pid->I > nILow)
            {
                pid->I = (u16)Change20Pct((s16)pid->I, false);
            }
            pid->P = (u16)( (s16)pid->P + nDeltaP);
            if((tune_xchange->nT_90 > tune_xchange->nT_90_p) && (case_p == fill_slowAgain) && (pid->D > D_NOT_LOW) )
            {
                pid->D = (u16)Change20Pct((s16)pid->D, false);
                case_c = fill_slow;
            }
            else
            {
                case_c = fill_slowAgain;
            }
            return case_c;
        }
        else
        {
            if(tune_xchange->nOvershoot > FIVE_PCT)
            {
                pid->P = (u16) ( (s16)pid->P - ((tune_xchange->nOvershoot*(s32)pid->P)/100));
            }
            case_c = fill_success;
        }
        if ( pid->PAdjust < -(s16)(pid->P/2) )
        {
            pid->PAdjust = -(s16)(pid->P/2);
        }
        else if ( pid->PAdjust > (s16)(pid->P/2) )
        {
            pid->PAdjust = (s16)(pid->P/2);
        }
        else
        {
        }
    }
    if(case_c == fill_success)
    {
        nSCount = 0;
        tune_xchange->nOvershoot = INI_VALUE;
        pid->PAdjust = Change20Pct(pid->PAdjust, true);
        return case_c;
    }
    else
    {
        //Doesn't matter: case_c = tunecase_init;
    }
    if( tune_xchange->nOvershoot > OVERSHOOT_MID )
    {
        pid->P = (u16)Change10Pct((s16)pid->P, false);
    }
    pid->P = (u16)( (s16)pid->P + (( m_TuneData.n1Level*(s32)pid->P)/25));
    pid->I = (u16)((s16)pid->I -(( m_TuneData.n1Level*(s16)pid->I)/20));
    return tunecase_finished;
}

/******************************************************************/


/** \brief Computes maximum, minimum, and final positions, overshoots and dead and peak time(s).
NOTE. Computations are based on the buffered results of the closed-loop step test executed
immediately before.
NOTE.This function does only calculations, does not wait for anything and does not move the valve.
*/
static void Data_Processing(const PIDData_t *pid, StepData_t *tune_xchange)
{
    s16 nY_last;
    s16 nDY_min, nT_DY_min;
    s16 nDY_max, nT_DY_max;
    s16 nTau_m, nY_max, nT_max;
    //s16 nT_min;

    s16 i = 1, nTemp;
    do
    {
        i++;
    }while( (ABS((s32)m_pDiagBuffer[i+STEP_CHANGE_INDEX])<(s32)NOISE) && (i<(DATA_PTS/2))  );
///AK:NOTE: i is the last point of small deviation in the first half of data (but beyond STEP_CHANGE_INDEX)
        nTau_m = i; ///AK:NOTE: Dead time

    //find the max to use to calc overshoot
        //find position max and time there
        //find delta position max and time there
    nY_max = 0;     nT_max = 0;
    nDY_max = 0;    nT_DY_max = 0;
    for(i=0; i<DATA_PTS; i++)
    {
        if(m_pDiagBuffer[i+STEP_CHANGE_INDEX] > nY_max)
        {
            nY_max = m_pDiagBuffer[i+STEP_CHANGE_INDEX];              /* search for peak value;    */
            nT_max = i;
        }
        if(i < (MAX_TIMES_LIMIT-2))
        {
            nTuneArray[i] = m_pDiagBuffer[i+1+STEP_CHANGE_INDEX]-m_pDiagBuffer[i+STEP_CHANGE_INDEX];
            if(nTuneArray[i] >nDY_max)         /* search for max rate of change */
            {
                nDY_max = nTuneArray[i];
                nT_DY_max = i;
            }
        }
    }

    //average the last 10 points to find Z_infinity
    s32 lTemp = 0;
    for(i=(DATA_PTS-AVERAGE_PTS); i<DATA_PTS; i++)
    {
        lTemp += m_pDiagBuffer[i+STEP_CHANGE_INDEX];
    }
    nY_last = (s16)(lTemp/AVERAGE_PTS); //nY_last is the final value (Z_infinity in "The Theory of Operation")

    //calculate t90 as time to final value minus 1/2 percent

    nTemp = nY_last - (HALF_PCT_82 + (s16)(pid->DeadZone/2));
    i = 1;
    if(nY_max > nTemp ) //If Overshoot occurred...
    {
        do
        {
            i++;
        }while( (m_pDiagBuffer[i+STEP_CHANGE_INDEX]<nTemp) && (i<(nT_max+1))  );
    }
    else
    {
        do
        {
            i++;
        }while( (m_pDiagBuffer[i+STEP_CHANGE_INDEX]<(nY_max-24)) && (i<(nT_max+1))  );
    }
    tune_xchange->nT_90_p = tune_xchange->nT_90;
    tune_xchange->nT_90 = i;

    s16 nY_min = nY_max;
    //U nT_min = nT_max;
    //look for a min starting at the max for calc of nOvershoot2
    if(nT_max < MAX_TIMES_LIMIT)
    {
        for(i=nT_max+1; i<DATA_PTS; i++)
        {
            if(m_pDiagBuffer[i+STEP_CHANGE_INDEX] < nY_min) //U fix as in ESD, was nY_max
            {
                nY_min = m_pDiagBuffer[i+STEP_CHANGE_INDEX];
                //U nT_min = i;
            }
        }
    }

    //find the minimum delta position and time but only before the peak
    //this is used to detect D too large
    nDY_min = nDY_max;
    nT_DY_min = nT_DY_max;
    if(nT_max > (nT_DY_max+7) ) ///AK:Q: What are these 7 and 5? And 5 and 8 and 20 below? Are those 5's the same? 8's?
    {                           /// DZ: A rough number significant enough to separate these times.
        for(i=(nTau_m+1); i<(nT_max-5); i++)
        {
            if(nTuneArray[i] < nDY_min)
            {
                nDY_min = nTuneArray[i];
                nT_DY_min = i;
            }
        }
    }
    tune_xchange->DY_min = nDY_min;

    //look at the DYmin from above and determine if D is too large
    bool_t bD_Large = false;
    if( (nT_DY_min < (nT_max-5)) && (nDY_max > (8*nDY_min)) &&
       (m_pDiagBuffer[nT_DY_min+STEP_CHANGE_INDEX] < POS_STD_4_75) && (nTau_avg < 20) )
    {
       //????
        //Quick fix of index TFS:3968 since the loop above is hard to lower bound
        s16 ind1 = MAX((nT_DY_min-2), 0);
//        if(( (nTuneArray[(nT_DY_min-2)] < (nDY_max/8)) &&
        if(( (nTuneArray[ind1] < (nDY_max/8)) &&
          (nTuneArray[nT_DY_min+2] < (nDY_max/8)) &&
          (nTuneArray[nT_DY_min+6] > (nDY_max/4)) ) || (nDY_min < (nDY_max/8)) )
        {
            bD_Large = true;
        }
    }
    tune_xchange->bD_Large = bD_Large;

    //calculate overshoot
    // *** extreme case where position approaches 3% but slowly
    //      max > last so will calculate overshoot even though
    //      valve never made it to final value
    nY_last = MAX(nY_last, TWO_PCT_328); ///AK:Q: Why?
    /// DZ: to avoid unreasonable Overshoot.
    tune_xchange->Y_last = nY_last; //U: Is the handover value this or previous nY_last?
    tune_xchange->nOvershoot_p = tune_xchange->nOvershoot;
    if (nY_max < nY_last)
    {
        tune_xchange->nOvershoot = 0;
    }
    else
    {
        tune_xchange->nOvershoot = (s16)((((nY_max-nY_last))*100)/(s32)nY_last); //lint !e414 Lint bug TFS:8331 - See nY_last above
    }
    if (nY_min > nY_last)
    {
        tune_xchange->nOvershoot2 = 0;
    }
    else
    {
        tune_xchange->nOvershoot2 = (s16)((((nY_last-nY_min))*100)/(s32)nY_last);
    }

    //Magic output to local UI
    s32 ui_out = (tune_xchange->nT_90*100) + tune_xchange->nOvershoot;
    WRITE_NUMBER(ui_out, 0);
}

/** \brief Try to  preliminarlity stabilize the valve someplace between POS_STAY_LOW and POS_STAY_HIGH,
    preferably at 40% of valve travel (AK:range?), by changing P and I parameters.
NOTE. The function does the best it can and termination on time-out is not considered a failure.
\return 0 on success, 1 on failure (process canceled or bias change flag is set).
*/
static s8 CheckPosStablize(u8_least index, PIDData_t *pid)
{
    s16 nPosScaled, nManualPos;
    s16 j = 0;
    do
    {
        nPosScaled = control_GetPosition();
        if( (nPosScaled<POS_STAY_LOW) || (nPosScaled>POS_STAY_HIGH) )
        {
            nManualPos=(s16)(FORTY_PCT);
        }
        else
        {
            nManualPos = nPosScaled;
        }
        mode_SetControlMode(CONTROL_MANUAL_POS, nManualPos);
        if (CheckStable(index, pid))
        {
            return 1;    // early exit - user cancelled ///AK:NOTE: Or Bias change
        }

///AK:Q: Error calculations need to be explained - here and in the loop test below
        // DZ: basically to see if valve is not moving fast enough
        if( (ABS(m_pPosErr->err7-m_pPosErr->err1)<PT1_PCT_16) && (m_pPosErr->err_abs>PT6_PCT_98) &&
            (ABS((s32)m_pPosErr->err7)>PT6_PCT_98 ) )
        {
///AK:Q: Sort of undo what CheckStable() did? Except limits and PAdjust (?)
            // DZ: Yes.
            if(pid->P < P_NOT_HIGH)
            {
                pid->P = (u16)Change20Pct((s16)pid->P, true);
            }
            if(pid->I > I_MID)
            {
                pid->I = (u16)Change20Pct((s16)pid->I, false);
            }
            tune_LimitPID(pid); //AK: That was missing
        }
        j++;
    }while((  ( (m_pPosErr->err_abs>HALF_PCT_82) ||
              (ABS(m_pPosErr->err7)>HALF_PCT_82)) && (j<COUNT_20) ) || (j<COUNT_3));
    return 0;
}

/** \brief This function tries to do its best in stabilizing the valve within 1% error tube.
It does so by scaling proportional gain(s) down and integral up, using CheckStable().
It doesn't fail if it cannot stabilize, settling on the timeout's PID values.
\return 1 on failure (process canceled or bias change flag set) or 0 on success
*/
static s8 tune_Stabilize(u8_least index, PIDData_t *pid)
{
    s8 i = STABLE_TRY_NUM;      //the timeout - 40, i.e., 40*2.5s=10s - is selected empirically
    ///NOTE: Max scaling down: .80**40=.00013 up: 1.2**40=1469.77
    do
    {
       //in phase 1 display the P term
        WRITE_NUMBER((s32)pid->P, 0);
        if (CheckStable(index, pid) == true)
        {
            return 1;    // early exit - process cancelled Or Bias changed
        }
        i--;

    //detect if valve has moved
    }while( (i>0) && ((m_pPosErr->err_abs>ONE_PCT_164) || (ABS((s32)m_pPosErr->err7)>ONE_PCT_164)) );
    return 0;
}

/** \brief If the recent error trajectory is outside .5% tube, reduce proprtional gains in both directions
and increase the I coefficient in a hope to stabilize the valve.
\return true on failure (process canceled or bias change flag is set), false on success
*/
static bool_t CheckStable(u8_least index, PIDData_t *pid)
{
    UNUSED_OK(index);
    //AK:TODO: Why not the latest .err ?
    if(( (m_pPosErr->err7>HALF_PCT_82) && (m_pPosErr->err1<-HALF_PCT_82)) || //If errors are outside the tube
     ( (m_pPosErr->err7<-HALF_PCT_82) && (m_pPosErr->err1>HALF_PCT_82)))
    {
        //AK:TODO: Need to parse DZ's "No" and see what will happen in unintended cases.
        //      [Maybe, Pfill=P and Pexhaust=P+PAdjust could be better params than P and PAdjust]
        if(pid->P > P_NOT_LOW)
        {
            pid->P = (u16)Change20Pct((s16)pid->P, false); ///AK:Q: Can go below tune_LimitPID() limit. Is it intended?
            // DZ: No.
        }
        pid->PAdjust = Change20Pct(pid->PAdjust, false); ///AK:Q: If negative, has a net effect of increasing. Is it intended?
        // DZ: No

        if(pid->I < I_NOT_HIGH )
        {
            pid->I = (u16)Change20Pct((s16)pid->I, true); ///AK:Q: Can go above tune_LimitPID() limit. Is it intended?
            // DZ: No
        }
    }
    //Set new live PID parameters atomically
    tune_LimitPID(pid); //AK: That was missing
    ErrorCode_t err = tune_SetCurrentPIDData(pid);
    MN_DBG_ASSERT(err == ERR_OK);
    UNUSED_OK(err); //for release build

    if (control_GetBiasChangeFlag() > 0) //AK:TODO: make it !=.
    {
        return true;
    }

    /* Per DZ, the intention of Wait is to let the new control parameter to have a chance play the role.
    On a slow valve, which this function makes slower, we may do excessive gain reduction - and eventually fail on time
    So, I (AK) added wait for stable position
    */
    if(process_WaitForTime(T2_500))
    {
        return true;
    }
    return !util_WaitForPos(T0_050,  STABLE_POS_TEST, false);
}

static s16 Change10Pct(s16 nValue, bool_t bIncrease)
{
    // DZ: 8/23/06
    // This function is internally called to change an integer value by about 10%
    // parameters description
    // s16 nValue:  the input to be changed
    // bool_t bIncrease: true for increasing and false for decreasing.
    // return an increased or decreased value based on input nValue;
    if (bIncrease == true)
    {
        return (s16)((11*(s32)nValue)/10);
    }
    else
    {
        return (s16)((9*(s32)nValue)/10);
    }
}

static s16 Change20Pct(s16 nValue, bool_t bIncrease)
{
    // DZ: 8/23/06
    // This function is internally called to change an integer value by about 20%
    // parameters description
    // s16 nValue:  the input to be changed
    // bool_t bIncrease: true for increasing and false for decreasing.
    // return an increased or decreased value based on input nValue;
    if (bIncrease == true)
    {
        return (s16)((6*(s32)nValue)/5);
    }
    else
    {
        return (s16)((4*(s32)nValue)/5);
    }
}

static void tune_LimitPID(PIDData_t *pid)
{
    // DZ: 8/23/06
    // This function is internally called to check and limit control parameters
    // to predefined ranges.
    pid->P = CLAMP(pid->P, P_NOT_LOW, P_HIGH_LIMIT);
    u16 pid_Imax = MIN(pid->P, I_NOT_HIGH);
    pid->I = CLAMP(pid->I, I_MIN, pid_Imax);
    pid->D = MIN(pid->D, D_HIGH_LIMIT);
    pid->PAdjust = CLAMP(pid->PAdjust, PADJ_LOW_LIMIT, PADJ_HIGH_LIMIT);

    if( (pid->P+pid->PAdjust)<P_LOW_LIMIT)
    {
        /* Need to increase PAdjust. Do it by the smallest amount possible
        */
        pid->PAdjust = (s16)MAX(P_LOW_LIMIT - (s32)pid->P, pid->PAdjust);
        /* PROOF
        1. P+Padjust = P + MAX(P_LOW_LIMIT-P, {...}) >= P+(P_LOW_LIMIT-P) = P_LOW_LIMIT
        2. Padjust is within its range if
            P_LOW_LIMIT - P <= PADJ_HIGH_LIMIT, or
            P >= P_LOW_LIMIT-PADJ_HIGH_LIMIT, which is always the case
        */
    }
    pid->Beta = CLAMP(pid->Beta, BETA_LOW_LIMIT, BETA_HIGH_LIMIT);
}

#ifndef NDEBUG //for debugging: inspect how the macros expand
#ifndef _lint
__root s32 bhl= BOOST_HIGH_LIMIT;
__root s32 dzhl= DEADZONE_HIGH_LIMIT;
__root s32 bsr = BAND_SUPPLY_RATIO;
#endif // _lint
#endif //NDEBUG

