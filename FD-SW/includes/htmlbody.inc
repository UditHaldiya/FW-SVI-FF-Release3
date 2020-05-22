#MP If 0 ;Tombstone header
A collection of macros to generate DD header
Currently, usable for parameter definitions
#MP Endif
#MP ;Include "ustd.inc"
#MP Include "gwtypes.inc"
#MP ;Include "paramstubs.inc"
#MP Save gwout
                                #MP
#MP Undef gwout {MAC}
#MP Macro gwout ;[param_name]
<br/>
<h2>
<a name = "param_#mp%ugwout">#mp%dgwout. #mp%s#1#</a>
</h2>
#MP gwout = gwout + 1

#MP; #mp%sgwout
#MP Endm
#MP
                                #MP
#MP Macro ddhelp ;takes a global DDHelp
HELP:
#MP Ifdef DDHelp {STR}
    #MP Ifdef DDHelp {NUM}
    (Not in DD ver. 4)
    #MP Endif
    #mp%sDDHelp<br>
    #MP Undef DDHelp {STR}
#MP Else
&lt;Unavailable&gt;<br>
#MP Endif
#MP Endm
                                #MP
#MP ;-------------------- attributes ---------------------
#MP Macro Attributes ;[attrib-bitmap]
Storage:
#MP If (#1# & param_attrib_SR) != 0
    #MP If (#1# & param_attrib_NV) != 0
        STATIC
    #MP Else
        Volatile
    #MP Endif
#MP Else
    #MP If (#1# & param_attrib_NV) != 0
        Non_Volatile
    #MP Else
        Dynamic
    #MP Endif
#MP Endif
#MP If (#1# & param_attrib_MN_A) != 0
<br>&nbsp;&nbsp;NOTE: Stored in APP. May not be used in FFP calculations unless transferred periodically.
#MP Endif
<br>
Access:
#MP If (#1# & param_attrib_W) != 0
    Writable
#MP Else
    Read-only
#MP Endif
<br>
#MP If (#1# & param_attrib_MN_DYN) != 0
&nbsp;&nbsp;NOTE: In Out-Of-Service mode, status is jammed to BAD/OOS.
<br>
#MP Endif
#MP Endm
                                #MP
#MP ;-------------------- instances for TOC ---------------------
#MP Undef NormalizeDDname {MAC}
#MP Macro NormalizeDDname ;[arg]
    #MP If !Isconst(#1#) ;Is it a name?
        #MP; var name
        #MP Ifdef #1# {STR} ;Is it a "foreign" name?
            #MP; defined
            #MP Setstr i=#1#
        #MP Else
            #MP; not defined
            #MP Setstr i={#1#}
        #MP Endif
    #MP Else
        #MP Setstr i=#1#
    #MP Endif
#MP Endm
                                #MP
#MP ;-------------------- bit enumerations ---------------------
#MP Macro bitreverse ;(bitnum, sizeof)
    #MP bitreverse = 1<<(#2#*8-1-#1#)
#MP Endm
                                #MP
#MP; Name must be distinctive, such as beginning with BENUM_
#MP Undef BeginBitEnumType {MAC}
#MP Macro BeginBitEnumType ;[basetype, name]
    #MP valcount = 0
    #MP Setstr typename = {%n#2#}
    #MP ;----------- Reference count: to account for orphaned types
    #MP Ifdef enums_count
        #MP enums_count = enums_count+1
    #MP Else
        #MP enums_count = 1
    #MP Endif
    #MP Setstr enum_typename_%denums_count = typename
    #MP enum_index_%stypename = enums_count
    #MP ;----------- End Reference count: to account for orphaned types
    #MP ddtypename_%n#2# = #1# ;size
    #MP tsizeof = #1# ;size, too (local)
    #MP Setstr typenote_%n#2# = "In firmware, bit order is reversed"
#MP Endm
                                #MP
#MP Undef BeginBitEnumType4 {MAC}
                #MP
#MP Undef BeginBitEnumType5 {MAC}
#MP Macro BeginBitEnumType5 ;[basetype, name]
        #MP BeginBitEnumType[[1:#0#]]
#MP Endm
                #MP
                                #MP
#MP Undef DefineBitEnumValue {MAC}
#MP Macro DefineBitEnumValue ;[name, value, dd-text.opt, dd-help.opt]
    #MP valcount = valcount+1
    #MP bitreverse[#2#, tsizeof]
    #MP Setstr enumval_%stypename%n_%dvalcount = {%n#1#}
    #MP enumval_%stypename%n_%dvalcount = #2#
    #MP If #0#>=3 ;otherwise, the definition is hidden from DD
        #MP Setstr enumtext_%stypename%n_%dvalcount = #3#
        #MP If #0#>=4
            #MP Setstr enumhelp_%stypename%n_%dvalcount = #4#
        #MP Endif
    #MP Else
        #MP Setstr enumtext_%stypename%n_%dvalcount = "NOTE: This enum value is hidden from DD"
    #MP Endif
    #MP Ifdef valnote
        #MP Setstr valnote_%stypename%n_%dvalcount = valnote
        #MP Undef valnote
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
                                #MP
