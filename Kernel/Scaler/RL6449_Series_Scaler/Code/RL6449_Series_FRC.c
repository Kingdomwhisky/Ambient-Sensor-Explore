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
// ID Code      : RL6449_Series_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __6449_SERIES_FRC__

#include "ScalerFunctionInclude.h"
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
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
void ScalerFRCInitial(void);
void ScalerFRCEn(BYTE ucSettingPath, bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCCompareIHFandDHF(WORD usVerSize);
WORD ScalerFRCSetOneFrameDVTotal(void);
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF);
void ScalerFRCWaitWriteFrameBufFinish(void);

#if(_FREEZE_SUPPORT == _ON)
void ScalerFRCDisplayFreeze(bit bEn);
#endif
#endif
void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
//--------------------------------------------------
// Description  : FRC Initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCInitial(void)
{
    //------------------------------
    // FRC - M1,M2
    //------------------------------
    // Set M1 Capture Line Step
    ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H, 0x00);
    ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M, 0x00);
    ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L, 0x00);

    // Set M1 Display Line Step
    ScalerSetBit(P5_99_DISP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_9A_DISP_M1_LINE_STEP_H, 0x00);
    ScalerSetByte(P5_9B_DISP_M1_LINE_STEP_M, 0x00);
    ScalerSetByte(P5_9C_DISP_M1_LINE_STEP_L, 0x00);

    // Set M2 Capture Line Step
    ScalerSetBit(P45_19_CAP_M2_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_1A_CAP_M2_LINE_STEP_H, 0x00);
    ScalerSetByte(P45_1B_CAP_M2_LINE_STEP_M, 0x00);
    ScalerSetByte(P45_1C_CAP_M2_LINE_STEP_L, 0x00);

    // Set M2 Display Line Step
    ScalerSetBit(P45_99_DISP_M2_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_9A_DISP_M2_LINE_STEP_H, 0x00);
    ScalerSetByte(P45_9B_DISP_M2_LINE_STEP_M, 0x00);
    ScalerSetByte(P45_9C_DISP_M2_LINE_STEP_L, 0x00);

    // Set Single Buffer Mode
    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

    // Set Line Mode / CAP Start Point to Change Block_sel = 1: Reference to vertical active region
    ScalerSetBit(P5_28_CAP_M1_DDR_CTRL2, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT6);
    ScalerSetBit(P45_28_CAP_M2_DDR_CTRL2, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT6);

    // Set 3 Buffer Disable
    ScalerSetByte(P5_29_CAP_M1_DDR_CTRL3, 0x00);
    ScalerSetByte(P45_29_CAP_M2_DDR_CTRL3, 0x00);

    // Disable One Frame FRC
    ScalerSetByte(P5_B1_DISP_M1_ONEF_DHF_H, 0x00);
    ScalerSetByte(P45_B1_DISP_M2_ONEF_DHF_H, 0x00);

    // One Frame FRC m1 m2 drop frame simultaneously
    ScalerSetBit(P5_44_CAP_M1_4CH_CTRL2, ~(_BIT2), 0x00);
    ScalerSetBit(P45_44_CAP_M2_4CH_CTRL2, ~(_BIT2), 0x00);
    ScalerSetBit(P31_C3_IMD_DB_STATUS1, ~0x07, 0x00);

    // Set Display :(1) Capture data from I-Domain, (2)E/O mode, (3) Disable 3 Buffer
    ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
    {
        ScalerFRCEn((_FRC_CAP_MAIN_1 | _FRC_DISP_MAIN_1 | _FRC_CAP_MAIN_2 | _FRC_DISP_MAIN_2), _ENABLE);

        // Set Frame sync with line buffer mode
        ScalerFRCSetDDomainSourceSelect(_DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);
    }

    // Set double frame buffer disable
    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Enable Display double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

#if(_MN_FRAME_TRACKING_SUPPORT == _ON)
    // Disable M:N frame tracking
    if(GET_MEMORY_SELECT() != _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemorySetFrameTrackingEnable(_DISABLE);
    }
#endif

    // Wait double buffer
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCEn(BYTE ucSettingPath, bit bEn)
{
    if((ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00) &&
       ((ucSettingPath & (_FRC_CAP_MAIN_1 | _FRC_CAP_MAIN_2)) != 0x00) &&
       (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0))
    {
        // Wait _EVENT_IEN_STOP before FRC Capture Disable
        ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
    }

    // FRC Capture M1
    if((ucSettingPath & _FRC_CAP_MAIN_1) == _FRC_CAP_MAIN_1)
    {
        if(bEn == _DISABLE)
        {
            // Disable Capture Block
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT7), 0x00);
        }
        else
        {
            if(ScalerGetBit(P5_27_CAP_M1_DDR_CTRL1, _BIT7) == 0x00)
            {
                // Enable Capture Block
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT7), _BIT7);
            }
        }
    }

    // FRC Capture M2
    if((ucSettingPath & _FRC_CAP_MAIN_2) == _FRC_CAP_MAIN_2)
    {
        if(bEn == _DISABLE)
        {
            // Disable Capture block
            ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT7), 0x00);
        }
        else
        {
            if(ScalerGetBit(P45_27_CAP_M2_DDR_CTRL1, _BIT7) == 0x00)
            {
                // Enable Capture block
                ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT7), _BIT7);
            }
        }
    }

    // FRC Display M1
    if((ucSettingPath & _FRC_DISP_MAIN_1) == _FRC_DISP_MAIN_1)
    {
        if(bEn == _DISABLE)
        {
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) &&
               (ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == 0x00))
            {
                return;
            }
