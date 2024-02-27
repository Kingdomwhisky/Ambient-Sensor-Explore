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
// ID Code      : BEA2014Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "BEA2014Project.h"
#include "BEA2014NVRamOsd.h"
#include "BEA2014OsdTextTableDefine.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + (_A0_INPUT_PORT_TYPE & 0x0F))
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + (_D0_INPUT_PORT_TYPE & 0x0F))
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + (_D1_INPUT_PORT_TYPE & 0x0F))
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + (_D2_INPUT_PORT_TYPE & 0x0F))
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + (_D3_INPUT_PORT_TYPE & 0x0F))
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + (_D4_INPUT_PORT_TYPE & 0x0F))
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + (_D5_INPUT_PORT_TYPE & 0x0F))
#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + (_D6_INPUT_PORT_TYPE & 0x0F))

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#define _CONTRAST_MAX                               2848
#define _CONTRAST_MIN                               1248
#else
#define _CONTRAST_MAX                               178
#define _CONTRAST_MIN                               78
#endif

#define _CONTRAST_CENTER                            (((_CONTRAST_MAX - _CONTRAST_MIN) / 2) + _CONTRAST_MIN)
//--------------------------------------------------
// Definitions of LUT Lux Range & Lut Attri Data
//--------------------------------------------------
#ifndef _LUT_ATTRI_VERSION
#define _LUT_ATTRI_VERSION                          LOBYTE(\
                                                        1 +\
                                                        _PRODUCT_ID_SEL +\
                                                        _PANEL_TYPE +\
                                                        _GAMMA_TYPE\
                                                    ) 
#endif

#ifndef _GAMMA_CONTRAST_RATIO
#define _GAMMA_CONTRAST_RATIO                       (1100)  // CR: 1100:1 
#endif
#ifndef _DICOM_CONTRAST_RATIO
#define _DICOM_CONTRAST_RATIO                       (400)  // CR: 400:1 
#endif

#ifndef _DEFAULT_GAMMA_LUX
#define _DEFAULT_GAMMA_LUX                          (450)  
#endif
#define _DEFAULT_DICOM_200_LUX						(200)
#define _DEFAULT_DICOM_250_LUX						(250)
#define _DEFAULT_DICOM_300_LUX						(300)
#define _DEFAULT_DICOM_350_LUX						(350)
#define _DEFAULT_DICOM_400_LUX						(400)
#define _DEFAULT_DICOM_450_LUX						(450)
#define _DEFAULT_DICOM_500_LUX						(500)
#define _DEFAULT_DICOM_550_LUX						(550)
#define _DEFAULT_DICOM_600_LUX						(600)
#define _DEFAULT_DICOM_650_LUX						(650)
#define _DEFAULT_DICOM_700_LUX						(700)

//--------------------------------------------------
// Definitions of LUT USER L MAX Range
//--------------------------------------------------
#define _LMAX_MAX                             		600
#define _LMAX_MIN                             		200

//--------------------------------------------------
// Definitions of LUT USER L MIN Range
//--------------------------------------------------
#define _LMIN_MAX                             		15 // 1.5
#define _LMIN_MIN                             		3  // 0.3

//--------------------------------------------------
// Definitions of LUT USER LAMB Range
//--------------------------------------------------
#define _LAMB_MAX                             		30 // 3.0
#define _LAMB_MIN                             		0  // 0.0

//--------------------------------------------------
// Definitions of LUT USER Value Range(Curve)
//--------------------------------------------------
#define _LUT_USER_VALUE_MAX                         30 // 3.0
#define _LUT_USER_VALUE_MIN                         10 // 1.0

// Definitions of User Calibration Lut
//-------------------------------------------------
#define _LUT_USER_DICOM							   	0x00							
#define _LUT_USER_GAMMA							   	0x01							

#define _LUT_USER_TYPE							   	_LUT_USER_DICOM				
#define _LUT_USER_L_MAX							   	500
#define _LUT_USER_L_MIN							   	6  // 0.6
#define _LUT_USER_LAMB							    5  // 0.5
#define _LUT_USER_VALUE_GAMMA					   	22 // 2.2
#define _LUT_USER_COLORTEMP_OFFSET				   	0

#define _DEFAULT_MIDDLE_A_DATA						4010
#define _DEFAULT_MIDDLE_B_DATA        				3222				

#define _DEFAULT_UP_A_DATA							3563
#define _DEFAULT_UP_B_DATA        					-10747		

#define _DEFAULT_DOWN_A_DATA						3355
#define _DEFAULT_DOWN_B_DATA        				5827		

#define _DEFAULT_LUX_MAX							432700
#define _DEFAULT_LUX_MIN							327			
#define _DEFAULT_CA310_LUX_MAX						428700
#define _DEFAULT_CA310_LUX_MIN						324			

#define _DEFAULT_LUX_MAX_COLOR2						436100
#define _DEFAULT_LUX_MIN_COLOR2						325				
#define _DEFAULT_CA310_LUX_MAX_COLOR2				416200
#define _DEFAULT_CA310_LUX_MIN_COLOR2				328	

//--------------------------------------------------
// Definitions of Monitor SN Length 
//--------------------------------------------------
#define _SN_BUF_LENGTH                              25  
#define _IDSN_BUF_LENGTH                            4  
#define _REPLACE_NAME_LENGTH                        5  

//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _BACKLIGHT_MAX                              255
#define _BACKLIGHT_MIN                              10   // Dimming PWM Duty 4%~100%
#else
#define _BACKLIGHT_MAX                              4095
#define _BACKLIGHT_MIN                              200   // Dimming PWM Duty 5%~100%
#endif
#define _BACKLIGHT_CENTER                           (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)
#define _INIT_BACKLIGHT                             50 //UI display range: 0-100  

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
//#define GET_OSD_BACKLIGHT()                         (g_stOSDUserData.usBackLight)
//#define SET_OSD_BACKLIGHT(x)                        (g_stOSDUserData.usBackLight = (x))
#define GET_OSD_BACKLIGHT()                         ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOSDUserData.usBackLight : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOSDUserData.usBackLight_CT2: g_stOSDUserData.usBackLight_CT3)) : ((GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)?(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOSDUserData.usPCMBackLight : g_stOSDUserData.usPCMBackLight_CT2):(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOSDUserData.usBackLight : g_stOSDUserData.usBackLight_CT2)))
#define SET_OSD_BACKLIGHT(x)                        {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
    															g_stOSDUserData.usBackLight = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOSDUserData.usBackLight_CT3 = x;\
															}\
															else\
															{\
																g_stOSDUserData.usBackLight_CT2 = x;\
															}\
														}\
														else\
														{\
                                                            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)\
                                                            {\															
                                                                if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOSDUserData.usPCMBackLight = x;\
    															}\
    															else\
    															{\
    																g_stOSDUserData.usPCMBackLight_CT2 = x;\
    															}\
    	                                                    }\
															else\
    														{\
    															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOSDUserData.usBackLight = x;\
    															}\
    															else\
    															{\
    																g_stOSDUserData.usBackLight_CT2 = x;\
    															}\
    	                                                    }\
	                                                    }\
                                                    }

#define _GET_DUT_BACKLIGHT_MIN                      ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBackLight_Min : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBackLight_Min_CT2: g_stOsdUser2Data.usBackLight_Min_CT3)) : (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBackLight_Min : g_stOsdUser2Data.usBackLight_Min_CT2))
#define _SET_DUT_BACKLIGHT_MIN(x)                   {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBackLight_Min = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usBackLight_Min_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBackLight_Min_CT2 = x;\
															}\
														}\
														else\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBackLight_Min = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBackLight_Min_CT2 = x;\
															}\
														}\
                                                    }

#define _GET_DUT_BACKLIGHT_MAX                      ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBackLight_Max : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBackLight_Max_CT2: g_stOsdUser2Data.usBackLight_Max_CT3)) : (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBackLight_Max : g_stOsdUser2Data.usBackLight_Max_CT2))
#define _SET_DUT_BACKLIGHT_MAX(x)                   {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBackLight_Max = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usBackLight_Max_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBackLight_Max_CT2 = x;\
															}\
														}\
														else\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBackLight_Max = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBackLight_Max_CT2 = x;\
															}\
														}\
                                                    }

#define _GET_DUT_BACKLIGHT_CENTER                   ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBackLight_Cen : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBackLight_Cen_CT2: g_stOsdUser2Data.usBackLight_Cen_CT3)) : ((GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)?(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usPCMBackLight_Cen : g_stOsdUser2Data.usPCMBackLight_Cen_CT2):(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBackLight_Cen : g_stOsdUser2Data.usBackLight_Cen_CT2)))
#define _SET_DUT_BACKLIGHT_CENTER(x)                {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBackLight_Cen = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usBackLight_Cen_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBackLight_Cen_CT2 = x;\
															}\
														}\
														else\
														{\
                                                            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)\
                                                            {\															
                                                                if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usPCMBackLight_Cen = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usPCMBackLight_Cen_CT2 = x;\
    															}\
    	                                                    }\
															else\
    														{\
    															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usBackLight_Cen = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usBackLight_Cen_CT2 = x;\
    															}\
    														}\
														}\
                                                    }

#define _GET_USER_BACKLIGHT_SENSOR_VALUE            ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightSensorValue : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBacklightSensorValue_CT2: g_stOsdUser2Data.usBacklightSensorValue_CT3)) : ((GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)?(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usPCMBacklightSensorValue : g_stOsdUser2Data.usPCMBacklightSensorValue_CT2):(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightSensorValue : g_stOsdUser2Data.usBacklightSensorValue_CT2)))
#define _SET_USER_BACKLIGHT_SENSOR_VALUE(x)         {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBacklightSensorValue = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usBacklightSensorValue_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBacklightSensorValue_CT2 = x;\
															}\
														}\
														else\
														{\
                                                            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)\
                                                            {\
    															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usPCMBacklightSensorValue = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usPCMBacklightSensorValue_CT2 = x;\
    															}\
    	                                                    }\
															else\
    														{\
                												if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usBacklightSensorValue = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usBacklightSensorValue_CT2 = x;\
    															}\
	 	                                                    }\
                                                        }\
                                                    }

#define _GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE       ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightRestoreSensorValue : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBacklightRestoreSensorValue_CT2: g_stOsdUser2Data.usBacklightRestoreSensorValue_CT3)) : ((GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)?(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usPCMBacklightRestoreSensorValue : g_stOsdUser2Data.usPCMBacklightRestoreSensorValue_CT2):(GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightRestoreSensorValue : g_stOsdUser2Data.usBacklightRestoreSensorValue_CT2)))
#define _SET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE(x)    {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBacklightRestoreSensorValue = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usBacklightRestoreSensorValue_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBacklightRestoreSensorValue_CT2 = x;\
															}\
														}\
														else\
														{\
                                                            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)\
                                                            {\
                                                            	if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
                                                            	{\
                                                            		g_stOsdUser2Data.usPCMBacklightRestoreSensorValue = x;\
                                                            	}\
                                                            	else\
                                                            	{\
                                                            		g_stOsdUser2Data.usPCMBacklightRestoreSensorValue_CT2 = x;\
                                                            	}\
                                                            }\
                                                            else\
                                                            {\
    															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usBacklightRestoreSensorValue = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usBacklightRestoreSensorValue_CT2 = x;\
    															}\
                                                            }\
                                                        }\
                                                    }

// PWM Duty
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _INIT_DICOM_BACKLIGHT_200                   120
#define _INIT_DICOM_BACKLIGHT_250                   130
#define _INIT_DICOM_BACKLIGHT_300                   140
#define _INIT_DICOM_BACKLIGHT_350                   150
#define _INIT_DICOM_BACKLIGHT_400                   160
#define _INIT_DICOM_BACKLIGHT_450                   170
#define _INIT_DICOM_BACKLIGHT_500                   180
#define _INIT_DICOM_BACKLIGHT_550                   190
#define _INIT_DICOM_BACKLIGHT_600                   200
#define _INIT_DICOM_BACKLIGHT_650                   210
#define _INIT_DICOM_BACKLIGHT_700                   220
#define _INIT_BACKLIGHT_CALIB                       180
#define _INIT_DICOM_BACKLIGHT                       180
#define _INIT_NATIVE_BACKLIGHT                      _BACKLIGHT_CENTER
#else
#define _INIT_DICOM_BACKLIGHT_200                   ((120) << 4)
#define _INIT_DICOM_BACKLIGHT_250                   ((130) << 4)
#define _INIT_DICOM_BACKLIGHT_300                   ((140) << 4)
#define _INIT_DICOM_BACKLIGHT_350                   ((150) << 4)
#define _INIT_DICOM_BACKLIGHT_400                   ((160) << 4)
#define _INIT_DICOM_BACKLIGHT_450                   ((170) << 4)
#define _INIT_DICOM_BACKLIGHT_500                   ((180) << 4)
#define _INIT_DICOM_BACKLIGHT_550                   ((190) << 4)
#define _INIT_DICOM_BACKLIGHT_600                   ((200) << 4)
#define _INIT_DICOM_BACKLIGHT_650                   ((210) << 4)
#define _INIT_DICOM_BACKLIGHT_700                   ((220) << 4)
#define _INIT_BACKLIGHT_CALIB                       ((180) << 4)
#define _INIT_DICOM_BACKLIGHT                       ((180) << 4)
#define _INIT_NATIVE_BACKLIGHT                      _BACKLIGHT_CENTER
#endif

#define _INIT_DICOM200_BACKLIGHT_SENSOR_VALUE       350//3200
#define _INIT_DICOM250_BACKLIGHT_SENSOR_VALUE       450//3400
#define _INIT_DICOM300_BACKLIGHT_SENSOR_VALUE       550//3600
#define _INIT_DICOM350_BACKLIGHT_SENSOR_VALUE       650//3800
#define _INIT_DICOM400_BACKLIGHT_SENSOR_VALUE       750//4000
#define _INIT_DICOM450_BACKLIGHT_SENSOR_VALUE       850//4200
#define _INIT_DICOM500_BACKLIGHT_SENSOR_VALUE       950//4500
#define _INIT_DICOM550_BACKLIGHT_SENSOR_VALUE       1050//4800
#define _INIT_DICOM600_BACKLIGHT_SENSOR_VALUE       1150//5000
#define _INIT_DICOM650_BACKLIGHT_SENSOR_VALUE       1250//5200
#define _INIT_DICOM700_BACKLIGHT_SENSOR_VALUE       1350//5500

#define _INIT_BACKLIGHT_SENSOR_VALUE                850//4500
#define _INIT_BACKLIGHT_CALIB_SENSOR_VALUE          850//4500
#define _INIT_DICOM_BACKLIGHT_SENSOR_VALUE          850//4500
#define _INIT_NATIVE_BACKLIGHT_SENSOR_VALUE         _INIT_BACKLIGHT_SENSOR_VALUE

#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT)
#define _GET_USER_DICOM_BACKLIGHT_200               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight200 : g_stOsdUser2Data.usDicomBacklight200_CT2)
#define _SET_USER_DICOM_BACKLIGHT_200(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight200 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight200_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_250               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight250 : g_stOsdUser2Data.usDicomBacklight250_CT2)
#define _SET_USER_DICOM_BACKLIGHT_250(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight250 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight250_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_300               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight300 : g_stOsdUser2Data.usDicomBacklight300_CT2)
#define _SET_USER_DICOM_BACKLIGHT_300(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight300 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight300_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_350               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight350 : g_stOsdUser2Data.usDicomBacklight350_CT2)
#define _SET_USER_DICOM_BACKLIGHT_350(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight350 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight350_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_400               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight400 : g_stOsdUser2Data.usDicomBacklight400_CT2)
#define _SET_USER_DICOM_BACKLIGHT_400(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight400 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight400_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_450               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight450 : g_stOsdUser2Data.usDicomBacklight450_CT2)
#define _SET_USER_DICOM_BACKLIGHT_450(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight450 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight450_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_500               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight500 : g_stOsdUser2Data.usDicomBacklight500_CT2)
#define _SET_USER_DICOM_BACKLIGHT_500(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight500 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight500_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_550               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight550 : g_stOsdUser2Data.usDicomBacklight550_CT2)
#define _SET_USER_DICOM_BACKLIGHT_550(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight550 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight550_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_600               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight600 : g_stOsdUser2Data.usDicomBacklight600_CT2)
#define _SET_USER_DICOM_BACKLIGHT_600(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight600 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight600_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_650               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight650 : g_stOsdUser2Data.usDicomBacklight650_CT2)
#define _SET_USER_DICOM_BACKLIGHT_650(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight650 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight650_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_700               (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight700 : g_stOsdUser2Data.usDicomBacklight700_CT2)
#define _SET_USER_DICOM_BACKLIGHT_700(x)            {\
														if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
														{\
															g_stOsdUser2Data.usDicomBacklight700 = x;\
														}\
														else\
														{\
															g_stOsdUser2Data.usDicomBacklight700_CT2 = x;\
														}\
                                                    }

#define _GET_USER_DICOM200_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight200SensorValue : g_stOsdUser2Data.usDicomBacklight200SensorValue_CT2)
#define _SET_USER_DICOM200_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight200SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight200SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM250_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight250SensorValue : g_stOsdUser2Data.usDicomBacklight250SensorValue_CT2)
#define _SET_USER_DICOM250_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight250SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight250SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM300_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight300SensorValue : g_stOsdUser2Data.usDicomBacklight300SensorValue_CT2)
#define _SET_USER_DICOM300_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight300SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight300SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM350_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight350SensorValue : g_stOsdUser2Data.usDicomBacklight350SensorValue_CT2)
#define _SET_USER_DICOM350_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight350SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight350SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM400_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight400SensorValue : g_stOsdUser2Data.usDicomBacklight400SensorValue_CT2)
#define _SET_USER_DICOM400_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight400SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight400SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM450_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight450SensorValue : g_stOsdUser2Data.usDicomBacklight450SensorValue_CT2)
#define _SET_USER_DICOM450_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight450SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight450SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM500_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight500SensorValue : g_stOsdUser2Data.usDicomBacklight500SensorValue_CT2)
#define _SET_USER_DICOM500_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight500SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight500SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM550_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight550SensorValue : g_stOsdUser2Data.usDicomBacklight550SensorValue_CT2)
#define _SET_USER_DICOM550_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight550SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight550SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM600_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight600SensorValue : g_stOsdUser2Data.usDicomBacklight600SensorValue_CT2)
#define _SET_USER_DICOM600_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight600SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight600SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM650_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight650SensorValue : g_stOsdUser2Data.usDicomBacklight650SensorValue_CT2)
#define _SET_USER_DICOM650_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight650SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight650SensorValue_CT2 = x;\
															}\
                                                        }

#define _GET_USER_DICOM700_BACKLIGHT_SENSOR_VALUE       (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight700SensorValue : g_stOsdUser2Data.usDicomBacklight700SensorValue_CT2)
#define _SET_USER_DICOM700_BACKLIGHT_SENSOR_VALUE(x)    {\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight700SensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight700SensorValue_CT2 = x;\
															}\
                                                        }
#endif


#if 1//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _OFF)
#define _GET_USER_DICOM_BACKLIGHT                   ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usDicomBacklight_CT2: g_stOsdUser2Data.usDicomBacklight_CT3)) : (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklight : g_stOsdUser2Data.usDicomBacklight_CT2))
#define _SET_USER_DICOM_BACKLIGHT(x)                {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usDicomBacklight_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight_CT2 = x;\
															}\
														}\
														else\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklight = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklight_CT2 = x;\
															}\
                                                        }\
                                                    }

#define _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE      ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklightSensorValue : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usDicomBacklightSensorValue_CT2: g_stOsdUser2Data.usDicomBacklightSensorValue_CT3)) : (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usDicomBacklightSensorValue : g_stOsdUser2Data.usDicomBacklightSensorValue_CT2))
#define _SET_USER_DICOM_BACKLIGHT_SENSOR_VALUE(x)   {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklightSensorValue = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usDicomBacklightSensorValue_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklightSensorValue_CT2 = x;\
															}\
														}\
														else\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usDicomBacklightSensorValue = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usDicomBacklightSensorValue_CT2 = x;\
															}\
	                                                    }\
                                                    }
#endif

#if 1//(_ARM_MCU_CALIBRATION_SUPPORT == _ON)
#define _GET_USER_BACKLIGHT_MCU_CALIB               ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightMCUCalibration : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBacklightMCUCalibration_CT2: g_stOsdUser2Data.usBacklightMCUCalibration_CT3)) : (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightMCUCalibration : g_stOsdUser2Data.usBacklightMCUCalibration_CT2))
#define _SET_USER_BACKLIGHT_MCU_CALIB(x)            {\
														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBacklightMCUCalibration = x;\
															}\
															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
															{\
																g_stOsdUser2Data.usBacklightMCUCalibration_CT3 = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBacklightMCUCalibration_CT2 = x;\
															}\
														}\
														else\
														{\
															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
															{\
																g_stOsdUser2Data.usBacklightMCUCalibration = x;\
															}\
															else\
															{\
																g_stOsdUser2Data.usBacklightMCUCalibration_CT2 = x;\
															}\
                                                        }\
                                                    }

#define _GET_USER_BACKLIGHT_MCU_CALIB_SENSOR_VALUE     ((_ENABLE_CANON_THREE_CT_SUPPORT == _ON) ? (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue : (GET_COLOR_TEMP_TYPE() == _CT_9300 ? g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue_CT2: g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue_CT3)) : (GET_COLOR_TEMP_TYPE() >= _CT_6500 ? g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue : g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue_CT2))
#define _SET_USER_BACKLIGHT_MCU_CALIB_SENSOR_VALUE(x)   {\
    														if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)\
    														{\
    															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue = x;\
    															}\
    															else if(GET_COLOR_TEMP_TYPE() == _CT_7500)\
    															{\
    																g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue_CT3 = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue_CT2 = x;\
    															}\
    														}\
    														else\
    														{\
    															if(GET_COLOR_TEMP_TYPE() >= _CT_6500)\
    															{\
    																g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue = x;\
    															}\
    															else\
    															{\
    																g_stOsdUser2Data.usBacklightMCUCalibrationSensorValue_CT2 = x;\
    															}\
    	                                                    }\
                                                        }
#endif

#if 1//(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)
#define _GET_USER_BACKLIGHT_CALIB                       (g_stOsdUser2Data.usBacklightCalibration)
#define _SET_USER_BACKLIGHT_CALIB(x)                    {\
    														g_stOsdUser2Data.usBacklightCalibration = x;\
                                                        }

#define _GET_USER_BACKLIGHT_CALIB_SENSOR_VALUE          (g_stOsdUser2Data.usBacklightCalibrationSensorValue)
#define _SET_USER_BACKLIGHT_CALIB_SENSOR_VALUE(x)       {\
															g_stOsdUser2Data.usBacklightCalibrationSensorValue = x;\
                                                        }

