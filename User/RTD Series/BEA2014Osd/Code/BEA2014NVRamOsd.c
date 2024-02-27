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
// ID Code      : BEA2014NVRamOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_NVRAM_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//--------------------------------------------------
// Version Code of NVRam
//--------------------------------------------------
#if 0
#define _CHECKSUM                                   LOBYTE(\
                                                        1 +\
                                                        _SYSTEM_DATA_ADDRESS_END +\
                                                        _OSD_DATA_USER_ADDRESS_END\
                                                    )// 0xF2
#else
#define _CHECKSUM                                   LOBYTE(\
                                                        3 +\
                                                        _PRODUCT_ID_SEL +\
                                                        _PANEL_TYPE\
                                                    )// 0xF2
#endif
#define _VERSION_CODE                               LOBYTE(\
                                                        5 +\
                                                        _SYSTEM_DATA_ADDRESS_END +\
                                                        _OSD_DATA_USER_ADDRESS_END +\
                                                        _PRODUCT_ID_SEL +\
                                                        _PANEL_TYPE\
                                                    )

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#define _CONTRAST_VGA                               0x800
#define _CONTRAST_DVI                               0x800
#define _CONTRAST_VIDEO8                            0x800
#define _CONTRAST_HDMI                              0x800
#define _CONTRAST_DP                                0x800
#else
#define _CONTRAST_VGA                               0x080
#define _CONTRAST_DVI                               0x080
#define _CONTRAST_VIDEO8                            0x080
#define _CONTRAST_HDMI                              0x080
#define _CONTRAST_DP                                0x080
#endif

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
#define _BRIGHTNESS_VGA                             0x1F8
#define _BRIGHTNESS_DVI                             0x200
#define _BRIGHTNESS_VIDEO8                          0x200
#define _BRIGHTNESS_HDMI                            0x200
#define _BRIGHTNESS_DP                              0x200
#else
#define _BRIGHTNESS_VGA                             0x07E
#define _BRIGHTNESS_DVI                             0x080
#define _BRIGHTNESS_VIDEO8                          0x080
#define _BRIGHTNESS_HDMI                            0x080
#define _BRIGHTNESS_DP                              0x080
#endif
//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                            50
#define _SIX_COLOR_SATURATION_R                     100

#define _SIX_COLOR_HUE_Y                            50
#define _SIX_COLOR_SATURATION_Y                     100

#define _SIX_COLOR_HUE_G                            50
#define _SIX_COLOR_SATURATION_G                     100

#define _SIX_COLOR_HUE_C                            50
#define _SIX_COLOR_SATURATION_C                     100

#define _SIX_COLOR_HUE_B                            50
#define _SIX_COLOR_SATURATION_B                     100

#define _SIX_COLOR_HUE_M                            50
#define _SIX_COLOR_SATURATION_M                     100

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PageInfo Address
//--------------------------------------------------
#define _FLASH_FW_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 16)
#define _FLASH_FW_VERSIONCODE_ADDR                  (_FLASH_PAGE_SIZE - 15)
#define _PAGEINFO_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 5)
#define _PAGEINFO_PAGEID_ADDR                       (_FLASH_PAGE_SIZE - 4)
#define _PAGEINFO_MOVECOUNT_ADDR                    (_FLASH_PAGE_SIZE - 3)

// This value is used to indicate the EEPROM emulaiton FW version
#define _EEPROM_EMULATION_VERSION                   0x01
#endif

// Attention: it is necessary for sizeof(StructOsdUserDataType) < ((_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START) * (_DATA_ITEM_LENGTH - 2))
// Please check it when add items in StructOsdUserDataType
code StructOsdUserDataType g_stOSDDefaultData =
{
    _INIT_BACKLIGHT,          // usBackLight -> _BACKLIGHT_CENTER;      
    _INIT_BACKLIGHT,          // usBackLight_CT2 -> _BACKLIGHT_CENTER;      
    _INIT_BACKLIGHT,          // usBackLight_CT3-> _BACKLIGHT_CENTER;      
    _INIT_BACKLIGHT,          // usPCMBackLight;      
    _INIT_BACKLIGHT,          // usPCMBackLight_CT2;      

    (_OSD_H_POS_DEFAULT),     // ucOsdHPos;
    (_OSD_V_POS_DEFAULT),     // ucOsdVPos;
    (_OSD_TIMEOUT_MIN),       // ucOsdTimeout;
    0,                        // ucAspectOriginRatio
    0,                        // ucTransparency;
//--------------------------------------------------------
    _ENGLISH,                 // b4Language;
    _COLOREFFECT_STANDARD,    // b4ColorEffect;
//--------------------------------------------------------
    _DEFAULT_COLORTEMP,       // b4ColorTempType;
    _COLOR_SPACE_RGB,         // b3VGARGBYUV;
    _COLOR_SPACE_RGB,         // b3DVIRGBYUV;
//--------------------------------------------------------
    2,                        // b3Sharpness;
    _DEFAULT_ROTATE_DEGREE,     // b2OsdRotate;
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,     // b2DispRotationSizeType;
    _OFF,                      // b1OverScan;
//--------------------------------------------------------
    _DEFAULT_GAMMA,           // b5Gamma;
    _OSD_ASPECT_RATIO_FULL,   // b3AspectRatio;
//--------------------------------------------------------
    _OD_GAIN_CENTER,          // ucODGain;
    _DEFAULT_HUE,             // cHue;
    _DEFAULT_SATURATION,      // ucSaturation;
    _HL_WIN_OFF,              // ucHLWinType;
//--------------------------------------------------------
    _PCM_OSD_NATIVE,          // b3PCMStatus : 3;
    _ULTRA_VIVID_OFF,         // b2UltraVividStatus : 2;
    _OFF,                     // b1VolumeMute : 1;
    _OFF,                     // b1AudioStandAloneStatus : 1;
    0,                        // b1AudioSourceStatus : 1;
//--------------------------------------------------------
    50,                       // ucVolume;
//--------------------------------------------------------
    _OFF,                      // b1ODStatus : 1;
    0x00,                      // b33DConvergenceMode : 3;
    _AUTO_COLOR_TYPE_EXTERNAL, // b1FactoryAutoColorType : 1;
    _DEFAULT_UNIFORMITY,       // BYTE b1PanelUniformity : 1;
    0,                         // BYTE b1PCMSoftProftMode : 1;
    _ON,                       // b1DDCCIStatus;
//--------------------------------------------------------
    _OSD_INPUT_AUTO,           // BYTE ucOsdInputPort;
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _TYPE_C_U3_OFF,            // BYTE b1D0TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D1TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D2TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D6TypeCU3Mode;
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D0TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D1TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D2TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D6TypeCPinAssignmentESupportSelect;
#endif
#endif
//--------------------------------------------------------
    _DP_VER_1_DOT_2,           // b2OsdDpD0PortVersion : 2;
    _DP_VER_1_DOT_2,           // b2OsdDpD1PortVersion : 2;
    _DP_VER_1_DOT_2,           // b2OsdDpD2PortVersion : 2;
    _DP_VER_1_DOT_2,           // b2OsdDpD6PortVersion : 2;
//--------------------------------------------------------
    0,                         // b1OsdDpVersionHotKeyDisp : 1;
    0,                         // b1PreShowDpHotKeyVersion : 1;
    0,                         // b3PanelUniformityType : 3;
    0,                         // b3OsdDispRotate : 3;
//--------------------------------------------------------
    _OFF,                      // b1FreeSyncStatus : 1;
    _OSD_CLONE_OFF,            // b1CloneMode : 1;
    _LATENCY_L,                // b2LatencyStatus : 2
    _OFF,                      // b1OsdDoubleSize : 1;
    _OFF,                      // b3OsdDpMST : 3;
//--------------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
    _HDR10_MODE_OFF,            // BYTE ucHdrMode;
    _OFF,                       // b1DarkEnhanceStatus : 1;
    _OFF,                       // b1HdrSharpness : 1;
    0,                          // BYTE ucHdrContrast;
    0,                          // BYTE ucHdrColorEnhance;
    0,                          // BYTE ucHdrLightEnhance;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _OFF,                       // BYTE b1HdrLocalDimming : 1;
    50,                         // BYTE ucHdrLocalDimmingAdj;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
    _OFF,                       // b1Sdr2HdrStatus : 1;
#endif

// --------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    _HDMI_1P4,                 // BYTE b2OsdHdmiD0PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD1PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD2PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD3PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD4PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD5PortVersion : 2;
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    _TRUE,                     // BYTE b1OsdUsb3RetimerPDWakeUp: 1;
    _TRUE,                     // BYTE b1OsdUsb3RetimerPSWakeUp: 1;
    _HUB_UFP_TYPE_C_INPUT_PORT, // EnumHubInputPort enumHubInputPortSwitchbyUser;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _OSD_MBR_USER_DISABLE,    // b2MbrStatus;
    _OSD_MBR_DUTY_DEFAULT,    // b7MbrDutys;
    _OSD_MBR_POS_DEFAULT,     // b7MbrPosition;
#endif

// --------------------------------------------------------
#if 1//(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    _GAMMA_18,                  // BYTE b3ColorGamma : 3;
    _GAMMA_20,                  // BYTE b3GrayGamma : 3;
#endif
    _ON,                        // BYTE b12HoursTips : 1;                                                          
    _OFF,                       // BYTE b1FactoryBrunInMode : 1;    
// --------------------------------------------------------

    _ON,                        // b1BacklightSensorMode : 1;
    _OSD_DISTANCE_OFF,          // b2DistanceSensorMode : 2;
    _OFF,                       // b1AmbientlightSensorMode : 1;  
    _OFF,                       // b2ReadingReportMode : 2;
    _OFF,                       // b2FPGATestMapIndex : 2;
// --------------------------------------------------------
    
    _DEEP_POWER_SAVING,         // b2PowerSavingMode : 2;
    _OFF,                       // b1LightBoxModeStatus : 1;                                                          
    _OFF,                       // b3BackgroundLightMode : 3;
    _OFF,                       // b1GravitySensorMode : 1;                                                        
// --------------------------------------------------------
   
    _CT_6500,                   // BYTE b3UserBaseColorTempType : 3;                               
    _ALC_X_RAY,                 // BYTE b3DicomALC : 3;   
    _OFF,                       // b1OsdDcrStatus;
    _OFF,//_ON,                        // b1PanelUseLifeTips : 1;                                                              
    0,                          // b4PCMInputGamma : 4; 
    _ON,                        // b1RS232Status    
// --------------------------------------------------------
#if(_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)    
    _RGB_LIGHT_R,               // b2RGBtMode : 2;  
    _RGB_LIGHT_OFF,             // b3RGBLightMode : 3;    
#endif    

    _OSD_POS_TYPE,				// ucOsdPostion;
    (((_PANEL_DV_HEIGHT / 6) + 1) & 0xFFFE),           // usLocalEnhancementWindowZoom;
};
/*
code StructOsdInputPortType tOsdInputPortDefault =
{
    _OSD_INPUT_AUTO,           // BYTE ucOsdInputPort;
};
*/
code StructBriConDataType tBriConDefaultData[] =
{
    {
        _BRIGHTNESS_VGA,
        _CONTRAST_VGA,
    },

    {
        _BRIGHTNESS_VIDEO8,
        _CONTRAST_VIDEO8,
    },

    {
        _BRIGHTNESS_DVI,
        _CONTRAST_DVI,
    },

    {
        _BRIGHTNESS_HDMI,
        _CONTRAST_HDMI,
    },

    {
        _BRIGHTNESS_DP,
        _CONTRAST_DP,
    },

};

