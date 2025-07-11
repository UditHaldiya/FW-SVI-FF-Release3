/*
Copyright 2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file eepshim.c
    \brief Implementation of shim layer - Softing API over Masoneilan NVRAM.

    For the time being (i.e. util more documentation becomes available from
    Softing), whatever is mapped via Softing API remains "all or nothing", i.e.
    if anything wrong with "eep" blocks is detected, they all will be
    reinitialized. This includes protocol blocks and RB/FB/TB parameters left
    for Softing to manage.

    To wean RB/FB/TB parameters off Softing eep management and to put them under
    Masonelan NVRAM management,
1. Remove the from eep: GW N attribute disappears and S attribute is replaced with V
2. Add as a normal NVRAM object

It is recommended (for the time being) that only non-standard parameters be placed
under native Masoneilan NVRAM management.

    CPU: Any

    OWNER: AK

    \ingroup nvmem
*/

#include "mnwrap.h"
#include "nvram.h"
#include <eep_if.h>
#include <fdev_cfg.h>
#include <fbap.h>
#include <fbif.h>
#include <fbif_dcl.h>
#include <osif.h>
#include "nvmemids.h"
#include "eepshim.h"
#include "crc.h"
#include "asciicodes.h"


/** \brief Restores constant data in blk_data of type F_BLOCK.
Only matters for changing the parameter definitions without full initialization.
NOTE: Doesn't repair the CheckWord.
NOTE: Must be called from a critical section.
\param dst - a pointer to block's blk_data sub-object
\param src - a pointer to replacement (may come from NVMEM, most likely)
\param fw_default - a pointer to firmware default value of blk_data
*/
void blk_data_Repair(F_BLOCK *dst, const F_BLOCK *src, const F_BLOCK *fw_default)
{
    /* Override block data */
    *dst = *fw_default;
    /* Restore mutables in blk_data */
    memcpy(dst->block_tag, src->block_tag, sizeof(src->block_tag));
    dst->period_of_execution = src->period_of_execution;
    dst->next_fb_to_execute = src->next_fb_to_execute;
}
//lint -esym(960 961, NVRAMSTUB_PROT) multiple '##' used


/** \brief NVRAMSTUB_PROT is an intercept of Softing manipulation with their eep model
of NVMEM of eep protocol blocks.
It is responsible for reading/writing data in "eep blocks" replacements
but doesn't deal with NVMEM operations such as ram2nvramAtomic().
Actual write operations are performed or requested by a replacement of eep_put().
Likewise, CheckWord protection is off. The "get" function creates a valid
checksum at destination; that's all.
*/
#if 0 //unrolled example of protocol block
EXTMEM static nv_trend_cfg_t nv_trend_cfg;
const nv_trend_cfg_t *eepshim_Get_nv_trend_cfg(nv_trend_cfg_t *dst)
{
    return STRUCT_GET(&nv_trend_cfg, dst);
}
ErrorCode_t eepshim_Set_nv_trend_cfg(const nv_trend_cfg_t *src)
{
    if(src == NULL)
    {
        //Will be immediately overwritten so don't bother with content (yet)
        memset(&nv_trend_cfg, EEP_INIT_VALUE, MN_OFFSETOF(nv_trend_cfg_t, CheckWord));
        STRUCT_CLOSE(nv_trend_cfg_t, &nv_trend_cfg);
    }
    else
    {
        Struct_Copy(nv_trend_cfg_t, &nv_trend_cfg, src); //No data checks - left to app
    }
    return ERR_OK;
}
#endif //0

EXTMEM static NV_fb_start_cfg_t nv_fb_start_cfg;
const NV_fb_start_cfg_t *eepshim_Get_nv_fb_start_cfg(NV_fb_start_cfg_t *dst)
{
    return STRUCT_GET(&nv_fb_start_cfg, dst);
}
ErrorCode_t eepshim_Set_nv_fb_start_cfg(const NV_fb_start_cfg_t *src)
{
    if(src == NULL)
    {
        //Will be immediately overwritten so don't bother with content (yet)
        memset(&nv_fb_start_cfg, EEP_INIT_VALUE, MN_OFFSETOF(NV_fb_start_cfg_t, CheckWord));
        STRUCT_CLOSE(NV_fb_start_cfg_t, &nv_fb_start_cfg);
    }
    else
    {
        Struct_Copy(NV_fb_start_cfg_t, &nv_fb_start_cfg, src); //No data checks - left to app
    }
    return ERR_OK;
}


