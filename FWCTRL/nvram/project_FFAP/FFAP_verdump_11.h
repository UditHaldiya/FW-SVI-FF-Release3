/* Public definitions for NVRAM layout version 11
*/
#ifndef FFAP_VERDUMP_11_H_
#define FFAP_VERDUMP_11_H_
#define FFAP_NVRAMID_StartupVersionNumber_11 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFAP_NVRAMID_ModeData_11 1U //NVRAM area id for the type ModeData_t
#define FFAP_NVRAMID_DigitalSpConf_11 2U //NVRAM area id for the type DigitalSpConf_t
#define FFAP_NVRAMID_digitalsp_11 3U //NVRAM area id for the type digitalsp_t
#define FFAP_NVRAMID_BoardTemperature_11 4U //NVRAM area id for the type BoardTemperature_t
#define FFAP_NVRAMID_PressureCalData_11 5U //NVRAM area id for the type PressureCalData_t
#define FFAP_NVRAMID_PositionConf_11 6U //NVRAM area id for the type PositionConf_t
#define FFAP_NVRAMID_PIDData_11 7U //NVRAM area id for the type PIDData_t
#define FFAP_NVRAMID_ErrorLimits_11 15U //NVRAM area id for the type ErrorLimits_t
#define FFAP_NVRAMID_CtlLimits_11 16U //NVRAM area id for the type CtlLimits_t
#define FFAP_NVRAMID_logdata_11 17U //NVRAM area id for the type logdata_t
#define FFAP_NVRAMID_ContinuousDiagnostics_11 18U //NVRAM area id for the type ContinuousDiagnostics_t
#define FFAP_NVRAMID_SwitchConfiguration_11 19U //NVRAM area id for the type SwitchConfiguration_t
#define FFAP_NVRAMID_OptionConfig_11 20U //NVRAM area id for the type OptionConfig_t
#define FFAP_NVRAMID_BiasData_11 21U //NVRAM area id for the type BiasData_t
#define FFAP_NVRAMID_BiasExt_11 22U //NVRAM area id for the type BiasExt_t
#define FFAP_NVRAMID_TuneData_11 23U //NVRAM area id for the type TuneData_t
#define FFAP_NVRAMID_ConfigurationChanged_11 24U //NVRAM area id for the type ConfigurationChanged_t
#define FFAP_NVRAMID_inpv_TCalRow_11 25U //NVRAM area id for the type inpv_TCalRow_t
#define FFAP_NVRAMID_pres1_TCalRow_11 26U //NVRAM area id for the type pres1_TCalRow_t
#define FFAP_NVRAMID_TemperatureConf_11 27U //NVRAM area id for the type TemperatureConf_t
#define FFAP_NVRAMID_tempr_TCalRow_11 28U //NVRAM area id for the type tempr_TCalRow_t
#define FFAP_NVRAMID_SensorType_11 29U //NVRAM area id for the type SensorType_t
#define FFAP_NVRAMID_posext_TCalRow_11 30U //NVRAM area id for the type posext_TCalRow_t
#define FFAP_NVRAMID_posint_TCalRow_11 31U //NVRAM area id for the type posint_TCalRow_t
#define FFAP_NVRAMID_presatm_TCalRow_11 32U //NVRAM area id for the type presatm_TCalRow_t
#define FFAP_NVRAMID_pres3_TCalRow_11 33U //NVRAM area id for the type pres3_TCalRow_t
#define FFAP_NVRAMID_pres2_TCalRow_11 34U //NVRAM area id for the type pres2_TCalRow_t
#define FFAP_NVRAMID_prespilot_TCalRow_11 35U //NVRAM area id for the type prespilot_TCalRow_t
#define FFAP_NVRAMID_ipcurr_TCalRow_11 36U //NVRAM area id for the type ipcurr_TCalRow_t
#define FFAP_NVRAMID_pwmcomp_TCalRow_11 37U //NVRAM area id for the type pwmcomp_TCalRow_t
#define FFAP_NVRAMID_TemperatureCalibrationPoints_11 38U //NVRAM area id for the type TemperatureCalibrationPoints_t
#define FFAP_NVRAMID_HartData_11 39U //NVRAM area id for the type HartData_t
#define FFAP_NVRAMID_PosCharactSel_11 40U //NVRAM area id for the type PosCharactSel_t
#define FFAP_NVRAMID_PosCharact_11 41U //NVRAM area id for the type PosCharact_t
#define FFAP_NVRAMID_FaultCodeData_11 42U //NVRAM area id for the type FaultCodeData_t
#define FFAP_NVRAMID_LCDContrasts_11 43U //NVRAM area id for the type LCDContrasts_t
#define FFAP_NVRAMID_LowPowerData_11 44U //NVRAM area id for the type LowPowerData_t
#define FFAP_NVRAMID_UIData_11 45U //NVRAM area id for the type UIData_t
#define FFAP_NVRAMID_PneumaticParams_11 46U //NVRAM area id for the type PneumaticParams_t
#define FFAP_NVRAMID_ActivateVerifyData_11 47U //NVRAM area id for the type ActivateVerifyData_t
#define FFAP_NVRAMID_CtlSetSlot_11 48U //NVRAM area id for the type CtlSetSlot_t
#define FFAP_NVRAMID_UnitsOptions_11 49U //NVRAM area id for the type UnitsOptions_t
#define FFAP_NVRAMID_UnitsConfig_11 50U //NVRAM area id for the type UnitsConfig_t
#define FFAP_NVRAMID_InterfaceAccess_11 51U //NVRAM area id for the type InterfaceAccess_t
#define FFAP_NVRAMID_RefVoltage_11 52U //NVRAM area id for the type RefVoltage_t
#define FFAP_NVRAMID_FFData_11 53U //NVRAM area id for the type FFData_t
#define FFAP_NVRAMID_PSTSchedTime_11 54U //NVRAM area id for the type PSTSchedTime_t
#define FFAP_NVRAMID_PSTConf_11 55U //NVRAM area id for the type PSTConf_t
#define FFAP_NVRAMID_PSTrigger_11 56U //NVRAM area id for the type PSTrigger_t
#define FFAP_NVRAMID_DatahogConf_11 57U //NVRAM area id for the type DatahogConf_t
#define FFAP_NVRAMID_DhogTriggerConf_11 58U //NVRAM area id for the type DhogTriggerConf_t
#define FFAP_NVRAMID_FactoryDefaultState_11 59U //NVRAM area id for the type FactoryDefaultState_t
#define FFAP_NVRAM_ENTRIES_VER_11 (60U)
extern const struct
   nvramDumpMap_t
       FFAP_nvram_map_11[FFAP_NVRAM_ENTRIES_VER_11];
extern const struct nvramDumpMap_t FFAP_LogFileBuf_11;
#endif //FFAP_VERDUMP_11_H_
