/*
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvramtypes.h
    \brief Collection of all types for NVRAM layout and interface.

    CPU: Any

    OWNER: AK

    \ingroup nvmem
*/

#ifndef NVRAMTYPES_H_
#define NVRAMTYPES_H_

/* Need to #include all NVRAM types.
*/
#include "projectdef.h"
#include "nvram.h"
#include "poscharact.h"
#include "tempcomp.h"
#include "faultpublic.h"
#include "smoothing.h"
#include "devicemode.h"
#include "configure.h"
#include "tempr.h"
#include "selftune.h"
#include "control.h"
#include "errlimits.h"
#include "tempcomp.h"
#include "diagnostics.h"
#include "hart.h"
#include "ctllimits.h"
#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_SIMPLE
#include "uisimple.h"
#include "uilock.h"
#include "osadjust.h"
#endif
#if FEATURE_LOCAL_UI == FEATURE_LOCAL_UI_LCD
#include "uipublic.h"
#include "uimenued.h"
#endif
#if FEATURE_BUMPLESS_XFER == FEATURE_BUMPLESS_XFER_ENABLED
#include "bumpless.h"
#endif
#if FEATURE_ACTIVATION == FEATURE_ACTIVATION_ID_SN
#   include "activate_id_sn.h"
#endif

#if FEATURE_SIGNAL_SETPOINT == FEATURE_SIGNAL_SETPOINT_SUPPORTED
#include "signalsp.h"
#endif

#if FEATURE_DIGITAL_SETPOINT == FEATURE_DIGITAL_SETPOINT_SUPPORTED
#include "digitalsp.h"
#endif

#include "nvmempriv.h"
// - needed for I/P disconnect - #if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#include "sysiolopwr.h"
//#endif
#include "mncbdefs_proj.h"
#include "interfacenvm.h"

//Need this for I/P disconnect detection -
#include "iplimit.h"

#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#   include "insignal.h"
#endif
#include "pwmcomp.h"
#if FEATURE_PVINPUT_SENSOR == FEATURE_PVINPUT_SENSOR_AVAILABLE
#   include "inpv.h"
#endif
#include "tempr_mncb.h"
#include "posint.h"
#if FEATURE_REMOTE_POSITION_SENSOR == FEATURE_REMOTE_POSITION_SENSOR_AVAILABLE
#   include "adtbl.h"
#   include "posext.h"
#endif
#include "ipcurr.h"
#if FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED
#   include "pneumatics.h"
#   include "prestab.h"
#endif
#if FEATURE_AO == FEATURE_AO_SUPPORTED
#include "ao.h"
#include "osubrange.h"
#endif

#include "doswitch.h"

#include "ifman.h"
#include "refvoltage.h"

#if (FEATURE_CPU == FEATURE_CPU_STM32F10xxE) || (FEATURE_CPU == FEATURE_CPU_pm2kSTM32F10xxE)
#include "ff_devicevars.h"
#else
//Huge kludge matching the one in nvramdef.inc
#include "longtag.h"
#endif

#if FEATURE_LOGFILES == FEATURE_LOGFILES_USED
#include "logfile.h"
#endif

#if FEATURE_PARTIAL_STROKE_TEST == FEATURE_PARTIAL_STROKE_TEST_SUPPORTED
#include "pstshell.h"
#include "pst.h"
#endif
#include "datahog.h"
#include "dhogtrigger.h"

#include "facdefaults.h"
#include "lcdio.h"

#ifdef OLD_NVRAM
#define NV_HEADERSIZE 1u //size of the header of a NVRAM record
#define NV_NUMCOPIES 2u //number of copies in the record
#else
//These are coming from nvmempreiv.h - don't belong here
#endif //OLD_NVRAM

#endif //NVRAMTYPES_H_
/* This line marks the end of the source */

