#MP If 0 ;Tombstone header
A collection of macros to generate DD header
Currently, usable for parameter definitions
#MP Endif
#MP Include "gwtypes.inc"
#MP Include "paramstubs.inc"
                                #MP
                                #MP
                                #MP
#MP Undef BeginChannels {MAC}
#MP Macro BeginChannels ;[basetype, name, ddname.opt]
    #MP Export Push
    #MP If #0# >= 3
        #MP Setstr outfile = {#3#}
    #MP Else
        #MP Setstr outfile = {#2#}
    #MP Endif
    #MP tolower[outfile]
    #MP Setstr outfile = tolower "fb.h"
    #MP Export (0) outfile
    #MP Save defchan
    #MP Undef defchan
    #MP Setstr out = "CHANNEL_INFORMATION"
#MP Endm
                                #MP
#MP Undef BeginChannels5 {MAC}
#MP Macro BeginChannels5 ;[basetype, name, ddname.opt]
    #MP BeginChannels[[1:#0#]]
#MP Endm
                                #MP
#MP Undef BeginChannels4 {MAC}
#MP Macro BeginChannels4 ;[basetype, name, ddname.opt]
    #MP If 0
--------->Got where shouldn't
#MP Endm
                                #MP
#MP Undef DefineChannel {MAC}
#MP Macro DefineChannel ;[name, value, dd-text, dd-help]
#MP Ifdef iochannel_number_%u#2#
    #MP If #2# != 0
#error "Channel #mp%siochannel_number_%u#2# already has number #mp%u#2#"
    #MP Endif
#MP Else
    #MP Setstr iochannel_number_%u#2# = {#1#}
#MP Endif
#define #mp%n#1# #mp%d#2#
    #MP Setstr out = out " {" {#1#} ",TB_POS}"
#MP Endm
                                #MP
#MP Undef DefineDefaultChannel {MAC}
#MP Macro DefineDefaultChannel ;[name, value, dd-text, dd-help]
    #MP Ifdef defchan
        #MP ;duplicate!
ERROR! duplicated default channel: was #mp%sdefchan, now #mp%s#1#
    #MP Else
        #MP Setstr defchan = {#1#}
    #MP Endif
    #MP DefineChannel[[1:#0#]]
#MP Endm
                                #MP
#MP Undef EndChannels {MAC}
#MP Macro EndChannels ;[]
#mp%sout
DEFAULT_CHANNEL #mp%sdefchan
    #MP Restore defchan
    #MP Export Pop
#MP Endm
                                #MP
#MP Undef EndChannels4 {MAC}
#MP Macro EndChannels4 ;()
    #MP Endif ;0
#MP Endm

