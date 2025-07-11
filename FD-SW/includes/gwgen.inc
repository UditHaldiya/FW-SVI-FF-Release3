#MP If 0 ;Tombstone header
A collection of macros to generate GW script
Currently, usable for parameter definitions
#MP Endif
#MP Include "ustd.inc"
#MP Include "gwtypes.inc"
#MP Include "paramstubs.inc"
                                #MP
                                #MP
#MP Undef gwout {MAC}
#MP Macro gwout
// Index = #mp%ugwout
#MP gwout = gwout + 1
#mp%sgwout
#MP Endm
#MP
                                #MP
                                #MP
#MP Undef BeginStruct {MAC}
#MP Macro BeginStruct ;[tag, GWtag.opt]
#MP Setstr StructTag {%n#1#}
#MP If #0# > 1
    #MP Setstr StructSubstTag_%n#1# = {#2#}
#MP Else
    #MP ;Setstr StructSubstTag_%n#1# = StructTag
#MP Endif
#MP Setstr BeginStruct "STRUCT " type_prefix {%n#1#}
#MP members = 0
#MP size = 0
#MP Setstr members ""
#MP Endm
                                #MP
                                #MP
#MP Undef StructMember {MAC}
#MP Macro StructMember ;(type, name)
#MP If !Defined(#1#)
	#MP strcmp({uSubstr, {#1#}, 0, 2}, "__")
   #MP If strcmp < 0
        #MP; not a standard type - do nothing to get an error
    #MP Else
        #MP; somewhat frivolously default a standard type to float
        #MP #1# = float32
        #MP Setstr #1# = float32
    #MP Endif
#MP Endif
#MP Setstr members = members " " #1# "|" {%d#1#} "|" {%n#2#}
#MP ParamIndex_%sStructTag%n_%n#2# = members
#MP Setstr MemberType_%umembers = {%n#1#}
#MP MemberType_%umembers = #1#
#MP MemberTypeS_%n#2# = #1#
#MP Setstr MemberTypeS_%n#2# = #1#
#MP members = members + 1
#MP size = size + #1#
#MP Endm
                                #MP
#MP Undef StructMemberLike {MAC}
#MP Macro StructMemberLike ;(basename, name, attrib_pairs.unused)
#MP Ifdef MemberTypeS_%n#1#
    #MP basetype = MemberTypeS_%n#1#
    #MP Setstr basetype = MemberTypeS_%n#1#
#MP Else
    #MP Setstr s = {uSubstr, {#1#}, 0, 2}
    #MP strcmp(s, "__")
    #MP If strcmp < 0
        #MP; not a standard parameter - do nothing to get an error
    #MP Else
        #MP; somewhat frivolously default a standard param to float
        #MP basetype = float32
        #MP Setstr basetype = float32
    #MP Endif
#MP Endif
#MP StructMember[basetype, #2#]
#MP Endm
                                #MP
#MP Undef EndStruct {MAC}
#MP Macro EndStruct ;(old_style.opt)
#MP Setstr gwout = BeginStruct " " {%dmembers} members
#MP UStructMems_%sStructTag = members
#MP UStructSize_%sStructTag = size
#MP If (#0# != 0)
#MP   If (#1# != 0) ; no params or param is non-0 - new style
#MP     ;Present the old-style definition of the struct
#MP     Setstr gwout = "STRUCT " type_prefix StructTag " " {%umembers}
#MP     For i=0, members-1
#MP         Setstr memtype = MemberType_%ui
#MP         memtype = MemberType_%ui
#MP         Setstr gwout = gwout " " %smemtype "," {%umemtype}
#MP     Endfor
#MP   Endif
#MP Endif
#MP Ifdef StructSubstTag_%sStructTag {STR}
    #MP ; The struct is substitued
#MP Else
#mp%sgwout
#MP Endif
#MP Endm
                                #MP
                                #MP
#MP ;--------------- Standard types ------------------

#MP     ;FLOAT_S
#MP UStructSize_FLOAT_S = 5
#MP UStructMems_FLOAT_S = 2
#MP ParamIndex_FLOAT_S_status = 0
#MP ParamIndex_FLOAT_S_value = 1
                                #MP
#MP     ;SCALE
#MP UStructSize_SCALE = 11
#MP UStructMems_SCALE = 4
#MP ParamIndex_SCALE_eu_100 = 0
#MP ParamIndex_SCALE_eu_0 = 1
#MP ParamIndex_SCALE_units = 2
#MP ParamIndex_SCALE_dec_pt = 3
                                #MP
#MP     ;DISC_S
#MP UStructSize_DISC_S = 2
#MP UStructMems_DISC_S = 2
#MP ParamIndex_DISC_S_status = 0
#MP ParamIndex_DISC_S_value = 1
                                #MP
                                #MP
                                #MP
#MP ;--------------- instances ------------------
                                #MP
