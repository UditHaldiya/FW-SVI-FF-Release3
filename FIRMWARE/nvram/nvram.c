/*
Copyright 2004-2007 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/** \addtogroup nvmem Non-volatile memory App layer management module
\brief Application layer interfaces to non-volatile memory device(s)

\htmlonly
<a href="../../../Doc/DesignDocs/Physical Design_nvram Module.doc"> Design document </a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/nvram1HTML.html"> Unit Test Report {1]</a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/nvram2HTML.html"> Unit Test Report {2]</a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/nvram3HTML.html"> Unit Test Report {3]</a><br>
<a href="../../inhouse/unit_test/Dbg/project_ESD/nvram4HTML.html"> Unit Test Report {4]</a><br>
\endhtmlonly
*/
/**
    \file nvram.c
    \brief Application layer of non-volatile memory interface

     CPU: Any

    OWNER: AK

    \ingroup nvmem
*/

#define NEED_NVMEM_END
#include "mnwrap.h"

// ------------------------- NVMEM access size - must be before nvram.h -------------
//lint -estring(961, *nv_rw_size*)
u16 nv_rw_size = 0U;

#include "errcodes.h"
#include "oswrap.h"
#include MEMMAP_H_
#include "mnassert.h"
#include "mncbtypes.h"
#include "faultpublic.h"
#include "nvmempriv.h"
#include "inituc.h" //for bios_SetVPBDividier_to2()
#include "fram.h"
#include "watchdog.h"
//#include "mncbdefs.h"
#include "process.h"

#include "nvram.h"
#include "watchdog.h"
#include "bitutils.h"

#include "power.h"
#include "mntrapdef.h"
#include "timer.h" //for bios_GetTimer0Ticker()
#include "resource.h"

//lint -emacro({826}, CHECKWORD_ADDR)  area too small:  The checksum is the two bytes beyond (dst + len)
#define CHECKWORD_ADDR(addr, len) ((u16 *)((u8*)(addr) + (len)))

#define HALFWORD_HIGH(word) (((u32)word)>>16) //!< extractor of low 16 bits of a word
#define NVRAM_CRC_SIZE sizeof(u16) //!< the number of bytes in NV memory that a CRC entry takes
#define length2halfwords(len) ((len)/2U) //!< (even) length in bytes (8 bits) converted to length in halfwords (16 bits)

//type and enum for initializing structures
typedef enum InitType_t InitType_t;
enum InitType_t
{
    INIT_FROM_NVRAM,
    INIT_TO_DEFAULT
};

/** Normally, NVRAM writes are skipped if there is an NVRAM fault. This is for
post mortem analysis of the dead unit. To ensure the unit can be initialized at all,
the passthrough flag, if true, disables this protection.
*/
static bool_t passthrough = false;

//forward
static ErrorCode_t nvram2ram(nvramId_t id, void *dst);


// ------------------------- NVMEM layout reporting section -----------------------------------------


/** \brief A public interface to retrieve NVMEM map
\param id - project-independent NVMEM id
\param[out] offset - a pointer to NVMEM offset holder
\param[out] length - a pointer to NVMEM entry length holder
\param[out] volid - a pointer to NVMEM entry volume id holder
\return true iff there is an entry.
*/
bool_t nvmem_GetMapEntry(nvramId_fast_t id, u16 *offset, u16 *length, u8 *volid)
{
    if(id >= NVRAM_ENTRIES)
    {
        return false;
    }
    if(offset != NULL)
    {
        *offset = nvram_map[id].offset + nvmem_GetVolumeBase(nvram_map[id].volid);
    }
    if(length != NULL)
    {
        *length = nvram_map[id].length;
    }
    if(volid != NULL)
    {
        *volid = nvram_map[id].volid;
    }
    return true;
}

//--------------------- thread-safe wrappers -----------------------

static ErrorCode_t nv_ReadExt(u8 *data, u32 addr, u32 length, u8 volid)
{
    ErrorCode_t err;
    if(oswrap_IsOSRunning())
    {
        MN_NVMEM_LOCK(length);
            err = nvmem_ReadVol(data, addr, length, volid);
        MN_NVMEM_UNLOCK();
    }
    else
    {
        err = nvmem_ReadVol(data, addr, length, volid);
    }
    return err;

}
static ErrorCode_t nv_WriteExt(const u8 *data, u32 addr, u32 length, u8 volid, bool_t get_mutex)
{
    ErrorCode_t err;
    if(get_mutex)
    {
        MN_NVMEM_LOCK(length);
            err = nvmem_WriteVol(data, addr, length, volid);
        MN_NVMEM_UNLOCK();
    }
    else
    {
        err = nvmem_WriteVol(data, addr, length, volid);
    }
    return err;
}

