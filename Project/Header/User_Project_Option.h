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
// ID Code      : User_Project_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//Product Module ID List
//Chip Series+Model number+PCB Type+Mono&Color+Client name+Panel name&resolution&interface type+PWM or DC
//STD       = Beacon
//PHILIPS   = Philips

//--------------------------------------------------
//  Chip Product Define start
//--------------------------------------------------
// UHD RL6410 RL6449 RL6492: 4096x2160&3840x2160
// QHD RL6410 RL6432 RL6449 RL6492: 2560x1600
// FHD RL6449 RL6432 RL6369 RL6463: 1920x1080
// RL6369 RL6463 OGC _GAMMA_TABLE_SIZE  387 other _GAMMA_TABLE_SIZE  2052
#define RTD2785TM_RL6432_DEMO_C_D_216PIN_STD_FHD  		                      0x01		
#define RTD2785TM_U231A_RL6432_216PIN_A_BBK_FHD  		                      0x02		
#define RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM         0x03	
#define RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80                    0x04
#define RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM               0x05	
#define RTD2556_LIANYING_1003_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM            0x06	


#define RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM       0x10	
#define RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM       0x11		
#define RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM       0x20	
#define RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI   0x21	
#define RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM       0x40		
#define RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI   0x41		
//!!!!Please define Gamma select type 
#define _GAMMA_NAME_G22_DICOM_USER_CALIB_HYBRID                          0 // Total:7   2.2 DICOM User CALIB Hybrid  [DICOM ALC: 1+5 DICOM curves]  [User is MCU Calibration and Hybrid is FPGA]  
#define _GAMMA_NAME_G22_DICOM_USER_CALIB                                 1 // Total:7   2.2 DICOM User CALIB [DICOM ALC: 1+5 DICOM curves]  [User is MCU Calibration]  
#define _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB                          2 // Total:10  2.0 2.2 2.4 2.6 DICOM CALIB  [DICOM ALC: 1+5 DICOM curves]
#define _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB                      3 // Total:9   2.2 [DICOM200 DICOM250 DICOM300]  [DICOM350 DICOM400 DICOM450]  [DICOM500 DICOM550 DICOM600] [DICOM ALC: 1+5 DICOM curves] CALIB


//!!!!Please Select Product Module 
#define _PRODUCT_ID_SEL      RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM//RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM//RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM//RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM

#if (_PRODUCT_ID_SEL == RTD2785TM_RL6432_DEMO_C_D_216PIN_STD_FHD)
//  
// Size = 34.0"  Active:H-795.6 V-335.7 Luminance variation 75% Min
// Bri  = 450cd/m2 Typ. 360cd/m2 Min.     
// Con  = 1200:1 Typ.	840:1 Min. 
// Color gamut[CIE1976] DCI 90% Min 98% Typ  sRGB 99% Min
// Color coordinates[CIE1931] R:x=0.680 y=0.313 G:x=0.268 y=0.685 B:x=0.151 y=0.055 W:x=0.313 y=0.329

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_DEMO_C_D_216PIN_1A2MHL1DP1mDP_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _AU_LVDS_21_5_WUXGA 


//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
//#define _KEYPAD_TYPE                              _KEYPAD_TYPE_RTD 

//#define _POWER_ON_LOGO_TYPE				          _LOGO_DBI
#define _DEFAULT_POWER_ON_LOGO					  _ON


//#define _DEFAULT_GAMMA                           _GAMMA_20
//#define _DEFAULT_COLORTEMP                       _CT_6500
//#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 

#elif (_PRODUCT_ID_SEL == RTD2785TM_U231A_RL6432_216PIN_A_BBK_FHD)
//  
// Size = 34.0"  Active:H-795.6 V-335.7 Luminance variation 75% Min
// Bri  = 450cd/m2 Typ. 360cd/m2 Min.     
// Con  = 1200:1 Typ.	840:1 Min. 
// Color gamut[CIE1976] DCI 90% Min 98% Typ  sRGB 99% Min
// Color coordinates[CIE1931] R:x=0.680 y=0.313 G:x=0.268 y=0.685 B:x=0.151 y=0.055 W:x=0.313 y=0.329

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BBK_A_HDMI_D3_216PIN_LVDS

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _AU_LVDS_21_5_WUXGA 


