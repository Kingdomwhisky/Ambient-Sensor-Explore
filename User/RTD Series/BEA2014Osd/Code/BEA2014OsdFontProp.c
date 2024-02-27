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
// ID Code      : BEA2014OsdFontProp.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFONTPROP__

#include "UserCommonInclude.h"
#include "BEA2014OsdTextTableBody.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#ifndef _OSD_FONT_MODE_FORCE_256_511
#define _OSD_FONT_MODE_FORCE_256_511                _ON
#endif
#define GET_OSD_INFO_MAP_FONT_BASE_ADDRESS()        g_usFontTableStart

#define GET_OSD_INFO_FONT_POINTER_0()               g_ucFontPointer0
#define GET_OSD_INFO_FONT_POINTER_1()               g_ucFontPointer1
#define GET_OSD_INFO_FONT_POINTER_2()               g_ucFontPointer2

#define SET_OSD_INFO_FONT_POINTER_0(x)              g_ucFontPointer0 = (x)
#define SET_OSD_INFO_FONT_POINTER_1(x)              g_ucFontPointer1 = (x)
#define SET_OSD_INFO_FONT_POINTER_2(x)              g_ucFontPointer2 = (x)

#if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_1)
#define _OSD_MODE_BYTE0                             0x8C
#define _OSD_MODE_BYTE0_256_511                     0x2C
#elif(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_2)
#define _OSD_MODE_BYTE0                             0x4C
#define _OSD_MODE_BYTE0_256_511                     0x6C
#endif // End of #if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_1)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
WORD code tSTRING_RESOLUTION_TABLE[][6]=
{
    {   _,   _,   _,   _,   _,   _},
    { 240, _4_, _8_, _0_, _i_,   _},
    { 480, _4_, _8_, _0_, _p_,   _},
    { 288, _5_, _7_, _6_, _i_,   _},
    { 576, _5_, _7_, _6_, _p_,   _},
    { 720, _7_, _2_, _0_, _p_,   _},
    { 540, _1_, _0_, _8_, _0_, _i_},
    {1080, _1_, _0_, _8_, _0_, _p_},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE *g_pucShowNumberAddress;
BYTE *g_pucShowRatioAddress;
BYTE *g_pucShowNumberPercentageAddress;
BYTE g_pucModeInfoData[28];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
void OsdPropGetShowInputPortStringAddress(BYTE ucInputPort);
void OsdPropGetShowVFreqStringAddress(void);
void OsdPropGetShowHFreqPClkStringAddress(void);



#if(_DIGITAL_PORT_SUPPORT == _ON)
void OsdPropGetShowHDCPEnable(BYTE ucVersion);
#endif
void OsdPropGetShowResolutionStringAddress(void);
#if(_FREESYNC_SUPPORT == _ON)
void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor, BYTE ucLanguage);
#endif
#if(_DP_DEBUG_MSG == _ON)
void OsdPropGetShowDpInfoStringAddress(BYTE Index);
#endif

BYTE OsdPropGetFontPointer(BYTE ucPointerSelect);
BYTE OsdPropVideoResolution(void);
BYTE OsdPropSetFontPointer(BYTE ucPointerSelect, BYTE ucPointer);
void OsdPropFontDataToSram(BYTE ucFptsSelect, BYTE *ucpArray, BYTE ucRotateType);

