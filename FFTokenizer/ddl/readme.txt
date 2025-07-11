Standard DD Library  
Version:   3.70 Release
Released:  2011-04-28

Minimum DD Tools/Services/ Compatibility
-----------------------------------------
To build w/ standard empty no_download/upload_wanted collections: Tokenizer v5.2.0
To build w/o standard empty no_download/upload_wanted collections: Tokenizer v5.1.2
-----------------------------------------

Copyright 1999-2010  Field Foundation  All Rights reserved.

!! IMPORTANT!!  
This release does not include import-ready files.  You must tokenize the standard library with your current
version of the Tokenizer before you will be able to import the files needed for creating your DD's.  Run the
batchfile "make_all_dd4.bat" to tokenize the complete library into DDv4 binaries (.ffo/.sym) or "make_all_dd5.bat"
to tokenize the complete library into DDv5 binaries (.ff5/.sy5).  If you are developing DDs for devices that are
compatible only with v2 of the Standard DD Library (non block-specific items), use "make_all_dd4_lib2.bat" and
"make_all_dd5_lib2.bat" to build the library.


How this library is organized:

For device developers making new DDs, using latest revisions in library, consult STD-DEFS.H for latest rev levels.
Developers have option of hardcoding Device revision level and DD revision level or using symbol names to take the
current revision level in STD-DEFS.H

Latest Source code for DDL files will be in the root level (DDL) directory.  The coding for the directory structure
of the library binaries will be /DDL/RELEASE/000000/nnnn/ where nnnn is the profile number of the block as designated
in TN-003.  The binary files coded ddrr.ffo/ff5 in the nnnn directory will be the files derived from the source where
dd is represents the profile revision of the block and rr the DD revision.

There is some beta level code in the library.  It is marked by assigning it a profile revision number of 0xFF.  Therefore,
all binaries and frozen source containing that number in the dd filed of ddrr denote beta level code.
When code advances from beta level to first release, it will begin first release with dd = 0x01.

The source files in the DDL directory can be identified as released or beta by examining the revision history, file header
lines and also noting the symbol used for profile revision and dd revision. It may be useful to the developer to look at
source code, and even compare versions of source code.

NOTE on HTK Source: included source DDL from HTK product "as is" for DD development reference.
ARs against HTK DDL should not be filed against this product (DL-006); ARs against
the HTK should be filed by those using it for host evaluation and testing.  The
HTK source is maintained independently of this product and may not be up-to-date
with subsequent releases of this product.

Changes since 3.60

- added new files for Temperature & Pressure TB Profiles
- finalized Flow TB and Totalizer FB
- finalized RIO files

AR #	Description
3982	added TRANSDUCER_TYPE_VER to new pressure profile
3984	added CAL_VALUE to new pressure profile
3993	added CAL_VALUE to new single-sensor temp profile and CAL_VALUE_1 and CAL_VALUE_2 to new dual-sensor temp profile
3994	added TRANSDUCER_TYPE_VER to new temp profile
5341	added TRANSDUCER_TYPE to all views of new temp profile
5632	undone changes done in AR4228 to be consistent with FF-912; __sub_code_32 changed back to UNSIGNED_INTEGER (4)
5663	added new temperature and pressure profiles
5668	changed TRANSDUCER_OPTS to XD_OPTS in new pressure and temp profiles

Changes since 3.50

- added beta validation DDL for WIO blocks
- finalized SIF-DO block
- added standard empty no_download/upload_wanted collections to blocks with option to build in batch files

