/*
Copyright 2013-2014 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

Based in part on the original Softing code whose copyright notice follows
*/

/*****************************************************************************
*                                                                            *
*                     SOFTING Industrial Automation GmbH                     *
*                          Richard-Reitzner-Allee 6                          *
*                                D-85540 Haar                                *
*                        Phone: ++49-89-4 56 56-0                            *
*                          Fax: ++49-89-4 56 56-3 99                         *
*                                                                            *
*                            SOFTING CONFIDENTIAL                            *
*                                                                            *
*                     Copyright (C) SOFTING IA GmbH 2012                     *
*                             All Rights Reserved                            *
*                                                                            *
* NOTICE: All information contained herein is, and remains the property of   *
*   SOFTING Industrial Automation GmbH and its suppliers, if any. The intel- *
*   lectual and technical concepts contained herein are proprietary to       *
*   SOFTING Industrial Automation GmbH and its suppliers and may be covered  *
*   by German and Foreign Patents, patents in process, and are protected by  *
*   trade secret or copyright law. Dissemination of this information or      *
*   reproduction of this material is strictly forbidden unless prior         *
*   written permission is obtained from SOFTING Industrial Automation GmbH.  *
******************************************************************************
******************************************************************************
*                                                                            *
* PROJECT_NAME             Softing FF/PA FD 2.42                             *
*                                                                            *
* VERSION                  FF - 2.42                                         *
*                          PA - 2.42 (beta)                                  *
*                                                                            *
* DATE                     16. April 2012                                    *
*                                                                            *
*****************************************************************************/

/* ===========================================================================

FILE_NAME          eep_if.c



FUNCTIONAL_MODULE_DESCRIPTION

=========================================================================== */
#include "keywords.h"
#define  MODULE_ID      (COMP_EEP + MOD_EEPIF)


INCLUDES
#include <base.h>
#include <osif.h>
#include "eep_if.h"
#include <hw_i2c.h> //for i2c mutex
#include <fbif.h>

#include <except.h>
#include <dbg_out.h>

#include "mnassert.h"
#include "fram.h"

#include "logfproc.h"
#include "logfile.h"
#include "faultpublic.h"
#include "nvmempriv.h"
#include "nvffext.h"

//FUNCTION_DECLARATIONS
LOCAL T_EEP_RESULT  eep_param_check (USIGN8 block_id, USIGN16 offset, USIGN16 length);
static void eep_put (u8_least block_id);


/*######################  EEP Interface Functions  #########################*/

/** \brief Compatibility layer for Softing-style API
Checks existence / consistency of a block and provides a pointer to the block
start address, if successful, NULL in case of error.

\param  block_id - ID of block
\param block_len - size of block
\param p_ram_image - pointer to pointer to data image
\return one of
    EEP_OK              => no error, '*p_ram_image' points to start of block
    EEP_NOT_EXIST       => block with ID 'block_id' does not exist
    EEP_INCONSISTENT    => size of block does not agree with 'block_len'
    EEP_CS_ERR          => checksum of block invalid -> data probably corrupt
    EEP_READ_ERR        => EEPROM could not be read
*/
T_EEP_RESULT eep_provide_block(USIGN8 block_id, USIGN16 block_len, void **p_ram_image)
{
    T_EEP_RESULT ret;
    *p_ram_image = NULL;

    if ( eep_param_check (block_id, 0, 0) != EEP_OK )
    {
        DBG_PRINT_NOWAIT_( ("eep_provide_block: block %d not existent\n", block_id) );
        ret = (EEP_NOT_EXIST);
    }
    else
    {
        ret = (EEP_INCONSISTENT);
        if (block_len != nvram_map[eepmap[block_id].nvid].length) //Too strict; could be >
        {
            DBG_PRINT_NOWAIT_( ("eep_provide_block: block %d not consistent\n", block_id) );
        }
        else
        {
            *p_ram_image = eepmap[block_id].buffer;
            if(eepmap[block_id].buffer != NULL)
            {
                /* NOTE:
                Softing used to check the CRC of the block here.
                Since
                1. we compute the CRC in the buffer
                2. the original implementation is not thread-safe
                there is no value in maintaining the CRC live
                */
                ret = EEP_OK;
            }
        }
    }
    return ret;
} /* FUNCTION eep_provide_block */

