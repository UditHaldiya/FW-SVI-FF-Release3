/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file FFAP_xlate_9_10.c
    \brief Trivial add-only translation between layouts 9 and 10

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "crc.h"
#include "FFAP_xlate_9_10.h"

//lint -esym(754, *_t9::*) -esym(754, *_t10::*) Types are for sizes here

typedef struct logdata_t9
{
    u8 extent_assignment[18];
    u16 CheckWord;
} logdata_t9; //Same as 10;

static const logdata_t9 logdata_9 =
{
    .extent_assignment =
    {
        [0] = 0xFFU,
        [1] = 0xFFU,
        [2] = 0xFFU,
        [3] = 0xFFU,
        [4] = 0xFFU,
        [5] = 0xFFU,
        [6] = 0xFFU,
        [7] = 0xFFU,
        [8] = 0xFFU,
        [9] = 0xFEU,
        [10] = 0xFEU,
        [11] = 0xFEU,
        [12] = 0xFEU,
        [13] = 0xFEU,
        [14] = 0xFEU,
        [15] = 0xFEU,
        [16] = 0xFEU,
        [15] = 0xFEU,
        [16] = 0xFEU,
        [17] = 0xFEU,
    },
    .CheckWord = 0, //don't care
};
static const logdata_t9 logdata_10 =
{
    .extent_assignment =
    {
        [0] = 0xFFU,
        [1] = 0xFFU,
        [2] = 0xFFU,
        [3] = 0xFFU,
        [4] = 0xFFU,
        [5] = 0xFFU,
        [6] = 0xFFU,
        [7] = 0xFFU,
        [8] = 0xFFU,
        [9] = 0xFFU,
        [10] = 0xFFU,
        [11] = 0xFFU,
        [12] = 0xFFU,
        [13] = 0xFFU,
        [14] = 0xFFU,
        [15] = 0xFFU,
        [16] = 0xFFU,
        [15] = 0xFFU,
        [16] = 0xFFU,
        [17] = 0xFEU,
    },
    .CheckWord = 0, //don't care
};

/** \A trivial translation routine, except that we reset log file system and request factory defaults to be written
NOTE: Never touch id 0!
*/
ErrorCode_t FFAP_xlatedn_10_9(u8 *dst, const u8 *src, void (*func)(void))
{
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_9; id++)
    {
        switch(id)
        {
            case FFAP_NVRAMID_logdata_10:
            {
                //Since file max sizes changed, need to reset file system
                STRUCT_GET(&logdata_9, dst + FFAP_nvram_map_9[id].offset);

            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_9[id].offset, src + FFAP_nvram_map_10[id].offset, FFAP_nvram_map_10[id].length);
            }
            break;
        }
        func();
    }
    return ERR_OK;
}

typedef struct SchedTime_t10
{
    s64 TimeSince; //!< time in ticks since last monitored event was scheduled
    s64 Guard; //!< guard time in ticks since the event was actually executed (by whatever means)
    u32 TicksSinceSpecial; //!< control of special timeout due to things like trip grace period
    u16 LastTickCount;      //!< last system tick count used to update TimeSince (small to damage-control glitches)
    u16 CheckWord;
} SchedTime_t10;
static const SchedTime_t10 DEF_SchedTime_t10 =
{
    //The NVMEMtable must be configured with NULL defaults; that's an indication of default init
    .TimeSince = (24*60*60*200)*30LL - 200LL, //DAYS_TO_TICKS(PSTrigger.interval) - DEFAULT_NEXT_TIME, //InitialTimeSince, //run 1st time in that time into interval
    .Guard = 0LL,
    .TicksSinceSpecial = 0,
    .LastTickCount = 0,
    .CheckWord = 0, //don't care
};

