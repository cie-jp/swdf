/***************************************************************** 
 *
 * SVGPLOT TICS LINE T
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__LINE_T(SVG      *svg,
			  REAL8     Xmin,
			  REAL8     Xmax,
			  REAL8     Ymin,
			  REAL8     Ymax,
			  T2000     tmin,
			  T2000     tmax,
			  T2000     ttics[],
			  INT4      tticsnum,
			  REAL8     tticslen,
			  SVG_STYLE tticsstyle,
			  INT4      mode){
  REAL8 X0;
  INT4  n;

  for(n = 0;n < tticsnum;n++){
    if((ttics[n] <= tmin) || (tmax <= ttics[n])){
      continue;
    }
    X0 = SVGPLOT_BASE__POSITION_T2000(Xmin,Xmax,tmin,tmax,ttics[n]);
    if(isnan(X0) || isinf(X0)){
      continue;
    }
    if((mode == 1) || (mode == 3)){
      SVG__LINE(svg,X0,Ymin,X0,Ymin + tticslen,tticsstyle);
    }
    if((mode == 2) || (mode == 3)){
      SVG__LINE(svg,X0,Ymax,X0,Ymax - tticslen,tticsstyle);
    }
  }
}
