#MP If 0
/**
Copyright 2004-2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file uinodedef.inc
    \brief Configuration of LCD UI nodes for MNCB

    This file cannot be processed by itself; it must be included in a
    .u file to generate the correct output.

    Pre-requisites: uinodes.inc included (it has all the macro definitions)

    CPU: Any

    OWNER: AK

    IMPORTANT:
    Pay close attention to defining the "node enabled" field. It must be
    of the form UINODE_ENABLED, UINODE_DISABLED or ENOFFS(en) where en is
    a valid element of the Enable structure defined elsewhere.
*/
#MP Endif

#MP
#MP ;Let's initialize text requests collection, minding that VARLABEL is implicit
#MP Setstr TEXTREQ_0 = "VARLABEL"
#MP TEXTREQ_0 = 0
#MP TEXTINUSE_VARLABEL = 1
#MP Setstr TEXTREQ_1 = "UNITS_SEPARATOR"
#MP TEXTREQ_1 = 1
#MP TEXTINUSE_UNITS_SEPARATOR = 1
#MP TEXTREQ_Count = 2 ;after adding VARLABEL and UNITS_SEPARATOR
#MP
#MP If FEATURE_UI_CYCLING_SIGNAL == FEATURE_UI_CYCLING_SIGNAL_SHOW
#MP     Setstr CyclingMenuStart = #@start_sig#
#MP Else
#MP     Setstr CyclingMenuStart = #@start_pos#
#MP Endif ;FEATURE_UI_CYCLING_SIGNAL == FEATURE_UI_CYCLING_SIGNAL_SHOW
#MP
#MP ;---- An info sequence in the cycling menu ---------
#MP Macro CycleMenu_TrippedOrFailed ;(node_name[, node_link])
#MP If FEATURE_UI_SHOW_TRIPPED == FEATURE_UI_SHOW_TRIPPED_ENABLED
    #MP Ifdef start_failhigh_count_%dpass {NUM}
    #MP     start_failhigh_count_%dpass = start_failhigh_count_%dpass + 1
    #MP Else
    #MP     start_failhigh_count_%dpass = 0
    #MP Endif
#MP If FAULTS_LATCH_IS_FAILSAFE == OPTION_ON
    #MP Expand StartNode(nodetype_nav, #1#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(IPTRIPPED)
        ENOFFS(iptripped), // enabled in non-OOS when tripped
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(start_failhigh_#mp%dstart_failhigh_count_%dpass),
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_NONE
    },
    #MP Expand EndNode()
#MP Else
    #MP Setstr latched_trip_node = {uJoin, #1#, "__latched__"}
    #MP Expand StartNode(nodetype_nav, #1#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(IPTRIPPED)
        ENOFFS(iptripped), // enabled in non-OOS when tripped
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(#mp%slatched_trip_node),
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_NONE
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, latched_trip_node)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(FLBL_LATCH_FSAFE)
        ENOFFS(iptripped_latched), // enabled in non-OOS when tripped
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(start_failhigh_#mp%dstart_failhigh_count_%dpass),
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_NONE
    },
    #MP Expand EndNode()
