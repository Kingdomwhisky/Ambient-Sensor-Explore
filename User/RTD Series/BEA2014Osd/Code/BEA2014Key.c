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
// ID Code      : BEA2014Key.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_KEY__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------
#define _RELEASE_KEY_MASK                           0x00
#define _POWER_KEY_MASK                             0x01
#define _MENU_KEY_MASK                              0x02
#define _RIGHT_KEY_MASK                             0x04
#define _UP_KEY_MASK								0x06
#define _LEFT_KEY_MASK                              0x08
#define _DOWN_KEY_MASK								0x0E
#define _EXIT_KEY_MASK                              0x10
#define _OK_KEY_MASK                                0x20 
//#define _LIGHTBOX_KEY_MASK                          0x40
#define _SOURCE_KEY_MASK                            0x80 //IR use
//#define _KEY5_MASK                                  0x20
//#define _KEY6_MASK                                  0x40
//#define _KEY7_MASK                                  0x80

#define _POWER_RIGHT_KEY_MASK                       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
#define _POWER_MENU_KEY_MASK                        (_POWER_KEY_MASK | _MENU_KEY_MASK)
#define _POWER_LEFT_RIGHT_KEY_MASK                  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)

//--------------------------------------------------
// Definitions of IR Key Code
//--------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
#define _IR_CODE_KEY_POWER                          0x0408
#define _IR_CODE_KEY_MENU                           0x0443
#define _IR_CODE_KEY_RIGHT                          0x0406
#define _IR_CODE_KEY_LEFT                           0x0407
#define _IR_CODE_KEY_EXIT                           0x045B

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
#define _IR_CODE_KEY_POWER                          0x0950
#define _IR_CODE_KEY_MENU                           0x0A50
#define _IR_CODE_KEY_RIGHT                          0x0920
#define _IR_CODE_KEY_LEFT                           0x0930
#define _IR_CODE_KEY_EXIT                           0x0940

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
#define _IR_CODE_KEY_POWER                          0x000C
#define _IR_CODE_KEY_MENU                           0x005C
#define _IR_CODE_KEY_RIGHT                          0x005B
#define _IR_CODE_KEY_LEFT                           0x005A
#define _IR_CODE_KEY_EXIT                           0x000A

#elif(_IR_PROTOCAL == _IR_NEC_BEACON)
//Custom Code:0x00EF  Menu:0x42
//Debug:IR0:0xBD IR1:0x42 IR2:0xEF IR3:0x00 
#define _IR_CODE_KEY_POWER                          0xEDEF
#define _IR_CODE_KEY_MENU                           0xBDEF  
#define _IR_CODE_KEY_RIGHT                          0xBAEF
#define _IR_CODE_KEY_LEFT                           0xEEEF
#define _IR_CODE_KEY_EXIT                           0xBCEF

#define _IR_CODE_KEY_SOURCE                         0xE9EF
#define _IR_CODE_KEY_OK                             0xEFEF  
#define _IR_CODE_KEY_UP                             0xEAEF
#define _IR_CODE_KEY_DOWN                           0xBFEF

//Custom Code:0xCA35  Menu:0x4E
//Debug:IR0:0xB1 IR1:0x4E IR2:0xCA IR3:0x35 
#define _IR_CODE_KEY2_POWER                         0xAFCA
#define _IR_CODE_KEY2_MENU                          0xB1CA  
#define _IR_CODE_KEY2_RIGHT                         0xA6CA
#define _IR_CODE_KEY2_LEFT                          0xF5CA
#define _IR_CODE_KEY2_EXIT                          0xFCCA

#define _IR_CODE_KEY2_SOURCE                        0xB8CA
#define _IR_CODE_KEY2_OK                            0xB0CA  
#define _IR_CODE_KEY2_UP                            0xB3CA
#define _IR_CODE_KEY2_DOWN                          0xB2CA

#define _IR_CODE_KEY2_LIGHTBOX                      0xA7CA

