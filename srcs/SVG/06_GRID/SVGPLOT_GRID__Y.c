/***************************************************************** 
 *
 * SVGPLOT GRID Y
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_GRID.h"

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
		     SVG_STYLE ygridstyle){
  REAL8 Y0;
  INT4  n;

  for(n = 0;n < ygridnum;n++){
    if((ygrid[n] <= ymin) || (ymax <= ygrid[n])){
      continue;
    }
    Y0 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,ygrid[n]);
    if(isnan(Y0) || isinf(Y0)){
      continue;
    }
    SVG__LINE(svg,Xmin,Y0,Xmax,Y0,ygridstyle);
  }
}