#endif

#if 1//(NATIVE:_GAMMA_OFF)
#define _GET_USER_NATIVE_BACKLIGHT                      (g_stOsdUser2Data.usNativeBacklight)
#define _SET_USER_NATIVE_BACKLIGHT(x)                   {\
															g_stOsdUser2Data.usNativeBacklight = x;\
                                                        }
#define _GET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE         (g_stOsdUser2Data.usNativeBacklightSensorValue)
#define _SET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE(x)      {\
                                                            g_stOsdUser2Data.usNativeBacklightSensorValue = x;\
                                                        }
#endif

//--------------------------------------------------
// Definitions of BackLight End
//--------------------------------------------------



//--------------------------------------------------
// Definitions of Brightness Range
//--------------------------------------------------
#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
#define _BRIGHTNESS_MAX                             712
#define _BRIGHTNESS_MIN                             312
#else
#define _BRIGHTNESS_MAX                             178
#define _BRIGHTNESS_MIN                             78
#endif

#define _BRIGHTNESS_CENTER                          (((_BRIGHTNESS_MAX - _BRIGHTNESS_MIN) / 2) + _BRIGHTNESS_MIN)

//--------------------------------------------------
// Definitions of Sharpness Range
//--------------------------------------------------
#define _SHARPNESS_MAX                              4
#define _SHARPNESS_MIN                              0
#define _SHARPNESS_CENTER                           (((_SHARPNESS_MAX - _SHARPNESS_MIN) / 2) + _SHARPNESS_MIN)
//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _OSD_PHASE_MAX                              100
#define _OSD_PHASE_MIN                              0

//--------------------------------------------------
// Definitions of Colortemp User RGB
//--------------------------------------------------
#define _USER_RGB_MAX                               255
#define _USER_RGB_MIN                               0
#define _USER_RGB_CENTER                            (((_USER_RGB_MAX - _USER_RGB_MIN) / 2) + _USER_RGB_MIN)

//--------------------------------------------------
// Definitions of OD Gain Range
//--------------------------------------------------
#define _OD_GAIN_MAX                                127
#define _OD_GAIN_MIN                                0
#define _OD_GAIN_CENTER                             (((_OD_GAIN_MAX - _OD_GAIN_MIN) / 2) + _OD_GAIN_MIN)

//--------------------------------------------------
// Definitions of MBR Backlight Range
//--------------------------------------------------
#define _OSD_MBR_DUTY_MAX                           100
#define _OSD_MBR_DUTY_MIN                           0
#define _OSD_MBR_DUTY_CENTER                        (((_OSD_MBR_DUTY_MAX - _OSD_MBR_DUTY_MIN) / 2) + _OSD_MBR_DUTY_MIN)
#define _OSD_MBR_DUTY_DEFAULT                       40
#define _OSD_MBR_POS_MAX                            100
#define _OSD_MBR_POS_MIN                            0
#define _OSD_MBR_POS_CENTER                         (((_OSD_MBR_POS_MAX - _OSD_MBR_POS_MIN) / 2) + _OSD_MBR_POS_MIN)
#define _OSD_MBR_POS_DEFAULT                        _OSD_MBR_POS_CENTER

//--------------------------------------------------
// Definitions of 3D EFFECT
//--------------------------------------------------
#define _3D_EFFECT_MAX                              0x10
#define _3D_EFFECT_MIN                              0x00

//--------------------------------------------------
// Definitions of 2DTO3D EFFECT
//--------------------------------------------------
#define _2DTO3D_H_EFFECT_MAX                        0x30
#define _2DTO3D_H_EFFECT_MIN                        0x00

#define _2DTO3D_H_V_EFFECT_MAX                      0xFF
#define _2DTO3D_H_V_EFFECT_MIN                      0x00

//--------------------------------------------------
// Definitions of Menu Time Range
//--------------------------------------------------
#define _OSD_TIMEOUT_MAX                            60
#define _OSD_TIMEOUT_MIN                            15
#define _OSD_TIMEOUT_CENTER                         (((_OSD_TIMEOUT_MAX - _OSD_TIMEOUT_MIN) / 2) + _OSD_TIMEOUT_MIN)

//--------------------------------------------------
// Definitions of Transparency Range
//--------------------------------------------------
#define _OSD_TRANSPARENCY_MAX                       255
#define _OSD_TRANSPARENCY_MIN                       0
#define _OSD_TRANSPARENCY_CENTER                    (((_OSD_TRANSPARENCY_MAX - _OSD_TRANSPARENCY_MIN) / 2) + _OSD_TRANSPARENCY_MIN)

//--------------------------------------------------
// Definitions of OSD position
//--------------------------------------------------
typedef enum
{
    _OSD_POSITON_LT,
    _OSD_POSITON_RT,
    _OSD_POSITON_LB,
    _OSD_POSITON_RB,
    _OSD_POSITON_MIDDLE,
    _OSD_POSITON_USER,
    _OSD_POSITON_AMOUNT=_OSD_POSITON_MIDDLE,
}EnumUIPositionType;
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
#define _OSD_POS_TYPE                              	_OSD_POSITON_RB
#define _OSD_H_POS_DEFAULT                          _OSD_H_POS_MAX
#define _OSD_V_POS_DEFAULT                          _OSD_V_POS_MAX
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
#define _OSD_POS_TYPE                              	_OSD_POSITON_RT
#define _OSD_H_POS_DEFAULT                          _OSD_H_POS_MAX
#define _OSD_V_POS_DEFAULT                          _OSD_V_POS_MIN+2
#else
#define _OSD_POS_TYPE                              	_OSD_POSITON_RT
#define _OSD_H_POS_DEFAULT                          _OSD_H_POS_MAX
#define _OSD_V_POS_DEFAULT                          _OSD_V_POS_MAX
#endif

//--------------------------------------------------
// Definitions of OSD H Position Range
//--------------------------------------------------
#define _OSD_H_POS_MAX                              100
#define _OSD_H_POS_MIN                              0
#define _OSD_H_POS_CENTER                           (((_OSD_H_POS_MAX - _OSD_H_POS_MIN) / 2) + _OSD_H_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_V_POS_MAX                              100
#define _OSD_V_POS_MIN                              0
#define _OSD_V_POS_CENTER                           (((_OSD_V_POS_MAX - _OSD_V_POS_MIN) / 2) + _OSD_V_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_ASPECT_ORIGINAL_RATIO_MAX              100
#define _OSD_ASPECT_ORIGINAL_RATIO_MIN              0
#define _OSD_ASPECT_ORIGINAL_RATIO_CENTER           ((_OSD_ASPECT_ORIGINAL_RATIO_MAX - _OSD_ASPECT_ORIGINAL_RATIO_MIN) / 2)

//--------------------------------------------------
// Definitions of Hue Saturation Range
// Allowed Hue = 0 ~ 360, Sat = 0 ~ 330
//--------------------------------------------------
#define _DEFAULT_HUE                                _HUE_CENTER
#define _DEFAULT_SATURATION                         _SATURATION_CENTER

//--------------------------------------------------
// Definitions of OSD Volume Range
//--------------------------------------------------
#define _OSD_VOLUME_MAX                             100
#define _OSD_VOLUME_MIN                             0
#define _OSD_VOLUME_CENTER                          (((_OSD_VOLUME_MAX - _OSD_VOLUME_MIN) / 2) + _OSD_VOLUME_MIN)

//--------------------------------------------------
// Definitions of Hue Saturation Range
//--------------------------------------------------
#define _SIX_COLOR_SATURATION_MAX                   200
#define _SIX_COLOR_SATURATION_MIN                   0
#define _SIX_COLOR_SATURATION_CENTER                100

#define _SIX_COLOR_HUE_MAX                          100
#define _SIX_COLOR_HUE_MIN                          0
#define _SIX_COLOR_HUE_CENTER                       50


//==========================================================================================================
// Timer
//==========================================================================================================
//--------------------------------------------------
// MACRO for Check Timer event
// Max 60 minutes
// 2000 comes from 60 secs div _TIMER_COUNT_20_MS
//--------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
#define GET_PIXEL_ORBITING_TIME()                   (g_stTimer.b4OrbitingTimer)
#define SET_PIXEL_ORBITING_TIME(x)                  (g_stTimer.b4OrbitingTimer = (x))

#define GET_PIXEL_ORBITING_CAPABILITY()             (g_stPixelOrbitingStatus.b1Capability)
#define SET_PIXEL_ORBITING_CAPABILITY(x)            (g_stPixelOrbitingStatus.b1Capability = (x))
#endif
#endif


//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT1))
#define SET_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT1)

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT0))
#define SET_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT0)

//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()                        (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT2)
#define SET_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl |= _BIT2)
#define CLR_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl &= ~_BIT2)

//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()                       (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl |= _BIT3)
#define CLR_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl &= ~_BIT3)

//--------------------------------------------------
// Macro of Key Hold Start
//--------------------------------------------------
#define GET_KEY_HOLD()                              (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT4)
#define SET_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl |= _BIT4)
#define CLR_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl &= ~_BIT4)

#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_OSD_ADDRESS()                  (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress)
#define SET_FREESYNC_OSD_ADDRESS(x)                 (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress = (x))
#endif

//--------------------------------------------------
// Macro of Key Message
//--------------------------------------------------
#define GET_KEYMESSAGE()                            (g_stOsdInfo.ucOsdKeyMessage)
#define SET_KEYMESSAGE(x)                           (g_stOsdInfo.ucOsdKeyMessage = (x))

//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
#define _MENU_KEY_MESSAGE                           0
#define _RIGHT_KEY_MESSAGE                          1
#define _LEFT_KEY_MESSAGE                           2
#define _EXIT_KEY_MESSAGE                           3
#define _OK_KEY_MESSAGE                             4
//#define _LIGHTBOX_KEY_MESSAGE                       5
#define _POWER_KEY_MESSAGE                          5
#define _SOURCE_KEY_MESSAGE                         6
#define _UP_KEY_MESSAGE								7
#define _DOWN_KEY_MESSAGE							8

#define _HOLD_KEY_MESSAGE                           9
#define _NONE_KEY_MESSAGE                           10

#define _KEY_AMOUNT                                 9

//--------------------------------------------------
// Definitions of LED indicction
//--------------------------------------------------
typedef enum
{
    _LED_ALL_OFF = _LED_SYSTEM_END,
} EnumUserLedIndication;

//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------
#define FONTBYTE0(x)                                HIBYTE(0x1000 | (x)), LOBYTE(0x1000 | (x))
#define FONTBYTE1(x)                                HIBYTE(0x5000 | (x)), LOBYTE(0x5000 | (x))
#define FONTBYTE2(x)                                HIBYTE(0x9000 | (x)), LOBYTE(0x9000 | (x))
#define FONTALLBYTE(x)                              HIBYTE(0xD000 | (x)), LOBYTE(0xD000 | (x))
#define WINDOWBYTE0(x)                              HIBYTE(0x0000 | (x)), LOBYTE(0x0000 | (x))
#define WINDOWBYTE1(x)                              HIBYTE(0x4000 | (x)), LOBYTE(0x4000 | (x))
#define WINDOWBYTE2(x)                              HIBYTE(0x8000 | (x)), LOBYTE(0x8000 | (x))
#define WINDOWALLBYTE(x)                            HIBYTE(0xC000 | (x)), LOBYTE(0xC000 | (x))
#define FRAMEBYTE0(x)                               WINDOWBYTE0(x)
#define FRAMEBYTE1(x)                               WINDOWBYTE1(x)
#define FRAMEBYTE2(x)                               WINDOWBYTE2(x)
#define FRAMEALLBYTE(x)                             WINDOWALLBYTE(x)
#define WINNO(x)                                    (x)
#define ROW(x)                                      (x)
#define COL(x)                                      (x)
#define WIDTH(x)                                    (x)
#define HEIGHT(x)                                   (x)
#define LENGTH(x)                                   (x)
#define FGCOLOR(x)                                  (x)
#define BGCOLOR(x)                                  (x)
#define COLOR00(x)                                  (x)
#define COLOR01(x)                                  (x)
#define COLOR10(x)                                  (x)
#define COLOR11(x)                                  (x)
#define XSTART(x)                                   (x)
#define YSTART(x)                                   (x)
#define XEND(x)                                     (x)
#define YEND(x)                                     (x)
#define PIXELROW(x)                                 ((x) * 18)
#define PIXELCOL(x)                                 ((x) * 12)

//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by OsdDisplayDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                          (0)
#define _DET_OVERRANGE_MIN                          (1)

//--------------------------------------------------
// Definitions of OSD Function
//--------------------------------------------------
#define _SPACE_                                     0xfc
#define _EXT_                                       0xfc
#define _REPEAT_                                    0xfd
#define _NEXT_                                      0xfe
#define _END_                                       0xff


//--------------------------------------------------
// Definitions of Write Byte
//--------------------------------------------------
#define _WRITE_BYTE0                                0
#define _WRITE_BYTE1                                1
#define _WRITE_BYTE2                                2
#define _WRITE_BYTEALL                              3

//--------------------------------------------------
// Macro of Osd Put String Mode
//--------------------------------------------------
typedef enum
{
    _PUT_STRING_LEFT = 0,
    _PUT_STRING_CENTER,
    _PUT_STRING_RIGHT,

} EnumOsdPutStringMode;

//--------------------------------------------------
// MACRO for OSD Logo Status
//--------------------------------------------------
#define GET_OSD_LOGO_ON()                           (g_stOsdInfo.b1OsdLogo)
#define SET_OSD_LOGO_ON(x)                          (g_stOsdInfo.b1OsdLogo = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Quick Menu
//--------------------------------------------------
#define GET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU()       (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort)
#define SET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU(x)      (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort = (x))

#if(_DP_DEBUG_MSG == _ON)
//--------------------------------------------------
// MACRO for Power Saving Show DP Info
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_INFO()         (g_stOsdInfo.b1OsdWakeUpShowDpINFO)
#define SET_OSD_POWER_SAVING_SHOW_DP_INFO(x)        (g_stOsdInfo.b1OsdWakeUpShowDpINFO = (x))
#define GET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT()    (g_stOsdInfo.b4OsdWakeUpShowDpINFOPort)
#define SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(x)   (g_stOsdInfo.b4OsdWakeUpShowDpINFOPort = (x))
#endif

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_SOURCE()          (g_stOsdInfo.b1OsdWakeUpShowSource)
#define SET_OSD_POWER_SAVING_SHOW_SOURCE(x)         (g_stOsdInfo.b1OsdWakeUpShowSource = (x))

//--------------------------------------------------
// MACRO for Power Saving Show LightBox Mode Option
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_LIGHTBOX_MODE()   (g_stOsdInfo.b1OsdWakeUpLightBoxMode)
#define SET_OSD_POWER_SAVING_SHOW_LIGHTBOX_MODE(x)  (g_stOsdInfo.b1OsdWakeUpLightBoxMode = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_IN_FACTORY_MENU_STATUS()            (g_stOsdInfo.b1OsdFactoryModeStatus)
#define SET_OSD_IN_FACTORY_MENU_STATUS(x)           (g_stOsdInfo.b1OsdFactoryModeStatus = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_DO_ASPECT_RATIO()                   (g_stOsdInfo.b1OsdDoAspectRatio)
#define SET_OSD_DO_ASPECT_RATIO(x)                  (g_stOsdInfo.b1OsdDoAspectRatio = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_COLOR_FORMAT()                      (g_stOsdInfo.b3OsdColorFormat)
#define SET_OSD_COLOR_FORMAT(x)                     (g_stOsdInfo.b3OsdColorFormat = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE_PREVIOUS()                    (g_stOsdInfo.ucOsdStatePrevious)
#define SET_OSD_STATE_PREVIOUS(x)                   (g_stOsdInfo.ucOsdStatePrevious = (x))


//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE()                             (g_stOsdInfo.usOsdState)
#define SET_OSD_STATE(x)                            (g_stOsdInfo.usOsdState = (x))

//--------------------------------------------------
// MACRO for Osd Evevt Message
//--------------------------------------------------
#define GET_OSD_EVENT_MESSAGE()                     (g_stOsdInfo.ucOsdEventMsg)
#define SET_OSD_EVENT_MESSAGE(x)                    (g_stOsdInfo.ucOsdEventMsg = (x))

//--------------------------------------------------
// MACRO for Six Color
//--------------------------------------------------
#define GET_OSD_SIX_COLOR()                         (g_stOsdInfo.b3OsdsixColor)
#define SET_OSD_SIX_COLOR(x)                        (g_stOsdInfo.b3OsdsixColor = (x))

//--------------------------------------------------
// MACRO for Six Color Hue
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_HUE()                     (g_stOsdInfo.b3OsdsixColorHue)
#define SET_OSD_SIX_COLOR_HUE(x)                    (g_stOsdInfo.b3OsdsixColorHue = (x))

//--------------------------------------------------
// MACRO for Six Color Saturation
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_SATURATION()              (g_stOsdInfo.b3OsdsixColorSaturation)
#define SET_OSD_SIX_COLOR_SATURATION(x)             (g_stOsdInfo.b3OsdsixColorSaturation = (x))

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_DOUBLE_SIZE()                       (g_stOsdInfo.b1OsdDoubleSizeStatus)
#define SET_OSD_DOUBLE_SIZE(x)                      (g_stOsdInfo.b1OsdDoubleSizeStatus = (x))

//--------------------------------------------------
// MACRO for Freeze Status
//--------------------------------------------------
#define GET_OSD_FREEZE_STATUS()                     (g_stOsdInfo.b1FreezeStatus)
#define SET_OSD_FREEZE_STATUS(x)                    (g_stOsdInfo.b1FreezeStatus = (x))

#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
#define GET_FREEZE_DISABLE_MSG_STATE()              (g_stOsdInfo.b1FreezeDisableOsdStatus)
#define SET_FREEZE_DISABLE_MSG_STATE(x)             (g_stOsdInfo.b1FreezeDisableOsdStatus = (x))
#endif

#define GET_OSD_ITEM_INDEX()                        (g_stOsdInfo.ucOsdItemIndex)
#define SET_OSD_ITEM_INDEX(x)                       (g_stOsdInfo.ucOsdItemIndex = (x))


#define GET_OSD_INFO_STRING_MODE()                  (g_stOsdInfo.b2StringMode)
#define SET_OSD_INFO_STRING_MODE(x)                 (g_stOsdInfo.b2StringMode = x)
#define CLR_OSD_INFO_STRING_MODE()                  (g_stOsdInfo.b2StringMode = _PUT_STRING_LEFT)

//--------------------------------------------------
// Macro of Osd Put String Center Length
//--------------------------------------------------
#define GET_OSD_INFO_STRING_MODE_LENGTH()           (g_stOsdInfo.ucStringModeLength)
#define SET_OSD_INFO_STRING_MODE_LENGTH(x)          (g_stOsdInfo.ucStringModeLength = x)
#define CLR_OSD_INFO_STRING_MODE_LENGTH()           (g_stOsdInfo.ucStringModeLength = 0)

//--------------------------------------------------
// Macro of Osd Put String Blank Pixel
//--------------------------------------------------
#define GET_OSD_INFO_STRING_BLANK_PIXEL()           (g_stOsdInfo.ucStringBlankPixel)
#define SET_OSD_INFO_STRING_BLANK_PIXEL(x)          (g_stOsdInfo.ucStringBlankPixel = x)
#define CLR_OSD_INFO_STRING_BLANK_PIXEL()           (g_stOsdInfo.ucStringBlankPixel = 0)

//==========================================================================================================
// Macro of NVRam BriCon Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_CONTRAST()                          (g_stBriConData.usContrast)
#define SET_OSD_CONTRAST(x)                         (g_stBriConData.usContrast = (x))

//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_BRIGHTNESS()                        (g_stBriConData.usBrightness)
#define SET_OSD_BRIGHTNESS(x)                       (g_stBriConData.usBrightness = (x))

//==========================================================================================================
// Macro of NVRam User Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Rotation Status
//--------------------------------------------------
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_OSD_DISP_ROTATION_SIZE_TYPE()           (g_stOSDUserData.b2DispRotationSizeType)
#define SET_OSD_DISP_ROTATION_SIZE_TYPE(x)          (g_stOSDUserData.b2DispRotationSizeType = (x))
#endif

//--------------------------------------------------
// MACRO for Motion Blur Reduction
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define GET_OSD_MBR_STATUS()                        (g_stOSDUserData.b2MbrStatus)
#define SET_OSD_MBR_STATUS(x)                       (g_stOSDUserData.b2MbrStatus = (x))
#define GET_OSD_MBR_DUTY()                          (g_stOSDUserData.b7MbrDuty)
#define SET_OSD_MBR_DUTY(x)                         (g_stOSDUserData.b7MbrDuty = (x))
#define GET_OSD_MBR_POSITION()                      (g_stOSDUserData.b7MbrPosition)
#define SET_OSD_MBR_POSITION(x)                     (g_stOSDUserData.b7MbrPosition = (x))
#endif

//--------------------------------------------------
// MACRO for DP Port Version
//--------------------------------------------------
#define GET_OSD_DP_D0_VERSION()                     (g_stOSDUserData.b2OsdDpD0PortVersion)
#define SET_OSD_DP_D0_VERSION(x)                    (g_stOSDUserData.b2OsdDpD0PortVersion = (x))

#define GET_OSD_DP_D1_VERSION()                     (g_stOSDUserData.b2OsdDpD1PortVersion)
#define SET_OSD_DP_D1_VERSION(x)                    (g_stOSDUserData.b2OsdDpD1PortVersion = (x))

#define GET_OSD_DP_D2_VERSION()                     (g_stOSDUserData.b2OsdDpD2PortVersion)
#define SET_OSD_DP_D2_VERSION(x)                    (g_stOSDUserData.b2OsdDpD2PortVersion = (x))

#define GET_OSD_DP_D6_VERSION()                     (g_stOSDUserData.b2OsdDpD6PortVersion)
#define SET_OSD_DP_D6_VERSION(x)                    (g_stOSDUserData.b2OsdDpD6PortVersion = (x))

#define GET_OSD_DP_MST()                            (g_stOSDUserData.b3OsdDpMST)
#define SET_OSD_DP_MST(x)                           (g_stOSDUserData.b3OsdDpMST = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DISP_ROTATE()                       (g_stOSDUserData.b3OsdDispRotate)
#define SET_OSD_DISP_ROTATE(x)                      (g_stOSDUserData.b3OsdDispRotate = (x))

//--------------------------------------------------
// MACRO for Latency
//--------------------------------------------------
#define GET_OSD_LATENCY()                           (g_stOSDUserData.b2LatencyStatus)
#define SET_OSD_LATENCY(x)                          (g_stOSDUserData.b2LatencyStatus = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DP_VERSION_HOTKEY_DISP()            (g_stOSDUserData.b1OsdDpVersionHotKeyDisp)
#define SET_OSD_DP_VERSION_HOTKEY_DISP(x)           (g_stOSDUserData.b1OsdDpVersionHotKeyDisp = (x))

