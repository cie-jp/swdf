/***************************************************************** 
 *
 * SVGPLOT DATA
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_DATA.h"

void SVGPLOT_DATA__INITIALIZE_XY        (SVGPLOT_DATA *dat,
					 INT4          num,
					 INT4          ptype,
					 const CHAR   *legend){
  void *buf;

  dat->xnum  = num;
  dat->tnum  =   0;
  dat->ynum  = num;
  dat->znum  =   0;
  dat->dtype =   0;
  if((buf = malloc(sizeof(REAL8) * dat->xnum + sizeof(REAL8) * dat->ynum)) == NULL){
    fprintf(stderr,"[ERROR : SVGPLOT_DATA__INITIALIZE_BY_DAT_XY]\n");
    exit(EXIT_FAILURE);
  }
  dat->x     = buf;
  dat->t     = NULL;
  dat->y     = (REAL8*)&dat->x[dat->xnum];
  dat->z     = NULL;
  dat->ptype = ptype;  
  if(legend == NULL){
    dat->legend[0] = '\0';
  }else{
    strcpy(dat->legend,legend);
  }
}

void SVGPLOT_DATA__INITIALIZE_TY        (SVGPLOT_DATA *dat,
					 INT4          num,
					 INT4          ptype,
					 const CHAR   *legend){
  void *buf;

  dat->xnum  =   0;
  dat->tnum  = num;
  dat->ynum  = num;
  dat->znum  =   0;
  dat->dtype =   1;
  if((buf = malloc(sizeof(T2000) * dat->tnum + sizeof(REAL8) * dat->ynum)) == NULL){
    fprintf(stderr,"[ERROR : SVGPLOT_DATA__INITIALIZE_DAT_TY]\n");
    exit(EXIT_FAILURE);
  }
  dat->x     = NULL;
  dat->t     = buf;
  dat->y     = (REAL8*)&dat->t[dat->tnum];
  dat->z     = NULL;
  dat->ptype = ptype;
  if(legend == NULL){
    dat->legend[0] = '\0';
  }else{
    strcpy(dat->legend,legend);
  }
}

void SVGPLOT_DATA__INITIALIZE_BY_DAT_XY (SVGPLOT_DATA *dat,
					 REAL8         x[],
					 REAL8         y[],
					 INT4          num,
					 INT4          ptype,
					 const CHAR   *legend){
  SVGPLOT_DATA__INITIALIZE_XY(dat,num,ptype,legend);
  memcpy(dat->x,x,sizeof(REAL8) * dat->xnum);
  memcpy(dat->y,y,sizeof(REAL8) * dat->ynum);
}

void SVGPLOT_DATA__INITIALIZE_BY_DAT_TY (SVGPLOT_DATA *dat,
					 T2000         t[],
					 REAL8         y[],
					 INT4          num,
					 INT4          ptype,
					 const CHAR   *legend){
  SVGPLOT_DATA__INITIALIZE_TY(dat,num,ptype,legend);
  memcpy(dat->t,t,sizeof(T2000) * dat->tnum);
  memcpy(dat->y,y,sizeof(REAL8) * dat->ynum);
}

void SVGPLOT_DATA__INITIALIZE_BY_CSV_XY (SVGPLOT_DATA *dat,
					 const CHAR   *filename,
					 const CHAR   *delimiters,
					 const CHAR   *comment_chars,
					 INT4          x_idx,
					 INT4          y_idx,
					 INT4          ptype,
					 const CHAR   *legend){
  FILE    *fp;
  TEXT_CSV csv;
  INT4     n;
  INT4     num;

  if((fp = fopen(filename,"rb")) == NULL){
    fprintf(stderr,"[ERROR : SVGPLOT_DATA__INITIALIZE_BY_CSV_XY]\n");    
    exit(EXIT_FAILURE);
  }
  num = TEXT_CSV__GET_NUM_ROWS(fp,comment_chars);
  SVGPLOT_DATA__INITIALIZE_XY(dat,num,ptype,legend);
  for(n = 0;n < num;n++){
    TEXT_CSV__READ_LINE(&csv,fp,delimiters,comment_chars);
    dat->x[n] = atof(TEXT_CSV__GET_DATA(&csv,x_idx));
    dat->y[n] = atof(TEXT_CSV__GET_DATA(&csv,y_idx));
  }  
}

void SVGPLOT_DATA__INITIALIZE_BY_CSV_TY (SVGPLOT_DATA *dat,
					 const CHAR   *filename,
					 const CHAR   *delimiters,
					 const CHAR   *comment_chars,
					 INT4          t_idx,
					 INT4          y_idx,
					 INT4          ptype,
					 const CHAR   *legend){
  FILE    *fp;
  TEXT_CSV csv;
  INT4     n;
  INT4     num;

  if((fp = fopen(filename,"rb")) == NULL){
    fprintf(stderr,"[ERROR : SVGPLOT_DATA__INITIALIZE_BY_CSV_XY]\n");    
    exit(EXIT_FAILURE);
  }
  num = TEXT_CSV__GET_NUM_ROWS(fp,comment_chars);
  SVGPLOT_DATA__INITIALIZE_TY(dat,num,ptype,legend);
  for(n = 0;n < num;n++){
    TEXT_CSV__READ_LINE(&csv,fp,delimiters,comment_chars);
    dat->t[n] = CDF_TT2000_from_UTC_string(TEXT_CSV__GET_DATA(&csv,t_idx));
    dat->y[n] = atof(TEXT_CSV__GET_DATA(&csv,y_idx));
  }  
}


void SVGPLOT_DATA__FINALIZE             (SVGPLOT_DATA *dat){
  if(dat->xnum <= 0){
    free(dat->x);
  }
  if(dat->tnum <= 0){
    free(dat->t);
  }
  if(dat->ynum <= 0){
    free(dat->y);
  }
  if(dat->znum <= 0){
    free(dat->z);
  }
}

INT4 SVGPLOT_DATA__GET_DATATYPE         (SVGPLOT_DATA *dat){
  return dat->dtype;
}

INT4 SVGPLOT_DATA__GET_PLOTTYPE         (SVGPLOT_DATA *dat){
  return dat->ptype;
}

void SVGPLOT_DATA__GET_RANGE_XY         (SVGPLOT_DATA *dat,
					 REAL8        *xmin,
					 REAL8        *xmax,
					 REAL8        *ymin,
					 REAL8        *ymax){
  *xmin = STATS__MIN(&dat->x[0],dat->xnum,0);
  *xmax = STATS__MAX(&dat->x[0],dat->xnum,0);
  *ymin = STATS__MIN(&dat->y[0],dat->ynum,0);
  *ymax = STATS__MAX(&dat->y[0],dat->ynum,0);
}

void SVGPLOT_DATA__GET_RANGE_TY         (SVGPLOT_DATA *dat,
					 T2000        *tmin,
					 T2000        *tmax,
					 REAL8        *ymin,
					 REAL8        *ymax){
  *tmin = STATS__MIN_T2000(&dat->t[0],dat->tnum);
  *tmax = STATS__MAX_T2000(&dat->t[0],dat->tnum);
  *ymin = STATS__MIN(&dat->y[0],dat->ynum,0);
  *ymax = STATS__MAX(&dat->y[0],dat->ynum,0);  
}

