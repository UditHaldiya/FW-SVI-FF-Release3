/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file instrumfb.h
    \brief Profiler wrapper interfaces of FB execution

    CPU: Any

    OWNER: AK
*/
#ifndef INSTRUMFB_H_
#define INSTRUMFB_H_

#include <base.h>
#include <fbif.h>
#include <fbif_idx.h>
#include <keywords.h>
#include <fbif_fct.h>
#include "mn_gleaned.h"

typedef USIGN16 (*instrumfb_mini_block_descr_t) (T_FBIF_BLOCK_INSTANCE *p_block_instance);
extern const instrumfb_mini_block_descr_t instrumfb_mini_block_descr[MN_NBLOCKS];
extern USIGN16 mnbprof_times[NELEM(instrumfb_mini_block_descr)];

extern USIGN16 mnbprof_execute_fb(T_FBIF_BLOCK_INSTANCE *p_block_instance);

#endif //INSTRUMFB_H_
/* This line marks the end of the source */
