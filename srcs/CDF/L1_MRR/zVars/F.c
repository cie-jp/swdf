/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L1 z変数 F [UINT4型][32][64]
 *
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName F
#define varType UINT4

#define numElems          1
#define numDims           2
#define dimSizes    {    32,    64,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

#define COMPRESS

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL              0
  #define VALIDMIN             0
  #define VALIDMAX     999999999
  #define CATDESC      "Received spectral signal power"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
  #define VAR_NOTES    "include the receiver noise floor"
//#define DICT_KEY     "."
//#define MONOTON      "."
//#define UNITS        "."
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
  #define DEPEND_0     "epoch"
  #define DEPEND_1     "H"
  #define DEPEND_2     "V"
//#define DEPEND_3     "."
  #define FORMAT       "d9"
//#define FORM_PTR     "."
  #define DISPLAY_TYPE "spectrogram"
  #define SCALETYP     "linear"
  #define LABLAXIS     "Power"
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
