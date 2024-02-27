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
// ID Code      : _RL6432_CANON_A_156PIN_1DUALDVI_LVDS.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6432_CANON_A_156PIN_1DUALDVI_LVDS)


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                               _XTAL14318K

///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#define _PCB_DEBUG_DDC                          _DDC1//_VGA_DDC

///////////////////////
// Input Port Config //
///////////////////////
//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_NO_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT
#define _D1_DDC_CHANNEL_SEL                     _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_DVI_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
//#define _D1_TMDS_BR_SWAP                         _OFF //      _ON//   
//#define _D1_TMDS_PN_SWAP                        _OFF //      _ON//

#define _D3_TMDS_BR_SWAP                        _ON//_OFF
#define _D3_TMDS_PN_SWAP                        _ON//_OFF


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
//#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                  _D3_INPUT_PORT
//#define _INPUT_PORT_SEARCH_PRI_1                  _A0_INPUT_PORT


////////////////////
// For LVDS Panel //
////////////////////

// !!!Only group C can be used for single LVDS
// MIRROR EX£º  0P 0N 1P 1N 2P 2N CP CN 3P 3N
//              3N 3P CN CP 2N 2P 1N 1P 0N 0P

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#if(_LVDS_OUTPUT_PORT == _LVDS_2_PORT)
#define _LVDS_PORT_SEL                          _LVDS_2_PORT_CD
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE//_DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE//_ENABLE//_ENABLE
#elif(_LVDS_OUTPUT_PORT == _LVDS_4_PORT)

#if(_LVDS_CABLE_TYPE == _LVDS_CABLE_TYPE_0)
#define _LVDS_PORT_SEL                          _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _ENABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#elif(_LVDS_CABLE_TYPE == _LVDS_CABLE_TYPE_1)
#define _LVDS_PORT_SEL                          _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                       _ENABLE
#define _LVDS_PORT_AB_SWAP                      _ENABLE
#define _LVDS_PORT_CD_SWAP                      _ENABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#endif

#elif(_LVDS_OUTPUT_PORT == _LVDS_1_PORT)
#define _LVDS_PORT_SEL                          _LVDS_1_PORT_C
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE

#endif

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                      _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL               _DISABLE
//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
//#define _LVDS_SPREAD_RANGE                      10
#define _LVDS_SPREAD_SPEED                      _SPEED_33K


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            0//5
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_12BIT

#define _BACKLIGHT_PWM                          _PWM5
#define _BACKLIGHT_PWM_INVERSE                  _ON

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _ON

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
#define _PWM1_RST_EN                            _OFF
#define _PWM2_RST_EN                            _OFF
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM5_RST_EN                            _ON
#define _PWM_RST_SIGNAL_SEL                     _DVS


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                         _ON//_OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _ON
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24WC64
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _HW_IIC_156PIN_77_78

//--------------------------------------------------
// External Device Sofware or Hardware IIC Bus Option[!!!HW BK Sensor use PIN_198_199]
//--------------------------------------------------
#define _PCB_SYS_EXTDEV_IIC0                    _SW_IIC_PIN_GPIO// ((_HW_IIC_SUPPORT == _ON) ? (_HW_IIC_156PIN_77_78) : _SW_IIC_PIN_GPIO)
#define _PCB_SYS_EXTDEV_IIC1                    _SW_IIC_PIN_GPIO//((_HW_IIC_SUPPORT == _ON) ? (_HW_IIC_156PIN_77_78) : _SW_IIC_PIN_GPIO)
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
#include "RL6432_CANON_A_156PIN_1DUALDVI_LVDS_PINSHARE.h"


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_SET_LVDS_DPTX_SWITCH(_DPTX_PANEL_OUTPUT);\
                                                }
#elif(_PANEL_STYLE == _PANEL_LVDS)
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_SET_LVDS_DPTX_SWITCH(_LVDS_PANEL_OUTPUT);\
                                                }
#endif

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
//#define bVCCKOFFPOWER                           (MCU_FE21_PORT81_PIN_REG) // 156PIN_PIN_68, P8.1
#define bVCCKOFFPOWER                           (MCU_FE20_PORT80_PIN_REG) // 156PIN_PIN_67, P8.0

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
//#define bPANELPOWER                             (MCU_FE45_PORTC5_PIN_REG) // 156PIN_PIN_43, PC.5
#define bPANELPOWER                             (MCU_FE1A_PORT72_PIN_REG) // 156PIN_PIN_63, P7.2

#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
//#define bBACKLIGHTPOWER                         (MCU_FE1F_PORT77_PIN_REG) // 156PIN_PIN_66, P7.7
#define bBACKLIGHTPOWER                         (MCU_FE1C_PORT74_PIN_REG) // 156PIN_PIN_64, P7.4

#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_SYSTEM_RUN_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, _PANEL_PWM_FREQUENCY);\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_SYSTEM_RUN_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_FE19_PORT71_PIN_REG) // 156PIN_PIN_61, P7.1

