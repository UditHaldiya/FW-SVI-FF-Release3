#MP If 0 ;Tombstone header
A collection of macros to generate DD header
Currently, usable for parameter definitions
#MP Endif
#MP Include "gwtypes.inc"
#MP Include "paramstubs.inc"
                                #MP
#MP Macro ddhelp ;takes a global DDHelp
#MP Ifdef DDHelp {STR}
    #MP Ifdef DDHelp {NUM}
#ifndef DD4
    #MP Endif
    #MP ;If it is in square brackets (=standard index), omit parens
    #MP strcmp({uSubstr, DDHelp, 0, 1}, "[") ;simplifying/cheating
    #MP If strcmp < 0
    HELP "#mp%sDDHelp";
    #MP Else
    HELP #mp%sDDHelp;
    #MP Endif
    #MP Ifdef DDHelp {NUM}
#endif
    #MP Endif
    #MP Undef DDHelp {STR}
#MP Endif
#MP Endm
                                #MP
                                #MP
#MP Undef BeginStruct {MAC}
#MP Macro BeginStruct ;[tag, GWtag.opt]
    #MP Setstr StructTag {%n#1#}
    #MP RecordMemberCount = 0
#MP Endm
                                #MP
#MP Undef StructMember {MAC}
#MP Macro StructMember ;(type, name, ddname.opt, attrib_pairs.opt)
    #MP RecordMemberCount = RecordMemberCount + 1
    #MP Ifdef GenDDdefs
        #MP ;If !Defined(#1#)
            #MP strcmp({uSubstr, {#1#}, 0, 2}, "__")
            #MP If strcmp < 0
                #MP; not a standard type - do nothing - to get an error
            #MP Else
                #MP; somewhat frivolously default a standard type to float
                #MP #1# = float32
                #MP Setstr #1# = float32
                #MP Setstr ddtype_%n#1# = ddtype_float32
                #MP Setstr SubstName_%sStructTag%n_%dRecordMemberCount = {#1#}
            #MP Endif
        #MP ;Endif
        #MP toupper[ddtype_%n#1#]
        #MP Setstr record_ddtype_%sStructTag%n_%dRecordMemberCount = toupper
        #MP ;Check for optional DD name"
        #MP ddtype_index = 2
        #MP If #0# == 3
            #MP ddtype_index = 3
        #MP Else
            #MP If #0# > 3
                #MP If !Isconst(#4#) ;If a string literal, should be attrib value, and #3# should be attrib name
                    #MP ddtype_index = 3
                #MP Endif
            #MP Endif
        #MP Endif
        #MP Setstr Srecord_ddtype_%sStructTag%n_%n#ddtype_index# = {%n#1#}
        #MP Ifdef ddtype_details_%n#1#
            #MP Setstr record_ddtype_details_%sStructTag%n_%dRecordMemberCount = ddtype_details_%n#1#
        #MP Endif
        #MP If #0# > ddtype_index
            #MP Setstr S = "{ "
            #MP For i=ddtype_index+1, #0#
                #MP Setstr S = S {#i#} " "
                #MP i=i+1 ;to increment by 2
                #MP Setstr S = S #i# ";"
            #MP Endfor
            #MP Setstr S = S " }"
            #MP Setstr record_ddtype_details_%sStructTag%n_%dRecordMemberCount = S
        #MP Endif
    #MP Endif
#MP Endm
                                #MP
