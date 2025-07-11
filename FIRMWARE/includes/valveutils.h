/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file valveutils.h
    \brief Header for valve utilities - stable pressure, position, bias detection

    CPU: Any (with standard C compiler)

    OWNER: EP
*/

#ifndef VALVEUITILS_H_
#define VALVEUITILS_H_
#include "pressuredef.h"
#include "position.h"

#define BIAS_ERR 1u
//#define WAIT_FOR_SETPOINT true
//#define WAIT_FOR_STABLE false

//All these functions are optional to use in a project:
MN_DECLARE_API_FUNC(util_GetStableBias, util_WaitStablePosPres, util_WaitForPos,
                    util_WaitForPosExt, vutil_StableReq_Init, vutil_StableReq_Run,
                    vutil_StablePosPresReq_Init, vutil_StablePosPresReq_Run)

//used in AP but not ESD
extern u16 	   util_GetStableBias(pos_t nStdPos, u16 nTime, HardPos_t nPosDB, pres_t nPresDB) MN_DECLARE_API_FUNC(util_GetStableBias);

extern bool_t  util_WaitStablePosPres(u16 nTime, HardPos_t nPosDB, pres_t nPresDB);
extern bool_t  util_WaitForPos(u16 nTime,  HardPos_t nNoiseDB , bool_t cFlag);

typedef struct StableReq_t
{
    HardPos_t pos; //!< (previous) position - to monitor direction change
    HardPos_t pos_diff; //!< (previous) increment of the position - to monitor direction change
    pres_t press; //!< (previous) pressure - to monitor direction change
    HardPos_t nPosDB; //!< dead band adjustment for position noise
    pres_t nPresDB; //!< dead band adjustment for pressure noise
    bool_t havePress; //!< true iff pressure sensor used
    u8 good;      //!< counter of stable points
} StableReq_t; //!< private structure to test for stable valve position/pressure

extern u8_least util_WaitForPosExt(u16 nTime,  HardPos_t nNoiseDB , bool_t cFlag, u8_least brk_mask);

typedef struct StablePosReq_t
{
    pos_least_t reference; //!< initial setpoint or previous position
    //pos_least_t lastPos;  //!< previous position
    //pos_t pos; //!< (previous) position - to monitor direction change
    //pos_t pos_diff; //!< (previous) increment of the position - to monitor direction change
    pos_t deadBand; //!< dead band at the moment of initialization
    pos_t nPosDB; //!< dead band adjustment for position noise
    bool_t cFlag; //!< true==stable @ setpoint, false== stable @ lastpos
    u8 good;      //!< counter of stable points
} StablePosReq_t; //!< private structure to test for stable valve position
//these routines are used in some projects and not others and depend on some features
extern void vutil_StableReq_Init(StablePosReq_t *StableReqState, HardPos_t nNoiseDB, bool_t cFlag) MN_DECLARE_API_FUNC(vutil_StableReq_Init);
extern bool_t vutil_StableReq_Run(StablePosReq_t *StableReqState) MN_DECLARE_API_FUNC(vutil_StableReq_Run);

extern void vutil_StablePosPresReq_Init(StableReq_t *StableReqState, HardPos_t nPosDB, pres_t nPresDB, bool_t havePress) MN_DECLARE_API_FUNC(vutil_StablePosPresReq_Init);
extern bool_t vutil_StablePosPresReq_Run(StableReq_t *StableReqState) MN_DECLARE_API_FUNC(vutil_StablePosPresReq_Run);

#if 0
extern bool_t vutil_TestPositioningAtStop(void);
#endif

#endif /* VALVEUITILS_H_ */

/* This line marks the end of the source */
