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
// ID Code      : RTD2014UserAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST__
#define __USER_PANEL__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
#define _HLWIN_TYPE5_MOVE_TIME                      SEC(0.01)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// IR TABLE
//----------------------------------------------------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE code tIR_INITIAL_TABLE[] =
{
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
    #include "IRRemote/NEC_DTV328.h"

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
    #include "IRRemote/SONY_B102P.h"

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
    #include "IRRemote/PHILIPS_RC6.h"

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
bit g_bHLWinRLMove = _RIGHT;
WORD g_usHLWinHPos;
WORD g_usHLWinHWidth;
WORD g_usHLWinVPos;
WORD g_usHLWinVHeight;
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
bit g_bTypeCPortControllerPowerOffFlag = _FALSE;
#endif
#endif

#if (_ENABLE_BACKLIGHT_SENSOR)
//--------------------------------------------------
// Define Backlight Sensor Device ID 
//--------------------------------------------------
typedef enum
{
    _BK_DEVICE_ID_NONE,
    _BK_DEVICE_ID_TSL2561,   
    _BK_DEVICE_ID_TSL2572,  
    _BK_DEVICE_ID_AMOUNT,
}EnumBacklightSensorDeviceID;

BYTE g_bBacklightSensorInitState = _BK_DEVICE_ID_NONE; 
BYTE uctemperaturesensor;
bit g_bBacklightSensorValueRestoreStatus = _FAIL; 
void UserTemperatureSensorHandler();
#endif

#if(_ENABLE_AMBIENTLIGHT_SENSOR)
//--------------------------------------------------
// Define Ambi Sensor Device ID 
//--------------------------------------------------
typedef enum
{
    _AMBI_DEVICE_ID_NONE,
    _AMBI_DEVICE_ID_TSL2581,   
    _AMBI_DEVICE_ID_TSL45315,  
    _AMBI_DEVICE_ID_VEML6030,
    _AMBI_DEVICE_ID_AMOUNT,
}EnumAmbiSensorDeviceID;

WORD usSensorLux=0;
WORD usAMBLux=0;    //The value which is Pre-processed by the Application 
WORD Lum_Real;      //The value that is most closest to real luminance
WORD Lum_RealFiltered = 0;  //Basis for calibration
WORD Lum_RealUsing = 0;  //Basis for Confirming the Info By DDC/CI
WORD usAmb_Light = 0;
BYTE ALC_state = 0;  //The flag that show the ALC state
BYTE pre_ALC_Auto = 0;  //Ready for switching curve once
BYTE Monitor_Restart = 1; //Restart flag 
BYTE g_bAmbiSensorInitState = _AMBI_DEVICE_ID_NONE; 
BYTE UserGetDICOMALCAmbiSensor(void);
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
void UserAdjustBacklight(WORD usBacklight);

#if(_OSD_TYPE == _BEACON_2014_OSD)

void UserAdjustBacklightDuty(WORD usBacklight);
#if ((_PRODUCT_ID_SEL != RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80))
void UserAdjustBackgroundLightPWM(void);
#endif
WORD UserGetDicomBacklightDuty(BYTE GammaTable);
WORD UserGetBacklightSensorTargetValue(void);
BYTE IsGammaOptionDICOM(BYTE GammaTable);
BYTE IsGammaOptionMCUCalibration(BYTE GammaTable);
BYTE IsGammaOptionPCCalibration(BYTE GammaTable);
BYTE IsGammaOptionHybridGamma(BYTE GammaTable);
BYTE IsGammaOptionNative(BYTE GammaTable);
BYTE IsMonoChromeorColorPanel(void);

#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)


//-------------------------------------------------------
// Dp Load Edid Related
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort);
#endif

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
void UserAdjustAudioMuteSwitch(void);
void UserAdjustAudioVolume(BYTE ucVolume);
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
void UserAdjustDCC(BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
void UserAdjustICM(BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
void UserAdjustSCM(BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
void UserAdjustColorEffectMode(void);
#endif

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
void UserAdjustContrast(WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
void UserAdjustBrightness(WORD usBrightness);
#endif

//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------

//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
void UserAdjustOD(void);
#endif

//-------------------------------------------------------
// Highlight window
//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void UserAdjustHLWinType(BYTE ucHLWinType);
void UserAdjustHLWinType5Move(void);
void UserAdjustHighLightWindowEffectSpace(void);
void UserAdjustHighLightWindowUserHander(void);

#endif

#if(_FREESYNC_OD_MEASURE == _ON)
void UserAdjustFREESYNCODMeasure(void);
#endif


//-------------------------------------------------------
// HW IR Mode
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP
//-------------------------------------------------------
#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void UserAdjustEmbeddedDpSwitch(void);
#endif

//-------------------------------------------------------
// Pixel Shift
//-------------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
void UserAdjustPixelShifting(void);
#endif

//-------------------------------------------------------
// SDRToHDR
//-------------------------------------------------------
#if(_SDR_TO_HDR_SUPPORT == _ON)
void UserAdjustSDRToHDR(bit bOn);
#endif

//-------------------------------------------------------
// DCR
//-------------------------------------------------------
#if(_DCR_SUPPORT == _ON)
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
void UserAdjustDCRTHD(void);
#endif
#endif

//-------------------------------------------------------
// Type-C Port Controller
//-------------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
void UserAjustTypeCPowerControl(EnumPowerAction enumSwitch);
#endif
#endif
#endif

//-------------------------------------------------------
// HDR
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
void UserAdjustHdrCheckDpVersion(WORD usHdrMode);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustBacklight(WORD usBacklight)
{
    //DebugMessageUart("Adjust BK = ",usBacklight);
    DebugMessageOsd("Adjust BK = ",usBacklight);
    
#if(_OSD_TYPE == _BEACON_2014_OSD)

	// for onekey Plus Display Luminance Mode or Local Enhancement Display Mode
	if((UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE) == _ON)||(UserCommonNVRamGetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE) == _ON))
	{
        UserAdjustBacklightDuty(_BACKLIGHT_MAX);
	}
    else if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        WORD usBacklightPWM;

        //DebugMessageUart("PCM_Cen:", _GET_DUT_BACKLIGHT_CENTER);
    	if(usBacklight <= _INIT_BACKLIGHT)
    	{
    		usBacklightPWM = _GET_DUT_BACKLIGHT_MIN + (DWORD)(_GET_DUT_BACKLIGHT_CENTER - _GET_DUT_BACKLIGHT_MIN)*usBacklight/_INIT_BACKLIGHT;
    	}
    	else 
    	{
    		usBacklightPWM = _GET_DUT_BACKLIGHT_CENTER + (DWORD)(_GET_DUT_BACKLIGHT_MAX - _GET_DUT_BACKLIGHT_CENTER)*(usBacklight - _INIT_BACKLIGHT)/(100 - _INIT_BACKLIGHT);
    	}
        
    	//check range must
    	if(usBacklightPWM <= _GET_DUT_BACKLIGHT_MIN)
    		usBacklightPWM = _GET_DUT_BACKLIGHT_MIN;
    	if(usBacklightPWM >= _GET_DUT_BACKLIGHT_MAX)
    		usBacklightPWM = _GET_DUT_BACKLIGHT_MAX;

#if(_BACKLIGHT_PWM_INVERSE == _ON)
        usBacklightPWM = _BACKLIGHT_MAX - usBacklightPWM;
#endif
	    DebugMessageUart("PCM Set BK>:", usBacklightPWM);

        // Adjust backlight by changing PWM duty
        PCB_BACKLIGHT_PWM(usBacklightPWM); 
    }
    else if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()))
    {
#if(_ARM_MCU_CALIBRATION_SUPPORT)
	    //DebugMessageUart("BK FPGA>:", GET_OSD_FPGA_GRAY_GAMMA());
    	if(IsGammaOptionMCUCalibration(GET_OSD_FPGA_GRAY_GAMMA()))
        {
    	    //DebugMessageUart("BK FPGA-MCU>:", _GET_USER_DICOM_BACKLIGHT);
            // Init Value
            UserAdjustBacklightDuty(_GET_USER_DICOM_BACKLIGHT);
        	ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
            ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
        }
        else
#endif
        {
            UserAdjustBacklightDuty(UserGetDicomBacklightDuty(GET_OSD_FPGA_GRAY_GAMMA()));
        }
    }
    else if(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))// is the gamma calibration with color sensor.
    {
	    //DebugMessageUart("BK Cali>:", _GET_USER_BACKLIGHT_CALIB);
        UserAdjustBacklightDuty(_GET_USER_BACKLIGHT_CALIB);
    }
#if(_ARM_MCU_CALIBRATION_SUPPORT)
	else if(IsGammaOptionMCUCalibration(GET_OSD_GAMMA()))
    {
	    //DebugMessageUart("BK MCU>:", _GET_USER_DICOM_BACKLIGHT/*_GET_USER_BACKLIGHT_MCU_CALIB*/);
        // Init Value
        UserAdjustBacklightDuty(_GET_USER_DICOM_BACKLIGHT/*_GET_USER_BACKLIGHT_MCU_CALIB*/);
    	ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
        ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
    }
#endif
    else if(IsGammaOptionNative(GET_OSD_GAMMA())) 
    {
	    //DebugMessageUart("BK Native = ", _GET_USER_NATIVE_BACKLIGHT);
        UserAdjustBacklightDuty(_GET_USER_NATIVE_BACKLIGHT);
    }
    else if(IsGammaOptionDICOM(GET_OSD_GAMMA())) 
    {
	    //DebugMessageUart("BK DICOM>:", UserGetDicomBacklightDuty(GET_OSD_GAMMA()));
        UserAdjustBacklightDuty(UserGetDicomBacklightDuty(GET_OSD_GAMMA()));
    }
    else
    {
        WORD usBacklightPWM;

    	//check range
		if(_GET_DUT_BACKLIGHT_MAX >=_BACKLIGHT_MAX)
    	{
    		_SET_DUT_BACKLIGHT_MAX(_BACKLIGHT_MAX);
    	}
    	if(_GET_DUT_BACKLIGHT_CENTER >=_BACKLIGHT_MAX)
    	{
    		_SET_DUT_BACKLIGHT_CENTER(_BACKLIGHT_MAX-2);
    	}
    	if(_GET_DUT_BACKLIGHT_MIN >=_BACKLIGHT_MAX)
    	{
    		_SET_DUT_BACKLIGHT_MIN(_BACKLIGHT_MAX-4);
    	}
    
    	if(_GET_DUT_BACKLIGHT_CENTER<= _GET_DUT_BACKLIGHT_MIN)
    	{
    		_SET_DUT_BACKLIGHT_CENTER(_GET_DUT_BACKLIGHT_MIN+1);
    	}
    	if(_GET_DUT_BACKLIGHT_MAX <= _GET_DUT_BACKLIGHT_CENTER)
    	{
    		_SET_DUT_BACKLIGHT_MAX(_GET_DUT_BACKLIGHT_CENTER+1);
    	}

        //DebugMessageUart("DUT_MIN:", _GET_DUT_BACKLIGHT_MIN);
        //DebugMessageUart("DUT_Cen:", _GET_DUT_BACKLIGHT_CENTER);
        //DebugMessageUart("DUT_MAX:", _GET_DUT_BACKLIGHT_MAX);
        if(usBacklight == _BACKLIGHT_MAX)
        {
            // RTD Tool input PWM 0 ~ 255 
            // for Input Value usBacklight is 8Bit PWM 0 ~ 255 or 12Bit PWM 0 ~ 4095
            usBacklight = 100;
        }
        if(usBacklight > 100)
        {
            usBacklight = 50;
        }

    	if(usBacklight <= _INIT_BACKLIGHT)
    	{
    		usBacklightPWM = _GET_DUT_BACKLIGHT_MIN + (DWORD)(_GET_DUT_BACKLIGHT_CENTER - _GET_DUT_BACKLIGHT_MIN)*usBacklight/_INIT_BACKLIGHT;
    	}
    	else 
    	{
    		usBacklightPWM = _GET_DUT_BACKLIGHT_CENTER + (DWORD)(_GET_DUT_BACKLIGHT_MAX - _GET_DUT_BACKLIGHT_CENTER)*(usBacklight - _INIT_BACKLIGHT)/(100 - _INIT_BACKLIGHT);
    	}
        
    	//check range must
    	if(usBacklightPWM <= _GET_DUT_BACKLIGHT_MIN)
    		usBacklightPWM = _GET_DUT_BACKLIGHT_MIN;
    	if(usBacklightPWM >= _GET_DUT_BACKLIGHT_MAX)
    		usBacklightPWM = _GET_DUT_BACKLIGHT_MAX;

#if(_BACKLIGHT_PWM_INVERSE == _ON)
        usBacklightPWM = _BACKLIGHT_MAX - usBacklightPWM;
#endif
	    DebugMessageUart("Set BK>:", usBacklightPWM);

        // Adjust backlight by changing PWM duty
        PCB_BACKLIGHT_PWM(usBacklightPWM); 
    }

#else

#if(_BACKLIGHT_PWM_INVERSE == _ON)
    usBacklight = _BACKLIGHT_MAX - usBacklight;
#endif

    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usBacklight);
#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)
}
#if (_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)
//--------------------------------------------------
// Description  : Adjust Backgroundlight PWM
// Input Value  : usBacklight(0 ~ _BACKLIGHT_MAX)
// Output Value : None
//--------------------------------------------------
void UserAdjustRGBLightPWM(void)
{        
    WORD usPWMTemp = 0;

    if(GET_DDCCI_RGB_LIGHT_MODE() == _RGB_LIGHT_OFF)
    {
        usPWMTemp = 0;
    }
    else if(GET_DDCCI_RGB_LIGHT_MODE() == _RGB_LIGHT_1)
    {
        // LED lamp Off Switch to low light (PWM == 200) flashing
        //usPWMTemp = _BACKLIGHT_MIN;
        usPWMTemp = _BACKLIGHT_MIN + ((_BACKLIGHT_CENTER - _BACKLIGHT_MIN) / 2);
    }   
    else if(GET_DDCCI_RGB_LIGHT_MODE() == _RGB_LIGHT_2)
    {
        usPWMTemp = _BACKLIGHT_CENTER;
    }     
    else if(GET_DDCCI_RGB_LIGHT_MODE() == _RGB_LIGHT_3)
    {
        // Avoid high temperature problem of LED lamp
        //usPWMTemp = _BACKLIGHT_MAX;
        usPWMTemp = _BACKLIGHT_MAX - ((_BACKLIGHT_MAX - _BACKLIGHT_CENTER)/10);
    }
    switch(GET_DDCCI_RGB_MODE())
        case _RGB_LIGHT_R:
            if(GET_DDCCI_RGB_LIGHT_MODE() != _OFF)
            {
                PCB_RED_LIGHT_EN(_ON);
            }
            DebugMessageUart("Set red_LIGHT PWM:", usPWMTemp);

            // Adjust Background light by changing PWM duty
            PCB_RED_LIGHT_PWM(usPWMTemp);
            break;
        case _RGB_LIGHT_B:
            if(GET_DDCCI_RGB_LIGHT_MODE() != _OFF)
            {
                PCB_BLUE_LIGHT_EN(_ON);
            }
            DebugMessageUart("Set blue_LIGHT PWM:", usPWMTemp);

            // Adjust Background light by changing PWM duty
            PCB_BLUE_LIGHT_PWM(usPWMTemp);
            break;
        case _RGB_LIGHT_G:
            if(GET_DDCCI_RGB_LIGHT_MODE() != _OFF)
            {
                PCB_GREEN_LIGHT_EN(_ON);
            }
            DebugMessageUart("Set green_LIGHT PWM:", usPWMTemp);

            // Adjust Background light by changing PWM duty
            PCB_GREEN_LIGHT_PWM(usPWMTemp);
            break;
}
#endif
#if(_OSD_TYPE == _BEACON_2014_OSD)
//--------------------------------------------------
// Description  : Adjust backlight PWM
// Input Value  : usBacklight(0 ~ _BACKLIGHT_MAX)
// Output Value : None
//--------------------------------------------------
void UserAdjustBacklightDuty(WORD usBacklight)
{    
    WORD usTemp = 0;

	//check range must
    if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
	{
		if(usBacklight <= 0)
		{
			usBacklight = 0;
		}
	}
	else
	{
		if(usBacklight <= _BACKLIGHT_MIN)
		{
			usBacklight = _BACKLIGHT_MIN;
		}
	}
	if(usBacklight >= _BACKLIGHT_MAX)
	{
		usBacklight = _BACKLIGHT_MAX;
	}

#if(_BACKLIGHT_PWM_INVERSE == _ON)
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
    usBacklight = _BACKLIGHT_MAX - usBacklight;
#endif
#endif
    //DebugMessageUart("Set PWM:", usBacklight);
    DebugMessageOsd("Set PWM:", usBacklight);
    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usBacklight);
}
#if ((_PRODUCT_ID_SEL != RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80))
//--------------------------------------------------
// Description  : Adjust Backgroundlight PWM
// Input Value  : usBacklight(0 ~ _BACKLIGHT_MAX)
// Output Value : None
//--------------------------------------------------
void UserAdjustBackgroundLightPWM(void)
{        
    WORD usPWMTemp = 0;

    if(GET_OSD_BACKGROUND_LIGHT_MODE() == _AMB_LIGHT_OFF)
    {
        usPWMTemp = 0;
    }
    else if(GET_OSD_BACKGROUND_LIGHT_MODE() == _AMB_LIGHT_1)
    {
        // LED lamp Off Switch to low light (PWM == 200) flashing
        //usPWMTemp = _BACKLIGHT_MIN;
        usPWMTemp = _BACKLIGHT_MIN + ((_BACKLIGHT_CENTER - _BACKLIGHT_MIN) / 2);
    }   
    else if(GET_OSD_BACKGROUND_LIGHT_MODE() == _AMB_LIGHT_2)
    {
        usPWMTemp = _BACKLIGHT_CENTER;
    }     
    else if(GET_OSD_BACKGROUND_LIGHT_MODE() == _AMB_LIGHT_3)
    {
        // Avoid high temperature problem of LED lamp
        //usPWMTemp = _BACKLIGHT_MAX;
        usPWMTemp = _BACKLIGHT_MAX - ((_BACKLIGHT_MAX - _BACKLIGHT_CENTER)/10);
    }

#if 0//(_BACKLIGHT_PWM_INVERSE == _ON)
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
    usPWMTemp = _BACKLIGHT_MAX - usPWMTemp;
#endif
#endif

    if(GET_OSD_BACKGROUND_LIGHT_MODE() != _OFF)
    {
        PCB_BACKGROUND_LIGHT_EN(_ON);
    }
    DebugMessageUart("Set_LIGHT PWM:", usPWMTemp);

    // Adjust Background light by changing PWM duty
    PCB_BACKGROUND_LIGHT_PWM(usPWMTemp);
}
#endif
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsGammaOptionDICOM(BYTE GammaTable)
{
    GammaTable = GammaTable;
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        return 0;
    }
#if((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)/*&&(_FPGA_COLOR_ADAPTIVE_SUPPORT)*/)
	return (GammaTable == _GAMMA_20);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
	return (GammaTable == _GAMMA_26);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
	return ((GammaTable >= _GAMMA_DICOM200)&&(GammaTable <= _GAMMA_DICOM600));
#else
	return (GammaTable == _GAMMA_26);
#endif    
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsGammaOptionDICOMALC(BYTE GammaTable)
{
    GammaTable = GammaTable;
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        return 0;
    }
#if((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)/*&&(_FPGA_COLOR_ADAPTIVE_SUPPORT)*/)
	return (GammaTable == _GAMMA_20);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
	return (GammaTable == _GAMMA_26);
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
	return (GammaTable == _GAMMA_DICOM450);
#else
    return 0;
#endif    
}
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsGammaOptionMCUCalibration(BYTE GammaTable)
{
    GammaTable = GammaTable;
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        return 0;
    }
#if((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)/*&&(_ARM_MCU_CALIBRATION_SUPPORT)*/)
	return (GammaTable == _GAMMA_22);
#else
    return 0;
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsGammaOptionPCCalibration(BYTE GammaTable)
{
    GammaTable = GammaTable;
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        return 0;
    }
#if((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)&&(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT))
	return (GammaTable == _GAMMA_24);
#elif((_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)&&(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT))
	return (GammaTable == _GAMMA_CALIB);
#elif((_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)&&(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT))
	return (GammaTable == _GAMMA_CALIB);
#else
    return 0;
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsGammaOptionHybridGamma(BYTE GammaTable)
{
    GammaTable = GammaTable;
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        return 0;
    }
#if((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)&&(_FPGA_COLOR_ADAPTIVE_SUPPORT))
	return (GammaTable == _GAMMA_26);
#else
    return 0;
#endif
}
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsGammaOptionNative(BYTE GammaTable)
{
    GammaTable = GammaTable;
	if(UserCommonNVRamGetSystemData(_GAMMA_NATIVE_SET_MODE) == _ON)
	{
        if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
        {
            return 0;
        }
		return ((GammaTable == _GAMMA_OFF)||(GET_COLOR_TEMP_TYPE() == _CT_SRGB));
	}
	else
	{
	    return 0;
	}
}
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE IsMonoChromeorColorPanel(void)
{
    return MODEL_COLOR_TYPE;// (MODEL_COLOR_TYPE != M_COLOR);
}
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD UserGetDicomBacklightDuty(BYTE GammaTable)
{
    WORD usBacklightPWM;

#if 1// _CT_SRGB is Native
    if(IsGammaOptionNative(GET_OSD_GAMMA()))
	{
	    DebugMessageUart("Get CT Native>:", _GET_USER_NATIVE_BACKLIGHT);
		usBacklightPWM = _GET_USER_NATIVE_BACKLIGHT;
        return usBacklightPWM;
	}
#endif

    GammaTable = GammaTable;
	switch(GammaTable)
	{
		case _GAMMA_OFF:
			if(IsGammaOptionNative(GET_OSD_GAMMA()))
			{
			    DebugMessageUart("Get Native>:", _GET_USER_NATIVE_BACKLIGHT);
				usBacklightPWM = _GET_USER_NATIVE_BACKLIGHT;
			}
			else
			{
			    DebugMessageUart("Get G2.2>:", _GET_DUT_BACKLIGHT_CENTER);
				usBacklightPWM = _GET_DUT_BACKLIGHT_CENTER;
			}
			break;
            
#if(_GAMMA_TYPE ==_GAMMA_NAME_G22_DICOM_USER_CALIB)
		case _GAMMA_18:
		    DebugMessageUart("Get G2.2>:", _GET_DUT_BACKLIGHT_CENTER);
			usBacklightPWM = _GET_DUT_BACKLIGHT_CENTER;
			break;

		default:   
		case _GAMMA_20:
		    DebugMessageUart("Get DICOM>:", _GET_USER_DICOM_BACKLIGHT);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT;
			break;

		case _GAMMA_22:
		    DebugMessageUart("Get MCU>:", _GET_USER_DICOM_BACKLIGHT/*_GET_USER_BACKLIGHT_MCU_CALIB*/);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT/*_GET_USER_BACKLIGHT_MCU_CALIB*/;
			break;
			
		case _GAMMA_24:
		    DebugMessageUart("Get Calib>:", _GET_USER_BACKLIGHT_CALIB);
			usBacklightPWM = _GET_USER_BACKLIGHT_CALIB;
			break;
            
#elif(_GAMMA_TYPE ==_GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
		default:   
		case _GAMMA_18:
		case _GAMMA_20:
		case _GAMMA_22:
		case _GAMMA_24:
		    DebugMessageUart("Get G2.2>:", _GET_DUT_BACKLIGHT_CENTER);
			usBacklightPWM = _GET_DUT_BACKLIGHT_CENTER;
			break;

		case _GAMMA_26:
		    DebugMessageUart("Get DICOM>:", _GET_USER_DICOM_BACKLIGHT);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT;
			break;

		case _GAMMA_CALIB:
		    DebugMessageUart("Get Calib>:", _GET_USER_BACKLIGHT_CALIB);
			usBacklightPWM = _GET_USER_BACKLIGHT_CALIB;
			break;

#elif(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
		default:   
		case _GAMMA_18:
		    DebugMessageUart("Get G2.2>:", _GET_DUT_BACKLIGHT_CENTER);
			usBacklightPWM = _GET_DUT_BACKLIGHT_CENTER;
			break;

		case _GAMMA_DICOM200:
		    DebugMessageUart("Get D200>:", _GET_USER_DICOM_BACKLIGHT_200);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_200;
			break;
		case _GAMMA_DICOM250:
		    DebugMessageUart("Get D250>:", _GET_USER_DICOM_BACKLIGHT_250);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_250;
			break;            
		case _GAMMA_DICOM300:
		    DebugMessageUart("Get D300>:", _GET_USER_DICOM_BACKLIGHT_300);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_300;
			break;
		case _GAMMA_DICOM350:
		    DebugMessageUart("Get D350>:", _GET_USER_DICOM_BACKLIGHT_350);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_350;
			break;
		case _GAMMA_DICOM400:
		    DebugMessageUart("Get D400>:", _GET_USER_DICOM_BACKLIGHT_400);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_400;
			break;
		case _GAMMA_DICOM450:
		    DebugMessageUart("Get D450>:", _GET_USER_DICOM_BACKLIGHT_450);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_450;
			break;            
		case _GAMMA_DICOM500:
		    DebugMessageUart("Get D500>:", _GET_USER_DICOM_BACKLIGHT_500);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_500;
			break;
		case _GAMMA_DICOM550:
		    DebugMessageUart("Get D550>:", _GET_USER_DICOM_BACKLIGHT_550);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_550;
			break;
		case _GAMMA_DICOM600:
		    DebugMessageUart("Get D600>:", _GET_USER_DICOM_BACKLIGHT_600);
			usBacklightPWM = _GET_USER_DICOM_BACKLIGHT_600;
			break;

		case _GAMMA_CALIB:
		    DebugMessageUart("Get Calib>:", _GET_USER_BACKLIGHT_CALIB);
			usBacklightPWM = _GET_USER_BACKLIGHT_CALIB;
			break;
#else
#warning "!!!Please Check Gamma define"

#endif

	}
   return usBacklightPWM;
}
#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)

