/*
Copyright 2004-2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file valveutils.c
    \brief Contains functions used by several other modules

    CPU: Any (with standard C compiler)

    OWNER: Schoonover

    \ingroup Diagnostics
*/

#include "mnwrap.h"
#include "mnassert.h"
#include "pwm.h"
#include "valveutils.h"
#include "timebase.h"
#include "selftune.h" //for tune_GetPIDData()
#include "control.h" //for CONTROL_MANUAL_POS
#include "process.h"
#include "position.h"
#include "devicemode.h"
#include "pneumatics.h"

// for Waits
#define WAIT_STABLE_POS_COUNT       4u
#define WAIT_STABLE_POS_PRES_COUNT  3u
#define STANDARD_TENTH_PERCENT ((pos_t)STD_FROM_PERCENT(0.1))
#define DEADBAND_DIVISOR 8    //used to calculate increment of deadband - make a power of 2


/** \brief This routine waits until the position and pressure quit changing -
            i.e. the valve becomes stable at the setpoint.

  Notes:  In order to prevent the software from waiting forever, after 2 minutes
   the valve is considered stable.

  \param[in] nTime - the time in timer ticks between tests to check if the valve has moved
  \param[in] nPosDB - the amount of position in linearized domain change that is considered just noise
  \param[in] nPresDB - the amount of pressure change that is considered just noise
  \return bool_t true if the valve is stable.  false if user canceled
*/
bool_t util_WaitStablePosPres(u16 nTime, HardPos_t nPosDB, pres_t nPresDB)
{

    HardPos_t NewPos;
    u16             exitTime = 0;
    u8_least        good = 0;
    bool_t          rslt;

    bool_t          DirectionChanged = false;
    bool_t          LastDirectionPlus = false;

    MN_ASSERT(nTime > 0);

    const BoardPressure_t  *BoardPressure    =     pres_GetPressureData();
    const pres_t *pres = &(BoardPressure->Pressures[PRESSURE_ACT1_INDEX]);
    bool_t havePress = (*pres != PRESSURE_INVALID);
    HardPos_t pos = vpos_GetRawPosition();

    // Loop forever
    do
    {
        pos = vpos_GetRawPosition();
        pres_t press = *pres;

        //If time since last test > nTime then
        rslt = process_WaitForTime(nTime);
        if (rslt)
        {
            //If CheckCancelProcess() then return FALSE
            return false;                       // early exit - user cancelled
        }

        //If total time since call is > 2 minutes return TRUE
        exitTime += nTime;

        //If position change since last test < | nPosDB | then
        NewPos = vpos_GetRawPosition();

        bool_t DirectionPlus = NewPos > pos;

            //lint -e{960}  the [mn_]abs function does not have side effects
        if ((mn_abs(pos - NewPos) < nPosDB)
            //If actuator pressure sensor available then
            && ((!havePress)
                //If Pressure change since last test < | nPresDB | then
                || ((u16)mn_abs(press - *pres) < nPresDB)) )
        {
            //Increment stable count
            good++;

            if(!equiv(DirectionPlus, LastDirectionPlus))
            {
                DirectionChanged = true;
            }
        }
        else
        {
            //Reset stable count to 0
            nPosDB += nPosDB/DEADBAND_DIVISOR;     //increase the deadbands so that we never get stuck
            nPresDB += nPresDB/DEADBAND_DIVISOR;
            good = 0;

            DirectionChanged = false;
        }
        LastDirectionPlus = DirectionPlus;
        pos = NewPos;

    //If ((stable count >= 3) & (direction changed) or timeout return TRUE
    }  while (((good < WAIT_STABLE_POS_PRES_COUNT) || (!DirectionChanged)) && (exitTime < T120_000));

    return true;
}

/** \brief Waits for the valve to become stable and returns the bias value.
  \param[in] nStdPos - the UN_ADJUSTED position in unadjusted standard range at which to stabilize the valve
  \param[in] nTime - the time in timer ticks between tests to check if the valve has moved
  \param[in] nPosDB - the amount of position change that is considered just noise
  \param[in] nPresDB - the amount of pressure change that is considered just noise
  \return   the IP output value when the valve is stable
*/
u16 util_GetStableBias(pos_t nStdPos, u16 nTime, HardPos_t nPosDB, pres_t nPresDB)
{
    u16 Bias;

    //put the device in manual mode at the desired position
    s32 sp;
    ctlmode_t ctlmode = mode_GetIntendedControlMode(&sp);
    mode_SetControlMode(CONTROL_MANUAL_POS, nStdPos);

    //todo ERP should we allow cancel here?
    // check for cancel
    if(process_WaitForTime(T4_000))
    {
        return BIAS_ERR;        // early return - user or error cancel
    }
    if(!util_WaitStablePosPres(nTime, nPosDB, nPresDB))
    {
        return BIAS_ERR;        // early return - user cancel
    }
    if(process_WaitForTime(T2_000))
    {
        return BIAS_ERR;        // early return - user cancel
    }

    Bias = pwm_GetValue();

    //Restore saved control mode
    mode_SetControlMode(ctlmode, sp);

    return Bias;
}

