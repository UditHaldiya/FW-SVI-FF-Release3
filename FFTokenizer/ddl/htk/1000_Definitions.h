/*****************************************************************************/
/* 1000_Definitions.h                                                        */
/*                                                                           */
/*   This file has custom definitions pertinent to device /10FF00/1000/.     */
/*                                                                           */
/* CRITERIA FOR TEST_CASE_SELECTION                                          */
/*                                                                           */
/*	 None.                                                                   */
/*                                                                           */
/* REFERENCE                                                                 */
/*                                                                           */
/*   Document:                                                               */
/*   Version:                                                                */
/*   Date:                                                                   */
/*   Section:                                                                */
/*                                                                           */
/* REVISION_HISTORY                                                          */
/*                                                                           */
/*----------+---------------------------------------------------+-----+------*/
/* Date     ! Changes                                           !Vers.! By   */
/*----------+---------------------------------------------------+-----+------*/
/* 02-07-07 ! Initial version                                   ! 1.0 ! ms   */
/* 03-27-07 ! Added enumerations for I/O FB channels            ! 1.0 ! ms   */
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/

#ifndef _1000_DEFINITIONS_H
#define _1000_DEFINITIONS_H

/*
******************************************************************************
** Device information                                                                
******************************************************************************
*/

#define _FF_MFG_ID          0x10FF00
#define _FF_HTK_DEV_ID      0x1000

#ifdef DEVREV1
    #define _FF_HTK_DEV_REV     0x01
#else
    #define _FF_HTK_DEV_REV     0x02
#endif

#ifndef DD_REV
    #define _FF_HTK_DD_REV  0x01
#else
    #define _FF_HTK_DD_REV  0x06
#endif

/*
******************************************************************************
** AR "switches" - Pending & Resolved                                                                
******************************************************************************
*/

#define _AR2251 1   /* error referencing bits of bit-enumerated variable */
#define _AR2259 1   /* action method error on bit-enumerated conditional */
#define _AR2273 1   /* collection record member reference causing crash */
#define _AR2316 1   /* invalid reference error on variable list record member reference */
#define _AR2318 1   /* invalid reference error on file record member reference */
#define _AR2319 1   /* invalid reference error on list rec member ref */
#define _AR2333 0   /* [Closed (Clarified)] axis.VIEW_MIN/MAX reference error */
#define _AR2334 1   /* invalid reference error on chart member reference */
#define _AR2339 0   /* [Closed (Clarified)] invalid reference error on graph member reference */
#define _AR2340 1   /* invalid reference error on source member reference */
#define _AR2342 0   /* [Closed (Clarified)] syntax error on source line-color reference */
#define _AR2343 0   /* [Closed (Clarified)] syntax error on waveform line-color reference */
#define _AR2344 1   /* invalid reference error on local parameter reference */
#define _AR2557 1   /* tok crashes with local_param.rec.mem ref in method */
#define _AR2574 1   /* crash when tokenizing item with string macros for label/help */
#define _AR2582 1   /* errors and tok crash referncing rec.mem and array[element] in various places */
#define _AR3478 1   /* delayfor2() has the wrong argument list in the method interpreter's builtin table */
#define _AR3479 1   /* select_from_menu2() has the wrong argument list in the method interpreter's builtin table */
#define _AR3488 0   /* Unicode standard text dictionary does not exist yet */
#define _AR3987 0   /* add test case for multiple MIN/MAX values */
#define _AR4063 0   /* additional builtins need implemented */
#define _AR4066 0   /* add validity test case for source and waveforms */
#define _AR4437 1   /* DL-006 3.50: __bkcal_in_d using wrong element items */
#define _AR4477 0   /* implement cross-block PARAM_LIST reference */
#define _AR4625 1   /* STATUS of OUT parameters should be writable for TFB */
#define _AR4629 1   /* STATUS of OUT parameters should be writable for Custom-In */
#define _AR4904 1   /* User method must be in block METHOD_ITEMS list */
#define _AR4905 1   /* test case TC_METH_001 fails if ALERT_KEY is set to 0 */
#define _AR5111 1   /* correct HTK DDL to be compatible with DDL 3.60 and TOK 5.2.0 */
#define _AR5274 1   /* fl_blk_param_file is contradictory to FF-900 section 1.21.1 */
#define _AR4940 1   /* tests do not use correct block root menu names for handheld hosts */
#define _AR4990 1   /* add action to insert test_input_rec into test_input_list when recored.member is edited */
#define _AR5072 1   /* cond0051b_var should use signed input for conditional */
#define _AR5487 1   /* Contradicting test requirements in TC_COND_0031 */
#define _AR5572 1   /* remove test requirement and procedures for TC_File_006 */