//----------------------------------------------------------------------------
// Not Kernel Related Function
//----------------------------------------------------------------------------

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : ucInputPort
// Output Value : Edid Index
//--------------------------------------------------
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort)
{
    BYTE ucIndex = 0;
    BYTE ucDpResolution = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((GET_OSD_FREE_SYNC_STATUS() == _ON))
    {
        ucIndex += ((_DP_HDR10_SUPPORT == _ON) ? 0x06 : 0x03);
    }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    if((UserInterfaceHDRGetHDR10ModeStatus(ucInputPort) != _HDR10_MODE_OFF))
    {
        ucIndex += 0x03;
    }
#endif

 	DebugMessageUart("Load EDID:", ucIndex);
    
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
            break;
        case _D1_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D1_SELECT);
            break;
        case _D2_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D2_SELECT);
            break;
        case _D6_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D6_SELECT);
            break;
        default:
            break;
    }

    switch(ucDpResolution)
    {
        case _DP_EDID_1080P:
            break;

        case _DP_EDID_2560_1440:
            ucIndex += 0x01;
            break;

        case _DP_EDID_4K2K_60HZ:
            ucIndex += 0x02;
            break;

        default:
            break;
    }

    return ucIndex;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mute/Unmute Aduio Volume
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserAdjustAudioMuteSwitch(void)
{
    SysAudioMuteProc(UserInterfaceGetAudioMuteStatus());
}

//--------------------------------------------------
// Description  : Adjust Aduio Volume
// Input Value  : ucVolume
// Output Value : Node
//--------------------------------------------------
void UserAdjustAudioVolume(BYTE ucVolume)
{
    ScalerAudioDigitalAdjustVolume(UserAdjustAudioVolumeMapping(ucVolume));
}

//--------------------------------------------------
// Description  : OSD Volume Mapping to Real Value
// Input Value  : usVolume
// Output Value : usVolume
//--------------------------------------------------
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
    {
        return (UserCommonAdjustPercentToRealValue(ucVolume, _LINE_IN_VOLUME_MAX, _LINE_IN_VOLUME_MIN, _LINE_IN_VOLUME_CENTER));
    }
    else
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    {
        return (UserCommonAdjustPercentToRealValue(ucVolume, _DIGITAL_VOLUME_MAX, _DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_CENTER));
    }
}
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set DCC Table
// Input Value  : Request DCC Table
// Output Value : None
//--------------------------------------------------
void UserAdjustDCC(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorDCCAdjust(tDCC_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_DCC_FUNCTION == _ON)


#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set ICM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustICM(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorICMLoadTable(tICM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_ICM_SUPPORT == _ON)

#if(_SCM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SCM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSCM(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorSCMLoadTable(tSCM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_SCM_SUPPORT == _ON)

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustColorEffectMode(void)
{
    BYTE ucIndex = 0;
    BYTE ucBackupSixColor = 0;
    BYTE ucBackupHue = 0;
    BYTE ucBackupSaturation = 0;

    ucBackupSixColor = GET_OSD_SIX_COLOR();
    ucBackupHue = GET_OSD_SIX_COLOR_HUE();
    ucBackupSaturation = GET_OSD_SIX_COLOR_SATURATION();

    switch(GET_OSD_COLOR_EFFECT())
    {
        case _COLOREFFECT_STANDARD:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif
            break;

        case _COLOREFFECT_USER:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(ucIndex);
                ScalerColorSixColorAdjust(ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial();
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(GET_OSD_COLOR_EFFECT());
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(GET_OSD_COLOR_EFFECT());
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(GET_OSD_COLOR_EFFECT());
#endif


#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_ON);
#endif
            break;

        default:
            break;
    }

    SET_OSD_SIX_COLOR(ucBackupSixColor);
    SET_OSD_SIX_COLOR_HUE(ucBackupHue);
    SET_OSD_SIX_COLOR_SATURATION(ucBackupSaturation);
}
#endif // End of #if(_SIX_COLOR_SUPPORT == _ON)

#if(_CONTRAST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Contrast
// Input Value  : 12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustContrast(WORD usContrast)
{
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    WORD pusData[6] = {0};

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    pusData[3] = 0x800;
    pusData[4] = 0x800;
    pusData[5] = 0x800;
#else
    pusData[3] = 0x80;
    pusData[4] = 0x80;
    pusData[5] = 0x80;
#endif

#else
    WORD pusData[3] = {0};
#endif

#if 1
    if(IsGammaOptionDICOM(GET_OSD_GAMMA()))
    {
        usContrast = _CONTRAST_CENTER;
    }
#endif

	// _CONTRAST_MIN = 1248  Step = 16
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_1)
    {  
        usContrast = (((_CONTRAST_CENTER - _CONTRAST_MIN) / 2) + _CONTRAST_MIN); 
    }
        
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048);

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // 10-bit Panel
        pusData[0] = UserCommonAdjust10bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust10bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust10bitPanelCompensate(pusData[2]);
    }
#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
    else if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        pusData[0] = UserCommonAdjust6bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust6bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust6bitPanelCompensate(pusData[2]);
    }
#endif

#else
    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 128);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 128);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 128);

#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        pusData[0] = UserCommonAdjust6bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust6bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust6bitPanelCompensate(pusData[2]);
    }
#endif
#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
        ScalerColorContrastAdjust(_CONTRAST_COEF_B, &pusData[3]);
    }
    else
    {
        ScalerColorContrastAdjust(_CONTRAST_COEF_B, pusData);
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, &pusData[3]);
    }
#else
    ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
#endif

    ScalerColorContrastEnable(_FUNCTION_ON);
}
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Brightness
// Input Value  : 10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustBrightness(WORD usBrightness)
{
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    WORD pusData[6] = {0};

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
    pusData[3] = 0x200;
    pusData[4] = 0x200;
    pusData[5] = 0x200;
#else
    pusData[3] = 0x80;
    pusData[4] = 0x80;
    pusData[5] = 0x80;
#endif

#else
    WORD pusData[3] = {0};
#endif

    pusData[0] = usBrightness;
    pusData[1] = usBrightness;
    pusData[2] = usBrightness;

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, &pusData[3]);
    }
    else
    {
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, pusData);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, &pusData[3]);
    }
#else
    ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
#endif

    ScalerColorBrightnessEnable(_FUNCTION_ON);
}
#endif


#if(_GLOBAL_HUE_SATURATION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat)  // for OSD Adjust & Dianliang:  Display Off & ON
{
    UserCommonAdjustGlobalHueSat(_DEFAULT_HUE - shHue, usSat);
}
#endif  // Enf of #if(_GLOBAL_HUE_SATURATION == _ON)

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load OD LUT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustOD(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
    {
        ScalerODLoadLUT(tOD_FREESYNC_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
    else
#endif
    {
        ScalerODLoadLUT(tOD_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust High Light Window
// Input Value  : HLWinType
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType(BYTE ucHLWinType)
{
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

    if(ucHLWinType == _HL_WIN_OFF)
    {
        return;
    }

    if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
    {
        g_usHLWinHPos = 0;
    }
    else
    {
        g_usHLWinHPos = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
    }

    if(GET_MDOMAIN_OUTPUT_VHEIGHT() == _PANEL_DV_HEIGHT)
    {
#if ((_PRODUCT_ID_SEL == RTD2785TM_C310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM)||\
     (_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))
        g_usHLWinVPos = 0;
#elif ((_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)||\
   (_PRODUCT_ID_SEL == RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM_DBI)||(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI))
        g_usHLWinVPos = 16;
#endif
    
    }
    else
    {
        g_usHLWinVPos = (_PANEL_DV_HEIGHT - GET_MDOMAIN_OUTPUT_VHEIGHT()) / 2;
    }
    switch(ucHLWinType)
    {
        case _HL_WIN_1:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
            
            break;

        case _HL_WIN_2:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_3:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;

            break;

        case _HL_WIN_4:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;
            g_usHLWinHPos = ((GET_MDOMAIN_OUTPUT_HWIDTH() - g_usHLWinHWidth) / 2) + ((_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2) - 1;
            g_usHLWinVPos = (GET_MDOMAIN_OUTPUT_VHEIGHT() - g_usHLWinVHeight) / 2 - 1;

            break;

        case _HL_WIN_5:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 6;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
            g_usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() - g_usHLWinHWidth) / 2;

            ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

            break;

        default:

            break;
    }
    
    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NONE);
}

//--------------------------------------------------
// Description  : High Light Window Type5 Move
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType5Move(void)
{
    WORD usNonFullScreenOffset = 0;

    if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
    {
        // Full screen
        usNonFullScreenOffset = 0;
    }
    else
    {
        // Non full screen
        usNonFullScreenOffset = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
    }

    if(g_bHLWinRLMove == _RIGHT)
    {
        g_usHLWinHPos++;

        if((GET_MDOMAIN_OUTPUT_HWIDTH() + usNonFullScreenOffset) <= (g_usHLWinHPos + g_usHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_bHLWinRLMove = _LEFT;
            g_usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() + usNonFullScreenOffset) - (g_usHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }
    else // _LEFT
    {
        g_usHLWinHPos--;

        if(g_usHLWinHPos <= usNonFullScreenOffset)
        {
            g_bHLWinRLMove = _RIGHT;
            g_usHLWinHPos = usNonFullScreenOffset;
        }
    }

    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NO_POLLING);

    ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
}

//--------------------------------------------------
// Description  : Adjust All High Light Window Effect Space
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHighLightWindowEffectSpace(void)
{
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
    ScalerColorHLWBRICTSAdjust(_BRI_CON_B_ON_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_DCC_FUNCTION == _ON)
    ScalerColorHLWDCCAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_GAMMA_FUNCTION == _ON)
    ScalerColorHLWOutputGammaAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
    ScalerColorHLWSRGBAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_IAPS_SUPPORT == _ON)
    ScalerColorHLWIAPSGainAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_ICM_SUPPORT == _ON)
    ScalerColorHLWICMAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
    ScalerColorHLWDCRAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWUltraVividAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_YPEAKING_SUPPORT == _ON)
    ScalerColorHLWYpeakingAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorHLWPanelUniformityAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_PCM_FUNCTION == _ON)
    ScalerColorHLWPCMAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_RGB_3D_GAMMA == _ON)
    ScalerColorHLWRGB3DGammaAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif
}

#if(_OSD_TYPE == _BEACON_2014_OSD)
//--------------------------------------------------
// Description  : High Light Window Type Move HVPos
// Input Value  : usHLWinHPosition usHLWinVPosition
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinTypeCus1Move(WORD usHLWinHPosition,WORD usHLWinVPosition)
{
    WORD usNonFullScreenOffset = 0;

    // usHLWinHPosition
    {
        g_usHLWinHPos = usHLWinHPosition;

        if(g_usHLWinHPos <= usNonFullScreenOffset)
        {
            g_usHLWinHPos = usNonFullScreenOffset;
        }

        if((_PANEL_DH_WIDTH + usNonFullScreenOffset) <= (g_usHLWinHPos + g_usHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_usHLWinHPos = (_PANEL_DH_WIDTH + usNonFullScreenOffset) - (g_usHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }

    // usHLWinVPosition
    {
        g_usHLWinVPos = usHLWinVPosition;
        
        if(g_usHLWinVPos <= usNonFullScreenOffset)
        {
            g_usHLWinVPos = usNonFullScreenOffset;
        }
        
        if((_PANEL_DV_HEIGHT + usNonFullScreenOffset) <= (g_usHLWinVPos + g_usHLWinVHeight + _HL_WIN_BORDER_SIZE))
        {
            g_usHLWinVPos = (_PANEL_DV_HEIGHT+ usNonFullScreenOffset) - (g_usHLWinVHeight + _HL_WIN_BORDER_SIZE);
        }
    }
        
    ScalerColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 64, 64, 64);
    ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON);
    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NO_POLLING);

}

//--------------------------------------------------
// Description  : High Light Window Type Move HVPos
// Input Value  : usHLWinHPosition usHLWinVPosition
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinTypeCus2Move(SWORD usHLWinHPosition,SWORD usHLWinVPosition)
{
    WORD usNonFullScreenOffset = 0;
    SWORD usScreenOffset;

    // usHLWinHPosition
    {
        //g_usHLWinHPos = usHLWinHPosition;
        usScreenOffset = ((SWORD)g_usHLWinHPos + usHLWinHPosition);
		if(usScreenOffset < 0)
		{
			g_usHLWinHPos = 0;
		}
		else
		{
	        g_usHLWinHPos = usScreenOffset;
		}

        if(g_usHLWinHPos <= usNonFullScreenOffset)
        {
            g_usHLWinHPos = usNonFullScreenOffset;
        }

        if((_PANEL_DH_WIDTH + usNonFullScreenOffset) <= (g_usHLWinHPos + g_usHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_usHLWinHPos = (_PANEL_DH_WIDTH + usNonFullScreenOffset) - (g_usHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }

    // usHLWinVPosition
    {
        //g_usHLWinVPos = usHLWinVPosition;
        usScreenOffset = ((SWORD)g_usHLWinVPos + usHLWinVPosition);
		if(usScreenOffset < 0)
		{
			g_usHLWinVPos = 0;
		}
		else
		{
	        g_usHLWinVPos = usScreenOffset;
		}
		
        if(g_usHLWinVPos <= usNonFullScreenOffset)
        {
            g_usHLWinVPos = usNonFullScreenOffset;
        }
        
        if((_PANEL_DV_HEIGHT + usNonFullScreenOffset) <= (g_usHLWinVPos + g_usHLWinVHeight + _HL_WIN_BORDER_SIZE))
        {
            g_usHLWinVPos = (_PANEL_DV_HEIGHT+ usNonFullScreenOffset) - (g_usHLWinVHeight + _HL_WIN_BORDER_SIZE);
        }
    }
        
    ScalerColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 64, 64, 64);
    ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON);
    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NO_POLLING);

}

//--------------------------------------------------
// Description  : Adjust User High Light Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHighLightWindowUserHander(void)
{
    DebugMessageUart(" HLW Hander= ", GET_OSD_HLWIN_TYPE());
	// HLW Type Adjust Flag
	if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
	{
		// Off Reading Report Mode
		SET_OSD_READING_REPORT_MODE(_READING_REPORT_OFF);
	}
	else
	{
		if(UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE) == _ON)
		{
			// Off onekey Plus Display Luminance Mode
			UserCommonNVRamSetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE, _OFF);
		}

		if(GET_OSD_HLWIN_TYPE() > _HL_WIN_1)
		{
			// Off Reading Report Mode
			SET_OSD_READING_REPORT_MODE(_READING_REPORT_OFF);
		}
	}
	UserCommonNVRamSaveSystemData();

    // Adjust HLWIN
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        UserAdjustHLWinType(_HL_WIN_OFF);
        ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
    }
    else
    {
    DebugMessageUart("GET_OSD_HLWIN_TYPE()", GET_OSD_HLWIN_TYPE());
    
        UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
        ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
    }

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif
#endif

#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCNormalizeFactorAdjust();
#endif					
}
#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set FREESYNC OD Measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void UserAdjustFREESYNCODMeasure(void)
{
    // Set Backlight
    UserAdjustBacklight(100);

    // Enable Backlight
    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

    // Disable OSD
    ScalerOsdDisableOsd();

    // Disable D-domain Pattern Gen.
    ScalerDDomainPatternGenEnable(_DISABLE);

    // According FREESYNC setting to set accurate Htotal/ Dclk
    ScalerMDomainFREESYNCODSetDisplayFormat(((WORD)_PANEL_DH_TOTAL), ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ), ((WORD)_PANEL_FREESYNC_MIN_FRAME_RATE));

    while(_TRUE)
    {
        ScalerDebug();
        ScalerDDomainFREESYNCODSetBackgroundGrayLevel();
    }
}
#endif


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : Set IR Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjusIR(void)
{
    ScalerIRHWModeDecoder(tIR_INITIAL_TABLE, GET_CURRENT_BANK_NUMBER());
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : Set embedded DP switch status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustEmbeddedDpSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D0_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D0_INPUT_PORT);
        }
        return;
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D1_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D1_INPUT_PORT);
        }
        return;
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D2_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D2_INPUT_PORT);
        }
        return;
    }
#endif
}
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pixel orbiting step as following
//  -2->
// ^    |
// |    3
// 1    |
// |    v
// < -0- <-7-
//      |     |
//      4     6
//      |     |
//      v -5->
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelShifting(void)
{
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
    BYTE ucPixelShift = 0;

    WORD usVdelay = 0;
    WORD usHdelay = 0;
    BYTE ucVstep = 2;
    BYTE ucHstep = 2;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        ucVstep = (ucVstep + 1) & 0xFE;
    }
#endif

    ScalerGlobalWatchDog(_DISABLE);

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usHdelay = ScalerVgaTopGetCaptureHDelay();
        usVdelay = ScalerVgaTopGetCaptureVDelay();
    }
    else
#endif
    {
        usHdelay = ScalerVgipGetCaptureHDelay();
        usVdelay = ScalerVgipGetCaptureVDelay();
    }

    for(ucPixelShift = 0; ucPixelShift < 8; ucPixelShift++)
    {
        ScalerTimerDelayXms(200);

        switch(ucPixelShift)
        {
            case 0: // _PIXEL0_TURN_LEFT:
            case 7: // _PIXEL1_TURN_LEFT:
                usHdelay += ucHstep;
                break;

            case 2: // _PIXEL0_TURN_RIGHT:
            case 5: // _PIXEL1_TURN_RIGHT:
                if(usHdelay >= ucHstep)
                {
                    usHdelay -= ucHstep;
                }
                else
                {
                    usHdelay = 0;
                }
                break;

            case 1: // _PIXEL0_TURN_UP:
            case 6: // _PIXEL1_TURN_UP:
                usVdelay += ucVstep;
                break;

            case 3: // _PIXEL0_TURN_DOWN:
            case 4: // _PIXEL1_TURN_DOWN:
                if(usVdelay >= ucVstep)
                {
                    usVdelay -= ucVstep;
                }
                else
                {
                    usVdelay = 0;
                }
                break;

            default:
                break;
        }

#if(_VGA_SUPPORT == _ON)
        if(SysSourceGetSourceType() == _SOURCE_VGA)
        {
            ScalerVgaTopSetCaptureHDelay(usHdelay);
            ScalerVgaTopSetCaptureVDelay(usVdelay);
            ScalerVgaTopDoubleBufferApply();
        }
        else
#endif
        {
            ScalerVgipSetCaptureHDelay(usHdelay);
            ScalerVgipSetCaptureVDelay(usVdelay);
            ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);
        }
    }

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerGlobalWatchDog(_ENABLE);

#endif

#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
    BYTE ucPixelShift = 0;
    WORD usDHstart = ScalerMDomainGetDisplayTimingGenActiveRegionHStart();
    WORD usDHend = ScalerMDomainGetDisplayTimingGenActiveRegionHEnd();
    WORD usDVstart = ScalerMDomainGetDisplayTimingGenActiveRegionVStart();
    WORD usDVend = ScalerMDomainGetDisplayTimingGenActiveRegionVEnd();
    WORD usDVBGstart = GET_MDOMAIN_OUTPUT_VBSTART();
    WORD usDVBGend = GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT();
    WORD usDisplayHstart = usDHstart;
    WORD usDisplayVstart = usDVstart;

    // usDVBGstart/usDVBGend
    ScalerMDomainSetDisplayTimingGenBackgroundVStart(HIBYTE(usDVBGstart), LOBYTE(usDVBGstart), _DB_APPLY_NONE);
    ScalerMDomainSetDisplayTimingGenBackgroundVEnd(HIBYTE(usDVBGend), LOBYTE(usDVBGend), _DB_APPLY_NO_POLLING);

    // capture H start/end
    ScalerMDomainSetCaptureWindowHStart(HIBYTE(usDHstart), LOBYTE(usDHstart));
    ScalerMDomainSetCaptureWindowHEnd(HIBYTE(usDHend), LOBYTE(usDHend));
    // capture V start/end
    ScalerMDomainSetCaptureWindowVStart(HIBYTE(usDVstart), LOBYTE(usDVstart));
    ScalerMDomainSetCaptureWindowVEnd(HIBYTE(usDVend), LOBYTE(usDVend));

    ScalerMDomainSetCaptureWindowEnable(_ENABLE);

    for(ucPixelShift = 0; ucPixelShift < 8; ucPixelShift++)
    {
        ScalerTimerDelayXms(200);
        switch(ucPixelShift)
        {
            // H <-
            case 0: // _PIXEL0_TURN_LEFT:
                usDHend -= 1;
                usDisplayHstart -= 1;
                break;

            // V ^
            case 1: // _PIXEL0_TURN_UP:
                usDVstart += 1;
                usDVBGstart += 1;
                usDVBGend += 1;
                break;

            // H ->
            case 2: // _PIXEL0_TURN_RIGHT:
                usDHend += 1;
                usDisplayHstart += 1;
                break;

            // V v
            case 3: // _PIXEL0_TURN_DOWN:
                usDVstart -= 1;
                usDVBGstart -= 1;
                usDVBGend -= 1;
                break;

            // V v
            case 4: // _PIXEL1_TURN_DOWN:
                usDisplayVstart += 1;
                usDVstart += 1;
                break;

            // H ->
            case 5: // _PIXEL1_TURN_RIGHT:
                usDisplayHstart += 1;
                usDHstart += 1;
                break;

            // V ^
            case 6: // _PIXEL1_TURN_UP:
                usDisplayVstart -= 1;
                usDVstart -= 1;
                break;

            // H <-
            case 7: // _PIXEL1_TURN_LEFT:
                usDisplayHstart -= 1;
                usDHstart -= 1;
                break;

            default:
                break;
        }

        switch(ucPixelShift)
        {
            case 0: // _PIXEL0_TURN_LEFT:
            case 2: // _PIXEL0_TURN_RIGHT:
            case 5: // _PIXEL1_TURN_RIGHT:
            case 7: // _PIXEL1_TURN_LEFT:
                // Display H active start setting
                ScalerMDomainSetDisplayTimingGenActiveRegionHStart(HIBYTE(usDisplayHstart), LOBYTE(usDisplayHstart), _DB_APPLY_POLLING);
                // Capture window H start setting
                ScalerMDomainSetCaptureWindowHStart(HIBYTE(usDHstart), LOBYTE(usDHstart));
                // Capture window H end setting
                ScalerMDomainSetCaptureWindowHEnd(HIBYTE(usDHend), LOBYTE(usDHend));

                break;

            case 1: // _PIXEL0_TURN_UP:
            case 3: // _PIXEL0_TURN_DOWN:
            case 4: // _PIXEL1_TURN_DOWN:
            case 6: // _PIXEL1_TURN_UP:
                // Display V active start setting
                ScalerMDomainSetDisplayTimingGenActiveRegionVStart(HIBYTE(usDisplayVstart), LOBYTE(usDisplayVstart), _DB_APPLY_POLLING);
                // Capture window V start setting
                ScalerMDomainSetCaptureWindowVStart(HIBYTE(usDVstart), LOBYTE(usDVstart));
                // Display V background start setting
                ScalerMDomainSetDisplayTimingGenBackgroundVStart(HIBYTE(usDVBGstart), LOBYTE(usDVBGstart), _DB_APPLY_POLLING);
                // Display V background end setting
                ScalerMDomainSetDisplayTimingGenBackgroundVEnd(HIBYTE(usDVBGend), LOBYTE(usDVBGend), _DB_APPLY_POLLING);
                break;

            default:
                break;
        }
    }

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerMDomainSetCaptureWindowEnable(_DISABLE);
#endif
}
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SDRToHDR parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSDRToHDR(bit bOn)
{
    if(bOn == _ON)
    {
#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustSDRToHDR(tSDRTOHDR_INPUTGAMMA, tSDRTOHDR_ICM, tSDRTOHDR_DCC, GET_CURRENT_BANK_NUMBER());
    }
    else
    {
        UserAdjustColorEffectMode();
        OsdFuncColorPcmAdjust();
    }
}
#endif // End of #if(_SDR_TO_HDR_SUPPORT == _ON)

