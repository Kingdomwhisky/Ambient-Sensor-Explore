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
// ID Code      : ScalerColorDigitalFilterNRingAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

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
void ScalerColorDigitalFilterNRingAdjust(BYTE ucTHD, BYTE ucDIV);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//-------------------------------------------------
// Description  : Set NRing
// Input Value  : THD,Div
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterNRingAdjust(BYTE ucTHD, BYTE ucDIV)
{
    // Set negative ring  parameter
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT6);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ((ucTHD << 4) | (ucDIV << 2) | _BIT7));
}