//--------------------------------------------------
// MACRO for Display
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_OPTION()       (g_stOSDUserData.b1PreShowDpHotKeyVersion)
#define SET_OSD_POWER_SAVING_SHOW_DP_OPTION(x)      (g_stOSDUserData.b1PreShowDpHotKeyVersion = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY()                  (g_stOSDUserData.b1PanelUniformity)
#define SET_OSD_PANEL_UNIFORMITY(x)                 (g_stOSDUserData.b1PanelUniformity = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY_TYPE()             (g_stOSDUserData.b3PanelUniformityType)
#define SET_OSD_PANEL_UNIFORMITY_TYPE(x)            (g_stOSDUserData.b3PanelUniformityType = (x))

//--------------------------------------------------
// MACRO for PCM Soft Proft
//--------------------------------------------------
#define GET_OSD_PCM_SOFT_PROFT_MODE()               (g_stOSDUserData.b1PCMSoftProftMode)
#define SET_OSD_PCM_SOFT_PROFT_MODE(x)              (g_stOSDUserData.b1PCMSoftProftMode = (x))
//--------------------------------------------------
// MACRO for BrunIn Mode
//--------------------------------------------------
#define GET_OSD_FACTORY_MODE_BRUNIN()               (g_stOSDUserData.b1FactoryBrunInMode)
#define SET_OSD_FACTORY_MODE_BRUNIN(x)              (g_stOSDUserData.b1FactoryBrunInMode = (x))

//--------------------------------------------------
// MACRO for Backlight Sensor Status
//--------------------------------------------------
#define GET_OSD_BACKLIGHT_SENSOR_STATUS()           (g_stOSDUserData.b1BacklightSensorMode)
#define SET_OSD_BACKLIGHT_SENSOR_STATUS(x)          (g_stOSDUserData.b1BacklightSensorMode = (x))

//--------------------------------------------------
// MACRO for OSD Input Port Value
//--------------------------------------------------
#define GET_OSD_INPUT_PORT_OSD_ITEM()               (g_stOSDUserData.ucOsdInputPort)
#define SET_OSD_INPUT_PORT_OSD_ITEM(x)              (g_stOSDUserData.ucOsdInputPort = (x))

//--------------------------------------------------
// MACRO for OSD Rotate
//--------------------------------------------------
#define GET_OSD_ROTATE_STATUS()                     (g_stOSDUserData.b2OsdRotate)
#define SET_OSD_ROTATE_STATUS(x)                    (g_stOSDUserData.b2OsdRotate = (x))

//--------------------------------------------------
// MACRO for Ambientlight Sensor Status
//--------------------------------------------------
#define GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()        (g_stOSDUserData.b1AmbientlightSensorMode)
#define SET_OSD_AMBIENTLIGHT_SENSOR_STATUS(x)       (g_stOSDUserData.b1AmbientlightSensorMode = (x))

//--------------------------------------------------
// MACRO for Distance Sensor Status    
//--------------------------------------------------
#define GET_OSD_DISTANCE_SENSOR_STATUS()            (g_stOSDUserData.b2DistanceSensorMode)
#define SET_OSD_DISTANCE_SENSOR_STATUS(x)           (g_stOSDUserData.b2DistanceSensorMode = (x))

//--------------------------------------------------
// MACRO for Gravity Sensor Status    
//--------------------------------------------------
#define GET_OSD_GRAVITY_SENSOR_STATUS()            (g_stOSDUserData.b1GravitySensorMode)
#define SET_OSD_GRAVITY_SENSOR_STATUS(x)           (g_stOSDUserData.b1GravitySensorMode = (x))
//--------------------------------------------------
// MACRO for LightBoxMode Status
//--------------------------------------------------
#define GET_OSD_LIGHTBOXMODE_STATUS()               (g_stOSDUserData.b1LightBoxModeStatus)
#define SET_OSD_LIGHTBOXMODE_STATUS(x)              (g_stOSDUserData.b1LightBoxModeStatus = (x))

//--------------------------------------------------
// MACRO for Two Hours Tips
//--------------------------------------------------
#define GET_OSD_2HOURS_TIPS()      	                (g_stOSDUserData.b12HoursTips)
#define SET_OSD_2HOURS_TIPS(x)		                (g_stOSDUserData.b12HoursTips = (x))

//--------------------------------------------------
// MACRO for Panel Use Life Hours Tips
//--------------------------------------------------
#define GET_OSD_PANEL_USELIFE_TIPS()      	        (g_stOSDUserData.b1PanelUseLifeTips)
#define SET_OSD_PANEL_USELIFE_TIPS(x)		        (g_stOSDUserData.b1PanelUseLifeTips = (x))

//--------------------------------------------------
// MACRO for Read Mode
//--------------------------------------------------
#define GET_OSD_READING_REPORT_MODE()      	        (g_stOSDUserData.b2ReadingReportMode)
#define SET_OSD_READING_REPORT_MODE(x)		        (g_stOSDUserData.b2ReadingReportMode = (x))

//--------------------------------------------------
// MACRO for FPGA Test Map
//--------------------------------------------------
#define GET_OSD_FPGA_TEST_IMAGE()      	            (g_stOSDUserData.b2FPGATestMapIndex)
#define SET_OSD_FPGA_TEST_IMAGE(x)		            (g_stOSDUserData.b2FPGATestMapIndex = (x))

//--------------------------------------------------
// MACRO for Power Saving Mode
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_MODE()      	        (g_stOSDUserData.b2PowerSavingMode)
#define SET_OSD_POWER_SAVING_MODE(x)		        (g_stOSDUserData.b2PowerSavingMode = (x))

//--------------------------------------------------
// MACRO for Background Light Mode
//--------------------------------------------------
#define GET_OSD_BACKGROUND_LIGHT_MODE()      	    (g_stOSDUserData.b3BackgroundLightMode)
#define SET_OSD_BACKGROUND_LIGHT_MODE(x)		    (g_stOSDUserData.b3BackgroundLightMode = (x))

#if(_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)    

#define GET_DDCCI_RGB_MODE()      	                 (g_stOSDUserData.b2RGBtMode)
#define SET_DDCCI_RGB_MODE(x)		                 (g_stOSDUserData.b2RGBtMode = (x))

#define GET_DDCCI_RGB_LIGHT_MODE()      	         (g_stOSDUserData.b3RGBLightMode)
#define SET_DDCCI_RGB_LIGHT_MODE(x)		             (g_stOSDUserData.b3RGBLightMode = (x))

#endif
//--------------------------------------------------
// MACRO for OSD Postion
//--------------------------------------------------
#define GET_OSD_POSTION()                           (g_stOSDUserData.ucOsdPostion)
#define SET_OSD_POSTION(x)                          (g_stOSDUserData.ucOsdPostion = (x))

//--------------------------------------------------
// MACRO for Local Enhancement Window Zoom
//--------------------------------------------------
#define GET_OSD_LOCALENHANCEMENT_WINDOW_ZOOM()      (g_stOSDUserData.usLocalEnhancementWindowZoom)
#define SET_OSD_LOCALENHANCEMENT_WINDOW_ZOOM(x)     (g_stOSDUserData.usLocalEnhancementWindowZoom = (x))

//--------------------------------------------------
// Macro of Aspect Origin Ratio
//--------------------------------------------------
#define GET_OSD_ASPECT_ORIGIN_RATIO()               (g_stOSDUserData.ucAspectOriginRatio)
#define SET_OSD_ASPECT_ORIGIN_RATIO(x)              (g_stOSDUserData.ucAspectOriginRatio = (x))

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE()                       (g_stOSDUserData.b4ColorTempType)
#define SET_COLOR_TEMP_TYPE(x)                      (g_stOSDUserData.b4ColorTempType = (x))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_R()                (g_stColorProcData.usColorTempR >> 4)
#define SET_COLOR_TEMP_TYPE_USER_R(x)               (g_stColorProcData.usColorTempR = ((x) << 4))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_G()                (g_stColorProcData.usColorTempG >> 4)
#define SET_COLOR_TEMP_TYPE_USER_G(x)               (g_stColorProcData.usColorTempG = ((x) << 4))
//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_B()                (g_stColorProcData.usColorTempB >> 4)
#define SET_COLOR_TEMP_TYPE_USER_B(x)               (g_stColorProcData.usColorTempB = ((x) << 4))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_ASPECT_RATIO_TYPE()                 (g_stOSDUserData.b3AspectRatio)
#define SET_OSD_ASPECT_RATIO_TYPE(x)                (g_stOSDUserData.b3AspectRatio = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_VGA_COLOR_FORMAT_STATUS()               (g_stOSDUserData.b3VGARGBYUV)
#define SET_VGA_COLOR_FORMAT_STATUS(x)              (g_stOSDUserData.b3VGARGBYUV = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_DVI_COLOR_FORMAT_STATUS()               (g_stOSDUserData.b3DVIRGBYUV)
#define SET_DVI_COLOR_FORMAT_STATUS(x)              (g_stOSDUserData.b3DVIRGBYUV = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_DDCCI_STATUS()                      (g_stOSDUserData.b1DDCCIStatus)
#define SET_OSD_DDCCI_STATUS(x)                     (g_stOSDUserData.b1DDCCIStatus = (x))

//--------------------------------------------------
// MACRO for Ultra Vivid Status
//--------------------------------------------------
#define GET_OSD_ULTRA_VIVID_STATUS()                (g_stOSDUserData.b2UltraVividStatus)
#define SET_OSD_ULTRA_VIVID_STATUS(x)               (g_stOSDUserData.b2UltraVividStatus = (x))

//--------------------------------------------------
// MACRO for Sharpness
//--------------------------------------------------
#define GET_OSD_SHARPNESS()                         (g_stOSDUserData.b3Sharpness)
#define SET_OSD_SHARPNESS(x)                        (g_stOSDUserData.b3Sharpness = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_TRANSPARENCY_STATUS()               (g_stOSDUserData.ucTransparency)
#define SET_OSD_TRANSPARENCY_STATUS(x)              (g_stOSDUserData.ucTransparency = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_LANGUAGE()                          (g_stOSDUserData.b4Language)
#define SET_OSD_LANGUAGE(x)                         (g_stOSDUserData.b4Language = (x))

//--------------------------------------------------
// MACRO for OsdTimeout
//--------------------------------------------------
#define GET_OSD_TIME_OUT()                          (g_stOSDUserData.ucOsdTimeout)
#define SET_OSD_TIME_OUT(x)                         (g_stOSDUserData.ucOsdTimeout = (x))

//--------------------------------------------------
// MACRO for OsdHPos
//--------------------------------------------------
#define GET_OSD_HPOS()                              (g_stOSDUserData.ucOsdHPos)
#define SET_OSD_HPOS(x)                             (g_stOSDUserData.ucOsdHPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_VPOS()                              (g_stOSDUserData.ucOsdVPos)
#define SET_OSD_VPOS(x)                             (g_stOSDUserData.ucOsdVPos = (x))

//--------------------------------------------------
// MACRO for Gamma 
//--------------------------------------------------
#define GET_OSD_GAMMA()                             (g_stOSDUserData.b5Gamma)
#define SET_OSD_GAMMA(x)                            (g_stOSDUserData.b5Gamma = (x))

//--------------------------------------------------
// MACRO for OD Status
//--------------------------------------------------
#define GET_OSD_OD_STATUS()                         (g_stOSDUserData.b1ODStatus)
#define SET_OSD_OD_STATUS(x)                        (g_stOSDUserData.b1ODStatus = (x))

//--------------------------------------------------
// MACRO for OD Gain
//--------------------------------------------------
#define GET_OSD_OD_GAIN()                           (g_stOSDUserData.ucODGain)
#define SET_OSD_OD_GAIN(x)                          (g_stOSDUserData.ucODGain = (x))

//--------------------------------------------------
// MACRO for Color Effect
//--------------------------------------------------
#define GET_OSD_COLOR_EFFECT()                      (g_stOSDUserData.b4ColorEffect)
#define SET_OSD_COLOR_EFFECT(x)                     (g_stOSDUserData.b4ColorEffect = (x))

//--------------------------------------------------
// MACRO for DCRStatus
//--------------------------------------------------
#define GET_OSD_DCR_STATUS()                        (g_stOSDUserData.b1OsdDcrStatus)
#define SET_OSD_DCR_STATUS(x)                       (g_stOSDUserData.b1OsdDcrStatus = (x))

#define GET_OSD_RS232_STATUS()                          (g_stOSDUserData.b1RS232Status)
#define SET_OSD_RS232_STATUS(x)                         (g_stOSDUserData.b1RS232Status = (x))
//--------------------------------------------------
// MACRO for FreeSync Status
//--------------------------------------------------
#define GET_OSD_FREE_SYNC_STATUS()                  (g_stOSDUserData.b1FreeSyncStatus)
#define SET_OSD_FREE_SYNC_STATUS(x)                 (g_stOSDUserData.b1FreeSyncStatus = (x))

//--------------------------------------------------
// MACRO for Clone Mode
//--------------------------------------------------
#define GET_OSD_CLONE_MODE()                        (g_stOSDUserData.b1CloneMode)
#define SET_OSD_CLONE_MODE(x)                       (g_stOSDUserData.b1CloneMode = (x))

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR Mode
//--------------------------------------------------
#define GET_OSD_HDR_MODE()                          (g_stOSDUserData.ucHdrMode)
#define SET_OSD_HDR_MODE(x)                         (g_stOSDUserData.ucHdrMode = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_DARK_ENHANCE_STATUS()               (g_stOSDUserData.b1DarkEnhanceStatus)
#define SET_OSD_DARK_ENHANCE_STATUS(x)              (g_stOSDUserData.b1DarkEnhanceStatus = (x))

//--------------------------------------------------
// MACRO for HDR Sharpness
//--------------------------------------------------
#define GET_OSD_HDR_SHARPNESS()                     (g_stOSDUserData.b1HdrSharpnesse)
#define SET_OSD_HDR_SHARPNESS(x)                    (g_stOSDUserData.b1HdrSharpnesse = (x))

//--------------------------------------------------
// MACRO for HDR Contrast
//--------------------------------------------------
#define GET_OSD_HDR_CONTRAST()                      (g_stOSDUserData.ucHdrContrast)
#define SET_OSD_HDR_CONTRAST(x)                     (g_stOSDUserData.ucHdrContrast = (x))

#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR ColorEnhance
//--------------------------------------------------
#define GET_OSD_HDR_COLOR_ENHANCE()                 (g_stOSDUserData.ucHdrColorEnhance)
#define SET_OSD_HDR_COLOR_ENHANCE(x)                (g_stOSDUserData.ucHdrColorEnhance = (x))
#endif
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR LightEnhance
//--------------------------------------------------
#define GET_OSD_HDR_LIGHT_ENHANCE()                 (g_stOSDUserData.ucHdrLightEnhance)
#define SET_OSD_HDR_LIGHT_ENHANCE(x)                (g_stOSDUserData.ucHdrLightEnhance = (x))
#endif
#endif

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for Local Dimming
//--------------------------------------------------
#define GET_OSD_LOCAL_DIMMING()                     (g_stOSDUserData.b1HdrLocalDimming)
#define SET_OSD_LOCAL_DIMMING(x)                    (g_stOSDUserData.b1HdrLocalDimming = (x))

//--------------------------------------------------
// MACRO for Local Dimming Smooth Backlight adjust
//--------------------------------------------------
#define GET_OSD_LD_ADJ()                            (g_stOSDUserData.ucHdrLocalDimmingAdj)
#define SET_OSD_LD_ADJ(x)                           (g_stOSDUserData.ucHdrLocalDimmingAdj = (x))
#endif

#if (_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for SDR to HDR
//--------------------------------------------------
#define GET_OSD_SDR_TO_HDR()                        (g_stOSDUserData.b1Sdr2HdrStatus)
#define SET_OSD_SDR_TO_HDR(x)                       (g_stOSDUserData.b1Sdr2HdrStatus = (x))
#endif
//--------------------------------------------------
// MACRO for Volume Mute
//--------------------------------------------------
#define GET_OSD_VOLUME_MUTE()                       (g_stOSDUserData.b1VolumeMute)
#define SET_OSD_VOLUME_MUTE(x)                      (g_stOSDUserData.b1VolumeMute = (x))

//--------------------------------------------------
// MACRO for Volume
//--------------------------------------------------
#define GET_OSD_VOLUME()                            (g_stOSDUserData.ucVolume)
#define SET_OSD_VOLUME(x)                           (g_stOSDUserData.ucVolume = (x))

//--------------------------------------------------
// MACRO for Audio Stand a long
//--------------------------------------------------
#define GET_OSD_AUDIO_STAND_ALONE()                 (g_stOSDUserData.b1AudioStandAloneStatus)
#define SET_OSD_AUDIO_STAND_ALONE(x)                (g_stOSDUserData.b1AudioStandAloneStatus = (x))

//--------------------------------------------------
// MACRO for Audio Source
//--------------------------------------------------
#define GET_OSD_AUDIO_SOURCE()                      (g_stOSDUserData.b1AudioSourceStatus)
#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOSDUserData.b1AudioSourceStatus = (x))

//--------------------------------------------------
// MACRO for Hue
//--------------------------------------------------
#define GET_OSD_HUE()                               (g_stOSDUserData.ucHue)
#define SET_OSD_HUE(x)                              (g_stOSDUserData.ucHue = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_SATURATION()                        (g_stOSDUserData.ucSaturation)
#define SET_OSD_SATURATION(x)                       (g_stOSDUserData.ucSaturation = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_OVERSCAN_STATUS()                   (g_stOSDUserData.b1OverScan)
#define SET_OSD_OVERSCAN_STATUS(x)                  (g_stOSDUserData.b1OverScan = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_HLWIN_TYPE()                        (g_stOSDUserData.ucHLWinType)
#define SET_OSD_HLWIN_TYPE(x)                       (g_stOSDUserData.ucHLWinType = (x))

//--------------------------------------------------
// MACRO for OSD 3D
//--------------------------------------------------
#define GET_OSD_3DOSD_STATUS()                      (g_stOSDUserData.b1Osd3DOSD)
#define SET_OSD_3DOSD_STATUS(x)                     (g_stOSDUserData.b1Osd3DOSD = (x))

//--------------------------------------------------
// MACRO for 3D Status
//--------------------------------------------------
#define GET_OSD_3D_STATUS()                         (g_stOSDUserData.b23DStatus)
#define SET_OSD_3D_STATUS(x)                        (g_stOSDUserData.b23DStatus = (x))

//--------------------------------------------------
// MACRO for 3D LR Status
//--------------------------------------------------
#define GET_OSD_3D_LR_STATUS()                      (g_stOSDUserData.b13DLRStatus)
#define SET_OSD_3D_LR_STATUS(x)                     (g_stOSDUserData.b13DLRStatus = (x))

//--------------------------------------------------
// MACRO for 3D Format Status
//--------------------------------------------------
#define GET_OSD_3D_FORMAT_STATUS()                  (g_stOSDUserData.b23DFormatStatus)
#define SET_OSD_3D_FORMAT_STATUS(x)                 (g_stOSDUserData.b23DFormatStatus = (x))

//--------------------------------------------------
// MACRO for 3D EFFECT
//--------------------------------------------------
#define GET_OSD_3D_EFFECT()                         (g_stOSDUserData.uc3DEffect)
#define SET_OSD_3D_EFFECT(x)                        (g_stOSDUserData.uc3DEffect = (x))

//--------------------------------------------------
// MACRO for 3D 3DTO2D
//--------------------------------------------------
#define GET_OSD_3D_3DTO2D()                         (g_stOSDUserData.b13D3DTO2DStatus)
#define SET_OSD_3D_3DTO2D(x)                        (g_stOSDUserData.b13D3DTO2DStatus = (x))

//--------------------------------------------------
// MACRO for 3D Convergence
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE()                    (g_stOSDUserData.uc3DConvergence)
#define SET_OSD_3D_CONVERGENCE(x)                   (g_stOSDUserData.uc3DConvergence = (x))

//--------------------------------------------------
// MACRO for 3D Convergence Mode
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE_MODE()               (g_stOSDUserData.b33DConvergenceMode)
#define SET_OSD_3D_CONVERGENCE_MODE(x)              (g_stOSDUserData.b33DConvergenceMode = (x))

//--------------------------------------------------
// MACRO for Auto-Color Type
//--------------------------------------------------
#define _AUTO_COLOR_TYPE_INTERNAL                   0
#define _AUTO_COLOR_TYPE_EXTERNAL                   1

#define GET_OSD_FACTORY_AUTO_COLOR_TYPE()           (g_stOSDUserData.b1FactoryAutoColorType)
#define SET_OSD_FACTORY_AUTO_COLOR_TYPE(x)          (g_stOSDUserData.b1FactoryAutoColorType = (x))

//--------------------------------------------------
// MACRO for PCM Status
//--------------------------------------------------
#define GET_OSD_PCM_STATUS()                        (g_stOSDUserData.b3PCMStatus)
#define SET_OSD_PCM_STATUS(x)                       (g_stOSDUserData.b3PCMStatus = (x))

//--------------------------------------------------
// MACRO for OSD PCM InputGamma
//--------------------------------------------------
#define GET_OSD_PCM_INPUTGAMMA()                    (g_stOSDUserData.b4PCMInputGamma)
#define SET_OSD_PCM_INPUTGAMMA(x)                   (g_stOSDUserData.b4PCMInputGamma = (x))

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for DP Lane Count switch
//--------------------------------------------------
#define GET_OSD_D0_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D0TypeCU3Mode)
#define SET_OSD_D0_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D0TypeCU3Mode = (x))

#define GET_OSD_D1_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D1TypeCU3Mode)
#define SET_OSD_D1_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D1TypeCU3Mode = (x))

#define GET_OSD_D2_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D2TypeCU3Mode)
#define SET_OSD_D2_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D2TypeCU3Mode = (x))

#define GET_OSD_D6_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D6TypeCU3Mode)
#define SET_OSD_D6_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D6TypeCU3Mode = (x))

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for Type-C Pin Assignment E Support Switch
//--------------------------------------------------
#define GET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D0TypeCPinAssignmentESupportSelect)
#define SET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D0TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D1TypeCPinAssignmentESupportSelect)
#define SET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D1TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D2TypeCPinAssignmentESupportSelect)
#define SET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D2TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D6TypeCPinAssignmentESupportSelect)
#define SET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D6TypeCPinAssignmentESupportSelect = (x))
#endif
#endif

//--------------------------------------------------
// MACRO for HDMI version
//--------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#define GET_OSD_D0_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD0PortVersion)
#define SET_OSD_D0_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD0PortVersion = (x))

