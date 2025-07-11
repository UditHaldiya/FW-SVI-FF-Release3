#target/sys/osif.emb/src

SOURCE := osif_mn.c osif_tsk.c osif_tim.c osif_cfg.c xmtx.c

ISUBDIR += ..\..\..\appl\fdev\inc ..\..\..\appl\fbif\inc
ISUBDIR += ..\..\..\..\..\FIRMWARE\framework\bios

LintDirArg := $(addprefix +libm$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(SOURCE)))