// --------------- NVMEM test static-duration data ---------------
/** The NVRAM Id under test. We don't care about the init value (will reset)
Also, it is self-repairing against glitches for the price of repeated portion
of the full test
*/
static u8 currId; //we don't care about the init value

/** If SAFEVAL(x) is defined non-empty, the bit patterns of valid states are
two-four bits apart, and a RAM glitch is very unlikely to make a legit value out
of another legit value. The price for it is about 200 bytes increase in the size
of speed-optimized switch statement code.
*/
//#define SAFEVAL(x) =(x)
#define SAFEVAL(x)

typedef enum //!< type for state of the NVRAM self-test
{
    read1 SAFEVAL(0x03), //!< read 1st copy
    rd4verify2 SAFEVAL(0x0c),  //!< read 2nd copy to verify against the valid 1st one
    write1 SAFEVAL(0x30), //!< write (recover) 1st copy
    read2 SAFEVAL(0xc0),  //!< read 2nd copy to restore the 1st one
    verify2 SAFEVAL(0x55), //!< verify the valid 2nd copy against the valid 1st one
    write2 SAFEVAL(0xaa), //!< write (recover) 2nd copy
    verifywrite1 SAFEVAL(0xa5),  //!< verify write1 operation
    verifywrite2 SAFEVAL(0x5a)  //!< verify write2 operation
} nvramtest_t;

/** The phase of time-separated test for a given NVRAM id.
If it has an invalid value, it is self-repairing (see nvram_PageTest_Internal).
If SAFEVAL(x) is defined non-empty, the bit patterns of valid phases are
four bits apart, and a RAM glitch is very unlikely to make a legit value out
of another legit value.
*/
static volatile nvramtest_t nvphase;

static void nvram_PageTest_OnInit(void); //forwrad

//----------- our own initialization ----------------
static StartupVersionNumber_t StartupVersionNumber[NVMEM_MAX_VOLID+1]; //not used except init and save

/** \brief NVMEM Initialization interface.

A quirk here is that if
- the last write before reset is valid,
- and on the right volume volid,
- and volume signature is correct (no FRAM layout change)
then we attempt to test the last write with any necessary repairs.
This addresses the following scenario that might otherwise ruin NVMEM:
1. A reset occurred during write of the second copy of a record (copy 1 good, copy 2 bad)
2. A reset occurred during write of the first copy of the same record (both copies bad)
3. A reset occurred and now we have FRAM fault.
While it may seem a remote possibility, it occurred in the field (AFAIK, once)
It is more likely with devices willing to reset at low power conditions (DLT12400)

\param index - index of NVMEM volume
\param src - a pointer to NVMEM signature
*/
ErrorCode_t TypeUnsafe_nvmem_SetVersion(u8_least index, const void *src)
{
    const StartupVersionNumber_t *v = src;
    u32 VersionNumber;
    if(v == NULL)
    {
        VersionNumber = nvmemVolConf[index].signature;
    }
    else
    {
        VersionNumber = v->VersionNumber;
    }
    ErrorCode_t err = (VersionNumber == nvmemVolConf[index].signature)?ERR_OK:ERR_INVALID_PARAMETER;
    if(err == ERR_OK)
    {
        err = nvram_SetSignature(VersionNumber, index);
    }
    if(err == ERR_OK)
    {
        if(!oswrap_IsOSRunning())
        {
            //initalization
            u8 testid = currId;
            if((testid < NVRAM_ENTRIES) && (nvram_map[testid].volid == index))
            {
                //presume currId valid and attempt to repair a potentially interrupted write if we are doing the right volume
                do
                {
                    nvram_PageTest_OnInit();
                } while(testid == currId);
            }
        }
    }
    return err;
}

const void *TypeUnsafe_nvmem_GetVersion(u8_least index, void *dst)
{
    if(index > NVMEM_MAX_VOLID)
    {
        return NULL;
    }
    return STRUCT_GET(&StartupVersionNumber[index], dst);
}

/** \brief An API to set any device signature
\param signature - a 32-bit pattern
*/
ErrorCode_t nvram_SetSignature(u32 signature, u8_least volid)
{
    if(volid > NVMEM_MAX_VOLID)
    {
        return ERR_INVALID_PARAMETER;
    }
    StartupVersionNumber[volid].VersionNumber = signature;
    STRUCT_CLOSE(StartupVersionNumber_t, &StartupVersionNumber[volid]);
    return ram2nvramAtomic(nvmemVolConf[volid].id);
}