//lint -esym(818, p_eep_block_dsc) can't change Softing public prototype to make it const*
/** \brief Verifies 'no_of_eep_block_dsc' block descriptions for compatibility
with FRAM layout.

\return EEP_OK if compatible, otherwise EEP_PARAM_ERR (and will crash in Debug build)
*/
T_EEP_RESULT eep_config_change(USIGN8 no_of_eep_block_dsc, T_EEP_BLOCK_DSC *p_eep_block_dsc)
{
    T_EEP_RESULT ret = EEP_OK;

    for (USIGN8 i=0; i<no_of_eep_block_dsc; i++)
    {
        USIGN8 block_id = p_eep_block_dsc[i].block_id;
        if (block_id  == 0 )
        {
            /* ID 0 is not valid, but indicates an unused entry */
        }
        else if((block_id >=eepmap_size) || (eepmap[block_id].buffer == NULL))
        {
            ret = EEP_PARAM_ERR;
        }
        else
        {
            nvramId_fast_t nvid = eepmap[block_id].nvid;
            if(nvram_map[nvid].length < p_eep_block_dsc[i].block_size)
            {
                ret = EEP_PARAM_ERR;
            }
        }
        if(ret != EEP_OK)
        {
            break;
        }

    }
    MN_DBG_ASSERT(ret == EEP_OK);

    return ret;
}


/******************************************************************************/
/** \brief Compatibility layer for Softing API
Prepares a block for write operations.

\param block_id - ID of block
\return one of
    EEP_OK          => no error occured
    EEP_PARAM_ERR   => wrong parameter
    EEP_IN_CHANGE   => EEP configuration not consistent temporarily
*/
T_EEP_RESULT eep_start_write(USIGN8   block_id)
{
    /* Check parameters */
    T_EEP_RESULT result = eep_param_check (block_id, 0, 0);
    return (result);

} /* FUNCTION eep_start_write */


/****************************************************************************/

FUNCTION GLOBAL T_EEP_RESULT eep_write
(
    IN  USIGN8   block_id,          /* ID of block                          */
    IN  USIGN16  offset,            /* data offset inside the block         */
    IN  USIGN16  length,            /* length of data in bytes              */
    IN  USIGN8   mode               /* selected write mode                  */
)
/*----------------------------------------------------------------------------

FUNCTIONAL_DESCRIPTION

Writes data to the RAM image and, if needed, to the EEPROM. The only valid
value for the 'mode' parameter is :
  EEP_WAIT          the function returns after the final write cycle is
                    completed in the EEPROM device
If 'offset' == 0 and 'length' == 0 the whole block is written.

RETURN_VALUE
    EEP_OK          => no error occured
    EEP_PARAM_ERR   => wrong parameter
    EEP_PRG_ERR     => error while programming EEPROM
    EEP_IN_CHANGE   => EEP configuration not consistent temporarily

----------------------------------------------------------------------------*/
{
    /* ONLY EEP_WAIT is supported! - But we don't care (anymore) */
    UNUSED_OK(mode);

    /* Don't write when the length is 0 and not the */
    /* whole block should be written. */
    if ( (offset != 0) && (length == 0) )
    {
        //Nothing to do
    }
    else
    {
        /* Write data to EEPROM area */
        eep_put (block_id);
    }
    return EEP_OK;
} /* FUNCTION eep_write */

/*########################  Internal functions  ############################*/


/** \brief Checks the calling parameters against EEP block description.
\param block_id - ID of block
\param offset - data offset inside the block
\param length - length of data in bytes
\return
    EEP_OK          => parameters ok
    EEP_PARAM_ERR   => parameters do not agree with block description
    EEP_IN_CHANGE   => EEP configuration not consistent temporarily
*/
static T_EEP_RESULT eep_param_check(USIGN8 block_id, USIGN16 offset, USIGN16 length)
{
    T_EEP_RESULT ret = EEP_OK;
    /* Is block_id within the valid range? */
    if((block_id >=eepmap_size) || (eepmap[block_id].buffer == NULL))
    {
        ret = EEP_PARAM_ERR;
    }
    else
    {
        nvramId_fast_t nvid = eepmap[block_id].nvid;
        if((nvid == 0) || (nvram_map[nvid].length < (offset + length)))
        {
            ret = EEP_PARAM_ERR;
        }
    }

    return ret;
}


