/*
Copyright 2016 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file mnreadhandler.c
    \brief A replacement of Softing read handler which honors Advanced param of TB.

    Based on original Softing version 2.42

    CPU: Any

    OWNER: AK
*/
#include <softing_base.h>
#include <fbif_dcl.h>
#include "mn_advanced.h"


//Here are the definitions for the structure and the global variable:

//lint +flb defined by Softing
typedef struct
  {
    USIGN16     index;
    USIGN8      subindex;
    USIGN8      subindex_offset;
    USIGN8      param_size;
    USIGN8 *    snd_buf;
    BOOL        copy_by_appl;
  }
    T_FBL_READ_IND;

typedef struct
{
  T_FBIF_BLOCK_INSTANCE     inst;
  USIGN8 *                  p_eep;
  USIGN8                    eep_id;
  USIGN16                   static_revision;
  USIGN16                   relative_index;
}
  T_FBS_BLOCK_LIST;

extern NO_INIT T_FBS_BLOCK_LIST                fbs_block_list[MAX_NO_OF_BLOCKS];
extern NO_INIT const T_FBIF_DICTIONARY *       p_fbs_fbif_dict;

#define _IS_RESB(p) (p->block_type == RES_BLK)
#define _IS_FBLK(p) (p->block_type == FUNCT_BLK)

extern USIGN16 mnRead_handler(T_FBL_READ_IND *p_read_ind);

//lint -flb


static T_FBIF_BLOCK_INSTANCE * fbsrw_get_block
  (
    IN USIGN16    index
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function returns the address of the block description of which the 'index'
is part of.

Input:  index     Index of the object to be accessed

Return: address of the block description of which the 'index' is part of.
        or NULL if no block was found

----------------------------------------------------------------------------*/
{
LOCAL_VARIABLES
  USIGN8    i;
    //const T_FBIF_DICTIONARY *p_fbs_fbif_dict = &fbif_dictionary;
FUNCTION_BODY

  for (i = 0; i < p_fbs_fbif_dict->no_of_blocks; i++)
  {
    if (  (index >= p_fbs_fbif_dict->fbif_block_dir[i].start_index) &&
         (index < p_fbs_fbif_dict->fbif_block_dir[i].start_index +
                  p_fbs_fbif_dict->fbif_block_dir[i].no_of_param)  )
    {
      return (&fbs_block_list[i].inst);
    }
  }

  return (NULL);
}


FUNCTION PUBLIC USIGN16 mnRead_handler
  (
    IN T_FBL_READ_IND *   p_read_ind
  )

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

  This function is called by the FB shell when a block parameter is read.

  Return values:
  if (no error)  E_OK
  else           error code in fbap.h (E_FB_xxx) or FF-890
----------------------------------------------------------------------------*/
{
    T_FBIF_READ_DATA            fbif_read;

    USIGN16 result = E_OK;
    T_FBIF_BLOCK_INSTANCE *p_block_instance = fbsrw_get_block (p_read_ind->index);
#if 0
    if (p_block_instance == NULL)
    {
        ;//_FFBL_FATAL (XCP_FFBL_BLK_ACC,XCP_FFBL_READ_HANDLER,p_read_ind->index);
    }
#endif
    const T_FBIF_BLOCK_DESCR *p_block_desc = p_block_instance->p_block_desc;

    fbif_read.rel_idx   = p_read_ind->index - p_block_desc->start_index;
    fbif_read.subindex  = p_read_ind->subindex;

    p_read_ind->copy_by_appl = FALSE;

    const T_FBIF_PARAM_DESCR *par_descr_ptr = &p_block_desc->param_dir[fbif_read.rel_idx];
    if ((par_descr_ptr->flags & FB_PARAM_NOT_IN_FBIF) != 0) /* X flag */
    {
        /* The current value must be provided by the application -------------- */
        fbif_read.param_size     = p_read_ind->param_size;
        fbif_read.dest           = p_read_ind->snd_buf;

        p_read_ind->copy_by_appl = TRUE;
    }
    else if ((par_descr_ptr->flags & FB_APPL_READ_PARAM) != 0) /* A flag */
    {
        /* The parameter may be updated by the application -------------------- */
        fbif_read.param_size = p_read_ind->param_size;
        fbif_read.dest       = (USIGN8 *)p_block_desc->p_block;
        fbif_read.dest      += par_descr_ptr->par_offset + p_read_ind->subindex_offset;
    }
    else
    {
        /* The current value is stored in the block interface ----------------- */
        fbif_read.param_size = 0;
        fbif_read.dest       = NULL;
    }

    if (fbif_read.param_size != 0)
    {
        if (_IS_RESB(p_block_instance->p_block_desc))
        {
            if (fbs_call_fdev_funct.a_of_read_hndl_RESB != NULL)
            {
                result = fbs_call_fdev_funct.a_of_read_hndl_RESB (p_block_instance,&fbif_read);
            }
        }
        else if (_IS_FBLK (p_block_instance->p_block_desc))
        {
            if (fbs_call_fdev_funct.a_of_read_hndl_FCTB != NULL)
            {
                result = fbs_call_fdev_funct.a_of_read_hndl_FCTB (p_block_instance,&fbif_read);
            }
        }
        else
        {
            //nothing - TB
        }
    }

    //Special treatment for TB FBO "Advanced" parameter
    bool_t skip = false;
    if(p_block_desc->p_block == &ptb_1)
    {
        if(!mnadv_JamPtbParam(p_block_instance, fbif_read.rel_idx, p_read_ind->snd_buf,
                              p_read_ind->subindex_offset, p_read_ind->param_size))
        {
            skip = true;
            result = E_OK;
        }
    }
    if( (result == E_OK) && !skip)
    {
        result = (*p_block_desc->a_of_read_hndl)(p_block_instance,&fbif_read);
    }

    return result;
}
/* This line marks the end of the source */
