/*
Copyright 2017 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file syncpatches.c
    \brief Where block parameters share a member, they must be kept together in
        a single NV object. This file replaces TB-to-NV automation to support objects
        of such unfortunate properties.

    CPU: Any

    OWNER: AK
*/
#ifndef SYNCPATCHES_H_
#define SYNCPATCHES_H_

#include <float.h>
#include <softing_base.h>
#include <ptb.h>
#include "mnhart2ff.h"

typedef struct TravelAlert_t
{
    _TRAVEL_ALERT travel_alert[2]; //0-A 1-B
    //_TRAVEL travel;
    u16 CheckWord;
} TravelAlert_t;
extern const TravelAlert_t *travel_Get(TravelAlert_t *dst);
extern ErrorCode_t travel_Set(const TravelAlert_t *src);
UNTYPEACC(travel_Set, travel_Get);
extern void travel_SaveAccum(void);

extern fferr_t travel_CommitTravelAccumulationAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance);
extern fferr_t travel_WriteTravelAccumulationAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write);
extern fferr_t travel_TestTravelAccumulationAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write);


typedef struct CycleCounterAlert_t
{
    _CYCLE_COUNTER_ALERT ccalert[2]; //0-A 1-B
    u16 CheckWord;
} CycleCounterAlert_t;
extern const CycleCounterAlert_t *ccalert_Get(CycleCounterAlert_t *dst);
extern ErrorCode_t ccalert_Set(const CycleCounterAlert_t *src);
UNTYPEACC(ccalert_Set, ccalert_Get);

extern fferr_t ccalert_TestCycleCounterAlert(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write);
extern fferr_t ccalert_WriteCycleCounterAlert(T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write);
extern void ccalert_ReadCycleCounterAlert(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_READ_DATA* p_read);
extern void taalert_ReadTravelAccumAlert(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_READ_DATA* p_read);

#define TRAVEL_STD_RANGE (100.0F)
MN_INLINE float32 Travel_ScaleToInternal(const T_FBIF_PTB *p_PTB)
{
    float32 scale = 0.0F;
    if(p_PTB->travel.TravelRange > FLT_EPSILON)
    {
        scale = TRAVEL_STD_RANGE/p_PTB->travel.TravelRange;
    }
    return scale;
}
MN_INLINE float32 Travel_ScaleToExternal(const T_FBIF_PTB *p_PTB)
{
    return p_PTB->travel.TravelRange/TRAVEL_STD_RANGE;
}



#endif //SYNCPATCHES_H_
/* This line marks the end of the source */
