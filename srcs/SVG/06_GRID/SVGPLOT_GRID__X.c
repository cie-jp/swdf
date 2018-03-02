/***************************************************************** 
 *
 * SVGPLOT GRID X
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_GRID.h"

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
		     SVG_STYLE xgridstyle){  
  REAL8 X0;
  INT4  n;

  for(n = 0;n < xgridnum;n++){
    if((xgrid[n] <= xmin) || (xmax <= xgrid[n])){
      continue;
    }
    X0 = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,xgrid[n]);
    if(isnan(X0) || isinf(X0)){
      continue;
    }
    SVG__LINE(svg,X0,Ymin,X0,Ymax,xgridstyle);
  }
}
