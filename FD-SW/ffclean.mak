include ..\FIRMWARE\inc_FFAP\ffids.mak
TARGET_BINARY_DD:=target\appl\fbif\ddl\$(DEVICE_TYPE)
DDL_root := target\appl\fbif
DDLDIR:=target\appl\fbif\ddl

uscripts_ptb := $(DDL_root)\script\ptb_custom.gw $(DDL_root)\ddl\svi_custom.h $(DDL_root)\ddl\svi_customvar.h
uscripts:= $(uscripts_ptb) $(nvport) $(iochannels) $(DDL_root)\ddl\rb_customvar.h $(DDLDIR)\faultdef_ff.h $(DDLDIR)\faultdef_ff.inc

ffclean :
	-del includes\havenv.bat
	-del $(cff) GenVFD
	-del $(uscripts)
	-del $(TARGET_BINARY_DD)\$(DEVICE_REV)$(DD_REV).sy*
	-del $(TARGET_BINARY_DD)\$(DEVICE_REV)$(DD_REV).ff*
	-del target\appl\fbif\inc\*.h
	-del  target\appl\fbif\src\*.c
	-del  target\appl\fbif\script\channel*.h
	-del  target\appl\fbif\ddl\cff.inc target\appl\fbif\ddl\*custom*.h target\appl\fbif\ddl\svi_ids.h
	-del  target\appl\fbif\src\*.c
	-del  target\appl\fbif\ddl\0008\_tmptok*
	-del  target\appl\fbif\ddl\0008\*.cff*
