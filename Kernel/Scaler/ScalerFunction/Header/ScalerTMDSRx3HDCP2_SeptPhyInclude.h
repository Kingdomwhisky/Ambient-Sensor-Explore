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
// ID Code      : ScalerTMDSRx3HDCP2_SeptPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_TMDS_RX3_HDCP2_AKE_INIT_RECEIVED()                      (bit)(g_ucTmdsRx3Hdcp2Ctrl & _BIT7)
#define SET_TMDS_RX3_HDCP2_AKE_INIT_RECEIVED()                      (g_ucTmdsRx3Hdcp2Ctrl |= _BIT7)
#define CLR_TMDS_RX3_HDCP2_AKE_INIT_RECEIVED()                      (g_ucTmdsRx3Hdcp2Ctrl &= ~_BIT7)

#define GET_TMDS_RX3_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (bit)(g_ucTmdsRx3Hdcp2Ctrl & _BIT6)
#define SET_TMDS_RX3_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucTmdsRx3Hdcp2Ctrl |= _BIT6)
#define CLR_TMDS_RX3_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucTmdsRx3Hdcp2Ctrl &= ~_BIT6)

#define GET_TMDS_RX3_HDCP2_AKE_STORED_KM_RECEIVED()                 (bit)(g_ucTmdsRx3Hdcp2Ctrl & _BIT5)
#define SET_TMDS_RX3_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucTmdsRx3Hdcp2Ctrl |= _BIT5)
#define CLR_TMDS_RX3_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucTmdsRx3Hdcp2Ctrl &= ~_BIT5)

#define GET_TMDS_RX3_HDCP2_LC_INIT_RECEIVED()                       (bit)(g_ucTmdsRx3Hdcp2Ctrl & _BIT4)
#define SET_TMDS_RX3_HDCP2_LC_INIT_RECEIVED()                       (g_ucTmdsRx3Hdcp2Ctrl |= _BIT4)
#define CLR_TMDS_RX3_HDCP2_LC_INIT_RECEIVED()                       (g_ucTmdsRx3Hdcp2Ctrl &= ~_BIT4)

#define GET_TMDS_RX3_HDCP2_SKE_SEND_EKS_RECEIVED()                  (bit)(g_ucTmdsRx3Hdcp2Ctrl & _BIT3)
#define SET_TMDS_RX3_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucTmdsRx3Hdcp2Ctrl |= _BIT3)
#define CLR_TMDS_RX3_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucTmdsRx3Hdcp2Ctrl &= ~_BIT3)

#define GET_TMDS_RX3_HDCP2_AUTHENTICATION_DONE()                    (bit)(g_ucTmdsRx3Hdcp2Ctrl & _BIT2)
#define SET_TMDS_RX3_HDCP2_AUTHENTICATION_DONE()                    (g_ucTmdsRx3Hdcp2Ctrl |= _BIT2)
#define CLR_TMDS_RX3_HDCP2_AUTHENTICATION_DONE()                    (g_ucTmdsRx3Hdcp2Ctrl &= ~_BIT2)

#define SET_TMDS_RX3_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive |= _BIT3)
#define CLR_TMDS_RX3_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive &= ~_BIT3)

//--------------------------------------------------
// Macro of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_TMDS_RX3_HDCP2_AUTH_STATE()                             (g_stTmdsRx3Hdcp2AuthInfo.b4AuthState)
#define SET_TMDS_RX3_HDCP2_AUTH_STATE(x)                            (g_stTmdsRx3Hdcp2AuthInfo.b4AuthState = (x))

#define GET_TMDS_RX3_HDCP2_MODE()                                   (ScalerGetBit(P2E_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
extern BYTE g_ucTmdsRx3Hdcp2Ctrl;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
extern void ScalerTMDSRx3Hdcp2AesOnlineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerTMDSRx3Hdcp2DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerTMDSRx3Hdcp2Enable_EXINT0(void);
extern void ScalerTMDSRx3Hdcp2Handler(void);
extern void ScalerTMDSRx3Hdcp2Initial(void);
extern void ScalerTMDSRx3Hdcp2IntHandler_EXINT0(void);
extern void ScalerTMDSRx3Hdcp2ReAuthEvent(void);
extern void ScalerTMDSRx3Hdcp2ResetProc(void);
extern void ScalerTMDSRx3Hdcp2ResetProc_EXINT0(void);
extern void ScalerTMDSRx3Hdcp2SetRdMsgIDCode_EXINT0(BYTE ucValue);
extern void ScalerTMDSRx3Hdcp2SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
extern void ScalerTMDSRx3Hdcp2AesOnlineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerTMDSRx3Hdcp2SetRdMsgIDCode(BYTE ucValue);
extern void ScalerTMDSRx3Hdcp2SetRdMsgValue(WORD usAddress, BYTE *pucReadArray, WORD usLength);
#endif

#endif
#endif

