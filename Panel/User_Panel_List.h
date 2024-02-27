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
// ID Code      : User_Panel_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Panel Type List
//--------------------------------------------------
#define _PANEL_LVDS_EXAMPLE                     0x01
#define _PANEL_DPTX_EXAMPLE                     0x02
#define _PANEL_VBO_EXAMPLE                      0x03
#define _PANEL_TTL_EXAMPLE                      0x04

#define _MULTIPANEL_LVDS_21_5_WUXGA             0x10
#define _CMO_LVDS_17                            0x11    // 1280 x 1024
#define _CMO_LVDS_19_WXGA                       0x12    // 1440 x  900
#define _AU_LVDS_22_WSXGA                       0x13    // 1680 x 1050
#define _AU_LVDS_22_WSXGA_QC                    0x14    // 1680 x 1050
#define _AU_LVDS_21_5_WUXGA                     0x15    // 1920 x 1080
#define _AU_LVDS_21_5_WUXGA_FREESYNC            0x16    // 1920 x 1080
#define _AU_LVDS_23_WUXGA                       0x17    // 1920 x 1200 
#define _AU_LVDS_24_WUXGA                       0x18    // 1920 x 1080
#define _AU_LVDS_27_WUXGA_FREESYNC              0x19    // 1920 x 1080
#define _LG_LED_LVDS_27_WUXGA                   0x1A    // 2560 x 1440
#define _LG_LED_LVDS_23_UHD                     0x1B    // 3840 x 2160
#define _INNOLUX_LVDS_G101ICE_L01               0x1C    // 1280 x 800
#define _INNOLUX_LVDS_R213TCE_LU2_2560x2048     0x1D    // 2560 x 2048  QSXGA
#define _INNOLUX_LVDS_R213TCE_LU1_2560x2048     0x1E    // 2560 x 2048  QSXGA
#define _INNOLUX_LVDS_R213RCE_LU1_1536x2048     0x1F    // 1536 x 2048  QXGA
#define _AUO_LVDS_G213QAN02_X_1536x2048         0x20    // 1536 x 2048  QXGA
#define _INNOLUX_LVDS_G121ICE_L02_1280x800      0x21    // 1280 x 800
#define _BOE_EV156FHM_N80_1920x1080             0x22    // 1920 x 1080
#define _BOE_LVDS_EV213QXM_N10_1536x2048        0x23    // 1536 x 2048  QXGA
#define _INNOLUX_LVDS_R213RCE_LU2_1536x2048     0x24    // 1536 x 2048  gray

#define _MULTIPANEL_DP_21_5_WUXGA               0x30
#define _AU_DP_21_5_WUXGA                       0x31    // 1920 x 1080
#define _AU_DP_21_5_WUXGA_FREESYNC              0x32    // 1920 x 1080
#define _LG_LED_DP_34_WFHD                      0x33    // 2560 x 1080
#define _LG_LED_DP_17_QHD                       0x34    // 2560 x 1440
#define _LG_LED_DP_27_QHD                       0x35    // 2560 x 1440
#define _LG_LED_DP_27_QHD_QC                    0x36    // 2560 x 1440
#define _SAMSUNG_LED_DP_15_6_UHD                0x37    // 3840 x 2160
#define _SAMSUNG_LED_DP_23_6_UHD                0x38    // 3840 x 2160
#define _LG_LED_DP_27_UHD                       0x39    // 3840 x 2160
#define _AUO_LED_DP_32_UHD                      0x3A    // 3840 x 2160
#define _LG_LED_DP_27_QQHD                      0x3B    // 5120 x 2880
#define _AUO_EDP_27_UHD_LOCAL_DIMMING           0x3C    // 3840 x 2160

#define _AUO_VBO_27_WUXGA_FREESYNC              0x51    // 1920 x 1080
#define _AUO_VBO_M250HTN01_0                    0x52    // 1920 x 1080 240Hz
#define _INNOLUX_LED_VBO_28_UHD                 0x53    // 3840 x 2160
#define _INNOLUX_LED_VBO_40_UHD                 0x54    // 3840 x 2160

#define _INNOLUX_TTL_7                          0x71    // 800 x  480

//--------------------------------------------------
// Panel Led Driver List (Can Not Be 0xFF)
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_01_O2_OZ9913         0x01
#define _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820    0x02
#define _DEVICE_LED_DRIVER_03_AUSTRIA_AS3824    0x03
