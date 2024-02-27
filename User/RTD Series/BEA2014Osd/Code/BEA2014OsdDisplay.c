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
// ID Code      : BEA2014OsdDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDDISPLAY__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VGA_A0 = 0x01,
} EnumOsdSourceTypeVga;

typedef enum
{
    _DVI = 0x02,
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    _DVI_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
    _DVI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
    _DVI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
    _DVI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
    _DVI_D4,
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
    _DVI_D5,
#endif

    _HDMI = 0x10,
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    _HDMI_D0,
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
    _HDMI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    _HDMI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    _HDMI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    _HDMI_D4,
#endif
#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    _HDMI_D5,
#endif
}EnumOsdSourceTypeTMDS;

typedef enum
{
    _DP = 0x0E,
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    _DP_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    _DP_D1,
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    _DP_D2,
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    _DP_D6,
#endif
} EnumOsdSourceTypeDP;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
bit g_bflagMinuteON = _FALSE;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE OsdDisplayGetSourcePortString(void);
#if(_OVERSCAN_SUPPORT == _ON)
WORD OsdDisplayGetOverScanRatio(BYTE bOverScanStatus);
#endif
#if(_VGA_SUPPORT == _ON)
BYTE OsdDisplayGetVGAModeString(bit bUserMode);
#endif
BYTE OsdDispJudgeSourceType(void);
void OsdDispDisableOsd(void);
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
void OsdDispMainKey(void);
void OsdDispMainMenu(void);
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue, BYTE ucRowIndex, BYTE ucColor);
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void OsdDisplayMstOverRange(void);
void OsdDisplaySixColorGetOneColor(BYTE ucColor);
void OsdDisplaySixColorSetOneColor(BYTE ucColor);
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
void OsdDispOsdRotateSwitch(void);
#endif
void OsdDispHotKeyOptionMenu(BYTE ucOption);
void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
void OsdDispHotKeyOptionMenuSwitch(BYTE ucPort);

void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);
void DrawMainPage(void);
void DrawServiceLevelPage(void);
void DrawSelectRegion(BYTE State);

#if(_VGA_SUPPORT == _ON)
void OsdDispAutoConfigProc(void);
void OsdDisplayAutoBalanceProc(void);
#endif
void OsdDispOsdReset(void);
#if(_DP_SUPPORT == _ON)
void OsdDispResetDpCapabilitySwitch(void);
#endif
void OsdDispShowLogo(void);
BYTE StateColor(BYTE State);                                                  
void OsdSelectedUpdate(BYTE bType,BYTE ucBeginItem,BYTE ucEndItem);
void SelectRegionAdjust(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
BYTE OsdDisplayGetSourcePortString(void)
{
    switch(SysSourceGetInputPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return _STRING_A0_PORT;
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return _STRING_D0_PORT;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return _STRING_D1_PORT;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return _STRING_D2_PORT;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return _STRING_D3_PORT;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return _STRING_D4_PORT;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return _STRING_D5_PORT;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
            return _STRING_D6_PORT;
#endif
        default:
            return _STRING_A0_PORT;
    }
}

#if 0//(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description :
// Input Value :  OverScan Status
// Output Value : 
//--------------------------------------------------
WORD OsdDisplayGetOverScanRatio(BYTE bOverScanStatus)
{
	// !!! Must Sync UserCommonAdjustOverScan:tusOverscanRatio
    WORD code tusOverscanRatio[][2] =
    {
        // Zoom-Factor  
        // 0 Original
        // 1 1:1.05 
        // 2 1:1.1 
        // 3 1:1.15 
        // 4 1:1.2 
        // 5 1:1.25
        // 6 1:1.5
        // 7 1:1.75
        // 8 1:2.0
        // 9 1:2.25
        // 10 1:2.5
        // then back to 1:1
    
        {100,   100},    //  1:1
        
        {100,   105},    //  1:1.05
        {100,   110},    //  1:1.1
        {100,   115},    //  1:1.15
        {100,   120},    //  1:1.2
        
        {100,   125},    //  1:1.25
        {100,   150},    //  1:1.5
        {100,   175},    //  1:1.75
        {100,   200},    //  1:2.0
        {100,   225},    //  1:2.25
        {100,   250},    //  1:2.5
        
        // Don't delete it, and place it at last.
        {100,     100},
    };
    
    return tusOverscanRatio[bOverScanStatus][1];
}
#endif

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
BYTE OsdDisplayGetVGAModeString(bit bUserMode)
{
    if(bUserMode == _USER_MODE_TYPE)
    {
        return _STRING_VGA_USER_MODE;
    }
    else
    {
        return _STRING_VGA_PRESET_MODE;
    }
}
#endif


//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : Source Port Number
//--------------------------------------------------
BYTE OsdDispJudgeSourceType(void)
{
    BYTE ucOsdSourcePort = _VGA_A0;

    switch(SysSourceGetInputPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            ucOsdSourcePort = _VGA_A0;
            return ucOsdSourcePort;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
            ucOsdSourcePort = _DVI_D0;
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            ucOsdSourcePort = _HDMI_D0;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ucOsdSourcePort = _DP_D0;
#endif
            return ucOsdSourcePort;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
            ucOsdSourcePort = _DVI_D1;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            ucOsdSourcePort = _HDMI_D1;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ucOsdSourcePort = _DP_D1;
#endif
            return ucOsdSourcePort;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
            if(_DVI_D2 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D2;
            }
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if(_HDMI_D2 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D2;
            }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(_DP_D2 > 0x10)
            {
                ucOsdSourcePort = 0x0F;
            }
            else
            {
                ucOsdSourcePort = _DP_D2;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
            if(_DVI_D3 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D3;
            }
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if(_HDMI_D3 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D3;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
            if(_DVI_D4 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D4;
            }
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if(_HDMI_D4 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D4;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
            if(_DVI_D5 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D5;
            }
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if(_HDMI_D5 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D5;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(_DP_D6 > 0x10)
            {
                ucOsdSourcePort = 0x0F;
            }
            else
            {
                ucOsdSourcePort = _DP_D6;
            }
#endif
            return ucOsdSourcePort;
#endif

        default:
            return ucOsdSourcePort;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispDisableOsd(void)
{

    SET_OSD_STATE(_MENU_NONE);
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncDisableOsd();
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    g_ucOsdWidth = 0;
    g_ucOsdHeight = 0;
    g_ucOsdWidthB = 0;
    g_ucOsdHeightB = 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
    WORD usX  = 0;
    WORD usY = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    BYTE ucHorizontalDelayStep = 4;
    BYTE ucTempWidth = g_ucOsdWidth;
    BYTE ucTempHeight = g_ucOsdHeight;

    if((enumOsdPositionType == _OSD_POSITION_GLOBAL_B) ||
       (enumOsdPositionType == _OSD_POSITION_FONT_B))
    {
        ucTempWidth = g_ucOsdWidthB;
        ucTempHeight = g_ucOsdHeightB;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL)
    {
        ucHorizontalDelayStep = 1;
    }

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth *= 2;
        ucFonHeight *= 2;
    }

    if(ucType == _POS_PERCENT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempHeight * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)(ucTempWidth - 1) * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)(ucTempHeight-1) * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#else
        usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
        usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
#endif
    }
    else
    {
        // Notice!!! if osd set double size need to chek real position
        usX = usHPos;
        usY = usVPos;
    }
    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        usX = usX / 2;
        usY = usY / 2;
    }
    OsdFuncSetPosition(enumOsdPositionType, usX, usY);
}


//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState)
{
    // _KEY_INFO_ALL
    BYTE ucColor = COLOR(_CP_WHITE, _CP_BG);
    BYTE ucRow = _OSD_MAIN_MENU_HEIGHT - _WIN_INFO_HEIGHT; 
    BYTE ucIsMainMenu = _FALSE;
    
    //BYTE ucKey1_Pos = 15,ucKey2_Pos = 20,ucKey3_Pos = 25,ucKey4_Pos = 30,ucKey5_Pos = 35,ucKey6_Pos = 40;
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    BYTE ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    BYTE ucKey1_Pos = 4,ucKey2_Pos = 12,ucKey3_Pos = 21,ucKey4_Pos = 29,ucKey5_Pos = 38,ucKey6_Pos = 47;
#else
    BYTE ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#endif
    ucItem = ucItem;
    ucState = ucState;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_HEIGHT) &&
           (g_ucOsdHeight == _OSD_MAIN_MENU_WIDTH))
        {
            ucIsMainMenu = _TRUE;
        }
    }
    else
#endif
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_WIDTH) &&
           (g_ucOsdHeight == _OSD_MAIN_MENU_HEIGHT))
        {
            ucIsMainMenu = _TRUE;
        }
    }

    if(GET_OSD_STATE() == _MENU_KEY)
    {
        // MAP_A  HEIGHT(4)
        ucColor = COLOR(_CP_WHITE, _TITLE_WIN_COLOR);
        ucRow = 0;

        //ucKey1_Pos = 3,ucKey2_Pos = 8,ucKey3_Pos = 13,ucKey4_Pos = 18,ucKey5_Pos = 23,ucKey6_Pos = 28;
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    ucKey1_Pos = 4,ucKey2_Pos = 12,ucKey3_Pos = 21,ucKey4_Pos = 29,ucKey5_Pos = 38,ucKey6_Pos = 47;
#else
    ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#endif
        
    }

    else if((GET_OSD_STATE() > _MAINMENU_END) && (GET_OSD_STATE() <= _MENU_HOTKEY_LIGHTBOX_MODE))
    {
        // MAP_A
        ucColor = COLOR(_CP_WHITE, _TITLE_WIN_COLOR);
        ucRow = _OSD_HOTKEY_MENU_HEIGHT - _WIN_HOTKEY_SOURCE_TITLE_HEIGHT;             	

        //ucKey1_Pos = 3,ucKey2_Pos = 8,ucKey3_Pos = 13,ucKey4_Pos = 18,ucKey5_Pos = 23,ucKey6_Pos = 28;
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    ucKey1_Pos = 4,ucKey2_Pos = 12,ucKey3_Pos = 21,ucKey4_Pos = 29,ucKey5_Pos = 38,ucKey6_Pos = 47;
#else
    ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#endif
        ucIsMainMenu = _TRUE;
    }

    // avoid abnormal: Lightbox mode not exit to _MENU_NONE
    if(((GET_OSD_STATE() == _MENU_KEY)&&(GET_OSD_LIGHTBOXMODE_STATUS() == _ON))||(GET_OSD_POWER_SAVING_SHOW_LIGHTBOX_MODE() == _TRUE))
    {
        //return;
    }

    // avoid abnormal: Hotkey UI mode press power key
    if((((GET_OSD_STATE() > _MAINMENU_END) && (GET_OSD_STATE() <= _MENU_HOTKEY_LIGHTBOX_MODE))&&(GET_KEYMESSAGE() == _POWER_KEY_MESSAGE)))
    {
        return;
    }

    
    if(ucState == _OSD_HIGHLIGHT) 
    {
        OsdFuncClearOsd(ROW(ucRow), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(_WIN_INFO_HEIGHT));

	    if(((GET_OSD_STATE() >= _MAINMENU_START) && (GET_OSD_STATE() <= _FUNCTION_SETTING_PAGE_END))||((GET_OSD_STATE() >= _SERVICE_PAGE_START) && (GET_OSD_STATE() <= _SERVICE_PAGE_5_END))||((GET_OSD_STATE() > _PAGE_2) && (GET_OSD_STATE() <= _IMAGE_HDR_END/*_IMAGE_PAGE_COLORTEMP_USER_END*/))||((GET_OSD_STATE() >= _SERVICE_PAGE_5_OSD_START) && (GET_OSD_STATE() <= _SERVICE_PAGE_5_OSD_END)))
        {
           // OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,   ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey2_Pos), tOSD_iKEY_ENTER,  ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey3_Pos), tOSD_iKEY_UP,     ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey4_Pos), tOSD_iKEY_DOWN,   ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey5_Pos), tOSD_iKEY_EXIT,   ucColor);

        }
    	else if((GET_OSD_STATE() == _ADVANCED_PASSWORD)||((GET_OSD_STATE() >= _IMAGE_PAGE_ADJ_START) && (GET_OSD_STATE() <= _FUNCTION_SETTING_PAGE_ADJ_END))||((GET_OSD_STATE() >= _SERVICE_PAGE_1_ADJUST_START) && (GET_OSD_STATE() <= _SERVICE_PAGE_5_ADJUST_END))||((GET_OSD_STATE() >= _IMAGE_PAGE_COLOR_TEMP_USER_ADJ_START) && (GET_OSD_STATE() <= _IMAGE_HDR_ADJ_END/*_IMAGE_PAGE_COLOR_TEMP_USER_ADJ_END*/))||((GET_OSD_STATE() >= _SERVICE_PAGE_5_OSD_ADJ_START) && (GET_OSD_STATE() <= _SERVICE_PAGE_5_OSD_ADJ_END)))
        {
            //OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,   ucColor);
            if(((GET_OSD_STATE() == _IMAGE_GAMMA_ADJ)&&((IsGammaOptionMCUCalibration(GET_OSD_GAMMA()))||(IsGammaOptionHybridGamma(GET_OSD_GAMMA()))))||
                ((GET_OSD_STATE() == _IMAGE_COLOR_TEMP_ADJ)&&(GET_COLOR_TEMP_TYPE() != _CT_SRGB)))
            {
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,   ucColor);
            }
            else
            {
                OsdFuncClearOsd(ROW(ucRow +1), COL(ucKey1_Pos), WIDTH(4), HEIGHT(1));
            }
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey2_Pos), tOSD_iKEY_ENTER,  ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey3_Pos), tOSD_iKEY_LEFT,   ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey4_Pos), tOSD_iKEY_RIGHT,  ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey5_Pos), tOSD_iKEY_EXIT,   ucColor);
        }
        else
        {
            if(GET_OSD_STATE() == _MENU_KEY)
            {
                if(ucState == _OSD_HIGHLIGHT) 
                {   
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,     ucColor);
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey2_Pos), tOSD_iKEY_GAMMA,    ucColor);
#if(_BEACON_OSD_AMB == _ON)                    
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey3_Pos), tOSD_iKEY_AMB,      ucColor);
#endif
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey4_Pos), tOSD_iKEY_KVM,      ucColor);
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey5_Pos), tOSD_iKEY_LIGHTBOX, ucColor);
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey6_Pos), tOSD_iKEY_SOURCE,   ucColor);
                }
            }
            else if((GET_OSD_STATE() > _MAINMENU_END) && (GET_OSD_STATE() <= _MENU_HOTKEY_LIGHTBOX_MODE))
            {            	    
                if(ucState == _OSD_HIGHLIGHT) 
                {
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,     ucColor);
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey2_Pos), tOSD_iKEY_GAMMA,    ucColor);
#if(_BEACON_OSD_AMB == _ON)                    
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey3_Pos), tOSD_iKEY_AMB,      ucColor);
#endif
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey4_Pos), tOSD_iKEY_KVM,      ucColor);
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey5_Pos), tOSD_iKEY_LIGHTBOX, ucColor);
                    OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey6_Pos), tOSD_iKEY_SOURCE,   ucColor);
                }
            }
        }
    }

    if(ucIsMainMenu == _FALSE)
    {
        return;
    }

    if((ucState == _OSD_SELECT) || (ucState == _OSD_HIGHLIGHT))
    {
        ucColor = COLOR(_CP_BLUE_120, _CP_BG);
        ScalerTimerReactiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT);
    }
		
    switch(ucItem)
    {
        case _KEY_INFO_MENU:
            if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey1_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
            }
            break;
			
        case _KEY_INFO_ENTER:
			if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey2_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
            }
            break;

        case _KEY_INFO_LEFT:
            if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey3_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
            }
            break;

        case _KEY_INFO_RIGHT:
            if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey4_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
            }
            break;

        case _KEY_INFO_EXIT:
            if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey5_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
            }
            break;

        case _KEY_INFO_ALL:
            if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey1_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey2_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey3_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey4_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ROW(ucRow +1), (ucKey5_Pos), WIDTH(2), HEIGHT(1), ucColor, _FONTFROM_0_255);
            }
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIcon(BYTE ucIconIndex)
{
    BYTE pucOsdItemColor = _CP_WHITE;
    BYTE ucI = 0;

    switch(ucIconIndex)
    {
	    case _ICON_MAINMENU_PAGE:
			for(ucI = _MAIN_PAGE_START; ucI <= _MAIN_PAGE_END; ucI++)
			{
    			OsdPropPutString(ROW(_OSD_MAIN_ITEM_ROW_START + (ucI - _MAIN_PAGE_START)*2), COL(_OSD_MAIN_ITEM_COL_START), _PFONT_PAGE_0,(_STRING_IMAGE + (ucI - _MAIN_PAGE_START)), _OPT_STRING_NORMAL_COLOR,  GET_OSD_LANGUAGE());	                 
			}
	    	break;
            
	     case _ICON_ADAVANCE_LEVEL_PAGE:
			for(ucI = _SERVICE_PAGE_START; ucI <= _SERVICE_PAGE_END; ucI++)
			{
    			OsdPropPutString(ROW(_OSD_MAIN_ITEM_ROW_START + (ucI - _SERVICE_PAGE_START)*2), COL(_OSD_MAIN_ITEM_COL_START), _PFONT_PAGE_0,(_STRING_PAGE_1 + (ucI - _SERVICE_PAGE_START)), _OPT_STRING_NORMAL_COLOR,  (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);	                 
			}
	    	break;			
	}

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainKey(void)
{
    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdDispDisableOsd();
    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(4), COLOR(_CP_WHITE, _CP_BG));

	//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(4), _DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
	
    // Background window
#if 0//(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
	{
	    OsdWindowDrawingByPixel(_MAINMENU_TITLE_WINDOW, ROW(_WIN_TITLE_ROW_START_PIXEL), COL(_WIN_TITLE_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-_WIN_TITLE_COL_START_PIXEL), HEIGHT(_WIN_TITLE_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_INFO_WINDOW, ROW(_WIN_MAIN_INFO_ROW_START_PIXEL), COL(_WIN_MAIN_INFO_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(_WIN_INFO_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_MAIN_ROW_START_PIXEL), COL(_WIN_MAIN_COL_START_PIXEL), WIDTH(_WIN_MAIN_WIDTH*12), HEIGHT(_WIN_MAIN_HEIGHT*18), _MAIN_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_SUB_WINDOW, ROW(_WIN_SUB_ROW_START_PIXEL), COL(_WIN_SUB_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-(_WIN_MAIN_WIDTH*12)), HEIGHT((g_ucOsdHeight - _WIN_INFO_HEIGHT-_WIN_TITLE_HEIGHT)*18), _SUB_WIN_COLOR);
	}
#endif

    SET_OSD_STATE(_MENU_KEY);
    ScalerOsdChange1BitColor(ROW(0), COL(_WIN_HOTKEY_COL_START_PIXEL), LENGTH(g_ucOsdWidth), HEIGHT(4), FG_COLOR(_TITLE_WIN_COLOR), BG_COLOR(_TITLE_WIN_COLOR));
     
    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_HIGHLIGHT);
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//DebugMessageUart("GET_OSD_HPOS_key()", GET_OSD_HPOS());
//DebugMessageUart("GET_OSD_VPOS_key()", GET_OSD_VPOS());

    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenu(void)
{
    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncDisableOsd();
    ScalerOsdWindowDisable(_OSD_WINDOW_ALL);

    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    //OsdFontVLCLoadFont(_FONT1_2BIT);
    //OsdFontVLCLoadMultiFont();

    // Background window
#if 0//(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
	{
	    OsdWindowDrawingByPixel(_MAINMENU_TITLE_WINDOW, ROW(_WIN_TITLE_ROW_START_PIXEL), COL(_WIN_TITLE_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-_WIN_TITLE_COL_START_PIXEL), HEIGHT(_WIN_TITLE_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_INFO_WINDOW, ROW(_WIN_MAIN_INFO_ROW_START_PIXEL), COL(_WIN_MAIN_INFO_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(_WIN_INFO_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_MAIN_ROW_START_PIXEL), COL(_WIN_MAIN_COL_START_PIXEL), WIDTH(_WIN_MAIN_WIDTH*12), HEIGHT(_WIN_MAIN_HEIGHT*18), _MAIN_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_SUB_WINDOW, ROW(_WIN_SUB_ROW_START_PIXEL), COL(_WIN_SUB_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-(_WIN_MAIN_WIDTH*12)), HEIGHT((g_ucOsdHeight - _WIN_INFO_HEIGHT-_WIN_TITLE_HEIGHT)*18), _SUB_WIN_COLOR);
	}
	
    if(UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE) == _ON)
    {
#if(_POWER_ON_LOGO_TYPE == _LOGO_BEACON)
    	//OsdFontPut2BitTable(ROW(0), COL(/*g_ucOsdWidth - 12*/0), tOSD_MAIN_LOGO, COLOR0(_CP_GRAY_32), COLOR1(_CP_WHITE),COLOR2(_CP_BLUE_120),COLOR3(_CP_BLUE_120));
#endif
	}
	
    DrawMainPage();
   
#if 0//(_STACK_SIZE_TEST == _ENABLE)
    OsdPropShowNumber(ROW(1), COL(20), g_max_sp,        (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
    OsdPropShowNumber(ROW(1), COL(24), g_EXINT0_count,  (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
    OsdPropShowNumber(ROW(1), COL(28), g_EXINT1_count,  (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
    for(pData[0] = 0; pData[0] < ((_DDCCI_RXBUF_LENGTH > 100) ? 82 : _DDCCI_RXBUF_LENGTH); pData[0]++)
	{
	    OsdPropShowNumber(ROW(4 + (pData[0]/10)), COL(20 + 4*(pData[0] % 10)), g_pucTempDdcciRxBuf[pData[0]], (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
	}	
#else
    DrawSubMenu(GET_OSD_STATE());           
#endif

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispServiceLevelMenu(void)
{
    OsdSelectedUpdate(_STATE_CLEAR,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
    SET_OSD_STATE(_SERVICE_PAGE_START);
	OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
	OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));

    DrawServiceLevelPage();
    UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
    DrawSubMenu(GET_OSD_STATE());           
}

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue, BYTE ucRowIndex, BYTE ucColor)
{
    BYTE ucCol = _OSD_ITEM_VALUE_COL;
    
    
    g_usAdjustValue = usValue;
 	//DebugMessageUart("Slider:", g_usAdjustValue);
 	DebugMessageOsd("Slider:", g_usAdjustValue);
    OsdFuncClearOsd(ROW(ucRowIndex*_OSD_ROW_STEP + _OSD_ITEM_1_ROW_START), COL(_OSD_ITEM_VALUE_COL), WIDTH(_OSD_MAIN_MENU_WIDTH - _OSD_ITEM_VALUE_COL), HEIGHT(2));

    switch(usOsdState)
    {
        case _IMAGE_PCM:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_COLOR_PCM_SRGB + g_usAdjustValue), ucColor, _ENGLISH);
            break; 
	
        case _IMAGE_GAMMA:
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),_PFONT_PAGE_1,(_STRING_PCM_STANDARD + g_usAdjustValue), ucColor, _ENGLISH);
            else
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),_PFONT_PAGE_1,(_STRING_GAMMA_OFF + g_usAdjustValue), ucColor,GET_OSD_LANGUAGE());
            break;

        case _IMAGE_DICOMALC:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_ALC_X_RAY  + g_usAdjustValue), ucColor, _ENGLISH);
            break;

        case _IMAGE_COLOR_TEMP:
            if((IsGammaOptionPCCalibration(GET_OSD_GAMMA()))&&(GET_COLOR_TEMP_TYPE() != _CT_SRGB))
            {
                // Refresh colortemp char: PC Calib is User define
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1, _STRING_CT_USER, ucColor, GET_OSD_LANGUAGE());
            }
            else
            {
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_CT_9300 + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            }
            break;

#if(_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        			
        case _IMAGE_BACKLIGHT:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;
#endif           

#if(_HDR10_SUPPORT == _ON)
        case _IMAGE_HDR_MODE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_HDR10_MODE_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;            
                                    
        case _IMAGE_HDR_DARK_ENHANCE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),_PFONT_PAGE_1,(_STRING_OFF  + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            
        case _IMAGE_HDR_SHARP_ENHANCE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),_PFONT_PAGE_1,(_STRING_OFF  + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            
        case _IMAGE_HDR_CONTRAST:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
    	     break;
#endif
 
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
        case _QA_TEST_IMAGE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
#endif

        case _FUNCTION_LANGUAGE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_ENGLISH + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;

        case _FUNCTION_AMB_LIGHT:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_AMB_OFF + g_usAdjustValue), ucColor, (g_usAdjustValue == 0)?GET_OSD_LANGUAGE(): _ENGLISH);
            break;

        case _FUNCTION_REPORT_MODE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            
        case _FUNCTION_2HOURS_REMINDER:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;

        case _FUNCTION_INPUT:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),_PFONT_PAGE_1,(_STRING_A0_PORT + g_usAdjustValue), ucColor, (g_usAdjustValue == _OSD_INPUT_AUTO)?GET_OSD_LANGUAGE(): _ENGLISH);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_A0_PORT + g_usAdjustValue), ucColor, (g_usAdjustValue == _OSD_INPUT_AUTO)?GET_OSD_LANGUAGE(): _ENGLISH);

            break;
            
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)            
        case _GAMMA_USER_TYPE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_GAMMA_USER_TYPE_DICON+ g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;

        case _GAMMA_USER_L_MAX:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;

        case _GAMMA_USER_L_MIN:
            OsdPropShowNumber_float(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;

        case _GAMMA_USER_LAMB:
            OsdPropShowNumber_float(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;

        case _GAMMA_USER_VALUE:
            OsdPropShowNumber_float(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_1), ucColor);
            break;
#endif
        case _COLOR_TEMP_USER_R:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;
			
        case _COLOR_TEMP_USER_G:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;

        case _COLOR_TEMP_USER_B:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)            
        case _IMAGE_HYBRID_GRAY_CURVE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_GAMMA_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