#MP ;-------------------- enumerations ---------------------
#MP; Name must be distinctive, such as beginning with ENUM_
#MP Undef BeginEnumType {MAC}
#MP Macro BeginEnumType ;[basetype, name, ddname.opt]
    #MP valcount = 0
    #MP Setstr typename = {#2#}
    #MP ;----------- Reference count: to account for orphaned types
    #MP Ifdef enums_count
        #MP enums_count = enums_count+1
    #MP Else
        #MP enums_count = 1
    #MP Endif
    #MP Setstr enum_typename_%denums_count = typename
    #MP enum_index_%stypename = enums_count
    #MP ;----------- End Reference count: to account for orphaned types
    #MP Ifdef GenDDdefs
        #MP If (GenDDdefs & (1<<4)) == 0
            #MP Setstr typenote_%n#2# = "In DD ver. 4 appears as integer"
        #MP Endif
    #MP Else
        #MP Setstr typenote_%n#2# = "In DD appears as integer"
    #MP Endif
    #MP If #0#>=3
        #MP Setstr ddtypename_%n#2# = {%n#3#}
    #MP Else
        #MP Setstr ddtypename_%n#2# = typename
    #MP Endif
    #MP IsEnumType_%n#2# = 1 ;Just define it to distinguish from bit enumerations
    #MP ddtypename_%n#2# = #1# ;size
#MP Endm
                                #MP
                                #MP
#MP Undef BeginEnumType5 {MAC}
#MP Macro BeginEnumType5 ;[basetype, name, ddname.opt]
    #MP Ifdef GenDDdefs
		#MP Save GenDDdefs
        #MP GenDDdefs = (1<<5)
        #MP BeginEnumType[[1:#0#]]
		#MP Restore GenDDdefs
    #MP Endif
#MP Endm
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
    #MP Ifdef valnote
        #MP Setstr valnote_%stypename%n_%dvalcount = valnote
        #MP Undef valnote
    #MP Endif
#MP Endm
                                #MP
#MP Undef EndEnumType {MAC}
#MP Macro EndEnumType
    #MP valcount_%stypename = valcount
#MP Endm
                                #MP
#MP ;------------------- records ----------------------------
#MP Undef BeginStruct {MAC}
#MP Macro BeginStruct ;(tag)
    #MP Setstr StructTag {%n#1#}
    #MP RecordMemberCount = 0
#MP Endm
                                #MP
#MP Undef StructMember {MAC}
#MP Macro StructMember ;(type, name)
    #MP ;-------- Unmark member type as orphaned -------
    #MP Ifdef enum_index_%n#1#
        #MP enum_index = enum_index_%n#1#
        #MP Undef enum_index_%n#1#
        #MP Undef enum_typename_%denum_index
        #MP; debug: using-enum-#mp%n#1#-of-index-#mp%denum_index<br>
    #MP Endif
    #MP ;-------- End Unmark member type as orphaned -------
    #MP RecordMemberCount = RecordMemberCount + 1
    #MP ;For now, do not document types of standard variables, even if redefined
    #MP strcmp({uSubstr, {#1#}, 0, 2}, "__")
    #MP If strcmp < 0 ; not a standard
        #MP Setstr membertype_%sStructTag%n_%n#2# = {%n#1#}
        #MP membertype_%sStructTag%n_%n#2# = #1#
    #MP Endif
#MP Endm
                                #MP
                                #MP
#MP Undef StructMemberLike {MAC}
#MP Macro StructMemberLike ;(basetype, name, attrib_pair0, ...)
    #MP ;-------- Unmark member type as orphaned -------
    #MP Ifdef enum_index_%n#1#
        #MP enum_index = enum_index_%n#1#
        #MP Undef enum_index_%n#1#
        #MP Undef enum_typename_%denum_index
        #MP; debug: using-enum-#mp%n#1#-of-index-#mp%denum_index<br>
    #MP Endif
    #MP ;-------- End Unmark member type as orphaned -------
    #MP RecordMemberCount = RecordMemberCount + 1
    #MP Setstr basename_%sStructTag%n_%n#2# = {%n#1#}
    #MP For x=3, #0#
        #MP ;x is attrib, x+1 is a string value
        #MP Setstr AttribRedef_%sStructTag%n_%n#2#%n_%dx = {%n#x#}
        #MP y=x+1
        #MP Setstr AttribRedef_%sStructTag%n_%n#2#%n_%dy = #y#
        #MP x=y
    #MP Endfor
    #MP ;For now, do not document types of standard variables, even if redefined
    #MP strcmp({uSubstr, {#1#}, 0, 2}, "__")
    #MP If strcmp < 0 ; not a standard
        #MP Setstr membertype_%sStructTag%n_%n#2# = membertype_%sStructTag%n_%n#1#
        #MP membertype_%sStructTag%n_%n#2# = membertype_%sStructTag%n_%n#1#
    #MP Endif
