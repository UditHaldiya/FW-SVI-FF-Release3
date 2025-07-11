#ifndef __ICCARM__
 #include <windows.h>
 #include <stdio.h>
#endif
#include <string.h>
#if (defined SW_DOWNLOAD) || (defined _lint)
 #include "base.h"
 #include "base_cfg.h"
 #include "keywords.h"
 #include "swdl_api.h"
 #include <rtos.h>
#endif
//#include <softing_base.h>
#include "crc.h"
#include "mn_comp.h"
#include "mnhart2ff.h"
#include "mn_fwdl.h"
#include "mnflashff.h"
#include "ffp_hmac.h"
#include "nvffext.h"
#include "process.h"
#include "watchdog.h"
#include "shaseed.h"
#include <hw_if.h>
#include <appl_svi.h>
#include <hm_cfg.h>

#include "appl_ptb.h"
#include "hmsndrcv5.h"
#include "bufferhandler.h"
#include "facdefaults.h"

#include "nvutils.h"
#include "vertranpub.h"
#include <hw_svi_swdl_if.h>
#include "mnassert.h"
#if 0
//Preserve for posterity
 static const BYTE mykey[] =
 {
	"\xf9\xd1\x43\x4a\x44\x4b\x13\x60\x44\x4c\x14\x60\x53\x60\x54\x60"
	"\xd3\x68\x43\xf0\x20\x03\xd3\x60\xd3\x68\x43\xf0\x40\x03\xd3\x60"
	"\x4f\xf4\x30\x23\x01\xe0\x5b\x1e\x3a\x4a\x92\x68\x02\xf0\x01\x02"
	"\x01\x2a\x01\xd1\x00\x2b\xf6\xd1\x02\xf0\x15\x03\x5a\x1e\x92\x41"
 };
#endif

#include "faultpublic.h"
#include <fbif_dcl.h>

/*lint -esym(457, FwMutex)
because it is embOS API
*/
static OS_RSEMA FwMutex;

//lint -sem(rsrc_Initialize, no_thread)
/** \brief Allocate the FRAM mutex
*/
void fwdl_Init(void)
{
    OS_CREATERSEMA(&FwMutex);
}

/**
  \brief  This function acquires the Masoneilan FRAM guardian mutex.
*/
void fwdl_AcquireMutex(void)
{
    if((u8_least)OS_Request(&FwMutex) == 0) //return value 1: Resource was available, now in use by calling task; 0: Resource was not available.
    {
        //Mutex not available
        (void)OS_Use(&FwMutex); //wait; returned value larger than 1 means the resource was already locked by the calling task
    }
} //lint !e456 embOS mutex model uses counting resource semaphore; implementation is per manual

void fwdl_ReleaseMutex(void)
{
    OS_Unuse(&FwMutex);
}

static FFInfo_t allvers[4];
//extern u8  smdls_dwnld_hdr[];           // kludge

// flags passed to WriteToFlash()
#define NE  4u          // do not erase (driver knows it is blank)
#define ER  0u          // erase when crossing page boundary
#define NU	0u			// flash write no CRC or  address update
#define UP	2u			// flash write do CRC and address update
#define LCL 0u			// flash write to local  (FF)  flash even if updating APP
#define REM 1u			// flash write to remote (APP) flash when    updating APP
#define LAST_WRITE 8u   // indicator to APP of the last write

#define WD_SZ	sizeof(u32)
#define HW_SZ	sizeof(u16)

#define IMG_BUF_SZ		MAX_PROG_DATA   	// size of an intermediate RAM buffer for firmware image
											// relocation is applied in this buffer
CONST_ASSERT((IMG_BUF_SZ % 4) == 0);		// must be a multiple of 4
CONST_ASSERT((IMG_BUF_SZ + DATA_OFFSET) <= MAX_HART_TELEGRAMM_LEN);

typedef enum {IDLE, LOAD_IH,   LOAD_PH, LOAD_RELOC, LOAD_FW, CHK_SIG} DL_STATE;

#define NO_BYTES_TO_HOLD	8				// number of vector bytes to defer writing
                                            // 2 wds - stack pointer and reset vect address

CONST_ASSERT((NO_BYTES_TO_HOLD % 4) == 0);

#define ALIGN(x, y)			(((x) + ((y) - 1)) & ~((y) - 1))


static	u32					byteCount,          // relative to start of private header
							bufIx;              // indiex into flash hold buffer
static	DL_STATE			dlState = IDLE;

// pH and iH are arrays to make Lint happy
static  private_header_t    pH[1];
static	image_header_t		iH[1];              // the current image header
static	u32					relocationAmount;   // amount to add when fixing up the image
static	u8					*fwCurrentAddress,  // absolute address at which to write next flash image byte(s)
							*fwBaseAddress;     // absolute address of image base (vector table)

// variables pertaining to current image
static u8		            cpuDest,            // 0 == FF, 1 == APP
                            *relocTable;        // an address near the top of the inactive FF bank
static bool_t	            compressed,         // true if relocation table and image are compressed
				            reloc;              // true if image needs to be relocated