//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_BBK 

//#define _POWER_ON_LOGO_TYPE						 _LOGO_DBI
#define _DEFAULT_POWER_ON_LOGO					 _OFF


//#define _DEFAULT_GAMMA                           _GAMMA_20
//#define _DEFAULT_COLORTEMP                       _CT_6500
//#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 


#elif (_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)
//  
// Size = 21.3"  Active:H-324.86 V-433.15 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1100cd/m2 Typ. 880cd/m2 Min.     
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.686 y=0.312 G:x=0.233 y=0.694 B:x=0.144 y=0.064 W:x=0.307 y=0.327

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                               _INNOLUX_LVDS_R213RCE_LU1_1536x2048//_AUO_LVDS_G213QAN02_X_1536x2048

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#if  (_PANEL_TYPE == _AUO_LVDS_G213QAN02_X_1536x2048)
#define _BACKLIGHT_SENSOR_PRECISION              60//32 
#define PANEL_NAME                               "AUO"

#elif(_PANEL_TYPE == _INNOLUX_LVDS_R213RCE_LU1_1536x2048)
#define _BACKLIGHT_SENSOR_PRECISION              50//12 
#define PANEL_NAME                               "INNOLUX"
#elif(_PANEL_TYPE == _BOE_LVDS_EV213QXM_N10_1536x2048)
#define _BACKLIGHT_SENSOR_PRECISION              50//12 
#define PANEL_NAME                               "BOE"
#endif
//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_BEACON
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1520) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420) // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450) // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_0

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                 _OFF//_ON

//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "C310S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif

#elif (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)
//  
// Size = 21.3"  Active:H-324.86 V-433.15 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1100cd/m2 Typ. 880cd/m2 Min.     
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.686 y=0.312 G:x=0.233 y=0.694 B:x=0.144 y=0.064 W:x=0.307 y=0.327

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                               _INNOLUX_LVDS_R213RCE_LU2_1536x2048//_INNOLUX_LVDS_R213RCE_LU1_1536x2048

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              30

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_BEACON
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_9300//_CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1520) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420) // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450) // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_0

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                 _OFF//_ON

#define MODEL_COLOR_TYPE                          M_MONO

//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "G310S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif


#elif (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)
//  
// Size = 21.3"  Active:H-422.4 V-337.9 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1150cd/m2 Typ. 920cd/m2 Min.[PWM duty 100%]    600cd/m2 Typ. 480cd/m2 Min. [PWM duty 53%] 
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.655 y=0.335 G:x=0.315 y=0.580 B:x=0.140 y=0.060 W:x=0.299 y=0.315
// The LCD Module Should be stabilized at given temperature for 60 minutes

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_R213TCE_LU2_2560x2048 

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              80//12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_BEACON
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_270

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                 _OFF//_ON

//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "C510S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif
#elif (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)
//  
// Size = 21.3"  Active:H-422.4 V-337.9 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1150cd/m2 Typ. 920cd/m2 Min.[PWM duty 100%]    600cd/m2 Typ. 480cd/m2 Min. [PWM duty 53%] 
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.655 y=0.335 G:x=0.315 y=0.580 B:x=0.140 y=0.060 W:x=0.299 y=0.315
// The LCD Module Should be stabilized at given temperature for 60 minutes

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_R213TCE_LU2_2560x2048 

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              80//12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_DBI
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_270

#define _PROTOCOL_DBI_COLOR_SENSOR_CALIBRATION   _ON
#define _DEFAULT_KEYLOCK                         _ON

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                 _OFF//_ON

//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "C510S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif

#elif (_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)
//  
// Size = 21.3"  Active:H-422.4 V-337.9 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1150cd/m2 Typ. 920cd/m2 Min.[PWM duty 100%]    600cd/m2 Typ. 480cd/m2 Min. [PWM duty 53%] 
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.655 y=0.335 G:x=0.315 y=0.580 B:x=0.140 y=0.060 W:x=0.299 y=0.315
// The LCD Module Should be stabilized at given temperature for 60 minutes

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_R213TCE_LU1_2560x2048 

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              32//12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_BEACON
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_9300//_CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_270

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                   _OFF//_ON
#define MODEL_COLOR_TYPE                          M_MONO
//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "G510S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif
#elif (_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)
//  
// Size = 21.3"  Active:H-422.4 V-337.9 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1150cd/m2 Typ. 920cd/m2 Min.[PWM duty 100%]    600cd/m2 Typ. 480cd/m2 Min. [PWM duty 53%] 
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.655 y=0.335 G:x=0.315 y=0.580 B:x=0.140 y=0.060 W:x=0.299 y=0.315
// The LCD Module Should be stabilized at given temperature for 60 minutes

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_R213TCE_LU1_2560x2048 

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              32//12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_DBI
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_9300//_CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_270

#define _PROTOCOL_DBI_COLOR_SENSOR_CALIBRATION   _ON
#define _DEFAULT_KEYLOCK                         _ON

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                   _OFF//_ON
#define MODEL_COLOR_TYPE                          M_MONO
//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "G510S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif
#elif (_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
//  
// Size = 10.1"  Active:H-216.96 V-135.6 Luminance variation 70% Min
// Bri  = 500cd/m2 Typ. 400cd/m2 Min.     
// Con  = 800:1 Typ.	600:1 Min. 
// Color Chromaticity Panel       R:x=0.592 y=0.340 G:x=0.316 y=0.591 B:x=0.154 y=0.123 W:x=0.313 y=0.329
// Color Chromaticity BT.709/sRGB R:x=0.640 y=0.330 G:x=0.300 y=0.600 B:x=0.150 y=0.060 W:x=0.313 y=0.329
// Color Chromaticity Adobe RGB   R:x=0.640 y=0.330 G:x=0.210 y=0.710 B:x=0.150 y=0.060 W:x=0.313 y=0.329

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_DHWANNI_A_156PIN_1DP1HDMI_LVDS

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_G101ICE_L01 


//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_RTD 

//#define _POWER_ON_LOGO_TYPE						 _LOGO_DBI
#define _DEFAULT_POWER_ON_LOGO					 _OFF


#define _DEFAULT_UNIFORMITY                      _OFF
#define _DEFAULT_GAMMA                           _GAMMA_20
#define _DEFAULT_COLORTEMP                       _CT_6500
//#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 

#define _GAMMA_NAME_G20_G22_G24_DICOM             // Off 2.0 2.2 2.4 DICOM ...

#define _ENABLE_BACKLIGHT_SENSOR                  _OFF 
#elif (_PRODUCT_ID_SEL == RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)
//  
// Size = 21.3"  Active:H-422.4 V-337.9 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1150cd/m2 Typ. 920cd/m2 Min.[PWM duty 100%]    600cd/m2 Typ. 480cd/m2 Min. [PWM duty 53%] 
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.655 y=0.335 G:x=0.315 y=0.580 B:x=0.140 y=0.060 W:x=0.299 y=0.315
// The LCD Module Should be stabilized at given temperature for 60 minutes

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_CANON_A_156PIN_1DUALDVI_LVDS

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_G121ICE_L02_1280x800 

//#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              32//12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_BEACON
#define _DEFAULT_POWER_ON_LOGO					 _OFF

#define _GAMMA_TYPE                              _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_9300//_CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D3
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_270

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                   _OFF//_ON
//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "canon1201"		        // max size : 13 bytes
#define MONITOR_SN                               "CL1201*NEJFPMB100010001"	// max size : 25 bytes
//#define _DP_HDR10_SUPPORT                                       _OFF
//#define _DP_HDCP_2_2_SUPPORT                                    _OFF

// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif
#elif (_PRODUCT_ID_SEL == RTD2556_LIANYING_1003_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)
//  
// Size = 21.3"  Active:H-422.4 V-337.9 Luminance variation 75% Min  PWM:100Hz-200Hz-1KHz  Duty@200Hz:5%~100%
// Bri  = 1150cd/m2 Typ. 920cd/m2 Min.[PWM duty 100%]    600cd/m2 Typ. 480cd/m2 Min. [PWM duty 53%] 
// Con  = 2000:1 Typ.	1600:1 Min. 
// Color coordinates[CIE1931] R:x=0.655 y=0.335 G:x=0.315 y=0.580 B:x=0.140 y=0.060 W:x=0.299 y=0.315
// The LCD Module Should be stabilized at given temperature for 60 minutes

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_lIANYING_A_156PIN_1DUALDVI_LVDS

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _INNOLUX_LVDS_G121ICE_L02_1280x800 

