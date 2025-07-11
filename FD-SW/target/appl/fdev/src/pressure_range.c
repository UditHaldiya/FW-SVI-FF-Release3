/*
Copyright 2009-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pressure_range.c
    \brief functions about parameter PRESSURE_RANGE

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include <ptb.h>

#define MODULE_ID (MOD_APPL_TRN | COMP_PAPP)

//MN FIRMWARE headers second
#include "hartdef.h"
#include "bufutils.h"
#include "crc.h"

//Glue headers last
#include "mnhart2ff.h"
#include "pressure_range.h"
#include "pressuredef.h"
#include "hmsndrcv5.h"
#include "mn_supply_pressure_alert.h"

static fferr_t ffpres_FixUpUnits(u8 hart_unit);

static fferr_t WritePressureRangeCheck
(
    const T_FBIF_PTB *p_PTB, const T_FBIF_WRITE_DATA* p_write, u8 *phart_code
);

/* \brief read pressure unit. Only needs to check that the units code is good
    \param p_block_instance - pointer to function block
    \param snd_buf - send buffer
    \param rcv_buf - receive buffer
    \return FF error
*/
fferr_t ReadPressureRange(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    UNUSED_OK(snd_buf);
    UNUSED_OK(rcv_buf); //was using hart cmd 170,176
    fferr_t fferr;

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    u16 units = p_PTB->pressure_range.units;

    p_PTB->pressure_range.eu_0 = ffpres_Internal2Eng(PRESSURE_MIN, units);
    p_PTB->pressure_range.eu_100 = ffpres_Internal2Eng(PSI_PRESSURE_MAX, units);
    fferr = E_OK;

    return fferr;
}

/* \brief write pressure unit
    param in:
        p_block_instance: pointer to function block
        snd_buf:  send buffer
        rcv_buf:  receive buffer
    return:
        FF error
*/
fferr_t ffpres_WritePressureRange(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write,
                                  void* snd_buf, void* rcv_buf)
{
    //hart cmd 171,176
    u8 hart_code;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    fferr_t fferr = WritePressureRangeCheck(p_PTB, p_write, &hart_code);
    if(fferr == E_OK)
    {
        //Then hart_code is valid
        Req_WritePressureUnits_t *req = snd_buf;
        util_PutU8(req->PressureUnits[0], hart_code);
        fferr = hmsndrcv5_WritePressureUnits(req, rcv_buf);

    }
    if(fferr == E_OK)
    {
        //Now we can update the TB parameter
        fferr = ffpres_FixUpUnits(hart_code);
    }
    return fferr;
}


static const PresAlertConf_t PresAlertConf_Defaults[PresAlerts_Count] =
{
    [PresAlertHi] =
    {
        .alert_point = 150.0F,
        .deadband = 0.5F, //0.0725189F,
        .historic_alert = FALSE,
        .enable = FALSE,
        .CheckWord = 0, //Dont't care
    },
    [PresAlertLo] =
    {
        .alert_point = 2.9F,
        .deadband = 0.5F, //0.0725189F,
        .historic_alert = FALSE,
        .enable = FALSE,
        .CheckWord = 0, //Dont't care
    },
    [PresAlertLoLo] =
    {
        .alert_point = 2.9F,
        .deadband = 0.5F, //0.0725189F,
        .historic_alert = FALSE,
        .enable = FALSE,
        .CheckWord = 0, //Dont't care
    },
};
static PresAlertConf_t PresAlertConf[PresAlerts_Count];

ErrorCode_t ffpres_SetAlertConf(u8_least index, const PresAlertConf_t *src)
{
    if(index >= NELEM(PresAlertConf))
    {
        return ERR_NOT_SUPPORTED;
    }
    if(src == NULL)
    {
        src = &PresAlertConf_Defaults[index];
    }
    ErrorCode_t err;
    //Working in internal units!!! They happen to be psi.
    if((src->alert_point > PSI_PRESSURE_MAX) || (src->alert_point < PRESSURE_MIN)
       || (src->deadband > PSI_PRESSURE_DEADBAND_MAX) || (src->deadband < PRESSURE_MIN))
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        STRUCT_GET(src, &PresAlertConf[index]);
        err = ram2nvramAtomic(NVRAMID_PresAlertConf+index);
    }
    return err;
}

const PresAlertConf_t *ffpres_GetAlertConf(u8_least index, PresAlertConf_t *dst)
{
    if(index >= NELEM(PresAlertConf))
    {
        return NULL;
    }
    return STRUCT_TESTGET(&PresAlertConf[index], dst);
}

enum
{
    psi_internal,
    kpa_internal,
    bar_internal
};

typedef struct pres_UnitsMap_t
{
    u8 hart_code;
    u16 ff_code;
    float32 scale;
    float32 eu_0;
} pres_UnitsMap_t;

const pres_UnitsMap_t pres_UnitsMap[] =
{
    [psi_internal] =
    {
        .hart_code = H_PSI,
        .ff_code = FF_UNITS_PSI,
        .scale = 1.0F,
        .eu_0 = (float32)UNITS_PSI_A,
    },
    [kpa_internal] =
    {
        .hart_code = H_KPA,
        .ff_code = FF_UNITS_KPA,
        .scale = (float32)PRESSURE_FACTOR_PSI2KPA,
        .eu_0 = (float32)UNITS_KPA_A,
    },
    [bar_internal] =
    {
        .hart_code = H_BAR,
        .ff_code = FF_UNITS_BAR,
        .scale = (float32)PRESSURE_FACTOR_PSI2BAR,
        .eu_0 = (float32)UNITS_BAR_A,
    },
};

