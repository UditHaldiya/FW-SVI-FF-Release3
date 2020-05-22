/* Public definitions for NVRAM layout version 3
*/
#ifndef FFP_VERDUMP_3_H_
#define FFP_VERDUMP_3_H_
#define FFP_NVRAMID_StartupVersionNumber_3 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFP_NVRAMID_ConfigurationChanged_3 1U //NVRAM area id for the type ConfigurationChanged_t
#define FFP_NVRAMID_AdvancedParam_3 2U //NVRAM area id for the type AdvancedParam_t
#define FFP_NVRAMID_logdata_3 3U //NVRAM area id for the type logdata_t
#define FFP_NVRAMID_FactoryDefaultState_3 4U //NVRAM area id for the type FactoryDefaultState_t
#define FFP_NVRAMID_ApplDeviceId_3 5U //NVRAM area id for the type ApplDeviceId_t
#define FFP_NVRAMID_nv_fb_link_cfg_3 6U //NVRAM area id for the type nv_fb_link_cfg_t
#define FFP_NVRAMID_nv_trend_cfg_3 7U //NVRAM area id for the type nv_trend_cfg_t
#define FFP_NVRAMID_nv_vcr_cfg_3 8U //NVRAM area id for the type nv_vcr_cfg_t
#define FFP_NVRAMID_nv_fb_start_cfg_3 9U //NVRAM area id for the type nv_fb_start_cfg_t
#define FFP_NVRAMID_nv_las_cfg_3 10U //NVRAM area id for the type nv_las_cfg_t
#define FFP_NVRAMID_NV_fb_3 11U //NVRAM area id for the type NV_fb_t
#define FFP_NVRAMID_nv_fdc_blk_base_cfg_3 12U //NVRAM area id for the type nv_fdc_blk_base_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_base_cfg_3 13U //NVRAM area id for the type nv_fdc_blk_dll_base_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_sm_cfg_3 14U //NVRAM area id for the type nv_fdc_blk_sm_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_lm_info_cfg_3 15U //NVRAM area id for the type nv_fdc_blk_dll_lm_info_cfg_t
#define FFP_NVRAMID_nv_fdc_blk_dll_lm_data_cfg_3 16U //NVRAM area id for the type nv_fdc_blk_dll_lm_data_cfg_t
#define FFP_NVRAMID_nv_swdl_blk_dwnld_cfg_3 17U //NVRAM area id for the type nv_swdl_blk_dwnld_cfg_t
#define FFP_NVRAMID_ST_ptb_3 18U //NVRAM area id for the type ST_ptb_t
#define FFP_NVRAMID_ST_resb_3 19U //NVRAM area id for the type ST_resb_t
#define FFP_NVRAMID_ST_aifb_3 20U //NVRAM area id for the type ST_aifb_t
#define FFP_NVRAMID_ST_aofb_3 23U //NVRAM area id for the type ST_aofb_t
#define FFP_NVRAMID_ST_difb_3 24U //NVRAM area id for the type ST_difb_t
#define FFP_NVRAMID_ST_dofb_3 26U //NVRAM area id for the type ST_dofb_t
#define FFP_NVRAMID_ST_maifb_3 28U //NVRAM area id for the type ST_maifb_t
#define FFP_NVRAMID_ST_pidfb_3 29U //NVRAM area id for the type ST_pidfb_t
#define FFP_NVRAMID_ST_isfb_3 31U //NVRAM area id for the type ST_isfb_t
#define FFP_NVRAMID_ST_osfb_3 32U //NVRAM area id for the type ST_osfb_t
#define FFP_NVRAMID_ST_csfb_3 33U //NVRAM area id for the type ST_csfb_t
#define FFP_NVRAMID_ST_arfb_3 34U //NVRAM area id for the type ST_arfb_t
#define FFP_NVRAMID_MN_NV_TRAVEL_CALIBRATION_3 35U //NVRAM area id for the type MN_NV_TRAVEL_CALIBRATION_t
#define FFP_NVRAMID_MN_NV_TRAVEL_3 36U //NVRAM area id for the type MN_NV_TRAVEL_t
#define FFP_NVRAMID_MN_NV_MN_DEVIATION_ALERT_3 37U //NVRAM area id for the type MN_NV_MN_DEVIATION_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_HIHI_ALERT_3 38U //NVRAM area id for the type MN_NV_POSITION_HIHI_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_HI_ALERT_3 39U //NVRAM area id for the type MN_NV_POSITION_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_LO_ALERT_3 40U //NVRAM area id for the type MN_NV_POSITION_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_POSITION_LOLO_ALERT_3 41U //NVRAM area id for the type MN_NV_POSITION_LOLO_ALERT_t
#define FFP_NVRAMID_MN_NV_NEAR_CLOSED_ALERT_3 42U //NVRAM area id for the type MN_NV_NEAR_CLOSED_ALERT_t
#define FFP_NVRAMID_MN_NV_SETPOINT_TIMEOUT_ALERT_3 43U //NVRAM area id for the type MN_NV_SETPOINT_TIMEOUT_ALERT_t
#define FFP_NVRAMID_MN_NV_XD_FSTATE_3 44U //NVRAM area id for the type MN_NV_XD_FSTATE_t
#define FFP_NVRAMID_MN_NV_READBACK_SELECT_3 45U //NVRAM area id for the type MN_NV_READBACK_SELECT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_HI_ALERT_3 46U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_LO_ALERT_3 47U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_SUPPLY_PRESSURE_LOLO_ALERT_3 48U //NVRAM area id for the type MN_NV_SUPPLY_PRESSURE_LOLO_ALERT_t
#define FFP_NVRAMID_MN_NV_TEMPERATURE_HI_ALERT_3 49U //NVRAM area id for the type MN_NV_TEMPERATURE_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_TEMPERATURE_LO_ALERT_3 50U //NVRAM area id for the type MN_NV_TEMPERATURE_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_IP_DRIVE_CURRENT_HI_ALERT_3 51U //NVRAM area id for the type MN_NV_IP_DRIVE_CURRENT_HI_ALERT_t
#define FFP_NVRAMID_MN_NV_IP_DRIVE_CURRENT_LO_ALERT_3 52U //NVRAM area id for the type MN_NV_IP_DRIVE_CURRENT_LO_ALERT_t
#define FFP_NVRAMID_MN_NV_UI_CUSTOM_CONFIGURATION_3 53U //NVRAM area id for the type MN_NV_UI_CUSTOM_CONFIGURATION_t
#define FFP_NVRAMID_MN_NV_FAILED_STATE_3 54U //NVRAM area id for the type MN_NV_FAILED_STATE_t
#define FFP_NVRAMID_MN_NV_DISCRETE_SWITCH_1_CONF_3 55U //NVRAM area id for the type MN_NV_DISCRETE_SWITCH_1_CONF_t
#define FFP_NVRAMID_MN_NV_DISCRETE_SWITCH_2_CONF_3 56U //NVRAM area id for the type MN_NV_DISCRETE_SWITCH_2_CONF_t
#define FFP_NVRAMID_MN_NV_SETPOINT_SOURCE_3 57U //NVRAM area id for the type MN_NV_SETPOINT_SOURCE_t
#define FFP_NVRAMID_MN_NV_ALERT_ACTION_3 58U //NVRAM area id for the type MN_NV_ALERT_ACTION_t
#define FFP_NVRAMID_MN_NV_ALERT_COUNTERS_3 59U //NVRAM area id for the type MN_NV_ALERT_COUNTERS_t
#define FFP_NVRAMID_MN_NV_WORKING_TIMES_3 60U //NVRAM area id for the type MN_NV_WORKING_TIMES_t
#define FFP_NVRAMID_MN_NV_WORKING_TIME_ALERT_3 61U //NVRAM area id for the type MN_NV_WORKING_TIME_ALERT_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_1_3 62U //NVRAM area id for the type MN_NV_ACTUATOR_1_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_2_3 63U //NVRAM area id for the type MN_NV_ACTUATOR_2_t
#define FFP_NVRAMID_MN_NV_ACTUATOR_INFO_3 64U //NVRAM area id for the type MN_NV_ACTUATOR_INFO_t
#define FFP_NVRAMID_MN_NV_VALVE_IDENTIFICATION_3 65U //NVRAM area id for the type MN_NV_VALVE_IDENTIFICATION_t
#define FFP_NVRAMID_MN_NV_VALVE_SERVICE_3 66U //NVRAM area id for the type MN_NV_VALVE_SERVICE_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_1_3 67U //NVRAM area id for the type MN_NV_VALVE_BODY_1_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_2_3 68U //NVRAM area id for the type MN_NV_VALVE_BODY_2_t
#define FFP_NVRAMID_MN_NV_VALVE_BODY_3_3 69U //NVRAM area id for the type MN_NV_VALVE_BODY_3_t
#define FFP_NVRAMID_MN_NV_VALVE_INFO_3 70U //NVRAM area id for the type MN_NV_VALVE_INFO_t
#define FFP_NVRAMID_MN_NV_BOOSTER_3 71U //NVRAM area id for the type MN_NV_BOOSTER_t
#define FFP_NVRAMID_MN_NV_ACCESSORY_3 72U //NVRAM area id for the type MN_NV_ACCESSORY_t
#define FFP_NVRAMID_HistogramPosNV_3 73U //NVRAM area id for the type HistogramPosNV_t
#define FFP_NVRAMID_HistogramPosErrNV_3 74U //NVRAM area id for the type HistogramPosErrNV_t
#define FFP_NVRAMID_TrendInfo_3 75U //NVRAM area id for the type TrendInfo_t
#define FFP_NVRAMID_PresAlertConf_3 78U //NVRAM area id for the type PresAlertConf_t
#define FFP_NVRAMID_Act3Min_3 81U //NVRAM area id for the type Act3Min_t
#define FFP_NVRAMID_CycleCounterAlert_3 82U //NVRAM area id for the type CycleCounterAlert_t
#define FFP_NVRAMID_TravelAlert_3 83U //NVRAM area id for the type TravelAlert_t
#define FFP_NVRAMID_APPHeader_3 84U //NVRAM area id for the type APPHeader_t
#define FFP_NVRAMID_FWDLInfo_3 85U //NVRAM area id for the type FWDLInfo_t
#define FFP_NVRAM_ENTRIES_VER_3 (86U)
extern const struct
   nvramDumpMap_t
       FFP_nvram_map_3[FFP_NVRAM_ENTRIES_VER_3];
extern const struct nvramDumpMap_t FFP_LogFileBuf_3;
#endif //FFP_VERDUMP_3_H_
