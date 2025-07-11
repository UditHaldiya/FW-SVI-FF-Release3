#MP Include "uconfig.inc"
#MP Macro select ; [option, value]
#MP OPTION_%n#1#%n__%n#2# = 1 ;just define
#MP Endm
#MP Include "TBALERTS_config.inc"
#MP Include "HISTOGRAM_config.inc"
            #MP
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP BeginEnumType[u8, ENUM_ALERT_STATE]
#MP DefineEnumValue[STATE_FALSE, 0, "|en|FALSE"]
#MP DefineEnumValue[STATE_TRUE, 1, "|en|TRUE"]
#MP EndEnumType
#MP Restore GenDDdefs
                    #MP
            #MP
#MP Macro AlertExtras ;Vlad's alert cached value
#MP Ifdef OPTION_TBALERTS_SELECTION_CACHE__INCLUDE
    #MP StructMember[ENUM_ALERT_STATE, alert] ;component_4
#MP Endif
#MP Ifdef OPTION_TBALERTS_SELECTION_HISTORY__INCLUDE
    #MP StructMember[ENUM_ALERT_STATE, historic_alert] ;component_5
#MP Endif
#MP Endm
            #MP
#MP Macro AlertExtrasDefaults  ;Vlad's alert cached value
#MP Ifdef OPTION_TBALERTS_SELECTION_CACHE__INCLUDE
    #MP Setstr DDLabel = "|en|Alert state"
    #MP Setstr DDHelp = "|en|A copy of alert state"
    #MP Setstr DDClass = "CONTAINED & DYNAMIC"
    #MP DefaultRecordParam [alert, "0", 0]
#MP Endif
#MP Ifdef OPTION_TBALERTS_SELECTION_HISTORY__INCLUDE
    #MP Setstr DDLabel = "|en|Historic Alert state "
    #MP DefaultRecordParam [historic_alert, "0", SUBX_ACCESS]
#MP Endif
#MP Endm
            #MP
            #MP
#MP ;Globally disable DD4 help
#MP DDHelp=5; if defined, DD4 help is suppressed
#MP
#MP gwout = 10 ;starting # of the first custom param
                    #MP
#MP; This is an example of how to define old-style GW struct:
#MP; Members must be named component_0, component_1, etc.
#MP; Endstruct must have a non-zero numeric parameter
#MP BeginStruct[STRUCT2_U8]
#MP StructMember[u8, component_0]
#MP StructMember[u8, component_1]
#MP EndStruct[1]
                    #MP
#MP BeginStruct[CHAR_TYPE]
#MP StructMember[u8, component_0]
#MP StructMember[u8, component_1]
#MP EndStruct[1]
                    #MP
#MP BeginStruct[UI_CUST_CONF]
#MP StructMember[u8, component_0]
#MP StructMember[u8, component_1]
#MP EndStruct[1]
                    #MP
#MP BeginStruct[POSITION_LIMITS]
#MP StructMember[u8, component_0]
#MP StructMember[u8, component_1]
#MP StructMember[u8, component_2]
#MP StructMember[float32, component_3]
#MP StructMember[float32, component_4]
#MP StructMember[u8, component_5]
#MP StructMember[u8, component_6]
#MP StructMember[float32, component_7]
#MP EndStruct[1]
                #MP
#MP BeginStruct[CONTROL_SET]
#MP StructMember[s16, component_0]
#MP StructMember[s16, component_1]
#MP StructMember[s16, component_2]
#MP StructMember[s16, component_3]
#MP StructMember[s16, component_4]
#MP StructMember[s16, component_5]
#MP StructMember[s16, component_6]
#MP StructMember[s16, component_7]
#MP EndStruct[1]
                    #MP
#MP BeginStruct[ACTIVE_CONTROL_SET]
#MP StructMember[s16, component_0]
#MP StructMember[s16, component_1]
#MP StructMember[s16, component_2]
#MP StructMember[s16, component_3]
#MP StructMember[s16, component_4]
#MP StructMember[s16, component_5]
#MP StructMember[s16, component_6]
#MP StructMember[s16, component_7]
#MP StructMember[s16, component_8]
#MP EndStruct[1]
                    #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                    #MP
#MP BeginStruct[POSITION_ALERT] ;Reference for GW
#MP StructMember[float32, position] ;component_0
#MP StructMember[float32, alert_point]
#MP StructMember[float32, deadband, MIN_VALUE, "0.01", MAX_VALUE, "1000"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                    #MP
#MP BeginStruct[MN_DEVIATION_ALERT] ;, MN_DEVIATION_ALERT]
#MP StructMember[float32, __deviation_value] ;component_0
#MP StructMemberLike[__pos_alert_hi, alert_point, LABEL, #@"|en|Threshold"#, HELP, #@"|en|User defined deviation to trigger alert when position error exceeds this value for specified time"#]
#MP ;StructMember[float32, alert_point] ;component_1
#MP StructMember[float32, __deviation_deadband] ;component_2
#MP StructMember[u32, time_threshold, MAX_VALUE, "3600"] ;component_3
#MP AlertExtras
#MP StructMember[bool_t, enable] ;component_6
#MP EndStruct
                    #MP
#MP BeginStruct[POSITION_LO_ALERT, POSITION_ALERT]
#MP StructMember[float32, position] ;component_0
#MP StructMember[float32, alert_point] ;component_1
#MP ;StructMember[__pos_alert_lo, alert_point] ;Goes as __pos_alert_lo and as alert_point to GW
#MP StructMember[float32, deadband]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                    #MP
#MP BeginStruct[POSITION_LOLO_ALERT, POSITION_ALERT]
#MP StructMember[float32, position] ;component_0
#MP StructMember[float32, alert_point] ;component_1
#MP ;StructMember[__pos_alert_lo, alert_point] ;Goes as __pos_alert_lo and as alert_point to GW
#MP StructMember[float32, deadband, MIN_VALUE, "0.01", MAX_VALUE, "1000"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                    #MP
#MP BeginStruct[POSITION_HI_ALERT, POSITION_ALERT]
#MP StructMember[float32, position] ;component_0
#MP StructMember[float32, alert_point] ;component_1
#MP ;StructMember[__pos_alert_hi, alert_point] ;Goes as __pos_alert_hi and as alert_point to GW
#MP StructMember[float32, deadband, MIN_VALUE, "0.01", MAX_VALUE, "1000"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                    #MP
#MP BeginStruct[POSITION_HIHI_ALERT, POSITION_ALERT]
#MP StructMember[float32, position] ;component_0
#MP StructMember[float32, alert_point] ;component_1
#MP ;StructMember[__pos_alert_lo, alert_point] ;Goes as __pos_alert_lo and as alert_point to GW
#MP StructMember[float32, deadband, MIN_VALUE, "0.01", MAX_VALUE, "1000"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                #MP
#MP BeginEnumType[u16, ENUM_UNITS_INDEX_TRAVEL]
#MP DefineEnumValue[UNITS_INDEX_INCH, 1019, "[unit_code_1019]", "[unit_code_1019_help]"]
#MP DefineEnumValue[UNITS_INDEX_CM, 1012, "[unit_code_1012]", "[unit_code_1012_help]"]
#MP DefineEnumValue[UNITS_INDEX_MM, 1013, "[unit_code_1013]", "[unit_code_1013_help]"]
#MP DefineEnumValue[UNITS_INDEX_DEG_ANGLE, 1005, "[unit_code_1005]", "[unit_code_1005_help]"]
#MP DefineEnumValue[UNITS_INDEX_RAD_ANGLE, 1004, "[unit_code_1004]", "[unit_code_1004_help]"]
#MP DefineEnumValue[UNITS_INDEX_PERCENT, 1342, "[unit_code_1342]", "[unit_code_1342_help]"]
#MP EndEnumType
                #MP
#MP BeginStruct[TRAVEL]
#MP StructMember[float32, TravelRange, MIN_VALUE, "0.1", MAX_VALUE, "10000"]
#MP StructMember[ENUM_UNITS_INDEX_TRAVEL, units_index]
#MP EndStruct
                #MP
#MP; This is an example of how to define new-style GW struct:
#MP; Members are named as desired
#MP; Endstruct must have no parameters (or at least a zero numeric parameter)
#MP BeginStruct[TRAVEL_ALERT]
#MP StructMember[u32, travel_accumulation]
#MP StructMember[u32, int_alert_point]
#MP StructMember[float32, deadband_ab, MIN_VALUE, "0.02", MAX_VALUE, "10.0"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                #MP
#MP BeginStruct[CYCLE_COUNTER_ALERT]
#MP StructMember[u32, cycle_counter]
#MP StructMember[u32, int_alert_point]
#MP StructMember[float32, deadband_ab, MIN_VALUE, "0.02", MAX_VALUE, "10.0"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginStruct[NEAR_CLOSED_ALERT]
#MP StructMember[float32, position_closed]
#MP StructMember[u32, near_closed]
#MP StructMember[u32, alert_point]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                #MP
#MP BeginStruct[SYSTEM_ALERT]
#MP StructMember[float32, curr_value] ;component_0
#MP StructMember[float32, alert_point] ;component_1
#MP StructMember[float32, deadband] ;component_2
#MP AlertExtras
#MP StructMember[bool_t, enable] ;component_5
#MP EndStruct
                #MP
#MP BeginStruct[XD_FSTATE]
#MP StructMember[u8, component_0]
#MP StructMember[u8, component_1]
#MP StructMember[float32, component_2]
#MP StructMember[float32, component_3]
#MP EndStruct[1]
                #MP
#MP BeginStruct[TREND]
#MP StructMember[u32, currently_collected]
#MP StructMember[u32, today]
#MP StructMember[u32, last_day]
#MP StructMember[u32, previous_day]
#MP StructMember[u32, three_days_ago]
#MP StructMember[u32, current_week]
#MP StructMember[u32, last_week]
#MP StructMember[u32, previous_week]
#MP StructMember[u32, three_weeks_ago]
#MP StructMember[u32, current_month]
#MP StructMember[u32, last_month]
#MP StructMember[u32, previous_month]
#MP StructMember[u32, three_months_ago]
#MP StructMember[u32, current_12_months]
#MP StructMember[u32, last_12_months]
#MP StructMember[u32, previous_12_months]
#MP StructMember[u32, three_years_ago]
#MP EndStruct
                    #MP
#MP BeginStruct[ERR_TREND]
#MP StructMember[float32, currently_collected]
#MP StructMember[float32, today]
#MP StructMember[float32, last_day]
#MP StructMember[float32, previous_day]
#MP StructMember[float32, three_days_ago]
#MP StructMember[float32, current_week]
#MP StructMember[float32, last_week]
#MP StructMember[float32, previous_week]
#MP StructMember[float32, three_weeks_ago]
#MP StructMember[float32, current_month]
#MP StructMember[float32, last_month]
#MP StructMember[float32, previous_month]
#MP StructMember[float32, three_months_ago]
#MP StructMember[float32, current_12_months]
#MP StructMember[float32, last_12_months]
#MP StructMember[float32, previous_12_months]
#MP StructMember[float32, three_years_ago]
#MP EndStruct
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP Setstr LBL_POS_5_PERCENT_CLOSED            "|en|Closed .. 5%"
#MP Setstr LBL_POS_10_PERCENT                  "|en|10%"
#MP Setstr LBL_POS_20_PERCENT                  "|en|20%"
#MP Setstr LBL_POS_30_PERCENT                  "|en|30%"
#MP Setstr LBL_POS_40_PERCENT                  "|en|40%"
#MP Setstr LBL_POS_50_PERCENT                  "|en|50%"
#MP Setstr LBL_POS_60_PERCENT                  "|en|60%"
#MP Setstr LBL_POS_70_PERCENT                  "|en|70%"
#MP Setstr LBL_POS_80_PERCENT                  "|en|80%"
#MP Setstr LBL_POS_90_PERCENT                  "|en|90%"
#MP Setstr LBL_POS_95_PERCENT                  "|en|95%"
#MP Setstr LBL_POS_95_PERCENT_OPEN             "|en|95% .. Open"
#MP BeginStruct[POS_HISTOGRAM]
#MP StructMember[u32, total_time] ;component_0
#MP StructMember[float32, pos_5_percent_closed] ;component_1
#MP StructMemberLike[pos_5_percent_closed, pos_10_percent, LABEL, LBL_POS_10_PERCENT] ;component_2
#MP StructMemberLike[pos_5_percent_closed, pos_20_percent, LABEL, LBL_POS_20_PERCENT] ;component_3
#MP StructMemberLike[pos_5_percent_closed, pos_30_percent, LABEL, LBL_POS_30_PERCENT] ;component_4
#MP StructMemberLike[pos_5_percent_closed, pos_40_percent, LABEL, LBL_POS_40_PERCENT] ;component_5
#MP StructMemberLike[pos_5_percent_closed, pos_50_percent, LABEL, LBL_POS_50_PERCENT] ;component_6
#MP StructMemberLike[pos_5_percent_closed, pos_60_percent, LABEL, LBL_POS_60_PERCENT] ;component_7
#MP StructMemberLike[pos_5_percent_closed, pos_70_percent, LABEL, LBL_POS_70_PERCENT] ;component_8
#MP StructMemberLike[pos_5_percent_closed, pos_80_percent, LABEL, LBL_POS_80_PERCENT] ;component_9
#MP StructMemberLike[pos_5_percent_closed, pos_90_percent, LABEL, LBL_POS_90_PERCENT] ;component_10
#MP StructMemberLike[pos_5_percent_closed, pos_95_percent, LABEL, LBL_POS_95_PERCENT] ;component_11
#MP StructMemberLike[pos_5_percent_closed, pos_95_percent_open, LABEL, LBL_POS_10_PERCENT] ;component_12
#MP EndStruct
                    #MP
#MP BeginStruct[POS_ERR_HISTOGRAM]
#MP StructMember[float32, pos_5_percent_closed] ;component_0
#MP StructMemberLike[pos_5_percent_closed, pos_10_percent, LABEL, LBL_POS_10_PERCENT] ;component_1
#MP StructMemberLike[pos_5_percent_closed, pos_20_percent, LABEL, LBL_POS_20_PERCENT] ;component_2
#MP StructMemberLike[pos_5_percent_closed, pos_30_percent, LABEL, LBL_POS_30_PERCENT] ;component_3
#MP StructMemberLike[pos_5_percent_closed, pos_40_percent, LABEL, LBL_POS_40_PERCENT] ;component_4
#MP StructMemberLike[pos_5_percent_closed, pos_50_percent, LABEL, LBL_POS_50_PERCENT] ;component_5
#MP StructMemberLike[pos_5_percent_closed, pos_60_percent, LABEL, LBL_POS_60_PERCENT] ;component_6
#MP StructMemberLike[pos_5_percent_closed, pos_70_percent, LABEL, LBL_POS_70_PERCENT] ;component_7
#MP StructMemberLike[pos_5_percent_closed, pos_80_percent, LABEL, LBL_POS_80_PERCENT] ;component_8
#MP StructMemberLike[pos_5_percent_closed, pos_90_percent, LABEL, LBL_POS_90_PERCENT] ;component_9
#MP StructMemberLike[pos_5_percent_closed, pos_95_percent, LABEL, LBL_POS_95_PERCENT] ;component_10
#MP StructMemberLike[pos_5_percent_closed, pos_95_percent_open, LABEL, LBL_POS_10_PERCENT] ;component_111
#MP EndStruct
                    #MP
#MP BeginStruct[SETPOINT_TIMEOUT_ALERT]
#MP StructMember[float32, time_since_update, MIN_VALUE, "0.0"]
#MP StructMember[float32, alert_point, MIN_VALUE, "0.5"]
#MP StructMember[float32, setpoint_max_time, MIN_VALUE, "0.0"]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
#MP Restore GenDDdefs
                #MP
#MP BeginStruct[AUTOTUNE]
#MP StructMember[float32, component_0]
#MP StructMember[s8, component_1]
#MP StructMember[u8, component_2]
#MP StructMember[u16, component_3]
#MP EndStruct[1]
                #MP
#MP BeginStruct[CHECK_PROCESS]
#MP StructMember[u8, component_0]
#MP StructMember[u32, component_1]
#MP EndStruct[1]
                    #MP
#MP BeginStruct[UI_ACCESS_CTRL]
#MP StructMember[u8, component_0]
#MP StructMember[bool_t, component_1]
#MP StructMember[s16, component_2]
#MP EndStruct[1]
                    #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP BeginEnumType5[u8, ENUM_PROCESS_ID]
