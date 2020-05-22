/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_failed_state.c
    \brief functions about parameter ADVANCED

    CPU: Any

    OWNER:
    $Date: 4/11/14 13:40p $
    $Revision: 1 $
    $Author: victoria huang $

*/
#include <softing_base.h>
#include <resb.h>
#include <ptb.h>

//Glue headers last
#include "mnhart2ff.h"
#include "mn_failed_state.h"

#define MODULE_ID (MOD_APPL_TRN | COMP_PAPP)

#define MN_PROPAGATE_RB_OOS        0U
#define MN_PROPAGATE_BOTH          1u
#define MN_NO_PROPAGATE            2U
#define MN_PROPAGATE_TBFS_TO_RB    3U

/* \brief check Accessory parameter when it is written, if the mode is wrong,
    return
    param in:
        p_write: pointer to write description block
    return:
        FF error
*/

fferr_t fffs_WritePropagateMode(const T_FBIF_WRITE_DATA* p_write)
{
    fferr_t fferr = E_OK;
    if(0 == p_write->subindex || 3 == p_write->subindex)
    {
        if (0 == p_write->subindex)
        {
            _FAILED_STATE *pFS = (void *)p_write->source;
            if (!(pFS->propagate_mode == MN_PROPAGATE_RB_OOS
                || pFS->propagate_mode == MN_PROPAGATE_BOTH
                || pFS->propagate_mode == MN_NO_PROPAGATE
                || pFS->propagate_mode == MN_PROPAGATE_TBFS_TO_RB))
            {
                fferr = E_FB_PARA_LIMIT;
            }
        }
        else
        {
            if (!(*(u8*)p_write->source == MN_PROPAGATE_RB_OOS
                || *(u8*)p_write->source == MN_PROPAGATE_BOTH
                || *(u8*)p_write->source == MN_NO_PROPAGATE
                || *(u8*)p_write->source == MN_PROPAGATE_TBFS_TO_RB))
            {
                fferr = E_FB_PARA_LIMIT;
            }
        }
    }
    else
    {
        fferr = E_FB_DATA_NO_WRITE;
    }
    return fferr;
}
