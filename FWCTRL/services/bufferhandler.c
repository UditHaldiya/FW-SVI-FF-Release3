/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup Bufferhandler Buffers handler module
\brief API and implementation of data buffer management for sampling and diagnostics
\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_BufferHandler Module.doc"> Design document </a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/BUFFERhandler1HTML.html"> Unit Test Report [1]</a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/bufferhandler2HTML.html"> Unit Test Report [2]</a><br>
\endhtmlonly
*/
/**
    \file bufferhandler.c
    \brief  the functions needed to control the data buffer used by
            diagnostics and data logging.

    Implements a circular/linear buffer which can be read continuously.

            Endianness change and task (thread) safety is controlled by
            switches in config.h

    OWNER: AK

    \ingroup Bufferhandler
*/

#include "config.h" //for compile-time switches
#include "mnwrap.h"
#include "numutils.h"
#include "bufferhandler.h"
#include "nvdimensions.h"
#include "crc.h"
#include "oswrap.h" //not needed for forward port to trunk

#if DIAG_STORE_THREAD_SAFE == OPTION_ON
#   define STORE_ENTER_CRITICAL() MN_ENTER_CRITICAL()
#   define STORE_EXIT_CRITICAL() MN_EXIT_CRITICAL()
#endif
#if DIAG_STORE_THREAD_SAFE == OPTION_OFF
#   define STORE_ENTER_CRITICAL()
#   define STORE_EXIT_CRITICAL()
#endif
//No #else : other values should cause compilation error

#define PRE_STORE16(a) (a)
//No #else : other values should cause compilation error


//Defines
#define DIAG_OVFL_SIGNATURE ((diag_t)0x8000)

typedef struct diagbuf_t
{
    SamplerInfo_t SamplerInfo;
    volatile bufindex_t startpos, endpos;
} diagbuf_t;

EXTMEM static diag_t diagbuf0[DIAGNOSTIC_BUFFER_SIZE];
#if NUM_DIAG_BUFFERS > 1U
EXTMEM static diag_t diagbuf1[DIAGNOSTIC_BUFFER_SIZE_AUX];
#endif
static const struct
{
    diag_t *buf;
    size_t lognelem;
} m_DiagnosticBuffer[NUM_DIAG_BUFFERS] =
{
    [DIAGBUF_DEFAULT] =
    {
        .buf = diagbuf0,
        .lognelem = DIAG_BUFFER_LOGSIZE,
    },
#if NUM_DIAG_BUFFERS > 1U
    [DIAGBUF_AUX] =
    {
        .buf = diagbuf1,
        .lognelem = DIAG_BUFFER_LOGSIZE_AUX,
    },
#endif
};

static MN_NO_INIT struct db_t
{
    diagbuf_t buf[NUM_DIAG_BUFFERS];
} db;

CONST_ASSERT(alignof(u32) <= alignof(struct db_t));

#define DIAG_BUFFER_NELEM(bufnum) (1U<<m_DiagnosticBuffer[bufnum].lognelem)
#define DIAG_BUFFER_INDEX_MASK(bufnum) (DIAG_BUFFER_NELEM(bufnum) - 1U)

static bufindex_fast_t SizeLeft(u8_least bufnum, bufindex_fast_t end)
{
    bufindex_fast_t szleft = db.buf[bufnum].startpos;
    szleft -= end;
    szleft--;

    szleft &= DIAG_BUFFER_INDEX_MASK(bufnum);
    return szleft;
}

static bufindex_t Entries(u8_least bufnum, bufindex_fast_t end)
{
    bufindex_fast_t e = end;
    e -= (bufindex_fast_t)db.buf[bufnum].startpos;
    e &= DIAG_BUFFER_INDEX_MASK(bufnum);
    return (bufindex_t)e;
}

static bufindex_fast_t IncrementCounter(u8_least bufnum, bufindex_fast_t n)
{
    bufindex_fast_t nn = n;
    nn++;
    nn &= DIAG_BUFFER_INDEX_MASK(bufnum);
    return nn;
}

