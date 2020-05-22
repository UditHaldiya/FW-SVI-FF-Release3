/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_trends.c
    \brief utility about trend structure moved outside TB block

    CPU: Any

    OWNER: AK
*/
#include <limits.h>
#include <float.h>
#include <softing_base.h>
#include <ptb.h>
#include <fbif_dcl.h>
#include "numutils.h"
#include "mn_trends.h"
#include "time_defs.h"
#include "mn_advanced.h"

#include "crc.h"
#include "mnassert.h"
#include "nvffext.h"
#include "ff2nvram.h"
#include "syncpatches.h"
#include "appl_alert.h"
#include <math.h>

//------------ NVMEM interface -------------------
static TrendInfo_t TrendInfo[index_trend_end];

/** \brief Standard dumb "get" accessor
*/
const TrendInfo_t *tbtrend_Get(u8_least index, TrendInfo_t *dst)
{
    return STRUCT_GET(&TrendInfo[index], dst);
}

/** \brief Standard dumb "set" accessor. Anything goes.
*/
ErrorCode_t tbtrend_Set(u8_least index, const TrendInfo_t *src)
{
    TrendInfo_t default_trend;
    if(src == NULL)
    {
        memset(&default_trend, 0, MN_OFFSETOF(TrendInfo_t, CheckWord));
        src = &default_trend;
    }
    Struct_Copy(TrendInfo_t, &TrendInfo[index], src);
    return ERR_OK;
}

//------------ Rescaling for presentation layer -------------------
#define NUM_BUCKETS (sizeof(_TREND)/ELEMSIZE(_TREND, currently_collected))
static u32 tbtrend_RescaleTravelAcc(float32 TravelRange, _TREND *dst)
{
    float32 scale = TravelRange * 0.01F;
    float32 result  = scale * TrendInfo[index_travel_acc].tbtrend.currently_collected;
    u32 now = (u32)result;
    if(dst != NULL)
    {
        dst->currently_collected = now;
        const u32 *bucket_src = (const void *)&TrendInfo[index_travel_acc].tbtrend;
        u32 *bucket_dst = (void *)dst;
        for(u8_least n=1U; n<NUM_BUCKETS; n++)
        {
            result = scale * bucket_src[n];
            bucket_dst[n] = (u32)(result);
        }
    }
    return now;
}

static u32 tbtrend_RescaleDummy(float32 TravelRange, _TREND *dst, u8_least index)
{
    UNUSED_OK(TravelRange);
    u32 now = TrendInfo[index].tbtrend.currently_collected;
    if(dst != NULL)
    {
        dst->currently_collected = now;
        const u32 *bucket_src = (const void *)&TrendInfo[index].tbtrend;
        u32 *bucket_dst = (void *)dst;
        for(u8_least n=1U; n<NUM_BUCKETS; n++)
        {
            bucket_dst[n] = bucket_src[n];
        }
    }
    return now;
}

static u32 tbtrend_RescaleCycleCounter(float32 TravelRange, _TREND *dst)
{
    return tbtrend_RescaleDummy(TravelRange, dst, index_cycle_counter);
}

static u32 tbtrend_RescalePositionErr(float32 TravelRange, _TREND *dst)
{
    return tbtrend_RescaleDummy(TravelRange, dst, index_position_err);
}

// ------------------ ? ----------------------
#define POSITION_ERROR_TREND_DEFINITION    (10)

typedef u32 func_GetDiff_t(const T_FBIF_PTB *p_PTB, float32 deadband);
typedef u32 func_CountNewPeriodValue_t(Trend_Counter_t* p_trend_counter, u8 trend_counter_offset);

typedef struct TrendInterface_t
{
    Trend_Counter_t* trend_counter;
    func_GetDiff_t* GetDiff;
    func_CountNewPeriodValue_t* CountNewPeriodValue;
    void (*init_func)(const T_FBIF_PTB *p_PTB);
    u32 (*rescale_func)(float32 TravelRange, _TREND *dst);
    float32 (*calc_deadband)(const T_FBIF_PTB *p_PTB);
    u16 trend_offset;
    u8 rel_idx;
    bool_t is_cumulative;
} TrendInterface_t;