/****************************************************************************/

/** \brief creates a request for an eep block to be written.
\param block_id - A block to write
For now, errors ignored because it's all internal
*/
static void eep_put
(
    IN  u8_least   block_id          /* ID of block                          */
)
{
    if(block_id < eepmap_size)
    {
        nvramId_t nvid = eepmap[block_id].nvid;
        if(nvid != 0) //valid map
        {
            (void)nvmem_RequestWrite(nvid);
        }
    }
} /* FUNCTION eep_put */

//No param check!!!
static size_t eep_FindNVOffset(u8 fb_id)
{
    size_t offset = 0;
    for(u8 id=0; id<fb_id; id++)
    {
        offset += fbif_block_descr[id].block_n_par_len;
    }
    return offset;
}

static T_EEP_RESULT eep_save_fb_nv(u8 nv_blk_id, const void *src_nv, size_t offset, size_t len)
{
    void *ram_img;
    T_EEP_RESULT result = eep_provide_block(nv_blk_id, nvram_map[eepmap[nv_blk_id].nvid].length, &ram_img);
    if(result == EEP_OK)
    {
        osif_disable_all_tasks();
        mn_memcpy((u8 *)ram_img + offset, src_nv, len);
        osif_enable_all_tasks();
        eep_put(nv_blk_id);
    }
    return result;
}

/** \brief Copy STATIC and NV areas of a function block from some RAM to FB and
requests a (delayed) write to FRAM.
\param fb_id - FB id (to include, here, RB and TB)
\param src_static - a pointer to RAM source for STATIC data; NULL skips the operation
\param offs_static - offset in FB STATIC image of the object to write
\param len_static - length in FB STATIC image of the object to write
\param src_nv- a pointer to RAM source for NV data; NULL skips the operation
\param offs_nv - offset in FB NV image of the object to write
\param len_nv - length in FB NV image of the object to write
\return eep-type error code
*/
T_EEP_RESULT eep_SaveFB(u8 fb_id,
                        const void *src_static, u16 offs_static, u16 len_static,
                        const void *src_nv, u16 offs_nv, u16 len_nv)
{
    if(fb_id >= fbif_dictionary.no_of_blocks)
    {
        return EEP_PARAM_ERR;
    }

    u8 eep_id = fb_id + EEP_FBL_BLK1;
    //STATIC param check
    if((src_static != NULL) && (nvram_map[eepmap[eep_id].nvid].length > (offs_static+len_static)))
    {
        return EEP_PARAM_ERR;
    }

    void *ram_img;
    T_EEP_RESULT result = EEP_OK;


    //NV data
    if((src_nv != NULL) && (fbif_block_descr[fb_id].block_n_par_len != 0))
    {
        u16 length = nvram_map[eepmap[EEP_NV_BLK1].nvid].length;
        size_t offset = eep_FindNVOffset(fb_id);
        if( (offset + fbif_block_descr[fb_id].block_n_par_len) > length)
        {
            result = EEP_INCONSISTENT;
        }
        else if((offs_nv + len_nv) > length)
        {
            result = EEP_PARAM_ERR;
        }
        else
        {
            offset += offs_nv;
            result = eep_save_fb_nv(EEP_NV_BLK1, src_nv, offset, len_nv);
        }
    }

    //STATIC data
    if(result == EEP_OK)
    {
        u16 length = nvram_map[eepmap[eep_id].nvid].length;
        if((src_static != NULL) && (fbif_block_descr[fb_id].block_eep_len != 0))
        {
            result = eep_provide_block(eep_id, length, &ram_img);
            if(result == EEP_OK)
            {
                osif_disable_all_tasks();
                mn_memcpy((u8 *)ram_img + offs_static, src_static, len_static);
                osif_enable_all_tasks();
                eep_put(eep_id);
            }
        }
    }
    return result;
}

