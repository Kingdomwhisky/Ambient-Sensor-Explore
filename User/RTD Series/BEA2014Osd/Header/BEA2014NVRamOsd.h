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
// ID Code      : BEA2014NVRamOsd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _BEACON_2014_OSD)

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
#define _PANEL_INDEX_ADDRESS                           (_VGA_MODE_DATA_ADDRESS_END + 1)
#define _OSD_DATA_ADDRESS                              (_PANEL_INDEX_ADDRESS + 1)
//#define _OSD_INPUT_MODE_ADDRESS                        (_OSD_DATA_ADDRESS + sizeof(StructOsdUserDataType))
#define _BRICON_DATA_ADDRESS                           (_OSD_DATA_ADDRESS + sizeof(StructOsdUserDataType))
#define _COLORTEMP_DATA_ADDRESS                        (_BRICON_DATA_ADDRESS + (sizeof(StructBriConDataType) * _SOURCE_AMOUNT))
#define _SIXCOLOR_DATA_ADDRESS                         (_COLORTEMP_DATA_ADDRESS + (sizeof(StructColorProcDataType) * (_CT_COLORTEMP_AMOUNT + 1)))
#define _OSD_DATA_USER_ADDRESS_END                     (_SIXCOLOR_DATA_ADDRESS + sizeof(StructSixColorDataType))
//---------------------------------------------------------------------------------------------------------------------------------------

#define _FACTORY_SETTING_DATA_ADDRESS                  (_OSD_DATA_USER_ADDRESS_END)

//--------------------------------------------
// VGA+DP+HDMI+DualDVI: _OSD_DATA_USER_ADDRESS_END = 0x178  DP+HDMI+DualDVI: _OSD_DATA_USER_ADDRESS_END = 0x7E 
//#warning "_OSD_DATA_USER_ADDRESS_END < 0x1F0"
//--------------------------------------------
#define _USER_CALIB_LUT_DATA_ADDRESS                   (0x1F0) // (_FACTORY_SETTING_DATA_ADDRESS + 1)
#define _USER_CALIB_LUT_DATA_ADDRESS_END               (_USER_CALIB_LUT_DATA_ADDRESS + sizeof(StructOsdUserCalibLutDataType) - 1)

//#warning "_USER_CALIB_LUT_DATA_ADDRESS_END < 0x200"
#define _PANEL_TIME_DATA_ADDRESS                       (0x200)
#define _PANEL_TIME_DATA_ADDRESS_END                   (_PANEL_TIME_DATA_ADDRESS + sizeof(StructTimeType))

#define _OSD_MCU_VERSION_ADDRESS                       (0x20E)
#define _OSD_FPGA_P_VERSION_ADDRESS                    (0x20F)

#define _MONITOR_SN_DATA_ADDRESS                       (0x210)  
#define _MONITOR_SN_DATA_ADDRESS_END                   (_MONITOR_SN_DATA_ADDRESS + _SN_BUF_LENGTH - 1)

#define _MONITOR_IDSN_DATA_ADDRESS                     (_MONITOR_SN_DATA_ADDRESS_END + 1)  
#define _MONITOR_IDSN_DATA_ADDRESS_END                 (_MONITOR_IDSN_DATA_ADDRESS + _IDSN_BUF_LENGTH - 1)

#define _USER_PANEL_LUT_LUX_RANGE_VERSION_ADDRESS      (0x22E)
#define _USER_PANEL_LUT_LUX_AB_VERSION_ADDRESS         (0x22F)

#define _USER_PANEL_LUX_AB_DATA_ADDRESS                (0x230)
#define _USER_PANEL_LUX_AB_DATA_ADDRESS_END            (_USER_PANEL_LUX_AB_DATA_ADDRESS + (sizeof(StructPanelLuxABDataType) * _BK_SENSOR_POS_AMOUNT) - 1)

#define _USER_PANEL_LUX_RANGE_DATA_ADDRESS             (_USER_PANEL_LUX_AB_DATA_ADDRESS_END + 1)
#define _USER_PANEL_LUX_RANGE_DATA_ADDRESS_END         (_USER_PANEL_LUX_RANGE_DATA_ADDRESS + (sizeof(StructPanelLuxRangeDataType) * _BK_SENSOR_CT_AMOUNT) - 1)

