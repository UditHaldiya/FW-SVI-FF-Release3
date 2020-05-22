/*
Copyright 2012-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file histogram.c
    \brief "histogram parameters of transduser block" handler

NOTE: This implementation relies on histograms not EVER being used internally.
Only PTB Read handler populates PTB parameters.
If/when this assumption is no longer valid, the read handler interfaces should
be called from Update functions; such handlers may be made more lightweight but
mind initialization

    CPU: Any

    OWNER: AK
*/

#include <softing_base.h>
#include <ptb.h>
#include "numutils.h"
#include "histogram.h"
#include "time_defs.h"
#include "mn_advanced.h"

#include "mnassert.h"
#include "crc.h"
#include "nvffext.h"

  #define  MODULE_ID      (COMP_FAPP + MOD_APPL_TRN)

// for positon error histogram,
#define INDEX_POSERR_COMP0  0
/*
#define INDEX_POSERR_COMP1  1
#define INDEX_POSERR_COMP2  2
#define INDEX_POSERR_COMP3  3
#define INDEX_POSERR_COMP4  4
#define INDEX_POSERR_COMP5  5
#define INDEX_POSERR_COMP6  6
#define INDEX_POSERR_COMP7  7
#define INDEX_POSERR_COMP8  8
#define INDEX_POSERR_COMP9  9
*/
#define INDEX_POSERR_COMP10 10
#define INTERVAL_OF_STORE   40 //! Number of 1-second intervals to skip saving the histogram

/* the cache for history positon err, the sum and counter */
static MN_NO_INIT HistogramPosErrNV_t hist_poserr;
/* the cache for posistion histogram internal counter value*/
static MN_NO_INIT HistogramPosNV_t hist_pos;

//Standard read accessors
const HistogramPosNV_t *histogram_GetPosData(HistogramPosErrNV_t *dst)
{
    return STRUCT_TESTGET(&hist_pos, dst);
}
const HistogramPosErrNV_t *histogram_GetPosErrData(HistogramPosErrNV_t *dst)
{
    return STRUCT_TESTGET(&hist_poserr, dst);
}

//A simplistic write accessor
//lint -esym(457 458, histogram_SetPosErrData) Lint *sometimes* treats & as access!
ErrorCode_t histogram_SetPosErrData(const HistogramPosErrNV_t *src)
{
    u8_least i;
    HistogramPosErrNV_t h; //default
    if(src == NULL)
    {
        for(i=0; i<NELEM(h.entry); i++)
        {
            h.entry[i].n[0] = 0U;
            h.entry[i].n[1] = 0U;
            h.entry[i].sum[0] = 0U;
            h.entry[i].sum[1] = 0U;
        }
        src = &h;
    }
    Struct_Copy(HistogramPosErrNV_t, &hist_poserr, src);
    return ram2nvramAtomic(NVRAMID_HistogramPosErrNV);
}

//lint -esym(457, histogram_SetPosData) Lint *sometimes* treats & as access!

//A simplistic write accessor
ErrorCode_t histogram_SetPosData(const HistogramPosNV_t *src)
{
    ErrorCode_t err = ERR_OK;
    u8_least i;
    HistogramPosNV_t h; //default
    if(src == NULL)
    {
        h.TotalTime = 0;
        for(i=0; i<NELEM(h.array); i++)
        {
            h.array[i] = 0;
        }
        src = &h;
    }
    //Basic data check
    if(src->TotalTime == 0)
    {
        for(i=0; i<NELEM(h.array); i++)
        {
            if(src->array[i] != 0)
            {
                err = ERR_INVALID_PARAMETER;
                break;
            }
        }
    }
    if(err == ERR_OK)
    {
        Struct_Copy(HistogramPosNV_t, &hist_pos, src);
        err = ram2nvramAtomic(NVRAMID_HistogramPosNV);
    }
    return err;
}

#if 0
static MN_NO_INIT Histogram_PosErr_t Histogram_PosErr[SIZE_POSERR_COMP];
static MN_NO_INIT u32 Position_Histogram_internal_array[NUM_OF_POSITION_HISTOGRAM_ITEM];
#endif

static u32 writeCounter = 0; //! interval counter for writing to NVRAM

#if 0
void histogram_Init(void)
{
    u16 len = sizeof(Position_Histogram_internal_array);
    ErrorCode_t err = logf_Retrieve(Position_Histogram_internal_array, &len, LOGF_POS_HIST_ARRAY_ID, 0);
    if(err != ERR_OK)
    {
        //missing or corrupted file
        mn_memset(Position_Histogram_internal_array, 0, sizeof(Position_Histogram_internal_array));
    }
    len = sizeof(Histogram_PosErr);
    err = logf_Retrieve(Histogram_PosErr, &len, LOGF_POS_HISTOGRAM_ID, 0);
    if(err != ERR_OK)
    {
        //missing or corrupted file
        mn_memset(Histogram_PosErr, 0, sizeof(Histogram_PosErr));
    }
}
#endif //0

