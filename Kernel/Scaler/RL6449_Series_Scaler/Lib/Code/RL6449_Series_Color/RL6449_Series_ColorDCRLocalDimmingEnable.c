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
// ID Code      : RL6449_Series_ColorDCRLocalDimmingEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_ColorLibInternalInclude.h"

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
void ScalerColorDCRLocalDimmingEnable(EnumFunctionOnOFF enumOn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DCR Local Dimming Enable/Disable
// Input Value  : DCR Local Dimming Enable/Disable Option
// Output Value : none
//--------------------------------------------------
void ScalerColorDCRLocalDimmingEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, ~_BIT0, _BIT0);
        ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, ~_BIT0, 0x00);
    }
}