//From FB to some RAM
/** \brief Copy STATIC and NV images of a function block to some RAM.
\param fb_id - FB id (to include, here, RB and TB)
\param dst_static - a pointer to RAM destination for STATIC data; NULL skips the operation
\param offs_static - offset in FB STATIC image of the object to read
\param len_static - length in FB STATIC image of the object to read
\param dst_nv- a pointer to RAM destination for NV data; NULL skips the operation
\param offs_nv - offset in FB NV image of the object to read
\param len_nv - length in FB NV image of the object to read
\return eep-type error code
*/
T_EEP_RESULT eep_ReadFB(u8 fb_id, void *dst_static, u16 len_static, void *dst_nv, u16 len_nv)
{
    if(fb_id >= fbif_dictionary.no_of_blocks)
    {
        return EEP_PARAM_ERR;
    }

    u8 eep_id = fb_id + EEP_FBL_BLK1;
    void *ram_img;
    T_EEP_RESULT result = EEP_OK;

    MN_NVMEM_LOCK(2U); //Just a small number since we don't go to FRAM here
    //NV data; don't care about the second copy
    if(fbif_block_descr[fb_id].block_n_par_len != 0)
    {
        u16 length = nvram_map[eepmap[EEP_NV_BLK1].nvid].length;
        size_t offset = 0;
        for(u8 id=0; id<fb_id; id++)
        {
            offset += fbif_block_descr[id].block_n_par_len;
        }
        if( (offset + fbif_block_descr[fb_id].block_n_par_len) > length)
        {
            result = EEP_INCONSISTENT;
        }
        else
        {
            result = eep_provide_block(EEP_NV_BLK1, length, &ram_img);
            if(result == EEP_OK)
            {
                mn_memcpy(dst_nv, (u8 *)ram_img + offset, len_nv);
            }
        }

    }

    //STATIC data
    if(result == EEP_OK)
    {
        if(fbif_block_descr[fb_id].block_eep_len != 0)
        {
            result = eep_provide_block(eep_id, len_static, &ram_img);
            if(result == EEP_OK)
            {
                mn_memcpy(dst_static, ram_img, len_static);
            }
        }
    }
    MN_NVMEM_UNLOCK();
    return result;
}

//---------- log file interface -----------------

static T_EEP_RESULT eep_err2eep(ErrorCode_t err)
{
    T_EEP_RESULT result;
    if(err == ERR_LOGF_INVALID)
    {
        result = EEP_NOT_EXIST;
    }
    else
    {
        MN_RT_ASSERT(err == ERR_OK); //TODO: test for I2C bus errors
        result = EEP_OK;
    }
    return result;
}


static T_EEP_RESULT eep_file2fb_nv(u8 logfId, u8 nv_blk_id, size_t offset, u16 len)
{
    void *ram_img;
    u16 length = nvram_map[eepmap[nv_blk_id].nvid].length;
    T_EEP_RESULT result = eep_provide_block(nv_blk_id, length, &ram_img);
    if(result == EEP_OK)
    {
        u8 *img = ram_img;
        ErrorCode_t err = logf_RetrieveAtomic(img + offset, &len, logfId, 0);
        result = eep_err2eep(err);
        if(result == EEP_OK)
        {
            eep_put(nv_blk_id);
        }
    }
    return result;
}