#endif
            // Disable Capture Block
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), 0x00);
        }
        else
        {
            if(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT0) == 0x00)
            {
                // Enable Capture block
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), _BIT0);
            }
        }

        // Enable FRC M1 Display double buffer
        ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    }

    // FRC Display M2
    if((ucSettingPath & _FRC_DISP_MAIN_2) == _FRC_DISP_MAIN_2)
    {
        if(bEn == _DISABLE)
        {
            // Disable Capture block
            ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT0), 0x00);
        }
        else
        {
            if(ScalerGetBit(P45_AC_DISP_M2_DISP_CTRL1, _BIT0) == 0x00)
            {
                // Enable Capture block
                ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT0), _BIT0);
            }
        }

        // Enable FRC M2 Display double buffer
        ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
    }

    if((ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00) &&
       ((ucSettingPath & (_FRC_DISP_MAIN_1 | _FRC_DISP_MAIN_2)) != 0x00))
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    // -----------------------
    // Set FRC IVS2DVSDelay
    // -----------------------
    ScalerFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Consider Input Faster Or Slower
    // -----------------------
    ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Frame tracking function for VFreq < 30Hz
    // -----------------------
    if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);
    }

    // -----------------------
    // Set Up FRC Capture
    // -----------------------
    ScalerFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Display
    // -----------------------
    ScalerFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // -----------------------
        // Enable FRC
        // -----------------------
        // -- 1 -- Enable FRC Capture

        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, _BIT7);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, _BIT7);


        // -- 2 -- Enable FRC Display
        // Wait _EVENT_DEN_START for FRC Display Enable At The Same Time
        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForEvent(_EVENT_DEN_START);
        }

        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT0, _BIT0);
        ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT0, _BIT0);

        // Enable FRC M1/M2 Display double buffer
        ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
        ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

        // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
        if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }
    }
    else
#endif
    {
        // Wait I-domain Stable Before FRC enable
        if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // -----------------------
        // Enable FRC
        // -----------------------
        // -- 1 -- Enable FRC Capture

        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT7, _BIT7);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT7, _BIT7);


        // -- 2 -- Enable FRC Display
        // Wait _EVENT_DEN_START for FRC Display Enable At The Same Time
        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForEvent(_EVENT_DEN_START);
        }

        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT0, _BIT0);
        ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT0, _BIT0);

        // Enable FRC M1/M2 Display double buffer
        ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
        ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

        // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
        if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // -----------------------
        // Set Double / Single Frame Buffer
        // -----------------------
        // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
        if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForEvent(_EVENT_IEN_START);
        }
    }

    switch(GET_MEMORY_FRAME_BUFFER())
    {
        case _MEMORY_1_FRAME_BUFFER:
        default:

            // Set Single Buffer
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
            ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            break;

        case _MEMORY_2_FRAME_BUFFER:

            // Set Double Buffer
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
            ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

            break;

        case _MEMORY_3_FRAME_BUFFER:

            // Set Double Buffer
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
            ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

            // Set 3 Buffer
            ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P45_29_CAP_M2_DDR_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            break;
    }

    // Enable FRC Display Double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~(_BIT4), _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~(_BIT4), _BIT4);

    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
    {
        // Wait double buffer
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_MEMORY_FRAME_BUFFER() != _MEMORY_3_FRAME_BUFFER))
    {
        // Set Rotation DB enable
        ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT1, _BIT1);
        ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT1, _BIT1);

        // Set CW180 Enable
        ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT0, _BIT0);
        ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT0, _BIT0);
    }
#endif

    DebugMessageFRC("FRC-H", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("FRC-V", pstFIFOSize->usInputVHeight);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucSettingPath --> Path
//                ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTemp = 0;
    BYTE ucLen = _FRC_ACCESS_WRITE_LENGTH;

    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    // Calculate Line Mode Size
    ulTemp = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

    // VHeight / 2 for E/O Mode
    usVerSize = usVerSize >> 1;

    // Calculate Line Step and Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);

    // One Line total pixel for Memory (FRC unit : 64 bits)
    ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
             (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
             ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, ucLen, 1);

    //***********************************
    // Main 1
    //***********************************
    // Set Line Mode
    ScalerSetBit(P5_28_CAP_M1_DDR_CTRL2, ~(_BIT4), 0x00);

    // Set Block Step
    ScalerMaskSetDWord(P5_15_CAP_M1_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);

    // Set Water level
    ScalerSetBit(P5_1D_CAP_M1_WATER_LEVEL_H, ~(_BIT0), ((((WORD)ucLen / 2) >> 8) & 0x01));
    ScalerSetByte(P5_1E_CAP_M1_WATER_LEVEL_L, (((WORD)ucLen / 2) & 0xFF));

    // Set Pixel Nmber
    ScalerSetWord(P5_1F_CAP_M1_PIXEL_NUM_H, usHorSize);

    // Set Line Number
    ScalerSetWord(P5_21_CAP_M1_LINE_NUM_H, usVerSize);

    // Set Number
    ScalerSetByte(P5_23_CAP_M1_WR_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P5_24_CAP_M1_WR_NUM_L, (ulTemp & 0xFF));

    // Set Length, Remain
    ScalerSetByte(P5_25_CAP_M1_WR_LEN, ucLen);
    ScalerSetByte(P5_26_CAP_M1_WR_REMAIN, ((ulTemp >> 16) & 0xFF));

    // Set Line Step
    ScalerMaskSetDWord(P5_19_CAP_M1_LINE_STEP_MSB, 0xF0000000, stStep.ulLineStep);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerRotationCheckStatus() == _TRUE) && ((GET_ROT_TYPE() == _ROT_VER_MIRROR) || (GET_ROT_TYPE() == _ROT_CW180)))
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            PDATA_DWORD(1) = 0x00;
            PDATA_DWORD(2) = stStep.ulLineStep * (usVerSize - 1);
            PDATA_DWORD(3) = 0x00;
        }
        else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            PDATA_DWORD(1) = stStep.ulBlockStep;
            PDATA_DWORD(2) = stStep.ulLineStep * (usVerSize - 1);
            PDATA_DWORD(3) = stStep.ulBlockStep + (stStep.ulLineStep * (usVerSize - 1));
        }
        else
        {
            PDATA_DWORD(1) = stStep.ulBlockStep;
            PDATA_DWORD(2) = stStep.ulBlockStep * 2;
            PDATA_DWORD(3) = 0x00;
        }
    }
    else
