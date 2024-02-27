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

#if(_PANEL_TYPE == _INNOLUX_LVDS_G101ICE_L01)
//----------------------------------------------------------------------------------------------------
// ID Code      : _INNOLUX_LVDS_G101ICE_L01.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////


//--------------------------------------------------
//panel PWM Frequency(Unit: 1 Hz):   190Hz -200Hz -20K 
//--------------------------------------------------
#define _PANEL_PWM_FREQUENCY                    2000 

//--------------------------------------------------
// Define LVDS SSC Range
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                      5

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#define _LVDS_OUTPUT_PORT                       _LVDS_1_PORT
#define _LVDS_PANEL_SECTION                     _LVDS_PANEL_1_SECTION
#define _LVDS_TABLE_TYPE                        _LVDS_BIT_MAP_TABLE_1_3

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_AUO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

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
#define _PANEL_DH_WIDTH                         1280
#define _PANEL_DH_END                           1328

#define _PANEL_DH_TOTAL                         1440
#define _PANEL_DH_TOTAL_MAX                     1480
#define _PANEL_DH_TOTAL_MIN                     1376

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        800
#define _PANEL_DV_END                           806

#define _PANEL_DV_TOTAL                         823
#define _PANEL_DV_TOTAL_MAX                     829
#define _PANEL_DV_TOTAL_MIN                     810

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      71
#define _PANEL_PIXEL_CLOCK_MAX                  75
#define _PANEL_PIXEL_CLOCK_MIN                  62

#define _PANEL_POWER_ON_T1                      30
#define _PANEL_POWER_ON_T2                      20
#define _PANEL_POWER_ON_T3                      250

#define _PANEL_POWER_OFF_T4                     20
#define _PANEL_POWER_OFF_T5                     40
#define _PANEL_POWER_OFF_T6                     600


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 150)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ


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



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _INNOLUX_LVDS_G101ICE_L01)
