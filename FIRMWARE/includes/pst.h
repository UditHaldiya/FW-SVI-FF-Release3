/*
Copyright 2005-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file pst.h
    \brief header for partial stroke test implementation

    CPU: Any

    OWNER: Larry Schoonover

    \ingroup PST
*/
#ifndef PST_H_
#define PST_H_

#include "errcodes.h"
#include "process.h"
//#include "pressures.h"
#include "pressuredef.h"
#include "position.h"
#include "signaldef.h"

#if 0
#define SP_ESD_DEFAULT_ATO INT_PERCENT_OF_RANGE(105.0) //!< 105% default setpoint for ATO valves
#define SP_ESD_DEFAULT_ATC  INT_PERCENT_OF_RANGE(-5.0) //!< -5% default setpoint for ATC valves
#define SP_ESD_DEFAULT ((cnfg_GetComputedConfigurationData()->bATO)?SP_ESD_DEFAULT_ATO:SP_ESD_DEFAULT_ATC)
#define SP_ESD_DEFAULT_LOWIP ((cnfg_GetComputedConfigurationData()->bATO)?SP_ESD_DEFAULT_ATC:SP_ESD_DEFAULT_ATO)
#define SP_CLOSE  INT_PERCENT_OF_RANGE(0.0) //!< 0%  setpoint
#define SP_OPEN   INT_PERCENT_OF_RANGE(100.0) //!< 100%  setpoint
#define RESP_TEST_STEP (INT_PERCENT_OF_RANGE(1.0))

#define RESP_TEST_LIMIT(bATO) ((bATO)?(STANDARD_100 - EXTRA_POS_OPEN):EXTRA_POS_CLOSED)
#define TEST_RESP_LIMIT(pos, bATO) (bATO?((pos)>(RESP_TEST_LIMIT(bATO))):((pos)<(RESP_TEST_LIMIT(bATO))))
#define TEST_CHANGE_SETPOINT(sp, step, bATO) (bATO?((sp)-(step)):((sp)+(step)))

#define SAVE_START_INDEX 0
#define SAVE_END_INDEX 0
#define SAVE_SPEED_INDEX 1
#define SAVE_IP_INDEX 1
#define SAVE_SUPPLY_INDEX 2
#define SAVE_PRESSURE_INDEX 2
#define SAVE_TIME_INDEX 3
#define PST_NUMBER_INIT_PARAM 4

#define MAX_PST_BYTES_EACH_WAY 500
#define DELIMITER_ENTRY (-1)
#define CHANNELS_PER_SAMPLE 2
#define HEADER_ENTRIES (PST_NUMBER_INIT_PARAM * 2)
#define BYTES_PER_CHANNEL (sizeof(diag_t))
#define MAX_SAMPLES ((MAX_PST_BYTES_EACH_WAY/(CHANNELS_PER_SAMPLE * BYTES_PER_CHANNEL)) - (PST_NUMBER_INIT_PARAM+1))

//pst error codes
#define PST_NO_ERROR 0
#define PST_TIMEOUT 1
#define PST_MAX_PRESURE 2
#endif

typedef u16 PstFreeze_t; //! Bitmap of freeze options so as to not get signaling excited about PST

//lint -esym(755, PST_FREEZE_*) not used PSTConf_t::FreezeOptions values
#define PST_FREEZE_AO 0x0001U
#define PST_FREEZE_DO 0x0002U
#define PST_FREEZE_SPRANGE 0x0004U //! Keeps range and cut-off for the time of PST; cancels PST if range is infringed upon
#define PST_FREEZE_SPRATE 0x0008U //! Enforces rate limit if enabled
#define PST_FREEZE_CUTOFF 0x0010U //! Enforces cut-off limits if enabled
#define PST_FREEZE_DEADZONE 0x0020U //! Enforces control deadzone if enabled
#define PST_FREEZE_STABLE 0x0040U //! Enforces "stabilize" step which otherwise returns immediately

//PST patterns
#define PST_PATTERN_DU 0
#define PST_PATTERN_DUD 1
#define PST_PATTERN_DUDU 2
#define PST_PATTERN_UD 3
#define PST_PATTERN_UDU 4
#define PST_PATTERN_UDUD 5