code StructColorProcDataType tColorTempDefaultData[] =
{
    {
        _CT9300_RED,
        _CT9300_GREEN,
        _CT9300_BLUE,
    },

    {
        _CT7500_RED,
        _CT7500_GREEN,
        _CT7500_BLUE,
    },

    {
        _CT6500_RED,
        _CT6500_GREEN,
        _CT6500_BLUE,
    },

    {
        _CT5800_RED,
        _CT5800_GREEN,
        _CT5800_BLUE,
    },

    {
        _CTSRGB_RED,
        _CTSRGB_GREEN,
        _CTSRGB_BLUE,
    },

    {
        _CTUSER_RED,
        _CTUSER_GREEN,
        _CTUSER_BLUE,
    },
};

code StructSixColorDataType g_stSixColorDefaultData =
{
    _SIX_COLOR_HUE_R,
    _SIX_COLOR_SATURATION_R,
    _SIX_COLOR_HUE_Y,
    _SIX_COLOR_SATURATION_Y,
    _SIX_COLOR_HUE_G,
    _SIX_COLOR_SATURATION_G,
    _SIX_COLOR_HUE_C,
    _SIX_COLOR_SATURATION_C,
    _SIX_COLOR_HUE_B,
    _SIX_COLOR_SATURATION_B,
    _SIX_COLOR_HUE_M,
    _SIX_COLOR_SATURATION_M,
};

code StructOsdUserCalibLutDataType g_stOsdUserLutDataDefault =
{
    _LUT_USER_TYPE,
    _LUT_USER_L_MAX,
    _LUT_USER_L_MIN,
    _LUT_USER_LAMB,
	_LUT_USER_VALUE_GAMMA,
	_LUT_USER_COLORTEMP_OFFSET,
};

code StructPanelLuxABDataType g_stPanelABDataDefault[] =
{
    {
		_DEFAULT_MIDDLE_A_DATA,
		_DEFAULT_MIDDLE_B_DATA,
	},	

    {
		_DEFAULT_UP_A_DATA,
		_DEFAULT_UP_B_DATA,
	},

    {
        _DEFAULT_DOWN_A_DATA,
        _DEFAULT_DOWN_B_DATA,
	},
};
code StructPanelAmbABDataType g_stAmbABDataDefault =
{
		_DEFAULT_MIDDLE_A_DATA,
		_DEFAULT_MIDDLE_B_DATA,
};

code StructPanelLuxRangeDataType  g_stPanelLuxRangeDefault[] = 
{
	//Color1
	{
        _DEFAULT_LUX_MAX,
        _DEFAULT_LUX_MIN,
        _DEFAULT_CA310_LUX_MAX,
        _DEFAULT_CA310_LUX_MIN,
	},
	
	//Color2
	{
        _DEFAULT_LUX_MAX_COLOR2,
        _DEFAULT_LUX_MIN_COLOR2,
        _DEFAULT_CA310_LUX_MAX_COLOR2,
        _DEFAULT_CA310_LUX_MIN_COLOR2,
	},
};

code StructTimeType tOsdPanelUserTimeDataDefault =
{
    0,                            // WORD usHour
    0,                            // BYTE ucMin
    0,                            // WORD usSystemRunHour
    0,                            // BYTE ucSystemRunMin
    0,                            // WORD usPanelRunHour
    0,                            // BYTE ucPanelRunMin
    0,                            // BYTE b4SystemRunOverflow : 4
    0,                            // BYTE b4PanelRunOverflow : 4
};

// Attention: it is necessary for sizeof(StructOsdUser2DataType) < ((_FLASH_ITEMID_OSD_DATA2_END - _FLASH_ITEMID_OSD_DATA2_START) * (_DATA_ITEM_LENGTH - 2))
// Please check it when add items in StructOsdUser2DataType
code StructOsdUser2DataType g_stOsdUser2DataDefault =
{
    _BACKLIGHT_MIN,                             // usBackLight_Min;  
    _BACKLIGHT_CENTER,                          // usBackLight_Cen;  
    _BACKLIGHT_MAX,                             // usBackLight_Max;  
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usBacklightSensorValue
	//Restore Sensor
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usBacklightRestoreSensorValue

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
    _INIT_DICOM_BACKLIGHT,                      // usDicomBacklight
    _INIT_DICOM_BACKLIGHT_SENSOR_VALUE,         // usDicomBacklightSensorValue  
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    _INIT_BACKLIGHT_CALIB,                      // usBacklightMCUCalibration
    _INIT_BACKLIGHT_CALIB_SENSOR_VALUE,         // usBacklightMCUCalibrationSensorValue  
#endif

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT)
    _INIT_DICOM_BACKLIGHT_200,                  // usDicomBacklight200
    _INIT_DICOM_BACKLIGHT_250,                  // usDicomBacklight250
    _INIT_DICOM_BACKLIGHT_300,                  // usDicomBacklight300
    _INIT_DICOM_BACKLIGHT_350,                  // usDicomBacklight350
    _INIT_DICOM_BACKLIGHT_400,                  // usDicomBacklight400
    _INIT_DICOM_BACKLIGHT_450,                  // usDicomBacklight450
    _INIT_DICOM_BACKLIGHT_500,                  // usDicomBacklight500
    _INIT_DICOM_BACKLIGHT_550,                  // usDicomBacklight550
    _INIT_DICOM_BACKLIGHT_600,                  // usDicomBacklight600
    _INIT_DICOM_BACKLIGHT_650,                  // usDicomBacklight650
    _INIT_DICOM_BACKLIGHT_700,                  // usDicomBacklight700

    _INIT_DICOM200_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight200SensorValue
    _INIT_DICOM250_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight250SensorValue
    _INIT_DICOM300_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight300SensorValue
    _INIT_DICOM350_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight350SensorValue
    _INIT_DICOM400_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight400SensorValue
    _INIT_DICOM450_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight450SensorValue
    _INIT_DICOM500_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight500SensorValue
    _INIT_DICOM550_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight550SensorValue
    _INIT_DICOM600_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight600SensorValue
    _INIT_DICOM650_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight650SensorValue
    _INIT_DICOM700_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight700SensorValue
#endif

#if 1//(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)
    _INIT_BACKLIGHT_CALIB,                      // usBacklightCalibration
    _INIT_BACKLIGHT_CALIB_SENSOR_VALUE,         // usBacklightCalibrationSensorValue  
#endif

#if 1//(NATIVE:_GAMMA_OFF)
    _INIT_NATIVE_BACKLIGHT,                     // usNativeBacklight
    _INIT_NATIVE_BACKLIGHT_SENSOR_VALUE,        // usNativeBacklightSensorValue  
