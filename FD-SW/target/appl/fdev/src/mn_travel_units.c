/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_travel_units.c
    \brief functions about parameter TRAVEL_UNITS

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include <ptb.h>
//Glue headers last
#include "mnhart2ff.h"
#include "mn_travel_units.h"
#include "syncpatches.h"
#include "ptbcustomsubx.h"

#define TRAVEL_RANGE_MIN    (TRAVEL_TravelRange_MIN_VALUE)
#define TRAVEL_RANGE_MAX    (TRAVEL_TravelRange_MAX_VALUE)

static fferr_t check_unit(u16_least unit)
{
    fferr_t ret = E_OK;
    switch(unit)
    {
        case UNITS_INDEX_RAD_ANGLE:
        case UNITS_INDEX_DEG_ANGLE:
        case UNITS_INDEX_CM:
        case UNITS_INDEX_MM:
        case UNITS_INDEX_INCH:
        case UNITS_INDEX_PERCENT:
            break;
        default:
            ret = E_FB_PARA_CHECK;
            break;
    }
    return ret;
}

/* \brief write travel parameter (Check only)
    \param p_block_instance: pointer to function block
    \return an FF error
*/
fferr_t WriteTravel(const T_FBIF_BLOCK_INSTANCE* p_block_instance,  const T_FBIF_WRITE_DATA* p_write)
{
    fferr_t fferr = E_OK;

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    if (p_PTB->mode_blk.target != MODE_OS
        && p_PTB->mode_blk.target != MODE_MAN)
    {
        fferr = E_FB_WRONG_MODE;
        return fferr;
    }
    switch (p_write->subindex)
    {
        case 0:
        {
            const _TRAVEL* p_travel = (const _TRAVEL*)(const void*)p_write->source;
            fferr = check_unit(p_travel->units_index);
            if((TRAVEL_RANGE_MIN > p_travel->TravelRange) || (TRAVEL_RANGE_MAX < p_travel->TravelRange))
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case PTB_SUBX_TRAVEL___TravelRange:
        {
            float32 p_range = *(float32*)(void*)p_write->source;
            if(TRAVEL_RANGE_MIN > p_range || TRAVEL_RANGE_MAX < p_range)
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case PTB_SUBX_TRAVEL___units_index:
        {
            fferr = check_unit(*(u16*)(void*)p_write->source);
            break;
        }
        default:
        {
            fferr = E_FB_PARA_CHECK;
            break;
        }
    }
    return fferr;
}

