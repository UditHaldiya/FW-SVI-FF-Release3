/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvutils.c
    \brief A collection of project-specific NVMEM helpers

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "evertran.h"
#include "hart.h"
#include "mn_flash.h"

#if NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST == OPTION_ON
//This is a required interface. Doc in header
size_t nvmem_FillDeviceId(void *dst)
{
    const HartData_t *p = hart_GetHartData();
    mn_memcpy(dst, p->device_id, sizeof(p->device_id));
    return sizeof(p->device_id);
}
#endif //NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST

//This is a required interface. Doc in header
/* We assume it's Release1 in the opposite flash bank of APP because build info
is not present.
We can only deal with it if
    1. source_layout == NV_LAYOUT_LEGACY, in which case no translation needed, or
    2. we are running from flash/nvmem bank 1, so translated image goes to
       bank 0 where Release1 expects it.
    If neither condition is met, we shall fail to activate Release1
*/
ErrorCode_t nvmem_CheckCompatible(u8 source_layout)
{
    ErrorCode_t err = ERR_OK;
    if(source_layout == NV_LAYOUT_LEGACY)
    {
        //OK
    }
    else if(flash_GetRunningPartitionID() != 0) //i.e. == 1
    {
        //OK
    }
    else
    {
        err = ERR_NOT_SUPPORTED;
    }
    return err;
}

/* This line marks the end of the source */
