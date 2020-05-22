#top level conf.mak

#Explanation: when building for bank 1, we pass the argument on the command line, and
#it will take precedence.


ifeq ($(PROJ),FFAP)
#A workaround for FRAM layout (no) translation from Release1
linker_redirect=$(join $(patsubst %,%=mn,$(1)),$(1))

Redirected = hartdisptab
LDFLAGS_PROJ+= $(addprefix --redirect , $(call linker_redirect, $(Redirected)))
$(info $(LDFLAGS_PROJ))
endif

#This is common for all MNCB projects
LDFLAGS_PROJ += $(foreach m,ROMSTART ROMEND RAMSTART RAMEND,--config_def $m=0x$(MEMMAP_$m))
#Need it exported for e.g. NVMEMDUMP target
export LDFLAGS_PROJ
#SOURCE, if defined, is a space-separated list of the sources in this directory
SOURCE:=

#We don't care about system headers' compliance w.r.t. standard guards
LintDirArg += -estring(451, "$(TOOLDIR)\*") /*System headers standard guards */

#SUBDIR, if defined,  is a space-separated list of subdirectories with sources
SUBDIR:=includes inc_$(PROJ) sysio tasks UTILITIES interface nvram \
    services framework \
    diagnostics

#ISUBDIR, if defined,  is a space-separated list of header subdirectories
ISUBDIR:=includes inc_$(PROJ) HAL\bsp hal\bios\inc
# RED_FLAG: Is this supposed to be here? HAL\{port,bsp}

#Supported instrumentation
ifneq (,$(wildcard mn_instrum/$(MN_INSTRUM)/conf.mak))
SUBDIR+=mn_instrum
endif

ifneq ($(UTSET),)
SUBDIR+=inhouse
ISUBDIR+=mn_instrum\maestra
endif