/** \brief A helper in a pass of persistent RAM initialization
\param skipflags - a bitmask of init flags of init phases to *NOT* skip
\param waitf - a pointer to function to run between each record. Presumably, it satisfies the watchdog(s)
*/
void ram_InitPass(u8 skipflags, void (*waitf)(void))
{
    nvramId_t nid;
    u8_least volid;
    const void *src; //where the data nuts come from
    //for init debugging: itype = INIT_TO_DEFAULT;

    for(volid=0; volid < NVMEM_MAX_VOLID+1; volid++)
    {
        InitType_t itype = INIT_FROM_NVRAM;
        ErrorCode_t err=ERR_OK;
        do
        {
            for(nid=0; nid < NVRAM_ENTRIES; nid++)
            {
                bool_t fixme = false;
                if((nvram_map[nid].volid == volid) && ((nvram_map[nid].flags & NVMFLAG_INIT_MASK & ~skipflags) == 0U))
                {
                    if(nvram_map[nid].initf.simple != NULL) //if application function is registered for this id...
                    {
                        if(itype == INIT_FROM_NVRAM)
                        {
                            //read from NVMEM
                            err = nvram2ram(nid, temppad);
                            src = temppad;

                            if((err != ERR_OK) && ((nvram_map[nid].flags & NVMFLAG_DEFAULT_RECOVER) != 0U))
                            {
                                //take the default; the app function shall figure out what to do
                                src = NULL;
                                fixme = true;
                            }
                        }
                        else
                        {
                            //take the default; the app function shall figure out what to do
                            err = ERR_OK;
                            src = NULL;
                        }

                        u8_least index = nvram_map[nid].index;
                        if(err == ERR_OK)
                        {
                            if(index == 0)
                            {
                                err = nvram_map[nid].initf.simple(src);
                            }
                            else
                            {
                                err = nvram_map[nid].initf.indexed(index-1, src);
                            }
                        }
                        if((err != ERR_OK) && ((nvram_map[nid].flags & NVMFLAG_DEFAULT_RECOVER) != 0U))
                        {
                            //This is the case when NVMEM data CRC is bad or it is good but Set function didn't accept it:
                            //take the default; the app function shall figure out what to do
                            src = NULL;
                            //Second try - with defaults
                            if(index == 0)
                            {
                                err = nvram_map[nid].initf.simple(src);
                            }
                            else
                            {
                                err = nvram_map[nid].initf.indexed(index-1, src);
                            }
                            fixme = true;
                        }

                        if(fixme) //can only be set for NVMFLAG_DEFAULT_RECOVER - review!
                        {
                            faultcode_t fcode;
                            if((nvram_map[nid].flags & NVMFLAG_GROUP_RECOVER) != 0)
                            {
                                //Only one group to recover now
                                fcode = nvmemVolConf[volid].fault_write; //hijack the fault id
                            }
                            else
                            {
                                fcode = nvmemVolConf[volid].fault_test;
                                ErrorCode_t err1 = ram2nvram(nid);
                                UNUSED_OK(err1); //if fails, will try to fix next boot
                            }
                            error_SetFault(fcode);
                        }
                        if(err != ERR_OK)
                        {
                            //Instead of setting a fault, give it a second chance by doing a trap
                            MN_RT_ASSERT(err != ERR_I2C_BUS_STUCK); //not VERY indicative but OK
                            error_SetFault(nvmemVolConf[volid].fault_crc);
                            //default values must be accepted without errors or we deservedly get a brick
                            MN_RT_ASSERT(itype == INIT_FROM_NVRAM);
                            itype = INIT_TO_DEFAULT;
                            break;
                        }

                        if(waitf != NULL)
                        {
                            waitf();  /* in case we were in the function for a long time */
                        }
                    }
                }
            }
        } while(err != ERR_OK);
    }

    //(Re-)init the NVMEM test state
    currId = 0;
    nvphase = read1;
}

/** \brief Initialization of all data with NVRAM image

    OS must NOT be running!
*/
void ram_InitCold(void)
{
    bios_SetVPBDividier_to2(false);  /* full clock speed during configuration load */

    //Initialize data for repair of potentially interrupted write
    (void)fram_ReadExt((void *)&currId, NVM_PREWRITE_ADDR, sizeof(currId), 0); //always in unit 0
    nvphase = read1;

    ram_InitPass(NVMFLAG_INIT_1, wdog_WatchdogTrigger);

    bios_SetVPBDividier_to2(true);  /* back to normal speed */
}

/** \brief Initialization of all tiered data with NVRAM image

    Does not accelerate peripheral clock on first init
    Acquires mutex to access NVMEM as needed
    Tickles watchdog unconditionally

    \param skipflags - a bitmap of init tiers to skip
*/
void ram_InitBrutal(u8 skipflags)
{
    MN_NVMEM_LOCK(UINT16_MAX); //make it obcenely large: who cares
        ram_InitPass(skipflags, wdog_WatchdogTrigger);
    MN_NVMEM_UNLOCK();
}

#if 1 //TODO: Remove process dependency
static void procwait(void)
{
    (void)process_WaitForTime(1U); //Min delay to allow normal watchdog mechanism
    //we've ignored a possible cancel request because we do not cancel this operation!
}

