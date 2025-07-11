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

FILE_NAME          osif_cfg.c



=========================================================================== */
#include "keywords.h"
#define  MODULE_ID      (COMP_OSIF + MOD_OSIFCFG)

INCLUDES
#include "base.h"

#include "osif.h"           /* OSIF interface declarations      */
#include "osif_cfg.h"       /* configuration data structures    */

#include "nvdimensions.h"

LOCAL_DEFINES
#define TASK_STACK(stack_area)  \
                .stacksize = sizeof (stack_area), .stack = stack_area

LOCAL_TYPEDEFS


LOCAL_DATA

#include "da_osstk.h"                            /* DATA SEGMENT DEFINITION */

#if defined (PROTOCOL_FF)

/*--------------------------------------------------------------------------*/
/* Tasks specific to FF-BFD (+ LM) communication layer                      */
/*--------------------------------------------------------------------------*/

#ifdef LINK_MASTER

/* LAS task --------------------------------------------------------------- */
#define LAS_EVENTS              OS_IF_EVENT_INDCON
#define LAS_MSGEVT              0
#define LAS_MSGNUM              0
#define LAS_STACK_SIZE          0x180 //0x100 was the original; seen overflow attempted MPU context extension
SOFTING_TASK_MEM STATIC NO_INIT uint8_t las_stack[LAS_STACK_SIZE];

#endif /* LINK_MASTER */

/* FDC task --------------------------------------------------------------- */
#if defined (MODBUS_MASTER)
#define FDC_EVENTS              OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + MODB_USR_EVENT + OS_IF_EVENT_RESUME
#define FDC_MSGEVT              OS_IF_EVENT_EEPROM + MODB_USR_EVENT
#elif defined (HART_MASTER)
#define FDC_EVENTS              (OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + OS_IF_EVENT_RESUME + HART_ACY_CMD_END_EVENT)
#define FDC_MSGEVT              (OS_IF_EVENT_EEPROM)
#else
#define FDC_EVENTS              OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + OS_IF_EVENT_RESUME
#define FDC_MSGEVT              OS_IF_EVENT_EEPROM
#endif
#define FDC_MSGNUM              (5)
#define FDC_STACK_SIZE          (0x300)
SOFTING_TASK_MEM STATIC NO_INIT uint8_t fdc_stack[FDC_STACK_SIZE];

/* SUBSCRIBER task ------------------------------------------------------- */
#define SBSCR_EVENTS            OS_IF_EVENT_INDCON
#define SBSCR_MSGEVT            0
#define SBSCR_MSGNUM            0
#define SBSCR_STACK_SIZE        0x200
SOFTING_TASK_MEM STATIC NO_INIT uint8_t sbscr_stack[SBSCR_STACK_SIZE];

#ifdef MVC_OBJECTS /* MVC task -------------------------------------------- */
#define MVC_EVENTS              OS_IF_EVENT_REQRES
#define MVC_MSGEVT              0
#define MVC_MSGNUM              0
#define MVC_STACK_SIZE          0x100
SOFTING_TASK_MEM STATIC NO_INIT uint8_t mvc_stack[MVC_STACK_SIZE];
#endif /* MVC_OBJECTS */


/* BGD50 task: timer triggered background actions ------------------------- */
#define BGD50_EVENTS          (OS_IF_EVENT_TIMER + OS_IF_EVENT_EEPROM)
#define BGD50_MSGEVT          (OS_IF_EVENT_EEPROM)
#define BGD50_MSGNUM          (2)
#define BGD50_STACK_SIZE      (0x280)
SOFTING_TASK_MEM STATIC NO_INIT uint8_t bgd50_stack[BGD50_STACK_SIZE];

/* BGD task: background actions ------------------------------------------- */
#define BGD_EVENTS               (OS_IF_EVENT_TIMER + OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM)
#define BGD_MSGEVT               (OS_IF_EVENT_EEPROM)
#define BGD_MSGNUM               (2)
#define BGD_STACK_SIZE           (0x800) //4x original size
STATIC NO_INIT uint8_t bgd_stack[BGD_STACK_SIZE];

#elif defined (PROTOCOL_PA) || defined (PROTOCOL_DP)

