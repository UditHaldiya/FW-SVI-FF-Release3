#/**
#Copyright 2008 by Dresser, Inc., as an unpublished work.  All rights reserved.
#
#This document and all information herein are the property of Dresser, Inc.
#It and its contents are  confidential and have been provided as a part of
#a confidential relationship.  As such, no part of it may be made public,
#decompiled, reverse engineered or copied and it is subject to return upon
#demand.
#
#    \file reqimport.mak
#    \brief Common makefile for extracting various requirements to the build
#
#    CPU: makefile is good for any platform running GNU make.
#
#    OWNER: AK
#    \n RCS: $Id: $
#     $DateTime: 11-AUG-2004 $ $Change: $ $Author: Arkkhasin $
#*/

include $(DIRWALK)

REQIMPORT : $(FORCED_DEPENDENCY)  $(SUBDIR_EFFECTIVE)

$(SUBDIR_EFFECTIVE) : force
    $(MAKE) REQIMPORT -C $@ -f $(REQIMPORT)

force : ;