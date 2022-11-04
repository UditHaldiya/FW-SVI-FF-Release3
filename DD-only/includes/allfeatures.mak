ifeq (0,1) #Tombstone header
Copyright 2006 by Dresser = Inc. = as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser = Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such = no part of it may be made public,
decompiled = reverse engineered or copied and it is subject to return upon
demand.

    \file includes/allfeatures.inc
    \brief Universal feature definitions for all projects.

    All projects of the family must select a complete feature set from the options
    defined here. See includes/project_<PROJ>/projectdef.inc for the use of the
    definitions.

    Definition syntax:
    FEATUREOPT_feature_name = feature_option_name_list

    OWNER: AK
    $Archive: /MNCB/Dev/FIRMWARE/includes/allfeatures.mak $
    $Date: 12/07/11 11:57a $
    $Revision: 14 $
    $Author: Arkkhasin $
    $History: allfeatures.mak $
 *
 * *****************  Version 14  *****************
 * User: Arkkhasin    Date: 12/07/11   Time: 11:57a
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * TFS:8204 - features for I/O channels
 *
 * *****************  Version 13  *****************
 * User: Arkkhasin    Date: 12/02/10   Time: 12:32p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * TFS:4922 Added features for activation and open stop adjustment
 *
 * *****************  Version 12  *****************
 * User: Arkkhasin    Date: 10/06/10   Time: 10:31p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Added FEATUREOPT_WRITEPROTECT
endif #Tombstone header

# --------------- large-scale stuff -------------
FEATUREOPT_CPU = LPC21x4 STM32F10xxE pm2kSTM32F10xxE
FEATUREOPT_POSITION_CONTROL = INCLUDED EXCLUDED
FEATUREOPT_HARDWARE_PLATFORM = MNCB DLT LCX
FEATUREOPT_LOCAL_UI = NONE LCD SIMPLE
FEATUREOPT_HART_TRANSMITTER_COMMANDS = INCLUDED EXCLUDED
FEATUREOPT_CONTROL_LIMITS = INCLUDED EXCLUDED
FEATUREOPT_AO_RETRANSMIT = AVAILABLE UNAVAILABLE
FEATUREOPT_ACTIVATION = NONE ID_SN

# -------------- I/O channels --------------------
FEATUREOPT_PRESSURE_INPUTS = INCLUDED EXCLUDED
FEATUREOPT_PRESSURE_SENSOR_1 = SUPPORTED UNSUPPORTED
FEATUREOPT_PRESSURE_SENSOR_2 = SUPPORTED UNSUPPORTED
FEATUREOPT_PRESSURE_SENSOR_3 = SUPPORTED UNSUPPORTED
FEATUREOPT_PRESSURE_SENSOR_PILOT = SUPPORTED UNSUPPORTED
FEATUREOPT_PRESSURE_SENSOR_ATM = SUPPORTED UNSUPPORTED
FEATUREOPT_REMOTE_POSITION_SENSOR = AVAILABLE UNAVAILABLE
FEATUREOPT_PVINPUT_SENSOR = AVAILABLE UNAVAILABLE
FEATUREOPT_LOOPSIGNAL_SENSOR = SUPPORTED UNSUPPORTED
# --------------- Analog Output support ------------------------------
FEATUREOPT_AO = SUPPORTED UNSUPPORTED
#FEATUREOPT_CTLOUT = SUPPORTED UNSUPPORTED


# --------------- presentation features -----------------------------
FEATUREOPT_CUSTOM_UNITS = SUPPORTED UNSUPPORTED

# --------------- diagnostic features -----------------------------
FEATUREOPT_DIAG_POSITIONER_DIAG = INCLUDED EXCLUDED
FEATUREOPT_PARTIAL_STROKE_TEST = SUPPORTED UNSUPPORTED #Partial stroke test support
FEATUREOPT_ESD_LIMITED_HART_CMDS = EXCLUDED INCLUDED #certain hart commands excluded in esd //AK:TODO
FEATUREOPT_TERMINAL_BOARD_TEST = SUPPORTED UNSUPPORTED #Partial stroke test support
FEATUREOPT_ESD_CONTINUOUS_DIAGS = SUPPORTED UNSUPPORTED #Partial stroke test support //AK:TODO

