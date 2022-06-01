#ifndef FF_ISBLOCKVARS_H_
#define FF_ISBLOCKVARS_H_

#include "ipcdefs.h"
#include "ffdefs.h"

// FF IS variables. May be move to standalone file if necessary
typedef struct IPC_FFISParam_t
{
    ffDataFloat_t     in1;
	ffDataFloat_t     in2;
	ffDataFloat_t     in3;
	ffDataFloat_t     in4;
    u16 CheckWord;
} IPC_FFISParams_t;

extern const IPC_FFISParams_t* GetIsBlockVar(IPC_FFISParams_t *dst);
extern ErrorCode_t  IPC_WriteISIN(IPC_Variable_IDs_t VarID, IPC_WritePtrs_t const *pIPC_WritePtrs, IPC_ReadPtrs_t const *pIPC_ReadPtrs);

#endif //FF_ISBLOCKVARS_H_