void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
void OsdPropShowNumber_float(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
void OsdPropShowNumberPercentage(BYTE ucRow, BYTE ucCol, DWORD usValue, bit bDecimalpointFlag, BYTE ucFontPoint, BYTE ucColor);
BYTE *OsdPropGetStringTableAddress(BYTE ucString);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowInputPortStringAddress(BYTE ucInputPort)
{
    BYTE ucI = 0;

#if 0
    if(ucInputPort == _A0_PORT)
    {
        g_pucModeInfoData[0] = _A_;
        g_pucModeInfoData[1] = _0_;
    }
    else
    {
        g_pucModeInfoData[0] = _D_;
        g_pucModeInfoData[1] = (ucInputPort - _D0_PORT) + _0_;
    }
#endif

    switch(ucInputPort)
    {
        case _A0_PORT:
        case _A1_PORT:
        case _A2_PORT:            
            ucI = _A0_INPUT_TYPE;
            break;
        case _D0_PORT:
            ucI = _D0_INPUT_TYPE;
            break;
        case _D1_PORT:
            ucI = _D1_INPUT_TYPE;
            break;
        case _D2_PORT:
            ucI = _D2_INPUT_TYPE;
            break;
        case _D3_PORT:
            ucI = _D3_INPUT_TYPE;
            break;
        case _D4_PORT:
            ucI = _D4_INPUT_TYPE;
            break;
        case _D5_PORT:
            ucI = _D5_INPUT_TYPE;
            break;
        case _D6_PORT:
            ucI = _D6_INPUT_TYPE;
            break;

        default:
            break;
    }
            DebugMessageUart("PORT", ucI);
            DebugMessageOsd("PORT", ucI);
            
    //g_pucModeInfoData[2] = _COLON_;

    switch(ucI)
    {
        case _ICON_INPUT_VGA:
            g_pucModeInfoData[0] = _V_;
            g_pucModeInfoData[1] = _G_;
            g_pucModeInfoData[2] = _A_;
            g_pucModeInfoData[3] = _END_;
            break;

        case _ICON_INPUT_DVI:
            g_pucModeInfoData[0] = _D_;
            g_pucModeInfoData[1] = _V_;
            g_pucModeInfoData[2] = _I_;
            g_pucModeInfoData[3] = _END_;
            break;

        case _ICON_INPUT_HDMI:
            g_pucModeInfoData[0] = _H_;
            g_pucModeInfoData[1] = _D_;
            g_pucModeInfoData[2] = _M_;
            g_pucModeInfoData[3] = _I_;
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)&&(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT))
            g_pucModeInfoData[4] = _;
            switch(ucInputPort)
		    {
		        case _D3_INPUT_PORT:
		            g_pucModeInfoData[5] = U0031;
		            break;
		        case _D4_INPUT_PORT:
		            g_pucModeInfoData[5] = U0032;
		            break;
		        default:
		            break;
		    }
            g_pucModeInfoData[6] = _END_;
#else
            g_pucModeInfoData[4] = _END_;
#endif
            break;

        case _ICON_INPUT_DP:
            g_pucModeInfoData[0] = _D_;
            g_pucModeInfoData[1] = _P_;
            g_pucModeInfoData[2] = _;
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT)&&(_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
            switch(ucInputPort)
		    {
		        case _D0_INPUT_PORT:
		            g_pucModeInfoData[3] = U0031;
		            break;
		        case _D1_INPUT_PORT:
		            g_pucModeInfoData[3] = U0032;
		            break;
		        default:
		            break;
		    }
            g_pucModeInfoData[4] = _END_;
#else
            g_pucModeInfoData[3] = _END_;
#endif
            break;

        case _ICON_INPUT_MHL:
            g_pucModeInfoData[0] = _M_;
            g_pucModeInfoData[1] = _H_;
            g_pucModeInfoData[2] = _L_;
            g_pucModeInfoData[3] = _END_;
            break;

        case _ICON_INPUT_DUAL_DVI:
            g_pucModeInfoData[0] = _D_;
            g_pucModeInfoData[1] = _u_;
            g_pucModeInfoData[2] = _a_;
            g_pucModeInfoData[3] = _l_;
            g_pucModeInfoData[4] = _;
            g_pucModeInfoData[5] = _D_;
            g_pucModeInfoData[6] = _V_;
            g_pucModeInfoData[7] = _I_;
            g_pucModeInfoData[8] = _END_;
            break;
            
        case _ICON_INPUT_NO_PORT:
            g_pucModeInfoData[0] = _N_;
            g_pucModeInfoData[1] = _O_;
            g_pucModeInfoData[2] = _N_;
            g_pucModeInfoData[3] = _E_;
            g_pucModeInfoData[4] = _END_;
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
BYTE *OsdPropGetShowPixelClockStringAddress(void)
{
    BYTE ucI = 0;
    WORD usFreq = ScalerSyncGetInputPixelClk();

    g_pucModeInfoData[0] = _P_;
    g_pucModeInfoData[1] = _C_;
    g_pucModeInfoData[2] = _L_;
    g_pucModeInfoData[3] = _K_;
    g_pucModeInfoData[4] = _COLON_;
    g_pucModeInfoData[5] = ___;
    g_pucModeInfoData[6] = ___;

    ucI = 10;

    while(_TRUE)
    {
        if(ucI == 9)
        {
            g_pucModeInfoData[ucI] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usFreq % 10 + _0_;
            usFreq /= 10;
        }

        if(usFreq <= 0)
        {
            break;
        }
        ucI--;
    }

    g_pucModeInfoData[11] = _M_;
    g_pucModeInfoData[12] = _H_;
    g_pucModeInfoData[13] = _z_;
    g_pucModeInfoData[14] = _END_;

    return g_pucModeInfoData;
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowVFreqStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = 0;

    usTemp = GET_INPUT_TIMING_VFREQ();

    g_pucModeInfoData[0] = _V_;
    g_pucModeInfoData[1] = _COLON_;
    g_pucModeInfoData[2] = _;

    ucI = 6;

    while(_TRUE)
    {
        if(ucI == 5)
        {
            g_pucModeInfoData[5] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;
        }

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[7] = _H_;
    g_pucModeInfoData[8] = _z_;
    g_pucModeInfoData[9] = _END_;
}
*/
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowHFreqPClkStringAddress(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    WORD usFreq = ScalerSyncGetInputPixelClk();
    WORD usTemp = GET_INPUT_TIMING_HFREQ();

    g_pucModeInfoData[0] = _H_;
    g_pucModeInfoData[1] = _COLON_;
    g_pucModeInfoData[2] = _;

    ucI = 6;

    while(_TRUE)
    {
        if(ucI == 5)
        {
            g_pucModeInfoData[5] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;
        }

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }

    g_pucModeInfoData[7] = _K_;
    g_pucModeInfoData[8] = _H_;
    g_pucModeInfoData[9] = _z_;

    g_pucModeInfoData[10] = _;
    g_pucModeInfoData[11] = _;
    g_pucModeInfoData[12] = _;

    g_pucModeInfoData[13] = _P_;
    g_pucModeInfoData[14] = _C_;
    g_pucModeInfoData[15] = _L_;
    g_pucModeInfoData[16] = _K_;
    g_pucModeInfoData[17] = _COLON_;
    g_pucModeInfoData[18] = _;
    g_pucModeInfoData[19] = _;

    ucJ = 23;

    while(_TRUE)
    {
        if(ucJ == 22)
        {
            g_pucModeInfoData[ucJ] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucJ] = usFreq % 10 + _0_;
            usFreq /= 10;
        }

        if(usFreq <= 0)
        {
            break;
        }
        ucJ--;
    }

    g_pucModeInfoData[24] = _M_;
    g_pucModeInfoData[25] = _H_;
    g_pucModeInfoData[26] = _z_;
    g_pucModeInfoData[27] = _END_;

    //return g_pucModeInfoData;
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowHDCPEnable(BYTE ucVersion)
{
    g_pucModeInfoData[0] = _H_;
    g_pucModeInfoData[1] = _D_;
    g_pucModeInfoData[2] = _C_;
    g_pucModeInfoData[3] = _P_;
    g_pucModeInfoData[4] = _;

    if(ucVersion == _OFF)
    {
        g_pucModeInfoData[5] = _D_;
        g_pucModeInfoData[6] = _i_;
        g_pucModeInfoData[7] = _s_;
        g_pucModeInfoData[8] = _a_;
        g_pucModeInfoData[9] = _b_;
        g_pucModeInfoData[10] = _l_;
        g_pucModeInfoData[11] = _e_;
        g_pucModeInfoData[12] = _d_;
        g_pucModeInfoData[13] = _END_;
    }
    else
    {
        if((ucVersion & 0x7F) == 0x14)
        {
            g_pucModeInfoData[5] = _1_;
            g_pucModeInfoData[6] = _DOT_;
            g_pucModeInfoData[7] = _4_;
            g_pucModeInfoData[8] = _;

        }
        else if((ucVersion & 0x7F) == 0x22)
        {
            g_pucModeInfoData[5] = _2_;
            g_pucModeInfoData[6] = _DOT_;
            g_pucModeInfoData[7] = _2_;
            g_pucModeInfoData[8] = _;
        }
        g_pucModeInfoData[9] = _E_;
        g_pucModeInfoData[10] = _n_;
        g_pucModeInfoData[11] = _a_;
        g_pucModeInfoData[12] = _b_;
        g_pucModeInfoData[13] = _l_;
        g_pucModeInfoData[14] = _e_;
        g_pucModeInfoData[15] = _d_;

        if((ucVersion & 0x80) == 0x80)
        {
            g_pucModeInfoData[16] = _;
            g_pucModeInfoData[17] = _R_;
            g_pucModeInfoData[18] = _e_;
            g_pucModeInfoData[19] = _p_;
            g_pucModeInfoData[20] = _e_;
            g_pucModeInfoData[21] = _a_;
            g_pucModeInfoData[22] = _t_;
            g_pucModeInfoData[23] = _e_;
            g_pucModeInfoData[24] = _r_;
            g_pucModeInfoData[25] = _END_;
        }
        else
        {
            g_pucModeInfoData[16] = _;
            g_pucModeInfoData[17] = _S_;
            g_pucModeInfoData[18] = _i_;
            g_pucModeInfoData[19] = _n_;
            g_pucModeInfoData[20] = _k_;
            g_pucModeInfoData[21] = _END_;
        }
    }
    //return g_pucModeInfoData;
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowResolutionStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = OsdPropVideoResolution();

    if(ucI != 0)
    {
        g_pucModeInfoData[0] = tSTRING_RESOLUTION_TABLE[ucI][1];
        g_pucModeInfoData[1] = tSTRING_RESOLUTION_TABLE[ucI][2];
        g_pucModeInfoData[2] = tSTRING_RESOLUTION_TABLE[ucI][3];
        g_pucModeInfoData[3] = tSTRING_RESOLUTION_TABLE[ucI][4];
        g_pucModeInfoData[4] = tSTRING_RESOLUTION_TABLE[ucI][5];
        // g_pucModeInfoData[5] = _END_;

        g_pucModeInfoData[5] = _AT_0_;
        g_pucModeInfoData[6] = _AT_1_;

        usTemp = GET_INPUT_TIMING_VFREQ();

        ucI = 8;
        g_pucModeInfoData[9] = _DOT_;
        g_pucModeInfoData[10] = usTemp % 10 + _0_;
        g_pucModeInfoData[11] = _H_;
        g_pucModeInfoData[12] = _z_;
        g_pucModeInfoData[13] = _END_;

        usTemp /= 10;

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }
    }
    else
    {
        if(GET_INPUT_TIMING_HWIDTH() >= 1000)
        {
            ucI = 3;
        }
        else
        {
            ucI = 2;
        }

        usTemp = GET_INPUT_TIMING_HWIDTH();
        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }

        if(GET_INPUT_TIMING_HWIDTH() >= 1000)
        {
            g_pucModeInfoData[4] = _x_;
        }
        else
        {
            g_pucModeInfoData[3] = _x_;
        }

        usTemp = GET_INPUT_TIMING_VHEIGHT();

        if((GET_INPUT_TIMING_HWIDTH() >= 1000) && (GET_INPUT_TIMING_VHEIGHT() >= 1000))
        {
            ucI = 8;
            g_pucModeInfoData[9] = _AT_0_;
            g_pucModeInfoData[10] = _AT_1_;

        }
        else if((GET_INPUT_TIMING_HWIDTH() < 1000) && (GET_INPUT_TIMING_VHEIGHT() < 1000))
        {
            ucI = 6;
            g_pucModeInfoData[7] = _AT_0_;
            g_pucModeInfoData[8] = _AT_1_;
        }
        else
        {
            ucI = 7;
            g_pucModeInfoData[8] = _AT_0_;
            g_pucModeInfoData[9] = _AT_1_;
        }

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }

        usTemp = GET_INPUT_TIMING_VFREQ();

        if((GET_INPUT_TIMING_HWIDTH() >= 1000) && (GET_INPUT_TIMING_VHEIGHT() >= 1000))
        {
            ucI = 12;
        }
        else if((GET_INPUT_TIMING_HWIDTH() < 1000) && (GET_INPUT_TIMING_VHEIGHT() < 1000))
        {
            ucI = 10;
        }
        else
        {
            ucI = 11;
        }

        // Modify V freq. string position for V freq. > 100Hz
        if(usTemp >= 1000)
        {
            ++ucI;
        }

        g_pucModeInfoData[ucI + 1] = _DOT_;
        g_pucModeInfoData[ucI + 2] = (usTemp % 10) + _0_;
        g_pucModeInfoData[ucI + 3] = _H_;
        g_pucModeInfoData[ucI + 4] = _z_;
        g_pucModeInfoData[ucI + 5] = _END_;

        usTemp /= 10;

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }
    }

    //return g_pucModeInfoData;
}
#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor, BYTE ucLanguage)
{
    WORD usTemp = 0;
    BYTE ucI = 0;

    usTemp = ScalerFreeSyncGetFreeSyncInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_MIN_VFREQ);

    if(usTemp == 0)
    {
        usTemp = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
    }

    g_pucModeInfoData[0] = _F_;
    g_pucModeInfoData[1] = _r_;
    g_pucModeInfoData[2] = _e_;
    g_pucModeInfoData[3] = _e_;
    g_pucModeInfoData[4] = _S_;
    g_pucModeInfoData[5] = _y_;
    g_pucModeInfoData[6] = _n_; // clear
    g_pucModeInfoData[7] = _c_; // clear
    g_pucModeInfoData[8] = _; // clear
    g_pucModeInfoData[9] = _R_;
    g_pucModeInfoData[10] = _a_;
    g_pucModeInfoData[11] = _n_;
    g_pucModeInfoData[12] = _g_;
    g_pucModeInfoData[13] = _e_;
    g_pucModeInfoData[14] = _COLON_;
    g_pucModeInfoData[15] = _;
    g_pucModeInfoData[16] = _; // clear
    g_pucModeInfoData[17] = _; // clear
    g_pucModeInfoData[18] = _; // clear
    ucI = 18;

    while(_TRUE)
    {
        g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
        usTemp /= 10;

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }

    usTemp = ScalerFreeSyncGetFreeSyncInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_MAX_VFREQ);

    if(usTemp == 0)
    {
        usTemp = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
    }

    g_pucModeInfoData[19] = _SLINE_;
    g_pucModeInfoData[20] = _; // clear
    g_pucModeInfoData[21] = _; // clear
    g_pucModeInfoData[22] = _; // clear
    g_pucModeInfoData[23] = _; // clear
    ucI = 23;

    while(_TRUE)
    {
        g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
        usTemp /= 10;

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[24] = _H_;
    g_pucModeInfoData[25] = _z_;
    g_pucModeInfoData[26] = _END_;
    OsdPropPutString(ucRow, ucCol, ucFptsSelect, _STRING_FREESYNC_SUPPORT_V_RANGE,  ucColor,  ucLanguage);
}
#endif
#if(_DP_DEBUG_MSG == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowDpInfoStringAddress(BYTE Index)
{
    BYTE ucI = 0;
    BYTE ucIndex = 0;
    EnumSourceSearchPort ucPortSel = SysSourceGetInputPort();
    if(SysModeGetModeState() != _MODE_STATUS_ACTIVE)
    {
        ucPortSel = GET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT();

        if(Index == _STRING_DP_INFO)
        {
            g_pucModeInfoData[ucIndex++] = _P_;
            g_pucModeInfoData[ucIndex++] = _W_0;
            g_pucModeInfoData[ucIndex++] = _W_1;
            g_pucModeInfoData[ucIndex++] = _COLON_;
            g_pucModeInfoData[ucIndex++] = _0_ + ScalerDpGetPowerStatus(ucPortSel);
            g_pucModeInfoData[ucIndex++] = _COMMA_;
        }
    }

    if(Index == _STRING_DP_INFO)
    {
        switch(ScalerDpGetLaneCount(ucPortSel))
        {
            case _DP_LINK_1_LANE:
                g_pucModeInfoData[ucIndex++] = _1_;
                break;
            case _DP_LINK_2_LANE:
                g_pucModeInfoData[ucIndex++] = _2_;
                break;
            case _DP_LINK_4_LANE:
                g_pucModeInfoData[ucIndex++] = _4_;
                break;
            default:
                g_pucModeInfoData[ucIndex++] = _0_;
                break;
        }
        g_pucModeInfoData[ucIndex++] = _L_;
        g_pucModeInfoData[ucIndex++] = _a_;
        g_pucModeInfoData[ucIndex++] = _n_;
        g_pucModeInfoData[ucIndex++] = _e_;
        switch(ScalerDpGetLinkRate(ucPortSel))
        {
            case _DP_LINK_RBR:
                g_pucModeInfoData[ucIndex++] = _R_;
                g_pucModeInfoData[ucIndex++] = _B_;
                g_pucModeInfoData[ucIndex++] = _R_;
                break;
            case _DP_LINK_HBR:
                g_pucModeInfoData[ucIndex++] = _H_;
                g_pucModeInfoData[ucIndex++] = _B_;
                g_pucModeInfoData[ucIndex++] = _R_;
                break;
            case _DP_LINK_HBR2:
                g_pucModeInfoData[ucIndex++] = _H_;
                g_pucModeInfoData[ucIndex++] = _B_;
                g_pucModeInfoData[ucIndex++] = _R_;
                g_pucModeInfoData[ucIndex++] = _2_;
                break;
             default:
                g_pucModeInfoData[ucIndex++] = _X_;
                g_pucModeInfoData[ucIndex++] = _X_;
                g_pucModeInfoData[ucIndex++] = _X_;
                g_pucModeInfoData[ucIndex++] = _X_;
                break;
        }

        g_pucModeInfoData[ucIndex++] = _COMMA_;
    }
    else if(Index == _STRING_DP_INFO_2)
    {
        g_pucModeInfoData[ucIndex++] = _S_;
        g_pucModeInfoData[ucIndex++] = _w_0;
        g_pucModeInfoData[ucIndex++] = _w_1;
        g_pucModeInfoData[ucIndex++] = _i_;
        g_pucModeInfoData[ucIndex++] = _n_;
        g_pucModeInfoData[ucIndex++] = _g_;
        g_pucModeInfoData[ucIndex++] = _;
        for(ucI=_DP_LANE_0 ; ucI<=_DP_LANE_3 ;ucI++)
        {
            g_pucModeInfoData[ucIndex++] = _LEFT_BRACE_;
            switch(ScalerDpGetLaneVoltageSwingLv(ucPortSel,ucI))
            {
                case _DP_LINK_VOLTAGE_SWING_LEVEL_0:
                    g_pucModeInfoData[ucIndex++] = _0_+0;
                    break;
                case _DP_LINK_VOLTAGE_SWING_LEVEL_1:
                    g_pucModeInfoData[ucIndex++] = _0_+1;
                    break;
                case _DP_LINK_VOLTAGE_SWING_LEVEL_2:
                    g_pucModeInfoData[ucIndex++] = _0_+2;
                    break;
                case _DP_LINK_VOLTAGE_SWING_LEVEL_3:
                    g_pucModeInfoData[ucIndex++] = _0_+3;
                    break;
                default:
                break;
            }
            g_pucModeInfoData[ucIndex++] = _COMMA_;
            switch(ScalerDpGetLanePreEmpLv(ucPortSel,ucI))
            {
                case _DP_LINK_PREEMPHASIS_LEVEL_0:
                    g_pucModeInfoData[ucIndex++] = _0_+0;
                    break;
                case _DP_LINK_PREEMPHASIS_LEVEL_1:
                    g_pucModeInfoData[ucIndex++] = _0_+1;
                    break;
                case _DP_LINK_PREEMPHASIS_LEVEL_2:
                    g_pucModeInfoData[ucIndex++] = _0_+2;
                    break;
                case _DP_LINK_PREEMPHASIS_LEVEL_3:
                    g_pucModeInfoData[ucIndex++] = _0_+2;
                    break;
                default:
                break;
            }
            g_pucModeInfoData[ucIndex++] = _RIGHT_BRACE_;
        }
    }

    g_pucModeInfoData[ucIndex++] = _END_;

    //return g_pucModeInfoData;
}
#endif


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropVideoResolution(void)
{
    bit bVideoTiming = _FALSE;
    BYTE ucI = 0;

    if(GET_INPUT_TIMING_VFREQ() > 620)
    {
        return _FALSE;
    }

    if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
    {
        bVideoTiming = _TRUE;
    }
#if(_VGA_SUPPORT == _ON)
    else if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_YPBPR)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif
#if(_DVI_SUPPORT == _ON)
    else if((SysSourceGetSourceType() == _SOURCE_DVI))
    {
#if(_DIGITAL_PORT_SUPPORT == _ON)
        if(ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort()) == _HDCP_NONE)
        {
            bVideoTiming = _FALSE;
        }
        else
        {
            bVideoTiming = _TRUE;
        }
#endif
    }
#endif
#if(_HDMI_SUPPORT == _ON)
    else if(SysSourceGetSourceType() == _SOURCE_HDMI)
    {
        if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _FALSE)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif
#if(_DP_SUPPORT == _ON)
    else if(SysSourceGetSourceType() == _SOURCE_DP)
    {
        if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _FALSE)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif

    if(bVideoTiming == _TRUE)
    {
        for(ucI = 1; ucI < 8; ucI++)
        {
            if(GET_INPUT_TIMING_VHEIGHT() == tSTRING_RESOLUTION_TABLE[ucI][0])
            {
                if((tSTRING_RESOLUTION_TABLE[ucI][0] == 480) && (GET_INPUT_TIMING_HWIDTH() == 848))
                {
                    return _FALSE;
                }

                if(((tSTRING_RESOLUTION_TABLE[ucI][0] == 240) ||
                    (tSTRING_RESOLUTION_TABLE[ucI][0] == 288) ||
                    (tSTRING_RESOLUTION_TABLE[ucI][0] == 540)) &&
                   (GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE))
                {
                    return _FALSE;
                }

                return ucI;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropGetFontPointer(BYTE ucPointerSelect)
{
    BYTE ucPointer = 0;

    if(ucPointerSelect == _PFONT_PAGE_0)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_0();
    }
    else if(ucPointerSelect == _PFONT_PAGE_1)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_1();
    }
    else if(ucPointerSelect == _PFONT_PAGE_2)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_1)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_1);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_2)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_2);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_3)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_3);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_4)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_4);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_5)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_5);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_6)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_6);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }

    return ucPointer;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropSetFontPointer(BYTE ucPointerSelect, BYTE ucPointer)
{
    ucPointer++;

    if(ucPointerSelect == _PFONT_PAGE_0)
    {
        if(ucPointer > _OSD_PAGE_0_END)
        {
            ucPointer = _OSD_PAGE_0_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_1)
    {
        if(ucPointer > _OSD_PAGE_1_END)
        {
            ucPointer = _OSD_PAGE_1_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_2)
    {
        if(ucPointer > _OSD_PAGE_2_END)
        {
            ucPointer = _OSD_PAGE_2_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_1)
    {
        if(ucPointer > _SUB_PAGE_ITEM_1_END)
        {
            ucPointer = _SUB_PAGE_ITEM_1;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_2)
    {
        if(ucPointer > _SUB_PAGE_ITEM_2_END)
        {
            ucPointer = _SUB_PAGE_ITEM_2;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_3)
    {
        if(ucPointer > _SUB_PAGE_ITEM_3_END)
        {
            ucPointer = _SUB_PAGE_ITEM_3;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_4)
    {
        if(ucPointer > _SUB_PAGE_ITEM_4_END)
        {
            ucPointer = _SUB_PAGE_ITEM_4;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_5)
    {
        if(ucPointer > _SUB_PAGE_ITEM_5_END)
        {
            ucPointer = _SUB_PAGE_ITEM_5;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_6)
    {
        if(ucPointer > _SUB_PAGE_ITEM_6_END)
        {
            ucPointer = _SUB_PAGE_ITEM_6;
        }
    }


    return ucPointer;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropFontDataToSram(BYTE ucFptsSelect, BYTE *ucpArray, BYTE ucRotateType)
{
    if(ucFptsSelect == _PFONT_PAGE_0)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_0() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_0() >= _OSD_PAGE_0_END)
        {
            SET_OSD_INFO_FONT_POINTER_0(_OSD_PAGE_0_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_0(GET_OSD_INFO_FONT_POINTER_0() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_1)
    {

        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_1() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_1() >= _OSD_PAGE_1_END)
        {
            SET_OSD_INFO_FONT_POINTER_1(_OSD_PAGE_1_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_1(GET_OSD_INFO_FONT_POINTER_1() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_2)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _OSD_PAGE_2_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_OSD_PAGE_2_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_1)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_1_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_1);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_2)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_2_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_2);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_3)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_3_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_3);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_4)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_4_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_4);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_5)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_5_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_5);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_6)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_6_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_6);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }

}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage)
{
    BYTE *pucArray = OsdPropGetStringTableAddress(ucString);
    bit bCenterFlag = _FALSE;
    bit bNextLineFlag = _FALSE;
    BYTE pucpTemp[27] = {0};
    BYTE ucElementCount = 0;
    BYTE ucColBackup = ucCol;

    pData[0] = ucLanguage;
    while(pData[0] != 0)
    {
        if(pucArray[0] == _END_)
        {
            pData[0]--;
        }
        pucArray++;
    }

    do
    {
        bNextLineFlag = _FALSE;
        memset(pData, 0x00, _DATA_ITEM_LENGTH);
        ucElementCount = 0;

        PDATA_WORD(5) = OsdPropGetFontPointer(ucFptsSelect);

        if(GET_OSD_INFO_STRING_MODE_LENGTH() != 0)
        {
            while((*(pucArray + ucElementCount) != _END_) &&
                  (*(pucArray + ucElementCount) != _NEXT_LINE))// calculate totwl string width
            {
                pData[2] = *(pucArray + ucElementCount);

                switch(pData[2])
                {
                    default:
                        PDATA_WORD(6) = 0;
                        break;

                    case _FONT_SELECT_EXT1:
                        PDATA_WORD(6) = _FONT_SELECT_OFFSET1;
                        break;

                    case _FONT_SELECT_EXT2:
                        PDATA_WORD(6) = _FONT_SELECT_OFFSET2;
                        break;

                    //if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                    /*case _FONT_SELECT_EXT3:
                        PDATA_WORD(6) = _FONT_SELECT_OFFSET3;
                        break;*/
                }

                if(PDATA_WORD(6) != 0)
                {
                    ucElementCount++;
                    pData[2] = *(pucArray + ucElementCount);
                }

                if((PDATA_WORD(6) + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                {
                    pData[1] += tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + PDATA_WORD(6)];
                }
                else
                {
                    pData[1] += tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                }

                ucElementCount++;
            }

            // String col size
            pData[0] = (pData[1] / 12) + (((pData[1] % 12) > 0) ? 1 : 0); // total pixels / 12 (round up)

            if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)// center-aligned
            {
                // add one font if centered width and actual sting width is not both even or both odd
                if((((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 0) && ((pData[0] % 2) == 1)) ||
                   (((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 1) && ((pData[0] % 2) == 0)))
                {
                    pData[0]++;
                }

                pData[9] = ((pData[0] * 12) - pData[1]) / 2;// total center-aligned pixels - total string pixels / 2
            }
            else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)// right aligned
            {
                pData[9] = (pData[0] * 12) - pData[1];// count right-aligned pixels
            }

            if(pData[9] != 0)// left-aligned
            {
                bCenterFlag = _TRUE;
            }
        }
        ucElementCount = pData[1] = pData[0] = 0;

        // reorder
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

        while((*(pucArray + ucElementCount) != _END_) &&
              (*(pucArray + ucElementCount) != _NEXT_LINE))
        {
            switch(*(pucArray + ucElementCount))
            {
                case _END_:
                    break;

                default:
                    if(pData[5] == 0)// pixel count = 0 ????
                    {
                        pData[2] = *(pucArray + ucElementCount);

                        if(pData[2] == _FONT_BLANK_PIXEL)
                        {
                            pData[5] = *(pucArray + ucElementCount + 1);

                            pData[2] = _;
                        }

                        if(bCenterFlag == _TRUE)
                        {
                            pData[2] = _;
                        }
                    }
                    else
                    {
                        pData[2] = _;
                    }

                    switch(pData[2])
                    {
                        default:
                            PDATA_WORD(6) = 0;
                            break;

                        case _FONT_SELECT_EXT1:
                            PDATA_WORD(6) = _FONT_SELECT_OFFSET1;
                            break;

                        case _FONT_SELECT_EXT2:
                            PDATA_WORD(6) = _FONT_SELECT_OFFSET2;
                            break;

                        //if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                        /*case _FONT_SELECT_EXT3:
                            PDATA_WORD(6) = _FONT_SELECT_OFFSET3;
                            break;*/
                    }

                    if(PDATA_WORD(6) != 0)
                    {
                        ucElementCount++;
                        pData[2] = *(pucArray + ucElementCount);
                    }

                    if((PDATA_WORD(6) + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + PDATA_WORD(6)];

                            if(bCenterFlag == _TRUE)
                            {
                                pData[3] = pData[9];
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                            pData[5] -= pData[3];
                        }
                    }
                    else
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];

                            if(bCenterFlag == _TRUE)
                            {
                                pData[3] = pData[9];
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                            pData[5] -= pData[3];
                        }
                    }

                    if(pData[5] == 0)
                    {
                        if((*(pucArray + ucElementCount) != _FONT_BLANK_PIXEL))
                        {
                            ucElementCount++;

                            if(bCenterFlag == _TRUE)
                            {
                                ucElementCount = 0;
                            }
                        }
                        else
                        {
                            ucElementCount += 2;
                        }
                    }
                    break;
            }

            if(pData[6] == 0)
            {
                pData[6] = pData[3];
            }


            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);    // first bits shift direction: left shift
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2)); // left bits shift direction: rigth shift
            SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pData[3] - pData[6]) << 4) | pData[6]); // first bits shift and second bits shift

            pData[8] = ucElementCount;
            pData[7] = pData[6];

            for(pData[0] = 0; pData[0] < 9; pData[0]++)
            {
                SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0); // restart from last three bytes

                if(PDATA_WORD(6) == _GLOBAL_FONT_END_OFFSET)
                {
                    if(pData[2] >= _GLOBAL_FONT_END)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                    }
                    else
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 2)));
                    }
                }
                else if(PDATA_WORD(6) > _GLOBAL_FONT_END_OFFSET)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                }
                else// if(ucOffset[0] < _GLOBAL_FONT_END_OFFSET)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 2)));
                }

                ucElementCount = pData[8];
                pData[6] = pData[7];

                if((pData[6] == 12) || (*(pucArray + ucElementCount) == _END_) || (*(pucArray + ucElementCount) == _NEXT_LINE))
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                }

                while((pData[6] < 12) &&
                      (*(pucArray + ucElementCount) != _END_) &&
                      (*(pucArray + ucElementCount) != _NEXT_LINE))
                {
                    SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pData[6] << 4) | pData[6]); // third bits shift and left bits shift

                    if(pData[5] == 0)
                    {
                        pData[1] = *(pucArray + ucElementCount);

                        if(pData[1] == _FONT_BLANK_PIXEL)
                        {
                            pData[5] = *(pucArray + ucElementCount + 1);

                            pData[1] = _;
                        }
                    }
                    else
                    {
                        pData[1] = _;
                    }

                    if((pData[1] == _FONT_SELECT_EXT1) ||
                       (pData[1] == _FONT_SELECT_EXT2))
                    {
                        PDATA_WORD(7) = (pData[1] == _FONT_SELECT_EXT1) ? _FONT_SELECT_OFFSET1 : _FONT_SELECT_OFFSET2;
                        ucElementCount++;
                        pData[1] = *(pucArray + ucElementCount);
                    }
                    else
                    {
                        PDATA_WORD(7) = 0;
                    }

                    if((PDATA_WORD(7) + pData[1]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[1] + PDATA_WORD(7)];
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                        }
                    }
                    else
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                        }
                    }

                    ucElementCount ++;
                    pData[6] += pData[3];

                    if(PDATA_WORD(7) == _GLOBAL_FONT_END_OFFSET)
                    {
                        if(pData[1] >= _GLOBAL_FONT_END)
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                        }
                        else
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 2)));
                        }
                    }
                    else if(PDATA_WORD(7) > _GLOBAL_FONT_END_OFFSET)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                    }
                    else// if(ucOffset[1] < _GLOBAL_FONT_END_OFFSET)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 2)));
                    }
                }

                pucpTemp[pData[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucpTemp[pData[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucpTemp[pData[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            }

            if(pData[6] <= 12)
            {
                pData[6] = 0;
            }
            else
            {
                pData[6] = pData[6] - 12;

                if(ucElementCount >= 1)
                {
                    ucElementCount--;
                }
                if(ucElementCount != 0)
                {
                    pData[1] = *(pucArray + ucElementCount - 1);

                    if((pData[1] == _FONT_SELECT_EXT1) ||
                       (pData[1] == _FONT_SELECT_EXT2))
                    {
                        ucElementCount--;
                    }
                }
            }

            // Write the pro font data to sram
            OsdPropFontDataToSram(ucFptsSelect, pucpTemp, GET_OSD_ROTATE_STATUS());

            // Record the length (coloumn) of prop string
            pData[4]++;

            // Only shift for the first word
            bCenterFlag = _FALSE;

        }// End of while(*(pArray + stringcnt) != _END_)



        if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
        {
            ucCol = ucColBackup  + ((((GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]) / 2) < 0) ? 0 : ((GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]) / 2));
        }
        else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
        {
            ucCol = ucColBackup  + (((GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]) < 0) ? 0 : (GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]));
        }

        ScalerOsdSramAddressCount(ucRow, ucCol, _OSD_BYTEALL);
        for(pData[0] = 0; pData[0] < pData[4]; pData[0]++)
        {
#if(_OSD_FONT_MODE_FORCE_256_511 == _ON)
            ScalerOsdDataPort(_OSD_MODE_BYTE0_256_511);
#else
            ScalerOsdDataPort((PDATA_WORD(5) < 256) ? _OSD_MODE_BYTE0 : _OSD_MODE_BYTE0_256_511);
#endif // End of #if(_OSD_FONT_MODE_FORCE_256_511 == _ON)
            ScalerOsdDataPort(PDATA_WORD(5) & 0xFF);
            ScalerOsdDataPort(ucColor);

            PDATA_WORD(5) = OsdPropSetFontPointer(ucFptsSelect, PDATA_WORD(5));
        }


        if(*(pucArray + ucElementCount) == _NEXT_LINE)
        {
            // Start the next line from pArray
            pucArray += ucElementCount + 1;
            ucRow++;

            bNextLineFlag = _TRUE;
        }

    }while(bNextLineFlag == _TRUE);

    CLR_OSD_INFO_STRING_MODE();
    CLR_OSD_INFO_STRING_MODE_LENGTH();
}



