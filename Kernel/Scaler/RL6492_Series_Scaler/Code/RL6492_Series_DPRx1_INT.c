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
// ID Code      : RL6492_Series_DPRx1_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_DPRX1_INT__

#include "ScalerFunctionInclude.h"

#if(_D1_DP_EXIST == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx1IntHandler_EXINT0(void);
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx1Tp2SetPhy_EXINT0(void);
void ScalerDpRx1AdjustLaneFLDBand_EXINT0(WORD usVCOBandDiff);
void ScalerDpRx1SetDFEInitial_EXINT0(void);
BYTE ScalerDpRx1DFECheck_EXINT0(void);
BYTE ScalerDpRx1SignalCheck_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1RebuildPhy_WDINT(BYTE ucDpLinkRate, BYTE ucDpcdLane);
#endif

BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx1TrainingPatternEnd_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
BYTE ScalerDpRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE ScalerDpRx1GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
#endif
#endif

BYTE ScalerDpRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1IntHandler_EXINT0(void) using 1
{
    // Aux Firmware Control -> Reply Defer
    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

    g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
    g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
    g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

    // DP Global IRQ Flag
    if(ScalerGetBit_EXINT(PBA_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        // Fifo overflow/ underflow IRQ & flag
        if((ScalerGetBit_EXINT(PB6_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PB5_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00))
        {
            // Disable fifo overflwo/ underflwo IRQ
            ScalerSetBit_EXINT(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

            // Set free run & force to BG
            ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);

#if(_AUDIO_SUPPORT == _ON)
            // Disable Audio Channel
            ScalerAudioDpAudioEnable_EXINT0(_DISABLE, _D1_INPUT_PORT);
#endif

            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Set DP Receive Port0 Out of Sync
            ScalerDpRx1SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

            // The Judge Handler take much time, It lead to MacBook 720P @50 <---> @60 Timing changing Issue
            if((ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
               ((ScalerDpRx1DFECheck_EXINT0() == _FALSE) && (ScalerDpRx1SignalCheck_EXINT0() == _FALSE)))
            {
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, 0x00);
            }

#if((_DP_TX_SUPPORT == _ON) || (_EMBEDDED_DP_TX_SUPPORT == _ON))
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Set DPTx Force Output Idle Pattern
                ScalerDpTxForceIdlePattern_EXINT0();
            }
#endif
        }

        // LLCTS 7.2.1.3 Sink Status
        if((ScalerGetBit_EXINT(PB6_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(PB6_36_DP_GLB_STATUS, _BIT6) == _BIT6))
        {
            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Clear VB-ID[3] Change Flag
            ScalerSetBit_EXINT(PB6_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

            if(ScalerGetBit_EXINT(PB6_01_DP_VBID, _BIT3) == _BIT3)
            {
                // Set DP Receive Port0 Out of Sync
                ScalerDpRx1SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
            }
        }

        if(ScalerGetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, _BIT0) == _BIT0) // Write 00600h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~_BIT0, _BIT0);

            if((ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
               (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                // DP Power Down
                SET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();

                g_pucDpRx1LinkStatusBackup_INT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x02);
                g_pucDpRx1LinkStatusBackup_INT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x03);
                g_pucDpRx1LinkStatusBackup_INT[2] = ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x04, _BIT0);

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), _BIT7);
            }
            else if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
            {
                // DP Power Normal
                if(GET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_pucDpRx1LinkStatusBackup_INT[0]);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_pucDpRx1LinkStatusBackup_INT[1]);
                    ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), (_BIT7 | g_pucDpRx1LinkStatusBackup_INT[2]));
                }

                CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();
                g_pucDpRx1LinkStatusBackup_INT[0] = 0x00;
                g_pucDpRx1LinkStatusBackup_INT[1] = 0x00;
                g_pucDpRx1LinkStatusBackup_INT[2] = 0x00;
            }
        }

        if(ScalerGetBit_EXINT(PBA_DA_AUX_FIFO_RST, (_BIT2 | _BIT1)) == (_BIT2 | _BIT1)) // Write 68xxxh into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Clear Integrity Failure Flag
            ScalerSetBit_EXINT(PB_1B_HDCP_INTGT_VRF, ~_BIT1, _BIT1);

            if(GET_DP_RX1_FAKE_LINK_TRAINING() == _TRUE)
            {
                // DP Mac Clock Select to Xtal Clock
                ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);
            }
        }

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
        // DPCD 68028h Into INT
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            ScalerDpRx1HdcpHandshakeMonitorDisable_EXINT0();

            // Check if source doing HDCP handshake while HDCP capability disable
            if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x06, 0x80, 0x28, _BIT0) == 0x00)
            {
                SET_DP_RX1_HDCP_HANDSHAKE_WO_CAP();
            }
        }