/** \brief Writes NVRAM from RAM all id's with start<=id<end.
Note that start is inclusive and end exclusive

    IMPORTANT: Can only be called from the process task's context!!!
    NOTE: Do NOT try to accelerate it with SetVPBDividier_to2()! It would
    screw up HART timing while the message is going out
    \param start - the first id to write
    \param end - 1 greater than the last id to write
*/
ErrorCode_t ram_CommitRange(bool_t (*selector)(u8 volid, u8 flags))
{
    return ram_CommitRangeExt(selector, procwait);
}
#endif

ErrorCode_t ram_CommitRangeExt(bool_t (*selector)(u8 volid, u8 flags), void (*waitf)(void))
{
    nvramId_t id;
    ErrorCode_t err;

    for(id=0; id < NVRAM_ENTRIES; id++)
    {
        const nvramMap_t *nvrow = &nvram_map[id];
        if(selector(nvrow->volid, nvrow->flags))
        {
            passthrough = true; //AK:TODO: This is an insufficient protection!
            err = ram2nvramAtomic(id);
            passthrough = false;
            if(waitf != NULL)
            {
                waitf();
            }
            if(err != ERR_OK)
            {
                return err;
            }
        }
    }
    return ERR_OK;
}


//------------------------- FRAM self-test section -----------------------------

typedef struct nvTransition_t nvTransition_t;
typedef ErrorCode_t nvramtestfunc_t(const nvTransition_t *testline, const nvramMap_t *nvrow);
/** NVMEM self-test configuration type */
struct nvTransition_t
{
    nvramtest_t next_OnOK;
    nvramtest_t next_OnErr;
    bool_t cpy2;
    nvramtestfunc_t *func;
    u16 *pRead;
    u16 *pWrite;
};

static u16 testlength = 0U;
static u16 testoffset = 0U;
#define NVTEST_CHUNK 20U //! max chunk to read/write during self-test deemed unobstructive to other accesses


/** \brief a function to do the chores of read1 or rd4verify2 phase of testing an NVM structure
where we just read the NVMEM image in.
\param pRead - RAM buffer to read the data into
\param pWrite - RAM buffer to write the data from (don't care)
\param offset - NVMEM address offset
\param length - the data length, CRC/Checksum field included
\return an error code
*/
static ErrorCode_t nvwrap_ReadFRAM(const nvTransition_t *testline, const nvramMap_t *nvrow)
{
    ErrorCode_t err;

    u16_least offs = nvrow->offset + nvmem_GetVolumeBase(nvrow->volid);
    if(testline->cpy2)
    {
        offs += nvrow->length + NVRAM_CRC_SIZE;
    }

    if(testoffset == 0U)
    {
        testlength = nvrow->length + NVRAM_CRC_SIZE; //we started read of a new NV record
    }

    //Read a small piece so as to not upset the rest of the code
    u16 rlen = MIN(testlength, NVTEST_CHUNK);

    err = nv_ReadExt((u8*)testline->pRead+testoffset, offs+testoffset, rlen, nvrow->volid);

    if(err == ERR_OK)
    {
        testlength -= rlen;
        if(testlength == 0)
        {
            testoffset = 0; //done with this read
            const u16 *pCheckWord = CHECKWORD_ADDR(testline->pRead, nvrow->length); //That's where the checksum is;
            if( *pCheckWord != HALFWORD_HIGH(hCrcChsum16(CRC_SEED, testline->pRead, length2halfwords(nvrow->length))) )
            {
                err = ERR_NVMEM_CRC;
            }
        }
        else
        {
            testoffset += rlen;
        }
    }
    return err;
}

/** \brief a function to do the chores of read2 phase of testing an NVM structure
where we read image 2 with the idea to write (restore) it to image 1.
\param pRead - RAM buffer to read the data into
\param pWrite - RAM buffer to write the data from
\param offset - NVMEM address offset
\param length - the data length, CRC/Checksum field included
\return an error code
*/
static ErrorCode_t nvwrap_ReadFRAM2(const nvTransition_t *testline, const nvramMap_t *nvrow)
{
    ErrorCode_t err = nvwrap_ReadFRAM(testline, nvrow);
    if(err != ERR_OK)
    {
        error_SetFault(nvmemVolConf[nvrow->volid].fault_test);
        ++currId;
    }
    return err;
}


/** \brief a function to do the chores of verify2 phase of testing an NVM structure
where we compare two good images.
\param pRead - RAM buffer to read the data into
\param pWrite - RAM buffer to write the data from
\param offset - NVMEM address offset
\param length - the data length, CRC/Checksum field included
\return an error code
NOTE. While a legal battle is raging over whether * and const * are
compatible types, we'll do the cast.
*/
static ErrorCode_t nvwrap_Verify(const nvTransition_t *testline, const nvramMap_t *nvrow)
{
    ErrorCode_t err;
    if(0 == mn_memcmp(testline->pRead, testline->pWrite, nvrow->length + NVRAM_CRC_SIZE))
    {
        err = ERR_OK;
        ++currId;
    }
    else
    {
        err = ERR_NVMEM_WRITE;
    }
    return err;
}

