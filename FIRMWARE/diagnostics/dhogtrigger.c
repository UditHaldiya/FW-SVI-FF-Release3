/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file dhogtrigger.c
    \brief Implementation of data collection trigger

    CPU: Any

    OWNER: AK

    \ingroup Diagnostics
*/
#include "mnwrap.h"
#include "datahog.h"
#include "key.h"
#include "inpv.h"
#include "dhogtrigger.h"

#include "devicemode.h"
#include "pressures.h"

static const DhogTriggerConf_t DhogTriggerConf_default =
{
    .pvthreshold =
    {
        [Xlow] =STD_FROM_MA(12.0),
        [Xhi] =STD_FROM_MA(12.0),
    },
    .DeviationThresh =
    {
        [trig_sp_deviation] = STD_FROM_PERCENT(2.0),
        [trig_pos_deviation] = STD_FROM_PERCENT(2.0),
        [trig_pres_deviation] = STD_FROM_PSI(10.0),
    },
    .BinaryOptions = (1U<<DhogBO_Extrn),
    .FilterConf =
    {
        .Shift = 6,
    },
    .CheckWord = CRC_SEED //doesn't matter
};

static DhogTriggerConf_t DhogTriggerConf; //! Datahog trigger configuration

const sig_t pvthreshold_range[Xends] = //! PV/AI threshold for data collection trigger
{
    [Xlow] = STD_FROM_MA(0.0),
    [Xhi] = STD_FROM_MA(23.0),
};

const pos_t spthreshold_range[Xends] = //! setpoint deviation threshold for data collection trigger
{
    [Xlow] = STD_FROM_PERCENT(0.01),
    [Xhi] = STD_FROM_PERCENT(100.0),
};

const pos_t posthreshold_range[Xends] = //! position deviation threshold for data collection trigger
{
    [Xlow] = STD_FROM_PERCENT(0.01),
    [Xhi] = STD_FROM_PERCENT(100.0),
};

const pres_t presthreshold_range[Xends] = //! main pressure deviation threshold for data collection trigger
{
    [Xlow] = STD_FROM_PSI(0.01),
    [Xhi] = STD_FROM_PSI(60.0),
};

/** \brief A standard Get function
*/
const DhogTriggerConf_t *datahog_GetTriggerConf(DhogTriggerConf_t *dst)
{
    return STRUCT_TESTGET(&DhogTriggerConf, dst);
}

/** \brief A standard Set function
*/
ErrorCode_t datahog_SetTriggerConf(const DhogTriggerConf_t *src)
{
    if(src == NULL)
    {
        src = &DhogTriggerConf_default;
    }

    ErrorCode_t err = ERR_INVALID_PARAMETER;
    const DhogTriggerConf_t *p = src;
    if( (p->pvthreshold[Xlow] >= pvthreshold_range[Xlow]) && (p->pvthreshold[Xlow] <= p->pvthreshold[Xhi]) && (p->pvthreshold[Xhi] <= pvthreshold_range[Xhi])
        && (p->DeviationThresh[trig_sp_deviation] >= spthreshold_range[Xlow]) && (p->DeviationThresh[trig_sp_deviation] <= spthreshold_range[Xhi])
        && (p->DeviationThresh[trig_pos_deviation] >= posthreshold_range[Xlow]) && (p->DeviationThresh[trig_pos_deviation] <= posthreshold_range[Xhi])
        && (p->DeviationThresh[trig_pres_deviation] >= presthreshold_range[Xlow]) && (p->DeviationThresh[trig_pres_deviation] <= presthreshold_range[Xhi])
            )
    {
        //NOTE: All binary options are OK
        Struct_Copy(DhogTriggerConf_t, &DhogTriggerConf, p);
        err = ram2nvramAtomic(NVRAMID_DhogTriggerConf);
    }
    return err;
}

