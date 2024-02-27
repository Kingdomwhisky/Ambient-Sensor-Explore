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
// ID Code      : BEA2014Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSD__

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
StructOsdInfo g_stOsdInfo;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
StructTimer g_stTimer;
StructPixelOrbitingStatus g_stPixelOrbitingStatus;
#endif
#endif

WORD g_usAdjustValue;
WORD g_usBackupValue;
//WORD g_us4thItemNum;
WORD g_usItemNum;
volatile BYTE g_ucLogoTimerCounter;
//bit  b_usLightBoxLongPressFlag = _FALSE;

BYTE code tFacPassword[] = 
{
	_OK_KEY_MESSAGE,
	_OK_KEY_MESSAGE,
	_OK_KEY_MESSAGE,
};

BYTE code tServicePassword[] = 
{
	_RIGHT_KEY_MESSAGE,
	_RIGHT_KEY_MESSAGE,
	_RIGHT_KEY_MESSAGE,
};

BYTE code tLightBoxPassword[] = 
{
	_RIGHT_KEY_MESSAGE,
	_RIGHT_KEY_MESSAGE,
	_RIGHT_KEY_MESSAGE,
};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
void RTDOsdSystemFlowProc(void);
void RTDOsdEventMsgProc(void);
bit UserOperationOSDOnKeep(void);

//--------------------------------------------------
// Description  : OSD Show on Keep
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserOperationOSDOnKeep(void)
{

#if 1
	if((GET_OSD_STATE() >= _MAINMENU_START) && (GET_OSD_STATE() <= _MAINMENU_END))
	{
        return _TRUE;
	}

	if(GET_OSD_STATE() == _MENU_HOTKEY_KVM_MODE)
	{
        return _TRUE;
	}
#endif

    //  Calibration 
    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
	{
        return _TRUE;
	}

	return _FALSE;
}

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserOsdHandler(void)
{
    RTDOsdSystemFlowProc();
    RTDOsdEventMsgProc();
}

//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdSystemFlowProc(void)
{
    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            break;

        case _MODE_STATUS_INITIAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREESYNC_OD_MEASURE == _ON)
                UserAdjustFREESYNCODMeasure();

#endif
                //Init Panel Time
                if((GET_PANEL_TIME_HOUR() >= 0) && (GET_PANEL_TIME_MIN() > 0))
                {
                    SET_PANEL_TIME_HOUR(0);
                    SET_PANEL_TIME_MIN(0);
					RTDNVRamSavePanelUsedTimeData();
                }

                if(UserCommonNVRamGetSystemData(_DISPLAY_LOGO_MODE) == _ON)
                {
                    OsdDispShowLogo();
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);    
                    
                    ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
                }
                else
                {
                 #if 0//(_ENABLE_HW_WATCHDOG == _ON)
                    //Time0 for HW WatchDog 
                    ScalerTimer0SetTimerCount(500);
                 #endif 
                }
                
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
 				if(GET_OSD_FPGA_TEST_IMAGE() != _TEST_IMAGE_OFF)
        	    {
                    // Check... 
            	    // Because it takes about 2 seconds to complete the signal scanning after closing the logo
                    ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_AC_ON_TEST_IMAGE_DISPLAY);
        	    }
#endif
#if(_ENABLE_BACKLIGHT_SENSOR)
                if(GET_OSD_BACKLIGHT_SENSOR_STATUS() == _ON)
                {
                    ReadBacklightSensorValue(0);
                    ScalerTimerActiveTimerEvent(SEC(10), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
                    ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
                }
#endif

#if(_ENABLE_AMBIENTLIGHT_SENSOR)
			    //if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _ON)
		    	{
			        DebugMessageUart("AMBI Sensor enable...", 61);
					ScalerTimerActiveTimerEvent(SEC(61), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
		    	}
#endif

#if(_ENABLE_DISTANCE_SENSOR)
			    //if(GET_OSD_DISTANCE_SENSOR_STATUS() != _OSD_DISTANCE_OFF)
		    	{
			        DebugMessageUart("Distance Sensor enable...", 62);
	            	ScalerTimerActiveTimerEvent(SEC(62), _USER_TIMER_EVENT_DISTANCESENSOR_HANDLER); 
		    	}
#endif

#if(_ENABLE_GRAVITY_SENSOR)
			    //if(GET_OSD_DISTANCE_SENSOR_STATUS() != _OSD_DISTANCE_OFF)
		    	{
			        DebugMessageUart("Distance Sensor enable...", 63);
	            	//ScalerTimerActiveTimerEvent(SEC(63), _USER_TIMER_EVENT_GRAVITYSENSOR_HANDLER); 
		    	}
#endif

            }

            break;


        case _MODE_STATUS_SEARCH:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREEZE_SUPPORT == _ON)
                if(GET_OSD_FREEZE_STATUS() == _ON)
                {
                    SET_OSD_FREEZE_STATUS(_OFF);
                }
#endif
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
                }
                if(GET_OSD_LIGHTBOXMODE_STATUS() == _ON)
                {
                    DebugMessageUart("LightBox...", 0);
                    break;
                }
                
            }
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) )
            {
                OsdDisplayPixelOrbitingAction();
            }
#endif
#endif

            break;

        case _MODE_STATUS_DISPLAY_SETTING:

            break;
            
        case _MODE_STATUS_ACTIVE:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
                }
            }

            break;

        case _MODE_STATUS_NOSUPPORT:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSUPPORT_MSG);
                    UserInterfaceKeyPadLedControl(_LED_POWER_NOSUPPORT);
                }
            }

            break;

        case _MODE_STATUS_NOSIGNAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(UserOperationOSDOnKeep() == _TRUE)
                {
                    OsdFuncEnableOsd();
		            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                    ScalerTimerActiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                }
				else
				{
                    // Check NSG to PS condition in display
                    if(SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)
                    {
                        ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                    }
                    else
                    {
                        ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                    }
				}
            }

            break;

        case _MODE_STATUS_POWER_SAVING:

            if(SysSourceGetCableDetect(SysSourceGetInputPort()) == _FALSE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if(GET_OSD_POWER_SAVING_SHOW_SOURCE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_SOURCE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
                }
                else if(GET_OSD_POWER_SAVING_SHOW_LIGHTBOX_MODE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_LIGHTBOX_MODE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_LIGHTBOXMODE_MSG);
                }                
                else if(GET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU() == _TRUE)
                {
                    SET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SHOW_QUICKLINK_MENU_MSG);
#if(_ENABLE_BACKLIGHT_SENSOR)
    				// Wake Up:Update BK Sensor Value
                    ReadBacklightSensorValue(0);
#endif
                }
#if(_DP_SUPPORT == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_OPTION() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_FALSE);
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_DP_VERSIOM_MSG);
                }
#endif
#if(_DP_DEBUG_MSG == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_INFO() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_INFO(_FALSE);

                    OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                }
#endif
            }

            break;

        case _MODE_STATUS_FACTORY:

            break;

        default:

            break;
    }

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
    // Check embedded DP switch status
    UserCommonAdjustEmbeddedDpSwitch();
#endif

#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
    // Check Auto Detect HDMI DP switch status
    if(GET_FORCE_SWITCH_SOURCE_STATUS() == _FALSE)
    {
        OsdFuncAutoDetectSwitchHdmiDPPort();
    }
#endif

    if(GET_KEYMESSAGE() < _KEY_AMOUNT)
    {
        // Make sure the Buzzer beep the same time
		if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_KEY_BEEP_READY) == _TRUE)
		{
			DebugMessageUart("**BEEP break**", GET_KEYMESSAGE());
            return;
		}
                
        // hot key
        if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) ||
           (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) ||
           (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
           (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
        {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
            if((GET_OSD_STATE() != _MENU_NONE) &&
               ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) 
               )
#else
            if((GET_OSD_STATE() != _MENU_NONE) && ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)))
#endif
            {
                SET_KEYREPEATENABLE();
            }
        }

        if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
        {
            // Clear the key message for _KEY_AMOUNT>4
            if(GET_KEYMESSAGE() > _EXIT_KEY_MESSAGE)
            {
    	        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
            }
            RTDFactoryMenuOperation();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);

            if(ScalerOsdGetOsdEnable() == _TRUE)
            {       
                 	//DebugMessageRx1("_SHOW_NO_SIGNAL 2:", 6);
            
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            else if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                 	//DebugMessageRx1("_SHOW_NO_SIGNAL 2:", 7);
                //ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);                    
                //ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);                    
               // ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
               
            }
            // Clear the key message for DDCCI Key CMD:[Move from RTDKeyHandler to here:2]
	        if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
	        {
		        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
	        }
        }
        else
        {
#if(_FREEZE_SUPPORT == _ON)
#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG) == _TRUE)
            {
                return;
            }
#else
            if(GET_FREEZE_DISABLE_MSG_STATE() == _ON)
            {
                return;
            }
#endif
#endif
            // back up previous OSD State
            SET_OSD_STATE_PREVIOUS(GET_OSD_STATE());

#if(_FREEZE_SUPPORT == _ON)
            if(GET_OSD_FREEZE_STATUS() == _ON) // Confirm whether disable the freeze status
            {
                if(OsdFuncCheckFreezeDisable() == _TRUE)
                {
                    return;
                }
            }
#endif

            // Perform OSD action

            (*OperationTable[GET_OSD_STATE()])();

            if((GET_OSD_STATE() > _MENU_NONE) &&
               (GET_OSD_STATE() <= _MENU_HOTKEY_LIGHTBOX_MODE/*_MAINMENU_END*/))
            {
                OsdDispMainMenuKeyInfo(GET_KEYMESSAGE(), _OSD_HIGHLIGHT);
            }
                    
            //DebugMessageUart("Key UI...", GET_OSD_STATE());

            if(GET_OSD_LIGHTBOXMODE_STATUS() == _ON)
            {
                if(GET_OSD_STATE()==_MENU_HOTKEY_LIGHTBOX_MODE)
                {
                    if(GET_KEYMESSAGE() == _POWER_KEY_MESSAGE)
                    {
                        // MenuMenuHotkeyLightBoxAdjProc _POWER_KEY_MESSAGE Exit HotKey UI
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
                    }
                }
                DebugMessageUart("Box break...", GET_OSD_STATE());
                // Clear the key message for DDCCI Key CMD:[Move from RTDKeyHandler to here:3]
    	        if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
    	        {
    		        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
    	        }
                return;
            }
            else
            {
                // Event needs to be cancel when Exit LightBox mode
                if(ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE))
                {
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
                }
            }

            // Clear the key message for DDCCI Key CMD:[Move from RTDKeyHandler to here:3]
	        if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
	        {
		        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
	        }
                                  
            // Reactive OSD disable event in check state
            if(GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)
            {
                if(GET_OSD_TIME_OUT() < _OSD_TIMEOUT_MIN)
                {
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                }
                else
                {
#if(_ARM_MCU_CALIBRATION_SUPPORT)
                    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == _ON)
                    {
                        // SEC(*) > _USER_TIMER_EVENT_QA_EVENT Timer
                        ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                    else
#endif
                    {
                        ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                }

                // Check NSG to PS condition in display
                if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
                {
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//DebugMessageRx1("_SHOW_NO_SIGNAL state:", SysModeGetModeState());        
                    if(/*(GET_OSD_STATE_PREVIOUS() != _MENU_NONE)&&*/(GET_OSD_STATE() == _MENU_NONE)) // press exit
                    {
                        ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                 	DebugMessageUart("_SHOW_NO_SIGNAL 2:", 0);
//DebugMessageRx1("_SHOW_NO_SIGNAL 2:", 0);        
                    }
                    ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                }
            }

            // Reactive OSD disable event in power saving state
            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) && (GET_OSD_IN_FACTORY_MENU_STATUS() != _TRUE))
            {
                if((GET_OSD_STATE() > _MENU_NONE)&&(GET_OSD_STATE() < _MENU_HOTKEY_INFORMATION))
                {
                    ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
//DebugMessageRx1("_SHOW_NO_SIGNAL 2:", 4);        
                    // wake up show
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);

                    // Check NSG to PS condition in display
                    //if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
                    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
                    {
//DebugMessageRx1("GET_OSD_TIME_OUT 2:", GET_OSD_TIME_OUT());        
                       ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                    }
                }
                else
                {
//DebugMessageRx1("_SHOW_NO_SIGNAL 2:", 2);        
                            OsdFuncShowSourceMenuCheck();
                    //ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                }
            }
        }
    }
