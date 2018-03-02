/*****************************************************************
 * 
 * CDF Library
 *
 *  Ceilometer L1 zVariable AWS [INT8]
 *
 *  Created by Kota Makino (2017/10/15)
 *
 *****************************************************************/ 

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName AWS
#define varType CHAR

#define numElems          1
#define numDims           1
#define dimSizes    {    12,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL          0
//#define VALIDMIN      "."
//#define VALIDMAX      "."
  #define CATDESC      "Alarm, Warning and internal Status"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
  #define VAR_NOTES    "Alarm(A), Warning(W), and internal status(S) information"
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
  #define SCALETYP     "linear"
  #define LABLAXIS     "Alarm, Warning and internal Status"
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
