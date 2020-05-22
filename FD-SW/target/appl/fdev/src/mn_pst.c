/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_pst.c
    \brief Support of Partial Stroke Test (front end)

    CPU: Any

    OWNER: AK
*/
#include "mnwrap.h"
#include "hmsndrcv5.h"
#include "bufutils.h"
#include "timebase.h"
#include "ptbcustomsubx.h"
#include "mn_diagnostic_configuration.h"

//Sanity check
#include "pstshell.h"
#include "pst.h"
CONST_ASSERT((s32)PSTUI_RUN_LO_BIT==(s32)PST_RUN_SETUP);
CONST_ASSERT((s32)PSTUI_RUN_AUTO_MAN_BIT==(s32)PST_RUN_AUTO_MAN);
CONST_ASSERT((s32)PSTUI_CONFIG_BIT==(s32)PST_CONFIG);
CONST_ASSERT((s32)PSTUI_VIEW_CONFIG_BIT==(s32)PST_VIEW_CONFIG);
CONST_ASSERT((s32)PST_PATTERN_DPU==(s32)PST_PATTERN_DU);
CONST_ASSERT((s32)PST_PATTERN_DPUPD==(s32)PST_PATTERN_DUD);
CONST_ASSERT((s32)PST_PATTERN_DPUuPDdPU==(s32)PST_PATTERN_DUDU);
CONST_ASSERT((s32)PST_PATTERN_UPD==(s32)PST_PATTERN_UD);
CONST_ASSERT((s32)PST_PATTERN_UPDPU==(s32)PST_PATTERN_UDU);
CONST_ASSERT((s32)PST_PATTERN_UPDdPUuPD==(s32)PST_PATTERN_UDUD);

static void populate_PST_CONFIG(_PST_CONFIG *pconf, const HPSTConfiguration_t *hc)
{
    pconf->setpoint_change_threshold = util_GetFloat(hc->PSTsetpointChangeThreshold[0]);
    pconf->pst_travel = util_GetFloat(hc->PSTtravel[0]);
    u32 maxtime = util_GetU32(hc->PSTMaxTime[0])/ONE_SECOND;
    pconf->pst_maxtime = (u16)MIN(maxtime, UINT16_MAX); //am I sure I want this?
    pconf->pst_setpoint_rate = util_GetFloat(hc->PSTSetpointRate[0]);
    pconf->pst_leadtime = util_GetU16(hc->PSTLeadTime[0]);
    pconf->pilot_threshold = util_GetFloat(hc->PSTPilotPressureThreshold[0]);
    pconf->actuator_threshold = util_GetFloat(hc->PSTActuatorPressureThreshold[0]);
    pconf->pst_pause = util_GetU16(hc->PSTDwellTime[0]);
    pconf->stroke_timeout_override = util_GetU32(hc->PSTStrokeTimeout[0]);
    pconf->pst_datamap = util_GetU16(hc->PSTdatamap[0]);
    pconf->pst_skip_count = util_GetU16(hc->PSTSkipCount[0]);
    pconf->pst_freeze_options = util_GetU16(hc->PSTFreezeOptions[0]);
    pconf->pst_pattern = util_GetU8(hc->PSTpattern[0]);
}

fferr_t ffdc_ReadPstConfig(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to
 )
{
    UNUSED_OK(p_block_instance);
    Req_ReadPartialStrokeTestConfiguration_t *req = from;
    Rsp_ReadPartialStrokeTestConfiguration_t *rsp = to;
    fferr_t fferr = hmsndrcv5_ReadPartialStrokeTestConfiguration(req, rsp);
    if(fferr == E_OK)
    {
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        _PST_CONFIG *pconf = &p_PTB->pst_config;
        HPSTConfiguration_t *hc = (void *)rsp->HPSTConfiguration[0];
        populate_PST_CONFIG(pconf, hc);
    }
    return fferr;
}

