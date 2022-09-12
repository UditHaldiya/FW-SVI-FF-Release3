/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pneumatics.h
    \brief Types and prototypes of pneumatics-related parameters

    CPU: Any

    OWNER: AK
    \ingroup control
*/

#ifndef PNEUMATICS_H_
#define PNEUMATICS_H_
#include "errcodes.h"
#include "pressures.h"
#include "pressuredef.h"
//#include "strong_types.h"

typedef struct boostCoeff_t
{
    u8 boost[Xends]; //low and high thresholds
    s8 BoostOffset; //!< beginning of "flat spot"
} boostCoeff_t;

typedef struct presLimits_t
{
    pres_t presLimit[Xends]; //low and high
} presLimits_t;

typedef struct PneumaticParams_t
{
    boostCoeff_t boostCoeff;
    presLimits_t presLimitsPilot;
    pres_t SupplyLossThreshold_Pilot;
//    curr_ma_t SupplyLossThreshold_Current;
    pres_t SupplyLossThreshold_Supply;
    u8 SingleActing;
    s8 SensorMap[NUMBER_OF_PRESSURE_SENSORS]; //mapping of logical to physical A/D sensors
    u16 CheckWord;
} PneumaticParams_t;

SAFEGET(pneu_GetParams, PneumaticParams_t);
SAFESET(pneu_SetParams, PneumaticParams_t);

#ifdef OLD_NVRAM
extern void pneu_InitData(InitType_t Type);
extern void pneu_SaveData(void);
#endif

/** \brief A simple wrapper to check for a single-acting relay
\return true iff single-acting
*/
MN_INLINE bool_t pneu_IsSingleActing(void)
{
    return pneu_GetParams(NULL)->SingleActing != 0U;
}

#endif //PNEUMATICS_H_
/* This line marks the end of the source */
