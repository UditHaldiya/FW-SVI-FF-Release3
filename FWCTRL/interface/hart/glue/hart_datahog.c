/*
Copyright 2014 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_datahog.c
    \brief HART glue layer for high-speed data collection

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "datahog.h"
#include "hartdef5.h"
#include "bufutils.h"
#include "hartfunc.h"
//#include "dimensions.h"

s8_least hartcmd_ReadDataCollectionState(const u8 *src, u8 *dst)
{
    const Req_ReadDataCollectionState_t *s = (const void *)src;
    UNUSED_OK(s);
    DatahogState_t hog;
    (void)datahog_GetState(&hog);
    Rsp_ReadDataCollectionState_t *d = (void *)dst;
    util_PutU16( d->DAQSkipsLeftPerm[0], hog.skipsleft[HogConfPerm] );
    util_PutU16( d->DAQSkipsLeftTemp[0], hog.skipsleft[HogConfTemporary] );

    util_PutU16( d->DAQNumPresamples[0], hog.num_presamples );
    util_PutU16( d->DAQPresamplesLeft[0], hog.presamples_left );

    util_PutU16( d->DAQNumberOfVariablesPerm[0], hog.numvars[HogConfPerm] );
    util_PutU16( d->DAQNumberOfVariablesTemp[0], hog.numvars[HogConfTemporary] );

    util_PutU8( d->DAQStatusPerm[0], (u8)hog.status[HogConfPerm] );
    util_PutU8( d->DAQStatusTemp[0], (u8)hog.status[HogConfTemporary] );

    util_PutU8( d->DAQProcessId[0], hog.procId );
    util_PutU8( d->DAQConfigId[0], hog.DatahogConfId );

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

s8_least hartcmd_ReadDataCollectionConfiguration(const u8 *src, u8 *dst)
{
    DatahogConf_t hog;
    ErrorCode_t err = ERR_OK;
    const Req_ReadDataCollectionConfiguration_t *s = (const void *)src;
    u8 selector = util_GetU8(s->DataCollectionConfSelector[0]);
    if(selector == (u8)DCCCurrent)
    {
        (void)datahog_Get(&hog);
    }
    else
    {
        (void)datahog_GetPerm(&hog);
        if(selector != (u8)DCCPersistent)
        {
            err = ERR_INVALID_PARAMETER;
        }
    }

    if(err == ERR_OK)
    {
        Rsp_ReadDataCollectionConfiguration_t *d = (void *)dst;
        util_PutU16(d->DataCollectionBitmap[0], hog.datamask);
        util_PutU16(d->DataCollectionSkipCount[0], hog.skip_count);
        DataCollectionContextEnum_t hcontext;
        if(hog.taskid == TASKID_CONTROL)
        {
            hcontext = DCCControlTask;
        }
        else
        {
            hcontext = DCCCycleTask;
        }
        util_PutU8(d->DataCollectionContext[0], (u8)hcontext);
        util_PutU16(d->DataCollectionMaxSamples[0], hog.maxsamples);
        util_PutU16(d->DataCollectionMaxPreSamples[0], hog.num_presamples);
        //These fields are filled automatically:
        UNUSED_OK(d->DataCollectionConfSelector);
    }

    return err2hart(err);
}

s8_least hartcmd_WriteDataCollectionConfiguration(const u8 *src, u8 *dst)
{
    DatahogConf_t hog;
    const Req_WriteDataCollectionConfiguration_t *s = (const void *)src;

    ErrorCode_t err = ERR_OK;
    u8 selector = util_GetU8(s->DataCollectionConfSelector[0]);
    if(selector == (u8)DCCCurrent)
    {
        (void)datahog_Get(&hog);
    }
    else if(selector == (u8)DCCPersistent)
    {
        (void)datahog_GetPerm(&hog);
    }
    else
    {
        err = ERR_INVALID_PARAMETER;
    }

    if(err == ERR_OK)
    {
        taskid_t taskid;
        if(util_GetU8(s->DataCollectionContext[0]) == (u8)DCCControlTask)
        {
            taskid = TASKID_CONTROL;
        }
        else
        {
            taskid = TASKID_CYCLE;
        }
        hog.taskid = taskid;
        hog.datamask = util_GetU16(s->DataCollectionBitmap[0]);
        hog.skip_count = util_GetU16(s->DataCollectionSkipCount[0]);
        hog.maxsamples = util_GetU16(s->DataCollectionMaxSamples[0]);
        hog.num_presamples = util_GetU16(s->DataCollectionMaxPreSamples[0]);

        if(util_GetU8(s->DataCollectionConfSelector[0]) == DCCPersistent)
        {
            err = datahog_SetPerm(&hog);
        }
        else
        {
            err = datahog_Set(&hog);
        }
    }

    s8_least ret;
    if(err == ERR_OK)
    {
        ret = hartcmd_ReadDataCollectionConfiguration(src, dst);
        //Since we rely on hartcmd_ReadDataCollectionConfiguration to build a response:
        //lint -esym(768, Rsp_WriteDataCollectionConfiguration_t::*)
    }
    else
    {
        ret = err2hart(err);
    }
    return ret;
}

/* This line marks the end of the source */
