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

FILE_NAME         hm_cfg.h



DESCRIPTION

=========================================================================== */

#ifndef HM_CFG_H_
#define HM_CFG_H_

/* HART communication settings */
#define PRIMARY                        /* This is a primary HART master */
#define HART_RETRY_LIMIT 2             /* HART master will try n times */
#define MAX_HART_TELEGRAMM_LEN          100 //54 // max. length of a hart telegram (in bytes)

#define RT1_PRIMARY                      33 //TBD if this is enough
#define RT1_SECONDARY                    41
#ifdef PRIMARY
#define RT1                              RT1_PRIMARY
#define MASTER_ADDR                      0x80U
#else
#define RT1                              RT1_SECONDARY
#define MASTER_ADDR                      0x00U
#endif

#define HM_HART_DEVICE_ADDRESS           0
#define HM_MAX_INIT_FAIL                 10

#endif /* HM_CFG_H_ */