#endif

//--------------------------------------------------------            
//----------------------Service---------------------------          
//--------------------------------------------------------            
        case _DISPLAY_ROTATE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_0_DEGREE  + g_usAdjustValue), ucColor, _ENGLISH);
            break;
            
         case _ASPECT_RATIO:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_ASPECT_FULL  + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;

#if 0            
        case _OVERSCAN:
            OsdPropShowNumberPercentage(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), OsdDisplayGetOverScanRatio(g_usAdjustValue), _FALSE, _PFONT_PAGE_1, ucColor);
            {
                if(g_usAdjustValue == 0)
                {
                    OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1, _STRING_OFF, ucColor,  (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
                }
                else
                {
                    OsdPropShowNumberPercentage(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), OsdDisplayGetOverScanRatio(g_usAdjustValue), _FALSE, _PFONT_PAGE_2, ucColor);
                }
            }
            break;
#endif
                                   
        case _DP_VERSION:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_1_DOT_1 + g_usAdjustValue), ucColor, _ENGLISH);
            break;
            
        case _DP_MST:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_MST_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
            
        case _DP_CLONE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
            
        case _DP_RESOLUTION:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_DP_1080P + g_usAdjustValue), ucColor, _ENGLISH);
            break;
            
        case _UNIFORMITY:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
                       
#if (_SDR_TO_HDR_SUPPORT == _ON)
        case _SDR:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
 #endif


 #if(_VGA_SUPPORT == _ON)            
        case _ANALOG_PAGE_H_POSTION_ITEM:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;
            
        case _ANALOG_PAGE_V_POSTION_ITEM:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;
            
        case _ANALOG_PAGE_CLOCK_ITEM:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;

        case _ANALOG_PAGE_PHASE_ITEM:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;
#endif            

         case _AMBIENT_SENSOR:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;

        case _BODY_SENSOR:
            if(g_usAdjustValue == _OSD_DISTANCE_OFF)
			{
	            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
			}
			else
			{
	            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_15S + g_usAdjustValue -1), ucColor,  _ENGLISH);
			}
            break;
            
        case _GRAVITY_SENSOR:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;

        case _BACKLIGHT_SENSOR:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
                        
        case _ENERGY_SAVING:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_ENERGYSAVING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
 
        case _OSD_TIME:
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, ucColor);
            break;
    
        case _OSD_ROTATE:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),_PFONT_PAGE_1,(_STRING_OSD_0_DEGREE  + g_usAdjustValue), ucColor, _ENGLISH);
            break;

        case _OSD_POSITION:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OSD_POSITON_LT + g_usAdjustValue), ucColor, _ENGLISH);
            break;
			
        case _USE_LIFE_REMINDER:
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), _PFONT_PAGE_1,(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;

            
//--------------------------------------------------------            
//----------------------Service---------------------------          
//--------------------------------------------------------            


//--------------------------------------------------------            
//************************ adjust ************************ 
//--------------------------------------------------------            
        case _IMAGE_PCM_ADJ:
            g_usAdjustValue = OsdFuncCheckPCMStatusAdjustType(g_usAdjustValue);
            SET_OSD_PCM_STATUS( g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_COLOR_PCM_SRGB + g_usAdjustValue), ucColor, _ENGLISH);
            break;
			
        case _IMAGE_GAMMA_ADJ:
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
            {
                g_usAdjustValue = OsdFuncCheckPCMInputGammaAdjustType(g_usAdjustValue);
                SET_OSD_PCM_INPUTGAMMA( g_usAdjustValue);
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_PCM_STANDARD + g_usAdjustValue), ucColor, _ENGLISH);
            }
            else
            {
                g_usAdjustValue = OsdFuncCheckGammaAdjustType(g_usAdjustValue);
                SET_OSD_GAMMA( g_usAdjustValue);
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_GAMMA_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            }
            break;

        case _IMAGE_DICOMALC_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ALC_AMOUNT, _ALC_X_RAY, _ON);
            //SET_OSD_DICOMALC( g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_ALC_X_RAY + g_usAdjustValue), ucColor, _ENGLISH);
            break;

        case _IMAGE_COLOR_TEMP_ADJ:
			g_usAdjustValue = OsdFuncCheckColorTempAdjustType(g_usAdjustValue);
			SET_COLOR_TEMP_TYPE( g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_CT_9300 + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            
        case _IMAGE_BACKLIGHT_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);  
            SET_OSD_BACKLIGHT(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;

#if(_HDR10_SUPPORT == _ON)
        case _IMAGE_HDR_MODE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _HDR10_MODE_FORCE_2084, _HDR10_MODE_OFF, _ON);
            SET_OSD_HDR_MODE( g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_HDR10_MODE_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
            
        case _IMAGE_HDR_DARK_ENHANCE_ADJ:
            SET_OSD_DARK_ENHANCE_STATUS(OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON));
            g_usAdjustValue = GET_OSD_DARK_ENHANCE_STATUS();
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),(_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF  + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            
        case _IMAGE_HDR_SHARP_ENHANCE_ADJ:
            SET_OSD_HDR_SHARPNESS(OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON));
            g_usAdjustValue = GET_OSD_HDR_SHARPNESS();
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol),(_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF  + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            
        case _IMAGE_HDR_CONTRAST_ADJ:
            SET_OSD_HDR_CONTRAST(OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF));
            g_usAdjustValue = GET_OSD_HDR_CONTRAST();
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3),(_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
    	     break;
#endif             

        case _QA_TEST_IMAGE_ADJ:
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
			g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
			//SET_OSD_FPGA_TEST_IMAGE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
#endif
            break;

        case _FUNCTION_LANGUAGE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LANGUAGE_AMOUNT, _ENGLISH, _ON);
            //SET_OSD_LANGUAGE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_ENGLISH  + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;

        case _FUNCTION_AMB_LIGHT_ADJ:
	        g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _AMB_LIGHT_AMOUNT, _AMB_LIGHT_OFF, _ON);
		    SET_OSD_BACKGROUND_LIGHT_MODE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_AMB_OFF + g_usAdjustValue), ucColor, (g_usAdjustValue == 0)?GET_OSD_LANGUAGE(): _ENGLISH);
            break;

        case _FUNCTION_REPORT_MODE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
		    //SET_OSD_READING_REPORT_MODE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;

        case _FUNCTION_2HOURS_REMINDER_ADJ:
	        g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
		    //SET_OSD_2HOURS_TIPS(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;

			
         case _FUNCTION_INPUT_ADJ:
            g_usAdjustValue = OsdFuncCheckInputPortType(g_usAdjustValue);
            //SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_A0_PORT + g_usAdjustValue), ucColor, (g_usAdjustValue == _OSD_INPUT_AUTO)?GET_OSD_LANGUAGE(): _ENGLISH);
			break;

