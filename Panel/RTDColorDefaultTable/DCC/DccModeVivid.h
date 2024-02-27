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
// ID Code      : DccModeVivid.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DCC MODE VIVID
//****************************************************************************
#if(_DCC_TABLE_TYPE == _DCC_GEN_0)

_DCC_CONTROL,
0x00,
_DCC_TABLE,
//control
0x04, 0x66, 0xc3,
0xb4, 0xff, 0x00,
0x10, 0x0c, 0x18,
//usercurve
0x09, 0x17, 0x28, 0x3c,
0x4e, 0x5f, 0x70, 0x84,
0x9a, 0xad, 0xbf, 0xcf,
0xdd, 0xec, 0xfa, 0xff,
0x10, 0x00, 0x00,
0x54, 0x14, 0x34, 0x23,
_DCC_END,

#elif(_DCC_TABLE_TYPE == _DCC_GEN_1)

_DCC_CONTROL,
0x10,
_DCC_TABLE,
//control
0x04, 0x44, 0xc3,
0xb4, 0xff, 0x00,
0x10, 0x0c, 0x18,
// control LSB 0x0017 ~ 0x001B
0x00, 0x00, 0x00, 0x00, 0x00,
//usercurve
0x07, 0x10, 0x1a, 0x26,
0x35, 0x49, 0x63, 0x80,
0x94, 0xa7, 0xb7, 0xc6,
0xd5, 0xe3, 0xf2, 0x00,
0x10, 0x00, 0x00,
0x50, 0x14, 0x34, 0x22,
// usercurve Add 0x011B ~ 0x0150
0x03, 0x80, 0x00, 0x0B, 0x80, 0x00,
0x15, 0x00, 0x00, 0x20, 0x00, 0x00,
0x2D, 0x80, 0x00, 0x3F, 0x00, 0x00,
0x56, 0x00, 0x00, 0x71, 0x80, 0x00,
0x8A, 0x00, 0x00, 0x9D, 0x80, 0x00,
0xAF, 0x00, 0x00, 0xBE, 0x80, 0x00,
0xCD, 0x80, 0x00, 0xDC, 0x00, 0x00,
0xEA, 0x80, 0x00, 0xF9, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
_DCC_END,

#endif
