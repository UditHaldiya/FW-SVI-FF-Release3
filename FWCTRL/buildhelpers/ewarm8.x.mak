ifeq (yin,yang)
 *************** IAR EWARM 8.x setup ******************
    $Author: Arkkhasin $
endif

.DELETE_ON_ERROR : ;

include $(projfeatures)

projdir_raw=$PROJ_DIR$#IAR thingie
export projdir:=$(value projdir_raw)
# ---------------- Debugger -----------------

ifneq ($(filter $(FEATURE_CPU),STM32F10xxE pm2kSTM32F10xxE),)
postlink_tool_flags=
endif
ifeq ($(FEATURE_CPU),MSP432)
postlink_tool_flags=
endif
ifeq ($(FEATURE_CPU),LPC21x4)
postlink_tool_flags= --checksum __vector+0x14:4,sum32:2;__vector-__vector+0x1f
endif

$(info ver=$(ver))

# --------- Root directory (Masoneilan convention) --------
export TOOLDIR=$(ProgramFiles)\IAR Systems\Embedded Workbench $(ver)
postlink_tool:=ielftool
debug_bits:=debug550.ide
hextool:=ielftool.exe --ihex --verbose $(postlink_tool_flags)
armsim_dll:=armsim2.dll
entry:=__iar_program_start

export debug_bits
# -------------- undefined variables default to older versions ------------

$(info debug_bits=$(debug_bits))
$(info IAR_FLASHLOADER=$(IAR_FLASHLOADER))

# -------------- System header locations -------------
export SYSINCDIR:=$(TOOLDIR)$(SLASH)ARM$(SLASH)inc$(SLASH)c
# ------------------ Compiler --------------------
export CC="$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)iccarm.exe"

#   Compiler flags (not final yet; see below)
#       Pe193 in CDIAGNOSTICS means #if XXX==YYY and XXX undefined is an error
#       Pe236 in CDIAGNOSTICS means means controlling expression is 0 (as in do ; while(0) )
#       Pe1374 explicit conversion of a 64-bit value to 32-bit value
#       Pe1375 conversion from a pointer to same-sized integer
#       Pa091 bitwise operator (~) on a value promoted to int
#       Pa039 use of address of unaligned structure member
#       Pe925 type qualifiers on function types are ignored
#       Pa182 bitwise operation drops significant bits from a constant (bug in EWARM 8.30.1)

DIAG_SUPPRESS:=Pe236 Pe1374 Pe1375 Pa091 Pa039 Pe925
ifeq ($(ver),8.30)
DIAG_SUPPRESS+=Pa182
endif
export DIAG_SUPPRESS
export DIAG_ERROR=Pe193
# A make kludge to replace spaces with commas
empty:=
export space:= $(empty) $(empty)
export comma:=,

CDIAGNOSTICS=--warnings_are_errors --remarks --diag_error $(subst $(space),$(comma),$(DIAG_ERROR)) --diag_suppress $(subst $(space),$(comma),$(DIAG_SUPPRESS))
#   IAR "runtime model"
RUNTIME_MODEL=DLib_Config_Normal
#   For some debug environments with file system support [they need to redefine RUNTIME_MODEL:=$(RUNTIME_MODEL_DEBUG)]
# Trouble with full library and the linker command files (or the linker) in 5.x
RUNTIME_MODEL_DEBUG=DLib_Config_Normal
# NVMEMDUMP target **needs** host file support
RUNTIME_MODEL_FULL=DLib_Config_Full

#   secondary target - for IDE/CSpyBat debugging/executing
export SIMTARGET=$(CMDDIR_PROJ)$(SLASH)$(PROG).out

LIB_OPTION=--dlib_config "$(TOOLDIR)$(SLASH)ARM$(SLASH)INC$(SLASH)c$(SLASH)$(RUNTIME_MODEL).h"

#   DEBUG_FLAG defines debug info and options depending on where we build
#       Note that we keep debug information in the output even in a release build
ifeq ($(DIR),Rel)
DEBUG_FLAG=-DNDEBUG --debug
else
DEBUG_FLAG=--debug
endif

