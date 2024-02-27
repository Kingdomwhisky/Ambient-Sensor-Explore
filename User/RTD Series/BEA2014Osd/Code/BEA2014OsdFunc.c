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
// ID Code      : BEA2014OsdFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFUNC__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usFontSelectStart;
WORD g_usFontTableStart;
BYTE g_ucOsdWidth;
BYTE g_ucOsdHeight;
BYTE g_ucOsdWidthB;
BYTE g_ucOsdHeightB;
WORD g_ucFontPointer0 = _OSD_PAGE_0_START;
WORD g_ucFontPointer1 = _OSD_PAGE_1_START;
WORD g_ucFontPointer2 = _OSD_PAGE_2_START;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);

void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
void OsdFuncTransparency(BYTE ucTrans);
void OsdFuncBlending(BYTE ucType);



void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
void OsdFuncDisableOsd(void);
void OsdFuncEnableOsd(void);
//void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
void OsdFuncSet2BitIconOffset(WORD usOffset);
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
#if(_SIX_COLOR_SUPPORT == _ON)
void OsdFuncSixColorAdjust(void);
#endif
void OsdFuncColorFormatAdjust(void);
void OsdFuncColorPcmAdjust(void);
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum);
BYTE OsdFuncCheckDPClonePortType(BYTE ucOsdClonePortNum);
void OsdFuncSetOsdItemFlag(void);

#if(_FREEZE_SUPPORT == _ON)
bit OsdFuncCheckFreezeDisable(void);
void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif


#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort);
void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue);
#endif


BYTE COsdCtrlMenuItemGetEnable(WORD ucState);
WORD MGetFirstOsdState(WORD ucBegin, WORD ucEnd);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    BYTE ucI = 0;
    BYTE ucTmp = 17; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif

    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
    }

    // Row Command end
    ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);
    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucTmp = 0x4E;  // 18 Pixel
    }
    else
#endif
    {
        ucTmp = 0x4C;  // 12 Pixel
    }

    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

    g_ucOsdWidth = ucWidth; // for calculation (unit: word count)
    g_ucOsdHeight = ucHeight;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    WORD usShiftValue = 0;
    BYTE ucXdouble = 1;
    WORD usTemp = 0;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucXdouble = 2;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_4_PIXEL)
    {
        // change horizontal delay step to 1 pixel for FB shift
        ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STEP_1_PIXEL);
        usX *= 4;
    }

#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
    usY = (usY >= GET_OSD_POSITION_V_OFFSET_CORRECT_COMPENSATION()) ? (usY - GET_OSD_POSITION_V_OFFSET_CORRECT_COMPENSATION()) : (usY);
#endif

    if(enumOsdPositionType == _OSD_POSITION_GLOBAL_A)
    {
        if((usX * ucXdouble) <= 100)
        {
//            ScalerOsdPosition(enumOsdPositionType, (usX * ucXdouble), usY);
            ScalerOsdPosition(enumOsdPositionType, (usX), usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 0);
        }
        else if((usX * ucXdouble) <= (4094 + 100))
        {
            ScalerOsdPosition(enumOsdPositionType, 100 / ucXdouble, usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, (usX * ucXdouble) - 100);
        }
        else // > 4095+100
        {
            ScalerOsdPosition(enumOsdPositionType, ((usX * ucXdouble) - 4094) / ucXdouble, usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 4094);
        }

        ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_INSIDE, 0x00);
        ScalerOsdFBShiftBoundarySize(0x00, 0x00);
        ScalerOsdFBShiftEn(_ENABLE);
    }
    else if(enumOsdPositionType == _OSD_POSITION_GLOBAL_B)
    {
        usShiftValue = ScalerOsdGetFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE);

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            usTemp = g_ucOsdWidthB * 12;
        }
        else
        {
            usTemp = g_ucOsdHeightB * 18;
        }

        // if HPOS over halt of Panel width + shift value, adjust to adaptable HPOS
        if((usX * ucXdouble) > ((_PANEL_DH_WIDTH / 2 + usShiftValue) - (usTemp * ucXdouble)))
        {
            ScalerOsdPosition(enumOsdPositionType, (((_PANEL_DH_WIDTH / 2 + usShiftValue) - (usTemp * ucXdouble)) / ucXdouble), usY);
        }
        else
        {
            ScalerOsdPosition(enumOsdPositionType, ((usX * ucXdouble) - usShiftValue) / ucXdouble, usY);
        }
    }
#else

#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
    usY = (usY >= GET_OSD_POSITION_V_OFFSET_CORRECT_COMPENSATION()) ? (usY - GET_OSD_POSITION_V_OFFSET_CORRECT_COMPENSATION()) : (usY);
#endif
//DebugMessageUart("y_OsdFuncSetPosition", usY);
    ScalerOsdPosition(enumOsdPositionType, usX, usY);
#endif

    ScalerTimerWaitForEvent(_EVENT_DVS);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncTransparency(BYTE ucTrans)
{
    ScalerOsdSetTransparency(ucTrans);
}

