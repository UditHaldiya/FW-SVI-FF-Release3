#'nvram/project_FFAP' directory conf.mak

UFILES_C:=

ifeq ($(FEATURE_LOGFILES),USED)
UFILES_C+=../logfdata.u
SOURCE+=../facdefaults.c ../clonenvram.c nvutils.c
endif

#Embedded NVMEM layout translation
SOURCE+=nvram_xtable.c \
 FFAP_verdump_8.c FFAP_verdump_9.c FFAP_xlate_8_9.c \
 FFAP_verdump_10.c FFAP_xlate_9_10.c \
 FFAP_verdump_11.c FFAP_xlate_10_11.c \
 FFAP_verdump_12.c FFAP_xlate_11_12.c

