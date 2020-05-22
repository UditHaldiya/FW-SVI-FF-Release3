/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup HARTapp
\brief HART application layer component

\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_Hart Module.doc"> Design document </a><br>
Unit Test Credit claim is found <a href="../../../Doc/TestDocs/UnitTests.doc"> here </a><br>
\endhtmlonly
*/
/**
    \file hart_posmon.c
    \brief Glue functions to support factory-defined smoothing of common input variables

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "hartfunc.h"
#include "hart.h"
#include "bufutils.h"
#include "hartdef.h"
#include "position.h"
#include "tempr.h"
#include "tempr_mncb.h"

s8_least hartcmd_ReadTemperatureSmoothingCoefficient(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadTemperatureSmoothingCoefficient_t *d = (void *)dst;
    util_PutU8(d->SmoothCoefTempr[0], tempr_GetTemperatureData(NULL)->filtercoef.Shift);
    return HART_OK;
}
s8_least hartcmd_WriteTemperatureSmoothingCoefficient(const u8 *src, u8 *dst)
{
    UNUSED_OK(dst);
    TemperatureConf_t tc;
    const Req_WriteTemperatureSmoothingCoefficient_t *s = (const void *)src;
    (void)tempr_GetTemperatureData(&tc);
    tc.filtercoef.Shift = util_GetU8(s->SmoothCoefTempr[0]);
    ErrorCode_t err = tempr_SetTemperatureData(&tc);
    s8_least ret;
    if(err == ERR_OK)
    {
        ret = HART_OK;
    }
    else
    {
        ret = HART_INVALID_DATA;
    }
    return ret;
}

/* This line marks the end of the source */
