/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_rwmemory.c
    \brief Intercepted memory manipulation commands

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include "hartfunc.h"
#include "hartcmd.h"
#include "bufutils.h"
#include "ffhartdef5.h"
#include "fram.h"

/* ------------------------------------------------------------------------ */
/* Error statistics handling ---------------------------------------------- */
/* ------------------------------------------------------------------------ */

typedef struct _T_DLL_ESTAT {
    USIGN32 fbc_hangup_cnt;    /* fieldbus controller watchdog timer expired */
    USIGN32 fcs_err_cnt;       /* FCS error */
    USIGN32 frm_err_cnt;       /* framing error, end delimiter not seen */
    USIGN32 cns_err_cnt;       /* carrier not seen */
    USIGN32 jab_err_cnt;       /* jabber timeout */
    USIGN32 nept_err_cnt;      /* receiver not empty  unexpected start delimiter */
    USIGN32 empty_err_cnt;     /* transmitter empty */
    USIGN32 fifo_err_cnt;      /* FIFO buffer error */
    USIGN32 rxov_err_cnt;      /* receiver overflow */
    USIGN32 rxlen_err_cnt;     /* receiver length */
} T_DLL_ESTAT;

#define NUM_FF_STATS (sizeof(T_DLL_ESTAT)/sizeof(USIGN32))
typedef u8 stat_rsp_t[sizeof(H_UINT4)];
CONST_ASSERT( (NUM_FF_STATS * sizeof(stat_rsp_t)) < sizeof(Rsp_ReadFFDLLstats_t) );

extern FDC_DATA_MEM T_DLL_ESTAT Dll_estat;

static T_DLL_ESTAT estat_prev;

s8_least hartcmd_ReadFFDLLstats(const u8 *src, u8 *dst)
{
    const Req_ReadFFDLLstats_t *s = (const void *)src;
    Rsp_ReadFFDLLstats_t *d = (void *)dst;
    UNUSED_OK(d->ReadRequest); //rely on framework to fill
    u8 reqtype = util_GetU8(s->ReadRequest[0]);

    /* Please note: pointers to arrays is MISRA 2 silliness.
    MISRA 3 does it better
    OTOH, explicit dimensions help Lint verify out-of-bounds conditions.
    */
    u8 (*rsp)[NUM_FF_STATS] = (void *)(((u8 *)dst) + sizeof(d->ReadRequest)); //first element
    const USIGN32 (*src_stat)[NUM_FF_STATS] = (const void *)&Dll_estat;
    USIGN32 (*dst_stat)[NUM_FF_STATS] = (void *)&estat_prev;

    for(u8_least n=0U; n<NUM_FF_STATS; n++)
    {
        USIGN32 stat = (*src_stat)[n];
        USIGN32 old_stat = (*dst_stat)[n];
        if(reqtype != (USIGN32)SinceReset)
        {
            (*dst_stat)[n] = stat;
            stat -= old_stat;
        }
        util_PutU32(&(*rsp)[n*sizeof(H_UINT4)], stat);
    }

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

#if 0
s8_least hartcmd_ReadFactoryValues(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}
#endif

#if 0
FUNCTION GLOBAL USIGN16 dll_fbc_get_error_stats
  (
    IN USIGN32 * u32_buff_ptr,
    IN USIGN16   n_items
  )
/*-----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION:
    Copies 'n_items' DLL error statistics values into the buffer indicated
    by 'u32_buff_ptr'. The buffer must be large enough to receive at least
    the specified number of USIGN32 elements.

PARAMETERS:
    u32_buff_ptr:       pointer to buffer which receves the statistics
    n_items:            number of items to be read

GLOBALS_AFFECTED:
    Dll_estats:         DLL error statistics will be read

RETURN_VALUES:
    (USIGN16)   number of actually transferred items

-----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES

FUNCTION_BODY

   n_items = min(n_items, sizeof(T_DLL_ESTAT)/sizeof(USIGN32));

   memcpy(u32_buff_ptr, &Dll_estat, n_items * sizeof(USIGN32));

   return (n_items);
} /* FUNCTION dll_fbc_get_error_stats */
#endif //0

/* This line marks the end of the source */