/** \brief Copy STATIC and NV areas of a function block from some RAM to FB and
requests a (delayed) write to FRAM.
\param fb_id - FB id (to include, here, RB and TB)
\param logf_static - Log file id for STATIC data
\param offs_static - offset in FB STATIC image of the object to write
\param len_static - length in FB STATIC image of the object to write
\param logf_nv - Log file id for NV data
\param offs_nv - offset in FB NV image of the object to write
\param len_nv - length in FB NV image of the object to write
\return eep-type error code
*/
T_EEP_RESULT eep_RestoreFile2FB(u8 fb_id,
                        u8 logf_static, u16 offs_static, u16 len_static,
                        size_t st_rev_offset, u16 st_rev,
                        u8 logf_nv, u16 offs_nv, u16 len_nv)
{
    if(fb_id >= fbif_dictionary.no_of_blocks)
    {
        return EEP_PARAM_ERR;
    }

    u8 eep_id = fb_id + EEP_FBL_BLK1;
    u16 length = nvram_map[eepmap[eep_id].nvid].length;
    //STATIC param check
    if(length > (offs_static+len_static))
    {
        return EEP_PARAM_ERR;
    }

    void *ram_img;
    T_EEP_RESULT result = EEP_OK;


    //NV data
    if((len_nv != 0) && (fbif_block_descr[fb_id].block_n_par_len != 0))
    {
        u16 lengthN = nvram_map[eepmap[EEP_NV_BLK1].nvid].length;
        size_t offset = eep_FindNVOffset(fb_id);
        if( (offset + fbif_block_descr[fb_id].block_n_par_len) > lengthN)
        {
            result = EEP_INCONSISTENT;
        }
        else if((offs_nv + len_nv) > lengthN)
        {
            result = EEP_PARAM_ERR;
        }
        else
        {
            offset += offs_nv;
            result = eep_file2fb_nv(logf_nv, EEP_NV_BLK1, offset, len_nv);
        }
    }

    //STATIC data
    if(result == EEP_OK)
    {
        if((len_static != 0) && (fbif_block_descr[fb_id].block_eep_len != 0))
        {
            result = eep_provide_block(eep_id, length, &ram_img);
            if(result == EEP_OK)
            {
                ErrorCode_t err = logf_RetrieveAtomic(ram_img, &len_static, logf_static, 0);
                result = eep_err2eep(err);
                if(result == EEP_OK)
                {
                    //fix static revision
                    *(u16 *)(void *)((u8 *)ram_img + st_rev_offset) = st_rev;
                    eep_put(eep_id);
                }
            }
        }
    }
    return result;
}

//From FB to some RAM
/** \brief Copy STATIC and NV images of a function block to some RAM.
\param fb_id - FB id (to include, here, RB and TB)
\param dst_static - a pointer to RAM destination for STATIC data; NULL skips the operation
\param offs_static - offset in FB STATIC image of the object to read
\param len_static - length in FB STATIC image of the object to read
\param dst_nv- a pointer to RAM destination for NV data; NULL skips the operation
\param offs_nv - offset in FB NV image of the object to read
\param len_nv - length in FB NV image of the object to read
\return eep-type error code
*/
T_EEP_RESULT eep_WriteFB2File(u8 fb_id,
                              u8 logf_static, u16 len_static,
                              u8 logf_nv, u16 len_nv)
{
    if(fb_id >= fbif_dictionary.no_of_blocks)
    {
        return EEP_PARAM_ERR;
    }

    u8 eep_id = fb_id + EEP_FBL_BLK1;
    void *ram_img;
    T_EEP_RESULT result = EEP_OK;

    //NV data
    if(fbif_block_descr[fb_id].block_n_par_len != 0)
    {
        size_t offset = 0;
        for(u8 id=0; id<fb_id; id++)
        {
            offset += fbif_block_descr[id].block_n_par_len;
        }
        u16 length = nvram_map[eepmap[EEP_NV_BLK1].nvid].length;
        if( (offset + fbif_block_descr[fb_id].block_n_par_len) > length)
        {
            result = EEP_INCONSISTENT;
        }
        else
        {
            result = eep_provide_block(EEP_NV_BLK1, length, &ram_img);
            if(result == EEP_OK)
            {
                ErrorCode_t err = logf_SubmitWrite(logf_nv, ram_img, len_nv);
                MN_DBG_ASSERT(err == ERR_OK);
                UNUSED_OK(err); //for release build
            }
        }

    }

    //STATIC data
    if(result == EEP_OK)
    {
        if(fbif_block_descr[fb_id].block_eep_len != 0)
        {
            result = eep_provide_block(eep_id, len_static, &ram_img);
            if(result == EEP_OK)
            {
                ErrorCode_t err = logf_SubmitWrite(logf_static, ram_img, len_static);
                MN_DBG_ASSERT(err == ERR_OK);
                UNUSED_OK(err); //for release build
            }
        }
    }
    return result;
}

//---------- end log file interface -----------------
