/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pidselect.c
    \brief Function that returns auto-tunable PID paramters set as the current set

    CPU: Any

    OWNER: AK

    \ingroup control
*/
#include "mnwrap.h"
#include "selftune.h"
#include "dimensions.h"
#include "nvram.h"
#include "crc.h"
#ifdef OLD_NVRAM
#include "oswrap.h"
#endif
#include "mnassert.h"
static const CtlSetSlot_t ctlset_default =
{
    .slot = CTLPARAMSET_AUTOTUNE,
    .CheckWord = CRC_SEED
};

static CtlSetSlot_t ctlset;

const void *TypeUnsafe_posctl_GetCtlset(void *dst)
{
    return STRUCT_TESTGET(&ctlset, dst);
}

ErrorCode_t TypeUnsafe_posctl_SetCtlset(const void *src)
{
    ErrorCode_t err;
    const CtlSetSlot_t *p = src;
    if(p == NULL)
    {
        p = &ctlset_default; //default init
    }
    if(p->slot >= NUM_POSCTL_PARAMSETS)
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        Struct_Copy(CtlSetSlot_t, &ctlset, p);
        ErrorCode_t err1 = tune_SetCurrentPIDData(tune_GetPIDData(p->slot, NULL));
        MN_DBG_ASSERT(err1 == ERR_OK); //An error here is purely a coding error
        err = ram2nvramAtomic(NVRAMID_CtlSetSlot);
#ifdef OLD_NVRAM
        if(oswrap_IsOSRunning())
        {
            posctl_Save();
        }
#endif
    }
    return err;
}


/** \brief Returns the current PID parameters index.
    \return u8 - PID Parameter index of auto-tunable set
*/
u8 posctl_GetCtlSetIndex(void)
{
    return posctl_GetCtlset(NULL)->slot;
}


#ifdef OLD_NVRAM
//NVRAM Shims
void posctl_Init(InitType_t itype)
{
    CtlSetSlot_t t;
    CtlSetSlot_t *p;
    if(itype==INIT_FROM_NVRAM)
    {
        nvram2ram(&t, NVRAMID_CtlSetSlot);
        p = &t;
    }
    else
    {
        p = NULL;
    }
    (void)posctl_SetCtlset(p);
}

void posctl_Save(void)
{
    Struct_Test(CtlSetSlot_t, &ctlset);
    MN_FRAM_ACQUIRE();
        ram2nvram(&ctlset, NVRAMID_CtlSetSlot);
    MN_FRAM_RELEASE();
}

#endif


/* This line marks the end of the source */