static u32                  imageCt;
//Get away from overloading imageCt
static u8 num_images_left;
static u8 num_images;
static u32 num_bytes_in_image;
static u32                  fwWds[IMG_BUF_SZ / sizeof(u32)];    // IMG_BUF_SZ is multiple of 4

CONST_ASSERT(sizeof(fwWds) >= SIGNATURE_SZ);     // fwWds is temporarily reused for 32-byte signature

// structure for Download Recovery sync
typedef struct sync_t
{
	u32 inbytes;			// offset in bytes into the DL file
	u32 outbytes;			// offset in bytes into the FW image
	u16 fwCRC,				// CRC of relocated firmware image  planted at end
                            //  of fw image in target flash
		dlCRC;				// CRC of downloaded firmware image (must match
                            //    iH.image_CRC)
} sync_t;

static sync_t ce;           // RAM copy (for DL Recovery this will be updated to
                            // flash ~ every 16 Kb

typedef struct pstate_t
{
    PARTN_STATE  st[2];
} pstate_t;

// number of elements of sync_t array that will fit in a flash sector
//#define ENTRIES ((SECT_SIZE - NO_BYTES_TO_HOLD - (8 * sizeof(u16))) / sizeof(sync_t))

// download state info kept in last sector of inactive FF CPU bank
typedef struct keepme_t
{
	pstate_t	state[8];                       // state of each partition
	sync_t	    entry[32];                      // not yet maintained - for DL Recovery
	u8		    firstBytes[NO_BYTES_TO_HOLD];   // first vector bytes for the firmware ...
                                                //  held until the partition CRC is ...
                                                //  validated
} keepme_t;
static keepme_t *phInfo = NULL;

CONST_ASSERT(sizeof(keepme_t) <= SECT_SIZE);

static void DownloadPrepare(DL_STATE state)
{
	byteCount       = 0;
    num_bytes_in_image = 0;
	bufIx           = 0;
	reloc           = false;
	compressed		= false;
	dlState         = state;
	ce.outbytes     = 0;
}

static void CloseFlashPartition(u8_least flags);

static void CloseAllFlash(void)
{
    CloseFlashPartition(LCL);
    CloseFlashPartition(REM);
}

static USIGN8 last_result; //! error interface between process and segment receiver
static volatile size_t write_head; //! advanced by incoming segments
static volatile size_t read_head; //! advanced by segment processing
static u8 dlmode;
void start_prepare_swdl  ( VOID  )
{
    CloseAllFlash();
    process_ForceProcessCommand(PROC_FWDL);
    last_result = E_OK;
    read_head = 0;
    write_head = 0;
    dlmode = facdef_GetState(NULL)->fwdl_mode; //cache to ignore any changes while download is running
    (void)fwdl_SetDLInfo(NULL);
}

void fwdl_reset_fddom(void)
{
    CloseAllFlash();
    process_CancelProcessEx(PROC_FWDL, ProcSourceDefault);
}
FUNCTION GLOBAL USIGN8 appl_check_fd_dom_hdr  ( IN const T_DOMAIN_HDR_API * p_dwnld_dom_hdr )
{
	UNUSED_OK(p_dwnld_dom_hdr);
    DownloadPrepare(LOAD_PH);
    const void *mykey = util_GetSeedKey();
    HMAC_HashKeyOnly(mykey, BLOCKSZ, IPAD);

    //kludge because Softing doesn't pass the entire header
   	sha256_update((const u8*)"\x00\x01\x00\x2c", 4);
	sha256_update((const u8*)p_dwnld_dom_hdr, 32);
	sha256_update((const u8*)"FD-DOM  ", 8);

	ce.inbytes      = 0;
	return E_OK;
}

/** \brief
*/
static u32 SetActive(u8_least otherCPU, PARTN_STATE st)
{
    u32 ret = 0U;

    if ((st == ACTIVATE0) || (st == ACTIVATE1))
    {
        u32 partn = (st == ACTIVATE1) ? 1 : 0;

    	if ((otherCPU & REM) == REM)
	    {
            ret = fwdk_WriteAppCPU32(SET_PARTN, partn); //on success, flip partition
	    }
    	else
	    {
		    ret = flash_SetPartition(partn);
    	}
    }
    // delay to allow update of NVRAM before reset
    //OS_Delay(200);

    return ret;
}

typedef struct UnActivate_t
{
    s8_least app_bank;
    PARTN_STATE st[2];
    u16 CheckWord;
} UnActivate_t; //! Type to hold new FW activation undo infomation

static UnActivate_t UnActivate =
{
    .app_bank = -1, //not captured yet
    .st =
    {
        [LCL] = NOTACTIVE,
        [REM] = NOTACTIVE,
    },
    .CheckWord = (u16)(CRC_SEED+0xFFFEU), //make it valid on init: FFFE is the sum of 32-bit "-1"
};

