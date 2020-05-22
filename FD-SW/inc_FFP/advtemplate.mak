UTARGET : advtemplate.txt advmap.c
    @echo done with adv
    $(pause)

advtemplate.txt : ptbcustomsubx.h ..\target\appl\fbif\inc\fbif_idx.h
    $(Hide)echo ;Template for advanced accept/reject read/write configuration >$@
    $(Hide)echo ;[]-fields are mandatory>>$@
    $(Hide)echo ;The template lists and enables everything>>$@
    $(Hide)echo ;Comment out with a semicolon in column 1>>$@
    $(Hide)echo ;what you don't want in a specific named configuration>>$@
    $(Hide)echo [Diagnostics]>>$@
    $(Hide)$(MN_SED) -n -e s/.*\b\(DIAG_[_0-9A-Z]\+\).*/\1/gp $< >>$@
    $(Hide)echo [Read]>>$@
    $(Hide)$(MN_SED) -n -e s/.*\(REL_IDX_PTB_\)\([_0-9A-Z]\+\).*/\2/gp $(word 2, $^) >>$@
    $(Hide)echo [Write]>>$@
    $(Hide)$(MN_SED) -n -e s/.*\(REL_IDX_PTB_\)\([_0-9A-Z]\+\).*/\2/gp $(word 2, $^) >>$@
    $(Hide)echo [End]>>$@

advmap.c : ptbcustomsubx.h ..\target\appl\fbif\inc\fbif_idx.h
    $(Hide)echo //Generated automatically. Do not edit>$@
    $(Hide)echo #include ^<mnwrap.h^>>>$@
    $(Hide)echo #include ^<advmap.h^>>>$@
    $(Hide)echo #include ^<fbif_idx.h^>>>$@
    $(Hide)echo #include ^<ptbcustomsubx.h^>>>$@
    $(Hide)echo const char * const diagnames[] =>>$@
    $(Hide)echo {>>$@
    $(Hide)$(MN_SED) -n -e s/.*\b\(DIAG_[_0-9A-Z]\+\).*/"    "\[\1\]=\"\1\",/gp $< >>$@
    $(Hide)echo };>>$@
    $(Hide)echo const size_t diagnames_size = NELEM(diagnames);>>$@
    $(Hide)echo const char * const paramnames[] =>>$@
    $(Hide)echo {>>$@
    $(Hide)$(MN_SED) -n -e s/.*\(REL_IDX_PTB_\)\([_0-9A-Z]\+\).*/"    "\[\1\2\]=\"\2\",/gp $(word 2, $^) >>$@
    $(Hide)echo };>>$@
    $(Hide)echo const size_t paramnames_size = NELEM(paramnames);>>$@
    $(Hide)echo /* This line marks the end of the source */>>$@