#MP DefineEnumValue[process_none, 0, "|en|No Process"]
#MP DefineEnumValue[process_find_stops, 1, "|en|Auto Find Stops"]
#MP DefineEnumValue[process_atune, 4, "|en|Autotune"]
#MP DefineEnumValue[process_signature, 7, "|en|Diagnostic Signature"]
#MP DefineEnumValue[process_step_test, 8, "|en|Step Test"]
#MP DefineEnumValue[process_ramp_test, 15, "|en|Ramp Test"]
#MP DefineEnumValue[process_pst, 16, "|en|Partial Stroke Test"]
#MP DefineEnumValue[process_fwdl, 22, "|en|FW download"]
#MP DefineEnumValue[process_loadbuffer, 24, "|en|Load saved diag."]
#MP DefineEnumValue[process_savebuffer, 25, "|en|Save diag. curve"]
#MP DefineEnumValue[process_save_tb_nvm, 26, "|en|Save TB as factory"]
#MP DefineEnumValue[process_restore_tb_nvm, 27, "|en|Restore TB to factory"]
#MP DefineEnumValue[process_clone_nvm, 28, "|en|Clone NVM", "|en|An internal service"]
#MP DefineEnumValue[process_cancel, 29, "|en|Cancelling", "|en|An internal service"]
#MP DefineEnumValue[process_write_logfile, 32, "|en|Deferred writes", "|en|An internal service"]
#MP DefineEnumValue[process_placeholder, 33, "|en|Placeholder", "|en|An internal service"]
#MP EndEnumType
                    #MP
#MP BeginEnumType5[u8, ENUM_ALERT_MAP]
#MP DefineEnumValue[mapped_to_rb, 1, "|en|Copy all to RB.BLOCK_ERR"]
#MP DefineEnumValue[stays_in_tb, 2, "|en|TB.BLOCK_ERR only"]
#MP DefineEnumValue[perFF890, 3, "|en|Report per FF890"]
#MP EndEnumType
                    #MP
#MP BeginEnumType5[u8, ENUM_ALERT_ACTION]
#MP DefineEnumValue[alert_silent, 0, "|en|No Alert & No Data Buffer", "|en|No effect on block_err"]
#MP DefineEnumValue[alert_silent_tOff, 20, "|en|No Alert & Buffer On>Off", "|en|No effect on block_err; start data collection if becomes inactive"]
#MP DefineEnumValue[alert_silent_tOn, 40, "|en|No Alert & Buffer Off>On", "|en|No effect on block_err; start data collection if becomes active"]
#MP DefineEnumValue[alert_silent_tChange, 60, "|en|No Alert & Buffer on Change", "|en|No effect on block_err; start data collection if state changes"]
#MP DefineEnumValue[alert_warn, 1, "|en|Warning & No Data Buffer", "|en|block_err sets NEEDS_MAINT_SOON"]
#MP DefineEnumValue[alert_warn_tOff, 21, "|en|Warning & Buffer On>Off", "|en|block_err sets NEEDS_MAINT_SOON; start data collection if becomes inactive"]
#MP DefineEnumValue[alert_warn_tOn, 41, "|en|Warning & Buffer Off>On", "|en|block_err sets NEEDS_MAINT_SOON; start data collection if becomes active"]
#MP DefineEnumValue[alert_warn_tChange, 61, "|en|Warning & Buffer on Change", "|en|block_err sets NEEDS_MAINT_SOON; start data collection if state changes"]
#MP DefineEnumValue[alert_maint, 2, "|en|Maintenance & No Data Buffer", "|en|block_err sets NEEDS_MAINT_NOW"]
#MP DefineEnumValue[alert_maint_tOff, 22, "|en|Maintenance & Buffer On>Off", "|en|block_err sets NEEDS_MAINT_NOW; start data collection if becomes inactive"]
#MP DefineEnumValue[alert_maint_tOn, 42, "|en|Maintenance & Buffer Off>On", "|en|block_err sets NEEDS_MAINT_NOW; start data collection if becomes active"]
#MP DefineEnumValue[alert_maint_tChange, 62, "|en|Maintenance & Buffer on Change", "|en|block_err sets NEEDS_MAINT_NOW; start data collection if state changes"]
#MP DefineEnumValue[alert_failure, 3, "|en|Failure & No Data Buffer", "|en|block_err sets FAULT_STATE_SET"]
#MP DefineEnumValue[alert_failure_tOff, 23, "|en|Failure & Buffer On>Off", "|en|block_err sets FAULT_STATE_SET; start data collection if becomes inactive"]
#MP DefineEnumValue[alert_failure_tOn, 43, "|en|Failure & Buffer Off>On", "|en|block_err sets FAULT_STATE_SET; start data collection if becomes active"]
#MP DefineEnumValue[alert_failure_tChange, 63, "|en|Failure & Buffer on Change", "|en|block_err sets FAULT_STATE_SET; start data collection if state changes"]
#MP EndEnumType
                    #MP
#MP Macro SimilarALerts ;[name_dd_suffix.opt]
#MP If #0# > 0
    #MP Setstr dd_suffix {#1#}
#MP Else
    #MP Setstr dd_suffix ""
#MP Endif
#MP StructMemberLike[deviation_alert%sdd_suffix, position_hihi_alert%sdd_suffix, LABEL, #@"|en|Position HiHi Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, position_hi_alert%sdd_suffix, LABEL, #@"|en|Position Hi Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, position_lo_alert%sdd_suffix, LABEL, #@"|en|Position Lo Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, position_lolo_alert%sdd_suffix, LABEL, #@"|en|Position LoLo Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, setpoint_timeout_alert%sdd_suffix, LABEL, #@"|en|Setpoint timeout Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, near_close_alert%sdd_suffix, LABEL, #@"|en|Near Close Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, travel_accumulation_a_alert%sdd_suffix, LABEL, #@"|en|Travel Accum. A Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, travel_accumulation_b_alert%sdd_suffix, LABEL, #@"|en|Travel Accum. B Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, cycle_counter_a_alert%sdd_suffix, LABEL, #@"|en|Cycle counter A Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, cycle_counter_b_alert%sdd_suffix, LABEL, #@"|en|Cycle counter B Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, working_time_alert%sdd_suffix, LABEL, #@"|en|Working time Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, supply_pressure_hi_alert%sdd_suffix, LABEL, #@"|en|Supply pressure Hi Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, supply_pressure_lo_alert%sdd_suffix, LABEL, #@"|en|Supply pressure Lo Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, supply_pressure_lolo_alert%sdd_suffix, LABEL, #@"|en|Supply pressure LoLo Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, temperature_hi_alert%sdd_suffix, LABEL, #@"|en|Temperature Hi Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, temperature_lo_alert%sdd_suffix, LABEL, #@"|en|Temperature Lo Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, ip_drive_current_alert_hi%sdd_suffix, LABEL, #@"|en|I/P current Hi Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, ip_drive_current_alert_lo%sdd_suffix, LABEL, #@"|en|I/P current Lo Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, sensor_failure_alert%sdd_suffix, LABEL, #@"|en|Sensor failure Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, processor_alert%sdd_suffix, LABEL, #@"|en|Processor Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, valve_control_alert%sdd_suffix, LABEL, #@"|en|Valve control Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, commissioning_alert%sdd_suffix, LABEL, #@"|en|Commissioning Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, air_supply_alert%sdd_suffix, LABEL, #@"|en|Critical air supply Alert"#]
#MP StructMemberLike[deviation_alert%sdd_suffix, supporting_hardware_alert%sdd_suffix, LABEL, #@"|en|Supporting hardware Alert"#]
#MP Endm
                    #MP
#MP BeginStruct[ALERT_ACTION]
#MP StructMember[ENUM_ALERT_MAP, block_err_map]
#MP StructMember[ENUM_ALERT_ACTION, deviation_alert_act]
#MP SimilarALerts[_act]
#MP EndStruct
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginStruct[FAILED_STATE]
#MP StructMember[u8, ff]
#MP StructMember[u8, app]
#MP StructMember[u8, propagate_mode]
#MP EndStruct
                #MP
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                   #MP
#MP BeginStruct[ALERT_STATE]
#MP StructMember[ENUM_ALERT_STATE, deviation_alert_st]
#MP SimilarALerts[_st]
#MP EndStruct
                #MP
#MP BeginStruct[ALERT_COUNTERS]
#MP StructMember[u16, deviation_alert_cnt]
#MP SimilarALerts[_cnt]
#MP EndStruct
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginStruct[WORKING_TIME_ALERT]
#MP StructMember[u32, total_time]
#MP StructMember[u32, alert_point]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                    #MP
#MP BeginStruct[ACTUATOR_1]
#MP StructMember[stringv32, act_man_id]
#MP StructMember[stringv32, act_model_num]
#MP StructMember[stringv32, act_sn]
#MP EndStruct
                    #MP
#MP BeginStruct[ACTUATOR_2]
#MP StructMember[stringv32, act_type_string]
#MP StructMember[stringv32, act_size]
#MP StructMember[stringv32, act_rotary_moment_arm]
#MP StructMember[u16, act_effective_area]
#MP EndStruct
                    #MP
#MP BeginStruct[ACTUATOR_3]
#MP StructMember[u16, shutoff_dp]
#MP StructMember[u8, hand_wheel]
#MP StructMember[u8, style]
#MP StructMember[u8, act_fail_action]
#MP StructMember[u8, relay_type]
#MP StructMember[float32, supply_prs_max]
#MP StructMember[float32, prs_control_hi]
#MP StructMember[float32, prs_control_lo]
#MP EndStruct
                #MP
#MP BeginStruct[ACTUATOR_INFO]
#MP StructMember[stringv32, descriptor]
#MP StructMember[stringv32, message]
#MP StructMember[stringv8, date_info]
#MP StructMember[stringv32, spec_sheet]
#MP EndStruct
                #MP
#MP BeginStruct[VALVE_IDENTIFICATION]
#MP StructMember[stringv32, valve_man_id]
#MP StructMember[stringv32, valve_model_num]
#MP StructMember[stringv32, valve_sn]
#MP EndStruct
                #MP
#MP BeginStruct[VALVE_SERVICE]
#MP StructMember[stringv32, service]
#MP StructMember[u8, pid_no]
#MP EndStruct
                #MP
#MP BeginStruct[VALVE_BODY_1]
#MP StructMember[u8, valve_type]
#MP StructMember[u16, body_size]
#MP StructMember[stringv32, packing]
#MP StructMember[stringv32, plug_type]
#MP StructMember[stringv32, seat_ring_type]
#MP EndStruct
                    #MP
#MP BeginStruct[VALVE_BODY_2]
#MP StructMember[stringv32, characteristic]
#MP StructMember[stringv32, leakage_class]
#MP EndStruct
                    #MP
#MP BeginStruct[VALVE_BODY_3]
#MP StructMember[stringv32, flow_action]
#MP StructMember[stringv32, rated_adj_cv]
#MP EndStruct
                #MP
#MP BeginStruct[VALVE_INFO]
#MP StructMember[u8, same_as_actuator]
#MP StructMember[stringv32, descriptor]
#MP StructMember[stringv32, message]
#MP StructMember[stringv8, date_info]
#MP StructMember[stringv32, spec_sheet]
#MP EndStruct
                    #MP
#MP BeginStruct[BOOSTER]
#MP StructMember[stringv32, manufacturer]
#MP StructMember[stringv32, model]
#MP StructMember[stringv32, qty]
#MP EndStruct
                #MP
#MP BeginStruct[ACCESSORY]
#MP StructMember[stringv32, solenoid]
#MP StructMember[u8, remote_sensor]
#MP EndStruct
                #MP
#MP BeginStruct[POSITION_EXTREMES]
#MP StructMember[float32, final_value_max]
#MP StructMember[float32, final_value_min]
#MP StructMember[float32, final_pos_value_max]
#MP StructMember[float32, final_pos_value_min]
#MP StructMember[float32, working_sp_max]
#MP StructMember[float32, working_sp_min]
#MP StructMember[float32, working_pos_max]
#MP StructMember[float32, working_pos_min]
#MP EndStruct
                    #MP
#MP BeginStruct[PRESSURE_EXTREMES]
#MP StructMember[float32, supply_pressure_max]
#MP StructMember[float32, supply_pressure_min]
#MP StructMember[float32, actuator_a_max]
#MP StructMember[float32, actuator_a_min]
#MP StructMember[float32, actuator_b_max]
#MP StructMember[float32, actuator_b_min]
#MP StructMember[float32, pilot_max]
#MP StructMember[float32, pilot_min]
#MP EndStruct
                    #MP
                    #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP BeginStruct[TEMPERATURE_EXTREMES]
#MP StructMember[float32, temperature_max]
#MP StructMember[float32, temperature_min]
#MP StructMemberLike[__internal_temp_max, tempr_max_lifetime, CONSTANT_UNIT, #@[unit_code_1001]#, HELP, #@"|en|Max Lifetime Temperature"#] ;Goes as __internal_temp_max to DD and as tempr_max_lifetime to GW
#MP StructMemberLike[__internal_temp_min, tempr_min_lifetime, CONSTANT_UNIT, #@[unit_code_1001]#, HELP, #@"|en|Min Lifetime Temperature"#] ;Goes as __internal_temp_max to DD and as tempr_max_lifetime to GW
#MP ;StructMember[__internal_temp_min, tempr_min_lifetime] ;Goes as __internal_temp_min to DD and as tempr_min_lifetime to GW
#MP EndStruct
#MP Restore GenDDdefs
                    #MP
                    #MP
#MP BeginStruct[IP_CURRENT_EXTREMES]
#MP StructMember[float32, ip_current_max]
#MP StructMember[float32, ip_current_min]
#MP EndStruct
                #MP
#MP BeginStruct[IP_DRIVE_CURRENT_ALERT]
#MP StructMember[float32, current]
#MP StructMember[float32, alert_point]
#MP StructMember[float32, deadband]
#MP StructMember[float32, duration_time]
#MP AlertExtras
#MP StructMember[bool_t, enable]
#MP EndStruct
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP BeginStruct[WORKING_TIMES]
#MP StructMember[u32, since_reset]
#MP StructMember[u32, total_time]
#MP EndStruct
#MP Restore GenDDdefs
                #MP
#MP BeginStruct[BACKUP_CONTROL_SET]
#MP StructMember[u16, selector]
#MP StructMember[s16, p]
#MP StructMember[s16, i]
#MP StructMember[s16, d]
#MP StructMember[s16, padj]
#MP StructMember[s16, beta]
#MP StructMember[s16, poscomp]
#MP StructMember[s16, deadzone]
#MP StructMember[s16, nonlin]
#MP EndStruct
                #MP
                #MP
#MP Save GenDDdefs
#MP BeginStruct[ALERT_LOG]
#MP StructMember[u8, alert_command]
#MP StructMember[time_s, time]
#MP StructMember[u32, data]
#MP EndStruct
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginStruct[DIAGNOSTIC_CONFIGURATION]
#MP StructMember[float32, start_postion]
#MP StructMember[float32, end_position]
#MP StructMember[float32, set_point_rate]
#MP StructMember[u16, sampling_time]
#MP StructMember[u8, direction]
#MP StructMember[u8, option]
#MP EndStruct
                    #MP
#MP BeginStruct[TRAVEL_CALIBRATION]
#MP StructMember[stringv32, cal_location]
#MP StructMember[date_t, cal_date]
#MP StructMember[stringv32, cal_who]
#MP StructMember[s32, stop_hi_pos]
#MP StructMember[s32, stop_lo_pos]
#MP StructMember[u8, cal_type]
#MP StructMember[u8, last_result]
#MP EndStruct
                #MP
#MP BeginStruct[FINAL_VALUE_CUTOFF_HI]
#MP StructMember[bool_t, enable]
#MP StructMember[float32, cutoff_point_hi]
#MP EndStruct
                    #MP
#MP BeginStruct[FINAL_VALUE_CUTOFF_LO]
#MP StructMember[bool_t, enable]
#MP StructMember[float32, cutoff_point_lo]
#MP EndStruct
                #MP
