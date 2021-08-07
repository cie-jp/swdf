/*****************************************************************
 *
 * CDF Library
 *
 *  Ceilometer L1 zVariable measurement_params [CHAR][9]
 *
 *  Created by Kota Makino (2017/10/15)
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName measurement_params
#define varType CHAR

#define numElems          1
#define numDims           1
#define dimSizes    {     9,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL          0
//#define VALIDMIN         0
//#define VALIDMAX         0
  #define CATDESC      "Measurement parameters"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
  #define VAR_NOTES    " Measurement parameters \
                         (pulse Long/Short, pulse qty0112x1024,\
                         gain High/Low, bandwidth Narrow/Wide,\
                         sampling 15/30 MHz)"
//#define DICT_KEY     "."
//#define MONOTON      "."
//#define UNITS        "m"
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