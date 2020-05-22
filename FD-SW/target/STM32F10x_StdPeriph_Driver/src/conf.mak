#target/STM32F10x_StdPeriph_Driver/src

SOURCE := misc.c stm32f10x_exti.c \
    stm32f10x_fsmc.c stm32f10x_gpio.c stm32f10x_rcc.c \
    stm32f10x_tim.c stm32f10x_usart.c

ISUBDIR += ..\..\..\..\FIRMWARE\framework\bios

#Unused stm32f10x_flash.c stm32f10x_i2c.c stm32f10x_crc.c

LintDirArg := $(addprefix +libm$(LPAREN)$(_CURDIR)\,$(addsuffix $(RPAREN),$(SOURCE)))
