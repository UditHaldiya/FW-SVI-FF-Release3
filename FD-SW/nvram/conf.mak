#'nvram' directory conf.mak
UFILES_C=eepshim_getset.u
#SOURCE, if defined, is a space-separated list of the sources in this directory
#SOURCE:=vertran.c
APP_SRC:=nvram.c confchanged.c logfile.c vertran.c firstrun.c
SOURCE+=$(addprefix ..\..\FIRMWARE\nvram\, $(APP_SRC))
SOURCE+=nvffext.c nvfbafext.c  ..\target\appl\fdev\src\mn_factory_defaults.c

#SUBDIR, if defined,  is a space-separated list of subdirectories with sources
#ISUBDIR, if defined,  is a space-separated list of header subdirectories
ISUBDIR+=..\..\FIRMWARE\nvram
ISUBDIR+=..\target\appl\fdev\inc ..\target\appl\fbif\inc

#Compiler flags private to this directory are below
CFLAGS_LOCAL=