#MP Undef StructMemberLike {MAC}
#MP Macro StructMemberLike ;(basename, name, attrib_pairs)
	#MP Liked_%n#2# = 2020 ;just define so DDLabel not be required
    #MP RecordMemberCount = RecordMemberCount + 1
    #MP Ifdef GenDDdefs
		#MP Ifdef Srecord_ddtype_%sStructTag%n_%n#1#
		    #MP ;basetype = MemberTypeS_%n#1#
		    #MP Setstr basetype = Srecord_ddtype_%sStructTag%n_%n#1#
		#MP Else
		    #MP Setstr s = {uSubstr, {#1#}, 0, 2}
		    #MP strcmp(s, "__")
		    #MP If strcmp < 0
		        #MP; not a standard parameter - do nothing to get an error
		    #MP Else
		        #MP; somewhat frivolously default a standard param to float
		        #MP ;basetype = float32
		        #MP Setstr basetype = {float32}
		        #MP Setstr ddbasename%n_%n#1# = {#1#}
		    #MP Endif
		#MP Endif
        #MP Setstr basename_%sStructTag%n_%n#2# = {%n#1#}
        #MP ;Setstr basetype = Srecord_ddtype_%sStructTag%n_%n#1#
        #MP ;StructMember[basetype, #2#]
        #MP toupper[ddtype_%sbasetype]
        #MP Setstr record_ddtype_%sStructTag%n_%dRecordMemberCount = toupper
        #MP Setstr Srecord_ddtype_%sStructTag%n_%n#2# = basetype
        #MP Ifdef ddtype_details_%sbasetype
            #MP Setstr record_ddtype_details_%sStructTag%n_%dRecordMemberCount = ddtype_details_%sbasetype
        #MP Endif
        #MP
        #MP For x=3, #0#
            #MP ;x is attrib, x+1 is a string value
            #MP Setstr AttribRedef_%sStructTag%n_%n#2#%n_%dx = {%n#x#}
            #MP x=x+1
            #MP Setstr AttribRedef_%sStructTag%n_%n#2#%n_%dx = #x#
       #MP Endfor
    #MP Endif
#MP Endm
                                #MP
#MP Undef EndStruct {MAC}
#MP Macro EndStruct ;(old_style.opt)
#MP Endm
                                #MP
                                #MP
#MP ;-------------------- channels ------------------ (Nothing here)
                                #MP
                                #MP
#MP ;-------------------- enumerations ------------------
#MP; Name must be distinctive, such as beginning with ENUM_
#MP Undef BeginEnumType {MAC}
#MP Macro BeginEnumType ;[basetype, name, ddname.opt]
    #MP valcount = 0
    #MP Setstr typename = {#2#}
    #MP Ifdef GenDDdefs
        #MP If #0#>=3
            #MP i=3
        #MP Else
            #MP i=2
        #MP Endif
        #MP Setstr ddtype_%n#i# = "ENUMERATED(" {%d#1#} ")"
        #MP Setstr ddtype_details_%n#i# = "{ " {%n#i#} " }"
        #MP Setstr #i# = #1#
        #MP #i# = #1#
        #MP IsEnumType_%n#i# = 1 ;Just define it
        #MP Setstr out_name = "#define " {%n#i#} " \"
        #MP out = 0 ;count enum values
    #MP Endif
#MP Endm
                #MP
#MP Undef BeginEnumType5 {MAC}
#MP Macro BeginEnumType5 ;[basetype, name, ddname.opt]
    #MP Ifdef GenDDdefs
        #MP BeginEnumType[[1:#0#]]
        #MP omit_help = 1 ;just define to consume at end
    #MP Endif
#MP Endm
                #MP
#MP Undef BeginEnumType4 {MAC}
                #MP
                #MP
#MP Undef DefineEnumValue {MAC}
#MP Macro DefineEnumValue ;[name, value, dd-text.opt, dd-help.opt, dd-help-prefix.opt, dd-help-suffix.opt ]
    #MP valcount = valcount+1
    #MP Setstr enumval_%stypename%n_%dvalcount = {%n#1#}
    #MP enumval_%stypename%n_%dvalcount = #2#
    #MP If #0#>=3 ;otherwise, the definition is hidden from DD
        #MP Setstr enumtext_%stypename%n_%dvalcount = #3#
        #MP If #0#>=4
            #MP Setstr enumhelp_%stypename%n_%dvalcount = #4#
        #MP Endif
    #MP Else
        #MP Setstr enumtext_%stypename%n_%dvalcount = "NOTE: enum value is hidden from DD"
    #MP Endif
                #MP
    #MP Ifdef GenDDdefs
        #MP If #0#>=3 ;otherwise, the definition is hidden from DD
            #MP ;Special handling of standard references (enclosed in [])
            #MP Setstr br = {uSubstr, #3#, 0, 1}
            #MP strcmp[br, "["]
            #MP Setstr out%dout = "{ " {%d#2#} ", "
            #MP If strcmp<0 ;not a ref - enclose in quotes (open)
                #MP Setstr out%dout = out%dout #@"#
            #MP Endif
            #MP Setstr out%dout = out%dout #3#
            #MP If strcmp<0 ;not a ref - enclose in quotes (close)
                #MP Setstr out%dout = out%dout #@"#
            #MP Endif
            #MP If #0#>=4
                #MP seen_help = 1
                #MP Setstr br = {uSubstr, #4#, 0, 1}
                #MP strcmp[br, "["]
                #MP If strcmp<0 ;not a ref - enclose in quotes and honor prefix and suffix
                    #MP If #0#>=5
                        #MP Setstr help%dout = #5# #@"# #4#
                    #MP Else
                        #MP Setstr help%dout = #@"# #4#
                    #MP Endif
                #MP Else
                    #MP Setstr help%dout = #4#
                #MP Endif
                #MP If strcmp<0 ;not a ref - enclose in quotes and honor prefix and suffix
                    #MP Setstr help%dout = help%dout #@"#
                    #MP If #0#>=6
                        #MP Setstr help%dout = help%dout #6#
                    #MP Endif
                #MP Endif
            #MP Endif
            #MP out = out+1
        #MP Endif
    #MP Endif