#endif
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            PDATA_DWORD(1) = 0x00;
        }
        else // _MEMORY_2_FRAME_BUFFER
        {
            PDATA_DWORD(1) = stStep.ulBlockStep;
        }
        PDATA_DWORD(2) = 0x00;
        PDATA_DWORD(3) = 0x00;
    }
    PDATA_DWORD(0) = 0x00;

    ScalerMaskSetDWord(P5_00_CAP_M1_MEM_ADDR_MSB, 0xF0000000, PDATA_DWORD(0));
    ScalerMaskSetDWord(P5_04_CAP_M1_BL2_ADDR_MSB, 0xF0000000, PDATA_DWORD(1));
    ScalerMaskSetDWord(P5_08_CAP_M1_BL3_ADDR_MSB, 0xF0000000, PDATA_DWORD(2));
    ScalerMaskSetDWord(P5_45_CAP_M1_BL4_ADDR_MSB, 0xF0000000, PDATA_DWORD(3));

    // Use IVS as synchronous reset
    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~(_BIT1), _BIT1);

    //***********************************
    // Main 2
    //***********************************

    // Set Line mode
    ScalerSetBit(P45_28_CAP_M2_DDR_CTRL2, ~(_BIT4), 0x00);

    // Set Block Step
    ScalerMaskSetDWord(P45_15_CAP_M2_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);

    // Set Water level
    ScalerSetBit(P45_1D_CAP_M2_WATER_LEVEL_H, ~(_BIT0), ((((WORD)ucLen / 2) >> 8) & 0x01));
    ScalerSetByte(P45_1E_CAP_M2_WATER_LEVEL_L, (((WORD)ucLen / 2) & 0xFF));

    // Set Pixel nmber
    ScalerSetWord(P45_1F_CAP_M2_PIXEL_NUM_H, usHorSize);

    // Set line number
    ScalerSetWord(P45_21_CAP_M2_LINE_NUM_H, usVerSize);

    // Set Number
    ScalerSetByte(P45_23_CAP_M2_WR_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P45_24_CAP_M2_WR_NUM_L, (ulTemp & 0xFF));

    // Set Length, Remain
    ScalerSetByte(P45_25_CAP_M2_WR_LEN, ucLen);
    ScalerSetByte(P45_26_CAP_M2_WR_REMAIN, ((ulTemp >> 16) & 0xFF));

    // Set Line Step
    ScalerMaskSetDWord(P45_19_CAP_M2_LINE_STEP_MSB, 0xF0000000, stStep.ulLineStep);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerRotationCheckStatus() == _TRUE) && ((GET_ROT_TYPE() == _ROT_VER_MIRROR) || (GET_ROT_TYPE() == _ROT_CW180)))
    {
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            PDATA_DWORD(0) = stStep.ulBlockStep;
            PDATA_DWORD(1) = 0x00;
            PDATA_DWORD(2) = stStep.ulBlockStep + stStep.ulLineStep * (usVerSize - 1);
            PDATA_DWORD(3) = 0x00;
        }
        else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            PDATA_DWORD(0) = stStep.ulBlockStep * 2;
            PDATA_DWORD(1) = stStep.ulBlockStep * 3;
            PDATA_DWORD(2) = stStep.ulBlockStep * 2 + (stStep.ulLineStep * (usVerSize - 1));
            PDATA_DWORD(3) = stStep.ulBlockStep * 3 + (stStep.ulLineStep * (usVerSize - 1));
        }
        else
        {
            PDATA_DWORD(0) = stStep.ulBlockStep * 3;
            PDATA_DWORD(1) = stStep.ulBlockStep * 4;
            PDATA_DWORD(2) = stStep.ulBlockStep * 5;
            PDATA_DWORD(3) = 0x00;
        }
#else
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            PDATA_DWORD(1) = 0x00;
            PDATA_DWORD(2) = stStep.ulLineStep * (usVerSize - 1);
            PDATA_DWORD(3) = 0x00;
        }
        else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            PDATA_DWORD(1) = stStep.ulBlockStep;
            PDATA_DWORD(2) = stStep.ulLineStep * (usVerSize - 1);
            PDATA_DWORD(3) = stStep.ulBlockStep + (stStep.ulLineStep * (usVerSize - 1));
        }
        else
        {
            PDATA_DWORD(1) = stStep.ulBlockStep;
            PDATA_DWORD(2) = stStep.ulBlockStep * 2;
            PDATA_DWORD(3) = 0x00;
        }
        PDATA_DWORD(0) = 0x00;
#endif
    }
    else
#endif
    {
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            PDATA_DWORD(0) = stStep.ulBlockStep;
            PDATA_DWORD(1) = 0x00;
        }
        else // _MEMORY_2_FRAME_BUFFER
        {
            PDATA_DWORD(0) = stStep.ulBlockStep * 2;
            PDATA_DWORD(1) = stStep.ulBlockStep * 3;
        }
        PDATA_DWORD(2) = 0x00;
        PDATA_DWORD(3) = 0x00;
#else
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            PDATA_DWORD(1) = 0x00;
        }
        else // _MEMORY_2_FRAME_BUFFER
        {
            PDATA_DWORD(1) = stStep.ulBlockStep;
        }
        PDATA_DWORD(0) = 0x00;
        PDATA_DWORD(2) = 0x00;
        PDATA_DWORD(3) = 0x00;
