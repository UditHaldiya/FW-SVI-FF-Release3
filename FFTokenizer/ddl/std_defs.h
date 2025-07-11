/*
** @(#)std_defs.h   1.32beta  2007-10-17
**
** FF common defines used by the standard blocks
** Filename: std_defs.h
** Spec revision:   FF-900 FS 1.4   DDL spec
**                  FF-890 FS 1.4   FBAP spec part 1
**                  FF-891 FS 1.4   FBAP spec part 2
**                  FF-903 PS 2.0   TBP spec
**                  FF-895 PS 1.1   SIS FBAP spec part 1
** Date of last change: 2006-08-10
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
** (c) Fieldbus Foundation(TM) (1994-2009)
**
*/

/*
** HISTORY:
** JPH   Revision 0.9  19950414
** TAB   Revision 1.0  19961015
** QLQ   Revision 1.2  19970731
** DAD   revision 1.21beta 1999-03-04
** SBM   revision 1.22beta 1999-12-01
** FI    revision 1.3  2005-11-09
**       fixed comment labels
**       added resource block 3
** ED    revision 1.31beta 2006-08-10
**		 added dual sensor temperature block
** ED 	 revision 1.32beta 2007-10-17
**		 added SIS blocks
** MS	 bumped up dd_rev numbers for blocks
**		 changed by AR2351 2007-07-17
** MS	 added ddl for programable resource AR2668 2007-11-12
** MS	 ARs 2285 & 2287; 2007-11-21
** TAB added definitions for flow totalizer block 2008-06-19
** ED  change from SIS to SIF 2008-12-03
** MS  changed profile- and DD-revisions from "beta" to "rel" and set to 0x01
**     for RB, AI, and standard-params 2008.12.15
** MS	ARs 3057, 4038 -- 2009.06.15
** TAB added definitions for RIO TBs 2009-08-10
** MS	ARs 5248 -- 2010.10.15
** MS	ARs 5663 -- 2011.04.22
*/

#ifndef  __STD_DEFS_H
#define  __STD_DEFS_H

/*
**********************************************************************
** Define the device type defines used within the DD source files
**********************************************************************
*/
#define  __FF                    0x00