#if(_DCR_SUPPORT == _ON)
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustDCRTHD(void)
{
    // Adjust DCR Threshold & Source
#if(_DCR_BIT_MODE == _DCR_GEN_1_0_10BIT)
    ScalerColorDCRAdjust(_DCR_THESHOLD1, _DCR_THESHOLD2, _MEASURE_AVERAGE);
#elif((_DCR_BIT_MODE == _DCR_GEN_0_0_8BIT) || (_DCR_BIT_MODE == _DCR_GEN_0_1_8BIT))
    ScalerColorDCRAdjust((_DCR_THESHOLD1 >> 2), (_DCR_THESHOLD2 >> 2), _MEASURE_AVERAGE);
#endif
}
#endif // End of #if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
#endif // End of #if(_DCR_SUPPORT == _ON)

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : User Control Type-C Port Controller Power
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserAjustTypeCPowerControl(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            //Switch On Port Controller Power By PCB Control
            PCB_PORT_CTRL_POW_RTD_USER(_PORT_CTRL_POWER_ON);
            CLR_TYPE_C_PORT_CTRL_POWER_OFF_FLG();

            break;

        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:

            if(GET_PCB_PORT_CTRL_POW_STATUS_RTD_USER() == _PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_PORT_CTRL_POW_RTD_USER(_PORT_CTRL_POWER_ON);
            }

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_PS:

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER )))
            if(SysSourceGetCableDetect(_D0_INPUT_PORT) == _FALSE)
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER )))
            if(SysSourceGetCableDetect(_D1_INPUT_PORT) == _FALSE)
#elif((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER )))
            if(SysSourceGetCableDetect(_D6_INPUT_PORT) == _FALSE)
#endif
            {
                // Switch Off Repeater Power By PCB Control
                PCB_PORT_CTRL_POW_RTD_USER(_PORT_CTRL_POWER_OFF);
                SET_TYPE_C_PORT_CTRL_POWER_OFF_FLG();
            }
            else
            {
                CLR_TYPE_C_PORT_CTRL_POWER_OFF_FLG();
            }

            break;

        default:

            break;
    }
}
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch Dp Version to 1.4, if HDR On
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHdrCheckDpVersion(WORD usHdrMode)
{
    // Switch Dp Version to 1.3, if HDR Function Support
    if(usHdrMode != _HDR10_MODE_OFF)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        if(GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2)
        {
            SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_3);

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2)
        {
            SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_3);

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        if(GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2)
        {
            SET_OSD_DP_D2_VERSION(_DP_VER_1_DOT_3);

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            UserCommonInterfaceDpVersionSwitch(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
#endif
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))


#if(_OSD_TYPE == _BEACON_2014_OSD)

#if(_ENABLE_BACKLIGHT_SENSOR)
//-----------------------TSL2561-----------------------------
//CMD 7 Select command register. Must write as 1.
//ADDRESS 3:0 Register Address. This field selects the specific control or status register for following write and read commands according to Table 2.

//---------------Table2--------------------
// .. COMMAND Specifies register address
// 0h CONTROL Control of basic functions
// 1h TIMING Integration time/gain control
// 2h THRESHLOWLOW Low byte of low interrupt threshold
// 3h THRESHLOWHIGH High byte of low interrupt threshold
// 4h THRESHHIGHLOW Low byte of high interrupt threshold
// 5h THRESHHIGHHIGH High byte of high interrupt threshold
// 6h INTERRUPT Interrupt control
// 7h .. Reserved
// 8h CRC Factory test not a user register
// 9h .. Reserved
// Ah ID Part number/ Rev ID
// Bh .. Reserved
// Ch DATA0LOW Low byte of ADC channel 0
// Dh DATA0HIGH High byte of ADC channel 0
// Eh DATA1LOW Low byte of ADC channel 1
// Fh DATA1HIGH High byte of ADC channel 1
//---------------Table2--------------------

//IIC Addr: 0x52=(0101001<<1)  0x72=(0111001<<1)  0x92=(1001001<<1)
//#define _BACKLIGHT_SENSOR_TSL2561_IIC_ADDR	0x52

#define BACKLIGHT_SENSOR_MIN                    10
#define BACKLIGHT_SENSOR_MAX	                20000

//------------------------TSL25721---------------------------
#define TSL2572_GAIN_1X             1
#define TSL2572_GAIN_8X             8
#define TSL2572_GAIN_16X            16
#define TSL2572_GAIN_120X           120

#define TSL2572_CMD_REGISTER        0x80
#define TSL2572_CMDS_ENABLE         0x00
#define TSL2572_CMDS_ALS_TIMING     0x01
#define TSL2572_CMDS_WAIT_TIME      0x03
#define TSL2572_CMDS_CONFIG         0x0d
#define TSL2572_CMDS_CONTROL        0x0f

#define _ATIME                      0x6e // 400ms
#define _ATIME_MS                   400  // 400s
#define _AGAIN                      0    //   0 // x1 //  1 X8 //    2 // X16    	
#define _AGAIN_VALUE                1    //   1  // 16  //     
#define _GA                         1

//--------------------------------------------------
// Description  : Init Backlight sensor TSL2561
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit BacklightSensor_TSL2561_Init(void)
{
    BYTE ucCmd_Buf[2]; //Nocall function will Inc xdata 2

    // ID Register(0x0Ah|CMD)   [7:4]0x00:2560 0x01:2561
    
    //SubAddr & Para;
    ucCmd_Buf[0]=0x81; //Timing Register (1h|CMD)
    ucCmd_Buf[1]=0x02; //Scale:1 Integration Time:402 ms
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
	    DebugMessageUart("BK TSL2561 Init1:", 0x81);     
        return _FAIL;        
    }
    
    //SubAddr & Para;
    ucCmd_Buf[0]=0x86;//Interrupt Control Register (6h|CMD)
    ucCmd_Buf[1]=0x00;
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
	    DebugMessageUart("BK TSL2561 Init2:", 0x86);     
        return _FAIL;        
    }

    //SubAddr & Para;
    ucCmd_Buf[0]=0x80;//Control Register (0h|CMD)
    ucCmd_Buf[1]=0x03;//Power up/power down. 03h is powered up. 00h is powered down.
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
	    DebugMessageUart("BK TSL2561 Init3:", 0x80);        
        return _FAIL;
    }
    
    return _SUCCESS;
}

bit BacklightSensor_TSL2572_Init(void)
{
    BYTE ucCmd_Buf[2]; //Nocall function will Inc xdata 2

#if 0
    // ID Register(0x12h|CMD)   0x34:25721 0x3D:25723
    //SubAddr & Para;
    if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x92, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
    {
        return _FAIL;
    }
#endif

    // Enable AEN and PON
    //SubAddr & Para;
    ucCmd_Buf[0]=0x80; // Enable Register (0h|CMD)
    ucCmd_Buf[1]=0x01; // [1] Writing 1h activates the ALS. 0h disable the ALS. [0] 01h is powered up. 00h is powered down.
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
	{
        return _FAIL;
    }
        
    // Set timing register
    //SubAddr & Para;
    ucCmd_Buf[0]=0x81; // ALS Timing Register (0x01h|CMD)
    ucCmd_Buf[1]=0x6E; // ATIME[7:0]  C0:175 ms 00:699ms  6E:400ms  ATIME = 256 - 400/2.73
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

#if 1
    // AGAIN =1X  and AGL=1 0.16
    // AGAIN =1X  and AGL=0 1.0
    // AGAIN =8X  and AGL=0 8.0

    // Configuration register:Reset 0x00
    //SubAddr & Para;
    ucCmd_Buf[0]=0x8D; // Configuration Register (0x0Dh|CMD)
    ucCmd_Buf[1]=0x00;//0x04; // AGL[2] = 1
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }
#endif

    ScalerTimerDelayXms(2);

    // Enable AEN and PON
    //SubAddr & Para;
    ucCmd_Buf[0]=0x80;// Enable Register (0h|CMD)
    ucCmd_Buf[1]=0x03;// [1] Writing 1h activates the ALS. 0h disable the ALS. [0] 01h is powered up. 00h is powered down.
    if(UserCommonEepromIICWrite(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }
    
    return _SUCCESS;
}


//--------------------------------------------------
// Description  : Init Backlight Sensor Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void InitBacklightSensorModule(void)
{     
	if(g_bBacklightSensorInitState == _BK_DEVICE_ID_NONE)//(GET_OSD_BACKLIGHT_SENSOR_STATUS() == _ON)
	{
		if(BacklightSensor_TSL2561_Init() == _SUCCESS)
		{
			g_bBacklightSensorInitState = _BK_DEVICE_ID_TSL2561;
		    DebugMessageUart("BK TSL2561 Init:", g_bBacklightSensorInitState);
		}
		else if(BacklightSensor_TSL2572_Init() == _SUCCESS) 
		{
			g_bBacklightSensorInitState = _BK_DEVICE_ID_TSL2572;
		    DebugMessageUart("BK TSL2572 Init:", g_bBacklightSensorInitState);
		}
		else
		{
    		g_bBacklightSensorInitState = _BK_DEVICE_ID_NONE;
		    DebugMessageUart("BK Init Fail:", g_bBacklightSensorInitState);
		}
//OsdDispOsdMessage(_OSD_DISP_DICOM_RESULT);
//OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 2), g_bBacklightSensorInitState, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));
        
	}	
}

//--------------------------------------------------
// Description  : Set Backlight PWM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UpdatePWMSettings(WORD ucValue)
{	
	if((ucValue < _BACKLIGHT_MIN)||(ucValue > _BACKLIGHT_MAX))
	{
		return;
	}
		
#if(_BACKLIGHT_PWM_INVERSE == _ON)
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
    ucValue = _BACKLIGHT_MAX - ucValue;
#endif
#endif

    DebugMessageUart("Update-PWM:", ucValue);

    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(ucValue);
}

//--------------------------------------------------
// Description  : Read Backlight Sensor Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ReadBacklightSensorValue(BYTE ucChannel)
{
    BYTE pucData[2]; 

	// check sensor initial status
	if(g_bBacklightSensorInitState == _FAIL)
	{
		InitBacklightSensorModule();

		return _FAIL;
	}

	if(g_bBacklightSensorInitState == _BK_DEVICE_ID_TSL2561)
    {
    	if(ucChannel == 0)
    	{
        	//SudAddr L = 0x0c; 	//Ch DATA0LOW Low byte of ADC channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, 0x8C, 1, 1, &pucData[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }

        	//SudAddr H = 0x0d; 	//Dh DATA0HIGH High byte of ADC channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, 0x8D, 1, 1, &pucData[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }
    	}
    	else
    	{
        	//SudAddr L = 0x0e; 	//Ch DATA0LOW Low byte of ADC channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, 0x8E, 1, 1, &pucData[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }

        	//SudAddr H = 0x0f; 	//Dh DATA0HIGH High byte of ADC channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2561_IIC_ADDR, 0x8F, 1, 1, &pucData[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }
    	}   
    }
	else if(g_bBacklightSensorInitState == _BK_DEVICE_ID_TSL2572)
    {
#if 1
    	//SudAddr L = 0x14; 	//DATA0LOW Low byte of ALS channel 0
        if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x94, 1, 1, &pucData[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
        {
            return _FAIL;
        }

    	//SudAddr H = 0x15; 	//DATA0HIGH High byte of ALS channel 0
        if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x95, 1, 1, &pucData[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
        {
            return _FAIL;
        }
#else
        DWORD CH0_light, CH1_light;
        double CurSensorValue1,CurSensorValue2;

        DWORD CurSensorValue;
        double CPL = 0;
       
        // Status Register(0x13h|CMD)
    	//SudAddr L = 0x93; 	 
        //if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x93, 1, 1, &pucData[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
        //{
        //    return _FAIL;
        //}
   
        // ALS AVALID[0]
        //if(pucData[0] & 0x01) 
        {
        	//SudAddr L = 0x14; 	//DATA0LOW Low byte of ALS channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x94, 1, 1, &pucData[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }

        	//SudAddr H = 0x15; 	//DATA0HIGH High byte of ALS channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x95, 1, 1, &pucData[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }
            CH0_light= ((WORD)(pucData[1]<<8)|pucData[0]);

        	//SudAddr L = 0x16; 	//DATA0LOW Low byte of ALS channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x96, 1, 1, &pucData[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }

        	//SudAddr H = 0x17; 	//DATA0HIGH High byte of ALS channel 0
            if(UserCommonEepromIICRead(_BACKLIGHT_SENSOR_TSL2572_IIC_ADDR, 0x97, 1, 1, &pucData[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
            {
                return _FAIL;
            }
            CH1_light= ((WORD)(pucData[1]<<8)|pucData[0]);

            CPL = (double)((_ATIME_MS * _AGAIN_VALUE)) / (_GA * 60);

            CurSensorValue1 = (CH0_light - 1.87 * CH1_light) / CPL;
            CurSensorValue2 = (0.63*CH0_light - CH1_light) / CPL;
            DebugMessageUart("CH0_light :", CH0_light);
            DebugMessageUart("CH1_light :", CH1_light);

            if(CurSensorValue1 > CurSensorValue2)
                CurSensorValue = (DWORD)CurSensorValue1;
            else
                CurSensorValue = (DWORD)CurSensorValue2;

            return CurSensorValue;

        }
#endif
    }
    //DebugMessageUart("pucData[1]:", pucData[1]);
    //DebugMessageUart("Sensor type:", g_bBacklightSensorInitState);
	return ((WORD)(pucData[1]<<8)|pucData[0]);
}

//--------------------------------------------------
// Description  : User Set Backlight Sensor TargetValue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserSetBacklightSensorTargetValue(WORD TargetValue)
{
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
	    DebugMessageUart("new Sensor PCM:", TargetValue);
		_SET_USER_BACKLIGHT_SENSOR_VALUE(TargetValue);
        return;
    }
    
#if 1// _CT_SRGB is Native
    if(IsGammaOptionNative(GET_OSD_GAMMA()))
	{
		DebugMessageUart("new Sensor CT Native:", TargetValue);
		_SET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE(TargetValue);
        return;
	}
#endif
	switch(GET_OSD_GAMMA())
	{
		case _GAMMA_OFF:
			if(IsGammaOptionNative(GET_OSD_GAMMA()))
			{
				DebugMessageUart("new Sensor Native:", TargetValue);
				_SET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE(TargetValue);
			}
			else
			{
    		    DebugMessageUart("new Sensor G2.2:", TargetValue);
    			//_SET_USER_BACKLIGHT_SENSOR_VALUE(TargetValue);
			}
			break;

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
		case _GAMMA_18:
		    DebugMessageUart("new Sensor G2.2:", TargetValue);
			_SET_USER_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;
            
		case _GAMMA_20:
		    DebugMessageUart("new Sensor Dicom:", TargetValue);           
			_SET_USER_DICOM_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_22:
		    DebugMessageUart("new Sensor MCU:", TargetValue);           
			_SET_USER_BACKLIGHT_MCU_CALIB_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_24:
		    DebugMessageUart("new Sensor Calib:", TargetValue);
			_SET_USER_BACKLIGHT_CALIB_SENSOR_VALUE(TargetValue);
			break;

        default:
			break;
            
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
		case _GAMMA_18:
		case _GAMMA_20:
		case _GAMMA_22:
		case _GAMMA_24:
		    DebugMessageUart("new Sensor G2.2:", TargetValue);
			_SET_USER_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;
            
		case _GAMMA_26:
		    DebugMessageUart("new Sensor Dicom:", TargetValue);           
			_SET_USER_DICOM_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_CALIB:
		    DebugMessageUart("new Sensor Calib:", TargetValue);
			_SET_USER_BACKLIGHT_CALIB_SENSOR_VALUE(TargetValue);
			break;
            
        default:
			break;
            
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
		case _GAMMA_18:
		    DebugMessageUart("new Sensor 2.2:", TargetValue);
			_SET_USER_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM200:
		    DebugMessageUart("new Sensor D200:", TargetValue);
			_SET_USER_DICOM200_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM250:
		    DebugMessageUart("new Sensor D250:", TargetValue);
			_SET_USER_DICOM250_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM300:
		    DebugMessageUart("new Sensor D300:", TargetValue);
			_SET_USER_DICOM300_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM350:
		    DebugMessageUart("new Sensor D350:", TargetValue);
			_SET_USER_DICOM350_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM400:
		    DebugMessageUart("new Sensor D400:", TargetValue);
			_SET_USER_DICOM400_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM450:
		    DebugMessageUart("new Sensor D450:", TargetValue);
			_SET_USER_DICOM450_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM500:
		    DebugMessageUart("new Sensor D500:", TargetValue);
			_SET_USER_DICOM500_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM550:
		    DebugMessageUart("new Sensor D550:", TargetValue);
			_SET_USER_DICOM550_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_DICOM600:
		    DebugMessageUart("new Sensor D600:", TargetValue);
			_SET_USER_DICOM600_BACKLIGHT_SENSOR_VALUE(TargetValue);
			break;

		case _GAMMA_CALIB:
		    DebugMessageUart("new Sensor Calib:", TargetValue);
			_SET_USER_BACKLIGHT_CALIB_SENSOR_VALUE(TargetValue);
			break;

        default:
			break;
#else
#warning "!!!Please Check Gamma define"

#endif

	}
}

//--------------------------------------------------
// Description  : User Get Backlight Sensor TargetValue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD UserGetBacklightSensorTargetValue(void)
{

    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
	    DebugMessageUart("Get Sensor PCM:", _GET_USER_BACKLIGHT_SENSOR_VALUE);
		return _GET_USER_BACKLIGHT_SENSOR_VALUE;
    }
    
#if(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()))
	{
       	switch(GET_OSD_FPGA_GRAY_GAMMA())
		{
#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
            case _GAMMA_18:
				return _GET_USER_BACKLIGHT_SENSOR_VALUE;

			case _GAMMA_20:
				return _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE;

			case _GAMMA_22:
				return _GET_USER_BACKLIGHT_MCU_CALIB_SENSOR_VALUE;

			case _GAMMA_24:
				return _GET_USER_BACKLIGHT_CALIB_SENSOR_VALUE;
                
	        default:
				return _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE;
#else
#warning "!!!Please Check Gamma define"
#endif
		}
	}
	else
#endif
    {
#if 1// _CT_SRGB is Native
		if(IsGammaOptionNative(GET_OSD_GAMMA()))
		{
    		DebugMessageUart("Get Sensor CT Native:", _GET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE);
			return _GET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE;
		}
#endif
    	switch(GET_OSD_GAMMA())
    	{
    		case _GAMMA_OFF:
    			if(IsGammaOptionNative(GET_OSD_GAMMA()))
    			{
    				return _GET_USER_NATIVE_BACKLIGHT_SENSOR_VALUE;
    			}
    			else
    			{
    				return _GET_USER_BACKLIGHT_SENSOR_VALUE;
    			}

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    		case _GAMMA_18:           
    			return _GET_USER_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_20:           
    			return _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_22:
    			return _GET_USER_BACKLIGHT_MCU_CALIB_SENSOR_VALUE;

    		case _GAMMA_24:
    			return _GET_USER_BACKLIGHT_CALIB_SENSOR_VALUE;

#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    		case _GAMMA_18:           
    		case _GAMMA_20:           
    		case _GAMMA_22:
    		case _GAMMA_24:
    			return _GET_USER_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_26:
    			return _GET_USER_DICOM_BACKLIGHT_SENSOR_VALUE;

#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    		case _GAMMA_18:           
    			return _GET_USER_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM200:
    			return _GET_USER_DICOM200_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM250:
    			return _GET_USER_DICOM250_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM300:
    			return _GET_USER_DICOM300_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM350:
    			return _GET_USER_DICOM350_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM400:
    			return _GET_USER_DICOM400_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM450:
    			return _GET_USER_DICOM450_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM500:
    			return _GET_USER_DICOM500_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM550:
    			return _GET_USER_DICOM550_BACKLIGHT_SENSOR_VALUE;

    		case _GAMMA_DICOM600:
    			return _GET_USER_DICOM600_BACKLIGHT_SENSOR_VALUE;
#else
#warning "!!!Please Check Gamma define"

#endif   

    		case _GAMMA_CALIB:
    			return _GET_USER_BACKLIGHT_CALIB_SENSOR_VALUE;

            default:
    			return _GET_USER_BACKLIGHT_SENSOR_VALUE;
                    
    	}
    }
}

// Add Backlight sensor average value processing or middle value processing
#define _ENABLE_BACKLIGHT_SENSOR_AVERAGE    _ON 
// Cause one[Handler]: The range of backlight sensor value range changes is wide and unstable or abnormal jump under long-term work or high temperature environment
// Cause two[Update]:  Reading the backlight sensor value range is unstable or abnormal jump


//--------------------------------------------------
// Description  : Update Backlight Sensor TargetValue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UpdateBacklightSensorValue(void)
{	
    WORD usBackupSensorValue;
    WORD usCurSensorValue;
        
    // Read BK sensor three times and calculate the average or middle
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
	static BYTE ucBKSensorMultiple = 0;
	static WORD usBKAverageValue[3] = 0;
#endif
    
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
		return;
	}
    else if(SysModeGetModeState() != _MODE_STATUS_ACTIVE)
    {
        DebugMessageUart("UpBK Skip:", SysModeGetModeState());
    	ScalerTimerReactiveTimerEvent(SEC(4), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_VALUE_UPDATE);
        return;
    }

    if(GET_OSD_BACKLIGHT_SENSOR_STATUS() == _OFF) 
    {
    	return;
    }

    //for Backlight ON flag
    if(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)
    {
        DebugMessageUart(">>BK Backlight Flag:", GET_PANELPOWERSTATUS());
    	ScalerTimerReactiveTimerEvent(SEC(4), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_VALUE_UPDATE);
		return;
    }    
        
    usBackupSensorValue = UserGetBacklightSensorTargetValue();
    DebugMessageUart("BK Old Sensor:", usBackupSensorValue);
    
    // Stop Speedy Hander
	ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER); 

    //Update target
    // Fac UI or Fac DDCCI CMD:Read BK sensor three times and calculate the average or middle
    if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
    {    
        // for Fac UI 
        do
        {
            usCurSensorValue = ReadBacklightSensorValue(0);
            usBKAverageValue[ucBKSensorMultiple] = usCurSensorValue;
            DebugMessageUart("Get Sensor:", usCurSensorValue);
            ucBKSensorMultiple++;
            // DDCCI Warning!!! Delay here for factory menu refresh 
            ScalerTimerDelayXms(500); 
        }while(ucBKSensorMultiple < 3);

        if(ucBKSensorMultiple >= 3)
        {
            ucBKSensorMultiple = 0;
            usCurSensorValue = (DWORD)(usBKAverageValue[0] + usBKAverageValue[1] + usBKAverageValue[2] + 3)/3;
    	    DebugMessageUart("Sensor Avg:", usCurSensorValue);
            // Avoid abnormal jumps: CL2713 Dicom= 148 Gamma1= 1526 new get 148 1526 1538 ->Save 1526
            usCurSensorValue = MIDOF(usBKAverageValue[0],usBKAverageValue[1],usBKAverageValue[2]);
    	    DebugMessageUart("Sensor Mid:", usCurSensorValue);
        }
    }
    else
    {
        // for Fac DDCCI CMD
        usCurSensorValue = ReadBacklightSensorValue(0);
    }

    //  for Fac DDCCI CMD 
    if(GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)
    {
        if(ucBKSensorMultiple >= 3)
        {
            ucBKSensorMultiple = 0;
            usCurSensorValue = (DWORD)(usBKAverageValue[0] + usBKAverageValue[1] + usBKAverageValue[2] + 3)/3;
    	    DebugMessageUart("Sensor Avg:", usCurSensorValue);
            // Avoid abnormal jumps: CL2713 Dicom= 148 Gamma1= 1526 new get 148 1526 1538 ->Save 1526
            usCurSensorValue = MIDOF(usBKAverageValue[0],usBKAverageValue[1],usBKAverageValue[2]);
    	    DebugMessageUart("Sensor Mid:", usCurSensorValue);
        }
        else
        {
            usBKAverageValue[ucBKSensorMultiple] = usCurSensorValue;
            ucBKSensorMultiple++;
        	ScalerTimerReactiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_VALUE_UPDATE);
    		return;
        }
    }

	if(usCurSensorValue < BACKLIGHT_SENSOR_MIN || usCurSensorValue > BACKLIGHT_SENSOR_MAX) 
	{ 
		return;  
	} 
	
	//if( abs(usCurSensorValue - usBackupSensorValue) >= _BACKLIGHT_SENSOR_PRECISION/6)
	{
	    UserSetBacklightSensorTargetValue(usCurSensorValue);

		// DDCCI Beacon QA Tool update Restore Backlight Target Value
	    {
			if(g_bBacklightSensorValueRestoreStatus == _TRUE)
			{
				g_bBacklightSensorValueRestoreStatus = _FAIL;
				_SET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE(_GET_USER_BACKLIGHT_SENSOR_VALUE);
		        DebugMessageUart("Restore Sensor G2.2:", _GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE);
			}
        	DebugMessageUart("BK new Sensor:", UserGetBacklightSensorTargetValue());
	        RTDNVRamSaveOsdUser2Data();
	    }
	}
}
#if(_ARM_MCU_CALIBRATION_SUPPORT) 
void UpdateUserCalibrationMessage(BYTE ucStatus)
{	
    BYTE ucPercentage;
    
    if(ucStatus == _OFF)
    {
        if(ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_QA_EVENT))
        {
    	    DebugMessageUart("_QA Time-:", ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_QA_EVENT));
            ucPercentage = 100;
            ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_QA_EVENT);
        }
        if(ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE))
        {
    	    DebugMessageUart("_LUX Time-:", ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE));
            ucPercentage = 100;
            ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE);
        }
    }
    else
    {
        if(ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_QA_EVENT))
        {
    	    DebugMessageUart(" Percent:", ((WORD)(61 - (ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_QA_EVENT)/1000))*100/61));
            ucPercentage = ((WORD)(61 - (ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_QA_EVENT)/1000))*100/61);
        }
        if(ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE))
        {
    	    DebugMessageUart(" Percent:", ((WORD)(61 - (ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE)/1000))*100/61));
            ucPercentage = ((WORD)(61 - (ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE)/1000))*100/61);
        }
    }
    if(GET_OSD_STATE() == _MENU_MESSAGE_DISPLAY)
    {
        OsdPropShowNumberPercentage(ROW(_WIN_HOTKEY_ITEM_ROW + 3), COL(_WIN_HOTKEY_INFO_WIDTH - 2), ucPercentage, _FALSE, _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG));
    }
}
#endif

