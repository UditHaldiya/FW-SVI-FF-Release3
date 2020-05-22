#ifndef DIAGNOSTIC_CONFIGURATION_H_
#define DIAGNOSTIC_CONFIGURATION_H_

#include <ptb.h>
#include "mnhart2ff.h"

extern fferr_t ffdc_WriteDiagnostic_Configuration
(
    const T_FBIF_BLOCK_INSTANCE* p_block_instance,
    const T_FBIF_WRITE_DATA* p_write
);

extern fferr_t ffdc_ReadPstConfig(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to);
extern fferr_t ffdc_ReadPstTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to);
//persistent
extern fferr_t ffdc_ReadDataCollectionConfigP(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to);
//transient
extern fferr_t ffdc_ReadDataCollectionConfigT(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to);
extern fferr_t ffdc_ReadDataCollectionTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                            void* from,
                            void* to);

extern fferr_t ffdc_WritePstConfig(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to);
extern fferr_t ffdc_WritePstTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to);
//persistent
extern fferr_t ffdc_WriteDataCollectionConfigP(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to);
//transient
extern fferr_t ffdc_WriteDataCollectionConfigT(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to);
extern fferr_t ffdc_WriteDataCollectionTrigger(const T_FBIF_BLOCK_INSTANCE* p_block_instance,
                             const T_FBIF_WRITE_DATA *p_write,
                             void* from,
                             void* to);

#endif // DIAGNOSTIC_CONFIGURATION_H_
