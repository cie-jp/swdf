/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L1 z変数 BW [UINT2型]
 *
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName BW
#define varType UINT2

#define numElems          1
#define numDims           0
#define dimSizes    {     0,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

#define COMPRESS

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL          0
  #define VALIDMIN         0
  #define VALIDMAX     50000
  #define CATDESC      "Band Width"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
  #define VAR_NOTES    "Band Width = constant"
//#define DICT_KEY     "."
//#define MONOTON      "."
  #define UNITS        "Hz"
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
  #define DEPEND_0     "epoch"
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