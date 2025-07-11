#MP ;parameter access and storage attributes
#MP param_attrib_R = 1
#MP param_attrib_W = 2
#MP param_attrib_NV = 4
#MP param_attrib_SR = 8 ;static revision must increment
#MP param_attrib_MN_N = 0x100 ;MN-style storage in FFP
#MP param_attrib_MN_F = 0x200 ;Storage in FFP log file
#MP param_attrib_MN_A = 0x400 ;Storage in APP
#MP param_attrib_MN_NoRestore = 0x800 ; no restore on "Restore to factory"
#MP param_attrib_MN_DYN = 0x1000 ;Dynamic variable to be jammed to BAD if TB in OOS
                    #MP
#MP ;MN combos
#MP MN_NOFR = param_attrib_MN_NoRestore
#MP MN_N = param_attrib_MN_N
#MP MN_F = param_attrib_MN_F
#MP MN_A = param_attrib_MN_A
#MP MN_AN = param_attrib_MN_A|param_attrib_MN_N
#MP MN_DYN = param_attrib_MN_DYN
#MP MN_EVERYTHING = MN_AN|MN_F|MN_DYN|MN_NOFR
                    #MP
#MP ;GW combos
#MP R = param_attrib_R
#MP RW = param_attrib_R|param_attrib_W
#MP NR = param_attrib_R|param_attrib_NV
#MP SR = param_attrib_R|param_attrib_SR
#MP NRW = param_attrib_R|param_attrib_W|param_attrib_NV
#MP SRW = param_attrib_R|param_attrib_W|param_attrib_NV|param_attrib_SR
#MP VR = param_attrib_R|param_attrib_SR
#MP VRW = param_attrib_R|param_attrib_W|param_attrib_SR
                    #MP
#MP ;Convert access attrib to effective GW attrib
#MP Macro gw_attrib ;[attrib]
#MP     gw_attrib = #1# & ~MN_EVERYTHING
#MP     If (#1# & (MN_EVERYTHING)) != 0
#MP         ;Softing N disappears; S turns to V
#MP         gw_attrib = gw_attrib & ~param_attrib_NV
#MP     Endif
#MP     Setstr  gw_attrib = gw_attrib_%ugw_attrib
#MP Endm
#MP Setstr gw_attrib_%uR = "R"
#MP Setstr gw_attrib_%uRW = "RW"
#MP Setstr gw_attrib_%uNR = "NR"
#MP Setstr gw_attrib_%uSR = "SR"
#MP Setstr gw_attrib_%uNRW = "NRW"
#MP Setstr gw_attrib_%uSRW = "SRW"
#MP If VR != SR
#MP Setstr gw_attrib_%uVR = "VR"
#MP Endif
#MP Setstr gw_attrib_%uVRW = "VRW"
                    #MP
#MP ; ========= types =============
#MP Setstr ddtype_bool_t = "ENUMERATED (1) {ENUM_ENABLE_DISABLE}"
#MP Setstr bool_t "BOOLEAN"
#MP bool_t = 1
                    #MP
#MP Setstr ddtype_u8 = "UNSIGNED_INTEGER(1)"
#MP Setstr u8 "UNSIGNED8"
#MP u8 = 1
                    #MP
#MP Setstr ddtype_s8 = "INTEGER(1)"
#MP Setstr s8 "INTEGER8"
#MP s8 = 1
                    #MP
#MP Setstr ddtype_u16 = "UNSIGNED_INTEGER(2)"
#MP u16 = 2 ;size
#MP Setstr u16 = "UNSIGNED16" ;.gw name
                    #MP
#MP Setstr ddtype_s16 = "INTEGER(2)"
#MP s16 = 2 ;size
#MP Setstr s16 = "INTEGER16" ;.gw name
                    #MP
#MP Setstr ddtype_u32 = "UNSIGNED_INTEGER(4)"
#MP Setstr u32 "UNSIGNED32"
#MP u32 = 4
                    #MP
#MP Setstr ddtype_s32 = "INTEGER(4)"
#MP Setstr s32 "INTEGER32"
#MP s32 = 4
                    #MP
#MP Setstr ddtype_float32 = "FLOAT"
#MP Setstr float32 "FLOATING_POINT"
#MP float32 = 4
                    #MP
#MP ;Setstr ddtype_date_t = "DATE_AND_TIME"
#MP Setstr date_t "DATE"
#MP date_t = 7
                    #MP
#MP ;Setstr ddtype_date_t = "DATE_AND_TIME"
#MP Setstr time_s "TIME_VALUE"
#MP time_s = 8
                    #MP
#MP For i=1, 32
#MP     Setstr ddtype_stringv%di = "VISIBLE (" {%di} ")"
#MP     Setstr stringv%di = "VISIBLE_STRING"
#MP     stringv%di = i
#MP Endfor
                    #MP
#MP Setstr bitstr1 = "BIT_STRING"
#MP bitstr1 = 1
                    #MP
#MP Setstr bitstr2 = "BIT_STRING"
#MP bitstr2 = 2
                    #MP
#MP Setstr bitstr4 = "BIT_STRING"
#MP bitstr4 = 4
                    #MP
#MP ;base types of standard parameters
#MP ; they are float32 by default; others are entered here in the form
#MP ;MemberTypeS_<std_param> = base type (FW/GW)
#MP ;Setstr MemberTypeS_<std_param> = base type (DD)
#MP ;================== End types ========================
#MP ;------------------ common structs -------------------
#MP Setstr record_ddtype_FLOAT_S_1 = "ENUMERATED(1)"
#MP Setstr record_ddtype_FLOAT_S_2 = ddtype_float32
#MP Setstr record_ddtype_DISCRETE_S_1 = "ENUMERATED(1)"
#MP Setstr record_ddtype_DISCRETE_S_2 = ddtype_u8
                    #MP
#MP Setstr type_prefix = "_"
                    #MP
                    #MP
#MP ;Symbolic flags (bitmap) for subindex access
#MP SUBX_ACCESS = 1
#MP SUBX_NOPARAMWRAP = 2 ;Not included in automatic definition of expanded Record in DD