#endif
    }
    ScalerMaskSetDWord(P45_00_CAP_M2_MEM_ADDR_MSB, 0xF0000000, PDATA_DWORD(0));
    ScalerMaskSetDWord(P45_04_CAP_M2_BL2_ADDR_MSB, 0xF0000000, PDATA_DWORD(1));
    ScalerMaskSetDWord(P45_08_CAP_M2_BL3_ADDR_MSB, 0xF0000000, PDATA_DWORD(2));
    ScalerMaskSetDWord(P45_45_CAP_M2_BL4_ADDR_MSB, 0xF0000000, PDATA_DWORD(3));

    // Use IVS as synchronous reset
    ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~(_BIT1), _BIT1);
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTemp = 0;
    WORD usPreReadLine = 0;
    DWORD ulDisp_addr1 = 0;
    DWORD ulDisp_addr2 = 0;
    DWORD ulDisp_addr3 = 0;
    DWORD ulDisp_addr4 = 0;
    BYTE ucLen = _FRC_ACCESS_READ_LENGTH;

    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    // Calculate Line Mode Size
    ulTemp = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

    usPreReadLine = ScalerFRCCalculatePreReadLine(usVerSize);

    // E/O mode
    usVerSize = usVerSize >> 1;

    // Calculate Line Step And Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);

    // One Line total pixel for Memory (FRC unit : 64 bits)
    ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
             (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
             ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, ucLen, 1);

    //***********************************
    // Main 1
    //***********************************
    // Set Block Step
    ScalerMaskSetDWord(P5_95_DISP_M1_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);

    // Set Line Step
    ScalerMaskSetDWord(P5_99_DISP_M1_LINE_STEP_MSB, 0xF0000000, stStep.ulLineStep);

    // Set Water Level
    // Display Water Level < FIFO Depth (512) - Length / 2
    ScalerSetBit(P5_A0_DISP_M1_WTLVL_H, ~(_BIT0), ((510 - ucLen / 2) >> 8) & 0x01);
    ScalerSetByte(P5_A1_DISP_M1_WTLVL_L, (BYTE)((510 - ucLen / 2) & 0xFF));

    // Set Pixel Number
    ScalerSetWord(P5_A2_DISP_M1_PXL_NUM_H, usHorSize);

    // Set Line number
    ScalerSetWord(P5_A4_DISP_M1_LINE_NUM_H, usVerSize);

    // Set Pre-read
    ScalerSetWord(P5_A6_DISP_M1_PRRD_VST_H, usPreReadLine);

    // Set Number
    ScalerSetByte(P5_A8_DISP_M1_READ_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P5_A9_DISP_M1_READ_NUM_L, (ulTemp & 0xFF));

    // Set Length, Remain
    ScalerSetByte(P5_AA_DISP_M1_READ_LEN, ucLen);
    ScalerSetByte(P5_AB_DISP_M1_READ_REMAIN, ((ulTemp >> 16) & 0xFF));

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerRotationCheckStatus() == _TRUE) && ((GET_ROT_TYPE() == _ROT_VER_MIRROR) || (GET_ROT_TYPE() == _ROT_CW180)))
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ulDisp_addr1 = 0x00;
            ulDisp_addr2 = 0x00;
            ulDisp_addr3 = stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr4 = 0x00;
        }
        else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            ulDisp_addr1 = 0x00;
            ulDisp_addr2 = stStep.ulBlockStep;
            ulDisp_addr3 = stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr4 = stStep.ulBlockStep + (stStep.ulLineStep * (usVerSize - 1));
        }
        else
        {
            ScalerMaskSetDWord(P5_99_DISP_M1_LINE_STEP_MSB, 0xF0000000, ((~stStep.ulLineStep) + 1));

            ulDisp_addr1 = stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr2 = stStep.ulBlockStep + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr3 = (stStep.ulBlockStep * 2) + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr4 = 0x00;
        }
    }
    else
#endif
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ulDisp_addr2 = 0x00;
        }
        else // _MEMORY_2_FRAME_BUFFER
        {
            ulDisp_addr2 = stStep.ulBlockStep;
        }
        ulDisp_addr1 = 0x00;
        ulDisp_addr3 = 0x00;
        ulDisp_addr4 = 0x00;
    }

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerRotationCheckStatus() == _TRUE) && ((GET_ROT_TYPE() == _ROT_VER_MIRROR) || (GET_ROT_TYPE() == _ROT_CW180)))
    {
        ScalerMaskSetDWord(P45_80_DISP_M2_READ_ADDR_MSB, 0xF0000000, ulDisp_addr1);
        ScalerMaskSetDWord(P45_84_DISP_M2_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr2);
        ScalerMaskSetDWord(P45_88_DISP_M2_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr3);
        ScalerMaskSetDWord(P45_DE_DISP_M2_BL4_ADDR_MSB, 0xF0000000, ulDisp_addr4);
    }
    else
