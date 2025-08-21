ifeq (yin,yang)
 Build execution driver

HCIMPORT support removed (should be part of REQIMPORT);
Explicit dependenices BUILD-UNIMAL-REQIMPORT-FEATURES-MEMMAP removed to avoid
redundant builds - must be set up in main makefile
endif

include $(scripts)
include $(LOCAL_CONF)
-include modconf_$(PROJ).mak

# The order is essential to enable the project to override tools version
#include $(projfeatures)
#include $(toolconf)

# C and Unimal project parameter headers and their command-line visibility
export hprojparam:=$(projparam).h
export uprojparam:=$(projparam).inc
# (Observe the patently bizarre quotes escape required by CMD.EXE!)
PROJSPEC:=PROJPARAM_H_="\"$(hprojparam)\""
export UPROJSPEC:=PROJPARAM_INC_=$(uprojparam)
_build: CFLAGS:=$(CFLAGS_COMMON) $(CFLAGS_NORMALBUILD) -D$(PROJSPEC)

export CFLAGS

# ---------- Targets configuration ---------------
#   main output - downloadable code
BTARGET=$(CMDDIR_PROJ)$(SLASH)$(PROG).mns
#   project library
PROJLIB=$(basename $(BTARGET))$(FileExt_LIB)
#   Librarian command file
LIBCMDLIST = $(basename $(BTARGET))$(FileExt_LIBCMD)
#   list of sources to link (discovered during dirwalk, hence export'ed)
export LINKLIST:=$(basename $(BTARGET)).lnk
#   list of files to link (updated on change)
LINKFILES:=$(basename $(BTARGET))$(FileExt_LINKCMD)
#   just an indicator of linker job required
export RELINK=$(basename $(BTARGET)).relink


ifdef NOGEN
GEN=
else
GEN=UNIMAL
endif

ifdef NOLINKREFRESH
BUILD_INIT=
else
BUILD_INIT=BUILD_INIT
endif

BUILD : $(BUILD_INIT) $(GEN) _build $(BTARGET)

define debugcmd
    @echo scripts=$(scripts)
    @echo cmpcpy=$(cmpcpy)
    @echo target=$(BTARGET)
endef

BUILD_INIT : #Remove the file list and create timestamp
    $(Hide)$(MN_RM) -f $(LINKLIST)
    $(Hide)$(MNS_CONVERT) -d timestamp 2>&1


$(BTARGET): $(RELINK) $(LINKFILES) $(MAKEFILE_LIST)
    $(Hide)echo . Linking : $@
#Build the project library at the same time; we need it to stub unit tests automatically
    $(Hide)$(LibCmd)
    echo MAINLIB=$(MAINLIB)
    $(pause)
    $(Hide)$(LinkCmd)
#To make sure it was built successfully, print the MNS header; let sed filter out the binary part (tee is not good at it)
    $(Hide)$(TEXTHEADER) $(basename $@).mns

_build:
    $(MAKE) -r -f $(buildmak) build

# RELINK is just an indicator of linker job required. It is normally written
# to by the last file compiled. In case nothing is compiled and the file
# doesn't exist we'll fake it (since we do need a relink in this case)
$(RELINK) :
    $(Hide)echo Force relink > $@

# Update the list of object files if it is different
ifdef NOLINKREFRESH
else
$(LINKFILES) : $(LINKLIST)
    $(Hide)echo . cmpcpy=$(cmpcpy)
    $(Hide)echo . Updating $@
    $(Hide)-$(cmpcpy) $< $@ >nul
    $(Hide)fc  $< $@ >nul
endif

# ----------------- preprocessor ---------------------------
UNIMAL:
    $(Hide)$(MAKE) -r -f $(unimalmak)

# ----------------- project-driving features ---------------


allfeatures:=$(PROJECT_DEFINITIONS_DIR)\allfeatures.inc
projfeatures:=$(PROJECT_INCDIR)\projfeatures.inc


FEATURES: $(CMDDIR_PROJ)  $(allfeatures) $(projfeatures) $(PROJECT_DEFINITIONS_DIR)\$(hprojparam) MEMMAP