//--------------------------------------------------
// Description  :
// Input Value  : Blending type1:Only windows blending.
//                Blending type2:All blending.
//                Blending type3:Windows & Character background blending.
// Output Value : None
//--------------------------------------------------
void OsdFuncBlending(BYTE ucType)
{
    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdWindow7SpecialFunction(_OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_ALL);
    ScalerOsdSetTransparencyType(ucType);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex)
{
    ScalerOsdWindowDisable(enumWinIndex);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncDisableOsd(void)
{
    ScalerOsdDisableOsd();
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
        SysAudioInternalGenTestProc(_OFF);
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncEnableOsd(void)
{
    ScalerOsdEnableOsd();
}
#if 0
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    // BYTE ucRow;
    BYTE ucCol = 3;

    if((ucRow == 18) || (ucRow == 8))
    {
        OsdFuncChangeColor1Bit(ucRow, ucCol, 8, ucHeight, (ucColor << 4) & 0xF0, _FONTFROM_256_512);
    }
    else
    {
        ucCol = COL(4) + ((ucItem % 4) * 10) - 2;
        OsdFuncChangeColor1Bit(ucRow, ucCol, ucWidth, ucHeight, (ucColor << 4) & 0xF0, _FONTFROM_0_255);
    }
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    BYTE ucWidthCount = 0;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4E | ucFontSelectFrom), ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4E | ucFontSelectFrom), ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4C | ucFontSelectFrom), ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSet2BitIconOffset(WORD usOffset)
{
    ScalerOsd2BitFontOffset(usOffset);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    BYTE ucWidthCount = 0;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucHeight);
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            if((ucHeightCount == 4)&&(GET_OSD_VPOS() <= 5))
            {
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            }
            // 1 Bit Font
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4C, ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}
#if 0
#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSixColorAdjust(void)
{
    ScalerColorSixColorAdjust(GET_OSD_SIX_COLOR(), GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorFormatAdjust(void)
{
    switch(SysSourceGetInputPort())
    {
        case _A0_INPUT_PORT:

            if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
            {
                SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
            }
            else
            {
                SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
            }

            break;

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
        case _D0_INPUT_PORT:
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
        case _D1_INPUT_PORT:
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DVI_PORT)
        case _D2_INPUT_PORT:
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DVI_PORT)
        case _D3_INPUT_PORT:
#endif

            if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
            {
                SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
            }
            else
            {
                SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
            }

            break;

        default:
            break;
    }

#if(_OVERSCAN_SUPPORT == _ON)
    if(GET_OSD_OVERSCAN_STATUS() == _ON)
    {
        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
    }
    else
#endif
    {
        SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_POLLING);
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorPcmAdjust(void)
{
#if(_PCM_FUNCTION == _ON)

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif

    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
        {
            UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
        }
#endif
        UserAdjustPCM(GET_OSD_PCM_STATUS());
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_BRIGHTNESS_SUPPORT == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
        {
            ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
        }
#endif
    }
    else
    {
#if(_GAMMA_FUNCTION == _ON)
        UserAdjustGamma(GET_OSD_GAMMA());
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
        UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif

#if((_GAMMA_FUNCTION == _ON) || (_GLOBAL_HUE_SATURATION == _ON))
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_GAMMA_FUNCTION == _ON)
        if(GET_OSD_GAMMA() != _GAMMA_OFF)
        {
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);

#if(_RGB_GAMMA_FUNCTION == _ON)
            ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif
        }
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
        ScalerColorSRGBEnable(_FUNCTION_ON);
#endif

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
#endif  // End of #if((_GAMMA_FUNCTION == _ON) || (_GLOBAL_HUE_SATURATION == _ON))

    }

#if(_UNIFORMITY_SUPPORT == _ON)
    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerDelayXms(2);
        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);

        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
    }
