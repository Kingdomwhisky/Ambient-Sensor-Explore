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
// ID Code      : RTDFactoryMode.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __FACTORY_MODE__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_FACTORY_PAGE_1_TABLE_END 18
#define _OSD_FACTORY_PAGE_2_TABLE_END 7


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucFactoryPage;
BYTE g_ucBgOnOff = _OFF;
BYTE g_ucBgColorR  = 128;
BYTE g_ucBgColorG  = 128;
BYTE g_ucBgColorB  = 128;
BYTE g_usBackupFacValue = 0;

BYTE g_ucAutoColotTypeFontPointer;

BYTE g_usBackupGammaValue;
BYTE g_usBackupPCMValue;
#if (_ENABLE_BACKLIGHT_SENSOR)
//extern BYTE g_bBacklightSensorInitState; 
extern bit g_bBacklightSensorValueRestoreStatus;
#endif
extern BYTE g_pucModeInfoData[28];

#if 0//(_ENABLE_AMBIENTLIGHT_SENSOR)
extern BYTE g_bAmbiSensorInitState; 
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void RTDFactoryMenuOperation(void);
void RTDFactoryMainMenu(void);
void RTDFactoryMainMenu1(void);
void RTDFactoryMainMenu2(void);
void OsdFactoryBacklightSensorValueShow(void);
//============= Auto Color =======================
void RTDFactoryAutoColorEnter(void);
void RTDFactoryAutoColorLeft(void);
void RTDFactoryAutoColorRight(void);
void RTDFactoryAutoColorExit(void);
//============= Auto Color Type =======================
void RTDFactoryAutoColorTypeEnter(void);
void RTDFactoryAutoColorTypeLeft(void);
void RTDFactoryAutoColorTypeRight(void);
void RTDFactoryAutoColorTypeExit(void);
//============= Burnin =======================
void RTDFactoryBurninEnter(void);
void RTDFactoryBurninLeft(void);
void RTDFactoryBurninRight(void);
void RTDFactoryBurninExit(void);
//============= Reset Burnin Time =======================
void RTDFactoryResetBurninTimeEnter(void);
void RTDFactoryResetBurninTimeLeft(void);
void RTDFactoryResetBurninTimeRight(void);
void RTDFactoryResetBurninTimeExit(void);
//============= Reset Panel Time =======================
void RTDFactoryResetPanelTimeEnter(void);
void RTDFactoryResetPanelTimeLeft(void);
void RTDFactoryResetPanelTimeRight(void);
void RTDFactoryResetPanelTimeExit(void);
//============= Colortemp 1 R=======================
void RTDFactoryColortemp1REnter(void);
void RTDFactoryColortemp1RLeft(void);
void RTDFactoryColortemp1RRight(void);
void RTDFactoryColortemp1RExit(void);
//============= Colortemp 1 G=======================
void RTDFactoryColortemp1GEnter(void);
void RTDFactoryColortemp1GLeft(void);
void RTDFactoryColortemp1GRight(void);
void RTDFactoryColortemp1GExit(void);
//============= Colortemp 1 B=======================
void RTDFactoryColortemp1BEnter(void);
void RTDFactoryColortemp1BLeft(void);
void RTDFactoryColortemp1BRight(void);
void RTDFactoryColortemp1BExit(void);
//============= Colortemp 2 R=======================
void RTDFactoryColortemp2REnter(void);
void RTDFactoryColortemp2RLeft(void);
void RTDFactoryColortemp2RRight(void);
void RTDFactoryColortemp2RExit(void);
//============= Colortemp 2 G=======================
void RTDFactoryColortemp2GEnter(void);
void RTDFactoryColortemp2GLeft(void);
void RTDFactoryColortemp2GRight(void);
void RTDFactoryColortemp2GExit(void);
//============= Colortemp 2 B=======================
void RTDFactoryColortemp2BEnter(void);
void RTDFactoryColortemp2BLeft(void);
void RTDFactoryColortemp2BRight(void);
void RTDFactoryColortemp2BExit(void);
//============= Colortemp 3 R=======================
void RTDFactoryColortemp3REnter(void);
void RTDFactoryColortemp3RLeft(void);
void RTDFactoryColortemp3RRight(void);
void RTDFactoryColortemp3RExit(void);
//============= Colortemp 3 G=======================
void RTDFactoryColortemp3GEnter(void);
void RTDFactoryColortemp3GLeft(void);
void RTDFactoryColortemp3GRight(void);
void RTDFactoryColortemp3GExit(void);
//============= Colortemp 3 B=======================
void RTDFactoryColortemp3BEnter(void);
void RTDFactoryColortemp3BLeft(void);
void RTDFactoryColortemp3BRight(void);
void RTDFactoryColortemp3BExit(void);
//============= Colortemp 4 R=======================
void RTDFactoryColortemp4REnter(void);
void RTDFactoryColortemp4RLeft(void);
void RTDFactoryColortemp4RRight(void);
void RTDFactoryColortemp4RExit(void);
//============= Colortemp 4 G=======================
void RTDFactoryColortemp4GEnter(void);
void RTDFactoryColortemp4GLeft(void);
void RTDFactoryColortemp4GRight(void);
void RTDFactoryColortemp4GExit(void);
//============= Colortemp 4 B=======================
void RTDFactoryColortemp4BEnter(void);
void RTDFactoryColortemp4BLeft(void);
void RTDFactoryColortemp4BRight(void);
void RTDFactoryColortemp4BExit(void);
//============= Colortemp 5 R=======================
void RTDFactoryColortemp5REnter(void);
void RTDFactoryColortemp5RLeft(void);
void RTDFactoryColortemp5RRight(void);
void RTDFactoryColortemp5RExit(void);
//============= Colortemp 5 G=======================
void RTDFactoryColortemp5GEnter(void);
void RTDFactoryColortemp5GLeft(void);
void RTDFactoryColortemp5GRight(void);
void RTDFactoryColortemp5GExit(void);
//============= Colortemp 5 B=======================
void RTDFactoryColortemp5BEnter(void);
void RTDFactoryColortemp5BLeft(void);
void RTDFactoryColortemp5BRight(void);
void RTDFactoryColortemp5BExit(void);
//============= Colortemp 6 R=======================
void RTDFactoryColortemp6REnter(void);
void RTDFactoryColortemp6RLeft(void);
void RTDFactoryColortemp6RRight(void);
void RTDFactoryColortemp6RExit(void);
//============= Colortemp 6 G=======================
void RTDFactoryColortemp6GEnter(void);
void RTDFactoryColortemp6GLeft(void);
void RTDFactoryColortemp6GRight(void);
void RTDFactoryColortemp6GExit(void);
//============= Colortemp 6 B=======================
void RTDFactoryColortemp6BEnter(void);
void RTDFactoryColortemp6BLeft(void);
void RTDFactoryColortemp6BRight(void);
void RTDFactoryColortemp6BExit(void);
//============= Adc Gain R=======================
void RTDFactoryAdcGainREnter(void);
void RTDFactoryAdcGainRLeft(void);
void RTDFactoryAdcGainRRight(void);
void RTDFactoryAdcGainRExit(void);
//============= Adc Gain G=======================
void RTDFactoryAdcGainGEnter(void);
void RTDFactoryAdcGainGLeft(void);
void RTDFactoryAdcGainGRight(void);
void RTDFactoryAdcGainGExit(void);
//============= Adc Gain B=======================
void RTDFactoryAdcGainBEnter(void);
void RTDFactoryAdcGainBLeft(void);
void RTDFactoryAdcGainBRight(void);
void RTDFactoryAdcGainBExit(void);
//============= Adc Offset R=======================
void RTDFactoryAdcOffsetREnter(void);
void RTDFactoryAdcOffsetRLeft(void);
void RTDFactoryAdcOffsetRRight(void);
void RTDFactoryAdcOffsetRExit(void);
//============= Adc Offset G=======================
void RTDFactoryAdcOffsetGEnter(void);
void RTDFactoryAdcOffsetGLeft(void);
void RTDFactoryAdcOffsetGRight(void);
void RTDFactoryAdcOffsetGExit(void);
//============= Adc Offset B=======================
void RTDFactoryAdcOffsetBEnter(void);
void RTDFactoryAdcOffsetBLeft(void);
void RTDFactoryAdcOffsetBRight(void);
void RTDFactoryAdcOffsetBExit(void);
//============= Osd Page=======================
void RTDFactoryOsdPageEnter(void);
void RTDFactoryOsdPageLeft(void);
void RTDFactoryOsdPageRight(void);
void RTDFactoryOsdPageExit(void);
//============= Exit=======================
void RTDFactoryExitEnter(void);
void RTDFactoryExitLeft(void);
void RTDFactoryExitRight(void);
void RTDFactoryExitExit(void);
//============= Auto Color Type Select=======================
void RTDFactoryAutoColorTypeSelectEnter(void);
void RTDFactoryAutoColorTypeSelectLeft(void);
void RTDFactoryAutoColorTypeSelectRight(void);
void RTDFactoryAutoColorTypeSelectExit(void);
//============= Burnin On Off=======================
void RTDFactoryBurninOnOffEnter(void);
void RTDFactoryBurninOnOffLeft(void);
void RTDFactoryBurninOnOffRight(void);
void RTDFactoryBurninOnOffExit(void);
//============= Colortemp 1 R Adjust=======================
void RTDFactoryColortemp1RAdjustEnter(void);
void RTDFactoryColortemp1RAdjustLeft(void);
void RTDFactoryColortemp1RAdjustRight(void);
void RTDFactoryColortemp1RAdjustExit(void);
//============= Colortemp 1 G Adjust=======================
void RTDFactoryColortemp1GAdjustEnter(void);
void RTDFactoryColortemp1GAdjustLeft(void);
void RTDFactoryColortemp1GAdjustRight(void);
void RTDFactoryColortemp1GAdjustExit(void);
//============= Colortemp 1 B Adjust=======================
void RTDFactoryColortemp1BAdjustEnter(void);
void RTDFactoryColortemp1BAdjustLeft(void);
void RTDFactoryColortemp1BAdjustRight(void);
void RTDFactoryColortemp1BAdjustExit(void);
//============= Colortemp 2 R Adjust=======================
void RTDFactoryColortemp2RAdjustEnter(void);
void RTDFactoryColortemp2RAdjustLeft(void);
void RTDFactoryColortemp2RAdjustRight(void);
void RTDFactoryColortemp2RAdjustExit(void);
//============= Colortemp 2 G Adjust=======================
void RTDFactoryColortemp2GAdjustEnter(void);
void RTDFactoryColortemp2GAdjustLeft(void);
void RTDFactoryColortemp2GAdjustRight(void);
void RTDFactoryColortemp2GAdjustExit(void);
//============= Colortemp 2 B Adjust=======================
void RTDFactoryColortemp2BAdjustEnter(void);
void RTDFactoryColortemp2BAdjustLeft(void);
void RTDFactoryColortemp2BAdjustRight(void);
void RTDFactoryColortemp2BAdjustExit(void);
//============= Colortemp 3 R Adjust=======================
void RTDFactoryColortemp3RAdjustEnter(void);
void RTDFactoryColortemp3RAdjustLeft(void);
void RTDFactoryColortemp3RAdjustRight(void);
void RTDFactoryColortemp3RAdjustExit(void);
//============= Colortemp 3 G Adjust=======================
void RTDFactoryColortemp3GAdjustEnter(void);
void RTDFactoryColortemp3GAdjustLeft(void);
void RTDFactoryColortemp3GAdjustRight(void);
void RTDFactoryColortemp3GAdjustExit(void);
//============= Colortemp 3 B Adjust=======================
void RTDFactoryColortemp3BAdjustEnter(void);
void RTDFactoryColortemp3BAdjustLeft(void);
void RTDFactoryColortemp3BAdjustRight(void);
void RTDFactoryColortemp3BAdjustExit(void);
//============= Colortemp 4 R Adjust=======================
void RTDFactoryColortemp4RAdjustEnter(void);
void RTDFactoryColortemp4RAdjustLeft(void);
void RTDFactoryColortemp4RAdjustRight(void);
void RTDFactoryColortemp4RAdjustExit(void);
//============= Colortemp 4 G Adjust=======================
void RTDFactoryColortemp4GAdjustEnter(void);
void RTDFactoryColortemp4GAdjustLeft(void);
void RTDFactoryColortemp4GAdjustRight(void);
void RTDFactoryColortemp4GAdjustExit(void);
//============= Colortemp 4 B Adjust=======================
void RTDFactoryColortemp4BAdjustEnter(void);
void RTDFactoryColortemp4BAdjustLeft(void);
void RTDFactoryColortemp4BAdjustRight(void);
void RTDFactoryColortemp4BAdjustExit(void);
//============= Colortemp 5 R Adjust=======================
void RTDFactoryColortemp5RAdjustEnter(void);
void RTDFactoryColortemp5RAdjustLeft(void);
void RTDFactoryColortemp5RAdjustRight(void);
void RTDFactoryColortemp5RAdjustExit(void);
//============= Colortemp 5 G Adjust=======================
void RTDFactoryColortemp5GAdjustEnter(void);
void RTDFactoryColortemp5GAdjustLeft(void);
void RTDFactoryColortemp5GAdjustRight(void);
void RTDFactoryColortemp5GAdjustExit(void);
//============= Colortemp 5 B Adjust=======================
void RTDFactoryColortemp5BAdjustEnter(void);
void RTDFactoryColortemp5BAdjustLeft(void);
void RTDFactoryColortemp5BAdjustRight(void);
void RTDFactoryColortemp5BAdjustExit(void);
//============= Colortemp 6 R Adjust=======================
void RTDFactoryColortemp6RAdjustEnter(void);
void RTDFactoryColortemp6RAdjustLeft(void);
void RTDFactoryColortemp6RAdjustRight(void);
void RTDFactoryColortemp6RAdjustExit(void);
//============= Colortemp 6 G Adjust=======================
void RTDFactoryColortemp6GAdjustEnter(void);
void RTDFactoryColortemp6GAdjustLeft(void);
void RTDFactoryColortemp6GAdjustRight(void);
void RTDFactoryColortemp6GAdjustExit(void);
//============= Colortemp 6 B Adjust=======================
void RTDFactoryColortemp6BAdjustEnter(void);
void RTDFactoryColortemp6BAdjustLeft(void);
void RTDFactoryColortemp6BAdjustRight(void);
void RTDFactoryColortemp6BAdjustExit(void);
//============= Adc Gain R Adjust=======================
void RTDFactoryAdcGainRAdjustEnter(void);
void RTDFactoryAdcGainRAdjustLeft(void);
void RTDFactoryAdcGainRAdjustRight(void);
void RTDFactoryAdcGainRAdjustExit(void);
//============= Adc Gain G Adjust=======================
void RTDFactoryAdcGainGAdjustEnter(void);
void RTDFactoryAdcGainGAdjustLeft(void);
void RTDFactoryAdcGainGAdjustRight(void);
void RTDFactoryAdcGainGAdjustExit(void);
//============= Adc Gain B Adjust=======================
void RTDFactoryAdcGainBAdjustEnter(void);
void RTDFactoryAdcGainBAdjustLeft(void);
void RTDFactoryAdcGainBAdjustRight(void);
void RTDFactoryAdcGainBAdjustExit(void);
//============= Adc Offset R Adjust=======================
void RTDFactoryAdcOffsetRAdjustEnter(void);
void RTDFactoryAdcOffsetRAdjustLeft(void);
void RTDFactoryAdcOffsetRAdjustRight(void);
void RTDFactoryAdcOffsetRAdjustExit(void);
//============= Adc Offset G Adjust=======================
void RTDFactoryAdcOffsetGAdjustEnter(void);
void RTDFactoryAdcOffsetGAdjustLeft(void);
void RTDFactoryAdcOffsetGAdjustRight(void);
void RTDFactoryAdcOffsetGAdjustExit(void);
//============= Adc Offset B Adjust=======================
void RTDFactoryAdcOffsetBAdjustEnter(void);
void RTDFactoryAdcOffsetBAdjustLeft(void);
void RTDFactoryAdcOffsetBAdjustRight(void);
void RTDFactoryAdcOffsetBAdjustExit(void);
//============= Osd Page Adjust=======================
void RTDFactoryOsdPageAdjustEnter(void);
void RTDFactoryOsdPageAdjustLeft(void);
void RTDFactoryOsdPageAdjustRight(void);
void RTDFactoryOsdPageAdjustExit(void);
//============= Background =======================
void RTDFactoryBgEnter(void);
void RTDFactoryBgLeft(void);
void RTDFactoryBgRight(void);
void RTDFactoryBgExit(void);
//============= Background R=======================
void RTDFactoryBgREnter(void);
void RTDFactoryBgRLeft(void);
void RTDFactoryBgRRight(void);
void RTDFactoryBgRExit(void);
//============= Background G=======================
void RTDFactoryBgGEnter(void);
void RTDFactoryBgGLeft(void);
void RTDFactoryBgGRight(void);
void RTDFactoryBgGExit(void);
//============= Background B=======================
void RTDFactoryBgBEnter(void);
void RTDFactoryBgBLeft(void);
void RTDFactoryBgBRight(void);
void RTDFactoryBgBExit(void);
//============= SSC=======================
void RTDFactorySSCEnter(void);
void RTDFactorySSCLeft(void);
void RTDFactorySSCRight(void);
void RTDFactorySSCExit(void);
//============= LVDS=======================
void RTDFactoryLVDSClockEnter(void);
void RTDFactoryLVDSClockLeft(void);
void RTDFactoryLVDSClockRight(void);
void RTDFactoryLVDSClockExit(void);
//============= LVDS Data=======================
void RTDFactoryLVDSDataEnter(void);
void RTDFactoryLVDSDataLeft(void);
void RTDFactoryLVDSDataRight(void);
void RTDFactoryLVDSDataExit(void);
//============= Pattern =======================
void RTDFactoryPatternEnter(void);
void RTDFactoryPatternLeft(void);
void RTDFactoryPatternRight(void);
void RTDFactoryPatternExit(void);
//============= Hot Plug DP DC Off High=======================
void RTDFactoryHotPlugDPDCOffHighEnter(void);
void RTDFactoryHotPlugDPDCOffHighLeft(void);
void RTDFactoryHotPlugDPDCOffHighRight(void);
void RTDFactoryHotPlugDPDCOffHighExit(void);
//============= Hot Plug HDMI Support=======================
void RTDFactoryHotPlugHDMISupportEnter(void);
void RTDFactoryHotPlugHDMISupportLeft(void);
void RTDFactoryHotPlugHDMISupportRight(void);
void RTDFactoryHotPlugHDMISupportExit(void);
//============= Hot Plug HDMI Support Time=======================
void RTDFactoryHotPlugHDMISupportTimeEnter(void);
void RTDFactoryHotPlugHDMISupportTimeLeft(void);
void RTDFactoryHotPlugHDMISupportTimeRight(void);
void RTDFactoryHotPlugHDMISupportTimeExit(void);
//============= DP AUX differentail mode=======================
void RTDFactoryDPAuxModeEnter(void);
void RTDFactoryDPAuxModeLeft(void);
void RTDFactoryDPAuxModeRight(void);
void RTDFactoryDPAuxModeExit(void);
//============= OSD double size=======================
void RTDFactoryOsdDoubleEnter(void);
void RTDFactoryOsdDoubleLeft(void);
void RTDFactoryOsdDoubleRight(void);
void RTDFactoryOsdDoubleExit(void);
//============= ColorimetrySeamless=======================
void RTDFactoryColorimetrySeamlessEnter(void);
void RTDFactoryColorimetrySeamlessLeft(void);
void RTDFactoryColorimetrySeamlessRight(void);
void RTDFactoryColorimetrySeamlessExit(void);
//============= DP AUX Setting=======================
void RTDFactoryDPAuxSettingEnter(void);
void RTDFactoryDPAuxSettingLeft(void);
void RTDFactoryDPAuxSettingRight(void);
void RTDFactoryDPAuxSettingExit(void);
//============= DP IQR HPD=======================
void RTDFactoryDPIrqHpdEnter(void);
void RTDFactoryDPIrqHpdLeft(void);
void RTDFactoryDPIrqHpdRight(void);
void RTDFactoryDPIrqHpdExit(void);
//============= ddcci=======================
void RTDFactoryDDCCIEnter(void);
void RTDFactoryDDCCILeft(void);
void RTDFactoryDDCCIRight(void);
void RTDFactoryDDCCIExit(void);
//============= ediden=======================
void RTDFactoryEDIDENEnter(void);
void RTDFactoryEDIDENLeft(void);
void RTDFactoryEDIDENRight(void);
void RTDFactoryEDIDENExit(void);
//============= logoen=======================
void RTDFactoryLogoENEnter(void);
void RTDFactoryLogoENLeft(void);
void RTDFactoryLogoENRight(void);
void RTDFactoryLogoENExit(void);
//============= colortemp=======================
void RTDFactoryColorTempEnter(void);
void RTDFactoryColorTempLeft(void);
void RTDFactoryColorTempRight(void);
void RTDFactoryColorTempExit(void);
//============= colortemp=======================
void RTDFactoryGAMMAEnter(void);
void RTDFactoryGAMMALeft(void);
void RTDFactoryGAMMARight(void);
void RTDFactoryGAMMAExit(void);

