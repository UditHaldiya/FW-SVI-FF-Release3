/* Public definitions for NVRAM layout version 9
*/
#ifndef FFAP_VERDUMP_9_H_
#define FFAP_VERDUMP_9_H_
#define FFAP_NVRAMID_StartupVersionNumber_9 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFAP_NVRAMID_ModeData_9 1U //NVRAM area id for the type ModeData_t
#define FFAP_NVRAMID_DigitalSpConf_9 2U //NVRAM area id for the type DigitalSpConf_t
#define FFAP_NVRAMID_digitalsp_9 3U //NVRAM area id for the type digitalsp_t
#define FFAP_NVRAMID_BoardTemperature_9 4U //NVRAM area id for the type BoardTemperature_t
#define FFAP_NVRAMID_PressureCalData_9 5U //NVRAM area id for the type PressureCalData_t
#define FFAP_NVRAMID_PositionConf_9 6U //NVRAM area id for the type PositionConf_t
#define FFAP_NVRAMID_PIDData_9 7U //NVRAM area id for the type PIDData_t
#define FFAP_NVRAMID_ErrorLimits_9 15U //NVRAM area id for the type ErrorLimits_t
#define FFAP_NVRAMID_CtlLimits_9 16U //NVRAM area id for the type CtlLimits_t
#define FFAP_NVRAMID_logdata_9 17U //NVRAM area id for the type logdata_t
#define FFAP_NVRAMID_ContinuousDiagnostics_9 18U //NVRAM area id for the type ContinuousDiagnostics_t
#define FFAP_NVRAMID_SwitchConfiguration_9 19U //NVRAM area id for the type SwitchConfiguration_t
#define FFAP_NVRAMID_OptionConfig_9 20U //NVRAM area id for the type OptionConfig_t
#define FFAP_NVRAMID_BiasData_9 21U //NVRAM area id for the type BiasData_t
#define FFAP_NVRAMID_BiasExt_9 22U //NVRAM area id for the type BiasExt_t
#define FFAP_NVRAMID_TuneData_9 23U //NVRAM area id for the type TuneData_t
#define FFAP_NVRAMID_ConfigurationChanged_9 24U //NVRAM area id for the type ConfigurationChanged_t
#define FFAP_NVRAMID_inpv_TCalRow_9 25U //NVRAM area id for the type inpv_TCalRow_t
#define FFAP_NVRAMID_pres1_TCalRow_9 26U //NVRAM area id for the type pres1_TCalRow_t
#define FFAP_NVRAMID_TemperatureConf_9 27U //NVRAM area id for the type TemperatureConf_t
#define FFAP_NVRAMID_tempr_TCalRow_9 28U //NVRAM area id for the type tempr_TCalRow_t
#define FFAP_NVRAMID_SensorType_9 29U //NVRAM area id for the type SensorType_t
#define FFAP_NVRAMID_posext_TCalRow_9 30U //NVRAM area id for the type posext_TCalRow_t
#define FFAP_NVRAMID_posint_TCalRow_9 31U //NVRAM area id for the type posint_TCalRow_t
#define FFAP_NVRAMID_presatm_TCalRow_9 32U //NVRAM area id for the type presatm_TCalRow_t
#define FFAP_NVRAMID_pres3_TCalRow_9 33U //NVRAM area id for the type pres3_TCalRow_t
#define FFAP_NVRAMID_pres2_TCalRow_9 34U //NVRAM area id for the type pres2_TCalRow_t
#define FFAP_NVRAMID_prespilot_TCalRow_9 35U //NVRAM area id for the type prespilot_TCalRow_t
#define FFAP_NVRAMID_ipcurr_TCalRow_9 36U //NVRAM area id for the type ipcurr_TCalRow_t
#define FFAP_NVRAMID_pwmcomp_TCalRow_9 37U //NVRAM area id for the type pwmcomp_TCalRow_t
#define FFAP_NVRAMID_TemperatureCalibrationPoints_9 38U //NVRAM area id for the type TemperatureCalibrationPoints_t
#define FFAP_NVRAMID_HartData_9 39U //NVRAM area id for the type HartData_t
#define FFAP_NVRAMID_PosCharactSel_9 40U //NVRAM area id for the type PosCharactSel_t
#define FFAP_NVRAMID_PosCharact_9 41U //NVRAM area id for the type PosCharact_t
#define FFAP_NVRAMID_FaultCodeData_9 42U //NVRAM area id for the type FaultCodeData_t
#define FFAP_NVRAMID_FaultCodeMasks_9 43U //NVRAM area id for the type FaultCodeMasks_t
#define FFAP_NVRAMID_LowPowerData_9 44U //NVRAM area id for the type LowPowerData_t
#define FFAP_NVRAMID_UIData_9 45U //NVRAM area id for the type UIData_t
#define FFAP_NVRAMID_PneumaticParams_9 46U //NVRAM area id for the type PneumaticParams_t
#define FFAP_NVRAMID_ActivateVerifyData_9 47U //NVRAM area id for the type ActivateVerifyData_t
#define FFAP_NVRAMID_CtlSetSlot_9 48U //NVRAM area id for the type CtlSetSlot_t
#define FFAP_NVRAMID_UnitsOptions_9 49U //NVRAM area id for the type UnitsOptions_t
#define FFAP_NVRAMID_UnitsConfig_9 50U //NVRAM area id for the type UnitsConfig_t
#define FFAP_NVRAMID_InterfaceAccess_9 51U //NVRAM area id for the type InterfaceAccess_t
#define FFAP_NVRAMID_RefVoltage_9 52U //NVRAM area id for the type RefVoltage_t
#define FFAP_NVRAMID_FFData_9 53U //NVRAM area id for the type FFData_t
#define FFAP_NVRAM_ENTRIES_VER_9 (54U)
extern const struct nvramDumpMap_t FFAP_nvram_map_9[FFAP_NVRAM_ENTRIES_VER_9];
extern const struct nvramDumpMap_t FFAP_LogFileBuf_9;
#endif //FFAP_VERDUMP_9_H_
