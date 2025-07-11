/* Public definitions for NVRAM layout version 8
*/
#ifndef FFAP_VERDUMP_8_H_
#define FFAP_VERDUMP_8_H_
#define FFAP_NVRAMID_StartupVersionNumber_8 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFAP_NVRAMID_ModeData_8 1U //NVRAM area id for the type ModeData_t
#define FFAP_NVRAMID_DigitalSpConf_8 2U //NVRAM area id for the type DigitalSpConf_t
#define FFAP_NVRAMID_digitalsp_8 3U //NVRAM area id for the type digitalsp_t
#define FFAP_NVRAMID_BoardTemperature_8 4U //NVRAM area id for the type BoardTemperature_t
#define FFAP_NVRAMID_PressureCalData_8 5U //NVRAM area id for the type PressureCalData_t
#define FFAP_NVRAMID_PositionConf_8 6U //NVRAM area id for the type PositionConf_t
#define FFAP_NVRAMID_PIDData_8 7U //NVRAM area id for the type PIDData_t
#define FFAP_NVRAMID_ErrorLimits_8 15U //NVRAM area id for the type ErrorLimits_t
#define FFAP_NVRAMID_CtlLimits_8 16U //NVRAM area id for the type CtlLimits_t
#define FFAP_NVRAMID_logdata_8 17U //NVRAM area id for the type logdata_t
#define FFAP_NVRAMID_ContinuousDiagnostics_8 18U //NVRAM area id for the type ContinuousDiagnostics_t
#define FFAP_NVRAMID_SwitchConfiguration_8 19U //NVRAM area id for the type SwitchConfiguration_t
#define FFAP_NVRAMID_OptionConfig_8 20U //NVRAM area id for the type OptionConfig_t
#define FFAP_NVRAMID_BiasData_8 21U //NVRAM area id for the type BiasData_t
#define FFAP_NVRAMID_BiasExt_8 22U //NVRAM area id for the type BiasExt_t
#define FFAP_NVRAMID_TuneData_8 23U //NVRAM area id for the type TuneData_t
#define FFAP_NVRAMID_ConfigurationChanged_8 24U //NVRAM area id for the type ConfigurationChanged_t
#define FFAP_NVRAMID_inpv_TCalRow_8 25U //NVRAM area id for the type inpv_TCalRow_t
#define FFAP_NVRAMID_pres1_TCalRow_8 26U //NVRAM area id for the type pres1_TCalRow_t
#define FFAP_NVRAMID_TemperatureConf_8 27U //NVRAM area id for the type TemperatureConf_t
#define FFAP_NVRAMID_tempr_TCalRow_8 28U //NVRAM area id for the type tempr_TCalRow_t
#define FFAP_NVRAMID_SensorType_8 29U //NVRAM area id for the type SensorType_t
#define FFAP_NVRAMID_posext_TCalRow_8 30U //NVRAM area id for the type posext_TCalRow_t
#define FFAP_NVRAMID_posint_TCalRow_8 31U //NVRAM area id for the type posint_TCalRow_t
#define FFAP_NVRAMID_presatm_TCalRow_8 32U //NVRAM area id for the type presatm_TCalRow_t
#define FFAP_NVRAMID_pres3_TCalRow_8 33U //NVRAM area id for the type pres3_TCalRow_t
#define FFAP_NVRAMID_pres2_TCalRow_8 34U //NVRAM area id for the type pres2_TCalRow_t
#define FFAP_NVRAMID_prespilot_TCalRow_8 35U //NVRAM area id for the type prespilot_TCalRow_t
#define FFAP_NVRAMID_ipcurr_TCalRow_8 36U //NVRAM area id for the type ipcurr_TCalRow_t
#define FFAP_NVRAMID_pwmcomp_TCalRow_8 37U //NVRAM area id for the type pwmcomp_TCalRow_t
#define FFAP_NVRAMID_TemperatureCalibrationPoints_8 38U //NVRAM area id for the type TemperatureCalibrationPoints_t
#define FFAP_NVRAMID_HartData_8 39U //NVRAM area id for the type HartData_t
#define FFAP_NVRAMID_PosCharactSel_8 40U //NVRAM area id for the type PosCharactSel_t
#define FFAP_NVRAMID_PosCharact_8 41U //NVRAM area id for the type PosCharact_t
#define FFAP_NVRAMID_FaultCodeData_8 42U //NVRAM area id for the type FaultCodeData_t
#define FFAP_NVRAMID_FaultCodeMasks_8 43U //NVRAM area id for the type FaultCodeMasks_t
#define FFAP_NVRAMID_LowPowerData_8 44U //NVRAM area id for the type LowPowerData_t
#define FFAP_NVRAMID_UIData_8 45U //NVRAM area id for the type UIData_t
#define FFAP_NVRAMID_PneumaticParams_8 46U //NVRAM area id for the type PneumaticParams_t
#define FFAP_NVRAMID_ActivateVerifyData_8 47U //NVRAM area id for the type ActivateVerifyData_t
#define FFAP_NVRAMID_CtlSetSlot_8 48U //NVRAM area id for the type CtlSetSlot_t
#define FFAP_NVRAMID_UnitsOptions_8 49U //NVRAM area id for the type UnitsOptions_t
#define FFAP_NVRAMID_UnitsConfig_8 50U //NVRAM area id for the type UnitsConfig_t
#define FFAP_NVRAMID_InterfaceAccess_8 51U //NVRAM area id for the type InterfaceAccess_t
#define FFAP_NVRAMID_RefVoltage_8 52U //NVRAM area id for the type RefVoltage_t
#define FFAP_NVRAMID_FFData_8 53U //NVRAM area id for the type FFData_t
#define FFAP_NVRAM_ENTRIES_VER_8 (54U)
extern const struct nvramDumpMap_t FFAP_nvram_map_8[FFAP_NVRAM_ENTRIES_VER_8];
extern const struct nvramDumpMap_t FFAP_LogFileBuf_8;
#endif //FFAP_VERDUMP_8_H_
