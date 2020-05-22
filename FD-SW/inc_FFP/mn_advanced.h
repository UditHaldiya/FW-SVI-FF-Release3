/*
Copyright 2013-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_advanced.h
    \brief Ext. interfaces of Advanced parameter application

    CPU: Any

    OWNER: AK
*/
#ifndef MN_ADVANCED_H_
#define MN_ADVANCED_H_
#include <base.h>
#include <fbap.h>
#include <ptb.h>
#include "mnhart2ff.h"
#include "errcodes.h"

extern fferr_t ffcheck_WriteAdvanced(T_FBIF_BLOCK_INSTANCE * p_block_instance, const T_FBIF_WRITE_DATA *p_write);
extern fferr_t ffcheck_WriteFilter(const T_FBIF_BLOCK_INSTANCE * p_block_instance, const T_FBIF_WRITE_DATA *p_write);

LINT_PURE(ffcheck_WriteBitmap)
extern bool_t ffcheck_WriteBitmap(u16_least index);

LINT_PURE(ffcheck_ReadBitmap)
extern bool_t ffcheck_ReadBitmap(const T_FBIF_BLOCK_INSTANCE * p_block_instance, u16_least index);

typedef struct AdvancedParam_t
{
    u32 advanced[elemsize(T_FBIF_PTB, advanced)/sizeof(u32)];
    u16 CheckWord;
} AdvancedParam_t;
extern const AdvancedParam_t *ffcheck_GetAdvancedParam(AdvancedParam_t *dst);
extern ErrorCode_t ffcheck_SetAdvancedParam(const AdvancedParam_t *src);
UNTYPEACC(ffcheck_SetAdvancedParam, ffcheck_GetAdvancedParam);

//Automation of diagnostic commands
extern const u8 adv_diag_lock[];
extern const u8 nelem_adv_diag_lock;

extern const u8 advanced_write_override[];
extern const u8 nelem_advanced_write_override;

extern bool_t mnadv_JamPtbParam(T_FBIF_BLOCK_INSTANCE *p_block_instance, u16_least rel_idx,
                         void *base_dst,
                         u16_least subindex_offset,
                         u16_least param_size);


#endif //MN_ADVANCED_H_
/* This line marks the end of the source */
