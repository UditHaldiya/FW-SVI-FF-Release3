#ifndef FF_PIDBLOCKVARS_H_
#define FF_PIDBLOCKVARS_H_

#include "ipcdefs.h"
#include "ffdefs.h"

#define FF_PID_TAG_WR_MAX_BLOCK_NUM              FF_TAG_WR_MAX_BLOCK_NUM

// FF PID variables. May be move to standalone file if necessary
typedef struct IPC_FFPIDParam_t
{
    u8              tag[FF_TAG_MAX_LEN];
    u8              ModeActual;
    u16             BlockErr;
    ffDataFloat_t     	pv;
    ffDataFloat_t     	sp;
    ffDataFloat_t     	out;
    u16             CheckWord;
} IPC_FFPIDParams_t;


extern const IPC_FFPIDParams_t* GetPidBlockVar(size_t index, IPC_FFPIDParams_t *dst);
extern ErrorCode_t  IPC_WritePIDTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WritePIDMode(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WritePIDError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WritePIDPV(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WritePIDSP(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WritePIDOUT(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);

#endif //FF_PIDBLOCKVARS_H_

