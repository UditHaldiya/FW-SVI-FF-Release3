#ifndef FF_DEVICEVARS_H_
#define FF_DEVICEVARS_H_

#include "FFIPC_config.h"
#include "ipcdefs.h"
#include "ffdefs.h"
#include "ipcvarids.h"

#if FFIPC_SELECTION_WPJUMPER_EMU == FFIPC_OPTIONS_WPJUMPER_EMU_OPTION_SUPPORTED
#include "timer.h"
extern tick_t wpjemu_Expire(void);
#endif

#define FF_DEVICE_TAG_DEF   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
#define FF_DEVICE_ID_DEF    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define SIMULATION_ACTIVE   1
#define SIMULATION_DEACTIVE 0

#define IPC_TIMESTAMPVALID      1
#define IPC_TIMESTAMPINVALID    0
#define IPC_TIMESTAMPMASK       0x01

typedef struct IPC_FFDeviceParam_t
{
    u8              dev_tag[FF_DEVICE_TAG_LEN];
    u8              dev_id[FF_DEVICE_ID_LEN];
    u8              dev_addr;
    u8              IPC_TimeStampStatus;
    u16 CheckWord;
} IPC_FFDeviceParams_t;

extern IPC_FFDeviceParams_t* GetDeviceVar(void);
//extern IPC_FFDeviceParams_t* SetDeviceVar(const IPC_FFDeviceParams_t* p);

extern ErrorCode_t  IPC_WriteDeviceAddress(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteDeviceTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteDeviceID(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_ReadAppFwVer(IPC_Variable_IDs_t VarID, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_ReadLuiSimulation(IPC_Variable_IDs_t VarID, IPC_ReadPtrs_t const *pIPC_ReadPtrs);

#if FFIPC_SELECTION_WPJUMPER_EMU == FFIPC_OPTIONS_WPJUMPER_EMU_OPTION_SUPPORTED
typedef enum LockEmu_t
{
    LockEmu_Disabled,
    LockEmu_Off,
    LockEmu_On
} LockEmu_t;
#endif

typedef struct FFData_t
{
    bool_t SimulationActive; //!< "Simulation enabled" emulated jumper state
#if FFIPC_SELECTION_WPJUMPER_EMU == FFIPC_OPTIONS_WPJUMPER_EMU_OPTION_SUPPORTED
    LockEmu_t LockEmu;
#endif
    u16 CheckWord;
} FFData_t;

//Application get/set interface
SAFEGET(ff_GetLocalFFData, FFData_t);
SAFESET(ff_RepairSetFFData, FFData_t);

#endif //FF_DEVICEVARS_H_

