/*
Copyright 2012 by GE Energy / Dresser, Inc., as an unpublished trade secret. All rights reserved.

This document and all information herein are the property of GE Energy.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon demand.
*/

/**
    \file appl_alert.c
    \brief Position and other types of Alerts (Level monitors)

    CPU: Any

    OWNER: AP
*/

#include <softing_base.h>
#include <ptb.h>
#include <hw_if.h>
#include <base.h>
#include "time_defs.h"
#include "numutils.h"

#include <appl_int.h>

#include "mn_advanced.h"
#include "ff2nvram.h"
#include "nvffext.h"

#include "mnhart2ff.h"
#include "mnassert.h"
#include "mnfault2alert.h"
#include "mntrapdef.h"
#include <osif.h>

#include "ptbcustomsubx.h"
#include "logfile.h"
#include "logfileids.h"
#include "logfproc.h"
#include "appl_alert.h"
#include "pressure_range.h"
#include "mntbmspff.h"

#include "syncpatches.h"
#include "mn_trends.h"
#include "mnhart2ff.h"

#include "TBALERTS_config.h"

//A few helpers not to be used directly
#if TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)
#define AlertCacheSet(al, val)                ((al)->alert = (val))
#else
#define AlertCacheSet(al, val)
#endif
#if TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE)
#define   AlertHistSet(al, val)              ((al)->historic_alert = (val))
#else
#define   AlertHistSet(al, val)
#endif
//Now, define set/clear - for public use
#define AlertCacheSetAll(al) AlertCacheSet(al, STATE_TRUE); AlertHistSet(al, STATE_TRUE)
#define AlertCacheClearCurr(al) AlertCacheSet(al, STATE_FALSE)
#define AlertCacheClearAll(al) AlertCacheSet(al, STATE_FALSE); AlertHistSet(al, STATE_FALSE)
#if 0
Usage:
                    AlertCacheSetAll(pAlert);
                    AlertCacheClearCurr(pAlert);
            AlertCacheClearAll(pAlert);
#endif

#if (TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)) || (TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE))
#define UNUSED_OK_AlertType
#else
#define UNUSED_OK_AlertType UNUSED_OK(AlertType)
#endif
//------------------------------------------------------------------

  #define  MODULE_ID      (COMP_FAPP + MOD_APPL_TRN)

//------------------------------------------------------------------

//lint -esym(818, 'T_FBIF_PTB `*')

#ifndef NDEBUG //for accelerated testing!
//You can change the value using direct write to RAM (sub of cmd 255). I use 5
//lint -esym(843, seconds_in_hour) could be const
u16_least seconds_in_hour = (60*60); //5 will do
#endif //NDEBUG



// The Alarm / Alert handling structure designed to provide unified Alarm
// Handling API

typedef enum AlertType_t
{
    ALERT_TYPE_DEVIATION,
    ALERT_TYPE_POSITION_HIHI,
    ALERT_TYPE_POSITION_HI,
    ALERT_TYPE_POSITION_LO,
    ALERT_TYPE_POSITION_LOLO,
    ALERT_TYPE_SP_TIMEOUT,

    ALERT_TYPE_NEAR_CLOSE,

    ALERT_TYPE_TRAVELACC_A,
    ALERT_TYPE_TRAVELACC_B,
    ALERT_TYPE_CYCLECNT_A,
    ALERT_TYPE_CYCLECNT_B,

    ALERT_TYPE_WORKTIME,

    ALERT_TYPE_SUP_PRES_HI,
    ALERT_TYPE_SUP_PRES_LO,
    ALERT_TYPE_SUP_PRES_LOLO,
    ALERT_TYPE_TEMP_HI,
    ALERT_TYPE_TEMP_LO,
    ALERT_TYPE_IPCUR_HI,
    ALERT_TYPE_IPCUR_LO,

    ALERT_TYPE_SENSOR_FAILED,
    ALERT_TYPE_PROCESSOR,
    ALERT_TYPE_VALVE_CONTROL,
    ALERT_TYPE_MISSION,
    ALERT_TYPE_AIR_SUPPLY,
    ALERT_TYPE_HARDWARE,

    ALERT_TYPE_MAX
} AlertType_t;

#define ALERT_FIRST_ALERT   ALERT_TYPE_DEVIATION

//-----------------------------------------------------------------------------------------------
// MACRO's for comparison

#define ABOVE_THHOLD(val,rng)               ((val) > (rng))
#define BELOW_THHOLD(val,rng)               ((val) < (rng))

#define ABOVE_DBAND(val,rng,db)             ((val) > ((rng) + (db)))
#define BELOW_DBAND(val,rng,db)             ((val) < ((rng) - (db)))

//-----------------------------------------------------------------------------------------------
// Type definition for Time handling

typedef struct Alert_TimeHandling_t
{
    u64 TimeStamp;  // Used for latching teh time of the condition POSITIVE
    bool_t  Latch;

} Alert_TimeHandling_t;

static volatile u64 Alert_SPTimeout_TimeStamp;

//-----------------------------------------------------------------------------------------------

// This function checks the Variable Status.
// Returns:
//  FALSE - BAD status, condition for FState activation;
//  TRUE  - No, GOOD status, no reasons to activate FState
static bool_t   ff_AlertSPTimeout_StatusOK(u8 VStatus)
{
    bool_t  result = true;
    u8      VQuality;

    VQuality    = VStatus & QUALITY_MASK;            // Extract the Quality
    switch (VQuality)
    {
        case SQ_BAD :
            // Bad value status -- activate FSTATE!
            result = false;
            break;
        default :
            // Nothing
            break;
    }

    return result;
}

/* \brief This function updates Alert_SPTimeout_TimeStamp
    param in:
        p_block_instance: pointer to function block
        Channel: channel
*/
void ff_AlertSPTimeout_Execute_fromFB(const T_FBIF_BLOCK_INSTANCE *p_block_instance, u16 Channel)
{
    T_FBIF_PTB *p_PTB = p_block_instance->p_block_desc->p_block;
    bool_t      UpdateTimeStamp = false;

    // Need to update the Time stamp, but!
    // -- If the status is BAD - do not update.
    switch (Channel)
    {
        case CH_AO_POSITION :                      // AO block
            if(p_PTB->setpoint_source == SP_SELECT_AOFB)
            {
                UpdateTimeStamp = ff_AlertSPTimeout_StatusOK(p_PTB->final_value.status);
            }
            break;

        case CH_DO_POSITION_OPEN_CLOSE :           // DO block BoolSP
            // Get the SP Time Stamp -- to be used later
            if(p_PTB->setpoint_source == SP_SELECT_DOBOOL)
            {
                UpdateTimeStamp = ff_AlertSPTimeout_StatusOK(p_PTB->final_value_d.status);
            }
            break;

        case CH_DO_POSITION_DISCRETE_POSITION :    // DO block IntSP
            if(p_PTB->setpoint_source == SP_SELECT_DOINT)
            {
                UpdateTimeStamp = ff_AlertSPTimeout_StatusOK(p_PTB->final_value_dint.status);
            }
            break;

        default :
            break;
    }

    MN_ENTER_CRITICAL();

        // Here we have a local flag that indicates that we should or should not update the TimeStamp
        if (UpdateTimeStamp)
        {
            Alert_SPTimeout_TimeStamp = osif_get_long_time_in_ms();
        }

    MN_EXIT_CRITICAL();
}

