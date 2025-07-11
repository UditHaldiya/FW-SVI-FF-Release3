/*
Copyright 2012 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_ffinfo.c
    \brief UI service functions for "foundation field bus" support

     CPU: Any

    OWNER: AK

    \ingroup UI
*/

#include "mnwrap.h"
#include "numutils.h"
#include "ui_config.h"
#include "ui_ffinfo.h"
#include "uidef.h"
#include "uishow.h"
#include "lcd.h"
#include "utilities.h"
#include "ff_resblockvars.h"
#include "ff_aoblockvars.h"
#include "ff_doblockvars.h"
#include "ff_pidblockvars.h"
#include "ff_tbblockvars.h"
#include "ff_devicevars.h"

#define FFSTR_LENGTH_MODE  (sizeof(FFSTR_MODE_NA)-1) /* 5 */
#define FFSTR_OFFSET_ERR   FFSTR_LENGTH_MODE         /* 5 */
#define FFSTR_LENGTH_ERR  (NUMBER_OF_DIGITS_PER_LINE - FFSTR_OFFSET_ERR) /* 4 */

/** \brief convert the mode from IPC to string
        input:
            mode: mode from IPC
            pbuf: the string
*/
static void ff_Mode2Str(const u8 mode, u8* pbuf)
{
    UNUSED_OK(pbuf);
    switch (mode)
    {
    case IPC_MODE_AUTO:
        mn_memcpy((void*)pbuf, FFSTR_MODE_AUTO, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_MANUAL:
        mn_memcpy((void*)pbuf, FFSTR_MODE_MAN, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_LOVERRIDE:
        mn_memcpy((void*)pbuf, FFSTR_MODE_LO, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_OOS:
        mn_memcpy((void*)pbuf, FFSTR_MODE_OOS, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_ROUT:
        mn_memcpy((void*)pbuf, FFSTR_MODE_ROUT, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_RCAS:
        mn_memcpy((void*)pbuf, FFSTR_MODE_RCAS, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_IMAN:
        mn_memcpy((void*)pbuf, FFSTR_MODE_IMAN, FFSTR_LENGTH_MODE);
        break;
    case IPC_MODE_CAS:
        mn_memcpy((void*)pbuf, FFSTR_MODE_CAS, FFSTR_LENGTH_MODE);
        break;

    default:
        mn_memcpy((void*)pbuf, FFSTR_MODE_NA, FFSTR_LENGTH_MODE);
        break;
    }
}

/** \brief convert the mode from IPC to string
        input:
            mode: err from IPC
            pbuf: the string
*/
static void ff_Err2Str(const u16 err, u8* pbuf)
{
    UNUSED_OK(pbuf);
    if (FF_BLK_ERR_NOERR != err)
    {
        mn_memcpy((void*)pbuf, FFSTR_ERR_ERR, FFSTR_LENGTH_ERR);
    }
    else
    {
        mn_memcpy((void*)pbuf, FFSTR_ERR_OK, FFSTR_LENGTH_ERR);
    }
}

/** \brief called when display exit a menu cycle of FF info, to
        infor mation of resource block.
*/
bool_t ui_ff_InfoRB(const uistate_t *state)
{
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1];

    u8 ModeActual;
    u16 BlockErr;
    MN_ENTER_CRITICAL();
        const IPC_FFResourceParams_t* pVar = GetResBlockVar(NULL);
        ModeActual = pVar->ModeActual;
        BlockErr = pVar->BlockErr;
    MN_EXIT_CRITICAL();

    // display the orignal digits on lcd, and will be replaced by string
    ff_Mode2Str(ModeActual, ln2);
    ff_Err2Str(BlockErr, &ln2[FFSTR_OFFSET_ERR]);
    ui_setDispmode(DISPMODE_FF_INFO, ln2);

    UNUSED_OK(state);
    return false;
}

/** \brief A helper for any partial substring of a string of 32 characters
\param str - a partial string (segment) to display
\param segment - a segment to display
\param len - length of the segment
\return false
*/
static bool_t ui_ff_Tag_helper(const u8 str[], size_t segment, size_t len)
{
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1];
    MN_ENTER_CRITICAL();
        mn_memcpy(ln2, &str[segment * NUMBER_OF_DIGITS_PER_LINE], len);
    MN_EXIT_CRITICAL();
    for(; len<NUMBER_OF_DIGITS_PER_LINE; len++)
    {
        ln2[len] = ASCII_SPACE;
    }
    ui_setDispmode(DISPMODE_FF_INFO, ln2);
    return false;
}

/** \brief A helper for RB tag
\param segment - a segment to display
\param len - length of the segment
\return false
*/
static bool_t ui_ff_TagRB_helper(const uistate_t *state, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetResBlockVar(NULL)->tag;
    return ui_ff_Tag_helper(str, segment, len);
}

/** \brief called when display exit a menu cycle of FF info, to
        part 1 of resource block.
*/
bool_t ui_ff_Tag1RB(const uistate_t *state)
{
    return ui_ff_TagRB_helper(state, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of resource block.
*/
bool_t ui_ff_Tag2RB(const uistate_t *state)
{
    return ui_ff_TagRB_helper(state, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of resource block.
*/
bool_t ui_ff_Tag3RB(const uistate_t *state)
{
    return ui_ff_TagRB_helper(state, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of resource block.
*/
bool_t ui_ff_Tag4RB(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagRB_helper(state, 3U, FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}

/** \brief A helper to retrieve device id
\param segment - dev id segment to retrieve
\param len - length of the segment
\return false
*/
static bool_t ui_ff_devIDhelper(const uistate_t *state, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetDeviceVar(NULL)->dev_id;
    CONST_ASSERT(FF_DEVICE_TAG_LEN == FF_DEVICE_ID_LEN);
    return ui_ff_Tag_helper(str, segment, len);
}

/** \brief called when display enter a menu cycle of FF info, to
        show device ID part 1.
*/
bool_t ui_ff_devID1(const uistate_t *state)
{
    return ui_ff_devIDhelper(state, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display enter a menu cycle of FF info, to
        show device ID part 2.
*/
bool_t ui_ff_devID2(const uistate_t *state)
{
    return ui_ff_devIDhelper(state, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display enter a menu cycle of FF info, to
        show device ID part 3.
*/
bool_t ui_ff_devID3(const uistate_t *state)
{
    return ui_ff_devIDhelper(state, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display enter a menu cycle of FF info, to
        show device ID part 4.
*/
bool_t ui_ff_devID4(const uistate_t *state)
{
    CONST_ASSERT ((FF_DEVICE_ID_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_devIDhelper(state, 3U, FF_DEVICE_ID_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}

/** \brief called when display exit a menu cycle of FF info, to
        show device address.
*/
bool_t ui_ff_devAddr(const uistate_t *state)
{

    IPC_FFDeviceParams_t* pVar;
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1] = BLANK_STR_LCD_1LINE;

    pVar = GetDeviceVar(NULL);
    ut_bin2asc(pVar->dev_addr, (p8*)ln2, 0);
    ui_setDispmode(DISPMODE_FF_INFO, ln2);

    UNUSED_OK(state);



    return false;
}

/** \brief A helper to retrieve device tag
\param segment - dev id segment to retrieve
\param len - length of the segment
\return false
*/
static bool_t ui_ff_devTag_helper(const uistate_t *state, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetDeviceVar(NULL)->dev_tag;
    return ui_ff_Tag_helper(str, segment, len);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 1 of device tag.
*/
bool_t ui_ff_devTag1(const uistate_t *state)
{
    return ui_ff_devTag_helper(state, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of device tag.
*/
bool_t ui_ff_devTag2(const uistate_t *state)
{
    return ui_ff_devTag_helper(state, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of device tag.
*/
bool_t ui_ff_devTag3(const uistate_t *state)
{
    return ui_ff_devTag_helper(state, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of device tag.
*/
bool_t ui_ff_devTag4(const uistate_t *state)
{
    CONST_ASSERT ((FF_DEVICE_TAG_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_devTag_helper(state, 3U, FF_DEVICE_TAG_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}

/** \brief called when display exit a menu cycle of FF info, to clear
        string on line 3.
*/
bool_t ui_Clr_Lin3(const uistate_t *state)
{
    ui_clearLine3();
    UNUSED_OK(state);
    return false;
}

/** \brief called when display exit a menu cycle of FF info, to clear
        string on line 3. Return true means disable current node
*/
bool_t ui_Clr_Lin3Silent(const uistate_t *state)
{
    ui_clearLine3();
    UNUSED_OK(state);
    return true;
}

/** \brief called when display exit a menu cycle of FF info, to
        infor mation of TB block.
*/
bool_t ui_ff_InfoTB(const uistate_t *state)
{
    const IPC_FFTBParams_t* pVar;
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1];

    pVar = GetTbBlockVar(NULL);
    // display the orignal digits on lcd, and will be replaced by string
    u8 ModeActual;
    u16 BlockErr;
    MN_ENTER_CRITICAL();
        ModeActual = pVar->ModeActual;
        BlockErr = pVar->BlockErr;
    MN_EXIT_CRITICAL();
    ff_Mode2Str(ModeActual, ln2);
    ff_Err2Str(BlockErr, &ln2[FFSTR_OFFSET_ERR]);
    ui_setDispmode(DISPMODE_FF_INFO, ln2);

    UNUSED_OK(state);
    return false;
}

static bool_t ui_ff_TagTB_helper(const uistate_t *state, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetTbBlockVar(NULL)->tag;
    return ui_ff_Tag_helper(str, segment, len);
}
/** \brief called when display exit a menu cycle of FF info, to
        part 1 of TB block.
*/
bool_t ui_ff_Tag1TB(const uistate_t *state)
{
    return ui_ff_TagTB_helper(state, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of TB block.
*/
bool_t ui_ff_Tag2TB(const uistate_t *state)
{
    return ui_ff_TagTB_helper(state, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of TB block.
*/
bool_t ui_ff_Tag3TB(const uistate_t *state)
{
    return ui_ff_TagTB_helper(state, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of TB block.
*/
bool_t ui_ff_Tag4TB(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagTB_helper(state, 3U, FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}
/** \brief called when display exit a menu cycle of FF info, to
        infor mation of AO block.
*/
bool_t ui_ff_InfoAO(const uistate_t *state)
{
    const IPC_FFAOParams_t* pVar;
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1];

    u8 ModeActual;
    u16 BlockErr;
    pVar = GetAoBlockVar(NULL);
    MN_ENTER_CRITICAL();
        ModeActual = pVar->ModeActual;
        BlockErr = pVar->BlockErr;
    MN_EXIT_CRITICAL();

    // display the orignal digits on lcd, and will be replaced by string
    ff_Mode2Str(ModeActual, ln2);
    ff_Err2Str(BlockErr, &ln2[FFSTR_OFFSET_ERR]);
    ui_setDispmode(DISPMODE_FF_INFO, ln2);

    UNUSED_OK(state);
    return false;
}

/** \brief A helper for PID block tag
\param index - PID number (0-based)
\param segment - segment of the tag
\param len - length of the segment
*/
static bool_t ui_ff_TagAO_helper(const uistate_t *state, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetAoBlockVar(NULL)->tag;
    return ui_ff_Tag_helper(str, segment, len);
}

/** \brief called when display exit a menu cycle of FF info, to
        part 1 of AO block.
*/
bool_t ui_ff_Tag1AO(const uistate_t *state)
{
    return ui_ff_TagAO_helper(state, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of AO block.
*/
bool_t ui_ff_Tag2AO(const uistate_t *state)
{
    return ui_ff_TagAO_helper(state, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of AO block.
*/
bool_t ui_ff_Tag3AO(const uistate_t *state)
{
    return ui_ff_TagAO_helper(state, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of AO block.
*/
bool_t ui_ff_Tag4AO(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagAO_helper(state, 3U, FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}

/** \brief A helper for PID block info.
\param index - PID block number (0-based)
*/
static bool_t ui_ff_InfoPID_helper(const uistate_t *state, size_t index)
{
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1];
    const IPC_FFPIDParams_t *pVar = GetPidBlockVar(index, NULL);
    u8 ModeActual;
    u16 BlockErr;
    // display the orignal digits on lcd, and will be replaced by string
    MN_ENTER_CRITICAL();
        ModeActual = pVar->ModeActual;
        BlockErr = pVar->BlockErr;
    MN_EXIT_CRITICAL();

    ff_Mode2Str(ModeActual, ln2);
    ff_Err2Str(BlockErr, &ln2[FFSTR_OFFSET_ERR]);
    ui_setDispmode(DISPMODE_FF_INFO, ln2);

    UNUSED_OK(state);
    return false;
}

/** \brief called when display exit a menu cycle of FF info, to
        infor mation of PID block.
*/
bool_t ui_ff_InfoPID(const uistate_t *state)
{
    return ui_ff_InfoPID_helper(state, 0U);
}

/** \brief A helper for PID block tag
\param index - PID number (0-based)
\param segment - segment of the tag
\param len - length of the segment
*/
static bool_t ui_ff_TagPID_helper(const uistate_t *state, size_t index, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetPidBlockVar(index, NULL)->tag;
    return ui_ff_Tag_helper(str, segment, len);
}

/** \brief called when display exit a menu cycle of FF info, to
        part 1 of PID block.
*/
bool_t ui_ff_Tag1PID(const uistate_t *state)
{
    return ui_ff_TagPID_helper(state, 0U, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of PID block.
*/
bool_t ui_ff_Tag2PID(const uistate_t *state)
{
    return ui_ff_TagPID_helper(state, 0U, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of PID block.
*/
bool_t ui_ff_Tag3PID(const uistate_t *state)
{
    return ui_ff_TagPID_helper(state, 0U, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of PID block.
*/
bool_t ui_ff_Tag4PID(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagPID_helper(state, 0U, 3U, FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}

/** \brief called when display exit a menu cycle of FF info, to
        infor mation of DO block.
*/
static bool_t ui_ff_InfoDO_helper(const uistate_t *state, size_t index)
{
    const IPC_FFDOParams_t* pVar;
    u8 ln2[NUMBER_OF_DIGITS_PER_LINE + 1];

    u8 ModeActual;
    u16 BlockErr;
    MN_ENTER_CRITICAL();
        pVar = GetDoBlockVar(index, NULL);
        // display the orignal digits on lcd, and will be replaced by string
        ModeActual = pVar->ModeActual;
        BlockErr = pVar->BlockErr;
    MN_EXIT_CRITICAL();

    ff_Mode2Str(ModeActual, ln2);
    ff_Err2Str(BlockErr, &ln2[FFSTR_OFFSET_ERR]);
    ui_setDispmode(DISPMODE_FF_INFO, ln2);

    UNUSED_OK(state);
    return false;
}

/** \brief called when display exit a menu cycle of FF info, to
        infor mation of DO block.
*/
bool_t ui_ff_InfoDO(const uistate_t *state)
{
    return ui_ff_InfoDO_helper(state, 0U);
}

/** \brief called when display exit a menu cycle of FF info, to
        part 1 of DO block.
*/
static bool_t ui_ff_TagDO_helper(const uistate_t *state, size_t index, size_t segment, size_t len)
{
    UNUSED_OK(state);
    const u8 *str = GetDoBlockVar(index, NULL)->tag;
    return ui_ff_Tag_helper(str, segment, len);
}


/** \brief called when display exit a menu cycle of FF info, to
        part 1 of DO block.
*/
bool_t ui_ff_Tag1DO(const uistate_t *state)
{
    return ui_ff_TagDO_helper(state, 0U, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of DO block.
*/
bool_t ui_ff_Tag2DO(const uistate_t *state)
{
    return ui_ff_TagDO_helper(state, 0U, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of DO block.
*/
bool_t ui_ff_Tag3DO(const uistate_t *state)
{
    return ui_ff_TagDO_helper(state, 0U, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of DO block.
*/
bool_t ui_ff_Tag4DO(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagDO_helper(state, 0U, 3U, FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}
/** \brief called when display exit a menu cycle of FF info, to
        infor mation of PID2 block.
*/
bool_t ui_ff_InfoPID2(const uistate_t *state)
{
    return ui_ff_InfoPID_helper(state, 1U);
}

/** \brief called when display exit a menu cycle of FF info, to
        part 1 of PID2 block.
*/
bool_t ui_ff_Tag1PID2(const uistate_t *state)
{
    return ui_ff_TagPID_helper(state, 1U, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of PID2 block.
*/
bool_t ui_ff_Tag2PID2(const uistate_t *state)
{
    return ui_ff_TagPID_helper(state, 1U, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of PID2 block.
*/
bool_t ui_ff_Tag3PID2(const uistate_t *state)
{
    return ui_ff_TagPID_helper(state, 1U, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of PID2 block.
*/
bool_t ui_ff_Tag4PID2(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagPID_helper(state, 1U, 3U, FF_TAG_MAX_LEN -NUMBER_OF_DIGITS_PER_LINE *3);
}
/** \brief called when display exit a menu cycle of FF info, to
        infor mation of DO2 block.
*/
bool_t ui_ff_InfoDO2(const uistate_t *state)
{
    return ui_ff_InfoDO_helper(state, 1U);
}

/** \brief called when display exit a menu cycle of FF info, to
        part 1 of DO2 block.
*/
bool_t ui_ff_Tag1DO2(const uistate_t *state)
{
    return ui_ff_TagDO_helper(state, 1U, 0U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 2 of DO2 block.
*/
bool_t ui_ff_Tag2DO2(const uistate_t *state)
{
    return ui_ff_TagDO_helper(state, 1U, 1U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 3 of DO2 block.
*/
bool_t ui_ff_Tag3DO2(const uistate_t *state)
{
    return ui_ff_TagDO_helper(state, 1U, 2U, NUMBER_OF_DIGITS_PER_LINE);
}

/** \brief called when display exit a menu cycle of FF info, to
        show part 4 of DO2 block.
*/
bool_t ui_ff_Tag4DO2(const uistate_t *state)
{
    CONST_ASSERT ((FF_TAG_MAX_LEN - NUMBER_OF_DIGITS_PER_LINE *3) <= NUMBER_OF_DIGITS_PER_LINE);
    return ui_ff_TagDO_helper(state, 1U, 3U, FF_TAG_MAX_LEN - NUMBER_OF_DIGITS_PER_LINE *3);
}

// ------- helpers for UI "simulation jumper" --------
static u8 simopt;
bool_t ui_SimulationInit(const uistate_t *state)
{
    UNUSED_OK(state);
    bool_t b = ff_GetLocalFFData(NULL)->SimulationActive;
    simopt = bool2int(b);
    return false;
}
void *ui_GetSimOption(void)
{
    return &simopt;
}
const void *ui_GetConstSimOption(void)
{
    return &simopt;
}
bool_t ui_SimulationSet(const uistate_t *state)
{
    UNUSED_OK(state);
    FFData_t ffdata;
    (void)ff_GetLocalFFData(&ffdata);
    ffdata.SimulationActive = int2bool(simopt);
    ErrorCode_t err = ff_RepairSetFFData(&ffdata);
    return (err != ERR_OK);
}
// --------------------- end sim jumper -------------

/** \brief called by ui enable list when display check if node is enabled
        depends on IPC time stamp
*/
const void *ui_GetIpcTimeStampStatus(void)
{
    IPC_FFDeviceParams_t* pVar;

    pVar = GetDeviceVar(NULL);
    return &(pVar->IPC_TimeStampStatus);
}

/* This line marks the end of the source */

