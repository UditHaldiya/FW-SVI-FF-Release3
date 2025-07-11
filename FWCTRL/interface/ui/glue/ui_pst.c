/*
Copyright 2009 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_pst.c
    \brief UI support functions for Partial stroke test

     CPU: Any

    OWNER: AK

    \ingroup UI
*/

#include "mnwrap.h"
#include "process.h"
#include "pstshell.h"
#include "pst.h"
#include "uidef.h"
#include "ui_pst.h"
#include "uiglue_common.h"
#include "ui_config.h"

static PSTConf_t pstconf; //! UI local working copy of PST configuration data
//lint -emacro(740, FIRSTVAR_IN_STRUCT) unusual pointer cast; C std guarantees correctness
#define FIRSTVAR_IN_STRUCT(s) ((s16 *)&(s))

bool_t ui_GetPstConf(const uistate_t *state)
{
    UNUSED_OK(state);
    (void)diag_GetPstData(&pstconf);
    return false; //ui_getConf(state); //Just to set up pressure units in scratchpad
}

bool_t ui_SetPstConf(const uistate_t *state)
{
    UNUSED_OK(state);
    return diag_SetPstData(&pstconf) == ERR_OK;
}

s16 *ui_GetPstConfData(void)
{
    return FIRSTVAR_IN_STRUCT(pstconf);
}

/** \brief UI PST enable function
\returns &0 iff PST start from pushbuttons is enabled, &1 otherwise
*/
const void *ui_IsPSTEnabled(void)
{
    static u8 ret;
    ret = pst_GetTriggerInfo(NULL)->PstUiTrigger;
    return &ret;
}

/** \brief A UI node entry function to start PST from the pushbuttons
\return false
*/
bool_t ui_pst(const uistate_t *state)
{
    UNUSED_OK(state);
    process_ForceProcessCommandEx(PROC_DIAG_PARTIAL_STROKE_TEST, ProcSourceUI);
    return false;
}
/* This line marks the end of the source */
