/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    Parsivel共通 L1 z変数 firmware_DSP_version  [CHAR型]
 *    DSPのバージョン
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable
// **********************************************

#define varName firmware_DSP_version
#define varType CHAR

#define numElems          1
#define numDims           0
#define dimSizes    {     0,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

//#define FILLVAL      "."
//#define VALIDMIN     "."
//#define VALIDMAX     "."
#define CATDESC      "Firmware DSP version number"
#define FIELDNAM     TSTR(varName)
#define VAR_TYPE     "data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
//#define MONOTON      "."
//#define UNITS        "."
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
//#define DEPEND_0     "."
//#define DEPEND_1     "."
//#define DEPEND_2     "."
//#define DEPEND_3     "."
#define FORMAT       "2.02.3"
//#define FORM_PTR     "."
//#define DISPLAY_TYPE "."
//#define SCALECAP     "."
#define LABLAXIS     TSTR(varName)
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