#endif

    // OCC:PCM
    _BACKLIGHT_CENTER,                          // usPCMBackLight_Cen;  
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usPCMBacklightSensorValue
	//Restore Sensor
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usPCMBacklightRestoreSensorValue

    _BACKLIGHT_MIN,                             // usBackLight_Min_CT2;  
    _BACKLIGHT_CENTER,                          // usBackLight_Cen_CT2;  
    _BACKLIGHT_MAX,                             // usBackLight_Max_CT2;  
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usBacklightSensorValue_CT2
	//Restore Sensor
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usBacklightRestoreSensorValue_CT2

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
    _INIT_DICOM_BACKLIGHT,                      // usDicomBacklight_CT2
    _INIT_DICOM_BACKLIGHT_SENSOR_VALUE,         // usDicomBacklightSensorValue_CT2  
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    _INIT_BACKLIGHT_CALIB,                      // usBacklightMCUCalibration_CT2
    _INIT_BACKLIGHT_CALIB_SENSOR_VALUE,         // usBacklightMCUCalibrationSensorValue_CT2  
#endif

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT)
    _INIT_DICOM_BACKLIGHT_200,                  // usDicomBacklight200_CT2
    _INIT_DICOM_BACKLIGHT_250,                  // usDicomBacklight250_CT2
    _INIT_DICOM_BACKLIGHT_300,                  // usDicomBacklight300_CT2
    _INIT_DICOM_BACKLIGHT_350,                  // usDicomBacklight350_CT2
    _INIT_DICOM_BACKLIGHT_400,                  // usDicomBacklight400_CT2
    _INIT_DICOM_BACKLIGHT_450,                  // usDicomBacklight450_CT2
    _INIT_DICOM_BACKLIGHT_500,                  // usDicomBacklight500_CT2
    _INIT_DICOM_BACKLIGHT_550,                  // usDicomBacklight550_CT2
    _INIT_DICOM_BACKLIGHT_600,                  // usDicomBacklight600_CT2
    _INIT_DICOM_BACKLIGHT_650,                  // usDicomBacklight650_CT2
    _INIT_DICOM_BACKLIGHT_700,                  // usDicomBacklight700_CT2

    _INIT_DICOM200_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight200SensorValue_CT2
    _INIT_DICOM250_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight250SensorValue_CT2
    _INIT_DICOM300_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight300SensorValue_CT2
    _INIT_DICOM350_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight350SensorValue_CT2
    _INIT_DICOM400_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight400SensorValue_CT2
    _INIT_DICOM450_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight450SensorValue_CT2
    _INIT_DICOM500_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight500SensorValue_CT2
    _INIT_DICOM550_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight550SensorValue_CT2
    _INIT_DICOM600_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight600SensorValue_CT2
    _INIT_DICOM650_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight650SensorValue_CT2
    _INIT_DICOM700_BACKLIGHT_SENSOR_VALUE,      // usDicomBacklight700SensorValue_CT2
#endif

    // OCC:PCM CT2
    _BACKLIGHT_CENTER,                          // usPCMBackLight_Cen_CT2;  
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usPCMBacklightSensorValue_CT2
	//Restore Sensor
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usPCMBacklightRestoreSensorValue_CT2

    _BACKLIGHT_MIN,                             // usBackLight_Min_CT3;  
    _BACKLIGHT_CENTER,                          // usBackLight_Cen_CT3;  
    _BACKLIGHT_MAX,                             // usBackLight_Max_CT3;  
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usBacklightSensorValue_CT3
	//Restore Sensor
    _INIT_BACKLIGHT_SENSOR_VALUE,               // usBacklightRestoreSensorValue_CT3

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
    _INIT_DICOM_BACKLIGHT,                      // usDicomBacklight_CT3
    _INIT_DICOM_BACKLIGHT_SENSOR_VALUE,         // usDicomBacklightSensorValue_CT3  
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    _INIT_BACKLIGHT_CALIB,                      // usBacklightMCUCalibration_CT3
    _INIT_BACKLIGHT_CALIB_SENSOR_VALUE,         // usBacklightMCUCalibrationSensorValue_CT3  
#endif

};

code Lut_Attri tFacDefaultLut_Attri[_GAMMA_AMOUNT + 1] =
{
    // Follow Consistent UI Gamma Index

	// _GAMMA_OFF
	{
    	// curve
        CURVE_NATIVE,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)

	// _GAMMA_18
	//  2.2
	{
    	// curve
        CURVE_GAMMA,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10)& 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_20
	// DICOM
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_22
    // MCU Calibration 
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_24
    // PC Calibration 
	{
    	// curve
        CURVE_USE_DEFINE_GUID,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_26  
    // Hybrid not use 

	// _GAMMA_DICOM_ALC1  
    // Dicom+0.3  
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)30 & 0x00FF)),
        (BYTE)(((WORD)30 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC2  
    // Dicom+0.5
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)50 & 0x00FF)),
        (BYTE)(((WORD)50 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC3  
    // Dicom+0.75
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)75 & 0x00FF)),
        (BYTE)(((WORD)75 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC4  
    // Dicom+1.0
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)100 & 0x00FF)),
        (BYTE)(((WORD)100 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},    
    
	// _GAMMA_DICOM_ALC5  
    // Dicom+1.3
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)130 & 0x00FF)),
        (BYTE)(((WORD)130 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    
	// _GAMMA_CALIB
    // not use 
	{
    	// curve
        CURVE_USE_DEFINE_GUID,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)

	// _GAMMA_18
	//  2.0
	{
    	// curve
        CURVE_GAMMA,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)200 & 0x00FF)),
        (BYTE)(((WORD)200 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10)& 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_20
	//  2.2
	{
    	// curve
        CURVE_GAMMA,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10)& 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_22
    // 2.4
	{
    	// curve
        CURVE_GAMMA,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)240 & 0x00FF)),
        (BYTE)(((WORD)240 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10)& 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_24
    // 2.6
	{
    	// curve
        CURVE_GAMMA,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)260 & 0x00FF)),
        (BYTE)(((WORD)260 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10)& 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_26  
    // DICOM 
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC1  
    // Dicom+0.3  
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)30 & 0x00FF)),
        (BYTE)(((WORD)30 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC2  
    // Dicom+0.5
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)50 & 0x00FF)),
        (BYTE)(((WORD)50 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC3  
    // Dicom+0.75
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)75 & 0x00FF)),
        (BYTE)(((WORD)75 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC4  
    // Dicom+1.0
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)100 & 0x00FF)),
        (BYTE)(((WORD)100 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},    
    
	// _GAMMA_DICOM_ALC5  
    // Dicom+1.3
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)130 & 0x00FF)),
        (BYTE)(((WORD)130 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    
	// _GAMMA_CALIB
    // CAL 
	{
    	// curve
        CURVE_DICOM ,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
	// _GAMMA_18
	//  2.2
	{
    	// curve
        CURVE_GAMMA,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10)& 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},

#if 1// (_ENABLE_MULTIPLE_DICOM_SUPPORT == _ON)        
    // _GAMMA_DICOM200
	// Dicom200
	{
    	// curve
        CURVE_ONLY_BRIGTE,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_200_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_200_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    // _GAMMA_DICOM250
	// Dicom250
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_250_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_250_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    // _GAMMA_DICOM300
	// Dicom300
	{
    	// curve
        CURVE_ONLY_BRIGTE,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_300_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_300_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
	
    // _GAMMA_DICOM350
	// Dicom350
	{
    	// curve
        CURVE_ONLY_BRIGTE,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_350_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_350_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    // _GAMMA_DICOM400
	// Dicom400
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_400_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_400_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    // _GAMMA_DICOM450
	// Dicom450
	{
    	// curve
        CURVE_ONLY_BRIGTE,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_450_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_450_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

    // _GAMMA_DICOM500
	// Dicom500
	{
    	// curve
        CURVE_ONLY_BRIGTE,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_500_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_500_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    // _GAMMA_DICOM550
	// Dicom550
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_550_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_550_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    // _GAMMA_DICOM600
	// Dicom600
	{
    	// curve
        CURVE_ONLY_BRIGTE,
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)0 & 0x00FF)),
        (BYTE)(((WORD)0 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_DICOM_600_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_DICOM_600_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC1  
    // Dicom+0.3  
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)30 & 0x00FF)),
        (BYTE)(((WORD)30 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC2  
    // Dicom+0.5
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)50 & 0x00FF)),
        (BYTE)(((WORD)50 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC3  
    // Dicom+0.75
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)75 & 0x00FF)),
        (BYTE)(((WORD)75 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},

	// _GAMMA_DICOM_ALC4  
    // Dicom+1.0
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)100 & 0x00FF)),
        (BYTE)(((WORD)100 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},    
    
	// _GAMMA_DICOM_ALC5  
    // Dicom+1.3
	{
    	// curve
        CURVE_DICOM,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)130 & 0x00FF)),
        (BYTE)(((WORD)130 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_DICOM_CONTRAST_RATIO & 0xFF00)>> 8),
	},
    
	// _GAMMA_CALIB
    // PC Calibration 
	{
    	// curve
        CURVE_DICOM ,
        
        // backlight
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0x00FF)),
        (BYTE)(((WORD)_BACKLIGHT_CENTER & 0xFF00)>> 8),

        // value
        (BYTE)(((WORD)220 & 0x00FF)),
        (BYTE)(((WORD)220 & 0xFF00)>> 8),

        // maxLuminance L -> H
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0x00FF)),
        (BYTE)(((WORD)(_DEFAULT_GAMMA_LUX*10) & 0xFF00)>> 8),

        // contrast L -> H
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0x00FF)),
        (BYTE)(((WORD)_GAMMA_CONTRAST_RATIO & 0xFF00)>> 8),
	},
        