/*--------------------------------------------------------------------------*/
/* Tasks specific to PA-Slave communication layer                           */
/*--------------------------------------------------------------------------*/
/* DPS task:  ------------------------------------------------------------- */
#define DPS_EVENTS          OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON + OS_IF_EVENT_TIMER + OS_IF_EVENT_UPDATE_IO
#define DPS_MSGEVT          OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON
#define DPS_MSGNUM          30
#define DPS_STACK_SIZE      0x280
NO_INIT STATIC char dps_stack[DPS_STACK_SIZE];

/* DUSR task:  ------------------------------------------------------------ */
#define DUSR_EVENTS          OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON + OS_IF_EVENT_TIMER + OS_IF_EVENT_RESUME
#define DUSR_MSGEVT          OS_IF_EVENT_REQRES + OS_IF_EVENT_INDCON
#define DUSR_MSGNUM          10
#define DUSR_STACK_SIZE      0x100
NO_INIT STATIC char dusr_stack[DUSR_STACK_SIZE];

/* FBS task --------------------------------------------------------------- */
#if defined (MODBUS_MASTER)
#define FBS_EVENTS           OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + OS_IF_EVENT_TIMER + OS_IF_EVENT_RESUME
#define FBS_MSGEVT           OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + MODB_USR_EVENT
#elif defined (HART_MASTER)
#define FBS_EVENTS           OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + OS_IF_EVENT_TIMER + OS_IF_EVENT_RESUME + HART_ACY_CMD_END_EVENT
#define FBS_MSGEVT           OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM
#else
#define FBS_EVENTS           OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM + OS_IF_EVENT_TIMER + OS_IF_EVENT_RESUME
#define FBS_MSGEVT           OS_IF_EVENT_INDCON + OS_IF_EVENT_EEPROM
#endif
#define FBS_MSGNUM           10
#define FBS_STACK_SIZE       0x400
NO_INIT STATIC char fbs_stack[FBS_STACK_SIZE];

/* BGD task: background actions ------------------------------------------- */
#define BGD_EVENTS           OS_IF_EVENT_TIMER + OS_IF_EVENT_EEPROM
#define BGD_MSGEVT           OS_IF_EVENT_EEPROM
#define BGD_MSGNUM           2
#define BGD_STACK_SIZE       0x280
NO_INIT STATIC char bgd_stack[BGD_STACK_SIZE];

#else

#error Protocol type (PROTOCOL_FF or PROTOCOL_PA) not defined!

#endif /* Protocol type */

/*--------------------------------------------------------------------------*/
/* Other system tasks                                                       */
/*--------------------------------------------------------------------------*/
/* EEP task: now Process task, which can send HART messages to APP*/
#if 1 //now process task
#define EEP_EVENTS          (OS_IF_EVENT_EEPROM | OS_IF_EVENT_EEPROG | OS_IF_EVENT_TIMER | HART_ACY_CMD_END_EVENT)
#define EEP_MSGEVT          (OS_IF_EVENT_EEPROM)
#define EEP_MSGNUM          (5) //(15)  //3x the original
#define EEP_STACK_SIZE      (0x600) //3x the original
STATIC NO_INIT uint8_t eep_stack[EEP_STACK_SIZE];
#else
#define EEP_MSGNUM          0
#endif //0

/*--------------------------------------------------------------------------*/
/* Function Block execution task(s)                                         */
/*--------------------------------------------------------------------------*/
/* FB tasks: each Function Block runs as a separate task ------------------ */
#define FB_EVENTS           (OS_IF_EVENT_TIMER + OS_IF_EVENT_EEPROM)
#define FB_MSGEVT           (OS_IF_EVENT_EEPROM)
#define FB_MSGNUM           (5)
#define FB_STACK_SIZE       (0x300)
STATIC NO_INIT uint8_t fb1_stack[FB_STACK_SIZE];

/* @Dresser-Masoneilan project: Watchdog Task not required, because external Watchdog is used. */
#if 0
/* WD task ---------------------------------------------------------------- */
#define WD_EVENTS               OS_IF_EVENT_TIMER
#define WD_MSGEVT               0
#define WD_MSGNUM               0
#define WD_STACK_SIZE           0x100
NO_INIT STATIC char wd_stack[WD_STACK_SIZE];
#endif