static void histogram_UpdatePosition(const T_FBIF_PTB *  p_PTB)
{
    s32     scaledPostion;
#if 1
    if (MODE_AUTO != p_PTB->mode_blk.actual)
    {
        return;
    }

    if (SQ_GOOD != (p_PTB->working_pos.status & QUALITY_MASK) ) // SQ_GOOD_CAS?
    {
        return;
    }
#endif
    scaledPostion = (s32)(p_PTB->working_pos.value);

/*      component_0     TOTAL
        component_1     5%-CLOSED
        component_2    < 10%
        component_3    < 20%
        component_4    < 30%
        component_5    < 40%
        component_6    < 50%
        component_7    < 60%
        component_8    < 70%
        component_9    < 80%
        component_10   < 90%
        component_11   < 95%
        component_12   < 95%-OPEN   */

    // TOTAL
    //p_PTB->position_histogram.component_0 += 1;

    s32 index;
    // 5% - close
    if (scaledPostion <= 4)
    {
        index = 0;
    }

    // 10% - 90%
    else if (scaledPostion <= 89)
    {
        index = scaledPostion / 10 + 1;
    }

    // 90% - 95%
    else if (scaledPostion <= 94)
    {
        index = 10;
    }
    // 95% - open
    else
    {
        index = 11;
    }
    MN_ENTER_CRITICAL();
        u32 t = hist_pos.array[index];
        t = MAX(t, t+1U); //saturation
        storeMemberInt(&hist_pos, array[index], t);
        t = hist_pos.TotalTime;
        t = MAX(t, t+1U); //saturation
        storeMemberInt(&hist_pos, TotalTime, t);
    MN_EXIT_CRITICAL();
}

#if 0
static void histogram_UpdateTotalTime(T_FBIF_PTB *  p_PTB)
{
#if 1
    if (MODE_AUTO != p_PTB->mode_blk.actual)
    {
        return;
    }
    if (SQ_GOOD != (p_PTB->working_pos.status & QUALITY_MASK) ) // SQ_GOOD_CAS?
    {
        return;
    }
#endif
    // TOTAL_TIME
    p_PTB->position_histogram.component_0 += 1;
}
#endif //0

#define ERROR_HISTOGRAM_SCALE    (100)
#define HISTOGRAM_POSERR_M  0xFFFFFFAU
/* A bucket's worth van be a few hours if error is large or up to 49+ days if
error is below 1%. Time is "stopwatch" time of position being within the bucket
*/
#define POSERR_CLAMP_VALUE(scale) ((u32)(200.0*(cdouble_t)scale))
/* \brief Updates the poserr histogram bucket

Up to first HISTOGRAM_POSERR_M samples in the bucket, calculates average
After that, calculates average of the last N samples where N falls
anywhere between HISTOGRAM_POSERR_M and 2*HISTOGRAM_POSERR_M, or less
if error is large.
The calculation is completed at reporting time, see histogram_ReadPositionErr()
\param index - an index of the bucket
\param err - absolute error scaled to integer
*/
static void histogram_CalcPoserrComponent(s32 index, u32 err)
{
    if(index >= SIZE_POSERR_COMP)
    {
        return;
    }

    osif_disable_all_tasks();
    Histogram_PosErr_t h = hist_poserr.entry[index];
    osif_enable_all_tasks();

    u32 batch_index = 0U;
    if(h.n[1] != 0U)
    {
        batch_index = 1U;
    }

    /* Accumulate but watch for overflow
    */
    u32 oldval = h.sum[batch_index];
    err = MIN(err, POSERR_CLAMP_VALUE(ERROR_HISTOGRAM_SCALE));
    u32 newval = oldval + err;
    if( (newval < oldval) /*overflow*/
       || (h.n[batch_index] >= HISTOGRAM_POSERR_M) /* batch filled up */ )
    {
        if(batch_index == 0U)
        {
            /* Simply switch to the still-empty second batch:
            batch_index = 1U is accomplished by starting n[1] (see below)
            */
        }
        else
        {
            //Discard first batch and replace with the second
            h.sum[0] = h.sum[1];
            h.n[0] = h.n[1];
        }
        /* In any case, we are starting with batch 1, which we prime here
        */
        h.sum[1] = err;
        h.n[1] = 1U;
    }
    else
    {
        //Normal textbook case
        h.sum[batch_index] = newval;
        h.n[batch_index]++;
    }

    osif_disable_all_tasks();
    for(u8_least i= 0U; i<NELEM(h.sum); i++)
    {
        storeMemberInt(&hist_poserr, entry[index].sum[i], h.sum[i]);
        storeMemberInt(&hist_poserr, entry[index].n[i], h.n[i]);
    }
    osif_enable_all_tasks();
}

