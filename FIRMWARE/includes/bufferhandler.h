/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file bufferhandler.h
    \brief  the functions needed to control the data buffer used by
            diagnostics and data logging.

            Endianness change and task (thread) safety is controlled by
            switches in config.h

    CPU: Any, with 8-bit bytes

    OWNER: AK

    \ingroup Bufferhandler
*/

#ifndef BUFFERHANDLER_H_
#define BUFFERHANDLER_H_

#include "bufferdefs.h"
#include "errcodes.h" //ErrorCode_t values
#include <taskids.h>


//Functions
extern diag_t *buffer_GetXDiagnosticBuffer(u8_least bufnum);
extern void buffer_InitializeXDiagnosticBuffer(u8_least bufnum);
extern bool_t buffer_AddXDiagnosticData1(u8_least bufnum, diag_t data);
extern bool_t buffer_AddXDiagnosticData2(u8_least bufnum, diag_t data1, diag_t data2);
extern bool_t buffer_AddXDiagnosticDataFloat(u8_least bufnum, float32 fData);
extern bufindex_t buffer_GetDataFromXDiagnosticBuffer(u8_least bufnum, bufindex_t count, diag_t* dst);
extern bufindex_t buffer_GetEntriesInXDiagnosticBuffer(u8_least bufnum);
extern void buffer_SelectRange(u8_least bufnum, bufindex_t *startpos, bufindex_t *endpos);

//Backward compatibility wrappers
MN_INLINE const s16* buffer_GetDiagnosticBuffer(void)
{
    return buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);
}
MN_INLINE void buffer_InitializeDiagnosticBuffer(void)
{
    buffer_InitializeXDiagnosticBuffer(DIAGBUF_DEFAULT);
}
MN_INLINE bool_t buffer_AddDiagnosticData1(diag_t n2Data)
{
    return buffer_AddXDiagnosticData1(DIAGBUF_DEFAULT, n2Data);
}
MN_INLINE bool_t buffer_AddDiagnosticData2(diag_t n2Data1, diag_t Data2)
{
    return buffer_AddXDiagnosticData2(DIAGBUF_DEFAULT, n2Data1, Data2);
}
MN_INLINE bool_t buffer_AddDiagnosticDataFloat(float32 fData)
{
    return buffer_AddXDiagnosticDataFloat(DIAGBUF_DEFAULT, fData);
}
MN_INLINE bufindex_t buffer_GetDataFromDiagnosticBuffer(bufindex_t NumberOfSamples, diag_t* Buffer)
{
    return buffer_GetDataFromXDiagnosticBuffer(DIAGBUF_DEFAULT, NumberOfSamples, Buffer);
}
MN_INLINE bufindex_t buffer_GetEntriesInDiagnosticBuffer(void)
{
    return buffer_GetEntriesInXDiagnosticBuffer(DIAGBUF_DEFAULT);
}

//--------------- Automatic sampling support ----------------
typedef struct SamplerInfo_t
{
    void (*fill_func)(diag_t data[2]);
    void *baseptr;
    taskid_t context; //!< sampling context
    u8 init_points;
    u16 prune_scale;
    u16 num_points;
    u16 max_points;
    u16 skip; //!< number of runs before sampling (1=every run); 0 means no sampling
    u16 prune_index;
    u16 CheckWord;
} SamplerInfo_t;

// Data sampler feature may or may not be employed by a particular project
MN_DECLARE_API_FUNC(buffer_StartSampling, buffer_StopSampling, buffer_SampleData,buffer_SampleAllData,buffer_GetSamplerInfo)
extern const SamplerInfo_t *buffer_GetSamplerInfo(u8_least bufnum);
extern ErrorCode_t buffer_StartSampling(u8_least bufnum,
                          taskid_t context,
                          void (*fill_func)(diag_t data[2]),
                          u16 max_points,
                          u8 init_points,
                          const dsample_t init_stuff[]);
extern ErrorCode_t buffer_StartSamplingExt(u8_least bufnum,
                          taskid_t context,
                          void (*fill_func)(diag_t data[2]),
                          u16 max_points,
                          u8 init_points,
                          const dsample_t init_stuff[],
                          u16 InitialPruneScale);
extern void buffer_StopSampling(u8_least bufnum);
extern void buffer_SampleData(u8_least bufnum);
extern void buffer_SampleAllData(void);

MN_DECLARE_API_FUNC(buffer_SuspendSampling, buffer_ResumeSampling)
extern void buffer_SuspendSampling(u8_least bufnum);
extern void buffer_ResumeSampling(u8_least bufnum);

MN_DECLARE_API_FUNC(buffer_AddXDiagnosticDataCircular, buffer_KeepAtMost)
extern void buffer_AddXDiagnosticDataCircular(u8_least bufnum, diag_t data);

//lint -sem(buffer_KeepAtMost, @n<=2n)
extern bufindex_t buffer_KeepAtMost(u8_least bufnum, bufindex_t num);



#endif //BUFFERHANDLER_H_
/* This line marks the end of the source */