#define GET_OSD_D1_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD1PortVersion)
#define SET_OSD_D1_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD1PortVersion = (x))

#define GET_OSD_D2_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD2PortVersion)
#define SET_OSD_D2_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD2PortVersion = (x))

#define GET_OSD_D3_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD3PortVersion)
#define SET_OSD_D3_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD3PortVersion = (x))

#define GET_OSD_D4_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD4PortVersion)
#define SET_OSD_D4_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD4PortVersion = (x))

#define GET_OSD_D5_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD5PortVersion)
#define SET_OSD_D5_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD5PortVersion = (x))
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Hub UFP Switch marco
//--------------------------------------------------
#define GET_OSD_USB3_RETIMER_PD_WAKEUP()            (g_stOSDUserData.b1OsdUsb3RetimerPDWakeUp)
#define SET_OSD_USB3_RETIMER_PD_WAKEUP(x)           (g_stOSDUserData.b1OsdUsb3RetimerPDWakeUp = (x))
#define GET_OSD_USB3_RETIMER_PS_WAKEUP()            (g_stOSDUserData.b1OsdUsb3RetimerPSWakeUp)
#define SET_OSD_USB3_RETIMER_PS_WAKEUP(x)           (g_stOSDUserData.b1OsdUsb3RetimerPSWakeUp = (x))

//--------------------------------------------------
// Hub UFP Switch marco
//--------------------------------------------------
#define GET_USER_USB_HUB_UFP_SWITCH()               (g_stOSDUserData.enumHubInputPortSwitchbyUser)
#define SET_USER_USB_HUB_UFP_SWITCH(x)              (g_stOSDUserData.enumHubInputPortSwitchbyUser = (x))
#endif

#if 1//(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for FPGA Color Gamma Type 
//--------------------------------------------------
#define GET_OSD_FPGA_COLOR_GAMMA()                  (g_stOSDUserData.b3ColorGamma)
#define SET_OSD_FPGA_COLOR_GAMMA( x)                (g_stOSDUserData.b3ColorGamma = (x))

//--------------------------------------------------
// MACRO for FPGA Gray Gamma Type
//--------------------------------------------------
#define GET_OSD_FPGA_GRAY_GAMMA()                   (g_stOSDUserData.b3GrayGamma)
#define SET_OSD_FPGA_GRAY_GAMMA( x)                 (g_stOSDUserData.b3GrayGamma = (x))
#endif

//--------------------------------------------------
// MACRO for Dicom ALC 
//--------------------------------------------------
#define GET_OSD_DICOMALC()                          (g_stOSDUserData.b3DicomALC)
#define SET_OSD_DICOMALC(x)                         (g_stOSDUserData.b3DicomALC = (x))

//--------------------------------------------------
// Macro of User Base Color Temperature
//--------------------------------------------------
#define GET_USER_BASE_COLOR_TEMP_TYPE()             (g_stOSDUserData.b3UserBaseColorTempType)
#define SET_USER_BASE_COLOR_TEMP_TYPE(x)            (g_stOSDUserData.b3UserBaseColorTempType = (x))

//--------------------------------------------------
// MACRO for LUT User Status
//--------------------------------------------------
#define GET_OSD_LUT_USER_TYPE()        				(g_stUserCalibLutData.ucLutUserType)
#define SET_OSD_LUT_USER_TYPE(x)       				(g_stUserCalibLutData.ucLutUserType = (x))

#define GET_OSD_LUT_USER_L_MAX()        			(g_stUserCalibLutData.usLutUserLMax)
#define SET_OSD_LUT_USER_L_MAX(x)       			(g_stUserCalibLutData.usLutUserLMax = (x))

#define GET_OSD_LUT_USER_L_MIN()        			(g_stUserCalibLutData.ucLutUserLMin)
#define SET_OSD_LUT_USER_L_MIN(x)       			(g_stUserCalibLutData.ucLutUserLMin = (x))

#define GET_OSD_LUT_USER_LAMB()        				(g_stUserCalibLutData.ucLutUserLAMB)
#define SET_OSD_LUT_USER_LAMB(x)       				(g_stUserCalibLutData.ucLutUserLAMB = (x))

#define GET_OSD_LUT_USER_VALUE()        			(g_stUserCalibLutData.ucLutUserValue)
#define SET_OSD_LUT_USER_VALUE(x)       			(g_stUserCalibLutData.ucLutUserValue = (x))

#define GET_OSD_LUT_USER_LUT_OFFSET()        		(g_stUserCalibLutData.usLutUserLutOffset)
#define SET_OSD_LUT_USER_LUT_OFFSET(x)       		(g_stUserCalibLutData.usLutUserLutOffset = (x))

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_NVRAM_DOUBLE_SIZE()                 (g_stOSDUserData.b1OsdDoubleSize)
#define SET_OSD_NVRAM_DOUBLE_SIZE(x)                (g_stOSDUserData.b1OsdDoubleSize = (x))

//==========================================================================================================
// Macro of NVRam Panel Time Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_PANEL_TIME_MIN()                        (g_stPanelTimeData.ucMin)
#define SET_PANEL_TIME_MIN(x)                       (g_stPanelTimeData.ucMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_PANEL_TIME_HOUR()                       (g_stPanelTimeData.usHour)
#define SET_PANEL_TIME_HOUR(x)                      (g_stPanelTimeData.usHour = (x))

//--------------------------------------------------
// MACRO for System Run Time Min
//--------------------------------------------------
#define GET_SYSTEM_RUN_TIME_MIN()                   (g_stPanelTimeData.ucSystemRunMin)
#define SET_SYSTEM_RUN_TIME_MIN(x)                  (g_stPanelTimeData.ucSystemRunMin = (x))

//--------------------------------------------------
// MACRO for System Run Hour
//--------------------------------------------------
#define GET_SYSTEM_RUN_TIME_HOUR()                  (g_stPanelTimeData.usSystemRunHour)
#define SET_SYSTEM_RUN_TIME_HOUR(x)                 (g_stPanelTimeData.usSystemRunHour = (x))

//--------------------------------------------------
// MACRO for Panel Run Time Min
//--------------------------------------------------
#define GET_PANEL_RUN_TIME_MIN()                    (g_stPanelTimeData.ucPanelRunMin)
#define SET_PANEL_RUN_TIME_MIN(x)                   (g_stPanelTimeData.ucPanelRunMin = (x))

//--------------------------------------------------
// MACRO for Panel Run Time Hour
//--------------------------------------------------
#define GET_PANEL_RUN_TIME_HOUR()                   (g_stPanelTimeData.usPanelRunHour)
#define SET_PANEL_RUN_TIME_HOUR(x)                  (g_stPanelTimeData.usPanelRunHour = (x))

//--------------------------------------------------
// MACRO for System Run Time Overflow
//--------------------------------------------------
#define GET_SYSTEM_RUN_TIME_OVERFLOW()              (g_stPanelTimeData.b4SystemRunOverflow)
#define SET_SYSTEM_RUN_TIME_OVERFLOW(x)             (g_stPanelTimeData.b4SystemRunOverflow = (x))

//--------------------------------------------------
// MACRO for Panel Run Time Overflow
//--------------------------------------------------
#define GET_PANEL_RUN_TIME_OVERFLOW()               (g_stPanelTimeData.b4PanelRunOverflow)
#define SET_PANEL_RUN_TIME_OVERFLOW(x)              (g_stPanelTimeData.b4PanelRunOverflow = (x))

//--------------------------------------------------
// MACRO for backlight min&cen&max backup Case
//--------------------------------------------------
#define GET_FORCE_BACKUP_STATUS()                   (g_bForceBackupStatus)
#define SET_FORCE_BACKUP_STATUS(x)                  (g_bForceBackupStatus = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity Calibration Data Case
//--------------------------------------------------
#define GET_PANEL_UNIFORMITY_CALIBRATION_DATA()     (g_ucPanelUniformityCalibrationData)
#define SET_PANEL_UNIFORMITY_CALIBRATION_DATA(x)    (g_ucPanelUniformityCalibrationData = (x))

//--------------------------------------------------
// MACRO for Embedded calibration Case
//--------------------------------------------------
#define GET_DDCCI_MCU_TYPE()						(g_ucScalerSendMcuData)
#define SET_DDCCI_MCU_TYPE(x)						(g_ucScalerSendMcuData = x)

#if (_PRODUCT_ID_SEL == RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)
//--------------------------------------------------
// MACRO for Embedded calibration Case
//--------------------------------------------------
#define GET_UART_MCU_TYPE()						    (g_ucScalerSendMcuUartID)
#define SET_UART_MCU_TYPE(x)						(g_ucScalerSendMcuUartID = x)
#endif
//--------------------------------------------------
// MACRO for Factory Power Saving Case
//--------------------------------------------------
#define GET_FORCE_POW_SAV_STATUS()                  (g_bForcePowSavStatus)
#define SET_FORCE_POW_SAV_STATUS(x)                 (g_bForcePowSavStatus = (x))

#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
//--------------------------------------------------
// MACRO for Force Switch Source Case
//--------------------------------------------------
#define GET_FORCE_SWITCH_SOURCE_STATUS()            (g_bForceSwitchSourceStatus)
#define SET_FORCE_SWITCH_SOURCE_STATUS(x)           (g_bForceSwitchSourceStatus = (x))
#endif

//--------------------------------------------------
// Definitions of OSD Number ROW COL
//--------------------------------------------------
#define _OSD_NUMBER_0_ROW                           2
#define _OSD_NUMBER_0_COL                           24

#define _OSD_NUMBER_1_ROW                           15
#define _OSD_NUMBER_1_COL                           21

#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
#define _OSD_NUMBER_GRAY_COLOR                      COLOR(_CP_GRAY, _CP_BG)

//--------------------------------------------------
// Definitions of OSD
//--------------------------------------------------
#define _PFONT_PAGE_0                               0
#define _PFONT_PAGE_1                               1
#define _PFONT_PAGE_2                               2
#define _PFONT_PAGE_ITEM_1                          3
#define _PFONT_PAGE_ITEM_2                          4
#define _PFONT_PAGE_ITEM_3                          5
#define _PFONT_PAGE_ITEM_4                          6
#define _PFONT_PAGE_ITEM_5                          7
#define _PFONT_PAGE_ITEM_6                          8
#define _PFONT_PAGE_ITEM_7                          9

#define _OSD_PAGE_0_START                           0x00
#define _OSD_PAGE_0_END                             0x2F

#define _OSD_PAGE_1_START                           0x30
#define _OSD_PAGE_1_END                             0x8F

#define _OSD_PAGE_2_START                           0x90
#define _OSD_PAGE_2_END                             0xFC

#define _SUB_PAGE_ITEM_1                            (_OSD_PAGE_2_START)
#define _SUB_PAGE_ITEM_1_END                        (_SUB_PAGE_ITEM_1 + 0x11)
#define _SUB_PAGE_ITEM_2                            (_SUB_PAGE_ITEM_1_END)
#define _SUB_PAGE_ITEM_2_END                        (_SUB_PAGE_ITEM_1_END + 0x11)
#define _SUB_PAGE_ITEM_3                            (_SUB_PAGE_ITEM_2_END)
#define _SUB_PAGE_ITEM_3_END                        (_SUB_PAGE_ITEM_2_END + 0x11)
#define _SUB_PAGE_ITEM_4                            (_SUB_PAGE_ITEM_3_END)
#define _SUB_PAGE_ITEM_4_END                        (_SUB_PAGE_ITEM_3_END + 0x11)
#define _SUB_PAGE_ITEM_5                            (_SUB_PAGE_ITEM_4_END)
#define _SUB_PAGE_ITEM_5_END                        (_SUB_PAGE_ITEM_4_END + 0x11)
#define _SUB_PAGE_ITEM_6                            (_SUB_PAGE_ITEM_5_END)
#define _SUB_PAGE_ITEM_6_END                        (_SUB_PAGE_ITEM_5_END + 0x11)


#if(_SUB_PAGE_ITEM_6_END > _OSD_PAGE_2_END)
#warning "!!!Please increase the space _OSD_PAGE_2_END"
#endif

#define _UP                                         0
#define _DOWN                                       1

//--------------------------------------------------
// Definitions of OSD Window
//--------------------------------------------------
//=========== OSD Window Setting ======================//
//Blending type1:Only windows blending.
//Blending type2:All blending.
//Blending type3:Windows & Character background blending.
#define _WIN0                                       0
#define _WIN1                                       1
#define _WIN2                                       2
#define _WIN3                                       3
#define _WIN4                                       4
#define _WIN5                                       5
#define _WIN6                                       6
#define _WIN7                                       7
#define _WIN8                                       8
#define _WIN9                                       9
#define _WIN_ALL                                    0xFF

#define _WIN0_TRANS                                 (_BIT7 | 0)
#define _WIN1_TRANS                                 (_BIT7 | 1)
#define _WIN2_TRANS                                 (_BIT7 | 2)
#define _WIN3_TRANS                                 (_BIT7 | 3)
#define _WIN4_TRANS                                 (_BIT7 | 4)
#define _WIN5_TRANS                                 (_BIT7 | 5)
#define _WIN6_TRANS                                 (_BIT7 | 6)
#define _WIN7_TRANS                                 (_BIT7 | 7)

#define COLOR(fg, bg)                               ((fg) << 4 | (bg))
#define COLOR0(x)                                   (x)
#define COLOR1(x)                                   (x)
#define COLOR2(x)                                   (x)
#define COLOR3(x)                                   (x)

#define X_START(x)                                  (x)
#define Y_START(x)                                  (x)
#define X_END(x)                                    (x)
#define Y_END(x)                                    (x)

#define _BORDER0_1_PIXEL                            0
#define _BORDER0_2_PIXEL                            1
#define _BORDER0_3_PIXEL                            2
#define _BORDER0_4_PIXEL                            3
#define _BORDER0_5_PIXEL                            4
#define _BORDER0_6_PIXEL                            5
#define _BORDER0_7_PIXEL                            6
#define _BORDER0_8_PIXEL                            7

#define _BORDER1_1_PIXEL                            0x00
#define _BORDER1_2_PIXEL                            0x08
#define _BORDER1_3_PIXEL                            0x10
#define _BORDER1_4_PIXEL                            0x18
#define _BORDER1_5_PIXEL                            0x20
#define _BORDER1_6_PIXEL                            0x28
#define _BORDER1_7_PIXEL                            0x30
#define _BORDER1_8_PIXEL                            0x38

#define _BLEND_DISABLE                              0
#define _BLEND_ENABLE                               0x80
#define _GRADIENT_DISABLE                           0
#define _GRADIENT_ENABLE                            0x40
#define _GRADIENT_DIRECTION_H                       0
#define _GRADIENT_DIRECTION_V                       0x20
#define _BORDER_DISABLE                             0
#define _BORDER_ENABLE                              0x10

#define _1_LEVEL_RER_GRADIENT                       0x20
#define _2_LEVEL_RER_GRADIENT                       0x40
#define _3_LEVEL_RER_GRADIENT                       0x60
#define _4_LEVEL_RER_GRADIENT                       0x80
#define _5_LEVEL_RER_GRADIENT                       0xA0
#define _6_LEVEL_RER_GRADIENT                       0xC0
#define _7_LEVEL_RER_GRADIENT                       0xE0
#define _8_LEVEL_RER_GRADIENT                       0x00

#define _R_GRADIENT_DEC                             0x00
#define _R_GRADIENT_INC                             0x80
#define _G_GRADIENT_DEC                             0x00
#define _G_GRADIENT_INC                             0x40
#define _B_GRADIENT_DEC                             0x00
#define _B_GRADIENT_INC                             0x20

#define _GRADIENT_LEVEL_1                           0
#define _GRADIENT_LEVEL_2                           0x08
#define _GRADIENT_LEVEL_3                           0x10
#define _GRADIENT_LEVEL_4                           0x18

#define _R_GRADIENT_ENABLE                          0x04
#define _R_GRADIENT_DISABLE                         0x00
#define _G_GRADIENT_ENABLE                          0x02
#define _G_GRADIENT_DISABLE                         0x00
#define _B_GRADIENT_ENABLE                          0x01
#define _B_GRADIENT_DISABLE                         0x00

#define _SHADOW_1                                   0x00
#define _SHADOW_2                                   0x02
#define _SHADOW_3                                   0x04
#define _SHADOW_4                                   0x06
#define _3D_BUTTON_1                                0x08
#define _3D_BUTTON_2                                0x0A

#define _OSD_UNSELECT                               0
#define _OSD_SELECT                                 1
#define _OSD_REJECT                                 2
#define _OSD_ADJUST                                 3
#define _OSD_UNHIGHLIGHT                            4
#define _OSD_HIGHLIGHT                              5
#define _OSD_PRE_SELECT                             6
#define _OSD_SELECT_ADJUST                          7


//--------------------------------------------------
// Definitions of OSD Beacon
//--------------------------------------------------
#define _ST_NORMAL									1
#define _ST_SELECT									2
#define _ST_DISABLE									3
#define _ST_ADJUST									4
#define _ST_HIDDEN									5
#define _SLIDER_BEGIN								0x09
#define _SLIDER_BEGIN_BOTTOM						0x12
#define _NOT_SHOW									0xFF
#define _EN_DL_STATE_HIDDEN							0x00
#define _EN_DL_STATE_NORMAL							0x01
#define _EN_DL_STATE_DISABLE						0x02
#define _ITEM_NORMAL_COLOR                  		COLOR(_CP_GRAY_32, _SUB_WIN_COLOR)
#define _ITEM_SELECT_COLOR                  		COLOR(_CP_GRAY_32, _CP_BG)
#define _ITEM_ADJUST_COLOR                  		COLOR(_CP_WHITE, _CP_BG)
#define _ITEM_HIDDEN_COLOR                  		COLOR(_SUB_WIN_COLOR, _CP_BG)
#define _ITEM_DISABLE_COLOR                  		COLOR(_CP_GRAY_80, _SUB_WIN_COLOR)
#define _ITEM_DRAW_PAGE_COLOR						COLOR(_SUB_WIN_COLOR, _SUB_WIN_COLOR)
#define _OPT_STRING_NORMAL_COLOR					_MAIN_WIN_COLOR
#define _OPT_STRING_SELECT_COLOR					_CP_WHITE_250
#define _OPT_FRAME_DISABLE_COLOR					_SUB_WIN_COLOR		


#define _KEY_INFO_MENU                              0
#define _KEY_INFO_RIGHT                             1
#define _KEY_INFO_LEFT                              2
#define _KEY_INFO_EXIT                              3
#define _KEY_INFO_ENTER                             4
#define _KEY_INFO_BACK                              5
#define _KEY_INFO_ALL                               6   // exit, left, right, enter

//=========== OSD Font Icon Address ======================//
#define _1GLOBAL_START                              0x00                        // Global 49
#define _1DYNAMIC_START                             (_1GLOBAL_START + 50)       // Dynamic 0
#define _1DYNAMIC_ICON_START                        (_1DYNAMIC_START + 0)       // main menu icon (6 x 4 x 8) = 196
#define _2DYNAMIC_START                             0x00
#define _2BIT_ICON_OFFSET                           0xFF

#define _LOGO_START_ADDRESS                         0x00

//=============== 1Bit Icon ========================

typedef enum
{
    ___ = 0,
    _iKEY_SOURCE_00,
    _iKEY_SOURCE_01,

    _iKEY_ENTER_00,
    _iKEY_ENTER_01,

    _iKEY_MENU_00,
    _iKEY_MENU_01,

    _iKEY_GAMMA_00,
    _iKEY_GAMMA_01,

    _iKEY_AMB_00,
    _iKEY_AMB_01,

    _iKEY_LIGHTBOX_00,
    _iKEY_LIGHTBOX_01,

    _iKEY_EXIT_00,
    _iKEY_EXIT_01,

    _iKEY_LEFT2,
    
    _iKEY_RIGHT2,

    _iKEY_KVM_00,
    _iKEY_KVM_01,

    _iKEY_UP,

    _iKEY_DOWN,
      
    

    

    _iINDICATE,
}EnumOneBitGLOBAL;

// RTD LOGO
#if(_POWER_ON_LOGO_TYPE == _LOGO_MEDBOT)
// OSDComposer.exe tool generates data
#define _OSD_LOGOA_WIDTH                            756
#define _OSD_LOGOA_HEIGHT                           126

#define _OSD_LOGOB_WIDTH                            756
#define _OSD_LOGOB_HEIGHT                           126

#define _OSD_LOGO_2BIT_OFFSET                       13
#define _OSD_LOGO_4BIT_OFFSET                       0

#if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_3)
#define _OSD_LOGO_FONT_BASE_ADDRESS                 404
#else
#define _OSD_LOGO_FONT_BASE_ADDRESS                 405
#endif // End of #if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_3)

#define _OSD_LOGOA_ADDRESS_ROWCOMMAND               0
#define _OSD_LOGOA_ADDRESS_CHARCOMMAND              8

#elif(_POWER_ON_LOGO_TYPE == _LOGO_DBI)
// OSDComposer.exe tool generates data
#define _OSD_LOGOA_WIDTH                            252//596//1152
#define _OSD_LOGOA_HEIGHT                           1152//126//252

#define _OSD_LOGOB_WIDTH                            252
#define _OSD_LOGOB_HEIGHT                           1152

#define _OSD_LOGO_2BIT_OFFSET                       198
#define _OSD_LOGO_4BIT_OFFSET                       0

#if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_3)
#define _OSD_LOGO_FONT_BASE_ADDRESS                 729
#else
#define _OSD_LOGO_FONT_BASE_ADDRESS                 729
#endif // End of #if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_3)

#define _OSD_LOGOA_ADDRESS_ROWCOMMAND               0
#define _OSD_LOGOA_ADDRESS_CHARCOMMAND              65

#else

#define _OSD_LOGOA_WIDTH                            840
#define _OSD_LOGOA_HEIGHT                           180

#endif

#define _LOGO_WINDOW_SIZE_X                         839
#define _LOGO_WINDOW_SIZE_Y                         179

