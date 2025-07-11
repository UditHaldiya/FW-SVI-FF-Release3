#/**
#Copyright 2005 by Dresser, Inc., as an unpublished work.  All rights reserved.
#
#This document and all information herein are the property of Dresser, Inc.
#It and its contents are  confidential and have been provided as a part of
#a confidential relationship.  As such, no part of it may be made public,
#decompiled, reverse engineered or copied and it is subject to return upon
#demand.
#
#    \file dirwalk.mak
#    \brief An include makefile encapsulating directories walk
#
#    Includes individual conf.mak files and resolves include and descend directories
#
#    OWNER: AK
#    $Archive: /MNCB/Dev/FIRMWARE/buildhelpers/dirwalk.mak $
#    $Date: 9/23/11 5:14p $
#    $Revision: 23 $
#    $Author: Arkkhasin $
#


#Machinations to get project-relative path
_CURDIR:=$(subst /,\,$(CURDIR))#Current directory with backslashes
_PROJDIR:=$(subst \,/,$(PROJDIR))#change to forward slashes
_RELDIR_RAW:=$(subst $(_PROJDIR),,$(CURDIR))#get relative directory path
#Remove the leading slash if it is there
DISAMBIGUATOR:=@@@@#Any odd-looking pattern without blanks is OK
_RELDIR_RAW1=$(addprefix $(DISAMBIGUATOR),$(_RELDIR_RAW))
_RELDIR_RAW2=$(subst $(DISAMBIGUATOR)/,,$(_RELDIR_RAW1))
_RELDIR=$(subst $(DISAMBIGUATOR),,$(_RELDIR_RAW2))#cleanup
RELDIR:=$(subst /,\\,$(_RELDIR))#back to backslashes, doubled for sed

#Local copy of top-level dependencies
local_topdep := $(topdep)
#An updated top-level dependencies set for subdirectory
export topdep := $(addprefix ../,$(LOCAL_CONF) $(local_topdep))

#Relative path to the project root
PATH2PROJROOT:=$(PROJROOTPATH)
export PROJROOTPATH:=..\$(PROJROOTPATH)

.DELETE_ON_ERROR : ;

include $(scripts)
include $(PROJECT_INCDIR)/projfeatures.mak

# include the makefile from the current directory.
# This should bring the definitions of SOURCE, ASOURCE SUBDIR, ISUBDIR etc.
# If the file doesn't exist, empty strings will **NOT** be "imported"
ifdef NOGEN
else
modconf_$(PROJ).mak : .force
    if exist $@.candidate $(cmpcpy) $@.candidate $@
endif

-include $(LOCAL_CONF)
-include modconf_$(PROJ).mak

%_config.h : %_config.mak  $(helpers)\modconfig.mak
    @echo Building $@ from $<
    $(paws)
    $(MAKE) -f $(helpers)\modconfig.mak src=$(@:.h=.mak)
	
#Ensure everything in the directory's conf has been seen
.PHONY : $(component_configuration)
comp_headers:= $(addsuffix .h, $(component_configuration))
FORCED_DEPENDENCY+=$(FORCED_DEPENDENCY_LOCAL)

$(FORCED_DEPENDENCY) : $(component_configuration) #No commands allowed

$(component_configuration) : $(comp_headers)

$(warning comp_headers=$(comp_headers))
$(warning component_configuration=$(component_configuration))




# -------------- multiple projects build support -------------
# 1. Subdir to descend to autoamtically is $(PROJ_PREFIX)$(PROJ)$(PROJ_SUFFIX)
# if it exists
MORE_SUBDIRS=$(filter $(PROJ_PREFIX)$(PROJ)$(PROJ_SUFFIX),$(shell $(DIRLIST_COMMAND)))
SUBDIR_EFFECTIVE:=$(subst \,/,$(SUBDIR) $(MORE_SUBDIRS))



# 4. If we are in a project-specific directory, Unimal output is project-specific
# It will automatically go to the right place (this project-specific directory).
# But the dependencies must go in the specific object directory (see below)

# 5. If we are in a project-specific directory, the object and dependency files
# must go in the specific object directory
_CURDIR_LIST=$(subst \, ,$(_CURDIR)) #Extract list of directories from path
in_specific=$(strip $(findstring $(PROJ_PREFIX)$(PROJ)$(PROJ_SUFFIX),$(_CURDIR_LIST)))#(conditionally compiled)...
ifeq ($(strip $(in_specific)),)
#project-independent source
UPARAMS:=
else
#project-specific source
INCDIR+=$(PROJECT_INCDIR)
UPARAMS:=-S$(UPROJSPEC)
endif
OBJDIR_EFFECTIVE=$(OBJDIR)\$(PROJ_PREFIX)$(PROJ)$(PROJ_SUFFIX)

