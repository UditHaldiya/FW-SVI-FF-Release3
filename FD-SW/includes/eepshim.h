/**
Copyright 2016 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file eepshim.h

    \brief Mapping between Softing eep model and MN NVRAM model of NV memory

    OWNER: AK
    CPU: Any

    \ingroup nvram
*/
#ifndef EEPSHIM_H_
#define EEPSHIM_H_
#include "errcodes.h"
#include "nvdimensions.h"
#include "havenv.h"
#include "eepshim_getset.h"
#include <keywords.h> //for Softing "keywords" annotations
#include <appl_int.h> //for T_APPL_DEVICE_ID

#include <fbap.h> //for common types needed for TB and FB
#include <spec_ds.h> //for common types needed for TB and FB
#if 0
#include <ptb.h> //for T_FBIF_PTB_STATIC, T_FBIF_PTB_NV
#include <aifb.h> //for T_FBIF_AIFB_STATIC, T_FBIF_AIFB_NV
#include <aofb.h> //for T_FBIF_AOFB_STATIC, T_FBIF_AOFB_NV
#include <arfb.h> //for T_FBIF_ARFB_STATIC, T_FBIF_ARFB_NV
#include <csfb.h> //for T_FBIF_CSFB_STATIC, T_FBIF_CSFB_NV
#include <difb.h> //for T_FBIF_DIFB_STATIC, T_FBIF_DIFB_NV
#include <dofb.h> //for T_FBIF_DOFB_STATIC, T_FBIF_DOFB_NV
#include <isfb.h> //for T_FBIF_ISFB_STATIC, T_FBIF_ISFB_NV
#include <maifb.h> //for T_FBIF_MAIFB_STATIC, T_FBIF_MAIFB_NV
#include <osfb.h> //for T_FBIF_OSFB_STATIC, T_FBIF_OSFB_NV
#include <pidfb.h> //for T_FBIF_PIDFB_STATIC, T_FBIF_PIDFB_NV
#include <resb.h> //for T_FBIF_RESB_STATIC, T_FBIF_RES_NV
#endif
/*Unreliable part - what's gleaned from Softing ACTUAL NV consumption
If after Softing update the initialization fails, these numbers must be updated
Some may be discovered from `T_FBIF_DICTIONARY fbif_dictionary`
*/
#define NVSIZE_FB_LINK_CFG 440
#define NVSIZE_TREND_CFG 288
#define NVSIZE_VCR_CFG 1304
#define NVSIZE_FB_START_CFG 328
#define NVSIZE_LAS_CFG 1140

#define NVSIZE_FDC_BLK_BASE_CFG 4
#define NVSIZE_FDC_BLK_DLL_BASE_CFG 14
#define NVSIZE_FDC_BLK_SM_CFG 44
#define NVSIZE_FDC_BLK_DLL_LM_INFO_CFG 16
#define NVSIZE_FDC_BLK_DLL_LM_DATA_CFG 2
#define NVSIZE_SWDL_BLK_DWNLD_CFG 4

typedef struct nv_fdc_blk_base_cfg_t
{
    u8 data[NVSIZE_FDC_BLK_BASE_CFG];
    u16 CheckWord;
} nv_fdc_blk_base_cfg_t;

typedef struct nv_fdc_blk_dll_base_cfg_t
{
    u8 data[NVSIZE_FDC_BLK_DLL_BASE_CFG];
    u16 CheckWord;
} nv_fdc_blk_dll_base_cfg_t;

typedef struct nv_fdc_blk_sm_cfg_t
{
    u8 data[NVSIZE_FDC_BLK_SM_CFG];
    u16 CheckWord;
} nv_fdc_blk_sm_cfg_t;

typedef struct nv_fdc_blk_dll_lm_info_cfg_t
{
    u8 data[NVSIZE_FDC_BLK_DLL_LM_INFO_CFG];
    u16 CheckWord;
} nv_fdc_blk_dll_lm_info_cfg_t;

typedef struct nv_fdc_blk_dll_lm_data_cfg_t
{
    u8 data[NVSIZE_FDC_BLK_DLL_LM_DATA_CFG];
    u16 CheckWord;
} nv_fdc_blk_dll_lm_data_cfg_t;

typedef struct nv_swdl_blk_dwnld_cfg_t
{
    u8 data[NVSIZE_SWDL_BLK_DWNLD_CFG];
    u16 CheckWord;
} nv_swdl_blk_dwnld_cfg_t;

