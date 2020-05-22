/*
** @(#)com_tbls.h   1.4 2002-06-13
**
** FF common table values used by FF blocks
** Filename: com_tbls.h
** Spec revision: FF-900 FS 1.0  DDL spec
**                FF-890 FS 1.2  FBAP spec part 1
**                FF-891 FS 1.2  FBAP spec part 2
**                FF-903 PS 2.0  TBP spec
** Date of last change: 2007-01-05
** Description:
**
**
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
** (c) Fieldbus Foundation(TM) (1994-2005)
**
*/

/*
** HISTORY:
** JPH   Revision 0.9  19960430
** TAB   Revision 1.0  19961015
** DAD   Revision 1.1  13MAY97
**       -- added units codes 1000-1429, spares 1430-1440
** QLQ   Revision 1.2  20AUG97
**       -- added __UNITS_CODES and __FF_MANUFAC_IDS
** SBM   Revision 1.3 2002-06-13
**       Added enumerations for FBAP Part 3 blocks
**       Updated Manufacturer IDs
** FI    Revision 1.4 20051109
**       added standard channel enumeration
**       added several discrete definitions for FBAP Part 3 blocks
**       added unit code definitions per ARs 1496,1583,1593,1617,1712,1713,1714,1715,1716,1717,1718.1719,1730
**       updated manufacturer ids
**       fixed and added alarm summary bits
**       added FBAP Part 3 alarm summary defintions
**       fixed __FF_CALC_ERRS_ENUMS per AR#1610
**       fixed __FF_CHECKBACK_ENUMS per AR#1610
**       fixed __FF_INTEG_OPTS_ENUMS per AR#1610
**       fixed __FF_OP_CMD_CXO_ENUMS per AR#1610
**       added IO_OPTS definitions per AR#708
**       added CONTROL_OPTS definitions per AR#708
**       added STATUS_OPTS definitions per AR#708
**       extended unit code range to 1699 to account for future assignments
** MS	 added several more manufacturer IDs
** MS    AR3343 - added macros for adding FD params to RB redefs
** MS   ARs 2055, 2126, 2128, 2211, 2258, 2297, 2298, 2583, 2692, 2862, 2934 -- 2008.10.07
** MS	ARs 3100, 3101, 3504, 3786, 3854, 3943, 4031, 2227, 4116, 3656, 4171 -- 2009.06.15
** MS   ARs 4815, 5095, 4231, 4324, 4416, 4536, 4617, 4628, 4658, 5080, 5100, 5282, 5337 -- 2010.06.14
*/

#ifndef  __COMMON_TABLES_H
#define  __COMMON_TABLES_H

/*
**********************************************************************
** Pull in standard defines
**********************************************************************
*/
#include "std_defs.h"

/*
**********************************************************************
** Standard undefined enumerations
**********************************************************************
*/
#define _UNINITIALIZED_VALUE   { 0x00, [uninitialized],   [uninitialized_help] }
#define _UNDEFINED_VALUE        { 0x00, [undefined],   [undefined_help] }
/*
**********************************************************************
** Standard channel enumeration
**********************************************************************
*/
#define _CHANNEL_0  { 0x00, [channel_0],   [channel_0_help] }
#define _CHANNEL_1  { 0x01, [channel_1],   [channel_1_help] }
#define _CHANNEL_2  { 0x02, [channel_2],   [channel_2_help] }

/*
**********************************************************************
** Status (status_*) values (DS-65,66,67)
**********************************************************************
*/
#define  _STATUS_0    {0x00,  [status_bad_non_not_ltd],           [status_bad_non_not_ltd_help] }
#define  _STATUS_1    {0x01,  [status_bad_non_low_ltd],           [status_bad_non_low_ltd_help] }
#define  _STATUS_2    {0x02,  [status_bad_non_high_ltd],          [status_bad_non_high_ltd_help] }
#define  _STATUS_3    {0x03,  [status_bad_non_const],             [status_bad_non_const_help] }
#define  _STATUS_4    {0x04,  [status_bad_config_not_ltd],        [status_bad_config_not_ltd_help] }
#define  _STATUS_5    {0x05,  [status_bad_config_low_ltd],        [status_bad_config_low_ltd_help] }
#define  _STATUS_6    {0x06,  [status_bad_config_high_ltd],       [status_bad_config_high_ltd_help] }
#define  _STATUS_7    {0x07,  [status_bad_config_const],          [status_bad_config_const_help] }
#define  _STATUS_8    {0x08,  [status_bad_connect_not_ltd],       [status_bad_connect_not_ltd_help] }
#define  _STATUS_9    {0x09,  [status_bad_connect_low_ltd],       [status_bad_connect_low_ltd_help] }
#define  _STATUS_10   {0x0a,  [status_bad_connect_high_ltd],      [status_bad_connect_high_ltd_help] }
#define  _STATUS_11   {0x0b,  [status_bad_connect_const],         [status_bad_connect_const_help] }
#define  _STATUS_12   {0x0c,  [status_bad_device_not_ltd],        [status_bad_device_not_ltd_help] }
#define  _STATUS_13   {0x0d,  [status_bad_device_low_ltd],        [status_bad_device_low_ltd_help] }
#define  _STATUS_14   {0x0e,  [status_bad_device_high_ltd],       [status_bad_device_high_ltd_help] }
#define  _STATUS_15   {0x0f,  [status_bad_device_const],          [status_bad_device_const_help] }
#define  _STATUS_16   {0x10,  [status_bad_sensor_not_ltd],        [status_bad_sensor_not_ltd_help] }
#define  _STATUS_17   {0x11,  [status_bad_sensor_low_ltd],        [status_bad_sensor_low_ltd_help] }
#define  _STATUS_18   {0x12,  [status_bad_sensor_high_ltd],       [status_bad_sensor_high_ltd_help] }
#define  _STATUS_19   {0x13,  [status_bad_sensor_const],          [status_bad_sensor_const_help] }
#define  _STATUS_20   {0x14,  [status_bad_comm_last_not_ltd],     [status_bad_comm_last_not_ltd_help] }
#define  _STATUS_21   {0x15,  [status_bad_comm_last_low_ltd],     [status_bad_comm_last_low_ltd_help] }
#define  _STATUS_22   {0x16,  [status_bad_comm_last_high_ltd],    [status_bad_comm_last_high_ltd_help] }
#define  _STATUS_23   {0x17,  [status_bad_comm_last_const],       [status_bad_comm_last_const_help] }
#define  _STATUS_24   {0x18,  [status_bad_comm_no_val_not_ltd],   [status_bad_comm_no_val_not_ltd_help] }
#define  _STATUS_25   {0x19,  [status_bad_comm_no_val_low_ltd],   [status_bad_comm_no_val_low_ltd_help] }
#define  _STATUS_26   {0x1a,  [status_bad_comm_no_val_high_ltd],  [status_bad_comm_no_val_high_ltd_help] }
#define  _STATUS_27   {0x1b,  [status_bad_comm_no_val_const],     [status_bad_comm_no_val_const_help] }
#define  _STATUS_28   {0x1c,  [status_bad_oos_not_ltd],           [status_bad_oos_not_ltd_help] }
#define  _STATUS_29   {0x1d,  [status_bad_oos_low_ltd],           [status_bad_oos_low_ltd_help] }
#define  _STATUS_30   {0x1e,  [status_bad_oos_high_ltd],          [status_bad_oos_high_ltd_help] }
#define  _STATUS_31   {0x1f,  [status_bad_oos_const],             [status_bad_oos_const_help] }

#define  _STATUS_64   {0x40,  [status_uncertain_non_not_ltd],     [status_uncertain_non_not_ltd_help] }
#define  _STATUS_65   {0x41,  [status_uncertain_non_low_ltd],     [status_uncertain_non_low_ltd_help] }
#define  _STATUS_66   {0x42,  [status_uncertain_non_high_ltd],    [status_uncertain_non_high_ltd_help] }
#define  _STATUS_67   {0x43,  [status_uncertain_non_const],       [status_uncertain_non_const_help] }
#define  _STATUS_68   {0x44,  [status_uncertain_last_not_ltd],    [status_uncertain_last_not_ltd_help] }
#define  _STATUS_69   {0x45,  [status_uncertain_last_low_ltd],    [status_uncertain_last_low_ltd_help] }
#define  _STATUS_70   {0x46,  [status_uncertain_last_high_ltd],   [status_uncertain_last_high_ltd_help] }
#define  _STATUS_71   {0x47,  [status_uncertain_last_const],      [status_uncertain_last_const_help] }
#define  _STATUS_72   {0x48,  [status_uncertain_subst_not_ltd],   [status_uncertain_subst_not_ltd_help] }
#define  _STATUS_73   {0x49,  [status_uncertain_subst_low_ltd],   [status_uncertain_subst_low_ltd_help] }
#define  _STATUS_74   {0x4a,  [status_uncertain_subst_high_ltd],  [status_uncertain_subst_high_ltd_help] }
#define  _STATUS_75   {0x4b,  [status_uncertain_subst_const],     [status_uncertain_subst_const_help] }
#define  _STATUS_76   {0x4c,  [status_uncertain_init_not_ltd],    [status_uncertain_init_not_ltd_help] }
#define  _STATUS_77   {0x4d,  [status_uncertain_init_low_ltd],    [status_uncertain_init_low_ltd_help] }
#define  _STATUS_78   {0x4e,  [status_uncertain_init_high_ltd],   [status_uncertain_init_high_ltd_help] }
#define  _STATUS_79   {0x4f,  [status_uncertain_init_const],      [status_uncertain_init_const_help] }
#define  _STATUS_80   {0x50,  [status_uncertain_snsr_not_ltd],    [status_uncertain_snsr_not_ltd_help] }
#define  _STATUS_81   {0x51,  [status_uncertain_snsr_low_ltd],    [status_uncertain_snsr_low_ltd_help] }
#define  _STATUS_82   {0x52,  [status_uncertain_snsr_high_ltd],   [status_uncertain_snsr_high_ltd_help] }
#define  _STATUS_83   {0x53,  [status_uncertain_snsr_const],      [status_uncertain_snsr_const_help] }
#define  _STATUS_84   {0x54,  [status_uncertain_rng_not_ltd],     [status_uncertain_rng_not_ltd_help] }
#define  _STATUS_85   {0x55,  [status_uncertain_rng_low_ltd],     [status_uncertain_rng_low_ltd_help] }
#define  _STATUS_86   {0x56,  [status_uncertain_rng_high_ltd],    [status_uncertain_rng_high_ltd_help] }
#define  _STATUS_87   {0x57,  [status_uncertain_rng_const],       [status_uncertain_rng_const_help] }
#define  _STATUS_88   {0x58,  [status_uncertain_sub_not_ltd],     [status_uncertain_sub_not_ltd_help] }
#define  _STATUS_89   {0x59,  [status_uncertain_sub_low_ltd],     [status_uncertain_sub_low_ltd_help] }
#define  _STATUS_90   {0x5a,  [status_uncertain_sub_high_ltd],    [status_uncertain_sub_high_ltd_help] }
#define  _STATUS_91   {0x5b,  [status_uncertain_sub_const],       [status_uncertain_sub_const_help] }

#define  _STATUS_128  {0x80,  [status_good_noncas_non_not_ltd],               [status_good_noncas_non_not_ltd_help] }
#define  _STATUS_129  {0x81,  [status_good_noncas_non_low_ltd],               [status_good_noncas_non_low_ltd_help] }
#define  _STATUS_130  {0x82,  [status_good_noncas_non_high_ltd],              [status_good_noncas_non_high_ltd_help] }
#define  _STATUS_131  {0x83,  [status_good_noncas_non_const],                 [status_good_noncas_non_const_help] }
#define  _STATUS_132  {0x84,  [status_good_noncas_blk_alm_not_ltd],           [status_good_noncas_blk_alm_not_ltd_help] }
#define  _STATUS_133  {0x85,  [status_good_noncas_blk_alm_low_ltd],           [status_good_noncas_blk_alm_low_ltd_help] }
#define  _STATUS_134  {0x86,  [status_good_noncas_blk_alm_high_ltd],          [status_good_noncas_blk_alm_high_ltd_help] }
#define  _STATUS_135  {0x87,  [status_good_noncas_blk_alm_const],             [status_good_noncas_blk_alm_const_help] }
#define  _STATUS_136  {0x88,  [status_good_noncas_adv_alm_not_ltd],           [status_good_noncas_adv_alm_not_ltd_help] }
#define  _STATUS_137  {0x89,  [status_good_noncas_adv_alm_low_ltd],           [status_good_noncas_adv_alm_low_ltd_help] }
#define  _STATUS_138  {0x8a,  [status_good_noncas_adv_alm_high_ltd],          [status_good_noncas_adv_alm_high_ltd_help] }
#define  _STATUS_139  {0x8b,  [status_good_noncas_adv_alm_const],             [status_good_noncas_adv_alm_const_help] }
#define  _STATUS_140  {0x8c,  [status_good_noncas_crit_alm_not_ltd],          [status_good_noncas_crit_alm_not_ltd_help] }
#define  _STATUS_141  {0x8d,  [status_good_noncas_crit_alm_low_ltd],          [status_good_noncas_crit_alm_low_ltd_help] }
#define  _STATUS_142  {0x8e,  [status_good_noncas_crit_alm_high_ltd],         [status_good_noncas_crit_alm_high_ltd_help] }
#define  _STATUS_143  {0x8f,  [status_good_noncas_crit_alm_const],            [status_good_noncas_crit_alm_const_help] }
#define  _STATUS_144  {0x90,  [status_good_noncas_unack_blk_alm_not_ltd],     [status_good_noncas_unack_blk_alm_not_ltd_help] }
#define  _STATUS_145  {0x91,  [status_good_noncas_unack_blk_alm_low_ltd],     [status_good_noncas_unack_blk_alm_low_ltd_help] }
#define  _STATUS_146  {0x92,  [status_good_noncas_unack_blk_alm_high_ltd],    [status_good_noncas_unack_blk_alm_high_ltd_help] }
#define  _STATUS_147  {0x93,  [status_good_noncas_unack_blk_alm_const],       [status_good_noncas_unack_blk_alm_const_help] }
#define  _STATUS_148  {0x94,  [status_good_noncas_unack_adv_alm_not_ltd],     [status_good_noncas_unack_adv_alm_not_ltd_help] }
#define  _STATUS_149  {0x95,  [status_good_noncas_unack_adv_alm_low_ltd],     [status_good_noncas_unack_adv_alm_low_ltd_help] }
#define  _STATUS_150  {0x96,  [status_good_noncas_unack_adv_alm_high_ltd],    [status_good_noncas_unack_adv_alm_high_ltd_help] }
#define  _STATUS_151  {0x97,  [status_good_noncas_unack_adv_alm_const],       [status_good_noncas_unack_adv_alm_const_help] }
#define  _STATUS_152  {0x98,  [status_good_noncas_unack_crit_alm_not_ltd],    [status_good_noncas_unack_crit_alm_not_ltd_help] }
#define  _STATUS_153  {0x99,  [status_good_noncas_unack_crit_alm_low_ltd],    [status_good_noncas_unack_crit_alm_low_ltd_help] }
#define  _STATUS_154  {0x9a,  [status_good_noncas_unack_crit_alm_high_ltd],   [status_good_noncas_unack_crit_alm_high_ltd_help] }
#define  _STATUS_155  {0x9b,  [status_good_noncas_unack_crit_alm_const],      [status_good_noncas_unack_crit_alm_const_help] }

#define  _STATUS_192  {0xc0,  [status_good_cas_non_not_ltd],                  [status_good_cas_non_not_ltd_help] }
#define  _STATUS_193  {0xc1,  [status_good_cas_non_low_ltd],                  [status_good_cas_non_low_ltd_help] }
#define  _STATUS_194  {0xc2,  [status_good_cas_non_high_ltd],                 [status_good_cas_non_high_ltd_help] }
#define  _STATUS_195  {0xc3,  [status_good_cas_non_const],                    [status_good_cas_non_const_help] }
#define  _STATUS_196  {0xc4,  [status_good_cas_init_ack_not_ltd],             [status_good_cas_init_ack_not_ltd_help] }
#define  _STATUS_197  {0xc5,  [status_good_cas_init_ack_low_ltd],             [status_good_cas_init_ack_low_ltd_help] }
#define  _STATUS_198  {0xc6,  [status_good_cas_init_ack_high_ltd],            [status_good_cas_init_ack_high_ltd_help] }
#define  _STATUS_199  {0xc7,  [status_good_cas_init_ack_const],               [status_good_cas_init_ack_const_help] }
#define  _STATUS_200  {0xc8,  [status_good_cas_init_req_not_ltd],             [status_good_cas_init_req_not_ltd_help] }
#define  _STATUS_201  {0xc9,  [status_good_cas_init_req_low_ltd],             [status_good_cas_init_req_low_ltd_help] }
#define  _STATUS_202  {0xca,  [status_good_cas_init_req_high_ltd],            [status_good_cas_init_req_high_ltd_help] }
#define  _STATUS_203  {0xcb,  [status_good_cas_init_req_const],               [status_good_cas_init_req_const_help] }
#define  _STATUS_204  {0xcc,  [status_good_cas_not_invited_not_ltd],          [status_good_cas_not_invited_not_ltd_help] }
#define  _STATUS_205  {0xcd,  [status_good_cas_not_invited_low_ltd],          [status_good_cas_not_invited_low_ltd_help] }
#define  _STATUS_206  {0xce,  [status_good_cas_not_invited_high_ltd],         [status_good_cas_not_invited_high_ltd_help] }
#define  _STATUS_207  {0xcf,  [status_good_cas_not_invited_const],            [status_good_cas_not_invited_const_help] }
#define  _STATUS_208  {0xd0,  [status_good_cas_not_selected_not_ltd],         [status_good_cas_not_selected_not_ltd_help] }
#define  _STATUS_209  {0xd1,  [status_good_cas_not_selected_low_ltd],         [status_good_cas_not_selected_low_ltd_help] }
#define  _STATUS_210  {0xd2,  [status_good_cas_not_selected_high_ltd],        [status_good_cas_not_selected_high_ltd_help] }
#define  _STATUS_211  {0xd3,  [status_good_cas_not_selected_const],           [status_good_cas_not_selected_const_help] }
#define  _STATUS_212  {0xd4,  [status_good_cas_do_not_select_not_ltd],        [status_good_cas_do_not_select_not_ltd_help] }
#define  _STATUS_213  {0xd5,  [status_good_cas_do_not_select_low_ltd],        [status_good_cas_do_not_select_low_ltd_help] }
#define  _STATUS_214  {0xd6,  [status_good_cas_do_not_select_high_ltd],       [status_good_cas_do_not_select_high_ltd_help] }
#define  _STATUS_215  {0xd7,  [status_good_cas_do_not_select_const],          [status_good_cas_do_not_select_const_help] }
#define  _STATUS_216  {0xd8,  [status_good_cas_loc_override_not_ltd],         [status_good_cas_loc_override_not_ltd_help] }
#define  _STATUS_217  {0xd9,  [status_good_cas_loc_override_low_ltd],         [status_good_cas_loc_override_low_ltd_help] }
#define  _STATUS_218  {0xda,  [status_good_cas_loc_override_high_ltd],        [status_good_cas_loc_override_high_ltd_help] }
#define  _STATUS_219  {0xdb,  [status_good_cas_loc_override_const],           [status_good_cas_loc_override_const_help] }
#define  _STATUS_220  {0xdc,  [status_good_cas_fs_act_not_ltd],               [status_good_cas_fs_act_not_ltd_help] }
#define  _STATUS_221  {0xdd,  [status_good_cas_fs_act_low_ltd],               [status_good_cas_fs_act_low_ltd_help] }
#define  _STATUS_222  {0xde,  [status_good_cas_fs_act_high_ltd],              [status_good_cas_fs_act_high_ltd_help] }
#define  _STATUS_223  {0xdf,  [status_good_cas_fs_act_const],                 [status_good_cas_fs_act_const_help] }
#define  _STATUS_224  {0xe0,  [status_good_cas_init_fs_not_ltd],              [status_good_cas_init_fs_not_ltd_help] }
#define  _STATUS_225  {0xe1,  [status_good_cas_init_fs_low_ltd],              [status_good_cas_init_fs_low_ltd_help] }
#define  _STATUS_226  {0xe2,  [status_good_cas_init_fs_high_ltd],             [status_good_cas_init_fs_high_ltd_help] }
#define  _STATUS_227  {0xe3,  [status_good_cas_init_fs_const],                [status_good_cas_init_fs_const_help] }

#define  __FF_STATUS_VALUES \
        _STATUS_0,\
        _STATUS_1,\
        _STATUS_2,\
        _STATUS_3,\
        _STATUS_4,\
        _STATUS_5,\
        _STATUS_6,\
        _STATUS_7,\
        _STATUS_8,\
        _STATUS_9,\
        _STATUS_10,\
        _STATUS_11,\
        _STATUS_12,\
        _STATUS_13,\
        _STATUS_14,\
        _STATUS_15,\
        _STATUS_16,\
        _STATUS_17,\
        _STATUS_18,\
        _STATUS_19,\
        _STATUS_20,\
        _STATUS_21,\
        _STATUS_22,\
        _STATUS_23,\
        _STATUS_24,\
        _STATUS_25,\
        _STATUS_26,\
        _STATUS_27,\
        _STATUS_28,\
        _STATUS_29,\
        _STATUS_30,\
        _STATUS_31,\
        _STATUS_64,\
        _STATUS_65,\
        _STATUS_66,\
        _STATUS_67,\
        _STATUS_68,\
        _STATUS_69,\
        _STATUS_70,\
        _STATUS_71,\
        _STATUS_72,\
        _STATUS_73,\
        _STATUS_74,\
        _STATUS_75,\
        _STATUS_76,\
        _STATUS_77,\
        _STATUS_78,\
        _STATUS_79,\
        _STATUS_80,\
        _STATUS_81,\
        _STATUS_82,\
        _STATUS_83,\
        _STATUS_84,\
        _STATUS_85,\
        _STATUS_86,\
        _STATUS_87,\
        _STATUS_88,\
        _STATUS_89,\
        _STATUS_90,\
        _STATUS_91,\
        _STATUS_128,\
        _STATUS_129,\
        _STATUS_130,\
        _STATUS_131,\
        _STATUS_132,\
        _STATUS_133,\
        _STATUS_134,\
        _STATUS_135,\
        _STATUS_136,\
        _STATUS_137,\
        _STATUS_138,\
        _STATUS_139,\
        _STATUS_140,\
        _STATUS_141,\
        _STATUS_142,\
        _STATUS_143,\
        _STATUS_144,\
        _STATUS_145,\
        _STATUS_146,\
        _STATUS_147,\
        _STATUS_148,\
        _STATUS_149,\
        _STATUS_150,\
        _STATUS_151,\
        _STATUS_152,\
        _STATUS_153,\
        _STATUS_154,\
        _STATUS_155,\
        _STATUS_192,\
        _STATUS_193,\
        _STATUS_194,\
        _STATUS_195,\
        _STATUS_196,\
        _STATUS_197,\
        _STATUS_198,\
        _STATUS_199,\
        _STATUS_200,\
        _STATUS_201,\
        _STATUS_202,\
        _STATUS_203,\
        _STATUS_204,\
        _STATUS_205,\
        _STATUS_206,\
        _STATUS_207,\
        _STATUS_208,\
        _STATUS_209,\
        _STATUS_210,\
        _STATUS_211,\
        _STATUS_212,\
        _STATUS_213,\
        _STATUS_214,\
        _STATUS_215,\
        _STATUS_216,\
        _STATUS_217,\
        _STATUS_218,\
        _STATUS_219,\
        _STATUS_220,\
        _STATUS_221,\
        _STATUS_222,\
        _STATUS_223,\
        _STATUS_224,\
        _STATUS_225,\
        _STATUS_226,\
        _STATUS_227

/*
**********************************************************************
** Discrete Values (DS-66)
**********************************************************************
*/
#define _DISCRETE_VALUE_0   { 0x00,   [discrete_state_0],   [discrete_state_0_help] }
#define _DISCRETE_VALUE_1   { 0x01,   [discrete_state_1],   [discrete_state_1_help] }
#define _DISCRETE_VALUE_2   { 0x02,   [discrete_state_2],   [no_help_available] }
#define _DISCRETE_VALUE_3   { 0x03,   [discrete_state_3],   [no_help_available] }
#define _DISCRETE_VALUE_4   { 0x04,   [discrete_state_4],   [no_help_available] }
#define _DISCRETE_VALUE_5   { 0x05,   [discrete_state_5],   [no_help_available] }
#define _DISCRETE_VALUE_6   { 0x06,   [discrete_state_6],   [no_help_available] }
#define _DISCRETE_VALUE_7   { 0x07,   [discrete_state_7],   [no_help_available] }
#define _DISCRETE_VALUE_8   { 0x08,   [discrete_state_8],   [no_help_available] }
#define _DISCRETE_VALUE_9   { 0x09,   [discrete_state_9],   [no_help_available] }
#define _DISCRETE_VALUE_10  { 0x0A,   [discrete_state_10],  [no_help_available] }
#define _DISCRETE_VALUE_11  { 0x0B,   [discrete_state_11],  [no_help_available] }
#define _DISCRETE_VALUE_12  { 0x0C,   [discrete_state_12],  [no_help_available] }
#define _DISCRETE_VALUE_13  { 0x0D,   [discrete_state_13],  [no_help_available] }
#define _DISCRETE_VALUE_14  { 0x0E,   [discrete_state_14],  [no_help_available] }
#define _DISCRETE_VALUE_15  { 0x0F,   [discrete_state_15],  [no_help_available] }
#define _DISCRETE_VALUE_16  { 0x10,   [discrete_state_16],  [no_help_available] }

#define _DISCRETE_VALUE_OFF { 0x00,   [off],   [no_help_available] }
#define _DISCRETE_VALUE_ON  { 0x01,   [on],   [no_help_available] }

#define _DISCRETE_VALUE_CONFIRM  { 0x01,   [confirm],   [no_help_available] }

