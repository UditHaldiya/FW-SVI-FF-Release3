#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <ptb.h>
#include "mnhart2ff.h"
#include "errcodes.h"

#define INDEX_POSERR_COMP11 11
#define SIZE_POSERR_COMP    (INDEX_POSERR_COMP11+1)
typedef struct Histogram_PosErr_t
{
    u32     sum[2]; //!< accumulation batches, FIFO style
    u32     n[2]; //!< Count per batch
} Histogram_PosErr_t;

#define NUM_OF_POSITION_HISTOGRAM_ITEM 12

typedef struct HistogramPosErrNV_t
{
    Histogram_PosErr_t entry[SIZE_POSERR_COMP];
    u16 CheckWord;
} HistogramPosErrNV_t;

typedef struct HistogramPosNV_t
{
    u32 TotalTime; //!< in 1 second increments
    u32 array[NUM_OF_POSITION_HISTOGRAM_ITEM];
    u16 CheckWord;
} HistogramPosNV_t;

/*
typedef struct
{
    u32 zero_to_5;
    u32 five_to_10;
    u32 ten_to_20;
    u32 twenty_to_30;
    u32 thirty_to_40;
    u32 forty_to_50;
    u32 fifty_to_60;
    u32 sixty_to_70;
    u32 seventy_to_80;
    u32 eighty_to_90;
    u32 ninety_to_95;
    u32 ninety_five_to_100;
} Position_Histogram_internal_t;
*/

/* the public interfaces for this module */
extern void UpdateHistogram(const T_FBIF_BLOCK_INSTANCE * p_block_instance);
extern u16  OnWritePosErrHistogram(const T_FBIF_PTB *  p_PTB);
extern fferr_t  OnWritePositionHistogram(const T_FBIF_WRITE_DATA* p_write);
extern fferr_t  histogram_ReadPosition(const T_FBIF_BLOCK_INSTANCE* p_block_instance);
extern fferr_t  histogram_ReadPositionErr(const T_FBIF_BLOCK_INSTANCE* p_block_instance);

extern void histogram_Init(void);

//NV storage interface:
extern const HistogramPosNV_t *histogram_GetPosData(HistogramPosErrNV_t *dst);
extern ErrorCode_t histogram_SetPosData(const HistogramPosNV_t *src);
UNTYPEACC(histogram_SetPosData, histogram_GetPosData);
extern const HistogramPosErrNV_t *histogram_GetPosErrData(HistogramPosErrNV_t *dst);
extern ErrorCode_t histogram_SetPosErrData(const HistogramPosErrNV_t *src);
UNTYPEACC(histogram_SetPosErrData, histogram_GetPosErrData);

#endif // HISTOGRAM_H_