// Mute:IR0:0xA5 IR1:0x5A IR2:0xCA IR3:0x35
// Auto:IR0:0xA7 IR1:0x58 IR2:0xCA IR3:0x35
// DVI: IR0:0xA8 IR1:0x57 IR2:0xCA IR3:0x35
// BNC: IR0:0xA9 IR1:0x56 IR2:0xCA IR3:0x35
// Info:IR0:0xAA IR1:0x55 IR2:0xCA IR3:0x35
// HDMI:IR0:0xFD IR1:0x02 IR2:0xCA IR3:0x35
// VGA: IR0:0xFE IR1:0x01 IR2:0xCA IR3:0x35
// SDI: IR0:0xFF IR1:0x00 IR2:0xCA IR3:0x35

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucKeyStatePrev;
BYTE g_ucKeyStateCurr;
BYTE g_ucKeyStateSkip;

#if(_AD_KEY_SUPPORT == _ON)
BYTE g_ucBackupKeyState = 0xFF;
#endif

BYTE g_ucKeyLockCount = 0;
BYTE code tLockKeyPassword[] = 
{
    _POWER_KEY_MESSAGE,
    _LEFT_KEY_MESSAGE,
    _LEFT_KEY_MESSAGE,
    _LEFT_KEY_MESSAGE,
};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceKeyHandler(void);
void RTDKeyInitial(void);
bit RTDKeyScanReady(void);
BYTE RTDKeyScan(void);
bit RTDKeyPowerKeyProc(void);
void RTDKeyPowerKeyMix(void);
void RTDKeyMessageProc(void);
void RTDKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);
bit RTDKeySpecialProc(BYTE ucKeyMask);

void RTDKeyHoldKeyTimerCancel(void);
void RTDKeyHoldKeyCheck(void);
void RTDKeyLockKeyProc(BYTE ucKeyMsg);
void RTDKeyBuzzerBeepProc(void);


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE RTDIRKeyScan(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Key Handler, executed in the main loop.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyHandler(void)
{
    // Skip key status update for tool
    if(g_ucKeyStateSkip != 0)
    {
        g_ucKeyStateSkip = 0;
        return;
    }

    // Clear the key message
    if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
    {
        // Clear the key message for DDCCI Key CMD:[Cancel]
        //SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
    }

	// Calibration Mode Skip
    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) != _OFF)
	{
        return;
	}
        
    if(RTDKeyScanReady() == _TRUE)
    {
        // Store previous key state
        g_ucKeyStatePrev = g_ucKeyStateCurr;

        // Get current key state
        g_ucKeyStateCurr = RTDKeyScan();

        // Set current key Buzzer Beep
		RTDKeyBuzzerBeepProc();

        // Power key process, return if power key is pressed
        if(RTDKeyPowerKeyProc() == _TRUE)
        {
            return;
        }

        // Convert key state to key message, store in (ucKeyNotify)
        RTDKeyMessageProc();
		if(GET_KEYMESSAGE() != _NONE_KEY_MESSAGE)
		{
		    // Lock Key Handler
	    	RTDKeyLockKeyProc(GET_KEYMESSAGE());
			
			if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_AC_ON_TEST_IMAGE_DISPLAY_TIME) == _TRUE)
			{
				DebugMessageUart("Exit Test IMAGE:", GET_OSD_FPGA_TEST_IMAGE());
				ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_AC_ON_TEST_IMAGE_DISPLAY_TIME);   
			    return;
			}
		}
        
    }
}