typedef struct PSTConf_t10
{
    s16 sp_threshold;  //!< Aborts PST if (process) sp walks outside the threshold
    s16 travel;             //!< travel from stop for pst test (in std units)
    u32 maxtime;            //!< time in milliseconds - if exceeded pst test failed
    s16 ramp_speed;         //!< ramp speed in %/sec
    s16 PresAbortActuator;         //!< main pressure threshold outside which we abort (std units)
    s16 PresAbortPilot;         //!< pilot pressure threshold outside which we abort (std units)
    u16 LeadTime; //breakout/stabilization time in ms
    u16 DwellTime;
    u32 StrokeTmout;
    u16 datamap; //!< what we collect
    u16 skip_count;
    u16 FreezeOptions;
    u8 pattern;
    u16 CheckWord;
} PSTConf_t10;

static const PSTConf_t10 DEF_PstConf10 =
{
    .sp_threshold = 819, //STD_FROM_PERCENT(PST_SETPOINT_THRESHOLD_DEFAULT),
    .travel = 819, //STD_FROM_PERCENT(DEFAULT_TRAVEL),
    .maxtime = 5000, //DEFAULT_MAX_TIME,
    .ramp_speed = 32752, //DEFAULT_RAMP_SPEED,
    .PresAbortActuator = 20*120, //PST_MAX_PRES_ABORT_ACT,
    .PresAbortPilot = 20*120, //PST_MAX_PRES_ABORT_PILOT,
    .LeadTime = 20, //LEAD_TIME_LIMIT_DEFAULT,
    .DwellTime = 4, //DEFAULT_DWELL_TIME,
    .StrokeTmout = 0, //will be replaced with auto
    .datamap = 0x7fU, /*
        (1U<<DATAHOG_POSITION)
        | (1U<<DATAHOG_SETPOINT)
        | (1U<<DATAHOG_MAINPRESSURE)
        | (1U<<DATAHOG_PRESSUREB)
        | (1U<<DATAHOG_IPCURRENT)
        | (1U<<DATAHOG_PILOTPRESSURE), */
    .skip_count = 0,
    .FreezeOptions = 0x3cU, //PST_FREEZE_SPRANGE | PST_FREEZE_SPRATE | PST_FREEZE_CUTOFF | PST_FREEZE_DEADZONE,
    .pattern = 2, //PST_PATTERN_DUDU,
    .CheckWord = 0, //don't care
};

typedef struct PSTrigger_t10
{
    u8 PstSchedTrigger;
    u8 PstUiTrigger; //
    u8 PstCommTrigger;
    u8 PstDiTrigger;
    u8 PstPvTrigger;
    s16 pvthreshold;
    s16 interval;           //!< Time in days between PST tests
    u16 CheckWord;
} PSTrigger_t10;
static const PSTrigger_t10 PSTrigger_default10 =
{
    .PstSchedTrigger = 0,
    .PstUiTrigger = 0U, //All PST features on local UI disabled by default
    .PstCommTrigger = 1U,
    .PstDiTrigger = 0,
    .PstPvTrigger = 0,
    .pvthreshold = 12000, //STD_FROM_MA(12.0), //mA
    .interval = 30, //days = PST_DEFAULT_INTERVAL,
    .CheckWord = 0U, //don't care
};

typedef struct DatahogConf_t10
{
    u16 datamask;
    u8 taskid;
    u8 padding;
    u16 skip_count;
    u16 maxsamples; //!< 0 means unlimited; meaningful for linear only
    u16 num_presamples; //!< In multiples of number of 1's in datamask
    u16 CheckWord;
} DatahogConf_t10;
static const DatahogConf_t10 DatahogConf_default =
{
    .datamask = 1U,
    .taskid = 2, //TASKID_CYCLE,
    .padding = 0,
    .skip_count = 0,
    .CheckWord = 0U, //don't care
};

typedef struct DhogTriggerConf_t10
{
    u8 DhogCommTrigger;
    u8 DhogDiTrigger;
    u8 DhogPvTrigger;
    s16 pvthreshold;
    u16 CheckWord;
} DhogTriggerConf_t10;
static const DhogTriggerConf_t10 DhogTriggerConf_default10 =
{
    .DhogCommTrigger = 1U,
    .DhogDiTrigger = 0,
    .DhogPvTrigger = 0,
    .pvthreshold = 12000, //STD_FROM_MA(12.0),
    .CheckWord = 0, //don't care
};

