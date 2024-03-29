/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6463_Series_EfuseInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#ifndef __RL6463_SERIES_EFUSE_H__
#define __RL6463_SERIES_EFUSE_H__
//--------------------------------------------------
// Enumerations of Efuse Data State
//--------------------------------------------------
typedef enum
{
    _EFUSE_NONE,
    _EFUSE_LC_TANK_CURRENT,
    _EFUSE_M2PLL_N_F_CODE,
    _EFUSE_THERMAL_SENSOR,
    _EFUSE_LVDS_DRIV,
    _EFUSE_LC_TANK_FREQ_FOR_APLL,
    _EFUSE_CP_WAFER_INFO,
} EnumEfuseDataState;

#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerEfuseGetData(EnumEfuseDataState enumEfuseDataState, BYTE ucEfuseLength, BYTE *pucEfuseData);