#MP BeginStruct[COMPLETE_STATUS]
#MP StructMember[bitstr1, dev_status_0_c]
#MP StructMember[bitstr1, dev_status_1_c]
#MP StructMember[bitstr1, dev_status_2_c]
#MP StructMember[bitstr1, dev_status_3_c]
#MP StructMember[bitstr1, dev_status_4_c]
#MP StructMember[bitstr1, dev_status_5_c]
#MP StructMember[bitstr1, dev_status_6_c]
#MP StructMember[bitstr1, dev_status_7_c]
#MP StructMember[bitstr1, dev_status_8_c]
#MP StructMember[bitstr1, dev_status_9_c]
#MP StructMember[bitstr1, dev_status_10_c]
#MP StructMember[bitstr1, dev_status_11_c]
#MP StructMember[bitstr1, dev_status_0_h]
#MP StructMember[bitstr1, dev_status_1_h]
#MP StructMember[bitstr1, dev_status_2_h]
#MP StructMember[bitstr1, dev_status_3_h]
#MP StructMember[bitstr1, dev_status_4_h]
#MP StructMember[bitstr1, dev_status_5_h]
#MP StructMember[bitstr1, dev_status_6_h]
#MP StructMember[bitstr1, dev_status_7_h]
#MP StructMember[bitstr1, dev_status_8_h]
#MP StructMember[bitstr1, dev_status_9_h]
#MP StructMember[bitstr1, dev_status_10_h]
#MP StructMember[bitstr1, dev_status_11_h]
#MP EndStruct
                #MP
#MP; This is an example of how to define a simple parameter:
#MP; BeginSimpleParam lists type, upper-case name, and storage attribute (as in GW)
#MP; DefaultSimpleParam specifies default value
#MP BeginSimpleParam[u16, POSITION_TRANSDUCER_TYPE, R]
#MP DefaultSimpleParam ["106"]
#MP EndSimpleParam
                #MP
                #MP
#MP Save GenDDdefs
#MP
#MP Macro DefineXdEnumValueCommon
#MP DefineEnumValue[XD_ERROR_NO_ERROR, 0, "|en|No Error"]
#MP ;;not used DefineEnumValue[16, "|en|16 Unspecified error (to be mapped to Other in Block Error"]
#MP DefineEnumValue[XD_ERROR_GENERAL_ERROR, 17, "|en|General error"]
#MP DefineEnumValue[XD_ERROR_CALIBRATION_ERROR, 18, "|en|Calibration error"]
#MP ;;not used DefineEnumValue[XD_ERROR_CONFIGURATION_ERROR, 19, "|en|Configuration error"]
#MP DefineEnumValue[XD_ERROR_ELECTRONICS_FAILURE, 20, "|en|Electronics Failure"]
#MP DefineEnumValue[XD_ERROR_MECHANICAL_FAILURE, 21, "|en|Mechanical Failure"]
#MP DefineEnumValue[XD_ERROR_I_O_FAILURE, 22, "|en|I/O Failure"]
#MP DefineEnumValue[XD_ERROR_DATA_INTEGRITY_ERROR, 23, "|en|Data Integrity Error"]
#MP DefineEnumValue[XD_ERROR_SOFTWARE_ERROR, 24, "|en|Software Error"]
#MP DefineEnumValue[XD_ERROR_ALGORITHM_ERROR, 25, "|en|Algorithm Error"]
#MP Endm
                #MP
                #MP
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP BeginEnumType[u8, ENUM_XD_ERROR]
#MP DefineXdEnumValueCommon
#MP EndEnumType
                    #MP
#MP ;This is a kludge workaround for DD size mismatch, due perhaps to alignment
#MP ;No_C_code = 2019
#MP ;BeginEnumType[u16, ENUM_XD_ERROR2]
#MP ;DefineXdEnumValueCommon
#MP ;EndEnumType
                    #MP
#MP Setstr DDHelp = "|en|Map of errors reported in COMPLETE_STATUS parameter"
#MP Setstr DDLabel = "|en|XD Error Position"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP BeginSimpleParam[ENUM_XD_ERROR, XD_ERROR_POS, R]
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
#MP Restore GenDDdefs
                #MP
                #MP
#MP; This is an example of how to define a standard record parameter:
#MP; BeginStdRecordParam lists type, upper-case name, and storage attribute (as in GW)
#MP; DefaultRecordParam specifies default value for name, in order, and indicates
#MP; whether it is writable (1) or not (0)
#MP BeginStdRecordParam[FLOAT_S, FINAL_VALUE, RW]
#MP DefaultRecordParam [status, "0", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[SCALE, FINAL_VALUE_RANGE, R]
#MP DefaultRecordParam [eu_100, "100.0", 1]
#MP DefaultRecordParam [eu_0, "0.0", 1]
#MP DefaultRecordParam [units, "1342", 1]
#MP DefaultRecordParam [dec_pt, "2", 1]
#MP EndRecordParam
                #MP
#MP; This is an example of how to define a custom record parameter, whether old or new style:
#MP; BeginRecordParam lists type, upper-case name, and storage attribute (as in GW)
#MP; DefaultRecordParam specifies default value for name, in order, and indicates
#MP; whether it is writable (1) or not (0)
#MP BeginRecordParam[POSITION_LIMITS, POSITION_LIMITS, SRW|MN_A]
#MP DefaultRecordParam [component_0, "0", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP DefaultRecordParam [component_2, "0", 1]
#MP DefaultRecordParam [component_3, "125.0", 1]
#MP DefaultRecordParam [component_4, "125.0", 1]
#MP DefaultRecordParam [component_5, "0", 1]
#MP DefaultRecordParam [component_6, "0", 1]
#MP DefaultRecordParam [component_7, "101.0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[FINAL_VALUE_CUTOFF_HI, FINAL_VALUE_CUTOFF_HI, SRW|MN_A]
#MP DefaultRecordParam [enable, "0", 1]
#MP DefaultRecordParam [cutoff_point_hi, "98.0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[FINAL_VALUE_CUTOFF_LO, FINAL_VALUE_CUTOFF_LO, SRW|MN_A]
#MP DefaultRecordParam [enable, "0", 1]
#MP DefaultRecordParam [cutoff_point_lo, "3.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, FINAL_POSITION_VALUE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x1c", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginSimpleParam[u8, ACTIVATE_CONTROL_SET, VRW]
#MP DefaultSimpleParam ["255"]
#MP EndSimpleParam
                #MP
#MP BeginRecordParam[ACTIVE_CONTROL_SET, ACTIVE_CONTROL_SET, R]
#MP DefaultRecordParam [component_0, "0", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP DefaultRecordParam [component_2, "0", 1]
#MP DefaultRecordParam [component_3, "0", 1]
#MP DefaultRecordParam [component_4, "0", 1]
#MP DefaultRecordParam [component_5, "0", 1]
#MP DefaultRecordParam [component_6, "0", 1]
#MP DefaultRecordParam [component_7, "0", 1]
#MP DefaultRecordParam [component_8, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[CONTROL_SET, CUSTOM_CONTROL_SET, SRW|MN_A]
#MP DefaultRecordParam [component_0, "0", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP DefaultRecordParam [component_2, "0", 1]
#MP DefaultRecordParam [component_3, "0", 1]
#MP DefaultRecordParam [component_4, "0", 1]
#MP DefaultRecordParam [component_5, "0", 1]
#MP DefaultRecordParam [component_6, "0", 1]
#MP DefaultRecordParam [component_7, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[BACKUP_CONTROL_SET, BACKUP_CONTROL_SET, R]
#MP DefaultRecordParam [selector, "0", 1]
#MP DefaultRecordParam [p, "0", 1]
#MP DefaultRecordParam [i, "0", 1]
#MP DefaultRecordParam [d, "0", 1]
#MP DefaultRecordParam [padj, "0", 1]
#MP DefaultRecordParam [beta, "0", 1]
#MP DefaultRecordParam [poscomp, "0", 1]
#MP DefaultRecordParam [deadzone, "0", 1]
#MP DefaultRecordParam [nonlin, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[TRAVEL_CALIBRATION, TRAVEL_CALIBRATION, NRW|MN_N]
#MP DefaultRecordParam [cal_location, "_32_SPACES", 1]
#MP DefaultRecordParam [cal_date, "0,0,0,0,0,0", 1]
#MP DefaultRecordParam [cal_who, "_32_SPACES", 1]
#MP DefaultRecordParam [stop_hi_pos, "0", 1]
#MP DefaultRecordParam [stop_lo_pos, "0", 1]
#MP DefaultRecordParam [cal_type, "0", 1]
#MP DefaultRecordParam [last_result, "0", 1]
#MP EndRecordParam
                #MP
#MP ;-------- requires special storage handling together with alert. Alas!
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP BeginRecordParam[TRAVEL, TRAVEL, SRW|MN_N, "|en|Travel", "|en|Travel Range Info"] ;RW]
#MP Setstr DDLabel = "|en|Travel Range"
#MP Setstr DDHelp = "|en|Scale of 0-100%"
#MP DefaultRecordParam [TravelRange, "100.0", 1]; component_0
#MP Setstr DDLabel = "|en|Travel Units"
#MP DefaultRecordParam [units_index, "1342", 1]; component_1
#MP EndRecordParam
#MP Restore GenDDdefs
                #MP
#MP BeginStdRecordParam[FLOAT_S, WORKING_SP, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, WORKING_POS, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP Setstr LBL_117_DEVIATION_ALERT                 "|en|Deviation Alert"
#MP Setstr HLP_117_DEVIATION_ALERT                 "|en|"
#MP BeginRecordParam[MN_DEVIATION_ALERT, DEVIATION_ALERT, SRW|MN_N, LBL_117_DEVIATION_ALERT, HLP_117_DEVIATION_ALERT, SVI2_DEVIATION_ALERT]
#MP Setstr DDLabel = "|en|Deviation STD" ;don't care
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [__deviation_value, "0.0", 0]
#MP Setstr DDLabel = "|en|Deviation Threshold"
#MP DefaultRecordParam [alert_point, "20.0", SUBX_ACCESS, dev_alert_point]
#MP Setstr DDLabel = "|en|Deadband STD" ;don't care
#MP DefaultRecordParam [__deviation_deadband, "1", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|Deviation Time Threshold"
#MP Setstr DDLabel = "[deviation_time_label]"
#MP Setstr DDHelp = "[deviation_time_help]"
#MP Setstr DDClass = "CONTAINED & SERVICE"
#MP Setstr DDUnits = "CONSTANT_UNIT   [sec];"
#MP DefaultRecordParam [time_threshold, "20", SUBX_ACCESS]
#MP AlertExtrasDefaults
#MP Setstr DDLabel = "|en|Enable"
#MP DefaultRecordParam [enable, "0", SUBX_ACCESS]
#MP EndRecordParam
                #MP
                #MP
#MP Setstr WorkposHelp "|en|Working Position in travel units"
#MP Macro RecordParam_Generic_POSITION_ALERT ;[name, dd_label, alert_point]
    #MP BeginRecordParam[POSITION_ALERT, #1#, SRW|MN_N, #2#, "|en|Pos Alert Configuration"]
    #MP Setstr DDLabel = "|en|Position"
    #MP Setstr DDHelp = "|en|Working Position in travel units"
    #MP Setstr DDClass = "CONTAINED & DYNAMIC"
    #MP DefaultRecordParam [position, "0.0", 0]
    #MP Setstr DDLabel = "|en|Alert Point"
    #MP DefaultRecordParam [alert_point, #3#, SUBX_ACCESS]
    #MP Setstr DDLabel = "|en|Deadband"
    #MP Setstr DDHelp = "|en|Position Alert Deadband"
    #MP Setstr DDClass = "CONTAINED & SERVICE"
    #MP DefaultRecordParam [deadband, "1", SUBX_ACCESS]
    #MP AlertExtrasDefaults
    #MP Setstr DDLabel = "|en|Enable"
    #MP DefaultRecordParam [enable, "0", SUBX_ACCESS]
    #MP EndRecordParam
#MP Endm
                #MP
#MP RecordParam_Generic_POSITION_ALERT[POSITION_HIHI_ALERT, "|en|Pos HiHi Alert", "110.0"]
#MP RecordParam_Generic_POSITION_ALERT[POSITION_HI_ALERT, "|en|Pos Hi Alert", "105.0"]
#MP RecordParam_Generic_POSITION_ALERT[POSITION_LO_ALERT, "|en|Pos Low Alert", "-5.0"]
#MP RecordParam_Generic_POSITION_ALERT[POSITION_LOLO_ALERT, "|en|Pos Low Low Alert", "-10.0"]
                #MP
        		#MP
#MP ;------------- Sync of deadband_ab requires special treatment of storage ---------------
#MP Macro RecordParam_Generic_TRAVEL_ACCUMULATION_ALERT ;[name, dd_label]
    #MP BeginRecordParam[TRAVEL_ALERT, #1#, RW, #2#]
    #MP Setstr DDLabel "|en|Accumulation"
    #MP Setstr DDClass = "CONTAINED & DYNAMIC"
    #MP DefaultRecordParam [travel_accumulation, "0", SUBX_ACCESS]
    #MP Setstr DDLabel = "|en|Alert Point"
    #MP DefaultRecordParam [int_alert_point, "1000000", SUBX_ACCESS]
    #MP Setstr DDLabel = "|en|DeadBand"
    #MP DefaultRecordParam [deadband_ab, "1", SUBX_ACCESS]
    #MP AlertExtrasDefaults
    #MP Setstr DDLabel = "|en|Enable"
    #MP DefaultRecordParam [enable, "0", SUBX_ACCESS]
    #MP EndRecordParam
#MP Endm
#MP Setstr LBL_153_TRAVEL_ACCUMULATION_A_ALERT = "|en|Travel Accumulation A Alert"
#MP RecordParam_Generic_TRAVEL_ACCUMULATION_ALERT[TRAVEL_ACCUMULATION_A_ALERT, LBL_153_TRAVEL_ACCUMULATION_A_ALERT]
#MP ;-- together; see code --
#MP Setstr LBL_160_TRAVEL_ACCUMULATION_B_ALERT = "|en|Travel Accumulation B Alert"
#MP RecordParam_Generic_TRAVEL_ACCUMULATION_ALERT[TRAVEL_ACCUMULATION_B_ALERT, LBL_160_TRAVEL_ACCUMULATION_B_ALERT]
#MP Restore GenDDdefs
                #MP
#MP BeginRecordParam[TREND, TRAVEL_ACCUMULATION_TREND, R, "", ""]
#MP DefaultRecordParam [currently_collected, "0.0", 1]
#MP DefaultRecordParam [today, "0.0", 1]
#MP DefaultRecordParam [last_day, "0.0", 1]
#MP DefaultRecordParam [previous_day, "0.0", 1]
#MP DefaultRecordParam [three_days_ago, "0.0", 1]
#MP DefaultRecordParam [current_week, "0.0", 1]
#MP DefaultRecordParam [last_week, "0.0", 1]
#MP DefaultRecordParam [previous_week, "0.0", 1]
#MP DefaultRecordParam [three_weeks_ago, "0.0", 1]
#MP DefaultRecordParam [current_month, "0.0", 1]
#MP DefaultRecordParam [last_month, "0.0", 1]
#MP DefaultRecordParam [previous_month, "0.0", 1]
#MP DefaultRecordParam [three_months_ago, "0.0", 1]
#MP DefaultRecordParam [current_12_months, "0.0", 1]
#MP DefaultRecordParam [last_12_months, "0.0", 1]
#MP DefaultRecordParam [previous_12_months, "0.0", 1]
#MP DefaultRecordParam [three_years_ago, "0.0", 1]
#MP EndRecordParam
                #MP
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP ;------------- Sync of deadband_ab requires special treatment of storage ---------------
#MP Macro RecordParam_Generic_CYCLE_COUNTER_ALERT ;[name, dd_label, dd_name.opt]
    #MP If #0#>2
        #MP BeginRecordParam[CYCLE_COUNTER_ALERT, #1#, RW, #2#, "|en|", #3#]
    #MP Else
        #MP BeginRecordParam[CYCLE_COUNTER_ALERT, #1#, RW, #2#, "|en|"]
    #MP Endif
    #MP Setstr DDLabel = "|en|Cycles"
    #MP Setstr DDHelp = "|en|Number of times the travel changes the direction"
    #MP Setstr DDClass = "CONTAINED & DYNAMIC"
    #MP DefaultRecordParam [cycle_counter, "0", SUBX_ACCESS]
    #MP Setstr DDLabel = "|en|Alert Point"
    #MP Setstr DDHelp = "|en|Threshold for setting the alert"
    #MP DefaultRecordParam [int_alert_point, "10000", SUBX_ACCESS]
    #MP Setstr DDLabel = "|en|DeadBand"
    #MP DefaultRecordParam [deadband_ab, "1", SUBX_ACCESS]
    #MP AlertExtrasDefaults
    #MP Setstr DDLabel = "|en|Enable"
    #MP DefaultRecordParam [enable, "0",SUBX_ACCESS]
    #MP EndRecordParam
