include $(src)
opt:=$(filter FEATUREOPT_%, $(.VARIABLES))
feat:=$(filter FEATURE_%, $(.VARIABLES))
uparamfiles:=$(filter %_U_PARAM, $(.VARIABLES))
hparamfiles:=$(filter %_H_PARAM, $(.VARIABLES))
uhparams:= $(subst _U_PARAM,_H_PARAM,$(uparamfiles))

.PHONY: projf allf $(feat) $(opt) $(uparamfiles)  $(hparamfiles)

allf : $(opt)

$(opt) :
    $(Hide)FOR %%x IN ($($@)) DO $(MN_ECHO) "#MP Expand DefineFeatureOption( $(subst FEATUREOPT_,,$@), %%x )" >> $(dst)

projf : $(feat)

$(feat) :
    $(Hide)$(MN_ECHO) "#MP SelectProjectFeature( $(subst FEATURE_,,$@), $($@) )" >>$(dst)

hparam : $(hparamfiles) $(uhparams)
    @echo HPARAM=$(hparamfiles)

$(hparamfiles) :
    $(Hide)$(MN_ECHO) "#define $(subst _H_PARAM,_H_,$@) \"$($@)\"" >>$(dst)

$(uhparams) :
    $(Hide)$(MN_ECHO) "#define $(subst _H_PARAM,_H_,$@) \"$($(@:_H_PARAM=_U_PARAM):.inc=.h)\"" >>$(dst)

uparam : $(uparamfiles)
    @echo UPARAM=$(uparamfiles)

$(uparamfiles) :
    $(Hide)$(MN_ECHO) "#MP Setstr $(subst _U_PARAM,_INC_,$@) = \"$($@)\"" >>$(dst)
