/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_activate.c
    \brief HART glue layer for control (position setpoint) limits

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "hartfunc.h"
#include "hartdef.h"
#include "bufutils.h"
#include "activate_id_sn.h"
#include "process.h"

/**
\brief Write activation code
*/
s8_least hartcmd_WriteActivationCode(const u8 *src, u8 *dst)
{
    UNUSED_OK(dst);
    const Req_WriteActivationCode_t *s = (const void *)src;
    ActivateVerifyData_t avd;
    avd.k[SIGNATURE_SERIALNUM] = util_GetU8(s->DeviceActivationCode1[0]);
    avd.k[SIGNATURE_DEVICEID] = util_GetU8(s->DeviceActivationCode2[0]);
    CONST_ASSERT(SIGNATURE_COUNT==2);
    CONST_ASSERT(sizeof(avd.avdata[SIGNATURE_SERIALNUM].signature) == sizeof(s->DeviceActivationSignature1));
    CONST_ASSERT(sizeof(avd.avdata[SIGNATURE_DEVICEID].signature) == sizeof(s->DeviceActivationSignature2));
    util_GetU8Array(s->DeviceActivationSignature1[0], sizeof(avd.avdata[SIGNATURE_SERIALNUM].signature),
                    (u8 *)&avd.avdata[SIGNATURE_SERIALNUM].signature);
    util_GetU8Array(s->DeviceActivationSignature2[0], sizeof(avd.avdata[SIGNATURE_DEVICEID].signature),
                    (u8 *)&avd.avdata[SIGNATURE_DEVICEID].signature);

    ErrorCode_t err = actver_SetData(&avd);
    return err2hart(err); //output buffer filled automatically but we don't care
}

/** Determines sign/verify algorithm or its parameters. So, instructs the signing server
how to compute signature. When becomes non-zero, should migrate to activate_id_sn.h
and affect the verification code.
*/
#define MN_ACTIVATION_VERSION 0

/**
\brief Read activation data
*/
s8_least hartcmd_ReadActivationData(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadActivationData_t *d = (void *)dst;
    u64 key;
    key = actver_GetKeyArtifact(SIGNATURE_SERIALNUM);
    util_PutU8Array(d->DeviceActivationData1[0], sizeof(key), (u8 *)&key);
    key = actver_GetKeyArtifact(SIGNATURE_DEVICEID);
    util_PutU8Array(d->DeviceActivationData2[0], sizeof(key), (u8 *)&key);
    util_PutU16(d->DeviceActivationData3[0], MN_ACTIVATION_VERSION);
    u32 t = actver_GetAndClearLength();
    t = MIN(t, 0x00FFFFFFU); //just limit to 24 bits
    util_PutU24(d->DeviceActivationData4[0], t);
    t = process_SampleAndClearOverhead();
    util_PutU8(d->DeviceActivationData5[0], (u8)MIN(t,0xFFU));
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/* This line marks the end of the source */
