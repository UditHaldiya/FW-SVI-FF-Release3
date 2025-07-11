/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_advanced.c
    \brief functions about parameter ADVANCED

    CPU: Any

    OWNER:
    $Date: 07/08/13 15:40p $
    $Revision: 1 $
    $Author: victoria huang $

*/
#include <softing_base.h>
#include <ptb.h>
#include <appl_int.h>
#include <fbif_dcl.h>

//Glue headers last
#include "mn_advanced.h"
#include "mnadvcalc.h"
#include "bitutils.h"

#define PARA_ADV_READ_DWORD          5u
#define PARA_ADV_READ_BYTES          (PARA_ADV_READ_DWORD * sizeof(u32))
#define PARA_ADV_RWF_DWORD           12u
#define DEVICE_ID_BYTES              32u
#define PARA_ADV_REDWRT_BYTES        (PARA_ADV_RWF_DWORD *sizeof(u32))

#define state_CommitAdvanced         0
#define state_WriteOne               1
#define state_CommitBuffer           2
#define state_DoNothing              3

//--------------- AK added to replace violent write
#include "crc.h"
#include "nvram.h"

static AdvancedParam_t AdvancedParam;
static const AdvancedParam_t AdvancedParam_default =
{
    .advanced =
    {
        0xffffffffU,
        0xffffffffU,
        0xffffffffU,
        0xffffffffU,
        0xffffffffU,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    },
    .CheckWord = CRC_SEED //don't care
};

const AdvancedParam_t *ffcheck_GetAdvancedParam(AdvancedParam_t *dst)
{
    return STRUCT_TESTGET(&AdvancedParam, dst);
}

/** \brief Set function for AdvancedParam.
On completion, ptb_1.advanced and AdvancedParam.advanced hold identical bit
patterns, and alerts affected by the new bit pattern are disabled
\return an error code
*/
ErrorCode_t ffcheck_SetAdvancedParam(const AdvancedParam_t *src)
{
    if(src == NULL)
    {
        src = &AdvancedParam_default;
    }
    osif_disable_all_tasks();
    Struct_Copy(AdvancedParam_t, &AdvancedParam, src);
    CONST_ASSERT(sizeof(ptb_1.advanced) == sizeof(AdvancedParam.advanced));
    mn_memcpy(ptb_1.advanced, AdvancedParam.advanced, sizeof(ptb_1.advanced));
    osif_enable_all_tasks();

    /* re-check of the alert related parameters used to be here.
    Now, alerts wrapper monitors "Advanced" on the go
    */

    return ram2nvramAtomic(NVRAMID_AdvancedParam);
}

static fferr_t ffcheck_ffSetAdvancedParam(const AdvancedParam_t *src)
{
    ErrorCode_t err = ffcheck_SetAdvancedParam(src);
    fferr_t fferr;
    if(err == ERR_OK)
    {
        fferr = E_OK;
    }
    else
    {
        fferr = E_FB_TEMP_ERROR; //only reason is NV access error
    }
    return fferr;
}

//-------------


//A helper to save some stack
static void get_dev_id_only(STRINGV dev_id[DEVICE_ID_BYTES])
{
    u8 dev_addr;
    STRINGV pd_tag[DEVICE_ID_BYTES];
    get_sm_config_data(&dev_addr, pd_tag, dev_id);
}

static bool_t ffcheck_Advanced(const u8 advkey[PARA_ADV_REDWRT_BYTES], u32 FFKey)
{
    STRINGV dev_id[DEVICE_ID_BYTES];
    get_dev_id_only(dev_id);
    return mn_CalcAdvanced(PARA_ADV_REDWRT_BYTES, advkey, DEVICE_ID_BYTES, dev_id) == FFKey;
}

/* \brief write advanced parameter
    \param in:
        p_block_instance: pointer to function block
        p_write:  pointer to write resource data

    \return:
        FF error
*/
fferr_t ffcheck_WriteAdvanced
(
    T_FBIF_BLOCK_INSTANCE * p_block_instance,
    const T_FBIF_WRITE_DATA *p_write
)
{
    UNUSED_OK(p_block_instance);
    fferr_t fferr = E_OK;
    STRINGV dev_id[DEVICE_ID_BYTES];
    get_dev_id_only(dev_id);

    u8 state;
    //T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    //got the device id.

    switch (p_write->subindex)
    {
    case 0:
        state = state_CommitAdvanced;
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        state = state_WriteOne;
        break;

    case 13:
        state = state_CommitBuffer;
        break;

    case 14:
    default:
        state = state_DoNothing;
        break;
    }

    switch (state)
    {
    case state_CommitAdvanced:
        if (ffcheck_Advanced(p_write->source,
            mn_pull_u32((void *)(&p_write->source[PARA_ADV_REDWRT_BYTES]))))
        {
            fferr = ffcheck_ffSetAdvancedParam((const void *)p_write->source);
        }
        else
        {
            fferr = E_FB_PARA_LIMIT;
        }
        //do_write = true;
        break;
    case state_WriteOne:
    {
        //replace the write value to the array.
        u32 value = mn_pull_u32(p_write->source);
        storeMemberInt(&AdvancedParam, advanced[p_write->subindex - 1], value);
        fferr = E_FB_PARA_LIMIT;
        break;
    }

    case state_CommitBuffer:
    {
        //if we just change part of the parameter, it is already pre-initialized from PTB::advanced

        //replace the write value to the array.
        u32 value = mn_pull_u32(p_write->source);
        storeMemberInt(&AdvancedParam, advanced[p_write->subindex - 1], value);
        if (ffcheck_Advanced((const void *)AdvancedParam.advanced, AdvancedParam.advanced[PARA_ADV_RWF_DWORD]))
        {
            fferr = ffcheck_ffSetAdvancedParam(&AdvancedParam);
        }
        else
        {
            fferr = E_FB_PARA_LIMIT;
        }
        break;
    }
    case state_DoNothing:
    default:
        break;
    }

    return fferr;
}