#define _OSD_USER2_DATA_ADDRESS                        (0x280)
#define _OSD_USER2_DATA_ADDRESS_END                    (_OSD_USER2_DATA_ADDRESS + sizeof(StructOsdUser2DataType) - 1)

#define _USER_PANEL_AMB_AB_VERSION_ADDRESS             (_OSD_USER2_DATA_ADDRESS_END)

#define _USER_PANEL_AMB_AB_DATA_ADDRESS                (_USER_PANEL_AMB_AB_VERSION_ADDRESS+2)
#define _USER_PANEL_AMB_AB_DATA_ADDRESS_END            (_USER_PANEL_AMB_AB_DATA_ADDRESS + (sizeof(StructPanelAmbABDataType) ) - 1)

// _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT define default Lut_Attri
#define _FT_LUTATTRIELEM_VERSION_ADDRESS               (0x2800)
#define _FT_LUTATTRIELEM_ADDRESS 			           (0x2802)  //  _GAMMA_AMOUNT * 2CT * sizeof(Lut_Attri)
#define _FT_LUTATTRIELEM_ADDRESS_END 			       (_FT_LUTATTRIELEM_ADDRESS + (20 * sizeof(Lut_Attri)))

//--------------------------------------------------------------------------------------------
#endif

typedef struct
{
    WORD usBackLight;
    WORD usBackLight_CT2;
    WORD usBackLight_CT3;

    WORD usPCMBackLight;
    WORD usPCMBackLight_CT2;
    
    BYTE ucOsdHPos;
    BYTE ucOsdVPos;
    BYTE ucOsdTimeout;
    BYTE ucAspectOriginRatio;
    BYTE ucTransparency;
//--------------------------------------------------------
    BYTE b4Language : 4;
    BYTE b4ColorEffect : 4;
//--------------------------------------------------------
    BYTE b4ColorTempType : 4;
    BYTE b3VGARGBYUV : 3;
    BYTE b3DVIRGBYUV : 3;
//--------------------------------------------------------
    BYTE b3Sharpness : 3;
    BYTE b2OsdRotate : 2;
    BYTE b2DispRotationSizeType : 2;
    BYTE b1OverScan : 1;
//--------------------------------------------------------
    BYTE b5Gamma : 5;
    BYTE b3AspectRatio : 3;
//--------------------------------------------------------
    BYTE ucODGain;
    BYTE ucHue;
    BYTE ucSaturation;
    BYTE ucHLWinType;
//--------------------------------------------------------
    BYTE b3PCMStatus : 3;
    BYTE b2UltraVividStatus : 2;
    BYTE b1VolumeMute : 1;
    BYTE b1AudioStandAloneStatus : 1;
    BYTE b1AudioSourceStatus : 1;
//--------------------------------------------------------
    BYTE ucVolume;
//--------------------------------------------------------
    BYTE b1ODStatus : 1;
    BYTE b33DConvergenceMode : 3;
    BYTE b1FactoryAutoColorType : 1;
    BYTE b1PanelUniformity : 1;
    BYTE b1PCMSoftProftMode : 1;
    BYTE b1DDCCIStatus : 1;
//--------------------------------------------------------
    BYTE ucOsdInputPort;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    BYTE b1D0TypeCU3Mode : 1;
    BYTE b1D1TypeCU3Mode : 1;
    BYTE b1D2TypeCU3Mode : 1;
    BYTE b1D6TypeCU3Mode : 1;
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    BYTE b1D0TypeCPinAssignmentESupportSelect : 1;
    BYTE b1D1TypeCPinAssignmentESupportSelect : 1;
    BYTE b1D2TypeCPinAssignmentESupportSelect : 1;
    BYTE b1D6TypeCPinAssignmentESupportSelect : 1;
#endif
#endif
//--------------------------------------------------------
    BYTE b2OsdDpD0PortVersion : 2;
    BYTE b2OsdDpD1PortVersion : 2;
    BYTE b2OsdDpD2PortVersion : 2;
    BYTE b2OsdDpD6PortVersion : 2;
//--------------------------------------------------------
    BYTE b1OsdDpVersionHotKeyDisp : 1;
    BYTE b1PreShowDpHotKeyVersion : 1;
    BYTE b3PanelUniformityType : 3;
    BYTE b3OsdDispRotate : 3;
//--------------------------------------------------------
    BYTE b1FreeSyncStatus : 1;
    BYTE b1CloneMode : 1;
    BYTE b2LatencyStatus : 2;
    BYTE b1OsdDoubleSize : 1;
    BYTE b3OsdDpMST : 3;
//--------------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
    BYTE ucHdrMode;
    BYTE b1DarkEnhanceStatus : 1;
    BYTE b1HdrSharpnesse : 1;
    BYTE ucHdrContrast;
    BYTE ucHdrColorEnhance;
    BYTE ucHdrLightEnhance;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    BYTE b1HdrLocalDimming : 1;
    BYTE ucHdrLocalDimmingAdj;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
    BYTE b1Sdr2HdrStatus : 1;
#endif
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    BYTE b2OsdHdmiD0PortVersion : 2;
    BYTE b2OsdHdmiD1PortVersion : 2;
    BYTE b2OsdHdmiD2PortVersion : 2;
    BYTE b2OsdHdmiD3PortVersion : 2;
    BYTE b2OsdHdmiD4PortVersion : 2;
    BYTE b2OsdHdmiD5PortVersion : 2;
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    BYTE b1OsdUsb3RetimerPDWakeUp: 1;
    BYTE b1OsdUsb3RetimerPSWakeUp: 1;
    EnumHubInputPort enumHubInputPortSwitchbyUser;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    BYTE b2MbrStatus : 2;
    BYTE b7MbrDuty : 7;
    BYTE b7MbrPosition : 7;
#endif

//--------------------------------------------------------
#if 1//(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    BYTE b3ColorGamma: 3;
    BYTE b3GrayGamma: 3;
#endif
    BYTE b12HoursTips : 1;	    
    BYTE b1FactoryBrunInMode : 1;
//--------------------------------------------------------

    BYTE b1BacklightSensorMode : 1;
    BYTE b2DistanceSensorMode : 2;
    BYTE b1AmbientlightSensorMode : 1;
    BYTE b2ReadingReportMode : 2;    
    BYTE b2FPGATestMapIndex : 2;
//--------------------------------------------------------
    
    BYTE b2PowerSavingMode : 2;
    BYTE b1LightBoxModeStatus : 1;
    BYTE b3BackgroundLightMode : 3;
    BYTE b1GravitySensorMode : 1;
//--------------------------------------------------------
        
    BYTE b3UserBaseColorTempType : 3;
    BYTE b3DicomALC : 3; 
    BYTE b1OsdDcrStatus : 1;
    BYTE b1PanelUseLifeTips : 1;	    

    BYTE b4PCMInputGamma : 4;
    BYTE b1RS232Status : 1; //
#if(_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)    
    BYTE b2RGBtMode : 2;  
    BYTE b3RGBLightMode : 3;   
    
#endif    
    
//--------------------------------------------------------

    BYTE ucOsdPostion;	
    WORD usLocalEnhancementWindowZoom;
} StructOsdUserDataType;
/*
typedef struct
{
    BYTE ucOsdInputPort;
} StructOsdInputPortType;
*/
typedef struct
{
    WORD usColorTempR;
    WORD usColorTempG;
    WORD usColorTempB;
} StructColorProcDataType;

