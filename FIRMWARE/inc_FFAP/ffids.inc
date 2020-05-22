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
    \file ffids.inc

    Man-made definitions of build ids for FFP (and APP for local UI)

    Owner: AK
    CPU: Any

*/
#MP Endif ;Tombstone header
#MP;  ======== FFP-specific ===============
#MP;  Device identification strings
#MP; Do not change unless instructed
#MP Setstr manufacturer_ID="004745"
#MP Setstr DEVICE_TYPE = "0008"
#MP ;FD_DOM_... used in ffid.u directly for now
#MP ;Setstr FD_DOM_DEV_REV="2"
#MP ;Setstr FD_DOM_DD_REV="1"
#MP ;Setstr FD_DOM_SW_REV="2-42    "

#MP Setstr DEVICE_REV="03"
#MP Setstr DD_REV="01"
#MP Setstr MIN_DD_REV="01" ;This is the *minimum* DD revision compatible with the firmware
#MP ;Softing ties the following with the previous by C flags -DRES_VAL_DEV_REV=0x$(DEVICE_REV)
#MP ;According to Vlad, they can go their separate ways if we wanted to
#MP Setstr RES_VAL_DEV_REV = DEVICE_REV
#MP ;Also from Softing C flag -DRES_VAL_DEV_TYPE=0x$(DEVICE_TYPE)
#MP Setstr RES_VAL_DEV_TYPE = DEVICE_TYPE
#MP Setstr RES_DEV_MINOR_REV="1"
#MP Setstr RES_BUILD="0"
#MP Setstr RES_BUILD_REV="0"

#MP ;Compatibility
#MP Setstr SW_FF_MAJOR = RES_VAL_DEV_REV
#MP COMPATIBILITY_REV = 3
#MP;/* This line marks the end of the source */
