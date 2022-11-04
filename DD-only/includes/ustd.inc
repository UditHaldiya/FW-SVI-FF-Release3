#MP If 0 ;Tombstone header
/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ustd.inc
    \brief Standard Unimal macros

    CPU: Any

    OWNER: AK
    $Archive: /MNCB/Dev/FIRMWARE/includes/ustd.inc $
    $Date: 9/21/10 6:55p $
    $Revision: 8 $
    $Author: Arkkhasin $

    \ingroup HARTapp
*/
$History: ustd.inc $
 *
 * *****************  Version 8  *****************
 * User: Arkkhasin    Date: 9/21/10    Time: 6:55p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Added more proscribed characters to UnSpace macro. Added tombstone
 * header
#MP Endif

#MP If Defined( PROJPARAM_INC_ {STR})
#MP Include PROJPARAM_INC_
#MP Endif
#MP
#MP Macro basename ;(string)
#MP Setstr basename = {uSubstr, #1#, Ustrlen(#1#), 0} ;invert
#MP Setstr temp = {uSplit, basename, "."}
#MP If uSplit>=0
#MP     Setstr basename = {uSubstr, basename, basename, Ustrlen(basename)} ;chop extension off
#MP Endif
#MP Setstr basename = {uSplit, basename, "/", "\"} ;chop on directory
#MP If uSplit<0
#MP     basename = Ustrlen(basename)
#MP Endif
#MP Setstr basename = {uSubstr, basename, basename, 0} ;chop dir off and invert
#MP Endm
#MP
#MP digit_0 = 0
#MP digit_1 = 1
#MP digit_2 = 2
#MP digit_3 = 3
#MP digit_4 = 4
#MP digit_5 = 5
#MP digit_6 = 6
#MP digit_7 = 7
#MP digit_8 = 8
#MP digit_9 = 9
#MP xdigit_0 = 0
#MP xdigit_1 = 1
#MP xdigit_2 = 2
#MP xdigit_3 = 3
#MP xdigit_4 = 4
#MP xdigit_5 = 5
#MP xdigit_6 = 6
#MP xdigit_7 = 7
#MP xdigit_8 = 8
#MP xdigit_9 = 9
#MP xdigit_a = 10
#MP xdigit_A = 10
#MP xdigit_b = 11
#MP xdigit_B = 11
#MP xdigit_c = 12
#MP xdigit_C = 12
#MP xdigit_d = 13
#MP xdigit_D = 13
#MP xdigit_e = 14
#MP xdigit_E = 14
#MP xdigit_f = 15
#MP xdigit_F = 15
#MP ;Missing definitions
#MP Setstr ascii_space = " "
#MP ascii_%sascii_space = 0x20
#MP Setstr ascii_exclamation_point = "!"
#MP ascii_%sascii_exclamation_point = 0x21
#MP Setstr ascii_quote = #@"#
#MP ascii_%sascii_quote = 0x22
#MP Setstr ascii_sharp = "#"
#MP ascii_%sascii_sharp = 0x23
#MP Setstr ascii_dollar = "$"
#MP ascii_%sascii_dollar = 0x24
#MP Setstr ascii_percent = "%"
#MP ascii_%sascii_percent = 0x25
#MP Setstr ascii_ampersand = "&"
#MP ascii_%sascii_ampersand = 0x26
#MP Setstr ascii_apostrophe = "'"
#MP ascii_%sascii_apostrophe = 0x27
#MP Setstr ascii_lparen = "("
#MP ascii_%sascii_lparen = 0x28
#MP Setstr ascii_rparen = ")"
#MP ascii_%sascii_rparen = 0x29
#MP Setstr ascii_asterisk = "*"
#MP ascii_%sascii_asterisk = 0x2A
#MP Setstr ascii_plus = "+"
#MP ascii_%sascii_plus = 0x2B
#MP Setstr ascii_comma = ","
#MP ascii_%sascii_comma = 0x2C
#MP Setstr ascii_minus = "-"
#MP ascii_%sascii_minus = 0x2D
#MP Setstr ascii_dot = "."
#MP ascii_%sascii_dot = 0x2E
#MP Setstr ascii_forward_slash = "/"
#MP ascii_%sascii_forward_slash = 0x2F
#MP ascii_0 = 0x30
#MP ascii_1 = 0x31
#MP ascii_2 = 0x32
#MP ascii_3 = 0x33
#MP ascii_4 = 0x34
#MP ascii_5 = 0x35
#MP ascii_6 = 0x36
#MP ascii_7 = 0x37
#MP ascii_8 = 0x38
#MP ascii_9 = 0x39
#MP Setstr ascii_colon = ":"
#MP ascii_%sascii_colon = 0x3A
#MP Setstr ascii_semicolon = ";"
#MP ascii_%sascii_semicolon = 0x3B
#MP Setstr ascii_lessthan = "<"
#MP ascii_%sascii_lessthan = 0x3C
#MP Setstr ascii_equal = "="
#MP ascii_%sascii_equal = 0x3D
#MP Setstr ascii_greaterthan = ">"
#MP ascii_%sascii_greaterthan = 0x3E
#MP Setstr ascii_questionmark = "?"
#MP ascii_%sascii_questionmark = 0x3F
#MP Setstr ascii_at = "@"
#MP ascii_%sascii_at = 0x40
#MP ascii_A = 0x41
#MP ascii_B = 0x42
#MP ascii_C = 0x43
#MP ascii_D = 0x44
#MP ascii_E = 0x45
#MP ascii_F = 0x46
#MP ascii_G = 0x47
#MP ascii_H = 0x48
#MP ascii_I = 0x49
#MP ascii_J = 0x4A
#MP ascii_K = 0x4B
#MP ascii_L = 0x4C
#MP ascii_M = 0x4D
#MP ascii_N = 0x4E
#MP ascii_O = 0x4F
#MP ascii_P = 0x50
#MP ascii_Q = 0x51
#MP ascii_R = 0x52
#MP ascii_S = 0x53
#MP ascii_T = 0x54
#MP ascii_U = 0x55
#MP ascii_V = 0x56
#MP ascii_W = 0x57
#MP ascii_X = 0x58
#MP ascii_Y = 0x59
#MP ascii_Z = 0x5A
#MP Setstr ascii_lbracket = "["
#MP ascii_%sascii_lbracket = 0x5B
#MP Setstr ascii_backslash = "\"
#MP ascii_%sascii_backslash = 0x5C
#MP Setstr ascii_rbracket = "]"
#MP ascii_%sascii_rbracket = 0x5D
#MP Setstr ascii_caret = "^"
#MP ascii_%sascii_caret = 0x5E
#MP ascii__ = 0x5F
#MP Setstr ascii_backtick = "`"
#MP ascii_%sascii_backtick = 0x60
#MP ascii_a = 0x61
#MP ascii_b = 0x62
#MP ascii_c = 0x63
#MP ascii_d = 0x64
#MP ascii_e = 0x65
#MP ascii_f = 0x66
#MP ascii_g = 0x67
#MP ascii_h = 0x68
#MP ascii_i = 0x69
#MP ascii_j = 0x6A
#MP ascii_k = 0x6B
#MP ascii_l = 0x6C
#MP ascii_m = 0x6D
#MP ascii_n = 0x6E
#MP ascii_o = 0x6F
#MP ascii_p = 0x70
#MP ascii_q = 0x71
#MP ascii_r = 0x72
#MP ascii_s = 0x73
#MP ascii_t = 0x74
#MP ascii_u = 0x75
#MP ascii_v = 0x76
#MP ascii_w = 0x77
#MP ascii_x = 0x78
#MP ascii_y = 0x79
#MP ascii_z = 0x7A
#MP Setstr ascii_lbrace = "{"
#MP ascii_%sascii_lbrace = 0x7B
#MP Setstr ascii_vertbar = "|"
#MP ascii_%sascii_vertbar = 0x7C
#MP Setstr ascii_rbrace = "}"
#MP ascii_%sascii_rbrace = 0x7D
#MP Setstr ascii_tilde = "~"
#MP ascii_%sascii_tilde = 0x7E