#endif
        // Detect if Aksv(0x6800B) is Written by Source
        if(ScalerGetBit_EXINT(PBA_A5_AUX_RESERVE5, (_BIT6 | _BIT2)) == (_BIT6 | _BIT2))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Switch HDCP to 1.4 Module from 2.2 Module as receiving AKsv
            if(GET_DP_RX1_HDCP_MODE_EXINT() == _HDCP_22)
            {
                // Select to HDCP 1.4 Module
                SET_DP_RX1_HDCP_MODE_EXINT(_HDCP_14);

                // Calculate R0' by manual toggle HDCP 1.4 Module
                ScalerSetBit_EXINT(PB_63_HDCP_OTHER, ~_BIT7, _BIT7);
                ScalerSetBit_EXINT(PB_63_HDCP_OTHER, ~_BIT7, 0x00);
            }

#if(_WD_TIMER_INT_SUPPORT == _ON)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
            ScalerDpRx1HdcpHandshakeMonitorDisable_EXINT0();

            // Check if source doing HDCP handshake while HDCP capability disable
            if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x06, 0x80, 0x28, _BIT0) == 0x00)
            {
                SET_DP_RX1_HDCP_HANDSHAKE_WO_CAP();
            }
#endif
        }

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_HDCP_ARBITER_SUPPORT == _ON))
        // DPCD 6921Xh Into INT
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);

            ScalerDpRx1HdcpHandshakeMonitorDisable_EXINT0();

            // Check if source doing HDCP handshake while HDCP capability disable
            if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x06, 0x92, 0x1F, _BIT1) == 0x00)
            {
                SET_DP_RX1_HDCP_HANDSHAKE_WO_CAP();
            }
        }
#endif

        if(ScalerGetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, _BIT2) == _BIT2) // Write 00270h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~_BIT2, _BIT2);

            if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT0) == _BIT0)
            {
                SET_DP_RX1_CRC_CALCULATE();
            }

            // Clear TEST_CRC_COUNT
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x46, 0x20);
        }