typedef struct
{
    WORD usBrightness;
    WORD usContrast;

} StructBriConDataType;

typedef struct
{
    WORD usHour;
    BYTE ucMin;
    WORD usSystemRunHour;
    BYTE ucSystemRunMin;
    WORD usPanelRunHour;
    BYTE ucPanelRunMin;
    BYTE b4SystemRunOverflow : 4;
    BYTE b4PanelRunOverflow : 4;
} StructTimeType;

typedef struct
{
    BYTE ucSixColorHueR;
    BYTE ucSixColorSaturationR;
    BYTE ucSixColorHueY;
    BYTE ucSixColorSaturationY;
    BYTE ucSixColorHueG;
    BYTE ucSixColorSaturationG;
    BYTE ucSixColorHueC;
    BYTE ucSixColorSaturationC;
    BYTE ucSixColorHueB;
    BYTE ucSixColorSaturationB;
    BYTE ucSixColorHueM;
    BYTE ucSixColorSaturationM;
} StructSixColorDataType;

//----------------------------------------------------
typedef struct
{
	BYTE ucLutUserType;    // Gamma or Dicom
    WORD usLutUserLMax;    
    BYTE ucLutUserLMin;    
    BYTE ucLutUserLAMB;    
    BYTE ucLutUserValue;   // Gamma Curve  
    WORD usLutUserLutOffset;    
}StructOsdUserCalibLutDataType;