#define  __STD_PARM                      0x0100      /* decimal 256 */
#define  __AI_BLOCK                      0x0101      /* decimal 257 , Analog Input */
#define  __AO_BLOCK                      0x0102      /* decimal 258 , Analog Output */
#define  __DI_BLOCK                      0x0103      /* decimal 259 , Discrete Input */
#define  __DO_BLOCK                      0x0104      /* decimal 260 , Discrete Output */
#define  __BG_BLOCK                      0x0105      /* decimal 261 , Bias Gain */
#define  __ML_BLOCK                      0x0106      /* decimal 262 , Manual Loader */
#define  __PD_BLOCK                      0x0107      /* decimal 263 , PD */
#define  __PID_BLOCK                     0x0108      /* decimal 264 , PID */
#define  __RA_BLOCK                      0x0109      /* decimal 265 , Ratio */
#define  __CS_BLOCK                      0x010A      /* decimal 266 , Control Selector */
#define  __RES_BLOCK                     0x010B      /* decimal 267 , original Resource Block */
#define  __GEN_XDCR_BLOCK                0x010C      /* decimal 268 , Generic Transducer Block */
#define  __ADV_POS_BASIC                 0x010D      /* decimal 269 , Advanced Positioner Basic Device */
#define  __BASIC_POS_BASIC               0x010F      /* decimal 271 , Basic Positioner Basic Device */
#define  __DISC_POS_BASIC                0x0111      /* decimal 273 , Discrete Positioner Basic Device*/
#define  __FLOW_BASIC                    0x0113      /* decimal 275 , Flow with Calibration for Basic Device */
#define  __PRESS_BASIC                   0x0115      /* decimal 277 , Presssure with Calibration for Basic Device */
#define  __RADAR_LVL_BASIC               0x0117      /* decimal 279 , Radar Level with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_2_SENSOR    0x0119      /* decimal 281 , Temperature with Calibration for Basic Two Sensor Device */
#define  __TEMPERATURE_BASIC             0x011A      /* decimal 282 , Temperature with Calibration for Basic Device */
#define  __DEVICE_CONTROL                0x011B      /* decimal 283 , Device Control */
#define  __OUTPUT_SPLITTER               0x011C      /* decimal 284 , Output Splitter */
#define  __SIGNAL_CHARACTERIZER          0x011D      /* decimal 285 , Signal Characterizer */
#define  __LEAD_LAG                      0x011E      /* decimal 286 , Lead Lag */
#define  __DEADTIME                      0x011F      /* decimal 287 , Deadtime */
#define  __INTEGRATOR                    0x0120      /* decimal 288 , Integrator */
#define  __PULSE_INPUT                   0x0121      /* decimal 289 , Pulse Input */
#define  __COMPLEX_AO                    0x0122      /* decimal 290 , Complex Analog Output */
#define  __COMPLEX_DO                    0x0123      /* decimal 291 , Complex Discrete Output */
#define  __STEP_OUTPUT_PID               0x0124      /* decimal 292 , Step Output PID */
#define  __SETPOINT_RAMP_GENERATOR       0x0125      /* decimal 293 , Setpoint Ramp Generator */
#define  __INPUT_SELECTOR                0x0126      /* decimal 294 , Input Selector */
#define  __ARITHMETIC                    0x0127      /* decimal 295 , Arithmetic */
#define  __CALCULATE_ANALOG              0x0128      /* decimal 296 , Calculate Analog version */
#define  __TIMER                         0x0129      /* decimal 297 , Timer */
#define  __ANALOG_ALARM                  0x012A      /* decimal 298 , Analog Alarm */
#define  __DISCRETE_ALARM                0x012B      /* decimal 299 , Discrete Alarm */
#define  __ANALOG_HUMAN_INTERFACE        0x012C      /* decimal 300 , Analog Human Interface */
#define  __DISCRETE_HUMAN_INTERFACE      0x012D      /* decimal 301 , Discrete Human Interface */
#define  __MDI                           0x012E      /* decimal 302 , Multiple Discrete Input */
#define  __MDO                           0x012F      /* decimal 303 , Multiple Discrete Input */
#define  __MAI                           0x0130      /* decimal 304 , Multiple Discrete Input */
#define  __MAO                           0x0131      /* decimal 305 , Multiple Discrete Input */
#define  __STD_MIO_PARM                  0x0132      /* decimal 306 , Standard Parms for MIO blocks */
#define  __RES_BLOCK_2                   0x0133      /* decimal 307 , The new (1999) Resource Block */
#define  __ADV_PARAM                     0x0134      /* decimal 308 , Advanced block parameters */
#define  __CALCULATE_DISCRETE            0x0135      /* decimal 309 , Calculate Discrete version */
#define  __COMPLEX_TB            		 0x013D      /* decimal 317 , Complex Transducer Block */
#define  __STD_XDCR_PARM				 0x013E		 /* decimal 318 , Transducer Parameters */
#define  __CUSTOM_INPUT_BLOCK			 0x013F		 /* decimal 319 , Custom Input Block */
#define  __CUSTOM_CONTROL_BLOCK			 0x0140		 /* decimal 320 , Custom Control Block */
#define  __CUSTOM_OUTPUT_BLOCK			 0x0141		 /* decimal 321 , Custom Output Block */
#define  __CUSTOM_CALC_BLOCK			 0x0142		 /* decimal 322 , Custom Calculation Block */
#define  __PROG_RES_BLOCK                0x0143      /* decimal 323 , Resource Block for Programmable Resource */
#define  __FLOW_TOTALIZER                0x0144      /* decimal 324 , Flow Totalizer */
#define  __POS_ANALOG                	 0x0145      /* decimal 325 , Positioner Analog TB */
#define  __POS_DISCRETE                	 0x0146      /* decimal 326 , Positioner Discrete TB */
#define  __POS_ANALOG_DISCRETE           0x0147      /* decimal 327 , Positioner Analog/Discrete TB */
#define  __RIO_ASSOC_PRIMARY_BLOCK       0x0148      /* decimal 328 , RIO Association Block (primary) */
#define  __RIO_ASSOC_BLOCK               0x0149      /* decimal 329 , RIO Association Block  */
#define  __RIO_H1_BLOCK                  0x014B      /* decimal 331 , Remote IO H1 Module Transducer Block */
#define  __RIO_HART_BLOCK                0x014C      /* decimal 332 , Remote IO HART Transducer block */
#define  __RIO_MBI64_BLOCK               0x014D      /* decimal 333 , Multiple Binary Input (64) */
#define  __RIO_MBO64_BLOCK               0x014E      /* decimal 334 , Mulitple Binary Ouptut (64) */
#define  __RIO_MAI16_BLOCK               0x014F      /* decimal 335 , Multiple Analog Input (16) */
#define  __RIO_MAO16_BLOCK               0x0150      /* decimal 336 , Multiple Analog Output (16) */
#define  __RIO_VFD_BLOCK                 0x0151      /* decimal 337 , Remote IO Extended VFD */
#define  __RIO_PARM                      0x0152      /* decimal 338 , Standard RIO Parameters */
#define  __RIO_XDCR_PARM                 0x0153      /* decimal 339 , Standard RIO Transducer Parameters */
#define  __RIO_ASSOC_PARM                0x0154      /* decimal 340 , Standard Association Block Parameters */
#define  __RIO_HART_XDCR_PARM            0x0155      /* decimal 341 , Standard HART Transducer Parameters */
#define  __RIO_WLESS_HART_BLOCK          0x0156      /* decimal 342 , Remote IO Wireless Hart Block */
#define  __PRESS_BASIC2                	 0x0158      /* decimal 344 , Presssure with Calibration for Basic Device 2 */
#define  __TEMPERATURE_BASIC_2_SENSOR2   0x0159      /* decimal 345 , Temperature with Calibration for Basic Two Sensor Device 2 */
#define  __TEMPERATURE_BASIC2	         0x0160      /* decimal 346 , Temperature with Calibration for Basic Device 2 */
#define  __SIF_PARM                      0x1000      /* decimal 4096, SIF Parameters */
#define  __SIF_RES_BLOCK                 0x1001      /* decimal 4097, SIF Resource Block */
#define  __SIF_AI_BLOCK                  0x1002      /* decimal 4098, SIF Analog Input */
#define  __SIF_DO_BLOCK                  0x1004      /* decimal 4100, SIF Discrete Output */
#define  __RIO_BLOCK                     0x2000      /* decimal 8192 , Remote IO Transducer Block */