#endif
#endif
    {
        ScalerMaskSetDWord(P5_80_DISP_M1_READ_ADDR_MSB, 0xF0000000, ulDisp_addr1);
        ScalerMaskSetDWord(P5_84_DISP_M1_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr2);
        ScalerMaskSetDWord(P5_88_DISP_M1_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr3);
        ScalerMaskSetDWord(P5_DE_DISP_M1_BL4_ADDR_MSB, 0xF0000000, ulDisp_addr4);
    }
    // Set Line mode
    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT7, 0x00);

    //***********************************
    // Main 2
    //***********************************
    // Set Block Step
    ScalerMaskSetDWord(P45_95_DISP_M2_BLOCK_STEP_MSB, 0xF0000000, stStep.ulBlockStep);

    // Set Line Step
    ScalerMaskSetDWord(P45_99_DISP_M2_LINE_STEP_MSB, 0xF0000000, stStep.ulLineStep);

    // Set Water Level
    // Display Water Level < FIFO Depth (512) - Length / 2
    ScalerSetBit(P45_A0_DISP_M2_WTLVL_H, ~(_BIT0), ((510 - ucLen / 2) >> 8) & 0x01);
    ScalerSetByte(P45_A1_DISP_M2_WTLVL_L, (BYTE)((510 - ucLen / 2) & 0xFF));

    // Set Pixel number
    ScalerSetWord(P45_A2_DISP_M2_PXL_NUM_H, usHorSize);

    // Set Line number
    ScalerSetWord(P45_A4_DISP_M2_LINE_NUM_H, usVerSize);

    // Set Pre-read
    ScalerSetWord(P45_A6_DISP_M2_PRRD_VST_H, usPreReadLine);

    // Set Number
    ScalerSetByte(P45_A8_DISP_M2_READ_NUM_H, ((ulTemp >> 8) & 0xFF));
    ScalerSetByte(P45_A9_DISP_M2_READ_NUM_L, (ulTemp & 0xFF));

    // Set Length, Remain
    ScalerSetByte(P45_AA_DISP_M2_READ_LEN, ucLen);
    ScalerSetByte(P45_AB_DISP_M2_READ_REMAIN, ((ulTemp >> 16) & 0xFF));

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerRotationCheckStatus() == _TRUE) && ((GET_ROT_TYPE() == _ROT_VER_MIRROR) || (GET_ROT_TYPE() == _ROT_CW180)))
    {
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ulDisp_addr1 = stStep.ulBlockStep;
            ulDisp_addr3 = ulDisp_addr1 + stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr2 = 0x00;
            ulDisp_addr4 = 0x00;
        }
        else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            ulDisp_addr1 = stStep.ulBlockStep * 2;
            ulDisp_addr2 = stStep.ulBlockStep * 3;
            ulDisp_addr3 = ulDisp_addr1 + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr4 = ulDisp_addr2 + (stStep.ulLineStep * (usVerSize - 1));
        }
        else
        {
            ScalerMaskSetDWord(P45_99_DISP_M2_LINE_STEP_MSB, 0xF0000000, ((~stStep.ulLineStep) + 1));

            ulDisp_addr1 = (stStep.ulBlockStep * 3) + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr2 = (stStep.ulBlockStep * 4) + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr3 = (stStep.ulBlockStep * 5) + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr4 = 0x00;
        }
#else
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ulDisp_addr1 = 0x00;
            ulDisp_addr2 = 0x00;
            ulDisp_addr3 = stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr4 = 0x00;
        }
        else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            ulDisp_addr1 = 0x00;
            ulDisp_addr2 = stStep.ulBlockStep;
            ulDisp_addr3 = stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr4 = stStep.ulBlockStep + (stStep.ulLineStep * (usVerSize - 1));
        }
        else
        {
            ScalerMaskSetDWord(P45_99_DISP_M2_LINE_STEP_MSB, 0xF0000000, ((~stStep.ulLineStep) + 1));

            ulDisp_addr1 = stStep.ulLineStep * (usVerSize - 1);
            ulDisp_addr2 = stStep.ulBlockStep + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr3 = (stStep.ulBlockStep * 2) + (stStep.ulLineStep * (usVerSize - 1));
            ulDisp_addr4 = 0x00;
        }
#endif
    }
    else
#endif
    {
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ulDisp_addr1 = stStep.ulBlockStep;
            ulDisp_addr3 = 0x00;
            ulDisp_addr2 = 0x00;
            ulDisp_addr4 = 0x00;
        }
        else // _MEMORY_2_FRAME_BUFFER
        {

            ulDisp_addr1 = stStep.ulBlockStep * 2;
            ulDisp_addr2 = stStep.ulBlockStep * 3;
            ulDisp_addr3 = 0x00;
            ulDisp_addr4 = 0x00;
        }
#else
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ulDisp_addr2 = 0x00;
        }
        else // _MEMORY_2_FRAME_BUFFER
        {
            ulDisp_addr2 = stStep.ulBlockStep;
        }
        ulDisp_addr1 = 0x00;
        ulDisp_addr3 = 0x00;
        ulDisp_addr4 = 0x00;
#endif
    }

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerRotationCheckStatus() == _TRUE) && ((GET_ROT_TYPE() == _ROT_VER_MIRROR) || (GET_ROT_TYPE() == _ROT_CW180)))
    {
        ScalerMaskSetDWord(P5_80_DISP_M1_READ_ADDR_MSB, 0xF0000000, ulDisp_addr1);
        ScalerMaskSetDWord(P5_84_DISP_M1_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr2);
        ScalerMaskSetDWord(P5_88_DISP_M1_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr3);
        ScalerMaskSetDWord(P5_DE_DISP_M1_BL4_ADDR_MSB, 0xF0000000, ulDisp_addr4);
    }
    else
