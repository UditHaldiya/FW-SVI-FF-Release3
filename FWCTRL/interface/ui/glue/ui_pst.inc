#MP If 0
/**
Copyright 2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file ui_pst.inc
    \brief Macros for PST configuration in MNCB

    This file cannot be processed by itself; it must be included in a
    .u file to generate the correct output.

    CPU: Any

    OWNER: AK

*/
#MP Endif

#MP Macro Pst_En ;() - "enable" nodes for PST
    #MP Expand StartEnEntry("EN_PST_CANCELED")
        DATAFUNC(ui_GetFaultCodeData), MN_OFFSETOF(FaultCodeData_t, fcode) + FWORD(FAULT_PST_CANCELED-1U), FBITPOS(FAULT_PST_CANCELED-1U), FBITPOS(FAULT_PST_CANCELED-1U),
        #MP Expand EnEntryNext()
    #MP Expand EndEnEntry()
    #MP Expand StartEnEntry("PST_ON")
        ui_getProcId, 0, 0xff, PROC_DIAG_PARTIAL_STROKE_TEST,
        #MP Expand EnEntryNext()
    #MP Expand EndEnEntry()
    #MP Expand StartEnEntry("PST_START")
        DATAFUNC(ui_IsPSTEnabled), 0, (1U<<PST_RUN_SETUP), (1U<<PST_RUN_SETUP),
        #MP Expand EnEntryNext(#@OPMODE_NOT_FSAFE_NOR_LOWPOWER#)
    #MP Expand EndEnEntry()
    #MP Expand StartEnEntry("EN_PST_SETUP")
        DATAFUNC(ui_IsPSTEnabled), 0, (1U<<PST_CONFIG), (1U<<PST_CONFIG),
        #MP Expand EnEntryNext("OPMODE_SETUP")
    #MP Expand EndEnEntry()
    #MP Expand StartEnEntry("EN_PST_VIEW")
        DATAFUNC(ui_IsPSTEnabled), 0, (1U<<PST_VIEW_CONFIG), (1U<<PST_VIEW_CONFIG),
        #MP Expand EnEntryNext()
    #MP Expand EndEnEntry()
#MP Endm

