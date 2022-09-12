/*
Copyright 2010 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_posctl.c
    \brief Glue functions related to position control HART support

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "errcodes.h" //not needed in the trunk
#include "selftune.h"
#include "hartpriv.h"
#include "hartapputils.h"
#include "process.h"
#include "ctllimits.h"
#include "hartfunc.h"
#include "hartdef.h"
#include "bufutils.h"
#include "fpconvert.h"

static s8_least GetSetTuningParameters(TuneData_t* pSelfTuningParameters, const AutotuneParams_t *s);

/** \brief Returns index of the current PID parameters set
*/
s8_least hartcmd_ReadControlParametersSelector(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadControlParametersSelector_t *d = (void *)dst;
    util_PutU8(d->PIDDataSelector[0], posctl_GetCtlSetIndex());
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

static s8_least hartcmd_ReadControlParams(const PIDData_t* pPIDData, ControlParams_t *d)
{
    if(pPIDData == NULL)
    {
        return HART_INVALID_SELECTION;
    }

    util_PutU16(d->PIDDataP[0], (u16)(pPIDData->P));
    util_PutU16(d->PIDDataI[0], (u16)(pPIDData->I));
    util_PutU16(d->PIDDataD[0], (u16)(pPIDData->D));
    util_PutU16(d->PIDDataPADJ[0], (u16)(pPIDData->PAdjust));
    util_PutU16(d->PIDDataBETA[0], (u16)(pPIDData->Beta));
    util_PutU16(d->PIDDataPOS_COMP[0], (u16)(pPIDData->PosComp));
    util_PutS16(d->PIDDataDEADZONE[0], pPIDData->DeadZone);
    util_PutU16(d->PIDDataNONLIN1[0], (u16)(pPIDData->Band));

    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/**
\brief Returns the PID values.

Notes:
This command is allowed in all modes, even when write busy or process busy is set
*/
s8_least hartcmd_ReadControlParametersExt(const u8 *src, u8 *dst)
{
    Rsp_ReadControlParametersExt_t *d1 = (void *)dst;
    ControlParams_t *d = (void *)d1->ControlParams[0];

    const Req_ReadControlParametersExt_t *s = (const void *)src;
    u8 selector = util_GetU8(s->PIDDataSelector[0]);
    const PIDData_t* pPIDData;
    pPIDData = tune_GetPIDData(selector, NULL);

    UNUSED_OK(d1->PIDDataSelector); //rely on HART framework to fill
    return hartcmd_ReadControlParams(pPIDData, d);
}

s8_least hartcmd_ReadCurrentControlParametersSet(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadCurrentControlParametersSet_t *d1 = (void *)dst;
    ControlParams_t *d = (void *)d1->ControlParams[0];
    const PIDData_t *pPIDData = tune_GetCurrentPIDData(NULL);
    return hartcmd_ReadControlParams(pPIDData, d);
}

/**
\brief Saves the PID parameters

Notes:
Only valid in OOS mode.
*/
s8_least hartcmd_WriteControlParameters(const u8 *src, u8 *dst)
{
    PIDData_t PIDData;
    s8_least ret;

    const Req_WriteControlParameters_t *s1 = (const void *)src;
    const ControlParams_t *s = (const void *)s1->ControlParams[0];


    //get the data
    u8 selector = util_GetU8(s1->PIDDataSelector[0]);
    PIDData.P = util_GetU16(s->PIDDataP[0]);
    PIDData.I = util_GetU16(s->PIDDataI[0]);
    PIDData.D = util_GetU16(s->PIDDataD[0]);
    PIDData.PAdjust = util_GetS16(s->PIDDataPADJ[0]);
    PIDData.Beta = util_GetS16(s->PIDDataBETA[0]);
    PIDData.PosComp = util_GetS16(s->PIDDataPOS_COMP[0]);
    PIDData.DeadZone = util_GetS16(s->PIDDataDEADZONE[0]);
    PIDData.Band = util_GetU16(s->PIDDataNONLIN1[0]);
    //PIDData.NonLin = util_GetS16(s->PIDDataNONLIN2[0]);
    //PIDData.Reserved1 = util_GetS16(s->PIDDataRES1[0]);
    //PIDData.Reason = util_GetS16(s->PIDDataRES2[0]);

    ErrorCode_t err = tune_SetPIDData(selector, &PIDData);
    if(err != ERR_OK)
    {
        ret = err2hart(err);
    }
    else
    {
        Rsp_WriteControlParameters_t *d = (void *)dst;
        UNUSED_OK(d->PIDDataSelector); //rely on HART framework to fill
        UNUSED_OK(d->ControlParams); //rely on read function to fill

        ret = hartcmd_ReadControlParametersExt(src, dst);
    }
    return ret;
}

/**\brief saves the tuning parameters in the hart destination buffer
    \param AutotuneParams_t *d - pointer to the destination buffer
*/
static s8_least ReadTuningParameters(AutotuneParams_t *d)
{
    const TuneData_t *pSelfTuningParameters = tune_GetTuneData(NULL);

    u8 units = fpconvert_IntToFloatBuffer(pSelfTuningParameters->SupplyPres_User, UNITSID_PRESSURE, d->DefaultSupplyPressure[0]);
    UNUSED_OK(units); //TODO: stuff it in the response?
    util_PutU8(d->TuneAggressiveness[0], (u8)pSelfTuningParameters->n1Level);
    util_PutU8(d->TuneFlags[0], pSelfTuningParameters->n1TunePara1);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}


/**\brief Reads previously set settings of the tuning algorithm, and last completion code
    \param const u8 *src - hart command source buffer (not used)
    \param u8 *dst - hart destination buffer
*/
s8_least hartcmd_ReadTuningParameters(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    Rsp_ReadTuningParameters_t *d1 = (void *)dst;

    util_PutU16(d1->TuneCompletionCode[0], (u16)tune_GetCompletionCode());
    AutotuneParams_t *d = (void *)d1->AutotuneParams[0];
    return ReadTuningParameters(d);
}


/**
\brief This command saves the autotune parameters - used from FF
    \param const u8 *src - hart command source buffer (not used)
    \param u8 *dst - hart destination buffer
*/
s8_least hartcmd_WriteTuningParameters(const u8 *src, u8 *dst)
{
    s8_least ret;

    //just save the parameters but don't run autotune
    //get them
    TuneData_t SelfTuningParameters;
    const Req_WriteTuningParameters_t *s1 = (const void *)src;
    const AutotuneParams_t *s = (const void *)s1->AutotuneParams[0];
    ret = GetSetTuningParameters(&SelfTuningParameters, s);

    //save them
    if(ret == HART_NO_COMMAND_SPECIFIC_ERRORS)
    {
        Rsp_WriteTuningParameters_t *d1 = (void *)dst;
        AutotuneParams_t *d = (void *)d1->AutotuneParams[0];
        ret = ReadTuningParameters(d);
    }

    return ret;
}



/**
\brief This command runs the autotune process
    \param const u8 *src - hart command source buffer (not used)
    \param u8 *dst - hart destination buffer
*/
s8_least hartcmd_Autotune(const u8 *src, u8 *dst)
{
    s8_least ret;
    TuneData_t SelfTuningParameters;

    //check for limits being set that are protected
    if(control_TestProtectLimits() == PROTECTED_LIMITS)
    {
        /* Legitimate early return: Pre-requisites check */
        return HART_TUNE_NOT_ALLOWED;
    }

    // ---------------------------------------------------------------
    // Check if it is OK to run AutoTune (PID slots are set correctly)
    if (!posctl_IsTunableCtlset())
    {   // AutoTune is not allowed - PID slots are not set correctly
        return HART_TUNE_NOT_ALLOWED;
    }
    // ---------------------------------------------------------------

    const Req_Autotune_t *s1 = (const void *)src;
    const AutotuneParams_t *s = (const void *)s1->AutotuneParams[0];
    ret = GetSetTuningParameters(&SelfTuningParameters, s);

    if(ret == HART_NO_COMMAND_SPECIFIC_ERRORS)
    {
        //start autotune
        if(hart_SetProcessCommand((u8)PROC_AUTOTUNE))
        {
            //could not start process
            ret = HART_BUSY;
        }
        else
        {
            Rsp_Autotune_t *d1 = (void *)dst;
            AutotuneParams_t *d = (void *)d1->AutotuneParams[0];

            ret = ReadTuningParameters(d);
        }
    }
    return ret;
}

/**
\brief This command gets the tuning parameters and updates them from the command
    It assumes that AutotuneParams is common to both command 189 and command 171-189
    \param TuneData_t* pSelfTuningParameters - (out)tuning parameters returned
    \param const AutotuneParams_t *s - pointer to command buffer containing tuning parameters
*/
static s8_least GetSetTuningParameters(TuneData_t* pSelfTuningParameters, const AutotuneParams_t *s)
{
    s8_least ret = HART_NO_COMMAND_SPECIFIC_ERRORS;
    //calling GetTuneData isn't really needed since all parameters are updated frm the commands - LS
    (void)tune_GetTuneData(pSelfTuningParameters);

    //get the data
    pres_t UserSupplyP = fpconvert_FloatBufferToInt16Clamped(s->DefaultSupplyPressure[0], UNITSID_PRESSURE, SupplyPressure_range);
    pSelfTuningParameters->SupplyPres_User = UserSupplyP;
    pSelfTuningParameters->n1Level = (s8)util_GetU8(s->TuneAggressiveness[0]);
    pSelfTuningParameters->n1TunePara1 = util_GetU8(s->TuneFlags[0]);

    //set the process parameters
    if(tune_SetTuneData(pSelfTuningParameters) != ERR_OK)
    {
        ret = HART_INVALID_DATA;
    }
    return ret;
}


/* This line marks the end of the source */