#define _DISCRETE_VALUE_FORWARD  { 0x00,   [forward],   [no_help_available] }
#define _DISCRETE_VALUE_REVERSE  { 0x01,   [reverse],   [no_help_available] }

#define _DISABLE_VALUE_0  { 0x00,   [use],   [no_help_available] }
#define _DISABLE_VALUE_1  { 0x01,   [disable],   [no_help_available] }

/*
**********************************************************************
** Unit codes (unit_index) (DS-68, etc.)
**********************************************************************
*/
/*
** NOTE:
** these will be moved to the units code table after FBDD testing
*/
#define    _UNIT_CODE_1000  { 1000, [unit_code_1000], [unit_code_1000_help] }
#define    _UNIT_CODE_1001  { 1001, [unit_code_1001], [unit_code_1001_help] }
#define    _UNIT_CODE_1002  { 1002, [unit_code_1002], [unit_code_1002_help] }
#define    _UNIT_CODE_1003  { 1003, [unit_code_1003], [unit_code_1003_help] }
#define    _UNIT_CODE_1004  { 1004, [unit_code_1004], [unit_code_1004_help] }
#define    _UNIT_CODE_1005  { 1005, [unit_code_1005], [unit_code_1005_help] }
#define    _UNIT_CODE_1006  { 1006, [unit_code_1006], [unit_code_1006_help] }
#define    _UNIT_CODE_1007  { 1007, [unit_code_1007], [unit_code_1007_help] }
#define    _UNIT_CODE_1008  { 1008, [unit_code_1008], [unit_code_1008_help] }
#define    _UNIT_CODE_1009  { 1009, [unit_code_1009], [unit_code_1009_help] }
#define    _UNIT_CODE_1010  { 1010, [unit_code_1010], [unit_code_1010_help] }
#define    _UNIT_CODE_1011  { 1011, [unit_code_1011], [unit_code_1011_help] }
#define    _UNIT_CODE_1012  { 1012, [unit_code_1012], [unit_code_1012_help] }
#define    _UNIT_CODE_1013  { 1013, [unit_code_1013], [unit_code_1013_help] }
#define    _UNIT_CODE_1014  { 1014, [unit_code_1014], [unit_code_1014_help] }
#define    _UNIT_CODE_1015  { 1015, [unit_code_1015], [unit_code_1015_help] }
#define    _UNIT_CODE_1016  { 1016, [unit_code_1016], [unit_code_1016_help] }
#define    _UNIT_CODE_1017  { 1017, [unit_code_1017], [unit_code_1017_help] }
#define    _UNIT_CODE_1018  { 1018, [unit_code_1018], [unit_code_1018_help] }
#define    _UNIT_CODE_1019  { 1019, [unit_code_1019], [unit_code_1019_help] }
#define    _UNIT_CODE_1020  { 1020, [unit_code_1020], [unit_code_1020_help] }
#define    _UNIT_CODE_1021  { 1021, [unit_code_1021], [unit_code_1021_help] }
#define    _UNIT_CODE_1022  { 1022, [unit_code_1022], [unit_code_1022_help] }
#define    _UNIT_CODE_1023  { 1023, [unit_code_1023], [unit_code_1023_help] }
#define    _UNIT_CODE_1024  { 1024, [unit_code_1024], [unit_code_1024_help] }
#define    _UNIT_CODE_1025  { 1025, [unit_code_1025], [unit_code_1025_help] }
#define    _UNIT_CODE_1026  { 1026, [unit_code_1026], [unit_code_1026_help] }
#define    _UNIT_CODE_1027  { 1027, [unit_code_1027], [unit_code_1027_help] }
#define    _UNIT_CODE_1028  { 1028, [unit_code_1028], [unit_code_1028_help] }
#define    _UNIT_CODE_1029  { 1029, [unit_code_1029], [unit_code_1029_help] }
#define    _UNIT_CODE_1030  { 1030, [unit_code_1030], [unit_code_1030_help] }
#define    _UNIT_CODE_1031  { 1031, [unit_code_1031], [unit_code_1031_help] }
#define    _UNIT_CODE_1032  { 1032, [unit_code_1032], [unit_code_1032_help] }
#define    _UNIT_CODE_1033  { 1033, [unit_code_1033], [unit_code_1033_help] }
#define    _UNIT_CODE_1034  { 1034, [unit_code_1034], [unit_code_1034_help] }
#define    _UNIT_CODE_1035  { 1035, [unit_code_1035], [unit_code_1035_help] }
#define    _UNIT_CODE_1036  { 1036, [unit_code_1036], [unit_code_1036_help] }
#define    _UNIT_CODE_1037  { 1037, [unit_code_1037], [unit_code_1037_help] }
#define    _UNIT_CODE_1038  { 1038, [unit_code_1038], [unit_code_1038_help] }
#define    _UNIT_CODE_1039  { 1039, [unit_code_1039], [unit_code_1039_help] }
#define    _UNIT_CODE_1040  { 1040, [unit_code_1040], [unit_code_1040_help] }
#define    _UNIT_CODE_1041  { 1041, [unit_code_1041], [unit_code_1041_help] }
#define    _UNIT_CODE_1042  { 1042, [unit_code_1042], [unit_code_1042_help] }
#define    _UNIT_CODE_1043  { 1043, [unit_code_1043], [unit_code_1043_help] }
#define    _UNIT_CODE_1044  { 1044, [unit_code_1044], [unit_code_1044_help] }
#define    _UNIT_CODE_1045  { 1045, [unit_code_1045], [unit_code_1045_help] }
#define    _UNIT_CODE_1046  { 1046, [unit_code_1046], [unit_code_1046_help] }
#define    _UNIT_CODE_1047  { 1047, [unit_code_1047], [unit_code_1047_help] }
#define    _UNIT_CODE_1048  { 1048, [unit_code_1048], [unit_code_1048_help] }
#define    _UNIT_CODE_1049  { 1049, [unit_code_1049], [unit_code_1049_help] }
#define    _UNIT_CODE_1050  { 1050, [unit_code_1050], [unit_code_1050_help] }
#define    _UNIT_CODE_1051  { 1051, [unit_code_1051], [unit_code_1051_help] }
#define    _UNIT_CODE_1052  { 1052, [unit_code_1052], [unit_code_1052_help] }
#define    _UNIT_CODE_1053  { 1053, [unit_code_1053], [unit_code_1053_help] }
#define    _UNIT_CODE_1054  { 1054, [unit_code_1054], [unit_code_1054_help] }
#define    _UNIT_CODE_1055  { 1055, [unit_code_1055], [unit_code_1055_help] }
#define    _UNIT_CODE_1056  { 1056, [unit_code_1056], [unit_code_1056_help] }
#define    _UNIT_CODE_1057  { 1057, [unit_code_1057], [unit_code_1057_help] }
#define    _UNIT_CODE_1058  { 1058, [unit_code_1058], [unit_code_1058_help] }
#define    _UNIT_CODE_1059  { 1059, [unit_code_1059], [unit_code_1059_help] }
#define    _UNIT_CODE_1060  { 1060, [unit_code_1060], [unit_code_1060_help] }
#define    _UNIT_CODE_1061  { 1061, [unit_code_1061], [unit_code_1061_help] }
#define    _UNIT_CODE_1062  { 1062, [unit_code_1062], [unit_code_1062_help] }
#define    _UNIT_CODE_1063  { 1063, [unit_code_1063], [unit_code_1063_help] }
#define    _UNIT_CODE_1064  { 1064, [unit_code_1064], [unit_code_1064_help] }
#define    _UNIT_CODE_1065  { 1065, [unit_code_1065], [unit_code_1065_help] }
#define    _UNIT_CODE_1066  { 1066, [unit_code_1066], [unit_code_1066_help] }
#define    _UNIT_CODE_1067  { 1067, [unit_code_1067], [unit_code_1067_help] }
#define    _UNIT_CODE_1068  { 1068, [unit_code_1068], [unit_code_1068_help] }
#define    _UNIT_CODE_1069  { 1069, [unit_code_1069], [unit_code_1069_help] }
#define    _UNIT_CODE_1070  { 1070, [unit_code_1070], [unit_code_1070_help] }
#define    _UNIT_CODE_1071  { 1071, [unit_code_1071], [unit_code_1071_help] }
#define    _UNIT_CODE_1072  { 1072, [unit_code_1072], [unit_code_1072_help] }
#define    _UNIT_CODE_1073  { 1073, [unit_code_1073], [unit_code_1073_help] }
#define    _UNIT_CODE_1074  { 1074, [unit_code_1074], [unit_code_1074_help] }
#define    _UNIT_CODE_1075  { 1075, [unit_code_1075], [unit_code_1075_help] }
#define    _UNIT_CODE_1076  { 1076, [unit_code_1076], [unit_code_1076_help] }
#define    _UNIT_CODE_1077  { 1077, [unit_code_1077], [unit_code_1077_help] }
#define    _UNIT_CODE_1078  { 1078, [unit_code_1078], [unit_code_1078_help] }
#define    _UNIT_CODE_1079  { 1079, [unit_code_1079], [unit_code_1079_help] }
#define    _UNIT_CODE_1080  { 1080, [unit_code_1080], [unit_code_1080_help] }
#define    _UNIT_CODE_1081  { 1081, [unit_code_1081], [unit_code_1081_help] }
#define    _UNIT_CODE_1082  { 1082, [unit_code_1082], [unit_code_1082_help] }
#define    _UNIT_CODE_1083  { 1083, [unit_code_1083], [unit_code_1083_help] }
#define    _UNIT_CODE_1084  { 1084, [unit_code_1084], [unit_code_1084_help] }
#define    _UNIT_CODE_1085  { 1085, [unit_code_1085], [unit_code_1085_help] }
#define    _UNIT_CODE_1086  { 1086, [unit_code_1086], [unit_code_1086_help] }
#define    _UNIT_CODE_1087  { 1087, [unit_code_1087], [unit_code_1087_help] }
#define    _UNIT_CODE_1088  { 1088, [unit_code_1088], [unit_code_1088_help] }
#define    _UNIT_CODE_1089  { 1089, [unit_code_1089], [unit_code_1089_help] }
#define    _UNIT_CODE_1090  { 1090, [unit_code_1090], [unit_code_1090_help] }
#define    _UNIT_CODE_1091  { 1091, [unit_code_1091], [unit_code_1091_help] }
#define    _UNIT_CODE_1092  { 1092, [unit_code_1092], [unit_code_1092_help] }
#define    _UNIT_CODE_1093  { 1093, [unit_code_1093], [unit_code_1093_help] }
#define    _UNIT_CODE_1094  { 1094, [unit_code_1094], [unit_code_1094_help] }
#define    _UNIT_CODE_1095  { 1095, [unit_code_1095], [unit_code_1095_help] }
#define    _UNIT_CODE_1096  { 1096, [unit_code_1096], [unit_code_1096_help] }
#define    _UNIT_CODE_1097  { 1097, [unit_code_1097], [unit_code_1097_help] }
#define    _UNIT_CODE_1098  { 1098, [unit_code_1098], [unit_code_1098_help] }
#define    _UNIT_CODE_1099  { 1099, [unit_code_1099], [unit_code_1099_help] }
#define    _UNIT_CODE_1100  { 1100, [unit_code_1100], [unit_code_1100_help] }
#define    _UNIT_CODE_1101  { 1101, [unit_code_1101], [unit_code_1101_help] }
#define    _UNIT_CODE_1102  { 1102, [unit_code_1102], [unit_code_1102_help] }
#define    _UNIT_CODE_1103  { 1103, [unit_code_1103], [unit_code_1103_help] }
#define    _UNIT_CODE_1104  { 1104, [unit_code_1104], [unit_code_1104_help] }
#define    _UNIT_CODE_1105  { 1105, [unit_code_1105], [unit_code_1105_help] }
#define    _UNIT_CODE_1106  { 1106, [unit_code_1106], [unit_code_1106_help] }
#define    _UNIT_CODE_1107  { 1107, [unit_code_1107], [unit_code_1107_help] }
#define    _UNIT_CODE_1108  { 1108, [unit_code_1108], [unit_code_1108_help] }
#define    _UNIT_CODE_1109  { 1109, [unit_code_1109], [unit_code_1109_help] }
#define    _UNIT_CODE_1110  { 1110, [unit_code_1110], [unit_code_1110_help] }
#define    _UNIT_CODE_1111  { 1111, [unit_code_1111], [unit_code_1111_help] }
#define    _UNIT_CODE_1112  { 1112, [unit_code_1112], [unit_code_1112_help] }
#define    _UNIT_CODE_1113  { 1113, [unit_code_1113], [unit_code_1113_help] }
#define    _UNIT_CODE_1114  { 1114, [unit_code_1114], [unit_code_1114_help] }
#define    _UNIT_CODE_1115  { 1115, [unit_code_1115], [unit_code_1115_help] }
#define    _UNIT_CODE_1116  { 1116, [unit_code_1116], [unit_code_1116_help] }
#define    _UNIT_CODE_1117  { 1117, [unit_code_1117], [unit_code_1117_help] }
#define    _UNIT_CODE_1118  { 1118, [unit_code_1118], [unit_code_1118_help] }
#define    _UNIT_CODE_1119  { 1119, [unit_code_1119], [unit_code_1119_help] }
#define    _UNIT_CODE_1120  { 1120, [unit_code_1120], [unit_code_1120_help] }
#define    _UNIT_CODE_1121  { 1121, [unit_code_1121], [unit_code_1121_help] }
#define    _UNIT_CODE_1122  { 1122, [unit_code_1122], [unit_code_1122_help] }
#define    _UNIT_CODE_1123  { 1123, [unit_code_1123], [unit_code_1123_help] }
#define    _UNIT_CODE_1124  { 1124, [unit_code_1124], [unit_code_1124_help] }
#define    _UNIT_CODE_1125  { 1125, [unit_code_1125], [unit_code_1125_help] }
#define    _UNIT_CODE_1126  { 1126, [unit_code_1126], [unit_code_1126_help] }
#define    _UNIT_CODE_1127  { 1127, [unit_code_1127], [unit_code_1127_help] }
#define    _UNIT_CODE_1128  { 1128, [unit_code_1128], [unit_code_1128_help] }
#define    _UNIT_CODE_1129  { 1129, [unit_code_1129], [unit_code_1129_help] }
#define    _UNIT_CODE_1130  { 1130, [unit_code_1130], [unit_code_1130_help] }
#define    _UNIT_CODE_1131  { 1131, [unit_code_1131], [unit_code_1131_help] }
#define    _UNIT_CODE_1132  { 1132, [unit_code_1132], [unit_code_1132_help] }
#define    _UNIT_CODE_1133  { 1133, [unit_code_1133], [unit_code_1133_help] }
#define    _UNIT_CODE_1134  { 1134, [unit_code_1134], [unit_code_1134_help] }
#define    _UNIT_CODE_1135  { 1135, [unit_code_1135], [unit_code_1135_help] }
#define    _UNIT_CODE_1136  { 1136, [unit_code_1136], [unit_code_1136_help] }
#define    _UNIT_CODE_1137  { 1137, [unit_code_1137], [unit_code_1137_help] }
#define    _UNIT_CODE_1138  { 1138, [unit_code_1138], [unit_code_1138_help] }
#define    _UNIT_CODE_1139  { 1139, [unit_code_1139], [unit_code_1139_help] }
#define    _UNIT_CODE_1140  { 1140, [unit_code_1140], [unit_code_1140_help] }
#define    _UNIT_CODE_1141  { 1141, [unit_code_1141], [unit_code_1141_help] }
#define    _UNIT_CODE_1142  { 1142, [unit_code_1142], [unit_code_1142_help] }
#define    _UNIT_CODE_1143  { 1143, [unit_code_1143], [unit_code_1143_help] }
#define    _UNIT_CODE_1144  { 1144, [unit_code_1144], [unit_code_1144_help] }
#define    _UNIT_CODE_1145  { 1145, [unit_code_1145], [unit_code_1145_help] }
#define    _UNIT_CODE_1146  { 1146, [unit_code_1146], [unit_code_1146_help] }
#define    _UNIT_CODE_1147  { 1147, [unit_code_1147], [unit_code_1147_help] }
#define    _UNIT_CODE_1148  { 1148, [unit_code_1148], [unit_code_1148_help] }
#define    _UNIT_CODE_1149  { 1149, [unit_code_1149], [unit_code_1149_help] }
#define    _UNIT_CODE_1150  { 1150, [unit_code_1150], [unit_code_1150_help] }
#define    _UNIT_CODE_1151  { 1151, [unit_code_1151], [unit_code_1151_help] }
#define    _UNIT_CODE_1152  { 1152, [unit_code_1152], [unit_code_1152_help] }
#define    _UNIT_CODE_1153  { 1153, [unit_code_1153], [unit_code_1153_help] }
#define    _UNIT_CODE_1154  { 1154, [unit_code_1154], [unit_code_1154_help] }
#define    _UNIT_CODE_1155  { 1155, [unit_code_1155], [unit_code_1155_help] }
#define    _UNIT_CODE_1156  { 1156, [unit_code_1156], [unit_code_1156_help] }
#define    _UNIT_CODE_1157  { 1157, [unit_code_1157], [unit_code_1157_help] }
#define    _UNIT_CODE_1158  { 1158, [unit_code_1158], [unit_code_1158_help] }
#define    _UNIT_CODE_1159  { 1159, [unit_code_1159], [unit_code_1159_help] }
#define    _UNIT_CODE_1160  { 1160, [unit_code_1160], [unit_code_1160_help] }
#define    _UNIT_CODE_1161  { 1161, [unit_code_1161], [unit_code_1161_help] }
#define    _UNIT_CODE_1162  { 1162, [unit_code_1162], [unit_code_1162_help] }
#define    _UNIT_CODE_1163  { 1163, [unit_code_1163], [unit_code_1163_help] }
#define    _UNIT_CODE_1164  { 1164, [unit_code_1164], [unit_code_1164_help] }
#define    _UNIT_CODE_1165  { 1165, [unit_code_1165], [unit_code_1165_help] }
#define    _UNIT_CODE_1166  { 1166, [unit_code_1166], [unit_code_1166_help] }
#define    _UNIT_CODE_1167  { 1167, [unit_code_1167], [unit_code_1167_help] }
#define    _UNIT_CODE_1168  { 1168, [unit_code_1168], [unit_code_1168_help] }
#define    _UNIT_CODE_1169  { 1169, [unit_code_1169], [unit_code_1169_help] }
#define    _UNIT_CODE_1170  { 1170, [unit_code_1170], [unit_code_1170_help] }
#define    _UNIT_CODE_1171  { 1171, [unit_code_1171], [unit_code_1171_help] }
#define    _UNIT_CODE_1172  { 1172, [unit_code_1172], [unit_code_1172_help] }
#define    _UNIT_CODE_1173  { 1173, [unit_code_1173], [unit_code_1173_help] }
#define    _UNIT_CODE_1174  { 1174, [unit_code_1174], [unit_code_1174_help] }
#define    _UNIT_CODE_1175  { 1175, [unit_code_1175], [unit_code_1175_help] }
#define    _UNIT_CODE_1176  { 1176, [unit_code_1176], [unit_code_1176_help] }
#define    _UNIT_CODE_1177  { 1177, [unit_code_1177], [unit_code_1177_help] }
#define    _UNIT_CODE_1178  { 1178, [unit_code_1178], [unit_code_1178_help] }
#define    _UNIT_CODE_1179  { 1179, [unit_code_1179], [unit_code_1179_help] }
#define    _UNIT_CODE_1180  { 1180, [unit_code_1180], [unit_code_1180_help] }
#define    _UNIT_CODE_1181  { 1181, [unit_code_1181], [unit_code_1181_help] }
#define    _UNIT_CODE_1182  { 1182, [unit_code_1182], [unit_code_1182_help] }
#define    _UNIT_CODE_1183  { 1183, [unit_code_1183], [unit_code_1183_help] }
#define    _UNIT_CODE_1184  { 1184, [unit_code_1184], [unit_code_1184_help] }
#define    _UNIT_CODE_1185  { 1185, [unit_code_1185], [unit_code_1185_help] }
#define    _UNIT_CODE_1186  { 1186, [unit_code_1186], [unit_code_1186_help] }
#define    _UNIT_CODE_1187  { 1187, [unit_code_1187], [unit_code_1187_help] }
#define    _UNIT_CODE_1188  { 1188, [unit_code_1188], [unit_code_1188_help] }
#define    _UNIT_CODE_1189  { 1189, [unit_code_1189], [unit_code_1189_help] }
#define    _UNIT_CODE_1190  { 1190, [unit_code_1190], [unit_code_1190_help] }
#define    _UNIT_CODE_1191  { 1191, [unit_code_1191], [unit_code_1191_help] }
#define    _UNIT_CODE_1192  { 1192, [unit_code_1192], [unit_code_1192_help] }
#define    _UNIT_CODE_1193  { 1193, [unit_code_1193], [unit_code_1193_help] }
#define    _UNIT_CODE_1194  { 1194, [unit_code_1194], [unit_code_1194_help] }
#define    _UNIT_CODE_1195  { 1195, [unit_code_1195], [unit_code_1195_help] }
#define    _UNIT_CODE_1196  { 1196, [unit_code_1196], [unit_code_1196_help] }
#define    _UNIT_CODE_1197  { 1197, [unit_code_1197], [unit_code_1197_help] }
#define    _UNIT_CODE_1198  { 1198, [unit_code_1198], [unit_code_1198_help] }
#define    _UNIT_CODE_1199  { 1199, [unit_code_1199], [unit_code_1199_help] }
#define    _UNIT_CODE_1200  { 1200, [unit_code_1200], [unit_code_1200_help] }
#define    _UNIT_CODE_1201  { 1201, [unit_code_1201], [unit_code_1201_help] }
#define    _UNIT_CODE_1202  { 1202, [unit_code_1202], [unit_code_1202_help] }
#define    _UNIT_CODE_1203  { 1203, [unit_code_1203], [unit_code_1203_help] }
#define    _UNIT_CODE_1204  { 1204, [unit_code_1204], [unit_code_1204_help] }
#define    _UNIT_CODE_1205  { 1205, [unit_code_1205], [unit_code_1205_help] }
#define    _UNIT_CODE_1206  { 1206, [unit_code_1206], [unit_code_1206_help] }
#define    _UNIT_CODE_1207  { 1207, [unit_code_1207], [unit_code_1207_help] }
#define    _UNIT_CODE_1208  { 1208, [unit_code_1208], [unit_code_1208_help] }
#define    _UNIT_CODE_1209  { 1209, [unit_code_1209], [unit_code_1209_help] }
#define    _UNIT_CODE_1210  { 1210, [unit_code_1210], [unit_code_1210_help] }
#define    _UNIT_CODE_1211  { 1211, [unit_code_1211], [unit_code_1211_help] }
#define    _UNIT_CODE_1212  { 1212, [unit_code_1212], [unit_code_1212_help] }
#define    _UNIT_CODE_1213  { 1213, [unit_code_1213], [unit_code_1213_help] }
#define    _UNIT_CODE_1214  { 1214, [unit_code_1214], [unit_code_1214_help] }
#define    _UNIT_CODE_1215  { 1215, [unit_code_1215], [unit_code_1215_help] }
#define    _UNIT_CODE_1216  { 1216, [unit_code_1216], [unit_code_1216_help] }
#define    _UNIT_CODE_1217  { 1217, [unit_code_1217], [unit_code_1217_help] }
#define    _UNIT_CODE_1218  { 1218, [unit_code_1218], [unit_code_1218_help] }
#define    _UNIT_CODE_1219  { 1219, [unit_code_1219], [unit_code_1219_help] }
#define    _UNIT_CODE_1220  { 1220, [unit_code_1220], [unit_code_1220_help] }
#define    _UNIT_CODE_1221  { 1221, [unit_code_1221], [unit_code_1221_help] }
#define    _UNIT_CODE_1222  { 1222, [unit_code_1222], [unit_code_1222_help] }
#define    _UNIT_CODE_1223  { 1223, [unit_code_1223], [unit_code_1223_help] }
#define    _UNIT_CODE_1224  { 1224, [unit_code_1224], [unit_code_1224_help] }
#define    _UNIT_CODE_1225  { 1225, [unit_code_1225], [unit_code_1225_help] }
#define    _UNIT_CODE_1226  { 1226, [unit_code_1226], [unit_code_1226_help] }
#define    _UNIT_CODE_1227  { 1227, [unit_code_1227], [unit_code_1227_help] }
#define    _UNIT_CODE_1228  { 1228, [unit_code_1228], [unit_code_1228_help] }
#define    _UNIT_CODE_1229  { 1229, [unit_code_1229], [unit_code_1229_help] }
#define    _UNIT_CODE_1230  { 1230, [unit_code_1230], [unit_code_1230_help] }
#define    _UNIT_CODE_1231  { 1231, [unit_code_1231], [unit_code_1231_help] }
#define    _UNIT_CODE_1232  { 1232, [unit_code_1232], [unit_code_1232_help] }
#define    _UNIT_CODE_1233  { 1233, [unit_code_1233], [unit_code_1233_help] }
#define    _UNIT_CODE_1234  { 1234, [unit_code_1234], [unit_code_1234_help] }
#define    _UNIT_CODE_1235  { 1235, [unit_code_1235], [unit_code_1235_help] }
#define    _UNIT_CODE_1236  { 1236, [unit_code_1236], [unit_code_1236_help] }
#define    _UNIT_CODE_1237  { 1237, [unit_code_1237], [unit_code_1237_help] }
#define    _UNIT_CODE_1238  { 1238, [unit_code_1238], [unit_code_1238_help] }
#define    _UNIT_CODE_1239  { 1239, [unit_code_1239], [unit_code_1239_help] }
#define    _UNIT_CODE_1240  { 1240, [unit_code_1240], [unit_code_1240_help] }
#define    _UNIT_CODE_1241  { 1241, [unit_code_1241], [unit_code_1241_help] }
#define    _UNIT_CODE_1242  { 1242, [unit_code_1242], [unit_code_1242_help] }
#define    _UNIT_CODE_1243  { 1243, [unit_code_1243], [unit_code_1243_help] }
#define    _UNIT_CODE_1244  { 1244, [unit_code_1244], [unit_code_1244_help] }
#define    _UNIT_CODE_1245  { 1245, [unit_code_1245], [unit_code_1245_help] }
#define    _UNIT_CODE_1246  { 1246, [unit_code_1246], [unit_code_1246_help] }
#define    _UNIT_CODE_1247  { 1247, [unit_code_1247], [unit_code_1247_help] }
#define    _UNIT_CODE_1248  { 1248, [unit_code_1248], [unit_code_1248_help] }
#define    _UNIT_CODE_1249  { 1249, [unit_code_1249], [unit_code_1249_help] }
#define    _UNIT_CODE_1250  { 1250, [unit_code_1250], [unit_code_1250_help] }
#define    _UNIT_CODE_1251  { 1251, [unit_code_1251], [unit_code_1251_help] }
#define    _UNIT_CODE_1252  { 1252, [unit_code_1252], [unit_code_1252_help] }
#define    _UNIT_CODE_1253  { 1253, [unit_code_1253], [unit_code_1253_help] }
#define    _UNIT_CODE_1254  { 1254, [unit_code_1254], [unit_code_1254_help] }
#define    _UNIT_CODE_1255  { 1255, [unit_code_1255], [unit_code_1255_help] }
#define    _UNIT_CODE_1256  { 1256, [unit_code_1256], [unit_code_1256_help] }
#define    _UNIT_CODE_1257  { 1257, [unit_code_1257], [unit_code_1257_help] }
#define    _UNIT_CODE_1258  { 1258, [unit_code_1258], [unit_code_1258_help] }
#define    _UNIT_CODE_1259  { 1259, [unit_code_1259], [unit_code_1259_help] }
#define    _UNIT_CODE_1260  { 1260, [unit_code_1260], [unit_code_1260_help] }
#define    _UNIT_CODE_1261  { 1261, [unit_code_1261], [unit_code_1261_help] }
#define    _UNIT_CODE_1262  { 1262, [unit_code_1262], [unit_code_1262_help] }
#define    _UNIT_CODE_1263  { 1263, [unit_code_1263], [unit_code_1263_help] }
#define    _UNIT_CODE_1264  { 1264, [unit_code_1264], [unit_code_1264_help] }
#define    _UNIT_CODE_1265  { 1265, [unit_code_1265], [unit_code_1265_help] }
#define    _UNIT_CODE_1266  { 1266, [unit_code_1266], [unit_code_1266_help] }
#define    _UNIT_CODE_1267  { 1267, [unit_code_1267], [unit_code_1267_help] }
#define    _UNIT_CODE_1268  { 1268, [unit_code_1268], [unit_code_1268_help] }
#define    _UNIT_CODE_1269  { 1269, [unit_code_1269], [unit_code_1269_help] }
#define    _UNIT_CODE_1270  { 1270, [unit_code_1270], [unit_code_1270_help] }
#define    _UNIT_CODE_1271  { 1271, [unit_code_1271], [unit_code_1271_help] }
#define    _UNIT_CODE_1272  { 1272, [unit_code_1272], [unit_code_1272_help] }
#define    _UNIT_CODE_1273  { 1273, [unit_code_1273], [unit_code_1273_help] }
#define    _UNIT_CODE_1274  { 1274, [unit_code_1274], [unit_code_1274_help] }
#define    _UNIT_CODE_1275  { 1275, [unit_code_1275], [unit_code_1275_help] }
#define    _UNIT_CODE_1276  { 1276, [unit_code_1276], [unit_code_1276_help] }
#define    _UNIT_CODE_1277  { 1277, [unit_code_1277], [unit_code_1277_help] }
#define    _UNIT_CODE_1278  { 1278, [unit_code_1278], [unit_code_1278_help] }
#define    _UNIT_CODE_1279  { 1279, [unit_code_1279], [unit_code_1279_help] }
#define    _UNIT_CODE_1280  { 1280, [unit_code_1280], [unit_code_1280_help] }
#define    _UNIT_CODE_1281  { 1281, [unit_code_1281], [unit_code_1281_help] }
#define    _UNIT_CODE_1282  { 1282, [unit_code_1282], [unit_code_1282_help] }
#define    _UNIT_CODE_1283  { 1283, [unit_code_1283], [unit_code_1283_help] }
#define    _UNIT_CODE_1284  { 1284, [unit_code_1284], [unit_code_1284_help] }
#define    _UNIT_CODE_1285  { 1285, [unit_code_1285], [unit_code_1285_help] }
#define    _UNIT_CODE_1286  { 1286, [unit_code_1286], [unit_code_1286_help] }
#define    _UNIT_CODE_1287  { 1287, [unit_code_1287], [unit_code_1287_help] }
#define    _UNIT_CODE_1288  { 1288, [unit_code_1288], [unit_code_1288_help] }
#define    _UNIT_CODE_1289  { 1289, [unit_code_1289], [unit_code_1289_help] }
#define    _UNIT_CODE_1290  { 1290, [unit_code_1290], [unit_code_1290_help] }
#define    _UNIT_CODE_1291  { 1291, [unit_code_1291], [unit_code_1291_help] }
#define    _UNIT_CODE_1292  { 1292, [unit_code_1292], [unit_code_1292_help] }
#define    _UNIT_CODE_1293  { 1293, [unit_code_1293], [unit_code_1293_help] }
#define    _UNIT_CODE_1294  { 1294, [unit_code_1294], [unit_code_1294_help] }
#define    _UNIT_CODE_1295  { 1295, [unit_code_1295], [unit_code_1295_help] }
#define    _UNIT_CODE_1296  { 1296, [unit_code_1296], [unit_code_1296_help] }
#define    _UNIT_CODE_1297  { 1297, [unit_code_1297], [unit_code_1297_help] }
#define    _UNIT_CODE_1298  { 1298, [unit_code_1298], [unit_code_1298_help] }
#define    _UNIT_CODE_1299  { 1299, [unit_code_1299], [unit_code_1299_help] }
#define    _UNIT_CODE_1300  { 1300, [unit_code_1300], [unit_code_1300_help] }
#define    _UNIT_CODE_1301  { 1301, [unit_code_1301], [unit_code_1301_help] }
#define    _UNIT_CODE_1302  { 1302, [unit_code_1302], [unit_code_1302_help] }
#define    _UNIT_CODE_1303  { 1303, [unit_code_1303], [unit_code_1303_help] }
#define    _UNIT_CODE_1304  { 1304, [unit_code_1304], [unit_code_1304_help] }
#define    _UNIT_CODE_1305  { 1305, [unit_code_1305], [unit_code_1305_help] }
#define    _UNIT_CODE_1306  { 1306, [unit_code_1306], [unit_code_1306_help] }
#define    _UNIT_CODE_1307  { 1307, [unit_code_1307], [unit_code_1307_help] }
#define    _UNIT_CODE_1308  { 1308, [unit_code_1308], [unit_code_1308_help] }
#define    _UNIT_CODE_1309  { 1309, [unit_code_1309], [unit_code_1309_help] }
#define    _UNIT_CODE_1310  { 1310, [unit_code_1310], [unit_code_1310_help] }
#define    _UNIT_CODE_1311  { 1311, [unit_code_1311], [unit_code_1311_help] }
#define    _UNIT_CODE_1312  { 1312, [unit_code_1312], [unit_code_1312_help] }
#define    _UNIT_CODE_1313  { 1313, [unit_code_1313], [unit_code_1313_help] }
#define    _UNIT_CODE_1314  { 1314, [unit_code_1314], [unit_code_1314_help] }
#define    _UNIT_CODE_1315  { 1315, [unit_code_1315], [unit_code_1315_help] }
#define    _UNIT_CODE_1316  { 1316, [unit_code_1316], [unit_code_1316_help] }
#define    _UNIT_CODE_1317  { 1317, [unit_code_1317], [unit_code_1317_help] }
#define    _UNIT_CODE_1318  { 1318, [unit_code_1318], [unit_code_1318_help] }
#define    _UNIT_CODE_1319  { 1319, [unit_code_1319], [unit_code_1319_help] }
#define    _UNIT_CODE_1320  { 1320, [unit_code_1320], [unit_code_1320_help] }
#define    _UNIT_CODE_1321  { 1321, [unit_code_1321], [unit_code_1321_help] }
#define    _UNIT_CODE_1322  { 1322, [unit_code_1322], [unit_code_1322_help] }
#define    _UNIT_CODE_1323  { 1323, [unit_code_1323], [unit_code_1323_help] }
#define    _UNIT_CODE_1324  { 1324, [unit_code_1324], [unit_code_1324_help] }
#define    _UNIT_CODE_1325  { 1325, [unit_code_1325], [unit_code_1325_help] }
#define    _UNIT_CODE_1326  { 1326, [unit_code_1326], [unit_code_1326_help] }
#define    _UNIT_CODE_1327  { 1327, [unit_code_1327], [unit_code_1327_help] }
#define    _UNIT_CODE_1328  { 1328, [unit_code_1328], [unit_code_1328_help] }
#define    _UNIT_CODE_1329  { 1329, [unit_code_1329], [unit_code_1329_help] }
#define    _UNIT_CODE_1330  { 1330, [unit_code_1330], [unit_code_1330_help] }
#define    _UNIT_CODE_1331  { 1331, [unit_code_1331], [unit_code_1331_help] }
#define    _UNIT_CODE_1332  { 1332, [unit_code_1332], [unit_code_1332_help] }
#define    _UNIT_CODE_1333  { 1333, [unit_code_1333], [unit_code_1333_help] }
#define    _UNIT_CODE_1334  { 1334, [unit_code_1334], [unit_code_1334_help] }
#define    _UNIT_CODE_1335  { 1335, [unit_code_1335], [unit_code_1335_help] }
#define    _UNIT_CODE_1336  { 1336, [unit_code_1336], [unit_code_1336_help] }
#define    _UNIT_CODE_1337  { 1337, [unit_code_1337], [unit_code_1337_help] }
#define    _UNIT_CODE_1338  { 1338, [unit_code_1338], [unit_code_1338_help] }
#define    _UNIT_CODE_1339  { 1339, [unit_code_1339], [unit_code_1339_help] }
#define    _UNIT_CODE_1340  { 1340, [unit_code_1340], [unit_code_1340_help] }
#define    _UNIT_CODE_1341  { 1341, [unit_code_1341], [unit_code_1341_help] }
#define    _UNIT_CODE_1342  { 1342, [unit_code_1342], [unit_code_1342_help] }
#define    _UNIT_CODE_1343  { 1343, [unit_code_1343], [unit_code_1343_help] }
#define    _UNIT_CODE_1344  { 1344, [unit_code_1344], [unit_code_1344_help] }
#define    _UNIT_CODE_1345  { 1345, [unit_code_1345], [unit_code_1345_help] }
#define    _UNIT_CODE_1346  { 1346, [unit_code_1346], [unit_code_1346_help] }
#define    _UNIT_CODE_1347  { 1347, [unit_code_1347], [unit_code_1347_help] }
#define    _UNIT_CODE_1348  { 1348, [unit_code_1348], [unit_code_1348_help] }
#define    _UNIT_CODE_1349  { 1349, [unit_code_1349], [unit_code_1349_help] }
#define    _UNIT_CODE_1350  { 1350, [unit_code_1350], [unit_code_1350_help] }
#define    _UNIT_CODE_1351  { 1351, [unit_code_1351], [unit_code_1351_help] }
#define    _UNIT_CODE_1352  { 1352, [unit_code_1352], [unit_code_1352_help] }
#define    _UNIT_CODE_1353  { 1353, [unit_code_1353], [unit_code_1353_help] }
#define    _UNIT_CODE_1354  { 1354, [unit_code_1354], [unit_code_1354_help] }
#define    _UNIT_CODE_1355  { 1355, [unit_code_1355], [unit_code_1355_help] }
#define    _UNIT_CODE_1356  { 1356, [unit_code_1356], [unit_code_1356_help] }
#define    _UNIT_CODE_1357  { 1357, [unit_code_1357], [unit_code_1357_help] }
#define    _UNIT_CODE_1358  { 1358, [unit_code_1358], [unit_code_1358_help] }
#define    _UNIT_CODE_1359  { 1359, [unit_code_1359], [unit_code_1359_help] }
#define    _UNIT_CODE_1360  { 1360, [unit_code_1360], [unit_code_1360_help] }
#define    _UNIT_CODE_1361  { 1361, [unit_code_1361], [unit_code_1361_help] }
#define    _UNIT_CODE_1362  { 1362, [unit_code_1362], [unit_code_1362_help] }
#define    _UNIT_CODE_1363  { 1363, [unit_code_1363], [unit_code_1363_help] }
#define    _UNIT_CODE_1364  { 1364, [unit_code_1364], [unit_code_1364_help] }
#define    _UNIT_CODE_1365  { 1365, [unit_code_1365], [unit_code_1365_help] }
#define    _UNIT_CODE_1366  { 1366, [unit_code_1366], [unit_code_1366_help] }
#define    _UNIT_CODE_1367  { 1367, [unit_code_1367], [unit_code_1367_help] }
#define    _UNIT_CODE_1368  { 1368, [unit_code_1368], [unit_code_1368_help] }
#define    _UNIT_CODE_1369  { 1369, [unit_code_1369], [unit_code_1369_help] }
#define    _UNIT_CODE_1370  { 1370, [unit_code_1370], [unit_code_1370_help] }
#define    _UNIT_CODE_1371  { 1371, [unit_code_1371], [unit_code_1371_help] }
#define    _UNIT_CODE_1372  { 1372, [unit_code_1372], [unit_code_1372_help] }
#define    _UNIT_CODE_1373  { 1373, [unit_code_1373], [unit_code_1373_help] }
#define    _UNIT_CODE_1374  { 1374, [unit_code_1374], [unit_code_1374_help] }
#define    _UNIT_CODE_1375  { 1375, [unit_code_1375], [unit_code_1375_help] }
#define    _UNIT_CODE_1376  { 1376, [unit_code_1376], [unit_code_1376_help] }
#define    _UNIT_CODE_1377  { 1377, [unit_code_1377], [unit_code_1377_help] }
#define    _UNIT_CODE_1378  { 1378, [unit_code_1378], [unit_code_1378_help] }
#define    _UNIT_CODE_1379  { 1379, [unit_code_1379], [unit_code_1379_help] }
#define    _UNIT_CODE_1380  { 1380, [unit_code_1380], [unit_code_1380_help] }
#define    _UNIT_CODE_1381  { 1381, [unit_code_1381], [unit_code_1381_help] }
#define    _UNIT_CODE_1382  { 1382, [unit_code_1382], [unit_code_1382_help] }
#define    _UNIT_CODE_1383  { 1383, [unit_code_1383], [unit_code_1383_help] }
#define    _UNIT_CODE_1384  { 1384, [unit_code_1384], [unit_code_1384_help] }
#define    _UNIT_CODE_1385  { 1385, [unit_code_1385], [unit_code_1385_help] }
#define    _UNIT_CODE_1386  { 1386, [unit_code_1386], [unit_code_1386_help] }
#define    _UNIT_CODE_1387  { 1387, [unit_code_1387], [unit_code_1387_help] }
#define    _UNIT_CODE_1388  { 1388, [unit_code_1388], [unit_code_1388_help] }
#define    _UNIT_CODE_1389  { 1389, [unit_code_1389], [unit_code_1389_help] }
#define    _UNIT_CODE_1390  { 1390, [unit_code_1390], [unit_code_1390_help] }
#define    _UNIT_CODE_1391  { 1391, [unit_code_1391], [unit_code_1391_help] }
#define    _UNIT_CODE_1392  { 1392, [unit_code_1392], [unit_code_1392_help] }
#define    _UNIT_CODE_1393  { 1393, [unit_code_1393], [unit_code_1393_help] }
#define    _UNIT_CODE_1394  { 1394, [unit_code_1394], [unit_code_1394_help] }
#define    _UNIT_CODE_1395  { 1395, [unit_code_1395], [unit_code_1395_help] }
#define    _UNIT_CODE_1396  { 1396, [unit_code_1396], [unit_code_1396_help] }
#define    _UNIT_CODE_1397  { 1397, [unit_code_1397], [unit_code_1397_help] }
#define    _UNIT_CODE_1398  { 1398, [unit_code_1398], [unit_code_1398_help] }
#define    _UNIT_CODE_1399  { 1399, [unit_code_1399], [unit_code_1399_help] }
#define    _UNIT_CODE_1400  { 1400, [unit_code_1400], [unit_code_1400_help] }
#define    _UNIT_CODE_1401  { 1401, [unit_code_1401], [unit_code_1401_help] }
#define    _UNIT_CODE_1402  { 1402, [unit_code_1402], [unit_code_1402_help] }
#define    _UNIT_CODE_1403  { 1403, [unit_code_1403], [unit_code_1403_help] }
#define    _UNIT_CODE_1404  { 1404, [unit_code_1404], [unit_code_1404_help] }
#define    _UNIT_CODE_1405  { 1405, [unit_code_1405], [unit_code_1405_help] }
#define    _UNIT_CODE_1406  { 1406, [unit_code_1406], [unit_code_1406_help] }
#define    _UNIT_CODE_1407  { 1407, [unit_code_1407], [unit_code_1407_help] }
#define    _UNIT_CODE_1408  { 1408, [unit_code_1408], [unit_code_1408_help] }
#define    _UNIT_CODE_1409  { 1409, [unit_code_1409], [unit_code_1409_help] }
#define    _UNIT_CODE_1410  { 1410, [unit_code_1410], [unit_code_1410_help] }
#define    _UNIT_CODE_1411  { 1411, [unit_code_1411], [unit_code_1411_help] }
#define    _UNIT_CODE_1412  { 1412, [unit_code_1412], [unit_code_1412_help] }
#define    _UNIT_CODE_1413  { 1413, [unit_code_1413], [unit_code_1413_help] }
#define    _UNIT_CODE_1414  { 1414, [unit_code_1414], [unit_code_1414_help] }
#define    _UNIT_CODE_1415  { 1415, [unit_code_1415], [unit_code_1415_help] }
#define    _UNIT_CODE_1416  { 1416, [unit_code_1416], [unit_code_1416_help] }
#define    _UNIT_CODE_1417  { 1417, [unit_code_1417], [unit_code_1417_help] }
#define    _UNIT_CODE_1418  { 1418, [unit_code_1418], [unit_code_1418_help] }
#define    _UNIT_CODE_1419  { 1419, [unit_code_1419], [unit_code_1419_help] }
#define    _UNIT_CODE_1420  { 1420, [unit_code_1420], [unit_code_1420_help] }
#define    _UNIT_CODE_1421  { 1421, [unit_code_1421], [unit_code_1421_help] }
#define    _UNIT_CODE_1422  { 1422, [unit_code_1422], [unit_code_1422_help] }
#define    _UNIT_CODE_1423  { 1423, [unit_code_1423], [unit_code_1423_help] }
#define    _UNIT_CODE_1424  { 1424, [unit_code_1424], [unit_code_1424_help] }
#define    _UNIT_CODE_1425  { 1425, [unit_code_1425], [unit_code_1425_help] }
#define    _UNIT_CODE_1426  { 1426, [unit_code_1426], [unit_code_1426_help] }
#define    _UNIT_CODE_1427  { 1427, [unit_code_1427], [unit_code_1427_help] }
#define    _UNIT_CODE_1428  { 1428, [unit_code_1428], [unit_code_1428_help] }
#define    _UNIT_CODE_1429  { 1429, [unit_code_1429], [unit_code_1429_help] }
#define    _UNIT_CODE_1430  { 1430, [unit_code_1430], [unit_code_1430_help] }
#define    _UNIT_CODE_1431  { 1431, [unit_code_1431], [unit_code_1431_help] }
#define    _UNIT_CODE_1432  { 1432, [unit_code_1432], [unit_code_1432_help] }
#define    _UNIT_CODE_1433  { 1433, [unit_code_1433], [unit_code_1433_help] }
#define    _UNIT_CODE_1434  { 1434, [unit_code_1434], [unit_code_1434_help] }
#define    _UNIT_CODE_1435  { 1435, [unit_code_1435], [unit_code_1435_help] }
#define    _UNIT_CODE_1436  { 1436, [unit_code_1436], [unit_code_1436_help] }
#define    _UNIT_CODE_1437  { 1437, [unit_code_1437], [unit_code_1437_help] }
#define    _UNIT_CODE_1438  { 1438, [unit_code_1438], [unit_code_1438_help] }
#define    _UNIT_CODE_1439  { 1439, [unit_code_1439], [unit_code_1439_help] }
#define    _UNIT_CODE_1440  { 1440, [unit_code_1440], [unit_code_1440_help] }
#define    _UNIT_CODE_1441  { 1441, [unit_code_1441], [unit_code_1441_help] }
#define    _UNIT_CODE_1442  { 1442, [unit_code_1442], [unit_code_1442_help] }
#define    _UNIT_CODE_1443  { 1443, [unit_code_1443], [unit_code_1443_help] }
#define    _UNIT_CODE_1444  { 1444, [unit_code_1444], [unit_code_1444_help] }
#define    _UNIT_CODE_1445  { 1445, [unit_code_1445], [unit_code_1445_help] }
#define    _UNIT_CODE_1446  { 1446, [unit_code_1446], [unit_code_1446_help] }
#define    _UNIT_CODE_1447  { 1447, [unit_code_1447], [unit_code_1447_help] }
#define    _UNIT_CODE_1448  { 1448, [unit_code_1448], [unit_code_1448_help] }
#define    _UNIT_CODE_1449  { 1449, [unit_code_1449], [unit_code_1449_help] }
#define    _UNIT_CODE_1450  { 1450, [unit_code_1450], [unit_code_1450_help] }
#define    _UNIT_CODE_1451  { 1451, [unit_code_1451], [unit_code_1451_help] }
#define    _UNIT_CODE_1452  { 1452, [unit_code_1452], [unit_code_1452_help] }
#define    _UNIT_CODE_1453  { 1453, [unit_code_1453], [unit_code_1453_help] }
#define    _UNIT_CODE_1454  { 1454, [unit_code_1454], [unit_code_1454_help] }
#define    _UNIT_CODE_1455  { 1455, [unit_code_1455], [unit_code_1455_help] }
#define    _UNIT_CODE_1456  { 1456, [unit_code_1456], [unit_code_1456_help] }
#define    _UNIT_CODE_1457  { 1457, [unit_code_1457], [unit_code_1457_help] }
#define    _UNIT_CODE_1458  { 1458, [unit_code_1458], [unit_code_1458_help] }
#define    _UNIT_CODE_1459  { 1459, [unit_code_1459], [unit_code_1459_help] }
#define    _UNIT_CODE_1460  { 1460, [unit_code_1460], [unit_code_1460_help] }
#define    _UNIT_CODE_1461  { 1461, [unit_code_1461], [unit_code_1461_help] }
#define    _UNIT_CODE_1462  { 1462, [unit_code_1462], [unit_code_1462_help] }
#define    _UNIT_CODE_1463  { 1463, [unit_code_1463], [unit_code_1463_help] }
#define    _UNIT_CODE_1464  { 1464, [unit_code_1464], [unit_code_1464_help] }
#define    _UNIT_CODE_1465  { 1465, [unit_code_1465], [unit_code_1465_help] }
#define    _UNIT_CODE_1466  { 1466, [unit_code_1466], [unit_code_1466_help] }
#define    _UNIT_CODE_1467  { 1467, [unit_code_1467], [unit_code_1467_help] }
#define    _UNIT_CODE_1468  { 1468, [unit_code_1468], [unit_code_1468_help] }
#define    _UNIT_CODE_1469  { 1469, [unit_code_1469], [unit_code_1469_help] }
#define    _UNIT_CODE_1470  { 1470, [unit_code_1470], [unit_code_1470_help] }
#define    _UNIT_CODE_1471  { 1471, [unit_code_1471], [unit_code_1471_help] }
#define    _UNIT_CODE_1472  { 1472, [unit_code_1472], [unit_code_1472_help] }
#define    _UNIT_CODE_1473  { 1473, [unit_code_1473], [unit_code_1473_help] }
#define    _UNIT_CODE_1474  { 1474, [unit_code_1474], [unit_code_1474_help] }
#define    _UNIT_CODE_1475  { 1475, [unit_code_1475], [unit_code_1475_help] }
#define    _UNIT_CODE_1476  { 1476, [unit_code_1476], [unit_code_1476_help] }
#define    _UNIT_CODE_1477  { 1477, [unit_code_1477], [unit_code_1477_help] }
#define    _UNIT_CODE_1478  { 1478, [unit_code_1478], [unit_code_1478_help] }
#define    _UNIT_CODE_1479  { 1479, [unit_code_1479], [unit_code_1479_help] }
#define    _UNIT_CODE_1480  { 1480, [unit_code_1480], [unit_code_1480_help] }
#define    _UNIT_CODE_1481  { 1481, [unit_code_1481], [unit_code_1481_help] }
#define    _UNIT_CODE_1482  { 1482, [unit_code_1482], [unit_code_1482_help] }
#define    _UNIT_CODE_1483  { 1483, [unit_code_1483], [unit_code_1483_help] }
#define    _UNIT_CODE_1484  { 1484, [unit_code_1484], [unit_code_1484_help] }
#define    _UNIT_CODE_1485  { 1485, [unit_code_1485], [unit_code_1485_help] }
#define    _UNIT_CODE_1486  { 1486, [unit_code_1486], [unit_code_1486_help] }
#define    _UNIT_CODE_1487  { 1487, [unit_code_1487], [unit_code_1487_help] }
#define    _UNIT_CODE_1488  { 1488, [unit_code_1488], [unit_code_1488_help] }
#define    _UNIT_CODE_1489  { 1489, [unit_code_1489], [unit_code_1489_help] }
#define    _UNIT_CODE_1490  { 1490, [unit_code_1490], [unit_code_1490_help] }
#define    _UNIT_CODE_1491  { 1491, [unit_code_1491], [unit_code_1491_help] }
#define    _UNIT_CODE_1492  { 1492, [unit_code_1492], [unit_code_1492_help] }
#define    _UNIT_CODE_1493  { 1493, [unit_code_1493], [unit_code_1493_help] }
#define    _UNIT_CODE_1494  { 1494, [unit_code_1494], [unit_code_1494_help] }
#define    _UNIT_CODE_1495  { 1495, [unit_code_1495], [unit_code_1495_help] }
#define    _UNIT_CODE_1496  { 1496, [unit_code_1496], [unit_code_1496_help] }
#define    _UNIT_CODE_1497  { 1497, [unit_code_1497], [unit_code_1497_help] }
#define    _UNIT_CODE_1498  { 1498, [unit_code_1498], [unit_code_1498_help] }
#define    _UNIT_CODE_1499  { 1499, [unit_code_1499], [unit_code_1499_help] }
#define    _UNIT_CODE_1500  { 1500, [unit_code_1500], [unit_code_1500_help] }




