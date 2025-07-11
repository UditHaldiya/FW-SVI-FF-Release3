/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_faultrept.c
    \brief HART app functions to report faults (commands 136 and friends)

    Based on trunk implementation in hart_faultrept.c,27110

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/

#include "mnwrap.h"
#include "oswrap.h"
#include "faultpublic.h"
#include "hartfunc.h"
#include "hartdef.h"

#include "bufutils.h"
//#include "nvram.h"

/**
\brief Returns the fault codes.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadAddlStatus(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);

    return COMMAND_NOT_IMPLEMENTED;
}

/**
\brief Returns the fault codes

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadFullStatus(const u8 *src, u8 *dst)
{
    //"136:Read Status,<FaultCode1,<FaultCode2,<FaultCode3,<FaultCode4,,<FaultCode5,<FaultCode6"
    //      "<FaultHistory1,<FaultHistory2,<FaultHistory3,<FaultHistory4,
    //      <FaultHistory5,<FaultHistory6;"
    const FaultCodeData_t* pFaultCodeData;

    UNUSED_OK(src);

    Rsp_ReadFullStatus_t *d = (void *)dst;

    //get the fault code data
    pFaultCodeData = error_GetFaultCodeData(NULL);

    //we must report all of the faults
    CONST_ASSERT(sizeof(d->CurrentStatus) >= sizeof(pFaultCodeData->fcode));
    CONST_ASSERT(sizeof(d->HistoryStatus) >= sizeof(pFaultCodeData->fcodeHistory));

    //put the data in the buffer
    mn_memcpy(d->CurrentStatus, pFaultCodeData->fcode, sizeof(pFaultCodeData->fcode));
    mn_memset(d->CurrentStatus+sizeof(pFaultCodeData->fcode), 0, sizeof(d->CurrentStatus)-sizeof(pFaultCodeData->fcode));
    mn_memcpy(d->HistoryStatus, pFaultCodeData->fcodeHistory, sizeof(pFaultCodeData->fcodeHistory));
    mn_memset(d->HistoryStatus+sizeof(pFaultCodeData->fcodeHistory), 0, sizeof(d->HistoryStatus)-sizeof(pFaultCodeData->fcodeHistory));

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
\brief reads which fault bits will cause read additional status bit to turn on
*/
s8_least hartcmd_ReadFaultCodeMasks(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);

    return COMMAND_NOT_IMPLEMENTED;
}

/**
\brief sets which fault bits will cause read additional status bit to turn on
*/
s8_least hartcmd_WriteFaultCodeMasks(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);

    return COMMAND_NOT_IMPLEMENTED;
}

/**
\brief simulates a fault by setting the corresponding fault bit
*/
s8_least hartcmd_InjectFault(const u8 *src, u8 *dst)
{
    const Req_InjectFault_t *s = (const void *)src;
    UNUSED_OK(dst);
    u8 fbitnum = util_GetU8(s->FaultNumber[0]);
    error_SetFaultByBitNumber(fbitnum);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}


/* This line marks the end of the source */
