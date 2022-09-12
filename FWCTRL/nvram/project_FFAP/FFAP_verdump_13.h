/* Public definitions for NVRAM layout version 13
*/
#ifndef FFAP_VERDUMP_13_H_
#define FFAP_VERDUMP_13_H_
#define FFAP_NVRAMID_StartupVersionNumber_13 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFAP_NVRAMID_ModeData_13 1U //NVRAM area id for the type ModeData_t
#define FFAP_NVRAMID_DigitalSpConf_13 2U //NVRAM area id for the type DigitalSpConf_t
#define FFAP_NVRAMID_digitalsp_13 3U //NVRAM area id for the type digitalsp_t
#define FFAP_NVRAMID_BoardTemperature_13 4U //NVRAM area id for the type BoardTemperature_t
#define FFAP_NVRAMID_PressureCalData_13 5U //NVRAM area id for the type PressureCalData_t
#define FFAP_NVRAMID_PositionConf_13 6U //NVRAM area id for the type PositionConf_t
#define FFAP_NVRAMID_PIDData_13 7U //NVRAM area id for the type PIDData_t
#define FFAP_NVRAMID_ErrorLimits_13 15U //NVRAM area id for the type ErrorLimits_t
#define FFAP_NVRAMID_CtlLimits_13 16U //NVRAM area id for the type CtlLimits_t
#define FFAP_NVRAMID_logdata_13 17U //NVRAM area id for the type logdata_t
#define FFAP_NVRAMID_ContinuousDiagnostics_13 18U //NVRAM area id for the type ContinuousDiagnostics_t
#define FFAP_NVRAMID_SwitchConfiguration_13 19U //NVRAM area id for the type SwitchConfiguration_t
#define FFAP_NVRAMID_OptionConfig_13 20U //NVRAM area id for the type OptionConfig_t
#define FFAP_NVRAMID_BiasData_13 21U //NVRAM area id for the type BiasData_t
#define FFAP_NVRAMID_BiasExt_13 22U //NVRAM area id for the type BiasExt_t
#define FFAP_NVRAMID_TuneData_13 23U //NVRAM area id for the type TuneData_t
#define FFAP_NVRAMID_ConfigurationChanged_13 24U //NVRAM area id for the type ConfigurationChanged_t
#define FFAP_NVRAMID_inpv_TCalRow_13 25U //NVRAM area id for the type inpv_TCalRow_t
#define FFAP_NVRAMID_pres1_TCalRow_13 26U //NVRAM area id for the type pres1_TCalRow_t
#define FFAP_NVRAMID_TemperatureConf_13 27U //NVRAM area id for the type TemperatureConf_t
#define FFAP_NVRAMID_tempr_TCalRow_13 28U //NVRAM area id for the type tempr_TCalRow_t
#define FFAP_NVRAMID_SensorType_13 29U //NVRAM area id for the type SensorType_t
#define FFAP_NVRAMID_posext_TCalRow_13 30U //NVRAM area id for the type posext_TCalRow_t
#define FFAP_NVRAMID_posint_TCalRow_13 31U //NVRAM area id for the type posint_TCalRow_t
#define FFAP_NVRAMID_presatm_TCalRow_13 32U //NVRAM area id for the type presatm_TCalRow_t
#define FFAP_NVRAMID_pres3_TCalRow_13 33U //NVRAM area id for the type pres3_TCalRow_t
#define FFAP_NVRAMID_pres2_TCalRow_13 34U //NVRAM area id for the type pres2_TCalRow_t
#define FFAP_NVRAMID_prespilot_TCalRow_13 35U //NVRAM area id for the type prespilot_TCalRow_t
#define FFAP_NVRAMID_ipcurr_TCalRow_13 36U //NVRAM area id for the type ipcurr_TCalRow_t
#define FFAP_NVRAMID_pwmcomp_TCalRow_13 37U //NVRAM area id for the type pwmcomp_TCalRow_t
#define FFAP_NVRAMID_TemperatureCalibrationPoints_13 38U //NVRAM area id for the type TemperatureCalibrationPoints_t
#define FFAP_NVRAMID_HartData_13 39U //NVRAM area id for the type HartData_t
#define FFAP_NVRAMID_PosCharactSel_13 40U //NVRAM area id for the type PosCharactSel_t
#define FFAP_NVRAMID_PosCharact_13 41U //NVRAM area id for the type PosCharact_t
#define FFAP_NVRAMID_FaultCodeData_13 42U //NVRAM area id for the type FaultCodeData_t
#define FFAP_NVRAMID_LCDContrasts_13 43U //NVRAM area id for the type LCDContrasts_t
#define FFAP_NVRAMID_LowPowerData_13 44U //NVRAM area id for the type LowPowerData_t
#define FFAP_NVRAMID_UIData_13 45U //NVRAM area id for the type UIData_t
#define FFAP_NVRAMID_PneumaticParams_13 46U //NVRAM area id for the type PneumaticParams_t
#define FFAP_NVRAMID_ActivateVerifyData_13 47U //NVRAM area id for the type ActivateVerifyData_t
#define FFAP_NVRAMID_CtlSetSlot_13 48U //NVRAM area id for the type CtlSetSlot_t
#define FFAP_NVRAMID_UnitsOptions_13 49U //NVRAM area id for the type UnitsOptions_t
#define FFAP_NVRAMID_UnitsConfig_13 50U //NVRAM area id for the type UnitsConfig_t
#define FFAP_NVRAMID_InterfaceAccess_13 51U //NVRAM area id for the type InterfaceAccess_t
#define FFAP_NVRAMID_RefVoltage_13 52U //NVRAM area id for the type RefVoltage_t
#define FFAP_NVRAMID_FFData_13 53U //NVRAM area id for the type FFData_t
#define FFAP_NVRAMID_PSTSchedTime_13 54U //NVRAM area id for the type PSTSchedTime_t
#define FFAP_NVRAMID_PSTConf_13 55U //NVRAM area id for the type PSTConf_t
#define FFAP_NVRAMID_PSTrigger_13 56U //NVRAM area id for the type PSTrigger_t
#define FFAP_NVRAMID_DatahogConf_13 57U //NVRAM area id for the type DatahogConf_t
#define FFAP_NVRAMID_DhogTriggerConf_13 58U //NVRAM area id for the type DhogTriggerConf_t
#define FFAP_NVRAMID_FactoryDefaultState_13 59U //NVRAM area id for the type FactoryDefaultState_t
#define FFAP_NVRAM_ENTRIES_VER_13 (60U)
extern const struct
   nvramDumpMap_t
       FFAP_nvram_map_13[FFAP_NVRAM_ENTRIES_VER_13];
extern const struct nvramDumpMap_t FFAP_LogFileBuf_13;
#endif //FFAP_VERDUMP_13_H_
