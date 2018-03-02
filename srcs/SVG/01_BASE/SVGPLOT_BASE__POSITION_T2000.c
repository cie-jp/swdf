/***************************************************************** 
 *
 * SVGPLOT BASE POSTION T2000
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_BASE.h"

REAL8 SVGPLOT_BASE__POSITION_T2000(REAL8 Vmin,
				   REAL8 Vmax,
				   T2000 tmin,
				   T2000 tmax,
				   T2000 t){
  REAL8 rV;

  rV = (REAL8)(t - tmin) / (REAL8)(tmax - tmin);

  return Vmin + (Vmax - Vmin) * rV;  
}
