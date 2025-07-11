#MP ; ------- This is an add-on for RB; temporarily (?) here ------
#MP Setstr fd_1 = "|en|Transducer Block does not work properly"
#MP Setstr help_fd_1 = fd_1
		#MP
#MP Setstr fd_2 = "|en|Valve Control Alert"
#MP Setstr help_fd_2 = "|en|May be Actuator or Air Supply"
#MP Setstr fd_3 = "|en|Hardware"
#MP Setstr help_fd_3 = "|en|May be Processor or Hardware Alert"
#MP Setstr fd_4 = "|en|Environment"
#MP Setstr help_fd_4 = "|en|May be Commissioning or Sensor Fsilure Alert"
#MP Setstr fd_5 = "|en|IP Drive Current Excursion"
#MP Setstr help_fd_5 = "|en|May be HI or LO Alert"
#MP Setstr fd_6 = "|en|Temperature Excursion"
#MP Setstr help_fd_6 = "|en|May be HI or LO Alert"
	#MP ;Setstr fd_7 = "|en|Cond06"
	#MP ;Setstr help_fd_7 = fd_7
#MP Setstr fd_8 = "|en|Supply Pressure LoLo Alert"
#MP Setstr help_fd_8 = fd_8
#MP Setstr fd_9 = "|en|Supply Pressure Excursion"
#MP Setstr help_fd_9 = "|en|May be HI or LO Alert"
	#MP ;Setstr fd_10 = "|en|Cond09"
	#MP ;Setstr help_fd_10 = fd_10
#MP Setstr fd_11 = "|en|Working time Alert"
#MP Setstr help_fd_11 = fd_11
#MP Setstr fd_12 = "|en|Travel B Alert"
#MP Setstr help_fd_12 = "|en|May be Travel accumulation or Cycle Counter"
	#MP ;Setstr fd_13 = "|en|Cond12"
	#MP ;Setstr help_fd_13 = fd_13
	#MP ;Setstr fd_14 = "|en|Cond13"
	#MP ;Setstr help_fd_14 = fd_14
#MP Setstr fd_15 = "|en|Travel A Alert"
#MP Setstr help_fd_15 = "|en|May be Travel accumulation or Cycle Counter"
#MP Setstr fd_16 = "|en|Near Close Alert"
#MP Setstr help_fd_16 = fd_16
#MP Setstr fd_17 = "|en|Setpoint Timeout Alert"
#MP Setstr help_fd_17 = fd_17
	#MP ;Setstr fd_18 = "|en|Cond17"
	#MP ;Setstr help_fd_18 = fd_18
#MP Setstr fd_19 = "|en|Position Excursion"
#MP Setstr help_fd_19 = "|en|May be HI or LO Alert"
	#MP ;Setstr fd_20 = "|en|Cond19"
	#MP ;Setstr help_fd_20 = fd_20
#MP Setstr fd_21 = "|en|Position Large Excursion"
#MP Setstr help_fd_21 = "|en|May be HIHI or LOLO Alert"
#MP Setstr fd_22 = "|en|Deviation Alert"
#MP Setstr help_fd_22 = fd_22
		#MP
#MP Setstr fd_23 = "|en|Faults reported in Detected_Faults only"
#MP Setstr help_fd_23 = fd_23
#MP Setstr fd_24 = "|en|Other"
#MP Setstr help_fd_24 = fd_24
#MP Setstr fd_25 = "|en|Block Configuration Error"
#MP Setstr help_fd_25 = fd_25
#MP Setstr fd_26 = "|en|Device Needs Maintenance Soon"
#MP Setstr help_fd_26 = fd_26
#MP Setstr fd_27 = "|en|Output Failure Detected"
#MP Setstr help_fd_27 = fd_27
#MP Setstr fd_28 = "|en|Memory Failure"
#MP Setstr help_fd_28 = fd_28
#MP Setstr fd_29 = "|en|Lost Static Data"
#MP Setstr help_fd_29 = fd_29
#MP Setstr fd_30 = "|en|Lost NV Data"
#MP Setstr help_fd_30 = fd_30
#MP Setstr fd_31 = "|en|Device Needs Maintenance Now"
#MP Setstr help_fd_31 = fd_31
#MP Setstr fd_32 = "|en|HART communication lost"
#MP Setstr help_fd_32 = fd_32
#MP
#MP NumFDbits = 32
                    #MP