#MP Macro PSTSetup ;Root node
#MP Setstr PSTSetup_autoname = "PstSetup"
    #MP StartNode(nodetype_xsel, PSTSetup_autoname)
    {
        {
            #MP Expand NodetType()
            .tmout = 0, //no timeout
            #MP TEXTLABEL(PST_CONF)
            .en = ENOFFS(EN_PST_SETUP),
            .advance = NODE_LINK(#mp%sUIGraphNodeNext),
            #MP Setstr pstsetup_autoname = PSTSetup_autoname LockCheckSuffix
            .select = NODE_LINK(#mp%spstsetup_autoname),
            .xfuncx = XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
        NULL, ui_GetPstConf
    },
    #MP EndNode
#MP Endm

#MP Macro PSTSetupMenu ;Submenu to set up PST params; requires that the root node be defined
#MP If Defined(PSTSetup_autoname {STR}) ;only then do we generate the nodes
    #MP ProtectedEntry[%sPSTSetup_autoname, CHECK_WRITE_PROTECTED, LOCK_SETUP]
    #MP Setstr uinode_autoname = PSTSetup_autoname TargetNodeSuffix
        #MP Expand StartNode(nodetype_nav, uinode_autoname) ;#@PstSetupTravel#
        { //-------- PST end position
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(PST_TRAVEL)
            ENOFFS(OPMODE_SETUP),
            #MP over_the_var = UIGraphNode+2
            NODE_LINK(#mp%sUIGraphNode_%dover_the_var),
            NODE_LINK(var_PstTravel),
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_POSITION,
        },
        #MP Expand EndNode()
            #MP Expand StartNode(nodetype_limvar, #@var_PstTravel#)
            {
                {
                    #MP Expand NodetType()
                    .checksum_offset = 0, //no checksum
                    .en = UINODE_ENABLED,
                    .parent = NODELINK_NONE,
                    .data_index = UI_PSTINDEX(travel), //location offset
                    .varfunc = VARFUNC(ui_GetPstConfData)
                },
                UI_VARLIM(&pstTravel_range[0]),
                UI_VARLIM(&pstTravel_range[1])
            },
            #MP Expand EndNode()
#MP If 0
        #MP Expand StartNode(nodetype_nav, "PstSetupMin")
        { //-------- Max pressure change
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(PST_MIN)
            ENOFFS(PRESS_ACTUATOR),
            #MP over_the_var = UIGraphNode+2
            NODE_LINK(#mp%sUIGraphNode_%dover_the_var),
            NODE_LINK(#mp%sUIGraphNodeNext),
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_PRESSURE_ENTRY,
        },
        #MP Expand EndNode()
            #MP Expand StartNode(nodetype_limvar, "var_Pst")
            {
                {
                    #MP Expand NodetType()
                    .checksum_offset = 0, //no checksum
                    .en = UINODE_ENABLED,
                    .parent = NODELINK_NONE,
                    .data_index = UI_PSTINDEX(MinPresAbort), //location offset
                    .varfunc = VARFUNC(ui_GetPstConfData)
                },
                UI_VARLIM(&pstPres_range[0]),
                UI_VARLIM(&pstPres_range[1])
            },
            #MP Expand EndNode()
        #MP Expand StartNode(nodetype_nav, #@PstSetupMaxTime#)
        { //-------- PST Max time
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(PST_MAXTIME)
            ENOFFS(OPMODE_SETUP),
            NODE_LINK(PstSetupRampSpeed),
            NODE_LINK(var_PstMaxTime),
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_DUMMY, //display verbatim as integer
        },
        #MP Expand EndNode()
            #MP Expand StartNode(nodetype_limvar, #@var_PstMaxTime#)
            {
                {
                    #MP Expand NodetType()
                    .checksum_offset = 0, //no checksum
                    .en = UINODE_ENABLED,
                    .parent = NODELINK_NONE,
                    .data_index = UI_PSTINDEX(maxtime), //location offset
                    .varfunc = VARFUNC(ui_GetPstConfData)
                },
                UI_VARLIM(&pstTestTime_range[0]),
                UI_VARLIM(&pstTestTime_range[1])
            },
            #MP Expand EndNode()
#MP Endif
        #MP Expand StartNode(nodetype_nav, #@PstSetupRampSpeed#)
        { //-------- PST ramp speed
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(PST_RAMPSPEED)
            ENOFFS(OPMODE_SETUP),
            NODE_LINK(PstSetup_done),
            NODE_LINK(var_PstRampSpeed),
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_POSITION_ENTRY, //reuse for %/s
        },
        #MP Expand EndNode()
            #MP Expand StartNode(nodetype_limvar, #@var_PstRampSpeed#)
            {
                {
                    #MP Expand NodetType()
                    .checksum_offset = 0, //no checksum
                    .en = UINODE_ENABLED,
                    .data_index = UI_PSTINDEX(ramp_speed), //location offset
                    .parent = NODELINK_NONE,
                    .varfunc = VARFUNC(ui_GetPstConfData)
                },
                UI_VARLIM(&pstRampSpeed_range[0]),
                UI_VARLIM(&pstRampSpeed_range[1])
            },
            #MP Expand EndNode()

        #MP Expand StartNode(nodetype_nav, #@PstSetup_done#)
        {
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(UP2SETUP)
            UINODE_ENABLED,
            NODE_LINK(#mp%suinode_autoname), //wrap
            NODE_LINK(try_toPstSetup), //try to go up
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
        #MP Expand EndNode()
        #MP Expand StartNode(nodetype_xsel, #@try_toPstSetup#)
        {
            {
                #MP Expand NodetType()
                TMOUT_TICKS_DEFAULT,
                #MP TEXTLABEL(FAILED)
                UINODE_ENABLED,
                NODE_LINK(#mp%sPSTSetup_autoname), //go up regardless but display FAILURE on data save failure
                NODE_LINK(#mp%sPSTSetup_autoname),
                XLATE_INDEX(xlate_NextIfEnabled),
                .uid = UNITSID_NONE,
            },
            ui_SetPstConf, NULL // ui_SavePstConf() must return failure if fails
        },
        #MP Expand EndNode()
#MP Endif ;Defined(PSTSetup_autoname {STR})
#MP Endm

#MP Macro ViewData_PST ;(next node)
    #MP Expand StartNode(nodetype_nav, #@viewdata_pst#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(PST_CONF)
        ENOFFS(EN_PST_VIEW),
        NODE_LINK(#mp%nviewdata_goback),
        NODE_LINK(PstSetupTravel_view),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
        #MP Expand StartNode(nodetype_alt, #@PstSetupTravel_view#)
        {
            { //-------- PST end position
                #MP Expand NodetType()
                -TMOUT_TICKS_REFRESH, //refresh rate
                #MP TEXTLABEL(PST_TRAVEL)
                UINODE_ENABLED,
                NODE_LINK(#mp%sUIGraphNodeNext),
                NODE_LINK(viewdata_pst),
                XLATE_INDEX(xlate_StdMenu),
                .uid = UNITSID_POSITION,
            },
            ui_GetPstConf,
            NODE_LINK(var_PstTravel)
        },
        #MP Expand EndNode()
#MP If 0;
        #MP Expand StartNode(nodetype_alt, "PstSetupMin_view")
        {
            { //-------- Max pressure change
                #MP Expand NodetType()
                -TMOUT_TICKS_REFRESH, //refresh rate
                #MP TEXTLABEL(PST_MIN)
                ENOFFS(PRESS_ACTUATOR),
                NODE_LINK(#mp%sUIGraphNodeNext),
                NODE_LINK(viewdata_pst),
                XLATE_INDEX(xlate_StdMenu),
                .uid = UNITSID_PRESSURE_ENTRY,
            },
            ui_GetPstConf,
            NODE_LINK(var_Pst)
        },
        #MP Expand EndNode()
        #MP Expand StartNode(nodetype_alt, #@PstSetupMaxTime_view#)
        {
            { //-------- PST Max time
                #MP Expand NodetType()
                -TMOUT_TICKS_REFRESH, //refresh rate
                #MP TEXTLABEL(PST_MAXTIME)
                UINODE_ENABLED,
                NODE_LINK(PstSetupRampSpeed_view),
                NODE_LINK(viewdata_pst),
                XLATE_INDEX(xlate_StdMenu),
                .uid = UNITSID_DUMMY, //display verbatim as integer
            },
            ui_GetPstConf,
            NODE_LINK(var_PstMaxTime)
        },
        #MP Expand EndNode()
#MP Endif
        #MP Expand StartNode(nodetype_alt, #@PstSetupRampSpeed_view#)
        {
            { //-------- PST ramp speed
                #MP Expand NodetType()
                -TMOUT_TICKS_REFRESH, //refresh rate
                #MP TEXTLABEL(PST_RAMPSPEED)
                UINODE_ENABLED,
                NODE_LINK(pst_viewdata_goback),
                NODE_LINK(viewdata_pst),
                XLATE_INDEX(xlate_StdMenu),
                .uid = UNITSID_POSITION_ENTRY,
            },
            ui_GetPstConf,
            NODE_LINK(var_PstRampSpeed)
        },
        #MP Expand EndNode()
        #MP Expand StartNode(nodetype_nav, "pst_viewdata_goback")
        { //Just display
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(GOBACK)
            UINODE_ENABLED,
            NODE_LINK(PstSetupTravel_view), //wrap around
            NODE_LINK(viewdata_pst), //do it on *
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
        #MP Expand EndNode()
#MP Endm

#MP Macro PST_Start
    #MP Expand StartNode(nodetype_xsel, #@ui_pstnode#)
    {
        {
            #MP Expand NodetType()
            0, //no timeout
            #MP TEXTLABEL(PST_START)
            ENOFFS(PST_START),
            NODE_LINK(#mp%sUIGraphNodeNext),
            NODE_LINK(ui_pstnode), //No node change on *
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
        NULL, ui_pst
    },
    #MP Expand EndNode()
#MP Endm


#MP Macro PST_RunInfo
    #MP Expand DeclareStartNode(#@UINODEID_PST_RUNNING#)
    #MP Expand StartNode(nodetype_nav, #@ui_pst_run#)
    { //Just display
        #MP Expand NodetType()
        -TMOUT_TICKS_REFRESH,
        #MP TEXTLABEL(PST_RUNNING)
        ENOFFS(PST_ON),
        NODE_LINK(canceled_pst), //when the node is no longer enabled, proceed to analyze the outcome
        NODE_LINK(ui_pst_run), //pushbuttons will have us stuck here
        XLATE_INDEX(xlate_SelectIfEnabled), //To allow falling through the cycling menu in OOS
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, "canceled_pst")
    {
        #MP Expand NodetType()
        TMOUT_TICKS_CANCELED,
        #MP TEXTLABEL(MSG_CANCELED)
        ENOFFS(EN_PST_CANCELED), //UINODE_ENABLED,
        NODE_LINK(#mp%sCyclingMenuStart), //do it on any key
        NODE_LINK(#mp%sCyclingMenuStart), //do it on disabled node
        XLATE_INDEX(xlate_NextIfEnabled), //To allow falling through the cycling menu in OOS
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endm

