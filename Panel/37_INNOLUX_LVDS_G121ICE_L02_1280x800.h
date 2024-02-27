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

#if(_PANEL_TYPE == _INNOLUX_LVDS_G121ICE_L02_1280x800)
//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Display Frame Sync Line Buffer Option
//--------------------------------------------------
#undef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT         _OFF
//--------------------------------------------------
// 2D / 3D panel type
//--------------------------------------------------
#define _PANEL_DISPLAY_TYPE                     _PANEL_DISPLAY_NORMAL  

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

#define _PANEL_PWM_FREQUENCY                    360 

//--------------------------------------------------
// Set Last Line Finetune Target (Must Be Larger than 4 Pixel!!)
//--------------------------------------------------
#define _LAST_LINE_TARGET                       400//(_PANEL_DH_TOTAL - 150)

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_INNOLUX          // _PANEL_CMO or _PANEL_AUO or _PANEL_SAMSUNG or _PANEL_INNOLUX or _PANEL_CPT

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS         // _PANEL_LVDS or _PANEL_RSDS or _PANEL_TTL
#define _LVDS_PANEL_SECTION                     _LVDS_PANEL_1_SECTION
#define _LVDS_TABLE_TYPE                        _LVDS_BIT_MAP_TABLE_1_3
#define _LVDS_OUTPUT_PORT                       _LVDS_1_PORT

//--------------------------------------------------
// Definitions for Panel Configuration
//--------------------------------------------------
//#define _DISP_OUTPUT_PORT                       _DISP_SINGLE_PORT   // _DISP_DOUBLE_PORT or _DISP_SINGLE_PORT
#define _PANEL_DISP_BIT_MODE                          _PANEL_DISP_24_BIT        // _DISP_30_BIT or _DISP_24_BIT or _DISP_18_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   630
#define _PANEL_MIN_FRAME_RATE                   570

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         32                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         1280                // Display Horizontal Width
#define _PANEL_DH_END                           (1280+32)          // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         1440                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     1500//1800                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     1360//1300                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        800                // Display Vertical Width
#define _PANEL_DV_END                           (800+6)                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         823                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     830//1000                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     810                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      71                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  75//120//80                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  67                 // Mininum Pixel Clock in MHz


#define _PANEL_POWER_ON_T1                      5//100                 // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      20//40                  // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      500//250                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     250//50//20                  // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     20//30//40                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     50//550                 // Panel Power Off T6 (ms)


//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
//#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 150)

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

#endif // End of #if(_PANEL_TYPE == _AU_LVDS_21_5_WUXGA)
