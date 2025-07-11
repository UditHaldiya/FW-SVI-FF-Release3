#ifndef FF_RESBLOCKVARS_H_
#define FF_RESBLOCKVARS_H_

#include "ipcdefs.h"
#include "ffdefs.h"
#include "ipcvarids.h"

#define FF_RB_TAG_WR_MAX_BLOCK_NUM              FF_TAG_WR_MAX_BLOCK_NUM

// FF RB variables. May be move to standalone file if necessary
typedef struct IPC_FFResourceParam_t
{
    u8          tag[FF_TAG_MAX_LEN];
    u8          ModeActual;
    u16         BlockErr;
    u16 CheckWord;
} IPC_FFResourceParams_t;

// for lint comment these 2 lines
//extern const void *GetResBlockTag(void *dst);
//extern ErrorCode_t SetResBlockTag(const void *src);

extern ErrorCode_t  IPC_WriteRbTag(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
//extern ErrorCode_t  IPC_ReadRbTag(IPC_Variable_IDs_t VarID, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
//extern ErrorCode_t  IPC_ReadRbModeActual(IPC_Variable_IDs_t VarID, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteRbModeActual(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);
extern ErrorCode_t  IPC_WriteRbError(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);

extern const IPC_FFResourceParams_t* GetResBlockVar(IPC_FFResourceParams_t *dst);

#endif //FF_RESBLOCKVARS_H_
/* This line marks the end of the source */