static bool_t   AlertHandle_Position(T_FBIF_PTB        *p_PTB,
                                     AlertType_t        AlertType)
{
    // 0 POSITION
    // 1 ALERT_POINT
    // 2 DEADBAND
    // 3 ALERT
    // 4 HISTORIC ALERT
    // 5 ENABLE

    FLOAT               Position;
    _POSITION_ALERT    *pAlert;
    USIGN8              VarQuality;
    bool_t              AlertDirectionUP = false;
    bool_t              OutsideOfRange;
    bool_t              InsideDeadBand;
    bool_t              AlertEnabled;
    bool_t              SetAlert;
    bool_t              ClearAlert;

    // Preset the data for the alert
    switch (AlertType)
    {
        case ALERT_TYPE_POSITION_HIHI :
            pAlert              = &p_PTB->position_hihi_alert;
            AlertDirectionUP    = true;
            AlertEnabled        = (bool_t)pAlert->enable;
            break;

        case ALERT_TYPE_POSITION_HI :
            pAlert              = &p_PTB->position_hi_alert;
            AlertDirectionUP    = true;
            AlertEnabled        = (bool_t)pAlert->enable;
            break;

        case ALERT_TYPE_POSITION_LO :
            pAlert              = &p_PTB->position_lo_alert;
            AlertDirectionUP    = false;
            AlertEnabled        = (bool_t)pAlert->enable;
            break;

        case ALERT_TYPE_POSITION_LOLO :
            pAlert              = &p_PTB->position_lolo_alert;
            AlertDirectionUP    = false;
            AlertEnabled        = (bool_t)pAlert->enable;
            break;

        default :
            pAlert              = NULL;
            AlertEnabled        = false;
            break;
    }

    bool_t astate = false; //pre-set

    if (pAlert != NULL)
    {   // Alert is present

        // Using the Working Position in Travel Units - and taking 60% off complexity of Anatoly's implementation
        Position            = p_PTB->working_pos.value * (p_PTB->travel.TravelRange / ONE_HUNDRED_PERCENT_FLOAT);
        VarQuality          = p_PTB->working_pos.status & QUALITY_MASK;  // Separate the Parameter Quality
        pAlert->position = Position;

        if (AlertEnabled)
        {   // Check the Var Quality
            if ((VarQuality == SQ_BAD) || (VarQuality == SQ_UNCERTAIN))
            {   // Quality NOT GOOD
                AlertEnabled = false;
            }
        }

        if (AlertEnabled)
        {   // If the Alert enabled
            astate = ((const u8 *)&p_PTB->alert_state)[AlertType] != 0;
            if (AlertDirectionUP)
            {
                OutsideOfRange = ABOVE_THHOLD(Position,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand = BELOW_DBAND(Position,pAlert->alert_point,pAlert->deadband);
            }
            else
            {
                OutsideOfRange = BELOW_THHOLD(Position,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand = ABOVE_DBAND(Position,pAlert->alert_point,pAlert->deadband);
            }


            SetAlert   = !astate && OutsideOfRange;
            ClearAlert =   astate && InsideDeadBand;

            if (SetAlert)
            {   // Alert is NOT set and is outside -> SET ALERT!
                astate = true;
                AlertCacheSetAll(pAlert);
            }

            if (ClearAlert)
            {   // Alert is set and is inside deadband -- clear alert
                astate = false;
                AlertCacheClearCurr(pAlert);
            }
        }
        else
        {   // Alert disabled --
            AlertCacheClearAll(pAlert);
        }

    }
    else
    {   // Alert is not present
        // Nothing
    }

    return astate;
}

//----------------------------------------------------------------------------------

#define TRAVEL_ACC_A        (0u)
#define TRAVEL_ACC_B        (TRAVEL_ACC_A + 1u)
#define TOTAL_TRAVEL_ACCS   (TRAVEL_ACC_B + 1u)

typedef struct TravelAcc_t
{
    u32     LastPos;
    bool_t  Initialized;

} TravelAcc_t;

static TravelAcc_t TravelAlertsData[TOTAL_TRAVEL_ACCS] =
{
    [TRAVEL_ACC_A] = {0u, false},
    [TRAVEL_ACC_B] = {0u, false}
};

/** \brief A restart patch for non-standard handling
*/
void alert_RestartTravelAlert(void)
{
    for(size_t n=0U; n<NELEM(TravelAlertsData); n++)
    {
        TravelAlertsData[n].Initialized = false;
    }
}

/** \brief Alerts are calculated in internal units
*/
static bool_t   AlertHandle_TravelAcc(T_FBIF_PTB *p_PTB, AlertType_t AlertType)
{
    UNUSED_OK(p_PTB);

    bool_t        astate = false;
    USIGN8        alertIndx;

    if (ALERT_TYPE_TRAVELACC_A == AlertType)
    {
        alertIndx = TRAVEL_ACC_A;
    }
    else if (ALERT_TYPE_TRAVELACC_B == AlertType)
    {
        alertIndx = TRAVEL_ACC_B;
    }
    else
    {
        //None of expected alerts
        alertIndx = TOTAL_TRAVEL_ACCS;
    }

    if (alertIndx != TOTAL_TRAVEL_ACCS)
    {
        TravelAlert_t t;
        (void)travel_Get(&t);
#if (TBALERTS_SELECTION_CACHE != (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)) && (TBALERTS_SELECTION_HISTORY != (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE))
        const
#endif
            _TRAVEL_ALERT *pAlert = &t.travel_alert[alertIndx];
        //float32 TravelRange = ta->travel.TravelRange;
        if ((bool_t)pAlert->enable)
        {
            //Calculate accumulation in internal units
            u32 travel = tbtrend_Get(index_travel_acc, NULL)->tbtrend.currently_collected;
            if ((bool_t)TravelAlertsData[alertIndx].Initialized)
            {
                t.travel_alert[alertIndx].travel_accumulation += (travel - TravelAlertsData[alertIndx].LastPos);
                ErrorCode_t e = travel_Set(&t);
                UNUSED_OK(e);
                astate = (ABOVE_THHOLD(pAlert->travel_accumulation,pAlert->int_alert_point));
                if(astate)
                {
                    AlertCacheSetAll(pAlert);
                }
                else
                {
                    AlertCacheClearCurr(pAlert);
                }
            }
            else
            {
                TravelAlertsData[alertIndx].Initialized = true;
            }
            TravelAlertsData[alertIndx].LastPos = travel;
        }
        else
        {   // Alert disabled --
            AlertCacheClearAll(pAlert);
        }

    }
    return astate;
}

//----------------------------------------------------------------------------------

#define CYC_COUNTER_A           (0u)
#define CYC_COUNTER_B           (CYC_COUNTER_A + 1u)
#define TOTAL_CYC_COUNTERS      (CYC_COUNTER_B + 1u)

typedef struct CycCounter_t
{
    u32 LastCycles;
    bool_t Initialized;
} CycCounter_t;

static CycCounter_t CycCounter[TOTAL_CYC_COUNTERS] =
{
    [CYC_COUNTER_A] =
    {
        .LastCycles=0U,
        .Initialized = false,
    },
    [CYC_COUNTER_B] =
    {
        .LastCycles=0U,
        .Initialized = false,
    },
};


/** \brief A restart patch for non-standard handling
*/
void alert_RestartCyclelAlert(void)
{
    for(size_t n=0U; n<NELEM(CycCounter); n++)
    {
        CycCounter[n].Initialized = false;
    }
}

static bool_t   AlertHandle_Counter(T_FBIF_PTB       *p_PTB,
                                    AlertType_t       AlertType)
{
    // 0 CYCLE_COUNTER
    // 1 ALERT_POINT
    // 2 DEADBAND
    // 3 ALERT
    // 4 HISTORIC ALERT
    // 5 ENABLE

    UNUSED_OK(p_PTB);

    bool_t               astate = false;
    USIGN8               alertIndx = TOTAL_CYC_COUNTERS;

    if (ALERT_TYPE_CYCLECNT_A == AlertType)
    {
        alertIndx = CYC_COUNTER_A;
    }
    else if (ALERT_TYPE_CYCLECNT_B == AlertType)
    {
        alertIndx = CYC_COUNTER_B;
    }
    else
    {   //None of expected alerts
        alertIndx = TOTAL_CYC_COUNTERS;
    }

    if (alertIndx < TOTAL_CYC_COUNTERS)
    {
        CycleCounterAlert_t c;
        (void)ccalert_Get(&c);
        _CYCLE_COUNTER_ALERT *pAlert = &c.ccalert[alertIndx];

        if ((bool_t)pAlert->enable)
        {
            u32 cycles = tbtrend_Get(index_cycle_counter, NULL)->tbtrend.currently_collected;
            if(CycCounter[alertIndx].Initialized)
            {
                pAlert->cycle_counter += cycles - CycCounter[alertIndx].LastCycles;
                ErrorCode_t e = ccalert_Set(&c);
                UNUSED_OK(e);

                astate = (ABOVE_THHOLD(pAlert->cycle_counter,pAlert->int_alert_point));
                if(astate)
                {
                    AlertCacheSetAll(pAlert);
                }
                else
                {
                    AlertCacheClearCurr(pAlert);
                }
            }
            else
            {
                CycCounter[alertIndx].Initialized = true;
            }
            CycCounter[alertIndx].LastCycles = cycles;
        }
        else
        {   // Alert disabled --
            AlertCacheClearAll(pAlert);
        }
    }
    return  astate;
}

//----------------------------------------------------------------------------------

static bool_t AlertHandle_Pressure(T_FBIF_PTB *p_PTB,
#if (TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)) || (TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE))
                                   _SYSTEM_ALERT *pAlert,
#endif
                                   AlertType_t AlertType, const PresAlertConf_t *aconf, bool_t AlertDirectionUP)
{
    bool_t              OutsideOfRange;
    bool_t              InsideDeadBand;

    u8 AlertEnabled = aconf->enable;

    u8 VarQuality = p_PTB->supply_pressure.status;

    // Check the Var quality
    VarQuality = VarQuality & QUALITY_MASK;
    if ((VarQuality == SQ_BAD) || (VarQuality == SQ_UNCERTAIN))
    {   // Quality NOT GOOD
        AlertEnabled = 0;
    }

    bool_t astate = false; //pre-set

    // Now process the Alert
    if (AlertEnabled != 0)
    {
        float32 Value = ffpres_ReadPressureInternalByIndex(pres_supply);
        if (AlertDirectionUP)
        {
            OutsideOfRange = ABOVE_THHOLD(Value,aconf->alert_point);        // In range or OUTSIDE?
            InsideDeadBand = BELOW_DBAND(Value,aconf->alert_point,aconf->deadband);
        }
        else
        {
            OutsideOfRange = BELOW_THHOLD(Value,aconf->alert_point);        // In range or OUTSIDE?
            InsideDeadBand = ABOVE_DBAND(Value,aconf->alert_point,aconf->deadband);
        }

        astate = ((const u8 *)&p_PTB->alert_state)[AlertType] != 0;
        bool_t SetAlert   = !astate && OutsideOfRange;
        bool_t ClearAlert =   astate && InsideDeadBand;

        if (SetAlert)
        {   // Alert is NOT set and is outside -> SET ALERT!
            astate = true;
            AlertCacheSetAll(pAlert);
        }

        if (ClearAlert)
        {   // Alert is set and is inside deadband -- clear alert
            astate = false;
            AlertCacheClearCurr(pAlert);
        }
    }
    else
    {   // Alert disabled --
        AlertCacheClearAll(pAlert);
    }

    return astate;
} //lint !e818 p_PTB CANNOT be a pointer to const - need common prototypes

static bool_t AlertHandle_PressureHi(T_FBIF_PTB *p_PTB, AlertType_t AlertType)
{
    UNUSED_OK_AlertType;
    const PresAlertConf_t *aconf = ffpres_GetAlertConf(PresAlertHi, NULL);
    return AlertHandle_Pressure(p_PTB,
#if (TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)) || (TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE))
                                &p_PTB->supply_pressure_hi_alert,
#endif
                                AlertType, aconf, true);
}
static bool_t AlertHandle_PressureLo(T_FBIF_PTB *p_PTB, AlertType_t AlertType)
{
    UNUSED_OK_AlertType;
    return AlertHandle_Pressure(p_PTB,
#if (TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)) || (TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE))
                                &p_PTB->supply_pressure_lo_alert,
#endif
                                AlertType, ffpres_GetAlertConf(PresAlertLo, NULL), false);
}
static bool_t AlertHandle_PressureLoLo(T_FBIF_PTB *p_PTB, AlertType_t AlertType)
{
    UNUSED_OK_AlertType;
    return AlertHandle_Pressure(p_PTB,
#if (TBALERTS_SELECTION_CACHE == (TBALERTS_OPTIONS_CACHE_OPTION_INCLUDE)) || (TBALERTS_SELECTION_HISTORY == (TBALERTS_OPTIONS_HISTORY_OPTION_INCLUDE))
                                &p_PTB->supply_pressure_lolo_alert,
#endif
                                AlertType, ffpres_GetAlertConf(PresAlertLoLo, NULL), false);
}

static bool_t   AlertHandle_System(T_FBIF_PTB          *p_PTB,
                                   AlertType_t          AlertType)
{
// PRESSURE or TEMPERATURE
// ALERT_POINT
// DEADBAND
// ALERT
// HISTORIC ALERT
// ENABLE

    FLOAT               Value;
    _SYSTEM_ALERT      *pAlert;
    USIGN8              VarQuality;
    bool_t              AlertDirectionUP = false;
    bool_t              AlertEnabled;

    // Preset the data for the alert
    switch (AlertType)
    {
        case ALERT_TYPE_TEMP_HI :
            pAlert              = &p_PTB->temperature_hi_alert;
            AlertEnabled        = (bool_t)pAlert->enable;
            AlertDirectionUP    = true;

            Value               = p_PTB->temperature.value;
            pAlert->curr_value = Value;
            VarQuality          = p_PTB->temperature.status;  // Separate the Parameter Quality
            break;

        case ALERT_TYPE_TEMP_LO :
            pAlert              = &p_PTB->temperature_lo_alert;
            AlertEnabled        = (bool_t)pAlert->enable;
            AlertDirectionUP    = false;

            Value               = p_PTB->temperature.value;
            pAlert->curr_value = Value;
            VarQuality          = p_PTB->temperature.status;  // Separate the Parameter Quality
            break;

        default :
            Value               = 0.0F;
            AlertEnabled        = false;
            pAlert              = NULL;
            VarQuality          = SQ_BAD;
            break;
    }

    bool_t astate = false; //pre-set

    if (pAlert != NULL)
    {   // Alert is present
        if (AlertEnabled)
        {   // Check the Var quality
            VarQuality = VarQuality & QUALITY_MASK;
            if ((VarQuality == SQ_BAD) || (VarQuality == SQ_UNCERTAIN))
            {   // Quality NOT GOOD
                AlertEnabled = false;
            }
        }

        // Now process the Alert
        if (AlertEnabled)
        {   // If the Alert enabled
            bool_t              OutsideOfRange;
            bool_t              InsideDeadBand;
            if (AlertDirectionUP)
            {
                OutsideOfRange = ABOVE_THHOLD(Value,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand = BELOW_DBAND(Value,pAlert->alert_point,pAlert->deadband);
            }
            else
            {
                OutsideOfRange = BELOW_THHOLD(Value,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand = ABOVE_DBAND(Value,pAlert->alert_point,pAlert->deadband);
            }

            astate = ((const u8 *)&p_PTB->alert_state)[AlertType] != 0;

            bool_t SetAlert   = !astate && OutsideOfRange;
            bool_t ClearAlert = astate && InsideDeadBand;

            if (SetAlert)
            {   // Alert is NOT set and is outside -> SET ALERT!
                astate = true;
                AlertCacheSetAll(pAlert);
            }

            if (ClearAlert)
            {   // Alert is set and is inside deadband -- clear alert
                astate = false;
                AlertCacheClearCurr(pAlert);
            }
        }
        else
        {   // Alert disabled --
            AlertCacheClearAll(pAlert);
        }
    }
    else
    {   // Alert is not present
        // Nothing
    }

    return astate;
}

static bool_t   AlertHandle_SPTimeout(T_FBIF_PTB          *p_PTB,
                                   AlertType_t          AlertType)
{
// TIME_SINCE_UPDATE - component_0
// ALERT_POINT
// MAXTIME
// ALERT
// HISTORIC ALERT
// ENABLE

    _SETPOINT_TIMEOUT_ALERT      *pAlert;

    if (AlertType == ALERT_TYPE_SP_TIMEOUT)
    {
        pAlert = &p_PTB->setpoint_timeout_alert;
    }
    else
    {
        pAlert = NULL;
    }

    bool_t astate = false;
    if (pAlert != NULL)
    { // alert present
        if ((bool_t)pAlert->enable)
        { //alert enabled

            astate = ((const u8 *)&p_PTB->alert_state)[AlertType] != 0;
            u64 timediff = osif_get_long_ms_since(Alert_SPTimeout_TimeStamp);
            float32 duration_time_s = MS_TO_SEC((float32)timediff);
            pAlert->time_since_update = duration_time_s;
            pAlert->setpoint_max_time = MAX(pAlert->setpoint_max_time, duration_time_s);

            //check the alert
            if (ABOVE_THHOLD(duration_time_s, pAlert->alert_point))
            {
                astate = true;
                AlertCacheSetAll(pAlert);
            }
            else
            {
                AlertCacheClearCurr(pAlert);
            }
        }
        else
        {
            //Alert disabled
            AlertCacheClearAll(pAlert);
        }
    }

    return astate;

}
//------------------------------------------------------------------------------------------------
// Time stamps for each

#define TIME_HANDLING_STRUC_HI      (0u)
#define TIME_HANDLING_STRUC_LO      (1u)

static Alert_TimeHandling_t Alert_IPCurHandle[] =
{
    [0u] = {0ULL,    false},
    [1u] = {0ULL,    false},
};

static bool_t   AlertHandle_IPCurrent(T_FBIF_PTB           *p_PTB,
                                      AlertType_t           AlertType)
{
    _IP_DRIVE_CURRENT_ALERT    *pAlert;
    FLOAT                       Value;
    USIGN8                      VarQuality;
    bool_t                      AlertDirectionUP = false;
    bool_t                      OutsideOfRange;
    bool_t                      InsideDeadBand;
    bool_t                      SetAlert;
    bool_t                      ClearAlert;
    bool_t                      AlertEnabled;
    USIGN32                     TimeHandlingIndex = TIME_HANDLING_STRUC_LO;
    bool_t                      astate = false;

    // Preset the data for the alert
    switch (AlertType)
    {
        case ALERT_TYPE_IPCUR_HI :
            pAlert              = &p_PTB->ip_drive_current_hi_alert;
            AlertEnabled        = (bool_t)pAlert->enable;
            AlertDirectionUP    = true;
            TimeHandlingIndex   = TIME_HANDLING_STRUC_HI;
            break;

        case ALERT_TYPE_IPCUR_LO :
            pAlert              = &p_PTB->ip_drive_current_lo_alert;
            AlertEnabled        = (bool_t)pAlert->enable;
            AlertDirectionUP    = false;
            TimeHandlingIndex   = TIME_HANDLING_STRUC_LO;
            break;

        default :
            AlertEnabled        = false;
            pAlert              = NULL;
            break;
    }

    if (pAlert != NULL)
    {   // Alert is present
        Value = p_PTB->ip_drive_current.value;
        pAlert->current = Value;                                     //Type mismatch between IP parameter and Alert
        VarQuality = p_PTB->ip_drive_current.status & QUALITY_MASK;  // Separate the Parameter Quality

        if (AlertEnabled)
        {   // Check Var Quality
            if ((VarQuality == SQ_BAD) || (VarQuality == SQ_UNCERTAIN))
            {   // Quality NOT GOOD
                AlertEnabled = false;
            }
        }

        if (AlertEnabled)
        {   // If the Alert enabled
            astate = ((const u8 *)&p_PTB->alert_state)[AlertType] != 0;
            if (AlertDirectionUP)
            {
                OutsideOfRange = ABOVE_THHOLD(Value,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand =  BELOW_DBAND(Value,pAlert->alert_point,pAlert->deadband);
            }
            else
            {
                OutsideOfRange = BELOW_THHOLD(Value,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand =  ABOVE_DBAND(Value,pAlert->alert_point,pAlert->deadband);
            }

            SetAlert   = !astate && OutsideOfRange;
            ClearAlert =   astate && InsideDeadBand;

            if (SetAlert)
            {   // Alert is NOT set and is outside -> SET ALERT!
                if (!Alert_IPCurHandle[TimeHandlingIndex].Latch)
                {
                    Alert_IPCurHandle[TimeHandlingIndex].Latch     = true;
                    Alert_IPCurHandle[TimeHandlingIndex].TimeStamp = osif_get_long_time_in_ms();
                }

                if (Alert_IPCurHandle[TimeHandlingIndex].Latch)
                {
                    u64 TimeDiff      = osif_get_long_ms_since(Alert_IPCurHandle[TimeHandlingIndex].TimeStamp);
                    float32 TimeDiffInSec = MS_TO_SEC((float32)TimeDiff);
                    if (TimeDiffInSec >= pAlert->duration_time)
                    {   // Time expired
                        astate = true;
                        AlertCacheSetAll(pAlert);
                    }
                }
            }
            else
            {
                Alert_IPCurHandle[TimeHandlingIndex].Latch     = false;
                Alert_IPCurHandle[TimeHandlingIndex].TimeStamp = 0ULL;
            }

            if (ClearAlert)
            {   // Alert is set and is inside deadband -- clear alert
                astate = false;
                AlertCacheClearCurr(pAlert);
                Alert_IPCurHandle[TimeHandlingIndex].Latch     = false;
                Alert_IPCurHandle[TimeHandlingIndex].TimeStamp = 0ULL;
            }
        }
        else
        {   // Alert disabled --
            AlertCacheClearAll(pAlert);
            Alert_IPCurHandle[TimeHandlingIndex].Latch     = false;
            Alert_IPCurHandle[TimeHandlingIndex].TimeStamp = 0ULL;
        }

    }
    else
    {   // Alert is not present
        // Nothing
    }

    return astate;
}

//----------------------------------------------------------------------------------

#if 0

static Alert_WorkingTime_t  Alert_WorkingTime =
{
    .TimeStamp_ms   = 0u,
    .TimeAccum_ms   = 0u,
};

#endif

static bool_t   AlertHandle_WorkingTime(T_FBIF_PTB           *p_PTB,
                                        AlertType_t           AlertType)
{
// TOTAL_TIME - in hours
// ALERT_POINT - in hours
// ALERT
// HISTORIC ALERT
// ENABLE

    _WORKING_TIME_ALERT *pAlert;
    bool_t              alertEnabled;
    bool_t              astate = false;

    if (AlertType == ALERT_TYPE_WORKTIME)
    {
        pAlert = &p_PTB->working_time_alert;
        alertEnabled = (bool_t)pAlert->enable;
    }
    else
    {
        pAlert       = NULL;
        alertEnabled = false;
    }

    if (pAlert != NULL)
    {   // Alert is present
        //transfer the working total_time to the alert
        pAlert->total_time = p_PTB->working_times.total_time;
        // Now process the Alert
        if (alertEnabled)
        {   // If the Alert enabled
            astate = (ABOVE_THHOLD(pAlert->total_time,pAlert->alert_point));
            if(astate)
            {
                AlertCacheSetAll(pAlert);
            }
            else
            {
                AlertCacheClearCurr(pAlert);
            }
        }
        else
        {   // Alert disabled --
            AlertCacheClearAll(pAlert);
        }

    }
    else
    {   // Alert is not present
        // Nothing
    }

    return astate;

}

static bool_t   AlertHandle_NearClosed(T_FBIF_PTB           *p_PTB,
                                        AlertType_t           AlertType)
{
    bool_t              astate = false;
    _NEAR_CLOSED_ALERT* pAlert;

    static u64 enter_time = 0ULL;
    static u64 total_time = 0ULL;

    if (AlertType == ALERT_TYPE_NEAR_CLOSE)
    {
        pAlert = &p_PTB->near_closed_alert;
    }
    else
    {   //Non of expected alert
        // Nothing
        pAlert = NULL;
    }

    bool_t AlertEnabled = false;
    if (pAlert != NULL)
    {
        AlertEnabled = (bool_t)pAlert->enable;

        if(AlertEnabled)
        {
#if TBALERTS_SELECTION_NEARCLOSED_CUTOFF != (TBALERTS_OPTIONS_NEARCLOSED_CUTOFF_OPTION_IGNORED)
            //Don't calculate the alert in CUTOFF on LOW side
            if(mn_IsAppFault(p_PTB, FAULT_POS_CUTOFF_LO))
            {
                AlertEnabled = false;
                astate = false;
                AlertCacheClearCurr(pAlert);
#if TBALERTS_SELECTION_NEARCLOSED_CUTOFF == (TBALERTS_OPTIONS_DEVIATION_CUTOFF_OPTION_CLEARED)
                //reset measuring
                enter_time = 0ULL;
#endif
            }
#endif
            USIGN8 sp_quality = p_PTB->working_sp.status & QUALITY_MASK;
            if (AlertEnabled
                && (sp_quality != SQ_UNCERTAIN)
                && (sp_quality != SQ_BAD)
                && (MODE_AUTO == p_PTB->mode_blk.actual || MODE_LO == p_PTB->mode_blk.actual || MODE_MAN == p_PTB->mode_blk.actual)
                 )
            {
                u64 current_time = osif_get_long_time_in_ms();

                if(BELOW_THHOLD(p_PTB->working_pos.value,pAlert->position_closed) && !mn_IsAppFault(p_PTB, FAULT_POS_CUTOFF_LO))
                {
                    //valve is near closed - start measuring the time
                    if (enter_time != 0)
                    {
                        total_time += (current_time - enter_time);

                        if (TIME_INSECOND_ONEHOUR <= MS_TO_SEC(total_time))
                        {
                            pAlert->near_closed++;
                            total_time = 0ULL;
                        }
                    }
                    //set initial time point
                    enter_time = current_time;
                }
                else
                {
                    //valve go out of 'near closed' position
                    //reset measuring
                    enter_time = 0ULL;
                }

                //check the alert
                astate = (ABOVE_THHOLD(pAlert->near_closed,pAlert->alert_point));
                if(astate)
                {
                    AlertCacheSetAll(pAlert);
                }
                else
                {
                    AlertCacheClearCurr(pAlert);
                }
            }
        }
        else
        {
            AlertCacheClearAll(pAlert); //only if disabled by config
            //It's unlike R2 where historic alert wasn't cleared
        }
    }
    return astate;
}

#if 0
/AK: Decentralize/Modularize alert suppression caused by advanced
//static
bool_t alert_EvalEnabledState(u8 rel_idx, u8 *enabled_flag, )
{
    BOOL en = *enabled_flag;
    bool_t ret = (en != FALSE);
    if(ret)
    {
        //Check "Advanced" to see if we must suppress the alert
        ret = ffcheck_WriteBitmap(rel_dx);
        if(!ret)
        {
            //Store it for posterity so that we don't come here again
            T_FBS_WRITE_PARAM_LOCAL mp_write;
            mp_write.rel_idx       = (u8)ptb_param_readonly[i].ptb_index;
            UNUSED_OK(ptb_param_readonly[i].alert_offset);
            //mp_write.dest          =
            //    (u8 *)((u8 *)p_PTB + ptb_param_readonly[i].alert_offset);
            en = 0;
            mp_write.length        = sizeof(u8);
            mp_write.source        = (u8 *)&en;
            mp_write.startup_sync        = TRUE;
            mp_write.subindex         = POST_WRITE_ACTION;
            (void)mn_fbs_write_param_loc(p_block_instance,&mp_write); //if fails (it won't) we'll come around again
        }
    }
    return ret;
}
#endif

//---------------------------------------------------------------------
// Time stamps for each

static Alert_TimeHandling_t Alert_Deviation =
{
    0ULL,     false
};

static bool_t   AlertHandle_Deviation(T_FBIF_PTB           *p_PTB,
                                      AlertType_t           AlertType)
{
// DEVIATION_VALUE
// ALERT_POINT
// DEADBAND
// TIME - in seconds
// ALERT
// HISTORIC ALERT
// ENABLE

    FLOAT               Deviation;
    FLOAT               AbsDeviation;
    _MN_DEVIATION_ALERT   *pAlert;
    USIGN8              VarQuality;
    bool_t              OutsideOfRange;
    bool_t              InsideDeadBand;
    bool_t              SetAlert;
    bool_t              ClearAlert;
    bool_t              AlertEnabled;
    bool_t              astate = false;

    if (AlertType == ALERT_TYPE_DEVIATION)
    {
        pAlert = &p_PTB->deviation_alert;
        AlertEnabled = (bool_t)pAlert->enable;
    }
    else
    {
        pAlert       = NULL;
        AlertEnabled = false;
    }

    if (pAlert != NULL)
    {
        if (AlertEnabled)
        {   // Check Var Quality
            VarQuality = p_PTB->working_pos.status;  // Separate the Parameter Quality
            if ((VarQuality == SQ_BAD) || (VarQuality == SQ_UNCERTAIN))
            {   // Quality NOT GOOD
                AlertEnabled = false;
            }

            VarQuality = p_PTB->working_sp.status;         // Separate the Parameter Quality
            if ((VarQuality == SQ_BAD) || (VarQuality == SQ_UNCERTAIN))
            {   // Quality NOT GOOD
                AlertEnabled = false;
            }
        }

        //AK: Update current deviation unconditionally
        Deviation = p_PTB->working_sp.value - p_PTB->working_pos.value;
        AbsDeviation = ABS(Deviation);
        pAlert->__deviation_value = AbsDeviation;

        if (AlertEnabled)
        {
            ClearAlert = false;

            //Don't calculate the alert in CUTOFF on either side
#if TBALERTS_SELECTION_DEVIATION_CUTOFF != TBALERTS_OPTIONS_DEVIATION_CUTOFF_OPTION_IGNORED
            if(mn_IsAppFault(p_PTB, FAULT_POS_CUTOFF_LO) || mn_IsAppFault(p_PTB, FAULT_POS_CUTOFF_HI))
            {
#if TBALERTS_SELECTION_DEVIATION_CUTOFF == TBALERTS_OPTIONS_DEVIATION_CUTOFF_OPTION_CLEARED
                ClearAlert = true; //restart alert calculation
#endif
#if TBALERTS_SELECTION_DEVIATION_CUTOFF == TBALERTS_OPTIONS_DEVIATION_CUTOFF_OPTION_SUSPENDED
                AlertEnabled = false;
#endif
            }
#endif
            if(AlertEnabled)
            {
                OutsideOfRange = ABOVE_THHOLD(AbsDeviation,pAlert->alert_point);        // In range or OUTSIDE?
                InsideDeadBand = BELOW_DBAND(AbsDeviation,pAlert->alert_point,pAlert->__deviation_deadband);

                astate = ((const u8 *)&p_PTB->alert_state)[AlertType] != 0;
                SetAlert   = !astate && OutsideOfRange;
                ClearAlert =   astate && InsideDeadBand;

                if (SetAlert)
                {
                    u64 CurrentTime = osif_get_long_time_in_ms();

                    if (!Alert_Deviation.Latch)
                    {   // Did we hit the condition FIRST time -- YES
                        Alert_Deviation.Latch     = true;
                        Alert_Deviation.TimeStamp = CurrentTime;
                    }

                    if (Alert_Deviation.Latch)
                    {   // Latched condition -- check the T/O

                        u64 TimeDiff = osif_get_long_ms_since(Alert_Deviation.TimeStamp);
                        if (MS_TO_SEC(TimeDiff) >= pAlert->time_threshold)
                        {   // Time expired
                            astate = true;
                            AlertCacheSetAll(pAlert);
                        }
                    }
                }
                else
                {
                    Alert_Deviation.Latch     = false;
                    Alert_Deviation.TimeStamp = 0LL;
                }
            }

            if (ClearAlert)
            {   // Alert is set and is inside deadband -- clear alert
                astate = false;
                Alert_Deviation.Latch     = false;
                Alert_Deviation.TimeStamp = 0LL;
                AlertCacheClearCurr(pAlert);
            }
        }
        else
        {   // Alert disabled --
            astate = false;
            AlertCacheClearAll(pAlert);
            Alert_Deviation.Latch     = false;
            Alert_Deviation.TimeStamp = 0LL;
        }
    }
    else
    {   // Alert is not present
        // Nothing
    }

    return astate;
}


//---------------------------------------------------------------------
// Talbe of function pointers for Alert processing

typedef struct AlertFunctionTable_t
{
    // Pointer to an Alert processing function
    bool_t      (* const pAlert_Process)(T_FBIF_PTB *p_PTB, AlertType_t AlertType);
    u16         AlertBitMap;
    u16 en_offs; //!< offset of the enable field
    u8 rel_idx;
} AlertFunctionTable_t;

static const AlertFunctionTable_t AlertFunctionTable[ALERT_TYPE_MAX] =
{
    [ALERT_TYPE_DEVIATION]      =
    {
        .pAlert_Process = AlertHandle_Deviation,
        .AlertBitMap = ALERT_INDEX(deviation_alert),
        .rel_idx = REL_IDX_PTB_DEVIATION_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, deviation_alert.enable),
    },

    [ALERT_TYPE_POSITION_HIHI]  =
    {
        .pAlert_Process = AlertHandle_Position,
        .AlertBitMap = ALERT_INDEX(position_hihi_alert),
        .rel_idx = REL_IDX_PTB_POSITION_HIHI_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, position_hihi_alert.enable),
    },
    [ALERT_TYPE_POSITION_HI]    =
    {
        .pAlert_Process = AlertHandle_Position,
        .AlertBitMap = ALERT_INDEX(position_hi_alert),
        .rel_idx = REL_IDX_PTB_POSITION_HI_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, position_hi_alert.enable),
    },
    [ALERT_TYPE_POSITION_LO]    =
    {
        .pAlert_Process = AlertHandle_Position,
        .AlertBitMap = ALERT_INDEX(position_lo_alert),
        .rel_idx = REL_IDX_PTB_POSITION_LO_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, position_lo_alert.enable),
    },
    [ALERT_TYPE_POSITION_LOLO]  =
    {
        .pAlert_Process = AlertHandle_Position,
        .AlertBitMap = ALERT_INDEX(position_lolo_alert),
        .rel_idx = REL_IDX_PTB_POSITION_LOLO_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, position_lolo_alert.enable),
    },

    [ALERT_TYPE_TRAVELACC_A]    =
    {
        .pAlert_Process = AlertHandle_TravelAcc,
        .AlertBitMap = ALERT_INDEX(travel_accumulation_a_alert),
        .rel_idx = REL_IDX_PTB_TRAVEL_ACCUMULATION_A_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, travel_accumulation_a_alert.enable),
    },
    [ALERT_TYPE_TRAVELACC_B]    =
    {
        .pAlert_Process = AlertHandle_TravelAcc,
        .AlertBitMap = ALERT_INDEX(travel_accumulation_b_alert),
        .rel_idx = REL_IDX_PTB_TRAVEL_ACCUMULATION_B_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, travel_accumulation_b_alert.enable),
    },

    [ALERT_TYPE_CYCLECNT_A]     =
    {
        .pAlert_Process = AlertHandle_Counter,
        .AlertBitMap = ALERT_INDEX(cycle_counter_a_alert),
        .rel_idx = REL_IDX_PTB_CYCLE_COUNTER_A_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, cycle_counter_a_alert.enable),
    },
    [ALERT_TYPE_CYCLECNT_B]     =
    {
        .pAlert_Process = AlertHandle_Counter,
        .AlertBitMap = ALERT_INDEX(cycle_counter_b_alert),
        .rel_idx = REL_IDX_PTB_CYCLE_COUNTER_B_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, cycle_counter_b_alert.enable),
    },

    [ALERT_TYPE_SUP_PRES_HI]    =
    {
        .pAlert_Process = AlertHandle_PressureHi,
        .AlertBitMap = ALERT_INDEX(supply_pressure_hi_alert),
        .rel_idx = REL_IDX_PTB_SUPPLY_PRESSURE_HI_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, supply_pressure_hi_alert.enable),
    },
    [ALERT_TYPE_SUP_PRES_LO]    =
    {
        .pAlert_Process = AlertHandle_PressureLo,
        .AlertBitMap = ALERT_INDEX(supply_pressure_lo_alert),
        .rel_idx = REL_IDX_PTB_SUPPLY_PRESSURE_LO_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, supply_pressure_lo_alert.enable),
    },
    [ALERT_TYPE_SUP_PRES_LOLO]  =
    {
        .pAlert_Process = AlertHandle_PressureLoLo,
        .AlertBitMap = ALERT_INDEX(supply_pressure_lolo_alert),
        .rel_idx = REL_IDX_PTB_SUPPLY_PRESSURE_LOLO_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, supply_pressure_lolo_alert.enable),
    },
    [ALERT_TYPE_TEMP_HI]        =
    {
        .pAlert_Process = AlertHandle_System,
        .AlertBitMap = ALERT_INDEX(temperature_hi_alert),
        .rel_idx = REL_IDX_PTB_TEMPERATURE_HI_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, temperature_hi_alert.enable),
    },
    [ALERT_TYPE_TEMP_LO]        =
    {
        .pAlert_Process = AlertHandle_System,
        .AlertBitMap = ALERT_INDEX(temperature_lo_alert),
        .rel_idx = REL_IDX_PTB_TEMPERATURE_LO_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, temperature_lo_alert.enable),
    },
    [ALERT_TYPE_SP_TIMEOUT]     =
    {
        .pAlert_Process = AlertHandle_SPTimeout,
        .AlertBitMap = ALERT_INDEX(setpoint_timeout_alert),
        .rel_idx = REL_IDX_PTB_SETPOINT_TIMEOUT_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, setpoint_timeout_alert.enable),
    },

    [ALERT_TYPE_IPCUR_HI]       =
    {
        .pAlert_Process = AlertHandle_IPCurrent,
        .AlertBitMap = ALERT_INDEX(ip_drive_current_alert_hi),
        .rel_idx = REL_IDX_PTB_IP_DRIVE_CURRENT_HI_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, ip_drive_current_hi_alert.enable),
    },
    [ALERT_TYPE_IPCUR_LO]       =
    {
        .pAlert_Process = AlertHandle_IPCurrent,
        .AlertBitMap = ALERT_INDEX(ip_drive_current_alert_lo),
        .rel_idx = REL_IDX_PTB_IP_DRIVE_CURRENT_LO_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, ip_drive_current_lo_alert.enable),
    },

    [ALERT_TYPE_WORKTIME]       =
    {
        .pAlert_Process = AlertHandle_WorkingTime,
        .AlertBitMap = ALERT_INDEX(working_time_alert),
        .rel_idx = REL_IDX_PTB_WORKING_TIME_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, working_time_alert.enable),
    },

    [ALERT_TYPE_NEAR_CLOSE]     =
    {
        .pAlert_Process = AlertHandle_NearClosed,
        .AlertBitMap = ALERT_INDEX(near_close_alert),
        .rel_idx = REL_IDX_PTB_NEAR_CLOSED_ALERT,
        .en_offs = MN_OFFSETOF(T_FBIF_PTB, near_closed_alert.enable),
    },
    [ALERT_TYPE_SENSOR_FAILED]  = {NULL,                            0u, 0u, 0u,},
    [ALERT_TYPE_PROCESSOR]      = {NULL,                            0u, 0u, 0u,},
    [ALERT_TYPE_VALVE_CONTROL]  = {NULL,                            0u, 0u, 0u,},
    [ALERT_TYPE_MISSION]        = {NULL,                            0u, 0u, 0u,},
    [ALERT_TYPE_AIR_SUPPLY]     = {NULL,                            0u, 0u, 0u,},
    [ALERT_TYPE_HARDWARE]       = {NULL,                            0u, 0u, 0u,},
};