#define    _UNIT_CODE_1501  { 1501, [unit_code_1501], [unit_code_1501_help] }
#define    _UNIT_CODE_1502  { 1502, [unit_code_1502], [unit_code_1502_help] }
#define    _UNIT_CODE_1503  { 1503, [unit_code_1503], [unit_code_1503_help] }
#define    _UNIT_CODE_1504  { 1504, [unit_code_1504], [unit_code_1504_help] }
#define    _UNIT_CODE_1505  { 1505, [unit_code_1505], [unit_code_1505_help] }
#define    _UNIT_CODE_1506  { 1506, [unit_code_1506], [unit_code_1506_help] }
#define    _UNIT_CODE_1507  { 1507, [unit_code_1507], [unit_code_1507_help] }
#define    _UNIT_CODE_1508  { 1508, [unit_code_1508], [unit_code_1508_help] }
#define    _UNIT_CODE_1509  { 1509, [unit_code_1509], [unit_code_1509_help] }
#define    _UNIT_CODE_1510  { 1510, [unit_code_1510], [unit_code_1510_help] }
#define    _UNIT_CODE_1511  { 1511, [unit_code_1511], [unit_code_1511_help] }
#define    _UNIT_CODE_1512  { 1512, [unit_code_1512], [unit_code_1512_help] }
#define    _UNIT_CODE_1513  { 1513, [unit_code_1513], [unit_code_1513_help] }
#define    _UNIT_CODE_1514  { 1514, [unit_code_1514], [unit_code_1514_help] }
#define    _UNIT_CODE_1515  { 1515, [unit_code_1515], [unit_code_1515_help] }
#define    _UNIT_CODE_1516  { 1516, [unit_code_1516], [unit_code_1516_help] }
#define    _UNIT_CODE_1517  { 1517, [unit_code_1517], [unit_code_1517_help] }
#define    _UNIT_CODE_1518  { 1518, [unit_code_1518], [unit_code_1518_help] }
#define    _UNIT_CODE_1519  { 1519, [unit_code_1519], [unit_code_1519_help] }
#define    _UNIT_CODE_1520  { 1520, [unit_code_1520], [unit_code_1520_help] }
#define    _UNIT_CODE_1521  { 1521, [unit_code_1521], [unit_code_1521_help] }
#define    _UNIT_CODE_1522  { 1522, [unit_code_1522], [unit_code_1522_help] }
#define    _UNIT_CODE_1523  { 1523, [unit_code_1523], [unit_code_1523_help] }
#define    _UNIT_CODE_1524  { 1524, [unit_code_1524], [unit_code_1524_help] }
#define    _UNIT_CODE_1525  { 1525, [unit_code_1525], [unit_code_1525_help] }
#define    _UNIT_CODE_1526  { 1526, [unit_code_1526], [unit_code_1526_help] }
#define    _UNIT_CODE_1527  { 1527, [unit_code_1527], [unit_code_1527_help] }
#define    _UNIT_CODE_1528  { 1528, [unit_code_1528], [unit_code_1528_help] }
#define    _UNIT_CODE_1529  { 1529, [unit_code_1529], [unit_code_1529_help] }
#define    _UNIT_CODE_1530  { 1530, [unit_code_1530], [unit_code_1530_help] }
#define    _UNIT_CODE_1531  { 1531, [unit_code_1531], [unit_code_1531_help] }
#define    _UNIT_CODE_1532  { 1532, [unit_code_1532], [unit_code_1532_help] }
#define    _UNIT_CODE_1533  { 1533, [unit_code_1533], [unit_code_1533_help] }
#define    _UNIT_CODE_1534  { 1534, [unit_code_1534], [unit_code_1534_help] }
#define    _UNIT_CODE_1535  { 1535, [unit_code_1535], [unit_code_1535_help] }
#define    _UNIT_CODE_1536  { 1536, [unit_code_1536], [unit_code_1536_help] }
#define    _UNIT_CODE_1537  { 1537, [unit_code_1537], [unit_code_1537_help] }
#define    _UNIT_CODE_1538  { 1538, [unit_code_1538], [unit_code_1538_help] }
#define    _UNIT_CODE_1539  { 1539, [unit_code_1539], [unit_code_1539_help] }
#define    _UNIT_CODE_1540  { 1540, [unit_code_1540], [unit_code_1540_help] }
#define    _UNIT_CODE_1541  { 1541, [unit_code_1541], [unit_code_1541_help] }
#define    _UNIT_CODE_1542  { 1542, [unit_code_1542], [unit_code_1542_help] }
#define    _UNIT_CODE_1543  { 1543, [unit_code_1543], [unit_code_1543_help] }
#define    _UNIT_CODE_1544  { 1544, [unit_code_1544], [unit_code_1544_help] }
#define    _UNIT_CODE_1545  { 1545, [unit_code_1545], [unit_code_1545_help] }
#define    _UNIT_CODE_1546  { 1546, [unit_code_1546], [unit_code_1546_help] }
#define    _UNIT_CODE_1547  { 1547, [unit_code_1547], [unit_code_1547_help] }
#define    _UNIT_CODE_1548  { 1548, [unit_code_1548], [unit_code_1548_help] }
#define    _UNIT_CODE_1549  { 1549, [unit_code_1549], [unit_code_1549_help] }
#define    _UNIT_CODE_1550  { 1550, [unit_code_1550], [unit_code_1550_help] }
#define    _UNIT_CODE_1551  { 1551, [unit_code_1551], [unit_code_1551_help] }
#define    _UNIT_CODE_1552  { 1552, [unit_code_1552], [unit_code_1552_help] }
#define    _UNIT_CODE_1553  { 1553, [unit_code_1553], [unit_code_1553_help] }
#define    _UNIT_CODE_1554  { 1554, [unit_code_1554], [unit_code_1554_help] }
#define    _UNIT_CODE_1555  { 1555, [unit_code_1555], [unit_code_1555_help] }
#define    _UNIT_CODE_1556  { 1556, [unit_code_1556], [unit_code_1556_help] }
#define    _UNIT_CODE_1557  { 1557, [unit_code_1557], [unit_code_1557_help] }
#define    _UNIT_CODE_1558  { 1558, [unit_code_1558], [unit_code_1558_help] }
#define    _UNIT_CODE_1559  { 1559, [unit_code_1559], [unit_code_1559_help] }
#define    _UNIT_CODE_1560  { 1560, [unit_code_1560], [unit_code_1560_help] }
#define    _UNIT_CODE_1561  { 1561, [unit_code_1561], [unit_code_1561_help] }
#define    _UNIT_CODE_1562  { 1562, [unit_code_1562], [unit_code_1562_help] }
#define    _UNIT_CODE_1563  { 1563, [unit_code_1563], [unit_code_1563_help] }
#define    _UNIT_CODE_1564  { 1564, [unit_code_1564], [unit_code_1564_help] }
#define    _UNIT_CODE_1565  { 1565, [unit_code_1565], [unit_code_1565_help] }
#define    _UNIT_CODE_1566  { 1566, [unit_code_1566], [unit_code_1566_help] }
#define    _UNIT_CODE_1567  { 1567, [unit_code_1567], [unit_code_1567_help] }
#define    _UNIT_CODE_1568  { 1568, [unit_code_1568], [unit_code_1568_help] }
#define    _UNIT_CODE_1569  { 1569, [unit_code_1569], [unit_code_1569_help] }
#define    _UNIT_CODE_1570  { 1570, [unit_code_1570], [unit_code_1570_help] }
#define    _UNIT_CODE_1571  { 1571, [unit_code_1571], [unit_code_1571_help] }
#define    _UNIT_CODE_1572  { 1572, [unit_code_1572], [unit_code_1572_help] }
#define    _UNIT_CODE_1573  { 1573, [unit_code_1573], [unit_code_1573_help] }
#define    _UNIT_CODE_1574  { 1574, [unit_code_1574], [unit_code_1574_help] }
#define    _UNIT_CODE_1575  { 1575, [unit_code_1575], [unit_code_1575_help] }
#define    _UNIT_CODE_1576  { 1576, [unit_code_1576], [unit_code_1576_help] }
#define    _UNIT_CODE_1577  { 1577, [unit_code_1577], [unit_code_1577_help] }
#define    _UNIT_CODE_1578  { 1578, [unit_code_1578], [unit_code_1578_help] }
#define    _UNIT_CODE_1579  { 1579, [unit_code_1579], [unit_code_1579_help] }
#define    _UNIT_CODE_1580  { 1580, [unit_code_1580], [unit_code_1580_help] }
#define    _UNIT_CODE_1581  { 1581, [unit_code_1581], [unit_code_1581_help] }
#define    _UNIT_CODE_1582  { 1582, [unit_code_1582], [unit_code_1582_help] }
#define    _UNIT_CODE_1583  { 1583, [unit_code_1583], [unit_code_1583_help] }
#define    _UNIT_CODE_1584  { 1584, [unit_code_1584], [unit_code_1584_help] }

