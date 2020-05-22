#services\conf.mak

APP_TASK_SOURCE:= mnassert.c bufferhandler.c activate_dummy.c syswd.c
SOURCE+=$(addprefix ..\..\FIRMWARE\services\, $(APP_TASK_SOURCE))
SOURCE+=asrtconf.c

ISUBDIR+=..\target\appl\fdev\inc ..\target\appl\fbif\inc
