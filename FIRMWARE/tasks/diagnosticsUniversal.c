/**
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/

/*
    CPU: Any

    \file diagnosticsUniversal.c
    \brief Performs open loop valve and actuator diagnositcs.
*/
#include "mnwrap.h"

#include "timebase.h" //for times
#include "valveutils.h" //for WaitStable...

//Other Module includes -- these CANNOT be order dependent
#include "timer.h"
#include "pwm.h"
#include "bufferhandler.h"
#include "errcodes.h"
#include "mnassert.h"
#include "process.h"
#include "sysio.h"
#include "hartdef.h"
#include "ctllimits.h"
#include "pressures.h"

#include "diagnostics.h"
#include "control.h"

#define EXTDIAG_INLINE_COMPLETION_TEST 0

#if EXTDIAG_INLINE_COMPLETION_TEST
//These are progression steps (mostly for debugging) posing as % complete
#define EXTDIAG_STABLEBIASCHANGE3 1
#define EXTDIAG_STABLEPRES_EOSCAN1 1
#define EXTDIAG_STABLEPRES_EOSCAN2 1
#endif //EXTDIAG_INLINE_COMPLETION_TEST

#define EXTDIAG_STABLEBIAS_2ND_DIR 1
#define EXTDIAG_STABLEBIAS 2
#define EXTDIAG_STABLEBIASCHANGE1 1
#define EXTDIAG_STABLEBIASCHANGE2 1
#define EXTDIAG_STABLEBIASCHANGE_STARTPOS1 1
#define EXTDIAG_STABLEBIASCHANGE_STARTPOS2 1
#define EXTDIAG_STABLEBIASCHANGE3 1
#define EXTDIAG_STABLEBIAS_ENDPOS 1
#define EXTDIAG_2ND_SCAN_START 60

//structures used internally
typedef struct bias_change_t                //prameters setup by prepare routine to control signature
{
    pos_t SpecifiedStartPosition;           //user entered start position
    pos_t SpecifiedEndPosition;             //user entered end position
    pos_t PreparationStartPosition;         //limited in range start position for preparation
    pos_t PreparationEndPosition;           //limited in range end position for preparation
    s32   BiasPer10Ticks;                   //amount to increment bias (scaled up for more resolution)
    s32    Slope;                           //pressure = position * Slope + Offset
    s32    Offset;
    bias_t BiasRate;                        //estimated bias change pressure count change (scaled)
    bool_t bIPIncreasing;                   //ip increasing when going from start to end
    bool_t bDirectionIncreasing;            //flag for increasing or decreasing position
    bool_t bStartPositionOutsideRange;      //flag when start is outside of 0-100
    bool_t bEndPositionOutsideRange;        //flag when end is outside of 0-100
    bool_t bSecondDirection;                //flag indicating that we have finished one direction and are going in the other dir
} bias_change_t;

typedef struct EndConditions_t              //parameters setup by setstartposition to control scan
{
    bias_t BiasStartAtLimit;                //starting bias when start is out of range
    pres_t PressureAtLimit;                 //pressure at the end of travel (full scale)
    pres_t StartPressure;                   //when position is outside of 0-100, pressure to start ramping at
    bias_t BiasAtStartPressureScaled;       //bias to go to starting pressure (scaled)
    pres_t EndPressure;                     //ending pressure if position is outside of 0-100
    pres_t LastPressure;                    //used to watch for pressure not changing
    u16    StableCount;                     //used to watch for pressure not changing
} EndConditions_t;


//local function prototypes
static procresult_t diag_ExtSignatureScanNew(const bias_change_t* bc, EndConditions_t* ec, s16 *procdetails);
static procresult_t diag_ExtSignaturePrepare(bias_change_t* bc, u16_least Speed);
static procresult_t diag_ExtSignatureSetToStartPosition(bias_change_t* bc, EndConditions_t* ec);
static procresult_t diag_WaitStableBiasChange(bias_t NewBias, u16 nTime, HardPos_t NoiseBandPosition,
                        pres_t NoiseBandPressure);
static bool_t diag_EndOfScan(const bias_change_t* bc, EndConditions_t* ec, s16 *procdetails);
static bool_t  CheckAcceleratedBias(bool_t bIPIncreasing, bias_t* pBias, const EndConditions_t* ec);
static s32 LimitWithSign(s32 Number, u32 LowLimit, u32 HighLimit);

//defines
#define SLOPE_SCALE_SHIFT 10
#define SLOPE_SCALE_FACTOR ((s32)(1u<<SLOPE_SCALE_SHIFT))  //1024
#define MIN_BIAS_SMALL_STEP 50
#define TEN_TICKS (LCL_TICKS_PER_SEC/10)
#define MAX_SMALL_STEP 500
#define PSI_03 ( STD_FROM_PSI(3.0))
#define PSI_01 ( STD_FROM_PSI(1.0))
#define STABLE_COUNT 200u  //10 second - changed from 60 - 3 seconds
#define TICKS_PER_INCREMENT 10u
#define ACCELERATE_START 8
#define ACCELERATE_INC 1
#define ACCELERATE_DIVISOR 16
#define BIAS_SCALE_SHIFT 6
#define BIAS_SCALE_FACTOR ((s32)(1u<<BIAS_SCALE_SHIFT))   //64
#define BIAS_PER_MIN ((u32)(0.2*BIAS_SCALE_FACTOR))  //increment bias 1 only every 5 times
#define BIAS_PER_MAX ((u32)(100*BIAS_SCALE_FACTOR))  //increment bias 1000 every second
//#define IN_RANGE_POSITION_MIN POSITION_05
//#define IN_RANGE_POSITION_MAX POSITION_95
#define REQUIRED_MOVEMENT POSITION_03