typedef struct
{
	// Panel Luminance AB factor in bypass mode
	float ucA_Data;    
	float ucB_Data;    

}StructPanelLuxABDataType;
typedef struct
{
	// Panel Luminance AB factor in bypass mode
	float usA_Data;    
	float usB_Data;    

}StructPanelAmbABDataType;

typedef struct
{
	// Off LUT Panel Luminance    
	// Native effect Panel LUT Luminance under beacon gamma correction
	float ucLuxMax;  
	float ucLuxMin; 
	// On  LUT Panel Luminance 
	// Correction effect panel LUT Luminance under beacon gamma correction
	float ucRealLuxMax; 
	float ucRealLuxMin;  
	
} StructPanelLuxRangeDataType;

typedef struct
{
    WORD usBackLight_Min;
    WORD usBackLight_Cen;
    WORD usBackLight_Max;
    
	WORD usBacklightSensorValue;
    // Restore G2.2
	WORD usBacklightRestoreSensorValue;

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
	WORD usDicomBacklight;
	WORD usDicomBacklightSensorValue;
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
	WORD usBacklightMCUCalibration;
	WORD usBacklightMCUCalibrationSensorValue;
#endif

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT)
	WORD usDicomBacklight200;
	WORD usDicomBacklight250;
	WORD usDicomBacklight300;
	WORD usDicomBacklight350;
	WORD usDicomBacklight400;
	WORD usDicomBacklight450;
	WORD usDicomBacklight500;
	WORD usDicomBacklight550;
	WORD usDicomBacklight600;
	WORD usDicomBacklight650;
	WORD usDicomBacklight700;
    
	WORD usDicomBacklight200SensorValue;
	WORD usDicomBacklight250SensorValue;
	WORD usDicomBacklight300SensorValue;    
	WORD usDicomBacklight350SensorValue;
	WORD usDicomBacklight400SensorValue;
	WORD usDicomBacklight450SensorValue;
	WORD usDicomBacklight500SensorValue;
	WORD usDicomBacklight550SensorValue;
	WORD usDicomBacklight600SensorValue;
	WORD usDicomBacklight650SensorValue;
	WORD usDicomBacklight700SensorValue;
#endif

#if 1//(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)
	WORD usBacklightCalibration;
	WORD usBacklightCalibrationSensorValue;
#endif

#if 1//(NATIVE:_GAMMA_OFF)
	WORD usNativeBacklight;
	WORD usNativeBacklightSensorValue;
#endif

    // OCC:PCM
    WORD usPCMBackLight_Cen;
	WORD usPCMBacklightSensorValue;
	WORD usPCMBacklightRestoreSensorValue;

    WORD usBackLight_Min_CT2;
    WORD usBackLight_Cen_CT2;
    WORD usBackLight_Max_CT2;
    
	WORD usBacklightSensorValue_CT2;
    // Restore G2.2
	WORD usBacklightRestoreSensorValue_CT2;

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
	WORD usDicomBacklight_CT2;
	WORD usDicomBacklightSensorValue_CT2;
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
	WORD usBacklightMCUCalibration_CT2;
	WORD usBacklightMCUCalibrationSensorValue_CT2;