//--------------------------------------------------
// Description  : Key intial.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDKeyScanReady(void)
{
    if((GET_KEYSCANSTART() == _TRUE) &&
       (GET_KEYSCANREADY() == _TRUE))
    {
        return _TRUE;
    }
    else if(GET_KEYSCANSTART() == _FALSE)
    {
        // Set Scan start flag.
        SET_KEYSCANSTART();

        // SET_KEYSCANREADY();
        // Wait 0.02 sec in order to keep the keypad debounce
        ScalerTimerReactiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_KEY_SCAN_READY);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Key Buzzer Beep.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyBuzzerBeepProc(void)
{
    if((_BUZZER_BEEP_PWM != _NO_PWM)&&(g_ucKeyStateCurr != _RELEASE_KEY_MASK) && (g_ucKeyStatePrev == _RELEASE_KEY_MASK))
	{
        if((SysPowerGetPowerStatus() == _POWER_STATUS_OFF)/* || (UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS) == _ON)*/)
    	{
	    	if(g_ucKeyStateCurr == _POWER_KEY_MASK)
    		{
                PCB_BUZZER_BEEP_PWM(_PWM_DUT_RESOLUTION == _PWM_12BIT ? 0x800 : 0x80);

			    ScalerTimerActiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_KEY_BEEP_READY);
    		}
			else
			{
                PCB_BUZZER_BEEP_PWM(0x00);
			}
		}
		else
    	{
            PCB_BUZZER_BEEP_PWM(_PWM_DUT_RESOLUTION == _PWM_12BIT ? 0x800 : 0x80);

		    ScalerTimerActiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_KEY_BEEP_READY);
    	}
	}
}	

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE RTDKeyScan(void)
{
    BYTE ucKeyState = 0;
    BYTE ucVoltage0 = 0;
    BYTE ucVoltage1 = 0;
    BYTE ucVoltage2 = 0;
    BYTE ucVoltage3 = 0;

#if(_AD_KEY_SUPPORT == _ON)
    ucVoltage0 = PCB_ADKEY0();
    ucVoltage1 = PCB_ADKEY1();
    ucVoltage2 = PCB_ADKEY2();
    ucVoltage3 = PCB_ADKEY3();
 
#if 1
    pData[0] = 0;
    do
    {
        ScalerTimerDelayXms(2);

        if((abs(PCB_ADKEY0() - ucVoltage0) < 2) && (abs(PCB_ADKEY1() - ucVoltage1) < 2) && (abs(PCB_ADKEY2() - ucVoltage2) < 2) && (abs(PCB_ADKEY3() - ucVoltage3) < 2))
        {
            break;
        }
        else
        {
	        ucVoltage0 = (PCB_ADKEY0() & 0xfc);
	        ucVoltage1 = (PCB_ADKEY1() & 0xfc);
	        ucVoltage2 = (PCB_ADKEY2() & 0xfc);
	        ucVoltage3 = (PCB_ADKEY3() & 0xfc);
        }

        pData[0]++;
    }
    while(pData[0] < 10);

#endif    
    if(ucVoltage1 < 248)
    {
        DebugMessageUart(" ucVoltage1= ", ucVoltage1);
    }

    if(ucVoltage2 < 248)
    {
        DebugMessageUart(" ucVoltage2= ", ucVoltage2);
        
        //DebugMessageUart(" _OSD_END= ", _OSD_DATA_USER_ADDRESS_END);
        //DebugMessageUart(" TIME_END= ", _PANEL_TIME_DATA_ADDRESS_END);
        
        //DebugMessageUart(" USER2_END= ", _OSD_USER2_DATA_ADDRESS_END);
    } 
    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);

    if((g_ucBackupKeyState == ucKeyState) && (ucKeyState != 0))
    {
        if(GET_KEYREPEATENABLE() != _ON)
        {
            RTDKeyInitial();
        }

        return g_ucBackupKeyState;
    }
    else
    {
        g_ucBackupKeyState = ucKeyState;
        ucKeyState = 0;
    }

#else
    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);
#endif // End of #if(_AD_KEY_SUPPORT == _ON)

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    if(ucKeyState == 0x00)
    {
        ucKeyState = RTDIRKeyScan();
    }
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

    if(ucKeyState != 0)
    {
        RTDKeyInitial();
    }

    return ucKeyState;
}