#   Common compiler flags
ifeq ($(FEATURE_CPU),MSP432)
CFLAGS_CPU:=-Oh --endian little --cpu Cortex-M4 --fpu None
CPU_DEF:=--cpu Cortex-M4
endif
ifneq ($(filter $(FEATURE_CPU),STM32F10xxE pm2kSTM32F10xxE),)
CFLAGS_CPU=-Oh --endian=little --cpu=Cortex-M3 --fpu=None --no_const_align
CPU_DEF:=--cpu=Cortex-M3 --drv_vector_table_base=0x$(MEMMAP_ROMSTART)
endif
ifeq ($(FEATURE_CPU),LPC21x4)
CFLAGS_CPU:=-Oh --cpu_mode arm --endian little --cpu ARM7TDMI-S --fpu None
CPU_DEF:=--cpu ARM7TDMI-S
endif

CFLAGS_CPU += $(CFLAGS_PROJ)

#***Should*** make no difference for static inline but it does at least in 6.30
INLINE_CONTROL=--use_c++_inline

$(info CFLAGS_CPU=$(CFLAGS_CPU))

CFLAGS_COMMON=-e $(CFLAGS_CPU) $(CDIAGNOSTICS) $(DEBUG_FLAG) \
    $(INLINE_CONTROL) $(LIB_OPTION)

#$(addprefix -I ", $(addsuffix ",$(SYSINCDIR))) \

CFLAGS_NORMALBUILD=

#   Canned C compilation command
#   It works its way to generate header dependencies via an intermediate file so that
#   if it fails at any point, the dependency file is not trash, and the next build can proceed.
define C_Command
    @echo . Compile $< [new = $(wordlist 1,4,$?)]
    $(Hide)$(CC) $(INCDIR_INCLUDE_C) -DMN__FILE__=$(notdir $(<:.c=)) $(CFLAGS) $(CFLAGS_LOCAL) $(subst BASENAME,$(REALNAME), -lC BASENAME.lst -o BASENAME.o --dependencies BASENAME.d_) $<
    $(Hide)echo $(subst BASENAME,$(REALNAME),BASENAME.o BASENAME.d:) \>$(REALNAME).d
    $(Hide)$(FIXDEP) $(REALNAME).d_>>$(REALNAME).d
    $(Hide)echo $< $(LOCAL_CONF) $(local_topdep)>>$(REALNAME).d
endef

# --------------- Assembler -----------------
export AS="$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)iasmarm.exe"
#   Assembler flags
ifeq ($(FEATURE_CPU),MSP432)
export AFLAGS=-s+ -M"<>" -w+ -r $(CPU_DEF) --fpu None
endif
ifneq ($(filter $(FEATURE_CPU),STM32F10xxE pm2kSTM32F10xxE),)
AFLAGS_CPU:=-DCORTEX -t8 --cpu Cortex-M3 --fpu None
endif
ifeq ($(FEATURE_CPU),LPC21x4)
AFLAGS_CPU:=--cpu ARM7TDMI-S --fpu None
endif
export AFLAGS=-s+ -M"<>" -w+ -r $(AFLAGS_CPU)
# Assembler command
define A_Command
    $(Hide)echo . Assemble $< [new = $(wordlist 1,4,$?)]
    $(Hide)$(AS) $< $(INCDIR_INCLUDE_C) $(AFLAGS) $(subst BASENAME,$(REALNAME), -o BASENAME.o)
endef

# -------------- Librarian ------------------
AR="$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)iarchive.exe"
# These will be needed for the $(SURROUND) script
SURROUND_PREFIX=
SURROUND_SUFFIX=
# Library building command
define LibCmd_
    @echo Stub for library build
endef

ifdef NOLINKREFRESH
libcmdlist=
else
libcmdlist=$(ONEPERLINE) $(LINKLIST) | $(REMOVE_EMPTY_LINES) > $(LIBCMDLIST)
endif
define LibCmd
    -$(MN_RM) $(PROJLIB)
    $(libcmdlist)
    $(AR) -f $(LIBCMDLIST) -o $(PROJLIB)
endef

# ---------------- supporting tools ----------------
MN_CRCGEN:=$(MNTOOLS)\elfix.exe

