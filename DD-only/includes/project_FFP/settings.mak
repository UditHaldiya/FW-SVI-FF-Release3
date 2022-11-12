#Default compiler version
ver?=6.50

#Temporary, until compiler 6.x is deployed for FFP (embOS and Softing dependencies, also lint fixes)
majorver:=$(basename $(ver))
ifneq (,$(filter $(majorver), 8 EWARM_FS_8_22_3 EWARM_FS_8_40_3_23190 FS8))
override ver:=6.50
endif
export ver

#ver=8.32
#export IDEBITSDIR=..\FIRMWARE\idebits5

#Lint configuration
LINTARG=codebase.lnt

#MN_INSTRUM=noinstum
MN_INSTRUM=fbprofiler

#Doxygen version and location
DOXVER?=1.8.5
DOXYGEN:="$(ProgramFiles)\doxygen_$(DOXVER)\bin\doxygen.exe"
#graphviz_dotpath:="$(ProgramFiles)\Graphviz2.32\bin"

# Local UI languages setup - handy to have here
# Space-separated list which must be a subset of column names in the spreadsheet
# ... and of names defined in $(HELPERS)\uitext.pl (.xls extractor helper script)
#LanguagePack ?= English French Spanish Portuguese Japanese Italian German

# ======== FFP-specific but made by FFAP build ===============
include inc_FFP\ffids.mak
export FAULTDEF:=$(PROJDIR)\FFAPmncb_FAULT_matrix.xls
export igdiff=

