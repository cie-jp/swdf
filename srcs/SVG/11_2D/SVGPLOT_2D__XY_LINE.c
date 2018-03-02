/***************************************************************** 
 *
 * SVGPLOT 2D XY LINE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_2D.h"

void SVGPLOT_2D__XY_LINE   (SVG        *svg,
			    REAL8       Xmin,
			    REAL8       Xmax,
			    REAL8       Ymin,
			    REAL8       Ymax,
			    REAL8       xmin,
			    REAL8       xmax,
			    INT4        xscaletype,
			    REAL8       ymin,
			    REAL8       ymax,
			    INT4        yscaletype,
			    REAL8       x[],
			    REAL8       y[],
			    INT4        num,
			    REAL8       xgap,
			    REAL8       ygap,
			    REAL8       lgap,
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
  REAL8     x1,x2,dx;
  REAL8     y1,y2,dy;
  REAL8     dl;
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
    x1 = x[n - 1];
    y1 = y[n - 1];
    x2 = x[n];
    y2 = y[n];
    dx = fabs(x2 - x1);
    dy = fabs(y2 - y1);
    dl = sqrt(dx * dx + dy * dy);
    if(isnan(x1) || isinf(x1) || 
       isnan(x2) || isinf(x2) || 
       isnan(y1) || isinf(y1) || 
       isnan(y2) || isinf(y2) ||
       ((xscaletype == 1) && ((x1 < DBL_MIN) || (x2 < DBL_MIN))) || 
       ((yscaletype == 1) && ((y1 < DBL_MIN) || (y2 < DBL_MIN))) ||  
       ((xgap >= 0.0) && (dx > xgap)) || 
       ((ygap >= 0.0) && (dy > ygap)) ||
       ((lgap >= 0.0) && (dl > lgap)) ){
      if(isinit){
	fprintf(svg->fp,
		"\"/>\n");
	isinit = 0;
      }
      continue;
    }

    X1 = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,x1);
    Y1 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y1);
    X2 = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,x2);
    Y2 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y2);

    if(isnan(X1) || isinf(X1) || 
       isnan(X2) || isinf(X2) || 
       isnan(Y1) || isinf(Y1) || 
       isnan(Y2) || isinf(Y2) ){
      fprintf(stderr,"[ERROR : SVGPLOT_2D__XY_LINE] NaN or inf\n");
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
      if(mode == 1){
	continue;
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
