/*****************************************************************************
*                                                                            *
*                     SOFTING Industrial Automation GmbH                     *
*                          Richard-Reitzner-Allee 6                          *
*                                D-85540 Haar                                *
*                        Phone: ++49-89-4 56 56-0                            *
*                          Fax: ++49-89-4 56 56-3 99                         *
*                                                                            *
*                            SOFTING CONFIDENTIAL                            *
*                                                                            *
*                     Copyright (C) SOFTING IA GmbH 2012                     *
*                             All Rights Reserved                            *
*                                                                            *
* NOTICE: All information contained herein is, and remains the property of   *
*   SOFTING Industrial Automation GmbH and its suppliers, if any. The intel- *
*   lectual and technical concepts contained herein are proprietary to       *
*   SOFTING Industrial Automation GmbH and its suppliers and may be covered  *
*   by German and Foreign Patents, patents in process, and are protected by  *
*   trade secret or copyright law. Dissemination of this information or      *
*   reproduction of this material is strictly forbidden unless prior         *
*   written permission is obtained from SOFTING Industrial Automation GmbH.  *
******************************************************************************
******************************************************************************
*                                                                            *
* PROJECT_NAME             Softing FF/PA FD 2.42                             *
*                                                                            *
* VERSION                  FF - 2.42                                         *
*                          PA - 2.42 (beta)                                  *
*                                                                            *
* DATE                     16. April 2012                                    *
*                                                                            *
*****************************************************************************/


/* ===========================================================================

FILE_NAME          eep_if.h



FUNCTIONAL_MODULE_DESCRIPTION

  This module contains definitions and function prototypes for the
  higher level access of the eeprom.

=========================================================================== */
#ifndef EEP_IF_H_
#define EEP_IF_H_

#include <keywords.h>   /* keyword defines */
#include <base.h>
#include "errcodes.h"
#include "nvram.h"

/* ------------------------------------------------------------------------ */
/* --- Block IDs to access the EEPROM data blocks ------------------------- */
/* ------------------------------------------------------------------------ */

#define EEP_APPL_BLK1           1
#define EEP_APPL_BLK2           2
#define EEP_APPL_BLK3           3
#define EEP_APPL_BLK4           4       /* Reserved for FF block instantiation              */

#define EEP_PROT_BLK1           5       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK2           6       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK3           7       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK4           8       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK5           9       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK6          10       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK7          11       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK8          12       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK9          13       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK10         14       /* DO NOT CHANGE!! Referred by protocol software    */
#define EEP_PROT_BLK11         15       /* DO NOT CHANGE!! Referred by protocol software    */

//From Markus - disclosure of blocks used in "protocol software"
#define FBS_BLK_FB_LINK_CFG           EEP_PROT_BLK1
#define FBS_BLK_TREND_CFG             EEP_PROT_BLK2
#define FBS_BLK_MVC_CFG               EEP_PROT_BLK3

#define FBS_BLK_STATE_CFG             EEP_APPL_BLK4      /* block instantiation */
#define FDC_BLK_BASE_CFG              EEP_PROT_BLK4
#define FDC_BLK_DLL_BASE_CFG          EEP_PROT_BLK5

#define FDC_BLK_VCR_CFG               EEP_PROT_BLK6
#define FDC_BLK_SM_CFG                EEP_PROT_BLK7
#define FDC_BLK_FB_START_CFG          EEP_PROT_BLK8

#define FDC_BLK_DLL_LM_INFO_CFG       EEP_PROT_BLK9
#define FDC_BLK_DLL_LM_DATA_CFG       EEP_PROT_BLK10
#define FDC_BLK_LAS_CFG               EEP_PROT_BLK11

#define SWDL_BLK_DWNLD_CFG            EEP_DWNLD_BLK1 /* firmware download via fieldbus*/
// --