/*
******************************************************************************
** Common help and message strings                                                               
******************************************************************************
*/

#define _VISTB_ALARM_HELP   "An alarm value used to test EDD visualizations."
#define _VISTB_RANGE_HELP   "A range value used to test EDD visualizations."
#define _VISTB_LIMIT_HELP   "A limit value used to test EDD visualizations."
#define _CONDTB_ENUM_HELP   "These enumerations represent conditional "     \
                            "evaluation values used to test the attributes "\
                            "of variables in this block."
#define _DD4_NO_SUPORT_MSG  "Test case not supported in v4 DD."
#define _TC_NO_SUPORT_MSG   "Test case not currently supported."

/*
******************************************************************************
** Enumeration Lists for ChannelTB Function Parameters                                                                
******************************************************************************
*/

#define _CHANNELTB_AI_FUNCTION  {0, "No Function"   },\
                                {1, "Ramp"          }

#define _CHANNELTB_DI_FUNCTION  {0, "No Function"   },\
                                {1, "Toggle"        },\
                                {2, "Ramp"          }

#define _CHANNELTB_MAI_FUNCTION {0, "No Function"   },\
                                {1, "Ramp"          }

#define _CHANNELTB_MDI_FUNCTION {0, "No Function"   },\
                                {1, "Toggle"        },\
                                {2, "Ramp"          }

#define _FUNCTION_PERIOD_ENUM   {0, "0.0"   },\
                                {1, "0.25"  },\
                                {2, "0.5"   },\
                                {4, "1.0"   },\
                                {8, "2.0"   }

/*
******************************************************************************
** Enumeration List for I/O FB Channels                                                                
******************************************************************************
*/

#define _IOFB_CHANNEL_ENUM      {0, "None"          },\
                                {1, "AI Channel"    },\
                                {2, "AO Channel"    },\
                                {3, "DI Channel"    },\
                                {4, "DO Channel"    },\
                                {5, "MAI Channel"   },\
                                {6, "MAO Channel"   },\
                                {7, "MDI Channel"   },\
                                {8, "MDO Channel"   }

#define _AI_CHANNEL_ENUM        {0, "None"          },\
                                {1, "AI Channel"    }

#define _AO_CHANNEL_ENUM        {0, "None"          },\
                                {2, "AO Channel"    }

#define _DI_CHANNEL_ENUM        {0, "None"          },\
                                {3, "DI Channel"    }

#define _DO_CHANNEL_ENUM        {0, "None"          },\
                                {4, "DO Channel"    }

#define _MAI_CHANNEL_ENUM       {0, "None"          },\
                                {5, "MAI Channel"   }

#define _MAO_CHANNEL_ENUM       {0, "None"          },\
                                {6, "MAO Channel"   }

#define _MDI_CHANNEL_ENUM       {0, "None"          },\
                                {7, "MDI Channel"   }

#define _MDO_CHANNEL_ENUM       {0, "None"          },\
                                {8, "MDO Channel"   }

/*
******************************************************************************
** Array size for arrays in DataTypesTB                                                                
******************************************************************************
*/

#define _ARRAY_SIZE     5

/*
******************************************************************************
** Enumeration Lists for DataTypesTB Parameters                                                                
******************************************************************************
*/

#define _DATATYPESTB_ENUM8              \
        {0x00000000,    "0"         },  \
        {0x00000001,    "1"         },  \
        {0x00000002,    "2"         },  \
        {0x00000004,    "4"         },  \
        {0x00000008,    "8"         },  \
        {0x00000010,    "16"        },  \
        {0x00000020,    "32"        },  \
        {0x00000040,    "64"        },  \
        {0x00000080,    "128"       }