/*@Dresser-Masoneilan project modified */
//#if defined (FBK2_HW) && defined (DOWNLOAD_DEVICE)
#if defined (SW_DOWNLOAD)
/*--------------------------------------------------------------------------*/
/* Software Download task(s)                                                */
/*--------------------------------------------------------------------------*/
#if 0
#define SWDL_EVENTS              OS_IF_EVENT_TIMER + OS_IF_EVENT_REQRES + OS_IF_EVENT_RESUME
#define SWDL_MSGEVT              0
#define SWDL_MSGNUM              5
#define SWDL_STACK_SIZE          0x300
NO_INIT STATIC char swdl_stack[SWDL_STACK_SIZE];
#endif
#endif /* FBK2_HW && DOWNLOAD_DEVICE */


/*--------------------------------------------------------------------------*/
/* Application task(s)                                                      */
/*--------------------------------------------------------------------------*/
#if defined (HART_MASTER) || defined (MODBUS_MASTER)
#define APPL_EVENTS             (OS_IF_EVENT_TIMER  + OS_IF_EVENT_EEPROM + OS_IF_EVENT_INDCON + OS_IF_EVENT_RESUME)
#else
#define APPL_EVENTS             (OS_IF_EVENT_TIMER + OS_IF_EVENT_EEPROM)
#endif
#define APPL_MSGEVT             (OS_IF_EVENT_EEPROM)
#define APPL_MSGNUM             (5)
#define APPL_STACK_SIZE         (0x300)
STATIC NO_INIT uint8_t appl_stack[APPL_STACK_SIZE];

//AK inserted
//#define PROCESS_STACK_SIZE         0x200
//static NO_INIT uint8_t process_stack[PROCESS_STACK_SIZE];


#if defined (HART_MASTER)
/*--------------------------------------------------------------------------*/
/* HART Master task(s)                                                      */
/*--------------------------------------------------------------------------*/
#define HM_EVENTS           (HART_START_EVENT +                                              \
                            OS_IF_EVENT_EEPROM + OS_IF_EVENT_TIMER + OS_IF_EVENT_REQRES +   \
                            HART_RECEIVE_END_EVENT + HART_SEND_END_EVENT + HART_ERROR_EVENT)
#define HM_MSGEVT           (OS_IF_EVENT_EEPROM)
#define HM_MSGNUM           (2)
#define HM_STACK_SIZE       (0x500)
STATIC NO_INIT uint8_t hm_stack[HM_STACK_SIZE];

#endif /* HART_MASTER */

#if defined (MODBUS_MASTER)
/*--------------------------------------------------------------------------*/
/* Modbus Master task(s)                                                    */
/*--------------------------------------------------------------------------*/
#define MODB_EVENTS             MODB_USR_EVENT + MODB_RCV_END_EVENT + MODB_XMT_END_EVENT + \
                                MODB_TIMEOUT_EVENT + OS_IF_EVENT_TIMER + MODB_START_EVENT
#define MODB_MSGEVT             OS_IF_EVENT_EEPROM + MODB_USR_EVENT
#define MODB_MSGNUM             5
#define MODB_STACK_SIZE         0x300
NO_INIT static char modb_stack[MODB_STACK_SIZE];

#endif /* MODBUS_MASTER */

#include "da_embos.h"                           /* DATA SEGMENT DEFINITION */

#define MB_MORE 0
//Placeholders for mailboxes
#if defined (PROTOCOL_FF)
    #ifdef LINK_MASTER
        #if LAS_MSGNUM == 0
#define las_mb NULL
        #else
SOFTING_TASK_MEM_Z static OS_MAILBOX las_mb[LAS_MSGNUM+MB_MORE];
        #endif
    #endif /* LINK_MASTER */
    #if FDC_MSGNUM == 0
#define fdc_mb NULL
    #else
SOFTING_TASK_MEM_Z static OS_MAILBOX fdc_mb[FDC_MSGNUM+MB_MORE];
    #endif
    #if SBSCR_MSGNUM == 0
#define sbscr_mb NULL
    #else
SOFTING_TASK_MEM_Z static OS_MAILBOX sbscr_mb[SBSCR_MSGNUM+MB_MORE];
    #endif
    #ifdef MVC_OBJECTS
        #if MVC_MSGNUM == 0
#define mvc_mb NULL
        #else
SOFTING_TASK_MEM_Z static OS_MAILBOX mvc_mb[MVC_MSGNUM+MB_MORE];
        #endif
    #endif /* MVC_OBJECTS */
    #if BGD50_MSGNUM == 0
#define bgd50_mb NULL
    #else
SOFTING_TASK_MEM_Z static OS_MAILBOX bgd50_mb[BGD50_MSGNUM+MB_MORE];
    #endif
#endif /* Protocol type */
    #if BGD_MSGNUM == 0