/*
**********************************************************************
** Define the device revision and DD revision defines used within the DD source files
**********************************************************************
*/
#define  __STD_XDCR_PARM_beta_dev_rev                 0xFF
#define  __ADV_POS_BASIC_beta_dev_rev                 0xFF      /*  Advanced Positioner Basic Device */
#define  __BASIC_POS_BASIC_beta_dev_rev               0xFF      /*  Basic Positioner Basic Device */
#define  __DISC_POS_BASIC_beta_dev_rev                0xFF      /*  Discrete Positioner Basic Device*/
#define  __FLOW_BASIC_beta_dev_rev                    0xFF      /*  Flow with Calibration for Basic Device */
#define  __PRESS_BASIC_beta_dev_rev                   0xFF      /*  Presssure with Calibration for Basic Device */
#define  __RADAR_LVL_BASIC_beta_dev_rev               0xFF      /*  Radar Level with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_beta_dev_rev             0xFF      /*  Temperature with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_2_SENSOR_beta_dev_rev    0xFF      /*  Temperature with Calibration for Basic 2 Sensor Device */
#define  __DEVICE_CONTROL_beta_dev_rev                0xFF      /*  Device Control */
#define  __OUTPUT_SPLITTER_beta_dev_rev               0xFF      /*  Output Splitter */
#define  __SIGNAL_CHARACTERIZER_beta_dev_rev          0xFF      /*  Signal Characterizer */
#define  __LEAD_LAG_beta_dev_rev                      0xFF      /*  Lead Lag */
#define  __DEADTIME_beta_dev_rev                      0xFF      /*  Deadtime */
#define  __INTEGRATOR_beta_dev_rev                    0xFF      /*  Integrator */
#define  __PULSE_INPUT_beta_dev_rev                   0xFF      /*  Pulse Input */
#define  __COMPLEX_AO_beta_dev_rev                    0xFF      /*  Complex Analog Output */
#define  __COMPLEX_DO_beta_dev_rev                    0xFF      /*  Complex Discrete Output */
#define  __STEP_OUTPUT_PID_beta_dev_rev               0xFF      /*  Step Output PID */
#define  __SETPOINT_RAMP_GENERATOR_beta_dev_rev       0xFF      /*  Setpoint Ramp Generator */
#define  __INPUT_SELECTOR_beta_dev_rev                0xFF      /*  Input Selector */
#define  __ARITHMETIC_beta_dev_rev                    0xFF      /*  Arithmetic */
#define  __CALCULATE_ANALOG_beta_dev_rev              0xFF      /*  Calculate */
#define  __TIMER_beta_dev_rev                         0xFF      /*  Timer */
#define  __ANALOG_ALARM_beta_dev_rev                  0xFF      /*  Analog Alarm */
#define  __DISCRETE_ALARM_beta_dev_rev                0xFF      /*  Discrete Alarm */
#define  __ANALOG_HUMAN_INTERFACE_beta_dev_rev        0xFF      /*  Analog Human Interface */
#define  __DISCRETE_HUMAN_INTERFACE_beta_dev_rev      0xFF      /*  Discrete Human Interface */
#define  __MDI_beta_dev_rev                           0xFF      /*  Multiple Discrete Input */
#define  __MDO_beta_dev_rev                           0xFF      /*  Multiple Discrete Input */
#define  __MAI_beta_dev_rev                           0xFF      /*  Multiple Discrete Input */
#define  __MAO_beta_dev_rev                           0xFF      /*  Multiple Discrete Input */
#define  __STD_MIO_PARM_beta_dev_rev                  0xFF      /*  Standard Parms for MIO blocks */
#define  __RES_BLOCK_2_beta_dev_rev                   0xFF      /*  The new (1999) Resource Block */
#define  __PROG_RES_BLOCK_beta_dev_rev                0xFF      /*  Resource Block for Programmable Resource */
#define  __CALCULATE_DISCRETE_beta_dev_rev            0xFF      /*  Calculate */
#define  __SIF_DO_BLOCK_beta_dev_rev                  0xFF      /*  SIF Discrete Output block */
#define  __GEN_XDCR_BLOCK_beta_dev_rev                0xFF      /*  Generic Transducer Block */
#define  __FLOW_TOTALIZER_beta_dev_rev                0xFF      /*  Flow Totalizer */
#define  __RIO_MAI16_BLOCK_beta_dev_rev               0xFF      /*  Remote IO MAI16 Block */
#define  __RIO_MAO16_BLOCK_beta_dev_rev               0xFF      /*  Remote IO MAO16 Block */
#define  __RIO_MBI64_BLOCK_beta_dev_rev               0xFF      /*  Remote IO MBI64 Block */
#define  __RIO_MBO64_BLOCK_beta_dev_rev               0xFF      /*  Remote IO MBO64 Block */
#define  __RIO_PARM_beta_dev_rev                      0xFF      /*  Remote IO MBO64 Block */
#define  __RIO_ASSOC_PRIMARY_BLOCK_beta_dev_rev       0xFF      /*  Remote IO Association Block (primary) */
#define  __RIO_ASSOC_BLOCK_beta_dev_rev               0xFF      /*  Remote IO Association Block */
#define  __RIO_HART_BLOCK_beta_dev_rev                0xFF      /*  Remote IO HART Transducer block */
#define  __RIO_XDCR_PARM_beta_dev_rev                 0xFF      /*  Standard RIO Transducer Parameters */
#define  __RIO_HART_XDCR_PARM_beta_dev_rev            0xFF      /*  Standard RIO HART Transducer Parameters */
#define  __RIO_H1_BLOCK_beta_dev_rev                  0xFF      /*  Standard RIO H1 Transducer Block */
#define  __RIO_VFD_BLOCK_beta_dev_rev                 0xFF      /*  Remote IO Extended VFD */
#define  __RIO_WLESS_HART_BLOCK_beta_dev_rev          0xFF      /*  Remote IO Wireless Hart Block */
#define  __RIO_BLOCK_beta_dev_rev                     0xFF      /*  Remote IO Conv I/O Block */

