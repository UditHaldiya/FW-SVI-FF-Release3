/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_ext_analysis.c
    \brief HART glue layer for control extended analysis command
           ("X-ray view" into control process)

    CPU: Any

    OWNER: SK

    \ingroup HARTapp
*/


#include "mnwrap.h"
#include "hartfunc.h"
#include "hartdef.h"
#include "bufutils.h"
#include "ext_analysis.h"

#include "adtype.h"
#include "adtbl.h"
#include "sysio.h"
#include "pressures.h"
#include "tempr.h"
#include "posint.h"
#include "projectdef.h"
#if FEATURE_REMOTE_POSITION_SENSOR == FEATURE_REMOTE_POSITION_SENSOR_AVAILABLE
#include "posext.h"
#endif //FEATURE_REMOTE_POSITION_SENSOR
#include "position.h"
#include "posctlmode.h"


/**
    \brief Extended Analysis Data Collector
           Note:
           This command is allowed in all modes
*/
//this is a command shell -- does nothing
s8_least hartcmd_ExtendedAnalysis(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hart_Command_242_ExtendedAnalysis() ------

//subcommand 0 -- returns a current version
//  first word -- version of the firmware, such as: 0xA8 -- Alpha_8, 0xB2 -- Beta_2, 0xC1 -- Release Candidate_1
//  second word -- if needed, the sub-version within the firmware version, if not needed -- zero
#define CMD242_VERSION_FW  0xB9    /** TFS:5899 */
#define CMD242_VERSION_CMD  0x01 //row-based tempcomp and no magnet comp

s8_least hartcmd_ExtendedAnalysisVersion(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ExtendedAnalysisVersion_t *d = (void *)dst;

    util_PutU16(d->eav_Version[0], (u16)CMD242_VERSION_FW);     //FW version
    util_PutU16(d->eav_Version[1], (u16)CMD242_VERSION_CMD);    //sub-version

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hartcmd_ExtendedAnalysisVersion() ------


//subcommand 1 -- working horse
s8_least hartcmd_ExtendedAnalysisDataCollector(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ExtendedAnalysisDataCollector_t *d = (void *)dst;
    ExtAnalysParams_t Params;

    ctlmode_t ctlmode;
    s32 sp;

    ctlmode = mode_GetEffectiveControlMode(&sp); //provides conditioned setpoint and translated control mode

    //obtain pointer to parameters from control.c
    control_FillExtAnalysParams(&Params);

    //assign the whole structure to HART buffer
    util_PutU8(d->ControlAlgorithmMode[0], (u8)ctlmode);
    util_PutS16(d->eadc_RateLimitedSetpoint[0], (s16)sp);

    (void)mode_GetIntendedControlMode(&sp); //user setpoint
    util_PutS16(d->eadc_UserSetpoint[0], (s16)sp);

    util_PutS16(d->eadc_PositionScaled[0], vpos_GetScaledPosition());
    util_PutU16(d->eadc_PWM[0], sysio_GetRealPWM());
    /** TFS:4016 **/  /** TFS:4226 */
    util_PutU16(d->eadc_CtlOutput[0], Params.CtlOutput);

    const BoardPressure_t *pr = pres_GetRawPressureData();
    util_PutS16(d->eadc_P_pilot[0], pr->Pressures[PRESSURE_PILOT_INDEX]);
    util_PutS16(d->eadc_P_1[0], pr->Pressures[PRESSURE_ACT1_INDEX]);
    util_PutS16(d->eadc_P_2[0], pr->Pressures[PRESSURE_ACT2_INDEX]);
    util_PutS16(d->eadc_P_supply[0], pr->Pressures[PRESSURE_SUPPLY_INDEX]);

    util_PutS16(d->eadc_AvgErr[0], Params.AvgErr);
    util_PutS16(d->eadc_MinErr[0], Params.MinErr);
    util_PutS16(d->eadc_MaxErr[0], Params.MaxErr);
    util_PutU16(d->eadc_PosComp[0], Params.PosComp);
    util_PutS16(d->eadc_P_element[0], Params.P_term);
    util_PutS16(d->eadc_D_element[0], Params.D_term);
    util_PutS16(d->eadc_Boost_element[0], Params.Boost_term);
    util_PutS16(d->eadc_Fast_elements[0], Params.Fast_terms);
    util_PutS32(d->eadc_Integral[0], Params.Integral);
    util_PutU16(d->eadc_Bias[0], Params.Bias);
    util_PutU16(d->eadc_Overshoots[0], Params.Overshoots);
    util_PutU16(d->eadc_JigglesPassed[0], Params.JigglesPassed);
    util_PutU16(d->eadc_CalcPeriod[0], Params.CalcPeriod);    // TFS:5746
    util_PutU8(d->eadc_IntegalCount[0], Params.IntegalCount);
    util_PutU8(d->eadc_CtrlByte[0], Params.CtrlByte);
    util_PutU16(d->eadc_BitPack[0], Params.BitPack);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hartcmd_ExtendedAnalysisDataCollector() ------


//subcommand 2 -- returns position propagation chain:
//ADraw --> TempComp --> Magnetic Corrected --> Linearized --> Std Scaled
s8_least hartcmd_ExtendedAnalysisPosPropagation(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ExtendedAnalysisPosPropagation_t *d = (void *)dst;

    OffsetSpanS32_t curveseg;
    PosState_t PosState;
    (void)pos_GetPosState(&PosState);

    u8 index;
    s32 pos_prelin;
#if FEATURE_REMOTE_POSITION_SENSOR == FEATURE_REMOTE_POSITION_SENSOR_AVAILABLE
    if(ad_GetSensorType(NULL)->IsRemotePositionSensor)
    {
        posext_GetInstantTempCompParams(&curveseg);
        index = AD_POS_REM;
        pos_prelin = PosState.hardpos;
    }
    else
#endif //FEATURE_REMOTE_POSITION_SENSOR
    {
        posint_GetInstantTempCompParams(&curveseg);
        index = AD_POS_INT;
        pos_prelin = posint_GetPreLinearized();
    }
    util_PutS32(d->eapp_posTCcalibrated[0], pos_prelin);
    const AdDataRaw_t* pRawData = bios_GetAdRawData();
    util_PutS32(d->eapp_posADraw[0], pRawData->AdValue[index]);
    util_PutU16(d->eapp_posLinearized[0], (u16)PosState.hardpos);
    util_PutS32(d->eapp_posScaled[0], PosState.pos_adjusted);

    const BoardPressure_t* pBoardPressure = pres_GetPressureData();
    util_PutS16(d->eapp_P_pilot[0], pBoardPressure->Pressures[PRESSURE_PILOT_INDEX]);

    util_PutS32(d->eapp_temperRaw[0], pRawData->AdValue[AD_TEMP_INT]);
    util_PutS32(d->eapp_temperTCcomp[0], tempr_GetInstantTempr(0));

    util_PutU16(d->eapp_PWM[0], sysio_GetRealPWM());

    util_PutS32(d->eapp_posTCspan[0], curveseg.span);
    util_PutS32(d->eapp_posTCoffset[0], curveseg.offset);

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
} //-----  end of hartcmd_ExtendedAnalysisPosPropagation() ------