//----------------------------------------------------------------------------------------------

// Number of reads of the state machine
#define MAX_CYCLES_OF_STATEMACHINE           (2u)

static u8       IPC_ReadsOfStateMachine     = 0u;
static bool_t   Alerts_Stable               = false;

void    Alert_IPCStateMachineExecuted(void)
{
    if (IPC_ReadsOfStateMachine >= MAX_CYCLES_OF_STATEMACHINE)
    {
        Alerts_Stable = true;
    }
    else
    {
        Alerts_Stable = false;
        IPC_ReadsOfStateMachine++;
    }
}

typedef struct trap_systime_t
{
    T_SYS_TIME systime;
    u16 CheckWord; //we use checksum to detect whether time is preserved and valid on reset
} trap_systime_t;

static MN_NO_INIT trap_systime_t trap_systime; //! Last captured timestamp goes to trap alert

/** Capture system time to assign to a trap alert (if of course a trap happens)
*/
static void systime_capture(void)
{
    trap_systime_t t;
    osif_get_system_time(&t.systime);
    STRUCT_CLOSE(trap_systime_t, &t);
    MN_ENTER_CRITICAL();
        trap_systime = t;
    MN_EXIT_CRITICAL();
}

/** \brief TB alerts processing.

Must be only called if TB target is not OOS
*/
u32     Execute_PTB_Alerts(const T_FBIF_BLOCK_INSTANCE * p_block_instance)
{
    T_FBIF_PTB* p_PTB = p_block_instance->p_block_desc->p_block;
    AlertType_t         AlertType;
    bool_t              funcval;
    u32                 TotalAlertBitMap = 0u;

    systime_capture();

    if (Alerts_Stable)
    {
        for (AlertType  = ALERT_FIRST_ALERT;
             AlertType != ALERT_TYPE_MAX;
             AlertType++)
        {
            bool_t (*f)(T_FBIF_PTB *p_PTB, AlertType_t AlertType) = AlertFunctionTable[AlertType].pAlert_Process;

            if (f != NULL)
            {
                //If alert is not writable, disable the function.
                bool_t enabled = ffcheck_WriteBitmap(AlertFunctionTable[AlertType].rel_idx);
                if(enabled)
                {
                    //processing function available and alert write is enabled:
                    {
                        funcval = f(p_PTB, AlertType);
                        if (funcval)
                        {
                            TotalAlertBitMap |= 1u << AlertFunctionTable[AlertType].AlertBitMap;
                        }
                    }
                }
                else
                {
                    // Make sure the alert is disabled.
                    u8 *en_p = (void *)p_PTB;
                    en_p += AlertFunctionTable[AlertType].en_offs;
                    if(*en_p != FALSE)
                    {
                        *en_p = FALSE;
                        //Save to NVMEM once so that we won't do it again
                        u8 rel_idx = AlertFunctionTable[AlertType].rel_idx;
                        if(rel_idx < ff2nvram_map_size)
                        {
                            nvramId_t nvid = ff2nvram_map[rel_idx].nvramid;
                            if(nvid != 0) //valid map
                            {
                                (void)nvmem_RequestWriteExt(nvid, 1U); //Always deferred
                            }
                        }
                    }
                }
            }
        }

        //replaced with alert_WriteAlertLog call in mnptb_ProcErrors() WriteEntry(p_block_instance, TotalAlertBitMap);
    }

    return TotalAlertBitMap;
}