/** \brief Waits until the valve becomes stable at the current setpoint
  \param[in] nTime - the time (in timer ticks) between tests of the position
  \param[in] nNoiseDB - the amount of position change that is considered just noise
  \param[in] cFlag - TRUE if waiting for the valve to match the setpoint,
                            FALSE if the waiting for the valve to be stable (at any position)
  \return true if the valve is stable, false if canceled
*/
bool_t util_WaitForPos(u16 nTime,  HardPos_t nNoiseDB , bool_t cFlag)
{
    return (util_WaitForPosExt(nTime, nNoiseDB, cFlag, 0U) == 0U);
}

/** \brief Waits until the valve becomes stable at the current setpoint
  \param[in] nTime - the time (in timer ticks) between tests of the position
  \param[in] nNoiseDB - the amount of position change that is considered just noise
  \param[in] cFlag - TRUE if waiting for the valve to match the setpoint,
                            FALSE if the waiting for the valve to be stable (at any position)
  \param brk_mask - a bitmap of masked-out (and ignored) cancel requests
  \return the bitmap of cancel request (0 means successful completion)
*/
u8_least util_WaitForPosExt(u16 nTime,  HardPos_t nNoiseDB , bool_t cFlag, u8_least brk_mask)
{
    pos_least_t lastPos, curPos;
	s32 Setpoint;
    s32 error;
    u8_least ret; //bitmap of not-masked-out process cancel requests

    MN_ASSERT(nTime > 0);

    (void)mode_GetIntendedControlMode(&Setpoint);
    lastPos = vpos_GetScaledPosition();

    pos_least_t deadBand = tune_GetCurrentPIDData(NULL)->DeadZone + STANDARD_TENTH_PERCENT;      /* 0.1% in case nDeadZone  = 0.0% */
    pos_t stable_pos_test = pos_ConvertHardposDiffToStd(nNoiseDB); //AK: changed for the correct type
    stable_pos_test = ABS(stable_pos_test);

    u8_least good     = 0u;

    do
    {
        ret = process_WaitForTimeExt(nTime, brk_mask);
        if(ret != 0U)
        {
            break;  // cancel request is not masked
        }

        (void)mode_GetIntendedControlMode(&Setpoint);
        curPos = vpos_GetScaledPosition();

        if(cFlag)  // == WAIT_FOR_SETPOINT
        {
            //error is difference from setpoint
            error = curPos - Setpoint;
        }
        else
        {
            //error is difference from last point
            error = curPos - lastPos;
        }

        if( mn_abs(error) < (stable_pos_test + deadBand))
        {
             good++;
        }
        else
        {
            good = 0;
            deadBand += MAX(1, stable_pos_test/DEADBAND_DIVISOR);
            lastPos = curPos;
        }
    } while (good < WAIT_STABLE_POS_COUNT);

    return ret;
}

//-------- Variation of the latter good for non-process contexts ---------------


/** \brief Initializer for Check stable position, good for any context
    \param[in] StableReqState - initialized private structure
    \param[in] nNoiseDB - deadband for position
    \param[in] cFlag - true wait for position versus setpoint; false wait for
                       stable position versus last position
*/
void vutil_StableReq_Init(StablePosReq_t *StableReqState, HardPos_t nNoiseDB, bool_t cFlag)
{
    if(cFlag)
    {
        (void)mode_GetIntendedControlMode(&StableReqState->reference);
    }
    else
    {
        StableReqState->reference = vpos_GetScaledPosition();
    }
    StableReqState->deadBand = tune_GetCurrentPIDData(NULL)->DeadZone + STANDARD_TENTH_PERCENT;      /* 0.1% in case nDeadZone  = 0.0% */
    StableReqState->good = 0U;
    pos_t PosDB = pos_ConvertHardposDiffToStd(nNoiseDB)/DEADBAND_DIVISOR;
    PosDB = ABS(PosDB);
    StableReqState->nPosDB = MAX(1, PosDB);
    StableReqState->cFlag = cFlag;
}