/* unit codes 1585 - 1600 are spares, with stub strings in STANDARD.DCT */
#define    _UNIT_CODE_1585  { 1585, [unit_code_1585], [unit_code_1585_help] }
#define    _UNIT_CODE_1586  { 1586, [unit_code_1586], [unit_code_1586_help] }
#define    _UNIT_CODE_1587  { 1587, [unit_code_1587], [unit_code_1587_help] }
#define    _UNIT_CODE_1588  { 1588, [unit_code_1588], [unit_code_1588_help] }
#define    _UNIT_CODE_1589  { 1589, [unit_code_1589], [unit_code_1589_help] }
#define    _UNIT_CODE_1590  { 1590, [unit_code_1590], [unit_code_1590_help] }
#define    _UNIT_CODE_1591  { 1591, [unit_code_1591], [unit_code_1591_help] }
#define    _UNIT_CODE_1592  { 1592, [unit_code_1592], [unit_code_1592_help] }
#define    _UNIT_CODE_1593  { 1593, [unit_code_1593], [unit_code_1593_help] }
#define    _UNIT_CODE_1594  { 1594, [unit_code_1594], [unit_code_1594_help] }
#define    _UNIT_CODE_1595  { 1595, [unit_code_1595], [unit_code_1595_help] }
#define    _UNIT_CODE_1596  { 1596, [unit_code_1596], [unit_code_1596_help] }
#define    _UNIT_CODE_1597  { 1597, [unit_code_1597], [unit_code_1597_help] }
#define    _UNIT_CODE_1598  { 1598, [unit_code_1598], [unit_code_1598_help] }
#define    _UNIT_CODE_1599  { 1599, [unit_code_1599], [unit_code_1599_help] }
#define    _UNIT_CODE_1600  { 1600, [unit_code_1600], [unit_code_1600_help] }

/* unit codes 1601 - 1645 are described in STANDARD.DCT */
#define    _UNIT_CODE_1601  { 1601, [unit_code_1601], [unit_code_1601_help] }
#define    _UNIT_CODE_1602  { 1602, [unit_code_1602], [unit_code_1602_help] }
#define    _UNIT_CODE_1603  { 1603, [unit_code_1603], [unit_code_1603_help] }
#define    _UNIT_CODE_1604  { 1604, [unit_code_1604], [unit_code_1604_help] }
#define    _UNIT_CODE_1605  { 1605, [unit_code_1605], [unit_code_1605_help] }
#define    _UNIT_CODE_1606  { 1606, [unit_code_1606], [unit_code_1606_help] }
#define    _UNIT_CODE_1607  { 1607, [unit_code_1607], [unit_code_1607_help] }
#define    _UNIT_CODE_1608  { 1608, [unit_code_1608], [unit_code_1608_help] }
#define    _UNIT_CODE_1609  { 1609, [unit_code_1609], [unit_code_1609_help] }
#define    _UNIT_CODE_1610  { 1610, [unit_code_1610], [unit_code_1610_help] }
#define    _UNIT_CODE_1611  { 1611, [unit_code_1611], [unit_code_1611_help] }
#define    _UNIT_CODE_1612  { 1612, [unit_code_1612], [unit_code_1612_help] }
#define    _UNIT_CODE_1613  { 1613, [unit_code_1613], [unit_code_1613_help] }
#define    _UNIT_CODE_1614  { 1614, [unit_code_1614], [unit_code_1614_help] }
#define    _UNIT_CODE_1615  { 1615, [unit_code_1615], [unit_code_1615_help] }
#define    _UNIT_CODE_1616  { 1616, [unit_code_1616], [unit_code_1616_help] }
#define    _UNIT_CODE_1617  { 1617, [unit_code_1617], [unit_code_1617_help] }
#define    _UNIT_CODE_1618  { 1618, [unit_code_1618], [unit_code_1618_help] }
#define    _UNIT_CODE_1619  { 1619, [unit_code_1619], [unit_code_1619_help] }
#define    _UNIT_CODE_1620  { 1620, [unit_code_1620], [unit_code_1620_help] }
#define    _UNIT_CODE_1621  { 1621, [unit_code_1621], [unit_code_1621_help] }
#define    _UNIT_CODE_1622  { 1622, [unit_code_1622], [unit_code_1622_help] }
#define    _UNIT_CODE_1623  { 1623, [unit_code_1623], [unit_code_1623_help] }
#define    _UNIT_CODE_1624  { 1624, [unit_code_1624], [unit_code_1624_help] }
#define    _UNIT_CODE_1625  { 1625, [unit_code_1625], [unit_code_1625_help] }
#define    _UNIT_CODE_1626  { 1626, [unit_code_1626], [unit_code_1626_help] }
#define    _UNIT_CODE_1627  { 1627, [unit_code_1627], [unit_code_1627_help] }
#define    _UNIT_CODE_1628  { 1628, [unit_code_1628], [unit_code_1628_help] }
#define    _UNIT_CODE_1629  { 1629, [unit_code_1629], [unit_code_1629_help] }
#define    _UNIT_CODE_1630  { 1630, [unit_code_1630], [unit_code_1630_help] }
#define    _UNIT_CODE_1631  { 1631, [unit_code_1631], [unit_code_1631_help] }
#define    _UNIT_CODE_1632  { 1632, [unit_code_1632], [unit_code_1632_help] }
#define    _UNIT_CODE_1633  { 1633, [unit_code_1633], [unit_code_1633_help] }
#define    _UNIT_CODE_1634  { 1634, [unit_code_1634], [unit_code_1634_help] }
#define    _UNIT_CODE_1635  { 1635, [unit_code_1635], [unit_code_1635_help] }
#define    _UNIT_CODE_1636  { 1636, [unit_code_1636], [unit_code_1636_help] }
#define    _UNIT_CODE_1637  { 1637, [unit_code_1637], [unit_code_1637_help] }
#define    _UNIT_CODE_1638  { 1638, [unit_code_1638], [unit_code_1638_help] }
#define    _UNIT_CODE_1639  { 1639, [unit_code_1639], [unit_code_1639_help] }
#define    _UNIT_CODE_1640  { 1640, [unit_code_1640], [unit_code_1640_help] }
#define    _UNIT_CODE_1641  { 1641, [unit_code_1641], [unit_code_1641_help] }
#define    _UNIT_CODE_1642  { 1642, [unit_code_1642], [unit_code_1642_help] }
#define    _UNIT_CODE_1643  { 1643, [unit_code_1643], [unit_code_1643_help] }
#define    _UNIT_CODE_1644  { 1644, [unit_code_1644], [unit_code_1644_help] }
#define    _UNIT_CODE_1645  { 1645, [unit_code_1645], [unit_code_1645_help] }
#define    _UNIT_CODE_1646  { 1646, [unit_code_1646], [unit_code_1646_help] }
#define    _UNIT_CODE_1647  { 1647, [unit_code_1647], [unit_code_1647_help] }
#define    _UNIT_CODE_1648  { 1648, [unit_code_1648], [unit_code_1648_help] }
#define    _UNIT_CODE_1649  { 1649, [unit_code_1649], [unit_code_1649_help] }
#define    _UNIT_CODE_1650  { 1650, [unit_code_1650], [unit_code_1650_help] }
#define    _UNIT_CODE_1651  { 1651, [unit_code_1651], [unit_code_1651_help] }
#define    _UNIT_CODE_1652  { 1652, [unit_code_1652], [unit_code_1652_help] }
#define    _UNIT_CODE_1653  { 1653, [unit_code_1653], [unit_code_1653_help] }
#define    _UNIT_CODE_1654  { 1654, [unit_code_1654], [unit_code_1654_help] }
#define    _UNIT_CODE_1655  { 1655, [unit_code_1655], [unit_code_1655_help] }
#define    _UNIT_CODE_1656  { 1656, [unit_code_1656], [unit_code_1656_help] }
#define    _UNIT_CODE_1657  { 1657, [unit_code_1657], [unit_code_1657_help] }
#define    _UNIT_CODE_1658  { 1658, [unit_code_1658], [unit_code_1658_help] }
#define    _UNIT_CODE_1659  { 1659, [unit_code_1659], [unit_code_1659_help] }
#define    _UNIT_CODE_1660  { 1660, [unit_code_1660], [unit_code_1660_help] }
#define    _UNIT_CODE_1661  { 1661, [unit_code_1661], [unit_code_1661_help] }
#define    _UNIT_CODE_1662  { 1662, [unit_code_1662], [unit_code_1662_help] }
#define    _UNIT_CODE_1663  { 1663, [unit_code_1663], [unit_code_1663_help] }
#define    _UNIT_CODE_1664  { 1664, [unit_code_1664], [unit_code_1664_help] }
#define    _UNIT_CODE_1665  { 1665, [unit_code_1665], [unit_code_1665_help] }
#define    _UNIT_CODE_1666  { 1666, [unit_code_1666], [unit_code_1666_help] }
#define    _UNIT_CODE_1667  { 1667, [unit_code_1667], [unit_code_1667_help] }
#define    _UNIT_CODE_1668  { 1668, [unit_code_1668], [unit_code_1668_help] }
#define    _UNIT_CODE_1669  { 1669, [unit_code_1669], [unit_code_1669_help] }
#define    _UNIT_CODE_1670  { 1670, [unit_code_1670], [unit_code_1670_help] }
#define    _UNIT_CODE_1671  { 1671, [unit_code_1671], [unit_code_1671_help] }
#define    _UNIT_CODE_1672  { 1672, [unit_code_1672], [unit_code_1672_help] }
#define    _UNIT_CODE_1673  { 1673, [unit_code_1673], [unit_code_1673_help] }
#define    _UNIT_CODE_1674  { 1674, [unit_code_1674], [unit_code_1674_help] }
#define    _UNIT_CODE_1675  { 1675, [unit_code_1675], [unit_code_1675_help] }
#define    _UNIT_CODE_1676  { 1676, [unit_code_1676], [unit_code_1676_help] }
#define    _UNIT_CODE_1677  { 1677, [unit_code_1677], [unit_code_1677_help] }
#define    _UNIT_CODE_1678  { 1678, [unit_code_1678], [unit_code_1678_help] }
#define    _UNIT_CODE_1679  { 1679, [unit_code_1679], [unit_code_1679_help] }
#define    _UNIT_CODE_1680  { 1680, [unit_code_1680], [unit_code_1680_help] }
#define    _UNIT_CODE_1681  { 1681, [unit_code_1681], [unit_code_1681_help] }
#define    _UNIT_CODE_1682  { 1682, [unit_code_1682], [unit_code_1682_help] }
#define    _UNIT_CODE_1683  { 1683, [unit_code_1683], [unit_code_1683_help] }
#define    _UNIT_CODE_1684  { 1684, [unit_code_1684], [unit_code_1684_help] }
#define    _UNIT_CODE_1685  { 1685, [unit_code_1685], [unit_code_1685_help] }
#define    _UNIT_CODE_1686  { 1686, [unit_code_1686], [unit_code_1686_help] }
#define    _UNIT_CODE_1687  { 1687, [unit_code_1687], [unit_code_1687_help] }
#define    _UNIT_CODE_1688  { 1688, [unit_code_1688], [unit_code_1688_help] }
#define    _UNIT_CODE_1689  { 1689, [unit_code_1689], [unit_code_1689_help] }
#define    _UNIT_CODE_1690  { 1690, [unit_code_1690], [unit_code_1690_help] }
#define    _UNIT_CODE_1691  { 1691, [unit_code_1691], [unit_code_1691_help] }
#define    _UNIT_CODE_1692  { 1692, [unit_code_1692], [unit_code_1692_help] }
#define    _UNIT_CODE_1693  { 1693, [unit_code_1693], [unit_code_1693_help] }
#define    _UNIT_CODE_1694  { 1694, [unit_code_1694], [unit_code_1694_help] }
#define    _UNIT_CODE_1695  { 1695, [unit_code_1695], [unit_code_1695_help] }
#define    _UNIT_CODE_1696  { 1696, [unit_code_1696], [unit_code_1696_help] }
#define    _UNIT_CODE_1697  { 1697, [unit_code_1697], [unit_code_1697_help] }
#define    _UNIT_CODE_1698  { 1698, [unit_code_1698], [unit_code_1698_help] }
#define    _UNIT_CODE_1699  { 1699, [unit_code_1699], [unit_code_1699_help] }
#define    _UNIT_CODE_1700  { 1700, [unit_code_1700], [unit_code_1700_help] }
#define    _UNIT_CODE_1701  { 1701, [unit_code_1701], [unit_code_1701_help] }
#define    _UNIT_CODE_1702  { 1702, [unit_code_1702], [unit_code_1702_help] }
#define    _UNIT_CODE_1703  { 1703, [unit_code_1703], [unit_code_1703_help] }
#define    _UNIT_CODE_1704  { 1704, [unit_code_1704], [unit_code_1704_help] }
#define    _UNIT_CODE_1705  { 1705, [unit_code_1705], [unit_code_1705_help] }
#define    _UNIT_CODE_1706  { 1706, [unit_code_1706], [unit_code_1706_help] }
#define    _UNIT_CODE_1707  { 1707, [unit_code_1707], [unit_code_1707_help] }
#define    _UNIT_CODE_1708  { 1708, [unit_code_1708], [unit_code_1708_help] }
#define    _UNIT_CODE_1709  { 1709, [unit_code_1709], [unit_code_1709_help] }
#define    _UNIT_CODE_1710  { 1710, [unit_code_1710], [unit_code_1710_help] }
#define    _UNIT_CODE_1711  { 1711, [unit_code_1711], [unit_code_1711_help] }
#define    _UNIT_CODE_1712  { 1712, [unit_code_1712], [unit_code_1712_help] }
#define    _UNIT_CODE_1713  { 1713, [unit_code_1713], [unit_code_1713_help] }
#define    _UNIT_CODE_1714  { 1714, [unit_code_1714], [unit_code_1714_help] }
#define    _UNIT_CODE_1715  { 1715, [unit_code_1715], [unit_code_1715_help] }
#define    _UNIT_CODE_1716  { 1716, [unit_code_1716], [unit_code_1716_help] }
#define    _UNIT_CODE_1717  { 1717, [unit_code_1717], [unit_code_1717_help] }
#define    _UNIT_CODE_1718  { 1718, [unit_code_1718], [unit_code_1718_help] }
#define    _UNIT_CODE_1719  { 1719, [unit_code_1719], [unit_code_1719_help] }
#define    _UNIT_CODE_1720  { 1720, [unit_code_1720], [unit_code_1720_help] }


