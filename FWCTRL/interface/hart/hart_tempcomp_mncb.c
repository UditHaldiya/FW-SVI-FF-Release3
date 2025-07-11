/*
Copyright 2008 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file hart_tempcomp_mncb.c
    \brief HART App-level interface to MNCB platform-specific factory operations

    CPU: Any

    OWNER: AK

    \ingroup HARTapp
*/
#include "mnwrap.h"
#include "projectdef.h"
#include "hartfunc.h"
#include "hartdef.h"
#include "tempcomp.h"
#include "hart_fac.h"

//Channels
#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
#   include "insignal.h"
#endif
#if FEATURE_PVINPUT_SENSOR == FEATURE_PVINPUT_SENSOR_AVAILABLE
#   include "inpv.h"
#endif

#include "tempr.h"
#include "tempr_mncb.h"
#include "posint.h"

#if FEATURE_REMOTE_POSITION_SENSOR == FEATURE_REMOTE_POSITION_SENSOR_AVAILABLE
#   include "posext.h"
#endif

#if FEATURE_AO == FEATURE_AO_SUPPORTED
#include "ao.h"
#endif

#include "ipcurr.h"

#if (FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED)
#include "prestab.h"
#endif

#include "pwmcomp.h"
#include "adtbl.h"

//----- Macro-ized implementation of HART tempcomp read/write by channel -----------

/* Note: AD_DIAG (Was 11) - analog reference voltage - is no longer tempcomp'ed */

#if FEATURE_LOOPSIGNAL_SENSOR == FEATURE_LOOPSIGNAL_SENSOR_SUPPORTED
READ_TEMPCOMP_16(ReadSPSignalTCRow, sig)
WRITE_TEMPCOMP_16(WriteSPSignalTCRow, sig)
#endif

READ_TEMPCOMP_16(ReadTemprTCRow, tempr) //yes board temperature itself is temperature-compensated
WRITE_TEMPCOMP_16(WriteTemprTCRow, tempr) //yes board temperature itself is temperature-compensated

#if (FEATURE_PRESSURE_INPUTS == FEATURE_PRESSURE_INPUTS_INCLUDED)
#if FEATURE_PRESSURE_SENSOR_PILOT == FEATURE_PRESSURE_SENSOR_PILOT_SUPPORTED
READ_TEMPCOMP_16(ReadPresPilotTCRow, prespilot)
WRITE_TEMPCOMP_16(WritePresPilotTCRow, prespilot)
#endif
#if FEATURE_PRESSURE_SENSOR_ATM == FEATURE_PRESSURE_SENSOR_ATM_SUPPORTED
READ_TEMPCOMP_16(ReadPresAtmTCRow, presatm)
WRITE_TEMPCOMP_16(WritePresAtmTCRow, presatm)
#endif
#if FEATURE_PRESSURE_SENSOR_1 == FEATURE_PRESSURE_SENSOR_1_SUPPORTED
READ_TEMPCOMP_16(ReadPres1TCRow, pres1)
WRITE_TEMPCOMP_16(WritePres1TCRow, pres1)
#endif
#if FEATURE_PRESSURE_SENSOR_2 == FEATURE_PRESSURE_SENSOR_2_SUPPORTED
READ_TEMPCOMP_16(ReadPres2TCRow, pres2)
WRITE_TEMPCOMP_16(WritePres2TCRow, pres2)
#endif
#if FEATURE_PRESSURE_SENSOR_3 == FEATURE_PRESSURE_SENSOR_3_SUPPORTED
READ_TEMPCOMP_16(ReadPres3TCRow, pres3)
WRITE_TEMPCOMP_16(WritePres3TCRow, pres3)
#endif
#endif //FEATURE_PRESSURE_INPUTS

READ_TEMPCOMP_32(ReadPosIntTCRow, posint)
WRITE_TEMPCOMP_32(WritePosIntTCRow, posint)

#if FEATURE_REMOTE_POSITION_SENSOR == FEATURE_REMOTE_POSITION_SENSOR_AVAILABLE
READ_TEMPCOMP_16(ReadPosExtTCRow, posext)
WRITE_TEMPCOMP_16(WritePosExtTCRow, posext)
#endif

READ_TEMPCOMP_16(ReadIPCurrentTCRow, ipcurr)
WRITE_TEMPCOMP_16(WriteIPCurrentTCRow, ipcurr)

READ_TEMPCOMP_16(ReadControlOutputTCRow, pwmcomp)
WRITE_TEMPCOMP_16(WriteControlOutputTCRow, pwmcomp)

//Macro-ized implementations of HART tempcomp read/write commands (common to all projects)

#if FEATURE_PVINPUT_SENSOR == FEATURE_PVINPUT_SENSOR_AVAILABLE
WRITE_TEMPCOMP_16(WritePVTCRow, inpv)
READ_TEMPCOMP_16(ReadPVTCRow, inpv)
#endif

#if FEATURE_AO == FEATURE_AO_SUPPORTED
WRITE_TEMPCOMP_16(WriteAO0RetransmitTCRow, ao0) //secondary (retransmit) AO
READ_TEMPCOMP_16(ReadAO0RetransmitTCRow, ao0) //secondary (retransmit) AO
#endif //FEATURE_AO

/** \brief Substitutes normal A/D sampling table with the table of all channels.
Used only for I/O calibration
*/
s8_least hartcmd_EnableAllADChannels(const u8 *src, u8 *dst)
{
    UNUSED_OK(src);
    UNUSED_OK(dst);
    adtbl_SetActiveSequence(AD_SEQ_CALIB);
    return HART_NO_COMMAND_SPECIFIC_ERRORS;
}

/* This line marks the end of the source */
