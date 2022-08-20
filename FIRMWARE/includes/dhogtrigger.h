#ifndef DHOGTRIGGER_H_
#define DHOGTRIGGER_H_
#include "errcodes.h"
#include "signaldef.h"
#include "pressuredef.h"
#include "position.h"
#include "datahog.h"

//lint -esym(641 756, DhogBinaryOptionsBits_t) enum on RHS of shift OK; Unused typedef OK
typedef enum DhogBinaryOptionsBits_t
{
    DhogBO_Extrn = 0, //!< Enable external trigger (via HART)
    DhogBO_TBAlerts = 1, //!< are we honoring DHOG_TB_ALERT_TRIGGER if comes by IPC?
#if 0 //maybe, future
    DhogBO_DO1Assert = 2,
    DhogBO_DO2Assert = 3,
#endif
    DhogBO_PosDeviation = 4,
    DhogBO_PresDeviation = 5,
    DhogBO_SpDeviation = 6,
    DhogBO_DiOpen = 7,
    DhogBO_DiClosed = 8,
    DhogBO_PvBelow = 9,
    DhogBO_PvAbove = 10,
    DhogBO_PvBetween = 11
} DhogBinaryOptionsBits_t;

enum
{
    trig_sp_deviation,
    trig_pos_deviation,
    trig_pres_deviation,
    trig_total
};

typedef struct DhogTriggerConf_t
{
    sig_t pvthreshold[Xends]; //!< AI (aka PV) threshold
    s16 DeviationThresh[trig_total];
    //pos_t spthreshold; //!< working SP deviation threshold
    //pos_t posthreshold; //!< working position deviation threshold
    //pres_t presthreshold; //!< main pressure deviation threshold
    u16 BinaryOptions; //
    FilterConf_t FilterConf; //common for all deviation triggers (for now)
    u16 CheckWord;
} DhogTriggerConf_t;

extern ErrorCode_t datahog_TriggerComm(DatahogConfId_t DatahogConfId, DatahogStatus_t cmd);

extern const sig_t pvthreshold_range[Xends];
extern const pos_t spthreshold_range[Xends];
extern const pos_t posthreshold_range[Xends];
extern const pres_t presthreshold_range[Xends];

extern const DhogTriggerConf_t *datahog_GetTriggerConf(DhogTriggerConf_t *dst);
extern ErrorCode_t datahog_SetTriggerConf(const DhogTriggerConf_t *src);
UNTYPEACC(datahog_SetTriggerConf, datahog_GetTriggerConf);

#endif //DHOGTRIGGER_H_