//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit RTDKeyPowerKeyProc(void)
{
    if((g_ucKeyStateCurr & _POWER_KEY_MASK) != 0)
    {
        if(((g_ucKeyStatePrev ^ g_ucKeyStateCurr) & _POWER_KEY_MASK) != 0)
        {
            RTDKeyPowerKeyMix();
#if 0
	        if((ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON) == _TRUE)||(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_PANEL_POWER_OFF) == _TRUE))
			{
		        DebugMessageUart(">> T3&T6 Skip Power <<", UserCommonTimerGetEventRemainTime(_USER_TIMER_EVENT_PANEL_POWER_OFF));
		        // Skip key process check in Panel On T3, and Panel Off T6 states
		        return _TRUE;
	    	}

		    if((SysModeGetModeState()==_MODE_STATUS_INITIAL)||(SysModeGetModeState()==_MODE_STATUS_DISPLAY_INITIAL))
		    {
		        DebugMessageUart(">> initial Skip Power <<", SysModeGetModeState());
		        // Skip key process check in initial, and display initial states
		        return _TRUE;
	    	}
            
            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                SET_OSD_STATE(_MENU_NONE);
                SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            }
            else
            {
                SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
            }

            return _TRUE;
#endif
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyPowerKeyMix(void)
{
    switch(g_ucKeyStateCurr)
    {
        case _POWER_RIGHT_KEY_MASK:
            break;

        case _POWER_MENU_KEY_MASK:
            break;

        case _POWER_LEFT_RIGHT_KEY_MASK:
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : Convert keypad status into key message, stores in ucKeyNotify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyMessageProc(void)
{
    switch(g_ucKeyStateCurr)
    {
        case _MENU_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:
            RTDKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            break;

        case _LEFT_KEY_MASK:
            RTDKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            break;

        case _EXIT_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_EXIT_KEY_MASK, _EXIT_KEY_MESSAGE);
            break;

        case _OK_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_OK_KEY_MASK, _OK_KEY_MESSAGE);
            break;

    	case _POWER_KEY_MASK:
            CLR_KEYREPEATENABLE();
	        RTDKeyMessageConvert(_POWER_KEY_MASK, _POWER_KEY_MESSAGE);
    		break;
            
#if 0
        case _KEY5_MASK:
#if 0
            if((ScalerOsdGetOsdEnable() == _OFF) && (SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL))
            {
                RTDFactoryMainMenu();
            }
            else
#endif
            {
                CLR_KEYREPEATENABLE();
                RTDKeyMessageConvert(_KEY5_MASK, _EXIT_KEY_MESSAGE);
            }
            break;
#endif

        default:
            if((g_ucKeyStateCurr == _RELEASE_KEY_MASK) &&
               (g_ucKeyStatePrev != _RELEASE_KEY_MASK))
            {
                RTDKeyHoldKeyCheck(); // Check key release
            }
            CLR_KEYREPEATSTART();
            CLR_KEYREPEATENABLE();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            break;
    }
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void RTDKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    // Key different
    if((g_ucKeyStatePrev != g_ucKeyStateCurr) && (ucKeyMask == g_ucKeyStateCurr))
    {
        // KeyLock function
        if (RTDKeySpecialProc(ucKeyMask) == _FALSE)
        {
            SET_KEYMESSAGE(ucKeyMsg);
            RTDKeyHoldKeyTimerCancel();
        }
    }
    else // Key the same
    {
        if(GET_KEYREPEATENABLE() == _TRUE)
        {
            if(GET_KEYREPEATSTART() == _TRUE)
            {
                SET_KEYMESSAGE(ucKeyMsg);
            }
            else
            {
                // Set repeat key after 500ms.
                ScalerTimerActiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            }
        }
    }
}


//--------------------------------------------------
// Description  :  for special key check
// Input Value  : scan Key data
// Output Value : None
//--------------------------------------------------
bit RTDKeySpecialProc(BYTE ucKeyMask)
{
	if((SysModeGetModeState() == _MODE_STATUS_POWER_OFF)&&(ucKeyMask != _POWER_KEY_MASK))
    {
	    return _FALSE;
    }

	if(UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS) == _ON)
	{
        if((GET_OSD_STATE() == _MENU_HOTKEY_LIGHTBOX_MODE) && (ucKeyMask == _EXIT_KEY_MASK) && (GET_OSD_LIGHTBOXMODE_STATUS() == _ON))
        {
            // Not Skip
        }
        else
        {
		    return _FALSE;
        }
	}

