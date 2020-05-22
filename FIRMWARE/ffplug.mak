include $(projfeatures)

#Modeled after definitions in miscexec.mak
# := doesn't work below - late eval needed
SISTER_PROJ_LOC=..\FD-SW
SISTER_OFFroot=$(OFFroot)\$(SISTER_PROJ_LOC)
SISTER_PROJ=FFP
SISTER_BUILD_DIR=$(SISTER_OFFroot)\cmdbuild\$(OFFDir)\project_$(SISTER_PROJ)

SISTER_BBASE=$(SISTER_BUILD_DIR)\$(SISTER_PROJ)
SISTER_BTARGET0=$(SISTER_BBASE)_0.mns

FFP_FW_HEADER0=$(shell type $(subst /,\,$(SISTER_BTARGET0)))
FFP_FW_CRCID0=$(subst $(FW_CRC),,$(filter $(FW_CRC)%,$(FFP_FW_HEADER0)))
FFP_FW_VERID0=$(subst $(FW_VER),,$(filter $(FW_VER)%,$(FFP_FW_HEADER0)))
ifeq ($(FFP_FW_CRCID0)$(FFP_FW_VERID0),)
SEND: send_error=$(error Unable to parse FF MNS header)
endif

OFFver?=$(buildname)

FFP_MNS_OFFICIAL_BNAME=FFFP_$(OFFDir)_$(OFFver)_$(FFP_FW_VERID0)_$(FFP_FW_CRCID0)
FFP_MNS_OFFICIAL_BNAME0=$(FFP_MNS_OFFICIAL_BNAME)_0

#Same for the second image
SISTER_BTARGET1=$(SISTER_BBASE)_1.mns

FFP_FW_HEADER1=$(shell type $(subst /,\,$(SISTER_BTARGET1)))
FFP_FW_CRCID1=$(subst $(FW_CRC),,$(filter $(FW_CRC)%,$(FFP_FW_HEADER1)))
FFP_FW_VERID1=$(subst $(FW_VER),,$(filter $(FW_VER)%,$(FFP_FW_HEADER1)))
ifeq ($(FFP_FW_CRCID1)$(FFP_FW_VERID1),)
SEND: send_error=$(error Unable to parse FF MNS header)
endif

FFP_MNS_OFFICIAL_BNAME1=FFFP_$(OFFDir)_$(OFFver)_$(FFP_FW_VERID1)_$(FFP_FW_CRCID1)_1

#What to do after FFAP modules are sync'ed: Get FFP and tokenizer
define VC_PLUGIN
    -$(MN_RM) -f -r $(SISTER_OFFroot)
    @echo Now getting FFP
    $(OFFVCS) workfold /map "$$/$(TFSProject)/FD-SW" $(SISTER_OFFroot) /workspace:$(OFFworkspace) $(OFFlogin)
    $(OFFVCS) workfold /map "$$/$(TFSProject)/FD-SW/$(TokenizerDir)" $(SISTER_OFFroot)/$(TokenizerDir) /workspace:$(OFFworkspace) $(OFFlogin)
    $(PAUSE)
    echo %TIME% Sync FF >> $(PROJDIR)\buildtime.log
    $(OFFVCS) get $(SISTER_OFFroot);$(OFFver) /recursive /force $(OFFlogin)
    $(OFFVCS) get $(SISTER_OFFroot)/$(TokenizerDir);$(OFFver) /recursive /force $(OFFlogin)
endef

ifeq ($(NO_MNS),1)
mns_cp:=echo Skipping cp #
else
mns_cp:=cp.exe
endif

NO_FFD_PIECES?=1
ifeq ($(NO_FFD_PIECES),1)
ffdpieces_cp:=echo Skipping cp#
else
ffdpieces_cp:=cp.exe
endif

