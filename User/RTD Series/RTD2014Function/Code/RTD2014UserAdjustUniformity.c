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
// ID Code      : RTD2014UserAdjustUniformity.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __USER_ADJUST_UNIFORMITY__

#include "UserCommonInclude.h"

#if(((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD)) && (_UNIFORMITY_SUPPORT == _ON))

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
void UserAdjustPanelUniformityMode(BYTE ucUniformity);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Auto Recognize Panel Uniformity Mode, and Load Corresponding Panel Uniformity LUT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustPanelUniformityMode(BYTE ucUniformity)
{
    EnumUniformityTypeSelect enumPanelUniformityType = 0;
    EnumUniformityModeSelect enumPanelUniformityMode = 0;
    BYTE ucUniformityCalibrationDataFlag = 0;
    BYTE ucUniformityTypeMaxNum;

    if(GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE)
    {
        enumPanelUniformityMode = _UNIFORMITY_OGC_MODE;
    }
#if(_OCC_SUPPORT == _ON)
    else
    {
        enumPanelUniformityMode = _UNIFORMITY_PCM_MODE;
    }
#endif

    switch(ucUniformity)
    {
        case _UNIFORMITY_OSD_TYPE1:
            enumPanelUniformityType = _UNIFORMITY_TYPE1;
            break;


        case _UNIFORMITY_OSD_TYPE2:
            enumPanelUniformityType = _UNIFORMITY_TYPE2;
            break;


        case _UNIFORMITY_OSD_TYPE3:
            enumPanelUniformityType = _UNIFORMITY_TYPE3;
            break;


        case _UNIFORMITY_OSD_TYPE4:
            enumPanelUniformityType = _UNIFORMITY_TYPE4;
            break;


        case _UNIFORMITY_OSD_TYPE5:
            enumPanelUniformityType = _UNIFORMITY_TYPE5;
            break;


        case _UNIFORMITY_OSD_TYPE6:
            enumPanelUniformityType = _UNIFORMITY_TYPE6;
            break;


        default:
            break;
    }


	// Beacon PanelUniformity Tool write data Flag
    UserCommonFlashRead(_UNIFORMITY_FLASH_BANK0, 0, 1, pData);
	ucUniformityCalibrationDataFlag = pData[0];

    // !!! must sync sizeof(tUniformityType)
    ucUniformityTypeMaxNum = 12; 

	//      1:All effects is one PanelUniformity
	// 2 or 3:One color temperature effect is one PanelUniformity.
	//  8~sizeof(tUniformityType):One Gamma effect is one PanelUniformity. [ 2 CT x 4 Gamma]
	if((ucUniformityCalibrationDataFlag < ucUniformityTypeMaxNum)&&(ucUniformityCalibrationDataFlag >= 1))
	{
		//SET_PANEL_UNIFORMITY_CALIBRATION_DATA(ucUniformityCalibrationDataFlag);
	}
	else
	{
		//SET_PANEL_UNIFORMITY_CALIBRATION_DATA(_FALSE);
	}
    //DebugMessageSystem("Uni Flag:", GET_PANEL_UNIFORMITY_CALIBRATION_DATA());

	//DebugMessageUart("Uni CT = ", GET_COLOR_TEMP_TYPE());
	if( ucUniformityCalibrationDataFlag == 1)
	{   
		enumPanelUniformityType = _UNIFORMITY_TYPE1;	
	}
	else if( ucUniformityCalibrationDataFlag == 2)
	{   
		if(GET_COLOR_TEMP_TYPE() < _CT_6500)
		{
			enumPanelUniformityType = _UNIFORMITY_TYPE1;
		}
		else
		{
			enumPanelUniformityType = _UNIFORMITY_TYPE2;
		}
	}
	else if( ucUniformityCalibrationDataFlag == 3)
	{   
		if(GET_COLOR_TEMP_TYPE() == _CT_9300)
		{
			enumPanelUniformityType = _UNIFORMITY_TYPE1;
		}
		else if(GET_COLOR_TEMP_TYPE() == _CT_7500)
		{
			enumPanelUniformityType = _UNIFORMITY_TYPE2;
		}
		else
		{
			enumPanelUniformityType = _UNIFORMITY_TYPE3;
		}
	}
	else if((ucUniformityCalibrationDataFlag < ucUniformityTypeMaxNum)&&(ucUniformityCalibrationDataFlag >= 8))
	{   
        BYTE ucNextCTIndex;

        // etc.  According to the actual curve combination settings. Two groups of color temperature, four groups of Gamma
        ucNextCTIndex = _GAMMA_AMOUNT;
        
        if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    	{
		    enumPanelUniformityType = GET_OSD_GAMMA() - 1;	
	    }
		else //  >= _CT_6500
		{
		    enumPanelUniformityType = ucNextCTIndex + GET_OSD_GAMMA() - 1;	
	    }
	}
	DebugMessageUart("Uni Type:", enumPanelUniformityType);
	DebugMessageUart("Uni Mode:", enumPanelUniformityMode);
    UserCommonAdjustPanelUniformity(enumPanelUniformityType, enumPanelUniformityMode);
}
#endif // End of #if(((_OSD_TYPE == _REALTEK_2014_OSD)||(_OSD_TYPE == _BEACON_2014_OSD)) && (_UNIFORMITY_SUPPORT == _ON))