#if 0
    if((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _LEFT_KEY_MASK))
    {
#if(_DP_SUPPORT == _ON)
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();
        return _TRUE;
#endif
    }

#if 0//(_VGA_SUPPORT == _ON)
    // Press Exit key for 3 sec to do Auto color
    else if((GET_OSD_STATE() == _MENU_NONE) && (SysSourceGetSourceType() == _SOURCE_VGA))
    {
        if (ucKeyMask == _EXIT_KEY_MASK)
        {
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_DO_AUTO_COLOR);
            SET_KEY_HOLD();
            CLR_KEYREPEATENABLE();
            return _TRUE;
        }
    }
#endif
#endif

    // Press key for 3 sec to do ...
    /*
    if((GET_OSD_STATE() == _MENU_HOTKEY_LIGHTBOX_MODE) && (ucKeyMask == _EXIT_KEY_MASK) && (GET_OSD_LIGHTBOXMODE_STATUS() == _ON))
    {
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_LIGHTBOXMODE_LONG_PRESS);
        ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_LIGHTBOX_OSD_DISABLE);
        DebugMessageUart("3", 3);        
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();        
        return _TRUE;
    }
    else */if((GET_OSD_STATE() == _MENU_HOTKEY_KVM_MODE) && (ucKeyMask == _RIGHT_KEY_MASK) )
    {
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_SET_KVM_DISPLAY_MODE);
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();        
        return _TRUE;
    }
    else if((GET_OSD_STATE() <= _MENU_KEY) && (ucKeyMask == _POWER_KEY_MASK)) 
    {
        // Beacon demand: Continuous press 3 seconds into Power off mode,Press the power key to return to Power on mode
    	//              : Power Saving mode does not enter Power off mode
    	if(SysModeGetModeState() == _MODE_STATUS_POWER_OFF)
        {
            ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_SYSTEM_POWER_ONOFF);
        }
        else if(SysModeGetModeState() != _MODE_STATUS_POWER_SAVING)
        {
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_SYSTEM_POWER_ONOFF);
        }

            SET_KEY_HOLD();
            CLR_KEYREPEATENABLE();
            return _TRUE;

    } 
#if((_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)&&(_PRODUCT_ID_SEL != RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM_DBI)&&\
    (_PRODUCT_ID_SEL != RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM))        
    else if((GET_OSD_STATE() == _MENU_KEY) && (ucKeyMask == _MENU_KEY_MASK))
    {
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_COLORMONO_LONG_PRESS);
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();        
        return _TRUE;
    }
#endif    
    else if((GET_OSD_STATE() == _MENU_KEY) && (ucKeyMask == _OK_KEY_MASK))
    {
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_KEY_PLUS_LUMINANCE_DISPLAY_MODE);
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();        
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyHoldKeyTimerCancel(void)
{
    if(GET_KEY_HOLD() == _TRUE)
    {
        CLR_KEY_HOLD();

        // list all off hold key timer event here!!!
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
    	//ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_LIGHTBOXMODE_LONG_PRESS);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_LOCAL_ENHANCEMENT);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_SYSTEM_POWER_ONOFF);
    if(IsMonoChromeorColorPanel() == M_COLOR)
        {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_COLORMONO_LONG_PRESS);
        }
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_SET_KVM_DISPLAY_MODE);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_PLUS_LUMINANCE_DISPLAY_MODE);
#if(_DP_SUPPORT == _ON)
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
#endif
    }
}

