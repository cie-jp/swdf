/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L2 z変数 H [UINT2型][32]
 *
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName H
#define varType UINT2

#define numElems          1
#define numDims           1
#define dimSizes    {    32,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance  NOVARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL          0
  #define VALIDMIN         0
  #define VALIDMAX      6000
  #define CATDESC      "Heights"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "support_data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
  #define MONOTON      "INCREASE"
  #define UNITS        "m"
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
  #define DEPEND_0     "epoch"
//#define DEPEND_1     "."
//#define DEPEND_2     "."
//#define DEPEND_3     "."
  #define FORMAT       "d9"
//#define FORM_PTR     "."
//#define DISPLAY_TYPE "."
  #define SCALETYP     "linear"
  #define LABLAXIS     "Height"
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
