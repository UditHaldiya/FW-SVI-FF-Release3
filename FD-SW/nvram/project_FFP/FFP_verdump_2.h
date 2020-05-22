/* Public definitions for NVRAM layout version 2
*/
#ifndef FFP_VERDUMP_2_H_
#define FFP_VERDUMP_2_H_
#define FFP_NVRAMID_StartupVersionNumber_2 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFP_NVRAMID_ConfigurationChanged_2 1U //NVRAM area id for the type ConfigurationChanged_t
#define FFP_NVRAMID_AdvancedParam_2 2U //NVRAM area id for the type AdvancedParam_t
#define FFP_NVRAMID_logdata_2 3U //NVRAM area id for the type logdata_t
#define FFP_NVRAMID_FactoryDefaultState_2 4U //NVRAM area id for the type FactoryDefaultState_t
#define FFP_NVRAMID_ApplDeviceId_2 5U //NVRAM area id for the type ApplDeviceId_t
#define FFP_NVRAMID_nv_fb_link_cfg_2 6U //NVRAM area id for the type nv_fb_link_cfg_t
#define FFP_NVRAMID_nv_trend_cfg_2 7U //NVRAM area id for the type nv_trend_cfg_t
#define FFP_NVRAMID_nv_vcr_cfg_2 8U //NVRAM area id for the type nv_vcr_cfg_t
#define FFP_NVRAMID_nv_fb_start_cfg_2 9U //NVRAM area id for the type nv_fb_start_cfg_t
#define FFP_NVRAMID_nv_las_cfg_2 10U //NVRAM area id for the type nv_las_cfg_t
#define FFP_NVRAMID_NV_fb_2 11U //NVRAM area id for the type NV_fb_t
#define FFP_NVRAMID_nv_fdc_blk_base_cfg_2 12U //NVRAM area id for the type nv_fdc_blk_base_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_base_cfg_2 13U //NVRAM area id for the type nv_fdc_blk_dll_base_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_sm_cfg_2 14U //NVRAM area id for the type nv_fdc_blk_sm_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_lm_info_cfg_2 15U //NVRAM area id for the type nv_fdc_blk_dll_lm_info_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_lm_data_cfg_2 16U //NVRAM area id for the type nv_fdc_blk_dll_lm_data_cfg_t
#define FFP_NVRAMID_nv_swdl_blk_dwnld_cfg_2 17U //NVRAM area id for the type nv_swdl_blk_dwnld_cfg_t
#define FFP_NVRAMID_ST_ptb_2 18U //NVRAM area id for the type ST_ptb_t
#define FFP_NVRAMID_ST_resb_2 19U //NVRAM area id for the type ST_resb_t
#define FFP_NVRAMID_ST_aifb_2 20U //NVRAM area id for the type ST_aifb_t
#define FFP_NVRAMID_ST_aofb_2 23U //NVRAM area id for the type ST_aofb_t
#define FFP_NVRAMID_ST_difb_2 24U //NVRAM area id for the type ST_difb_t
#define FFP_NVRAMID_ST_dofb_2 26U //NVRAM area id for the type ST_dofb_t
#define FFP_NVRAMID_ST_maifb_2 28U //NVRAM area id for the type ST_maifb_t
#define FFP_NVRAMID_ST_pidfb_2 29U //NVRAM area id for the type ST_pidfb_t
#define FFP_NVRAMID_ST_isfb_2 31U //NVRAM area id for the type ST_isfb_t
#define FFP_NVRAMID_ST_osfb_2 32U //NVRAM area id for the type ST_osfb_t
#define FFP_NVRAMID_ST_csfb_2 33U //NVRAM area id for the type ST_csfb_t
#define FFP_NVRAMID_ST_arfb_2 34U //NVRAM area id for the type ST_arfb_t
#define FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_2 35U //NVRAM area id for the type MN_NV_TRAVEL_CALIBRATION_t
#define FFP_NVRAMID_MN_NV_DEVIATION_ALERT_2 36U //NVRAM area id for the type MN_NV_DEVIATION_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_HIHI_ALERT_2 37U //NVRAM area id for the type MN_NV_POSITION_HIHI_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_HI_ALERT_2 38U //NVRAM area id for the type MN_NV_POSITION_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_LO_ALERT_2 39U //NVRAM area id for the type MN_NV_POSITION_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_LOLO_ALERT_2 40U //NVRAM area id for the type MN_NV_POSITION_LOLO_ALERT_t
#define FFP_NVRAMID_MN_NV_TRAVEL_ACCUMULATION_TREND_2 41U //NVRAM area id for the type MN_NV_TRAVEL_ACCUMULATION_TREND_t
#define FFP_NVRAMID_MN_NV_CYCLE_COUNTER_TREND_2 42U //NVRAM area id for the type MN_NV_CYCLE_COUNTER_TREND_t
#define FFP_NVRAMID_MN_NV_POSITION_ERROR_TREND_2 43U //NVRAM area id for the type MN_NV_POSITION_ERROR_TREND_t
#define FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_2 44U //NVRAM area id for the type MN_NV_NEAR_CLOSED_ALERT_t
#define FFP_NVRAMID_MN_NV_SETPOINT_TIMEOUT_ALERT_2 45U //NVRAM area id for the type MN_NV_SETPOINT_TIMEOUT_ALERT_t
#define FFP_NVRAMID_MN_NV_XD_FSTATE_2 46U //NVRAM area id for the type MN_NV_XD_FSTATE_t
#define FFP_NVRAMID_MN_NV_READBACK_SELECT_2 47U //NVRAM area id for the type MN_NV_READBACK_SELECT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_HI_ALERT_2 48U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_LO_ALERT_2 49U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_LOLO_ALERT_2 50U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_LOLO_ALERT_t
#define FFP_NVRAMID_MN_NV_TEMPERATURE_HI_ALERT_2 51U //NVRAM area id for the type MN_NV_TEMPERATURE_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_TEMPERATURE_LO_ALERT_2 52U //NVRAM area id for the type MN_NV_TEMPERATURE_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_IP_DRIVE_CURRENT_HI_ALERT_2 53U //NVRAM area id for the type MN_NV_IP_DRIVE_CURRENT_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_IP_DRIVE_CURRENT_LO_ALERT_2 54U //NVRAM area id for the type MN_NV_IP_DRIVE_CURRENT_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_UI_CUSTOM_CONFIGURATION_2 55U //NVRAM area id for the type MN_NV_UI_CUSTOM_CONFIGURATION_t
#define FFP_NVRAMID_MN_NV_FAILED_STATE_2 56U //NVRAM area id for the type MN_NV_FAILED_STATE_t
#define FFP_NVRAMID_MN_NV_DISCRETE_SWITCH_1_CONF_2 57U //NVRAM area id for the type MN_NV_DISCRETE_SWITCH_1_CONF_t
#define FFP_NVRAMID_MN_NV_DISCRETE_SWITCH_2_CONF_2 58U //NVRAM area id for the type MN_NV_DISCRETE_SWITCH_2_CONF_t
#define FFP_NVRAMID_MN_NV_SETPOINT_SOURCE_2 59U //NVRAM area id for the type MN_NV_SETPOINT_SOURCE_t
#define FFP_NVRAMID_MN_NV_ALERT_ACTION_2 60U //NVRAM area id for the type MN_NV_ALERT_ACTION_t
#define FFP_NVRAMID_MN_NV_ALERT_COUNTERS_2 61U //NVRAM area id for the type MN_NV_ALERT_COUNTERS_t
#define FFP_NVRAMID_MN_NV_WORKING_TIMES_2 62U //NVRAM area id for the type MN_NV_WORKING_TIMES_t
#define FFP_NVRAMID_MN_NV_WORKING_TIME_ALERT_2 63U //NVRAM area id for the type MN_NV_WORKING_TIME_ALERT_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_1_2 64U //NVRAM area id for the type MN_NV_ACTUATOR_1_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_2_2 65U //NVRAM area id for the type MN_NV_ACTUATOR_2_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_INFO_2 66U //NVRAM area id for the type MN_NV_ACTUATOR_INFO_t
#define FFP_NVRAMID_MN_NV_VALVE_IDENTIFICATION_2 67U //NVRAM area id for the type MN_NV_VALVE_IDENTIFICATION_t
#define FFP_NVRAMID_MN_NV_VALVE_SERVICE_2 68U //NVRAM area id for the type MN_NV_VALVE_SERVICE_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_1_2 69U //NVRAM area id for the type MN_NV_VALVE_BODY_1_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_2_2 70U //NVRAM area id for the type MN_NV_VALVE_BODY_2_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_3_2 71U //NVRAM area id for the type MN_NV_VALVE_BODY_3_t
#define FFP_NVRAMID_MN_NV_VALVE_INFO_2 72U //NVRAM area id for the type MN_NV_VALVE_INFO_t
#define FFP_NVRAMID_MN_NV_BOOSTER_2 73U //NVRAM area id for the type MN_NV_BOOSTER_t
#define FFP_NVRAMID_MN_NV_ACCESSORY_2 74U //NVRAM area id for the type MN_NV_ACCESSORY_t
#define FFP_NVRAMID_HistogramPosNV_2 75U //NVRAM area id for the type HistogramPosNV_t
#define FFP_NVRAMID_HistogramPosErrNV_2 76U //NVRAM area id for the type HistogramPosErrNV_t
#define FFP_NVRAMID_Trend_Counter_2 77U //NVRAM area id for the type Trend_Counter_t
#define FFP_NVRAMID_PresAlertConf_2 80U //NVRAM area id for the type PresAlertConf_t
#define FFP_NVRAMID_Act3Min_2 83U //NVRAM area id for the type Act3Min_t
#define FFP_NVRAMID_CycleCounterAlert_2 84U //NVRAM area id for the type CycleCounterAlert_t
#define FFP_NVRAMID_TravelAlert_2 85U //NVRAM area id for the type TravelAlert_t
#define FFP_NVRAMID_APPHeader_2 86U //NVRAM area id for the type APPHeader_t
#define FFP_NVRAMID_FWDLInfo_2 87U //NVRAM area id for the type FWDLInfo_t
#define FFP_NVRAM_ENTRIES_VER_2 (88U)
extern const struct
   nvramDumpMap_t
       FFP_nvram_map_2[FFP_NVRAM_ENTRIES_VER_2];
extern const struct nvramDumpMap_t FFP_LogFileBuf_2;
#endif //FFP_VERDUMP_2_H_
