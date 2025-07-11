/*----------------------------------/
** TB block members for SVI2 special
/----------------------------------*/

#define TB_BLOCK_MEMBERS_SVI                                            \
    POSITION_TRANSDUCER_TYPE,            position_transducer_type;      \
    XD_ERROR_POS,                        xd_error_pos;                  \
    /* COLLECTION_DIRECTORY,                __collection_directory; */ \
    FINAL_VALUE,                         final_value;                   \
    FINAL_VALUE_RANGE,                   final_value_range;             \
    POSITION_LIMITS,                     position_limits;               \
    FINAL_VALUE_CUTOFF_HI,               final_value_cutoff_hi;         \
    FINAL_VALUE_CUTOFF_LO,               final_value_cutoff_lo;         \
    FINAL_POSITION_VALUE,                final_position_value;          \
    ACTIVATE_CONTROL_SET,                activate_control_set;          \
    ACTIVE_CONTROL_SET,                  active_control_set;            \
    CUSTOM_CONTROL_SET,                  custom_control_set;            \
    BACKUP_CONTROL_SET,                  backup_control_set;            \
    TRAVEL_CALIBRATION,                  travel_calibration;             \
    TRAVEL,                              travel;                        \
    WORKING_SP,                          working_sp;                    \
    WORKING_POS,                         working_pos;                   \
    DEVIATION_ALERT,                     svi2_deviation_alert;               \
    POSITION_HIHI_ALERT,                 position_hihi_alert;           \
    POSITION_HI_ALERT,                   position_hi_alert;             \
    POSITION_LO_ALERT,                   position_lo_alert;             \
    POSITION_LOLO_ALERT,                 position_lolo_alert;           \
    TRAVEL_ACCUMULATION_A_ALERT,         travel_accumulation_a_alert;   \
    TRAVEL_ACCUMULATION_B_ALERT,         travel_accumulation_b_alert;   \
    TRAVEL_ACCUMULATION_TREND,           travel_accumulation_trend;     \
    CYCLE_COUNTER_A_ALERT,               svi2_cycle_counter_a_alert;         \
    CYCLE_COUNTER_B_ALERT,               cycle_counter_b_alert;         \
    CYCLE_COUNTER_TREND,                 cycle_counter_trend;           \
    POSITION_ERROR_TREND,                position_error_trend;          \
    POSITION_HISTOGRAM,                  position_histogram;            \
    NEAR_CLOSED_ALERT,                   near_closed_alert;             \
    POSITION_ERROR_HISTOGRAM,            position_error_histogram;      \
    SETPOINT_TIMEOUT_ALERT,              setpoint_timeout_alert;        \
    XD_FSTATE,                           xd_fstate;                     \
    CHAR_SELECTION,                      char_selection;                \
    CURRENT_CHAR_POINTS,                 current_char_points;           \
    CUSTOM_CHAR,                         custom_char;                   \
    CUSTOM_CHAR_POINTS,                  custom_char_points;            \
    READBACK_SELECT,                     readback_select;               \
    TRANSDUCER_TYPE,                     transducer_type;               \
    XD_ERROR_PRESSURE,                   xd_error_pressure;             \
    SUPPLY_PRESSURE,                     supply_pressure;               \
    PRESSURE_RANGE,                      pressure_range;                \
    SUPPLY_PRESSURE_HI_ALERT,            supply_pressure_hi_alert;      \
    SUPPLY_PRESSURE_LO_ALERT,            supply_pressure_lo_alert;      \
    SUPPLY_PRESSURE_LOLO_ALERT,          supply_pressure_lolo_alert;    \
    ACTUATOR_A_PRESSURE,                 actuator_a_pressure;           \
    ACTUATOR_B_PRESSURE,                 actuator_b_pressure;           \
    ATMOSPHERIC_PRESSURE,                atmospheric_pressure;          \
    PILOT_PRESSURE,                      pilot_pressure;                \
    /* PRESSURE_CALIBRATION,                pressure_calibration;  */         \
    /* SET_TO_FACTORY_PR_CALIBRATION,       set_to_factory_pr_calibration; */ \
    TEMP_TRANSDUCER_TYPE,                temp_transducer_type;          \
    XD_ERROR_TEMPERATURE,                xd_error_temperature;          \
    TEMPERATURE,                         temperature;                   \
    TEMPERATURE_HI_ALERT,                temperature_hi_alert;          \
    TEMPERATURE_LO_ALERT,                temperature_lo_alert;          \
    IP_DRIVE_CURRENT,                    ip_drive_current;              \
    IP_DRIVE_CURRENT_HI_ALERT,           ip_drive_current_hi_alert;     \
    IP_DRIVE_CURRENT_LO_ALERT,           ip_drive_current_lo_alert;     \
    FIND_STOPS,                          find_stops;                    \
    OFFLINE_DIAGNOSTIC,                  offline_diagnostic;            \
    DIAGNOSTIC_CONFIGURATION,            diagnostic_configuration;      \
    DIAGNOSTIC_DATA,                     diagnostic_data;               \
    AUTOTUNE,                            autotune;                      \
    /* AUTOTUNE_STATE,                      autotune_state; */                \
    /* TRAVEL_CALIBRATION,                  travel_calibration;  */           \
    CHECK_PROCESS,                       check_process;                 \
    UI_CUSTOM_CONFIGURATION,             ui_custom_configuration;       \
    FAILED_STATE,                        failed_state;                  \
    FINAL_VALUE_D,                       final_value_d;                 \
    FINAL_POSITION_VALUE_D,              final_position_value_d;        \
    FINAL_VALUE_DINT,                    final_value_dint;              \
    FINAL_POSITION_VALUE_DINT,           final_position_value_dint;     \
    /* FSC_SET_D,                           fsc_set_d; */                     \
    /* FSC_ACTUAL_D,                        fsc_actual_d; */                  \
    DISCRETE_OUTPUT_1_STATE,             discrete_output_1_state;             \
    DISCRETE_OUTPUT_2_STATE,             discrete_output_2_state;             \
    DISCRETE_INPUT,                      discrete_input;            \
    DISCRETE_SWITCH_1_CONF,              discrete_switch_1_conf;        \
    DISCRETE_SWITCH_2_CONF,              discrete_switch_2_conf;        \
    UI_ACCESS_CONTROL,                   ui_access_control;             \
    UI_LANGUAGE,                         ui_language;                   \
    APP_MODE,                            app_mode;                      \
    COMPLETE_STATUS,                     complete_status;               \
    CLEAR_STATUS,                        clear_status;                  \
    OPEN_STOP_ADJUSTMENT,                open_stop_adjustment;          \
    SETPOINT_SOURCE,                     setpoint_source;               \
    SETPOINT,                            setpoint;                      \
    /* MANUAL_SETPOINT,                     manual_setpoint; */ \
    ACTUAL_POSITION,                     actual_position;               \
    RAW_POSITION,                        raw_position; \
    /* WRONG_CONFIGURATION,                 wrong_configuration; */           \
    ALERT_ACTION,                        alert_action;                  \
    ALERT_STATE,                         alert_state;                   \
    ALERT_COUNTERS,                      alert_counters;                \
    ALERT_LOG,                           alert_log;                     \
    WORKING_TIMES,                       working_times;                 \
    WORKING_TIME_ALERT,                  working_time_alert;            \
    FACTORY_USE_1,                       factory_use_1;                 \
    FACTORY_USE_2,                       factory_use_2;                 \
    ACTUATOR_1,                          actuator_1;                    \
    ACTUATOR_2,                          actuator_2;                    \
    ACTUATOR_3,                          actuator_3;                    \
    ACTUATOR_INFO,                       actuator_info;                 \
    VALVE_IDENTIFICATION,                valve_identification;          \
    VALVE_SERVICE,                       valve_service;                 \
    VALVE_BODY_1,                        valve_body_1;                  \
    VALVE_BODY_2,                        valve_body_2;                  \
    VALVE_BODY_3,                        valve_body_3;                  \
    VALVE_INFO,                          valve_info;                    \
    BOOSTER,                             booster;                       \
    ACCESSORY,                           accessory;                     \
    POSITION_EXTREMES,                   position_extremes;             \
    PRESSURE_EXTREMES,                   pressure_extremes;             \
    TEMPERATURE_EXTREMES,                temperature_extremes;          \
    IP_CURRENT_EXTREMES,                 ip_current_extremes;           \
    ADVANCED,                            advanced;                      \
    BLOCK_ERR_DESC_1,                    tb_block_err_desc_1

