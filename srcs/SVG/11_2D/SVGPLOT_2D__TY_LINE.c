/***************************************************************** 
 *
 * SVGPLOT 2D TY LINE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_2D.h"

void SVGPLOT_2D__TY_LINE   (SVG        *svg, 
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
			    T2000       tgap,
			    REAL8       ygap,
			    INT4        mode,
			    const CHAR *opacity,         
			    const CHAR *stroke,          
			    const CHAR *stroke_width,    
			    const CHAR *stroke_dasharray,
			    const CHAR *stroke_dashoffset,
			    const CHAR *stroke_linecap,  
			    const CHAR *stroke_linejoin){
  SVG_STYLE style;
  INT4      isinit;
  T2000     t1,t2,dt;
  REAL8     y1,y2,dy;
  REAL8     X1,X1clip;
  REAL8     Y1,Y1clip;
  REAL8     X2,X2clip;
  REAL8     Y2,Y2clip;
  INT4      status;
  INT4      n;

  SVG_STYLE__SET_001(style,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin,"none");

  fprintf(svg->fp,
	  "<g>\n");

  isinit = 0;
  for(n = 1;n < num;n++){
    t1 = t[n - 1];
    y1 = y[n - 1];
    t2 = t[n];
    y2 = y[n];
    dt = llabs(t2 - t1);
    dy =  fabs(y2 - y1);
    if((t1 == ILLEGAL_TT2000_VALUE) || 
       (t2 == ILLEGAL_TT2000_VALUE) || 
       isnan(y1) || isinf(y1) || 
       isnan(y2) || isinf(y2) ||
       ((yscaletype == 1) && ((y1 < DBL_MIN) || (y2 < DBL_MIN))) ||  
       ((tgap >=  0LL) && (dt > tgap)) || 
       ((ygap >= 0.00) && (dy > ygap)) ){
      if(isinit){
	fprintf(svg->fp,
		"\"/>\n");
	isinit = 0;
      }
      continue;
    }

    X1 = SVGPLOT_BASE__POSITION_T2000(Xmin,Xmax,tmin,tmax,t1);
    Y1 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y1);
    X2 = SVGPLOT_BASE__POSITION_T2000(Xmin,Xmax,tmin,tmax,t2);
    Y2 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y2);

    if(isnan(X1) || isinf(X1) || 
       isnan(X2) || isinf(X2) || 
       isnan(Y1) || isinf(Y1) || 
       isnan(Y2) || isinf(Y2) ){
      fprintf(stderr,"[ERROR : SVGPLOT_2D__TY_LINE] NaN or inf\n");
      exit(EXIT_FAILURE);
    }


    status = SVGPLOT_CHECK__LINE_CLIPPING(&X1clip,&Y1clip,&X2clip,&Y2clip,X1,Y1,X2,Y2,Xmin,Xmax,Ymin,Ymax);

    if((status == -1) || //INVALID
       (status ==  4) ){ //NO INTERSECTION
      continue;
    }
    if((status ==  2) || //OUT => IN
       (status ==  3) ){ //INTERSECTION
      if(isinit){
	fprintf(svg->fp,
		"\"/>\n");
	isinit = 0;
      }
    }
    if(!isinit){
      isinit = 1;
      fprintf(svg->fp,
	      "<path style=\"%s\" "
	      "d=\""
	      "M%lf,%lf L%lf,%lf",
	      style,
	      X1clip,svg->height - Y1clip,
	      X2clip,svg->height - Y2clip);
    }else{
      fprintf(svg->fp,
	      " %lf,%lf",
	      X2clip,svg->height - Y2clip);
    }
    if((status ==  1) || //IN  => OUT
       (status ==  3) ){ //INTERSECTION
      fprintf(svg->fp,
	      "\"/>\n");
      isinit = 0;
    }

  }

  if(isinit){
    fprintf(svg->fp,
	    "\"/>\n");
  }
  fprintf(svg->fp,
	  "</g>\n");
}