//--------------------------------------------------
// Description  : Backlight Sensor Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserBacklightSensorHandler(void)
{ 	
	WORD usBacklightPWM;	
	WORD usCurSensorValue, usDeltaValue;
    
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
	static BYTE ucBKSensorMultipleInc = 0;
	static BYTE ucBKSensorMultipleDec = 0;
	static WORD usBKAverageDeltaValue[4] = 0;
#endif

    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
		return;
	}

	if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER) == _TRUE)
    {
		ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
        //DebugMessageSystem("BK speedy...", UserCommonTimerGetEventRemainTime(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER));
    }
	else
	{
        ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
        // Do not read the temperature sensor quickly
#if(_PRODUCT_ID_SEL != RTD2785TM_U231A_RL6432_216PIN_A_BBK_FHD)
        UserTemperatureSensorHandler();	
#endif
	}
	
    if(SysModeGetModeState() != _MODE_STATUS_ACTIVE)
    {
		return;
	}
	
	if(GET_OSD_BACKLIGHT_SENSOR_STATUS() == _OFF) // Sensor off. 
	{	
        DebugMessageSystem("BK Sensor off...", 0);
		return;
	}

	if(GET_OSD_STATE() > _MENU_NONE) // OSD On. Calibration except
	{	
	    if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
        {
			return;
        }
	}
	

    //for Brun In flag
	if(GET_OSD_FACTORY_MODE_BRUNIN()==_ON) // burn in mode 
    {
        DebugMessageUart("BK Sensor burnin...", 0);
		return;
    }

    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SAVE_USER2_DATA) == _TRUE)
    {
        DebugMessageSystem("BK user2 save...", 0);
        return;
    }

    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_VALUE_UPDATE) == _TRUE)
    {
        DebugMessageSystem("BK Sensor update...", 0);
        return;
    }

    //for Backlight ON flag
    if(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)
    {
        DebugMessageSystem(">>BK Backlight Flag:", GET_PANELPOWERSTATUS());
		return;
    } 

	usCurSensorValue = ReadBacklightSensorValue(0);
    //DebugMessageUart("Cur Sensor:", usCurSensorValue);
	
    //Get PWM
	usBacklightPWM = PCB_GET_BACKLIGHT_PWM();
 #if(_BACKLIGHT_PWM_INVERSE == _ON)
    usBacklightPWM = _BACKLIGHT_MAX - usBacklightPWM;
 #endif
		
    //disable if light too Low or too high( circuit not work).
	if(usCurSensorValue < BACKLIGHT_SENSOR_MIN || usCurSensorValue > BACKLIGHT_SENSOR_MAX) 
	{ 
		return;  
	}   

	//if(abs(usCurSensorValue - UserGetBacklightSensorTargetValue()) < _BACKLIGHT_SENSOR_PRECISION)
    //{
		//return;
    //}

	// The photo sensor compensation is working 
	{ 
		if(usCurSensorValue > UserGetBacklightSensorTargetValue())
		{
			usDeltaValue = usCurSensorValue - UserGetBacklightSensorTargetValue();
			
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
            usBKAverageDeltaValue[ucBKSensorMultipleDec] = usDeltaValue;
            ucBKSensorMultipleDec++;
            ucBKSensorMultipleInc = 0;
            
            if(ucBKSensorMultipleDec >= 4)
            {
                usDeltaValue = ((DWORD)usBKAverageDeltaValue[0] + usBKAverageDeltaValue[1] + usBKAverageDeltaValue[2] + usBKAverageDeltaValue[3] + 4)/4;
        	    DebugMessageUart("Delta Avg:", usDeltaValue);
            }
#endif
            
#if 1//(_PRODUCT_ID_SEL != PRODUCT_G101WPlus_BEACON_A_MONO_STD_R300M1_L01_10M_LVDS)
            if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*24)&&(usBacklightPWM > ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MIN + (20<<4)) : (_BACKLIGHT_MIN + 20))))
			{
				//usBacklightPWM-=20;
				usBacklightPWM = usBacklightPWM - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (20<<4) : 20);
			}
            else if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*12)&&(usBacklightPWM > ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MIN + (8<<4)) : (_BACKLIGHT_MIN + 8))))
			{
				//usBacklightPWM-=8;
				usBacklightPWM = usBacklightPWM - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (8<<4) : 8);
			}
            else if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*8)&&(usBacklightPWM > ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MIN + (4<<4)) : (_BACKLIGHT_MIN + 4))))
			{
				//usBacklightPWM-=4;
				usBacklightPWM = usBacklightPWM - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (4<<4) : 4);
			}
			else
#endif
			if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*4)&&(usBacklightPWM > ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MIN + (2<<4)) : (_BACKLIGHT_MIN + 2))))
			{
				//usBacklightPWM-=2;
				usBacklightPWM = usBacklightPWM - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (2<<4) : 2);
			}
			else if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*2)&&(usBacklightPWM > _BACKLIGHT_MIN))
			{
				//usBacklightPWM--;	
				usBacklightPWM = usBacklightPWM - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<3) : 1);
            }
			else
			{
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
                ucBKSensorMultipleDec = 0;
                memset(&usBKAverageDeltaValue, 0, sizeof(usBKAverageDeltaValue));
#endif
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
#if(_ARM_MCU_CALIBRATION_SUPPORT)            
                UpdateUserCalibrationMessage(_OFF);
#endif

				return;
			}
		}
		else
		{
			usDeltaValue = UserGetBacklightSensorTargetValue() - usCurSensorValue;
			
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
            usBKAverageDeltaValue[ucBKSensorMultipleInc] = usDeltaValue;
            ucBKSensorMultipleInc++;
            ucBKSensorMultipleDec = 0;

            if(ucBKSensorMultipleDec >= 4)
            {
                usDeltaValue = ((DWORD)usBKAverageDeltaValue[0] + usBKAverageDeltaValue[1] + usBKAverageDeltaValue[2] + usBKAverageDeltaValue[3] + 4)/4;
        	    DebugMessageUart("Delta Avg:", usDeltaValue);
            }
#endif

#if 1//(_PRODUCT_ID_SEL != PRODUCT_G101WPlus_BEACON_A_MONO_STD_R300M1_L01_10M_LVDS)
            if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*24)&&(usBacklightPWM < ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MAX - (20<<4)) : (_BACKLIGHT_MAX - 20))))	
			{
				//usBacklightPWM+=20;
				usBacklightPWM = usBacklightPWM + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (20<<4) : 20);
			}
            else if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*12)&&(usBacklightPWM < ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MAX - (8<<4)) : (_BACKLIGHT_MAX - 8))))	
			{
				//usBacklightPWM+=8;
				usBacklightPWM = usBacklightPWM + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (8<<4) : 8);
			}
            else if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*8)&&(usBacklightPWM < ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MAX - (4<<4)) : (_BACKLIGHT_MAX - 4))))	
			{
				//usBacklightPWM+=4;
				usBacklightPWM = usBacklightPWM + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (4<<4) : 4);
			}
			else 
#endif
			if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*4)&&(usBacklightPWM < ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (_BACKLIGHT_MAX - (2<<4)) : (_BACKLIGHT_MAX - 2))))
			{
				//usBacklightPWM+=2;
				usBacklightPWM = usBacklightPWM + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (2<<4) : 2);
			}
			else if((usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*2/3)&&(usBacklightPWM < _BACKLIGHT_MAX))
			{
				//usBacklightPWM+=1;
				usBacklightPWM = usBacklightPWM + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<3) : 1);
                //_PWM_12BIT 4088+8 = 4096
                if(usBacklightPWM > _BACKLIGHT_MAX)
        	    {
            	    usBacklightPWM = _BACKLIGHT_MAX;
        	    }
			}
			else
			{
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
                ucBKSensorMultipleInc = 0;
                memset(&usBKAverageDeltaValue, 0, sizeof(usBKAverageDeltaValue));
#endif
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
#if(_ARM_MCU_CALIBRATION_SUPPORT)            
            UpdateUserCalibrationMessage(_ON);
#endif

				return;
			}
		}

		if(usDeltaValue >= _BACKLIGHT_SENSOR_PRECISION*2/3)
	    {
            //DebugMessageSystem("BK Adj PWM:", usBacklightPWM);
	    }

        // Multiple times Check if the backlight sensor value has changed 
#if(_ENABLE_BACKLIGHT_SENSOR_AVERAGE == _ON)
        if((ucBKSensorMultipleInc >= 4)||(ucBKSensorMultipleDec >= 4))
        {
            ucBKSensorMultipleInc = 0;
            ucBKSensorMultipleDec = 0;
            memset(&usBKAverageDeltaValue, 0, sizeof(usBKAverageDeltaValue));
    		UpdatePWMSettings(usBacklightPWM);
#if(_ARM_MCU_CALIBRATION_SUPPORT)            
            UpdateUserCalibrationMessage(_ON);
#endif
            
        }
#else
		UpdatePWMSettings(usBacklightPWM);
#endif
	}
}

//--------------------------------------------------
// Description  : Restore Backlight Sensor Value to FAC Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustRestoreBacklightSensorValue(void)
{
	BYTE ucColorTemp,ucPCMStatus;
	ucColorTemp = GET_COLOR_TEMP_TYPE();
	ucPCMStatus = GET_OSD_PCM_STATUS();

	SET_OSD_PCM_STATUS(_PCM_OSD_SRGB);
	SET_COLOR_TEMP_TYPE(_CT_9300);
	_SET_USER_BACKLIGHT_SENSOR_VALUE(_GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE);

	SET_COLOR_TEMP_TYPE(_CT_6500);
	_SET_USER_BACKLIGHT_SENSOR_VALUE(_GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE);
	SET_OSD_PCM_STATUS(ucPCMStatus);
    
	SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);

    
	if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
    {
		SET_COLOR_TEMP_TYPE(_CT_7500);
		_SET_USER_BACKLIGHT_SENSOR_VALUE(_GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE);
    }
    
	SET_COLOR_TEMP_TYPE(_CT_9300);
	_SET_USER_BACKLIGHT_SENSOR_VALUE(_GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE);

	SET_COLOR_TEMP_TYPE(_CT_6500);
	_SET_USER_BACKLIGHT_SENSOR_VALUE(_GET_USER_BACKLIGHT_RESTORE_SENSOR_VALUE);

	SET_COLOR_TEMP_TYPE(ucColorTemp);
    RTDNVRamSaveOsdUser2Data();
}

//--------------------------------------------------
// Description  : Get the value of the Panel Front Lux corresponding to a current location by the Backlight Sensor value.
// Input Value  : Backlight Sensor Position
// Output Value : None
//--------------------------------------------------
WORD UserAdjustQAGetCurrPanelLux(BYTE ucIndex)
{
	WORD ucLux = _DEFAULT_GAMMA_LUX;
	WORD usSensor = 0; 
	float ucLuxA,ucLuxB,ucBypassMax,ucCMax;
	BYTE ucColortemp,ucLuxABMode;

    // Load data
	RTDNVRamLoadPanelLuxABData();
	RTDNVRamLoadPanelLuxRangeData();

#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
    if(GET_COLOR_TEMP_TYPE() == _CT_9300)
	{
        ucColortemp = _BK_SENSOR_CT_9300;
	}
    else if(GET_COLOR_TEMP_TYPE() == _CT_7500)
	{
        ucColortemp = _BK_SENSOR_CT_7500;
	}
	else
	{
        ucColortemp = _BK_SENSOR_CT_6500;
	}
#else
    if(GET_COLOR_TEMP_TYPE() < _CT_6500)
	{
        ucColortemp = _BK_SENSOR_CT_9300;
	}
	else
	{
        ucColortemp = _BK_SENSOR_CT_6500;
	}
#endif

	switch(ucIndex)
	{
		case _BK_SENSOR_UP:
		    usSensor = ReadBacklightSensorValue(0);
			break;

		case _BK_SENSOR_DOWN:
		    usSensor = ReadBacklightSensorValue(0);
			break;

		default:
		case _BK_SENSOR_MIDDLE:
		    usSensor = ReadBacklightSensorValue(0);
			break;
	}
	
    //Calc A,B Data
    memcpy(&ucLuxA,&g_stPanelLuxABData[ucIndex].ucA_Data,4);
    //DebugMessageUart("ucLuxA:", ucLuxA);
#if 0//(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)
    ucLuxA = 2.4;
#else
    ucLuxA = ucLuxA/1000;
#endif  
    DebugMessageUart("ucLuxA:", ucLuxA);

    memcpy(&ucLuxB,&g_stPanelLuxABData[ucIndex].ucB_Data,4);
    //DebugMessageUart("ucLuxB:", ucLuxB);
#if 0//(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)
    ucLuxB = 0;
#else    
    ucLuxB = ucLuxB/1000;    
#endif
    DebugMessageUart("ucLuxB:", ucLuxB);

    memcpy(&ucBypassMax,&g_stPanelLuxRangeData[ucColortemp].ucLuxMax,4);
    DebugMessageUart("ucBypassMax:", ucBypassMax);
    ucBypassMax = ucBypassMax/1000;
    
    memcpy(&ucCMax,&g_stPanelLuxRangeData[ucColortemp].ucRealLuxMax,4);
    DebugMessageUart("ucCMax:", ucCMax);
    ucCMax = ucCMax/1000;

    UserCommonEepromRead(_USER_PANEL_LUT_LUX_AB_VERSION_ADDRESS, 1, &ucLuxABMode);
    //DebugMessageUart("LuxAB Ver", ucLuxABMode);    
    //DebugMessageUart("usSensor:", usSensor);
	if((ucLuxABMode == 0x00)||(ucLuxABMode == 0xFF))
	{
    	ucLux = (WORD)((float)usSensor - ucLuxB)/ucLuxA;
	    DebugMessageUart("Lux:", ucLux);
    }
    else
	{
	    ucLux = (WORD)((float)usSensor*ucLuxA + (float)ucLuxB);
	    DebugMessageUart("QA,Lux:", ucLux);
	}
    if(IsMonoChromeorColorPanel() == M_MONO)
    {
    	return ucLux;
    }

    if(GET_OSD_GAMMA() != _GAMMA_OFF)
	{
	    ucLux = (WORD)ucLux*ucCMax/(ucBypassMax);
	    DebugMessageUart("Front Lux:", ucLux);
	}

	return ucLux;
}

//--------------------------------------------------
// Description  : Get the current Lut Bypass Lux.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD UserAdjustQAGetStandardLux(BYTE ucColorType,WORD usTargetLux) 
{
	float ucBypassMax,ucFrontMax;	
	
	if(ucColorType > _BK_SENSOR_CT_6500)
		return _DEFAULT_GAMMA_LUX;

    memcpy(&ucBypassMax,&g_stPanelLuxRangeData[ucColorType].ucLuxMax,4);
    //DebugMessageUart("Bypass Max", ucBypassMax);
    ucBypassMax = ucBypassMax/1000;
    
    memcpy(&ucFrontMax,&g_stPanelLuxRangeData[ucColorType].ucRealLuxMax,4);
    //DebugMessageUart("Front Max", ucFrontMax);
    ucFrontMax = ucFrontMax/1000;
    
    return (WORD)(usTargetLux*ucBypassMax/ucFrontMax);//Bypass Lux
}

//--------------------------------------------------
// Description  : Get current Backlight Sensor value from current Bypass Lux.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD UserAdjustQAGetTargetSensor(WORD usTargetLux)
{
	float ucLuxA,ucLuxB;	
	WORD usSensor;
	BYTE ucLuxABMode;
	
    //Calc A,B Data
    memcpy(&ucLuxA,&g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucA_Data,4);
    //DebugMessageUart("ucLuxA", ucLuxA);
#if 0//(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)
    ucLuxA =  2.4;
#else    
	ucLuxA = ucLuxA/1000;
#endif

    memcpy(&ucLuxB,&g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucB_Data,4);
    //DebugMessageUart("ucLuxB", ucLuxB);    
#if 0//(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)
    ucLuxB = 0;
#else    
    ucLuxB = ucLuxB/1000;
#endif
    // Calculated Backlight Sensor
    UserCommonEepromRead(_USER_PANEL_LUT_LUX_AB_VERSION_ADDRESS, 1, &ucLuxABMode);
    //DebugMessageUart("LuxAB Ver", ucLuxABMode);    
	if((ucLuxABMode == 0xFF)||(ucLuxABMode == 0x00))
	{
    	usSensor = (WORD)(ucLuxA*usTargetLux + ucLuxB);
        //DebugMessageUart("usSensor", usSensor);    
    }
    else
    {
    	usSensor = (WORD)((float)(usTargetLux - ucLuxB)/(float)ucLuxA);
        //DebugMessageUart("QA,usSensor", usSensor);    
	}
	
	return usSensor;	
}