#MP Endm
                #MP
#MP Undef EndEnumType {MAC}
                #MP
#MP Macro helpless
#mp%sout_name
    #MP For i=0,out-1
        #MP Setstr out = out%di "}"
        #MP If i<out-1
            #MP Setstr out = out ", \"
        #MP Endif
    #mp%sout
    #MP Endfor
#MP Endm
                #MP
#MP Macro helpful
#mp%sout_name
    #MP For i=0,out-1
        #MP Setstr out = out%di
        #MP Ifdef help%di {STR}
            #MP Setstr out = out ", "  help%di
            #MP Undef help%di
        #MP Endif
        #MP Setstr out = out "}"
        #MP If i<out-1
            #MP Setstr out = out ", \"
        #MP Endif
    #mp%sout
    #MP Endfor
#MP Endm
                #MP
#MP Macro EndEnumType
    #MP ;valcount_%stypename = valcount
    #MP Ifdef GenDDdefs
        #MP If !Defined(seen_help)
            #MP helpless
        #MP Else
            #MP If Defined(omit_help) ;i.e. seen help but want to omit it
#ifdef DD4
                #MP helpless
#else
                #MP helpful
#endif
            #MP Else
                #MP helpful
            #MP Endif
        #MP Endif
        #MP Undef omit_help
        #MP Undef seen_help
        #MP Undef out_name
    #MP Endif ;GenDDdefs
#MP Endm
                #MP
#MP Undef EndEnumType4 {MAC}
#MP ;-------------------- bit enumerations ------------------
#MP Macro bitreverse ;(bitnum, sizeof)
    #MP bitreverse = 1<<(#2#*8-1-#1#)
#MP Endm
#MP Macro bitreverse1 ;(bitnum, sizeof)
    #MP bitreverse1 = (#2#*8-1-#1#) ;bit number
#MP Endm
#MP; Name must be distinctive, such as beginning with ENUM_
#MP Undef BeginBitEnumType {MAC}
#MP Macro BeginBitEnumType ;[basetype, name]
    #MP Ifdef GenDDdefs
        #MP Setstr ddtype_%n#2# = "BIT_ENUMERATED(" {%d#1#} ")"
        #MP Setstr ddtype_details_%n#2# = "{ " {%n#2#} " }"
        #MP Setstr #2# = #1#
        #MP #2# = #1#
        #MP tsizeof = #1#
        #MP IsEnumType_%n#2# = 1 ;Just define it
        #MP Setstr out_name = "#define " {%n#2#} " \"
        #MP out = 0
    #MP Endif
#MP Endm
                #MP
#MP Undef BeginBitEnumType5 {MAC}
#MP Macro BeginBitEnumType5 ;[basetype, name]
    #MP Ifdef GenDDdefs
        #MP BeginBitEnumType[[1:#0#]]
        #MP omit_help = 1 ;just define to consume at end
    #MP Endif
#MP Endm
                #MP
#MP Undef BeginBitEnumType4 {MAC}
                #MP
#MP Undef DefineBitEnumValue {MAC}
#MP Macro DefineBitEnumValue ;[name, value, dd-text, dd-help.opt]
        #MP bitreverse1[#2#, tsizeof]