//============= Osd Page 1=======================
void RTDFactoryOsdPage1Enter(void);
void RTDFactoryOsdPage1Left(void);
void RTDFactoryOsdPage1Right(void);
void RTDFactoryOsdPage1Exit(void);
//============= Exit 1=======================
void RTDFactoryExit1Enter(void);
void RTDFactoryExit1Left(void);
void RTDFactoryExit1Right(void);
void RTDFactoryExit1Exit(void);
//============= BG On Off=======================
void RTDFactoryBgOnOffEnter(void);
void RTDFactoryBgOnOffLeft(void);
void RTDFactoryBgOnOffRight(void);
void RTDFactoryBgOnOffExit(void);
//============= BG R Adjust=======================
void RTDFactoryBgRAdjustEnter(void);
void RTDFactoryBgRAdjustLeft(void);
void RTDFactoryBgRAdjustRight(void);
void RTDFactoryBgRAdjustExit(void);
//============= BG G Adjust=======================
void RTDFactoryBgGAdjustEnter(void);
void RTDFactoryBgGAdjustLeft(void);
void RTDFactoryBgGAdjustRight(void);
void RTDFactoryBgGAdjustExit(void);
//============= Adc Gain B Adjust=======================
void RTDFactoryBgBAdjustEnter(void);
void RTDFactoryBgBAdjustLeft(void);
void RTDFactoryBgBAdjustRight(void);
void RTDFactoryBgBAdjustExit(void);
//============= SSC Adjust=======================
void RTDFactorySSCAdjustEnter(void);
void RTDFactorySSCAdjustLeft(void);
void RTDFactorySSCAdjustRight(void);
void RTDFactorySSCAdjustExit(void);
//============= LVDS Clock Current Adjust=======================
void RTDFactoryLVDSClockCurrentAdjustEnter(void);
void RTDFactoryLVDSClockCurrentAdjustLeft(void);
void RTDFactoryLVDSClockCurrentAdjustRight(void);
void RTDFactoryLVDSClockCurrentAdjustExit(void);
//============= LVDS Data Current Adjust=======================
void RTDFactoryLVDSDataCurrentAdjustEnter(void);
void RTDFactoryLVDSDataCurrentAdjustLeft(void);
void RTDFactoryLVDSDataCurrentAdjustRight(void);
void RTDFactoryLVDSDataCurrentAdjustExit(void);
//============= Hot Plug DP DC Off High Adjust=======================
void RTDFactoryHotPlugDPDCOffHighAdjustEnter(void);
void RTDFactoryHotPlugDPDCOffHighAdjustLeft(void);
void RTDFactoryHotPlugDPDCOffHighAdjustRight(void);
void RTDFactoryHotPlugDPDCOffHighAdjustExit(void);
//============= Hot Plug HDMI Support Adjus=======================
void RTDFactoryHotPlugHDMISupportAdjustEnter(void);
void RTDFactoryHotPlugHDMISupportAdjustLeft(void);
void RTDFactoryHotPlugHDMISupportAdjustRight(void);
void RTDFactoryHotPlugHDMISupportAdjustExit(void);
//============= Hot Plug HDMI Support Time Adjust=======================
void RTDFactoryHotPlugHDMISupportTimeAdjustEnter(void);
void RTDFactoryHotPlugHDMISupportTimeAdjustLeft(void);
void RTDFactoryHotPlugHDMISupportTimeAdjustRight(void);
void RTDFactoryHotPlugHDMISupportTimeAdjustExit(void);
//============= DP AUX differentail mode=======================
void RTDFactoryDPAuxModeAdjustEnter(void);
void RTDFactoryDPAuxModeAdjustLeft(void);
void RTDFactoryDPAuxModeAdjustRight(void);
void RTDFactoryDPAuxModeAdjustExit(void);
//============= OSD Double Size=======================
void RTDFactoryOsdDoubleAdjustEnter(void);
void RTDFactoryOsdDoubleAdjustLeft(void);
void RTDFactoryOsdDoubleAdjustRight(void);
void RTDFactoryOsdDoubleAdjustExit(void);
//============= Colorimetry Seamless=======================
void RTDFactoryColorimetrySeamlessAdjustEnter(void);
void RTDFactoryColorimetrySeamlessAdjustLeft(void);
void RTDFactoryColorimetrySeamlessAdjustRight(void);
void RTDFactoryColorimetrySeamlessAdjustExit(void);
//============= DP Aux Adj=======================
void RTDFactoryDPAuxAdjustEnter(void);
void RTDFactoryDPAuxAdjustLeft(void);
void RTDFactoryDPAuxAdjustRight(void);
void RTDFactoryDPAuxAdjustExit(void);
//============= DP IRQ HDP Adj======================
void RTDFactoryDPIrqHpdAdjEnter(void);
void RTDFactoryDPIrqHpdAdjLeft(void);
void RTDFactoryDPIrqHpdAdjRight(void);
void RTDFactoryDPIrqHpdAdjExit(void);
//============= ddcci adjust======================
void RTDFactoryDDCCIAdjEnter(void);
void RTDFactoryDDCCIAdjLeft(void);
void RTDFactoryDDCCIAdjRight(void);
void RTDFactoryDDCCIAdjExit(void);
//============= ediden adjust======================
void RTDFactoryEDIDENAdjEnter(void);
void RTDFactoryEDIDENAdjLeft(void);
void RTDFactoryEDIDENAdjRight(void);
void RTDFactoryEDIDENAdjExit(void);
//============= logoen adjust======================
void RTDFactoryLogoENAdjEnter(void);
void RTDFactoryLogoENAdjLeft(void);
void RTDFactoryLogoENAdjRight(void);
void RTDFactoryLogoENAdjExit(void);
//============= colortemp adjust======================
void RTDFactoryColorTempAdjEnter(void);
void RTDFactoryColorTempAdjLeft(void);
void RTDFactoryColorTempAdjRight(void);
void RTDFactoryColorTempAdjExit(void);
//============= GAMMA adjust======================
void RTDFactoryGAMMAAdjEnter(void);
void RTDFactoryGAMMAAdjLeft(void);
void RTDFactoryGAMMAAdjRight(void);
void RTDFactoryGAMMAAdjExit(void);

//============= Osd Page 1 Adjust=======================
void RTDFactoryOsdPage1AdjustEnter(void);
void RTDFactoryOsdPage1AdjustLeft(void);
void RTDFactoryOsdPage1AdjustRight(void);
void RTDFactoryOsdPage1AdjustExit(void);
//============= uiBackLigh Adjust=======================
void RTDFactoryPCMEnter(void);
void RTDFactoryPCMLeft(void);
void RTDFactoryPCMRight(void);
void RTDFactoryPCMExit(void);
//============= BackLigh Adjust=======================
void RTDFactoryBackLightEnter(void);
void RTDFactoryBackLightLeft(void);
void RTDFactoryBackLightRight(void);
void RTDFactoryBackLightExit(void);
//============= uiBackLigh Adjust=======================
void RTDFactoryUIBackLightEnter(void);
void RTDFactoryUIBackLightLeft(void);
void RTDFactoryUIBackLightRight(void);
void RTDFactoryUIBackLightExit(void);
//============= BLMinPoint Adjust=======================
void RTDFactoryBLMinPointEnter(void);
void RTDFactoryBLMinPointLeft(void);
void RTDFactoryBLMinPointRight(void);
void RTDFactoryBLMinPointExit(void);
//============= BLCenPoint Adjust=======================
void RTDFactoryBLCenPointEnter(void);
void RTDFactoryBLCenPointLeft(void);
void RTDFactoryBLCenPointRight(void);
void RTDFactoryBLCenPointExit(void);
//============= BLMaxPoint Adjust=======================
void RTDFactoryBLMaxPointEnter(void);
void RTDFactoryBLMaxPointLeft(void);
void RTDFactoryBLMaxPointRight(void);
void RTDFactoryBLMaxPointExit(void);
//============= BLDicom Adjust=======================
void RTDFactoryBLDicomEnter(void);
void RTDFactoryBLDicomLeft(void);
void RTDFactoryBLDicomRight(void);
void RTDFactoryBLDicomExit(void);
//============= BLUser Adjust=======================
void RTDFactoryBLUserEnter(void);
void RTDFactoryBLUserLeft(void);
void RTDFactoryBLUserRight(void);
void RTDFactoryBLUserExit(void);
//============= BLcalib Adjust=======================
void RTDFactoryBLCalibEnter(void);
void RTDFactoryBLCalibLeft(void);
void RTDFactoryBLCalibRight(void);
void RTDFactoryBLCalibExit(void);
//============= Dicom600 Adjust=======================
void RTDFactoryDicom600Enter(void);
void RTDFactoryDicom600Left(void);
void RTDFactoryDicom600Right(void);
void RTDFactoryDicom600Exit(void);
//============= Dicom550 Adjust=======================
void RTDFactoryDicom550Enter(void);
void RTDFactoryDicom550Left(void);
void RTDFactoryDicom550Right(void);
void RTDFactoryDicom550Exit(void);
//============= Dicom500 Adjust=======================
void RTDFactoryDicom500Enter(void);
void RTDFactoryDicom500Left(void);
void RTDFactoryDicom500Right(void);
void RTDFactoryDicom500Exit(void);
//============= Dicom450 Adjust=======================
void RTDFactoryDicom450Enter(void);
void RTDFactoryDicom450Left(void);
void RTDFactoryDicom450Right(void);
void RTDFactoryDicom450Exit(void);
//============= Dicom400 Adjust=======================
void RTDFactoryDicom400Enter(void);
void RTDFactoryDicom400Left(void);
void RTDFactoryDicom400Right(void);
void RTDFactoryDicom400Exit(void);
//============= Dicom350 Adjust=======================
void RTDFactoryDicom350Enter(void);
void RTDFactoryDicom350Left(void);
void RTDFactoryDicom350Right(void);
void RTDFactoryDicom350Exit(void);
//============= Dicom300 Adjust=======================
void RTDFactoryDicom300Enter(void);
void RTDFactoryDicom300Left(void);
void RTDFactoryDicom300Right(void);
void RTDFactoryDicom300Exit(void);
//============= Dicom250 Adjust=======================
void RTDFactoryDicom250Enter(void);
void RTDFactoryDicom250Left(void);
void RTDFactoryDicom250Right(void);
void RTDFactoryDicom250Exit(void);
//============= Dicom200 Adjust=======================
void RTDFactoryDicom200Enter(void);
void RTDFactoryDicom200Left(void);
void RTDFactoryDicom200Right(void);
void RTDFactoryDicom200Exit(void);

//============= Osd Page 2=======================
void RTDFactoryOsdPage2Enter(void);
void RTDFactoryOsdPage2Left(void);
void RTDFactoryOsdPage2Right(void);
void RTDFactoryOsdPage2Exit(void);
//============= Exit=======================
void RTDFactoryExit2Enter(void);
void RTDFactoryExit2Left(void);
void RTDFactoryExit2Right(void);
void RTDFactoryExit2Exit(void);


//============= Save Sensor=======================
void RTDFactorySaveUpdateBKSensor(void);

