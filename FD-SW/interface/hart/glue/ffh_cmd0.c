/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffh_nvmemif.c
    \brief HART-over-FF glue layer for MN interfaces

    Similar to APP's version

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/

#include "mnwrap.h"
#include "hartdef.h"
#include "hartcmd.h"
#include "hartfunc.h"
#include "bufutils.h"
#include "mncbdefs.h"

#include <keywords.h>
#include <base.h>
#include "hm_api.h"

//From hart.h which can't be included in FFP (too much stuff there)
#define NBR_REQUEST_PREAM  (u8)5     /* Anzahl der Requestpreambles      */
#define UNIV_CMD_REV       (u8)0x05  /* Revisionstaende fuer universal-, */
#define FLAGS              (u8)0x00

/**
\brief Returns basic HART addressing and command information

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hart_Command_0_ReadUniqueIdentifier(const u8 *src, u8 *dst)
{
    dst[HC0_DUMMY] = 254;
    dst[HC0_MFGID] = MNCB_MANUFACTURER_ID;
    dst[HC0_DEVICE_TYPE] = MNCB_MANUFACTURER_DEVICE_CODE;
    dst[HC0_PREAMBLES] = NBR_REQUEST_PREAM;
    dst[HC0_CMDREV] = UNIV_CMD_REV;
    dst[HC0_TXREV] = TXSPEC_REV; //by new convention FFP same as APP

    dst[HC0_SWREV] = SW_REV;
    dst[HC0_HWREV] = MNCB_HARDWARE_REVISION;
    dst[HC0_FLAG] = FLAGS;

    const APPHeader_t *p = hm_GetAPPHeader(NULL);
    util_PutU8Array(&dst[HC0_DEVICE_ID], 3u, &p->appheader[3]); //See construction of APPHeader

    UNUSED_OK(src);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/* This line marks the end of the source */