#define _DATATYPESTB_ENUM16             \
        {0x00000000,    "0"         },  \
        {0x00000001,    "1"         },  \
        {0x00000002,    "2"         },  \
        {0x00000004,    "4"         },  \
        {0x00000008,    "8"         },  \
        {0x00000010,    "16"        },  \
        {0x00000020,    "32"        },  \
        {0x00000040,    "64"        },  \
        {0x00000080,    "128"       },  \
        {0x00000100,    "256"       },  \
        {0x00000200,    "512"       },  \
        {0x00000400,    "1024"      },  \
        {0x00000800,    "2048"      },  \
        {0x00001000,    "4096"      },  \
        {0x00002000,    "8192"      },  \
        {0x00004000,    "16384"     },  \
        {0x00008000,    "32768"     }

#define _DATATYPESTB_ENUM32             \
        {0x00000000,    "0"         },  \
        {0x00000001,    "1"         },  \
        {0x00000002,    "2"         },  \
        {0x00000004,    "4"         },  \
        {0x00000008,    "8"         },  \
        {0x00000010,    "16"        },  \
        {0x00000020,    "32"        },  \
        {0x00000040,    "64"        },  \
        {0x00000080,    "128"       },  \
        {0x00000100,    "256"       },  \
        {0x00000200,    "512"       },  \
        {0x00000400,    "1024"      },  \
        {0x00000800,    "2048"      },  \
        {0x00001000,    "4096"      },  \
        {0x00002000,    "8192"      },  \
        {0x00004000,    "16384"     },  \
        {0x00008000,    "32768"     },  \
        {0x00010000,    "65536"     },  \
        {0x00020000,    "131072"    },  \
        {0x00040000,    "262144"    },  \
        {0x00080000,    "524288"    },  \
        {0x00100000,    "1048576"   },  \
        {0x00200000,    "2097152"   },  \
        {0x00400000,    "4194304"   },  \
        {0x00800000,    "8388608"   },  \
        {0x01000000,    "16777216"  },  \
        {0x02000000,    "33554432"  },  \
        {0x04000000,    "67108864"  },  \
        {0x08000000,    "134217728" },  \
        {0x10000000,    "268435456" },  \
        {0x20000000,    "536870912" },  \
        {0x40000000,    "1073741824"},  \
        {0x80000000,    "2147483648"}

#define _DATATYPESTB_BITENUM8           \
        {0x00000001,    "Bit 0"     },  \
        {0x00000002,    "Bit 1"     },  \
        {0x00000004,    "Bit 2"     },  \
        {0x00000008,    "Bit 3"     },  \
        {0x00000010,    "Bit 4"     },  \
        {0x00000020,    "Bit 5"     },  \
        {0x00000040,    "Bit 6"     },  \
        {0x00000080,    "Bit 7"     }

#define _DATATYPESTB_BITENUM16          \
        {0x00000001,    "Bit 0"     },  \
        {0x00000002,    "Bit 1"     },  \
        {0x00000004,    "Bit 2"     },  \
        {0x00000008,    "Bit 3"     },  \
        {0x00000010,    "Bit 4"     },  \
        {0x00000020,    "Bit 5"     },  \
        {0x00000040,    "Bit 6"     },  \
        {0x00000080,    "Bit 7"     },  \
        {0x00000100,    "Bit 8"     },  \
        {0x00000200,    "Bit 9"     },  \
        {0x00000400,    "Bit 10"    },  \
        {0x00000800,    "Bit 11"    },  \
        {0x00001000,    "Bit 12"    },  \
        {0x00002000,    "Bit 13"    },  \
        {0x00004000,    "Bit 14"    },  \
        {0x00008000,    "Bit 15"    }