#MP For fcond=1, NumFDbits
	#MP Ifdef fd_%dfcond {STR}
		#MP ;Create a C name from English description
		#MP Setstr cn = fd_%dfcond
		#MP Setstr dummy = {uSplit, cn, "|en|"}
		#MP Setstr cn = {uSubstr, cn, cn, 1000} ;removed leading |en|
		#MP Setstr cn = {uSplit, cn, "|"} ;removed next language marker, if any
		#MP toupper[cn]
		#MP UnSpace[toupper, "_"]
		#MP Setstr cn_%dfcond = "FDCOND_" UnSpace
	#MP Endif
#MP Endfor
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                    #MP
#MP BeginBitEnumType(bitstr4, FD_CONDITIONS_ENUM)
#MP For fcond1=1, NumFDbits
	#MP fcond = NumFDbits - fcond1 + 1
	#MP Ifdef fd_%dfcond {STR}
		#MP Setstr cn = cn_%dfcond
		#MP Ifdef DD4
			#MP DefineBitEnumValue(%scn, fcond-1, fd_%dfcond, help_fd_%dfcond)
		#MP Else
			#MP DefineBitEnumValue(%scn, fcond-1, fd_%dfcond, "|en|")
		#MP Endif
	#MP Endif
#MP Endfor
#MP EndBitEnumType
                    #MP
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5 and ver 4
#MP BeginEnumType[u16, FD_RECOMMEN_ACT_ENUM]
#MP
#MP DefineEnumValue[RECOM_ACT_NOTINIT, 0,  "|en|Not Initialized", "|en|The Recommended Action parameter is not initialized", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_NONE, 1,  "|en|No Action Required", "|en|Device works fine no action required", "HLP5(", ")" ]
#MP DefineEnumValue[RECOM_ACT_SIMULATE, 2,   "|en|Leave Simulation mode", "|en|Simulate is activated and must be left to return to normal operation", "HLP5(", ")" ]
#MP DefineEnumValue[RECOM_ACT_MODE, 3,  "|en|Set Transducer Block to AUTO mode", "|en|Transducer Block does not work properly", "HLP5(", ")"]
#MP
#MP DefineEnumValue[RECOM_ACT_IPC, 4,   "|en|Internal fault", "|en|Cycle power. If persists, replace device", "HLP5(", ")"]
#MP
#MP DefineEnumValue[RECOM_ACT_RESET, 5,   "|en|Reset occured", "|en|Any reset", "HLP5(", ")"]
#MP
#MP ;;;;DefineEnumValue[RECOM_ACT_, 6,   "|en|Check LOW_POWER",              "|en|Input current < 3.2 mA", "HLP5(", ")"]
#MP
#MP DefineEnumValue[RECOM_ACT_ACTUATOR, 7,   "|en|Actuator",               "|en|Positioner is unable to position a valve normally", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_SUPPLY, 8,   "|en|Check AIR SUPPLY LOW",         "|en|Supply pressure critically low", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_POSERR, 9,   "|en|POSITION ERROR",   "|en|T1 error is configured AND the position error outside the error band for T1", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_CRIT, 10,  "|en|Internal Fault",           "|en|Reset device. If persists, replace device", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_KEYPAD, 11,  "|en|Local keypad error",     "|en|May be a sign of moisture inside housing", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 12,  "|en|Check MARGINAL_POWER",        "|en|When raw A/D signal read is below a factory-configurable value but above low power", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_CAL, 13,  "|en|CALIBRATION FAILED",  "|en|Re-do calibration of pressure", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_STOPS, 14,  "|en|FIND STOPS FAILED",      "|en|Correct the environment and re-do find stops", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_TUNE, 15,  "|en|AUTOTUNE FAILED",        "|en|If the self-tune process fails for any reason", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 16,  "|en|Check STD_DIAGNOSTICS_FAILED", "|en|If the std diagnostics process fails for any reason (AP).Not Implemented (ESD)", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_DIAG, 17,  "|en|EXT DIAGNOSTICS FAILED", "|en|Extended diagnostics process failed", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_INTERNAL, 18,  "|en|Internal error",        "|en|Internal error occurred and self-corrected. Clear it and contact tech support", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 19,  "|en|Check SUPPLY_HIGH",            "|en|Supply pressure above range", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 20,  "|en|Check detected_faults bit 15", "|en|DETECTED FAULTS BIT 15", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_BIAS, 21,  "|en|BIAS OUT OF RANGE",      "|en|Output BIAS outside of range", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_IP, 22,  "|en|Check IP_OUT_OF_RANGE",        "|en|Output current out of normal range", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_TEMPR, 23,  "|en|Check TEMPR_OUT_OF_RANGE",     "|en|Temperture outside of operating range[-40, 85] deg.C", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 24,  "|en|Check DI_ABNORMAL",            "|en|DI_ABNORMAL", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 25,  "|en|Check CONF_1",                 "|en|Low supply pressure alarm limit is configured too low", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 26,  "|en|Check LATCH_FSAFE",            "|en|LATCH_FSAFE", "HLP5(", ")"]
#MP ;;It is just an indication DefineEnumValue[RECOM_ACT_, 27,  "|en|Check TIGHT_SHUTOFF",          "|en|TIGHT_SHUTOFF", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 28,  "|en|Check detected_faults bit 23", "|en|DETECTED FAULTS BIT 23", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 29,  "|en|Check NVM_CHECKSUM0",          "|en|If an FRAM record and its copy both have CRC errors (as detected by read on initialization,)  OR if the temperature calibration table has not been written in its entirety (detected by CRC of column CRCs) OR bad FRAM signature", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 30,  "|en|Check RAM_CHECKSUM",           "|en|A valid hidden record (in RAM) existing upon reset indicating that a RAM data item had a bad checksum, as detected by on-request data test", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 31,  "|en|Check Check FW_CHECKSUM",      "|en|Flash CRC test fails. (AP 311 only: The test runs only on (any) reset) The test takes about 4-10 seconds roundtrip", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 32,  "|en|Check STACK",                  "|en|A valid hidden record (in RAM) existing upon reset indicating that a stack overflow had occurred, as detected by the task switching code", "HLP5(", ")"]
#MP ;;AK DefineEnumValue[RECOM_ACT_FACW, 33,  "|en|Check FACTORYWRITE",           "|en|Unauthorized write to NV memory", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_NVTEST, 34,  "|en|NV memory failed",           "|en|Device is likely to fail on reset", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 35,  "|en|Check detected_faults bit 30", "|en|DETECTED FAULTS BIT 30", "HLP5(", ")"]
#MP ;;AK DefineEnumValue[RECOM_ACT_FACMODE, 36,  "|en|FACTORY MODE",            "|en|Reset device", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 37,  "|en|Check REF_VOLTAGE",            "|en|If temperature compensated reference voltage is out of range [0, 30000] counts for 5 reads in a row, or if the raw reading is outside the range +-5% of nominal", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 38,  "|en|Check POSITION_SENSOR",        "|en|If upon request temperature compensated remote position sensor reading is outside the range [ 2.5, 120.0-2.5] degrees or internal position sensor reading is outside the range [ 70.0, 70.0] Gauss for 5 reads in a row", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 39,  "|en|Check CURRENT_SENSOR",         "|en|If, upon request, temperature compensated current sensor reading is outside the range [ 100, 30.0] mA for 5 reads in a row", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 40,  "|en|Check TEMPERATURE_SENSOR",     "|en|If, upon request, temperature compensated temperature sensor reading is outside the range [ 60.0, 100.0] C for 5 reads in a row", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_AI, 41,  "|en|Analog input",     "|en|Physical Analog input failed", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_PRES1, 42,  "|en|PRESSURE1",              "|en|pressure sensor 1 (SA: pressure A, DA: pressure B) reading is outside the range", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_PRES2, 43,  "|en|PRESSURE2",              "|en|pressure sensor 2 (SA: supply, DA: pressure A) reading is outside the range", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_PRES3, 44,  "|en|PRESSURE3",              "|en|pressure sensor 3 (DA: supply) reading is outside the range", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_PRES4, 45,  "|en|PRESSURE4",              "|en|pressure sensor 4 (pilot) reading is outside the range", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_PRES5, 46,  "|en|PRESSURE5",              "|en|pressure sensor 5 (atmospheric) reading is outside the range", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 47,  "|en|Check WATCHDOG_TIMEOUT",       "|en|Stored upon reset", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_NVWRITE, 48,  "|en|NVM WRITE",              "|en|Write to FRAM failed. Clear and try again", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 49,  "|en|Check IRQ_FAULT",              "|en|A valid hidden record (in RAM) existing upon reset indicating that an illegal interrupt occurred", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 50,  "|en|Check TMOUT_FLASH_TEST",       "|en|If a round of flash test is not completed in 2 hrs", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 51,  "|en|Check SELF_CHECK",             "|en|A valid hidden record (in RAM) existing upon reset indicating that a fatal event (watchdog, illegal interrupt, stack overflow, data checksum) occurred twice in a N-second period. (AP 311 N=10; ESD N= 20)", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 52,  "|en|Check SOFTWARE",               "|en|A catch-all not-otherwise-defined fault. Currently: A valid hidden record (in RAM) existing upon reset indicating that a CPU exception (such as invalid instruction) occurred, OR invalid target mode of the device was found", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 53,  "|en|Check ESD_TRIP",               "|en|If I/P feedback is below threshold, position and pressure are deemed stable, actuator1 pressure is below threshold", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 54,  "|en|Check AI_PV_LOW",              "|en|PV voltage too low", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 55,  "|en|Check AI_PV_HIGH",             "|en|PV voltage too high", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 56,  "|en|Check IP_SERVO_LOW",           "|en|IP is below its defined pressure range", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 57,  "|en|Check IP_SERVO_HIGH",          "|en|IP is above its defined pressure range", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 58,  "|en|Check detected_faults bit 53", "|en|DETECTED FAULTS BIT 53", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 59,  "|en|Check DIAGPROC1",              "|en|DIAGPROC1", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 60,  "|en|Check RANGE1",                 "|en|RANGE1", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 61,  "|en|Check RANGE2",                 "|en|RANGE2", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 62,  "|en|Check LINKAGE_DRIFT",          "|en|The measured position is more than LinkageLimit above/below expected", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 63,  "|en|Check VALVE_STUCK_CLOSED",     "|en|Stable & (SP > 99.5%) and (Position < StuckLimit)", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 64,  "|en|Check VALVE_STUCK_OPENED",     "|en|stable & (SP < .5%) and (Position > StuckLimit)", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_UI, 62,  "|en|Check UI_OFF",                 "|en|UI is turned off because it is not responsive at low (main board) temperature, -10 deg.C", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 66,  "|en|Check RANGE3",                 "|en|RANGE3", "HLP5(", ")"]
#MP ;;;;DefineEnumValue[RECOM_ACT_, 67,  "|en|Check RANGE4",                 "|en|RANGE4", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_UNKNOWN, 68,  "|en|Unknown recommended action",   "|en|Unknown recommended action", "HLP5(", ")"]
#MP DefineEnumValue[RECOM_ACT_FACBK, 72,  "|en|Factory backup",   "|en|Create/Restore TB data failed", "HLP5(", ")"]
#MP EndEnumType
                    #MP
