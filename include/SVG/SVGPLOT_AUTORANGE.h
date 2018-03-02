/***************************************************************** 
 *
 * SVGPLOT AUTORANGE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_AUTORANGE_H_INCLUDE_
#define _SVGPLOT_AUTORANGE_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"
#include"SVGPLOT_TICS.h"

void SVGPLOT__AUTORANGE_REAL8      (REAL8             *valmin,
				    REAL8             *valmax,
				    REAL8              val[],
				    INT4               num,
				    SVGPLOT__SCALETYPE scaletype);

void SVGPLOT__AUTORANGE_TIME_TT2000(TIME_TT2000       *valmin,
				    TIME_TT2000       *valmax,
				    TIME_TT2000        val[],
				    INT4               num);

#ifdef __cplusplus
}
#endif

#endif
