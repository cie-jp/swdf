/***************************************************************** 
 *
 * SVGPLOT CHECK
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_CHECK_H_INCLUDE_
#define _SVGPLOT_CHECK_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"

  INT4  SVGPLOT_CHECK__OUT_OF_RANGE_1D(REAL8 val,
				       REAL8 min,
				       REAL8 max);
  
  INT4  SVGPLOT_CHECK__OUT_OF_RANGE_2D(REAL8 X,
				       REAL8 Y,
				       REAL8 Xmin,
				       REAL8 Xmax,
				       REAL8 Ymin,
				       REAL8 Ymax);
  
  INT4  SVGPLOT_CHECK__LINE_CLIPPING  (REAL8 *X1clip,
				       REAL8 *Y1clip,
				       REAL8 *X2clip,
				       REAL8 *Y2clip,
				       REAL8  X1,
				       REAL8  Y1,
				       REAL8  X2,
				       REAL8  Y2,
				       REAL8  Xmin,
				       REAL8  Xmax,
				       REAL8  Ymin,
				       REAL8  Ymax);
  
#ifdef __cplusplus
}
#endif

#endif
