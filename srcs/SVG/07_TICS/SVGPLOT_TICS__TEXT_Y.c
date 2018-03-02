/***************************************************************** 
 *
 * SVGPLOT TICS TEXT Y
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__TEXT_Y(SVG        *svg,
			  REAL8       Xmin,
			  REAL8       Xmax,
			  REAL8       Ymin,
			  REAL8       Ymax,
			  REAL8       ymin,
			  REAL8       ymax,
			  INT4        yscaletype,
			  REAL8       y[],
			  INT4        ynum,
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
  REAL8 Y;
  INT4  n;

  if(mode == 0){
    return;
  }

  if(yscaletype == 0){
    SVGPLOT__GET_OPT_LINEAR_SCALE(&shift,&exponent,&digitnumu,&digitnuml,y,ynum);
  }

  for(n = 0;n < ynum;n++){
    if((y[n] <= ymin) || (ymax <= y[n])){
      continue;
    }
    if(yscaletype == 0){
      SVGPLOT__SET_TEXT_FROM_REAL8_LINEAR(text,y[n],shift,exponent,digitnumu,digitnuml);
    }else 
    if(yscaletype == 1){
      SVGPLOT__SET_TEXT_FROM_REAL8_LOG   (text,y[n]);
    }else{
      continue;
    }
    fprintf(stderr,"%30e %s\n",y[n],text);
    Y = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y[n]);
    if(isnan(Y) || isinf(Y)){
      continue;
    }
    if((mode == 1) || (mode == 3)){
      SVG__TEXT(svg,
		Xmin - offset,Y,0.0,
		text,1,font_family,font_size,style,2,1);  
    }
    if((mode == 2) || (mode == 3)){
      SVG__TEXT(svg,
		Xmax + offset,Y,0.0,
		text,1,font_family,font_size,style,0,1);  
    }
  }
}