// -------------------------------------------------------------------
// Functions to get the states of specific alerts

bool_t  Alert_AirSupply(const T_FBIF_PTB *p_PTB)
{
    const _SYSTEM_ALERT    *pAlert;
    bool_t                  AlertEnabled;
    bool_t                  retval = false;

    // Note, there are 3 Air Supply Alerts, we return logical OR of them
    pAlert = &p_PTB->supply_pressure_hi_alert;
    AlertEnabled = (bool_t)pAlert->enable;
    if (AlertEnabled)
    {
        retval = (retval || (bool_t)((const u8 *)&p_PTB->alert_state)[ALERT_TYPE_SUP_PRES_HI]);
    }

    pAlert = &p_PTB->supply_pressure_lo_alert;
    AlertEnabled = (bool_t)pAlert->enable;
    if (AlertEnabled)
    {
        retval = (retval || (bool_t)((const u8 *)&p_PTB->alert_state)[ALERT_TYPE_SUP_PRES_LO]);
    }

    pAlert = &p_PTB->supply_pressure_lolo_alert;
    AlertEnabled = (bool_t)pAlert->enable;
    if (AlertEnabled)
    {
        retval = (retval || (bool_t)((const u8 *)&p_PTB->alert_state)[ALERT_TYPE_SUP_PRES_LOLO]);
    }

    return retval;
}

