#MP If 0
/**
Copyright 2008 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file ui_finstops.inc
    \brief Configuration of LCD UI nodes for MNCB : "Find stops" with active control

    This file cannot be processed by itself; it must be included in a
    .u file to generate the correct output.

    CPU: Any

    OWNER: AK

    IMPORTANT:
    Pay close attention to defining the "node enabled" field. It must be
    of the form UINODE_ENABLED, UINODE_DISABLED or ENOFFS(en) where en is
    a valid element of the Enable structure defined elsewhere.
*/
#MP Endif

#MP Macro CalStops ;Root node - name supplied in uinode_autoname
#MP Setstr CalStops_autoname = uinode_autoname
    #MP Expand StartNode(nodetype_nav, uinode_autoname) ;cal stops
    {
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(STOPS)
        UINODE_ENABLED,
        NODE_LINK(#mp%sUIGraphNodeNext),
        NODE_LINK(cal_stops_submenu), //go to submenu on *
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endm

#MP Macro CalStopsMenu
#MP ;Failure handling
    #MP Expand DeclareStartNode(#@UINODEID_RUNSTOPS_FAILED#)
    #MP Expand StartNode(nodetype_nav, #@runstops_failed#)
    {
        #MP Expand NodetType()
        -TMOUT_TICKS_REFRESH,
        #MP TEXTLABEL(FAILED)
        ENOFFS(XMODE_SETUP),
        NODE_LINK(#mp%sCalStops_autoname), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(cal_stops_submenu), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_DUMMY,
    },
    #MP Expand EndNode()
#MP ;End failure handling
#MP ;Process support
    #MP Expand DeclareStartNode(#@UINODEID_STOPS_RUNNING_LOW#)
    #MP Expand StartNode(nodetype_alt, #@cal_stops_run_LOW#)
    {
        { //Display "running" and a number, without node timeout
            #MP Expand NodetType()
            -1, //-TMOUT_TICKS_REFRESH,
            #MP TEXTLABEL(RUNNING) ;//The label may be different, as in SVI2
            ENOFFS(XMODE_SETUP),
            NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
            NODE_LINK(cal_stops_run_LOW), //stay here on *
            XLATE_INDEX(xlate_SelectIfEnabled),
            .uid = UNITSID_DUMMY,
        },
        NULL,
        NODE_LINK(val_RawPos),
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_STOPS_RUNNING_HIGH#)
    #MP Expand StartNode(nodetype_alt, #@cal_stops_run_HIGH#)
    {
        { //Display "running" and a number, with a node timeout
            #MP Expand NodetType()
            -1, //-TMOUT_TICKS_REFRESH,
            #MP TEXTLABEL(RUNNING) ;//The label may be different, as in SVI2
            ENOFFS(XMODE_SETUP),
            NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
            NODE_LINK(cal_stops_run_HIGH), //stay here on *
            XLATE_INDEX(xlate_SelectIfEnabled),
            .uid = UNITSID_DUMMY,
        },
        NULL,
        NODE_LINK(val_RawPos),
    },
    #MP Expand EndNode()
#MP ;End process support
    #MP Expand StartNode(nodetype_xsel, "cal_stops_submenu")
    {
        {
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(AUTO_STOPS)
            UINODE_ENABLED,
            NODE_LINK(#mp%sUIGraphNodeNext),
            NODE_LINK(cal_stops_submenu), //stay here on *
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
        NULL, ui_process_FindStops
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, "cal_stops_manual")
    {
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(MAN_STOPS)
        UINODE_ENABLED,
        NODE_LINK(#mp%sUIGraphNodeNext),
        NODE_LINK(cal_stops_manual_low), //on *
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, "cal_stops_goback")
    {
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(GOBACK)
        UINODE_ENABLED,
        NODE_LINK(cal_stops_submenu), //wrap
        NODE_LINK(#mp%sCalStops_autoname), //on *
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP
#MP
#MP         ;----------------- Manual Find Stops support -------
    #MP Expand StartNode(nodetype_xsel, "cal_stops_manual_low")
    {
        {
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(STOP_LOW)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual_goback),
            NODE_LINK(cal_stops_manual_low_accept),
            XLATE_INDEX(xlate_StdWiz),
            .uid = UNITSID_NONE,
        },
        NULL, ui_IPout_low
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_alt, "cal_stops_manual_low_accept")
    {
        {
            #MP Expand NodetType()
            -1, //refresh every time
            #MP TEXTLABEL(ACCEPT_LOW)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual_goback),
            NODE_LINK(cal_stops_manual_low_failed), //on *
            XLATE_INDEX(xlate_StdWiz),
            .uid = UNITSID_DUMMY,
        },
        NULL,
        NODE_LINK(val_RawPos)
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_xsel, #@cal_stops_manual_low_failed#) ;pass through if OK
    {
        {
            #MP Expand NodetType()
            TMOUT_TICKS_DEFAULT,
            #MP TEXTLABEL(FAILED)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual), //go up regardless but display FAILURE on data save failure
            NODE_LINK(#mp%sUIGraphNodeNext),
            XLATE_INDEX(xlate_NextIfEnabled),
            .uid = UNITSID_NONE,
        },
        ui_SetLowStop, NULL // ui_SetLowStop() must return failure flag if fails
    },
    #MP Expand EndNode()
    #MP condex[UnLatchAtStop]
    #MP Expand StartNode(nodetype_xsel, "cal_stops_manual_high")
    {
        {
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(STOP_HIGH)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual_goback),
            NODE_LINK(cal_stops_manual_high_accept),
            XLATE_INDEX(xlate_StdWiz),
            .uid = UNITSID_NONE,
        },
        NULL, ui_IPout_high
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_alt, "cal_stops_manual_high_accept")
    {
        {
            #MP Expand NodetType()
            -1, //refresh every time
            #MP TEXTLABEL(ACCEPT_HIGH)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual_goback),
            NODE_LINK(cal_stops_manual_high_failed), //on *
            XLATE_INDEX(xlate_StdWiz),
            .uid = UNITSID_DUMMY,
        },
        NULL,
        NODE_LINK(val_RawPos)
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_xsel, #@cal_stops_manual_high_failed#) ;pass through if OK
    {
        {
            #MP Expand NodetType()
            TMOUT_TICKS_DEFAULT,
            #MP TEXTLABEL(FAILED)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual), //go up regardless but display FAILURE on data save failure
            NODE_LINK(cal_stops_manual_commit),
            XLATE_INDEX(xlate_NextIfEnabled),
            .uid = UNITSID_NONE,
        },
        ui_SetHighStop, NULL // ui_SetHighStop() must return failure flag if fails
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, "cal_stops_manual_commit")
    {
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(COMMIT)
        UINODE_ENABLED,
        NODE_LINK(cal_stops_manual_goback),
        NODE_LINK(cal_stops_manual_commit_failed),
        XLATE_INDEX(xlate_StdWiz),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_xsel, #@cal_stops_manual_commit_failed#) ;pass through if OK
    {
        {
            #MP Expand NodetType()
            TMOUT_TICKS_DEFAULT,
            #MP TEXTLABEL(FAILED)
            UINODE_ENABLED,
            NODE_LINK(cal_stops_manual), //go up regardless but display FAILURE on data save failure
            NODE_LINK(cal_stops_manual),
            XLATE_INDEX(xlate_NextIfEnabled),
            .uid = UNITSID_NONE,
        },
        ui_CommitStops, NULL // ui_SetHighStop() must return failure flag if fails
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, "cal_stops_manual_goback")
    { //Just display
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(GOBACK)
        UINODE_ENABLED,
        NODE_LINK(cal_stops_manual_low), //wrap around
        NODE_LINK(cal_stops_manual), //up
        XLATE_INDEX(xlate_StdWiz),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endm
