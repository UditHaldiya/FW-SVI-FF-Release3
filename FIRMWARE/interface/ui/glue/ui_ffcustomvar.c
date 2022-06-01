/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_ffcustomvar.c
    \brief UI service functions for "foundation field bus" support (MNCB)

     CPU: Any

    OWNER: EJ

\ingroup UI
*/
#include "mnwrap.h"
#include "numutils.h"
#include "ui_config.h"
#include "uidef.h"
#include "uishow.h"
#include "lcd.h"
#include "ui_ffcustomvar.h"
#include "ff_resblockvars.h"
#include "ff_aoblockvars.h"
#include "ff_doblockvars.h"
#include "ff_pidblockvars.h"
#include "ff_tbblockvars.h"
#include "ff_aiblockvars.h"
#include "ff_isblockvars.h"
#include "bufutils.h"
#include "mnassert.h"

/**\brief show NULL for string initial value
*/
static void check_initial_string(u8* str, u8 len)
{
	if(0 == str[0])
	{
		util_GetU8Array((const u8*)"    NULL", len, str);
	}
}

/** \brief called by ui enable list when display check if node is enabled
        by custom 1
*/
const void *ui_CycleMenuGetFfCustom1(void)
{
    const IPC_FFTBParams_t* pVar;

    pVar = GetTbBlockVar(NULL);
    return &(pVar->cust_config_0);
}

/** \brief called by ui enable list when display check if node is enabled
        by custom 2
*/
const void *ui_CycleMenuGetFfCustom2(void)
{
    const IPC_FFTBParams_t* pVar;

    pVar = GetTbBlockVar(NULL);
    return &(pVar->cust_config_1);
}


/* local invoked, display variable status at line 3
    #define SQ_BAD                       (0 * 0x40)
    #define SQ_UNCERTAIN                 (1 * 0x40)
    #define SQ_GOOD_NC                   (2 * 0x40)
    #define SQ_GOOD_CAS                  (3 * 0x40)
    #define SQ_GOOD                      (2 * 0x40)
*/
static void ui_dispFfVarStatus(u8 status)
{
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1] = BLANK_STR_LCD_1LINE;

    status = status & IPC_QUALITY_MASK;
    switch (status)
    {
    case IPC_QUALITY_BAD:
        mn_memcpy((void*)ln2, FFSTR_VARSTATUS_BAD, NUMBER_OF_DIGITS_PER_LINE);
        break;
    case IPC_QUALITY_UNCERTAIN:
        mn_memcpy((void*)ln2, FFSTR_VARSTATUS_UNCERTAIN, NUMBER_OF_DIGITS_PER_LINE);
        break;
    case IPC_QUALITY_GOODCASCADE:
        mn_memcpy((void*)ln2, FFSTR_VARSTATUS_GOODCAS, NUMBER_OF_DIGITS_PER_LINE);
        break;
    case IPC_QUALITY_GOOD:
        mn_memcpy((void*)ln2, FFSTR_VARSTATUS_GOOD, NUMBER_OF_DIGITS_PER_LINE);
        break;
    default:
        //Nothing to do
        break;
    }
    ui_setDispmode(DISPMODE_FF_INFO, ln2);
}

/** \brief called by ui variable node
        to get the value for display, index 1
*/
u8 ui_ffGetWorkingSP(u8 * str, u8 maxlen)
{
    const IPC_FFTBParams_t* pvar;

    pvar = GetTbBlockVar(NULL);
    MN_ENTER_CRITICAL();
        ui_dispFfVarStatus(pvar->final_sp.status);
        util_GetU8Array(pvar->final_sp.value, maxlen, str);
    MN_EXIT_CRITICAL();
	check_initial_string(str, maxlen);
	return maxlen;
}

/** \brief called by ui variable node
        to get the value for display, index 2
*/
u8 ui_ffGetWorkingPos(u8 * str, u8 maxlen)
{
    const IPC_FFTBParams_t* pvar;

    pvar = GetTbBlockVar(NULL);
    MN_ENTER_CRITICAL();
        ui_dispFfVarStatus(pvar->final_pos.status);
        util_GetU8Array(pvar->final_pos.value, maxlen, str);
    MN_EXIT_CRITICAL();
	check_initial_string(str, maxlen);
	return maxlen;
}

