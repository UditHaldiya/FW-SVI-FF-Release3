/*
Copyright 2004-2015 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**

    \file key.h
    \brief header BIOS routines for support of the keyboard buttons
    keyboard/display reconnect is also supported

    CPU: Any (with standard C compiler)

    OWNER: AP

    \ingroup bios
*/

#ifndef KEY_H_
#define KEY_H_
#include "faultpublic.h"
/* bitcoding of pushbuttons */
#define PUSHBUTTON_STAR     ((u8)(1U << 0))	/* "*" Button */
#define PUSHBUTTON_MINUS    ((u8)(1U << 1))	/* "-" Button */
#define PUSHBUTTON_PLUS     ((u8)(1U << 2))	/* "+" Button */
#define PUSHBUTTON_CANCEL   ((u8)(0U))	    /* --- No Button -- CANCEL but def is required now */

#define PUSHBUTTON_DOWN_EDGE    ((u8)0U)    /* return down edges of pushbuttons */
#define PUSHBUTTON_RELEASE_EDGE ((u8)1U)  /* return down edges of pushbutton */

extern u8       bios_ReadPushButtonStatus(u8 *pUpdown);
extern bool_t   bios_ReadDiState(void);
extern void     bios_InitKeyboardDriver(void);
extern void   bios_HandleDigitalInput(void);
extern faultcode_fast_t bios_ProcessDigitalInput(void);
extern void     key_Mopup(void);

#endif // KEY_H_

/* End of the source */
