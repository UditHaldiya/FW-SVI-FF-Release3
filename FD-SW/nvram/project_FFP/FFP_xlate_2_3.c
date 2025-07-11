/*
Copyright 2020 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFP_xlate_2_3.c
    \brief Translation between FFP layouts 2 and 3

NOTE: Scaling of travel trend, trend alert and cycle alert to internal range (%) is missing

Layout 2 has travel trend, trend alert and cycle alert in user scaling (TB.TRAVEL.TravelRange)
Layout 3 has those in internal scaling (%)
In this implementation the rescaling is missing.
IT MUST BE ADDED if we decide to preserve SVI FF Rev.2 (or even perhaps Rev.1) NVMEM content

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFP_xlate_2_3.h"
#include "nvram.h"
#include "evertran.h"

//lint -e754 Struct members are for size/reference only
typedef struct AccTrend_t2
{
    u32 count;
    u32 sum;
} AccTrend_t2; //! Integer trend

typedef struct Trend_Counter_t2
{
    AccTrend_t2 day;
    AccTrend_t2 week;
    AccTrend_t2 month;
    AccTrend_t2 year;
    u16 CheckWord;
} Trend_Counter_t2;//! Integer trend

typedef struct TREND_t2
{
    u32 stuff[17];
#if 0
    USIGN32 currently_collected;
    USIGN32 today;
    USIGN32 last_day;
    USIGN32 previous_day;
    USIGN32 three_days_ago;
    USIGN32 current_week;
    USIGN32 last_week;
    USIGN32 previous_week;
    USIGN32 three_weeks_ago;
    USIGN32 current_month;
    USIGN32 last_month;
    USIGN32 previous_month;
    USIGN32 three_months_ago;
    USIGN32 current_12_months;
    USIGN32 last_12_months;
    USIGN32 previous_12_months;
    USIGN32 three_years_ago;
#endif //0
    u16 CheckWord;
} TREND_t2;

typedef struct TrendInfo_t3
{
    Trend_Counter_t2 Trend_Counter;
    TREND_t2 tbtrend;
    u16 CheckWord;
} TrendInfo_t3; //! Atomic type of trend artifacts

typedef struct _TRAVEL_t3
  {
    float32 TravelRange;
    u16 units_index;
  }
_TRAVEL_t3;
typedef _TRAVEL_t3 _TRAVEL_t2;

typedef struct _TRAVEL_ALERT_t2
  {
    u32 travel_accumulation;
    u32 alert_point;
    float32 deadband_ab;
    u8 enable;
  }
_TRAVEL_ALERT_t2;

typedef struct MN_NV_TRAVEL_t3
{
    _TRAVEL_t3 TRAVEL;
    u16 CheckWord;
} MN_NV_TRAVEL_t3;

typedef struct TravelAlert_t3
{
    _TRAVEL_ALERT_t2 travel_alert[2]; //0-A 1-B
    //_TRAVEL travel;
    u16 CheckWord;
} TravelAlert_t3;

typedef _TRAVEL_ALERT_t2 _TRAVEL_ALERT_t3;
typedef struct TravelAlert_t2
{
    _TRAVEL_ALERT_t3 travel_alert[2]; //0-A 1-B
    _TRAVEL_t3 travel;
    u16 CheckWord;
} TravelAlert_t2;

CONST_ASSERT(FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_2==FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_3);
#define NV_GAP1_2_3 1U
#define NV_GAP2_2_3 2U

CONST_ASSERT(FFP_NVRAMID_MN_NV_TRAVEL_3 == FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_3 + NV_GAP1_2_3);
CONST_ASSERT(FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_3 + NV_GAP2_2_3 == FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_2);
CONST_ASSERT(FFP_NVRAMID_TrendInfo_3 + NV_GAP2_2_3 == FFP_NVRAMID_Trend_Counter_2);
CONST_ASSERT(FFP_NVRAMID_MN_NV_MN_DEVIATION_ALERT_3 == FFP_NVRAMID_MN_NV_DEVIATION_ALERT_2 + NV_GAP1_2_3);

/** \A translation routine
NOTE: Never touch id 0!
NOTE: Scaling of travel trend, trend alert and cycle alert to internal range (%) is missing
*/
ErrorCode_t FFP_xlateup_2_3(const u8 *src, u8 *dst, void (*func)(void))
{
    //Copy unchanged and unmoved items
    for(u8_least id = 1U; id<=FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_2; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_3[id].offset, src + FFP_nvram_map_2[id].offset, FFP_nvram_map_3[id].length);
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, cant' we?
        {
            func();
        }
    }
    //Separated/extracted record
    {
        //Extract TRAVEL
        MN_NV_TRAVEL_t3 *d = (void *)(dst + FFP_nvram_map_3[FFP_NVRAMID_MN_NV_TRAVEL_3].offset);
        const TravelAlert_t2 *s = (const void *)(src + FFP_nvram_map_2[FFP_NVRAMID_TravelAlert_2].offset);
        const _TRAVEL_t2 *s1 = &s->travel;
        d->TRAVEL = *s1;
        STRUCT_CLOSE(MN_NV_TRAVEL_t3, d);
        //Extract travel alerts
        TravelAlert_t3 *d1 = (void *)(dst + FFP_nvram_map_3[FFP_NVRAMID_TravelAlert_3].offset);
        d1->travel_alert[0] = s->travel_alert[0];
        d1->travel_alert[1] = s->travel_alert[1];
        STRUCT_CLOSE(TravelAlert_t3, d);
    }
    //Copy unchanged but moved items
    for(u8_least id = FFP_NVRAMID_MN_NV_DEVIATION_ALERT_2; id<=FFP_NVRAMID_MN_NV_POSITION_LOLO_ALERT_2; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_3[id + NV_GAP1_2_3].offset, src + FFP_nvram_map_2[id].offset, FFP_nvram_map_3[id].length);
    }
    func();

    for(u8_least id = FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_3; id<FFP_NVRAMID_TrendInfo_3; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_3[id].offset, src + FFP_nvram_map_2[id + NV_GAP2_2_3].offset, FFP_nvram_map_3[id].length);
    }
    func();

    //convert the changed objects
    for(u8_least id = 0; id<3; id++) //all 3 trend objects
    {
        TrendInfo_t3 *d = (void *)(dst + FFP_nvram_map_3[id+FFP_NVRAMID_TrendInfo_3].offset);
        const TREND_t2 *t = (const void *)(src + FFP_nvram_map_2[id+FFP_NVRAMID_MN_NV_TRAVEL_ACCUMULATION_TREND_2].offset);
        memcpy(&(d->tbtrend), t, MN_OFFSETOF(TREND_t2, CheckWord));
        const Trend_Counter_t2 *p = (const void *)(src + FFP_nvram_map_2[id+FFP_NVRAMID_Trend_Counter_2].offset);
        memcpy(&(d->Trend_Counter), p, MN_OFFSETOF(Trend_Counter_t2, CheckWord));
        STRUCT_CLOSE(TrendInfo_t3, d);
    }
    func();

    CONST_ASSERT(FFP_NVRAMID_TrendInfo_3 + 3 == FFP_NVRAMID_PresAlertConf_3);

    //A few more to copy
    for(u8_least id = FFP_NVRAMID_PresAlertConf_3; id<FFP_NVRAM_ENTRIES_VER_3; id++)
    {
        if(id == FFP_NVRAMID_TravelAlert_3)
        {
            //already taken care of
        }
        else
        {
            //NOTE: CycleCounterAlert would need scaling here
            mn_memcpy(dst + FFP_nvram_map_3[id].offset, src + FFP_nvram_map_2[id + NV_GAP2_2_3].offset, FFP_nvram_map_3[id].length);
        }
    }
    func();

    return ERR_OK;
}

