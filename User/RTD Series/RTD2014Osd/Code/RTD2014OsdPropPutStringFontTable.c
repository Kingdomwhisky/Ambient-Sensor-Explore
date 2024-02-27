
#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Font Body Table
//--------------------------------------------------
#include "./TextTableBody/Rtd2014OsdTextTableBody_0.h"

#include "./TextTableBody/Rtd2014OsdTextTableBody_Chinese.h"

#include "./TextTableBody/Rtd2014OsdTextTableBody_FontTableDefine.h"

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD ucFontPoint)
{
    return *(tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage] + ucFontPoint);
}

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
