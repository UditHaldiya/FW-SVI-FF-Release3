#target/appl/fbif/src

#We generate instrumentation files unconditionally...

instrumfb_fbif_dsc.c : fbif_dsc.c 
	$(MN_ECHO) #include "\"instrumfb.h"\" >$@
	$(MN_SED) -e "s/\&.*execute FB function.*/mnbprof_execute_fb,/g" $< >>$@

instrumfb_fbif_dsc_mini.c : fbif_dsc.c
	$(MN_ECHO) #include "\"instrumfb.h"\" >$@
	$(MN_ECHO) const instrumfb_mini_block_descr_t instrumfb_mini_block_descr[] = >>$@
	$(MN_ECHO) { >>$@
	$(MN_SED) -n -e "s/\([A-Z0-9_]*\),.*symbolic block identifier.*/[\1]=/p" -e "s/\([A-Za-z0-9_]\),.*execute FB function.*/\1,/p" $< >>$@
	$(MN_ECHO) }; >>$@

$(PROJDIR)\inc_$(PROJ)\mn_gleaned.h : fbif_dsc.c
	$(MN_ECHO) //Automatically generated from $< >$@
	$(MN_ECHO) #ifndef MN_GLEANED_H_ >>$@
	$(MN_ECHO) #define MN_GLEANED_H_ >>$@
	$(MN_SED) -n -e "s/[ \t]*\([0-9]*\),.*Number of blocks.*/#define MN_NBLOCKS \1/p" $< >>$@
	$(MN_ECHO) #endif //MN_GLEANED_H_ >>$@

REQIMPORT : instrumfb_fbif_dsc.c instrumfb_fbif_dsc_mini.c $(PROJDIR)\inc_$(PROJ)\mn_gleaned.h

# ... but use them only instrumentation is asked for

ifneq (,$(filter fbprofiler,$(MN_INSTRUM)))
fbif_dsc:=instrumfb_fbif_dsc.c instrumfb_fbif_dsc_mini.c
else
fbif_dsc:=fbif_dsc.c
endif
	
SOURCE:= aifb.c aofb.c arfb.c csfb.c difb.c dofb.c \
    $(fbif_dsc) instance.c isfb.c maifb.c osfb.c \
    pidfb.c ptb.c resb.c spec_ds.c

ISUBDIR:= ..\inc

LintDirArg := $(addprefix +libm$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(SOURCE)))
