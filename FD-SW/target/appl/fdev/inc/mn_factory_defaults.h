#ifndef FACTORY_DEFAULTS_H_
#define FACTORY_DEFAULTS_H_

#include <softing_base.h>
#include "ptbif.h"
#include "process.h"

extern fferr_t ffres_restart_APP(void);
extern fferr_t ffres_ReinitNvmem(void);
extern fferr_t ffres_restart_hidden(void);
extern fferr_t ffres_restart_factory_defaults(void);

#define LOGF_PTB_ST_NUM 1U //common for NV and ST
#define LOGF_PTB_ST_SIZE (sizeof(T_FBIF_PTB_STATIC))
#define LOGF_PTB_NV_SIZE (sizeof(T_FBIF_PTB_NV))

//-------- An addition for quickstart defaults ---------------
extern fferr_t ffres_QuickSet(void);

#endif //FACTORY_DEFAULTS_H_