/** \A translation routine
NOTE: Never touch id 0!
NOTE: Scaling of travel trend, trend alert and cycle alert to user range (TB.TRAVEL.TravelRange) is missing
*/
ErrorCode_t FFP_xlatedn_3_2(u8 *dst, const u8 *src, void (*func)(void))
{
    //Copy unchanged and unmoved items
    for(u8_least id = 1U; id<=FFP_NVRAMID_MN_NV_POSITION_LOLO_ALERT_2; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_2[id].offset, src + FFP_nvram_map_3[id].offset, FFP_nvram_map_2[id].length);
        if((id%8U)==0U) //we CAN copy 8 records without watchdog, cant' we?
        {
            func();
        }
    }

    //Separated/extracted record
    {
        //Join TRAVEL
        const MN_NV_TRAVEL_t3 *s = (const void *)(src + FFP_nvram_map_3[FFP_NVRAMID_MN_NV_TRAVEL_3].offset);
        const TravelAlert_t3 *s1 = (const void *)(src + FFP_nvram_map_3[FFP_NVRAMID_TravelAlert_3].offset);
        TravelAlert_t2 *d = (void *)(dst + FFP_nvram_map_2[FFP_NVRAMID_TravelAlert_2].offset);
        d->travel = s->TRAVEL;
        //Join travel alerts
        d->travel_alert[0] = s1->travel_alert[0];
        d->travel_alert[1] = s1->travel_alert[1];
        STRUCT_CLOSE(TravelAlert_t2, d);
    }

    //Copy unchanged but moved items
    for(u8_least id = FFP_NVRAMID_MN_NV_DEVIATION_ALERT_2; id<=FFP_NVRAMID_MN_NV_POSITION_LOLO_ALERT_2; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_2[id].offset, src + FFP_nvram_map_3[id + NV_GAP1_2_3].offset, FFP_nvram_map_3[id].length);
    }
    func();

    for(u8_least id = FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_3; id<FFP_NVRAMID_TrendInfo_3; id++)
    {
        mn_memcpy(dst + FFP_nvram_map_2[id + NV_GAP2_2_3].offset, src + FFP_nvram_map_3[id].offset, FFP_nvram_map_3[id].length);
    }
    func();

    //convert the changed objects
    for(u8_least id = 0; id<3; id++)  //all 3 trend objects
    {
        const TrendInfo_t3 *s = (const void *)(src + FFP_nvram_map_3[id+FFP_NVRAMID_TrendInfo_3].offset);
        TREND_t2 *t = (void *)(dst + FFP_nvram_map_2[id+FFP_NVRAMID_MN_NV_TRAVEL_ACCUMULATION_TREND_2].offset);
        memcpy(t, &(s->tbtrend), MN_OFFSETOF(TREND_t2, CheckWord));
        STRUCT_CLOSE(TREND_t2, t);
        Trend_Counter_t2 *p = (void *)(dst + FFP_nvram_map_2[id+FFP_NVRAMID_Trend_Counter_2].offset);
        memcpy(p, &(s->Trend_Counter), MN_OFFSETOF(Trend_Counter_t2, CheckWord));
        STRUCT_CLOSE(Trend_Counter_t2, p);
    }
    func();

    //A few more to copy
    for(u8_least id = FFP_NVRAMID_PresAlertConf_3; id<FFP_NVRAMID_TravelAlert_3; id++)
    {
        if(id == FFP_NVRAMID_TravelAlert_3)
        {
            CONST_ASSERT(FFP_NVRAMID_TravelAlert_3 + NV_GAP2_2_3 == FFP_NVRAMID_TravelAlert_2);
            //already taken care of
        }
        else
        {
            //NOTE: CycleCounterAlert would need scaling here
            mn_memcpy(dst + FFP_nvram_map_2[id + NV_GAP2_2_3].offset, src + FFP_nvram_map_3[id].offset, FFP_nvram_map_3[id].length);
        }
    }
    func();
    {
        mn_memcpy(dst + FFP_nvram_map_2[FFP_NVRAMID_PresAlertConf_2].offset,
                  src + FFP_nvram_map_3[FFP_NVRAMID_PresAlertConf_3].offset,
                  FFP_nvram_map_3[FFP_NVRAMID_PresAlertConf_3].length);
        mn_memcpy(dst + FFP_nvram_map_2[FFP_NVRAMID_Act3Min_2].offset,
                  src + FFP_nvram_map_3[FFP_NVRAMID_Act3Min_3].offset,
                  FFP_nvram_map_3[FFP_NVRAMID_Act3Min_3].length);
    }

    return ERR_OK;
}

/* This line marks the end of the source */
