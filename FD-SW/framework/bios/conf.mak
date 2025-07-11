#framework\bios\conf.mak

SOURCE+= \
    ../../../FIRMWARE/framework/bios/stm_flash.c \
    ../../../FIRMWARE/framework/bios/project_FFAP/fram.c \
    ../../../FIRMWARE/framework/bios/project_FFAP/i2c.c \
    ../../../FIRMWARE/framework/bios/stm_nvic.c

SOURCE+=../../../FIRMWARE/framework/bios/stm_timer.c stm_watchdogff.c

ISUBDIR+=../../../FIRMWARE/framework/bios
#ISUBDIR+=../../FIRMWARE/framework ../../FIRMWARE/framework/bios
