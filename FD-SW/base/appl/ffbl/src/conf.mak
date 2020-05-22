#base/appl/ffbl/src

SOURCE:= ffbl_dom.c ffbl_bas.c ffbl_res.c ffbl_fd.c \
    ffbl_ai.c ffbl_pai.c ffbl_mai.c ffbl_ao.c ffbl_mo.c \
    ffbl_pao.c ffbl_di.c ffbl_do.c ffbl_ar.c ffbl_is.c \
    ffbl_os.c ffbl_pid.c ffbl_krn.c

LintDirArg := $(addprefix +libm$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(SOURCE)))
