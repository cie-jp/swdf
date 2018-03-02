/***************************************************************** 
 *
 * SVGPLOT DATALIST
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_DATALIST.h"

void SVGPLOT_DATALIST__INITIALIZE    (SVGPLOT_DATALIST *list){
  list->num = 0;
}

void SVGPLOT_DATALIST__FINALIZE      (SVGPLOT_DATALIST *list){
  INT4 n;
  
  for(n = 0;n < list->num;n++){
    SVGPLOT_DATA__FINALIZE(&list->dat[n]);
  }
}

void SVGPLOT_DATALIST__ADD_BY_DAT_XY (SVGPLOT_DATALIST *list,
				      REAL8             x[],
				      REAL8             y[],
				      INT4              num,
				      INT4              ptype,
				      const CHAR       *legend){
  if(list->num >= SVGPLOT_DATALIST__MAXNUM){
    fprintf(stderr,"[ERROR : SVGPLOT_DATALIST__ADD_BY_DAT_XY]\n");
    exit(EXIT_FAILURE);
  }
  SVGPLOT_DATA__INITIALIZE_BY_DAT_XY(&list->dat[list->num],x,y,num,ptype,legend);
  list->num++;
}

void SVGPLOT_DATALIST__ADD_BY_DAT_TY (SVGPLOT_DATALIST *list,
				      T2000             t[],
				      REAL8             y[],
				      INT4              num,
				      INT4              ptype,
				      const CHAR       *legend){
  if(list->num >= SVGPLOT_DATALIST__MAXNUM){
    fprintf(stderr,"[ERROR : SVGPLOT_DATALIST__ADD_BY_DAT_TY]\n");
    exit(EXIT_FAILURE);
  }
  SVGPLOT_DATA__INITIALIZE_BY_DAT_TY(&list->dat[list->num],t,y,num,ptype,legend);
  list->num++;
}

void SVGPLOT_DATALIST__ADD_BY_CSV_XY (SVGPLOT_DATALIST *list,
				      const CHAR       *filename,
				      const CHAR       *delimiters,
				      const CHAR       *comment_chars,
				      INT4              x_idx,
				      INT4              y_idx,
				      INT4              ptype,
				      const CHAR       *legend){
  if(list->num >= SVGPLOT_DATALIST__MAXNUM){
    fprintf(stderr,"[ERROR : SVGPLOT_DATALIST__ADD_BY_CSV_XY]\n");
    exit(EXIT_FAILURE);
  }  
  SVGPLOT_DATA__INITIALIZE_BY_CSV_XY(&list->dat[list->num],filename,delimiters,comment_chars,x_idx,y_idx,ptype,legend);
  list->num++;
}

void SVGPLOT_DATALIST__ADD_BY_CSV_TY (SVGPLOT_DATALIST *list,
				      const CHAR       *filename,
				      const CHAR       *delimiters,
				      const CHAR       *comment_chars,
				      INT4              t_idx,
				      INT4              y_idx,
				      INT4              ptype,
				      const CHAR       *legend){
  if(list->num >= SVGPLOT_DATALIST__MAXNUM){
    fprintf(stderr,"[ERROR : SVGPLOT_DATALIST__ADD_BY_CSV_TY]\n");
    exit(EXIT_FAILURE);
  }  
  SVGPLOT_DATA__INITIALIZE_BY_CSV_TY(&list->dat[list->num],filename,delimiters,comment_chars,t_idx,y_idx,ptype,legend);
  list->num++;  
}

void SVGPLOT_DATALIST__FLUSH         (SVGPLOT_DATALIST *list){
  SVGPLOT_DATALIST__FINALIZE  (list);
  SVGPLOT_DATALIST__INITIALIZE(list);
}

void SVGPLOT_DATALIST__GET_RANGE_XY  (SVGPLOT_DATALIST *list,
				      REAL8            *xmin,
				      REAL8            *xmax,
				      REAL8            *ymin,
				      REAL8            *ymax){
  INT4  isinit;
  INT4  n;
  REAL8 xmin_tmp,xmax_tmp;
  REAL8 ymin_tmp,ymax_tmp;
  REAL8 xmin_min = 0.0;
  REAL8 xmax_max = 0.0;
  REAL8 ymin_min = 0.0;
  REAL8 ymax_max = 0.0;

  isinit = 0;
  for(n = 0;n < list->num;n++){
    SVGPLOT_DATA__GET_RANGE_XY(&list->dat[n],&xmin_tmp,&xmax_tmp,&ymin_tmp,&ymax_tmp);
    if(!isinit){
      xmin_min = xmin_tmp;
      xmax_max = xmax_tmp;
      ymin_min = ymin_tmp;
      ymax_max = ymax_tmp;
      isinit = 1;
    }else{
      if(xmin_min > xmin_tmp){
	xmin_min = xmin_tmp;
      }
      if(xmax_max < xmax_tmp){
	xmax_max = xmax_tmp;
      }
      if(ymin_min > ymin_tmp){
	ymin_min = ymin_tmp;
      }
      if(ymax_max < ymax_tmp){
	ymax_max = ymax_tmp;
      }
    }
  }
  *xmin = xmin_min;
  *xmax = xmax_max;
  *ymin = ymin_min;
  *ymax = ymax_max;
}

void SVGPLOT_DATALIST__GET_RANGE_TY  (SVGPLOT_DATALIST *list,
				      T2000            *tmin,
				      T2000            *tmax,
				      REAL8            *ymin,
				      REAL8            *ymax){
  INT4  isinit;
  INT4  n;
  T2000 tmin_tmp,tmax_tmp;
  REAL8 ymin_tmp,ymax_tmp;
  T2000 tmin_min = ILLEGAL_TT2000_VALUE;
  T2000 tmax_max = ILLEGAL_TT2000_VALUE;
  REAL8 ymin_min = 0.0;
  REAL8 ymax_max = 0.0;

  isinit = 0;
  for(n = 0;n < list->num;n++){
    SVGPLOT_DATA__GET_RANGE_TY(&list->dat[n],&tmin_tmp,&tmax_tmp,&ymin_tmp,&ymax_tmp);
    if(!isinit){
      tmin_min = tmin_tmp;
      tmax_max = tmax_tmp;
      ymin_min = ymin_tmp;
      ymax_max = ymax_tmp;
      isinit = 1;
    }else{
      if(tmin_min > tmin_tmp){
	tmin_min = tmin_tmp;
      }
      if(tmax_max < tmax_tmp){
	tmax_max = tmax_tmp;
      }
      if(ymin_min > ymin_tmp){
	ymin_min = ymin_tmp;
      }
      if(ymax_max < ymax_tmp){
	ymax_max = ymax_tmp;
      }
    }
  }
  *tmin = tmin_min;
  *tmax = tmax_max;
  *ymin = ymin_min;
  *ymax = ymax_max;
}

