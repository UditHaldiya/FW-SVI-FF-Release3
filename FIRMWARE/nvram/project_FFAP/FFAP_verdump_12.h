/* Public definitions for NVRAM layout version 12
*/
#ifndef FFAP_VERDUMP_12_H_
#define FFAP_VERDUMP_12_H_
#define FFAP_NVRAMID_StartupVersionNumber_12 0U //NVRAM area id for the type StartupVersionNumber_t
#define FFAP_NVRAMID_ModeData_12 1U //NVRAM area id for the type ModeData_t
#define FFAP_NVRAMID_DigitalSpConf_12 2U //NVRAM area id for the type DigitalSpConf_t
#define FFAP_NVRAMID_digitalsp_12 3U //NVRAM area id for the type digitalsp_t
#define FFAP_NVRAMID_BoardTemperature_12 4U //NVRAM area id for the type BoardTemperature_t
#define FFAP_NVRAMID_PressureCalData_12 5U //NVRAM area id for the type PressureCalData_t
#define FFAP_NVRAMID_PositionConf_12 6U //NVRAM area id for the type PositionConf_t
#define FFAP_NVRAMID_PIDData_12 7U //NVRAM area id for the type PIDData_t
#define FFAP_NVRAMID_ErrorLimits_12 15U //NVRAM area id for the type ErrorLimits_t
#define FFAP_NVRAMID_CtlLimits_12 16U //NVRAM area id for the type CtlLimits_t
#define FFAP_NVRAMID_logdata_12 17U //NVRAM area id for the type logdata_t
#define FFAP_NVRAMID_ContinuousDiagnostics_12 18U //NVRAM area id for the type ContinuousDiagnostics_t
#define FFAP_NVRAMID_SwitchConfiguration_12 19U //NVRAM area id for the type SwitchConfiguration_t
#define FFAP_NVRAMID_OptionConfig_12 20U //NVRAM area id for the type OptionConfig_t
#define FFAP_NVRAMID_BiasData_12 21U //NVRAM area id for the type BiasData_t
#define FFAP_NVRAMID_BiasExt_12 22U //NVRAM area id for the type BiasExt_t
#define FFAP_NVRAMID_TuneData_12 23U //NVRAM area id for the type TuneData_t
#define FFAP_NVRAMID_ConfigurationChanged_12 24U //NVRAM area id for the type ConfigurationChanged_t
#define FFAP_NVRAMID_inpv_TCalRow_12 25U //NVRAM area id for the type inpv_TCalRow_t
#define FFAP_NVRAMID_pres1_TCalRow_12 26U //NVRAM area id for the type pres1_TCalRow_t
#define FFAP_NVRAMID_TemperatureConf_12 27U //NVRAM area id for the type TemperatureConf_t
#define FFAP_NVRAMID_tempr_TCalRow_12 28U //NVRAM area id for the type tempr_TCalRow_t
#define FFAP_NVRAMID_SensorType_12 29U //NVRAM area id for the type SensorType_t
#define FFAP_NVRAMID_posext_TCalRow_12 30U //NVRAM area id for the type posext_TCalRow_t
#define FFAP_NVRAMID_posint_TCalRow_12 31U //NVRAM area id for the type posint_TCalRow_t
#define FFAP_NVRAMID_presatm_TCalRow_12 32U //NVRAM area id for the type presatm_TCalRow_t
#define FFAP_NVRAMID_pres3_TCalRow_12 33U //NVRAM area id for the type pres3_TCalRow_t
#define FFAP_NVRAMID_pres2_TCalRow_12 34U //NVRAM area id for the type pres2_TCalRow_t
#define FFAP_NVRAMID_prespilot_TCalRow_12 35U //NVRAM area id for the type prespilot_TCalRow_t
#define FFAP_NVRAMID_ipcurr_TCalRow_12 36U //NVRAM area id for the type ipcurr_TCalRow_t
#define FFAP_NVRAMID_pwmcomp_TCalRow_12 37U //NVRAM area id for the type pwmcomp_TCalRow_t
#define FFAP_NVRAMID_TemperatureCalibrationPoints_12 38U //NVRAM area id for the type TemperatureCalibrationPoints_t
#define FFAP_NVRAMID_HartData_12 39U //NVRAM area id for the type HartData_t
#define FFAP_NVRAMID_PosCharactSel_12 40U //NVRAM area id for the type PosCharactSel_t
#define FFAP_NVRAMID_PosCharact_12 41U //NVRAM area id for the type PosCharact_t
#define FFAP_NVRAMID_FaultCodeData_12 42U //NVRAM area id for the type FaultCodeData_t
#define FFAP_NVRAMID_LCDContrasts_12 43U //NVRAM area id for the type LCDContrasts_t
#define FFAP_NVRAMID_LowPowerData_12 44U //NVRAM area id for the type LowPowerData_t
#define FFAP_NVRAMID_UIData_12 45U //NVRAM area id for the type UIData_t
#define FFAP_NVRAMID_PneumaticParams_12 46U //NVRAM area id for the type PneumaticParams_t
#define FFAP_NVRAMID_ActivateVerifyData_12 47U //NVRAM area id for the type ActivateVerifyData_t
#define FFAP_NVRAMID_CtlSetSlot_12 48U //NVRAM area id for the type CtlSetSlot_t
#define FFAP_NVRAMID_UnitsOptions_12 49U //NVRAM area id for the type UnitsOptions_t
#define FFAP_NVRAMID_UnitsConfig_12 50U //NVRAM area id for the type UnitsConfig_t
#define FFAP_NVRAMID_InterfaceAccess_12 51U //NVRAM area id for the type InterfaceAccess_t
#define FFAP_NVRAMID_RefVoltage_12 52U //NVRAM area id for the type RefVoltage_t
#define FFAP_NVRAMID_FFData_12 53U //NVRAM area id for the type FFData_t
#define FFAP_NVRAMID_PSTSchedTime_12 54U //NVRAM area id for the type PSTSchedTime_t
#define FFAP_NVRAMID_PSTConf_12 55U //NVRAM area id for the type PSTConf_t
#define FFAP_NVRAMID_PSTrigger_12 56U //NVRAM area id for the type PSTrigger_t
#define FFAP_NVRAMID_DatahogConf_12 57U //NVRAM area id for the type DatahogConf_t
#define FFAP_NVRAMID_DhogTriggerConf_12 58U //NVRAM area id for the type DhogTriggerConf_t
#define FFAP_NVRAMID_FactoryDefaultState_12 59U //NVRAM area id for the type FactoryDefaultState_t
#define FFAP_NVRAM_ENTRIES_VER_12 (60U)
extern const struct
   nvramDumpMap_t
       FFAP_nvram_map_12[FFAP_NVRAM_ENTRIES_VER_12];
extern const struct nvramDumpMap_t FFAP_LogFileBuf_12;
#endif //FFAP_VERDUMP_12_H_
