/***************************************************************** 
 *
 * SVGPLOT TICS LINE X
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__LINE_X(SVG      *svg,
			  REAL8     Xmin,
			  REAL8     Xmax,
			  REAL8     Ymin,
			  REAL8     Ymax,
			  REAL8     xmin,
			  REAL8     xmax,
			  INT4      xscaletype,
			  REAL8     xtics[],
			  INT4      xticsnum,
			  REAL8     xticslen,
			  SVG_STYLE xticsstyle,
			  INT4      mode){
  REAL8 X0;
  INT4  n;

  if(mode == 0){
    return;
  }

  for(n = 0;n < xticsnum;n++){    
    if((xtics[n] <= xmin) || (xmax <= xtics[n])){
      continue;
    }
    X0 = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,xtics[n]);
    if(isnan(X0) || isinf(X0)){
      continue;
    }
    if((mode == 1) || (mode == 3)){
      SVG__LINE(svg,X0,Ymin,X0,Ymin + xticslen,xticsstyle);
    }
    if((mode == 2) || (mode == 3)){
      SVG__LINE(svg,X0,Ymax,X0,Ymax - xticslen,xticsstyle);
    }
  }
}