/** \brief This function must be called periodically (unfortunately).

It monitors failure of APP to initialize with newly translated NVMEM.
(See description and code for FAULT_REVERTFW_NV in APP.)
If the failure is detected, it is presumably a bug in NVMEM translation
and instead of bricking the device, we revert to previous firmware.

The argument is that the device may still be upgradable if parameters are set
within (new) range befor activating.
This implementation has a small vulnerability of device losing power or otherwise
reset when APP reverted the flash bank and FFP did not.
This can be remedied with NVMEM storage etc. like in normal activation
but it's unclear if there are merits to it (double failure)
*/
void fwdl_UndoMonitor(void)
{
    Struct_Test(UnActivate_t, &UnActivate);

    if(mn_IsAppFault(&ptb_1, FAULT_REVERTFW_NV))
    {
        s8_least app_bank = UnActivate.app_bank;
        if(app_bank < 0)
        {
            //Time permitting, commonize with switch_flash_banks()
            app_bank = fwdk_GetAppBank();
            if(app_bank < 0)
            {
                //Error; will try next time
            }
            else
            {
                UnActivate_t undo =
                {
                    .app_bank = app_bank,
                    .st =
                    {
                        [REM] = (app_bank == 0) ? ACTIVATE1 : ACTIVATE0, //APP
                        [LCL] = (flash_GetRunningPartitionID() == 0) ? ACTIVATE1 : ACTIVATE0, //FFP
                    },
                    .CheckWord = 0U, //don't care
                };
                STRUCT_GET(&undo, &UnActivate);

            }
        }
    }
    u32 ret = 0U;
    if(UnActivate.st[REM] != NOTACTIVE)
    {
        ret = SetActive(REM, UnActivate.st[REM]);
        if(ret == 0U)
        {
            storeMemberInt(&UnActivate, st[REM], NOTACTIVE);
        }
    }
    if(UnActivate.st[REM] == NOTACTIVE) //APP is done with
    {
        if(UnActivate.st[LCL] != NOTACTIVE)
        {
            ret = SetActive(LCL, UnActivate.st[LCL]);
            if(ret == 0U)
            {
                Reset_CPU(); //Make it simple, in a single operation
            }
        }
    }
}

/** \brief Get the base (vector table) address of the partition.  The address
    is returned by a call to the flash driver.

    \param otherCPU - 0 if FF CPU, 1 if APP CPU
*/
static u32 GetPartitonBaseAddress(bool_t otherCPU)
{
	if (otherCPU)
	{
        return fwdk_WriteAppCPU32(PARTN_BASE, 0);   // get partiton addr from app CPU
	}
	return flash_GetPartitionBaseAddress(0u);
}

/** \brief
*/
static void OpenFlashPartition(u8_least flags)
{
	if ((flags & REM) == REM)
	{
        // deferred for (;;) {}
	}
    (void)flash_OpenPartition(CRC_SEED);      // need to open local regardless
}

/** \brief
*/
static void CloseFlashPartition(u8_least flags)
{
    if ((flags & REM) == REM)
	{
        (void)fwdk_WriteAppCPU32(CLOSE_PARTN, 0u);
	}
    (void)flash_ClosePartition(0u);     // need to close local regardless
}


/** \brief
    \return - range-separated hi/lo halfwords:
    0/(partial CRC) if OK; otherwise error 0x8000|(BSY | WRPRTERR | PGERR)/0
*/
static u32 WriteToFlash(const void *dat, void *adr, u32 noWds, u8_least flags)
{
	if ((flags & UP) == UP)		// want to compute the CRC and update the flash address?
	{
		fwCurrentAddress += (noWds * HW_SZ);
		ce.fwCRC = Crc16((const u8*)dat, noWds * HW_SZ, ce.fwCRC);
	}

    u8_least flgs = (flags & NE) != 0 ? NO_ERASE : 0u;

    if ((flags & UP) != 0u)
    {
        flgs |= UPD_CRC;
    }
    if ((flags & LAST_WRITE) != 0u)
    {
        flgs |= FWDL_WRITE_INLINE;
    }
	if ((flags & REM) == REM)
	{
        return fwdk_WriteAppCPU(dat, HARDWARE(u32, adr), noWds * HW_SZ, flgs);
	}
	else
	{
        return flash_ProgramBlock(dat, adr,  noWds * HW_SZ, flgs);
	}
}

/** \brief
*/
static u8 LoadPrivateHeader(u8 kh)
{
	u8 *ph = HARDWARE(u8*, &pH[0]);

	ph[byteCount++] = kh;
    num_bytes_in_image++;
	if (byteCount == sizeof(pH[0]))
	{
        if ((pH[0].header_version != 1) ||                          // image header format: initial value 1
            (pH[0].header_length  != sizeof(private_header_t)))		// image header length: initial value 36
        {
            return E_SWDL_OTHER;
        }
        // number of CPU images in .ffd
        imageCt = ((pH[0].spare[0] >> 1) & 1u) + (pH[0].spare[0] & 1u);
        num_images = (u8)imageCt;
        num_images_left = num_images;
		DownloadPrepare(LOAD_IH);
	}
	return E_OK;
}

/** \brief Record the state of the selected partition.  This maintains a state
    for each CPU in the flash at the top of the FF CPU.  Noite that opdating the
    staew erases the top segment of flash in the FF CPU.  This is OK because we
    do not change it during a download.

    \param state - one of the state enumerated in PARTN_STATE.
*/
static void SetPartitionState(PARTN_STATE state)
{
    MN_ASSERT(phInfo != NULL);
    pstate_t lstate = phInfo->state[0];

    UNUSED_OK(phInfo->entry[0]);       // future use
    lstate.st[cpuDest] = state;
    void *statewr = &lstate, *gstate = &phInfo->state[0];
	(void)WriteToFlash(statewr, gstate, sizeof(pstate_t) / HW_SZ, (NU | LCL | ER));
}

