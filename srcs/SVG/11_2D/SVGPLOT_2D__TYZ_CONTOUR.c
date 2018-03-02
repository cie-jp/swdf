/***************************************************************** 
 *
 * SVGPLOT 2D TYZ CONTOUR
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_2D.h"

void SVGPLOT__CONTOUR_IMAGE2_TIME(IMAGE              img,
				  INT4               imgwidth,
				  INT4               imgheight,
				  SVGPLOT_PALETTE   *pal,		      
				  T2000        tmin,
				  T2000        tmax,
				  T2000        tgap,
				  REAL8              ymin,
				  REAL8              ymax,
				  REAL8              ygap,//[ygap < 0] => ギャップなし
				  REAL8              zmin,
				  REAL8              zmax,
				  T2000        t[], //t[k]
				  INT4               tnum,
				  REAL8              y[], //y[l]
				  INT4               ynum,
				  REAL8              z[], //z[k * ynum + l]
				  INT4 yscaletype,
				  INT4 zscaletype);

void SVGPLOT_2D__TYZ_CONTOUR(SVG             *svg,
			     REAL8            Xmin,
			     REAL8            Xmax,
			     REAL8            Ymin,
			     REAL8            Ymax,
			     T2000            tmin,
			     T2000            tmax,
			     REAL8            ymin,
			     REAL8            ymax,
			     INT4             yscaletype,
			     REAL8            zmin,
			     REAL8            zmax,
			     INT4             zscaletype,
			     T2000            t[], //t[k]
			     INT4             tnum,
			     REAL8            y[], //y[l]
			     INT4             ynum,
			     REAL8            z[], //z[k * ynum + l]
			     T2000            tgap,
			     REAL8            ygap,
			     INT4             mode,
			     SVGPLOT_PALETTE *pal){
  INT4  imgwidth;
  INT4  imgheight;
  IMAGE img;

  imgwidth  = (INT4)fabs(Xmax - Xmin) + 1; 
  imgheight = (INT4)fabs(Ymax - Ymin) + 1;

  if((img = (IMAGE)malloc(sizeof(RGBA) * imgwidth * imgheight)) == NULL){
    exit(EXIT_FAILURE);
  }
  if(mode == 0){
    SVGPLOT__CONTOUR_IMAGE_TIME(img,imgwidth,imgheight,pal,
				tmin,tmax,tgap,
				ymin,ymax,ygap,
				zmin,zmax,t,tnum,y,ynum,z,
				yscaletype,
				zscaletype);
  }else{
    SVGPLOT__CONTOUR_IMAGE2_TIME(img,imgwidth,imgheight,pal,
				 tmin,tmax,tgap,
				 ymin,ymax,ygap,
				 zmin,zmax,t,tnum,y,ynum,z,
				 yscaletype,
				 zscaletype);
  }
  SVG__IMAGE2(svg,img,imgwidth,imgheight,Xmin,Ymin,Xmax,Ymax);
  free(img);
}

void SVGPLOT__CONTOUR_IMAGE_TIME(IMAGE              img,
				 INT4               imgwidth,
				 INT4               imgheight,
				 SVGPLOT_PALETTE   *pal,		      
				 TIME_TT2000        xmin,
				 TIME_TT2000        xmax,
				 TIME_TT2000        xgap,//[xgap < 0] => ギャップなし
				 REAL8              ymin,
				 REAL8              ymax,
				 REAL8              ygap,//[ygap < 0] => ギャップなし
				 REAL8              zmin,
				 REAL8              zmax,
				 TIME_TT2000        x[], //x[k]
				 INT4               xnum,
				 REAL8              y[], //y[l]
				 INT4               ynum,
				 REAL8              z[], //z[k * ynum + l]
				 SVGPLOT__SCALETYPE yscaletype,
				 SVGPLOT__SCALETYPE zscaletype){
  INT4 *idxx;
  INT4 *idxy;
  INT4 *buf;
  TIME_TT2000 xn,dx;
  REAL8 ym;
  REAL8 dy;
  REAL8 rx,ry;
  INT4  n,m,k,l;

  if((buf = (INT4*)malloc(sizeof(INT4) * (imgwidth + imgheight))) == NULL){
    exit(EXIT_FAILURE);
  }
  idxx = &buf[       0];
  idxy = &buf[imgwidth];

  for(n = 0;n < imgwidth ;n++){
    rx = n / (REAL8)(imgwidth  - 1);
    xn = xmin +    (xmax - xmin) * rx;

    idxx[n] = 0;
    dx      = llabs(xn - x[0]);
    for(k = 1;k < xnum;k++){
      if(dx > llabs(xn - x[k])){
	idxx[n] = k;
	dx      = llabs(xn - x[k]);
      }
    }
    if((xgap >= 0.0) && (dx > xgap)){
      idxx[n] = -1;
    }
  }

  for(m = 0;m < imgheight;m++){
    ry = m / (REAL8)(imgheight - 1);
    switch(yscaletype){
    case SVGPLOT__SCALETYPE_LINEAR:
      ym = ymin +    (ymax - ymin) * ry;
      break;
    case SVGPLOT__SCALETYPE_LOG:
      ym = ymin * pow(ymax / ymin,   ry);
      break;
    default:
      fprintf(stderr,"[WARNING] UNKNOWN SCALETYPE\n");
      exit(EXIT_FAILURE);
    }
    idxy[m] = 0;
    dy      = fabs(ym - y[0]);
    for(l = 1;l < ynum;l++){
      if(dy > fabs(ym - y[l])){
	idxy[m] = l;
	dy      = fabs(ym - y[l]);
      }
    }
    if((ygap >= 0.0) && (dy > ygap)){
      idxy[m] = -1;
    }
  }

  for(m = 0;m < imgheight;m++){
    for(n = 0;n < imgwidth ;n++){
      if((idxx[n] == -1) || (idxy[m] == -1)){
	img[(imgheight - 1 - m) * imgwidth + n] = pal->color_gap;
      }else{
	img[(imgheight - 1 - m) * imgwidth + n] = SVGPLOT_PALETTE__Get_RGBA(pal,zmin,zmax,zscaletype,z[idxx[n] * ynum + idxy[m]]);
      }
    }
  }

  free(buf);
}

void SVGPLOT__CONTOUR_IMAGE2_TIME(IMAGE              img,
				  INT4               imgwidth,
				  INT4               imgheight,
				  SVGPLOT_PALETTE   *pal,		      
				  T2000        tmin,
				  T2000        tmax,
				  T2000        tgap,
				  REAL8              ymin,
				  REAL8              ymax,
				  REAL8              ygap,//[ygap < 0] => ギャップなし
				  REAL8              zmin,
				  REAL8              zmax,
				  T2000        t[], //t[k]
				  INT4               tnum,
				  REAL8              y[], //y[l]
				  INT4               ynum,
				  REAL8              z[], //z[k * ynum + l]
				  INT4 yscaletype,
				  INT4 zscaletype){
  
  void  *buf;
  INT4  *t_idx1;
  INT4  *t_idx2;
  INT4  *y_idx1;
  INT4  *y_idx2;
  T2000 *t_grid;
  REAL8 *y_grid;
  T2000  dt,dt_abs;
  T2000  dt_abs_min1 = ILLEGAL_TT2000_VALUE;
  T2000  dt_abs_min2 = ILLEGAL_TT2000_VALUE;
  REAL8  dy,dy_abs;
  REAL8  dy_abs_min1 = 0.0;
  REAL8  dy_abs_min2 = 0.0;
  REAL8  z0_t1_y1;
  REAL8  z0_t1_y2;
  REAL8  z0_t2_y1;
  REAL8  z0_t2_y2;
  REAL8  ry;
  REAL8  dx;
  REAL8  z0 = 0.0;
  INT4   n,m,k,l;

  if((buf = malloc(sizeof(INT4) * (imgwidth * 2 + imgheight * 2) + sizeof(T2000) * imgwidth + sizeof(REAL8) * imgheight)) == NULL){
    exit(EXIT_FAILURE);
  }

  t_idx1 = (INT4 *)buf;
  t_idx2 = (INT4 *)&t_idx1[imgwidth];

  y_idx1 = (INT4 *)&t_idx2[imgwidth];
  y_idx2 = (INT4 *)&y_idx1[imgheight];

  t_grid = (T2000*)&y_idx2[imgheight];
  y_grid = (REAL8*)&t_grid[imgwidth] ;

  for(n = 0;n < imgwidth ;n++){
    t_grid[n] = tmin + (tmax - tmin) * n / (REAL8)(imgwidth  - 1);
  }
  
  for(m = 0;m < imgheight;m++){
    ry = m / (REAL8)(imgheight - 1);
    switch(yscaletype){
    case 0:
      y_grid[m] = ymin +    (ymax - ymin) * ry;
      break;
    case 1:
      y_grid[m] = ymin * pow(ymax / ymin,   ry);
      break;
    default:
      fprintf(stderr,"[WARNING] UNKNOWN SCALETYPE\n");
      exit(EXIT_FAILURE);
    }
  }

  for(n = 0;n < imgwidth ;n++){
    t_idx1[n] = -1;
    t_idx2[n] = -1;
    for(k = 0;k < tnum;k++){
      dt     = t_grid[n] - t[k];
      dt_abs = llabs(dt);
      if((tgap >= 0.0) && (dt_abs > tgap)){
	continue;
      }
      if(dt < 0.0){
	if(t_idx1[n] == -1){
	  t_idx1[n]   = k;
	  dt_abs_min1 = dt_abs;
	}else{
	  if(dt_abs_min1 > dt_abs){
	    t_idx1[n]   = k;
	    dt_abs_min1 = dt_abs;
	  }
	}
      }else{
	if(t_idx2[n] == -1){
	  t_idx2[n]   = k;
	  dt_abs_min2 = dt_abs;
	}else{
	  if(dt_abs_min2 > dt_abs){
	    t_idx2[n]   = k;
	    dt_abs_min2 = dt_abs;
	  }
	}	
      }
    }
  }

  for(m = 0;m < imgheight;m++){
    y_idx1[m] = -1;
    y_idx2[m] = -1;
    for(l = 0;l < ynum;l++){
      dy     = y_grid[m] - y[l];
      dy_abs = fabs(dy);
      if((ygap >= 0.0) && (dy_abs > ygap)){
	continue;
      }
      if(dy < 0.0){
	if(y_idx1[m] == -1){
	  y_idx1[m]   = l;
	  dy_abs_min1 = dy_abs;
	}else{
	  if(dy_abs_min1 > dy_abs){
	    y_idx1[m]   = l;
	    dy_abs_min1 = dy_abs;
	  }
	}
      }else{
	if(y_idx2[m] == -1){
	  y_idx2[m]   = l;
	  dy_abs_min2 = dy_abs;
	}else{
	  if(dy_abs_min2 > dy_abs){
	    y_idx2[m]   = l;
	    dy_abs_min2 = dy_abs;
	  }
	}	
      }
    }
  }

  for(m = 0;m < imgheight;m++){
    for(n = 0;n < imgwidth ;n++){
      if((t_idx1[n] == -1) && (t_idx2[n] == -1) && (y_idx1[m] == -1) && (y_idx2[m] == -1)){//0000: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] == -1) && (y_idx1[m] == -1) && (y_idx2[m] != -1)){//0001: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] == -1) && (y_idx1[m] != -1) && (y_idx2[m] == -1)){//0010: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] == -1) && (y_idx1[m] != -1) && (y_idx2[m] != -1)){//0011: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] != -1) && (y_idx1[m] == -1) && (y_idx2[m] == -1)){//0100: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] != -1) && (y_idx1[m] == -1) && (y_idx2[m] != -1)){//0101: 近傍にデータが一つ存在する場合
	z0 = z[t_idx2[n] * ynum + y_idx2[m]];
	goto EXIT1;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] != -1) && (y_idx1[m] != -1) && (y_idx2[m] == -1)){//0110: 近傍にデータが一つ存在する場合
	z0 = z[t_idx2[n] * ynum + y_idx1[m]];
	goto EXIT1;
      }
      if((t_idx1[n] == -1) && (t_idx2[n] != -1) && (y_idx1[m] != -1) && (y_idx2[m] != -1)){//0111: 近傍にデータが二つ存在する場合
	z0_t2_y1 = z[t_idx2[n] * ynum + y_idx1[m]];
	z0_t2_y2 = z[t_idx2[n] * ynum + y_idx2[m]];
	dy = (y_grid[m] - y[y_idx1[m]]) / (y[y_idx2[m]] - y[y_idx1[m]]);
	z0 = (1.0 - dy) * z0_t2_y1 + dy * z0_t2_y2;
	goto EXIT1;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] == -1) && (y_idx1[m] == -1) && (y_idx2[m] == -1)){//1000: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] == -1) && (y_idx1[m] == -1) && (y_idx2[m] != -1)){//1001: 近傍にデータが一つ存在する場合
	z0 = z[t_idx1[n] * ynum + y_idx2[m]];
	goto EXIT1;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] == -1) && (y_idx1[m] != -1) && (y_idx2[m] == -1)){//1010: 近傍にデータが一つ存在する場合
	z0 = z[t_idx1[n] * ynum + y_idx1[m]];
	goto EXIT1;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] == -1) && (y_idx1[m] != -1) && (y_idx2[m] != -1)){//1011: 近傍にデータが二つ存在する場合
	z0_t1_y1 = z[t_idx1[n] * ynum + y_idx1[m]];
	z0_t1_y2 = z[t_idx1[n] * ynum + y_idx2[m]];
	dy = (y_grid[m] - y[y_idx1[m]]) / (y[y_idx2[m]] - y[y_idx1[m]]);
	z0 = (1.0 - dy) * z0_t1_y1 + dy * z0_t1_y2;
	goto EXIT1;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] != -1) && (y_idx1[m] == -1) && (y_idx2[m] == -1)){//1100: 近傍にデータが存在しない場合
	goto EXIT2;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] != -1) && (y_idx1[m] == -1) && (y_idx2[m] != -1)){//1101: 近傍にデータが二つ存在する場合
	z0_t1_y2 = z[t_idx1[n] * ynum + y_idx2[m]];
	z0_t2_y2 = z[t_idx2[n] * ynum + y_idx2[m]];
	dx = (t_grid[n] - t[t_idx1[n]]) / (REAL8)(t[t_idx2[n]] - t[t_idx1[n]]);
	z0 = (1.0 - dx) * z0_t1_y2 + dx * z0_t2_y2;
	goto EXIT1;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] != -1) && (y_idx1[m] != -1) && (y_idx2[m] == -1)){//1110: 近傍にデータが二つ存在する場合
	z0_t1_y1 = z[t_idx1[n] * ynum + y_idx1[m]];
	z0_t2_y1 = z[t_idx2[n] * ynum + y_idx1[m]];
	dx = (t_grid[n] - t[t_idx1[n]]) / (REAL8)(t[t_idx2[n]] - t[t_idx1[n]]);
	z0 = (1.0 - dx) * z0_t1_y1 + dx * z0_t2_y1;
	goto EXIT1;
      }
      if((t_idx1[n] != -1) && (t_idx2[n] != -1) && (y_idx1[m] != -1) && (y_idx2[m] != -1)){//1111: 近傍にデータが四つ存在する場合
	z0_t1_y1 = z[t_idx1[n] * ynum + y_idx1[m]];
	z0_t1_y2 = z[t_idx1[n] * ynum + y_idx2[m]];
	z0_t2_y1 = z[t_idx2[n] * ynum + y_idx1[m]];
	z0_t2_y2 = z[t_idx2[n] * ynum + y_idx2[m]];
	dx = (t_grid[n] - t[t_idx1[n]]) / (REAL8)(t[t_idx2[n]] - t[t_idx1[n]]);
	dy = (y_grid[m] - y[y_idx1[m]]) / (y[y_idx2[m]] - y[y_idx1[m]]);
	z0 = (1.0 - dx) * (1.0 - dy) * z0_t1_y1 + (1.0 - dx) * dy * z0_t1_y2 + dx * (1.0 - dy) * z0_t2_y1 + dx * dy * z0_t2_y2;
	goto EXIT1;
      }
    EXIT1:
      img[(imgheight - 1 - m) * imgwidth + n] = SVGPLOT_PALETTE__Get_RGBA(pal,zmin,zmax,zscaletype,z0);
      continue;
    EXIT2:
      img[(imgheight - 1 - m) * imgwidth + n] = pal->color_gap;
    }
  }

  free(buf);
}