typedef enum pidvartype_t
{
    pidvartype_invalid,
    pidvartype_sp,
    pidvartype_pv,
    pidvartype_out
} pidvartype_t;

static u8 ui_ffGetPidVar_helper(u8 *str, u8 maxlen, size_t index, pidvartype_t pidvartype)
{
    const IPC_FFPIDParams_t* pparam = GetPidBlockVar(index, NULL);
    const ffDataFloat_t *pvar;
    switch(pidvartype)
    {
        case pidvartype_sp:
            pvar = &pparam->sp;
            break;
        case pidvartype_pv:
            pvar = &pparam->pv;
            break;
        case pidvartype_out:
            pvar = &pparam->out;
            break;
        case pidvartype_invalid:
        default:
            pvar = NULL;
            break;
    }
    MN_DBG_ASSERT(pvar != NULL);
    MN_ENTER_CRITICAL();
        ui_dispFfVarStatus(pvar->status);
        util_GetU8Array(pvar->value, maxlen, str);
    MN_EXIT_CRITICAL();
	check_initial_string(str, maxlen);

	return maxlen;
}
/** \brief called by ui variable node
        to get the value for display, index 3
*/
u8 ui_ffGetPidSp(u8 * str, u8 maxlen)
{
    return ui_ffGetPidVar_helper(str, maxlen, 0U, pidvartype_sp);
}

/** \brief called by ui variable node
        to get the value for display, index 4
*/
u8 ui_ffGetPidPv(u8 * str, u8 maxlen)
{
    return ui_ffGetPidVar_helper(str, maxlen, 0U, pidvartype_pv);
}

/** \brief called by ui variable node
        to get the value for display, index 5
*/
u8 ui_ffGetPidOut(u8 * str, u8 maxlen)
{
    return ui_ffGetPidVar_helper(str, maxlen, 0U, pidvartype_out);
}

/** \brief called by ui variable node
        to get the value for display, index 6
*/
u8 ui_ffGetPid2Sp(u8 * str, u8 maxlen)
{
    return ui_ffGetPidVar_helper(str, maxlen, 1U, pidvartype_sp);
}

/** \brief called by ui variable node
        to get the value for display, index 7
*/
u8 ui_ffGetPid2Pv(u8 * str, u8 maxlen)
{
    return ui_ffGetPidVar_helper(str, maxlen, 1U, pidvartype_pv);
}

/** \brief called by ui variable node
        to get the value for display, index 8
*/
u8 ui_ffGetPid2Out(u8 * str, u8 maxlen)
{
    return ui_ffGetPidVar_helper(str, maxlen, 1U, pidvartype_out);
}

/** \brief A common helper for AI OUT parameter display
\param str - destination string
\param maxlen - max display length
\param index - which AI (0-based)
\return maxlen
*/
static u8 ui_ffGetAiOut(u8 * str, u8 maxlen, size_t index)
{
    IPC_FFAIParams_t aidata;
    const IPC_FFAIParams_t *pvar = GetAiBlockVar(index, &aidata);
    MN_DBG_ASSERT(pvar != NULL);
    ui_dispFfVarStatus(aidata.out.status);
	util_GetU8Array(aidata.out.value, maxlen, str);
	check_initial_string(str, maxlen);
	return maxlen;
}

/** \brief called by ui variable node
        to get the value for display AI 1 display
\param str - destination string
\param maxlen - max display length
\return maxlen
*/
u8 ui_ffGetAi1Out(u8 * str, u8 maxlen)
{
    return ui_ffGetAiOut(str, maxlen, 0);
}

/** \brief called by ui variable node
        to get the value for display AI 2 display
\param str - destination string
\param maxlen - max display length
\return maxlen
*/
u8 ui_ffGetAi2Out(u8 * str, u8 maxlen)
{
    return ui_ffGetAiOut(str, maxlen, 1);
}