#define EEP_FBL_BLK1           16
#define EEP_FBL_BLK2           17
#define EEP_FBL_BLK3           18
#define EEP_FBL_BLK4           19
#define EEP_FBL_BLK5           20
#define EEP_FBL_BLK6           21
#define EEP_FBL_BLK7           22
#define EEP_FBL_BLK8           23
#define EEP_FBL_BLK9           24
#define EEP_FBL_BLK10          25
#define EEP_FBL_BLK11          26
#define EEP_FBL_BLK12          27
#define EEP_FBL_BLK13          28
#define EEP_FBL_BLK14          29
#define EEP_FBL_BLK15          30
#define EEP_FBL_BLK16          31
#define EEP_FBL_BLK17          32
#define EEP_FBL_BLK18          33
#define EEP_FBL_BLK19          34
#define EEP_FBL_BLK20          35
#define EEP_FBL_BLK21          36
#define EEP_FBL_BLK22          37
#define EEP_FBL_BLK23          38
#define EEP_FBL_BLK24          39
#define EEP_FBL_BLK25          40
#define EEP_FBL_BLK26          41
#define EEP_FBL_BLK27          42
#define EEP_FBL_BLK28          43
#define EEP_FBL_BLK29          44
#define EEP_FBL_BLK30          45
#define EEP_FBL_BLK31          46
#define EEP_FBL_BLK32          47

#define EEP_NV_BLK1            48
#define EEP_NV_BLK2            49
#define EEP_NV_BLK3            50
#define EEP_NV_BLK4            51       /* IDs must not exceed EEP_NBR_OF_BLOCKS - 1        */

#define EEP_DWNLD_BLK1         52

#define EEP_NBR_OF_BLOCKS      53       /* May be adjusted, if needed                       */


#define NV_EEP_BLK             EEP_NV_BLK1


#ifdef USE_NV_DATA_DOUBLE_BUFFER

#define MAX_NV_DATA_BLOCKS     2
#define NV_EXTRA_EEP_BLK       EEP_NV_BLK3

#else

#define MAX_NV_DATA_BLOCKS     1
#define NV_EXTRA_EEP_BLK       EEP_NV_BLK2

#endif

#define EXTRA_NV_ADJUST        sizeof(T_CHKSUM)      /* Used to calculate the address of the checksum */

LOCAL_DEFINES

EXPORT_TYPEDEFS

/* EEP function return values */
typedef enum _T_EEP_RESULT
{
    EEP_OK                  = 0,
    EEP_NOT_AVAIL           = 1,
    EEP_NOT_EXIST,
    EEP_MEM_INSUFF,
    EEP_PARAM_ERR,
    EEP_READ_ERR,
    EEP_PRG_ERR,
    EEP_CS_ERR,
    EEP_INCONSISTENT,
    EEP_INVALID_SERVICE     = 0x20,
    EEP_IN_CHANGE           = 0xF0
} T_EEP_RESULT;

typedef  USIGN16 (FAR_C * EEP_INI_FCT)(USIGN8 FAR_D *, T_EEP_RESULT);

typedef enum
{
    NO_INI,                             /* No initialisation required               */
    DATA_INI,                           /* memcopy from data area                   */
    FCT_INI                             /* call initialsation function              */
} T_EEP_INI_TYPE;

typedef union
{
    void FAR_D *        ptr_data;       /* pointer to initialisation data block     */
    EEP_INI_FCT         ptr_fct;        /* pointer to initialisation function       */
} T_EEP_INI_PTR;

/* offset and length of an EEPROM block */
typedef struct T_EEP_BLOCK_DSC
{
    USIGN8              block_id;       /* block id                                 */
    USIGN8              auto_write_length;  /* size if auto-store data              */
    USIGN16             block_size;     /* size of block                            */
}
T_EEP_BLOCK_DSC;

typedef USIGN16         T_CHKSUM;       /* type of the checksum             */