#if(_UART_SUPPORT == _ON)
	        //DebugMessageSystem("_PANEL_ON:", GET_OSD_RS232_STATUS());
#if (_PRODUCT_ID_SEL == RTD2556_CANON_1201_RL6432_156PIN_A_G101ICE_L01_LVDS_PWM)
        //ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_SCALER_MCU_CHECK);                                    
        UserMcuBootUartStart();
#endif
		//UserInterfaceUartHandler();
#endif
    
	if((SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)&&(GET_OSD_RS232_STATUS()==_ON))
	{
	}          
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdEventMsgProc(void)
{
    switch(GET_OSD_EVENT_MESSAGE())
    {
        case _OSDEVENT_SHOW_NOSIGNAL_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerActiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOCABLE_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerActiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOSUPPORT_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;



        case _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);                        
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            //OsdDispHotKeySourceMenu();
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_WAKE_UP_SHOW_QUICKLINK_MENU_MSG: // wake up show QuickLink Menu
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
         	DebugMessageUart("_WAKE_UP_QUICKLINK:", GET_OSD_DOUBLE_SIZE());

            OsdDispMainKey();
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            // Check NSG to PS condition in display
            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                       
            break;

        case _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG:
#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
#else            
         	DebugMessageUart("_SHOW_SAVING_MODE:", GET_OSD_POWER_SAVING_MODE());
         	DebugMessageSystem("_BRUNIN:", GET_OSD_FACTORY_MODE_BRUNIN());
         	DebugMessageUart("_LIGHTBOX:", GET_OSD_LIGHTBOXMODE_STATUS());

			//for Brun-in Mode flag
            if(GET_OSD_FACTORY_MODE_BRUNIN()==_ON)
			{
				ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BURN_IN);
                break;
			}
            
            //avoid exit when LightBoxMode
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_ON) 
            {
                break;
            }
			
			//for Calibration Mode flag
		    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
			{
                break;
			}

           
//#if(_ENABLE_POWER_SAVING_MODE_SUPPORT == _ON)
            if(GET_OSD_POWER_SAVING_MODE()== _OFF_POWER_SAVING)
            {
                // Check NSG to PS condition in single display
                if((GET_OSD_STATE() == _MENU_NONE)&&(ScalerOsdGetOsdEnable() == _FALSE))
                {
                 	DebugMessageUart("_SHOW_NO_SIGNAL 1:", 0);
                    ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                }
            }
            else
//#endif
            {
                OsdDispDisableOsd();
                OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            }
#endif

            break;

        case _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG:
         	DebugMessageUart("_GO_TO_SAVING_MODE:", GET_OSD_POWER_SAVING_MODE());

			//for Brun-in Mode flag
            if(GET_OSD_FACTORY_MODE_BRUNIN()==_ON)
			{
				ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BURN_IN);
                break;
			}
            
            //avoid exit when LightBoxMode
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_ON) 
            {
                break;
            }
			
			//for Calibration Mode flag
		    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
			{
                break;
			}
            
            OsdDispDisableOsd();
            SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_DO_AUTO_CONFIG_MSG:
#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif
            OsdDispAutoConfigProc();
            break;
#endif

        case _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG:
            OsdDispOsdMessage(_OSD_DISP_FAIL_SAFE_MODE_MSG);
            break;
			
        case _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG:

#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
            break;
#endif

#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(UserInterfaceGetFirstAutoConfigStatus() == _TRUE)
                {
                    OsdDispAutoConfigProc();
                }
            }
#endif
    	    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
    		{
    			// Calibration 
    		}
            else
            {
    			if(UserOperationOSDOnKeep() == _TRUE)
    			{
                    OsdFuncEnableOsd();
                    ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
    			}
    			else
    			{
                    if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
                    {
                        OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                }
        	}
            break;

        case _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG:
            UserCommonNVRamSaveSystemData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG:
            UserCommonNVRamSaveModeUserData();
            break;
#endif
        case _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG:
            RTDNVRamSaveOSDData();
            DebugMessageUart("user save...", 0);
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG:
            if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
            }
            else
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            break;
#endif
/*
        case _OSDEVENT_SAVE_NVRAM_INPUTPORT_MSG:
            RTDNVRamSaveOsdInputPortData();
            break;
            */
        case _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG:
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _OSDEVENT_SAVE_NVRAM_BRICON_MSG:
            RTDNVRamSaveBriCon(SysSourceGetSourceType());
            break;

        case _OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG:
            RTDNVRamSaveSixColorData();
            break;


#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
        case _OSDEVENT_PIXEL_ORBITING_ACTION_MSG:
            UserAdjustPixelShifting();
            SET_PIXEL_ORBITING_TIME(10);
            break;
#endif
#endif

        case _OSDEVENT_SAVE_NVRAM_OSDUSER2DATA_MSG:
            RTDNVRamSaveOsdUser2Data();
			break;

		case _OSDEVENT_SAVE_NVRAM_USER_LUTDATA_MSG:
		    RTDNVRamSaveUserLutData();
            DebugMessageUart("_Save_LUT:", 0);
		    break;

        // wake up LightBoxMode            
        case _OSDEVENT_WAKE_UP_LIGHTBOXMODE_MSG: 
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX);
            OsdDispMainMenuKeyInfo(GET_KEYMESSAGE(), _OSD_HIGHLIGHT);
            
            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
            {
				//Null
            }
            else
            {
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
            }
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
			
            // Check NSG to PS condition in display
            if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            break;


        default:
            break;
    }

    SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD GetItemValue(WORD ucState)
{
    g_usBackupValue = 0;

	switch(ucState)
	{	
        case _IMAGE_PCM:
	        g_usBackupValue = GET_OSD_PCM_STATUS();
            break;

        case _IMAGE_GAMMA:
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                g_usBackupValue = GET_OSD_PCM_INPUTGAMMA();
            else            
    			g_usBackupValue = GET_OSD_GAMMA();
            break;

        case _IMAGE_DICOMALC:
			g_usBackupValue = GET_OSD_DICOMALC();
            break;

        case _IMAGE_COLOR_TEMP:
			g_usBackupValue = GET_COLOR_TEMP_TYPE();
            break;

#if (_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        
        case _IMAGE_BACKLIGHT:
			g_usBackupValue = GET_OSD_BACKLIGHT();
            break;
#endif

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
        case _IMAGE_HYBRID_GRAY_CURVE:
			g_usBackupValue = GET_OSD_FPGA_GRAY_GAMMA();
            break;
#endif

#if (_HDR10_SUPPORT == _ON)
        case _IMAGE_HDR_MODE:
            g_usBackupValue = GET_OSD_HDR_MODE();
            break;

        case _IMAGE_HDR_DARK_ENHANCE:
            g_usBackupValue = GET_OSD_DARK_ENHANCE_STATUS();
            break;
            
        case _IMAGE_HDR_SHARP_ENHANCE:
            g_usBackupValue = GET_OSD_HDR_SHARPNESS();
            break;

        case _IMAGE_HDR_CONTRAST:
            g_usBackupValue = GET_OSD_HDR_CONTRAST();
            break;
#endif            

        case _QA_TEST_IMAGE:
			g_usBackupValue = GET_OSD_FPGA_TEST_IMAGE();
            break;

        case _FUNCTION_LANGUAGE :
	        g_usBackupValue = GET_OSD_LANGUAGE();
            break;

        case _FUNCTION_INPUT :
	        g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
            break;
            
        case _FUNCTION_AMB_LIGHT:
	        g_usBackupValue = GET_OSD_BACKGROUND_LIGHT_MODE();
            break;

        case _FUNCTION_REPORT_MODE:
	        g_usBackupValue = GET_OSD_READING_REPORT_MODE();
            break;

        case _FUNCTION_2HOURS_REMINDER:
	        g_usBackupValue = GET_OSD_2HOURS_TIPS();
            break;
            
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)   
        case _GAMMA_USER_TYPE:
	        g_usBackupValue = GET_OSD_LUT_USER_TYPE();
            break;
            
        case _GAMMA_USER_L_MAX:
	        g_usBackupValue = GET_OSD_LUT_USER_L_MAX();
            break;
            
        case _GAMMA_USER_L_MIN:
	        g_usBackupValue = GET_OSD_LUT_USER_L_MIN();
            break;
            
        case _GAMMA_USER_LAMB:
	        g_usBackupValue = GET_OSD_LUT_USER_LAMB();
            break;
            
        case _GAMMA_USER_VALUE:
	        g_usBackupValue = GET_OSD_LUT_USER_VALUE();
            break;
#endif

        case _COLOR_TEMP_USER_R:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_R();
            break;
			
        case _COLOR_TEMP_USER_G:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_G();
            break;

        case _COLOR_TEMP_USER_B:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_B();
            break;

        case _DISPLAY_ROTATE:
            g_usBackupValue = GET_OSD_DISP_ROTATE();
            break;
			            
        case _ASPECT_RATIO:
            g_usBackupValue = GET_OSD_ASPECT_RATIO_TYPE();
            break;
            
        /*case _OVERSCAN :
              g_usBackupValue = GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort());
            break;
			

            
        case _DP_HDMI_DSC:
          
                g_usBackupValue = GET_OSD_1P_DSC_PORT();
            break;*/
            
        case _UNIFORMITY:
	        g_usBackupValue =GET_OSD_PANEL_UNIFORMITY();
            break;
           
#if (_SDR_TO_HDR_SUPPORT == _ON)
        case _SDR:
	        g_usBackupValue = GET_OSD_SDR_TO_HDR();
            break;
#endif            
        case _AMBIENT_SENSOR:
	        g_usBackupValue = GET_OSD_AMBIENTLIGHT_SENSOR_STATUS();
            break;
            
        case _BODY_SENSOR:
	        g_usBackupValue = GET_OSD_DISTANCE_SENSOR_STATUS();
            break;

        case _GRAVITY_SENSOR:
	        g_usBackupValue = GET_OSD_GRAVITY_SENSOR_STATUS();
            break;
            
        case _BACKLIGHT_SENSOR:
	        g_usBackupValue = GET_OSD_BACKLIGHT_SENSOR_STATUS();
            break;
       
        case _ENERGY_SAVING:
	        g_usBackupValue = GET_OSD_POWER_SAVING_MODE();
            break;

        case _DP_VERSION:
            g_usBackupValue = GET_OSD_DP_D0_VERSION();
            break;
            
        case _DP_MST:
            g_usBackupValue = GET_OSD_DP_MST();
            break;
            
        case _DP_CLONE:
        
            g_usBackupValue = GET_OSD_CLONE_MODE();
            break;
        case _DP_RESOLUTION:
            g_usBackupValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
            break;
            
/*
        case _HDMI_VERSION_D3:
            g_usBackupValue = GET_OSD_D3_HDMI_VER();
            break;

        case _RESOLUTION_D0:
            g_usBackupValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
            break;*/

        case _OSD_TIME:
	        g_usBackupValue = GET_OSD_TIME_OUT();
            break;

        case _OSD_ROTATE:
            g_usBackupValue = GET_OSD_ROTATE_STATUS();
            break;

        case _OSD_POSITION:
	        g_usBackupValue = GET_OSD_POSTION();
            break;
            
        case _USE_LIFE_REMINDER:
	        g_usBackupValue = GET_OSD_PANEL_USELIFE_TIPS();
            break;

#if(_VGA_PORT_EXIST == _ON)
        //**********************************************************************
        //Analog Page
        //**********************************************************************
        case _ANALOG_PAGE_AUTO_COLOR_ITEM:
            g_usBackupValue = GET_OSD_FACTORY_AUTO_COLOR_TYPE();
            break;
                
        case _ANALOG_PAGE_H_POSTION_ITEM:
            g_usBackupValue = GET_VGA_MODE_ADJUST_H_POSITION();
            break;

        case _ANALOG_PAGE_V_POSTION_ITEM:
            g_usBackupValue = GET_VGA_MODE_ADJUST_V_POSITION();
            break;

        case _ANALOG_PAGE_CLOCK_ITEM:
            g_usBackupValue = GET_VGA_MODE_ADJUST_CLOCK();
            break;
            
        case _ANALOG_PAGE_PHASE_ITEM:
            g_usBackupValue = GET_VGA_MODE_ADJUST_PHASE();
            break;
#endif
            
            
         default:
            break;
	}

 	DebugMessageUart("Get Backup:", g_usBackupValue);
    // [ !!!Must add]init Value when Adj _LEFT_KEY_MESSAGE and _RIGHT_KEY_MESSAGE  for _OK_KEY_MESSAGE: or _EXIT_KEY_MESSAGE: if(g_usBackupValue != g_usAdjustValue)
    g_usAdjustValue = g_usBackupValue;
    
	return g_usBackupValue;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
        case _OK_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:             
        case _LEFT_KEY_MESSAGE:
        case _EXIT_KEY_MESSAGE:
        case _POWER_KEY_MESSAGE:
        //case _SOURCE_KEY_MESSAGE:
         	DebugMessageUart("MenuNone:", SysModeGetModeState());
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else if((SysModeGetModeState() == _MODE_STATUS_ACTIVE)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
            if(!((GET_KEYMESSAGE()!=_EXIT_KEY_MESSAGE)&&(GET_OSD_LIGHTBOXMODE_STATUS() == _ON)))
                {
                OsdDispMainKey();
                }
            }
            break;

        default:
        break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuKey(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
            {            
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {                
                    OsdDispDisableOsd();
                    SET_OSD_STATE(_MAINMENU_START);
                    OsdDispMainMenu();
                    UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
                }
            }			
            else if((SysModeGetModeState() == _MODE_STATUS_ACTIVE)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                OsdDispDisableOsd();
                SET_OSD_STATE(_MAINMENU_START);
                OsdDispMainMenu();
                UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            }
            }
            break;

        case _OK_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
            {
	        OsdDispHotKeyOptionMenu(_HOTKEY_GAMMA);
                }
    		break;
		
        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
            {
            OsdDispHotKeyOptionMenu(_HOTKEY_KVM);
                }
            break;

        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)            
            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
            {            
            OsdDispHotKeyOptionMenu(_HOTKEY_AMB);
                }
