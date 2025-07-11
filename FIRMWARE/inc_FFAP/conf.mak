#inc_FFAP conf.mak

#an include for project-specific feature-independent headers:
ISUBDIR = ../includes/project_$(PROJ)

FORCED_DEPENDENCY_LOCAL+=dimensions.inc
target:=dimensions
include ..\buildhelpers\h2inc.mak

ifeq ($(FEATURE_LOCAL_UI),LCD)
ISUBDIR+=../interface/ui ../interface/ui/glue ../interface/ui/project_$(PROJ)
UFILES_H+=../includes/uistartnodes.u
endif

ifeq ($(FEATURE_LOGFILES),USED)
UFILES_H+=../includes/logfileids.u
endif

UFILES_H+=ffids.u

#This is needed by FFP build
FORCED_DEPENDENCY_LOCAL += ffids.mak

ffids.mak : ffids.u ffids.inc
    $(UNIMAL) -Nmak=1 -I. $(INCDIR_INCLUDE_UNIMAL) ffids.u
	$(cmpcpy) $(@:.mak=.tmp) $@

component_configuration = HART_config FFIPC_config