/** \brief a function to do the chores of write1 or write2 phase of testing an NVM structure
where we overwrite a bad image with a good one.
\param pRead - RAM buffer to read the data into
\param pWrite - RAM buffer to write the data from
\param offset - NVMEM address offset
\param length - the data length, CRC/Checksum field included
\return an error code
*/
static ErrorCode_t nvwrap_WriteFRAM(const nvTransition_t *testline, const nvramMap_t *nvrow)
{
    ErrorCode_t err;
    size_t len = nvrow->length + NVRAM_CRC_SIZE;
    u16_least offs = nvrow->offset  + nvmem_GetVolumeBase(nvrow->volid);
    if(testline->cpy2)
    {
        offs += len;
    }

    if(error_IsFault(nvmemVolConf[nvrow->volid].fault_crc))
    {
        err = ERR_NVMEM_CRC;
    }
    else
    {
        if(testoffset == 0U)
        {
            testlength = nvrow->length + NVRAM_CRC_SIZE; //we started read of a new NV record
        }

        //Read a small piece so as to not upset the rest of the code
        u16 rlen = MIN(testlength, NVTEST_CHUNK);

        err = nv_WriteExt((u8*)testline->pWrite+testoffset, offs+testoffset, rlen, nvrow->volid, oswrap_IsOSRunning());

        if(err == ERR_OK)
        {
            testlength -= rlen;
            if(testlength == 0)
            {
                testoffset = 0; //done with this write
            }
            else
            {
                testoffset += rlen;
            }
        }
    }
    if(err != ERR_OK)
    {
        error_SetFault(nvmemVolConf[nvrow->volid].fault_write);
        ++currId;
    }
    return err;
}


/** \brief a function to do the chores of write1 or write2 phase of testing an NVM structure
where we overwrite a bad image with a good one.
\param pRead - RAM buffer to read the data into
\param pWrite - RAM buffer to write the data from
\param offset - NVMEM address offset
\param length - the data length, CRC/Checksum field included
\return an error code
*/
static ErrorCode_t nvwrap_VerifyWriteFRAM(const nvTransition_t *testline, const nvramMap_t *nvrow)
{
    ErrorCode_t err = nvwrap_ReadFRAM(testline, nvrow);
    if((err == ERR_OK) && (testoffset == 0))
    {
        if(0 != mn_memcmp(testline->pRead, testline->pWrite, nvrow->length + NVRAM_CRC_SIZE))
        {
            err = ERR_NVMEM_WRITE;  //verify failed
        }
    }

    if((err != ERR_OK) && (err != ERR_NVMEM_CRC))
    {
        error_SetFault(nvmemVolConf[nvrow->volid].fault_write);
    }

    ++currId;
    return err;
}


static const nvTransition_t testtable[] =
{
    [read1] =
    {
        .next_OnOK = rd4verify2,
        .next_OnErr = read2,
        .cpy2 = false,
        .func = nvwrap_ReadFRAM,
        .pRead = testpad1,
        .pWrite = NULL
    },
    [rd4verify2] =
    {
        .next_OnOK = verify2,
        .next_OnErr = write2,
        .cpy2 = true,
        .func = nvwrap_ReadFRAM,
        .pRead = testpad2,
        .pWrite = NULL
    },
    [read2] =
    {
        .next_OnOK = write1,
        .next_OnErr = read1,
        .cpy2 = true,
        .func = nvwrap_ReadFRAM2,
        .pRead = testpad2,
        .pWrite = NULL
    },
    [verify2] =
    {
        .next_OnOK = read1,
        .next_OnErr = write2,
        .cpy2 = false,
        .func = nvwrap_Verify,
        .pRead = testpad2,
        .pWrite = testpad1
    },
    [write1] =
    {
        .next_OnOK = verifywrite1,
        .next_OnErr = read1,
        .cpy2 = false,
        .func = nvwrap_WriteFRAM,
        .pRead = NULL,
        .pWrite = testpad2
    },
    [verifywrite1] =
    {
        .next_OnOK = read1,
        .next_OnErr = read1,
        .cpy2 = false,
        .func = nvwrap_VerifyWriteFRAM,
        .pRead = testpad1,
        .pWrite = testpad2
    },
    [write2] =
    {
        .next_OnOK = verifywrite2,
        .next_OnErr = read1,
        .cpy2 = true,
        .func = nvwrap_WriteFRAM,
        .pRead = NULL,
        .pWrite = testpad1
    },
    [verifywrite2] =
    {
        .next_OnOK = read1,
        .next_OnErr = read1,
        .cpy2 = true,
        .func = nvwrap_VerifyWriteFRAM,
        .pRead = testpad2,
        .pWrite = testpad1
    },
};