#define bgd_mb NULL
    #else
SOFTING_TASK_MEM_Z static OS_MAILBOX bgd_mb[BGD_MSGNUM+MB_MORE];
    #endif
    #if EEP_MSGNUM == 0
#define eep_mb NULL
    #else
//We do not access this but are shy of removing it
SOFTING_TASK_MEM_Z static OS_MAILBOX eep_mb[EEP_MSGNUM+MB_MORE];
    #endif
    #if FB_MSGNUM == 0
#define fb_mb NULL
    #else
SOFTING_TASK_MEM_Z static OS_MAILBOX fb_mb[FB_MSGNUM+MB_MORE];
    #endif
    #if defined (HART_MASTER)
        #if HM_MSGNUM == 0
#define hm_mb NULL
        #else
static OS_MAILBOX hm_mb[HM_MSGNUM+MB_MORE];
        #endif
    #endif /* HART_MASTER */
    #if APPL_MSGNUM == 0
#define appl_mb NULL
    #else
static OS_MAILBOX appl_mb[APPL_MSGNUM+MB_MORE];
    #endif

//AK inserted
//#define PROCESS_MSGNUM 2
//static OS_MAILBOX process_mb[PROCESS_MSGNUM+MB_MORE];


#include "da_def.h"                                 /* DEFAULT DATA SEGMENT */

EXPORT_DATA

