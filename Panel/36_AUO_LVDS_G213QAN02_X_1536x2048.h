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

#if(_PANEL_TYPE == _AUO_LVDS_G213QAN02_X_1536x2048)
//----------------------------------------------------------------------------------------------------
// ID Code      : _AUO_LVDS_G213QAN02_X_1536x2048.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Display Frame Sync Line Buffer Option
//--------------------------------------------------
#undef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT         _OFF

//--------------------------------------------------
//panel PWM Frequency(Unit: 1 Hz):   100Hz -200Hz -1K  Duty:5%~100%
//--------------------------------------------------
#define _PANEL_PWM_FREQUENCY                    600//360 

//--------------------------------------------------
// Define LVDS SSC Range
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                      0

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#define _LVDS_OUTPUT_PORT                       _LVDS_4_PORT
#define _LVDS_PANEL_SECTION                     _LVDS_PANEL_2_SECTION
#define _LVDS_TABLE_TYPE                        _LVDS_BIT_MAP_TABLE_2_4

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_INNOLUX

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_30_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         1536
#define _PANEL_DH_END                           1584

#define _PANEL_DH_TOTAL                         1792
#define _PANEL_DH_TOTAL_MAX                     1980
#define _PANEL_DH_TOTAL_MIN                     1636

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        2048
#define _PANEL_DV_END                           2054

#define _PANEL_DV_TOTAL                         2074
#define _PANEL_DV_TOTAL_MAX                     2088
#define _PANEL_DV_TOTAL_MIN                     2064

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      223
#define _PANEL_PIXEL_CLOCK_MAX                  227
#define _PANEL_PIXEL_CLOCK_MIN                  218


#define _PANEL_POWER_ON_T1                      30
#define _PANEL_POWER_ON_T2                      5
#define _PANEL_POWER_ON_T3                      450

#define _PANEL_POWER_OFF_T4                     200
#define _PANEL_POWER_OFF_T5                     20
#define _PANEL_POWER_OFF_T6                     1200


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 350)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ

//--------------------------------------------------
// Definitions for video compensation
//-------------------------------------------------
#define BYPASS_VIDEO_COMPENSATION(Vin, Vout)    ((Vin) == ((Vout) >> 1))


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////


//--------------------------------------------------
// Definitions for Display HDR
//--------------------------------------------------
#define _PANEL_MAX_LUMINANCE                    0x62 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x62 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool


/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _AUO_LVDS_G213QAN02_X_1536x2048)
