#MP Macro eepshim ;[volume, Type+, ... ]
#MP For eep_i=2, #0#
#MP nvram_Entry[%n#eep_i#, TypeUnsafe_eepshim_Set_%n#eep_i#, TypeUnsafe_eepshim_Get_%n#eep_i#, %n#1#, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_GROUP_RECOVER|NVMFLAG_INIT_1"]
#MP Endfor
#MP Endm
#MP eepshim[Vol0, ApplDeviceId]
#MP eepshim[Vol0, nv_fb_link_cfg, nv_trend_cfg, nv_vcr_cfg, nv_fb_start_cfg, nv_las_cfg, NV_fb]
#MP eepshim[Vol0, nv_fdc_blk_base_cfg, nv_fdc_blk_dll_base_cfg, nv_fdc_blk_sm_cfg, nv_fdc_blk_dll_lm_info_cfg, nv_fdc_blk_dll_lm_data_cfg, nv_swdl_blk_dwnld_cfg]
#MP Macro eepshimx ;[volume, <Type, count>+ ... ]
#MP For eep_b=1, (#0#-1)/2
#MP     eep_i = 2*eep_b
#MP     eep_n = eep_i+1
#MP     nvram_Entry[%nST_%n#eep_i#, TypeUnsafe_eepshim_Set%n#eep_i#%nStaticData, TypeUnsafe_eepshim_Get%n#eep_i#%nStaticData, %n#1#, "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_GROUP_RECOVER|NVMFLAG_INIT_1", #eep_n#]
#MP Endfor
#MP Endm
#MP Save nv_std
#MP Save nvflags
#MP Setstr nv_std = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_GROUP_RECOVER|NVMFLAG_INIT_1" ;standard block flags
#MP Setstr nvflags = nv_std "|NVMFLAG_RESTORED" ;mark as restored on "Restore to Factory"; currently, PTB only
#MP eepshimx[Vol0, ptb, 1]
#MP Setstr nvflags = nv_std
#MP eepshimx[Vol0, resb, 1, aifb, 3, aofb, 1, difb, 2, dofb, 2, maifb, 1, pidfb, 2, isfb, 1, osfb, 1, csfb, 1, arfb, 1]
#MP Restore nvflags
#MP Restore nv_std