/** \brief sets or increments %complete
\param increment - if <0, sets -increment, otherwise increments by increment
*/
static void diag_UpdatePercentComplete(s8_least increment)
{
    u8 base;
    if(increment < 0)
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

/** \brief Waits for the valve to become stable and returns the bias value.
  \param[in] nStdPos - the UN_ADJUSTED position in unadjusted standard range at which to stabilize the valve
  \param[in] nTime - the time in timer ticks between tests to check if the valve has moved
  \param[in] nPosDB - the amount of position change that is considered just noise
  \param[in] nPresDB - the amount of pressure change that is considered just noise
  \return   the IP output value when the valve is stable
*/
static bias_t util_GetStableBias1(pos_t nStdPos, u16 nTime, HardPos_t nPosDB, pres_t nPresDB)
{
    //UNUSED_OK(nPresDB);
    bias_t Bias = (bias_t)BIAS_ERR;

    //put the device in manual mode at the desired position
    s32 sp;
    ctlmode_t ctlmode = mode_GetIntendedControlMode(&sp);
    mode_SetControlMode(CONTROL_MANUAL_POS, nStdPos);

    // check for cancel
    if(process_WaitForTime(T4_000))
    {
        //keep error - user or error cancel
    }
    else if(!util_WaitForPos(nTime, nPosDB, true)) //let's go to setpoint (new)
    {
        //keep error - user or error cancel
    }
    else if(!util_WaitForPos(nTime, nPosDB, true)) //let's go to setpoint (new, once again)
    {
        //keep error - user or error cancel
    }
#if 0
    else if(!util_WaitStablePosPres(nTime, nPosDB, nPresDB)) //let pressure stabilize
    {
        //keep error - user or error cancel
    }
    else if(process_WaitForTime(T2_000))
    {
        //keep error - user or error cancel
    }
#endif
    else
    {
        Bias = control_GetBias();
    }
    
    //Restore saved control mode
    mode_SetControlMode(ctlmode, sp);
    UNUSED_OK(nPresDB);

    return Bias;
}

/** \brief do a open loop signature

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
                     pos_t StartPosition, pos_t EndPosition, u16 Speed, u8_least DiagDirection, s16 *procdetails)
{
    procresult_t procresult;
    bias_change_t BiasFirst;
    bias_change_t BiasSecond;
    EndConditions_t EndConditions;
    bool_t bSamplingStarted = false;

    //Prepare for open loop signature by finding bias increment for proper speed
    //  Must measure the bias speed in the correct direction of movement to
    //  deal with hysteresis
    BiasFirst.SpecifiedStartPosition = StartPosition;
    BiasFirst.SpecifiedEndPosition = EndPosition;
    BiasFirst.bSecondDirection = false;
    // BiasFirst.complete = 0;
    procresult = diag_ExtSignaturePrepare(&BiasFirst, (u16_least)Speed);

    if(procresult == PROCRESULT_OK)
    {
        //take care of reverse direction if BOTH WAYS is specified
        if(DiagDirection == DIAGDIR_UPDOWN)
        {
            //reverse the start and end positions - leave other parameters the same
            BiasSecond.SpecifiedStartPosition = EndPosition;
            BiasSecond.SpecifiedEndPosition = StartPosition;
            BiasSecond.bSecondDirection = true;
            //BiasSecond.complete = BiasFirst.complete; //=5
            //process_SetProcessProgress(BiasSecond.complete);
            procresult = diag_ExtSignaturePrepare(&BiasSecond, (u16_least)Speed);
            //BiasFirst.complete = BiasSecond.complete; //=10
        }
    }

    //now do the scan
    if(procresult == PROCRESULT_OK)
    {
        //get to starting position (but stay in range if start position < 0 or > 100)
        procresult = diag_ExtSignatureSetToStartPosition(&BiasFirst, &EndConditions);
    }

    if(procresult == PROCRESULT_OK)
    {
        //start sampling first direction
        (void)buffer_SuspendSampling(DIAGBUF_DEFAULT);   //just in case (and to set skip=0)
        ErrorCode_t err = buffer_StartSampling(
                         DIAGBUF_DEFAULT,
                         TaskContext, //That's where we are sampling now
                         sample_func,
                         DIAG_MAX_SAMPLES, //That's how much we can save in a log file, not MAX_NUM_DSAMPLES(EXTDIAG_HEADERSZ),
                         EXTDIAG_HEADERSZ/2U,
                         NULL);
        if(err != ERR_OK)
        {
            procresult = PROCRESULT_FAILED;
        }
        else
        {
            bSamplingStarted = true;
        }
    }

    if(procresult == PROCRESULT_OK)
    {
        //start ramping the pressure
        procresult = diag_ExtSignatureScanNew(&BiasFirst, &EndConditions, procdetails);

        //pause sampling
        u16 skip = buffer_SuspendSampling(DIAGBUF_DEFAULT);
        SetSamplesFirstDirection();  //save the number of points sampled

        //if we need to do the second direction
        if( (procresult == PROCRESULT_OK) && (DiagDirection == DIAGDIR_UPDOWN) )
        {
            diag_UpdatePercentComplete(-EXTDIAG_2ND_SCAN_START);
    
            //get to starting position (but stay in range if start position < 0 or > 100)
            //  but since this is the 2nd direction, just stay where we are
            procresult = diag_ExtSignatureSetToStartPosition(&BiasSecond, &EndConditions);

            if(procresult == PROCRESULT_OK)
            {
                //resume sampling
                buffer_ResumeSampling(DIAGBUF_DEFAULT, skip); //Make the next sample go in the buffer

                //start the scan
                procresult = diag_ExtSignatureScanNew(&BiasSecond, &EndConditions, procdetails);
            }
        }
    }

    //stop sampling in all cases
    if(bSamplingStarted)
    {
        buffer_StopSampling(DIAGBUF_DEFAULT);
        SetSamplesLastDirection();  //save total number of points
    }

    if(procresult == PROCRESULT_OK)
    {
        //fill in the data in the header record
        FillExtDiagHeader(procdetails);
    }


    return procresult;
}

/** \brief moves the valve at a constant rate for an ext actuator test

moves the valve at a constant rate for an ext actuator test
\param[in] bc - data set up in prepare to control this scan
\param ec - data set up at start position to control this scan
\return false if there is an error, true if completed

*/
static procresult_t diag_ExtSignatureScanNew(const bias_change_t* bc, EndConditions_t* ec, s16 *procdetails)
{
    s32 BiasScaled;
    bool_t EndOfScan=false;
    bool_t bEndAccelerate = false;
    bool_t bStartAccelerate = false;
    s32 BiasAccelerateFactor;
    s32 BiasAccelerateIncrement;
    procresult_t procresult = PROCRESULT_OK;

    //initialize the loop timer
    tick_t LastTime  = timer_GetTicks();
    BiasAccelerateIncrement = 0;

    //if we are starting out of range, move the pressure faster
    if(bc->bStartPositionOutsideRange)
    {
        bStartAccelerate = true;
    }
    else
    {
        bStartAccelerate = false;
    }

    //loop and ramp the bias until we finish
    //BiasScaled = BIAS_SCALE_FACTOR * pwm_GetValue();  //initialize the Bias incremented in the loop
    //BiasScaled = BIAS_SCALE_FACTOR * control_GetBias();  //initialize the Bias incremented in the loop
    bias_t Bias1 = util_GetStableBias1(vpos_GetScaledPosition(), T1_000, NOISE_BAND_STABLE,
                    NOISE_BAND_PRES_STABLE);

    //BiasScaled = BIAS_SCALE_FACTOR * control_GetBias();  //initialize the Bias incremented in the loop
    if( Bias1 == (bias_t)BIAS_ERR)
    {
        procresult = PROCRESULT_FAILED;
    }
    else
    {

        BiasScaled = BIAS_SCALE_FACTOR * Bias1;  //initialize the Bias incremented in the loop
        do
        {
            //we increment the bias every 10 ticks
            tick_t timediff = timer_GetTicksSince(LastTime);
            if(timediff>=TICKS_PER_INCREMENT)
            {
                if(bStartAccelerate || bEndAccelerate)
                {
                    //if we are accelerating increment faster and keep increasing that
                    BiasAccelerateIncrement += ACCELERATE_INC;
                    BiasAccelerateFactor = ACCELERATE_START + BiasAccelerateIncrement/ACCELERATE_DIVISOR;
                    BiasScaled += bc->BiasPer10Ticks * BiasAccelerateFactor;
                    if(bStartAccelerate)
                    {
                        bStartAccelerate = CheckAcceleratedBias(bc->bIPIncreasing, &BiasScaled, ec);
                    }
                }
                else
                {
                    //if we are not accelerating just increment by our constant amount
                    BiasScaled += bc->BiasPer10Ticks;
                }

                BiasScaled = CLAMP(BiasScaled, MIN_DA_VALUE*BIAS_SCALE_FACTOR, MAX_DA_VALUE*BIAS_SCALE_FACTOR); //limit bias
                ErrorCode_t err = sysio_SetForcedCtlOutput((u16)(BiasScaled/BIAS_SCALE_FACTOR), PWMEXACT);
                if(err != ERR_OK)
                {
                    procresult = PROCRESULT_FAILED;
                    break;
                }

                LastTime += timediff;

                //check to see if we have finished
                EndOfScan = diag_EndOfScan(bc, ec, procdetails);

                //move quickly past 'tail' if end is out of range
                if(EndOfScan && bc->bEndPositionOutsideRange && !bEndAccelerate)
                {
                    //reset end conditions and continue ramping until supply pressure (but ramp faster)
                    bEndAccelerate = true;
                    ec->EndPressure = ec->PressureAtLimit;
                    EndOfScan = false; //continue ramping until we reach the end of tail
                    BiasAccelerateIncrement = 0;
                }
            }

            if(process_WaitForTime(1U)) //let periodic services (mopup and WD) run
            {
                EndOfScan = true; //canceled - so end the scan
                procresult = PROCRESULT_CANCELED;
            }

        }while(!EndOfScan);
    }
    
    //make sure last point is put in buffer
    if(process_WaitForTime(TICKS_PER_INCREMENT)) //let periodic services (mopup and WD) run
    {
        procresult = PROCRESULT_CANCELED;
    }

    return procresult;
}

/** \brief checks to see if starting acceleration has reached its target pressure

checks to see if starting acceleration has reached its target pressure
\param[in] bool_t bIPIncreasing - true if IP is increasing in this scan
\param[in] bias_t* pBias - pointer to the current bias (scaled)
\param[in] EndConditions_t* - data set up at start position to control this scan
\return false if we have reached the end (acceleration should stop)

*/
static bool_t  CheckAcceleratedBias(bool_t bIPIncreasing, bias_t* pBias, const EndConditions_t* ec)
{
    bool_t End=true;

    //if we have reached the starting pressure bias, limit the bias (in case we have gone too far)
    //   and set the flag to stop accelerating
    if(bIPIncreasing)
    {
        if(*pBias > ec->BiasAtStartPressureScaled)
        {
            *pBias = ec->BiasAtStartPressureScaled;  //dont let it exceed the start bias
            End = false;
        }
    }
    else
    {
        if(*pBias < ec->BiasAtStartPressureScaled)
        {
            *pBias = ec->BiasAtStartPressureScaled; //dont let it exceed the start bias
            End = false;
        }
    }

    return End;
}


/** \brief prepares for an extended signature test by gathering bias/pressure rate

  prepares for an extended signature test by gathering bias/pressure rate
  \param[in] bias_change_t* - structure to hold the parameters determined here
  \param[in] u16_least Speed - the speed to scan in position units
  \return procresult_t - error code
*/
static procresult_t diag_ExtSignaturePrepare(bias_change_t* bc, u16_least Speed)
{
    bias_t Bias1; //, Bias2 = 0;
    pres_t Pressure1 = 0; //, Pressure2 = 1;
    pos_t  Position1 = 0;
    bias_t SmallBiasStep = 0;
    bias_t BiasEnd;
    pres_t PressureEnd=0;
    procresult_t procresult = PROCRESULT_OK;

    pos_t Position2=0;
    pos_t Ends[Xends];

    //set up flags that indicate whether this scan increases position and increases IP
    bc->bDirectionIncreasing = (bc->SpecifiedEndPosition > bc->SpecifiedStartPosition);
    bc->bIPIncreasing = pos_GetStopAdjustment(Ends);//pos_GetPositionConf(NULL)->bATO;
    if(!bc->bDirectionIncreasing)
    {
        //if direction is decreasing reverse ipincreasing flag
        bc->bIPIncreasing = !bc->bIPIncreasing;
    }

    //for preparation we must be between 5 and 95 (5 less than open stop adjusted max)
    pos_t LowestInRange = Ends[Xlow] + POSITION_05;
    pos_t HighestInRange = (pos_t)CLAMP((STANDARD_100*STANDARD_100)/(s32)Ends[Xhi],  MIN_ALLOWED_POSITION, MAX_ALLOWED_POSITION);
    HighestInRange -= POSITION_05;

    bc->PreparationStartPosition = CLAMP(bc->SpecifiedStartPosition, LowestInRange, HighestInRange);
    bc->PreparationEndPosition = CLAMP(bc->SpecifiedEndPosition, LowestInRange, HighestInRange);
    MN_ASSERT(equiv(bc->PreparationEndPosition>bc->PreparationStartPosition, bc->bDirectionIncreasing));


    //move to start position
    Bias1 = util_GetStableBias1(bc->PreparationStartPosition, T1_000, NOISE_BAND_STABLE,
                    NOISE_BAND_PRES_STABLE);
    if(Bias1 == (s16)BIAS_ERR) //error case
    {
        procresult = PROCRESULT_FAILED;
    }

    diag_UpdatePercentComplete(EXTDIAG_STABLEBIAS);
    
    if(procresult == PROCRESULT_OK)
    {
        if(!CheckIPLimits(Bias1))
        {
            procresult = PROCRESULT_FAILED;
        }
    }

    if(procresult == PROCRESULT_OK)
    {
        mode_SetControlMode(CONTROL_OFF, SmallBiasStep);  //note - 2nd argument is not relevant
        procresult = diag_WaitStableBiasChange(Bias1, T1_000, NOISE_BAND_STABLE,
                NOISE_BAND_PRES_STABLE);
    }

    diag_UpdatePercentComplete(EXTDIAG_STABLEBIASCHANGE1);
    //this moves us in the right direction to get on the right hysteresis curve
    if(procresult == PROCRESULT_OK)
    {
        //save the bias change to use in testing valve movement
        if(bc->bIPIncreasing)
        {
            SmallBiasStep = MIN_BIAS_SMALL_STEP;
        }
        else
        {
            SmallBiasStep = -MIN_BIAS_SMALL_STEP;
        }

        Bias1 += SmallBiasStep;
        procresult = diag_WaitStableBiasChange(Bias1, T1_000, NOISE_BAND_STABLE,
                        NOISE_BAND_PRES_STABLE);
        Pressure1 = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];
        Position1 = vpos_GetScaledPosition();
        
        diag_UpdatePercentComplete(EXTDIAG_STABLEBIASCHANGE2);
    }

    //lint -esym(644, Bias2, Pressure2)  Lint misses procresult dependency
    bias_t Bias2;
    pres_t Pressure2;
    //continue moving slowly to get info to calc biasrate
    if(procresult == PROCRESULT_OK)
    {
        do //increment bias until we get at least 3% movement
        {
            Bias2 = Bias1 + SmallBiasStep;
            procresult = diag_WaitStableBiasChange((bias_t)Bias2, T1_000, NOISE_BAND_STABLE,
                            NOISE_BAND_PRES_STABLE);
            Pressure2 = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];
            Position2 = vpos_GetScaledPosition();
            SmallBiasStep += SmallBiasStep;  //double it
        } while( (mn_abs(Position2-Position1)<REQUIRED_MOVEMENT) && mn_abs(SmallBiasStep)<MAX_SMALL_STEP );
        diag_UpdatePercentComplete(EXTDIAG_STABLEBIASCHANGE3);
#if 0 //BAD MOVE: The goal is to be on the correct side of histeresis
        //At this point, the valve may be moving a lot faster than we account for. Let's stabilize it here first
        Bias2 = util_GetStableBias1(Position2, T1_000, NOISE_BAND_STABLE,
                        NOISE_BAND_PRES_STABLE);
        if(Bias2 == (s16)BIAS_ERR) //error case
        {
            procresult = PROCRESULT_FAILED;
        }
#endif
    }

    // move to endposition
    if(procresult == PROCRESULT_OK)
    {
        BiasEnd = util_GetStableBias1(bc->PreparationEndPosition, T1_000, NOISE_BAND_STABLE,
                        NOISE_BAND_PRES_STABLE);
        
        diag_UpdatePercentComplete(EXTDIAG_STABLEBIAS_ENDPOS);
        
        if(BiasEnd == (s16)BIAS_ERR) //error case
        {
            procresult = PROCRESULT_FAILED;
        }
        if(procresult == PROCRESULT_OK)
        {
            if(!CheckIPLimits(BiasEnd))
            {
                procresult = PROCRESULT_FAILED;
            }
        }
        PressureEnd = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];
    }

    //calculations
    if(procresult == PROCRESULT_OK)
    {
#if 1
        s32 BiasDiffBoosted = BIAS_SCALE_FACTOR*(Bias2-Bias1);
        pres_least_t presdiff_bias = Pressure2-Pressure1;
        pres_least_t presdiff_pres = PressureEnd-Pressure1;
        pos_least_t posdiff_pres = bc->PreparationEndPosition - Position1;
        pos_least_t posdiff_bias = Position2 - Position1;
#elif 1 //premature end of scan here
        s32 BiasDiffBoosted = BIAS_SCALE_FACTOR*(Bias2-Bias1);
        pres_least_t presdiff_bias = Pressure2-Pressure1;
        pres_least_t presdiff_pres = PressureEnd-Pressure1;
        pos_least_t posdiff_pres = vpos_GetScaledPosition() - Position1;
        pos_least_t posdiff_bias = Position2 - Position1;
#else
        s32 BiasDiffBoosted = BIAS_SCALE_FACTOR*(BiasEnd-Bias1);
        pres_least_t presdiff_bias = PressureEnd-Pressure1;
        pres_least_t presdiff_pres = PressureEnd-Pressure1;
        
        pos_least_t PositionEnd = vpos_GetScaledPosition();
        pos_least_t posdiff_pres = PositionEnd - Position1;
        
        pos_least_t posdiff_bias = PositionEnd - Position1;
        UNUSED_OK(Pressure2);
#endif
        //calculate open loop bias change per pressure count change (scaled)
        bc->BiasRate = BiasDiffBoosted/presdiff_bias;

        //calculate spring range (actually slope and offset for converting position to pressure)
        bc->Slope = (SLOPE_SCALE_FACTOR*presdiff_pres)/posdiff_pres;
        bc->Offset = Pressure1 - (bc->Slope*(s32)(Position1)/SLOPE_SCALE_FACTOR);

        //calculate bias rate per 10 ticks
        //bc->BiasPer10Ticks = ComputeBiasPer10Ticks((s32)bc->PreparationStartPosition, (s32)bc->PreparationEndPosition,
        //                                               (u32)bc->BiasStart, (u32)bc->BiasEnd, (u32)Speed);
        //lint -e{414} positions not equal tested above - no divide by 0
        bc->BiasPer10Ticks = (s32)(((s32)Speed * BiasDiffBoosted)/((s32)TEN_TICKS*posdiff_bias));
#if 1
        bc->BiasPer10Ticks = CLAMP(bc->BiasPer10Ticks, (bias_t)BIAS_PER_MIN, (bias_t)BIAS_PER_MAX);
        UNUSED_OK(LimitWithSign);
#else
        bc->BiasPer10Ticks = LimitWithSign(bc->BiasPer10Ticks, BIAS_PER_MIN, BIAS_PER_MAX);
#endif
        if(!bc->bDirectionIncreasing)
        {
            bc->BiasPer10Ticks = - bc->BiasPer10Ticks;
        }
    }


    return procresult;
}