#if(_AUDIO_SUPPORT == _ON)
        // Detect if Auido Sampling is Changed
        if(ScalerGetBit_EXINT(PB6_50_AUD_FREQUENY_DET_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
        {
            // Clear Auido Sampling Change Flag
            ScalerSetBit_EXINT(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

#if(_LINE_IN_SUPPORT == _ON)
            if(ScalerAudioGetInputSource_EXINT0() == _DIGITAL_AUDIO)
#endif
            {
                // Disable Boundary Tracking Method
                ScalerSetBit_EXINT(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

                // Disable Trend Tracking Method
                ScalerSetBit_EXINT(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

                // Reload D code
                ScalerSetBit_EXINT(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
            }
        }
#endif
    }

    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    BYTE ucD1Z0Status = 0;
    BYTE ucD2Z0Status = 0;


    ////////////////////
    // Mode Select DP //
    ////////////////////

    // Backup Z0 Status
    ucD1Z0Status = ScalerGetBit_EXINT(P1D_17_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ucD2Z0Status = ScalerGetBit_EXINT(P1D_19_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable Z0
    ScalerSetBit_EXINT(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [5] dp_mode = 1'b1 --> Select DP Mode
    ScalerSetBit_EXINT(P1D_16_BANDGAP_02, ~_BIT5, _BIT5);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit_EXINT(P1D_15_BANDGAP_01, ~_BIT4, 0x00);

    // Restore Z0 Status
    ScalerSetBit_EXINT(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD1Z0Status);
    ScalerSetBit_EXINT(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD2Z0Status);


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D1_DP_LANE3 << 6);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D1_DP_LANE2 << 4);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D1_DP_LANE1 << 2);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX1_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX1_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX1_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX1_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Lane3 CMU Disable
    ScalerSetBit_EXINT(P1D_21_CMU_04, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte_EXINT(P1D_20_CMU_03, 0x00);

    // Enable RX_EN
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] MAC One Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
            ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), GET_DP_RX1_PCB_LANE0_MAPPING() << 2);

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT2, _BIT2);
            }

            break;

        case _DP_TWO_LANE:

            // [4:3] MAC Two Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            if((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) || (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3))
            {
                // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
                ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            }
            else
            {
                // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
                ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), GET_DP_RX1_PCB_LANE0_MAPPING() << 2);
            }

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT2, _BIT2);
            }

            if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT2, _BIT2);
            }

            break;

        case _DP_FOUR_LANE:
        default:

            // [4:3] MAC Four Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
            ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Enable Lane0/1/2 CDR_EN for DCDR
            ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;
    }

    // Enable Lane3 CDR_EN for BBPD
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~_BIT3, _BIT3);

    // ln_clk_func_sel[1:0] --> MAC Clock from Analog CDR Lane
    ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), (ScalerGetBit_EXINT(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // Delay Time us [25,x]
    DELAY_25US_EXINT();

    // Enable Analog CDR and FLD
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));


    ///////////////////////
    // Frequency Setting //
    ///////////////////////


    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR:

            g_usDpRx1ClockTargetCount = 0x1388; // ideal 2.7G

            // [2:0] rate_sel = 3'b001 --> 1.75~3.5Gbps
            ScalerSetBit_EXINT(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // [1:0] SEL_DIV = 2'b00 --> 1.75~3.5Gbps
            ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT1 | _BIT0), 0x00);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [6] reg_xtal_en = 1'b1 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~_BIT6, _BIT6);

                // 25/500 = 1/20 = 5*(27M/2.7G)
                // ref_conuter = 24
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x18);

                // cdr_counter = 499
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xF3);
            }
            else
            {
                // [6] xtal_en = 1'b1 --> D10.2 clock
                ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~_BIT6, 0x00);

                // 125/500 = 1/4 = 5*(135M/2.7G)
                // ref_conuter = 124
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x7C);

                // cdr_counter = 499
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xF3);
            }

            break;

        case _DP_LINK_RBR:
        default:

            g_usDpRx1ClockTargetCount = 0xBB8; // ideal 1.62G

            // [2:0] rate_sel = 3'b001 --> 875M~1.75Gbps
            ScalerSetBit_EXINT(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [1:0] SEL_DIV = 2'b00 --> 875M~1.75Gbps
            ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT1 | _BIT0), _BIT0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [6] reg_xtal_en = 1'b1 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~_BIT6, _BIT6);

                // 20/480 = 1/24 = 5*(27M/3.24G)
                // ref_conuter = 19
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x13);

                // cdr_counter = 479
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xDF);
            }
            else
            {
                // [6] xtal_en = 1'b1 --> D10.2 clock
                ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~_BIT6, 0x00);

                // 60/480 = 1/8 = 5*(81M/3.24G)
                // ref_conuter = 59
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x3B);

                // cdr_counter = 479
                ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xDF);
            }

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // Disable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [1] bypass_clk_rdy = 1'b1 --> Clk Rdy Signal in Manual Mode
    // [0] en_clkout_manual = 1'b1 --> Enable Clkout
    ScalerSetBit_EXINT(P1D_0E_SDM_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_eqen_rdy = 1'b1 --> EQEN Rdy Signal in Manual Mode
    // [0] en_eqen_manual = 1'b1 --> Enable EQ
    ScalerSetBit_EXINT(P1D_10_EQEN_TIMER, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_data_rdy = 1'b1 --> Data Rdy Signal in Manual Mode
    // [0] en_data_manual = 1'b0 --> Disable Dataout
    ScalerSetBit_EXINT(P1D_11_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [3] reg_en_data_manual_l3 = 1'b0 --> Disable Data Ready
    // [2] reg_bypass_data_rdy_l3 = 1'b1 --> Data Ready Signal in Manual Mode
    // [1] reg_en_eqen_manual_l3 = 1'b1 --> Enable EQ
    // [0] reg_bypass_eqen_rdy_l3 = 1'b1 --> EQ Ready Signal in Manual Mode
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Digital Circuit Reset Toggle
    ScalerSetByte_EXINT(P1D_38_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P1D_38_TMDS_RESET, 0xF0);

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            break;

        case _DP_TWO_LANE:

            // [3] cdr_rst_n_lane0 = CDR_EN[0]
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT3, (ScalerGetBit_EXINT(P1D_20_CMU_03, _BIT0) << 3));

            // [2] cdr_rst_n_lane1 = CDR_EN[1]
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT2, (ScalerGetBit_EXINT(P1D_20_CMU_03, _BIT1) << 1));

            // [1] cdr_rst_n_lane2 = CDR_EN[2]
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT1, (ScalerGetBit_EXINT(P1D_20_CMU_03, _BIT2) >> 1));

            if((GET_DP_RX1_PCB_LANE0_MAPPING() != _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() != _DP_SCALER_LANE3))
            {
                if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
                {
                    // [3] cdr_rst_n_lane0 = 0 --> Disable DCDR Lane0
                    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT3, 0x00);
                }
                else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
                {
                    // [2] cdr_rst_n_lane1 = 0 --> Disable DCDR Lane1
                    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT2, 0x00);
                }
                else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
                {
                    // [1] cdr_rst_n_lane2 = 0 --> Disable DCDR Lane2
                    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT1, 0x00);
                }
            }

            break;

        case _DP_FOUR_LANE:
        default:

            // [3:0] cdr_rst_n_lane0~3 = 4'b1110
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;
    }


    /////////////////
    // CDR Setting //
    /////////////////

    // [6:4] sel_cdr_res = 3'b110 --> 8K Ohm
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR:

            // [3:0] cdr_cp_in = 4'b0101 --> (1nF)16.5uA
            ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Lane0~2 KP = 4
            ScalerSetByte_EXINT(P1D_56_CDR_07, 0x10);
            ScalerSetByte_EXINT(P1D_57_CDR_08, 0x10);
            ScalerSetByte_EXINT(P1D_58_CDR_09, 0x10);

            break;

        case _DP_LINK_RBR:
        default:

            // [3:0] cdr_cp_in = 4'b0110 --> (1nF)19.5uA
            ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Lane0~2 KP = 8
            ScalerSetByte_EXINT(P1D_56_CDR_07, 0x20);
            ScalerSetByte_EXINT(P1D_57_CDR_08, 0x20);
            ScalerSetByte_EXINT(P1D_58_CDR_09, 0x20);

            break;
    }


    ////////////////
    // EQ Setting //
    ////////////////

    // [4:0] reg_fore_off_adjr_Lane0~3 = 5'b10000
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit_EXINT(P1D_2B_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit_EXINT(P1D_2C_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit_EXINT(P1D_2D_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR:

            // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
            ScalerSetBit_EXINT(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
            ScalerSetBit_EXINT(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
            ScalerSetBit_EXINT(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            break;

        case _DP_LINK_RBR:
        default:

            // [7] le_lowgain_highboost = 1'b0 --> Enable LE High-boost Mode
            ScalerSetBit_EXINT(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
            ScalerSetBit_EXINT(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
            ScalerSetBit_EXINT(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            break;
    }

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial_EXINT0();

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground offset calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground Offset Calibration Auto Mode
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS_EXINT(85);


    ///////////////////
    // FLD Auto Mode //
    ///////////////////

    // Set FLD Auto Mode
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~_BIT7, _BIT7);

    // [2] cp_en_manual = 1'b0 --> CDR Open Loop
    // [1] adp_en_manual = 1'b0 --> Disable CDR Clock
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~(_BIT2 | _BIT1), 0x00);

    // [7] rstb_fld --> Reset Timer of Analog CDR
    // [6] rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Delay Time us [150,x]
    DELAY_XUS_EXINT(150);

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit_EXINT(P1D_11_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] xclk_sel = 1'b0 --> Keep Link Clock from Analog
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    /////////////////////////
    // D10.2 Clock Measure //
    /////////////////////////

    // [5] ln_ck_sel = 1'b0 -> DP Raw Data
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL(27M) Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit_EXINT(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_usDpRx1ClockTargetCount = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));
    }
    else
    {
        switch(g_ucDpRx1LinkRate)
        {
            case _DP_LINK_HBR:

                g_usDpRx1ClockTargetCount = 0x1270;

                break;

            default:
            case _DP_LINK_RBR:

                g_usDpRx1ClockTargetCount = 0xB10;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp2SetPhy_EXINT0(void) using 1
{
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE ucIcp = (ScalerGetByte_EXINT(P1D_31_ANA_CDR_03) & 0x0F);

    // Enable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(P1D_11_DATA_TIMER, ~_BIT0, 0x00);

    // [3] reg_en_data_manual_l3 = 1'b0 --> Disable Data Ready
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, 0x00);

    // Digital Circuit Reset Toggle
    ScalerSetByte_EXINT(P1D_38_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P1D_38_TMDS_RESET, 0xF0);

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            break;

        case _DP_TWO_LANE:

            // [3] cdr_rst_n_lane0 = CDR_EN[0]
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT3, (ScalerGetBit_EXINT(P1D_20_CMU_03, _BIT0) << 3));

            // [2] cdr_rst_n_lane1 = CDR_EN[1]
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT2, (ScalerGetBit_EXINT(P1D_20_CMU_03, _BIT1) << 1));

            // [1] cdr_rst_n_lane2 = CDR_EN[2]
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT1, (ScalerGetBit_EXINT(P1D_20_CMU_03, _BIT2) >> 1));

            if((GET_DP_RX1_PCB_LANE0_MAPPING() != _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() != _DP_SCALER_LANE3))
            {
                if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
                {
                    // [3] cdr_rst_n_lane0 = 0 --> Disable DCDR Lane0
                    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT3, 0x00);
                }
                else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
                {
                    // [2] cdr_rst_n_lane1 = 0 --> Disable DCDR Lane1
                    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT2, 0x00);
                }
                else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
                {
                    // [1] cdr_rst_n_lane2 = 0 --> Disable DCDR Lane2
                    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~_BIT1, 0x00);
                }
            }

            break;

        case _DP_FOUR_LANE:
        default:

            // [3:0] cdr_rst_n_lane0~3 = 4'b1110
            ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;
    }


    ///////////////////
    // FLD Auto Mode //
    ///////////////////

    if(ScalerGetBit_EXINT(P1D_30_ANA_CDR_02, _BIT6) == _BIT6) // Using 28.6M Xtal
    {
        // Set FLD Auto Mode
        ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~_BIT7, _BIT7);

        // [2] cp_en_manual = 1'b0 --> CDR Open Loop
        // [1] adp_en_manual = 1'b0 --> Disable CDR Clock
        ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~(_BIT2 | _BIT1), 0x00);

        // [7] rstb_fld --> Reset Timer of Analog CDR
        // [6] rstb_fsm --> FLD Reset
        ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Delay Time us [150,x]
        DELAY_XUS_EXINT(150);
    }


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // Scan Auto FLD + 4
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P1D_34_ANA_CDR_06) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~_BIT7, 0x00);

    // [1] adp_en_manual = 1'b1 --> Enable CDR Clock Out
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT1, _BIT1);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();


    //////////////////////////
    //  Scan FLD Band + 4   //
    //////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [0] DP_XTAL_CYCLE = 1'b0 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit_EXINT(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usVCOBandScan = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Auto FLD Band
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P1D_34_ANA_CDR_06) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        if((usVCOBandScan == 0) || (ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    if((usVCOBandScan != 0) && (ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        g_usDpRx1ClockMeasureCount = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_usDpRx1ClockMeasureCount) >> 2);
    }
    else
    {
        usVCOBandDiff = 0;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(usVCOBandDiff != 0)
    {
        // VCO Adjust
        ScalerDpRx1AdjustLaneFLDBand_EXINT0(usVCOBandDiff);
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();


    ////////////////////
    // CDR Close Loop //
    ////////////////////

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x]
    DELAY_45US_EXINT();

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit_EXINT(P1D_11_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] xclk_sel = 1'b0 --> Keep Link Clock from Analog
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}
//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustLaneFLDBand_EXINT0(WORD usVCOBandDiff) using 1
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    ucAutoVCOBand = (ScalerGetByte_EXINT(P1D_34_ANA_CDR_06) & 0x7F);

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit_EXINT(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_usDpRx1ClockMeasureCount = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

        if(g_usDpRx1ClockMeasureCount < g_usDpRx1ClockTargetCount)
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_usDpRx1ClockTargetCount - g_usDpRx1ClockMeasureCount) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_usDpRx1ClockMeasureCount - g_usDpRx1ClockTargetCount) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Reload Best FLD Band
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDFEInitial_EXINT0(void) using 1
{
    // LE Initial = 10
    ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x0A);
    ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x0A);
    ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x0A);
    ScalerSetByte_EXINT(P1D_D2_L3_LIMIT_INIT, 0x0A);

    // Tap0 Initial Value = 15
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, 0x0F);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_D6_L3_INIT_4, 0x00);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx1DFECheck_EXINT0(void) using 1
{
    // DFECheck is not adopted for RL6492 Rx1
    return _FALSE;
}

