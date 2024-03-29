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
// ID Code      : RL6410_Series_OSDLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __RL6410_SERIES_OSD_LIB_INTERFACE__
#define __RL6410_SERIES_OSD_LIB_INTERFACE__

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_POSITION_OFFSET_H                                  0x40
#define _OSD_POSITION_OFFSET_V                                  0x04

#define _OSD_DOUBLE_POSITION_OFFSET_H                           0x18
#define _OSD_DOUBLE_POSITION_OFFSET_V                           0x01

#define _OSD_ROTATE_NO_SWAP                                     0x00
#define _OSD_ROTATE_CCW                                         (_BIT7)
#define _OSD_ROTATE_CW                                          (_BIT7 | _BIT6)
#define _OSD_ROTATE_CW180                                       (_BIT6)

#define GET_OSD_POSITION_V_OFFSET_CORRECT_COMPENSATION()        (g_ucOSDPositionVOffsetCorrectCompensation)

//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _OSD_FONT_SCALING_RATIO_150,
    _OSD_FONT_SCALING_RATIO_200,
    _OSD_FONT_SCALING_RATIO_250,
    _OSD_FONT_SCALING_RATIO_300,
} EnumOsdFontScalingRatioType;

typedef enum
{
    _OSD_FONT_SCALING_BOUNDARY_NEIGHTBOOR,
    _OSD_FONT_SCALING_BOUNDARY_THIN,
    _OSD_FONT_SCALING_BOUNDARY_FAT,
} EnumOsdFontScalingBoundaryType;

typedef enum
{
    _OSD_FRONT_BACK_SHIFT_INSIDE,
    _OSD_FRONT_BACK_SHIFT_OUTSIDE,

}EnumOsdFrontBackShiftType;

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE g_ucOSDPositionVOffsetCorrectCompensation;


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//--------------------------------------------------
// SRAM
//--------------------------------------------------
extern void ScalerOsd4BitFontOffset(WORD usOffset);
extern void ScalerOsdFont24x36OnOff(bit bOnOff);
extern void ScalerOsdFontScalingUpRatio(EnumOsdFontScalingRatioType enumRatio);
extern void ScalerOsdFontScalingUpBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary);
extern void ScalerOsdFontScalingUpOnOff(bit bOnOff);
extern void ScalerOsdFontRotateCtrl(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn, BYTE ucDispRotEn);
extern void ScalerOsdHardwareCompression(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void ScalerOsdHardwareVLC(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType);
extern void ScalerOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, BYTE ucRowCommandStart, WORD usCharactorCommandStart, WORD usFontStart);

//--------------------------------------------------
// Function
//--------------------------------------------------
extern void ScalerOsdSetTransparency(BYTE ucTransparency);
extern void ScalerOsdSetTransparency_EXINT(BYTE ucTransparency);
extern void ScalerOsdAutoRotateFontBStartAddr(BYTE ucStartAddr);
extern void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void ScalerOsdPositionOffsetCorrection(void);
extern void ScalerOsdVerticalBoundary(bit bEnable);
extern void ScalerOsdFBShiftEn(bit bEnable);
extern void ScalerOsdFBShiftValue(EnumOsdFrontBackShiftType enumOsdFrontBackShiftType, WORD usBoundaryValue);
extern void ScalerOsdFBShiftBoundarySize(WORD usUpperBoundary, WORD usLowerBoundary);
extern WORD ScalerOsdGetFBShiftValue(EnumOsdFrontBackShiftType enumOsdFrontBackShiftType);

#endif
