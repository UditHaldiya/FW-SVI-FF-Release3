#MP If 0 ;Tombstone header
A collection of macros to generate DD header
Currently, usable for parameter definitions
#MP Endif
#MP Include "gwtypes.inc"
#MP Include "paramstubs.inc"
#MP Save gwout
                                #MP
#MP Undef gwout {MAC}
#MP Macro gwout ;[param_name]
<a href = "#param_#mp%ugwout">#mp%dgwout. #mp%s#1#</a>
<br/>
#MP gwout = gwout + 1

#MP; #mp%sgwout
#MP Endm
#MP

#MP ;-------------------- instances for TOC ---------------------

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

#MP Undef BeginRecordParam {MAC}
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP If #0# > 5
    #MP ;Setstr i=#6#
    #MP NormalizeDDname[#6#]
#MP Else
    #MP Setstr i={#2#}
#MP Endif
#MP gwout[i]
#MP Endm
                #MP
#MP Undef BeginStdRecordParam {MAC}
#MP Macro BeginStdRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Save type_prefix
#MP Setstr type_prefix = ""
#MP BeginRecordParam[[1 : #0#]]
#MP Restore type_prefix
#MP Endm
                #MP
#MP Macro BeginSimpleParam_Common ;[type, name, access, dd_name.opt]
#MP If #0# > 3
    #MP NormalizeDDname[#4#]
#MP Else
    #MP Setstr i={#2#}
#MP Endif
#MP gwout[i]
#MP Endm
                #MP
#MP Undef BeginSimpleParam {MAC}
#MP Macro BeginSimpleParam ;[type, name, access, dd_name.opt]
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
#MP Undef BeginSimpleStdParam {MAC}
#MP Macro BeginSimpleStdParam ;[type, name, access, dd_name.opt]
#MP BeginSimpleParam_Common[[1:#0#]]
#MP Endm
                #MP
#MP Undef BeginArrayParam {MAC}
#MP Macro BeginArrayParam ;[type, name, dimension, access]
#MP gwout[{#2#}]
#MP Endm