/** \brief called by ui variable node
        to get the value for display AI 3 display
\param str - destination string
\param maxlen - max display length
\return maxlen
*/
u8 ui_ffGetAi3Out(u8 * str, u8 maxlen)
{
    return ui_ffGetAiOut(str, maxlen, 2);
}

/** \brief called by ui variable node
        to get the value for display, index 12
*/
u8 ui_ffGetAoSp(u8 * str, u8 maxlen)
{
    const IPC_FFAOParams_t* pvar = GetAoBlockVar(NULL);
    u8 status;
    MN_ENTER_CRITICAL();
        status =(pvar->sp.status);
        util_GetU8Array(pvar->sp.value, maxlen, str);
    MN_EXIT_CRITICAL();
    ui_dispFfVarStatus(status);
	check_initial_string(str, maxlen);
	return maxlen;
}

static uivalvar_t DOx_value;
/** \brief A helper for DO1 and DO2 setpoint
*/
static uivalvar_t *ui_ffGetDoSp_helper(size_t index)
{
    const IPC_FFDOParams_t* pvar;

    MN_ENTER_CRITICAL();
        pvar = GetDoBlockVar(index, NULL);
        ui_dispFfVarStatus(pvar->sp_d.status);
        DOx_value = (pvar->sp_d.value);
    MN_EXIT_CRITICAL();
    return &DOx_value;
}

/** \brief called by ui variable node
        to get the value for display, index 14
*/
uivalvar_t *ui_ffGetDoSp(void)
{
    return ui_ffGetDoSp_helper(0U);
}

/** \brief called by ui variable node
        to get the value for display, index 14
*/
uivalvar_t *ui_ffGetDo2Sp(void)
{
    return ui_ffGetDoSp_helper(1U);
}
/** \brief called by ui variable node
        to get the value for display, index 15
*/
static u8 ui_ffGetIsIn_helper(u8 * str, u8 maxlen, size_t index)
{
    IPC_FFISParams_t var;
    const IPC_FFISParams_t* pvar = GetIsBlockVar(&var);
    MN_DBG_ASSERT(pvar != NULL);


    ffDataFloat_t *p_in;
    switch(index)
    {
        case 1:
            p_in = &var.in1;
            break;
        case 2:
            p_in = &var.in2;
            break;
        case 3:
            p_in = &var.in3;
            break;
        case 4:
            p_in = &var.in4;
            break;
        default:
            p_in = NULL;
            break;
    }
    MN_DBG_ASSERT(p_in != NULL);

    ui_dispFfVarStatus(p_in->status);
    util_GetU8Array(p_in->value, maxlen, str);
	check_initial_string(str, maxlen);
	return maxlen;
}
/** \brief called by ui variable node
        to get the value for display, index 15
*/
u8 ui_ffGetIsIn1(u8 * str, u8 maxlen)
{
    return ui_ffGetIsIn_helper(str, maxlen, 1U);
}
/** \brief called by ui variable node
        to get the value for display, index 16
*/
u8 ui_ffGetIsIn2(u8 * str, u8 maxlen)
{
    return ui_ffGetIsIn_helper(str, maxlen, 2U);
}

/** \brief called by ui variable node
        to get the value for display, index 17
*/
u8 ui_ffGetIsIn3(u8 * str, u8 maxlen)
{
    return ui_ffGetIsIn_helper(str, maxlen, 3U);
}

/** \brief called by ui variable node
        to get the value for display, index 18
*/
u8 ui_ffGetIsIn4(u8 * str, u8 maxlen)
{
    return ui_ffGetIsIn_helper(str, maxlen, 4U);
}

/** \brief called by ui variable node
        to get the value for display, index 18
*/
u8 ui_ffGetParamBadDefault(u8 * str, u8 maxlen)
{
    ui_dispFfVarStatus(IPC_QUALITY_BAD);
    util_PutU8(str, 0);
    check_initial_string(str, maxlen);
    return maxlen;
}

/* This line marks the end of the source */

