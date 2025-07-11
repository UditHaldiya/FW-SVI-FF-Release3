#'hart' directory conf.mak
UFILES_C:=
#SOURCE, if defined, is a space-separated list of the sources in this directory
SOURCE:=

ifeq ($(PROJ),FFAP)

SOURCE+=stm_ispcomm.c

#A workaround for FRAM layout (no) translation from Release1
SOURCE+=hartvers_compat.c
endif

#SUBDIR, if defined,  is a space-separated list of subdirectories with sources
SUBDIR:=glue
#ISUBDIR, if defined,  is a space-separated list of header subdirectories
#Compiler flags private to this directory are below
CFLAGS_LOCAL=
