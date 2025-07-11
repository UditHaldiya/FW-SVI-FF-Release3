/*
Copyright 2020 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_tempr.c
    \brief Handling of temperature (extremes) interface

    CPU: Any

    OWNER: AK
*/


#include "hmsndrcv5.h"
#include <ptb.h>

//MN FIRMWARE headers second
#include "bufutils.h"

//Glue headers last
#include "ptbcustomsubx.h"
#include "mn_tempr.h"


fferr_t fftempr_ReadTemprExtremes(T_FBIF_BLOCK_INSTANCE *p_block_instance, T_FBIF_READ_DATA *p_read, void *from, void *to)
{
    UNUSED_OK(p_read);
    Req_ReadTemperatures_t *req = from;
    Rsp_ReadTemperatures_t *rsp = to;
    fferr_t fferr = hmsndrcv5_ReadTemperatures(req, rsp);
    if(fferr == E_OK)
    {
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        const Temperatures_t *t = to; //same start as rsp
        p_PTB->temperature_extremes.tempr_max_lifetime = util_GetFloat(t->MaxTemperature[0]);
        p_PTB->temperature_extremes.tempr_min_lifetime = util_GetFloat(t->MinTemperature[0]);
        //NOTE: Current min/max are computed on IPC receipt of temperature
    }
    return fferr;
} //lint !e818 const-ness may be confusing to reader since the pointed-to object is modified indirectly


/** \brief Writes Temperature Extremes except lifetime min/max
NOTE: apprently, p_write->source is filled in correct order but without alignment padding
*/
fferr_t fftempr_WriteTemprExtremes
(
    T_FBIF_BLOCK_INSTANCE *p_block_instance,
    const T_FBIF_WRITE_DATA *p_write,
    void *from,
    void *to
)
{
    UNUSED_OK(from);
    UNUSED_OK(to);

    fferr_t fferr = E_OK;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    switch(p_write->subindex)
    {
        case 0: //everything)
        {
            //extract only non-lifetime subparameters
            const _TEMPERATURE_EXTREMES *t = (const void *)p_write->source;
            p_PTB->temperature_extremes.temperature_max = t->temperature_max;
            p_PTB->temperature_extremes.temperature_min = t->temperature_min;
            break;
        }
        case PTB_SUBX_TEMPERATURE_EXTREMES___tempr_max_lifetime:
        case PTB_SUBX_TEMPERATURE_EXTREMES___tempr_min_lifetime:
        {
            fferr = E_FB_DATA_NO_WRITE;
            break;
        }
        case PTB_SUBX_TEMPERATURE_EXTREMES___temperature_max:
        {
            p_PTB->temperature_extremes.temperature_max = mn_pull_float(p_write->source);
            break;
        }
        case PTB_SUBX_TEMPERATURE_EXTREMES___temperature_min:
        {
            p_PTB->temperature_extremes.temperature_min = mn_pull_float(p_write->source);
            break;
        }
        default:
            fferr = E_FB_PARA_CHECK;
            break;
    }
    return fferr;
} //lint !e818 const-ness may be confusing to reader since the pointed-to object is modified indirectly

/* This line marks the end of the source */