static bufindex_fast_t DecrementCounter(u8_least bufnum, bufindex_fast_t n)
{
    bufindex_fast_t nn = n;
    nn--;
    nn &= DIAG_BUFFER_INDEX_MASK(bufnum);
    return nn;
}

/**
\brief The routine returns a pointer to a diagnostic buffer
\return pointer to a diagnostic buffer
*/
diag_t *buffer_GetXDiagnosticBuffer(u8_least bufnum)
{
    if(bufnum>=NUM_DIAG_BUFFERS)
    {
        return NULL;
    }
    return m_DiagnosticBuffer[bufnum].buf;
}

static void dummy_sampler(diag_t data[2])
{
    UNUSED_OK(data);
}


/**
\brief resets the diagnostic buffer to empty condition

Notes:
This function should be called before a diagnostic test and should be called
at startup.
Only the hart task should get data from the buffer (which manipulates
the start pointer) and only the process task should put data into the buffer
(which manipulates the end pointer).
The places in the code that uses both must be made thread safe.
*/
void buffer_InitializeXDiagnosticBuffer(u8_least bufnum)
{
    if(bufnum>=NUM_DIAG_BUFFERS)
    {
        return;
    }
    const SamplerInfo_t init_sampler =
    {
        .fill_func = dummy_sampler,
        .baseptr = m_DiagnosticBuffer[bufnum].buf,
        .init_points = 0,
        .prune_scale = 1,
        .context = TASKID_PROCESS, //TBD if matters
        .num_points = 0,
        .max_points = 2,
        .skip = 0,
        .prune_index = 2,
        .CheckWord = 0, //don't care

    };
    //THIS CODE MUST BE DONE AS A CRITICAL SECTION (e.g. disable interrupts)
    MN_ENTER_CRITICAL();
        db.buf[bufnum].startpos = 0U;
        db.buf[bufnum].endpos = 0U;
    MN_EXIT_CRITICAL();
    Struct_Copy(SamplerInfo_t, &db.buf[bufnum].SamplerInfo, &init_sampler);

}

/** \brief A helper for buffer_SelectRange() to swap values
\param pold - a pointer to the old value
\param pnew - a pointer to the new value
*/
static void bufswap(volatile bufindex_t *pold, bufindex_t *pnew)
{
    if(pnew != NULL)
    {
        bufindex_t newv = *pnew;
        *pnew = *pold;
#if DIAGNOSTIC_BUFFER_SIZE < 65536
        if(newv < DIAGNOSTIC_BUFFER_SIZE)
#endif
        {
            *pold = newv;
        }
    }
}

/** \brief Forces adjustment of diagnostic buffer content limits.

This has two uses, both related to reads in circular mode:
1. When we want to select a known subset of data in circular mode
2. When we want to let the buffer know what we filled in linear mode
\param bufnum - buffer id
\param[in][out] startpos - a pointer to [in]new [out]old start position
\param[in][out] endpos - a pointer to [in]new [out]old end position.
NULL pointer would leave the position unchanged.
Out-of-range value will not be set but the old value will be filled
*/
void buffer_SelectRange(u8_least bufnum, bufindex_t *startpos, bufindex_t *endpos)
{
    if(bufnum < NUM_DIAG_BUFFERS)
    {
        MN_ENTER_CRITICAL();
            bufswap(&db.buf[bufnum].startpos, startpos);
            bufswap(&db.buf[bufnum].endpos, endpos);
        MN_EXIT_CRITICAL();
    }
}