#endif
#endif
    {
        ScalerMaskSetDWord(P45_80_DISP_M2_READ_ADDR_MSB, 0xF0000000, ulDisp_addr1);
        ScalerMaskSetDWord(P45_84_DISP_M2_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr2);
        ScalerMaskSetDWord(P45_88_DISP_M2_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr3);
        ScalerMaskSetDWord(P45_DE_DISP_M2_BL4_ADDR_MSB, 0xF0000000, ulDisp_addr4);
    }

    // Set Line mode
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT7, 0x00);

    // Use information from Capture
    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);

    // Enable FRC M1/M2 Display double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer apply
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : ucSettingPath --> Path
//                stFIFOSize    --> FIFO size
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerFRCCompareIHFandDHF(WORD usVerSize)
{
    WORD usPreRead = 0;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) && ((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR)))
    {
        // Set input slower than display
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT3, 0x00);
        ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT3, 0x00);

        // Write in double buffer
        ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
        ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
    }
    else
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
    {
        // Get Pre-read line
        usPreRead = ScalerFRCCalculatePreReadLine(usVerSize);
        usPreRead = (usPreRead == 0) ? (g_stMDomainOutputData.usVStart) : (g_stMDomainOutputData.usVStart - usPreRead);

        if(g_stMDomainOutputData.usVHeight > g_stMDomainInputData.usVHeight)
        {
            // IHF'
            PDATA_DWORD(1) = (DWORD)g_stMDomainInputData.usHFreq;
            // DHF'
            PDATA_DWORD(2) = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight);
        }
        else
        {
            // IHF'
            PDATA_DWORD(1) = GET_MDOMAIN_IHF_IN_DDOMAIN();
            // DHF'
            PDATA_DWORD(2) = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal);
        }

        // IDEN Period = IVH / IHF
        PDATA_WORD(0) = ((DWORD)GET_INPUT_TIMING_VHEIGHT() * 100 / g_stMDomainInputData.usHFreq);

        // DDEN Period = (DVH + Pre-read line) / DHF
        PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVHeight + usPreRead) * 100 / ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal));

        if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
        {
            // Set Input Slower Than Display
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT3, 0x00);
            ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT3, 0x00);
        }
        else
        {
            // Set FRC Style
            if(PDATA_WORD(1) < PDATA_WORD(0)) // If IDEN period = DDEN period, then set input faster.
            {
                // Set Input Slower Than Display
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT3, 0x00);
                ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT3, 0x00);
            }
            else
            {
                // Set Input Fast Than Display
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT3, _BIT3);
                ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~_BIT3, _BIT3);
            }
        }

        pData[8] = (PDATA_DWORD(1) > PDATA_DWORD(2)) ? (_BIT3) : (0x00);
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(GET_ROT_TYPE() != _ROT_DISABLE)
        {
            if((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) ^ pData[8]) != 0)
            {
                DebugMessageFRC("Error1-input faster/slower mis-match: IDEN", PDATA_WORD(0));
                DebugMessageFRC("Error2-input faster/slower mis-match: DDEN", PDATA_WORD(1));
                DebugMessageFRC("Error3-input faster/slower mis-match: IHF\'", PDATA_DWORD(1));
                DebugMessageFRC("Error4-input faster/slower mis-match: DHF\'", PDATA_DWORD(2));
            }
        }
        else
#endif
        {
            if((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) ^ pData[8]) != 0)
            {
                DebugMessageFRC("Error1-input faster/slower mis-match: IDEN", PDATA_WORD(0));
                DebugMessageFRC("Error2-input faster/slower mis-match: DDEN", PDATA_WORD(1));
                DebugMessageFRC("Error3-input faster/slower mis-match: IHF\'", PDATA_DWORD(1));
                DebugMessageFRC("Error4-input faster/slower mis-match: DHF\'", PDATA_DWORD(2));
            }
        }

        // Write in double buffer
        ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
        ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);


        if((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) || (GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY))
        {
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
            {
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            }

            // Set Frame sync when FRC
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(GET_MEMORY_SELECT() == _FREE_RUN_MEMORY)
        {
            if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
            {
                // m1 m2 drop frame simultaneously
                ScalerSetBit(P5_44_CAP_M1_4CH_CTRL2, ~(_BIT2), _BIT2);
                ScalerSetBit(P45_44_CAP_M2_4CH_CTRL2, ~(_BIT2), _BIT2);
                ScalerFRCOneFrameCtrl(PDATA_DWORD(1), PDATA_DWORD(2));
            }
            else
            {
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
            }
        }
    }
}

//-------------------------------------------------
// Description  : Calculate DVTotal for OneFrame FRC
// Input Value  : None
// Output Value : usDVTotal
//-------------------------------------------------
WORD ScalerFRCSetOneFrameDVTotal(void)
{
    DWORD ulFrameDiff = 0;
    DWORD ulActiveRegionDiff = 0;
    WORD usIHF = 0;
    WORD usDHF = 0;
    WORD usDVTotal = 0;

    if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDHF = (DWORD)g_usDVFreq * _PANEL_DV_TOTAL / 1000;
    }
    else
    {
        usDHF = (DWORD)g_usDVFreq * (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 / 1000;
    }

    usIHF = (DWORD)g_stMDomainInputData.usVFreq * g_stMDomainInputData.usVTotal / 1000;
    ulFrameDiff = (DWORD)1000 * ((DWORD)1000 * g_stMDomainInputData.usVFreq - (DWORD)1000 * g_usDVFreq) / ((DWORD)g_stMDomainInputData.usVFreq * g_usDVFreq);
    ulActiveRegionDiff = (DWORD) 1000 * ((DWORD)g_stMDomainOutputData.usVHeight * usIHF - (DWORD)g_stMDomainInputData.usVHeight * usDHF) / ((DWORD)usIHF * usDHF);

    // If((Input frame ahead) < 0.8*(Conflict region)), Then DVT = DVH / ((Input Frame ahead)*0.8 + IVH/IHF) * (1/DVF).
    // Else if(DVH*1.66 < DVT), Then DVT = Panel_DVT.
    // Else DVT = DVH*1.66
    if((ulFrameDiff * 100 / ulActiveRegionDiff) < 125)
    {
        usDVTotal = (DWORD)1000 * g_stMDomainOutputData.usVHeight / ((ulFrameDiff * 100 / 125) + ((DWORD)1000 * g_stMDomainInputData.usVHeight / usIHF)) * 1000 / g_usDVFreq;
    }
    else if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDVTotal = _PANEL_DV_TOTAL;
    }
    else
    {
        usDVTotal = (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000;
    }

    if(usDVTotal > _PANEL_DV_TOTAL_MAX)
    {
        usDVTotal = _PANEL_DV_TOTAL_MAX;
    }
    else if(usDVTotal < _PANEL_DV_TOTAL_MIN)
    {
        usDVTotal = _PANEL_DV_TOTAL_MIN;
    }

    return usDVTotal;
}