#define _DATATYPESTB_BITENUM32          \
        {0x00000001,    "Bit 0"     },  \
        {0x00000002,    "Bit 1"     },  \
        {0x00000004,    "Bit 2"     },  \
        {0x00000008,    "Bit 3"     },  \
        {0x00000010,    "Bit 4"     },  \
        {0x00000020,    "Bit 5"     },  \
        {0x00000040,    "Bit 6"     },  \
        {0x00000080,    "Bit 7"     },  \
        {0x00000100,    "Bit 8"     },  \
        {0x00000200,    "Bit 9"     },  \
        {0x00000400,    "Bit 10"    },  \
        {0x00000800,    "Bit 11"    },  \
        {0x00001000,    "Bit 12"    },  \
        {0x00002000,    "Bit 13"    },  \
        {0x00004000,    "Bit 14"    },  \
        {0x00008000,    "Bit 15"    },  \
        {0x00010000,    "Bit 16"    },  \
        {0x00020000,    "Bit 17"    },  \
        {0x00040000,    "Bit 18"    },  \
        {0x00080000,    "Bit 19"    },  \
        {0x00100000,    "Bit 20"    },  \
        {0x00200000,    "Bit 21"    },  \
        {0x00400000,    "Bit 22"    },  \
        {0x00800000,    "Bit 23"    },  \
        {0x01000000,    "Bit 24"    },  \
        {0x02000000,    "Bit 25"    },  \
        {0x04000000,    "Bit 26"    },  \
        {0x08000000,    "Bit 27"    },  \
        {0x10000000,    "Bit 28"    },  \
        {0x20000000,    "Bit 29"    },  \
        {0x40000000,    "Bit 30"    },  \
        {0x80000000,    "Bit 31"    }

/*
******************************************************************************
** Enumeration Lists for CondTB1/2 Test Parameters                                                                
******************************************************************************
*/

#define _CONDTB_TEST_INPUT_ENUM                   \
                    {0,  "NONE"                 },\
                    {1,  "DISPLAY_FORMAT_1"     },\
                    {2,  "DISPLAY_FORMAT_2"     },\
                    {3,  "EDIT_FORMAT_1"        },\
                    {4,  "EDIT_FORMAT_2"        },\
                    {5,  "MIN_VALUE_1"          },\
                    {6,  "MIN_VALUE_2"          },\
                    {7,  "MAX_VALUE_1"          },\
                    {8,  "MAX_VALUE_2"          },\
                    {9,  "ENUMERATED_1"         },\
                    {10, "ENUMERATED_2"         },\
                    {11, "BIT_ENUMERATED_1"     },\
                    {12, "BIT_ENUMERATED_2"     },\
                    {13, "CONSTANT_UNIT_1"      },\
                    {14, "CONSTANT_UNIT_2"      },\
                    {15, "HANDLING_1"           },\
                    {16, "HANDLING_2"           },\
                    {17, "VALIDITY_1"           },\
                    {18, "VALIDITY_2"           }

#define _CONDTB_TEST_INPUT_BIT_ENUM           \
        {0x00000001,    "DISPLAY_FORMAT_1"  },\
        {0x00000002,    "DISPLAY_FORMAT_2"  },\
        {0x00000004,    "EDIT_FORMAT_1"     },\
        {0x00000008,    "EDIT_FORMAT_2"     },\
        {0x00000010,    "MIN_VALUE_1"       },\
        {0x00000020,    "MIN_VALUE_2"       },\
        {0x00000040,    "MAX_VALUE_1"       },\
        {0x00000080,    "MAX_VALUE_2"       },\
        {0x00000100,    "ENUMERATED_1"      },\
        {0x00000200,    "ENUMERATED_2"      },\
        {0x00000400,    "BIT_ENUMERATED_1"  },\
        {0x00000800,    "BIT_ENUMERATED_2"  },\
        {0x00001000,    "CONSTANT_UNIT_1"   },\
        {0x00002000,    "CONSTANT_UNIT_2"   },\
        {0x00004000,    "HANDLING_1"        },\
        {0x00008000,    "HANDLING_2"        },\
        {0x00010000,    "VALIDITY_1"        },\
        {0x00020000,    "VALIDITY_2"        }
                                            
#define _CONDTB_ZERO_ENUM       {0, "Zero"}

#if _AR5111
    #define _CONDTB_ZERO_BIT_ENUM   {0x01, "Bit 0"}
#else
    #define _CONDTB_ZERO_BIT_ENUM   {0x00, "Bit 0"}