# ---------------- Linker ------------------
export LD="$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)ilinkarm.exe"
#entry point can be changed by a wrapping makefile or from the command line
entry?=__iar_program_start
#   Linker flags
#       Output format(s)
OUTFMT=
#       Libraries directories
export LIBDIR="$(TOOLDIR)$(SLASH)ARM$(SLASH)lib"
#       All linker flags combined
LDFLAGS=--map $(CMDDIR_PROJ)$(SLASH)$(PROG).map --log initialization,modules,sections,veneers --log_file $(CMDDIR_PROJ)$(SLASH)$(PROG).log --config $(PROJDIR)$(SLASH)mncblink.icf --entry $(entry) $(OUTFMT)

#The following example helperes for linker configuration file
#must be, as appropriate for the project, in a
#well visible place, e.g. top-level conf.mak
#rombank?=0
#LDFLAGS_PROJ += --config_def rombank=$(rombank)
#or
#LDFLAGS_PROJ += $(foreach m,ROMSTART ROMEND RAMSTART RAMEND,--config_def $m=0x$(MEMMAP_$m))

# Link command (we are not shy to include linker post-processing commands in it)
define LinkCmd
    $(LD) -f $(LINKFILES) $(LDFLAGS_PROJ) $(LDFLAGS) $(MAINLIB) -o $(basename $@).out.tmp
    $(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)$(postlink_tool) $(basename $@).out.tmp $(basename $@).out
    $(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)$(hextool) $(basename $@).out $(basename $@).hex
    $(MNS_CONVERT) -u timestamp -i $(basename $@).hex -p $(PROJ) -b $@
    $(MN_CRCGEN) $(basename $@).out
endef

# ================= Unit test and NVMEMDUMP support ========================
OBJECTFILES=-f $(LINKFILES)
IAR_ENTRY:=__iar_program_start
define LinkCmd_UTest
    $(LD) $(OBJECTFILES) -o $@.tmp $(LDFLAGS_PROJ) $(LSIMFLAGS1) $(LSIMFLAGS2) $(UTEST_LIB) $(MAINLIB)
    $(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)$(postlink_tool) $(basename $@).out.tmp $(basename $@).out
    -$(MN_CRCGEN) $(basename $@).out
endef
CFLAGS_Utest:=--diag_suppress Pe177,Pe181

# ----------------- Simulator (command line) -----------------
#   Simulator flags
export LSIMFLAGS1=--semihosting --diag_suppress Li006 $(LDFLAGS_PROJ) --config $(PROJDIR)\mncbtest.icf  --entry $(entry)
LSIMFLAGS2=--map $(basename $@).map --log initialization,modules,sections,veneers --log_file $(basename $@).linklog
export SIMLIB_OPTION=

# command-line execution in debugger
export DEBUGGER = "$(TOOLDIR)$(SLASH)common$(SLASH)bin$(SLASH)CSpyBat.exe"
export DEBUGOPTIONS = "$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)armproc.dll" "$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)$(armsim_dll)"  --code_coverage_file $(PROJDIR)\codecov_$(UTSET).log
export DEBUGOPTIONJ = "$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)armproc.dll" "$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)armjlink.dll"
export DEBUG_PLUGIN = --plugin "$(TOOLDIR)$(SLASH)ARM$(SLASH)bin$(SLASH)armbat.dll"
export DEBUGOPTIONS_BACKEND = --backend -B -d sim $(CPU_DEF) --endian little
export DEBUGOPTIONJ_BACKEND = --backend -B -d jlink --jlink_connection USB $(CPU_DEF) --endian little