#endif
#endif  // End of #if(_PCM_FUNCTION == _ON)
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckPCMStatusAdjustType(BYTE ucOsdPCMStatusNum)
{
    BYTE ucCheckloop =0;
    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                if (ucOsdPCMStatusNum >= _PCM_OSD_AMOUNT)
                {
                    ucOsdPCMStatusNum = _PCM_OSD_SRGB;
                }
                else
                {
                    ucOsdPCMStatusNum++;
                }
                break;

            case _LEFT_KEY_MESSAGE:
                if (ucOsdPCMStatusNum <= _PCM_OSD_SRGB)
                {
                    ucOsdPCMStatusNum = _PCM_OSD_AMOUNT;
                }
                else
                {
                    ucOsdPCMStatusNum--;
                }
                break;

            default:
                break;
        }
        DebugMessageUart("PCMStatusNum =", ucOsdPCMStatusNum);

        switch(ucOsdPCMStatusNum)
        {
            case _PCM_OSD_SRGB :
                ucCheckloop = 1;
                break;
            case _PCM_OSD_ADOBE_RGB :
                ucCheckloop = 0;
				break;
            //case _PCM_OSD_EBU :
            //    ucCheckloop = 0;
            //    break;
            //case _PCM_OSD_REC_709 :
            //    ucCheckloop = 0;
            //    break;
            //case _PCM_OSD_SMPTE_C :
            //    ucCheckloop = 0;
            //    break;
            case _PCM_OSD_USER :
                ucCheckloop = 0;
                break;

            case _PCM_OSD_NATIVE:
                ucCheckloop = 1;
                break;

            default:
                break;

        }
    }while(ucCheckloop == 0x00);//0x00=>NO PCM

    return ucOsdPCMStatusNum;

}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckPCMInputGammaAdjustType(BYTE ucOsdInputGammaTypeNum)
{
    BYTE ucCheckloop =0;
    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                if (ucOsdInputGammaTypeNum >= _PCM_INPUTGAMMA_AMOUNT)
                {
                    ucOsdInputGammaTypeNum = _PCM_INPUTGAMMA_NATIVE;
                }
                else
                {
                    ucOsdInputGammaTypeNum++;
                }
                break;

            case _LEFT_KEY_MESSAGE:
                if (ucOsdInputGammaTypeNum <= _PCM_INPUTGAMMA_NATIVE)
                {
                    ucOsdInputGammaTypeNum = _PCM_INPUTGAMMA_AMOUNT;
                }
                else
                {
                    ucOsdInputGammaTypeNum--;
                }
                break;

            default:
                break;
        }

        switch(ucOsdInputGammaTypeNum)
        {
            case _PCM_INPUTGAMMA_NATIVE:
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_18 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_19 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_20 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_21 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_22 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_24 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_26 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_28 :
                ucCheckloop = 1;
                break;
            case _PCM_INPUTGAMMA_30 :
                ucCheckloop = 1;
                break;
                
            case _PCM_INPUTGAMMA_DICOM :
                ucCheckloop = 0;
                break;

            case _PCM_INPUTGAMMA_HLG :
                ucCheckloop = 0;
                break;

            default:
                break;

        }
    }while(ucCheckloop == 0x00);//0x00=>NO PORT

    return ucOsdInputGammaTypeNum;

}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckGammaAdjustType(BYTE ucOsdGammaTypeNum)
{
    BYTE ucCheckloop =0;
    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:  
#if(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
				if(GET_OSD_STATE()==_IMAGE_HYBRID_GRAY_CURVE_ADJ)
				{
                    if (ucOsdGammaTypeNum >= (_GAMMA_AMOUNT - 1))
                    {
                        ucOsdGammaTypeNum = _GAMMA_20;
                    }
                    else
                    {
                        ucOsdGammaTypeNum++;
                    }
				} 
                else //if(GET_OSD_STATE()==_IMAGE_GAMMA_ADJ)
#endif                                
				{
    				if (ucOsdGammaTypeNum >= _GAMMA_AMOUNT)
				    {
    					 ucOsdGammaTypeNum = _GAMMA_18;
				    }
    				else
				    {
                         ucOsdGammaTypeNum++;
				    }
				}
				break;

            case _LEFT_KEY_MESSAGE:
#if(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
                if(GET_OSD_STATE()==_IMAGE_HYBRID_GRAY_CURVE_ADJ)
				{
                    if (ucOsdGammaTypeNum <= _GAMMA_20)
                    {
                        ucOsdGammaTypeNum = (_GAMMA_AMOUNT - 1);
                    }
                    else
                    {
                        ucOsdGammaTypeNum--;
                    }
				} 
                else //if(GET_OSD_STATE()==_IMAGE_GAMMA_ADJ)
#endif                                
				{
                    if (ucOsdGammaTypeNum <= _GAMMA_18)
                    {
                        ucOsdGammaTypeNum = _GAMMA_AMOUNT;
                    }
                    else
                    {
                        ucOsdGammaTypeNum--;
                    }
				}
				break;

            case _OK_KEY_MESSAGE:
				if(GET_OSD_STATE()==_MENU_HOTKEY_GAMMA_MODE)
				{
    				if (ucOsdGammaTypeNum >= _GAMMA_AMOUNT)
				    {
    					 ucOsdGammaTypeNum = _GAMMA_18;
				    }
    				else
				    {
                         ucOsdGammaTypeNum++;
				    }
                } 
				break;
                
            default:
                break;

        }

        switch(ucOsdGammaTypeNum)
        {
            case _GAMMA_OFF :
                ucCheckloop = 0;
                break;

#if(_GAMMA_TYPE ==_GAMMA_NAME_G22_DICOM_USER_CALIB)
            case _GAMMA_18 :   // 2.2
            case _GAMMA_20 :   // DICOM
            case _GAMMA_22 :   // User
            case _GAMMA_24 :   // Calib
                ucCheckloop = 1;
                break;
            case _GAMMA_26 :   // Hybrid:->cancel change to On/Off
            case _GAMMA_DICOM_ALC1 :
            case _GAMMA_DICOM_ALC2 :
            case _GAMMA_DICOM_ALC3 :
            case _GAMMA_DICOM_ALC4 :
            case _GAMMA_DICOM_ALC5 :
            case _GAMMA_CALIB :
                ucCheckloop = 0;
                break;

#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)  
            case _GAMMA_18 :   // 2.0
            case _GAMMA_20 :   // 2.2
            case _GAMMA_22 :   // 2.4
            case _GAMMA_24 :   // 2.6
            case _GAMMA_26 :   // DICOM 
                ucCheckloop = 1;
                break;

            case _GAMMA_DICOM_ALC1 :
            case _GAMMA_DICOM_ALC2 :
            case _GAMMA_DICOM_ALC3 :
            case _GAMMA_DICOM_ALC4 :
            case _GAMMA_DICOM_ALC5 :
                ucCheckloop = 0;
                break;
                
            case _GAMMA_CALIB :
                ucCheckloop = 1;
                break;

#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)  
            case _GAMMA_18 : 
                ucCheckloop = 1;
                break;
                                
            case _GAMMA_DICOM200 :
            case _GAMMA_DICOM250 :
            case _GAMMA_DICOM300 :
            case _GAMMA_DICOM350 :
            case _GAMMA_DICOM400 :
            case _GAMMA_DICOM450 :
            case _GAMMA_DICOM500 :
            case _GAMMA_DICOM550 :
            case _GAMMA_DICOM600 :     
            case _GAMMA_CALIB :
                ucCheckloop = 1;
                break;

            case _GAMMA_DICOM_ALC1 :
            case _GAMMA_DICOM_ALC2 :
            case _GAMMA_DICOM_ALC3 :
            case _GAMMA_DICOM_ALC4 :
            case _GAMMA_DICOM_ALC5 :
                ucCheckloop = 0;
                break;

#else

#endif 
            default:
                break;

        }
    }while(ucCheckloop == 0x00);//0x00=>NO PORT

    return ucOsdGammaTypeNum;

}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckColorTempAdjustType(BYTE ucOsdColorTempTypeNum)
{
    BYTE ucCheckloop =0;
    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
                    if ((ucOsdColorTempTypeNum < _CT_SRGB)||(ucOsdColorTempTypeNum >= _CT_USER))
                    {
                        ucOsdColorTempTypeNum = _CT_SRGB;
                    }
                    else
                    {
                        ucOsdColorTempTypeNum ++;
                    }
                }
                else
                {
                    if (ucOsdColorTempTypeNum >= _CT_COLORTEMP_AMOUNT)
                    {
                        ucOsdColorTempTypeNum = _CT_9300;
                    }
                    else
                    {
                        ucOsdColorTempTypeNum++;
                    }
                }
                break;

            case _LEFT_KEY_MESSAGE:
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
                    if ((ucOsdColorTempTypeNum < _CT_SRGB)||(ucOsdColorTempTypeNum >= _CT_USER))
                    {
                        ucOsdColorTempTypeNum = _CT_SRGB;
                    }
                    else
                    {
                        ucOsdColorTempTypeNum = _CT_USER;
                    }
                }
                else
                {
                    if (ucOsdColorTempTypeNum <= _CT_9300)
                    {
                        ucOsdColorTempTypeNum = _CT_USER;
                    }
                    else
                    {
                        ucOsdColorTempTypeNum--;
                    }
                }
                break;
            case _EXIT_KEY_MESSAGE:
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
                if (ucOsdColorTempTypeNum <_CT_SRGB)
                {
                    ucOsdColorTempTypeNum = _CT_USER;
                }
                }
                break;
            default:
                break;
        }
        switch(ucOsdColorTempTypeNum)
        {
            case _CT_9300 :
                ucCheckloop = 1;
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
	                ucCheckloop = 0;
                } 
                break;
                
            case _CT_7500 :
                ucCheckloop = 1;
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
	                ucCheckloop = 0;
                }                
				if((_SKIP_COLORTEMP & _kBIT_CT_7500) != 0)
				{
	                ucCheckloop = 0;
				}
                if((GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)&&(_ENABLE_CANON_THREE_CT_SUPPORT == _OFF))
				{
	                ucCheckloop = 0;
				}
                if(IsMonoChromeorColorPanel() == M_MONO)
                {
	                ucCheckloop = 0;
                }
				break;
                
            case _CT_6500 :
                ucCheckloop = 1;
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
	                ucCheckloop = 0;
                }  
                if(IsMonoChromeorColorPanel() == M_MONO)
                {
	                ucCheckloop = 0;
                }
                
                break;
                
            case _CT_5800 :
                ucCheckloop = 1;
                if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))
                {
	                ucCheckloop = 0;
                }
                
				if((_SKIP_COLORTEMP & _kBIT_CT_5800) != 0)
				{
	                ucCheckloop = 0;
				}
                if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
				{
	                ucCheckloop = 0;
				}
                if(IsMonoChromeorColorPanel() == M_MONO)
                {
	                ucCheckloop = 0;
                }                
                break;

            case _CT_SRGB :   
                // _OUTGAMMA_OFF    
                ucCheckloop = 1;
                if((GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)&&(GET_OSD_PCM_STATUS()!= _PCM_OSD_NATIVE))
				{
	                ucCheckloop = 0;
				}  
                if(IsMonoChromeorColorPanel() == M_MONO)
                {
	                ucCheckloop = 0;
                }                
                break;
                
            case _CT_USER :
                ucCheckloop = 1;
                if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
				{
	                ucCheckloop = 0;
				}
                if(IsMonoChromeorColorPanel() == M_MONO)
                {
	                ucCheckloop = 0;
                }                
                break;

            default:
                break;

        }
    }while(ucCheckloop == 0x00);//0x00=>NO PORT
    return ucOsdColorTempTypeNum;

}
#if 0
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckAspectAdjustType(WORD usValue, WORD usMax, WORD usMin)
{
    BYTE ucCheckloop =0;
    do
    {
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                return usMin;
            }
            else
            {
                usValue++;
            }

            break;

        case _LEFT_KEY_MESSAGE:           
            if (usValue <= usMin)
            {
                    return usMax;
            }
            else
            {
                usValue--;
            }            
            break;

        default:
            break;
    }
        switch(usValue)
        {
            case _OSD_ASPECT_RATIO_FULL :
            case _OSD_ASPECT_RATIO_16_BY_9 :
            case _OSD_ASPECT_RATIO_4_BY_3 :
            case _OSD_ASPECT_RATIO_5_BY_4 :                
            case _OSD_ASPECT_RATIO_ORIGIN :                
                ucCheckloop = 1;
                break;
            case _OSD_ASPECT_RATIO_USER :                
                ucCheckloop = 0;
                break;
                
            default:
                break;
                
            }
    }while(ucCheckloop == 0x00);//0x00=>NO PORT
        
    return usValue;
}
#endif
#if 1
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowSourceMenuCheck(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING) == _TRUE)
    {
        ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    }
    else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
            (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING) == _TRUE))
    {
//DebugMessageRx1("checkps", 1);        
        ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    }