#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)        
        case _GAMMA_USER_TYPE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LUT_USER_GAMMA, _LUT_USER_DICOM, _ON);
            //SET_OSD_LUT_USER_TYPE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_GAMMA_USER_TYPE_DICON + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
  
        case _GAMMA_USER_L_MAX_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LMAX_MAX, _LMAX_MIN, _OFF); 
            SET_OSD_LUT_USER_L_MAX(g_usAdjustValue);
            //DebugMessageUart("ADJ _L_MAX:", g_usAdjustValue);

            // Check if the user setting parameters conform to the actual contrast ratio of the panel 
            {
                WORD g_usCurrPanelContrastRatio,g_usUserSetPanelContrastRatio;

            	RTDNVRamLoadPanelLuxRangeData();
                g_usCurrPanelContrastRatio = MINOF((WORD)(g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax/g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin), (WORD)(g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax/g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin));
                g_usCurrPanelContrastRatio = (g_usCurrPanelContrastRatio / 100)*100;
                //1268->1200
                
                g_usUserSetPanelContrastRatio = GET_OSD_LUT_USER_L_MAX()*10 /  GET_OSD_LUT_USER_L_MIN();
                g_usUserSetPanelContrastRatio = (g_usUserSetPanelContrastRatio /100)*100;
                //1639->1600

             	//DebugMessageUart("Panel-Ratio:", g_usCurrPanelContrastRatio);
                //DebugMessageUart("Set Ratio:", g_usUserSetPanelContrastRatio);

                // Check if the user setting parameters conform to the actual contrast ratio of the panel 
                if(g_usUserSetPanelContrastRatio >= g_usCurrPanelContrastRatio)
                {
                    SET_OSD_LUT_USER_L_MIN((((BYTE)((DWORD)GET_OSD_LUT_USER_L_MAX()*100/g_usCurrPanelContrastRatio) + 5)/10));
                 	//DebugMessageUart("adj-LMin:", GET_OSD_LUT_USER_L_MIN());
                }
            }
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;
    
        case _GAMMA_USER_L_MIN_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LMIN_MAX, _LMIN_MIN, _OFF); 
            SET_OSD_LUT_USER_L_MIN(g_usAdjustValue);
            //DebugMessageUart("ADJ _L_MIN:", g_usAdjustValue);

            // Check if the user setting parameters conform to the actual contrast ratio of the panel 
            {
                WORD g_usCurrPanelContrastRatio,g_usUserSetPanelContrastRatio;

            	RTDNVRamLoadPanelLuxRangeData();
                g_usCurrPanelContrastRatio = MINOF((WORD)(g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax/g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin), (WORD)(g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax/g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin));
                g_usCurrPanelContrastRatio = (g_usCurrPanelContrastRatio / 100)*100;
                //1268->1200
                
                g_usUserSetPanelContrastRatio = GET_OSD_LUT_USER_L_MAX()*10 /  GET_OSD_LUT_USER_L_MIN();
                g_usUserSetPanelContrastRatio = (g_usUserSetPanelContrastRatio /100)*100;
                //1639->1600

             	//DebugMessageUart("Panel-Ratio:", g_usCurrPanelContrastRatio);
                //DebugMessageUart("Set Ratio:", g_usUserSetPanelContrastRatio);

                // Check if the user setting parameters conform to the actual contrast ratio of the panel 
                if(g_usUserSetPanelContrastRatio >= g_usCurrPanelContrastRatio)
                {
                    g_usAdjustValue =(((BYTE)((DWORD)GET_OSD_LUT_USER_L_MAX()*100/g_usCurrPanelContrastRatio) + 5)/10);
                 	//DebugMessageUart("1-LMin:", ((BYTE)((DWORD)GET_OSD_LUT_USER_L_MAX()*100/g_usCurrPanelContrastRatio)));
                 	//DebugMessageUart("1-LMin:", g_usAdjustValue);
                    SET_OSD_LUT_USER_L_MIN(g_usAdjustValue);
                }
            }
            if(g_usAdjustValue == 0)
            {
                OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            }
            else
            {
                OsdPropShowNumber_float(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            }
            break;
         
        case _GAMMA_USER_LAMB_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LAMB_MAX, _LAMB_MIN, _OFF); 
            SET_OSD_LUT_USER_LAMB(g_usAdjustValue);
            if(g_usAdjustValue == 0)
            {
                OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            }
            else
            {
                OsdPropShowNumber_float(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            }
            break;
            
        case _GAMMA_USER_VALUE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LUT_USER_VALUE_MAX, _LUT_USER_VALUE_MIN, _OFF); 
            SET_OSD_LUT_USER_VALUE(g_usAdjustValue);
            OsdPropShowNumber_float(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;
#endif			
        case _COLOR_TEMP_USER_R_ADJ:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;
			
        case _COLOR_TEMP_USER_G_ADJ:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;

        case _COLOR_TEMP_USER_B_ADJ:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)            
        case _IMAGE_HYBRID_GRAY_CURVE_ADJ:
            g_usAdjustValue = OsdFuncCheckGammaAdjustType(g_usAdjustValue);
            SET_OSD_FPGA_GRAY_GAMMA( g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_GAMMA_OFF + g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
#endif

//--------------------------------------------------------            
//--------------------Service  adjust---------------------          
//--------------------------------------------------------                        
         
         case _DISPLAY_ROTATE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _DISP_ROTATE_AMOUNT-1, _DISP_ROTATE_0, _ON);
            //SET_OSD_DISP_ROTATE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_0_DEGREE + g_usAdjustValue), ucColor, _ENGLISH);
            break;
                                 
         case _ASPECT_RATIO_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_ASPECT_RATIO_AMOUNT, _OSD_ASPECT_RATIO_FULL, _ON);
            //SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_ASPECT_FULL + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
             
#if 0          
        case  _OVERSCAN_ADJ:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OVER_SCAN_AMOUNT, _OVER_SCAN_OFF, _ON);
            SET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort(),g_usAdjustValue);
            OsdPropShowNumberPercentage(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), OsdDisplayGetOverScanRatio(g_usAdjustValue), _FALSE, (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);

			if(g_usAdjustValue == 0)
			{
	            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex), _STRING_OFF, ucColor, GET_OSD_LANGUAGE());
			}
			else
			{
    		    OsdPropShowNumberPercentage(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), OsdDisplayGetOverScanRatio(g_usAdjustValue), _FALSE, (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
        	}
            break;
#endif

        case _DP_VERSION_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _DP_VER_AMOUNT, _DP_VER_1_DOT_1, _ON);			
            //SET_OSD_DP_D0_VERSION(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_1_DOT_1 + g_usAdjustValue), ucColor, _ENGLISH);
            break;
            
        case _DP_MST_ADJ:
            OsdDisplayMstOverRange();
    	    g_usAdjustValue = GET_OSD_DP_MST();
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_MST_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
            
        case _DP_CLONE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            //SET_OSD_CLONE_MODE_1P(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
            
        case _DP_RESOLUTION_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _DP_EDID_2560_1440, _DP_EDID_1080P, _ON);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_DP_1080P + g_usAdjustValue), ucColor, _ENGLISH);
            break;
            
        case _UNIFORMITY_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            //SET_OSD_PANEL_UNIFORMITY(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;

#if (_SDR_TO_HDR_SUPPORT == _ON)        
        case _SDR_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            //SET_OSD_PANEL_UNIFORMITY(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
#endif    

        //**********************************************************************
        //Analog Page Adust
        //**********************************************************************
#if(_VGA_SUPPORT == _ON)        
        case _ANALOG_PAGE_H_POS_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
    		#if(_VGA_SUPPORT == _ON)
            SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
    		#endif
            break;
            
        case _ANALOG_PAGE_V_POS_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
    		#if(_VGA_SUPPORT == _ON)
            SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
    		#endif
            break;
            
        case _ANALOG_PAGE_CLOCK_ADJUST:
			#if(_VGA_SUPPORT == _ON)
    		#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
    		#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                //usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                //usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, usClockRangeMax, usClockRangeMin, _OFF);
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
            }
    		#endif
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
			#endif
            break;
            
        case _ANALOG_PAGE_PHASE_ADJUST:
			#if(_VGA_SUPPORT == _ON)
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PHASE_MAX, _OSD_PHASE_MIN, _OFF);
            SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3),(_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
			#endif
            break;
#endif 

        case _AMBIENT_SENSOR_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            //SET_OSD_AMBIENTLIGHT_SENSOR_STATUS(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
                        
        case _BODY_SENSOR_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_DISTANCE_AMOUNT, _OSD_DISTANCE_OFF, _ON);
            //SET_OSD_DISTANCE_SENSOR_STATUS(g_usAdjustValue);
            if(g_usAdjustValue == _OSD_DISTANCE_OFF)
            {
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),_STRING_OFF, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            }
            else
            {
                OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_15S + g_usAdjustValue - 1), ucColor, _ENGLISH);
            }
            break;
            
        case _GRAVITY_SENSOR_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            //SET_OSD_DISTANCE_SENSOR_STATUS(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);            
            break;

        case _BACKLIGHT_SENSOR_ADJ:
	        g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
	        //SET_OSD_BACKLIGHT_SENSOR_STATUS(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
			break;
            
         case _ENERGY_SAVING_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _DEEP_POWER_SAVING, _OFF_POWER_SAVING, _ON);
            //SET_OSD_POWER_SAVING_MODE(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_ENERGYSAVING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
            
        case _OSD_TIME_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OFF);
            //SET_OSD_TIME_OUT(g_usAdjustValue);
            OsdPropShowNumber(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), g_usAdjustValue, (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), (_PFONT_PAGE_ITEM_1 + ucRowIndex), ucColor);
            break;
            
        case _OSD_POSITION_ADJ:                
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_POSITON_AMOUNT, _OSD_POSITON_LT, _ON);
            SET_OSD_POSTION(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OSD_POSITON_LT + g_usAdjustValue), ucColor,  _ENGLISH);
            break;
         
        case _OSD_ROTATE_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_ROTATE_DEGREE_180, _OSD_ROTATE_DEGREE_0, _ON);
            SET_OSD_ROTATE_STATUS(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OSD_0_DEGREE + g_usAdjustValue), ucColor, _ENGLISH);
            break;                             
            
        case _USE_LIFE_REMINDER_ADJ:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            //SET_OSD_PANEL_USELIFE_TIPS(g_usAdjustValue);
            OsdPropPutString(ROW(ucRowIndex*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(ucCol), (_PFONT_PAGE_ITEM_1 + ucRowIndex),(_STRING_OFF + g_usAdjustValue), ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
            break;
          
        default:
            break;
	
    }
}

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    usValue = MINOF(usValue, usMax);
    usValue = MAXOF(usValue, usMin);

    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }

            break;

        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)
            if(GET_OSD_STATE() == _MENU_HOTKEY_AMB_MODE)
            {  
                // _LEFT_KEY_MESSAGE
                if(usValue >= usMax)
                {
                    if(bCycle == _ON)
                    {
                        return usMin;
                    }
                    else
                    {
                        return usMax;
                    }
                }
                else
                {
                    usValue++;
                }
            }
            else
#endif
            {
                if (usValue <= usMin)
                {
                    if(bCycle == _ON)
                    {
                        return usMax;
                    }
                    else
                    {
                        return usMin;
                    }
                }
                else
                {
                    usValue--;
                }
            }
            break;

        default:
            break;
    }

    return usValue;
}
//--------------------------------------------------
// mst 
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisplayMstOverRange(void)
{
    BYTE ucDone = _FALSE;
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        switch(GET_OSD_DP_MST())
        {
            case _MST_OFF:
                break;
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
            case _MST_AUTO:
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                     ucDone = _TRUE;
                }
                break;
#endif
            case _MST_D0:
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_AUTO);
                    ucDone = _TRUE;
                }
#endif
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }
                break;

            case _MST_D1:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D0);
                    ucDone = _TRUE;
                }
#endif
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_AUTO);
                    ucDone = _TRUE;
                }
#endif
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                break;

            case _MST_D6:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D1);
                    ucDone = _TRUE;
                }
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D0);
                    ucDone = _TRUE;
                }
#endif
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_AUTO);
                    ucDone = _TRUE;
                }
#endif
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                break;

            default:
                break;
        }
    }
    else if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        switch(GET_OSD_DP_MST())
        {
            case _MST_OFF:
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                if(ucDone == _FALSE)
                {
                    SET_OSD_DP_MST(_MST_AUTO);
                    ucDone = _TRUE;
                }
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D0);
                    ucDone = _TRUE;
                }
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D1);
                    ucDone = _TRUE;
                }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))

                if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D6);
                    ucDone = _TRUE;
                }
#endif
                break;

#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
            case _MST_AUTO:
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D0);
                    ucDone = _TRUE;
                }
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D1);
                    ucDone = _TRUE;
                }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))

                if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D6);
                    ucDone = _TRUE;
                }
#endif
                break;
#endif
            case _MST_D0:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))

                if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D1);
                    ucDone = _TRUE;
                }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))

                if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D6);
                    ucDone = _TRUE;
                }
#endif
                break;

            case _MST_D1:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
                if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                {
                    SET_OSD_DP_MST(_MST_D6);
                    ucDone = _TRUE;
                }
#endif

                break;

            case _MST_D6:
                break;

            default:
                break;
        }
    }  
}            

//--------------------------------------------------
// Description  : Six Color Get One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColor(BYTE ucColor)
{
    switch(ucColor)
    {
        case _SIXCOLOR_R:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueR);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationR);
            break;

        case _SIXCOLOR_Y:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueY);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationY);
            break;

        case _SIXCOLOR_G:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueG);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationG);
            break;

        case _SIXCOLOR_C:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueC);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationC);
            break;

        case _SIXCOLOR_B:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueB);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationB);
            break;

        case _SIXCOLOR_M:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueM);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationM);
            break;

        default:
            break;
    }
}

