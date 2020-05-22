#'nvram/project_FFP' directory conf.mak

UFILES_C:=..\logfdata.u

APP_U_C:=nvramtable.u

UFILES_C+=$(addprefix ..\..\..\FIRMWARE\nvram\, $(APP_U_C))

#Embedded NVMEM layout translation + map tables
SOURCE+=nvram_xtable.c nvutils.c ..\logfproc.c eepshim.c ff2nvram.c ..\..\..\FIRMWARE\nvram\clonenvram.c ..\..\..\FIRMWARE\nvram\facdefaults.c

SOURCE+=FFP_verdump_1.c
SOURCE+=FFP_verdump_2.c FFP_xlate_1_2.c
SOURCE+=FFP_verdump_3.c FFP_xlate_2_3.c

$(info $(ISUBDIR))

#For lint
ISUBDIR+=..\..\includes\project_$(PROJ)
