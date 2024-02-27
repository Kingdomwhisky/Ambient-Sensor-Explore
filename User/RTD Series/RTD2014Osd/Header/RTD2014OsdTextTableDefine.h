/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2017>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : Rtd2014OsdTextTableDefine.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Definitions of OSD Font Body Extension
//--------------------------------------------------
#define _FONT_SELECT_EXT1               251
#define _FONT_SELECT_EXT2               252
#define _NEXT_LINE                      253
#define _FONT_BLANK_PIXEL               254
#define _FONT_SELECT_OFFSET1            251
#define _FONT_SELECT_OFFSET2            502
#define _GLOBAL_FONT_END_OFFSET         (0)


//****************************************************************************
// Definitions of User
//****************************************************************************
enum OSDStringTextDef
{
_OSD_TEXT_NULL,
_OSD_TEXT_PICTURE,
_OSD_TEXT_DISPLAY,
_OSD_TEXT_COLOR,
_OSD_TEXT_ADVANCE,
_OSD_TEXT_INPUT,
_OSD_TEXT_AUDIO,
_OSD_TEXT_OTHER,
_OSD_TEXT_INFORMATION,
_OSD_TEXT_FACTORY,
_OSD_TEXT_BACKLIGHT,
_OSD_TEXT_BRIGHTNESS,
_OSD_TEXT_CONTRAST,
_OSD_TEXT_SHARPNESS,
_OSD_TEXT_AUTO_ADJUST,
_OSD_TEXT_H_POSITION,
_OSD_TEXT_V_POSITION,
_OSD_TEXT_CLOCK,
_OSD_TEXT_PHASE,
_OSD_TEXT_DISP_ROTATE,
_OSD_TEXT_DISP_LATENCY,
_OSD_TEXT_PANEL_UNIFORMITY,
_OSD_TEXT_GAMMA,
_OSD_TEXT_TEMPERATURE,
_OSD_TEXT_COLOR_EFFECT,
_OSD_TEXT_DEMO,
_OSD_TEXT_COLOR_FORMAT,
_OSD_TEXT_PCM,
_OSD_TEXT_HUE,
_OSD_TEXT_SATURATION,
_OSD_TEXT_ASPECT_RATIO,
_OSD_TEXT_OVER_SCAN,
_OSD_TEXT_OVER_DRIVE,
_OSD_TEXT_DCR,
_OSD_TEXT_DDCCI,
_OSD_TEXT_ULTRA_VIVID,
_OSD_TEXT_DP_OPTION,
_OSD_TEXT_DP_MST,
_OSD_TEXT_DP_RESOLUTION,
_OSD_TEXT_CLONE_MODE,
#if(_FREESYNC_II_SUPPORT == _ON)
_OSD_TEXT_FREE_SYNC2,
#endif //#if(_FREESYNC_II_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _OFF)
_OSD_TEXT_FREE_SYNC,
#endif //#if(_FREESYNC_II_SUPPORT == _OFF)

_OSD_TEXT_FREEZE,
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
_OSD_TEXT_TYPE_C_CONFIG,
#endif //#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
_OSD_TEXT_ULTRA_HDR,
_OSD_TEXT_ULTRA_HDR_MODE,
_OSD_TEXT_DARK_ENHANCE,
_OSD_TEXT_SHARPNESS_ENHANCE,
_OSD_TEXT_COLOR_ENHANCE,
_OSD_TEXT_LIGHT_ENHANCE,
#endif //#if(_HDR10_SUPPORT == _ON)

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
_OSD_TEXT_LOCAL_DIMMING,
#endif //#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)

#if(_PIXEL_SHIFT_SUPPORT == _ON)
_OSD_TEXT_PIXEL_SHIFTING,
#endif //#if(_PIXEL_SHIFT_SUPPORT == _ON)

_OSD_TEXT_HDMI_VERSION,
#if(_SDR_TO_HDR_SUPPORT == _ON)
_OSD_TEXT_SDR_TO_HDR,
#endif //#if(_SDR_TO_HDR_SUPPORT == _ON)

_OSD_TEXT_AUTO_SELECT,
_OSD_TEXT_VOLUME,
_OSD_TEXT_MUTE,
_OSD_TEXT_STAND_ALONG,
_OSD_TEXT_AUDIO_SOURCE,
_OSD_TEXT_SOUND_MODE,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
_OSD_TEXT_AUDIO_SELF_TEST,
#endif //#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

_OSD_TEXT_RESET,
_OSD_TEXT_MENU_TIME,
_OSD_TEXT_OSD_H_POSITION,
_OSD_TEXT_OSD_V_POSITION,
_OSD_TEXT_LANGUAGE,
_OSD_TEXT_TRANSPARENCY,
_OSD_TEXT_ROTATE,
_OSD_TEXT_USER_MODE,
_OSD_TEXT_PRESET_MODE,
_OSD_TEXT_PLEASE_WAIT,
_OSD_TEXT_NO_CABLE,
_OSD_TEXT_NO_SIGNAL,
_OSD_TEXT_NO_SUPPORT,
_OSD_TEXT_AUTO_COLOR,
_OSD_TEXT_GO_TO_POWER_SAVING,
_OSD_TEXT_PASS,
_OSD_TEXT_FAIL,
_OSD_TEXT_STR480I,
_OSD_TEXT_STR480P,
_OSD_TEXT_STR576I,
_OSD_TEXT_STR576P,
_OSD_TEXT_STR720P,
_OSD_TEXT_STR1080I,
_OSD_TEXT_STR1080P,
};	//StringText

