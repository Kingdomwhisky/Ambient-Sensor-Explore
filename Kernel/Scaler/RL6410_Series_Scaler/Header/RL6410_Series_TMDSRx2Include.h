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
// ID Code      : RL6410_Series_TMDSRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D2_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX2_PHY_SET()                          (g_stTMDSRx2CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX2_PHY_SET()                          (g_stTMDSRx2CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX2_PHY_SET()                          (g_stTMDSRx2CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX2_RGBHV_DETECTING()                  (g_stTMDSRx2CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX2_RGBHV_DETECTING()                  (g_stTMDSRx2CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX2_RGBHV_DETECTING()                  (g_stTMDSRx2CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX2_PACKET_DETECTING()                 (g_stTMDSRx2CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX2_PACKET_DETECTING()                 (g_stTMDSRx2CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX2_PACKET_DETECTING()                 (g_stTMDSRx2CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx2CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX2_GCP_RECEIVED()                     (g_stTMDSRx2CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX2_GCP_RECEIVED()                     (g_stTMDSRx2CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX2_GCP_RECEIVED()                     (g_stTMDSRx2CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of HDR Received Flag
//--------------------------------------------------
#if(_HDMI_HDR10_SUPPORT == _ON)
#define GET_HDMI_RX2_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx2CtrlInfo.b1HDRInfoFrameReceived)
#define SET_HDMI_RX2_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx2CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX2_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx2CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX2_Z0_ASSERTED()                      (g_stTMDSRx2CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX2_Z0_ASSERTED()                      (g_stTMDSRx2CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX2_Z0_ASSERTED()                      (g_stTMDSRx2CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX2_HPD_TRIGGER_EVENT()                (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX2_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX2_HPD_TRIGGER_EVENT()                (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#if(_D2_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx2CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx2CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx2CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX2_RR_ENABLE()                    (g_stTMDSRx2CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX2_RR_ENABLE()                    (g_stTMDSRx2CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX2_RR_ENABLE()                    (g_stTMDSRx2CtrlInfo.b1HDMI2RREnable = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 High Speed Mode
//--------------------------------------------------
#define GET_TMDS_RX2_HIGH_SPEED_MODE()                  (g_stTMDSRx2CtrlInfo.b1HDMI2HighSpeedMode)
#define SET_TMDS_RX2_HIGH_SPEED_MODE()                  (g_stTMDSRx2CtrlInfo.b1HDMI2HighSpeedMode = _TRUE)
#define CLR_TMDS_RX2_HIGH_SPEED_MODE()                  (g_stTMDSRx2CtrlInfo.b1HDMI2HighSpeedMode = _FALSE)
#endif

#define GET_TMDS_RX2_DDC_DETECTED()                     (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX2_DDC_DETECTED()                     (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX2_DDC_DETECTED()                     (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define GET_TMDS_RX2_CLK_MODE()                         (g_ucTMDSRx2ClkMode)
#define SET_TMDS_RX2_CLK_MODE(x)                        (g_ucTMDSRx2ClkMode = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx2CtrlInfo;
extern WORD g_usTMDSRx2ClkCount;

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
extern BYTE g_ucTMDSRx2ClkMode;
#endif

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)))
extern BYTE g_pucTmdsRx2Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx2Initial(void);
extern void ScalerTMDSRx2InterruptInitial(void);
extern void ScalerTMDSRx2IntHandler_EXINT0(void);
extern bit ScalerTMDSRx2CheckCDRStable(WORD usClkCount);
extern void ScalerTMDSRx2SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D2_HDMI_SUPPORT == _ON)

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern bit ScalerTMDSRx2HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)

extern void ScalerTMDSRx2HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx2HdmiAVMuteProc(void);
extern void ScalerTMDSRx2HdmiWatchDog(BYTE ucWDType, bit bEnable);
#endif

extern void ScalerTMDSRx2PowerSavingProc(void);
extern void ScalerTMDSRx2FreqDetectDisable(void);

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern BYTE ScalerTMDSRx2TMDSScanInputPort(BYTE ucInputType);
extern bit ScalerTMDSRx2HdcpEnabled(void);
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)

extern bit ScalerTMDSRx2CheckDataDFE(void);

extern bit ScalerTMDSRx2TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx2HotPlugEvent(void);
extern void ScalerTMDSRx2SwitchSlaveAddr(void);
extern void ScalerTMDSRx2BeforeHotPlugEventProc(void);
extern void ScalerTMDSRx2AfterHotPlugEventProc(void);
extern void ScalerTMDSRx2Hdcp1p4AksvClear(void);

#endif // End of #if(_D2_TMDS_SUPPORT == _ON)