#MP Endif ;FAULTS_LATCH_IS_FAILSAFE == OPTION_OFF
    #MP nstart_failhigh_count_ = start_failhigh_count_%dpass ;get rid of composite name
    #MP Expand StartNode(nodetype_nav, {uJoin, "start_failhigh_", {%dnstart_failhigh_count_}})
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(FAILED)
        ENOFFS(failhigh), // enabled in non-OOS when a failhigh fault is present
        NODE_LINK(#mp%sMainMenuFirstNode),
      #MP If #0#>1
        NODE_LINK(#mp%s#2#),
      #MP Else ;If link is not supplied, take the next node
        NODE_LINK(#mp%sUIGraphNodeNext),
      #MP Endif
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_NONE
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_UI_SHOW_TRIPPED == FEATURE_UI_SHOW_TRIPPED_ENABLED
#MP Endm

#MP If FEATURE_UI_SHOW_TRIPPED == FEATURE_UI_SHOW_TRIPPED_ENABLED
#MP     Setstr CyclingMenuNodeAfterSignal = "TrippedFailed1"
#MP     If FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
#MP         Setstr CyclingMenuNodeAfterPos = "TrippedFailed2"
#MP         Setstr CyclingMenuNodeAfterPres = "TrippedFailed3"
#MP     Else
#MP         Setstr CyclingMenuNodeAfterPos = "TrippedFailed3"
#MP     Endif
#MP Else
#MP     Setstr CyclingMenuNodeAfterSignal = "start_pos"
#MP     If FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
#MP         Setstr CyclingMenuNodeAfterPos = "start_setpoint"
#MP         Setstr CyclingMenuNodeAfterPres = "working_setpoint1"
#MP        If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
#MP         Setstr CyclingMenuNodeAfterSetpoint = "start_pres"
#MP        Else
#MP         Setstr CyclingMenuNodeAfterSetpoint = CyclingMenuStart
#MP        Endif ;FEATURE_CPU
#MP     Else
#MP         Setstr CyclingMenuNodeAfterPos = CyclingMenuStart
#MP     Endif
#MP Endif ;FEATURE_UI_SHOW_TRIPPED == FEATURE_UI_SHOW_TRIPPED_ENABLED

#MP Ifdef UI_SuppressDeprecatedOutput
#MP Else
#define CyclingMenuStart #mp%sCyclingMenuStart
#MP If FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#define CyclingMenuNodeAfterSignal #mp%sCyclingMenuNodeAfterSignal
#MP Endif
#define CyclingMenuNodeAfterPos #mp%sCyclingMenuNodeAfterPos
#MP     If FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
#define CyclingMenuNodeAfterPres #mp%sCyclingMenuNodeAfterPres
#define CyclingMenuNodeAfterSetpoint #mp%sCyclingMenuNodeAfterSetpoint
#MP Endif
#MP Endif ;UI_SuppressDeprecatedOutput

#MP
#MP Expand StartNodeTable()
    #MP banner ;what we brag about on reset
#MP ;--------------- long automatically cycling loop where visibility (per mode) is controlled by 'enable' entries -------------
#MP If FEATURE_UI_CYCLING_SIGNAL == FEATURE_UI_CYCLING_SIGNAL_SHOW
    #MP Expand DeclareStartNode(#@UINODEID_INITNODE#)
    #MP Expand StartNode(nodetype_nav, #@start_sig#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(SIG)
        ENOFFS(OPMODE_OPERMAN), // enabled in non-OOS
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(var_start_sig),
        XLATE_INDEX(xlate_OperMenu1),
#MP If FEATURE_UI_CYCLING_SIGNAL_RES == FEATURE_UI_CYCLING_SIGNAL_RES_POINT3
        .uid = UNITSID_SIGNAL_ENTRY
#MP Endif
#MP If FEATURE_UI_CYCLING_SIGNAL_RES == FEATURE_UI_CYCLING_SIGNAL_RES_POINT1
        .uid = UNITSID_SIGNAL
#MP Endif
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_var, #@var_start_sig#)
    {
        #MP Expand NodetType()
        .checksum_offset = 0, //no checksum
        .en = UINODE_DISABLED,
        .parent = NODE_LINK(CyclingMenuNodeAfterSignal),
        .data_index = 0,
        .varfunc = VARFUNC(ui_GetSignal)
    },
    #MP Expand EndNode()
#MP Else
    #MP Expand DeclareStartNode(#@UINODEID_INITNODE#)
#MP Endif ;FEATURE_UI_CYCLING_SIGNAL == FEATURE_UI_CYCLING_SIGNAL_SHOW
    #MP Expand CycleMenu_TrippedOrFailed(CyclingMenuNodeAfterSignal) ;Automatic next node will be taken
    #MP Expand StartNode(nodetype_xsel, #@start_pos#)
    {
        {
            #MP Expand NodetType()
            TMOUT_TICKS_DEFAULT, //timeout
            #MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_DLT
            #MP TEXTLABEL(LEVEL)
            #MP Else
            #MP TEXTLABEL(POS)
            #MP Endif
            ENOFFS(OPMODE_OPER),  // enabled in OPREATE or MANUAL
            NODE_LINK(man_pos), //Instead of Fsafe (to pick up man_pos on mode switch; Fall down Fsafe from there
            NODE_LINK(var_start_pos),
            XLATE_INDEX(xlate_OperMenu1),
            .uid = UNITSID_POSITION
        },
        ui_DontHavePosition, NULL,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_var, #@var_start_pos#)
    {
        #MP Expand NodetType("UINODE_V32_FLAG")
        .checksum_offset = 0, //no checksum
        .en = UINODE_DISABLED,
        .parent = NODE_LINK(#mp%sUIGraphNodeNext),
        .data_index = 0,
        .varfunc = VARFUNC32(ui_GetPosition)
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_xsel, #@start_no_pos#)
    {
        {
            #MP Expand NodetType()
            TMOUT_TICKS_DEFAULT, //timeout
            #MP TEXTLABEL(NO_POS)
            ENOFFS(OPMODE_OPERMAN),  // enabled in OPREATE or MANUAL
            NODE_LINK(#mp%sUIGraphNodeNext),
            NODE_LINK(#mp%sUIGraphNodeNext),
            XLATE_INDEX(xlate_OperMenu1),
            .uid = UNITSID_NONE
        },
        ui_HavePosition, NULL,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_alt, #@man_pos#)
    {
        {
            #MP Expand NodetType()
            TMOUT_TICKS_DEFAULT, //timeout
            #MP TEXTLABEL(POSM)
            ENOFFS(OPMODE_MAN),  // enabled in MANUAL
            NODE_LINK(#mp%sMainMenuFirstNode),
            NODE_LINK(CyclingMenuNodeAfterPos),
            XLATE_INDEX(xlate_OperMenu1),
            .uid = UNITSID_POSITION
        },
        NULL,
        NODE_LINK(var_start_pos)
    },
    #MP Expand EndNode()
#MP If FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
    #MP Expand CycleMenu_TrippedOrFailed(CyclingMenuNodeAfterPos) ;Automatic next node will be taken
    #MP;//------------ Main PRESsure descriptor ------------------
    #MP Expand StartNode(nodetype_nav, "start_pres")
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(SPLY_PRES)
        ENOFFS(PRESS_ACTUATOR_TO_OPERMAN),
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(#mp%sUIGraphNodeNext),
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_PRESSURE
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_var, "var_start_pres")
    {
        #MP Expand NodetType()
        .checksum_offset = 0, //no checksum
        .en = UINODE_DISABLED,
        .parent = NODE_LINK(#mp%sUIGraphNodeNext),
        .data_index = 0,
        .varfunc = VARFUNC(ui_getSupplyPressure)
    },
    #MP Expand EndNode()
    #MP;//------------ Actuator PRESsure descriptor ------------------
    #MP Expand StartNode(nodetype_nav, "act_pres")
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(ACTR_PRES)
        ENOFFS(PRESS_ACTUATOR_TO_OPERMAN),
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(#mp%sUIGraphNodeNext),
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_PRESSURE
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_var, "var_act_pres")
    {
        #MP Expand NodetType()
        .checksum_offset = 0, //no checksum
        .en = UINODE_DISABLED,
        .parent = NODE_LINK(CyclingMenuNodeAfterPres),
        .data_index = 0,
        .varfunc = VARFUNC(ui_getMainPressure)
    },
    #MP Expand EndNode()
    #MP Expand CycleMenu_TrippedOrFailed(CyclingMenuNodeAfterPres, CyclingMenuStart)
#MP Else
    #MP CycleMenu_TrippedOrFailed(CyclingMenuNodeAfterPos, CyclingMenuStart)
#MP Endif ;FEATURE_PRESSURE_INPUTS_INCLUDED
#MP Expand CycleMenu_TrippedOrFailed(CyclingMenuNodeAfterPres) ;Automatic next node will be taken
#MP;//------------ Main Setpoint descriptor ------------------
#MP Expand StartNode(nodetype_nav, #@start_setpoint#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT, //timeout
        #MP TEXTLABEL(SETPOINT)
#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
        ENOFFS(OPMODE_OPER),  // enabled in OPREATE or MANUAL
#MP Else
        .en = UINODE_DISABLED,
#MP Endif
        NODE_LINK(#mp%sMainMenuFirstNode),
        NODE_LINK(#mp%sUIGraphNodeNext),
        XLATE_INDEX(xlate_OperMenu1),
        .uid = UNITSID_POSITION
    },
#MP Expand EndNode()
#MP Expand StartNode(nodetype_var, #@var_start_setpoint#)
    {
        #MP Expand NodetType()
        .checksum_offset = 0, //no checksum
        .en = UINODE_DISABLED,
        .parent = NODE_LINK(CyclingMenuNodeAfterSetpoint),
        .data_index = 0,
        .varfunc = VARFUNC(ui_GetSetpoint)
    },
#MP Expand EndNode()
#MP Expand CycleMenu_TrippedOrFailed(CyclingMenuNodeAfterSetpoint, CyclingMenuStart)

#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
    #MP condex(CycleMenu_FfVar)
#MP Endif ;FEATURE_CPU


#MP ;--------------- end of automatically cycling menu nodes --------------------
#MP
#MP ;--------------- long "+-"-navigable loop where visibility (per mode) is controlled by 'enable' entries -------------
#MP Setstr MainMenuFirstNode ="MainMenuFirstNode"
#MP If 0 ;Comment
The reason for seemingly pointless inclusion of SETUP group of nodes in this long loop is
that it is the easiest way to ensure that whenever someone sends UI to UINODEID_SETUPNODE
while we got failsafe or low power mode, the UI automatically advances accordingly
from here to the correct node (see ui_jump() for details). When not needed, it is disabled
#MP Endif ;comment
#MP Setstr SetupMenuFirstNode = MainMenuFirstNode
    #MP Expand DeclareStartNode(#@UINODEID_SETUPNODE#)
#MP Setstr uinode_autoname = SetupMenuFirstNode
        #MP ;----------------------Setup Menu Begining------------------------------
#MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_MNCB
    #MP Config ;Root node of configuration menu
    #MP Calib ;Root node of calibration menu
    #MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
        #MP Method
    #MP Endif
#MP Endif  ;FEATURE_HARDWARE_PLATFORM_MNCB
#MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_DLT
    #MP BasSetupRoot
    #MP AdvSetupRoot
    #MP
    #MP
#MP Endif  ;FEATURE_HARDWARE_PLATFORM_DLT
    #MP ;moved to ui_calib.c: condex(PSTSetup) ;Root of PST setup menu (if supported)
#MP;AK::--------------------------
#MP If FEATURE_POSITION_CONTROL == FEATURE_POSITION_CONTROL_INCLUDED
    #MP;//------------- Manual setpoint descriptor (2+1 nodes) ---------------
    #MP Setstr ManSp_autoname = "man_sp"
    #MP Save uinode_autoname
    #MP Expand StartNode(nodetype_nav, ManSp_autoname)
    { //- Manual SP (SetPoint) descriptor
        #MP Expand NodetType()
        -TMOUT_TICKS_REFRESH, //refresh rate
        #MP TEXTLABEL(SP_M)
        ENOFFS(NOFAILHIGH_AND_SETUP_OR_MANUAL),
        #MP over_the_var = UIGraphNode+8
        .advance = NODE_LINK(#mp%sUIGraphNode_%dover_the_var),
        #MP Setstr uinode_autoname = ManSp_autoname LockCheckSuffix ;
        .select = NODE_LINK(#mp%suinode_autoname),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_POSITION_ENTRY,
    },
    #MP Expand EndNode()
    #MP ProtectedEntry[%sManSp_autoname, CHECK_WRITE_PROTECTED, LOCK_SETUP]
    #MP Setstr uinode_autoname = ManSp_autoname TargetNodeSuffix
#MP
    #MP Expand StartNode(nodetype_nav, uinode_autoname)
    {
        #MP Expand NodetType()
        .tmout = 1,//smallest timeout
        #MP TEXTLABEL(SP_M)
        .en = UINODE_ENABLED,
        #MP over_the_var = UIGraphNode+2
        .advance = NODE_LINK(#mp%suinode_autoname),
        .select = NODE_LINK(var_man_sp),
        .xfuncx = XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_POSITION_ENTRY,
    },
    #MP Expand EndNode()
#MP
    #MP Expand StartNode(nodetype_xlimvar, #@var_man_sp#)
    { //- Manual setpoint variable
        {
            {
                #MP Expand NodetType()
                .checksum_offset = 0, //no checksum
                .en = UINODE_ENABLED, //if we got here, stay here (can be thrown out e.g. by failsafe)
                .parent = NODE_LINK(#mp%sManSp_autoname),
                .data_index = 0,
                .varfunc = VARFUNC(ui_getManSetpoint),
            },
            UI_VARLIM(&positionsp_range[0]),
            UI_VARLIM(&positionsp_range[1])
        },
        ui_setManSetpoint
    },
    #MP Expand EndNode()
    #MP Restore uinode_autoname
#MP ;;;If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_DLT
    #MP DevModesStretch ;not a submenu! inline stretch of modes
#MP ;;;Endif  ;FEATURE_HARDWARE_PLATFORM_DLT
#MP Endif ;FEATURE_POSITION_CONTROL_INCLUDED
#MP ;AK::--------
    #MP Expand StartNode(nodetype_xsel, #@man_viewData#)
    {
        {
            #MP Expand NodetType()
            0, //no timeout
            #MP TEXTLABEL(VIEW)
            //ENOFFS(OPMODE_OPERMAN),
            UINODE_ENABLED, //"VIEW DATA" menu enabled in all modes
            NODE_LINK(#mp%sUIGraphNodeNext),
            NODE_LINK(proxy_viewData),
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
#MP ;Temporary kludge until MNCB UI refactoring
#MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_MNCB
        NULL, ui_getCalibMenuData //display from local area so as not to create extra "enable" nodes
#MP Else
        NULL, NULL //display from local area so as not to create extra "enable" nodes
#MP Endif
    },
    #MP Expand EndNode()

#MP ViewClearFaults
#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
        #MP Simulation_root
#MP Endif ;// FEATURE_CPU
#MP condex(UnLatchMenu) ;trip unlatch menu (if supported)

#MP
    #MP condex(DispMode_Root)
    #MP ;--------------- end long "+-"-navigable loop where visibility (per mode) is controlled by 'enable' entries -------------
    #MP
    #MP
    #MP
    #MP ;-------------- top setup loop "+-"-navigable, with lock check on entry --------------
    #MP ;                   entry check
    #MP ;                 -- the setup loop proper --
    #MP Expand DeclareStartNode(#@HART_OVERRIDE_INFO_NODE#)
    #MP Expand StartNode(nodetype_nav, #@HART_override#)
    { //An indicator that HART kicked UI out of setup
        #MP Expand NodetType()
        0, //Bob & Larry want it persist - TMOUT_TICKS_DEFAULT,
        #MP TEXTLABEL(HART_OVERRIDE)
        ENOFFS(OPMODE_SETUP),
        NODE_LINK(#mp%sCyclingMenuStart),
        NODE_LINK(#mp%sCyclingMenuStart),
        XLATE_INDEX(xlate_NextIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP ;-------------- end top setup loop "+-"-navigable, with lock check on exit --------------
    #MP
    #MP
    #MP
    #MP
    #MP
#MP;//-------------- A long list of fault report nodes ------------
    #MP Expand StartNode(nodetype_nav, #@nofault_node#)
    {
        #MP Expand NodetType()
        -TMOUT_TICKS_REFRESH, //Refresh every half-second so that any new fault is displayed automatically
        #MP TEXTLABEL(LABEL_NOFAULT)
        ENOFFS(NOFAULT1),
        NODE_LINK(faultnode_0), //next
        NODE_LINK(man_viewFaults), //up
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
  #MP For fault_count = 0, NUM_DIFFERENT_FAULTS_PROJ-1
    #MP Expand StartNode(nodetype_nav, #@faultnode_#, fault_count)
    {
        #MP Expand NodetType()
        -TMOUT_TICKS_REFRESH, //refresh
        #MP Setstr helper = LABEL_FAULT_%ufault_count
        #MP TEXTLABEL(%shelper)
        ENOFFS(FAULT#mp%ufault_count),
       #MP ;next node wraps around if it's the last one
       #MP If fault_count == NUM_DIFFERENT_FAULTS_PROJ-1
        NODE_LINK(viewfaults_goback), //wrap
       #MP Else ;link to next
       #MP Set temp = fault_count+1
        NODE_LINK(faultnode_#mp%dtemp), //next
       #MP Endif
        NODE_LINK(man_viewFaults), //up
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
  #MP Endfor
    #MP Expand StartNode(nodetype_nav, "viewfaults_goback")
    { //Just display
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(GOBACK)
        UINODE_ENABLED,
        NODE_LINK(nofault_node), //wrap around
        NODE_LINK(man_viewFaults), //up
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()

#MP;//-------- End of the long list of fault report nodes ----------------------
#MP;
#MP;//-------- View Data menu --------------------------------------------------

#MP;    // dummy node to get info from configuration module
#MP If 0 ;Comment
In the current UI implementation, there is a problem with descending into a
submenu with a SELECT action: if the first node is disabled, the UI engine
passes through it to whatever follows.
A workaround is to have an artificial node with timeout 1 which would be
always enabled and transition to the ADVANCE node right away.
#MP Endif ;Comment
    #MP Expand StartNode(nodetype_nav, #@proxy_viewData#)
    {
        #MP Expand NodetType()
        1, //smallest timeout
        #MP TEXTLABEL(VIEW)
        UINODE_ENABLED,
        NODE_LINK(#mp%sUIGraphNodeNext),
        NODE_LINK(man_viewData),
        //NODE_LINK(#mp%sUIGraphNodeNext),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP condex(view_Version, man_viewData)
    #MP condex(view_VersionFF, man_viewData)

#MP ;EJ::-- begin of node [ff_Info]  ------
#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
    #MP Expand StartNode(nodetype_nav, #@ff_Info#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(FF_INFO)
        UINODE_ENABLED, //"FF Info" menu enabled in all modes
        NODE_LINK(#mp%sUIGraphNodeNext),
        NODE_LINK(proxy_ffInfo),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;------ end of node [ff_Info] -----------

    #MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_DLT
    #MP ViewBasSetupRoot
    #MP ViewAdvSetupRoot
    #MP DiagnRoot
    #MP SGMeter
    #MP
        #MP Endif  ;FEATURE_HARDWARE_PLATFORM_DLT
#MP If FEATURE_POSITION_CONTROL == FEATURE_POSITION_CONTROL_INCLUDED
    #MP Expand StartNode(nodetype_nav, #@view_ActSingle#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(SINGLEACT)
        ENOFFS(Act_Single),
        NODE_LINK(view_ActDouble),
        NODE_LINK(man_viewData),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, #@view_ActDouble#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(DOUBLEACT)
        ENOFFS(Act_Double),
        NODE_LINK(view_Air2open),
        NODE_LINK(man_viewData),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_POSITION_CONTROL_INCLUDED

#MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_MNCB
#MP;    //-------- Air to Open/Close -------------
    #MP Expand StartNode(nodetype_nav, #@view_Air2open#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(ATO)
        ENOFFS(AIR_TO_OPEN_),
        NODE_LINK(view_Air2close),
        NODE_LINK(man_viewData),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, #@view_Air2close#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(ATC)
        ENOFFS(AIR_TO_CLOSE_),
        NODE_LINK(#mp%sUIGraphNodeNext),
        NODE_LINK(man_viewData),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_HARDWARE_PLATFORM_MNCB
#MP ;------------view open/stop adjustment ----------------------
#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
#MP condex(Cal_Open_Stop_View)
#MP Endif ;FEATURE_CPU_STM32F10xxE
#MP ;------------------------------------------------------------
#MP condex(SigSpCharact_View)

#MP If FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
    #MP;    //-------------- Pressure units -------------------
    #MP Expand StartNode(nodetype_nav, "view_Press")
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(UNITS_PREFIX)
        ENOFFS(PRESS_ACTUATOR),
        NODE_LINK(#mp%sUIGraphNodeNext),
        NODE_LINK(man_viewData),
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_PRESSURE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_PRESSURE_INPUTS_INCLUDED
#MP
#MP condex(TightShutoffLo_View)
#MP condex(TightShutoffHi_View)
#MP condex(Manual_Tune_View)
#MP condex(View_RawPosVal)
#MP
#MP condex(ViewSignalCal)
#MP
#MP condex(ViewData_PST, viewdata_goback)
    #MP Expand StartNode(nodetype_nav, "viewdata_goback")
    { //Just display
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(GOBACK)
        UINODE_ENABLED,
        NODE_LINK(view_Version), //wrap around
        NODE_LINK(man_viewData), //do it on *
        XLATE_INDEX(xlate_StdMenu),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP
#MP;    //-------------- end "view data" menu ------------
#MP
#MP ;----------------- Long process display support -------

#MP condex(PST_RunInfo)

#MP If FEATURE_ESD_CONTINUOUS_DIAGS == FEATURE_ESD_CONTINUOUS_DIAGS_SUPPORTED
    #MP Expand DeclareStartNode(#@UINODEID_PNEUMATIC_TEST_RUNNING#)
    #MP Expand StartNode(nodetype_nav, #@ui_pneu_run#)
    { //Just display
        #MP Expand NodetType()
        -TMOUT_TICKS_REFRESH,
        #MP TEXTLABEL(PNEU_RUNNING)
        ENOFFS(EN_PNEU_ON),
        NODE_LINK(canceled_pneu), //proceed to analyze the outcome
        NODE_LINK(ui_pneu_run),  //pushbuttons will have us stuck here
        XLATE_INDEX(xlate_SelectIfEnabled), //To allow falling through the cycling menu in OOS
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, "canceled_pneu")
    {
        #MP Expand NodetType()
        TMOUT_TICKS_CANCELED,
        #MP TEXTLABEL(MSG_CANCELED)
        ENOFFS(EN_PNEU_CANCELED),
        NODE_LINK(CyclingMenuStart), //do it on any key
        NODE_LINK(CyclingMenuStart), //do it on disabled node
        XLATE_INDEX(xlate_NextIfEnabled), //To allow falling through the cycling menu in OOS
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_ESD_CONTINUOUS_DIAGS == FEATURE_ESD_CONTINUOUS_DIAGS_SUPPORTED

#MP If FEATURE_POSITION_CONTROL == FEATURE_POSITION_CONTROL_INCLUDED
    #MP Expand DeclareStartNode(#@UINODEID_TUNE1#)
    #MP Expand StartNode(nodetype_xsel, #@cal_tune_1#)
    { //display "step 1/3" AND refresh all calibration menu data
        {
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(TUNE1)
            ENOFFS(XMODE_SETUP),
            NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
            NODE_LINK(cal_tune), //do it on *
            XLATE_INDEX(xlate_SelectIfEnabled),
            .uid = UNITSID_NONE,
        },
        ui_getCalibMenuData, NULL
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_TUNE2#)
    #MP Expand StartNode(nodetype_nav, #@cal_tune_2#)
    { //Just display "step 2/3"
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(TUNE2)
        ENOFFS(XMODE_SETUP),
        NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(cal_tune), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_TUNE3#)
    #MP Expand StartNode(nodetype_nav, #@cal_tune_3#)
    { //Just display "step 3/3"
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(TUNE3)
        ENOFFS(XMODE_SETUP),
        NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(cal_tune), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_TUNE_OK#)
    #MP Expand StartNode(nodetype_nav, #@cal_tune_ok#)
    { //Just display "tune ok"
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT,
        #MP TEXTLABEL(TUNEOK)
        ENOFFS(OPMODE_SETUP),
        NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(cal_tune), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_TUNE_FAILED#)
    #MP Expand StartNode(nodetype_alt, #@cal_tune_failed#)
    {
        { //Just display "failed"
            #MP Expand NodetType()
            0,
            #MP TEXTLABEL(FLBL_AUTOTUNE_FAILED) ;reuse the text
            ENOFFS(OPMODE_SETUP),
            NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
            NODE_LINK(cal_tune), //do it on *
            XLATE_INDEX(xlate_SelectIfEnabled),
            .uid = UNITSID_DUMMY,
        },
        NULL,
        NODE_LINK(var_misc)
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_POSITION_CONTROL_INCLUDED
#MP
    #MP condex(var_misc) ;stick a required var node somewhere
#MP
#MP If FEATURE_POSITION_CONTROL == FEATURE_POSITION_CONTROL_INCLUDED
    #MP Expand DeclareStartNode(#@UINODEID_TUNE_PROTECTED#)
    #MP Expand StartNode(nodetype_nav, #@cal_tune_protected#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT,
        #MP TEXTLABEL(TUNELOCK)
        ENOFFS(OPMODE_SETUP),
        NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(cal_tune), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_POSITION_CONTROL_INCLUDED
#MP ;While we are at it, diagnostic things
#MP If FEATURE_DIAG_POSITIONER_DIAG == FEATURE_DIAG_POSITIONER_DIAG_INCLUDED
    #MP Expand DeclareStartNode(#@UINODEID_DIAG_EX#)
    #MP Expand StartNode(nodetype_nav, #@diag_ex#)
    {
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(UINODE_DIAG_EX)
        ENOFFS(XMODE_SETUP),
        NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(#mp%sSetupMenuFirstNode), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_DIAG_STD#)
    #MP Expand StartNode(nodetype_nav, #@diag_std#)
    {
        #MP Expand NodetType()
        0,
        #MP TEXTLABEL(UINODE_DIAG_STD)
        ENOFFS(OPMODE_SETUP),
        NODE_LINK(#mp%sMainMenuFirstNode), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(#mp%sSetupMenuFirstNode), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_DIAG_POSITIONER_DIAG == FEATURE_DIAG_POSITIONER_DIAG_INCLUDED
#MP ;End diagnostic things
#MP
#MP
#MP If FEATURE_BUMPLESS_XFER == FEATURE_BUMPLESS_XFER_ENABLED
    #MP Expand DeclareStartNode(#@UINODEID_BUMPLESS_XFER#)
    #MP Expand StartNode(nodetype_nav, #@bumpless_xfer#)
    {
        #MP Expand NodetType()
        0, //no timeout
        #MP TEXTLABEL(BUMPLESS_XFER)
        UINODE_ENABLED,
        NODE_LINK(xfer_failed), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(xfer_failed), //do it on *
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand DeclareStartNode(#@UINODEID_BUMPLESS_XFER_FAILED#)
    #MP Expand StartNode(nodetype_nav, #@xfer_failed#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT,
        #MP TEXTLABEL(FAILED)
        UINODE_ENABLED,
        NODE_LINK(man_toOper), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(xfer_failed_failed), //do it on *
        XLATE_INDEX(xlate_NextIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_nav, #@xfer_failed_failed#)
    {
        #MP Expand NodetType()
        TMOUT_TICKS_DEFAULT,
        #MP TEXTLABEL(FAILED)
        UINODE_ENABLED,
        NODE_LINK(Fsafe), //On Advance (from ui_jump()) honor the mode
        NODE_LINK(Fsafe), //do it on *
        XLATE_INDEX(xlate_NextIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
#MP Endif ;FEATURE_BUMPLESS_XFER == FEATURE_BUMPLESS_XFER_ENABLED
#MP
#MP ; ------------------ Callable subgraphs -------------------
    #MP ; ----------- all locked (standalone) -----------
    #MP Expand DeclareStartNode(#@UINODEID_LOCKNODE#)
    #MP Expand StartNode(nodetype_nav, #@btn_lock#)
    {
        #MP Expand NodetType(#@UINODE_RETFLAG#)
        TMOUT_TICKS_DEFAULT,
        #MP TEXTLABEL(BUTTONS_LOCKED)
        UINODE_ENABLED,
        NODELINK_NONE, //don't care
        NODELINK_NONE, //return
        XLATE_INDEX(xlate_SelectIfEnabled),
        .uid = UNITSID_NONE,
    },
    #MP Expand EndNode()
    #MP condex(DispMode_Nodes)

#MP If FEATURE_CUSTOM_UNITS == FEATURE_CUSTOM_UNITS_SUPPORTED
    #MP CustomUnitsMenu[Level_units_root, UNITSID_POSITION]
#MP Endif ;FEATURE_CUSTOM_UNITS_SUPPORTED

#MP If FEATURE_WPROTECT_CLRERR == FEATURE_WPROTECT_CLRERR_FALSE
    #MP ProtectedEntry[man_clrFaults, 0, LOCK_ANYWRITE]
#MP Else
    #MP ProtectedEntry[man_clrFaults, CHECK_WRITE_PROTECTED, LOCK_ANYWRITE]
#MP Endif
    #MP Expand StartNode(nodetype_xsel, #@man_clrFaults_Do#)
    {
        {
            #MP Expand NodetType()
            0, //no timeout
            #MP TEXTLABEL(CLRFLT)
            UINODE_ENABLED,
            .advance = NODE_LINK(#mp%sUIGraphNodeNext), //don't care
            .select = NODE_LINK(man_clrFaults), //return
            XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_NONE,
        },
        ui_clearFaults, NULL //the entry function must keep this node disabled
    },
    #MP Expand EndNode()

#MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_DLT
    #MP BasSetupMenu
    #MP AdvSetupMenu
    #MP DiagnMenu
    #MP SignalGeneratorMenu
    #MP ATune_HelperNodes
    #MP SGMeterMenu ; for VIEW DATA
    #MP ViewBasSetupMenu ; for VIEW DATA
    #MP ViewAdvSetupMenu ; for VIEW DATA
#MP Endif  ;FEATURE_HARDWARE_PLATFORM_DLT

#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
    #MP FFBasSetupMenu
    #MP FFAdvSetupMenu
    #MP MethodMenu
#MP Else
#MP If FEATURE_HARDWARE_PLATFORM == FEATURE_HARDWARE_PLATFORM_MNCB
    #MP CalibMenu
    #MP ConfigMenu
#MP Endif  ;FEATURE_HARDWARE_PLATFORM_MNCB
#MP Endif  ;FEATURE_CPU_STM32F10xxE

#MP If (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
#MP Expand subMenu_ffInfo()
#MP Expand Simulation_sub()
#MP Endif
#MP DevModesHelpers ;misc. supporting nodes for device mode change
#MP PSTSetupMenu ;PST setup submenu (if supported)

#MP Expand EndNodeTable()
#MP
#MP ;/* This line marks the end of the source */
