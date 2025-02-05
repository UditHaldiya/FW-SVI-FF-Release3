OFFVCS ?= "$(ProgramFiles)\Microsoft Visual Studio 10.0\Common7\IDE\tf.exe"
TFPT = "$(ProgramFiles)\Microsoft Team Foundation Server 2010 Power Tools\tfpt.exe"

export OFFlogin=/login:"$(OFFuser),$(OFFpass)"

#latest CS number extracted from 1st word of appserverc.txt
ifeq ($(strip $(appserverc)),)
override appserverc = $(firstword $(shell cmd /C sort /R appserverc.txt))
$(info appserverc="$(appserverc)")
endif
#recursively update current dir (Projects/FIRMWARE) with latest CS sourcecode
#synccmd = $(OFFVCS) get . /recursive /noprompt /overwrite
#modcmd = gnumake proj=FFAP MODULES

#This is project family's release path basename
export ReleaseDir=Release3

#output files (e.g. .mns, .map etc.) will be here
out_dir := $(BUILD_REPOSITORY)\SVIFF\FromReleasesBranch\From$(ReleaseDir)
buildname = C$(appserverc)

#Here is where the official build be actually performed; should come from environment vars
OFFLastBuild?=C:\LastBuild
uniqroot = $(OFFLastBuild)\SVIFF\FromReleasesBranch\From$(ReleaseDir)
OFFroot = $(uniqroot)\FIRMWARE
OFFmodroot = $(uniqroot)\Core\FIRMWARE

#For ffplug.mak - FF-specific

#select the FF tokenizer version
export FFTokVer=3.70

ifneq ($(FFTokVer),3.70)
export TokenizerDir:=..\FFTokenizer.3.82
else
export TokenizerDir:=..\FFTokenizer
endif


#all - displays CS number being built; performs latest CS get;
#if latest CS folder doesn't exist in $(out_dir), create it & perform OFFICIAL build
#output results into build.log in out directory ($(out_dir)\CXXXXX)
all : appserverc.txt
    @echo appserverc=$(appserverc)
    $(synccmd)
	$(modcmd)
    if not exist $(out_dir)\$(buildname) cmd /C mkdir $(out_dir)\$(buildname) && ($(MAKE) Hide= OFFDir=Rel proj=FFAP plugin=ffplug.mak OFFICIAL notask=1 buildname=$(buildname) OFFver=$(buildname) \
	ver=FS8.40_3_30356 Hide= \
	NO_MNS=1 OFFroot=$(OFFroot) OFFmodroot=$(OFFmodroot) MNS_OFFICIAL_DIR=$(out_dir)\$(buildname) \
	avplugin=avplugin.mak silent=1) 2>&1 |ptee $(out_dir)\$(buildname)\build.log

#> 

appserverc.txt : force
    $(OFFVCS) history . /noprompt /sort:descending /recursive /stopafter:1 | sed --text -e "$$!d" >$@
    $(OFFVCS) history ..\FD-SW /noprompt /sort:descending /recursive /stopafter:1 | sed --text -e "$$!d" >>$@
    $(OFFVCS) history $(TokenizerDir) /noprompt /sort:descending /recursive /stopafter:1 | sed --text -e "$$!d" >>$@
	type appserverc.txt

force : ;

