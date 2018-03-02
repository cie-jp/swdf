/***************************************************************** 
 *
 * SVGPLOT GRID
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_GRID_H_INCLUDE_
#define _SVGPLOT_GRID_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"
#include"SVGPLOT_BASE.h"
  
  void SVGPLOT_GRID__X(SVG      *svg,
		       REAL8     Xmin,
		       REAL8     Xmax,
		       REAL8     Ymin,
		       REAL8     Ymax,
		       REAL8     xmin,
		       REAL8     xmax,
		       INT4      xscaletype,
		       REAL8     xgrid[],
		       INT4      xgridnum,
		       SVG_STYLE xgridstyle);
  
  void SVGPLOT_GRID__T(SVG      *svg,
		       REAL8     Xmin,
		       REAL8     Xmax,
		       REAL8     Ymin,
		       REAL8     Ymax,
		       T2000     tmin,
		       T2000     tmax,
		       T2000     tgrid[],
		       INT4      tgridnum,
		       SVG_STYLE tgridstyle);
  
  void SVGPLOT_GRID__Y(SVG      *svg,
		       REAL8     Xmin,
		       REAL8     Xmax,
		       REAL8     Ymin,
		       REAL8     Ymax,
		       REAL8     ymin,
		       REAL8     ymax,
		       INT4      yscaletype,
		       REAL8     ygrid[],
		       INT4      ygridnum,
		       SVG_STYLE ygridstyle);
  
#ifdef __cplusplus
}
#endif

#endif