#endif

#else
#warning "!!!Please Check Gamma define"

#endif
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructOsdUserDataType g_stOSDUserData;
//StructOsdInputPortType g_stOsdInputPortData;

StructBriConDataType g_stBriConData;
StructColorProcDataType g_stColorProcData;
StructSixColorDataType g_stSixColorData;

StructOsdUserCalibLutDataType g_stUserCalibLutData;
StructPanelLuxABDataType g_stPanelLuxABData[3];
StructPanelAmbABDataType g_stPanelAmbABData;
StructPanelLuxRangeDataType g_stPanelLuxRangeData[2];
StructTimeType g_stPanelTimeData;
StructOsdUser2DataType g_stOsdUser2Data;
Lut_Attri g_pstFacLut_Attri;


#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
DWORD g_ulFlashMoveCount;
BYTE g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
void RTDEepromStartup(void);
void RTDEepromWholeRestore(void);
void RTDEepromRestoreBacklight(void);
void RTDEepromLoadOSDData(void);
void RTDEepromSaveOSDData(void);
void RTDEepromRestoreOSDData(void);
void RTDEepromLoadBriCon(BYTE ucSource);
void RTDEepromSaveBriCon(BYTE ucSource);
void RTDEepromRestoreBriCon(void);
void RTDEepromLoadColorSetting(BYTE ucColorTempType);
void RTDEepromSaveColorSetting(BYTE ucColorTempType);
void RTDEepromRestoreColorSetting(void);
void RTDEepromRestoreUserColorSetting(void);
void RTDEepromLoadSixColorData(void);
void RTDEepromSaveSixColorData(void);
void RTDEepromRestoreSixColorData(void);
void RTDEepromLoadUserCalibLutData(void);
void RTDEepromRestoreUserCalibLutData(void);
void RTDEepromLoadPanelUsedTimeData(void);
void RTDEepromSavePanelUsedTimeData(void);
void RTDEepromRestorePanelUsedTimeData(void);

void RTDEepromLoadOsdUser2Data(void);
void RTDEepromSaveOsdUser2Data(void);
void RTDEepromRestoreOsdUser2Data(void);

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

BYTE RTDFlashGetFreePage(void);
bit RTDFlashIsPageInfoValid(BYTE ucPage);
void RTDFlashInitialDataPage(BYTE ucPageID);
WORD RTDFlashSearchPageAddr(BYTE ucPageID);
void RTDFlashInitialAddr(void);
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode);
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode);
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);

void RTDFlashStartup(void);
void RTDFlashWholeRestore(void);
void RTDFlashRestoreBacklight(void);
void RTDFlashLoadOSDData(void);
void RTDFlashSaveOSDData(void);
void RTDFlashRestoreOSDData(void);
void RTDFlashLoadBriCon(BYTE ucSource);
void RTDFlashSaveBriCon(BYTE ucSource);
void RTDFlashRestoreBriCon(void);
void RTDFlashLoadColorSetting(BYTE ucColorTempType);
void RTDFlashSaveColorSetting(BYTE ucColorTempType);
void RTDFlashRestoreColorSetting(void);
void RTDFlashRestoreUserColorSetting(void);
void RTDFlashLoadSixColorData(void);
void RTDFlashSaveSixColorData(void);
void RTDFlashRestoreSixColorData(void);
void RTDFlashLoadPanelUsedTimeData(void);
void RTDFlashSavePanelUsedTimeData(void);
void RTDFlashRestorePanelUsedTimeData(void);

#if(_PANEL_EXIST_MULTIPANEL == _ON)
void RTDFlashLoadPanelIndex(void);
void RTDFlashSavePanelIndex(void);
void RTDFlashRestorePanelIndex(void);
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

#if 1//(_BEACON_MONITOR_SN_SET_FUNCTION == _ON)
bit RTDNVRamLoadMonitorSNData(BYTE *pucData);
bit RTDNVRamSaveMonitorSNData(BYTE ucLength, BYTE *pucData);
bit RTDNVRamLoadMonitorIDSNData(BYTE *pucData);
bit RTDNVRamSaveMonitorIDSNData(BYTE ucLength, BYTE *pucData);
#endif // End of #if (_BEACON_MONITOR_SN_SET_FUNCTION == _ON)

void RTDNVRamLoadPanelLuxABData(void);
void RTDNVRamSavePanelLuxABData(void);
void RTDNVRamRestorePanelLuxABData(void);

void RTDNVRamLoadPanelAmbABData(void);
void RTDNVRamSavePanelAmbABData(void);
void RTDNVRamRestorePanelAmbABData(void);

void RTDNVRamLoadPanelLuxRangeData(void);
void RTDNVRamSavePanelLuxRangeData(void);
void RTDNVRamRestorePanelLuxRangeData(void);
void RTDNVRamCheckPanelLuxUserLutData(void);

void RTDNVRamRestoreLutAttriData(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromStartup(void)
{
    BYTE ucCnt = 0;

    // Check twice if VERSION CODE matches
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        pData[0] = _CHECKSUM ^ 0xFF;
        pData[1] = _VERSION_CODE ^ 0xFF;
        UserCommonEepromRead(_EEPROM_CHECKSUM_ADDRESS, 2, pData);

        if((pData[0] == _CHECKSUM) && (pData[1] == _VERSION_CODE))
        {
            break;
        }
    }

    if(pData[0] != _CHECKSUM)
    {
        // Load default value and save to EEPROM
        RTDEepromWholeRestore();
        // Save VERSION CODE to EEPROM
        pData[0] = _CHECKSUM;
        pData[1] = _VERSION_CODE;
        pData[2] = 0; // _PANEL_INDEX_ADDRESS

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        SET_MDOMAIN_PANEL_INDEX(0);
#endif

        UserCommonEepromWrite(_EEPROM_CHECKSUM_ADDRESS, 2, pData);
        UserCommonEepromWrite(_PANEL_INDEX_ADDRESS, 1, &pData[2]);
    }
    else if(pData[1] != _VERSION_CODE)
    {
        UserCommonEepromRestoreSystemData();
        RTDEepromRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonEepromRestoreModeUserData();
        UserCommonEepromRestoreADCSetting();
#endif

#if 1
        RTDEepromRestoreColorSetting();
        RTDEepromRestoreUserColorSetting();
#else
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDEepromSaveColorSetting(_CT_USER);
#endif

        RTDEepromRestoreBriCon();
        RTDEepromRestoreSixColorData();

        // osd display mode
        //RTDEepromRestoreOsdInputPortData();
        
        RTDEepromLoadUserCalibLutData();
        RTDEepromLoadPanelUsedTimeData();
        RTDEepromLoadOsdUser2Data();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
    }
    else
    {
        UserCommonEepromLoadSystemData();
        RTDEepromLoadOSDData();
        //RTDEepromLoadOsdInputPortData();
        RTDEepromLoadSixColorData();
        RTDEepromLoadUserCalibLutData();        
        RTDEepromLoadPanelUsedTimeData();
        RTDEepromLoadOsdUser2Data();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS() > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            RTDEepromSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDEepromSaveOSDData();
        }
#endif
    }

    // SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    /*
    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    */

    RTDEepromLoadColorSetting(GET_COLOR_TEMP_TYPE());
    RTDNVRamCheckPanelLuxUserLutData();
    RTDNVRamRestoreLutAttriData();

}