fferr_t  histogram_ReadPositionErr(const T_FBIF_BLOCK_INSTANCE* p_block_instance)
{
    T_FBIF_PTB* p_PTB = p_block_instance->p_block_desc->p_block;
    struct buckets_t
    {
        float32 bucket[12];
    } *p = (void *)&p_PTB->position_error_histogram;

    //Assert my assumptions:
    //1. (No) padding
    CONST_ASSERT(sizeof(*p) == sizeof(p_PTB->position_error_histogram));
    //2. Alignment
    //MN_DBG_ASSERT(p->bucket[0] == p_PTB->position_error_histogram.component_0);
    for(u8_least i=0; i<NELEM(p->bucket); i++)
    {
        if(hist_poserr.entry[i].n[0] == 0U)
        {
            p->bucket[i] = 0.0F; //never been in the bucket
        }
        else
        {
            osif_disable_all_tasks();
            u32 denom = hist_poserr.entry[i].n[0] + hist_poserr.entry[i].n[0];
            p->bucket[i] = (((float32)hist_poserr.entry[i].sum[0] + (float32)hist_poserr.entry[i].sum[1])
                / ERROR_HISTOGRAM_SCALE)
                / (float32)denom;
            osif_enable_all_tasks();
        }
    }

    return E_OK;
}

static void histogram_UpdatePositionErr(const T_FBIF_PTB *  p_PTB)
{
    u32         err;
    s32         scaledPosition;

    if (MODE_AUTO != p_PTB->mode_blk.actual)
    {
        return;
    }

    if (SQ_GOOD != (p_PTB->working_pos.status & QUALITY_MASK) ) // SQ_GOOD_CAS?
    {
        return;
    }

    if (SQ_GOOD != (p_PTB->working_sp.status & QUALITY_MASK) ) // SQ_GOOD_CAS?
    {
        return;
    }

    // position error
    float32 fVal = p_PTB->working_sp.value - p_PTB->working_pos.value;
    fVal = ABS(fVal) * ERROR_HISTOGRAM_SCALE + 0.5F; //rounding
    err = (u32)fVal;
    scaledPosition = (s32)(p_PTB->working_pos.value);

/* component_0    5%-CLOSED
   component_1  < 10%
   component_2  < 20%
   component_3  < 30%
   component_4  < 40%
   component_5  < 50%
   component_6  < 60%
   component_7  < 70%
   component_8  < 80%
   component_9  < 90%
   component_10 < 95%
   component_11   95%-OPEN  */


    s32 index;

    // 5% - close
    if (scaledPosition <= 4)
    {
        index = INDEX_POSERR_COMP0;
    }
    // 10% - 90%
    else if (scaledPosition <= 89)
    {
        index = scaledPosition / 10 + 1;
    }
    // 95%
    else if (scaledPosition <= 94)
    {
        index = INDEX_POSERR_COMP10;
    }
    // 95% - open
    else
    {
        index = INDEX_POSERR_COMP11;
    }
    histogram_CalcPoserrComponent(index, err);
}


/* \brief update the histogram of positon, position err
            when transducer block excute once
    \param[in] p_PTB: pointer to the objects of transducer block
*/
void UpdateHistogram(const T_FBIF_BLOCK_INSTANCE * p_block_instance)
{
    u32         TimeDiff;
    static u32      LastTime;
    static bool_t first_run = true;
    bool_t PosFlag, PosErrFlag;

    //check the parameter is readable or not.
    PosFlag = ffcheck_ReadBitmap(p_block_instance, REL_IDX_PTB_POSITION_HISTOGRAM);
    PosErrFlag = ffcheck_ReadBitmap(p_block_instance, REL_IDX_PTB_POSITION_ERROR_HISTOGRAM);

    //if both the two histogram of positon and position err can be read
    //return and do not need to anything.
    if ((!PosFlag) && (!PosErrFlag))
    {
        return;
    }

    if(first_run)
    {
        //Initialization
        LastTime = osif_get_time_in_ms();
        first_run = false;
    }
    else
    {
        TimeDiff = osif_get_ms_since(LastTime);

        // less than 1 second, do nothing
        if (TimeDiff < NUMBER_OF_MS_IN_SECOND)
        {
        }
        else
        {
            LastTime += NUMBER_OF_MS_IN_SECOND;
            if (PosFlag)
            {
                //histogram_UpdateTotalTime(p_block_instance->p_block_desc->p_block);
                histogram_UpdatePosition(p_block_instance->p_block_desc->p_block);
            }
            if (PosErrFlag)
            {
                histogram_UpdatePositionErr(p_block_instance->p_block_desc->p_block);
            }

            writeCounter ++;
            if (writeCounter >= INTERVAL_OF_STORE)
            {
                //Use delayed write
                ErrorCode_t err1 = ERR_OK;;
                if (PosErrFlag)
                {
                    err1 = nvmem_RequestWrite(NVRAMID_HistogramPosErrNV);
                }
                ErrorCode_t err2=ERR_OK;
                if (PosFlag)
                {
                    err2 = nvmem_RequestWrite(NVRAMID_HistogramPosNV);
                }
                if((err1 == ERR_OK) && (err2==ERR_OK))
                {
                    writeCounter = 0;
                }
                else
                {
                    //will try next time
                }
            }
        }
    }
}