#endif            
            break;

        case _POWER_KEY_MESSAGE:
            OsdDispDisableOsd();
    		break;
			
        case _SOURCE_KEY_MESSAGE:

    		break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
	        {
	            SET_OSD_POWER_SAVING_SHOW_LIGHTBOX_MODE(_TRUE);
	        
	            if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
	            {
	                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
	            }
	        }   	        
            else if((SysModeGetModeState() == _MODE_STATUS_ACTIVE)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

                OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX); 
                if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
                {
    	         	//Null
                }
                else
                {	
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                    ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
                    
                }
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            }
             
			break;

        default:
            break;
    }
}

//==============================================================================
//   Level 1
//==============================================================================

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImagePage(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_MAIN_PAGE_START, _MAIN_PAGE_END, _ON));
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:    	
            break;
            
        case _OK_KEY_MESSAGE:
            SET_OSD_STATE(MGetFirstOsdState(_IMAGE_PAGE_START,_IMAGE_PAGE_END));
            //GetItemValue(GET_OSD_STATE());
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuQAPage(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_MAIN_PAGE_START, _MAIN_PAGE_END, _ON));
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
	        SET_OSD_STATE(MGetFirstOsdState(_QA_PAGE_START,_QA_PAGE_END));
           // GetItemValue(GET_OSD_STATE());
            OsdSelectedUpdate(_STATE_SELECT,_QA_PAGE_START, _QA_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionSettingPage(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_MAIN_PAGE_START, _MAIN_PAGE_END, _ON));
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
	        SET_OSD_STATE(MGetFirstOsdState(_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END));
            //GetItemValue(GET_OSD_STATE());
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuInfoPage(void)
{
    static BYTE ucPswCount = 0;

	if(GET_KEYMESSAGE() == tFacPassword[ucPswCount])
	{
		ucPswCount ++;
		if(ucPswCount >= sizeof(tFacPassword))
		{
            ucPswCount = 0;
            
            OsdDispDisableOsd();
            RTDFactoryMainMenu();

#if(_ARM_MCU_CALIBRATION_SUPPORT)
            // !!! Check   
        	UserAdjustDdcciSetARMMcuCommand(_CMD_DDC_MCU_VERSION);
#endif
            
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		ucPswCount = 0;
	}

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_MAIN_PAGE_START, _MAIN_PAGE_END, _ON));
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        //case _MENU_KEY_MESSAGE:
        //    break;
            
        //case _OK_KEY_MESSAGE:
        //    break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAdvancePage(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_MAIN_PAGE_START, _MAIN_PAGE_END, _ON));
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
	        SET_OSD_STATE(MGetFirstOsdState(_ADVANCED_PAGE_START,_ADVANCED_PAGE_END));
            //GetItemValue(GET_OSD_STATE());
            OsdSelectedUpdate(_STATE_SELECT,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

//==============================================================================
//   Level 2
//==============================================================================

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImagePCMProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_START,_IMAGE_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_PCM_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            SET_OSD_STATE(_MENU_IMAGE);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageGammaProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_START, _IMAGE_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_GAMMA_ADJ);
            break;
            
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            SET_OSD_STATE(_MENU_IMAGE);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageDicomALCProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_START, _IMAGE_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_DICOMALC_ADJ);
            break;
            
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            SET_OSD_STATE(_MENU_IMAGE);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageColorTempProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_START, _IMAGE_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_COLOR_TEMP_ADJ);
            break;
            
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            SET_OSD_STATE(_MENU_IMAGE);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageBacklightProc(void)
{
#if(_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_START, _IMAGE_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_BACKLIGHT_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            SET_OSD_STATE(_MENU_IMAGE);
            break;

            default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHDRProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_START, _IMAGE_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);	
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START, _IMAGE_PAGE_END);
            SET_OSD_STATE(_IMAGE_HDR_MODE);
            GetItemValue(_IMAGE_HDR_MODE);
            DrawSubMenu(_IMAGE_HDR_START);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            SET_OSD_STATE(_MENU_IMAGE);
            break;

        default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuQATestProc(void) 
{
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_QA_PAGE_START, _QA_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_QA_PAGE_START, _QA_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_QA_PAGE_START,_QA_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_QA_TEST_IMAGE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_QA_PAGE_START,_QA_PAGE_END);
            SET_OSD_STATE(_MENU_QA);
            break;

            default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuQADeviationProc(void) 
{
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_QA_PAGE_START, _QA_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_QA_PAGE_START, _QA_PAGE_END);
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_DEVIATION);
            SET_OSD_STATE(_MENU_HOTKEY_DEVIATION_ADJ);
            break;
            
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_QA_PAGE_START,_QA_PAGE_END);
            SET_OSD_STATE(_MENU_QA);
            break;

        default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionLanguageProc(void)  
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_FUNCTION_LANGUAGE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            SET_OSD_STATE(_MENU_FUNCTION_SETTING);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionInputProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_FUNCTION_INPUT_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            SET_OSD_STATE(_MENU_FUNCTION_SETTING);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionAmbLightProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:      
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_FUNCTION_AMB_LIGHT_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            SET_OSD_STATE(_MENU_FUNCTION_SETTING);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionReportModeProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_FUNCTION_REPORT_MODE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            SET_OSD_STATE(_MENU_FUNCTION_SETTING);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunction2hoursReminderProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_FUNCTION_2HOURS_REMINDER_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            SET_OSD_STATE(_MENU_FUNCTION_SETTING);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionFactoryResetProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START, _FUNCTION_SETTING_PAGE_END);
            break;
            
        case _OK_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_RESET);
            SET_OSD_STATE(_MENU_HOTKEY_FACTORY_RESET_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            SET_OSD_STATE(_MENU_FUNCTION_SETTING);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAdvancedPassWord(void)
{
    static BYTE ucServicePswCount = 0;
    if(GET_KEYMESSAGE() == tServicePassword[ucServicePswCount])
	{
		ucServicePswCount ++;
		if(ucServicePswCount >= sizeof(tServicePassword))
		{
            ucServicePswCount = 0;
            
            OsdDispServiceLevelMenu();
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		ucServicePswCount = 0;
	}

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:            
        case _MENU_KEY_MESSAGE:
        case _OK_KEY_MESSAGE:
            break;
            
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            SET_OSD_STATE(_MENU_ADVANCE);
            break;

        default:
            break;
    }
}

//==============================================================================
//  Level 3
//==============================================================================

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImagePCMAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_PCM_STATUS();
            PCMAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                //SET_OSD_PCM_STATUS( g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                DrawImagePage();    
            }
            SET_OSD_STATE(_IMAGE_PCM);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                PCMAdjust();      
            }			
            SET_OSD_STATE(_IMAGE_PCM);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;              

        default:
            break;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageGammaAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_GAMMA();	
            GammaAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
#if(_ARM_MCU_CALIBRATION_SUPPORT)
            if(IsGammaOptionMCUCalibration(GET_OSD_GAMMA()))
            {
    			// Reload: after adjusting parameters, calibration not performed or OSD auto exit 
                RTDNVRamLoadUserLutData();

                // Must here load or MenuGammaUserSetProc
                RTDNVRamCheckPanelLuxUserLutData();
                OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END-1);                                
                ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
                SET_OSD_STATE(_GAMMA_USER_TYPE);
                GetItemValue(_GAMMA_USER_TYPE);
                DrawSubMenu(_IMAGE_PAGE_GAMMA_USER_START);
                OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            } 
#endif      