#MP Endm
#MP Setstr LBL_185_CYCLE_COUNTER_A_ALERT = "|en|Cycle Counter A Alert"
#MP RecordParam_Generic_CYCLE_COUNTER_ALERT[CYCLE_COUNTER_A_ALERT, LBL_185_CYCLE_COUNTER_A_ALERT, SVI2_CYCLE_COUNTER_A_ALERT]
#MP ;-- together; see code --
#MP Setstr LBL_192_CYCLE_COUNTER_B_ALERT = "|en|Cycle Counter B Alert"
#MP RecordParam_Generic_CYCLE_COUNTER_ALERT[CYCLE_COUNTER_B_ALERT, LBL_192_CYCLE_COUNTER_B_ALERT]
#MP Restore GenDDdefs
                #MP
#MP BeginRecordParam[TREND, CYCLE_COUNTER_TREND, R, "", ""]
#MP DefaultRecordParam [currently_collected, "0.0", 1]
#MP DefaultRecordParam [today, "0.0", 1]
#MP DefaultRecordParam [last_day, "0.0", 1]
#MP DefaultRecordParam [previous_day, "0.0", 1]
#MP DefaultRecordParam [three_days_ago, "0.0", 1]
#MP DefaultRecordParam [current_week, "0.0", 1]
#MP DefaultRecordParam [last_week, "0.0", 1]
#MP DefaultRecordParam [previous_week, "0.0", 1]
#MP DefaultRecordParam [three_weeks_ago, "0.0", 1]
#MP DefaultRecordParam [current_month, "0.0", 1]
#MP DefaultRecordParam [last_month, "0.0", 1]
#MP DefaultRecordParam [previous_month, "0.0", 1]
#MP DefaultRecordParam [three_months_ago, "0.0", 1]
#MP DefaultRecordParam [current_12_months, "0.0", 1]
#MP DefaultRecordParam [last_12_months, "0.0", 1]
#MP DefaultRecordParam [previous_12_months, "0.0", 1]
#MP DefaultRecordParam [three_years_ago, "0.0", 1]
#MP EndRecordParam
                #MP
#MP ;trends and histograms to file(s)?
#MP BeginRecordParam[ERR_TREND, POSITION_ERROR_TREND, R, "", ""]
#MP DefaultRecordParam [currently_collected, "0.0", 1]
#MP DefaultRecordParam [today, "0.0", 1]
#MP DefaultRecordParam [last_day, "0.0", 1]
#MP DefaultRecordParam [previous_day, "0.0", 1]
#MP DefaultRecordParam [three_days_ago, "0.0", 1]
#MP DefaultRecordParam [current_week, "0.0", 1]
#MP DefaultRecordParam [last_week, "0.0", 1]
#MP DefaultRecordParam [previous_week, "0.0", 1]
#MP DefaultRecordParam [three_weeks_ago, "0.0", 1]
#MP DefaultRecordParam [current_month, "0.0", 1]
#MP DefaultRecordParam [last_month, "0.0", 1]
#MP DefaultRecordParam [previous_month, "0.0", 1]
#MP DefaultRecordParam [three_months_ago, "0.0", 1]
#MP DefaultRecordParam [current_12_months, "0.0", 1]
#MP DefaultRecordParam [last_12_months, "0.0", 1]
#MP DefaultRecordParam [previous_12_months, "0.0", 1]
#MP DefaultRecordParam [three_years_ago, "0.0", 1]
#MP EndRecordParam
                #MP
#MP Ifdef OPTION_HISTOGRAM_SELECTION_POSITION__READONLY
	#MP memopt = R
    #MP subx_access = 0
#MP Else
	#MP memopt = RW
    #MP subx_access = SUBX_ACCESS
#MP Endif
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP Setstr LBL_235_POSITION_HISTOGRAM              "|en|Position Histogram"
#MP Setstr HLP_235_POSITION_HISTOGRAM  "|en|An array of counters, that will count how many macro cycles the valve"
#MP Setstr HLP_235_POSITION_HISTOGRAM HLP_235_POSITION_HISTOGRAM  " was in different position segments. The counters should increase only if the"
#MP Setstr HLP_235_POSITION_HISTOGRAM HLP_235_POSITION_HISTOGRAM   " device is under control - the transducer block is in AUTO mode and the quality"
#MP Setstr HLP_235_POSITION_HISTOGRAM HLP_235_POSITION_HISTOGRAM   " of the set point is GOOD."
#MP BeginRecordParam[POS_HISTOGRAM, POSITION_HISTOGRAM, memopt, LBL_235_POSITION_HISTOGRAM, HLP_235_POSITION_HISTOGRAM] ;Only underlying data is stored in NVMEM
#MP Undef memopt ;cleanup
#MP Setstr DDLabel "|en|Total Time"
#MP Setstr HLP_236_TOTAL "|en|Total time since the reset for the values in the histogram"
#MP Setstr DDHelp HLP_236_TOTAL
#MP Setstr DDUnits "CONSTANT_UNIT [unit_code_1054];"
#MP DefaultRecordParam [total_time, "0", subx_access] ;component_0
#MP Undef subx_access ;cleanup
#MP Setstr DDLabel = LBL_POS_5_PERCENT_CLOSED
#MP DefaultRecordParam [pos_5_percent_closed, "0.0", 0] ;component_1
#MP Setstr DDLabel = LBL_POS_10_PERCENT
#MP DefaultRecordParam [pos_10_percent, "0.0", 0] ;component_2
#MP Setstr DDLabel = LBL_POS_20_PERCENT
#MP DefaultRecordParam [pos_20_percent, "0.0", 0] ;component_3
#MP Setstr DDLabel = LBL_POS_30_PERCENT
#MP DefaultRecordParam [pos_30_percent, "0.0", 0] ;component_4
#MP Setstr DDLabel = LBL_POS_40_PERCENT
#MP DefaultRecordParam [pos_40_percent, "0.0", 0] ;component_5
#MP Setstr DDLabel = LBL_POS_50_PERCENT
#MP DefaultRecordParam [pos_50_percent, "0.0", 0] ;component_6
#MP Setstr DDLabel = LBL_POS_60_PERCENT
#MP DefaultRecordParam [pos_60_percent, "0.0", 0] ;component_7
#MP Setstr DDLabel = LBL_POS_70_PERCENT
#MP DefaultRecordParam [pos_70_percent, "0.0", 0] ;component_8
#MP Setstr DDLabel = LBL_POS_80_PERCENT
#MP DefaultRecordParam [pos_80_percent, "0.0", 0] ;component_9
#MP Setstr DDLabel = LBL_POS_90_PERCENT
#MP DefaultRecordParam [pos_90_percent, "0.0", 0] ;component_10
#MP Setstr DDLabel = LBL_POS_95_PERCENT
#MP DefaultRecordParam [pos_95_percent, "0.0", 0] ;component_11
#MP Setstr DDLabel = LBL_POS_95_PERCENT_OPEN
#MP DefaultRecordParam [pos_95_percent_open, "0.0", 0] ;component_12
#MP EndRecordParam
                #MP
#MP Restore GenDDdefs
                #MP
#MP ;Ref#15892.
#MP ;All members are Static *except* alert
#MP ;Because of the exception, the object is N (not S) and ST_REV is handled manually
#MP BeginRecordParam[NEAR_CLOSED_ALERT, NEAR_CLOSED_ALERT, NRW|MN_N, "", ""]
#MP DefaultRecordParam [position_closed, "0.0", 1]
#MP DefaultRecordParam [near_closed, "0", 1]
#MP DefaultRecordParam [alert_point, "2000", 1]
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "1", 1]
#MP EndRecordParam
                #MP
#MP Ifdef OPTION_HISTOGRAM_SELECTION_POSERR__READONLY
	#MP memopt = R
    #MP subx_access = 0
#MP Else
	#MP memopt = RW
    #MP subx_access = SUBX_ACCESS
#MP Endif
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP Setstr LBL_255_POSITION_ERROR_HISTOGRAM        "|en|Position Error Histogram"
#MP Setstr HLP_255_POSITION_ERROR_HISTOGRAM "|en|Each bucket keeps average absolute error of working position over time the position spent within the bucket. "
#MP Setstr HLP_255_POSITION_ERROR_HISTOGRAM HLP_255_POSITION_ERROR_HISTOGRAM "It may overflow in 13 years or so and thus may need to be cleared once in a while."
#MP BeginRecordParam[POS_ERR_HISTOGRAM, POSITION_ERROR_HISTOGRAM, memopt, LBL_255_POSITION_ERROR_HISTOGRAM, HLP_255_POSITION_ERROR_HISTOGRAM] ;Only underlying data is stored in NVMEM
#MP Undef memopt ;cleanup
#MP Setstr DDLabel LBL_POS_5_PERCENT_CLOSED
#MP DefaultRecordParam [pos_5_percent_closed, "0.0", subx_access] ;component_0
#MP Setstr DDLabel LBL_POS_10_PERCENT
#MP DefaultRecordParam [pos_10_percent, "0.0", subx_access] ;component_1
#MP Setstr DDLabel LBL_POS_20_PERCENT
#MP DefaultRecordParam [pos_20_percent, "0.0", subx_access] ;component_2
#MP Setstr DDLabel LBL_POS_30_PERCENT
#MP DefaultRecordParam [pos_30_percent, "0.0", subx_access] ;component_3
#MP Setstr DDLabel LBL_POS_40_PERCENT
#MP DefaultRecordParam [pos_40_percent, "0.0", subx_access] ;component_4
#MP Setstr DDLabel LBL_POS_50_PERCENT
#MP DefaultRecordParam [pos_50_percent, "0.0", subx_access] ;component_5
#MP Setstr DDLabel LBL_POS_60_PERCENT
#MP DefaultRecordParam [pos_60_percent, "0.0", subx_access] ;component_6
#MP Setstr DDLabel LBL_POS_70_PERCENT
#MP DefaultRecordParam [pos_70_percent, "0.0", subx_access] ;component_7
#MP Setstr DDLabel LBL_POS_80_PERCENT
#MP DefaultRecordParam [pos_80_percent, "0.0", subx_access] ;component_8
#MP Setstr DDLabel LBL_POS_90_PERCENT
#MP DefaultRecordParam [pos_90_percent, "0.0", subx_access] ;component_9
#MP Setstr DDLabel LBL_POS_95_PERCENT
#MP DefaultRecordParam [pos_95_percent, "0.0", subx_access] ;component_10
#MP Setstr DDLabel LBL_POS_95_PERCENT_OPEN
#MP DefaultRecordParam [pos_95_percent_open, "0.0", subx_access] ;component_11
#MP Undef subx_access ;cleanup
#MP EndRecordParam
                #MP
#MP Setstr LBL_268_SETPOINT_TIMEOUT_ALERT          "|en|Setpoint Timeout Alert"
#MP Setstr HLP_268_SETPOINT_TIMEOUT_ALERT "|en|The alert is active if controlling FB (AO or DO) has not updated final value for longer than ALERT_POINT time"
#MP BeginRecordParam[SETPOINT_TIMEOUT_ALERT, SETPOINT_TIMEOUT_ALERT, SRW|MN_N, LBL_268_SETPOINT_TIMEOUT_ALERT, HLP_268_SETPOINT_TIMEOUT_ALERT]
#MP Setstr DDHelp = "|en|Time since final value last updated"
#MP Setstr DDLabel = "|en|Time Since Update"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP Setstr DDUnits "CONSTANT_UNIT [unit_code_1054];"
#MP DefaultRecordParam [time_since_update, "0.0", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|Time Limit"
#MP Setstr DDHelp = "|en|Time threshold to trigger the alert" ;
#MP DefaultRecordParam [alert_point, "20.0", SUBX_ACCESS, setpoint_alert_point] ;need unique name for DD
#MP Setstr DDLabel = "|en|Max Observed"
#MP Setstr DDHelp = "|en|Maximum seen gap between final value updates"
#MP DefaultRecordParam [setpoint_max_time, "0.0", SUBX_ACCESS]
#MP AlertExtrasDefaults
#MP Setstr DDLabel = "|en|Enable"
#MP DefaultRecordParam [enable, "0", SUBX_ACCESS]
#MP EndRecordParam
                #MP
#MP Restore GenDDdefs
                #MP
#MP BeginRecordParam[XD_FSTATE, XD_FSTATE, SRW|MN_N, "", ""]
#MP DefaultRecordParam [component_0, "2", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP DefaultRecordParam [component_2, "0.0", 1]
#MP DefaultRecordParam [component_3, "600", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[CHAR_TYPE, CHAR_SELECTION, SRW|MN_A, "", ""]
#MP DefaultRecordParam [component_0, "5", 1]
#MP DefaultRecordParam [component_1, "19", 1]
#MP EndRecordParam
                #MP
#MP BeginArrayParam[s16, CURRENT_CHAR_POINTS, 38, R]
#MP DefaultArrayParams[0, 1, "0"]
#MP DefaultArrayParams[2, 37, "1600"]
#MP EndArrayParam
                #MP
#MP BeginRecordParam[CHAR_TYPE, CUSTOM_CHAR, RW, "", ""]
#MP DefaultRecordParam [component_0, "255", 1]
#MP DefaultRecordParam [component_1, "19", 1]
#MP EndRecordParam
                #MP
#MP BeginArrayParam[s16, CUSTOM_CHAR_POINTS, 38, RW]
#MP DefaultArrayParams[0, 1, "0"]
#MP DefaultArrayParams[2, 37, "1600"]
#MP EndArrayParam
                #MP
#MP BeginSimpleParam[u8, READBACK_SELECT, SRW|MN_N]
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
                #MP
#MP BeginSimpleParam[u16, TRANSDUCER_TYPE, R]
#MP DefaultSimpleParam ["100"]
#MP EndSimpleParam
                #MP
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP Setstr DDHelp = "|en|Pressure Transducer Error"
#MP Setstr DDLabel = "|en|XD Error Pressure"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP BeginSimpleParam[ENUM_XD_ERROR, XD_ERROR_PRESSURE, R] ;kludge for DD size mismatch
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginStdRecordParam[FLOAT_S, SUPPLY_PRESSURE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x1c", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[SCALE, PRESSURE_RANGE, SRW|MN_A] ;nothing to store in FFP
#MP DefaultRecordParam [eu_100, "1034.2", 0]
#MP DefaultRecordParam [eu_0, "0.0", 0]
#MP DefaultRecordParam [units, "1133", 1] ;Any valid units would do
#MP DefaultRecordParam [dec_pt, "3", 1]
#MP EndRecordParam
                #MP
#MP ;All members are Static *except* alert
#MP ;Because of the exception, the object is N (not S) and ST_REV is handled manually
#MP BeginRecordParam[SYSTEM_ALERT, SUPPLY_PRESSURE_HI_ALERT, NRW|MN_N]
#MP DefaultRecordParam [curr_value, "0.0", 0|SUBX_NOPARAMWRAP] ;component_0
#MP DefaultRecordParam [alert_point, "1034.2", 1] ;component_1
#MP DefaultRecordParam [deadband, "0.5", 1] ;component_2
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1] ;component_5
#MP EndRecordParam
                #MP
#MP ;All members are Static *except* alert
#MP ;Because of the exception, the object is N (not S) and ST_REV is handled manually
#MP BeginRecordParam[SYSTEM_ALERT, SUPPLY_PRESSURE_LO_ALERT, SRW|MN_N]
#MP DefaultRecordParam [curr_value, "149.0", 0|SUBX_NOPARAMWRAP] ;component_0
#MP DefaultRecordParam [alert_point, "20", 1] ;component_1
#MP DefaultRecordParam [deadband, "0.5", 1] ;component_2
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1] ;component_5
#MP EndRecordParam
                #MP
