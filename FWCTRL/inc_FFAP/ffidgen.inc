#MP If 0 ;Tombstone header
/*
Copyright 2014 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ffidgen.inc

    Generation engine of build ids for FFP (and APP for local UI)

    Owner: AK
    CPU: Any

*/
#MP Endif ;Tombstone header
#MP Macro Cparam_prepare
#MP ;NOTE: Names are chosen compatible with Softing code
#MP ;Current definition:  RES_VAL_DEV_REV.RES_DEV_MINOR_REV.RES_BUILD.RES_BUILD_REV, thus:
#MP atoi[DEVICE_REV]
#MP Setstr RES_VAL_DEV_REV = {%dDEVICE_REV} ;remove padding, if any
#MP atoi[RES_VAL_DEV_REV]

#MP atoi[RES_DEV_MINOR_REV]
#MP Setstr SW_FF_MINOR = {%dRES_DEV_MINOR_REV} ;remove padding, if any
#MP atoi[SW_FF_MINOR]

#MP atoi[RES_BUILD]
#MP Setstr SW_FF_BUILD = {%dRES_BUILD} ;remove padding, if any
#MP atoi[SW_FF_BUILD]

#MP atoi[RES_BUILD_REV]
#MP Setstr SW_FF_REVISION = {%dRES_BUILD_REV} ;remove padding, if any
#MP atoi[SW_FF_REVISION]

#MP atoi[DEVICE_TYPE]
#MP ;Setstr DEVICE_TYPE = {%dDEVICE_TYPE} ;remove padding, if any

#MP atoi[MIN_DD_REV]
#MP atoi[DD_REV]

#MP Endm
#MP;/* This line marks the end of the source */