#MP Endm
                                #MP
                                #MP
#MP Macro BeginRecordParam_Common ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Setstr StructTag = {%n#1#}
#MP If #0# > 5
    #MP ;Setstr i=#6#
    #MP NormalizeDDname[#6#]
#MP Else
    #MP Setstr i={#2#}
#MP Endif
#MP gwout[i]
#MP RecordMemberCount = 0
#MP Attributes[#3#]
#MP
#MP Endm

#MP Undef BeginRecordParam {MAC}
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP BeginRecordParam_Common[[1:#0#]]
<br>Type: Custom Record</br>
#MP Endm
                #MP
#MP Undef BeginStdRecordParam {MAC}
#MP Macro BeginStdRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Save type_prefix
#MP Setstr type_prefix = ""
#MP BeginRecordParam_Common[[1 : #0#]]
#MP Restore type_prefix
<br>Type: Standard Record #mp%n#1#. Variables:<br>
#MP Endm
                #MP
#MP Undef DefaultRecordParam {MAC}
#MP Macro DefaultRecordParam ;[eu_100, "100.0", 1]
#MP RecordMemberCount = RecordMemberCount + 1
<h3>Variable #mp%dRecordMemberCount. #mp%n#1#</h3>
    #MP Ifdef DDLabel
Descriptive Label: #mp%sDDLabel<br>
    #MP Endif
    #MP Undef DDLabel ;consumed, then undefined
    #MP Ifdef basename_%sStructTag%n_%n#1# ;redefinition of underlying variable
<br>
        #MP Setstr T = basename_%sStructTag%n_%n#1#
Same as #mp%sT except:
        #MP x=3
        #MP Repeat
            #MP Setstr T = AttribRedef_%sStructTag%n_%n#1#%n_%dx
            #MP x=x+1
            #MP Setstr S = AttribRedef_%sStructTag%n_%n#1#%n_%dx
<br>
#mp%sT = #mp%sS
        #MP x=x+1
        #MP While Defined(AttribRedef_%sStructTag%n_%n#1#%n_%dx)
<br>
    #MP Endif ;basename_%sStructTag%n_%n#1#
    #MP ddhelp
<br>
<span style="text-decoration: underline;">Type:</span>
    #MP If !Defined(basename_%sStructTag%n_%n#1#) ;not a redefinition
        #MP ;comment: We need to know the type of member variable by StructType and variable name.
        #MP Ifdef membertype_%sStructTag%n_%n#1#
            #MP Setstr qualified_type = membertype_%sStructTag%n_%n#1#
        #MP Else
            #MP Setstr qualified_type = "<font style=""background-color:#ccffff"" face=""Courier"">&lt;standard&gt;</font>"
        #MP Endif
        #MP Ifdef valcount_%squalified_type
            #MP ;This is enum or bit-enum type. #1# is the (internal) type name/size
            #MP Setstr membertype = membertype_%sStructTag%n_%n#1# ;typename_%n#1#
            #MP RenderEnum[qualified_type, Defined(IsEnumType_%smembertype), 0]
        #MP Else
            #MP ;Scalar or built-in type
            #mp%squalified_type
        #MP Endif
    #MP Endif
<br>
Firmware default #mp%s#2#<br>
    #MP If (#3# & SUBX_ACCESS) != 0
        #MP Setstr access = "Accessible"
    #MP Else
        #MP Setstr access = "Unaccessible"
    #MP Endif
#mp%saccess individually <br>
#MP Endm
                                #MP
                                #MP
#MP ;-------------------- simple parameters ---------------------
#MP Undef BeginSimpleParam_Common {MAC}
#MP Macro BeginSimpleParam_Common ;[type, name, access, dd_name.opt]
#MP If #0# > 3
    #MP NormalizeDDname[#4#]
#MP Else
    #MP Setstr i={#2#}
#MP Endif
#MP gwout[i]
#MP ddhelp
#MP Setstr qualified_type={#1#}
#MP Ifdef valcount_%squalified_type
    #MP ;This is enum or bit-enum type. #1# is the (internal) type name/size
    #MP RenderEnum[qualified_type, Defined(IsEnumType_%squalified_type), 0]
    #MP enum_index = enum_index_%stypename
    #MP Undef enum_typename_%denum_index; remove from orphans
#MP Else
    #MP ;Scalar or built-in type
    #MP ;#mp%squalified_type
Type: #mp%n#1#<br>
Size: #mp%d#1#<br>
#MP Endif
#MP Attributes[#3#]
#MP Endm
                #MP
#MP Undef BeginSimpleParam {MAC}
#MP Macro BeginSimpleParam ;[type, name, access, dd_name.opt]
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
                                #MP
#MP Undef BeginSimpleStdParam {MAC}
#MP Macro BeginSimpleStdParam ;[type, name, access, dd_name.opt]
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
                                #MP
#MP Undef DefaultSimpleParam {MAC}
#MP ;Relies on the call point being adjacent to call to BeginSimple(Std)Param
#MP Macro DefaultSimpleParam ;[value]
Firmware default #mp%s#1#
#MP Endm
                                #MP
                                #MP
#MP ;-------------------- array parameters ---------------------
#MP Undef BeginArrayParam {MAC}
#MP Macro BeginArrayParam ;[type, name, dimension, access]
#MP gwout[{#2#}]
Type: Array of #mp%d#3# elements of type #mp%n#1#<br>
Size of element: #mp%d#1#<br>
Dimension: #mp%d#3#<br>
#MP Attributes[#4#]
Firmware default:<br>
#MP Endm
                                #MP
#MP Undef DefaultArrayParams {MAC}
#MP Macro DefaultArrayParams ;[min_index, max_index, value]
For index range [#mp%d#1# - #mp%d#2#], #mp%s#3#
#MP Endm
                                #MP


#MP Macro RenderEnum ;[string:type, int:flag-of-enum(not bit_enum), int:flag-of orphaned]
    #MP ;This is enum or bit-enum type. #1# is the (internal) type name/size
    #MP If #3#
<h2>
    #MP Endif
    #MP size = ddtypename_%s#1#
    #MP If #2#
Enumeration
    #MP Else
Bit enumeration
    #MP Endif
    #MP If #3#
 type #mp%s#1#
</h2>
Size: #mp%dsize<br>
    #MP Else ;don't render type
(described below) of size #mp%dsize<br>
    #MP Endif
    #MP Ifdef typenote_%s#1#
NOTE: #mp%stypenote_%s#1#<br>
    #MP Endif
    #MP For valcount=1, valcount_%s#1#
        #MP Setstr v = enumval_%s#1#%n_%dvalcount
        #MP v = enumval_%s#1#%n_%dvalcount ;firmware value
<h4>
        #MP If #2# ;enum or bit enum?
#mp%sv = #mp%dv
        #MP Else
            #MP bitreverse[v, size]
#mp%sv
            #MP bitmap = 1<<v
            #MP If size == 1
bit #mp%dv: bitmap(DD)=0x#mp%02Xbitreverse bitmap(firmware)=0x#mp%02Xbitmap
            #MP Endif
            #MP If size == 2
bit #mp%dv: bitmap(DD)=0x#mp%04Xbitreverse bitmap(firmware)=0x#mp%04Xbitmap
            #MP Endif
            #MP If size == 4
bit #mp%dv: bitmap(DD)=0x#mp%08Xbitreverse bitmap(firmware)=0x#mp%08Xbitmap
            #MP Endif
        #MP Endif
</h4>
Descriptive Label: #mp%senumtext_%s#1#%n_%dvalcount
<br>
Help:
        #MP Ifdef enumhelp_%s#1#%n_%dvalcount
            #MP ;debug: Type: #mp%s#1# - value # #mp%dvalcount<br>
#mp%senumhelp_%s#1#%n_%dvalcount
        #MP Else
&lt;Not available; may be in DD or mapping table&gt;
        #MP Endif
<br>
        #MP Ifdef valnote_%s#1#%n_%dvalcount
#mp%svalnote_%s#1#%n_%dvalcount<br>
        #MP Endif
    #MP Endfor
<br>
#MP Endm

#MP Macro AllOrphans
#MP For index=1, enums_count
    #MP Ifdef enum_typename_%dindex
        #MP Setstr typename = enum_typename_%dindex
        #MP RenderEnum[typename, Defined(IsEnumType_%stypename), 1]
    #MP Else
        #MP ;debug type #mp%dindex is used
    #MP Endif
#MP Endfor
#MP Endm