//--------------------------------------------------
// Description  : Load default data and save to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromWholeRestore(void)
{
    UserCommonEepromRestoreSystemData();
    RTDEepromRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonEepromRestoreModeUserData();
    UserCommonEepromRestoreADCSetting();
#endif

    RTDEepromRestoreBriCon();
    RTDEepromRestoreColorSetting();
    RTDEepromRestoreUserColorSetting();

    RTDEepromRestoreSixColorData();

    // osd display mode
    //RTDEepromRestoreOsdInputPortData();
    // Lut User Data
    RTDEepromRestoreUserCalibLutData();
    // osd panel user time 
    RTDEepromRestorePanelUsedTimeData();
    // Osd user2 data
    RTDEepromRestoreOsdUser2Data();
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBacklight(void)
{
	BYTE ucColorTemp,ucPCMStatus;
	ucColorTemp = GET_COLOR_TEMP_TYPE();
	ucPCMStatus = GET_OSD_PCM_STATUS();

    // OCC
	SET_OSD_PCM_STATUS(_PCM_OSD_SRGB);
	SET_COLOR_TEMP_TYPE(_CT_9300);
    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usPCMBackLight_CT2);

	SET_COLOR_TEMP_TYPE(_CT_6500);
    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usPCMBackLight);

    // OGC
	SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
	if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
    {
		SET_COLOR_TEMP_TYPE(_CT_7500);
        SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight_CT3);
    }
	SET_COLOR_TEMP_TYPE(_CT_9300);
    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight_CT2);
    
	SET_COLOR_TEMP_TYPE(_CT_6500);
    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight);
    
	SET_COLOR_TEMP_TYPE(ucColorTemp);
	SET_OSD_PCM_STATUS(ucPCMStatus);

    RTDEepromSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOSDData(void)
{
    UserCommonEepromRead(_OSD_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOSDUserData));

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) &&
       (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Save OSD data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOSDData(void)
{
    UserCommonEepromWrite(_OSD_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOSDUserData));
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOSDData(void)
{
	BYTE tempOsdInputPort;
    tempOsdInputPort = g_stOSDUserData.ucOsdInputPort;

    g_stOSDUserData = g_stOSDDefaultData;
	if(GET_FORCE_BACKUP_STATUS() == _TRUE)
    {   
    g_stOSDUserData.ucOsdInputPort = tempOsdInputPort;
       }
    DebugMessageUart("tempOsdInputPort", tempOsdInputPort);
    RTDEepromSaveOSDData();
}
/*
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromLoadOsdInputPortData(void)
{
    UserCommonEepromRead(_OSD_INPUT_MODE_ADDRESS, sizeof(StructOsdInputPortType), (BYTE *)(&g_stOsdInputPortData));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromSaveOsdInputPortData(void)
{
    UserCommonEepromWrite(_OSD_INPUT_MODE_ADDRESS, sizeof(StructOsdInputPortType), (BYTE *)(&g_stOsdInputPortData));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDEepromRestoreOsdInputPortData(void)
{
        g_stOsdInputPortData = tOsdInputPortDefault;
        RTDEepromSaveOsdInputPortData();
}
*/
//--------------------------------------------------
// Description  : Load brightness/contrast from EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadBriCon(BYTE ucSource)
{
    UserCommonEepromRead(_BRICON_DATA_ADDRESS + ucSource * sizeof(StructBriConDataType), sizeof(StructBriConDataType), (BYTE *)(&g_stBriConData));
}

//--------------------------------------------------
// Description  : Save brightness/contrast to EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveBriCon(BYTE ucSource)
{
    UserCommonEepromWrite(_BRICON_DATA_ADDRESS + ucSource * sizeof(StructBriConDataType), sizeof(StructBriConDataType), (BYTE *)(&g_stBriConData));
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBriCon(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _SOURCE_AMOUNT; ucTemp++)
    {
        g_stBriConData = tBriConDefaultData[ucTemp];
        RTDEepromSaveBriCon(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Load color settings from EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadColorSetting(BYTE ucColorTempType)
{
#if(_OGC_SUPPORT == _ON)
    if((GET_OSD_GAMMA() != _GAMMA_OFF)&&(UserCommonNVRamGetSystemData(_OGCOCC_SEL_BEACON) == _OFF))
    {
        UserCommonAdjustOGCColorTempGain(ucColorTempType, (GET_OSD_GAMMA() - 1), pData, _OGC_NORMAL_TYPE);

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
        g_stColorProcData.usColorTempR = pData[0];
        g_stColorProcData.usColorTempG = pData[1];
        g_stColorProcData.usColorTempB = pData[2];
#endif
    }
    else
#endif
    {
        UserCommonEepromRead(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }

    /*
    else
    {
        g_stColorProcData.usColorTempR = 0x800;
        g_stColorProcData.usColorTempG = 0x800;
        g_stColorProcData.usColorTempB = 0x800;
    }
    */
}

//--------------------------------------------------
// Description  : Save color settings to EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveColorSetting(BYTE ucColorTempType)
{
    // if(ucColorTempType != _CT_OFF)
    {
        UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreColorSetting(void)
{
    BYTE ucTemp = 0;
    for(ucTemp = _CT_9300; ucTemp < _CT_USER; ucTemp++)
    {
        g_stColorProcData = tColorTempDefaultData[ucTemp];
        RTDEepromSaveColorSetting(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp;
    BYTE ucIndex = 0;

    for(ucIndex = _CT_9300; ucIndex <= _CT_USER; ++ucIndex)
    {
        stUserColorTemp = tColorTempDefaultData[ucIndex];
        UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucIndex) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&stUserColorTemp));
    }
}


//--------------------------------------------------
// Description  : Load six color data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadSixColorData(void)
{
    UserCommonEepromRead(_SIXCOLOR_DATA_ADDRESS, sizeof(StructSixColorDataType), (BYTE *)(&g_stSixColorData));
}

//--------------------------------------------------
// Description  : Save six color data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveSixColorData(void)
{
    UserCommonEepromWrite(_SIXCOLOR_DATA_ADDRESS, sizeof(StructSixColorDataType), (BYTE *)(&g_stSixColorData));
}

//--------------------------------------------------
// Description  : Restore default six color data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreSixColorData(void)
{
    g_stSixColorData = g_stSixColorDefaultData;
    RTDEepromSaveSixColorData();
}

//--------------------------------------------------
// Description  : Load User Calibration Lut data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadUserCalibLutData(void)
{
    UserCommonEepromRead(_USER_CALIB_LUT_DATA_ADDRESS, sizeof(StructOsdUserCalibLutDataType), (BYTE *)(&g_stUserCalibLutData));
}

//--------------------------------------------------
// Description  : Save User Calibration Lut data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveUserCalibLutData(void)
{
    UserCommonEepromWrite(_USER_CALIB_LUT_DATA_ADDRESS, sizeof(StructOsdUserCalibLutDataType), (BYTE *)(&g_stUserCalibLutData));
}
//--------------------------------------------------
// Description  : Restore default User Calibration Lut data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreUserCalibLutData(void)
{
    g_stUserCalibLutData = g_stOsdUserLutDataDefault;
    RTDEepromSaveUserCalibLutData();
}

//--------------------------------------------------
// Description  : Load Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadPanelUsedTimeData(void)
{
    UserCommonEepromRead(_PANEL_TIME_DATA_ADDRESS, sizeof(StructTimeType), (BYTE *)(&g_stPanelTimeData));
}

//--------------------------------------------------
// Description  : Save Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSavePanelUsedTimeData(void)
{
    UserCommonEepromWrite(_PANEL_TIME_DATA_ADDRESS, sizeof(StructTimeType), (BYTE *)(&g_stPanelTimeData));
}

//--------------------------------------------------
// Description  : Restore Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestorePanelUsedTimeData(void)
{
    WORD tempusSystemRunHour;
    BYTE tempucSystemRunMin;

    WORD tempusPanelRunHour;
    BYTE tempucPanelRunMin;

    BYTE tempb4SystemRunOverflow;
    BYTE tempb4PanelRunOverflow;

	tempusSystemRunHour = g_stPanelTimeData.usSystemRunHour;
	tempucSystemRunMin = g_stPanelTimeData.ucSystemRunMin;

	tempusPanelRunHour = g_stPanelTimeData.usPanelRunHour;
	tempucPanelRunMin = g_stPanelTimeData.ucPanelRunMin;

	tempb4SystemRunOverflow = g_stPanelTimeData.b4SystemRunOverflow;
	tempb4PanelRunOverflow = g_stPanelTimeData.b4PanelRunOverflow;
	
    g_stPanelTimeData = tOsdPanelUserTimeDataDefault;

	if(GET_FORCE_BACKUP_STATUS() == _TRUE)
	{
		 g_stPanelTimeData.usSystemRunHour = tempusSystemRunHour;
		 g_stPanelTimeData.ucSystemRunMin = tempucSystemRunMin;
		
		 g_stPanelTimeData.usPanelRunHour = tempusPanelRunHour;
		 g_stPanelTimeData.ucPanelRunMin = tempucPanelRunMin;

		 g_stPanelTimeData.b4SystemRunOverflow = tempb4SystemRunOverflow;
		 g_stPanelTimeData.b4PanelRunOverflow = tempb4PanelRunOverflow;
	}
	
    RTDEepromSavePanelUsedTimeData();
}

//--------------------------------------------------
// Description  : Load OSD data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdUser2Data(void)
{
    UserCommonEepromRead(_OSD_USER2_DATA_ADDRESS, sizeof(StructOsdUser2DataType), (BYTE *)(&g_stOsdUser2Data));
}

//--------------------------------------------------
// Description  : Save OSD data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdUser2Data(void)
{
    UserCommonEepromWrite(_OSD_USER2_DATA_ADDRESS, sizeof(StructOsdUser2DataType), (BYTE *)(&g_stOsdUser2Data));
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdUser2Data(void)
{
    g_stOsdUser2Data = g_stOsdUser2DataDefault;
    RTDEepromSaveOsdUser2Data();
}

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get the free page number of flash
// Input Value  : None
// Output Value : Free page index
//--------------------------------------------------
BYTE RTDFlashGetFreePage(void)
{
    BYTE ucPageID = _START_OF_PAGEID;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    // If the _END_PAGE page has the biggest move count, suppose first page is free page
    if(g_ulFlashMoveCount > 0)
    {
        if(g_ucFlashLastPage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
        {
            ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
        }
        else
        {
            ucFreePage = g_ucFlashLastPage + 1;
        }
    }

    // Check the supposed free page is actual free page which has not been used ever
    do
    {
        if(ucFreePage == g_pucFlashPageArr[ucPageID])
        {
            if(ucFreePage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
            {
                ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
            }
            else
            {
                ucFreePage += 1;
            }

            ucPageID = _START_OF_PAGEID;
        }
        else
        {
            ucPageID++;
        }
    }
    while(ucPageID <= _END_OF_PAGEID);

    return ucFreePage;
}

//--------------------------------------------------
// Description  : Check the page is vaild or not
// Input Value  : ucPage: The page to be check, must between 0 and (_END_PAGE - _START_PAGE)
// Output Value : _TRUE means the page is valid, _FLASE is invalid
//--------------------------------------------------
bit RTDFlashIsPageInfoValid(BYTE ucPage)
{
    WORD usPageInfoAddr = ucPage * _FLASH_PAGE_SIZE;
    BYTE ucPageInfoChecksum = 0;
    BYTE pucPageInfo[5] = {0};
    BYTE pucPageInfoTemp[4] = {0};

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageInfoAddr + _PAGEINFO_CHECKSUM_ADDR, 5, pucPageInfo);
    pucPageInfoTemp[0] = pucPageInfo[1];
    pucPageInfoTemp[1] = pucPageInfo[2];
    pucPageInfoTemp[2] = pucPageInfo[3];
    pucPageInfoTemp[3] = pucPageInfo[4];
    ucPageInfoChecksum = UserCommonFlashCalculateCheckSumData(pucPageInfoTemp, 4);
    ucPageInfoChecksum = (ucPageInfoChecksum & 0x7F);

    if(ucPageInfoChecksum == pucPageInfo[0])
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial data page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialDataPage(BYTE ucPageID)
{
    WORD usAddr = _SYSTEM_EEPROM_EMULATION_START_PAGE * _FLASH_PAGE_SIZE;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucVersionCode = 0;
    BYTE ucChecksum = 0;

    ucFreePage = RTDFlashGetFreePage();
    // Initial page index
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Initial address
    g_pusFlashAddrArr[ucPageID] = 0;
    // Initial move count
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID]);

    pData[0] = ucPageID;
    pData[1] = (BYTE)(g_ulFlashMoveCount >> 16);
    pData[2] = (BYTE)(g_ulFlashMoveCount >> 8);
    pData[3] = (BYTE)g_ulFlashMoveCount;
    pData[4] = UserCommonFlashCalculateCheckSumData(pData, 4);
    pData[4] = (pData[4] & 0x7F);

    ucVersionCode = _VERSION_CODE;
    ucChecksum = _CHECKSUM;

    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_PAGEID_ADDR, 4, pData);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_CHECKSUM_ADDR, 1, &pData[4]);
}

//--------------------------------------------------
// Description  : Search the last saved item address, and next new item position
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD RTDFlashSearchPageAddr(BYTE ucPageID)
{
    WORD usItemAddr = 0;
    WORD usPageAddr = 0;

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the last data item address
    for(usItemAddr = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usItemAddr > 0; usItemAddr--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + (usItemAddr - 1) * _DATA_ITEM_LENGTH, 1, pData);
        if(pData[0] != 0xFF)
        {
            return usItemAddr;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : Flash address initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialAddr(void)
{
    BYTE ucCnt = 0;
    WORD usAddr = 0;
    DWORD ulMoveCount = 0;
    BYTE ucPageID = 0;
    DWORD ulMoveCountTemp = 0;

    g_ulFlashMoveCount = 0;
    g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        g_pucFlashPageArr[ucPageID] = 0xFF;
    }

    // Find the page whose move count is the biggest and get the max move count
    for(ucCnt = _SYSTEM_EEPROM_EMULATION_START_PAGE; ucCnt < (_SYSTEM_EEPROM_EMULATION_END_PAGE + 1); ucCnt++)
    {
        // Check the page is valid or not
        if(RTDFlashIsPageInfoValid(ucCnt) == _TRUE)
        {
            usAddr = ucCnt * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR;

            // Get the move count of current page
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 4, pData);
            ulMoveCount = ((DWORD)(pData[1]) << 16) | ((DWORD)(pData[2]) << 8) | ((DWORD)(pData[3]));

            // Get the max move count and its page index, ulMoveCount Only 3 Bytes, extra Judge 0xFFFFFF < 0x000001 Case
            if(((ulMoveCount >= g_ulFlashMoveCount) && (!((ulMoveCount == 0xFFFFFF) && (g_ulFlashMoveCount == 0x01)))) ||\
               ((ulMoveCount < g_ulFlashMoveCount) && ((ulMoveCount == 0x01) && (g_ulFlashMoveCount == 0xFFFFFF))))
            {
                g_pucFlashPageArr[pData[0]] = ucCnt;
                g_ulFlashMoveCount = ulMoveCount;
                g_ucFlashLastPage = ucCnt;
            }
            // Check Other vaild page index
            else
            {
                if(g_pucFlashPageArr[pData[0]] == 0xFF)
                {
                    g_pucFlashPageArr[pData[0]] = ucCnt;
                }
                else // Check which page have begger Movecount
                {
                    usAddr = g_pucFlashPageArr[pData[0]] * _FLASH_PAGE_SIZE + _PAGEINFO_MOVECOUNT_ADDR;
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 3, &pData[1]);
                    ulMoveCountTemp = (((DWORD)(pData[1]) << 16) | ((DWORD)(pData[2]) << 8) | ((DWORD)(pData[3])));
                    if(((ulMoveCount >= ulMoveCountTemp) && (!((ulMoveCount == 0xFFFFFF) && (ulMoveCountTemp == 0x01)))) ||\
                       ((ulMoveCount < ulMoveCountTemp) && ((ulMoveCount == 0x01) && (ulMoveCountTemp == 0xFFFFFF))))
                    {
                        g_pucFlashPageArr[pData[0]] = ucCnt;
                    }
                }
            }
        }
    }

    // If this page is missing, intial this single page
    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        if(g_pucFlashPageArr[ucPageID] == 0xFF)
        {
            // This function will increase g_ulFlashMovePage,and now g_ucFlashLastPage is the page index which has the biggest move count value
            RTDFlashInitialDataPage(ucPageID);
            RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
        }
        else
        {
            // Initial g_pusFlashAddrArr
            g_pusFlashAddrArr[ucPageID] = RTDFlashSearchPageAddr(ucPageID);
        }
    }
}

//--------------------------------------------------
// Description  : Get the checksum and version code from flash
// Input Value  : pucChecksum: the checksum get from flash
//                pucVersionCode: the version code get from flash
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode)
{
    // Get the checksum and version code
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, pucChecksum);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, pucVersionCode);
}

