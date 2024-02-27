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
// ID Code      : SysMain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "SysInclude.h"

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


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void main(void);
void SysMainSystemInitial(void);
bit SysMainSytemPowerDetect(void);

#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
void SysMainStartUserCode(BYTE ucBankAddress);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : The main function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void main(void)
{
    do
    {
        SysMainSystemInitial();

        while(SysMainSytemPowerDetect() == _TRUE)
        {
            UserInterfaceKeyHandler();
            SysPowerHandler();
            SysJudgeHandler();

#if(_AUDIO_SUPPORT == _ON)
            SysAudioHandler();
#endif
            SysTimerHandler();
            SysSourceHandler();
            SysModeHandler();

#if(_MHL_SUPPORT == _ON)
            SysMHLMscHandler();
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCHandler();

#endif

#if(_DP_SUPPORT == _ON)
            SysDpRxHandler();
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
            SysTMDSRxHandler();

#if(_HDMI_CEC_SUPPORT == _ON)
            SysCecHandler();
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
            SysDpTxHandler();
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
            SysDpEmbeddedTxHandler();
#endif

#if(_DP_MST_SUPPORT == _ON)
            SysDpMstHandler();
#endif

#if(_HDMI_TX_SUPPORT == _ON)
            SysHdmiTxHandler();
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
            ScalerHdcp2Handler();
#endif

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
            ScalerBBHandler();
#endif

#if(_AUTO_TEST_SUPPORT == _ON)
            SysAutotestHandler();
#endif

            UserCommonInterfaceOsdHandler();

#if(_DDCCI_CODE_REDUCTION == _OFF)
            UserCommonDdcciHandler();
#endif
            SysColorHandler();
            ScalerDebug();
        }
    }
    while(_TRUE);
}

//--------------------------------------------------
// Description  : System AC on initial flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainSystemInitial(void)
{
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) &&\
    (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
    ScalerMcuBootInitial();

    SysMainStartUserCode(UserInterfaceGetUserCodeLocation());
#endif

    ScalerMcuInitial();

    ScalerPinshareInitial();

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)

    UserCommonSignExterMoveKey();

#elif(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL)

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
    UserCommonSignHandler();
    SysMainStartUserCode(UserCommonSignGetSwitchUserBank());
#elif(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
    UserCommonSignInterMoveKey();
#endif

#endif

    ScalerTimerInitialTimerEvent();

    UserCommonInterfaceInitial();

    ScalerMcuDdcRamEnable();

    SysSourceInitial();

    SysPowerInitial();

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    ScalerIRHWModeInitial();
#endif

    SET_POWER_STATUS(_POWER_STATUS_AC_ON);
    UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE,_OFF);
    UserCommonNVRamSetSystemData(_ONEKEY_PLUS_LUMINANCE_DISPLAY_MODE,_OFF);
    UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS,_ON);

    if(UserCommonNVRamGetSystemData(_MONITOR_POWER_STATUS) == _ON)
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
    }
    else
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
    }
    SET_MODE_STATE(_MODE_STATUS_POWER_OFF);
}

//--------------------------------------------------
// Description  : System power detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysMainSytemPowerDetect(void)
{
    return PCB_POWER_5V_DETECT();
}

#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
//--------------------------------------------------
// Description  : Switch bank and jump to user code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainStartUserCode(BYTE ucBankAddress)
{
#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
    // Set bank offset for user code
    SET_BANK_SWITCH_OFFSET(ucBankAddress);
#endif

    // Switch current bank
    MCU_FFFF_PBANK_SWITCH = ucBankAddress;

    // The below code is used here to ignore the pre-read code of mcu
    _nop_();
    _nop_();
    _nop_();
    _nop_();

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
    // Reset FW after switched to user code
    ((void (*)(void))0x0000)();
#endif
}
#endif