//--------------------------------------------------
// Description : Check Valid Signal in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx1SignalCheck_EXINT0(void) using 1
{
    WORD usDataStreamL0 = 0;

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    SET_DP_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    // [5] Scramble_dis check
    if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x02, _BIT5) == _BIT5)
    {
        return _TRUE;
    }

    // [3:0] Enable Data Stream Signal Detection
    ScalerSetBit_EXINT(P1D_22_CMU_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b0 -> data stream
    // [4:0] DP_XTAL_CYCLE = 4'b00100 -> XTAL Counter Cycles = 2000 need to wait at least 75us
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usDataStreamL0 = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR:

            if((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0x157C))
            {
                return _FALSE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0xCE4))
            {
                return _FALSE;
            }

            break;
    }

    return _TRUE;
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RebuildPhy_WDINT(BYTE ucDpLinkRate, BYTE ucDpcdLane) using 3
{
    WORD pusLevel0LEErrorCount[4];
    WORD pusLevel1LEErrorCount[4];
    WORD pusLevel2LEErrorCount[4];
    WORD pusLevel3LEErrorCount[4];
    BYTE ucLELevel0 = 0;
    BYTE ucLELevel1 = 0;
    BYTE ucLELevel2 = 0;
    BYTE ucLELevel3 = 0;
    BYTE ucIcp = 0;
    BYTE ucLaneSelect = 0;

    ucDpLinkRate = ucDpLinkRate;
    ucDpcdLane = ucDpcdLane;

    ucIcp = (ScalerGetByte_EXINT(P1D_31_ANA_CDR_03) & 0x0F);
    ucLELevel2 = ScalerGetBit_EXINT(P1D_A2_L0_LIMIT_INIT, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)); // 10/12
    ucLELevel0 = ucLELevel2 - 9; // 1/3
    ucLELevel1 = ucLELevel2 - 5; // 5/7
    ucLELevel3 = ucLELevel2 + 5; // 15/17


    ////////////////////////////
    // LE = Default = Level 2 //
    ////////////////////////////

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay Time us [600,x] Delay for Checking 8b10b Error Count
    DELAY_XUS_EXINT(600);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#endif

    //////////////////
    // LE = Level 3 //
    //////////////////

    // LE Initial = 15/17
    ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, ucLELevel3);
    ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, ucLELevel3);
    ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, ucLELevel3);
    ScalerSetByte_EXINT(P1D_D2_L3_LIMIT_INIT, ucLELevel3);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x80);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS_EXINT(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay Time us [600,x] Delay for Checking 8b10b Error Count
    DELAY_XUS_EXINT(600);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#endif

    //////////////////
    // LE = Level 1 //
    //////////////////

    // LE Initial = 5/7
    ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, ucLELevel1);
    ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, ucLELevel1);
    ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, ucLELevel1);
    ScalerSetByte_EXINT(P1D_D2_L3_LIMIT_INIT, ucLELevel1);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x80);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS_EXINT(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay Time us [600,x] Delay for Checking 8b10b Error Count
    DELAY_XUS_EXINT(600);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#endif


    //////////////////
    // LE = Level 0 //
    //////////////////

    // LE Initial = 1/3
    ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, ucLELevel0);
    ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, ucLELevel0);
    ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, ucLELevel0);
    ScalerSetByte_EXINT(P1D_D2_L3_LIMIT_INIT, ucLELevel0);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x80);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x80);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS_EXINT(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay Time us [600,x] Delay for Checking 8b10b Error Count
    DELAY_XUS_EXINT(600);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4));

