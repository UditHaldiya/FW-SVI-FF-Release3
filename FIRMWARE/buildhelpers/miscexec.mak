ifeq (yin,yang)
    $Author: Arkkhasin $
    $History: miscexec.mak $
endif

-include $(scripts)
include $(settings)
include $(plugin)
include $(avplugin)
include $(signingplugin)

FILELIST:=$(PROJDIR)$(SLASH)filelist_$(PROJ).dox
doxinc:=$(PROJDIR)$(SLASH)doxinc_$(PROJ).dox
doxfiles:= doxfiles_$(PROJ).txt

$(FILELIST) : force
    $(MN_RM) -f $@
    $(MAKE) -f $(snapshotmak) sources SNAPSHOTFILE=$@

$(doxinc) : force
    $(HIDE)$(MN_RM) $@
    $(MAKE) -r -f $(lintmak) INCFILES LINTCLUDE=$@ INC_CMDSWITCH=


QUOTE=\"#
#""
$(doxfiles): $(FILELIST) $(doxinc)
    $(Hide)$(MN_ECHO) PREDEFINED = PROJPARAM_H_=\"project_$(PROJ).h\" >$@
    $(Hide)$(MN_ECHO) HTML_OUTPUT = html_$(PROJ)>>$@
    $(Hide)$(ONEPERLINE) $< | $(MN_SORT) | $(MN_UNIQ) -i | $(RELPATHS) | $(KILL2DOTS) > $(<:.dox=.tmp)
    $(Hide)echo STRIP_FROM_PATH = $(PROJDIR)>>$@
    $(Hide)echo PROJECT_NAME = $(PROJ)>>$@
    $(Hide)echo INCLUDE_PATH = $(SLASH)>>$@
    $(Hide)$(ONEPERLINE) $(doxinc) | $(MN_SORT) | $(MN_UNIQ) -i | $(RELPATHS) | $(KILL2DOTS) > $(doxinc).tmp
    $(Hide)$(ADDBACKSLASH) $(doxinc).tmp >>$@
    $(Hide)$(MN_ECHO) >>$@
    $(Hide)echo INPUT = $(SLASH)>>$@
    $(Hide)$(ADDBACKSLASH) $(basename $<).tmp >>$@
    $(Hide)$(MN_ECHO) >>$@

DOX: $(doxfiles) force
    $(Hide)$(MN_ECHO) @INCLUDE = Doxyfile.base > Doxyfile
    $(Hide)$(MN_ECHO) CHM_FILE = $(PROJ).chm >> Doxyfile
    $(Hide)$(MN_ECHO) @INCLUDE = $(doxfiles) >> Doxyfile
    $(Hide)$(MN_ECHO) EXCLUDE_PATTERNS = *.dep *.ewd *ewp *eww dox*.* >> Doxyfile
    $(Hide)$(MN_ECHO) DOT_PATH = \"$(ProgramFiles)\Graphviz2.32\bin\" >> Doxyfile
    $(Hide)$(MN_ECHO) WARN_LOGFILE = doxygen_$(PROJ).log >> Doxyfile
    $(DOXYGEN)

# ----------------- Files snapshot ----------------
export SNAPSHOTFILE:=$(PROJDIR)$(SLASH)snapshot.lst


$(SNAPSHOTFILE): force
    $(Hide)echo makefile > $@
    DIR /B *.xcl *.icf >>$@
    $(Hide)$(MN_CAT) $(addsuffix .xd_,$(addprefix inc_$(PROJ)\hartdef,$(hart_versions))) >>$@
    $(Hide)dir /B/S *.candidate >>$@
    $(Hide)$(MAKE) -f $(snapshotmak)

snapshot: snapshot.tmp

snapshot.tmp: $(SNAPSHOTFILE) force
    $(ONEPERLINE) $< | $(RELPATHS) | $(MN_SED) -e s.\/.\\.g | $(KILL2DOTS) | $(MN_SORT) | $(MN_UNIQ) -i  > $@
    $(Hide)echo buildhelpers\* >>$@
    $(Hide)echo idebits*\* >>$@
    $(Hide)echo tools\* >>$@
    $(Hide)echo $(PROJ)mncb_FAULT_matrix.xls >>$@
    $(MN_ZIP) a -i@$@ -i!$(PROJ).ew* snapshot_$(PROJ)

ifeq (0,1)
    $(Hide)echo includes\project_$(PROJ)\settings.mak>> $@
    $(Hide)echo includes\project_$(PROJ)\projfeatures.mak>> $@
    $(Hide)echo includes\allfeatures.mak >>$@
    $(Hide)echo includes\faultproperties.mak >>$@
endif