/** \brief move the valve to starting position and get on proper hysteresis curve

  move the valve to starting position and get on proper hysteresis curve
  \param[in] none
  \return false if an error
*/
static procresult_t diag_ExtSignatureSetToStartPosition(bias_change_t* bc, EndConditions_t* ec)
{
    bias_t Bias1;
    pres_t PressureCurrent, PressureSupply, PressureStartAtLimit;
    s32 PressureTemp;
    pos_t Position;
    procresult_t result = PROCRESULT_OK;
    pos_t Ends[Xends];

    (void)pos_GetStopAdjustment(Ends);
    pos_t LowestInRange = Ends[Xlow] + POSITION_05;
    pos_t HighestInRange = (pos_t)CLAMP((STANDARD_100*STANDARD_100)/(s32)Ends[Xhi],  MIN_ALLOWED_POSITION, MAX_ALLOWED_POSITION);
    HighestInRange -= POSITION_05;

    PressureSupply = pres_GetPressureData()->Pressures[PRESSURE_SUPPLY_INDEX];

    //set up end conditions
    Position = (pos_t)CLAMP(bc->SpecifiedStartPosition, LowestInRange, HighestInRange);
    bc->bStartPositionOutsideRange = (Position != bc->SpecifiedStartPosition);

    PressureTemp = intscale32(bc->Slope, (s32)bc->SpecifiedStartPosition, bc->Offset, SLOPE_SCALE_SHIFT);
    ec->StartPressure = (pres_t)CLAMP(PressureTemp, PRESSURE_LOW_CUTOFF, PRESSURE_MAX_STD);

    Position = (pos_t)CLAMP(bc->SpecifiedEndPosition,LowestInRange, HighestInRange);
    bc->bEndPositionOutsideRange = (Position != bc->SpecifiedEndPosition);

    PressureTemp = intscale32(bc->Slope, (s32)bc->SpecifiedEndPosition, bc->Offset, SLOPE_SCALE_SHIFT);
    ec->EndPressure = (pres_t)CLAMP(PressureTemp, PRESSURE_LOW_CUTOFF, PRESSURE_MAX_STD);
    ec->LastPressure = 0;
    ec->StableCount = 0;

    if(bc->bIPIncreasing)
    {
        ec->PressureAtLimit = PressureSupply - PSI_01;
        PressureStartAtLimit = PSI_01;
    }
    else
    {
        ec->PressureAtLimit = PSI_01;
        PressureStartAtLimit = PressureSupply - PSI_01;
    }

    if(bc->bSecondDirection)
    {
        if(!bc->bStartPositionOutsideRange)
        {
             //go prep position - do it twice to make sure we are stable at the start position
            //for(u32 i = 0; i<2; ++i)
            {
                Bias1 = util_GetStableBias1(bc->PreparationStartPosition, T1_000, NOISE_BAND_STABLE,
                                NOISE_BAND_PRES_STABLE);
            }
        }
        else
        {
                Bias1 = util_GetStableBias1(bc->SpecifiedStartPosition, T1_000, NOISE_BAND_STABLE, //AK:TODO Fixme
                                NOISE_BAND_PRES_STABLE);
        }
        diag_UpdatePercentComplete(EXTDIAG_STABLEBIAS_2ND_DIR);
        if(Bias1 == (s16)BIAS_ERR) //error case
        {
            result = PROCRESULT_CANCELED;
        }

        //for second direction we are already at the starting position but need to do some calcs
        //Bias1 = pwm_GetValue();
        PressureCurrent = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];

        //calculate bias at starting point (not the limit)
        ec->BiasAtStartPressureScaled
            = BIAS_SCALE_FACTOR * intscale32(bc->BiasRate, -(PressureCurrent - ec->StartPressure), Bias1, BIAS_SCALE_SHIFT);
            ec->BiasAtStartPressureScaled = CLAMP(ec->BiasAtStartPressureScaled, MIN_DA_VALUE*BIAS_SCALE_FACTOR, MAX_DA_VALUE*BIAS_SCALE_FACTOR);
    }
    else
    {
        // ----For Start->End increasing ----------
        if(bc->bDirectionIncreasing)
        {
            //if start is outside of the limits then start pressure is stop - 10%
            if(bc->bStartPositionOutsideRange)
            {
                //start at the pressure that represents -10%
                PressureTemp = intscale32(bc->Slope, (LowestInRange-POSITION_10), bc->Offset, SLOPE_SCALE_SHIFT);
                ec->StartPressure = (pres_t)CLAMP(PressureTemp, PRESSURE_LOW_CUTOFF, PRESSURE_MAX_STD);
            }

            //if end is outside of the limits then end pressure is stop + 10%
            if(bc->bEndPositionOutsideRange)
            {
                PressureTemp = intscale32(bc->Slope, (HighestInRange+POSITION_10), bc->Offset, SLOPE_SCALE_SHIFT);
                ec->EndPressure = (pres_t)CLAMP(PressureTemp, PRESSURE_LOW_CUTOFF, PRESSURE_MAX_STD);            }
        }
        // ----For Start->End decreasing ----------
        else
        {
            //if start is outside of the limits then start pressure is stop + 10%
            if(bc->bStartPositionOutsideRange)
            {
                //start at the pressure that represents -10%
                PressureTemp = intscale32(bc->Slope, (HighestInRange+POSITION_10), bc->Offset, SLOPE_SCALE_SHIFT);
                ec->StartPressure = (pres_t)CLAMP(PressureTemp, PRESSURE_LOW_CUTOFF, PRESSURE_MAX_STD);
            }

            //if end is outside of the limits then end pressure is stop - 10%
            if(bc->bEndPositionOutsideRange)
            {
                PressureTemp = intscale32(bc->Slope, (LowestInRange-POSITION_10), bc->Offset, SLOPE_SCALE_SHIFT);
                ec->EndPressure = (pres_t)CLAMP(PressureTemp, PRESSURE_LOW_CUTOFF, PRESSURE_MAX_STD);
            }

        }

        //go prep position - do it twice to make sure we are stable at the start position
        //for(u32 i = 0; i<2; ++i)
        {
            Bias1 = util_GetStableBias1(bc->PreparationStartPosition, T1_000, NOISE_BAND_STABLE,
                            NOISE_BAND_PRES_STABLE);
            if(Bias1 == (s16)BIAS_ERR) //error case
            {
                result = PROCRESULT_CANCELED;
            }
        }
        diag_UpdatePercentComplete(EXTDIAG_STABLEBIASCHANGE3);

        PressureCurrent = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];

        //calculate bias at start
        if(bc->bStartPositionOutsideRange)
        {
            ec->BiasAtStartPressureScaled = intscale32(bc->BiasRate, -(PressureCurrent - ec->StartPressure), Bias1, BIAS_SCALE_SHIFT);
            //AK:TODO clamp to range
        }
        else
        {
            ec->BiasAtStartPressureScaled = Bias1;
        }
        ec->BiasAtStartPressureScaled *= BIAS_SCALE_FACTOR;
        ec->BiasAtStartPressureScaled = CLAMP(ec->BiasAtStartPressureScaled, MIN_DA_VALUE*BIAS_SCALE_FACTOR, MAX_DA_VALUE*BIAS_SCALE_FACTOR);

        ec->BiasStartAtLimit = intscale32(bc->BiasRate, -(PressureCurrent - PressureStartAtLimit), Bias1, BIAS_SCALE_SHIFT);
        ec->BiasStartAtLimit = CLAMP(ec->BiasStartAtLimit, MIN_DA_VALUE*BIAS_SCALE_FACTOR, MAX_DA_VALUE*BIAS_SCALE_FACTOR);

        //go to open loop moving to 0 pressure if necessary
        if(result == PROCRESULT_OK)
        {
            if(bc->bStartPositionOutsideRange)
            {
                //outside of range - start at the limit (0 or supply pressure)
                result = diag_WaitStableBiasChange(ec->BiasStartAtLimit,  T1_000, NOISE_BAND_STABLE,
                                        NOISE_BAND_PRES_STABLE);
            }
            else
            {
                //inside range - start where we are
                result = diag_WaitStableBiasChange(ec->BiasAtStartPressureScaled/BIAS_SCALE_FACTOR,  T1_000, NOISE_BAND_STABLE,
                                        NOISE_BAND_PRES_STABLE);
            }

            diag_UpdatePercentComplete(EXTDIAG_STABLEBIASCHANGE_STARTPOS1);
        }
    }

    //wait additional for things to get more stable
    if(result == PROCRESULT_OK)
    {
        if(!util_WaitStablePosPres(T1_000, NOISE_BAND_STABLE,  NOISE_BAND_PRES_STABLE))
        {
            result = PROCRESULT_CANCELED;        // early return - user cancel
        }
    }
    diag_UpdatePercentComplete(EXTDIAG_STABLEBIASCHANGE_STARTPOS2);

    return result;
}


