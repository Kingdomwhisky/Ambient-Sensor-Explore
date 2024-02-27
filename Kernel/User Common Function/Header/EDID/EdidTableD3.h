//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))

#define _EDID_D3_TYPE_SEL                               _EDID_DVI_1680_1050_60HZ

#elif((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))

#if(_D3_HDMI_2_0_SUPPORT == _ON)

#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#define _EDID_D3_TYPE_SEL                               _EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420
#else
#define _EDID_D3_TYPE_SEL                               _EDID_HDMI_1920_1080_60HZ
#endif

#else
#define _EDID_D3_TYPE_SEL                               _EDID_HDMI_1920_1080_60HZ
#endif

#endif


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D3[] =
{
#if(_EDID_D3_TYPE_SEL == _EDID_DVI_1680_1050_60HZ)
#include "./EDID/EdidDvi/EDID_DVI_1680x1050@60.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_1920_1080_60HZ)
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080@60.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_1920_1080_60HZ_HDR)
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080@60_HDR.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_1920_1080_40HZ_75HZ_WITH_VSDB_FREESYNC)
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080_FREESYNC(40,75).h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_1920_1080_40HZ_120HZ_WITH_VSDB_FREESYNC)
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080_FREESYNC(40,120).h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_2560_1440_60HZ)
#include "./EDID/EdidHdmi/EDID_HDMI_2560x1440@60.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_2560_1440_60HZ_HDR)
#include "./EDID/EdidHdmi/EDID_HDMI_2560x1440@60_HDR.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_2560_1440_40HZ_70HZ_WITH_VSDB_FREESYNC)
#include "./EDID/EdidHdmi/EDID_HDMI_2560x1440_FREESYNC(40,70).h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI_3840_2160_30HZ)
#include "./EDID/EdidHdmi/EDID_HDMI_3840x2160@30.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_WITH_420)
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60_HFVSDB_WITH420.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420)
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60_HFVSDB.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_WITH_420_HDR)
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60_HFVSDB_WITH420_HDR.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420)
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60_WITH420.h"
#elif(_EDID_D3_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420)
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60.h"
#endif
};

#endif