#if 0
//--------------------------------------------------
// Description  : Six Color Set One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorSetOneColor(BYTE ucColor)
{
    switch(ucColor)
    {
        case _SIXCOLOR_R:
            g_stSixColorData.ucSixColorHueR = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationR = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_Y:
            g_stSixColorData.ucSixColorHueY = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationY = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_G:
            g_stSixColorData.ucSixColorHueG = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationG = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_C:
            g_stSixColorData.ucSixColorHueC = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationC = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_B:
            g_stSixColorData.ucSixColorHueB = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationB = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_M:
            g_stSixColorData.ucSixColorHueM = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationM = GET_OSD_SIX_COLOR_SATURATION();
            break;

        default:
            break;
    }
}
#endif

#if ((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdRotateSwitch(void)
{
    OsdFuncDisableOsd();

    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    //OsdFontVLCLoadFont(_FONT1_2BIT);
    //OsdFontVLCLoadMultiFont();

    // Background window
#if 0//(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
	{
	    OsdWindowDrawingByPixel(_MAINMENU_TITLE_WINDOW, ROW(_WIN_TITLE_ROW_START_PIXEL), COL(_WIN_TITLE_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-_WIN_TITLE_COL_START_PIXEL), HEIGHT(_WIN_TITLE_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_INFO_WINDOW, ROW(_WIN_MAIN_INFO_ROW_START_PIXEL), COL(_WIN_MAIN_INFO_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(_WIN_INFO_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_MAIN_ROW_START_PIXEL), COL(_WIN_MAIN_COL_START_PIXEL), WIDTH(_WIN_MAIN_WIDTH*12), HEIGHT(_WIN_MAIN_HEIGHT*18), _MAIN_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_SUB_WINDOW, ROW(_WIN_SUB_ROW_START_PIXEL), COL(_WIN_SUB_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-(_WIN_MAIN_WIDTH*12)), HEIGHT((g_ucOsdHeight - _WIN_INFO_HEIGHT-_WIN_TITLE_HEIGHT)*18), _SUB_WIN_COLOR);
	}
	
    if(UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE) == _ON)
    {
#if(_POWER_ON_LOGO_TYPE == _LOGO_BEACON)
    	//OsdFontPut2BitTable(ROW(0), COL(0), tOSD_MAIN_LOGO, COLOR0(_CP_GRAY_32), COLOR1(_CP_WHITE),COLOR2(_CP_BLUE_120),COLOR3(_CP_BLUE_120));
#endif
	}
	
    SET_OSD_STATE(_SERVICE_PAGE_5);
    DrawServiceLevelPage();
    UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);

    SET_OSD_STATE(_SERVICE_PAGE_5_OSD_START);
    DrawSubMenu(GET_OSD_STATE());           

	SET_OSD_STATE(_OSD_ROTATE);
    OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
    
    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif



//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispHotKeyOptionMenu(BYTE ucOption)
{
    BYTE ucInterval;
    BYTE ucColor = COLOR(_CP_WHITE, _TITLE_WIN_COLOR);
    BYTE ucRow = _OSD_HOTKEY_MENU_HEIGHT - _WIN_HOTKEY_SOURCE_TITLE_HEIGHT; 

    //BYTE ucKey1_Pos = 3,ucKey2_Pos = 8,ucKey3_Pos = 13,ucKey4_Pos = 18,ucKey5_Pos = 23,ucKey6_Pos = 28;
#if ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
     (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    BYTE ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    BYTE ucKey1_Pos = 4,ucKey2_Pos = 12,ucKey3_Pos = 21,ucKey4_Pos = 29,ucKey5_Pos = 38,ucKey6_Pos = 47;
#else
    BYTE ucKey1_Pos = 2,ucKey2_Pos =  9,ucKey3_Pos = 16,ucKey4_Pos = 22,ucKey5_Pos = 29,ucKey6_Pos = 36;
#endif

	//DebugMessageUart("HotKey Menu:", ucOption);

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdDispDisableOsd();
    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif
    
    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    //OsdFontVLCLoadFont(_FONT1_2BIT);

    OsdFuncClearOsd(ROW(2), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(4));

    if((ucOption == _HOTKEY_DEVIATION)||(ucOption ==_HOTKEY_RESET))
    {
        OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_HOTKEY_ROW_START_PIXEL), COL(_WIN_HOTKEY_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT((g_ucOsdHeight-4)*18), _MAIN_WIN_COLOR);
        OsdWindowDrawingByPixel(_MAINMENU_INFO_WINDOW, ROW((g_ucOsdHeight-4)*18), COL(_WIN_HOTKEY_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(4*18), _TITLE_WIN_COLOR);

        ucInterval = (g_ucOsdWidth-_WIN_HOTKEY_VALUE_COL)/2;
        OsdFontPut1BitTable((g_ucOsdHeight-3), ucKey2_Pos, tOSD_iKEY_ENTER, COLOR(_CP_WHITE, _CP_BG));
        OsdPropPutString((g_ucOsdHeight-2),    ucKey2_Pos, _PFONT_PAGE_0, _STRING_YES, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());            

        OsdFontPut1BitTable((g_ucOsdHeight-3), ucKey5_Pos, tOSD_iKEY_EXIT, COLOR(_CP_WHITE, _CP_BG));
        OsdPropPutString((g_ucOsdHeight-2),    ucKey5_Pos, _PFONT_PAGE_0, _STRING_NO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());            
    }
    else if((ucOption == _HOTKEY_GAMMA)||(ucOption == _HOTKEY_AMB)||(ucOption == _HOTKEY_KVM)||(ucOption == _HOTKEY_COLOR_MONO)||(ucOption == _HOTKEY_I_LUMINANCE)||(ucOption == _HOTKEY_LIGHTBOX))
    {
        OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_HOTKEY_ROW_START_PIXEL), COL(_WIN_HOTKEY_COL_START_PIXEL), WIDTH(_WIN_HOTKEY_INFO_WIDTH*12), HEIGHT((g_ucOsdHeight-4)*18), _MAIN_WIN_COLOR);
        OsdWindowDrawingByPixel(_MAINMENU_SUB_WINDOW, ROW(_WIN_HOTKEY_ROW_START_PIXEL), COL(_WIN_HOTKEY_INFO_WIDTH*12-1), WIDTH((g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH)*12), HEIGHT((g_ucOsdHeight-4)*18), _SUB_WIN_COLOR);
        OsdWindowDrawingByPixel(_MAINMENU_INFO_WINDOW, ROW((g_ucOsdHeight-4)*18), COL(_WIN_HOTKEY_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(4*18), _TITLE_WIN_COLOR);

    }
    else
    {
        OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_HOTKEY_ROW_START_PIXEL), COL(_WIN_HOTKEY_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(g_ucOsdHeight*18), _MAIN_WIN_COLOR);
    }
	
    switch(ucOption)
    {
        case _HOTKEY_LIGHTBOX:
            {
                SET_OSD_STATE(_MENU_HOTKEY_LIGHTBOX_MODE);     
              
                OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(_WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_0, _STRING_LIGHT_BOX, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
                OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (_STRING_OFF + GET_OSD_LIGHTBOXMODE_STATUS()), COLOR(_CP_WHITE, _SUB_WIN_COLOR), GET_OSD_LANGUAGE());
            }
            break;
#if((_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)&&\
    (_PRODUCT_ID_SEL != RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
        case _HOTKEY_COLOR_MONO:
            {
                SET_OSD_STATE(_MENU_HOTKEY_COLOR_MONO);
                if(GET_OSD_SATURATION() == _SATURATION_CENTER)
                {
                    g_usAdjustValue = 50;
                }
                else
                {
                    g_usAdjustValue = 0;
                }
                g_usBackupValue = g_usAdjustValue;

                OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(_WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_0, _STRING_COLOR_SWITCH, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
                OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (GET_OSD_SATURATION() == _SATURATION_CENTER)?_STRING_COLOR_SWITCH_COLOR : _STRING_COLOR_SWITCH_SINGLE, _ITEM_ADJUST_COLOR, _ENGLISH);

                // MAP_A
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,     ucColor);
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey2_Pos), tOSD_iKEY_GAMMA,    ucColor);
#if(_BEACON_OSD_AMB == _ON)                
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey3_Pos), tOSD_iKEY_AMB,      ucColor);
#endif
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey4_Pos), tOSD_iKEY_KVM,      ucColor);
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey5_Pos), tOSD_iKEY_LIGHTBOX, ucColor);
                OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey6_Pos), tOSD_iKEY_SOURCE,   ucColor);

            }
            break;
#endif            
        case _HOTKEY_I_LUMINANCE:
            SET_OSD_STATE(_MENU_HOTKEY_I_LUMINANCE_MODE);            
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(_WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_0, _STRING_LUMIN, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, _STRING_OFF + UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE), _ITEM_ADJUST_COLOR, GET_OSD_LANGUAGE());

            // MAP_A
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey1_Pos), tOSD_iKEY_MENU,     ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey2_Pos), tOSD_iKEY_GAMMA,    ucColor);
#if(_BEACON_OSD_AMB == _ON)            
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey3_Pos), tOSD_iKEY_AMB,      ucColor);
#endif
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey4_Pos), tOSD_iKEY_KVM,      ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey5_Pos), tOSD_iKEY_LIGHTBOX, ucColor);
            OsdFontPut1BitTable(ROW(ucRow +1), COL(ucKey6_Pos), tOSD_iKEY_SOURCE,   ucColor);
            break;

        case _HOTKEY_GAMMA:
            SET_OSD_STATE(_MENU_HOTKEY_GAMMA_MODE);                   
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(_WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_0, _STRING_GAMMA, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (_STRING_GAMMA_OFF + GET_OSD_GAMMA()), _ITEM_ADJUST_COLOR, _ENGLISH);
            break;
        
        case _HOTKEY_AMB:
#if(_BEACON_OSD_AMB == _ON)            
            SET_OSD_STATE(_MENU_HOTKEY_AMB_MODE);                   
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(_WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_0, _STRING_AMB_LIGHT, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (_STRING_AMB_OFF + GET_OSD_BACKGROUND_LIGHT_MODE()), _ITEM_ADJUST_COLOR, _ENGLISH);	
#endif
            break;
        
        case _HOTKEY_KVM:
            SET_OSD_STATE(_MENU_HOTKEY_KVM_MODE);                   
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(_WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_0, _STRING_KVM, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());

            g_usAdjustValue =(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO ? SysSourceGetInputPort() : GET_OSD_INPUT_PORT_OSD_ITEM());
DebugMessageUart("_HOTKEY_KVM", g_usAdjustValue);
DebugMessageUart("_HOTKEY_", SysSourceGetInputPort);

#if(_PCB_TYPE == _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP)
            // Only Support DP&DVI
#endif
            if(((g_usAdjustValue == _OSD_INPUT_D0)||(g_usAdjustValue == _OSD_INPUT_D2)))
            {
                OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (_STRING_A0_PORT + g_usAdjustValue), _ITEM_ADJUST_COLOR, _ENGLISH);	
            }
            else
            {
                OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, _STRING_NO_SUPPORT, _ITEM_ADJUST_COLOR, GET_OSD_LANGUAGE());	    
            }
         
            break;

        case _HOTKEY_DEVIATION:
            SET_OSD_STATE(_MENU_HOTKEY_DEVIATION_ADJ);
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, _STRING_Execute, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _HOTKEY_USER_CALIBRATION_GAMMA:
            SET_OSD_STATE(_MENU_MESSAGE_DISPLAY);
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, _STRING_Processing_Do_Not_Operate, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break; 
				 	
        case _HOTKEY_RESET:
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, _STRING_Execute, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break; 	
    }

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();

}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyOptionMenuSwitch(BYTE ucPort)
{
    switch(ucPort)
    {

        case _HOTKEY_GAMMA:
         
            break;

        case _HOTKEY_LIGHTBOX:

            SET_OSD_LIGHTBOXMODE_STATUS(~(GET_OSD_LIGHTBOXMODE_STATUS())); 
            
            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_2, (_STRING_OFF + GET_OSD_LIGHTBOXMODE_STATUS()), COLOR(_CP_WHITE, _SUB_WIN_COLOR), GET_OSD_LANGUAGE());
            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
            {            
                //Null
            }
            else
            {
                ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            }
            OsdDispShowLightBoxMode();

            break;

    }

    RTDNVRamSaveOSDData();
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
/*
void DrawHotKeySourcePageMenuItem(BYTE ucItem,BYTE ucState)
{
    BYTE ucY;
    BYTE ucColor;
    WORD ucStringID;
	BYTE ucType = _INPUT_NO_PORT;
	
    ucY = GetSourceIndex(ucItem);
    if(ucY == _NOT_SHOW)
    	return;
    	
    //DebugMessageSystem("ucItem = ", ucItem);

    //DebugMessageSystem("Y = ", ucY);
    // get display color
    ucColor = StateColor(ucState);
    
    // draw menu item 
    ucStringID = ucItem + _STRING_A0_PORT;    
    
    OsdPropPutStringCenter(ROW(4+ucY*3), COL(0), WIDTH(g_ucOsdWidth), _PFONT_SUB_NAME, ucStringID, ucColor, (ucStringID == _STRING_AUTOSELECT_PORT)?GET_OSD_LANGUAGE(): _ENGLISH );

}

*/

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
/*void OsdDispHotKeySourceMenuIcon(BYTE ucPort)
{
    BYTE ucCol = 5;

    if(GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
    {
        OsdFuncClearOsd(ROW(6), COL(13), WIDTH(47), HEIGHT(1));
        OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_INPUT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

        // Left & Right Arrow
        OsdFontPut1Bit(ROW(3), COL(13), _iLEFT_00, COLOR(_CP_BLUE, _CP_BG));
        OsdFontPut1Bit(ROW(3) + 1, COL(13), _iLEFT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

        OsdFontPut1Bit(ROW(3), COL(62), _iRIGHT_00, COLOR(_CP_BLUE, _CP_BG));
        OsdFontPut1Bit(ROW(3) + 1, COL(62), _iRIGHT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

        if(ucPort <= _OSD_INPUT_D2)
        {
            // A0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _A0_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_A0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D0_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D1
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D1_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D2
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D2_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
        else if((ucPort > _OSD_INPUT_D2) && (ucPort <= _OSD_INPUT_D6))
        {
            // D3
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D3_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D3_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D4
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D4_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D4_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D5
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D5_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D5_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D6
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D6_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D6_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
        else
        {
            // D7
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D7_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D7_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D8
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D8_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D8_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // auto
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_INPUT_AUTO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutStringCenter(ROW(6), COL(ucCol + (12 * 3)), WIDTH(7), _PFONT_PAGE_1, _STRING_AUTOSELECT_PORT, COLOR(_CP_BLUE, _CP_BG), GET_OSD_LANGUAGE());

            // None
            OsdFuncClearOsd(ROW(2), COL(ucCol + (12 * 4)), WIDTH(12), HEIGHT(4));
        }
    }
}*/