//--------------------------------------------------
// Description  : Save the checksum & version code to flash
// Input Value  : ucChecksum, checksum value
//                ucVersionCode, version code value
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode)
{
    BYTE ucVersionCodeRead = 0;
    BYTE ucChecksumRead = 0;

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCodeRead);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksumRead);

    // Do not need save checksum or version code
    if((ucVersionCode == ucVersionCodeRead) && (ucChecksum == ucChecksumRead))
    {
        return;
    }
    // Need to save version code and checksum in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save version code in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum == ucChecksumRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    }
    // Need to save checksum in current page
    else if((ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF) && (ucVersionCode == ucVersionCodeRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save checksum and version code to free page
    else
    {
        memset(pData, 0xFF, _DATA_ITEM_LENGTH);
        RTDFlashMoveData(_CHECKSUM_VERSIONCODE_ID, pData);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
}

//--------------------------------------------------
// Description  : Move data to another page of flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData)
{
    BYTE ucPrevPage = g_pucFlashPageArr[ucPageID];
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucItemIndex = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usPrevPageAddr = 0;
    WORD usMovedItemCount = 0;
    WORD usMovedAddrIndex = 0;
    BYTE ucItemID = 0;
    BYTE ucChecksum = 0xFF;
    BYTE ucVersioncode = 0xFF;

    // Load checksum and version code
    if(pucData[0] != 0xFF)
    {
        RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersioncode);
    }

    // Get free page data will move to
    ucFreePage = RTDFlashGetFreePage();

    // First sector erase the free page specified by g_ucFlashFreePage
    if(UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage) == _FALSE)
    {
        return _FALSE;
    }

    // Save the latest data item to the new page if need, when save checksum and version, it is not necessary
    // We do not save the item id at last because page info has not been saved
    if(pucData[0] != 0xFF)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage * _FLASH_PAGE_SIZE + ucItemIndex, _DATA_ITEM_LENGTH, pucData);

        // Clear Buffer
        memset(pucData, 0xFF, _DATA_ITEM_LENGTH);

        // And then load the latest data items which saved in the old full page to the new page from bottom to top
        usMovedItemCount = 1;
    }
    else
    {
        usMovedItemCount = 0;
    }

    // Update ucFlashPage
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Update move count value
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usPrevPageAddr = ucPrevPage * _FLASH_PAGE_SIZE;
    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the valid item and move to new free page
    for(usAddrIndex = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex > 0; usAddrIndex--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, 1, &ucItemID);

        if(ucItemID != 0xFF)
        {
            // Check the item has been moved or not by item ID
            for(usMovedAddrIndex = 0; usMovedAddrIndex < usMovedItemCount; usMovedAddrIndex++)
            {
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedAddrIndex * _DATA_ITEM_LENGTH, 1, pData);
                if(pData[0] == ucItemID)
                {
                    break;
                }
            }

            if(usMovedAddrIndex >= usMovedItemCount)
            {
                // The item has not been moved, then check the item is valid or not
                pucData[15] = 0;
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH - 1, pData);
                pucData[15] = UserCommonFlashCalculateCheckSumData(pData, (_DATA_ITEM_LENGTH - 1));
                pucData[15] = (pucData[15] & 0x7F);

                // Check the checksum
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + usAddrIndex * _DATA_ITEM_LENGTH - 1, 1, pData);
                if(pucData[15] != pData[0])
                {
                    // Checksum check fail, the item is invalid
                    continue;
                }

                // Move the item to new free page
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);
                UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedItemCount * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);

                usMovedItemCount++;
            }
        }
    }

    // Update the data item address in the new page
    g_pusFlashAddrArr[ucPageID] = usMovedItemCount;

    // Last update the new moved page info fields
    // Save checksum & version code
    if(ucPageID == _CHECKSUM_VERSIONCODE_ID)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersioncode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }

    // Save page info
    pData[0] = ucPageID;
    pData[1] = (BYTE)(g_ulFlashMoveCount >> 16);
    pData[2] = (BYTE)(g_ulFlashMoveCount >> 8);
    pData[3] = (BYTE)g_ulFlashMoveCount;
    pData[4] = UserCommonFlashCalculateCheckSumData(pData, 4);
    pData[4] = (pData[4] & 0x7F);

    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR, 4, pData);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_CHECKSUM_ADDR, 1, &pData[4]);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Flash check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashStartup(void)
{
    BYTE ucChecksum = 0;
    BYTE ucVersionCode = 0;
    BYTE ucPageID = 0;

    RTDFlashInitialAddr();

    // Get FW checksum and version code
    RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersionCode);

    if(ucChecksum != _CHECKSUM)
    {
        // Checksum is changed, load default value and save to flash
        for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
        {
            RTDFlashInitialDataPage(ucPageID);
        }

        RTDFlashWholeRestore();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashRestorePanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else if(ucVersionCode != _VERSION_CODE)
    {
        // Restore CT User color setting
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + _CT_USER, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(_CT_USER);
        }

        UserCommonFlashRestoreSystemData();
        RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonFlashRestoreModeUserData();
#endif

        RTDFlashRestoreBriCon();
        RTDFlashRestoreSixColorData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else
    {
        UserCommonFlashLoadSystemData();
        RTDFlashLoadOSDData();
        RTDFlashLoadSixColorData();
        RTDFlashLoadPanelUsedTimeData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS() > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            RTDFlashSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDFlashSaveOSDData();
        }
#endif
    }

    RTDFlashLoadColorSetting(GET_COLOR_TEMP_TYPE());
}

