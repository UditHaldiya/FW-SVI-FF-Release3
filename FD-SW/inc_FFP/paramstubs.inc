#MP If 0 ;Tombstone header
/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ptbcustomsubx.u
    \brief Stubs for unused macros.

    If you need a macro foo in your code, precede the definition
    with #MP Undef foo {MAC}

    CPU: Any

    OWNER: AK

*/
#MP Endif ;Tombstone header
                #MP
#MP Macro gwout
#MP Endm
                #MP
#MP Macro DDcolbreak
#MP Endm
#MP Macro DDrowbreak
#MP Endm
                #MP
#MP Macro BeginStruct ;(tag)
#MP Endm
                #MP
#MP Macro StructMember ;(type, name)
#MP Endm
                #MP
                #MP
#MP Macro StructMemberLike ;(basetype, type, attrib0, attrib_text0, ...)
#MP Endm
                #MP
#MP Macro EndStruct ;(old_style.opt)
#MP Endm
                #MP
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Endm
#MP Macro DefaultRecordParam ;(member_name, default_value, subx_access, dd_name.opt)
#MP Endm
#MP Macro DefaultStdRecordParam ;(member_name, default_value, subx_access, dd_name.opt)
#MP DefaultRecordParam([1:#0#])
#MP Endm
#MP Macro EndRecordParam ;()
#MP Endm
                #MP
#MP Macro BeginSimpleParam ;[type, name, access, dd_name.opt]
#MP Endm
#MP Macro DefaultSimpleParam ;[value]
#MP Endm
#MP Macro EndSimpleParam ;[type, name, access]
#MP Endm
                #MP
#MP Macro BeginArrayParam ;[type, name, dimension, access]
#MP Endm
#MP Macro DefaultArrayParams ;[min_index, max_index, value]
#MP Endm
#MP Macro EndArrayParam
#MP Endm
                #MP
#MP Macro BeginStdRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Endm
                #MP
#MP Macro BeginSimpleStdParam ;[type, name, access, dd_name.opt]
#MP Endm
                #MP
                #MP
#MP; Name must be distinctive, such as beginning with ENUM_
#MP Macro BeginEnumType ;[basetype, name]
#MP Setstr ddtype_%n#2# = "ENUMERATED(" {%d#1#} ")"
#MP Setstr #2# = #1#
#MP #2# = #1#
#MP Endm
                #MP
#MP; Name must be distinctive, such as beginning with ENUM_
#MP Macro BeginEnumType5 ;[basetype, name]
#MP BeginEnumType[[1:#0#]]
#MP Endm
                #MP
                #MP


#MP Macro BeginEnumType4 ;[basetype, name]
    #MP If 0
#MP Endm
                #MP
#MP Macro DefineEnumValue ;[name, value, dd-text, dd-help.opt, dd-help-prefix.opt, dd-help-suffix.opt ]
#MP Endm
                #MP
#MP Macro EndEnumType
#MP Endm
#MP Macro EndEnumType4
    #MP Endif
#MP Endm
                #MP
                #MP
#MP; Name must be distinctive, such as beginning with BENUM_
#MP Macro BeginBitEnumType ;[basetype, name]
#MP Setstr ddtype_%n#2# = "ENUMERATED(" {%d#1#} ")"
#MP Setstr #2# = #1#
#MP #2# = #1#
#MP Endm
                #MP
#MP Macro BeginBitEnumType5 ;[basetype, name]
#MP BeginEnumType5[[1:#0#]]
#MP Endm
                #MP
                #MP
#MP Macro BeginBitEnumType4 ;[basetype, name]
    #MP If 0
#MP Endm
                #MP
#MP Macro DefineBitEnumValue ;[name, value, dd-text]
#MP Endm
                #MP
#MP Macro EndBitEnumType
#MP Endm
#MP Macro EndBitEnumType4
    #MP Endif
#MP Endm
                #MP
#MP ;-------------------- channels ----------------------
#MP ;Except block definitions, channels look like enums of size 2, so they are defaults
#MP Macro BeginChannels ;[basetype, name, ddname.opt]
    #MP BeginEnumType[u16, [1:#0#]]
#MP Endm
#MP Macro BeginChannels5 ;[basetype, name, ddname.opt]
    #MP BeginEnumType5[u16, [1:#0#]]
#MP Endm
#MP Macro BeginChannels4 ;[basetype, name, ddname.opt]
    #MP BeginEnumType[u16, [1:#0#]]
#MP Endm
#MP Macro DefineChannel ;[name, value, dd-text, dd-help]
    #MP DefineEnumValue[[1:#0#]]
#MP Endm
#MP Macro DefineDefaultChannel ;[name, value, dd-text, dd-help]
    #MP DefineChannel[[1:#0#]]
#MP Endm
#MP Macro EndChannels ;[]
    #MP EndEnumType
#MP Endm
#MP Macro EndChannels4 ;()
    #MP EndEnumType()
#MP Endm
                #MP
#MP ;-------------------- Diagnostic commands ----------------------
#MP ;Except Advanced parameter checks, Diagnostic commands look like enums of size 1, so they are defaults
#MP Macro BeginAdvDiags ;[basetype, name, ddname.opt]
    #MP BeginEnumType[u8, [1:#0#]]
#MP Endm
#MP Macro BeginAdvDiags4 ;[basetype, name, ddname.opt]
    #MP BeginEnumType[u8, [1:#0#]]
#MP Endm
#MP Macro DefineAdvDiag ;[lock_bitnum, name, value, dd-text, dd-help]
    #MP DefineEnumValue[[2:#0#]]
#MP Endm
#MP Macro DefineDefaultAdvDiag ;[lock_bitnum, name, value, dd-text, dd-help]
    #MP DefineAdvDiag[[1:#0#]]
#MP Endm
#MP Macro EndAdvDiags ;[]
    #MP EndEnumType
#MP Endm
#MP Macro EndAdvDiags4 ;()
    #MP EndEnumType()
#MP Endm

