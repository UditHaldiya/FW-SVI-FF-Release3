#ifndef MN_FWDL_H_
#define MN_FWDL_H_

#include <base.h> //for types
#include <swdl_api.h> //for types

#define SET_BITD(a,n)  ( a[(n) / 8U] |= (0x80U >> ((n) & 7U)))
#define TST_BITD(a,n)  ((a[(n) / 8U]  & (0x80U >> ((n) & 7U))) != 0)

/*                       min   typ  max
16-bit programming time       52.5   70 us
page (2 KB) erase time    20         40 ms
*/

#if 0
typedef struct T_DOMAIN_HDR_API
{
     USIGN16 Header_Version_Number;
     USIGN16 Header_Size; //Softing doesn't provide it
     CHAR    Manufacturer_Id[6];
     CHAR    Device_Family[4];
     CHAR    Device_Type[4];
     USIGN8  Device_Revision;
     USIGN8  DD_Revision;
     CHAR    Software_Revision[8];
     CHAR    Software_Name[8];
     CHAR    Domain_Name[8];
} T_DOMAIN_HDR_API;
#endif

typedef struct private_header_t
{
    USIGN16 header_version;		// private header format: initial value 1
    USIGN16 header_length;		// private header length: initial value 36
    USIGN8  FF_fw_version[4];   //
    USIGN8  APP_fw_version[4];	//
    USIGN32 spare[5];			// room to grow
} private_header_t;

typedef struct image_header_t
{
    USIGN16 header_version;		// image header format: initial value 1
    USIGN16 header_length;		// image header length: initial value 24
    USIGN32 offset_to_next_ih;	// relative offset to next image in .ffd …
					            //    file relative to end of image header
    USIGN32 image_address;	 	// used if relocation_size == 0
    USIGN32 image_size;
    USIGN16 image_CRC;               	//
    USIGN16 relocation_size;        	// 0 == no relocation
    USIGN16 relocation_CRC;
    USIGN8  destination_cpu_flag;   	// 0 == FF,   1 == APP
    USIGN8  compression_method;     	// 0 == NONE; 1 = modifed LZ77, ...
} image_header_t;

/*
Notes:
	1. there is one domain header and 1 private header per file.
    2. the image header immediately follows the private header
    3. the relocation table, if any, immediately follows the image header
	4. the firmware image immediately follows the relocation table.
	5. the image address is the load (vector) address if there is no relocation
       table; otherwise ignored
	6. in the relocation case, the load address comes from the partition manager.
	7  items 2 throgh 6 may occur for the other CPU
*/

extern bool_t vh_CheckDomainHeader(T_DOMAIN_HDR_API vH);
extern bool_t vh_CheckPrivateHeader(private_header_t pH);
extern T_DOMAIN_HDR_API *vh_GetDomainHeader(void);

//Hardening of FW activation
typedef struct FWDLInfo_t
{
	void *phInfo; //This is an absolute address manufactured by Ernie,
                  //as opposed to linker-generated pointer.
                  //So, it's OK to store it in NVMEM
	u16 CheckWord;
} FWDLInfo_t;
extern const FWDLInfo_t *fwdl_GetDLInfo(FWDLInfo_t *dst);
extern ErrorCode_t fwdl_SetDLInfo(const FWDLInfo_t *src);
UNTYPEACC(fwdl_SetDLInfo, fwdl_GetDLInfo);

#endif // MN_FWDL_H_

// end of source