//--------------------------------------------------
// Description  : Embedded MCU QA Update Backlight Sensor value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustQAUpdateTargetSensor(WORD usTargetLux) 
{
	WORD usSensor,ucTargetLuxTemp,ucLux = _DEFAULT_GAMMA_LUX;
	BYTE ucPos,ucColortemp,ucGammaTemp;
	BYTE ucBackupColortemp = GET_COLOR_TEMP_TYPE();
	BYTE ucBackUpGamma = GET_OSD_GAMMA();
	
	for(ucPos = 0; ucPos < _BK_SENSOR_CT_AMOUNT; ucPos++) // Color
	{
		if(ucPos == 0)
		{
            SET_COLOR_TEMP_TYPE(_CT_9300);
            ucColortemp = _BK_SENSOR_CT_9300;
		}
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
		else if(ucPos == 1)
		{
            SET_COLOR_TEMP_TYPE(_CT_7500);
            ucColortemp = _BK_SENSOR_CT_7500;
		}
		else if(ucPos == 2)
		{
            SET_COLOR_TEMP_TYPE(_CT_6500);
            ucColortemp = _BK_SENSOR_CT_6500;
		}
        else if(ucPos == 3)
		{
	        SET_COLOR_TEMP_TYPE(_CT_USER);
			ucColortemp = _BK_SENSOR_CT_6500;
			if(GET_OSD_GAMMA() == _GAMMA_18)
			{
				usTargetLux = usTargetLux + GET_OSD_LUT_USER_LUT_OFFSET();
				DebugMessageUart("LUT_OFFSET", GET_OSD_LUT_USER_LUT_OFFSET());
			}
		}
#else
		else if(ucPos == 1)
		{
            SET_COLOR_TEMP_TYPE(_CT_6500);
            ucColortemp = _BK_SENSOR_CT_6500;
		}
		else if(ucPos == 2)
		{
	        SET_COLOR_TEMP_TYPE(_CT_USER);
			ucColortemp = _BK_SENSOR_CT_6500;
			if(GET_OSD_GAMMA() == _GAMMA_18)
			{
				usTargetLux = usTargetLux + GET_OSD_LUT_USER_LUT_OFFSET();
				DebugMessageUart("LUT_OFFSET", GET_OSD_LUT_USER_LUT_OFFSET());
			}
		}
#endif

		ucTargetLuxTemp = usTargetLux;
		DebugMessageUart("usTargetLux", usTargetLux);
        
		for(ucGammaTemp = _DEFAULT_GAMMA/*_GAMMA_OFF*/; ucGammaTemp <= _DEFAULT_GAMMA; ucGammaTemp++)
		{
			SET_OSD_GAMMA(ucGammaTemp);
			{
				if(ucGammaTemp == _DEFAULT_GAMMA)
				{
                    ucTargetLuxTemp = usTargetLux;
				}
				else
				{
                    ucTargetLuxTemp = _DEFAULT_GAMMA_LUX;
				}
			}
			
            ucLux = UserAdjustQAGetStandardLux(ucColortemp,ucTargetLuxTemp);
            //DebugMessageUart("Bypass ucLux", ucLux);
            
            usSensor = UserAdjustQAGetTargetSensor(ucLux);
            
		    //DebugMessageUart("QA Updata BK Sensor", GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            UserSetBacklightSensorTargetValue(usSensor); 
		}

	}
	
    SET_OSD_GAMMA(ucBackUpGamma);
	SET_COLOR_TEMP_TYPE(ucBackupColortemp);

	RTDNVRamSaveOsdUser2Data();
}


#if (_PRODUCT_ID_SEL != RTD2785TM_U231A_RL6432_216PIN_A_BBK_FHD)
//--------------------------------------------------
// Description  : Init DS1631 Temperature Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit InitDS1631(void)
{
    BYTE ucCmd_Buf[2];

    ucCmd_Buf[0]=0xac; 	// Access Config
    ucCmd_Buf[1]=0x0c;	//
    if(UserCommonEepromIICWrite(DS1631_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
        //DebugMessageSystem("Temp Sensor IIC Fail:", DS1631_IIC_ADDR);
        return _FAIL;
    }

    ucCmd_Buf[0]=0x51;	//start convert T command
    if(UserCommonEepromIICWrite(DS1631_IIC_ADDR, 0, 0, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
        //DebugMessageSystem("Temp Sensor IIC Fail 1:", DS1631_IIC_ADDR);
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Temperature Sensor Handler ��oTemperature range: -55 ~ 125 degree
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserTemperatureSensorHandler(void)
{
    static bit g_bInitState = _FAIL;
    BYTE ucCmd_Buf[1];
    WORD temperature;
    BYTE SignBit;

    ucCmd_Buf[0] = 0xAA; //read Temperature CMD
    if(g_bInitState == _FAIL)
    {
    	g_bInitState = InitDS1631();
    	return;
    }

    if(UserCommonEepromIICWrite(DS1631_IIC_ADDR, 0, 0, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0, _WRITE_SIZE_8) == _FAIL)
    {
        DebugMessageSystem("Temp Sensor IIC Fail 3:", DS1631_IIC_ADDR);
        return;
    }
    
    if(UserCommonEepromIICRead(DS1631_IIC_ADDR, 0, 0, 2, pData, _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC0) == _FAIL)
    {
        return;
    }

    temperature	= (((WORD)pData[0]<<8)|pData[1]);

    // pData[0]-TH, MS Byte,bit15=S, bit14=2^6,bit13=2^5,...,bit8=2^0 // range: -55 ~ 125 degree
    // pData[1]-TL, LS Byte,bit7=2^-1,bit6=2^-2,bit4=2^-4,bit3~bit0=0
    temperature = pData[0]&0x7F;
    SignBit		= pData[0]&0x80;// Positive S=0, Negative S=1

    uctemperaturesensor = temperature;
        
    if(SignBit) // Negative
    {

    }
    else
    {

    }
}
#endif

#endif //#if(_ENABLE_BACKLIGHT_SENSOR)

#if(_ENABLE_AMBIENTLIGHT_SENSOR)

#if 0
//The TSL258x is controlled and monitored by sixteen registers and a command register accessed through the
//serial interface. These registers provide for a variety of control functions and can be read to determine results
//of the ADC conversions. The register set is summarized in Table 2.

//------------Table 2. Register Address----------
//ADDRESS RESISTER NAME REGISTER FUNCTION R/W
//.. COMMAND Specifies register address W
//00h CONTROL Control of basic functions
//01h TIMING Integration time/gain control
//02h INTERRUPT Interrupt control
//03h THLLOW Low byte of low interrupt threshold   R/W
//04h THLHIGH High byte of low interrupt threshold
//05h THLLOW Low byte of high interrupt threshold
//06h THLHIGH High byte of high interrupt threshold
//07h ANALOG Analog control register
//12h ID Part number / Rev ID
//13h CONSTANT Number 4 (for SMBus block reads)
//14h DATA0LOW ADC channel 0 LOW data register
//15h DATA0HIGH ADC channel 0 HIGH data register R
//16h DATA1LOW ADC channel 1 LOW data register
//17h DATA1HIGH ADC channel 1 HIGH data register
//18h TIMERLOW Manual integration timer LOW register
//19h TIMERHIGH Manual integration timer HIGH register

//Table 3. Command Register
//Bit:  7      6 5       4 3 2 1 0   Reset
//     CMD TRANSACTION    ADDRESS     00h
// 
//FIELD       BIT DESCRIPTION
//    CMD      7  Select command register. Must write as 1 when addressing COMMAND register.
//----------------------
//                00 Byte protocol read/write byte protocol
//TRANSACTION 6:5 01 Word protocol read/write word protocol
//----------------------
//                
//ADDRESS     4:0 Register Address/Special Function. This field selects the specific control or status register  
//                for following write and read commands according to Table 2
//----------------------

// Integration time scaling factors
//...................................................
#define CH_SCALE 16 // scale channel values by 2^16
#define RATIO_SCALE 9 // scale ratio by 2^9
#define NOM_INTEG_CYCLE 148 // Nominal 400 ms integration. See Timing Register
#define LUX_SCALE 16 // scale by 2^16
// Gain scaling factors
//...................................................
#define CH0GAIN128X 107 // 128X gain scalar for Ch0
#define CH1GAIN128X 115 // 128X gain scalar for Ch1
//...................................................
// FN Package coefficients
//...................................................
// For Ch1/Ch0=0.00 to 0.30:
// Lux=0.13*Ch0.0.24*Ch1
//
// For Ch1/Ch0=0.30 to 0.38:
// Lux=0.1649*Ch0.0.3562*Ch1
//
// For Ch1/Ch0=0.38 to 0.45:
// Lux=0.0974*Ch0.0.1786*Ch1
//
// For Ch1/Ch0=0.45 to 0.54:
// Lux=0.062*Ch0.0.10*Ch1
//
// For Ch1/Ch0>0.54:
// Lux/Ch0=0
//
//...................................................
#define K1C 0x009a // 0.30 * 2^RATIO_SCALE
#define B1C 0x2148 // 0.13 * 2^LUX_SCALE
#define M1C 0x3d71 // 0.24 * 2^LUX_SCALE

#define K2C 0x00c3 // 0.38 * 2^RATIO_SCALE
#define B2C 0x2a37 // 0.1649 * 2^LUX_SCALE
#define M2C 0x5b30 // 0.3562 * 2^LUX_SCALE

#define K3C 0x00e6 // 0.45 * 2^RATIO_SCALE
#define B3C 0x18ef // 0.0974 * 2^LUX_SCALE
#define M3C 0x2db9 // 0.1786 * 2^LUX_SCALE

#define K4C 0x0114 // 0.54 * 2^RATIO_SCALE
#define B4C 0x0fdf // 0.062 * 2^LUX_SCALE
#define M4C 0x199a // 0.10 * 2^LUX_SCALE

#define K5C 0x0114 // 0.54 * 2^RATIO_SCALE
#define B5C 0x0000 // 0.00000 * 2^LUX_SCALE
#define M5C 0x0000 // 0.00000 * 2^LUX_SCALE
// lux equation approximation without floating point calculations
      
//////////////////////////////////////////////////////////////////////////////
// Routine: unsigned int CalculateLux(unsigned int ch0, unsigned int ch0,int iType)
//
// Description: Calculate the approximate illuminance (lux) given the raw
// channel values of the TSL2581. The equation if implemented
// as a piece.wise linear approximation.
//
// Arguments: unsigned int iGain . gain, where 0:1X, 1:8X, 2:16X, 3:128X
// unsigned int tIntCycles . INTEG_CYCLES defined in Timing Register
// unsigned int iType . package type (1:CS)
// unsigned int ch0 . raw channel value from channel 0 of TSL2581
// unsigned int ch1 . raw channel value from channel 1 of TSL2581
//
// Return: unsigned int . the approximate illuminance (lux)
//////////////////////////////////////////////////////////////////////////////

WORD CalculateLux(BYTE iGain, BYTE tIntCycles, WORD ch0, WORD ch1, BYTE iType)
{
	//........................................................................
	// first, scale the channel values depending on the gain and integration time
	// 1X, 400ms is nominal setting
	DWORD chScale0=0;//ch_temp0=0x00;
	DWORD chScale1=0;//ch_temp1=0x00;
	DWORD channel0=0;//channel_temp0=0x00;
	DWORD channel1=0;//channel_temp1=0x00;
			
	DWORD temp;
	WORD lux;

	DWORD ratio1 = 0;//,ratio1_temp=0x000000;

	// round the ratio value
	DWORD ratio; // = (ratio1 + 1) >> 1;
	// is ratio <= eachBreak?
	WORD b, m;


	// No scaling if nominal integration (148 cycles or 400 ms) is used
	if (tIntCycles == NOM_INTEG_CYCLE)
	{
	    chScale0 = (DWORD)1 << CH_SCALE;  //65536;
	}
	else
	{
		chScale0 = (DWORD)(NOM_INTEG_CYCLE << CH_SCALE) / tIntCycles;
	}
	
	switch (iGain)
	{
		case 0: // 1x gain
			chScale1 = chScale0; // No scale. Nominal setting
		break;
		case 1: // 8x gain
			chScale0 = chScale0 >> 3; // Scale/multiply value by 1/8
			chScale1 = chScale0;
		break;
		case 2: // 16x gain
			chScale0 = chScale0 >> 4; // Scale/multiply value by 1/16
			chScale1 = chScale0;
		break;
		case 3: // 128x gain
			chScale1 = chScale0 / CH1GAIN128X; //Ch1 gain correction factor applied
			chScale0 = chScale0 / CH0GAIN128X; //Ch0 gain correction factor applied
		break;
	}


	// scale the channel values
	channel0 = (ch0 * chScale0) >> CH_SCALE;
	channel1 = (ch1 * chScale1) >> CH_SCALE;


	//........................................................................
	// find the ratio of the channel values (Channel1/Channel0)
	// protect against divide by zero
	//unsigned long ratio1 = 0;
	if (channel0 != 0) ratio1 = (channel1 << (RATIO_SCALE+1)) / channel0;

    
	// round the ratio value
	ratio = (ratio1 + 1) >> 1;
	// is ratio <= eachBreak?
	//unsigned int b, m;

	switch (iType)
	{
		case 1: // FN package
			if ((ratio >= 0) && (ratio <= K1C))
			{
				b=B1C; 
				m=M1C;
			}
			else if (ratio <= K2C)
			{
				b=B2C;
				m=M2C;
			}
			else if (ratio <= K3C)
			{
				b=B3C; 
				m=M3C;
			}
			else if (ratio <= K4C)
			{
				b=B4C; 
				m=M4C;
			}
			else if (ratio > K5C)
			{
				b=B5C; 
				m=M5C;
			}
		break;
	}

	temp = ((channel0 * b) - (channel1 * m));
		
	// round lsb (2^(LUX_SCALE.1))
	temp += ((DWORD)1 << (LUX_SCALE-1));

	// strip off fractional portion
	lux = (WORD)(temp >> LUX_SCALE);
	
	return(lux);
}

//--------------------------------------------------
// Description  : Init Ambient light sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit AmbiSensor_TSL2581_InitADC(void)
{
	BYTE ucCmd_Buf[2];
    
    //SubAddr & Para;
    ucCmd_Buf[0]=0x80; //Set Command bit and Control Reg (0h|CMD) 
    ucCmd_Buf[1]=0x01; //power on sensor
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        DebugMessageSystem("Ambi TSL2581 IIC Fail:", _AMBI_SENSOR_TSL2581_IIC_ADDR);
		return _FAIL;
    }

    //SubAddr & Para;
    ucCmd_Buf[0]=0x81; //Set Command bit and ALS Timing Reg (1h|CMD)  
    ucCmd_Buf[1]=(255-NOM_INTEG_CYCLE); //set 399.6 ms integration cycle (255-NOM_INTEG_CYCLE)
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
		return _FAIL;
    }
    
    //SubAddr & Para;
    ucCmd_Buf[0]=0x82; //Set Command bit and Interrpt Reg (2h|CMD) 
    ucCmd_Buf[1]=0x00; //Disable the Interrupt
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
		return _FAIL;
    }

    //SubAddr & Para;
    ucCmd_Buf[0]=0x87; //Set Command bit and Analog Reg (7h|CMD) 
    ucCmd_Buf[1]=0x00; //Inital the 1x Gain.
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
		return _FAIL;
    }

	UserCommonTimerDelayXms(2); //after power is asserted, a 2-ms delay is required before asserting adc_en

    //SubAddr & Para;
    ucCmd_Buf[0]=0x80; //Set Command bit and Control Reg(0h|CMD) 
    ucCmd_Buf[1]=0x03; //ADC Enable&Power On.
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
		return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read luminance value from sensor module
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit AmbiSensor_TSL2581_ReadLux(void)
{
	BYTE ControlFlg=0,ucCmd_Buf[2],ucAdcChData[2];
	WORD usSensorLuxTmp;
	WORD usSensorDataCh0,usSensorDataCh1;

	ucCmd_Buf[0] = 0x80; //Set Command bit and Control Reg (0h|CMD) 
    if(UserCommonEepromIICRead(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, ucCmd_Buf, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
		usSensorLux = 0;
        return _FAIL;
    }

	ControlFlg = ucCmd_Buf[0];
	
	if((ControlFlg&0x10) == 0x10)
	{
	    // enable the adc channels data0:0x14
	    ucCmd_Buf[0]=0xB4;   //Set Command bit and Word bit and ADC channel 0
        if(UserCommonEepromIICRead(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 2, ucAdcChData, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        {
            return _FAIL;
        }
		usSensorDataCh0 = (WORD)ucAdcChData[1] * 256 + ucAdcChData[0];

		// enable the adc channels data1:0x16
 		ucCmd_Buf[0]=0xB6; //Set Command bit and Word bit and ADC channel 1
        if(UserCommonEepromIICRead(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 2, ucAdcChData, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        {
            return _FAIL;
        }
		usSensorDataCh1 = (WORD)ucAdcChData[1] * 256 + ucAdcChData[0];

		// power off the sensor
		ucCmd_Buf[0]=0x80; //Set Command bit and Byte bit and Control Reg
		ucCmd_Buf[1]=0x00;
        if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL2581_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
			return _FAIL;
        }

		usSensorLuxTmp = CalculateLux(0, NOM_INTEG_CYCLE, usSensorDataCh0, usSensorDataCh1, 1);
    
		if(usSensorLux!=usSensorLuxTmp)
		{
			usSensorLux = usSensorLuxTmp;
		}

		return _SUCCESS;
	}
	else
	{
		return _FAIL;
	}
	
}

//--------------------------------------------------
// Description  : Init Ambient light sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit AmbiSensor_TSL45315_Init(void)
{		
	//---------------------------------------------------
    // Register Set
	// COMMAND [7] Select Command Register. Must write as 1.
	// -- COMMAND W Specifies register address
	// 0x00 CONTROL R/W Power on/off and single cycle
	// 0x01 CONFIG R/W Powersave Enable / Integration Time
	// 0x04 DATALOW R ALS Data LOW Register
	// 0x05 DATAHIGH R ALS Data HIGH Register
	//---------------------------------------------------

	BYTE ucCmd_Buf[2];	
	
	ucCmd_Buf[0] = 0x80;  // Control Register (0x00)
	ucCmd_Buf[1] = 0x03;  // MODE[1:0] 00:Power Down 11:Normal Operation
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL45315_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        DebugMessageSystem("Ambi TSL45315 IIC Fail:", _AMBI_SENSOR_TSL45315_IIC_ADDR);
        return _FAIL;
    }
	
	ucCmd_Buf[0] = 0x81;  // Configuration Register (0x01)
	ucCmd_Buf[1] = 0x08;  // TCNTRL[1:0] 00:multi = 1x Tint = 400 ms  01:multi = 2x Tint = 200 ms 10:multi = 4x Tint = 100 ms
	// PSAVESKIP[3] PowerSave Mode. When asserted, the power save states are skipped following a light integration cycle for shorter sampling rates(Note A).
    // Note A:When PSAVESKIP = 0, the typical total cycle time is Tint + (60/MULTIPLIER) ms. When PSAVESKIP = 1, the typical total cycle time is Tint
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_TSL45315_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }
	
	return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read luminance value from sensor module
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit AmbiSensor_TSL45315_ReadLux(void)
{
	BYTE ucCmd_Buf[2];
	WORD usCurSensorValue;

    ucCmd_Buf[0] = 0x84; // ALS Data Registers (0x04 - 0x05)
	if(UserCommonEepromIICRead(_AMBI_SENSOR_TSL45315_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	{
		return _FAIL;
	}

 	// ADC Channel Data Registers (04h)
	// Data_LOW    04h  7:0 ADC lower byte
	// Data_HIGH   05h 15:8 ADC upper byte

    usCurSensorValue = ((WORD)(pData[1]<<8)|pData[0]);
	usSensorLux = usCurSensorValue;
		
	return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Init Ambient light sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit AmbiSensor_VEML6030_Init(void)
{
 //*************0: Configuration Register****************
//    ALS_GAIN    bit12 : 11  
//        00 = ALS gain x 1
//        01 = ALS gain x 2
//        10 = ALS gain x (1/8)
//        11 = ALS gain x (1/4)
//    ALS_IT       bit9 : 6
//        1100 = 25 ms
//        1000 = 50 ms
//        0000 = 100 ms
//        0001 = 200 ms
//        0010 = 400 ms
//        0011 = 800 ms
//    ALS_PERS     bit5 : 4
//        00 = 1
//        01 = 2
//        10 = 4
//        11 = 8
//    ALS_INT_EN    bit1   0 = ALS INT disable  1 = ALS INT enable
//    ALS_SD        bit0   0 = ALS power on     1 = ALS shut down

    BYTE ucCmd_Buf[2];

    // ALS CONF Data Registers (Write:0x00 16Bit)
    ucCmd_Buf[0]=0x80;   //bit7-0    // 400ms
    ucCmd_Buf[1]=0x10;   //bit15-8   // ALS gain x (1/4) 0x18  ALS gain x (1/8) 0x10
    
    if(UserCommonEepromIICWrite(_AMBI_SENSOR_VEML6030_IIC_ADDR, 0x00, 1, 2, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        //DebugMessageSystem("Ambi VEML6030 IIC Fail:",_AMBI_SENSOR_VEML6030_IIC_ADDR);
        //DebugMessageOsd("Ambi VEML6030 IIC Fail:",_AMBI_SENSOR_VEML6030_IIC_ADDR);
        
        return _FAIL;
    }
    
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read luminance value from sensor module
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD AmbiSensor_VEML6030_ReadLux(void)
{
	BYTE ucCmd_Buf[2];
	WORD usCurSensorValue;

    // ALS Data Registers (Read:0x04 16Bit)
    ucCmd_Buf[0] = 0x04; 
	if(UserCommonEepromIICRead(_AMBI_SENSOR_VEML6030_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	{
		return _FAIL;
	}
    usCurSensorValue = ((WORD)(pData[1]<<8)|pData[0])/8;
	usSensorLux = usCurSensorValue;
        DebugMessageUart("usambSensorLux == ",usSensorLux);
        DebugMessageSystem("usambSensorLux",usSensorLux);

	return _SUCCESS;
}

//--------------------------------------------------
// Description  : Ambient light sensor Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAmbiSensorADCStart(void)
{	
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
		return;
	}

	if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _OFF)
	{
	    ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
	}
	else
	{
	    ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
	}
	
    if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _OFF)
	{
        //return;
	}

	if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_NONE)
	{
		if(AmbiSensor_VEML6030_Init() == _SUCCESS)
		{
			g_bAmbiSensorInitState = _AMBI_DEVICE_ID_VEML6030;
		    DebugMessageUart("Ambi VEML6030 Init:", g_bAmbiSensorInitState);
            DebugMessageSystem("Ambi VEML6030 Init:", g_bAmbiSensorInitState);
		   // DebugMessageOsd("Ambi VEML6030 Init:", g_bAmbiSensorInitState);
            
		}
        #if 0
		else if(AmbiSensor_TSL45315_Init() == _SUCCESS) 
		{
			g_bAmbiSensorInitState = _AMBI_DEVICE_ID_TSL45315;
		    DebugMessageUart("Ambi TSL45315 Init:", g_bAmbiSensorInitState);
		}
		else if(AmbiSensor_TSL2581_InitADC() == _SUCCESS)
		{
			g_bAmbiSensorInitState = _AMBI_DEVICE_ID_TSL2581;
		    DebugMessageUart("Ambi TSL2581 Init:", g_bAmbiSensorInitState);
		}
        #endif
		else
		{
    		g_bAmbiSensorInitState = _AMBI_DEVICE_ID_NONE;
		    DebugMessageUart("Ambi Init Fail:", g_bAmbiSensorInitState);
            DebugMessageSystem("Ambi Init Fail:", g_bAmbiSensorInitState);
		    //DebugMessageOsd("Ambi Init Fail:", g_bAmbiSensorInitState);
		}
	}
	
    if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_VEML6030)
	{
        ScalerTimerReactiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_AMBI_SENSOR_HANDLER);     
	}
	else if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_TSL45315)
	{
        ScalerTimerReactiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_AMBI_SENSOR_HANDLER); 
	}
	else if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_TSL2581)
	{
        ScalerTimerReactiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_AMBI_SENSOR_HANDLER);     
	}
    else
    {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_AMBI_SENSOR_HANDLER);   
        ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
    }
}

//--------------------------------------------------
// Description  : Get Current Ambient light 
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit AmbiSensor_ReadLux(void)
{
#if 0
	if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_TSL2581)
	{
		return AmbiSensor_TSL2581_ReadLux();
	}
	else if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_TSL45315)
	{
		return AmbiSensor_TSL45315_ReadLux();
	}
	else 
#endif
    if(g_bAmbiSensorInitState == _AMBI_DEVICE_ID_VEML6030)
	{
		return AmbiSensor_VEML6030_ReadLux();
	}
	else
	{
	    ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
        return _FAIL;
	}
}

//--------------------------------------------------
// Description  : Ambient light sensor filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#define AMBI_LUMI_INVALID_VALUE      0xffff
#define AMBI_LUMI_VALIDATION_WINDOW  4  
#define AMBI_LUMI_LEVEL_MARGIN       18

//Range for curve(Added by KW)
#define Range_ALC0_L	0
#define Range_ALC0_H	15

#define Range_ALC1_L	15
#define Range_ALC1_H	60

#define Range_ALC2_L	60
#define Range_ALC2_H	120

#define Range_ALC3_L	120
#define Range_ALC3_H	200

