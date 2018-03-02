/***************************************************************** 
 *
 * SVGPLOT BASE POSTION REAL8
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_BASE.h"

REAL8 SVGPLOT_BASE__POSITION_REAL8(REAL8 Vmin,
				   REAL8 Vmax,
				   REAL8 vmin,
				   REAL8 vmax,
				   INT4  vscaletype,
				   REAL8 val){
  REAL8 rV;

  switch(vscaletype){
  case 0:
    rV =    (val - vmin) /    (vmax - vmin);
    break;
  case 1:
    rV = log(val / vmin) / log(vmax / vmin);
    break;
  default:
    fprintf(stderr,"[WARNING : SVGPLOT_BASE__POSITION_REAL8] UNKNOWN SCALETYPE\n");
    exit(EXIT_FAILURE);
  }

  return Vmin + (Vmax - Vmin) * rV;  
}