const u8 pres_UnitsMap_size = NELEM(pres_UnitsMap);

u8_least ffpres_FFCode2Index(u16 ff_code)
{
    u8_least index = 0;
    for(; index < NELEM(pres_UnitsMap); index++)
    {
        if(pres_UnitsMap[index].ff_code == ff_code)
        {
            break;
        }
    }
    return index;
}

/** \brief Converts FF pressure units code to HART units code
\param ff_code - FF units code
\return HART units code or 0 on error (invalid input)
*/
u8 ffpres_FFUnits2HartUnits(u16 ff_code)
{
    u8 hart_code = 0;
    for(u8_least index = 0; index < NELEM(pres_UnitsMap); index++)
    {
        if(pres_UnitsMap[index].ff_code == ff_code)
        {
            hart_code = pres_UnitsMap[index].hart_code;
            break;
        }
    }
    return hart_code;
}

/** \brief Converts HART pressure units codeto FF units code
\param ff_code - FF units code
\return HART units code or 0 on error (invalid input)
*/
u16 ffpres_HartUnits2FFUnits(u8 hart_code)
{
    u16 ff_code = 0;
    for(u8_least index = 0; index < NELEM(pres_UnitsMap); index++)
    {
        if(pres_UnitsMap[index].hart_code == hart_code)
        {
            ff_code = pres_UnitsMap[index].ff_code;
            break;
        }
    }
    return ff_code;
}


/** \brief Fixes up PTB's pressure_range parameter
\param p_block_instance - pointer to PTB instance
\param unit - hart unit code
\param test - if true, only test, don't change anything
\return E_OK on success or E_ERROR on invalid units
*/
static fferr_t ffpres_FixUpUnits(u8 hart_unit)
{
    //T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    u8_least index;
    //u16 ff_units = 0;
    for(index = 0; index < NELEM(pres_UnitsMap); index++)
    {
        if(pres_UnitsMap[index].hart_code == hart_unit)
        {
            //ff_units = pres_UnitsMap[index].ff_code;
            break;
        }
    }

    fferr_t ret;

    if(index < NELEM(pres_UnitsMap))
    {
        //Units found!
        //Let Softing framework write it and increment ST_REV
        ret = E_OK;
    }
    else
    {
        ret = E_FB_PARA_LIMIT;
    }

    return ret;
}

float32 ffpres_Internal2Eng(float32 val, u16 ff_code)
{
    u8_least index;
    for(index = 0; index < NELEM(pres_UnitsMap); index++)
    {
        if(pres_UnitsMap[index].ff_code == ff_code)
        {
            break;
        }
    }
    if(index < NELEM(pres_UnitsMap))
    {
        val = (val - pres_UnitsMap[psi_internal].eu_0)*pres_UnitsMap[index].scale + pres_UnitsMap[index].eu_0;
    }
    else
    {
        val = 0.0F; //Or NaN? Unexpected anyway
    }
    return val;
}

float32 ffpres_Eng2Internal(float32 val, u16 ff_code)
{
    u8_least index;
    for(index = 0; index < NELEM(pres_UnitsMap); index++)
    {
        if(pres_UnitsMap[index].ff_code == ff_code)
        {
            break;
        }
    }
    if(index < NELEM(pres_UnitsMap))
    {
        val = (val - pres_UnitsMap[index].eu_0)/pres_UnitsMap[index].scale + pres_UnitsMap[psi_internal].eu_0; //simple for now, without caring of abstract offsets etc
    }
    else
    {
        val = 0.0F; //Or NaN? Unexpected anyway
    }
    return val;
}


/* \brief check pressure unit parameter when it is written, and store the
    previous pressure at static virable sLastPressureUnit
    param in:
        p_write: pointer to write description block
    return:
        FF error
*/

static fferr_t WritePressureRangeCheck
(
    const T_FBIF_PTB *p_PTB, const T_FBIF_WRITE_DATA* p_write, u8 *phart_code
)
{
    fferr_t fferr = E_OK;
    u16 uCurUnit = p_PTB->pressure_range.units;;

    switch (p_write->subindex)
    {
        case 0:
        {
            SCALE* p_pressure_range = (void*)p_write->source;
            uCurUnit = p_pressure_range->units;
            if(p_pressure_range->dec_pt != PRESSURE_RANGE_DECIMAL)
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        case 3:
        {
            u16* p_units_index = (void*)p_write->source;
            uCurUnit = *p_units_index;
            break;
        }
        case 4:
        {
            if(PRESSURE_RANGE_DECIMAL != p_write->source[0])
            {
                fferr = E_FB_PARA_CHECK;
            }
            break;
        }
        default:
        {
            fferr = E_FB_NO_SUBIDX_ACCESS;
        }
    }

    u8 hart_code;
    if(fferr == E_OK)
    {
        hart_code = ffpres_FFUnits2HartUnits(uCurUnit);
        if(hart_code == 0)
        {
            fferr = E_FB_PARA_CHECK;
        }
    }
    else
    {
        hart_code = 0;
    }
    *phart_code = hart_code;
    return fferr;
}

/* This line marks the end of the source */