#define Range_ALC4_L	200
#define Range_ALC4_H	300

#define Range_ALC5_L	300
#define Range_ALC5_H	400

//Grade for curve
#define Grade_For_Change_ALCcurve0	2
#define Grade_For_Change_ALCcurve1	5
#define Grade_For_Change_ALCcurve2	5
#define Grade_For_Change_ALCcurve3	10
#define Grade_For_Change_ALCcurve4	15
#define Grade_For_Change_ALCcurve5	15

bit ambiLumi_filter(WORD ambiLumi, WORD *pFilteredValue)
{
	static WORD confirmedAmbiLumiValue = AMBI_LUMI_INVALID_VALUE;
	static WORD confirmAmbiLumiValue = AMBI_LUMI_INVALID_VALUE;
	
	static BYTE confirmCounter = 0;

	BYTE ambiLumiChanged = 0;
	BYTE Check_Changed_LEVEL_MARGIN;

	//--------ambient light sensor update-------------------
	if ((GET_OSD_STATE() > _MENU_NONE)||(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS() == _OFF)) // OSD On. Sensor off. 
	{
		return _FAIL;
	}

    //for Brun In flag
	if (GET_OSD_FACTORY_MODE_BRUNIN()==_ON) // burn in mode 
    {
		return _FAIL;
    }
    
    //for LightBoxMode flag
    if(GET_OSD_LIGHTBOXMODE_STATUS()==_ON)
    {
		return _FAIL;
    }

	//for Calibration Mode flag
    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
	{
        return _FAIL;
	}
    
    //for No Signal flag
	if(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)
    {
        return _FAIL;
    }

    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SAVE_USER2_DATA) == _TRUE)
    {
        DebugMessageUart("Ambi user2 save...", 0);
        return _FAIL;
    }

    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_VALUE_UPDATE) == _TRUE)
    {
        DebugMessageUart("Ambi Sensor update...", 0);
        return _FAIL;
    }

    //for Backlight ON flag
    if(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)
    {
        DebugMessageUart(">>Ambi Backlight Flag:", GET_PANELPOWERSTATUS());
		return _FAIL;
    } 

	if(UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE) == _ON)
    {
        DebugMessageUart("One Key Lumi Flag...", 0);
        return _FAIL;
    }

	if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
	{
        DebugMessageUart("Scaler Enhancement Flag...", 0);
        return _FAIL;
	}

	if(UserCommonNVRamGetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE) == _ON)
    {
        DebugMessageUart("FPGA Enhancement Flag...", 0);
        return _FAIL;
    }
	//--------ambient light sensor update-------------------
	
    DebugMessageUart("ambi Curr:", ambiLumi);
    //DebugMessageUart("ambi confirmed:", confirmedAmbiLumiValue);
    //DebugMessageUart("ambi confirm:", confirmAmbiLumiValue);
    //DebugMessageUart("ambi abs:", (IsGammaOptionDICOMALC(GET_OSD_GAMMA(GET_OSD_SELECT_REGION())) == _TRUE ? (_AMBIENT_SENSOR_LIGHT_LEVEL/_ALC_AUTO) : (_AMBIENT_SENSOR_LIGHT_LEVEL/10)));
#if 0   //Current range of Lux:10-60, 60-200, 200-250, 250-300, 300-400 (For switching curve)
    if((ambiLumi<=10)&&(ambiLumi>=0))
        Check_Changed_LEVEL_MARGIN = 5;
    else if((ambiLumi<=60)&&(ambiLumi>10))
        Check_Changed_LEVEL_MARGIN = 5;
    else if((ambiLumi<=200)&&(ambiLumi>60))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=250)&&(ambiLumi>200))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=300)&&(ambiLumi>250))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=400)&&(ambiLumi>300))
        Check_Changed_LEVEL_MARGIN = 10;
    else
        Check_Changed_LEVEL_MARGIN = 20;     
#endif
#if 0   //Added by KW
    if((ambiLumi<=15)&&(ambiLumi>=0))
        Check_Changed_LEVEL_MARGIN = 5;
    else if((ambiLumi<=60)&&(ambiLumi>15))
        Check_Changed_LEVEL_MARGIN = 5;
    else if((ambiLumi<=180)&&(ambiLumi>60))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=300)&&(ambiLumi>180))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=350)&&(ambiLumi>300))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=400)&&(ambiLumi>350))
        Check_Changed_LEVEL_MARGIN = 10;
    else
        Check_Changed_LEVEL_MARGIN = 20;
#endif
#if 1   //Added by KW
    if((ambiLumi<=Range_ALC0_H)&&(ambiLumi>=Range_ALC0_L))
        Check_Changed_LEVEL_MARGIN = 5;
    else if((ambiLumi<=Range_ALC1_H)&&(ambiLumi>Range_ALC1_L))
        Check_Changed_LEVEL_MARGIN = 5;
    else if((ambiLumi<=Range_ALC2_H)&&(ambiLumi>Range_ALC2_L))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=Range_ALC3_H)&&(ambiLumi>Range_ALC3_L))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=Range_ALC4_H)&&(ambiLumi>Range_ALC4_L))
        Check_Changed_LEVEL_MARGIN = 10;
    else if((ambiLumi<=Range_ALC5_H)&&(ambiLumi>Range_ALC5_L))
        Check_Changed_LEVEL_MARGIN = 10;
    else
        Check_Changed_LEVEL_MARGIN = 20;
#endif              
    //Check_Changed_LEVEL_MARGIN = (IsGammaOptionDICOMALC(GET_OSD_GAMMA()) == _TRUE ? (_AMBIENT_SENSOR_LIGHT_LEVEL/_ALC_AUTO) : AMBI_LUMI_LEVEL_MARGIN);
    
  	if(AMBI_LUMI_INVALID_VALUE == confirmedAmbiLumiValue)
	{ /*first time*/
		confirmCounter = 0;
		confirmedAmbiLumiValue = ambiLumi;
		ambiLumiChanged = 0;
        confirmAmbiLumiValue = ambiLumi;
        //usAmb_Light = ambiLumi;
		//SetAmbiSensorValue(ambiLumi);
		//DebugMessageUart("ambi first:", ambiLumi);
	}
	else
	{				  
		/*ambi lumi changed?*/ 
	    if((WORD)(ABSDWORD(ambiLumi,confirmedAmbiLumiValue)) > Check_Changed_LEVEL_MARGIN)
		{
			if(0 == confirmCounter)
			{
				confirmCounter = AMBI_LUMI_VALIDATION_WINDOW; /*start confirming*/
				confirmAmbiLumiValue = ambiLumi;
                //DebugMessageUart("ambi Last:", confirmedAmbiLumiValue);
                //DebugMessageUart("ambi  Cur:", ambiLumi);
			}
			else
			if((WORD)(ABSDWORD(ambiLumi,confirmAmbiLumiValue)) < Check_Changed_LEVEL_MARGIN)
		    {
				confirmCounter--;
                DebugMessageUart("ambi Counter:", confirmCounter);
				
				if(0 == confirmCounter)
				{ /* confirmed */		
			
					confirmedAmbiLumiValue = ambiLumi;
					ambiLumiChanged = 1;
					DebugMessageUart(">>>new AmbiLumi<<<", confirmedAmbiLumiValue);
				}
			}
			else
			{ /* confirm failed, start again*/
				confirmCounter = AMBI_LUMI_VALIDATION_WINDOW; /*start confirming*/
				confirmAmbiLumiValue = ambiLumi;
				//DebugMessageUart("ambi filter:", ambiLumi);
			}
		}
		else
		{ /* confirm failed, start again*/
			confirmCounter = AMBI_LUMI_VALIDATION_WINDOW; /*start confirming*/
			//DebugMessageUart("ambi filter 2:", confirmAmbiLumiValue);
		}
	}
    DebugMessageSystem("Flag ambiLumi Changed:", ambiLumiChanged);
	*pFilteredValue = confirmedAmbiLumiValue;

	return ambiLumiChanged;
}	


//--------------------------------------------------
// Description  : Get the value of the AMB Front Lux corresponding to a current location by the Backlight Sensor value.
// Input Value  : Ambient Sensor Position
// Output Value : None
//--------------------------------------------------
#define LUMI_REFLECTION_COEFFCIENT   0.003//0.005 //0.087   //Coefficient of reflection
#define LUMI_DIVIDE_TO_BACKLIGHT     (_AMBIENT_SENSOR_LIGHT_LEVEL/100)    //User to adjust backlight according to the value of sensor

WORD UserAdjustQAGetCurrAmbLux(void)
{
	WORD usSensor = 0; 
	float ucLuxA,ucLuxB;
	BYTE ucLuxABMode;

    //Use the Sensor Value to calculate the real Luminance Value;
    //y = a*x + b   <------>    usAMBLux = ucLuxA*usSensorLux + ucLuxB
    usSensor = usSensorLux;     //Changed By KW

    // Load data
	RTDNVRamLoadPanelAmbABData();
    //Calc A,B Data
    //memcpy(&ucLuxA,&g_stPanelAmbABData.usA_Data,4);
    //DebugMessageUart("ucLuxA:", ucLuxA);
    //ucLuxA = 711.86;     //DebugMessageSystem(x,y) Only can show the data without float
    //ucLuxA = (WORD)(g_stPanelAmbABData.usA_Data)&0xFFFF; 
    if(((WORD)(g_stPanelAmbABData.usA_Data)&0xFFFF) == 0xFFFF)    //If the value of usA in Eeprom is invalid, use the default value.
    {
        g_stPanelAmbABData.usA_Data = _DEFAULT_MIDDLE_A_DATA;
        RTDNVRamSavePanelAmbABData();
    }
    ucLuxA = g_stPanelAmbABData.usA_Data;
    DebugMessageSystem("g_stPanelAmbABData.usA_Data:", g_stPanelAmbABData.usA_Data);
    //DebugMessageSystem("g_stAmbABDataDefault.usA_Data:",_DEFAULT_MIDDLE_A_DATA);
    DebugMessageSystem("ucLuxA:", ucLuxA);

    ucLuxA = fabs(ucLuxA/1000);    //Change by KW
    DebugMessageUart("ucLuxA: ", ucLuxA);
    DebugMessageSystem("ucLuxA / 1000:", ucLuxA);

    //memcpy(&ucLuxB,&g_stPanelAmbABData.usB_Data,4);
    //DebugMessageUart("ucLuxB:", ucLuxB);
    if(((WORD)(g_stPanelAmbABData.usB_Data)&0xFFFF) == 0xFFFF)    //If the value of usA in Eeprom is invalid, use the default value.
    {
        g_stPanelAmbABData.usB_Data = _DEFAULT_MIDDLE_B_DATA;
        RTDNVRamSavePanelAmbABData();
    }
    ucLuxB = g_stPanelAmbABData.usB_Data;
    DebugMessageSystem("g_stPanelAmbABData.usB_Data:", g_stPanelAmbABData.usB_Data);
    DebugMessageSystem("ucLuxB:", ucLuxB);    
    
    ucLuxB = fabs(ucLuxB/1000);  //Change by KW
    DebugMessageUart("ucLuxB: ", ucLuxB);
    DebugMessageSystem("ucLuxB / 1000:", ucLuxB);


    UserCommonEepromRead(_USER_PANEL_AMB_AB_VERSION_ADDRESS, 1, &ucLuxABMode);
    DebugMessageSystem("ucLuxABMode:", ucLuxABMode); 
    //DebugMessageUart("LuxAB Ver", ucLuxABMode);    
    //DebugMessageUart("usSensor:", usSensor);
	if((ucLuxABMode == 0x00)||(ucLuxABMode == 0xFF))
	{
    	usAMBLux = (WORD)((float)usSensor - ucLuxB)/ucLuxA;
	    DebugMessageUart("Lux:", usAMBLux);
    }
    else
	{
	    usAMBLux = (WORD)((float)usSensor*ucLuxA + (float)ucLuxB);
	    DebugMessageUart("QA,Lux:", usAMBLux);
        DebugMessageSystem("QA,Lux:", usAMBLux);
	}

 	return _SUCCESS;
}

//--------------------------------------------------
// Description  : User Get Dicom ALC Index value from Ambi sensor luminance
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserGetDICOMALCAmbiSensor(void)
{
#if(_ENABLE_AMBIENTLIGHT_SENSOR)
    if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS() == _ON)
    {
        DebugMessageSystem("UserGetDICOMALC: Amb_Light =", usAmb_Light);
        if(usAmb_Light > _AMBIENT_SENSOR_LIGHT_LEVEL)
        {
            DebugMessageSystem("Current Dicom ALC Curve = _ALC_OPERATING_ROOMS", _ALC_OPERATING_ROOMS);
            ALC_state = _ALC_OPERATING_ROOMS;
            return _ALC_OPERATING_ROOMS;
        }
        else
        {
            DebugMessageUart("Dicom ALC:", ((usAmb_Light/(_AMBIENT_SENSOR_LIGHT_LEVEL/_ALC_AUTO))%(_ALC_AUTO)));
            if((usAmb_Light<=Range_ALC0_H)&&(usAmb_Light>=Range_ALC0_L))
            {
               DebugMessageSystem("Current Dicom ALC Curve = _ALC_X_RAY", _ALC_X_RAY);
               ALC_state = _ALC_X_RAY;
               return _ALC_X_RAY;
            }
            else if((usAmb_Light<=Range_ALC1_H)&&(usAmb_Light>Range_ALC1_L))
            {
               DebugMessageSystem("Current Dicom ALC Curve = _ALC_CT_MR_NM", _ALC_CT_MR_NM);
               ALC_state = _ALC_CT_MR_NM;
               return _ALC_CT_MR_NM;
            }
            else if((usAmb_Light<=Range_ALC2_H)&&(usAmb_Light>Range_ALC2_L))
            {
                DebugMessageSystem("Current Dicom ALC Curve = _ALC_STAFF_OFFICES", _ALC_STAFF_OFFICES);
                ALC_state = _ALC_STAFF_OFFICES;
                return _ALC_STAFF_OFFICES;
            }                
            else if((usAmb_Light<=Range_ALC3_H)&&(usAmb_Light>Range_ALC3_L))
            {
                DebugMessageSystem("Current Dicom ALC Curve = _ALC_HOSPITAL_CLINICAL_VIEWING", _ALC_HOSPITAL_CLINICAL_VIEWING);
                ALC_state = _ALC_HOSPITAL_CLINICAL_VIEWING;
                return _ALC_HOSPITAL_CLINICAL_VIEWING;
            }                
            else if((usAmb_Light<=Range_ALC4_H)&&(usAmb_Light>Range_ALC4_L))
            {
                DebugMessageSystem("Current Dicom ALC Curve = _ALC_EMERGENCY_MEDICINE", _ALC_EMERGENCY_MEDICINE);
                ALC_state = _ALC_EMERGENCY_MEDICINE;
                return _ALC_EMERGENCY_MEDICINE;
            }                
            else if((usAmb_Light<=Range_ALC5_H)&&(usAmb_Light>Range_ALC5_L))
            {
                DebugMessageSystem("Current Dicom ALC Curve = _ALC_OPERATING_ROOMS", _ALC_OPERATING_ROOMS);
                ALC_state = _ALC_OPERATING_ROOMS;
                return _ALC_OPERATING_ROOMS;
            }   
            //return ((usAmb_Light/(_AMBIENT_SENSOR_LIGHT_LEVEL/_ALC_AUTO))%(_ALC_AUTO));
        }
    }
#endif
    DebugMessageSystem("Current Dicom ALC Curve = _ALC_X_RAY", _ALC_X_RAY);
    DebugMessageSystem("Ambient Sensor State = OFF", _ALC_X_RAY);
    ALC_state = _ALC_X_RAY;
    return _ALC_X_RAY;
}

//--------------------------------------------------
// Description  : According to the Ambient light to change the panel backlight PWM 
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SetAmbiSensorValue(WORD btData)
{
    if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _ON)  //Ambilight Sensor is on
    {
        if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()) ||
            IsGammaOptionMCUCalibration(GET_OSD_GAMMA()) ||
            IsGammaOptionPCCalibration(GET_OSD_GAMMA()) ||
            IsGammaOptionNative(GET_OSD_GAMMA()))
        {

        }
        else if(IsGammaOptionDICOM(GET_OSD_GAMMA()))
        {
#if ((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB) || (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB))
            if(GET_OSD_DICOMALC()/(_ALC_AUTO) == _TRUE)
            {
                // == _ALC_AUTO
                usAmb_Light = btData;
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
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
            if((GET_OSD_DICOMALC()/(_ALC_AUTO) == _TRUE)/*&&(IsGammaOptionDICOMALC(GET_OSD_GAMMA()))*/)
            {
                // == _ALC_AUTO
                usAmb_Light = btData;
                //DebugMessageUart("usAmb_Light", usAmb_Light);
#if(_GAMMA_FUNCTION == _ON)
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                if(GET_OSD_GAMMA() != _GAMMA_OFF)
                {
               // DebugMessageUart("GET_OSD_GAMMA()", GET_OSD_GAMMA());
                    UserAdjustGamma(GET_OSD_GAMMA());
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                }
#endif
            }
            else
            {
/*            
                // == _ALC_AUTO 
                usAmb_Light = btData;
                SET_OSD_GAMMA(_GAMMA_DICOM200 + UserGetDICOMALCAmbiSensor());
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
*/
            }
#else
#warning "!!!Please Check ALC"
#endif
        }
        else
        {
            usAmb_Light = btData;
            if(usAmb_Light > _AMBIENT_SENSOR_LIGHT_LEVEL)
            {
                UserAdjustBacklight(100);
            }
            else
            {
                //UserAdjustBacklight(usAmb_Light/4);
                UserAdjustBacklight((usAmb_Light/LUMI_DIVIDE_TO_BACKLIGHT)*5/4);    
            }
        }
    }
}

//--------------------------------------------------
// Description  : Ambient light sensor Hander
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAmbiSensorHander(void)
{
    WORD filteredAmbiLumi;
	
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
		return;
	}

    if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _OFF)
	{
		ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
	}
	else
	{
		ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
	}
	
    if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _OFF)
	{
        //return;
	}

	//for No Signal flag
	if(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)
    {
        return;
    }

    //Add By KW
    if((GET_OSD_DICOMALC()/(_ALC_AUTO) != _TRUE) || (Monitor_Restart == 1))
    {
        pre_ALC_Auto = 1;
        Monitor_Restart = 0;
    }    
    
    //------------------------------------
    //Read current ambi sensor Lux
    if(AmbiSensor_ReadLux())
    {
        if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _ON)
        {
            UserAdjustQAGetCurrAmbLux();    //Added By KW
            Lum_Real =  usAMBLux;   //Real value of light
            DebugMessageSystem("Lum_Real =", Lum_Real);
            if(ambiLumi_filter(Lum_Real, &filteredAmbiLumi))//if(ambiLumi_filter(usAmb_Light, &filteredAmbiLumi))
            {
                DebugMessageUart("filteredAmbiLumi", filteredAmbiLumi);
            
                SetAmbiSensorValue((WORD)filteredAmbiLumi);
                DebugMessageSystem("AmbLumi after filtering = Make change",filteredAmbiLumi);
            }
            else   //Considering the Luminance don't need to be changed after filtering
            {
                DebugMessageSystem("AmbLumi after filtering = Not change",filteredAmbiLumi);
            }
            //Add By KW
            if((GET_OSD_DICOMALC()/(_ALC_AUTO) == _TRUE) && (pre_ALC_Auto == 1))
            {
                //SetAmbiSensorValue((WORD)filteredAmbiLumi);
                SetAmbiSensorValue(Lum_Real);            
                pre_ALC_Auto = 0;
            }
            DebugMessageSystem("ALC_state =", ALC_state);
            
            Lum_RealUsing = filteredAmbiLumi;
            DebugMessageSystem("Lum_RealUsing =", Lum_RealUsing);
            Lum_RealFiltered = filteredAmbiLumi*LUMI_REFLECTION_COEFFCIENT;
        }
    }
}

#endif //End #if (_ENABLE_AMBIENTLIGHT_SENSOR)

#if (_ENABLE_DISTANCE_SENSOR)
//--------------------------------------------------
// Define VCNL Device ID 
//--------------------------------------------------
typedef enum
{
    _DISTANCE_DEVICE_ID_NONE,
    _DISTANCE_DEVICE_ID_VCNL4020,   
    _DISTANCE_DEVICE_ID_VCNL4200,   
    _DISTANCE_DEVICE_ID_AMOUNT,
}EnumVCNLDeviceID;

BYTE g_bVCNLSensorInitDeviceID  = _DISTANCE_DEVICE_ID_NONE; 
static bit g_bDistanceSensorPowerStatus = _ON;