#if(_FPGA_COLOR_ADAPTIVE_SUPPORT)            
            if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()))
            {
                OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END-1);                
                ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
                SET_OSD_STATE(_IMAGE_HYBRID_GRAY_CURVE);
                GetItemValue(_IMAGE_HYBRID_GRAY_CURVE);
                DrawSubMenu(_IMAGE_HYBRID_START);
                OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HYBRID_START,_IMAGE_HYBRID_END);                  
            }
#endif
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                //SET_OSD_GAMMA(g_usAdjustValue);	
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                DrawImagePage();    
            }

            SET_OSD_STATE(_IMAGE_GAMMA);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GammaAdjust();
            }			
            SET_OSD_STATE(_IMAGE_GAMMA);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageDicomALCAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_DICOMALC();	
            DicomALCAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DICOMALC( g_usAdjustValue);	
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                {
                    //OsdFuncColorPcmAdjust();
                }
                else
                {
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
            }
            SET_OSD_STATE(_IMAGE_DICOMALC);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                DicomALCAdjust();
            }			
            SET_OSD_STATE(_IMAGE_DICOMALC);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageColorTempAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_COLOR_TEMP_TYPE();
            ColorTempAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            if(GET_COLOR_TEMP_TYPE() != _CT_SRGB)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
                SET_OSD_STATE(_IMAGE_PAGE_COLORTEMP_USER_START);
                GetItemValue(_IMAGE_PAGE_COLORTEMP_USER_START);
                DrawSubMenu(_IMAGE_PAGE_COLORTEMP_USER_START);
                OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            }            
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                //SET_COLOR_TEMP_TYPE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                DrawImagePage();    
            }
                
            SET_OSD_STATE(_IMAGE_COLOR_TEMP);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                ColorTempAdjust();
            }	
            SET_OSD_STATE(_IMAGE_COLOR_TEMP);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageBacklightAdjProc(void)
{
#if(_ARM_MCU_CALIBRATION_SUPPORT == _OFF)        
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_BACKLIGHT();
            BackLightAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                //SET_OSD_BACKLIGHT(g_usAdjustValue);
            }
            SET_OSD_STATE(_IMAGE_BACKLIGHT);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                //SET_OSD_BACKLIGHT(g_usBackupValue);
            }			
            SET_OSD_STATE(_IMAGE_BACKLIGHT);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;
            
        default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuQATestImageAdjProc(void) 
{
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
    		//g_usAdjustValue = GET_OSD_FPGA_TEST_IMAGE();
            TestImageAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
        	if((g_usBackupValue != g_usAdjustValue) || (GET_OSD_FPGA_TEST_IMAGE() != _TEST_IMAGE_OFF))
        	{
//#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
                
				SET_OSD_FPGA_TEST_IMAGE(g_usAdjustValue);
                
				if(GET_OSD_FPGA_TEST_IMAGE() != _TEST_IMAGE_OFF)
			 	{
                    // Switch to FPGA Test Image On
                    //SysSourceInitialTestImageStart();
                    //UserAdjustFPGATestImageHandler();

#if(_DP_MST_SUPPORT == _ON)
                    //UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif
			 	}
				else
				{
					// Switch to FPGA Test Image Off
					//SysSourceInitialTestImageEnd();
#if(_DP_MST_SUPPORT == _ON)
                    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif
				}
	            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//#endif
        	}
            SET_OSD_STATE(_QA_TEST_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_QA_PAGE_START,_QA_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                TestImageAdjust();
            }			
            SET_OSD_STATE(_QA_TEST_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_QA_PAGE_START,_QA_PAGE_END);
            break;
            
        default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyDeviationAdjProc(void)
{
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:

#if 0//(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
        	if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()) == _ON)
        	{
                SET_OSD_GAMMA( _GAMMA_20);
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
#endif

#if(_ARM_MCU_CALIBRATION_SUPPORT)
            if(abs(ReadBacklightSensorValue(0) - UserGetBacklightSensorTargetValue()) >= _BACKLIGHT_SENSOR_PRECISION*2)
            {
                // Show Info
                OsdDispHotKeyOptionMenu(_HOTKEY_USER_CALIBRATION_GAMMA);
                UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _ON);

                // Start Show 1%
                if(GET_OSD_STATE() == _MENU_MESSAGE_DISPLAY)
                {
                    OsdPropShowNumberPercentage(ROW(_WIN_HOTKEY_ITEM_ROW + 3), COL(_WIN_HOTKEY_INFO_WIDTH - 2), 1, _FALSE, _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG));
                }                
                
            	ScalerTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
	            ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
    	        ScalerTimerReactiveTimerEvent(SEC(61), _USER_TIMER_EVENT_QA_EVENT);

                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
        	   // DebugMessageUart("Set_QA Time:", UserCommonTimerGetEventRemainTime(_USER_TIMER_EVENT_QA_EVENT));
            }
            else
            {
    	        ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_QA_EVENT);
            }
#endif
            break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();	
            SET_OSD_STATE(_QA_DEVIATION);
            OsdDispMainMenu();
            UpdateMainMenuCursor(_MENU_QA,_STATE_SELECT);
            DrawSubMenu(_MENU_QA);
            OsdSelectedUpdate(_STATE_SELECT,_QA_PAGE_START,_QA_PAGE_END);
            break;

        default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionLanguageAdjProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_LANGUAGE();
            LanguageAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LANGUAGE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
                OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));

                DrawMainPage();
                UpdateMainMenuCursor(_MENU_FUNCTION_SETTING,_STATE_SELECT);
                DrawSubMenu(_MENU_FUNCTION_SETTING); 
            }
            SET_OSD_STATE(_FUNCTION_LANGUAGE);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                LanguageAdjust();
            }			
            SET_OSD_STATE(_FUNCTION_LANGUAGE);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionInputAdjProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_INPUT_PORT_OSD_ITEM();
            FunctionInputAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
                //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
                {
                    switch(GET_OSD_INPUT_PORT_OSD_ITEM())
                    {
                        case _OSD_INPUT_AUTO: // auto
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
                            if(GET_OSD_DP_MST() != _MST_OFF)
                            {
                                SET_OSD_DP_MST(_MST_OFF);
                            }
#endif
                            SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
                            {
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;

                        case _OSD_INPUT_A0: // A0
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_A0_INPUT_PORT);
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


                        case _OSD_INPUT_D0: // D0
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D0_INPUT_PORT);
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

                        case _OSD_INPUT_D2:    // D2
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D2_INPUT_PORT);
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

                        case _OSD_INPUT_D4:    // D4
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D4_INPUT_PORT);
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

                        case _OSD_INPUT_D5:    // D5
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D5_INPUT_PORT);
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

                        case _OSD_INPUT_D6:    // D6
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D6_INPUT_PORT);
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

                        default:
                            break;
                    }

#if(_DP_MST_SUPPORT == _ON)
                    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                    RTDNVRamSaveOSDData();
#endif
                    //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORT_MSG);
                }
            }
            SET_OSD_STATE(_FUNCTION_INPUT);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                FunctionInputAdjust();
            }			
            SET_OSD_STATE(_FUNCTION_INPUT);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionAmbLightAdjProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_BACKGROUND_LIGHT_MODE();
            AmbLightAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_BACKGROUND_LIGHT_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_FUNCTION_AMB_LIGHT);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                AmbLightAdjust();
            }			
            SET_OSD_STATE(_FUNCTION_AMB_LIGHT);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunctionReportModeAdjProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_READING_REPORT_MODE();	
            ReportModeAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_READING_REPORT_MODE(g_usAdjustValue);	
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if 1
            	if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
                {	                		
                    if(GET_OSD_READING_REPORT_MODE() == _READING_REPORT_ON)
                    {
                        SET_OSD_HLWIN_TYPE(_HL_WIN_1);
                    }
                    else if(GET_OSD_READING_REPORT_MODE() == _READING_REPORT_OFF)
                    {
                        SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
                    }
            		UserAdjustHighLightWindowUserHander();
                }
#endif
            }
            SET_OSD_STATE(_FUNCTION_REPORT_MODE);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                ReportModeAdjust();
            }			
            SET_OSD_STATE(_FUNCTION_REPORT_MODE);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break; 
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuFunction2hoursReminderAdjProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_2HOURS_TIPS();	
            TwohoursReminderAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_2HOURS_TIPS(g_usAdjustValue);	
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_FUNCTION_2HOURS_REMINDER);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                TwohoursReminderAdjust();
            }			
            SET_OSD_STATE(_FUNCTION_2HOURS_REMINDER);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuHotkeyFactoryResetAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdDispOsdReset();
            break;
            
        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();	
            SET_OSD_STATE(_FUNCTION_FACTORY_RESET);
            OsdDispMainMenu();
            UpdateMainMenuCursor(_MENU_FUNCTION_SETTING,_STATE_SELECT);
            DrawSubMenu(_MENU_FUNCTION_SETTING);
            OsdSelectedUpdate(_STATE_SELECT,_FUNCTION_SETTING_PAGE_START,_FUNCTION_SETTING_PAGE_END);
            break;
            break;
        default:
            break;
    }
}


//==============================================================================
//  Level 4
//==============================================================================
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserTypeProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_GAMMA_USER_TYPE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserLMaxProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_GAMMA_USER_L_MAX_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserLMinProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_GAMMA_USER_L_MIN_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserLambProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_GAMMA_USER_LAMB_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserValueProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_GAMMA_USER_VALUE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserSetProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            {
    			// Show Info calibration
                OsdDispHotKeyOptionMenu(_HOTKEY_USER_CALIBRATION_GAMMA);

#if 0//(_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
            	if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()) == _ON)
            	{
                    SET_OSD_GAMMA( _DEFAULT_GAMMA);
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
#endif
                
    			// Save: When performing calibration
                RTDNVRamSaveUserLutData();

                UserAdjustQAUpdateTargetSensor(GET_OSD_LUT_USER_L_MAX());

                UserAdjustDdcciSetARMMcuCommand(_CMD_LUM_DIFF);

                // Must Waiting for Embedded MCU calculation to complete(<2s) 
                // _DDCCI_ARM_MCU_GET_LUM_DIFF Reactive
                UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _ON);
                ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_SET_LUT_DATA);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_GAMMA_USER_START, _IMAGE_PAGE_GAMMA_USER_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuColorTempUserRProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_COLORTEMP_USER_START, _IMAGE_PAGE_COLORTEMP_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START, _IMAGE_PAGE_COLORTEMP_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_COLOR_TEMP_USER_R_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            SET_OSD_STATE(_IMAGE_COLOR_TEMP);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuColorTempUserGProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_COLORTEMP_USER_START, _IMAGE_PAGE_COLORTEMP_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START, _IMAGE_PAGE_COLORTEMP_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_COLOR_TEMP_USER_G_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            SET_OSD_STATE(_IMAGE_COLOR_TEMP);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuColorTempUserBProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_PAGE_COLORTEMP_USER_START, _IMAGE_PAGE_COLORTEMP_USER_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START, _IMAGE_PAGE_COLORTEMP_USER_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_COLOR_TEMP_USER_B_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            SET_OSD_STATE(_IMAGE_COLOR_TEMP);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuHybridGrayCurveProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_HYBRID_START, _IMAGE_HYBRID_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HYBRID_START, _IMAGE_HYBRID_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_HYBRID_START, _IMAGE_HYBRID_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_HYBRID_GRAY_CURVE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_HYBRID_START, _IMAGE_HYBRID_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuHybridColorCurveProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:

            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_HYBRID_START, _IMAGE_HYBRID_END);
            SET_OSD_STATE(_IMAGE_GAMMA);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHdrModeProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_HDR_START, _IMAGE_HDR_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START, _IMAGE_HDR_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_HDR_START, _IMAGE_HDR_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_HDR_MODE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_HDR_START, _IMAGE_HDR_END);
            SET_OSD_STATE(_IMAGE_HDR);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