/** \brief checks to see if we have reached the end of the open loop signature scan

  checks to see if we have reached the end of the open loop signature scan
  \param[in] const bias_change_t* bc - initial conditions measured in prepare
  \param[in] EndConditions_t* ec - end conditions measured in set to position
  \return bool_t - true if end of scan is reached
*/
static bool_t diag_EndOfScan(const bias_change_t* bc, EndConditions_t* ec, s16 *procdetails)
{
    //end conditions
    //  IP increasing
    //      position reaches end position
    //      pressure reaches end pressure
    //      pressure within 1psi of supply pressure
    //      pressure not changing for n seconds (after we've started moving)
    //
    //  IP decreasing
    //      position reaches end position
    //      pressure reaches end pressure
    //      pressure less than 1psi
    //      pressure not changing for n seconds
    //
    //just for now
    pos_t Position = vpos_GetScaledPosition();
    pres_t Pressure = pres_GetPressureData()->Pressures[PRESSURE_ACT1_INDEX];
    pres_t SupplyPressure = pres_GetPressureData()->Pressures[PRESSURE_SUPPLY_INDEX];
    bool_t EndOfScan = false;
    bool_t bCheckForStablePressure=false;

    //check for postion reaching the end
    if(bc->bDirectionIncreasing)
    {
        if(Position > bc->SpecifiedEndPosition)
        {
            EndOfScan = true;
        }
        if(Position > (bc->PreparationStartPosition + REQUIRED_MOVEMENT))
        {
            bCheckForStablePressure = true;
        }
    }
    else
    {
        if(Position < bc->SpecifiedEndPosition)
        {
            EndOfScan = true;
        }
        if(Position < (bc->PreparationStartPosition - REQUIRED_MOVEMENT))
        {
            bCheckForStablePressure = true;
        }
    }

    //check for pressure reaching target or supply or 0
    if(bc->bEndPositionOutsideRange)
    {
        if(bc->bIPIncreasing)
        {
            if(Pressure > ec->EndPressure)
            {
                EndOfScan = true;
            }
            if(Pressure > (SupplyPressure - PSI_03))
            {
                EndOfScan = true;
            }
        }
        else
        {
            if(Pressure < ec->EndPressure)
            {
                EndOfScan = true;
            }
            if(Pressure < (PSI_01))
            {
                EndOfScan = true;
            }
        }
    }

    UNUSED_OK(procdetails);
    //check for pressure not changing
    if(bCheckForStablePressure && (mn_abs(Pressure - ec->LastPressure) < NOISE_BAND_PRES_STABLE))
    {
        ec->StableCount++;
        if(ec->StableCount > STABLE_COUNT)
        {
            EndOfScan = true;
        }
    }
    else
    {
        ec->LastPressure = Pressure;
        ec->StableCount = 0;
    }

    return EndOfScan;
} //lint !e818