#endif


    ///////////////////////////////////
    // Choose The Best DFE Parameter //
    ///////////////////////////////////

    for(ucLaneSelect = 0; ucLaneSelect < 4; ucLaneSelect++)
    {
#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_1_LANE)

        g_ucDpRx1Temp = _D1_DP_LANE0;

#elif(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

        g_ucDpRx1Temp = ucLaneSelect;
#endif

        if(pusLevel3LEErrorCount[g_ucDpRx1Temp] >= pusLevel0LEErrorCount[g_ucDpRx1Temp])
        {
            if((pusLevel2LEErrorCount[g_ucDpRx1Temp] > pusLevel0LEErrorCount[g_ucDpRx1Temp]) && (pusLevel1LEErrorCount[g_ucDpRx1Temp] >= pusLevel0LEErrorCount[g_ucDpRx1Temp]))
            {
                if(pusLevel1LEErrorCount[g_ucDpRx1Temp] == pusLevel0LEErrorCount[g_ucDpRx1Temp])
                {
                    // LE Initial = 3/5
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel0 + ucLELevel1) >> 1);
                }
                else
                {
                    // LE Initial = 1/3
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel0);
                }
            }
            else if((pusLevel0LEErrorCount[g_ucDpRx1Temp] > pusLevel2LEErrorCount[g_ucDpRx1Temp]) && (pusLevel1LEErrorCount[g_ucDpRx1Temp] >= pusLevel2LEErrorCount[g_ucDpRx1Temp]))
            {
                if(pusLevel1LEErrorCount[g_ucDpRx1Temp] == pusLevel2LEErrorCount[g_ucDpRx1Temp])
                {
                    // LE Initial = 7/9
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel1 + ucLELevel2) >> 1);
                }
                else
                {
                    // LE Initial = 10/12
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel2);
                }
            }
            else
            {
                // LE Initial = 5/7
                ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel1);
            }
        }
        else
        {
            if((pusLevel1LEErrorCount[g_ucDpRx1Temp] > pusLevel3LEErrorCount[g_ucDpRx1Temp]) && (pusLevel2LEErrorCount[g_ucDpRx1Temp] >= pusLevel3LEErrorCount[g_ucDpRx1Temp]))
            {
                if(pusLevel2LEErrorCount[g_ucDpRx1Temp] == pusLevel3LEErrorCount[g_ucDpRx1Temp])
                {
                    // LE Initial = 12/14
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel2 + ucLELevel3) >> 1);
                }
                else
                {
                    // LE Initial = 15/17
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel3);
                }
            }
            else if((pusLevel3LEErrorCount[g_ucDpRx1Temp] > pusLevel1LEErrorCount[g_ucDpRx1Temp]) && (pusLevel2LEErrorCount[g_ucDpRx1Temp] >= pusLevel1LEErrorCount[g_ucDpRx1Temp]))
            {
                if(pusLevel2LEErrorCount[g_ucDpRx1Temp] == pusLevel1LEErrorCount[g_ucDpRx1Temp])
                {
                    // LE Initial = 7/9
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel1 + ucLELevel2) >> 1);
                }
                else
                {
                    // LE Initial = 5/7
                    ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel1);
                }
            }
            else
            {
                // LE Initial = 10/12
                ScalerSetByte_EXINT((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel2);
            }
        }
    }

    // HBR Reload Tap0 = 21
    if(ScalerDpRx1GetDpcdInfo_WDINT(0x00, 0x01, 0x00) == _DP_LINK_HBR)
    {
        ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x15);
        ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x15);
        ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x15);
        ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, 0x15);
    }

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x81);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x81);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x81);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x81);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);

    // Toggle en_fore_offset
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS_EXINT(85);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS_EXINT(150);
}
#endif

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PBA_C4_DPCD_DATA_PORT);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}
//--------------------------------------------------
// Description  : DP Sink Status Setting in EXINT
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync) using 1
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _OFF)
        if(g_ucDpRx1LinkRate > _D1_DP_LINK_CLK_RATE)