#define _Logo_0x00                                  0x00
#define _Logo_0x01                                  (_Logo_0x00 + 0x01)
#define _Logo_0x02                                  (_Logo_0x00 + 0x02)
#define _Logo_0x03                                  (_Logo_0x00 + 0x03)
#define _Logo_0x04                                  (_Logo_0x00 + 0x04)
#define _Logo_0x05                                  (_Logo_0x00 + 0x05)
#define _Logo_0x06                                  (_Logo_0x00 + 0x06)
#define _Logo_0x07                                  (_Logo_0x00 + 0x07)
#define _Logo_0x08                                  (_Logo_0x00 + 0x08)
#define _Logo_0x09                                  (_Logo_0x00 + 0x09)
#define _Logo_0x0a                                  (_Logo_0x00 + 0x0a)
#define _Logo_0x0b                                  (_Logo_0x00 + 0x0b)
#define _Logo_0x0c                                  (_Logo_0x00 + 0x0c)
#define _Logo_0x0d                                  (_Logo_0x00 + 0x0d)
#define _Logo_0x0e                                  (_Logo_0x00 + 0x0e)
#define _Logo_0x0f                                  (_Logo_0x00 + 0x0f)
#define _Logo_0x10                                  (_Logo_0x00 + 0x10)
#define _Logo_0x11                                  (_Logo_0x00 + 0x11)
#define _Logo_0x12                                  (_Logo_0x00 + 0x12)
#define _Logo_0x13                                  (_Logo_0x00 + 0x13)
#define _Logo_0x14                                  (_Logo_0x00 + 0x14)
#define _Logo_0x15                                  (_Logo_0x00 + 0x15)
#define _Logo_0x16                                  (_Logo_0x00 + 0x16)
#define _Logo_0x17                                  (_Logo_0x00 + 0x17)
#define _Logo_0x18                                  (_Logo_0x00 + 0x18)
#define _Logo_0x19                                  (_Logo_0x00 + 0x19)
#define _Logo_0x1a                                  (_Logo_0x00 + 0x1a)
#define _Logo_0x1b                                  (_Logo_0x00 + 0x1b)
#define _Logo_0x1c                                  (_Logo_0x00 + 0x1c)
#define _Logo_0x1d                                  (_Logo_0x00 + 0x1d)
#define _Logo_0x1e                                  (_Logo_0x00 + 0x1e)
#define _Logo_0x1f                                  (_Logo_0x00 + 0x1f)
#define _Logo_0x20                                  (_Logo_0x00 + 0x20)
#define _Logo_0x21                                  (_Logo_0x00 + 0x21)
#define _Logo_0x22                                  (_Logo_0x00 + 0x22)
#define _Logo_0x23                                  (_Logo_0x00 + 0x23)
#define _Logo_0x24                                  (_Logo_0x00 + 0x24)
#define _Logo_0x25                                  (_Logo_0x00 + 0x25)
#define _Logo_0x26                                  (_Logo_0x00 + 0x26)
#define _Logo_0x27                                  (_Logo_0x00 + 0x27)
#define _Logo_0x28                                  (_Logo_0x00 + 0x28)
#define _Logo_0x29                                  (_Logo_0x00 + 0x29)
#define _Logo_0x2a                                  (_Logo_0x00 + 0x2a)
#define _Logo_0x2b                                  (_Logo_0x00 + 0x2b)
#define _Logo_0x2c                                  (_Logo_0x00 + 0x2c)
#define _Logo_0x2d                                  (_Logo_0x00 + 0x2d)
#define _Logo_0x2e                                  (_Logo_0x00 + 0x2e)
#define _Logo_0x2f                                  (_Logo_0x00 + 0x2f)
#define _Logo_0x30                                  (_Logo_0x00 + 0x30)
#define _Logo_0x31                                  (_Logo_0x00 + 0x31)
#define _Logo_0x32                                  (_Logo_0x00 + 0x32)
#define _Logo_0x33                                  (_Logo_0x00 + 0x33)
#define _Logo_0x34                                  (_Logo_0x00 + 0x34)
#define _Logo_0x35                                  (_Logo_0x00 + 0x35)
#define _Logo_0x36                                  (_Logo_0x00 + 0x36)
#define _Logo_0x37                                  (_Logo_0x00 + 0x37)
#define _Logo_0x38                                  (_Logo_0x00 + 0x38)
#define _Logo_0x39                                  (_Logo_0x00 + 0x39)
#define _Logo_0x3a                                  (_Logo_0x00 + 0x3a)
#define _Logo_0x3b                                  (_Logo_0x00 + 0x3b)
#define _Logo_0x3c                                  (_Logo_0x00 + 0x3c)
#define _Logo_0x3d                                  (_Logo_0x00 + 0x3d)
#define _Logo_0x3e                                  (_Logo_0x00 + 0x3e)
#define _Logo_0x3f                                  (_Logo_0x00 + 0x3f)
#define _Logo_0x40                                  (_Logo_0x00 + 0x40)
#define _Logo_0x41                                  (_Logo_0x00 + 0x41)
#define _Logo_0x42                                  (_Logo_0x00 + 0x42)
#define _Logo_0x43                                  (_Logo_0x00 + 0x43)
#define _Logo_0x44                                  (_Logo_0x00 + 0x44)
#define _Logo_0x45                                  (_Logo_0x00 + 0x45)
#define _Logo_0x46                                  (_Logo_0x00 + 0x46)
#define _Logo_0x47                                  (_Logo_0x00 + 0x47)
#define _Logo_0x48                                  (_Logo_0x00 + 0x48)
#define _Logo_0x49                                  (_Logo_0x00 + 0x49)
#define _Logo_0x4a                                  (_Logo_0x00 + 0x4a)
#define _Logo_0x4b                                  (_Logo_0x00 + 0x4b)
#define _Logo_0x4c                                  (_Logo_0x00 + 0x4c)
#define _Logo_0x4d                                  (_Logo_0x00 + 0x4d)
#define _Logo_0x4e                                  (_Logo_0x00 + 0x4e)
#define _Logo_0x4f                                  (_Logo_0x00 + 0x4f)
#define _Logo_0x50_End                              (_Logo_0x00 + 0x50)

#define _Logo1_0x00                                 (_Logo_0x50_End + 0x00)
#define _Logo1_0x01                                 (_Logo1_0x00 + 0x01)
#define _Logo1_0x02                                 (_Logo1_0x00 + 0x02)
#define _Logo1_0x03                                 (_Logo1_0x00 + 0x03)
#define _Logo1_0x04                                 (_Logo1_0x00 + 0x04)
#define _Logo1_0x05                                 (_Logo1_0x00 + 0x05)
#define _Logo1_0x06                                 (_Logo1_0x00 + 0x06)
#define _Logo1_0x07                                 (_Logo1_0x00 + 0x07)
#define _Logo1_0x08                                 (_Logo1_0x00 + 0x08)
#define _Logo1_0x09                                 (_Logo1_0x00 + 0x09)
#define _Logo1_0x0a                                 (_Logo1_0x00 + 0x0a)
#define _Logo1_0x0b                                 (_Logo1_0x00 + 0x0b)
#define _Logo1_0x0c                                 (_Logo1_0x00 + 0x0c)
#define _Logo1_0x0d                                 (_Logo1_0x00 + 0x0d)
#define _Logo1_0x0e                                 (_Logo1_0x00 + 0x0e)
#define _Logo1_0x0f                                 (_Logo1_0x00 + 0x0f)
#define _Logo1_0x10                                 (_Logo1_0x00 + 0x10)
#define _Logo1_0x11                                 (_Logo1_0x00 + 0x11)
#define _Logo1_0x12                                 (_Logo1_0x00 + 0x12)
#define _Logo1_0x13                                 (_Logo1_0x00 + 0x13)
#define _Logo1_0x14                                 (_Logo1_0x00 + 0x14)
#define _Logo1_0x15                                 (_Logo1_0x00 + 0x15)
#define _Logo1_0x16                                 (_Logo1_0x00 + 0x16)
#define _Logo1_0x17                                 (_Logo1_0x00 + 0x17)
#define _Logo1_0x18                                 (_Logo1_0x00 + 0x18)
#define _Logo1_0x19                                 (_Logo1_0x00 + 0x19)
#define _Logo1_0x1a                                 (_Logo1_0x00 + 0x1a)
#define _Logo1_0x1b                                 (_Logo1_0x00 + 0x1b)
#define _Logo1_0x1c                                 (_Logo1_0x00 + 0x1c)
#define _Logo1_0x1d                                 (_Logo1_0x00 + 0x1d)
#define _Logo1_0x1e                                 (_Logo1_0x00 + 0x1e)
#define _Logo1_0x1f                                 (_Logo1_0x00 + 0x1f)
#define _Logo1_0x20                                 (_Logo1_0x00 + 0x20)
#define _Logo1_0x21                                 (_Logo1_0x00 + 0x21)
#define _Logo1_0x22                                 (_Logo1_0x00 + 0x22)
#define _Logo1_0x23                                 (_Logo1_0x00 + 0x23)
#define _Logo1_0x24                                 (_Logo1_0x00 + 0x24)
#define _Logo1_0x25                                 (_Logo1_0x00 + 0x25)
#define _Logo1_0x26                                 (_Logo1_0x00 + 0x26)
#define _Logo1_0x27                                 (_Logo1_0x00 + 0x27)
#define _Logo1_0x28                                 (_Logo1_0x00 + 0x28)
#define _Logo1_0x29                                 (_Logo1_0x00 + 0x29)
#define _Logo1_0x2a                                 (_Logo1_0x00 + 0x2a)
#define _Logo1_0x2b                                 (_Logo1_0x00 + 0x2b)
#define _Logo1_0x2c                                 (_Logo1_0x00 + 0x2c)
#define _Logo1_0x2d                                 (_Logo1_0x00 + 0x2d)
#define _Logo1_0x2e                                 (_Logo1_0x00 + 0x2e)
#define _Logo1_0x2f                                 (_Logo1_0x00 + 0x2f)
#define _Logo1_0x30                                 (_Logo1_0x00 + 0x30)
#define _Logo1_0x31                                 (_Logo1_0x00 + 0x31)
#define _Logo1_0x32                                 (_Logo1_0x00 + 0x32)
#define _Logo1_0x33                                 (_Logo1_0x00 + 0x33)
#define _Logo1_0x34                                 (_Logo1_0x00 + 0x34)
#define _Logo1_0x35                                 (_Logo1_0x00 + 0x35)
#define _Logo1_0x36                                 (_Logo1_0x00 + 0x36)
#define _Logo1_0x37                                 (_Logo1_0x00 + 0x37)
#define _Logo1_0x38                                 (_Logo1_0x00 + 0x38)
#define _Logo1_0x39                                 (_Logo1_0x00 + 0x39)
#define _Logo1_0x3a                                 (_Logo1_0x00 + 0x3a)
#define _Logo1_0x3b                                 (_Logo1_0x00 + 0x3b)
#define _Logo1_0x3c                                 (_Logo1_0x00 + 0x3c)
#define _Logo1_0x3d                                 (_Logo1_0x00 + 0x3d)
#define _Logo1_0x3e                                 (_Logo1_0x00 + 0x3e)
#define _Logo1_0x3f                                 (_Logo1_0x00 + 0x3f)
#define _Logo1_0x40                                 (_Logo1_0x00 + 0x40)
#define _Logo1_0x41                                 (_Logo1_0x00 + 0x41)
#define _Logo1_0x42                                 (_Logo1_0x00 + 0x42)
#define _Logo1_0x43                                 (_Logo1_0x00 + 0x43)
#define _Logo1_0x44                                 (_Logo1_0x00 + 0x44)
#define _Logo1_0x45                                 (_Logo1_0x00 + 0x45)
#define _Logo1_0x46                                 (_Logo1_0x00 + 0x46)

//=============== 2Bit Icon ========================



//---------------------------------------------------------------------
// Definitions of OSD Show Number Function Used by OsdDisplayShowNumber()
//---------------------------------------------------------------------
#define _ALIGN_LEFT                                 (0)
#define _ALIGN_RIGHT                                (1)

#define _FORCE_SHOW_NUMBER_OFF                      (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                       (1 << 1)

#define _SHOW_1                                     (0 << 4)
#define _SHOW_2                                     (1 << 4)
#define _SHOW_3                                     (2 << 4)
#define _SHOW_4                                     (3 << 4)
#define _SHOW_5                                     (4 << 4)
#define _SHOW_6                                     (5 << 4)

//------------------------------------------------------
// Definitions of OSD Slider Function Used by OsdDisplaySlider()
//------------------------------------------------------
#define _SLIDER_RESOLUTION                          (10)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define _PALETTE_INDEX0                             0   // 0 ~ 15
#define _PALETTE_INDEX1                             1   // 16 ~ 31
#define _PALETTE_INDEX2                             2   // 32 ~ 47
#define _PALETTE_INDEX3                             3   // 48 ~ 63

// OSD Position
#define _POS_DIRECT                                 0
#define _POS_PERCENT                                1

//--------------------------------------------------
// Definitions of OSD MAIN MENU
//--------------------------------------------------
#if   ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
#define _OSD_MAIN_MENU_WIDTH                        45//44
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
#define _OSD_MAIN_MENU_WIDTH                        55//44
#else
#define _OSD_MAIN_MENU_WIDTH                        44
#endif
#define _OSD_MAIN_MENU_HEIGHT                       20

//--------------------------------------------------
// Definitions of OSD MSG MENU
//--------------------------------------------------
#define _OSD_MSG_MENU_WIDTH                      	36
#define _OSD_MSG_MENU_HEIGHT                     	8

#if ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
#define _OSD_HOTKEY_MENU_WIDTH                      45//32
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
#define _OSD_HOTKEY_MENU_WIDTH                      56//32
#else
#define _OSD_HOTKEY_MENU_WIDTH                      45//32
#endif
#define _OSD_HOTKEY_MENU_HEIGHT                     8

#define _OSD_MESSAGE_STRING_LENGHT                  23

#define _OSD_HOTKEY_SOURCE_MENU_WIDTH               46
#define _OSD_HOTKEY_SOURCE_MENU_HEIGHT              30

#define _OSD_2PLR_INFO_MENU_WIDTH                   48
#define _OSD_2PLR_INFO_MENU_HEIGHT                  8

#define _OSD_2PTB_INFO_MENU_WIDTH                   24
#define _OSD_2PTB_INFO_MENU_HEIGHT                  16

#define _OSD_2PPIP_INFO_MENU_WIDTH                  48
#define _OSD_2PPIP_INFO_MENU_HEIGHT                 16

#define _OSD_4P_INFO_MENU_WIDTH                     48
#define _OSD_4P_INFO_MENU_HEIGHT                    16
#if((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
#define _OSD_CALI_INFO_WIDTH                        50//36//32
#define _OSD_CALI_INFO_HEIGHT                       40//24
#elif((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
#define _OSD_CALI_INFO_WIDTH                        36//32
#define _OSD_CALI_INFO_HEIGHT                       24
#else
#define _OSD_CALI_INFO_WIDTH                        36//32
#define _OSD_CALI_INFO_HEIGHT                       24
#endif
//******************************************************************************
#define _WIN_TITLE_ROW_START_PIXEL					0//6
#define _WIN_TITLE_COL_START_PIXEL					0//7
#define _WIN_TITLE_HEIGHT							3

#define _WIN_MAIN_ROW_START_PIXEL					(_WIN_TITLE_HEIGHT*18 + _WIN_TITLE_ROW_START_PIXEL*18)
#define _WIN_MAIN_COL_START_PIXEL					0*12
#define _WIN_MAIN_WIDTH								12//19 //16
#define _WIN_MAIN_HEIGHT							(_OSD_MAIN_MENU_HEIGHT - _WIN_TITLE_HEIGHT - _WIN_INFO_HEIGHT)	

#define _WIN_MAIN_INFO_ROW_START_PIXEL				(_WIN_TITLE_HEIGHT*18 + _WIN_TITLE_ROW_START_PIXEL*18 + _WIN_MAIN_HEIGHT*18)
#define _WIN_MAIN_INFO_COL_START_PIXEL				0*12
#define _WIN_INFO_HEIGHT							3///4

#define _WIN_SUB_ROW_START_PIXEL					(_WIN_TITLE_HEIGHT*18 + _WIN_TITLE_ROW_START_PIXEL)
#define _WIN_SUB_COL_START_PIXEL					(_WIN_MAIN_COL_START_PIXEL+_WIN_MAIN_WIDTH*12)
#define _WIN_SUB_WIN_BORDER_WIDTH					0
#define _WIN_SUB_WIN_BORDER_HEIGHT					0

#define _OSD_MAIN_ITEM_ROW_START					4//7
#define _OSD_MAIN_ITEM_COL_START					1
#define _OSD_MAIN_ITEM_SELECT_WIDTH				    10


#define _OSD_ROW_STEP                               2
#define _OSD_ROW_NUM                                7


#define _WIN_MAINITEM_WIDTH							(_WIN_MAIN_WIDTH-1)//15
#define _WIN_MAINITEM_SELECT						(_WIN_MAIN_WIDTH-2)//12 

#define _WIN_HOTKEY_ROW_START_PIXEL					0
#define _WIN_HOTKEY_COL_START_PIXEL					0

#define _WIN_HOTKEY_VALUE_COL						_WIN_HOTKEY_INFO_WIDTH				

#define _WIN_HOTKEY_INFO_WIDTH						(_OSD_HOTKEY_MENU_WIDTH/2) 			
#define _WIN_HOTKEY_INFO_HEIGHT						_OSD_HOTKEY_MENU_HEIGHT				
#define _WIN_HOTKEY_ITEM_ROW						2				

#define _WIN_HOTKEY_PANEL_UNIFORMITY_WIDTH			30

#define _WIN_HOTKEY_SOURCE_TITLE_HEIGHT				4			
#define _WIN_HOTKEY_SOURCE_HEIGHT					_OSD_HOTKEY_MENU_HEIGHT				
#define _WIN_HOTKEY_SOURCE_TIPS_ROW					27				
#define _WIN_HOTKEY_SOURCE_TIPS_HEIGHT				4				

#define _SUBITEM_COL_START							(_WIN_MAIN_WIDTH+1)
#define _SUBITEM_INFO_SEC                           22
#define _SUBITEM_INFO_THI                           29
 
#define _OSD_OPTION_TYPE_COL_START					1//3

#define _OSD_SLIDER_COL_START						25
#define _OSD_SLIDER_LENGTH							16

//#define _OSD_ITEM_SLIDER_LENGTH					    12

#define _OSD_ITEM_1_ROW_START						_OSD_MAIN_ITEM_ROW_START
#define _OSD_ITEM_2_ROW_START						(_OSD_ITEM_1_ROW_START + 3)
#define _OSD_ITEM_3_ROW_START						(_OSD_ITEM_2_ROW_START + 3)
#define _OSD_ITEM_4_ROW_START						(_OSD_ITEM_3_ROW_START + 3)
#define _OSD_ITEM_5_ROW_START						(_OSD_ITEM_4_ROW_START + 3)
#define _OSD_ITEM_6_ROW_START						(_OSD_ITEM_5_ROW_START + 3)
#define _OSD_ITEM_7_ROW_START						(_OSD_ITEM_6_ROW_START + 3)

#define _OSD_ITEM_VALUE_COL							30//(_OSD_MAIN_MENU_WIDTH - 2*_OSD_ITEM_SLIDER_LENGTH)
#define _OSD_ITEM_VALUE_RIGHT_ALIGN_COL				(_OSD_MAIN_MENU_WIDTH - 2*2)

//MainMenu
#define _MESSAGE_BG_WINDOW                        	_OSD_WINDOW_0
#define _MAINMENU_TITLE_WINDOW                      _OSD_WINDOW_8
#define _MAINMENU_MAIN_WINDOW                       _OSD_WINDOW_2 
#define _MAINMENU_SUB_WINDOW                        _OSD_WINDOW_1 
#define _SUBMENU_SELECT_WINDOW                      _OSD_WINDOW_4 

//#define _MAINMENU_POPUP_WINDOW                      _OSD_WINDOW_4

//Info Menu
#define _MAINMENU_INFO_WINDOW						_OSD_WINDOW_0


#define _POPUP_WINDOW_COL_START                     _OSD_ITEM_VALUE_COL 
#define _OSD_POPUP_COL_START						(_POPUP_WINDOW_COL_START + 2) 
#define _OSD_POPUP_COL_LENGTH					    12
#define _OSD_POPUP_VALUE_COL						(_OSD_MAIN_MENU_WIDTH - _OSD_POPUP_COL_LENGTH)

#define _POPUP_WINDOW_HEIGHT                      	10
#define _POPUP_WINDOW_WIDTH                      	20

//#define _BG_WIN_COLOR                 				_CP_GRAY_32
#define _TITLE_WIN_COLOR							_CP_GRAY_32
#define _MAIN_WIN_COLOR                 			_CP_GRAY_80
#define _INFO_WIN_COLOR								_CP_BLACK
#define _SUB_WIN_COLOR                 				_CP_GRAY

#define _OPT_SELECT_FRAME_COLOR				        _CP_BLUE_120		

//#define _POPUP_WIN_COLOR                 			_CP_GRAY_80
//#define _OPTION_WIN_COLOR                 			_CP_BLUE_120

#define _STATE_CLEAR								0
#define _STATE_SELECT								1
#define _STATE_ADJUST								2

#define _LEFT_TYPE									0
#define _RIGHT_TYPE									1
#define _ALIGN_TYPE									_LEFT_TYPE 

 
#define _SUB_OPTION_TITLE_ROW						4
#define _SUB_OPTION_TITLE_COL_START				 	1

//--------------------------------------------------
// Definitions of OSD Type
//--------------------------------------------------

#define _OSD_MESSAGE_ROW_START                      2
#define _OSD_MESSAGE_CENTER_COL_START               12
#define _OSD_MESSAGE_CENTER_COL_END                 23

//--------------------------------------------------
// Definitions of HL window Border Size
//--------------------------------------------------
#define _HL_WIN_BORDER_SIZE                         0// 2

//--------------------------------------------------
// Definitions of Slider
//--------------------------------------------------
#define _SLIDER_LENGHT                              120 // 250
#define _SLIDER_HIGH                                18 // 20
#define _SLIDER_BORDER_PIXEL                        1 // 2
#define _SLIDER_OFFSET                              6

#define _SLIDER_SELECT_BORDER_COLOR                 _CP_GRAY
#define _SLIDER_SELECT_BG_COLOR                     _CP_WHITE

#define _SLIDER_UNSELECT_BORDER_COLOR               _CP_WHITE
#define _SLIDER_UNSELECT_BG_COLOR                   _CP_GRAY

#define _SLIDER_SELECT_COLOR                        _CP_ORANGE
#define _SLIDER_UNSELECT_COLOR                      _CP_BLUE

#define _SLIDER_0                                   0
#define _SLIDER_1                                   1
#define _SLIDER_2                                   2

#define _SELECT                                     1
#define _UNSELECT                                   0

#define _SLIDER_0_BAR_WINDOW                        _OSD_WINDOW_4_8 
#define _SLIDER_0_BG_WINDOW                         _OSD_WINDOW_4_7 
#define _SLIDER_0_BORDER_WINDOW                     _OSD_WINDOW_4_6 

#define _SLIDER_1_BAR_WINDOW                        _OSD_WINDOW_4_8
#define _SLIDER_1_BG_WINDOW                         _OSD_WINDOW_4_7
#define _SLIDER_1_BORDER_WINDOW                     _OSD_WINDOW_4_6

#define _SLIDER_0_ROW                               16
#define _SLIDER_0_COL                               11