MEMMAP: $(PROJECT_DEFINITIONS_DIR)\$(uprojparam) /includes/memmap.h$(MEMMAP_H_PARAM)

# Creates project_XYZ.h (with symbolic names of C header files)
$(PROJECT_DEFINITIONS_DIR)/$(hprojparam) : $(projfeatures:.inc=.mak) $(featmak) $(MAKEFILE_LIST)
    $(Hide)$(MN_ECHO) Making $@ out of $<
    $(MN_ECHO) #ifndef PROJPARAM_G_ >$@
    $(MN_ECHO) #define PROJPARAM_G_ >>$@
    $(MN_ECHO) #ifdef PROJPARAM_H_ >>$@
    $(Hide)$(MAKE) -r -f $(featmak) src=$< dst=$@ hparam
    $(MN_ECHO) #endif //PROJPARAM_H_ >>$@
    $(MN_ECHO) #endif //PROJPARAM_G_ >>$@

# Creates project_XYZ.inc (with symbolic names of Unimal include files)
$(PROJECT_DEFINITIONS_DIR)/$(uprojparam) : $(projfeatures:.inc=.mak) $(featmak) $(MAKEFILE_LIST)
    $(MN_ECHO) Making $@ out of $<
    $(MN_ECHO) #MP Ifdef PROJPARAM_INC_ >$@
    $(Hide)$(MAKE) -r -f $(featmak) src=$< dst=$@ uparam
    $(MN_ECHO) #MP Setstr PROJ_PREFIX \"$(PROJ)\" >>$@
    $(MN_ECHO) #MP Endif ;PROJPARAM_INC_ >>$@

# Creates projfeatures.inc (with Unimal switches which Unimal propagates to C)
$(projfeatures) : $(projfeatures:.inc=.mak) $(featmak)
    $(Hide)$(MN_RM) -f $@
    $(Hide)$(MAKE) -r -f $(featmak) src=$< dst=$@ projf

# Creates allfeatures.inc (with Unimal switches which Unimal propagates to C)
$(allfeatures) : $(allfeatures:.inc=.mak) $(featmak)
    $(Hide)$(MN_RM) -f $@
    $(Hide)$(MAKE) -r -f $(featmak) src=$< dst=$@ allf


/includes/memmap.h$(MEMMAP_H_PARAM) : $(MAKEFILE_LIST)
    $(MN_ECHO) #ifndef MEMMAP_G_ >>$@
    $(MN_ECHO) #define MEMMAP_G_ >>$@
    $(MN_ECHO) #ifdef MEMMAP_H_ >>$@
    $(MN_ECHO) #define ROMSTART ( $(addsuffix U,$(addprefix 0x,$(MEMMAP_ROMSTART))) ) >>$@
    $(MN_ECHO) #define ROMEND  ( $(addsuffix U,$(addprefix 0x,$(MEMMAP_ROMEND))) ) >>$@
    $(MN_ECHO) #define RAMSTART  ( $(addsuffix U,$(addprefix 0x,$(MEMMAP_RAMSTART))) ) >>$@
    $(MN_ECHO) #define RAMEND  ( $(addsuffix U,$(addprefix 0x,$(MEMMAP_RAMEND))) ) >>$@
    $(MN_ECHO) #define NVMEMSTART ( $(addsuffix U,$(addprefix 0x,$(MEMMAP_NVMEMSTART))) ) >>$@
    $(MN_ECHO) #define NVMEMEND ( $(addsuffix U,$(addprefix 0x,$(MEMMAP_NVMEMEND))) ) >>$@
    $(MN_ECHO) #endif //MEMMAP_H_ >>$@
    $(MN_ECHO) #endif //MEMMAP_G_ >>$@


#--------------------- IDE --------------------------
IDE :
    $(IDE_Cmd)

#--------------------- Compiler pre-defines discovery --------------------------

CCVER :
    echo /* Compiler pre-defines discovery */>iccarm.predef.c
    $(CC) $(CFLAGS_CPU) --predef_macros iccarm.predef.$(PROJ).$(ver) iccarm.predef.c

define TODO
#AK:TODO: Why isn't the rule working (not detected)
# Rule for project features and project features
%.inc : %.mak $(featuresgenmak) $(featmak)
    echo ++++
endef