#else
        if(g_ucDpRx1LinkRate > ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x22, 0x01))
#endif
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }
    else
    {
        if(g_ucDpRx1LinkRate > ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, 0x01))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }

    ScalerDpRx1ErrorCounterDisable_EXINT0();

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & (_BIT1 | _BIT0)) >= _BIT0)
        {
            ScalerDpRx1Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
        }
        else
        {
            if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
            {
#if(_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _OFF)

                ScalerDpRx1Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
#endif
            }
        }
    }

    ScalerDpRx1ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpRx1Tp1Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    ScalerDpRx1ErrorCounterDisable_EXINT0();

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        ScalerDpRx1Tp2SetPhy_EXINT0();
    }

    ScalerDpRx1ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpRx1Tp2Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Settings after Link Training Pass
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1TrainingPatternEnd_EXINT0(void) using 1
{
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            // Clear Lane1/2/3 Link status
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x02, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _DP_TWO_LANE:
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            // Clear Lane2/3 Link status
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _DP_FOUR_LANE:
        default:
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;
    }

    // De-Skew Circuit Reset
    ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Enable Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 3
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PBA_C4_DPCD_DATA_PORT);
}
#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 3
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}
#endif
#endif

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE pucDpPhyLinkTrainingLevel[4];
    BYTE pucDpPhyLinkTrainingRequest[4];
    BYTE ucFakeLTLaneCount = g_ucDpRx1LaneCount;

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
           (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL) &&
           (g_bDpRx1Tp1Initial == _FALSE))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);

            g_ucDpRx1LinkRequest01 = 0x00;
            g_ucDpRx1LinkRequest23 = 0x00;