#endif    
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHdrDarkEnhanceProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_HDR_START, _IMAGE_HDR_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START, _IMAGE_HDR_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_HDR_START, _IMAGE_HDR_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_HDR_DARK_ENHANCE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_HDR_START, _IMAGE_HDR_END);
            SET_OSD_STATE(_IMAGE_HDR);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
#endif    
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHdrSharpEnhanceProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_HDR_START, _IMAGE_HDR_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START, _IMAGE_HDR_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_HDR_START, _IMAGE_HDR_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_HDR_SHARP_ENHANCE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_HDR_START, _IMAGE_HDR_END);
            SET_OSD_STATE(_IMAGE_HDR);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
#endif    
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHdrContrastProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_IMAGE_HDR_START, _IMAGE_HDR_END, _ON));

            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START, _IMAGE_HDR_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_IMAGE_HDR_START, _IMAGE_HDR_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_IMAGE_HDR_CONTRAST_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_IMAGE_HDR_START, _IMAGE_HDR_END);
            SET_OSD_STATE(_IMAGE_HDR);
            DrawSubMenu(_MENU_IMAGE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_START,_IMAGE_PAGE_END);
            break;

            default:
            break;
    }
#endif    
}
//==============================================================================
// Level 5
//==============================================================================
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserTypeAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_LUT_USER_TYPE();
            GammaUserTypeAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LUT_USER_TYPE(g_usAdjustValue);
                // Support Switch Dicom/Gamma: Save User Lut Type
    		    RTDNVRamSaveUserLutData();

                if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
                {
                    OsdFuncClearOsd(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), WIDTH(_OSD_MAIN_MENU_WIDTH -_WIN_MAIN_WIDTH), HEIGHT(2));
                    OsdPropPutString(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_LAMB, _ITEM_NORMAL_COLOR,  GET_OSD_LANGUAGE());
                    OsdDispSliderAndNumber(_GAMMA_USER_LAMB, GET_OSD_LUT_USER_LAMB(),3,_ITEM_NORMAL_COLOR);
                }
                else
                {
                    OsdFuncClearOsd(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), WIDTH(_OSD_MAIN_MENU_WIDTH -_WIN_MAIN_WIDTH), HEIGHT(2));
                    OsdPropPutString(ROW(3*_OSD_ROW_STEP+_OSD_ITEM_1_ROW_START), COL(_SUBITEM_COL_START), _PFONT_PAGE_1,_STRING_USER_VALUE, _ITEM_NORMAL_COLOR,  GET_OSD_LANGUAGE());
                    OsdDispSliderAndNumber(_GAMMA_USER_VALUE, GET_OSD_LUT_USER_VALUE(),3,_ITEM_NORMAL_COLOR);
                }
            }
            SET_OSD_STATE(_GAMMA_USER_TYPE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GammaUserTypeAdjust();
            }			
            SET_OSD_STATE(_GAMMA_USER_TYPE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break; 
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserLMaxAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            g_usAdjustValue = GET_OSD_LUT_USER_L_MAX();
         	//DebugMessageUart("GET_L_MAX:", g_usAdjustValue);
            GammaUserLMaxAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LUT_USER_L_MAX(g_usAdjustValue);
            }
            SET_OSD_STATE(_GAMMA_USER_L_MAX);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GammaUserLMaxAdjust();
            }			
            SET_OSD_STATE(_GAMMA_USER_L_MAX);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break; 
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserLMinAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            g_usAdjustValue = GET_OSD_LUT_USER_L_MIN();
         	//DebugMessageUart("GET_L_LMin:", g_usAdjustValue);
            GammaUserLMinAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
        	if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LUT_USER_L_MIN(g_usAdjustValue);
            }
            SET_OSD_STATE(_GAMMA_USER_L_MIN);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GammaUserLMinAdjust();
            }			
            SET_OSD_STATE(_GAMMA_USER_L_MIN);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break; 
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserLambAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            g_usAdjustValue = GET_OSD_LUT_USER_LAMB();
            GammaUserLambAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LUT_USER_LAMB(g_usAdjustValue);
            }
            SET_OSD_STATE(_GAMMA_USER_LAMB);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GammaUserLambAdjust();
            }			
            SET_OSD_STATE(_GAMMA_USER_LAMB);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break;  
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuGammaUserValueAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            g_usAdjustValue = GET_OSD_LUT_USER_VALUE();
            GammaUserValueAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LUT_USER_VALUE(g_usAdjustValue);
            }
            SET_OSD_STATE(_GAMMA_USER_VALUE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GammaUserValueAdjust();
            }			
            SET_OSD_STATE(_GAMMA_USER_VALUE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_GAMMA_USER_START,_IMAGE_PAGE_GAMMA_USER_END);
            break; 
            
            default:
            break;
    }
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuColorTempUserRAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_COLOR_TEMP_TYPE_USER_R();
            ColorTempUserRAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                if((GET_COLOR_TEMP_TYPE() == _CT_9300)||(GET_COLOR_TEMP_TYPE() == _CT_6500))
                {
                    SET_USER_BASE_COLOR_TEMP_TYPE(GET_COLOR_TEMP_TYPE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }
                
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    SET_COLOR_TEMP_TYPE( _CT_USER);
                }
                SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
                RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
            }
            SET_OSD_STATE(_COLOR_TEMP_USER_R);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                ColorTempUserRAdjust();
            }			
            SET_OSD_STATE(_COLOR_TEMP_USER_R);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            break; 
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuColorTempUserGAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_COLOR_TEMP_TYPE_USER_G();
            ColorTempUserGAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                if((GET_COLOR_TEMP_TYPE() == _CT_9300)||(GET_COLOR_TEMP_TYPE() == _CT_6500))
                {
                    SET_USER_BASE_COLOR_TEMP_TYPE(GET_COLOR_TEMP_TYPE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }

                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    SET_COLOR_TEMP_TYPE( _CT_USER);
                }
                SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
                RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
            }
            SET_OSD_STATE(_COLOR_TEMP_USER_G);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                ColorTempUserGAdjust();
            }			
            SET_OSD_STATE(_COLOR_TEMP_USER_G);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            break; 
            
            default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuColorTempUserBAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_COLOR_TEMP_TYPE_USER_B();
            ColorTempUserBAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                if((GET_COLOR_TEMP_TYPE() == _CT_9300)||(GET_COLOR_TEMP_TYPE() == _CT_6500))
                {
                    SET_USER_BASE_COLOR_TEMP_TYPE(GET_COLOR_TEMP_TYPE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }

                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    SET_COLOR_TEMP_TYPE( _CT_USER);
                }
                SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
                RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
            }
            SET_OSD_STATE(_COLOR_TEMP_USER_B);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                ColorTempUserBAdjust();
            }			
            SET_OSD_STATE(_COLOR_TEMP_USER_B);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_PAGE_COLORTEMP_USER_START,_IMAGE_PAGE_COLORTEMP_USER_END);
            break;  
            
            default:
            break;
    }
}

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuHybridGrayCurveAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_FPGA_GRAY_GAMMA();
            HybridGrayCurveAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                //SET_OSD_FPGA_GRAY_GAMMA(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_IMAGE_HYBRID_GRAY_CURVE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HYBRID_START,_IMAGE_HYBRID_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                HybridGrayCurveAdjust();
            }			
            SET_OSD_STATE(_IMAGE_HYBRID_GRAY_CURVE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HYBRID_START,_IMAGE_HYBRID_END);
            break;  
            
            default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHdrModeAdjProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_HDR_MODE();
            HdrModeAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_MODE())
            {                
                DrawHDRPage();
                if(((g_usBackupValue == _HDR10_MODE_OFF) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF)) ||
                   ((g_usBackupValue != _HDR10_MODE_OFF) && (GET_OSD_HDR_MODE() == _HDR10_MODE_OFF)))
                {
#if (_EDID_HDR10_AUTO_SWITCH == _ON)

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
                    // Switch All HDMI Port Edid
                    UserCommonInterfaceHDMISwitchAllPortEdid();
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                    // Switch Dp Version to 1.3, if HDR On
                    UserAdjustHdrCheckDpVersion(GET_OSD_HDR_MODE());

                    // Switch All DP Port Edid
                    UserCommonInterfaceDPSwitchAllPortEdid();
#endif

#if(_HDR10_SUPPORT == _ON)
                    UserCommonHDR10SupportSwitch();
#endif

#endif
                }
                
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_IMAGE_HDR_MODE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                HdrModeAdjust();
            }			
            SET_OSD_STATE(_IMAGE_HDR_MODE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;  
            
            default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageDarkEnhanceAdjProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_DARK_ENHANCE_STATUS();
            DarkEnhanceAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
        if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DARK_ENHANCE_STATUS(g_usAdjustValue);
                UserCommonHDRAdjust(_HDR_FLOW_OSD_DARK_ENHANCE);                
            }

            SET_OSD_STATE(_IMAGE_HDR_DARK_ENHANCE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                DarkEnhanceAdjust();
            }			
            SET_OSD_STATE(_IMAGE_HDR_DARK_ENHANCE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;  
            
            default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageSharpEnhanceAdjProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_HDR_SHARPNESS();
            SharpEnhanceAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
        if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_HDR_SHARPNESS(g_usAdjustValue);
#if(_ULTRA_VIVID_SUPPORT == _ON)
            UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
#endif
                
            }

            SET_OSD_STATE(_IMAGE_HDR_SHARP_ENHANCE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                SharpEnhanceAdjust();
            }			
            SET_OSD_STATE(_IMAGE_HDR_SHARP_ENHANCE);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;  
            
            default:
            break;
    }
#endif    
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuImageHdrContrastAdjProc(void)
{
#if(_HDR10_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_HDR_CONTRAST();
            HdrContrastAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_HDR_CONTRAST(g_usAdjustValue);
#if((_CONTRAST_SUPPORT == _ON) && (_HDR10_SUPPORT == _ON))
                UserCommonHDRAdjustHDR10Contrast(GET_OSD_HDR_CONTRAST());
#endif
                
            }

            SET_OSD_STATE(_IMAGE_HDR_CONTRAST);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                HdrContrastAdjust();
            }			
            SET_OSD_STATE(_IMAGE_HDR_CONTRAST);
            OsdSelectedUpdate(_STATE_SELECT,_IMAGE_HDR_START,_IMAGE_HDR_END);
            break;  
            
            default:
            break;
    }
#endif    
}


