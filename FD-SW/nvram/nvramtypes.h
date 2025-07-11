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
    \brief Collection of all types for NVRAM layout and interface in FFP.

    CPU: Any

    OWNER: AK

    \ingroup nvmem
*/
#ifndef NVRAMTYPES_H_
#define NVRAMTYPES_H_

/* Need to #include all NVRAM types.
*/
//#include "projectdef.h"
#include "nvram.h"
#include "faultpublic.h"
#include "mnassert.h"

#include "nvmempriv.h"
#include "mncbdefs_proj.h"
#include "interfacenvm.h"

#include "mn_advanced.h"
#include "logfile.h"

#include "eepshim.h"
#include "ff2nvram.h"

#include "facdefaults.h"

#include "histogram.h"
#include "mn_trends.h"

#include "mn_actuator_3.h"
#include "pressure_range.h"

#include "syncpatches.h"

#include "mn_fwdl.h"

#include <hm_api.h>

#ifndef EXTMEM
#define EXTMEM /*nothing*/
#endif

#endif //NVRAMTYPES_H_
/* This line marks the end of the source */