/** \brief Accumulate the image header one byte at a time.

    \param kh - a character to store in the header structure.
*/
static u8 LoadImageHeader(u8 kh)
{
	u8 *ih = HARDWARE(u8*, &iH[0]);
	u32 temp, relocTblsz;

	ih[byteCount++] = kh;
    num_bytes_in_image++;
	if (byteCount == sizeof(iH[0]))
	{
        if ((iH[0].header_version != 1) ||                          // image header format: initial value 1
            (iH[0].header_length  != sizeof(image_header_t)))		// image header length: initial value 24
        {
            return E_SWDL_OTHER;
        }

		ce.dlCRC   = CRC_SEED;
		compressed =  iH[0].compression_method   != 0;
//        cpuDest    = REM;
		cpuDest    = (iH[0].destination_cpu_flag != 0) ? REM : LCL;
		byteCount  = 0;
		if (iH[0].relocation_size != 0)
		{
			reloc   = true;
			dlState = LOAD_RELOC;
		}
		else
		{
			dlState = LOAD_FW;
		}
		relocTblsz       = ALIGN(iH[0].relocation_size, SECT_SIZE); // sector bytes for reloc table
		relocationAmount = GetPartitonBaseAddress((cpuDest & REM) == REM);

		fwBaseAddress    = HARDWARE(u8*, relocationAmount);
		temp             = GetPartitonBaseAddress(false);
		temp             = (temp & BANK_MASK) + (BANK_SIZE - SECT_SIZE) - relocTblsz;

		fwCurrentAddress = fwBaseAddress;
		relocTable       = HARDWARE(u8*, temp);
		phInfo           = HARDWARE(keepme_t*, (temp + relocTblsz));
        OpenFlashPartition(cpuDest);
        SetPartitionState(NOTACTIVE);

        /* The harm of fwdl_SetDLInfo here
        is that failed download and following reset may attempt to flip partitions.
        To avoid this, the setting is moved
        */
	}
	return E_OK;
}

/** \brief Load the relocation table into local flash memory - one byte at a time. Once
	we have received iH.relocation_size bytes, the CRC is checked.

	\return E_OK if everything is good; other wise E_SWDL_CHECKSUM_FAIL
*/
static u8 LoadRelocationTable(u8 kh)
{
	static	u16 word = 0;
			u8	rslt = E_OK;

	if ((byteCount & 1U) != 0)
	{
		word |= (kh << 8);
        void *relok = relocTable + byteCount - 1;
		(void)WriteToFlash(&word, relok, 1, (NU | LCL | ER));
	}
	else
	{
		word = kh;
	}
	byteCount++;
    num_bytes_in_image++;
	if (byteCount >= iH[0].relocation_size)
	{
		if (ce.dlCRC == iH[0].relocation_CRC)
		{
			ce.dlCRC  = CRC_SEED;		// prepare for firmware block
			ce.fwCRC  = CRC_SEED;		// prepare for firmware block
			dlState   = LOAD_FW;
			byteCount = 0;
		}
		else
		{
			rslt = E_SWDL_CHECKSUM_FAIL;
		}
	}
	return rslt;
}

