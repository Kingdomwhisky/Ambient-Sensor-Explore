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
// ID Code      : RTD2014UserAdjustOutputGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_OUTPUT_GAMMA__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD))

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
#if(_GAMMA_FUNCTION == _ON)
void UserAdjustGamma(BYTE ucGamma);
#endif


//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
void UserAdjustPCM(BYTE ucPCM);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void UserAdjustGamma(BYTE ucGamma)
{
#if(_OGC_SUPPORT == _ON)
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;
#endif

#if ((_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)&&(_OSD_TYPE == _BEACON_2014_OSD))
    UserAdjustFPGAColorAdaptiveHandler(_ON);
#endif

#if((_OSD_TYPE == _BEACON_2014_OSD)&&(_BEACON_GAMMA_PCM_PARTITION_SUPPORT == _ON))
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#endif

   // DebugMessageUart("Adjust ucGamma:", ucGamma);

#if(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    // for Load gamma data index(!!!must sync Flash Addr) 
    if((ucGamma == _GAMMA_DICOM500)||(ucGamma == _GAMMA_DICOM550)||(ucGamma == _GAMMA_DICOM600))
        ucGamma = _GAMMA_DICOM300;  
    else if((ucGamma == _GAMMA_DICOM350)||(ucGamma == _GAMMA_DICOM400)||(ucGamma == _GAMMA_DICOM450))
        ucGamma = _GAMMA_DICOM250;  
    else if((ucGamma == _GAMMA_DICOM200)||(ucGamma == _GAMMA_DICOM250)||(ucGamma == _GAMMA_DICOM300))
        ucGamma = _GAMMA_DICOM200;  
    else 
        ucGamma = ucGamma; 
#else
    ucGamma = ucGamma; // for Load gamma data
#endif

    if(ucGamma != _GAMMA_OFF)
    {
#if(_OGC_SUPPORT == _ON)
        ucGammaBankNum = UserCommonAdjustOGCBank(ucGamma - 1, _OGC_NORMAL_TYPE);
        pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGamma - 1, _OGC_NORMAL_TYPE);

        UserCommonAdjustGamma(pucGammaBankAddr, ucGammaBankNum);

        RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#else

#if(_RGB_GAMMA_FUNCTION == _ON)
        ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif

        UserCommonAdjustGamma(tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());

#if(_RGB_GAMMA_FUNCTION == _ON)
        UserAdjustRGBGamma(ucGamma);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif

#endif // End of #if(_OGC_SUPPORT == _ON)
    }
}
#endif

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust PCM
// Input Value  : ucPCM
// Output Value : None
//--------------------------------------------------
void UserAdjustPCM(BYTE ucPCM)
{
    if(ucPCM != _PCM_OSD_NATIVE)
    {
#if((_OSD_TYPE == _BEACON_2014_OSD)&&(_BEACON_GAMMA_PCM_PARTITION_SUPPORT == _ON))
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
#endif

#if(_OCC_SUPPORT == _ON)
        {
        	BYTE ucPCMInputGamma;
            
            if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_18)
            {
                ucPCMInputGamma = _PCM_USER_DEFINE_2;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_19)
            {
                ucPCMInputGamma = _PCM_USER_DEFINE_3;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_20)
            {
                ucPCMInputGamma = _PCM_USER_DEFINE_4;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_21)
            {
                ucPCMInputGamma = _PCM_USER_DEFINE_5;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_22)
            {
                ucPCMInputGamma = _PCM_ADOBE_RGB; 
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_24)
            {
                ucPCMInputGamma = _PCM_REC_709;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_26)
            {
                ucPCMInputGamma = _PCM_DCI_P3;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_28)
            {
                ucPCMInputGamma = _PCM_USER_DEFINE_6;
            }
            else if(GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_30)
            {
                ucPCMInputGamma = _PCM_SOFT_PROFT;
            }
            else // (GET_OSD_PCM_INPUTGAMMA() == _PCM_INPUTGAMMA_NATIVE)
            {
                if(ucPCM == _PCM_OSD_SRGB)
                {
                    ucPCMInputGamma = _PCM_SRGB;
                }
                else if(ucPCM == _PCM_OSD_ADOBE_RGB)
                {
                    ucPCMInputGamma = _PCM_ADOBE_RGB;                
                }
                else
                {
                    ucPCMInputGamma = _PCM_ADOBE_RGB;
                }
            }

            // _OCC_USERDEFINE_ADDRESS : sRGB CT9300
            
            if(ucPCM == _PCM_OSD_SRGB)
            {
        		if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    {
                    UserCommonAdjustPCM(ucPCMInputGamma, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
                }
                else
                {
                    UserCommonAdjustPCM(ucPCMInputGamma, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
                }
            }
            else if(ucPCM == _PCM_OSD_ADOBE_RGB)
            {
        		if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    {
                    UserCommonAdjustPCM(ucPCMInputGamma, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
                }
                else
                {
                    UserCommonAdjustPCM(ucPCMInputGamma, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
                }
            }

#if(_RGB_3D_GAMMA == _ON)
            else if(ucPCM == _PCM_OSD_SOFT_PROFT)
            {
                UserCommonAdjustPCM(_PCM_SOFT_PROFT, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#endif // End of #if(_RGB_3D_GAMMA == _ON)

            else
#endif // End of #if(_OCC_SUPPORT == _ON)
            {
                //UserCommonAdjustPCM(_PCM_USER_MODE, tPCM_USER_TABLE[(ucPCM - _PCM_OSD_USER) * 3], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 1], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 2], GET_CURRENT_BANK_NUMBER(), _OCC_COLORMATRIX_TABLE_SIZE);
        		if(GET_COLOR_TEMP_TYPE() < _CT_6500)
                {
                    UserCommonAdjustPCM(ucPCMInputGamma, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
                }
                else
                {
                    UserCommonAdjustPCM(ucPCMInputGamma, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
                }
            }
        }
    }
}
#endif  // End of #if(_PCM_FUNCTION == _ON)
#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD))
