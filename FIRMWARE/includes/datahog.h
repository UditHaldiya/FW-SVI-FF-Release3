/*
Copyright 2014-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file datahog.c
    \brief Implementation of data collection trigger

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/
#ifndef DATAHOG_H_
#define DATAHOG_H_
#include "errcodes.h"
#include "taskids.h"
#include "process.h"

//Bits
#define DATAHOG_POSITION 0
#define DATAHOG_MAINPRESSURE 1
#define DATAHOG_PILOTPRESSURE 2
#define DATAHOG_SUPPLYPRESSURE 3
#define DATAHOG_PRESSUREB 4
#define DATAHOG_SETPOINT 5
#define DATAHOG_IPCURRENT 6
#define DATAHOG_AI_INPUT 7

typedef u8 DatahogConfId_t;
#define HogConfPerm 0U
#define HogConfTemporary 1U
#define HogConfsCount 2U

typedef enum DatahogStatus_t
{
    DatahogIdle,
    DatahogInterrupted,
    DatahogCollecting,
    DatahogCompleted,
    DatahogStop,
    DatahogStart,
    DatahogForceStart //bypass process constraint
} DatahogStatus_t;

typedef struct DatahogState_t
{
    u16 skipsleft;
    u16 num_presamples; //!< In multiples of number of diag_t entries
    u16 presamples_left; //!< # of presamples left to copy to main buffer - In multiples of number of diag_t entries
    u8 numvars; //!< # of vars in a sample
    DatahogStatus_t status;
    //u8 bufmode; //!< 0 - circular, no header, 1 - linear, 2 - linear with pruning
    ProcId_t procId;
    DatahogConfId_t DatahogConfId; //!< which configuration to use
    u16 CheckWord;
} DatahogState_t;

typedef struct DatahogConf_t
{
    u16 datamask;
    taskid_t taskid;
    u16 skip_count;
    u16 maxsamples; //!< 0 means unlimited; meaningful for linear only
    u16 num_presamples; //!< In multiples of number of 1's in datamask
    u16 CheckWord;
} DatahogConf_t;

extern const DatahogConf_t *datahog_Get(DatahogConf_t *dst);
extern ErrorCode_t datahog_Set(const DatahogConf_t *src);
extern void datahog_Collect(void);
extern u8_least datahog_TestDataMap(u16 datamask);

extern ErrorCode_t datahog_ControlAuto(DatahogStatus_t op, DatahogConfId_t confid);
extern ErrorCode_t datahog_Control(DatahogStatus_t op, DatahogConfId_t confid);

ErrorCode_t datahog_SetPerm(const DatahogConf_t* src);
const DatahogConf_t* datahog_GetPerm(DatahogConf_t *dst);
UNTYPEACC(datahog_SetPerm, datahog_GetPerm);

extern void datahog_TriggerMon(void);
extern void datahog_InitDeviationFilters(void);

#endif //DATAHOG_H_
/* This line marks the end of the source */
