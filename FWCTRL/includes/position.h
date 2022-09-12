/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file position.h
    \brief API for System-level data and services related to valve position

    CPU: Any

    OWNER: AK

    \ingroup sysio
*/
#ifndef POSITION_H_
#define POSITION_H_
#include <limits.h>
#include "smoothing.h"
#include "numutils.h"
#include "errcodes.h"

#include "percent.h"
#include <process.h> //for procresult_t

/* ------------------- Position: ------------------------
   Physical units - % of full range
   Mapping - [0..100]<==>[0..2^^14] (The upper limit must be a power of 2)
*/
/* A type representing position must be sufficient to hold 199.99% and withstand
   application-defined scalings, such as open stop adjustment, without overflow.
   This may (and currently does) impose restrictions on valid scaling factors; the
   numeric values of the constraints ABSOLUTELY must be checked; preferably at
   compile time (second choice is runtime code optimized out by the compiler, last
   resort is error_SetFault()).
    We choose the generic percent type to represent position in internal units.
    This is arbitrary but convenient and consistent with the connotation.
*/
typedef percent_t pos_t;
typedef percent_least_t pos_least_t;

/* ------------------- Position: ------------------------
   Physical units - % of full range
   Mapping - [0..100]<==>[0..2^^14] (The upper limit must be a power of 2)
*/
/* Internal representation of values in standard range:
   For instance, INT_PERCENT_OF_RANGE(3) will evaluate to 491u,
   whereas SCALED_PERCENT_OF_RANGE(3, 100) evaluates to 49152, 100 times greater.
   SCALED_PERCENT_OF_RANGE() can be useful as part of larger calculation.
*/
//lint -emacro(912, INT_PERCENT_OF_RANGE) Implicit promotion allowed
//#define INT_PERCENT_OF_RANGE(pct) ((s32)((STANDARD_RANGE*((cdouble_t)(pct)))/100))
#define INT_PERCENT_OF_RANGE(pct) STD_FROM_PERCENT(pct)
#define SCALED_PERCENT_OF_RANGE(pct,scale) ((((s32)STANDARD_RANGE*(pct)*(scale))/100))


/* Non-strong types representing "adjusted" position.
Adjustment may be for air action (ATO/ATC) and or stop adjustment
*/
#if 1
#define adjpos_t pos_t
#define adjpos_least_t pos_least_t
#else
typedef pos_t adjpos_t;
typedef pos_least_t adjpos_least_t;
#endif

//typedef s16 posspeed_t;
#define POSTYPE_MAX SHRT_MAX
//#define POSTYPE_MIN SHRT_MIN

//check that the type holds 199.99%, per application definition
CONST_ASSERT( ((u32)SCALED_PERCENT_OF_RANGE(200,2)-1U) <= ((u32)100*(u32)POSTYPE_MAX) );


/** Empirical estimate for noise level in MNCB position sensor.
It's used as an initial guess.
*/
#define NOISE_BAND_STABLE   ((HardPos_t)40) //Like in AP; maybe, same
typedef s32 HardPos_t; //! Type of the sensor-technology-dependent sensor read, tempcomp'ed and perhaps linearized

typedef struct PositionConf_t
{
    HardPos_t  rangeval[Xends]; //!< compensated sensor readings corresponding to extreme travel limits - de-energized [Xlow] and energized [Xhi]
    pos_t  PositionRange[Xends]; //!< mapping of normalized [0%, 100%] range to user-scaled range. Closed stop adj [Xlow] and Open stop adj [Xhi]
    //percent_t OpenStopAdjustment;
    //percent_t fClosedStopAdjustment;   IMPLEMENT IN PHASE III
    FilterConf_t filtercoef;
    bool_t bATO;
    u16 CheckWord;
} PositionConf_t;