#endif

#define _TEST_ENUM1         {1, "YES"},\
			                {2, "NO"}

#define _TEST_ENUM2         {1, "YES"}, \
			                {2, "NO"},  \
                            {3, "MAYBE"}

#define _TEST_BIT_ENUM1     {0x01, "Bit 0"},\
                            {0x02, "Bit 1"},\
                            {0x04, "Bit 2"}

#define _TEST_BIT_ENUM2     {0x01, "Bit 0"},\
                            {0x02, "Bit 1"},\
                            {0x04, "Bit 2"},\
                            {0x40, "Bit 6"}     

/*
******************************************************************************
** Cascading Style Sheets, Level 2 RGB color values (HEX)                                                               
******************************************************************************
*/

#define _RGB_WHITE          0xffffff    /*  1 */
#define _RGB_GREY           0xbebebe    /*  2 */
#define _RGB_BLUE           0x0000ff    /*  3 */
#define _RGB_CYAN           0x00ffff    /*  4 */
#define _RGB_GREEN          0x00ff00    /*  5 */
#define _RGB_YELLOW         0xffff00    /*  6 */
#define _RGB_BROWN          0xa52a2a    /*  7 */
#define _RGB_ORANGE         0xffa500    /*  8 */
#define _RGB_RED            0xff0000    /*  9 */
#define _RGB_PINK           0xffc0cb    /* 10 */
#define _RGB_MAROON         0xb03060    /* 11 */
#define _RGB_VIOLET         0xee82ee    /* 12 */
#define _RGB_PURPLE         0xa020f0    /* 13 */
#define _RGB_AZURE          0xf0ffff    /* 14 */
#define _RGB_NAVY           0x000080    /* 15 */
#define _RGB_TURQUOISE      0x40e0d0    /* 16 */
#define _RGB_KHAKI          0xf0e68c    /* 17 */
#define _RGB_GOLD           0xffd700    /* 18 */
#define _RGB_BLACK          0x000000    /* default */      

/*
******************************************************************************
** Multi-language label and help strings                                                               
******************************************************************************
*/

#define _MULTI_LANG_LABEL                           \
                            "|zh|Chinese label"     \
                            "|en|English label"     \
                            "|fr|French label"      \
                            "|de|German label"      \
                            "|it|Italian label"     \
                            "|ja|Japanese label"    \
                            "|pt|Portuguese label"  \
                            "|ru|Russian label"     \
                            "|es|Spanish label"

#define _MULTI_LANG_HELP                            \
                            "|zh|Chinese help"      \
                            "|en|English help"      \
                            "|fr|French help"       \
                            "|de|German help"       \
                            "|it|Italian help"      \
                            "|ja|Japanese help"     \
                            "|pt|Portuguese help"   \
                            "|ru|Russian help"      \
                            "|es|Spanish help"      
#define _UNICODE_LABEL                           \
                            "|zh|Chinese label 这是测试"     \
                            "|en|English label"     \
                            "|fr|French label"      \
                            "|de|German label"      \
                            "|it|Italian label Ciò è una prova"     \
                            "|ja|Japanese label これはテストである"    \
                            "|pt|Portuguese label"  \
                            "|ru|Russian label Это испытание"     \
                            "|es|Spanish label"

#define _UNICODE_HELP                            \
                            "|zh|Chinese help 这是测试"      \
                            "|en|English help"      \
                            "|fr|French help"       \
                            "|de|German help"       \
                            "|it|Italian help Ciò è una prova"      \
                            "|ja|Japanese help これはテストである"     \
                            "|pt|Portuguese help"   \
                            "|ru|Russian help Это испытание"      \
                            "|es|Spanish help"      

/*
******************************************************************************
** Bit-masks for bit-enumerated variable referencing                                                                
******************************************************************************
*/