//============= pcm adjust=======================
void RTDFactoryPCMAdjEnter(void);
void RTDFactoryPCMAdjLeft(void);
void RTDFactoryPCMAdjRight(void);
void RTDFactoryPCMAdjExit(void);
//============= ULBackLight adjust=======================
void RTDFactoryULBackLightAdjEnter(void);
void RTDFactoryULBackLightAdjLeft(void);
void RTDFactoryULBackLightAdjRight(void);
void RTDFactoryULBackLightAdjExit(void);
//============= BLMinPoint adjust=======================
void RTDFactoryBLMinPointAdjEnter(void);
void RTDFactoryBLMinPointAdjLeft(void);
void RTDFactoryBLMinPointAdjRight(void);
void RTDFactoryBLMinPointAdjExit(void);
//============= BLCenPoint adjust=======================
void RTDFactoryBLCenPointAdjEnter(void);
void RTDFactoryBLCenPointAdjLeft(void);
void RTDFactoryBLCenPointAdjRight(void);
void RTDFactoryBLCenPointAdjExit(void);
//============= BLMaxPoint adjust=======================
void RTDFactoryBLMaxPointAdjEnter(void);
void RTDFactoryBLMaxPointAdjLeft(void);
void RTDFactoryBLMaxPointAdjRight(void);
void RTDFactoryBLMaxPointAdjExit(void);
//============= Dicom adjust=======================
void RTDFactoryDicomAdjEnter(void);
void RTDFactoryDicomAdjLeft(void);
void RTDFactoryDicomAdjRight(void);
void RTDFactoryDicomAdjExit(void);
//============= User adjust=======================
void RTDFactoryUserAdjEnter(void);
void RTDFactoryUserAdjLeft(void);
void RTDFactoryUserAdjRight(void);
void RTDFactoryUserAdjExit(void);
//============= Calib adjust=======================
void RTDFactoryCalibAdjEnter(void);
void RTDFactoryCalibAdjLeft(void);
void RTDFactoryCalibAdjRight(void);
void RTDFactoryCalibAdjExit(void);
//============= Dicom600 adjust=======================
void RTDFactoryDicom600AdjEnter(void);
void RTDFactoryDicom600AdjLeft(void);
void RTDFactoryDicom600AdjRight(void);
void RTDFactoryDicom600AdjExit(void);
//============= Dicom550 adjust=======================
void RTDFactoryDicom550AdjEnter(void);
void RTDFactoryDicom550AdjLeft(void);
void RTDFactoryDicom550AdjRight(void);
void RTDFactoryDicom550AdjExit(void);
//============= Dicom500 adjust=======================
void RTDFactoryDicom500AdjEnter(void);
void RTDFactoryDicom500AdjLeft(void);
void RTDFactoryDicom500AdjRight(void);
void RTDFactoryDicom500AdjExit(void);
//============= Dicom450 adjust=======================
void RTDFactoryDicom450AdjEnter(void);
void RTDFactoryDicom450AdjLeft(void);
void RTDFactoryDicom450AdjRight(void);
void RTDFactoryDicom450AdjExit(void);
//============= Dicom400 adjust=======================
void RTDFactoryDicom400AdjEnter(void);
void RTDFactoryDicom400AdjLeft(void);
void RTDFactoryDicom400AdjRight(void);
void RTDFactoryDicom400AdjExit(void);
//============= Dicom350 adjust=======================
void RTDFactoryDicom350AdjEnter(void);
void RTDFactoryDicom350AdjLeft(void);
void RTDFactoryDicom350AdjRight(void);
void RTDFactoryDicom350AdjExit(void);
//============= Dicom300 adjust=======================
void RTDFactoryDicom300AdjEnter(void);
void RTDFactoryDicom300AdjLeft(void);
void RTDFactoryDicom300AdjRight(void);
void RTDFactoryDicom300AdjExit(void);
//============= Dicom250 adjust=======================
void RTDFactoryDicom250AdjEnter(void);
void RTDFactoryDicom250AdjLeft(void);
void RTDFactoryDicom250AdjRight(void);
void RTDFactoryDicom250AdjExit(void);
//============= Dicom200 adjust=======================
void RTDFactoryDicom200AdjEnter(void);
void RTDFactoryDicom200AdjLeft(void);
void RTDFactoryDicom200AdjRight(void);
void RTDFactoryDicom200AdjExit(void);