typedef struct ComputedPositionConf_t
{
    s32  slope_scaled; //!< scale coefficient to map pos. reading (voodoo domain) to app [0%-100%] domain; can be of either sign
    HardPos_t offset_scaled; //!< de-energized hard stop
    s32  slope_adjusted; //!< scale coefficient to convert pos. in original range to adjusted range; can be of either sign
    s32  slope_unadjust; //!< scale coefficient to convert pos. in adjusted domain to the "hard stops" domain; can be of either sign
    pos_t offset_adjusted; //!< offset to move the converted pos. in original range to adjusted range (as in closed stop adjustment)
    //pos_t  PositionSoftStop[Xends]; //!< readings corresponding to closed [Xlow] or open [Xhi] positions; provide scaling for the position
    //pos_t  ExtraPos[Xends]; //!< scaled position values - practically closed [Xlow] or practically open [Xhi]
    bool_t direct_scaled; //bATO;
    bool_t direct_adjusted; //bATO;
    //backward-compatible kludge
    pos_t ExtraPosLow;
    pos_t ExtraPosHigh;
    s32 n4OpenStopAdj;
    //end backward-compatible kludge
    u16 CheckWord;
} ComputedPositionConf_t;



extern void pos_UpdateState(HardPos_t hardpos, ErrorCode_t err);
extern void pos_InitFilter(void);
extern void pos_InitFilterRaw(void);

extern pos_t vpos_GetScaledPosition(void);
extern pos_least_t vpos_GetSmoothedScaledPosition(void);
extern pos_least_t vpos_GetSmoothedRawPosition(void);
extern HardPos_t vpos_GetRawPosition(void);

//Project-independent wrapper for common interfaces
MN_INLINE pos_least_t pos_GetPresentationPosition(void)
{
    return vpos_GetSmoothedScaledPosition();
}


SAFESET(pos_SetPositionConf, PositionConf_t);
SAFEGET(pos_GetPositionConf, PositionConf_t);

extern const ComputedPositionConf_t *pos_GetComputedPositionConf(ComputedPositionConf_t *dst);
//extern ErrorCode_t pos_TestPositionConf(const PositionConf_t* pPositionConf);

//ranges
extern const percent_t OpenStopAdj_range[Xends];
extern const pos_t Position_FullRange[Xends];

//defaults
extern const PositionConf_t def_PositionConf;

/** constants for position scaling */
#define FACTOR_NUMBITS_30 30U
#define FACTOR_HISTORIC_NOISE_SCALE 16U //as in David's MAX_FOR_16BIT==65535u (I don't care about 1 count error over the range)

/** \brief a rough estimate of the noise in measuring the position.
It is borrowed from control.c from two places but remains a brutal hack.

TODO: A more intelligent method is badly needed.
AK: NOTE: Now it applies to un-adjusted domain, so it is not that bad as before

This method assumes the noise range to be the sum of a constant noise and a noise
inversely proportional to the (soft, adjusted) range of the position.
\param additive - fixed contributor
\param multiplicative - scaled coef on the range of the position
\return a noise level estimate
\deprectaed Justin recommends removing/rewriting pos_NoiseEstimate so it's left as is until better times
*/
MN_INLINE pos_least_t pos_NoiseEstimate(pos_t additive, s32 multiplicative)
{
    s32 abs_slope = pos_GetComputedPositionConf(NULL)->slope_scaled;
    abs_slope = ABS(abs_slope);
    abs_slope = div_by_pwr2(abs_slope, FACTOR_NUMBITS_30-FACTOR_HISTORIC_NOISE_SCALE);
    return additive + (abs_slope*multiplicative);
}

//Required interfaces
#define STOPS_MIN_RANGE  1535 //bogus. borrowed from MNCB where it corresponds to 7 deg. in Hall sensor

extern void cnfghook_CorrectForNewPositionConf(const ComputedPositionConf_t *oldposconf, const ComputedPositionConf_t *newposconf);

typedef struct PosState_t
{
    HardPos_t hardpos; //!< instant position, temperature-corrected and linearized
    pos_t pos; //!< instant position, temperature-corrected and linearized, mapped to standard range ~ 0%-100% w.r.t. stops
    adjpos_t pos_adjusted; //!< instant position, corrected w.r.t. user adjustments
    FilterState_t posfilter; //!< the state of the position smoothing
    FilterState_t posfilterRaw; //!< the state of raw position smoothing
    u8 lifeleft; //!< a countdown counter; when reaches 0, the `pos' member etc. are invalid
    u16 CheckWord; //We don't use it for now
} PosState_t;

