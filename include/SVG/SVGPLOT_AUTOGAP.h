/***************************************************************** 
 *
 * SVGPLOT AUTOGAP
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_AUTOGAP_H_INCLUDE_
#define _SVGPLOT_AUTOGAP_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"

void SVGPLOT__AUTOGAP_REAL8      (REAL8 *valgap,
				  REAL8  val[],
				  INT4   num);

void SVGPLOT__AUTOGAP_TIME_TT2000(TIME_TT2000 *valgap,
				  TIME_TT2000  val[],
				  INT4         num);

#ifdef __cplusplus
}
#endif

#endif
