/*
Copyright 2015 by Dresser, Inc., as an unpublished trade secret.  All rights reserved.
This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file vertran.c
    \brief Frame shell for embedded NVMEM layout translation

    CPU: Any

    OWNER: AK

    \ingroup nvram
*/
#include "mnwrap.h"
#include "nvram.h"
#include "crc.h"
#include "evertran.h"
#include "vertranpub.h"

/** \brief A helper to adjust layout number
\param src - a pointer to source layout info
\param dst - a pointer to destination layout info
\param dir - direction of increment (expected to be -1 or +1)
*/
void changeVersionId(const StartupVersionNumber_t *src, StartupVersionNumber_t *dst, s8_least dir)
{
    *dst = *src;
    if(dir > 0)
    {
        dst->VersionNumber++;
    }
    else if (dir < 0)
    {
        dst->VersionNumber--;
    }
    else
    {
        //leave alone
    }
    STRUCT_CLOSE(StartupVersionNumber_t, dst);
}

/** \brief A default dummy for a delay function
*/
static void dummy_func(void)
{
}

/*Obviously, doesn't work with forward translation - there is no-one to set
the struct in newly downloaded image with new vertran
*/
#if 0
/* It may be necessary to fix the NV image before or after translation
*/
typedef struct imgfix_t
{
    void (*srcfix)( void *src, u16_least srcVer);
    void (*dstfix)(void *src, u16_least dstVer);
    u16 CheckWord;
} imgfix_t;

static imgfix_t imgfix =
{
    .srcfix = NULL,
    .dstfix = NULL,
    .CheckWord = CRC_SEED
};

void nv_SetImgfix(void (*srcfix)( void *src, u16_least srcVer), void (*dstfix)(void *src, u16_least dstVer))
{
    MN_ENTER_CRITICAL();
        imgfix.srcfix = srcfix;
        imgfix.dstfix = dstfix;
        STRUCT_CLOSE(imgfix_t, &imgfix);
    MN_EXIT_CRITICAL();
}
#endif //0


/* \brief A table-based translation wrapper.
Presumes versions ranges are already checked.
Translates current image to a new image
\param xTable translation table
\param src[in][out] - a pointer to a pointer to a source buffer (may be destroyed)
\param dst[out] - a pointer to a pointer to a destination buffer
\param srcVer - source layout number
\param dstVer - destination layout number
\param func - a function to call periodically
\return error code
*/
ErrorCode_t vertran( void * const *src, void **dst, u16_least srcVer, u16_least dstVer, void (*func)(void))
{
    ErrorCode_t err = ERR_OK;
    u16_least i;
    if((src == NULL) || (dst == NULL))
    {
        return ERR_INVALID_PARAMETER;
    }

    void *pSrc = *src;
    void *pDst = *dst;
    void *pTemp;

    if(func ==NULL)
    {
        func = dummy_func; //regularize
    }

#if 0
    Struct_Test(imgfix_t, &imgfix);
    if(imgfix.srcfix != NULL)
    {
        imgfix.srcfix(pSrc, srcVer);
    }
#endif

    if (srcVer == dstVer)
    {
        //nothing to do except put pSrc to *dst below
    }
    else
    {
        if(srcVer < dstVer)
        {
            for(i=srcVer; i<dstVer; i++)
            {
                if(xTable[i].xup == NULL)
                {
                    err = ERR_NOT_SUPPORTED;
                }
                else
                {
                    changeVersionId(pSrc, pDst, 1);
                    err = xTable[i].xup(pSrc, pDst, func);
                }

                if(err != ERR_OK)
                {
                    break;
                }
                //swap source and destination buffers
                pTemp = pDst;
                pDst = pSrc;
                pSrc = pTemp;
            }
        }
        else //srcVer > dstVer
        {
            for(i=srcVer; i>dstVer; i--)
            {
                if(xTable[i].xdown == NULL)
                {
                    err = ERR_NOT_SUPPORTED;
                }
                else
                {
                    changeVersionId(pSrc, pDst, -1);
                    err = xTable[i].xdown(pDst, pSrc, func);
                }
                if(err != ERR_OK)
                {
                    break;
                }
                //swap source and destination buffers
                pTemp = pDst;
                pDst = pSrc;
                pSrc = pTemp;
            }
        }
    }
    *dst = pSrc; //because pSrc and pDst were just swapped or because there was nothing to do

#if 0
    Struct_Test(imgfix_t, &imgfix);
    if((err == ERR_OK) && (imgfix.dstfix != NULL))
    {
        imgfix.dstfix(pSrc, dstVer); //Note that pSrc is the correct pointer!
    }
#endif

    return err;
}
/* This line marks the end of the source */
