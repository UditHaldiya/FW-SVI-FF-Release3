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
    \file hart_refvoltage.c
    \brief Glue functions to support factory-defined Vref variables

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "hartfunc.h"
#include "hart.h"
#include "bufutils.h"
#include "hartdef.h"
#include "errcodes.h"
#include "refvoltage.h"
#include "crc.h"


s8_least hartcmd_Writereferencevoltage(const u8 *src, u8 *dst)
{
    const Req_Writereferencevoltage_t *s = (const void *)src;
    RefVoltage_t refVoltage;
    ErrorCode_t err;

    refVoltage.HiLimit = util_GetU32(s->refvHiLimit[0]);
    refVoltage.LoLimit = util_GetU32(s->refvLoLimit[0]);
    STRUCT_CLOSE(RefVoltage_t, &refVoltage);

    err = refvoltage_SetData(&refVoltage);

    UNUSED_OK(dst);
    return err2hart(err);
}

s8_least hartcmd_Readreferencevoltage(const u8 *src, u8 *dst)
{
    Rsp_Readreferencevoltage_t* d = (void*)dst;
    RefVoltage_t refVoltage;

    (void)refvoltage_GetData(&refVoltage); //lint, ignor return value
    util_PutU32(d->refvHiLimit[0], refVoltage.HiLimit);
    util_PutU32(d->refvLoLimit[0], refVoltage.LoLimit);

    UNUSED_OK(src);
    return HART_OK;
}
/* This line marks the end of the source */