/** \brief A common helper to execute one phase of NVMEM test

Also sets the next phase to execute
\param nvtphase - phase to execute
*/
static void testphase(nvramtest_t nvtphase)
{
    const nvTransition_t *testline;
    const nvramMap_t *nvrow = &nvram_map[currId];
    testline = &testtable[nvtphase];
    ErrorCode_t err = testline->func(testline, nvrow);
    if(err==ERR_OK)
    {
        if(testoffset == 0U) //phase completed
        {
            nvphase = testline->next_OnOK;
        }
    }
    else
    {
        testoffset = 0U;
        nvphase = testline->next_OnErr;
    }
}

/**
\brief Checks NVRAM entries one at a time. This function executes one step
and must be called periodically. A dummy/default process is a good candidate.

The check is split in several pieces:
- Read the 1st copy
- if it is OK,
    - read the 2nd copy
    - if it is bad, write 1st copy to 2nd copy
    - if it is good, compare with the 1st
        - if comparison fails, write 1st copy to 2nd copy
- if 1st is bad
    - read 2nd
    - if it is good, write 2nd to 1st
    - if it is bad, set the fault
If FRAM write occurs between the phases to the entry under test,
then before we get to the next phase, both copies will be written,
and a mismatch will cause an extra FRAM write. To avoid this, we reset
the test phase if the id just written is the id under test (in ram2nvram below).
*/
void nvram_PageTest(void)
{
    nvramtest_t nvt;  //a local copy
    static u32 timestamp = 0U;

    if(error_IsFault(FAULT_FACTORYWRITE))
    {
        currId = NVRAM_ENTRIES; //invalidate the test state
    }
    else
    {
            //Since nvphase can be reset externally, everything has to be within mutex guard.
            nvt = nvphase;
            if((u32)nvt >= NELEM(testtable))   //nvphase out of wack??
            {
                nvt = read1; //make a valid state of the test phase
            }
            if(currId >= NVRAM_ENTRIES)
            {
                currId = 0;
                nvt = read1;
            }

            testphase(nvt);

        if(currId == NVRAM_ENTRIES)
        {
            //completed the round of FRAM test
            tick_t tdiff = timer_GetTicksSince(timestamp);
            selftest_SetNvmemRoundTripTime(tdiff); //valid up to 0xFFFFFFFF*.005s > 248 days. Should be enough :)
            timestamp += tdiff;
        }
    }
}

/** \brief A clone of nvram_PageTest_Internal for init when OS isn't running yet
*/
static void nvram_PageTest_OnInit(void)
{
    nvramtest_t nvt;  //a local copy
    nvt = nvphase;

    MN_DBG_ASSERT(!oswrap_IsOSRunning() && ((size_t)nvt < NELEM(testtable))) ; //by construction of initialization phase

    if(currId < NVRAM_ENTRIES) //valid currId retrieved from FRAM
    {
        testphase(nvt);
    }
    else
    {
        currId = 0U;
    }
}

// --------------------------- Data read/write section -------------------------------------


/** \brief Read data from NVMEM - application layer
    This function can only be called when the RAM image is bad (init or RAM fault)
    So, we are not shy of clobbering the destination buffer on read failure
    \param[out] dst - a pointer to the destination buffer (NULL means data is left in the predefined internal buffer)
    \param id - the data structure id (predefined)
    \return a pointer to the buffer where the data is read to
*/
static ErrorCode_t nvram2ram(nvramId_t id, void *dst)
{
    u16 len;
    u32 offs;
    ErrorCode_t err;
    u16 *pCheckWord;

    if(id >= NVRAM_ENTRIES)
    {
        return ERR_INVALID_PARAMETER;
    }

    len = nvram_map[id].length;
    offs = nvram_map[id].offset + nvmem_GetVolumeBase(nvram_map[id].volid);

    pCheckWord= CHECKWORD_ADDR(dst, len);

    u8_least i;
    u32 crcchecksum;
    //MN_ASSERT((!oswrap_IsContext(TASKID_CONTROL)) || (!oswrap_IsOSRunning()));        // make sure it is not the Control task calling

    for(i=0; i<NV_NUMCOPIES; i++)
    {
        err = nv_ReadExt(dst, offs, len + NVRAM_CRC_SIZE, nvram_map[id].volid);
        crcchecksum = hCrcChsum16(CRC_SEED, dst, length2halfwords(len));

        if(err == ERR_OK)
        {
            if(HALFWORD_HIGH(crcchecksum) != (u32)*pCheckWord)
            {
                err = ERR_NVMEM_CRC;
            }
        }
        if(err == ERR_OK)
        {
            break;
        }
        //Try reading from the copy
        offs += len + NVRAM_CRC_SIZE;
    }

    //Regardless of whether we managed to read OK: fill the checksum
    *pCheckWord = (u16)crcchecksum;

    return err;
}

