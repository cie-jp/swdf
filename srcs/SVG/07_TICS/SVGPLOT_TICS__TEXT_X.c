/***************************************************************** 
 *
 * SVGPLOT TICS TEXT X
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__TEXT_X(SVG        *svg,
			  REAL8       Xmin,
			  REAL8       Xmax,
			  REAL8       Ymin,
			  REAL8       Ymax,
			  REAL8       xmin,
			  REAL8       xmax,
			  INT4        xscaletype,
			  REAL8       x[],
			  INT4        xnum,
			  REAL8       offset,
			  const CHAR *font_family,
			  REAL8       font_size,
			  SVG_STYLE   style,
			  INT4        mode){
  INT4  shift;
  INT4  exponent;
  INT4  digitnumu;
  INT4  digitnuml;
  CHAR  text[2048];
  REAL8 X;
  INT4  n;

  if(mode == 0){
    return;
  }

  if(xscaletype == 0){
    SVGPLOT__GET_OPT_LINEAR_SCALE(&shift,&exponent,&digitnumu,&digitnuml,x,xnum);
  }

  for(n = 0;n < xnum;n++){
    if((x[n] <= xmin) || (xmax <= x[n])){
      continue;
    }
    if(xscaletype == 0){
      SVGPLOT__SET_TEXT_FROM_REAL8_LINEAR(text,x[n],shift,exponent,digitnumu,digitnuml);
    }else 
    if(xscaletype == 1){
      SVGPLOT__SET_TEXT_FROM_REAL8_LOG   (text,x[n]);
    }else{
      continue;
    }
    fprintf(stderr,"%30e %s\n",x[n],text);
    X = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,x[n]);
    if(isnan(X) || isinf(X)){
      continue;
    }
    if((mode == 1) || (mode == 3)){
      SVG__TEXT(svg,
		X,Ymin - offset,0.0,
		text,1,font_family,font_size,style,1,2);  
    }
    if((mode == 2) || (mode == 3)){
      SVG__TEXT(svg,
		X,Ymax + offset,0.0,
		text,1,font_family,font_size,style,1,0);  
    }
  }
}
