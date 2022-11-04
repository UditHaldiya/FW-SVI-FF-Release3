#MP If 0 ;Tombstone header
A collection of macros to generate DD header
Currently, usable for parameter definitions
#MP Endif
#MP Include "gwtypes.inc"
#MP Include "paramstubs.inc"
                                #MP
                                #MP
#MP Undef BeginStruct {MAC}
#MP Macro BeginStruct ;(tag)
#MP Setstr StructTag {%n#1#}
#MP Setstr BeginStruct "STRUCT " type_prefix {%n#1#}
#MP members = 0
#MP size = 0
#MP Setstr members ""
#MP Endm
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
#MP Macro AppendParam ;[out, type, name]
#MP Setstr #1# = #1# "    " #2# ",    "
#MP Setstr #1# = #1# #3# ";   ||"
#MP Endm
                                #MP
#MP Macro AddParam ;[dd_name, dd_record_type.opt]
#MP If #0#>1
#MP toupper[{%n#2#}]
#MP Else
#MP toupper[#1#]
#MP Endif
#MP tolower[#1#]
#MP only5 = 0
#MP If Defined(GenDDdefs)
	#MP If 0 ;FieldComm disallowed (GenDDdefs & (1<<4)) == 0
		#MP only5 = 1
	#MP Endif
#MP Endif
#MP If only5
	#MP AppendParam[out5, toupper, tolower]
#MP Else
	#MP AppendParam[out, toupper, tolower]
#MP Endif
#MP Endm
                                #MP
#MP Undef BeginRecordParam {MAC}
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP If #0# > 5
#MP Setstr s = {%n#6#}
#MP Else
#MP Setstr s = {%n#2#}
#MP Endif
#MP AddParam[s, #2#]
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
#MP Endm
                                #MP
#MP Undef EndRecordParam {MAC}
#MP Macro EndRecordParam ;()
#MP Endm
                                #MP
                                #MP
#MP Undef BeginSimpleParam {MAC}
#MP Macro BeginSimpleParam ;[type, name, access, dd_name.opt]
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
#MP Undef BeginSimpleStdParam {MAC}
#MP Macro BeginSimpleStdParam ;[type, name, access, dd_name.opt]
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
#MP Macro BeginSimpleParam_Common ;[type, name, access, dd_name.opt]
#MP If #0# > 3
#MP Setstr s = {%n#4#}
#MP Else
#MP Setstr s = {%n#2#}
#MP Endif
#MP AddParam[s, #2#]
#MP Endm
                                #MP
#MP Undef DefaultSimpleParam {MAC}
#MP Macro DefaultSimpleParam ;[value]
#MP Endm
                                #MP
#MP Undef EndSimpleParam {MAC}
#MP Macro EndSimpleParam ;[type, name, access]
#MP Endm
                                #MP
                                #MP
#MP Undef BeginArrayParam {MAC}
#MP Macro BeginArrayParam ;[type, name, dimension, access]
#MP AddParam[{%n#2#}]
#MP Endm
                                #MP
#MP Undef DefaultArrayParams {MAC}
#MP Macro DefaultArrayParams ;[min_index, max_index, value]
#MP Endm
                                #MP
#MP Undef EndArrayParam {MAC}
#MP Macro EndArrayParam
#MP Endm
                                #MP
#MP Undef DefineEnumValue {MAC}
#MP Macro DefineEnumValue ;[name, value, dd-text.opt, dd-help.opt, dd-help-prefix.opt, dd-help-suffix.opt ]
#define #mp%n#1# (#mp%d#2#) /*Compatible with definition for C*/
#MP Endm
                #MP