#define #mp{%n#1#}_BIT (#mp%dbitreverse1) /* compatible with C definition but bit order reversed */
    #MP Ifdef GenDDdefs
        #MP If #0#>=3 ;otherwise, the definition is hidden from DD
            #MP ;mask = 1<<#2#
            #MP bitreverse[#2#, tsizeof]
            #MP Setstr out%dout = "{ 0x" {%Xbitreverse}
            #MP Setstr out%dout = out%dout #@, "# #3# #@"#
            #MP If #0#>=4
                #MP seen_help = 1
                #MP Setstr help%dout = #@"# #4# #@"#
            #MP Endif
            #MP out = out+1
        #MP Endif
    #MP Endif
#MP Endm
                #MP
#MP Undef EndBitEnumType {MAC}
#MP Macro EndBitEnumType
    #MP EndEnumType
#MP Endm
                #MP
#MP Undef EndBitEnumType4 {MAC}
#MP Macro EndBitEnumType4
    #MP EndBitEnumType
#MP Endm
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
#MP Macro AddParam ;[dd_name, dd_record_type.opt]
#MP Endm
                                #MP
#MP Undef BeginRecordParam {MAC}
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help.opt, dd_name.opt)
#MP Ifdef GenDDdefs
    #MP If #0# > 5
        #MP Setstr StructTag = {%n#6#}
    #MP Else
        #MP Setstr StructTag = {%n#2#}
    #MP Endif
    #MP toupper({#1#})
    #MP Setstr StructType = toupper
    #MP AddParam[s, #2#]
    #MP If #0#>=4
        #MP Setstr CurrentRecordLabel = #4#
    #MP Else
        #MP Setstr CurrentRecordLabel = "|en|No label"
    #MP Endif
    #MP If #0#>=5
        #MP Setstr CurrentRecordHelp = #5#
    #MP Else
        #MP Undef CurrentRecordHelp
    #MP Endif
    #MP attrib_%sStructTag = #3#
#MP Endif ;GenDDdefs
#MP RecordMemberCount = 0
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
#MP RecordMemberCount = RecordMemberCount+1
#MP Ifdef GenDDdefs
    #MP Setstr record_varname_%sStructTag%n_%dRecordMemberCount = {%n#1#}
    #MP If #0# < 4
        #MP Setstr record_ddvarname_%sStructTag%n_%dRecordMemberCount = {%n#1#}
        #MP Setstr ddbasename%n_%n#1# = {%n#1#}
    #MP Else
        #MP Setstr record_ddvarname_%sStructTag%n_%dRecordMemberCount = {%n#4#}
        #MP Setstr ddbasename%n_%n#1# = {%n#4#}
    #MP Endif
    #MP If Defined(DDLabel)
		#MP Setstr record_ddlabel_%sStructTag%n_%dRecordMemberCount = DDLabel ;absolutely MUST be specified
    #MP Else
		#MP If Defined(basename_%sStructTag%n_%n#1#) || Defined(Liked_%n#1#)
			#MP ;redefined variable or LIKE member: Don't need DDLabel
		#MP Else
*** Missing DDLabel for #mp%n#1# of #mp%sStructTag ***
		#MP Endif
    #MP Endif
    #MP Undef DDLabel ;consumed, then undefined
    #MP Ifdef DDHelp {STR}
        #MP Setstr record_ddhelp_%sStructTag%n_%dRecordMemberCount = DDHelp ;should be specified
        #MP Undef DDHelp {STR} ;consumed, then undefined
    #MP Endif
    #MP DefaultStdRecordParam[[1:#0#]]
    #MP
#MP Endif ;GenDDdefs
#MP Endm
                                #MP
#MP Undef DefaultStdRecordParam {MAC}
#MP Macro DefaultStdRecordParam ;(member_name, default_value, subx_access, dd_name.opt)
#MP Ifdef GenDDdefs
    #MP If ((#3# & SUBX_ACCESS) != 0) && ((#3# & SUBX_READONLY) == 0)
    #MP     Setstr record_ddhandling_%sStructTag%n_%dRecordMemberCount = "READ & WRITE"
    #MP Else
    #MP     Setstr record_ddhandling_%sStructTag%n_%dRecordMemberCount = "READ"
    #MP Endif
    #MP Ifdef DDClass
        #MP Setstr record_ddclass_%sStructTag%n_%dRecordMemberCount = DDClass
        #MP Undef DDClass ;consumed, then undefined
    #MP Else
        #MP Setstr record_ddclass_%sStructTag%n_%dRecordMemberCount = "CONTAINED"
    #MP Endif
    #MP Ifdef DDUnits
        #MP Setstr record_ddunits_%sStructTag%n_%dRecordMemberCount = DDUnits
        #MP Undef DDUnits ;consumed, then undefined
    #MP Endif
