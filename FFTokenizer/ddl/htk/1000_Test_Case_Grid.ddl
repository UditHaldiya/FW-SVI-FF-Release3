/*****************************************************************************/
/* 1000_Test_Case_Grid.ddl                                                   */
/*                                                                           */
/*   This file contains DDL for the grid test cases.                         */
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
/*          !                                                   !     !      */
/*****************************************************************************/
/*                                                                           */
/* Copyright:  Fieldbus Foundation(TM)  1994-2007                            */
/*                                                                           */
/*****************************************************************************/

#if _DD5_PROFILE

/*
******************************************************************************
** Grid test cases                                                                
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_001                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid with three float arrays. The height,   */
/*   width, orientation and handling are undefined.                          */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_001_grid
{
    LABEL   "TC_GRD_001 Grid";
    HELP    "Verify that host displays a grid with three float "
            "arrays. The height, width, orientation and handling "
            "are undefined.";
    VECTORS
    {
        {"X Array 1",   test_x_array_1},
        {"Y Array 1",   test_y_array_1},
        {"Y Array 2",   test_y_array_2}
    }
}

MENU    tc_grd_001_page
{
    LABEL   "TC_GRD_001";
    STYLE   PAGE;
    ITEMS   {   tc_grd_001_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_002                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid with one float arrays. The height,     */
/*   width, orientation and handling are all defined.                        */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_002_grid
{
    LABEL   "TC_GRD_002 Grid";
    HELP    "Verify that host displays a grid with one float arrays. "
            "The height, width, orientation and handling are all defined.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    VALIDITY        TRUE;
	HEIGHT          MEDIUM;
	WIDTH           MEDIUM;
	HANDLING        READ & WRITE;
	ORIENTATION     VERTICAL;
}

tc_grd_002_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_002";
    REDEFINE ITEMS  {   tc_grd_002_grid }
}
  
/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_003                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host does not display a grid with the validity set to false.*/
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_003_grid
{
    LABEL   "TC_GRD_003 Grid";
    HELP    "Verify that host does not display a grid with the "
            "validity set to false.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    VALIDITY        FALSE;
	HEIGHT          MEDIUM;
	WIDTH           MEDIUM;
	HANDLING        READ & WRITE;
	ORIENTATION     VERTICAL;
}

tc_grd_003_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_003";
    REDEFINE ITEMS  {   tc_grd_003_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_004                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid that's xx_small.                       */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_004_grid
{
    LABEL   "TC_GRD_004 Grid";
    HELP    "Verify that host displays a grid that's xx_small.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    HEIGHT  XX_SMALL;
	WIDTH   XX_SMALL;
}

tc_grd_004_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_004";
    REDEFINE ITEMS  {   tc_grd_004_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_005                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid that's x_small.                        */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_005_grid
{
    LABEL   "TC_GRD_005 Grid";
    HELP    "Verify that host displays a grid that's x_small.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    HEIGHT  X_SMALL;
	WIDTH   X_SMALL;
}

tc_grd_005_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_005";
    REDEFINE ITEMS  {   tc_grd_005_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_006                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid that's small.                          */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_006_grid
{
    LABEL   "TC_GRD_006 Grid";
    HELP    "Verify that host displays a grid that's small.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    HEIGHT  SMALL;
	WIDTH   SMALL;
}

tc_grd_006_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_006";
    REDEFINE ITEMS  {   tc_grd_006_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_007                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid that's large.                          */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_007_grid
{
    LABEL   "TC_GRD_007 Grid";
    HELP    "Verify that host displays a grid that's large.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    HEIGHT  LARGE;
	WIDTH   LARGE;
}

tc_grd_007_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_007";
    REDEFINE ITEMS  {   tc_grd_007_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_008                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid that's x_large.                        */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_008_grid
{
    LABEL   "TC_GRD_008 Grid";
    HELP    "Verify that host displays a grid that's x_large.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    HEIGHT  X_LARGE;
	WIDTH   X_LARGE;
}

tc_grd_008_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_008";
    REDEFINE ITEMS  {   tc_grd_008_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_009                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that host displays a grid that's xx_large.                       */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_009_grid
{
    LABEL   "TC_GRD_009 Grid";
    HELP    "Verify that host displays a grid that's xx_large.";
    VECTORS
    {
        {"Y Array 1",   test_y_array_1}
    }
    HEIGHT  XX_LARGE;
	WIDTH   XX_LARGE;
}

tc_grd_009_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_009";
    REDEFINE ITEMS  {   tc_grd_009_grid }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_GRD_010                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Grid                                                                    */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   View a grid with a horizontal orientation with 10 variables. The        */
/*   handling attribute shall be READ.                                       */
/*                                                                           */
/*****************************************************************************/
GRID    tc_grd_010_grid
{
    LABEL   "TC_GRD_010 Grid";
    HELP    "View a grid with a horizontal orientation with 10 "
            "variables. The handling attribute shall be READ.";
    VECTORS
    {
        { "Item 1",     test_record.VALUE       },
		{ "Item 2",     test_string             },
		{ "Item 3",     "Constant String Text"  },
		{ "Item 4",     test_y_array_1          },
		{ "Item 5",     test_val_int_32         },
		{ "Item 6",     test_val_int_16         },
		{ "Item 7",     test_hi_hi_limit        },
		{ "Item 8",     test_hi_limit           },
		{ "Item 9",     test_lo_limit           },
		{ "Item 10",    test_lo_lo_limit        }
    }
    ORIENTATION HORIZONTAL;
    HANDLING    READ & WRITE;
}

tc_grd_010_page LIKE MENU tc_grd_001_page
{
    REDEFINE LABEL  "TC_GRD_010";
    REDEFINE ITEMS  {   tc_grd_010_grid }
}
   
/***********************************************************************/

#endif