/** \brief Process a byte of downloaded firmware image. Writes to flash are
    performed at IMG_BUF_SZ size intervals and at other, smaller intervals:
        1. First 8 bytes copied to reserved memory in FF CPU flash
        2. Blocks of IMG_BUF_SZ
        3. Whatever is accumulated when we reach 2 bytes (CRC size) from the end
        4. The last two bytes (CRC) after validation
        5, The first 8 byte previously saved

    \param kh - on byte of firmwware image data
	\return E_OK if everything is good; otherwise E_SWDL_CHECKSUM_FAIL
*/
static u8 FirmwareLoad(u8 kh)
{
    static  u32 fwCRC = (u16)0;

            u8  *fwBuffer = (u8*)(void*)fwWds;
            u16 *fwBf16   = (u16*)(void*)fwWds;
			u8 rslt = E_OK;

	fwBuffer[bufIx++] = kh;
	byteCount++;
    num_bytes_in_image++;

	if (reloc && ((bufIx & 3U) == 0))		    // time to check for relocation fixup?
	{
		u32 wofs = byteCount / WD_SZ;			// word offset in fw image
		if (TST_BITD(relocTable, wofs - 1))
		{
            fwWds[(bufIx / WD_SZ) - 1]  += relocationAmount;
		}
	}
	if (byteCount == NO_BYTES_TO_HOLD)			// got first 8 bytes?
	{
		// put in a temporary place in the FF flash
        MN_ASSERT(phInfo != NULL);
		fwCRC = WriteToFlash(fwBuffer, phInfo->firstBytes, bufIx / HW_SZ, (UP | LCL | NE));
        if (cpuDest == REM)
        {
		    // open APP CPU Partition here. Download Recovery will need different handling
            fwCRC = fwdk_WriteAppCPU32(OPEN_PARTN, ce.fwCRC);   // open APP partiton
        }
		bufIx    = 0;
	}
	if (byteCount >= iH[0].image_size)         // done?
	{
		if ((bufIx >= 2) && (ce.dlCRC == iH[0].image_CRC) && (fwCRC == ce.fwCRC))
		{
            fwBf16[(bufIx / HW_SZ) - 1] = ce.fwCRC;     // correct dlCRC

			fwCRC = WriteToFlash(fwBuffer,         fwCurrentAddress, bufIx            / HW_SZ, (NU | cpuDest | ER));
			(void)WriteToFlash(phInfo->firstBytes, fwBaseAddress,    NO_BYTES_TO_HOLD / HW_SZ, (NU | cpuDest | NE | LAST_WRITE));
            SetPartitionState((HARDWARE(u32, fwCurrentAddress) >= BANK2_BASE) ? ACTIVATE1 : ACTIVATE0);
            CloseFlashPartition(cpuDest);
        }
		else
		{
			rslt = E_SWDL_CHECKSUM_FAIL;
		}
        if (--imageCt != 0)
        {
		    DownloadPrepare(LOAD_IH);         // get ready for another image header, etc
            num_images_left--;
        }
        else
        {
        	sha256_final((u8*)fwWds);
            const void *mykey = util_GetSeedKey();
	        HMAC_HashKeyText(mykey, BLOCKSZ, OPAD, (u8*)fwWds, HASHSZ, (u8*)fwWds);
            dlState = CHK_SIG;
            imageCt = 0;
            /* Last image is in! Indicate we are ready
            */
            FWDLInfo_t info;
            (void)fwdl_GetDLInfo(&info);
            info.phInfo = phInfo;
            (void)fwdl_SetDLInfo(&info);
        }
	}
	if ((bufIx >= IMG_BUF_SZ) || (byteCount == (iH[0].image_size - 2)))
	{
		// buffer full or only two bytes (the CRC) left
        fwCRC = WriteToFlash(fwBuffer, fwCurrentAddress, bufIx / HW_SZ, (UP | cpuDest | ER));
		bufIx    = 0;
	}
	return rslt;
}

/** \brief the download state machine for the binary section of the file

	\param kh - a plaintext character that is part of a private header,
				image header, relocation table or the firmmware image.
*/
static u8 ProcessDownloadByte(u8 kh)
{
	u8	rslt;

	ce.dlCRC = Crc16(&kh, 1, ce.dlCRC);
    if (dlState != CHK_SIG)
    {
        sha256_update(&kh, 1);
    }

	switch (dlState)
	{
		case LOAD_PH:
			rslt = LoadPrivateHeader(kh);
			break;

		case LOAD_IH:
			rslt = LoadImageHeader(kh);
			break;

		case LOAD_RELOC:
			rslt = LoadRelocationTable(kh);
			break;

		case LOAD_FW:
			ce.outbytes++;          // for possible download recovery
			rslt = FirmwareLoad(kh);
			break;

		case CHK_SIG:
            {
                u8 *signature = (u8*)fwWds;
                rslt = E_OK;
                if ((imageCt > SIGNATURE_SZ) || (signature[imageCt] != kh))
                {
                    rslt = E_SWDL_OTHER;
                }
                imageCt++;
            }
			break;

		default:
			rslt = E_SWDL_OTHER;

	}
	return rslt;
}

/** \brief Synopsis is the same as for dwnld_handle_data
*/
//lint -e{818} p_segment could be const * - don't mess with Softing header files
static USIGN8 dwnld_handle_data_internal(IN USIGN8 segment_id, IN USIGN8 segment_len, IN USIGN8 *p_segment)
{
	u8 rslt = E_OK;

	while ((segment_len-- != 0u) && (rslt == E_OK))
	{
		ce.inbytes++;
		if (compressed)
		{
		    //rslt = DecompressChar(*p_segment++, ProcessDownloadByte);
		}
		else
		{
			rslt = ProcessDownloadByte(*p_segment++);
		}
	}
	if (segment_id == SWDL_LOAD_LAST_SEGM)
	{
        if (imageCt != SIGNATURE_SZ)
		{
			rslt = E_SWDL_OTHER;
		}
		dlState = IDLE;
	}
	return rslt;
}

#define SWDL_BUFSIZE 600 //to start with

/** \brief Push a downloaded segment onto the circular buffer.
\param src - a pointer to data received
\param datalen - data length
\return true if the data was buffered OK, false if not enough room
*/
static bool_t fwdl_BufferData(USIGN8 segment_id, USIGN8 segment_len, const USIGN8 *p_segment)
//(const u8 *src, size_t datalen)
{
    size_t whead = write_head;
    size_t rhead = read_head;
    void *p = buffer_GetXDiagnosticBuffer(DIAGBUF_DEFAULT);
    u8 *dst = p;
    dst[whead++] = segment_id;
    if(whead == SWDL_BUFSIZE)
    {
        whead = 0; //wraparound
    }
    if(whead == rhead)
    {
        //overflow
    }
    else
    {
        dst[whead++] = segment_len;
        if(whead == SWDL_BUFSIZE)
        {
            whead = 0; //wraparound
        }
        if(whead == rhead)
        {
            //overflow
        }
        else
        {
            for(u8_least i=0; i<segment_len; i++)
            {
                dst[whead++] = p_segment[i];
                if(whead == SWDL_BUFSIZE)
                {
                    whead = 0; //wraparound
                }
                if(whead == rhead)
                {
                    //overflow
                    break;
                }
            }
        }
    }

    bool_t ret;
    if(whead == rhead)
    {
        //Overflow occurred
        ret = false;
    }
    else
    {
        ret = true;
        write_head = whead; //register the written segment
    }
    return ret;
}

