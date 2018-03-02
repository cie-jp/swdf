/***************************************************************** 
 *
 * SVGPLOT SET RANGE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__SET_RANGE_X_001(SVGPLOT    *plt){
  plt->xautorange = 1;
  plt->xmin       = 0.1;
  plt->xmax       = 1.0;
}

void SVGPLOT__SET_RANGE_X_002(SVGPLOT    *plt,
			      REAL8       x[],
			      INT4        num){
  plt->xautorange = 0;
  SVGPLOT__AUTORANGE_REAL8(&plt->xmin,&plt->xmax,x,num,plt->xscaletype);
}

void SVGPLOT__SET_RANGE_X_003(SVGPLOT    *plt,
			      REAL8       xmin,
			      REAL8       xmax){
  plt->xautorange = 0;
  plt->xmin       = xmin;
  plt->xmax       = xmax;
}

void SVGPLOT__SET_RANGE_T_001(SVGPLOT    *plt){
  plt->tautorange = 1;
  plt->tmin       = 0LL;
  plt->tmax       = 1LL;
}

void SVGPLOT__SET_RANGE_T_002(SVGPLOT    *plt,
			      TIME_TT2000 t[],
			      INT4        num){
  plt->tautorange = 0;
  SVGPLOT__AUTORANGE_TIME_TT2000(&plt->tmin,&plt->tmax,t,num);
}

void SVGPLOT__SET_RANGE_T_003(SVGPLOT    *plt,
			      TIME_TT2000 tmin,
			      TIME_TT2000 tmax){
  plt->tautorange = 0;
  plt->tmin       = tmin;
  plt->tmax       = tmax;  
}

void SVGPLOT__SET_RANGE_Y_001(SVGPLOT    *plt){
  plt->yautorange = 1;
  plt->ymin       = 0.1;
  plt->ymax       = 1.0;
}

void SVGPLOT__SET_RANGE_Y_002(SVGPLOT    *plt,
			      REAL8       y[],
			      INT4        num){
  plt->yautorange = 0;
  SVGPLOT__AUTORANGE_REAL8(&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
}

void SVGPLOT__SET_RANGE_Y_003(SVGPLOT    *plt,
			      REAL8       ymin,
			      REAL8       ymax){
  plt->yautorange = 0;
  plt->ymin       = ymin;
  plt->ymax       = ymax;    
}

void SVGPLOT__SET_RANGE_Z_001(SVGPLOT    *plt){
  plt->zautorange = 1;
  plt->zmin       = 0.1;
  plt->zmax       = 1.0;
}

void SVGPLOT__SET_RANGE_Z_002(SVGPLOT    *plt,
			      REAL8       z[],
			      INT4        num){
  plt->zautorange = 0;
  SVGPLOT__AUTORANGE_REAL8(&plt->zmin,&plt->zmax,z,num,plt->zscaletype);
}

void SVGPLOT__SET_RANGE_Z_003(SVGPLOT    *plt,
			      REAL8       zmin,
			      REAL8       zmax){
  plt->zautorange = 0;
  plt->zmin       = zmin;
  plt->zmax       = zmax;    
}
