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
// ID Code      : BEA2014Ddcci.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_DDCCI__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#define _DDCCI_FIRMWARE_VERSION                     0x01

#define _DDCCI_BLACKLEVEL_DEFAULT                   0x50

// RC
#define _DDCCI_CMD_GETVCP_RC_NO_ERROR               0x00
#define _DDCCI_CMD_GETVCP_RC_UNSUPPORTED            0x01

// TP
#define _DDCCI_CMD_GETVCP_TP_SET_PARAMETER          0x00
#define _DDCCI_CMD_GETVCP_TP_MOMENTARY              0x01

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _COLORTEMP_USER_MAX                         255
#define _COLORTEMP_USER_MIN                         0
#define _COLORTEMP_USER_CENTER                      (((_COLORTEMP_USER_MAX - _COLORTEMP_USER_MIN) / 2) + _COLORTEMP_USER_MIN)

//--------------------------------------------------
// For DDCCI Set Input Port
//--------------------------------------------------
#if(_PCB_TYPE == _RL6432_DHWANNI_A_156PIN_1DP1HDMI_LVDS)

#define _VGA_1                                      _NO_INPUT_PORT
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D1_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D3_INPUT_PORT
#define _HDMI_2                                     _NO_INPUT_PORT
#else

#define _VGA_1                                      _A0_INPUT_PORT
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D0_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT
#endif

//--------------------------------------------------
// Dell DDM Tool
//--------------------------------------------------
#define _DDCCI_OPCODE_VCP_DELL_DDM_SUPPORT          0xF1


//--------------------------------------------------
// Beacon Function
//--------------------------------------------------
#define _DDCCI_BYPASS_PARAMTER			0x00
#define _DDCCI_COLOR1_PARAMTER			0x01
#define _DDCCI_COLOR2_PARAMTER			0x02
#define _DDCCI_COLOR3_PARAMTER			0x03

/*Bits define for kPos_Info_SupportDicom2*/
#define kBIT_DICOM_300 	0x01 
#define kBIT_DICOM_350 	0x02
#define kBIT_DICOM_400 	0x04
#define kBIT_DICOM_450 	0x08
#define kBIT_DICOM_500 	0x10
#define kBIT_DICOM_550 	0x20
#define kBIT_DICOM_600 	0x40
#define kBIT_DICOM_650 	0x80

/*Bits define for kPos_Info_SupportGamma1*/
#define kBIT_DICOM_700 	0x01
#define kBIT_DICOM_750 	0x02
#define kBIT_DICOM_800 	0x04
#define kBIT_DICOM_850 	0x08

#define kBIT_DICOM_100 	0x10
#define kBIT_DICOM_150 	0x20
#define kBIT_DICOM_200 	0x40
#define kBIT_DICOM_250 	0x80

#define kBIT_DICOM_SKIP 0x00 

#if(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
//(_ENABLE_MULTIPLE_DICOM_SUPPORT == _ON)   
#define Dicom_sup1	( kBIT_DICOM_300 |kBIT_DICOM_350 |kBIT_DICOM_400 |kBIT_DICOM_450 |kBIT_DICOM_500 |kBIT_DICOM_550 |kBIT_DICOM_600)
#define Dicom_sup2	( kBIT_DICOM_200 |kBIT_DICOM_250) 
#else // one Dicom
      #ifndef Dicom_sup1
      #define Dicom_sup1    0x08// kBIT_DICOM_450  
      #endif
      #ifndef Dicom_sup2
      #define Dicom_sup2	0x00 
      #endif
#endif

#if (_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)
typedef struct
{
   BYTE lut_id; 
   Lut_Attri lut_attri; 
}LutAttriElem;

typedef struct
{
    WORD r;
    WORD g;
    WORD b;
    BYTE integration_time;
}SENSOR_DATA;

typedef struct
{
	SDWORD Matrix_elem_X; 
	SDWORD Matrix_elem_Y; 
	SDWORD Matrix_elem_Z; 
}MatrixElem;

typedef struct
{
	SDWORD Matrix_Para_r1; 
	SDWORD Matrix_Para_r2; 
	SDWORD Matrix_Para_r3; 
	SDWORD Matrix_Para_g1; 
	SDWORD Matrix_Para_g2; 
	SDWORD Matrix_Para_g3; 
	SDWORD Matrix_Para_b1; 
	SDWORD Matrix_Para_b2; 
	SDWORD Matrix_Para_b3; 
}MatrixPara_SENSOR;

typedef enum
{
    _DEVICE_ID_NONE,
    _DEVICE_ID_TCS3414,   
    _DEVICE_ID_MTCSCDCAF,   
    _DEVICE_ID_TCS3430,   
    _DEVICE_ID_VEML3328,   
    _DEVICE_ID_AMOUNT,
}EnumFSensorDeviceID;

typedef enum 
{
    GAIN_1X,
    GAIN_4X,   	
    GAIN_16X,  
    GAIN_64X,   
};

MatrixPara_SENSOR MatrixPara_sensorData;
static MatrixElem MatrixElem_FSensorData;
SENSOR_DATA sensor_data;
BYTE multi = 1;
BYTE g_ucDisplayModeBackup = 0;
BYTE g_ucAspectRatioTypeBackup = 0;

	
BYTE FSensor_integrationTime=0;
BYTE FSensor_Gain=0;
bit RefreshMatrix=0;
BYTE g_bFrontSensorInitState = _DEVICE_ID_NONE;

static BYTE I2CReadPtr[8]={0,0,0,0,0,0,0,0};


#define _FT_LutAttriElemSize				(sizeof(Lut_Attri))
#define _FT_MatrixSize						(36)
#define _FT_CorrespondeceTableSize			(256)
#define _FT_GSDFSize						(0x2000)
#define _FT_CustomDataSize					(0x800)  //2048

#define _FT_MonitorModelSize				(13)  // EDID Spec Max

#define _FT_Ch_MatrixSize  			        (_FT_MatrixSize/3)

#define _FT_GammaNameInfoSize			    (256)

// AT24C128B:128K (16,384 x 8)  Total=0x4000
// E2PROM address
#define _FT_MONITORSN_ADDRESS  				(_MONITOR_SN_DATA_ADDRESS) // (0x600)   //  25
#define _FT_MATRIX_ADDRESS  				(0x630)   //  36
#define _FT_CORRESPONDENCE_ADDRESS  	    (0x660)   //  256
#define _FT_GSDF_ADDRESS 					(0x800)   //  0x2000

//#define _FT_LUTATTRIELEM_VERSION_ADDRESS    (0x2800)
//#define _FT_LUTATTRIELEM_ADDRESS 			(0x2802)  //  _GAMMA_AMOUNT * 2CT * sizeof(Lut_Attri)

#define _FT_CUSTOM_DATA_ADDRESS 			(0x3000)  //  for DBI Custom data 2048 Byte

//Gamma Lut save to Flash or EEPROM

#define ORDER_PART_DATE_LEN                 112
#define ORDER_PART2_DATE_LEN                22

//Version: 3.0
#define	SENSOR_VERSION_MAJOR			    5
#define	SENSOR_VERSION_MINOR			    1
 
/*See TCS3414 spec for details*/
#define	CMD_VALUE						    0x80
#define	TRANS_BYTE_PROTOC				    0x00
#define	TRANS_BLOCK_PROTOL				    0x40

#define	CMD_SS_CONTROL					    0x00
#define	CMD_SS_TIMING					    0x01
#define	CMD_SS_ANALOG 					    0x07
#define	CMD_SS_DATA1LOW   			        0x10


#define	DICOM_SURPORT_TYPE1				    (0X01)
#define	DICOM_SURPORT_TYPE2				    (0X00)

#define	COLORTEMP_SURPORT_TYPE1			    (0XFF)
#define	COLORTEMP_SURPORT_TYPE2			    (0X00)

#endif



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
BYTE code tCOLORPRESET_VALUE[] = {0x08, 0x06, 0x05, 0x04, 0x01, 0x0B, 0x02};

BYTE code tLANGUAGEDEFINE[] = {0x02, 0x03, 0x04, 0x0A, 0x08, 0x05, 0x0B, 0x1E, 0x09, 0x06, 0x0F, 0x0D};//{0x02, 0x01, 0x03, 0x04, 0x0A, 0x0D, 0x06};
/*
//----------------------- gamma:off   2.2  DICOM USER  CALIB 
BYTE code tGAMMASET_VALUE[] = 
{
#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
0x00, 0x01, 0x02, 0x03, 0x04
//off 2.2   dicom user  calib
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x0B
//OFF  2.0   2.2  2.4   2.6   DICOM
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x10,
//off 1.8   200   250   300   350   400   450   500   550   600   calib
#endif
};
*/
BYTE code C_HWVersion[] = HW_VERSION;
BYTE code C_FWVersion[] = FW_VERSION;


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucDdcciRedBlackLevel   = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciGreenBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciBlueBlackLevel  = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciNewControlValue = 1;
BYTE g_ucDdcciActiveValue;
BYTE g_ucColorTempUnSupport;


#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
bit g_bForceSwitchSourceStatus = _FALSE;
#endif

bit g_bForcePowSavStatus = _FALSE;
bit g_bForceBackupStatus = _FALSE;
BYTE g_ucPanelUniformityCalibrationData = _FAIL; // Panel Uniformity Calibration data
#if 1//(_ARM_MCU_CALIBRATION_SUPPORT)
BYTE g_ucScalerSendMcuData = 0xFF;
bit g_bPCAppCalibrationFlag = _FALSE;
#endif
bit g_bForceAutoSwitchEDIDStatus = _TRUE;  // force Auto Switch EDID data

#if ((_BEACON_GAMMA_AUTO_PROCESS_SUPPORT == _ON) || (_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON))    
// DDCCI CMD Check Flag ->_DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS
// DDCCI CMD Check Flag ->_DDCCI_SENSOR_CALIB_GET_ORDER_STATUS
/*static*/ bit E_OrderStatus=0;         
#endif

#if (_ENABLE_BACKLIGHT_SENSOR)
extern BYTE g_bBacklightSensorInitState; 
extern bit g_bBacklightSensorValueRestoreStatus; 
extern BYTE uctemperaturesensor;
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern WORD g_usHLWinHPos;
extern WORD g_usHLWinHWidth;
extern WORD g_usHLWinVPos;
extern WORD g_usHLWinVHeight;
#endif

#if(_ENABLE_AMBIENTLIGHT_SENSOR)
extern BYTE g_bAmbiSensorInitState;
extern BYTE ALC_state;
extern WORD Lum_RealUsing;  //Basis for Confirming the Info By DDC/CI
extern WORD Lum_Real;      //The value that is most closest to real luminance(Not stable)
#endif


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserDdcciHandler(void);
void RTDDdcciGetVCPFeature(void);
bit RTDDdcciSetVCPFeatureCheck(void);
void RTDDdcciSetVCPFeature(void);
void RTDDdcciResetAllSettings(void);
void RTDDdcciColorReset(void);

//--------------------------------------------------
// Beacon Function
//--------------------------------------------------
#if (_ENABLE_BACKLIGHT_SENSOR)
extern void InitBacklightSensorModule(void);
extern WORD ReadBacklightSensorValue(BYTE ucChannel);
extern WORD UserGetBacklightSensorTargetValue(void);
#endif
extern WORD AmbiSensor_VEML6030_ReadLux(void);

void RTDDdcciFactoryGammaAutoProcess(void);
void RTDDdcciFactoryColorSensorProcess(void);
#if (_ENABLE_BACKLIGHT_SENSOR)
extern void UserTemperatureSensorHandler(void);
#endif

extern void OsdDispDdcInfo(void);   //Addbed by KW

//--------------------------------------------------

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserDdcciHandler(void)
{
#if ((_BEACON_GAMMA_AUTO_PROCESS_SUPPORT == _ON)||(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON))    
	BYTE IsChecksumOK = _FALSE;
    BYTE ucChecksumIdx = 0;
#endif

    if(GET_OSD_DDCCI_STATUS() == _ON)
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
        {
#if 0//((_PRODUCT_ID_SEL == RTD2785TM_G310S_RL6432_216PIN_BEACON_A_STD_R213RCE_LU1_LVDS_PWM) || (RTD2785TM_C510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU2_LVDS_PWM))
            OsdDispDdcInfo();
#endif

        #if ((_BEACON_GAMMA_AUTO_PROCESS_SUPPORT == _ON)||(_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON))    
			ucChecksumIdx = (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) + 2; // 0x51, length
			if(UserCommonDdcciCalRxCheckSum() == g_pucDdcciRxBuf[ucChecksumIdx])
			{
				IsChecksumOK = _TRUE;
			}
        #endif

		#if (defined(_PROTOCOL_DBI_COLOR_SENSOR_CALIBRATION))
            if((g_pucDdcciRxBuf[_DDCCI_COMMAND] == 0xC2 ) && (g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE] == _DDCCI_SENSOR_CALIB_GET_PROTOCOL_INFOR))
        	{
        	    // Set _DDCCI_CMD_COLOR_SENSOR_CALIBRATION
				g_pucDdcciRxBuf[_DDCCI_COMMAND] = 0xC3;
			}
		#endif
        
            switch(g_pucDdcciRxBuf[_DDCCI_COMMAND])
            {
                case _DDCCI_CMD_GET_VCP_FEATURE:
                    RTDDdcciGetVCPFeature();
                    break;

                case _DDCCI_CMD_SET_VCP_FEATURE:
                    RTDDdcciSetVCPFeature();
                    break;

                case _DDCCI_CMD_GET_TIMING_REPORT:
                    UserCommonDdcciGetTimingReport();
                    break;

                case _DDCCI_CMD_SAVE_CURRENT_SETTINGS:
                    break;

                case _DDCCI_CMD_CAPABILITIES_REQUEST:
                    UserCommonDdcciGetCapabilitiesRequest();
                    break;
                    
               #if (_BEACON_GAMMA_AUTO_PROCESS_SUPPORT == _ON)// for beacon gamma auto processing function     
                case _DDCCI_CMD_FACTORY_GAMMA_AUTO_PROCESS:
                    if(IsChecksumOK)
                    {
                        RTDDdcciFactoryGammaAutoProcess();
                    }
                    break;
               #endif
               
               #if (_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)// for beacon color sensor calibration function     
                case _DDCCI_CMD_COLOR_SENSOR_CALIBRATION:
                    if(IsChecksumOK)
                    {
                        RTDDdcciFactoryColorSensorProcess();
                    }
                    break;
               #endif

                default:
                    UserCommonDdcciInitTx();
                    break;
            }
            UserCommonDdcciInitRx();

            SET_RUN_DDCCI_COMMAND(_FAIL);
        }
    }
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    else
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if((GET_RUN_DDCCI_COMMAND() == _SUCCESS) && (UserCommonInterfaceGetDpMstCapablePort() != _DP_MST_NO_PORT))
        {
            UserCommonDdcciInitTx();
            SET_RUN_DDCCI_COMMAND(_FAIL);
        }
    }
#endif
}

#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get custom capability string data
// Input Value  : pucDest -> destination
//                enumPortType -> port type
//                usStartIndex -> data offset
//                usLength -> data length
// Output Value : None
//--------------------------------------------------
void UserInterfaceDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength)
{
    pucDest = pucDest;
    enumPortType = enumPortType;
    usStartIndex = usStartIndex;
    usLength = usLength;
}

//--------------------------------------------------
// Description  : Get custom capability string size
// Input Value  : enumPortType -> port type
// Output Value : size
//--------------------------------------------------
WORD UserInterfaceDdcciGetCpStringSize(EnumInputPortType enumPortType)
{
    enumPortType = enumPortType;
    return 0;
}
#endif

//--------------------------------------------------
// Description  : DDCCI Get VCP Feature & VCP Feature Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciGetVCPFeature(void)
{
    BYTE pucTemp[2] = {0};
	BYTE Cmd_Reply = 0x00;

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY;
    g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_NO_ERROR;
    g_pucDdcciTxBuf[_DDCCI_SINK_OPCODE] = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE];
    //DebugMessageUart("GetVCP:", g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]);
    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0002, g_ucDdcciNewControlValue);
            break;

        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_TEMP_INCREMENT:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, 100);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST:
            switch(GET_COLOR_TEMP_TYPE())
            {
                case _CT_SRGB:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (40 - 30));
                    break;

                case _CT_9300:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (93 - 30));
                    break;

                case _CT_7500:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (75 - 30));
                    break;

                case _CT_6500:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (65 - 30));
                    break;

                case _CT_5800:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (50 - 30));
                    break;

                default:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (65 - 30));
                    break;
            }
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK:

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_CLOCK());
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                BYTE ucClock = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                ucClock = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, ucClock);
            }
#endif
            break;

#endif // End of #if(_VGA_SUPPORT == _ON)

        case _DDCCI_OPCODE_VCP_BACKLIGHT:
           // UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,
              //                              (WORD)UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,GET_OSD_BACKLIGHT());

           break;

        case _DDCCI_OPCODE_VCP_CONTRAST:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,
                                            (WORD)UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000B,
                                            tCOLORPRESET_VALUE[GET_COLOR_TEMP_TYPE()]);
            break;

        case _DDCCI_OPCODE_VCP_GAMMA:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x001F, GET_OSD_GAMMA());
            break;

        case _DDCCI_OPCODE_VCP_RED_GAIN:
            pucTemp[0] = GET_COLOR_TEMP_TYPE();

            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(_CT_USER);

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }

            pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, pucTemp[1]);

            SET_COLOR_TEMP_TYPE(pucTemp[0]);

            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _DDCCI_OPCODE_VCP_GREEN_GAIN:
            pucTemp[0] = GET_COLOR_TEMP_TYPE();

            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(_CT_USER);

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }

            pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, pucTemp[1]);

            SET_COLOR_TEMP_TYPE(pucTemp[0]);

            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _DDCCI_OPCODE_VCP_BLUE_GAIN:
            pucTemp[0] = GET_COLOR_TEMP_TYPE();

            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(_CT_USER);

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }

            pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, pucTemp[1]);

            SET_COLOR_TEMP_TYPE(pucTemp[0]);

            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_AUTO_COLOR:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, 0x01);
            break;
#endif

        case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_H_POSITION());
            }
            else
#endif
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_DIGITAL_H_POSITION());
            }

            break;

        case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_V_POSITION());
            }
            else
#endif
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_DIGITAL_V_POSITION());
            }
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK_PHASE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_PHASE());
            break;
#endif

        case _DDCCI_OPCODE_VCP_ACTIVE_CONTROL:
            break;

        case _DDCCI_OPCODE_VCP_INPUT_SOURCE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x03, OsdDispJudgeSourceType());
            break;

#if(_AUDIO_SUPPORT == _ENABLE)
        case _DDCCI_OPCODE_VCP_AUDIO_VOLUME:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_OSD_VOLUME());
            break;
#endif

        case _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciRedBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciGreenBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciBlueBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_PRODUCTKEY:
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 9;
            g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY;
            break;

        case _DDCCI_OPCODE_VCP_HFREQ:
            // For softMCCS & MonInfo
            // PDATA_DWORD(0) = (DWORD)GET_INPUT_TIMING_HFREQ() * 100;
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, HIWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)), LOWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)));
            break;

        case _DDCCI_OPCODE_VCP_VFREQ:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, GET_INPUT_TIMING_VFREQ()*10);
            break;

        case _DDCCI_OPCODE_VCP_PANEL_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, 1);
            break;

        case _DDCCI_OPCODE_VCP_MONITOR_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x05, 3);
            break;

        case _DDCCI_OPCODE_VCP_USAGE_TIME:
			// MCCS: (in hours) by the display in the ML, SH and SL bytes. The MH byte must be set to 00h
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, GET_PANEL_TIME_HOUR());
            break;

        case _DDCCI_OPCODE_VCP_APPLICATION_ENABLE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFF, 0x5a);
            break;

        case _DDCCI_OPCODE_VCP_CONTROLLER_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, 0x0009);
            break;

        case _DDCCI_OPCODE_VCP_FW_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, _DDCCI_FIRMWARE_VERSION);
            break;

        case _DDCCI_OPCODE_VCP_OSD_ON_OFF:
#if(_TRANSLATOR_SUPPORT == _OFF)
            if(ScalerOsdGetOsdEnable() == _TRUE)
            {
                pucTemp[0] = 2;
            }
            else
#endif
            {
                pucTemp[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x02, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0D, tLANGUAGEDEFINE[GET_OSD_LANGUAGE()]);
            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:
            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                pucTemp[0] = 5;
            }
            else if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
            {
                pucTemp[0] = 4;
            }
            else
            {
                pucTemp[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0005, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_VERSION:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, 0x0202);
            break;

        case _DDCCI_OPCODE_VCP_SHARPNESS:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0004, GET_OSD_SHARPNESS());
            break;

        case _DDCCI_OPCODE_VCP_DELL_DDM_SUPPORT:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, 0x01);
            break;

		case _DDCCI_OPCODE_VCP_BEACON_HW_VERSION:
            // Write: 6e 51 82 01 E6 CheckSum  Length = 3
            // Read: Length = 27  6e 99 + ASCII
			{
				Cmd_Reply = 1;
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(_SN_BUF_LENGTH)); // Length 0x80|(data(25))

			    // Clear buffer for new message
			    memset(&g_pucDdcciTxBuf[2], 0, _SN_BUF_LENGTH);
				memcpy(&g_pucDdcciTxBuf[2], C_HWVersion, strlen(C_HWVersion));

            	g_pucDdcciTxBuf[2 + _SN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum
            	
	            ScalerMcuDdcciSendData( g_pucDdcciTxBuf);
			}
			break;

		case _DDCCI_OPCODE_VCP_BEACON_FW_VERSION:
            // Write: 6e 51 82 01 E7 CheckSum  Length = 3
            // Read: Length = 27  6e 99 + ASCII
			{
				Cmd_Reply = 1;
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(_SN_BUF_LENGTH)); // Length 0x80|(data(25))

			    // Clear buffer for new message
			    memset(&g_pucDdcciTxBuf[2], 0, _SN_BUF_LENGTH);
				memcpy(&g_pucDdcciTxBuf[2], C_FWVersion, strlen(C_FWVersion));

            	g_pucDdcciTxBuf[2 + _SN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum
            	
	            ScalerMcuDdcciSendData( g_pucDdcciTxBuf);
			}
			break;
		
        case _DDCCI_OPCODE_VCP_BEACON_MONITOR_SN:
			{
				Cmd_Reply = 1;
				
	        	g_pucDdcciTxBuf[0] = _DDCCI_DEST_ADDRESS;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(_SN_BUF_LENGTH));  // Length 0x80|(data(25))

			    // Clear buffer for new message
			    memset(&g_pucDdcciTxBuf[2], 0, _SN_BUF_LENGTH);
				RTDNVRamLoadMonitorSNData(&g_pucDdcciTxBuf[2]);  
	        	g_pucDdcciTxBuf[2 + _SN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum

	            ScalerMcuDdcciSendData( g_pucDdcciTxBuf);
			}
			break;

        default:
            g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_UNSUPPORTED;
            break;
    }

	if(Cmd_Reply == 1)
	{
      // NULL
	}
	else
	{
        g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE + 1] = UserCommonDdcciCalCheckSum();

        ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
	}
}

//--------------------------------------------------
// Description  : Check DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDDdcciSetVCPFeatureCheck(void)
{
    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
        case _DDCCI_OPCODE_VCP_COLOR_RESET:

            if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0)
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
        case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
        case _DDCCI_OPCODE_VCP_AUTO_COLOR:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 3))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x0E))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x26))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x06))
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciSetVCPFeature(void)
{
    BYTE ucTemp = 0;
    //DebugMessageUart("SetVCP:", g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]);
    //DebugMessageUart("SetVCP:", g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
    
    if(RTDDdcciSetVCPFeatureCheck() == _FAIL)
    {
        UserCommonDdcciInitTx();
    }
    else
    {
        switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
        {
            case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    g_ucDdcciNewControlValue = 0x01;
                }

                break;

            case _DDCCI_OPCODE_VCP_SOFT_CONTROLS:
		        //  New Tool V1.4 Menu:0 Right:1 Left:2 Exit:3 OK:4 LightBox:5 Source:6 Up:7 Down:8 CT:0x92 Gamma:0x91 Display Mode:0xA5

                // _Menu:  6e 51 84 03 03 00 00 Checksum
    			if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] < _KEY_AMOUNT)
    			{
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                    {
                    case 1:
                        SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
                        break;

                    case 2:
                        SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
                        break;

                    case 3:
                        SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
                        break;

                    case 4:
                        SET_KEYMESSAGE(_EXIT_KEY_MESSAGE);
                        break;

                    case 5:
                        SET_KEYMESSAGE(_OK_KEY_MESSAGE);
                        break;
                    default:
                        break;
                }    			
    				//SET_KEYMESSAGE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE-1]);
    			}
                break;
                
#if(_SHARPNESS_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_SHARPNESS:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 4)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 4;
                }
                SET_OSD_SHARPNESS(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserCommonAdjustSharpness(SysSourceGetInputPort());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#endif

            case _DDCCI_OPCODE_VCP_INPUT_SOURCE:

                // VGA:  6e 51 84 03 60 00 01 Checksum
                // DP1:  6e 51 84 03 60 00 0F Checksum
                // DP2:  6e 51 84 03 60 00 10 Checksum
                // HDMI1:6e 51 84 03 60 00 11 Checksum
                // HDMI2:6e 51 84 03 60 00 12 Checksum
                // DVI1: 6e 51 84 03 60 00 03 Checksum
                // DVI2: 6e 51 84 03 60 00 04 Checksum

                if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
                {
                    if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                    {
                        SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                    }
                }
                
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_VGA_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x03)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DVI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x04)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DVI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x0F)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DP_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
                    SET_FORCE_SWITCH_SOURCE_STATUS(_TRUE);
#endif
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x10)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DP_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x11)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_HDMI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
#if(_PRODUCT_ID_SEL == RTD2556T_DHWANNI_RL6432_156PIN_A_PHILIPS_G101ICE_L01_LVDS_PWM)
                    SET_FORCE_SWITCH_SOURCE_STATUS(_TRUE);
#endif
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x12)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_HDMI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                break;

            case _DDCCI_OPCODE_VCP_FACTORY_RESET:

                RTDDdcciResetAllSettings();

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    UserCommonAutoConfig();
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(50);
                    SET_DIGITAL_V_POSITION(50);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

            case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:

                RTDNVRamRestoreBriCon();
                RTDNVRamRestoreBacklight();

                UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
                break;

            case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    UserCommonAutoConfig();
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(50);
                    SET_DIGITAL_V_POSITION(50);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

            case _DDCCI_OPCODE_VCP_COLOR_RESET:

                RTDDdcciColorReset();

                break;

            case _DDCCI_OPCODE_VCP_FACTORY_TV_RESET:
                OsdDispDisableOsd();
                                
                RTDNVRamWholeRestore();                
                
                SET_OSD_STATE(_MENU_NONE);            
#if(_DP_MST_SUPPORT == _ON)
               UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() != _SOURCE_NONE)
                {
                    UserCommonAutoConfig();
                }
                
#endif
                break;
				
            case _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST:

                g_ucColorTempUnSupport = (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] + 30);
                if(g_ucColorTempUnSupport >= 93)
                {
                    SET_COLOR_TEMP_TYPE(_CT_9300);
                }
                else if((g_ucColorTempUnSupport < 85) && (g_ucColorTempUnSupport >= 75))
                {
                    SET_COLOR_TEMP_TYPE(_CT_7500);
                }
                else if((g_ucColorTempUnSupport < 75) && (g_ucColorTempUnSupport >= 65))
                {
                    SET_COLOR_TEMP_TYPE(_CT_6500);
                }
                else if((g_ucColorTempUnSupport < 60) && (g_ucColorTempUnSupport >= 50))
                {
                    SET_COLOR_TEMP_TYPE(_CT_5800);
                }
                else
                {
                    SET_COLOR_TEMP_TYPE(_CT_SRGB);
                }

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                OsdDispDisableOsd();

                break;

            case _DDCCI_OPCODE_VCP_CLOCK:

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
                    SET_VGA_MODE_ADJUST_CLOCK(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#else
                    {
                        WORD usClockRangeMax = 0;
                        WORD usClockRangeMin = 0;

                        usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                        usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);

                        SET_VGA_MODE_ADJUST_CLOCK(UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin)));
                    }
#endif
                    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif // End of #if(_VGA_SUPPORT == _ON)

                break;

            case _DDCCI_OPCODE_VCP_BACKLIGHT:
                // BACKLIGHT:  6e 51 84 03 10 00 32 Checksum

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                //SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE], _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
                SET_OSD_BACKLIGHT(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserAdjustBacklight(GET_OSD_BACKLIGHT());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;

            case _DDCCI_OPCODE_VCP_BACKLIGHT_PWM_FREQ:
                // 6e 51 84 03 6A 01 14 c7 ->2000Hz
                // 6e 51 84 03 6A 02 64 b4 ->20KHz
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 255)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 255;
                }

                if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x01)
				{
                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 100));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x02)
				{
                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x04)
				{
                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 120));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x05)
				{
                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 240));
				}
                else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x10)
				{
                    ScalerMcuPwmAdjustFrequency(_PWM0, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x20)
				{
                    ScalerMcuPwmAdjustFrequency(_PWM1, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x30)
				{
                    ScalerMcuPwmAdjustFrequency(_PWM2, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x40)
			    {
                    ScalerMcuPwmAdjustFrequency(_PWM3, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x50)
			    {
                    ScalerMcuPwmAdjustFrequency(_PWM4, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
				else if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]==0x60)
			    {
                    ScalerMcuPwmAdjustFrequency(_PWM5, ((DWORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 200));
				}
                break;
                
            case _DDCCI_OPCODE_VCP_CONTRAST:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE], _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);

                break;

            case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x0B:
                        SET_COLOR_TEMP_TYPE(_CT_USER);
                        break;

                    case 0x05:
                        SET_COLOR_TEMP_TYPE(_CT_6500);
                        break;

                    case 0x08:
                        SET_COLOR_TEMP_TYPE(_CT_9300);
                        break;

                    case 0x01:
                        SET_COLOR_TEMP_TYPE(_CT_SRGB);
                        break;

                    case 0x04:
                        SET_COLOR_TEMP_TYPE(_CT_5800);
                        break;

                    case 0x06:
                        SET_COLOR_TEMP_TYPE(_CT_7500);
                        break;
                    /*
                    case 0x02:
                        SET_COLOR_TEMP_TYPE(_CT_OFF);
                        break;
                    */
                    default:
                        break;
                }

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                OsdDispDisableOsd();
#if((_OSD_TYPE == _BEACON_2014_OSD)&&(_BEACON_GAMMA_PCM_PARTITION_SUPPORT == _ON))
			    if(UserCommonNVRamGetSystemData(_OGCOCC_SEL_BEACON) == _ON)
		        {
#if(_GAMMA_FUNCTION == _ON)
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                    if(GET_OSD_GAMMA() != _GAMMA_OFF)
                    {
                        UserAdjustGamma(GET_OSD_GAMMA());
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                    }
#endif
		        }
#endif

                break;

            case _DDCCI_OPCODE_VCP_RED_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();

                    SET_COLOR_TEMP_TYPE(_CT_USER);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE(ucTemp);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

            case _DDCCI_OPCODE_VCP_GREEN_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();

                    SET_COLOR_TEMP_TYPE(_CT_USER);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE(ucTemp);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

            case _DDCCI_OPCODE_VCP_BLUE_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();

                    SET_COLOR_TEMP_TYPE(_CT_USER);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE(ucTemp);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUTO_SET_UP:

                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] != 0)
                    {
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
                    }
                }

                break;

            case _DDCCI_OPCODE_VCP_AUTO_COLOR:

                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] != 0)
                    {
                        OsdDisplayAutoBalanceProc();
                    }
                }

                break;
#endif

            case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    SET_VGA_MODE_ADJUST_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                }
                break;

            case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(abs(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] - GET_VGA_MODE_ADJUST_V_POSITION()) > 50)
                    {
                        SET_VGA_MODE_ADJUST_V_POSITION(50);
                    }
                    SET_VGA_MODE_ADJUST_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_CLOCK_PHASE:

                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

                    SET_VGA_MODE_ADJUST_PHASE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                    UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }

                break;
#endif

            case _DDCCI_OPCODE_VCP_ACTIVE_CONTROL:

                g_ucDdcciActiveValue = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];

                break;

#if(_AUDIO_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUDIO_VOLUME:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_VOLUME(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserAdjustAudioVolume(GET_OSD_VOLUME());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            case _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL:

                g_ucDdcciRedBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciRedBlackLevel);                            // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL:

                g_ucDdcciGreenBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciGreenBlackLevel);                             // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL:

                g_ucDdcciBlueBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciGreenBlackLevel);                             // Please don't delete

                break;
            case _DDCCI_OPCODE_VCP_GAMMA:
            case _DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE:                
#if(_PCM_FUNCTION == _ON)
                // if PCM != native
                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                {
                    switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                    {
                        case 0x01:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_NATIVE);
                            break;

                        case 0x02:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_18);
                            break;

                        case 0x03:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_20);
                            break;

                        case 0x04:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_22);
                            break;

                        case 0x05:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_24);
                            break;

                        case 0x06:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_26);
                            break;

                        default:
                            SET_OSD_PCM_INPUTGAMMA(_PCM_INPUTGAMMA_NATIVE);
                            break;
                    }

                    OsdFuncColorPcmAdjust();
                }
                else
#endif
                {
                    switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                    {
                        case _GAMMA_OFF:
                            SET_OSD_GAMMA(_GAMMA_OFF);
                            break;
#if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                        case _GAMMA_18:
                            SET_OSD_GAMMA(_GAMMA_18);
                            break;
                        case _GAMMA_20:
                            SET_OSD_GAMMA(_GAMMA_20);
                            break;
                        case _GAMMA_22:
                            SET_OSD_GAMMA(_GAMMA_22);
                            break;
                        case _GAMMA_24:
                            SET_OSD_GAMMA(_GAMMA_24);
                            break;
#elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
                        case _GAMMA_18:
                            SET_OSD_GAMMA(_GAMMA_18);
                            break;
                        case _GAMMA_20:
                            SET_OSD_GAMMA(_GAMMA_20);
                            break;
                        case _GAMMA_22:
                            SET_OSD_GAMMA(_GAMMA_22);
                            break;
                        case _GAMMA_24:
                            SET_OSD_GAMMA(_GAMMA_24);
                            break;
                        case _GAMMA_26:
                            SET_OSD_GAMMA(_GAMMA_26);
                            break;
                        case _GAMMA_CALIB:
                            SET_OSD_GAMMA(_GAMMA_CALIB);
                            break;
#elif(_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                        case _GAMMA_18:
                            SET_OSD_GAMMA(_GAMMA_18);
                            break;
                        case _GAMMA_DICOM200:
                            SET_OSD_GAMMA(_GAMMA_DICOM200);
                            break;
                        case _GAMMA_DICOM250:
                            SET_OSD_GAMMA(_GAMMA_DICOM250);
                            break;
                        case _GAMMA_DICOM300:
                            SET_OSD_GAMMA(_GAMMA_DICOM300);
                            break;
                        case _GAMMA_DICOM350:
                            SET_OSD_GAMMA(_GAMMA_DICOM350);
                            break;
                        case _GAMMA_DICOM400:
                            SET_OSD_GAMMA(_GAMMA_DICOM400);
                            break;
                        case _GAMMA_DICOM450:
                            SET_OSD_GAMMA(_GAMMA_DICOM450);
                            break;
                        case _GAMMA_DICOM500:
                            SET_OSD_GAMMA(_GAMMA_DICOM500);
                            break;
                        case _GAMMA_DICOM550:
                            SET_OSD_GAMMA(_GAMMA_DICOM550);
                            break;
                        case _GAMMA_DICOM600:
                            SET_OSD_GAMMA(_GAMMA_DICOM600);
                            break;
                        case _GAMMA_CALIB:
                            SET_OSD_GAMMA(_GAMMA_CALIB);
                            break;
#endif                            
                        default:
                            break;
                    }
#if(_GAMMA_FUNCTION == _ON)
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
                if(GET_OSD_GAMMA() != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_GAMMA());
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                }
#endif
                }  
                OsdDispDisableOsd();

            break;
/*
            case _DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case _GAMMA_OFF:
                        SET_OSD_GAMMA(_GAMMA_OFF);
                        break;

                    case _GAMMA_18:
                        SET_OSD_GAMMA(_GAMMA_18);
                        break;

                    case _GAMMA_20:
                        SET_OSD_GAMMA(_GAMMA_20);
                        break;

                    case _GAMMA_22:
                        SET_OSD_GAMMA(_GAMMA_22);
                        break;

                    case _GAMMA_24:
                        SET_OSD_GAMMA(_GAMMA_24);
                        break;

                    default:
                        break;
                }

#if(_GAMMA_FUNCTION == _ON)
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
                if(GET_OSD_GAMMA() != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_GAMMA());
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                }
#endif
                OsdDispDisableOsd();

                break;
*/
           case _DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case _CT_9300:
                        SET_COLOR_TEMP_TYPE(_CT_9300);
                        break;

					case _CT_7500:
                        /*SET_COLOR_TEMP_TYPE(_CT_7500);
                        break;*/

                    case _CT_6500:
                        SET_COLOR_TEMP_TYPE(_CT_6500);
                        break;

                    case _CT_5800:
                        SET_COLOR_TEMP_TYPE(_CT_5800);
                        break;

                    case _CT_SRGB:
                        SET_COLOR_TEMP_TYPE(_CT_SRGB);
                        break;

                    case _CT_USER:
                        SET_COLOR_TEMP_TYPE(_CT_USER);
                        break;

                    default:
                        break;
                }

                // Adjust Color
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                OsdDispDisableOsd();
#if(_BEACON_GAMMA_PCM_PARTITION_SUPPORT == _ON)
			    if(UserCommonNVRamGetSystemData(_OGCOCC_SEL_BEACON) == _ON)
				{
#if(_PCM_FUNCTION == _ON)
                    // if PCM != native
                    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                    {
                		OsdFuncColorPcmAdjust();
                    }
                    else
#endif
                    {
#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
    				}
				}
#endif

                break;
						
            case _DDCCI_OPCODE_VCP_USAGE_TIME:
    			// for Test: (in hours) 
    			if((g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] == 0x00)&&(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x00))
			    {
                    RTDNVRamRestorePanelUsedTimeData();
                }
                else
                {
    		        SET_PANEL_TIME_HOUR((WORD)g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]*256 + g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    SET_SYSTEM_RUN_TIME_HOUR((WORD)g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE]*256 + g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    RTDNVRamSavePanelUsedTimeData();
                }
                break;
                
            case _DDCCI_OPCODE_VCP_POWER_MODE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 5)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 4)
                {
                    SET_FORCE_POW_SAV_STATUS(_TRUE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }

                break;

            case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x01:
                        //SET_OSD_LANGUAGE(_CHINESE_T);
                        SET_OSD_LANGUAGE(_CHINESE_S);
                        break;

                    case 0x02:
                        SET_OSD_LANGUAGE(_ENGLISH);
                        break;

                    case 0x03:
                        SET_OSD_LANGUAGE(_FRENCH);
                        break;

                    case 0x04:
                        SET_OSD_LANGUAGE(_GERMAN);
                        break;

                    case 0x05:
                        SET_OSD_LANGUAGE(_ITALIAN);
                        break;

                    case 0x06:
                        SET_OSD_LANGUAGE(_JAPANESE);
                        break;

                    //case 0x07:
                    //    SET_OSD_LANGUAGE(_KOREAN);
                    //    break;

                    case 0x08:  // Portugal
                    //case 0x0E:  // Brazil
                        SET_OSD_LANGUAGE(_PORTUGUESE);
                        break;

                    case 0x09:
                        SET_OSD_LANGUAGE(_RUSSIAN);
                        break;

                    case 0x0A:
                        SET_OSD_LANGUAGE(_SPANISH);
                        break;

                    case 0x0B:
                        SET_OSD_LANGUAGE(_SWEDISH);
                        break;

                    //case 0x0C:
                    //    SET_OSD_LANGUAGE(_TURKISH);
                    //    break;

                    case 0x0D:
                        SET_OSD_LANGUAGE(_CHINESE_S);
                        break;

                    case 0x0F:
                        SET_OSD_LANGUAGE(_ARABIC);
                        break;

                    case 0x1E:
                        SET_OSD_LANGUAGE(_POLISH);
                        break;

                    default:
                        break;
                }

                OsdDispDisableOsd();
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;

            case _DDCCI_OPCODE_VCP_OSD_ON_OFF:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    OsdDispDisableOsd();
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 2)
                {
                    OsdFuncEnableOsd();
                }

                break;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
            case _DDCCI_OPCODE_VCP_DISP_CALIBRATION:

                UserCommonDdcciDispCalibProcess();

                break;
#endif
#if (_PRODUCT_ID_SEL == RTD2555T_LYCL1506_RL6432_156PIN_A_BOE_EV156FHM_N80)
            case _DDCCI_OPCODE_VCP_GRB_LIGHT_VERSION:
    			if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] < 4)
    			{
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                    case 0x00:
                        SET_DDCCI_RGB_MODE(_RGB_LIGHT_R);
                        break;
                    case 0x01:
                        SET_DDCCI_RGB_MODE(_RGB_LIGHT_G);
                        break;                        
                    case 0x10:  
                        SET_DDCCI_RGB_MODE(_RGB_LIGHT_B);
                        break;                        
                 }
    			if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] < 4)
    			{
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                    case 0x00:
                        SET_DDCCI_RGB_LIGHT_MODE(_RGB_LIGHT_OFF);
                        break;
                    case 0x01:
                        SET_DDCCI_RGB_LIGHT_MODE(_RGB_LIGHT_1);
                        break;                        
                    case 0x10:  
                        SET_DDCCI_RGB_LIGHT_MODE(_RGB_LIGHT_2);
                        break;                        
                    case 0x11:  
                        SET_DDCCI_RGB_LIGHT_MODE(_RGB_LIGHT_3);
                        break;                        
                 }
                UserAdjustRGBLightPWM();
                break;
#endif
            default:

                UserCommonDdcciInitTx();

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Reset monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciResetAllSettings(void)
{
    UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();
#endif

    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
    {
        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        UserCommonNVRamSaveSystemData();
    }

    RTDDdcciColorReset();
}

//--------------------------------------------------
// Description  : Reset color to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciColorReset(void)
{
    g_ucDdcciRedBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
    g_ucDdcciGreenBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
    g_ucDdcciBlueBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;

    RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

    RTDNVRamRestoreBriCon();
    RTDNVRamRestoreBacklight();

    UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
}

#if (_BEACON_GAMMA_AUTO_PROCESS_SUPPORT == _ON)     
//--------------------------------------------------
// function: beacon Gamma tool RGB data exchange to chip gamma lut data format
//--------------------------------------------------
static void swap(BYTE *a, BYTE *b/*, BYTE width*/)
{
    char tmp;

    if(a != b)
    {
        //while(width--)
        {
            tmp = *a;
            *a/*++*/ = *b;
            *b/*++*/ = tmp;
        }
    }
}

//--------------------------------------------------
// Description  : Set DDC-DI Command&data for beacon factory Gamma auto Processing function
// Input Value  : null
// Output Value : cmd Status..etc
//#define _DDCCI_SOURCE                               0
//#define _DDCCI_LENGTH                               1
//#define _DDCCI_COMMAND                              2       
//    0  1  2
// 6e 51 8* c0 
//--------------------------------------------------
void RTDDdcciFactoryGammaAutoProcess(void)
{
	BYTE CMDCode;
	BYTE *CmdPara;
    WORD usTemp = 0;

	CMDCode = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]; // Index:3
	CmdPara = &g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE];  // Index:4

#if 1//(_ENABLE_BACKLIGHT_SENSOR||_ENABLE_AMBIENTLIGHT_SENSOR)
	if(CMDCode == _DDCCI_GAMMA_ADJUST_GET_BACKLIGHT_SENSOR_PWM)
	{
      // NULL
	}
	else
	{
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER); 
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
		ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
	}
#endif

	if((CMDCode == _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_MID)||
	   (CMDCode == _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT)||
	   (CMDCode == _DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE)||
	   (CMDCode == _DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE)||
	   (CMDCode == _DDCCI_GAMMA_ADJUST_SET_DICOM_BACKLIGHT)||
	   (CMDCode == _DDCCI_GAMMA_ADJUST_SEND_GAMMA_RGB_VALUE))
	{

    	if((CMDCode == _DDCCI_GAMMA_ADJUST_SET_DICOM_BACKLIGHT)||
    	   (CMDCode == _DDCCI_GAMMA_ADJUST_SEND_GAMMA_RGB_VALUE))
        {
#if(_PCM_FUNCTION == _ON)
            // if PCM != native
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
            {
        		SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
        		OsdFuncColorPcmAdjust();
            }
#endif
	    }
        
#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
    	if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()) == _ON)
    	{
            SET_OSD_GAMMA(_DEFAULT_GAMMA);

#if(_GAMMA_FUNCTION == _ON)
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

            if(GET_OSD_GAMMA() != _GAMMA_OFF)
            {
                UserAdjustGamma(GET_OSD_GAMMA());
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
            }
#endif
    	}
#endif
	}
    DebugMessageUart("CMD:", CMDCode);
    
	switch( CMDCode )
	{
        case _DDCCI_GAMMA_ADJUST_SET_DDCCI2_KEY:
            //Beacon DDC-CI Test Tool
            //Menu:   51 83 C0 96 00 CheckSum:EA
            //Left:   51 83 C0 96 01 CheckSum:EB
            //Right:  51 83 C0 96 02 CheckSum:E8
            //Exit:   51 83 C0 96 03 CheckSum:E9
            //Factory:51 83 C0 96 04 CheckSum:EE
            usTemp = CmdPara[0];
			if((usTemp == 0))
			{
				SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
			}
			else if((usTemp == 1))
			{
				SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
			}
			else if((usTemp == 2))
			{
				SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
			}
			else if((usTemp == 3))
			{
				SET_KEYMESSAGE(_EXIT_KEY_MESSAGE);
			}            
			else if(usTemp == 4)
			{
				SET_KEYMESSAGE(_OK_KEY_MESSAGE);
                /*OsdDispDisableOsd();
                RTDFactoryMainMenu();
#if(_ARM_MCU_CALIBRATION_SUPPORT)
                // !!! Check   
            	UserAdjustDdcciSetARMMcuCommand(_CMD_DDC_MCU_VERSION);
#endif*/
			} 
            
			break;
            
    	case _DDCCI_GAMMA_ADJUST_SET_GAMMA_BYPASS:
            //parameter 0: 0x00:set no bypass   0x01:set all bypass
            //0x02:set only R linear 0x03:set only G linear 0x04:set only B linear
			{
                //ScalerColorOutputGammaEnable(CmdPara[0]);
			}
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_ADC_OFFSET:
#if(_VGA_SUPPORT == _ON)
			//param  range: 0-255
            //parameter 0-1-2 : offset R-G-B
            {
                g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL] = CmdPara[0];
                g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL] = CmdPara[1];
                g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL] = CmdPara[2];                

                if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                }
                else
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
                }
			}
#endif
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_ADC_GAIN:
#if(_VGA_SUPPORT == _ON)
			//param  range	: 0-255                
            //parameter 0-1-2 : Gain R-G-B
			{
                g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL] = CmdPara[0];
                g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL] = CmdPara[1];
                g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL] = CmdPara[2];                

                if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                }
                else
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
                }
			}
#endif
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_LOW:
            //parameter 0 : backlight value (0~250 for 8Bit)
            {	
            if(IsMonoChromeorColorPanel() == M_MONO)
                {
                SET_COLOR_TEMP_TYPE(_CT_9300);
                }
                {
	                #if 1
					usTemp = CmdPara[0];
            	    // Input 8Bit 0~255 -> Output 8Bit 0~255 or 12Bit 0~4095
            	    usTemp =((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? ((usTemp == 255) ? (((usTemp + 1)<<4)-1) : (usTemp<<4)) : usTemp);
	                #else
                    if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
                	{
    	                // Input 12Bit 0~4095  
    					usTemp = (((WORD)CmdPara[1] << 8) | ((WORD)CmdPara[0]));
                	}
    				else
    				{
                	    // Input 8Bit 0~255  
    					usTemp = CmdPara[0];		
    				}
	                #endif

                    //check range
                    if(usTemp > _BACKLIGHT_MAX - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (4<<4) : 4))
                    {
                        usTemp = _BACKLIGHT_MAX - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (4<<4) : 4);
                    }
                    
                    if(usTemp < _BACKLIGHT_MIN)
                    {
                        usTemp = _BACKLIGHT_MIN;
                    }	
                    
                	if(_GET_DUT_BACKLIGHT_CENTER <= usTemp)
            	    {
                		_SET_DUT_BACKLIGHT_CENTER(usTemp + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<4) : 1));
            	    }
                	if(_GET_DUT_BACKLIGHT_MAX <= _GET_DUT_BACKLIGHT_CENTER)
            	    {
                		_SET_DUT_BACKLIGHT_MAX(_GET_DUT_BACKLIGHT_CENTER + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<4) : 1));
            	    }
                    
                    _SET_DUT_BACKLIGHT_MIN(usTemp);
                }
                				
                UserAdjustBacklightDuty(_GET_DUT_BACKLIGHT_MIN);
                //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSER2DATA_MSG);
    	    }
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_MID:
            //parameter 0 : backlight value (0~253 for 8Bit)
            {
            if(IsMonoChromeorColorPanel() == M_MONO)
                {
                SET_COLOR_TEMP_TYPE(_CT_9300);
                }            
                {
	                #if 1
					usTemp = CmdPara[0];
            	    // Input 8Bit 0~255 -> Output 8Bit 0~255 or 12Bit 0~4095
            	    usTemp =((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? ((usTemp == 255) ? (((usTemp + 1)<<4)-1) : (usTemp<<4)) : usTemp);
	                #else
                    if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
                	{
    	                // Input 12Bit 0~4095  
    					usTemp = (((WORD)CmdPara[1] << 8) | ((WORD)CmdPara[0]));
                	}
    				else
    				{
                	    // Input 8Bit 0~255  
    					usTemp = CmdPara[0];		
    				}
	                #endif
                    
                    //check range
                    if(usTemp > _BACKLIGHT_MAX - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (2<<4) : 2))
                    {
                        usTemp = _BACKLIGHT_MAX - ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (2<<4) : 2);
                    }
                    
                	if(_GET_DUT_BACKLIGHT_MIN >= usTemp)
            	    {
                		usTemp = _GET_DUT_BACKLIGHT_MIN + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<4) : 1);
                		_SET_DUT_BACKLIGHT_CENTER(usTemp);
            	    }

                    if(_GET_DUT_BACKLIGHT_MAX <= usTemp)
            	    {
                		_SET_DUT_BACKLIGHT_MAX(usTemp + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<4) : 1));
            	    }
                    
                    _SET_DUT_BACKLIGHT_CENTER(usTemp);
                }

#if(_PCM_FUNCTION == _ON)
                // if PCM != native
                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                {
            		//SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            		//OsdFuncColorPcmAdjust();
                }
                else
#endif
                {
                    // DDCCI Switch to gamma off: Switch back to gamma here
            	    if(GET_OSD_GAMMA() == _GAMMA_OFF)
                    {
                        SET_OSD_GAMMA(_DEFAULT_GAMMA);
                    }
                    
    				if(	IsGammaOptionDICOM(GET_OSD_GAMMA()) ||
    					IsGammaOptionMCUCalibration(GET_OSD_GAMMA()) ||
    					IsGammaOptionPCCalibration(GET_OSD_GAMMA()) ||
    					IsGammaOptionHybridGamma(GET_OSD_GAMMA()) ||
    					IsGammaOptionNative(GET_OSD_GAMMA())
    				)
    				{
    					if(IsGammaOptionDICOM(_DEFAULT_GAMMA))
    					{
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
        	                SET_OSD_GAMMA(_GAMMA_18);
#else
    		                SET_OSD_GAMMA(_GAMMA_18);
#endif
    					}
    					else
    					{
    				        SET_OSD_GAMMA(_DEFAULT_GAMMA);
    					}

#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
                	}
                }
                
#if (_ENABLE_AMBIENTLIGHT_SENSOR)
                if(GET_OSD_AMBIENTLIGHT_SENSOR_STATUS()== _ON)
            	{
                    SET_OSD_AMBIENTLIGHT_SENSOR_STATUS(_OFF);
            	}      
#endif
                
				if(GET_OSD_BACKLIGHT() != _INIT_BACKLIGHT)
				{
		            SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
				}
                
                UserAdjustBacklight(GET_OSD_BACKLIGHT());

                // Beacon_Qa_TestGamma0.1.6 Auto Backlight Adjust
                // CMD 0x55 Pwm0...0x55 Pwm5 //CMD 0x56 Pwm10...0x56 Pwm30  //CMD 0x57 Pwm30...0x57 Pwm40  //CMD 0x90

                // Beacon_Qa_TestGamma0.1.9 Auto Backlight Adjust: Command sequence exchange,Send it again after OK
                // CMD 0x55 Pwm0...0x55 Pwm5 //CMD 0x57 Pwm10...0x56 Pwm40  //CMD 0x56 Pwm10...0x56 Pwm30 Double send[0x56 Pwm30]  //CMD 0x90
                // CMD 0x55&0x57 interval is about 700m ~ 1000ms
                // CMD 0x56      interval is about 1000m ~ 1400ms
                
             #if (_ENABLE_BACKLIGHT_SENSOR)
  				g_bBacklightSensorValueRestoreStatus = _TRUE;
                // Save only at the end of automatic adjustment:SEC(0.02)->SEC(2)
            	ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SAVE_USER2_DATA);
             #endif
            }
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_HIGH:
            //parameter 0 : backlight value (0~255 for 8Bit)
            {
                if(IsMonoChromeorColorPanel() == M_MONO)
                {
                SET_COLOR_TEMP_TYPE(_CT_9300);
                }
            
                {
	                #if 1
					usTemp = CmdPara[0];
            	    // Input 8Bit 0~255 -> Output 8Bit 0~255 or 12Bit 0~4095
            	    usTemp =((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? ((usTemp == 255) ? (((usTemp + 1)<<4)-1) : (usTemp<<4)) : usTemp);
	                #else
                    if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
                	{
    	                // Input 12Bit 0~4095  
    					usTemp = (((WORD)CmdPara[1] << 8) | ((WORD)CmdPara[0]));
                	}
    				else
    				{
                	    // Input 8Bit 0~255  
    					usTemp = CmdPara[0];		
    				}
	                #endif
                    
	                //check range
	                if(usTemp > _BACKLIGHT_MAX)
	                {
	                    usTemp = _BACKLIGHT_MAX;
	                }
	            	if(usTemp <= _GET_DUT_BACKLIGHT_CENTER)
	        	    {
	            		usTemp = _GET_DUT_BACKLIGHT_CENTER + ((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? (1<<4) : 1);
	            		_SET_DUT_BACKLIGHT_MAX(usTemp);
	        	    }
                    
            		_SET_DUT_BACKLIGHT_MAX(usTemp);
            	}				
                UserAdjustBacklightDuty(_GET_DUT_BACKLIGHT_MAX);
                //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSER2DATA_MSG);
            }
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT:
            //parameter 0 : backlight value (0~100)
			if(CmdPara[0] <= 100) 
			{
#if(_PCM_FUNCTION == _ON)
                // if PCM != native
                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                {

                }
                else
#endif
                {
    				if(IsGammaOptionDICOM(GET_OSD_GAMMA()) ||
    					IsGammaOptionMCUCalibration(GET_OSD_GAMMA()) ||
    					IsGammaOptionPCCalibration(GET_OSD_GAMMA()) ||
    					IsGammaOptionHybridGamma(GET_OSD_GAMMA()) ||
    					IsGammaOptionNative(GET_OSD_GAMMA())
    				)
    				{
    					if(IsGammaOptionDICOM(_DEFAULT_GAMMA))
    					{
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
        	                SET_OSD_GAMMA(_GAMMA_18);
#else
    		                SET_OSD_GAMMA(_GAMMA_18);
#endif
    					}
    					else
    					{
    				        SET_OSD_GAMMA(_DEFAULT_GAMMA);
    					}

#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
                	}
            	}

				//UI display range: 0-100  
             #if(_ENABLE_BACKLIGHT_SENSOR)
				if(g_bBacklightSensorValueRestoreStatus == _TRUE)
				{
    				//if(GET_OSD_BACKLIGHT() != _INIT_BACKLIGHT)
    				{
    		            SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
                        UserAdjustBacklight(GET_OSD_BACKLIGHT());

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    				}
				}
				else
             #endif
				{
    				//if(GET_OSD_BACKLIGHT() != CmdPara[0])
				    {
				   // DebugMessageUart("GET_OSD_BACKLIGHT", GET_OSD_BACKLIGHT());
				   // DebugMessageUart("CmdPara[0]", CmdPara[0]);
    	                SET_OSD_BACKLIGHT(CmdPara[0]);
                        UserAdjustBacklight(GET_OSD_BACKLIGHT());

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
				    }
				}

             #if(_ENABLE_BACKLIGHT_SENSOR)
            	ScalerTimerReactiveTimerEvent(SEC(0.3), _USER_TIMER_EVENT_OSD_SAVE_USER2_DATA);
             #endif
			}
			break;

		case _DDCCI_GAMMA_ADJUST_SAVE_DICOM_BACKLIGHT:
            {
				//UserPrefDicomBacklight = CmdPara[2];
				//CMDPara[1] Dicom_sup1  CMDPara[0] Dicom_sup2

                #if 1
				usTemp = CmdPara[2];		
        	    // Input 8Bit 0~255 -> Output 8Bit 0~255 or 12Bit 0~4095
        	    usTemp =((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? ((usTemp == 255) ? (((usTemp + 1)<<4)-1) : (usTemp<<4)) : usTemp);
                #else
                if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
            	{
	                // Input 12Bit 0~4095  
					usTemp = (((WORD)CmdPara[3] << 8) | CmdPara[2]);
            	}
				else
				{
            	    // Input 8Bit 0~255  
					usTemp = CmdPara[2];		
				}
                #endif
                
#if(_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
//OsdDispOsdMessage(_OSD_DISP_DICOM_RESULT);
//OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 14), (CmdPara[0]), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));
//OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 7), (CmdPara[1]), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));

				if(CmdPara[0]>=1) //CMDPara[0] is high of the support dicom word   0x01 is dicom700
				{
    				switch(CmdPara[0])
    				{
        				case kBIT_DICOM_700:
		                    //SET_OSD_GAMMA( _GAMMA_DICOM700);
							//_SET_USER_DICOM_BACKLIGHT_700(usTemp);
        					break;
        				case kBIT_DICOM_200:
                            SET_OSD_GAMMA( _GAMMA_DICOM200);
                            _SET_USER_DICOM_BACKLIGHT_200(usTemp);
        					break;
        				case kBIT_DICOM_250:
                            SET_OSD_GAMMA( _GAMMA_DICOM250);
                            _SET_USER_DICOM_BACKLIGHT_250(usTemp);
        					break;
        				default:
        					break;
    				}
				}
				else if(CmdPara[1]>=1)
				{
    				switch(CmdPara[1])
    				{
        				case kBIT_DICOM_300:
                            SET_OSD_GAMMA(_GAMMA_DICOM300);
        					_SET_USER_DICOM_BACKLIGHT_300(usTemp);
        					break;
        				case kBIT_DICOM_350:
                            SET_OSD_GAMMA(_GAMMA_DICOM350);
        					_SET_USER_DICOM_BACKLIGHT_350(usTemp);
        					break;
        				case kBIT_DICOM_400:
                            SET_OSD_GAMMA(_GAMMA_DICOM400);
        					_SET_USER_DICOM_BACKLIGHT_400(usTemp);
        					break;
        				case kBIT_DICOM_450:
                            SET_OSD_GAMMA(_GAMMA_DICOM450);
        					_SET_USER_DICOM_BACKLIGHT_450(usTemp);
        					break;
        				case kBIT_DICOM_500:
                            SET_OSD_GAMMA(_GAMMA_DICOM500);
        					_SET_USER_DICOM_BACKLIGHT_500(usTemp);
        					break;
        				case kBIT_DICOM_550:
                            SET_OSD_GAMMA(_GAMMA_DICOM550);
        					_SET_USER_DICOM_BACKLIGHT_550(usTemp);
        					break;
        				case kBIT_DICOM_600:
                            SET_OSD_GAMMA(_GAMMA_DICOM600);
        					_SET_USER_DICOM_BACKLIGHT_600(usTemp);
        					break;
        				case kBIT_DICOM_650:
                            //SET_OSD_GAMMA(_GAMMA_DICOM650);
        					//_SET_USER_DICOM_BACKLIGHT_650(usTemp);
        					break;					
        				default:
        					break;
    				}
				}
    			UserAdjustBacklightDuty(usTemp);
// End of #if (_GAMMA_TYPE ==_GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
#else
                //-----One Dicom
                {
                    //Update Dicom
                    #if(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
	                SET_OSD_GAMMA(_GAMMA_20);
                    #elif(_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
	                SET_OSD_GAMMA(_GAMMA_26);
                    #else
	                SET_OSD_GAMMA(_GAMMA_20);
                    #endif
					_SET_USER_DICOM_BACKLIGHT(usTemp);
                }
#endif

                //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_ENABLE_BACKLIGHT_SENSOR)
            	ScalerTimerReactiveTimerEvent(SEC(0.3), _USER_TIMER_EVENT_OSD_SAVE_USER2_DATA);
#endif
            }
			break;
            
		case _DDCCI_GAMMA_ADJUST_SET_DICOM_BACKLIGHT:
			{                
                #if 1
				usTemp = CmdPara[0];		
        	    // Input 8Bit 0~255 -> Output 8Bit 0~255 or 12Bit 0~4095
        	    usTemp =((_PWM_DUT_RESOLUTION == _PWM_12BIT) ? ((usTemp == 255) ? (((usTemp + 1)<<4)-1) : (usTemp<<4)) : usTemp);
                #else
                if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
            	{
	                // Input 12Bit 0~4095  
					usTemp = (((WORD)CmdPara[1] << 8) | CmdPara[0]);
            	}
				else
				{
            	    // Input 8Bit 0~255  
					usTemp = CmdPara[0];		
				}
                #endif
				UserAdjustBacklightDuty(usTemp);
			}
			break;
            
    	case _DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE:
            //parameter 0 : the gamma index
			{
				BYTE gamma_table,color_temp;

				if(CmdPara[0]>_GAMMA_AMOUNT)
                    CmdPara[0]= _GAMMA_OFF;

                // for Beacon Gamma Tool skip off
                //if((CmdPara[0] > _GAMMA_OFF)&&(CmdPara[0] < (_GAMMA_AMOUNT -1))) 
                //    CmdPara[0]++;

                // In order to make Panel AB calculation more accurate and convenient without skipping Gamma off
                               
				gamma_table = CmdPara[0];
				color_temp = GET_COLOR_TEMP_TYPE();	

#if(_PCM_FUNCTION == _ON)
                // if PCM != native
                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                {
    				if(gamma_table > _PCM_INPUTGAMMA_26)
                        gamma_table = _PCM_INPUTGAMMA_NATIVE;
                    
                    SET_OSD_PCM_INPUTGAMMA(gamma_table);
            		OsdFuncColorPcmAdjust();
                }
                else
#endif
                {
                    SET_OSD_GAMMA(gamma_table/*_GAMMA_24*/);

#if(_GAMMA_FUNCTION == _ON)
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                    if(GET_OSD_GAMMA() != _GAMMA_OFF)
                    {
                        UserAdjustGamma(GET_OSD_GAMMA());
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                    }
#endif
                }

                OsdDispDisableOsd();
			}
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE:
            {
  //  DebugMessageUart("_DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE:", CmdPara[0]);
                
            //parameter 0 : index of color temperature
				if(CmdPara[0]>_CT_COLORTEMP_AMOUNT)
					CmdPara[0] = _CT_9300;

                // for Beacon Gamma Tool
                if(CmdPara[0] == _CT_7500) 
                    CmdPara[0]= _CT_6500;

                OsdDispDisableOsd();
                if(IsMonoChromeorColorPanel() == M_COLOR)
    			{
                SET_COLOR_TEMP_TYPE(CmdPara[0]/*_CT_9300*/);
                }
                else
    			{
                SET_COLOR_TEMP_TYPE(_CT_9300);
                }   
   // DebugMessageUart("SET_COLOR_TEMP_TYPE:",GET_COLOR_TEMP_TYPE());
                
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
				
#if(_BEACON_GAMMA_PCM_PARTITION_SUPPORT == _ON)
			    if(UserCommonNVRamGetSystemData(_OGCOCC_SEL_BEACON) == _ON)
				{
#if(_PCM_FUNCTION == _ON)
                    // if PCM != native
                    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
                    {
                		OsdFuncColorPcmAdjust();
                    }
                    else
#endif
                    {
#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
    				}
				}
#endif
			}
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_AUTO_ADJUST:
#if(_VGA_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE) && (SysSourceGetSourceType() == _SOURCE_VGA))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
            }
#endif
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_AUTO_COLOR:
#if(_VGA_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE) && (SysSourceGetSourceType() == _SOURCE_VGA))
            {
                ScalerTimerActiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_DO_AUTO_COLOR);
            }
#endif
			break;
			
    	case _DDCCI_GAMMA_ADJUST_SET_CONTRAST:
            //parameter 0 : the of the contrast(0~100)
			if(CmdPara[0] < 101) 
			{
    			//UI display range: 0-100   
#if(_CONTRAST_SUPPORT == _ON)
                SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(CmdPara[0], _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
                UserAdjustContrast(GET_OSD_CONTRAST());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
#endif
			}
			break;
        
    	case _DDCCI_GAMMA_ADJUST_SEND_GAMMA_RGB_VALUE: // 14-bit 0~0x3FFF range: 0 ~ (2^14-1) 
            //order    : set zero gamma tabble
            //Gamma tool data format:
            //parameter 0 : low byte of R   parameter 1 : high byte of R   
            //parameter 2 : low byte of G   parameter 3 : high byte of G   
            //parameter 4 : low byte of B   parameter 5 : high byte of B 
            
            //gamma Lut data format:    
            //index 0 : high byte of R/G/B   index 1 : low byte of R/G/B   
    		{
				WORD GammaData_R,GammaData_G,GammaData_B;

				GammaData_R = ((WORD)(CmdPara[0]) + (WORD)(CmdPara[1]<<8));
				GammaData_G = ((WORD)(CmdPara[2]) + (WORD)(CmdPara[3]<<8));
				GammaData_B = ((WORD)(CmdPara[4]) + (WORD)(CmdPara[5]<<8));
            
				// Range check
				if((GammaData_R <= 0x3FFF)&&(GammaData_G <= 0x3FFF)&&(GammaData_B <= 0x3FFF))
				{					
                    //gamma tool data format->gamma lut data format
                    swap(&CmdPara[0],&CmdPara[1]/*,1*/); //R Word H|L swap
                    swap(&CmdPara[2],&CmdPara[3]/*,1*/); //G Word H|L swap
                    swap(&CmdPara[4],&CmdPara[5]/*,1*/); //B Word H|L swap

					ScalerColorOutputGammaAdjustRGBValue(CmdPara);				
				}
			}
			break;
                 
		case _DDCCI_GAMMA_ADJUST_SET_FAC_MONITOR_SN:
			{				
			    BYTE g_pucIDSNRxBuf[_IDSN_BUF_LENGTH] = {0};
            	DWORD ulIDSNDecTemp;
                BYTE ucIndex;   

				// range check...max length is 25
				if(CmdPara[0] > _SN_BUF_LENGTH)
				{
					CmdPara[0] = _SN_BUF_LENGTH;
				}

                // Save SN data
				{    
                    RTDNVRamSaveMonitorSNData(_SN_BUF_LENGTH,&CmdPara[1]); 

        	        DebugMessageUart("Save SN:", CmdPara[0]);
                	for(ucIndex = 0; ucIndex < _SN_BUF_LENGTH; ucIndex++)
                	{
            	        DebugMessageUart(":", CmdPara[1+ucIndex]);
                	}

#if 1				
                    // Beacon Gamma Tool update IDSN
					// IDSN Number & Year & Week
                    for(ucIndex = 8; ucIndex > 0; ucIndex--)
                    {
                        // ASCII(Char)->Dec [8 numbers]:
                        // C125020490269:0x43 0x31 0x32 0x35 0x30 0x32 0x30 0x34 0x39 0x30 0x32 0x36 0x39 0x00...
                        // -> 20490269
                    	// C61WA03D21140002[New spec in 2020]
                        if((CmdPara[CmdPara[0] - ucIndex + 1] >= 0x30)&&(CmdPara[CmdPara[0] - ucIndex  + 1] <= 0x39))
                        {
                            ulIDSNDecTemp = ulIDSNDecTemp * 10 + (CmdPara[CmdPara[0] - ucIndex + 1] - 0x30);
                        }
                        else
                        {
                            ulIDSNDecTemp = 0x01010101;
                            break;
                        }
                    }

                    // Need Update 
                    if(ulIDSNDecTemp != 0)
                    {
                        // Dec -> Hex: 20490269 -> 0x138A81D
                		g_pucIDSNRxBuf[0] = (BYTE)(ulIDSNDecTemp>>24);  // highest byte       
                		g_pucIDSNRxBuf[1] = (BYTE)(ulIDSNDecTemp>>16);  //                
                		g_pucIDSNRxBuf[2] = (BYTE)(ulIDSNDecTemp>>8);   //                
                		g_pucIDSNRxBuf[3] = (BYTE)(ulIDSNDecTemp);      // lowest byte  
                        // moninfo show is 20490269 EDIDW2K show is 138A81D
                        RTDNVRamSaveMonitorIDSNData(_IDSN_BUF_LENGTH,&g_pucIDSNRxBuf[0]); 
                    }
					// Avoid fail(Beacon Gamma Tool GetSN) So do not updating DP EDID
#endif
				}
			}
			break;

		case _DDCCI_GAMMA_ADJUST_GET_FAC_MONITOR_SN:
			{				

            	g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(5+_SN_BUF_LENGTH));  // Length 0x80|(0xC0,CMD,data(25))
				g_pucDdcciTxBuf[2] = 0xc0;
				g_pucDdcciTxBuf[3] = 0x00;
				g_pucDdcciTxBuf[4] = 0x00;
				g_pucDdcciTxBuf[5] = (0x80|(3+_SN_BUF_LENGTH));
				g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_FAC_MONITOR_SN;

				RTDNVRamLoadMonitorSNData(&g_pucDdcciTxBuf[7]);  
                
            	g_pucDdcciTxBuf[7 + _SN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum

                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
			}
			break;

		case _DDCCI_GAMMA_ADJUST_SET_MONITOR_EDID_IDSN:
            //order  : [Length + data] update RAM EDID ID Serial Number
			{				
				// range check...max length is 4                
				if(CmdPara[0] == _IDSN_BUF_LENGTH)
				{
                    // Beacon QA Tool Input is Dec: 20490269 ->Send DDCCI Hex: -> 0x138A81D
                    RTDNVRamSaveMonitorIDSNData(_IDSN_BUF_LENGTH,&CmdPara[1]); 
				}
                else  if((CmdPara[0] == 0x01)&&(CmdPara[1] == 0x02)&&(CmdPara[2] == 0x03))
                {
                    //Gamma Auto Adjust Tool T9 add (ST Sequia use)  
                    //order    : begin adjust gamma step
                    //parameter 0 : must 0x01
                    //parameter 1 : must 0x02
                    //parameter 2 : must 0x03
                    //#define  BEACON_I2C_BEGIN_ADJUST_GAMMA				0xA0
                }
			}
			break;

		case _DDCCI_GAMMA_ADJUST_GET_MONITOR_EDID_IDSN:
            //order  :  Get RAM EDID ID Serial Number
            {
                if((CmdPara[0] == 0x03)&&(CmdPara[1] == 0x02)&&(CmdPara[2] == 0x01))
                {
                    //order    : begin adjust gamma step
                    //parameter 0 : must 0x03
                    //parameter 1 : must 0x02
                    //parameter 2 : must 0x01
                    //#define  BEACON_I2C_END_ADJUST_GAMMA				0xA1
                }
                else
    			{
                	g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(5+_IDSN_BUF_LENGTH));  // Length 0x80|(0xC0,CMD,data(4))
    				g_pucDdcciTxBuf[2] = 0xc0;
    				g_pucDdcciTxBuf[3] = 0x00;
    				g_pucDdcciTxBuf[4] = 0x00;
    				g_pucDdcciTxBuf[5] = (0x80|(3+_IDSN_BUF_LENGTH));
    				g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_MONITOR_EDID_IDSN;

    				RTDNVRamLoadMonitorIDSNData(&g_pucDdcciTxBuf[7]);  
                
                	g_pucDdcciTxBuf[7 + _IDSN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum

                    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

    			}
			}
			break;	
			
		case _DDCCI_GAMMA_ADJUST_SET_EDID_PROTECT_EXT_EEPROM:
            //order  : Change write protection status to download EDID data external EEPROM:24C02
            //Function:UserInterfaceGetEmbeddedEDIDData()
			{
                // Disable EDID EEPROM Write Protect(24C02)
                if(CmdPara[0]== 0x00)
                {
                    PCB_D0_EDID_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
                }
                else
                {
                    PCB_D0_EDID_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                }
			}
			break;

		case _DDCCI_GAMMA_ADJUST_SET_EDID_BANKSEL_EXT_EEPROM:
            //order  : 0~4 for Select external EEPROM Bank
			{
                if(CmdPara[0]== 0x00)
                {
                
                }
                else if(CmdPara[0]== 0x01)
                {
                
                }
			}
			break;
            
        case _DDCCI_GAMMA_ADJUST_SET_LOCAL_ENHANCEMENT_ON_OFF:
            // Write:   51 83 C0 E0 00 CheckSum(9C) 
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
			{
				if(CmdPara[0] <= 0x03)
	            {
	                OsdDispDisableOsd();
					
					#if(_FPGA_COLOR_ADAPTIVE_SUPPORT)
	                if(CmdPara[0]== 0x00)
	                {
						UserCommonNVRamSetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE,_OFF); 
	                }
	                else if(CmdPara[0]== 0x01)
	                {
						UserCommonNVRamSetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE,_ON); 
	                }
			        UserCommonNVRamSaveSystemData();
					UserAdjustFPGALocalEnhancementHandler(_ON);
					#else
	                if(CmdPara[0]== 0x00)
	                {
	                    SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
	                }
	                else if(CmdPara[0]== 0x01)
	                {
	                    SET_OSD_HLWIN_TYPE(_HL_WIN_4);
	                }
					UserAdjustHighLightWindowUserHander();
					
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
					#endif
	            }
			}
			break;

        case _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_TYPE1:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
	            #if(_FPGA_COLOR_ADAPTIVE_SUPPORT)
	            if(UserCommonNVRamGetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE) == _ON) 
	            {
					WORD usHLWinHPos,usHLWinVPos;

					usHLWinHPos = ((CmdPara[0]<<8) + (CmdPara[1]));
					usHLWinVPos = ((CmdPara[2]<<8) + (CmdPara[3]));

					UserAdjustFPGALocalEnhancementCus1Move(usHLWinHPos,usHLWinVPos);
				}
	            #else
	            if(GET_OSD_HLWIN_TYPE() == _HL_WIN_4)
	            {
					WORD usHLWinHPos,usHLWinVPos;

					usHLWinHPos = ((CmdPara[0]<<8) + (CmdPara[1]));
					usHLWinVPos = ((CmdPara[2]<<8) + (CmdPara[3]));

	                UserAdjustHLWinTypeCus1Move(usHLWinHPos,usHLWinVPos);
				}
				#endif
        	}
			break;

		case _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_TYPE2:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
#if(_FPGA_COLOR_ADAPTIVE_SUPPORT)
	            if(UserCommonNVRamGetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE) == _ON) 
	            {
					SWORD usHLWinHPos,usHLWinVPos;

					usHLWinHPos = (SWORD)(((SWORD)(CmdPara[0]<<8) + (SWORD)CmdPara[1]));
					usHLWinVPos = (SWORD)(((SWORD)(CmdPara[2]<<8) + (SWORD)CmdPara[3]));

					UserAdjustFPGALocalEnhancementCus2Move((SWORD)((usHLWinHPos) << 3),(SWORD)((usHLWinVPos) << 3));
				}            
#else
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_4)
                {
					SWORD usHLWinHPos,usHLWinVPos;

					usHLWinHPos = (SWORD)(((SWORD)(CmdPara[0]<<8) + (SWORD)CmdPara[1]));
					usHLWinVPos = (SWORD)(((SWORD)(CmdPara[2]<<8) + (SWORD)CmdPara[3]));

	                UserAdjustHLWinTypeCus2Move((SWORD)((usHLWinHPos) << 3),(SWORD)((usHLWinVPos) << 3));
	        	}
#endif
        	}
			break;

		case _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_ZOOM:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
				SBYTE usHLWinHVZoom;
                
				usHLWinHVZoom = (SBYTE)CmdPara[0];
        		if(usHLWinHVZoom < 0)
        		{
            		if(g_usHLWinHWidth > (((_PANEL_DV_HEIGHT / 10) + 1) & 0xFFFE))
                        g_usHLWinHWidth = g_usHLWinHWidth - 16;
                    else
                        g_usHLWinHWidth = (((_PANEL_DV_HEIGHT / 10) + 1) & 0xFFFE);
        		}
        		else
        		{
            		if(g_usHLWinHWidth < (((_PANEL_DV_HEIGHT / 4) + 1) & 0xFFFE))
                        g_usHLWinHWidth = g_usHLWinHWidth + 16;
                    else
                        g_usHLWinHWidth = (((_PANEL_DV_HEIGHT / 4) + 1) & 0xFFFE);
        		}
                g_usHLWinVHeight = g_usHLWinHWidth;
                SET_OSD_LOCALENHANCEMENT_WINDOW_ZOOM(g_usHLWinHWidth);

#if(_FPGA_COLOR_ADAPTIVE_SUPPORT)
	            if(UserCommonNVRamGetSystemData(_FPGA_LOCAL_ENHANCEMENT_MODE) == _ON) 
	            {
                	UserAdjustFPGALocalEnhancementHandler(_ON);
				} 
#else
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_4)
                {
	                UserAdjustHLWinTypeCus2Move(0,0);
	        	}
#endif
				//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
        	}
			break;
                        
		case _DDCCI_GAMMA_ADJUST_SET_AMBI_DICOM_BACKLIGHT:
			break;

		case _DDCCI_GAMMA_ADJUST_GET_AMBI_DICOM_BACKLIGHT:
			break;
			
		case _DDCCI_GAMMA_ADJUST_ENTER_BRUNIN:
			{
                if(CmdPara[0]== 0x01)
                {
                    SET_OSD_FACTORY_MODE_BRUNIN(_ON);
                }
                else
                {
                    SET_OSD_FACTORY_MODE_BRUNIN(_OFF);
                }
                //RTDNVRamSaveOsdUserData();
			}
			break;
				   
		case _DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS:
            //��ȡǰһ������״̬��������ֻ���ڣ�PC��MCUд����ʱ��ȡ)��
            //��ȷ��ǰһ�������������յ�����ǰһ���������У��
            //��ȷ����0x01,����ȷ����0x00
            {
                //(_BEACON_CALIBRATION_COMMAND_STATUS_EXINT_SUPPORT == _OFF)
            	g_pucDdcciTxBuf[0] 			= 0x6e;	// Source
            	g_pucDdcciTxBuf[1] 			= 0x86;	// Length //Byte size from next byte to before byte of checksum
            	
            	g_pucDdcciTxBuf[2] 			= 0xc0;	// VCP Prefix 0xC0 0x00 0x00
            	g_pucDdcciTxBuf[3] 			= 0x00;	 
            	g_pucDdcciTxBuf[4] 			= 0x00;  
            	g_pucDdcciTxBuf[5] 			= 0x84; // length
            	g_pucDdcciTxBuf[6] 			= _DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS; // cmd
            	g_pucDdcciTxBuf[7] 			= E_OrderStatus; // parameter
            	
            	g_pucDdcciTxBuf[8] 			= UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
        	    DebugMessageUart("E_0:", E_OrderStatus);

                // Clear flag: PC only reads once
                E_OrderStatus=0;
            }
			break;

		case _DDCCI_GAMMA_ADJUST_GET_DICOM_SUPPORT:
			{               
            	g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = 0x87;   // Length //Byte size from next byte to before byte of checksum
				g_pucDdcciTxBuf[2] = 0xc0;
				g_pucDdcciTxBuf[3] = 0x00;
				g_pucDdcciTxBuf[4] = 0x00;
				
				g_pucDdcciTxBuf[5] = 0x85;
				g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_DICOM_SUPPORT;
				g_pucDdcciTxBuf[7] = Dicom_sup2;
				g_pucDdcciTxBuf[8] = Dicom_sup1;
                
            	g_pucDdcciTxBuf[9] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
			}
		    break; 

		case _DDCCI_GAMMA_ADJUST_GET_BACKLIGHT_SENSOR_PWM:
            // parameter 0 : temperature
            // parameter 1 : Backlight Sensor Current H data
            // parameter 2 : Backlight Sensor Current L data
            // parameter 3 : Backlight Sensor Target H data
            // parameter 4 : Backlight Sensor Target L data
            // parameter 5 : PWM H data
            // parameter 6 : PWM L data
#if (_ENABLE_BACKLIGHT_SENSOR)            
			{				
            	g_pucDdcciTxBuf[0] = 0x6e;	         // Source
				g_pucDdcciTxBuf[1] = (0x80|(0x0C));  // Length //Byte size from next byte to before byte of checksum
				g_pucDdcciTxBuf[2] = 0xc0;            // VCP Prefix 0xC0 0x00 0x00
				g_pucDdcciTxBuf[3] = 0x00;
				g_pucDdcciTxBuf[4] = 0x00;
				
        		g_pucDdcciTxBuf[5] = (0x80|(0x0A));	 // Length // checksum to the current byte size
				g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_BACKLIGHT_SENSOR_PWM; //CMD	

                UserTemperatureSensorHandler();
				g_pucDdcciTxBuf[7] = (BYTE)(uctemperaturesensor&0xFF);
				g_pucDdcciTxBuf[8] = (BYTE)((ReadBacklightSensorValue(0)>>8)&0xFF); 		
				g_pucDdcciTxBuf[9] = (BYTE)(ReadBacklightSensorValue(0)&0xFF); 		

				g_pucDdcciTxBuf[10] = (BYTE)((UserGetBacklightSensorTargetValue()>>8)&0xFF); 			
				g_pucDdcciTxBuf[11] = (BYTE)(UserGetBacklightSensorTargetValue()&0xFF); 		

            	usTemp = PCB_GET_BACKLIGHT_PWM();
 #if(_BACKLIGHT_PWM_INVERSE == _ON)
                usTemp = _BACKLIGHT_MAX - usTemp;
 #endif
				g_pucDdcciTxBuf[12] = (BYTE)((usTemp>>8)&0xFF); 			
				g_pucDdcciTxBuf[13] = (BYTE)(usTemp&0xFF); 	
				
             	g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
			}			
 #endif
			break;	

#if 1			
		case _DDCCI_GAMMA_ADJUST_SET_PANEL_LUX_AB_COEFFICENT:
			// parameter 0:sensor index,0 mid,1 up,2 down;
			// parameter 1-8 luminance hight first
			
			// Beacon_Gamma_Color(I2C)2.29_T19: Second page->[Auto Cali(a and b for the Sensor)]
			// When the application is finished generating calibration data, select the [Auto Cali] option to execute the output AB value.

            // Sensor type: 0       a: 1.067616 b: -0.376512
			// 6E 51 8B c0 a8 00 00 00 04 2b ff ff fe 88 Checksum:85 [00 00 04 2b = 0x0000042b = 1067 = 1.067616*1000]  [ff ff fe 88 = 0xffffffff-0x177  -0.376512*1000 = -376 = 0x177]
			{				
				switch(CmdPara[0])
				{
    				default:
					case _BK_SENSOR_MIDDLE:
	                    g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucA_Data = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                    g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucB_Data = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
						break;

					case _BK_SENSOR_UP:
		                g_stPanelLuxABData[_BK_SENSOR_UP].ucA_Data = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
		                g_stPanelLuxABData[_BK_SENSOR_UP].ucB_Data = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
						break;

					case _BK_SENSOR_DOWN:
		                g_stPanelLuxABData[_BK_SENSOR_DOWN].ucA_Data = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
		                g_stPanelLuxABData[_BK_SENSOR_DOWN].ucB_Data = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
						break;
				}
#if 0//(_PRODUCT_ID_SEL == RTD2785TM_G510S_RL6432_216PIN_BEACON_A_STD_R213TCE_LU1_LVDS_PWM)
                g_stPanelLuxABData[_BK_SENSOR_DOWN].ucA_Data = 2.4;
                g_stPanelLuxABData[_BK_SENSOR_DOWN].ucB_Data = 0;

#endif				
				RTDNVRamSavePanelLuxABData();
                DebugMessageUart("set_a", g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucA_Data);
                DebugMessageUart("set_b", g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucB_Data);
#if ((_ARM_MCU_CALIBRATION_SUPPORT)&&(_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB))
				//Ensure that the save target Sensor value is the default state
				SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
				UserAdjustQAUpdateTargetSensor(_DEFAULT_GAMMA_LUX);
#endif                
			}
			break; 

        case _DDCCI_GAMMA_ADJUST_GET_PANEL_LUX_AB_COEFFICENT:
			// Write:6e 51 82 C0 AB CheckSum:0x ->50ms 
            // Sensor type: 0    Write   a: 1.067616 b: -0.376512
			// Read: 6e 89 c0 44 85 60 00 c3 bc 00 00 CheckSum:0x  1.067 -0.376
            {
				DWORD ucLuxA,ucLuxB;
                               
                g_pucDdcciTxBuf[0] = 0x6e;  // Source
                g_pucDdcciTxBuf[1] = 0x89;  // Length //Byte size from next byte to before byte of checksum
                g_pucDdcciTxBuf[2] = 0xc0;

				RTDNVRamLoadPanelLuxABData();
			    memcpy(&ucLuxA,&g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucA_Data,4);
				memcpy(&ucLuxB,&g_stPanelLuxABData[_BK_SENSOR_MIDDLE].ucB_Data,4);

                g_pucDdcciTxBuf[3] = (BYTE)(((DWORD)ucLuxA & 0xFF000000)>>24);
                g_pucDdcciTxBuf[4] = (BYTE)(((DWORD)ucLuxA & 0x00FF0000)>>16);
                g_pucDdcciTxBuf[5] = (BYTE)(((DWORD)ucLuxA & 0x0000FF00)>>8);
                g_pucDdcciTxBuf[6] = (BYTE)(((DWORD)ucLuxA & 0x000000FF)>>0);
        
                g_pucDdcciTxBuf[7] = (BYTE)(((DWORD)ucLuxB & 0xFF000000)>>24);
                g_pucDdcciTxBuf[8] = (BYTE)(((DWORD)ucLuxB & 0x00FF0000)>>16);
                g_pucDdcciTxBuf[9]  = (BYTE)(((DWORD)ucLuxB & 0x0000FF00)>>8);
                g_pucDdcciTxBuf[10] = (BYTE)(((DWORD)ucLuxB & 0x000000FF)>>0);
        
                g_pucDdcciTxBuf[11] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
                //DebugMessageUart("a", ucLuxA);
                //DebugMessageUart("b", ucLuxB);
            }
            break;

		case _DDCCI_GAMMA_ADJUST_GET_BK_SENSOR_TO_PANEL_LUX:
			// Write:6e 51 82 C0 A9 00 CheckSum:0x ->50ms 
			// Read: 6e 87 c0 00 00 85 A9 01 ef CheckSum:0x
			{
            	BYTE ucBKSensorPos;
            	WORD ucLux;

				switch(CmdPara[0])
				{
    				default:
					case _BK_SENSOR_MIDDLE:
						ucBKSensorPos = _BK_SENSOR_MIDDLE;
						break;

					case _BK_SENSOR_UP:					
						ucBKSensorPos = _BK_SENSOR_UP;
						break;

					case _BK_SENSOR_DOWN:
						ucBKSensorPos = _BK_SENSOR_DOWN;
						break;
				}
				
				{					
					ucLux = UserAdjustQAGetCurrPanelLux(ucBKSensorPos);

	                g_pucDdcciTxBuf[0]          = 0x6e; // Source
	                g_pucDdcciTxBuf[1]          = 0x87; // Length //Byte size from next byte to before byte of checksum
	                
	                g_pucDdcciTxBuf[2]          = 0xc0; // VCP Prefix 0xC0 0x00 0x00
	                g_pucDdcciTxBuf[3]          = 0x00;  
	                g_pucDdcciTxBuf[4]          = 0x00;  
	                g_pucDdcciTxBuf[5]          = 0x85; // length // checksum to the current byte size
	                g_pucDdcciTxBuf[6]          = _DDCCI_GAMMA_ADJUST_GET_BK_SENSOR_TO_PANEL_LUX; // cmd

	                g_pucDdcciTxBuf[7]          = (BYTE)(((WORD)ucLux & 0xFF00)>> 8); // 0x1ef = 495cd/m2
	                g_pucDdcciTxBuf[8]          = (BYTE)(((WORD)ucLux & 0x00FF)>> 0);
					
	                g_pucDdcciTxBuf[9]          = UserCommonDdcciCalCheckSum(); // checksum
	                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
	            }
			}
			break;
			
        case _DDCCI_GAMMA_ADJUST_SET_PANEL_LUX_RANGE_PARAMTER:
			// parameter 0: CT index0, index1, 
			// Color temperature order of Gamma standard table
			
			// Beacon_Gamma_Color(I2C)2.29_T19: First page->[Support Auto Adjust Gamma]
			// Select the Auto Gamma option when the application generates calibration data.

			// 6e 51 8B C0 AA 00 00 07 69 CC 00 00 01 0B 76 -> max:485.8399 min:0.2679  [00 07 69 CC = 0x769CC = 485836 = 485.8399*1000]
			// 6e 51 8B C0 AA 01 00 06 15 6A 00 00 01 0B AC -> max:398.699  min:0.2679
			// 6e 51 8B C0 AA 02 00 06 C8 96 00 00 01 0B 8E -> max:444.5644 min:0.2679			
			{				
		        if(CmdPara[0] == 0x00/*_DDCCI_BYPASS_PARAMTER*/)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
#endif
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
				}
				else if(CmdPara[0]== 0x01/*_DDCCI_COLOR1_PARAMTER*/)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
				}
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
				else if(CmdPara[0]== 0x02/*_DDCCI_COLOR2_PARAMTER*/)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
				}
				else if(CmdPara[0]== 0x03/*_DDCCI_COLOR3_PARAMTER*/)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
				}
#else
				else if(CmdPara[0]== 0x02/*_DDCCI_COLOR2_PARAMTER*/)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax = (((SDWORD)CmdPara[1] << 24) | ((SDWORD)CmdPara[2] << 16) | ((SDWORD)CmdPara[3] << 8) | ((SDWORD)CmdPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin = (((SDWORD)CmdPara[5] << 24) | ((SDWORD)CmdPara[6] << 16) | ((SDWORD)CmdPara[7] << 8) | ((SDWORD)CmdPara[8] << 0));
				}
#endif
				RTDNVRamSavePanelLuxRangeData();
                DebugMessageUart("ucLuxMax", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax);
                DebugMessageUart("ucLuxMin", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMin);
                DebugMessageUart("ucRealLuxMax", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax);
                DebugMessageUart("ucRealLuxMin", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax);

			}
            break;
        
        case _DDCCI_GAMMA_ADJUST_GET_PANEL_LUX_RANGE_PARAMTER:
			// Write:6e 51 82 C0 AC Checksum ->50ms 
			// Read: 6e A1 C0 [48 FF 2E C0 44 05 40 00] [48 FF 2E C0 44 05 40 00] [48 D2 B7 E0 44 05 40 00] [48 FD 4F E0 44 05 40 00] 7B -> max:522.614 min:0.533  max:522.614 min:0.533  max:431.551 min:0.533 max:518.783 min:0.533
            {
				DWORD ucMax,ucMin;
				               
                g_pucDdcciTxBuf[0] = 0x6e;       // Source
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
                g_pucDdcciTxBuf[1] = (0x80|34);  // Length [8x4+2] //Byte size from next byte to before byte of checksum
#else
                g_pucDdcciTxBuf[1] = (0x80|26);  // Length [8x3+2] //Byte size from next byte to before byte of checksum
#endif
                g_pucDdcciTxBuf[2] = 0xc0;
                g_pucDdcciTxBuf[3] = _DDCCI_GAMMA_ADJUST_GET_PANEL_LUX_RANGE_PARAMTER; // cmd
                
				RTDNVRamLoadPanelLuxRangeData();
                // Bypass->Off[Native]
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMin,4);
			    g_pucDdcciTxBuf[4] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[5] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[6] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[7] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[8] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[9] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[10] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[11] = (BYTE)(((DWORD)ucMin & 0x000000ff));

#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
                // COLOR1
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[12] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[13] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[14] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[15] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[16] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[17] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[18] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[19] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                // COLOR2
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[20] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[21] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[22] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[23] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[24] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[25] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[26] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[27] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                // COLOR3
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax,4);
			    memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[28] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[29] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[30]= (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[31]= (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[32]= (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[33]= (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[34]= (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[35]= (BYTE)(((DWORD)ucMin & 0x000000ff));
                g_pucDdcciTxBuf[36] = UserCommonDdcciCalCheckSum(); // checksum#else
#else			
                // COLOR1
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[12] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[13] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[14] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[15] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[16] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[17] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[18] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[19] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                // COLOR2
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax,4);
			    memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[20] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[21] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[22]= (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[23]= (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[24]= (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[25]= (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[26]= (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[27]= (BYTE)(((DWORD)ucMin & 0x000000ff));
			
                g_pucDdcciTxBuf[28] = UserCommonDdcciCalCheckSum(); // checksum
#endif
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
            }
            break;
#endif

		default:
			break;
	}	

    if(CMDCode == _DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS)
    {
        //��ȡǰһ������״̬��������ֻ���ڣ�PC��MCUд����ʱ��ȡ)��
        //��ȷ��ǰһ�������������յ�����ǰһ���������У��
        //��ȷ����0x01,����ȷ����0x00
    }
    else if(CMDCode == _DDCCI_GAMMA_ADJUST_SAVE_DICOM_BACKLIGHT)
    {
        //Beacon_Gamma_Color(I2C)3.0_T9�����������¶�ȡǰһ������״̬�ļ��ʱ���ӳ���ִ����һ������ʱ���ӳ�
        //  ��ȡǰһ������״̬������0x00���ӳ�1�룬�����Ĵ�ÿ�ζ�������ʱ1�롣����ִ����֮���ӳ�2�룬ִ����һ������
        //���ȡǰһ������״̬������0x01���ӳ�3�롣ִ����һ������
        //������0x00��ȷ����ִ�б���Sensor����Ŀ��ֵ����ɺ�����״̬��0x01
        E_OrderStatus=1;
    }
    else
    {
        E_OrderStatus=1;
    }
    
}
#endif //#if (_BEACON_GAMMA_AUTO_PROCESS_SUPPORT == _ON)      

#if (_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)

BYTE code C_MonitorType[] = MONITOR_TYPE;
BYTE code C_SerialNumber[] = MONITOR_SN;

BYTE code C_GammaName[] = GAMMA_NAME_INFO;

//BYTE code C_FWVersion[] = FW_VERSION;

void ReadGammaName(BYTE *buffer, BYTE IndexDelta)
{
	BYTE ucIndex;
	
	for(ucIndex=0;ucIndex<ORDER_PART2_DATE_LEN;ucIndex++)
	{
		buffer[ucIndex] = '\0';
		if(C_GammaName[ucIndex+IndexDelta*ORDER_PART2_DATE_LEN]!= '\0')
		{
			buffer[ucIndex] = C_GammaName[ucIndex+IndexDelta*ORDER_PART2_DATE_LEN];
		}
        else
        {
            break;
        }
	}	
}

void ReadModelName(BYTE *buffer, BYTE IndexDelta)
{
	BYTE ucIndex,SN_Buffer[_SN_BUF_LENGTH];
	BYTE ucResult=_FAIL;

    // Clear buffer for new message
    memset(&buffer[IndexDelta], 0, _FT_MonitorModelSize);
        
    // Get EDID SN Data
	ucResult = RTDNVRamLoadMonitorSNData(&SN_Buffer[0]);  

    ucIndex = 0;
    if((ucResult==_SUCCESS)&&
       (((SN_Buffer[0] >= 0x30)&&(SN_Buffer[0] <= 0x39))||((SN_Buffer[0] >= 0x41)&&(SN_Buffer[0] <= 0x5A))||((SN_Buffer[0] >= 0x61)&&(SN_Buffer[0] <= 0x7A)))&& \
       (((SN_Buffer[1] >= 0x30)&&(SN_Buffer[1] <= 0x39))||((SN_Buffer[1] >= 0x41)&&(SN_Buffer[1] <= 0x5A))||((SN_Buffer[1] >= 0x61)&&(SN_Buffer[1] <= 0x7A)))&& \
       (((SN_Buffer[2] >= 0x30)&&(SN_Buffer[2] <= 0x39))||((SN_Buffer[2] >= 0x41)&&(SN_Buffer[2] <= 0x5A))||((SN_Buffer[2] >= 0x61)&&(SN_Buffer[2] <= 0x7A)))&& \
       (((SN_Buffer[3] >= 0x30)&&(SN_Buffer[3] <= 0x39))||((SN_Buffer[3] >= 0x41)&&(SN_Buffer[3] <= 0x5A))||((SN_Buffer[3] >= 0x61)&&(SN_Buffer[3] <= 0x7A))))
    {
        DebugMessageUart("Replace Name:", SN_Buffer[0]);
        for(ucIndex = 0; ucIndex < _REPLACE_NAME_LENGTH; ucIndex++)
        {
			buffer[ucIndex+IndexDelta] = SN_Buffer[ucIndex];
	        DebugMessageUart(":", buffer[ucIndex+IndexDelta]);
        }
    }
    DebugMessageUart("ucIndex:", ucIndex);

	for(ucIndex = ucIndex; ucIndex < _FT_MonitorModelSize; ucIndex++)
	{
		//buffer[ucIndex+IndexDelta] = '\0';
		if(C_MonitorType[ucIndex]!= '\0')
		{
			buffer[ucIndex+IndexDelta] = C_MonitorType[ucIndex];
            DebugMessageUart("*", buffer[ucIndex+IndexDelta]);
		}
        else
        {
            break;
        }
	}	
}

void ReadSnHeader(BYTE *buffer, BYTE IndexDelta)
{
	BYTE ucIndex,SN_Buffer[_SN_BUF_LENGTH];
	BYTE ucResult=_FAIL;

    // Clear buffer for new message
    memset(&buffer[IndexDelta], 0, _SN_BUF_LENGTH);

    // Get EDID SN Data
	ucResult = RTDNVRamLoadMonitorSNData(&SN_Buffer[0]);  

    if(ucResult == _SUCCESS)
    {
        if((((SN_Buffer[0] >= 0x30)&&(SN_Buffer[0] <= 0x39))||((SN_Buffer[0] >= 0x41)&&(SN_Buffer[0] <= 0x5A))||((SN_Buffer[0] >= 0x61)&&(SN_Buffer[0] <= 0x7A)))&& \
           (((SN_Buffer[1] >= 0x30)&&(SN_Buffer[1] <= 0x39))||((SN_Buffer[1] >= 0x41)&&(SN_Buffer[1] <= 0x5A))||((SN_Buffer[1] >= 0x61)&&(SN_Buffer[1] <= 0x7A)))&& \
           (((SN_Buffer[2] >= 0x30)&&(SN_Buffer[2] <= 0x39))||((SN_Buffer[2] >= 0x41)&&(SN_Buffer[2] <= 0x5A))||((SN_Buffer[2] >= 0x61)&&(SN_Buffer[2] <= 0x7A)))&& \
           (((SN_Buffer[3] >= 0x30)&&(SN_Buffer[3] <= 0x39))||((SN_Buffer[3] >= 0x41)&&(SN_Buffer[3] <= 0x5A))||((SN_Buffer[3] >= 0x61)&&(SN_Buffer[3] <= 0x7A))))
        {
            for(ucIndex = 0; ucIndex < _SN_BUF_LENGTH; ucIndex++)
            {
    			buffer[ucIndex+IndexDelta] = SN_Buffer[ucIndex];
            }
        }
    	else
    	{
            // The EDID SN is not written, so the preset SN is read
     		for(ucIndex=0;ucIndex<_SN_BUF_LENGTH;ucIndex++)
    		{
    			//buffer[ucIndex+IndexDelta] = '\0'; 
    			if(C_SerialNumber[ucIndex]!= '\0')
    			{
    				buffer[ucIndex+IndexDelta] = C_SerialNumber[ucIndex];
    			}
                else
                {
                    break;
                }
    		}
    	}
    }
}

void ReadFWVersion(BYTE *buffer, BYTE IndexDelta)
{
	BYTE ucIndex;

    // Clear buffer for new message
    memset(&buffer[IndexDelta], 0, _SN_BUF_LENGTH);
	for(ucIndex=0;ucIndex<_SN_BUF_LENGTH;ucIndex++)
	{
		//buffer[ucIndex+IndexDelta] = '\0';
		if(C_FWVersion[ucIndex]!= '\0')
		{
			buffer[ucIndex+IndexDelta] = C_FWVersion[ucIndex];
		}
        else
        {
            break;
        }
	}	
}

BYTE ReadLut_ID_GammaIndex(BYTE Lut_id)
{
    BYTE ucLutIndex,gamma_table;

    DebugMessageUart("Lut_id:", Lut_id);
    ucLutIndex = (Lut_id & 0x1F);
    //DebugMessageUart("gamma_table_index:", ucLutIndex);
    // Lut_id to UI Gamma Index
    if((ucLutIndex >= _GAMMA_OFF)&&(ucLutIndex <= _GAMMA_AMOUNT)) 
    {
        // Get Gamma Index
        if((ucLutIndex >= _GAMMA_OFF)&&(ucLutIndex <= _GAMMA_AMOUNT)) 
    	{
			if(ucLutIndex == 0)
		    {
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
				gamma_table = _GAMMA_24;
#else
				gamma_table = _GAMMA_CALIB;
#endif
    DebugMessageUart("gamma_table_index0:", gamma_table);

		    }
			else if(ucLutIndex == 1)
		    {
				gamma_table = _GAMMA_OFF;
    DebugMessageUart("gamma_table_index1:", gamma_table);
                
		    }
			else
			{
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex >= 5)
                {
    				gamma_table = _GAMMA_20;      //  DICOM ALC
    				SET_OSD_DICOMALC((ucLutIndex - 5) + _ALC_CT_MR_NM);	
                    DebugMessageUart("Set_DICOMALC:", GET_OSD_DICOMALC());
                }
                //else if(ucLutIndex == 5)
                //{
    			//	gamma_table = _GAMMA_26;      //  Hybrid
                //}
                else
                {
                    if(ucLutIndex == 3) //  DICOM ALC
                    {
        				SET_OSD_DICOMALC(_ALC_X_RAY);	
                        DebugMessageUart("Set_DICOMALC:", GET_OSD_DICOMALC());
                    }
    				gamma_table = ucLutIndex - 1; //_GAMMA_18 = 2-1;
                }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex >= 7)
                {
    				gamma_table = _GAMMA_26;      //  DICOM ALC
    				SET_OSD_DICOMALC((ucLutIndex - 7) + _ALC_CT_MR_NM);	
                    DebugMessageUart("Set_DICOMALC:", GET_OSD_DICOMALC());
                }
                else
                {
                    if(ucLutIndex == 6) //  DICOM ALC
                    {
        				SET_OSD_DICOMALC(_ALC_X_RAY);	
                        DebugMessageUart("Set_DICOMALC:", GET_OSD_DICOMALC());
                    }
                    gamma_table = ucLutIndex - 1; //_GAMMA_18 = 2-1;
                }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex >= 12)
                {
    				gamma_table = _GAMMA_DICOM450;      //  DICOM ALC
    				SET_OSD_DICOMALC((ucLutIndex - 12) + _ALC_CT_MR_NM);	
                    DebugMessageUart("Set_DICOMALC:", GET_OSD_DICOMALC());
                }
                else
                {
                    if(ucLutIndex == 8) //  DICOM ALC
                    {
        				SET_OSD_DICOMALC(_ALC_X_RAY);	
                        DebugMessageUart("Set_DICOMALC:", GET_OSD_DICOMALC());
                    }
    				gamma_table = ucLutIndex - 1; //_GAMMA_18 = 2-1;
                }

#else
				gamma_table = ucLutIndex - 1; //_GAMMA_18 = 2-1;
#endif
			}
    	}
		else
	    {
			gamma_table = _DEFAULT_GAMMA;
	    }
    }
    DebugMessageUart("gamma_table2:", gamma_table);
	return gamma_table;
}


BYTE ReadLut_ID_ColorTempIndex(BYTE Lut_id)
{
    BYTE ucCTIndex,color_temp;

    ucCTIndex = ((Lut_id & (_BIT7|_BIT6|_BIT5)) >> 5) & 0x07;
   /* if(IsMonoChromeorColorPanel() == M_MONO)		 
    {
        if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
        {
        ucCTIndex = 2;
        }
        else
        {
        ucCTIndex = 1;
        }
    }*/
                        
    // Lut_id to UI ColorTemp Index
    if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
    {
    	if(ucCTIndex == 2)
    		color_temp = _CT_9300;
    	else if(ucCTIndex == 1)
    		color_temp = _CT_7500;
    	else
    		color_temp = _CT_6500; 
    }
    else
    {
    	if(ucCTIndex == 1)
    		color_temp = _CT_9300;
    	else
    		color_temp = _CT_6500; 
    }    
    	
	return color_temp;
}

bit  SaveGammaLutDataToNVRam(BYTE Lut_id,WORD usDataIndex, BYTE ucDataLen,BYTE *Buffer)
{
    WORD usAddress;
    BYTE ucResult;
    
    BYTE ucLutIndex,ucCTIndex,ucWriteBank;

    // BeaconMonitorManager Tool protocol V4.1:CAL-OFF-1.8-2.0-2.2
	// Lut_id: CAL=0 OFF=1 Others- reserved
    // BeaconMonitorManager Gets Lut_id from:_DDCCI_SENSOR_CALIB_GET_CURRENT_GAMMA
	// For Embedded QA Redefine:Lut_id [Bit7~Bit5]is the color temperature Index [Bit4~Bit0] is the Gamma Tab Index
    
    ucLutIndex = ReadLut_ID_GammaIndex(Lut_id);
    ucCTIndex = ReadLut_ID_ColorTempIndex(Lut_id);

    if(usDataIndex == 0)
    {
    	DebugMessageUart("W Lut:", ucLutIndex);
    	//DebugMessageUart("CT:", ucCTIndex);
    }

#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_20)
    {
        //  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY) 
	    {
			ucLutIndex = (Lut_id & 0x1F);	
	    }
        DebugMessageUart("W ALC New Lut:", ucLutIndex);
    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_26)
    {
        //  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY) 
	    {
			ucLutIndex = (Lut_id & 0x1F) - 1;	
	    }
        DebugMessageUart("W ALC New Lut:", ucLutIndex);
    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_DICOM450)
    {
        //  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY) 
	    {
			ucLutIndex = (Lut_id & 0x1F) - 1;	
	    }
        DebugMessageUart("W ALC New Lut:", ucLutIndex);
    }

#endif
    
    if(1)
    {
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
        // CAL Write is PC Calibration
    	if(ucLutIndex == _GAMMA_24)// (Lut_id == 0)
    	{
            DebugMessageUart("W PC Lut:", ucLutIndex);
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
            // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
    	    
    	    usAddress = (WORD)(_BEACON_OGC_CALIB1_ADDRESS + usDataIndex);
            ucWriteBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
        }
        // Native
    	else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
    	{
        	return _FALSE;
    	}
        // Write data is GAMMA 2.2
    	else if(ucLutIndex == _GAMMA_18) 
    	{
            DebugMessageUart("W 2.2 Lut:", ucLutIndex);
            if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
            {
                #warning "_THREE_CT_SUPPORT"
                if(ucCTIndex == _CT_9300) 
            	{   // _CT_9300
            	}
            	else if(ucCTIndex == _CT_7500)
            	{   // _CT_7500
            	}
            	else if(ucCTIndex == _CT_6500)
            	{   // _CT_6500 
            	}  
            }
            else
    	    {
                if(ucCTIndex == _CT_9300) 
            	{   // _CT_9300
            	    usAddress = (WORD)(_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            	}
            	else if(ucCTIndex == _CT_6500)
            	{   // _CT_6500
            	    usAddress = (WORD)(_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            	}
    	    }
    	} 
        // Write data is DICOM
    	else if(ucLutIndex == _GAMMA_20) 
    	{
            DebugMessageUart("W Dicom Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
        // Write data is User: MCU Calibration
    	else if(ucLutIndex == _GAMMA_22) 
    	{
            DebugMessageUart("W MCU Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
            	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        	    {
            	    usAddress = (WORD)(_BEACON_OGC_CALIB2_ADDRESS + usDataIndex);
        	    }
                else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                {
            	    usAddress = (WORD)(_BEACON_OGC_CALIB4_ADDRESS + usDataIndex);
                }
                ucWriteBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
            	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        	    {
            	    usAddress = (WORD)(_BEACON_OGC_CALIB3_ADDRESS + usDataIndex);
        	    }
                else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                {
            	    usAddress = (WORD)(_BEACON_OGC_CALIB5_ADDRESS + usDataIndex);
                }
                ucWriteBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
        	}
    	} 
        //---------------------------------------------------------------
        // Write data is DICOM ALC
    	else if(ucLutIndex == (_GAMMA_DICOM_ALC1 - 1)) 
    	{
            DebugMessageUart("W ALC1 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if(ucLutIndex == (_GAMMA_DICOM_ALC2 - 1)) 
    	{
            DebugMessageUart("W ALC2 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if(ucLutIndex == (_GAMMA_DICOM_ALC3 - 1)) 
    	{
            DebugMessageUart("W ALC3 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
    	else if(ucLutIndex == (_GAMMA_DICOM_ALC4 - 1)) 
    	{
            DebugMessageUart("W ALC4 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
    	else if(ucLutIndex == (_GAMMA_DICOM_ALC5 - 1)) 
    	{
            DebugMessageUart("W ALC5 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
        //---------------------------------------------------------------
        else
        {
        	return _FALSE;
            // Null
        }

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
        // CAL Write is PC Calibration
    	if(ucLutIndex == _GAMMA_CALIB)// (Lut_id == 0)
    	{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
            // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
    	    
    	    usAddress = (WORD)(_BEACON_OGC_CALIB1_ADDRESS + usDataIndex);
            ucWriteBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
        }
        // Native
    	else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
    	{
        	return _FALSE;
    	}
        // Write data is GAMMA 2.0
    	else if(ucLutIndex == _GAMMA_18) 
    	{
            if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
            {
                #warning "_THREE_CT_SUPPORT"
                if(ucCTIndex == _CT_9300) 
            	{   // _CT_9300
            	}
            	else if(ucCTIndex == _CT_7500)
            	{   // _CT_7500
            	}
            	else if(ucCTIndex == _CT_6500)
            	{   // _CT_6500 
            	}  
            }
            else
    	    {
                if(ucCTIndex == _CT_9300) 
            	{   // _CT_9300
            	    usAddress = (WORD)(_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            	}
            	else if(ucCTIndex == _CT_6500)
            	{   // _CT_6500
            	    usAddress = (WORD)(_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            	}
    	    }
    	} 
        // Write data is GAMMA 2.2
    	else if(ucLutIndex == _GAMMA_20) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
        // Write data is GAMMA 2.4
    	else if(ucLutIndex == _GAMMA_22) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}     	 
        // Write data is GAMMA 2.6
    	else if(ucLutIndex == _GAMMA_24) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}  
        // Write data is DICOM
    	else if(ucLutIndex == _GAMMA_26) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
        //---------------------------------------------------------------
        // Write data is DICOM ALC
    	else if(ucLutIndex == _GAMMA_DICOM_ALC1) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if(ucLutIndex == _GAMMA_DICOM_ALC2) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if(ucLutIndex == _GAMMA_DICOM_ALC3) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
    	else if(ucLutIndex == _GAMMA_DICOM_ALC4) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
    	else if(ucLutIndex == _GAMMA_DICOM_ALC5) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA10_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA10_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
        //---------------------------------------------------------------
        else
        {
        	return _FALSE;
            // Null
        }
        
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
        // CAL Write is PC Calibration
    	if(ucLutIndex == _GAMMA_CALIB)// (Lut_id == 0)
    	{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
            // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
    	    
    	    usAddress = (WORD)(_BEACON_OGC_CALIB1_ADDRESS + usDataIndex);
            ucWriteBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
        }
        // Native
    	else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
    	{
        	return _FALSE;
    	}
        // Write data is GAMMA 2.2
    	else if(ucLutIndex == _GAMMA_18) 
        {
            if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
            {
 
            }
            else
    	    {
                if(ucCTIndex == _CT_9300) 
            	{   // _CT_9300
            	    usAddress = (WORD)(_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            	}
            	else if(ucCTIndex == _CT_6500)
            	{   // _CT_6500
            	    usAddress = (WORD)(_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            	}
    	    }
    	}
        // Write data is Multi DICOM
    	else if((ucLutIndex >= _GAMMA_DICOM200)&&(ucLutIndex <= _GAMMA_DICOM300))
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}     	 
    	else if((ucLutIndex >= _GAMMA_DICOM350)&&(ucLutIndex <= _GAMMA_DICOM450))
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if((ucLutIndex >= _GAMMA_DICOM500)&&(ucLutIndex <= _GAMMA_DICOM600))
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
        //---------------------------------------------------------------
        // Write data is DICOM ALC
    	else if(ucLutIndex == _GAMMA_DICOM_ALC1) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if(ucLutIndex == _GAMMA_DICOM_ALC2) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	} 
    	else if(ucLutIndex == _GAMMA_DICOM_ALC3) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
    	else if(ucLutIndex == _GAMMA_DICOM_ALC4) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
    	else if(ucLutIndex == _GAMMA_DICOM_ALC5) 
    	{
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
        	    usAddress = (WORD)(_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucWriteBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
        	}
    	}
        //---------------------------------------------------------------
        else
        {
        	return _FALSE;
            // Null
        }
#else
#warning "!!!Please Check Gamma define"
#endif  // End of #if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)

        ucResult = UserCommonFlashWrite(ucWriteBank, usAddress, ucDataLen, (BYTE *)Buffer );

#else
    	ucResult = UserCommonEepromWrite(usAddress, ucDataLen, (BYTE *)Buffer );
#endif

    	return ucResult;
    }
}

void WriteLutData_Factory(WORD usDataIndex,BYTE ucDataLen,BYTE *GammaData,BYTE Lut_id)  
{
	WORD W_IndexDelta;
    BYTE ucResult;
	
	W_IndexDelta = 0;//Channel*2052;
	
	// Is received index and count valid?    
	if((usDataIndex + ucDataLen)<= _BEACON_OGC_GAMMA_TABLE_SIZE)
	{
		ucResult = SaveGammaLutDataToNVRam(Lut_id,(W_IndexDelta + usDataIndex),ucDataLen,GammaData);
        
		if(ucResult == _SUCCESS)
		{

		}
		else
		{

		}
	}
}

void ReadLutData_Factory(WORD usDataIndex,BYTE ucDataLen,BYTE Lut_id,BYTE *buffer) 
{								
	WORD W_NvramAddr;
	BYTE ucResult=_FALSE;
	BYTE Bp_Data[ORDER_PART_DATE_LEN];
	BYTE ucIndex;

    BYTE ucLutIndex,ucCTIndex,ucReadBank;
    
    // BeaconMonitorManager Tool protocol V4.1:CAL-OFF-1.8-2.0-2.2
	// Lut_id: CAL=0 OFF=1 Others- reserved
    // BeaconMonitorManager Gets Lut_id from:_DDCCI_SENSOR_CALIB_GET_CURRENT_GAMMA
	// For Embedded QA Redefine:Lut_id [Bit7~Bit5]is the color temperature Index [Bit4~Bit0] is the Gamma Tab Index

    ucLutIndex = ReadLut_ID_GammaIndex(Lut_id);
    ucCTIndex = ReadLut_ID_ColorTempIndex(Lut_id);

    if(usDataIndex == 0)
    {
    	DebugMessageUart("R Lut:", ucLutIndex);
        //DebugMessageUart("CT =", ucCTIndex);
    }

#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_20)
    {
		//  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY)
	    {
			ucLutIndex = (Lut_id & 0x1F);	
	    }
        DebugMessageUart("R ALC New Lut:", ucLutIndex);
    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_26)
    {
		//  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY)
	    {
			ucLutIndex = (Lut_id & 0x1F) - 1;	
	    }
        DebugMessageUart("R ALC New Lut:", ucLutIndex);
    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_DICOM450)
    {
		//  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY)
	    {
			ucLutIndex = (Lut_id & 0x1F) - 1;	
	    }
        DebugMessageUart("R ALC New Lut:", ucLutIndex);
    }

#endif

	if(1)//(IsGammaOptionPCCalibration(GET_OSD_GAMMA()))// is the gamma calibrated with color sensor.
    {
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
	    // CAL is PC Calibration
		if(ucLutIndex == _GAMMA_24)//(Lut_id == 0)
		{
            DebugMessageUart("R PC Lut:", ucLutIndex);
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
	        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
            // BeaconMonitorManager3.25 QA Support and protocol version > 5.0
            
			W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
	    // Native
		else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
		{
    		// Avoid DDCCI communication crash and activate key
            ucResult=_FALSE;
            UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _OFF);
		}
        // Read data is Gamma 2.2
		else if(ucLutIndex == _GAMMA_18) 
		{
            DebugMessageUart("R 2.2 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is DICOM
		else if(ucLutIndex == _GAMMA_20) 
		{            
            DebugMessageUart("R Dicom Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is MCU Calibration
		else if(ucLutIndex == _GAMMA_22)   
		{
            DebugMessageUart("R MCU Lut:", ucLutIndex);
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
            
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
            	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        	    {
            	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB2_ADDRESS + usDataIndex);
        	    }
                else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                {
            	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB4_ADDRESS + usDataIndex);
                }
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
            	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        	    {
            	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB3_ADDRESS + usDataIndex);
        	    }
                else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                {
            	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB5_ADDRESS + usDataIndex);
                }
        	}
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}		
        //------------------------------------------------------------------------
        // Read data is DICOM ALC
		else if(ucLutIndex == (_GAMMA_DICOM_ALC1 - 1)) 
		{            
            DebugMessageUart("R ALC1 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC2 - 1)) 
		{            
            DebugMessageUart("R ALC2 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC3 - 1)) 
		{            
            DebugMessageUart("R ALC3 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC4 - 1)) 
		{            
            DebugMessageUart("R ALC4 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC5 - 1)) 
		{            
            DebugMessageUart("R ALC5 Lut:", ucLutIndex);
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}        
        //------------------------------------------------------------------------
		else
		{
    		// BeaconMonitorManager3.22 QA only read current data
			{
				//------------------------------------------------------------------
				// Read data is Gamma 2.2
				if(GET_OSD_GAMMA() == _GAMMA_18)
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				// Read data is DICOM
				else if(GET_OSD_GAMMA() == _GAMMA_20)
				{
					if(GET_OSD_DICOMALC() > _ALC_X_RAY)
    					W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex + GET_OSD_DICOMALC()*_BEACON_OGC_GAMMA_TABLE_SIZE);
                    else
    					W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
                // Read data is MCU Calibration
				else if(GET_OSD_GAMMA() == _GAMMA_22)
				{
                    ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
                    
                    if(GET_COLOR_TEMP_TYPE() < _CT_6500) 
                	{   // _CT_9300
                    	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
                	    {
                    	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB2_ADDRESS + usDataIndex);
                	    }
                        else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                        {
                    	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB4_ADDRESS + usDataIndex);
                        }
                	}
                	else
                	{   // _CT_6500 
                    	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
                	    {
                    	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB3_ADDRESS + usDataIndex);
                	    }
                        else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                        {
                    	    W_NvramAddr = (WORD)(_BEACON_OGC_CALIB5_ADDRESS + usDataIndex);
                        }
                	}
				}		
                // Read data is PC Calibration
				else if(GET_OSD_GAMMA() == _GAMMA_24)
				{
                    W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                    ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
				}				
				else 
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
                }
				//------------------------------------------------------------------

                ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
			}

		}

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
	    // CAL is PC Calibration
		if(ucLutIndex == _GAMMA_CALIB)//(Lut_id == 0)
		{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
	        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
            // BeaconMonitorManager3.25 QA Support and protocol version > 5.0
            
			W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
	    // Native
		else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
		{
    		// Avoid DDCCI communication crash and activate key
            ucResult=_FALSE;
            UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _OFF);
		}
        // Read data is Gamma 2.0
		else if(ucLutIndex == _GAMMA_18) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is Gamma 2.2
		else if(ucLutIndex == _GAMMA_20) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is Gamma 2.4
		else if(ucLutIndex == _GAMMA_22) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is Gamma 2.6
		else if(ucLutIndex == _GAMMA_24) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is DICOM
		else if(ucLutIndex == _GAMMA_26) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        //------------------------------------------------------------------------
        // Read data is DICOM ALC
		else if(ucLutIndex == _GAMMA_DICOM_ALC1) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC2) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC3) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC4) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC5) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA10_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA10_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}        
        //------------------------------------------------------------------------
		else
		{
    		// BeaconMonitorManager3.22 QA only read current data
			{
				//------------------------------------------------------------------
				// Read data is Gamma 2.0
				if(GET_OSD_GAMMA() == _GAMMA_18)
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				// Read data is Gamma 2.2
				if(GET_OSD_GAMMA() == _GAMMA_20)
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				// Read data is Gamma 2.4
				if(GET_OSD_GAMMA() == _GAMMA_22)
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				// Read data is Gamma 2.6
				if(GET_OSD_GAMMA() == _GAMMA_24)
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				// Read data is DICOM
				else if(GET_OSD_GAMMA() == _GAMMA_26)
				{
					if(GET_OSD_DICOMALC() > _ALC_X_RAY)
    					W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex + GET_OSD_DICOMALC()*_BEACON_OGC_GAMMA_TABLE_SIZE);
                    else
    					W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				else 
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
                }
				//------------------------------------------------------------------

                ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
			}

		}

#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
	    // CAL is PC Calibration
		if(ucLutIndex == _GAMMA_CALIB)//(Lut_id == 0)
		{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
	        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
            // BeaconMonitorManager3.25 QA Support and protocol version > 5.0
            
			W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
	    // Native
		else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
		{
    		// Avoid DDCCI communication crash and activate key
            ucResult=_FALSE;
            UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _OFF);
		}
        // Read data is Gamma 2.2
		else if(ucLutIndex == _GAMMA_18) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
        // Read data is Multi DICOM
		else if((ucLutIndex >= _GAMMA_DICOM200)&&(ucLutIndex <= _GAMMA_DICOM300)) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if((ucLutIndex >= _GAMMA_DICOM350)&&(ucLutIndex <= _GAMMA_DICOM450)) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if((ucLutIndex >= _GAMMA_DICOM500)&&(ucLutIndex <= _GAMMA_DICOM600)) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}				
        //------------------------------------------------------------------------
        // Read data is DICOM ALC
		else if(ucLutIndex == _GAMMA_DICOM_ALC1) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA5_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC2) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA6_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC3) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA7_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC4) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA8_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC5) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = (_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = (_BEACON_OGC_GAMMA9_ADDRESS + usDataIndex);
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
            ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
		}        
        //------------------------------------------------------------------------
		else
		{
    		// BeaconMonitorManager3.22 QA only read current data
			{
				//------------------------------------------------------------------
				if(GET_OSD_GAMMA() == _GAMMA_18)
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				else if((GET_OSD_GAMMA() >= _GAMMA_DICOM200)&&(GET_OSD_GAMMA() <= _GAMMA_DICOM300))
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA2_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				else if((GET_OSD_GAMMA() >= _GAMMA_DICOM350)&&(GET_OSD_GAMMA() <= _GAMMA_DICOM450))
				{
					if(GET_OSD_DICOMALC() > _ALC_X_RAY)
    					W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex + GET_OSD_DICOMALC()*_BEACON_OGC_GAMMA_TABLE_SIZE);
                    else
    					W_NvramAddr = (_BEACON_OGC_GAMMA3_ADDRESS + usDataIndex);

    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
				else if((GET_OSD_GAMMA() >= _GAMMA_DICOM500)&&(GET_OSD_GAMMA() <= _GAMMA_DICOM600))
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA4_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
				}
                else 
				{
					W_NvramAddr = (_BEACON_OGC_GAMMA1_ADDRESS + usDataIndex);
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
    		    	}
    		        else
    		    	{
                        ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
    		    	}
                }
				//------------------------------------------------------------------

                ucResult = UserCommonFlashRead(ucReadBank, W_NvramAddr, ucDataLen, Bp_Data );
			}

		}
#else
#warning "!!!Please Check Gamma define"

#endif  // End of #if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)

#else
    	ucResult = UserCommonEepromRead(W_NvramAddr, ucDataLen, Bp_Data );
#endif
    }
    else
    {
        // load gamma table
    }

    //avoid crash Ddcci communication module
    if(ucDataLen > ORDER_PART_DATE_LEN)
    {
        ucDataLen = ORDER_PART_DATE_LEN;
    }
    //--------------------------------------

	if(ucResult == _SUCCESS)
	{
		buffer[0] = 0x6e;	// Source
		buffer[1] = (0x80|(6 + ucDataLen)); // Length
		
		buffer[2] = 0xc2;	// Prefix 0xC2
		buffer[3] = _DDCCI_SENSOR_CALIB_GET_LUT_DATA; //CMD
		buffer[4] = ucDataLen;
		buffer[5] = Lut_id;
		buffer[6] = (BYTE)(usDataIndex&0xFF);
		buffer[7] = (BYTE)(usDataIndex>>8);
		for(ucIndex = 0; ucIndex < ucDataLen; ucIndex++)
		{
			buffer[8 + ucIndex] = Bp_Data[ucIndex];
		}
		
    	buffer[8+ucDataLen] = UserCommonDdcciCalCheckSum(); // checksum
	}
	else
	{
		buffer[0] = 0x6e;	 // Source
		buffer[1] = 0x80;    // Length
            	        
    	buffer[2] = UserCommonDdcciCalCheckSum(); // checksum
	}
}

void ReadLutData_CalCheckSum(BYTE Lut_id,BYTE *buffer) 
{
    WORD usI = 0;
    WORD usJ = 0;
    BYTE ucReadBank = 0;
    
    BYTE ucLutIndex,ucCTIndex;                    
 	WORD W_NvramAddr;
   	BYTE ucResult=_FALSE;

    ucLutIndex = ReadLut_ID_GammaIndex(Lut_id);
    ucCTIndex = ReadLut_ID_ColorTempIndex(Lut_id);

#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_20)
    {
		//  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY)
	    {
			ucLutIndex = (Lut_id & 0x1F);	
	    }
        DebugMessageUart("R ALC New Lut:", ucLutIndex);
    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_26)
    {
		//  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY)
	    {
			ucLutIndex = (Lut_id & 0x1F) - 1;	
	    }
        DebugMessageUart("R ALC New Lut:", ucLutIndex);
    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
    // !!! must sync GAMMA_NAME_INFO
    if(ucLutIndex == _GAMMA_DICOM450)
    {
		//  DICOM ALC
		if(GET_OSD_DICOMALC() > _ALC_X_RAY)
	    {
			ucLutIndex = (Lut_id & 0x1F) - 1;	
	    }
        DebugMessageUart("R ALC New Lut:", ucLutIndex);
    }
#endif

	if(1)
    {
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
	    // CAL
		if(ucLutIndex == _GAMMA_24)//(Lut_id == 0)
		{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
	        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
            // BeaconMonitorManager QA Support and protocol version > 5.0
            
			W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
		}
	    // Native
		else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
		{

		}
        // Read & Embedded calibration Ref data is  GAMMA 2.2
		else if(ucLutIndex == _GAMMA_18) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        // Read data is Dicom
		else if(ucLutIndex == _GAMMA_20) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA2_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA2_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        // Read data is MCU Calibration
		else if(ucLutIndex == _GAMMA_22) 
		{
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
            
            if(ucCTIndex == _CT_9300) 
        	{   // _CT_9300
            	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        	    {
            	    W_NvramAddr = _BEACON_OGC_CALIB2_ADDRESS;
        	    }
                else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                {
            	    W_NvramAddr = _BEACON_OGC_CALIB4_ADDRESS;
                }
        	}
        	else if(ucCTIndex == _CT_6500)
        	{   // _CT_6500 
            	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        	    {
            	    W_NvramAddr = _BEACON_OGC_CALIB3_ADDRESS;
        	    }
                else if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)
                {
            	    W_NvramAddr = _BEACON_OGC_CALIB5_ADDRESS;
                }
        	}
		}		
        //---------------------------------------------------------
        // Read data is Dicom ALC
		else if(ucLutIndex == (_GAMMA_DICOM_ALC1 - 1)) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA3_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA3_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC2 - 1)) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA4_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA4_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC3 - 1)) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA5_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA5_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC4 - 1)) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA6_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA6_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == (_GAMMA_DICOM_ALC5 - 1)) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA7_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA7_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}		
        //---------------------------------------------------------
		else
		{
            // 	
		}

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
	    // CAL
		if(ucLutIndex == _GAMMA_CALIB)//(Lut_id == 0)
		{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
	        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
            // BeaconMonitorManager QA Support and protocol version > 5.0
            
			W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
		}
	    // Native
		else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
		{

		}
        // Read data is GAMMA 2.0
		else if(ucLutIndex == _GAMMA_18) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        // Read data is Gamma 2.2
		else if(ucLutIndex == _GAMMA_20) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA2_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA2_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        // Read data is Gamma 2.4
		else if(ucLutIndex == _GAMMA_22) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA3_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA3_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}				
        // Read data is Gamma 2.6
		else if(ucLutIndex == _GAMMA_24) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA4_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA4_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        // Read data is DICOM
		else if(ucLutIndex == _GAMMA_26) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA5_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA5_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        //---------------------------------------------------------
        // Read data is DICOM ALC
		else if(ucLutIndex == _GAMMA_DICOM_ALC1) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA6_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA6_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC2) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA7_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA7_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC3) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA8_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA8_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC4) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA9_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA9_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC5) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA10_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA10_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}		
        //---------------------------------------------------------
		else
		{
            // 	
		}
        
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
	    // CAL
		if(ucLutIndex == _GAMMA_CALIB)//(Lut_id == 0)
		{
            // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
	        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 
            // BeaconMonitorManager QA Support and protocol version > 5.0
            
			W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
            ucReadBank = _BEACON_GAMMA_CALIBRATION_FLASH_BANK;
		}
	    // Native
		else if(ucLutIndex == _GAMMA_OFF)//(Lut_id == 1)
		{

		}
        // Read & Embedded calibration Ref data is  GAMMA 2.2
		else if(ucLutIndex == _GAMMA_18) 
		{            
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA1_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        // Read data is Multi Dicom
		else if((ucLutIndex >= _GAMMA_DICOM200)&&(ucLutIndex <= _GAMMA_DICOM300))
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA2_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA2_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if((ucLutIndex >= _GAMMA_DICOM350)&&(ucLutIndex <= _GAMMA_DICOM450))
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA3_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA3_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if((ucLutIndex >= _GAMMA_DICOM500)&&(ucLutIndex <= _GAMMA_DICOM600))
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA4_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA4_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
        //---------------------------------------------------------
        // Read data is DICOM ALC
		else if(ucLutIndex == _GAMMA_DICOM_ALC1) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA5_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA5_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC2) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA6_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA6_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC3) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA7_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA7_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC4) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA8_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA8_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}
		else if(ucLutIndex == _GAMMA_DICOM_ALC5) 
		{
            if(ucCTIndex == _CT_9300)
            {   // _CT_9300
                W_NvramAddr = _BEACON_OGC_GAMMA9_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
            }
            else if(ucCTIndex == _CT_6500)
            {   // _CT_6500
                W_NvramAddr = _BEACON_OGC_GAMMA9_ADDRESS;
                ucReadBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
            }
		}		
        //---------------------------------------------------------
		else
		{
            // 	
		}
#else
#warning "!!!Please Check Gamma define"

#endif  // End of #if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)

        // [2020-04-10 14:54:03.202]# RECV ASCII> 
        pData[0] = 0;
        pData[1] = 0;
        for(usJ = 0; usJ < 3; usJ++)
        {
            for(usI = 0; usI < 2052; usI = usI + 4)
            {
                ucResult = UserCommonFlashRead(ucReadBank, (W_NvramAddr + usJ * 2052 + usI), 4, pData + 2);

                // BYTE[0]:lut cumulative value, 
                pData[0] += pData[2];
                pData[0] += pData[3];
                pData[0] += pData[4];
                pData[0] += pData[5];
                
                // BYTE[1]:lut XOR value
                pData[1] = pData[1] ^ pData[2];
                pData[1] = pData[1] ^ pData[3];
                pData[1] = pData[1] ^ pData[4];
                pData[1] = pData[1] ^ pData[5];
            }
        }
        // [2020-04-10 14:54:03.283]# RECV ASCII>   

    	if(ucResult == _SUCCESS)
    	{
    		buffer[0] = 0x6e;	// Source
    		buffer[1] = (0x80|(5)); // Length
    		
    		buffer[2] = 0xc2;	// Prefix 0xC2
    		buffer[3] = _DDCCI_SENSOR_CALIB_GET_LUT_DATA; //CMD
    		buffer[4] = Lut_id;
    		buffer[5] = (BYTE)pData[0];
    		buffer[6] = (BYTE)pData[1];
        	buffer[7] = UserCommonDdcciCalCheckSum(); // checksum
    	}
    	else
    	{
    		buffer[0] = 0x6e;	 // Source
    		buffer[1] = 0x80;    // Length
        	buffer[2] = UserCommonDdcciCalCheckSum(); // checksum
    	}
    }
}

void ReadMatrixParaData(void)
{
    BYTE ret;
    BYTE Bp_Data[_FT_MatrixSize];
    BYTE ucIndex;
    SDWORD *pMatrixPara;

    pMatrixPara = &MatrixPara_sensorData.Matrix_Para_r1;

    if(RefreshMatrix==0)///don't read everytime
    {
        ret = UserCommonEepromRead(_FT_MATRIX_ADDRESS, _FT_MatrixSize, Bp_Data );

        if(ret==_SUCCESS)
        {
            for(ucIndex=0;ucIndex<_FT_MatrixSize;ucIndex++)
            {
                *pMatrixPara=(((DWORD)Bp_Data[ucIndex+3])<<24)+(((DWORD)Bp_Data[ucIndex+2])<<16)+(((DWORD)Bp_Data[ucIndex+1])<<8)+Bp_Data[ucIndex];
                pMatrixPara++;
                ucIndex=ucIndex+3;
            }
            RefreshMatrix=1;
        }
    }
    //DebugMessageUart("ReadMatrixParaData:", MatrixPara_sensorData.Matrix_Para_r1);
//OsdDispOsdMessage(_OSD_DISP_DICOM_RESULT);
//OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 14), MatrixPara_sensorData.Matrix_Para_r1, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));
    
}


void FSensor_SetTiming(BYTE uctime)
{
	BYTE ucCmd_Buf[2];

    if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
    {
    	// Timing Register (01h)
    	// Bit[3:0] 0001 100 ms  0010 400 ms
    	ucCmd_Buf[0]=CMD_VALUE|TRANS_BYTE_PROTOC|CMD_SS_TIMING;
    	ucCmd_Buf[1]=uctime;

        if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
        	g_bFrontSensorInitState = _FAIL; 
        }
        else
        {
        	g_bFrontSensorInitState = _DEVICE_ID_TCS3414; 
        }
    }
    else if(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)
    {
    	// ATIME Register (81h)
        // Integration time = (uctime+1)*2.78ms
    	ucCmd_Buf[0]=0x81;
    	ucCmd_Buf[1]=uctime;

        if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
        	g_bFrontSensorInitState = _FAIL; 
        }
        else
        {
        	g_bFrontSensorInitState = _DEVICE_ID_TCS3430; 
        }
    }
    
	FSensor_integrationTime = uctime;
}

void FSensor_SetGain(BYTE Gain)
{
	BYTE ucCmd_Buf[2];
    
    /*if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
    {
    	// Gain Register (07h)
    	// GAIN 5:4 00-1x 01-4x 10-16x 11-64x
    	// PRESCALER 2:0 000-Div 1 001-Div 2 010-Div 4 011-Div 8 100-Div 16 ...
    	ucCmd_Buf[0]=CMD_VALUE|TRANS_BYTE_PROTOC|CMD_SS_ANALOG;
        ucCmd_Buf[1]=(Gain << 4)|0x03; //divide by 8

	    if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
        	g_bFrontSensorInitState = _FAIL; 
        }
        else
        {
        	g_bFrontSensorInitState = _DEVICE_ID_TCS3414; 
        }
    }
    else if(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)
    {
    	// CFG1 Register (90h)
        // AGAIN 1:0  00-1x 01-4x 10-16x 11-64x
        ucCmd_Buf[0] = 0x90;
        ucCmd_Buf[1] = Gain;
        
        if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
        	g_bFrontSensorInitState = _FAIL; 
        }
        else
        {
        	g_bFrontSensorInitState = _DEVICE_ID_TCS3430; 
        }
    }
    else */if(g_bFrontSensorInitState == _DEVICE_ID_VEML3328)
    {
    	// Command code = 0x00 
    	//   DG           bit13-12:  00 = x1(default)  01 = x2          10 = x4   11 = reserved
    	//   GAIN         bit11-10:  11 = x1/2         00 = x1(default) 01 = x2   10 = x4
    	//   SENS         bit6:      0 = high sensitivity(default)  1 = low sensitivity(1/3)
    	//   IT           bit5-4:    Integration time setting 00 = 50ms(default)  01 = 100ms  10 = 200ms 11 = 400ms
    	//   AF           bit3:      Auto/active force mode   0 = auto mode(default)  1 = active force mode
    	//   TRIG         bit2:      Trigger s single measurement when in active mode, This bit resets to 0 automatically 
        
        // GAIN_1X  DG=1x GAIN=1/2 IT=200 or 100 or 50  MSB:0000 1100=0x0C   LSB:0010 0000=0x20 or LSB:0001 0000=0x10 or LSB:0000 0000=0x00
        // GAIN_4X  DG=2x GAIN=1   IT=200 or 100 or 50  MSB:0001 0000=0x10   LSB:0010 0000=0x20 or LSB:0001 0000=0x10 or LSB:0000 0000=0x00
        // GAIN_16X DG=4x GAIN=2   IT=200 or 100 or 50  MSB:0010 0100=0x24   LSB:0010 0000=0x20 or LSB:0001 0000=0x10 or LSB:0000 0000=0x00
        // GAIN_64X DG=4x GAIN=4   IT=400 or 200 or 100 MSB:0010 1000=0x28   LSB:0011 0000=0x30 or LSB:0010 0000=0x20 or LSB:0001 0000=0x10 

        // first
        // 1x1/2  x2   = 1   DG=1x GAIN=1/2 IT=100  MSB:0000 1100=0x0C   LSB:0001 0000=0x10
        // 2x1    x2   = 4   DG=1x GAIN=1   IT=100  MSB:0000 1100=0x10   LSB:0001 0000=0x10
        // 4x2    x2   = 16  DG=4x GAIN=2   IT=100  MSB:0010 0100=0x24   LSB:0001 0000=0x10
        // 4x4    x4   = 64  DG=4x GAIN=4   IT=200  MSB:0010 1000=0x28   LSB:0010 0000=0x20

        // =1/2
        // 1x1/2  x1   = 1   DG=1x GAIN=1/2 IT=50   MSB:0000 1100=0x0C   LSB:0000 0000=0x00
        // 2x1    x1   = 4   DG=1x GAIN=1   IT=50   MSB:0000 1100=0x10   LSB:0000 0000=0x00
        // 4x2    x1   = 16  DG=4x GAIN=2   IT=50   MSB:0010 0100=0x24   LSB:0000 0000=0x00
        // 4x4    x2   = 64  DG=4x GAIN=4   IT=100  MSB:0010 1000=0x28   LSB:0001 0000=0x10

        // =first
        // 1x1/2  x2   = 1   DG=1x GAIN=1/2 IT=100  MSB:0000 1100=0x0C   LSB:0011 0000=0x10
        // 1x1/2  x8   = 4   DG=1x GAIN=1/2 IT=400  MSB:0000 1100=0x0C   LSB:0011 0000=0x30
        // 2x1    x8   = 16  DG=2x GAIN=1   IT=400  MSB:0001 0000=0x10   LSB:0011 0000=0x30
        // 4x2    x8   = 64  DG=4x GAIN=2   IT=400  MSB:0010 0100=0x24   LSB:0011 0000=0x30

        // =1/2
        // 1x1/2  x1   = 1   DG=1x GAIN=1/2 IT=50   MSB:0000 1100=0x0C   LSB:0000 0000=0x00
        // 1x1/2  x4   = 4   DG=1x GAIN=1/2 IT=200  MSB:0000 1100=0x0C   LSB:0010 0000=0x20
        // 1x1    x8   = 16  DG=1x GAIN=1   IT=400  MSB:0000 0000=0x00   LSB:0011 0000=0x30
        // 2x2    x8   = 64  DG=2x GAIN=2   IT=400  MSB:0001 0100=0x14   LSB:0011 0000=0x30

        // Registers (Write:0x00 16Bit)
        if(Gain == GAIN_1X)
        {
            ucCmd_Buf[0]=(0x00|0x0C);   // bit7-0     
            ucCmd_Buf[1]=0x0C;   // bit15-8    
        }
        else if(Gain == GAIN_4X)
        {
            ucCmd_Buf[0]=(0x20|0x0C);   // bit7-0     
            ucCmd_Buf[1]=0x0C;   // bit15-8    
        }
        else if(Gain == GAIN_16X)
        {
            ucCmd_Buf[0]=(0x30|0x0C);   // bit7-0     
            ucCmd_Buf[1]=0x00;   // bit15-8    
        }
        else if(Gain == GAIN_64X)
        {
            ucCmd_Buf[0]=(0x30|0x0C);   // bit7-0     
            ucCmd_Buf[1]=0x14;   // bit15-8    
        }

        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerWaitForEvent(_EVENT_DVS);
        
        if(UserCommonEepromIICWrite(_FRONT_SENSOR_VEML3328_IIC_ADDR, 0x00, 1, 2, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
        	g_bFrontSensorInitState = _FAIL; 
        }
        else
        {
        	g_bFrontSensorInitState = _DEVICE_ID_VEML3328; 
        }
    }
        
	FSensor_Gain = Gain;
}

#if 0 //  MTCSCDCAF Sensor
typedef struct
{
	BYTE b4MTCS_CREG1_GAIN : 4;
	BYTE b4MTCS_CREG1_TIME : 4;
	
	BYTE b1MTCS_CREG2_ENTM : 1;
	BYTE b1MTCS_CREG2_ENDIV : 1;
	BYTE b3MTCS_CREG2_DIV : 3;
	BYTE b2MTCS_CREG3_MMODE : 2;
	BYTE b1MTCS_CREG3_SB : 1;	
	
	BYTE b2MTCS_CREG3_CCLK : 2;
	BYTE b1MTCS_OSR_SS : 1;
	BYTE b1MTCS_OSR_PD : 1;
	BYTE b1MTCS_OSR_SW_RES : 1;
	BYTE b3MTCS_OSR_DOS : 3;
	
}MTCSCDCAF_Workpara;

MTCSCDCAF_Workpara g_workPara;

WORD MTCS_BaseDiv2X(WORD usBaseDiv2x)
{
	WORD value = 1;
	while(usBaseDiv2x--)
	{
	  value *= 2; 
	}
	return value;
}

/*
Desc: find the largest number in a three entry array.
*/
/*
WORD getLargestElement(WORD *pTempData)
{
	WORD usLargest = *pTempData;

	pTempData++;
	if(usLargest < *pTempData)
	{
		usLargest = *pTempData;
	}

	pTempData++;
	if(usLargest < *pTempData)
	{
		usLargest = *pTempData;
	}
	return usLargest;
}
*/
void MTCSCDCAF_InitPara(void)
{
	if(1)
	{
		g_workPara.b4MTCS_CREG1_TIME=0x07;    
		g_workPara.b4MTCS_CREG1_GAIN=0x00;  
		
		g_workPara.b3MTCS_CREG2_DIV=0x07;
		g_workPara.b1MTCS_CREG2_ENDIV=0x01;
		g_workPara.b1MTCS_CREG2_ENTM=0x00,
			
		g_workPara.b2MTCS_CREG3_MMODE=0x01;
		g_workPara.b1MTCS_CREG3_SB=0x00;
		g_workPara.b2MTCS_CREG3_CCLK=0x00;
		
		g_workPara.b1MTCS_OSR_PD=0x00;
	}
}

/*
Desc: configure the parameters in configuration mode, then switch to measure mode.
*/	
BYTE MTCSCDCAF_Init(void)
{
    BYTE ucCmd_Buf[2];

	// OSR ADDR = 0x00 
	// Desc:write Operational State Register.
	//     bit7:   0   = stop measurement    1   = start measurement
	//     bit6:   0   = no power down mode  1   = activate power down mode
	//     bit2-0: 010 = configuration state 011 = measurement state
	
    ucCmd_Buf[0]=0x00;	
	g_workPara.b1MTCS_OSR_SS = 0;  // stop measurement
	g_workPara.b3MTCS_OSR_DOS = 2; // configuration state
    ucCmd_Buf[1]=((g_workPara.b1MTCS_OSR_SS << 7) | g_workPara.b1MTCS_OSR_PD << 6| (g_workPara.b3MTCS_OSR_DOS));	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

	// CREG1 ADDR = 0x06
	// bit7-4: GAIN 0000=2048x 0001=1024x  0010=512x ...1010=2x 1011=1x
	// bit3-0: TIME 0000=1ms 0001=2ms ...0110=64ms 0111=128ms 1000=256ms 1001=512ms 1010=1024ms 1011=2048ms
    ucCmd_Buf[0]=0x06;	 
    ucCmd_Buf[1]=((g_workPara.b4MTCS_CREG1_GAIN<< 4) | (g_workPara.b4MTCS_CREG1_TIME));	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

	// BREAK ADDR = 0x09
	/* setup BREAK  0 to 255*/
	// pause time TBREAK between two measurements(except CMD mode): from 033 to 2040��s, step size 8��s

	ucCmd_Buf[0]=0x09;	 
    ucCmd_Buf[1]= 250; // (g_workPara.ucMTCS_BREAK);	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

	// CREG3 ADDR = 0x08
	// bit7:6  00:CONT mode (continuous measurement) 
	//         01:CMD  mode (measurement per command)
	//         10:SYNS mode (externally synchronized start of measurement)
	//         11:SYND mode (start and end of measurement are externally synchronized)
	// bit 5:  Reserved
	// bit 4:  SB      0:Standby is switched OFF 1:Standby is switched ON
    // bit 3:  RDYOD   0:pin READY operates as Push Pull output 1:pin READY operates as Open Drain output
	// bit 2:  Reserved
	// bit 1:0 CCLK    0:internal clock frequency fCLK = 1.024 MHz 1:2.048 MHz 2:4.096 MHz 3:8.192 MHz
	
    ucCmd_Buf[0]=0x08;	 
    ucCmd_Buf[1]=((g_workPara.b2MTCS_CREG3_MMODE << 6) | (g_workPara.b1MTCS_CREG3_SB << 4) | (g_workPara.b2MTCS_CREG3_CCLK));	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

	// CREG2 ADDR = 0x07
	// bit 7:  Reserved
	// bit 6:  EN_TM 0:In combination with SYND mode the internal measurement of the conversion time is disabled and no temperature measurement takes place.
	//               1:Internal measurement of the externally defined conversion time via SYN pulse in SYND mode is enabled 
	//                 (OUTCONV results are generated as well as temperature values for output register TEMP).
	// bit 5:4 Reserved
	// bit 3:  EN_DIV  0:Digital divider of the measurement result registers is disabled
	//                 1:Digital divider of the measurement result registers is enabled (might be needed @CREG1:TIME > 6 dec)
	// bit 2:0 DIV     000:2  001:4 010:8 011:16 100:32 101:64 110:128 111:256

	if(g_workPara.b1MTCS_CREG2_ENDIV==0)
	{
	    ucCmd_Buf[0]=0x07;	 
	    ucCmd_Buf[1]= 0x08;	
	    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	    {
	        return _FAIL;
	    }
	}

    ucCmd_Buf[0]=0x07;	 
    ucCmd_Buf[1]=((g_workPara.b1MTCS_CREG2_ENTM << 6) | (g_workPara.b1MTCS_CREG2_ENDIV << 3) | (g_workPara.b3MTCS_CREG2_DIV));	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

	// OPTREG ADDR = 0x0B
	// bit 7:1  Reserved
	// bit 0    INIT_IDX  0:Defining the index address is only possible via write sequence and not affected by I2C STOP condition, which is necessary, 
    //                      if the I2C master does not support the I2C Repeated START condition.
    //                    1:Each I2C STOP condition sets the internal register address to the default value. After writing an index address 
    //                      it is possible to change the data direction for reading using I2C Repeated START condition.
    
    ucCmd_Buf[0]=0x0B;	 
    ucCmd_Buf[1]=0x00; 
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
        return _FAIL;
    }

#if 0
	{
	    ucCmd_Buf[0]=0x00;
/*		if(UserCommonEepromIICRead(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 12, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
		{
			return _FAIL;
		}*/
	}
#endif

	return _SUCCESS;
}

/* command measurement mode */
BYTE MTCSCDCAF_Measure(void)
{
    BYTE ucCmd_Buf[2];
    WORD usTimeOutCnt = 50;
	
	// OSR ADDR = 0x00 
	// Desc:write Operational State Register.
	//     bit7    0   = stop measurement    1   = start measurement
	//     bit6    0   = no power down mode  1   = activate power down mode
	//     bit2-0: 010 = configuration state 011 = measurement state
	
    ucCmd_Buf[0]=0x00;
	g_workPara.b1MTCS_OSR_SS = 1;  // Start measurement
	g_workPara.b3MTCS_OSR_DOS = 3; // measurement state
    ucCmd_Buf[1]=((g_workPara.b1MTCS_OSR_SS << 7) | (g_workPara.b1MTCS_OSR_PD << 6) | (g_workPara.b3MTCS_OSR_DOS));	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
		DebugMessageSystem("MTCS Measure OSR=0x00 Fail !!!:", 0);
        return _FAIL;
    }

	//while(PCB_MTCS_READY_PIN_DETECT() == 0)
	{
		// MTCS:The measurement process is low, and the measurement end is high.
		// wait for READY_PIN go low change to _USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END
	}
	
	return _SUCCESS;
}

BYTE MTCSCDCAF_ReadAdcResults(SENSOR_DATA *results)
{
    BYTE ucCmd_Buf[2];

    ucCmd_Buf[0]=0x02;
	if(UserCommonEepromIICRead(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	{
		return _FAIL;
	}
	
    ucCmd_Buf[0]=0x03;
	if(UserCommonEepromIICRead(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[2], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	{
		return _FAIL;
	}
	
    ucCmd_Buf[0]=0x04;
	if(UserCommonEepromIICRead(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[4], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	{
		return _FAIL;
	}

	// ADC Channel Data Registers (02h . 04h)
	// RED_LOW    02h  7:0 ADC channel 1 lower byte
	// RED_HIGH   02h 15:8 ADC channel 1 upper byte
	// GREEN_LOW  03h  7:0 ADC channel 2 lower byte
	// GREEN_HIGH 03h 15:8 ADC channel 2 upper byte
	// BLUE_LOW   04h  7:0 ADC channel 3 lower byte
	// BLUE_HIGH  04h 15:8 ADC channel 3 upper byte

	results->r= pData[1];
	results->g= pData[3];
	results->b= pData[5];

	results->r<<=8;
	results->g<<=8;
	results->b<<=8;

	results->r+= pData[0];
	results->g+= pData[2];
	results->b+= pData[4];

	//DebugMessageUart("M.r", results->r);
	//DebugMessageUart("M.g", results->g);
	//DebugMessageUart("M.b", results->b);
	
    return _SUCCESS;
}


// 5=32ms 6=64ms 7=128ms 8=256ms 9=512ms 10=1024ms 11=2048ms
#define MTCSCDCAF_TIME_START	 7
/*
BYTE MTCSCDCAF_GetRGB(void)
{
	DWORD largestData;
	SENSOR_DATA results;
    BYTE usTimeOutCnt = 100;

	if(1)
	{		
		// Waiting for measurement time complete, then detecting READY_PIN
		// MTCS_Measure wait for ready go high
	
		while(PCB_MTCS_READY_PIN_DETECT() == 0)
		{                      
			usTimeOutCnt--;

			ScalerTimerDelayXms(1);
		  
			if(usTimeOutCnt == 0x00)
			{
			    ScalerTimerActiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END);
			}
		}

		// First MTCS_Measure result
		if(g_workPara.b4MTCS_CREG1_TIME == MTCSCDCAF_TIME_START)
		{
			if(MTCSCDCAF_ReadAdcResults(&results) == 0)     // Get 128ms
			{
				DebugMessageUart("MTCS Measure Err0", 0);
			}

			largestData = getLargestElement((WORD*)&results.r);

			// 512ms sampling does not exceed 65535*0.8
			if((largestData*4) < 52428)     
			{
				
			    BYTE ucCount;

				// Get the minimum DIV value. That is, the frequency division closest to 52428
				for(ucCount = 8; ucCount > 0; ucCount--)
				{
					if((largestData*4)*MTCS_BaseDiv2X(ucCount) < 52428)
					{   
						DebugMessageUart("break Div:", ucCount);
						break;
					}
				}

				// Set the default sampling time to 512ms=128*4, adjust the DIV first.
				g_workPara.b4MTCS_CREG1_TIME = (MTCSCDCAF_TIME_START + 2);      // Set 512ms

				// Multiply by the maximum, that is, without dividing the frequency, it will not exceed the maximum 80%, increasing the sampling time.
				if(ucCount == 8)
				{
					g_workPara.b3MTCS_CREG2_DIV = 0;
					g_workPara.b1MTCS_CREG2_ENDIV = 0;
					
					// Up to 2048ms, ie x4 based on 512
					if((largestData*4)*256*4 < 52428) // largestData <13
					{   
						g_workPara.b4MTCS_CREG1_TIME = (MTCSCDCAF_TIME_START + 4);    // Set 2048ms
						multi = 4;
					}
					else if((largestData*4)*256*2 < 52428) // largestData <26
					{   
						g_workPara.b4MTCS_CREG1_TIME = (MTCSCDCAF_TIME_START + 3);    // Set 1024ms
						multi = 2;
					}
				}
				else // Simply adjusting the parameters of the DIV will suffice.
				{
					// The final divided register value, 0 starts with 2 divided, 1->4....
					g_workPara.b1MTCS_CREG2_ENDIV = 1;
					g_workPara.b3MTCS_CREG2_DIV = 7-ucCount;
				}
				
				// Second MTCS_Measure Init
				MTCSCDCAF_Init();
				MTCSCDCAF_Measure();
				
				// MTCS_Measure wait for ready go high(PCB_MTCS_READY_PIN_DETECT() == 1)
			    ScalerTimerReactiveTimerEvent((1<<g_workPara.b4MTCS_CREG1_TIME), _USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END);
			}
			else  // Too bright: If the maximum value exceeds 65535*0.8, reduce the sampling time and re-measure.
			{
				results.r = results.g = results.b = 0x0;
				DebugMessageUart("Sensor Overflow", 0);
				return _FAIL;
			}
		}
		else  
		{   
			// Second MTCS_Measure result
			if(MTCSCDCAF_ReadAdcResults(&results) == 0)  // Get 512ms or 1024ms or 2048ms
			{
				DebugMessageUart("MTCS Measure Err1", 0);
				results.r = results.g = results.b = 0x0;
				return _FAIL;
			}
		}
	}

	return _SUCCESS;
}
*/
#endif

	
BYTE VEML3328_Init(void)
{
    BYTE ucCmd_Buf[2];

	// Command code = 0x00 
	//   SD1          bit15:   Shutdown setting  SD1 = 0 power on    SD1 = 1 shutdown(default)
	//   SD_ALS only  bit14:   0   = power on all channels(default)  1   = power on G,C,and IR(R,B shutdown)
	//   DG           bit13-12:  00 = x1(default)  01 = x2          10 = x4   11 = reserved
	//   GAIN         bit11-10:  11 = x1/2         00 = x1(default) 01 = x2   10 = x4
	//   SENS         bit6:      0 = high sensitivity(default)  1 = low sensitivity(1/3)
	//   IT           bit5-4:    Integration time setting 00 = 50ms(default)  01 = 100ms  10 = 200ms 11 = 400ms
	//   AF           bit3:      Auto/active force mode   0 = auto mode(default)  1 = active force mode
	//   TRIG         bit2:      Trigger s single measurement when in active mode, This bit resets to 0 automatically 
	//                           when the measurement cycle is complete. 0 = no trigger(default) 1 = trigger one measurement cycle
	//   SD0          bit0:      Shutdown setting  SD0 = 0 power on  SD0 = 1 shutdown(default)

    // GAIN_1X  DG=1x GAIN=1/2 IT=200 or 100 or 50  MSB:0000 1100=0x0C   LSB:0010 0000=0x20 or LSB:0001 0000=0x10 or LSB:0000 0000=0x00
    // GAIN_4X  DG=2x GAIN=1   IT=200 or 100 or 50  MSB:0001 0000=0x10   LSB:0010 0000=0x20 or LSB:0001 0000=0x10 or LSB:0000 0000=0x00
    // GAIN_16X DG=4x GAIN=2   IT=200 or 100 or 50  MSB:0010 0100=0x24   LSB:0010 0000=0x20 or LSB:0001 0000=0x10 or LSB:0000 0000=0x00
    // GAIN_64X DG=4x GAIN=4   IT=400 or 200 or 100 MSB:0010 1000=0x28   LSB:0011 0000=0x30 or LSB:0010 0000=0x20 or LSB:0001 0000=0x10 

    // first
    // 1x1/2  x2   = 1   DG=1x GAIN=1/2 IT=100  MSB:0000 1100=0x0C   LSB:0001 0000=0x10
    // 2x1    x2   = 4   DG=1x GAIN=1   IT=100  MSB:0000 1100=0x10   LSB:0001 0000=0x10
    // 4x2    x2   = 16  DG=4x GAIN=2   IT=100  MSB:0010 0100=0x24   LSB:0001 0000=0x10
    // 4x4    x4   = 64  DG=4x GAIN=4   IT=200  MSB:0010 1000=0x28   LSB:0010 0000=0x20

    // =1/2
    // 1x1/2  x1   = 1   DG=1x GAIN=1/2 IT=50   MSB:0000 1100=0x0C   LSB:0000 0000=0x00
    // 2x1    x1   = 4   DG=1x GAIN=1   IT=50   MSB:0000 1100=0x10   LSB:0000 0000=0x00
    // 4x2    x1   = 16  DG=4x GAIN=2   IT=50   MSB:0010 0100=0x24   LSB:0000 0000=0x00
    // 4x4    x2   = 64  DG=4x GAIN=4   IT=100  MSB:0010 1000=0x28   LSB:0001 0000=0x10

    // =first
    // 1x1/2  x2   = 1   DG=1x GAIN=1/2 IT=100  MSB:0000 1100=0x0C   LSB:0011 0000=0x10
    // 1x1/2  x8   = 4   DG=1x GAIN=1/2 IT=400  MSB:0000 1100=0x0C   LSB:0011 0000=0x30
    // 2x1    x8   = 16  DG=2x GAIN=1   IT=400  MSB:0001 0000=0x10   LSB:0011 0000=0x30
    // 4x2    x8   = 64  DG=4x GAIN=2   IT=400  MSB:0010 0100=0x24   LSB:0011 0000=0x30

    // =1/2
    // 1x1/2  x1   = 1   DG=1x GAIN=1/2 IT=50   MSB:0000 1100=0x0C   LSB:0000 0000=0x00
    // 1x1/2  x4   = 4   DG=1x GAIN=1/2 IT=200  MSB:0000 1100=0x0C   LSB:0010 0000=0x20
    // 1x1    x8   = 16  DG=1x GAIN=1   IT=400  MSB:0000 0000=0x00   LSB:0011 0000=0x30
    // 2x2    x8   = 64  DG=2x GAIN=2   IT=400  MSB:0001 0100=0x14   LSB:0011 0000=0x30

    // TCS3430:703cd/m2  VEML3328:713cd/m2
    // Registers (Write:0x00 16Bit)
    ucCmd_Buf[0]=(0x30|0x0C);   // bit7-0     
    ucCmd_Buf[1]=0x14;   // bit15-8    
    // !!!must sync init
	FSensor_Gain = GAIN_64X;
	
    if(UserCommonEepromIICWrite(_FRONT_SENSOR_VEML3328_IIC_ADDR, 0x00, 1, 2, &ucCmd_Buf[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    {
		//DebugMessageUart("VEML3328 Init Fail", 0x20);
        return _FAIL;
    }
    
	return _SUCCESS;
}

void FSensor_init(void)
{
	BYTE ucCmd_Buf[2];

#if 0
    // Check TMTCSCDCAF start
	MTCSCDCAF_InitPara();
	if(MTCSCDCAF_Init() == _SUCCESS)
	{
    	g_bFrontSensorInitState = _DEVICE_ID_MTCSCDCAF; 
	}
    else 
#endif
    if(VEML3328_Init() == _SUCCESS)
	{
    	g_bFrontSensorInitState = _DEVICE_ID_VEML3328; 
    }
	else
	{
#if 1	
        // Check TCSTCS3414 or TCS3430 start
        
    	// TCS3414 ID Register (04h)
    	// Bit7:4  0000:TCS3404  0001:TCS3414  Bit3:0 Revision number identification
    	ucCmd_Buf[0]=CMD_VALUE|0x04;
        
    	if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        {
            g_bFrontSensorInitState = _FAIL;
        }
        
        if((pData[0] == 0x11)||((pData[0]&0xF0) == 0x10))
        {
            g_bFrontSensorInitState = _DEVICE_ID_TCS3414;
        }
        else
        {
        	// TCS3430 REVID Register (91h)
        	// Bit7:3 Reserve 01000 Bit2:0  001 
            ucCmd_Buf[0]=0x91;  
            
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                g_bFrontSensorInitState = _FAIL;
            }

        	// TCS3430 ID Register (92h)
        	// Bit7:2  110111  Bit1:0  00 
            ucCmd_Buf[0]=0x92; 
            
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &pData[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                g_bFrontSensorInitState = _FAIL;
            }

            if((pData[0] == 0x41)&&(pData[1] == 0xDC))
            {
                g_bFrontSensorInitState = _DEVICE_ID_TCS3430;
            }
        }
        // Check TCSTCS3414 or TCS3430 end

        if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
        {
            // Integration time = 0001:100 ms  0010:400 ms
        	FSensor_SetTiming(0x02); 
            FSensor_SetGain(GAIN_64X);
        }
        else if(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)
        {
            // Integration time = (uctime+1)*2.78ms  0x8F:400ms
            FSensor_SetTiming(0x8F);   
            FSensor_SetGain(GAIN_64X);
        }
#endif        
	}
}

void StartGetFSensorData(void)
{
	BYTE ucCmd_Buf[2];	

	if(g_bFrontSensorInitState == _FAIL)
    {
		FSensor_init();
    }

    //DebugMessageUart("FSensor:", g_bFrontSensorInitState);
#if 1    
	if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
	{
		// Control Register (00h)
		// Bit[1] ADC enable. Bit[0] Power on.
		ucCmd_Buf[0]=CMD_VALUE|TRANS_BYTE_PROTOC|CMD_SS_CONTROL;
		ucCmd_Buf[1]=0x03;  
       
	    if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	    {
	        //return _FAIL;
	    }
	}
    else if(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)
    {
		// ENABLE Register (00h)
		// Bit3: WEN Bit1: ALS Bit0: PON
        ucCmd_Buf[0]=0x80;
    	ucCmd_Buf[1]=0x03;
      
        if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
        {
	        //return _FAIL;
        }
    }
#endif    
#if 0
	else if(g_bFrontSensorInitState == _DEVICE_ID_MTCSCDCAF)
	{
	    // Waiting time is completed for command execution: 
	    // Write:6e 51 83 c2 03 00(120ms) Write:6e 51 82 c2 00 (1P:180ms 2P:220~380ms) Read:6e 51 82 c2 00 01
        // Total Time: 320ms = (120+180 + Data time)
        
		if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END) == _TRUE)
		{
			// MTCS_Measure:last measurement not completed
		}
		else
		{
			// Minimum sampling, maximum crossover, trial read value
			multi = 1;
			g_workPara.b4MTCS_CREG1_TIME = MTCSCDCAF_TIME_START;  // 128ms
			g_workPara.b3MTCS_CREG2_DIV = 7;   // div 256
			g_workPara.b1MTCS_CREG2_ENDIV = 1;
			MTCSCDCAF_Init();
			MTCSCDCAF_Measure();

			// MTCS_Measure wait for ready go high(PCB_MTCS_READY_PIN_DETECT() == 1)
		    ScalerTimerReactiveTimerEvent(/*SEC*/(1<<g_workPara.b4MTCS_CREG1_TIME), _USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END);
		}
	}
#endif
    /*else */if(g_bFrontSensorInitState == _DEVICE_ID_VEML3328)
    {
        FSensor_SetGain(FSensor_Gain);
    }
    		//DebugMessageUart("FSensor_Gain:", FSensor_Gain);
    
//OsdDispOsdMessage(_OSD_DISP_DICOM_RESULT);
//OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 14), g_bFrontSensorInitState, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));
}

void FinishedGetFSensorData(MatrixElem *pMatrixElemData) 
{
	SDWORD rValue,gValue,bValue;   
	SENSOR_DATA sensor_data;
	BYTE ucCmd_Buf[2];	
    
	if((g_bFrontSensorInitState == _DEVICE_ID_TCS3414)||(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)||(g_bFrontSensorInitState == _DEVICE_ID_VEML3328))
	{
    	if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
	    {
    		// Control Register (00h)
    		// Bit[1] ADC enable. Bit[0] Power on.
    		ucCmd_Buf[0]=CMD_VALUE|TRANS_BYTE_PROTOC|CMD_SS_CONTROL;
    		ucCmd_Buf[1]=0x01;
           
    	    if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }

    		// ADC Channel Data Registers (10h . 17h)
    		// GREEN_LOW  10h 7:0 ADC channel 1 lower byte
    		// GREEN_HIGH 11h 7:0 ADC channel 1 upper byte
    		// RED_LOW    12h 7:0 ADC channel 2 lower byte
    		// RED_HIGH   13h 7:0 ADC channel 2 upper byte
    		// BLUE_LOW   14h 7:0 ADC channel 3 lower byte
    		// BLUE_HIGH  15h 7:0 ADC channel 3 upper byte
    		ucCmd_Buf[0]=CMD_VALUE|TRANS_BLOCK_PROTOL|CMD_SS_DATA1LOW;
          
    	    if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 6, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }

    		sensor_data.g= pData[1];
    		sensor_data.r= pData[3];
    		sensor_data.b= pData[5];

    		sensor_data.g<<=8;
    		sensor_data.r<<=8;
    		sensor_data.b<<=8;

    		sensor_data.g+= pData[0];
    		sensor_data.r+= pData[2];
    		sensor_data.b+= pData[4];

	    }
        else if(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)
        {
    		// ENABLE Register (00h)
    		// Bit3: WEN Bit1: ALS Bit0: PON
        	ucCmd_Buf[0]=0x80;
        	ucCmd_Buf[1]=0x01;
        
            if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
            {
                //return _FAIL;
            }

            // CFG1 Register (90h) Bit3: AMUX
            // CFG2 Register (9Fh) Bit4: HGAIN 128X, if this bit is set and AGAIN in the CFG1 register is set to 11
            
    		// ADC Channel Data Registers (94h . 99h)
    		// CH0DATAL  94h 7:0 Contains Z data
    		// CH0DATAH  95h 7:0 Contains Z data
    		// CH1DATAL  96h 7:0 Contains Y data
    		// CH1DATAH  97h 7:0 Contains Y data
    		// CH2DATAL  98h 7:0 Contains IR1 data
    		// CH2DATAH  99h 7:0 Contains IR1 data
    		// CH3DATAL  9Ah 7:0 Contains X data AMUX=0 Contains IR2 data AMUX=1
    		// CH3DATAH  9Bh 7:0 Contains X data AMUX=0 Contains IR2 data AMUX=1

            // Contains Z data
            ucCmd_Buf[0]=0x94;  
            
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                //return _FAIL;
            }

        	sensor_data.g= pData[1];
        	sensor_data.g<<=8;
        	sensor_data.g+= pData[0];

            // Contains Y data
            ucCmd_Buf[0]=0x96;  
           
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                //return _FAIL;
            }

        	sensor_data.r= pData[1];
        	sensor_data.r<<=8;
        	sensor_data.r+= pData[0];

            // Contains X data
            ucCmd_Buf[0]=0x9A;  
         
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                //return _FAIL;
            }

        	sensor_data.b= pData[1];
        	sensor_data.b<<=8;
        	sensor_data.b+= pData[0];
        }
    	else if(g_bFrontSensorInitState == _DEVICE_ID_VEML3328)
    	{
        	// Command code = 0x04 
        	// Low  bit 7:0  C_LSB -> High bit 7:0  C_MSB
        	// Command code = 0x05 
        	// Low  bit 7:0  R_LSB -> High bit 7:0  R_MSB
        	// Command code = 0x06 
        	// Low  bit 7:0  G_LSB -> High bit 7:0  G_MSB
        	// Command code = 0x07 
        	// Low  bit 7:0  B_LSB -> High bit 7:0  B_MSB
        	// Command code = 0x08 
        	// Low  bit 7:0 IR_LSB -> High bit 7:0 IR_MSB
        	// Command code = 0x0C 
        	// Low  bit 7:0 ID_L   -> High bit 7:0 Reserved

            ucCmd_Buf[0]=0x05;
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_VEML3328_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        	{
        		//return _FAIL;
        	}

            ucCmd_Buf[0]=0x06;
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_VEML3328_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[2], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        	{
        		//return _FAIL;
        	}
           
            ucCmd_Buf[0]=0x07;
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_VEML3328_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[4], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        	{
        		//return _FAIL;
        	}

    		sensor_data.r= pData[1];
    		sensor_data.g= pData[3];
    		sensor_data.b= pData[5];

    		sensor_data.r<<=8;
    		sensor_data.g<<=8;
    		sensor_data.b<<=8;

    		sensor_data.r+= pData[0];
    		sensor_data.g+= pData[2];
    		sensor_data.b+= pData[4];
    	}
        //--------------------------------------------
        
		//if((sensor_data.r == 0xffff)||(sensor_data.g == 0xffff)||(sensor_data.b == 0xffff))
		{
    		/*DebugMessageUart(" r:", sensor_data.r);
    		DebugMessageUart(" g:", sensor_data.g);
    		DebugMessageUart(" b:", sensor_data.b);*/
		}
        
		if(((sensor_data.r==0xffff)||(sensor_data.g==0xffff)
			||(sensor_data.b==0xffff))&&(FSensor_Gain > GAIN_1X)) // >= 65535
		{
                FSensor_Gain--;
                FSensor_SetGain(FSensor_Gain);
                //DebugMessageUart("-Gain:", FSensor_Gain);
				 				
				// inform the software of PC side that the sensor has changed the gain. need read again.
				pMatrixElemData->Matrix_elem_X = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Y = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Z = 0xFFFFFFFF;
		}
		else if((sensor_data.r<=(0xffff/4)) && (sensor_data.g<=(0xffff/4))
				&& (sensor_data.b<=(0xffff/4)) && (FSensor_Gain < GAIN_64X)) // <= 16383
		{
                FSensor_Gain++;
                FSensor_SetGain(FSensor_Gain);
                //DebugMessageUart("+Gain:", FSensor_Gain);
				 
				// inform the software of PC side that the sensor has changed the gain. need read again.
				pMatrixElemData->Matrix_elem_X = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Y = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Z = 0xFFFFFFFF;
		}
		else
		{
            if(FSensor_Gain == GAIN_64X)
            {
                multi = 1;
            }
            else if(FSensor_Gain == GAIN_16X)
            {
                multi = 4;
            }
            else if(FSensor_Gain == GAIN_4X)
            {
                multi = 16;
            }
            else if(FSensor_Gain == GAIN_1X)
            {
                multi = 64;
            }

			rValue = (SDWORD)multi*sensor_data.r;
			gValue = (SDWORD)multi*sensor_data.g;
			bValue = (SDWORD)multi*sensor_data.b;
            
            {
        		/*DebugMessageUart(" multi:", multi);
        		DebugMessageUart(" rV:", rValue);
        		DebugMessageUart(" gV:", gValue);
        		DebugMessageUart(" bV:", bValue);*/
    		}

			pMatrixElemData->Matrix_elem_X=MatrixPara_sensorData.Matrix_Para_r1*rValue+
				MatrixPara_sensorData.Matrix_Para_g1*gValue+
				MatrixPara_sensorData.Matrix_Para_b1*bValue;
			
			pMatrixElemData->Matrix_elem_Y=MatrixPara_sensorData.Matrix_Para_r2*rValue+
				MatrixPara_sensorData.Matrix_Para_g2*gValue+
				MatrixPara_sensorData.Matrix_Para_b2*bValue;
			
			pMatrixElemData->Matrix_elem_Z=MatrixPara_sensorData.Matrix_Para_r3*rValue+
				MatrixPara_sensorData.Matrix_Para_g3*gValue+
				MatrixPara_sensorData.Matrix_Para_b3*bValue;
        		/*DebugMessageUart(" Matrix_elem_X:", pMatrixElemData->Matrix_elem_X);
        		DebugMessageUart(" Matrix_elem_Y:", pMatrixElemData->Matrix_elem_Y);
        		DebugMessageUart(" Matrix_elem_Z:", pMatrixElemData->Matrix_elem_Z);*/
            
		}
	}
#if 0
	else if(g_bFrontSensorInitState == _DEVICE_ID_MTCSCDCAF)
	{
		// MTCS sensor measurement completed?
		if(PCB_MTCS_READY_PIN_DETECT() == 0)
		{
			// inform the software of PC side that the MTCS sensor measurement result is not completed. need read again.
			pMatrixElemData->Matrix_elem_X = 0xFFFFFFFF;
			pMatrixElemData->Matrix_elem_Y = 0xFFFFFFFF;
			pMatrixElemData->Matrix_elem_Z = 0xFFFFFFFF;

		    // Waiting time is completed for command execution: 
		    // Write:6e 51 83 c2 03 01(133ms) Read:6F 6e 8e c2 03 FF FF FF FF FF FF FF FF FF FF FF FF (15ms)
		    // Write:6e 51 83 c2 03 00(120ms) Write:6e 51 82 c2 00 (180ms) Read:6e 51 82 c2 00 01

			// Make sure that MTCSCDCAF_Init and MTCSCDCAF_Measure are not executed when reading again.
			// Reset MTCS_Measure Waiting time: Must > 180ms = (133+15 + data time)ms
		    //if(ScalerTimerGetEventRemainTime(_USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END) < SEC(0.3))
	    	{
			    ScalerTimerReactiveTimerEvent(SEC(0.3), _USER_TIMER_EVENT_FSENSOR_MTCSCDCAF_MEASUREMENT_END);
	    	}
		}
		else
		{
			if(MTCSCDCAF_ReadAdcResults(&sensor_data) == 0)
			{
	           sensor_data.r = sensor_data.g = sensor_data.b = 0;
			}

			if(g_workPara.b1MTCS_CREG2_ENDIV == 1)
			{
				rValue = (DWORD)(sensor_data.r)*MTCS_BaseDiv2X(g_workPara.b3MTCS_CREG2_DIV+1);
				gValue = (DWORD)(sensor_data.g)*MTCS_BaseDiv2X(g_workPara.b3MTCS_CREG2_DIV+1);
				bValue = (DWORD)(sensor_data.b)*MTCS_BaseDiv2X(g_workPara.b3MTCS_CREG2_DIV+1);
			}
			else
			{
				rValue = sensor_data.r;
				gValue = sensor_data.g;
				bValue = sensor_data.b;
			}
			
			rValue = rValue / multi;
			gValue = gValue / multi;
			bValue = bValue / multi;

            // Overflow Patch
			rValue = rValue / 8;
			gValue = gValue / 8;
			bValue = bValue / 8;

			pMatrixElemData->Matrix_elem_X = MatrixPara_sensorData.Matrix_Para_r1*rValue+
				MatrixPara_sensorData.Matrix_Para_g1*gValue+
				MatrixPara_sensorData.Matrix_Para_b1*bValue;
			
			pMatrixElemData->Matrix_elem_Y = MatrixPara_sensorData.Matrix_Para_r2*rValue+
				MatrixPara_sensorData.Matrix_Para_g2*gValue+
				MatrixPara_sensorData.Matrix_Para_b2*bValue;
			
			pMatrixElemData->Matrix_elem_Z = MatrixPara_sensorData.Matrix_Para_r3*rValue+
				MatrixPara_sensorData.Matrix_Para_g3*gValue+
				MatrixPara_sensorData.Matrix_Para_b3*bValue;
		}
	}
#endif
}
/*
void FinishedGetFSensorData_Thr(MatrixElem *pMatrixElemData) 
{
	SDWORD rValue,gValue,bValue;   
	SENSOR_DATA sensor_data;
	BYTE ucCmd_Buf[2];	
	static BYTE ucFSensorMultiple = 0;
	static SDWORD usFAverageXValue[3] = {0};
	static SDWORD usFAverageYValue[3] = {0};
	static SDWORD usFAverageZValue[3] = {0};    
	if((g_bFrontSensorInitState == _DEVICE_ID_TCS3414)||(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)||(g_bFrontSensorInitState == _DEVICE_ID_VEML3328))
	{
    	if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
	    {
    		// Control Register (00h)
    		// Bit[1] ADC enable. Bit[0] Power on.
    		ucCmd_Buf[0]=CMD_VALUE|TRANS_BYTE_PROTOC|CMD_SS_CONTROL;
    		ucCmd_Buf[1]=0x01;
           
    	    if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }

    		// ADC Channel Data Registers (10h . 17h)
    		// GREEN_LOW  10h 7:0 ADC channel 1 lower byte
    		// GREEN_HIGH 11h 7:0 ADC channel 1 upper byte
    		// RED_LOW    12h 7:0 ADC channel 2 lower byte
    		// RED_HIGH   13h 7:0 ADC channel 2 upper byte
    		// BLUE_LOW   14h 7:0 ADC channel 3 lower byte
    		// BLUE_HIGH  15h 7:0 ADC channel 3 upper byte
    		ucCmd_Buf[0]=CMD_VALUE|TRANS_BLOCK_PROTOL|CMD_SS_DATA1LOW;
          
    	    if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 6, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
    	    {
    	        //return _FAIL;
    	    }

    		sensor_data.g= pData[1];
    		sensor_data.r= pData[3];
    		sensor_data.b= pData[5];

    		sensor_data.g<<=8;
    		sensor_data.r<<=8;
    		sensor_data.b<<=8;

    		sensor_data.g+= pData[0];
    		sensor_data.r+= pData[2];
    		sensor_data.b+= pData[4];

	    }
        else if(g_bFrontSensorInitState == _DEVICE_ID_TCS3430)
        {
    		// ENABLE Register (00h)
    		// Bit3: WEN Bit1: ALS Bit0: PON
        	ucCmd_Buf[0]=0x80;
        	ucCmd_Buf[1]=0x01;
        
            if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 1, &ucCmd_Buf[1], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
            {
                //return _FAIL;
            }

            // CFG1 Register (90h) Bit3: AMUX
            // CFG2 Register (9Fh) Bit4: HGAIN 128X, if this bit is set and AGAIN in the CFG1 register is set to 11
            
    		// ADC Channel Data Registers (94h . 99h)
    		// CH0DATAL  94h 7:0 Contains Z data
    		// CH0DATAH  95h 7:0 Contains Z data
    		// CH1DATAL  96h 7:0 Contains Y data
    		// CH1DATAH  97h 7:0 Contains Y data
    		// CH2DATAL  98h 7:0 Contains IR1 data
    		// CH2DATAH  99h 7:0 Contains IR1 data
    		// CH3DATAL  9Ah 7:0 Contains X data AMUX=0 Contains IR2 data AMUX=1
    		// CH3DATAH  9Bh 7:0 Contains X data AMUX=0 Contains IR2 data AMUX=1

            // Contains Z data
            ucCmd_Buf[0]=0x94;  
            
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                //return _FAIL;
            }

        	sensor_data.g= pData[1];
        	sensor_data.g<<=8;
        	sensor_data.g+= pData[0];

            // Contains Y data
            ucCmd_Buf[0]=0x96;  
           
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                //return _FAIL;
            }

        	sensor_data.r= pData[1];
        	sensor_data.r<<=8;
        	sensor_data.r+= pData[0];

            // Contains X data
            ucCmd_Buf[0]=0x9A;  
         
            if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
            {
                //return _FAIL;
            }

        	sensor_data.b= pData[1];
        	sensor_data.b<<=8;
        	sensor_data.b+= pData[0];
        }
    	else if(g_bFrontSensorInitState == _DEVICE_ID_VEML3328)
    	{
        	// Command code = 0x04 
        	// Low  bit 7:0  C_LSB -> High bit 7:0  C_MSB
        	// Command code = 0x05 
        	// Low  bit 7:0  R_LSB -> High bit 7:0  R_MSB
        	// Command code = 0x06 
        	// Low  bit 7:0  G_LSB -> High bit 7:0  G_MSB
        	// Command code = 0x07 
        	// Low  bit 7:0  B_LSB -> High bit 7:0  B_MSB
        	// Command code = 0x08 
        	// Low  bit 7:0 IR_LSB -> High bit 7:0 IR_MSB
        	// Command code = 0x0C 
        	// Low  bit 7:0 ID_L   -> High bit 7:0 Reserved

            ucCmd_Buf[0]=0x05;
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_VEML3328_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[0], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        	{
        		//return _FAIL;
        	}

            ucCmd_Buf[0]=0x06;
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_VEML3328_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[2], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        	{
        		//return _FAIL;
        	}
           
            ucCmd_Buf[0]=0x07;
        	if(UserCommonEepromIICRead(_FRONT_SENSOR_VEML3328_IIC_ADDR, ucCmd_Buf[0], 1, 2, &pData[4], _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
        	{
        		//return _FAIL;
        	}

    		sensor_data.r= pData[1];
    		sensor_data.g= pData[3];
    		sensor_data.b= pData[5];

    		sensor_data.r<<=8;
    		sensor_data.g<<=8;
    		sensor_data.b<<=8;

    		sensor_data.r+= pData[0];
    		sensor_data.g+= pData[2];
    		sensor_data.b+= pData[4];
    	}
        //--------------------------------------------
        
		//if((sensor_data.r == 0xffff)||(sensor_data.g == 0xffff)||(sensor_data.b == 0xffff))
		{
		}
        
		if(((sensor_data.r==0xffff)||(sensor_data.g==0xffff)
			||(sensor_data.b==0xffff))&&(FSensor_Gain > GAIN_1X)) // >= 65535
		{
                FSensor_Gain--;
                FSensor_SetGain(FSensor_Gain);
                DebugMessageUart("-Gain:", FSensor_Gain);
				 				
				// inform the software of PC side that the sensor has changed the gain. need read again.
				pMatrixElemData->Matrix_elem_X = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Y = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Z = 0xFFFFFFFF;
		}
		else if((sensor_data.r<=(0xffff/4)) && (sensor_data.g<=(0xffff/4))
				&& (sensor_data.b<=(0xffff/4)) && (FSensor_Gain < GAIN_64X)) // <= 16383
		{
                FSensor_Gain++;
                FSensor_SetGain(FSensor_Gain);
                DebugMessageUart("+Gain:", FSensor_Gain);
				 
				// inform the software of PC side that the sensor has changed the gain. need read again.
				pMatrixElemData->Matrix_elem_X = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Y = 0xFFFFFFFF;
				pMatrixElemData->Matrix_elem_Z = 0xFFFFFFFF;
		}
		else
		{
            if(FSensor_Gain == GAIN_64X)
            {
                multi = 1;
            }
            else if(FSensor_Gain == GAIN_16X)
            {
                multi = 4;
            }
            else if(FSensor_Gain == GAIN_4X)
            {
                multi = 16;
            }
            else if(FSensor_Gain == GAIN_1X)
            {
                multi = 64;
            }

			rValue = (SDWORD)multi*sensor_data.r;
			gValue = (SDWORD)multi*sensor_data.g;
			bValue = (SDWORD)multi*sensor_data.b;
            
            {
    		}

			pMatrixElemData->Matrix_elem_X=MatrixPara_sensorData.Matrix_Para_r1*rValue+
				MatrixPara_sensorData.Matrix_Para_g1*gValue+
				MatrixPara_sensorData.Matrix_Para_b1*bValue;
			
			pMatrixElemData->Matrix_elem_Y=MatrixPara_sensorData.Matrix_Para_r2*rValue+
				MatrixPara_sensorData.Matrix_Para_g2*gValue+
				MatrixPara_sensorData.Matrix_Para_b2*bValue;
			
			pMatrixElemData->Matrix_elem_Z=MatrixPara_sensorData.Matrix_Para_r3*rValue+
				MatrixPara_sensorData.Matrix_Para_g3*gValue+
				MatrixPara_sensorData.Matrix_Para_b3*bValue;

    usFAverageXValue[ucFSensorMultiple] = (pMatrixElemData->Matrix_elem_X);
    usFAverageYValue[ucFSensorMultiple] = (pMatrixElemData->Matrix_elem_Y);
    usFAverageZValue[ucFSensorMultiple] = (pMatrixElemData->Matrix_elem_Z);

    //DebugMessageUart("Get Sensor:", usCurSensorValue);
    
    ucFSensorMultiple++;
    if((ucFSensorMultiple == 1)||(ucFSensorMultiple == 2))
    {
		pMatrixElemData->Matrix_elem_X = 0xFFFFFFFF;
		pMatrixElemData->Matrix_elem_Y = 0xFFFFFFFF;
		pMatrixElemData->Matrix_elem_Z = 0xFFFFFFFF;
	    //DebugMessageUart("Sensor Mid:", usCurSensorValue);
    }
    else if(ucFSensorMultiple >= 3)
    {
        ucFSensorMultiple = 0;
        pMatrixElemData->Matrix_elem_X =  MIDOF(usFAverageXValue[0],usFAverageXValue[1],usFAverageXValue[2]);
        pMatrixElemData->Matrix_elem_Y =  MIDOF(usFAverageYValue[0],usFAverageYValue[1],usFAverageYValue[2]);;
        pMatrixElemData->Matrix_elem_Z =  MIDOF(usFAverageZValue[0],usFAverageZValue[1],usFAverageZValue[2]);;            
	    //DebugMessageUart("Sensor Mid:", usCurSensorValue);
    }
   
		}
	}
}
*/
#if(_ARM_MCU_CALIBRATION_SUPPORT)
void RTDDdcciSendDataToARMMCU(void)
{
	WORD usTempBuf[2];

    switch(GET_DDCCI_MCU_TYPE())
    {
        case _CMD_DDC_QA_EVENT:
			{
	            g_pucDdcciTxBuf[0] = 0x6E;
	            g_pucDdcciTxBuf[1] = (0x80|3);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _CMD_DDC_QA_EVENT;	//CMD
	            g_pucDdcciTxBuf[4] = _TRUE; // bQA_Flag;
	            g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
            break;

        case _CMD_DDC_UPDATE_FPGA:
			{
                // Old 12M MCU:0xFF Update All 0x00 is Calib 0x01 is Off ...[Lut ID]
                // Rew 12M MCU:0xFF Update All other is Calib, At the same time, improve UI progress and add exit UI function[CMD:44 1 0 0]
                // It is different from 6-8M MCU
	            g_pucDdcciTxBuf[0] = 0x6E;
	            g_pucDdcciTxBuf[1] = (0x80|3);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _CMD_DDC_UPDATE_FPGA;	
	            g_pucDdcciTxBuf[4] = 0x00; 
	            g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
            break;

        case _CMD_DDC_MCU_VERSION:
			{
	            g_pucDdcciTxBuf[0] = 0x6E;
	            g_pucDdcciTxBuf[1] = (0x80|3);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _CMD_DDC_MCU_VERSION;	
	            g_pucDdcciTxBuf[4] = _TRUE; 
	            g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
            break;
            
       	case _CMD_LUM_DIFF:
			{
	            g_pucDdcciTxBuf[0] = 0x6E;
	            g_pucDdcciTxBuf[1] = (0x80|11);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _CMD_LUM_DIFF;	//CMD
                DebugMessageUart("_LUM_DIFF:", GET_OSD_LUT_USER_TYPE());

                RTDNVRamLoadUserLutData();
	            g_pucDdcciTxBuf[4] = GET_OSD_LUT_USER_TYPE();//GAMMA or DICOM
	            
	            usTempBuf[0] = GET_OSD_LUT_USER_L_MAX()*10;
	            usTempBuf[1] = GET_OSD_LUT_USER_L_MIN()*100;
	            g_pucDdcciTxBuf[5] = (BYTE)((usTempBuf[0] & 0xff00)>>8);         
	            g_pucDdcciTxBuf[6] = (BYTE)((usTempBuf[0] & 0x00ff));
	            g_pucDdcciTxBuf[7] = (BYTE)((usTempBuf[1] & 0xff00)>>8);            
	            g_pucDdcciTxBuf[8] = (BYTE)((usTempBuf[1] & 0x00ff));
	            
	            if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
            	{
		            g_pucDdcciTxBuf[9] = GET_OSD_LUT_USER_LAMB(); 
            	}
	            else
            	{
		            g_pucDdcciTxBuf[9] = GET_OSD_LUT_USER_VALUE(); 
            	}

	            usTempBuf[0] = GET_COLOR_TEMP_TYPE();
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    SET_COLOR_TEMP_TYPE( _CT_USER);
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                g_pucDdcciTxBuf[10] = GET_COLOR_TEMP_TYPE_USER_R();
                g_pucDdcciTxBuf[11] = GET_COLOR_TEMP_TYPE_USER_G();
                g_pucDdcciTxBuf[12] = GET_COLOR_TEMP_TYPE_USER_B();
                if(GET_COLOR_TEMP_TYPE() != usTempBuf[0])
                {
                    SET_COLOR_TEMP_TYPE( usTempBuf[0]);
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                
	            g_pucDdcciTxBuf[13] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
       		break;

       	case _CMD_USER_LUT_CAL:
			{                
	            g_pucDdcciTxBuf[0] = 0x6E;
	        	g_pucDdcciTxBuf[1] = (0x80|8);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _CMD_USER_LUT_CAL;	//CMD
                DebugMessageUart("_LUT_CAL:", GET_OSD_LUT_USER_TYPE());

                RTDNVRamLoadUserLutData();
	        	g_pucDdcciTxBuf[4] = GET_OSD_LUT_USER_TYPE(); //GAMMA or DICOM
				
	        	usTempBuf[0] = GET_OSD_LUT_USER_L_MAX()*10;
	        	usTempBuf[1] = GET_OSD_LUT_USER_L_MIN()*100;
	        	g_pucDdcciTxBuf[5] = (BYTE)((usTempBuf[0] & 0xff00)>>8);         
	        	g_pucDdcciTxBuf[6] = (BYTE)((usTempBuf[0] & 0x00ff));
	        	g_pucDdcciTxBuf[7] = (BYTE)((usTempBuf[1] & 0xff00)>>8);            
	        	g_pucDdcciTxBuf[8] = (BYTE)((usTempBuf[1] & 0x00ff));
	        
	        	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        		{
	        		g_pucDdcciTxBuf[9] = GET_OSD_LUT_USER_LAMB(); 
        		}
	        	else
        		{
	        		g_pucDdcciTxBuf[9] = GET_OSD_LUT_USER_VALUE(); 
        		}
	            g_pucDdcciTxBuf[10] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
       		break;

       	case _CMD_MAX_MIN_CMD:
			{
				DWORD ulLuxMax,ulLuxMin;

				g_pucDdcciTxBuf[0] = 0x6E;
				g_pucDdcciTxBuf[1] = (0x80|18);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _CMD_MAX_MIN_CMD;	//CMD

				RTDNVRamLoadPanelLuxRangeData();
			    memcpy(&ulLuxMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax,4);
				memcpy(&ulLuxMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[4] = (BYTE)(((DWORD)ulLuxMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[5] = (BYTE)(((DWORD)ulLuxMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[6] = (BYTE)(((DWORD)ulLuxMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[7] = (BYTE)(((DWORD)ulLuxMax & 0x000000ff));
			    g_pucDdcciTxBuf[8] = (BYTE)(((DWORD)ulLuxMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[9] = (BYTE)(((DWORD)ulLuxMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[10] = (BYTE)(((DWORD)ulLuxMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[11] = (BYTE)(((DWORD)ulLuxMin & 0x000000ff));

			    memcpy(&ulLuxMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax,4);
			    memcpy(&ulLuxMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[12] = (BYTE)(((DWORD)ulLuxMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[13] = (BYTE)(((DWORD)ulLuxMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[14] = (BYTE)(((DWORD)ulLuxMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[15] = (BYTE)(((DWORD)ulLuxMax & 0x000000ff));
			    g_pucDdcciTxBuf[16] = (BYTE)(((DWORD)ulLuxMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[17] = (BYTE)(((DWORD)ulLuxMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[18] = (BYTE)(((DWORD)ulLuxMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[19] = (BYTE)(((DWORD)ulLuxMin & 0x000000ff));

	            g_pucDdcciTxBuf[20] = UserCommonDdcciCalCheckSum(); // checksum

       		}
       		break;
			
    }
    
	UserAdjustDdcciSetARMMcuCommand(_CMD_NONE);
}
#endif //#if(_ARM_MCU_CALIBRATION_SUPPORT)


//--------------------------------------------------
// Description  : Set DDC-DI Command&data for beacon factory color sensor adjust function
// Input Value  : null
// Output Value : cmd Status..etc
//#define _DDCCI_SOURCE                               0
//#define _DDCCI_LENGTH                               1
//#define _DDCCI_COMMAND                              2       
//        0  1  2
//BEA: 6e 51 8* c2 
//DBI: 6e 51 8* c3 
//--------------------------------------------------
void RTDDdcciFactoryColorSensorProcess(void) 
{
	BYTE CMDCode;
	BYTE *CMDPara;
	BYTE Cmd_Reply = 0x00;
    WORD usTemp = 0;

	CMDCode = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]; // Index:3
	CMDPara = &g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE];  // Index:4


#if 1//(_ENABLE_BACKLIGHT_SENSOR||_ENABLE_AMBIENTLIGHT_SENSOR)
    if(CMDCode != _DDCCI_SENSOR_CALIB_GET_ORDER_STATUS)
    {
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER); 
    	ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
    }
#endif
//Add By KW
#if 0
	if(CMDCode ==_DDCCI_SENSOR_CALIB_GET_FSENSOR_DATA)
	{
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);
		ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_AMBI_SENSOR_HANDLER);  
    	ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);
	}
#endif

	if((CMDCode == _DDCCI_SENSOR_CALIB_SET_WIN_POS) ||
       (CMDCode == _DDCCI_SENSOR_CALIB_SET_BACKLIGHT)||
       (CMDCode == _DDCCI_SENSOR_CALIB_SET_LUT_DATA) ||
       (CMDCode == _DDCCI_SENSOR_CALIB_SET_LUT_ENTRY_VALUE)||
       (CMDCode == _DDCCI_SENSOR_CALIB_SET_CURRENT_GAMMA)||
       (CMDCode == _DDCCI_SENSOR_CALIB_SET_COLOR_TEMP))
	{
#if(_PCM_FUNCTION == _ON)
        // Skip Gamma if PCM != native
        if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
        {
			SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
			OsdFuncColorPcmAdjust();
        }
#endif

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT == _ON)
//#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
    	if(IsGammaOptionHybridGamma(GET_OSD_GAMMA()) == _ON)
    	{
            SET_OSD_GAMMA( _DEFAULT_GAMMA);
#if(_GAMMA_FUNCTION == _ON)
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

            if(GET_OSD_GAMMA() != _GAMMA_OFF)
            {
                UserAdjustGamma(GET_OSD_GAMMA());
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
            }
#endif
    	}
//#endif
#endif
	}

	if((CMDCode != _DDCCI_SENSOR_CALIB_SET_LUT_DATA)&&(CMDCode != _DDCCI_SENSOR_CALIB_GET_LUT_DATA))
	{
        DebugMessageUart("CMD:", CMDCode);
    }
    
	switch(CMDCode)	
	{
        case _DDCCI_SENSOR_CALIB_GET_ORDER_STATUS:  //ok
			{
                //(_BEACON_CALIBRATION_COMMAND_STATUS_EXINT_SUPPORT == _OFF)
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(0x03)); // Length 0x80|(0xC2,CMD,data)

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_ORDER_STATUS;	//CMD
				g_pucDdcciTxBuf[4] = E_OrderStatus; // data
                
            	g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum(); // checksum

                ScalerMcuDdcciSendData( g_pucDdcciTxBuf);
        	   // DebugMessageUart("E_0:", E_OrderStatus);

                // Clear flag: PC only reads once
                E_OrderStatus = 0;

				//( E_OrderStatus :1, previous order is write order,
				//0, previous order is read order or GET_ORDER_STATUS order)
			}
            break;

		case _DDCCI_SENSOR_CALIB_GET_STATUS: //ok
			{
                //Write:  0x6e 0x51 0x82 0xC2 0x02 CheckSum:0x7C  
                //Read:   0x6e 0x84 0xC2 0x02 0x01 0x02 CheckSum:0x79  

				BYTE B_PowerState;

                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
					B_PowerState = 0x01;
				else
					B_PowerState = 0x00;
				
				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(0x04)); // Length(0xC2,cmd,data) 
				
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_STATUS; //CMD
        	    DebugMessageUart("B_PowerState:", B_PowerState);
                
				g_pucDdcciTxBuf[4] = B_PowerState;			            // 0-sleep, 1-active power_sync 
				                                                         /*bit[1:0] power state 0 = power off, 1 = power on*/
                                                                         /*bit[2] sync state 0 = no sync 1 = sync*/	
				g_pucDdcciTxBuf[5] = GET_COLOR_TEMP_TYPE();

            	g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum();      // checksum
			}
			break;	

		case _DDCCI_SENSOR_CALIB_GET_FSENSOR_DATA:  //ok
			{
                //BYTE btContorl; 
                //0x00 for MCU read data from front sensor data 
				//0x01 for PC read the MCU data which for the front sensor
				//0x20 for the back sensor to begin test the brightness luminance 
				//0x21 for the back sensor to read the data						  
				//ע�⣬ÿһ��0x01֮ǰ������һ��0x00���ƣ�����ʱ400ms���ϡ�
				BYTE btControl = CMDPara[0];
	
				if(btControl == 0x00) // MCU read front sensor data
				{                    
					ReadMatrixParaData();
					StartGetFSensorData();
				}
				else if(btControl == 0x01)// PC read front sensor data from MCU buffer
				{
					Cmd_Reply = 1;

					FinishedGetFSensorData(&MatrixElem_FSensorData);
                    //FinishedGetFSensorData_Thr(&MatrixElem_FSensorData);
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(0x0E)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FSENSOR_DATA;	//CMD

                    // Matrix_elem_X
                    g_pucDdcciTxBuf[4] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_X); 		
					g_pucDdcciTxBuf[5] = (BYTE)((MatrixElem_FSensorData.Matrix_elem_X)>>8);			
					g_pucDdcciTxBuf[6] = (BYTE)((MatrixElem_FSensorData.Matrix_elem_X)>>16);		
					g_pucDdcciTxBuf[7] = (BYTE)((MatrixElem_FSensorData.Matrix_elem_X)>>24);	

                    // Matrix_elem_Y
					g_pucDdcciTxBuf[8] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Y); 		
					g_pucDdcciTxBuf[9] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Y>>8); 		
					g_pucDdcciTxBuf[10] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Y>>16);		
					g_pucDdcciTxBuf[11] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Y>>24);	
						
                    // Matrix_elem_Z
					g_pucDdcciTxBuf[12] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Z);	
					g_pucDdcciTxBuf[13] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Z>>8); 		
					g_pucDdcciTxBuf[14] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Z>>16);		
					g_pucDdcciTxBuf[15] = (BYTE)(MatrixElem_FSensorData.Matrix_elem_Z>>24);	

                	g_pucDdcciTxBuf[16] = UserCommonDdcciCalCheckSum(); // checksum
    		//DebugMessageUart(" g_pucDdcciTxBuf:", MatrixElem_FSensorData.Matrix_elem_Z);
				}
				else if(btControl == 0x20)// start backlight sensor Integration
				{
					InitBacklightSensorModule(); 
				}
				else if(btControl == 0x21)// read backlight sensor data
				{
					WORD W_SensorCh0,W_SensorCh1;
					W_SensorCh0 = ReadBacklightSensorValue(0); 
					W_SensorCh1 = ReadBacklightSensorValue(1); 
                    
					Cmd_Reply = 1;
					
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(0x0E)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FSENSOR_DATA; //CMD	

                    // Matrix_elem_X
                    g_pucDdcciTxBuf[4] = (BYTE)(W_SensorCh1&0xFF); 			
					g_pucDdcciTxBuf[5] = (BYTE)((W_SensorCh1>>8)&0xFF); 
					g_pucDdcciTxBuf[6] = 0x00; 			
					g_pucDdcciTxBuf[7] = 0x00; 		

                    // Matrix_elem_Y
					g_pucDdcciTxBuf[8] = (BYTE)(W_SensorCh0&0xFF); 		
					g_pucDdcciTxBuf[9] = (BYTE)((W_SensorCh0>>8)&0xFF); 		
					g_pucDdcciTxBuf[10] = 0x00; 			
					g_pucDdcciTxBuf[11] = 0x00; 		
						
                    // Matrix_elem_Z
					g_pucDdcciTxBuf[12] = 0x00; 		
					g_pucDdcciTxBuf[13] = 0x00; 			
					g_pucDdcciTxBuf[14] = 0x00; 
					g_pucDdcciTxBuf[15] = 0x00; 			
                    
                	g_pucDdcciTxBuf[16] = UserCommonDdcciCalCheckSum(); // checksum
				}		
				else if(btControl == 0x30) // MCU read front sensor data
				{
					DebugMessageUart("CMD 0x30 Send Data:",0xC2);
				#if 1	
					if(/*AmbiSensor_VEML6030_ReadLux()*/AmbiSensor_ReadLux() == _FAIL)    //AmbiSensor_ReadLux()
					{
						ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
						g_bAmbiSensorInitState = 0;
						DebugMessageUart("Read [Fail] Ambi !!!",0xFFFF);
						
					}
					else
					{
						DebugMessageUart("Read [Success] Ambi VEML6030! ==",usSensorLux);
					}
				#endif                 
				}
				else if(btControl == 0x31)// PC read front sensor data from MCU buffer
				{
					Cmd_Reply = 1;
					DebugMessageUart("CMD 0x31 Send Data:",0xC2);
					//DebugMessageUart("-Rest_Temp--",Rest_Temp);					
					//AmbiSensor_VEML6030_ReadLux();
                    //FinishedGetFSensorData_Thr(&MatrixElem_FSensorData);
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|0x04); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FSENSOR_DATA;	//CMD

					g_pucDdcciTxBuf[4] = (BYTE)(usSensorLux & 0xFF); 	//Low Byte of usSensorLux	
					g_pucDdcciTxBuf[5] = (BYTE)(usSensorLux >> 8);		//High Byte of usSensorLux

					g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
				}
			}
		    break;
		case _DDCCI_SENSOR_CALIB_WRITE_AMBI_AB_DATA:
			{
				DebugMessageUart("AB Value:----------",0);
				DebugMessageUart("CMDPara[0]: ",CMDPara[0]);
				DebugMessageUart("CMDPara[1]: ",CMDPara[1]);
				DebugMessageUart("CMDPara[2]: ",CMDPara[2]);
				DebugMessageUart("CMDPara[3]: ",CMDPara[3]);
				DebugMessageUart("CMDPara[4]: ",CMDPara[4]);
				DebugMessageUart("CMDPara[5]: ",CMDPara[5]);
				DebugMessageUart("CMDPara[6]: ",CMDPara[6]);
				DebugMessageUart("CMDPara[7]: ",CMDPara[7]);
				DebugMessageUart("CMDPara[8]: ",CMDPara[8]);
				#if 0
				g_stPanelAmbABData.usA_Data = (((SDWORD)CMDPara[0] << 24) | ((SDWORD)CMDPara[1] << 16) | ((SDWORD)CMDPara[2] << 8) | ((SDWORD)CMDPara[3] << 0));
				g_stPanelAmbABData.usB_Data = (((SDWORD)CMDPara[4] << 24) | ((SDWORD)CMDPara[5] << 16) | ((SDWORD)CMDPara[6] << 8) | ((SDWORD)CMDPara[7] << 0));
				#endif
				g_stPanelAmbABData.usA_Data = (((SDWORD)CMDPara[0] << 0) | ((SDWORD)CMDPara[1] << 8) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 24));
				g_stPanelAmbABData.usB_Data = (((SDWORD)CMDPara[4] << 0) | ((SDWORD)CMDPara[5] << 8) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 24));
				RTDNVRamSavePanelAmbABData();
			}
			break;
		case _DDCCI_SENSOR_CALIB_SET_AMBI_AB_DATA:  
			{
                WORD AMB;
                
				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(0x04)); // Length
				
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_SET_AMBI_AB_DATA; //CMD

				AMB = Lum_RealFiltered;		//AMB = Lum_RealFiltered*100 ???
				DebugMessageUart("AMB Value:----------",AMB);
				g_pucDdcciTxBuf[4] = (BYTE)(AMB&0xFF);
				g_pucDdcciTxBuf[5] = (BYTE)(AMB>>8);
                
            	g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
			}
		    break;

		case _DDCCI_SENSOR_CALIB_READ_AMBI_RELATIVE:
			{
				switch(CMDPara[0])
				{
					case 0x01:  //Show current Ambient Sensor(VEML6030) Coefficient
					{
						Cmd_Reply = 1;

						g_pucDdcciTxBuf[0] = 0x6E;	// Source
						g_pucDdcciTxBuf[1] = (0x80|(0x03+0x08)); // Length
						
						g_pucDdcciTxBuf[2] = 0xC2;	// Prefix 0xC2
						g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_READ_AMBI_RELATIVE;	//CMD

						g_pucDdcciTxBuf[4] = 0x01;	//Option code
						// Matrix_elem_X
						RTDNVRamLoadPanelAmbABData();
						#if 0
						//Coefficient A (High Byte in the Front)
						g_pucDdcciTxBuf[5] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0xFF000000)>>24); 	//High byte	of A
						g_pucDdcciTxBuf[6] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0x00FF0000)>>16);  //Low byte of A
						g_pucDdcciTxBuf[7] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0x0000FF00)>>8); 	//High byte	of A
						g_pucDdcciTxBuf[8] = (BYTE)((SWORD)(g_stPanelAmbABData.usA_Data) & 0x000000FF);  //Low byte of A						

						//Coefficient B (High Byte in the Front)
						g_pucDdcciTxBuf[9] =  (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0xFF000000)>>24);	//High byte	of B
						g_pucDdcciTxBuf[10] = (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0x00FF0000)>>16);	//High byte	of B 		
						g_pucDdcciTxBuf[11] = (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0x0000FF00)>>8);	//High byte	of B 														 		
						g_pucDdcciTxBuf[12] = (BYTE)((SWORD)(g_stPanelAmbABData.usB_Data) & 0x000000FF);	//Low byte of B
						#endif
						//Coefficient A	(Low Byte in the Front)
						g_pucDdcciTxBuf[5] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0x000000FF)>>0); 	//LOW byte	of A
						g_pucDdcciTxBuf[6] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0x0000FF00)>>8);  	//Low byte of A
						g_pucDdcciTxBuf[7] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0x00FF0000)>>16); 	//High byte	of A
						g_pucDdcciTxBuf[8] = (BYTE)(((SWORD)(g_stPanelAmbABData.usA_Data) & 0xFF000000)>>24); 	//High byte	of A				

						//Coefficient B (Low Byte in the Front)
						g_pucDdcciTxBuf[9] =  (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0x000000FF)>>0);	//Low byte	of B
						g_pucDdcciTxBuf[10] = (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0x0000FF00)>>8);	//Low byte	of B 		
						g_pucDdcciTxBuf[11] = (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0x00FF0000)>>16);	//High byte	of B 														 		
						g_pucDdcciTxBuf[12] = (BYTE)(((SWORD)(g_stPanelAmbABData.usB_Data) & 0xFF000000)>>24);	//High byte	of B 
						
						g_pucDdcciTxBuf[13] = UserCommonDdcciCalCheckSum(); // checksum

					}break;

					case 0x02:	//The flag that show the ALC state
					{
						Cmd_Reply = 1;

						g_pucDdcciTxBuf[0] = 0x6E;	// Source
						g_pucDdcciTxBuf[1] = (0x80|(0x03+0x01)); // Length
						
						g_pucDdcciTxBuf[2] = 0xC2;	// Prefix 0xC2
						g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_READ_AMBI_RELATIVE;	//CMD

						g_pucDdcciTxBuf[4] = 0x02;	//Option code

						g_pucDdcciTxBuf[5] = ALC_state;	//Current DICOM curve state						

						g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
					}break;

					case 0x03:	//The stable value that show the ALC state
					{
						Cmd_Reply = 1;

						g_pucDdcciTxBuf[0] = 0x6E;	// Source
						g_pucDdcciTxBuf[1] = (0x80|(0x03+0x02)); // Length
						
						g_pucDdcciTxBuf[2] = 0xC2;	// Prefix 0xC2
						g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_READ_AMBI_RELATIVE;	//CMD

						g_pucDdcciTxBuf[4] = 0x03;	//Option code

						g_pucDdcciTxBuf[5] = (BYTE)((Lum_RealUsing&0xFF00)>>8);	//High Byte <--> AMB Luminance					
						g_pucDdcciTxBuf[6] = (BYTE)((Lum_RealUsing&0x00FF)>>0);	//Low Byte <--> AMB Luminance

						g_pucDdcciTxBuf[7] = UserCommonDdcciCalCheckSum(); // checksum
					}break;

					case 0x04:	//The unstable value that show the ALC state
					{
						Cmd_Reply = 1;

						g_pucDdcciTxBuf[0] = 0x6E;	// Source
						g_pucDdcciTxBuf[1] = (0x80|(0x03+0x02)); // Length
						
						g_pucDdcciTxBuf[2] = 0xC2;	// Prefix 0xC2
						g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_READ_AMBI_RELATIVE;	//CMD

						g_pucDdcciTxBuf[4] = 0x04;	//Option code

						g_pucDdcciTxBuf[5] = (BYTE)((Lum_Real&0xFF00)>>8);	//High Byte <--> AMB Luminance					
						g_pucDdcciTxBuf[6] = (BYTE)((Lum_Real&0x00FF)>>0);	//Low Byte <--> AMB Luminance

						g_pucDdcciTxBuf[7] = UserCommonDdcciCalCheckSum(); // checksum
					}break;					
				}
			}
			break;

		 case _DDCCI_SENSOR_CALIB_SET_WIN_POS:  //ok
			 {
                //CW_NONE:         Write: 6E Rx[0]:0x51 0x83 0xC2 0x04 0x00 CheckSum:0x7A  
                //CW_FRONT_SENSOR: Write: 6E Rx[0]:0x51 0x83 0xC2 0x04 0x01 CheckSum:0x7B  

                //CW_BYPASS_PATCH_MODE: Write: 6E Rx[0]:0x51 0x84 0xC2 0x04 0x05 0x01 CheckSum:0x7B  

                //CW_LUT_PATCH_MODE: Write: 6E Rx[0]:0x51 0x84 0xC2 0x04 0x06 0x01 CheckSum:0x7A  

				//UserPrefUSBCaliOsdPosition = (BYTE)CMDPara[0];
 				//UserPrefUSBCalibrationMode = 1;

                //---------------------------------------------------------------------------------
				// The next command interval takes more than a few seconds, which is determined by the scaler chip platform
                // First:               Write:6e 51 84 C2 04 05 01 79(checksum) 
                // Second:   Delay100ms Write:6e 51 82 C2 00 7f(checksum) Delay50~60ms Read:6e 83 C2 00 01(CMD Completed within 200ms) [Delay 6s]
                // Second: or[Delay 6s] Write:6e 51 82 C2 00 7f(checksum) Delay50~60ms Read:6e 83 C2 00 01 Delay100~200ms
                // ....................
                // Third:               Write:6e 51 84 C2 04 05 02 7a(checksum) Delay100~200ms 
                //                      Write:6e 51 82 C2 00 7f(checksum) Delay50~60ms Read:6e 83 C2 00 01
                // ....................
                // Must execute exit:CW_NONE
                // Write:6e 51 83 C2 04 00 7a(checksum) [Delay 6s] 
                // Write:6e 51 82 C2 00 7f(checksum) Delay 50~60ms Read:6e 83 C2 00 01
                //---------------------------------------------------------------------------------

				if(CMDPara[0] != 0)
				{
	                UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, (BYTE)CMDPara[0]);
				}
DebugMessageUart("CMDPara[0]", CMDPara[0]);
				switch(CMDPara[0])//(UserPrefUSBCaliOsdPosition)
				{
					case 1: // CW_FRONT_SENSOR
					case 2: // CW_CENTER
        				OsdDispDisableOsd();
                    	ScalerTimerReactiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_COLOR_SENSOR_CALIBRATION_MODE);
						break;

 					case 3: // BOTH ->used to creat compare table
                    	ScalerTimerReactiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_COLOR_SENSOR_CALIBRATION_MODE);
						break;

 					case 4: // go to the work state.
 						//UserPrefUSBCalibrationMode = 1;
        				//OsdDispDisableOsd();
                    	//ScalerTimerReactiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_COLOR_SENSOR_CALIBRATION_MODE); 						
						break;

 					case 5: // CW_BYPASS_PATCH_MODE
						if(CMDPara[1] == 0x01)
						{
	                    	ScalerTimerReactiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_COLOR_SENSOR_CALIBRATION_MODE);
						}
						else if(CMDPara[1] == 0x02)
						{
							// Use Background Calibration
							OsdDispDisableOsd();
						    ScalerDDomainBackgroundEnable( _ENABLE);
					        ScalerDDomainBackgroundSetColor10bit(1023, 1023, 1023);
						    ScalerDDomainPatternGenEnable(_DISABLE);
						}
						break;

 					case 6: // CW_LUT_PATCH_MODE
						if(CMDPara[1] == 0x01)
						{

							if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
							{
					            if(_OSD_ASPECT_RATIO_FULL != GET_OSD_ASPECT_RATIO_TYPE())
								{
			 						//Backup AspectRatioType before calibration
									g_ucAspectRatioTypeBackup = GET_OSD_ASPECT_RATIO_TYPE();
								}
							}
							ScalerTimerReactiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_COLOR_SENSOR_CALIBRATION_MODE);
						}
						else if(CMDPara[1] == 0x02)
						{
							// Use Pattern Calibration
							OsdDispDisableOsd();
						    ScalerDDomainPatternGenEnable(_ENABLE);
					        ScalerDDomainPatternGenAdjustColor10bit(1023, 1023, 1023);
						    ScalerDDomainBackgroundEnable(_DISABLE);
						}
						break;

 					case 0: //  CW_NONE
					default:
 						//UserPrefUSBCalibrationMode = 0;
						//ExitUsbCalibration();

						if((UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 5)||(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 6))
						{
	                        // Close Pattern or Background Calibration
							ScalerDDomainBackgroundEnable( _ENABLE);
					        ScalerDDomainBackgroundSetColor10bit(0, 0, 0);
				            ScalerDDomainPatternGenEnable(_DISABLE);
					        ScalerDDomainPatternGenAdjustColor10bit(0, 0, 0);

							if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 6)
							{
								if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
								{
			                        // Restore the original AspectRatioType after calibration exits[MultiP]
				                    SET_OSD_ASPECT_RATIO_TYPE(g_ucAspectRatioTypeBackup);
									g_ucAspectRatioTypeBackup = 0;
								}
							}

					        if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) ||
					           (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
					    	{
						        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
					    	}
						}                            
						else
						{
						    // Close UI Calibration
							OsdDispDisableOsd();
						}
						
					    
#if((_ARM_MCU_CALIBRATION_SUPPORT)&&(_FPGA_COLOR_ADAPTIVE_SUPPORT))
                        // PC or MCU calibration
                        if(g_bPCAppCalibrationFlag == _TRUE)
                        {
                            // After the PC calibration is complete, need to notify the ARM MCU to update the FPGA Gamma calibration data [MCU DDCCI gets data]
                            g_bPCAppCalibrationFlag = _FALSE;
                            // waiting write:C2 04 00->write:C2 00->read:C2 00 01 complete
        		            ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_NOTIFY_MCU_UPDATE_FPGA);
                        }
#endif
						
                        UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _OFF);

                        // Check NSG to PS condition in display
						if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
	                    {
                            ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
	                    }
						break;
				}
			 }
			 break;

 		 case _DDCCI_SENSOR_CALIB_SET_WIN_RGB://ok
			{
				WORD bk_red, bk_grn, bk_blu;

                // Write: 6E Rx[0]:0x51 0x88 0xC2 0x05 0x00 0x01 0x00 0x01 0x00 0x08 CheckSum:0x78  
                // bk_red = 4 bk_grn = 4 bk_blu = 32
                
				// range:range: 0~16383, input -14bits, 0~1023, output -10bits, 
				//bk_red = (WORD)(((WORD)(CMDPara[1]<<8)+CMDPara[0])>> 4);
				//bk_grn = (WORD)(((WORD)(CMDPara[3]<<8)+CMDPara[2])>> 4);
				//bk_blu = (WORD)(((WORD)(CMDPara[5]<<8)+CMDPara[4])>> 4);

				// Use OSD
                // range:range: 0~16383(0x3FFF), input -14bits, 0~255, output -8bits, 
				//bk_red = (WORD)(((WORD)(CMDPara[1]<<8)+CMDPara[0])>> 6);
				//bk_grn = (WORD)(((WORD)(CMDPara[3]<<8)+CMDPara[2])>> 6);
				//bk_blu = (WORD)(((WORD)(CMDPara[5]<<8)+CMDPara[4])>> 6);

				// Use OSD Color Palette
                // range:range: 0~16383(0x3FFF), input -14bits, 0~63, output -6bits, 
				//bk_red = (WORD)(((WORD)(CMDPara[1]<<8)+CMDPara[0])>> 8);
				//bk_grn = (WORD)(((WORD)(CMDPara[3]<<8)+CMDPara[2])>> 8);
				//bk_blu = (WORD)(((WORD)(CMDPara[5]<<8)+CMDPara[4])>> 8);

				if((UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 1)||(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 2)||(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 3))
				{
					// Use OSD
	                // range:range: 0~16383(0x3FFF), input -14bits, 0~255, output -8bits, 
	                bk_red = (WORD)(((WORD)(CMDPara[1]<<8)+CMDPara[0])>> 6);
					bk_grn = (WORD)(((WORD)(CMDPara[3]<<8)+CMDPara[2])>> 6);
					bk_blu = (WORD)(((WORD)(CMDPara[5]<<8)+CMDPara[4])>> 6);
    				if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 1)
                    {
                        ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_0, bk_red, bk_grn, bk_blu);
                    }            
    				if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 2)
                    {
    	                ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_5, bk_red, bk_grn, bk_blu);
                    }                        
                    if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 3)
                    {
                        ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_0, bk_red, bk_grn, bk_blu);
    	                ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_5, bk_red, bk_grn, bk_blu);
                    }                        
				}
				else if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 5)
				{
					// Use Background
					// range:range: 0~16383(0x3FFF), input -14bits, 0~1023, output -10bits, 

					// Rx[0]:0x51 Rx[1]:0x88 Rx[2]:0xC2 Rx[3]:0x05 Rx[4]:0xF0 Rx[5]:0x3F Rx[6]:0xF0 Rx[7]:0x3F Rx[8]:0xF0 Rx[9]:0x3F Rx[10]CheckSum:0xBF  
	                // bk_red = 1023 bk_grn = 1023 bk_blu = 1023   0x3FF0->0x3FF

					bk_red = (WORD)(((WORD)(CMDPara[1]<<8)+CMDPara[0])>> 4);
					bk_grn = (WORD)(((WORD)(CMDPara[3]<<8)+CMDPara[2])>> 4);
					bk_blu = (WORD)(((WORD)(CMDPara[5]<<8)+CMDPara[4])>> 4);
					
			        ScalerDDomainBackgroundSetColor10bit(bk_red, bk_grn, bk_blu);
	 		 	}
				else if(UserCommonNVRamGetSystemData(_SENSOR_CALIBRATION_MODE) == 6)
				{
					// Use Pattern
					// range:range: 0~16383(0x3FFF), input -14bits, 0~1023, output -10bits, 
					bk_red = (WORD)(((WORD)(CMDPara[1]<<8)+CMDPara[0])>> 4);
					bk_grn = (WORD)(((WORD)(CMDPara[3]<<8)+CMDPara[2])>> 4);
					bk_blu = (WORD)(((WORD)(CMDPara[5]<<8)+CMDPara[4])>> 4);
					
			        ScalerDDomainPatternGenAdjustColor10bit(bk_red, bk_grn, bk_blu);
	 		 	}
			}
			break;

		case _DDCCI_SENSOR_CALIB_GET_AMBI_LUMI:  
			{
                //BYTE ambi_lux[2];
                
				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(0x04)); // Length
				
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_AMBI_LUMI; //CMD

                //ambi_lux[2]:[0] low byte [1] hight byte
                if(AmbiSensor_ReadLux() == _FAIL)
                {
            	    ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AMBI_SENSOR_ADC_START);   
            		g_bAmbiSensorInitState = 0;
                }
				g_pucDdcciTxBuf[4] = (BYTE)(usSensorLux&0xFF);
				g_pucDdcciTxBuf[5] = (BYTE)(usSensorLux>>8);
                
            	g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
			}
		    break;

		case _DDCCI_SENSOR_CALIB_SET_BACKLIGHT:  //0~255
            // Write: 0x6e 0x51 0x84 0xC2 0x07 L H CheckSum:0x  
			{
                // protocol version <5.0
                //BYTE backlight; /*0 (dark) - 255 (bright)*/ 

                // protocol version >=5.0
                //BYTE backlight[2]; /*0 (dark) - 255 or 4095 (bright)*/  L->H

                // first:  must execute this command[_DDCCI_SENSOR_CALIB_SET_CURRENT_GAMMA], 
                // second: then adjust the PWM to the target value[_DDCCI_SENSOR_CALIB_SET_BACKLIGHT], 
                // third:  then call the stored command[_DDCCI_SENSOR_CALIB_SAVE_BACKLIGHT], otherwise Gamma switch is required
                
                // protocol version >=5.0 and BeaconMonitorManager3.25
                if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
            	{
	                // Input 12Bit 0~4095  
					usTemp = (((WORD)CMDPara[1] << 8) | ((WORD)CMDPara[0]));
            	}
				else
				{
            	    // Input 8Bit 0~255  
					usTemp = CMDPara[0];		
				}
                
				if(GET_OSD_BACKLIGHT() != _INIT_BACKLIGHT)
				{
		            SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
                    UserAdjustBacklight(GET_OSD_BACKLIGHT());
				}
                
                UserAdjustBacklightDuty(usTemp);
			}
			break;
			
		case _DDCCI_SENSOR_CALIB_SAVE_BACKLIGHT: /* save backlight settings*/  
            // Write: 0x6e 0x51 0x85 0xC2 0x08 Lut_id L H CheckSum:0x  
			{				
				//BYTE lut_id;    /*the lut number*/

                // protocol version <5.0
				//BYTE backlight; /*0 (dark) - 255 (bright)*/

                // protocol version >=5.0
				//BYTE backlight[2]; /*0 (dark) - 255 or 4095 (bright)*/  L->H
				
				// Lut_id: CAL=0 OFF=1 Others- reserved

                BYTE lut_id = CMDPara[0];
                BYTE gamma_table,color_temp;
                BYTE gamma_table_backup,color_temp_backup;
                BYTE ucResult = _SUCCESS;
                    
                // protocol version >=5.0 and BeaconMonitorManager3.25
				// Get PWM
                if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
            	{
	                // Input 12Bit 0~4095  L->H
					usTemp = (((WORD)CMDPara[2] << 8) | ((WORD)CMDPara[1]));
            	}
				else
				{
            	    // Input 8Bit 0~255  
					usTemp = CMDPara[1];	
				}	

				//check range must
				if(usTemp <= _BACKLIGHT_MIN)
					usTemp = _BACKLIGHT_MIN;
				if(usTemp >= _BACKLIGHT_MAX)
					usTemp = _BACKLIGHT_MAX;
                
                // Get Last Gamma Index & ColorTemp Index
                gamma_table_backup = GET_OSD_GAMMA();
                color_temp_backup = GET_COLOR_TEMP_TYPE();
     
                // Lut_id to UI Gamma Index
                gamma_table = ReadLut_ID_GammaIndex(lut_id);
            	DebugMessageUart("Save Gamma:", gamma_table);

                // Lut_id to UI CT Index
                color_temp = ReadLut_ID_ColorTempIndex(lut_id);
                SET_COLOR_TEMP_TYPE( color_temp);
            
                if(gamma_table <= _GAMMA_AMOUNT)
    			{
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
            	    // CAL -> PC Calibration
            		if(gamma_table == _GAMMA_24)
            		{
						_SET_USER_BACKLIGHT_CALIB(usTemp);
            		}
            	    // Native
            		else if(gamma_table == _GAMMA_OFF) 
            		{
                        // Set Gamma Native Flag
                        // Write: 0x6e 0x51 0x85 0xC2 0x08 0xE1 L H CheckSum:0x  
                        if(lut_id == 0xE1)
                        {
    						UserCommonNVRamSetSystemData(_GAMMA_NATIVE_SET_MODE,_OFF);                        
#if 1// _CT_SRGB is Native
                            SET_COLOR_TEMP_TYPE(color_temp_backup);
#endif
                            ucResult = _FAIL;
                        }
                        else
                        {
    						UserCommonNVRamSetSystemData(_GAMMA_NATIVE_SET_MODE,_ON);                        
#if 1// _CT_SRGB is Native
                            // !!! _CT_SRGB is Native == set _OUTGAMMA_OFF
                            SET_COLOR_TEMP_TYPE(_CT_SRGB);
                            color_temp_backup = GET_COLOR_TEMP_TYPE();
                            gamma_table = gamma_table_backup;
#endif
    						_SET_USER_NATIVE_BACKLIGHT(usTemp);
                        }
						UserCommonNVRamSaveSystemData();
					}
                    // is Gamma2.2
                    else if(gamma_table == _GAMMA_18)
        			{    
        				if(GET_OSD_BACKLIGHT() != _INIT_BACKLIGHT)
        				{
        		            SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
                            UserAdjustBacklight(GET_OSD_BACKLIGHT());
        				}
                        
                        _SET_DUT_BACKLIGHT_CENTER(usTemp);
          				g_bBacklightSensorValueRestoreStatus = _TRUE;
        			}            			            			            			
    			    // is  _DICOM
                    else if(gamma_table == _GAMMA_20)
        			{    
                        _SET_USER_DICOM_BACKLIGHT(usTemp);
        			}
                    else
                    {
                        ucResult = _FAIL;
                    }

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
            	    // CAL -> PC Calibration
            		if(gamma_table == _GAMMA_CALIB)
            		{
						_SET_USER_BACKLIGHT_CALIB(usTemp);
            		}
            	    // Native
            		else if(gamma_table == _GAMMA_OFF) 
            		{
                        // Set Gamma Native Flag
                        // Write: 0x6e 0x51 0x85 0xC2 0x08 0xE1 L H CheckSum:0x  
                        if(lut_id == 0xE1)
                        {
    						UserCommonNVRamSetSystemData(_GAMMA_NATIVE_SET_MODE,_OFF);                        
#if 1// _CT_SRGB is Native
                            SET_COLOR_TEMP_TYPE(color_temp_backup);
#endif
                            ucResult = _FAIL;
                        }
                        else
                        {
    						UserCommonNVRamSetSystemData(_GAMMA_NATIVE_SET_MODE,_ON);                        
#if 1// _CT_SRGB is Native
                            // !!! _CT_SRGB is Native == set _OUTGAMMA_OFF
                            SET_COLOR_TEMP_TYPE(_CT_SRGB);
                            color_temp_backup = GET_COLOR_TEMP_TYPE();
                            gamma_table = gamma_table_backup;
#endif
    						_SET_USER_NATIVE_BACKLIGHT(usTemp);
                        }
						UserCommonNVRamSaveSystemData();
					}
                    // is Gamma2.0
                    else if(gamma_table == _GAMMA_18)
        			{    
        				if(GET_OSD_BACKLIGHT() != _INIT_BACKLIGHT)
        				{
        		            SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
                            UserAdjustBacklight(GET_OSD_BACKLIGHT());
        				}
                        
                        _SET_DUT_BACKLIGHT_CENTER(usTemp);
          				g_bBacklightSensorValueRestoreStatus = _TRUE;
        			}            			            			            			
    			    // is  _DICOM
                    else if(gamma_table == _GAMMA_26)
        			{    
                        _SET_USER_DICOM_BACKLIGHT(usTemp);
        			}
                    else
                    {
                        ucResult = _FAIL;
                    }

#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
            	    // CAL -> PC Calibration
            		if(gamma_table == _GAMMA_CALIB)
            		{
						_SET_USER_BACKLIGHT_CALIB(usTemp);
            		}
            	    // Native
            		else if(gamma_table == _GAMMA_OFF) 
            		{
                        // Set Gamma Native Flag
                        // Write: 0x6e 0x51 0x85 0xC2 0x08 0xE1 L H CheckSum:0x  
                        if(lut_id == 0xE1)
                        {
    						UserCommonNVRamSetSystemData(_GAMMA_NATIVE_SET_MODE,_OFF);                        
#if 1// _CT_SRGB is Native
                            SET_COLOR_TEMP_TYPE(color_temp_backup);
#endif
                            ucResult = _FAIL;
                        }
                        else
                        {
    						UserCommonNVRamSetSystemData(_GAMMA_NATIVE_SET_MODE,_ON);                        
#if 1// _CT_SRGB is Native
                            // !!! _CT_SRGB is Native == set _OUTGAMMA_OFF
                            SET_COLOR_TEMP_TYPE(_CT_SRGB);
                            color_temp_backup = GET_COLOR_TEMP_TYPE();
                            gamma_table = gamma_table_backup;
#endif
    						_SET_USER_NATIVE_BACKLIGHT(usTemp);
                        }
						UserCommonNVRamSaveSystemData();
					}
                    // is Gamma2.2
                    else if(gamma_table == _GAMMA_18)
        			{    
        				if(GET_OSD_BACKLIGHT() != _INIT_BACKLIGHT)
        				{
        		            SET_OSD_BACKLIGHT(_INIT_BACKLIGHT);
                            UserAdjustBacklight(GET_OSD_BACKLIGHT());
        				}
                        
                        _SET_DUT_BACKLIGHT_CENTER(usTemp);
          				g_bBacklightSensorValueRestoreStatus = _TRUE;
        			}            			            			            			
    			    // is  Multi _DICOM
                    else if(gamma_table == _GAMMA_DICOM200)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_200(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM250)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_250(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM300)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_300(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM350)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_350(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM400)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_400(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM450)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_450(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM500)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_500(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM550)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_550(usTemp);
        			}
                    else if(gamma_table == _GAMMA_DICOM600)
        			{    
                        _SET_USER_DICOM_BACKLIGHT_600(usTemp);
        			}
                    else
                    {
                        ucResult = _FAIL;
                    }
#else
#warning "!!!Please Check Gamma define"

#endif  // End of #if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                                        
                    // Set Gamma Index & CT Index
                    if(gamma_table <= _GAMMA_AMOUNT)
    				{  
                        if((ucResult == _SUCCESS)&&((gamma_table_backup != gamma_table)||(color_temp_backup != color_temp)))
            			{
                            SET_OSD_GAMMA( gamma_table);
#if(_GAMMA_FUNCTION == _ON)
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                            if(GET_OSD_GAMMA() != _GAMMA_OFF)
                            {
                                UserAdjustGamma(GET_OSD_GAMMA());
                                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                                UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                            }
#endif
            			}
                        
                        if(ucResult == _SUCCESS)
                        {
            				UserAdjustBacklightDuty(usTemp);

                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                         #if 1//(_ENABLE_BACKLIGHT_SENSOR)
                        	ScalerTimerReactiveTimerEvent(SEC(0.02), _USER_TIMER_EVENT_OSD_SAVE_USER2_DATA);
                         #endif
                        }
    				}

                }
			}
	        break;

		case _DDCCI_SENSOR_CALIB_SET_LUT_DATA:  //ok
			{
				//BYTE btDataLen;  /*bytes of real btData length */
				//BYTE lut_id;     /*the lut id*/ //user gamma,always is 0
				//BYTE offset[2];
				//BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX]; 

				//RxBuf[] Size=65 ->51 8* c2 09 btDataLen lut_id offset[2] btData[] CheckSum
				//BeaconMonitorManager3.12 change 0x00:data_read_max=56->55[TRANSPORT_EVERY_DATA_LEN_MAX]

			    // for Beacon Sensor Tool protocol V4.1:CAL-OFF-1.8-2.0-2.2
				// Lut_id: CAL=0 OFF=1 Others- reserved
            	// For X-Rite & Embedded MCU Redefine:Lut_id [Bit7~Bit5]is the colortemp Index [Bit4~Bit0] is the GammaTab Index
                
				BYTE ucDataLen = CMDPara[0];
				BYTE lut_id = CMDPara[1];
				WORD usDataIndex = (WORD)((WORD)(CMDPara[2])+(WORD)(CMDPara[3]<<8));
				BYTE *GammaData = (BYTE *)&CMDPara[4];

   				BYTE ucLutIndex,ucCTIndex,ucEarsePage;
   				BYTE ucLutIndex_backup,ucCTIndex_backup;

                //must Earse Flash Page
                if(usDataIndex == _FALSE)
                {
                    // [2020-04-10 14:53:22.923]# RECV ASCII>
            	    DebugMessageUart("Earse ID=", lut_id);

                    // Get Last Gamma Index & ColorTemp Index
                    ucLutIndex_backup = GET_OSD_GAMMA();
                    ucCTIndex_backup = GET_COLOR_TEMP_TYPE();

                    ucLutIndex = ReadLut_ID_GammaIndex(lut_id);
                    ucCTIndex = ReadLut_ID_ColorTempIndex(lut_id);

            	    DebugMessageUart("Lut=", ucLutIndex);
            	    DebugMessageUart("CT=", ucCTIndex);
                    
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                    // CAL -> PC Calibration
                	if(ucLutIndex == _GAMMA_24) 
                	{
                        // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
                    	// Embedded write two Curve needs attention: write lut_id = 0x00 is _CT_6500, write lut_id = 0x20 is _CT_9300
                        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 

                    	for(ucEarsePage = 0; ucEarsePage < 2; ucEarsePage++)
                    	{
                        	// Page 0~1
    	                    UserCommonFlashErasePage(_BEACON_GAMMA_CALIBRATION_FLASH_BANK, ucEarsePage);
                    	}
                	}
                    // Off
                	else if(ucLutIndex == _GAMMA_OFF) 
                	{

                	}
                    // Gamma 2.2 & DICOM
			        else if(ucLutIndex == _GAMMA_18)  
                	{
                        // Beacon Sensor Tool & X-Rite Calibration 
    				    if(ucCTIndex == _CT_9300) 
    			    	{
                        	for(ucEarsePage = 0; ucEarsePage < 16; ucEarsePage++)
                        	{
                            	// Page 0~15
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_PARTITION0_FLASH_BANK, ucEarsePage);
                        	}
    			    	}

                        // Beacon Sensor Tool & X-Rite Calibration 
    				    if(ucCTIndex == _CT_6500) 
    			    	{
                            // Beacon Sensor Tool & X-Rite Calibration 
                        	for(ucEarsePage = 0; ucEarsePage < 16; ucEarsePage++)
                        	{
                            	// Page 0~15
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_PARTITION1_FLASH_BANK, ucEarsePage);
                        	}
    			    	}
                	} 
                    // User -> MCU Calibration
			        else if(ucLutIndex == _GAMMA_22)  
                	{
                        // Embedded MCU Calibration: must first _CT_9300 
                     	//DebugMessageUart("LUT_TYPE:", GET_OSD_LUT_USER_TYPE());
                        if((GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)&&(ucCTIndex == _CT_9300))
                        {
                        	for(ucEarsePage = 2; ucEarsePage < 6; ucEarsePage++)
                        	{
                            	// Page 2~5
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_CALIBRATION_FLASH_BANK, ucEarsePage);
                        	}
                        }
                        else if((GET_OSD_LUT_USER_TYPE() == _LUT_USER_GAMMA)&&(ucCTIndex == _CT_9300))
                        {
                        	for(ucEarsePage = 6; ucEarsePage < 10; ucEarsePage++)
                        	{
                            	// Page 6~9
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_CALIBRATION_FLASH_BANK, ucEarsePage);
                        	}
                        }

                	}

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
                    // CAL -> PC Calibration
                	if(ucLutIndex == _GAMMA_CALIB) 
                	{
                        // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
                    	// Embedded write two Curve needs attention: write lut_id = 0x00 is _CT_6500, write lut_id = 0x20 is _CT_9300
                        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 

                    	for(ucEarsePage = 0; ucEarsePage < 2; ucEarsePage++)
                    	{
                        	// Page 0~1
    	                    UserCommonFlashErasePage(_BEACON_GAMMA_CALIBRATION_FLASH_BANK, ucEarsePage);
                    	}
                	}
                    // Off
                	else if(ucLutIndex == _GAMMA_OFF) 
                	{

                	}
                    // Gamma 2.2 & DICOM
			        else if(ucLutIndex == _GAMMA_18)  
                	{
                        // Beacon Sensor Tool & X-Rite Calibration 
    				    if(ucCTIndex == _CT_9300) 
    			    	{
                        	for(ucEarsePage = 0; ucEarsePage < 16; ucEarsePage++)
                        	{
                            	// Page 0~15
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_PARTITION0_FLASH_BANK, ucEarsePage);
                        	}
    			    	}

                        // Beacon Sensor Tool & X-Rite Calibration 
    				    if(ucCTIndex == _CT_6500) 
    			    	{
                            // Beacon Sensor Tool & X-Rite Calibration 
                        	for(ucEarsePage = 0; ucEarsePage < 16; ucEarsePage++)
                        	{
                            	// Page 0~15
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_PARTITION1_FLASH_BANK, ucEarsePage);
                        	}
    			    	}
                	} 

#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                    // CAL -> PC Calibration
                	if(ucLutIndex == _GAMMA_CALIB) 
                	{
                        // BeaconMonitorManager Only write one Curve: always write lut_id = 0x00 
                    	// Embedded write two Curve needs attention: write lut_id = 0x00 is _CT_6500, write lut_id = 0x20 is _CT_9300
                        // BeaconMonitorManager QA read data is by Get Lut_id[Bit7~5] 

                    	for(ucEarsePage = 0; ucEarsePage < 2; ucEarsePage++)
                    	{
                        	// Page 0~1
    	                    UserCommonFlashErasePage(_BEACON_GAMMA_CALIBRATION_FLASH_BANK, ucEarsePage);
                    	}
                	}
                    // Off
                	else if(ucLutIndex == _GAMMA_OFF) 
                	{

                	}
                    // Gamma 2.2 & Multi Dicom
			        else if(ucLutIndex == _GAMMA_18)  
                	{
                        // Beacon Sensor Tool & X-Rite Calibration 
    				    if(ucCTIndex == _CT_9300) 
    			    	{
                        	for(ucEarsePage = 0; ucEarsePage < 16; ucEarsePage++)
                        	{
                            	// Page 0~15
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_PARTITION0_FLASH_BANK, ucEarsePage);
                        	}
    			    	}

                        // Beacon Sensor Tool & X-Rite Calibration 
    				    if(ucCTIndex == _CT_6500) 
    			    	{
                            // Beacon Sensor Tool & X-Rite Calibration 
                        	for(ucEarsePage = 0; ucEarsePage < 16; ucEarsePage++)
                        	{
                            	// Page 0~15
        	                    UserCommonFlashErasePage(_BEACON_GAMMA_PARTITION1_FLASH_BANK, ucEarsePage);
                        	}
    			    	}
                	}                 	
#else
#warning "!!!Please Check Gamma define"

#endif  // End of #if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)

    		    }

				WriteLutData_Factory(usDataIndex,ucDataLen,GammaData,lut_id);  
                
				if(usDataIndex + ucDataLen >= _BEACON_OGC_GAMMA_TABLE_SIZE )
				{
                    // Must be regained: Get Current
                    ucLutIndex = ReadLut_ID_GammaIndex(lut_id);
                    ucCTIndex = ReadLut_ID_ColorTempIndex(lut_id);
                    if(IsMonoChromeorColorPanel() == M_MONO)		 
                    {
                    ucCTIndex = _CT_9300;
                    }

                    if((ucLutIndex <= _GAMMA_AMOUNT)&&((ucLutIndex_backup != ucLutIndex)||(ucCTIndex_backup != ucCTIndex)))
    				{
#if(_GAMMA_FUNCTION == _ON)
                        SET_COLOR_TEMP_TYPE( ucCTIndex);
                        SET_OSD_GAMMA( ucLutIndex/*_GAMMA_CALIB*/);
#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
#endif
        		    }

#if((_ARM_MCU_CALIBRATION_SUPPORT)&&(_FPGA_COLOR_ADAPTIVE_SUPPORT))
                    // PC calibration update
                    if(ucLutIndex == _GAMMA_24)
                    {
                        g_bPCAppCalibrationFlag = _TRUE;
                    }
#endif
                
            	    DebugMessageUart("Rx End=", ucLutIndex);
                    // [2020-04-10 14:53:45.562]# RECV ASCII> 23s
				}
			}
		    break;

		case _DDCCI_SENSOR_CALIB_GET_LUT_DATA: /* read LUT data */ 
			{   
				BYTE ucDataLen = CMDPara[0];
				BYTE lut_id = CMDPara[1];
				WORD usDataIndex = (WORD)((WORD)(CMDPara[2])+(WORD)(CMDPara[3]<<8));

				Cmd_Reply = 1;

                if(usDataIndex == 0)
                {
            	    //DebugMessageUart("Tx ID=", lut_id);
                    // PC ->[2020-04-10 14:53:47.833]# RECV ASCII>
                    // MCU->[2020-04-10 14:54:07.650]# RECV ASCII>
                }
				
				if(usDataIndex + ucDataLen <= _BEACON_OGC_GAMMA_TABLE_SIZE )
			    {
    				ReadLutData_Factory(usDataIndex,ucDataLen,lut_id,(BYTE *)g_pucDdcciTxBuf);
			    }

                if(usDataIndex + ucDataLen >= _BEACON_OGC_GAMMA_TABLE_SIZE)
                {
            	    DebugMessageUart("Tx End=", (usDataIndex + ucDataLen));
                    // PC ->[2020-04-10 14:54:03.202]# RECV ASCII>  16s
                    // MCU->[2020-04-10 14:54:19.034]# RECV ASCII>  12s
                }
                
                // For X-Rite & Embedded QA Data CheckSum:BYTE[0]lut cumulative value, BYTE[1]lut XOR value
				// Write: 6e 51 86 C2 0A 02 04[G2.2] 0C 18 CheckSum  delay 50ms Read 6 Data
                if(usDataIndex + ucDataLen == _BEACON_OGC_GAMMA_TABLE_SIZE + 2)
			    {
                    ReadLutData_CalCheckSum(lut_id,(BYTE *)g_pucDdcciTxBuf);
                }
            }
		    break;

		 case _DDCCI_SENSOR_CALIB_SET_COLOR_TEMP:  //ok
		 	{
				if(CMDPara[0] < _CT_COLORTEMP_AMOUNT)
				{
                    if(IsMonoChromeorColorPanel() == M_COLOR)		 
                    {
                    SET_COLOR_TEMP_TYPE(CMDPara[0]/*_CT_9300*/);                    
                    }
                    else
                    {
                    SET_COLOR_TEMP_TYPE(_CT_9300);                    
                    }
                        
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BEACON_GAMMA_PCM_PARTITION_SUPPORT == _ON)
				    if(UserCommonNVRamGetSystemData(_OGCOCC_SEL_BEACON) == _ON)
			    	{

#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
			    	}
#endif
                    OsdDispDisableOsd();
                }
		 	}
		    break;

		case _DDCCI_SENSOR_CALIB_GET_LUT_ATTRI:  //ok
			{
               //BYTE lut_id; 
               //LUT_ATTRI lut_attri;
               
				BYTE Lut_id = CMDPara[0];
				Lut_Attri LutAttri_temp;
                
				BYTE ucResult = _FAIL;
				BYTE ucLutIndex;

				Cmd_Reply = 1;

                // The order of tFacDefaultLut_Attri should be consistent with the order processed here
                ucLutIndex = ReadLut_ID_GammaIndex(Lut_id);

                DebugMessageUart("Get Lut:", ucLutIndex);
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex == _GAMMA_20)
                {
    				//  DICOM ALC
    				if(GET_OSD_DICOMALC() > _ALC_X_RAY)
				    {
        				ucLutIndex = (Lut_id & 0x1F);	
				    }
                    DebugMessageUart("_DICOM_ALC1:", _GAMMA_DICOM_ALC1);
                    DebugMessageUart("ALC New Lut:", ucLutIndex);
                }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex == _GAMMA_26)
                {
    				//  DICOM ALC
    				if(GET_OSD_DICOMALC() > _ALC_X_RAY)
				    {
        				ucLutIndex = (Lut_id & 0x1F) - 1;	
				    }
                    DebugMessageUart("ALC New Lut:", ucLutIndex);
                }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex == _GAMMA_DICOM450)
                {
    				//  DICOM ALC
    				if(GET_OSD_DICOMALC() > _ALC_X_RAY)
				    {
        				ucLutIndex = (Lut_id & 0x1F) - 1;	
				    }
                    DebugMessageUart("ALC New Lut:", ucLutIndex);
                }
#endif

                if(ucLutIndex <= _GAMMA_AMOUNT)
                {
                	ucResult = UserCommonEepromRead(_FT_LUTATTRIELEM_ADDRESS + (ucLutIndex * sizeof(LutAttri_temp)), sizeof(LutAttri_temp), (BYTE *)&LutAttri_temp );
                }                
               
				if(ucResult == _SUCCESS)
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(0x0C)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_LUT_ATTRI; //CMD
	
					g_pucDdcciTxBuf[4] = Lut_id;
					g_pucDdcciTxBuf[5] = LutAttri_temp.curve; 
					g_pucDdcciTxBuf[6] = LutAttri_temp.backlight[0];
					g_pucDdcciTxBuf[7] = LutAttri_temp.backlight[1];
					g_pucDdcciTxBuf[8] = LutAttri_temp.value[0];
					g_pucDdcciTxBuf[9] = LutAttri_temp.value[1];
					g_pucDdcciTxBuf[10] = LutAttri_temp.maxLuminance[0];
					g_pucDdcciTxBuf[11] = LutAttri_temp.maxLuminance[1];
					g_pucDdcciTxBuf[12] = LutAttri_temp.contrast[0];
					g_pucDdcciTxBuf[13] = LutAttri_temp.contrast[1];

                	g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum(); // checksum
				}
				else
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = 0x80;  // Length
    				
                	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				}
			}
			break;	

		case _DDCCI_SENSOR_CALIB_SET_LUT_ATTRI:  //ok
			{
               //BYTE lut_id; 
               //LUT_ATTRI lut_attri;

				BYTE Lut_id = CMDPara[0];
				Lut_Attri LutAttri_temp;
                
				BYTE ucResult = _FAIL;
				BYTE ucLutIndex;
                
                // The order of tFacDefaultLut_Attri should be consistent with the order processed here
                ucLutIndex = ReadLut_ID_GammaIndex(Lut_id);
                DebugMessageUart("Set Lut:", ucLutIndex);

#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex == _GAMMA_20)
                {
    				if(GET_OSD_DICOMALC() > _ALC_X_RAY)  //  DICOM ALC
				    {
        				//ucLutIndex = _GAMMA_DICOM_ALC1 + GET_OSD_DICOMALC() -1;	
        				ucLutIndex = (Lut_id & 0x1F);	
				    }
                    DebugMessageUart("ALC New Lut:", ucLutIndex);
                }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex == _GAMMA_26)
                {
    				if(GET_OSD_DICOMALC() > _ALC_X_RAY)  //  DICOM ALC
				    {
        				//ucLutIndex = _GAMMA_DICOM_ALC1 + GET_OSD_DICOMALC() -1;	
        				ucLutIndex = (Lut_id & 0x1F) - 1;	
				    }
                    DebugMessageUart("ALC New Lut:", ucLutIndex);
                }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                // !!! must sync GAMMA_NAME_INFO
                if(ucLutIndex == _GAMMA_DICOM450)
                {
    				if(GET_OSD_DICOMALC() > _ALC_X_RAY)  //  DICOM ALC
				    {
        				//ucLutIndex = _GAMMA_DICOM_ALC1 + GET_OSD_DICOMALC() -1;	
        				ucLutIndex = (Lut_id & 0x1F) - 1;	
				    }
                    DebugMessageUart("ALC New Lut:", ucLutIndex);
                }
#endif

                // protocol version >=5.0 and BeaconMonitorManager3.25
                //lut_id   CMDPara[0] 
				LutAttri_temp.curve = CMDPara[1];
				LutAttri_temp.backlight[0] = CMDPara[2]; //byte0:low 
				LutAttri_temp.backlight[1] = CMDPara[3]; //byte1:high

				LutAttri_temp.value[0] = CMDPara[4];  //byte0:low 
				LutAttri_temp.value[1] = CMDPara[5];  //byte1:high 

				LutAttri_temp.maxLuminance[0] = CMDPara[6]; //byte0:low   
				LutAttri_temp.maxLuminance[1] = CMDPara[7]; //byte1:high
				
				LutAttri_temp.contrast[0] = CMDPara[8]; //byte0:low   
				LutAttri_temp.contrast[1] = CMDPara[9]; //byte1:high

                if(ucLutIndex <= _GAMMA_AMOUNT)
                {
                	ucResult = UserCommonEepromWrite(_FT_LUTATTRIELEM_ADDRESS + (ucLutIndex * sizeof(LutAttri_temp)), sizeof(LutAttri_temp), (BYTE *)&LutAttri_temp );
    		    }   
                
				if(ucResult == _SUCCESS)
				{
#if 0//(_ARM_MCU_CALIBRATION_SUPPORT)
                    // New storage layout:MCU and PC calibration do not share a data storage area 
                    WORD g_usCurrPanelContrastRatio,g_usUserSetPanelContrastRatio;

                    // PC Calibration needs to update MCU calibration parameter to ensure UI QA success
                    // LC_GAMMA =0 LC_DICOM =1
                    if(LutAttri_temp.curve <= 0x01)
                    {
                        if(LutAttri_temp.curve == 0x00)
                        {
                            SET_OSD_LUT_USER_TYPE(_LUT_USER_GAMMA);
                            SET_OSD_LUT_USER_VALUE(((WORD)(LutAttri_temp.value[1]<<8) + LutAttri_temp.value[0])/10);
                        }
                        else if(LutAttri_temp.curve == 0x01)
                        {
                            SET_OSD_LUT_USER_TYPE(_LUT_USER_DICOM);
                            SET_OSD_LUT_USER_LAMB(((WORD)(LutAttri_temp.value[1]<<8) + LutAttri_temp.value[0])/10);
                        }
                        SET_OSD_LUT_USER_L_MAX(((WORD)(LutAttri_temp.maxLuminance[1]<<8) + LutAttri_temp.maxLuminance[0])/10);

                        // Check if the user setting parameters conform to the actual contrast of the panel
                        // Get Panel Contrast Ratio
        				RTDNVRamLoadPanelLuxRangeData();
                        g_usCurrPanelContrastRatio = MINOF((WORD)(g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax/g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin), (WORD)(g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax/g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin));
                        // Get User Setting
                        g_usUserSetPanelContrastRatio = ((WORD)(LutAttri_temp.contrast[1]<<8) + LutAttri_temp.contrast[0]);

                        SET_OSD_LUT_USER_L_MIN(((WORD)(LutAttri_temp.maxLuminance[1]<<8) + LutAttri_temp.maxLuminance[0])/MINOF(g_usCurrPanelContrastRatio, g_usUserSetPanelContrastRatio));
                        
                        RTDNVRamSaveUserLutData();
				    }
#endif
				}
			}
		    break;

		case _DDCCI_SENSOR_CALIB_SET_LUT_ENTRY_VALUE:  //ok
			{
                //BYTE entry_index[2];  [0] low byte [1] hight byte һ������ʾ�����һ��ȫ�ڻ��棬Ȼ���ֵΪ0
                //BYTE r[2]; /*byte 1 is most significant*/	
                //BYTE g[2]; /*byte 1 is most significant*/
                //BYTE b[2]; /*byte 1 is most significant*/
               
				WORD GammaData_R,GammaData_G,GammaData_B;

				GammaData_R = ((WORD)(CMDPara[2]) + (WORD)(CMDPara[3]<<8));
				GammaData_G = ((WORD)(CMDPara[4]) + (WORD)(CMDPara[5]<<8));
				GammaData_B = ((WORD)(CMDPara[6]) + (WORD)(CMDPara[7]<<8));
                            
				// Range check
				if((GammaData_R <= 0x3FFF)&&(GammaData_G <= 0x3FFF)&&(GammaData_B <= 0x3FFF))
				{					
                    //gamma tool data format->Scaler gamma lut data format
                    swap(&CMDPara[2],&CMDPara[3]/*,1*/); //R Word H|L swap
                    swap(&CMDPara[4],&CMDPara[5]/*,1*/); //G Word H|L swap
                    swap(&CMDPara[6],&CMDPara[7]/*,1*/); //B Word H|L swap

					ScalerColorOutputGammaAdjustRGBValue(&(CMDPara[2]));				
				}
			}
			break;

		case _DDCCI_SENSOR_CALIB_SET_SN:  //ok
			{	
				BYTE *Buffer = (BYTE *)&CMDPara[0];
                                                				
				if(RTDNVRamSaveMonitorSNData(_SN_BUF_LENGTH,Buffer) == _SUCCESS)
				{
    				BYTE ucIndex;
    				                
        	        DebugMessageUart("Set SN:", CMDPara[0]);
                	for(ucIndex = 0; ucIndex < _SN_BUF_LENGTH; ucIndex++)
                	{
            	        DebugMessageUart(":", CMDPara[1+ucIndex]);
                	}
				}
			}
			break;

		case _DDCCI_SENSOR_CALIB_GET_SN:   //ok
            // Write: 6e 51 82 c2 10 Checksum   Read: 28 Byte[Checksum]
			{
				Cmd_Reply = 1;
                               
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(2+_SN_BUF_LENGTH)); // Length 0x80|(0xC2,CMD,data(25))

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_SN; //CMD
                
				ReadSnHeader(g_pucDdcciTxBuf, 4);
                
            	g_pucDdcciTxBuf[4+_SN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break;

		case _DDCCI_SENSOR_CALIB_SET_CO_TABLE://ok
			{
               //BYTE btDataLen; /*bytes of real btData length */
               //BYTE offset; 
               //BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
               
				BYTE ucDataLen = CMDPara[0];				 
				BYTE ucDataIndex = CMDPara[1];
				BYTE *CorrespondenceTable = (BYTE *)&CMDPara[2];
				BYTE ucResult = _FAIL;
                 
				if((ucDataIndex+ucDataLen) <= _FT_CorrespondeceTableSize)//CO_TABLE 256bytes		
			    {
                	ucResult = UserCommonEepromWrite(_FT_CORRESPONDENCE_ADDRESS+ucDataIndex, ucDataLen, CorrespondenceTable);
			    }
                
				if(ucResult == _SUCCESS)
				{
				
				}
			}
		    break;

		case _DDCCI_SENSOR_CALIB_GET_CO_TABLE:  //ok
		    {
				BYTE ucDataLen = CMDPara[0];
				BYTE ucDataIndex = CMDPara[1];
				BYTE Bp_Data[ORDER_PART_DATE_LEN];
				BYTE ucResult = _FAIL;
				BYTE i;
                
				Cmd_Reply = 1;
				
				if((ucDataIndex+ucDataLen) <= _FT_CorrespondeceTableSize)
			    {
                	ucResult = UserCommonEepromRead(_FT_CORRESPONDENCE_ADDRESS+ucDataIndex, ucDataLen, Bp_Data );
			    }
                
                //avoid crash Ddcci communication module
                if(ucDataLen > ORDER_PART_DATE_LEN)
                {
                    ucDataLen = ORDER_PART_DATE_LEN;
                }
                //--------------------------------------
                
				if(ucResult == _SUCCESS)
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(4+ucDataLen)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_CO_TABLE; //CMD
					g_pucDdcciTxBuf[4] = ucDataLen;
					g_pucDdcciTxBuf[5] = ucDataIndex;
					for(i=0;i<ucDataLen;i++)
					{
						g_pucDdcciTxBuf[6+i] = Bp_Data[i];
					}

                	g_pucDdcciTxBuf[6+ucDataLen] = UserCommonDdcciCalCheckSum(); // checksum
				}
				else
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = 0x80;  // Length
    				
                	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				}	
			}
		    break;

		case _DDCCI_SENSOR_CALIB_SET_FSENSOR_I2C: /* write front sensor I2C, for factory use*/ //ok
			{		
               //BYTE btDataLen; /*bytes of real btData length */
               //BYTE dev_addr; 
               //BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
               
				BYTE ucDataLen = CMDPara[0];
				BYTE Dev_addr = CMDPara[1];
				BYTE *BpData = (BYTE *)&CMDPara[2];
				
            	if(g_bFrontSensorInitState == _FAIL)
			    {
					FSensor_init();
			    }

            	if(g_bFrontSensorInitState == _DEVICE_ID_TCS3414)
				{
	             /*   if(UserCommonEepromIICWrite(_FRONT_SENSOR_TCS3414_IIC_ADDR, Dev_addr, 1, ucDataLen, BpData, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	                {
	                    //return _FAIL;
	                }
	                
	                if(UserCommonEepromIICRead(_FRONT_SENSOR_TCS3414_IIC_ADDR, Dev_addr, 1, 8, I2CReadPtr, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	                {
	                    //return _FAIL;
	                }
				}
				else if(g_bFrontSensorInitState == _DEVICE_ID_MTCSCDCAF)
				{
	                if(UserCommonEepromIICWrite(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, Dev_addr, 1, ucDataLen, BpData, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1, _WRITE_SIZE_8) == _FAIL)
	                {
	                    //return _FAIL;
	                }
	                
	                if(UserCommonEepromIICRead(_FRONT_SENSOR_MTCSCDCAF_IIC_ADDR, Dev_addr, 1, 8, I2CReadPtr, _IIC_SYS_BUS_EXTDEV_I2C1, _PCB_SYS_EXTDEV_IIC1) == _FAIL)
	                {
	                    //return _FAIL;
	                }*/
				}
			}
			break;

		case _DDCCI_SENSOR_CALIB_GET_FSENSOR_I2C: /* read front sensor I2C, for factory use*///ok
			{
				BYTE ucDataLen = CMDPara[0];
				BYTE Dev_addr = CMDPara[1];
				BYTE ucIndex;
				
				Cmd_Reply = 1;
                
                //avoid crash Ddcci communication module
                if(ucDataLen > ORDER_PART_DATE_LEN)
                {
                    ucDataLen = ORDER_PART_DATE_LEN;
                }
                //--------------------------------------
								
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(4+ucDataLen)); // Length 0x80|(0xC2,CMD,data)

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FSENSOR_I2C; //CMD
				g_pucDdcciTxBuf[4] = ucDataLen;
				g_pucDdcciTxBuf[5] = Dev_addr;
				for(ucIndex = 0; ucIndex < ucDataLen; ucIndex++)
				{
				   g_pucDdcciTxBuf[6+ucIndex]=I2CReadPtr[ucIndex];
				   I2CReadPtr[ucIndex] = 0;
				}
                
            	g_pucDdcciTxBuf[6+ucDataLen] = UserCommonDdcciCalCheckSum(); // checksum
		    }
		    break;

        case _DDCCI_SENSOR_CALIB_SET_FSENSOR_MATRIX: /*write RGB->CIE matrix*/ //ok
			{
               //BYTE r[3][4]; /*float*10000*/  //��λ��ǰ����λ�ں�
               //BYTE g[3][4]; /*float*10000*/
               //BYTE b[3][4]; /*float*10000*/
               
				BYTE ucResult = _FAIL;
				BYTE *Buffer;
				Buffer = (BYTE *)&CMDPara[0];
                
            	ucResult = UserCommonEepromWrite(_FT_MATRIX_ADDRESS, _FT_MatrixSize, Buffer);

				if(ucResult == _SUCCESS)
				{
					RefreshMatrix=0;					
				}
			}
		    break;

        case _DDCCI_SENSOR_CALIB_GET_FSENSOR_MATRIX: /*Read RGB->CIE matrix*/ //ok
			{
               //BYTE r[3][4]; /*float*10000*/  //��λ��ǰ����λ�ں�
               //BYTE g[3][4]; /*float*10000*/
               //BYTE b[3][4]; /*float*10000*/
               
				BYTE Bp_Data[_FT_MatrixSize];
				BYTE i;
				BYTE ucResult = _FAIL;
                
				Cmd_Reply = 1;

            	ucResult = UserCommonEepromRead(_FT_MATRIX_ADDRESS, _FT_MatrixSize, Bp_Data );
                                                
				if(ucResult == _SUCCESS)
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(3+_FT_MatrixSize)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FSENSOR_MATRIX;
					for(i=0;i<_FT_MatrixSize;i++)
					{
						g_pucDdcciTxBuf[4+i] = Bp_Data[i];
					}

                	g_pucDdcciTxBuf[4+_FT_MatrixSize] = UserCommonDdcciCalCheckSum(); // checksum
				}
				else
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = 0x80;  // Length
    				
                	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				}	
			}
		    break;
            
		 case _DDCCI_SENSOR_CALIB_SET_GSDF_DATA:
		 	{
            	//BYTE btDataLen; /*bytes of real btData length */
            	//BYTE offset[2]; /*byte 1 is most significant*/
            	//BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
            	
				BYTE ucDataLen = CMDPara[0]; //bytes of real btData length 
				WORD usAddress = (WORD)((WORD)(CMDPara[2]<<8)+CMDPara[1]); //byte 1 is most significant
				BYTE *btData = (BYTE *)&CMDPara[3];								
				BYTE ucResult = _FAIL;
                
				if((usAddress+ucDataLen) <= _FT_GSDFSize)
				{
                	ucResult = UserCommonEepromWrite(_FT_GSDF_ADDRESS+usAddress, ucDataLen, btData);

					if(ucResult==_SUCCESS)
					{
					
					}
				}
		 	}
		    break;

		    case _DDCCI_SENSOR_CALIB_GET_GSDF_DATA:
		 	{
				BYTE ucDataLen = CMDPara[0]; //bytes of real Data length  
				WORD usAddress = (WORD)((WORD)(CMDPara[2]<<8)+CMDPara[1]); //byte 1 is most significant
				BYTE btData[ORDER_PART_DATE_LEN];
				BYTE ucResult = _FAIL;
				BYTE ucIndex;

				Cmd_Reply = 1;

                //avoid crash Ddcci communication module
                if(ucDataLen > ORDER_PART_DATE_LEN)
                {
                    ucDataLen = ORDER_PART_DATE_LEN;
                }
		DebugMessageUart("_DDCCI_SENSOR_CALIB_GET_GSDF_DATA", _DDCCI_SENSOR_CALIB_GET_GSDF_DATA);
                
                //--------------------------------------
                    
				if((usAddress+ucDataLen) <= _FT_GSDFSize)
				{		   					
	            	ucResult = UserCommonEepromRead(_FT_GSDF_ADDRESS+usAddress, ucDataLen, btData);

					if(ucResult == _SUCCESS)
					{
                		g_pucDdcciTxBuf[0] = 0x6e;	// Source
        				g_pucDdcciTxBuf[1] = (0x80|(5+ucDataLen)); // Length
        				
                		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
    					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_GSDF_DATA; //CMD
    					g_pucDdcciTxBuf[4] = ucDataLen;
						g_pucDdcciTxBuf[5] = (BYTE)(usAddress&0xFF);
						g_pucDdcciTxBuf[6] = (BYTE)(usAddress>>8);
    					for(ucIndex = 0; ucIndex < ucDataLen; ucIndex++)
    					{
    						g_pucDdcciTxBuf[7+ucIndex] = btData[ucIndex];
    					}

                    	g_pucDdcciTxBuf[7+ucDataLen] = UserCommonDdcciCalCheckSum(); // checksum
		DebugMessageUart("checkcum", g_pucDdcciTxBuf[7+ucDataLen]);
                    	
				   }
				   else
				   {
                		g_pucDdcciTxBuf[0] = 0x6e;	// Source
        				g_pucDdcciTxBuf[1] = 0x80;  // Length
                    	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				   }
				}
		 	}
			break;
			
			case _DDCCI_SENSOR_CALIB_GET_GAMMA_NAME_INFO:  //
			{
                // Eg: "CAL,Native,1.8,2.0,2.2,CIE,User1,User2.." 
            	// For X-Rite & Embedded MCU Redefine:Lut_id [Bit7~Bit5]is the colortemp Index [Bit4~Bit0] is the GammaTab Index
                // Eg: "CAL,Native,1.8,2.0,2.2,CIE,User1,User2..;D93,D65" 
                // CT&Gamma Index: ->GAMMA_NAME_INFO	   

                //Write:  0x6e 0x51 0x83 0xC2 0x19 0x00 CheckSum:0x71  
                //Write:  0x6e 0x51 0x83 0xC2 0x19 0x16 CheckSum:0x71  

				BYTE ucDataIndex = CMDPara[0]; // 0 22 44 66 88 110...
				BYTE Bp_Data[ORDER_PART2_DATE_LEN];
				BYTE ucResult = _FAIL;
				BYTE ucIndex;
                
				Cmd_Reply = 1;
            	DebugMessageUart("_NAME_Index:", ucDataIndex);

				if(ucDataIndex <= _FT_GammaNameInfoSize)
			    {
			        // Get Gamma Name Info
					ReadGammaName(Bp_Data,(ucDataIndex/ORDER_PART2_DATE_LEN));	

            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(2 + ORDER_PART2_DATE_LEN)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_GAMMA_NAME_INFO; //CMD
					for(ucIndex = 0; ucIndex < ORDER_PART2_DATE_LEN; ucIndex++)
					{
						g_pucDdcciTxBuf[4+ucIndex] = Bp_Data[ucIndex];
					}
					
                	g_pucDdcciTxBuf[4+ORDER_PART2_DATE_LEN] = UserCommonDdcciCalCheckSum(); // checksum
				}
				else
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = 0x80;  // Length
    				
                	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				}	
			}			
			break;

			case _DDCCI_SENSOR_CALIB_GET_CURRENT_GAMMA:
			//Write: 6e 51 82 C2 1A CheckSum
			//Read:  6e 51 83 C2 1A Lut_id CheckSum
			{
            	// For X-Rite & Embedded MCU Redefine:Lut_id [Bit7~Bit5]is the colortemp Index [Bit4~Bit0] is the GammaTab Index
            	BYTE Lut_id;
            	BYTE gamma_table,color_temp = 0;

				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(0x03)); // Length 0x80|(0xC2,CMD,data)

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_CURRENT_GAMMA;//CMD

                // UI Gamma & CT to Lut_id
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
				if(GET_OSD_GAMMA() == _GAMMA_24)
#else
				if(GET_OSD_GAMMA() == _GAMMA_CALIB)
#endif
			    {
					gamma_table = 0;
			    }
    			else if(GET_OSD_GAMMA() == _GAMMA_OFF)
			    {
					gamma_table = 1;
			    }
                else
                {
#if (_GAMMA_TYPE == _GAMMA_NAME_G22_DICOM_USER_CALIB)
                    // "CAL,OFF,2.2=2,DICOM=3,User=4,Hybrid =5,Dicom+0.3=6,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93"  
                    if(GET_OSD_GAMMA() == _GAMMA_20) // DICOM ALC
                    {
                    	DebugMessageUart("Get _DICOMALC:", GET_OSD_DICOMALC());
                        if(GET_OSD_DICOMALC() == 0) // _ALC_X_RAY
                        {
        					gamma_table = GET_OSD_GAMMA() + 1;
                        }
                        else
                        {
        					gamma_table = _GAMMA_DICOM_ALC1 + GET_OSD_DICOMALC() - _ALC_CT_MR_NM;
                        }
                    }
                    else if(GET_OSD_GAMMA() == _GAMMA_26) // Hybrid
                    {
    					gamma_table = GET_OSD_GAMMA();
                    }
                    else
                    {
    					gamma_table = GET_OSD_GAMMA() + 1;
                    }

#elif (_GAMMA_TYPE == _GAMMA_NAME_G20_G22_G24_G26_DICOM_CALIB)
                    // "CAL,OFF,2.0=2,2.2,2.4,2.6,DICOM=6,Dicom+0.3,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
                    if(GET_OSD_GAMMA() == _GAMMA_26) // DICOM ALC
                    {
                    	DebugMessageUart("Get _DICOMALC:", GET_OSD_DICOMALC());
                        if(GET_OSD_DICOMALC() == 0) // _ALC_X_RAY
                        {
        					gamma_table = GET_OSD_GAMMA() + 1;
                        }
                        else
                        {
        					gamma_table = _GAMMA_DICOM_ALC1 + GET_OSD_DICOMALC() ;
                        }
                    }
                    else
                    {
    					gamma_table = GET_OSD_GAMMA() + 1;
                    }
#elif (_GAMMA_TYPE == _GAMMA_NAME_G22_MULTI_DICOM_D200_D600_CALIB)
                    // "CAL,OFF,2.2,D200,D250,D300,D350,D400,D450 8,D500,D550,D600,Dicom+0.3 c,Dicom+0.5,Dicom+0.75,Dicom+1.0,Dicom+1.3;CT65,CT93" // max size : 256 bytes
                    if(GET_OSD_GAMMA() == _GAMMA_DICOM450) // DICOM ALC
                    {
                    	DebugMessageUart("Get _DICOMALC:", GET_OSD_DICOMALC());
                        if(GET_OSD_DICOMALC() == 0) // _ALC_X_RAY
                        {
        					gamma_table = GET_OSD_GAMMA() + 1;
                        }
                        else
                        {
        					gamma_table = _GAMMA_DICOM_ALC1 + GET_OSD_DICOMALC() ;
                        }
                    }
                    else
                    {
    					gamma_table = GET_OSD_GAMMA() + 1;
                    }

#else
					gamma_table = GET_OSD_GAMMA() + 1;
#endif
                }

            	DebugMessageUart("Get Name Lut:", gamma_table);
                if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
                {
    				if(GET_COLOR_TEMP_TYPE() == _CT_9300)
    					color_temp = 2;
    				else if(GET_COLOR_TEMP_TYPE() == _CT_7500)
    					color_temp = 1;
    				else
    					color_temp = 0;
                }
                else
                {
    				if(GET_COLOR_TEMP_TYPE() < _CT_6500)
    					color_temp = 1;
    				else 
    					color_temp = 0;
                }
            	DebugMessageUart("Get Name CT:", color_temp);

                Lut_id = ((BYTE)(color_temp << 5) & (_BIT7|_BIT6|_BIT5))|(gamma_table & 0x1F);
            	DebugMessageUart("Get Lut_id:", Lut_id);
                
				g_pucDdcciTxBuf[4] = Lut_id;
            	g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break;

			case _DDCCI_SENSOR_CALIB_SET_CURRENT_GAMMA:
			{
				// Write: 6e 51 83 C2 1B 00 65->Cal
				// Write: 6e 51 83 C2 1B 01 64->Off

                // for Beacon Sensor Tool protocol V4.0:CAL-OFF-1.8-2.0-...
                // for RTD2796 code: OFF-1.8-2.0-...CAL
            	// For X-Rite & Embedded MCU Redefine:Lut_id [Bit7~Bit5]is the colortemp Index [Bit4~Bit0] is the GammaTab Index

				BYTE lut_id = CMDPara[0];
            	BYTE gamma_table,color_temp;
             	
                //ucLutIndex = (lut_id & 0x1F);
                //ucCTIndex = ((lut_id & (_BIT7|_BIT6|_BIT5)) >> 5) & 0x07;
                gamma_table = ReadLut_ID_GammaIndex(lut_id);
                color_temp = ReadLut_ID_ColorTempIndex(lut_id);
             	//DebugMessageUart("Set gamma:", gamma_table);
             	//DebugMessageUart("Set CT:", color_temp);
                if(IsMonoChromeorColorPanel() == M_MONO)		 
                {
                color_temp = _CT_9300;
                }

				if(gamma_table <= _GAMMA_AMOUNT)
				{  

    				if(gamma_table <= _GAMMA_AMOUNT)
        			{
                        SET_COLOR_TEMP_TYPE (color_temp);
                        SET_OSD_GAMMA( gamma_table);
#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
                        OsdDispDisableOsd();
        			}
				}
			}
			break;
			
			//case _DDCCI_SENSOR_CALIB_GET_INFO: // Matrix Tool
			case _DDCCI_SENSOR_CALIB_GET_PROTOCOL_INFOR:
			{
            	//BYTE protocol_version[2]; /*for the protocol version [1], major, [0], minor current version 4.0 */ 
            	//BYTE type;                //for the chip
            	//BYTE typeLable[10];       //for the chip name, Last 3 is Protocol
            	//BYTE PWMDutyrange[2];     //for the chip PWM Duty adjustment range
            	//BYTE reserved[3];
            	
				Cmd_Reply = 1;
                
        		g_pucDdcciTxBuf[0] = 0x6e;	        // Source
				g_pucDdcciTxBuf[1] = (0x80|(0x14)); // Length

        		g_pucDdcciTxBuf[2] = 0xc2;	        // Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_PROTOCOL_INFOR;//CMD

                // the protocol version of the communication.
				g_pucDdcciTxBuf[4] = SENSOR_VERSION_MINOR; 			//Version minor
				g_pucDdcciTxBuf[5] = SENSOR_VERSION_MAJOR; 			//Version Major

                // 0x00:data_read_max=55 Write:55  0x01:data_read_max=22 Write:55 0x02:data_read_max=112 Write:112
                // 0x03:data_read_max=22 Write:22 other:data_read_max=22 Write:55 
				// RTD2796 All parameters are OK: ScalerMcuDdcci*SendData->1ms & _DDCCI_TIMEOUT_LIMIT = 800ms(2P LR >500)
				// Note!!! that there must be a write control before reading data larger than 22Byte and the interval time is between 30ms and _DDCCI_TIMEOUT_LIMIT
				// BeaconMonitorManager3.12 change 0x00:data_read_max=56->55
//								0x00:  Write:55 Read : 55
//								0x01 : Write:55 Read : 22	
//								0x02 : Write : 112 Read : 112
//								0x03 : Write : 22 Read : 22  (BeaconMonitorManage3.18������)
//								����:  Write : 55 Read : 22

                // 0x00  _DDCCI_RXBUF_LENGTH & _DDCCI_TXBUF_LENGTH   ==  64
                // 0x02  _DDCCI_RXBUF_LENGTH & _DDCCI_TXBUF_LENGTH   ==  128     UserCommonInterfaceGetDpMstCapablePort
                g_pucDdcciTxBuf[6] = 0x01;//(0x00); // (UserCommonInterfaceGetDpMstCapablePort() != _DP_MST_NO_PORT) ? (0x00) : (0x02);

				g_pucDdcciTxBuf[7] = 'R';          // 
				g_pucDdcciTxBuf[8] = 'T';          // 
				g_pucDdcciTxBuf[9] = 'D';          // 
				g_pucDdcciTxBuf[10] = '2';         // 
				g_pucDdcciTxBuf[11] = '7';         // 
				g_pucDdcciTxBuf[12] = '8';         // 
				g_pucDdcciTxBuf[13] = '5';         // 
#if (defined(_PROTOCOL_DBI_COLOR_SENSOR_CALIBRATION))
				g_pucDdcciTxBuf[14] = 'D';         // DBI
				g_pucDdcciTxBuf[15] = 'B';         // 
				g_pucDdcciTxBuf[16] = 'I';         // 
#else
				g_pucDdcciTxBuf[14] = 'B';         // BEACON
				g_pucDdcciTxBuf[15] = 'E';         // 
				g_pucDdcciTxBuf[16] = 'A';         // 
#endif
                usTemp = _BACKLIGHT_MAX;
				g_pucDdcciTxBuf[17] = (BYTE)((usTemp)&0xFF);          
				g_pucDdcciTxBuf[18] = (BYTE)((usTemp>>8)&0xFF);         
				g_pucDdcciTxBuf[19] = 0x00;         //reserved 1
				g_pucDdcciTxBuf[20] = 0x00;         //reserved 2
				g_pucDdcciTxBuf[21] = 0x00;         //reserved 3

            	g_pucDdcciTxBuf[22] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break;
            
            case _DDCCI_SENSOR_CALIB_GET_GEN_BASIC_INFO:
			{
				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] =(0x80|(0x17)); //length 0x17 (0xC2,cmd,data,checksum)

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_GEN_BASIC_INFO;//CMD

				// the protocal version of the communication.
				g_pucDdcciTxBuf[4] = SENSOR_VERSION_MINOR;	   //Version minor
				g_pucDdcciTxBuf[5] = SENSOR_VERSION_MAJOR;	   //Version Major

                // Update sensor status
            	if(g_bFrontSensorInitState == _FAIL)
                {
DebugMessageUart("FrontInitState", g_bFrontSensorInitState);
            		FSensor_init();
                }
                
            	if(g_bBacklightSensorInitState == _FAIL)
                {
            		InitBacklightSensorModule();
                }
                              
			 	if(g_bFrontSensorInitState != _FAIL)
			 	{
					g_pucDdcciTxBuf[6] = MODEL_COLOR_TYPE;//0x01;                 //MODEL_COLOR_TYPE;	Mono=0 Color=1
					// sensor,bit[2]=backlight sensor,bit[1]=amb sensor,bit[0]=Front sensor, 
					if(g_bBacklightSensorInitState !=_FAIL)
                    g_pucDdcciTxBuf[7] = 0x07;                 //sensor, 	
                    else
                    g_pucDdcciTxBuf[7] = 0x03;                 //sensor, 	                        
				}
				else
				{
				    // 1.add 0x80 to model type;
				    // 2.set bit[2]=1.
					g_pucDdcciTxBuf[6] = 0x80|MODEL_COLOR_TYPE;//0x01;
					// sensor,bit[2]=backlight sensor
					if(g_bBacklightSensorInitState != _FAIL)
    					g_pucDdcciTxBuf[7] = 0x06;	   //sensor, bit[2]=backlight sensor,bit[1]=amb sensor, bit[0]=front sensor						
                    else
    					g_pucDdcciTxBuf[7] = 0x02;	   //sensor, bit[2]=backlight sensor,bit[1]=amb sensor, bit[0]=front sensor						
				}
	
				// reflection factor - N/A
				g_pucDdcciTxBuf[8] = 0x00;				        //reflection factor	
				g_pucDdcciTxBuf[9] = 0x00;					    //reflection factor	

				// Compression method  RTD2796 must 0x03
				g_pucDdcciTxBuf[10] = 0x03;              	    //compression mode of LUT

				// LUT step  max - 1024
				g_pucDdcciTxBuf[11] = 0xff;					    //lut_input_step - 1023 steps
				g_pucDdcciTxBuf[12] = 0x03;					    //lut_input_step

				// LUT value max - 16383
				g_pucDdcciTxBuf[13] = 0xff;						//lut_input_max 
				g_pucDdcciTxBuf[14] = 0x3f;						//lut_input_max  16383

				// LUT gamma size : the size of the total bytes 
				g_pucDdcciTxBuf[15] = 0x0c;				        //lut_output_max -6156 
				g_pucDdcciTxBuf[16] = 0x18;						//lut_output_max

				//Dicom support type
				g_pucDdcciTxBuf[17] = DICOM_SURPORT_TYPE1;		//dicom_support_type
				g_pucDdcciTxBuf[18] = DICOM_SURPORT_TYPE2;		//dicom_support_type

				// color temperature
				g_pucDdcciTxBuf[19] = COLORTEMP_SURPORT_TYPE1;	//COLOR_TEMPERATURE_SURPORT_TYPE
				g_pucDdcciTxBuf[20] = COLORTEMP_SURPORT_TYPE2;	//COLOR_TEMPERATURE_SURPORT_TYPE

				// bt_luminance_max
    			g_pucDdcciTxBuf[21] = (BYTE)(600&0xFF);			//max_num_preset_luts;
    			g_pucDdcciTxBuf[22] = (BYTE)(600>>8);;			//max_num_preset_luts;

				// scaler fw version -v1.2
				g_pucDdcciTxBuf[23] = 0x01;						//scaler_fw_ver -[0], major, [1], minor
				g_pucDdcciTxBuf[24] = 0x02;						//scaler_fw_ver -[0], major, [1], minor

            	g_pucDdcciTxBuf[25] = UserCommonDdcciCalCheckSum(); // checksum
			}
//OsdDispOsdMessage(_OSD_DISP_DICOM_RESULT);
//OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(0 + 7), g_bFrontSensorInitState, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _MAIN_WIN_COLOR));
			break;	
            
            case _DDCCI_SENSOR_CALIB_GET_DISP_RES_AND_POS:
			// Write: 6e 51 82 C2 1E CheckSum
			{
                // VStart Offset must sync OsdFuncCalibrationWindowsColor
                BYTE ucVPosOffset;

                if(_PANEL_DV_HEIGHT == 2560)
                {
                    ucVPosOffset = 140;
                }
                else if(_PANEL_DV_HEIGHT == 2048)
                {
                    ucVPosOffset = 100;
                }
            	else
                {
                    ucVPosOffset = 102; 
                }
                
				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	        // Source
				g_pucDdcciTxBuf[1] = (0x80|(0x12)); // Length

        		g_pucDdcciTxBuf[2] = 0xc2;	        // Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_DISP_RES_AND_POS;//CMD

                // the protocal version of the communication.
				g_pucDdcciTxBuf[4] = LOBYTE(_PANEL_DH_WIDTH);              //display default resolution width
				g_pucDdcciTxBuf[5] = HIBYTE(_PANEL_DH_WIDTH); 	
                g_pucDdcciTxBuf[6] = LOBYTE(_PANEL_DV_HEIGHT);             //display default resolution height
				g_pucDdcciTxBuf[7] = HIBYTE(_PANEL_DV_HEIGHT);     
				
				g_pucDdcciTxBuf[8] = LOBYTE(GET_INPUT_TIMING_HWIDTH());    //display real resolution width
				g_pucDdcciTxBuf[9] = HIBYTE(GET_INPUT_TIMING_HWIDTH());             
				g_pucDdcciTxBuf[10] = LOBYTE(GET_INPUT_TIMING_VHEIGHT());  //display real resolution height
				g_pucDdcciTxBuf[11] = HIBYTE(GET_INPUT_TIMING_VHEIGHT());            

                //front sensor window x
				g_pucDdcciTxBuf[12] = LOBYTE(_PANEL_DH_WIDTH - (_OSD_CALI_INFO_WIDTH*12));   
				g_pucDdcciTxBuf[13] = HIBYTE(_PANEL_DH_WIDTH - (_OSD_CALI_INFO_WIDTH*12));   
                //front sensor window y
				g_pucDdcciTxBuf[14] = LOBYTE(_PANEL_DV_HEIGHT - (_OSD_CALI_INFO_HEIGHT*18) - ucVPosOffset);   
				g_pucDdcciTxBuf[15] = HIBYTE(_PANEL_DV_HEIGHT - (_OSD_CALI_INFO_HEIGHT*18) - ucVPosOffset);    

                //front sensor window width
				g_pucDdcciTxBuf[16] = LOBYTE(_OSD_CALI_INFO_WIDTH*12);   
				g_pucDdcciTxBuf[17] = HIBYTE(_OSD_CALI_INFO_WIDTH*12);  
                //front sensor window height
				g_pucDdcciTxBuf[18] = LOBYTE(_OSD_CALI_INFO_HEIGHT*18);  
				g_pucDdcciTxBuf[19] = HIBYTE(_OSD_CALI_INFO_HEIGHT*18);    
				
            	g_pucDdcciTxBuf[20] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break;
            
           case _DDCCI_SENSOR_CALIB_GET_MODEL_STRING: 
			{
				Cmd_Reply = 1;
                
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(2+_FT_MonitorModelSize)); // Length 0x80|(0xC2,CMD,data(13))

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_MODEL_STRING;
				ReadModelName(g_pucDdcciTxBuf, 4);
                
            	g_pucDdcciTxBuf[4+_FT_MonitorModelSize] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break; 
            
           case _DDCCI_SENSOR_CALIB_GET_FSENSOR_MATRIX_PART:   
			{
                //BYTE btChannel;  //0 for r,1 for g, 2 fro b
                //BYTE data[3][4]; /*float *10000 ȡ��*/  //��λ��ǰ����λ�ں� 

				BYTE ucDataIndex = CMDPara[0];
				BYTE Bp_Data[_FT_Ch_MatrixSize];
				BYTE i;
				BYTE ucResult = _FAIL;
                
				Cmd_Reply = 1;
				
				if(ucDataIndex <= _FT_MatrixSize)
			    {
                	ucResult = UserCommonEepromRead(_FT_MATRIX_ADDRESS+ucDataIndex*_FT_Ch_MatrixSize, _FT_Ch_MatrixSize, Bp_Data );
			    }
                                                
				if(ucResult == _SUCCESS)
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(3+_FT_Ch_MatrixSize)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FSENSOR_MATRIX_PART;
					g_pucDdcciTxBuf[4] = ucDataIndex;
					for(i = 0;i < _FT_Ch_MatrixSize;i++)
					{
						g_pucDdcciTxBuf[5+i] = Bp_Data[i];
					}

                	g_pucDdcciTxBuf[5+_FT_Ch_MatrixSize] = UserCommonDdcciCalCheckSum(); // checksum
				}
				else
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = 0x80;  // Length
    				
                	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				}	
			}
			break;

            case _DDCCI_SENSOR_CALIB_SET_ATTRIBUTE_INFO:
			{
				// Write: 6e 51 84 C2 24 01 00 CheckSum
				// Write: 6e 51 84 C2 24 01 01 CheckSum

                // BYTE mode;  NULL=0  UNIFORMITY=1 PCM=2   
                // BYTE status; ON=1 OFF=0  
                
                if(CMDPara[0] == 0x01) // PanelUniformity
                {
                    if((CMDPara[1] == 0x00)||(CMDPara[1] == 0x01)) // On or Off
                    {
                        SET_OSD_PANEL_UNIFORMITY( CMDPara[1]);

#if(_UNIFORMITY_SUPPORT == _ON)
                        UserAdjustPanelUniformityMode(_DB_APPLY_POLLING);
#endif
                    }
                }
                else if(CMDPara[0] == 0x02) // PCM
                {
                    if((CMDPara[1] == 0x00)||(CMDPara[1] == 0x01)) // On or Off
                    {
                        SET_OSD_PCM_STATUS( CMDPara[1]);

                        OsdFuncColorPcmAdjust();
                    }
                }
			}
			break;

            case _DDCCI_SENSOR_CALIB_GET_ATTRIBUTE_INFO:
			{
				Cmd_Reply = 1;

                // Get Mode
				if(CMDPara[0] == 0x01) // PanelUniformity
				{
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(4)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_ATTRIBUTE_INFO;
					g_pucDdcciTxBuf[4] = CMDPara[0];
					g_pucDdcciTxBuf[5] = GET_OSD_PANEL_UNIFORMITY();
                	g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
				}
                else if(CMDPara[0] == 0x02) // PCM
                {
            		g_pucDdcciTxBuf[0] = 0x6e;	// Source
    				g_pucDdcciTxBuf[1] = (0x80|(4)); // Length
    				
            		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_ATTRIBUTE_INFO;
					g_pucDdcciTxBuf[4] = CMDPara[0];
					g_pucDdcciTxBuf[5] = GET_OSD_PCM_STATUS();                  
                	g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
				}
			}
			break;

        case _DDCCI_SENSOR_CALIB_SET_LUX_RANGE_PARAMTER:
			// parameter 0: CT index0, index1, 
			// Color temperature order of Gamma standard table
			
			// Beacon_Gamma_Color(I2C)2.29_T19: First page->[Support Auto Adjust Gamma]
			// Select the Auto Gamma option when the application generates calibration data.

			// 6e 51 8B C0 AA 00 00 07 69 CC 00 00 01 0B 76 -> max:485.8399 min:0.2679  [00 07 69 CC = 0x769CC = 485836 = 485.8399*1000]
			// 6e 51 8B C0 AA 01 00 06 15 6A 00 00 01 0B AC -> max:398.699  min:0.2679
			// 6e 51 8B C0 AA 02 00 06 C8 96 00 00 01 0B 8E -> max:444.5644 min:0.2679			
			{				
		        if(CMDPara[0]== _DDCCI_BYPASS_PARAMTER)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
#endif
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
				}
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
				else if(CMDPara[0]== _DDCCI_COLOR1_PARAMTER)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
				}
				else if(CMDPara[0]== _DDCCI_COLOR2_PARAMTER)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
				}
                else if(CMDPara[0]== _DDCCI_COLOR3_PARAMTER)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
				}
#else
				else if(CMDPara[0]== _DDCCI_COLOR1_PARAMTER)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
				}
				else if(CMDPara[0]== _DDCCI_COLOR2_PARAMTER)
				{
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax = (((SDWORD)CMDPara[1] << 24) | ((SDWORD)CMDPara[2] << 16) | ((SDWORD)CMDPara[3] << 8) | ((SDWORD)CMDPara[4] << 0));
	                g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin = (((SDWORD)CMDPara[5] << 24) | ((SDWORD)CMDPara[6] << 16) | ((SDWORD)CMDPara[7] << 8) | ((SDWORD)CMDPara[8] << 0));
				}
#endif
DebugMessageUart("g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax);
DebugMessageUart("g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax", g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax);

                RTDNVRamSavePanelLuxRangeData();
			}
            break;
        
        case _DDCCI_SENSOR_CALIB_GET_LUX_RANGE_PARAMTER:
			// Write:6e 51 82 C0 AC Checksum ->50ms 
			// Read: 6e A1 C0 27 [48 FF 2E C0 44 05 40 00] [48 FF 2E C0 44 05 40 00] [48 D2 B7 E0 44 05 40 00] [48 FD 4F E0 44 05 40 00] 7B -> max:522.614 min:0.533  max:522.614 min:0.533  max:431.551 min:0.533 max:518.783 min:0.533
            {
				DWORD ucMax,ucMin;

                Cmd_Reply = 1;
				               
                g_pucDdcciTxBuf[0] = 0x6e;       // Source
#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
                g_pucDdcciTxBuf[1] = (0x80|34);  // Length [8x4+2] //Byte size from next byte to before byte of checksum
#else
                g_pucDdcciTxBuf[1] = (0x80|26);  // Length [8x3+2] //Byte size from next byte to before byte of checksum
#endif
                g_pucDdcciTxBuf[2] = 0xc2;
                g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_LUX_RANGE_PARAMTER; // cmd

				RTDNVRamLoadPanelLuxRangeData();
DebugMessageUart("CT_9300].ucLuxMax", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucLuxMax);
DebugMessageUart("_CT_9300].ucRealLuxMax", g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax);
                // Bypass->Off[Native]
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucLuxMin,4);
			    g_pucDdcciTxBuf[4] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[5] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[6] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[7] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[8] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[9] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[10] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[11] = (BYTE)(((DWORD)ucMin & 0x000000ff));

#if(_ENABLE_CANON_THREE_CT_SUPPORT == _ON)
                // COLOR1
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[12] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[13] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[14] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[15] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[16] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[17] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[18] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[19] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                // COLOR2
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_7500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[20] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[21] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[22] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[23] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[24] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[25] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[26] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[27] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                // COLOR3
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax,4);
			    memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[28] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[29] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[30]= (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[31]= (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[32]= (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[33]= (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[34]= (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[35]= (BYTE)(((DWORD)ucMin & 0x000000ff));
			
                g_pucDdcciTxBuf[36] = UserCommonDdcciCalCheckSum(); // checksum
#else
                // COLOR1
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax,4);
				memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[12] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[13] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[14] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[15] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[16] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[17] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[18] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[19] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                // COLOR2
			    memcpy(&ucMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax,4);
			    memcpy(&ucMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[20] = (BYTE)(((DWORD)ucMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[21] = (BYTE)(((DWORD)ucMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[22] = (BYTE)(((DWORD)ucMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[23] = (BYTE)(((DWORD)ucMax & 0x000000ff));
			    g_pucDdcciTxBuf[24] = (BYTE)(((DWORD)ucMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[25] = (BYTE)(((DWORD)ucMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[26] = (BYTE)(((DWORD)ucMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[27] = (BYTE)(((DWORD)ucMin & 0x000000ff));

                g_pucDdcciTxBuf[28] = UserCommonDdcciCalCheckSum(); // checksum
#endif                
            }
            break;
            
           case _DDCCI_SENSOR_CALIB_SET_CUSTOM_DATA:
		 	{
            	//BYTE btDataLen; /*bytes of real btData length */
            	//BYTE offset[2]; /*byte 1 is most significant*/
            	//BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
            	
				BYTE ucDataLen = CMDPara[0]; //bytes of real btData length 
				WORD usAddress = (WORD)((WORD)(CMDPara[2]<<8)+CMDPara[1]); //byte 1 is most significant
				BYTE *btData = (BYTE *)&CMDPara[3];								
				BYTE ucResult = _FAIL;
                
				if((usAddress+ucDataLen) <= _FT_CustomDataSize)
				{
                	ucResult = UserCommonEepromWrite(_FT_CUSTOM_DATA_ADDRESS+usAddress, ucDataLen, btData);

					if(ucResult==_SUCCESS)
					{
					
					}
				}
		 	}
		    break;

           case _DDCCI_SENSOR_CALIB_GET_CUSTOM_DATA:
		 	{
				BYTE ucDataLen = CMDPara[0]; //bytes of real Data length  
				WORD usAddress = (WORD)((WORD)(CMDPara[2]<<8)+CMDPara[1]); //byte 1 is most significant
				BYTE btData[ORDER_PART_DATE_LEN];
				BYTE ucResult = _FAIL;
				BYTE ucIndex;

				Cmd_Reply = 1;

                //avoid crash Ddcci communication module
                if(ucDataLen > ORDER_PART_DATE_LEN)
                {
                    ucDataLen = ORDER_PART_DATE_LEN;
                }
                //--------------------------------------
                    
				if((usAddress+ucDataLen) <= _FT_CustomDataSize)
				{		   					
	            	ucResult = UserCommonEepromRead(_FT_CUSTOM_DATA_ADDRESS+usAddress, ucDataLen, btData);

					if(ucResult == _SUCCESS)
					{
                		g_pucDdcciTxBuf[0] = 0x6e;	// Source
        				g_pucDdcciTxBuf[1] = (0x80|(5+ucDataLen)); // Length
        				
                		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
    					g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_CUSTOM_DATA; //CMD
    					g_pucDdcciTxBuf[4] = ucDataLen;
						g_pucDdcciTxBuf[5] = (BYTE)(usAddress&0xFF);
						g_pucDdcciTxBuf[6] = (BYTE)(usAddress>>8);
    					for(ucIndex = 0; ucIndex < ucDataLen; ucIndex++)
    					{
    						g_pucDdcciTxBuf[7+ucIndex] = btData[ucIndex];
    					}

                    	g_pucDdcciTxBuf[7+ucDataLen] = UserCommonDdcciCalCheckSum(); // checksum
				   }
				   else
				   {
                		g_pucDdcciTxBuf[0] = 0x6e;	// Source
        				g_pucDdcciTxBuf[1] = 0x80;  // Length
                    	g_pucDdcciTxBuf[2] = UserCommonDdcciCalCheckSum(); // checksum
				   }
				}
				else
				{

				}
		 	}
			break;

           case _DDCCI_SENSOR_CALIB_GET_SYSTEM_TIME_TEMP:  
			{
                //BYTE Temperature;
                //g_stPanelTimeData
                
				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|12); // Length
				
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_SYSTEM_TIME_TEMP; //CMD

                // Temperature
                UserTemperatureSensorHandler();
				g_pucDdcciTxBuf[4] = (BYTE)(uctemperaturesensor&0xFF);

				// System Run Time
				g_pucDdcciTxBuf[5] = LOBYTE(GET_SYSTEM_RUN_TIME_HOUR());
				g_pucDdcciTxBuf[6] = HIBYTE(GET_SYSTEM_RUN_TIME_HOUR());
				g_pucDdcciTxBuf[7] = GET_SYSTEM_RUN_TIME_MIN();

				// Panel Run Time
				g_pucDdcciTxBuf[8] = LOBYTE(GET_PANEL_RUN_TIME_HOUR());
				g_pucDdcciTxBuf[9] = HIBYTE(GET_PANEL_RUN_TIME_HOUR());
				g_pucDdcciTxBuf[10] = GET_PANEL_RUN_TIME_MIN();

				// Panel Time
				g_pucDdcciTxBuf[11] = LOBYTE(GET_PANEL_TIME_HOUR());
				g_pucDdcciTxBuf[12] = HIBYTE(GET_PANEL_TIME_HOUR());
				g_pucDdcciTxBuf[13] = GET_PANEL_TIME_MIN();
                
            	g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum(); // checksum
			}
		    break;

		case _DDCCI_SENSOR_CALIB_GET_BACKLIGHT:  //0~255 or 4095
			{                
                //Write:  0x6e 0x51 0x82 0xC2 0x33 CheckSum  
                //Read:   0x6e 0x84 0xC2 0x33 L H CheckSum  

				Cmd_Reply = 1;

        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(0x04)); // Length
				
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_BACKLIGHT; //CMD

             	usTemp = PCB_GET_BACKLIGHT_PWM();
 #if(_BACKLIGHT_PWM_INVERSE == _ON)
                usTemp = _BACKLIGHT_MAX - usTemp;
 #endif
				g_pucDdcciTxBuf[4] = (BYTE)((usTemp)&0xFF); 			
				g_pucDdcciTxBuf[5] = (BYTE)((usTemp>>8)&0xFF); 	

            	g_pucDdcciTxBuf[6] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break;

           case _DDCCI_SENSOR_CALIB_GET_FW_VERSION: 
            // Write: 0x6e 0x51 0x82 0xC2 0x34 CheckSum:0x4b  
			{
				Cmd_Reply=1;
                
        		g_pucDdcciTxBuf[0] = 0x6e;	// Source
				g_pucDdcciTxBuf[1] = (0x80|(2+_SN_BUF_LENGTH)); // Length 0x80|(0xC2,CMD,data(25))

        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
				g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FW_VERSION;
				ReadFWVersion(g_pucDdcciTxBuf, 4);
                
            	g_pucDdcciTxBuf[4+_SN_BUF_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum
			}
			break; 

#if (_FPGA_COLOR_ADAPTIVE_SUPPORT)
           case _DDCCI_SENSOR_CALIB_SET_FPGA_HYBRID_GAMMA: 
            // Write: 0x6e 0x51 0x85 0xC2 0x35 0x20 0x00 0x01 CheckSum:0x4b  
			if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
			{
                //BYTE ucHybridGammaType; 
                      //0x20 for Hybrid Gamma Color Curve
				      //0x21 for Hybrid Gamma Gray Curve
				      //0x30 for Hybrid Gamma Adaptive Threshold
				      
                //BYTE ucHybridGammaCurve; ->use lut_id
                      //0~31 ->Please refer to _DDCCI_SENSOR_CALIB_GET_GAMMA_NAME_INFO
                      //0~7  -> For FPGA Adaptive Threshold
                      
                //BYTE ucHybridGammaEnable; 
				
				BYTE ucHybridGammaType = CMDPara[0];
				BYTE lut_id = CMDPara[1];
                BYTE ucHybridGammaEnable = CMDPara[2];
            	BYTE gamma_table,color_temp;

				// Beacon monitor APP List Conversion to Scaler UI List
                // Lut_id to UI Gamma Index
                gamma_table = ReadLut_ID_GammaIndex(lut_id);

                // Lut_id to UI CT Index
                color_temp = ReadLut_ID_ColorTempIndex(lut_id);
                //SET_COLOR_TEMP_TYPE( color_temp);

                if(ucHybridGammaType == 0x20)
            	{
    				if(gamma_table <= _GAMMA_AMOUNT)
    				{
                        // Is color curve
                        switch(gamma_table)
                        {
                            case _GAMMA_18 :
                                SET_OSD_FPGA_COLOR_GAMMA( gamma_table);
                                break;
                            case _GAMMA_20 :
                                SET_OSD_FPGA_COLOR_GAMMA( gamma_table);
                                break;
                            case _GAMMA_22 :
                                SET_OSD_FPGA_COLOR_GAMMA( gamma_table);
                                break;
                            case _GAMMA_24 :
                                SET_OSD_FPGA_COLOR_GAMMA( gamma_table);
                                break;

                            default:
                                break;

                        }
    				}
            	}
				else if(ucHybridGammaType == 0x21)
            	{
    				if(gamma_table <= _GAMMA_AMOUNT)
    				{                       
                        // Is gray curve
                        switch(gamma_table)
                        {
                            case _GAMMA_18 :
                                SET_OSD_FPGA_GRAY_GAMMA( gamma_table);
                                break;
                            case _GAMMA_20 :
                                SET_OSD_FPGA_GRAY_GAMMA( gamma_table);
                                break;
                            case _GAMMA_22 :
                                SET_OSD_FPGA_GRAY_GAMMA( gamma_table);
                                break;
                            case _GAMMA_24 :
                                SET_OSD_FPGA_GRAY_GAMMA( gamma_table);
                                break;

                            default:
                                break;

                        }
    				}
            	}
				else if(ucHybridGammaType == 0x30)
            	{
    				if(lut_id <= 7)
    				{                       
                        // Is Adaptive Threshold
                        UserCommonNVRamSetSystemData(_FPGA_COLOR_ADAPTIVE_THRESHOLD,lut_id);
    				}
            	}

                // Hybrid Gamma On/Off 
            	if(ucHybridGammaEnable <= _ON)
            	{
    				if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
    	            {	                
                        if(ucHybridGammaEnable == _ON)
                        {
                            //IsGammaOptionHybridGamma(GET_OSD_GAMMA());
                            SET_OSD_GAMMA( _GAMMA_26);
                        }
                        else
                        {
                            SET_OSD_GAMMA( _GAMMA_20);
                        }

#if(_GAMMA_FUNCTION == _ON)
                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                        if(GET_OSD_GAMMA() != _GAMMA_OFF)
                        {
                            UserAdjustGamma(GET_OSD_GAMMA());
                            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                        }
#endif
                        
    		            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
    				}
            	}        	
			}
			break; 

           case _DDCCI_SENSOR_CALIB_GET_FPGA_HYBRID_GAMMA: 
            // Write: 0x6e 0x51 0x82 0xC2 0x36 CheckSum:0x4b  Delay 50ms
            // Read:  0x6e 0x85 0xC2 0x36 0x02 0x0B 0x01 CheckSum:0x79  
            {				
            	BYTE gamma_table;
				Cmd_Reply = 1;

	            g_pucDdcciTxBuf[0] = 0x6E;
	        	g_pucDdcciTxBuf[1] = (0x80|5);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _DDCCI_SENSOR_CALIB_GET_FPGA_HYBRID_GAMMA;	// CMD

                // Color Curve
                {
                    // UI Gamma to Lut_id
    				if(GET_OSD_FPGA_COLOR_GAMMA() == _GAMMA_24)
    			    {
    					gamma_table = 0;
    			    }
        			else if(GET_OSD_FPGA_COLOR_GAMMA() == _GAMMA_OFF)
    			    {
    					gamma_table = 1;
    			    }
                    else
                    {
    					gamma_table = GET_OSD_FPGA_COLOR_GAMMA() + 1;
                    }

    	        	g_pucDdcciTxBuf[4] = gamma_table;         
    			}

                // Gray Curve
                {
                    // UI Gamma to Lut_id
    				if(GET_OSD_FPGA_GRAY_GAMMA() == _GAMMA_24)
    			    {
    					gamma_table = 0;
    			    }
        			else if(GET_OSD_FPGA_GRAY_GAMMA() == _GAMMA_OFF)
    			    {
    					gamma_table = 1;
    			    }
                    else
                    {
    					gamma_table = GET_OSD_FPGA_GRAY_GAMMA() + 1;
                    }

    	        	g_pucDdcciTxBuf[5] = gamma_table;         
    			}
                
                // Hybrid Gamma On/Off
	        	g_pucDdcciTxBuf[6] = IsGammaOptionHybridGamma(GET_OSD_GAMMA()); 
				
	            g_pucDdcciTxBuf[7] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
			break; 
#endif
                        
#if(_ARM_MCU_CALIBRATION_SUPPORT)
		case _DDCCI_NOTIFY_ARM_MCU_READ_DATA:
			{
				Cmd_Reply 		   = 1;
                RTDDdcciSendDataToARMMCU();
			}
			break;

		case _DDCCI_ARM_MCU_QA_RESULT:
			// u8 Cmd;           ->CMDCode
			// u8 type;          ->CMDPara[0]
			// u16 lumDiff[18];  ->(WORD)((WORD)(CMDPara[1])+(WORD)(CMDPara[2]<<8));

			// DICOM 
            // Write: 0x6e 0x51 0xA7 0xC2 0x41 0x00 0x1A 0x00 0x11 0x00 0x10 0x00... CheckSum:0x  

			// Gamma 
            // Write: 0x6e 0x51 0xA7 0xC2 0x41 0x01 0x1A 0x00 0x1A 0x00 0x1A 0x00... CheckSum:0x  

			{

			    BYTE ucCount;
			    WORD usMaxlumDiff = 0;  /*lumDiff[0]*100*/ 

				// Get Max
			    for(ucCount = 0; ucCount < 36; ucCount++)
				{
					if(ucCount%2 == 0)
					{
						usMaxlumDiff = (WORD)((WORD)(CMDPara[1+ucCount])+(WORD)(CMDPara[2+ucCount]<<8));
                        //DebugMessageUart("Diff:", usMaxlumDiff);
						if(usMaxlumDiff <= (WORD)((WORD)(CMDPara[1+ucCount])+(WORD)(CMDPara[2+ucCount]<<8)))
						{
							usMaxlumDiff = (WORD)((WORD)(CMDPara[1+ucCount])+(WORD)(CMDPara[2+ucCount]<<8));
						}
					}
				}
                //DebugMessageUart("lumDiff:", usMaxlumDiff);

				// Show QA Data
				OsdDispOsdMessage(_OSD_DISP_QA_RESULT);
		        OsdPropPutStringCenter(ROW(3), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_1, ((usMaxlumDiff/100) > 10) ? _STRING_FAIL : _STRING_PASS, (((usMaxlumDiff/100) > 10) ? COLOR(_CP_RED, _MAIN_WIN_COLOR) : COLOR(_CP_WHITE, _MAIN_WIN_COLOR)), GET_OSD_LANGUAGE());

                OsdPropPutString(ROW(5), COL(12), _PFONT_PAGE_1, _STRING_DEVIATION, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
	            OsdPropShowNumberPercentage(ROW(5), COL(20), ((usMaxlumDiff == 0) ? 1 : usMaxlumDiff), _TRUE, _PFONT_PAGE_1, (((usMaxlumDiff/100) > 10) ? COLOR(_CP_RED, _CP_BG) : COLOR(_CP_WHITE, _CP_BG)));

			    OsdFuncEnableOsd();
                ScalerTimerActiveTimerEvent(SEC(15), _USER_TIMER_EVENT_OSD_DISABLE);
			}
			break;

		case _DDCCI_ARM_MCU_GET_LUM_DIFF:
			{
				WORD usTemp;
	            usTemp = (WORD)(CMDPara[0]<<8)|CMDPara[1];
	            SET_OSD_LUT_USER_LUT_OFFSET(usTemp);
	            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_USER_LUTDATA_MSG);

				// Waiting for ARM MCU calculation to complete
	            ScalerTimerReactiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_SET_LUT_DATA);
			}
			break;

		case _DDCCI_ARM_MCU_GET_VERSION:
			{
                // MCU etc. Vesion:18 Revesion:5
				// CMDPara[0] = MCU Version   CMDPara[1] = MCU Revesion   
                UserCommonEepromWrite(_OSD_MCU_VERSION_ADDRESS, 1, &CMDPara[0]);
			}
			break;
            
		case _DDCCI_ARM_MCU_READ_GAMMA_DATA:
            // u8 type;               ->CMDPara[0]  _CMD_MAX_MIN_CMD or _CMD_USER_LUT_CAL
            // u8 OsdStatus;          ->CMDPara[1]  OSD Off or On
            // u8 Percentage;         ->CMDPara[2]  
			{
                // Write: 0x6e 0x51 0x85 0xC2 0x44 0x00 0x01 0x20 CheckSum:0x  

                // USER_LUT_CAL GAMMA CMD:1C CMD:19 CMD:19 CMD:44 1 1 1% CMD:A ... CMD:44 0 1 64% ...  CMD:45
                //                                         CMD:44 1 1 1% CMD:A ... CMD:44 0 1 64% ...  CMD:45
                //                                         CMD:44 1 0 0  CMD:0
                // [2021-12-10 16:21:40.396]# RECV ASCII>  F-CMD: 44 1 0 0 
                // [2021-12-10 16:21:40.519]# RECV ASCII>  Show UI end 
                // [2021-12-10 16:21:40.917]# RECV ASCII>  F-CMD: 0 E_0: 1

                // USB Update FPGA GAMMA  CMD:19 CMD:19 CMD:44 1 1 1% CMD:A ... CMD:44 0 1 64% ...  CMD:45
                //                                      CMD:44 1 1 1% CMD:A ... CMD:44 0 1 64% ...  CMD:45
                //                                      CMD:44 0 0 0

                // USB Update Ref Gamma Data     CMD:46 CMD:44 0 1 0%  CMD:1C  CMD:44 0 1 14% CMD:A ... CMD:44 0 1 x%
                //                                      CMD:44 0 0 0
                
                if(CMDPara[2] <= 2) 
                {
                    DebugMessageUart("Para[0]:", CMDPara[0]);
                    DebugMessageUart("Para[1]:", CMDPara[1]);
                    DebugMessageUart("Para[2]:", CMDPara[2]);
                }

				if(CMDPara[1] == _OFF)
				{
		            //OsdDispDisableOsd();

	                UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, (BYTE)CMDPara[1]);

					if(CMDPara[0] == 1) // _CMD_USER_LUT_CAL
					{
                        DebugMessageUart("_CAL_LUT_end:", 0);

                        // UI Calibration Exit Must Clear Flag
                        g_bPCAppCalibrationFlag = _FALSE;

        				// Update Message
    	                if(GET_OSD_STATE() != _MENU_MESSAGE_DISPLAY)
	                    {
                            OsdDispHotKeyOptionMenu(_HOTKEY_USER_CALIBRATION_GAMMA);
	                    }

    		            OsdWindowSliderDisable();
                        OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(4));

                        // Check NSG to PS condition in display
                        if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
                        {
                            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                        }
                        else
                        {
                            UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, _ON);
                            
                            // Wait BK sensor to adjust the lux to the target lux value
    		            	ScalerTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_HANDLER); 
                            
            				// Update Message
                            OsdPropPutStringCenter(ROW(_WIN_HOTKEY_ITEM_ROW), COL(0), WIDTH(g_ucOsdWidth), _PFONT_PAGE_0, _STRING_Lumin_Processing_Do_Not_Operate, COLOR(_CP_WHITE, _MAIN_WIN_COLOR), GET_OSD_LANGUAGE());
            	            OsdPropShowNumberPercentage(ROW(_WIN_HOTKEY_ITEM_ROW + 3), COL(_WIN_HOTKEY_INFO_WIDTH - 2), 1, _FALSE, _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG));

                            if(abs(ReadBacklightSensorValue(0) - UserGetBacklightSensorTargetValue()) >= _BACKLIGHT_SENSOR_PRECISION*4)
                            {
                	            ScalerTimerReactiveTimerEvent(SEC(60), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
                    	        ScalerTimerReactiveTimerEvent(SEC(61), _USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE);
                            }                        
                            else
                            {
        			            ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_BACKLIGHT_SENSOR_SPEEDY_TIMER);
            		            ScalerTimerReactiveTimerEvent(SEC(6), _USER_TIMER_EVENT_CALIBRATION_LUX_COMPLETE);
                            }
                        }
					}
					else if(CMDPara[0] == 0) // _CMD_MAX_MIN_CMD
					{
                        // 0x00 0x00 ..
                        OsdDispDisableOsd();
                        
                        // Check NSG to PS condition in display
                        if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
                        {
                            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                        }
                        DebugMessageUart("_CAL_MAX_end:", 0);
					}
				}
				else if(CMDPara[1] == _ON)
				{
    				// USB Update FPGA_GAMMA.bin form 1% start
                    // 0x00 0x01 0x00
    				if(CMDPara[2] <= 1) 
				    {
                        DebugMessageUart("_MCU_Start:", CMDPara[1]);

    	                UserCommonNVRamSetSystemData(_SENSOR_CALIBRATION_MODE, (BYTE)CMDPara[1]);
    				    // 200ms
    	                if(GET_OSD_STATE() != _MENU_MESSAGE_DISPLAY)
	                    {
                            OsdDispHotKeyOptionMenu(_HOTKEY_USER_CALIBRATION_GAMMA);
	                    }
                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
				    }
                    else // Tip bar percentage
                    {
                        // 0x00 0x01 0x01~0x64
                        DebugMessageUart("_Percent:", CMDPara[2]);
                        if(GET_OSD_STATE() != _MENU_MESSAGE_DISPLAY)
	                    {
                            OsdDispHotKeyOptionMenu(_HOTKEY_USER_CALIBRATION_GAMMA);
	                    }
                        
                        if(CMDPara[2] > 100) 
                        {
                            CMDPara[2] = 99;
                        }
                        // 100ms
                        OsdWindowSlider(ROW(_WIN_HOTKEY_ITEM_ROW + 3), COL((_OSD_HOTKEY_MENU_WIDTH - _SLIDER_LENGHT/12)/2 - 2), CMDPara[2], _SLIDER_0, _SELECT);
                        OsdFuncClearOsd(ROW(_WIN_HOTKEY_ITEM_ROW + 3), COL(((_OSD_HOTKEY_MENU_WIDTH - _SLIDER_LENGHT/12)/2) + _SLIDER_LENGHT/12), WIDTH(4), HEIGHT(1));
        	            OsdPropShowNumberPercentage(ROW(_WIN_HOTKEY_ITEM_ROW + 3), COL(((_OSD_HOTKEY_MENU_WIDTH - _SLIDER_LENGHT/12)/2) + _SLIDER_LENGHT/12), CMDPara[2], _FALSE, _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG));
                    }
				}
			}
			break;		

       	case _DDCCI_ARM_MCU_GET_QA_CALI_DATA:
            // Write: 0x6e 0x51 0x82 0xC2 0x45 CheckSum:0x  
            // Read:  0x6e 0x8a 0xC2 0x45 00 17 70 02 58 05 01 f6 CheckSum:0x  
			{
				WORD usTemp_Buf[2];
                
				Cmd_Reply = 1;

	            g_pucDdcciTxBuf[0] = 0x6E;
	        	g_pucDdcciTxBuf[1] = (0x80|10);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _DDCCI_ARM_MCU_GET_QA_CALI_DATA;	// CMD
                        
				// From _CMD_USER_LUT_CAL
                RTDNVRamLoadUserLutData();
	        	g_pucDdcciTxBuf[4] = GET_OSD_LUT_USER_TYPE(); // GAMMA or DICOM
				
	        	usTemp_Buf[0] = GET_OSD_LUT_USER_L_MAX()*10;  // 600x10 = 0x1770
	        	usTemp_Buf[1] = GET_OSD_LUT_USER_L_MIN()*100;
	        	g_pucDdcciTxBuf[5] = (BYTE)((usTemp_Buf[0] & 0xff00)>>8);         
	        	g_pucDdcciTxBuf[6] = (BYTE)((usTemp_Buf[0] & 0x00ff));
	        	g_pucDdcciTxBuf[7] = (BYTE)((usTemp_Buf[1] & 0xff00)>>8);            
	        	g_pucDdcciTxBuf[8] = (BYTE)((usTemp_Buf[1] & 0x00ff));
				
	        	if(GET_OSD_LUT_USER_TYPE() == _LUT_USER_DICOM)
        		{
	        		g_pucDdcciTxBuf[9] = GET_OSD_LUT_USER_LAMB(); 
        		}
	        	else
        		{
	        		g_pucDdcciTxBuf[9] = GET_OSD_LUT_USER_VALUE(); 
        		}

				// From _DDCCI_GAMMA_ADJUST_GET_BK_SENSOR_TO_PANEL_LUX
				usTemp_Buf[0] = UserAdjustQAGetCurrPanelLux(_BK_SENSOR_MIDDLE); // 502cd/m2 = 0x1F6
                g_pucDdcciTxBuf[10] = (BYTE)(((WORD)usTemp_Buf[0] & 0xFF00)>> 8);
                g_pucDdcciTxBuf[11] = (BYTE)(((WORD)usTemp_Buf[0] & 0x00FF)>> 0);

	            g_pucDdcciTxBuf[12] = UserCommonDdcciCalCheckSum(); // checksum
	    	}
       		break;

       	case _DDCCI_ARM_MCU_GET_MAX_MIN_LUX:
            // Write: 0x6e 0x51 0x82 0xC2 0x46 CheckSum:0x  
            // Read:  0x6e 0x92 0xC2 0x46  48 d2 b7 e0  44 05 40 00  48 fd 4f e0  44 05 40 00 CheckSum:0x  max:431.551 min:0.533 max:518.783 min:0.533
			{
				DWORD ulLuxMax,ulLuxMin;

				Cmd_Reply = 1;

				g_pucDdcciTxBuf[0] = 0x6E;
				g_pucDdcciTxBuf[1] = (0x80|18);
        		g_pucDdcciTxBuf[2] = 0xc2;	// Prefix 0xC2
        		g_pucDdcciTxBuf[3] = _DDCCI_ARM_MCU_GET_MAX_MIN_LUX;	//CMD

				RTDNVRamLoadPanelLuxRangeData();
			    memcpy(&ulLuxMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMax,4);
				memcpy(&ulLuxMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_9300].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[4] = (BYTE)(((DWORD)ulLuxMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[5] = (BYTE)(((DWORD)ulLuxMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[6] = (BYTE)(((DWORD)ulLuxMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[7] = (BYTE)(((DWORD)ulLuxMax & 0x000000ff));
			    g_pucDdcciTxBuf[8] = (BYTE)(((DWORD)ulLuxMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[9] = (BYTE)(((DWORD)ulLuxMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[10] = (BYTE)(((DWORD)ulLuxMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[11] = (BYTE)(((DWORD)ulLuxMin & 0x000000ff));

			    memcpy(&ulLuxMax,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMax,4);
			    memcpy(&ulLuxMin,&g_stPanelLuxRangeData[_BK_SENSOR_CT_6500].ucRealLuxMin,4);
			    g_pucDdcciTxBuf[12] = (BYTE)(((DWORD)ulLuxMax & 0xff000000)>>24);
			    g_pucDdcciTxBuf[13] = (BYTE)(((DWORD)ulLuxMax & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[14] = (BYTE)(((DWORD)ulLuxMax & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[15] = (BYTE)(((DWORD)ulLuxMax & 0x000000ff));
			    g_pucDdcciTxBuf[16] = (BYTE)(((DWORD)ulLuxMin & 0xff000000)>>24);
			    g_pucDdcciTxBuf[17] = (BYTE)(((DWORD)ulLuxMin & 0x00ff0000)>>16);
			    g_pucDdcciTxBuf[18] = (BYTE)(((DWORD)ulLuxMin & 0x0000ff00)>>8);
			    g_pucDdcciTxBuf[19] = (BYTE)(((DWORD)ulLuxMin & 0x000000ff));

	            g_pucDdcciTxBuf[20] = UserCommonDdcciCalCheckSum(); // checksum

       		}
       		break;
#endif

		default:
			break;
			
	}

	if(Cmd_Reply == 1)
	{
        ScalerMcuDdcciSendData( g_pucDdcciTxBuf);
	} 

    if(CMDCode == _DDCCI_SENSOR_CALIB_GET_ORDER_STATUS)
    {
        //��ȡǰһ������״̬��������ֻ���ڣ�PC��MCUд����ʱ��ȡ)��
        //��ȷ��ǰһ�������������յ�����ǰһ���������У��
        //��ȷ����0x01,����ȷ����0x00
    }
    else if(CMDCode == _DDCCI_SENSOR_CALIB_SAVE_BACKLIGHT)
    {
        //BeaconMonitorManager3.25�����������¶�ȡǰһ������״̬�ļ��ʱ���ӳ���ִ����һ������ʱ���ӳ�
        //  ��ȡǰһ������״̬������0x00���ӳ�1�룬�����Ĵ�ÿ�ζ�������ʱ1�롣����ִ����֮���ӳ�2�룬ִ����һ������
        //���ȡǰһ������״̬������0x01���ӳ�3�롣ִ����һ������
        //������0x00��ȷ����ִ�б���Sensor����Ŀ��ֵ����ɺ�����״̬��0x01
        E_OrderStatus=1;
        if((E_OrderStatus == 0x00)&&(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SAVE_USER2_DATA) == _FALSE))
        {
            //��δִ�б���Sensor����Ŀ��ֵ����Ҫ��״̬��0x01����ͨѶ��ȡ״̬������
            E_OrderStatus=1;
        }
    }
    else
    {
        E_OrderStatus=1;
    }
    
}
#endif//#if (_BEACON_COLOR_SENSOR_CALIBRATION_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)