#------------- bumpless transfer -------------
FEATUREOPT_BUMPLESS_XFER = ENABLED DISABLED  #Bumpless transfer supported in the project

# --------------- pusbuttons/LCD/LED UI features -----------------------------
FEATUREOPT_UI_TRANSITION_FSAFE2MANUAL = ENABLED DISABLED #Allow failsafe to manual transition
FEATUREOPT_UI_TRANSITION_FSAFE2SETUP = ENABLED DISABLED #Allow failsafe to setup transition
FEATUREOPT_UI_SHOW_TRIPPED = ENABLED DISABLED #Show TRIPPED in the cycling menu
FEATUREOPT_UI_CYCLING_SIGNAL = SHOW DONT_SHOW #Show signal in the cycling menu
FEATUREOPT_UI_CYCLING_SIGNAL_RES = POINT1 POINT3 #Show signal in the cycling menu with 1 or 3 decimal digits
FEATUREOPT_UI_TIGHT_SHUTOFF = SHOW DONT_SHOW #Display TSO config menu
FEATUREOPT_UI_CHARACTERIZATION = SHOW DONT_SHOW #Display characterization config menu
FEATUREOPT_UI_OPSTOP_ADJ = SHOW DONT_SHOW PROCESS #Display Open Stop Adjustment calib menu or start an interactive adj
FEATUREOPT_UI_SIGNAL_LIMITS = SHOW DONT_SHOW #Display signal limits (split range) calib menu

# --------------- setpoint features -----------------------------
FEATUREOPT_SIGNAL_SETPOINT = SUPPORTED DROPPED #Support for signal setpoint
FEATUREOPT_DIGITAL_SETPOINT = SUPPORTED DROPPED #Support for digital setpoint in normal mode

# --------------- shutdown monitoring ---------------------
FEATUREOPT_EVENT_MONITOR_SHUTDOWN = SUPPORTED UNSUPPORTED #Shutdown event watched?
FEATUREOPT_SOFTWARE_SHUTDOWN = ENABLED DISABLED #Shutdown event watched?

# --------------- fault storage features ---------------------
FEATUREOPT_USER_FAULT_CATEGORIES = SUPPORTED UNSUPPORTED #Allow user fault categories?
# This line marks the end of the source

# --------------- DO switch 1 features ----------------------
FEATUREOPT_DO1_OVERRIDE_OPTION_CONFIG = FALSE TRUE #Ignore OptionConfig flag when processing the switch?
FEATUREOPT_DO1_ACTION_CONFIGURABLE = FALSE TRUE #Allow configuration of when the switch is asseted ?
FEATUREOPT_DO1_DIRECTION_CONFIGURABLE = FALSE TRUE #Allow configuration of switch assert as open or closed?
# --------------- DO switch 2 features ----------------------
FEATUREOPT_DO2_OVERRIDE_OPTION_CONFIG = FALSE TRUE #Ignore OptionConfig flag when processing the switch?
FEATUREOPT_DO2_ACTION_CONFIGURABLE = FALSE TRUE #Allow configuration of when the switch is asseted ?
FEATUREOPT_DO2_DIRECTION_CONFIGURABLE = FALSE TRUE #Allow configuration of switch assert as open or closed?

# --------------- Log file system ---------------------------
FEATUREOPT_LOGFILES = USED NOTUSED
# --------------- Write-protect hardware -------------
FEATUREOPT_WRITEPROTECT = NONE HWJUMPER
# --------------- Write-protect jumper behavior -------------
FEATUREOPT_WPROTECT_MODE = FALSE TRUE ENABLE_UPMODE #Mode change from UI is write-protected by jumper
FEATUREOPT_WPROTECT_CLRERR = FALSE TRUE #Clear errors from UI is write-protected by jumper
#Note: Similar stuff for HART is configured in message flags in xml definitions
