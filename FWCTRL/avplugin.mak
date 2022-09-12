AV_PLUGIN_CMD = C:\McAfeeCMDScan\scan.exe $(MNS_OFFICIAL_DIR)\* /driver="$(ProgramFiles)\Common Files\McAfee\Engine" /all
define AV_PLUGIN
	echo Running Antivirus on the build output; see $(MNS_OFFICIAL_DIR)\av.log
	echo %DATE% %TIME% cmdline: $(AV_PLUGIN_CMD) > $(MNS_OFFICIAL_DIR)\av.log
	$(AV_PLUGIN_CMD) >> $(MNS_OFFICIAL_DIR)\av.log
endef
