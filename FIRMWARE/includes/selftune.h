/*
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file selftune.h
    \brief Data owner for PID and its self-tuner data and handles get/save of data

    CPU: Any (with standard C compiler)

    OWNER: Zhou
*/

#ifndef SELFTUNE_H_
#define SELFTUNE_H_
#include "pressuredef.h"
#include "errcodes.h"
#include "crc.h"
#include "position.h"
#include <process.h>

// -------------- tune options ---------------------
enum
{
     OvershootCountUse = 0, //UNDO_59585[1] overshoot count use, 1=like ESD, 0=like AP
     AllowOutOfRangeInterimPID = 1, //UNDO_59585[2] pid limiting before setting
     AllowExtraStabilityWait = 2, //UNDO_59585[3] 0 // *0 extra stability #1 didn't help
     UseActualPosDiffForPoscomp = 3, // UNDO_59661 0 // **poscomp calc
     UseTimeForTauCalc = 4, // UNDO_59594 0 // *tau calc
     MinLimitingPAdjust = 5, //UNDO_79755 0 //Padjust limiting
     RampStabilizeByPos = 6, //OPTION_STABILIZE_BY_POS 1 //vs. wait for time
     StabilizeBias = 7, //OPTION_STABILIZE_BIAS 1 //vs. wait for time
     PostStabilizePosPres = 8, //try to get to a stable value in initial stabilization effort
     StartWithNominalPosComp = 9, //Begin tuning with PosComp=COMP_BASE for uniformity - looks pretty bad
     UseSmoothedPositionForPosComp = 10, // (1 doesn't do much good.) Use smoothed (1st-order filtered) position
	 UseSmoothedPositionForStep = 11, //Use smoothed (1st-order filtered) position
	 UsePrelimPosComp = 12 //Use interim poscomp calc
} ;

typedef struct TuneOptions_t
{
    u32 toption;
    u8 min_number_of_ramp_points; //!< 7 in AP, 10 in ESD
    s8 low_overshoot_thresh; //!< 4 in AP, OVERSHOOT_LOW=3 in ESD
    s8 PAdjust_recalc_scale; //!< inconsistent 20 in AP, PADJ_INC_RATIO=16 in ESD
    u16 CheckWord;
} TuneOptions_t;

extern const TuneOptions_t *tune_GetTOptions(TuneOptions_t *dst);
extern ErrorCode_t tune_SetTOptions(const TuneOptions_t *src);

typedef struct TuneData_t
{
    pres_t SupplyPres_User;
    u8  n1TunePara1;
    s8  n1Level;
    CHECKFIELD;
} TuneData_t;

typedef struct PIDData_t
{
    u16 P;
    u16 I;
    u16 D;
    s16 PAdjust;
    s16 Beta;
    //removed s16 Damping;
    s16 PosComp;
    pos_t DeadZone;
    u16 Band;
    //s16 NonLin;
    //removed s16 Reserved1;
    //removed s16 Reason;
    CHECKFIELD;
} PIDData_t;


extern const pres_t SupplyPressure_range[Xends]; //for user supply pressure

/** Public Defines  */

#define PERCENT_TO_SCALED_RANGE 163.84F     /* 16384/100 */

/** Additive part of position noise (guess) */
#define NOISE 40 //Should be 0.244% ?

#define POS_STAY_LOW 2458
#define POS_STAY_HIGH 13107

#define PRES_SUPPLY_HI  STD_FROM_PSI(150.0F) //was 25000   // 100.0F ///AK:NOTE: Changed to STD_FROM_PSI(100.0)
#define PRES_SUPPLY_LO  STD_FROM_PSI(20.0F)  //was 3750  // 15.0F    ///AK:NOTE: Changed to STD_FROM_PSI(15.0)
#define BAND_SUPPLY_RATIO  STD_FROM_PSI(6.6F) //was 1650 before change of pressure scaling - now 1320

#define P_HIGH_LIMIT  5000
#define P_LOW_LIMIT     10
#define I_HIGH_LIMIT  1000U
#define D_HIGH_LIMIT  200U
#define PADJ_LOW_LIMIT  (-PADJ_HIGH_LIMIT)
#define PADJ_HIGH_LIMIT  3000
#define BETA_LOW_LIMIT  -9
#define BETA_HIGH_LIMIT  9
#define PCOMP_LOW_LIMIT  2
#define PCOMP_HIGH_LIMIT  20
//#define BOOST_HIGH_LIMIT  20
#define BOOST_HIGH_LIMIT ((u16_least)((PRES_SUPPLY_HI/BAND_SUPPLY_RATIO)+1))  //compute from pres limits and round up
#define DEADZONE_HIGH_LIMIT  STD_FROM_PERCENT(5.011) //The bizarre value is chosen to match the magic number, 821

// #define SUPPLY_LOW  1.0F
// #define SUPPLY_HIGH  1500.0F
#define TUNE_LEVEL_LOW  -9
#define TUNE_LEVEL_HIGH  9

/** constants for scaling */



/** Public functions
*/
#ifdef OLD_NVRAM
extern void  tune_InitTuneData(InitType_t Type);
#endif

SAFEGETX(tune_GetPIDData, PIDData_t);
SAFESETX(tune_SetPIDData, PIDData_t);

extern ErrorCode_t tune_SetCurrentPIDData(const PIDData_t *src);
extern const PIDData_t *tune_GetWorkinPIDData(PIDData_t *dst);

#define tune_GetCurrentPIDData tune_GetWorkinPIDData //! for backward compatibility

#define CTLPARAMSET_AUTOTUNE 0U //!< Index of tunable set of PID parameters
#define CTLPARAMSET_5CAMFLEX 1U
#define CTLPARAMSET_6CAMFLEX 2U
#define CTLPARAMSET_10_20    3U
#define CTLPARAMSET_10_24    4U
#define CTLPARAMSET_23_12    5U
#define CTLPARAMSET_9CAMFLEX 6U
#define CTLPARAMSET_23_24    7U

#define MANUALTUNE_MASK      0x07u

//required interface
extern u8 posctl_GetCtlSetIndex(void);

typedef struct CtlSetSlot_t
{
    u8 slot;
    u16 CheckWord;
} CtlSetSlot_t;

SAFEGET(posctl_GetCtlset, CtlSetSlot_t);
SAFESET(posctl_SetCtlset, CtlSetSlot_t);

#ifdef OLD_NVRAM
//NVRAM Shims
extern void posctl_Init(InitType_t itype);
extern void posctl_Save(void);
#endif //OLD_NVRAM

/** \brief Indicates whether the currently effective control param set
is tunable.
\return true iff tunable
*/
MN_INLINE bool_t posctl_IsTunableCtlset(void)
{
    return posctl_GetCtlSetIndex()==CTLPARAMSET_AUTOTUNE;
}


extern procresult_t tune_Run_Selftune(s16 *procdetails);

SAFEGET(tune_GetTuneData, TuneData_t);
SAFESET(tune_SetTuneData, TuneData_t);

extern s16 tune_GetCompletionCode(void);

#endif  /** SELFTUNE_H_  */

/* end of the source */