#else
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        if(GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION)
        {
        }
        else
        {
//DebugMessageRx1("checkps", 2);        
        
            ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
        }
    }
#endif
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetOsdItemFlag(void)
{
    // input port
    if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
    {
        SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_AUTO);
    }
    else
    {
        switch(SysSourceGetInputPort())
        {
            case _A0_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
                break;

            case _D0_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D0);
                break;

            case _D1_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D1);
                break;

            case _D2_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D2);
                break;

            case _D3_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D3);
                break;

            case _D4_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D4);
                break;

            case _D5_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D5);
                break;

            case _D6_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D6);
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum)
{
    BYTE ucCheckloop = 0;

    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
#if 1
				if(GET_OSD_STATE()==_MENU_HOTKEY_KVM_MODE)
				{
                    if(ucOsdInputNum >= _OSD_INPUT_D2)
                    {
                        ucOsdInputNum = _OSD_INPUT_D0;
                    }
                    else
                    {
                        ucOsdInputNum++;
                    }
				} 
                else
#endif
                {
                    if(ucOsdInputNum >= _OSD_INPUT_AUTO)
                    {
                        ucOsdInputNum = _OSD_INPUT_A0;
                    }
                    else
                    {
                        ucOsdInputNum++;
                    }
                }
                break;

            case _LEFT_KEY_MESSAGE:
#if 1
				if(GET_OSD_STATE()==_MENU_HOTKEY_KVM_MODE)
				{
                    if(ucOsdInputNum == _OSD_INPUT_D0)
                    {
                        ucOsdInputNum = _OSD_INPUT_D2;
                    }
                    else
                    {
                        ucOsdInputNum--;
                    }
				} 
                else
#endif
                {
                    if(ucOsdInputNum <= _OSD_INPUT_A0)
                    {
                        ucOsdInputNum = _OSD_INPUT_AUTO;
                    }
                    else
                    {
                        ucOsdInputNum--;
                    }
                }
                break;

            default:
                break;
        }
        DebugMessageUart("ucOsdInputNum:", ucOsdInputNum);

        switch(ucOsdInputNum)
        {
            case _OSD_INPUT_A0:
                ucCheckloop = (_A0_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_A1:
            case _OSD_INPUT_A2:
                ucCheckloop = 0;
                break;
            case _OSD_INPUT_D0:
                ucCheckloop = (_D0_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D1:
                ucCheckloop = (_D1_INPUT_TYPE - _OPTION_ICON_END);
				if(GET_OSD_STATE()==_MENU_HOTKEY_KVM_MODE)
                {            
                ucCheckloop = 0;
                }
#if(_NO_HDMI)  
                {            
                ucCheckloop = 0;
                }
#endif
                break;
            case _OSD_INPUT_D2:
                ucCheckloop = (_D2_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D3:
                ucCheckloop = (_D3_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D4:
                ucCheckloop = (_D4_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D5:
                ucCheckloop = (_D5_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D6:
                ucCheckloop = (_D6_INPUT_TYPE - _OPTION_ICON_END);
                break;

            case _OSD_INPUT_AUTO:
                DebugMessageUart("_Auto:", ucOsdInputNum);
                return ucOsdInputNum;
                break;
                
            default:
                break;
        }
    }while(ucCheckloop == 0x00); // 0x00=>NO PORT
    DebugMessageUart("return:", ucOsdInputNum);

    return ucOsdInputNum;
}

#if 0//(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckDPClonePortType(BYTE ucOsdClonePortNum)
{
    BYTE ucCheckloop =0;
    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                if (ucOsdClonePortNum >= _OSD_CLONE_MTP_D6)
                {
                    ucOsdClonePortNum = _OSD_CLONE_MTP_OFF;
                }
                else
                {
                    ucOsdClonePortNum++;
                }
                break;

            case _LEFT_KEY_MESSAGE:
                if (ucOsdClonePortNum <= _OSD_CLONE_MTP_OFF)
                {
                    ucOsdClonePortNum = _OSD_CLONE_MTP_D6;
                }
                else
                {
                    ucOsdClonePortNum--;
                }
                break;

            default:
                break;
        }

        switch(ucOsdClonePortNum)
        {
            case _OSD_CLONE_MTP_OFF :
                ucCheckloop = 1;
                break;
            case _OSD_CLONE_MTP_A0 :
                ucCheckloop = (_A0_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D0 :
                ucCheckloop = (_D0_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D1 :
                ucCheckloop = (_D1_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D2 :
                ucCheckloop = (_D2_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D3 :
                ucCheckloop = (_D3_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D4 :
                ucCheckloop = (_D4_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D5 :
                ucCheckloop = (_D5_INPUT_TYPE-_OPTION_ICON_END);
                break;
            case _OSD_CLONE_MTP_D6 :
                ucCheckloop = (_D6_INPUT_TYPE-_OPTION_ICON_END);
                break;

            default:
                break;

        }
    }while(ucCheckloop == 0x00);//0x00=>NO PORT

    return ucOsdClonePortNum;

}
#endif

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFreezeDisable(void)
{
    if(((((GET_OSD_STATE() >= _MENU_DISPLAY_AUTO) &&
          (GET_OSD_STATE() <= _MENU_DISPLAY_PHASE)) ||
         (GET_OSD_STATE() == _MENU_COLOR_FORMAT) ||
         (GET_OSD_STATE() == _MENU_ADVANCE_ITEM) ||
         (GET_OSD_STATE() == _MENU_OTHER_RESET) ||
         (GET_OSD_STATE() == _MENU_DISPLAY_LATENCY)) &&
        (GET_KEYMESSAGE() == _MENU_KEY_MESSAGE)) ||
       ((GET_OSD_STATE() == _MENU_ADVANCE_ULTRA_VIVID_ADJUST) && (GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
       ((GET_OSD_STATE() == _MENU_ADVANCE_ULTRA_VIVID_ADJUST) && (GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_L) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
    {
        OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
        ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
        SET_OSD_STATE(GET_OSD_STATE_PREVIOUS());
        SET_OSD_FREEZE_STATUS(_OFF);
        UserCommonAdjustDisplayFreeze(_OFF);
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
        SET_FREEZE_DISABLE_MSG_STATE(_ON);
#endif
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowOSDAfterClosedFreezeMsg(void)
{
    OsdDispMainMenu();
}
#endif


#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort)
{
    switch(enumSearchPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return (GET_OSD_D0_HDMI_VER());
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return (GET_OSD_D1_HDMI_VER());
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return (GET_OSD_D2_HDMI_VER());
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return (GET_OSD_D3_HDMI_VER());
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return (GET_OSD_D4_HDMI_VER());
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return (GET_OSD_D5_HDMI_VER());
#endif

        default:
            return 0;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue)
{
    ucValue = ucValue;

    switch(enumSearchPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_OSD_D0_HDMI_VER(ucValue);
            break;
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_OSD_D1_HDMI_VER(ucValue);
            break;
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_OSD_D2_HDMI_VER(ucValue);
            break;
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_OSD_D3_HDMI_VER(ucValue);
            break;
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_OSD_D4_HDMI_VER(ucValue);
            break;
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            SET_OSD_D5_HDMI_VER(ucValue);
            break;
#endif
        default:
            break;
    }
}
#endif

#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncAutoDetectSwitchHdmiDPPort(void)
{
    g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
  
    if(GET_PCB_HDMI_DP_SWITCH_DETECT() == _LOW)
    {
        SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D1);  //OSD input set to DP
    }
    else
    {
        SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D3);  //OSD input set to HDMI
    }

    if((g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM()))
    {
        switch(GET_OSD_INPUT_PORT_OSD_ITEM())
        {

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
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
    }
}
#endif

#if 0
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void OsdFuncCalibrationWindowsColor(BYTE ucWin, BYTE ucPos, BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{    
    BYTE ucVPosOffset=0;
    
    if(_PANEL_DV_HEIGHT == 2560)
    {
        ucVPosOffset = 140;
    }
    else
    {
        ucVPosOffset = 66;
    }
    
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE_G(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE_B(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE(_DISABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    
    //CW_FRONT_SENSOR
    if(ucPos == 1)
    {
        if(_PANEL_DV_HEIGHT == 2560)
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/4)), COL((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/4)-ucVPosOffset), WIDTH((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/2)), HEIGHT((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/2)-ucVPosOffset), _CP_BLACK);
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
        }
        else
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH((g_ucOsdWidth*12)/4), HEIGHT((g_ucOsdHeight*18)/4), _CP_BLACK);
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - (g_ucOsdWidth*12)/4)/4), ((_PANEL_DV_HEIGHT - (g_ucOsdHeight*18)/4)-ucVPosOffset));
        }
    }

    //CW_CENTER
    if(ucPos == 2)
    {
        OsdWindowDrawing(_OSD_WINDOW_5, ROW(0), COL(0), WIDTH(g_ucOsdWidth*12), HEIGHT(g_ucOsdHeight*18), _CP_BLACK);
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
    }

    // BOTH ->used to creat compare table
    if(ucPos == 3)
    {
        if(ucWin==_OSD_WINDOW_0)
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/4)), COL((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/4)-ucVPosOffset), WIDTH((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/2)), HEIGHT((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/2)-ucVPosOffset), _CP_BLACK);
        }
        if(ucWin==_OSD_WINDOW_5)
        {
            OsdWindowDrawing(_OSD_WINDOW_5, ROW(0), COL(0), WIDTH(g_ucOsdWidth*12), HEIGHT(g_ucOsdHeight*18), _CP_BLACK);
        }
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
    }
    
    ScalerOsdWindowSaturatedColorSelect(ucWin, ucRed, ucGreen, ucBlue);
}
#endif

//--------------------------------------------------
// Description  : Calibration  Windows Color
// Input Value  :
// Output Value : None
//--------------------------------------------------
void OsdFuncCalibrationWindowsColor(BYTE ucWin, BYTE ucPos, BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{    
    BYTE ucVPosOffset=0;

    // must sync _DDCCI_SENSOR_CALIB_GET_DISP_RES_AND_POS
    if(_PANEL_DV_HEIGHT == 2560)
    {
        ucVPosOffset = 140;
    }
    else if(_PANEL_DV_HEIGHT == 2048)
    {
        ucVPosOffset = 100;
    }
	else
    {
        ucVPosOffset = 100;
    }
    
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE_G(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE_B(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE(_DISABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    
    //CW_FRONT_SENSOR
    if(ucPos == 1)
    {
        if(_PANEL_DV_HEIGHT == 2560)
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/4)), COL((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/4)-ucVPosOffset), WIDTH((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/2)), HEIGHT((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/2)-ucVPosOffset), _CP_BLACK);
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
        }
        else
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH((g_ucOsdWidth*12)/4), HEIGHT((g_ucOsdHeight*18)/4), _CP_BLACK);
#if((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
DebugMessageUart("g_ucOsdWidth", g_ucOsdWidth);
DebugMessageUart("g_ucOsdHeight", g_ucOsdHeight);

            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A,575, 16);  
            //OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A,200, 60);  
            
#elif((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - (g_ucOsdWidth*12)/4)/4), ((_PANEL_DV_HEIGHT - (g_ucOsdHeight*18)/4)-ucVPosOffset-50));
#else
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - (g_ucOsdWidth*12)/4)/4), ((_PANEL_DV_HEIGHT - (g_ucOsdHeight*18)/4)-ucVPosOffset));
#endif
        }
    }

    //CW_CENTER
    if(ucPos == 2)
    {
        OsdWindowDrawing(_OSD_WINDOW_5, ROW(0), COL(0), WIDTH(g_ucOsdWidth*12), HEIGHT(g_ucOsdHeight*18), _CP_BLACK);
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
    }

    // BOTH ->used to creat compare table
    if(ucPos == 3)
    {
#if((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
        if(ucWin==_OSD_WINDOW_0)
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW(1224), COL(0), WIDTH(1224+((g_ucOsdWidth*12)/4)), HEIGHT(((g_ucOsdHeight*18)/4)), _CP_BLACK);        
        }
        if(ucWin==_OSD_WINDOW_5)
        {
            OsdWindowDrawing(_OSD_WINDOW_5, ROW(0), COL(0+((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2)), WIDTH(g_ucOsdWidth*12), HEIGHT(((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2)+(g_ucOsdHeight*18)), _CP_BLACK);
        }
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), 0);        
        //OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