#if(_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _ON)
            SET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
            SET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
            SET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
            SET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
#endif
            g_bDpRx1Tp1Initial = _TRUE;
        }

        pucDpPhyLinkTrainingLevel[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpPhyLinkTrainingLevel[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpPhyLinkTrainingLevel[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpPhyLinkTrainingLevel[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        for(pData_EXINT[0] = 0; pData_EXINT[0] <= 1; pData_EXINT[0]++)
        {
            if((pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x02;
#else
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = (pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) + 0x01;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x03;
            }

            if((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x20;
#else
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = ((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] << 4) & (_BIT5 | _BIT4)) + 0x10;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x30;
            }
        }

        g_ucDpRx1LinkStatus01 = 0;
        g_ucDpRx1LinkStatus23 = 0;

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane3 Check
                if(((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ((g_ucDpRx1LinkRequest23 >> 4) & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                            CLR_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                }

                // Lane2 Check
                if(((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest23 & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                            CLR_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                }

                // Lane1 Check
                if(((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ((g_ucDpRx1LinkRequest01 >> 4) & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                            CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest01 & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                            CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_TWO_LANE:

                // Lane1 Check
                if(((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ((g_ucDpRx1LinkRequest01 >> 4) & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                            CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest01 & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                            CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else
                    {
                        if((GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                           ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest01 & (_BIT1 | _BIT0))))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                            CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx1LinkStatus01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx1LinkStatus23);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx1LinkStatus01 & _BIT0) == _BIT0)
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx1LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx1LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0)) && (((g_ucDpRx1LinkStatus23 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))))
                {
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) && (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);
        }

        pucDpPhyLinkTrainingLevel[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpPhyLinkTrainingLevel[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpPhyLinkTrainingLevel[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpPhyLinkTrainingLevel[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        for(pData_EXINT[0] = 0; pData_EXINT[0] <= 1; pData_EXINT[0]++)
        {
            if((pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x02;
#else
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = (pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) + 0x01;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x03;
            }

            if((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x20;
#else
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = ((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] << 4) & (_BIT5 | _BIT4)) + 0x10;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x30;
            }
        }

        g_ucDpRx1LinkRequest01 = (pucDpPhyLinkTrainingLevel[0] & 0x03) | ((pucDpPhyLinkTrainingLevel[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pucDpPhyLinkTrainingLevel[2] & 0x03) | ((pucDpPhyLinkTrainingLevel[3] << 4) & 0x30);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        if(g_ucDpRx1FakeLTLaneCount <= g_ucDpRx1LaneCount)
        {
            ucFakeLTLaneCount = g_ucDpRx1FakeLTLaneCount;
        }
        else
        {
            ucFakeLTLaneCount = g_ucDpRx1LaneCount;
        }
#endif
        switch(ucFakeLTLaneCount)
        {
            case _DP_ONE_LANE:

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0))))) &&
                   (((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                }

                if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

                if((((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))) &&
                   (((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))) &&
                   (((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) == ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT1 | _BIT0)))) &&
                   (((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucDecodeStatus = 0;
    BYTE ucFakeLTLaneCount = g_ucDpRx1LaneCount;

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        g_ucDpRx1LinkRequest01 = ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & 0x03) |
                                  ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) >> 1) & 0x0C) |
                                  ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) << 4) & 0x30) |
                                  ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) << 3) & 0xC0));

        g_ucDpRx1LinkRequest23 = ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05) & 0x03) |
                                  ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05) >> 1) & 0x0C) |
                                  ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06) << 4) & 0x30) |
                                  ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06) << 3) & 0xC0));

        // Clear 8b/10b Decode Error Flag
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status (-K28.5)
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [45,x]
        DELAY_45US_EXINT();

        ucEQCRCStatus = ScalerGetByte_EXINT(PB_12_EQ_CRC_1);

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status (+K28.5)
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [45,x]
        DELAY_45US_EXINT();

        ucEQCRCStatus = (ucEQCRCStatus | ScalerGetByte_EXINT(PB_12_EQ_CRC_1));

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ucDecodeStatus = ScalerGetByte_EXINT(PB_06_DECODE_10B8B_ERROR);

        g_ucDpRx1EQCRC = 0x00;

        if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x01);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) >> 2);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 3);
        }

        if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x02);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 2);
        }

        if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x04);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 1);
        }

        if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 3);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x08);
        }

        ucEQCRCStatus = g_ucDpRx1EQCRC;

        g_ucDpRx1EQCRC = 0x00;

        if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= (ucDecodeStatus & 0x01);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x02) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x04) >> 2);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x08) >> 3);
        }

        if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x01) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= (ucDecodeStatus & 0x02);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x04) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x08) >> 2);
        }

        if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x01) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x02) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= (ucDecodeStatus & 0x04);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x08) >> 1);
        }

        if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x01) << 3);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x02) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucDecodeStatus & 0x04) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= (ucDecodeStatus & 0x08);
        }

        ucDecodeStatus = g_ucDpRx1EQCRC;

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane2 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT2) == _BIT2) && ((ucDecodeStatus & _BIT2) == 0x00))
                {
                    g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest23 & 0x03) + ((g_ucDpRx1LinkRequest23 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x04;
                    }
                }

                // Lane3 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT3) == _BIT3) && ((ucDecodeStatus & _BIT3) == 0x00))
                {
                    g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x70;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06) & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx1LinkRequest23 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest23 >> 6) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x40;
                    }
                }

                // Lane1 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT1) == _BIT1) && ((ucDecodeStatus & _BIT1) == 0x00))
                {
                    g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx1LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest01 >> 6) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x40;
                    }
                }

                // Lane0 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT0) == _BIT0) && ((ucDecodeStatus & _BIT0) == 0x00))
                {
                    g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                    }
                }

                break;

            case _DP_TWO_LANE:

                // Lane1 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT1) == _BIT1) && ((ucDecodeStatus & _BIT1) == 0x00))
                {
                    g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx1LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest01 >> 6) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x40;
                    }
                }

                // Lane0 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT0) == _BIT0) && ((ucDecodeStatus & _BIT0) == 0x00))
                {
                    g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                    }
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Lane0 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT0) == _BIT0) && ((ucDecodeStatus & _BIT0) == 0x00))
                {
                    g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                    }
                }

                break;
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx1LinkStatus01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx1LinkStatus23);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx1LinkStatus01 & 0x07) == 0x07)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx1LinkStatus01 & 0x77) == 0x77)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx1LinkStatus01 & 0x77) == 0x77) && (((g_ucDpRx1LinkStatus23 & 0x77) == 0x77)))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        pData_EXINT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pData_EXINT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pData_EXINT[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pData_EXINT[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        g_ucDpRx1LinkRequest01 = (pData_EXINT[0] & 0x03) | ((pData_EXINT[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pData_EXINT[2] & 0x03) | ((pData_EXINT[3] << 4) & 0x30);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        if(g_ucDpRx1FakeLTLaneCount <= g_ucDpRx1LaneCount)
        {
            ucFakeLTLaneCount = g_ucDpRx1FakeLTLaneCount;
        }
        else
        {
            ucFakeLTLaneCount = g_ucDpRx1LaneCount;
        }
#endif
        switch(ucFakeLTLaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x07);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                }

                if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                }

                if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                }

                if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                }

                if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))) &&
                   (((pData_EXINT[2] & _BIT5) == _BIT5) || ((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[3] & _BIT5) == _BIT5) || ((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}

#endif // End of #if(_D1_DP_EXIST == _ON)