#define POS_LIFELEFT_MAX 10U //! Max number of tolerated invalid reads of position

extern ErrorCode_t pos_SetStopAdjustment(pos_least_t ClosedStopAdjustment, pos_least_t OpenStopAdjustment);
extern bool_t pos_GetStopAdjustment(pos_t dst[Xends]);

extern adjpos_t pos_AdjustStdPositionExt(pos_least_t pos, const ComputedPositionConf_t *posconf);
MN_DECLARE_API_FUNC(pos_UnAdjust)
extern pos_t pos_UnAdjust(adjpos_least_t pos);
extern pos_t pos_UnAdjustExt(adjpos_least_t pos, const ComputedPositionConf_t *posconf);

extern const PosState_t *pos_GetPosState(PosState_t *dst);

MN_DECLARE_API_FUNC(pos_ConvertHardposDiffToStd)
/** \brief A helper to convert a difference of hard positions to a difference in % domain.
Stop adjustment is accounted for.
\param hardpos - position difference in linearized sensor domain
\return value of position difference as percent of range, clamped to position's allowed range
*/
extern pos_t pos_ConvertHardposDiffToStd(HardPos_t hardpos);

#if 0
typedef struct ExtraPos_t
{
    pos_t ExtraLim[Xends];
    u16 CheckWord;
} ExtraPos_t;
extern const ExtraPos_t *pos_GetExtraLimits(ExtraPos_t *dst); //may need to move elsewhere - TBD
#endif //0

// ---------- Calibration support --------------------------
typedef struct poscalib_t
{
    HardPos_t rangeval[Xends]; //!< existing range values (may or may not be valid)
    bool_t valid[Xends]; //!< flags indicating validity of the existing range values
#if 0
    bool_t inherit[Xends]; //!< flags of user intention to preserve an old range value
#endif //0
} poscalib_t; //! API type for position/level range calibration procedures

#if 0
extern ErrorCode_t poscal_Init(poscalib_t *poscalib, bool_t clow, bool_t chigh);
extern ErrorCode_t poscal_Commit(poscalib_t *poscalib);
extern ErrorCode_t poscal_SetRangeValue(poscalib_t *poscalib, s8_least index);

extern void poscal_Invalidate(poscalib_t *poscalib);
//  -- required project-specific plugins
/** \brief Populate the poscalib structure with existing "stops"
\param poscaib - a pointer to the struct to fill out
\return an error code
*/
extern ErrorCode_t pos_GetGuardedRV(poscalib_t *poscalib);
/** \brief Replace the existing "stops" with ones from the poscalib structure
\param poscaib - a pointer to the struct containing replacements
\return an error code
*/
extern ErrorCode_t pos_SetGuardedRV(const poscalib_t *poscalib);

extern void pos_AdjustForStopsRange(void);
#endif


//position range
#define MAX_ALLOWED_POSITION ((2*STANDARD_100)-1)
#define MIN_ALLOWED_POSITION (-MAX_ALLOWED_POSITION)


//Scaling and Presentation parameters
#define UNITSID_POSITION_a STANDARD_ZERO
#define UNITSID_POSITION_b STANDARD_100
#define UNITS_PERCENT_A 0.0
#define UNITS_PERCENT_B 100.0
#define UNITS_PERCENT_N 2

//PERCENT_PER_SEC (% per 4 s internally)
#define H_PERCENT_PER_SEC H_NOT_USED
#define UNITSID_MN_POSITION_SPEED_a 0
#define UNITSID_MN_POSITION_SPEED_b 400
#define UNITS_PERCENT_PER_SEC_A 0.0 //
#define UNITS_PERCENT_PER_SEC_B 100.0 //
#define UNITS_PERCENT_PER_SEC_N 2

//Travel calibration (find stops) business:
extern ErrorCode_t poscal_AcceptStop(void);
extern ErrorCode_t poscal_CommitStops(bool_t save);
extern procresult_t poscal_RunFindStops(s16 *procdata);

#endif //POSITION_H_
/* This line marks the end of the source */
