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
// ID Code      : ScalerTconGlobalEnable.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerTconLibInternalInclude.h"

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
void ScalerTconGlobalEnable(bit bEnable);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set Tcon global control
// Input Value  : bEnable --> Tcon global enable
// Output Value : None
//--------------------------------------------------
void ScalerTconGlobalEnable(bit bEnable)
{
    if(bEnable == _ON)
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, ~(_BIT7 | _BIT2), (_BIT7 | _BIT2));
    }
    else
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, ~(_BIT7 | _BIT2), 0x00);
    }
}

