#ifndef MNFAULT2ALERT_H_
#define MNFAULT2ALERT_H_

#include <fbap.h> //for block errors
#include <ptb.h> //T_FBIF_PTB
#include <spec_ds.h> //_ALERT_ACTION
#include <fbif_dcl.h> //ptb_1

#include "faultpublic.h"

#include "mnerrorif.h"

typedef struct MnFaultAlarmMap_t
{
    u16 BlockError;
    u32 block_err_desc_1;
    xdX_t xd_index;
    u8 xd_error;
    u8 BlockAlertX; //alert index
    u8 recommended_action;
    u8 priority; //!< higher number means higher priority
} MnFaultAlarmMap_t;



#define ALERT_NONE 0U //no block alert for a fault
#define ALERT_INDEX(alert_name) (MN_OFFSETOF(_ALERT_STATE, CAT(alert_name, _st)))


typedef struct
{
    u16 old_block_alarm_bits;
    u16 rect_period;
} T_APPL_TB_DATA;

extern const MnFaultAlarmMap_t MnFaultAlarmMap[MAX_FAULT_NUMBER];

extern u16 mnfaults_Import(const T_FBIF_PTB *p_PTB, MnAlertsEtc_t *AlertsEtc);
extern void mnptb_ProcErrors(const T_FBIF_BLOCK_INSTANCE *p_block_instance);


//Softing goodies, originally from appl_dia.c
  #define FD_NO_RECOMM_ACT          1
  #define FD_SIMULATE_RECOMM_ACT    2
  #define FD_RECOMM_ACT_TB          3
  #define FD_NO_HART_COMMUNICATION  4
  #define FD_RECOMM_ACT_UNKNOWN     68


#endif //MNFAULT2ALERT_H_