typedef struct PSTConf_t
{
    pos_t sp_threshold;  //!< Aborts PST if (process) sp walks outside the threshold
    pos_t travel;             //!< travel from stop for pst test (in std units)
    u32 maxtime;            //!< time in milliseconds - if exceeded pst test failed
    s16 ramp_speed;         //!< ramp speed in %/sec
    pres_t PresAbortActuator;         //!< main pressure threshold outside which we abort (std units)
    pres_t PresAbortPilot;         //!< pilot pressure threshold outside which we abort (std units)
#if 0 //When needed, move to a different struct
    pres_t FrictionLowLimit;
    pres_t FrictionLimit;
    pres_t BreakoutLimit;
    pres_t DroopLimit;
#endif //0
    u16 LeadTime; //breakout/stabilization time in ms
    u16 DwellTime;
    u32 StrokeTmout;
    u16 datamap; //!< what we collect
    u16 skip_count;
    PstFreeze_t FreezeOptions;
    u8 pattern;
    u16 CheckWord;
} PSTConf_t;

//Required project-specific interfaces
/** \brief A project-specific plugin which freezes signaling interfaces
so that a running PST doesn't trigger false/unwanted signaling
\param freeze_options - a bitmap of predefined signaling to freeze
\return bitmap of interfaces actually frozen
*/
extern ErrorCode_t pst_Freeze(PstFreeze_t freeze_options);
/** \brief A project-specific plugin which unfreezes signaling interfaces
so that a running PST doesn't trigger false/unwanted signaling
\param freeze_options - a bitmap of predefined signaling to freeze
\return bitmap of interfaces actually frozen
*/
extern void pst_UnFreeze(PstFreeze_t freeze_options);

/* pst_Freeze and pst_UnFreeze absolutely must be used in pairs.
We provide a standard macro wrappers to ensure that
*/
#define PST_FREEZE(freeze_options) do {PstFreeze_t PstFreeze_freeze=freeze_options; (void)pst_Freeze(freeze_options); { CONST_ASSERT(0==0)
//lint -emacro(717, PST_UNFREEZE) enable do while(0)
#define PST_UNFREEZE() } pst_UnFreeze(PstFreeze_freeze); } while(false)

#if 0
typedef struct PSTComputedData_t
{
   s16 PassFailFlag;        //!< 0 for pass, other value indicates failure cause
   pres_t nFriction;           //!< Computed valve friction in std pressure units
   pres_t LSpringRange;         //!< pressure where valve is 0% (100% for atc)
   pres_t USpringRange;         //!< pressure where valve is 100% (0% for atc)
   pres_t nBreakAwayPressure;  //!< pressure required to move valve off stops
   pres_t nDroop;              //!< drop in supply pressure during response test
   s16 SpeedExhaust; //!< psi/s  (or other pressure units) exhausting direction
   s16 SpeedFill;    //!< psi/s  (or other pressure units) filling direction
   u16 PointsDown;          //!< number of points in the down pst signature
   u16 Reserved;            //!< reserved for future use
   //u16 PointsTotal; these will be automatically added by the save routine         //!< number of points in the pst signature
   //u16 PruneScale;  these will be automatically added by the save routine         //!< the number of times the data was pruned
} PSTComputedData_t;

typedef struct PSTFactoryChangeable_t
{
   u32 Resp_Test_Timeout;       //!< timeout waiting for pressure to change in response test
   s16 Resp_Test_Pres_Dif;       //!<  STD_FROM_PSI(8)  //8 psi
   s16 Resp_Test_Pres_Dif_End;   //!<  STD_FROM_PSI(2)  //2 psi
   s16 Pos_Error_Allowance;     //!<  error limit in pst test  INT_PERCENT_OF_RANGE(2.0)
   s16 Low_Position;            //!<  lower useable position for friction calc  INT_PERCENT_OF_RANGE(3.0)
   s16 High_Position;            //!<  upper useable position for friction calc  INT_PERCENT_OF_RANGE(97.0)
   s16 Movement_Detection;       //!< limit for detection of valve movement  INT_PERCENT_OF_RANGE(1.0)
   s16 AI_PST_Band;              //!< deadband for AI invocation of pst  STD_FROM_MA(.2)/2
   u16 CheckWord;
} PSTFactoryChangeable_t;
#define RESP_TEST_TIMEOUT (TICKS_FROM_MS(15000)) //15 sec
#define RESP_TEST_PRES_DIF STD_FROM_PSI(8)  //8 psi
#define RESP_TEST_PRES_DIF_END STD_FROM_PSI(2)  //2 psi
#define POS_ERROR_ALLOWANCE INT_PERCENT_OF_RANGE(2.0)
#define LOW_POSITION INT_PERCENT_OF_RANGE(3.0)
#define HIGH_POSITION INT_PERCENT_OF_RANGE(97.0)
#define MOVEMENT_DETECTION INT_PERCENT_OF_RANGE(1.0)
#define AI_PST_BAND     STD_FROM_MA(.2)