bool_t  Alert_TravelDeviation(const T_FBIF_PTB *p_PTB)
{
    const _MN_DEVIATION_ALERT     *pAlert;
    bool_t                      AlertEnabled;
    bool_t                      retval = false;

    pAlert = &p_PTB->deviation_alert;
    AlertEnabled = (bool_t)pAlert->enable;
    if (AlertEnabled)
    {
        retval = (bool_t)((const u8 *)&p_PTB->alert_state)[ALERT_TYPE_DEVIATION];
    }
    return retval;
}

bool_t  Alert_PositionHI(const T_FBIF_PTB *p_PTB)
{
    const _POSITION_ALERT      *pAlert;
    bool_t                      AlertEnabled;
    bool_t                      retval = false;

    pAlert = &p_PTB->position_hi_alert;
    AlertEnabled = (bool_t)pAlert->enable;
    if (AlertEnabled)
    {
        retval = (bool_t)((const u8 *)&p_PTB->alert_state)[ALERT_TYPE_POSITION_HI];
    }
    return retval;
}

bool_t  Alert_PositionLO(const T_FBIF_PTB *p_PTB)
{
    const _POSITION_ALERT      *pAlert;
    bool_t                      AlertEnabled;
    bool_t                      retval = false;

    pAlert = &p_PTB->position_lo_alert;
    AlertEnabled = (bool_t)pAlert->enable;
    if (AlertEnabled)
    {
        retval = (bool_t)((const u8 *)&p_PTB->alert_state)[ALERT_TYPE_POSITION_LO];
    }
    return retval;
}