#else    
        if(ucWin==_OSD_WINDOW_0)            
        {
            OsdWindowDrawing(_OSD_WINDOW_0, ROW((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/4)), COL((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/4)-ucVPosOffset), WIDTH((_PANEL_DH_WIDTH/2)+((g_ucOsdWidth*12)/2)), HEIGHT((_PANEL_DV_HEIGHT/2)+((g_ucOsdHeight*18)/2)-ucVPosOffset), _CP_BLACK);
        }
        if(ucWin==_OSD_WINDOW_5)
        {
            OsdWindowDrawing(_OSD_WINDOW_5, ROW(0), COL(0), WIDTH(g_ucOsdWidth*12), HEIGHT(g_ucOsdHeight*18), _CP_BLACK);
        }
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - g_ucOsdWidth*12)/4/2), ((_PANEL_DV_HEIGHT - g_ucOsdHeight*18)/2));
#endif
    }
    
    ScalerOsdWindowSaturatedColorSelect(ucWin, ucRed, ucGreen, ucBlue);
}

//--------------------------------------------------
// Description  : OsdDisp2ndMenuCheck
// Input Value  :
// Output Value : None
//--------------------------------------------------
BYTE COsdCtrlMenuItemGetEnable(WORD ucState)
{
    switch (ucState)
    {

        case _IMAGE_PCM:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
            {
                // if != OGCOCC Tool Calibration data
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS), 6, pData);
                if((PDATA_WORD(0) == 0xFFFF) || (PDATA_WORD(1) == 0xFFFF) || (PDATA_WORD(2) == 0xFFFF))        
                {
                    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                    {
                        SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
                    }
    	            return _EN_DL_STATE_DISABLE;
                }
            }
            break;

        case _IMAGE_GAMMA:
        case _IMAGE_DICOMALC:
        case _IMAGE_COLOR_TEMP:
        	if((ucState == _IMAGE_GAMMA)&&(GET_COLOR_TEMP_TYPE() == _CT_SRGB))
        	{
                return _EN_DL_STATE_DISABLE;
        	}            
        	if((ucState == _IMAGE_COLOR_TEMP)&&(IsGammaOptionPCCalibration(GET_OSD_GAMMA())))
        	{
                //return _EN_DL_STATE_DISABLE;
        	}
        	if((ucState == _IMAGE_COLOR_TEMP)&&(IsMonoChromeorColorPanel() == M_MONO))
            {
                return _EN_DL_STATE_HIDDEN;
            }
            if((ucState == _IMAGE_DICOMALC)&&(!IsGammaOptionDICOMALC(GET_OSD_GAMMA())))
        	{
                return _EN_DL_STATE_DISABLE;
        	}