#include "cs_osif.h"                         /* CONSTANT SEGMENT DEFINITION */
const TASK_CFG Task_cfg[MAX_TASK_NUM] = MN_ALLOW_INIT_ZERODEFAULT()
{
/*   TASK_ID      , TASK_PRIO      , NUM_MSG     , EVENTS      , MSG_EVTS    , STACKSIZE + STACKAREA  , MAIN_FKT, NAME           */
#if defined (PROTOCOL_FF)
#ifdef LINK_MASTER
    [LAS_TASK_ID] =
    {
        .prio = LAS_TASK_PRIO  ,
        .num_msg = LAS_MSGNUM  ,
        .valid_events = LAS_EVENTS | OS_IF_EVENT_SYSSTART  ,
        .msg_events = LAS_MSGEVT  ,
        TASK_STACK(las_stack)  ,
        .mb = las_mb,
        .name = "LAS Task"
    },
#endif /* LINK_MASTER */
    [FDC_TASK_ID] =
    {
        .prio = FDC_TASK_PRIO  ,
        .num_msg = FDC_MSGNUM  ,
        .valid_events = FDC_EVENTS | OS_IF_EVENT_SYSSTART  ,
        .msg_events = FDC_MSGEVT  ,
        TASK_STACK(fdc_stack)  ,
        .mb = fdc_mb,
        .name = "FDC Task"
    },
    [SBSCR_TASK_ID] =
    {
        .prio = SBSCR_TASK_PRIO,
        .num_msg = SBSCR_MSGNUM,
        .valid_events = SBSCR_EVENTS | OS_IF_EVENT_SYSSTART,
        .msg_events = SBSCR_MSGEVT,
        TASK_STACK(sbscr_stack),
        .mb = sbscr_mb,
        .name = "SBSCR Task"
    },
#ifdef MVC_OBJECTS
    [MVC_TASK_ID] =
    {
        .prio = MVC_TASK_PRIO,
        .num_msg = MVC_MSGNUM,
        .valid_events = MVC_EVENTS | OS_IF_EVENT_SYSSTART,
        .msg_events = MVC_MSGEVT,
        TASK_STACK(mvc_stack),
        .mb = mvc_mb,
        .name = "MVC Task"
    },
#endif /* MVC_OBJECTS */
    [BGD50_TASK_ID] =
    {
        .prio = BGD50_TASK_PRIO,
        .num_msg = BGD50_MSGNUM,
        .valid_events = BGD50_EVENTS | OS_IF_EVENT_SYSSTART,
        .msg_events = BGD50_MSGEVT,
        TASK_STACK(bgd50_stack),
        .mb = bgd50_mb,
        .name = "BGD50 Task"
    },
#elif defined (PROTOCOL_PA) || defined (PROTOCOL_DP)
    [DPS_TASK_ID] = {  , DPS_TASK_PRIO  , DPS_MSGNUM  , DPS_EVENTS  , DPS_MSGEVT  , TASK_STACK(dps_stack)  , NULL    , "DPS Task"     },
    [DUSR_TASK_ID] = { , DUSR_TASK_PRIO , DUSR_MSGNUM , DUSR_EVENTS , DUSR_MSGEVT , TASK_STACK(dusr_stack) , NULL    , "DUSR Task"    },
    [FBS_TASK_ID] = {  , FBS_TASK_PRIO  , FBS_MSGNUM  , FBS_EVENTS  , FBS_MSGEVT  , TASK_STACK(fbs_stack)  , NULL    , "FBS Task"     },
#endif /* Protocol type */
    [BGD_TASK_ID] =
    {
        .prio = BGD_TASK_PRIO  ,
        .num_msg = BGD_MSGNUM  ,
        .valid_events = BGD_EVENTS | OS_IF_EVENT_SYSSTART  ,
        .msg_events = BGD_MSGEVT  ,
        TASK_STACK(bgd_stack)  ,
        .mb = bgd_mb,
        .name = "BGD Task"
    },
#if 1 //This is now process task
    [EEP_TASK_ID] =
    {
        .prio = EEP_TASK_PRIO  ,
        .num_msg = EEP_MSGNUM  ,
        .valid_events = EEP_EVENTS | OS_IF_EVENT_SYSSTART  ,
        .msg_events = EEP_MSGEVT  ,
        TASK_STACK(eep_stack)  ,
        .mb = eep_mb,
        .name = "EEP Task"
    },
#endif //0
    [FB_TASK_ID] =
    {
        .prio = FB_TASK_PRIO   ,
        .num_msg = FB_MSGNUM   ,
        .valid_events = FB_EVENTS | OS_IF_EVENT_SYSSTART   ,
        .msg_events = FB_MSGEVT   ,
        TASK_STACK(fb1_stack)  ,
        .mb = fb_mb,
        .name = "FB Exec Task"
    },
    /* @Dresser-Masoneilan project: Watchdog Task not required, because external Watchdog is used. */
    //{FDC_WD_TASK_ID , FDC_WD_TASK_PRIO , WD_MSGNUM , WD_EVENTS , WD_MSGEVT   , TASK_STACK(wd_stack)   , NULL    , "WD Task"      },
/*@Dresser-Masoneilan project modified */
#if 0
#if defined (FBK2_HW) && defined (DOWNLOAD_DEVICE)
    [FBK2_DWNLD_HANDLER_TASK_ID] = { , FBK2_DWNLD_HANDLER_TASK_PRIO , SWDL_MSGNUM , SWDL_EVENTS , SWDL_MSGEVT , TASK_STACK(swdl_stack) , NULL  , "SWDL Task"    },
#endif /* DOWNLOAD_DEVICE */
#endif
#if defined (HART_MASTER)
    [HM_TASK_ID] =
    {
        /*We need boosted HM task priority so that FF stack doesn't run
        until we are ready. This is subtle and fragile but it ain't my design :)
        */
        .prio = HM_TASK_START_PRIO   , //Must block FF stack until ready
        .num_msg = HM_MSGNUM   ,
        .valid_events = HM_EVENTS | OS_IF_EVENT_SYSSTART   ,
        .msg_events = HM_MSGEVT   ,
        TASK_STACK(hm_stack)   ,
        .mb = hm_mb,
        .name = "HM Task"
    },
#endif /* HART_MASTER */
#if defined (MODBUS_MASTER)
    [MODB_TASK_ID] = { , MODB_TASK_PRIO , MODB_MSGNUM , MODB_EVENTS , MODB_MSGEVT , TASK_STACK(modb_stack) , NULL    , "Modbus Task"  },
#endif /* MODBUS_MASTER */
    [APPL_TASK_ID] =
    {
        .prio = APPL_TASK_PRIO ,
        .num_msg = APPL_MSGNUM ,
        .valid_events = APPL_EVENTS | OS_IF_EVENT_SYSSTART ,
        .msg_events = APPL_MSGEVT ,
        TASK_STACK(appl_stack) ,
        .mb = appl_mb,
        .name = "APPL Task"
    },
#if 0
    [TASKID_PROCESS] =
    {
        .prio = PROCESS_TASK_PRIO ,
        .num_msg = 0 ,
        .valid_events = 0 ,
        .msg_events = 0 ,
        TASK_STACK(process_stack) ,
        .mb = process_mb,
        .name = "Process Task"
    },
#endif //0
};
#include "cs_def.h"                           /* DEFAULT CONSTANT SEGMENT */
