/**
Copyright 2004-2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file diagnostics.h
    \brief Includes all the public APIs for diagnostics
    OWNER: LS
    CPU: Any

*/

#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_

#include "dimensions.h"
#include "pressuredef.h"
#include "position.h"
#include "process.h"
#include "bufferhandler.h"

#define WAIT_TICKS ((u16)3u)

#define DIAG_EXT_ACT        2u
#define DIAG_STEP           3u
#define DIAG_RAMP           4u
#define DIAG_DATAHOG ((diag_t)0x5500)
//#define DIAG_PST            5u
#define DIAG_PST            DIAG_DATAHOG

#define STABLE_POS_TEST (NOISE_BAND_STABLE)
#define STABLE_PRES_TEST (NOISE_BAND_PRES_STABLE)

//legacy for autotune
extern ErrorCode_t diag_SetDiagnosticParameters(u8_least Type, u16_least nSpeed, pos_t StartPosition,
    pos_t EndPosition, u16_least SampleRate); //deprecated
extern bool_t diag_Perform_StepTest(void); //deprecated

extern procresult_t diag_Run_ExtActuatorSignature(s16 *procdetails);
extern void diag_Run_StepTest(void);
extern procresult_t diag_Run_RampTest(s16 *procdetails);
extern ErrorCode_t diag_LaunchStepTest(pos_t StartPosition, pos_t EndPosition, u16 SamplingTime);
extern ErrorCode_t diag_LaunchRampTest(pos_t StartPosition, pos_t EndPosition, pos_t SetpointRampSpeed, u8 DiagDirection);
extern ErrorCode_t diag_LaunchExtDiagnostics(pos_t StartPosition, pos_t EndPosition, pos_t SetpointRampSpeed, u8 DiagDirection, u8 DiagControlOption);
extern void FillExtDiagHeader(const s16 *procdetails);
extern bool_t CheckIPLimits(s32 IP);
extern void SetSamplesFirstDirection(void);
extern void SetSamplesLastDirection(void);

MN_DECLARE_API_FUNC(dsampler_SamplePosPres)
extern void dsampler_SamplePosPres(diag_t data[2]);


//Defines to cross check
typedef s32 bias_t;

// ---- FFAP additions ----

#define EXTDIAG_HEADERSZ 24 //in diag_t entries; a dogmatic number to please FF params
/* What's the max number of samples we can collect?
The buffer can hold (DIAGNOSTIC_BUFFER_SIZE-1) diag_t entries of which
headersz is reserved for the header.
The remaining entries will hold dsample_t-sized entries, i.e.
sizeof(dsample_t)/sizeof(diag_t) times less than the number of entries
*/
#define DENTRIES_IN_DSAMPLE (sizeof(dsample_t)/sizeof(diag_t))
//Sanity check:
CONST_ASSERT((sizeof(dsample_t)%sizeof(diag_t))==0U);
#define MAX_NUM_DSAMPLES(headersz) (((((DIAGNOSTIC_BUFFER_SIZE-1U)-headersz)/DENTRIES_IN_DSAMPLE)/2U)*2U) //must be even!

#define DIAG_REQUIRED_SAMPLES 1000U //! requirement from Marketing
#define DIAG_MAX_SAMPLES (2U*DIAG_REQUIRED_SAMPLES) //! need twice the required to account for pruning

#define DIAGSIGN_LOGFILE_MAXSIZE ((EXTDIAG_HEADERSZ*sizeof(diag_t)) + (DIAG_MAX_SAMPLES*sizeof(dsample_t)))

#define NUMBER_DIAGNOSTIC_BASELINES 1U
#define NUMBER_DIAGNOSTIC_USER_CURVES 1U
#define NUMBER_DIAGNOSTIC_CURRENT_CURVES 1U

//Diagn signature control options
#define DIAGOPT_OPENLOOP 0
#define DIAGOPT_CLOSEDLOOP 1
//Diagn signature directions
#define DIAGDIR_UPDOWN 0
#define DIAGDIR_ONEWAY 1
#define DIAGDIR_UP DIAGDIR_ONEWAY

//used in multiple diagnostic files
#define POSITION_03 STD_FROM_PERCENT(0.03)
#define POSITION_05 STD_FROM_PERCENT(0.05)
#define POSITION_10 STD_FROM_PERCENT(0.10)
#define POSITION_20 STD_FROM_PERCENT(0.20)
//#define POSITION_90 STD_FROM_PERCENT(0.90)
//#define POSITION_95 STD_FROM_PERCENT(0.95)

#define PRESSURE_LOW_CUTOFF STD_FROM_PSI(0.25)

#endif

/* This line marks the end of the source */

