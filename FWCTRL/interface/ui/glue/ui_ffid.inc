#MP If 0 ;Tombstone header
/*
Copyright 2014 by Dresser, Inc., as an unpublished work.  All rights reserved.

This document and all information herein are the property of Dresser, Inc.
It and its contents are  confidential and have been provided as a part of
a confidential relationship.  As such, no part of it may be made public,
decompiled, reverse engineered or copied and it is subject to return upon
demand.
*/
/**
    \file ui_ffid.inc

    UI Graph definitions of nodes for viewing the FF build version

    Owner: AK
    CPU: Any

*/
#MP Endif ;Tombstone header
#MP ;a companion macro to view version in "view data" menu
#MP Macro view_VersionFF   ;(return node on "*" as name)
    #MP Expand StartNode(nodetype_alt, "view_VersionFF")
    {
        {
            #MP Expand NodetType()
            0, //refresh
            //#MP TEXTLABEL(%sPROJ_PREFIX%n_BANNER)
                        #MP TEXTLABEL(FIRM_REV)
            .en = UINODE_ENABLED,
            #MP over_the_var = UIGraphNode+2
            .advance = NODE_LINK(#mp%sUIGraphNode_%dover_the_var),
            .select = NODE_LINK(#mp%n#1#), //on *
            .xfuncx = XLATE_INDEX(xlate_StdMenu),
            .uid = UNITSID_DUMMY,
        },
        NULL,
        NODE_LINK(banner_versionFF)
    },
    #MP Expand EndNode()
    #MP Expand StartNode(nodetype_strvar, "banner_versionFF")
    {
        #MP Expand NodetType()
        .checksum_offset = 0, //no checksum
        .en = UINODE_DISABLED,
        .parent = NODE_LINK(#mp%sUIGraphNodeNext), //fall through
        .strvarf = ui_GetFFidString,
    },
    #MP Expand EndNode()
#MP Endm
#MP;/* This line marks the end of the source */

