/*
Copyright 2013-2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mnipcff.h
    \brief Ext. interfaces of IPC layer

    CPU: Any

    OWNER: AK
*/
#ifndef MNIPCFF_H_
#define MNIPCFF_H_
extern void mnipc_ReadVars(T_FBIF_BLOCK_INSTANCE *p_block_instance, const u8 *receive_buff);
extern void mnipc_WriteDOswitches(const T_FBIF_BLOCK_INSTANCE *p_block_instance, u8 *send_buff);
extern void mnipc_WriteVars(T_FBIF_BLOCK_INSTANCE *p_block_instance, u8 *send_buff, u8 *send_length);

extern void mnipc_DhogRequest(void);
#endif //MNIPCFF_H_

/* This line marks the end of the source */