#MP ;All members are Static *except* component_3
#MP ;Because of the exception, the object is N (not S) and ST_REV is handled manually
#MP BeginRecordParam[SYSTEM_ALERT, SUPPLY_PRESSURE_LOLO_ALERT, NRW|MN_N]
#MP DefaultRecordParam [curr_value, "149.0", 0|SUBX_NOPARAMWRAP] ;component_0
#MP DefaultRecordParam [alert_point, "20", 1] ;component_1
#MP DefaultRecordParam [deadband, "0.5", 1] ;component_2
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1] ;component_5
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, ACTUATOR_A_PRESSURE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "50.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, ACTUATOR_B_PRESSURE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "50.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, ATMOSPHERIC_PRESSURE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "50.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, PILOT_PRESSURE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginSimpleParam[u16, TEMP_TRANSDUCER_TYPE, R]
#MP DefaultSimpleParam ["101"]
#MP EndSimpleParam
                #MP
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP Setstr DDHelp = "|en|Temperature Transducer Error"
#MP Setstr DDLabel = "|en|XD Error Temperature"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP BeginSimpleParam[ENUM_XD_ERROR, XD_ERROR_TEMPERATURE, R] ;kludge for DD size mismatch
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginStdRecordParam[FLOAT_S, TEMPERATURE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "20.0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[SYSTEM_ALERT, TEMPERATURE_HI_ALERT, SRW|MN_N]
#MP DefaultRecordParam [curr_value, "-45.0", 0|SUBX_NOPARAMWRAP] ;component_0
#MP DefaultRecordParam [alert_point, "85.0", 1] ;component_1
#MP DefaultRecordParam [deadband, "2.0", 1] ;component_2
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1] ;component_5
#MP EndRecordParam
                #MP
#MP BeginRecordParam[SYSTEM_ALERT, TEMPERATURE_LO_ALERT, SRW|MN_N]
#MP DefaultRecordParam [curr_value, "85.0", 0|SUBX_NOPARAMWRAP] ;component_0
#MP DefaultRecordParam [alert_point, "-40.0", 1] ;component_1
#MP DefaultRecordParam [deadband, "2.0", 1] ;component_2
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1] ;component_5
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, IP_DRIVE_CURRENT, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "50.0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[IP_DRIVE_CURRENT_ALERT, IP_DRIVE_CURRENT_HI_ALERT, SRW|MN_N]
#MP DefaultRecordParam [current, "0.0", 0|SUBX_NOPARAMWRAP]
#MP DefaultRecordParam [alert_point, "100", 1]
#MP DefaultRecordParam [deadband, "5.0", 1]
#MP DefaultRecordParam [duration_time, "60.0", 1]
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[IP_DRIVE_CURRENT_ALERT, IP_DRIVE_CURRENT_LO_ALERT, SRW|MN_N]
#MP DefaultRecordParam [current, "100.0", 0|SUBX_NOPARAMWRAP]
#MP DefaultRecordParam [alert_point, "0.0", 1]
#MP DefaultRecordParam [deadband, "5.0", 1]
#MP DefaultRecordParam [duration_time, "60.0", 1]
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginSimpleParam[u8, FIND_STOPS, VRW]
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
                        #MP
    #MP ;NOTE: Protection/lock bits below 13 are as in Release 2; Some, e.g. 10, are suspicious!
#MP Macro OfflineDiag_4_5 ;Common for DD ver.5 and ver 4
#MP DefineAdvDiag[-1, DIAG_NOT_RUNNING, 0, "|en|0. Not Running"]
#MP DefineAdvDiag[0, DIAG_EXEC_SIGNATURE, 1, "|en|1. Execute signature"]
#MP DefineAdvDiag[1, DIAG_EXEC_RAMP_TEST, 2, "|en|2. Execute Ramp test"]
#MP DefineAdvDiag[2, DIAG_SAVE_AS_BASELINE, 3, "|en|3. Save as Baseline"]
#MP DefineAdvDiag[3, DIAG_SAVE_AS_CUSTOM, 4, "|en|4. Save as Custom"]
#MP DefineAdvDiag[4, DIAG_SAVE_AS_CURRENT, 5, "|en|5. Save as Current"]
#MP DefineAdvDiag[5, DIAG_PREPARE_BASELINE_FOR_UPLOAD, 6, "|en|6. Prepare Baseline for Upload"]
#MP DefineAdvDiag[6, DIAG_PREPARE_CUSTOM_FOR_UPLOAD, 7, "|en|7. Prepare Custom for Upload"]
#MP DefineAdvDiag[7, DIAG_PREPARE_CURRENT_FOR_UPLOAD, 8, "|en|8. Prepare Current for Upload"]
#MP DefineAdvDiag[8, DIAG_EXECUTE_STEP_TEST, 9, "|en|9. Execute Step Test"]
#MP DefineAdvDiag[10, DIAG_CANCEL_TEST, 99, "|en|99. Cancel"]
#MP DefineAdvDiag[-1, DIAG_RUNNING, 100, "|en|100. Running"]
#MP Endm
                        #MP
                        #MP
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP BeginAdvDiags[ENUM_OFFLINE_DIAGNOSTIC]
#MP OfflineDiag_4_5
#MP DefineAdvDiag[-1, DIAG_SAVE_AS_FACTORY, 10] ;Missing DD text means "exclude from DD"
#MP DefineAdvDiag[-1, DIAG_FINISHED, 101, "|en|101. Finished"]
#MP DefineAdvDiag[12, DIAG_DATAHOG_START_REV2COMPAT, 98] ;Rev2 style is still supported but remains undocumented and becomes deprecated:, "|en|98. Start data collection (temporary config"]
#MP DefineAdvDiag[11, DIAG_DATAHOG_STOP, 97, "|en|97. Stop data collection"]
#MP DefineAdvDiag[12, DIAG_DATAHOG_PRECONF, 92, "|en|92. Start data collection (preconfigured)"]
#MP DefineAdvDiag[12, DIAG_DATAHOG_START, 91, "|en|91. Start data collection (temporary config)"]
#MP DefineAdvDiag[13, DIAG_PST_START, 90, "|en|90. Start Partial Stroke Test"]
#MP DefineAdvDiag[14, DIAG_ENABLE_WRITE_BUFFER, 94]
#MP DefineAdvDiag[-1, DIAG_CLEAR_TREND_TRAVEL, 55, "|en|Clear Travel Accum. Trend"]
#MP DefineAdvDiag[-1, DIAG_CLEAR_TREND_CYCLE_COUNT, 56, "|en|Clear Cycle Counter Trend"]
#MP DefineAdvDiag[-1, DIAG_CLEAR_TREND_POS_ERROR, 57, "|en|Clear Position Error Trend"]
#MP DefineAdvDiag[-1, DIAG_CLEAR_POSITION_HISTOGRAM, 58, "|en|Clear Position Histogram"]
#MP DefineAdvDiag[-1, DIAG_CLEAR_POS_ERROR_HISTOGRAM, 59, "|en|Clear Position Error Histogram"]
#MP DefineAdvDiag[-1, DIAG_CLEAR_WORKING_TIMES, 60, "|en|Clear Working Times"]
#MP Setstr valnote = "Enables writes to diagnostic buffer. Not useful yet, but no harm"
#MP If NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST == OPTION_ON
	#MP Setstr valnote = "Not implemented correctly and shall not be used"
	#MP Setstr valnote = "Not implemented correctly and shall not be used"
	#MP DefineAdvDiag[14, DIAG_READ_NVMEM_TO_BUFFER, 93]
	#MP Setstr valnote = "Not implemented correctly and shall not be used"
	#MP DefineAdvDiag[14, DIAG_TRANSLATE_BUFFER, 95]
	#MP Setstr valnote = "Not implemented correctly and shall not be used"
	#MP DefineAdvDiag[14, DIAG_COMMIT_BUFFER_TO_NVMEM, 96]
#MP Endif ;NVMEM_IMAGE_CAN_BE_WRITTEN_BY_HOST
#MP EndAdvDiags
                        #MP
                        #MP
#MP Setstr DDHelp = "|en|Offline valve diagnostic procedure command and status."
#MP Setstr DDHelp = DDHelp "\nWriting to this parameter will trigger the requested procedure."
#MP Setstr DDHelp = DDHelp   "\nReading this parameter will provide the status of the last OffLine Procedure"
#MP Setstr DDHelp = DDHelp   "\nNot Running"
#MP Setstr DDHelp = DDHelp   "\nRunning"
#MP DDHelp = 5
#MP Setstr DDLabel = "|en|Offline Diagnostic"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP BeginSimpleParam[ENUM_OFFLINE_DIAGNOSTIC, OFFLINE_DIAGNOSTIC, VRW]
#MP DefaultSimpleParam ["0x00"]
#MP EndSimpleParam
                        #MP
#MP Undef GenDDdefs
                        #MP
                        #MP
                        #MP
#MP BeginRecordParam[DIAGNOSTIC_CONFIGURATION, DIAGNOSTIC_CONFIGURATION, VRW]
#MP DefaultRecordParam [start_postion, "10.0", 1]
#MP DefaultRecordParam [end_position, "90.0", 1]
#MP DefaultRecordParam [set_point_rate, "2.0", 1]
#MP DefaultRecordParam [sampling_time, "50", 1]
#MP DefaultRecordParam [direction, "0x01", 1]
#MP DefaultRecordParam [option, "0x01", 1]
#MP EndRecordParam
                #MP
#MP; This is an example of how to define an array parameter:
#MP; BeginArrayParam lists type, upper-case name, number of elements, and storage attribute (as in GW)
#MP; DefaultArrayParams specifies range of indices and common default value for them, in order,
#MP; and indicates whether it is writable (1) or not (0)
#MP BeginArrayParam[u16, DIAGNOSTIC_DATA, 27, RW]
#MP DefaultArrayParams[0, 0, "0xFFFF"]
#MP DefaultArrayParams[1, 26, "0"]
#MP EndArrayParam
                #MP
#MP BeginRecordParam[AUTOTUNE, AUTOTUNE, VRW]
#MP DefaultRecordParam [component_0, "0.0", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP DefaultRecordParam [component_2, "1", 1]
#MP DefaultRecordParam [component_3, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[CHECK_PROCESS, CHECK_PROCESS, R]
#MP DefaultRecordParam [component_0, "0", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[UI_CUST_CONF, UI_CUSTOM_CONFIGURATION, SRW|MN_N]
#MP DefaultRecordParam [component_0, "1", 1]
#MP DefaultRecordParam [component_1, "2", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[FAILED_STATE, FAILED_STATE, SRW|MN_N]
#MP DefaultRecordParam [ff, "0", 1]
#MP DefaultRecordParam [app, "0", 1]
#MP DefaultRecordParam [propagate_mode, "1", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, FINAL_VALUE_D, RW]
#MP DefaultRecordParam [status, "0x00", 1]
#MP DefaultRecordParam [value, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, FINAL_POSITION_VALUE_D, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, FINAL_VALUE_DINT, RW]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, FINAL_POSITION_VALUE_DINT, R|MN_DYN]
#MP DefaultRecordParam [status, "0x1c", 1]
#MP DefaultRecordParam [value, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, DISCRETE_OUTPUT_1_STATE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x1c", 1]
#MP DefaultRecordParam [value, "1", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, DISCRETE_OUTPUT_2_STATE, R|MN_DYN]
#MP DefaultRecordParam [status, "0x1c", 1]
#MP DefaultRecordParam [value, "1", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[DISC_S, DISCRETE_INPUT, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[STRUCT2_U8, DISCRETE_SWITCH_1_CONF, SRW|MN_N]
#MP DefaultRecordParam [component_0, "0x80", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[STRUCT2_U8, DISCRETE_SWITCH_2_CONF, SRW|MN_N]
#MP DefaultRecordParam [component_0, "0x80", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[UI_ACCESS_CTRL, UI_ACCESS_CONTROL, SRW|MN_A]
#MP DefaultRecordParam [component_0, "0", 1]
#MP DefaultRecordParam [component_1, "0", 1]
#MP DefaultRecordParam [component_2, "8888", 1]
#MP EndRecordParam
                #MP
#MP BeginSimpleParam[u8, UI_LANGUAGE, SRW|MN_A]
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
                #MP
#MP BeginSimpleParam[u8, APP_MODE, RW]
#MP DefaultSimpleParam ["0x03"]
#MP EndSimpleParam
                #MP
#MP BeginRecordParam[COMPLETE_STATUS, COMPLETE_STATUS, R]
#MP DefaultRecordParam [dev_status_0_c, "0", 1]
#MP DefaultRecordParam [dev_status_1_c, "0", 1]
#MP DefaultRecordParam [dev_status_2_c, "0", 1]
#MP DefaultRecordParam [dev_status_3_c, "0", 1]
#MP DefaultRecordParam [dev_status_4_c, "0", 1]
#MP DefaultRecordParam [dev_status_5_c, "0", 1]
#MP DefaultRecordParam [dev_status_6_c, "0", 1]
#MP DefaultRecordParam [dev_status_7_c, "0", 1]
#MP DefaultRecordParam [dev_status_8_c, "0", 1]
#MP DefaultRecordParam [dev_status_9_c, "0", 1]
#MP DefaultRecordParam [dev_status_10_c, "0", 1]
#MP DefaultRecordParam [dev_status_11_c, "0", 1]
#MP DefaultRecordParam [dev_status_0_h, "0", 1]
#MP DefaultRecordParam [dev_status_1_h, "0", 1]
#MP DefaultRecordParam [dev_status_2_h, "0", 1]
#MP DefaultRecordParam [dev_status_3_h, "0", 1]
#MP DefaultRecordParam [dev_status_4_h, "0", 1]
#MP DefaultRecordParam [dev_status_5_h, "0", 1]
#MP DefaultRecordParam [dev_status_6_h, "0", 1]
#MP DefaultRecordParam [dev_status_7_h, "0", 1]
#MP DefaultRecordParam [dev_status_8_h, "0", 1]
#MP DefaultRecordParam [dev_status_9_h, "0", 1]
#MP DefaultRecordParam [dev_status_10_h, "0", 1]
#MP DefaultRecordParam [dev_status_11_h, "0", 1]
#MP EndRecordParam
                #MP
#MP BeginSimpleParam[u8, CLEAR_STATUS, RW]
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
                #MP
#MP BeginSimpleParam[float32, OPEN_STOP_ADJUSTMENT, SRW|MN_A]
#MP DefaultSimpleParam ["100.0"]
#MP EndSimpleParam
                #MP
#MP BeginSimpleParam[u8, SETPOINT_SOURCE, SRW|MN_N]
#MP DefaultSimpleParam ["1"]
#MP EndSimpleParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, SETPOINT, R]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginStdRecordParam[FLOAT_S, ACTUAL_POSITION, R|MN_DYN]
#MP DefaultRecordParam [status, "0x4f", 1]
#MP DefaultRecordParam [value, "0.0", 1]
#MP EndRecordParam
                #MP
#MP BeginSimpleParam[s32, RAW_POSITION, R]
#MP DefaultSimpleParam ["0x00"]
#MP EndSimpleParam
                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5) |(1<<4) ; for DD ver 5
