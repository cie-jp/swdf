/*****************************************************************
 *
 * CDF操作関連ライブラリ
 *
 *    LPM共通 L1 z変数 D [REAL4型]
 *    各クラスの平均粒径
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable
// **********************************************

#define varName D
#define varType REAL4

#define numElems          1
#define numDims           1
#define dimSizes    {     22,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    NOVARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

#define FILLVAL      00
#define VALIDMIN     00
#define VALIDMAX     25
#define CATDESC      "grain diameter"
#define FIELDNAM     TSTR(varName)
#define VAR_TYPE     "support_data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
//#define MONOTON      "."
#define DEPEND_0     "epoch"
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
//#define DEPEND_0     "."
//#define DEPEND_1     "."
//#define DEPEND_2     "."
//#define DEPEND_3     "."
//#define FORMAT       "."
//#define FORM_PTR     "."
//#define DISPLAY_TYPE "."
#define SCALETYP     "linear"
#define LABLAXIS     TSTR(varName)
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