#define _NO_HDMI                                _ON
//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              32//12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_3_5M 
#define _BEACON_OSD_AMB                          _OFF

#define _POWER_ON_LOGO_TYPE						 _LOGO_BEACON
#define _DEFAULT_POWER_ON_LOGO					 _OFF

#define _GAMMA_TYPE                              _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_22
#define _DEFAULT_COLORTEMP                       _CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D3
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_0

#define _ENABLE_DISTANCE_SENSOR                  _OFF//_ON 
#define _ENABLE_GRAVITY_SENSOR                   _OFF//_ON
//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "canon1201"		        // max size : 13 bytes
#define MONITOR_SN                               "CL1201*NEJFPMB100010001"	// max size : 25 bytes
//#define _DP_HDR10_SUPPORT                                       _OFF
//#define _DP_HDCP_2_2_SUPPORT                                    _OFF

// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif
#elif (_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)
//  
// Size = 10.1"  Active:H-216.96 V-135.6 Luminance variation 70% Min
// Bri  = 500cd/m2 Typ. 400cd/m2 Min.     
// Con  = 800:1 Typ.	600:1 Min. 
// Color Chromaticity Panel       R:x=0.592 y=0.340 G:x=0.316 y=0.591 B:x=0.154 y=0.123 W:x=0.313 y=0.329
// Color Chromaticity BT.709/sRGB R:x=0.640 y=0.330 G:x=0.300 y=0.600 B:x=0.150 y=0.060 W:x=0.313 y=0.329
// Color Chromaticity Adobe RGB   R:x=0.640 y=0.330 G:x=0.210 y=0.710 B:x=0.150 y=0.060 W:x=0.313 y=0.329

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_DHWANNI_A_156PIN_1DP1HDMI_LVDS

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _BOE_EV156FHM_N80_1920x1080//_INNOLUX_LVDS_G101ICE_L01 


//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
#define _KEYPAD_TYPE                             _KEYPAD_TYPE_RTD 

#define _POWER_ON_LOGO_TYPE						 _LOGO_NONE
#define _DEFAULT_POWER_ON_LOGO					 _ON

#define _GAMMA_TYPE                              _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB 

#define _DEFAULT_GAMMA                           _GAMMA_DICOM450
#define _DEFAULT_COLORTEMP                       _CT_9300//_CT_6500
#define _DEFAULT_OSDINPUTPORT0                   _OSD_INPUT_D0
#define _SKIP_COLORTEMP                          (_kBIT_CT_7500 | _kBIT_CT_5800) 
//#define Dicom_sup1                               (kBIT_DICOM_450) 

#define _GAMMA_CONTRAST_RATIO                    (1530) // CR: 1500:1 
#define _DICOM_CONTRAST_RATIO                    (420)  // CR: 400:1 
#define _DEFAULT_GAMMA_LUX                       (450)  // 450cd/m2
#define _DEFAULT_ROTATE_DEGREE                    _OSD_ROTATE_DEGREE_0

#define _ENABLE_DISTANCE_SENSOR                  _ON 
#define _ENABLE_GRAVITY_SENSOR                   _OFF//_ON
#define MODEL_COLOR_TYPE                          M_MONO
//--Front Color Sensor ---------------------------
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT _ON
#define MONITOR_TYPE                             "G510S"		        // max size : 13 bytes
#define MONITOR_SN                               "CL3101*NEJFPMB100010001"	// max size : 25 bytes
// !!!Must sync EnumGammaType[Swap _GAMMA_OFF/_GAMMA_CALIB]
#if( _GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,DICOM,User,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.0,2.2,2.4,2.6,DICOM,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#elif( _GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#define GAMMA_NAME_INFO	                         "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450,D500,D550,D600,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
#endif
#else

//--------------------------------------------------
//  Pcb Define
//--------------------------------------------------
#define _PCB_TYPE                                _RL6432_DEMO_C_D_216PIN_1A2MHL1DP1mDP_DPTX_LVDS_eDP

