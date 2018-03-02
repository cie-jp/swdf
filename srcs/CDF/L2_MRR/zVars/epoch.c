/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L2 z変数 epoch [TIME_TT2000型]
 *
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName epoch
#define varType TIME_TT2000

#define numElems          1
#define numDims           0
#define dimSizes    {     0,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL      CDF_TT2000_from_UTC_parts(9999.0,12.0,31.0,23.0,59.0,59.0,999.0,999.0,999.0)
  #define VALIDMIN     CDF_TT2000_from_UTC_parts(1970.0, 1.0, 1.0, 0.0, 0.0, 0.0,  0.0,  0.0,  0.0)
  #define VALIDMAX     CDF_TT2000_from_UTC_parts(2029.0,12.0,31.0,23.0,59.0,59.0,999.0,999.0,999.0)
  #define CATDESC      "Default time"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "support_data"
//#define VAR_NOTES    "."
  #define DICT_KEY     "TIME > Epoch"
  #define MONOTON      "INCREASE"
//#define UNITS        "."
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
