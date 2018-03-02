/*****************************************************************
 *
 * CDF Library
 *
 *  Ceilometer L1 zVariable back_scat [REAL8][770]
 *
 *  Created by Kota Makino (2017/10/15)
 *
 *****************************************************************/

#include"zVar_header.h"

// **********************************************
//  zVariable 
// **********************************************

#define varName back_scat
#define varType REAL8

#define numElems          1
#define numDims           1
#define dimSizes    {   770,     0,     0}
#define dimVarys    {  VARY,  VARY,  VARY}
#define recVariance    VARY

#define COMPRESS

// **********************************************
//  vAttribute (ISTP/IACG Guidelines)
// **********************************************

  #define FILLVAL              0
  #define VALIDMIN    -999999999
  #define VALIDMAX     999999999
  #define CATDESC      "Received backscatter coefficient"
  #define FIELDNAM     TSTR(varName)
  #define VAR_TYPE     "data"
  #define VAR_NOTES    "carry out the 1's complement plus 1 and normalization."
//#define DICT_KEY     "."
//#define MONOTON      "."
//#define UNITS        "."
//#define UNIT_PTR     "."
//#define UNITS_PTR    "."
  #define DEPEND_0     "epoch"
  #define DEPEND_1     "H"
//#define DEPEND_2     "V"
//#define DEPEND_3     "."
  #define FORMAT       "d9"
//#define FORM_PTR     "."
  #define DISPLAY_TYPE "spectrogram"
  #define SCALETYP     "log"
  #define LABLAXIS     "Backscatter coefficient"
//#define LABL_PTR_1   "."
//#define LABL_PTR_2   "."
//#define LABL_PTR_3   "."
//#define BUNDLE_1     "."

#include"zVar_footer.h"
