/*
Copyright 2022 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFAP_xlate_12_13.c
    \brief Translation between layouts 12 and 13 (expanded data hog trigger)

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFAP_xlate_12_13.h"

//lint -esym(754, *_t12::*) -esym(754, *_t13::*) Types are for sizes here

CONST_ASSERT(FFAP_NVRAM_ENTRIES_VER_12==FFAP_NVRAM_ENTRIES_VER_13);
CONST_ASSERT(FFAP_NVRAMID_TuneData_12==FFAP_NVRAMID_TuneData_13);

typedef struct TuneOptions_t13
{
    u32 toption;
    u8 min_number_of_ramp_points; //!< 7 in AP, 10 in ESD
    s8 low_overshoot_thresh; //!< 4 in AP, OVERSHOOT_LOW=3 in ESD
    s8 PAdjust_recalc_scale; //!< inconsistent 20 in AP, PADJ_INC_RATIO=16 in ESD
    s8 PAdjust_recalc_scale2; //!< inconsistent 20 in AP, PADJ_INC_RATIO=16 in ESD
} TuneOptions_t13;

typedef struct TuneData_t13
{
    s16 SupplyPres_User;
    u8  n1TunePara1;
    s8  n1Level;
    TuneOptions_t13 TuneOptions;
    u16 CheckWord;
} TuneData_t13;

typedef struct TuneData_t12
{
    s16 SupplyPres_User;
    u8  n1TunePara1;
    s8  n1Level;
    u16 CheckWord;
} TuneData_t12;

enum
{
     OvershootCountUse_13 = 0, //UNDO_59585[1] overshoot count use, 1=like ESD, 0=like AP
     DisAllowOutOfRangeInterimPID_13 = 1, //UNDO_59585[2] pid limiting before setting
     AllowExtraStabilityWait_13 = 2, //UNDO_59585[3] 0 // *0 extra stability #1 didn't help
     UseActualPosDiffForPoscomp_13 = 3, // UNDO_59661 0 // **poscomp calc
     UseTimeForTauCalc_13 = 4, // UNDO_59594 0 // *tau calc
     MinLimitingPAdjust_13 = 5, //UNDO_79755 0 //Padjust limiting
     RampStabilizeByPos_13 = 6, //OPTION_STABILIZE_BY_POS 1 //vs. wait for time
     StabilizeBias_13 = 7, //OPTION_STABILIZE_BIAS 1 //vs. wait for time
     PostStabilizePosPres_13 = 8, //try to get to a stable value in initial stabilization effort
     StartWithNominalPosComp_13 = 9, //Begin tuning with PosComp=COMP_BASE for uniformity - looks pretty bad
     UseSmoothedPositionForPosComp_13 = 10, // (1 doesn't do much good.) Use smoothed (1st-order filtered) position
	 UseSmoothedPositionForStep_13 = 11, //Use smoothed (1st-order filtered) position
     UseSmoothedPositionForRamp_13 = 12,
	 UsePrelimPosComp_13 = 13, //Use interim poscomp calc
     Apply_nY_min_fix_13 = 14, //Fix like in ESD. AP will always go to the end
     Include_P_and_D_in_bias_13 = 15 //AP doesn't have it, contrary to Ernie's caution of ESD time
} ;

#ifdef _lint
static
#endif
const TuneOptions_t13 TuneOptions_default_13 =
{
    .toption =
        (0U<<OvershootCountUse_13) |
        (1U<<DisAllowOutOfRangeInterimPID_13) |
        (0U<<AllowExtraStabilityWait_13) |
        (0U<<UseActualPosDiffForPoscomp_13) |
        (0U<<UseTimeForTauCalc_13) |
        (1U<<MinLimitingPAdjust_13) |
        (0U<<RampStabilizeByPos_13) |
        (1U<<StabilizeBias_13) |
        (0U<<PostStabilizePosPres_13) |
        (0U<<StartWithNominalPosComp_13) |
        (0U<<UseSmoothedPositionForPosComp_13) |
        (0U<<UseSmoothedPositionForStep_13) |
        (0U<<UseSmoothedPositionForRamp_13) |
        (1U<<UsePrelimPosComp_13) |
        (0U<<Apply_nY_min_fix_13) |
        (0U<<Include_P_and_D_in_bias_13) | //AP doesn't have it, contrary to Ernie's caution of ESD time
        0U,
    .min_number_of_ramp_points = 10, // 7 in AP and R2, 10 in ESD (C9565[1])
    .low_overshoot_thresh = 3, // 4 in AP, OVERSHOOT_LOW=3 in ESD (C59565[2])
    .PAdjust_recalc_scale = 20, // inconsistent 20 in AP, PADJ_INC_RATIO=16 in ESD
    .PAdjust_recalc_scale2 = 20, // inconsistent 16 in AP, PADJ_INC_RATIO=16 in ESD
};

/** \brief A trivial contraction translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlatedn_13_12(u8 *dst, const u8 *src, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_13; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_TuneData_13:
            {
                TuneData_t12 *d = (TuneData_t12 *)(void *)(&dst[FFAP_nvram_map_12[id].offset]);
                const TuneData_t13 *s = (const TuneData_t13 *)(const void *)(&dst[FFAP_nvram_map_13[id].offset]);
                d->SupplyPres_User = s->SupplyPres_User;
                d->n1TunePara1 = s->n1TunePara1;
                d->n1Level = s->n1Level;
                STRUCT_CLOSE(TuneData_t12, d);
            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_12[id].offset, src + FFAP_nvram_map_13[id].offset, FFAP_nvram_map_13[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}


/** \A trivial expansion translation routine
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlateup_12_13(const u8 *src, u8 *dst, void (*func)(void))
{
    //Common part of layout
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_13; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_TuneData_13:
            {
                TuneData_t13 *d = (TuneData_t13 *)(void *)(&dst[FFAP_nvram_map_13[id].offset]);
                const TuneData_t12 *s = (const TuneData_t12 *)(const void *)(&dst[FFAP_nvram_map_12[id].offset]);
                d->SupplyPres_User = s->SupplyPres_User;
                d->n1TunePara1 = s->n1TunePara1;
                d->n1Level = s->n1Level;
                d->TuneOptions = TuneOptions_default_13;
                STRUCT_CLOSE(TuneData_t13, d);
            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_13[id].offset, src + FFAP_nvram_map_12[id].offset, FFAP_nvram_map_12[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}


/* This line marks the end of the source */