#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_SDR_TO_HDR_SUPPORT == _ON)
            if(GET_OSD_SDR_TO_HDR() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)

            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif

            break;
#if(_BEACON_OSD_AMB == _OFF)
        case _FUNCTION_AMB_LIGHT:
            {
                return _EN_DL_STATE_HIDDEN;
        	}
        break;
#endif      

        case _IMAGE_BACKLIGHT:
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)        
        	{
                return _EN_DL_STATE_DISABLE;
        	}
#endif

#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif

        	if(GET_COLOR_TEMP_TYPE() == _CT_SRGB)
        	{
                return _EN_DL_STATE_DISABLE;
        	}
			
        	if(	IsGammaOptionDICOM(GET_OSD_GAMMA()) ||
				IsGammaOptionMCUCalibration(GET_OSD_GAMMA()) ||
				IsGammaOptionPCCalibration(GET_OSD_GAMMA()) ||
				IsGammaOptionHybridGamma(GET_OSD_GAMMA()) ||
				IsGammaOptionNative(GET_OSD_GAMMA()))
        	{
                return _EN_DL_STATE_DISABLE;
        	}
        	break;

        case _IMAGE_HDR:
#if(_HDR10_SUPPORT == _ON)
            {
                // if != OGCOCC Tool Calibration data
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_MAX_BRI_ADDRESS), 6, pData);
                if((PDATA_WORD(0) == 0xFFFF) || (PDATA_WORD(1) == 0xFFFF) || (PDATA_WORD(2) == 0xFFFF))        
                {
    	            return _EN_DL_STATE_DISABLE;
                }
            }