#if 0
//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuSwitch(BYTE ucPort)
{
    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(0), COL(3 + (12 * ((ucPort % 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
}


#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispShowLightBoxMode(void)
{	               
    //DebugMessageUart("Set LightBox:", GET_OSD_LIGHTBOXMODE_STATUS());
    if(GET_OSD_LIGHTBOXMODE_STATUS() == _ON)
    {
        if(_LIGHTBOX_MODE_LEFT == UserCommonNVRamGetSystemData(_LIGHTBOX_MODE_TYPE))
        {
            //_Left;
            // Background window
        }
        else if(_LIGHTBOX_MODE_RIGHT == UserCommonNVRamGetSystemData(_LIGHTBOX_MODE_TYPE))
        {
            //_Right;
            // Background window
        }
        else
        {
			//_FULL;
            // Background window
        }
        ScalerDDomainBackgroundEnable(_ENABLE);
        ScalerDDomainBackgroundSetColor(255, 255, 255);

        UserAdjustBacklightDuty(_BACKLIGHT_MAX);
    }
    else
    {
        if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
    	{
            ScalerDDomainBackgroundEnable(_DISABLE);
            ScalerDDomainBackgroundSetColor(0, 0, 0);
            //SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
    	}
        else
    	{
            ScalerDDomainBackgroundSetColor(0, 0, 0);
    	}  
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage)
{
    OsdDispDisableOsd();
    //OsdFuncDisableOsd();

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    if(enumMessage == _OSD_DISP_KEY_LOCK_MSG)
    {
        OsdFuncApplyMap(WIDTH(_OSD_MSG_MENU_WIDTH/2), HEIGHT(_OSD_MSG_MENU_HEIGHT-2), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MSG_MENU_HEIGHT-2), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
    }
    else
    {
        OsdFuncApplyMap(WIDTH(_OSD_MSG_MENU_WIDTH), HEIGHT(_OSD_MSG_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MSG_MENU_HEIGHT), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
    }

#if 0//(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    if(enumMessage == _OSD_DISP_KEY_LOCK_MSG)
    {
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MSG_MENU_HEIGHT-2), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
    }
    else
    {
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MSG_MENU_HEIGHT), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
    }    
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth), _MAIN_WIN_COLOR);
        //OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
    }
    else
#endif
     OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight), _MAIN_WIN_COLOR);

/*
 {
        if(enumMessage == _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG)
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), g_ucOsdHeight, _CP_LIGHTBLUE);
        }
        else
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), g_ucOsdHeight, _CP_LIGHTBLUE);
        }
    }*/

    //==== Show page item =======
    switch(enumMessage)
    {
        case _OSD_DISP_NOSIGNAL_MSG:
	        OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_NO_SIGNAL, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_NOCABLE_MSG:
	        OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_NO_CABLE, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_NOSUPPORT_MSG:
	        OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_FAIL_SAFE_MODE_MSG:
	        OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_AUTO_CONFIG_MSG:

            break;
        case _OSD_DISP_INPUT_SIGNAL_MSG:
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_H_POS_CENTER, _OSD_V_POS_MAX - 2);
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            
#if(_DP_DEBUG_MSG == _ON)
            if(SysModeGetModeState() != _MODE_STATUS_ACTIVE)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(_D0_INPUT_PORT);
                OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +1), COL(0),  _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +1), COL(10),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(_D1_INPUT_PORT);
                OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START +3), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +4), COL(0), _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +4), COL(0+10),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(_D2_INPUT_PORT);
                OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START +6), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +7), COL(0),  _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +7), COL(0+10),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif
                break;
            }
#endif

            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, OsdDisplayGetSourcePortString(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, _STRING_NOW_RESOLUTION_0, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 2), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, _STRING_HFREQPCLK_0, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);


            switch(SysSourceGetSourceType())
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0), WIDTH(_OSD_MSG_MENU_WIDTH), _PFONT_PAGE_0, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_WHITE, _MAIN_WIN_COLOR), _ENGLISH);
                    OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 14), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));
                    break;
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0), WIDTH(_OSD_MSG_MENU_WIDTH), _PFONT_PAGE_0, _STRING_HDCP_MODE, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                    break;
                
#endif
             }
#if(_FREESYNC_SUPPORT == _ON)
                    if (ScalerSyncGetFREESYNCEnable() == _TRUE)
                    {
                        SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
                        SET_OSD_INFO_STRING_MODE_LENGTH(_OSD_MESSAGE_CENTER_COL_END);
                        OsdPropShowFreeSyncVFreqRange(ROW(_OSD_MESSAGE_ROW_START + 4), COL(0),WIDTH(_OSD_MSG_MENU_WIDTH),  _PFONT_PAGE_0, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                    }
#endif
#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START + 5), COL( 26), _PFONT_PAGE_0, _STRING_HDR_MODE, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), _ENGLISH);
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START + 5), COL( 26), _PFONT_PAGE_0, _STRING_FREESYNC, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), _ENGLISH);
                break;
            }
#endif
#endif
            break;

        case _OSD_DISP_AUTO_COLOR_MSG:
            // title
              break;
        case _OSD_DISP_DICOM_RESULT:
            // title
              break;
            
        case _OSD_DISP_2HOUR_REMINDER_MSG:
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+0), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_2HOUR_REMINDER_TEXT_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+3), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_2HOUR_REMINDER_TEXT_1, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;
			
        case _OSD_DISP_USE_LIFE_MSG:
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+0), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_DISPLAY_USELIFE_TEXT_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+3), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_DISPLAY_USELIFE_TEXT_1, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_POWER_SAVING_MSG:
	        OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START+1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, _STRING_POWERSAVING, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_KEY_LOCK_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, (_ICON_KEYLOCK_OFF + UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS)));
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(6), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _MAIN_WIN_COLOR);
            break;

     	case _OSD_DISP_QA_RESULT:
	        //OsdPropPutStringCenter(ROW(1), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, (GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM) ? _STRING_GAMMA_USER_TYPE_DICON : _STRING_GAMMA_USER_TYPE_GAMMA, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
       		break;
            
#if(_FREEZE_SUPPORT == _ON)
        case _OSD_DISP_DISABLE_FREEZE_MSG:
            break;
#endif
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_DISP_MST_WARNING_MSG:
            break;
#endif
        default:
            break;
    }

    if(enumMessage == _OSD_DISP_KEY_LOCK_MSG)
    {
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS() - 4, GET_OSD_VPOS() - 2);
    }
    else
    {
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))    
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_V_POS_MAX - 2,_OSD_H_POS_CENTER );
        else
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_H_POS_CENTER, _OSD_V_POS_MAX - 2);        
    }
    
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

void DrawMainPage(void)
{
    OsdDispMainMenuIcon(_ICON_MAINMENU_PAGE); 
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServiceLevelPage(void)
{
    BYTE i =0;
    OsdDispMainMenuIcon(_ICON_ADAVANCE_LEVEL_PAGE); 
    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(_OSD_MAIN_ITEM_ROW_START), COL(_OSD_MAIN_ITEM_COL_START), WIDTH(_OSD_MAIN_ITEM_SELECT_WIDTH), HEIGHT(2), _MAIN_WIN_COLOR, _OPT_STRING_SELECT_COLOR, _MAIN_WIN_COLOR);
}


#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispAutoConfigProc(void)
{
    OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);
    UserCommonAutoConfig();
    OsdDispDisableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayAutoBalanceProc(void)
{
    OsdDispDisableOsd();
    OsdDispOsdMessage(_OSD_DISP_AUTO_COLOR_MSG);

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
        {
            // Perform auto-color for RGB
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                // Calculate YPbPr gain/offset using formula
                g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                // Restore RGB gain/offset
                ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        else
        {
            // Perform auto-color for YPbPr
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_YPBPR) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#endif
    }

    OsdDispDisableOsd();
    // SET_KEYMESSAGE(_HOLD_KEY_MESSAGE);
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdReset(void)
{
    BYTE ucIndex = GET_OSD_LANGUAGE();
    
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWDDomainEnable(_FUNCTION_OFF);
#endif

    OsdDispDisableOsd();

    SET_FORCE_BACKUP_STATUS(_TRUE);    
    //UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOSDData();
    SET_FORCE_BACKUP_STATUS(_FALSE);
    
    //RTDEepromLoadOsdInputPortData();
    //RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
    RTDNVRamRestoreSixColorData();

    RTDNVRamRestoreBriCon();
    RTDNVRamRestoreBacklight();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);
        UserCommonModeSearchInitalUserAndCenterData(g_stVGAModeUserData.ucModeNumber);
        UserCommonNVRamSaveModeUserData();
    }
#endif

#if(_DP_SUPPORT == _ON)
    OsdDispResetDpCapabilitySwitch();
#endif

#if((_FREESYNC_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
    // Switch Free Sync Capability
    UserCommonInterfaceFreeSyncSupportSwitch();
#endif

    if(ucIndex != GET_OSD_LANGUAGE())
    {
        SET_OSD_LANGUAGE(ucIndex);
        RTDNVRamSaveOSDData();
    }
#if ((_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI))
    UserCommonNVRamSetSystemData(_KEY_LOCK_STATUS, _ON);   
	UserCommonNVRamSaveSystemData();
#endif    
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    // Disable HLW
    SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
    UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
#endif
    
    OsdFuncSetOsdItemFlag();
    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

    // Adjust Background Light
#if ((_PRODUCT_ID_SEL != RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80))
    UserAdjustBackgroundLightPWM();
#endif
	// Gamma2.2 reset Backlight Sensor Target
	UserAdjustRestoreBacklightSensorValue();    
    SET_OSD_STATE(_MENU_NONE);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
    UserCommonInterfaceDataExchangeAllDataReset();
#endif
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Osd Display Reset Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispResetDpCapabilitySwitch(void)
{
    // Set Aux Diff mode & Resistance Setting
    SET_DP_AUX_DIFF_MODE();

    SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

    UserCommonInterfaceDpAuxSet();

    // Switch All DP Port Dp Version
    UserCommonInterfaceDPSwitchAllPortDpVersion();

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    // Switch All DP Port Dp Edid
    UserCommonInterfaceDPSwitchAllPortEdid();
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    // Switch All DP Port Dp Lane Count Capability
    UserCommonInterfaceTypeCU3ModeAllPortCapabilitySwitch();
#endif

#if(_DP_MST_SUPPORT == _ON)
    // Switch DP Mst Capability
    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif
}
#endif

//--------------------------------------------------
// Description  : Logo showing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowLogo(void)
{
    BYTE g_ucOsdDoubleSizeBackup = GET_OSD_DOUBLE_SIZE();

    g_ucLogoTimerCounter = 0;

#if(_POWER_ON_LOGO_TYPE == _LOGO_REALTEK)
    ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    ScalerDDomainPatternGenEnable(_ENABLE);
    ScalerDDomainBackgroundEnable(_DISABLE);

    OsdFuncDisableOsd();
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
    OsdFuncApplyMap(WIDTH(_OSD_LOGOA_WIDTH/12), HEIGHT(_OSD_LOGOA_HEIGHT/18), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);

    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdFontPut1BitTable(ROW(0), COL(19), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(1), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BLUE);

#elif(_POWER_ON_LOGO_TYPE == _LOGO_BEACON)
    ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    ScalerDDomainPatternGenEnable(_ENABLE);
    ScalerDDomainBackgroundEnable(_DISABLE); 

    OsdDispDisableOsd();    
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);    
    OsdFuncApplyMap(WIDTH(_OSD_LOGOA_WIDTH/12), HEIGHT(_OSD_LOGOA_HEIGHT/18), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
#if ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
     (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM))
    SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_270);
#endif

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);  
#endif
        
    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);

    OsdFontPut1BitTable( ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    OsdFuncChangeColor1Bit(ROW(4), COL(16), WIDTH(6), HEIGHT(2), COLOR(_LOGO_CP_BLUE, _LOGO_CP_BG), _FONTFROM_0_255);

#elif(_POWER_ON_LOGO_TYPE == _LOGO_DBI)
    // (_SCALER_TYPE == _RL6432_SERIES) Display Logo cannot use PatternGenEnable and needs to use BackgroundEnable
    SET_OSD_DOUBLE_SIZE(_OFF);

    ScalerDDomainBackgroundEnable(_ENABLE); 
    ScalerDDomainBackgroundSetColor(239, 239, 239);

    OsdDispDisableOsd();
    OsdPaletteSelectPalette(_PALETTE_DBI_LOGO);
    OsdFuncApplyMap(WIDTH(_OSD_LOGOA_WIDTH/12), HEIGHT(_OSD_LOGOA_HEIGHT/18), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);	

    ScalerOsdHardwareVLC(tiOSD_REALTEK_1BIT_LOGO0, VLC_TABLE_SIZE(tiOSD_REALTEK_1BIT_LOGO0), GET_CURRENT_BANK_NUMBER(), 0x00, 0x00, _OSD_ROTATE_DEGREE_0);
    ScalerOsdSramBaseAddressSet(_OSD_A, _OSD_LOGOA_ADDRESS_ROWCOMMAND, _OSD_LOGOA_ADDRESS_CHARCOMMAND, _OSD_LOGO_FONT_BASE_ADDRESS);

    OsdFuncSet2BitIconOffset(_OSD_LOGO_2BIT_OFFSET);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 60, 30);

#elif(_POWER_ON_LOGO_TYPE == _LOGO_UNITED_IMAGING)
    ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    ScalerDDomainPatternGenEnable(_ENABLE);
    ScalerDDomainBackgroundEnable(_DISABLE); 

    OsdDispDisableOsd();    
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);    
    OsdFuncApplyMap(WIDTH(64), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);  
#endif
        
    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);

    OsdFontPut1BitTable( ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);    

#elif(_POWER_ON_LOGO_TYPE == _LOGO_MEDBOT)

    ScalerDDomainBackgroundEnable(_ENABLE); 
    ScalerDDomainBackgroundSetColor(255, 255, 255);

    OsdDispDisableOsd();
    OsdPaletteSelectPalette(_PALETTE_MEDBOT_LOGO);
    OsdFuncApplyMap(WIDTH(_OSD_LOGOA_WIDTH/12), HEIGHT(_OSD_LOGOA_HEIGHT/18), COLOR(1, 0));

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);	

    ScalerOsdHardwareVLC(tiOSD_REALTEK_1BIT_LOGO0, VLC_TABLE_SIZE(tiOSD_REALTEK_1BIT_LOGO0), GET_CURRENT_BANK_NUMBER(), 0x00, 0x00, _OSD_ROTATE_DEGREE_0);
    ScalerOsdSramBaseAddressSet(_OSD_A, _OSD_LOGOA_ADDRESS_ROWCOMMAND, _OSD_LOGOA_ADDRESS_CHARCOMMAND, _OSD_LOGO_FONT_BASE_ADDRESS);
    OsdFuncSet2BitIconOffset(_OSD_LOGO_2BIT_OFFSET);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

#endif//end of #if(_POWER_ON_LOGO_TYPE )

    OsdFuncEnableOsd();

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(16);
#endif

    SET_OSD_LOGO_ON(_ON);

    SET_OSD_DOUBLE_SIZE(g_ucOsdDoubleSizeBackup);
}

