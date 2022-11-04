ifeq (0,1)
This is a generic makefile to generate module switches; module being
any logical component.
It takes as command-line parameter:
mod=module codename

Usage for module xyz:
1. It creates xyz_config.h in the directory where
    1.1. xyz_config.mak exists, and
    1.2. conf.mak (or modconf_<MODULE>.mak) has the following passage:
component_configuration = xyz_config
NOTE: xyz must be a single word without _.

2. The syntax of xyz_config.mak is as follows:
    2.1. Module options are defined as a comma-separated list, e.g.
        xyz_OPTIONS_A = AA, BB, CC, DD
        xyz_OPTIONS_B = UU, VV, WW
    2.2. Selection from each choice are made
        xyz_SELECTION_A = BB
        xyz_SELECTION_B = WW

3. For each option set, number of unique constants will be created semi-randomly, e.g.
    #define     xyz_OPTIONS_A_OPTION_AA (2018+7)
    #define     xyz_OPTIONS_A_OPTION_BB (2019+7)
    #define     xyz_OPTIONS_A_OPTION_CC (2032+1)
    #define     xyz_OPTIONS_A_OPTION_DD (2046+3)

    and for each selection, a definition, e.g.
    #define xyz_SELECTION_A (xyz_OPTIONS_A_OPTION_BB)
NOTE: Enums would be handier but they can't be in #if statements (by the C abstract machine translation phases)

endif

include $(src)
file_mod:=$(subst \,/,$(src:_config.mak=))
mod:=$(notdir $(file_mod))

opt:=$(sort $(filter $(mod)_OPTIONS_%, $(.VARIABLES)))
feat:=$(sort $(filter $(mod)_SELECTION_%, $(.VARIABLES)))
#MN_ECHO:=tools\echo.exe
#UNIMAL:=tools\Unimal.exe

$(info opt=$(opt))
$(info feat=$(feat))

.PHONY : all prime_it $(feat) $(opt)

all : $(file_mod)_config.h $(file_mod)_config.inc
    @echo opt = $(opt)
    @echo feat = $(feat)
    $(paws)

$(file_mod)_config.h : $(file_mod)_config.inc
    $(Hide)$(MN_ECHO) /*Module $(mod) configuration automatically generated from $(src)*/>$@
    $(Hide)$(MN_ECHO) #ifndef $(mod)_CONFIG_H_>>$@
    $(Hide)$(MN_ECHO) #define $(mod)_CONFIG_H_>>$@
    $(Hide)$(UNIMAL) -I. $(addprefix -I,$(INCDIR)) -Sdefinitions=$(mod)_config.inc $(helpers)\modconfig.u>>$@
    $(Hide)$(MN_ECHO) #endif /*$(mod)_CONFIG_H_*/>>$@
    $(Hide)$(MN_ECHO) /*End of file*/>>$@
    $(paws)


$(file_mod)_config.inc : $(feat) $(opt) $(src)
    $(MN_CP) $@.tmp $@

$(feat) : $(opt) $(src)
    $(Hide)$(MN_ECHO) "#MP select[$@, $($@) ]" >> $(file_mod)_config.inc.tmp
    $(paws)

$(opt) : prime_it $(src)
    $(Hide)$(MN_ECHO) "#MP optionset[$@, $($@)]" >> $(file_mod)_config.inc.tmp
    $(paws)

prime_it :  $(src)  $(helpers)\modconfig.u $(helpers)\modconfig.mak
    @echo Here! $(mod)_config.inc
    $(Hide)$(MN_ECHO) "#MP ;Configuration of component $(mod)" > $(file_mod)_config.inc.tmp
    $(Hide)echo #MP If Defined(optionset {MAC}) >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Else" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Macro optionset" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Endm" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Endif" >> $(file_mod)_config.inc.tmp
    $(Hide)echo #MP If Defined(select {MAC}) >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Else" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Macro select" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Setstr #1# {#2#}" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Endm" >> $(file_mod)_config.inc.tmp
    $(Hide)$(MN_ECHO) "#MP Endif" >> $(file_mod)_config.inc.tmp
    $(paws)