//--------------------------------------------------
// Description  : Load default data and save to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashWholeRestore(void)
{
    UserCommonFlashRestoreSystemData();
    RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonFlashRestoreModeUserData();
    UserCommonFlashRestoreADCSetting();
#endif

    RTDFlashRestoreBriCon();
    RTDFlashRestoreColorSetting();
    RTDFlashRestoreSixColorData();
    RTDFlashRestorePanelUsedTimeData();
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBacklight(void)
{
    BYTE ucItemOffset = 0;

    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            g_stOSDUserData = g_stOSDDefaultData;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((((BYTE *)(&g_stOSDUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((((BYTE *)(&g_stOSDUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) && (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}


//--------------------------------------------------
// Description  : Save OSD data to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOSDUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOSDUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOSDData(void)
{
    BYTE ucItemOffset = 0;

    g_stOSDUserData = g_stOSDDefaultData;

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load brightness/contrast from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadBriCon(BYTE ucSource)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSource, pData, sizeof(StructBriConDataType)) == _TRUE)
    {
        memcpy(&g_stBriConData, pData, sizeof(StructBriConDataType));
    }
    else
    {
        g_stBriConData = tBriConDefaultData[ucSource];
    }
}

//--------------------------------------------------
// Description  : Save brightness/contrast to Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveBriCon(BYTE ucSource)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSource, (BYTE *)(&g_stBriConData), sizeof(StructBriConDataType));
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBriCon(void)
{
    BYTE ucSourceIndex = 0;

    for(ucSourceIndex = 0; ucSourceIndex < _SOURCE_AMOUNT; ucSourceIndex++)
    {
        g_stBriConData = tBriConDefaultData[ucSourceIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSourceIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveBriCon(ucSourceIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Load color settings from Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadColorSetting(BYTE ucColorTempType)
{
#if(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserCommonAdjustOGCColorTempGain(ucColorTempType, (GET_OSD_GAMMA() - 1), pData, _OGC_NORMAL_TYPE);

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
        g_stColorProcData.usColorTempR = pData[0];
        g_stColorProcData.usColorTempG = pData[1];
        g_stColorProcData.usColorTempB = pData[2];
#endif
    }
    else
#endif
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, pData, sizeof(StructColorProcDataType)) == _TRUE)
        {
            memcpy(&g_stColorProcData, pData, sizeof(StructColorProcDataType));
        }
        else
        {
            g_stColorProcData = tColorTempDefaultData[ucColorTempType];
        }
    }
}


//--------------------------------------------------
// Description  : Save color settings to Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveColorSetting(BYTE ucColorTempType)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, (BYTE *)(&g_stColorProcData), sizeof(StructColorProcDataType));
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreColorSetting(void)
{
    BYTE ucColorTempIndex = 0;

    for(ucColorTempIndex = 0; ucColorTempIndex < _CT_COLORTEMP_AMOUNT; ucColorTempIndex++)
    {
        g_stColorProcData = tColorTempDefaultData[ucColorTempIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(ucColorTempIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC5_USER, pData, 1) == _TRUE)
    {
        stUserColorTemp = g_stColorProcData;
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDFlashSaveColorSetting(_CT_USER);
        g_stColorProcData = stUserColorTemp;
    }
}

//--------------------------------------------------
// Description  : Load six color data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadSixColorData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SIXCOLOR_DATA, pData, sizeof(StructSixColorDataType)) == _TRUE)
    {
        memcpy((BYTE *)(&g_stSixColorData), pData, sizeof(StructSixColorDataType));
    }
    else
    {
        g_stSixColorData = g_stSixColorDefaultData;
    }
}

//--------------------------------------------------
// Description  : Save six color data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveSixColorData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_SIXCOLOR_DATA, (BYTE *)(&g_stSixColorData), sizeof(StructSixColorDataType));
}

//--------------------------------------------------
// Description  : Restore default six color data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreSixColorData(void)
{
    g_stSixColorData = g_stSixColorDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SIXCOLOR_DATA, pData, 1) == _TRUE)
    {
        RTDFlashSaveSixColorData();
    }
}

//--------------------------------------------------
// Description  : Load Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelUsedTimeData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_DATA, pData, sizeof(StructTimeType)) == _TRUE)
    {
        memcpy((BYTE *)(&g_stPanelTimeData), pData, sizeof(StructTimeType));
    }
    else
    {
        SET_PANEL_TIME_HOUR(0);
        SET_PANEL_TIME_MIN(0);
    }
}

//--------------------------------------------------
// Description  : Save Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelUsedTimeData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_DATA, (BYTE *)(&g_stPanelTimeData), sizeof(StructTimeType));
}

//--------------------------------------------------
// Description  : Restore Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelUsedTimeData(void)
{
    SET_PANEL_TIME_HOUR(0);
    SET_PANEL_TIME_MIN(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_DATA, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelUsedTimeData();
    }
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Load panel index from flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelIndex(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
    }
    else
    {
        SET_MDOMAIN_PANEL_INDEX(0);
    }
}

//--------------------------------------------------
// Description  : Save panel index to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelIndex(void)
{
    BYTE ucPanelIndex = 0;

    ucPanelIndex = GET_MDOMAIN_PANEL_INDEX();

    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_INDEX, &ucPanelIndex, 1);
}

//--------------------------------------------------
// Description  : Restore panel index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelIndex(void)
{
    SET_MDOMAIN_PANEL_INDEX(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelIndex();
    }
}
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

#if 1//(_BEACON_MONITOR_SN_SET_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Load Monitor SN data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDNVRamLoadMonitorSNData(BYTE *pucData)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromRead(_MONITOR_SN_DATA_ADDRESS, _SN_BUF_LENGTH, (BYTE *)(&pucData[0]));
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Save Monitor SN data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDNVRamSaveMonitorSNData(BYTE ucLength,BYTE *pucData)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromWrite(_MONITOR_SN_DATA_ADDRESS, ucLength, (BYTE *)(&pucData[0]));
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Load Monitor IDSN data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDNVRamLoadMonitorIDSNData(BYTE *pucData)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromRead(_MONITOR_IDSN_DATA_ADDRESS, _IDSN_BUF_LENGTH, (BYTE *)(&pucData[0]));
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Save Monitor IDSN data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDNVRamSaveMonitorIDSNData(BYTE ucLength,BYTE *pucData)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    return UserCommonEepromWrite(_MONITOR_IDSN_DATA_ADDRESS, ucLength, (BYTE *)(&pucData[0]));
#else
    // Flash
#endif
}
#endif //#if (_BEACON_MONITOR_SN_SET_FUNCTION == _ON)