/**
\brief stuffs the buffer with one or two fields
\param bufnum - a buffer to stuff the data into
\param items - must be 1 or 2
\param item1 - first item to stuff
\param item2 - second item to stuff
\return error indicator (true iff overflow)
*/
static bool_t buff_stuff(u8_least bufnum, u8_least items, diag_t item1, diag_t item2)
{
    bool_t ret;
    bufindex_fast_t pos;

    if(bufnum >= NUM_DIAG_BUFFERS)
    {
        return false; //OK to stuff data into abyss
    }

    STORE_ENTER_CRITICAL();
        pos = db.buf[bufnum].endpos;
        if(SizeLeft(bufnum, pos) < items)
        {
            //not enough room
            pos = DecrementCounter(bufnum, pos);
            m_DiagnosticBuffer[bufnum].buf[pos] = DIAG_OVFL_SIGNATURE;
            //items = 0;
            ret = true;
        }
        else
        {
            //stuff the items
            m_DiagnosticBuffer[bufnum].buf[pos] = PRE_STORE16(item1);
            pos = IncrementCounter(bufnum, pos);
            if(items > 1u)
            {
                m_DiagnosticBuffer[bufnum].buf[pos] = PRE_STORE16(item2);
                pos = IncrementCounter(bufnum, pos);
            }
            db.buf[bufnum].endpos = (bufindex_t)pos;
            ret = false;
        }
    STORE_EXIT_CRITICAL();
    return ret; //items;
}

/** \brief A helper to collect data in a round buffer while
discarding the oldest entry if needed to prevent overflow
\param bufnum - buffer to stuff into
\param data - data to stuff
*/
void buffer_AddXDiagnosticDataCircular(u8_least bufnum, diag_t data)
{
    STORE_ENTER_CRITICAL();
        bufindex_fast_t pos = db.buf[bufnum].endpos;
        m_DiagnosticBuffer[bufnum].buf[pos] = PRE_STORE16(data);
        pos = IncrementCounter(bufnum, pos);
        db.buf[bufnum].endpos = (bufindex_t)pos;
        if(pos == db.buf[bufnum].startpos)
        {
            //Overflow; silently discard the oldest
            db.buf[bufnum].startpos = (bufindex_t)IncrementCounter(bufnum, db.buf[bufnum].startpos);
        }
    STORE_EXIT_CRITICAL();
}

/** \brief In circular mode, discards any entries in excess of `num'
\param bufnum - buffer id
\param num - excess threshold
\return number of entries actually kept
*/
bufindex_t buffer_KeepAtMost(u8_least bufnum, bufindex_t num)
{
    bufindex_t num_stored = buffer_GetEntriesInXDiagnosticBuffer(bufnum);
    if(num_stored > num)
    {
        bufindex_t nn = db.buf[bufnum].startpos + (num_stored - num);
        nn &= DIAG_BUFFER_INDEX_MASK(bufnum);
        db.buf[bufnum].startpos = nn;
    }
    else
    {
        num = num_stored;
    }
    return num;
}

/**
\brief puts one word into the diagnostic data buffer

Note:
The places in the
code that uses Add/Read must be made thread safe.

\param bufnum - buffer to stuff into
\param data to stuff
\return FALSE if no error, TRUE if error
*/
bool_t buffer_AddXDiagnosticData1(u8_least bufnum, diag_t data)
{
    return buff_stuff(bufnum, 1u, data, (diag_t)0);
}
/**
\brief puts two words into the diagnostic data buffer

Notes:
Only the hart task should get data from the buffer (which manipulates the
start pointer) and only the process task should put data into the buffer
(which manipulates the end pointer).  The places in the code
that uses both must be made thread safe.
\param bufnum - buffer to stuff into
\param data1 to stuff
\param data2 to stuff
\return FALSE if no error, TRUE if error
*/
bool_t buffer_AddXDiagnosticData2(u8_least bufnum, diag_t data1, diag_t data2)
{
    return buff_stuff(bufnum, 2u, data1, data2);
}

