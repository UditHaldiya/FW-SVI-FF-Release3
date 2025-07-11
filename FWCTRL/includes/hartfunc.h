/**
Copyright 2004 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.

    \file hartfunc.h
    \brief Public interfaces of the HART Functions Module

    The Mesco HART module must be modified to pass pointers to all
    of the hart command functions.

    CPU: Any

    OWNER: AK
*/

#ifndef HARTFUNC_H_
#define HARTFUNC_H_
#include "config.h"
#include "hartvers.h"
#if !defined(HART_REV_5) || (HART_REV_5 != 0) //There are versions other than HART 5
#include "ifman.h"
#endif
#include "errcodes.h"
#include "hmid.h"

//defines for the flags
#define HC_WRITE_PROTECT 0x01U
#define HC_MODIFY 0x02U
#define HC_WRITE_COMMAND (HC_MODIFY | HC_WRITE_PROTECT)
#define HC_READ_COMMAND 0x00U //Not used for anything
#define HC_UNPUBLISHED_COMMAND 0x00U //Not used for anything
#define HC_COMMAND_COMMAND HC_MODIFY
#define HC_PROCESS_COMMAND 0x04U
#define HC_FACTORY_COMMAND 0x08U

#ifdef OLD_DEVMODE
#define HC_ALLOWED_MODE_ALL HC_ALLOWED_MODE_MASK
#define HC_ALLOWED_MODE_NORMAL 0x40U
#define HC_ALLOWED_MODE_MAN 0x20U
#define HC_ALLOWED_MODE_OOS 0x10U
#define HC_ALLOWED_MODE_FS 0x80U
#define HC_ALLOWED_MODE_MAN_OOS (HC_ALLOWED_MODE_MAN|HC_ALLOWED_MODE_OOS)
#define HC_ALLOWED_MODE_MASK 0xf0U
#else
#include "devicemode.h"
#define HC_ALLOWED_MODE_SHIFT 4u
#define HC_MODE_BITMASK(mode) (((u8)(mode))<<HC_ALLOWED_MODE_SHIFT)

#define HC_ALLOWED_MODE_FS HC_MODE_BITMASK(MODE_FAILSAFE)
#define HC_ALLOWED_MODE_MAN HC_MODE_BITMASK(MODE_MANUAL)
#define HC_ALLOWED_MODE_OOS HC_MODE_BITMASK(MODE_SETUP)
#define HC_ALLOWED_MODE_NORMAL HC_MODE_BITMASK(MODE_OPERATE)
//Handy combo
#define HC_ALLOWED_MODE_ALL (HC_ALLOWED_MODE_MAN|HC_ALLOWED_MODE_OOS|HC_ALLOWED_MODE_NORMAL|HC_ALLOWED_MODE_FS) //note HC_ALLOWED_MODE_FS present
#endif //OLD_DEVMODE

//Module Member Data
struct hartDispatch_t
{
    u8 cmd; //command id
    u8 rsp_len; //response length, 2-based (+2, that is)
    u8 req_len; //request/command length; 0 means no length checking
    u8 flags;
    s8_least (*proc)(const u8 *src, u8 *dst); //processing function; if NULL, nothing to do
};
typedef struct hartDispatch_t hartDispatch_t;
extern const hartDispatch_t *HART_cmdlookup(u8_least key);

typedef enum hart_address_t
{
    //These are addressing from host (STX frame)
    hart_address_ok =0,
    hart_address_long = hart_address_ok,
    hart_address_broadcast =1,
    hart_address_not4us =2,
    hart_address_short = 3
        //no need in this: , hart_address_short_not4us = 4
    /*In the future, these may be expanded to addressing
      for listening to others ACK or even BACK frames
    */
} hart_address_t;

/** \brief Checks if the addressing is appropriate for a request (STX frame) command
\param cmd - received request command number
\param hart_address_type - addressing in the received command
\return true iff command COULD be accepted
*/
extern bool_t hart_TestStxAddressing(u8_least cmd, hart_address_t hart_address_type);