/** \brief Write data to NVMEM - application layer helper
    \param id - the data structure id (translated "real id")
    \param cpmask - a mask of copies to write
*/
static ErrorCode_t ram2nvram_raw(nvramId_fast_t id, u8_least cpmask, bool_t get_mutex)
{
    //put the data to write in temppad
    u8_least index = nvram_map[id].index;
    if(index == 0)
    {
        (void)nvram_map[id].getf.simple(temppad);
    }
    else
    {
        (void)nvram_map[id].getf.indexed(index - 1, temppad);
    }

    u16 len = nvram_map[id].length;
    u32 offs = nvram_map[id].offset + nvmem_GetVolumeBase(nvram_map[id].volid);
    u32 CrcChecksum;
    u16 *pDstCheckWord;

    //Compute CRC and checksum
    CrcChecksum = hCrcChsum16(CRC_SEED, temppad, (len>>1));

    pDstCheckWord = CHECKWORD_ADDR(temppad, len); //That's where the checksum is;

    if((u16)CrcChecksum == *pDstCheckWord)
    {
        //Data is good; replace checksum with CRC
        *pDstCheckWord = CrcChecksum>>16;
    }
    else
    {
        //RAM fault
        mn_assert(HARDWARE(const void *, id), -TRAPID_RAMDATA);
    }

    ErrorCode_t err = ERR_OK;
    //write all copies in the mask at once

    for(u8_least i=0; i<NV_NUMCOPIES; i++)
    {
        if(((1U<<i) & cpmask) != 0U) //write of this copy requested?
        {
            err = nv_WriteExt((void *)temppad, offs, len+NVRAM_CRC_SIZE, nvram_map[id].volid, get_mutex);
            if(err != ERR_OK)
            {
                error_SetFault(nvmemVolConf[nvram_map[id].volid].fault_write);
            }
        }
        //to the next copy
        offs += len + NVRAM_CRC_SIZE;
    }
    return err;
}

/** \brief Write data to NVMEM - application layer.

    This version handles atomic copying and configuration changed flag
    automatically as configured in the table (nvramflags).

    To help self-test consistent behavior, we reset the test phase if
    the id just written is the id under test.
    \param id - the data structure id (predefined)
    \param cpmask - a mask of copies to write
*/
ErrorCode_t ram2nvramExt(nvramId_fast_t id, u8_least cpmask, bool_t get_mutex)
{
    //Do we have an erroneous program flow?
    MN_DBG_ASSERT((!oswrap_IsContext(TASKID_CONTROL)) || (!oswrap_IsOSRunning()));        // make sure it is not the Control task calling

	// nvram writes not allowed during raw nvram update
    if (error_IsFault(FAULT_FACTORYWRITE))
    {
        return ERR_MODE_ILLEGAL_SUBMODE;                                 // early return - prerequisite
    }

    /* IMPORTANT:
       If FAULT_NVM_CHECKSUMx is set, DO NOT write anything!
       Otherwise, we may clobber bad data needed for
       post mortem analysis
    */
    if(error_IsFault(nvmemVolConf[nvram_map[id].volid].fault_crc) && (!passthrough))
    {
        //do nothing and get out
        return ERR_NOT_SUPPORTED;
    }

    if (!power_OKtoWriteFRAM())
    {
        return ERR_CNFG_PROTECTED_LIMITS;
    }

    ErrorCode_t err;
#ifdef NVRAMID_ConfigurationChanged
    //NB: Because of recursion, DO NOT use temppad (or any non-reentant data) before this point!!!
    if((nvram_map[id].flags & NVMFLAG_CONF_CHANGED) != 0)
    {
        err = nvram_SetFRAMConfigurationChanged(true, true, get_mutex); //This may cause depth 1 recursion; we can live with it
        if(err != ERR_OK)
        {
            return err;
        }
    }
#endif //NVRAMID_ConfigurationChanged
    return ram2nvram_prechecked(id, cpmask, get_mutex);
}

/** \brief Write data to NVMEM - backward-compatible application layer.

    This version handles atomic copying and configuration changed flag
    automatically as configured in the table (nvramflags).

    To help self-test consistent behavior, we reset the test phase if
    the id just written is the id under test.
    \param id - the data structure id (predefined)
*/
ErrorCode_t ram2nvram(nvramId_fast_t id)
{
    return ram2nvramExt(id, NV_ALLCOPIES, false); //request all copies
}

