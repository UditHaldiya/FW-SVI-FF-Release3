/*
Copyright 2006-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file logfile.h
    \brief Public interfaces of the Log File module.

    CPU: Any

    OWNER: AK

    \ingroup logfile
*/

#ifndef LOGFILE_H_
#define LOGFILE_H_
#include <limits.h> //for CHAR_BIT
#include "errcodes.h"
#include "logfileconfig.h"

#define LOGFILE_AREA_ADDR logf_AreaBase //! project-dependent "right-aligned" area
extern const u16 logf_AreaBase; //! project-dependent log file data area base address

//Log access methods
#define LOG_WRITE 0
#define LOG_READ 1

//"No log open" marker
#define LOGF_INVALID ((1U<<(sizeof(LogfId_t)*CHAR_BIT)) - 1U)

//representation of log id in a byte
#define LOGF_IDMASK ((1U<<LOGF_IDBITS)-1U)
#define LOGF_ID(IdAge) ((IdAge) & LOGF_IDMASK) //!< extract id from age+id combo
#define LOGF_AGE(IdAge) ((IdAge)>>LOGF_IDBITS) //!< extract age from age+id combo
#define LOGF_AGEUNIT (1U<<LOGF_IDBITS)
#define LOGF_FULL_ID(Id, Version) ((Id) + (u8)((Version)<<LOGF_IDBITS))

/* These two project-independent definitions are sucked from thin air
to serve as project-independent upper boundaries, so that the types
using these numbers can be project-independent.
It is the responsibility of project-dependent logfdata.c (whether automatically
generated or not) to CONST_ASSERT that the actual project numbers do not
exceed these limits.
*/
#define LOGF_MAX_NUM_LOGS (1U<<LOGF_IDBITS) //! Max number of log files supported

#define LOGF_MAX_AGE ((1U<<((sizeof(LogfId_t)*CHAR_BIT)-LOGF_IDBITS))-2U) //-2, not -1, is to avoid clash with LOGF_INVALID
CONST_ASSERT( (((LOGF_MAX_AGE+1U)<<LOGF_IDBITS) + LOGF_IDMASK) == LOGF_INVALID );

//make sure we are within our arithmetic
CONST_ASSERT(LOGF_MAX_NUM_LOGS <= (LOGF_IDMASK+1U));

#define MAX_EXTENT_TYPES LOGF_MAX_NUM_LOGS //!< Max number of extents (and therefore extent types) a log can span (upper boundary)

extern const u8 logf_extents_total; //!< (from logfdata.c) project-dependent number of extents required
#define LOGF_EXT_COUNT_PROJ logf_extents_total //!< a transparent synonym for project-dependent number of extents required

extern const u8 logf_total; //!< project-dependent number of log files in the system
#define NUM_LOG_FILES_PROJ logf_total //!< an internal API synonym to the number of log files in the system

typedef struct logdata_t logdata_t;
struct logdata_t
{
    u8 extent_assignment[LOGF_EXT_COUNT];
    u16 CheckWord;
};

MN_DECLARE_API_FUNC(logf_Read,logf_Write,logf_Seek,logf_GetLastError,logf_CloseAnyRead,logf_GetLength)
MN_DECLARE_API_FUNC(logf_Retrieve)
/* You are free to use a common wrapper for reads or elemental functions to suppot reads.
These are optional API functions; the linker will remove the unused ones.
Functions marked as mandatory are required for the module integration
*/
//optional API functions
extern ErrorCode_t logf_Retrieve(void *data, u16 *plen, u8 logIdAge, u16 offset);
extern ErrorCode_t logf_Read(void *data, u16 *plen, u8 logId);
extern ErrorCode_t logf_Write(const void *data, u16 *plen, u8 logId);
extern ErrorCode_t logf_Seek(u16 *plen, u8 logId);
extern ErrorCode_t logf_Close(u8 logId, bool_t discard);
extern ErrorCode_t logf_Open(u8 logIdAge, u8 mode, u16 *plen);
extern ErrorCode_t logf_ResetFS(void);
extern u16_least logf_GetLength(void);
extern ErrorCode_t logf_GetLastError(void);
extern void logf_CloseAnyRead(void);
extern ErrorCode_t logf_Move(u8 temp, u8 dst);
extern ErrorCode_t logf_RetrieveAtomic(void *data, u16 *plen, u8 logIdAge, u16 offset);
LINT_PURE(logf_Exist)
extern bool_t logf_Exist(u8 logIdAge);

//functions mandatory for integration


extern ErrorCode_t TypeUnsafe_logf_InitSet(const void *src);
extern const void *TypeUnsafe_logf_InitGet(void *dst);

#endif //LOGFILE_H_
/* This line marks the end of the source */