//----------------------------------------------------------------------------------------------
// Alert Logger implementation
// Definitions for the alert log READ parameter

#define     ALERT_LOG_CMD_READ      (0x00)
#define     ALERT_LOG_CMD_CLEAR     (0xFA)
#define     ALERT_LOG_DATA_CLEAR    (0x00)
#define     ALERT_LOG_TIME_CLEAR    (0x00)

#define     ALERT_INVALID_INDEX     (0xFFFFu)

// Read index -- init to
static      u16     alert_ReadBufferIndex = ALERT_INVALID_INDEX;

// Read buffer. On a specific command the Alart Log Data will be copied
// to this buffer for reading
static  _ALERT_LOG      alert_ReadBuffer[ALERT_LOG_NUM_ENTRIES];

// The data are supposed to be initalized from FRAM
static  AlertStoreStruc_t   alert_AlertStorage;

//----------------------------------------------------------------------------------------------
void get_AlertLogPtr(void** pp_value, u16* p_len)
{
    *pp_value = &alert_AlertStorage;
    *p_len = sizeof(alert_AlertStorage);
}

//----------------------------------------------------------------------------------------------
// Copy Alerts for Reading

static void CopyAlertLog4Read(void)
{
    u16     TransferReadIndex;
    u16     TransferWriteIndex;

    TransferWriteIndex = 0u;
    osif_disable_all_tasks();
    TransferReadIndex  = alert_AlertStorage.StoreBufferOldIndex;
    while (TransferWriteIndex < ALERT_LOG_NUM_ENTRIES)
    {
        // Read the data
        alert_ReadBuffer[TransferWriteIndex].alert_command = alert_AlertStorage.StoreDataSize;

        if (TransferWriteIndex < alert_AlertStorage.StoreDataSize)
        {   // Data entry is not empty
            alert_ReadBuffer[TransferWriteIndex].time    = alert_AlertStorage.Buffer[TransferReadIndex].time;
            alert_ReadBuffer[TransferWriteIndex].data    = alert_AlertStorage.Buffer[TransferReadIndex].data;
        }
        else
        {   // Data entry is empty
            alert_ReadBuffer[TransferWriteIndex].time.high = ALERT_LOG_TIME_CLEAR;
            alert_ReadBuffer[TransferWriteIndex].time.low  = ALERT_LOG_TIME_CLEAR;
            alert_ReadBuffer[TransferWriteIndex].data      = ALERT_LOG_DATA_CLEAR;
        }

        TransferWriteIndex++;
        TransferReadIndex++;
        if (TransferReadIndex >= ALERT_LOG_NUM_ENTRIES)
        {
            TransferReadIndex = 0u;
        }
    }

    // Reset the READ BUFFER
    alert_ReadBufferIndex = 0u;
    osif_enable_all_tasks();
}