#define  __UNITS_CODES1 \
        _UNIT_CODE_1000,\
        _UNIT_CODE_1001, _UNIT_CODE_1002, _UNIT_CODE_1003, _UNIT_CODE_1004, _UNIT_CODE_1005,\
        _UNIT_CODE_1006, _UNIT_CODE_1007, _UNIT_CODE_1008, _UNIT_CODE_1009, _UNIT_CODE_1010,\
        _UNIT_CODE_1011, _UNIT_CODE_1012, _UNIT_CODE_1013, _UNIT_CODE_1014, _UNIT_CODE_1015,\
        _UNIT_CODE_1016, _UNIT_CODE_1017, _UNIT_CODE_1018, _UNIT_CODE_1019, _UNIT_CODE_1020,\
        _UNIT_CODE_1021, _UNIT_CODE_1022, _UNIT_CODE_1023, _UNIT_CODE_1024, _UNIT_CODE_1025,\
        _UNIT_CODE_1026, _UNIT_CODE_1027, _UNIT_CODE_1028, _UNIT_CODE_1029, _UNIT_CODE_1030,\
        _UNIT_CODE_1031, _UNIT_CODE_1032, _UNIT_CODE_1033, _UNIT_CODE_1034, _UNIT_CODE_1035,\
        _UNIT_CODE_1036, _UNIT_CODE_1037, _UNIT_CODE_1038, _UNIT_CODE_1039, _UNIT_CODE_1040,\
        _UNIT_CODE_1041, _UNIT_CODE_1042, _UNIT_CODE_1043, _UNIT_CODE_1044, _UNIT_CODE_1045,\
        _UNIT_CODE_1046, _UNIT_CODE_1047, _UNIT_CODE_1048, _UNIT_CODE_1049, _UNIT_CODE_1050,\
        _UNIT_CODE_1051, _UNIT_CODE_1052, _UNIT_CODE_1053, _UNIT_CODE_1054, _UNIT_CODE_1055,\
        _UNIT_CODE_1056, _UNIT_CODE_1057, _UNIT_CODE_1058, _UNIT_CODE_1059, _UNIT_CODE_1060,\
        _UNIT_CODE_1061, _UNIT_CODE_1062, _UNIT_CODE_1063, _UNIT_CODE_1064, _UNIT_CODE_1065,\
        _UNIT_CODE_1066, _UNIT_CODE_1067, _UNIT_CODE_1068, _UNIT_CODE_1069, _UNIT_CODE_1070,\
        _UNIT_CODE_1071, _UNIT_CODE_1072, _UNIT_CODE_1073, _UNIT_CODE_1074, _UNIT_CODE_1075,\
        _UNIT_CODE_1076, _UNIT_CODE_1077, _UNIT_CODE_1078, _UNIT_CODE_1079, _UNIT_CODE_1080,\
        _UNIT_CODE_1081, _UNIT_CODE_1082, _UNIT_CODE_1083, _UNIT_CODE_1084, _UNIT_CODE_1085,\
        _UNIT_CODE_1086, _UNIT_CODE_1087, _UNIT_CODE_1088, _UNIT_CODE_1089, _UNIT_CODE_1090,\
        _UNIT_CODE_1091, _UNIT_CODE_1092, _UNIT_CODE_1093, _UNIT_CODE_1094, _UNIT_CODE_1095,\
        _UNIT_CODE_1096, _UNIT_CODE_1097, _UNIT_CODE_1098, _UNIT_CODE_1099, _UNIT_CODE_1100,\
        _UNIT_CODE_1101, _UNIT_CODE_1102, _UNIT_CODE_1103, _UNIT_CODE_1104, _UNIT_CODE_1105,\
        _UNIT_CODE_1106, _UNIT_CODE_1107, _UNIT_CODE_1108, _UNIT_CODE_1109, _UNIT_CODE_1110,\
        _UNIT_CODE_1111, _UNIT_CODE_1112, _UNIT_CODE_1113, _UNIT_CODE_1114, _UNIT_CODE_1115,\
        _UNIT_CODE_1116, _UNIT_CODE_1117, _UNIT_CODE_1118, _UNIT_CODE_1119, _UNIT_CODE_1120,\
        _UNIT_CODE_1121, _UNIT_CODE_1122, _UNIT_CODE_1123, _UNIT_CODE_1124, _UNIT_CODE_1125,\
        _UNIT_CODE_1126, _UNIT_CODE_1127, _UNIT_CODE_1128, _UNIT_CODE_1129, _UNIT_CODE_1130,\
        _UNIT_CODE_1131, _UNIT_CODE_1132, _UNIT_CODE_1133, _UNIT_CODE_1134, _UNIT_CODE_1135,\
        _UNIT_CODE_1136, _UNIT_CODE_1137, _UNIT_CODE_1138, _UNIT_CODE_1139, _UNIT_CODE_1140,\
        _UNIT_CODE_1141, _UNIT_CODE_1142, _UNIT_CODE_1143, _UNIT_CODE_1144, _UNIT_CODE_1145,\
        _UNIT_CODE_1146, _UNIT_CODE_1147, _UNIT_CODE_1148, _UNIT_CODE_1149, _UNIT_CODE_1150,\
        _UNIT_CODE_1151, _UNIT_CODE_1152, _UNIT_CODE_1153, _UNIT_CODE_1154, _UNIT_CODE_1155,\
        _UNIT_CODE_1156, _UNIT_CODE_1157, _UNIT_CODE_1158, _UNIT_CODE_1159, _UNIT_CODE_1160,\
        _UNIT_CODE_1161, _UNIT_CODE_1162, _UNIT_CODE_1163, _UNIT_CODE_1164, _UNIT_CODE_1165,\
        _UNIT_CODE_1166, _UNIT_CODE_1167, _UNIT_CODE_1168, _UNIT_CODE_1169, _UNIT_CODE_1170,\
        _UNIT_CODE_1171, _UNIT_CODE_1172, _UNIT_CODE_1173, _UNIT_CODE_1174, _UNIT_CODE_1175,\
        _UNIT_CODE_1176, _UNIT_CODE_1177, _UNIT_CODE_1178, _UNIT_CODE_1179, _UNIT_CODE_1180,\
        _UNIT_CODE_1181, _UNIT_CODE_1182, _UNIT_CODE_1183, _UNIT_CODE_1184, _UNIT_CODE_1185,\
        _UNIT_CODE_1186, _UNIT_CODE_1187, _UNIT_CODE_1188, _UNIT_CODE_1189, _UNIT_CODE_1190,\
        _UNIT_CODE_1191, _UNIT_CODE_1192, _UNIT_CODE_1193, _UNIT_CODE_1194, _UNIT_CODE_1195,\
        _UNIT_CODE_1196, _UNIT_CODE_1197, _UNIT_CODE_1198, _UNIT_CODE_1199, _UNIT_CODE_1200,\
        _UNIT_CODE_1201, _UNIT_CODE_1202, _UNIT_CODE_1203, _UNIT_CODE_1204, _UNIT_CODE_1205,\
        _UNIT_CODE_1206, _UNIT_CODE_1207, _UNIT_CODE_1208, _UNIT_CODE_1209, _UNIT_CODE_1210,\
        _UNIT_CODE_1211, _UNIT_CODE_1212, _UNIT_CODE_1213, _UNIT_CODE_1214, _UNIT_CODE_1215,\
        _UNIT_CODE_1216, _UNIT_CODE_1217, _UNIT_CODE_1218, _UNIT_CODE_1219, _UNIT_CODE_1220,\
        _UNIT_CODE_1221, _UNIT_CODE_1222, _UNIT_CODE_1223, _UNIT_CODE_1224, _UNIT_CODE_1225,\
        _UNIT_CODE_1226, _UNIT_CODE_1227, _UNIT_CODE_1228, _UNIT_CODE_1229, _UNIT_CODE_1230,\
        _UNIT_CODE_1231, _UNIT_CODE_1232, _UNIT_CODE_1233, _UNIT_CODE_1234, _UNIT_CODE_1235,\
        _UNIT_CODE_1236, _UNIT_CODE_1237, _UNIT_CODE_1238, _UNIT_CODE_1239, _UNIT_CODE_1240,\
        _UNIT_CODE_1241, _UNIT_CODE_1242, _UNIT_CODE_1243, _UNIT_CODE_1244, _UNIT_CODE_1245,\
        _UNIT_CODE_1246, _UNIT_CODE_1247, _UNIT_CODE_1248, _UNIT_CODE_1249, _UNIT_CODE_1250,\
        _UNIT_CODE_1256, _UNIT_CODE_1257, _UNIT_CODE_1258, _UNIT_CODE_1259, _UNIT_CODE_1260,\
        _UNIT_CODE_1261, _UNIT_CODE_1262, _UNIT_CODE_1263, _UNIT_CODE_1264, _UNIT_CODE_1265,\
        _UNIT_CODE_1266, _UNIT_CODE_1267, _UNIT_CODE_1268, _UNIT_CODE_1269, _UNIT_CODE_1270,\
        _UNIT_CODE_1271, _UNIT_CODE_1272, _UNIT_CODE_1273, _UNIT_CODE_1274, _UNIT_CODE_1275,\
        _UNIT_CODE_1276, _UNIT_CODE_1277, _UNIT_CODE_1278, _UNIT_CODE_1279, _UNIT_CODE_1280,\
        _UNIT_CODE_1281, _UNIT_CODE_1282, _UNIT_CODE_1283, _UNIT_CODE_1284, _UNIT_CODE_1285,\
        _UNIT_CODE_1286, _UNIT_CODE_1287, _UNIT_CODE_1288, _UNIT_CODE_1289, _UNIT_CODE_1290,\
        _UNIT_CODE_1291, _UNIT_CODE_1292, _UNIT_CODE_1293, _UNIT_CODE_1294, _UNIT_CODE_1295,\
        _UNIT_CODE_1296, _UNIT_CODE_1297, _UNIT_CODE_1298, _UNIT_CODE_1299, _UNIT_CODE_1300,\
        _UNIT_CODE_1301, _UNIT_CODE_1302, _UNIT_CODE_1303, _UNIT_CODE_1304, _UNIT_CODE_1305,\
        _UNIT_CODE_1306, _UNIT_CODE_1307, _UNIT_CODE_1308, _UNIT_CODE_1309, _UNIT_CODE_1310,\
        _UNIT_CODE_1311, _UNIT_CODE_1312, _UNIT_CODE_1313, _UNIT_CODE_1314, _UNIT_CODE_1315,\
        _UNIT_CODE_1316, _UNIT_CODE_1317, _UNIT_CODE_1318, _UNIT_CODE_1319, _UNIT_CODE_1320,\
        _UNIT_CODE_1321, _UNIT_CODE_1322, _UNIT_CODE_1323, _UNIT_CODE_1324, _UNIT_CODE_1325,\
        _UNIT_CODE_1326, _UNIT_CODE_1327, _UNIT_CODE_1328, _UNIT_CODE_1329, _UNIT_CODE_1330,\
        _UNIT_CODE_1331, _UNIT_CODE_1332, _UNIT_CODE_1333, _UNIT_CODE_1334, _UNIT_CODE_1335,\
        _UNIT_CODE_1336, _UNIT_CODE_1337, _UNIT_CODE_1338, _UNIT_CODE_1339, _UNIT_CODE_1340,\
        _UNIT_CODE_1341, _UNIT_CODE_1342, _UNIT_CODE_1343, _UNIT_CODE_1344, _UNIT_CODE_1345,\
        _UNIT_CODE_1346, _UNIT_CODE_1347, _UNIT_CODE_1348, _UNIT_CODE_1349, _UNIT_CODE_1350,\
        _UNIT_CODE_1351, _UNIT_CODE_1352, _UNIT_CODE_1353, _UNIT_CODE_1354, _UNIT_CODE_1355,\
        _UNIT_CODE_1356, _UNIT_CODE_1357, _UNIT_CODE_1358, _UNIT_CODE_1359, _UNIT_CODE_1360,\
        _UNIT_CODE_1361, _UNIT_CODE_1362, _UNIT_CODE_1363, _UNIT_CODE_1364, _UNIT_CODE_1365,\
        _UNIT_CODE_1366, _UNIT_CODE_1367, _UNIT_CODE_1368, _UNIT_CODE_1369, _UNIT_CODE_1370,\
        _UNIT_CODE_1371, _UNIT_CODE_1372, _UNIT_CODE_1373, _UNIT_CODE_1374, _UNIT_CODE_1375,\
        _UNIT_CODE_1376, _UNIT_CODE_1377, _UNIT_CODE_1378, _UNIT_CODE_1379, _UNIT_CODE_1380,\
        _UNIT_CODE_1381, _UNIT_CODE_1382, _UNIT_CODE_1383, _UNIT_CODE_1384, _UNIT_CODE_1385,\
        _UNIT_CODE_1386, _UNIT_CODE_1387, _UNIT_CODE_1388, _UNIT_CODE_1389, _UNIT_CODE_1390,\
        _UNIT_CODE_1391, _UNIT_CODE_1392, _UNIT_CODE_1393, _UNIT_CODE_1394, _UNIT_CODE_1395,\
        _UNIT_CODE_1396, _UNIT_CODE_1397, _UNIT_CODE_1398, _UNIT_CODE_1399, _UNIT_CODE_1400,\
        _UNIT_CODE_1401, _UNIT_CODE_1402, _UNIT_CODE_1403, _UNIT_CODE_1404, _UNIT_CODE_1405,\
        _UNIT_CODE_1406, _UNIT_CODE_1407, _UNIT_CODE_1408, _UNIT_CODE_1409, _UNIT_CODE_1410,\
        _UNIT_CODE_1411, _UNIT_CODE_1412, _UNIT_CODE_1413, _UNIT_CODE_1414, _UNIT_CODE_1415,\
        _UNIT_CODE_1416, _UNIT_CODE_1417, _UNIT_CODE_1418, _UNIT_CODE_1419, _UNIT_CODE_1420,\
        _UNIT_CODE_1421, _UNIT_CODE_1422, _UNIT_CODE_1423, _UNIT_CODE_1424, _UNIT_CODE_1425,\
        _UNIT_CODE_1426, _UNIT_CODE_1427, _UNIT_CODE_1428, _UNIT_CODE_1429, _UNIT_CODE_1430,\
        _UNIT_CODE_1431, _UNIT_CODE_1432, _UNIT_CODE_1433, _UNIT_CODE_1434, _UNIT_CODE_1435,\
        _UNIT_CODE_1436, _UNIT_CODE_1437, _UNIT_CODE_1438, _UNIT_CODE_1439, _UNIT_CODE_1440,\
        _UNIT_CODE_1441, _UNIT_CODE_1442, _UNIT_CODE_1443, _UNIT_CODE_1444, _UNIT_CODE_1445,\
        _UNIT_CODE_1446, _UNIT_CODE_1447, _UNIT_CODE_1448, _UNIT_CODE_1449, _UNIT_CODE_1450,\
        _UNIT_CODE_1451, _UNIT_CODE_1452, _UNIT_CODE_1453, _UNIT_CODE_1454, _UNIT_CODE_1455,\
        _UNIT_CODE_1456, _UNIT_CODE_1457, _UNIT_CODE_1458, _UNIT_CODE_1459, _UNIT_CODE_1460,\
        _UNIT_CODE_1461, _UNIT_CODE_1462, _UNIT_CODE_1463, _UNIT_CODE_1464, _UNIT_CODE_1465,\
        _UNIT_CODE_1466, _UNIT_CODE_1467, _UNIT_CODE_1468, _UNIT_CODE_1469, _UNIT_CODE_1470

#define __UNITS_CODES2 \
        _UNIT_CODE_1471, _UNIT_CODE_1472, _UNIT_CODE_1473, _UNIT_CODE_1474, _UNIT_CODE_1475,\
        _UNIT_CODE_1476, _UNIT_CODE_1477, _UNIT_CODE_1478, _UNIT_CODE_1479, _UNIT_CODE_1480,\
        _UNIT_CODE_1481, _UNIT_CODE_1482, _UNIT_CODE_1483, _UNIT_CODE_1484, _UNIT_CODE_1485,\
        _UNIT_CODE_1486, _UNIT_CODE_1487, _UNIT_CODE_1488, _UNIT_CODE_1489, _UNIT_CODE_1490,\
        _UNIT_CODE_1491, _UNIT_CODE_1492, _UNIT_CODE_1493, _UNIT_CODE_1494, _UNIT_CODE_1495,\
        _UNIT_CODE_1496, _UNIT_CODE_1497, _UNIT_CODE_1498, _UNIT_CODE_1499, _UNIT_CODE_1500,\
        _UNIT_CODE_1501, _UNIT_CODE_1502, _UNIT_CODE_1503, _UNIT_CODE_1504, _UNIT_CODE_1505,\
        _UNIT_CODE_1506, _UNIT_CODE_1507, _UNIT_CODE_1508, _UNIT_CODE_1509, _UNIT_CODE_1510,\
        _UNIT_CODE_1511, _UNIT_CODE_1512, _UNIT_CODE_1513, _UNIT_CODE_1514, _UNIT_CODE_1515,\
        _UNIT_CODE_1516, _UNIT_CODE_1517, _UNIT_CODE_1518, _UNIT_CODE_1519, _UNIT_CODE_1520,\
        _UNIT_CODE_1521, _UNIT_CODE_1522, _UNIT_CODE_1523, _UNIT_CODE_1524, _UNIT_CODE_1525,\
        _UNIT_CODE_1526, _UNIT_CODE_1527, _UNIT_CODE_1528, _UNIT_CODE_1529, _UNIT_CODE_1530,\
        _UNIT_CODE_1531, _UNIT_CODE_1532, _UNIT_CODE_1533, _UNIT_CODE_1534, _UNIT_CODE_1535,\
        _UNIT_CODE_1536, _UNIT_CODE_1537, _UNIT_CODE_1538, _UNIT_CODE_1539, _UNIT_CODE_1540,\
        _UNIT_CODE_1541, _UNIT_CODE_1542, _UNIT_CODE_1543, _UNIT_CODE_1544, _UNIT_CODE_1545,\
        _UNIT_CODE_1546, _UNIT_CODE_1547, _UNIT_CODE_1548, _UNIT_CODE_1549, _UNIT_CODE_1550,\
        _UNIT_CODE_1551, _UNIT_CODE_1552, _UNIT_CODE_1553, _UNIT_CODE_1554, _UNIT_CODE_1555,\
        _UNIT_CODE_1556, _UNIT_CODE_1557, _UNIT_CODE_1558, _UNIT_CODE_1559, _UNIT_CODE_1560,\
        _UNIT_CODE_1561, _UNIT_CODE_1562, _UNIT_CODE_1563, _UNIT_CODE_1564, _UNIT_CODE_1565,\
        _UNIT_CODE_1566, _UNIT_CODE_1567, _UNIT_CODE_1568, _UNIT_CODE_1569, _UNIT_CODE_1570,\
        _UNIT_CODE_1571, _UNIT_CODE_1572, _UNIT_CODE_1573, _UNIT_CODE_1574, _UNIT_CODE_1575,\
        _UNIT_CODE_1576, _UNIT_CODE_1577, _UNIT_CODE_1578, _UNIT_CODE_1579, _UNIT_CODE_1580,\
        _UNIT_CODE_1581, _UNIT_CODE_1582, _UNIT_CODE_1583, _UNIT_CODE_1584, _UNIT_CODE_1585,\
        _UNIT_CODE_1586, _UNIT_CODE_1587, _UNIT_CODE_1588, _UNIT_CODE_1589, _UNIT_CODE_1590,\
        _UNIT_CODE_1591, _UNIT_CODE_1592, _UNIT_CODE_1593, _UNIT_CODE_1594, _UNIT_CODE_1595,\
        _UNIT_CODE_1596, _UNIT_CODE_1597, _UNIT_CODE_1598, _UNIT_CODE_1599, _UNIT_CODE_1600,\
        _UNIT_CODE_1601, _UNIT_CODE_1602, _UNIT_CODE_1603, _UNIT_CODE_1604, _UNIT_CODE_1605,\
        _UNIT_CODE_1606, _UNIT_CODE_1607, _UNIT_CODE_1608, _UNIT_CODE_1609, _UNIT_CODE_1610,\
        _UNIT_CODE_1611, _UNIT_CODE_1612, _UNIT_CODE_1613, _UNIT_CODE_1614, _UNIT_CODE_1615,\
        _UNIT_CODE_1616, _UNIT_CODE_1617, _UNIT_CODE_1618, _UNIT_CODE_1619, _UNIT_CODE_1620,\
        _UNIT_CODE_1621, _UNIT_CODE_1622, _UNIT_CODE_1623, _UNIT_CODE_1624, _UNIT_CODE_1625,\
        _UNIT_CODE_1626, _UNIT_CODE_1627, _UNIT_CODE_1628, _UNIT_CODE_1629, _UNIT_CODE_1630,\
        _UNIT_CODE_1631, _UNIT_CODE_1632, _UNIT_CODE_1633, _UNIT_CODE_1634, _UNIT_CODE_1635,\
        _UNIT_CODE_1636, _UNIT_CODE_1637, _UNIT_CODE_1638, _UNIT_CODE_1639, _UNIT_CODE_1640,\
        _UNIT_CODE_1641, _UNIT_CODE_1642, _UNIT_CODE_1643, _UNIT_CODE_1644, _UNIT_CODE_1645,\
        _UNIT_CODE_1646, _UNIT_CODE_1647, _UNIT_CODE_1648, _UNIT_CODE_1649, _UNIT_CODE_1650,\
        _UNIT_CODE_1651, _UNIT_CODE_1652, _UNIT_CODE_1653, _UNIT_CODE_1654, _UNIT_CODE_1655,\
        _UNIT_CODE_1656, _UNIT_CODE_1657, _UNIT_CODE_1658, _UNIT_CODE_1659, _UNIT_CODE_1660,\
        _UNIT_CODE_1661, _UNIT_CODE_1662, _UNIT_CODE_1663, _UNIT_CODE_1664, _UNIT_CODE_1665,\
        _UNIT_CODE_1666, _UNIT_CODE_1667, _UNIT_CODE_1668, _UNIT_CODE_1669, _UNIT_CODE_1670,\
        _UNIT_CODE_1671, _UNIT_CODE_1672, _UNIT_CODE_1673, _UNIT_CODE_1674, _UNIT_CODE_1675,\
        _UNIT_CODE_1676, _UNIT_CODE_1677, _UNIT_CODE_1678, _UNIT_CODE_1679, _UNIT_CODE_1680,\
        _UNIT_CODE_1681, _UNIT_CODE_1682, _UNIT_CODE_1683, _UNIT_CODE_1684, _UNIT_CODE_1685,\
        _UNIT_CODE_1686, _UNIT_CODE_1687, _UNIT_CODE_1688, _UNIT_CODE_1689, _UNIT_CODE_1690,\
        _UNIT_CODE_1691, _UNIT_CODE_1692, _UNIT_CODE_1693, _UNIT_CODE_1694, _UNIT_CODE_1695,\
        _UNIT_CODE_1696, _UNIT_CODE_1697, _UNIT_CODE_1698, _UNIT_CODE_1699, _UNIT_CODE_1700,\
        _UNIT_CODE_1701, _UNIT_CODE_1702, _UNIT_CODE_1703, _UNIT_CODE_1704, _UNIT_CODE_1705,\
        _UNIT_CODE_1706, _UNIT_CODE_1707, _UNIT_CODE_1708, _UNIT_CODE_1709, _UNIT_CODE_1710,\
        _UNIT_CODE_1711, _UNIT_CODE_1712, _UNIT_CODE_1713, _UNIT_CODE_1714, _UNIT_CODE_1715,\
        _UNIT_CODE_1716, _UNIT_CODE_1717, _UNIT_CODE_1718, _UNIT_CODE_1719, _UNIT_CODE_1720


/*
*********************************************************************
**Actual, Manual, Value Manufacturer IDs
*********************************************************************
*/

