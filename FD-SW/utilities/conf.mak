#utilities\conf.mak

APP_UTILS:=chsum.c bufutils.c crc.c datautils.c sha256.c hmac.c shaseed.c
SOURCE+=$(addprefix ..\..\FIRMWARE\utilities\,$(APP_UTILS))