/* \brief check if the parameter is readeable or not accroding to the advanced
    parameter read bitmap.
   \param p_block_instance - a pointer to TB instance
   \param index - the parameter index number

   \return true iff the related parameter is readable
*/
bool_t ffcheck_ReadBitmap(const T_FBIF_BLOCK_INSTANCE *p_block_instance, u16_least index)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    //check if the parameter is readable or not according to bitmap.
    bool_t bBit = util_GetBit(index,
       (const void*)p_PTB->advanced, PARA_ADV_READ_BYTES);

    if(!bBit)
    {
        bBit = ffcheck_WriteBitmap(index); //Must be able to read what we write
    }

    return bBit;

}

/* \brief check if the parameter is writeable or not accroding to the advanced
    parameter write bitmap.
   \param in:
        index: the parameter index number

   \return:
        True:  the related parameter is writeable
        False: the related parameter is not writeable
*/
bool_t ffcheck_WriteBitmap(u16_least index)
{
    const T_FBIF_PTB *p_PTB = fbs_get_block_inst(ID_PTB_1)->p_block_desc->p_block;

    //check if the parameter is writeable or not according to bitmap.
    bool_t bBit = util_GetBit(index,
       (const void*)&p_PTB->advanced[PARA_ADV_READ_DWORD], PARA_ADV_READ_BYTES);
    if(!bBit)
    {
        //Check if it is subject to override
        if(( index < nelem_advanced_write_override) && (advanced_write_override[index] != 0)) //lint !e416 !e415 missing short-circuiting
        {
            bBit = true;
        }
    }
    return bBit;

}

/* \brief check if the device is standard type, disable the advanced parameter
    write function, and will reject the write operation.
   \param in:
        p_block_instance: pointer to function block
        p_write:  pointer to write resource data

   \return:
        FF error
*/
fferr_t ffcheck_WriteFilter
(
    const T_FBIF_BLOCK_INSTANCE *p_block_instance,
    const T_FBIF_WRITE_DATA     *p_write
)
{
    fferr_t fferr = E_OK;
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;

    bool_t bWBit;

    //filter for not writeable parameters.
    bWBit = ffcheck_WriteBitmap(p_write->rel_idx);
    if(!bWBit)
    {
        fferr = E_FB_WRITE_LOCK;
    }

    //check when the TB.actual mode is LO,reject the parameter write except the
    //MODE_BLK,APP_MODE,Factory_USE1 and Advanced key;
    if (E_OK == fferr)
    {
        if (MODE_LO == p_PTB->mode_blk.actual)
        {
            if (p_write->rel_idx != REL_IDX_PTB_PTB
                &&p_write->rel_idx != REL_IDX_PTB_MODE_BLK
                && p_write->rel_idx != REL_IDX_PTB_APP_MODE
                && p_write->rel_idx != REL_IDX_PTB_ADVANCED
                && p_write->rel_idx != REL_IDX_PTB_FACTORY_USE_1)
            {
                fferr = E_FB_WRONG_MODE;
            }
        }
    }

    return fferr;
}

/* \brief Jams the TB parameter disallowed by "Advanced"

Applies to read handler (MN redirected version) or internal application such as
IPC layer. If NOT read handler, the whole parameter is jammed to a constant value,
otherwise only sub-parameter.

This is messy, so it is encapsulated into an awkward function

\param p_block_instance  - TB instance pointer
\param base_dst - where to write (base address)
\param rel_idx - index of the parameter
\param subindex_offset - passed by read handler; ignored for live TB
\param size - passed by read handler; ignored for live TB
\return true iff no jamming (param allowed)
*/
bool_t mnadv_JamPtbParam(T_FBIF_BLOCK_INSTANCE *p_block_instance, u16_least rel_idx,
                         void *base_dst,
                         u16_least subindex_offset,
                         u16_least param_size)
{
    bool_t ret = ffcheck_ReadBitmap(p_block_instance, rel_idx);
    if(!ret)
    {
        u8 *dst = (u8 *)base_dst;
        const T_FBIF_BLOCK_DESCR *p_block_desc = p_block_instance->p_block_desc;
        const T_FBIF_PARAM_DESCR *par_descr_ptr = &p_block_desc->param_dir[rel_idx];
        if(base_dst == p_block_desc->p_block)
        {
            //We are jamming the whole parameter in live TB!
            dst += par_descr_ptr->par_offset;
            param_size = par_descr_ptr->par_size;
            subindex_offset = 0;
        }

#if 1
        //Jam with 0's pattern which is OK
        memset(dst, 0, param_size);
        UNUSED_OK(subindex_offset);
#else
        //Jam with firmware defaults (better but needs a review/fix of default values
        const u8 *src = (const u8 *)&c_ptb;
        src += par_descr_ptr->par_offset + subindex_offset; //lint !e960 pointer arithmetic
        memcpy(dst, src, param_size);
#endif

    }
    return ret;
} //lint !e818 const T_FBIF_BLOCK_INSTANCE * would be misleading


/* This line marks the end of the source */