#define _ITEM_0                                     0
#define _ITEM_1                                     1
#define _ITEM_2                                     2
#define _ITEM_3                                     3
#define _ITEM_4                                     4
#define _ITEM_5                                     5
#define _ITEM_6                                     6
#define _ITEM_7                                     7

#define _NONE_ITEM                                  8

#define _FONTFROM_0_255                             0x00
#define _FONTFROM_256_512                           _BIT5
//--------------------------------------------------
// Definitions of Highlight Window
//--------------------------------------------------

#define _OSD_WIN_HIGHLIGHT_1                        _OSD_WINDOW_4_1
#define _OSD_WIN_HIGHLIGHT_2                        _OSD_WINDOW_4_2

//--------------------------------------------------
// Definitions of Color effect user mode Hue & Saturation
//--------------------------------------------------
#define _COLOR_HUE                                  0
#define _COLOR_SATURATION                           1

//--------------------------------------------------
// Definitions of Percentage
//--------------------------------------------------
#define _0_PERCENT                                  0
#define _50_PERCENT                                 50
#define _100_PERCENT                                100
typedef enum
{
    _ADJ_BAR_REAL,
    _ADJ_BAR_REAL_PWM_FACT,
    _ADJ_BAR_PERCENT,
    _ADJ_BAR_10_TIMES,
    _ADJ_LIST,
    _ADJ_DIRECT,
}EnumAdjType;

//--------------------------------------------------
// Define enter panel uniformity msg adjust from pcm or gamma
//--------------------------------------------------
typedef enum
{
    _FROM_STATE_PCM,
    _FROM_STATE_GAMMA,
    _FROM_STATE_HDR,
    _FROM_STATE_LD,
    _FROM_STATE_SDRTOHDR,
} EnumFromWhichState;


//--------------------------------------------------
// Define PCM Soft Proft
//--------------------------------------------------
typedef enum
{
    _PCM_SOFT_MODE_1,
    _PCM_SOFT_MODE_2,
    _PCM_SOFT_MODE_AMOUNT = _PCM_SOFT_MODE_2,
} EnumPCMSoftProftMode;

//--------------------------------------------------
// Define PCM InputGamma
//--------------------------------------------------
typedef enum
{
    _PCM_INPUTGAMMA_NATIVE = 0,
    _PCM_INPUTGAMMA_18,
    _PCM_INPUTGAMMA_19,
    _PCM_INPUTGAMMA_20,
    _PCM_INPUTGAMMA_21,
    _PCM_INPUTGAMMA_22,
    _PCM_INPUTGAMMA_24,
    _PCM_INPUTGAMMA_26,
    _PCM_INPUTGAMMA_28,
    _PCM_INPUTGAMMA_30,
    _PCM_INPUTGAMMA_DICOM,
    _PCM_INPUTGAMMA_HLG,
    _PCM_INPUTGAMMA_AMOUNT = _PCM_INPUTGAMMA_HLG,
}EnumPCMInputGammaType;

//--------------------------------------------------
// Define Gamma
//--------------------------------------------------
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_18,

    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,
    _GAMMA_26,   // 5  _GAMMA_NAME_G22_DICOM_USER_CALIB_HYBRID -> Hybrid

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    _GAMMA_DICOM200 = _GAMMA_20,
    _GAMMA_DICOM250,    
    _GAMMA_DICOM300,
    
    _GAMMA_DICOM350,
    _GAMMA_DICOM400,        
    _GAMMA_DICOM450,//7
    
    _GAMMA_DICOM500,        
    _GAMMA_DICOM550,
    _GAMMA_DICOM600, //a
#endif   

    // Only X-Rite Calibration Index[DDCCI CMD]
    _GAMMA_DICOM_ALC1, 
    _GAMMA_DICOM_ALC2, 
    _GAMMA_DICOM_ALC3, 
    _GAMMA_DICOM_ALC4, 
    _GAMMA_DICOM_ALC5, 

    _GAMMA_CALIB,
    _GAMMA_AMOUNT = _GAMMA_CALIB,
}EnumGammaType;
//--------------------------------------------------
// Define Panel Color Mode
//--------------------------------------------------
typedef enum
{
   M_MONO,
   M_COLOR,
}EnumPanelColorType;
//--------------------------------------------------
// Define HL Window Type
//--------------------------------------------------
typedef enum
{
    _HL_WIN_OFF,
    _HL_WIN_1,//full
    _HL_WIN_2,//leftside
    _HL_WIN_3,//rightside
    _HL_WIN_4,//center
    _HL_WIN_5,//move
    _HL_WIN_AMOUNT = _HL_WIN_5,
}EnumHLWinType;

typedef enum
{
    _COLOREFFECT_STANDARD,
    _COLOREFFECT_GAME,
    _COLOREFFECT_MOVIE,
    _COLOREFFECT_PHOTO,
    _COLOREFFECT_VIVID,
    _COLOREFFECT_USER,
    _COLOREFFECT_AMOUNT = _COLOREFFECT_USER,
}EnumColorEffectType;

//--------------------------------------------------
// Define Color Effect Six Color
//--------------------------------------------------
typedef enum
{
    _SIXCOLOR_R,
    _SIXCOLOR_Y,
    _SIXCOLOR_G,
    _SIXCOLOR_C,
    _SIXCOLOR_B,
    _SIXCOLOR_M,
    _SIXCOLOR_AMOUNT = _SIXCOLOR_M,
}EnumSixColorType;

//--------------------------------------------------
// Define Ultra Vivid
//--------------------------------------------------
typedef enum
{
    _ULTRA_VIVID_OFF,
    _ULTRA_VIVID_L,
    _ULTRA_VIVID_M,
    _ULTRA_VIVID_H,
    _ULTRA_VIVID_AMOUNT = _ULTRA_VIVID_H,
}EnumUltraVividType;


//--------------------------------------------------
// Define Supported Aspect Ratios
//--------------------------------------------------
typedef enum
{
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_16_BY_9,
    _OSD_ASPECT_RATIO_4_BY_3,
    _OSD_ASPECT_RATIO_5_BY_4,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_ORIGIN,
}EnumAspectRatioTypeIndex;

//--------------------------------------------------
// Define DP Port Version
//--------------------------------------------------
typedef enum
{
    _DP_VER_1_DOT_1 = 0,
    _DP_VER_1_DOT_2,
    _DP_VER_1_DOT_3,
    _DP_VER_AMOUNT = _DP_VER_1_DOT_3,
}EnumOSDDpPortVersionDef;

typedef enum
{
    _MST_OFF = 0,
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    _MST_AUTO,
#endif
    _MST_D0,
    _MST_D1,
    _MST_D6,
    _MST_AMOUNT = _MST_D6,
}EnumOSDDpMstTypeDef;

//--------------------------------------------------
// Define Display Image Rotate
//--------------------------------------------------
typedef enum
{
    _DISP_ROTATE_0 = 0,
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _DISP_ROTATE_90,
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _DISP_ROTATE_180,
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _DISP_ROTATE_270,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_HOR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_VER_MIRROR,
#endif

    _DISP_ROTATE_AMOUNT,

}EnumOSDDispRotateDegree;

//--------------------------------------------------
// Define Display Latency
//--------------------------------------------------
typedef enum
{
    _LATENCY_L = 0,
    _LATENCY_M,
    _LATENCY_H,
    _LATENCY_AMOUNT = _LATENCY_H,
}EnumOSDDLatency;

//--------------------------------------------------
// Define HotKey Option
//--------------------------------------------------
typedef enum
{
    _HOTKEY_GAMMA = 0, 
    _HOTKEY_AMB,
    _HOTKEY_KVM,
    _HOTKEY_USER_CALIBRATION_GAMMA,
    _HOTKEY_DEVIATION,
    _HOTKEY_RESET,
    _HOTKEY_COLOR_MONO,
    _HOTKEY_I_LUMINANCE,
    _HOTKEY_LIGHTBOX,
    _HOTKEY_AMOUNT = _HOTKEY_LIGHTBOX,
}EnumOSDHotKeyDef;


//--------------------------------------------------
// Definitions of Input Port
//--------------------------------------------------
typedef enum
{
    _OSD_INPUT_A0,
    _OSD_INPUT_A1,
    _OSD_INPUT_A2,    
    _OSD_INPUT_D0,
    _OSD_INPUT_D1,
    _OSD_INPUT_D2,
    _OSD_INPUT_D3,
    _OSD_INPUT_D4,
    _OSD_INPUT_D5,
    _OSD_INPUT_D6,
    _OSD_INPUT_AUTO,
    _OSD_INPUT_AMOUNT = _OSD_INPUT_AUTO,
}EnumOSDInputPortDef;


//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
typedef enum
{
    _CT_9300,
    _CT_7500,
    _CT_6500,
    _CT_5800,
    _CT_SRGB,
    _CT_USER,
    _CT_COLORTEMP_AMOUNT = _CT_USER,
}EnumColortemptureDef;


//--------------------------------------------------
// Definitions of 3D Effect
//--------------------------------------------------
typedef enum
{
    _3D_EFFECT_OFF = _OFF,
    _3D_EFFECT_WEAK,
    _3D_EFFECT_MEDIUM,
    _3D_EFFECT_STRONG,
    _3D_EFFECT_AMOUNT = _3D_EFFECT_STRONG,
}EnumOSDSelect3DEffectDef;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
#if(_OCC_SUPPORT == _ON)
    _PCM_OSD_SRGB,
    _PCM_OSD_ADOBE_RGB,
#endif

    _PCM_OSD_USER,
    _PCM_OSD_NATIVE,
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
    _PCM_OSD_SOFT_PROFT,
    _PCM_OSD_AMOUNT = _PCM_OSD_SOFT_PROFT,
#else
    _PCM_OSD_AMOUNT = _PCM_OSD_NATIVE,
#endif
}EnumPCMTypeIndex;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_OSD_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_OSD_TYPE2,      // gamma 2.0
    _UNIFORMITY_OSD_TYPE3,      // gamma 2.2
    _UNIFORMITY_OSD_TYPE4,      // gamma 2.4
    _UNIFORMITY_OSD_TYPE5,      // srgb
    _UNIFORMITY_OSD_TYPE6,      // adobe rgb
}EnumUniformityTypeSelectIndex;
//--------------------------------------------------
// Definitions of Clone Mode
//--------------------------------------------------
typedef enum
{
    _OSD_CLONE_OFF = 0,
    _OSD_CLONE_ON,
}EnumOSDCloneModeDef;
//--------------------------------------------------
// Define of Level Type
//--------------------------------------------------
typedef enum
{
    _LEVEL_OFF = 0,
    _LEVEL_L,
    _LEVEL_M,
    _LEVEL_H,
    _LEVEL_AMOUNT = _LEVEL_H,
}EnumLevelType;

typedef enum
{
    _LIGHTBOX_MODE_LEFT,
    _LIGHTBOX_MODE_RIGHT,
    _LIGHTBOX_MODE_FULL,
}EnumLightBoxMode;

typedef enum
{
    _OFF_POWER_SAVING,
    _FAKE_POWER_SAVING,
    _DEEP_POWER_SAVING,
}EnumPowerSavingMode;

//--------------------------------------------------
// Definitions of Distance Sensor Mode
//--------------------------------------------------
typedef enum
{
    _OSD_DISTANCE_OFF = 0,
    _OSD_DISTANCE_MODE1,
    _OSD_DISTANCE_MODE2,
    _OSD_DISTANCE_MODE3,
    _OSD_DISTANCE_AMOUNT = _OSD_DISTANCE_MODE3,
}EnumOSDDistanceSensorMode;

typedef enum
{
    _AMB_LIGHT_OFF = 0,
    _AMB_LIGHT_1,
    _AMB_LIGHT_2,
    _AMB_LIGHT_3,
    _AMB_LIGHT_AMOUNT = _AMB_LIGHT_3,
}EnumOsdBackgroundLightMode;
#if (_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)
typedef enum
{
    _RGB_LIGHT_OFF = 0,
    _RGB_LIGHT_1,
    _RGB_LIGHT_2,
    _RGB_LIGHT_3,
    _RGB_LIGHT_AMOUNT = _RGB_LIGHT_3,
}EnumRGBLightMode;
typedef enum
{
    _RGB_LIGHT_R = 0,
    _RGB_LIGHT_G,
    _RGB_LIGHT_B,
    _RGB_AMOUNT = _RGB_LIGHT_B,
}EnumRGBtMode;
#endif
typedef enum
{
    _ALC_X_RAY = 0,
    _ALC_CT_MR_NM,
    _ALC_STAFF_OFFICES,
    _ALC_HOSPITAL_CLINICAL_VIEWING,
    _ALC_EMERGENCY_MEDICINE,
    _ALC_OPERATING_ROOMS,
    _ALC_AUTO,
    _ALC_AMOUNT = _ALC_AUTO,
    //Area                              Illumination(lux)  Beacon(lux)
    //X-ray ��                                2~10            5lux 
    //CT/MR/NM ��                             15~60           50lux
    //Staff offices ��                        50~180          100lux 
    //Hospital clinical viewing stations ��   200~250         200lux
    //Emergency medicine ��                   150~300         300lux
    //Operating rooms ��                      300~400         400lux
}EnumOsdDICOMALC;

//--------------------------------------------------
// Definitions of FPGA Test Image
//--------------------------------------------------
typedef enum
{
    _TEST_IMAGE_OFF = 0,
    //_TEST_IMAGE_TG18_CH, 
    //_TEST_IMAGE_TG18_MM1,  //FPGA DDR Index = 22 (2P LR) for new
    _TEST_IMAGE_TG18_QC,   // FPGA DDR Index = 23 (1P)
    _TEST_IMAGE_AMOUNT = _TEST_IMAGE_TG18_QC,
}EnumOSDTestImageIndexDef;

//--------------------------------------------------
// Definitions of Read Mode
//--------------------------------------------------
typedef enum
{
    _READING_REPORT_OFF = 0,
    _READING_REPORT_ON,
    _READING_REPORT_MODE_AMOUNT = _READING_REPORT_ON,
}EnumOSDReadingReportModeDef;

//--------------------------------------------------
// Definitions of Auto Panel Luminance AB Backlight Sensor pos
//--------------------------------------------------
typedef enum
{
	 _BK_SENSOR_MIDDLE,							  	
	 _BK_SENSOR_UP,								  	
	 _BK_SENSOR_DOWN,							  	
     _BK_SENSOR_POS_AMOUNT,
}EnumPanelLuxABBKSensorPosDef;

//--------------------------------------------------
// Definitions of Auto Panel Luminance Range Backlight Sensor Color Temperature
//--------------------------------------------------
typedef enum
{
    _BK_SENSOR_CT_9300,   
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
    _BK_SENSOR_CT_7500,   
#endif        
    _BK_SENSOR_CT_6500,   
    _BK_SENSOR_CT_AMOUNT,
}EnumPanelLuxRangeBKSensorCTDef;

//--------------------------------------------------
// Enumerations of ARM MCU Cmd Type Identifier
//--------------------------------------------------
typedef enum
{
    _CMD_USER_LUT_CAL = 0x01,      // User Lut:Type[DICOM/Gamma] L Max-Min Amb./Curve 
    _CMD_MAX_MIN_CMD  = 0x03,
    _CMD_LUM_DIFF     = 0x04,      // User Lut:Type[DICOM/Gamma] L Max-Min Amb./Curve and User Colortemp Value

	_CMD_DDC_QA_EVENT = 0xA4,     // Start&Result

	_CMD_DDC_UPDATE_FPGA = 0xF0,     // Updata FPGA Gamma data
	_CMD_DDC_MCU_VERSION = 0xF1,     //  Get MCU Version data
	
    _CMD_NONE         = 0xFF,
}EnumMcuCommunicationIndex;

//--------------------------------------------------
//--------------------------------------------------

typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
    BYTE b1OsdFactoryModeStatus : 1;
    BYTE b1OsdDoAspectRatio : 1;
    BYTE b3OsdColorFormat : 3;
    BYTE b3OsdsixColor : 3;
    BYTE b1OsdDoubleSizeStatus : 1;
    BYTE b1FreezeStatus : 1;
    BYTE b1OsdWakeUpLightBoxMode : 1;    
#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
    BYTE b1FreezeDisableOsdStatus : 1;
#endif
#if(_DP_DEBUG_MSG == _ON)
    BYTE b1OsdWakeUpShowDpINFO : 1;
    BYTE b4OsdWakeUpShowDpINFOPort : 4;
#endif
    WORD ucOsdStatePrevious;
    WORD usOsdState;
    BYTE ucOsdEventMsg;
    BYTE ucOsdKeyMessage;
    BYTE ucOsdKeyControl;
    BYTE ucOsdDoAspectRatio;

    BYTE b3OsdsixColorHue;
    BYTE b3OsdsixColorSaturation;
    BYTE ucOsdColorTempOsdItem;

#if(_FREESYNC_SUPPORT == _ON)
    BYTE ucOsdFREESYNCInforOsdAddress;
#endif
    BYTE ucOsdItemIndex;

    BYTE b1OsdPixelShift : 1;
    BYTE b2StringMode : 2;
    BYTE ucStringModeLength;
    BYTE ucStringBlankPixel;

} StructOsdInfo;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
typedef struct
{
    BYTE b4OrbitingTimer : 4;
}StructTimer;

typedef struct
{
    BYTE b1Capability : 1;
}StructPixelOrbitingStatus;
#endif
#endif

typedef enum
{
    _ = U0020,
    _Percentage = U0025,            //%
    _UPDOT_ = U0027,                // '
    _LEFT_BRACE_ = U0028,           // (
    _RIGHT_BRACE_ = U0029,          // )
    _COMMA_ = U002C,                // ,
    _SLINE_ = U002D,                // -
    _DOT_ = U002E,                  // .
    _AND_ = U002F,                  // /
    _DEGREE_0=U2103_0,
    _DEGREE_1=U2103_1,


    _0_ = U0030, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_,

    _COLON_ = U003A,                // :
    _SEPERATE_ = U003B,             // ;
    _QUERY_ = U003F,                // ?
    _AT_0_ = U0040_0,               // @
    _AT_1_ = U0040_1,               // @

    _A_ = U0041, _B_, _C_, _D_, _E_, _F_, _G_, _H_, _I_, _J_, _K_, _L_,
    _M_, _N_, _O_, _P_, _Q_, _R_, _S_, _T_, _U_, _V_,
    _W_0, _W_1,
    _X_, _Y_, _Z_,

    _a_ = U0061, _b_, _c_, _d_, _e_, _f_, _g_, _h_, _i_, _j_, _k_, _l_,
    _m_, _n_, _o_, _p_, _q_, _r_, _s_, _t_, _u_, _v_,
    _w_,
    _x_, _y_, _z_,
}EnumOSDFontDef;

typedef enum
{
    _CP_EMPTY = 0,
    _CP_BG = 0,
    _CP_BLACK = 0,    
    _CP_WHITE,
	_CP_GRAY_32,
	_CP_GRAY_80,
	_CP_GRAY,
    _CP_BLUE_120,
	_CP_WHITE_250,
	_CP_RED,
    _CP_BLUE,
	_CP_YELLOW,
	_CP_GREEN_119,
	_CP_ORANGE,
	_CP_LIGHTBLUE,
	_CP_PINK,
	_CP_ORANGE_H,
    _CP_BLUE_200,

}EnumOSDColorPaletteDef;

typedef enum
{
    _LOGO_CP_BG = 0,
    _LOGO_CP_BLACK = 0,
    _LOGO_CP_DARKBLUE,
    _LOGO_CP_WHITE,
    _LOGO_CP_RED,
    _LOGO_CP_GREEN,
    _LOGO_CP_BLUE,
    _LOGO_CP_YELLOW,
    _LOGO_CP_GRAY,
    _LOGO_CP_LIGHTBLUE,
    _LOGO_CP_SELECTBOTTOM,
    _LOGO_CP_PINK,
    _LOGO_CP_RED_1,
    _LOGO_CP_GREEN_1,
    _LOGO_CP_ORANGE_L,
    _LOGO_CP_ORANGE_H,
    _LOGO_CP_GRAY_1,
}EnumOSDColorPaletteLogo;

typedef enum
{
    
    _MENU_NONE,
    _MENU_KEY,

// Level 1  
    _MAINMENU_START,
    _MAIN_PAGE_START = _MAINMENU_START,
    _MENU_IMAGE = _MAIN_PAGE_START,
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    _MENU_QA,
#endif        
    _MENU_FUNCTION_SETTING,
    _MENU_INFO,
    _MENU_ADVANCE,
    _MAIN_PAGE_END = _MENU_ADVANCE,

// Level 2
	_IMAGE_PAGE_START,
	_IMAGE_PCM = _IMAGE_PAGE_START,
	_IMAGE_GAMMA,
	_IMAGE_DICOMALC,
	_IMAGE_COLOR_TEMP,	
	_IMAGE_BACKLIGHT,
	_IMAGE_HDR,
	_IMAGE_PAGE_END = _IMAGE_HDR,

	_QA_PAGE_START,
	_QA_TEST_IMAGE = _QA_PAGE_START,
	_QA_DEVIATION,
	_QA_PAGE_END = _QA_DEVIATION,

	_FUNCTION_SETTING_PAGE_START,
	_FUNCTION_LANGUAGE = _FUNCTION_SETTING_PAGE_START,
	_FUNCTION_INPUT,
	_FUNCTION_AMB_LIGHT,
	_FUNCTION_REPORT_MODE,
	_FUNCTION_2HOURS_REMINDER,
	_FUNCTION_FACTORY_RESET,
	_FUNCTION_SETTING_PAGE_END = _FUNCTION_FACTORY_RESET,


	_ADVANCED_PAGE_START,
	_ADVANCED_PASSWORD = _ADVANCED_PAGE_START,
	_ADVANCED_PAGE_END = _ADVANCED_PASSWORD,

// Level 3
	_IMAGE_PAGE_ADJ_START,
	_IMAGE_PCM_ADJ = _IMAGE_PAGE_ADJ_START,
	_IMAGE_GAMMA_ADJ ,
	_IMAGE_DICOMALC_ADJ,
	_IMAGE_COLOR_TEMP_ADJ,	
	_IMAGE_BACKLIGHT_ADJ,
	_IMAGE_PAGE_ADJ_END = _IMAGE_BACKLIGHT_ADJ,

	_QA_PAGE_ADJ_START,
	_QA_TEST_IMAGE_ADJ = _QA_PAGE_ADJ_START,
	_MENU_HOTKEY_DEVIATION_ADJ,
	_QA_PAGE_ADJ_END = _MENU_HOTKEY_DEVIATION_ADJ,

	_FUNCTION_SETTING_PAGE_ADJ_START,
	_FUNCTION_LANGUAGE_ADJ = _FUNCTION_SETTING_PAGE_ADJ_START,
	_FUNCTION_INPUT_ADJ,
	_FUNCTION_AMB_LIGHT_ADJ,
	_FUNCTION_REPORT_MODE_ADJ,
	_FUNCTION_2HOURS_REMINDER_ADJ,
	_MENU_HOTKEY_FACTORY_RESET_ADJ,
	_FUNCTION_SETTING_PAGE_ADJ_END = _MENU_HOTKEY_FACTORY_RESET_ADJ,

// Level 4 
   _PAGE_2=_FUNCTION_SETTING_PAGE_ADJ_END,
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    _IMAGE_PAGE_GAMMA_USER_START,
    _GAMMA_USER_TYPE = _IMAGE_PAGE_GAMMA_USER_START,
    _GAMMA_USER_L_MAX,
    _GAMMA_USER_L_MIN,
    _GAMMA_USER_LAMB,
    _GAMMA_USER_VALUE,
    _GAMMA_USER_SET,
    _IMAGE_PAGE_GAMMA_USER_END = _GAMMA_USER_SET,
#endif

    _IMAGE_PAGE_COLORTEMP_USER_START,
    _COLOR_TEMP_USER_R = _IMAGE_PAGE_COLORTEMP_USER_START,
    _COLOR_TEMP_USER_G,
    _COLOR_TEMP_USER_B,
    _IMAGE_PAGE_COLORTEMP_USER_END = _COLOR_TEMP_USER_B,

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    _IMAGE_HYBRID_START,
    _IMAGE_HYBRID_GRAY_CURVE = _IMAGE_HYBRID_START,
    _IMAGE_HYBRID_COLOR_CURVE,
    _IMAGE_HYBRID_END = _IMAGE_HYBRID_COLOR_CURVE,
#endif 

    _IMAGE_HDR_START,
    _IMAGE_HDR_MODE = _IMAGE_HDR_START,
    _IMAGE_HDR_DARK_ENHANCE,
    _IMAGE_HDR_SHARP_ENHANCE,
    _IMAGE_HDR_CONTRAST,
    _IMAGE_HDR_END = _IMAGE_HDR_CONTRAST,

// Level 5
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)        
    _IMAGE_PAGE_GAMMA_USER_ADJ_START,
    _GAMMA_USER_TYPE_ADJ = _IMAGE_PAGE_GAMMA_USER_ADJ_START,
    _GAMMA_USER_L_MAX_ADJ,
    _GAMMA_USER_L_MIN_ADJ,
    _GAMMA_USER_LAMB_ADJ,
    _GAMMA_USER_VALUE_ADJ,
    //_MENU_HOTKEY_GAMMA_SET_ADJ,
    _IMAGE_PAGE_GAMMA_USER_ADJ_END = _GAMMA_USER_VALUE_ADJ,