#if 0//((_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM) || (RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM))
extern BYTE DDC_INFO_BUF[64];
extern BYTE DDC_TX_BUF[64];
extern BYTE g_bAmbiSensorInitState; 
//extern BYTE DDC_NSTD_INFO_BUF[64];
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispDdcInfo(void)
{
    BYTE DDC_INFO_CNT;
    BYTE DDC_INFO_ROW = 0, DDC_INFO_COL = 0;
    BYTE DDC_TX_COL = 0;

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncDisableOsd();
    ScalerOsdWindowDisable(_OSD_WINDOW_ALL);

    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    //OsdFontVLCLoadFont(_FONT1_2BIT);
    //OsdFontVLCLoadMultiFont();

    // Background window
#if 0//(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
	{
	    OsdWindowDrawingByPixel(_MAINMENU_TITLE_WINDOW, ROW(_WIN_TITLE_ROW_START_PIXEL), COL(_WIN_TITLE_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-_WIN_TITLE_COL_START_PIXEL), HEIGHT(_WIN_TITLE_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_INFO_WINDOW, ROW(_WIN_MAIN_INFO_ROW_START_PIXEL), COL(_WIN_MAIN_INFO_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12), HEIGHT(_WIN_INFO_HEIGHT*18), _TITLE_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_MAIN_WINDOW, ROW(_WIN_MAIN_ROW_START_PIXEL), COL(_WIN_MAIN_COL_START_PIXEL), WIDTH(_WIN_MAIN_WIDTH*12), HEIGHT(_WIN_MAIN_HEIGHT*18), _MAIN_WIN_COLOR);
	    OsdWindowDrawingByPixel(_MAINMENU_SUB_WINDOW, ROW(_WIN_SUB_ROW_START_PIXEL), COL(_WIN_SUB_COL_START_PIXEL), WIDTH(g_ucOsdWidth*12-(_WIN_MAIN_WIDTH*12)), HEIGHT((g_ucOsdHeight - _WIN_INFO_HEIGHT-_WIN_TITLE_HEIGHT)*18), _SUB_WIN_COLOR);
	}
	
    //DrawMainPage();
    if(AmbiSensor_ReadLux() == _FAIL)
    {
        ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
        g_bAmbiSensorInitState = 0;
    }
   for(DDC_INFO_CNT = 0; DDC_INFO_CNT < ((DDC_INFO_BUF[_DDCCI_LENGTH]&0x7F)+3); DDC_INFO_CNT++)   //Show RX_BUF
   {
        OsdPropShowNumber(ROW(DDC_INFO_ROW), COL(DDC_INFO_COL), DDC_INFO_BUF[DDC_INFO_CNT], (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _CP_BG));
        DDC_INFO_COL = DDC_INFO_COL + 4;
   }
   for(DDC_INFO_CNT = 0; DDC_INFO_CNT < ((DDC_TX_BUF[_DDCCI_LENGTH]&0x7F)); DDC_INFO_CNT++)  //Show TX_BUF
   {
        OsdPropShowNumber(ROW(1), COL(DDC_TX_COL), DDC_TX_BUF[DDC_INFO_CNT], (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_BLUE, _CP_BG));
        DDC_TX_COL = DDC_TX_COL + 4;
   }
    OsdPropShowNumber(ROW(2), COL(0), usSensorLux, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_YELLOW, _CP_BG));
//Nonstandard DDCCI Format Data
#if 0
   DDC_INFO_COL = 0;
   for(DDC_INFO_CNT = 0; DDC_INFO_CNT < 8; DDC_INFO_CNT++)
   {
        OsdPropShowNumber(ROW(2), COL(DDC_INFO_COL), DDC_NSTD_INFO_BUF[DDC_INFO_CNT], (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG));
        DDC_INFO_COL = DDC_INFO_COL + 4;
   }
#endif
#if 0//(_STACK_SIZE_TEST == _ENABLE)
    OsdPropShowNumber(ROW(1), COL(20), g_max_sp,        (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
    OsdPropShowNumber(ROW(1), COL(24), g_EXINT0_count,  (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
    OsdPropShowNumber(ROW(1), COL(28), g_EXINT1_count,  (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
    for(pData[0] = 0; pData[0] < ((_DDCCI_RXBUF_LENGTH > 100) ? 82 : _DDCCI_RXBUF_LENGTH); pData[0]++)
	{
	    OsdPropShowNumber(ROW(4 + (pData[0]/10)), COL(20 + 4*(pData[0] % 10)), g_pucTempDdcciRxBuf[pData[0]], (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_SUB_NAME, COLOR(_CP_WHITE, _CP_BG));
	}	
#else
    DrawSubMenu(GET_OSD_STATE());           
#endif

    //OSD Position
    //OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}

#endif


#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayPixelOrbitingAction(void)
{
    if((GET_PIXEL_ORBITING_CAPABILITY() == _ON) && (GET_OSD_PIXELSHIFT_STATUS() == _TRUE))
    {
        if(g_bflagMinuteON == _TRUE)
        {
            if(GET_PIXEL_ORBITING_TIME() > 0)
            {
                GET_PIXEL_ORBITING_TIME()--;
            }
            if(GET_PIXEL_ORBITING_TIME() == 0)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_PIXEL_ORBITING_ACTION_MSG);
            }
            g_bflagMinuteON = _FALSE;
        }
    }
}
#endif
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE StateColor(BYTE State)                                                  
{                                                                            
    switch(State)                                                            
    {                                                                        
	    case _ST_NORMAL:    return _ITEM_NORMAL_COLOR;                           
	    case _ST_SELECT:    return _ITEM_SELECT_COLOR;                           
	    case _ST_ADJUST:    return _ITEM_ADJUST_COLOR;
	    case _ST_HIDDEN:	return _ITEM_HIDDEN_COLOR;
	   // case _ST_DRAW_PAGE:	return _ITEM_DRAW_PAGE_COLOR;
	    case _ST_DISABLE:                                                        
	    default:            return _ITEM_DISABLE_COLOR;                          
    }                                                                        
} 

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdSelectedUpdate(BYTE bType,BYTE ucBeginItem,BYTE ucEndItem)
{
	BYTE ucIndex;
    ucIndex = GetShowIndex(GET_OSD_STATE(),ucBeginItem,ucEndItem);


    if(ucIndex == _NOT_SHOW)
    return;

    ucIndex =ucIndex%(_OSD_ROW_NUM);

    if(bType == _STATE_CLEAR)
    {	
        ScalerOsdWindowDisable(_OSD_WIN_HIGHLIGHT_2);
    }
    else if(bType == _STATE_SELECT)
    {	
        OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_2, ROW(_OSD_MAIN_ITEM_ROW_START +( ucIndex*_OSD_ROW_STEP)), COL(_SUBITEM_COL_START), WIDTH((g_ucOsdWidth-_SUBITEM_COL_START-1)), HEIGHT(1), _OPT_SELECT_FRAME_COLOR, _OPT_STRING_NORMAL_COLOR, _OPT_SELECT_FRAME_COLOR);
    }
    else if(bType == _STATE_ADJUST)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_2, ROW(_OSD_MAIN_ITEM_ROW_START +( ucIndex*_OSD_ROW_STEP)), COL(_SUBITEM_COL_START), WIDTH((g_ucOsdWidth-_SUBITEM_COL_START-1)), HEIGHT(1), _OPT_SELECT_FRAME_COLOR, _OPT_STRING_SELECT_COLOR, _OPT_SELECT_FRAME_COLOR);
    }

}

//==============================================================================
//==============================================================================
//==============================================================================
void DrawSubMenu(WORD ucPageIndex)
{
    //ScalerTimerDelayXms(120);
	OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
    //OsdFuncOsdLine(ROW(_OSD_MAIN_ITEM_ROW_START-1), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT), _ITEM_DRAW_PAGE_COLOR, _OSD_BYTE2);
 	//DebugMessageUart("SubMenu:", ucPageIndex);

    switch(ucPageIndex)
    {
        case _MENU_IMAGE:             		     DrawImagePage();        	 break;
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
        case _MENU_QA:			                 DrawQAPage();			     break;
#endif        
        case _MENU_FUNCTION_SETTING:			 DrawFunctionSettingPage();  break;	
        case _MENU_INFO:				         DrawInfoPage();	         break;
        case _MENU_ADVANCE:				         DrawAdvancePage();          break;
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)        
        case _IMAGE_PAGE_GAMMA_USER_START:		 DrawGammaUserPage();		 break;	
#endif        
        case _IMAGE_PAGE_COLORTEMP_USER_START:	 DrawColorTempUserPage();	 break;
#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
        case _IMAGE_HYBRID_START:	             DrawHybridPage();	       break;     
#endif        
        case _IMAGE_HDR_START:	                 DrawHDRPage();	           break;     


        case _SERVICE_PAGE_1:				     DrawServicePage1();       break;
        case _SERVICE_PAGE_2:				     DrawServicePage2();       break;
        case _SERVICE_PAGE_3:				     DrawServicePage3();       break;
#if(_VGA_SUPPORT == _ON)        
        case _SERVICE_PAGE_4:				     DrawServicePage4();       break;
#endif        
        case _SERVICE_PAGE_5:				     DrawServicePage5();       break;       
        case _SERVICE_PAGE_5_OSD_START:          DrawOSDPage();            break;
        
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImagePageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _IMAGE_PCM:            DrawPCM(ucState);		        break;
		case _IMAGE_GAMMA:			DrawImageGamma(ucState);  	    break;
		case _IMAGE_DICOMALC:		DrawImageDicomALC(ucState);  	break;        
		case _IMAGE_COLOR_TEMP:		DrawImageColorTemp(ucState);	break;	
#if(_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        	
		case _IMAGE_BACKLIGHT:		DrawImageBacklight(ucState);	break;
#endif 
#if(_HDR10_SUPPORT == _ON)
    	case _IMAGE_HDR:			DrawImageHDR(ucState);	        break;
#endif        
    }

}

#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawQAPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        //ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
		case _QA_TEST_IMAGE:		DrawQATest(ucState);  	   break;
		case _QA_DEVIATION:			DrawQADeviation(ucState);  break;	
    }

}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionSettingPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
		case _FUNCTION_LANGUAGE:		DrawFunctionLanguage(ucState);  	  break;
		case _FUNCTION_INPUT:			DrawFunctionInput(ucState);		      break;	
		case _FUNCTION_AMB_LIGHT:		DrawFunctionAmbLight(ucState);		  break;
		case _FUNCTION_REPORT_MODE:		DrawFunctionReportMode(ucState);	  break;
		case _FUNCTION_2HOURS_REMINDER:	DrawFunction2hoursReminder(ucState);  break;
		case _FUNCTION_FACTORY_RESET:	DrawFunctionFactoryReset(ucState);	  break;
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawAdvancePageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);
    
    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        //ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _ADVANCED_PASSWORD:      DrawAdvancedPassword(ucState);    break;
    }
}

#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        //ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case  _GAMMA_USER_TYPE:       DrawGammaUserType(ucState);		break;
        case  _GAMMA_USER_L_MAX:      DrawGammaUserLMax(ucState);		break;
        case  _GAMMA_USER_L_MIN:      DrawGammaUserLMin(ucState);		break;
        case  _GAMMA_USER_LAMB:       DrawGammaUserLamb(ucState);		break;
        case  _GAMMA_USER_VALUE:      DrawGammaUserValue(ucState);		break;   
        case  _GAMMA_USER_SET:        DrawGammaUserSet(ucState);		break; 
    }

}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawColorTempUserPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        //ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _COLOR_TEMP_USER_R:        DrawColorTempUserR(ucState);	break;
        case _COLOR_TEMP_USER_G:        DrawColorTempUserG(ucState);	break;
        case _COLOR_TEMP_USER_B:		DrawColorTempUserB(ucState);	break;
    }

}

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHybridPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
		case _IMAGE_HYBRID_GRAY_CURVE:		DrawHybridGrayCurve(ucState);	break;	
		case _IMAGE_HYBRID_COLOR_CURVE:		DrawHybridColorCurve(ucState);  break;
    } 

}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHDRPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }

#if(_HDR10_SUPPORT == _ON)
    switch(ucItem)
    {
		case _IMAGE_HDR_MODE:			    DrawHDR(ucState);		    break;	
		case _IMAGE_HDR_DARK_ENHANCE:		DrawDarkEnhance(ucState);   break;
		case _IMAGE_HDR_SHARP_ENHANCE:		DrawSharpEnhance(ucState);  break;
		case _IMAGE_HDR_CONTRAST:			DrawHdrContrast(ucState);   break;
        
    } 
#endif
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImagePage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_IMAGE_PAGE_START;i<=_IMAGE_PAGE_END;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawImagePageMenuItem(i,   ucState);
    }

}
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawQAPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_QA_PAGE_START;i<=_QA_PAGE_END ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawQAPageMenuItem(i,  ucState);
    }

}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionSettingPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_FUNCTION_SETTING_PAGE_START;i<=_FUNCTION_SETTING_PAGE_END;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawFunctionSettingPageMenuItem(i,  ucState);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawInfoPage(void)
{

    BYTE ucColor = _ITEM_DISABLE_COLOR;

    OsdPropPutString(ROW(0*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_INFO_PRODUCT_ID, ucColor,  _ENGLISH);
    OsdPropPutString(ROW(0*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START + 4), _PFONT_PAGE_1,_STRING_PRODUCT_ID, ucColor,  _ENGLISH);

    OsdPropPutString(ROW(1*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_FIRMWARE_VERSION, ucColor,  _ENGLISH);

    OsdPropPutString(ROW(2*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1, _STRING_INFO_PANEL_LUMIN, ucColor, GET_OSD_LANGUAGE());
    OsdPropPutString(ROW(2*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START + 6), _PFONT_PAGE_1, _STRING_INFO_PANEL_LUMINANCE, ucColor, _ENGLISH);
    OsdPropPutString(ROW(2*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_INFO_THI), _PFONT_PAGE_1,_STRING_INFO_TIME, ucColor,  GET_OSD_LANGUAGE());
    //OsdPropShowNumber(ROW(2*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_INFO_THI + 5), GET_SYSTEM_RUN_TIME_HOUR(), (_LEFT_TYPE | _FORCE_SHOW_NUMBER_OFF | _SHOW_6), _PFONT_PAGE_1, ucColor);
    OsdPropPutString(ROW(2*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_INFO_THI + 9), _PFONT_PAGE_1,_STRING_INFO_USE_TIME, ucColor,  _ENGLISH);


    OsdFuncClearOsd(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), WIDTH(_OSD_MAIN_MENU_WIDTH -_WIN_MAIN_WIDTH), HEIGHT(8));
    OsdPropPutString(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_WINDOW_1, ucColor,  GET_OSD_LANGUAGE());
    OsdPropPutString(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_INFO_SEC), _PFONT_PAGE_1, OsdDisplayGetSourcePortString(), ucColor, _ENGLISH);
    if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
    {
        OsdPropPutString(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_INFO_THI), _PFONT_PAGE_1, _STRING_NOW_RESOLUTION_0, ucColor, _ENGLISH);
    }	
    else
    {
        OsdPropPutString(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_INFO_THI), _PFONT_PAGE_1, _STRING_NO_SIGNAL, ucColor, _ENGLISH);
    }
  
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawAdvancePage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_ADVANCED_PAGE_START;i<=_ADVANCED_PAGE_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawAdvancePageMenuItem(i,  ucState);
    }

}

#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_IMAGE_PAGE_GAMMA_USER_START;i<=_IMAGE_PAGE_GAMMA_USER_END ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawGammaUserMenuItem(i,  ucState);
    }

}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawColorTempUserPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_IMAGE_PAGE_COLORTEMP_USER_START;i<=_IMAGE_PAGE_COLORTEMP_USER_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawColorTempUserPageMenuItem(i,  ucState);
    }

}

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHybridPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_IMAGE_HYBRID_START;i<=_IMAGE_HYBRID_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        DrawHybridPageMenuItem(i,  ucState);
    }

}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHDRPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_IMAGE_HDR_START;i<=_IMAGE_HDR_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        DrawHDRPageMenuItem(i,  ucState);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawPCM(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_PCM,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(y == _NOT_SHOW)
        return;
     
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_PCM, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_IMAGE_PCM, GET_OSD_PCM_STATUS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImageGamma(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_GAMMA,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_GAMMA, ucColor,  GET_OSD_LANGUAGE());
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        OsdDispSliderAndNumber(_IMAGE_GAMMA, GET_OSD_PCM_INPUTGAMMA(),y,ucColor);
    }
    else
    {
        OsdDispSliderAndNumber(_IMAGE_GAMMA, GET_OSD_GAMMA(),y,ucColor);
    }        
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImageDicomALC(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_DICOMALC,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_ALC, ucColor,  _ENGLISH);
    OsdDispSliderAndNumber(_IMAGE_DICOMALC, GET_OSD_DICOMALC(),y,ucColor);

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImageColorTemp(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_COLOR_TEMP,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_COLOR_TEMP, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_IMAGE_COLOR_TEMP, GET_COLOR_TEMP_TYPE(),y,ucColor);
}