#define INTERVAL_MAX DAYS_PER_YEAR    //pst interval cant be greater than 1 year
#define INTERVAL_MIN 1

#define PST_FRICTION_LIMIT_LOW STD_FROM_PSI(0.0)
#define PST_FRICTION_LIMIT_HIGH STD_FROM_PSI(30.0)
#define PST_BREAKOUT_LIMIT_LOW STD_FROM_PSI(0.0)
#define PST_BREAKOUT_LIMIT_HIGH STD_FROM_PSI(30.0)
#define PST_DROOP_LIMIT_LOW STD_FROM_PSI(0.0)
#define PST_DROOP_LIMIT_HIGH STD_FROM_PSI(30.0)
#endif //0

#define PST_MIN_PRES_ABORT_ACT STD_FROM_PSI(-120.0)
#define PST_MAX_PRES_ABORT_ACT STD_FROM_PSI(120.0)   //increased to 150 as per Sandro
#define PST_MIN_PRES_ABORT_PILOT STD_FROM_PSI(-120.0)
#define PST_MAX_PRES_ABORT_PILOT STD_FROM_PSI(120.0)   //increased to 150 as per Sandro

#define PST_TRAVEL_LOW INT_PERCENT_OF_RANGE(0.1)
#define PST_TRAVEL_HIGH INT_PERCENT_OF_RANGE(30.0)
#define PST_TIME_LIMIT_LOW (5*ONE_SECOND)
#define PST_TIME_LIMIT_HIGH (300*ONE_SECOND)
#define PST_DWELL_LIMIT_LOW 2
#define PST_DWELL_LIMIT_HIGH 60
#define PST_RAMP_SPEED_LOW STD_FROM_PERCENT(0.2)
#define PST_RAMP_SPEED_HIGH STD_FROM_PERCENT(199.99)

extern const PSTConf_t *diag_GetPstData(PSTConf_t *dst);
extern ErrorCode_t diag_SetPstData(const PSTConf_t *src);
UNTYPEACC(diag_SetPstData, diag_GetPstData);

// ----- ranges of data ---------
//extern const s16 pstTestTime_range[Xends];
extern const pos_t pstTravel_range[Xends];
extern const pos_t pstRampSpeed_range[Xends];
extern const pos_t pstSpThreshold_range[Xends];
extern const pres_t pstPresActuator_range[Xends];
extern const pres_t pstPresPilot_range[Xends];

#if 0
extern const pres_t pstFrictionLimit_range[Xends];
extern const pres_t pstBreakoutLimit_range[Xends];
extern const pres_t pstDroopLimit_range[Xends];
#endif

//processs support
extern procresult_t diag_PartialStrokeTest(s16 *procdetails);
// *procdetails completion codes
// not used #define PSTDETAILS_FAILED_INTERNAL 1
// not used #define PSTDETAILS_TRAVEL_OUTSIDE_RANGE 2
#define PSTDETAILS_USER_CANCELED 3
#define PSTDETAILS_STABILIZE_TIMEOUT 4
#define PSTDETAILS_OVERALL_TIMEOUT 5
#define PSTDETAILS_INHIBITING_FAULTS 6
#define PSTDETAILS_NOT_ALLOWED 7

typedef struct pst_abort_t //! A type for monitoring PST abort
{
    s32 setpoint;
    pres_t pilot_base;
    pres_t act_base;
    bool_t active;
    u16 CheckWord;
} pst_abort_t;
extern void pst_InitAbort(const pst_abort_t *src);


#define PST_MAX_PATTERN_STEPS 6  //! Max number of ramp steps in a pattern

#endif  //PST_H_

/* This line marks the end of the source */