/**
\brief puts a floating point value into the diagnostic data buffer

Notes:
Only the hart task should get data from the buffer (which manipulates
the start pointer) and only the process task should put data into the
buffer (which manipulates the end pointer).  The places in
the code that uses both must be made thread safe.

\param bufnum - buffer to sample into
\param fData - a 4-byte floating-point number to sample
\return bError = false if no error, true if error
*/
bool_t buffer_AddXDiagnosticDataFloat(u8_least bufnum, float32 fData)
{
    diag_t data1, data2;
    u32 uData = (u32)float2ieee(fData);
    data1 = (diag_t)uData; //lower halfword
    uData >>= 16; //upper halfword
    data2 = (diag_t)uData;
    return buff_stuff(bufnum, 2u, data1, data2);
}

/**
\brief fills data from the circular buffer

Notes:
Only the hart task should get data from the buffer (which manipulates
the start pointer) and only the process task should put data into
the buffer (which manipulates the end pointer).
  The places in the code that uses both must be made thread safe.

This function is reentrant all right but if preempted by itself will
skip the values filled into another buffer (with at most one entry
getting into both buffers in the beginning and the end.
If there is ever a need to fail on second entry, write a small
wrapper to check if the routine is already running (by checking
a static volatile flag).

\param bufnum - buffer to sample into
\param count - the number of diag_t points to get
\param[out] dst - the recipent of the data array
\return the number of entries filled
*/
bufindex_t buffer_GetDataFromXDiagnosticBuffer(u8_least bufnum, bufindex_t count, diag_t* dst)
{
    bufindex_t n = 0; //count the number of entries actually filled
    if((dst == NULL) || (bufnum >= NUM_DIAG_BUFFERS))
    {
        return 0; /* legitimate early return: pre-requisite check */
    }
    if(db.buf[bufnum].SamplerInfo.skip != 0)
    {
        //The buffer is sampling in linear self-pruning mode: can't give up data
        return 0; /* legitimate early return: pre-requisite check */
    }
    while(n < count)
    {
        bufindex_t pos = db.buf[bufnum].startpos;
        if(pos == db.buf[bufnum].endpos)
        {
            break; //buffer empty
        }
        else
        {
            *dst++ = m_DiagnosticBuffer[bufnum].buf[pos];
            db.buf[bufnum].startpos = (bufindex_t)IncrementCounter(bufnum, pos);
            n++;
        }
    }
    return n;
}
/**
\brief returns the current number of entries in the diagnostic buffer
\param bufnum - buffer to sample into
\return the current number of entries in the diagnostic buffer
*/
bufindex_t buffer_GetEntriesInXDiagnosticBuffer(u8_least bufnum)
{
    if(bufnum >= NUM_DIAG_BUFFERS)
    {
        return 0;
    }
    bufindex_fast_t end = db.buf[bufnum].endpos;
    return Entries(bufnum, end);
}

/** \brief Amortized pruning: X[i] <= X[2*i] recursively from the end.
Has worst-case logarithmic complexity. Implementation should be optimized for time.
\param p - base pointer
\param point - index of place (pointed to by p) which must be relinquished
*/
static void buffer_PrunePoint32(SamplerInfo_t *SamplerInfo, bufindex_t point)
{
    bufindex_t npoint = point+2U;
    storeMemberInt(SamplerInfo, prune_index, npoint); //prepare next point
    u32 *p = SamplerInfo->baseptr;
    bufindex_t prev_point;
    u32 val = p[point];
    while(/*(point != 0) &&*/ ((point & 1U) == 0)) //i.e. while the index is even
    {
        prev_point = point/2U;
        u32 prev_val = p[prev_point];
        p[prev_point] = val;
        val = prev_val;
        point = prev_point;
    }
}