#endif

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT)
	WORD usDicomBacklight200_CT2;
	WORD usDicomBacklight250_CT2;
	WORD usDicomBacklight300_CT2;
	WORD usDicomBacklight350_CT2;
	WORD usDicomBacklight400_CT2;
	WORD usDicomBacklight450_CT2;
	WORD usDicomBacklight500_CT2;
	WORD usDicomBacklight550_CT2;
	WORD usDicomBacklight600_CT2;
	WORD usDicomBacklight650_CT2;
	WORD usDicomBacklight700_CT2;
    
	WORD usDicomBacklight200SensorValue_CT2;
	WORD usDicomBacklight250SensorValue_CT2;
	WORD usDicomBacklight300SensorValue_CT2;    
	WORD usDicomBacklight350SensorValue_CT2;
	WORD usDicomBacklight400SensorValue_CT2;
	WORD usDicomBacklight450SensorValue_CT2;
	WORD usDicomBacklight500SensorValue_CT2;
	WORD usDicomBacklight550SensorValue_CT2;
	WORD usDicomBacklight600SensorValue_CT2;
	WORD usDicomBacklight650SensorValue_CT2;
	WORD usDicomBacklight700SensorValue_CT2;
#endif
	
    // OCC:PCM CT2
    WORD usPCMBackLight_Cen_CT2;
	WORD usPCMBacklightSensorValue_CT2;
	WORD usPCMBacklightRestoreSensorValue_CT2;

    WORD usBackLight_Min_CT3;
    WORD usBackLight_Cen_CT3;
    WORD usBackLight_Max_CT3;

	WORD usBacklightSensorValue_CT3;
    // Restore G2.2
	WORD usBacklightRestoreSensorValue_CT3;

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
	WORD usDicomBacklight_CT3;
	WORD usDicomBacklightSensorValue_CT3;
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
	WORD usBacklightMCUCalibration_CT3;
	WORD usBacklightMCUCalibrationSensorValue_CT3;
#endif
} StructOsdUser2DataType;

#if 1
typedef enum _EM_CURVE_TYPE_
{
	CURVE_GAMMA,            // Standard gamma curve type
	CURVE_DICOM,            // Standard Dicom curve type
	CURVE_CIE,
	CURVE_USE_DEFINE_GUID,  // for user calibrate
	CURVE_ONLY_BRIGTE,      // DICOM shares a Lut,only calibrated bright
	CURVE_NATIVE,           // for Lut Bypass not use
	
	CURVE_OUT_RANGE         // Define the upper limit of the type
}emCurveType;

// lut gamma attribute
typedef struct 
{	
	BYTE curve;         //gamma type, please see emCurveType definition
	
	BYTE backlight[2];	//Menu backlight value, value range 0 ~255 or 0~4095
                            //[0] low byte
                            //[1] hight byte
	BYTE value[2];      /*   value*100 if the type is not LC_USE_DEFINE_GUID
                                gamma value for the LC_GAMMA,
                                ambient for teh LC_DICOM,
                                the curve GUID for the LC_USE_DEFINE_GUID*/ //Define the ambient brightness value.
                            //[0] low byte
                            //[1] hight byte
	BYTE maxLuminance[2];  // in cd/m2 *10
                            //[0] low byte
                            //[1] hight byte
	BYTE contrast[2];      // 
                            //[0] low byte
                            //[1] hight byte
}Lut_Attri;
#endif


#ifndef __RTD_NVRAM_OSD__
//----------------------------------------------------------------------------------------
// Extern Variables from RTD2011NVRamOsd.c
//----------------------------------------------------------------------------------------
extern BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
extern WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];

//----------------------------------------------------------------------------------------
// Extern functions from RTD2011NVRamOsd.c
//----------------------------------------------------------------------------------------

