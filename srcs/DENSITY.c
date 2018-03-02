/***************************************************************** 
 *
 * 数密度
 *
 *
 *                           Created  by Mamoru Ota (2018/02/07)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"DENSITY.h"

void  DENSITY_2D__INITIALIZE(DENSITY_2D *dens,
			     const CHAR *dirname,
			     INT4        year,   //年
			     INT4        month,  //月
			     INT4        day,    //日
			     INT4        hour,   //時
			     INT4        minute, //分
			     REAL8       second, //秒
			     REAL8       Kp,     //Kp指数
			     REAL8       phi){   //[rad]
  FILE *fp;

  sprintf(dens->filename,"%s/dens_%04d%02d%02dT%02d%02d%02d_%3.1lf_%03d.bin",
	  dirname,
	  year,month,day,hour,minute,(int)second,Kp,(int)(phi / M_PI * 180.0 + 0.5));
  dens->year   = year;
  dens->month  = month;
  dens->day    = day;
  dens->hour   = hour;
  dens->minute = minute;
  dens->second = second;
  dens->Kp     = Kp;
  dens->phi    = phi;

  if((fp = fopen(dens->filename,"rb")) == NULL){
    fprintf(stderr,"[ERROR : FILE NOT FOUND] %s\n",dens->filename);
    exit(EXIT_FAILURE);
  }
  
  fread(&dens->    r_num ,sizeof(INT4) ,1,fp);
  fread(&dens->theta_num ,sizeof(INT4) ,1,fp);

  fread(&dens->    r_min ,sizeof(REAL8),1,fp);
  fread(&dens->theta_min ,sizeof(REAL8),1,fp);

  fread(&dens->    r_max ,sizeof(REAL8),1,fp);
  fread(&dens->theta_max ,sizeof(REAL8),1,fp);

  fread(&dens->    r_diff,sizeof(REAL8),1,fp);
  fread(&dens->theta_diff,sizeof(REAL8),1,fp);

  if((dens->data = (DENSITY*)malloc(sizeof(DENSITY) * dens->r_num * dens->theta_num)) == NULL){
    fprintf(stderr,"[ERROR : DENSITY MEMORY ALLOCATION]\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr,"r_num = %d, theta_num = %d\n",dens->r_num,dens->theta_num);
  fprintf(stderr,"    r_min = %e,     r_max = %e,     r_diff = %e\n",dens->    r_min,dens->    r_max,dens->    r_diff);
  fprintf(stderr,"theta_min = %e, theta_max = %e, theta_diff = %e\n",dens->theta_min,dens->theta_max,dens->theta_diff);
  fprintf(stderr,"sizeof(DENSITY) = %d\n",(int)sizeof(DENSITY));

  fread(dens->data,sizeof(DENSITY),dens->r_num * dens->theta_num,fp);

  fclose(fp);
}

void  DENSITY_2D__FINALIZE  (DENSITY_2D *dens){
  free(dens->data);
}

void  DENSITY_2D__GET_DATA  (DENSITY    *data,
			     DENSITY_2D *dens,
			     REAL8       r,     //地心距離  [m]
			     REAL8       theta){//地理余緯度[rad]
  INT4    i1,i2;
  INT4    j1,j2;
  REAL8   x ,y;
  REAL8   x1,x2;
  REAL8   y1,y2;
  REAL8   dx,dy;
  DENSITY data_x1_y1;
  DENSITY data_x1_y2;
  DENSITY data_x2_y1;
  DENSITY data_x2_y2;

  x  = r;
  y  = theta;

  i1 = (    r - dens->    r_min) / dens->    r_diff;
  i2 = i1 + 1;
  j1 = (theta - dens->theta_min) / dens->theta_diff;
  j2 = j1 + 1;
  x1 = dens->    r_min + dens->    r_diff * i1;
  x2 = dens->    r_min + dens->    r_diff * i2;
  y1 = dens->theta_min + dens->theta_diff * j1;
  y2 = dens->theta_min + dens->theta_diff * j2;  

  if((i1 < 0) || (dens->    r_num <= i1)){
    i1 = -1;
  }
  if((i2 < 0) || (dens->    r_num <= i2)){
    i2 = -1;
  }
  if((j1 < 0) || (dens->theta_num <= j1)){
    j1 = -1;
  }
  if((j2 < 0) || (dens->theta_num <= j2)){
    j2 = -1;
  }

  if((i1 == -1) || (j1 == -1)){
    goto EXIT2;
  }
  /*else{
    *data = dens->data[i1 * dens->theta_num + j1];
    return;
    }*/

  if((i1 == -1) && (i2 == -1) && (j1 == -1) && (j2 == -1)){//0000: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 == -1) && (i2 == -1) && (j1 == -1) && (j2 != -1)){//0001: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 == -1) && (i2 == -1) && (j1 != -1) && (j2 == -1)){//0010: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 == -1) && (i2 == -1) && (j1 != -1) && (j2 != -1)){//0011: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 == -1) && (i2 != -1) && (j1 == -1) && (j2 == -1)){//0100: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 == -1) && (i2 != -1) && (j1 == -1) && (j2 != -1)){//0101: 近傍にデータが一つ存在する場合
    *data = dens->data[i2 * dens->theta_num + j2];
    goto EXIT1;
  }
  if((i1 == -1) && (i2 != -1) && (j1 != -1) && (j2 == -1)){//0110: 近傍にデータが一つ存在する場合
    *data = dens->data[i2 * dens->theta_num + j1];
    goto EXIT1;
  }
  if((i1 == -1) && (i2 != -1) && (j1 != -1) && (j2 != -1)){//0111: 近傍にデータが二つ存在する場合
    data_x2_y1 = dens->data[i2 * dens->theta_num + j1];
    data_x2_y2 = dens->data[i2 * dens->theta_num + j2];
    dy = (y - y1) / (y2 - y1);
    data->lnN         = (1.0 - dy) * data_x2_y1.lnN         + dy * data_x2_y2.lnN;
    data->dlnN_dr     = (1.0 - dy) * data_x2_y1.dlnN_dr     + dy * data_x2_y2.dlnN_dr;
    data->dlnN_dtheta = (1.0 - dy) * data_x2_y1.dlnN_dtheta + dy * data_x2_y2.dlnN_dtheta;
    data->dlnN_dphi   = (1.0 - dy) * data_x2_y1.dlnN_dphi   + dy * data_x2_y2.dlnN_dphi;
    goto EXIT1;
  }
  if((i1 != -1) && (i2 == -1) && (j1 == -1) && (j2 == -1)){//1000: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 != -1) && (i2 == -1) && (j1 == -1) && (j2 != -1)){//1001: 近傍にデータが一つ存在する場合
    *data = dens->data[i1 * dens->theta_num + j2];
    goto EXIT1;
  }
  if((i1 != -1) && (i2 == -1) && (j1 != -1) && (j2 == -1)){//1010: 近傍にデータが一つ存在する場合
    *data = dens->data[i1 * dens->theta_num + j1];
    goto EXIT1;
  }
  if((i1 != -1) && (i2 == -1) && (j1 != -1) && (j2 != -1)){//1011: 近傍にデータが二つ存在する場合
    data_x1_y1 = dens->data[i1 * dens->theta_num + j1];
    data_x1_y2 = dens->data[i1 * dens->theta_num + j2];
    dy = (y - y1) / (y2 - y1);
    data->lnN         = (1.0 - dy) * data_x1_y1.lnN         + dy * data_x1_y2.lnN;
    data->dlnN_dr     = (1.0 - dy) * data_x1_y1.dlnN_dr     + dy * data_x1_y2.dlnN_dr;
    data->dlnN_dtheta = (1.0 - dy) * data_x1_y1.dlnN_dtheta + dy * data_x1_y2.dlnN_dtheta;
    data->dlnN_dphi   = (1.0 - dy) * data_x1_y1.dlnN_dphi   + dy * data_x1_y2.dlnN_dphi;
    goto EXIT1;
  }
  if((i1 != -1) && (i2 != -1) && (j1 == -1) && (j2 == -1)){//1100: 近傍にデータが存在しない場合
    goto EXIT2;
  }
  if((i1 != -1) && (i2 != -1) && (j1 == -1) && (j2 != -1)){//1101: 近傍にデータが二つ存在する場合
    data_x1_y2 = dens->data[i1 * dens->theta_num + j2];
    data_x2_y2 = dens->data[i2 * dens->theta_num + j2];
    dx = (x - x1) / (x2 - x1);
    data->lnN         = (1.0 - dx) * data_x1_y2.lnN         + dx * data_x2_y2.lnN;
    data->dlnN_dr     = (1.0 - dx) * data_x1_y2.dlnN_dr     + dx * data_x2_y2.dlnN_dr;
    data->dlnN_dtheta = (1.0 - dx) * data_x1_y2.dlnN_dtheta + dx * data_x2_y2.dlnN_dtheta;
    data->dlnN_dphi   = (1.0 - dx) * data_x1_y2.dlnN_dphi   + dx * data_x2_y2.dlnN_dphi;
    goto EXIT1;
  }
  if((i1 != -1) && (i2 != -1) && (j1 != -1) && (j2 == -1)){//1110: 近傍にデータが二つ存在する場合
    data_x1_y1 = dens->data[i1 * dens->theta_num + j1];
    data_x2_y1 = dens->data[i2 * dens->theta_num + j1];
    dx = (x - x1) / (x2 - x1);
    data->lnN         = (1.0 - dx) * data_x1_y1.lnN         + dx * data_x2_y1.lnN;
    data->dlnN_dr     = (1.0 - dx) * data_x1_y1.dlnN_dr     + dx * data_x2_y1.dlnN_dr;
    data->dlnN_dtheta = (1.0 - dx) * data_x1_y1.dlnN_dtheta + dx * data_x2_y1.dlnN_dtheta;
    data->dlnN_dphi   = (1.0 - dx) * data_x1_y1.dlnN_dphi   + dx * data_x2_y1.dlnN_dphi;
    goto EXIT1;
  }
  if((i1 != -1) && (i2 != -1) && (j1 != -1) && (j2 != -1)){//1111: 近傍にデータが四つ存在する場合
    data_x1_y1 = dens->data[i1 * dens->theta_num + j1];
    data_x1_y2 = dens->data[i1 * dens->theta_num + j2];
    data_x2_y1 = dens->data[i2 * dens->theta_num + j1];
    data_x2_y2 = dens->data[i2 * dens->theta_num + j2];
    dx = (x - x1) / (x2 - x1);
    dy = (y - y1) / (y2 - y1);
    data->lnN         = (1.0 - dx) * (1.0 - dy) * data_x1_y1.lnN         + (1.0 - dx) * dy * data_x1_y2.lnN         + dx * (1.0 - dy) * data_x2_y1.lnN         + dx * dy * data_x2_y2.lnN;
    data->dlnN_dr     = (1.0 - dx) * (1.0 - dy) * data_x1_y1.dlnN_dr     + (1.0 - dx) * dy * data_x1_y2.dlnN_dr     + dx * (1.0 - dy) * data_x2_y1.dlnN_dr     + dx * dy * data_x2_y2.dlnN_dr;
    data->dlnN_dtheta = (1.0 - dx) * (1.0 - dy) * data_x1_y1.dlnN_dtheta + (1.0 - dx) * dy * data_x1_y2.dlnN_dtheta + dx * (1.0 - dy) * data_x2_y1.dlnN_dtheta + dx * dy * data_x2_y2.dlnN_dtheta;
    data->dlnN_dphi   = (1.0 - dx) * (1.0 - dy) * data_x1_y1.dlnN_dphi   + (1.0 - dx) * dy * data_x1_y2.dlnN_dphi   + dx * (1.0 - dy) * data_x2_y1.dlnN_dphi   + dx * dy * data_x2_y2.dlnN_dphi;
    goto EXIT1;
  }
 EXIT1:
  return;
 EXIT2:
  data->lnN         = log(0.0);
  data->dlnN_dr     = 0.0;
  data->dlnN_dtheta = 0.0;
  data->dlnN_dphi   = 0.0;
}

