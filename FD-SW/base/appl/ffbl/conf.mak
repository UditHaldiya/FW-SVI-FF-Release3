#base/appl

SUBDIR := src
ISUBDIR:= inc ..\..\..\target\appl\ffbl\inc ..\..\..\target\appl\fbif\inc
$(info LPAREN=$(LPAREN) RPAREN=$(RPAREN))
LintDirArg = +libdir$(LPAREN)$(_CURDIR)\inc$(RPAREN)
