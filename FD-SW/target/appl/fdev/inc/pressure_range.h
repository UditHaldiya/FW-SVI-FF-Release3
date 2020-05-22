#ifndef PRESSURE_RANGE_H_
#define PRESSURE_RANGE_H_

#include <softing_base.h>
#include "mnhart2ff.h"

#define FF_UNITS_KPA                1133u
#define FF_UNITS_PSI                1141u
#define FF_UNITS_BAR                1137u
#define PSI_MAX                     (150.0F)
#define KPA_MAX                     ((float32)(PSI_MAX*PRESSURE_FACTOR_PSI2KPA))
#define BAR_MAX                     ((float32)(PSI_MAX*PRESSURE_FACTOR_PSI2BAR))
#define PRESSURE_RANGE_DECIMAL      (3)
#define PRESSURE_FACTOR_BAR2KPA     (100.0F)
#define PRESSURE_FACTOR_KPA2BAR     (0.01F)

extern fferr_t ReadPressureRange(const T_FBIF_BLOCK_INSTANCE* p_block_instance, void* snd_buf, void* rcv_buf);
extern fferr_t ffpres_WritePressureRange(const T_FBIF_BLOCK_INSTANCE* p_block_instance, const T_FBIF_WRITE_DATA* p_write, void* snd_buf, void* rcv_buf);

typedef struct PresAlertConf_t
{
    float32 alert_point; //!< always in PSI (as internal units)
    float32 deadband; //!< always in PSI (as internal units)
    BOOL historic_alert;
    BOOL enable;
    u16 CheckWord;
} PresAlertConf_t;

enum
{
    PresAlertHi,
    PresAlertLo,
    PresAlertLoLo,
    PresAlerts_Count
};

typedef enum ffpresIndex_t
{
    pres_supply,
    pres_act_a,
    pres_act_b,
    pres_pilot,
    pres_atm,
    pres_total_count
} ffpresIndex_t;
extern float32 ffpres_ReadPressureEngByIndex(ffpresIndex_t index);
extern float32 ffpres_ReadPressureInternalByIndex(ffpresIndex_t index);

extern const u8 pres_UnitsMap_size;
extern u8_least ffpres_FFCode2Index(u16 ff_code);
extern u8 ffpres_FFUnits2HartUnits(u16 ff_code);
extern u16 ffpres_HartUnits2FFUnits(u8 hart_code);

extern float32 ffpres_Internal2Eng(float32 val, u16 ff_code);
extern float32 ffpres_Eng2Internal(float32 val, u16 ff_code);
extern void ffpres_ReadExtremes(_PRESSURE_EXTREMES *dst);
extern void ffpres_WriteExtremes(const _PRESSURE_EXTREMES *src);

extern ErrorCode_t ffpres_SetAlertConf(u8_least index, const PresAlertConf_t *src);
extern const PresAlertConf_t *ffpres_GetAlertConf(u8_least index, PresAlertConf_t *dst);
UNTYPEACCX(ffpres_SetAlertConf, ffpres_GetAlertConf);

#endif // PRESSURE_RANGE_H_