//--------------------------------------------------
// Description  : Hold Key check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyHoldKeyCheck(void)
{
    if(GET_KEY_HOLD() == _TRUE)
    {
        switch(g_ucKeyStatePrev)
        {
            case _EXIT_KEY_MASK:
                SET_KEYMESSAGE(_EXIT_KEY_MESSAGE);
                break;

            case _MENU_KEY_MASK:
                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
                break;
            case _RIGHT_KEY_MASK:
                SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
                break;
            case _LEFT_KEY_MASK:
                SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
                break;

            case _UP_KEY_MASK:
                SET_KEYMESSAGE(_UP_KEY_MESSAGE);
                break;
				
            case _DOWN_KEY_MASK:
                SET_KEYMESSAGE(_DOWN_KEY_MESSAGE);
                break;
				
            case _OK_KEY_MASK:
                SET_KEYMESSAGE(_OK_KEY_MESSAGE);
                break;
				
            case _SOURCE_KEY_MASK:
                SET_KEYMESSAGE(_SOURCE_KEY_MESSAGE);
                break;

            case _POWER_KEY_MASK:
                SET_KEYMESSAGE(_POWER_KEY_MESSAGE);
                break;

            default:
                break;
        }
        RTDKeyHoldKeyTimerCancel();
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyLockKeyProc(BYTE ucKeyMsg)
{	
	// No OSD
	if((GET_OSD_STATE() == _MENU_NONE) /*&& (ScalerOsdGetOsdEnable() == _FALSE)*/)
	{
		if(ucKeyMsg == tLockKeyPassword[g_ucKeyLockCount])
		{
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_LOCK_COUNT);
            ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_KEY_LOCK_COUNT);
			g_ucKeyLockCount++;

            // Check NSG to PS condition in display
            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
            if(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)
                {
                ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                }
            else
                {
                ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                }
                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()+3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
			if(g_ucKeyLockCount >= sizeof(tLockKeyPassword))
			{
				CLR_KEYREPEATENABLE();
				
			    if(UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS) == _OFF)
			    {
			    	UserCommonNVRamSetSystemData(_KEY_LOCK_STATUS, _ON);
			    }
			    else if(UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS) == _ON)
			    {
			    	UserCommonNVRamSetSystemData(_KEY_LOCK_STATUS, _OFF);
				}
				UserCommonNVRamSaveSystemData();

			    g_ucKeyLockCount = 0;
			   	SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
				RTDKeyHoldKeyTimerCancel();
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_LOCK_COUNT);
                ScalerTimerActiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_KEY_LOCK_OSD_MSG);

			   	DebugMessageUart("***lock status***=", UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS));
			   	return;
			}
            if((ucKeyMsg == tLockKeyPassword[0])&&(GET_PANELPOWERSTATUS()!= _BACKLIGHT_ON_ALREADY)&&(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                // Power Key Wake up
            }
            else
            {
    		   	SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
		    }
			RTDKeyHoldKeyTimerCancel();
		}
		else
		{
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_LOCK_COUNT);
			g_ucKeyLockCount = 0;
		}
	
	}

	if(UserCommonNVRamGetSystemData(_KEY_LOCK_STATUS) == _ON)
	{
    	//  != LightBoxMode
	    if(ucKeyMsg != _EXIT_KEY_MESSAGE)
		{
            if((GET_OSD_LIGHTBOXMODE_STATUS() == _ON)&&(ScalerOsdGetOsdEnable() == _TRUE)&&(ucKeyMsg == _EXIT_KEY_MESSAGE))
        	{
              // Not Skip
        	}
            else if(((GET_OSD_STATE() == _MENU_KEY)||(GET_OSD_STATE() == _MENU_HOTKEY_LIGHTBOX_MODE))&&(ucKeyMsg == _POWER_KEY_MESSAGE))
        	{
              // Not Skip: Power Key Exit UI
        	}
            else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)&&(ucKeyMsg == _POWER_KEY_MESSAGE))
            {
              // Not Skip: Power Key Wake up
	        }
			else
			{
				SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
			}
		   	DebugMessageUart("***lock Key***=", GET_KEYMESSAGE());
			RTDKeyHoldKeyTimerCancel();
			//if((ucKeyMsg != _POWER_KEY_MESSAGE)&&(ucKeyMsg != _LEFT_KEY_MESSAGE))
            if(ucKeyMsg == tLockKeyPassword[(g_ucKeyLockCount >= 1 ? g_ucKeyLockCount - 1 : g_ucKeyLockCount)])
		    {
              // Not Show OSD            
            }
            else
			{
                ScalerTimerActiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_KEY_LOCK_OSD_MSG);
			}
		}
	}
}

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : IR Key Scan
// Input Value  : None
// Output Value : Key Mask
//--------------------------------------------------
BYTE RTDIRKeyScan(void)
{
    BYTE pucIRCodeBuffer[8] = {0};
    WORD usKeyCode = 0;
    BYTE ucKeyState = 0;

    if(ScalerIRHWModeGetData(pucIRCodeBuffer) == _TRUE)
    {
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
        if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (pucIRCodeBuffer[2] == ~(pucIRCodeBuffer[3])))
        {
            usKeyCode = (((WORD)pucIRCodeBuffer[3]) << 8) + pucIRCodeBuffer[1];
        }

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
        usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[1];

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
        usKeyCode = (((WORD)pucIRCodeBuffer[2]) << 8) + pucIRCodeBuffer[3];

#elif(_IR_PROTOCAL == _IR_NEC_BEACON)
        if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (((pucIRCodeBuffer[2] == 0xEF)&&(pucIRCodeBuffer[3] == 0x00))||(pucIRCodeBuffer[2] == ~(pucIRCodeBuffer[3]))))
        {
            usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[2];
        }
