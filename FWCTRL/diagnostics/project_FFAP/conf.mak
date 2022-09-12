#diagnostics\project_FFAP\conf.mak
include $(PROJECT_INCDIR)/projfeatures.mak
ifeq ($(FEATURE_PARTIAL_STROKE_TEST),SUPPORTED)
SOURCE += pstfreeze.c
endif
