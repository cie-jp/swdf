/***************************************************************** 
 *
 * SVGPLOT 2D TY POINT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_2D.h"

void SVGPLOT_2D__TY_POINT  (SVG        *svg,         
			    REAL8       Xmin,        
			    REAL8       Xmax,        
			    REAL8       Ymin,        
			    REAL8       Ymax,        
			    T2000       tmin,        
			    T2000       tmax,        
			    REAL8       ymin,        
			    REAL8       ymax,        
			    INT4        yscaletype,  
			    T2000       t[],         
			    REAL8       y[],         
			    INT4        num,         
			    REAL8       pointsize,   
			    INT4        pointtype,   
			    const CHAR *opacity,          
			    const CHAR *stroke,           
			    const CHAR *stroke_width,			    
			    const CHAR *stroke_dasharray,
			    const CHAR *stroke_dashoffset,
			    const CHAR *stroke_linecap,   
			    const CHAR *stroke_linejoin,  
			    const CHAR *fill){
  SVG_STYLE style;
  REAL8     X0;
  REAL8     Y0;
  INT4      n;

  SVG_STYLE__SET_001(style,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin,fill);

  fprintf(svg->fp,
	  "<g>\n");

  for(n = 0;n < num;n++){
    if(((t[n] == ILLEGAL_TT2000_VALUE)  || (t[n] < tmin) || (tmax < t[n])) || 
       (isnan(y[n]) || isinf(y[n])      || (y[n] < ymin) || (ymax < y[n])) ){
      continue;
    }

    X0 = SVGPLOT_BASE__POSITION_T2000(Xmin,Xmax,tmin,tmax,t[n]);
    Y0 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y[n]);

    if(isnan(X0) || isinf(X0) || 
       isnan(Y0) || isinf(Y0) ){
      fprintf(stderr,"[ERROR : SVGPLOT_2D__XY_POINT] NaN or inf\n");
      exit(EXIT_FAILURE);
    }

    SVG__POINT(svg,X0,Y0,pointsize,pointtype,style);
  }

  fprintf(svg->fp,
	  "</g>\n");
}
