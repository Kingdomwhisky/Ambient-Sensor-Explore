/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2014UserHDMIEdid.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD))

//****************************************************************************
// EDID LOCATION TABLES
//****************************************************************************
// Users Decide the location of Dx HdmiEdid to Edid Index
#if((_D0_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D0_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD0_EdidLocatedTable[_D0_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1

#if(_D0_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D0_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D0_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D0_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD0_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if((_D1_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D1_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD1_EdidLocatedTable[_D1_MAX_HDMI_EDID_COUNT] =
{
#if(_D1_FIRST_1_INDEX_EMBEDDED_EDID == _ON)
    _HDMI_EDID_EMBEDDED,   // EDID Index 0
#else
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
#endif
    _HDMI_EDID_EMBEDDED,   // EDID Index 1

#if(_D1_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D1_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D1_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D1_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD1_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if((_D2_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D2_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD2_EdidLocatedTable[_D2_MAX_HDMI_EDID_COUNT] =
{
#if(_D2_FIRST_1_INDEX_EMBEDDED_EDID == _ON)
    _HDMI_EDID_EMBEDDED,   // EDID Index 0
#else
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
#endif
    _HDMI_EDID_EMBEDDED,   // EDID Index 1

#if(_D2_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D2_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D2_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D2_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD2_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if((_D3_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D3_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD3_EdidLocatedTable[_D3_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1

#if(_D3_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D3_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D3_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD3_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if((_D4_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D4_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD4_EdidLocatedTable[_D4_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1

#if(_D4_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D4_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D4_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD4_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if((_D5_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D5_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD5_EdidLocatedTable[_D5_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1

#if(_D5_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D5_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D5_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D5_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD5_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EMBEDDED,   // EDID Index 1
    _HDMI_EDID_EMBEDDED,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tNullEdidTable[1] = {0};

code BYTE *tEdidMultiLocatedTable[] =
{
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD0_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD1_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD2_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD3_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD4_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD5_EdidLocatedTable,
#else
    tNullEdidTable,
#endif
};
#endif

//****************************************************************************
// EDID CONTENT TABLES
//****************************************************************************
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_HDMI_SUPPORT == _ON))
BYTE code tHDMI_EDID_FHD_TABLE[] =
{
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080@60.h"
};

BYTE code tHDMI_EDID_QHD_TABLE[] =
{
#include "./EDID/EdidHdmi/EDID_HDMI_2560x1440@60.h"
};

BYTE code tHDMI_EDID_UHD_TABLE[] =
{
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60_HFVSDB_WITH420.h"
};

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tHDMI14_EDID_TABLE[] =
{
//#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440@60.h"
#if((_PANEL_TYPE == _INNOLUX_LVDS_R213RCE_LU1_1536x2048)||(_PANEL_TYPE == _AUO_LVDS_G213QAN02_X_1536x2048)||(_PANEL_TYPE == _BOE_LVDS_EV213QXM_N10_1536x2048)||(_PANEL_TYPE == _INNOLUX_LVDS_R213RCE_LU2_1536x2048))
#include "./EDID/EdidHdmi/EDID_HDMI_1536x2048@60.h"
#elif(_PANEL_TYPE == _INNOLUX_LVDS_R213TCE_LU2_2560x2048)//c510
#include "./EDID/EdidHdmi/EDID_HDMI_C_2560x2048@60.h"
#elif(_PANEL_TYPE == _INNOLUX_LVDS_R213TCE_LU1_2560x2048)//G510
#include "./EDID/EdidHdmi/EDID_HDMI_G_2560x2048@60.h"
#elif(_PANEL_TYPE == _INNOLUX_LVDS_G121ICE_L02_1280x800)
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080@60.h"
#elif(_PANEL_TYPE == _BOE_EV156FHM_N80_1920x1080)
#include "./EDID/EdidHdmi/EDID_HDMI_3840x2160@30.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160@60_WITH420.h"
#endif
};

