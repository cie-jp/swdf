/*****************************************************************
 *
 * CDF Library
 *
 *  Ceilometer L1 zVariable Parameter_SCALE [UINT4]
 *
 *  Created by Kota Makino (2017/10/15)
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName Parameter_SCALE
#define varType UINT4

#define numElems          1
#define numDims           0
#define dimSizes    {     0,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

#define COMPRESS

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL        0
  #define VALIDMIN       0
  #define VALIDMAX   99999
  #define CATDESC      "Parameter SCALE"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
  #define VAR_NOTES    "Parameter SCALE, 100 (%) is normal(0...99999 possible)"
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
  #define LABLAXIS     TSTR(varName)
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