static void alert_SubmitWrite(void)
{
    MN_ENTER_CRITICAL(); //critical foolishness for Lint
        ErrorCode_t err = logf_SubmitWrite(LOGF_ALERT_STORE_ID, &alert_AlertStorage, sizeof(alert_AlertStorage));
        MN_DBG_ASSERT(err == ERR_OK); //check correct use of protocol
        UNUSED_OK(err); //for release build
    MN_EXIT_CRITICAL(); //critical foolishness for Lint
}

static void StuffAlertEntry(const T_SYS_TIME *systime, u32 BitMap)
{
    TIME_VALUE_S                TimeVal;
    TimeVal.high = systime->high;
    TimeVal.low  = systime->low;


    if (alert_AlertStorage.StoreDataSize == 0u)
    {   // No data yet
        alert_AlertStorage.Buffer[alert_AlertStorage.StoreBufferNewIndex].data = BitMap;
        alert_AlertStorage.Buffer[alert_AlertStorage.StoreBufferNewIndex].time = TimeVal;
    }
    else
    {   // There are some data
        alert_AlertStorage.StoreBufferNewIndex++;                   // Next index
        if (alert_AlertStorage.StoreBufferNewIndex >= ALERT_LOG_NUM_ENTRIES)
        {
            alert_AlertStorage.StoreBufferNewIndex = 0u;
        }

        if (alert_AlertStorage.StoreDataSize >= ALERT_LOG_NUM_ENTRIES)
        {   // Pointing to the OLD entry (not empty)
            alert_AlertStorage.StoreBufferOldIndex++;
            if (alert_AlertStorage.StoreBufferOldIndex >= ALERT_LOG_NUM_ENTRIES)
            {
                alert_AlertStorage.StoreBufferOldIndex = 0u;
            }
        }

        alert_AlertStorage.Buffer[alert_AlertStorage.StoreBufferNewIndex].data = BitMap;
        alert_AlertStorage.Buffer[alert_AlertStorage.StoreBufferNewIndex].time = TimeVal;
    }

    if (alert_AlertStorage.StoreDataSize < ALERT_LOG_NUM_ENTRIES)
    {   // If teh buffer is not full yet -- ncrement data counter
        alert_AlertStorage.StoreDataSize++;
    }
    alert_SubmitWrite();
}