#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)

        switch(usKeyCode)
        {
            case _IR_CODE_KEY_POWER:
            case _IR_CODE_KEY2_POWER:
                ucKeyState = _POWER_KEY_MASK;
                break;

            case _IR_CODE_KEY_MENU:
            case _IR_CODE_KEY2_MENU:
                ucKeyState = _MENU_KEY_MASK;
                break;

            case _IR_CODE_KEY_RIGHT:
            case _IR_CODE_KEY2_RIGHT:
                ucKeyState = _RIGHT_KEY_MASK;
                break;

            case _IR_CODE_KEY_LEFT:
            case _IR_CODE_KEY2_LEFT:
                ucKeyState = _LEFT_KEY_MASK;
                break;

            case _IR_CODE_KEY_EXIT:
            case _IR_CODE_KEY2_EXIT:
                ucKeyState = _EXIT_KEY_MASK;
                break;

#if(_IR_PROTOCAL == _IR_NEC_BEACON)
            case _IR_CODE_KEY_SOURCE:
            case _IR_CODE_KEY2_SOURCE:
				if(_TRUE)//(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
	                ucKeyState = _RIGHT_KEY_MASK;
				else
                    ucKeyState = _SOURCE_KEY_MASK;
                break;

            case _IR_CODE_KEY_OK:
            case _IR_CODE_KEY2_OK:
            	if((GET_OSD_STATE() != _MENU_NONE) && (ScalerOsdGetOsdEnable() == _TRUE))
				//if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
	                ucKeyState = _MENU_KEY_MASK;
				else
	                ucKeyState = _OK_KEY_MASK;
                break;

            case _IR_CODE_KEY_UP:
            case _IR_CODE_KEY2_UP:
				if(_TRUE)//(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
	                ucKeyState = _LEFT_KEY_MASK;
				else
	                ucKeyState = _UP_KEY_MASK;
                break;
                
            case _IR_CODE_KEY_DOWN:
            case _IR_CODE_KEY2_DOWN:
				if(_TRUE)//(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
	                ucKeyState = _RIGHT_KEY_MASK;
				else
	                ucKeyState = _DOWN_KEY_MASK;
                break;
#endif

            default:
                ucKeyState = 0x00;
                break;
        }
    }

    return ucKeyState;
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#endif//#if(_OSD_TYPE == _BEACON_2014_OSD)