/** \brief Process all downloaded segments in the round buffer at once
*/
static procresult_t fwdl_ProcessBufferedData(void)
{
    size_t whead = write_head;
    size_t rhead = read_head;
    const void *p = buffer_GetDiagnosticBuffer();
    const u8 *src = p;
    u8 rslt = E_OK;
    procresult_t procresult = PROCRESULT_OK;

    while(rhead != whead)
    {
        //Not empty; assume valid content
        USIGN8 segment_id = src[rhead++];
        if(rhead == SWDL_BUFSIZE)
        {
            rhead = 0;
        }
        USIGN8 segment_len = src[rhead++];
        if(rhead == SWDL_BUFSIZE)
        {
            rhead = 0;
        }

        if (segment_id == SWDL_LOAD_LAST_SEGM)
        {
            //The last segment is processed inline; nothing to do here
        }
        else
        {
            while ((segment_len-- != 0u) && (rslt == E_OK))
            {
                ce.inbytes++;
                rslt = ProcessDownloadByte(src[rhead++]);
                if(rhead == SWDL_BUFSIZE)
                {
                    rhead = 0;
                }
            }
        }
        u8_least brk = process_WaitForTimeExt(1, ~CANCELPROC_INTERNALREQ);
        if(brk != 0)
        {
            procresult = PROCRESULT_CANCELED;
            break;
        }
    }
    if(last_result == E_OK)
    {
        last_result = rslt;
    }
    read_head = rhead;
    return procresult;
}

//-------------------- process wrapper -------------------

procresult_t fwdl_ProcEnvelope(s16 *procdetails)
{
    UNUSED_OK(procdetails);
    procresult_t procresult = PROCRESULT_OK;
    do
    {
        procresult = fwdl_ProcessBufferedData();

        //Very roughly, assume equal time for all images:
        u8_least complete = (
           /*completed images*/ 100*(num_images - num_images_left)
           /*current image*/   +100*num_bytes_in_image/(sizeof(iH[0]) + iH[0].relocation_size + iH[0].image_size)
                            )/num_images;
        process_SetProcessProgress((u8)complete);


        u8_least brk = process_WaitForTimeExt(1, ~CANCELPROC_INTERNALREQ);
        if(brk != 0)
        {
            procresult = PROCRESULT_CANCELED;
        }

    } while(procresult == PROCRESULT_OK);

    return PROCRESULT_OK;
}

/** \brief Process a block of firmware download data received by the FF stack
    This function receives data for the Private Header, Image Header, Relocation
    Table or the Firmware image.

    \param segment_id - one of: SWDL_LOAD_FIRST_SEGM, SWDL_LOAD_SEGM , SWDL_LOAD_LAST_SEGM
    \param segment length - up to 100 bytes of data
    \param p_segment - pointer to the downalod data
    \return - E_OK if everything is good; otherwise one of the E_SWDL_... values
*/
FUNCTION GLOBAL USIGN8 dwnld_handle_data(IN USIGN8 segment_id, IN USIGN8 segment_len, IN USIGN8 *p_segment)
{
    USIGN8 ret;
    //Original scheme
    if(process_GetProcId() != PROC_FWDL)
    {
        ret = E_SWDL_OTHER;
    }
    else
    {
	    if(dlmode == 1U)
	    {
	        //Original scheme
	        ret = dwnld_handle_data_internal(segment_id, segment_len, p_segment);
	    }
	    else
	    {
            ret = last_result;
	        if(ret == E_OK)
	        {
	            /* A safe but a slower way: Delay response until the buffer
	            is processed
	            */
	            size_t whead = write_head;
	            while(read_head != whead)
	            {
	                OS_Delay(5);
	            }
	            if(segment_id != SWDL_LOAD_LAST_SEGM)
	            {
	                bool_t e = fwdl_BufferData(segment_id, segment_len, p_segment);
	                if(!e)
	                {
	                    //no room - but gotta reply
	                    ret = E_SWDL_OTHER;
	                }
	            }
	            else
	            {
	                //execute this last segment inline
	                ret = dwnld_handle_data_internal(segment_id, segment_len, p_segment);
	            }
	        }
		}
    }

    //Terminate the handover process on error or or last segment
    if((ret != E_OK) || (segment_id == SWDL_LOAD_LAST_SEGM))
    {
        process_CancelProcessEx(PROC_FWDL, ProcSourceDefault);
    }
    return ret;
}

//----------------testpoints -------------------
#define RESET_APP_ACT 0xAA55U
#define RESET_FFP_ACT 0x55AAU
#define RESET_POST_ACT 0xAAAAU