enum OSDFontCBody0Def
{
_FONT_SPACE_1,
U0020,
U0025_0,U0025_1,
U0027,
U0028,
U0029,
U002C,
U002D,
U002E,
U002F,
U0030,
U0031,
U0032,
U0033,
U0034,
U0035,
U0036,
U0037,
U0038,
U0039,
U003A,
U003B,
U003F,
U0040_0,U0040_1,
U0041,
U0042,
U0043,
U0044,
U0045,
U0046,
U0047,
U0048,
U0049,
U004A,
U004B,
U004C,
U004D,
U004E,
U004F,
U0050,
U0051,
U0052,
U0053,
U0054,
U0055,
U0056,
U0057_0,U0057_1,
U0058,
U0059,
U005A,
U0061,
U0062,
U0063,
U0064,
U0065,
U0066,
U0067,
U0068,
U0069,
U006A,
U006B,
U006C,
U006D,
U006E,
U006F,
U0070,
U0071,
U0072,
U0073,
U0074,
U0075,
U0076,
U0077_0,U0077_1,
U0078,
U0079,
U007A,
U2019,
U201C,
U201D,
U2026,
U3002,
UFF08,
UFF09,
UFF0C,
_GLOBAL_FONT_END,
};	//FontCBody0, 88

enum OSDFontCBodyChineseDef
{
U4E0D_2_0 = _GLOBAL_FONT_END,U4E0D_2_1,
U4EAE_2_0,U4EAE_2_1,
U4F4D_2_0,U4F4D_2_1,
U4F7F_2_0,U4F7F_2_1,
U5019_2_0,U5019_2_1,
U50CF_2_0,U50CF_2_1,
U5149_2_0,U5149_2_1,
U5165_2_0,U5165_2_1,
U5176_2_0,U5176_2_1,
U51CD_2_0,U51CD_2_1,
U5206_2_0,U5206_2_1,
U5229_2_0,U5229_2_1,
U52D5_2_0,U52D5_2_1,
U52FB_2_0,U52FB_2_1,
U53CD_2_0,U53CD_2_1,
U548C_2_0,U548C_2_1,
U55AE_2_0,U55AE_2_1,
U5716_2_0,U5716_2_1,
U5747_2_0,U5747_2_1,
U5782_2_0,U5782_2_1,
U589E_2_0,U589E_2_1,
U5B83_2_0,U5B83_2_1,
U5BEC_2_0,U5BEC_2_1,
U5C0D_2_0,U5C0D_2_1,
U5C40_2_0,U5C40_2_1,
U5C55_2_0,U5C55_2_1,
U5DE5_2_0,U5DE5_2_1,
U5E73_2_0,U5E73_2_1,
U5EA6_2_0,U5EA6_2_1,
U5EE0_2_0,U5EE0_2_1,
U5EF6_2_0,U5EF6_2_1,
U5F0F_2_0,U5F0F_2_1,
U5F37_2_0,U5F37_2_1,
U5F71_2_0,U5F71_2_1,
U6027_2_0,U6027_2_1,
U606F_2_0,U606F_2_1,
U614B_2_0,U614B_2_1,
U61C9_2_0,U61C9_2_1,
U63F4_2_0,U63F4_2_1,
U64C7_2_0,U64C7_2_1,
U652F_2_0,U652F_2_1,
U6548_2_0,U6548_2_1,
U6574_2_0,U6574_2_1,
U65CB_2_0,U65CB_2_1,
U660E_2_0,U660E_2_1,
U6642_2_0,U6642_2_1,
U672C_2_0,U672C_2_1,
U679C_2_0,U679C_2_1,
U683C_2_0,U683C_2_1,
U6A21_2_0,U6A21_2_1,
U6BD4_2_0,U6BD4_2_1,
U6C34_2_0,U6C34_2_1,
U6E90_2_0,U6E90_2_1,
U6EAB_2_0,U6EAB_2_1,
U7121_2_0,U7121_2_1,
U7248_2_0,U7248_2_1,
U7368_2_0,U7368_2_1,
U7387_2_0,U7387_2_1,
U7528_2_0,U7528_2_1,
U756B_2_0,U756B_2_1,
U76F4_2_0,U76F4_2_1,
U76F8_2_0,U76F8_2_1,
U7701_2_0,U7701_2_1,
U793A_2_0,U793A_2_1,
U79FB_2_0,U79FB_2_1,
U7A0D_2_0,U7A0D_2_1,
U7ACB_2_0,U7ACB_2_1,
U7D20_2_0,U7D20_2_1,
U7D50_2_0,U7D50_2_1,
U7DDA_2_0,U7DDA_2_1,
U7F6E_2_0,U7F6E_2_1,
U8005_2_0,U8005_2_1,
U8072_2_0,U8072_2_1,
U80CC_2_0,U80CC_2_1,
U8108_2_0,U8108_2_1,
U81EA_2,
U8272_2_0,U8272_2_1,
U865F_2_0,U865F_2_1,
U88FD_2_0,U88FD_2_1,
U8907_2_0,U8907_2_1,
U8A00_2_0,U8A00_2_1,
U8A0A_2_0,U8A0A_2_1,
U8A2D_2_0 = 0,U8A2D_2_1,
U8A9E_2_0,U8A9E_2_1,
U8ABF_2_0,U8ABF_2_1,
U8ACB_2_0,U8ACB_2_1,
U8F38_2_0,U8F38_2_1,
U8F49_2_0,U8F49_2_1,
U8FA8_2_0,U8FA8_2_1,
U900F_2_0,U900F_2_1,
U9032_2_0,U9032_2_1,
U9072_2_0,U9072_2_1,
U9078_2_0,U9078_2_1,
U90E8_2_0,U90E8_2_1,
U914D_2_0,U914D_2_1,
U91CD_2_0,U91CD_2_1,
U91CF_2_0,U91CF_2_1,
U92B3_2_0,U92B3_2_1,
U9577_2_0,U9577_2_1,
U9593_2_0,U9593_2_1,
U968E_2_0,U968E_2_1,
U96FB_2_0,U96FB_2_1,
U9759_2_0,U9759_2_1,
U9762_2_0,U9762_2_1,
U97F3_2_0,U97F3_2_1,
U9805_2_0,U9805_2_1,
U9810_2_0,U9810_2_1,
U983B_2_0,U983B_2_1,
U984F_2_0,U984F_2_1,
U986F_2_0,U986F_2_1,
U98FD_2_0,U98FD_2_1,
U9ED1_2_0,U9ED1_2_1,
_COMMON_FONT2_END,
};	//FontCBodyChinese, 311