//--------------------------------------------------
// Description  : Set OneFrame FRC
// Input Value  : IHF, DHF
// Output Value : None
//--------------------------------------------------
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF)
{
    SWORD shMarginM1 = 0;
    SWORD shMarginM2 = 0;
    WORD usPreRead1 = 0;
    WORD usPreRead2 = 0;
    WORD usLeadingLine = 0;
    WORD usLength = g_stMDomainInputData.usVHeight;
    bit bAutoMode = _ENABLE; // 1:auto mode; 0:manual mode

    if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usVHeight)
    {
        usLength = g_stMDomainOutputData.usVHeight;
    }

    /// 1. Only if meet the following check condition, Write data to Memory:
    /// (1) Input Faster :
    ///      1. When R-FIFO is working check:  (IHP' * Length) > (DHP' * (Remain + Line_Margin)) --> (DHF' * Length) > (IHF' * (Remain + LIne_Margin))
    ///      2. When R-FIFO is idle check:     [W-FIFO starts] before [R-FIFO starts + Margin]
    /// (2) Input Slower :
    ///      1. When R-FIFO is working:  ((IHP' !V DHP') * Length) < (DHP'* (Remain + LIne_Margin)) --> ((DHF' - IHF')* Length) < ((DHF' * (Remain + Line_Margin)))
    ///      2. When R-FIFO is idle: Porch > [(IHP' !V DHP') * Length ] / DHP'
    /// 2. Remain Value:
    /// (1) Input Faster :
    ///    if ( pre_read_trig | (pre_cnt > pre_read_margin) )
    ///       Remain = line_counter
    ///    else
    ///       Remain = 0
    /// (2) Input Slower :
    ///    if ( line_counter < (length-1) )
    ///       Remain = line_counter
    ///    else
    ///       Remain = 0

    // Input Faster Case
    if(ulIHF > ulDHF)
    {
        usPreRead2 = g_stMDomainOutputData.usVStart - _PRE_READ_MEMORY;
        usPreRead1 = (usPreRead2 > 1) ? (usPreRead2 - 1) : 0;

        // Assume IHF_M = 37.48KHz, if input faster, IHF_M set 38, else set 37.
        ulIHF = (ulIHF % 10) ? (ulIHF / 10 + 1) : (ulIHF / 10);

        /// Set Line Merge
        ///      Auto mode : margin to avoid frame tear, range from -2048 to 2047
        ///      Manual mode : decide whether write data to Memory or not
        shMarginM2 = 0x02;
        shMarginM1 = shMarginM2 + 1;

        // Input faster case : DHF * Length
        ulDHF = ulDHF * usLength / 10;
    }
    else
    {
        // Input Slower Case
        // forbidden lines (conflict region)
        usPreRead2 = ((DWORD)g_stMDomainOutputData.usVHeight * ulDHF / ulIHF - g_stMDomainOutputData.usVHeight);
        usPreRead2 = (usPreRead2 < 10) ? 10 : usPreRead2;

        // Input frame leading lines in display (Display Frame Ahead)(uint: display line)
        if(g_stMDomainInputData.usVFreq > _PANEL_MAX_FRAME_RATE)
        {
            usLeadingLine = (DWORD)(g_stMDomainInputData.usVFreq - g_usDVFreq) * _PANEL_DV_TOTAL_MIN / g_stMDomainInputData.usVFreq;
        }
        else if(g_stMDomainInputData.usVFreq < _PANEL_MIN_FRAME_RATE)
        {
            usLeadingLine = (DWORD)(g_usDVFreq - g_stMDomainInputData.usVFreq) * _PANEL_DV_TOTAL_MIN / g_stMDomainInputData.usVFreq;
        }

        if(usPreRead2 <= g_stMDomainOutputData.usVStart)
        {
            /// 1. Set OneFrameFRC control by Manual mode
            ///  --> Write data control by Manual mode:
            ///  * Only if meet the following check condition, Write data to Memory:
            ///      (1)Input Faster: Remain + Line-margin(CRE8, CRE9) < 0.
            ///      (2)Input Slower: Remain + Line-mergin(CRE8, CRE9) > 0.
            /// 2. Set Input Faster mode

            if((usPreRead2 * 15 / 10) < usLeadingLine)
            {
                if((usPreRead2 * 15 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead2 = 0; // PRRD_Margin
                }
                else
                {
                    usPreRead2 = g_stMDomainOutputData.usVStart - usPreRead2 * 15 / 10;
                }
            }
            else if((usPreRead2 * 13 / 10) < usLeadingLine)
            {
                if((usLeadingLine - 1) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead2 = 0;
                }
                else
                {
                    usPreRead2 = g_stMDomainOutputData.usVStart - (usLeadingLine - 1);
                }
            }
            else
            {
                if((usPreRead2 * 13 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead2 = 0;
                }
                else
                {
                    usPreRead2 = g_stMDomainOutputData.usVStart - usPreRead2 * 13 / 10;
                }
            }

            ulIHF = (g_stMDomainInputData.usHFreq % 10) ? (g_stMDomainInputData.usHFreq / 10 + 1) : (g_stMDomainInputData.usHFreq / 10);
            shMarginM2 = (SWORD)0 - (g_stMDomainOutputData.usVHeight - 1);
            shMarginM1 = (shMarginM2 > 1) ? (shMarginM2 - 1) : 0;
            usPreRead1 = (usPreRead2 > 1) ? (usPreRead2 - 1) : 0;

            // Input Slower Case : (DHF - IHF) * Length
            ulDHF = ulDHF * g_stMDomainInputData.usVHeight / 10;
            bAutoMode = _DISABLE;

            // Set Input Faster Mode
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT3, _BIT3);
        }
        else
        {
            usPreRead2 = (DWORD)(_PANEL_DV_TOTAL_MIN - g_stMDomainOutputData.usVHeight) * usLength / g_stMDomainOutputData.usVHeight - 3;
            shMarginM2 = (usPreRead2 > 20) ? (usPreRead2 - 20) : 0;
            shMarginM1 = (shMarginM2 > 1) ? (shMarginM2 - 1) : 0;

            usPreRead2 = usLength;
            usPreRead1 = (usPreRead2 > 1) ? (usPreRead2 - 1) : 0;

            // Input Slower Case : (DHF - IHF) * Length
            ulDHF = (ulDHF - ulIHF) * usLength / 10;
            ulIHF = (DWORD)ulIHF / 10;
        }
    }

    // Set FRC M1/M2
    ScalerSetByte(P5_B1_DISP_M1_ONEF_DHF_H, ((ulDHF >> 16) | ((BYTE)bAutoMode << 6) | (_BIT7)));
    ScalerSetByte(P5_B2_DISP_M1_ONEF_DHF_M, (BYTE)(ulDHF >> 8));
    ScalerSetByte(P5_B3_DISP_M1_ONEF_DHF_L, (BYTE)ulDHF);
    ScalerSetByte(P5_B4_DISP_M1_ONEF_IHF, (BYTE)ulIHF);
    ScalerSetByte(P5_B5_DISP_M1_LINE_MAGN_L, LOBYTE(shMarginM1));
    ScalerSetByte(P5_B6_DISP_M1_ONEF_MAGN_H, (((HIBYTE(shMarginM1) << 4) & 0xF0) | (HIBYTE(usPreRead1) & 0x0F)));
    ScalerSetByte(P5_B7_DISP_M1_ONEF_MAGN_L, LOBYTE(usPreRead1));

    ScalerSetByte(P45_B1_DISP_M2_ONEF_DHF_H, ((ulDHF >> 16) | ((BYTE)bAutoMode << 6) | (_BIT7)));
    ScalerSetByte(P45_B2_DISP_M2_ONEF_DHF_M, (BYTE)(ulDHF >> 8));
    ScalerSetByte(P45_B3_DISP_M2_ONEF_DHF_L, (BYTE)ulDHF);
    ScalerSetByte(P45_B4_DISP_M2_ONEF_IHF, (BYTE)ulIHF);
    ScalerSetByte(P45_B5_DISP_M2_LINE_MAGN_L, LOBYTE(shMarginM2));
    ScalerSetByte(P45_B6_DISP_M2_ONEF_MAGN_H, (((HIBYTE(shMarginM2) << 4) & 0xF0) | (HIBYTE(usPreRead2) & 0x0F)));
    ScalerSetByte(P45_B7_DISP_M2_ONEF_MAGN_L, LOBYTE(usPreRead2));

    // Write in double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~(_BIT4), _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~(_BIT4), _BIT4);

    // Disable Osd Overlay In Case of Garbage
    pData[0] = ScalerGetByte(P0_6C_OVERLAY_CTRL);
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, 0x00);

    // Set Frame sync
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // Set Free Run
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

    // Enable Osd Overlay In Case of Garbage
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, (pData[0] & _BIT0));
}