#define _DISPLAY_FORMAT_1_BIT   0x00000001
#define _DISPLAY_FORMAT_2_BIT	0x00000002
#define _EDIT_FORMAT_1_BIT		0x00000004
#define _EDIT_FORMAT_2_BIT		0x00000008
#define _MIN_VALUE_1_BIT		0x00000010
#define _MIN_VALUE_2_BIT		0x00000020
#define _MAX_VALUE_1_BIT		0x00000040
#define _MAX_VALUE_2_BIT		0x00000080
#define _ENUMERATED_1_BIT		0x00000100
#define _ENUMERATED_2_BIT		0x00000200
#define _BIT_ENUMERATED_1_BIT	0x00000400
#define _BIT_ENUMERATED_2_BIT	0x00000800
#define _CONSTANT_UNIT_1_BIT	0x00001000
#define _CONSTANT_UNIT_2_BIT	0x00002000
#define _HANDLING_1_BIT			0x00004000
#define _HANDLING_2_BIT			0x00008000
#define _VALIDITY_1_BIT			0x00010000
#define _VALIDITY_2_BIT			0x00020000

/*
******************************************************************************
** Definitions for use with the conditional test cases                                                                
******************************************************************************
*/

#define _DISPLAY_FORMAT_1	1
#define _DISPLAY_FORMAT_2	2
#define _EDIT_FORMAT_1		3
#define _EDIT_FORMAT_2		4
#define _MIN_VALUE_1		5
#define _MIN_VALUE_2		6
#define _MAX_VALUE_1		7
#define _MAX_VALUE_2		8
#define _ENUMERATED_1		9
#define _ENUMERATED_2		10
#define _BIT_ENUMERATED_1	11
#define _BIT_ENUMERATED_2	12
#define _CONSTANT_UNIT_1	13
#define _CONSTANT_UNIT_2	14
#define _HANDLING_1			15
#define _HANDLING_2			16
#define _VALIDITY_1			17
#define _VALIDITY_2			18
#define _NUM_OF_CONDITIONAL_OPTIONS 18
#define _NUM_OF_PARAMS_CONDTB1 109 /* 108 parameters + 1 for the block record */

#define _EXIT_METHOD		255

/* String should not exceed the size of 36 characters */
#define _STR_DISPLAY_FORMAT_1	"1  Display Format = 0.XX \n"
#define _STR_DISPLAY_FORMAT_2	"2  Display Format = 0.XXXX \n"
#define _STR_EDIT_FORMAT_1		"3  Edit Format = 0.XX \n"
#define _STR_EDIT_FORMAT_2		"4  Edit Format = 0.XXXX \n"
#define _STR_MIN_VALUE_1		"5  Min Value = 2 \n"
#define _STR_MIN_VALUE_2		"6  Min Value = 1 \n"
#define _STR_MAX_VALUE_1		"7  Max Value = 5 \n"
#define _STR_MAX_VALUE_2		"8  Max Value = 10 \n"
#define _STR_ENUMERATED_1		"9  Enum = YES and NO \n"
#define _STR_ENUMERATED_2		"10 Enum = YES, NO, & MAYBE\n"
#define _STR_BIT_ENUMERATED_1	"11 Bit Enum = bits 0,1,&2\n"
#define _STR_BIT_ENUMERATED_2	"12 Bit Enum = bits 0,1,2,&6\n"
#define _STR_CONSTANT_UNIT_1	"13 Constant Unit = msec\n"
#define _STR_CONSTANT_UNIT_2	"14 Constant Unit = sec\n"
#define _STR_HANDLING_1			"15 Handling = READ\n"
#define _STR_HANDLING_2			"16 Handling = READ & WRITE\n"
#define _STR_VALIDITY_1			"17 Validity = Does not Exist\n"
#define _STR_VALIDITY_2			"18 Validity = Exists\n"
#define _STR_EXIT_METHOD		"255 Exit Test Case\n"