//Type of automatic subcommands support - HART 5
typedef struct SubCommandInfo_t
{
    u8 type_offset; //!< where the subcommand id is located in the input data frame
    u8 length_offset; //!< 1-based offset of the subcommand request length  in the input data frame (0=absent)
    u8 data_offset; //!< offset of the subcommand request data  in the input data frame
    const hartDispatch_t *(*lookup_func)(u8_least key); //A lookup function to rettrieve disp info for the subcommand
} SubCommandInfo_t;

const SubCommandInfo_t *hart_GetSubCommandInfo(u8_least cmd);
#define HART_WARNING_SCALER 12 //12 bits of range separation

typedef struct HartCmdParams_t
{
    u8 req_data_len;
    u8 rsp_data_len;
    u8 rsp_warning;
    HartMaster_t master;
} HartCmdParams_t;

#if !defined(HART_REV_5) || (HART_REV_5 != 0) //There are revisions other than 5
struct HartDispatch_t
{
    u8 cmd; //command id
    u8 rsp_len; //response length, 2-based (+2, that is)
    u8 req_len; //request/command length; 0 means no length checking
    u8 flags;
    s8_least (*proc)(const void *src, void *dst, HartCmdParams_t *params); //processing function; if NULL, nothing to do
};

//Type of automatic subcommands support - beyond HART 5
struct HartSubCommandInfo_t
{
    u8 type_offset; //!< where the subcommand id is located in the input data frame
    //not used u8 length_offset; //!< 1-based offset of the subcommand request length  in the input data frame (0=absent)
    u8 data_offset; //!< offset of the subcommand request data  in the input data frame
    const HartDispatch_t *(*lookup_func)(u8_least key); //A lookup function to rettrieve disp info for the subcommand
};

extern s8_least hart_BurstDispatchCommon(u8_least cmd, u8 *dst,
                        const HartDispatch_t *(*CmdlookupFunc)(u8_least cmd));

extern s32 hart_DispatchCommon(u8_least cmd, const u8 *src, u8 *dst, u8 req_data_len,
                        const HartSubCommandInfo_t *(*SubCmdInfoFunc)(u8_least cmd),
                        const HartDispatch_t *(*CmdlookupFunc)(u8_least cmd));
#endif //There are revisions other than 5


//Defines
#define HART_NOT_USED 250u //Common value across HART common enum tables


//----------------- HART commands response codes spec-307.pdf ---------------------
#define COMMAND_NOT_IMPLEMENTED                     64

#define HART_NO_COMMAND_SPECIFIC_ERRORS                   0
#define HART_TYPE_MISMATCH                                1 //obsolte not to be used
#define HART_COMMAND_UNDEFINED HART_TYPE_MISMATCH //use it to prevent fallback to previous HART version
#define HART_INVALID_SELECTION                            2
#define HART_PASSED_PARAMETER_TOO_LARGE                   3
#define HART_PASSED_PARAMETER_TOO_SMALL                   4
#define HART_TOO_FEW_DATA_BYTES_RECEIVED                  5
#define TRANSMITTER_SPECIFIC_COMMAND_ERROR           6
#define HART_WRITE_PROTECT_MODE                        7
#define HART_INVALID_LOCK_CODE                      HART_RV_LOW_TOO_LOW //multi-def error

#define HART_ERROR_BYTECOUNT 2u
#define HART_BUSY 32

#define HART_NOT_PROPER_OUTPUT_MODE HART_RV_LOW_TOO_HIGH //9 has multiple definitions; see chpater 3.1 in spec-307
#define HART_RV_LOW_TOO_HIGH 9 //multi-def err
#define HART_CANNOT_START_PROCESS HART_NOT_PROPER_OUTPUT_MODE //multi-def err
#define HART_RV_LOW_TOO_LOW 10
#define HART_RV_HIGH_TOO_HIGH 11
#define HART_RV_HIGH_TOO_LOW 12
#define HART_INVALID_SLOT HART_RV_HIGH_TOO_LOW //multi-def error
#define HART_NO_DATA HART_INVALID_SLOT  //multi-def error