//#define test_Reset(a) //Comment out to enable the test
#ifndef test_Reset
static u16 fwact_testpoint = 0;
static void test_Reset(u16 testpoint)
{
    if(testpoint == fwact_testpoint)
    {
        fwact_testpoint = 0; //for Lint
        Reset_CPU();
    }
}
#endif

/** \brief Switches flash partitions without translating NVMEM
    \param st[in][out] in - requested, out - resulting partition state
    \return TRUE on sccess, FALSE on failure
*/
BOOL flash_SwitchPartitions( PARTN_STATE st[2] )
{
    u32 ret = 1;
    BOOL result = TRUE; //prime for success
    //APP first
    if(st[REM] != NOTACTIVE)
    {
        ret = SetActive(REM, st[REM]);
        test_Reset(RESET_APP_ACT);
        if(ret == ~0U) //command interface failed
        {
            ret = SetActive(REM, st[REM]); //try again
        }
        ret &= ~PGERR; //ignore it

        //Check if the requested parition has activated
        if((ret & 0xFFFFU) == 0) //then local
        {
            ret = 0U;
            /* Give APP a generous 0.5 sec time to wake up from internal reset
            and check if partition has changed
            */
            s32 dly = 500; //ms
            do
            {
                wdog_WatchdogTrigger();
                OS_Delay(50);
                dly -=50;
            } while(dly > 0);

            s8_least bank = fwdk_GetAppBank();
            if(bank < 0) //error
            {
                //last-ditch attempt
                bank = fwdk_GetAppBank();
            }
            if(bank < 0) //error
            {
                ret = 1;
            }
            else
            {
                if(((bank==0) && st[REM]==ACTIVATE0) || ((bank==1) && st[REM]==ACTIVATE1))
                {
                    //OK
                }
                else
                {
                    ret = 1; //target bank didn't activate
                }
            }
        }
    }
    else
    {
        ret = 0U;
    }

    //Finally, we are ready to activate FFP; SetActive accounts for NOTACTIVE
    if(ret == 0)
    {
        test_Reset(RESET_FFP_ACT);
        ret = SetActive(LCL, st[LCL]);
        ret &= ~PGERR;
#if 0
        if(ret != 0U)
        {
            ret = SetActive(LCL, st[LCL]); //try again
            ret &= ~PGERR;
        }
#endif
    }

#if 0 //no need: reset will occur shortly
    //if(ret == 0)
    {
        //Reset APP in case it wants to time out on FFP
        Req_Reset_t *req = (void *)snd_buf;
        Rsp_Reset_t *rsp = (void *)rcv_buf;
        (void)hmsndrcv5_Reset(req, rsp);
    }
#endif
    if(ret != 0)
    {
        result = FALSE;
    }
    test_Reset(RESET_POST_ACT);
    return result;
} //lint !e818 must have common prototype

/** \brief Activate the downloaded firmware.  If either, or both, CPUs are
    updated, the preferred boot bank bit in each is toggled.  On return
    the stack will cause a reset.

NOTE that we don't need to wait for NVMEM writes to comlete (as previous
versions did), because translation is from RAM image.
The inherent weakness is that the image is loaded non-atomically, and the
writes may go on during activation.
This issue must be addressed by a coherent design of NVMEM objects which
must be independent of each other.

    \param st[in][out] in - requested, out - resulting partition state
    \return TRUE on sccess, FALSE on failure
*/
FUNCTION GLOBAL BOOL activate_fd_sw_internal  ( PARTN_STATE st[2] )
{
    BOOL result = TRUE; //prime for success

    /* EXPLANATION of the sequence
    We skip NVMEM translation (and activation altogether) for the (test only?)
    case where we activate the same partition.

    Now we need to activate new partitions, APP first. Since it is critical,
    we better retry on first failure.

    Finally, on success, we want to reset APP; Softing framework will reset FFP,
    and that will reset APP as well, so no action is needed here.
    */

    if(st[LCL] != NOTACTIVE)
    {
        u8_least new_partn_lcl = (st[LCL] == ACTIVATE1) ? 1 : 0;
        if(new_partn_lcl != flash_GetRunningPartitionID())
        {
            //Start FRAM translation
            process_ForceProcessCommand(PROC_CLONE_NVMEM);
        }
        else
        {
            st[LCL] = NOTACTIVE; //Came here by mistake due to unexpected reset?
        }
    }

    if(st[REM] != NOTACTIVE)
    {
        s8_least new_partn_rem = (st[REM] == ACTIVATE1) ? 1 : 0;
        s8_least bank = fwdk_GetAppBank();
        if(bank < 0) //error
        {
            //last-ditch attempt
            bank = fwdk_GetAppBank();
        }
        if(new_partn_rem != bank)
        {
            //Do FRAM translation in APP
            fferr_t fferr = fwdk_AdaptAppNvmem(); //On APP, it is bullet-proof so no harm yet
            if(fferr != E_OK)
            {
                //Translation failed
                result = FALSE;
                st[REM] = NOTACTIVE;
                st[LCL] = NOTACTIVE;
                process_CancelProcess();
            }
        }
        else
        {
            st[REM] = NOTACTIVE; //Came here by mistake due to unexpected reset?
        }
    }

    //Wait for FFP NVMEM translation to complete
    if(st[LCL] != NOTACTIVE)
    {
        //Wait for completion inline
        ProcId_t procid;
        do
        {
            OS_Delay(50);
            wdog_WatchdogTrigger();
            procid = process_GetProcId();
        } while(procid != PROC_NONE);
        /* While we CAN glean completion code from the diagnostic buffer,
        we don't. We gave it a shot, and in case of failure, FFP has a means
        of default initialization, so we go ahead with activation
        */
    }

    //Now we prepared to switch partitions; SetActive will skip NOTACTIVE
    if(result != FALSE)
    {
        //APP translated NVMEM OK
        result = flash_SwitchPartitions(st);
    }

    return result;
}