#MP
#MP Macro str2num ;(string)
#MP result = 0
#MP For n=0,Ustrlen(#1#) - 1
#MP Setstr digit_string = {uSubstr, #1#, n, n+1}
#MP result = 16*result + xdigit_%sdigit_string
#MP Endfor
#MP Undef n {NUM} ;cleanup
#MP Undef digit_string{STR} ;cleanup
#MP Endm
#MP
#MP Macro atoi ;(string)
    #MP #1#=0
    #MP Save i
    #MP For i=0, Ustrlen(#1#)-1
        #MP Setstr temp = {uSubstr, #1#, i, i+1}
        #MP #1# = #1#*10 + digit_%stemp
    #MP Endfor
    #MP Restore i
#MP Endm
#MP
#MP Macro str2hex ;(string)
#MP result = 0
#MP For n=0,Ustrlen(#1#) - 1
#MP Setstr digit_string = {uSubstr, #1#, n, n+1}
#MP If ((result<<4)>>4) != result ;(1)
#MP Error “result overflow” ;(2)
#MP Endif ;(3)
#MP result = (result<<4) | xdigit_%sdigit_string ;(4)
#MP Endfor
#MP Undef n {NUM} ;cleanup
#MP Undef digit_string{STR} ;cleanup
#MP Endm
#MP
#MP Setstr toupper_a = "A"
#MP Setstr toupper_b = "B"
#MP Setstr toupper_c = "C"
#MP Setstr toupper_d = "D"
#MP Setstr toupper_e = "E"
#MP Setstr toupper_f = "F"
#MP Setstr toupper_g = "G"
#MP Setstr toupper_h = "H"
#MP Setstr toupper_i = "I"
#MP Setstr toupper_j = "J"
#MP Setstr toupper_k = "K"
#MP Setstr toupper_l = "L"
#MP Setstr toupper_m = "M"
#MP Setstr toupper_n = "N"
#MP Setstr toupper_o = "O"
#MP Setstr toupper_p = "P"
#MP Setstr toupper_q = "Q"
#MP Setstr toupper_r = "R"
#MP Setstr toupper_s = "S"
#MP Setstr toupper_t = "T"
#MP Setstr toupper_u = "U"
#MP Setstr toupper_v = "V"
#MP Setstr toupper_w = "W"
#MP Setstr toupper_x = "X"
#MP Setstr toupper_y = "Y"
#MP Setstr toupper_z = "Z"
#MP
#MP Macro toupper ;(string)
#MP Setstr toupper = ""
#MP For n=0,Ustrlen(#1#) - 1
#MP Setstr letter_string = {uSubstr, #1#, n, n+1}
#MP Ifdef toupper_%sletter_string {STR} ;(1)
#MP Setstr letter_string = toupper_%sletter_string ;(2)
#MP Endif
#MP Setstr toupper = {uJoin, toupper, letter_string} ;(3)
#MP Endfor
#MP Undef letter_string{STR} ;cleanup
#MP Endm
#MP
#MP Setstr tolower_A = "a"
#MP Setstr tolower_B = "b"
#MP Setstr tolower_C = "c"
#MP Setstr tolower_D = "d"
#MP Setstr tolower_E = "e"
#MP Setstr tolower_F = "f"
#MP Setstr tolower_G = "g"
#MP Setstr tolower_H = "h"
#MP Setstr tolower_I = "i"
#MP Setstr tolower_J = "j"
#MP Setstr tolower_K = "k"
#MP Setstr tolower_L = "l"
#MP Setstr tolower_M = "m"
#MP Setstr tolower_N = "n"
#MP Setstr tolower_O = "o"
#MP Setstr tolower_P = "p"
#MP Setstr tolower_Q = "q"
#MP Setstr tolower_R = "r"
#MP Setstr tolower_S = "s"
#MP Setstr tolower_T = "t"
#MP Setstr tolower_U = "u"
#MP Setstr tolower_V = "v"
#MP Setstr tolower_W = "w"
#MP Setstr tolower_X = "x"
#MP Setstr tolower_Y = "y"
#MP Setstr tolower_Z = "z"
#MP
#MP Macro tolower ;(string)
#MP Setstr tolower = ""
#MP For n=0,Ustrlen(#1#) - 1
#MP Setstr letter_string = {uSubstr, #1#, n, n+1}
#MP Ifdef tolower_%sletter_string {STR} ;(1)
#MP Setstr letter_string = tolower_%sletter_string ;(2)
#MP Endif
#MP Setstr tolower = {uJoin, tolower, letter_string} ;(3)
#MP Endfor
#MP Undef letter_string{STR} ;cleanup
#MP Endm
#MP
#MP ;A macro to output a dummy file required by a convention
#MP Macro dummy ;(string extension)
#MP Export Push
#MP Save dummy
#MP Save uJoin
#MP Setstr uJoin=""
#MP Setstr dummy = {uJoin, basename, #1#}
#MP Export (0) dummy
/*
#mp%sdummy is worthless; its sole purpose is to keep IAR IDE happy.
Do not use it.
*/
#MP Restore dummy
#MP Restore uJoin
#MP Export Pop
#MP Endm
#MP
#MP
#MP ;These are commonly used so they run right here
#MP If Defined (basename {STR})
#MP     basename(basename)
#MP     toupper(basename)
#MP Endif
#MP
#MP
#MP ;========= useful general-purpose macros ======================
#MP ;Compare 1st string with any number of other strings.
#MP ;strcmp=2-based index of a matching string or negative if no match
#MP Macro strcmp ;[1st-string, string2, string3, ..., stringN]
#MP Save uSplit
#MP Setstr strcmp = {uSplit, [1:#0#]}
#MP strcmp = uSplit
#MP If strcmp >= 0
#MP     strcmp = strcmp+2
#MP     If Ustrlen(#1#) != Ustrlen(#strcmp#)
#MP         strcmp = -1
#MP     Endif
#MP Endif
#MP Restore uSplit
#MP Endm
#MP
#MP ;Remove/replaces spaces and other proscribed characters from a string. UnSpace contains the resulting string
#MP Macro UnSpace ;(string, replace.opt)
#MP Save src
#MP Save replace
#MP If #0# < 2
#MP     Setstr replace = ""
#MP Else
#MP     Setstr replace = #2#
#MP Endif
#MP Setstr UnSpace = ""
#MP Setstr src = #1#
#MP Space2_Internal[src, UnSpace]
#MP Setstr UnSpace = {uSubstr, UnSpace, Ustrlen(replace), Ustrlen(UnSpace)}
#MP Restore src
#MP Restore replace
#MP Endm
#MP ;       A helper for UnSpace
#MP ;Extract one word from one string to another
#MP Macro Space2_Internal ;(src, dst)
#MP Setstr t = {uSplit, #1#, " ", "'", #@"#, "%", "&", "-", "+", "(", ")", "/", "\", "{", "}", "[", "]"} ;add proscribed symbols as needed
#MP If uSplit < 0 ;no spaces
#MP     Setstr #2# = #2# replace #1#
#MP Else
#MP     Setstr #2# = #2# replace {uSubstr, #1#, 0, #1#-1}
#MP     Setstr #1# = {uSubstr, #1#, #1#, Ustrlen(#1#)}
#MP     Space2_Internal[#1#, #2#]
#MP Endif
#MP Endm
#MP
#MP ;Crash and exit immediately after printing supplied text
#MP Macro Fatal ;[Text]
#mp%s#1#
Exiting with bogus error!
#MP Export (0) "" ;same to stdout
#mp%s#1#
Exiting with bogus error!
#MP Include ":" ;guaranteed failure
#MP Endm
#MP
#MP
#MP Macro condex ;(macro-name, params)
#MP If !Isconst(#1#)
#MP     If Defined( #1# {MAC} )
#MP         #1#([2:#0#])
#MP     Endif
#MP Endif
#MP Endm
#MP