//============= Osd Page 2 Adjust=======================
void RTDFactoryOsdPage2AdjustEnter(void);
void RTDFactoryOsdPage2AdjustLeft(void);
void RTDFactoryOsdPage2AdjustRight(void);
void RTDFactoryOsdPage2AdjustExit(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// OSD Factory Operation Table
//----------------------------------------------------------------------------------------------------
code void (*OperationFactoryTable[][4])(void) =
{
    {RTDFactoryAutoColorEnter,                      RTDFactoryAutoColorLeft,                        RTDFactoryAutoColorRight,                       RTDFactoryAutoColorExit,},
    {RTDFactoryAutoColorTypeEnter,                  RTDFactoryAutoColorTypeLeft,                    RTDFactoryAutoColorTypeRight,                   RTDFactoryAutoColorTypeExit,},
    {RTDFactoryBurninEnter,                         RTDFactoryBurninLeft,                           RTDFactoryBurninRight,                          RTDFactoryBurninExit,},
    {RTDFactoryResetBurninTimeEnter,                RTDFactoryResetBurninTimeLeft,                  RTDFactoryResetBurninTimeRight,                 RTDFactoryResetBurninTimeExit,},
    {RTDFactoryResetPanelTimeEnter,                 RTDFactoryResetPanelTimeLeft,                   RTDFactoryResetPanelTimeRight,                  RTDFactoryResetPanelTimeExit,},
    {RTDFactoryColortemp1REnter,                    RTDFactoryColortemp1RLeft,                      RTDFactoryColortemp1RRight,                     RTDFactoryColortemp1RExit,},
    {RTDFactoryColortemp1GEnter,                    RTDFactoryColortemp1GLeft,                      RTDFactoryColortemp1GRight,                     RTDFactoryColortemp1GExit,},
    {RTDFactoryColortemp1BEnter,                    RTDFactoryColortemp1BLeft,                      RTDFactoryColortemp1BRight,                     RTDFactoryColortemp1BExit,},
    {RTDFactoryColortemp2REnter,                    RTDFactoryColortemp2RLeft,                      RTDFactoryColortemp2RRight,                     RTDFactoryColortemp2RExit,},
    {RTDFactoryColortemp2GEnter,                    RTDFactoryColortemp2GLeft,                      RTDFactoryColortemp2GRight,                     RTDFactoryColortemp2GExit,},
    {RTDFactoryColortemp2BEnter,                    RTDFactoryColortemp2BLeft,                      RTDFactoryColortemp2BRight,                     RTDFactoryColortemp2BExit,},
    {RTDFactoryColortemp3REnter,                    RTDFactoryColortemp3RLeft,                      RTDFactoryColortemp3RRight,                     RTDFactoryColortemp3RExit,},
    {RTDFactoryColortemp3GEnter,                    RTDFactoryColortemp3GLeft,                      RTDFactoryColortemp3GRight,                     RTDFactoryColortemp3GExit,},
    {RTDFactoryColortemp3BEnter,                    RTDFactoryColortemp3BLeft,                      RTDFactoryColortemp3BRight,                     RTDFactoryColortemp3BExit,},
    {RTDFactoryColortemp4REnter,                    RTDFactoryColortemp4RLeft,                      RTDFactoryColortemp4RRight,                     RTDFactoryColortemp4RExit,},
    {RTDFactoryColortemp4GEnter,                    RTDFactoryColortemp4GLeft,                      RTDFactoryColortemp4GRight,                     RTDFactoryColortemp4GExit,},
    {RTDFactoryColortemp4BEnter,                    RTDFactoryColortemp4BLeft,                      RTDFactoryColortemp4BRight,                     RTDFactoryColortemp4BExit,},
    {RTDFactoryColortemp5REnter,                    RTDFactoryColortemp5RLeft,                      RTDFactoryColortemp5RRight,                     RTDFactoryColortemp5RExit,},
    {RTDFactoryColortemp5GEnter,                    RTDFactoryColortemp5GLeft,                      RTDFactoryColortemp5GRight,                     RTDFactoryColortemp5GExit,},
    {RTDFactoryColortemp5BEnter,                    RTDFactoryColortemp5BLeft,                      RTDFactoryColortemp5BRight,                     RTDFactoryColortemp5BExit,},
    {RTDFactoryColortemp6REnter,                    RTDFactoryColortemp6RLeft,                      RTDFactoryColortemp6RRight,                     RTDFactoryColortemp6RExit,},
    {RTDFactoryColortemp6GEnter,                    RTDFactoryColortemp6GLeft,                      RTDFactoryColortemp6GRight,                     RTDFactoryColortemp6GExit,},
    {RTDFactoryColortemp6BEnter,                    RTDFactoryColortemp6BLeft,                      RTDFactoryColortemp6BRight,                     RTDFactoryColortemp6BExit,},
    {RTDFactoryAdcGainREnter,                       RTDFactoryAdcGainRLeft,                         RTDFactoryAdcGainRRight,                        RTDFactoryAdcGainRExit,},
    {RTDFactoryAdcGainGEnter,                       RTDFactoryAdcGainGLeft,                         RTDFactoryAdcGainGRight,                        RTDFactoryAdcGainGExit,},
    {RTDFactoryAdcGainBEnter,                       RTDFactoryAdcGainBLeft,                         RTDFactoryAdcGainBRight,                        RTDFactoryAdcGainBExit,},
    {RTDFactoryAdcOffsetREnter,                     RTDFactoryAdcOffsetRLeft,                       RTDFactoryAdcOffsetRRight,                      RTDFactoryAdcOffsetRExit,},
    {RTDFactoryAdcOffsetGEnter,                     RTDFactoryAdcOffsetGLeft,                       RTDFactoryAdcOffsetGRight,                      RTDFactoryAdcOffsetGExit,},
    {RTDFactoryAdcOffsetBEnter,                     RTDFactoryAdcOffsetBLeft,                       RTDFactoryAdcOffsetBRight,                      RTDFactoryAdcOffsetBExit,},
    {RTDFactoryOsdPageEnter,                        RTDFactoryOsdPageLeft,                          RTDFactoryOsdPageRight,                         RTDFactoryOsdPageExit,},
    {RTDFactoryExitEnter,                           RTDFactoryExitLeft,                             RTDFactoryExitRight,                            RTDFactoryExitExit,},

    {RTDFactoryAutoColorTypeSelectEnter,            RTDFactoryAutoColorTypeSelectLeft,              RTDFactoryAutoColorTypeSelectRight,             RTDFactoryAutoColorTypeSelectExit,},
    {RTDFactoryBurninOnOffEnter,                    RTDFactoryBurninOnOffLeft,                      RTDFactoryBurninOnOffRight,                     RTDFactoryBurninOnOffExit,},
    {RTDFactoryColortemp1RAdjustEnter,              RTDFactoryColortemp1RAdjustLeft,                RTDFactoryColortemp1RAdjustRight,               RTDFactoryColortemp1RAdjustExit,},
    {RTDFactoryColortemp1GAdjustEnter,              RTDFactoryColortemp1GAdjustLeft,                RTDFactoryColortemp1GAdjustRight,               RTDFactoryColortemp1GAdjustExit,},
    {RTDFactoryColortemp1BAdjustEnter,              RTDFactoryColortemp1BAdjustLeft,                RTDFactoryColortemp1BAdjustRight,               RTDFactoryColortemp1BAdjustExit,},
    {RTDFactoryColortemp2RAdjustEnter,              RTDFactoryColortemp2RAdjustLeft,                RTDFactoryColortemp2RAdjustRight,               RTDFactoryColortemp2RAdjustExit,},
    {RTDFactoryColortemp2GAdjustEnter,              RTDFactoryColortemp2GAdjustLeft,                RTDFactoryColortemp2GAdjustRight,               RTDFactoryColortemp2GAdjustExit,},
    {RTDFactoryColortemp2BAdjustEnter,              RTDFactoryColortemp2BAdjustLeft,                RTDFactoryColortemp2BAdjustRight,               RTDFactoryColortemp2BAdjustExit,},
    {RTDFactoryColortemp3RAdjustEnter,              RTDFactoryColortemp3RAdjustLeft,                RTDFactoryColortemp3RAdjustRight,               RTDFactoryColortemp3RAdjustExit,},
    {RTDFactoryColortemp3GAdjustEnter,              RTDFactoryColortemp3GAdjustLeft,                RTDFactoryColortemp3GAdjustRight,               RTDFactoryColortemp3GAdjustExit,},
    {RTDFactoryColortemp3BAdjustEnter,              RTDFactoryColortemp3BAdjustLeft,                RTDFactoryColortemp3BAdjustRight,               RTDFactoryColortemp3BAdjustExit,},
    {RTDFactoryColortemp4RAdjustEnter,              RTDFactoryColortemp4RAdjustLeft,                RTDFactoryColortemp4RAdjustRight,               RTDFactoryColortemp4RAdjustExit,},
    {RTDFactoryColortemp4GAdjustEnter,              RTDFactoryColortemp4GAdjustLeft,                RTDFactoryColortemp4GAdjustRight,               RTDFactoryColortemp4GAdjustExit,},
    {RTDFactoryColortemp4BAdjustEnter,              RTDFactoryColortemp4BAdjustLeft,                RTDFactoryColortemp4BAdjustRight,               RTDFactoryColortemp4BAdjustExit,},
    {RTDFactoryColortemp5RAdjustEnter,              RTDFactoryColortemp5RAdjustLeft,                RTDFactoryColortemp5RAdjustRight,               RTDFactoryColortemp5RAdjustExit,},
    {RTDFactoryColortemp5GAdjustEnter,              RTDFactoryColortemp5GAdjustLeft,                RTDFactoryColortemp5GAdjustRight,               RTDFactoryColortemp5GAdjustExit,},
    {RTDFactoryColortemp5BAdjustEnter,              RTDFactoryColortemp5BAdjustLeft,                RTDFactoryColortemp5BAdjustRight,               RTDFactoryColortemp5BAdjustExit,},
    {RTDFactoryColortemp6RAdjustEnter,              RTDFactoryColortemp6RAdjustLeft,                RTDFactoryColortemp6RAdjustRight,               RTDFactoryColortemp6RAdjustExit,},
    {RTDFactoryColortemp6GAdjustEnter,              RTDFactoryColortemp6GAdjustLeft,                RTDFactoryColortemp6GAdjustRight,               RTDFactoryColortemp6GAdjustExit,},
    {RTDFactoryColortemp6BAdjustEnter,              RTDFactoryColortemp6BAdjustLeft,                RTDFactoryColortemp6BAdjustRight,               RTDFactoryColortemp6BAdjustExit,},
    {RTDFactoryAdcGainRAdjustEnter,                 RTDFactoryAdcGainRAdjustLeft,                   RTDFactoryAdcGainRAdjustRight,                  RTDFactoryAdcGainRAdjustExit,},
    {RTDFactoryAdcGainGAdjustEnter,                 RTDFactoryAdcGainGAdjustLeft,                   RTDFactoryAdcGainGAdjustRight,                  RTDFactoryAdcGainGAdjustExit,},
    {RTDFactoryAdcGainBAdjustEnter,                 RTDFactoryAdcGainBAdjustLeft,                   RTDFactoryAdcGainBAdjustRight,                  RTDFactoryAdcGainBAdjustExit,},
    {RTDFactoryAdcOffsetRAdjustEnter,               RTDFactoryAdcOffsetRAdjustLeft,                 RTDFactoryAdcOffsetRAdjustRight,                RTDFactoryAdcOffsetRAdjustExit,},
    {RTDFactoryAdcOffsetGAdjustEnter,               RTDFactoryAdcOffsetGAdjustLeft,                 RTDFactoryAdcOffsetGAdjustRight,                RTDFactoryAdcOffsetGAdjustExit,},
    {RTDFactoryAdcOffsetBAdjustEnter,               RTDFactoryAdcOffsetBAdjustLeft,                 RTDFactoryAdcOffsetBAdjustRight,                RTDFactoryAdcOffsetBAdjustExit,},
    {RTDFactoryOsdPageAdjustEnter,                  RTDFactoryOsdPageAdjustLeft,                    RTDFactoryOsdPageAdjustRight,                   RTDFactoryOsdPageAdjustExit,},

    //Factory page 1
    {RTDFactoryBgEnter,                             RTDFactoryBgLeft,                               RTDFactoryBgRight,                              RTDFactoryBgExit,},
    {RTDFactoryBgREnter,                            RTDFactoryBgRLeft,                              RTDFactoryBgRRight,                             RTDFactoryBgRExit,},
    {RTDFactoryBgGEnter,                            RTDFactoryBgGLeft,                              RTDFactoryBgGRight,                             RTDFactoryBgGExit,},
    {RTDFactoryBgBEnter,                            RTDFactoryBgBLeft,                              RTDFactoryBgBRight,                             RTDFactoryBgBExit,},
    {RTDFactorySSCEnter,                            RTDFactorySSCLeft,                              RTDFactorySSCRight,                             RTDFactorySSCExit,},
    {RTDFactoryLVDSClockEnter,                      RTDFactoryLVDSClockLeft,                        RTDFactoryLVDSClockRight,                       RTDFactoryLVDSClockExit,},
    {RTDFactoryLVDSDataEnter,                       RTDFactoryLVDSDataLeft,                         RTDFactoryLVDSDataRight,                        RTDFactoryLVDSDataExit,},
    {RTDFactoryHotPlugDPDCOffHighEnter,             RTDFactoryHotPlugDPDCOffHighLeft,               RTDFactoryHotPlugDPDCOffHighRight,              RTDFactoryHotPlugDPDCOffHighExit,},
    {RTDFactoryHotPlugHDMISupportEnter,             RTDFactoryHotPlugHDMISupportLeft,               RTDFactoryHotPlugHDMISupportRight,              RTDFactoryHotPlugHDMISupportExit,},
    {RTDFactoryHotPlugHDMISupportTimeEnter,         RTDFactoryHotPlugHDMISupportTimeLeft,           RTDFactoryHotPlugHDMISupportTimeRight,          RTDFactoryHotPlugHDMISupportTimeExit,},
    {RTDFactoryDPAuxModeEnter,                      RTDFactoryDPAuxModeLeft,                        RTDFactoryDPAuxModeRight,                       RTDFactoryDPAuxModeExit,},
    {RTDFactoryOsdDoubleEnter,                      RTDFactoryOsdDoubleLeft,                        RTDFactoryOsdDoubleRight,                       RTDFactoryOsdDoubleExit,},
    {RTDFactoryColorimetrySeamlessEnter,            RTDFactoryColorimetrySeamlessLeft,              RTDFactoryColorimetrySeamlessRight,             RTDFactoryColorimetrySeamlessExit,},
    {RTDFactoryDPAuxSettingEnter,                   RTDFactoryDPAuxSettingLeft,                     RTDFactoryDPAuxSettingRight,                    RTDFactoryDPAuxSettingExit,},
    {RTDFactoryDPIrqHpdEnter,                       RTDFactoryDPIrqHpdLeft,                         RTDFactoryDPIrqHpdRight,                        RTDFactoryDPIrqHpdExit,},
    {RTDFactoryDDCCIEnter,                          RTDFactoryDDCCILeft,                            RTDFactoryDDCCIRight,                           RTDFactoryDDCCIExit,},
    {RTDFactoryEDIDENEnter,                         RTDFactoryEDIDENLeft,                           RTDFactoryEDIDENRight,                          RTDFactoryEDIDENExit,},
    {RTDFactoryLogoENEnter,                         RTDFactoryLogoENLeft,                           RTDFactoryLogoENRight,                          RTDFactoryLogoENExit,},
    {RTDFactoryColorTempEnter,                      RTDFactoryColorTempLeft,                        RTDFactoryColorTempRight,                       RTDFactoryColorTempExit,},
    {RTDFactoryGAMMAEnter,                          RTDFactoryGAMMALeft,                            RTDFactoryGAMMARight,                           RTDFactoryGAMMAExit,},
    {RTDFactoryOsdPage1Enter,                       RTDFactoryOsdPage1Left,                         RTDFactoryOsdPage1Right,                        RTDFactoryOsdPage1Exit,},
    {RTDFactoryExit1Enter,                          RTDFactoryExit1Left,                            RTDFactoryExit1Right,                           RTDFactoryExit1Exit,},

    {RTDFactoryBgOnOffEnter,                        RTDFactoryBgOnOffLeft,                          RTDFactoryBgOnOffRight,                         RTDFactoryBgOnOffExit,},
    {RTDFactoryBgRAdjustEnter,                      RTDFactoryBgRAdjustLeft,                        RTDFactoryBgRAdjustRight,                       RTDFactoryBgRAdjustExit,},
    {RTDFactoryBgGAdjustEnter,                      RTDFactoryBgGAdjustLeft,                        RTDFactoryBgGAdjustRight,                       RTDFactoryBgGAdjustExit,},
    {RTDFactoryBgBAdjustEnter,                      RTDFactoryBgBAdjustLeft,                        RTDFactoryBgBAdjustRight,                       RTDFactoryBgBAdjustExit,},
    {RTDFactorySSCAdjustEnter,                      RTDFactorySSCAdjustLeft,                        RTDFactorySSCAdjustRight,                       RTDFactorySSCAdjustExit,},
    {RTDFactoryLVDSClockCurrentAdjustEnter,         RTDFactoryLVDSClockCurrentAdjustLeft,           RTDFactoryLVDSClockCurrentAdjustRight,          RTDFactoryLVDSClockCurrentAdjustExit,},
    {RTDFactoryLVDSDataCurrentAdjustEnter,          RTDFactoryLVDSDataCurrentAdjustLeft,            RTDFactoryLVDSDataCurrentAdjustRight,           RTDFactoryLVDSDataCurrentAdjustExit,},
    {RTDFactoryHotPlugDPDCOffHighAdjustEnter,       RTDFactoryHotPlugDPDCOffHighAdjustLeft,         RTDFactoryHotPlugDPDCOffHighAdjustRight,        RTDFactoryHotPlugDPDCOffHighAdjustExit,},
    {RTDFactoryHotPlugHDMISupportAdjustEnter,       RTDFactoryHotPlugHDMISupportAdjustLeft,         RTDFactoryHotPlugHDMISupportAdjustRight,        RTDFactoryHotPlugHDMISupportAdjustExit,},
    {RTDFactoryHotPlugHDMISupportTimeAdjustEnter,   RTDFactoryHotPlugHDMISupportTimeAdjustLeft,     RTDFactoryHotPlugHDMISupportTimeAdjustRight,    RTDFactoryHotPlugHDMISupportTimeAdjustExit,},

    {RTDFactoryDPAuxModeAdjustEnter,                RTDFactoryDPAuxModeAdjustLeft,                  RTDFactoryDPAuxModeAdjustRight,                 RTDFactoryDPAuxModeAdjustExit,},
    {RTDFactoryOsdDoubleAdjustEnter,                RTDFactoryOsdDoubleAdjustLeft,                  RTDFactoryOsdDoubleAdjustRight,                 RTDFactoryOsdDoubleAdjustExit,},
    {RTDFactoryColorimetrySeamlessAdjustEnter,      RTDFactoryColorimetrySeamlessAdjustLeft,        RTDFactoryColorimetrySeamlessAdjustRight,       RTDFactoryColorimetrySeamlessAdjustExit,},
    {RTDFactoryDPAuxAdjustEnter,                    RTDFactoryDPAuxAdjustLeft,                      RTDFactoryDPAuxAdjustRight,                     RTDFactoryDPAuxAdjustExit,},
    {RTDFactoryDPIrqHpdAdjEnter,                    RTDFactoryDPIrqHpdAdjLeft,                      RTDFactoryDPIrqHpdAdjRight,                     RTDFactoryDPIrqHpdAdjExit,},
    {RTDFactoryDDCCIAdjEnter,                       RTDFactoryDDCCIAdjLeft,                         RTDFactoryDDCCIAdjRight,                        RTDFactoryDDCCIAdjExit,},
    {RTDFactoryEDIDENAdjEnter,                      RTDFactoryEDIDENAdjLeft,                        RTDFactoryEDIDENAdjRight,                       RTDFactoryEDIDENAdjExit,},
    {RTDFactoryLogoENAdjEnter,                      RTDFactoryLogoENAdjLeft,                        RTDFactoryLogoENAdjRight,                       RTDFactoryLogoENAdjExit,},
    {RTDFactoryColorTempAdjEnter,                   RTDFactoryColorTempAdjLeft,                     RTDFactoryColorTempAdjRight,                    RTDFactoryColorTempAdjExit,},
    {RTDFactoryGAMMAAdjEnter,                       RTDFactoryGAMMAAdjLeft,                         RTDFactoryGAMMAAdjRight,                        RTDFactoryGAMMAAdjExit,},

    {RTDFactoryOsdPage1AdjustEnter,                 RTDFactoryOsdPage1AdjustLeft,                   RTDFactoryOsdPage1AdjustRight,                  RTDFactoryOsdPage1AdjustExit,},

    {RTDFactoryPCMEnter,                                    RTDFactoryPCMLeft,                                      RTDFactoryPCMRight,                                        RTDFactoryPCMExit,},
    {RTDFactoryUIBackLightEnter,                    RTDFactoryUIBackLightLeft,                      RTDFactoryUIBackLightRight,                     RTDFactoryUIBackLightExit,},
    {RTDFactoryBLMinPointEnter,                     RTDFactoryBLMinPointLeft,                       RTDFactoryBLMinPointRight,                      RTDFactoryBLMinPointExit,},
    {RTDFactoryBLCenPointEnter,                     RTDFactoryBLCenPointLeft,                       RTDFactoryBLCenPointRight,                      RTDFactoryBLCenPointExit,},
    {RTDFactoryBLMaxPointEnter,                     RTDFactoryBLMaxPointLeft,                       RTDFactoryBLMaxPointRight,                      RTDFactoryBLMaxPointExit,},
    {RTDFactoryBLCalibEnter,                        RTDFactoryBLCalibLeft,                          RTDFactoryBLCalibRight,                         RTDFactoryBLCalibExit,},    

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    {RTDFactoryBLDicomEnter,                        RTDFactoryBLDicomLeft,                          RTDFactoryBLDicomRight,                         RTDFactoryBLDicomExit,},
    {RTDFactoryBLUserEnter,                         RTDFactoryBLUserLeft,                           RTDFactoryBLUserRight,                          RTDFactoryBLUserExit,},
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    {RTDFactoryBLDicomEnter,                        RTDFactoryBLDicomLeft,                          RTDFactoryBLDicomRight,                         RTDFactoryBLDicomExit,},
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    {RTDFactoryDicom200Enter,                       RTDFactoryDicom200Left,                         RTDFactoryDicom200Right,                        RTDFactoryDicom200Exit,},
    {RTDFactoryDicom250Enter,                       RTDFactoryDicom250Left,                         RTDFactoryDicom250Right,                        RTDFactoryDicom250Exit,},
    {RTDFactoryDicom300Enter,                       RTDFactoryDicom300Left,                         RTDFactoryDicom300Right,                        RTDFactoryDicom300Exit,},    
    {RTDFactoryDicom350Enter,                       RTDFactoryDicom350Left,                         RTDFactoryDicom350Right,                        RTDFactoryDicom350Exit,},
    {RTDFactoryDicom400Enter,                       RTDFactoryDicom400Left,                         RTDFactoryDicom400Right,                        RTDFactoryDicom400Exit,},    
    {RTDFactoryDicom450Enter,                       RTDFactoryDicom450Left,                         RTDFactoryDicom450Right,                        RTDFactoryDicom450Exit,},
    {RTDFactoryDicom500Enter,                       RTDFactoryDicom500Left,                         RTDFactoryDicom500Right,                        RTDFactoryDicom500Exit,},    
    {RTDFactoryDicom550Enter,                       RTDFactoryDicom550Left,                         RTDFactoryDicom550Right,                        RTDFactoryDicom550Exit,},
    {RTDFactoryDicom600Enter,                       RTDFactoryDicom600Left,                         RTDFactoryDicom600Right,                        RTDFactoryDicom600Exit,},    
#else
#warning "!!!Please Check Gamma define"
#endif 
    
    {RTDFactoryOsdPage2Enter,                       RTDFactoryOsdPage2Left,                         RTDFactoryOsdPage2Right,                        RTDFactoryOsdPage2Exit,},
    {RTDFactoryExit2Enter,                          RTDFactoryExit2Left,                            RTDFactoryExit2Right,                           RTDFactoryExit2Exit,},
    {RTDFactoryPCMAdjEnter,                          RTDFactoryPCMAdjLeft,                                      RTDFactoryPCMAdjRight,                                  RTDFactoryPCMAdjExit,},
    {RTDFactoryULBackLightAdjEnter,                 RTDFactoryULBackLightAdjLeft,                   RTDFactoryULBackLightAdjRight,                  RTDFactoryULBackLightAdjExit,},
    {RTDFactoryBLMinPointAdjEnter,                  RTDFactoryBLMinPointAdjLeft,                    RTDFactoryBLMinPointAdjRight,                   RTDFactoryBLMinPointAdjExit,},
    {RTDFactoryBLCenPointAdjEnter,                  RTDFactoryBLCenPointAdjLeft,                    RTDFactoryBLCenPointAdjRight,                   RTDFactoryBLCenPointAdjExit,},
    {RTDFactoryBLMaxPointAdjEnter,                  RTDFactoryBLMaxPointAdjLeft,                    RTDFactoryBLMaxPointAdjRight,                   RTDFactoryBLMaxPointAdjExit,},
    {RTDFactoryCalibAdjEnter,                       RTDFactoryCalibAdjLeft,                         RTDFactoryCalibAdjRight,                        RTDFactoryCalibAdjExit,},

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    {RTDFactoryDicomAdjEnter,                       RTDFactoryDicomAdjLeft,                         RTDFactoryDicomAdjRight,                        RTDFactoryDicomAdjExit,},
    {RTDFactoryUserAdjEnter,                        RTDFactoryUserAdjLeft,                          RTDFactoryUserAdjRight,                         RTDFactoryUserAdjExit,},
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    {RTDFactoryDicomAdjEnter,                       RTDFactoryDicomAdjLeft,                         RTDFactoryDicomAdjRight,                        RTDFactoryDicomAdjExit,},
#elif(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    {RTDFactoryDicom200AdjEnter,                    RTDFactoryDicom200AdjLeft,                      RTDFactoryDicom200AdjRight,                     RTDFactoryDicom200AdjExit,},
    {RTDFactoryDicom250AdjEnter,                    RTDFactoryDicom250AdjLeft,                      RTDFactoryDicom250AdjRight,                     RTDFactoryDicom250AdjExit,},
    {RTDFactoryDicom300AdjEnter,                    RTDFactoryDicom300AdjLeft,                      RTDFactoryDicom300AdjRight,                     RTDFactoryDicom300AdjExit,},    
    {RTDFactoryDicom350AdjEnter,                    RTDFactoryDicom350AdjLeft,                      RTDFactoryDicom350AdjRight,                     RTDFactoryDicom350AdjExit,},
    {RTDFactoryDicom400AdjEnter,                    RTDFactoryDicom400AdjLeft,                      RTDFactoryDicom400AdjRight,                     RTDFactoryDicom400AdjExit,},    
    {RTDFactoryDicom450AdjEnter,                    RTDFactoryDicom450AdjLeft,                      RTDFactoryDicom450AdjRight,                     RTDFactoryDicom450AdjExit,},
    {RTDFactoryDicom500AdjEnter,                    RTDFactoryDicom500AdjLeft,                      RTDFactoryDicom500AdjRight,                     RTDFactoryDicom500AdjExit,},    
    {RTDFactoryDicom550AdjEnter,                    RTDFactoryDicom550AdjLeft,                      RTDFactoryDicom550AdjRight,                     RTDFactoryDicom550AdjExit,},
    {RTDFactoryDicom600AdjEnter,                    RTDFactoryDicom600AdjLeft,                      RTDFactoryDicom600AdjRight,                     RTDFactoryDicom600AdjExit,},    
#else
#warning "!!!Please Check Gamma define"
#endif    
    {RTDFactoryOsdPage2AdjustEnter,                 RTDFactoryOsdPage2AdjustLeft,                   RTDFactoryOsdPage2AdjustRight,                  RTDFactoryOsdPage2AdjustExit,},

};

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMenuOperation(void)
{
    if((GET_OSD_STATE() >= _MENU_FACTORY_AUTOCOLOR) &&
       (GET_OSD_STATE() < _MENU_FACTORY_OSD_END) &&
       (GET_KEYMESSAGE() < _KEY_AMOUNT))
    {
        (*OperationFactoryTable[GET_OSD_STATE() - _MENU_FACTORY_AUTOCOLOR][GET_KEYMESSAGE()])();
    }
}

//----------------------------------------------------------------------------------------------------
// OSD Factory
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMainMenu(void)
{
    BYTE ucRowCount = 0;

    g_ucFontPointer0 = _FACTORY_PAGE_0_START;
    g_ucFontPointer1 = _FACTORY_PAGE_1_START;
    g_ucFactoryPage = 0;

    RTDFactoryOsdFuncDisableOsd();
    SET_OSD_STATE(_MENU_FACTORY_EXIT);
    SET_OSD_IN_FACTORY_MENU_STATUS(_TRUE);
    RTDFactoryOsdFuncApplyMap(WIDTH(_FACTORY_OSD_COL), HEIGHT(_FACTORY_OSD_ROW), COLOR(_CP_WHITE, _CP_BG));
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_FACTORY_OSD_ROW), _DISABLE, 0, _ENABLE);
#endif
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_90);
#endif
    //ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //RTDFactoryOsdFuncClearOsdFontAll();
    OsdFactoryPropShowSpecifiedstringAddress();

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[0], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_FUNCTION_COL + 11), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[1], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_FW_VERSION_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, g_pucModeInfoData, _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[3], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[20], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[4], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_RESET_BURNIN_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[5], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[6], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_RESET_PANEL_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[7], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[8], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[9], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[10], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[11], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[12], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[13], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[14], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[15], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[16], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[17], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[18], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[19], _ENGLISH);
#if 0
    if(AmbiSensor_ReadLux() == _FAIL)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_ROW +1), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[20], _ENGLISH);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_EXIT_ROW +1), COL(_FACTORY_SETVALUE_COL), 0, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_PAGE_ITEM_35);
        ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
    	g_bAmbiSensorInitState = 0;
    }
    else
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_ROW +1), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[20], _ENGLISH);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_EXIT_ROW +1), COL(_FACTORY_SETVALUE_COL), usSensorLux, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_PAGE_ITEM_35);
    }