#MP BeginEnumType[u8, ENUM_RB_RESTART]
#MP DefineEnumValue[ RS_RESTART_RUN, 0x01,  "[restart_run]",   "[restart_run_help]"]
#MP DefineEnumValue[ RS_RESTART_RESOURCE, 0x02,    "[restart_resource]",      "[restart_resource_help]" ]
#MP DefineEnumValue[ RS_RESTART_WITH_DEFAULTS, 0x03,    "[restart_defaults]",      "[restart_defaults_help]" ]
#MP DefineEnumValue[ RS_RESTART_PROCESSOR, 0x04,    "[restart_processor]",     "[restart_processor_help]" ]
    #MP ;stolen from svi_positioner.h
#MP Setstr RESTART_FACTORY_DEFAULT       "|en|Restore TB to Factory"
#MP Setstr RESTART_FACTORY_DEFAULT_HELP  "|en|Restart device and reset all transducer block parameters to the values before any configuration was done by the user"
    #MP ;end stolen
#MP DefineEnumValue[ RS_RESTART_FACTORY_DEFAULTS, 0x05,    RESTART_FACTORY_DEFAULT, RESTART_FACTORY_DEFAULT_HELP ]
#MP Setstr RS_RESTART_QUICKSTART       "|en|Quick Defaults"
#MP Setstr RS_RESTART_QUICKSTART_HELP  "|en|Init some block parameters to sensible default values. Requires RB in OOS mode"
#MP DefineEnumValue[ RS_RESTART_QUICKSTART, 0x06,    RS_RESTART_QUICKSTART, RS_RESTART_QUICKSTART_HELP ]
#MP Setstr valnote = "Not used except for instantiated blocks. May be removed from SVI FF."
#MP DefineEnumValue[ RS_RESET_BLOCKS, 11 ]
#MP Setstr valnote = "Tests external watchdog in FFP. Expected: a reset and a reset trap. APP may report timeouts."
#MP DefineEnumValue[ RS_RESTART_TEST_WATCHDOG, 30 ]
#MP Setstr valnote = "Tests internal watchdog in FFP. Expected: a reset and watchdog trap. APP may report timeouts."
#MP DefineEnumValue[ RS_RESTART_TEST_IWDOG, 31 ]
#MP Setstr valnote = "Creates a copy of of current TB parameters. Required by ""Restore to Factory""."
#MP DefineEnumValue[ RS_RESTART_HIDDEN, 42 ]
#MP Setstr valnote = "Causes reinitialization of FFP NVMEM and reset."
#MP DefineEnumValue[ RS_RESTART_REINIT_NVMEM, 169 ]
#MP EndEnumType
                    #MP
#MP Restore GenDDdefs ;= (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                    #MP
#MP ;-------------- end RB -----------------------------
