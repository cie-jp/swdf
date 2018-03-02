/***************************************************************** 
 *
 * SVGPLOT TICS TEXT T
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"cdf.h"
#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__TEXT_T(SVG        *svg,
			  REAL8       Xmin,
			  REAL8       Xmax,
			  REAL8       Ymin,
			  REAL8       Ymax,
			  T2000       tmin,
			  T2000       tmax,
			  REAL8       offset0,
			  REAL8       offset1,
			  REAL8       offset2,
			  const CHAR *font_family,
			  REAL8       font_size,
			  SVG__STYLE  style){
  T2000 diff;
  INT4  dt;
  T2000 m  =    60000000000LL;
  T2000 h  =  3600000000000LL;
  T2000 d  = 86400000000000LL;
  
  diff = tmax - tmin;
  if(( 5 * m <= diff) && (diff < 10 * m)){
    dt =  1;
  }else 
  if((10 * m <= diff) && (diff < 18 * m)){
    dt =  2;
  }else 
  if((18 * m <= diff) && (diff < 30 * m)){
    dt =  3;
  }else 
  if((30 * m <= diff) && (diff <  1 * h)){
    dt =  5;
  }else 
  if(( 1 * h <= diff) && (diff <  2 * h)){
    dt = 10;
  }else 
  if(( 2 * h <= diff) && (diff <  3 * h)){
    dt = 20;
  }else 
  if(( 3 * h <= diff) && (diff <  6 * h)){
    dt = 30;
  }else 
  if(( 6 * h <= diff) && (diff < 12 * h)){
    dt =  1 * 60;
  }else 
  if((12 * h <= diff) && (diff <  1 * d)){
    dt =  2 * 60;
  }else 
  if(( 1 * d <= diff) && (diff <  2 * d)){
    dt =  4 * 60;
  }else 
  if(( 2 * d <= diff) && (diff <  4 * d)){
    dt =  8 * 60;
  }else 
  if(( 4 * d <= diff) && (diff <  6 * d)){
    dt = 12 * 60;
  }else 
  if(( 6 * d <= diff) && (diff < 12 * d)){
    dt =  1;
  }else 
  if((12 * d <= diff) && (diff < 24 * d)){
    dt =  2;
  }else 
  if((24 * d <= diff) && (diff < 48 * d)){
    dt =  5;
  }else 
  if((48 * d <= diff) && (diff < 96 * d)){
    dt = 10;
  }else{
    dt = 20;
  }
  
  if(diff < 6 * d){
    fprintf(stderr,"TIMESCALE diff = %lf[min] dt = %d[min]\n",(REAL8)diff / (REAL8)m,dt);
    SVGPLOT_TICS__TEXT_T_HHMM(svg,Xmin,Xmax,Ymin,Ymax,tmin,tmax,offset0,offset1,offset2,font_family,font_size,style,dt);
  }else{
    SVGPLOT_TICS__TEXT_T_DATE(svg,Xmin,Xmax,Ymin,Ymax,tmin,tmax,offset0,offset1,offset2,font_family,font_size,style,dt);
  }  
}