#define   _MFR_000103   {0x000103, [mfr_id_000103], [mfr_id_help] }
#define   _MFR_00012C   {0x00012C, [mfr_id_00012C], [mfr_id_help] }
#define   _MFR_00014D   {0x00014D, [mfr_id_00014D], [mfr_id_help] }
#define   _MFR_0001BF   {0x0001BF, [mfr_id_0001BF], [mfr_id_help] }
#define   _MFR_0001F4   {0x0001F4, [mfr_id_0001F4], [mfr_id_help] }
#define   _MFR_000302   {0x000302, [mfr_id_000302], [mfr_id_help] }
#define   _MFR_000309   {0x000309, [mfr_id_000309], [mfr_id_help] }
#define   _MFR_0003E8   {0x0003E8, [mfr_id_0003E8], [mfr_id_help] }
#define   _MFR_001151   {0x001151, [mfr_id_001151], [mfr_id_help] }
#define   _MFR_0022B8   {0x0022B8, [mfr_id_0022B8], [mfr_id_help] }
#define   _MFR_004649   {0x004649, [mfr_id_004649], [mfr_id_help] }
#define   _MFR_005100   {0x005100, [mfr_id_005100], [mfr_id_help] }
#define   _MFR_014A7E   {0x014A7E, [mfr_id_014A7E], [mfr_id_help] }
#define   _MFR_0BE0EC   {0x0BE0EC, [mfr_id_0BE0EC], [mfr_id_help] }
#define   _MFR_0DFC96   {0x0DFC96, [mfr_id_0DFC96], [mfr_id_help] }
#define   _MFR_1E6D11   {0x1E6D11, [mfr_id_1E6D11], [mfr_id_help] }
#define   _MFR_385884   {0x385884, [mfr_id_385884], [mfr_id_help] }
#define   _MFR_48574C   {0x48574C, [mfr_id_48574C], [mfr_id_help] }
#define   _MFR_4D5043   {0x4D5043, [mfr_id_4D5043], [mfr_id_help] }
#define   _MFR_4E4943   {0x4E4943, [mfr_id_4E4943], [mfr_id_help] }
#define   _MFR_594543   {0x594543, [mfr_id_594543], [mfr_id_help] }
#define   _MFR_000101   {0x000101, [mfr_id_000101], [mfr_id_help] }
#define   _MFR_000156   {0x000156, [mfr_id_000156], [mfr_id_help] }
#define   _MFR_000310   {0x000310, [mfr_id_000310], [mfr_id_help] }
#define   _MFR_000320   {0x000320, [mfr_id_000320], [mfr_id_help] }
#define   _MFR_00043E   {0x00043E, [mfr_id_00043E], [mfr_id_help] }
#define   _MFR_000457   {0x000457, [mfr_id_000457], [mfr_id_help] }
#define   _MFR_0004D2   {0x0004D2, [mfr_id_0004D2], [mfr_id_help] }
#define   _MFR_0007D1   {0x0007D1, [mfr_id_0007D1], [mfr_id_help] }
#define   _MFR_000E05   {0x000E05, [mfr_id_000E05], [mfr_id_help] }
#define   _MFR_002000   {0x002000, [mfr_id_002000], [mfr_id_help] }
#define   _MFR_0021C3   {0x0021C3, [mfr_id_0021C3], [mfr_id_help] }
#define   _MFR_005774   {0x005774, [mfr_id_005774], [mfr_id_help] }
#define   _MFR_00E099   {0x00E099, [mfr_id_00E099], [mfr_id_help] }
#define   _MFR_00FF01   {0x00FF01, [mfr_id_00FF01], [mfr_id_help] }
#define   _MFR_010253   {0x010253, [mfr_id_010253], [mfr_id_help] }
#define   _MFR_05E35D   {0x05E35D, [mfr_id_05E35D], [mfr_id_help] }
#define   _MFR_0B87A3   {0x0B87A3, [mfr_id_0B87A3], [mfr_id_help] }
#define   _MFR_385885   {0x385885, [mfr_id_385885], [mfr_id_help] }
#define   _MFR_445644   {0x445644, [mfr_id_445644], [mfr_id_help] }
#define   _MFR_452B48   {0x452B48, [mfr_id_452B48], [mfr_id_help] }
#define   _MFR_464C53   {0x464C53, [mfr_id_464C53], [mfr_id_help] }
#define   _MFR_465253   {0x465253, [mfr_id_465253], [mfr_id_help] }
#define   _MFR_466847   {0x466847, [mfr_id_466847], [mfr_id_help] }
#define   _MFR_4C444E   {0x4C444E, [mfr_id_4C444E], [mfr_id_help] }
#define   _MFR_502B46   {0x502B46, [mfr_id_502B46], [mfr_id_help] }
#define   _MFR_524149   {0x524149, [mfr_id_524149], [mfr_id_help] }
#define   _MFR_545758   {0x545758, [mfr_id_545758], [mfr_id_help] }
#define   _MFR_56474B   {0x56474B, [mfr_id_56474B], [mfr_id_help] }
#define   _MFR_534147   {0x534147, [mfr_id_534147], [mfr_id_help] }
#define   _MFR_564142   {0x564142, [mfr_id_564142], [mfr_id_help] }
#define   _MFR_564143   {0x564143, [mfr_id_564143], [mfr_id_help] }
#define   _MFR_564144   {0x564144, [mfr_id_564144], [mfr_id_help] }
#define   _MFR_564153   {0x564153, [mfr_id_564153], [mfr_id_help] }
#define   _MFR_564154   {0x564154, [mfr_id_564154], [mfr_id_help] }
#define   _MFR_574343   {0x574343, [mfr_id_574343], [mfr_id_help] }
#define   _MFR_000105   {0x000105, [mfr_id_000105], [mfr_id_help] }
#define   _MFR_000102   {0x000102, [mfr_id_000102], [mfr_id_help] }
#define   _MFR_000108   {0x000108, [mfr_id_000108], [mfr_id_help] }
#define   _MFR_000111   {0x000111, [mfr_id_000111], [mfr_id_help] }
#define   _MFR_0007B0   {0x0007B0, [mfr_id_0007B0], [mfr_id_help] }
#define   _MFR_0007D0   {0x0007D0, [mfr_id_0007D0], [mfr_id_help] }
#define   _MFR_000A1C   {0x000A1C, [mfr_id_000A1C], [mfr_id_help] }
#define   _MFR_003000   {0x003000, [mfr_id_003000], [mfr_id_help] }
#define   _MFR_004241   {0x004241, [mfr_id_004241], [mfr_id_help] }
#define   _MFR_004549   {0x004549, [mfr_id_004549], [mfr_id_help] }
#define   _MFR_00A000   {0x00A000, [mfr_id_00A000], [mfr_id_help] }
#define   _MFR_00F302   {0x00F302, [mfr_id_00F302], [mfr_id_help] }
#define   _MFR_0A10FF   {0x0A10FF, [mfr_id_0A10FF], [mfr_id_help] }
#define   _MFR_31FF52   {0x31FF52, [mfr_id_31FF52], [mfr_id_help] }
#define   _MFR_41434C   {0x41434C, [mfr_id_41434C], [mfr_id_help] }
#define   _MFR_435349   {0x435349, [mfr_id_435349], [mfr_id_help] }
#define   _MFR_44594E   {0x44594E, [mfr_id_44594E], [mfr_id_help] }
#define   _MFR_464C4F   {0x464C4F, [mfr_id_464C4F], [mfr_id_help] }
#define   _MFR_465255   {0x465255, [mfr_id_465255], [mfr_id_help] }
#define   _MFR_004745   {0x004745, [mfr_id_004745], [mfr_id_help] }
#define   _MFR_0006B0   {0x0006B0, [mfr_id_0006B0], [mfr_id_help] }
#define   _MFR_004000   {0x004000, [mfr_id_004000], [mfr_id_help] }
#define   _MFR_00A1FF   {0x00A1FF, [mfr_id_00A1FF], [mfr_id_help] }
#define   _MFR_445343   {0x445343, [mfr_id_445343], [mfr_id_help] }
#define   _MFR_4E5246   {0x4E5246, [mfr_id_4E5246], [mfr_id_help] }
#define   _MFR_575353   {0x575353, [mfr_id_575353], [mfr_id_help] }
#define   _MFR_576363   {0x576363, [mfr_id_576363], [mfr_id_help] }
#define   _MFR_5945FF   {0x5945FF, [mfr_id_5945FF], [mfr_id_help] }
#define   _MFR_005754   {0x005754, [mfr_id_005754], [mfr_id_help] }
#define   _MFR_10FF00   {0x10FF00, [mfr_id_10FF00], [mfr_id_help] }
#define   _MFR_001000   {0x001000, [mfr_id_001000], [mfr_id_help] }
#define   _MFR_001167   {0x001167, [mfr_id_001167], [mfr_id_help] }
#define   _MFR_038CBF   {0x038CBF, [mfr_id_038CBF], [mfr_id_help] }
#define   _MFR_000246   {0x000246, [mfr_id_000246], [mfr_id_help] }
#define   _MFR_00094B   {0x00094B, [mfr_id_00094B], [mfr_id_help] }
#define   _MFR_4E554D   {0x4E554D, [mfr_id_4E554D], [mfr_id_help] }
#define   _MFR_001D6D   {0x001D6D, [mfr_id_001D6D], [mfr_id_help] }
#define   _MFR_0C1DC0   {0x0C1DC0, [mfr_id_0C1DC0], [mfr_id_help] }
#define   _MFR_000313   {0x000313, [mfr_id_000313], [mfr_id_help] }
#define   _MFR_77E1A5   {0x77E1A5, [mfr_id_77E1A5], [mfr_id_help] }
#define   _MFR_424946   {0x424946, [mfr_id_424946], [mfr_id_help] }
#define   _MFR_454E4F   {0x454E4F, [mfr_id_454E4F], [mfr_id_help] }
#define   _MFR_507843   {0x507843, [mfr_id_507843], [mfr_id_help] }
#define   _MFR_001988   {0x001988, [mfr_id_001988], [mfr_id_help] }
#define   _MFR_00094A   {0x00094A, [mfr_id_00094A], [mfr_id_help] }
#define   _MFR_000212   {0x000212, [mfr_id_000212], [mfr_id_help] }
#define   _MFR_000888   {0x000888, [mfr_id_000888], [mfr_id_help] }
#define   _MFR_47E86B   {0x47E86B, [mfr_id_47E86B], [mfr_id_help] }
#define   _MFR_0001FD   {0x0001FD, [mfr_id_0001FD], [mfr_id_help] }
#define   _MFR_544653   {0x544653, [mfr_id_544653], [mfr_id_help] }
#define   _MFR_000211   {0x000211, [mfr_id_000211], [mfr_id_help] }
#define   _MFR_000188   {0x000188, [mfr_id_000188], [mfr_id_help] }
#define   _MFR_000109   {0x000109, [mfr_id_000109], [mfr_id_help] }
#define   _MFR_000106   {0x000106, [mfr_id_000106], [mfr_id_help] }
#define   _MFR_000993   {0x000993, [mfr_id_000993], [mfr_id_help] }
#define   _MFR_01FC49   {0x01FC49, [mfr_id_01FC49], [mfr_id_help] }
#define   _MFR_000110   {0x000110, [mfr_id_000110], [mfr_id_help] }
#define   _MFR_0008F0   {0x0008F0, [mfr_id_0008F0], [mfr_id_help] }
#define   _MFR_43414D   {0x43414D, [mfr_id_43414D], [mfr_id_help] }
#define   _MFR_012FD1   {0x012FD1, [mfr_id_012FD1], [mfr_id_help] }

#define   __FF_MFR_INDEX  \
              _MFR_000103,\
              _MFR_00012C,\
              _MFR_00014D,\
              _MFR_0001BF,\
              _MFR_0001F4,\
              _MFR_000302,\
              _MFR_000309,\
              _MFR_0003E8,\
              _MFR_001151,\
              _MFR_0022B8,\
              _MFR_004649,\
              _MFR_005100,\
              _MFR_014A7E,\
              _MFR_0BE0EC,\
              _MFR_0DFC96,\
              _MFR_1E6D11,\
              _MFR_385884,\
              _MFR_48574C,\
              _MFR_4D5043,\
              _MFR_4E4943,\
              _MFR_594543,\
              _MFR_000101,\
              _MFR_000156,\
              _MFR_000310,\
              _MFR_000320,\
              _MFR_00043E,\
              _MFR_000457,\
              _MFR_0004D2,\
              _MFR_0007D1,\
              _MFR_000E05,\
              _MFR_002000,\
              _MFR_0021C3,\
              _MFR_005774,\
              _MFR_00E099,\
              _MFR_00FF01,\
              _MFR_010253,\
              _MFR_05E35D,\
              _MFR_0B87A3,\
              _MFR_385885,\
              _MFR_445644,\
              _MFR_452B48,\
              _MFR_464C53,\
              _MFR_465253,\
              _MFR_466847,\
              _MFR_4C444E,\
              _MFR_502B46,\
              _MFR_524149,\
              _MFR_545758,\
              _MFR_56474B,\
              _MFR_534147,\
              _MFR_564142,\
              _MFR_564143,\
              _MFR_564144,\
              _MFR_564153,\
              _MFR_564154,\
              _MFR_574343,\
              _MFR_000105,\
              _MFR_000102,\
              _MFR_000108,\
              _MFR_000111,\
              _MFR_0007B0,\
              _MFR_0007D0,\
              _MFR_000A1C,\
              _MFR_003000,\
              _MFR_004241,\
              _MFR_004549,\
              _MFR_00A000,\
              _MFR_00F302,\
              _MFR_0A10FF,\
              _MFR_31FF52,\
              _MFR_41434C,\
              _MFR_435349,\
              _MFR_44594E,\
              _MFR_464C4F,\
              _MFR_465255,\
              _MFR_004745,\
              _MFR_0006B0,\
              _MFR_004000,\
              _MFR_00A1FF,\
              _MFR_445343,\
              _MFR_4E5246,\
              _MFR_575353,\
              _MFR_576363,\
              _MFR_5945FF,\
              _MFR_005754,\
              _MFR_10FF00,\
              _MFR_001000,\
              _MFR_001167,\
              _MFR_038CBF,\
              _MFR_000246,\
              _MFR_00094B,\
              _MFR_4E554D,\
              _MFR_001D6D,\
              _MFR_0C1DC0,\
              _MFR_000313,\
              _MFR_77E1A5,\
              _MFR_424946,\
              _MFR_454E4F,\
              _MFR_507843,\
              _MFR_001988,\
              _MFR_00094A,\
              _MFR_000212,\
              _MFR_000888,\
              _MFR_47E86B,\
              _MFR_0001FD,\
              _MFR_544653,\
              _MFR_000211,\
			  _MFR_000188,\
			  _MFR_000109,\
			  _MFR_000106,\
			  _MFR_000993,\
			  _MFR_01FC49,\
              _MFR_000110,\
			  _MFR_0008F0,\
			  _MFR_43414D,\
			  _MFR_012FD1

/*
**********************************************************************
** Actual, Normal, Target Modes (DS-69)
**********************************************************************
*/
#define  _MODE_REMOTE_OUTPUT  { 0x01, [mode_remote_output],    [mode_remote_output_help] }
#define  _MODE_REMOTE_CASCADE { 0x02, [mode_remote_cascade],   [mode_remote_cascade_help] }
#define  _MODE_CASCADE        { 0x04, [mode_cascade],          [mode_cascade_help] }
#define  _MODE_AUTOMATIC      { 0x08, [mode_automatic],        [mode_automatic_help] }
#define  _MODE_MANUAL         { 0x10, [mode_manual],           [mode_manual] }
#define  _MODE_LOCKED         { 0x20, [mode_locked],           [mode_locked_help] }
#define  _MODE_INITIALIZATION { 0x40, [mode_initialization],   [mode_initialization_help] }
#define  _MODE_OUT_OF_SERVICE { 0x80, [mode_out_of_service],   [mode_out_of_service_help] }

/*
**********************************************************************
** Permitted Modes (DS-69)
**********************************************************************
*/
#define  _PERMITTED_REMOTE_OUTPUT   { 0x01, [permitted_remote_output],  [permitted_remote_output_help] }
#define  _PERMITTED_REMOTE_CASCADE  { 0x02, [permitted_remote_cascade], [permitted_remote_cascade_help] }
#define  _PERMITTED_CASCADE         { 0x04, [permitted_cascade],        [permitted_cascade_help] }
#define  _PERMITTED_AUTOMATIC       { 0x08, [permitted_automatic],      [permitted_automatic_help] }
#define  _PERMITTED_MANUAL          { 0x10, [permitted_manual],         [permitted_manual_help] }
#define  _PERMITTED_LOCKED          { 0x20, [permitted_locked],         [permitted_locked_help] }
#define  _PERMITTED_INITIALIZATION  { 0x40, [permitted_initialization], [permitted_initialization_help] }
#define  _PERMITTED_OUT_OF_SERVICE  { 0x80, [permitted_out_of_service], [permitted_out_of_service_help] }

/*
**********************************************************************
** Alarm state (alarm_state) values (DS-71,72)
**********************************************************************
*/
#define  _ALARM_STATE_1  { 0x01,   [alarm_state_1],   [alarm_state_1_help] }
#define  _ALARM_STATE_2  { 0x02,   [alarm_state_2],   [alarm_state_2_help] }
#define  _ALARM_STATE_3  { 0x03,   [alarm_state_3],   [alarm_state_3_help] }
#define  _ALARM_STATE_4  { 0x04,   [alarm_state_4],   [alarm_state_4_help] }

/*
**********************************************************************
** Acknowledged State (unacknowledged) values (DS-71,72,73)
**********************************************************************
*/
#define  _ALARM_EVENT_ACKED   { 0x01, [acknowledged],   [acknowledged_help] }
#define  _ALARM_EVENT_UNACKED { 0x02, [unacknowledged], [unacknowledged_help] }

/*
**********************************************************************
** Update State (update_state) values (DS-73)
**********************************************************************
*/
#define  _UPDATE_REPORTED     { 0x01, [update_reported],    [update_reported_help] }
#define  _UPDATE_UNREPORTED   { 0x02, [update_unreported],  [update_unreported_help] }

/*
**********************************************************************
** Define the alarm summary bits (DS-74)
**********************************************************************
*/
#define  _DISCRETE_ALARM         0x0001
#define  _HIGH_HIGH_ALARM        0x0002
#define  _HIGH_ALARM             0x0004
#define  _LOW_LOW_ALARM          0x0008
#define  _LOW_ALARM              0x0010
#define  _DEVIATION_HIGH_ALARM   0x0020
#define  _DEVIATION_LOW_ALARM    0x0040
#define  _BLOCK_ALARM            0x0080
#define  _FAIL_ALARM           	 0x0100
#define  _OFF_SPEC_ALARM         0x0200
#define  _MAINTENANCE_ALARM      0x0400
#define  _CHECK_ALARM      		 0x0800

/*
**********************************************************************
** Current alarm (current_summary) values (DS-74)
**********************************************************************
*/
#define  _CURR_SUMM_0   { _DISCRETE_ALARM,       [curr_summ_0],   [curr_summ_0_help] }
#define  _CURR_SUMM_1   { _HIGH_HIGH_ALARM,      [curr_summ_1],   [curr_summ_1_help] }
#define  _CURR_SUMM_2   { _HIGH_ALARM,           [curr_summ_2],   [curr_summ_2_help] }
#define  _CURR_SUMM_3   { _LOW_LOW_ALARM,        [curr_summ_3],   [curr_summ_3_help] }
#define  _CURR_SUMM_4   { _LOW_ALARM,            [curr_summ_4],   [curr_summ_4_help] }
#define  _CURR_SUMM_5   { _DEVIATION_HIGH_ALARM, [curr_summ_5],   [curr_summ_5_help] }
#define  _CURR_SUMM_6   { _DEVIATION_LOW_ALARM,  [curr_summ_6],   [curr_summ_6_help] }
#define  _CURR_SUMM_7   { _BLOCK_ALARM,          [curr_summ_7],   [curr_summ_7_help] }
#define  _CURR_SUMM_8   { _FAIL_ALARM,         	 [curr_summ_8],   [curr_summ_8_help] }
#define  _CURR_SUMM_9   { _OFF_SPEC_ALARM,       [curr_summ_9],   [curr_summ_9_help] }
#define  _CURR_SUMM_10  { _MAINTENANCE_ALARM,    [curr_summ_10],  [curr_summ_10_help] }
#define  _CURR_SUMM_11  { _CHECK_ALARM,    		 [curr_summ_11],  [curr_summ_11_help] }

#define  _UNACK_SUMM_0  { _DISCRETE_ALARM,       [unack_summ_0],  [unack_summ_0_help] }
#define  _UNACK_SUMM_1  { _HIGH_HIGH_ALARM,      [unack_summ_1],  [unack_summ_1_help] }
#define  _UNACK_SUMM_2  { _HIGH_ALARM,           [unack_summ_2],  [unack_summ_2_help] }
#define  _UNACK_SUMM_3  { _LOW_LOW_ALARM,        [unack_summ_3],  [unack_summ_3_help] }
#define  _UNACK_SUMM_4  { _LOW_ALARM,            [unack_summ_4],  [unack_summ_4_help] }
#define  _UNACK_SUMM_5  { _DEVIATION_HIGH_ALARM, [unack_summ_5],  [unack_summ_5_help] }
#define  _UNACK_SUMM_6  { _DEVIATION_LOW_ALARM,  [unack_summ_6],  [unack_summ_6_help] }
#define  _UNACK_SUMM_7  { _BLOCK_ALARM,          [unack_summ_7],  [unack_summ_7_help] }
#define  _UNACK_SUMM_8  { _FAIL_ALARM,           [unack_summ_8],  [unack_summ_8_help] }
#define  _UNACK_SUMM_9  { _OFF_SPEC_ALARM,       [unack_summ_9],  [unack_summ_9_help] }
#define  _UNACK_SUMM_10 { _MAINTENANCE_ALARM,    [unack_summ_10], [unack_summ_10_help] }
#define  _UNACK_SUMM_11 { _CHECK_ALARM,    		 [unack_summ_11], [unack_summ_11_help] }

#define  _UNREP_SUMM_0  { _DISCRETE_ALARM,       [unrep_summ_0],  [unrep_summ_0_help] }
#define  _UNREP_SUMM_1  { _HIGH_HIGH_ALARM,      [unrep_summ_1],  [unrep_summ_1_help] }
#define  _UNREP_SUMM_2  { _HIGH_ALARM,           [unrep_summ_2],  [unrep_summ_2_help] }
#define  _UNREP_SUMM_3  { _LOW_LOW_ALARM,        [unrep_summ_3],  [unrep_summ_3_help] }
#define  _UNREP_SUMM_4  { _LOW_ALARM,            [unrep_summ_4],  [unrep_summ_4_help] }
#define  _UNREP_SUMM_5  { _DEVIATION_HIGH_ALARM, [unrep_summ_5],  [unrep_summ_5_help] }
#define  _UNREP_SUMM_6  { _DEVIATION_LOW_ALARM,  [unrep_summ_6],  [unrep_summ_6_help] }
#define  _UNREP_SUMM_7  { _BLOCK_ALARM,          [unrep_summ_7],  [unrep_summ_7_help] }
#define  _UNREP_SUMM_8  { _FAIL_ALARM,           [unrep_summ_8],  [unrep_summ_8_help] }
#define  _UNREP_SUMM_9  { _OFF_SPEC_ALARM,       [unrep_summ_9],  [unrep_summ_9_help] }
#define  _UNREP_SUMM_10 { _MAINTENANCE_ALARM,    [unrep_summ_10], [unrep_summ_10_help] }
#define  _UNREP_SUMM_11 { _CHECK_ALARM,    		 [unrep_summ_11], [unrep_summ_11_help] }

#define  _DISAB_SUMM_0  { _DISCRETE_ALARM,       [disab_summ_0],  [disab_summ_0_help] }
#define  _DISAB_SUMM_1  { _HIGH_HIGH_ALARM,      [disab_summ_1],  [disab_summ_1_help] }
#define  _DISAB_SUMM_2  { _HIGH_ALARM,           [disab_summ_2],  [disab_summ_2_help] }
#define  _DISAB_SUMM_3  { _LOW_LOW_ALARM,        [disab_summ_3],  [disab_summ_3_help] }
#define  _DISAB_SUMM_4  { _LOW_ALARM,            [disab_summ_4],  [disab_summ_4_help] }
#define  _DISAB_SUMM_5  { _DEVIATION_HIGH_ALARM, [disab_summ_5],  [disab_summ_5_help] }
#define  _DISAB_SUMM_6  { _DEVIATION_LOW_ALARM,  [disab_summ_6],  [disab_summ_6_help] }
#define  _DISAB_SUMM_7  { _BLOCK_ALARM,          [disab_summ_7],  [disab_summ_7_help] }
#define  _DISAB_SUMM_8  { _FAIL_ALARM,           [disab_summ_8],  [disab_summ_8_help] }
#define  _DISAB_SUMM_9  { _OFF_SPEC_ALARM,       [disab_summ_9],  [disab_summ_9_help] }
#define  _DISAB_SUMM_10 { _MAINTENANCE_ALARM,    [disab_summ_10], [disab_summ_10_help] }
#define  _DISAB_SUMM_11 { _CHECK_ALARM,    		 [disab_summ_11], [disab_summ_11_help] }

/*
**********************************************************************
** Define the alarm acknowledge bits
**********************************************************************
*/
#define	_ACK_OPT_0	{ _DISCRETE_ALARM,			[ack_opt_0],	[ack_opt_0_help] }
#define	_ACK_OPT_1	{ _HIGH_HIGH_ALARM,			[ack_opt_1],	[ack_opt_1_help] }
#define	_ACK_OPT_2	{ _HIGH_ALARM,				[ack_opt_2],	[ack_opt_2_help] }
#define	_ACK_OPT_3	{ _LOW_LOW_ALARM,			[ack_opt_3],	[ack_opt_3_help] }
#define	_ACK_OPT_4	{ _LOW_ALARM,				[ack_opt_4],	[ack_opt_4_help] }
#define	_ACK_OPT_5	{ _DEVIATION_HIGH_ALARM,	[ack_opt_5],	[ack_opt_5_help] }
#define	_ACK_OPT_6	{ _DEVIATION_LOW_ALARM,		[ack_opt_6],	[ack_opt_6_help] }
#define	_ACK_OPT_7	{ _BLOCK_ALARM,				[ack_opt_7],	[ack_opt_7_help] }
#define	_ACK_OPT_8	{ _FAIL_ALARM,				[ack_opt_8],	[ack_opt_8_help] }
#define	_ACK_OPT_9	{ _OFF_SPEC_ALARM,			[ack_opt_9],	[ack_opt_9_help] }
#define	_ACK_OPT_10	{ _MAINTENANCE_ALARM,		[ack_opt_10],	[ack_opt_10_help] }
#define	_ACK_OPT_11	{ _CHECK_ALARM,				[ack_opt_11],	[ack_opt_11_help] }


#define    __FF_ACCEPT_D_ENUMS        /* Enums for ACCEPT_D */ \
            {0 , [accept_d_val_0], [no_help_available]},\
            {1 , [accept_d_val_1], [no_help_available]}

#define    __FF_ARITH_TYPE_ENUMS       /* Enums for ARITH_TYPE */ \
            {1 , [arith_type_val_1], [no_help_available]},\
            {2 , [arith_type_val_2], [no_help_available]},\
            {3 , [arith_type_val_3], [no_help_available]},\
            {4 , [arith_type_val_4], [no_help_available]},\
            {5 , [arith_type_val_5], [no_help_available]},\
            {6 , [arith_type_val_6], [no_help_available]},\
            {7 , [arith_type_val_7], [no_help_available]},\
            {8 , [arith_type_val_8], [no_help_available]},\
            {9 , [arith_type_val_9], [no_help_available]}

#define    __FF_AUTO_CYCLE_ENUMS       /* Enums for AUTO_CYCLE */ \
            {0 , [auto_cycle_val_0], [no_help_available]},\
            {1 , [auto_cycle_val_1], [no_help_available]}

#define    __FF_CALC_ERRS_ENUMS       /* Enums for CALC_ERRS */ \
            {0x0004, [calc_errs_val_0x0004], [no_help_available]},\
            {0x0008, [calc_errs_val_0x0008], [no_help_available]},\
            {0x0010, [calc_errs_val_0x0010], [no_help_available]},\
            {0x0020, [calc_errs_val_0x0020], [no_help_available]},\
            {0x0040, [calc_errs_val_0x0040], [no_help_available]},\
            {0x0080, [calc_errs_val_0x0080], [no_help_available]},\
            {0x0100, [calc_errs_val_0x0100], [no_help_available]},\
            {0x0200, [calc_errs_val_0x0200], [no_help_available]},\
            {0x0400, [calc_errs_val_0x0400], [no_help_available]},\
            {0x0800, [calc_errs_val_0x0800], [no_help_available]},\
            {0x1000, [calc_errs_val_0x1000], [no_help_available]},\
            {0x2000, [calc_errs_val_0x2000], [no_help_available]},\
            {0x4000, [calc_errs_val_0x4000], [no_help_available]},\
            {0x8000, [calc_errs_val_0x8000], [no_help_available]}


#define    __FF_CHECKBACK_ENUMS       /* Enums for CHECKBACK */ \
            {0x0004, [checkback_val_0x0004], [no_help_available]},\
            {0x0008, [checkback_val_0x0008], [no_help_available]},\
            {0x0010, [checkback_val_0x0010], [no_help_available]},\
            {0x0020, [checkback_val_0x0020], [no_help_available]},\
            {0x0040, [checkback_val_0x0040], [no_help_available]},\
            {0x0080, [checkback_val_0x0080], [no_help_available]},\
            {0x0100, [checkback_val_0x0100], [no_help_available]},\
            {0x0200, [checkback_val_0x0200], [no_help_available]},\
            {0x0400, [checkback_val_0x0400], [no_help_available]},\
            {0x0800, [checkback_val_0x0800], [no_help_available]},\
            {0x1000, [checkback_val_0x1000], [no_help_available]},\
            {0x2000, [checkback_val_0x2000], [no_help_available]},\
            {0x4000, [checkback_val_0x4000], [no_help_available]},\
            {0x8000, [checkback_val_0x8000], [no_help_available]}


