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
// ID Code      : RL6463_Series_MDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
void ScalerMDomainControlDBApply(void);
bit ScalerMDomainMemoryCheck(void);
void ScalerMDomainDisplayTimingGenDBApply(EnumDBApply enumDBApply);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Special Double Buffer Apply Procedure for FS
// Input Value  : None
// Output Value : None
// Note : Only for Frame Sync case
//--------------------------------------------------
void ScalerMDomainControlDBApply(void)
{
    bit bFreeRunEn = _FALSE;

    // Enable double buffer
    if((GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) || (GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY))
    {
        if(ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT1) == _BIT1)
        {
            // Avoid (Current_IVStart + IVHeight) > IVToal + New_IVSDelay in digital capture
            PDATA_WORD(0) = (g_stInputTimingData.usVStart + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
        }
        else
        {
            // Avoid (Current_IVSDelay + IVStart + IVHeight) > IVToal + New_IVSDelay in analog capture
            PDATA_WORD(0) = (ScalerVgipGetCaptureVDelay() + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
        }

        bFreeRunEn = (PDATA_WORD(0) > g_stMDomainInputData.usVTotal) ? (_TRUE) : (_FALSE);


        if(bFreeRunEn == _TRUE)
        {
            ScalerTimerWaitForEvent(_EVENT_DEN_START);

            // Set Free run
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, 0x00);
        }

        // I-domain & D-domain apply polling
        ScalerGlobalIDDomainDBApply(_DB_APPLY_POLLING);

        if(bFreeRunEn == _TRUE)
        {
            if(GET_MEMORY_DVF_SELECT() == _1_IVF)
            {
                ScalerTimerWaitForEvent(_EVENT_IVS);
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

                // Set Frame sync
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            }
        }
    }
    else
    {
        // I-domain & D-domain apply polling
        ScalerGlobalIDDomainDBApply(_DB_APPLY_POLLING);
    }
}

//--------------------------------------------------
// Description  : Check memory
// Input Value  : None
// Output Value : Memory check pass or fail
//--------------------------------------------------
bit ScalerMDomainMemoryCheck(void)
{
    // Check fifo under/overflow and Input HVsync error flag, Display Vsync timeout flag
    if((ScalerGetBit(P0_02_STATUS0, (_BIT6 | _BIT5 | _BIT1 | _BIT0)) != 0x00) || (ScalerGetBit(P0_0C_WATCH_DOG_CTRL0, _BIT0) != 0x00))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Apply Display Timing Gen Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainDisplayTimingGenDBApply(EnumDBApply enumDBApply)
{
    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Check if Display Timing Gen DB is enabled
        if(ScalerGetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, _BIT7) == 0x00)
        {
            return;
        }

        // Check D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            // Disable Double Buffer
            ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT7, 0x00);
            return;
        }

        // Apply Display Timing Gen Double Buffer
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT6, _BIT6);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            // Wait Display Timing Gen double buffer
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, _BIT6, 0) == _FALSE)
            {
                // Disable Double Buffer
                ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT7, 0x00);
            }
        }
    }
}

