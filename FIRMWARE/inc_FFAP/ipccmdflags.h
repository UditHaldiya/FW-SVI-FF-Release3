/*
Copyright 2022 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ipccmdflags.h
    \brief IPC command flags

    CPU: Any (with standard C compiler)

    OWNER: AK
    \addtogroup IPC
*/
#ifndef IPCCMDFLAGS_H_
#define IPCCMDFLAGS_H_

//--------------------------------------------------------------
// Command bits in the 16-bit IPC buffer, all must be different

//Discrete switches
#define DO_2_IPC_STATE                  (0x8000u)
#define DO_1_IPC_STATE                  (0x4000u)

//Write lock
#define OPTIONVAL_WRITE_LOCK (0x0001U) //! From FFP to APP

//Data collection trigger by TB alert
#define DHOG_TB_ALERT_TRIGGER (0x0002U) //! IPC Trigger on conditions detected in FFP

//Setpoint tracking acknowledgment
#define ACK_SP_TRACKING (0x0004U)
//--------------------------------------------------------------


#endif //IPCCMDFLAGS_H_
/* This line marks the end of the source */