MNS_OFFICIAL_NAME_1=$(subst $(PROG),$(PROJ)_1,$(MNS_OFFICIAL_NAME))
#What to do after FFAP output is uploaded
define SEND_PLUGIN
    @echo Checking in APP bank 1 image
    $(mns_cp) -f -p $(BTARGET:$(PROG).mns=$(PROJ)_1.mns) $(MNS_OFFICIAL_DIR)\$(MNS_OFFICIAL_NAME_1)
    $(mns_cp) -f -p $(BTARGET:$(PROG).mns=$(PROJ)_1.map) $(MNS_OFFICIAL_DIR)\$(MNS_OFFICIAL_NAME_1:.mns=.map)
    @echo Also checking in FFP image
    $(PAUSE)
    $(mns_cp) -f -p $(SISTER_BTARGET0) $(MNS_OFFICIAL_DIR)\$(FFP_MNS_OFFICIAL_BNAME0).mns
    $(mns_cp) -f -p $(SISTER_BTARGET1) $(MNS_OFFICIAL_DIR)\$(FFP_MNS_OFFICIAL_BNAME1).mns
    cp.exe -f -p $(SISTER_BTARGET0:.mns=.map) $(MNS_OFFICIAL_DIR)\$(FFP_MNS_OFFICIAL_BNAME0).map
    cp.exe -f -p $(SISTER_BTARGET1:.mns=.map) $(MNS_OFFICIAL_DIR)\$(FFP_MNS_OFFICIAL_BNAME1).map
    cp.exe -f -p $(SISTER_OFFroot)\target\appl\fbif\script\paramdoc.html $(MNS_OFFICIAL_DIR)\paramdoc.html
    -cmd /C for %v in ($(hart_versions)) do cp.exe -f -p $(SISTER_BTARGET0:.mns=-ver%v.html) $(MNS_OFFICIAL_DIR)\$(FFP_MNS_OFFICIAL_BNAME)-ver%v.html
    -cmd /C for %v in ($(hart_versions)) do cp.exe -f -p $(SISTER_BTARGET0:.mns=-ver%v.xml) $(MNS_OFFICIAL_DIR)\$(FFP_MNS_OFFICIAL_BNAME)-ver%v.xml
    $(MAKE) -C $(SISTER_OFFroot) -f makefile SEND proj=$(SISTER_PROJ) MNS_OFFICIAL_DIR=$(MNS_OFFICIAL_DIR)
    @echo Also checking in .ffd files
    cp.exe -f -p $(BTARGET:.mns=.ffd) $(MNS_OFFICIAL_DIR)\ALLFF_$(OFFDir)_$(OFFver)_F$(FFP_FW_VERID0)_$(FFP_FW_CRCID0)_A$(FW_VERID)_$(FW_CRCID).ffd
    $(ffdpieces_cp) -f -p $(BTARGET:.mns=.tmp.ffd) $(MNS_OFFICIAL_DIR)\ALLFF_$(OFFDir)_$(OFFver)_F$(FFP_FW_VERID0)_$(FFP_FW_CRCID0)_A$(FW_VERID)_$(FW_CRCID).tmp.ffd
    $(ffdpieces_cp) -f -p $(BTARGET:.mns=1.ffd) $(MNS_OFFICIAL_DIR)\FFAP_$(OFFDir)_$(OFFver)_$(FW_VERID)_$(FW_CRCID).ffd
    $(ffdpieces_cp) -f -p $(BTARGET:.mns=0.ffd) $(MNS_OFFICIAL_DIR)\FFFP_$(OFFDir)_$(OFFver)_$(FFP_FW_VERID0)_$(FFP_FW_CRCID0).ffd
    cp.exe -f -p tools\partman.ffd $(MNS_OFFICIAL_DIR)\partman.ffd
    $(ffdpieces_cp) -f -p tools\partman0.ffd $(MNS_OFFICIAL_DIR)\partman0.ffd
    $(ffdpieces_cp) -f -p tools\partman1.ffd $(MNS_OFFICIAL_DIR)\partman1.ffd
    $(PAUSE)
endef

ifeq (0,1)
    @echo Now creating FFP snapshot
    $(PAUSE)
    $(MAKE) -C $(OFFroot) -f snapshot snapshot=snapshot_$(buildname)
    $(PAUSE)
endif

memmap1_arg := MEMMAP_ROMSTART=$(MEMMAP_ROMSTART1) MEMMAP_ROMEND=$(MEMMAP_ROMEND1)

#What to do after FFAP is built
#	$(MAKE) -C $(OFFroot) -f ffbuild.mak clean tok $(fflint) build_raw $(ffthreads) DIR=$(OFFDir)
define BUILD_PLUGIN
    @echo Now building FFP at ROM bank 0
    $(PAUSE)
	$(MAKE) -C $(SISTER_OFFroot) -f makefile proj=$(SISTER_PROJ) BUILD PROG=$(SISTER_PROJ)_0
    @echo Now building APP at ROM bank 1
    $(PAUSE)
	cp $(BTARGET:.mns=.xlib) $(BTARGET:$(PROG).mns=$(PROJ)_1.xlib)
	cp $(BTARGET:.mns=.icf) $(BTARGET:$(PROG).mns=$(PROJ)_1.icf)
	$(MAKE) -C $(OFFroot) proj=FFAP MEMMAP $(memmap1_arg) -B
	$(MAKE) -C $(OFFroot) proj=FFAP BUILD NOGEN=1 $(memmap1_arg) NOLINKREFRESH=1 LINT_OPT= PROG=$(PROJ)_1
    @echo Now building FFP at ROM bank 1
    $(PAUSE)
	$(MAKE) -C $(SISTER_OFFroot) proj=$(SISTER_PROJ) MEMMAP $(memmap1_arg) -B
	$(MAKE) -C $(SISTER_OFFroot) -f makefile proj=$(SISTER_PROJ) BUILD NOGEN=1 $(memmap1_arg) LINT_OPT= PROG=$(SISTER_PROJ)_1
	@echo Now restoring memmap for bank 0
	$(MAKE) -C $(OFFroot) proj=FFAP MEMMAP -B
	$(MAKE) -C $(SISTER_OFFroot) proj=$(SISTER_PROJ) MEMMAP -B
    @echo Now building ffd images
    $(PAUSE)
	echo $(OFFver)>newstamp
	hex2ffd.exe /C newstamp $(SISTER_BUILD_DIR)\$(SISTER_PROJ)_0.hex $(SISTER_BUILD_DIR)\$(SISTER_PROJ)_1.hex $(BTARGET:$(PROG).mns=$(PROJ).hex) $(BTARGET:$(PROG).mns=$(PROJ)_1.hex) $(BTARGET:.mns=.tmp.ffd)
	hex2ffd.exe /h $(BTARGET:.mns=.tmp.ffd) $(BTARGET:.mns=.ffd)
endef

#What else to clean
define CLEAN_PLUGIN
endef