fferr_t ffdc_WritePstConfig(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to)
{
    //First of all, make sure TB parameter is populated correctly; does no harm
    fferr_t fferr = ffdc_ReadPstConfig(p_block_instance, from, to);
    _PST_CONFIG conf;

    if(fferr == E_OK)
    {
        u8 subindex = p_write->subindex;
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        //lint -esym(644, conf) may not have been initialized - lint sometimes overlooks if/else pattern
        if(subindex == 0)
        {
            conf = *(const _PST_CONFIG *)(const void *)p_write->source;
        }
        else
        {
            conf = p_PTB->pst_config;
            switch(subindex)
            {
                case PTB_SUBX_PST_CONFIG___setpoint_change_threshold:
                    conf.setpoint_change_threshold = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_travel:
                    conf.pst_travel = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_maxtime:
                    conf.pst_maxtime = mn_pull_u16(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_setpoint_rate:
                    conf.pst_setpoint_rate = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_leadtime:
                    conf.pst_leadtime = mn_pull_u16(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pilot_threshold:
                    conf.pilot_threshold = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___actuator_threshold:
                    conf.actuator_threshold = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___stroke_timeout_override:
                    conf.stroke_timeout_override = mn_pull_u32(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_datamap:
                    conf.pst_datamap = mn_pull_u16(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_skip_count:
                    conf.pst_skip_count = mn_pull_u16(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_freeze_options:
                    conf.pst_freeze_options = mn_pull_u16(p_write->source);
                    break;
                case PTB_SUBX_PST_CONFIG___pst_pattern:
                    conf.pst_pattern = *p_write->source;
                    break;
                default:
                    fferr = E_FB_PARA_CHECK;
                    break;
            }
        }
    }

    if(fferr == E_OK)
    {
        //Populate the HART buffer
        Req_WritePartialStrokeTestConfiguration_t *req = from;
        HPSTConfiguration_t *hc = (void *)req->HPSTConfiguration[0];
        util_PutFloat(hc->PSTsetpointChangeThreshold[0], conf.setpoint_change_threshold);
        util_PutFloat(hc->PSTtravel[0], conf.pst_travel);
        util_PutU32(hc->PSTMaxTime[0], conf.pst_maxtime*ONE_SECOND);
        util_PutFloat(hc->PSTSetpointRate[0], conf.pst_setpoint_rate);
        util_PutU16(hc->PSTLeadTime[0], conf.pst_leadtime);
        util_PutFloat(hc->PSTPilotPressureThreshold[0], conf.pilot_threshold);
        util_PutFloat(hc->PSTActuatorPressureThreshold[0], conf.actuator_threshold);
        util_PutU16(hc->PSTDwellTime[0], conf.pst_pause);
        util_PutU32(hc->PSTStrokeTimeout[0], conf.stroke_timeout_override);
        util_PutU16(hc->PSTdatamap[0], conf.pst_datamap);
        util_PutU16(hc->PSTSkipCount[0], conf.pst_skip_count);
        util_PutU16(hc->PSTFreezeOptions[0], conf.pst_freeze_options);
        util_PutU8(hc->PSTpattern[0], conf.pst_pattern);
        fferr = hmsndrcv5_WritePartialStrokeTestConfiguration(req, to);
    }

    return fferr;
}

//--------------------- pst trigger --------------------
static void populate_PST_TRIGGER(_PST_TRIGGER *pconf, const Rsp_ReadPartialStrokeTestStartConfig_t *hc)
{
    pconf->PST_Trigger_On_Demand = util_GetU8(hc->DataCollectionTriggerByHART[0]);
    pconf->PST_Trigger_by_UI = util_GetU8(hc->PSTTriggerByUI[0]);
    pconf->PST_Trigger_By_DI_Switch = util_GetU8(hc->DataCollectionTriggerByDISwitch[0]);
    pconf->PST_Trigger_By_AI_Input = util_GetU8(hc->DataCollectionTriggerByAIInput[0]);
    pconf->PST_AI_Trigger_Input_Threshold = util_GetFloat(hc->DataCollectionTriggerAIInputThreshold[0]);
}


fferr_t ffdc_ReadPstTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to
 )
{
    UNUSED_OK(p_block_instance);
    Req_ReadPartialStrokeTestStartConfig_t *req = from;
    Rsp_ReadPartialStrokeTestStartConfig_t *rsp = to;
    fferr_t fferr = hmsndrcv5_ReadPartialStrokeTestStartConfig(req, rsp);
    if(fferr == E_OK)
    {
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        _PST_TRIGGER *pconf = &p_PTB->pst_trigger;
        populate_PST_TRIGGER(pconf, rsp);
    }
    return fferr;
}

fferr_t ffdc_WritePstTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to)
{
    //First of all, make sure TB parameter is populated correctly; does no harm
    fferr_t fferr = ffdc_ReadPstTrigger(p_block_instance, from, to);
    _PST_TRIGGER conf;

    if(fferr == E_OK)
    {
        u8 subindex = p_write->subindex;
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        //lint -esym(644, conf) may not have been initialized - lint sometimes overlooks if/else pattern
        if(subindex == 0)
        {
            conf = *(const _PST_TRIGGER *)(const void *)p_write->source;
        }
        else
        {
            conf = p_PTB->pst_trigger;
            switch(subindex)
            {
                case PTB_SUBX_PST_TRIGGER___PST_Trigger_On_Demand:
                    conf.PST_Trigger_On_Demand = p_write->source[0];
                    break;
                case PTB_SUBX_PST_TRIGGER___PST_Trigger_by_UI:
                    conf.PST_Trigger_by_UI = p_write->source[0];
                    break;
                case PTB_SUBX_PST_TRIGGER___PST_Trigger_By_DI_Switch:
                    conf.PST_Trigger_By_DI_Switch = p_write->source[0];
                    break;
                case PTB_SUBX_PST_TRIGGER___PST_Trigger_By_AI_Input:
                    conf.PST_Trigger_By_AI_Input = p_write->source[0];
                    break;
                case PTB_SUBX_PST_TRIGGER___PST_AI_Trigger_Input_Threshold:
                    conf.PST_AI_Trigger_Input_Threshold = mn_pull_float(p_write->source);
                    break;
                default:
                    fferr = E_FB_PARA_CHECK;
                    break;
            }
        }
    }

    if(fferr == E_OK)
    {
        //Populate the HART buffer
        Req_WritePartialStrokeTestStartConfig_t *req = from;
        util_PutFloat(req->DataCollectionTriggerAIInputThreshold[0], conf.PST_AI_Trigger_Input_Threshold);
        util_PutU8(req->DataCollectionTriggerByAIInput[0], conf.PST_Trigger_By_AI_Input);
        util_PutU8(req->DataCollectionTriggerByDISwitch[0], conf.PST_Trigger_By_DI_Switch);
        util_PutU8(req->PSTTriggerByUI[0], conf.PST_Trigger_by_UI);
        util_PutU8(req->DataCollectionTriggerByHART[0], conf.PST_Trigger_On_Demand);
        fferr = hmsndrcv5_WritePartialStrokeTestStartConfig(req, to);
    }
    return fferr;
}

//--------------------- data collection trigger --------------------

/* This is a good place to assert that APP and FFP have the same notion of
binary option bits
*/
CONST_ASSERT((s32)TrigManual_BIT == (s32)DhogBO_Extrn);
CONST_ASSERT((s32)TrigAlerts_BIT == (s32)DhogBO_TBAlerts);
CONST_ASSERT((s32)TrigPosDev_BIT == (s32)DhogBO_PosDeviation);
CONST_ASSERT((s32)TrigPresDev_BIT == (s32)DhogBO_PresDeviation);
CONST_ASSERT((s32)TrigSPDev_BIT == (s32)DhogBO_SpDeviation);
CONST_ASSERT((s32)TrigDIOpen_BIT == (s32)DhogBO_DiOpen);
CONST_ASSERT((s32)TrigDIClosed_BIT == (s32)DhogBO_DiClosed);
CONST_ASSERT((s32)TrigAIBelow_BIT == (s32)DhogBO_PvBelow);
CONST_ASSERT((s32)TrigAIAbove_BIT == (s32)DhogBO_PvAbove);
CONST_ASSERT((s32)TrigAIBetween_BIT == (s32)DhogBO_PvBetween);

static void populate_DATA_COLLECTION_TRIGGER(_DATA_COLLECTION_TRIGGER *pconf, const Rsp_ReadDataCollectionTriggerConfiguration_t *hc)
{
    pconf->TriggerEnabled = util_GetU8(hc->DataCollectionTriggerBinaryOptions[0]);
    pconf->AI_Trigger_ThresholdLow = util_GetFloat(hc->DataCollectionTriggerAIInputThreshold[Xlow]);
    pconf->AI_Trigger_ThresholdHigh = util_GetFloat(hc->DataCollectionTriggerAIInputThreshold[Xhi]);
    pconf->Setpont_Threshold = util_GetFloat(hc->DataCollectionSetpointDeviationThreshold[0]);
    pconf->Position_Threshold = util_GetFloat(hc->DataCollectionPositionDeviationThreshold[0]);
    pconf->Pressure_Threshold = util_GetFloat(hc->DataCollectionPressureDeviationThreshold[0]);
    pconf->FilterCoef = util_GetU8(hc->DataCollectionFilterCoef[0]);
}


fferr_t ffdc_ReadDataCollectionTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to
 )
{
    UNUSED_OK(p_block_instance);
    Req_ReadDataCollectionTriggerConfiguration_t *req = from;
    Rsp_ReadDataCollectionTriggerConfiguration_t *rsp = to;
    fferr_t fferr = hmsndrcv5_ReadDataCollectionTriggerConfiguration(req, rsp);
    if(fferr == E_OK)
    {
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        _DATA_COLLECTION_TRIGGER *pconf = &p_PTB->data_collection_trigger;
        populate_DATA_COLLECTION_TRIGGER(pconf, rsp);
    }
    return fferr;
}

fferr_t ffdc_WriteDataCollectionTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to)
{
    //First of all, make sure TB parameter is populated correctly; does no harm
    fferr_t fferr = ffdc_ReadDataCollectionTrigger(p_block_instance, from, to);
    _DATA_COLLECTION_TRIGGER conf;

    if(fferr == E_OK)
    {
        u8 subindex = p_write->subindex;
        T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
        //lint -esym(644, conf) may not have been initialized - lint sometimes overlooks if/else pattern
        if(subindex == 0)
        {
            conf = *(const _DATA_COLLECTION_TRIGGER *)(const void *)p_write->source;
        }
        else
        {
            conf = p_PTB->data_collection_trigger;
            switch(subindex)
            {
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___TriggerEnabled:
                    conf.TriggerEnabled = mn_pull_u16(p_write->source);
                    break;
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___FilterCoef:
                    conf.FilterCoef = p_write->source[0];
                    break;
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___AI_Trigger_ThresholdLow:
                    conf.AI_Trigger_ThresholdLow = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___AI_Trigger_ThresholdHigh:
                    conf.AI_Trigger_ThresholdHigh = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___Position_Threshold:
                    conf.Position_Threshold = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___Pressure_Threshold:
                    conf.Pressure_Threshold = mn_pull_float(p_write->source);
                    break;
                case PTB_SUBX_DATA_COLLECTION_TRIGGER___Setpont_Threshold:
                    conf.Setpont_Threshold = mn_pull_float(p_write->source);
                    break;
                default:
                    fferr = E_FB_PARA_CHECK;
                    break;
            }
        }
    }

    if(fferr == E_OK)
    {
        //Populate the HART buffer
        Req_WriteDataCollectionTriggerConfiguration_t *req = from;
        util_PutFloat(req->DataCollectionTriggerAIInputThreshold[Xlow], conf.AI_Trigger_ThresholdLow);
        util_PutFloat(req->DataCollectionTriggerAIInputThreshold[Xhi], conf.AI_Trigger_ThresholdHigh);
        util_PutFloat(req->DataCollectionPositionDeviationThreshold[0], conf.Position_Threshold);
        util_PutFloat(req->DataCollectionPressureDeviationThreshold[0], conf.Pressure_Threshold);
        util_PutFloat(req->DataCollectionSetpointDeviationThreshold[0], conf.Setpont_Threshold);
        util_PutU16(req->DataCollectionTriggerBinaryOptions[0], conf.TriggerEnabled);
        util_PutU8(req->DataCollectionFilterCoef[0], conf.FilterCoef);
        fferr = hmsndrcv5_WriteDataCollectionTriggerConfiguration(req, to);
    }
    return fferr;
}

//--------------------- data collection configuration --------------------
//permanent config
static fferr_t ffdc_ReadDataCollectionConfigP_local(_DATA_CONFIG_PERM *dst,
                            void* from,
                            void* to
 )
{
    Req_ReadDataCollectionConfiguration_t *req = from;

    util_PutU8( req->DataCollectionConfSelector[0], DCCPersistent);
    Rsp_ReadDataCollectionConfiguration_t *rsp = to;
    fferr_t fferr = hmsndrcv5_ReadDataCollectionConfiguration(req, rsp);
    if(fferr == E_OK)
    {
        dst->DataCollectBase = util_GetU8(rsp->DataCollectionContext[0]);
        dst->DataCollectBitmap = util_GetU16(rsp->DataCollectionBitmap[0]);
        dst->DataCollectMaxPreSamples = util_GetU16(rsp->DataCollectionMaxPreSamples[0]);
        dst->DataCollectMaxSamples = util_GetU16(rsp->DataCollectionMaxSamples[0]);
        dst->DataCollectSkipCount = util_GetU16(rsp->DataCollectionSkipCount[0]);
    }
    return fferr;
}
fferr_t ffdc_ReadDataCollectionConfigP(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to
 )
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    return ffdc_ReadDataCollectionConfigP_local(&p_PTB->data_config_perm, from, to);
}

