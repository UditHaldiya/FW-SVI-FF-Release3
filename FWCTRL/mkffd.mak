#Builds FFAP.ffd in cmdbuild\SVIFF\project_FFAP from
#whatever is found in FIRMWARE and FD-SW folders

#output files (e.g. .mns, .map etc.) will be at FF_Auto_Builds\CXXXXX
out_dir := C:\FF_Auto_Builds\FromDevelBranch
buildname = SVIFF
uniqroot = C:\tfsbuildR\SVIFF\Devel
OFFroot = .
export DIR=$(buildname)
OFFmodroot = $(uniqroot)\Core\FIRMWARE

_CURDIR:=$(subst /,\,$(CURDIR))
PROJ=FFAP
export PROG=$(PROJ)

export DIR=SVIFF
export OFFDir=$(DIR)
CMDDIR_ROOT=$(_CURDIR)\cmdbuild
CMDDIR=$(CMDDIR_ROOT)\$(DIR)
export CMDDIR_PROJ=$(CMDDIR)\project_$(PROJ)
export MEMMAP_ROMSTART1=08080800
export MEMMAP_ROMEND1=080FFFFF
export BTARGET=$(CMDDIR_PROJ)\$(PROG).mns

#cp = cmd /C copy /Y
cp = cp.exe

#memmap0_arg := MEMMAP_ROMSTART=$(MEMMAP_ROMSTART0) MEMMAP_ROMEND=$(MEMMAP_ROMEND0)

MN_ECHO:=tools\echo.exe

mfile:=includes
include ffplug.mak

.PHONY : all
all :
    echo BTARGET=$(BTARGET) $(memmap0_arg)
    $(cp) ..\FD-SW\includes\memmap_FFP.h ..\FD-SW\includes\memmap_FFP.h.bak
    $(cp) includes\memmap_FFAP.h includes\memmap_FFAP.h.bak
    cmd /C del ..\FD-SW\includes\memmap_FFP.h
    cmd /C del includes\memmap_FFAP.h
    if not exist $(out_dir)\$(buildname) cmd /C mkdir $(out_dir)\$(buildname)
    $(MAKE)  BUILD proj=FFAP
    $(BUILD_PLUGIN) BTARGET=$(BTARGET)
    $(cp) ..\FD-SW\includes\memmap_FFP.h.bak ..\FD-SW\includes\memmap_FFP.h
    $(cp) includes\memmap_FFAP.h.bak includes\memmap_FFAP.h



