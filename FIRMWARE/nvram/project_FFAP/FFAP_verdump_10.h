/* Public definitions for NVRAM layout version 10
*/
#ifndef FFAP_VERDUMP_10_H_
#define FFAP_VERDUMP_10_H_
#define FFAP_NVRAMID_StartupVersionNumber_10 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFAP_NVRAMID_ModeData_10 1U //NVRAM area id for the type ModeData_t
#define FFAP_NVRAMID_DigitalSpConf_10 2U //NVRAM area id for the type DigitalSpConf_t
#define FFAP_NVRAMID_digitalsp_10 3U //NVRAM area id for the type digitalsp_t
#define FFAP_NVRAMID_BoardTemperature_10 4U //NVRAM area id for the type BoardTemperature_t
#define FFAP_NVRAMID_PressureCalData_10 5U //NVRAM area id for the type PressureCalData_t
#define FFAP_NVRAMID_PositionConf_10 6U //NVRAM area id for the type PositionConf_t
#define FFAP_NVRAMID_PIDData_10 7U //NVRAM area id for the type PIDData_t
#define FFAP_NVRAMID_ErrorLimits_10 15U //NVRAM area id for the type ErrorLimits_t
#define FFAP_NVRAMID_CtlLimits_10 16U //NVRAM area id for the type CtlLimits_t
#define FFAP_NVRAMID_logdata_10 17U //NVRAM area id for the type logdata_t
#define FFAP_NVRAMID_ContinuousDiagnostics_10 18U //NVRAM area id for the type ContinuousDiagnostics_t
#define FFAP_NVRAMID_SwitchConfiguration_10 19U //NVRAM area id for the type SwitchConfiguration_t
#define FFAP_NVRAMID_OptionConfig_10 20U //NVRAM area id for the type OptionConfig_t
#define FFAP_NVRAMID_BiasData_10 21U //NVRAM area id for the type BiasData_t
#define FFAP_NVRAMID_BiasExt_10 22U //NVRAM area id for the type BiasExt_t
#define FFAP_NVRAMID_TuneData_10 23U //NVRAM area id for the type TuneData_t
#define FFAP_NVRAMID_ConfigurationChanged_10 24U //NVRAM area id for the type ConfigurationChanged_t
#define FFAP_NVRAMID_inpv_TCalRow_10 25U //NVRAM area id for the type inpv_TCalRow_t
#define FFAP_NVRAMID_pres1_TCalRow_10 26U //NVRAM area id for the type pres1_TCalRow_t
#define FFAP_NVRAMID_TemperatureConf_10 27U //NVRAM area id for the type TemperatureConf_t
#define FFAP_NVRAMID_tempr_TCalRow_10 28U //NVRAM area id for the type tempr_TCalRow_t
#define FFAP_NVRAMID_SensorType_10 29U //NVRAM area id for the type SensorType_t
#define FFAP_NVRAMID_posext_TCalRow_10 30U //NVRAM area id for the type posext_TCalRow_t
#define FFAP_NVRAMID_posint_TCalRow_10 31U //NVRAM area id for the type posint_TCalRow_t
#define FFAP_NVRAMID_presatm_TCalRow_10 32U //NVRAM area id for the type presatm_TCalRow_t
#define FFAP_NVRAMID_pres3_TCalRow_10 33U //NVRAM area id for the type pres3_TCalRow_t
#define FFAP_NVRAMID_pres2_TCalRow_10 34U //NVRAM area id for the type pres2_TCalRow_t
#define FFAP_NVRAMID_prespilot_TCalRow_10 35U //NVRAM area id for the type prespilot_TCalRow_t
#define FFAP_NVRAMID_ipcurr_TCalRow_10 36U //NVRAM area id for the type ipcurr_TCalRow_t
#define FFAP_NVRAMID_pwmcomp_TCalRow_10 37U //NVRAM area id for the type pwmcomp_TCalRow_t
#define FFAP_NVRAMID_TemperatureCalibrationPoints_10 38U //NVRAM area id for the type TemperatureCalibrationPoints_t
#define FFAP_NVRAMID_HartData_10 39U //NVRAM area id for the type HartData_t
#define FFAP_NVRAMID_PosCharactSel_10 40U //NVRAM area id for the type PosCharactSel_t
#define FFAP_NVRAMID_PosCharact_10 41U //NVRAM area id for the type PosCharact_t
#define FFAP_NVRAMID_FaultCodeData_10 42U //NVRAM area id for the type FaultCodeData_t
#define FFAP_NVRAMID_FaultCodeMasks_10 43U //NVRAM area id for the type FaultCodeMasks_t
#define FFAP_NVRAMID_LowPowerData_10 44U //NVRAM area id for the type LowPowerData_t
#define FFAP_NVRAMID_UIData_10 45U //NVRAM area id for the type UIData_t
#define FFAP_NVRAMID_PneumaticParams_10 46U //NVRAM area id for the type PneumaticParams_t
#define FFAP_NVRAMID_ActivateVerifyData_10 47U //NVRAM area id for the type ActivateVerifyData_t
#define FFAP_NVRAMID_CtlSetSlot_10 48U //NVRAM area id for the type CtlSetSlot_t
#define FFAP_NVRAMID_UnitsOptions_10 49U //NVRAM area id for the type UnitsOptions_t
#define FFAP_NVRAMID_UnitsConfig_10 50U //NVRAM area id for the type UnitsConfig_t
#define FFAP_NVRAMID_InterfaceAccess_10 51U //NVRAM area id for the type InterfaceAccess_t
#define FFAP_NVRAMID_RefVoltage_10 52U //NVRAM area id for the type RefVoltage_t
#define FFAP_NVRAMID_FFData_10 53U //NVRAM area id for the type FFData_t
#define FFAP_NVRAMID_PSTSchedTime_10 54U //NVRAM area id for the type PSTSchedTime_t
#define FFAP_NVRAMID_PSTConf_10 55U //NVRAM area id for the type PSTConf_t
#define FFAP_NVRAMID_PSTrigger_10 56U //NVRAM area id for the type PSTrigger_t
#define FFAP_NVRAMID_DatahogConf_10 57U //NVRAM area id for the type DatahogConf_t
#define FFAP_NVRAMID_DhogTriggerConf_10 58U //NVRAM area id for the type DhogTriggerConf_t
#define FFAP_NVRAMID_FactoryDefaultState_10 59U //NVRAM area id for the type FactoryDefaultState_t
#define FFAP_NVRAM_ENTRIES_VER_10 (60U)
extern const struct
   nvramDumpMap_t
       FFAP_nvram_map_10[FFAP_NVRAM_ENTRIES_VER_10];
extern const struct nvramDumpMap_t FFAP_LogFileBuf_10;
#endif //FFAP_VERDUMP_10_H_
