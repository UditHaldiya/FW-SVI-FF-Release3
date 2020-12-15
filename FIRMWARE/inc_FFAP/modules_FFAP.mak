ifeq (yin,yang)

This file contains a collection of modules the project uses.
It may be empty (for a project not using modules) but it must exist.

A module may be listed as foo_x-y.mak,z which references revision z
or as foo_x-y.mak which references the latest revision.
All traceable builds are required to specify explicit revisions
of all modules.

    Owner: AK
    modules_FFAP.mak
endif

#MUST go first
PREMODULES:=projconf_1-2.mak,72964

#HART
SUBMODULES+=hartslave_1-3.mak,77968
MOD_OVERRIDE+=hartutils.c

SUBMODULES+=hcframework_2-3.mak,75969

#Extensions to oswrap and rtos
MOD_OVERRIDE+=os_cfg.h taskids.h tasktable.c #Proxy task added
MOD_OVERRIDE+=oswrap.c oswrap.h #Wrappers for a standalone semaphore
MOD_OVERRIDE+=hart_faultrept.c #exclude irrelevant commands

#Local UI
SUBMODULES+=uicommonapi_2-0.mak,37113
SUBMODULES+=uiengine_4-0.mak,82880 uiif_2-0.mak,77266
#LCD driver
SUBMODULES+=lcd_2-0.mak,66988
#ASCII utility
SUBMODULES+=asciiutils_1-0.mak,55618

#makebasicprimer_1-0.mak,2

#Build environment
SUBMODULES+=lint_3-0.mak,72784 \
    buildutils_1-0.mak,76118 \
    ideutils_1-0.mak,70660 \
    makefiles_3-2.mak,83162

MOD_OVERRIDE+=nvram.c #Bug 64096
SUBMODULES+= MNEnvir_5-0.mak,72775 \
    process_3-1.mak,81955 \
    faultman_2-0.mak,77195 \
    mnassert_2-1.mak,66864 \
    bufutils_1-1.mak,70043 \
    nvram_6-0.mak,60203 \
    resource_1-0.mak,55618 \
    errcodes_1-0.mak,27138 \
    syswd_2-0.mak,66864

#General helpers
SUBMODULES+=numutils_1-1.mak,55618 \
    bitutils_1-0.mak,55618

#BIOS
SUBMODULES+= \
    pbypass_1-0.mak,27138

#HART Glue layer
SUBMODULES+= corefac_1-1.mak,79757 \
    hart_base_1-0.mak,27138 \
    faultsif_1-0.mak,27138 \
    smoothingif_0-0.mak,27138 \
    pbypassif_1-0.mak,55618 \
    hwswitchesif_1-0.mak,29467 \
    pressuresif_1-0.mak,77238

#Since DI is present
SUBMODULES+=diswif_1-0.mak,27138


#SUBMODULES+=hcframework_1-0.mak,35209
SUBMODULES+=faultsimport_1-0.mak,82880

#NVMEM
SUBMODULES+=nvmemdump_1-0.mak,48200

#RTOS
SUBMODULES+=uC_OS_II_2_74_1-0.mak,27226 \
    taskhelpers_1-1.mak,58007 \
	osport_1-0.mak,56559

#I/O Subsystem
SUBMODULES+=temprmncb_1-0.mak,55618 \
    tempr_1-0.mak,55618 \
    smoothing_1-0.mak,55618 \
    signaldef_1-1.mak,55650 \
    lcduiio_4-0.mak,77268

#Tempcomp engine
SUBMODULES+=tempcomp_2-0.mak,54722

#Floating point
SUBMODULES+=engunits_1-0.mak,72968

#Timer
SUBMODULES+=timer_1-0.mak,35141

#Always the latest profiler module
ifeq ($(MN_INSTRUM),profiler)
SUBMODULES+= instrum_profiling_2-0.mak,T
endif