AR #	Description
3438	set additional class attributes for parameters to correlate with FB & TB spec updates
4223	updated Flow TB view definitions to correlate with FF-908 DPS 3.1
4228	changed __sub_code_32 to BIT_ENUMERATED
4231	added VL_FD_VER to view 4 redefinition macro for Field Diagnostics
4233	corrected RESET_IN enumerations
4234	corrected VALUE item reference for OUT_TRIP and OUT_PRETRIP
4274	changed RESET_IN item references to those of class INPUT
4324	added Tefulong Group Co., Ltd. and Heinrichs Messtechnik mfg id to lib
4372	editorial on labels for faultstate_off and faultstate_set in dictionary
4416	added SAIC mfg id to lib
4437	corrected BKCAL_IN_D item references to those of class INPUT
4461	corrected member names for FD_SIMULATE to match with spec; member IDs not changed
4487	removed _MODE_LOCKED and _MODE_INITIALIZATION from __target_mode as they are invalid target modes
4497	added |*ja| flag to some non-SI-units in standard dictionary
4521	added definition for TRANSDUCER_OPTS
4522	added TRANSDUCER_TYPE_VER and TRANSDUCER_OPTS to FLow TB def as per spec
4536	added MORGAN KOREA LTD. mfg id to lib
4538	added VL_BKCAL_OUT_D to SIF DO view 1 as per spec
4617	added Hollysys mfg id to lib
4626	changed item and member names from CAPABILITY_LEVEL to CAPABILITY_LEV as per spec; item/member IDs not changed
4628	added FLUID COMPONENTS INTL mfg id to lib
4658	various corrections for Flow TB as per spec
4673	updated name of manufacturer Cidra Corporation to "CiDRA Corporate Services"
4815	removed 0x0 bit-enumerations as TOK 5.1.3 beta+ gives error
4863	added empty standard no_download/upload_wanted collections to all profiles to correlate with FF-946 requirements and ITK 6.0
5044	added SIF_ITK_VER defintion
5071	editorial on primary_value_help in standard dictionary
5080	added Forbes Marshall mfg id to lib
5095	added generic bit-enumeration definitions to FD parameters to assist with prototyping and development
5100	removed “Generate reset event” option from INTEG_OPTS as per spec
5151	changed revision number in lib batch files to 3.60
5152	editorial on block_err_desc in standard dictionary
5157	changed __act_man_id type to UNSIGNED_INTEGER(4) as per spec
5158	changed __act_model_num handling to R/W as per spec
5159	changed __act_man_id handling to R/W as per spec
5160	changed __act_sn handling to R/W as per spec
5161	changed __valve_man_id handling to R/W as per spec
5162	changed __valve_model_num handling to R/W as per spec
5163	changed __valve_sn handling to R/W as per spec
5164	changed __valve_type handling to R/W as per spec
5178	changed __totalizer_opts to 2 bytes as per spec
5203	corrected unit relations in flow_cb.ddl, temp_cb.ddl, & temp_c2s.ddl
5248	finalized SIF-DO block to FF-895 FS 1.4; made release version
5282	new variable item for STATUS_OPTS in SIF-AI to restrict enumerations
5291	added definitions for SOFTWARE_REV and HARDWARE_REV to standard parameters
5337	added DET-TRONICS, Cameron, and Young Tech mfg id to lib

Changes since 3.41

- contains release DDL for Positioner TB
- added beta validation DDL for RIO blocks

AR #	Description
2227	ACK_OPTION enumerations updated per latest spec
2345	corrected record members for IN_D parameters in adv_parm.ddl
2710	added Japaneese SI-Unit flags to non-SI-Units in standard.dct/dc8
2945	beta DDL added for flow totalizer
2997	changed handling of PST_BREAKOUT_TIME to read only
2998	changed handling of READBACK_SELECT to read & write
3036	changed handling of HI/LO(_HI/_LO)_LIMX parameters to read only
3057	added DDL for Complex TB, Analog, Discrete, & Analog/Discrete Positioner TBs
3079	added POS_FEATURES parameter for Positioner TBs
3100	added manafacturer ID for Phoenix Contact
3101	added manafacturer IDs for Hawk & Koso Service Co., Ltd.
3102	added operate enumerations to GRANT_DENY parameter
3146	manafacturer ID 0x424946 renamed to Biffi Italia srl
3225	changed DEV_TYPE from UInt to Enum as per FF-901
3236	added COMPATABILITY_REV parameter
3450	changed handling of SENSOR_SN parameter to read & write
3504	added manufacturer ID for CQSIC Co., Ltd
3641	corrected record members for OUT_EXP & OUT_REM
3656	corrected/extended enumerations for SENSOR_TYPE, TRANSDUCER_TYPE, & PRIMARY_VALUE parameters as per latest TN-016
3786	added manufacturer ID for  SUPCON
3845	added manufacturer ID for Sense Eletronica LTDA
3887	editorial correction in on deny_local in standard dictionary
3910	added missing micro character for unit_code_1679 in standard dictionary
3943	added manufacturer ID for Fieldbus Diagnostics LLC
3992	added CAL_VALUE to standard transducer parameters
3999	corrected STATUS member of OUT & OUT_D to read only variable
4000	corrected STATUS member of SP & SP_D to read only variable
4006	corrected some view-list members for SIF RB
4031	added manufacturer IDs for Thermo Fisher Scientific & Heinrichs Messtechnik
4038	added DDL for profiled custom function blocks
4116	corrected bit enumerations 9-11 for ALARM_SUM
4143	changed item name __event_update to __update_evt to be consistent with rest of DDL; item ID# did not change
4171	added  Bit 12 Units Conversion to IO_OPTS enumerations
4184	changed TOTALIZER_OPTS and FAILURE_OPTS from BIT_ENUMERATED(2) to ENUMERATED(1)
4185	added CAL_VALUE to flow TB
4109	removed unit relation of optional/common-practice parameters for flow TB
4200	added OUT_TRIP & OUT_PTRIP to view lists of flow totalizer
4201	corrected unit relation item reference PARAM.PRESET_IN to PARAM.PRESET_IN.VALUE
4203	modified __fcb_view_4 for multiple views; flow DPS should be updated accordingly
4205	added PRE_TRIP to view 4 in flow totalizer
4209	corrected bit 0 enumeration in FD parameters to be "Check"