//==============================================================================
//======================== Service  Page  Start ================================
//==============================================================================

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_START, _SERVICE_PAGE_END, _ON));
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);

            DrawSubMenu(GET_OSD_STATE()); 
            break;
			
       	 case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:  
            SET_OSD_STATE(MGetFirstOsdState(_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_CLEAR);
            SET_OSD_STATE(_ADVANCED_PASSWORD);
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));

            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            DrawMainPage();
            UpdateMainMenuCursor(_MENU_ADVANCE,_STATE_SELECT);
            DrawSubMenu(_MENU_ADVANCE);           
            OsdSelectedUpdate(_STATE_SELECT,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_START, _SERVICE_PAGE_END, _ON));
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE: 
            SET_OSD_STATE(MGetFirstOsdState(_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END));

            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_CLEAR);
            SET_OSD_STATE(_ADVANCED_PASSWORD);
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            DrawMainPage();
            UpdateMainMenuCursor(_MENU_ADVANCE, _STATE_SELECT);
            DrawSubMenu(_MENU_ADVANCE);   
            OsdSelectedUpdate(_STATE_SELECT,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage3(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_START, _SERVICE_PAGE_END, _ON));
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE: 
            SET_OSD_STATE(MGetFirstOsdState(_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END));

            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_CLEAR);
            SET_OSD_STATE(_ADVANCED_PASSWORD);
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            DrawMainPage();
            UpdateMainMenuCursor(_MENU_ADVANCE, _STATE_SELECT);
            DrawSubMenu(_MENU_ADVANCE);   
            OsdSelectedUpdate(_STATE_SELECT,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            break;
            
        default:
            break;
    }
}

#if(_VGA_SUPPORT == _ON)       
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage4(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_START, _SERVICE_PAGE_END, _ON));
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE: 
            SET_OSD_STATE(MGetFirstOsdState(_ANALOG_PAGE_START,_ANALOG_PAGE_END));

            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START,_ANALOG_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_CLEAR);
            SET_OSD_STATE(_ADVANCED_PASSWORD);
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            DrawMainPage();
            UpdateMainMenuCursor(_MENU_ADVANCE, _STATE_SELECT);
            DrawSubMenu(_MENU_ADVANCE);   
            OsdSelectedUpdate(_STATE_SELECT,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            break;
            
        default:
            break;
    }
}
#endif


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_START, _SERVICE_PAGE_END, _ON));
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            DrawSubMenu(GET_OSD_STATE()); 
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE: 
            SET_OSD_STATE(MGetFirstOsdState(_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END));

            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            UpdateServiceMenuCursor(GET_OSD_STATE(),_STATE_CLEAR);
            SET_OSD_STATE(_ADVANCED_PASSWORD);
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(1), WIDTH(_WIN_MAINITEM_WIDTH), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            OsdFuncClearOsd(ROW(_OSD_MAIN_ITEM_ROW_START), COL(_SUBITEM_COL_START), WIDTH(g_ucOsdWidth-_SUBITEM_COL_START), HEIGHT(g_ucOsdHeight-_OSD_MAIN_ITEM_ROW_START - _WIN_INFO_HEIGHT));
            DrawMainPage();
            UpdateMainMenuCursor(_MENU_ADVANCE, _STATE_SELECT);
            DrawSubMenu(_MENU_ADVANCE);   
            OsdSelectedUpdate(_STATE_SELECT,_ADVANCED_PAGE_START,_ADVANCED_PAGE_END);
            break;
            
        default:
            break;
    }
}



//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage1DisplayRotate(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:          
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_DISPLAY_ROTATE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END);
            SET_OSD_STATE(_SERVICE_PAGE_1);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage1AspectRatio(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_ASPECT_RATIO_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_1_START, _SERVICE_PAGE_1_END);
            SET_OSD_STATE(_SERVICE_PAGE_1);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPVersion(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_DP_VERSION_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            SET_OSD_STATE(_SERVICE_PAGE_2);
           break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPMst(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_DP_MST_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            SET_OSD_STATE(_SERVICE_PAGE_2);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPClone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_DP_CLONE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            SET_OSD_STATE(_SERVICE_PAGE_2);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPResolution(void)
{
    switch(GET_KEYMESSAGE())
    {

        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_DP_RESOLUTION_ADJ);

            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            SET_OSD_STATE(_SERVICE_PAGE_2);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage3Uniformity(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_UNIFORMITY_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END);
            SET_OSD_STATE(_SERVICE_PAGE_3);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage3SDR(void)
{
#if (_SDR_TO_HDR_SUPPORT == _ON)        
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_SDR_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_3_START, _SERVICE_PAGE_3_END);
            SET_OSD_STATE(_SERVICE_PAGE_3);
            break;

        default:
            break;
    }
#endif    
}

//Analog Page
#if(_VGA_SUPPORT == _ON)       
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageAutoColorProc(void)
{
#if(_VGA_SUPPORT == _ON)
        WORD ucNewState = 0;
        BYTE ucTemp = 0;

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_ANALOG_PAGE_START, _ANALOG_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdSelectedUpdate(_STATE_ADJUST,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            GetItemValue(GET_OSD_STATE());
			#if(_VGA_SUPPORT == _ON)

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
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                }
                else
                {
                    UserCommonNVRamRestoreADCSetting();
                }
            }
			#endif
            //OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);    
#endif // End of #if(_VGA_SUPPORT == _ON)
            
            break;
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            SET_OSD_STATE(_SERVICE_PAGE_4);
            break;
    
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageAutoProc(void)
{
#if(_VGA_SUPPORT == _ON)
	WORD ucNewState = 0;

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_ANALOG_PAGE_START, _ANALOG_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() != _SOURCE_NONE)
                {
            OsdSelectedUpdate(_STATE_ADJUST,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
			#if(_VGA_SUPPORT == _ON)
	            g_usAdjustValue = 0;
	            UserCommonAutoConfig();
			#endif
			
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
                }
#endif
            break;
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            SET_OSD_STATE(_SERVICE_PAGE_4);
            break;
    
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageHPosProc(void)
{
#if(_VGA_SUPPORT == _ON)

	WORD ucNewState = 0;

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_ANALOG_PAGE_START, _ANALOG_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _MENU_KEY_MESSAGE:
            break;
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_ANALOG_PAGE_H_POS_ADJUST);
            break;
        	
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            SET_OSD_STATE(_SERVICE_PAGE_4);
            break;
            
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageVPosProc(void)
{
#if(_VGA_SUPPORT == _ON)

	WORD ucNewState = 0;

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_ANALOG_PAGE_START, _ANALOG_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _MENU_KEY_MESSAGE:
            break;
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_ANALOG_PAGE_V_POS_ADJUST);
            break;
        	
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            SET_OSD_STATE(_SERVICE_PAGE_4);
            break;
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageClockProc(void)
{
#if(_VGA_SUPPORT == _ON)

	WORD ucNewState = 0;

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_ANALOG_PAGE_START, _ANALOG_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _MENU_KEY_MESSAGE:
            break;
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_ANALOG_PAGE_CLOCK_ADJUST);
            break;
        	
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            SET_OSD_STATE(_SERVICE_PAGE_4);
            break;
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPagePhaseProc(void)
{
#if(_VGA_SUPPORT == _ON)

	WORD ucNewState = 0;

    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_ANALOG_PAGE_START, _ANALOG_PAGE_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _MENU_KEY_MESSAGE:
            break;
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_ANALOG_PAGE_PHASE_ADJUST);
            break;
        	
        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            SET_OSD_STATE(_SERVICE_PAGE_4);
            break;
        default:
            break;
    }
#endif
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5AmbientSensor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_AMBIENT_SENSOR_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            SET_OSD_STATE(_SERVICE_PAGE_5);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5BodySensor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_BODY_SENSOR_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            SET_OSD_STATE(_SERVICE_PAGE_5);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5GravitySensor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_GRAVITY_SENSOR_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            SET_OSD_STATE(_SERVICE_PAGE_5);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5BacklightSensor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_BACKLIGHT_SENSOR_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            SET_OSD_STATE(_SERVICE_PAGE_5);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5EnergySaving(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_ENERGY_SAVING_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            SET_OSD_STATE(_SERVICE_PAGE_5);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5Osd(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_SERVICE_PAGE_5_OSD_START);
            DrawSubMenu(_SERVICE_PAGE_5_OSD_START);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);

            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            SET_OSD_STATE(_SERVICE_PAGE_5);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdTimeProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_OSD_TIME_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            SET_OSD_STATE(_OSD);
            DrawSubMenu(_SERVICE_PAGE_5);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdPositionProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_OSD_POSITION_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            SET_OSD_STATE(_OSD);
            DrawSubMenu(_SERVICE_PAGE_5);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdRotateProc(void) 
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_OSD_ROTATE_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            SET_OSD_STATE(_OSD);
            DrawSubMenu(_SERVICE_PAGE_5);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        default:
            break;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdUseLifeProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(MGetNextOsdState(GET_OSD_STATE(),_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END, _ON));
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            OsdSelectedUpdate(_STATE_ADJUST,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            GetItemValue(GET_OSD_STATE());
            SET_OSD_STATE(_USE_LIFE_REMINDER_ADJ);
            break;

        case _EXIT_KEY_MESSAGE:
            ScalerOsdWindowDisable(_SUBMENU_SELECT_WINDOW);
            OsdSelectedUpdate(_STATE_CLEAR,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            SET_OSD_STATE(_OSD);
            DrawSubMenu(_SERVICE_PAGE_5);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START, _SERVICE_PAGE_5_END);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage1DisplayRotateAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                //g_usAdjustValue = GET_OSD_DISP_ROTATE();
                RotateAdjust();
            }			
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
                {
                    SET_OSD_DISP_ROTATE(g_usAdjustValue);

                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                }
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_DISPLAY_ROTATE);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    g_usAdjustValue = g_usBackupValue;
                    RotateAdjust(); 
                }			
            }			
            SET_OSD_STATE(_DISPLAY_ROTATE);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
            break;              

        default:
            break;
    }
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage1AspectRatioAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                //g_usAdjustValue = GET_OSD_ASPECT_RATIO_TYPE();
                AspectAdjust();
            }
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
#if(_ASPECT_RATIO_SUPPORT == _ON)
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
#else
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
#endif
                    
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }
            }
            SET_OSD_STATE(_ASPECT_RATIO);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    g_usAdjustValue = g_usBackupValue;
                    AspectAdjust();      
                }			
            }			
            SET_OSD_STATE(_ASPECT_RATIO);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_1_START,_SERVICE_PAGE_1_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPVersionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_DP_D0_VERSION();
            DPVersionAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DP_D0_VERSION(g_usAdjustValue);
                SET_OSD_DP_D1_VERSION(g_usAdjustValue);
                SET_OSD_DP_D2_VERSION(g_usAdjustValue);
                
                if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }
                

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE( _HDR10_MODE_OFF);

                    // Switch DP D0 Port Edid
                    ScalerDpEdidSwitch(_D0_INPUT_PORT);
                }
#endif
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_D1_INPUT_PORT, _HDR10_MODE_OFF);

                    // Switch DP D1 Port Edid
                    ScalerDpEdidSwitch(_D1_INPUT_PORT);
                }
#endif
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_D2_INPUT_PORT, _HDR10_MODE_OFF);

                    // Switch DP D2 Port Edid
                    ScalerDpEdidSwitch(_D2_INPUT_PORT);
                }
#endif
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            }
            SET_OSD_STATE(_DP_VERSION);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                DPVersionAdjust();
            }			
            SET_OSD_STATE(_DP_VERSION);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START, _SERVICE_PAGE_2_END);
            break; 
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPMstAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_DP_MST();
            DPMSTAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DP_MST(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());

                if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
#endif
            }
            SET_OSD_STATE(_DP_MST);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                DPMSTAdjust();      
            }			
            SET_OSD_STATE(_DP_MST);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPCloneAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            DPCloneAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
            SET_OSD_CLONE_MODE(g_usAdjustValue);                