//--------------------------------------------------
// Description  : Init Distance Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit InitVCNL4020(void)
{
	BYTE ucCmd_Buf[2];

	// Set current to 200mA	->Bit[5-0]From 0mA to 200mA steps to 10mA 0=0mA 1=10mA...20=200MA (2=20MA=DEFAULT)
	ucCmd_Buf[0]=0x83;
	ucCmd_Buf[1]=0x14;  
	if(UserCommonEepromIICWrite(VCNL4020_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
        DebugMessageUart("VCNL4020 IIC Fail:", VCNL4020_IIC_ADDR);
        //DebugMessageOsd("VCNL4020 IIC Fail:", VCNL4020_IIC_ADDR);
        
		return _FAIL;
	}

	//set proximity rate to 4/s ->Bit[2-0] 000-1.95c/s(DEFAULT) 001-3.90625c/s 010-7.8125c/s 011-16.625c/s 100...
	ucCmd_Buf[0]=0x82;
	ucCmd_Buf[1]=0x01;	
	if(UserCommonEepromIICWrite(VCNL4020_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

	// enable prox in selftimed mode ->Bit1:prox_en Enable  Bit0:selftimed_en Enable 
	ucCmd_Buf[0]=0x80;
	ucCmd_Buf[1]=0x03;	
	if(UserCommonEepromIICWrite(VCNL4020_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}
	
	ScalerTimerDelayXms(30);

	return _SUCCESS;

}

//--------------------------------------------------
// Description  : Init Distance Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit InitVCNL4200(void)
{
	BYTE ucCmd_Buf[3];

	//Send Byte .. Write Command to VCNL4200
	// 1 7              1 1 8            1 8             1 8              1 1
	// S Slave Address Wr A Command Code A Data Byte Low A Data Byte High A P
	
	// COMMAND CODE: 03H_L (03H DATA BYTE LOW)
	// PS_Duty Bit[7:6](00)= 1/160,(01)= 1/320,(10)= 1/640,(11)= 1/1280 PS IRED on / off duty ratio setting
	// PS_PERS Bit[5:4](00)= 1,(01)= 2,(10)= 3,(11)= 4 PS interrupt persistence setting
	// PS_IT   Bit[3:1](000)= 1T, (001)= 1.5T, (010)= 2T, (011)= 4T, (100)= 8T, (101)= 9T
	// PS_SD   Bit[0]  0 = PS power on, 1 = PS shut down
	
	// COMMAND CODE: 03H_H (03H DATA BYTE HIGH)
	// PS_HD   Bit[3] = PS output is 12 bits, 1 = PS output is 16 bits
	// PS_INT  Bit[1:0] Proximity interrupt configuration (00)= interrupt disable, (01)= trigger by closing,(10)= trigger by away, (11)= trigger by closing and away
	ucCmd_Buf[0]=0x03;
	ucCmd_Buf[1]=0x4A;  
	ucCmd_Buf[2]=0x08; 
    if(GET_OSD_DISTANCE_SENSOR_STATUS() == _OSD_DISTANCE_OFF)
    {
        // PS shut down
    	ucCmd_Buf[1]=0x4B; 
    }
	if(UserCommonEepromIICWrite(VCNL4200_IIC_ADDR, ucCmd_Buf[0], 1, 2, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
        DebugMessageUart("VCNL4200 IIC Fail:", VCNL4200_IIC_ADDR);
		return _FAIL;
	}

    // COMMAND CODE: 04H_L (04H DATA BYTE LOW)
    // PS_MPS        Bit[6:5] Proximity multi pulse numbers (00)= 1,(01)= 2,(10)= 4, (11)= 8 multi pulses
    // PS_SMART_PERS Bit[4]   Proximity sensor smart persistence 0= disable; 1= enable
    // PS_AF         Bit[3]   0 = active force mode disable (normal mode), 1 = active force mode enable
	// PS_TRIG       Bit[2]   0 = no PS active force mode trigger, 1 = trigger one time cycle
    //               VCNL4200 output one cycle data every time host writes in ?��1?�� to sensor. The state returns to ?��0?��automatically.
    // PS_SC_ADV     Bit[1]   0 = typical sunlight immunity; 1 = 2 x typical sunlight immunity
    // PS_SC_EN      Bit[0]   PS sunlight cancel enable setting, 1 = sunlight cancellation function enable
    // COMMAND CODE: 04H_H (04H DATA BYTE HIGH)
    // PS_MS  Bit[5]   Proximity operation mode 0 = proximity normal operation with interrupt function, 1 = proximity detection logic output mode enable
    // PS_SP  Bit[4]   0 = typical sunlight capability, 1 = 1.5 x typical sunlight capability
	// PS_SPO Bit[3]   0 = output is 00h in sunlight protect mode, 1 = output is FFh in sunlight protect mode
	// LED_I  Bit[2:0] (000)=50mA,(001)=75mA,(010)=100mA,(011)=120mA,(100)=140mA,(101)=160mA,(110)=180mA,(111)=200mA
	ucCmd_Buf[0]=0x04;
	ucCmd_Buf[1]=0x61;
	ucCmd_Buf[2]=0x06;	
	if(UserCommonEepromIICWrite(VCNL4200_IIC_ADDR, ucCmd_Buf[0], 1, 2, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

	ScalerTimerDelayXms(10);
	
	return _SUCCESS;

}

//--------------------------------------------------
// Description  : Read Distance Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ReadVCNLSensorValue(void)
{
	BYTE ucCmd_Buf[2];
	WORD distance_val;
		
	if(g_bVCNLSensorInitDeviceID == _DISTANCE_DEVICE_ID_NONE)
	{
		if(InitVCNL4200() == _SUCCESS)
		{
			g_bVCNLSensorInitDeviceID = _DISTANCE_DEVICE_ID_VCNL4200;
		    DebugMessageUart("VCNL4200 Init:", g_bVCNLSensorInitDeviceID);
		}

		if(g_bVCNLSensorInitDeviceID  == _DISTANCE_DEVICE_ID_NONE)
		{
    		if( InitVCNL4020() == _SUCCESS) 
    		{
    			g_bVCNLSensorInitDeviceID = _DISTANCE_DEVICE_ID_VCNL4020;
    		    DebugMessageUart("VCNL4020 Init:", g_bVCNLSensorInitDeviceID);
    		   // DebugMessageOsd("VCNL4020 Init:", g_bVCNLSensorInitDeviceID);
                
    		}
        }
	}
		
	if((g_bVCNLSensorInitDeviceID == _DISTANCE_DEVICE_ID_NONE))
	{
	    DebugMessageUart("VCNL4020&VCNL4200 Init Fail:", 0);
        return _FAIL;
	}

	if(g_bVCNLSensorInitDeviceID == _DISTANCE_DEVICE_ID_VCNL4020)
	{// VCNL4020
	
		// prox data ready ?
		ucCmd_Buf[0]=0x80;	
	    if(UserCommonEepromIICRead(VCNL4020_IIC_ADDR, ucCmd_Buf[0], 1, 1, ucCmd_Buf, _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	    {
	        return _FAIL;
	    }
	    if(ucCmd_Buf[0]&_BIT5 == _FAIL)
		{
		    DebugMessageUart("VCNL4020 prox ready ?:", ucCmd_Buf[0]);
			return _FAIL;
		}
		
		// Receive Byte .. Read Data from VCNL4020
		// The high byte is stored in register #7 and the low byte in register #8.
		// read Proximity Measurement Result 
		ucCmd_Buf[0] = 0x87;    //High Byte
		ucCmd_Buf[1] = 0x88;	//Low Byte
	    if(UserCommonEepromIICRead(VCNL4020_IIC_ADDR, ucCmd_Buf[0], 1, 1, ucCmd_Buf, _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	    {
	        return _FAIL;
	    }
	    if(UserCommonEepromIICRead(VCNL4020_IIC_ADDR, ucCmd_Buf[1], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	    {
	        return _FAIL;
	    }
		distance_val = (WORD)ucCmd_Buf[0]*256 + ucCmd_Buf[1];
	}
	else if(g_bVCNLSensorInitDeviceID == _DISTANCE_DEVICE_ID_VCNL4200)	
	{// VCNL4200
	
		// Receive Byte .. Read Data from VCNL4200
		// S Slave Address Wr A Command Code A S Slave Address Rd A Data Byte Low A Data Byte High A P

		// read Proximity Measurement Result 
		ucCmd_Buf[0]= 0x08;	 
	    if(UserCommonEepromIICRead(VCNL4200_IIC_ADDR, ucCmd_Buf[0], 1, 2, ucCmd_Buf, _IIC_SYS_BUS_EXTDEV_I2C0, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	    {
		    DebugMessageUart("VCNL4200 08HL:", ucCmd_Buf[0]);
	        return _FAIL;
	    }
		distance_val = (WORD)ucCmd_Buf[1]*256 + ucCmd_Buf[0];
	}
		   // DebugMessageUart("distance_val:", distance_val);
	return distance_val;
}

//--------------------------------------------------
// Description  : Read Distance Sensor Time
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD GetHumanSensorTime(void)
{
    WORD DistanceSensorTime;
    switch(GET_OSD_DISTANCE_SENSOR_STATUS())
    {
        case _OSD_DISTANCE_OFF:
            DistanceSensorTime = 0;      // OFF
            break;
        case _OSD_DISTANCE_MODE1:
            DistanceSensorTime = 15;     // 15s
            break;
        case _OSD_DISTANCE_MODE2:
            DistanceSensorTime = 300;    // 5min
            break; 
        case _OSD_DISTANCE_MODE3:
            DistanceSensorTime = 900;    // 15min
            break;
        default:
            DistanceSensorTime = 0;
            break;
    }

    return DistanceSensorTime;
}
#define _ENABLE_DISTANCE_SENSOR_AVERAGE    _ON 
//--------------------------------------------------
// Description  : Distance Sensor filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit DistanceLumi_filter(void)
{
	BYTE DistanceLumiChanged = 0;

    //------------------------------------------------
    WORD CurrDistanceValue =0;
    static WORD PrevDistanceValue = 0;
    static BYTE TempDistanceSensorSensitivity = (5/*_OSD_DISTANCE_SENSOR_THRESHOLD_MIN*/ -1);
    static WORD DistanceValueStable = 0,DistanceValueOffCount = 0;
    static WORD PowerOffValue = 0;
    WORD DistanceSensorTime;
    static WORD PrevDistanceSensorTime = 0;
    //------------------------------------------------
#if 0//(_ENABLE_DISTANCE_SENSOR_AVERAGE == _ON)
	static BYTE ucDisSensorMultiple = 0;
	static WORD usDisMidofValue[3] = 0;
#endif

	
	if ((GET_OSD_STATE() > _MENU_NONE)||(GET_OSD_DISTANCE_SENSOR_STATUS() == _OSD_DISTANCE_OFF)) // OSD On. Sensor off. 
	{
        return _FAIL;
	}

    //for Brun In flag
	if (GET_OSD_FACTORY_MODE_BRUNIN()==_ON) // burn in mode 
    {
        return _FAIL;
    }
    
    //for LightBoxMode flag
    if(GET_OSD_LIGHTBOXMODE_STATUS()==_ON)
    {
        return _FAIL;
    }

	//for Calibration Mode flag
    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
	{
        return _FAIL;
	}

    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SAVE_USER2_DATA) == _TRUE)
    {
        DebugMessageUart("Distance user2 save...", 0);
        return _FAIL;
    }

    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_VALUE_UPDATE) == _TRUE)
    {
        DebugMessageUart("Distance Sensor update...", 0);
        return _FAIL;
    }

	if(UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE) == _ON)
    {
        DebugMessageUart("One Key Lumi Flag...", 0);
        return _FAIL;
    }

	if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
	{
        DebugMessageUart("Local Enhancement Flag...", 0);
        return _FAIL;
	}

	if(UserCommonNVRamGetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE) == _ON)
    {
        DebugMessageUart("Local Enhancement Flag...", 0);
        return _FAIL;
    }
	
    {
        DistanceSensorTime = GetHumanSensorTime();
        if((DistanceSensorTime == 0)||(PrevDistanceSensorTime != DistanceSensorTime))
        {
            PrevDistanceSensorTime = DistanceSensorTime;
            if(g_bDistanceSensorPowerStatus == _OFF)
            {
                g_bDistanceSensorPowerStatus = _ON;
				DistanceLumiChanged = 1;
            }
            TempDistanceSensorSensitivity = 10/*GET_OSD_DISTANCE_SENSOR_THRESHOLD_VALUE()*/;
            DistanceValueStable = 0;
            DistanceValueOffCount = 0;
            
            return _FAIL; //OFF
        }
        /* 
        do
        {
            CurrDistanceValue = ReadVCNLSensorValue();
            usDisMidofValue[ucDisSensorMultiple] = CurrDistanceValue;
            DebugMessageUart("Get Sensor:", CurrDistanceValue);
            ucDisSensorMultiple++;
        }while(ucDisSensorMultiple < 3);

        if(ucDisSensorMultiple >= 3)
        {
            ucDisSensorMultiple = 0;
            CurrDistanceValue = MIDOF(usDisMidofValue[0],usDisMidofValue[1],usDisMidofValue[2]);
    	    DebugMessageUart("disSensor Mid:", CurrDistanceValue);
        }*/
        CurrDistanceValue = ReadVCNLSensorValue();
        if(CurrDistanceValue == 0)          
        {
            return _FAIL;
        }

        DebugMessageUart(">>Distance Curr:", CurrDistanceValue);  
        if(ABSDWORD(CurrDistanceValue,PrevDistanceValue) >= 5)
        {
            // The jitter interval of the sensor's long-term sampling value is 3~8(More 3~6), so the threshold should be slightly larger, but not too large
        }
        DebugMessageUart(">>POWER OFF VALUE:", PowerOffValue);  
        if((CurrDistanceValue < PowerOffValue)||(PowerOffValue == 0))
        {
            PowerOffValue = CurrDistanceValue;   //update PowerOffValue
        }
        
        if(ABSDWORD(CurrDistanceValue,PrevDistanceValue) >= TempDistanceSensorSensitivity)  //value fast change
        {
            TempDistanceSensorSensitivity = 10/*GET_OSD_DISTANCE_SENSOR_THRESHOLD_VALUE()*/;
            DistanceValueStable = 0;
            DistanceValueOffCount = 0;
            
            if((g_bDistanceSensorPowerStatus == _OFF)&&(CurrDistanceValue > PrevDistanceValue))
            {            
                g_bDistanceSensorPowerStatus = _ON;
				DistanceLumiChanged = 1;
            }
            PrevDistanceValue = CurrDistanceValue;
        }  
        else //stable or change slowly
        {   
            DistanceValueStable++;
            PrevDistanceValue = (PrevDistanceValue+CurrDistanceValue)/2 ;

            if((DistanceValueStable%30 == 0)&&(TempDistanceSensorSensitivity < (10/*GET_OSD_DISTANCE_SENSOR_THRESHOLD_VALUE()*/+3)))
            {
                TempDistanceSensorSensitivity++; //every 30s make the value more and more biger
            }

            DebugMessageUart(">> Stable:", DistanceValueStable);  
            DebugMessageUart(">> OffCount:", DistanceValueOffCount); 
            DebugMessageUart(">> POWER OFF VALUE2t:", PowerOffValue); 
            DebugMessageUart(">> ABS:", ABSDWORD(CurrDistanceValue,PowerOffValue));  
            if(ABSDWORD(CurrDistanceValue,PowerOffValue)<= TempDistanceSensorSensitivity*2)  //far and stable,this state can Power off
            {
                DistanceValueOffCount++;   
            }
            else if((ABSDWORD(CurrDistanceValue,PowerOffValue)> TempDistanceSensorSensitivity*2)) //value slow change and biger
            {
                if((g_bDistanceSensorPowerStatus == _OFF)&&(CurrDistanceValue > PrevDistanceValue))
                {            
                    g_bDistanceSensorPowerStatus = _ON;                    
    				DistanceLumiChanged = 1;
                }
                TempDistanceSensorSensitivity = 10/*GET_OSD_DISTANCE_SENSOR_THRESHOLD_VALUE()*/;
                //DistanceValueStable = 0;
                DistanceValueOffCount = 0;
            }

            if((DistanceValueStable % 300 == 0)&&(DistanceValueStable > 0) )   //long time 5min repair when the round of monitor changed
            {
                PowerOffValue = CurrDistanceValue;
            }
            
            if((DistanceValueOffCount > DistanceSensorTime)&&(g_bDistanceSensorPowerStatus == _ON)\
                &&(CurrDistanceValue <= PrevDistanceValue))  //Panel off
            {
                g_bDistanceSensorPowerStatus = _OFF;
				DistanceLumiChanged = 1;
            }     
        }
    }

	return DistanceLumiChanged;
}	

//--------------------------------------------------
// Description  : Distance Sensor Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserDistanceSensorHandler(void)
{
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
		return;
	}

	ScalerTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_DISTANCESENSOR_HANDLER);	
	//DebugMessageUart("**Distance**", g_bVCNLSensorInitDeviceID);
        
    //------------------------------------
    //Read current Distance Lumi
    if(GET_OSD_DISTANCE_SENSOR_STATUS() != _OSD_DISTANCE_OFF)
    {
        if(DistanceLumi_filter())
        {
	        if((GET_PANELPOWERSTATUS() != _PANEL_BACKLIGHT_OFF)&&(g_bDistanceSensorPowerStatus == _OFF))
	        {
		        UserInterfaceKeyPadLedControl(_LED_TYPE_FLASH);
	    		UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
                
				DebugMessageUart("**Distance Panel off**", 0);
	        }
	        else if((GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)&&(g_bDistanceSensorPowerStatus == _ON))
	        {
	            UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
	    		UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                
				DebugMessageUart("**Distance Panel on**", 0);
	        }
        }

		// LED status
		if((g_bDistanceSensorPowerStatus == _OFF)&&(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY))
		{
	        UserInterfaceKeyPadLedControl(_LED_TYPE_FLASH);
		}
		else
		{
            //RTDKeyPadLedControl(_LED_POWER_ACTIVE);
		}
    }
    else
    {
        // Avoid occasional infrared light flickering after the distance sensor is turned off
		DebugMessageUart("**Distance off**", g_bVCNLSensorInitDeviceID);
    	//if(g_bVCNLSensorInitDeviceID != _DISTANCE_DEVICE_ID_NONE)
	    {
        	g_bVCNLSensorInitDeviceID = 0;
            ReadVCNLSensorValue();
        	g_bVCNLSensorInitDeviceID = 0;
	    }
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DISTANCESENSOR_HANDLER);	 
    }
}
#endif

#if(_ENABLE_GRAVITY_SENSOR == _ON)
/** Device Identification (Who am I) **/
#define      LIS2DW12_ID             0x44
#define      LIS3DH_ID               0x33

typedef struct
{
    WORD x;
    WORD y;
    WORD z;
}GRAVITYR_DATA;

typedef struct
{
	SDWORD EulerAngle_pitch; 
	SDWORD EulerAngle_roll; 
}EulerAngle;
//--------------------------------------------------
// Define Gravity Device ID 
//--------------------------------------------------
typedef enum
{
    _GRAVITY_DEVICE_ID_NONE,
    _GRAVITY_DEVICE_ID_LIS3DH,  
    _GRAVITY_DEVICE_ID_LIS2DW12,       
    _GRAVITY_DEVICE_ID_AMOUNT,
}EnumGRADeviceID;

GRAVITYR_DATA gravity_data;
static EulerAngle EulerAngle_sensorData;

BYTE g_bGravitySensorInitDeviceID  = _GRAVITY_DEVICE_ID_NONE; 

typedef enum
{
  ORIENTATION_XL=0x01,
  ORIENTATION_XH=0X02,
  ORIENTATION_YL=0X04,
  ORIENTATION_YH=0X08,
  ORIENTATION_ZL=0X10,
  ORIENTATION_ZH=0X20,    
  ORIENTATION_INVAILD=0XFF,
}eORIENTATION;
eORIENTATION g_CurOrientation=ORIENTATION_INVAILD;

BYTE lis3dh_CheckID(void)
{
	BYTE ucCmd_Buf[2];
	/*	Check device ID */
    // ID Register(0x22h)   0x34:25721 0x3D:25723
    //SubAddr & Para;
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x0F, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        DebugMessageOsd("LIS3DH IIC Fail check:", LIS3DH_IIC_ADDR);    
      return _FAIL;
    }
    DebugMessageOsd("CheckID:", ucCmd_Buf[0]);        
    
    if(ucCmd_Buf[0]== LIS3DH_ID )
    {
    DebugMessageOsd("CheckID:", LIS3DH_ID);        
	  return _SUCCESS;
	}        
}

BYTE lis2dw12_CheckID(void)
{
	BYTE ucCmd_Buf[2];
	/*	Check device ID */
    // ID Register(0x22h)   0x34:25721 0x3D:25723
    //SubAddr & Para;
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x0F, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        DebugMessageOsd("LIS3DH IIC Fail check:", LIS3DH_IIC_ADDR);    
      return _FAIL;
    }
    
    if(ucCmd_Buf[0]== LIS2DW12_ID )
    {
    //DebugMessageOsd("CheckID:", LIS2DW12_ID);        
	  return _SUCCESS;
	}        
}

//--------------------------------------------------
// Description  : Init Gravity Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit lis3dh_int(void)
{
	BYTE ucCmd_Buf[2];

	if(lis3dh_CheckID() == _SUCCESS)
    {
    //DebugMessageOsd("CheckID:", 1);
    }   

	/* Set Output Data Rate to 25 Hz */
	ucCmd_Buf[0]=0x20;
	ucCmd_Buf[1]=0x37;  
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
        DebugMessageOsd("LIS3DH IIC Fail:", LIS3DH_IIC_ADDR);
		return _FAIL;
	}

	/* Set full scale to 2 g */
	ucCmd_Buf[0]=0x23;
	ucCmd_Buf[1]=0x00;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

	// enable prox in selftimed mode ->Bit1:prox_en Enable  Bit0:selftimed_en Enable 
	ucCmd_Buf[0]=0x32;
	ucCmd_Buf[1]=0x12;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

	/* Enable AOI1 on int1 pin */
    // ID Register(0x22h)   0x34:25721 0x3D:25723
    //SubAddr & Para;
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x22, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        return _FAIL;
    }
	ucCmd_Buf[0]=0x22;
	ucCmd_Buf[1]=0x40;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}
	/* Set no time duration. */
	ucCmd_Buf[0]=0x33;
	ucCmd_Buf[1]=0x00;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

	/* Configure for movement recognition on all axis
	 *
	 * Follow a short definition of movement recognition
	 * and direction recognition supported by device:
	 *
	 * AOI-6D = 01 is movement recognition:
	 *	   An interrupt is generated when the orientation
	 *	   moves from an unknown zone to a known zone.
	 *	   The interrupt signal remains for a duration ODR.
	 *
	 * AOI-6D = 11 is direction recognition:
	 *	   An interrupt is generated when the orientation is
	 *	   inside a known zone.
	 *	   The interrupt signal remains while the orientation
	 *	   is inside the zone. */
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x30, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        return _FAIL;
    }
	ucCmd_Buf[0]=0x30;
	ucCmd_Buf[1]=0x7f;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}
	/* Set device in HR mode */
	ucCmd_Buf[0]=0x20;
	ucCmd_Buf[1]=0x07;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}
	ucCmd_Buf[0]=0x23;
	ucCmd_Buf[1]=0x08;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

	
	ScalerTimerDelayXms(10);

	return _SUCCESS;

}
//--------------------------------------------------
// Description  : Init Gravity Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit lis2dw12_int(void)
{
	BYTE ucCmd_Buf[2];

	if(lis2dw12_CheckID() == _SUCCESS)
    {
    //DebugMessageOsd("CheckID:", 1);
    }   

   /* Restore default configuration */
	ucCmd_Buf[0]=0x21;
	ucCmd_Buf[1]=0x44;  
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
        DebugMessageOsd("LIS3DH Restore Fail:", LIS3DH_IIC_ADDR);
		return _FAIL;
	}
    
    //DebugMessageOsd("INTSUCCEC:", 1);
	//ScalerTimerDelayXms(10);

	return _SUCCESS;

}

WORD lis2dw12_orientation(void)
{
	BYTE ucCmd_Buf[1];
	if(lis2dw12_int() == _SUCCESS)
    {
	g_bGravitySensorInitDeviceID = _GRAVITY_DEVICE_ID_LIS2DW12;
    DebugMessageOsd("lis2dw12 Init:", g_bGravitySensorInitDeviceID);
    }   
  /* Set full scale */
	ucCmd_Buf[0]=0x25;
	ucCmd_Buf[1]=0x04;  
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

  /* Configure power mode */
	ucCmd_Buf[0]=0x20;
	ucCmd_Buf[1]=0x60;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

  /* Set threshold to 60 degrees */
	ucCmd_Buf[0]=0x30;
	ucCmd_Buf[1]=0x40;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}

  /* LPF2 on 6D function selection. */
	ucCmd_Buf[0]=0x3F;
	ucCmd_Buf[1]=0x01;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
	}
      /* Enable interrupt generation on 6D INT1 pin. */
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x24, 1, 1, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        return _FAIL;
    }
    if(pData[0] == 0)
        {
            if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x3f, 1, 1, &pData[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                return _FAIL;
            }
        }
    if(pData[1] == 0)
        {
        	ucCmd_Buf[0]=0x23;
        	ucCmd_Buf[1]=0x80;	
        	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        	{
        		return _FAIL;
        	}
        }
	ucCmd_Buf[0]=0x3f;
	ucCmd_Buf[1]=pData[1]|0x20;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
	
		return _FAIL;
	}
    
  /* Set Output Data Rate */
	ucCmd_Buf[0]=0x22;
	ucCmd_Buf[1]=0x00;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
		return _FAIL;
        
	}

    
    /* Check 6D Orientation */
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x3A, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        return _FAIL;
        
    }
        DebugMessageOsd("orientation:", ucCmd_Buf[0] & 0x40);
        DebugMessageOsd("orientation1:", ucCmd_Buf[0] & 0x3f);
        
    /* Check 6D Orientation events */
    if (ucCmd_Buf[0] & 0x40) {
        switch (ucCmd_Buf[0] & 0x3f) {
          case ORIENTATION_XL:
    	  	if(g_CurOrientation!=ORIENTATION_XL)
    	  	{
    			g_CurOrientation=ORIENTATION_XL;
    DebugMessageOsd("g_CurOrientation 1:", g_CurOrientation);
                
    			//OrientationUpdate();
    		}
            break;

          case ORIENTATION_XH:
    	  	if(g_CurOrientation!=ORIENTATION_XH)
    	  	{
    			g_CurOrientation=ORIENTATION_XH;
    DebugMessageOsd("g_CurOrientation 2:", g_CurOrientation);
    		}
            break;

          case ORIENTATION_YL:
    	  	if(g_CurOrientation!=ORIENTATION_YL)
    	  	{
    			g_CurOrientation=ORIENTATION_YL;
    DebugMessageOsd("g_CurOrientation 3:", g_CurOrientation);
    		}
            break;

          case ORIENTATION_YH:
    	  	if(g_CurOrientation!=ORIENTATION_YH)
    	  	{
    			g_CurOrientation=ORIENTATION_YH;
    DebugMessageOsd("g_CurOrientation 4:", g_CurOrientation);
    		}
            break;

          case ORIENTATION_ZL:
    	  	if(g_CurOrientation!=ORIENTATION_ZL)
    	  	{
    			g_CurOrientation=ORIENTATION_ZL;
    DebugMessageOsd("g_CurOrientation 5:", g_CurOrientation);
    		}
            break;

          case ORIENTATION_ZH:
    	  	if(g_CurOrientation!=ORIENTATION_ZH)
    	  	{
    			g_CurOrientation=ORIENTATION_ZH;
    DebugMessageOsd("g_CurOrientation 6:", g_CurOrientation);
    		}
            break;

          default:
            break;
        }
    }
  }