#endif

    _IMAGE_PAGE_COLOR_TEMP_USER_ADJ_START,
    _COLOR_TEMP_USER_R_ADJ = _IMAGE_PAGE_COLOR_TEMP_USER_ADJ_START,
    _COLOR_TEMP_USER_G_ADJ,
    _COLOR_TEMP_USER_B_ADJ,
    _IMAGE_PAGE_COLOR_TEMP_USER_ADJ_END = _COLOR_TEMP_USER_B_ADJ,

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    _IMAGE_HYBRID_ADJ_START,
    _IMAGE_HYBRID_GRAY_CURVE_ADJ = _IMAGE_HYBRID_ADJ_START,
    _IMAGE_HYBRID_ADJ_END = _IMAGE_HYBRID_GRAY_CURVE_ADJ,
#endif        

    _IMAGE_HDR_ADJ_START,
    _IMAGE_HDR_MODE_ADJ = _IMAGE_HDR_ADJ_START,
    _IMAGE_HDR_DARK_ENHANCE_ADJ,
    _IMAGE_HDR_SHARP_ENHANCE_ADJ,
    _IMAGE_HDR_CONTRAST_ADJ,
    _IMAGE_HDR_ADJ_END = _IMAGE_HDR_CONTRAST_ADJ,

//==============================================================================
// Service Page Start
// Level 3
    _SERVICE_PAGE_START,
    _SERVICE_PAGE_1= _SERVICE_PAGE_START,
    _SERVICE_PAGE_2,
    _SERVICE_PAGE_3,
#if(_VGA_SUPPORT == _ON)       
    _SERVICE_PAGE_4,   
#endif                
    _SERVICE_PAGE_5, 
    _SERVICE_PAGE_END = _SERVICE_PAGE_5,

// Level 4
    _SERVICE_PAGE_1_START,
    _DISPLAY_ROTATE = _SERVICE_PAGE_1_START,      
    _ASPECT_RATIO,                
    _SERVICE_PAGE_1_END=_ASPECT_RATIO,
        
    _SERVICE_PAGE_2_START,
    _DP_VERSION = _SERVICE_PAGE_2_START,
    _DP_MST,
    _DP_CLONE,                
    _DP_RESOLUTION,
    _SERVICE_PAGE_2_END=_DP_RESOLUTION,
        
    _SERVICE_PAGE_3_START,
    _UNIFORMITY=_SERVICE_PAGE_3_START,
    _SDR,
    _SERVICE_PAGE_3_END=_SDR,

#if(_VGA_SUPPORT == _ON)               
	_ANALOG_PAGE_START,
	_ANALOG_PAGE_AUTO_COLOR_ITEM = _ANALOG_PAGE_START,
	_ANALOG_PAGE_AUTO_ADJUST_ITEM,
	_ANALOG_PAGE_H_POSTION_ITEM,
	_ANALOG_PAGE_V_POSTION_ITEM,
	_ANALOG_PAGE_CLOCK_ITEM,
	_ANALOG_PAGE_PHASE_ITEM,
	_ANALOG_PAGE_END = _ANALOG_PAGE_PHASE_ITEM,
#endif        

    _SERVICE_PAGE_5_START,
	_AMBIENT_SENSOR = _SERVICE_PAGE_5_START,
    _BODY_SENSOR,
    _GRAVITY_SENSOR,
    _BACKLIGHT_SENSOR, 
    _ENERGY_SAVING,
    _OSD,        
    _SERVICE_PAGE_5_END = _OSD,

// Level 5
    _SERVICE_PAGE_1_ADJUST_START,
    _DISPLAY_ROTATE_ADJ = _SERVICE_PAGE_1_ADJUST_START,   
    _ASPECT_RATIO_ADJ,   
    _SERVICE_PAGE_1_ADJUST_END = _ASPECT_RATIO_ADJ,

    _SERVICE_PAGE_2_ADJUST_START,
    _DP_VERSION_ADJ = _SERVICE_PAGE_2_ADJUST_START,
    _DP_MST_ADJ,
    _DP_CLONE_ADJ,                        
    _DP_RESOLUTION_ADJ,
    _SERVICE_PAGE_2_ADJUST_END = _DP_RESOLUTION_ADJ,

    _SERVICE_PAGE_3_ADJUST_START,
    _UNIFORMITY_ADJ = _SERVICE_PAGE_3_ADJUST_START,
    _SDR_ADJ,
    _SERVICE_PAGE_3_ADJUST_END=_SDR_ADJ,

#if(_VGA_SUPPORT == _ON)               
    _ANALOG_PAGE_ADJUST_START,
    _ANALOG_PAGE_H_POS_ADJUST = _ANALOG_PAGE_ADJUST_START,
    _ANALOG_PAGE_V_POS_ADJUST,
    _ANALOG_PAGE_CLOCK_ADJUST,
    _ANALOG_PAGE_PHASE_ADJUST,
    _ANALOG_PAGE_ADJUST_END = _ANALOG_PAGE_PHASE_ADJUST,
#endif

    _SERVICE_PAGE_5_ADJUST_START,
	_AMBIENT_SENSOR_ADJ = _SERVICE_PAGE_5_ADJUST_START,
    _BODY_SENSOR_ADJ,
    _GRAVITY_SENSOR_ADJ,
    _BACKLIGHT_SENSOR_ADJ, 
    _ENERGY_SAVING_ADJ,
    _SERVICE_PAGE_5_ADJUST_END = _ENERGY_SAVING_ADJ,

    _SERVICE_PAGE_5_OSD_START,
    _OSD_TIME = _SERVICE_PAGE_5_OSD_START,
    _OSD_POSITION,
    _OSD_ROTATE,
    _USE_LIFE_REMINDER,    
    _SERVICE_PAGE_5_OSD_END = _USE_LIFE_REMINDER,

    _SERVICE_PAGE_5_OSD_ADJ_START,
    _OSD_TIME_ADJ = _SERVICE_PAGE_5_OSD_ADJ_START,
    _OSD_POSITION_ADJ,
    _OSD_ROTATE_ADJ,
    _USE_LIFE_REMINDER_ADJ,    
    _SERVICE_PAGE_5_OSD_ADJ_END = _USE_LIFE_REMINDER_ADJ,


	_MAINMENU_END = _SERVICE_PAGE_5_OSD_ADJ_END,

	
    // HOT KEY
    _MENU_HOTKEY_GAMMA_MODE,
#if(_BEACON_OSD_AMB == _ON)    
    _MENU_HOTKEY_AMB_MODE,
#endif    
    _MENU_HOTKEY_KVM_MODE,
#if((_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)&&(_PRODUCT_ID_SEL != RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
    _MENU_HOTKEY_COLOR_MONO,
#endif    
    _MENU_HOTKEY_I_LUMINANCE_MODE,

    _MENU_HOTKEY_LIGHTBOX_MODE,

    _MENU_HOTKEY_INFORMATION,
    _MENU_MESSAGE_DISPLAY,
    _MENU_END,
}EnumOsdMenuStatus;

typedef enum
{
    _ICON_PAGE_CLEAR = 0,

    //_ICON_TITLE,
    _ICON_MAINMENU_PAGE,
    _ICON_ADAVANCE_LEVEL_PAGE,
}EnumIconPage;

typedef enum
{
    _ICON_NONE = 0,

	_ICON_LIGHTBOX_LEFT,
	_ICON_LIGHTBOX_RIGHT,
	_ICON_LIGHTBOX_FULL,

	_ICON_KEYLOCK_OFF,
	_ICON_KEYLOCK_ON,

	_ICON_I_LUMINATE_TM,
	
    _OPTION_ICON_END,
}EnumIconIndex;


typedef enum
{
    _ICON_INPUT_NO_PORT = _OPTION_ICON_END,
    _ICON_INPUT_VGA,
    _ICON_INPUT_DVI,
    _ICON_INPUT_HDMI,
    _ICON_INPUT_DP,
    _ICON_INPUT_MHL,
    _ICON_INPUT_HDMI20,
    _ICON_INPUT_DUAL_DVI,

    _ICON_INPUT_END,

}EnumIconPort;

typedef enum
{
    _ICON_A0_PORT = _ICON_INPUT_END,
    _ICON_D0_PORT,
    _ICON_D1_PORT,
    _ICON_D2_PORT,
    _ICON_D3_PORT,
    _ICON_D4_PORT,
    _ICON_D5_PORT,
    _ICON_D6_PORT,

    _ICON_PORT_END,
}EnumIconPortIndex;




typedef enum
{
    _FONT1_GLOBAL,
    _REALTEK_1BIT_LOGO0,
    _REALTEK_1BIT_LOGO1,
}EnumFont;


typedef enum
{
    _PALETTE_RTD_LOGO,
	_PALETTE_DBI_LOGO,
	_PALETTE_MEDBOT_LOGO,
    _PALETTE_MAIN_MENU,
}EnumPalette;

typedef enum
{
    _ENGLISH = 0,
    _FRENCH,
    _GERMAN,    
    _SPANISH,
    _PORTUGUESE,
    _ITALIAN, 
    _SWEDISH,
    _POLISH, 
    _RUSSIAN, 
    _JAPANESE, 
    _ARABIC,
    _CHINESE_S,
    _LANGUAGE_AMOUNT = _CHINESE_S,
    _CHINESE_T,
}EnumOSDLanguageDef;

typedef enum
{
    _OSDEVENT_NONE_MSG = 0,
    _OSDEVENT_SHOW_NOSIGNAL_MSG,
    _OSDEVENT_SHOW_NOCABLE_MSG,
    _OSDEVENT_SHOW_NOSUPPORT_MSG,
    _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG,
    _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG,
    _OSDEVENT_WAKE_UP_SHOW_QUICKLINK_MENU_MSG,
    _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG,    
    _OSDEVENT_DO_AUTO_CONFIG_MSG,
    _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG,
    _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG,
    //_OSDEVENT_SAVE_NVRAM_INPUTPORT_MSG,
    _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG,
    _OSDEVENT_SAVE_NVRAM_BRICON_MSG,
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
    _OSDEVENT_PIXEL_ORBITING_ACTION_MSG,
#endif
#endif
    _OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDUSER2DATA_MSG,
    _OSDEVENT_SAVE_NVRAM_USER_LUTDATA_MSG,
    _OSDEVENT_WAKE_UP_LIGHTBOXMODE_MSG,
    _OSDEVENT_DP_VERSIOM_MSG,
}EnumOSDEvenMassage;

typedef enum
{
    _OSD_DISP_NOSIGNAL_MSG,
    _OSD_DISP_NOCABLE_MSG,
    _OSD_DISP_NOSUPPORT_MSG,
    _OSD_DISP_FAIL_SAFE_MODE_MSG,
    _OSD_DISP_AUTO_CONFIG_MSG,
    _OSD_DISP_INPUT_SIGNAL_MSG,
    _OSD_DISP_AUTO_COLOR_MSG,
    _OSD_DISP_SWITCH_DDCCI_PORT_MSG,
    _OSD_DISP_POWER_SAVING_MSG,
#if(_FREEZE_SUPPORT == _ON)
    _OSD_DISP_DISABLE_FREEZE_MSG,
#endif
    _OSD_DISP_2HOUR_REMINDER_MSG,
    _OSD_DISP_USE_LIFE_MSG,    
#if(_DP_MST_SUPPORT == _ON)
    _OSD_DISP_MST_WARNING_MSG,
#endif
    _OSD_DISP_KEY_LOCK_MSG,
    _OSD_DISP_QA_RESULT,
    _OSD_DISP_DICOM_RESULT,
} EnumOSDDispMsg;

typedef enum
{
    _ICON_POS_UP_0,
    _ICON_POS_UP_1,
    _ICON_POS_UP_2,
    _ICON_POS_UP_3,
    _ICON_POS_DOWN_0,
    _ICON_POS_DOWN_1,
    _ICON_POS_DOWN_2,
    _ICON_POS_DOWN_3,
}EnumOSDMainMenuIcon;

typedef enum
{
    _STRING_IMAGE,
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    _STRING_QA,
#endif    
    _STRING_FUNCTION_SETTING,
    _STRING_INFO,
    _STRING_ADVANCE,


    _STRING_GAMMA,
    _STRING_ALC,         
    _STRING_COLOR_TEMP,
    _STRING_HYBRID,
    _STRING_CALIB,
    _STRING_BACKLIGJT,//10

#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    _STRING_TEST_IMAGE,
#endif
    _STRING_DEVIATION,

    _STRING_LANGUAGE,
    _STRING_INPUT,
    _STRING_AMB_LIGHT,
    _STRING_REPORT_MODE,
    _STRING_2HOURS_REMINDER,
    _STRING_FACTORY_RESET,

    _STRING_POS_H,
    _STRING_POS_V,
    _STRING_PCM,
    _STRING_OSD,//20


    _STRING_COLOR_SWITCH,
    _STRING_LUMIN,    
    _STRING_OSD_LOCK,	
    _STRING_PASSWORD,
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    _STRING_USER_TYPE,
    _STRING_USER_L_MAX,
    _STRING_USER_L_MIN,
    _STRING_USER_LAMB,
    _STRING_USER_VALUE,
    _STRING_USER_SET,	
#endif
    _STRING_TEMP_USER_R,
    _STRING_TEMP_USER_G,
    _STRING_TEMP_USER_B,	

    _STRING_HYBRID_GRAY,
    _STRING_HYBRID_COLOR,//30

    _STRING_DISPLAY_MODE,
    _STRING_WINDOW_1,



    _STRING_INFO_PRODUCT_ID,
    _STRING_PRODUCT_ID,
    _STRING_FIRMWARE_VERSION,
    //_STRING_INFO_FORMAT,
    //_STRING_INFO_LAMB_CURRENT,
    //_STRING_INFO_AMB_LIGHT,//40
    _STRING_INFO_TIME,
    _STRING_INFO_USE_TIME,
    _STRING_INFO_PANEL_LUMIN,
    _STRING_INFO_PANEL_LUMINANCE,
    _STRING_INFO_INPUT,

    //_STRING_INFO_RESOLUTION,
    _STRING_NOW_RESOLUTION_0,

    
    _STRING_GAMMA_OFF,
    _STRING_GAMMA1_8,

    _STRING_GAMMA2_0,
    _STRING_GAMMA2_2,//50
    _STRING_GAMMA2_4,
    _STRING_GAMMA2_6,

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    _STRING_GAMMA_DICOM200 = _STRING_GAMMA2_0,
    _STRING_GAMMA_DICOM250,    
    _STRING_GAMMA_DICOM300,
    _STRING_GAMMA_DICOM350,
    _STRING_GAMMA_DICOM400,        
    _STRING_GAMMA_DICOM450,        
    _STRING_GAMMA_DICOM500,        
    _STRING_GAMMA_DICOM550,
    _STRING_GAMMA_DICOM600,      
#endif

    // Only X-Rite Calibration Index[DDCCI CMD] sync EnumGammaType
    _STRING_GAMMA_DICOM_ALC1, 
    _STRING_GAMMA_DICOM_ALC2, 
    _STRING_GAMMA_DICOM_ALC3, 
    _STRING_GAMMA_DICOM_ALC4, 
    _STRING_GAMMA_DICOM_ALC5, 

    _STRING_GAMMA_CALIB,


    _STRING_ALC_X_RAY,
    _STRING_ALC_CTMRNM,
    _STRING_ALC_STAFF_OFFICES,
    _STRING_ALC_HOSPITAL_CLINICAL,
    _STRING_ALC_EMERGENCY_MEDICINE,
    _STRING_ALC_OPERATING_ROOM,
    _STRING_ALC_AUTO,

    _STRING_CT_9300,
    _STRING_CT_7500,
    _STRING_CT_6500,
    _STRING_CT_5800,
    _STRING_CT_SRGB,
    _STRING_CT_USER,

    _STRING_OFF,
    _STRING_ON,

    _STRING_ENGLISH,
    _STRING_FRENCH,
    _STRING_GERMAN,
    _STRING_SPANISH, 
    _STRING_PORTUGUESE, 
    _STRING_ITALIAN, 
    _STRING_SWEDISH,
    _STRING_POLISH, 
    _STRING_RUSSIAN, 
    _STRING_JAPANESE, 
    _STRING_ARABIC,
    _STRING_CHINESE,

    _STRING_AMB_OFF,
    _STRING_AMB_1,
    _STRING_AMB_2,
    _STRING_AMB_3,//100

    _STRING_REPORT_OFF,
    _STRING_REPORT_LEFT,
    _STRING_REPORT_RIGHT,

    _STRING_FORMAT_RGB,
    _STRING_FORMAT_YUV,


    _STRING_ENERGYSAVING_OFF,
    _STRING_ENERGYSAVING_FAKE,
    _STRING_ENERGYSAVING_DEEP,


    _STRING_COLOR_PCM_SRGB,
    _STRING_COLOR_PCM_ADOBE_RGB,
    _STRING_COLOR_PCM_USER,
    _STRING_COLOR_PCM_NATIVE,
    _STRING_COLOR_PCM_SOFT_PROFT_1,
    _STRING_COLOR_PCM_SOFT_PROFT_2,

    _STRING_PCM_STANDARD,
    _STRING_PCM_GAMMA_18,
    _STRING_PCM_GAMMA_19,
    _STRING_PCM_GAMMA_20,
    _STRING_PCM_GAMMA_21,
    _STRING_PCM_GAMMA_22,
    _STRING_PCM_GAMMA_24,
    _STRING_PCM_GAMMA_26,
    _STRING_PCM_GAMMA_28,
    _STRING_PCM_GAMMA_30,
    _STRING_PCM_HLG,

    _STRING_HDR10_MODE_OFF,
    _STRING_HDR10_MODE_AUTO,
    _STRING_HDR10_MODE_FORCE_2084,
    _STRING_HDR10_MODE_AUTO_HLG,
    _STRING_HDR10_MODE_FORCE_HLG,

    _STRING_HLG_STANDARD,//120
    _STRING_HLG_USER1,
    _STRING_HLG_USER2,
    _STRING_HLG_USER3,


    _STRING_ASPECT_FULL,
    _STRING_ASPECT_16_9,
    _STRING_ASPECT_4_3,
    _STRING_ASPECT_5_4,
    _STRING_ASPECT_ORIGIN,
    _STRING_ASPECT_USER,
	
	_STRING_LIGHT_BOX_LEFT,
	_STRING_LIGHT_BOX_RIGHT,
	_STRING_LIGHT_BOX_FULL,

    _STRING_COLOR_SWITCH_SINGLE,
    _STRING_COLOR_SWITCH_COLOR,

    _STRING_DISP_ROTATE,
    _STRING_ASPECT,
    _STRING_OVER_SCAN,
    _STRING_SHOW_NUMBER_PERCENTAGE,


    _STRING_0_DEGREE,
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _STRING_90_DEGREE,
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _STRING_180_DEGREE,//140
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _STRING_270_DEGREE,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _STRING_LR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _STRING_UD_MIRROR,
#endif

    _STRING_OSD_0_DEGREE,
    _STRING_OSD_90_DEGREE,
    _STRING_OSD_270_DEGREE,
    _STRING_OSD_180_DEGREE,


    _STRING_OSD_POSITON_LT,
    _STRING_OSD_POSITON_RT,
    _STRING_OSD_POSITON_LB,
    _STRING_OSD_POSITON_RB,
    _STRING_OSD_POSITON_MIDDLE,
    _STRING_OSD_POSITON_USER,
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    _STRING_GAMMA_USER_TYPE_DICON,
    _STRING_GAMMA_USER_TYPE_GAMMA,
#endif

    _STRING_NO_SIGNAL,
    _STRING_NO_CABLE,
    _STRING_NO_SUPPORT,
    _STRING_POWERSAVING,
    _STRING_2HOUR_REMINDER_TEXT_0,
    _STRING_2HOUR_REMINDER_TEXT_1,
    _STRING_DISPLAY_USELIFE_TEXT_0,
    _STRING_DISPLAY_USELIFE_TEXT_1,

    // Show OSD Number
    _STRING_SHOW_NUMBER,

    // information
    _STRING_HFREQPCLK_0,
    //_STRING_DSC,

    _STRING_HLG,//160
    _STRING_FREESYNC,
    _STRING_SDR,
    _STRING_HDCP_MODE,
    _STRING_USELIFE,
    


    _STRING_VERSION,
    _STRING_DP_RESOLUTION,
    _STRING_DSC,

#if(_HDR10_SUPPORT == _ON)
    _STRING_HDR_MODE,
    _STRING_DARK_ENHANCE,
    _STRING_SHARPNESS_ENHANCE,
    _STRING_HDR_CONTRAST,
    _STRING_HLG_OOTF,
#endif
    _STRING_15S,
    _STRING_5M,
    _STRING_15M,



    _STRING_1_DOT_4,
    _STRING_2_DOT_0,
    _STRING_2_DOT_1,

    _STRING_1_DOT_1,
    _STRING_1_DOT_2,
    // _STRING_1_DOT_3,
    _STRING_DP_1_DOT_4,//180

    _STRING_DSC_NONE,
    _STRING_DSC_D0,
    _STRING_DSC_D1,
    _STRING_DSC_D2,
    _STRING_DSC_D3,
    _STRING_DSC_D4,
    _STRING_DSC_D5,

    _STRING_CLONE_MT_OFF,
    _STRING_CLONE_MT_A0,
    _STRING_CLONE_MT_D0,
    _STRING_CLONE_MT_D1,
    _STRING_CLONE_MT_D2,
    _STRING_CLONE_MT_D3,
    _STRING_CLONE_MT_D4,
    _STRING_CLONE_MT_D5,
    _STRING_CLONE_MT_D6,

    _STRING_DSC_OFF,
    _STRING_DSC_AUTO,

    _STRING_MST_OFF,
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    _STRING_MST_AUTO,//200
#endif
    _STRING_MST_D0,
    _STRING_MST_D1,
    _STRING_MST_D6,


    _STRING_DP,
    _STRING_OSD_TIME,    
    _STRING_OSD_ROTATE,
    _STIRNG_POSITION,

    _STRING_AUTO_ADJUST,
    _STRING_HPOS,
    _STRING_VPOS,
    _STRING_CLOCK,
    _STRING_PHASE,

    _STRING_MST,
    _STRING_CLONE,

    _STRING_AMBIENT_SENSOR,
    _STRING_BODY_INDUCTION,
    _STRING_GRAVITY_SENSOR,
    _STRING_BACKLIGHT_SENSOR,
    _STRING_UNIFORMITY,
    _STRING_ENERGY_SAVING,    
    //_STRING_LOGO,


    _STRING_DP_1080P,
    _STRING_DP_2560_1440,   
    _STRING_DP_4K2K_60HZ,//220

    //_STRING_MENU,
    //_STRING_OK,
    //_STRING_UP,
    //_STRING_DOWN,
    //_STRING_LEFT,
    //_STRING_RIGHT,
    //_STRING_RETURN,
    //_STRING_ADJUST,
    //_STRING_SOURCE,
    _STRING_BOX,

    _STRING_YES,

    _STRING_PAGE_1,
    _STRING_PAGE_2,
    _STRING_PAGE_3,
    _STRING_PAGE_4,

    _STRING_LIGHT_BOX,
    //_STRING_BACKLIGHT,
    _STRING_KVM,

   // HDCP
    _STRING_HDCP_NONE,//240
    _STRING_HDCP_14,
    _STRING_HDCP_22,
    _STRING_HDCP_14_REPEATER,
    _STRING_HDCP_22_REPEATER,

    _STRING_VGA_USER_MODE,
    _STRING_VGA_PRESET_MODE,

    _STRING_Execute,
    _STRING_NO,

    _STRING_PASS,
    _STRING_FAIL,
    _STRING_Processing_Do_Not_Operate,
    _STRING_Lumin_Processing_Do_Not_Operate,
    
#if(_DP_DEBUG_MSG == _ON)
    _STRING_DP_INFO,
    _STRING_DP_INFO_2,
#endif
    
    _STRIN_END,//260
}EnumStringIndex;