Changes since 3.4

- added UTF-8 formated standard dictionary (standard.dc8)
- updated source DDL from HTK product with device-level menus and cross-block enhancements for DD development reference.

AR #	Description
2471	fixed German units that had ² and ³ inverted in standard.dct
3499	CRITICAL: replaced all characters (°,ø,µ,Å,²,³) that inadvertently got striped from standard.dct in version 3.30
3609	corrected "guage" to "gauge" in three unit descriptions in standard.dct
3847	put cubic character back in unit codes 1671, 1672, 1674, & 1677 in standard.dct
3848	put micro character back in unit codes 1675, 1676, 1677, & 1678 in standard.dct
3849	corrected "propogate" to "propagate" for status_opt_fail_ strings in standard.dct

Changes since 3.3

- verified SIF DDL against FF-895 FS 1.0 for SIF-RB and SIF-AI blocks; made DDL release for those blocks

Changes since 3.2

- added DDL for Field Diagnostics and SIF blocks
- included source DDL from HTK product "as is" for DD development reference.

AR #	Description
3471	added unit codes 1686-1688
3470	added unit codes 1684 & 1685
3469	added unit codes 1689-1712
3343	added convenience macros to com_tbls.h for adding FD parameters to RB redef;
	added FD params to RB in ff_test.ddl
3005	added HTK source to DDL "as is" (see readme)
2934	added macro definitions for mode values in com_tbls.h
2901	added tok-time macro HSE to use __views_index32 in characteristics for HSE devices
2883	added enumerations for Bits 8-12 in __features and __feature_sel
2862	added ENOTEC GmbH to __manufac_id
2692	changed __invert_opts to type BIT_ENUMERATED
2668	added prog_resblock.ddl for Programmable Resource profile 0x0143
2583	added Biffi Italia to __manufac_id
2538	added unit codes 1715-1717
2531	added unit code 1714
2529	added unit code 1713
2298	added added Chemtrac Systems, Inc. to __manufac_id
2297	added Dandong Top Instrument to __manufac_id
2295	changed comment for variable __control_opts_ra to bit-enumerated 0x800202DA
2294	change comment in symbols.txt in folder \000000\0131 for proper items range
2258	added Cidra Corporation & HACH Company to __manufac_id
2211	added Hach Company to __manufac_id
2197	changed __bitstring_contained_rw size to (16)
2128	added enumerations for Bit 10 & 11 in STATUS_OPTS
2126	updated CONTROL_OPTS to make Bit 6 "Track if Bad TRK_IN_D"
2123	changed HANDLING of __unacknowledged_evt to READ & WRITE
2122	changed __fstate_status type-size to (2)
2101	removed PARAM.SENSOR_OFFSET & PARAM.LEVEL_OFFSET from UNIT __unit_tcb_sensor_range
2055	changed type of __sensor_fill_fluid & __sensor_isolator_mtl to ENUMERATED(2)
2006	changed __module_sn to type VISIBLE(32)
1992	fixed unit-relation for calc a/d blocks to __units_index

Changes since 3.1

AR #	Description
2939	translated label & help strings for temperatur blocks to German
2140	Changed MTL to MTL Instruments.
2170	Added manufacturer name/ID for Beck, Harold & Sons.
2171	Added manufacturer name/ID for Dynamic Flow Computers.
2175	Added manufacturer name/ID for Beamex Oy Ab.
2176	Added manufacturer name/ID for Brooks Instrument.
2178	Added manufacturer name/ID for Rexa, Koso America.
2182	Added manufacturer name/ID for Numatics Inc.
2285	modified profiles to reserve 0x010c for generic transducer blocks
2287	transducer parameters moved from profile 0x010c to 0x013e
2351	created batch files to build Lib. v2 compatible library (non block-specific items)
2683	removed make_new batch files for ease of maintanance; files seldom used
2819	removed BLTIN_BAD_POINTER from builtins.h (DDS did not use)
2820	added BLTIN_BLOCK_NOT_FOUND to builtins.h