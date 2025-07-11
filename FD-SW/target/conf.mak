#target

SUBDIR := appl hw sys STM32F10x_StdPeriph_Driver

LintDirArg = +libdir[$(_CURDIR)\cfg] +libdir[$(_CURDIR)\inc] +libdir[$(_CURDIR)\inc\ff] +libdir[$(_CURDIR)\inc\segm]
LintDirArg += -libh[$(_CURDIR)\inc\eep_if.h] -libh[$(_CURDIR)\inc\i2c.h] -libh[$(_CURDIR)\inc\mnbasetypes.h]