#define  __STD_XDCR_PARM_beta_dd_rev                 0x04
#define  __ADV_POS_BASIC_beta_dd_rev                 0x03      /*  Advanced Positioner Basic Device */
#define  __BASIC_POS_BASIC_beta_dd_rev               0x03      /*  Basic Positioner Basic Device */
#define  __DISC_POS_BASIC_beta_dd_rev                0x03      /*  Discrete Positioner Basic Device*/
#define  __FLOW_BASIC_beta_dd_rev                    0x05      /*  Flow with Calibration for Basic Device */
#define  __PRESS_BASIC_beta_dd_rev                   0x02      /*  Presssure with Calibration for Basic Device */
#define  __RADAR_LVL_BASIC_beta_dd_rev               0x03      /*  Radar Level with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_beta_dd_rev             0x02      /*  Temperature with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_2_SENSOR_beta_dd_rev    0x01      /*  Temperature with Calibration for Basic 2 Sensor Device */
#define  __DEVICE_CONTROL_beta_dd_rev                0x02      /*  Device Control */
#define  __OUTPUT_SPLITTER_beta_dd_rev               0x02      /*  Output Splitter */
#define  __SIGNAL_CHARACTERIZER_beta_dd_rev          0x01      /*  Signal Characterizer */
#define  __LEAD_LAG_beta_dd_rev                      0x02      /*  Lead Lag */
#define  __DEADTIME_beta_dd_rev                      0x02      /*  Deadtime */
#define  __INTEGRATOR_beta_dd_rev                    0x02      /*  Integrator */
#define  __PULSE_INPUT_beta_dd_rev                   0x04      /*  Pulse Input */
#define  __COMPLEX_AO_beta_dd_rev                    0x04      /*  Complex Analog Output */
#define  __COMPLEX_DO_beta_dd_rev                    0x04      /*  Complex Discrete Output */
#define  __STEP_OUTPUT_PID_beta_dd_rev               0x04      /*  Step Output PID */
#define  __SETPOINT_RAMP_GENERATOR_beta_dd_rev       0x02      /*  Setpoint Ramp Generator */
#define  __INPUT_SELECTOR_beta_dd_rev                0x02      /*  Input Selector */
#define  __ARITHMETIC_beta_dd_rev                    0x02      /*  Arithmetic */
#define  __CALCULATE_ANALOG_beta_dd_rev              0x04      /*  Calculate */
#define  __TIMER_beta_dd_rev                         0x02      /*  Timer */
#define  __ANALOG_ALARM_beta_dd_rev                  0x02      /*  Analog Alarm */
#define  __DISCRETE_ALARM_beta_dd_rev                0x04      /*  Discrete Alarm */
#define  __ANALOG_HUMAN_INTERFACE_beta_dd_rev        0x02      /*  Analog Human Interface */
#define  __DISCRETE_HUMAN_INTERFACE_beta_dd_rev      0x02      /*  Discrete Human Interface */
#define  __MDI_beta_dd_rev                           0x01      /*  Multiple Discrete Input */
#define  __MDO_beta_dd_rev                           0x01      /*  Multiple Discrete Input */
#define  __MAI_beta_dd_rev                           0x01      /*  Multiple Discrete Input */
#define  __MAO_beta_dd_rev                           0x01      /*  Multiple Discrete Input */
#define  __STD_MIO_PARM_beta_dd_rev                  0x01      /*  Standard Parms for MIO blocks */
#define  __RES_BLOCK_2_beta_dd_rev                   0x02      /*  The new (1999) Resource Block */
#define  __PROG_RES_BLOCK_beta_dd_rev                0x02      /*  Resource Block for Programmable Resource */
#define  __CALCULATE_DISCRETE_beta_dd_rev            0x04      /*  Calculate */
#define  __GEN_XDCR_BLOCK_beta_dd_rev                0x02      /*  Generic Transducer Block */
#define  __FLOW_TOTALIZER_beta_dd_rev                0x04      /*  Flow Totalizer */
#define  __RIO_MAI16_BLOCK_beta_dd_rev               0xFF      /*  Remote IO MAI16 Block */
#define  __RIO_MAO16_BLOCK_beta_dd_rev               0xFF      /*  Remote IO MAO16 Block */
#define  __RIO_MBI64_BLOCK_beta_dd_rev               0xFF      /*  Remote IO MBI64 Block */
#define  __RIO_MBO64_BLOCK_beta_dd_rev               0xFF      /*  Remote IO MBO64 Block */
#define  __RIO_PARM_beta_dd_rev                      0xFF      /*  Remote IO MBO64 Block */
#define  __RIO_ASSOC_PRIMARY_BLOCK_beta_dd_rev       0xFF      /*  Remote IO Association Block (primary) */
#define  __RIO_ASSOC_BLOCK_beta_dd_rev               0xFF      /*  Remote IO Association Block */
#define  __RIO_HART_BLOCK_beta_dd_rev                0xFF      /*  Remote IO HART Transducer block */
#define  __RIO_XDCR_PARM_beta_dd_rev                 0xFF      /*  Standard RIO Transducer Parameters */
#define  __RIO_HART_XDCR_PARM_beta_dd_rev            0xFF      /*  Standard RIO HART Transducer Parameters */
#define  __RIO_H1_BLOCK_beta_dd_rev                  0xFF      /*  Standard RIO H1 Transducer Block */
#define  __RIO_VFD_BLOCK_beta_dd_rev                 0xFF      /*  Remote IO Extended VFD */
#define  __RIO_WLESS_HART_BLOCK_beta_dd_rev          0xFF      /*  Remote IO Wireless Hart Block */
#define  __RIO_BLOCK_beta_dd_rev                     0xFF      /*  Remote IO Conv I/O Block */

