/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_dhogtrigger.c
    \brief HART glue layer for data collection trigger

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "dhogtrigger.h"
#include "hartdef5.h"
#include "bufutils.h"
#include "hartfunc.h"
#include "fpconvert.h"

static const DatahogStatus_t cmd_tab[] =
{
    [HC_StartCollecting] = DatahogStart,
    [HC_StopCollecting] = DatahogStop,
};

s8_least hartcmd_ControlDataCollection(const u8 *src, u8 *dst)
{
    const Req_ControlDataCollection_t *s = (const void *)src;
    UNUSED_OK(dst);
    DatahogConfId_t selector = util_GetU8(s->DataCollectionConfSelector[0]);
    u8 cmd = util_GetU8(s->DataCollectionCommand[0]);
    ErrorCode_t err = ERR_OK;
    if(cmd >= NELEM(cmd_tab))
    {
        err = ERR_INVALID_PARAMETER;
    }
    else
    {
        err = datahog_TriggerComm(selector, cmd_tab[cmd]);
    }
    return err2hart(err);
}


s8_least hartcmd_ReadDataCollectionTriggerConfiguration(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadDataCollectionTriggerConfiguration_t *d = (void *)dst;
    DhogTriggerConf_t conf;
    (void)datahog_GetTriggerConf(&conf);
    //populate the response buffer
    util_PutU8(d->DataCollectionFilterCoef[0], conf.FilterConf.Shift);
    util_PutU16(d->DataCollectionTriggerBinaryOptions[0], conf.BinaryOptions);
    (void)fpconvert_IntToFloatBuffer(conf.pvthreshold[Xlow], UNITSID_SIGNAL_ENTRY, d->DataCollectionTriggerAIInputThreshold[Xlow]);
    (void)fpconvert_IntToFloatBuffer(conf.pvthreshold[Xhi], UNITSID_SIGNAL_ENTRY, d->DataCollectionTriggerAIInputThreshold[Xhi]);
    (void)fpconvert_IntToFloatBuffer(conf.DeviationThresh[trig_sp_deviation], UNITSID_POSITION_ENTRY, d->DataCollectionSetpointDeviationThreshold[0]);
    (void)fpconvert_IntToFloatBuffer(conf.DeviationThresh[trig_pos_deviation], UNITSID_POSITION_ENTRY, d->DataCollectionPositionDeviationThreshold[0]);
    (void)fpconvert_IntToFloatBuffer(conf.DeviationThresh[trig_pres_deviation], UNITSID_PRESSURE_ENTRY, d->DataCollectionPressureDeviationThreshold[0]);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_WriteDataCollectionTriggerConfiguration(const u8 *src, u8 *dst)
{
    const Req_WriteDataCollectionTriggerConfiguration_t *s = (const void *)dst;
    DhogTriggerConf_t conf;
    (void)datahog_GetTriggerConf(&conf);
    conf.FilterConf.Shift = util_GetU8(s->DataCollectionFilterCoef[0]);
    conf.BinaryOptions = util_GetU16(s->DataCollectionTriggerBinaryOptions[0]);
    conf.pvthreshold[Xlow] = fpconvert_FloatBufferToInt16Clamped(s->DataCollectionTriggerAIInputThreshold[Xlow],
                                                           UNITSID_SIGNAL_ENTRY, pvthreshold_range);
    conf.pvthreshold[Xhi] = fpconvert_FloatBufferToInt16Clamped(s->DataCollectionTriggerAIInputThreshold[Xhi],
                                                           UNITSID_SIGNAL_ENTRY, pvthreshold_range);
    conf.DeviationThresh[trig_sp_deviation] = fpconvert_FloatBufferToInt16Clamped(s->DataCollectionSetpointDeviationThreshold[0],
                                                           UNITSID_POSITION_ENTRY, spthreshold_range);
    conf.DeviationThresh[trig_pos_deviation] = fpconvert_FloatBufferToInt16Clamped(s->DataCollectionPositionDeviationThreshold[0],
                                                           UNITSID_POSITION_ENTRY, posthreshold_range);
    conf.DeviationThresh[trig_pres_deviation] = fpconvert_FloatBufferToInt16Clamped(s->DataCollectionPressureDeviationThreshold[0],
                                                           UNITSID_PRESSURE_ENTRY, presthreshold_range);
    ErrorCode_t err = datahog_SetTriggerConf(&conf);
    s8_least ret;
    if(err == ERR_OK)
    {
        ret = hartcmd_ReadDataCollectionTriggerConfiguration(src, dst);
        //Since we rely on hartcmd_ReadDataCollectionTriggerConfiguration to build a response:
        //lint -esym(768, Rsp_WriteDataCollectionTriggerConfiguration_t::*)
    }
    else
    {
        ret = err2hart(err);
    }
    return ret;
}

/* This line marks the end of the source */