#define _MSG_DISPLAY_FORMAT_1	"Fail if float variable is not displayed as 0.XX"
#define _MSG_DISPLAY_FORMAT_2	"Fail if float variable is not displayed as 0.XXXX"
#define _MSG_EDIT_FORMAT_1		"Fail if float variable is not 0.XX when edited"
#define _MSG_EDIT_FORMAT_2		"Fail if float variable is not 0.XXXX when edited"
#define _MSG_MIN_VALUE_1		"Fail if float variable is writable to a value less than 2.00"
#define _MSG_MIN_VALUE_2		"Fail if float variable is writable to a value less than 1.00"
#define _MSG_MAX_VALUE_1		"Fail if float variable is writable to a value greater than 5.00"
#define _MSG_MAX_VALUE_2		"Fail if float variable is writable to a value greater than 10.00"
#define _MSG_ENUMERATED_1		"Fail if enum variable does not display YES & NO"
#define _MSG_ENUMERATED_2		"Fail if enum variable does not display YES, NO, & MAYBE"
#define _MSG_BIT_ENUMERATED_1	"Fail if bit enum variable does not display bits 0, 1, & 2"
#define _MSG_BIT_ENUMERATED_2	"Fail if bit enum variable does not display bits 0, 1, 2, & 6"
#define _MSG_CONSTANT_UNIT_1	"Fail if float variable does not have msec as its unit"
#define _MSG_CONSTANT_UNIT_2	"Fail if float variable does not have sec as its unit"
#define _MSG_HANDLING_1			"Fail if float variable is editable"
#define _MSG_HANDLING_2			"Fail if float variable is read only"
#define _MSG_VALIDITY_1			"Fail if float variable exists"
#define _MSG_VALIDITY_2			"Fail if float variable does not exist"


#define _STR_SUBTEST_SELECTION  (						\
								_STR_DISPLAY_FORMAT_1	\
                                _STR_DISPLAY_FORMAT_2	\
								_STR_EDIT_FORMAT_1		\
                                _STR_EDIT_FORMAT_2		\
								_STR_MIN_VALUE_1		\
                                _STR_MIN_VALUE_2		\
								_STR_MAX_VALUE_1		\
                                _STR_MAX_VALUE_2		\
								_STR_ENUMERATED_1		\
                                _STR_ENUMERATED_2		\
								_STR_BIT_ENUMERATED_1	\
                                _STR_BIT_ENUMERATED_2	\
								_STR_CONSTANT_UNIT_1	\
                                _STR_CONSTANT_UNIT_2	\
								_STR_HANDLING_1			\
                                _STR_HANDLING_2			\
								_STR_VALIDITY_1			\
                                _STR_VALIDITY_2			\
                                _STR_EXIT_METHOD        \
							    )

#define _MSG_OPEN_TC_MENU   "Open the menu with the corresponding test-case name"
/*
******************************************************************************
** menu enable/disable flags
******************************************************************************
*/

#define _DIAG_ROOT_MENU         0
#define _PROC_VAR_ROOT_MENU     0

/*
******************************************************************************
** menu item lists
******************************************************************************
*/

#define _CONDTB1_TEST_PAGES                                                         \
        display_format_test, edit_format_test , min_value_test, max_value_test,     \
        enum_value_test, bit_enum_value_test, constant_unit_test, handling_test,    \
        validity_test

#define _CONDTB2_TEST_PAGES                                                         \
        cond0050_page, cond0051_page, cond0052_page, cond0053_page, cond0054_page,  \
        cond0055_page, cond0056_page, cond0057_page, cond0058_page, cond0059_page,  \
        cond0070_page, cond0071_page, cond0072_page, cond0073_page, cond0080_page,  \
        cond0081_page

#define _VISTB_TC_GR_PAGES                                                              \
        tc_gr_001_page, tc_gr_002_page, tc_gr_003_page, tc_gr_004_page, tc_gr_005_page, \
        tc_gr_006_page, tc_gr_007_page, tc_gr_008_page, tc_gr_009_page, tc_gr_010_page, \
        tc_gr_011_page, tc_gr_012_page, tc_gr_013_page, tc_gr_014_page, tc_gr_015_page, \
        tc_gr_016_page

#define _VISTB_TC_CH_PAGES                                                              \
        tc_ch_001_page, tc_ch_002_page, tc_ch_003_page, tc_ch_004_page, tc_ch_005_page, \
        tc_ch_006_page, tc_ch_007_page, tc_ch_008_page, tc_ch_009_page, tc_ch_010_page, \
        tc_ch_011_page, tc_ch_012_page, tc_ch_013_page, tc_ch_014_page, tc_ch_015_page, \
        tc_ch_016_page, tc_ch_017_page, tc_ch_018_page, tc_ch_019_page, tc_ch_020_page, \
        tc_ch_021_page, tc_ch_022_page, tc_ch_023_page, tc_ch_024_page

