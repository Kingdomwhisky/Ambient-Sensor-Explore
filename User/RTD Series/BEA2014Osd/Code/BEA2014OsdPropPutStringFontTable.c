
#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_2014_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Font Body Table
//--------------------------------------------------
#include "./TextTableBody/BEA2014OsdTextTableBody_0.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_English.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_French.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_German.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Spanish.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Portuguese.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Italian.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Swedish.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Polish.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Russian.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Japanese.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Chinese.h"

#include "./TextTableBody/BEA2014OsdTextTableBody_Arabic.h"


#include "./TextTableBody/BEA2014OsdTextTableBody_FontTableDefine.h"

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD usFontPoint)
{
    return *(tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage] + usFontPoint);
}
#endif // End of #if(_OSD_TYPE == _BEACON_2014_OSD)