#define NVRAMSTUB_PROT(bname) \
EXTMEM static bname ## _t bname; \
const bname ## _t *eepshim_Get_ ## bname(bname##_t *dst) \
{ \
    return STRUCT_GET(&bname, dst); \
} \
ErrorCode_t eepshim_Set_##bname(const bname##_t *src) \
{ \
    if(src == NULL) \
    { \
        /* Will be immediately overwritten so don't bother with content (yet) */ \
        mn_memset(&bname, EEP_INIT_VALUE, MN_OFFSETOF(bname##_t, CheckWord)); \
    } \
    else \
    { \
        Struct_Copy(bname##_t, &bname, src); /*No data checks - left to app*/ \
    } \
    return ERR_OK; \
}

NVRAMSTUB_PROT(nv_trend_cfg)
NVRAMSTUB_PROT(nv_vcr_cfg)
//NVRAMSTUB_PROT(nv_fb_start_cfg)
NVRAMSTUB_PROT(nv_las_cfg)
NVRAMSTUB_PROT(nv_fb_link_cfg)
NVRAMSTUB_PROT(nv_fdc_blk_base_cfg)
NVRAMSTUB_PROT(nv_fdc_blk_dll_base_cfg)
NVRAMSTUB_PROT(nv_fdc_blk_sm_cfg)
NVRAMSTUB_PROT(nv_fdc_blk_dll_lm_info_cfg)
NVRAMSTUB_PROT(nv_fdc_blk_dll_lm_data_cfg)
NVRAMSTUB_PROT(nv_swdl_blk_dwnld_cfg)


// ------------- NVRAM entry for "N" memory of FB/RB/TB ----------------
//Follows the pattern of NVRAMSTUB_PROT; may be macroized
EXTMEM static NV_fb_t NV_fb;
const NV_fb_t *eepshim_Get_NV_fb(NV_fb_t *dst)
{
    return STRUCT_GET(&NV_fb, dst);
}
ErrorCode_t eepshim_Set_NV_fb(const NV_fb_t *src)
{
    if(src == NULL)
    {
        //Will be immediately overwritten so don't bother with content (yet)
        memset(&NV_fb, EEP_INIT_VALUE, MN_OFFSETOF(NV_fb_t, CheckWord));
    }
    else
    {
        Struct_Copy(NV_fb_t, &NV_fb, src); //No data checks - left to app
    }
    return ERR_OK;
}

// ------------- "Appl device id" NVRAM entry ----------------
EXTMEM static ApplDeviceId_t ApplDeviceId;
const ApplDeviceId_t ApplDeviceId_default =
{
    .data =
    {
        .manufacturer_id = RES_VAL_MANUFAC_ID,
        .device_type = RES_VAL_DEV_TYPE,
        .device_revision = RES_VAL_DEV_REV,
        .dd_revision = RES_VAL_DD_REV,
        .config_revision = DEV_CONFIG_REVISION,
    },
    .CheckWord = CRC_SEED, //don't care
};

const ApplDeviceId_t *eepshim_Get_ApplDeviceId(ApplDeviceId_t *dst)
{
    return STRUCT_GET(&ApplDeviceId, dst);
}
ErrorCode_t eepshim_Set_ApplDeviceId(const ApplDeviceId_t *src)
{
    if(src == NULL)
    {
        src = &ApplDeviceId_default;
    }
    Struct_Copy(ApplDeviceId_t, &ApplDeviceId, src); //No data checks - left to app
    return ERR_OK;
}



const eepmap_t eepmap[] =
{
    [EEP_APPL_BLK1] = {.nvid = NVRAMID_ApplDeviceId, .buffer = &ApplDeviceId,},

    [FBS_BLK_FB_LINK_CFG] = {.nvid = NVRAMID_nv_fb_link_cfg, .buffer = &nv_fb_link_cfg,},
    [FBS_BLK_TREND_CFG] = {.nvid = NVRAMID_nv_trend_cfg, .buffer = &nv_trend_cfg,},
    //not used [FBS_BLK_MVC_CFG] = {.nvid = NVRAMID_, .buffer = NULL,},

    //not used [FBS_BLK_STATE_CFG] = {.nvid = NVRAMID_, .buffer = NULL,},
    [FDC_BLK_BASE_CFG] = {.nvid = NVRAMID_nv_fdc_blk_base_cfg, .buffer = &nv_fdc_blk_base_cfg,},
    [FDC_BLK_DLL_BASE_CFG] = {.nvid = NVRAMID_nv_fdc_blk_dll_base_cfg, .buffer = &nv_fdc_blk_dll_base_cfg,},

    [FDC_BLK_VCR_CFG] = {.nvid = NVRAMID_nv_vcr_cfg, .buffer = &nv_vcr_cfg,},
    [FDC_BLK_SM_CFG] = {.nvid = NVRAMID_nv_fdc_blk_sm_cfg, .buffer = &nv_fdc_blk_sm_cfg,},
    [FDC_BLK_FB_START_CFG] = {.nvid = NVRAMID_nv_fb_start_cfg, .buffer = &nv_fb_start_cfg,},

    [FDC_BLK_DLL_LM_INFO_CFG] = {.nvid = NVRAMID_nv_fdc_blk_dll_lm_info_cfg, .buffer = &nv_fdc_blk_dll_lm_info_cfg,},
    [FDC_BLK_DLL_LM_DATA_CFG] = {.nvid = NVRAMID_nv_fdc_blk_dll_lm_data_cfg, .buffer = &nv_fdc_blk_dll_lm_data_cfg,},
    [FDC_BLK_LAS_CFG] = {.nvid = NVRAMID_nv_las_cfg, .buffer = &nv_las_cfg,},

    [SWDL_BLK_DWNLD_CFG] = {.nvid = NVRAMID_nv_swdl_blk_dwnld_cfg, .buffer = &nv_swdl_blk_dwnld_cfg,},

    [EEP_NV_BLK1] = {.nvid = NVRAMID_NV_fb, .buffer = &NV_fb,},
    [EEP_NV_BLK2] = {.nvid = NVRAMID_NV_fb, .buffer = &NV_fb,},
    /* EXPLANATION: No need to double-store NV_fb *twice*. By mapping two Softing blocks
    to one NVRAM image we eliminate this duplication.
    */

    [EEP_FBL_BLK1] = {.nvid = NVRAMID_ST_resb + 0, .buffer = &ST_resb[0],},
    [EEP_FBL_BLK2] = {.nvid = NVRAMID_ST_aifb + 0, .buffer = &ST_aifb[0],},
    [EEP_FBL_BLK3] = {.nvid = NVRAMID_ST_aifb + 1, .buffer = &ST_aifb[1],},
    [EEP_FBL_BLK4] = {.nvid = NVRAMID_ST_aifb + 2, .buffer = &ST_aifb[2],},
    [EEP_FBL_BLK5] = {.nvid = NVRAMID_ST_aofb + 0, .buffer = &ST_aofb[0],},
    [EEP_FBL_BLK6] = {.nvid = NVRAMID_ST_difb + 0, .buffer = &ST_difb[0],},
    [EEP_FBL_BLK7] = {.nvid = NVRAMID_ST_difb + 1, .buffer = &ST_difb[1],},
    [EEP_FBL_BLK8] = {.nvid = NVRAMID_ST_dofb + 0, .buffer = &ST_dofb[0],},
    [EEP_FBL_BLK9] = {.nvid = NVRAMID_ST_dofb + 1, .buffer = &ST_dofb[1],},
    [EEP_FBL_BLK10] = {.nvid = NVRAMID_ST_maifb + 0, .buffer = &ST_maifb[0],},
    [EEP_FBL_BLK11] = {.nvid = NVRAMID_ST_pidfb + 0, .buffer = &ST_pidfb[0],},
    [EEP_FBL_BLK12] = {.nvid = NVRAMID_ST_pidfb + 1, .buffer = &ST_pidfb[1],},
    [EEP_FBL_BLK13] = {.nvid = NVRAMID_ST_isfb + 0, .buffer = &ST_isfb[0],},
    [EEP_FBL_BLK14] = {.nvid = NVRAMID_ST_osfb + 0, .buffer = &ST_osfb[0],},
    [EEP_FBL_BLK15] = {.nvid = NVRAMID_ST_ptb + 0, .buffer = &ST_ptb[0],},
    [EEP_FBL_BLK16] = {.nvid = NVRAMID_ST_csfb + 0, .buffer = &ST_csfb[0],},
    [EEP_FBL_BLK17] = {.nvid = NVRAMID_ST_arfb + 0, .buffer = &ST_arfb[0],},
};

const u8 eepmap_size = NELEM(eepmap);