#MP BeginRecordParam[ALERT_ACTION, ALERT_ACTION, SRW|MN_N, "|en|Alert Action", "|en|Configures effect on block error and on start of data collection"]
#MP Setstr DDLabel "|en|Mapping to block_err"
#MP DefaultRecordParam [block_err_map, "0x03", 1] ;Apportion per FF spec
#MP Setstr DDLabel "|en|Deviation Alert"
#MP DefaultRecordParam [deviation_alert_act, "0x02", 1, deviation_alert_act]
#MP DefaultRecordParam [position_hihi_alert_act, "0x02", 1, position_hihi_alert_act]
#MP DefaultRecordParam [position_hi_alert_act, "0x01", 1, position_hi_alert_act]
#MP DefaultRecordParam [position_lo_alert_act, "0x01", 1, position_lo_alert_act]
#MP DefaultRecordParam [position_lolo_alert_act, "0x02", 1, position_lolo_alert_act]
#MP DefaultRecordParam [setpoint_timeout_alert_act, "0x02", 1, setpoint_timeout_alert_act]
#MP DefaultRecordParam [near_close_alert_act, "0x01", 1, near_close_alert_act]
#MP DefaultRecordParam [travel_accumulation_a_alert_act, "0x01", 1, travel_accumulation_a_alert_act]
#MP DefaultRecordParam [travel_accumulation_b_alert_act, "0x01", 1, travel_accumulation_b_alert_act]
#MP DefaultRecordParam [cycle_counter_a_alert_act, "0x02", 1, cycle_counter_a_alert_act]
#MP DefaultRecordParam [cycle_counter_b_alert_act, "0x02", 1, cycle_counter_b_alert_act]
#MP DefaultRecordParam [working_time_alert_act, "0x01", 1, working_time_alert_act]
#MP DefaultRecordParam [supply_pressure_hi_alert_act, "0x02", 1, supply_pressure_hi_alert_act]
#MP DefaultRecordParam [supply_pressure_lo_alert_act, "0x00", 1, supply_pressure_lo_alert_act]
#MP DefaultRecordParam [supply_pressure_lolo_alert_act, "0x00", 1, supply_pressure_lolo_alert_act]
#MP DefaultRecordParam [temperature_hi_alert_act, "0x01", 1, temperature_hi_alert_act]
#MP DefaultRecordParam [temperature_lo_alert_act, "0x01", 1, temperature_lo_alert_act]
#MP DefaultRecordParam [ip_drive_current_alert_hi_act, "0x00", 1, ip_drive_current_alert_hi_act]
#MP DefaultRecordParam [ip_drive_current_alert_lo_act, "0x00", 1, ip_drive_current_alert_lo_act]
#MP DefaultRecordParam [sensor_failure_alert_act, "0x03", 1, sensor_failure_alert_act]
#MP DefaultRecordParam [processor_alert_act, "0x03", 1, processor_alert_act]
#MP DefaultRecordParam [valve_control_alert_act, "0x00", 1, valve_control_alert_act]
#MP DefaultRecordParam [commissioning_alert_act, "0x01", 1, commissioning_alert_act]
#MP DefaultRecordParam [air_supply_alert_act, "0x00", 1, air_supply_alert_act]
#MP DefaultRecordParam [supporting_hardware_alert_act, "0x01", 1, supporting_hardware_alert_act]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[ALERT_STATE, ALERT_STATE, R, "|en|Alerts State"]
#MP Setstr DDLabel "|en|Deviation Alert"
#MP Setstr DDClass "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [deviation_alert_st, "0", 0, deviation_alert_st]
#MP DefaultRecordParam [position_hihi_alert_st, "0", 0, position_hihi_alert_st]
#MP DefaultRecordParam [position_hi_alert_st, "0", 0, position_hi_alert_st]
#MP DefaultRecordParam [position_lo_alert_st, "0", 0, position_lo_alert_st]
#MP DefaultRecordParam [position_lolo_alert_st, "0", 0, position_lolo_alert_st]
#MP DefaultRecordParam [setpoint_timeout_alert_st, "0", 0, setpoint_timeout_alert_st]
#MP DefaultRecordParam [near_close_alert_st, "0", 0, near_close_alert_st]
#MP DefaultRecordParam [travel_accumulation_a_alert_st, "0", 0, travel_accumulation_a_alert_st]
#MP DefaultRecordParam [travel_accumulation_b_alert_st, "0", 0, travel_accumulation_b_alert_st]
#MP DefaultRecordParam [cycle_counter_a_alert_st, "0", 0, cycle_counter_a_alert_st]
#MP DefaultRecordParam [cycle_counter_b_alert_st, "0", 0, cycle_counter_b_alert_st]
#MP DefaultRecordParam [working_time_alert_st, "0", 0, working_time_alert_st]
#MP DefaultRecordParam [supply_pressure_hi_alert_st, "0", 0, supply_pressure_hi_alert_st]
#MP DefaultRecordParam [supply_pressure_lo_alert_st, "0", 0, supply_pressure_lo_alert_st]
#MP DefaultRecordParam [supply_pressure_lolo_alert_st, "0", 0, supply_pressure_lolo_alert_st]
#MP DefaultRecordParam [temperature_hi_alert_st, "0", 0, temperature_hi_alert_st]
#MP DefaultRecordParam [temperature_lo_alert_st, "0", 0, temperature_lo_alert_st]
#MP DefaultRecordParam [ip_drive_current_alert_hi_st, "0", 0, ip_drive_current_alert_hi_st]
#MP DefaultRecordParam [ip_drive_current_alert_lo_st, "0", 0, ip_drive_current_alert_lo_st]
#MP DefaultRecordParam [sensor_failure_alert_st, "0", 0, sensor_failure_alert_st]
#MP DefaultRecordParam [processor_alert_st, "0", 0, processor_alert_st]
#MP DefaultRecordParam [valve_control_alert_st, "0", 0, valve_control_alert_st]
#MP DefaultRecordParam [commissioning_alert_st, "0", 0, commissioning_alert_st]
#MP DefaultRecordParam [air_supply_alert_st, "0", 0, air_supply_alert_st]
#MP DefaultRecordParam [supporting_hardware_alert_st, "0", 0, supporting_hardware_alert_st]
#MP EndRecordParam
                #MP
#MP BeginRecordParam[ALERT_COUNTERS, ALERT_COUNTERS, VRW|MN_N, "|en|Alert Counters", "|en|A counter increments on a new occurrence of alert"]
#MP Setstr DDLabel "|en|Deviation Alert"
#MP Setstr DDClass "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [deviation_alert_cnt, "0", 1, deviation_alert_cnt]
#MP DefaultRecordParam [position_hihi_alert_cnt, "0", 1, position_hihi_alert_cnt]
#MP DefaultRecordParam [position_hi_alert_cnt, "0", 1, position_hi_alert_cnt]
#MP DefaultRecordParam [position_lo_alert_cnt, "0", 1, position_lo_alert_cnt]
#MP DefaultRecordParam [position_lolo_alert_cnt, "0", 1, position_lolo_alert_cnt]
#MP DefaultRecordParam [setpoint_timeout_alert_cnt, "0", 1, setpoint_timeout_alert_cnt]
#MP DefaultRecordParam [near_close_alert_cnt, "0", 1, near_close_alert_cnt]
#MP DefaultRecordParam [travel_accumulation_a_alert_cnt, "0", 1, travel_accumulation_a_alert_cnt]
#MP DefaultRecordParam [travel_accumulation_b_alert_cnt, "0", 1, travel_accumulation_b_alert_cnt]
#MP DefaultRecordParam [cycle_counter_a_alert_cnt, "0", 1, cycle_counter_a_alert_cnt]
#MP DefaultRecordParam [cycle_counter_b_alert_cnt, "0", 1, cycle_counter_b_alert_cnt]
#MP DefaultRecordParam [working_time_alert_cnt, "0", 1, working_time_alert_cnt]
#MP DefaultRecordParam [supply_pressure_hi_alert_cnt, "0", 1, supply_pressure_hi_alert_cnt]
#MP DefaultRecordParam [supply_pressure_lo_alert_cnt, "0", 1, supply_pressure_lo_alert_cnt]
#MP DefaultRecordParam [supply_pressure_lolo_alert_cnt, "0", 1, supply_pressure_lolo_alert_cnt]
#MP DefaultRecordParam [temperature_hi_alert_cnt, "0", 1, temperature_hi_alert_cnt]
#MP DefaultRecordParam [temperature_lo_alert_cnt, "0", 1, temperature_lo_alert_cnt]
#MP DefaultRecordParam [ip_drive_current_alert_hi_cnt, "0", 1, ip_drive_current_alert_hi_cnt]
#MP DefaultRecordParam [ip_drive_current_alert_lo_cnt, "0", 1, ip_drive_current_alert_lo_cnt]
#MP DefaultRecordParam [sensor_failure_alert_cnt, "0", 1, sensor_failure_alert_cnt]
#MP DefaultRecordParam [processor_alert_cnt, "0", 1, processor_alert_cnt]
#MP DefaultRecordParam [valve_control_alert_cnt, "0", 1, valve_control_alert_cnt]
#MP DefaultRecordParam [commissioning_alert_cnt, "0", 1, commissioning_alert_cnt]
#MP DefaultRecordParam [air_supply_alert_cnt, "0", 1, air_supply_alert_cnt]
#MP DefaultRecordParam [supporting_hardware_alert_cnt, "0", 1, supporting_hardware_alert_cnt]
#MP EndRecordParam
#MP Restore GenDDdefs
                #MP
                #MP
#MP BeginRecordParam[ALERT_LOG, ALERT_LOG, RW] ;was SRW|MN_N but no-one wrote it
#MP DefaultRecordParam [alert_command, "0x00", 1]
#MP DefaultRecordParam [time, "0,0", 0]
#MP DefaultRecordParam [data, "0", 0]
#MP EndRecordParam
                #MP
#MP ;This needs to be in MN storage because it is manipulated internally
#MP Ifdef OPTION_HISTOGRAM_SELECTION_WORKING_TIMES__READONLY
	#MP memopt = NR
    #MP subx_access = 0
#MP Else
	#MP memopt = NRW
    #MP subx_access = SUBX_ACCESS
#MP Endif
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
                #MP
#MP Setstr LBL_531_WORKING_TIMES = "|en|Working Times"
#MP BeginRecordParam[WORKING_TIMES, WORKING_TIMES, memopt|MN_N, LBL_531_WORKING_TIMES]
#MP Undef memopt ;cleanup
#MP Setstr LBL_SINCE_RESET "|en|Since Reset"
#MP Setstr HLP_SINCE_RESET "|en|Hours since last reset"
#MP Setstr DDLabel LBL_SINCE_RESET
#MP Setstr DDHelp HLP_SINCE_RESET
#MP Setstr DDUnits "CONSTANT_UNIT [unit_code_1059];"
#MP DefaultRecordParam [since_reset, "0", subx_access]
        #MP Setstr LBL_TOTAL_TIME "|en|Total Time"
        #MP Setstr HLP_TOTAL_TIME "|en|Run time since last cleared"
#MP Setstr DDLabel LBL_TOTAL_TIME
#MP Setstr DDHelp HLP_TOTAL_TIME
#MP Setstr DDUnits "CONSTANT_UNIT [unit_code_1059];"
#MP DefaultRecordParam [total_time, "0", 0, total_time_r] ;never writable like in R2
    #MP ;Explanation: A different DD name to avoid units collision
#MP Undef subx_access ;cleanup
#MP EndRecordParam
                #MP
#MP Restore GenDDdefs
                #MP
#MP ;This needs to be in MN storage because it is manipulated internally
#MP BeginRecordParam[WORKING_TIME_ALERT, WORKING_TIME_ALERT, SRW|MN_N]
#MP DefaultRecordParam [total_time, "0", 0]
#MP DefaultRecordParam [alert_point, "8760", 1]
#MP AlertExtrasDefaults
#MP DefaultRecordParam [enable, "0", 1]
#MP EndRecordParam
                                #MP
#MP ;Make FF-HART buffers multiple of 4. Screw GW and/or Tokenizer!
                                #MP
#MP BeginArrayParam[u8, FACTORY_USE_1, 92, RW, "|en|Factory Use 1" ,"|en|Used for factory configuration of the instrument"]
#MP DefaultArrayParams[0, 91, "0"]
#MP EndArrayParam
                                #MP
#MP BeginArrayParam[u8, FACTORY_USE_2, 92, R, "|en|Factory Use 2" ,"|en|Used for factory configuration of the instrument"]
#MP DefaultArrayParams[0, 91, "0"]
#MP EndArrayParam
                                #MP
#MP BeginRecordParam[ACTUATOR_1, ACTUATOR_1, NRW|MN_N]
#MP DefaultRecordParam [act_man_id, "_32_SPACES", 1]
#MP DefaultRecordParam [act_model_num, "_32_SPACES", 1]
#MP DefaultRecordParam [act_sn, "_32_SPACES", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[ACTUATOR_2, ACTUATOR_2, NRW|MN_N]
#MP DefaultRecordParam [act_type_string, "_32_SPACES", 1]
#MP DefaultRecordParam [act_size, "_32_SPACES", 1]
#MP DefaultRecordParam [act_rotary_moment_arm, "_32_SPACES", 1]
#MP DefaultRecordParam [act_effective_area, "0x00", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[ACTUATOR_3, ACTUATOR_3, RW] ;Storage separate (MN-style object)
#MP DefaultRecordParam [shutoff_dp, "0x00", 1]
#MP DefaultRecordParam [hand_wheel, "0x00", 1]
#MP DefaultRecordParam [style, "1", 0]
#MP DefaultRecordParam [act_fail_action, "1", 1]
#MP DefaultRecordParam [relay_type, "1", 1]
#MP DefaultRecordParam [supply_prs_max, "241.3", 1]
#MP DefaultRecordParam [prs_control_hi, "103.4", 1]
#MP DefaultRecordParam [prs_control_lo, "20.6", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[ACTUATOR_INFO, ACTUATOR_INFO, NRW|MN_N]
#MP DefaultRecordParam [descriptor, "_32_SPACES", 1]
#MP DefaultRecordParam [message, "_32_SPACES", 1]
#MP DefaultRecordParam [date_info, #@"        "#, 1]
#MP DefaultRecordParam [spec_sheet, "_32_SPACES", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[VALVE_IDENTIFICATION, VALVE_IDENTIFICATION, NRW|MN_N]
#MP DefaultRecordParam [valve_man_id, "_32_SPACES", 1]
#MP DefaultRecordParam [valve_model_num, "_32_SPACES", 1]
#MP DefaultRecordParam [valve_sn, #@_32_SPACES#, 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[VALVE_SERVICE, VALVE_SERVICE, NRW|MN_N]
#MP DefaultRecordParam [service, "_32_SPACES", 1]
#MP DefaultRecordParam [pid_no, "0x00", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[VALVE_BODY_1, VALVE_BODY_1, NRW|MN_N]
#MP DefaultRecordParam [valve_type, "1", 1]
#MP DefaultRecordParam [body_size, "0", 1]
#MP DefaultRecordParam [packing, "_32_SPACES", 1]
#MP DefaultRecordParam [plug_type, "0x00", 1]
#MP DefaultRecordParam [seat_ring_type, "0x00", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[VALVE_BODY_2, VALVE_BODY_2, NRW|MN_N]
#MP DefaultRecordParam [characteristic, "_32_SPACES", 1]
#MP DefaultRecordParam [leakage_class, "_32_SPACES", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[VALVE_BODY_3, VALVE_BODY_3, NRW|MN_N]
#MP DefaultRecordParam [flow_action, "_32_SPACES", 1]
#MP DefaultRecordParam [rated_adj_cv, "_32_SPACES", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[VALVE_INFO, VALVE_INFO, NRW|MN_N]
#MP DefaultRecordParam [same_as_actuator, "0x01", 1]
#MP DefaultRecordParam [descriptor, "_32_SPACES", 1]
#MP DefaultRecordParam [message, "_32_SPACES", 1]
#MP DefaultRecordParam [date_info, #@"        "#, 1]
#MP DefaultRecordParam [spec_sheet, "_32_SPACES", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[BOOSTER, BOOSTER, NRW|MN_N]
#MP DefaultRecordParam [manufacturer, "_32_SPACES", 1]
#MP DefaultRecordParam [model, "_32_SPACES", 1]
#MP DefaultRecordParam [qty, "_32_SPACES", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[ACCESSORY, ACCESSORY, SRW|MN_N]
#MP DefaultRecordParam [solenoid, "_32_SPACES", 1]
#MP DefaultRecordParam [remote_sensor, "0", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[POSITION_EXTREMES, POSITION_EXTREMES, RW] ;by design, not persistent
#MP DefaultRecordParam [final_value_max, "-50", 1]
#MP DefaultRecordParam [final_value_min, "199", 1]
#MP DefaultRecordParam [final_pos_value_max, "-50", 1]
#MP DefaultRecordParam [final_pos_value_min, "199", 1]
#MP DefaultRecordParam [working_sp_max, "-50", 1]
#MP DefaultRecordParam [working_sp_min, "199", 1]
#MP DefaultRecordParam [working_pos_max, "-50", 1]
#MP DefaultRecordParam [working_pos_min, "199", 1]
#MP EndRecordParam
                                #MP
#MP BeginRecordParam[PRESSURE_EXTREMES, PRESSURE_EXTREMES, RW] ;by design, not persistent
#MP DefaultRecordParam [supply_pressure_max, "-25", 1]
#MP DefaultRecordParam [supply_pressure_min, "1050", 1]
#MP DefaultRecordParam [actuator_a_max, "-25", 1]
#MP DefaultRecordParam [actuator_a_min, "1050", 1]
#MP DefaultRecordParam [actuator_b_max, "-25", 1]
#MP DefaultRecordParam [actuator_b_min, "1050", 1]
#MP DefaultRecordParam [pilot_max, "-25", 1]
#MP DefaultRecordParam [pilot_min, "1050", 1]
#MP EndRecordParam
                                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ; for DD ver 5
