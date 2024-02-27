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
// ID Code      : BEA2014OsdPalette.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDPALETTE__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RGB_BLACK                                       0x00, 0x00, 0x00
#define _RGB_WHITE                                       0xFF, 0xFF, 0xFF
#define _RGB_WHITE_250                                   0xFA, 0xFA, 0xFA
#define _RGB_BLUE_120                                    0x98, 0xB7, 0xFF//0x00, 0x1E, 0x78
#define _RGB_GREEN_119                                   0x13, 0x77, 0x13
#define _RGB_BLUE                                        0x00, 0x00, 0xFF//0x00, 0x44, 0xA6
#define _RGB_YELLOW                                      0xFF, 0xFF, 0x00
#define _RGB_GRAY_32                                     0x20, 0x20, 0x20
#define _RGB_GRAY_80                        	         0x64, 0x64, 0x64//0x50, 0x50, 0x50 
#define _RGB_GRAY                                        0x80, 0x80, 0x80//0x60, 0x60, 0x60

#define _RGB_ORANGE                                      0xFF, 0xC4, 0x00
#define _RGB_LIGHTBLUE                                   0xD0, 0xD0, 0xD0
#define _RGB_SELECTBOTTOM                                0x3A, 0x46, 0x50
#define _RGB_PINK                                        0xFF, 0x80, 0xFF
#define _RGB_RED                                         0xFF, 0x00, 0x00
#define _RGB_ORANGE_DARK                                 0xE0, 0x78, 0x07
#define _RGB_ORANGE_H                                    0xFA, 0xB4, 0x28
#define _RGB_BLUE_200                                    0x00, 0x00, 0xC8


#define _LOGO_BLACK                                      0x00, 0x00, 0x00
#define _LOGO_WHITE                                      0xFF, 0xFF, 0xFF
#define _LOGO_RED                                        0xFF, 0x00, 0x00
#define _LOGO_GREEN                                      0x00, 0xFF, 0x00
#define _LOGO_BLUE                                       0x96, 0xB4, 0xFF // 0x00, 0xBE, 0xF0 // 0x00, 0x00, 0xFF 
#define _LOGO_YELLOW                                     0xFF, 0xFF, 0x00
#define _LOGO_GRAY                                       0x60, 0x60, 0x60
#define _LOGO_DARKBLUE                                   0x00, 0x00, 0x80//0x40, 0x40, 0xFF
#define _LOGO_LIGHTBLUE                                  0x80, 0x80, 0xFF
#define _LOGO_SELECTBOTTOM                               0x3A, 0x46, 0x50
#define _LOGO_PINK                                       0xFF, 0x80, 0xFF

#define _LOGO_ORANGE_H                                   0xFA, 0xB4, 0x28
#define _LOGO_ORANGE_L                                   0xEB, 0xA0, 0x05

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tPALETTE_RTD_LOGO[] =
{
    _LOGO_BLACK,
    _LOGO_DARKBLUE,
    _LOGO_WHITE,
    _LOGO_RED,
    _LOGO_GREEN,
    _LOGO_BLUE,
    _LOGO_YELLOW,
    _LOGO_GRAY,
    _LOGO_LIGHTBLUE,
    _LOGO_SELECTBOTTOM,
    _LOGO_PINK,
    _LOGO_RED,
    _LOGO_GREEN,
    _LOGO_ORANGE_L,
    _LOGO_ORANGE_H,
    _LOGO_GRAY,
};

BYTE code tPALETTE_DBI_LOGO[] =
{
    0xef,0xef,0xef,
    0x00,0x00,0x00,
    0x30,0x31,0x30,
    0x31,0x64,0xad,
    0xff,0xff,0xff,
    0x77,0x71,0x6d,
    0xb7,0xb3,0xb0,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

BYTE code tPALETTE_MEDBOT_LOGO[] =
{
    0xff,0xff,0xff,
    0x00,0x00,0x80,
    0x80,0x80,0x80,
    0xc0,0xc0,0xc0,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

BYTE code tPALETTE_MAIN_MENU[] =
{
	_RGB_BLACK,
	_RGB_WHITE,	
	_RGB_GRAY_32,
    _RGB_GRAY_80,
    _RGB_GRAY,
    _RGB_BLUE_120,
    _RGB_WHITE_250,
    _RGB_RED,
    _RGB_BLUE,
    _RGB_YELLOW,
    _RGB_GREEN_119,
    _RGB_ORANGE,
    _RGB_LIGHTBLUE,
    _RGB_PINK,
    _RGB_ORANGE_H,
    _RGB_BLUE_200,

};


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdPaletteLoadPigment(BYTE ucPaletteIndex, BYTE *pucColorPaletteArray);
void OsdPaletteSelectPalette(BYTE ucValue);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPaletteLoadPigment(BYTE ucPaletteIndex, BYTE *pucColorPaletteArray)
{
    BYTE ucAddr = ucPaletteIndex * 16;
    BYTE ucI = 0;

    for(ucI = 0; ucI < 16; ucI++)
    {
        ScalerOsdSetColorPalette(ucAddr + ucI, *(pucColorPaletteArray + (ucI * 3)), *(pucColorPaletteArray + (ucI * 3) + 1), *(pucColorPaletteArray + (ucI * 3) + 2));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPaletteSelectPalette(BYTE ucValue)
{
    switch(ucValue)
    {
        case _PALETTE_RTD_LOGO:
            OsdPaletteLoadPigment(_PALETTE_INDEX0, tPALETTE_RTD_LOGO);
            break;

        case _PALETTE_DBI_LOGO:
            OsdPaletteLoadPigment(_PALETTE_INDEX0, tPALETTE_DBI_LOGO);
            break;
            
        case _PALETTE_MEDBOT_LOGO:
            OsdPaletteLoadPigment(_PALETTE_INDEX0, tPALETTE_MEDBOT_LOGO);
            break;
            
        case _PALETTE_MAIN_MENU:
            OsdPaletteLoadPigment(_PALETTE_INDEX0, tPALETTE_MAIN_MENU);
            break;

        default:
            break;
    }
}

#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)