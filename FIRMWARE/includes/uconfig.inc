#MP If 0
Copyright 2006 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file uconfig.u
    \brief Project-independent configuration shared between Unimal and C

    CPU: Any

    OWNER: AK
#MP Endif
#MP
#MP ;This macro ensures that C and Unimal get identical definitions
#MP Macro ConfigExpand ;(name, value)
#MP     #1# = #2#
#MP     Ifdef ConfigExpand {NUM}
#MP         If Isconst(#2#)
#define #mp%n#1# #mp%d#2#
#MP         Else
#define #mp%n#1# #mp%n#2#
#MP         Endif
#MP     Endif
#MP Endm
#MP
#MP
#MP Expand ConfigExpand(OPTION_ON, 1) ;do not change
#MP Expand ConfigExpand(OPTION_OFF, 2) ;do not change
#MP
#MP
#MP ;options that Unimal must be aware of
#MP
#MP ;Before changing to OPTION_ON, make sure to correct, complete and test the code conditionally compiled out
#MP ;Additionally, 
#MP ;1. reenable HART (sub)commands in nvmclone.xml by removing the prefix "Disabled"
#MP ;2. add sha256.c shaseed.c hmac.c back to utilities\conf.mak
#MP Expand ConfigExpand(NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST, OPTION_OFF)
#MP ;This line marks the end of the source