#MP Endif ;GenDDdefs
#MP Endm
                                #MP
#MP Undef EndRecordParam {MAC}
#MP Macro EndRecordParam ;()
    #MP ;Here we emit
    #MP ;1. All member variables definitions
    #MP ;2. Record definition
    #MP Ifdef GenDDdefs
      #MP If !Defined(IsStdRecord)
        #MP For i=1, RecordMemberCount
          #MP Ifdef SubstName_%sStructTag%n_%di {STR}
            #MP Setstr vname = SubstName_%sStructTag%n_%di
            #MP ;Fatal("reached it")
          #MP Else
            #MP Setstr vname = record_ddvarname_%sStructTag%n_%di
          #MP Endif
          #MP If !Defined(emitted_%svname)
            #MP emitted_%svname = 42 ;just define
            #MP tolower[vname]
            #MP Setstr T1 = {uSubstr, tolower, 0, 2} ;do not emit standard dictionary (starts with __)
            #MP strcmp(T1, "__")
            #MP If strcmp < 0 ;non-standard
                #MP ;a very special treatment of a variable named "status"
                #MP strcmp[tolower, "status"]
            #MP Else
				#MP ;standard variable. Treat as redefined, like elsewhere
              	#MP ;Setstr name = record_varname_%sStructTag%n_%di
				#MP ;Setstr basename_%sStructTag%n_%sname = "|en|" ;have it defined
			#MP Endif
            #MP If strcmp<0
              	#MP ;not a status or standard; emit a VARIABLE
              	#MP Setstr name = record_varname_%sStructTag%n_%di
              	#MP Ifdef basename_%sStructTag%n_%sname ;redefined variable?
	                #MP ;Setstr vname = tolower ;name of variable
	                #MP Setstr basename = basename_%sStructTag%n_%sname
	                #MP Setstr basename = ddbasename%n_%sbasename
#mp%svname LIKE VARIABLE #mp%sbasename
{
	                #MP x=3
	                #MP ;start bad
	                #MP Repeat
	                    #MP Setstr T = AttribRedef_%sStructTag%n_%sname%n_%dx
	                    #MP x=x+1
	                    #MP Setstr S = AttribRedef_%sStructTag%n_%sname%n_%dx
	                    #MP x=x+1
    REDEFINE #mp%sT #mp%sS;
	                    #MP y = Defined(AttribRedef_%sStructTag%n_%sname%n_%dx)
	                #MP While y
	                #MP ;end bad
}
              #MP Else ;not redefined
VARIABLE #mp%stolower
{
                #MP Setstr T = record_ddlabel_%sStructTag%n_%di
                #MP ;If it is in square brackets (=standard index), omit parens
                #MP strcmp({uSubstr, T, 0, 1}, "[") ;simplifying/cheating
                #MP If strcmp < 0
    LABEL "#mp%sT";
                #MP Else
    LABEL #mp%sT;
                #MP Endif
                    #MP Ifdef record_ddhelp_%sStructTag%n_%di
                        #MP Setstr T = record_ddhelp_%sStructTag%n_%di
                        #MP Setstr DDHelp = T
                        #MP ddhelp
                    #MP Endif
                    #MP Setstr T = record_ddclass_%sStructTag%n_%di
    CLASS #mp%sT;
                    #MP Ifdef record_ddunits_%sStructTag%n_%di
                        #MP Setstr T = record_ddunits_%sStructTag%n_%di
    #mp%sT
                    #MP Endif
                    #MP ;Ifdef Srecord_ddtype_%sStructTag%n_%di
                        #MP ;Setstr T = Srecord_ddtype_%sStructTag%n_%di
                    #MP ;Else
                        #MP Setstr T = record_ddtype_%sStructType%n_%di
                    #MP ;Endif
    TYPE  #mp%sT
                    #MP Ifdef record_ddtype_details_%sStructType%n_%di {STR}
    #mp%srecord_ddtype_details_%sStructType%n_%di
                    #MP Else
                        #MP lenT = Ustrlen(T)
                        #MP Setstr lenT = {uSubstr, T, lenT-1, lenT}
                        #MP strcmp[lenT, "}"]
                        #MP If strcmp<0
                            #MP ;not a composite type
            ;
                            #MP Endif
                        #MP Endif
                    #MP Setstr T = record_ddhandling_%sStructTag%n_%di
    HANDLING #mp%sT;
}
              #MP Endif ;Redefined_...
            #MP Endif ;status
          #MP Endif
        #MP Endfor
      #MP Endif ;IsStdRecord
        #MP tolower[StructTag]
