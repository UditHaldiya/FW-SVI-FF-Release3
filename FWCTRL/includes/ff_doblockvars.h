#ifndef FF_DOBLOCKVARS_H_
#define FF_DOBLOCKVARS_H_

#include "ipcdefs.h"
#include "ffdefs.h"

#define FF_DO_TAG_WR_MAX_BLOCK_NUM              FF_TAG_WR_MAX_BLOCK_NUM

// FF DO variables. May be move to standalone file if necessary
typedef struct IPC_FFDOParam_t
{
    u8                  tag[FF_TAG_MAX_LEN];
    u8                  ModeActual;
    u16                 BlockErr;
    ffDataDiscrete_t         	sp_d;
    u16 CheckWord;
} IPC_FFDOParams_t;

extern const IPC_FFDOParams_t *GetDoBlockVar(size_t index, IPC_FFDOParams_t *dst);
extern ErrorCode_t  IPC_WriteDOTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteDOMode(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteDOError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteDOSPD(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);

#endif //FF_DOBLOCKVARS_H_