/***********************************************************************************************/

static float32 pre_pos = FLT_MAX;
static void initAccDiff(const T_FBIF_PTB *  p_PTB)
{
    pre_pos = p_PTB->working_pos.value;
    alert_RestartTravelAlert();
}

static float32 trac_residual = 0.0F; //! For less than 1%; don't care if lose it
static u32 GetTravelAccDiff(const T_FBIF_PTB *  p_PTB, float32 deadband)
{
    float32 ftemp;
    u32 ret;

    ftemp = ABS(pre_pos - p_PTB->working_pos.value);
    ftemp += trac_residual;
    if(ftemp > deadband) //Use unscaled
    {
        pre_pos = p_PTB->working_pos.value;
        float32 f = floorf(ftemp);
        trac_residual = ftemp - f;
        ret = (u32)f;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

static float32 calc_travel_deadband(const T_FBIF_PTB *p_PTB)
{
    UNUSED_OK(p_PTB);
    const TravelAlert_t *p = travel_Get(NULL);
    float32 deadband = p->travel_alert[0].deadband_ab;
    return deadband;
}

static float32 pre_working_pos = FLT_MAX;
static enum {dir_unknown, dir_down, dir_up} is_positive_direction = dir_unknown; //positive direction is true
static void initCycleDiff(const T_FBIF_PTB *  p_PTB)
{
    pre_working_pos = p_PTB->working_pos.value;
    is_positive_direction = dir_unknown;
    alert_RestartCyclelAlert();
}

/** \brief
\param p_PTB - a ponter to runtime TB data
\param deadband - a deadband in stantard units (%range)
\return increment in cycle counter
*/
static u32 GetCycleCounterDiff(const T_FBIF_PTB *p_PTB, float32 deadband)
{
    float32 ftemp;
    u32 ret = 0;

    float32 wpos = p_PTB->working_pos.value;
    ftemp = (pre_working_pos - wpos);
    if(ABS(ftemp) > deadband)
    {
        if(is_positive_direction == dir_unknown)
        {
            if(ftemp < 0.0F)
            {
                is_positive_direction = dir_down;
            }
            else
            {
                is_positive_direction = dir_up;
            }
        }
        pre_working_pos = wpos;
        if((ftemp < 0.0F) && (is_positive_direction == dir_up))
        {
            is_positive_direction = dir_down;
            ret = 1u;
        }
        if((ftemp > 0.0F) && (is_positive_direction == dir_down))
        {
            is_positive_direction = dir_up;
            ret = 1u;
        }
    }
    return ret;
}

static float32 calc_cycle_deadband(const T_FBIF_PTB *p_PTB)
{
    UNUSED_OK(p_PTB);
    const CycleCounterAlert_t *p = ccalert_Get(NULL);
    float32 deadband = p->ccalert[0].deadband_ab;
    return deadband;
}


static void initErrDiff(const T_FBIF_PTB *  p_PTB)
{
    //Nothing to do - this one is not stateful
    UNUSED_OK(p_PTB);
}
static u32 GetPositionErrDiff(const T_FBIF_PTB *  p_PTB, float32 deadband)
{
    UNUSED_OK(deadband);
    osif_disable_all_tasks(); //non-atomic operation follows
    float32 t_value = p_PTB->working_sp.value - p_PTB->working_pos.value;
    osif_enable_all_tasks();
    t_value = ABS(t_value) * POSITION_ERROR_TREND_DEFINITION;
    MN_DBG_ASSERT(t_value < UINT32_MAX);
    return (u32)t_value;
}

static float32 calc_poserr_deadband(const T_FBIF_PTB *p_PTB)
{
    return p_PTB->deviation_alert.__deviation_deadband;
}

static u32 CountNewPeriodValueForTraveAcc(Trend_Counter_t* p_trend_counter, u8 trend_counter_offset)
{
    AccTrend_t* p_acc_trend = (AccTrend_t*)(void*)((u8*)p_trend_counter + trend_counter_offset);

    return p_acc_trend->sum;
}

static u32 CountNewPeriodValueForCycleCounter(Trend_Counter_t* p_trend_counter, u8 trend_counter_offset)
{
    AccTrend_t* p_acc_trend = (AccTrend_t*)(void*)((u8*)p_trend_counter + trend_counter_offset);

    return p_acc_trend->sum;
}

/**
\return a u32 bitmap of the floating-point value of accumulated error
*/
static u32 CountNewPeriodValueForPositionErr(Trend_Counter_t* p_trend_counter, u8 trend_counter_offset)
{
    AccTrend_t* p_acc_trend = (AccTrend_t*)(void*)((u8*)(p_trend_counter) + trend_counter_offset);

    u32 ret = 0;
    if(p_acc_trend->count != 0)
    {
        float32 t = ((float32)p_acc_trend->sum/POSITION_ERROR_TREND_DEFINITION)/p_acc_trend->count;
        ieee754_t ret1 = float2ieee(t);
        ret = ret1; //lint !e633 assignment from strong type
    }
    return ret;
}

#define trend_counter_travel_acc (TrendInfo[index_travel_acc].Trend_Counter)
#define trend_counter_cycle_counter (TrendInfo[index_cycle_counter].Trend_Counter)
#define trend_counter_position_err (TrendInfo[index_position_err].Trend_Counter)

/*Trend parameters in this table will be constantly calculated*/
const TrendInterface_t trend_list[] =
{
    [index_travel_acc] =
    {
        .trend_offset = MN_OFFSETOF(T_FBIF_PTB, travel_accumulation_trend),
        .trend_counter = &trend_counter_travel_acc,
        .GetDiff = GetTravelAccDiff,
        .CountNewPeriodValue = CountNewPeriodValueForTraveAcc,
        .init_func = initAccDiff,
        .rescale_func = tbtrend_RescaleTravelAcc,
        .calc_deadband = calc_travel_deadband,
        .rel_idx = REL_IDX_PTB_TRAVEL_ACCUMULATION_TREND,
        .is_cumulative = true,
    },
    [index_cycle_counter] =
    {
        .trend_offset = MN_OFFSETOF(T_FBIF_PTB, cycle_counter_trend),
        .trend_counter = &trend_counter_cycle_counter,
        .GetDiff = GetCycleCounterDiff,
        .CountNewPeriodValue = CountNewPeriodValueForCycleCounter,
        .init_func = initCycleDiff,
        .rescale_func = tbtrend_RescaleCycleCounter,
        .calc_deadband = calc_cycle_deadband,
        .rel_idx = REL_IDX_PTB_CYCLE_COUNTER_TREND,
        .is_cumulative = true,
    },
    [index_position_err] =
    {
        .trend_offset = MN_OFFSETOF(T_FBIF_PTB, position_error_trend),
        .trend_counter = &trend_counter_position_err,
        .GetDiff = GetPositionErrDiff,
        .CountNewPeriodValue = CountNewPeriodValueForPositionErr,
        .init_func = initErrDiff,
        .rescale_func = tbtrend_RescalePositionErr,
        .calc_deadband = calc_poserr_deadband,
        .rel_idx = REL_IDX_PTB_POSITION_ERROR_TREND,
        .is_cumulative = false,
    },
};

/***********************************************************************************************/

static void UpdateTrendDay(const TrendInterface_t* p_trend_interface, _TREND* p_trend)
{
    p_trend->three_days_ago = p_trend->previous_day;
    p_trend->previous_day = p_trend->last_day;
    p_trend->last_day = p_trend->today;
    p_trend->today = p_trend->currently_collected;
    if(!p_trend_interface->is_cumulative)
    {
        p_trend->currently_collected = 0u;
        p_trend_interface->trend_counter->day.sum = 0;
    }
    p_trend_interface->trend_counter->day.count -= TIME_INSECOND_ONEDAY;
}

static void UpdateTrendWeek(const TrendInterface_t* p_trend_interface, _TREND* p_trend)
{
    p_trend->three_weeks_ago = p_trend->previous_week;
    p_trend->previous_week = p_trend->last_week;
    p_trend->last_week = p_trend->current_week;
    p_trend->current_week = p_trend_interface->CountNewPeriodValue(p_trend_interface->trend_counter, MN_OFFSETOF(Trend_Counter_t, week));
    if(!p_trend_interface->is_cumulative)
    {
        p_trend_interface->trend_counter->week.sum = 0;
    }
    p_trend_interface->trend_counter->week.count -= TIME_INSECOND_ONEWEEK;
}

static void UpdateTrendMonth(const TrendInterface_t* p_trend_interface, _TREND* p_trend)
{
    p_trend->three_months_ago = p_trend->previous_month;
    p_trend->previous_month = p_trend->last_month;
    p_trend->last_month = p_trend->current_month;
    p_trend->current_month = p_trend_interface->CountNewPeriodValue(p_trend_interface->trend_counter, MN_OFFSETOF(Trend_Counter_t, month));
    if(!p_trend_interface->is_cumulative)
    {
        p_trend_interface->trend_counter->month.sum = 0;
    }
    p_trend_interface->trend_counter->month.count -= TIME_INSECOND_ONEMONTH;
}

static void UpdateTrendYear(const TrendInterface_t* p_trend_interface, _TREND* p_trend)
{
    p_trend->three_years_ago = p_trend->previous_12_months;
    p_trend->previous_12_months = p_trend->last_12_months;
    p_trend->last_12_months = p_trend->current_12_months;
    p_trend->current_12_months = p_trend_interface->CountNewPeriodValue(p_trend_interface->trend_counter, MN_OFFSETOF(Trend_Counter_t, year));
    if(!p_trend_interface->is_cumulative)
    {
        p_trend_interface->trend_counter->year.sum = 0;
    }
    p_trend_interface->trend_counter->year.count -= TIME_INSECOND_ONEYEAR;
}
// Update element "CURRENTLY COLLECTION" of the record
static void UpdateTrendCurrent(const TrendInterface_t* p_trend_interface, _TREND *p_trend, u32 diff)
{
    p_trend_interface->trend_counter->day.count += 1;

    p_trend_interface->trend_counter->day.sum += diff;

    p_trend->currently_collected = p_trend_interface->CountNewPeriodValue(p_trend_interface->trend_counter, MN_OFFSETOF(Trend_Counter_t, day));

    if (p_trend_interface->trend_counter->day.count >= TIME_INSECOND_ONEDAY)
    {
        p_trend_interface->trend_counter->week.count += TIME_INSECOND_ONEDAY;
        p_trend_interface->trend_counter->month.count += TIME_INSECOND_ONEDAY;
        p_trend_interface->trend_counter->year.count += TIME_INSECOND_ONEDAY;
        UpdateTrendDay(p_trend_interface, p_trend);
    }
    if (p_trend_interface->trend_counter->week.count >= TIME_INSECOND_ONEWEEK)
    {
        p_trend_interface->trend_counter->week.sum = p_trend_interface->trend_counter->day.sum;
        UpdateTrendWeek(p_trend_interface, p_trend);
    }
    if (p_trend_interface->trend_counter->month.count >= TIME_INSECOND_ONEMONTH)
    {
        p_trend_interface->trend_counter->month.sum = p_trend_interface->trend_counter->day.sum;
        UpdateTrendMonth(p_trend_interface, p_trend);
    }
    if (p_trend_interface->trend_counter->year.count >= TIME_INSECOND_ONEYEAR)
    {
        p_trend_interface->trend_counter->year.sum = p_trend_interface->trend_counter->day.sum;
        UpdateTrendYear(p_trend_interface, p_trend);
    }
}

static u32      LastTime;
static u32      LastWriteTime;
/** \brief Initializes RAM state of all trends
*/
static void tbtrends_Init(const T_FBIF_PTB *p_PTB)
{
    LastTime = osif_get_time_in_ms();
    LastWriteTime = LastTime;

    for(u8_least n=0; n<NELEM(trend_list); n++)
    {
        trend_list[n].init_func(p_PTB);
    }
}

/*lint -esym(457 458, trend_restart)
EXPLANATION
Each element is atomic, and only individual members are
of importance. The whole array doesn't matter
*/
static bool_t trend_restart[NELEM(trend_list)];

/** \brief Request a trend restart; the action is delegated to UpdateTrends
\param tindex - one of predefined drend indices (cf. mn_trends.h)
*/
void trend_RequestRestart(u8_least tindex)
{
    if(tindex < NELEM(trend_restart))
    {
        trend_restart[tindex] = true;
    }
}

/** \brief update the trend of positon error about every 1 second
            when transducer block excute once
    \param p_block_instance: pointer to the instance of transducer block
*/
void UpdateTrends(const T_FBIF_BLOCK_INSTANCE * p_block_instance)
{
    T_FBIF_PTB *    p_PTB = p_block_instance->p_block_desc->p_block;
    static bool_t first_run = true;

    bool_t status_ok = ((p_PTB->working_pos.status & p_PTB->working_sp.status & SQ_GOOD) == SQ_GOOD);
    if(status_ok)
    {
        if(first_run)
        {
            //Initialization
            tbtrends_Init(p_PTB);
            first_run = false;
        }
    }
    else
    {
        first_run = true;
    }

    u32 TimeDiff = osif_get_ms_since(LastTime);
    if (TimeDiff < NUMBER_OF_MS_IN_SECOND)
    {
        if(status_ok)
        {
            // less than 1 second, do nothing except checking for restart
            for(u16_least i = 0; i < NELEM(trend_list); i++)
            {
                if(trend_restart[i])
                {
                    /* We need to do things atomically atomically in RAM.
                    For RAM, we can afford to disable task switching
                    We will write to NVMEM after that.
                    */
                    osif_disable_all_tasks();
                    trend_list[i].init_func(p_PTB);

                    ErrorCode_t err1 = tbtrend_Set(i, NULL); //Use the fact this doesn't write to NVMEM at all
                    UNUSED_OK(err1); //can't fail setting defaults
                    osif_enable_all_tasks();

                    ErrorCode_t err = ram2nvramAtomic(NVRAMID_TrendInfo+i);
                    if(err == ERR_OK)
                    {
                        trend_restart[i] = false;
                    }
                }
            }
        }
    }
    else
    {
        LastTime += NUMBER_OF_MS_IN_SECOND;

        if(status_ok)
        {
                //write every minute
            bool_t save = (osif_get_ms_since(LastWriteTime) >= NUMBER_OF_MS_IN_MINUTE);

            if(save)
            {
                LastWriteTime += NUMBER_OF_MS_IN_MINUTE;
            }

            if(((p_PTB->mode_blk.actual & (MODE_OS|MODE_LO)) == 0) && !first_run)
            {
                float32 TravelRange = p_PTB->travel.TravelRange;
                for(u16_least i = 0; i < NELEM(trend_list); i++)
                {
                    float32 deadband = trend_list[i].calc_deadband(p_PTB);
                    u32 diff = trend_list[i].GetDiff(p_PTB, deadband);

                    if ( ffcheck_ReadBitmap(p_block_instance, trend_list[i].rel_idx))
                    {
                        UpdateTrendCurrent(&trend_list[i], &TrendInfo[i].tbtrend, diff);

                        _TREND *scaled_trend = (_TREND*)(void*)((u8*)p_PTB + trend_list[i].trend_offset);
                        u32 rescaled = trend_list[i].rescale_func(TravelRange, scaled_trend); //Needed somewhere; in the background task is cheap
                        UNUSED_OK(rescaled);
                    }
                    if(save)
                    {
                        ErrorCode_t err = nvmem_RequestWriteExt(NVRAMID_TrendInfo+i, 1); //always defer
                        UNUSED_OK(err); //can't fail on deferral
                    }
                }// for loop
            }
            else
            {
                //tbtrends_Init(p_PTB);
            }
        }//TimeDiff
    }
}

