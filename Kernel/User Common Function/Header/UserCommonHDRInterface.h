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
// ID Code      : UserCommonHDRInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_HDR10_SUPPORT == _ON)
extern StructHDR10Setting g_stHDR10Setting;
extern StructHDR10PortSettingInfo g_stHDR10PortSettingInfo;
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
extern StructFreeSyncIIInfo g_stFreeSyncIISetting;
extern bit UserCommonHDRGetFreeSyncIILDDisable(void);
extern BYTE UserCommonHDRGetFreeSyncIIEOTFType(void);
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
