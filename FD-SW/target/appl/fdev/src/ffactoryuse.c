/*
Copyright 2013 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffactoryuse.c
    \brief factory_use_{1,2} support in FFP

    HART pass-through and FFP intercepts
*/
#include <softing_base.h>
#include <ptb.h>
#include <eep_if.h>


#include "ffactoryuse.h"

#include "hartvers.h"
#include "hartfunc.h"
#include "wprotect.h"

/*factory_use_1 layout
0 - cmd
1 - length
2+ - data payload
*/
/*factory_use_2 layout
0 - cmd
1 - delimiter
2 - response code 1
3 - response code 2
4+ - data payload
*/
#define FFACT_DATA_OFFSET 4

/** \brief Handler of Write to FACTORY_USE_1
Processes a "HART command" in FACTORY_USE_1 to
\param p_block_instance - a pointer to block instance
\return E_OK
*/
fferr_t ffact_WriteFactoryUse1(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    UNUSED_OK(snd_buf);
    UNUSED_OK(rcv_buf);
    u8_least i;
    fferr_t e = E_OK;

    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    //clear factory_use_2 PTB array before filling it from HART
    for ( i = 2; i < NELEM(p_PTB->factory_use_2); i++ )
    {
        p_PTB->factory_use_2[i] = 0x0;
    }
    //write command number to factory_use_2 to return it in the read
    p_PTB->factory_use_2[0] = p_PTB->factory_use_1[0];
    p_PTB->factory_use_2[1] = 0xFF; // delimiter between cmd number and returned values

    s8_least ret = hart5_Dispatch(p_PTB->factory_use_1[0], &p_PTB->factory_use_1[2],
                                  &p_PTB->factory_use_2[FFACT_DATA_OFFSET], p_PTB->factory_use_1[1]);
    if(ret != -COMMAND_NOT_IMPLEMENTED)
    {
        //intercepted!
        if(ret > 0)
        {
            //ret is length; no error
            ret = 0;
        }
        else
        {
            //ret = -error
            ret = -ret;
        }
        p_PTB->factory_use_2[2] = (u8)(ret);
        p_PTB->factory_use_2[3] = 0; //bogus status 2
    }
    else
    {
        //send the requested HART command to APP
        (void)mn_HART_acyc_cmd( p_PTB->factory_use_1[0], &p_PTB->factory_use_1[2],
                                p_PTB->factory_use_1[1], &p_PTB->factory_use_2[2] );
         if(p_PTB->factory_use_2[2] == HART_TYPE_MISMATCH)
         {
             p_PTB->factory_use_2[2] = HART_BUSY; //we actually timed out
         }
    }

    return e;
}

fferr_t ffact_ReadFactoryUse1or2(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf)
{
    UNUSED_OK(snd_buf);
    UNUSED_OK(rcv_buf);
    //clear factory_use_1 PTB array
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    mn_memset(p_PTB->factory_use_1, 0xFF, sizeof(p_PTB->factory_use_1));
    return E_OK;
}
/* This line marks the end of the source */