#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
                UserCommonInterfaceCloneModeSwitch(GET_OSD_CLONE_MODE());
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_DP_CLONE);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                DPCloneAdjust();      
            }			
            SET_OSD_STATE(_DP_CLONE);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage2DPResolutionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);            
            DPResolutionAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                UserCommonNVRamSetSystemData(_EDID_D0_SELECT, g_usAdjustValue);
                UserCommonNVRamSetSystemData(_EDID_D1_SELECT, g_usAdjustValue);
                UserCommonNVRamSetSystemData(_EDID_D2_SELECT, g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                // Switch All DP Port Edid
                UserCommonInterfaceDPSwitchAllPortEdid();
#endif

            }
            SET_OSD_STATE(_DP_RESOLUTION);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                DPResolutionAdjust();
            }			
            SET_OSD_STATE(_DP_RESOLUTION);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_2_START,_SERVICE_PAGE_2_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage3UniformityAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY())
            UniformityAdjust();
            break;

            
        case _MENU_KEY_MESSAGE:
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PANEL_UNIFORMITY( g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_UNIFORMITY_SUPPORT == _ON)
                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    ScalerTimerWaitForEvent(_EVENT_DVS);
                    ScalerTimerDelayXms(2);
                    UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);

                    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
                }
#endif
            }
            SET_OSD_STATE(_UNIFORMITY);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                UniformityAdjust();      
            }			
            SET_OSD_STATE(_UNIFORMITY);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage3SDRAdj(void)
{
#if (_SDR_TO_HDR_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_PCM_STATUS();
            SDRAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PCM_STATUS( g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            }
            SET_OSD_STATE(_SDR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                SDRAdjust();      
            }			
            SET_OSD_STATE(_SDR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_3_START,_SERVICE_PAGE_3_END);
            break;              

        default:
            break;
    }
#endif    
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuReturnAnalogPageProc(BYTE ucState)
{
#if(_VGA_SUPPORT == _ON)

	BYTE y,ucColor,ucColorState = _ST_NORMAL;	
	BYTE ucStatus = COsdCtrlMenuItemGetEnable(ucState);
	
    y = GetShowIndex(ucState,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
    if(y == _NOT_SHOW)
        return;

    if(ucStatus == _EN_DL_STATE_DISABLE)
    {
        ucColorState = _ST_DISABLE;  
    }
    else if(ucStatus == _EN_DL_STATE_HIDDEN)
    {
		return;
    }

    // get display color
    ucColor = StateColor(ucColorState);
    
	SET_OSD_STATE(ucState);

	switch(ucState)
	{
        case _ANALOG_PAGE_H_POSTION_ITEM:
            OsdDispSliderAndNumber(_ANALOG_PAGE_H_POSTION_ITEM, GET_VGA_MODE_ADJUST_H_POSITION(),y,ucColor);
	        break;
	        
        case _ANALOG_PAGE_V_POSTION_ITEM:
            OsdDispSliderAndNumber(_ANALOG_PAGE_V_POSTION_ITEM, GET_VGA_MODE_ADJUST_V_POSITION(),y,ucColor);
            break;
            
        case _ANALOG_PAGE_CLOCK_ITEM:
            OsdDispSliderAndNumber(_ANALOG_PAGE_CLOCK_ITEM, GET_VGA_MODE_ADJUST_CLOCK(),y,ucColor);
            break;
            
        case _ANALOG_PAGE_PHASE_ITEM:
            OsdDispSliderAndNumber(_ANALOG_PAGE_PHASE_ITEM, GET_VGA_MODE_ADJUST_PHASE(),y,ucColor);
            break;

	}
#else
    ucState = ucState;

#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageHPosAdjustProc(void)
{
#if(_VGA_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            VGAHPosAdjust();
            break;
        case _MENU_KEY_MESSAGE:
            break;
            
        case _OK_KEY_MESSAGE:
        	if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
        	{
	            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
        	}        	
            SET_OSD_STATE(_ANALOG_PAGE_H_POSTION_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
                VGAHPosAdjust();                
            }
            SET_OSD_STATE(_ANALOG_PAGE_H_POSTION_ITEM);
            MenuReturnAnalogPageProc(_ANALOG_PAGE_H_POSTION_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
            
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageVPosAdjustProc(void)
{
#if(_VGA_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            VGAVPosAdjust();
            break;
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
        	if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
        	{
	            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
        	}        	
            SET_OSD_STATE(_ANALOG_PAGE_V_POSTION_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
                        
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
                VGAVPosAdjust();                
            }
            SET_OSD_STATE(_ANALOG_PAGE_V_POSTION_ITEM);            
            MenuReturnAnalogPageProc(_ANALOG_PAGE_V_POSTION_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
            
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPageClockAdjustProc(void)
{
#if(_VGA_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            VGAClockAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
        	if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
        	{
	            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
        	}        	
            SET_OSD_STATE(_ANALOG_PAGE_CLOCK_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
                VGAClockAdjust();                
            }
            SET_OSD_STATE(_ANALOG_PAGE_CLOCK_ITEM);
            MenuReturnAnalogPageProc(_ANALOG_PAGE_CLOCK_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
            
        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuAnalogPagePhaseAdjustProc(void)
{
#if(_VGA_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            VGAPhaseAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
        	if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
        	{
	            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
        	}        	
            SET_OSD_STATE(_ANALOG_PAGE_PHASE_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
                VGAPhaseAdjust();                
            }
            SET_OSD_STATE(_ANALOG_PAGE_PHASE_ITEM);            
            MenuReturnAnalogPageProc(_ANALOG_PAGE_PHASE_ITEM);
            OsdSelectedUpdate(_STATE_SELECT,_ANALOG_PAGE_START, _ANALOG_PAGE_END);
            break;
            
        default:
            break;
    }
#endif
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5AmbientSensorAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_AMBIENTLIGHT_SENSOR_STATUS();
            AmbientSensorAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_AMBIENTLIGHT_SENSOR_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                //Ambient Sensor:Start or Stop[Off state reading ambient lux] 
                ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);	
                if(IsGammaOptionDICOM(GET_OSD_GAMMA()))
                {
#if ((_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB) || (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB))
                    if(GET_OSD_DICOMALC()/(_ALC_AUTO) == _TRUE)
                    {
                        // == _ALC_AUTO
#if(_GAMMA_FUNCTION == _ON)
                        UserAdjustGamma(GET_OSD_GAMMA());
#endif
                    }                
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                    if((GET_OSD_DICOMALC()/(_ALC_AUTO) == _TRUE)&&(IsGammaOptionDICOMALC(GET_OSD_GAMMA())))
                    {
                        // == _ALC_AUTO
#if(_GAMMA_FUNCTION == _ON)
                        UserAdjustGamma(GET_OSD_GAMMA());
#endif
                    }
                    else
                        {}
#endif                
                }
                else
                {
                    UserAdjustBacklight(GET_OSD_BACKLIGHT());
                } 
/*                
                if(IsGammaOptionDICOM(GET_OSD_GAMMA())&&(GET_OSD_DICOMALC()/(_ALC_AUTO) == _TRUE))
                {
                    // == _ALC_AUTO
#if(_GAMMA_FUNCTION == _ON)
                    UserAdjustGamma(GET_OSD_GAMMA());
#endif
                }
                else
                {
                    UserAdjustBacklight(GET_OSD_BACKLIGHT());
                }
*/                
            }
            SET_OSD_STATE(_AMBIENT_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                AmbientSensorAdjust();      
            }			
            SET_OSD_STATE(_AMBIENT_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5BodySensorAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_DISTANCE_SENSOR_STATUS();
            BodySensorAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DISTANCE_SENSOR_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                //Distance Sensor:Start or Stop 
        		ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_DISTANCESENSOR_HANDLER);	 
            }
            SET_OSD_STATE(_BODY_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                BodySensorAdjust();      
            }			
            SET_OSD_STATE(_BODY_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5GravitySensorAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_DISTANCE_SENSOR_STATUS();
            GravitySensorAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_GRAVITY_SENSOR_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                //Distance Sensor:Start or Stop 
        		//ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GRAVITYSENSOR_HANDLER);	 
            }
            SET_OSD_STATE(_GRAVITY_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                GravitySensorAdjust();      
            }			
            SET_OSD_STATE(_GRAVITY_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5BacklightSensorAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_BACKLIGHT_SENSOR_STATUS();
            BacklightSensorEnAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_BACKLIGHT_SENSOR_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                //Backlight Sensor:Start or Stop 
            	if(GET_OSD_BACKLIGHT_SENSOR_STATUS()== _ON)
            	{
            		ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER);	 
            	}
            }
            SET_OSD_STATE(_BACKLIGHT_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                BacklightSensorEnAdjust();      
            }			
            SET_OSD_STATE(_BACKLIGHT_SENSOR);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;              
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5EnergySavingAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_POWER_SAVING_MODE();
            EnergySavingAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_POWER_SAVING_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_ENERGY_SAVING);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                EnergySavingAdjust();      
            }			
            SET_OSD_STATE(_ENERGY_SAVING);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_START,_SERVICE_PAGE_5_END);
            break;              
        default:
            break;
    }
}
void MenuServicePage5OsdTimeAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_TIME_OUT();                
            OsdTimeAdjust();
            break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_TIME_OUT(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                ScalerTimerReactiveTimerEvent(SEC(g_usAdjustValue), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            SET_OSD_STATE(_OSD_TIME);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                OsdTimeAdjust();
            }			
            SET_OSD_STATE(_OSD_TIME);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;              

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdPositionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_POSTION();
            OsdPositionAdjust();
            break;
            
        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_POSTION(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_OSD_POSITION);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                OsdPositionAdjust();
            }			
            SET_OSD_STATE(_OSD_POSITION);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdRotateAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
             g_usAdjustValue = GET_OSD_ROTATE_STATUS(); 
             OsdRotateAdjust();
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
             //OsdDispOsdRotateSwitch();
#endif
             break;

        case _MENU_KEY_MESSAGE:
            break;

        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ROTATE_STATUS())
            {
                //SET_OSD_ROTATE_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_OSD_ROTATE);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ROTATE_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                OsdRotateAdjust();
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
                //OsdDispOsdRotateSwitch();
#endif
             }			
            SET_OSD_STATE(_OSD_ROTATE);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;              

        default:
            break;
    }
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuServicePage5OsdUseLifeAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_PANEL_USELIFE_TIPS())
            UseLifeAdjust();
            break;

            
        case _MENU_KEY_MESSAGE:
        case _OK_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PANEL_USELIFE_TIPS(g_usAdjustValue);	
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_USE_LIFE_REMINDER);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;
            
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                g_usAdjustValue = g_usBackupValue;
                UseLifeAdjust();      
            }			
            SET_OSD_STATE(_USE_LIFE_REMINDER);
            OsdSelectedUpdate(_STATE_SELECT,_SERVICE_PAGE_5_OSD_START, _SERVICE_PAGE_5_OSD_END);
            break;              

        default:
            break;
    }
}

//==============================================================================
//======================= Service  Page  End ===================================
//==============================================================================


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyGammaAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {            
        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)            
            OsdDispHotKeyOptionMenu(_HOTKEY_AMB);