#define    __FF_COMB_TYPE_ENUMS       /* Enums for COMB_TYPE */ \
            {0 , [comb_type_val_0], [no_help_available]},\
            {1 , [comb_type_val_1], [no_help_available]},\
            {2 , [comb_type_val_2], [no_help_available]},\
            {3 , [comb_type_val_3], [no_help_available]},\
            {21, [comb_type_val_21], [no_help_available]},\
            {22, [comb_type_val_22], [no_help_available]},\
            {23, [comb_type_val_23], [no_help_available]},\
            {40, [comb_type_val_40], [no_help_available]},\
            {41, [comb_type_val_41], [no_help_available]}

#define    __FF_COND_TYPE_ENUMS       /* Enums for COND_TYPE */ \
            {0 , [cond_type_val_0], [no_help_available]},\
            {1 , [cond_type_val_1], [no_help_available]},\
            {2 , [cond_type_val_2], [no_help_available]},\
            {3 , [cond_type_val_3], [no_help_available]},\
            {4 , [cond_type_val_4], [no_help_available]},\
            {5 , [cond_type_val_5], [no_help_available]}

#define    __FF_DC_STATE_ENUMS        /* Enums for DC_STATE */ \
            {0 , [dc_state_val_0], [no_help_available]},\
            {1 , [dc_state_val_1], [no_help_available]},\
            {2 , [dc_state_val_2], [no_help_available]},\
            {3 , [dc_state_val_3], [no_help_available]},\
            {4 , [dc_state_val_4], [no_help_available]},\
            {5 , [dc_state_val_5], [no_help_available]}

#define    __FF_DISABLE_1_ENUMS       /* Enums for DISABLE_1 */ \
            {0 , [disable_1_val_0], [no_help_available]},\
            {1 , [disable_1_val_1], [no_help_available]}

#define    __FF_DISABLE_2_ENUMS       /* Enums for DISABLE_2 */ \
            {0 , [disable_2_val_0], [no_help_available]},\
            {1 , [disable_2_val_1], [no_help_available]}

#define    __FF_DISABLE_3_ENUMS       /* Enums for DISABLE_3 */ \
            {0 , [disable_3_val_0], [no_help_available]},\
            {1 , [disable_3_val_1], [no_help_available]}

#define    __FF_DISABLE_4_ENUMS       /* Enums for DISABLE_4 */ \
            {0 , [disable_4_val_0], [no_help_available]},\
            {1 , [disable_4_val_1], [no_help_available]}

#define    __FF_DISC_COND_ENUMS       /* Enums for DISC_COND */ \
            {0 , [disc_cond_val_0], [no_help_available]},\
            {1 , [disc_cond_val_1], [no_help_available]},\
            {2 , [disc_cond_val_2], [no_help_available]},\
            {3 , [disc_cond_val_3], [no_help_available]}

#define    __FF_ERR_LATCH_ENUMS       /* Enums for ERR_LATCH */ \
            {0 , [err_latch_val_0], [no_help_available]},\
            {1 , [err_latch_val_1], [no_help_available]}

#define    __FF_FAIL_ENUMS            /* Enums for FAIL */ \
            {0 , [fail_val_0], [no_help_available]},\
            {1 , [fail_val_1], [no_help_available]}

#define    __FF_FOLLOW_ENUMS          /* Enums for FOLLOW */ \
            {0 , [follow_val_0], [no_help_available]},\
            {1 , [follow_val_1], [no_help_available]}

#define    __FF_IN_D_ENUMS            /* Enums for IN_D */ \
            {0 , [in_d_val_0], [no_help_available]},\
            {1 , [in_d_val_1], [no_help_available]}

#define    __FF_INPUT_OPTS_ENUMS            /* Enums for INPUT_OPTS*/ \
            { 0x0001,    [input_opt_val_0x0001], [no_help_available]},\
            { 0x0002,    [input_opt_val_0x0002], [no_help_available]},\
            { 0x0004,    [input_opt_val_0x0004], [no_help_available]},\
            { 0x0008,    [input_opt_val_0x0008], [no_help_available]},\
            { 0x0010,    [input_opt_val_0x0010], [no_help_available]},\
            { 0x0020,    [input_opt_val_0x0020], [no_help_available]},\
            { 0x0040,    [input_opt_val_0x0040], [no_help_available]},\
            { 0x0080,    [input_opt_val_0x0080], [no_help_available]}

#define __FF_CONTROL_OPTS_ENUMS            /* enums for CONTROL_OPTS*/ \
            { 0x0001,    [bypass_enable],         [bypass_enable_help] },\
            { 0x0002,    [sp_pv_track_man],       [sp_pv_track_man_help] },\
            { 0x0004,    [sp_pv_track_rout],      [sp_pv_track_rout_help] },\
            { 0x0008,    [sp_pv_track_lo],        [sp_pv_track_lo_help] }, \
            { 0x0010,    [sp_track_retain],       [sp_track_retain_help] },\
            { 0x0020,    [direct_acting],         [direct_acting_help] },\
            { 0x0040,    [track_if_bad_trkind],          [track_if_bad_trkind_help] },\
            { 0x0080,    [track_enable],          [track_enable_help] },\
            { 0x0100,    [track_in_man],          [track_in_man_help] },\
            { 0x0200,    [pv_for_bkcal_out],      [pv_for_bkcal_out_help] },\
            { 0x0400,    [act_on_ir],             [act_on_ir_help] },\
            { 0x0800,    [bkcalout_with_in1],     [bkcalout_with_in1_help] },\
            { 0x1000,    [obey_sp_limits],        [obey_sp_limits_help] },\
            { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }


#define __FF_CONTROL_OPTS_BG_ENUMS            /* BG enums for CONTROL_OPTS*/ \
        { 0x0010,    [sp_track_retain],       [sp_track_retain_help] },\
        { 0x0040,    [track_if_bad_trkind],          [track_if_bad_trkind_help] },\
        { 0x0080,    [track_enable],          [track_enable_help] },\
        { 0x0100,    [track_in_man],          [track_in_man_help] },\
        { 0x0400,    [act_on_ir],             [act_on_ir_help] },\
        { 0x0800,    [bkcalout_with_in1],     [bkcalout_with_in1_help] },\
        { 0x1000,    [obey_sp_limits],        [obey_sp_limits_help] },\
        { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }

#define    __FF_CONTROL_OPTS_ML_ENUMS            /* ML enums for CONTROL_OPTS*/ \
        { 0x0040,    [track_if_bad_trkind],          [track_if_bad_trkind_help] },\
        { 0x0080,    [track_enable],          [track_enable_help] },\
        { 0x0100,    [track_in_man],          [track_in_man_help] },\
        { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }

#define    __FF_CONTROL_OPTS_PD_ENUMS            /* PD enums for CONTROL_OPTS*/ \
        { 0x0001,    [bypass_enable],         [bypass_enable_help] },\
        { 0x0002,    [sp_pv_track_man],       [sp_pv_track_man_help] },\
        { 0x0004,    [sp_pv_track_rout],      [sp_pv_track_rout_help] },\
        { 0x0008,    [sp_pv_track_lo],        [sp_pv_track_lo_help] },\
        { 0x0010,    [sp_track_retain],       [sp_track_retain_help] }, \
        { 0x0020,    [direct_acting],         [direct_acting_help] }, \
        { 0x0040,    [track_if_bad_trkind],          [track_if_bad_trkind_help] },\
        { 0x0080,    [track_enable],          [track_enable_help] }, \
        { 0x0100,    [track_in_man],          [track_in_man_help] }, \
        { 0x0200,    [pv_for_bkcal_out],      [pv_for_bkcal_out_help] }, \
        { 0x0400,    [act_on_ir],             [act_on_ir_help] }, \
        { 0x1000,    [obey_sp_limits],        [obey_sp_limits_help] },\
        { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }


#define    __FF_CONTROL_OPTS_PID_ENUMS            /* PID enums for CONTROL_OPTS*/ \
        { 0x0001,    [bypass_enable],         [bypass_enable_help] },\
        { 0x0002,    [sp_pv_track_man],       [sp_pv_track_man_help] },\
        { 0x0004,    [sp_pv_track_rout],      [sp_pv_track_rout_help] },\
        { 0x0008,    [sp_pv_track_lo],        [sp_pv_track_lo_help] },\
        { 0x0010,    [sp_track_retain],       [sp_track_retain_help] }, \
        { 0x0020,    [direct_acting],         [direct_acting_help] },\
        { 0x0040,    [track_if_bad_trkind],          [track_if_bad_trkind_help] },\
        { 0x0080,    [track_enable],          [track_enable_help] },\
        { 0x0100,    [track_in_man],          [track_in_man_help] },\
        { 0x0200,    [pv_for_bkcal_out],      [pv_for_bkcal_out_help] },\
        { 0x1000,    [obey_sp_limits],        [obey_sp_limits_help] },\
        { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }


#define    __FF_CONTROL_OPTS_RA_ENUMS            /* RA enums for CONTROL_OPTS*/ \
        { 0x0002,    [sp_pv_track_man],       [sp_pv_track_man_help] }, \
        { 0x0008,    [sp_pv_track_lo],        [sp_pv_track_lo_help] },\
        { 0x0010,    [sp_track_retain],       [sp_track_retain_help] },\
        { 0x0040,    [track_if_bad_trkind],          [track_if_bad_trkind_help] },\
        { 0x0080,    [track_enable],          [track_enable_help] },\
        { 0x0100,    [track_in_man],          [track_in_man_help] },\
        { 0x0200,    [pv_for_bkcal_out],      [pv_for_bkcal_out_help] }, \
        { 0x0400,    [act_on_ir],             [act_on_ir_help] },\
        { 0x0800,    [bkcalout_with_in1],     [bkcalout_with_in1_help] },\
        { 0x1000,    [obey_sp_limits],        [obey_sp_limits_help] }, \
        { 0x2000,    [no_out_lim_man],        [no_out_lim_man_help] }

#define    __FF_IO_OPTS_ENUMS            /* Enums for IO_OPTS*/ \
        { 0x0001,   [io_invert],              [io_invert_help] },\
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] },\
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] },\
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] },\
        { 0x0020,   [io_inc_to_close],        [io_inc_to_close_help] },\
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },\
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] },\
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },\
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] },\
        { 0x0400,   [io_low_cutoff],          [io_low_cutoff_help] },\
        { 0x0800,   [io_latch_fstate],        [io_latch_fstate_help] },\
        { 0x1000,   [io_units_conversion],    [io_units_conversion_help] }

#define    __FF_IO_OPTS_AI_ENUMS            /* AI enums for IO_OPTS*/ \
        { 0x0400,   [io_low_cutoff],          [io_low_cutoff_help] },\
        { 0x1000,   [io_units_conversion],    [io_units_conversion_help] }

#define     __FF_IO_OPTS_DI_ENUMS            /* DI enums for IO_OPTS*/ \
        { 0x0001,   [io_invert],              [io_invert_help] }

#define     __FF_IO_OPTS_DO_ENUMS            /* DO enums for IO_OPTS*/ \
        { 0x0001,   [io_invert],              [io_invert_help] },\
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] },\
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] },\
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] },\
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },\
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] },\
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },\
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] }


#define     __FF_IO_OPTS_PI_ENUMS            /* PI enums for IO_OPTS*/ \
        { 0x0001,   [io_invert],              [io_invert_help] },\
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] },\
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] },\
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] },\
        { 0x0020,   [io_inc_to_close],        [io_inc_to_close_help] },\
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },\
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] },\
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },\
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] },\
        { 0x0400,   [io_low_cutoff],          [io_low_cutoff_help] }

#define     __FF_IO_OPTS_SPID_ENUMS            /* SPID enums for IO_OPTS*/ \
        { 0x0001,   [io_invert],              [io_invert_help] },\
        { 0x0002,   [io_sp_pv_track_man],     [io_sp_pv_track_man_help] },\
        { 0x0008,   [io_sp_pv_track_lo],      [io_sp_pv_track_lo_help] },\
        { 0x0010,   [io_sp_track_target],     [io_sp_track_target_help] },\
        { 0x0020,   [io_inc_to_close],        [io_inc_to_close_help] },\
        { 0x0040,   [io_faultstate],          [io_faultstate_help] },\
        { 0x0080,   [io_faultstate_restart],  [io_faultstate_restart_help] },\
        { 0x0100,   [io_target_to_man],       [io_target_to_man_help] },\
        { 0x0200,   [io_pv_for_bkcal_out],    [io_pv_for_bkcal_out_help] },\
        { 0x0400,   [io_low_cutoff],          [io_low_cutoff_help] }

#define    __FF_INTEG_OPTS_ENUMS       /* Enums for INTEG_OPTS */ \
            {0x0001, [integ_opts_val_0x0001], [no_help_available]},\
            {0x0002, [integ_opts_val_0x0002], [no_help_available]},\
            {0x0004, [integ_opts_val_0x0004], [no_help_available]},\
            {0x0008, [integ_opts_val_0x0008], [no_help_available]},\
            {0x0010, [integ_opts_val_0x0010], [no_help_available]},\
            {0x0020, [integ_opts_val_0x0020], [no_help_available]},\
            {0x0040, [integ_opts_val_0x0040], [no_help_available]},\
            {0x0080, [integ_opts_val_0x0080], [no_help_available]},\
            {0x0100, [integ_opts_val_0x0100], [no_help_available]}
            /*{0x0200, [integ_opts_val_0x0200], [no_help_available]} AR5100*/


#define    __FF_INVERT_OPTS_ENUMS            /* Enums for INVERT_OPTS*/ \
            {0x0001, [invert_opts_val_0x0001], [no_help_available]},\
            {0x0002, [invert_opts_val_0x0002], [no_help_available]},\
            {0x0004, [invert_opts_val_0x0004], [no_help_available]},\
            {0x0008, [invert_opts_val_0x0008], [no_help_available]},\
            {0x0010, [invert_opts_val_0x0010], [no_help_available]},\
            {0x0020, [invert_opts_val_0x0020], [no_help_available]}

#define    __FF_INTEG_TYPE_ENUMS       /* Enums for INTEG_TYPE */ \
            {1 , [integ_type_val_1], [no_help_available]},\
            {2 , [integ_type_val_2], [no_help_available]},\
            {3 , [integ_type_val_3], [no_help_available]},\
            {4 , [integ_type_val_4], [no_help_available]},\
            {5 , [integ_type_val_5], [no_help_available]},\
            {6 , [integ_type_val_6], [no_help_available]},\
            {7 , [integ_type_val_7], [no_help_available]}

#define    __FF_FEATURES_ENUMS       /* Enums for FEATURES & FEATURE_SEL */ \
            { 0x0001,  [feature_unicode],         [feature_unicode_help] },\
            { 0x0002,  [feature_report],          [feature_report_help] },\
            { 0x0004,  [feature_faultstate],      [feature_faultstate_help] },\
            { 0x0008,  [feature_soft_write],      [feature_soft_write_help] }, \
            { 0x0010,  [feature_hard_write],      [feature_hard_write_help] },\
            { 0x0020,  [feature_out_readback],    [feature_out_readback_help] },\
            { 0x0040,  [feature_direct_write],    [feature_direct_write_help] },\
            { 0x0080,  [feature_bypass_auto],     [feature_bypass_auto_help] },\
            { 0x0100,  [feature_mvc_report_dist],     [feature_mvc_report_dist_help] },\
            { 0x0200,  [feature_pub_sub],     [feature_pub_sub_help] },\
            { 0x0400,  [feature_multi_bit],     [feature_multi_bit_help] },\
            { 0x0800,  [feature_restart_fb_act],     [feature_restart_fb_act_help] },\
            { 0x1000,  [feature_defer_wrt_chk],     [feature_defer_wrt_chk_help] }

#define    __FF_LOCKVAL_ENUMS         /* Enums for LOCKVAL */ \
            {1 , [lockval_val_1], [no_help_available]},\
            {2 , [lockval_val_2], [no_help_available]}

#define    __FF_OP_CMD_CXO_ENUMS       /* Enums for OP_CMD_CXO */ \
            {0x0800, [op_cmd_cxo_val_0x0800], [no_help_available]},\
            {0x1000, [op_cmd_cxo_val_0x1000], [no_help_available]},\
            {0x2000, [op_cmd_cxo_val_0x2000], [no_help_available]},\
            {0x4000, [op_cmd_cxo_val_0x4000], [no_help_available]}


#define    __FF_OP_CMD_INT_ENUMS       /* Enums for OP_CMD_INT */ \
            {0 , [op_cmd_int_val_0], [no_help_available]},\
            {1 , [op_cmd_int_val_1], [no_help_available]}

#define    __FF_OP_CMD_SPG_ENUMS       /* Enums for OP_CMD_SPG */ \
            {0 , [op_cmd_spg_val_0], [no_help_available]},\
            {1 , [op_cmd_spg_val_1], [no_help_available]},\
            {2 , [op_cmd_spg_val_2], [no_help_available]},\
            {3 , [op_cmd_spg_val_3], [no_help_available]},\
            {4 , [op_cmd_spg_val_4], [no_help_available]}

#define    __FF_OUT_1_STATE_ENUMS       /* Enums for OUT_1_STATE */ \
            {0 , [out_1_state_val_0], [no_help_available]},\
            {1 , [out_1_state_val_1], [no_help_available]},\
            {2 , [out_1_state_val_2], [no_help_available]},\
            {3 , [out_1_state_val_3], [no_help_available]},\
            {4 , [out_1_state_val_4], [no_help_available]}

#define    __FF_OUT_2_STATE_ENUMS       /* Enums for OUT_2_STATE */ \
            {0 , [out_2_state_val_0], [no_help_available]},\
            {1 , [out_2_state_val_1], [no_help_available]},\
            {2 , [out_2_state_val_2], [no_help_available]},\
            {3 , [out_2_state_val_3], [no_help_available]},\
            {4 , [out_2_state_val_4], [no_help_available]}

#define    __FF_OUT_3_STATE_ENUMS       /* Enums for OUT_3_STATE */ \
            {0 , [out_3_state_val_0], [no_help_available]},\
            {1 , [out_3_state_val_1], [no_help_available]},\
            {2 , [out_3_state_val_2], [no_help_available]},\
            {3 , [out_3_state_val_3], [no_help_available]},\
            {4 , [out_3_state_val_4], [no_help_available]}

#define    __FF_OUT_4_STATE_ENUMS       /* Enums for OUT_4_STATE */ \
            {0 , [out_4_state_val_0], [no_help_available]},\
            {1 , [out_4_state_val_1], [no_help_available]},\
            {2 , [out_4_state_val_2], [no_help_available]},\
            {3 , [out_4_state_val_3], [no_help_available]},\
            {4 , [out_4_state_val_4], [no_help_available]}

#define    __FF_OUT_ALM_SUM_ENUMS       /* Enums for OUT_ALM_SUM */ \
            {0 , [out_alm_sum_val_0], [no_help_available]},\
            {1 , [out_alm_sum_val_1], [no_help_available]},\
            {2 , [out_alm_sum_val_2], [no_help_available]},\
            {3 , [out_alm_sum_val_3], [no_help_available]},\
            {4 , [out_alm_sum_val_4], [no_help_available]},\
            {6 , [out_alm_sum_val_6], [no_help_available]},\
            {8 , [out_alm_sum_val_8], [no_help_available]},\
            {9 , [out_alm_sum_val_9], [no_help_available]},\
            {12, [out_alm_sum_val_12], [no_help_available]},\
            {15, [out_alm_sum_val_15], [no_help_available]}

#define    __FF_PAUSE_CAUSE_ENUMS       /* Enums for PAUSE_CAUSE */ \
            {0 , [pause_cause_val_0], [no_help_available]},\
            {1 , [pause_cause_val_1], [no_help_available]},\
            {2 , [pause_cause_val_2], [no_help_available]},\
            {4 , [pause_cause_val_4], [no_help_available]},\
            {3 , [pause_cause_val_3], [no_help_available]},\
            {5 , [pause_cause_val_5], [no_help_available]},\
            {6 , [pause_cause_val_6], [no_help_available]},\
            {7 , [pause_cause_val_7], [no_help_available]}

#define    __FF_PROP_LIMS_ENUMS       /* Enums for PROP_LIMS */ \
            {0 , [prop_lims_val_0], [no_help_available]},\
            {1 , [prop_lims_val_1], [no_help_available]}

#define    __FF_QUIES_OPT_ENUMS       /* Enums for QUIES_OPT */ \
            {1 , [quies_opt_val_1], [no_help_available]},\
            {2 , [quies_opt_val_2], [no_help_available]}

#define    __FF_RESET_CONFIRM_ENUMS       /* Enums for RESET_CONFIRM */ \
            {0 , [reset_confirm_val_0], [no_help_available]},\
            {1 , [reset_confirm_val_1], [no_help_available]}

#define    __FF_RESET_D_ENUMS         /* Enums for RESET_D */ \
            {0 , [reset_d_val_0], [no_help_available]},\
            {1 , [reset_d_val_1], [no_help_available]}

#define    __FF_RESET_IN_ENUMS        /* Enums for RESET_IN */ \
            {0 , [reset_in_val_0], [no_help_available]},\
            {1 , [reset_in_val_1], [no_help_available]}

#define    __FF_REV_FLOW1_ENUMS       /* Enums for REV_FLOW1 */ \
            {0 , [rev_flow1_val_0], [no_help_available]},\
            {1 , [rev_flow1_val_1], [no_help_available]}

#define    __FF_REV_FLOW2_ENUMS       /* Enums for REV_FLOW2 */ \
            {0 , [rev_flow2_val_0], [no_help_available]},\
            {1 , [rev_flow2_val_1], [no_help_available]}

#define    __FF_SELECT_TYPE_ENUMS       /* Enums for SELECT_TYPE */ \
            {1 , [select_type_val_1], [no_help_available]},\
            {2 , [select_type_val_2], [no_help_available]},\
            {3 , [select_type_val_3], [no_help_available]},\
            {4 , [select_type_val_4], [no_help_available]},\
            {5 , [select_type_val_5], [no_help_available]}

#define    __FF_SPG_STATE_ENUMS       /* Enums for SPG_STATE */ \
            {0 , [spg_state_val_0], [no_help_available]},\
            {1 , [spg_state_val_1], [no_help_available]},\
            {2 , [spg_state_val_2], [no_help_available]},\
            {3 , [spg_state_val_3], [no_help_available]},\
            {4 , [spg_state_val_4], [no_help_available]}

#define    __FF_START_TYPE_ENUMS       /* Enums for START_TYPE */ \
            {1 , [start_type_val_1], [no_help_available]},\
            {2 , [start_type_val_2], [no_help_available]},\
            {3 , [start_type_val_3], [no_help_available]}

#define    __FF_STATUS_OPTS_ENUMS       /* Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         }, \
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            }, \
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] },\
        { 0x0400,    [status_opt_target_to_man_bad_trkind],     [status_opt_target_to_man_bad_trkind_help] },\
        { 0x0800,    [status_opt_ifs_bad_trkind],     [status_opt_ifs_bad_trkind_help] }

#define    __FF_STATUS_OPTS_AAL_ENUMS       /* AAL Enums for STATUS_OPTS */ \
        { 0x0001,    "none available",             "There are no status opts for the AAL block."         }

#define    __FF_STATUS_OPTS_AI_ENUMS       /* AI Enums for STATUS_OPTS */ \
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }

#define    __FF_STATUS_OPTS_SAI_ENUMS       /* SIF-AI Enums for STATUS_OPTS */ \
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }

#define    __FF_STATUS_OPTS_AO_ENUMS       /* AO Enums for STATUS_OPTS */ \
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          }


#define    __FF_STATUS_OPTS_BG_ENUMS       /* BG Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] },\
        { 0x0400,    [status_opt_target_to_man_bad_trkind],     [status_opt_target_to_man_bad_trkind_help] },\
        { 0x0800,    [status_opt_ifs_bad_trkind],     [status_opt_ifs_bad_trkind_help] }

#define    __FF_STATUS_OPTS_CS_ENUMS       /* CS Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     }

#define    __FF_STATUS_OPTS_OS_ENUMS       /* OS Enums for STATUS_OPTS */ \
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     }


#define    __FF_STATUS_OPTS_ML_ENUMS       /* ML Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0400,    [status_opt_target_to_man_bad_trkind],     [status_opt_target_to_man_bad_trkind_help] },\
        { 0x0800,    [status_opt_ifs_bad_trkind],     [status_opt_ifs_bad_trkind_help] }

#define    __FF_STATUS_OPTS_PD_ENUMS       /* PD Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] },\
        { 0x0400,    [status_opt_target_to_man_bad_trkind],     [status_opt_target_to_man_bad_trkind_help] },\
        { 0x0800,    [status_opt_ifs_bad_trkind],     [status_opt_ifs_bad_trkind_help] }

#define    __FF_STATUS_OPTS_DC_ENUMS       /* DC Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     }

#define    __FF_STATUS_OPTS_DI_ENUMS       /* DI Enums for STATUS_OPTS */ \
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }

#define    __FF_STATUS_OPTS_DO_ENUMS       /* DO Enums for STATUS_OPTS */ \
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          }

#define    __FF_STATUS_OPTS_DT_ENUMS       /* DT Enums for STATUS_OPTS */ \
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }

#define    __FF_STATUS_OPTS_PID_ENUMS       /* PID Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] },\
        { 0x0400,    [status_opt_target_to_man_bad_trkind],     [status_opt_target_to_man_bad_trkind_help] },\
        { 0x0800,    [status_opt_ifs_bad_trkind],     [status_opt_ifs_bad_trkind_help] }

#define    __FF_STATUS_OPTS_SPG_ENUMS       /* SPG Enums for STATUS_OPTS */ \
    { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         }

#define    __FF_STATUS_OPTS_TMR_ENUMS       /* TMR Enums for STATUS_OPTS */ \
    { 0x0001,    "none available",             "There are no status opts for the AAL block." }

