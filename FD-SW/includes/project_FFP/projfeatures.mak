# FF FFP project features

# =========== Microcontroller definitions ==============
include $(helpers)/mcu_pm2kSTM32F10xxG.mak

#=========== Discrete features (switches) ==============
# --------------- large-scale stuff -------------
FEATURE_CPU = pm2kSTM32F10xxE
# --------------- Log file system ---------------------------
#Needed for NVMEMDUMP 
FEATURE_LOGFILES = USED

#===== Project-dependent implementations of project-independent interfaces =====
# ======== parameter files =================
# These are the C headers that define parameters of whatever nature
# for the implementation that needs the parameters but otherwise
# doesn't care what they are.
# The parameter files macros in the makefile must use _H_PARAM suffix as in
# FOO_H_PARAM = foo123.h
# The C code must use the symbol with the _H_ suffix, as in
# #include FOO_H_. The Unimal parameter files have _U_PARAM suffix.
MEMMAP_H_PARAM = memmap_$(PROJ).h

# ======= implementation files ==============
# These are the C sources that provide an implementation of required
# interfaces defined in a header file
# The parameter files macros in the makefile must use _C_IMPLEM suffix as in
# BAR_C_IMPLEM = bar2007.c
# The definitions of this sort are used in conf.mak files to include the
# appropriate implementation for the project. Whether they propagate to the
# project header is TBD. There is no obvious use for them in the C code.
# E.g. MNCBDEF_C_IMPLEM = mncbdefs.c
