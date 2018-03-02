/***************************************************************** 
 *
 * SVGPLOT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/


#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include  <math.h>
#include"SVGPLOT.h"
#include   "cdf.h"

void SVGPLOT__XLABEL     (SVGPLOT    *plt,
			  const CHAR *xlabel_bottom,
			  const CHAR *xlabel_top){
  if(xlabel_bottom != NULL){
    SVG__TEXT(&plt->svg,
	      (plt->Xmin + plt->Xmax) / 2.0,plt->Ymin - plt->xlabeloffset,0.0,
	      xlabel_bottom,0,plt->xlabelfont_family,plt->xlabelfont_size,plt->xlabelstyle,1,1);
  }
  if(xlabel_top    != NULL){
    SVG__TEXT(&plt->svg,
	      (plt->Xmin + plt->Xmax) / 2.0,plt->Ymax + plt->xlabeloffset,0.0,
	      xlabel_top   ,0,plt->xlabelfont_family,plt->xlabelfont_size,plt->xlabelstyle,1,1);
  }    
}

void SVGPLOT__YLABEL     (SVGPLOT    *plt,
			  const CHAR *ylabel_left,
			  const CHAR *ylabel_right){
  if(ylabel_left  != NULL){
    SVG__TEXT(&plt->svg,
	      plt->Xmin - plt->ylabeloffset,(plt->Ymin + plt->Ymax) / 2.0,90.0,
	      ylabel_left ,0,plt->ylabelfont_family,plt->ylabelfont_size,plt->ylabelstyle,1,1);
  }
  if(ylabel_right != NULL){
    SVG__TEXT(&plt->svg,
	      plt->Xmax + plt->ylabeloffset,(plt->Ymin + plt->Ymax) / 2.0,90.0,
	      ylabel_right,0,plt->ylabelfont_family,plt->ylabelfont_size,plt->ylabelstyle,1,1);
  }
}

void SVGPLOT__ZLABEL     (SVGPLOT    *plt,
			  const CHAR *zlabel){
  SVG__TEXT(&plt->svg,
	    plt->Xmax + plt->cboffset + plt->cbwidth + plt->cblabeloffset,(plt->Ymin + plt->Ymax) / 2.0,270.0,
	    zlabel,0,plt->cblabelfont_family,plt->cblabelfont_size,plt->cblabelstyle,1,1);
}

void SVGPLOT__TITLE      (SVGPLOT    *plt,
			  const CHAR *title){
  SVG__TEXT(&plt->svg,
	    (plt->Xmin + plt->Xmax) / 2.0,plt->Ymax + plt->titleoffset,0.0,
	    title,0,plt->titlefont_family,plt->titlefont_size,plt->titlestyle,1,1);
}

void SVGPLOT__XY_LPLOT   (SVGPLOT    *plt,
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
  if(plt->xautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->xmin,&plt->xmax,x,num,plt->xscaletype);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
  }
  SVGPLOT_2D__XY_LINE(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,plt->ymin,plt->ymax,plt->yscaletype, 
		      x,y,num,xgap,ygap,lgap,mode,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin);
}

void SVGPLOT__TY_LPLOT   (SVGPLOT    *plt,
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
  if(plt->tautorange){
    SVGPLOT__AUTORANGE_TIME_TT2000      (&plt->tmin,&plt->tmax,t,num);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
  }
  SVGPLOT_2D__TY_LINE(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,plt->ymin,plt->ymax,plt->yscaletype, 
		      t,y,num,tgap,ygap,mode,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin);
}

void SVGPLOT__XY_IPLOT   (SVGPLOT    *plt,
			  REAL8       x[],
			  REAL8       y[],
			  INT4        num,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin){
  if(plt->xautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->xmin,&plt->xmax,x,num,plt->xscaletype);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
  }
  SVGPLOT_2D__XY_IMPULSE(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,plt->ymin,plt->ymax,plt->yscaletype, 
			 x,y,num,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin);
}

void SVGPLOT__TY_IPLOT   (SVGPLOT    *plt,
			  T2000       t[],
			  REAL8       y[],
			  INT4        num,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin){
  if(plt->tautorange){
    SVGPLOT__AUTORANGE_TIME_TT2000      (&plt->tmin,&plt->tmax,t,num);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
  }
  SVGPLOT_2D__TY_IMPULSE(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,plt->ymin,plt->ymax,plt->yscaletype, 
			 t,y,num,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin);
}

void SVGPLOT__XY_PPLOT   (SVGPLOT    *plt,
			  REAL8       x[],
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
  if(plt->xautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->xmin,&plt->xmax,x,num,plt->xscaletype);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
  }
  SVGPLOT_2D__XY_POINT(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,plt->ymin,plt->ymax,plt->yscaletype, 
		       x,y,num,pointsize,pointtype,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin,fill);
}

void SVGPLOT__TY_PPLOT   (SVGPLOT    *plt,
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
  if(plt->tautorange){
    SVGPLOT__AUTORANGE_TIME_TT2000      (&plt->tmin,&plt->tmax,t,num);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,num,plt->yscaletype);
  }
  SVGPLOT_2D__TY_POINT(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,plt->ymin,plt->ymax,plt->yscaletype, 
		       t,y,num,pointsize,pointtype,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin,fill);
}

void SVGPLOT__XYZ_CONTOUR(SVGPLOT    *plt,
			  REAL8       x[],
			  INT4        xnum,
			  REAL8       y[],
			  INT4        ynum,
			  REAL8       z[],
			  REAL8       xgap,
			  REAL8       ygap,
			  INT4        mode){
  if(plt->xautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->xmin,&plt->xmax,x,xnum,plt->xscaletype);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,ynum,plt->yscaletype);
  }
  if(plt->zautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->zmin,&plt->zmax,z,xnum * ynum,plt->zscaletype);
  }
  SVGPLOT_2D__XYZ_CONTOUR(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,plt->ymin,plt->ymax,plt->yscaletype,plt->zmin,plt->zmax,plt->zscaletype,x,xnum,y,ynum,z,xgap,ygap,mode,&plt->pal);
}

void SVGPLOT__TYZ_CONTOUR(SVGPLOT    *plt,
			  TIME_TT2000 t[],
			  INT4        tnum,
			  REAL8       y[],
			  INT4        ynum,
			  REAL8       z[],
			  T2000       tgap,
			  REAL8       ygap,
			  INT4        mode){
  if(plt->tautorange){
    SVGPLOT__AUTORANGE_TIME_TT2000      (&plt->tmin,&plt->tmax,t,tnum);
  }
  if(plt->yautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->ymin,&plt->ymax,y,ynum,plt->yscaletype);
  }
  if(plt->zautorange){
    SVGPLOT__AUTORANGE_REAL8      (&plt->zmin,&plt->zmax,z,tnum * ynum,plt->zscaletype);
  }

  SVGPLOT_2D__TYZ_CONTOUR(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,plt->ymin,plt->ymax,plt->yscaletype,plt->zmin,plt->zmax,plt->zscaletype,t,tnum,y,ynum,z,tgap,ygap,mode,&plt->pal);
}


void SVGPLOT__ADD_BY_DAT_XY (SVGPLOT    *plt,
			     REAL8       x[],
			     REAL8       y[],
			     INT4        num,
			     INT4        ptype,
			     const CHAR *legend){
  SVGPLOT_DATALIST__ADD_BY_DAT_XY(&plt->list,x,y,num,ptype,legend);
}

void SVGPLOT__ADD_BY_DAT_TY (SVGPLOT    *plt,
			     T2000       t[],
			     REAL8       y[],
			     INT4        num,
			     INT4        ptype,
			     const CHAR *legend){
  SVGPLOT_DATALIST__ADD_BY_DAT_TY(&plt->list,t,y,num,ptype,legend);
}

void SVGPLOT__ADD_BY_CSV_XY (SVGPLOT    *plt,
			     const CHAR *filename,
			     const CHAR *delimiters,
			     const CHAR *comment_chars,
			     INT4        x_idx,
			     INT4        y_idx,
			     INT4        ptype,
			     const CHAR *legend){
  SVGPLOT_DATALIST__ADD_BY_CSV_XY(&plt->list,filename,delimiters,comment_chars,x_idx,y_idx,ptype,legend);
}

void SVGPLOT__ADD_BY_CSV_TY (SVGPLOT    *plt,
			     const CHAR *filename,
			     const CHAR *delimiters,
			     const CHAR *comment_chars,
			     INT4        t_idx,
			     INT4        y_idx,
			     INT4        ptype,
			     const CHAR *legend){
  SVGPLOT_DATALIST__ADD_BY_CSV_TY(&plt->list,filename,delimiters,comment_chars,t_idx,y_idx,ptype,legend);
}

void SVGPLOT__PLOT          (SVGPLOT    *plt){
  const CHAR *lstroke;
  const CHAR *lstroke_width;
  const CHAR *lstroke_dasharray;
  REAL8       pointsize;
  INT4        pointtype;
  const CHAR *pstroke;
  const CHAR *pstroke_width;
  const CHAR *pstroke_dasharray;
  const CHAR *pfill;
  SVG_STYLE   style;
  REAL8       X1,X2,Y0;
  REAL8       xmin,xmax;
  REAL8       ymin,ymax;
  INT4        mode = 0;
  INT4        l;

  SVGPLOT_DATALIST__GET_RANGE_XY(&plt->list,&xmin,&xmax,&ymin,&ymax);
  if(plt->xautorange){
    SVGPLOT__SET_RANGE_X_003(plt,xmin,xmax);
  }
  if(plt->yautorange){
    SVGPLOT__SET_RANGE_Y_003(plt,ymin,ymax);			   
  }
  for(l = 0;l < plt->list.num;l++){    
    switch(l){
    case 0:
      if(mode == 0){
	lstroke           = "#FF2800";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#000000";
	lstroke_width     = "2.0px";
	lstroke_dasharray = NULL;
	pointsize         = 6.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 1:
      if(mode == 0){
	lstroke           = "#0041FF";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#606060";
	lstroke_width     = "2.0px";
	lstroke_dasharray = "4,4";
	pointsize         = 6.0;
	pointtype         = 1;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 2:
      if(mode == 0){
	lstroke           = "#35A16B";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#303030";
	lstroke_width     = "2.0px";
	lstroke_dasharray = "4,4";
	pointsize         = 6.0;
	pointtype         = 2;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 3:
      lstroke           = "#FF9900";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 4:
      lstroke           = "#66CCFF";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 5:
      lstroke           = "#FF99A0";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 6:
      lstroke           = "#9A0079";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 7:
      lstroke           = "#663300";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    default:
      lstroke           = "#000000";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
    }
    switch(plt->list.dat[l].ptype){
    case 0:
      SVGPLOT__XY_LPLOT(plt,plt->list.dat[l].x,plt->list.dat[l].y,plt->list.dat[l].xnum,-1.0,-1.0,-1.0,0,
			"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
      break;
    case 1:
      SVGPLOT__XY_PPLOT(plt,plt->list.dat[l].x,plt->list.dat[l].y,plt->list.dat[l].xnum,pointsize,pointtype,
			"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
      break;
    case 2:
      SVGPLOT__XY_LPLOT(plt,plt->list.dat[l].x,plt->list.dat[l].y,plt->list.dat[l].xnum,-1.0,-1.0,-1.0,0,
			"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
      SVGPLOT__XY_PPLOT(plt,plt->list.dat[l].x,plt->list.dat[l].y,plt->list.dat[l].xnum,pointsize,pointtype,
			"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
      break;
    case 3:
      SVGPLOT__XY_IPLOT(plt,plt->list.dat[l].x,plt->list.dat[l].y,plt->list.dat[l].xnum,
			"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
      break;
    }

    if(strlen(plt->list.dat[l].legend) == 0){
      continue;
    }

    // ====================================================
    // 凡例
    // ====================================================
    X1 = plt->Xmax + 20.0;
    X2 = X1        + 70.0;
    Y0 = plt->Ymax - plt->legendfont_size * (l + 1) * 1.5;

    SVG_STYLE__SET_001(style,"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round","none");
    SVG__LINE(&plt->svg,
	      X1,Y0,
	      X2,Y0,
	      style); 

    SVG_STYLE__SET_001(style,"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
    SVG__POINT(&plt->svg,(X1 + X2) / 2.0,Y0,pointsize,pointtype,style);

    SVG__TEXT(&plt->svg,
	      X2 + 20.0,Y0,0.0,
	      plt->list.dat[l].legend,0,plt->legendfont_family,plt->legendfont_size,plt->legendstyle,0,1);
  }

  SVGPLOT_DATALIST__FLUSH(&plt->list);  
}

void SVGPLOT__PLOT_TY          (SVGPLOT    *plt){
  const CHAR *lstroke;
  const CHAR *lstroke_width;
  const CHAR *lstroke_dasharray;
  REAL8       pointsize;
  INT4        pointtype;
  const CHAR *pstroke;
  const CHAR *pstroke_width;
  const CHAR *pstroke_dasharray;
  const CHAR *pfill;
  SVG_STYLE   style;
  REAL8       X1,X2,Y0;
  T2000       tmin,tmax;
  REAL8       ymin,ymax;
  INT4        mode = 0;
  INT4        l;

  SVGPLOT_DATALIST__GET_RANGE_TY(&plt->list,&tmin,&tmax,&ymin,&ymax);
  fprintf(stderr,"TIMESPAN %lld %lld\n",tmin,tmax);
  if(plt->tautorange){
    SVGPLOT__SET_RANGE_T_003(plt,tmin,tmax);
  }
  if(plt->yautorange){
    SVGPLOT__SET_RANGE_Y_003(plt,ymin,ymax);			   
  }
  for(l = 0;l < plt->list.num;l++){    
    switch(l){
    case 0:
      if(mode == 0){
	lstroke           = "#FF2800";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#000000";
	lstroke_width     = "2.0px";
	lstroke_dasharray = NULL;
	pointsize         = 6.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 1:
      if(mode == 0){
	lstroke           = "#0041FF";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#606060";
	lstroke_width     = "2.0px";
	lstroke_dasharray = "4,4";
	pointsize         = 6.0;
	pointtype         = 1;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 2:
      if(mode == 0){
	lstroke           = "#35A16B";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
      }else{
	lstroke           = "#303030";
	lstroke_width     = "2.0px";
	lstroke_dasharray = "4,4";
	pointsize         = 6.0;
	pointtype         = 2;
	pstroke           = lstroke;
	pstroke_width     = "2.0px";
	pstroke_dasharray = NULL;      
	pfill             = "#FFFFFF";
      }
      break;
    case 3:
      lstroke           = "#FF9900";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 4:
      lstroke           = "#66CCFF";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 5:
      lstroke           = "#FF99A0";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 6:
      lstroke           = "#9A0079";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    case 7:
      lstroke           = "#663300";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
      break;
    default:
      lstroke           = "#000000";
      lstroke_width     = "3.0px";
      lstroke_dasharray = NULL;
      pointsize         = 4.0;
      pointtype         = 0;
      pstroke           = lstroke;
      pstroke_width     = lstroke_width;
      pstroke_dasharray = NULL;      
      pfill             = pstroke;
    }
    switch(plt->list.dat[l].ptype){
    case 0:
      SVGPLOT__TY_LPLOT(plt,plt->list.dat[l].t,plt->list.dat[l].y,plt->list.dat[l].tnum,-1.0,-1.0,0,
			"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
      break;
    case 1:
      SVGPLOT__TY_PPLOT(plt,plt->list.dat[l].t,plt->list.dat[l].y,plt->list.dat[l].tnum,pointsize,pointtype,
			"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
      break;
    case 2:
      SVGPLOT__TY_LPLOT(plt,plt->list.dat[l].t,plt->list.dat[l].y,plt->list.dat[l].tnum,-1.0,-1.0,0,
			"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
      SVGPLOT__TY_PPLOT(plt,plt->list.dat[l].t,plt->list.dat[l].y,plt->list.dat[l].tnum,pointsize,pointtype,
			"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
      break;
    case 3:
      SVGPLOT__TY_IPLOT(plt,plt->list.dat[l].t,plt->list.dat[l].y,plt->list.dat[l].tnum,
			"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
      break;
    }

    if(strlen(plt->list.dat[l].legend) == 0){
      continue;
    }

    // ====================================================
    // 凡例
    // ====================================================
    X1 = plt->Xmax + 20.0;
    X2 = X1        + 70.0;
    Y0 = plt->Ymax - plt->legendfont_size * (l + 1) * 1.5;

    SVG_STYLE__SET_001(style,"1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round","none");
    SVG__LINE(&plt->svg,
	      X1,Y0,
	      X2,Y0,
	      style); 

    SVG_STYLE__SET_001(style,"1.0",pstroke,pstroke_width,pstroke_dasharray,NULL,"butt","butt",pfill);
    SVG__POINT(&plt->svg,(X1 + X2) / 2.0,Y0,pointsize,pointtype,style);

    SVG__TEXT(&plt->svg,
	      X2 + 20.0,Y0,0.0,
	      plt->list.dat[l].legend,0,plt->legendfont_family,plt->legendfont_size,plt->legendstyle,0,1);
  }

  SVGPLOT_DATALIST__FLUSH(&plt->list);  
}

