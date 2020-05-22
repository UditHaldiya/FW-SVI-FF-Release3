ifeq (yin,yang)
    $Author: Arkkhasin $
endif

modexec:=$(lastword $(MAKEFILE_LIST))
#mycopy:=xcopy /R/K/Y
mycopy:=.\cp.exe -f -p
OFFVCS?="$(ProgramFiles)\Microsoft Visual Studio 10.0\Common7\IDE\tf.exe"

comma:=,
empty:=
space:= $(empty) $(empty)

# Version control interface to modules
VCS_MODULES_ROOT:=$$/Core/FIRMWARE
modules_path:=$(lastword $(shell $(OFFVCS) workfold $(VCS_MODULES_ROOT) $(LOGIN)))

export submodfile:=$(PROJDIR)/modules_$(PROJ)
export modreqfile:=$(PROJDIR)/reqmodules_$(PROJ)

#Backward compatibility
HCMD-ver5=$(HCMD)
allhartcmd=$(strip $(foreach hartver, $(hart_versions), $(HCMD-ver$(hartver))))

FILEMEMBERS=$(SRC) $(HDR) $(ASRC) $(USRC) $(UHDR) $(allhartcmd)
MEMBERS=$(FILEMEMBERS) $(SUB) $(MCPY) $(MKINC)

# ----------- Outer shell part -----------------
.PHONY : filelist.txt filecpy.butt modlist.txt modcpy.butt
.PHONY : MODULES modsetup modeprepare hcinit modverify all_of_module modclean modverify

MODULES :
	$(Hide)-mkdir modules
    $(Hide)$(mycopy) inc_$(PROJ)\modules_$(PROJ).mak modules\modules_$(PROJ).mak
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) module=modules\modules_$(PROJ).mak modread
ifeq ($(Hide),)
    @echo finished at level $(MAKELEVEL)
endif
    @echo Verifying modules
    $(Hide)$(MAKE) --no-print-directory -f $(PROJDIR)$(SLASH)$(HELPERS)$(SLASH)modverify.mak

ifneq ($(module),)
include $(firstword $(subst $(comma),$(space),$(module)))
export MOD_OVERRIDE
ifeq ($(Hide),)
$(info module=[$(module)] REQUIRE=[$(REQUIRE)])
$(info SUB=$(SUB))
$(info SRC=$(SRC))
$(info MCPY=$(MCPY))
$(info ++++++++++++++++++++ included $(firstword $(subst $(comma),$(space),$(module))) )
endif
endif

modstart :
    $(pause)
    $(Hide)echo get $(MODARG) $(LOGIN)\>modlist.txt
	$(Hide)$(MN_ECHO) @Rem Modules to copy > modcpy.butt

modmidst :
    $(pause)
    $(Hide)$(OFFVCS) @modlist.txt
    $(pause)
	$(Hide)cp.exe modcpy.butt modcpy.bat
	$(Hide)modcpy.bat
    @echo Retrieving files from modules
	$(Hide)echo get $(MODARG) $(LOGIN) $(SLASH)>filelist.txt
	$(Hide)echo @Rem Files to copy > filecpy.butt

modend :
	$(Hide)$(OFFVCS) @filelist.txt
    $(pawz)
    @echo Copying modules' files
	$(Hide)cp.exe filecpy.butt filecpy.bat
	$(Hide)filecpy.bat
    $(pause)

modread : modsetup
    @echo Registering modules
ifeq ($(Hide),)
    @echo module=$(module)
    @echo SUBMODULES=$(SUBMODULES) PREMODULES=$(PREMODULES)
endif
ifneq ($(strip $(PREMODULES)),)
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) modstart
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) module=modules\modules_$(PROJ).mak $(PREMODULES)
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) modmidst
    $(Hide)cmd /C for %m in ( $(filter %.mak, $(subst $(comma),$(space),$(PREMODULES))) ) do \
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) module=modules\%m all_of_module
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) modend
endif
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) modstart
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) module=modules\modules_$(PROJ).mak $(SUBMODULES)
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) modmidst
    $(Hide)cmd /C for %m in ( $(filter %.mak, $(subst $(comma),$(space),$(SUBMODULES))) ) do \
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) module=modules\%m all_of_module
    $(Hide)$(MAKE) --no-print-directory -f $(modexec) modend

# Set up environment and root module
modsetup : modprepare
	@echo modules_path=$(modules_path)
    $(pause)