#MP Setstr LBL_617_TEMPERATURE_EXTREMES "|en|Temperature Extremes"
#MP BeginRecordParam[TEMPERATURE_EXTREMES, TEMPERATURE_EXTREMES, RW, LBL_617_TEMPERATURE_EXTREMES] ;by design, not persistent, except lifetime from APP
#MP Setstr DDHelp "|en|Max value since restart or last user update"
#MP Setstr DDLabel "|en|Temperature Max"
#MP Setstr DDUnits "CONSTANT_UNIT [unit_code_1001];"
#MP DefaultRecordParam [temperature_max, "-40", SUBX_ACCESS]
#MP Setstr DDLabel  "|en|Temperature Min"
#MP Setstr DDHelp "|en|Min value since restart or last user update"
#MP Setstr DDUnits "CONSTANT_UNIT [unit_code_1001];"
#MP DefaultRecordParam [temperature_min, "85", SUBX_ACCESS]
#MP DDcolbreak ;for presentation
#MP Setstr DDLabel "|en|STDDummy"
#MP DefaultRecordParam[tempr_max_lifetime, "-40", SUBX_ACCESS] ;Goes as __internal_temp_max to DD and as tempr_max_lifetime to GW
#MP Setstr DDLabel "|en|STDDummy"
#MP DefaultRecordParam[tempr_min_lifetime, "85", SUBX_ACCESS] ;Goes as __internal_temp_max to DD and as tempr_max_lifetime to GW
#MP EndRecordParam
#MP Restore GenDDdefs
                                #MP
#MP BeginRecordParam[IP_CURRENT_EXTREMES, IP_CURRENT_EXTREMES, RW] ;by design, not persistent
#MP DefaultRecordParam [ip_current_max, "-25", 1]
#MP DefaultRecordParam [ip_current_min, "150", 1]
#MP EndRecordParam
                                #MP
#MP BeginArrayParam[u32, ADVANCED, 14, RW]
#MP DefaultArrayParams[0, 4, "0xffffffff"]
#MP DefaultArrayParams[5, 13, "0"]
#MP EndArrayParam
                                #MP
#MP Save GenDDdefs
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
#MP BeginBitEnumType5[bitstr4, BENUM_TB_BLOCK_ERR_DESC_1]
#MP DefineBitEnumValue[DESC_DEVICE_RESET, 0, "|en|Device reset", "|en|Power cycle, user command or internal exception. Check COMPLETE_STATUS", "|en|"]
#MP DefineBitEnumValue[DESC_MODE_CHANGE_ERR, 1, "|en|AUTO mode refused"]
#MP DefineBitEnumValue[DESC_INTERNAL_BUS, 2, "|en|Internal bus failure"]
#MP DefineBitEnumValue[DESC_TRAVEL_RANGE_INOP, 3, "|en|Travel Range inop"]
#MP DefineBitEnumValue[DESC_AUTO_TUNE, 4, "|en|Could not autotune"]
#MP DefineBitEnumValue[DESC_DIAG_METHOD_FAILED, 5, "|en|Diagnostic method didn't succeed"]
#MP DefineBitEnumValue[DESC_DEGRADED_PERFORMANCE, 6, "|en|Degraded performance"]
#MP DefineBitEnumValue[DESC_IP_DRIVE_CURRENT, 7, "|en|I/P current out of normal range"]
#MP DefineBitEnumValue[DESC_NV_LOST_FAC_SERV, 8, "|en|Lost critical data", "|en|Needs factory service"]
#MP DefineBitEnumValue[DESC_DEVICE_FAILED, 9, "|en|Critical failure"]
#MP DefineBitEnumValue[DESC_UNUSABLE_AFTER_RESET, 10, "|en|Start-up memory failed", "|en|device is unusable after reset"]
#MP DefineBitEnumValue[DESC_FACTORY_OP_ALLOWED, 11, "|en|Privileged operations enabled"]
#MP DefineBitEnumValue[DESC_AI_FAILED, 12, "|en|Physical analog input failed"]
#MP DefineBitEnumValue[DESC_PRESSURE_SENSOR_FAILED, 13, "|en|Non-critical pressure sensor failed"]
#MP DefineBitEnumValue[DESC_OUT_OF_SPEC, 14, "|en|System overload"]
#MP DefineBitEnumValue[DESC_FACTORY_OP_PERFORMED, 15, "|en|Privileged op performed"]
#MP DefineBitEnumValue[DESC_AUTO_RECOVERED_FROM_ERROR, 16, "|en|Auto-recovered from a glich", "|en|Watch for recurrence"]
#MP EndBitEnumType
                #MP
#MP Setstr DDLabel = "|en|Block Error Description"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP BeginSimpleParam[BENUM_TB_BLOCK_ERR_DESC_1, BLOCK_ERR_DESC_1, R, TB_BLOCK_ERR_DESC_1]
#MP DefaultSimpleParam ["0"]
#MP EndSimpleParam
#MP Restore GenDDdefs
                                #MP
                                #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                    #MP
                    #MP
#MP BeginEnumType[u8, ENUM_TRIGGER_ON_DEMAND]
#MP DefineEnumValue[TD_DISABLED, 0, "|en|Trigger disabled"]
#MP DefineEnumValue[TD_ENABLED, 1, "|en|Trigger enabled"]
#MP EndEnumType
                    #MP
#MP BeginEnumType[u8, ENUM_TRIGGER_BY_LOCAL_UI] ;future devel, foo]
#MP DefineEnumValue[TDUI_DISABLED, 0, "|en|Trigger disabled"]
#MP DefineEnumValue[TDUI_ENABLED, 1, "|en|Trigger enabled"]
#MP EndEnumType
                    #MP
#MP BeginBitEnumType5[bitstr1, BENUM_PST_TRIGGER_BY_LOCAL_UI]
#MP DefineBitEnumValue[PSTUI_RUN_LO, 0] ;Hide from DD, "|en|Run in LO/AppSetup", "|en|Run PST from METHODS UI menu"]
#MP DefineBitEnumValue[PSTUI_RUN_AUTO_MAN, 1] ;Hide from DD, "|en|Run in AUTO/MAN", "|en|Run from main UI menu"]
#MP DefineBitEnumValue[PSTUI_CONFIG, 2] ;Hide from DD, "|en|Config by local UI", "|en|Partial Config by local UI"]
#MP DefineBitEnumValue[PSTUI_VIEW_CONFIG, 3] ;Hide from DD, "|en|View Config in local UI", "|en|View Config by local UI VIEW DATA menu"]
#MP DefineBitEnumValue[PSTReserved1, 5, "|en|Reserved1", "|en|R1"]
#MP DefineBitEnumValue[PSTReserved2, 6, "|en|Reserved2", "|en|R2"]
#MP EndBitEnumType
                    #MP
#MP BeginEnumType[u8, ENUM_TRIGGER_BY_DI_SWITCH]
#MP DefineEnumValue[TDISW_DISABLED, 0, "|en|Trigger disabled"]
#MP DefineEnumValue[TDISW_ENABLED_OPEN, 1, "|en|Trigger on DI switch open"]
#MP DefineEnumValue[TDISW_ENABLED_CLOSED, 2, "|en|Trigger on DI switch closed"]
#MP EndEnumType
                    #MP
#MP BeginEnumType[u8, ENUM_TRIGGER_BY_AI_INPUT]
#MP DefineEnumValue[TAII_DISABLED, 0, "|en|Trigger disabled"]
#MP DefineEnumValue[TAII_ENABLED_OPEN, 1, "|en|Trigger on AI below threshold"]
#MP DefineEnumValue[TAII_ENABLED_CLOSED, 2, "|en|Trigger on AI above threshold"]
#MP EndEnumType
                    #MP
#MP BeginStruct[PST_TRIGGER]
#MP StructMember[ENUM_TRIGGER_ON_DEMAND, PST_Trigger_On_Demand]
#MP If 0 ;future development; now conflicts with gwgen.inc
#MP StructMember[foo, PST_Trigger_by_UI, Reserved]
#MP Else
#MP StructMember[BENUM_PST_TRIGGER_BY_LOCAL_UI, PST_Trigger_by_UI]
#MP ;StructMember[ENUM_TRIGGER_BY_LOCAL_UI, PST_Trigger_by_UI, Reserved]
#MP Endif
#MP StructMember[ENUM_TRIGGER_BY_DI_SWITCH, PST_Trigger_By_DI_Switch]
#MP StructMember[ENUM_TRIGGER_BY_AI_INPUT, PST_Trigger_By_AI_Input]
#MP StructMember[float32, PST_AI_Trigger_Input_Threshold]
#MP EndStruct
                    #MP
#MP BeginRecordParam[PST_TRIGGER, PST_TRIGGER, NRW|MN_A, "|en|Partial Stroke Test trigger", "|en|PST trigger configuration"]
#MP Setstr DDLabel = "|en|Trigger On Demand"
#MP Setstr DDHelp = "|en|May be enabled or disabled"
#MP DefaultRecordParam [PST_Trigger_On_Demand, "1", 1]
#MP Setstr DDLabel = "|en|Trigger by local UI"
#MP ;Setstr DDHelp = "|en|Trigger by local UI"
#MP DefaultRecordParam [PST_Trigger_by_UI, "0", SUBX_ACCESS|SUBX_NOPARAMWRAP]
#MP Setstr DDLabel = "|en|Trigger By DI Switch"
#MP Setstr DDHelp = "|en|May be disabled or enabled per options values"
#MP DefaultRecordParam [PST_Trigger_By_DI_Switch, "0", 1]
#MP Setstr DDLabel = "|en|Trigger By AI Input"
#MP Setstr DDHelp = "|en|May be disabled or enabled per options values"
#MP DefaultRecordParam [PST_Trigger_By_AI_Input, "0", 1]
#MP Setstr DDLabel = "|en|Physical AI Trigger Input Threshold"
#MP Setstr DDHelp = "|en|Threshold above/below which sampling is activated"
#MP DefaultRecordParam [PST_AI_Trigger_Input_Threshold, "12.0", 1]
#MP EndRecordParam
                                #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                                #MP
#MP BeginEnumType[u8, ENUM_PST_PATTERN]
#MP DefineEnumValue[PST_PATTERN_DPU, 0, "|en|Down-Pause-Up"]
#MP DefineEnumValue[PST_PATTERN_DPUPD, 1, "|en|Down-Pause-Up-Pause-Down"]
#MP DefineEnumValue[PST_PATTERN_DPUuPDdPU, 2, "|en|Down-Pause-Up-Pause-Down-Pause-Up"]
#MP DefineEnumValue[PST_PATTERN_UPD, 3, "|en|Up-Pause-Down"]
#MP DefineEnumValue[PST_PATTERN_UPDPU, 4, "|en|Up-Pause-Down-Pause-Up"]
#MP DefineEnumValue[PST_PATTERN_UPDdPUuPD, 5, "|en|Up-Pause-Down-Pause-Up-Pause-Down"]
#MP EndEnumType
                    #MP
#MP BeginBitEnumType5[bitstr2, BENUM_VAR_BITMAP]
#MP DefineBitEnumValue[VAR_WRK_POSITION, 0, "|en|Working position", "|en|Position before inverse characterization"]
#MP DefineBitEnumValue[VAR_MAIN_PRESSURE, 1, "|en|Main pressure", "|en|Actuator pressure A (single-acting) or A-B (double-acting)"]
#MP DefineBitEnumValue[VAR_PILOT_PRESSURE, 2, "|en|Pilot pressure"]
#MP DefineBitEnumValue[VAR_SUPPLY_PRESSURE, 3, "|en|Supply pressure"]
#MP DefineBitEnumValue[VAR_PRESSURE_B, 4, "|en|Actuator pressure B", "|en|N/A for single-acting"]
#MP DefineBitEnumValue[VAR_SETPOINT, 5, "|en|Working setpoint", "|en|Setpoint after characterization"]
#MP DefineBitEnumValue[VAR_IP_CURRENT, 6, "|en|I/P current", "|en|I/P current"]
#MP DefineBitEnumValue[VAR_AI_INPUT, 7, "|en|Analog Input", "|en|Physical AI"]
#MP EndBitEnumType
                    #MP
#MP BeginBitEnumType5[bitstr2, BENUM_PSTOPTION]
#MP DefineBitEnumValue[PSTFREEZE_RANGE, 2, "|en|Setpoint range freeze", "|en|Honor position range limits if set"]
#MP DefineBitEnumValue[PSTFREEZE_RATE, 3, "|en|Setpoint rate freeze", "|en|Honor setpoint rate limits if set"]
#MP DefineBitEnumValue[PSTFREEZE_CUTOFF, 4, "|en|Cutoff limits freeze", "|en|Honor position cutoff limits if set"]
#MP DefineBitEnumValue[PSTFREEZE_DEADZONE, 5, "|en|Control deadzone freeze", "|en|Honor position control deadzone if set"]
#MP EndBitEnumType
                    #MP
#MP BeginStruct[PST_CONFIG]
#MP StructMember[float32, setpoint_change_threshold]
#MP StructMember[float32, pst_travel]
#MP StructMember[float32, pst_setpoint_rate]
#MP StructMember[float32, pilot_threshold]
#MP StructMember[float32, actuator_threshold]
#MP StructMember[u32, stroke_timeout_override]
#MP StructMember[u16, pst_pause]
#MP StructMember[u16, pst_leadtime]
#MP StructMember[u16, pst_maxtime]
#MP StructMember[BENUM_VAR_BITMAP, pst_datamap]
#MP StructMember[u16, pst_skip_count]
#MP StructMember[BENUM_PSTOPTION, pst_freeze_options]
#MP StructMember[ENUM_PST_PATTERN, pst_pattern]
#MP EndStruct
                                #MP
#MP BeginRecordParam[PST_CONFIG, PST_CONFIG, NRW|MN_A, "|en|Partial Stroke Test configuration", "|en|Partial Stroke Test configuration parameters"]
#MP Setstr DDLabel = "|en|PST Setpoint change threshold"
#MP Setstr DDHelp = "|en|If process setpoint changes more than threshold, PST is aborted"
#MP DefaultRecordParam [setpoint_change_threshold, "5.0", 1]
#MP Setstr DDLabel = "|en|Travel"
#MP Setstr DDHelp = "|en|magnitude of partial stroke"
#MP DefaultRecordParam [pst_travel, "3.0", 1]
#MP Setstr DDLabel = "|en|Setpoint rate, %/s"
#MP Setstr DDHelp = "|en|Rate of setpoint change in a stroke"
#MP DefaultRecordParam [pst_setpoint_rate, "10.0", 1]
#MP Setstr DDLabel = "|en|PST Pilot pressure change threshold"
#MP Setstr DDHelp = "|en|If pilot pressure changes more than threshold from end of lead time, PST is aborted"
#MP DefaultRecordParam [pilot_threshold, "100.0", 1]
#MP Setstr DDLabel = "|en|PST Actuator pressure change threshold"
#MP Setstr DDHelp = "|en|If actuator pressure changes more than threshold from end of lead time, PST is aborted"
#MP DefaultRecordParam [actuator_threshold, "100.0", 1]
#MP Setstr DDLabel = "|en|Stroke timeout override, ms"
#MP Setstr DDHelp = "|en|If non-0, overrides automatically computed stroke time.\n Can be useful when setpoint rate limits are in effect"
#MP DefaultRecordParam [stroke_timeout_override, "0", 1]
#MP Setstr DDLabel = "|en|Pause (dwell time), ms"
#MP Setstr DDHelp = "|en|PST spends about pause time between consecutive strokes"
#MP DefaultRecordParam [pst_pause, "300", 1]
#MP Setstr DDLabel = "|en|PST lead time, s"
#MP Setstr DDHelp = "|en|Time before the first stroke"
#MP DefaultRecordParam [pst_leadtime, "3", 1]
#MP Setstr DDLabel = "|en|Max time of PST completion, s"
#MP Setstr DDHelp = "|en|If running time exceeds, PST is aborted"
#MP DefaultRecordParam [pst_maxtime, "60", 1]
#MP Setstr DDLabel = "|en|Data Bitmap"
#MP Setstr DDHelp = "|en|Specifies which variables are collected"
#MP DefaultRecordParam [pst_datamap, "0x7F", 1]
#MP Setstr DDLabel = "|en|Number of samples skipped"
#MP Setstr DDHelp = "|en|Number of samples skipped between recorded samples; 0 means every sample recorded, 1 - every second sample etc."
#MP DefaultRecordParam [pst_skip_count, "0", 1]
#MP Setstr DDLabel = "|en|Freeze options"
#MP Setstr DDHelp = "|en|Cutoff limits, position limits, setpoint rate, deadzone can be honored (frozen with a bit set) or disabled"
#MP DefaultRecordParam [pst_freeze_options, "0x3c", 1]
#MP Setstr DDLabel = "|en|PST stroke pattern"
#MP Setstr DDHelp = "|en|One of the predefined sequences of up/down strokes"
#MP DefaultRecordParam [pst_pattern, "0", 1]
#MP EndRecordParam
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                    #MP
                    #MP
                    #MP
