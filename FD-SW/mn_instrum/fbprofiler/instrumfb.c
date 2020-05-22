/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file instrumfb.c
    \brief Profiler wrapper of FB execution

    CPU: Any

    OWNER: AK
*/
#include "instrumfb.h"
#include <osif.h>

USIGN16 mnbprof_times[NELEM(instrumfb_mini_block_descr)];

/** \brief A shim between Softing FB Shell and block's Execute function to capture time length.
To be reachable, the instrumentation requires companion post-processing of
fbif_dsc.c into instrumfb_fbif_dsc.c and instrumfb_fbif_dsc_mini.c which together
replace the original in the build.
\param p_block_instance - a pointer to block instance
\return "next block to execute"
*/
USIGN16 mnbprof_execute_fb(T_FBIF_BLOCK_INSTANCE *p_block_instance)
{
    USIGN16 ret = 0;
    u32 capture = osif_get_time_in_ms();
    const T_FBIF_BLOCK_DESCR *p_block_desc = p_block_instance->p_block_desc;
    USIGN16 block_id = p_block_desc->block_id;
    if((block_id < NELEM(instrumfb_mini_block_descr)) && (instrumfb_mini_block_descr[block_id] != NULL))
    {
        ret = instrumfb_mini_block_descr[block_id](p_block_instance);
        capture = osif_get_ms_since(capture);
        if(mnbprof_times[block_id] < capture)
        {
            mnbprof_times[block_id] = (USIGN16)capture;
        }
    }
    return ret;
}

/* This line marks the end of the source */