//--------------------------------------------------
//  Panel Define
//--------------------------------------------------
#define _PANEL_TYPE                              _AU_LVDS_21_5_WUXGA 


//  BK Sensor:8Bit PWM adjustment one ->cd/m2->350:500:650[600Hz:3~6] + Get Sensor[600Hz:��0~3]
//  When the ambient temperature is high, the backlight sensor value changes in a wide range
#define _BACKLIGHT_SENSOR_PRECISION              12 

//--------------------------------------------------
//  KeyPad Define
//--------------------------------------------------
//#define _KEYPAD_TYPE                             _KEYPAD_TYPE_RTD 


#endif

#ifndef _DEFAULT_UNIFORMITY
#define _DEFAULT_UNIFORMITY                      _ON
#endif
#ifndef _DEFAULT_KEYLOCK
#define _DEFAULT_KEYLOCK                         _OFF
#endif



#ifndef FW_VERSION
#define FW_VERSION                               "SVN:231016-1200 FW:V1.00"
#define _MAIN_VERSION							 "V1.00"
#define _TEST_VERSION							 "T103"
#endif

#ifndef MODEL_COLOR_TYPE
#define MODEL_COLOR_TYPE                         M_COLOR
#endif
#ifndef HW_VERSION
#define HW_VERSION                               "11M91-8CDB-1"      // max size : 25 bytes
#endif

//--------------------------------------------------
// Definitions of DP extra infomation for debug , DP Support must set ON
//--------------------------------------------------
#define _DP_DEBUG_MSG                                           _OFF

//--------------------------------------------------
// Definitions to Switch EDID/Capability String to Dell Spec (DDM Tool)
//--------------------------------------------------
#define _USER_SWITCH_TO_DELL_EDID_CAP_STRING                    _OFF

#if(_USER_SWITCH_TO_DELL_EDID_CAP_STRING == _ON)
#undef _CAPABILITIES_STRING_VGA
#undef _CAPABILITIES_STRING_DVI
#undef _CAPABILITIES_STRING_HDMI
#undef _CAPABILITIES_STRING_DP

#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 1E 1F 20 30 3E 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_DVI                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif


//--------------------------------------------------
// BEACON Option
//--------------------------------------------------
#ifndef _BEACON_GAMMA_PCM_PARTITION_SUPPORT
#define _BEACON_GAMMA_PCM_PARTITION_SUPPORT                     _ON 
#endif

#ifndef _BEACON_GAMMA_AUTO_PROCESS_SUPPORT
#define _BEACON_GAMMA_AUTO_PROCESS_SUPPORT                      _ON 
#endif

#ifndef _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT
#define _BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT                _ON 
#endif

#ifndef _BEACON_CALIBRATION_COMMAND_STATUS_EXINT_SUPPORT
#define _BEACON_CALIBRATION_COMMAND_STATUS_EXINT_SUPPORT        _ON 
#endif

#ifndef _BEACON_MONITOR_SN_SET_FUNCTION
#define _BEACON_MONITOR_SN_SET_FUNCTION                         _ON 
#endif

#ifndef _ENABLE_CANON_THREE_CT_SUPPORT
#define _ENABLE_CANON_THREE_CT_SUPPORT                          _OFF 
#endif

#ifndef _ENABLE_POWER_SAVING_MODE_SUPPORT
#define _ENABLE_POWER_SAVING_MODE_SUPPORT                       _ON 
#endif

//--------------------------------------------------
// Stack Size Option
//--------------------------------------------------
#ifndef _STACK_SIZE_TEST
#define _STACK_SIZE_TEST                                        _OFF
#endif

//-----------------------------------------------
// Definitions of External HW Setting for Beacon PCB [FPGA]
//-----------------------------------------------
#ifndef _FPGA_COLOR_ADAPTIVE_SUPPORT
#define _FPGA_COLOR_ADAPTIVE_SUPPORT                    _OFF 
#endif

#ifndef _FPGA_TEST_IAMGE_SUPPORT
#define _FPGA_TEST_IAMGE_SUPPORT                        _OFF 
#endif

#ifndef _ARM_MCU_CALIBRATION_SUPPORT
#define _ARM_MCU_CALIBRATION_SUPPORT                    _OFF 
#endif