extern StructOsdUserDataType g_stOSDUserData;
//extern StructOsdInputPortType g_stOsdInputPortData;
extern StructBriConDataType g_stBriConData;
extern StructColorProcDataType g_stColorProcData;
extern code StructColorProcDataType tColorTempDefaultData[];
extern StructSixColorDataType g_stSixColorData;
extern StructOsdUserCalibLutDataType g_stUserCalibLutData;
extern StructPanelLuxABDataType g_stPanelLuxABData[3];
extern StructPanelAmbABDataType g_stPanelAmbABData;
extern StructPanelLuxRangeDataType g_stPanelLuxRangeData[2];
extern StructTimeType g_stPanelTimeData;
extern StructOsdUser2DataType g_stOsdUser2Data;

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern void RTDEepromStartup(void);
extern void RTDEepromWholeRestore(void);
extern void RTDEepromRestoreBacklight(void);
extern void RTDEepromLoadOSDData(void);
extern void RTDEepromSaveOSDData(void);
extern void RTDEepromRestoreOSDData(void);
/*
extern void RTDEepromLoadOsdInputPortData(void);
extern void RTDEepromSaveOsdInputPortData(void);
extern void RTDEepromRestoreOsdInputPortData(void);
*/
extern void RTDEepromLoadBriCon(BYTE ucSource);
extern void RTDEepromSaveBriCon(BYTE ucSource);
extern void RTDEepromRestoreBriCon(void);
extern void RTDEepromLoadColorSetting(BYTE ucColorTempType);
extern void RTDEepromSaveColorSetting(BYTE ucColorTempType);
extern void RTDEepromRestoreColorSetting(void);
extern void RTDEepromRestoreUserColorSetting(void);
extern void RTDEepromSaveSixColorData(void);
extern void RTDEepromRestoreSixColorData(void);

extern void RTDEepromLoadUserCalibLutData(void);
extern void RTDEepromSaveUserCalibLutData(void);
extern void RTDEepromRestoreUserCalibLutData(void);

extern void RTDEepromLoadPanelUsedTimeData(void);
extern void RTDEepromSavePanelUsedTimeData(void);
extern void RTDEepromRestorePanelUsedTimeData(void);

extern void RTDEepromLoadOsdUser2Data(void);
extern void RTDEepromSaveOsdUser2Data(void);
extern void RTDEepromRestoreOsdUser2Data(void);

#define RTDNVRamStartup()                              RTDEepromStartup()
#define RTDNVRamWholeRestore()                         RTDEepromWholeRestore()
#define RTDNVRamRestoreBacklight()                     RTDEepromRestoreBacklight()
#define RTDNVRamSaveOSDData()                          RTDEepromSaveOSDData()
#define RTDNVRamRestoreOSDData()                       RTDEepromRestoreOSDData()
//#define RTDNVRamLoadOsdInputPortData()                 RTDEepromLoadOsdInputPortData()
//#define RTDNVRamSaveOsdInputPortData()                 RTDEepromSaveOsdInputPortData()
//#define RTDNVRamRestoreOsdInputPortData()              RTDEepromRestoreOsdInputPortData()

#define RTDNVRamLoadBriCon(x)                          RTDEepromLoadBriCon(x)
#define RTDNVRamSaveBriCon(x)                          RTDEepromSaveBriCon(x)
#define RTDNVRamRestoreBriCon()                        RTDEepromRestoreBriCon()
#define RTDNVRamLoadColorSetting(x)                    RTDEepromLoadColorSetting(x)
#define RTDNVRamSaveColorSetting(x)                    RTDEepromSaveColorSetting(x)
#define RTDNVRamRestoreColorSetting()                  RTDEepromRestoreColorSetting()
#define RTDNVRamRestoreUserColorSetting()              RTDEepromRestoreUserColorSetting()
#define RTDNVRamSaveSixColorData()                     RTDEepromSaveSixColorData()
#define RTDNVRamRestoreSixColorData()                  RTDEepromRestoreSixColorData()
#define RTDNVRamLoadUserLutData()                      RTDEepromLoadUserCalibLutData()
#define RTDNVRamSaveUserLutData()                      RTDEepromSaveUserCalibLutData()
#define RTDNVRamRestoreUserLutData()                   RTDEepromRestoreUserCalibLutData()
#define RTDNVRamLoadPanelUsedTimeData(x)               RTDEepromLoadPanelUsedTimeData(x)
#define RTDNVRamSavePanelUsedTimeData()                RTDEepromSavePanelUsedTimeData()
#define RTDNVRamRestorePanelUsedTimeData()             RTDEepromRestorePanelUsedTimeData()