#define  __STD_PARM_rel_dev_rev                      0x01
#define  __AI_BLOCK_rel_dev_rev                      0x01
#define  __AO_BLOCK_rel_dev_rev                      0x01
#define  __DI_BLOCK_rel_dev_rev                      0x01
#define  __DO_BLOCK_rel_dev_rev                      0x01
#define  __BG_BLOCK_rel_dev_rev                      0x01
#define  __ML_BLOCK_rel_dev_rev                      0x01
#define  __PD_BLOCK_rel_dev_rev                      0x01
#define  __PID_BLOCK_rel_dev_rev                     0x01
#define  __RA_BLOCK_rel_dev_rev                      0x01
#define  __CS_BLOCK_rel_dev_rev                      0x01
#define  __RES_BLOCK_rel_dev_rev                     0x01
#define  __STD_XDCR_PARM_rel_dev_rev                 0x01
#define  __ADV_POS_BASIC_rel_dev_rev                 0x01      /*  Advanced Positioner Basic Device */
#define  __BASIC_POS_BASIC_rel_dev_rev               0x01      /*  Basic Positioner Basic Device */
#define  __DISC_POS_BASIC_rel_dev_rev                0x01      /*  Discrete Positioner Basic Device*/
#define  __FLOW_BASIC_rel_dev_rev                    0x01      /*  Flow with Calibration for Basic Device */
#define  __PRESS_BASIC_rel_dev_rev                   0x01      /*  Presssure with Calibration for Basic Device */
#define  __RADAR_LVL_BASIC_rel_dev_rev               0x01      /*  Radar Level with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_rel_dev_rev             0x01      /*  Temperature with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_2_SENSOR_rel_dev_rev    0x01      /*  Temperature with Calibration for Basic 2 Sensor Device */
#define  __DEVICE_CONTROL_rel_dev_rev                0x01      /*  Device Control */
#define  __OUTPUT_SPLITTER_rel_dev_rev               0x01      /*  Output Splitter */
#define  __SIGNAL_CHARACTERIZER_rel_dev_rev          0x01      /*  Signal Characterizer */
#define  __LEAD_LAG_rel_dev_rev                      0x01      /*  Lead Lag */
#define  __DEADTIME_rel_dev_rev                      0x01      /*  Deadtime */
#define  __INTEGRATOR_rel_dev_rev                    0x01      /*  Integrator */
#define  __PULSE_INPUT_rel_dev_rev                   0x01      /*  Pulse Input */
#define  __COMPLEX_AO_rel_dev_rev                    0x01      /*  Complex Analog Output */
#define  __COMPLEX_DO_rel_dev_rev                    0x01      /*  Complex Discrete Output */
#define  __STEP_OUTPUT_PID_rel_dev_rev               0x01      /*  Step Output PID */
#define  __SETPOINT_RAMP_GENERATOR_rel_dev_rev       0x01      /*  Setpoint Ramp Generator */
#define  __INPUT_SELECTOR_rel_dev_rev                0x01      /*  Input Selector */
#define  __ARITHMETIC_rel_dev_rev                    0x01      /*  Arithmetic */
#define  __CALCULATE_ANALOG_rel_dev_rev              0x01      /*  Calculate */
#define  __TIMER_rel_dev_rev                         0x01      /*  Timer */
#define  __ANALOG_ALARM_rel_dev_rev                  0x01      /*  Analog Alarm */
#define  __DISCRETE_ALARM_rel_dev_rev                0x01      /*  Discrete Alarm */
#define  __ANALOG_HUMAN_INTERFACE_rel_dev_rev        0x01      /*  Analog Human Interface */
#define  __DISCRETE_HUMAN_INTERFACE_rel_dev_rev      0x01      /*  Discrete Human Interface */
#define  __MDI_rel_dev_rev                           0x01      /*  Multiple Discrete Input */
#define  __MDO_rel_dev_rev                           0x01      /*  Multiple Discrete Input */
#define  __MAI_rel_dev_rev                           0x01      /*  Multiple Discrete Input */
#define  __MAO_rel_dev_rev                           0x01      /*  Multiple Discrete Input */
#define  __STD_MIO_PARM_rel_dev_rev                  0x01      /*  Standard Parms for MIO blocks */
#define  __RES_BLOCK_2_rel_dev_rev                   0x01      /*  The new (1999) Resource Block */
#define  __ADV_PARAM_rel_dev_rev                     0x01      /*  Advanced Parameters */
#define  __CALCULATE_DISCRETE_rel_dev_rev            0x01      /*  Calculate */
#define  __SIF_PARM_rel_dev_rev                      0x01      /*  SIF Parameters */
#define  __SIF_RES_BLOCK_rel_dev_rev                 0x01      /*  SIF Resource block */
#define  __SIF_AI_BLOCK_rel_dev_rev                  0x01      /*  SIF Analog Input block */
#define  __SIF_DO_BLOCK_rel_dev_rev                  0x01      /*  SIF Discrete Output block */
#define  __PROG_RES_BLOCK_rel_dev_rev                0x01      /*  Resource Block for Programmable Resource */
#define  __GEN_XDCR_BLOCK_rel_dev_rev                0x01      /*  Generic Transducer Block */
#define  __COMPLEX_TB_rel_dev_rev            		 0x01      /*  Complex Transducer Block */
#define  __CUSTOM_INPUT_BLOCK_rel_dev_rev			 0x01	   /*  Custom Input Block */
#define  __CUSTOM_CONTROL_BLOCK_rel_dev_rev			 0x01	   /*  Custom Control Block */
#define  __CUSTOM_OUTPUT_BLOCK_rel_dev_rev			 0x01	   /*  Custom Output Block */
#define  __CUSTOM_CALC_BLOCK_rel_dev_rev			 0x01	   /*  Custom Calculation Block */
#define  __POS_ANALOG_rel_dev_rev                	 0x01      /* 	Positioner Analog TB */
#define  __POS_DISCRETE_rel_dev_rev                  0x01      /* 	Positioner Discrete TB */
#define  __POS_ANALOG_DISCRETE_rel_dev_rev           0x01      /* 	Positioner Analog/Discrete TB */
#define  __PRESS_BASIC2_rel_dev_rev                  0x01      /*  Presssure with Calibration for Basic Device 2 */
#define  __TEMPERATURE_BASIC2_rel_dev_rev            0x01      /*  Temperature with Calibration for Basic Device 2 */
#define  __TEMPERATURE_BASIC_2_SENSOR2_rel_dev_rev   0x01      /*  Temperature with Calibration for Basic 2 Sensor Device 2 */
#define  __FLOW_TOTALIZER_rel_dev_rev                0x01      /*  Flow Totalizer */
#define  __RIO_MAI16_BLOCK_rel_dev_rev               0x01      /*  Remote IO MAI16 Block */
#define  __RIO_MAO16_BLOCK_rel_dev_rev               0x01      /*  Remote IO MAO16 Block */
#define  __RIO_MBI64_BLOCK_rel_dev_rev               0x01      /*  Remote IO MBI64 Block */
#define  __RIO_MBO64_BLOCK_rel_dev_rev               0x01      /*  Remote IO MBO64 Block */
#define  __RIO_PARM_rel_dev_rev                      0x01      /*  Remote IO MBO64 Block */
#define  __RIO_ASSOC_PRIMARY_BLOCK_rel_dev_rev       0x01      /*  Remote IO Association Block (primary) */
#define  __RIO_ASSOC_BLOCK_rel_dev_rev               0x01      /*  Remote IO Association Block */
#define  __RIO_HART_BLOCK_rel_dev_rev                0x01      /*  Remote IO HART Transducer block */
#define  __RIO_XDCR_PARM_rel_dev_rev                 0x01      /*  Standard RIO Transducer Parameters */
#define  __RIO_HART_XDCR_PARM_rel_dev_rev            0x01      /*  Standard RIO HART Transducer Parameters */
#define  __RIO_H1_BLOCK_rel_dev_rev                  0x01      /*  Standard RIO H1 Transducer Block */
#define  __RIO_VFD_BLOCK_rel_dev_rev                 0x01      /*  Remote IO Extended VFD */
#define  __RIO_WLESS_HART_BLOCK_rel_dev_rev          0x01      /*  Remote IO Wireless Hart Block */
#define  __RIO_BLOCK_rel_dev_rev                     0x01      /*  Remote IO Conv I/O Block */

