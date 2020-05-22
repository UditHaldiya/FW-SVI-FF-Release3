#include "STD_DEFS.H"

/*
** This DDL will build a complete DD containing all blocks and parameters 
** DD is stored by default as Release\000000\ffff\ffff.ddo
**
** Filename:	SIF_TEST.DDL
** Revision:	1.1
** Date:		2007-10-02
** Std. Lib:	3.0
** DISCLAIMER OF WARRANTIES
**
** THIS DOCUMENT IS PROVIDED ON AN "AS IS" BASIS AND MAY BE SUBJECT TO FUTURE
** ADDITIONS, MODIFICATIONS, OR CORRECTIONS DEPENDING ON THE RESULTS OF FIELD
** TRIAL TESTING.  THE FIELDBUS FOUNDATION(TM) HEREBY DISCLAIMS ALL WARRANTIES
** OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING ANY WARRANTY OF MERCHANTABILITY
** OR FITNESS FOR A PARTICULAR PURPOSE, FOR THIS DOCUMENT.  IN NO EVENT WILL
** THE FIELDBUS FOUNDATION(TM) BE RESPONSIBLE FOR ANY LOSS OR DAMAGE ARISING
** OUT OF OR RESULTING FROM ANY DEFECT, ERROR OR OMISSION IN THIS DOCUMENT OR
** FROM ANYONE'S USE OF OR RELIANCE ON THIS DOCUMENT.
** DISCLAIMER OF WARRANTIES
**
** (c) Fieldbus Foundation(TM) (1994-2007)
*/

	
#define __FF_TEST_DD		0xFFFF
#define __FF_TEST_dev_rev	0xFF
#define __FF_TEST_dd_rev	0xFF

/*
***********************************************************************
Test DD
***********************************************************************
*/

MANUFACTURER 	  __FF, 
DEVICE_TYPE 	  __FF_TEST_DD, 
DEVICE_REVISION __FF_TEST_dev_rev, 
DD_REVISION 	  __FF_TEST_dd_rev

/*
***********************************************************************
IMPORT entire standard library
***********************************************************************
*/

IMPORT  MANUFACTURER 		__FF,
		DEVICE_TYPE 		    __STD_PARM,
		DEVICE_REVISION 	  __STD_PARM_rel_dev_rev,
		DD_REVISION 		    __STD_PARM_rel_dd_rev
{EVERYTHING;}  
	
IMPORT  MANUFACTURER 		__FF,
		DEVICE_TYPE 		    __SIF_PARM,
		DEVICE_REVISION 	  __SIF_PARM_rel_dev_rev,
		DD_REVISION 		    __SIF_PARM_rel_dd_rev
{EVERYTHING;}  

IMPORT  MANUFACTURER 		__FF,
		DEVICE_TYPE 		    __SIF_AI_BLOCK,
		DEVICE_REVISION   	__SIF_AI_BLOCK_rel_dev_rev,
		DD_REVISION 		    __SIF_AI_BLOCK_rel_dd_rev
{EVERYTHING;}

IMPORT  MANUFACTURER 		__FF,
		DEVICE_TYPE 		    __SIF_DO_BLOCK,
		DEVICE_REVISION 	  __SIF_DO_BLOCK_rel_dev_rev,
		DD_REVISION 		    __SIF_DO_BLOCK_rel_dd_rev
{EVERYTHING;}

IMPORT  MANUFACTURER 		__FF,
		DEVICE_TYPE 		    __SIF_RES_BLOCK,
		DEVICE_REVISION 	  __SIF_RES_BLOCK_rel_dev_rev,
		DD_REVISION 		    __SIF_RES_BLOCK_rel_dd_rev
{EVERYTHING;}

