SOURCE+=vramptest.c datahog.c dhogtrigger.c

ifeq ($(FEATURE_LOGFILES),USED)
SOURCE+=diagrw.c
endif
ifeq ($(FEATURE_PARTIAL_STROKE_TEST),SUPPORTED)
SOURCE+=pst.c pstshell.c
endif
