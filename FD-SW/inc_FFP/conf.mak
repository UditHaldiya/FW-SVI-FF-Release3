# inc_FFP\conf.mak

include advtemplate.mak
#an include for project-specific feature-independent headers:
ISUBDIR = ../includes/project_$(PROJ)

component_configuration = TBALERTSTRENDS_config HISTOGRAM_config

FORCED_DEPENDENCY_LOCAL+=nvdimensions.inc
target:=nvdimensions
include ..\..\FIRMWARE\buildhelpers\h2inc.mak

FORCED_DEPENDENCY_LOCAL+=dimensions.inc
target:=dimensions
include ..\..\FIRMWARE\buildhelpers\h2inc.mak

UFILES_H+=ffhartdef5.u
UFILES_H+=ffhartdef5_enum.u

UFILES_H+=..\interface\hart\hmsndrcv5.u ptbcustomsubx.u

UFILES_H+=..\..\FIRMWARE\includes\logfileids.u
UFILES_H+=..\..\FIRMWARE\nvram\nvmemids.u
UFILES_H+=common_h_cff.u