#define  __STD_PARM_rel_dd_rev                       0x0A
#define  __AI_BLOCK_rel_dd_rev                       0x04
#define  __AO_BLOCK_rel_dd_rev                       0x04
#define  __DI_BLOCK_rel_dd_rev                       0x04
#define  __DO_BLOCK_rel_dd_rev                       0x04
#define  __BG_BLOCK_rel_dd_rev                       0x04
#define  __ML_BLOCK_rel_dd_rev                       0x04
#define  __PD_BLOCK_rel_dd_rev                       0x04
#define  __PID_BLOCK_rel_dd_rev                      0x04
#define  __RA_BLOCK_rel_dd_rev                       0x04
#define  __CS_BLOCK_rel_dd_rev                       0x04
#define  __RES_BLOCK_rel_dd_rev                      0x04
#define  __STD_XDCR_PARM_rel_dd_rev                 0x05
#define  __ADV_POS_BASIC_rel_dd_rev                 0x02      /*  Advanced Positioner Basic Device */
#define  __BASIC_POS_BASIC_rel_dd_rev               0x02      /*  Basic Positioner Basic Device */
#define  __DISC_POS_BASIC_rel_dd_rev                0x02      /*  Discrete Positioner Basic Device*/
#define  __FLOW_BASIC_rel_dd_rev                    0x01      /*  Flow with Calibration for Basic Device */
#define  __PRESS_BASIC_rel_dd_rev                   0x03      /*  Presssure with Calibration for Basic Device */
#define  __RADAR_LVL_BASIC_rel_dd_rev               0x02      /*  Radar Level with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_rel_dd_rev             0x05      /*  Temperature with Calibration for Basic Device */
#define  __TEMPERATURE_BASIC_2_SENSOR_rel_dd_rev    0x03      /*  Temperature with Calibration for Basic 2 Sensor Device */
#define  __DEVICE_CONTROL_rel_dd_rev                0x04      /*  Device Control */
#define  __OUTPUT_SPLITTER_rel_dd_rev               0x04      /*  Output Splitter */
#define  __SIGNAL_CHARACTERIZER_rel_dd_rev          0x02      /*  Signal Characterizer */
#define  __LEAD_LAG_rel_dd_rev                      0x04      /*  Lead Lag */
#define  __DEADTIME_rel_dd_rev                      0x04      /*  Deadtime */
#define  __INTEGRATOR_rel_dd_rev                    0x04      /*  Integrator */
#define  __PULSE_INPUT_rel_dd_rev                   0x02      /*  Pulse Input */
#define  __COMPLEX_AO_rel_dd_rev                    0x02      /*  Complex Analog Output */
#define  __COMPLEX_DO_rel_dd_rev                    0x02      /*  Complex Discrete Output */
#define  __STEP_OUTPUT_PID_rel_dd_rev               0x02      /*  Step Output PID */
#define  __SETPOINT_RAMP_GENERATOR_rel_dd_rev       0x04      /*  Setpoint Ramp Generator */
#define  __INPUT_SELECTOR_rel_dd_rev                0x04      /*  Input Selector */
#define  __ARITHMETIC_rel_dd_rev                    0x03      /*  Arithmetic */
#define  __CALCULATE_ANALOG_rel_dd_rev              0x02      /*  Calculate */
#define  __TIMER_rel_dd_rev                         0x04      /*  Timer */
#define  __ANALOG_ALARM_rel_dd_rev                  0x04      /*  Analog Alarm */
#define  __DISCRETE_ALARM_rel_dd_rev                0x02      /*  Discrete Alarm */
#define  __ANALOG_HUMAN_INTERFACE_rel_dd_rev        0x01      /*  Analog Human Interface */
#define  __DISCRETE_HUMAN_INTERFACE_rel_dd_rev      0x01      /*  Discrete Human Interface */
#define  __MDI_rel_dd_rev                           0x02      /*  Multiple Discrete Input */
#define  __MDO_rel_dd_rev                           0x02      /*  Multiple Discrete Input */
#define  __MAI_rel_dd_rev                           0x02      /*  Multiple Discrete Input */
#define  __MAO_rel_dd_rev                           0x02      /*  Multiple Discrete Input */
#define  __STD_MIO_PARM_rel_dd_rev                  0x01      /*  Standard Parms for MIO blocks */
#define  __RES_BLOCK_2_rel_dd_rev                   0x04      /*  The new (1999) Resource Block */
#define  __ADV_PARAM_rel_dd_rev                     0x05      /*  Advanced Parameters */
#define  __CALCULATE_DISCRETE_rel_dd_rev            0x02      /*  Calculate */
#define  __PROG_RES_BLOCK_rel_dd_rev                0x01      /*  Resource Block for Programmable Resource */
#define  __SIF_PARM_rel_dd_rev                      0x02      /*  SIF Parameters */
#define  __SIF_RES_BLOCK_rel_dd_rev                 0x03      /*  SIF Resource block */
#define  __SIF_AI_BLOCK_rel_dd_rev                  0x02      /*  SIF Analog Input block */
#define  __SIF_DO_BLOCK_rel_dd_rev                  0x01      /*  SIF Discrete Output block */
#define  __GEN_XDCR_BLOCK_rel_dd_rev                0x01      /*  Generic Transducer Block */
#define  __COMPLEX_TB_rel_dd_rev            		0x01      /*  Complex Transducer Block */
#define  __CUSTOM_INPUT_BLOCK_rel_dd_rev			0x01	  /*  Custom Input Block */
#define  __CUSTOM_CONTROL_BLOCK_rel_dd_rev			0x01	  /*  Custom Control Block */
#define  __CUSTOM_OUTPUT_BLOCK_rel_dd_rev			0x01	  /*  Custom Output Block */
#define  __CUSTOM_CALC_BLOCK_rel_dd_rev			 	0x01	  /*  Custom Calculation Block */
#define  __POS_ANALOG_rel_dd_rev                	0x01      /*  Positioner Analog TB */
#define  __POS_DISCRETE_rel_dd_rev                	0x01      /*  Positioner Discrete TB */
#define  __POS_ANALOG_DISCRETE_rel_dd_rev           0x01      /*  Positioner Analog/Discrete TB */
#define  __PRESS_BASIC2_rel_dd_rev                  0x01      /*  Presssure with Calibration for Basic Device 2 */
#define  __TEMPERATURE_BASIC2_rel_dd_rev            0x01      /*  Temperature with Calibration for Basic Device 2 */
#define  __TEMPERATURE_BASIC_2_SENSOR2_rel_dd_rev   0x01      /*  Temperature with Calibration for Basic 2 Sensor Device 2 */
#define  __FLOW_TOTALIZER_rel_dd_rev                0x01      /*  Flow Totalizer */
#define  __RIO_MAI16_BLOCK_rel_dd_rev               0x01      /*  Remote IO MAI16 Block */
#define  __RIO_MAO16_BLOCK_rel_dd_rev               0x01      /*  Remote IO MAO16 Block */
#define  __RIO_MBI64_BLOCK_rel_dd_rev               0x01      /*  Remote IO MBI64 Block */
#define  __RIO_MBO64_BLOCK_rel_dd_rev               0x01      /*  Remote IO MBO64 Block */
#define  __RIO_PARM_rel_dd_rev                      0x01      /*  Remote IO MBO64 Block */
#define  __RIO_ASSOC_PRIMARY_BLOCK_rel_dd_rev       0x01      /*  Remote IO Association Block (primary) */
#define  __RIO_ASSOC_BLOCK_rel_dd_rev               0x01      /*  Remote IO Association Block */
#define  __RIO_HART_BLOCK_rel_dd_rev                0x01      /*  Remote IO HART Transducer block */
#define  __RIO_XDCR_PARM_rel_dd_rev                 0x01      /*  Standard RIO Transducer Parameters */
#define  __RIO_HART_XDCR_PARM_rel_dd_rev            0x01      /*  Standard RIO HART Transducer Parameters */
#define  __RIO_H1_BLOCK_rel_dd_rev                  0x01      /*  Standard RIO H1 Transducer Block */
#define  __RIO_VFD_BLOCK_rel_dd_rev                 0x01      /*  Remote IO Extended VFD */
#define  __RIO_WLESS_HART_BLOCK_rel_dd_rev          0x01      /*  Remote IO Wireless Hart Block */
#define  __RIO_BLOCK_rel_dd_rev                     0x01      /*  Remote IO Conv I/O Block */