/* \brief reset the internal sum and counter for position error histogram
    param in:
        p_PTB: pointer to the objects of transducer block
    return:
        void
*/
u16 OnWritePosErrHistogram(const T_FBIF_PTB *  p_PTB)
{
    u32 i;
    struct buckets_t
    {
        float32 bucket[12];
    } const *p = (const void *)&p_PTB->position_error_histogram;

    //Assert my assumptions:
    //1. (No) padding
    CONST_ASSERT(sizeof(*p) == sizeof(p_PTB->position_error_histogram));
    //2. Alignment
    //MN_DBG_ASSERT(p->bucket[0] == p_PTB->position_error_histogram.component_0);

    osif_disable_all_tasks();
    for (i=0; i< SIZE_POSERR_COMP; i += 1)
    {
        hist_poserr.entry[i].n[0] = 1U;
        hist_poserr.entry[i].n[1] = 0U;
        float32 t = p->bucket[i] * ERROR_HISTOGRAM_SCALE;
        hist_poserr.entry[i].sum[0] = (u32)t;
//      Histogram_PosErr[i].sum1 = *( &(p_PTB->position_error_histogram.component_0) + i );
        hist_poserr.entry[i].sum[1] = 0U;
    }
    STRUCT_CLOSE(HistogramPosErrNV_t, &hist_poserr);
    osif_enable_all_tasks();
    return E_OK;
}

/* \brief when user write POSITION_HISTOGRAM, this function will be invoked to check the values
    param in:
        T_FBIF_BLOCK_INSTANCE: function block pointer
        T_FBIF_WRITE_DATA: write structure
    return:
        fferr
*/
fferr_t  OnWritePositionHistogram(const T_FBIF_WRITE_DATA* p_write)
{
    fferr_t fferr = E_OK;

    switch (p_write->subindex)
    {
        case 0:
        {
            _POS_HISTOGRAM* p_pos_histogram= (_POS_HISTOGRAM*)(void*)p_write->source;

            if(0 != p_pos_histogram->total_time)
            {
                fferr=E_ERROR;
            }
            break;
        }
        case 1:
        {
            u32* p_total_time = (u32*)(void*)p_write->source;

            if(0 != *p_total_time)
            {
                fferr=E_ERROR;
            }
            break;
        }
        default:
        {
            fferr=E_ERROR;
        }
    }

    if(E_OK == fferr)
    {
        ErrorCode_t err = histogram_SetPosData(NULL);
        if(err != ERR_OK)
        {
            if(err == ERR_INVALID_PARAMETER)
            {
                fferr = E_FB_PARA_CHECK;
            }
            else
            {
                fferr = E_FB_TEMP_ERROR;
            }
        }
    }

    return fferr;
}

/* \brief when user read POSITION_HISTOGRAM, this function will be invoked to convert the values
    param in:
        T_FBIF_BLOCK_INSTANCE: function block pointer
    return:
        fferr
*/
fferr_t histogram_ReadPosition(const T_FBIF_BLOCK_INSTANCE* p_block_instance)
{
    T_FBIF_PTB* p_PTB = p_block_instance->p_block_desc->p_block;

    u32 sum = 0;

    osif_disable_all_tasks();
    for(u16 i=0; i<NUM_OF_POSITION_HISTOGRAM_ITEM; i++)
    {
        sum += hist_pos.array[i];
    }

    //float p_pos_histogram_item_start = (void *)&(p_PTB->position_histogram.component_1);
    struct buckets_t
    {
        u32 total_time;
        float32 bucket[NUM_OF_POSITION_HISTOGRAM_ITEM];
    } *p_external = (void *)&(p_PTB->position_histogram);

    p_external->total_time = hist_pos.TotalTime;

    if(0 != sum)
    {
        for(u16 i=0; i<NUM_OF_POSITION_HISTOGRAM_ITEM; i++)
        {
            p_external->bucket[i] = (float32)hist_pos.array[i] / sum;
        }
    }
    else
    {
        for(u16 i=0; i<NUM_OF_POSITION_HISTOGRAM_ITEM; i++)
        {
            p_external->bucket[i] = 0.0f;
        }
    }
    osif_enable_all_tasks();
    return E_OK;
}