void  DENSITY_3D__INITIALIZE(DENSITY_3D *dens,
			     const CHAR *dirname,
			     INT4        year,   //年
			     INT4        month,  //月
			     INT4        day,    //日
			     INT4        hour,   //時
			     INT4        minute, //分
			     REAL8       second, //秒
			     REAL8       Kp){    //Kp指数
  sprintf(dens->dirname,"%s",dirname);
  dens->year     = year;
  dens->month    = month;
  dens->day      = day;
  dens->hour     = hour;
  dens->minute   = minute;
  dens->second   = second;
  dens->Kp       = Kp;
  dens->phi1_deg = -1;
  dens->phi2_deg = -1;
}

void  DENSITY_3D__FINALIZE  (DENSITY_3D *dens){
  DENSITY_2D__FINALIZE(&dens->dat1);
  DENSITY_2D__FINALIZE(&dens->dat2);
}

void  DENSITY_3D__GET_DATA  (DENSITY    *data,
			     DENSITY_3D *dens,
			     REAL8       r,     //地心距離  [m]
			     REAL8       theta, //地理余緯度[rad]
			     REAL8       phi){  //地理経度  [rad]
  FILE   *fp;
  CHAR    filename[2048];
  INT4    phi_idx;
  INT4    n;
  DENSITY d1,d2;
  REAL8   dp;
  REAL8   phi_deg;

  phi_deg = phi / M_PI * 180.0;
  while(phi_deg <   0.0){
    phi_deg += 360.0;
  }
  while(phi_deg > 360.0){
    phi_deg -= 360.0;
  }

  if((dens->phi1_deg == -1) || (dens->phi2_deg == -1) || !((dens->phi1_deg <= phi_deg) && (phi_deg <= dens->phi2_deg))){

    if(dens->phi1_deg != -1){
      DENSITY_2D__FINALIZE(&dens->dat1);
    }
    if(dens->phi2_deg != -1){
      DENSITY_2D__FINALIZE(&dens->dat2);
    }

    for(n = 0;n < 360;n++){
      phi_idx  = n;
      sprintf(filename,"%s/dens_%04d%02d%02dT%02d%02d%02d_%3.1lf_%03d.bin",
	      dens->dirname,
	      dens->year,dens->month,dens->day,dens->hour,dens->minute,(int)dens->second,dens->Kp,phi_idx);
      
      if((fp = fopen(filename,"rb")) == NULL){
	continue;
      }
      fclose(fp);
      if(phi_idx <= phi_deg){
	dens->phi1_deg = phi_idx;
      }else{
	break;
      }
    }
    for(n = 0;n < 360;n++){
      phi_idx  = n + dens->phi1_deg + 1;
      phi_idx %= 360;
      sprintf(filename,"%s/dens_%04d%02d%02dT%02d%02d%02d_%3.1lf_%03d.bin",
	      dens->dirname,
	      dens->year,dens->month,dens->day,dens->hour,dens->minute,(int)dens->second,dens->Kp,phi_idx);
      
      if((fp = fopen(filename,"rb")) == NULL){
	continue;
      }
      fclose(fp);
      if(phi_idx >= phi_deg){
	dens->phi2_deg = phi_idx;
	break;
      }
    }

    fprintf(stderr,"phi1 = %d [deg], phi2 = %d [deg]\n",dens->phi1_deg,dens->phi2_deg);
    
    if((dens->phi1_deg == -1) || (dens->phi2_deg == -1)){
      exit(EXIT_FAILURE);
    }
    
    DENSITY_2D__INITIALIZE(&dens->dat1,dens->dirname,dens->year,dens->month,dens->day,dens->hour,dens->minute,dens->second,dens->Kp,dens->phi1_deg / 180.0 * M_PI);
    DENSITY_2D__INITIALIZE(&dens->dat2,dens->dirname,dens->year,dens->month,dens->day,dens->hour,dens->minute,dens->second,dens->Kp,dens->phi2_deg / 180.0 * M_PI);
  }

  DENSITY_2D__GET_DATA(&d1,&dens->dat1,r,theta);
  DENSITY_2D__GET_DATA(&d2,&dens->dat2,r,theta);

  if(dens->phi1_deg == dens->phi2_deg){
    *data = d1;
  }else{
    dp = (phi_deg - dens->phi1_deg) / (dens->phi2_deg - dens->phi1_deg);
    
    data->lnN         = (1.0 - dp) * d1.lnN         + dp * d2.lnN;
    data->dlnN_dr     = (1.0 - dp) * d1.dlnN_dr     + dp * d2.dlnN_dr;
    data->dlnN_dtheta = (1.0 - dp) * d1.dlnN_dtheta + dp * d2.dlnN_dtheta;
    data->dlnN_dphi   = (1.0 - dp) * d1.dlnN_dphi   + dp * d2.dlnN_dphi;  
  }
}