# ------------ IDE production from make's conf.mak and project definitions -------------
define IDE_Cmd
    $(Hide) $(MN_RM) -f $(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\projhead.ide  >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-general.ide  | $(MN_SED) -e s/__OBJPATH__/$(IDEObjPath)/g -e s/__EXEPATH__/$(IDEExePath)/g -e s/__LISTPATH__/$(IDEListPath)/g  -e s/__CPU_ID_STRING__/$(CPU_ID_STRING)/g >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-iccarm-head.ide | $(MN_SED) -e s/__DIAG_SUPPRESS__/$(subst $(space),$(comma),$(DIAG_SUPPRESS))/g -e s/__DIAG_ERROR__/$(subst $(space),$(comma),$(DIAG_ERROR))/g >>$(EWPFILE)
    $(Hide)$(MAKE) -f $(idemak) GROUP_CONF IDEBITSDIR=$(IDEBITSDIR)
    $(Hide)type $(IDEBITSDIR)\group-setting-iccarm-tail.ide  >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-aarm.ide | $(MN_SED) -e s/__ASMINC__/inc_$(PROJ)/g >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-objcopy.ide  | $(MN_SED) -e s/__OUTPUT__/$(OutputBaseName)/g >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-custom.ide  >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-bicomp.ide  >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-buildaction.ide | $(MN_SED) -e s/__PREBUILD__/$(PreBuildAction)/g -e s/__POSTBUILD__/$(PostBuildAction)/g >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-ilink-head1.ide  | $(MN_SED) -e s/__OUTPUT__/$(OutputBaseName)/g -e s/__ENTRY_POINT__/$(entry)/g >>$(EWPFILE)
    $(Hide)$(MAKE) -f $(idemak) IDEBITSDIR=$(IDEBITSDIR) linkoptions LDFLAGS_PROJ=$(subst $(space),__SPACE_PLACEHOLDER__,$(LDFLAGS_PROJ))
    $(Hide)type $(IDEBITSDIR)\proj-settings-ilink-tail.ide >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-xar.ide  >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\proj-settings-bilink.ide  >>$(EWPFILE)
    $(Hide)type $(IDEBITSDIR)\conftail.ide  >>$(EWPFILE)
    $(Hide)$(MAKE) -f $(idemak) IDEBITSDIR=$(IDEBITSDIR)
    $(Hide)type $(IDEBITSDIR)\projtail.ide  >>$(EWPFILE)
    @echo debug_bits=$(debug_bits)
    $(Pause)
    $(Hide)type $(IDEBITSDIR)\$(debug_bits) | $(MN_SED) -e s/__DEBUGGER_DEVICE_DEFINITION__/$(IAR_DEBUGGER_DEVICE_DEFINITION)/g -e s/__IAR_FLASHLOADER__/$(IAR_FLASHLOADER)/g -e s/__MemFile__/$(MemFile)/g  -e s/__OverrideDefFlashBoard__/$(OverrideDefFlashBoard)/g   -e s/__CCJLinkMultiTarget__/$(CCJLinkMultiTarget)/g>$(EWDFILE)
endef
#AK:TODO: The directory is wrong but the debugger can somehow figure it out. keep an eye on it

export idemak:=$(helpers)/idefile.mak
export  EWPFILE:=$(PROJDIR)$(SLASH)$(PROJ).ewp
EWDFILE=$(PROJDIR)$(SLASH)$(PROJ).ewd
OutputBaseName=$(PROJ)
majorver:=$(basename $(ver))
#IDEBITSDIR?=idebits$(majorver)
IDEBITSDIR?=idebits5
#Double backslashes are needed for $(MN_SED)
IDEBUILD?=idebld\\$(PROJ)
IDEObjPath?=$(IDEBUILD)\\Obj
IDEExePath?=$(IDEBUILD)\\Exe
IDEListPath?=$(IDEBUILD)\\List
PreBuildAction=
PostBuildAction=$(subst \,\\,$(subst $(PROJDIR),$(value projdir),$(MN_CRCGEN)))\t$(value projdir)\\$(IDEExePath)\\$(PROJ).out

# ----------------- What gets saved in the snapshot ------------
snapshot_TOOLS=

# ----------------- PC-Lint compiler configuration
co_lnt:=co5.lnt

# ---------------- What is seen by build makefiles -------------
#   Compilation commands
CCmd:=$(value C_Command)
AsmCmd:=$(value A_Command)
export CCmd AsmCmd
#   File extensions (tool-dependent)
FileExt_LIB:=.a
FileExt_LIBCMD:=.xlib
export FileExt_OBJ:=.o
FileExt_EXE:=.out
FileExt_ASM:=.s79
FileExt_LINKCMD:=.icf