BYTE code tHDMIDVI14_EDID_TABLE[] =
{
#if((_PANEL_TYPE == _INNOLUX_LVDS_R213RCE_LU1_1536x2048)||(_PANEL_TYPE == _AUO_LVDS_G213QAN02_X_1536x2048)||(_PANEL_TYPE == _BOE_LVDS_EV213QXM_N10_1536x2048)||(_PANEL_TYPE == _INNOLUX_LVDS_R213RCE_LU2_1536x2048))
//DebugMessageSystem("edid", 1);
#include "./EDID/EdidDvi/EDID_DVI_1536x2048_1.3@60.h"
//#include "./EDID/EdidDvi/EDID_DVI_1440x1080_1.3@60.h"
#elif(_PANEL_TYPE == _INNOLUX_LVDS_R213TCE_LU2_2560x2048)//c510
#include "./EDID/EdidDvi/EDID_DVI_C_2560x2048_1.3@60.h"
#elif(_PANEL_TYPE == _INNOLUX_LVDS_R213TCE_LU1_2560x2048)//G510
#include "./EDID/EdidDvi/EDID_DVI_G_2560x2048_1.3@60.h"
#elif(_PANEL_TYPE == _INNOLUX_LVDS_G121ICE_L02_1280x800)
#include "./EDID/EdidDvi/EDID_DVI_C_2560x2048_1.3@60.h"
#elif(_PANEL_TYPE == _BOE_EV156FHM_N80_1920x1080)
#include "./EDID/EdidDvi/EDID_DVI_C_2560x2048_1.3@60.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160@60_WITH420.h"
#endif
};

BYTE code tHDMI20_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160@60_WITH420.h"
};

BYTE code tHDMI21_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160@60_WITH420.h"
};

#if(_HDMI_HDR10_SUPPORT == _ON)
BYTE code tHDMI14_HDR_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440@60_HDR.h"
};

BYTE code tHDMI20_HDR_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160@60_WITH420_HDR.h"
};

BYTE code tHDMI21_HDR_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160@60_WITH420_HDR.h"
};
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE code tHDMI14_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M_FS2.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)_FS2.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70).h"
#endif

#endif
};

BYTE code tHDMI20_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_FS2_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_FS2_WITH420.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_WITH420.h"
#endif

#endif
};

BYTE code tHDMI21_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_FS2_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_FS2_WITH420.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_WITH420.h"
#endif

#endif
};
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
BYTE code tHDMI14_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M_FS2_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)_FS2_HDR.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)_HDR.h"
#endif

#endif
};

BYTE code tHDMI20_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_FS2_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_FS2_WITH420_HDR.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_WITH420_HDR.h"
#endif

#endif
};

BYTE code tHDMI21_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_FS2_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_FS2_WITH420_HDR.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_WITH420_HDR.h"
#endif

#endif
};
#endif

// Users Decide the Edid Content of the Edid Index
code BYTE *tHDMI_EDID_TABLE[] =
{
    tHDMI14_EDID_TABLE,               // _EDID_INDEX_0
    tHDMI20_EDID_TABLE,               // _EDID_INDEX_1
    tHDMI21_EDID_TABLE,               // _EDID_INDEX_2

#if(_HDMI_HDR10_SUPPORT == _ON)
    tHDMI14_HDR_EDID_TABLE,           // _EDID_INDEX_3
    tHDMI20_HDR_EDID_TABLE,           // _EDID_INDEX_4
    tHDMI21_HDR_EDID_TABLE,           // _EDID_INDEX_5
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    tHDMI14_FS_EDID_TABLE,            // _EDID_INDEX_6
    tHDMI20_FS_EDID_TABLE,            // _EDID_INDEX_7
    tHDMI21_FS_EDID_TABLE,            // _EDID_INDEX_8
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    tHDMI14_FS_HDR_EDID_TABLE,        // _EDID_INDEX_9
    tHDMI20_FS_HDR_EDID_TABLE,        // _EDID_INDEX_10
    tHDMI21_FS_HDR_EDID_TABLE,        // _EDID_INDEX_11
#endif
};
// Users Decide the Edid Content of the Edid Index
code BYTE *tHDMI_EDID_TABLE2[] =
{
    tHDMIDVI14_EDID_TABLE,               // _EDID_INDEX_0
    tHDMI20_EDID_TABLE,               // _EDID_INDEX_1
    tHDMI21_EDID_TABLE,               // _EDID_INDEX_2

#if(_HDMI_HDR10_SUPPORT == _ON)
    tHDMI14_HDR_EDID_TABLE,           // _EDID_INDEX_3
    tHDMI20_HDR_EDID_TABLE,           // _EDID_INDEX_4
    tHDMI21_HDR_EDID_TABLE,           // _EDID_INDEX_5
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    tHDMI14_FS_EDID_TABLE,            // _EDID_INDEX_6
    tHDMI20_FS_EDID_TABLE,            // _EDID_INDEX_7
    tHDMI21_FS_EDID_TABLE,            // _EDID_INDEX_8
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    tHDMI14_FS_HDR_EDID_TABLE,        // _EDID_INDEX_9
    tHDMI20_FS_HDR_EDID_TABLE,        // _EDID_INDEX_10
    tHDMI21_FS_HDR_EDID_TABLE,        // _EDID_INDEX_11
#endif
};
#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_HDMI_SUPPORT == _ON))

#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD))