/** \brief Check stable position, good for any context
    \param StableReqState - initialized private structure
    \return true if stable is detected
*/
bool_t vutil_StableReq_Run(StablePosReq_t *StableReqState)
{
    pos_least_t curPos;
    pos_least_t error;

    curPos = vpos_GetScaledPosition();

    if(StableReqState->cFlag)  // == WAIT_FOR_SETPOINT
    {
        (void)mode_GetIntendedControlMode(&StableReqState->reference);
    }
    error = curPos - StableReqState->reference;

    if( mn_abs(error) < (StableReqState->nPosDB + StableReqState->deadBand))
    {
         StableReqState->good++;
    }
    else
    {
        StableReqState->good = 0;
        StableReqState->deadBand += StableReqState->nPosDB;
        StableReqState->reference = curPos; //will be overwritten next run
    }
    return (StableReqState->good > WAIT_STABLE_POS_COUNT);
}

/** \brief Initializer for Check stable position and pressure, good for any context
    \param[out] StableReqState - initialized private structure
    \param[in] nPosDB - deadband for position
    \param[in] nPresDB - deadband for pressure
    \param[in] havePress - indicates we have pressure sensors
*/
void vutil_StablePosPresReq_Init(StableReq_t *StableReqState, HardPos_t nPosDB, pres_t nPresDB, bool_t havePress)
{
    StableReqState->good = 0U;
    StableReqState->nPosDB = nPosDB;
    StableReqState->nPresDB = nPresDB;

    StableReqState->havePress = havePress;
    StableReqState->press = pres_GetMainPressure();
    StableReqState->pos_diff = 0; //actually, don't care
    StableReqState->pos = vpos_GetRawPosition();
}

/** \brief Check stable position, good for any context
    \param StableReqState - initialized private structure
    \return true if stable is detected
*/
bool_t vutil_StablePosPresReq_Run(StableReq_t *StableReqState)
{
    //If position change since last test < | nPosDB | then
    HardPos_t oldPos = StableReqState->pos;
    StableReqState->pos = vpos_GetRawPosition();
    HardPos_t pos_diff = StableReqState->pos - oldPos;
    pres_t newpress = pres_GetMainPressure();
    bool_t havePress = StableReqState->havePress && (newpress != PRESSURE_INVALID);

        //lint -e{960}  the [mn_]abs function does not have side effects
    if (mn_abs(pos_diff) < StableReqState->nPosDB
        //If actuator pressure sensor available then
        && ((!havePress)
            //If Pressure change since last test < | nPresDB | then
            || (mn_abs(StableReqState->press - newpress) < StableReqState->nPresDB)) )
    {
        //Increment stable count
        StableReqState->good++;
    }
    else
    {
        //Reset stable count to 0
        StableReqState->nPosDB += MAX(1, StableReqState->nPosDB/DEADBAND_DIVISOR);     //increase the deadbands so that we never get stuck
        StableReqState->nPresDB += MAX(1, StableReqState->nPresDB/DEADBAND_DIVISOR);
        StableReqState->good = 0;
    }

    HardPos_t old_pos_diff = StableReqState->pos_diff;

    StableReqState->pos_diff = pos_diff;
    /* Explanation of the cast:
    If pos_diff is so huge as to need all 17 bits, we are in the path with StableReqState->good = 0.
    In this case, it doesn't matter.
    */

    StableReqState->press = newpress;

    return (!IsSameDirection(old_pos_diff, pos_diff)) && (StableReqState->good > WAIT_STABLE_POS_PRES_COUNT);
}

#if 0 //we keep it for now but it appears ESD-specific and should go to a specific source file
/** \brief Return true if valve is in manual control mode near the energized stop
    \return true if valve is in manual control mode and position near energized stop
    THIS FUNCTION MUST HAVE NO SIDE EFFECTS
*/
MN_DECLARE_API_FUNC(vutil_TestPositioningAtStop)
bool_t vutil_TestPositioningAtStop(void)
{
    s32 Setpoint;
    bool_t bReturn = true;

    (void)mode_GetIntendedControlMode(&Setpoint); //ignore the control mode

    if (error_IsFault(FAULT_AIR_SUPPLY_LOW))
    {
        bReturn = false;
    }
    if(ad_IpCurrentBelowTripThreshhold())
    {
        bReturn = false;
    }
    if (bReturn &&
       (Setpoint < POS_ENERGIZED_THRESHOLD))
    {
        bReturn = false;
    }
    else
    {
       //return true
    }

    return bReturn;
}
#endif //0

/* This line marks the end of the source */
