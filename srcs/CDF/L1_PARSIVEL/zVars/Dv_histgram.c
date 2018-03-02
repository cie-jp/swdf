/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    Parsivel共通 L1 z変数 Dv_histgram   [UINT2型][32][32]
 *    生データ
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable
// **********************************************

#define varName Dv_histgram
#define varType UINT2

#define numElems          1
#define numDims           2
#define dimSizes    {    32,    32,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

#define FILLVAL      0
#define VALIDMIN     0
#define VALIDMAX     999
#define CATDESC      "raw data"
#define FIELDNAM     TSTR(varName)
#define VAR_TYPE     "data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
//#define MONOTON      "."
//#define UNITS        "."
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
#define DEPEND_0     "epoch"
#define DEPEND_1     "D"
#define DEPEND_2     "v"
//#define DEPEND_3     "."
//#define FORMAT       "."
//#define FORM_PTR     "."
//#define DISPLAY_TYPE "."
#define SCALECAP     "linear"
#define LABLAXIS     TSTR(varName)
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
