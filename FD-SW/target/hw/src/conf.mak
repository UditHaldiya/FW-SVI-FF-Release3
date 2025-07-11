#target/hw/src

SOURCE := hw_init.c hw_periph_cfg.c hw_intr.c \
        stubs_app.c hw_io.c hw_os.c hw_tim.c

LintDirArg := $(addprefix +libm$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(SOURCE)))


ISUBDIR+=../../../../FIRMWARE/framework


#Kludge for Softing bugs - won't compile
CFLAGS_LOCAL:=-DOS_UART_USED=0 -DOS_USE_JLINKMEM=0