# 2. Get the include subdirectories for descend subdirectories, removing redundancies but preserving order
#See http://stackoverflow.com/questions/16144115/makefile-remove-duplicate-words-without-sorting
#I added a wrapper to strip away leading newlines
define uniq1
$(eval seen :=)
$(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
${seen}
endef
uniq = $(strip $(call uniq1, $1))

export INCDIR_downstream := $(INCDIR_downstream) $(CURDIR) $(addprefix $(CURDIR)/,$(strip $(ISUBDIR)))
export INCDIR:= $(call uniq, $(INCDIR) $(INCDIR_downstream))

# 3. Note: INCDIR contains fully qualified paths, probably with mixture of forward and back slashes.
# We may need to make them project-root-relative or current-directory-relative
INCDIR_SLASH=$(subst \,/,$(INCDIR))
INCDIR_BACKSLASH=$(subst /,\,$(INCDIR))
# 3a. Note: In project-relative paths, we leave leading (back)slash in and eliminate project directory itself
INCDIR_PROJREL_BACKSLASH=$(subst $(PROJDIR),,$(INCDIR_BACKSLASH))
INCDIR_PROJREL_SLASH=$(subst $(_PROJDIR),,$(INCDIR_SLASH))
# 3b. Specific patterns to use
INCDIR_INCLUDE_UNIMAL=$(addprefix -I,$(INCDIR_BACKSLASH))
INCDIR_INCLUDE_C=$(addprefix -I, $(INCDIR_BACKSLASH))
INCDIR_INCLUDE_IDE=$(subst \,\\,$(INCDIR_PROJREL_BACKSLASH))#Need to double backslashes for disambiguation and for sed


#Gnu make doesn't like colons in targets; use relative path
OBJDIR_RELATIVE=$(subst $(PROJDIR)\,$(PATH2PROJROOT),$(OBJDIR_EFFECTIVE))

#Just a handy place to put it in
.PHONY: $(SUBDIR_EFFECTIVE)
.force: ;

#Clear the source search paths (just in case)
#vpath %.c
#vpath %.s79
VPATH=

#Add in case an old conf.mak already defined
UFILES+=$(UFILES_C) $(UFILES_H)
UFILES:=$(sort $(UFILES))

UHEADERS=$(notdir $(UFILES_H))
USOURCE=$(notdir $(UFILES_C))
SOURCE+=$(USOURCE:%.u=%.c)

# -------------- unit test support -------------------
ifneq ($(UTSET),)
#Remove source files not in the set from the sources
#If the harness is in the current directory, add it to the build
SOURCE:=$(filter $(UTEST_C) $(UTEST_HARNESS),$(SOURCE))
ASOURCE:=$(filter $(UTEST_A),$(ASOURCE))
endif
# -------------- end unit test support -------------------


# --------- File's Tombstone Header parser -----------
DOLLAR:=$
EXTRACT_DUMMIES:=$(SOURCE:.c=.extract) $(ASOURCE:.s79=.extract)
EXTRACT_REVISION:=-e "s%%.*$$\(Revision\): \([0-9]\+\).*%%\1 \2%%p"
EXTRACT_ARCHNAME:=-e "s%%.*$$\(Archive\): \([0-9/\\A-Za-z_.]\+\).*%%\1 \2%%p"
EXTRACT_INFO : $(EXTRACT_DUMMIES) ;

%.extract : %.c
    echo $(LBANGLE)br$(RBANGLE) >> $(EXTRACT_FILE)
    $(MN_CAT) $< | $(MN_SED) -n $(EXTRACT_REVISION) $(EXTRACT_ARCHNAME) >> $(EXTRACT_FILE)

%.extract : %.s79
    echo $(LBANGLE)br$(RBANGLE) >> $(EXTRACT_FILE)
    $(MN_CAT) $< | $(MN_SED) -n $(EXTRACT_REVISION) $(EXTRACT_ARCHNAME) >> $(EXTRACT_FILE)


# --------- Useful macros ------------

#A shorthand for the target's basename in the build directory (for C, Unimal rules, otherwise very long)
REALNAME=$(OBJDIR_RELATIVE)/$(OBJPREFIX)$(notdir $(basename $<))

# End of source
