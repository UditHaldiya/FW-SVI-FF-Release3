#MP If 0 ;Tombstone header
/*
Copyright 2004-2012 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file nvramdef.inc
    \brief Definitions of NVRAM layout entries

    This version COULD be a hull which includes nvmassembly.inc which in turn
    may be generated automatically e.g. by NVMEM entries exported by modules

    CPU: Any

    OWNER: AK
*/
#MP Endif ;Tombstone header
#MP
#MP Include "nvdimensions.inc"
#MP Include "projectdef.inc"
#MP
#MP ;bitmapped flags defining the handling of data structures
#MP; Usage: nvram_Entry(typename_without_t, set_function, get_function, volume, flags_string, [num_elements]optional)
#MP; flags_string is a straight pass-through to C code
#MP
#MP NVMEM_NUM_VOLUMES = NVMEM_MAX_VOLID+1
#MP
#MP
#MP Expand nvram_LayoutStart(nvram_version)
#MP Save uJoin
#MP Setstr uJoin = " | "

#MP nvram_Entry[StartupVersionNumber, TypeUnsafe_nvmem_SetVersion, TypeUnsafe_nvmem_GetVersion, VolX, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_GROUP_RECOVER|NVMFLAG_INIT_1", NVMEM_NUM_VOLUMES]
#MP nvram_Entry[ConfigurationChanged, nvram_SetConfigurationChanged, nvram_GetConfigurationChanged, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1"] ;absolutely cannot have Flags_ConfChanged
#MP nvram_Entry[AdvancedParam, TypeUnsafe_ffcheck_SetAdvancedParam, TypeUnsafe_ffcheck_GetAdvancedParam, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2"]
#MP nvram_Entry[logdata, TypeUnsafe_logf_InitSet, TypeUnsafe_logf_InitGet, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1"]
#MP nvram_Entry(FactoryDefaultState, TypeUnsafe_facdef_SetState, TypeUnsafe_facdef_GetState, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1") ;factory default state

#MP Include "eepshim.inc"
#MP Include "ff2nvram.inc"

#MP nvram_Entry(HistogramPosNV, TypeUnsafe_histogram_SetPosData, TypeUnsafe_histogram_GetPosData, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1|NVMFLAG_RESTORED") ;position histogram
#MP nvram_Entry(HistogramPosErrNV, TypeUnsafe_histogram_SetPosErrData, TypeUnsafe_histogram_GetPosErrData, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1|NVMFLAG_RESTORED") ;position error histogram

#MP ;The NVMFLAG_RESTORED here must match the flag in TB trends (see ff2nvram.inc and how it is generated). 
#MP ;Otherwise, there will be a mess in RB.RESTART=Defaults and on TB.OFFLINE_DIAGNOSTICS=Clear any trend.
#MP ;When the flag is set (equally in dependent cases), trends will clear on RB.RESTART=Defaults; otherwise, the values will be preserved.
#MP nvram_Entry(TrendInfo, TypeUnsafe_tbtrend_Set, TypeUnsafe_tbtrend_Get, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1", 3) ;cycle/position/poserr trend service info

#MP nvram_Entry(PresAlertConf, TypeUnsafe_ffpres_SetAlertConf, TypeUnsafe_ffpres_GetAlertConf, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1|NVMFLAG_RESTORED", 3) ;hi/lo/lolo alerts
#MP nvram_Entry(Act3Min, TypeUnsafe_act3min_Set, TypeUnsafe_act3min_Get, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1|NVMFLAG_RESTORED") ;

#MP nvram_Entry(CycleCounterAlert, TypeUnsafe_ccalert_Set, TypeUnsafe_ccalert_Get, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2|NVMFLAG_RESTORED") ;
#MP nvram_Entry(TravelAlert, TypeUnsafe_travel_Set, TypeUnsafe_travel_Get, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2|NVMFLAG_RESTORED") ;

#MP nvram_Entry(APPHeader, TypeUnsafe_hm_SetAPPHeader, TypeUnsafe_hm_GetAPPHeader, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1") ;
#MP nvram_Entry(FWDLInfo, TypeUnsafe_fwdl_SetDLInfo, TypeUnsafe_fwdl_GetDLInfo, Vol0, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_1") ;

#MP Restore uJoin

#MP Expand nvram_LayoutEnd()
#MP ;/* This line marks the end of the source */