/*
**********************************************************************
** Define the alarm values
**********************************************************************
*/
#define  _ACKNOWLEDGED           0x01
#define  _UNACKNOWLEDGED         0x02

#define  _ENABLED                0x01
#define  _DISABLED               0x02

/*
**********************************************************************
** Define the alert standard type values
**********************************************************************
*/
#define  _STD_TYPE_LO            0x01
#define  _STD_TYPE_HI            0x02
#define  _STD_TYPE_LO_LO         0x05
#define  _STD_TYPE_HI_HI         0x06
#define  _STD_TYPE_DV_LO         0x09
#define  _STD_TYPE_DV_HI         0x0A
#define  _STD_TYPE_DISC          0x10
#define  _STD_TYPE_BLOCK         0x11
#define  _STD_TYPE_UPDATE        0x12
#define  _STD_TYPE_WRITE         0x14

/*
**********************************************************************
** Define the alert message type values
**********************************************************************
*/
#define  _MSG_TYPE_EVENT_NOTIFY  0x01
#define  _MSG_TYPE_ALARM_CLEAR   0x02
#define  _MSG_TYPE_ALARM_OCCUR   0x04

/*
**********************************************************************
** Define the trend sample type values
**********************************************************************
*/
#define  _SAMPLE_AT_EXECUTION    0x01
#define  _SAMPLE_IS_AVERAGE      0x02

/*
**********************************************************************
** Define the link object service type values
**********************************************************************
*/
#define  _LOCAL                  0x00
#define  _PUBLISH                0x01
#define  _SUBSCRIBER             0x02
#define  _CLIENT                 0x05
#define  _SERVER                 0x06
#define  _ALERT_NOTIFY           0x09
#define  _TREND_REPORT           0x11

/*
**********************************************************************
** Define the states for the function block
**********************************************************************
*/
#define  _POWER_ON               0x01
#define  _INITIALIZE             0x02
#define  _FAILURE                0x03
#define  _STANDBY                0x04
#define  _ONLINE                 0x05
#define  _ONLINE_LINKING         0x06

#endif   /*__STD_DEFS_H*/
