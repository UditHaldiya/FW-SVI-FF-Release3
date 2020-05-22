#framework\conf.mak

SOURCE+= ../../FIRMWARE/framework/cortextrapc.c \
    ../../FIRMWARE/framework/mncbdefs.c \
    ../../FIRMWARE/framework/verinfo.c

SOURCE+=hack.c

ASOURCE := ../../FIRMWARE/framework/cortextrap.s79 \
    ../../FIRMWARE/framework/endofimage.s79

ISUBDIR+=../../FIRMWARE/framework

SUBDIR+=osport bios