extern const nv_fdc_blk_base_cfg_t *eepshim_Get_nv_fdc_blk_base_cfg(nv_fdc_blk_base_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fdc_blk_base_cfg(const nv_fdc_blk_base_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fdc_blk_base_cfg, eepshim_Get_nv_fdc_blk_base_cfg);

extern const nv_fdc_blk_dll_base_cfg_t *eepshim_Get_nv_fdc_blk_dll_base_cfg(nv_fdc_blk_dll_base_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fdc_blk_dll_base_cfg(const nv_fdc_blk_dll_base_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fdc_blk_dll_base_cfg, eepshim_Get_nv_fdc_blk_dll_base_cfg);

extern const nv_fdc_blk_sm_cfg_t *eepshim_Get_nv_fdc_blk_sm_cfg(nv_fdc_blk_sm_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fdc_blk_sm_cfg(const nv_fdc_blk_sm_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fdc_blk_sm_cfg, eepshim_Get_nv_fdc_blk_sm_cfg);

extern const nv_fdc_blk_dll_lm_info_cfg_t *eepshim_Get_nv_fdc_blk_dll_lm_info_cfg(nv_fdc_blk_dll_lm_info_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fdc_blk_dll_lm_info_cfg(const nv_fdc_blk_dll_lm_info_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fdc_blk_dll_lm_info_cfg, eepshim_Get_nv_fdc_blk_dll_lm_info_cfg);

extern const nv_fdc_blk_dll_lm_data_cfg_t *eepshim_Get_nv_fdc_blk_dll_lm_data_cfg(nv_fdc_blk_dll_lm_data_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fdc_blk_dll_lm_data_cfg(const nv_fdc_blk_dll_lm_data_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fdc_blk_dll_lm_data_cfg, eepshim_Get_nv_fdc_blk_dll_lm_data_cfg);

extern const nv_swdl_blk_dwnld_cfg_t *eepshim_Get_nv_swdl_blk_dwnld_cfg(nv_swdl_blk_dwnld_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_swdl_blk_dwnld_cfg(const nv_swdl_blk_dwnld_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_swdl_blk_dwnld_cfg, eepshim_Get_nv_swdl_blk_dwnld_cfg);


//--
typedef struct nv_fb_link_cfg_t
{
    u8 data[NVSIZE_FB_LINK_CFG];
    u16 CheckWord;
} nv_fb_link_cfg_t;

typedef struct nv_trend_cfg_t
{
    u8 data[NVSIZE_TREND_CFG];
    u16 CheckWord;
} nv_trend_cfg_t;

typedef struct nv_vcr_cfg_t
{
    u8 data[NVSIZE_VCR_CFG];
    u16 CheckWord;
} nv_vcr_cfg_t;

typedef struct nv_fb_start_cfg_t
{
    u8 data[NVSIZE_FB_START_CFG];
    u16 CheckWord;
} nv_fb_start_cfg_t;

typedef struct nv_las_cfg_t
{
    u8 data[NVSIZE_LAS_CFG];
    u16 CheckWord;
} nv_las_cfg_t;

extern const nv_fb_link_cfg_t *eepshim_Get_nv_fb_link_cfg(nv_fb_link_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fb_link_cfg(const nv_fb_link_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fb_link_cfg, eepshim_Get_nv_fb_link_cfg);

extern const nv_trend_cfg_t *eepshim_Get_nv_trend_cfg(nv_trend_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_trend_cfg(const nv_trend_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_trend_cfg, eepshim_Get_nv_trend_cfg);

extern const nv_vcr_cfg_t *eepshim_Get_nv_vcr_cfg(nv_vcr_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_vcr_cfg(const nv_vcr_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_vcr_cfg, eepshim_Get_nv_vcr_cfg);


typedef struct NV_fb_start_cfg_elem_t
{
    u8 sort_idx[4];  //4
    u32 start;       //8
    u16 fb_od_id[2]; //12
    u32 vfd_ref;     //16
    u32 delta;       //20
} NV_fb_start_cfg_elem_t;

typedef struct NV_fb_start_cfg_t
{
    u16 sched_vers[2];
    NV_fb_start_cfg_elem_t data[16]; //16*20=320
    u32 macrocycle;
    u16 CheckWord;
} NV_fb_start_cfg_t;

CONST_ASSERT(MN_OFFSETOF(NV_fb_start_cfg_t, CheckWord) == MN_OFFSETOF(nv_fb_start_cfg_t, CheckWord));

extern const NV_fb_start_cfg_t *eepshim_Get_nv_fb_start_cfg(NV_fb_start_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_fb_start_cfg(const NV_fb_start_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_fb_start_cfg, eepshim_Get_nv_fb_start_cfg);

extern const nv_las_cfg_t *eepshim_Get_nv_las_cfg(nv_las_cfg_t *dst);
extern ErrorCode_t eepshim_Set_nv_las_cfg(const nv_las_cfg_t *src);
UNTYPEACC(eepshim_Set_nv_las_cfg, eepshim_Get_nv_las_cfg);

// ----------- Known types -----------------
typedef struct ApplDeviceId_t
{
    T_APPL_DEVICE_ID data;
    u16 CheckWord;
} ApplDeviceId_t;

extern const ApplDeviceId_t *eepshim_Get_ApplDeviceId(ApplDeviceId_t *dst);
extern ErrorCode_t eepshim_Set_ApplDeviceId(const ApplDeviceId_t *src);
UNTYPEACC(eepshim_Set_ApplDeviceId, eepshim_Get_ApplDeviceId);

//-------- function blocks (could be automated) ---------------
extern void blk_data_Repair(F_BLOCK *dst, const F_BLOCK *src, const F_BLOCK *fw_default);

#if 0
typedef struct ST_ptb_t
{
    T_FBIF_PTB_STATIC data;
    u16 CheckWord;
} ST_ptb_t;

typedef struct ST_aifb_t
{
    T_FBIF_AIFB_STATIC data;
    u16 CheckWord;
} ST_aifb_t;

typedef struct ST_aofb_t
{
    T_FBIF_AOFB_STATIC data;
    u16 CheckWord;
} ST_aofb_t;

typedef struct ST_arfb_t
{
    T_FBIF_ARFB_STATIC data;
    u16 CheckWord;
} ST_arfb_t;

typedef struct ST_csfb_t
{
    T_FBIF_CSFB_STATIC data;
    u16 CheckWord;
} ST_csfb_t;

typedef struct ST_difb_t
{
    T_FBIF_DIFB_STATIC data;
    u16 CheckWord;
} ST_difb_t;

typedef struct ST_dofb_t
{
    T_FBIF_DOFB_STATIC data;
    u16 CheckWord;
} ST_dofb_t;

typedef struct ST_isfb_t
{
    T_FBIF_ISFB_STATIC data;
    u16 CheckWord;
} ST_isfb_t;

typedef struct ST_maifb_t
{
    T_FBIF_MAIFB_STATIC data;
    u16 CheckWord;
} ST_maifb_t;

typedef struct ST_osfb_t
{
    T_FBIF_OSFB_STATIC data;
    u16 CheckWord;
} ST_osfb_t;

typedef struct ST_pidfb_t
{
    T_FBIF_PIDFB_STATIC data;
    u16 CheckWord;
} ST_pidfb_t;

typedef struct ST_resbfb_t
{
    T_FBIF_RESB_STATIC data;
    u16 CheckWord;
} ST_resb_t;
#endif
typedef struct NV_fb_t
{
#ifdef HAVE_NV_AIFB
    T_FBIF_AIFB_NV aifb[3]; //1 2 3
#endif
#ifdef HAVE_NV_AOFB
    T_FBIF_AOFB_NV aofb[1]; //4
#endif
#ifdef HAVE_NV_DIFB
    T_FBIF_DIFB_NV difb[2]; //5 6
#endif
#ifdef HAVE_NV_DOFB
    T_FBIF_DOFB_NV dofb[2]; //7 8
#endif
#ifdef HAVE_NV_MAIFB
    T_FBIF_MAIFB_NV maifb[1]; //9
#endif
#ifdef HAVE_NV_PIDFB
    T_FBIF_PIDFB_NV pidfb[2]; //10 11
#endif
#ifdef HAVE_NV_ISFB
    T_FBIF_ISFB_NV isfb[1]; //12
#endif
#ifdef HAVE_NV_OSFB
    T_FBIF_OSFB_NV osfb[1]; //13
#endif
#ifdef HAVE_NV_PTB
    T_FBIF_PTB_NV ptb[1]; //14
#endif
#ifdef HAVE_NV_CSFB
    T_FBIF_CSFB_NV csfb[1]; //15
#endif
#ifdef HAVE_NV_ARFB
    T_FBIF_ARFB_NV arfb[1]; //16
#endif
    u16 CheckWord;
} NV_fb_t;

#if 0
#define NVRAMSTUBH(block_name) \
extern const ST_## block_name ##_t *eepshim_Get## block_name ##StaticData(u8_least index, ST_## block_name ##_t *dst); \
extern ErrorCode_t eepshim_Set## block_name ##StaticData(u8_least index, const ST_## block_name ##_t *src); \
UNTYPEACCX(eepshim_Set## block_name ##StaticData, eepshim_Get## block_name ##StaticData)

NVRAMSTUBH(resb);
NVRAMSTUBH(aifb);
NVRAMSTUBH(aofb);
NVRAMSTUBH(difb);
NVRAMSTUBH(dofb);
NVRAMSTUBH(maifb);
NVRAMSTUBH(pidfb);
NVRAMSTUBH(isfb);
NVRAMSTUBH(osfb);
NVRAMSTUBH(ptb);
NVRAMSTUBH(csfb);
NVRAMSTUBH(arfb);
#endif //0

extern const NV_fb_t *eepshim_Get_NV_fb(NV_fb_t *dst);
extern ErrorCode_t eepshim_Set_NV_fb(const NV_fb_t *src);
UNTYPEACC(eepshim_Set_NV_fb, eepshim_Get_NV_fb);

#define EEP_INIT_VALUE      ASCII_q         /* EEP RAM image value after init   */

#endif //EEPSHIM_H_
/* This line marks the end of the source */