ErrorCode_t ram2nvram_prechecked(nvramId_fast_t id, u8_least cpmask, bool_t get_mutex)
{
    //Push NVRAMID on NVMEM for reset recovery
    u8 prewrite = (u8)id;
    CONST_ASSERT(sizeof(prewrite) <= NVM_PREWRITE_SIZE);

    ErrorCode_t err = nv_WriteExt((void *)&prewrite, NVM_PREWRITE_ADDR, sizeof(prewrite), 0, get_mutex); //always in vol 0
    if(err == ERR_OK)
    {
        //pre-write OK; ready to write

        //If we screwed up the test pad or wrote data under test, reset the test.
        /* EXPLANATION: We could not have preempted the FRAM test because it acquires
           the FRAM mutex when it runs. So it will re-read nvphase.
        */
        if(currId == id)
        {
            nvphase = read1;
            testoffset = 0; //to the beginning
        }

        err = ram2nvram_raw(id, cpmask, get_mutex);
    }
    return err;
}

/** \brief ATOMIC Write data to NVMEM - application layer.

Acquires and frees the FRAM mutex separately for every copy to write
so that the app doesn't need to bother
    \param id - the data structure id (predefined)
    \param cpmask - a mask of copies to write
*/
ErrorCode_t ram2nvramAtomicExt(nvramId_fast_t id, u8_least cpmask)
{
    ErrorCode_t err = ERR_OK;
    if(oswrap_IsOSRunning())
    {
        for(u8_least i=0U; i<NV_NUMCOPIES; i++)
        {
            u8_least bmask = 1U<<i;
            if((cpmask & bmask) != 0U) //we want to write this copy
            {
                MN_NVMEM_LOCK(nvram_map[id].length + NVRAM_CRC_SIZE);
                    ErrorCode_t err1 = ram2nvramExt(id, bmask, false);
                    if(err != ERR_OK)
                    {
                        err = err1; //need only one success
                    }
                MN_NVMEM_UNLOCK();
            }
        }
    }
    return err;
}

/** \brief ATOMIC Write data to NVMEM - backward-compatible application layer.

Acquires and frees the FRAM mutex so that the app doesn't need to bother
    \param id - the data structure id (predefined)
*/
ErrorCode_t ram2nvramAtomic(nvramId_fast_t id)
{
    ErrorCode_t err = ERR_OK;
    if(oswrap_IsOSRunning())
    {
        MN_NVMEM_LOCK((nvram_map[id].length + NVRAM_CRC_SIZE)*NV_NUMCOPIES);
            err = ram2nvramExt(id, NV_ALLCOPIES, false); //we grabbed mutex for all copies
        MN_NVMEM_UNLOCK();
    }
    return err;
}

//-------- utilities ---------------

/** \brief A type-unsafe utility to retrieve RAM-cached data
of an object with NVMEM image
NOTE: Relays to the object's "get" function which obviously cannot use this util.
\param dst - a pointer to destination memory buffer or a NULL
\param id - NVRAMID of the object
\return a pointer to "live" object or NULL if invalid id
*/
const void *nvmem_GetItemById(void *dst, nvramId_fast_t id)
{
    const void *p;
    u8 index = nvram_map[id].index;
    if(index == 0)
    {
        p = nvram_map[id].getf.simple(dst);
    }
    else
    {
        p = nvram_map[id].getf.indexed(index-1, dst);
    }
    return p;
}

/** \brief A type-unsafe utility to set RAM (but not FRAM - A BUG HERE: FRAM IS WRITTEN TO!)
of an object with NVMEM image.
NOTE: Relays to the object's "set" function which obviously cannot use this util.
\param src - a pointer to a new value of the object
\param id - NVRAMID of the object
\return an error code
*/
ErrorCode_t nvmem_SetItemById(const void *src, nvramId_fast_t id)
{
    ErrorCode_t err;
    u8 index = nvram_map[id].index;
    if(index == 0)
    {
        err = nvram_map[id].initf.simple(src);
    }
    else
    {
        err = nvram_map[id].initf.indexed(index-1, src);
    }
    return err;
}

//Additions for logical volume to physical unit translation

/** \brief A helper to read NVMEM by logical volume
\param data - a pointer to data to write
\param addr - nvmem address
\param length - data length
\param vol - logical volume
\return an error code
*/
ErrorCode_t nvmem_ReadVol(void *data, u32 addr, u32 length, u8_least vol) //logical 'volume'
{
    return fram_ReadExt(data, addr, length, nvmem_banks[vol][nvmem_GetPhysicalVol(vol)].volid);
}

/** \brief A helper to write NVMEM by logical volume
\param data - a pointer to data to write
\param addr - nvmem address
\param length - data length
\param vol - logical volume
\return an error code
*/
ErrorCode_t nvmem_WriteVol(const void *data, u32 addr, u32 length, u8_least vol) //logical 'volume'
{
    return fram_WriteExt(data, addr, length, nvmem_banks[vol][nvmem_GetPhysicalVol(vol)].volid);
}

/* This line marks the end of the source */
