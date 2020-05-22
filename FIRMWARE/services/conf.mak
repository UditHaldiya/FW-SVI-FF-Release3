#'services' directory conf.mak
#Unimal
UFILES_C = charact_tables.u
#SOURCE, if defined, is a space-separated list of the sources in this directory
SOURCE:=charact.c bufferhandler.c devicemode.c calib.c power.c
SOURCE+=ramdatamap.c ramtable.c

###ifeq ($(FEATURE_LOOPSIGNAL_SENSOR),SUPPORTED)
SOURCE+=sysiolopwr.c
###else
###SOURCE+=sysiolopwr_stub.c
###endif

ifeq ($(FEATURE_BUMPLESS_XFER),ENABLED)
SOURCE+=bumpless.c
else
SOURCE+=nobumpless.c
endif

ifeq ($(FEATURE_AO), SUPPORTED)
SOURCE+= osubrange.c
endif

ifeq ($(FEATURE_ACTIVATION),ID_SN)
SOURCE+=activate_id_sn.c
endif
ifeq ($(FEATURE_ACTIVATION),NONE)
SOURCE+=activate_dummy.c
endif

SOURCE+=refvoltage.c asrtconf.c



#SUBDIR, if defined,  is a space-separated list of subdirectories with sources
SUBDIR=
#ISUBDIR, if defined,  is a space-separated list of header subdirectories
#Compiler flags private to this directory are below
CFLAGS_LOCAL=