//--------------------------------------------------
// Description  : Wait Capture Write Memory Block Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCWaitWriteFrameBufFinish(void)
{
    if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
    {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(GET_ROT_TYPE() != _ROT_DISABLE)
        {
            // Get FRC Capture Block Index
            pData[0] = ScalerGetBit((P5_2A_CAP_M1_STATUS), _BIT6);

            // Wait Write Data
            ScalerTimerPollingFlagProc(50, P5_2A_CAP_M1_STATUS, _BIT6, ((~pData[0]) & _BIT6));
            ScalerTimerPollingFlagProc(50, P5_2A_CAP_M1_STATUS, _BIT6, ((pData[0]) & _BIT6));
            ScalerTimerPollingFlagProc(50, P5_2A_CAP_M1_STATUS, _BIT6, ((~pData[0]) & _BIT6));
        }
        else
#endif
        {
            // Get FRC Capture Block Index
            pData[0] = ScalerGetBit((P5_2A_CAP_M1_STATUS), _BIT6);

            // Wait Write Data
            ScalerTimerPollingFlagProc(50, (P5_2A_CAP_M1_STATUS), _BIT6, ((~pData[0]) & _BIT6));
            ScalerTimerPollingFlagProc(50, (P5_2A_CAP_M1_STATUS), _BIT6, ((pData[0]) & _BIT6));
        }

        ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC freeze mode
// Input Value  : ON --> Freeze
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayFreeze(bit bEn)
{
    ScalerTimerWaitForEvent(_EVENT_IEN_STOP);

    if(bEn == _ON)
    {
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT2, _BIT2);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT2, _BIT2);
    }
    else
    {
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT2, 0x00);
        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT2, 0x00);
    }
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : D Domain Source Select
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect)
{
    if(enumSourceSelect == _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE)
    {
        // Set Frame sync with line buffer mode
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), _BIT2);
        ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), _BIT2);
    }
    else
    {
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
        ScalerSetBit(P45_AC_DISP_M2_DISP_CTRL1, ~(_BIT2 | _BIT1), 0x00);
    }

    // Enable Double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~(_BIT4), _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~(_BIT4), _BIT4);
}

