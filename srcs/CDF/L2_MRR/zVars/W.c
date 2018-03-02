/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L2 z変数 W [REAL4型][32]
 *
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName W
#define varType REAL4

#define numElems          1
#define numDims           1
#define dimSizes    {    32,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL              0.0
  #define VALIDMIN             0.0
  #define VALIDMAX     0.1887 * 63
  #define CATDESC      "W"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
//#define MONOTON      "."
  #define UNITS        "m/s"
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
  #define DEPEND_0     "epoch"
  #define DEPEND_1     "H"
  #define DEPEND_2     "V"
//#define DEPEND_3     "."
  #define FORMAT       "f9"
//#define FORM_PTR     "."
  #define DISPLAY_TYPE "spectrogram"
  #define SCALETYP     "linear"
  #define LABLAXIS     "W"
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