#MP BeginEnumType[u8, ENUM_DATA_COLLECT_TICK_BASE]
#MP DefineEnumValue[DATACCT_15MS, 0, "|en|15ms"]
#MP DefineEnumValue[DATACCT_60MS, 1, "|en|60ms"]
#MP EndEnumType
                    #MP
#MP Macro Datahog
#MP StructMember[ENUM_DATA_COLLECT_TICK_BASE, DataCollectBase]
#MP StructMember[u16, DataCollectSkipCount]
#MP StructMember[BENUM_VAR_BITMAP, DataCollectBitmap]
#MP StructMember[u16, DataCollectMaxSamples]
#MP Endm
                    #MP
#MP Macro DatahogParam
#MP Setstr DDLabel = "|en|Base rate"
#MP Setstr DDHelp = "|en|0 - 15 ms base (limited number of variables), 1 - 60 ms base period of sampling"
#MP DefaultRecordParam [DataCollectBase, "1", 1]
#MP Setstr DDLabel = "|en|Skip count"
#MP Setstr DDHelp = "|en|Distance between samples in multiples of DataCollectBase"
#MP DefaultRecordParam [DataCollectSkipCount, "0", 1]
#MP Setstr DDLabel = "|en|Bitmap of variables collected"
#MP Setstr DDHelp = "|en|Bitmap (mask) of what variables are collected"
#MP DefaultRecordParam [DataCollectBitmap, "1", 1]
#MP Setstr DDLabel = "|en|Max Samples"
#MP Setstr DDHelp = "|en|Max number of samples to record. 0 means unlimited (other than by buffer size)"
#MP DefaultRecordParam [DataCollectMaxSamples, "0", 1]
#MP Endm
                    #MP
#MP BeginStruct[DATA_CONFIG_PERM]
#MP Datahog
#MP StructMember[u16, DataCollectMaxPreSamples]
#MP EndStruct
                    #MP
#MP BeginStruct[DATA_CONFIG_TEMP]
#MP Datahog
#MP EndStruct
                    #MP
#MP BeginRecordParam[DATA_CONFIG_PERM, DATA_CONFIG_PERM, NRW|MN_A, "|en|Data collection config perm.", "|en|Data collection persistent configuration parameters"]
#MP DatahogParam
#MP Setstr DDLabel = "|en|Number of pre-samples"
#MP Setstr DDHelp = "|en|Samples before trigger to include in total samples"
#MP DefaultRecordParam [DataCollectMaxPreSamples, "0", 1]
#MP EndRecordParam
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                    #MP
                    #MP
#MP BeginBitEnumType5[bitstr2, BENUM_TRIGGER_OPTIONS, "|en|Enablers"]
#MP DefineBitEnumValue[TrigManual, 0, "|en|Manual", "|en|Start on demand"]
#MP DefineBitEnumValue[TrigAlerts, 1, "|en|On TB Alerts", "|en|Start on TB alert event as configured"]
#MP DefineBitEnumValue[TrigPosDev, 4, "|en|Pos Deviation", "|en|Working position deviation from average"]
#MP DefineBitEnumValue[TrigPresDev, 5, "|en|Pres Deviation", "|en|Actuator pressure deviation from average"]
#MP DefineBitEnumValue[TrigSPDev, 6, "|en|SP Deviation", "|en|Working setpoint deviation from average"]
#MP DefineBitEnumValue[TrigDIOpen, 7, "|en|DI open", "|en|On Input switch open"]
#MP DefineBitEnumValue[TrigDIClosed, 8, "|en|DI closed", "|en|On Input switch closed"]
#MP DefineBitEnumValue[TrigAIBelow, 9, "|en|AI<LO", "|en|On Analog Input below low threshold"]
#MP DefineBitEnumValue[TrigAIAbove, 10, "|en|AI>HI", "|en|On Analog Input above high threshold"]
#MP DefineBitEnumValue[TrigAIBetween, 11, "|en|AI btwn", "|en|On Analog Input between low and high thresholds"]
#MP EndBitEnumType
                    #MP
#MP BeginStruct[DATA_COLLECTION_TRIGGER]
#MP StructMember[BENUM_TRIGGER_OPTIONS, TriggerEnabled]
#MP StructMember[float32, AI_Trigger_ThresholdLow]
#MP StructMember[float32, AI_Trigger_ThresholdHigh]
#MP StructMember[float32, Position_Threshold]
#MP StructMember[float32, Pressure_Threshold]
#MP StructMember[float32, Setpont_Threshold]
#MP StructMember[u8, FilterCoef]
#MP EndStruct
                    #MP
#MP BeginRecordParam[DATA_COLLECTION_TRIGGER, DATA_COLLECTION_TRIGGER, NRW|MN_A, "|en|Data collection trigger", "|en|Data collection trigger event configuration parameters"]
#MP Setstr DDLabel = "|en|Enabling options"
#MP Setstr DDHelp = "|en|Allowed events to trigger Data Collection"
#MP DefaultRecordParam [TriggerEnabled, "0", SUBX_ACCESS] ;, SUBX_NOPARAMWRAP|SUBX_ACCESS]
#MP Setstr DDLabel = "|en|AI Low Threshold"
#MP Setstr DDHelp = "|en|Physical AI threshold below which sampling is activated"
#MP DefaultRecordParam [AI_Trigger_ThresholdLow, "12.0", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|AI High Threshold"
#MP Setstr DDHelp = "|en|Physical AI threshold above which sampling is activated"
#MP DefaultRecordParam [AI_Trigger_ThresholdHigh, "12.0", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|Pos Deviation Threshhold"
#MP Setstr DDHelp = "|en|Working position deviation from average"
#MP DefaultRecordParam[Position_Threshold, "0.5", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|Pressure Deviation Thresh"
#MP Setstr DDHelp = "|en|Actuator pressure deviation from average"
#MP DefaultRecordParam[Pressure_Threshold, "5.0", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|SP Deviation Threshold"
#MP Setstr DDHelp = "|en|Working setpoint deviation from average"
#MP DefaultRecordParam[Setpont_Threshold, "0.5", SUBX_ACCESS]
#MP Setstr DDLabel = "|en|Averaging Coef"
#MP Setstr DDHelp = "|en|Averaging works as exponential forgetting with 1/2**AveragingCoef weight"
#MP DefaultRecordParam[FilterCoef, "6", SUBX_ACCESS]
#MP EndRecordParam
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
                    #MP
#MP BeginStdRecordParam(FLOAT_S, ANALOG_INPUT, R|MN_DYN, "|en|Analog Input", "|en|Physical input to the device")
#MP Setstr DDLabel = "|en|status"
#MP Setstr DDHelp = "|en|In TB OOS jammed to BAD"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [status, "0x1c", 0]
#MP Setstr DDLabel = "|en|physical analog input"
#MP Setstr DDHelp = "|en|value of analog input in mA"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [value, "0.0", 0]
#MP EndRecordParam
                    #MP
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
#MP BeginEnumType[u8, ENUM_ACT_FAIL_ACTION] ;replacement for automation
#MP DefineEnumValue[ACTUATOR_ATO, 1, "|en|1 - Valve Closed (air to open)"]
#MP DefineEnumValue[ACTUATOR_ATC, 2, "|en|2 - Valve Open (air to close)"]
#MP EndEnumType
                    #MP
#MP BeginStruct[TB_FSTATE_STATUS]
#MP StructMember[ENUM_ALERT_STATE, DO_usr_req]
#MP StructMember[ENUM_ALERT_STATE, final_value_req]
#MP StructMember[float32, time_to_fstate]
#MP EndStruct
                    #MP;
#MP BeginRecordParam[TB_FSTATE_STATUS, TB_FSTATE_STATUS, RW, "|en|Status controlled by XD_FSTATE", "|en|"]
#MP Setstr DDLabel = "|en|DO FB/user request"
#MP Setstr DDHelp = "|en|Request from DO with CHANNEL=CH_DO_FAULT or from user"
#MP DefaultRecordParam [DO_usr_req, "0", 1]
#MP Setstr DDLabel = "|en|Request from FB"
#MP Setstr DDHelp = "|en|Request from FB controlling FINAL_VALUE_x per setpoint source"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [final_value_req, "0", 1]
#MP Setstr DDLabel = "|en|Time to Fstate"
#MP Setstr DDHelp = "|en|Time in s until activation of Failed State if requested by FB"
#MP Setstr DDClass = "CONTAINED & DYNAMIC"
#MP DefaultRecordParam [time_to_fstate, "0.0", 1]
#MP EndRecordParam
                    #MP
                    #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4
#MP BeginRecordParam[DATA_CONFIG_TEMP, DATA_CONFIG_TEMP, NRW|MN_A, "|en|Data collection transient config", "|en|Data collection persistent configuration parameters"]
#MP DatahogParam
#MP EndRecordParam
                    #MP
#MP Undef GenDDdefs ;end non-DD4 parameters
                    #MP
#MP ;------------------ channels ---------------------
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5 and ver 4
                    #MP
#MP BeginChannels5[Channels_MAI, CHANNELS_MAI]
#MP DefineDefaultChannel[CH_MAI_NOT_CONFIGURED, 0, "|en|Not Configured", "|en|Prevents the block to go to Auto Mode"]
#MP DefineChannel[CH_MAI_CHANNEL1, 20, "|en|Default MAI Channel number", "|en|The one and only channel number available for MAI block"]
#MP EndChannels
                    #MP
#MP BeginChannels5[Channels_DI, CHANNELS_DI]
#MP DefineChannel[CH_DI_NOT_CONFIGURED, 0, "|en|Not Configured", "|en|Prevents the block to go to Auto Mode"]
#MP DefineChannel[CH_DI_DISCRETE_INPUT, 17, "|en|Discrete Input", "|en|Provides the state of the discrete input to the FF control"]
#MP DefineDefaultChannel[CH_DI_STATE_OF_SW1, 18, "|en|State of Sw1", "|en|Provides the state of the discrete Switch 1 from APP processor to the FF"]
#MP DefineChannel[CH_DI_STATE_OF_SW2, 19, "|en|State of Sw2", "|en|Provides the state of the discrete Switch 2 from APP processor to the FF"]
#MP EndChannels
                    #MP
#MP BeginChannels5[Channels_DO, CHANNELS_DO]
#MP DefineChannel[CH_DO_NOT_CONFIGURED, 0, "|en|Not Configured", "|en|Should prevent the block to go to Auto Mode"]
#MP Setstr hlp = "|en|Updates the FINAL_VALUE_D"
#MP Setstr hlp = hlp " parameter in the Transducer block. Readback provided from FINAL_POSITION_VALUE_D."
#MP Setstr hlp = hlp "\nShould not allow to switch the DO block to auto mode if the"
#MP Setstr hlp = hlp "TB.SETPOINT_SOURCE is not equal to 2 (DO block in Open/Close mode)"
#MP Setstr hlp = hlp "\nShould report an error for the setting mismatch."
#MP DefineChannel[CH_DO_POSITION_OPEN_CLOSE, 2, "|en|Open/Close", hlp]
#MP Setstr hlp =  "|en|Updates the FINAL_VALUE_DINT parameter in the Transducer"
#MP Setstr hlp = hlp  "block. Readback shall be provided from FINAL_POSITION_VALUE_DINT."
#MP Setstr hlp = hlp  "\nShould not allow to switch the DO block to auto mode if the"
#MP Setstr hlp = hlp  "TB.SETPOINT_SOURCE is not equal to 3 (Discrete Output block in Discrete"
#MP Setstr hlp = hlp  "Mode)"
#MP Setstr hlp = hlp  "\nShould report an error for the setting mismatch."
#MP DefineChannel[CH_DO_POSITION_DISCRETE_POSITION, 3, "|en|Discrete Position", hlp]
#MP Setstr hlp =  "|en|The DO.OUT value shall update the TB.DISCRETE_OUTPUT_1 parameter, which"
#MP Setstr hlp = hlp  "controls the DO1 switch controlled by the APP processor."
#MP DefineDefaultChannel[CH_DO_DISCRETE_SWITCH_1, 4, "|en|Discrete Switch 1", hlp]
#MP Setstr hlp =  "|en|The DO.OUT value shall update the TB.DISCRETE_OUTPUT_2 parameter, which"
#MP Setstr hlp = hlp  "controls the DO2 switch controlled by the APP processor."
#MP DefineChannel[CH_DO_DISCRETE_SWITCH_2, 5, "|en|Discrete Switch 2", hlp]
#MP Setstr hlp  "|en|The DO.Out value enables/disables the valve control. Setting the value to"
#MP Setstr hlp = hlp  "TRUE with good state forces the TB to Fault State "
#MP DefineChannel[CH_DO_FAULT, 6, "|en|Fault State", hlp]
#MP EndChannels
                    #MP
#MP BeginChannels5[Channels_AO, CHANNELS_AO]
#MP DefineDefaultChannel[CH_AO_NOT_CONFIGURED, 0, "|en|Not Configured", "|en|Should prevent the block to go to Auto Mode"]
#MP Setstr hlp = "|en|Updates FINAL_VALUE parameter in the Transducer block. "
#MP Setstr hlp = hlp "Readback provided from FINAL_POSITION_VALUE. "
#MP Setstr hlp = hlp "Prevents AO block to auto mode if TB.SETPOINT_SOURCE is not equal to 1 (Analog Output block)"
#MP Setstr hlp = hlp   "\nShould report an error for the setting mismatch."
#MP DefineChannel[CH_AO_POSITION, 1, "|en|POSITION", hlp]
#MP EndChannels
                    #MP
#MP Macro channels_ai_4_5
#MP DefineChannel[CH_AI_NOT_CONFIGURED, 0, "|en|Not Configured", "|en|Prevents the Analog Input block to go to Auto Mode"]
#MP DefineDefaultChannel[CH_AI_SUPPLY_PRESSURE, 7, "|en|Supply Pressure", "|en|Provides the value of the supply pressure to the FF control"]
#MP DefineChannel[CH_AI_ACTUATOR_PRESSURE_1, 8, "|en|Actuator Pressure 1", "|en|Provides the value of the pressure in Actuator 1 to the FF control"]
#MP DefineChannel[CH_AI_ACTUATOR_PRESSURE_2, 9, "|en|Actuator Pressure 2", "|en|Provides the value of the pressure in Actuator 2 to the FF control"]
#MP DefineChannel[CH_AI_IP_CURRENT, 10, "|en|IP_Current", "|en|Provides the value of the IP current to the FF control"]
#MP DefineChannel[CH_AI_PILOT_PRESSURE, 11, "|en|Pilot Pressure", "|en|Provides the value of the pilot pressure to the FF control"]
#MP DefineChannel[CH_AI_TEMPERATURE, 12, "|en|Temperature", "|en|Provides the board temperature to the FF control"]
#MP DefineChannel[CH_AI_FINAL_VALUE, 13, "|en|Final Value", "|en|Provides back the TB setpoint to the FF control"]
#MP DefineChannel[CH_AI_FINAL_POSITION_VALUE, 14, "|en|Final Position Value", "|en|Provides back the TB actual position to the FF control"]
#MP DefineChannel[CH_AI_WORKING_SP, 15, "|en|Working SP", "|en|Provides back the TB working setpoint (after characterization) to the FF control"]
#MP DefineChannel[CH_AI_WORKING_POSITION, 16, "|en|Working Position", "|en|Provides back the TB working position (before de-characterization) to the FF control"]
#MP Endm
                        #MP
#MP ;Note round (i.e., not square) braces: The begin/end macros default to imbalanced eat-all
#MP ;BeginChannels4(CHANNELS_AI, CHANNELS_AI)
#MP ;channels_ai_4_5
#MP ;EndChannels4()
                        #MP
#MP GenDDdefs = (1<<5)|(1<<4) ;Generate DD ver.5; ver 4 ran out of dictionary size
#MP BeginChannels5[Channels_AI, CHANNELS_AI]
#MP channels_ai_4_5
#MP DefineChannel[CH_AI_ANALOG_INPUT, 21, "|en|Physical Analog Input", "|en|Provides the read of the 4-20 mA analog input to the FF control"]
#MP EndChannels
#MP Undef GenDDdefs ;end non-DD4 parameters
