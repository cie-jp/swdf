/***************************************************************** 
 *
 * SVGPLOT GRID T
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_GRID.h"

void SVGPLOT_GRID__T(SVG      *svg,
		     REAL8     Xmin,
		     REAL8     Xmax,
		     REAL8     Ymin,
		     REAL8     Ymax,
		     T2000     tmin,
		     T2000     tmax,
		     T2000     tgrid[],
		     INT4      tgridnum,
		     SVG_STYLE tgridstyle){
  REAL8 X0;
  INT4  n;

  for(n = 0;n < tgridnum;n++){
    if((tgrid[n] <= tmin) || (tmax <= tgrid[n])){
      continue;
    }
    X0 = SVGPLOT_BASE__POSITION_T2000(Xmin,Xmax,tmin,tmax,tgrid[n]);
    if(isnan(X0) || isinf(X0)){
      continue;
    }
    SVG__LINE(svg,X0,Ymin,X0,Ymax,tgridstyle);
  }  
}
