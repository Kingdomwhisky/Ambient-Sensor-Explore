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
// ID Code      : RL6449_QA_A_156PIN_2H1DP_eDP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6449_QA_A_156PIN_2H1DP_eDP)


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                               _XTAL14318K


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_MINI
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                     _D2_HDMI_PORT
#define _D2_DDC_CHANNEL_SEL                     _DDC2
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D2_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_HDMI_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D2_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D3_INPUT_PORT


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_FB_SWAP                 _DISABLE
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            12
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_SWING_LEVEL             _DP_SWING_800_MV
#define _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_3_5_DB

//--------------------------------------------------
// eDPTx 1.2 HBR2 SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_SPREAD_RANGE            12
#define _PANEL_DPTX_1_2_SPREAD_SPEED            _SPEED_33K

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_FB_SWAP                 _DISABLE
#define _PANEL_DPTX_1_2_LANE_SWAP               _DISABLE
#define _PANEL_DPTX_1_2_LANE_PN_SWAP            _DISABLE


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _PWM1
#define _BACKLIGHT_PWM_INVERSE                  _ON

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _ON
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _OFF

#define _PWM0_PSAV_EN                           _OFF
#define _PWM1_PSAV_EN                           _OFF
#define _PWM2_PSAV_EN                           _OFF
#define _PWM3_PSAV_EN                           _OFF
#define _PWM4_PSAV_EN                           _OFF
#define _PWM5_PSAV_EN                           _OFF

#define _PWM0_PDOW_EN                           _OFF
#define _PWM1_PDOW_EN                           _OFF
#define _PWM2_PDOW_EN                           _OFF
#define _PWM3_PDOW_EN                           _OFF
#define _PWM4_PDOW_EN                           _OFF
#define _PWM5_PDOW_EN                           _OFF

#define _PWM0_RST_EN                            _OFF
#define _PWM1_RST_EN                            _ON
#define _PWM2_RST_EN                            _OFF
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM5_RST_EN                            _OFF
#define _PWM_RST_SIGNAL_SEL                     _DVS


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                         _OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _ON
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _HW_IIC_PIN_210_211


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                         _ON

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                  _ON


//////////////////////
// Series Pin Share //
//////////////////////
#include "RL6449_QA_A_156PIN_2H1DP_eDP_PINSHARE.h"


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                }

#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                {\
                                                }

#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define bVCCKOFFPOWER                           (MCU_FE21_PORT81_PIN_REG) // _156PIN_PIN_135

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#define bDDRPOWER                               (MCU_FE29_PORT91_PIN_REG) // _156PIN_PIN_147

#define _DDR_POWER_ON                           1
#define _DDR_POWER_OFF                          0

#define PCB_DDR_POWER(x)                        {\
                                                    bDDRPOWER = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                             (MCU_FE19_PORT71_PIN_REG) // _156PIN_PIN_118_OFF_REGION

#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                         (MCU_FE25_PORT85_PIN_REG) // _156PIN_PIN_138

#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, (((DWORD)_PANEL_TYP_FRAME_RATE * 60) / 100));\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_FE26_PORT86_PIN_REG) // _156PIN_PIN_143

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_FE36_PORTA6_PIN_REG) // _156PIN_PIN_152

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_FE23_PORT83_PIN_REG) // _156PIN_PIN_135

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (P1_7) // _156PIN_PIN_50
#define bD0_DP_PIN16_CONNECT                    (P1_6) // _156PIN_PIN_49
#define bD0_DP_PIN17_CONNECT                    (P1_5) // _156PIN_PIN_48

#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))
#define bD2_CONNECT                             (MCU_FE31_PORTA1_PIN_REG) // _156PIN_PIN_150
#define bD3_CONNECT                             (MCU_FE30_PORTA0_PIN_REG) // _156PIN_PIN_149

#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D2_PIN()                            (bD2_CONNECT)
#define PCB_D3_PIN()                            (bD3_CONNECT)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                 (MCU_FE01_PORT41_PIN_REG) // _156PIN_PIN_67
#define bD2_HPD                                 (P1_1) // _156PIN_PIN_17
#define bD3_HPD                                 (P1_0) // _156PIN_PIN_4