RECORD #mp%stolower
{
    LABEL "#mp%sCurrentRecordLabel";
        #MP Ifdef CurrentRecordHelp
            #MP Setstr DDHelp = CurrentRecordHelp
            #MP ddhelp
        #MP Endif
    MEMBERS
    {
        #MP For i=1, RecordMemberCount
            #MP tolower[record_ddvarname_%sStructTag%n_%di]
            #MP toupper[record_varname_%sStructTag%n_%di]
            #MP ;a very special treatment of a variable named "status" (part 2)
            #MP strcmp[tolower, "status"]
            #MP If strcmp<0
                #MP ;not a status; emit a usual member stuff
            #MP;#mp%srecord_ddvarname_%sStructTag%n_%di, #mp%stolower;
            #MP Else
                #MP ;status: borrow a definition (plugging it in tolower for commonality)
                #MP If (attrib_%sStructTag & param_attrib_W) == 0
                    #MP Setstr tolower = "__status_contained_r"
                #MP Else
                    #MP Setstr tolower = "__status_contained"
                #MP Endif
            #MP Endif
            #MP Ifdef SubstName_%sStructTag%n_%di {STR}
                #MP Setstr tolower = SubstName_%sStructTag%n_%di
            #MP Endif
            #mp%stoupper, #mp%stolower;
        #MP Endfor
    }
}
    #MP Endif ;GenDDdefs
    #MP Undef IsStdRecord
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
  #MP Ifdef GenDDdefs
    #MP If #0# >=4
        #MP tolower[{%n#4#}]
    #MP Else
        #MP tolower[{%n#2#}]
    #MP Endif
VARIABLE #mp%stolower
{
    #MP Ifdef DDLabel
    LABEL "#mp%sDDLabel";
        #MP Undef DDLabel
    #MP Endif
    #MP ddhelp
    #MP Ifdef DDClass
    CLASS #mp%sDDClass
        #MP Undef DDClass ;consumed, then undefined
    #MP Else
    CLASS CONTAINED
    #MP Endif
    #MP;
    ;
    #MP If (#3# & param_attrib_W)==0
    HANDLING READ;
    #MP Endif
    TYPE #mp%sddtype_%n#1#
    #MP If Defined(ddtype_details_%n#1#)
    #MP ;If Defined(typeattrib_%n#1#) ;&& (typeattrib_%n#1# == enum_attrib)
        #MP; looks same { #mp%n#1# }
        #mp%sddtype_details_%n#1#
    #MP Else
    ;
    #MP Endif
}
  #MP Endif
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
                                #MP
#MP ;DD Array type is a variable of type, not the type of the variable.
#MP ;We are remapping here from pre-defined
#MP Setstr ArrayTypeMap_u8_RW "uint_element"
#MP Setstr ArrayTypeMap_u8_R "uint_element_r"
#MP ;Expand as needed when the cases grow, and consider CLASS DYNAMIC
                                #MP
#MP Macro BeginArrayParam ;[type, name, dimension, access, dd_name.opt, dd_help.opt]
#MP If #0#>=5
    #MP ;Otherwise, not generating DD definition
    #MP tolower({%n#2#})

ARRAY #mp%stolower
{
    LABEL "#mp%s#5#";
    #MP If #0#>=6
#ifndef DD4
    HELP "#mp%s#6#";
#endif
    #MP Endif
    #MP Setstr T = ArrayTypeMap_%n#1#%n_%n#4#
    TYPE #mp%sT;
    NUMBER_OF_ELEMENTS #mp%d#3#;
}
#MP Endif
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