# ----------------- Official build ---------------------------

#Build type (by output directory) - do not override unless you know
#what you are doing
OFFDir:=Rel
#Where the build actually happen; can override from command line
buildname?=nevermind
OFFroot := C:\tfsbuild\$(buildname)\FIRMWARE
#Version control system root

#Version to build (see /version for tf get); can override from command line
#Default is T (latest)
OFFver ?=T

#  -- Do not change unless instructed by IT should come from environment --
#   Bogus builder user, 
OFFtemplateuser ?=GENPITFI01\502098661

#OFFuname:=lg098661sv
OFFuname?=svc-TFSBuildValves
#OFFuser :=Logon\$(OFFuname)
#OFFuser?=BHI-MASTER\$(OFFuname)
#   Password of the bogus user
#OFFpass:=Sha2118d
#OFFpass?=9Jc*MS8)9?s8g7G6X7j:E515G
#   Where modules are retrieved
OFFmodroot:= C:\rbuilder\Core\FIRMWARE
#   Template workspace
OFFworktemplate ?=rbuilder;$(OFFtemplateuser)
#   Local builder workspace
OFFworkspace :=rbuilder_$(OFFuname)
#   Version control system commands
OFFVCS?="$(ProgramFiles)\Microsoft Visual Studio 10.0\Common7\IDE\tf.exe"
OFFTester:=Hu, Helen
OFFWIT:="$(ProgramFiles)\Microsoft Team Foundation Server 2010 Power Tools\tfpt.exe" workitem
# -- End Do not change --

VCSmodroot :="$$/Core/FIRMWARE"
OFFlogin:=/login:"$(OFFuser),$(OFFpass)"
OFFWITFields:="Title=*SVI FF 3.1.0.x test build $(buildname) $(OFFver);Assigned To=$(OFFTester);Discipline=Testing Task;Estimated Time=5;Description=Ready for testing"

#Version control system root - we'll discover it
ifneq (, $(filter OFFICIAL SS SEND OFFREPARE test, $(MAKECMDGOALS)))
VCSroot=$(strip $(subst :,,$(subst $(_CURDIR),,\
$(shell $(OFFVCS) workfold . $(OFFlogin)| $(MN_SED) -e "$$!d")\
)))
TFSProject=$(subst ?, ,$(word 2,$(subst /, ,$(subst $(empty) $(empty),?,$(VCSroot)))))
endif

export VCSroot TFSProject

test test1:
	@echo VCSroot=$(VCSroot)
	@echo TFSProject=$(TFSProject)
	@echo OFFlogin=$(OFFlogin)

#Default OFFICIAL goals
OGOALS?=BUILD #DOX DOXZIP

SS:=SS

OFFICIAL : $(SS)
    echo %TIME% Do local build >> $(PROJDIR)\buildtime.log
    $(MAKE) -C $(OFFroot) -f $(OFFroot)\makefile $(OGOALS) proj=$(PROJ) DIR=$(OFFDir)
    echo %TIME% Check in build results >> $(PROJDIR)\buildtime.log
    $(BUILD_PLUGIN)
    $(MAKE) SEND proj=$(PROJ) DIR=$(OFFDir)
    echo %TIME% Finished >> $(PROJDIR)\buildtime.log

# -- Get the build sources --
export LOGIN=$(OFFlogin)
SS : force
# 1. Start clean
    echo %TIME% Start build > $(PROJDIR)\buildtime.log
    -$(MAKE) OFFREPARE
    -$(MN_RM) -f -r $(OFFroot)
    -$(MN_RM) -f -r $(MNS_OFFICIAL_DIR)
    $(CLEAN_PLUGIN)
# 2. Clone the builder's abstract workspace on local machine
    echo %TIME% Prepare workspace >> $(PROJDIR)\buildtime.log
    $(OFFVCS) workspace /new /noprompt /template:$(OFFworktemplate) $(OFFworkspace) $(OFFlogin)
# 3. Map the sandbox
    $(OFFVCS) workfold /map "$(VCSroot)" $(OFFroot) /workspace:$(OFFworkspace) $(OFFlogin)
    $(OFFVCS) workfold /map $(VCSmodroot) $(OFFmodroot) /workspace:$(OFFworkspace) $(OFFlogin)
# 4. Sync with the build sandbox
    echo %TIME% Sync >> $(PROJDIR)\buildtime.log
    $(OFFVCS) get $(OFFroot);$(OFFver) /recursive /force $(OFFlogin) || $(OFFVCS) get $(OFFroot);$(OFFver) /recursive $(OFFlogin)