modprepare : hcinit
    -$(Hide)del /S/Q modconf_$(PROJ).mak.candidate
    -$(Hide)$(MN_RM) $(submodfile) $(modreqfile)
    -$(Hide)$(MN_RM) -f modules/*,*
    $(pause)

hcinit :
    $(foreach hartver, $(hart_versions), if exist $(hcmdroot)$(hartver).candidate $(Hide)$(MN_RM) $(hcmdroot)$(hartver).candidate)

modclean : modprepare
    -$(Hide)del /S/Q -r modconf_$(PROJ).mak

#debug helper
modverify :
    $(Hide)$(MAKE) --no-print-directory -f $(PROJDIR)$(SLASH)$(HELPERS)$(SLASH)modverify.mak


# ^----------- End outer shell part -----------------

LOGIN:=

mchangeset?=T
mitem=$(subst ;T,;$(mchangeset), $(subst $(comma),;,$@))
fitem=$(subst ;T,;$(mchangeset), $(subst $(comma),;,$^))

ifeq ($(Hide),)
$(info allhartcmd=$(allhartcmd))
endif

all_of_module: $(module) $(SUBMODULES) $(MEMBERS) $(allhartcmd) HCMD filelist.txt filecpy.butt modget

.PHONY : $(MEMBERS) $(allhartcmd) HCMD

#The next rule's dependency is:
#   from $(FILEMEMBERS), filter out files in any directory and of any version, if basename is listed in $(MOD_OVERRIDE).
#   The sequence can be clarified as follows:
# Remove directories: A=$(notdir $(FILEMEMBERS))
# Pattern to match any version: B=$(addsuffix %, $(MOD_OVERRIDE))
# Files to remove from any directory: C=$(filter $(B), $(A)) [mod_test_removal]
# Make a directory pattern for file removal D=$(addprefix %, $(C))
# Remove the files in any directory: E=$(filter-out $(D), $(FILEMEMBERS))
mod_test_removal = $(filter $(addsuffix %, $(MOD_OVERRIDE)), $(notdir $1))

filelist.txt : $(filter-out $(addprefix %, $(filter $(addsuffix %, $(MOD_OVERRIDE)), $(notdir $(FILEMEMBERS)))), $(FILEMEMBERS))
ifeq ($(Hide),)
    @echo MOD_OVERRIDE=$(MOD_OVERRIDE)
    @echo effective files = $^
endif
    $(pause)
	$(Hide)echo $(addprefix $(VCS_MODULES_ROOT)/,$(fitem)) \>>$@

filecpy.butt : $(FILEMEMBERS)
	
#Maybe, we don't want it. Or we can add a marker as before
$(module) : inc_$(PROJ)\modules_$(PROJ).mak


modget : $(FILEMEMBERS)


#Create read marker in the last operation
define modgetMod
    $(Hide)echo $(VCS_MODULES_ROOT)/modules_store/$(notdir $(mitem)) \>>modlist.txt
	$(Hide)echo $(Hide)$(mycopy) $(modules_path)\modules_store\$(firstword $(subst $(comma),$(space),$(notdir $@))) modules\$(firstword $(subst $(comma),$(space),$(notdir $@))) >>modcpy.butt
    @echo $@
endef

modmember=$(subst /,\,$(firstword $(subst $(comma),$(space),$@)))

define modget
	$(if $(call mod_test_removal, $(modmember)),, $(Hide)echo $(Hide)$(mycopy) $(modules_path)\$(modmember) $(modmember) >> filecpy.butt)
    $(pause)
endef

modconf=$(dir $@)modconf_$(PROJ).mak.candidate
modcpy=$(subst ->,$(space),$@)
$(MCPY) : modconf=$(lastword $(modcpy)).candidate
$(MCPY) : SourceVar=$(firstword $(modcpy))

$(MKINC) : modconf=$(lastword $(modcpy)).candidate
$(MKINC) : SourceVar=include $(firstword $(modcpy))

$(SRC): SourceVar=SOURCE
$(ASRC): SourceVar=ASOURCE
$(USRC): SourceVar=UFILES_C
$(UHDR): SourceVar=UFILES_H
$(SUB): SourceVar=SUBDIR

ifeq ($(Hide),)
$(info SourceVar=[$(SourceVar)])
endif

define write_modconf
    $(Hide)$(MN_ECHO) $(SourceVar)+=$(firstword $(subst $(comma),$(space),$(notdir $@))) >> $(modconf)
endef

define write_var
    $(Hide)$(MN_ECHO) $(subst `escquote`,\\\",$(subst `semicolon`,;,$(subst `colon`,:,$(subst `space`, ,$(SourceVar))))) >> $(modconf)
endef

$(PREMODULES) $(SUBMODULES) : filelist.txt filecpy.butt $(module) force
    $(Hide)$(MN_ECHO) $(REQUIRE) >> $(modreqfile)
    $(paws)
    $(modgetMod)
    $(Hide)echo Read marker >"$@"
    $(Hide)$(MN_ECHO) $(addprefix modules\,$@) >> $(submodfile)
ifeq ($(Hide),)
	echo SUB=[$(SUB)]
endif

$(SRC) $(ASRC) $(USRC) $(UHDR) : $(SUBMODULES)
    @echo Registering $@ (module=$(module))
    $(pause)
    $(modget)
    $(write_modconf)

$(HDR) : $(SUBMODULES)
    $(modget)

#directory $(SUB) may exist hence force
$(SUB) : $(SUBMODULES) force
    $(write_modconf)
    $(Hide)if not exist $@ $(Hide)cmd.exe /E /C mkdir $(subst /,\,$@)
	$(pawz)

$(MCPY) $(MKINC) : $(SUBMODULES)
ifeq ($(Hide),)
    @echo SourceVar=[$(SourceVar)]
    @echo modconf=[$(modconf)]
endif
    $(write_var)
    $(pause)

#XML-defined HART 5,6 commands in the modules

HCMD : $(allhartcmd) $(SUBMODULES)
ifneq ($(allhartcmd),)
    $(Hide)($(MN_ECHO) Writing $(allhartcmd) from the module) \
    $(foreach hartver, $(subst X,6,$(hart_versions)), && ($(MN_ECHO) $(filter %.xml, $(subst $(comma), ,$(HCMD-ver$(hartver)))) >> $(hcmdroot)$(hartver).candidate ))
    $(pause)
endif

$(allhartcmd) : $(SUBMODULES)
    $(Hide)$(modget)

# ---------------------------------------------------
force : ;