//--------------- Automatic sampling --------------------------
void buffer_StopSampling(u8_least bufnum)
{
    if(bufnum >= NUM_DIAG_BUFFERS)
    {
        return; //OK to stop non-existent sampling
    }
    SamplerInfo_t *SamplerInfo = &db.buf[bufnum].SamplerInfo;
    MN_ENTER_CRITICAL();
        storeMemberInt(SamplerInfo, skip, 0);
    MN_EXIT_CRITICAL();
    //Now complete any remaining pruning
    for(bufindex_t prune_index = SamplerInfo->prune_index; prune_index < SamplerInfo->max_points; prune_index+=2)
    {
        buffer_PrunePoint32(SamplerInfo, prune_index);
    }
    Struct_Test(SamplerInfo_t, SamplerInfo);
    //Allow circular buffer interface to read the buffer
    db.buf[bufnum].endpos = (bufindex_t)(2U*(SamplerInfo->init_points+SamplerInfo->num_points)); //valid non-losing cast: we already checked pre-requisites
}

/** \brief Reports the state of the data sampler
\param bufnum - buffer to sample into
\return a pointer to const sampler info
*/
const SamplerInfo_t *buffer_GetSamplerInfo(u8_least bufnum)
{
    if(bufnum >= NUM_DIAG_BUFFERS)
    {
        return NULL;
    }
    //do not test SamplerInfo: it is tested once in the end at StopSampling
    return &db.buf[bufnum].SamplerInfo;
}


ErrorCode_t buffer_StartSampling(u8_least bufnum,
                          taskid_t context,
                          void (*fill_func)(diag_t data[2]),
                          u16 max_points,
                          u8 init_points,
                          const dsample_t init_stuff[])
{
  //call with the default value of 1 for prune scale
  return buffer_StartSamplingExt(bufnum,
                          context,
                          fill_func,
                          max_points,
                          init_points,
                          init_stuff,
                          1u);
}

MN_DECLARE_API_FUNC(buffer_StartSamplingExt)
/** \brief Starts data sampling, always with the rate of the cycle task where dsampler_SampleData call is
\param bufnum - buffer to sample into
\param sinfo - a pointer to caller-prepared sampler configuration
\param init_stuff - the points to stuff initially (ignored if init_points=0)
*/
ErrorCode_t buffer_StartSamplingExt(u8_least bufnum,
                          taskid_t context,
                          void (*fill_func)(diag_t data[2]),
                          u16 max_points,
                          u8 init_points,
                          const dsample_t init_stuff[],
                          u16 InitialPruneScale)
{
    s8_least i;
    if(
       (bufnum >= NUM_DIAG_BUFFERS)
       || (fill_func == NULL)
       || (((bufindex_fast_t)max_points + (bufindex_fast_t)init_points) >= DIAGNOSTIC_BUFFER_SIZE)
       || ((max_points & 0x0001U) != 0) //better yet, if agreed, ((num_points & 0x0003U) != 0x0002U)
       || (max_points < 4) //e.g. 4
       )
    {
        return ERR_INVALID_PARAMETER;
    }
    //Future; need to change initialization: Struct_Test(SamplerInfo_t, &db.buf[bufnum].SamplerInfo);
    if(db.buf[bufnum].SamplerInfo.skip != 0)
    {
        return ERR_MODE_ILLEGAL_SUBMODE; //A hijack of an error code no longer used
    }
    const SamplerInfo_t sampler =
    {
        .fill_func = fill_func,
        .baseptr = &m_DiagnosticBuffer[bufnum].buf[2U*init_points],
        .init_points = init_points,
        .prune_scale = InitialPruneScale,  //LS:  changed to allow initialization other than 1u
        .context = context,
        .num_points = 0,
        .max_points = max_points,
        .skip = 1,
        .prune_index = max_points,
        .CheckWord = 0, //don't care

    };
    const SamplerInfo_t *sinfo = &sampler;
    buffer_InitializeXDiagnosticBuffer(bufnum);
    MN_ENTER_CRITICAL();
        Struct_Copy(SamplerInfo_t, &db.buf[bufnum].SamplerInfo, sinfo);

        //This has to be in a critical section so as to not be interrupted by the first sample(s)
        //If need be, this can be improved (?)
        if(init_stuff != NULL)
        {
            for(i=0; i<sinfo->init_points; i++)
            {
                (void)buffer_AddXDiagnosticData2(bufnum, init_stuff[i].data1, init_stuff[i].data2);
                //Who pre-fills the buffer with too much stuff will discover it on read; no error reporting here.
            }
        }
        else
        {
            //just reserve the space
            for(i=0; i<sinfo->init_points; i++)
            {
                (void)buffer_AddXDiagnosticData2(bufnum, 0, 0);
                //Who pre-fills the buffer with too much stuff will discover it on read; no error reporting here.
            }
        }
    MN_EXIT_CRITICAL();
    return ERR_OK;
}