/** \brief set the IP and wait until stable

  set the IP and wait until stable
  \param[in] NewBias - the IP value to set
  \param[in] nTime - util_WaitStablePosPres
  \param[in] NoiseBandPosition - util_WaitStablePosPres
  \param[in] NoiseBandPressure - util_WaitStablePosPres
  \return  PROCRESULT_OK if stable, or error if canceled or failed
*/
static procresult_t diag_WaitStableBiasChange(bias_t NewBias, u16 nTime, HardPos_t NoiseBandPosition,
                        pres_t NoiseBandPressure)
{
    procresult_t ret;

    ErrorCode_t err = sysio_SetForcedCtlOutput(NewBias, PWMEXACT);

    if(err != ERR_OK)
    {
        ret = PROCRESULT_FAILED;
    }
    else if(process_WaitForTime(nTime))
    {
        ret=PROCRESULT_CANCELED;
    }
    else if(!util_WaitStablePosPres(nTime, NoiseBandPosition,  NoiseBandPressure))
    {
        ret=PROCRESULT_CANCELED;
    }
    else
    {
        ret = PROCRESULT_OK;
    }
    return ret;

}

/** \brief make absolute value of parameter between limits

  make absolute value of parameter between limits
  \param[in] s32 Number - signed number to limit
  \param[in] u32 LowLimit - (positive)lower limit
  \param[in] u32 HighLimit - (positive)upper limit
  \return s32 Number limited - original sign and LowLimit <= |Number| <= HighLimit
*/
static s32 LimitWithSign(s32 Number, u32 LowLimit, u32 HighLimit)
{
    u32 AbsNumber = (u32)mn_abs(Number);
    bool_t SignPositive = (AbsNumber == (u32)Number);

    AbsNumber = CLAMP(AbsNumber, LowLimit, HighLimit);

    Number = (s32)AbsNumber;
    if(!SignPositive)
    {
        Number = -Number;
    }
    return Number;
}


