/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file errcodes.h
    \brief Error code definitions

    These error codes are NOT fault codes!!! (Fault codes are in faultdef.h)
    These are error codes returned by functions of all sorts which do not
    handle errors internally and need to propagate them up.

    CPU: Any

    OWNER: AK
    $Archive: /MNCB/Dev/FIRMWARE/includes/errcodes.h $
    $Date: 11/15/11 12:15p $
    $Revision: 32 $
    $Author: Arkkhasin $

    \ingroup Faultman
*/
/* (Optional) $History: errcodes.h $
 *
 * *****************  Version 32  *****************
 * User: Arkkhasin    Date: 11/15/11   Time: 12:15p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Added Digital Potentiometer errors FBO LCX
 *
 * *****************  Version 31  *****************
 * User: Arkkhasin    Date: 5/28/10    Time: 1:00a
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Partial taming of headers toward modularization. No code change
 *
 * *****************  Version 30  *****************
 * User: Arkkhasin    Date: 5/29/09    Time: 2:11a
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Error forming utilities and a few new error codes
 *
 * *****************  Version 29  *****************
 * User: Arkkhasin    Date: 4/03/09    Time: 2:59p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Added HART locks management component
 *
 * *****************  Version 28  *****************
 * User: Sergey Kruss Date: 3/12/09    Time: 2:56p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Added one SG error code
 *
 * *****************  Version 27  *****************
 * User: Anatoly Podpaly Date: 3/05/09    Time: 6:24p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * LINT: added undefined ERR_CAL_MOUNTING_MISMATCH.
 *
 * *****************  Version 26  *****************
 * User: Ernieprice   Date: 5/12/08    Time: 9:36a
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Updates for 12400 BIOS - added new errorcodes for I@C - bus stuck and
 * device missing
 *
 * *****************  Version 25  *****************
 * User: Arkkhasin    Date: 3/14/08    Time: 5:35p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * A first baby step toward uniform support of engineering units:
 * Removed no longer used ERR_CNFG_INVALID_PRESSURE_UNITS
 *
 * *****************  Version 24  *****************
 * User: Arkkhasin    Date: 1/23/08    Time: 6:46p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Added ERR_NOT_SUPPORTED
 *
 * *****************  Version 23  *****************
 * User: Arkkhasin    Date: 6/20/07    Time: 6:46p
 * Updated in $/MNCB/Dev/FIRMWARE/includes
 * Updated tombstone file headers. No code change
*/
#ifndef ERRCODES_H_
#define ERRCODES_H_

typedef enum ErrorCode_t ErrorCode_t;
enum ErrorCode_t
{
    ERR_OK,

    ERR_PASSWORD,

    ERR_INVALID_PARAMETER,
    ERR_LOWERLIM,
    ERR_UPPERLIM,

    ERR_NOT_SUPPORTED,

    ERR_MODE_CANNOT_CHANGE,
    ERR_MODE_ILLEGAL_SUBMODE,

    ERR_CNFG_SIGNAL_RANGE,
    ERR_CNFG_PRESSURE_RANGE,
    ERR_CNFG_STOPS_RANGE,
    ERR_CNFG_PROTECTED_LIMITS,

    ERR_CHARACT_INVALID_ARG,
    ERR_CHARACT_ERROR,
    ERR_CHARACT_CUSTOM_SIZE,  //invalid table size
    ERR_CHARACT_CUSTOM_ORDER, //values not monotonic

    ERR_HART_PARAM_TOO_BIG,
    ERR_HART_NO_DATA_AVAILABLE,
    ERR_HART_INVALID_DATA,

    ERR_CAL_INVALID_PROCEDURE_CALL,
    ERR_CAL_PROCESS_CANCELED,
    ERR_CAL_POSITION_OUT_OF_RANGE,
    ERR_CAL_NOT_AT_STOPS,
    ERR_CAL_DIFFERENCE,
    ERR_CAL_MOUNTING_MISMATCH,
    ERR_CAL_SG_OUT_OF_RANGE,
    ERR_CAL_VALUE, //!< actually read value is outside the range allowed for calibration

    ERR_DIAG_POSITION_RANGE,
    ERR_DIAG_LIMITS_ON,
    ERR_DIAG_LOW_COST_LIM,
    ERR_DIAG_NO_PRESSURE,
    ERR_DIAG_TYPE_NOT_AVAILABLE,
    ERR_DIAG_FAILED_TO_START,

    ERR_COMP_INVALID_TABLE,

    //bios level error codes, with MN naming convention
    ERR_NVMEM_RANGE,
    ERR_NVMEM_CRC,
    ERR_NVMEM_READ,
    ERR_NVMEM_WRITE,
    ERR_NVMEM_WRITE_DISABLED,
    ERR_BIOS_PARAM,
    ERR_NVMEM_SIGNATURE, /* no magic number in FRAM */
    ERR_I2C_BUS_STUCK,
    ERR_I2C_NO_DEVICE,

    ERR_PROCESS_START, //cannot start a process

    ERR_LOGF_INVALID, //wrong log file - a different log is open
    ERR_LOGF_PREVIOUS_ERROR, //an error existed when an operation was attempted
    ERR_LOGF_OPENMODE, //A read operation attempted on a log open for writes or vice versa
    ERR_LOGF_LENGTH, //log data read/write request is beyond the limits

    ERR_PST_CANCELED,       //pst failed or was canceled
    ERR_PST_FAILED_PRESSURE,
	ERR_PST_FAILED_TIME,
    ERR_PST_FAILED_SAVE,
    ERR_RESP_TEST_FAILED,

    ERR_HART_RV_LOW_TOO_HIGH ,
    ERR_HART_RV_LOW_TOO_LOW ,
    ERR_HART_RV_HIGH_TOO_HIGH ,
    ERR_HART_RV_HIGH_TOO_LOW ,
    ERR_HART_RV_BOTH_OOR ,
    ERR_HART_RV_SPAN_LOW,

    // Additionial Error codes for the Digital Potentiometer (DP)
    ERR_DP_DEVICE_LOCKED,
    ERR_DP_DEVICE_BUSY,
    
    ERR_WRITE_PROTECT //write lock set
};

LINT_PURE(err_CheckRange32)
LINT_PURE(err_CheckValue)
MN_DECLARE_API_FUNC(err_CheckRange32, err_CheckValue)
extern ErrorCode_t err_CheckRange32(s32 lrv, s32 urv, const s32 lrvrange[Xends], const s32 urvrange[Xends]);
extern ErrorCode_t err_CheckValue(s32 val, s32 lower, s32 upper);

#endif //ERRCODES_H_

/* This line marks the end of the source */