#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0

#define _D2_HOT_PLUG_HIGH                       1
#define _D2_HOT_PLUG_LOW                        0

#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0

#define PCB_D0_HOTPLUG(x)                       {\
                                                    bD0_HPD = (x);\
                                                }

#define PCB_D2_HOTPLUG(x)                       {\
                                                    bD2_HPD = (x);\
                                                }

#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }

#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D2_HOTPLUG_DETECT()                 (bD2_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)


///////////////////
// Display Macro //
///////////////////

//--------------------------------------------------
// Macro of LVDS eDP Panel and eQC model Switch Control
//--------------------------------------------------
#define bDPTXSQC_GPU_SWICH                      (MCU_FE02_PORT42_PIN_REG) // _156PIN_PIN_68

#define _DPTX_PANEL_OUTPUT                      0
#define _EQC_FUNTION_OUTPUT                     1

#define PCB_SET_LVDS_DPTX_SWITCH(x)             {\
                                                    bDPTXSQC_GPU_SWICH = (x);\
                                                }


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                }

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_8BIT_PWM_DUTY(_BACKLIGHT_PWM))

#elif(_PWM_DUT_RESOLUTION == _PWM_12BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))

#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define bLED1                                   (MCU_FE2D_PORT95_PIN_REG) // _156PIN_PIN_148
#define bLED2                                   (P3_5) // _156PIN_PIN_62
#define bLED3                                   (P3_6) // _156PIN_PIN_63
#define bLED4                                   (MCU_FE13_PORT63_PIN_REG) // _156PIN_PIN_112_OFF_REGION
#define bLED5                                   (MCU_FE18_PORT70_PIN_REG) // _156PIN_PIN_117_OFF_REGION

#define _LED_ON                                 1
#define _LED_OFF                                0

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                    bLED3 = _LED_OFF;\
                                                    bLED4 = _LED_OFF;\
                                                    bLED5 = _LED_OFF;\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_OFF;\
                                                    bLED3 = _LED_OFF;\
                                                    bLED4 = _LED_OFF;\
                                                    bLED5 = _LED_OFF;\
                                                }

#define PCB_LED_IDLE()                          {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                    bLED3 = _LED_OFF;\
                                                    bLED4 = _LED_OFF;\
                                                    bLED5 = _LED_OFF;\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                    bLED3 = _LED_OFF;\
                                                    bLED4 = _LED_OFF;\
                                                    bLED5 = _LED_OFF;\
                                                }

#define PCB_LED_ON()                            {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_ON;\
                                                    bLED3 = _LED_ON;\
                                                    bLED4 = _LED_ON;\
                                                    bLED5 = _LED_ON;\
                                                }

#define PCB_LED_OFF()                           {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                    bLED3 = _LED_OFF;\
                                                    bLED4 = _LED_OFF;\
                                                    bLED5 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                    bLED1 = _LED_ON;\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_TYPE3()                         {\
                                                    bLED3 = _LED_ON;\
                                                }

#define PCB_LED_TYPE4()                         {\
                                                    bLED4 = _LED_ON;\
                                                }

#define PCB_LED_TYPE5()                         {\
                                                    bLED5 = _LED_ON;\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // _156PIN_PIN_65
#define AD_KEY2                                 (MCU_FF0A_ADC_A1_CONVERT_RESULT) // _156PIN_PIN_66

#define PCB_ADKEY1()                            (AD_KEY1)
#define PCB_ADKEY2()                            (AD_KEY2)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((ucV2) < 0x20)\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x40 <= (ucV2)) && ((ucV2) < 0x80))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0x90 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((ucV1) < 0x20)\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                    if((0x40 <= (ucV1)) && ((ucV1) < 0x80))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\
                                                    if((0x90 <= (ucV1)) && ((ucV1) < 0xE0))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                }

#endif // End of #if(_PCB_TYPE == _RL6449_QA_A_156PIN_2H1DP_eDP)
