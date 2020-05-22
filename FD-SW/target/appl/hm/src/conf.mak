#target/appl/hm/src

SOURCE := hm_if.c

UseSimple?=OK
ifeq ($(UseSimple),OK)
SOURCE+=hmtask_simple.c
else
SOURCE+=hm.c hm_task.c
endif

LintDirArg := $(addprefix +libm$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(SOURCE)))

#hm_simple.c must be clean
ifeq ($(UseSimple),OK)
SOURCE+=hm_simple.c
endif

SOURCE+= hm_dma.c instrum_hm.c
ISUBDIR += ..\..\..\..\..\FIRMWARE\framework\bios