//temporary config - read
static fferr_t ffdc_ReadDataCollectionConfigT_local(_DATA_CONFIG_TEMP *dst,
                            void* from,
                            void* to
 )
{
    Req_ReadDataCollectionConfiguration_t *req = from;

    util_PutU8( req->DataCollectionConfSelector[0], DCCCurrent);
    Rsp_ReadDataCollectionConfiguration_t *rsp = to;
    fferr_t fferr = hmsndrcv5_ReadDataCollectionConfiguration(req, rsp);
    if(fferr == E_OK)
    {
        dst->DataCollectBase = util_GetU8(rsp->DataCollectionContext[0]);
        dst->DataCollectBitmap = util_GetU16(rsp->DataCollectionBitmap[0]);
        dst->DataCollectMaxSamples = util_GetU16(rsp->DataCollectionMaxSamples[0]);
        dst->DataCollectSkipCount = util_GetU16(rsp->DataCollectionSkipCount[0]);
    }
    return fferr;
}
fferr_t ffdc_ReadDataCollectionConfigT(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to
 )
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    return ffdc_ReadDataCollectionConfigT_local(&p_PTB->data_config_temp, from, to);
}

//permanent
fferr_t ffdc_WriteDataCollectionConfigP(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    _DATA_CONFIG_PERM conf;

    u8 subindex = p_write->subindex;
    fferr_t fferr = E_OK;
    //lint -esym(644, conf) may not have been initialized - lint sometimes overlooks if/else pattern
    if(subindex == 0)
    {
        conf = *(const _DATA_CONFIG_PERM *)(const void *)p_write->source;
    }
    else
    {
        fferr = ffdc_ReadDataCollectionConfigP_local(&conf, from, to);
        switch(subindex)
        {
            case PTB_SUBX_DATA_CONFIG_PERM___DataCollectBase:
                conf.DataCollectBase = p_write->source[0];
                break;
            case PTB_SUBX_DATA_CONFIG_PERM___DataCollectSkipCount:
                conf.DataCollectSkipCount = mn_pull_u16(p_write->source);
                break;
            case PTB_SUBX_DATA_CONFIG_PERM___DataCollectBitmap:
                conf.DataCollectBitmap = mn_pull_u16(p_write->source);
                break;
            case PTB_SUBX_DATA_CONFIG_PERM___DataCollectMaxSamples:
                conf.DataCollectMaxSamples = mn_pull_u16(p_write->source);
                break;
            case PTB_SUBX_DATA_CONFIG_PERM___DataCollectMaxPreSamples:
                conf.DataCollectMaxPreSamples = mn_pull_u16(p_write->source);
                break;
            default:
                fferr = E_FB_PARA_CHECK;
                break;
        }
    }

    if(fferr == E_OK)
    {
        //Populate the HART buffer
        Req_WriteDataCollectionConfiguration_t *req = from;
        util_PutU16(req->DataCollectionBitmap[0], conf.DataCollectBitmap);
        util_PutU16(req->DataCollectionMaxSamples[0], conf.DataCollectMaxSamples);
        util_PutU16(req->DataCollectionMaxPreSamples[0], conf.DataCollectMaxPreSamples);
        util_PutU16(req->DataCollectionSkipCount[0], conf.DataCollectSkipCount);
        util_PutU8(req->DataCollectionConfSelector[0], DCCPersistent);
        util_PutU8(req->DataCollectionContext[0], conf.DataCollectBase);
        fferr = hmsndrcv5_WriteDataCollectionConfiguration(req, to);
    }
    if(fferr == E_OK)
    {
        p_PTB->data_config_perm = conf;
    }

    return fferr;
}
//temporary config
fferr_t ffdc_WriteDataCollectionConfigT(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    _DATA_CONFIG_TEMP conf;

    u8 subindex = p_write->subindex;
    fferr_t fferr = E_OK;
    //lint -esym(644, conf) may not have been initialized - lint sometimes overlooks if/else pattern
    if(subindex == 0)
    {
        conf = *(const _DATA_CONFIG_TEMP *)(const void *)p_write->source;
    }
    else
    {
        fferr = ffdc_ReadDataCollectionConfigT_local(&conf, from, to);
        switch(subindex)
        {
            case PTB_SUBX_DATA_CONFIG_TEMP___DataCollectBase:
                conf.DataCollectBase = p_write->source[0];
                break;
            case PTB_SUBX_DATA_CONFIG_TEMP___DataCollectSkipCount:
                conf.DataCollectSkipCount = mn_pull_u16(p_write->source);
                break;
            case PTB_SUBX_DATA_CONFIG_TEMP___DataCollectBitmap:
                conf.DataCollectBitmap = mn_pull_u16(p_write->source);
                break;
            case PTB_SUBX_DATA_CONFIG_TEMP___DataCollectMaxSamples:
                conf.DataCollectMaxSamples = mn_pull_u16(p_write->source);
                break;
            default:
                fferr = E_FB_PARA_CHECK;
                break;
        }
    }

    if(fferr == E_OK)
    {
        //Populate the HART buffer
        Req_WriteDataCollectionConfiguration_t *req = from;
        util_PutU16(req->DataCollectionBitmap[0], conf.DataCollectBitmap);
        util_PutU16(req->DataCollectionMaxSamples[0], conf.DataCollectMaxSamples);
        util_PutU16(req->DataCollectionMaxPreSamples[0], 0); //any valid; will be ignored
        util_PutU16(req->DataCollectionSkipCount[0], conf.DataCollectSkipCount);
        util_PutU8(req->DataCollectionConfSelector[0], DCCCurrent);
        util_PutU8(req->DataCollectionContext[0], conf.DataCollectBase);
        fferr = hmsndrcv5_WriteDataCollectionConfiguration(req, to);
    }
    if(fferr == E_OK)
    {
        p_PTB->data_config_temp = conf;
    }

    return fferr;
}