void lis3dh_raw_get(EulerAngle *pEulerAngle_Data)
{
	BYTE ucCmd_Buf[1];
	GRAVITYR_DATA gravity_data;

	if(lis2dw12_CheckID() == _SUCCESS)
    {
    DebugMessageOsd("CheckID:", 1);
    }   
	/* Read output only if new value available */
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x27, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
    DebugMessageOsd("LIS3DH_STATUS_REG:", 0x27);
    
        //return _FAIL;
    }
    if (ucCmd_Buf[0] & 0x8) {
      /* Read accelerometer data */
    	    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x28, 1, 6, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }

    		gravity_data.x = pData[1]*256 + pData[0];
    		gravity_data.y = pData[3]*256 + pData[2];
    		gravity_data.z = pData[5]*256 + pData[4];

    		//gravity_data.x <<=8;
    		//gravity_data.y <<=8;
    		//gravity_data.z <<=8;

    		//gravity_data.x += pData[0];
            gravity_data.x = ( (float)gravity_data.x / 16.0f ) * 1.0f;            
    		//gravity_data.y += pData[2];
            gravity_data.y = ( (float)gravity_data.y / 16.0f ) * 1.0f;            
    		//gravity_data.z += pData[4];
            gravity_data.z = ( (float)gravity_data.z / 16.0f ) * 1.0f; 
            
            pEulerAngle_Data->EulerAngle_pitch = (atan2((float)(0-gravity_data.y),gravity_data.z) * 180 / 3.14159);
            pEulerAngle_Data->EulerAngle_roll  = (atan2((float)(  gravity_data.x),gravity_data.z) * 180 / 3.14159);
            DebugMessageOsd("gravity_data.z:", gravity_data.z);     
            DebugMessageOsd("gravity_data.x:", gravity_data.x);        
            DebugMessageOsd("gravity_data.y:", gravity_data.y);        

    }
	#if 0
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x07, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        //return _FAIL;
    }

    if (ucCmd_Buf[0] & 0x04) 
	{
      /* Read temperature data */
    	    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x0C, 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }
            temperature_degC = pData[1];
            temperature_degC <<=8;
            temperature_degC += pData[0];
            temperature_degC =( ( (float)temperature_degC / 64.0f ) / 4.0f ) + 25.0f;
     }
	#endif
 }

void lis2dw12_raw_get(EulerAngle *pEulerAngle_Data)
{
	BYTE ucCmd_Buf[1];
	GRAVITYR_DATA gravity_data;

	if(lis2dw12_int() == _SUCCESS)
    {
	g_bGravitySensorInitDeviceID = _GRAVITY_DEVICE_ID_LIS2DW12;
    DebugMessageOsd("lis2dw122 Init:", g_bGravitySensorInitDeviceID);
    }   
 /* Enable Block Data Update */
	ucCmd_Buf[0]=0x21;
	ucCmd_Buf[1]=0x4c;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
	}
  /* Set full scale */
	ucCmd_Buf[0]=0x25;
	ucCmd_Buf[1]=0x40;  
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
        DebugMessageOsd("LIS3DH IIC Fail:", LIS3DH_IIC_ADDR);
	}

  /* Configure filtering chain
   * Accelerometer - filter path / bandwidth
   */
	ucCmd_Buf[0]=0x3F;
	ucCmd_Buf[1]=0x00;  
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
        DebugMessageOsd("LIS3DH IIC Fail:", LIS3DH_IIC_ADDR);
	}
  
  /* Configure power mode */
	ucCmd_Buf[0]=0x20;
	ucCmd_Buf[1]=0x34;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
	}

 /* Set Output Data Rate */
	ucCmd_Buf[0]=0x22;
	ucCmd_Buf[1]=0x00;	
	if(UserCommonEepromIICWrite(LIS3DH_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	{
	}
    
	/* Read output only if new value available */
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x27, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
    DebugMessageOsd("LIS3DH_STATUS_REG:", 0x27);
    
        //return _FAIL;
    }
    if (ucCmd_Buf[0] & 0x1) {
      /* Read accelerometer data */
    	    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x28, 1, 6, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }

    		gravity_data.x = pData[1]*256 + pData[0];
    		gravity_data.y = pData[3]*256 + pData[2];
    		gravity_data.z = pData[5]*256 + pData[4];

    		//gravity_data.x <<=8;
    		//gravity_data.y <<=8;
    		//gravity_data.z <<=8;

    		//gravity_data.x += pData[0];
            //gravity_data.x = ( (float)gravity_data.x / 16.0f ) * 1.0f;            
    		//gravity_data.y += pData[2];
            //gravity_data.y = ( (float)gravity_data.y / 16.0f ) * 1.0f;            
    		//gravity_data.z += pData[4];
            //gravity_data.z = ( (float)gravity_data.z / 16.0f ) * 1.0f; 

            gravity_data.x = ( (float)gravity_data.x * 0.061 ) ;            
    		//gravity_data.y += pData[2];
            gravity_data.y = ( (float)gravity_data.y * 0.061 ) ;            
    		//gravity_data.z += pData[4];
            gravity_data.z = ( (float)gravity_data.z * 0.061 ) ; 

            
            pEulerAngle_Data->EulerAngle_pitch = (atan2((float)(  gravity_data.y),gravity_data.z) * 180 / 3.14159);
            pEulerAngle_Data->EulerAngle_roll  = (atan2((float)(  gravity_data.x),gravity_data.z) * 180 / 3.14159);
            DebugMessageOsd("gravity_data.z:", gravity_data.z);     
            DebugMessageOsd("gravity_data.x:", gravity_data.x);        
            DebugMessageOsd("gravity_data.y:", gravity_data.y); 

            DebugMessageOsd("EulerAngle_pitch:", pEulerAngle_Data->EulerAngle_pitch); 
            DebugMessageOsd("EulerAngle_roll:", pEulerAngle_Data->EulerAngle_roll);      

    }
	#if 0
    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x07, 1, 1, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    {
        //return _FAIL;
    }

    if (ucCmd_Buf[0] & 0x04) 
	{
      /* Read temperature data */
    	    if(UserCommonEepromIICRead(LIS3DH_IIC_ADDR, 0x0C, 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }
            temperature_degC = pData[1];
            temperature_degC <<=8;
            temperature_degC += pData[0];
            temperature_degC =( ( (float)temperature_degC / 64.0f ) / 4.0f ) + 25.0f;
     }
	#endif
 }

void UserGravitySensorHandler(void)
{
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
		return;
	}
	ScalerTimerReactiveTimerEvent(SEC(15), _USER_TIMER_EVENT_GRAVITYSENSOR_HANDLER);	
	//DebugMessageUart("**Distance**", g_bVCNLSensorInitDeviceID);
        
    //------------------------------------
    //Read current Distance Lumi
    if(GET_OSD_GRAVITY_SENSOR_STATUS() == _ON)
    {
    lis2dw12_orientation();
	lis2dw12_raw_get(&EulerAngle_sensorData);
    
    switch(g_CurOrientation){
        case ORIENTATION_YH:
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            break;
        case ORIENTATION_XL:
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_90);
            break;
        case ORIENTATION_XH:
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_270);
            break;
        case ORIENTATION_YL:
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_180);
            break;
    }
     OsdDispDisableOsd();
   
#if 0    
	lis2dw12_raw_get(&EulerAngle_sensorData);
        if((EulerAngle_sensorData.EulerAngle_pitch >=70)||(EulerAngle_sensorData.EulerAngle_pitch <=110)) 
            {
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)                        
            SET_OSD_ROTATE_STATUS(_DISP_ROTATE_90);
#endif
           // UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
            //SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }
        else if((EulerAngle_sensorData.EulerAngle_pitch >=160)||(EulerAngle_sensorData.EulerAngle_pitch <=-160))
            {
            SET_OSD_ROTATE_STATUS(_DISP_ROTATE_0);
            //UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
            //SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }
        else if((EulerAngle_sensorData.EulerAngle_pitch >=-90)||(EulerAngle_sensorData.EulerAngle_pitch <=-70))
            {
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)            
            SET_OSD_ROTATE_STATUS(_DISP_ROTATE_180);
#endif
            //UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
            //SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);             
            }
        else if((EulerAngle_sensorData.EulerAngle_pitch >=-20)||(EulerAngle_sensorData.EulerAngle_pitch <= 20))
            {
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)                        
            SET_OSD_ROTATE_STATUS(_DISP_ROTATE_270);
#endif
            //UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
            //SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);            
            }
#endif        
    }
    else
    {
        // Avoid occasional infrared light flickering after the distance sensor is turned off
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GRAVITYSENSOR_HANDLER);	 
    }
}
#endif
#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
#include <ScalerColorInterface.h>
//#define FPGA_COLOR_ADAPTIVE_IIC_ADDR	           0x54  //  7b (0101010)<<1  Color adaptive FPGA
//--------------------------------------------------
// Description  : User cmd to FPGA ColorAdaptive  
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustFPGAColorAdaptiveHandler(BYTE ucForceOn)
{
    BYTE ucCmd_Buf[25];
	

	if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
	{
		//ucForceOn = _OFF;
		//DebugMessageSystem("HLWIN off Adaptive :", ucForceOn);
	}

	// FPGA Color Adaptive Mode ON=1 OFF=0
	if(ucForceOn == _OFF)
	{
	    ucCmd_Buf[0] = 0;	
	}
	else
	{
	    ucCmd_Buf[0] = ((IsGammaOptionHybridGamma(GET_OSD_GAMMA())<<4)| IsGammaOptionHybridGamma(GET_OSD_GAMMA()));	
	}
	DebugMessageUart("0:Color Adaptive:", ucCmd_Buf[0]);

	// Display Mode 
    ucCmd_Buf[1] = SysSourceGetInputPort();	  
	//DebugMessageUart("1:DISPLAY_MODE:", ucCmd_Buf[1]);

#if 1
    // FPGA Select COLOR TEMP&GAMMA
	//DebugMessageSystem("----------FPGA CT&Gamma---------", 0);
	{
		// OSD Select Region
	    //ucCmd_Buf[2] = GET_OSD_SELECT_REGION();
		//DebugMessageUart("2:OSD SEL:", GET_OSD_SELECT_REGION());	
		//DebugMessageUart("2:COLOR SEL:", GET_OSD_FPGA_COLOR_GAMMA(GET_OSD_SELECT_REGION()));	
		//DebugMessageUart("2:GRAY SEL:", GET_OSD_FPGA_GRAY_GAMMA(GET_OSD_SELECT_REGION()));	
		
		// Color Gamma
	    if(GET_OSD_FPGA_COLOR_GAMMA() != _GAMMA_OFF)
	    {
			// Must Index from 1 Start[FPGA Index]
			if(IsGammaOptionPCCalibration(GET_OSD_FPGA_COLOR_GAMMA())) 
			{
    			// Only default curve 
			    ucCmd_Buf[3] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
			    ucCmd_Buf[4] = 1;	
			}
            else if(IsGammaOptionMCUCalibration(GET_OSD_FPGA_COLOR_GAMMA())) 
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
	        	{
				    ucCmd_Buf[3] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[4] = 2;	
                    else
    				    ucCmd_Buf[4] = 4;	
				}
	            else
	        	{
				    ucCmd_Buf[3] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[4] = 3;	
                    else
    				    ucCmd_Buf[4] = 5;	
	        	}	
			}
			else
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
	        	{
				    ucCmd_Buf[3] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
				    ucCmd_Buf[4] = GET_OSD_FPGA_COLOR_GAMMA();	
				}
	            else
	        	{
				    ucCmd_Buf[3] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
				    ucCmd_Buf[4] = GET_OSD_FPGA_COLOR_GAMMA();	
	        	}
			}
	    }

	    //DebugMessageUart("3:C-SEL:Bank = ", ucCmd_Buf[3]);
	    //DebugMessageUart("4:C-SEL:Index = ", ucCmd_Buf[4]);

	    // Gray Dicom
	    if(GET_OSD_FPGA_GRAY_GAMMA() != _GAMMA_OFF)
	    {
			// Must Index from 1 Start
			if(IsGammaOptionPCCalibration(GET_OSD_FPGA_GRAY_GAMMA())) 
			{
    			// Only default curve 
			    ucCmd_Buf[5] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
			    ucCmd_Buf[6] = 1;	
			}
			else if(IsGammaOptionMCUCalibration(GET_OSD_FPGA_GRAY_GAMMA())) 
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
	        	{
				    ucCmd_Buf[5] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[6] = 2;	
                    else
    				    ucCmd_Buf[6] = 4;	
				}
	            else
	        	{
				    ucCmd_Buf[5] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[6] = 3;	
                    else
    				    ucCmd_Buf[6] = 5;	
	        	}
			}
			else
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
	        	{
				    ucCmd_Buf[5] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
				    ucCmd_Buf[6] = GET_OSD_FPGA_GRAY_GAMMA();	
				}
	            else
	        	{
				    ucCmd_Buf[5] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
				    ucCmd_Buf[6] = GET_OSD_FPGA_GRAY_GAMMA();	
	        	}
			}
	    }
	    //DebugMessageUart("5:G-SEL:Bank = ", ucCmd_Buf[5]);
	    //DebugMessageUart("6:G-SEL:Index = ", ucCmd_Buf[6]);
	}
#endif

#if 1
	{
		// OSD Inverse Region
	   // ucCmd_Buf[7] = GET_OSD_INVERSE_REGION();
		//DebugMessageUart("7:OSD INV:", GET_OSD_INVERSE_REGION());	
		//DebugMessageUart("7:COLOR INV:", GET_OSD_FPGA_COLOR_GAMMA(GET_OSD_INVERSE_REGION()));	
		//DebugMessageUart("7:GRAY INV:", GET_OSD_FPGA_GRAY_GAMMA(GET_OSD_INVERSE_REGION()));	

	    if(GET_OSD_FPGA_COLOR_GAMMA() != _GAMMA_OFF)
		{
			// Must Index from 1 Start
			if(IsGammaOptionPCCalibration(GET_OSD_FPGA_COLOR_GAMMA())) 
			{
    			// Only default curve 
			    ucCmd_Buf[8] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
			    ucCmd_Buf[9] = 1;	
			}
			else if(IsGammaOptionMCUCalibration(GET_OSD_FPGA_COLOR_GAMMA())) 
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[8] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[9] = 2;	
                    else
    				    ucCmd_Buf[9] = 4;	
				}
	            else
            	{
				    ucCmd_Buf[8] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[9] = 3;	
                    else
    				    ucCmd_Buf[9] = 5;	
            	}
			}
			else
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[8] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
				    ucCmd_Buf[9] = GET_OSD_FPGA_COLOR_GAMMA();	
				}
	            else
            	{
				    ucCmd_Buf[8] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
				    ucCmd_Buf[9] = GET_OSD_FPGA_COLOR_GAMMA();	
            	}
			}
	    }

	    //DebugMessageUart("8:C-INV:Bank = ", ucCmd_Buf[8]);
	    //DebugMessageUart("9:C-INV:Index = ", ucCmd_Buf[9]);

	    if(GET_OSD_FPGA_GRAY_GAMMA() != _GAMMA_OFF)
		{
			// Must Index from 1 Start
			if(IsGammaOptionPCCalibration(GET_OSD_FPGA_GRAY_GAMMA())) 
			{
    			// Only default curve 
			    ucCmd_Buf[10] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
			    ucCmd_Buf[11] = 1;	
			}
			else if(IsGammaOptionMCUCalibration(GET_OSD_FPGA_GRAY_GAMMA())) 
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[10] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[11] = 2;	
                    else
    				    ucCmd_Buf[11] = 4;	
				}
	            else
            	{
				    ucCmd_Buf[10] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
                    if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
    				    ucCmd_Buf[11] = 3;	
                    else
    				    ucCmd_Buf[11] = 5;	
            	}
			}
			else
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[10] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
				    ucCmd_Buf[11] = GET_OSD_FPGA_GRAY_GAMMA();	
				}
	            else
            	{
				    ucCmd_Buf[10] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
				    ucCmd_Buf[11] = GET_OSD_FPGA_GRAY_GAMMA();	
            	}
			}
	    }	    

	    //DebugMessageUart("10:G-INV:Bank = ", ucCmd_Buf[10]);
	    //DebugMessageUart("11:G-INV:Index = ", ucCmd_Buf[11]);
	}	
#endif

#if 1
	{
	    // Scaler Select COLOR TEMP&GAMMA
		//DebugMessageSystem("----------Scaler CT&Gamma---------", 0);
		//DebugMessageUart("7:Scaler SEL:", GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));	
		//DebugMessageUart("7:Scaler INV:", GET_OSD_GAMMA(GET_OSD_INVERSE_REGION()));	
		
	    if(GET_OSD_GAMMA() != _GAMMA_OFF)
	    {
			// Must Index from 1 Start
	    	if(IsGammaOptionPCCalibration(GET_OSD_GAMMA())) 
			{
    			// Only default curve 
			    ucCmd_Buf[12] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
			    ucCmd_Buf[13] = 1;	
			}
	    	else if(IsGammaOptionMCUCalibration(GET_OSD_GAMMA())) 
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[12] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
				    ucCmd_Buf[13] = 3;	
				}
	            else
            	{
				    ucCmd_Buf[12] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
				    ucCmd_Buf[13] = 4;	
            	}
			}
			else
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[12] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
				    ucCmd_Buf[13] = GET_OSD_GAMMA();	
				}
	            else
            	{
				    ucCmd_Buf[12] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
				    ucCmd_Buf[13] = GET_OSD_GAMMA();	
            	}
			}
	    }
        else
		{
            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
        	{
			    ucCmd_Buf[12] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
			    ucCmd_Buf[13] = _GAMMA_OFF;	
			}
            else
        	{
			    ucCmd_Buf[12] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
			    ucCmd_Buf[13] = _GAMMA_OFF;	
        	}
		}
	    //DebugMessageUart("12:Sel:Bank = ", ucCmd_Buf[12]);
	    //DebugMessageUart("13:Sel:Index = ", ucCmd_Buf[13]);

        if(GET_OSD_GAMMA() != _GAMMA_OFF)
	    {
			// Must Index from 1 Start
	    	if(IsGammaOptionPCCalibration(GET_OSD_GAMMA())) 
			{
    			// Only default curve 
			    ucCmd_Buf[14] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
			    ucCmd_Buf[15] = 1;	
			}
	    	else if(IsGammaOptionMCUCalibration(GET_OSD_GAMMA())) 
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[14] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
				    ucCmd_Buf[15] = 3;	
				}
	            else
            	{
				    ucCmd_Buf[14] = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;	  
				    ucCmd_Buf[15] = 4;	
            	}
			}
			else
			{
	            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
            	{
				    ucCmd_Buf[14] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
				    ucCmd_Buf[15] = GET_OSD_GAMMA();	
				}
	            else
            	{
				    ucCmd_Buf[14] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
				    ucCmd_Buf[15] = GET_OSD_GAMMA();	
            	}
			}
	    }
        else
		{
            if(GET_COLOR_TEMP_TYPE() < _CT_6500)
        	{
			    ucCmd_Buf[14] = _BEACON_GAMMA_PARTITION0_FLASH_BANK;	  
			    ucCmd_Buf[15] = _GAMMA_OFF;	
			}
            else
        	{
			    ucCmd_Buf[14] = _BEACON_GAMMA_PARTITION1_FLASH_BANK;	  
			    ucCmd_Buf[15] = _GAMMA_OFF;	
        	}
		}
	    //DebugMessageUart("14:Inv:Bank = ", ucCmd_Buf[14]);
	    //DebugMessageUart("15:Inv:Index = ", ucCmd_Buf[15]);
	}	
#endif

#if 1
	// FPGA Data Processing Module Format Requirements:[HWidth=18&19 VHeight=22&23] 
	{
        ucCmd_Buf[16] = (BYTE)(((GET_MDOMAIN_OUTPUT_HSTART() - _PANEL_DH_START) & 0xff00)>>8);         
        ucCmd_Buf[17] = (BYTE)(((GET_MDOMAIN_OUTPUT_HSTART() - _PANEL_DH_START) & 0x00ff));
        ucCmd_Buf[18] = (BYTE)((GET_MDOMAIN_OUTPUT_HWIDTH() & 0xff00)>>8);         
        ucCmd_Buf[19] = (BYTE)((GET_MDOMAIN_OUTPUT_HWIDTH() & 0x00ff));
        ucCmd_Buf[20] = (BYTE)(((GET_MDOMAIN_OUTPUT_VSTART() - _PANEL_DV_START) & 0xff00)>>8);         
        ucCmd_Buf[21] = (BYTE)(((GET_MDOMAIN_OUTPUT_VSTART() - _PANEL_DV_START) & 0x00ff));
        ucCmd_Buf[22] = (BYTE)((GET_MDOMAIN_OUTPUT_VHEIGHT() & 0xff00)>>8);         
        ucCmd_Buf[23] = (BYTE)((GET_MDOMAIN_OUTPUT_VHEIGHT() & 0x00ff));
	}
#endif

	// Color & monochrome adaptive processing threshold[>=1]: FPGA  R - G or R - B[>0] 
	// AMD W5100 or WX5100 :[4] 
	// Nvida P2000         :[8]->RGB 8Bit Full [24]->RGB 8Bit Limit [24]->YCbCr 8Bit Limit
	// Nvida P400          :[16]->RGB 8Bit Full

    ucCmd_Buf[24] = (1 << UserCommonNVRamGetSystemData(_FPGA_COLOR_ADAPTIVE_THRESHOLD));     
    //DebugMessageUart("threshold = ", UserCommonNVRamGetSystemData(_FPGA_COLOR_ADAPTIVE_THRESHOLD));
    DebugMessageUart("24:threshold = ", ucCmd_Buf[24]);

    //DebugMessageSystem("sizeof(ucCmd_Buf) = ", sizeof(ucCmd_Buf));

    if((ucForceOn == _ON)&&(ucCmd_Buf[0]))
	{
        DebugMessageUart("I-DDither_Off = ", ucCmd_Buf[0]);
	}
	else
	{
        DebugMessageUart("I-DDither_ON = ", ucCmd_Buf[0]);
	}
		
}

#endif
#if(_ARM_MCU_CALIBRATION_SUPPORT)

//--------------------------------------------------
// Description  : User DDCCI cmd to ARM MCU  
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustDdcciSetARMMcuCommand(BYTE ucMCUCMDIdx)
{	
	SET_DDCCI_MCU_TYPE(ucMCUCMDIdx);	
#if(_ARM_MCU_CALIBRATION_SUPPORT)
	if(ucMCUCMDIdx != _CMD_NONE)
	{
		PCB_TRIGGER_MCU_CONTROL(_OFF);
		UserCommonTimerDelayXms(10);
		PCB_TRIGGER_MCU_CONTROL(_ON);
	}
#endif
}
#endif
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

#endif//#if((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD))