#MP Undef BeginRecordParam {MAC}
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP gw_attrib[#3#]
#MP param_attrib = #3#
#MP size = UStructSize_%n#1#
#MP members = UStructMems_%n#1#
#MP SubIndexAccess=0
#MP Setstr Separator = " #"
#MP Setstr InitString = ""
#MP Setstr RecordParam = "PARAM " {%n#2#}
#MP If #0# > 5
#MP     Setstr RecordParam = RecordParam "|" {%n#6#}
#MP Endif
#MP Ifdef StructSubstTag_%n#1#
    #MP Setstr T = StructSubstTag_%n#1#
#MP Else
    #MP Setstr T = {%n#1#}
#MP Endif
#MP Setstr RecordParam = RecordParam " " gw_attrib " " {%dsize} " Record " type_prefix T " " {%dmembers}
#MP Setstr StructTag {%n#1#}
#MP Endm


#MP Undef BeginStdRecordParam {MAC}
#MP Macro BeginStdRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Save type_prefix
#MP Setstr type_prefix = ""
#MP BeginRecordParam[[1 : #0#]]
#MP Restore type_prefix
#MP Endm

                                #MP
#MP Undef DefaultRecordParam {MAC}
#MP Macro DefaultRecordParam ;(member_name, default_value, subx_access, dd_name.opt)
#MP n = ParamIndex_%sStructTag%n_%n#1#
#MP ;If #0# > 3
#MP ;Setstr
#MP ;Else
#MP     ;default name - with a _ prefix
#MP ;todo Setstr DD_var_name_%sStructTag%n_%un = "_" ?
#MP ;Endif
#MP If (#3# & SUBX_ACCESS) != 0
#MP     SubIndexAccess = SubIndexAccess | (1<<n)
#MP Endif
#MP Setstr InitString = InitString + Separator + #2# ;TODO: Account for order of initialization!!!!!!!!
#MP Setstr Separator = ";"
#MP Endm
                                #MP
#MP Undef EndRecordParam {MAC}
#MP Macro EndRecordParam ;()
#MP If SubIndexAccess == (1<<members) - 1
#MP     SubIndexAccess = 0
#MP Endif
#MP Setstr gwout = RecordParam InitString
#MP If 1 ;(param_attrib & param_attrib_W) != 0
#MP     Setstr gwout = gwout " SubIndexAccess=" {%uSubIndexAccess}
#MP Endif
#MP gwout
#MP Undef param_attrib
#MP Endm
                                #MP
                                #MP
#MP Undef BeginSimpleParam {MAC}
#MP Macro BeginSimpleParam ;[type, name, access, dd_name.opt]
#MP Setstr gwout = ""
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
#MP Undef BeginSimpleStdParam {MAC}
#MP Macro BeginSimpleStdParam ;[type, name, access, dd_name.opt]
#MP Setstr gwout = "STANDARD_"
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
#MP Macro BeginSimpleParam_Common ;[type, name, access, dd_name.opt]
#MP gw_attrib[#3#]
#MP Setstr gwout = gwout "PARAM " {%n#2#}
#MP If #0# > 3
#MP     Setstr gwout = gwout "|" {%n#4#}
#MP Endif
#MP Setstr gwout = gwout " " gw_attrib " " {%d#1#} " Simple " #1# " 1"
#MP Endm
                                #MP
#MP Undef DefaultSimpleParam {MAC}
#MP Macro DefaultSimpleParam ;[value]
#MP Setstr gwout = gwout " #" #1#
#MP Endm
                                #MP
#MP Undef EndSimpleParam {MAC}
#MP Macro EndSimpleParam ;[type, name, access]
#MP gwout
#MP Endm
                                #MP
                                #MP
#MP Undef BeginArrayParam {MAC}
#MP Macro BeginArrayParam ;[type, name, dimension, access]
#MP ArrayDim = #3#
#MP size = ArrayDim * #1#
#MP gw_attrib[#4#]
#MP Setstr gwout = "PARAM " {%n#2#} " " gw_attrib " " {%dsize} " Array " #1# " " {%uArrayDim}
#MP Setstr Separator = " #"
#MP Endm
                                #MP
#MP Undef DefaultArrayParams {MAC}
#MP Macro DefaultArrayParams ;[min_index, max_index, value]
#MP If (#1# < 0) || (#2# >= ArrayDim)
#MP     "Error: invlaid indices"
#MP Endif
#MP For i=#1#, #2#
#MP     Ifdef ArrayParam_%ui
#MP         "Error: overlapping indices"
#MP     Endif
#MP     Setstr ArrayParam_%ui = #3#
#MP Endfor
#MP Endm
                                #MP
#MP Undef EndArrayParam {MAC}
#MP Macro EndArrayParam
#MP For i=0, ArrayDim-1
#MP     If !Defined(ArrayParam_%ui)
#MP         "Error: undefined index"
#MP     Endif
#MP     Setstr gwout = gwout Separator ArrayParam_%ui
#MP     Setstr Separator = ","
#MP     Undef ArrayParam_%ui
#MP Endfor
#MP gwout
#MP Endm
                                #MP
#MP Undef BeginEnumType {MAC}
#MP; Name must be distinctive, such as beginning with ENUM_
#MP Macro BeginEnumType ;[basetype, name]
#MP Setstr ddtype_%n#2# = "ENUMERATED(" {%d#1#} ")"
#MP Setstr #2# = #1#
#MP #2# = #1#
#MP Endm
                                #MP


