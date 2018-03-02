/***************************************************************** 
 *
 * SVGPLOT TICS LINE Y
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__LINE_Y(SVG      *svg,
			  REAL8     Xmin,
			  REAL8     Xmax,
			  REAL8     Ymin,
			  REAL8     Ymax,
			  REAL8     ymin,
			  REAL8     ymax,		
			  INT4      yscaletype,
			  REAL8     ytics[],
			  INT4      yticsnum,
			  REAL8     yticslen,
			  SVG_STYLE yticsstyle,
			  INT4      mode){
  REAL8 Y0;
  INT4  n;

  if(mode == 0){
    return;
  }

  for(n = 0;n < yticsnum;n++){
    if((ytics[n] <= ymin) || (ymax <= ytics[n])){
      continue;
    }
    Y0 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,ytics[n]);
    if(isnan(Y0) || isinf(Y0)){
      continue;
    }
    if((mode == 1) || (mode == 3)){
      SVG__LINE(svg,Xmin,Y0,Xmin + yticslen,Y0,yticsstyle);
    }
    if((mode == 2) || (mode == 3)){
      SVG__LINE(svg,Xmax,Y0,Xmax - yticslen,Y0,yticsstyle);
    }
  }
}