typedef struct FactoryDefaultState_t10
{
    u8 first_time;
    u8 padding;
    u16 CheckWord;
} FactoryDefaultState_t10;
static const FactoryDefaultState_t10 fdstate_default10 =
{
    .first_time = 1, //IMPORTANT: On translation; re-save current as factory defaults
    .padding = 0,
    .CheckWord = 0U, //don't care
};

typedef struct PIDData_t10
{
    u16 P;
    u16 I;
    u16 D;
    s16 PAdjust;
    s16 Beta;
    s16 PosComp;
    s16 DeadZone;
    u16 Band;
    u16 CheckWord;
} PIDData_t10;

CONST_ASSERT(FFAP_NVRAMID_PIDData_10 ==FFAP_NVRAMID_PIDData_9);
#define P_LOW_LIMIT_10 10

ErrorCode_t FFAP_xlateup_9_10(const u8 *src, u8 *dst, void (*func)(void))
{
    //Common part of layout
    for(u8_least id = 1U; id<FFAP_NVRAM_ENTRIES_VER_9; id++)
    {
        switch(id)
        {
            //for all 8 slots, remove possible positive feedback (bug 42246)
            case FFAP_NVRAMID_PIDData_10:
            case FFAP_NVRAMID_PIDData_10+1:
            case FFAP_NVRAMID_PIDData_10+2:
            case FFAP_NVRAMID_PIDData_10+3:
            case FFAP_NVRAMID_PIDData_10+4:
            case FFAP_NVRAMID_PIDData_10+5:
            case FFAP_NVRAMID_PIDData_10+6:
            case FFAP_NVRAMID_PIDData_10+7:
            {
                const PIDData_t10 *s = (const void *)(src + FFAP_nvram_map_9[id].offset);
                PIDData_t10 *d = (void *)(dst + FFAP_nvram_map_10[id].offset);
                *d = *s;
                s32 Pa = d->P;
                if( Pa < P_LOW_LIMIT_10)
                {
                    d->P = P_LOW_LIMIT_10;
                }
                Pa += d->PAdjust;
                //Same logic as in tune_LimitPID() (atune.c)
                if( Pa < P_LOW_LIMIT_10)
                {
                    d->PAdjust = (s16)MAX(P_LOW_LIMIT_10 - (s32)d->P, d->PAdjust);
                }
                STRUCT_CLOSE(PIDData_t10, d);
            }
            break;
            case FFAP_NVRAMID_logdata_10:
            {
                //Since file max sizes changed, need to reset file system
                STRUCT_GET(&logdata_10, dst + FFAP_nvram_map_10[id].offset);
            }
            break;
            default:
            {
                mn_memcpy(dst + FFAP_nvram_map_10[id].offset, src + FFAP_nvram_map_9[id].offset, FFAP_nvram_map_9[id].length);
            }
            break;
        }
        func();
    }

    //Complete new records:
    STRUCT_GET(&DEF_SchedTime_t10, dst + FFAP_nvram_map_10[FFAP_NVRAMID_PSTSchedTime_10].offset);
    STRUCT_GET(&DEF_PstConf10, dst + FFAP_nvram_map_10[FFAP_NVRAMID_PSTConf_10].offset);
    STRUCT_GET(&PSTrigger_default10, dst + FFAP_nvram_map_10[FFAP_NVRAMID_PSTrigger_10].offset);
    STRUCT_GET(&DatahogConf_default, dst + FFAP_nvram_map_10[FFAP_NVRAMID_DatahogConf_10].offset);
    STRUCT_GET(&DhogTriggerConf_default10, dst + FFAP_nvram_map_10[FFAP_NVRAMID_DhogTriggerConf_10].offset);
    STRUCT_GET(&fdstate_default10, dst + FFAP_nvram_map_10[FFAP_NVRAMID_FactoryDefaultState_10].offset);
    return ERR_OK;
}


/* This line marks the end of the source */