//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage)
{
    SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
    SET_OSD_INFO_STRING_MODE_LENGTH(ucWidth);

    OsdPropPutString(ucRow, ucCol, ucFptsSelect, ucString, ucColor, ucLanguage);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE ucI = 0;
    BYTE pucDataSN[17] = {0};

    pucDataSN[5] = (_0_ + (ulValue / 100000));
    pucDataSN[4] = (_0_ + (ulValue % 100000 / 10000));
    pucDataSN[3] = (_0_ + (ulValue % 10000) / 1000);
    pucDataSN[2] = (_0_ + (ulValue % 1000) / 100);
    pucDataSN[1] = (_0_ + (ulValue % 100) / 10);
    pucDataSN[0] = (_0_ + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[5 - ucIndex] != ((bit)(ucPar & _BIT1) ? _ : _0_))
        {
            ucIndex = 5 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && ((bit)(ucPar & 0x02) == 0))
    {
        ucIndex = 0;
    }

    if((bit)(ucPar & _BIT1) != 0)
    {
        ucTemp = (ucPar & 0x70) >> 4;
        ucIndex = (ucPar & 0x70) >> 4;
    }
    else
    {
        ucTemp = (ucPar & 0x70) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    for(ucI = 0; ucI <= ucTemp; ucI++)
    {
        if(ucIndex >= ucTemp)
        {
            pucDataSN[ucI + 8] = pucDataSN[ucIndex - ucI];
        }
        else
        {
            if(ucI < (ucTemp - ucIndex))
            {
                pucDataSN[ucI + 8] = 0x00;
            }
            else
            {
                pucDataSN[ucI + 8] = pucDataSN[ucIndex - (ucI - (ucTemp - ucIndex))];
            }
        }
    }
    if((ucPar & 0x01) == _ALIGN_LEFT) // Align Right
    {
        pucDataSN[8 + ucTemp + 1] = _; // clear
        pucDataSN[8 + ucTemp + 2] = _; // clear
        pucDataSN[8 + ucTemp + 3] = _END_;
    }
    else
    {
        pucDataSN[8 + ucTemp + 1] = _END_;
    }
    g_pucShowNumberAddress = &pucDataSN[8];

    if((ucPar & 0x01) == _ALIGN_RIGHT)        // Align Right
    {
        ScalerOsdSramDataValue(ROW(ucRow), COL(ucCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), 0x4C, _OSD_BYTE0);
        ScalerOsdSramDataValue(ROW(ucRow), COL(ucCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), 0x00, _OSD_BYTE1);
        ScalerOsdSramDataValue(ROW(ucRow), COL(ucCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), ((FG_COLOR(ucColor & 0x0F) << 4) | BG_COLOR(ucColor & 0x0F)), _OSD_BYTE2);
    
        OsdPropPutString(ucRow, ROW(ucCol - ucTemp), ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
    else
    {
        ScalerOsdSramDataValue(ROW(ucRow), COL(ucCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), 0x4C, _OSD_BYTE0);
        ScalerOsdSramDataValue(ROW(ucRow), COL(ucCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), 0x00, _OSD_BYTE1);
        ScalerOsdSramDataValue(ROW(ucRow), COL(ucCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), ((FG_COLOR(ucColor & 0x0F) << 4) | BG_COLOR(ucColor & 0x0F)), _OSD_BYTE2);
    
        OsdPropPutString(ucRow, ucCol, ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
}
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)            
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowNumber_float(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE ucI = 0;
    BYTE pucDataSN[16] = {0};
	BYTE ucdecimal=0;
    
	ucdecimal =(_0_ + (ulValue%10));
	ulValue = ulValue/10;

    pucDataSN[5] = (_0_ + (ulValue / 100000));
    pucDataSN[4] = (_0_ + (ulValue % 100000 / 10000));
    pucDataSN[3] = (_0_ + (ulValue % 10000) / 1000);
    pucDataSN[2] = (_0_ + (ulValue % 1000) / 100);
    pucDataSN[1] = (_0_ + (ulValue % 100) / 10);
    pucDataSN[0] = (_0_ + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[5 - ucIndex] != ((bit)(ucPar & _BIT1) ? _ : _0_))
        {
            ucIndex = 5 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && ((bit)(ucPar & 0x02) == 0))
    {
        ucIndex = 0;
    }

    if((bit)(ucPar & _BIT1) != 0)
    {
        ucTemp = (ucPar & 0x70) >> 4;
        ucIndex = (ucPar & 0x70) >> 4;
    }
    else
    {
        ucTemp = (ucPar & 0x70) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    for(ucI = 0; ucI <= ucTemp; ucI++)
    {
        if(ucIndex >= ucTemp)
        {
            pucDataSN[ucI + 8] = pucDataSN[ucIndex - ucI];
        }
        else
        {
            if(ucI < (ucTemp - ucIndex))
            {
                pucDataSN[ucI + 8] = 0x00;
            }
            else
            {
                pucDataSN[ucI + 8] = pucDataSN[ucIndex - (ucI - (ucTemp - ucIndex))];
            }
        }
    }
    if((ucPar & 0x01) == _ALIGN_LEFT) // Align Right
    {
        pucDataSN[8 + ucTemp + 1] = _; // clear
        pucDataSN[8 + ucTemp + 2] = _; // clear
        pucDataSN[8 + ucTemp + 3]   = _DOT_;
        pucDataSN[8 + ucTemp + 4] = ucdecimal;
        pucDataSN[8 + ucTemp + 5] = _END_;
        
    }
    else
    {
        pucDataSN[8 + ucTemp + 1]   = _DOT_;
        pucDataSN[8 + ucTemp + 2] = ucdecimal;
        pucDataSN[8 + ucTemp + 3] = _END_;
        
    }
    g_pucShowNumberAddress = &pucDataSN[8];

    if((ucPar & 0x01) == _ALIGN_RIGHT)        // Align Right
    {
        OsdPropPutString(ucRow, ROW(ucCol - ucTemp), ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
    else
    {
        OsdPropPutString(ucRow, ucCol, ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
}
#endif
#if(_ARM_MCU_CALIBRATION_SUPPORT)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowNumberPercentage(BYTE ucRow, BYTE ucCol, DWORD usValue , bit bDecimalpointFlag, BYTE ucFontPoint, BYTE ucColor)
{
    BYTE pucData[7] = {0};

	if(usValue == 0)
	{
	    pucData[0] = _0_;
	    pucData[1] = _END_;
	}
	else
    {
		if(bDecimalpointFlag == _TRUE)
		{
		    pucData[0] = ((((usValue % 100000) / 10000) > 0) ? (_0_ + ((usValue % 100000) / 10000)) : U0020);
		    pucData[1] = ((((usValue % 10000) / 1000) > 0) ? (_0_ + ((usValue % 10000) / 1000)) : U0020);
		    pucData[2] = (_0_ + ((usValue % 1000) / 100));
            // print "."
		    pucData[3] = _DOT_;
		    pucData[4] = (_0_ + ((usValue % 100) / 10));
		    pucData[5] = (_0_ + (usValue % 10));
            // print "%"
		    pucData[6] = _Percentage;
		    pucData[7] = _END_;
		}
        else
        {
            pucData[0] = ((((usValue % 1000) / 100) > 0) ? (_0_ + ((usValue % 1000) / 100)) : U0020);
            pucData[1] = ((((usValue % 100) / 10) > 0) ? (_0_ + ((usValue % 100) / 10)) : ((((usValue % 1000) / 100) > 0) ? (_0_ + ((usValue % 100) / 10)) : U0020));
            pucData[2] = (_0_ + (usValue % 10));
            // print "%"
            pucData[3] = _Percentage;
            pucData[4] = _END_;
	    }
    }

    g_pucShowNumberPercentageAddress = pucData;

    OsdPropPutString(ucRow, ucCol, ucFontPoint, _STRING_SHOW_NUMBER_PERCENTAGE, ucColor, _ENGLISH);
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowPanelUseTimeStringAddress(void)
{
    DWORD ulUseTime;
    BYTE ucDest;

    ulUseTime = (GET_SYSTEM_RUN_TIME_HOUR() + GET_SYSTEM_RUN_TIME_OVERFLOW()*65535);

    // print Time in "xxxxxx" format
    ucDest = 0;
    g_pucModeInfoData[ucDest++] = (ulUseTime < 100000) ? _ :
                                  (_0_ + ((ulUseTime / 100000) % 10));
    g_pucModeInfoData[ucDest++] = (ulUseTime < 10000) ? _ :
                                  (_0_ + ((ulUseTime / 10000) % 10));
    g_pucModeInfoData[ucDest++] = (ulUseTime < 1000) ? _ :
                                  (_0_ + ((ulUseTime / 1000) % 10));
    g_pucModeInfoData[ucDest++] = (ulUseTime < 100) ? _ :
                                  (_0_ + ((ulUseTime / 100) % 10));
    g_pucModeInfoData[ucDest++] = (ulUseTime < 10) ? _ :
                                  (_0_ + ((ulUseTime / 10) % 10));
    g_pucModeInfoData[ucDest++] = (_0_ + (ulUseTime % 10));

    g_pucModeInfoData[ucDest++] = _LEFT_BRACE_;
    g_pucModeInfoData[ucDest++] = _h_;
    g_pucModeInfoData[ucDest++] = _RIGHT_BRACE_;
    g_pucModeInfoData[ucDest++] = _END_;

    //return g_pucModeInfoData;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowPanelluminanceStringAddress(void)
{
    WORD temp = 0;

    temp = UserAdjustQAGetCurrPanelLux(_BK_SENSOR_MIDDLE);

    //g_pucModeInfoData[0] = _L_;
    //g_pucModeInfoData[1] = _u_;
    //g_pucModeInfoData[2] = _m_;
    //g_pucModeInfoData[3] = _i_;
    //g_pucModeInfoData[4] = _n_;
    //g_pucModeInfoData[5] = _;
    //g_pucModeInfoData[0] = _COLON_;
    DebugMessageUart("temp", temp);
    g_pucModeInfoData[0] = ((((temp % 10000) / 1000) > 0) ? (_0_ + (temp % 10000) / 1000) : _);
    g_pucModeInfoData[1] = (_0_ + (temp % 1000) / 100);
    g_pucModeInfoData[2] = (_0_ + (temp % 100) / 10);
    g_pucModeInfoData[3] = (_0_ + (temp % 10));

    g_pucModeInfoData[4] = _c_;
    g_pucModeInfoData[5] = _d_;

    g_pucModeInfoData[6] = _AND_;
    g_pucModeInfoData[7] = _m_;
    g_pucModeInfoData[8] = _2_;
    g_pucModeInfoData[9] = _END_;
   
    //return g_pucModeInfoData;
}

//--------------------------------------------------
// Description  : ASCII:0->48 A->65 a->97
// Input Value  : ASCII Index->RTDNVRamLoadMonitorSNData(x)
// Output Value : RTD Font Index
//--------------------------------------------------
void OsdPropPutShowSpecifiedstringAddress(BYTE usString)
{
    BYTE ucSrc;
    BYTE ucDest;
    BYTE pucDataSN[_SN_BUF_LENGTH];
    
    if(usString == _STRING_FIRMWARE_VERSION)
    {
        ReadFWVersion(&pucDataSN[0], 0);
    }
    else if(usString == _STRING_PRODUCT_ID)
    {
        RTDNVRamLoadMonitorSNData(&pucDataSN[0]);
    }

    ucDest = 0;
    for(ucSrc = 0; ucSrc < _SN_BUF_LENGTH; ucSrc++)
    {
        if(('0'<=pucDataSN[ucSrc])&&(pucDataSN[ucSrc]<='9'))
        {
            g_pucModeInfoData[ucDest++] = pucDataSN[ucSrc] - '0' + _0_;
        } 
        else if(('A'<=pucDataSN[ucSrc])&&(pucDataSN[ucSrc]<='Z'))
        {
            g_pucModeInfoData[ucDest++] = pucDataSN[ucSrc] - 'A' + _A_;

            // 'W' = 0x57
            if(pucDataSN[ucSrc]=='W')
            {
                g_pucModeInfoData[ucDest++] = (pucDataSN[ucSrc] - 'A' + _A_ + 1);
            }
        }    
        else if(('a'<=pucDataSN[ucSrc])&&(pucDataSN[ucSrc]<='z'))
        {
            g_pucModeInfoData[ucDest++] = pucDataSN[ucSrc] - 'a' + _a_;
        }    
        else if(pucDataSN[ucSrc] == '+')
        {
            g_pucModeInfoData[ucDest++] = _SLINE_;
        }
        else if(pucDataSN[ucSrc] == ':')
        {
            g_pucModeInfoData[ucDest++] = _COLON_;
        }
        else if(pucDataSN[ucSrc] == '.')
        {
            g_pucModeInfoData[ucDest++] = _DOT_; 
        }   
        else if(pucDataSN[ucSrc] == '-')
        {
            g_pucModeInfoData[ucDest++] = _SLINE_;
        }
        else if(pucDataSN[ucSrc] == ' ')
    	{
    		g_pucModeInfoData[ucDest++] = U0020;
    	}
    	else
    	{
            g_pucModeInfoData[ucDest++] = _END_;
            break;
    	}
    }

    g_pucModeInfoData[ucDest++] = _END_;
    
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetStringTableAddress(BYTE ucString)
{
    BYTE *pucArray = tsOsdNull;

    switch(ucString)
    {

        case _STRING_IMAGE:
            pucArray = tsOsdImage;
            break;
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
        case _STRING_QA:
            pucArray = tsOsdQA;
            break;
#endif
        case _STRING_FUNCTION_SETTING:
            pucArray = tsOsdFunctionSetting;
            break;

        case _STRING_INFO:
            pucArray = tsOsdInfo;
            break;

        case _STRING_ADVANCE:
            pucArray = tsOsdAdvanced;
            break;

        case _STRING_GAMMA:
            pucArray = tsOsdGamma;
            break;
			
        case _STRING_ALC:
            pucArray = tsOsdALC;
            break;
			
        case _STRING_ALC_X_RAY:
            pucArray = tsOsdXray;
            break;
			
        case _STRING_ALC_CTMRNM:
            pucArray = tsOsdCTMRNM;
            break;
			
        case _STRING_ALC_STAFF_OFFICES:
            pucArray = tsOsdStaffOffices;
            break;
			
        case _STRING_ALC_HOSPITAL_CLINICAL:
            pucArray = tsOsdHospitalClinical;
            break;
			
        case _STRING_ALC_EMERGENCY_MEDICINE:
            pucArray = tsOsdEmergencyMedicine;
            break;
			
        case _STRING_ALC_OPERATING_ROOM:
            pucArray = tsOsdOperatingRoom;
            break;
			
        case _STRING_ALC_AUTO:
            pucArray = tsOsdAuto;
            break;

        case _STRING_COLOR_TEMP:
            pucArray = tsOsdColorTemp;
            break;

        case _STRING_HYBRID:
            pucArray = tsOsdHybrid;
            break;
        case _STRING_BACKLIGJT:
            pucArray = tsOsdBacklight;
            break;
            
        case _STRING_CALIB:
            pucArray = tsOsdCalib;
            break;
            
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
        case _STRING_TEST_IMAGE:
            pucArray = tsOsdTestImage;
            break;
#endif

        case _STRING_DEVIATION:
            pucArray = tsOsdDeviation;
            break;

        case _STRING_LANGUAGE:
            pucArray = tsOsdLanguage;
            break;

        case _STRING_INPUT:
            pucArray = tsOsdInput;
            break;

        case _STRING_AMB_LIGHT:
            pucArray = tsOsdAmbLight;
            break;
        
        case _STRING_REPORT_MODE:
            pucArray = tsOsdReportMode;
            break;

        case _STRING_2HOURS_REMINDER:
            pucArray = tsOsdTime2HoursReminder;
            break;

        case _STRING_FACTORY_RESET:
            pucArray = tsOsdReset;
            break;
			
        case _STRING_AMBIENT_SENSOR:
            pucArray = tsOsdAmbientSensor;
            break;

        case _STRING_BODY_INDUCTION :
            pucArray = tsOsdBodyInduction;
            break;
        case _STRING_GRAVITY_SENSOR :
            pucArray = tsOsdGravitySensor;
            break;
            
        case _STRING_BACKLIGHT_SENSOR :
            pucArray = tsOsdBacklightSensor;
            break;
			
            			
        case _STRING_VERSION:
            pucArray = tsOsdVersion;
            break;
            
        case _STRING_ENERGY_SAVING:
            pucArray = tsOsdEnergySaving;
            break;
		/*	
	    case _STRING_LOGO:
            pucArray = tsOsdLogo;
            break;
	*/
    	case _STRING_OSD_TIME:
            pucArray = tsOsdTime;
            break;
            
    	case _STRING_OSD_ROTATE:
            pucArray = tsOsdRotate;
            break;
            
        case _STIRNG_POSITION:
            pucArray = tsOsdPosition;
            break;
            
        case _STRING_AUTO_ADJUST:
            pucArray = tsOsdAutoAdjust;
            break;
        case _STRING_HPOS:
            pucArray = tsOsdHPosition;
            break;
        case _STRING_VPOS:
            pucArray = tsOsdVPosition;
            break;
        case _STRING_CLOCK:
            pucArray = tsOsdClock;
            break;
        case _STRING_PHASE:
            pucArray = tsOsdPhase;
            break;
            
        case _STRING_POS_H:
            pucArray = tsOsdHPosition;
            break;
            
        case _STRING_POS_V:
            pucArray = tsOsdVPosition;
            break;
            
        case _STRING_UNIFORMITY:
            pucArray = tsOsdUniformity;
            break;

        case _STRING_PCM:
            pucArray = tsOsdPcm;
            break;
			
        case _STRING_OSD:
            pucArray = tsOsdOsd;
            break;

        case _STRING_ASPECT:
            pucArray = tsOsdAspectRatio;
            break;
			
        //case _STRING_OVER_SCAN:
            //pucArray = tsOsdOverScan;
            //break;
			
        case _STRING_SHOW_NUMBER_PERCENTAGE:
            pucArray = g_pucShowNumberPercentageAddress;
            break;
			
			
        case _STRING_MST:
            pucArray = tsOsdMst;
            break;

        case _STRING_LIGHT_BOX:
            pucArray = tsOsdLightBox;
            break;
        /*
        case _STRING_BACKLIGHT:
            pucArray = tsOsdBacklight;
            break;
            */
            
        case _STRING_KVM:
            pucArray = tsOsdKvm;
            break;


        case _STRING_COLOR_SWITCH:
            pucArray = tsOsdColorSwitch;
            break;
            
        case _STRING_LUMIN:
            pucArray = tsOsdIluminance;
            break;

        case _STRING_OSD_LOCK:	
            pucArray = tsOsdOsdLock;
            break;
            
        case _STRING_PASSWORD:	
            pucArray = tsOsdPassWord;
            break;
            
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
        case _STRING_USER_TYPE:
            pucArray = tsOsdType;
            break;

        case _STRING_USER_L_MAX:
            pucArray = tsOsdLightMax;
            break;

        case _STRING_USER_L_MIN:
            pucArray = tsOsdLightMin;
            break;

        case _STRING_USER_LAMB:
            pucArray = tsOsdLamb;
            break;

        case _STRING_USER_VALUE:
            pucArray = tsOsdGamma;
            break;

        case _STRING_USER_SET:	
            pucArray = tsOsdUserSet;
            break;
#endif
        case _STRING_TEMP_USER_R:
            pucArray = tsOsdUserR;
            break;

        case _STRING_TEMP_USER_G:
            pucArray = tsOsdUserG;
            break;

        case _STRING_TEMP_USER_B:	
            pucArray = tsOsdUserB;
            break;
        case _STRING_HYBRID_GRAY:
            pucArray = tsOsdGrayCurve;
            break;
        case _STRING_HYBRID_COLOR:
            pucArray = tsOsdColorCurve;
            break;

            
        case _STRING_WINDOW_1:
            pucArray = tsOsdWindow1;
            break;
  /*          
        case _STRING_PIP_POSITION:
            pucArray = tsOsdPipPosition;
            break;
        
        case _STRING_PIP_SIZE:
            pucArray = tsOsdPipSize;
            break;
			
        case _STRING_PIP_USER_POSITION_H:
            pucArray = tsOsdPipHPosition;
            break;
            
        case _STRING_PIP_USER_POSITION_V:
            pucArray = tsOsdPipVPosition;
            break;
            
        case _STRING_PIP_TRANSPARENCY:
            pucArray = tsOsdPipTransparency;
            break;
		
        case _STRING_RATIO:
            pucArray = tsOsdRatio;
            break;
	*/        
        case _STRING_OSD_POSITON_LB: 
            pucArray = tsOsdPipLB;
            break;
			
        case _STRING_OSD_POSITON_LT:
            pucArray = tsOsdPipLT;
            break;	
        
        case _STRING_OSD_POSITON_RB:
            pucArray = tsOsdPipRB;
            break;
            
        case _STRING_OSD_POSITON_RT:
            pucArray = tsOsdPipRT;
            break;
        
        case _STRING_OSD_POSITON_MIDDLE:
            pucArray = tsOsdPipMID;
            break;
        
        case _STRING_OSD_POSITON_USER:
            pucArray = tsOsdUser;
            break;

        case _STRING_INFO_PRODUCT_ID:
            pucArray = tsOsdInfoProductId;
            break;

        case _STRING_PRODUCT_ID:
            OsdPropPutShowSpecifiedstringAddress(ucString);
            pucArray = g_pucModeInfoData;
            break;
        
        case _STRING_FIRMWARE_VERSION:
            OsdPropPutShowSpecifiedstringAddress(ucString);
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_INFO_TIME:
            pucArray = tsOsdUserTime;
            break;

        case _STRING_INFO_USE_TIME:
            OsdPropGetShowPanelUseTimeStringAddress();
            pucArray = g_pucModeInfoData;
            break;
			
        case _STRING_INFO_PANEL_LUMIN:
            pucArray = tsOsdLumin;
            break;
			
        case _STRING_INFO_PANEL_LUMINANCE:
            OsdPropGetShowPanelluminanceStringAddress();
            pucArray = g_pucModeInfoData;
            break;    

        case _STRING_NOW_RESOLUTION_0:
            OsdPropGetShowResolutionStringAddress();
            pucArray = g_pucModeInfoData;
            break;

        case  _STRING_GAMMA_OFF:
            pucArray = tsOsdOff;
            break;

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
        case _STRING_GAMMA1_8:
            pucArray = tsOsdStr2Dot2;    
            break;

        case _STRING_GAMMA2_0:
            pucArray = tsOsdDicom;    
            break;

        case _STRING_GAMMA2_2:
            pucArray = tsOsdUser;    
            break;
            
        case _STRING_GAMMA2_4:
            pucArray = tsOsdCalib;    
            break;

        case _STRING_GAMMA2_6:    
            pucArray = tsOsdHybrid;    
            break;

#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
        case _STRING_GAMMA1_8:
            pucArray = tsOsdStr2Dot0;    
            break;

        case _STRING_GAMMA2_0:
            pucArray = tsOsdStr2Dot2;    
            break;

        case _STRING_GAMMA2_2:
            pucArray = tsOsdStr2Dot4;    
            break;
            
        case _STRING_GAMMA2_4:
            pucArray = tsOsdStr2Dot6;    
            break;

        case _STRING_GAMMA2_6:    
            pucArray = tsOsdDicom;    
            break;
            
        case _STRING_GAMMA_CALIB:
            pucArray = tsOsdCalib;
            break;
            
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
        case _STRING_GAMMA1_8:
            pucArray = tsOsdStr2Dot2;    
            break;

        case _STRING_GAMMA_DICOM200:
            pucArray = tsOsdDicom200;
            break;
            
        case _STRING_GAMMA_DICOM250:
            pucArray = tsOsdDicom250;
            break;
            
        case _STRING_GAMMA_DICOM300:
            pucArray = tsOsdDicom300;
            break;
            
        case _STRING_GAMMA_DICOM350:
            pucArray = tsOsdDicom350;
            break;

        case _STRING_GAMMA_DICOM400:
            pucArray = tsOsdDicom400;
            break;
            
        case _STRING_GAMMA_DICOM450:
            pucArray = tsOsdDicom450;
            break;

        case _STRING_GAMMA_DICOM500:
            pucArray = tsOsdDicom500;
            break;
            
        case _STRING_GAMMA_DICOM550:
            pucArray = tsOsdDicom550;
            break;

        case _STRING_GAMMA_DICOM600:
            pucArray = tsOsdDicom600;
            break;
            
        case _STRING_GAMMA_CALIB:
            pucArray = tsOsdCalib;
            break;            
#else
#warning "!!!Please Check Gamma define"
#endif
            
        case _STRING_CT_9300:
            pucArray = tsOsdBlue;
            break;

        case _STRING_CT_7500:
            pucArray = tsOsd7500;
            break;

        case _STRING_CT_6500:
            pucArray = tsOsdClear;
            break;

        case _STRING_CT_5800:
            pucArray = tsOsd5800;
            break;

        case _STRING_CT_SRGB:
            pucArray = tsOsdNative;
            break;

        case _STRING_CT_USER:
            pucArray = tsOsdUser;
            break;
            
        case _STRING_OFF:
            pucArray = tsOsdOff;
            break;

        case _STRING_ON:
            pucArray = tsOsdOn;
            break;

        case _STRING_ENGLISH:
            pucArray = tsOsdEnglish;
            break;
            
        case _STRING_FRENCH:
            pucArray = tsOsdFrench;
            break;
            
        case _STRING_GERMAN:
            pucArray = tsOsdGerman;
            break;

        case _STRING_SPANISH: 
            pucArray = tsOsdSpanish;
            break;
            
        case _STRING_PORTUGUESE: 
            pucArray = tsOsdPortuguese;
            break;
            
        case _STRING_ITALIAN: 
            pucArray = tsOsdItalian;
            break;
            
        case _STRING_SWEDISH:
            pucArray = tsOsdSwedish;
            break;
            
        case _STRING_POLISH: 
            pucArray = tsOsdPolish;
            break; 
            
        case _STRING_RUSSIAN: 
            pucArray = tsOsdRussian;
            break;
            
        case _STRING_JAPANESE: 
            pucArray = tsOsdJapanese;
            break;

        case _STRING_ARABIC:
            pucArray = tsOsdArabic;
            break;

        case _STRING_CHINESE:
            pucArray = tsOsdChinese;
            break;
            
        case _STRING_AMB_OFF:
            pucArray = tsOsdOff;
            break;

        case _STRING_AMB_1:
            pucArray = tsOsdAmb1;
            break;

        case _STRING_AMB_2:
            pucArray = tsOsdAmb2;
            break;

        case _STRING_AMB_3:
            pucArray = tsOsdAmb3;
            break;

        case _STRING_REPORT_OFF:
            pucArray = tsOsdOff;
            break;

        case _STRING_REPORT_LEFT:
            pucArray = tsOsdLeft;
            break;

        case _STRING_REPORT_RIGHT:
            pucArray = tsOsdRight;
            break;

        case _STRING_FORMAT_RGB:
            pucArray = tsOsdFormatRgb;
            break;

        case _STRING_FORMAT_YUV:
            pucArray = tsOsdFormatYuv;
            break;

	/*		
	case _STRING_DP_1_1:
            pucArray = tsOsdDp11;
            break;
			
	case _STRING_DP_1_2:
            pucArray = tsOsdDp12;
            break;
	case _STRING_DP_1_4:
            pucArray = tsOsdDp14;
            break;*/

        case _STRING_ENERGYSAVING_OFF:
            pucArray = tsOsdOff;
            break;
            
        case _STRING_ENERGYSAVING_FAKE:
            pucArray = tsOsdFake;
            break;
            
        case _STRING_ENERGYSAVING_DEEP:
            pucArray = tsOsdDeep;
            break;

        case _STRING_ASPECT_FULL:
            pucArray = tsOsdFull;
            break;

        case _STRING_ASPECT_16_9:
            pucArray = tsOsdAspect169;
            break;

        case _STRING_ASPECT_4_3:
            pucArray = tsOsdAspect43;
            break;

        case _STRING_ASPECT_5_4:
            pucArray = tsOsdAspect54;
            break;

        case _STRING_ASPECT_ORIGIN:
            pucArray = tsOsdAspectOrigin;
            break;
			
        case _STRING_ASPECT_USER:
            pucArray = tsOsdUser;
            break;
			

 			
	/*		
	case _STRING_HDMI_1_4:
            pucArray = tsOsdHdmi14;
            break;
			
	case _STRING_HDMI_2_0:
            pucArray = tsOsdHdmi20;
            break;
       case _STRING_HDMI_2_1:
            pucArray = tsOsdHdmi21;
            break;*/
			
        case _STRING_LIGHT_BOX_LEFT:
            pucArray = tsOsdLeft;
            break;

        case _STRING_LIGHT_BOX_RIGHT:
            pucArray = tsOsdRight;
            break;

        case _STRING_LIGHT_BOX_FULL:
            pucArray = tsOsdFull;
            break;

        case _STRING_COLOR_SWITCH_SINGLE:
            pucArray = tsOsdColorSwitchMono;
            break;

        case _STRING_COLOR_SWITCH_COLOR:
            pucArray = tsOsdColorSwitchColor;
            break;
        
        // display mode
/*        
        case _STRING_MODE:            
    	    pucArray = tsOsdDisplayMode;
            break;	
            
        case _STRING_SELECT:            
            pucArray = tsOsdSelectRegion;
            break;
*/            
        case _STRING_DISP_ROTATE:
            pucArray = tsOsdDispRotate;
            break;

        case _STRING_OSD_0_DEGREE:
            pucArray = tsOsdStrDegree0;
            break;

        case _STRING_OSD_90_DEGREE:
            pucArray = tsOsdStrDegree90;
            break;

        case _STRING_OSD_270_DEGREE:
            pucArray = tsOsdStrDegree270;
            break;

        case _STRING_OSD_180_DEGREE:
            pucArray = tsOsdStrDegree180;
            break;
        case _STRING_0_DEGREE:
            pucArray = tsOsdStrDegree0;
            break;
            
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
        case _STRING_90_DEGREE:
            pucArray = tsOsdStrDegree90;
            break;
#endif

#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
        case _STRING_180_DEGREE:
            pucArray = tsOsdStrDegree180;
            break;
#endif

#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
        case _STRING_270_DEGREE:
            pucArray = tsOsdStrDegree270;
            break;
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _STRING_LR_MIRROR:
            pucArray = tsOsdStrLrMirror;
            break;
#endif

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _STRING_UD_MIRROR:
            pucArray = tsOsdStrUdMirror;
            break;
#endif   
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)		
        case _STRING_GAMMA_USER_TYPE_DICON:
            pucArray = tsOsdDicom;
            break;

        case _STRING_GAMMA_USER_TYPE_GAMMA:
            pucArray = tsOsdGamma;
            break;
#endif            

        case _STRING_NO_CABLE:
            pucArray = tsOsdNoCable;
            if(GET_OSD_FACTORY_MODE_BRUNIN())
            {
                pucArray = tsOsdBurnIn;
            }            
            break;
			
        case _STRING_NO_SIGNAL:
            pucArray = tsOsdNoSignal;
            if(GET_OSD_FACTORY_MODE_BRUNIN())
            {
                pucArray = tsOsdBurnIn;
            }            
            break;

        case _STRING_NO_SUPPORT:
            pucArray = tsOsdNoSupport;
            if(GET_OSD_FACTORY_MODE_BRUNIN())
            {
                pucArray = tsOsdBurnIn;
            }            
            break;

        case _STRING_POWERSAVING:
            pucArray = tsOsdPowerSaving;
            break;

        case _STRING_2HOUR_REMINDER_TEXT_0:
            pucArray = tsOsdString2HourReminderText0;
            break;

        case  _STRING_2HOUR_REMINDER_TEXT_1:
            pucArray = tsOsdString2HourReminderText1;
            break;
            
        case _STRING_DISPLAY_USELIFE_TEXT_0:
            pucArray = tsOsdStringDisplayUseLifeText0;
            break;

        case  _STRING_DISPLAY_USELIFE_TEXT_1:
            pucArray = tsOsdStringDisplayUseLifeText1;
            break;

        case _STRING_SHOW_NUMBER:
            pucArray = g_pucShowNumberAddress;
            break;
/*            
        case _STRING_SHOW_RATIO:
            pucArray = g_pucShowRatioAddress;
            break;	
        
        case _STRING_MENU:
            pucArray = tsOsdMenu;
            break;
            
        case _STRING_SOURCE:
            pucArray = tsOsdPower;
            break;
        
        case _STRING_OK:
            pucArray = tsOsdOk;
            break;
            
        case _STRING_UP:
            pucArray = tsOsdUp;
            break;

        case _STRING_DOWN:
            pucArray = tsOsdDown;
            break;

        case _STRING_LEFT:        
            pucArray = tsOsdLeft;
            break;

        case _STRING_RIGHT:        
            pucArray = tsOsdRight;
            break;
*/
        //case _STRING_RETURN:
            //pucArray = tsOsdReturn;
            //break;
            
        //case _STRING_ADJUST:
        //    pucArray = tsOsdKeyAdjust;
        //    break;
            
        case _STRING_PAGE_1:
            pucArray = tsOsdDisplay;
            break;
            
        case _STRING_PAGE_2:
            pucArray = tsOsdAdvanced;
            break;
            
        case _STRING_PAGE_3:
            pucArray = tsOsdColor;
            break;

        case _STRING_PAGE_4:
            pucArray = tsOsdOther;
            break;

        case _STRING_HDCP_NONE:
            pucArray = tsOsdStrHdcpDisable;
            break;
        
        case _STRING_HDCP_14:
            pucArray = tsOsdStrHdcp14Sink;
            break;
        
        case _STRING_HDCP_22:
            pucArray = tsOsdStrHdcp22Sink;
            break;
            
        case _STRING_HDCP_14_REPEATER:
            pucArray = tsOsdStrHdcp14Repeater;
            break;
        
        case _STRING_HDCP_22_REPEATER:
            pucArray = tsOsdStrHdcp22Repeater;
            break;
        
        case _STRING_VGA_USER_MODE:
        case _STRING_VGA_PRESET_MODE:
            pucArray = tsOsdReturn;
            break;

        case _STRING_HFREQPCLK_0:
            OsdPropGetShowHFreqPClkStringAddress();
            pucArray = g_pucModeInfoData;
            break;
        case _STRING_HDCP_MODE:
#if(_DIGITAL_PORT_SUPPORT == _ON)
            OsdPropGetShowHDCPEnable(ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort()));
            pucArray = g_pucModeInfoData;

#endif
            break;

        //case _STRING_DSC:
            //pucArray = tsOsdDsc;
            //break;
			
        case _STRING_1_DOT_1:
            pucArray = tsOsdStr1Dot1;
            break;
            
        case _STRING_1_DOT_2:
            pucArray = tsOsdStr1Dot2;
            break;
    /*        
        case _STRING_1_DOT_3:
            pucArray = tsOsdStr1Dot3;
            break;*/
            
        case _STRING_DP_1_DOT_4:
            pucArray = tsOsdStr1Dot4;
            break;
            
        case _STRING_1_DOT_4:
            pucArray = tsOsdStr1Dot4;
            break;
            
        case _STRING_2_DOT_0:
            pucArray = tsOsdStr2Dot0;
            break;
            
        case _STRING_2_DOT_1:
            pucArray = tsOsdStr2Dot1;
            break;
#if(_HDR10_SUPPORT == _ON)            
        case _STRING_HDR_MODE:
            pucArray = tsOsdHdr;
            break;
            
        case _STRING_DARK_ENHANCE:
            pucArray = tsOsdDarkEnhance;
            break;
            
        case _STRING_SHARPNESS_ENHANCE:
            pucArray = tsOsdSharpnessEnhance;
            break;
            
        case _STRING_HDR_CONTRAST:
            pucArray = tsOsdHdrContrast;
            break;
#endif            
        //case _STRING_HLG_OOTF:
        //    pucArray = tsOsdStrHlgOotf;
        //    break;
            
        case _STRING_SDR:
            pucArray = tsOsdStrSdr;
            break;

        case _STRING_USELIFE:
            pucArray = tsOsdUseLife;
            break;
            
        case _STRING_DP_RESOLUTION:
            pucArray = tsOsdDpResolution;
            break;
            
        case _STRING_CLONE:
            pucArray = tsOsdClone;
            break;
            
        //case _STRING_HLG:
        //    pucArray = tsOsdStrHlg;
        //    break;
        
        case _STRING_FREESYNC:
#if(_FREESYNC_II_SUPPORT == _ON)
            pucArray = tsOsdFreeSync2;
#else
            pucArray = tsOsdFreeSync;
#endif // #if(_FREESYNC_II_SUPPORT == _ON)
            break;
			
        case _STRING_DSC_NONE:
        case _STRING_CLONE_MT_OFF:
            pucArray = tsOsdOff;
            break;
            
        case _STRING_DSC_D0:
        case _STRING_CLONE_MT_D0:
           pucArray = tsOsdStrDP0;
            break;
            
        case _STRING_DSC_D1:
        case _STRING_CLONE_MT_D1:
            pucArray = tsOsdStrDP1;
            break;
            
        case _STRING_DSC_D2:
        case _STRING_CLONE_MT_D2:
            pucArray = tsOsdStrDP2;
            break;
            
        case _STRING_DSC_D3:
        case _STRING_CLONE_MT_D3:
            pucArray = tsOsdStrHdmi1;
            break;
            
        case _STRING_DSC_D4:
        case _STRING_CLONE_MT_D4:
            pucArray = tsOsdStrHdmi2;
            break;
            
        case _STRING_DSC_D5:
        case _STRING_CLONE_MT_D5:
            pucArray = tsOsdStrHdmi3;
            break;
            
        case _STRING_CLONE_MT_A0:
            pucArray = tsOsdStrVga;
            break;
            
        case _STRING_DSC_AUTO:
            pucArray = tsOsdAuto;
            break;
            
        case _STRING_DSC_OFF:
            pucArray = tsOsdOff;
            break;

         case _STRING_MST_OFF:
            pucArray = tsOsdOff;
            break;
            
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        case _STRING_MST_AUTO:
            pucArray = tsOsdAuto;
            break;
#endif
        case _STRING_DP:
            pucArray = tsOsdStrDp;
            break;

        case _STRING_MST_D0:
            pucArray = tsOsdStrDP0;
            break;
            
        case _STRING_MST_D1:
            pucArray = tsOsdStrDP1;
            break;
            
        case _STRING_MST_D6:
        case _STRING_CLONE_MT_D6:
            pucArray = tsOsdStrDP2;
            break;

        case _STRING_15S:
            pucArray = tsOsdString15S;
            break;

        case _STRING_5M:
            pucArray = tsOsdString5M;
            break;
			
        case _STRING_15M:
            pucArray = tsOsdString15M;
            break;
            
        case _STRING_DP_1080P:
            pucArray = tsOsdStr1080p;
            break;
            
        case _STRING_DP_2560_1440:
            pucArray = tsOsdStr25601440;
            break;
                        
        case _STRING_DP_4K2K_60HZ:
            pucArray = tsOsdStr4kat60;
            break;
			
        case _STRING_AUTOSELECT_PORT:
            pucArray = tsOsdAuto;
            break;
            
#if 1
        case _STRING_A0_PORT:
        case _STRING_A1_PORT:
        case _STRING_A2_PORT:            
        case _STRING_D0_PORT:
        case _STRING_D1_PORT:
        case _STRING_D2_PORT:
        case _STRING_D3_PORT:
        case _STRING_D4_PORT:
        case _STRING_D5_PORT:
        case _STRING_D6_PORT:
            OsdPropGetShowInputPortStringAddress(ucString - _STRIN_END);
            pucArray = g_pucModeInfoData;
            break;
#endif

#if(_DP_DEBUG_MSG == _ON)
        case _STRING_DP_INFO:
            OsdPropGetShowDpInfoStringAddress(_STRING_DP_INFO);
            pucArray = g_pucModeInfoData;
            break;
        case _STRING_DP_INFO_2:
            OsdPropGetShowDpInfoStringAddress(_STRING_DP_INFO_2);
            pucArray = g_pucModeInfoData;
            break;
#endif
            
         case _STRING_COLOR_PCM_SRGB:
            pucArray = tsOsdStrPcmSrgb;
            break;
            
        case _STRING_COLOR_PCM_ADOBE_RGB:
            pucArray = tsOsdStrPcmAdobeRgb;
            break;
            
        case _STRING_COLOR_PCM_USER:
            pucArray = tsOsdUser;
            break;
            
        case _STRING_COLOR_PCM_NATIVE:
            pucArray = tsOsdNative;
            break;
			
        case _STRING_COLOR_PCM_SOFT_PROFT_1:
            pucArray = tsOsdStrMode1;
            break;
            
        case _STRING_COLOR_PCM_SOFT_PROFT_2:
            pucArray = tsOsdStrMode2;
            break;


        case _STRING_PCM_STANDARD:
            pucArray = tsOsdStrStandard;
            break;

        case _STRING_PCM_GAMMA_18:
            pucArray = tsOsdStr1Dot8;
            break;

        case _STRING_PCM_GAMMA_19:
            pucArray = tsOsdStr1Dot9;
            break;

        case _STRING_PCM_GAMMA_20:
            pucArray = tsOsdStr2Dot0;
            break;

        case _STRING_PCM_GAMMA_21:
            pucArray = tsOsdStr2Dot1;
            break;
            
        case _STRING_PCM_GAMMA_22:
            pucArray = tsOsdStr2Dot2;
            break;

        case _STRING_PCM_GAMMA_24:
            pucArray = tsOsdStr2Dot4;
            break;

        case _STRING_PCM_GAMMA_26:
            pucArray = tsOsdStr2Dot6;
            break;

        case _STRING_PCM_GAMMA_28:
            pucArray = tsOsdStr2Dot8;
            break;

        case _STRING_PCM_GAMMA_30:
            pucArray = tsOsdStr3Dot0;
            break;
            
        //case _STRING_PCM_HLG:
        //    pucArray = tsOsdHLG;
        //    break;
            
        case _STRING_HDR10_MODE_OFF:
            pucArray = tsOsdOff;
            break;
            
        case _STRING_HDR10_MODE_AUTO:
            pucArray = tsOsdAuto;
            break;
            
        case _STRING_HDR10_MODE_FORCE_2084:
            pucArray = tsOsdStrForce2084;
            break;
            
        case _STRING_HDR10_MODE_AUTO_HLG:
            pucArray = tsOsdStrAutoHdrHlg;
            break;
            
        case _STRING_HDR10_MODE_FORCE_HLG:
            pucArray = tsOsdStrForceHlg;
            break;
            
        //case _STRING_HLG_STANDARD:
        //    pucArray = tsOsdStrStandard;
        //    break;
            
        //case _STRING_HLG_USER1:
        //    pucArray = tsOsdStrUserMode1;
        //    break;
            
        //case _STRING_HLG_USER2:
        //    pucArray = tsOsdStrUserMode2;
        //    break;
            
        //case _STRING_HLG_USER3:
        //    pucArray = tsOsdStrUserMode3;
        //    break;
            
            
        case _STRING_PASS:
            pucArray = tsOsdPass;
            break;

        case _STRING_FAIL:
            pucArray = tsOsdFail;
            break; 
            
        case _STRING_Execute:
            pucArray = tsOsdToExecute;
            break;

        case _STRING_Processing_Do_Not_Operate:
            pucArray = tsOsdDataProcessingDoNotOperate;
            break;
            
        case _STRING_Lumin_Processing_Do_Not_Operate:
            pucArray = tsOsdLuminanceProcessingDoNotOperate;
            break;		

        case _STRING_NO:
            pucArray = tsOsdNo;
            break;
        
        case _STRING_YES:
            pucArray = tsOsdYes;
            break;


        default:
            break;
    }

    return pucArray;
}
#endif//#if(_OSD_TYPE == _BEACON_2014_OSD)