//--------------------------------------------------
// Description  : Load Panel Lux AB data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamLoadPanelLuxABData(void)
{
	BYTE ucIndex;
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    for(ucIndex = 0; ucIndex < _BK_SENSOR_POS_AMOUNT; ucIndex++)
    {
	    UserCommonEepromRead((_USER_PANEL_LUX_AB_DATA_ADDRESS + sizeof(StructPanelLuxABDataType)*ucIndex), sizeof(StructPanelLuxABDataType), (BYTE *)(&g_stPanelLuxABData[ucIndex]));
    }
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Save Panel Lux AB data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamSavePanelLuxABData(void)
{
	BYTE ucIndex = 0;
	
    pData[0] = 0x22;	
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromWrite(_USER_PANEL_LUT_LUX_AB_VERSION_ADDRESS, 1, &pData[0]);
    for(ucIndex = 0; ucIndex< _BK_SENSOR_POS_AMOUNT; ucIndex++)//Backlight Sensor Postion
    {
	    UserCommonEepromWrite((_USER_PANEL_LUX_AB_DATA_ADDRESS + sizeof(StructPanelLuxABDataType)*ucIndex), sizeof(StructPanelLuxABDataType), (BYTE *)(&g_stPanelLuxABData[ucIndex]));
	}
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Restore Panel Lux AB Data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamRestorePanelLuxABData(void)
{
	BYTE ucIndex = 0;
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
	// EEPROM     
    for(ucIndex = 0; ucIndex < _BK_SENSOR_POS_AMOUNT; ucIndex++)
    {
        g_stPanelLuxABData[ucIndex] = g_stPanelABDataDefault[ucIndex];
    }
    RTDNVRamSavePanelLuxABData();
#else
    // Flash
#endif
}


//--------------------------------------------------
// Description  : Load Panel Amb AB data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamLoadPanelAmbABData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead((_USER_PANEL_AMB_AB_DATA_ADDRESS + sizeof(StructPanelAmbABDataType)), sizeof(StructPanelAmbABDataType), (BYTE *)(&g_stPanelAmbABData));
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Save Panel Amb AB data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamSavePanelAmbABData(void)
{	
    pData[0] = 0x11;	
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromWrite(_USER_PANEL_AMB_AB_VERSION_ADDRESS, 1, &pData[0]);
    UserCommonEepromWrite((_USER_PANEL_AMB_AB_DATA_ADDRESS + sizeof(StructPanelAmbABDataType)), sizeof(StructPanelAmbABDataType), (BYTE *)(&g_stPanelAmbABData));
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Restore Panel Amb AB Data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamRestorePanelAmbABData(void)
{
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
	// EEPROM     
        g_stPanelAmbABData = g_stAmbABDataDefault;
    RTDNVRamSavePanelAmbABData();
#else
    // Flash
#endif
}


//--------------------------------------------------
// Description  : Load Panel Lux Range data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamLoadPanelLuxRangeData(void)
{
	BYTE ucIndex;
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    for(ucIndex = 0; ucIndex < _BK_SENSOR_CT_AMOUNT; ucIndex++)//Color -> Lux
    {
		UserCommonEepromRead((_USER_PANEL_LUX_RANGE_DATA_ADDRESS + sizeof(StructPanelLuxRangeDataType)*ucIndex), sizeof(StructPanelLuxRangeDataType), (BYTE *)(&g_stPanelLuxRangeData[ucIndex]));
    }
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Save Panel Lux Range data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamSavePanelLuxRangeData(void)
{
	BYTE ucIndex;
	
    pData[0] = 0x11;
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromWrite(_USER_PANEL_LUT_LUX_RANGE_VERSION_ADDRESS, 1, &pData[0]);
    for(ucIndex = 0; ucIndex < _BK_SENSOR_CT_AMOUNT; ucIndex++)//Color -> Lux
    {
	    UserCommonEepromWrite((_USER_PANEL_LUX_RANGE_DATA_ADDRESS + sizeof(StructPanelLuxRangeDataType)*ucIndex), sizeof(StructPanelLuxRangeDataType), (BYTE *)(&g_stPanelLuxRangeData[ucIndex]));
    }
#else
    // Flash
#endif
}

//--------------------------------------------------
// Description  : Restore Panel Lux Range Data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamRestorePanelLuxRangeData(void)
{
	BYTE ucIndex = 0;

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
	// EEPROM     
    for(ucIndex = 0; ucIndex < _BK_SENSOR_CT_AMOUNT; ucIndex++)
    {
        g_stPanelLuxRangeData[ucIndex] = g_stPanelLuxRangeDefault[ucIndex];
    }
    RTDNVRamSavePanelLuxRangeData();
#else
    // Flash    
#endif
}

void RTDNVRamCheckPanelLuxUserLutData(void)
{

 #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(_USER_PANEL_LUT_LUX_RANGE_VERSION_ADDRESS, 2, &pData[0]);
 #else
    // Flash
 #endif

    if(_USER_CALIB_LUT_DATA_ADDRESS_END >= _USER_PANEL_LUT_LUX_RANGE_VERSION_ADDRESS)
    {
        DebugMessageSystem("!!!space=", _USER_CALIB_LUT_DATA_ADDRESS_END);
        DebugMessageUart("!!!space=", _USER_CALIB_LUT_DATA_ADDRESS_END);
    }

	if((pData[0] != 0x11)||(pData[1] != 0x22))
	{		
        DebugMessageUart("!!!LuxAB pData[0]=", pData[0]);
        DebugMessageUart("!!!LuxRange pData[1]=", pData[1]);
		RTDNVRamRestorePanelLuxABData();
        RTDNVRamRestorePanelAmbABData();        
		RTDNVRamRestorePanelLuxRangeData();
		UserAdjustQAUpdateTargetSensor(_DEFAULT_GAMMA_LUX);
	}
	else
	{
		RTDNVRamLoadPanelLuxABData();
		RTDNVRamLoadPanelLuxRangeData();
		RTDNVRamLoadPanelAmbABData();        
	}

    //DebugMessageUart("Lux-A", g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucA_Data);
    //DebugMessageUart("Lux-B", g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucB_Data);

    //DebugMessageUart("LuxMax 9300:", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax);
    //DebugMessageUart("LuxMin 9300:", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMin);
    //DebugMessageUart("RealMax 9300:", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax);
    //DebugMessageUart("RealMin 9300:", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin);
	
    //DebugMessageUart("LuxMax 6500", g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMax);
    //DebugMessageUart("LuxMin 6500", g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMin);
    //DebugMessageUart("RealMax 6500:", g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax);
    //DebugMessageUart("RealMin 6500:", g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin);

}

//--------------------------------------------------
// Description  : Restore Lut Attri Data to EEPROM or FLASH
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDNVRamRestoreLutAttriData(void)
{
	BYTE ucIndex;
	Lut_Attri LutAttri_temp;
    WORD g_usCurrContrastRatio,g_usCurrCenterLuminance;

 #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    UserCommonEepromRead(_FT_LUTATTRIELEM_VERSION_ADDRESS, 1, &pData[0]);
 #else
    // Flash
 #endif
     
	UserCommonEepromRead(_FT_LUTATTRIELEM_ADDRESS + (_GAMMA_18 * sizeof(LutAttri_temp)), sizeof(LutAttri_temp), (BYTE *)&LutAttri_temp );
    g_usCurrContrastRatio = ((WORD)(LutAttri_temp.contrast[1]<<8) + LutAttri_temp.contrast[0]);
    g_usCurrCenterLuminance = ((WORD)(LutAttri_temp.maxLuminance[1]<<8) + LutAttri_temp.maxLuminance[0]);

    if(pData[0] != _LUT_ATTRI_VERSION)
    {
        pData[0] = _LUT_ATTRI_VERSION;
        DebugMessageUart("Init _LUT_ATTRI=", pData[0]);
        UserCommonEepromWrite(_FT_LUTATTRIELEM_VERSION_ADDRESS, 1, &pData[0]);

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
    	// EEPROM     
        for(ucIndex = 0; ucIndex <= _GAMMA_AMOUNT; ucIndex++)
        {
            g_pstFacLut_Attri = tFacDefaultLut_Attri[ucIndex];
            UserCommonEepromWrite(_FT_LUTATTRIELEM_ADDRESS + (ucIndex * sizeof(Lut_Attri)), sizeof(Lut_Attri), (BYTE *)(&g_pstFacLut_Attri));
        }
#else
        // Flash    
#endif
    }
}

#endif // #if(_OSD_TYPE == _BEACON_2014_OSD)