#if(_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImageBacklight(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_BACKLIGHT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_BACKLIGJT, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_IMAGE_BACKLIGHT,  GET_OSD_BACKLIGHT(),y,ucColor);
}
#endif
#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawImageHDR(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HDR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_HDR_MODE, ucColor,  GET_OSD_LANGUAGE());
}
#endif
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawQATest(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_QA_TEST_IMAGE,_QA_PAGE_START,_QA_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);

    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_TEST_IMAGE, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_QA_TEST_IMAGE, GET_OSD_FPGA_TEST_IMAGE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawQADeviation(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_QA_DEVIATION,_QA_PAGE_START,_QA_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_DEVIATION, ucColor,  GET_OSD_LANGUAGE());
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionLanguage(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_FUNCTION_LANGUAGE,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_LANGUAGE, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_FUNCTION_LANGUAGE, GET_OSD_LANGUAGE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionInput(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_FUNCTION_INPUT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_INPUT, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_FUNCTION_INPUT, GET_OSD_INPUT_PORT_OSD_ITEM(),y,ucColor);

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionAmbLight(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_FUNCTION_AMB_LIGHT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_AMB_LIGHT, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_FUNCTION_AMB_LIGHT, GET_OSD_BACKGROUND_LIGHT_MODE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionReportMode(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_FUNCTION_REPORT_MODE,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_REPORT_MODE, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_FUNCTION_REPORT_MODE, GET_OSD_READING_REPORT_MODE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunction2hoursReminder(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_FUNCTION_2HOURS_REMINDER,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_2HOURS_REMINDER, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_FUNCTION_2HOURS_REMINDER, GET_OSD_2HOURS_TIPS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawFunctionFactoryReset(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_FUNCTION_FACTORY_RESET,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_FACTORY_RESET, ucColor,  GET_OSD_LANGUAGE());
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawAdvancedPassword(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ADVANCED_PASSWORD,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
    if(y == _NOT_SHOW)
        return;
	
      y =y%(_OSD_ROW_NUM);
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_PASSWORD, ucColor,  GET_OSD_LANGUAGE());
}

#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserType(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GAMMA_USER_TYPE,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_TYPE, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_GAMMA_USER_TYPE, GET_OSD_LUT_USER_TYPE(),y,ucColor);

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserLMax(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GAMMA_USER_L_MAX,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_L_MAX, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_GAMMA_USER_L_MAX, GET_OSD_LUT_USER_L_MAX(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserLMin(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GAMMA_USER_L_MIN,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_L_MIN, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_GAMMA_USER_L_MIN, GET_OSD_LUT_USER_L_MIN(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserLamb(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GAMMA_USER_LAMB,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_LAMB, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_GAMMA_USER_LAMB, GET_OSD_LUT_USER_LAMB(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserValue(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GAMMA_USER_VALUE,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_VALUE, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_GAMMA_USER_VALUE, GET_OSD_LUT_USER_VALUE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGammaUserSet(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GAMMA_USER_SET,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_SET, ucColor,  GET_OSD_LANGUAGE());
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawColorTempUserR(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_COLOR_TEMP_USER_R,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_TEMP_USER_R, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawColorTempUserG(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_COLOR_TEMP_USER_G,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_TEMP_USER_G, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawColorTempUserB(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_COLOR_TEMP_USER_B,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END );
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_TEMP_USER_B, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B(),y,ucColor);
}

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHybridGrayCurve(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HYBRID_GRAY_CURVE,_IMAGE_HYBRID_START,_IMAGE_HYBRID_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_HYBRID_GRAY, ucColor,  GET_OSD_LANGUAGE());
    OsdDispSliderAndNumber(_IMAGE_HYBRID_GRAY_CURVE,  GET_OSD_FPGA_GRAY_GAMMA(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHybridColorCurve(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HYBRID_COLOR_CURVE,_IMAGE_HYBRID_START,_IMAGE_HYBRID_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_HYBRID_COLOR, ucColor,  GET_OSD_LANGUAGE());
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_OSD_ITEM_VALUE_COL), _PFONT_PAGE_1,_STRING_GAMMA1_8, _ITEM_DISABLE_COLOR, _ENGLISH);

}
#endif
#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHDR(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HDR_MODE,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_HDR_MODE, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_IMAGE_HDR_MODE, GET_OSD_HDR_MODE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDarkEnhance(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HDR_DARK_ENHANCE,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_DARK_ENHANCE, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_IMAGE_HDR_DARK_ENHANCE, GET_OSD_DARK_ENHANCE_STATUS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawSharpEnhance(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HDR_SHARP_ENHANCE,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_SHARPNESS_ENHANCE, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_IMAGE_HDR_SHARP_ENHANCE, GET_OSD_HDR_SHARPNESS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawHdrContrast(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_IMAGE_HDR_CONTRAST,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_HDR_CONTRAST, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_IMAGE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST(),y,ucColor);
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void PCMAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_PCM,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_IMAGE_PCM_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

    OsdFuncColorPcmAdjust();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GammaAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_GAMMA ,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_IMAGE_GAMMA_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        OsdFuncColorPcmAdjust();
    }
    else
    {
#if(_GAMMA_FUNCTION == _ON)
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

        if(GET_OSD_GAMMA() != _GAMMA_OFF)
        {
            UserAdjustGamma(GET_OSD_GAMMA());
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        }
#endif
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DicomALCAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_DICOMALC ,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_IMAGE_DICOMALC_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ColorTempAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_COLOR_TEMP,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    OsdDispSliderAndNumber(_IMAGE_COLOR_TEMP_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

    //RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
#if(_CONTRAST_SUPPORT == _ON)
    //UserAdjustContrast(GET_OSD_CONTRAST());
#endif

    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        OsdFuncColorPcmAdjust();
    }
    else
    {
#if(_GAMMA_FUNCTION == _ON)
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

        if(GET_OSD_GAMMA() != _GAMMA_OFF)
        {
            UserAdjustGamma(GET_OSD_GAMMA());
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        }
#endif
    }
}
#if(_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void BackLightAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_BACKLIGHT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;

    if(GET_COLOR_TEMP_TYPE() == _CT_SRGB)
         return;
   
    OsdDispSliderAndNumber(_IMAGE_BACKLIGHT_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

    UserAdjustBacklight(GET_OSD_BACKLIGHT());
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SAVE_USER2_DATA);    
}
#endif

#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void TestImageAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_QA_TEST_IMAGE ,_QA_PAGE_START,_QA_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_QA_TEST_IMAGE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void LanguageAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_FUNCTION_LANGUAGE,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_FUNCTION_LANGUAGE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void FunctionInputAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_FUNCTION_INPUT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_FUNCTION_INPUT_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void AmbLightAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_FUNCTION_AMB_LIGHT ,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_FUNCTION_AMB_LIGHT_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
#if ((_PRODUCT_ID_SEL != RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80))
    UserAdjustBackgroundLightPWM();
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ReportModeAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_FUNCTION_REPORT_MODE,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_FUNCTION_REPORT_MODE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void TwohoursReminderAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_FUNCTION_2HOURS_REMINDER,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_FUNCTION_2HOURS_REMINDER_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GammaUserTypeAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_GAMMA_USER_TYPE,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_GAMMA_USER_TYPE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GammaUserLMaxAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_GAMMA_USER_L_MAX,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END );
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_GAMMA_USER_L_MAX_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GammaUserLMinAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_GAMMA_USER_L_MIN,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_GAMMA_USER_L_MIN_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GammaUserLambAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_GAMMA_USER_LAMB,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_GAMMA_USER_LAMB_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GammaUserValueAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_GAMMA_USER_VALUE,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_GAMMA_USER_VALUE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ColorTempUserRAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_COLOR_TEMP_USER_R,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_COLOR_TEMP_USER_R_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ColorTempUserGAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_COLOR_TEMP_USER_G,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_COLOR_TEMP_USER_G_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ColorTempUserBAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_COLOR_TEMP_USER_B,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_COLOR_TEMP_USER_B_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif
}

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HybridGrayCurveAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_HYBRID_GRAY_CURVE,_IMAGE_HYBRID_START,_IMAGE_HYBRID_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_IMAGE_HYBRID_GRAY_CURVE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    UserAdjustFPGAColorAdaptiveHandler(_ON);
#endif
    
}
#endif

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HdrModeAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_HDR_MODE,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_IMAGE_HDR_MODE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

#if(_ULTRA_HDR_SUPPORT == _ON)
    UserCommonHDRAdjust(_HDR_FLOW_COLOR_PROC_INITIAL);
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DarkEnhanceAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_HDR_DARK_ENHANCE,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_IMAGE_HDR_DARK_ENHANCE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void SharpEnhanceAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_HDR_SHARP_ENHANCE,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_IMAGE_HDR_SHARP_ENHANCE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HdrContrastAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_IMAGE_HDR_CONTRAST,_IMAGE_HDR_START,_IMAGE_HDR_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_IMAGE_HDR_CONTRAST_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

}
#endif

//==============================================================================
//======================== Service  Page  Start ================================
//==============================================================================

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage1MenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _DISPLAY_ROTATE:              DrawDisplayRotate(ucState);		break;
        case _ASPECT_RATIO:                DrawDisplayAspect(ucState);      break;
           
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage2MenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _DP_VERSION:               DrawDPVersion(ucState);	       break;
        case _DP_MST:                   DrawDPMST(ucState);		       break;
        case _DP_CLONE:                 DrawDPClone(ucState);		   break;        
        case _DP_RESOLUTION:            DrawDPResolution(ucState);	   break;
    
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage3MenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _UNIFORMITY:               DrawUniformity(ucState);	 break;
#if (_SDR_TO_HDR_SUPPORT == _ON)        
        case _SDR:                      DrawSDR(ucState);            break;
#endif
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage5MenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
        case _AMBIENT_SENSOR:          DrawAmbientSensor(ucState);	  break;    
        case _BODY_SENSOR:             DrawBodyInduction(ucState);	  break;
        case _GRAVITY_SENSOR:          DrawGravitySensor(ucState);	  break;
        case _BACKLIGHT_SENSOR:        DrawBacklightSensor(ucState);  break;        
        case _ENERGY_SAVING:           DrawEnergySaving(ucState);	  break;
        case _OSD:                     DrawOSD(ucState);		      break;
                
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawOSDPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
       ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }

    switch(ucItem)
    {
        case _OSD_TIME:              DrawOsdTime(ucState);		break;
        case _OSD_POSITION:          DrawOsdPosition(ucState);	break;
        case _OSD_ROTATE:            DrawOsdRotate(ucState);	break;
        case _USE_LIFE_REMINDER:     DrawUseLife(ucState);      break;
        
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage1(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_SERVICE_PAGE_1_START;i<=_SERVICE_PAGE_1_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawServicePage1MenuItem(i,  ucState);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage2(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_SERVICE_PAGE_2_START;i<=_SERVICE_PAGE_2_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawServicePage2MenuItem(i,  ucState);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage3(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_SERVICE_PAGE_3_START;i<=_SERVICE_PAGE_3_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawServicePage3MenuItem(i,  ucState);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage5(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_SERVICE_PAGE_5_START;i<=_SERVICE_PAGE_5_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawServicePage5MenuItem(i,  ucState);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawOSDPage(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_SERVICE_PAGE_5_OSD_START;i<=_SERVICE_PAGE_5_OSD_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawOSDPageMenuItem(i,  ucState);
    }

}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawVGAColor(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ANALOG_PAGE_AUTO_COLOR_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;
	
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1, _STRING_COLOR_SWITCH_COLOR, ucColor, _ENGLISH);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawVGAAuto(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ANALOG_PAGE_AUTO_ADJUST_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_AUTO_ADJUST, ucColor, GET_OSD_LANGUAGE());

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawVGAHPostion(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ANALOG_PAGE_H_POSTION_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_HPOS, ucColor,  GET_OSD_LANGUAGE());
	
	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_H_POSTION_ITEM, GET_VGA_MODE_ADJUST_H_POSITION(),y,ucColor);
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawVGAVPostion(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ANALOG_PAGE_V_POSTION_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_VPOS, ucColor, GET_OSD_LANGUAGE());
	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_V_POSTION_ITEM, GET_VGA_MODE_ADJUST_V_POSITION(),y,ucColor);
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawVGAClock(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ANALOG_PAGE_CLOCK_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_CLOCK, ucColor,  GET_OSD_LANGUAGE());
	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_CLOCK_ITEM, GET_VGA_MODE_ADJUST_CLOCK(),y,ucColor);
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawVGAPhase(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ANALOG_PAGE_PHASE_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_PHASE, ucColor, GET_OSD_LANGUAGE());
	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_PHASE_ITEM, GET_VGA_MODE_ADJUST_PHASE(),y,ucColor);
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawAnalogPageMenuItem(BYTE ucItem,BYTE ucState)
{
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucItem);

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }
    
    switch(ucItem)
    {
    	case _ANALOG_PAGE_AUTO_COLOR_ITEM:			DrawVGAColor(ucState);     	break;    
    	case _ANALOG_PAGE_AUTO_ADJUST_ITEM:			DrawVGAAuto(ucState);     	break;
    	case _ANALOG_PAGE_H_POSTION_ITEM:			DrawVGAHPostion(ucState);   break;
    	case _ANALOG_PAGE_V_POSTION_ITEM:			DrawVGAVPostion(ucState);   break;
    	case _ANALOG_PAGE_CLOCK_ITEM:				DrawVGAClock(ucState);     	break;
    	case _ANALOG_PAGE_PHASE_ITEM:				DrawVGAPhase(ucState);     	break;

    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawServicePage4(void)
{
    BYTE i;
    BYTE ucState;
    
    for(i=_ANALOG_PAGE_START;i<=_ANALOG_PAGE_END  ;i++)
    {
        if(i == GET_OSD_STATE())
        {
            ucState = _ST_SELECT;
        }
        else
        {
            ucState = _ST_NORMAL;
        }
        
        DrawAnalogPageMenuItem(i,  ucState);
    }

}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDisplayRotate(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_DISPLAY_ROTATE,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
    if(y == _NOT_SHOW)
        return;
   
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_DISP_ROTATE, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_DISPLAY_ROTATE, GET_OSD_DISP_ROTATE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDisplayAspect(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ASPECT_RATIO,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
    if(y == _NOT_SHOW)
        return;
   
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_ASPECT, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_ASPECT_RATIO, GET_OSD_ASPECT_RATIO_TYPE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDPVersion(BYTE State)
{
    BYTE ucY,ucColor;
    ucY = GetShowIndex(_DP_VERSION,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(ucY == _NOT_SHOW)
        return;

    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(ucY*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_DP, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_DP_VERSION, GET_OSD_DP_D0_VERSION(),ucY,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDPMST(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_DP_MST,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_MST, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_DP_MST, GET_OSD_DP_MST(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDPClone(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_DP_CLONE,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_CLONE, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_DP_CLONE, GET_OSD_CLONE_MODE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDPResolution(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_DP_RESOLUTION,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_DP_RESOLUTION, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_DP_RESOLUTION,UserCommonNVRamGetSystemData(_EDID_D0_SELECT),y,ucColor);

}

/*
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawDSC(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_DP_HDMI_DSC,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_DSC, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        OsdDispSliderAndNumber(_DP_HDMI_DSC, GET_OSD_1P_DSC_PORT(),y,ucColor);
    }
    else
    {
        OsdDispSliderAndNumber(_DP_HDMI_DSC, GET_OSD_DSC_PORT(),y,ucColor);
    }
}
*/

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawUniformity(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_UNIFORMITY,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
    if(y == _NOT_SHOW)
        return;
    
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_UNIFORMITY, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_UNIFORMITY,GET_OSD_PANEL_UNIFORMITY(),y,ucColor);
}

#if (_SDR_TO_HDR_SUPPORT == _ON)        
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawSDR(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_SDR,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
    if(y == _NOT_SHOW)
        return;
	
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_SDR, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_SDR, GET_OSD_SDR_TO_HDR(),y,ucColor);
}
#endif

void DrawAmbientSensor(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_AMBIENT_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;
   
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_AMBIENT_SENSOR, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_AMBIENT_SENSOR, GET_OSD_AMBIENTLIGHT_SENSOR_STATUS() ,y,ucColor);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawBodyInduction(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_BODY_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;
	
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_BODY_INDUCTION, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_BODY_SENSOR, GET_OSD_DISTANCE_SENSOR_STATUS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawGravitySensor(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_GRAVITY_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;
	
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_GRAVITY_SENSOR, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_GRAVITY_SENSOR, GET_OSD_GRAVITY_SENSOR_STATUS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawBacklightSensor(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_BACKLIGHT_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;
	
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_BACKLIGHT_SENSOR, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_BACKLIGHT_SENSOR, GET_OSD_BACKLIGHT_SENSOR_STATUS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawEnergySaving(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_ENERGY_SAVING,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_ENERGY_SAVING, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_ENERGY_SAVING, GET_OSD_POWER_SAVING_MODE(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawOSD(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_OSD,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_OSD, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawOsdTime(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_OSD_TIME,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_OSD_TIME, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_OSD_TIME, GET_OSD_TIME_OUT(),y,ucColor);
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawOsdPosition(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_OSD_POSITION,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STIRNG_POSITION, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_OSD_POSITION, GET_OSD_POSTION(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawOsdRotate(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_OSD_ROTATE,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(y == _NOT_SHOW)
        return;
	
    // get display color
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_OSD_ROTATE, ucColor, (GET_OSD_LANGUAGE()==_CHINESE_S)? _CHINESE_S: _ENGLISH);
    OsdDispSliderAndNumber(_OSD_ROTATE, GET_OSD_ROTATE_STATUS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DrawUseLife(BYTE State)
{
    BYTE y,ucColor;
    y = GetShowIndex(_USE_LIFE_REMINDER,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(y == _NOT_SHOW)
        return;
	
    ucColor = StateColor(State);
    
    OsdPropPutString(ROW(y*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USELIFE, ucColor, _ENGLISH);
    OsdDispSliderAndNumber(_USE_LIFE_REMINDER, GET_OSD_PANEL_USELIFE_TIPS(),y,ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RotateAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_DISPLAY_ROTATE ,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
    if(ucY == _NOT_SHOW)
        return;
    
    OsdDispSliderAndNumber(_DISPLAY_ROTATE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void AspectAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_ASPECT_RATIO,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_ASPECT_RATIO_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------

void DPVersionAdjust(void)
{
    BYTE ucY;    

    ucY = GetShowIndex(_DP_VERSION,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(ucY == _NOT_SHOW)
        return;
        
    OsdDispSliderAndNumber(_DP_VERSION_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DPMSTAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_DP_MST,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_DP_MST_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DPCloneAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_DP_CLONE,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_DP_CLONE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void DPResolutionAdjust(void)
{
    BYTE ucY;    

    ucY = GetShowIndex(_DP_RESOLUTION,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
    if(ucY == _NOT_SHOW)
        return;
        
    OsdDispSliderAndNumber(_DP_RESOLUTION_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

#if (_SDR_TO_HDR_SUPPORT == _ON)        
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void SDRAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_SDR,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_SDR_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
#if(_SDR_TO_HDR_SUPPORT == _ON)
    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());
#endif

}
#endif


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UniformityAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_UNIFORMITY,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_UNIFORMITY_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void AmbientSensorAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_AMBIENT_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_AMBIENT_SENSOR_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void BodySensorAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_BODY_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_BODY_SENSOR_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void GravitySensorAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_GRAVITY_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_GRAVITY_SENSOR_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void BacklightSensorEnAdjust(void)
{
    BYTE y;
    y = GetShowIndex(_BACKLIGHT_SENSOR,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(y == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_BACKLIGHT_SENSOR_ADJ, g_usAdjustValue, y, _ITEM_NORMAL_COLOR);

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void EnergySavingAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_ENERGY_SAVING,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_ENERGY_SAVING_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdTimeAdjust(void)
{
    BYTE ucY;    

    ucY = GetShowIndex(_OSD_TIME,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(ucY == _NOT_SHOW)
        return;
        
    OsdDispSliderAndNumber(_OSD_TIME_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdPositionAdjust(void)
{
    BYTE ucY;    

    ucY = GetShowIndex(_OSD_POSITION,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(ucY == _NOT_SHOW)
        return;
        
    OsdDispSliderAndNumber(_OSD_POSITION_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

    if(g_usAdjustValue == _OSD_POSITON_LT)
    {
        SET_OSD_HPOS(0);
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
        SET_OSD_VPOS(0);
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
        SET_OSD_VPOS(2);
#endif
    }
    else if(g_usAdjustValue == _OSD_POSITON_RT)
    {
        SET_OSD_HPOS(100);
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
        SET_OSD_VPOS(0);
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
        SET_OSD_VPOS(2);
#endif
    }
    else if(g_usAdjustValue == _OSD_POSITON_LB)
    {
        SET_OSD_HPOS(0);
        SET_OSD_VPOS(100);
    }
    else if(g_usAdjustValue == _OSD_POSITON_MIDDLE)
    {
        SET_OSD_HPOS(50);
        SET_OSD_VPOS(50);
    }
    else //if(g_usAdjustValue == _OSD_POSITON_RB)
    {
        SET_OSD_HPOS(100);
        SET_OSD_VPOS(100);
    }
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdRotateAdjust(void)
{
    BYTE ucY;

    ucY = GetShowIndex(_OSD_ROTATE,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(ucY == _NOT_SHOW)
        return;
        
    OsdDispSliderAndNumber(_OSD_ROTATE_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

	#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
    OsdDispOsdRotateSwitch();
	#endif

	//SET_OSD_STATE_PREVIOUS(_MENU_NONE);
	SET_OSD_STATE(_OSD_ROTATE_ADJ);
    
    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UseLifeAdjust(void)
{
    BYTE ucY;
    ucY = GetShowIndex(_USE_LIFE_REMINDER,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
    if(ucY == _NOT_SHOW)
        return;

    OsdDispSliderAndNumber(_USE_LIFE_REMINDER_ADJ, g_usAdjustValue, ucY, _ITEM_NORMAL_COLOR);

}
   
#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void VGAHPosAdjust(void)
{
    BYTE y;
    y = GetShowIndex(_ANALOG_PAGE_H_POSTION_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_H_POS_ADJUST, GET_VGA_MODE_ADJUST_H_POSITION(),y,_ITEM_ADJUST_COLOR);
    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void VGAVPosAdjust(void)
{
    BYTE y;
    y = GetShowIndex(_ANALOG_PAGE_V_POSTION_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_V_POS_ADJUST, GET_VGA_MODE_ADJUST_V_POSITION(),y,_ITEM_ADJUST_COLOR);
    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void VGAClockAdjust(void)
{
    BYTE y;
    y = GetShowIndex(_ANALOG_PAGE_CLOCK_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_CLOCK_ADJUST, GET_VGA_MODE_ADJUST_CLOCK(),y,_ITEM_ADJUST_COLOR);
    //UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
	#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void VGAPhaseAdjust(void)
{
    BYTE y;
    y = GetShowIndex(_ANALOG_PAGE_PHASE_ITEM,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

	#if(_VGA_SUPPORT == _ON)
    OsdDispSliderAndNumber(_ANALOG_PAGE_PHASE_ADJUST, GET_VGA_MODE_ADJUST_PHASE(),y,_ITEM_ADJUST_COLOR);
    //UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
	#endif
}
#endif

//==============================================================================
//======================= Service  Page  End ===================================
//==============================================================================


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HotkeyGammaAdjust(void)
{
    OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_INFO_WIDTH), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), HEIGHT(2));
    SET_OSD_GAMMA( OsdFuncCheckGammaAdjustType(g_usAdjustValue));
    g_usAdjustValue = GET_OSD_GAMMA();
    OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_INFO_WIDTH), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (g_usAdjustValue + _STRING_GAMMA_OFF), _ITEM_ADJUST_COLOR, _ENGLISH);	

#if(_GAMMA_FUNCTION == _ON)
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserAdjustGamma(GET_OSD_GAMMA());
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
    }
#endif
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

}
#if(_BEACON_OSD_AMB == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HotkeyAmbAdjust(void)
{
    OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_INFO_WIDTH), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), HEIGHT(2));
    SET_OSD_BACKGROUND_LIGHT_MODE(OsdDisplayDetOverRange(g_usAdjustValue, _AMB_LIGHT_AMOUNT, _AMB_LIGHT_OFF, _ON));
    g_usAdjustValue = GET_OSD_BACKGROUND_LIGHT_MODE();    
    OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_INFO_WIDTH), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (_STRING_AMB_OFF + g_usAdjustValue), _ITEM_ADJUST_COLOR, _ENGLISH);	
#if ((_PRODUCT_ID_SEL != RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80))
    UserAdjustBackgroundLightPWM();
#endif
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HotkeyKvmAdjust(void)
{
    OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_INFO_WIDTH), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), HEIGHT(2));
DebugMessageUart("KVMM", GET_OSD_INPUT_PORT_OSD_ITEM());
    SET_OSD_INPUT_PORT_OSD_ITEM(OsdFuncCheckInputPortType(g_usAdjustValue));
DebugMessageUart("KVMM+", GET_OSD_INPUT_PORT_OSD_ITEM());
    
    g_usAdjustValue = GET_OSD_INPUT_PORT_OSD_ITEM();
    OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_INFO_WIDTH), WIDTH(g_ucOsdWidth- _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (_STRING_A0_PORT + g_usAdjustValue), _ITEM_ADJUST_COLOR, _ENGLISH);	

    switch(g_usAdjustValue)
                    //switch(GET_OSD_INPUT_PORT_OSD_ITEM())
                    {
                        case _OSD_INPUT_AUTO: // auto
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
                            if(GET_OSD_DP_MST() != _MST_OFF)
                            {
                                SET_OSD_DP_MST(_MST_OFF);
                            }
#endif
                            SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
                            {
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;

                        case _OSD_INPUT_A0: // A0
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_A0_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }
                            break;
#else
                            return;
#endif


                        case _OSD_INPUT_D0: // D0
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D0_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D1:    // D1
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D1_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D2:    // D2
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D2_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D3:    // D3
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D3_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D4:    // D4
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D4_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D5:    // D5
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D5_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D6:    // D6
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D6_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }
                            break;
#else
                            return;
#endif

                        default:
                            break;
                    }

#if(_DP_MST_SUPPORT == _ON)
                    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                    RTDNVRamSaveOSDData();
#endif
}
#if((_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)&&\
    (_PRODUCT_ID_SEL != RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))    

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HotkeyColorMonoAdjust(void)
{    
    if(GET_OSD_SATURATION() == _SATURATION_CENTER)
    {
        g_usAdjustValue = 0;
    }
    else
    {
        g_usAdjustValue = 50;
    }

    SET_OSD_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));

#if(_GLOBAL_HUE_SATURATION == _ON)
    UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif

    OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), HEIGHT(2));
    OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, (GET_OSD_SATURATION() == _SATURATION_CENTER)?_STRING_COLOR_SWITCH_COLOR : _STRING_COLOR_SWITCH_SINGLE, _ITEM_ADJUST_COLOR,_ENGLISH);

}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void HotkeyILuminanceAdjust(void)
{    
    if(UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE) == _OFF)
    {
        UserCommonNVRamSetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE, _ON);
        // Auto exit after 1 minute
        ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_KEY_PLUS_LUMINANCE_DISPLAY_MODE_END);
    }
    else
    {
        UserCommonNVRamSetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE, _OFF);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_PLUS_LUMINANCE_DISPLAY_MODE_END);
    }

#if 1
    UserCommonNVRamSaveSystemData();
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#endif

    OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), HEIGHT(2));
    OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(_WIN_HOTKEY_VALUE_COL), WIDTH(g_ucOsdWidth - _WIN_HOTKEY_INFO_WIDTH), _PFONT_PAGE_1, _STRING_OFF + UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE), _ITEM_ADJUST_COLOR,GET_OSD_LANGUAGE());

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UpdateMainMenuCursor(BYTE OSDState , bit bState)
{
	BYTE ucItem = 0;
	
	ucItem = OSDState - _MAIN_PAGE_START;
	if(ucItem > (_MAIN_PAGE_END - _MAIN_PAGE_START))
		return;
    
    if(bState == _STATE_SELECT)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(_OSD_MAIN_ITEM_ROW_START +( ucItem*_OSD_ROW_STEP)), COL(_OSD_MAIN_ITEM_COL_START), WIDTH(_OSD_MAIN_ITEM_SELECT_WIDTH), HEIGHT(1), _OPT_SELECT_FRAME_COLOR, _OPT_STRING_SELECT_COLOR, _OPT_SELECT_FRAME_COLOR);
    }
    else
    { 
        OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(_OSD_MAIN_ITEM_ROW_START +( ucItem*_OSD_ROW_STEP)), COL(_OSD_MAIN_ITEM_COL_START), WIDTH(_OSD_MAIN_ITEM_SELECT_WIDTH), HEIGHT(1), _MAIN_WIN_COLOR, _OPT_STRING_NORMAL_COLOR, _MAIN_WIN_COLOR);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UpdateServiceMenuCursor(BYTE OSDState,bit bState)
{
	BYTE ucItem = 0;
	
	ucItem = OSDState - _SERVICE_PAGE_START;
	if(ucItem > (_SERVICE_PAGE_END - _SERVICE_PAGE_START))
		return;
    
    if(bState == _STATE_SELECT)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(_OSD_MAIN_ITEM_ROW_START +( ucItem*_OSD_ROW_STEP)), COL(_OSD_MAIN_ITEM_COL_START), WIDTH(_OSD_MAIN_ITEM_SELECT_WIDTH), HEIGHT(1), _OPT_SELECT_FRAME_COLOR, _OPT_STRING_SELECT_COLOR, _OPT_SELECT_FRAME_COLOR);
    }
    else
    { 
        OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(_OSD_MAIN_ITEM_ROW_START +( ucItem*_OSD_ROW_STEP)), COL(_OSD_MAIN_ITEM_COL_START), WIDTH(_OSD_MAIN_ITEM_SELECT_WIDTH), HEIGHT(1), _MAIN_WIN_COLOR, _OPT_STRING_NORMAL_COLOR, _MAIN_WIN_COLOR);
    }
}

#endif
