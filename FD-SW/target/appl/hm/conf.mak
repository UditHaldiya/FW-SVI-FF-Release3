#target/appl/hm

SUBDIR := src

ISUBDIR := inc ..\..\STM32F10x_StdPeriph_Driver\inc

LintDirArg := $(addprefix +libdir$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(ISUBDIR)))