#else
            return _EN_DL_STATE_DISABLE;
#endif
        	break;

        case _IMAGE_HDR_DARK_ENHANCE:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() != _HDR10_ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
            break;

        case _IMAGE_HDR_SHARP_ENHANCE:
        case _IMAGE_HDR_CONTRAST:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() != _HDR10_ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
            break;

#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)        
        case _QA_DEVIATION:
        	if(!IsGammaOptionMCUCalibration(GET_OSD_GAMMA()))
        	{
                return _EN_DL_STATE_DISABLE;
        	}
        	break;
#endif            

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)            
        case _IMAGE_HYBRID_COLOR_CURVE:
            return _EN_DL_STATE_DISABLE;
        	break;
#endif            
            
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
        case _GAMMA_USER_LAMB:
            if(GET_OSD_LUT_USER_TYPE()!= _LUT_USER_DICOM)
            {
                return _EN_DL_STATE_HIDDEN;
            }
            break;	

        case _GAMMA_USER_VALUE:
            if(GET_OSD_LUT_USER_TYPE()!= _LUT_USER_GAMMA)
            {
                return _EN_DL_STATE_HIDDEN;
            }
            break;
#endif
			
        case _UNIFORMITY:
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            if(GET_OSD_LOCAL_DIMMING() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_SDR_TO_HDR_SUPPORT == _ON)
            if(GET_OSD_SDR_TO_HDR() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)

            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
            break;
        case _DP_RESOLUTION:
            return _EN_DL_STATE_HIDDEN;
            break;

        case _SDR:
#if(_SDR_TO_HDR_SUPPORT == _OFF)
            return _EN_DL_STATE_HIDDEN;
#endif

#if(_HDR10_SUPPORT == _ON)
            if((UserCommonHDRGetHDR10Status() == _HDR10_ON))
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                return _EN_DL_STATE_DISABLE;
            }
#endif
            break; 
        case _BODY_SENSOR:
#if(_ENABLE_DISTANCE_SENSOR == _OFF)            
            return _EN_DL_STATE_DISABLE;
#endif
            break;
        case _GRAVITY_SENSOR:
#if(_ENABLE_GRAVITY_SENSOR==_OFF)            
            return _EN_DL_STATE_DISABLE;
#endif
            break;
            
        case _USE_LIFE_REMINDER:
            return _EN_DL_STATE_HIDDEN;
            break;


    }
    return _EN_DL_STATE_NORMAL;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
BYTE GetShowIndex(BYTE ucMenuItem,BYTE ucBeginItem,BYTE ucEndItem)
{
     BYTE Index;
     bit fEnable;
     bit fNotShow;

	 if((ucMenuItem<ucBeginItem) ||(ucMenuItem>ucEndItem))
	 	return 0;
     
     Index = 0;

     while(ucBeginItem <= ucEndItem)
     {
     	fEnable = COsdCtrlMenuItemGetEnable(ucBeginItem);

		if(fEnable == _EN_DL_STATE_HIDDEN)
			fNotShow = 1;
		else
			fNotShow = 0;

			
     	if(ucBeginItem == ucMenuItem)
     	{
     		if(fEnable == _EN_DL_STATE_NORMAL)		
     		{
     			return Index;
     		}
     		else
     		{
				if(fNotShow)
					return _NOT_SHOW;
				else
					return Index;
     		}
     	}

     	if(ucBeginItem > ucMenuItem)
     		return _NOT_SHOW;
     		
       	if(!fNotShow)
       	{	
    	    Index++;
        }
        else
        {
            if(fEnable)
            {
                Index++;
            }
	    }
        ucBeginItem++;
     }

     return _NOT_SHOW;     
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
WORD MGetFirstOsdState(WORD ucBegin, WORD ucEnd)
{
	//Return En Show state
    BYTE ucItemCnt;
    BYTE ucTotal;
    BYTE ucState;	

	ucTotal = ucEnd - ucBegin + 1;
	
    ucItemCnt = ucTotal;

    ucState = 0;

    do
    {

        if(COsdCtrlMenuItemGetEnable(ucState + ucBegin) == _EN_DL_STATE_NORMAL)
        {
            return (ucBegin+ucState);			
        }
        ucState = (ucState + 1) % ucTotal;
        ucItemCnt--;
    }
    while (ucItemCnt != 0);

    return 0xff;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
WORD MGetNextOsdState(WORD ucState,WORD ucBegin, WORD ucEnd, bit bCycle)
{
    //Return En Show state
    BYTE ucItemCnt;
    BYTE ucTotal;
    BYTE ucType = _EN_DL_STATE_NORMAL;
    WORD ucOldOsdState = ucState;	
    WORD ucOldStart = ucBegin;
    WORD ucOldEnd = ucEnd;
    bit bReCalc = _TRUE;
    bit ucDirect = _RIGHT;

    if(ucState < _MAIN_PAGE_START)
        return ucState;

    ucTotal = ucEnd - ucBegin + 1;

    ucItemCnt = ucTotal;

    ucState = ucState - ucBegin;

    if((GET_KEYMESSAGE() == _MENU_KEY_MESSAGE) || (GET_KEYMESSAGE() == _OK_KEY_MESSAGE) || (GET_KEYMESSAGE() == _DOWN_KEY_MESSAGE)|| (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE))
    {
        ucDirect = _RIGHT;
    }
    else if((GET_KEYMESSAGE() == _UP_KEY_MESSAGE)|| (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE))
    {
        ucDirect = _LEFT;
    }

    do
    {
        if (ucDirect)//Down
        {
            ucState = (ucState + 1) % ucTotal;

            if(((ucState + ucBegin) < ucOldOsdState) && (bCycle == _OFF))
            {
                bReCalc = _FALSE;
            }
            else //if(bCycle == _ON)
            {
                bReCalc = _TRUE;
            }
        }
        else
        {
            ucState = (ucState + ucTotal - 1) % ucTotal;

            if(((ucState + ucBegin) > ucOldOsdState) && (bCycle == _OFF))
            {
                bReCalc = _FALSE;
            }
            else //if(bCycle == _ON)
            {
                bReCalc = _TRUE;
            }

        }
        ucType = COsdCtrlMenuItemGetEnable(ucState + ucBegin);

        if(bReCalc == _FALSE)
            break;

        if (ucType== _EN_DL_STATE_NORMAL)
            break;
        
        ucItemCnt--;

    }
    while (ucItemCnt != 0);


    if(bReCalc == _FALSE)
    {
        ucState = ucOldOsdState;
    }
    else
    {
        ucState = (WORD)(ucState + ucBegin);
    }

    return ucState;
}
#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)