#define _FLASH_WRITE_PROTECT_ENABLE                1
#define _FLASH_WRITE_PROTECT_DISABLE               0

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_FE29_PORT91_PIN_REG) // 156PIN_PIN_76, P9.1

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     MCU_EMPTY_PIN_ASSIGN_ADDRESS//(MCU_FE21_PORT81_PIN_REG) // 156PIN_PIN_68, P8.1

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }
#define PCB_EDID_EEPROM_WRITE_PROTECT_DETECT()  (bEDID_WRITE_PROTECT)


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect  
// PIN15 DP_SINK_ASS_P PIN16 DP_CABLE_DET PIN17 DP_SINK_ASS_N 
// PCB_D1_PIN PIN15 PIN16 PIN17->DP Cable:0 0 1 1  DP No Cable:1 1 1 0
//-----------------------------------------------
#define bD3_CONNECT                             (P1_0)//(P1_0)//(MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(P1_0) // 156PIN_PIN_82, P1.0


#define PCB_D3_PIN()                            (bD3_CONNECT)


/////////////////////////
// Macro of Source Switch Control //
/////////////////////////

//#define bHDMI_DP_SWITCH                         (MCU_FE30_PORTA0_PIN_REG) // 156PIN_PIN_81, PA.0

//#define _DP_OUTPUT                              0
//#define _HDMI_OUTPUT                            1

//#define GET_PCB_HDMI_DP_SWITCH_DETECT()         (bHDMI_DP_SWITCH)

////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
//#define bD0_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE22_PORT82_PIN_REG) // 156PIN_PIN_70, P8.2
//#define bD1_HPD                                 (P1_0)//(P3_1)//(MCU_EMPTY_PIN_ASSIGN_ADDRESS) // 156PIN_PIN_84, P1.1
#define bD3_HPD                                 (P1_1)//(P1_1) // 156PIN_PIN_84, P1.1

#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0


#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }

//#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
//#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)



///////////////////
// Display Macro //
///////////////////

//--------------------------------------------------
// Macro of LVDS eDP Panel Switch Control
//--------------------------------------------------
//#define bLVDSDPTXSWICH                          (MCU_FE13_PORT63_PIN_REG) // 156PIN_PIN_48, P6.3
#define bLVDSDPTXSWICH                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE13_PORT63_PIN_REG) // 156PIN_PIN_48, P6.3

#define _LVDS_PANEL_OUTPUT                      0
#define _DPTX_PANEL_OUTPUT                      1

#define PCB_SET_LVDS_DPTX_SWITCH(x)             {\
                                                    bLVDSDPTXSWICH = (x);\
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
#define bLED1                                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)// (MCU_FE26_PORT86_PIN_REG)//156PIN_73,P8.6//(MCU_FE04_PORT44_PIN_REG) // 156PIN_PIN_151, P4.4
#define bLED2                                   MCU_FE1F_PORT77_PIN_REG//(MCU_FE26_PORT86_PIN_REG)//156PIN_74,P8.7 // 156PIN_PIN_152, P4.5

#define _LED_ON                                 1
#define _LED_OFF                                0

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_IDLE()                          {\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_ON()                            {\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_OFF()                           {\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                    bLED1 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE3()                         {\
                                                }

#define PCB_LED_TYPE4()                         {\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }

#if 0
#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_IDLE()                          {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_ON()                            {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_OFF()                           {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                    bLED1 = _LED_ON;\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_TYPE3()                         {\
                                                }

#define PCB_LED_TYPE4()                         {\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }

#endif
//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------

#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // 156PIN_PIN_143,A-ADC0
#define AD_KEY2                                 MCU_EMPTY_PIN_ASSIGN_ADDRESS//(MCU_FF0A_ADC_A1_CONVERT_RESULT) // 156PIN_PIN_144,A-ADC1

//#define BACKLIGHT_INC_PIN                       (MCU_FE05_PORT45_PIN_REG)

#define PCB_ADKEY1()                            (AD_KEY2)
#define PCB_ADKEY2()                            (AD_KEY1)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\                                                    
                                                    \
                                                }


//--------------------------------------------------
// Macro of GPIO Switch Contorl 
//--------------------------------------------------

#define TCA_RESET                               (MCU_FE25_PORT85_PIN_REG)
#define TCA_RESET_ON                            0
#define TCA_RESET_OFF                           1
#define TCA_RESET_CONTORL(x)                    {\
                                                    TCA_RESET = (x);\
                                                }
     
//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_FE2B_PORT93_PIN_REG) // _156PIN_PIN_77, P9.3
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_FE2E_PORT96_PIN_REG) // _156PIN_PIN_78, P9.6

//_IIC_SYS_BUS_I2C0: Backlight Sensor[!!!HW BK Sensor use PIN_198_199]
#define bSWIIC_SYS_BUS_I2C0_SCL                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)  // _PIN_198 P8.0
#define bSWIIC_SYS_BUS_I2C0_SDA                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)  // _PIN_199 P8.1

//_IIC_SYS_BUS_I2C1: Other Sensor
#define bSWIIC_SYS_BUS_I2C1_SCL                 (MCU_FE14_PORT64_PIN_REG)//(MCU_FE16_PORT66_PIN_REG)  // _PIN_179 P6.6
#define bSWIIC_SYS_BUS_I2C1_SDA                 (MCU_FE13_PORT63_PIN_REG)//(MCU_FE17_PORT67_PIN_REG)  // _PIN_180 P6.7

#define PCB_SW_IIC_SDA_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SDA = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SDA = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C0_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C1_SDA;\
                                                    }\
                                                }

#define PCB_SW_IIC_SCL_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SCL = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SCL = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C0_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C1_SCL;\
                                                    }\
                                                }

#endif // End of #if(_PCB_TYPE == _RL6432_CANON_A_156PIN_1DUALDVI_LVDS)

