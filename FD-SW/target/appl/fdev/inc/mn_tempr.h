/*
Copyright 2020 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mn_tempr.h
    \brief API of temperature (extremes) interface

    CPU: Any

    OWNER: AK
*/
#ifndef MN_TEMPR_H_
#define MN_TEMPR_H_
extern fferr_t fftempr_ReadTemprExtremes(T_FBIF_BLOCK_INSTANCE *p_block_instance, T_FBIF_READ_DATA *p_read, void *from, void *to);
extern fferr_t fftempr_WriteTemprExtremes
(
    T_FBIF_BLOCK_INSTANCE *p_block_instance,
    const T_FBIF_WRITE_DATA *p_write,
    void *from,
    void *to
);


#endif //MN_TEMPR_H_
/* This line marks the end of the source */