#endif
    for(ucRowCount = 0; ucRowCount < 8; ucRowCount++)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_R_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[0], _ENGLISH);
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_G_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[1], _ENGLISH);
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_B_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[2], _ENGLISH);
    }
    g_usBackupFacValue = GET_COLOR_TEMP_TYPE();

    for(ucRowCount = 0; ucRowCount <= _CT_COLORTEMP_AMOUNT; ucRowCount++)
    {
        SET_COLOR_TEMP_TYPE(ucRowCount);
        RTDNVRamLoadColorSetting(ucRowCount);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_R_NUMBER_COL), (g_stColorProcData.usColorTempR >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_R + ucRowCount * 3);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_G_NUMBER_COL), (g_stColorProcData.usColorTempG >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_G + ucRowCount * 3);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_B_NUMBER_COL), (g_stColorProcData.usColorTempB >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_B + ucRowCount * 3);
    }
    SET_COLOR_TEMP_TYPE( g_usBackupFacValue);    
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);

    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
#else
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);

    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
#endif

    // Auto color pass or fail
    // RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_AUTO_COLOR, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PASS_FAIL_TABLE[0], _ENGLISH);

    // Burnin on or off
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_BURNIN, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[GET_OSD_FACTORY_MODE_BRUNIN()], _ENGLISH);

    // Panel/Burnin Time hour and min.
    for(ucRowCount = 0; ucRowCount < 2; ucRowCount++)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_TIME_ROW + ucRowCount * 2), COL(_FACTORY_TIME_HOUR_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_HOUR_MIN_TABLE[0], _ENGLISH);
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_TIME_ROW + ucRowCount * 2), COL(_FACTORY_TIME_MIN_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_HOUR_MIN_TABLE[1], _ENGLISH);
    }

#if(_ADC_SELF_CALIBRATION == _OFF)
    SET_OSD_FACTORY_AUTO_COLOR_TYPE(_AUTO_COLOR_TYPE_EXTERNAL);
#endif

    // Auto color type
    g_ucAutoColotTypeFontPointer = g_ucFontPointer0;
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_AUTO_COLOR_TYPE, tFONT_FACTORY_EUROPE, tOSD_FACTORY_AUTO_COLOR_TYPE_TABLE[GET_OSD_FACTORY_AUTO_COLOR_TYPE()], _ENGLISH);

    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_BURNIN_TIME_HOUR_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_BURNIN_TIME_HOUR);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_BURNIN_TIME_MIN_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BURNIN_TIME_MIN);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_HOUR_NUMBER_COL), GET_PANEL_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_PANEL_TIME_HOUR);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_MIN_NUMBER_COL), GET_PANEL_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_PANEL_TIME_MIN);
    // OSD Page value
    //RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_OSD_PAGE_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_OSD_PAGE);

    RTDFactoryOsdFuncDrawWindow(tOSD_FACTORY_WIN0, 0, 0, _FACTORY_OSD_WINDOW_SIZE_X, _FACTORY_OSD_WINDOW_SIZE_Y, _CP_BLACK);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);

#if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)
    RTDFactoryOnePieceMark();
#endif

#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, 105);
#else
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
#endif    
    RTDFactoryOsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMainMenu1(void)
{
    BYTE ucLoop = 0;
    g_ucFontPointer0 = _FACTORY_PAGE_0_START;
    g_ucFontPointer1 = _FACTORY_PAGE_1_START;

    RTDFactoryOsdFuncDisableOsd();
    SET_OSD_STATE(_MENU_FACTORY_EXIT1);
    SET_OSD_IN_FACTORY_MENU_STATUS(_TRUE);
    RTDFactoryOsdFuncApplyMap(WIDTH(_FACTORY_OSD_COL), HEIGHT(_FACTORY_OSD_ROW), COLOR(_CP_WHITE, _CP_BG));
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_FACTORY_OSD_ROW), _DISABLE, 0, _ENABLE);
#endif
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);
#endif

    //ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    RTDFactoryOsdFuncClearOsdFontAll();

    //Draw item string
    for(ucLoop=0; ucLoop < _OSD_FACTORY_PAGE_1_TABLE_END ; ucLoop++)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_ROW+ucLoop), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[ucLoop], _ENGLISH);
    }
    //draw Item value
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_OSD_PAGE_1_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[_OSD_FACTORY_PAGE_1_TABLE_END], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_1_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[_OSD_FACTORY_PAGE_1_TABLE_END+1], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[0], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[1], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[2], _ENGLISH);

    // Background on/off value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_ROW), COL(_FACTORY_ON_OFF_COL), g_ucBgOnOff, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_ON_OFF);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_BACKGROUND_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[0], _ENGLISH);

    // Background color R/G/B value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_NUMBER_COL), g_ucBgColorR, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_NUMBER_COL), g_ucBgColorG, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_NUMBER_COL), g_ucBgColorB, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_B);

    // SSC value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_SSC_ROW), COL(_FACTORY_SSC_NUMBER_COL), g_stSystemData.ucSSC, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_SSC);
    //RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_SSC_ROW), COL(_FACTORY_SSC_NUMBER_COL), UserCommonNVRamGetSystemData(_SSC), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_SSC);
    // LVDS value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_LVDS_CLOCK_ROW), COL(_FACTORY_LVDS_NUMBER_COL), _LVDS_VCM_CONTROL, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_LVDS_CLOCK);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_LVDS_DATA_ROW), COL(_FACTORY_LVDS_NUMBER_COL), _LVDS_DRIV_CONTROL, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_LVDS_DATA);

    // Hot Plug Option
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), _PFONT_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH)], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), _PFONT_FACTORY_HOT_PLUG_HDMI_SUPPORT, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT)], _ENGLISH);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_HOT_PLUG_HDMI_TIME);
    // DP Aux Mode
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DP_AUX_MODE_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_DP_AUX_MODE_SEL, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE)], _ENGLISH);

    // OSD double size
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_OSD_DOUBLE_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_OSD_DOUBLE_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[GET_OSD_DOUBLE_SIZE()], _ENGLISH);
    //Colorimetry Seamless
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORIMETRY_SEAMLESS_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_COLORIMETRY_SEAMLESS, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE)], _ENGLISH);
#else
    RTDFactoryOsdFuncChangeColor1Bit(ROW(_FACTORY_COLORIMETRY_SEAMLESS_ROW), COL(0), _FACTORY_OSD_COL, 1, COLOR(_CP_GRAY, _CP_BG));
#endif

    // DP Aux Adjr Setting
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DP_AUX_ADJR_ROW), COL(_FACTORY_ON_OFF_COL), UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING),(_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_DP_AUX_ADJR);

    // DP IRQ Time Adjust
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DP_IRQ_ROW), COL(_FACTORY_ON_OFF_COL), (UserCommonNVRamGetSystemData(_DP_IRQ_TIME)*10), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DP_IRQ_ADJ);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DDCCI_EN), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[GET_OSD_DDCCI_STATUS()], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EDID_EN), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[PCB_EDID_EEPROM_WRITE_PROTECT_DETECT()], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_LOGO_EN), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE)], _ENGLISH);
    if(IsMonoChromeorColorPanel() == M_MONO)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP_1), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE,  tOSD_FACTORY_COLORTEMP_TYPE_TABLE[0], _ENGLISH);
    }
    else
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP_1), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE,  tOSD_FACTORY_COLORTEMP_TYPE_TABLE[GET_COLOR_TEMP_TYPE()], _ENGLISH);
    }
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_GAMMA), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_GAMMA_TABLE[GET_OSD_GAMMA()], _ENGLISH);

    RTDFactoryOsdFuncDrawWindow(tOSD_FACTORY_WIN0, 0, 0, _FACTORY_OSD_WINDOW_SIZE_X, _FACTORY_OSD_WINDOW_SIZE_Y, _CP_BLACK);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, 105);
#else
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);

#endif    
    RTDFactoryOsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMainMenu2(void)
{
    BYTE ucLoop = 0;
    g_ucFontPointer0 = _FACTORY_PAGE_0_START;
    g_ucFontPointer1 = _FACTORY_PAGE_1_START;

    RTDFactoryOsdFuncDisableOsd();
    SET_OSD_STATE(_MENU_FACTORY_EXIT2);
    SET_OSD_IN_FACTORY_MENU_STATUS(_TRUE);
    RTDFactoryOsdFuncApplyMap(WIDTH(_FACTORY_OSD_COL), HEIGHT(_FACTORY_OSD_ROW), COLOR(_CP_WHITE, _CP_BG));
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_FACTORY_OSD_ROW), _DISABLE, 0, _ENABLE);
#endif
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);
#endif
    //ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    RTDFactoryOsdFuncClearOsdFontAll();

    //Draw item string
    for(ucLoop=0; ucLoop < _OSD_FACTORY_PAGE_2_TABLE_END ; ucLoop++)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_ROW+ucLoop), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[ucLoop], _ENGLISH);
    }

   // RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BACKLIGHT_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[0], _ENGLISH);
    OsdFactoryBacklightSensorValueShow();

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_USER_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+1], _ENGLISH); 
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END], _ENGLISH); 
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM200_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM250_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+1], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM300_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+2], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM350_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+3], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM400_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+4], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM450_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+5], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM500_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+6], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM550_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+7], _ENGLISH); 
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DICOM600_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_2_TABLE[_OSD_FACTORY_PAGE_2_TABLE_END+8], _ENGLISH); 
#else
#warning "!!!Please Check Gamma define"
#endif    
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_OSD_PAGE_2_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_EXIT_TABLE[0], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_2_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_EXIT_TABLE[1], _ENGLISH);

    g_usBackupGammaValue = GET_OSD_GAMMA();
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_PCM_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PCM_TABLE[GET_OSD_PCM_STATUS()], _ENGLISH);

    RTDFactoryOsdFuncDrawWindow(tOSD_FACTORY_WIN0, 0, 0, _FACTORY_OSD_WINDOW_SIZE_X, _FACTORY_OSD_WINDOW_SIZE_Y, _CP_BLACK);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT2);
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
       (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, 105);
#else
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
#endif    
    RTDFactoryOsdFuncEnableOsd();
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryBacklightSensorValueShow(void)
{
	WORD usFacCurSensorValue,usCurBacklightPWM;
	usFacCurSensorValue = ReadBacklightSensorValue(0);

    //Get PWM
	usCurBacklightPWM = PCB_GET_BACKLIGHT_PWM();
#if(_BACKLIGHT_PWM_INVERSE == _ON)
    usCurBacklightPWM = _BACKLIGHT_MAX - usCurBacklightPWM;
#endif

	//Sensor Value	
#if (_ENABLE_BACKLIGHT_SENSOR)
	//if(g_bBacklightSensorInitState)
	{

        // End (_PFONT_FACTORY_PAGE_ITEM_1 + (_OSD_FACTORY2_BL_PC_CALIB - _OSD_FACTORY2_DDCCI))
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_UIBACKLIGHT_ROW), COL(_FACTORY_SETVALUE_COL), GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), (_PFONT_FACTORY_ULBACKLIGHT));
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BLMIN_ROW), COL(_FACTORY_SETVALUE_COL), _GET_DUT_BACKLIGHT_MIN, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_BLMIN_POINT);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BLCEN_ROW), COL(_FACTORY_SETVALUE_COL), _GET_DUT_BACKLIGHT_CENTER, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_BLCEN_POINT);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BLMAX_ROW), COL(_FACTORY_SETVALUE_COL), _GET_DUT_BACKLIGHT_MAX, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_BLMAX_POINT);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_CALIB_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_BACKLIGHT_CALIB, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_CALIB);
  
#if(_GAMMA_TYPE ==_GAMMA_NAME_G22_DICOM_USER_CALIB)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_USER_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_BACKLIGHT_MCU_CALIB, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_USER);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM200_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_200, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_200);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM250_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_250, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_250);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM300_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_300, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_300);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM350_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_350);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM400_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_400);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM450_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_450);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM500_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_500);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM550_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_550);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM600_ROW), COL(_FACTORY_SETVALUE_COL), _GET_USER_DICOM_BACKLIGHT_600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DICOM_600);

#else
#warning "!!!Please Check Gamma define"
#endif
        // Start (_PFONT_FACTORY_PAGE_ITEM_1 + _OSD_FACTORY_PAGE2_ITEM_AMOUNT)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_UIBACKLIGHT_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_16);
        RTDFactoryOsdFuncClearOsdFont(ROW(_FACTORY_UIBACKLIGHT_ROW), COL(_FACTORY_BKGET_CURPWM_COL), 4, 1, __);                                                

        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_UIBACKLIGHT_ROW), COL(_FACTORY_BKGET_CURPWM_COL), usCurBacklightPWM, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_17);

        RTDFactoryOsdFuncClearOsdFont(ROW(_FACTORY_UIBACKLIGHT_ROW), COL(_FACTORY_BKGET_SENVALUE_COL), 4, 1, __);                                                
        
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_UIBACKLIGHT_ROW), COL(_FACTORY_BKGET_SENVALUE_COL), usFacCurSensorValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_18);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BLCEN_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_19);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_CALIB_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_BACKLIGHT_CALIB_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_20);
   
#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_21);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_USER_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_BACKLIGHT_MCU_CALIB_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_22);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_21);  
#elif(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM200_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM200_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_21);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM250_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM250_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_22);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM300_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM300_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_23);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM350_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM350_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_24);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM400_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM400_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_25);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM450_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM450_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_26);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM500_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM500_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_27);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM550_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM550_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_28);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DICOM600_ROW), COL(_FACTORY_BKSET_SENTARGET_COL), _GET_USER_DICOM600_BACKLIGHT_SENSOR_VALUE, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_PAGE_ITEM_29);
#else
#warning "!!!Please Check Gamma define"
#endif
}
#endif
	
}

//----------------------------------------------------------------------------------------------------
// OSD Factory Operation
//----------------------------------------------------------------------------------------------------
//============= Auto Color =======================
void RTDFactoryAutoColorEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    BYTE ucTemp = 0;

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(GET_OSD_FACTORY_AUTO_COLOR_TYPE() == _AUTO_COLOR_TYPE_INTERNAL)
        {
            RTDFactoryOsdFuncDisableOsd();
            ucTemp = _AUTO_CALIBRATE_RGB;
        }
        else
        {
            ucTemp = _AUTO_TUNE_RGB;
        }

        if(ScalerAutoDoWhiteBalance(ucTemp) == _AUTO_SUCCESS)
        {
            ScalerAutoGetAutoColorResult(&g_stAdcData);
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_BG, _CP_BG));
            RTDFactoryOsdFuncPutStringProp(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, _PFONT_FACTORY_AUTO_COLOR, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PASS_FAIL_TABLE[1], _ENGLISH);
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_WHITE, _CP_BG));
            UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
        }
        else
        {
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_BG, _CP_BG));
            RTDFactoryOsdFuncPutStringProp(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, _PFONT_FACTORY_AUTO_COLOR, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PASS_FAIL_TABLE[0], _ENGLISH);
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_WHITE, _CP_BG));
            UserCommonNVRamRestoreADCSetting();
        }
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);

        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
    }
#endif // End of #if(_VGA_SUPPORT == _ON)
}

void RTDFactoryAutoColorLeft(void)
{
#if(_ADC_SELF_CALIBRATION == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR_TYPE);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
#endif // End of #if(_ADC_SELF_CALIBRATION == _ON)
}

void RTDFactoryAutoColorRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);
}

void RTDFactoryAutoColorExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Auto Color Type =======================
void RTDFactoryAutoColorTypeEnter(void)
{
    g_usBackupValue = GET_OSD_FACTORY_AUTO_COLOR_TYPE();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTO_COLOR_TYPE);
}

void RTDFactoryAutoColorTypeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

void RTDFactoryAutoColorTypeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR);
}

void RTDFactoryAutoColorTypeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Burnin =======================
void RTDFactoryBurninEnter(void)
{
    g_usBackupValue = GET_OSD_FACTORY_MODE_BRUNIN();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN_ON_OFF);
}

void RTDFactoryBurninLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_BURNIN_TIME);
}

void RTDFactoryBurninRight(void)
{
#if(_ADC_SELF_CALIBRATION == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR_TYPE);

#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR);

#endif // End of #if(_ADC_SELF_CALIBRATION == _ON)
}

void RTDFactoryBurninExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Reset Burnin Time =======================
void RTDFactoryResetBurninTimeEnter(void)
{
	SET_SYSTEM_RUN_TIME_HOUR(0); 				
	SET_SYSTEM_RUN_TIME_MIN(0); 				
	SET_SYSTEM_RUN_TIME_OVERFLOW(0); 				
	RTDNVRamSavePanelUsedTimeData();
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_BURNIN_TIME_HOUR_NUMBER_COL), GET_SYSTEM_RUN_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6), _PFONT_FACTORY_BURNIN_TIME_HOUR);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_BURNIN_TIME_MIN_NUMBER_COL), GET_SYSTEM_RUN_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BURNIN_TIME_MIN);
}

void RTDFactoryResetBurninTimeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_PANEL_TIME);
}

void RTDFactoryResetBurninTimeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

void RTDFactoryResetBurninTimeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Reset Panel Time =======================
void RTDFactoryResetPanelTimeEnter(void)
{
	SET_PANEL_RUN_TIME_HOUR(0); 				
	SET_PANEL_RUN_TIME_MIN(0); 				
	SET_PANEL_TIME_HOUR(0); 				
	SET_PANEL_TIME_MIN(0); 				
	SET_PANEL_RUN_TIME_OVERFLOW(0); 				
	RTDNVRamSavePanelUsedTimeData();
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_HOUR_NUMBER_COL), GET_PANEL_RUN_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6), _PFONT_FACTORY_PANEL_TIME_HOUR);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_MIN_NUMBER_COL), GET_PANEL_RUN_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_PANEL_TIME_MIN);
}

void RTDFactoryResetPanelTimeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
    RTDFactoryOsdChangColorTemp(_CT_9300);
}

void RTDFactoryResetPanelTimeRight(void)
{
    //RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_BURNIN_TIME);
}

void RTDFactoryResetPanelTimeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 1 R=======================
void RTDFactoryColortemp1REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED_ADJ);
}

void RTDFactoryColortemp1RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

void RTDFactoryColortemp1RRight(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_PANEL_TIME);
}

void RTDFactoryColortemp1RExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 1 G=======================
void RTDFactoryColortemp1GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN_ADJ);
}

void RTDFactoryColortemp1GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
}

void RTDFactoryColortemp1GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
}

void RTDFactoryColortemp1GExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 1 B=======================
void RTDFactoryColortemp1BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE_ADJ);
}

void RTDFactoryColortemp1BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
    RTDFactoryOsdChangColorTemp(_CT_7500);
}

void RTDFactoryColortemp1BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

void RTDFactoryColortemp1BExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 2 R=======================
void RTDFactoryColortemp2REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED_ADJ);
}

void RTDFactoryColortemp2RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

void RTDFactoryColortemp2RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_9300);
}

void RTDFactoryColortemp2RExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 2 G=======================
void RTDFactoryColortemp2GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN_ADJ);
}

void RTDFactoryColortemp2GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
}

void RTDFactoryColortemp2GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
}

void RTDFactoryColortemp2GExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 2 B=======================
void RTDFactoryColortemp2BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE_ADJ);
}

void RTDFactoryColortemp2BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
    RTDFactoryOsdChangColorTemp(_CT_6500);
}

void RTDFactoryColortemp2BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

void RTDFactoryColortemp2BExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 3 R=======================
void RTDFactoryColortemp3REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED_ADJ);
}

void RTDFactoryColortemp3RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

void RTDFactoryColortemp3RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_7500);
}

void RTDFactoryColortemp3RExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 3 G=======================
void RTDFactoryColortemp3GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN_ADJ);
}

void RTDFactoryColortemp3GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
}

void RTDFactoryColortemp3GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
}

void RTDFactoryColortemp3GExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 3 B=======================
void RTDFactoryColortemp3BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE_ADJ);
}

void RTDFactoryColortemp3BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
    RTDFactoryOsdChangColorTemp(_CT_5800);
}

void RTDFactoryColortemp3BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

void RTDFactoryColortemp3BExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 4 R=======================
void RTDFactoryColortemp4REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED_ADJ);
}

void RTDFactoryColortemp4RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

void RTDFactoryColortemp4RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_6500);
}

void RTDFactoryColortemp4RExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 4 G=======================
void RTDFactoryColortemp4GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN_ADJ);
}

void RTDFactoryColortemp4GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
}

void RTDFactoryColortemp4GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
}

void RTDFactoryColortemp4GExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 4 B=======================
void RTDFactoryColortemp4BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE_ADJ);
}

void RTDFactoryColortemp4BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
    RTDFactoryOsdChangColorTemp(_CT_SRGB);
}

void RTDFactoryColortemp4BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

void RTDFactoryColortemp4BExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 5 R=======================
void RTDFactoryColortemp5REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED_ADJ);
}

void RTDFactoryColortemp5RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

void RTDFactoryColortemp5RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_5800);
}

void RTDFactoryColortemp5RExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 5 G=======================
void RTDFactoryColortemp5GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN_ADJ);
}

void RTDFactoryColortemp5GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
}

void RTDFactoryColortemp5GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
}

void RTDFactoryColortemp5GExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 5 B=======================
void RTDFactoryColortemp5BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE_ADJ);
}

void RTDFactoryColortemp5BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
    RTDFactoryOsdChangColorTemp(_CT_USER);
}

void RTDFactoryColortemp5BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

void RTDFactoryColortemp5BExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 6 R=======================
void RTDFactoryColortemp6REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED_ADJ);
}

void RTDFactoryColortemp6RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

void RTDFactoryColortemp6RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_SRGB);
}

void RTDFactoryColortemp6RExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 6 G=======================
void RTDFactoryColortemp6GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN_ADJ);
}

void RTDFactoryColortemp6GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
}

void RTDFactoryColortemp6GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
}

void RTDFactoryColortemp6GExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 6 B=======================
void RTDFactoryColortemp6BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE_ADJ);
}

void RTDFactoryColortemp6BLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
    RTDFactoryOsdChangColorTemp(_CT_9300);
#else
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE);
#endif
}

void RTDFactoryColortemp6BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

void RTDFactoryColortemp6BExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Gain R=======================
void RTDFactoryAdcGainREnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED_ADJ);
#endif
}

void RTDFactoryAdcGainRLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
}

void RTDFactoryAdcGainRRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_USER);
}

void RTDFactoryAdcGainRExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Gain G=======================
void RTDFactoryAdcGainGEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN_ADJ);
#endif
}

void RTDFactoryAdcGainGLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
}

void RTDFactoryAdcGainGRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
}

void RTDFactoryAdcGainGExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Gain B=======================
void RTDFactoryAdcGainBEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE_ADJ);
#endif
}

void RTDFactoryAdcGainBLeft(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
}

void RTDFactoryAdcGainBRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
}

void RTDFactoryAdcGainBExit(void)
{
    RTDFactoryOsdChangColorTemp(g_usBackupFacValue);
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Offset R=======================
void RTDFactoryAdcOffsetREnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED_ADJ);
#endif
}

void RTDFactoryAdcOffsetRLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
}

void RTDFactoryAdcOffsetRRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
}

void RTDFactoryAdcOffsetRExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Offset G=======================
void RTDFactoryAdcOffsetGEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN_ADJ);
#endif
}

void RTDFactoryAdcOffsetGLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
}

void RTDFactoryAdcOffsetGRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
}

void RTDFactoryAdcOffsetGExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Offset B=======================
void RTDFactoryAdcOffsetBEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE_ADJ);
#endif
}

void RTDFactoryAdcOffsetBLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE);
}

void RTDFactoryAdcOffsetBRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
}

void RTDFactoryAdcOffsetBExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Osd Page=======================
void RTDFactoryOsdPageEnter(void)
{
    g_ucFactoryPage = 1;
    RTDFactoryMainMenu1();
}

void RTDFactoryOsdPageLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);
}

void RTDFactoryOsdPageRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_USER);
#endif
}

void RTDFactoryOsdPageExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Exit=======================
void RTDFactoryExitEnter(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

void RTDFactoryExitLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
#endif
}

void RTDFactoryExitRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE);
}

void RTDFactoryExitExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}


//============= Auto Color Type Select =======================
void RTDFactoryAutoColorTypeSelectEnter(void)
{
    if(g_usBackupValue != GET_OSD_FACTORY_AUTO_COLOR_TYPE())
    {
        SET_OSD_FACTORY_AUTO_COLOR_TYPE(g_usAdjustValue);
        RTDNVRamSaveOSDData();
    }

    RTDFactoryAutoColorTypeSelectExit();
}

void RTDFactoryAutoColorTypeSelectLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_AUTO_COLOR_TYPE, g_usAdjustValue);
}

void RTDFactoryAutoColorTypeSelectRight(void)
{
    RTDFactoryAutoColorTypeSelectLeft();
}

void RTDFactoryAutoColorTypeSelectExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR_TYPE);
}

//============= Burnin On Off=======================
void RTDFactoryBurninOnOffEnter(void)
{
    if(g_usBackupValue != GET_OSD_FACTORY_MODE_BRUNIN())
    {
        SET_OSD_FACTORY_MODE_BRUNIN(g_usAdjustValue);
        RTDNVRamSaveOSDData();
    }
    if(!GET_OSD_FACTORY_MODE_BRUNIN())
    {
        ScalerDDomainBackgroundSetColor(0, 0, 0);
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BURN_IN);
//DebugMessageRx1("burn_on", 1);        
        
        // Check NSG to PS condition in multi-display
        /*if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
        {
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
        }*/
        
    }
    else
    {
        if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
        {
//DebugMessageRx1("burn_on", 2);        
            ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BURN_IN);
        }
    }

 //   DebugMessageRx1("g_usAdjustValue", g_usAdjustValue);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

void RTDFactoryBurninOnOffLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BURNIN_ON_OFF, GET_OSD_FACTORY_MODE_BRUNIN());
}

void RTDFactoryBurninOnOffRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BURNIN_ON_OFF, GET_OSD_FACTORY_MODE_BRUNIN());
}

void RTDFactoryBurninOnOffExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

//============= Colortemp 1 R Adjust=======================
void RTDFactoryColortemp1RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
}

void RTDFactoryColortemp1RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp1RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp1RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
}

//============= Colortemp 1 G Adjust=======================
void RTDFactoryColortemp1GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

void RTDFactoryColortemp1GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp1GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp1GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

//============= Colortemp 1 B Adjust=======================
void RTDFactoryColortemp1BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
}

void RTDFactoryColortemp1BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp1BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp1BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
}

//============= Colortemp 2 R Adjust=======================
void RTDFactoryColortemp2RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
}

void RTDFactoryColortemp2RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp2RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp2RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
}

//============= Colortemp 2 G Adjust=======================
void RTDFactoryColortemp2GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

void RTDFactoryColortemp2GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp2GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp2GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

//============= Colortemp 2 B Adjust=======================
void RTDFactoryColortemp2BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
}

void RTDFactoryColortemp2BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp2BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp2BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
}

//============= Colortemp 3 R Adjust=======================
void RTDFactoryColortemp3RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
}

void RTDFactoryColortemp3RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp3RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp3RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
}

//============= Colortemp 3 G Adjust=======================
void RTDFactoryColortemp3GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

void RTDFactoryColortemp3GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp3GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp3GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

//============= Colortemp 3 B Adjust=======================
void RTDFactoryColortemp3BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
}

void RTDFactoryColortemp3BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp3BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp3BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
}

//============= Colortemp 4 R Adjust=======================
void RTDFactoryColortemp4RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
}

void RTDFactoryColortemp4RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp4RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp4RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
}

//============= Colortemp 4 G Adjust=======================
void RTDFactoryColortemp4GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

void RTDFactoryColortemp4GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp4GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp4GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

//============= Colortemp 4 B Adjust=======================
void RTDFactoryColortemp4BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
}

void RTDFactoryColortemp4BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp4BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp4BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
}

//============= Colortemp 5 R Adjust=======================
void RTDFactoryColortemp5RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
}

void RTDFactoryColortemp5RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp5RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp5RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
}

//============= Colortemp 5 G Adjust=======================
void RTDFactoryColortemp5GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

void RTDFactoryColortemp5GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp5GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp5GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

//============= Colortemp 5 B Adjust=======================
void RTDFactoryColortemp5BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
}

void RTDFactoryColortemp5BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp5BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp5BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
}

//============= Colortemp 6 R Adjust=======================
void RTDFactoryColortemp6RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
}

void RTDFactoryColortemp6RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp6RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp6RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
}

//============= Colortemp 6 G Adjust=======================
void RTDFactoryColortemp6GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

void RTDFactoryColortemp6GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp6GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp6GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

//============= Colortemp 6 B Adjust=======================
void RTDFactoryColortemp6BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
}

void RTDFactoryColortemp6BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp6BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp6BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
}

//============= Adc Gain R Adjust=======================
void RTDFactoryAdcGainRAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
#endif
}

void RTDFactoryAdcGainRAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_RED_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcGainRAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_RED_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcGainRAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL])
    {
        g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_RED_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
#endif
}

//============= Adc Gain G Adjust=======================
void RTDFactoryAdcGainGAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
#endif
}

void RTDFactoryAdcGainGAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_GREEN_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcGainGAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_GREEN_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcGainGAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL])
    {
        g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_GREEN_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
#endif
}

//============= Adc Gain B Adjust=======================
void RTDFactoryAdcGainBAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
#endif
}

void RTDFactoryAdcGainBAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_BLUE_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcGainBAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_BLUE_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcGainBAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL])
    {
        g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_BLUE_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
#endif
}

//============= Adc Offset R Adjust=======================
void RTDFactoryAdcOffsetRAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
#endif
}

void RTDFactoryAdcOffsetRAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_RED_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetRAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_RED_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetRAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL])
    {
        g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_RED_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
#endif
}

//============= Adc Offset G Adjust=======================
void RTDFactoryAdcOffsetGAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
#endif
}

void RTDFactoryAdcOffsetGAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_GREEN_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetGAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_GREEN_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetGAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL])
    {
        g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_GREEN_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
#endif
}

//============= Adc Offset B Adjust=======================
void RTDFactoryAdcOffsetBAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
#endif
}

void RTDFactoryAdcOffsetBAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_BLUE_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetBAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_BLUE_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetBAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL])
    {
        g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_BLUE_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
#endif
}

//============= Osd Page Adjust=======================
void RTDFactoryOsdPageAdjustEnter(void)
{
    if(g_ucFactoryPage == 1)
    {
        RTDFactoryMainMenu1();
    }
}

void RTDFactoryOsdPageAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPageAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPageAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);
}


//============= Background =======================
void RTDFactoryBgEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_ON_OFF);
}

void RTDFactoryBgLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

void RTDFactoryBgRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
}

void RTDFactoryBgExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Background R=======================
void RTDFactoryBgREnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED_ADJ);
}

void RTDFactoryBgRLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

void RTDFactoryBgRRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

void RTDFactoryBgRExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Background G=======================
void RTDFactoryBgGEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN_ADJ);
}

void RTDFactoryBgGLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

void RTDFactoryBgGRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

void RTDFactoryBgGExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Background B=======================
void RTDFactoryBgBEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE_ADJ);
}

void RTDFactoryBgBLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

void RTDFactoryBgBRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

void RTDFactoryBgBExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= SSC=======================
void RTDFactorySSCEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_SSC);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC_ADJ);
}

void RTDFactorySSCLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

void RTDFactorySSCRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

void RTDFactorySSCExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= LVDS Clock=======================
void RTDFactoryLVDSClockEnter(void)
{
	g_usBackupValue = g_usAdjustValue = _LVDS_VCM_CONTROL;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ);
}

void RTDFactoryLVDSClockLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryLVDSClockRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

void RTDFactoryLVDSClockExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= LVDS Data=======================
void RTDFactoryLVDSDataEnter(void)
{
	g_usBackupValue = g_usAdjustValue = _LVDS_DRIV_CONTROL;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA_CURRENT_ADJ);
}

void RTDFactoryLVDSDataLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

void RTDFactoryLVDSDataRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

void RTDFactoryLVDSDataExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Pattern =======================
/*
void RTDFactoryPatternEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_PATTERN_ADJ);
}

void RTDFactoryPatternLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

void RTDFactoryPatternRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryPatternExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
*/
//============= Hot Plug DP DC Off High=======================
void RTDFactoryHotPlugDPDCOffHighEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF);
}
void RTDFactoryHotPlugDPDCOffHighLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}

void RTDFactoryHotPlugDPDCOffHighRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryHotPlugDPDCOffHighExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Hot Plug HDMI Support=======================
void RTDFactoryHotPlugHDMISupportEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF);
}
void RTDFactoryHotPlugHDMISupportLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}

void RTDFactoryHotPlugHDMISupportRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

void RTDFactoryHotPlugHDMISupportExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Hot Plug HDMI Support Time=======================
void RTDFactoryHotPlugHDMISupportTimeEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ);
}
void RTDFactoryHotPlugHDMISupportTimeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_MODE);
}

void RTDFactoryHotPlugHDMISupportTimeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}

void RTDFactoryHotPlugHDMISupportTimeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= DP Aux Mode=======================
void RTDFactoryDPAuxModeEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE);
    g_usAdjustValue = g_usBackupValue;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_MODE_ON_OFF);
}

void RTDFactoryDPAuxModeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_DOUBLE_SIZE);
}

void RTDFactoryDPAuxModeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}

void RTDFactoryDPAuxModeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= OSD Double Size======================
void RTDFactoryOsdDoubleEnter(void)
{
    g_usBackupValue = GET_OSD_DOUBLE_SIZE();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_DOUBLE_SIZE_ON_OFF);
}

void RTDFactoryOsdDoubleLeft(void)
{
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORIMETRY_SEAMLESS);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_SETTING);
#endif
}

void RTDFactoryOsdDoubleRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_MODE);
}

void RTDFactoryOsdDoubleExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= COLORIMETRY SEAMLESS======================
void RTDFactoryColorimetrySeamlessEnter(void)
{
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    g_usBackupValue = UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE);
    g_usAdjustValue = g_usBackupValue;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORIMETRY_SEAMLESS_ON_OFF);