// ----------------------------------------------------------
static FWDLInfo_t FWDLInfo;
static const FWDLInfo_t FWDLInfo_Default =
{
    .phInfo = NULL,
    .CheckWord = CRC_SEED, //Don't care
};

const FWDLInfo_t *fwdl_GetDLInfo(FWDLInfo_t *dst)
{
    return STRUCT_TESTGET(&FWDLInfo, dst);
}
ErrorCode_t fwdl_SetDLInfo(const FWDLInfo_t *src)
{
    if(src == NULL)
    {
        src = &FWDLInfo_Default;
    }
    Struct_Copy(FWDLInfo_t, &FWDLInfo, src);
    ErrorCode_t err;
    for(s8_least i=0; i<3; i++) //REAL paranoia (because it is crirical)
    {
        err = ram2nvramAtomic(NVRAMID_FWDLInfo);
        if(err == ERR_OK)
        {
            break;
        }
    }
    MN_RT_ASSERT(err==ERR_OK);
    return err;
}

/** \brief Checks for any unfinished activation business on startup.
May only be called from SWDL_DOM_ACTIVATING case on startup.

[Migrated from appl_svi_swdl.c]
If everything checks out, returns E_OK. Otherwise, finishes and resets.
\return E_OK (or doesn't return)
*/
FUNCTION PUBLIC USIGN8 verify_activation(void)
{
    const FWDLInfo_t *dl = fwdl_GetDLInfo(NULL);
    USIGN8 ret = E_OK;
    if(dl->phInfo == NULL)
    {
        //OK, we are done
    }
    else
    {
        const keepme_t *phi = dl->phInfo;
        const PARTN_STATE *st = &phi->state[0].st[0];
        if((st[LCL] == NOTACTIVE) && (st[REM] == NOTACTIVE))
        {
            //OK, just clean up
            (void)fwdl_SetDLInfo(NULL);
        }
        else
        {
            BOOL result = activate_fd_sw();
            if(result != FALSE)
            {
                Reset_CPU(); //Will try again
            }
            else
            {
                ret = E_ERROR;
            }
        }
    }
    return ret;
}


// ----------------------------------------------------------

FUNCTION GLOBAL BOOL activate_fd_sw  ( VOID )
{
    /* We may come here after reset at any point since after complete download.
    So, we need to be VERY careful about the state we find
    */
    BOOL ret;
    phInfo = fwdl_GetDLInfo(NULL)->phInfo;
    if(phInfo == NULL)
    {
        //Nothing to do
        ret = TRUE;
    }
    else
    {
        pstate_t cur = phInfo->state[0];
        ret = activate_fd_sw_internal(cur.st);

        //The order of the following does matter, in case of interim reset
        //1. Invalidate NVMEM
        //if(ret != FALSE)
        {
            //Success or failure, we are done with activation
            (void)fwdl_SetDLInfo(NULL); //clear the download info
            /* NOTE that this happens AFTER FFP NVMEM translation,
            so unless FFP was NOT subject to activation, this operation
            has only a cleanup value
            */
        }
        //2. Invalidate flash record
        cur.st[LCL] = NOTACTIVE;
        cur.st[REM] = NOTACTIVE;
        OpenFlashPartition(LCL);
        (void)WriteToFlash(&cur, &phInfo->state[0], sizeof(pstate_t) / HW_SZ, (NU | LCL | ER));
        CloseFlashPartition(LCL);

    }
    /* EXPLANATION: If we come here with non-NULL FWDLInfo.phInfo, it is a
    pointer to last FW download info whose activation we want to complete.
    It must be cleared in prepare_download to avoid any confusion whatsoever.
    If we come here after reset at any point in the process, the worst
    thing that can happen is that we will try to activate partition/bank
    which has already been activated.
    The low-level activation code must be prepared for that.
    */

    return ret;
}


/** \brief Get a  pointer to the version info created below.

    \return - pointer to the FFInfo_t array[4]
*/
FFInfo_t *fwdl_GetVerInfo(void)
{
    return allvers;
}

/** \brief get the assembel the firmware version ofo for each of the four banks of flash
    Two in the FF CPU and two in the APP CPU.
*/
void fwdl_CreateVVerInfo(void)
{
    (void)GetFwInfo(allvers);
    fwdk_GetVerInfo(&allvers[2]);
}

// end of source
