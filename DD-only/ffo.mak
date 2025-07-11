.PHONY: $(pretok)

FFTokenizerpath:=$(TokenizerBin)\tok\bin
dictfile:=$(TokenizerDir)\ddl\standard.dct
imagepath:=$(DDLDIR)\Photos
#Warining we need to suppress in tokenizer
SuppressWarning:=718 768

_tok: $(pretok)
    $(FFTokenizerpath)\$(tok_exe) -s $(releasepath) $(pretok)
ifneq ($(filter -DDD4,$(option)),)
    $(MN_CP) $(basename).ffo $(dst)/
    $(MN_CP) $(basename).sym $(dst)/
else
    $(MN_CP) $(basename).ff5 $(dst)/
    $(MN_CP) $(basename).sy5 $(dst)/
endif

$(pretok) : $(DDLSRC)
    @echo option=$(option)
    $(FFTokenizerpath)\$(pretok_exe) $(option) -d $(dictfile) $(addprefix -w , $(SuppressWarning)) -I$(includepath) -Iinc_$(PROJ) -R $(releasepath) -p "$(imagepath)" $< $@
	$(pause)

#    $(FFTokenizerpath)\$(pretok_exe) $(option) -d $(dictfile) $(addprefix -w , $(SuppressWarning)) -I$(includepath) -R $(releasepath) -p "$(imagepath)" $< $@
