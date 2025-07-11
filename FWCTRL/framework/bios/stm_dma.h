/*
Copyright 2014 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**

    \file stm_dma.h

    \brief DMA cell driver API

    OWNER:
    CPU: STM32F10xx Cortex

*/
#ifndef STM_DMA_H_
#define STM_DMA_H_
// DMA API
//lint ++flb
typedef enum {DMA_Chan_1, DMA_Chan_2, DMA_Chan_3, DMA_Chan_4, DMA_Chan_5, DMA_Chan_6, DMA_Chan_7,   // channels in DMA1
              DMA_Chan_8, DMA_Chan_9, DMA_Chan_10, DMA_Chan_11, DMA_Chan_12} DMA_Chan;              // channels in DMA2
//lint --flb
extern void DMA_ConfigUART(const volatile void *pBuffer, u32 BufferSize, u32 devadr, DMA_Chan chn);
extern void DMA_SetUART(DMA_Chan chntx, DMA_Chan chnrx);
extern u32 DMA_getcount(DMA_Chan chan);

#endif //STM_DMA_H_
/* This line marks the end of the source */