/** \brief Populates Alerts Log
\param BitMap - a bitmap of current alerts
*/
void alert_WriteAlertLog(u32 BitMap)
{
    T_SYS_TIME  SysTimeVal;

    osif_disable_all_tasks();
    if (BitMap != alert_AlertStorage.Buffer[alert_AlertStorage.StoreBufferNewIndex].data)
    {   // Change detected! Add entry

        // Get the current time
        osif_get_system_time(&SysTimeVal);
        StuffAlertEntry(&SysTimeVal, BitMap);

    }
    osif_enable_all_tasks();
}

// This function READS one entry from the Read Buffer. Supports Circular Reading
fferr_t     Alert_ReadAlertLogEntry(const T_FBIF_BLOCK_INSTANCE * p_block_instance,
                                    AlertBufferControl_t          Action)
{
    T_FBIF_PTB* p_PTB = p_block_instance->p_block_desc->p_block;

    if (alert_ReadBufferIndex == 0xFFFFu)
    {   // Read has not been initialized
        CopyAlertLog4Read();
    }

    osif_disable_all_tasks();
    // Initialized. Now do the read
    p_PTB->alert_log.alert_command = alert_ReadBuffer[alert_ReadBufferIndex].alert_command;
    p_PTB->alert_log.time    = alert_ReadBuffer[alert_ReadBufferIndex].time;
    p_PTB->alert_log.data    = alert_ReadBuffer[alert_ReadBufferIndex].data;

    if (Action == ALERT_AUTO_INC)
    {
        alert_ReadBufferIndex++;
        if (alert_ReadBufferIndex >= ALERT_LOG_NUM_ENTRIES)
        {
            alert_ReadBufferIndex = 0u;
        }
    }
    else
    {
        // No Action!!
    }
    osif_enable_all_tasks();

    return E_OK;
}

static void alert_ClearBuffer(void)
{
    u8              Index;

    osif_disable_all_tasks();
    for (Index = 0u;
         Index < ALERT_LOG_NUM_ENTRIES;
         Index++)
    {
        // Wipe out storage buffer
        alert_AlertStorage.Buffer[Index].time.high = ALERT_LOG_TIME_CLEAR;
        alert_AlertStorage.Buffer[Index].time.low  = ALERT_LOG_TIME_CLEAR;
        alert_AlertStorage.Buffer[Index].data      = ALERT_LOG_DATA_CLEAR;
        alert_AlertStorage.Buffer[Index].alert_command   = 0u;
    }

    // Clear indexes
    alert_AlertStorage.StoreBufferOldIndex = 0u;
    alert_AlertStorage.StoreBufferNewIndex = 0u;
    alert_AlertStorage.StoreDataSize       = 0u;
    osif_enable_all_tasks();
}

// This function WRITES one entry from the Read Buffer. Supports Circular Reading
fferr_t     Alert_WriteAlertLogEntry(const T_FBIF_BLOCK_INSTANCE * p_block_instance)
{
    fferr_t         Retval = E_OK;
    T_FBIF_PTB*     p_PTB = p_block_instance->p_block_desc->p_block;

    switch (p_PTB->alert_log.alert_command)
    {
        case ALERT_LOG_CMD_READ :
            // Prepare the Log Entry for reading
            CopyAlertLog4Read();
            break;

        case ALERT_LOG_CMD_CLEAR :
            // Clear the main Storage array
            alert_ClearBuffer();

            // Store data in NVRAM
            alert_SubmitWrite();

            // Clear the Read buffer
            CopyAlertLog4Read();
            break;

        default :
            // Do nothing
            // Retval = E_ERROR;       // Bad parameter
            break;
    }

    return Retval;
}


static const AlertType_t traptab[] = //!< Trap behavior configuration table
{
    [1+(-1)] = ALERT_TYPE_SENSOR_FAILED, //for asserts
    [1+TRAPID_NONE] = ALERT_TYPE_DEVIATION, //for normal reset
    [1+TRAPID_DATA_ABORT] = ALERT_TYPE_PROCESSOR,
    [1+TRAPID_PREFETCH_ABORT] = ALERT_TYPE_PROCESSOR,
    [1+TRAPID_FIQ] = ALERT_TYPE_PROCESSOR,
    [1+TRAPID_SWI] = ALERT_TYPE_MISSION, //registered reset
    [1+TRAPID_UNDEF_INSTRUCTION] = ALERT_TYPE_PROCESSOR,
    [1+TRAPID_STACK_OVFL] = ALERT_TYPE_HARDWARE,
    [1+TRAPID_RAMDATA] = ALERT_TYPE_AIR_SUPPLY,
    [1+TRAPID_WATCHDOG] = ALERT_TYPE_MISSION,
    [1+TRAPID_STACK_UNDRFL] = ALERT_TYPE_HARDWARE,
    [1+TRAPID_REPEAT_FATAL] = ALERT_TYPE_VALVE_CONTROL,
    [1+TRAPID_ACTIVATE] = ALERT_TYPE_VALVE_CONTROL,
};

static void trap2alertlog(void)
{
    s32 trapid;

    trapid = mn_GetAssertId();
    trapid = MAX(trapid+1, 0); //make traps 1-based with 0 for true asserts

    if((trapid < (s32)NELEM(traptab)) )
    {
        MN_ENTER_CRITICAL();
            //set alert corresponding to the trap
            if(whChecksum1__(&trap_systime.systime, MN_OFFSETOF(trap_systime_t, CheckWord)) != trap_systime.CheckWord)
            {
                systime_capture();
            }
        MN_EXIT_CRITICAL();
        u32 bmap = 1U<<traptab[trapid]; //lint !e641 Since when enum can't be a shift count?!
        osif_disable_all_tasks();
        StuffAlertEntry(&trap_systime.systime, bmap);
        osif_enable_all_tasks();
    }
}


void    Alert_InitAlertLog(void)
{
    // Read the Storage Array from NVRAM -- all 32 entries, indexes, size
    u16 len = sizeof(alert_AlertStorage);
    ErrorCode_t err = logf_Retrieve(&alert_AlertStorage, &len, LOGF_ALERT_STORE_ID, 0);

    // Check if the data are legitimate -- size and indexes
    if ((err != ERR_OK) || //no file or corrupted file
        (alert_AlertStorage.StoreDataSize > ALERT_LOG_NUM_ENTRIES) ||
        (alert_AlertStorage.StoreBufferNewIndex >= ALERT_LOG_NUM_ENTRIES) ||
        (alert_AlertStorage.StoreBufferOldIndex >= ALERT_LOG_NUM_ENTRIES))
    {   // Data size is NOT valied or indexes are not valid.
        // clear the data
        alert_ClearBuffer();

        // Clear the Read buffer
        CopyAlertLog4Read();
    }

    //Addition for traps
    trap2alertlog();
}

/** \brief Adds
*/
void Alert_ExpireAssertHook(void)
{
    osif_disable_all_tasks();
    StuffAlertEntry(&trap_systime.systime, 0U /*temporarily(?)*/);
    osif_enable_all_tasks();
}

//----------------------------------------------------------------------------------------------
//                           -- -- -- -- End of file -- -- -- --
//----------------------------------------------------------------------------------------------

