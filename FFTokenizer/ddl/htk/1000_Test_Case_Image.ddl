/*****************************************************************************/
/* 1000_Test_Case_Image.ddl                                                  */
/*                                                                           */
/*   This file contains DDL for the image test cases.                        */
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
** Image test cases                                                                
******************************************************************************
*/

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_001                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a jpg can be displayed.                                     */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_001_image
{
    LABEL   "TC_IMG_001 Image";
    HELP    "Verify that a jpg can be displayed.";
    PATH	"ff_jpg.jpg";
}

MENU    tc_img_001_window
{
    LABEL   "TC_IMG_001 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_001_image    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_002                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a gif can be displayed.                                     */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_002_image
{
    LABEL   "TC_IMG_002 Image";
    HELP    "Verify that a gif can be displayed.";
    PATH	"ff_gif.gif";
}

MENU    tc_img_002_window
{
    LABEL   "TC_IMG_002 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_002_image    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_003                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a png can be displayed.                                     */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_003_image
{
    LABEL   "TC_IMG_003 Image";
    HELP    "Verify that a png can be displayed.";
    PATH	"ff_png.png";
}

MENU    tc_img_003_window
{
    LABEL   "TC_IMG_003 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_003_image    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_004                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   View a jpg image in a window with the Validity on. The jpg image shall  */
/*   link to another window.                                                 */    
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_004_image
{
    LABEL       "TC_IMG_004 Image";
    HELP        "View a jpg image in a window with the Validity on. "
                "The jpg image shall link to another window.";
    PATH	    "ff_jpg.jpg";
    VALIDITY    TRUE;
    LINK        tc_img_004_linked_window;
}

MENU    tc_img_004_window
{
    LABEL   "TC_IMG_004 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_004_image    }
}

MENU    tc_img_004_linked_window
{
    LABEL   "TC_IMG_004 Linked Window";
    STYLE   WINDOW;
    ITEMS   {   "Image Link Successful!"    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_005                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   View a jpg image in a window. The jpg image shall link to a method.     */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_005_image
{
    LABEL       "TC_IMG_005 Image";
    HELP        "View a jpg image in a window. The jpg image shall link to a method.";
    PATH	    "ff_jpg.jpg";
    LINK        tc_img_005_link_method;
}

MENU    tc_img_005_window
{
    LABEL   "TC_IMG_005 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_005_image    }
}

METHOD  tc_img_005_link_method
{
	LABEL   "TC_IMG_005 Link Method";
	CLASS   INPUT;
	DEFINITION
	{
        long status;
        unsigned long ids[1], indices[1];

        status=display_message("Image Link Successful!",ids,indices,0);
    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_006                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a jpg image is not displayed when the VALIDITY is set to    */
/*   FALSE.                                                                  */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_006_image
{
    LABEL       "TC_IMG_006 Image";
    HELP        "Verify that a jpg image is not displayed when the "
                "VALIDITY is set to FALSE.";
    PATH	    "ff_jpg.jpg";
    VALIDITY    FALSE;
}

MENU    tc_img_006_window
{
    LABEL   "TC_IMG_006 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_006_image    }
}

/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_007                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that a large jpg image is handled properly.                      */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_007_image
{
    LABEL   "TC_IMG_007 Image";
    HELP    "Verify that a large jpg image is handled properly.";
    PATH	"ff_750by546.jpg";
}

MENU    tc_img_007_window
{
    LABEL   "TC_IMG_007 Window";
    STYLE   WINDOW;
    ITEMS   {   tc_img_007_image    }
}
/*****************************************************************************/
/* TEST_CASE_IDENTIFIER                                                      */
/*                                                                           */
/*   TC_IMG_008                                                              */
/*                                                                           */
/* SUBCLASS                                                                  */
/*                                                                           */
/*   Image                                                                   */
/*                                                                           */
/* TEST_DESCRIPTION                                                          */
/*                                                                           */
/*   Verify that an inline image can be displayed.                           */
/*                                                                           */
/*****************************************************************************/
IMAGE   tc_img_008_image
{
    LABEL   "TC_IMG_008 Label Text";
    HELP    "TC_IMG_008 Help Text";
    PATH	"ff_jpg.jpg";
}

MENU    tc_img_008_window
{
    LABEL   "TC_IMG_008 Window";
    STYLE   WINDOW;
    ITEMS
    {
        tc_img_008_page
    }
}

MENU    tc_img_008_page
{
    LABEL   "Page 1";
    STYLE   PAGE;
    ITEMS
    {
        tc_img_008_image,
        lower_range_value,
        upper_range_value,
        tc_img_008_image(INLINE)
    }
}

/***********************************************************************/

#endif