/* This line marks the end of the source code */

/*
Open Loop Extended Signature Description

The goal of the open loop signature is to ramp the pressure smoothly,
at a constant rate and measure position and pressure while the valve
position moves from the start to the end of the test.
The major problems occur at the ends below 0% and over 100% position
(or higher when there is an open stop adjustment).
When start or end is specified outside of this region, it is expected
that the test will run from 0psi to supply pressure so the user can see
the test results when the valve comes off/on the seat or goes to full
open (however the user doesn't want or need as many points during the
"tails" of the test).  Since to ramp the pressure, the device controller
must be put in open loop (control off), the issue that has been the
hardest to solve in the past is what to set as the starting I/P value
and how fast to ramp the I/P to run the test at the specified rate.
This implementation attempts to solve this by making some initial
measurements in open loop mode and by mapping I/P to pressure then
running the tests monitoring the pressure.

The procedure in the firmware is:
1.	Prepare (measure bias rates) for the first direction.  If BOTH was
    selected prepare the 2nd direction.
2.	Set to 1st direction start position
3.	Start sampling
4.	Scan - ramp the I/P from start to end
5.	Suspend sampling
6.	If BOTH was selected
    a.	Set to 2nd direction start position
    b.	Resume sampling
    c.	Scan - ramp the I/P from start to end
7.	Stop sampling

Details of Function:

Prepare-

8.	Go to the starting position.  Because we cannot always accurately position
    near the stops, use a starting position between 10% and 90% for this step
    if the actual starting position is outside of this range.  Let the valve become stable.
    Measure the I/P (Bias)
9.	Set the positioner to open loop at the current bias.
    Increase the I/P (or decrease as is necessary to move the valve toward the
    end position - in this description we will always describe this as increasing
    bias to move toward the end but the firmware accounts for the other cases) a
    small amount to put us on the right part of the hysteresis curve.  Measure
    the position and pressure.
10.	Increment the I/P in small steps until we move the valve at least 3%.
    We increment the I/P, wait, measure the position change and then double the
    I/P step size until we get enough position movement.  Measure the position and pressure.
11.	Calculate BiasRate as the change in bias per change in pressure measured in
    the 2 preceding steps.  Calculate BiasPer10Ticks as the change in bias needed
    every 50ms to move the valve at the speed requested.  This is computed from
    the bias and position measurements made in the preceding steps.  Note that these
    measurements are made during open loop movement so as to not corrupt them by
    direction reversals due to the control algorithm.
12.	Move to the end position.  Because we cannot always accurately position near
    the stops, use an ending  position between 10% and 90% for this step.
    Let the valve become stable.  Measure the position and pressure.
13.	Calculate the spring range from the first position in step 3 and the end
    position - a linear mapping that takes as input the position and outputs the
    corresponding pressure.  This mapping will be used to determine the pressures
    that should be used at various steps of the test.

Starting Position (and calculate parameters to determine the end of the test)-

14.	Determine if the starting position and/or the ending position are outside
    the 0-100 range (set flags for later use).
15.	Calculate the pressure that corresponds to the end of the test.
16.	Calculate the pressure at the end stop (use 1psi or 3psi less than supply pressure)
17.	Calculate the starting pressure (which may be out of the 0-100 position range).
    Calculate the test end pressure (which may be out of the 0-100 position range).
18.	Go to the starting position but limit it to between 10% and 90%.
    Wait for the position/pressure to become stable.  Save the I/P and pressure.
19.	Calculate the pressure at the starting position (which may be the current position
    or different if the position was limited in the previous step).
    Calculate the I/P that will achieve that pressure.
20.	If the starting position is out of 0-100 range - set the bias to move the pressure to the limit
    If start position is in range - set the bias to move to the start position
21.	Wait for the pressure to become stable.

Scan-

22.	Get the current I/P to use as the starting Bias
23.	If the starting position was outside of range then we are at the limit then
    flag to increment the I/P at an accelerated rate
24.	Loop until we reach end of signature test
    a.	Only check every 10 timer ticks
    b.	If we are accelerating the I/P then increment at a much higher rate (and increase the rate as we go along)
    c.	Otherwise, increment the I/P to achieve the desired test speed
    d.	Set the incremented I/P as the current I/P
    e.	Check for end of test
        i.	If the end position was out of range, reset the end pressure to be the pressure
            at the stop, set the accelerate flag and continue with the loop.
        ii.	If not then the test is finished

*/


/* This line marks the end of the source file */

