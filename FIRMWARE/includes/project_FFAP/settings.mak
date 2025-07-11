#Version control common configuration


#Version control root of the project
export VCS_PROJ_ROOT:="\mncb\dev\LCX2AP\firmware"

#Place for sharing xml commands definitions with tools
export VCS_SHARED_ROOT:="\Common Source\Dev\Current"


#Version control builder username
#Version control builder password

#Default compiler version
#ver?=6.50
ver?=8.32

#Lint configuration
LINTARG=codebase.lnt

MN_INSTRUM=ffprofiler

#Doxygen version and location
DOXVER?=1.8.5
DOXYGEN:="$(ProgramFiles)\doxygen_$(DOXVER)\bin\doxygen.exe"
#graphviz_dotpath:="$(ProgramFiles)\Graphviz2.32\bin"

#Supported HART versions
export hart_versions=5

#   Where the definitions are imported from
#Where the faults and UI texts are defined (currently, same file)
export TEXTDEF:=$(PROJDIR)\$(PROJ)mncb_FAULT_matrix.xls
export FAULTDEF:=$(PROJDIR)\$(PROJ)mncb_FAULT_matrix.xls

# Local UI languages setup
# Space-separated list which must be a subset of column names in the spreadsheet
# ... and of names defined in $(HELPERS)\uitext.pl (.xls extractor helper script)
# must match names of columns names in $(TEXTDEF) and may be a proper subset
LanguagePack ?= English French Spanish Portuguese Japanese Italian German
export LanguagePack


