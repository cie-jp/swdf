/***************************************************************** 
 *
 * SVGPLOT BASE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_BASE_H_INCLUDE_
#define _SVGPLOT_BASE_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"

  REAL8 SVGPLOT_BASE__POSITION_REAL8(REAL8 Vmin,
				     REAL8 Vmax,
				     REAL8 vmin,
				     REAL8 vmax,
				     INT4  vscaletype,
				     REAL8 val);

  REAL8 SVGPLOT_BASE__POSITION_T2000(REAL8 Vmin,
				     REAL8 Vmax,
				     T2000 tmin,
				     T2000 tmax,
				     T2000 t);
  
#ifdef __cplusplus
}
#endif

#endif