#endif
}

void RTDFactoryColorimetrySeamlessLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_SETTING);
}

void RTDFactoryColorimetrySeamlessRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_DOUBLE_SIZE);
}

void RTDFactoryColorimetrySeamlessExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= DP AUX Settung Adjust======================

void RTDFactoryDPAuxSettingEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING);
    g_usAdjustValue = g_usBackupValue;

    if(UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE) == _TRUE)
    {
        RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_SETTING_ADJR);
    }
}
void RTDFactoryDPAuxSettingLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_IRQ_TIME);
}
void RTDFactoryDPAuxSettingRight(void)
{
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORIMETRY_SEAMLESS);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_DOUBLE_SIZE);
#endif
}
void RTDFactoryDPAuxSettingExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= DP IRQ HDP adjust======================

void RTDFactoryDPIrqHpdEnter(void)
{
    g_usBackupValue = g_usAdjustValue = UserCommonNVRamGetSystemData(_DP_IRQ_TIME);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_IRQ_TIME_ADJ);
}
void RTDFactoryDPIrqHpdLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DDCCI);
}
void RTDFactoryDPIrqHpdRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_SETTING);
}
void RTDFactoryDPIrqHpdExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= ddcci adjust======================

void RTDFactoryDDCCIEnter(void)
{
    g_usBackupValue = g_usAdjustValue = GET_OSD_DDCCI_STATUS();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DDCCI_ADJ);
}
void RTDFactoryDDCCILeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EDIDEN);
}
void RTDFactoryDDCCIRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_IRQ_TIME);
}
void RTDFactoryDDCCIExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= ediden adjust======================

void RTDFactoryEDIDENEnter(void)
{
    g_usBackupValue = g_usAdjustValue = PCB_EDID_EEPROM_WRITE_PROTECT_DETECT();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EDIDEN_ADJ);
}
void RTDFactoryEDIDENLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LOGOEN);
}
void RTDFactoryEDIDENRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DDCCI);
}
void RTDFactoryEDIDENExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= logoen adjust======================

void RTDFactoryLogoENEnter(void)
{
    g_usBackupValue = g_usAdjustValue = UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LOGOEN_ADJ);
}
void RTDFactoryLogoENLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORTEMP);
}
void RTDFactoryLogoENRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EDIDEN);
}
void RTDFactoryLogoENExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= colortemp adjust======================

void RTDFactoryColorTempEnter(void)
{
    g_usBackupValue = g_usAdjustValue = GET_COLOR_TEMP_TYPE();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORTEMP_ADJ);
}
void RTDFactoryColorTempLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAMMA);
}
void RTDFactoryColorTempRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LOGOEN);
}
void RTDFactoryColorTempExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Gamma adjust======================

void RTDFactoryGAMMAEnter(void)
{
    g_usBackupValue = g_usAdjustValue = GET_OSD_GAMMA();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAMMA_ADJ);
}
void RTDFactoryGAMMALeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1);
}
void RTDFactoryGAMMARight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORTEMP);
}
void RTDFactoryGAMMAExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= Osd Page 1=======================
void RTDFactoryOsdPage1Enter(void)
{
    //RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1_ADJ);
    g_ucFactoryPage = 2;
    RTDFactoryMainMenu2();
}

void RTDFactoryOsdPage1Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
}

void RTDFactoryOsdPage1Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAMMA);
}

void RTDFactoryOsdPage1Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Exit=======================
void RTDFactoryExit1Enter(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

void RTDFactoryExit1Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

void RTDFactoryExit1Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1);
}

void RTDFactoryExit1Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= BG On Off=======================
void RTDFactoryBgOnOffEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

void RTDFactoryBgOnOffLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_ON_OFF, g_ucBgOnOff);
}

void RTDFactoryBgOnOffRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_ON_OFF, g_ucBgOnOff);
}

void RTDFactoryBgOnOffExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

//============= BG R Adjust=======================
void RTDFactoryBgRAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

void RTDFactoryBgRAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_RED_ADJ, g_ucBgColorR);
}

void RTDFactoryBgRAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_RED_ADJ, g_ucBgColorR);
}

void RTDFactoryBgRAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

//============= BG G Adjust=======================
void RTDFactoryBgGAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

void RTDFactoryBgGAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_GREEN_ADJ, g_ucBgColorG);
}

void RTDFactoryBgGAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_GREEN_ADJ, g_ucBgColorG);
}

void RTDFactoryBgGAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

//============= Adc Gain B Adjust=======================
void RTDFactoryBgBAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

void RTDFactoryBgBAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_BLUE_ADJ, g_ucBgColorB);
}

void RTDFactoryBgBAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_BLUE_ADJ, g_ucBgColorB);
}

void RTDFactoryBgBAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

//============= SSC Adjust=======================
void RTDFactorySSCAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_SSC))
    {    
        g_usAdjustValue = UserCommonNVRamGetSystemData(_SSC);
        UserCommonNVRamSetSystemData(_SSC, g_usAdjustValue);
        ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
	}
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

void RTDFactorySSCAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_SSC_ADJ, g_stSystemData.ucSSC);
}

void RTDFactorySSCAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_SSC_ADJ, g_stSystemData.ucSSC);
}

void RTDFactorySSCAdjustExit(void)
{
    if(g_usBackupValue != g_usAdjustValue)
    {
        g_usAdjustValue = g_usBackupValue;
        UserCommonNVRamSetSystemData(_SSC, g_usAdjustValue);
        ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
	}
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

//============= LVDS Clock Current Adjust=======================
void RTDFactoryLVDSClockCurrentAdjustEnter(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)
	ScalerDisplayVcmControl(_LVDS_VCM_CONTROL);
#endif
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

void RTDFactoryLVDSClockCurrentAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSClockCurrentAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSClockCurrentAdjustExit(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)
	ScalerDisplayVcmControl(_LVDS_VCM_CONTROL);
#endif
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

//============= LVDS Data Current Adjust=======================
void RTDFactoryLVDSDataCurrentAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryLVDSDataCurrentAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_DATA_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSDataCurrentAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_DATA_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSDataCurrentAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}


//============= Hot Plug DP DC Off High Adjust=======================
void RTDFactoryHotPlugDPDCOffHighAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}
void RTDFactoryHotPlugDPDCOffHighAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF, UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH));
}
void RTDFactoryHotPlugDPDCOffHighAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF, UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH));
}
void RTDFactoryHotPlugDPDCOffHighAdjustExit(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH))
    {
        UserCommonNVRamSetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH, g_usBackupValue);
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF, UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

//============= Hot Plug HDMI Support Adjus=======================
void RTDFactoryHotPlugHDMISupportAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}
void RTDFactoryHotPlugHDMISupportAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT));
}
void RTDFactoryHotPlugHDMISupportAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT));
}
void RTDFactoryHotPlugHDMISupportAdjustExit(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT))
    {
        UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT, g_usBackupValue);
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}

//============= Hot Plug HDMI Support Time Adjust=======================
void RTDFactoryHotPlugHDMISupportTimeAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}
void RTDFactoryHotPlugHDMISupportTimeAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
}
void RTDFactoryHotPlugHDMISupportTimeAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
}
void RTDFactoryHotPlugHDMISupportTimeAdjustExit(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME))
    {
        UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME, g_usBackupValue);
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}

//============= DP/HDMI FREESYNC  Adjust=======================
void RTDFactoryDPAuxModeAdjustEnter(void)
{
#if(_DP_SUPPORT == _ON)
    if(g_usBackupValue != g_usAdjustValue)
    {
        UserCommonNVRamSetSystemData(_DP_AUX_DIFF_MODE, g_usAdjustValue);
        UserCommonInterfaceDpAuxSet();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
#endif
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_MODE);
}

void RTDFactoryDPAuxModeAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_AUX_MODE_ON_OFF, UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE));
}

void RTDFactoryDPAuxModeAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_AUX_MODE_ON_OFF, UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE));
}

void RTDFactoryDPAuxModeAdjustExit(void)
{
#if(_DP_SUPPORT == _ON)
    if(g_usBackupValue != g_usAdjustValue)
    {
        g_usAdjustValue = g_usBackupValue;
        UserCommonNVRamSetSystemData(_DP_AUX_DIFF_MODE, g_usAdjustValue);
        UserCommonInterfaceDpAuxSet();
        RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_AUX_MODE_ON_OFF, g_usBackupValue);
    }
#endif
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_MODE);
}
//============= OSD Double Size=======================
void RTDFactoryOsdDoubleAdjustEnter(void)
{
    if(g_usBackupValue != GET_OSD_DOUBLE_SIZE())
    {
        SET_OSD_NVRAM_DOUBLE_SIZE(GET_OSD_DOUBLE_SIZE());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_DOUBLE_SIZE);
}

void RTDFactoryOsdDoubleAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_DOUBLE_SIZE_ON_OFF, GET_OSD_DOUBLE_SIZE());
}

void RTDFactoryOsdDoubleAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_DOUBLE_SIZE_ON_OFF, GET_OSD_DOUBLE_SIZE());
}

void RTDFactoryOsdDoubleAdjustExit(void)
{
    if(g_usBackupValue != GET_OSD_DOUBLE_SIZE())
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_DOUBLE_SIZE_ON_OFF, GET_OSD_DOUBLE_SIZE());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_DOUBLE_SIZE);
}
//============= COLORIMETRY SEAMLESS=======================
void RTDFactoryColorimetrySeamlessAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORIMETRY_SEAMLESS);
}

void RTDFactoryColorimetrySeamlessAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_COLORIMETRY_SEAMLESS_ON_OFF, g_usAdjustValue);
}

void RTDFactoryColorimetrySeamlessAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_COLORIMETRY_SEAMLESS_ON_OFF, g_usAdjustValue);
}

void RTDFactoryColorimetrySeamlessAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORIMETRY_SEAMLESS);
}
//============= DP AUX SETTING ADJUST =======================

void RTDFactoryDPAuxAdjustEnter(void)
{
    if(g_usBackupValue != g_usAdjustValue)
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_SETTING);
}
void RTDFactoryDPAuxAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_AUX_SETTING_ADJR, g_usAdjustValue);
}
void RTDFactoryDPAuxAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_AUX_SETTING_ADJR, g_usAdjustValue);
}
void RTDFactoryDPAuxAdjustExit(void)
{
    if(g_usBackupValue != g_usAdjustValue)
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_AUX_SETTING_ADJR, g_usBackupValue);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_AUX_SETTING);
}
//============= DP IRQ HDP adjust======================

void RTDFactoryDPIrqHpdAdjEnter(void)
{
    if(g_usBackupValue != g_usAdjustValue)
    {
        UserCommonNVRamSetSystemData(_DP_IRQ_TIME, g_usAdjustValue);

        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_IRQ_TIME);
}
void RTDFactoryDPIrqHpdAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_IRQ_TIME_ADJ, g_usAdjustValue);
}
void RTDFactoryDPIrqHpdAdjRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_IRQ_TIME_ADJ, g_usAdjustValue);
}
void RTDFactoryDPIrqHpdAdjExit(void)
{
    if(g_usAdjustValue != UserCommonNVRamGetSystemData(_DP_IRQ_TIME))
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_IRQ_TIME_ADJ, UserCommonNVRamGetSystemData(_DP_IRQ_TIME));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_IRQ_TIME);
}
//============= ddcci adjust======================

void RTDFactoryDDCCIAdjEnter(void)
{
    if(g_usAdjustValue != GET_OSD_DDCCI_STATUS())
    {
        SET_OSD_DDCCI_STATUS(g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DDCCI);
}
void RTDFactoryDDCCIAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DDCCI_ADJ, g_usAdjustValue);
}
void RTDFactoryDDCCIAdjRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DDCCI_ADJ, g_usAdjustValue);
}
void RTDFactoryDDCCIAdjExit(void)
{  
    if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_DDCCI_ADJ, GET_OSD_DDCCI_STATUS());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DDCCI);
}
//============= ediden adjust======================

void RTDFactoryEDIDENAdjEnter(void)
{
    if(g_usAdjustValue != PCB_EDID_EEPROM_WRITE_PROTECT_DETECT())
    {
        PCB_D0_EDID_EEPROM_WRITE_PROTECT(g_usAdjustValue);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EDIDEN);
}
void RTDFactoryEDIDENAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_EDIDEN_ADJ, g_usAdjustValue);
}
void RTDFactoryEDIDENAdjRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_EDIDEN_ADJ, g_usAdjustValue);
}
void RTDFactoryEDIDENAdjExit(void)
{  
    if(g_usBackupValue != PCB_EDID_EEPROM_WRITE_PROTECT_DETECT())
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_EDIDEN_ADJ, PCB_EDID_EEPROM_WRITE_PROTECT_DETECT());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EDIDEN);
}
//============= logoen adjust======================

void RTDFactoryLogoENAdjEnter(void)
{
    if(g_usBackupValue != g_usAdjustValue)
    {
        UserCommonNVRamSetSystemData(_DISPLAY_LOGO_MODE, g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);        
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LOGOEN);
}
void RTDFactoryLogoENAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LOGOEN_ADJ, g_usAdjustValue);
}
void RTDFactoryLogoENAdjRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LOGOEN_ADJ, g_usAdjustValue);
}
void RTDFactoryLogoENAdjExit(void)
{
    if(g_usAdjustValue != UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE))
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_LOGOEN_ADJ, UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LOGOEN);
}
//============= colortemp adjust======================

void RTDFactoryColorTempAdjEnter(void)
{
    if(g_usBackupValue != GET_COLOR_TEMP_TYPE())
    {  
        SET_COLOR_TEMP_TYPE(g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);        
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORTEMP);
}
void RTDFactoryColorTempAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_COLORTEMP_ADJ, GET_COLOR_TEMP_TYPE());
}
void RTDFactoryColorTempAdjRight(void)
{
    RTDFactoryColorTempAdjLeft();
}
void RTDFactoryColorTempAdjExit(void)
{
    if(g_usBackupValue != GET_COLOR_TEMP_TYPE())
    {
        g_usAdjustValue  = g_usBackupValue;
        SET_COLOR_TEMP_TYPE(g_usAdjustValue);
        RTDFactoryColorTempAdjLeft();
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_COLORTEMP);
}
//============= gamma adjust======================

void RTDFactoryGAMMAAdjEnter(void)
{
    if(g_usBackupValue != GET_OSD_GAMMA())
    {  
        SET_OSD_GAMMA(g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAMMA);
}
void RTDFactoryGAMMAAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAMMA_ADJ, GET_OSD_GAMMA());
}
void RTDFactoryGAMMAAdjRight(void)
{
    RTDFactoryGAMMAAdjLeft();
}
void RTDFactoryGAMMAAdjExit(void)
{
    if(g_usBackupValue != GET_OSD_GAMMA())
    {
        g_usAdjustValue  = g_usBackupValue;
        SET_OSD_GAMMA(g_usAdjustValue);
        RTDFactoryGAMMAAdjLeft();
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAMMA);
}

//============= Osd Page 1 Adjust=======================
void RTDFactoryOsdPage1AdjustEnter(void)
{
    if(g_ucFactoryPage == 2)
    {
        RTDFactoryMainMenu2();
    }
}

void RTDFactoryOsdPage1AdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_1_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPage1AdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_1_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPage1AdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
}
//============= PCM adjust======================

void RTDFactoryPCMEnter(void)
{
    g_usBackupValue = g_usAdjustValue = GET_OSD_PCM_STATUS();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_PCM_ADJ);

}
void RTDFactoryPCMLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_UIBACKLIGHT_VALUE);
}
void RTDFactoryPCMRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT2);
}
void RTDFactoryPCMExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

void RTDFactoryUIBackLightEnter(void)
{
    g_usBackupValue = g_usAdjustValue = GET_OSD_BACKLIGHT();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_UIBACKLIGHT_VALUE_ADJ);

}
void RTDFactoryUIBackLightLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MIN_POINT);
}
void RTDFactoryUIBackLightRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_PCM_VALUE);
}
void RTDFactoryUIBackLightExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= blmin adjust======================

void RTDFactoryBLMinPointEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_DUT_BACKLIGHT_MIN;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MIN_POINT_ADJ);

}
void RTDFactoryBLMinPointLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_CEN_POINT);
}
void RTDFactoryBLMinPointRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_UIBACKLIGHT_VALUE);
}
void RTDFactoryBLMinPointExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= blcen adjust======================

void RTDFactoryBLCenPointEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_DUT_BACKLIGHT_CENTER;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_CEN_POINT_ADJ);
}
void RTDFactoryBLCenPointLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MAX_POINT);
}
void RTDFactoryBLCenPointRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MIN_POINT);
}
void RTDFactoryBLCenPointExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= blmax adjust======================

void RTDFactoryBLMaxPointEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_DUT_BACKLIGHT_MAX;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MAX_POINT_ADJ);
}
void RTDFactoryBLMaxPointLeft(void)
{
if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_2);
else    
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryBLMaxPointRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_CEN_POINT);
}
void RTDFactoryBLMaxPointExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= blCalib adjust======================

void RTDFactoryBLCalibEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_BACKLIGHT_CALIB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB_ADJ);
}
void RTDFactoryBLCalibLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB+1);
}
void RTDFactoryBLCalibRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MAX_POINT);
}
void RTDFactoryBLCalibExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}


#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
//============= blDICOM adjust======================
void RTDFactoryBLDicomEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM_ADJ);
}
void RTDFactoryBLDicomLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM + 1);
}
void RTDFactoryBLDicomRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryBLDicomExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= blMcuUser adjust======================

void RTDFactoryBLUserEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_BACKLIGHT_MCU_CALIB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MCU_USER_ADJ);
}
void RTDFactoryBLUserLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_2);
}
void RTDFactoryBLUserRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM);
}
void RTDFactoryBLUserExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
//============= blDICOM adjust======================
void RTDFactoryBLDicomEnter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM_ADJ);
}
void RTDFactoryBLDicomLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM + 1);
}
void RTDFactoryBLDicomRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryBLDicomExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

#elif(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
//============= dicom600 adjust======================

void RTDFactoryDicom600Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_600;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM600_ADJ);
}
void RTDFactoryDicom600Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_2);
}
void RTDFactoryDicom600Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM550);
}
void RTDFactoryDicom600Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom550 adjust======================

void RTDFactoryDicom550Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_550;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM550_ADJ);
}
void RTDFactoryDicom550Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM600);
}
void RTDFactoryDicom550Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM500);
}
void RTDFactoryDicom550Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom500 adjust======================

void RTDFactoryDicom500Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_500;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM500_ADJ);
}
void RTDFactoryDicom500Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM550);
}
void RTDFactoryDicom500Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM450);
}
void RTDFactoryDicom500Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom450 adjust======================

void RTDFactoryDicom450Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_450;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM450_ADJ);
}
void RTDFactoryDicom450Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM500);
}
void RTDFactoryDicom450Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM400);
}
void RTDFactoryDicom450Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom400 adjust======================

void RTDFactoryDicom400Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_400;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM400_ADJ);
}
void RTDFactoryDicom400Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM450);
}
void RTDFactoryDicom400Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM350);
}
void RTDFactoryDicom400Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom350 adjust======================

void RTDFactoryDicom350Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_350;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM350_ADJ);
}
void RTDFactoryDicom350Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM400);
}
void RTDFactoryDicom350Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM300);
}
void RTDFactoryDicom350Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom300 adjust======================

void RTDFactoryDicom300Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_300;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM300_ADJ);
}
void RTDFactoryDicom300Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM350);
}
void RTDFactoryDicom300Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM250);
}
void RTDFactoryDicom300Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom250 adjust======================

void RTDFactoryDicom250Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_250;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM250_ADJ);
}
void RTDFactoryDicom250Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM300);
}
void RTDFactoryDicom250Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM200);
}
void RTDFactoryDicom250Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= dicom200 adjust======================

void RTDFactoryDicom200Enter(void)
{
    g_usBackupValue = g_usAdjustValue = _GET_USER_DICOM_BACKLIGHT_200;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM200_ADJ);
}
void RTDFactoryDicom200Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM250);
}
void RTDFactoryDicom200Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryDicom200Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

#else
#warning "!!!Please Check Gamma define"
#endif

//============= Osd Page 2=======================
void RTDFactoryOsdPage2Enter(void)
{
    //RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1_ADJ);
    g_ucFactoryPage = 0;
    RTDFactoryMainMenu();
}

void RTDFactoryOsdPage2Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT2);
}

void RTDFactoryOsdPage2Right(void)
{
if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MAX_POINT);    
else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_2 - 1);
}

void RTDFactoryOsdPage2Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Exit=======================
void RTDFactoryExit2Enter(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

void RTDFactoryExit2Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_PCM_VALUE);
}

void RTDFactoryExit2Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_2);
}

void RTDFactoryExit2Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= PCM adjust======================

void RTDFactoryPCMAdjEnter(void)
{
    if(g_usBackupValue != GET_OSD_PCM_STATUS())
    {  
        SET_OSD_PCM_STATUS(g_usAdjustValue);
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);        
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_PCM_VALUE);
}
void RTDFactoryPCMAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_PCM_ADJ, g_usAdjustValue);
}
void RTDFactoryPCMAdjRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_PCM_ADJ, g_usAdjustValue);
}
void RTDFactoryPCMAdjExit(void)
{
    if(g_usBackupValue != GET_OSD_PCM_STATUS())
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY2_PCM_ADJ, GET_OSD_PCM_STATUS());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_PCM_VALUE);
}


//=============  BackLight Sensor Save==================
void RTDFactorySaveUpdateBKSensor(void)
{
#if (_ENABLE_BACKLIGHT_SENSOR)
        // Update Sensor
		UpdateBacklightSensorValue();
		OsdFactoryBacklightSensorValueShow();	
#else
        RTDNVRamSaveOsdUser2Data();
#endif
}

//============= ULBackLight adjust======================
void RTDFactoryULBackLightAdjEnter(void)
{
    if(g_usBackupValue != GET_OSD_BACKLIGHT())
    {  
        SET_OSD_BACKLIGHT(g_usAdjustValue);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_UIBACKLIGHT_VALUE);
}
void RTDFactoryULBackLightAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_UIBACKLIGHT_VALUE_ADJ, g_usAdjustValue);
}
void RTDFactoryULBackLightAdjRight(void)
{
    RTDFactoryULBackLightAdjLeft();
}
void RTDFactoryULBackLightAdjExit(void)
{
    if(g_usBackupValue != GET_OSD_BACKLIGHT())
    {
        RTDFactoryULBackLightAdjLeft();
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_UIBACKLIGHT_VALUE);
}

//============= BLMinPoint adjust======================

void RTDFactoryBLMinPointAdjEnter(void)
{
    if(g_usBackupValue != _GET_DUT_BACKLIGHT_MIN)
    {  
        _SET_DUT_BACKLIGHT_MIN(g_usAdjustValue);
        RTDNVRamSaveOsdUser2Data();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MIN_POINT);
}
void RTDFactoryBLMinPointAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_MIN_POINT_ADJ, g_usAdjustValue);
}
void RTDFactoryBLMinPointAdjRight(void)
{
    RTDFactoryBLMinPointAdjLeft();
}
void RTDFactoryBLMinPointAdjExit(void)
{
    if(g_usBackupValue != _GET_DUT_BACKLIGHT_MIN)
    {
        g_usAdjustValue = g_usBackupValue;
        _SET_DUT_BACKLIGHT_MIN(g_usAdjustValue);
        RTDFactoryBLMinPointAdjLeft();
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MIN_POINT);
}

//============= BLCenPoint adjust======================
void RTDFactoryBLCenPointAdjEnter(void)
{
    if(g_usBackupValue != _GET_DUT_BACKLIGHT_CENTER)
    {  
        _SET_DUT_BACKLIGHT_CENTER(g_usAdjustValue);
        g_usBackupGammaValue = GET_OSD_GAMMA();
        
#if (_ENABLE_BACKLIGHT_SENSOR)
		// Update Restore BK Sensor
		g_bBacklightSensorValueRestoreStatus = _TRUE;
#endif
        RTDFactorySaveUpdateBKSensor();
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_CEN_POINT);
}

void RTDFactoryBLCenPointAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_18);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_CEN_POINT_ADJ, g_usAdjustValue);
}

void RTDFactoryBLCenPointAdjRight(void)
{
    RTDFactoryBLCenPointAdjLeft();
}

void RTDFactoryBLCenPointAdjExit(void)
{
    if(g_usBackupValue != _GET_DUT_BACKLIGHT_CENTER)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_DUT_BACKLIGHT_CENTER(g_usBackupValue);
        RTDFactoryBLCenPointAdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_CEN_POINT);
}

//============= BLMaxPoint adjust======================
void RTDFactoryBLMaxPointAdjEnter(void)
{
    if(g_usBackupValue != _GET_DUT_BACKLIGHT_MAX)
    {  
        _SET_DUT_BACKLIGHT_MAX(g_usAdjustValue);
        RTDNVRamSaveOsdUser2Data();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MAX_POINT);
}

void RTDFactoryBLMaxPointAdjLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_MAX_POINT_ADJ, g_usAdjustValue);
}

void RTDFactoryBLMaxPointAdjRight(void)
{
    RTDFactoryBLMaxPointAdjLeft();
}

void RTDFactoryBLMaxPointAdjExit(void)
{
    if(g_usBackupValue != _GET_DUT_BACKLIGHT_MAX)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_DUT_BACKLIGHT_MAX(g_usAdjustValue);
        RTDFactoryBLMaxPointAdjLeft();
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MAX_POINT);
}

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
//============= dicom adjust======================
void RTDFactoryDicomAdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT)
    {  
        _SET_USER_DICOM_BACKLIGHT(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM);
}
void RTDFactoryDicomAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_20);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM_ADJ, g_usAdjustValue);
}
void RTDFactoryDicomAdjRight(void)
{
    RTDFactoryDicomAdjLeft();
}
void RTDFactoryDicomAdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT(g_usAdjustValue);
        RTDFactoryDicomAdjLeft();
    }
    
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM);
}

//============= user adjust======================
void RTDFactoryUserAdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_MCU_CALIB)
    {  
        _SET_USER_BACKLIGHT_MCU_CALIB(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MCU_USER);
}
void RTDFactoryUserAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_22);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_MCU_USER_ADJ, g_usAdjustValue);
}
void RTDFactoryUserAdjRight(void)
{
    RTDFactoryUserAdjLeft();
}
void RTDFactoryUserAdjExit(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_MCU_CALIB)
    {
        g_usAdjustValue = g_usBackupValue;
        _SET_USER_BACKLIGHT_MCU_CALIB(g_usAdjustValue);
        RTDFactoryUserAdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_MCU_USER);
}

//============= calib adjust======================
void RTDFactoryCalibAdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_CALIB)
    {  
        _SET_USER_BACKLIGHT_CALIB(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryCalibAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_24);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_PC_CALIB_ADJ, g_usAdjustValue);
}
void RTDFactoryCalibAdjRight(void)
{
    RTDFactoryCalibAdjLeft();
}
void RTDFactoryCalibAdjExit(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_CALIB)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_BACKLIGHT_CALIB(g_usAdjustValue);
        RTDFactoryCalibAdjRight();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
       
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
//============= dicom adjust======================
void RTDFactoryDicomAdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT)
    {  
        _SET_USER_DICOM_BACKLIGHT(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM);
}
void RTDFactoryDicomAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_26);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM_ADJ, g_usAdjustValue);
}
void RTDFactoryDicomAdjRight(void)
{
    RTDFactoryDicomAdjLeft();
}
void RTDFactoryDicomAdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT(g_usAdjustValue);
        RTDFactoryDicomAdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM);
}

//============= calib adjust======================
void RTDFactoryCalibAdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_CALIB)
    {  
        _SET_USER_BACKLIGHT_CALIB(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryCalibAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_CALIB);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_PC_CALIB_ADJ, g_usAdjustValue);
}
void RTDFactoryCalibAdjRight(void)
{
    RTDFactoryCalibAdjLeft();
}
void RTDFactoryCalibAdjExit(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_CALIB)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_BACKLIGHT_CALIB(g_usAdjustValue);
        RTDFactoryCalibAdjRight();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}

#elif(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)

//============= dicom200 adjust======================
void RTDFactoryDicom200AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_200)
    {  
	    _SET_USER_DICOM_BACKLIGHT_200(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM200);
}
void RTDFactoryDicom200AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM200);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM200_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom200AdjRight(void)
{
    RTDFactoryDicom200AdjLeft();
}
void RTDFactoryDicom200AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_200)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_200(g_usAdjustValue);
        RTDFactoryDicom200AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM200);
}

//============= dicom250 adjust======================
void RTDFactoryDicom250AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_250)
    {  
	 _SET_USER_DICOM_BACKLIGHT_250(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM250);
}
void RTDFactoryDicom250AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM250);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM250_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom250AdjRight(void)
{
    RTDFactoryDicom250AdjLeft();
}
void RTDFactoryDicom250AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_250)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_250(g_usAdjustValue);
        RTDFactoryDicom250AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM250);
}
//============= dicom300 adjust======================
void RTDFactoryDicom300AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_300)
    {  
	 _SET_USER_DICOM_BACKLIGHT_300(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM300);
}
void RTDFactoryDicom300AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM300);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM300_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom300AdjRight(void)
{
    RTDFactoryDicom300AdjLeft();
}
void RTDFactoryDicom300AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_300)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_300(g_usAdjustValue);
        RTDFactoryDicom300AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM300);
}

//============= dicom350 adjust======================
void RTDFactoryDicom350AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_350)
    {  
	 _SET_USER_DICOM_BACKLIGHT_350(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM350);
}
void RTDFactoryDicom350AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM350);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM350_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom350AdjRight(void)
{
    RTDFactoryDicom350AdjLeft();
}
void RTDFactoryDicom350AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_350)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_350(g_usAdjustValue);
        RTDFactoryDicom350AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM350);
}

//============= dicom400 adjust======================
void RTDFactoryDicom400AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_400)
    {  
	 _SET_USER_DICOM_BACKLIGHT_400(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM400);
}
void RTDFactoryDicom400AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM400);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM400_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom400AdjRight(void)
{
    RTDFactoryDicom400AdjLeft();
}
void RTDFactoryDicom400AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_400)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_400(g_usAdjustValue);
        RTDFactoryDicom400AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM400);
}

//============= dicom450 adjust======================
void RTDFactoryDicom450AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_450)
    {  
        _SET_USER_DICOM_BACKLIGHT_450(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM450);
}
void RTDFactoryDicom450AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM450);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM450_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom450AdjRight(void)
{
    RTDFactoryDicom450AdjLeft();
}
void RTDFactoryDicom450AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_450)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_450(g_usAdjustValue);
        RTDFactoryDicom450AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM450);
}

//============= dicom500 adjust======================
void RTDFactoryDicom500AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_500)
    {  
        _SET_USER_DICOM_BACKLIGHT_500(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM500);
}
void RTDFactoryDicom500AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM500);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM500_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom500AdjRight(void)
{
    RTDFactoryDicom500AdjLeft();
}
void RTDFactoryDicom500AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_500)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_500(g_usAdjustValue);
        RTDFactoryDicom500AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM600);
}

//============= dicom550 adjust======================
void RTDFactoryDicom550AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_550)
    {  
        _SET_USER_DICOM_BACKLIGHT_550(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM550);
}
void RTDFactoryDicom550AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM550);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM550_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom550AdjRight(void)
{
    RTDFactoryDicom550AdjLeft();
}
void RTDFactoryDicom550AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_550)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_550(g_usAdjustValue);
        RTDFactoryDicom550AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM550);
}

//============= dicom600 adjust======================
void RTDFactoryDicom600AdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_600)
    {  
        _SET_USER_DICOM_BACKLIGHT_600(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM600);
}
void RTDFactoryDicom600AdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_DICOM600);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_DICOM600_ADJ, g_usAdjustValue);
}
void RTDFactoryDicom600AdjRight(void)
{
    RTDFactoryDicom600AdjLeft();
}
void RTDFactoryDicom600AdjExit(void)
{
    if(g_usBackupValue != _GET_USER_DICOM_BACKLIGHT_600)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_DICOM_BACKLIGHT_600(g_usAdjustValue);
        RTDFactoryDicom600AdjLeft();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_DICOM600);
}

//============= calib adjust======================
void RTDFactoryCalibAdjEnter(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_CALIB)
    {  
        _SET_USER_BACKLIGHT_CALIB(g_usAdjustValue);
        RTDFactorySaveUpdateBKSensor();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}
void RTDFactoryCalibAdjLeft(void)
{
    SET_OSD_GAMMA(_GAMMA_CALIB);
    RTDFactoryOsdDispNumber(_MENU_FACTORY2_BL_PC_CALIB_ADJ, g_usAdjustValue);
}
void RTDFactoryCalibAdjRight(void)
{
    RTDFactoryCalibAdjLeft();
}
void RTDFactoryCalibAdjExit(void)
{
    if(g_usBackupValue != _GET_USER_BACKLIGHT_CALIB)
    {
        g_usAdjustValue = g_usBackupValue;
	    _SET_USER_BACKLIGHT_CALIB(g_usAdjustValue);
        RTDFactoryCalibAdjRight();
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY2_BL_PC_CALIB);
}

#else
#warning "!!!Please Check Gamma define"

#endif        



//============= Osd Page 2 Adjust=======================
void RTDFactoryOsdPage2AdjustEnter(void)
{
    if(g_ucFactoryPage == 0)
    {
        RTDFactoryMainMenu();
    }
}

void RTDFactoryOsdPage2AdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_2_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPage2AdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_2_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPage2AdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT2);
}