#define _VISTB_TC_IMG_WINDOWS                                                       \
        tc_img_001_window, tc_img_002_window, tc_img_003_window, tc_img_004_window, \
        tc_img_005_window, tc_img_006_window, tc_img_007_window, tc_img_008_window

#define _VISTB_TC_MN_WINDOWS                                                    \
        tc_mn_001_window, tc_mn_002_window, tc_mn_003_window, tc_mn_004_window, \
        tc_mn_005_window, tc_mn_006_window, tc_mn_007_window, tc_mn_008_menu,   \
        tc_mn_009_window, tc_mn_010_window, tc_mn_011_window, tc_mn_012_window, \
        tc_mn_013_menu

#define _VISTB_TC_GRD_PAGES                                                 \
        tc_grd_001_page, tc_grd_002_page, tc_grd_003_page, tc_grd_004_page, \
        tc_grd_005_page, tc_grd_006_page, tc_grd_007_page, tc_grd_008_page, \
        tc_grd_009_page, tc_grd_010_page

#define _TC_MN_5_BY_7_ITEMS                                                         \
    "1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5",ROWBREAK,   \
	"1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5",ROWBREAK,   \
	"1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5",ROWBREAK,   \
	"1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5",ROWBREAK,   \
	"1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5",ROWBREAK,   \
	"1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5",ROWBREAK,   \
	"1",COLUMNBREAK,"2",COLUMNBREAK,"3",COLUMNBREAK,"4",COLUMNBREAK,"5"

/*
******************************************************************************
** Field Diagnostics bitstring extension redefinitions
******************************************************************************
*/

#define _FD_BITS_ADD            \
    ADD {0x00000002,    "Bit 1"}  \
    ADD {0x00000004,    "Bit 2"}  \
    ADD {0x00000008,    "Bit 3"}  \
    ADD {0x00000010,    "Bit 4"}  \
    ADD {0x00000020,    "Bit 5"}  \
    ADD {0x00000040,    "Bit 6"}  \
    ADD {0x00000080,    "Bit 7"}  \
    ADD {0x00000100,    "Bit 8"}  \
    ADD {0x00000200,    "Bit 9"}  \
    ADD {0x00000400,    "Bit 10"}  \
    ADD {0x00000800,    "Bit 11"}  \
    ADD {0x00001000,    "Bit 12"}  \
    ADD {0x00002000,    "Bit 13"}  \
    ADD {0x00004000,    "Bit 14"}  \
    ADD {0x00008000,    "Bit 15"}

#define _FD_BITS_REDEFINE           \
    REDEFINE {0x00000002,    "Bit 1"}  \
    REDEFINE {0x00000004,    "Bit 2"}  \
    REDEFINE {0x00000008,    "Bit 3"}  \
    REDEFINE {0x00000010,    "Bit 4"}  \
    REDEFINE {0x00000020,    "Bit 5"}  \
    REDEFINE {0x00000040,    "Bit 6"}  \
    REDEFINE {0x00000080,    "Bit 7"}  \
    REDEFINE {0x00000100,    "Bit 8"}  \
    REDEFINE {0x00000200,    "Bit 9"}  \
    REDEFINE {0x00000400,    "Bit 10"}  \
    REDEFINE {0x00000800,    "Bit 11"}  \
    REDEFINE {0x00001000,    "Bit 12"}  \
    REDEFINE {0x00002000,    "Bit 13"}  \
    REDEFINE {0x00004000,    "Bit 14"}  \
    REDEFINE {0x00008000,    "Bit 15"}

/*
******************************************************************************
** it is intended to define the macro V4 (Tokenizer flag -DV4) when tokenizing
** with the -4 flag (v4 binary) to exclude the v5 constructs.  you may also
** exclude the v5 constructs by toggling the _DD5_PROFILE macro after the
** #else directive below.                                                                
******************************************************************************
*/

#ifdef V4
    #define _DD5_PROFILE        0
#else
    #define _DD5_PROFILE        1
#endif


#endif
