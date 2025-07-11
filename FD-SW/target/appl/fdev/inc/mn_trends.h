#ifndef MN_TRENDS_H_
#define MN_TRENDS_H_

#include <ptb.h>
#include "errcodes.h"

typedef struct AccTrend_t
{
    u32 count;
    u32 sum;
} AccTrend_t; //! Integer trend

typedef struct Trend_Counter_t
{
    AccTrend_t day;
    AccTrend_t week;
    AccTrend_t month;
    AccTrend_t year;
    u16 CheckWord;
} Trend_Counter_t;//! Integer trend

typedef struct TrendInfo_t
{
    Trend_Counter_t Trend_Counter;
    _TREND tbtrend;
    u16 CheckWord;
} TrendInfo_t; //! Atomic type of trend artifacts


extern void UpdateTrends(const T_FBIF_BLOCK_INSTANCE * p_block_instance);

enum
{
    index_travel_acc = (0),
    index_cycle_counter = (1),
    index_position_err = (2),
    index_trend_end = (3)
};
extern void trend_RequestRestart(u8_least tindex);

extern const TrendInfo_t *tbtrend_Get(u8_least index, TrendInfo_t *dst);
extern ErrorCode_t tbtrend_Set(u8_least index, const TrendInfo_t *src);
UNTYPEACCX(tbtrend_Set, tbtrend_Get);

#endif //MN_TRENDS_H_