typedef enum
{
    // input
    _STRING_A0_PORT = _STRIN_END,
    _STRING_A1_PORT,
    _STRING_A2_PORT,
    _STRING_D0_PORT,
    _STRING_D1_PORT,
    _STRING_D2_PORT,
    _STRING_D3_PORT,
    _STRING_D4_PORT,
    _STRING_D5_PORT,
    _STRING_D6_PORT,
    _STRING_AUTOSELECT_PORT,    
}EnumStringPort;

typedef enum
{
    _A0_PORT = 0,
    _A1_PORT,
    _A2_PORT,    
    _D0_PORT,
    _D1_PORT,
    _D2_PORT,
    _D3_PORT,
    _D4_PORT,
    _D5_PORT,
    _D6_PORT,
}EnumPortInx;

typedef enum
{
    _OSD_ROTATE_DISPLAY_FULL = 0,
    _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL,
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,
}EnumOsdRotationDisplaySizeDef;

typedef enum
{
    _AUTO_CONFIG_DO = 0,
    _AUTO_CONFIG_RESULT,
}EnumAutoConfig;

typedef enum
{
    _OSD_HLW_INSIDE = 0,
    _OSD_HLW_OUTSIDE,
}EnumOSDHLWRegion;

typedef enum
{
    _OSD_HUB_AUTO = 0,
    _OSD_HUB_TYPEB,
    _OSD_HUB_D0,
    _OSD_HUB_D1,
}EnumOsdUSBHubUfpSwitch;

typedef enum
{
    _EAGLE_SIGHT_FUNCTION = 0,
    _EAGLE_SIGHT_TRANSPARENT,
    _EAGLE_SIGHT_ZOOM,
    _EAGLE_SIGHT_CAPTURE_POSITION,
    _EAGLE_SIGHT_DISPLAY_POSITION,
}EnumOsdEagleSightItem;

typedef enum
{
    _OSD_MBR_OFF = 0,
    _OSD_MBR_USERMODE,
    _OSD_MBR_RTK_ADV,
}EnumOsdMBR;

typedef enum
{
    _MBR_MODE = 0,
    _MBR_DUTY,
    _MBR_POSITION,
}EnumOsdMBRMode;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// __RTD_POWER__
extern bit g_bPowerForcePowSavStatus;

// __RTD_DDCCI__
extern bit g_bForceBackupStatus;
extern BYTE g_ucPanelUniformityCalibrationData; // for Panel Uniformity Calibration data
extern bit g_bForceAutoSwitchEDIDStatus;  // force Auto Switch EDID data
extern BYTE g_ucScalerSendMcuData;
extern BYTE g_ucScalerSendMcuUartID;
extern bit g_bSingleFontEnable;
extern bit b_usLightBoxLongPressFlag;
extern BYTE g_ucKeyLockCount;
extern BYTE uctemperaturesensor;
extern WORD usSensorLux;    //Far Ambient Sensor
extern WORD Lum_RealFiltered;  //Basis for calibration
extern bit g_bForcePowSavStatus;
#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
extern bit g_bForceSwitchSourceStatus;
#endif

// __RTD_OSD__
extern StructOsdInfo g_stOsdInfo;
extern WORD g_usAdjustValue;
extern WORD g_usBackupValue;
extern WORD g_us4thItemNum;
extern volatile BYTE g_ucLogoTimerCounter;

// __RTD_OSDFUNC__
extern WORD g_usFontSelectStart;
extern WORD g_usFontTableStart;
extern BYTE g_ucOsdWidth;
extern BYTE g_ucOsdHeight;
extern BYTE g_ucOsdWidthB;
extern BYTE g_ucOsdHeightB;
extern WORD g_ucFontPointer0;
extern WORD g_ucFontPointer1;
extern WORD g_ucFontPointer2;
extern WORD g_ucFontPointer3;


#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
extern bit g_bflagMinuteON;
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern Tables from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];

//----------------------------------------------------------------------------------------
// Extern Tables from OsdTable.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTTABLE__
//extern BYTE code tOSD_iREALTEK[];
//extern BYTE code tOSD_iKEY_BACK[];
extern BYTE code tOSD_iKEY_MENU[];
extern BYTE code tOSD_iKEY_GAMMA[];
extern BYTE code tOSD_iKEY_KVM[];
extern BYTE code tOSD_iKEY_AMB[];
extern BYTE code tOSD_iKEY_SOURCE[];
extern BYTE code tOSD_iKEY_LIGHTBOX[];

extern BYTE code tOSD_iKEY_LEFT[];
extern BYTE code tOSD_iKEY_RIGHT[];
extern BYTE code tOSD_iKEY_UP[];
extern BYTE code tOSD_iKEY_DOWN[];
extern BYTE code tOSD_iKEY_ENTER[];
extern BYTE code tOSD_iKEY_EXIT[];
extern BYTE code tOSD_iKEY_ADJUST[];                    
extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
extern BYTE code tOSD_REALTEK_4BIT_LOGO[];
extern code BYTE *tTips_HOTKEY_TABLE[];
extern code BYTE *tTips_HOTKEY_TABLE1[];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserDdcci.c
//----------------------------------------------------------------------------------------
// __RTD_DDCCI__
extern void UserDdcciHandler(void);
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)
extern void UserInterfaceDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength);
extern WORD UserInterfaceDdcciGetCpStringSize(EnumInputPortType enumPortType);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from RTDKey.c
//----------------------------------------------------------------------------------------
// __RTD_KEY__
extern void UserInterfaceKeyHandler(void);
extern void RTDKeyInitial(void);

//----------------------------------------------------------------------------------------
// Extern functions from Osd.c
//----------------------------------------------------------------------------------------
extern bit UserOperationOSDOnKeep(void);


//----------------------------------------------------------------------------------------
// Extern functions from OsdFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFUNC__
extern void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB);


extern void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void OsdFuncTransparency(BYTE ucTrans);
extern void OsdFuncBlending(BYTE ucType);

extern void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
extern void OsdFuncDisableOsd(void);
extern void OsdFuncEnableOsd(void);
extern void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth ,BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
extern void OsdFuncSet2BitIconOffset(WORD usOffset);
extern void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth ,BYTE ucHeight);

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
extern void OsdDisplayPixelOrbitingAction(void);
extern void OsdDisplaySetPixelOrbitingCapability(void);
#endif
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
extern void OsdFuncSixColorAdjust(void);
#endif

extern void OsdFuncColorFormatAdjust(void);

extern void OsdFuncColorPcmAdjust(void);
extern BYTE OsdFuncCheckPCMStatusAdjustType(BYTE ucOsdPCMStatusNum);
extern BYTE OsdFuncCheckPCMInputGammaAdjustType(BYTE ucOsdInputGammaTypeNum);
extern BYTE OsdFuncCheckGammaAdjustType(BYTE ucOsdGammaTypeNum);
extern BYTE OsdFuncCheckAspectAdjustType(WORD usValue, WORD usMax, WORD usMin);
extern void OsdFuncShowSourceMenuCheck(void);
extern BYTE OsdFuncCheckColorTempAdjustType(BYTE ucOsdColorTempTypeNum);
extern void OsdFuncSetOsdItemFlag(void);
extern BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum);
extern BYTE OsdFuncCheckDPClonePortType(BYTE ucOsdClonePortNum);

#if(_FREEZE_SUPPORT == _ON)
extern bit OsdFuncCheckFreezeDisable(void);
extern void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif


#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort);
extern void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue);
#endif

#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
extern void OsdFuncAutoDetectSwitchHdmiDPPort(void);
#endif


extern BYTE COsdCtrlMenuItemGetEnable(WORD ucState);
extern BYTE GetShowIndex(BYTE ucMenuItem,BYTE ucBeginItem,BYTE ucEndItem);
extern WORD MGetNextOsdState(WORD ucState,WORD ucBegin, WORD ucEnd, bit bCycle);
extern WORD MGetFirstOsdState(WORD ucBegin, WORD ucEnd);
extern void UpdateMainMenuCursor(BYTE OSDState,bit bState);
extern void UpdateServiceMenuCursor(BYTE OSDState,bit bState);

extern void OsdFuncCalibrationWindowsColor(BYTE ucWin, BYTE ucPos, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);

extern void PCMAdjust(void);
extern void GammaAdjust(void);
extern void DicomALCAdjust(void);
extern void ColorTempAdjust(void);
extern void BackLightAdjust(void);
extern void HybridAdjust(void);
extern void CalibrationAdjust(void);
extern void TestImageAdjust(void);
extern void LanguageAdjust(void);
extern void FunctionInputAdjust(void);
extern void AmbLightAdjust(void);
extern void ReportModeAdjust(void);
extern void TwohoursReminderAdjust(void);
extern void RotateAdjust(void);
extern void BodySensorAdjust(void);
extern void GravitySensorAdjust(void);
extern void BacklightSensorEnAdjust(void);
extern void AmbientSensorAdjust(void);
extern void LogoAdjust(void);
extern void EnergySavingAdjust(void);
extern void LogoEnableAdjust(void);
extern void UniformityAdjust(void); 
extern void ColorMonoAdjust(void);
extern void SDRAdjust(void);
extern void DarkEnhanceAdjust(void);
extern void SharpEnhanceAdjust(void);
extern void HdrContrastAdjust(void);
extern void HlgOotfAdjust(void);
extern void AspectAdjust(void);
extern void GammaUserTypeAdjust(void);
extern void GammaUserLMaxAdjust(void);
extern void GammaUserLMinAdjust(void);
extern void GammaUserLambAdjust(void);
extern void GammaUserValueAdjust(void);
extern void ColorTempUserRAdjust(void);
extern void ColorTempUserGAdjust(void);
extern void ColorTempUserBAdjust(void);
extern void HybridGrayCurveAdjust(void);
extern void HdrModeAdjust(void);
extern void InputSourceAdjust(void);
extern void HotkeyGammaAdjust(void);
extern void HotkeyAmbAdjust(void);
extern void HotkeyKvmAdjust(void);
extern void HotkeyColorMonoAdjust(void);
extern void HotkeyILuminanceAdjust(void);
extern void OsdOverScanAdjust(void);
extern void DPVersionAdjust(void);
extern void DPResolutionAdjust(void);
extern void DPMSTAdjust(void);
extern void DPCloneAdjust(void);
extern void DSCAdjust(void);
extern void OsdTimeAdjust(void);
extern void OsdPositionAdjust(void);
extern void OsdRotateAdjust(void);
extern void UseLifeAdjust(void);
#if(_VGA_SUPPORT == _ON)

extern void VGAHPosAdjust(void);
extern void VGAVPosAdjust(void);
extern void VGAClockAdjust(void);
extern void VGAPhaseAdjust(void);
#endif
//----------------------------------------------------------------------------------------
// Extern functions from OsdDisplay.c
//----------------------------------------------------------------------------------------
// __RTD_OSDDISPLAY__
extern BYTE StateColor(BYTE State); 
extern BYTE OsdDispJudgeSourceType(void);
extern void OsdDispDisableOsd(void);
extern void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
extern void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
extern void OsdDispMainKey(void);
extern void OsdDispMainMenu(void);
extern void OsdDispServiceLevelMenu(void);
extern void SelectRegionAdjust(void);
extern void DrawSubMenu(WORD ucPageIndex);
extern void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue, BYTE ucRowIndex, BYTE ucColor);
extern WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
extern void OsdDisplaySixColorGetOneColor(BYTE ucColor);
extern void OsdDisplaySixColorSetOneColor(BYTE ucColor);
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
extern void OsdDispOsdRotateSwitch(void);
#endif
extern void OsdDispOsdReset(void);
extern void OsdDispHotKeyOptionMenu(BYTE ucOption);
extern void OsdDispHotKeyOptionMenuSwitch(BYTE ucPort);

extern void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
extern void OsdDispHotKeySourceMenuSwitch(BYTE ucPort);


extern void OsdDispShowLightBoxMode(void);

//extern void OsdDispPanelUniformityMsgSwitch(void);
extern void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);

#if(_VGA_SUPPORT == _ON)
extern void OsdDispAutoConfigProc(void);
extern void OsdDisplayAutoBalanceProc(void);
#endif
extern void OsdSelectedUpdate(BYTE bType,BYTE ucBeginItem,BYTE ucEndItem);
extern void OsdDispShowLogo(void);
extern void DrawImagePage(void);
extern void DrawQAPage(void);
extern void DrawFunctionSettingPage(void);
extern void DrawInfoPage(void);
extern void DrawAdvancePage(void);
extern void DrawGammaUserPage(void);
extern void DrawColorTempUserPage(void);
extern void DrawHybridPage(void);
extern void DrawHDRPage(void);
extern void DrawInputPage(void);
extern void DrawServicePage1(void);
extern void DrawServicePage2(void);
extern void DrawServicePage3(void);
extern void DrawServicePage4(void);
extern void DrawServicePage5(void);
extern void DrawPIPPage(void);
extern void DrawVersionPage(void);
//extern void DrawDpVersionPage(void);
extern void DrawDpResolutionPage(void);
extern void DrawOSDPage(void);
extern void DrawImageGamma(BYTE State);
extern void DrawImageDicomALC(BYTE State);
extern void DrawImageColorTemp(BYTE State);
extern void DrawImageHybrid(BYTE State);
extern void DrawImageBacklight(BYTE State);
extern void DrawImageHDR(BYTE State);
extern void DrawQATest(BYTE State);
extern void DrawQADeviation(BYTE State);

extern void DrawFunctionLanguage(BYTE State);
extern void DrawFunctionInput(BYTE State);
extern void DrawFunctionAmbLight(BYTE State);
extern void DrawFunctionReportMode(BYTE State);
extern void DrawFunction2hoursReminder(BYTE State);
extern void DrawFunctionFactoryReset(BYTE State);

//extern void DrawAmbientLight(BYTE State);
//extern void DrawDPVersion(BYTE State);
extern void DrawGravitySensor(BYTE State);
extern void DrawUniformity(BYTE State);
extern void DrawOSD(BYTE State);
extern void DrawOsdTime(BYTE State);
extern void DrawOsdRotate(BYTE State);
extern void DrawOsdPosition(BYTE State);
extern void DrawOsdPosH(BYTE State);
extern void DrawOsdPosV(BYTE State);
extern void DrawPCM(BYTE State);
extern void DrawHdrMode(BYTE State);
extern void DrawSDR(BYTE State);
extern void DrawUseLife(BYTE State);
extern void DrawVGAColor(BYTE State);
extern void DrawVGAAuto(BYTE State);
extern void DrawVGAHPostion(BYTE State);
extern void DrawVGAVPostion(BYTE State);
extern void DrawVGAClock(BYTE State);
extern void DrawVGAPhase(BYTE State);
#if(_HDR10_SUPPORT == _ON)
extern void DrawHDR(BYTE State);
extern void DrawDarkEnhance(BYTE State);
extern void DrawSharpEnhance(BYTE State);
extern void DrawHdrContrast(BYTE State);
#endif
extern void DrawHlgOoft(BYTE State);
extern void DrawAmbientSensor(BYTE State);
extern void DrawBodyInduction(BYTE State);
extern void DrawBacklightSensor(BYTE State);
extern void DrawGravitySensor(BYTE State);
extern void DrawEnergySaving(BYTE State);
extern void DrawLightBox(BYTE State);
extern void DrawColorSwitch(BYTE State);
extern void DrawOsdLock(BYTE State);
extern void DrawAdvancedPassword(BYTE State);

extern void DrawGammaUserType(BYTE State);
extern void DrawGammaUserLMax(BYTE State);
extern void DrawGammaUserLMin(BYTE State);
extern void DrawGammaUserLamb(BYTE State);
extern void DrawGammaUserValue(BYTE State);
extern void DrawGammaUserSet(BYTE State);

extern void DrawColorTempUserR(BYTE State);
extern void DrawColorTempUserG(BYTE State);
extern void DrawColorTempUserB(BYTE State);
extern void DrawHybridGrayCurve(BYTE State);
extern void DrawHybridColorCurve(BYTE State);
extern void DrawInputDisplayMode(BYTE State);
extern void DrawLRRatio(BYTE State);
extern void DrawDisplayRegionSelect(BYTE State);
extern void DrawDisplayRotate(BYTE State);
extern void DrawDisplayAspect(BYTE State);
extern void DrawOverScan(BYTE State);
extern void Draw2PFrameSync(BYTE State);
extern void DrawDPVersion(BYTE State);
extern void DrawDPMST(BYTE State);
extern void DrawDPClone(BYTE State);
extern void DrawDPResolution(BYTE State);
extern void DrawDSC(BYTE State);

extern void DrawPIPMode(BYTE State);
extern void DrawPIPPos(BYTE State);
extern void DrawPIPSize(BYTE State);
extern void DrawPipTrans(BYTE State);


#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
extern StructTimer g_stTimer;
extern StructPixelOrbitingStatus g_stPixelOrbitingStatus;
#endif
#endif
extern void DrawMainPage(void);
extern void DrawServiceLevelPage(void);

//extern EnumOsdMenuStatus OsdDispGetUpLayer(EnumOsdItem enumOsdItem);
//extern BYTE OsdDispGetOsdItemIdx(EnumOsdItem enumOsdItem);
//extern void OsdDispDirectMenu(EnumOsdItem enumOsdItem);
//----------------------------------------------------------------------------------------
// Extern functions from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern void OsdFontVLCLoadFont(BYTE ucState);

// __RTD_OSDFONTDYNAMICICON_1__
extern void OsdFontVLCDynamicLoadIcon(BYTE ucIconPos, WORD usIcon);

// __RTD_OSDFONTDYNAMICICON_2__
//extern void OsdFontVLCLoadMainIcon_2(BYTE ucIconPos, WORD usIcon);

// __RTD_OSDFONTTABLE__
extern void OsdFontPut1Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor);
extern void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor);
extern void OsdFontPut1BitMainMenuIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdFontPut2Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void OsdFontPut2BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);

// __RTD_OSDFONTPROP__
extern void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumber_float(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumberPercentage(BYTE ucRow, BYTE ucCol, DWORD usValue, bit bDecimalpointFlag, BYTE ucFontPoint, BYTE ucColor);
extern BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD usFontPoint);
extern void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucColor);

// __RTD_OSDPALETTE__
extern void OsdPaletteSelectPalette(BYTE ucValue);

// __RTD_OSDWINDOW__
extern void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdWindowDrawingByPixel(BYTE ucWindow, WORD ucRow, WORD ucCol, WORD ucWidth, WORD ucHeight, BYTE ucColor);
extern void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
extern void OsdWindowSliderDisable(void);

//----------------------------------------------------------------------------------------
// Extern functions from OsdTableFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDTABLEFUNC__
extern void OsdTableFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint);
extern BYTE OsdTableFuncVideoResolution(void);
extern void OsdTableFuncPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, BYTE ucLanguage);
extern void OsdTableFuncPutStringCenter(BYTE ucRow, BYTE ucColStart, BYTE ucColEnd, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, SBYTE chCenterOffset, BYTE ucLanguage);
extern void OsdTableFuncDrawWindow(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdTableFuncPutIcon1BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdTableFuncPutIcon2BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
#if(_UART_SUPPORT == _ON)
#if (_PRODUCT_ID_SEL == RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)
extern void UserMcuBootUartStart(void);
#endif
#endif
#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)

