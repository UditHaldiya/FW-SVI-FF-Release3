#MP If 0 ;Tombstone header
A collection of macros to generate log file definitions from PTB parameters
#MP Endif
#MP Include "gwtypes.inc"
#MP Include "paramstubs.inc"
                                #MP
                                #MP
#MP ;--------------- instances ------------------
                                #MP
#MP Macro nvstorage
#MP If (#3# & param_attrib_MN_N) == 0
		#MP Setstr T "0U"
#MP Else
		#MP Setstr T = "TB_STORAGE_FFP"
#MP Endif
#MP If (#3# & param_attrib_MN_A) != 0
		#MP Setstr T = T " | TB_STORAGE_APP"
#MP Endif
#MP Setstr nvstorage__%dgwout = T
#MP toupper({%n#2#})
#MP Setstr nvstorage_index__%dgwout = toupper
#MP If !Defined(gwout_start)
	#MP gwout_start = gwout
#MP Endif
#MP gwout = gwout + 1
#MP Endm
                                #MP
#MP ;This macro assumes string addrof prepared by caller
#MP Macro RecordArrayCommon ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP toupper({%n#2#})
#MP tolower({%n#2#})
#MP     Setstr mnid = "MN_NV_" {%n#2#}
#MP     Setstr mntype = mnid "_t"
#MP     Setstr mnget = mnid "_Get"
#MP     Setstr mnset = mnid "_Set"
#MP     ;Header info
#MP     Export Push
#MP     Export (1) out_h
typedef struct #mp%smntype
{
    u8 #mp%n#2# [elemsize(T_FBIF_PTB, #mp%stolower)];
    u16 CheckWord;
} #mp%smntype;
extern const void *#mp%smnget(void *dst);
extern ErrorCode_t #mp%smnset(const void *src);

#MP     Export Pop
#MP     ;Common C implementation
#MP     Export Push
#MP     Export (1) out_c
/** \brief "Clever" copying get function for #mp%n#2#
Requires dst!=NULL, or will return NULL as indication of an error
Creates a valid checksum
\param dst - a pointer to a destination buffer
\return dst
*/
const void *#mp%smnget(void *dst)
{
    #mp%smntype *buf = dst;
    if(dst != NULL)
    {
        MN_ENTER_CRITICAL();
            mn_memcpy(dst, #mp{%s addrof}ptb_1.#mp%stolower, sizeof(buf->#mp%n#2#));
            STRUCT_CLOSE(#mp%smntype, buf);
        MN_EXIT_CRITICAL();
    }
    return dst;
}
/** \brief Basic copying set function for #mp%n#2#
As of now, no application-level data check, nor saving to NVMEM.
The latter is routed via mn_fbs_write_param{_loc}
\param src - source of data (NULL means default as usual)
\return an error code (currently, always ERR_OK)
*/
ErrorCode_t #mp%smnset(const void *src)
{
    if(src == NULL)
    {
        src = #mp{%s addrof}c_ptb.#mp%stolower;
    }
    const #mp%smntype *buf = src; //lint !e826 Lint sees type mismatch which is here intentional
    MN_ENTER_CRITICAL();
        mn_memcpy(#mp{%s addrof}ptb_1.#mp%stolower, buf->#mp%n#2#, sizeof(buf->#mp%n#2#));
    MN_EXIT_CRITICAL();
    return ERR_OK;
}

#MP     Export Pop
#MP     ;NVRAM entry defintion info
#MP     Export Push
#MP     Export (1) out_inc
#MP     Setstr nvstring = "#MP    nvram_Entry[" mnid ", " mnset ", " mnget #@, Vol0, "# nvflags #@"]#
#mp%snvstring
#MP     Export Pop
#MP     ;Map of REL_IDX to log file
#MP Setstr nvmapstring = nvmapstring splitstr "    [REL_IDX_PTB_" toupper "] = {.nvramid = NVRAMID_" mnid ",},"
                                #MP
#MP Endm
                                #MP
#MP Undef BeginRecordParam {MAC}
#MP Macro BeginRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP doit = #3# & param_attrib_MN_F
#MP If doit != 0
#MP     ;Header info
#MP     ;Log file defintion info
#MP     ;Map of REL_IDX to log file
#MP Endif
#MP doit = #3# & param_attrib_MN_N
#MP If doit != 0
#MP     Setstr addrof = "&"
#MP     If (#3# & param_attrib_MN_NoRestore) != 0
#MP         Setstr nvflags = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2"
#MP     Else
#MP         Setstr nvflags = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2|NVMFLAG_RESTORED"
#MP     Endif
#MP     RecordArrayCommon[[1 : #0#]]
#MP Endif
#MP nvstorage[[1 : #0#]]
#MP Endm
                                #MP
                                #MP
#MP Undef BeginStdRecordParam {MAC}
#MP Macro BeginStdRecordParam ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP BeginRecordParam[[1 : #0#]]
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
#MP doit = #3# & param_attrib_MN_N
#MP If doit != 0
#MP     Setstr addrof = "&"
#MP     If (#3# & param_attrib_MN_NoRestore) != 0
#MP         Setstr nvflags = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2"
#MP     Else
#MP         Setstr nvflags = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2|NVMFLAG_RESTORED"
#MP     Endif
#MP     RecordArrayCommon[[1:3]] ;(type, name, attrib, dd_label, dd_help, dd_name.opt)
#MP Endif
#MP nvstorage[[1 : #0#]]
#MP Endm
                                #MP
                                #MP
#MP Undef BeginArrayParam {MAC}
#MP Macro BeginArrayParam ;[type, name, dimension, access]
#MP doit = #4# & param_attrib_MN_F
#MP If doit != 0
#MP     ;Header info
#MP     ;Log file defintion info
#MP     ;Map of REL_IDX to log file
#MP Endif
#MP doit = #4# & param_attrib_MN_N
#MP If doit != 0
#MP     Setstr addrof = ""
#MP     If (#4# & param_attrib_MN_NoRestore) != 0
#MP         Setstr nvflags = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2"
#MP     Else
#MP         Setstr nvflags = "NVMFLAG_DEFAULT_RECOVER|NVMFLAG_INIT_2|NVMFLAG_RESTORED"
#MP     Endif
#MP     RecordArrayCommon[[1:#0#]]
#MP Endif
#MP nvstorage[[1 : #0#]]
#MP Endm