FUNCTION GLOBAL T_EEP_RESULT eep_provide_block
(
    IN  USIGN8      block_id,           /* ID of block                      */
    IN  USIGN16     block_len,          /* size of block                    */
    OUT VOID * *    p_ram_image         /* pointer to data image            */
)
/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Checks existence / consistency of a block and provides a pointer to the block
start address, if successful, NULL in case of error.

RETURN_VALUE
    EEP_OK              => no error, '*p_ram_image' points to start of block
    EEP_NOT_EXIST       => block with ID 'block_id' does not exist
    EEP_INCONSISTENT    => size of block does not agree with 'block_len'
    EEP_CS_ERR          => checksum of block invalid -> data probably corrupt
    EEP_READ_ERR        => EEPROM could not be read
----------------------------------------------------------------------------*/
;



FUNCTION GLOBAL T_EEP_RESULT eep_config_change
(
    IN USIGN8               no_of_eep_block_dsc, /* number of descriptors       */
    IN T_EEP_BLOCK_DSC *    p_eep_block_dsc      /* pointer to descriptor array */
)
/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
Inserts 'no_of_eep_block_dsc' block descriptions into the global descriptor
structure. If descriptions for certain block IDs are already existing, they
are overwritten.

possible return values:
    EEP_OK              => completed successfully
    EEP_PARAM_ERR       => block ID(s) exceed limit
------------------------------------------------------------------------------*/
;


FUNCTION GLOBAL T_EEP_RESULT eep_start_write
(
    IN  USIGN8   block_id               /* ID of block                       */
)
/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION
Prepares a block for write operations.

RETURN_VALUE
    EEP_OK          => no error occured
    EEP_PARAM_ERR   => wrong parameter
    EEP_IN_CHANGE   => EEP configuration not consistent temporarily
---------------------------------------------------------------------------- */
;



/* mode value for eep_write (), eep_restore () */
#define EEP_WAIT          0x01          /* wait until writing is finished    */

FUNCTION GLOBAL T_EEP_RESULT eep_write
(
    IN  USIGN8   block_id,              /* ID of block                       */
    IN  USIGN16  offset,                /* data offset inside the block      */
    IN  USIGN16  length,                /* length of data in bytes           */
    IN  USIGN8   mode                   /* selected write mode               */
)
/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

Writes data to the RAM image and, if needed, to the EEPROM. The only valid
value for the 'mode' parameter is :
  EEP_WAIT          the function returns after the final write cycle is
                    completed in the EEPROM device
If 'offset' == 0 and 'length' == 0 the whole block is written.

RETURN_VALUE
    EEP_OK          => no error occured
    EEP_PARAM_ERR   => wrong parameter
    EEP_PRG_ERR     => error while programming EEPROM
    EEP_IN_CHANGE   => EEP configuration not consistent temporarily
----------------------------------------------------------------------------*/
;


//Direct FB/RB/TB interface
extern T_EEP_RESULT eep_ReadFB(u8 fb_id, void *dst_static, u16 len_static, void *dst_nv, u16 len_nv);
extern T_EEP_RESULT eep_SaveFB(u8 fb_id,
                               const void *src_static, u16 offs_static, u16 len_static,
                               const void *src_nv, u16 offs_nv, u16 len_nv);

//extern void eep_put(u8_least   block_id);          /* ID of block                          */

extern T_EEP_RESULT eep_WriteFB2File(u8 fb_id,
                              u8 logf_static, u16 len_static,
                              u8 logf_nv, u16 len_nv);
extern T_EEP_RESULT eep_RestoreFile2FB(u8 fb_id,
                        u8 logf_static, u16 offs_static, u16 len_static,
                        size_t st_rev_offset, u16 st_rev,
                        u8 logf_nv, u16 offs_nv, u16 len_nv);

//Shim interface
typedef struct eepmap_t
{
    nvramId_t nvid;
    void *buffer;
} eepmap_t;
extern const eepmap_t eepmap[];
extern const u8 eepmap_size;

#endif /* EEP_IF_H_ */