#endif
            break;
            
        case _RIGHT_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_KVM);
            break;
           
        case _MENU_KEY_MESSAGE:   
            OsdDispDisableOsd();
            SET_OSD_STATE(_MAINMENU_START);
            OsdDispMainMenu();
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            break;
            
        case _OK_KEY_MESSAGE:
            g_usAdjustValue = GET_OSD_GAMMA();	
            HotkeyGammaAdjust();
            break;

        case _EXIT_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX); 
            }
            break;

        case _POWER_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;
            
        default:
            break;
    }
}
#if(_BEACON_OSD_AMB == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyAmbAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
            g_usAdjustValue = GET_OSD_BACKGROUND_LIGHT_MODE();	
            HotkeyAmbAdjust();
            break;
            
        case _RIGHT_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_KVM);
            break;
            
        case _MENU_KEY_MESSAGE:   
            OsdDispDisableOsd();
            SET_OSD_STATE(_MAINMENU_START);
            OsdDispMainMenu();
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            break;
            
        case _OK_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_GAMMA);
            break;

        case _EXIT_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX); 
            }
            break;

        case _POWER_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;
            
        default:
            break;
    }
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyKVMAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)            
            OsdDispHotKeyOptionMenu(_HOTKEY_AMB); 
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _MENU_KEY_MESSAGE:   
            OsdDispDisableOsd();
            SET_OSD_STATE(_MAINMENU_START);
            OsdDispMainMenu();
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            break;

        case _OK_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_GAMMA);
            break;

        case _EXIT_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX); 
            }
            break;

        case _POWER_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyLightBoxAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)            
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispHotKeyOptionMenu(_HOTKEY_AMB);
            }
#endif            
            break;
            
        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispHotKeyOptionMenu(_HOTKEY_KVM);
            }
            break;
            
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispDisableOsd();
                SET_OSD_STATE(_MAINMENU_START);
                OsdDispMainMenu();
                UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            }
            break;

        case _OK_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_OFF)
            {
                OsdDispHotKeyOptionMenu(_HOTKEY_GAMMA);
            }
            break;
            
        case _EXIT_KEY_MESSAGE:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
	          
            /*if(b_usLightBoxLongPressFlag == _TRUE) 
            {
                b_usLightBoxLongPressFlag = _FALSE;
                g_usAdjustValue = UserCommonNVRamGetSystemData(_LIGHTBOX_MODE_TYPE);
                if(g_usAdjustValue >= _LIGHTBOX_MODE_FULL)
                {
                    g_usAdjustValue = _LIGHTBOX_MODE_LEFT;
                }
                else
                {
                    g_usAdjustValue++;
                }
                UserCommonNVRamSetSystemData(_LIGHTBOX_MODE_TYPE, g_usAdjustValue);
                UserCommonNVRamSaveSystemData();

                OsdDispShowLightBoxMode();
 
                ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);

                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);

            }
            else*/
            {
                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_LIGHTBOX);                
            }
            break;
        case _POWER_KEY_MESSAGE:
            if(GET_OSD_LIGHTBOXMODE_STATUS()==_ON)
            {
                ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            }
            else
            {
                OsdDispDisableOsd();
            }
            break;
            
        default:
            break;
    }
}
#if((_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)&&\
(_PRODUCT_ID_SEL != RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))    
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyColorMonoAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)            
            OsdDispHotKeyOptionMenu(_HOTKEY_AMB);
#endif
            break;
            
        case _RIGHT_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_KVM);
            break;
            
        case _MENU_KEY_MESSAGE:
            //g_usAdjustValue = GET_OSD_SATURATION();	
            HotkeyColorMonoAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;

        case _OK_KEY_MESSAGE:
	        OsdDispHotKeyOptionMenu(_HOTKEY_GAMMA);
            break;
            
        case _EXIT_KEY_MESSAGE:	
            {
	            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
	            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
	            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

                OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX); 
	            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
	            {
    	         	//Null
	            }
	            else
	            {	               
	                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
	            }
            }
            break;

        case _POWER_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;
            
        default:
            break;
    }
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuMenuHotkeyILuminanceAdjProc(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _LEFT_KEY_MESSAGE:
#if(_BEACON_OSD_AMB == _ON)            
            OsdDispHotKeyOptionMenu(_HOTKEY_AMB);
#endif
            break;
            
        case _RIGHT_KEY_MESSAGE:
            OsdDispHotKeyOptionMenu(_HOTKEY_KVM);
            break;
            
        case _MENU_KEY_MESSAGE:
            OsdDispDisableOsd();
            SET_OSD_STATE(_MAINMENU_START);
            OsdDispMainMenu();
            UpdateMainMenuCursor(GET_OSD_STATE(),_STATE_SELECT);
            break;

        case _OK_KEY_MESSAGE:
            //g_usAdjustValue = UserCommonNVRamGetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE);	
            HotkeyILuminanceAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            break;
            
        case _EXIT_KEY_MESSAGE:	
            {
	            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
	            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
	            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

                OsdDispHotKeyOptionMenu(_HOTKEY_LIGHTBOX); 
	            if(GET_OSD_LIGHTBOXMODE_STATUS() == _OFF)
	            {
    	         	//Null
	            }
	            else
	            {	               
	                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
	            }
            }
            break;

        case _POWER_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void MenuHotKeyInformation(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
        case _EXIT_KEY_MESSAGE:
        default:
            OsdDispDisableOsd();
            break;
    }
}

//==============================================================================
void MenuMeseageDisplay(void)
{
}

//==============================================================================
code void (*OperationTable[])(void) =
{
    
    MenuNone,
    MenuKey,

// Level 1
    MenuImagePage,
#if(_FPGA_TEST_IAMGE_SUPPORT == _ON)
    MenuQAPage,
#endif    
    MenuFunctionSettingPage,
    MenuInfoPage,
    MenuAdvancePage,

// Level 2
    MenuImagePCMProc,
    MenuImageGammaProc,   
    MenuImageDicomALCProc,    
    MenuImageColorTempProc,   
    MenuImageBacklightProc,
    MenuImageHDRProc,

    MenuQATestProc,  
    MenuQADeviationProc, 

    MenuFunctionLanguageProc,  
    MenuFunctionInputProc, 
    MenuFunctionAmbLightProc, 
    MenuFunctionReportModeProc, 
    MenuFunction2hoursReminderProc, 
    MenuFunctionFactoryResetProc, 

    MenuAdvancedPassWord,

// Level 3
    MenuImagePCMAdjProc,
    MenuImageGammaAdjProc, 
    MenuImageDicomALCAdjProc,    
    MenuImageColorTempAdjProc, 
    MenuImageBacklightAdjProc,

    MenuQATestImageAdjProc, 
    MenuMenuHotkeyDeviationAdjProc,

   // MenuQADeviationADJProc,

    MenuFunctionLanguageAdjProc, 
    MenuFunctionInputAdjProc,
    MenuFunctionAmbLightAdjProc, 
    MenuFunctionReportModeAdjProc, 
    MenuFunction2hoursReminderAdjProc, 
    MenuHotkeyFactoryResetAdjProc,

// Level 4
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    MenuGammaUserTypeProc, 
    MenuGammaUserLMaxProc, 
    MenuGammaUserLMinProc, 
    MenuGammaUserLambProc, 
    MenuGammaUserValueProc, 
    MenuGammaUserSetProc, 
#endif

    MenuColorTempUserRProc, 
    MenuColorTempUserGProc, 
    MenuColorTempUserBProc, 
#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    MenuHybridGrayCurveProc,
    MenuHybridColorCurveProc,
#endif    

    MenuImageHdrModeProc,
    MenuImageHdrDarkEnhanceProc,  
    MenuImageHdrSharpEnhanceProc,
    MenuImageHdrContrastProc,

// Level 5 
#if (_ARM_MCU_CALIBRATION_SUPPORT == _ON)
    MenuGammaUserTypeAdjProc,
    MenuGammaUserLMaxAdjProc,
    MenuGammaUserLMinAdjProc,
    MenuGammaUserLambAdjProc,
    MenuGammaUserValueAdjProc,
    //MenuGammaUserSetAdjProc,
#endif
    MenuColorTempUserRAdjProc,
    MenuColorTempUserGAdjProc,
    MenuColorTempUserBAdjProc,
#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    MenuHybridGrayCurveAdjProc,
#endif  

    MenuImageHdrModeAdjProc,
    MenuImageDarkEnhanceAdjProc,
    MenuImageSharpEnhanceAdjProc,
    MenuImageHdrContrastAdjProc,

// Service Page
// Level 3 
    MenuServicePage1,
    MenuServicePage2,
    MenuServicePage3,    
#if(_VGA_SUPPORT == _ON)           
    MenuServicePage4,    
#endif    
    MenuServicePage5,   

// Level 4 
    MenuServicePage1DisplayRotate,
    MenuServicePage1AspectRatio,

    MenuServicePage2DPVersion,
    MenuServicePage2DPMst,
    MenuServicePage2DPClone,
    MenuServicePage2DPResolution,

    MenuServicePage3Uniformity,
    MenuServicePage3SDR,
    
#if(_VGA_SUPPORT == _ON)
    MenuAnalogPageAutoColorProc,
    MenuAnalogPageAutoProc,
    MenuAnalogPageHPosProc,
    MenuAnalogPageVPosProc,
    MenuAnalogPageClockProc,
    MenuAnalogPagePhaseProc,
#endif

    MenuServicePage5AmbientSensor,
    MenuServicePage5BodySensor,
    MenuServicePage5GravitySensor,
    MenuServicePage5BacklightSensor,
    MenuServicePage5EnergySaving,
    MenuServicePage5Osd,
    
// Level 5 
    MenuServicePage1DisplayRotateAdj,
    MenuServicePage1AspectRatioAdj,

    MenuServicePage2DPVersionAdj,
    MenuServicePage2DPMstAdj,
    MenuServicePage2DPCloneAdj,
    MenuServicePage2DPResolutionAdj,

    MenuServicePage3UniformityAdj,
    MenuServicePage3SDRAdj,
    
#if(_VGA_SUPPORT == _ON)
    MenuAnalogPageHPosAdjustProc,
    MenuAnalogPageVPosAdjustProc,
    MenuAnalogPageClockAdjustProc,
    MenuAnalogPagePhaseAdjustProc,
#endif
    
    MenuServicePage5AmbientSensorAdj,
    MenuServicePage5BodySensorAdj,
    MenuServicePage5GravitySensorAdj,
    MenuServicePage5BacklightSensorAdj,
    MenuServicePage5EnergySavingAdj,

    MenuServicePage5OsdTimeProc,
    MenuServicePage5OsdPositionProc,    
    MenuServicePage5OsdRotateProc,
    MenuServicePage5OsdUseLifeProc,

    MenuServicePage5OsdTimeAdj,
    MenuServicePage5OsdPositionAdj,
    MenuServicePage5OsdRotateAdj,
    MenuServicePage5OsdUseLifeAdj,
    
    // HOT KEY
    MenuMenuHotkeyGammaAdjProc,
#if(_BEACON_OSD_AMB == _ON)    
    MenuMenuHotkeyAmbAdjProc,
#endif    
    MenuMenuHotkeyKVMAdjProc,
#if((_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)&&\
    (_PRODUCT_ID_SEL != RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))        
    MenuMenuHotkeyColorMonoAdjProc,
#endif    
    MenuMenuHotkeyILuminanceAdjProc,
    MenuMenuHotkeyLightBoxAdjProc,
    
    MenuHotKeyInformation,
    MenuMeseageDisplay,
};

#endif// #if(_OSD_TYPE == _BEACON_2014_OSD)
