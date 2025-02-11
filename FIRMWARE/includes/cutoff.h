/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file cutoff.h
    \brief Header for cutoff.c -- Full Open/Close controller

    CPU:

    \ingroup
*/

#ifndef CUTOFF_H_
#define CUTOFF_H_

extern bool_t cutoff_IsActive(void);
bool_t cutoff_Eval(bool_t closed_loop);

typedef struct CutoffConf_t
{
    faultcode_t fcode;
    u16 output[Xends];
} CutoffConf_t;

extern CutoffConf_t CutoffConf[];   

#endif // CUTOFF_H_

/* This line marks the end of the source */
