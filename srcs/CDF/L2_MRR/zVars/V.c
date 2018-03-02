/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 * 
 *    MRR共通 L2 z変数 V [REAL4型][64]
 *
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName V
#define varType REAL4

#define numElems          1
#define numDims           1
#define dimSizes    {    64,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance  NOVARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL              0.0
  #define VALIDMIN             0.0
  #define VALIDMAX     63 * 0.1887
  #define CATDESC      "Velocities"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "support_data"
//#define VAR_NOTES    "."
//#define DICT_KEY     "."
//#define MONOTON      "."
  #define UNITS        "m/s"
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
  #define DEPEND_0     "epoch"
//#define DEPEND_1     "."
//#define DEPEND_2     "."
//#define DEPEND_3     "."
  #define FORMAT       "f7.4"
//#define FORM_PTR     "."
//#define DISPLAY_TYPE "."
  #define SCALETYP     "linear"
  #define LABLAXIS     "Velocity"
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