//#define RTDNVRamLoadOsdUser2Data()                      RTDEepromLoadOsdUser2Data()
#define RTDNVRamSaveOsdUser2Data()                      RTDEepromSaveOsdUser2Data()
#define RTDNVRamRestoreOsdUser2Data()                   RTDEepromRestoreOsdUser2Data()

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);
extern void RTDFlashStartup(void);
extern void RTDFlashWholeRestore(void);
extern void RTDFlashRestoreBacklight(void);
extern void RTDFlashSaveOSDData(void);
extern void RTDFlashRestoreOSDData(void);
extern void RTDFlashLoadBriCon(BYTE ucSource);
extern void RTDFlashSaveBriCon(BYTE ucSource);
extern void RTDFlashRestoreBriCon(void);
extern void RTDFlashLoadColorSetting(BYTE ucColorTempType);
extern void RTDFlashSaveColorSetting(BYTE ucColorTempType);
extern void RTDFlashRestoreColorSetting(void);
extern void RTDFlashRestoreUserColorSetting(void);
extern void RTDFlashSaveSixColorData(void);
extern void RTDFlashRestoreSixColorData(void);
extern void RTDFlashSavePanelUsedTimeData(void);

#define RTDNVRamStartup()                              RTDFlashStartup()
#define RTDNVRamWholeRestore()                         RTDFlashWholeRestore()
#define RTDNVRamRestoreBacklight()                     RTDFlashRestoreBacklight()
#define RTDNVRamSaveOSDData()                          RTDFlashSaveOSDData()
#define RTDNVRamRestoreOSDData()                       RTDFlashRestoreOSDData()
#define RTDNVRamLoadBriCon(x)                          RTDFlashLoadBriCon(x)
#define RTDNVRamSaveBriCon(x)                          RTDFlashSaveBriCon(x)
#define RTDNVRamRestoreBriCon()                        RTDFlashRestoreBriCon()
#define RTDNVRamLoadColorSetting(x)                    RTDFlashLoadColorSetting(x)
#define RTDNVRamSaveColorSetting(x)                    RTDFlashSaveColorSetting(x)
#define RTDNVRamRestoreColorSetting()                  RTDFlashRestoreColorSetting()
#define RTDNVRamRestoreUserColorSetting()              RTDFlashRestoreUserColorSetting()
#define RTDNVRamSaveSixColorData()                     RTDFlashSaveSixColorData()
#define RTDNVRamRestoreSixColorData()                  RTDFlashRestoreSixColorData()
#define RTDNVRamSavePanelUsedTimeData()                RTDFlashSavePanelUsedTimeData()

#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

#endif // End of #ifndef __RTD_NVRAM_OSD__

#if 1//(_BEACON_MONITOR_SN_SET_FUNCTION == _ON)
extern bit RTDNVRamLoadMonitorSNData(BYTE *pucData);
extern bit RTDNVRamSaveMonitorSNData(BYTE ucLength, BYTE *pucData);
extern bit RTDNVRamLoadMonitorIDSNData(BYTE *pucData);
extern bit RTDNVRamSaveMonitorIDSNData(BYTE ucLength, BYTE *pucData);
#endif // End of #if (_BEACON_MONITOR_SN_SET_FUNCTION == _ON)

extern void RTDNVRamLoadPanelLuxABData(void);
extern void RTDNVRamSavePanelLuxABData(void);
extern void RTDNVRamRestorePanelLuxABData(void);

extern void RTDNVRamLoadPanelAmbABData(void);
extern void RTDNVRamSavePanelAmbABData(void);
extern void RTDNVRamRestorePanelAmbABData(void);

extern void RTDNVRamLoadPanelLuxRangeData(void);
extern void RTDNVRamSavePanelLuxRangeData(void);
extern void RTDNVRamRestorePanelLuxRangeData(void);

extern void RTDNVRamCheckPanelLuxUserLutData(void);

extern void RTDNVRamRestoreLutAttriData(void);

extern void ReadFWVersion(BYTE *buffer, BYTE IndexDelta);
#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)