#define HART_RV_BOTH_OOR 13
#define HART_RV_SPAN_INVALID 29 //(Spec307; undocumented in HART 5)

#define HART_INVALID_DATA HART_INVALID_SELECTION

// Definition of HART Response codes (not compatible with 3.1.x AP and ESD but correct-er)
#define HART_WRONG_MODE         HART_ACCESS_RESTRICTED
#define HART_ACCESS_RESTRICTED  16
#define HART_CANT_CHANGE_MODE   95
#define HART_FIND_STOPS_FAILED  94
#define HART_CAL_FAILED         93
#define HART_LOGF_ERROR         HART_CAL_FAILED //multi-definition error
#define HART_DIAG_NOT_ALLOWED   HART_ACCESS_RESTRICTED
#define HART_TUNE_NOT_ALLOWED   HART_ACCESS_RESTRICTED

#define HART_LOWERRANGE_TOOHIGH    HART_RV_LOW_TOO_HIGH
#define HART_LOWERRANGE_TOOLOW     HART_RV_LOW_TOO_LOW
#define HART_UPPERRANGE_TOOHIGH    HART_RV_HIGH_TOO_HIGH
#define HART_UPPERRANGE_TOOLOW     HART_RV_HIGH_TOO_LOW
#define HART_INVALID_SPAN          HART_RV_SPAN_INVALID
#define HART_INVALID_UNITCODE      18

//For cmd 45, 46
#define HART_INVALID_LOOPCURRENT_MODE_OR_VALUE    HART_NOT_PROPER_OUTPUT_MODE //multi-def error
#define HART_LOOPCURRENT_NOT_ACTIVATE    HART_RV_HIGH_TOO_HIGH


//--------------------------------------------------

#define HART_DEVICE_FAILED 0x80U
#define HART_CONFIG_CHANGED 0x40U
#define HART_COLD_START 0x20U
#define HART_ADDL_STATUS 0x10U
#define HART_LOOPCURRENT_FIXED 0x08U
#define HART_OUTPUT_FIXED HART_LOOPCURRENT_FIXED //compatibility
#define HART_OUTPUT_SATURATED 0x04U
#define HART_SECONDARYVAR_OUT_OF_LIMITS 0x02U
#define HART_PRIMARYVAR_OUT_OF_LIMITS 0x01U

//--------------------------------------------------
// Device Variable Units Codes (HART6-Spec 183, $5.2)

#define HART_PERCENT_CODE       57u
#define HART_CELSIUS_CODE       32u
//pressure units
#define HART_PSI_CODE            6u
#define HART_BAR_CODE            7u
#define HART_MBAR_CODE           8u
#define HART_PASCAL_CODE        11u //Pa
#define HART_KPASCAL_CODE       12u //kPa
//electric units
#define HART_VOLT_CODE          58u
#define HART_MVOLT_CODE         36u  //(mV)
#define HART_MAMP_CODE          39u  //(mA)
#define HART_TIME_CODE          51u  //(second)
//
#define HART_UNITSNONE_CODE     251u //counts, no units

//Types known to automatic HART commands import
#define H_UCHAR u8
#define H_CHAR u8
#define H_ASCII u8
#define H_ARRAY u8
#define H_FLOAT float32
#define H_UINT u16
#define H_INT s16
#define H_UINT4 u32
#define H_INT4 s32
typedef u8 H_UINT3[3];
typedef u8 H_INT3[3];

extern u8 hart_makeResponseFlags(HartMaster_t masterFlag, u8_least hart_version);
extern s8_least err2hart(ErrorCode_t err);
extern s8_least hart_CheckMode(u8 ModeFlag);

/** \brief Project-specific plugin to set device-specific status bits
\param partially assembled HART response byte 2
\return fully assembled HART response byte 2
*/
extern u8 hart_StatusPlugin(u8 rsp2);

#endif //HARTFUNC_H_
/* This line marks the end of the source */
