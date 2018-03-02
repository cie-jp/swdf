/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    Parsivel共通 L1 z変数 weathercode_rain [INT2型]
 *    天気コード(SYNOP Table4680)
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable
// **********************************************

#define varName weathercode_rain
#define varType INT2

#define numElems          1
#define numDims           0
#define dimSizes    {     0,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

#define FILLVAL       0
#define VALIDMIN     -3
#define VALIDMAX     +3
#define CATDESC      "Weather code rain (0 : NP | +1 : RA | +2 : RADZ | +3 : DZ | -1 : RASN | -2 : GS | -3 : Other)"
#define FIELDNAM     TSTR(varName)
#define VAR_TYPE     "data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
//#define MONOTON      "."
//#define UNITS        "."
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
#define DEPEND_0     "epoch"
//#define DEPEND_1     "."
//#define DEPEND_2     "."
//#define DEPEND_3     "."
//#define FORMAT       "."
//#define FORM_PTR     "."
//#define DISPLAY_TYPE "."
//#define SCALETYP     "."
#define LABLAXIS     TSTR(varName)
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#define SCALEMIN     -4
#define SCALEMAX     +4

#include"zVar_footer.h"