/** \brief Starts data hogging if DhogCommTrigger is enabled
\param DatahogConfId - selector of permanent or temporary configuration
\return an error code
*/
ErrorCode_t datahog_TriggerComm(DatahogConfId_t DatahogConfId, DatahogStatus_t cmd)
{
    ErrorCode_t err = ERR_DP_DEVICE_BUSY; //shameless hijack of error code
    if( (DhogTriggerConf.BinaryOptions & (1U<< DhogBO_Extrn)) != 0U)
    {
        err = datahog_Control(cmd, DatahogConfId);
    }
    return err;
}

static pos_t getsp(void)
{
    pos_least_t sp;
    (void)mode_GetIntendedControlMode(&sp);
    return (pos_t)CLAMP(sp, MIN_ALLOWED_POSITION, MAX_ALLOWED_POSITION);
}

static  s16 ((* const read_trig_func [])(void)) =
{
    [trig_sp_deviation] = getsp,
    [trig_pos_deviation] = vpos_GetScaledPosition,
    [trig_pres_deviation] = pres_GetMainPressure,
};

static FilterState_t TrigFilterState[trig_total];

/** \brief Reset/Initialize deviation filters
*/
void datahog_InitDeviationFilters(void)
{
    for(u8_least i=0; i<NELEM(read_trig_func); i++)
    {
        filter_Init(read_trig_func[i](), &TrigFilterState[i], &DhogTriggerConf.FilterConf);
    }
}

static const u16 binopts[] =
{
    [trig_sp_deviation] = 1U<<DhogBO_SpDeviation,
    [trig_pos_deviation] = 1U<<DhogBO_PosDeviation,
    [trig_pres_deviation] = 1U<<DhogBO_PresDeviation,
};

/** \brief A helper monitor of deviation-based data collection triggers
*/
static bool_t datahog_DeviationTriggerMon(void)
{
    bool_t ret = false;
    for(u8_least i=0; i<NELEM(read_trig_func); i++)
    {
        s16_least now = read_trig_func[i]();
        if((binopts[i] & DhogTriggerConf.BinaryOptions) != 0U)
        {
            s16_least avg = filter_Report(&TrigFilterState[i], &DhogTriggerConf.FilterConf);
            if(!ret)
            {
                ret = ABS(now-avg) > DhogTriggerConf.DeviationThresh[i];
            }
        }
        filter_Update(now, &TrigFilterState[i], &DhogTriggerConf.FilterConf);
    }
    return ret;
}

/** \brief Monotors internal trigger events and starts data hogging if an event occurs.

NOTE: External requests are handled independently as follows:
1. On demand - via (async.) HART command - is handled by datahog_TriggerComm()
2. On TB alerts - via IPC - is handled by IPC_Process_DOSwitches()
In general, search for use of datahog_Control()
*/
void datahog_TriggerMon(void)
{
    //Check if new collection if requested. Very tedious
    //1. All deviation triggers
    bool_t need_trigger = datahog_DeviationTriggerMon();

    if(!need_trigger)
    {
        //2. Analog input
        sig_t pv = inpv_GetPV();
        if(pv < DhogTriggerConf.pvthreshold[Xlow])
        {
            if( (DhogTriggerConf.BinaryOptions & (1U << DhogBO_PvBelow))!=0U)
            {
                need_trigger = true;
            }
        }
        else if(pv > DhogTriggerConf.pvthreshold[Xhi])
        {
            if( (DhogTriggerConf.BinaryOptions & (1U << DhogBO_PvAbove))!=0U)
            {
                need_trigger = true;
            }
        }
        else if ( (DhogTriggerConf.BinaryOptions & (1U << DhogBO_PvBetween))!=0U)
        {
            need_trigger = true;
        }
        else
        {
            //3. Digital input
            bool_t di = bios_ReadDiState(); //true == open; false closed
            if((((DhogTriggerConf.BinaryOptions & (1U << DhogBO_DiClosed))!=0U) && !di)
                || (((DhogTriggerConf.BinaryOptions & (1U << DhogBO_DiOpen))!=0U) && di))
            {
                need_trigger = true;
            }
        }
    }
    if(need_trigger)
    {
        (void)datahog_Control(DatahogStart, HogConfPerm);
        datahog_InitDeviationFilters();
    }
}

/* This line marks the end of the source */
