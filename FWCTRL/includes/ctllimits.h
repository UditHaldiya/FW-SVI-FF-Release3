/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ctllimits.h
    \brief API of Limits for Position Control

     CPU: Any

    OWNER: AK

\ingroup control
*/
#ifndef CTLLIMITS_H_
#define CTLLIMITS_H_

//lint -d__SIGNED_INT_MIN__=(-0x7FFFFFFF-1) for now
#include <limits.h>

#include "errcodes.h"
#include "param.h"
#include "posctlmode.h"

/** This struct is only of interest to control. It may need to be further
split into tight shutoff and setpoint limits parts.
Historically, it's been derived from ConfigurationData_t (ver. 129)
*/
typedef struct CtlLimits_t
{
    u8 EnableTightShutoff[Xends]; //!< Tight shutoff enable flags
    pos_t TightShutoff[Xends];       //!< Tight shutoff limits in % open
    u8 EnableSetpointLimit[Xends];   //!< Lower and Upper setpoint limits enable flags
    pos_t SetpointLimit[Xends];      //!< Lower and Upper setpoint limit in % open
    u8 EnableSetpointRateLimit[Xends];   //!< Lower and Upper setpoint rate limits enable flags
    pos_t SetpointRateLimit[Xends];      //!< Lower and Upper setpoint rate limit in % travel
    u8 Protected;           //!< a flag indicating whether temporary changes are enabled
    u16 CheckWord;
} CtlLimits_t;

/*
typedef enum ProtectTest_t ProtectTest_t;
enum ProtectTest_t
{
    PROTECTED_LIMITS,
    NO_LIMITS_SET,
    UNPROTECTED_LIMITS
};
*/

//For interface layer (UI and HART)
#define TIGHT_SHUTOFF_MASK 1U
#define TIGHT_SHUTOFF_VALUE_ON TIGHT_SHUTOFF_MASK
#define TIGHT_SHUTOFF_VALUE_OFF 0U

extern const pos_t spposlimits_range[Xends][Xends];
extern const pos_t tso_limits[Xends];
extern const pos_t tco_limits[Xends];
extern const pos_t spratelim_range[Xends];

SAFEGET(control_GetLimits, CtlLimits_t);
SAFESET(control_SetLimits, CtlLimits_t);

extern const CtlLimits_t *ctllim_GetPermLimits(CtlLimits_t *dst);

//gone static extern ErrorCode_t control_SetTentativeLimits(const CtlLimits_t *lims);
typedef enum ProtectTest_t ProtectTest_t;
enum ProtectTest_t
{
    PROTECTED_LIMITS,
    NO_LIMITS_SET,
    UNPROTECTED_LIMITS
};

extern ProtectTest_t  control_TestProtectLimits(void);
//gone static: extern ErrorCode_t control_TestCtlLimits(const CtlLimits_t *lims);
extern procresult_t control_ProcWithNoLimits(procresult_t (*procf)(s16 *procdetails), s16 *procdetails);

#define SETPOINT_INVALID INT_MIN
#define POS_SETPOINT_LOW_INT INT_PERCENT_OF_RANGE(POS_SETPOINT_LOW)
#define POS_SETPOINT_HIGH_INT INT_PERCENT_OF_RANGE(POS_SETPOINT_HIGH)

/** defines FBO OS Adjust */ /*TFS:4713 - moved SP limits here from hartfunc.h*/
#define POS_SETPOINT_LOW -5.0F
//should be 5% higher than max which is 167 due to open stop adj
//#define POS_SETPOINT_HIGH 160.0F
#define POS_SETPOINT_HIGH 175.0F

//Setpoint Rate limits in %/s
#define SP_RATE_LIMIT_LOW 0.2 //reverse engineered from 3.1.x 2 counts/ctl cycle = 0.81380208333333333333333333333333
#define SP_RATE_LIMIT_HIGH 199.98 //reverse engineered from 3.1.x 246 counts/ctl cycle = 100.09765625
/*the limits are arbitrary and can be changed within type range to requirements
*/



extern const pos_t positionsp_range[Xends];

extern void ctllim_Reinit(pos_least_t sp);

extern ctlmode_t ctllim_ConditionControlMode(ctlmode_t ctlmode, s32 *pSetpoint);
extern pos_t ctllim_GetRangeBoundedSetpoint(void);

extern ErrorCode_t cnfg_DisableLimits(void);
extern void cnfg_ReEnableLimits(void);
extern ErrorCode_t control_SetTentativeLimits(const CtlLimits_t *lims);


//---------------- old-style NVMEM interface -------------------
#ifdef OLD_NVRAM
extern void  ctllim_SaveControlLimits(void);
extern void  ctllim_InitControlLimits(InitType_t Type);
#endif

#endif //CTLLIMITS_H_
/* This line marks the end of the source */