# 5. Get modules
    echo %TIME% Get modules >> $(PROJDIR)\buildtime.log
    gnumake -C $(OFFroot) proj=$(PROJ) MODULES VCS_MODULES_ROOT=$(OFFmodroot) MODARG=
# 6. Execute a plugin if supplied
    $(VC_PLUGIN)
# 7. Delete temporary workspace
    echo %TIME% Remove workspace >> $(PROJDIR)\buildtime.log
    $(OFFVCS) workspace /delete /noprompt $(OFFworkspace);$(OFFuser) $(OFFlogin)

# -- In case temporary workspace lingers around --
OFFREPARE : force
# 6. Delete temporary workspace
    $(OFFVCS) workspace /delete /noprompt $(OFFworkspace);$(OFFuser) $(OFFlogin)



DOXZIP :
    $(MN_RM) doxydoc\dox_$(PROJ).zip
    $(MN_ZIP) a -i!doxydoc\html_$(PROJ)\* doxydoc\dox_$(PROJ).zip


# ----------------- TFS stuff ----------------------------
#By default, if build name is not specified, put it on top:
buildname?=misc
MNS_OFFICIAL_DIR=$(PROJDIR)\..\builds\$(buildname)

FW_CRC:=FirmwareCRC=
FW_VER:=FirmwareVer=

# Shorthands for clarity
#AK:TODO Commonize with buildexec
BTARGET=$(subst $(PROJDIR),$(OFFroot),$(CMDDIR_PROJ))$(SLASH)$(PROG).mns
#BTARGET=$(CMDDIR_PROJ)$(SLASH)$(PROG).mns

FW_HEADER=$(shell type $(BTARGET))
FW_CRCID=$(subst $(FW_CRC),,$(filter $(FW_CRC)%,$(FW_HEADER)))
FW_VERID=$(subst $(FW_VER),,$(filter $(FW_VER)%,$(FW_HEADER)))
$(info BTARGET=$(BTARGET))
ifeq ($(FW_CRCID)$(FW_VERID),)
SEND: send_error=$(error Unable to parse MNS header)
endif
MNS_OFFICIAL_NAME=$(PROG)_$(OFFDir)_$(OFFver)_$(FW_VERID)_$(FW_CRCID).mns
SS_POST_CMD_COMMENT:="From $(CMDDIR_PROJ) by $(USERNAME)"

WIT=$(word 3, $(shell type wit.log))
$(info WIT=$(WIT))

#It looks like there is a make bug which causes a premature evaluation of a variable
#$(shell ...). A workaround is to split use of it from creating a file to evaluate
#in two targets. So SEND is split in SEND and SEND_part.
SEND : SEND_part
ifeq ($(notask),)
	echo wit=$(WIT)
	$(OFFWIT) /uploadattachment $(WIT) /recursive /comment:"Build results" ..\builds\$(buildname)\* $(OFFlogin)
endif

NO_PIECES?=1

SEND_part :force
    -cmd /E /C mkdir $(MNS_OFFICIAL_DIR)
ifneq ($(NO_MNS),1)
    cp.exe -f -p $(BTARGET) $(MNS_OFFICIAL_DIR)\$(MNS_OFFICIAL_NAME)
endif
    cp.exe -f -p $(BTARGET:.mns=.map) $(MNS_OFFICIAL_DIR)\$(MNS_OFFICIAL_NAME:.mns=.map)
ifeq ($(NO_PIECES),0)
    cmd /C for %v in ($(hart_versions)) do cp.exe -f -p $(BTARGET:.mns=-ver%v.html) $(MNS_OFFICIAL_DIR)\$(MNS_OFFICIAL_NAME:.mns=-ver%v.html)
    cmd /C for %v in ($(hart_versions)) do cp.exe -f -p $(BTARGET:.mns=-ver%v.xml) $(MNS_OFFICIAL_DIR)\$(MNS_OFFICIAL_NAME:.mns=-ver%v.xml)
endif
    $(SEND_PLUGIN)
	$(SIGNING_PLUGIN)
	$(AV_PLUGIN)

ifeq ($(notask),)
ifneq ($(checkin),silent)
    @echo Any key to check in or Control-C to abort
    @pause
endif
	$(OFFWIT) /new "$(TFSProject)\Task" /fields:$(OFFWITFields) $(OFFlogin) > wit.log
endif


SYNC : force
    $(OFFVCS) whoami -Y$(OFFuser),$(OFFpass)
    $(OFFVCS) cp $(VCS_PROJ_ROOT) -Y$(OFFuser),$(OFFpass)
    $(OFFVCS) get * -R -I- -GTC -GL$(OFFroot) -Y$(OFFuser),$(OFFpass) $(VSSARG)

# --------------------------------------------------
force : ;
