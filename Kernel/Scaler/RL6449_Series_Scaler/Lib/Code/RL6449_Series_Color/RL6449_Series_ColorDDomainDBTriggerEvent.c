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
// ID Code      : RL6449_Series_ColorDDomainDBTriggerEvent.c
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
void ScalerColorDDomainDBTriggerEvent(EnumDBTriggerEvent enumDBTriggerEvent);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set D domain double buffer trigger event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDDomainDBTriggerEvent(EnumDBTriggerEvent enumDBTriggerEvent)
{
    if(ScalerGlobalGetIDCode() >= _RL6449_VER_D_ID_CODE)
    {
        if(enumDBTriggerEvent == _DB_VS_TRIGGER)
        {
            // Set D-domain DB trigger source: DVS
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, 0x00);
        }
        else
        {
            // Set D-domain DB trigger source: DENA STOP
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);
        }
    }
}