/** \brief Performs periodic data sampling. Stops automatically if prune scale wraps to 0 and is used.
*/
void buffer_SampleData(u8_least bufnum)
{
    SamplerInfo_t *SamplerInfo = &db.buf[bufnum].SamplerInfo;

    u16_least skip = SamplerInfo->skip;
    if(skip == 0)
    {
        return; //we are not sampling
    }
    if(!oswrap_IsContext(SamplerInfo->context))
    {
        return; //wrong context
    }

    skip--;
    if(skip == 0)
    {
        u16 num_points = SamplerInfo->num_points;
        if(SamplerInfo->num_points == SamplerInfo->max_points)
        {
            //we need to prune and delay the samples
            num_points/=2U; //restart with pruning
            storeMemberInt(SamplerInfo, prune_scale, SamplerInfo->prune_scale * 2U);
            if((num_points & 1U)==0)
            {
                //start amortized pruning with points that need to get out of the way first
                buffer_PrunePoint32(SamplerInfo, num_points);
            }
            else
            {
                storeMemberInt(SamplerInfo, prune_index, num_points+1);
            }
        }
        //else
        {
            void *baseptr = (u32 *)(SamplerInfo->baseptr) + num_points;
            num_points += 1;
            SamplerInfo->fill_func(baseptr);
        }
        storeMemberInt(SamplerInfo, num_points, num_points);
        skip = SamplerInfo->prune_scale; //set wait period until next writable sample
    }
    else
    {
        //Do amortized pruning
        u16 prune_index = SamplerInfo->prune_index; //no reason to trace odd indices;
        if(prune_index < SamplerInfo->max_points)
        {
            buffer_PrunePoint32(SamplerInfo, prune_index);
        }
    }
    storeMemberInt(SamplerInfo, skip,  skip);
}

/** \brief A wrapper for sampling all buffers
*/
void buffer_SampleAllData(void)
{
    for(u8_least bufnum=0; bufnum<NUM_DIAG_BUFFERS; bufnum++)
    {
        buffer_SampleData(bufnum);
    }
}

/** \brief suspend/resume sampling
\param bufnum - buffer id
\param new_skip - number skips to next sample
\return old skip count
*/
static u16 buffer_HackSampling(u8_least bufnum, u16 new_skip)
{
    u16 old_skip;
    if(bufnum < NUM_DIAG_BUFFERS)
    {
        SamplerInfo_t *SamplerInfo = &db.buf[bufnum].SamplerInfo;
        MN_ENTER_CRITICAL();
            old_skip = SamplerInfo->skip; //OK to suspend non-existent sampling
            storeMemberInt(SamplerInfo, skip, new_skip);
        MN_EXIT_CRITICAL();
    }
    else
    {
        old_skip = 0; //OK to suspend non-existent sampling
    }
    return old_skip;
}

/** \brief suspend linear sampling
\param bufnum - buffer id
\return old skip count (to know where to resume)
*/
u16 buffer_SuspendSampling(u8_least bufnum)
{
    //This may be broken by reading the buffer as circular
    return buffer_HackSampling(bufnum, 0);
}

/** \brief resume linear sampling
\param bufnum - buffer id
\param skip - number skips to next sample
*/
void buffer_ResumeSampling(u8_least bufnum, u16 skip)
{
    //Make the next samle go in the buffer
    u16 old_skip = buffer_HackSampling(bufnum, skip);
    UNUSED_OK(old_skip);
}


/* This line marks the end of the source */