#define    __FF_STATUS_OPTS_LL_ENUMS       /* LL Enums for STATUS_OPTS */ \
             {0x0004, [status_opt_uncertain_good], [status_opt_uncertain_good_help]},\
             {0x0100, [status_opt_uncertain_man],  [status_opt_uncertain_man_help]}

#define    __FF_STATUS_OPTS_IS_ENUMS       /* IS Enums for STATUS_OPTS */ \
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }

#define    __FF_STATUS_OPTS_IT_ENUMS       /* IT Enums for STATUS_OPTS */ \
             { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }

#define    __FF_STATUS_OPTS_RA_ENUMS       /* RA Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] },\
        { 0x0400,    [status_opt_target_to_man_bad_trkind],     [status_opt_target_to_man_bad_trkind_help] },\
        { 0x0800,    [status_opt_ifs_bad_trkind],     [status_opt_ifs_bad_trkind_help] }

#define    __FF_STATUS_OPTS_MIO_ENUMS       /* CALCA Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_CALCA_ENUMS       /* CALCA Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_CALCD_ENUMS       /* CALCD Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_CAO_ENUMS       /* CAO Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_CDO_ENUMS       /* CDO Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_DAL_ENUMS       /* DAL Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_SPID_ENUMS       /* SPID Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_PI_ENUMS       /* PI Enums for STATUS_OPTS */ \
        { 0x0001,    [status_opt_ifs_bad_in],             [status_opt_ifs_bad_in_help]         },\
        { 0x0002,    [status_opt_ifs_bad_cas_in],         [status_opt_ifs_bad_cas_in_help]     },\
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0008,    [status_opt_fail_fwd],               [status_opt_fail_fwd_help]           },\
        { 0x0010,    [status_opt_fail_bkwd],              [status_opt_fail_bkwd_help]          },\
        { 0x0020,    [status_opt_man_bad_in],             [status_opt_man_bad_in_help]         },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      },\
        { 0x0200,    [status_opt_trgt_nxt_bad_casin],     [status_opt_trgt_nxt_bad_casin_help] }

#define    __FF_STATUS_OPTS_TOT_ENUMS       /* TOT Enums for STATUS_OPTS */ \
        { 0x0004,    [status_opt_uncertain_good],         [status_opt_uncertain_good_help]     },\
        { 0x0040,    [status_opt_uncertain_ltd],          [status_opt_uncertain_ltd_help]      },\
        { 0x0080,    [status_opt_bad_ltd],                [status_opt_bad_ltd_help]            },\
        { 0x0100,    [status_opt_uncertain_man],          [status_opt_uncertain_man_help]      }


#define    __FF_SWAP_2_ENUMS          /* Enums for SWAP_2 */ \
            {1 , [swap_2_val_1], [no_help_available]},\
            {2 , [swap_2_val_2], [no_help_available]}

#define    __FF_TIME_UNIT1_ENUMS       /* Enums for TIME_UNIT1 */ \
            {1 , [time_unit1_val_1], [no_help_available]},\
            {2 , [time_unit1_val_2], [no_help_available]},\
            {3 , [time_unit1_val_3], [no_help_available]},\
            {4 , [time_unit1_val_4], [no_help_available]}

#define    __FF_TIME_UNIT2_ENUMS       /* Enums for TIME_UNIT2 */ \
            {1 , [time_unit2_val_1], [no_help_available]},\
            {2 , [time_unit2_val_2], [no_help_available]},\
            {3 , [time_unit2_val_3], [no_help_available]},\
            {4 , [time_unit2_val_4], [no_help_available]}

#define    __FF_TIME_UNITS_ENUMS       /* Enums for TIME_UNITS */ \
            {1 , [time_units_val_1], [no_help_available]},\
            {2 , [time_units_val_2], [no_help_available]},\
            {3 , [time_units_val_3], [no_help_available]},\
            {4 , [time_units_val_4], [no_help_available]},\
            {5 , [time_units_val_5], [no_help_available]}

#define    __FF_TIMER_TYPE_ENUMS       /* Enums for TIMER_TYPE */ \
            {0 , [timer_type_val_0], [no_help_available]},\
            {1 , [timer_type_val_1], [no_help_available]},\
            {2 , [timer_type_val_2], [no_help_available]},\
            {3 , [timer_type_val_3], [no_help_available]},\
            {4 , [timer_type_val_4], [no_help_available]},\
            {5 , [timer_type_val_5], [no_help_available]},\
            {6 , [timer_type_val_6], [no_help_available]},\
            {7 , [timer_type_val_7], [no_help_available]}

/*
**********************************************************************
** Sensor Type Enumerations
**********************************************************************
*/
#define __SENSOR_TYPES	\
		{ 100, [flow_snsr_unknown_label],   [flow_snsr_unknown_help] },\
		{ 101, [coriolis_label],            [coriolis_help]         },\
		{ 102, [electromag_label],          [electromag_help]       },\
		{ 103, [mv_label],                  [mv_help]               },\
		{ 104, [ohms_label],                [ohms_help]             },\
		{ 105, [delta_ohms_label],          [delta_ohms_help]       },\
		{ 106, [nuc_mag_resn_label],        [nuc_mag_resn_help]     },\
		{ 107, [pos_displ_label],           [pos_displ_help]        },\
		{ 108, [refrac_label],              [refrac_help]           },\
		{ 109, [taggin_label],              [taggin_help]           },\
		{ 110, [ultrasonic_dop_label],      [ultrasonic_dop_help]   },\
		{ 111, [ultrasonic_time_label],     [ultrasonic_time_help]  },\
		{ 112, [vortex_label],              [vortex_help]           },\
		{ 113, [target_label],              [target_label]          },\
		{ 114, [var_area_label],            [var_area_help]         },\
		{ 115, [lev_snsr_unknown_label],    [lev_snsr_unknown_help] },\
		{ 116, [radar_label],               [radar_help]            },\
		{ 117, [capacitance_label],         [capacitance_help]      },\
		{ 118, [nuc_label],                 [nuc_help]              },\
		{ 119, [ultrasonic_label],          [ultrasonic_help]       },\
		{ 120, [float_gauge_label],         [float_gauge_help]      },\
		{ 121, [pres_snsr_unknown_label],   [pres_snsr_unknown_help]},\
		{ 122, [res_wire_label],            [res_wire_help]         },\
		{ 123, [vib_beam_label],            [vib_beam_help]         },\
		{ 124, [strain_gauge_label],        [strain_gauge_help]    },\
		{ 125, [piezo_res_label],           [piezo_res_help]        },\
		{ 126, [silicon_res_label],         [silicon_res_help]      },\
		{ 127, [temp_snsr_unknown_label],   [temp_snsr_unknown_help] },\
		{ 128, [pt100_a_385_label],         [pt100_a_385_help]      },\
		{ 129, [pt100_a_392_label],         [pt100_a_392_help]      },\
		{ 130, [pt200_a_385_label],         [pt200_a_385_help]      },\
		{ 131, [pt500_a_385_label],         [pt500_a_385_help]      },\
		{ 132, [ni120_label],               [ni120_help]            },\
		{ 133, [cu10_label],                [cu10_help]             },\
		{ 134, [tc_typeb_label],            [tc_typeb_help]         },\
		{ 135, [tc_typec_label],            [tc_typec_help]         },\
		{ 136, [tc_typee_label],            [tc_typee_help]         },\
		{ 137, [tc_typej_label],            [tc_typej_help]         },\
		{ 138, [tc_typek_label],            [tc_typek_help]         },\
		{ 139, [tc_typen_label],            [tc_typen_help]         },\
		{ 140, [tc_typer_label],            [tc_typer_help]         },\
		{ 141, [tc_types_label],            [tc_types_help]         },\
		{ 142, [tc_typet_label],            [tc_typet_help]         },\
		{ 143, [tc_type_dinl_label],        [tc_type_dinl_help]     },\
		{ 144, [tc_type_dinu_label],        [tc_type_dinu_help]     },\
		{ 145, [sensor_type_145_label], 	[sensor_type_145_help] 	},\
		{ 146, [sensor_type_146_label],     [sensor_type_146_help] },\
		{ 147, [sensor_type_147_label],     [sensor_type_147_help] },\
		{ 148, [sensor_type_148_label],  	[sensor_type_148_help] },\
		{ 149, [sensor_type_149_label],     [sensor_type_149_help] },\
		{ 150, [sensor_type_150_label],  	[sensor_type_150_help] },\
		{ 151, [sensor_type_151_label],  	[sensor_type_151_help] },\
		{ 152, [sensor_type_152_label],  	[sensor_type_152_help] },\
		{ 153, [sensor_type_153_label],  	[sensor_type_153_help] },\
		{ 154, [sensor_type_154_label],     [sensor_type_154_help] },\
		{ 155, [sensor_type_155_label],  	[sensor_type_155_help] },\
		{ 156, [sensor_type_156_label],  	[sensor_type_156_help] },\
		{ 157, [sensor_type_157_label],     [sensor_type_157_help] },\
		{ 158, [sensor_type_158_label],     [sensor_type_158_help] },\
		{ 159, [sensor_type_159_label],  	[sensor_type_159_help] },\
		{ 160, [thermal_label],  	    [thermal_help] },\
		{ 161, [turbine_label],  	    [turbine_help] },\
		{ 162, [sensor_type_162_label],  	[sensor_type_162_help] },\
		{ 163, [open_channel_flume_label],  [open_channel_flume_help] },\
		{ 164, [sensor_type_164_label],  	[sensor_type_164_help] },\
		{ 65535, [non_std_snsr],            [non_std_snsr_help]     }

/*
**********************************************************************
** Primary Value Type Enumerations
**********************************************************************
*/
#define	__PRIMARY_VALUE_TYPES	\
		{ 100,  [mass_flow_label],          [mass_flow_help] },			\
		{ 101,  [volume_flow_label],        [volume_flow_help] },		\
		{ 102,  [avg_mass_flow_label],      [avg_mass_flow_help] },		\
		{ 103,  [avg_volume_flow_label],    [avg_volume_flow_help] },	\
		{ 104,  [process_temp_label],       [process_temp_help] },		\
		{ 105,  [non_process_temp_label],   [non_process_temp_help] },	\
		{ 106,  [diff_temp_label],          [diff_temp_help] },			\
		{ 107,  [diff_press_label],         [diff_press_help]},			\
		{ 108,  [gauge_press_label],        [gauge_press_help] },		\
		{ 109,  [absolute_press_label],     [absolute_press_help] },	\
		{ 110,  [prim_val_type_110_label],  [prim_val_type_110_help] }, \
        { 111,  [prim_val_type_111_label],  [prim_val_type_111_help] }, \
        { 112,  [prim_val_type_112_label],  [prim_val_type_112_help] }, \
        { 113,  [prim_val_type_113_label],  [prim_val_type_113_help] }, \
        { 114,  [prim_val_type_114_label],  [prim_val_type_114_help] }, \
        { 115,  [prim_val_type_115_label],  [prim_val_type_115_help] }, \
        { 116,  [prim_val_type_116_label],  [prim_val_type_116_help] }, \
        { 117,  [prim_val_type_117_label],  [prim_val_type_117_help] }, \
        { 118,  [prim_val_type_118_label],  [prim_val_type_118_help] }, \
        { 119,  [prim_val_type_119_label],  [prim_val_type_119_help] }, \
        { 120,  [prim_val_type_120_label],  [prim_val_type_120_help] }, \
        { 121,  [prim_val_type_121_label],  [prim_val_type_121_help] }, \
        { 122,  [prim_val_type_122_label],  [prim_val_type_122_help] }, \
        { 123,  [prim_val_type_123_label],  [prim_val_type_123_help] }, \
        { 124,  [prim_val_type_124_label],  [prim_val_type_124_help] }, \
        { 125,  [prim_val_type_125_label],  [prim_val_type_125_help] }, \
        { 255,  [other],                    [other_help] }

/*
**********************************************************************
** Transducer Type Enumerations
**********************************************************************
*/
#define	__TRANSDUCER_TYPES	\
		{ 100,  [press_cal_label],  [press_cal_help]        },\
		{ 101,  [temp_cal_label],   [temp_cal_help]         },\
		{ 102,  [d_temp_cal_label], [d_temp_cal_help]       },\
		{ 103,  [radar_cal_label],  [radar_cal_help]        },\
		{ 104,  [flow_cal_label],   [flow_cal_help]         },\
		{ 105,  [bas_p_valve_label],[bas_p_valve_help]      },\
		{ 106,  [adv_p_valve_label],[adv_p_valve_help]      },\
		{ 107,  [disc_valve_label], [disc_valve_help]       },\
        { 108,  [xdcr_type_108_label], [xdcr_type_108_help]       },\
        { 109,  [xdcr_type_109_label], [xdcr_type_109_help]       },\
        { 110,  [xdcr_type_110_label], [xdcr_type_110_help]       },\
        { 111,  [xdcr_type_111_label], [xdcr_type_111_help]       },\
        { 112,  [xdcr_type_112_label], [xdcr_type_112_help]       },\
        { 65535,[other],            [other_help]            }

/*
**********************************************************************
** Convenience macros for adding Field Diagnostic parameters to
** Resource Block parameter and view redefinitions
**********************************************************************
*/

#define     __FD_PARAMS                                         \
            ADD FD_VER,                 __fd_ver;               \
            ADD FD_FAIL_ACTIVE,         __fd_fail_active;       \
            ADD FD_OFFSPEC_ACTIVE,      __fd_offspec_active;    \
            ADD FD_MAINT_ACTIVE,        __fd_maint_active;      \
            ADD FD_CHECK_ACTIVE,        __fd_check_active;      \
            ADD FD_FAIL_MAP,            __fd_fail_map;          \
            ADD FD_OFFSPEC_MAP,         __fd_offspec_map;       \
            ADD FD_MAINT_MAP,           __fd_maint_map;         \
            ADD FD_CHECK_MAP,           __fd_check_map;         \
            ADD FD_FAIL_MASK,           __fd_fail_mask;         \
            ADD FD_OFFSPEC_MASK,        __fd_offspec_mask;      \
            ADD FD_MAINT_MASK,          __fd_maint_mask;        \
            ADD FD_CHECK_MASK,          __fd_check_mask;        \
            ADD FD_FAIL_ALM,            __fd_fail_alm;          \
            ADD FD_OFFSPEC_ALM,         __fd_offspec_alm;       \
            ADD FD_MAINT_ALM,           __fd_maint_alm;         \
            ADD FD_CHECK_ALM,           __fd_check_alm;         \
            ADD FD_FAIL_PRI,            __fd_fail_pri;          \
            ADD	FD_OFFSPEC_PRI,         __fd_offspec_pri;       \
            ADD	FD_MAINT_PRI,           __fd_maint_pri;         \
            ADD	FD_CHECK_PRI,           __fd_check_pri;         \
            ADD	FD_SIMULATE,            __fd_simulate;          \
            ADD	FD_RECOMMEN_ACT,        __fd_recommen_act;

#define     __FD_PARAMS_VIEW1                                       \
            ADD VL_FD_FAIL_ACTIVE,      PARAM.FD_FAIL_ACTIVE;       \
            ADD VL_FD_OFFSPEC_ACTIVE,   PARAM.FD_OFFSPEC_ACTIVE;    \
            ADD VL_FD_MAINT_ACTIVE,     PARAM.FD_MAINT_ACTIVE;      \
            ADD VL_FD_CHECK_ACTIVE,     PARAM.FD_CHECK_ACTIVE;      \
            ADD VL_FD_RECOMMEN_ACT,     PARAM.FD_RECOMMEN_ACT;

#define     __FD_PARAMS_VIEW3                                       \
            ADD VL_FD_FAIL_ACTIVE,      PARAM.FD_FAIL_ACTIVE;       \
            ADD VL_FD_OFFSPEC_ACTIVE,   PARAM.FD_OFFSPEC_ACTIVE;    \
            ADD VL_FD_MAINT_ACTIVE,     PARAM.FD_MAINT_ACTIVE;      \
            ADD VL_FD_CHECK_ACTIVE,     PARAM.FD_CHECK_ACTIVE;      \
            ADD VL_FD_SIMULATE,         PARAM.FD_SIMULATE;          \
            ADD VL_FD_RECOMMEN_ACT,     PARAM.FD_RECOMMEN_ACT;

#define     __FD_PARAMS_VIEW4                                       \
            ADD VL_FD_VER,         		PARAM.FD_VER;				\
            ADD VL_FD_FAIL_MAP,         PARAM.FD_FAIL_MAP;          \
            ADD VL_FD_OFFSPEC_MAP,      PARAM.FD_OFFSPEC_MAP;       \
            ADD VL_FD_MAINT_MAP,        PARAM.FD_MAINT_MAP;         \
            ADD VL_FD_CHECK_MAP,        PARAM.FD_CHECK_MAP;         \
            ADD VL_FD_FAIL_MASK,        PARAM.FD_FAIL_MASK;         \
            ADD VL_FD_OFFSPEC_MASK,     PARAM.FD_OFFSPEC_MASK;      \
            ADD VL_FD_MAINT_MASK,       PARAM.FD_MAINT_MASK;        \
            ADD VL_FD_CHECK_MASK,       PARAM.FD_CHECK_MASK;        \
            ADD VL_FD_FAIL_PRI,         PARAM.FD_FAIL_PRI;          \
            ADD VL_FD_OFFSPEC_PRI,      PARAM.FD_OFFSPEC_PRI;       \
            ADD VL_FD_MAINT_PRI,        PARAM.FD_MAINT_PRI;         \
            ADD VL_FD_CHECK_PRI,        PARAM.FD_CHECK_PRI;

/*
**********************************************************************
** Generic enumeration definitions for FD parameters
**********************************************************************
*/

#define __FD_BITENUMS          												\
        {0x00000001,    [check_label],     [check_help]					},  \
        {0x00000002,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000004,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000008,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000010,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000020,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000040,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000080,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000100,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000200,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000400,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00000800,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00001000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00002000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00004000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00008000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00010000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00020000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00040000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00080000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00100000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00200000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00400000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x00800000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x01000000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x02000000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x04000000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x08000000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x10000000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x20000000,    [mfg_specific_label],    [mfg_specific_help]	},  \
        {0x40000000,    [mfg_specific_label],    [mfg_specific_help]	}
 /*       {0x80000000,    [mfg_specific_label],    [mfg_specific_help] */

/*
**********************************************************************
** Mode definitions for WRITE_MODE attribute
**********************************************************************
*/

#define _REMOTE_OUTPUT 0x01
#define _REMOTE_CASCADE 0x02
#define _CASCADE 0x04
#define _AUTOMATIC 0x08
#define _MANUAL 0x10
#define _LOCKED 0x20
#define _INITIALIZATION 0x40
#define _OUT_OF_SERVICE 0x80

/*
**********************************************************************
** Convenience macros for adding Positioner parameters from
** groups to TB parameter redefinitions
**********************************************************************
*/

#define	__POS_GROUP_A_PARAMS	\
		ADD ACT_FAIL_ACTION,		__act_fail_action ;\
		ADD ACT_MAN_ID,		__act_man_id ;\
		ADD ACT_MODEL_NUM,		__act_model_num ;\
		ADD ACT_SN,		__act_sn ;\
		ADD VALVE_MAN_ID,		__valve_man_id ;\
		ADD VALVE_MODEL_NUM,		__valve_model_num ;\
		ADD VALVE_SN,		__valve_sn ;\
		ADD VALVE_TYPE,		__valve_type ;\
		ADD XD_CAL_LOC,		__xd_cal_loc ;\
		ADD XD_CAL_DATE,		__xd_cal_date ;\
		ADD XD_CAL_WHO,		__xd_cal_who ;


#define	__POS_GROUP_B_PARAMS	\
		ADD FINAL_VALUE,		__final_value ;\
		ADD FINAL_VALUE_RANGE,		__final_value_range ;\
		ADD FINAL_VALUE_CUTOFF_HI,		__final_value_cutoff_hi ;\
		ADD FINAL_VALUE_CUTOFF_LO,		__final_value_cutoff_lo ;\
		ADD FINAL_POSITION_VALUE,		__final_position_value ;\
		ADD WORKING_POS,		__working_pos ;\
		ADD WORKING_SP,		__working_sp ;\
		ADD DEVIATION_DEADBAND,		__deviation_deadband ;\
		ADD DEVIATION_TIME,		__deviation_time ;\
		ADD DEVIATION_VALUE,		__deviation_value ;\
		ADD POS_ALERT_HI,		__pos_alert_hi ;\
		ADD POS_ALERT_LO,		__pos_alert_lo ;\
		ADD RATED_TRAVEL,		__rated_travel ;\
		ADD STOP_HI_POS,		__stop_hi_pos ;\
		ADD STOP_LO_POS,		__stop_lo_pos ;\
		ADD TRAVEL_ACCUM,		__travel_accum ;\
		ADD TRAVEL_UNITS,		__travel_units ;\
		ADD XD_FSTATE_VAL,		__xd_fstate_val ;

#define	__POS_GROUP_C_PARAMS	\
		ADD FINAL_VALUE_D,		__final_value_d ;\
		ADD FINAL_POSITION_VALUE_D,		__final_position_value_d ;\
		ADD WORKING_POS_D,		__working_pos_d ;\
		ADD WORKING_SP_D,		__working_sp_d ;\
		ADD XD_FSTATE_VAL_D,		__xd_fstate_val_d ;

#define	__POS_GROUP_D_PARAMS	\
		ADD XD_FSTATE_OPT,		__xd_fstate_opt ;\
		ADD CYCLE_CNTR,		__cycle_cntr ;\
		ADD SIGNAL_ACTION,		__signal_action ;\
		ADD READBACK_SELECT,		__readback_select ;\
		ADD XD_COMMAND,		__xd_command ;\
		ADD XD_COMMAND_STATE,		__xd_command_state ;\
		ADD XD_OOS_OPT,		__xd_oos_opt ;\
		ADD POS_FEATURES,		__pos_features ;

#define	__POS_GROUP_E_PARAMS	\
		ADD VST_COMMAND,		__vst_command ;\
		ADD VST_MODE,		__vst_mode ;\
		ADD VST_PAUSE,		__vst_pause ;\
		ADD VST_RESULT,		__vst_result ;\
		ADD VST_DETAILED_RESULT,		__vst_detailed_result ;

#define	__POS_GROUP_F_PARAMS	\
		ADD CLOSED_POS_DEADBAND,		__closed_pos_deadband ;\
		ADD CLOSED_POS_SHIFT,		__closed_pos_shift ;\
		ADD CUSTOM_CURVE_DESCRIPTION,		__custom_curve_description ;\
		ADD CUSTOM_CURVE_XY,		__custom_curve_xy ;\
		ADD CUSTOM_CURVE_XY_FLOAT,		__custom_curve_xy_float ;\
		ADD CYCLE_CNTR_DEADBAND,		__cycle_cntr_deadband ;\
		ADD FRICTION_UNITS,		__friction_units ;\
		ADD FRICTION,		__friction ;\
		ADD HYSTERISIS,		__hysterisis ;\
		ADD POS_DEADBAND,		__pos_deadband ;\
		ADD STROKE_TIME_CLOSED,		__stroke_time_closed ;\
		ADD STROKE_TIME_OPEN,		__stroke_time_open ;\
		ADD TRAVEL_ACCUM_DEADBAND,		__travel_accum_deadband ;\
		ADD TRIP_TIMEOUT,		__trip_timeout ;\
		ADD XD_COMMAND_FLAGS,		__xd_command_flags ;\
		ADD CYCLE_CNTR_LIM,		__cycle_cntr_lim ;

#define	__POS_GROUP_G_PARAMS	\
		ADD PST_BREAKOUT_TIME,		__pst_breakout_time ;\
		ADD PST_BREAKOUT_TIMEOUT,		__pst_breakout_timeout ;\
		ADD PST_INITIAL_START_TIME,		__pst_initial_start_time ;\
		ADD PST_INTERVAL,		__pst_interval ;\
		ADD PST_OPTIONS,		__pst_options ;\
		ADD PST_RAMP_RATE,		__pst_ramp_rate ;\
		ADD PST_STRK_TRAV,		__pst_strk_trav ;\
		ADD PST_STRK_TRAV_TIMEOUT,		__pst_strk_trav_timeout ;\
		ADD PST_COMPLETION_TIMEOUT,		__pst_completion_timeout ;

#define	__POS_GROUP_H_PARAMS	\
		ADD TORQUE_UNITS,		__torque_units ;\
		ADD TORQUE,		__torque ;

#define	__POS_GROUP_I_PARAMS	\
		ADD FST_BREAKOUT_TIME,		__fst_breakout_time ;\
		ADD FST_BREAKOUT_TIMEOUT,		__fst_breakout_timeout ;\
		ADD FST_RAMP_RATE,		__fst_ramp_rate ;\
		ADD FST_STRK_TRAV_TIMEOUT,		__fst_strk_trav_timeout ;\
		ADD FST_COMPLETION_TIMEOUT,		__fst_completion_timeout ;

#define	__POS_GROUP_J_PARAMS	\
		ADD PRESSURE_PORT_A,	__pressure_port_a ;\
		ADD PRESSURE_PORT_B,	__pressure_port_b ;\
		ADD PRESSURE_UNITS,		__pressure_units ;\
		ADD PRESSURE_SUPPLY,	__pressure_supply ;


#define	__POS_GROUP_K_PARAMS	\
		ADD CHARACTERIZATION,		__characterization ;\
		ADD STROKE_TIME_CLOSE_LIM,		__stroke_time_close_lim ;\
		ADD STROKE_TIME_OPEN_LIM,		__stroke_time_open_lim ;\
		ADD TRAVEL_ACCUM_LIM,		__travel_accum_lim ;\
		ADD TRAVEL_ACCUM_UNITS,		__travel_accum_units ;

#define	__POS_GROUP_L_PARAMS	\
		ADD INTERNAL_TEMP,		__internal_temp ;\
		ADD INTERNAL_TEMP_MIN,		__internal_temp_min ;\
		ADD INTERNAL_TEMP_MAX,		__internal_temp_max ;\
		ADD INTERNAL_TEMP_UNITS,		__internal_temp_units ;


#endif
