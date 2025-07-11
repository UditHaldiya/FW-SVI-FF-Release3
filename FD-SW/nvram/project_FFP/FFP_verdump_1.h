/* Public definitions for NVRAM layout version 1
*/
#ifndef FFP_VERDUMP_1_H_
#define FFP_VERDUMP_1_H_
#define FFP_NVRAMID_StartupVersionNumber_1 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFP_NVRAMID_ConfigurationChanged_1 1U //NVRAM area id for the type ConfigurationChanged_t
#define FFP_NVRAMID_AdvancedParam_1 2U //NVRAM area id for the type AdvancedParam_t
#define FFP_NVRAMID_logdata_1 3U //NVRAM area id for the type logdata_t
#define FFP_NVRAMID_FactoryDefaultState_1 4U //NVRAM area id for the type FactoryDefaultState_t
#define FFP_NVRAMID_ApplDeviceId_1 5U //NVRAM area id for the type ApplDeviceId_t
#define FFP_NVRAMID_nv_fb_link_cfg_1 6U //NVRAM area id for the type nv_fb_link_cfg_t
#define FFP_NVRAMID_nv_trend_cfg_1 7U //NVRAM area id for the type nv_trend_cfg_t
#define FFP_NVRAMID_nv_vcr_cfg_1 8U //NVRAM area id for the type nv_vcr_cfg_t
#define FFP_NVRAMID_nv_fb_start_cfg_1 9U //NVRAM area id for the type nv_fb_start_cfg_t
#define FFP_NVRAMID_nv_las_cfg_1 10U //NVRAM area id for the type nv_las_cfg_t
#define FFP_NVRAMID_NV_fb_1 11U //NVRAM area id for the type NV_fb_t
#define FFP_NVRAMID_nv_fdc_blk_base_cfg_1 12U //NVRAM area id for the type nv_fdc_blk_base_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_base_cfg_1 13U //NVRAM area id for the type nv_fdc_blk_dll_base_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_sm_cfg_1 14U //NVRAM area id for the type nv_fdc_blk_sm_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_lm_info_cfg_1 15U //NVRAM area id for the type nv_fdc_blk_dll_lm_info_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_lm_data_cfg_1 16U //NVRAM area id for the type nv_fdc_blk_dll_lm_data_cfg_t
#define FFP_NVRAMID_nv_swdl_blk_dwnld_cfg_1 17U //NVRAM area id for the type nv_swdl_blk_dwnld_cfg_t
#define FFP_NVRAMID_ST_ptb_1 18U //NVRAM area id for the type ST_ptb_t
#define FFP_NVRAMID_ST_resb_1 19U //NVRAM area id for the type ST_resb_t
#define FFP_NVRAMID_ST_aifb_1 20U //NVRAM area id for the type ST_aifb_t
#define FFP_NVRAMID_ST_aofb_1 23U //NVRAM area id for the type ST_aofb_t
#define FFP_NVRAMID_ST_difb_1 24U //NVRAM area id for the type ST_difb_t
#define FFP_NVRAMID_ST_dofb_1 26U //NVRAM area id for the type ST_dofb_t
#define FFP_NVRAMID_ST_maifb_1 28U //NVRAM area id for the type ST_maifb_t
#define FFP_NVRAMID_ST_pidfb_1 29U //NVRAM area id for the type ST_pidfb_t
#define FFP_NVRAMID_ST_isfb_1 31U //NVRAM area id for the type ST_isfb_t
#define FFP_NVRAMID_ST_osfb_1 32U //NVRAM area id for the type ST_osfb_t
#define FFP_NVRAMID_ST_csfb_1 33U //NVRAM area id for the type ST_csfb_t
#define FFP_NVRAMID_ST_arfb_1 34U //NVRAM area id for the type ST_arfb_t
#define FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_1 35U //NVRAM area id for the type MN_NV_TRAVEL_CALIBRATION_t
#define FFP_NVRAMID_MN_NV_DEVIATION_ALERT_1 36U //NVRAM area id for the type MN_NV_DEVIATION_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_HIHI_ALERT_1 37U //NVRAM area id for the type MN_NV_POSITION_HIHI_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_HI_ALERT_1 38U //NVRAM area id for the type MN_NV_POSITION_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_LO_ALERT_1 39U //NVRAM area id for the type MN_NV_POSITION_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_LOLO_ALERT_1 40U //NVRAM area id for the type MN_NV_POSITION_LOLO_ALERT_t
#define FFP_NVRAMID_MN_NV_TRAVEL_ACCUMULATION_TREND_1 41U //NVRAM area id for the type MN_NV_TRAVEL_ACCUMULATION_TREND_t
#define FFP_NVRAMID_MN_NV_CYCLE_COUNTER_TREND_1 42U //NVRAM area id for the type MN_NV_CYCLE_COUNTER_TREND_t
#define FFP_NVRAMID_MN_NV_POSITION_ERROR_TREND_1 43U //NVRAM area id for the type MN_NV_POSITION_ERROR_TREND_t
#define FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_1 44U //NVRAM area id for the type MN_NV_NEAR_CLOSED_ALERT_t
#define FFP_NVRAMID_MN_NV_SETPOINT_TIMEOUT_ALERT_1 45U //NVRAM area id for the type MN_NV_SETPOINT_TIMEOUT_ALERT_t
#define FFP_NVRAMID_MN_NV_XD_FSTATE_1 46U //NVRAM area id for the type MN_NV_XD_FSTATE_t
#define FFP_NVRAMID_MN_NV_READBACK_SELECT_1 47U //NVRAM area id for the type MN_NV_READBACK_SELECT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_HI_ALERT_1 48U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_LO_ALERT_1 49U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_LOLO_ALERT_1 50U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_LOLO_ALERT_t
#define FFP_NVRAMID_MN_NV_TEMPERATURE_HI_ALERT_1 51U //NVRAM area id for the type MN_NV_TEMPERATURE_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_TEMPERATURE_LO_ALERT_1 52U //NVRAM area id for the type MN_NV_TEMPERATURE_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_IP_DRIVE_CURRENT_HI_ALERT_1 53U //NVRAM area id for the type MN_NV_IP_DRIVE_CURRENT_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_IP_DRIVE_CURRENT_LO_ALERT_1 54U //NVRAM area id for the type MN_NV_IP_DRIVE_CURRENT_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_UI_CUSTOM_CONFIGURATION_1 55U //NVRAM area id for the type MN_NV_UI_CUSTOM_CONFIGURATION_t
#define FFP_NVRAMID_MN_NV_FAILED_STATE_1 56U //NVRAM area id for the type MN_NV_FAILED_STATE_t
#define FFP_NVRAMID_MN_NV_DISCRETE_SWITCH_1_CONF_1 57U //NVRAM area id for the type MN_NV_DISCRETE_SWITCH_1_CONF_t
#define FFP_NVRAMID_MN_NV_DISCRETE_SWITCH_2_CONF_1 58U //NVRAM area id for the type MN_NV_DISCRETE_SWITCH_2_CONF_t
#define FFP_NVRAMID_MN_NV_SETPOINT_SOURCE_1 59U //NVRAM area id for the type MN_NV_SETPOINT_SOURCE_t
#define FFP_NVRAMID_MN_NV_ALERT_ACTION_1 60U //NVRAM area id for the type MN_NV_ALERT_ACTION_t
#define FFP_NVRAMID_MN_NV_ALERT_COUNTERS_1 61U //NVRAM area id for the type MN_NV_ALERT_COUNTERS_t
#define FFP_NVRAMID_MN_NV_WORKING_TIMES_1 62U //NVRAM area id for the type MN_NV_WORKING_TIMES_t
#define FFP_NVRAMID_MN_NV_WORKING_TIME_ALERT_1 63U //NVRAM area id for the type MN_NV_WORKING_TIME_ALERT_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_1_1 64U //NVRAM area id for the type MN_NV_ACTUATOR_1_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_2_1 65U //NVRAM area id for the type MN_NV_ACTUATOR_2_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_INFO_1 66U //NVRAM area id for the type MN_NV_ACTUATOR_INFO_t
#define FFP_NVRAMID_MN_NV_VALVE_IDENTIFICATION_1 67U //NVRAM area id for the type MN_NV_VALVE_IDENTIFICATION_t
#define FFP_NVRAMID_MN_NV_VALVE_SERVICE_1 68U //NVRAM area id for the type MN_NV_VALVE_SERVICE_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_1_1 69U //NVRAM area id for the type MN_NV_VALVE_BODY_1_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_2_1 70U //NVRAM area id for the type MN_NV_VALVE_BODY_2_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_3_1 71U //NVRAM area id for the type MN_NV_VALVE_BODY_3_t
#define FFP_NVRAMID_MN_NV_VALVE_INFO_1 72U //NVRAM area id for the type MN_NV_VALVE_INFO_t
#define FFP_NVRAMID_MN_NV_BOOSTER_1 73U //NVRAM area id for the type MN_NV_BOOSTER_t
#define FFP_NVRAMID_MN_NV_ACCESSORY_1 74U //NVRAM area id for the type MN_NV_ACCESSORY_t
#define FFP_NVRAMID_HistogramPosNV_1 75U //NVRAM area id for the type HistogramPosNV_t
#define FFP_NVRAMID_HistogramPosErrNV_1 76U //NVRAM area id for the type HistogramPosErrNV_t
#define FFP_NVRAMID_Trend_Counter_1 77U //NVRAM area id for the type Trend_Counter_t
#define FFP_NVRAMID_PresAlertConf_1 80U //NVRAM area id for the type PresAlertConf_t
#define FFP_NVRAMID_Act3Min_1 83U //NVRAM area id for the type Act3Min_t
#define FFP_NVRAMID_CycleCounterAlert_1 84U //NVRAM area id for the type CycleCounterAlert_t
#define FFP_NVRAMID_TravelAlert_1 85U //NVRAM area id for the type TravelAlert_t
#define FFP_NVRAMID_APPHeader_1 86U //NVRAM area id for the type APPHeader_t
#define FFP_NVRAM_ENTRIES_VER_1 (87U)
extern const struct
   nvramDumpMap_t
       FFP_nvram_map_1[FFP_NVRAM_ENTRIES_VER_1];
extern const struct nvramDumpMap_t FFP_LogFileBuf_1;
#endif //FFP_VERDUMP_1_H_
