
/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    Parsivel共通 L2 z変数 E [REAL4型]
 *    降水種パラメーターE
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable
// **********************************************

#define varName E
#define varType REAL4

#define numElems          1
#define numDims           0
#define dimSizes    {     00,     00,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

#define FILLVAL      0.0
#define VALIDMIN     0.0
#define VALIDMAX     9999.999
#define CATDESC      "snow_type E"
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
#define SCALECAP     "linear"
#define LABLAXIS     TSTR(varName)
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"