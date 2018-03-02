#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define RE (6371.0e3)

// SM座標系からLMMへの変換
void  SM_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //SM [m]
		double  src_y,  //   [m]
		double  src_z,  //   [m]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		

  double r    = sqrt(src_x * src_x + src_y * src_y + src_z * src_z);
  double mlon = atan2(-src_y,-src_x);

  *mlat = atan2(src_z,sqrt(src_x * src_x + src_y * src_y));
  *mlt  = (mlon * 180.0 / M_PI) * 24.0 / 360.0;
  *L    = (r / RE) / pow(cos(*mlat),2.0);
}

//LMMから SM座標系への変換
void LMM_to_SM (double *dst_x,  //SM [m]
		double *dst_y,  //   [m]
		double *dst_z,  //   [m]
		double  L    ,  //L値
		double  mlat ,  //磁気緯度  [rad]
		double  mlt  ,  //磁気地方時[hour]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)
  double r     = L * RE * pow(cos(mlat),2.0);
  double theta = M_PI / 2.0 - mlat;
  double phi   = mlt * M_PI / 12.0 + M_PI;

  *dst_x = r * sin(theta) * cos(phi);
  *dst_y = r * sin(theta) * sin(phi);
  *dst_z = r * cos(theta);
}

//GEO座標系からLMMへの変換
void GEO_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
  
  double tmp_x,tmp_y,tmp_z;
  
  GEO_to_SM (&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
   SM_to_LMM(     L,  mlat,   mlt,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//LMMからGEO座標系への変換
void LMM_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  L    ,  //L値
		double  mlat ,  //磁気緯度  [rad]
		double  mlt  ,  //磁気地方時[hour]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)

  double tmp_x,tmp_y,tmp_z;

  LMM_to_SM (&tmp_x,&tmp_y,&tmp_z,
	          L,  mlat,   mlt,
	      year,month,day,hour,minute,second);  
   SM_to_GEO( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//GEI座標系からLMMへの変換
void GEI_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
  
  double tmp_x,tmp_y,tmp_z;
  
  GEI_to_SM (&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
   SM_to_LMM(     L,  mlat,   mlt,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//LMMからGEI座標系への変換
void LMM_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  L    ,  //L値
		double  mlat ,  //磁気緯度  [rad]
		double  mlt  ,  //磁気地方時[hour]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)

  double tmp_x,tmp_y,tmp_z;

  LMM_to_SM (&tmp_x,&tmp_y,&tmp_z,
	          L,  mlat,   mlt,
	      year,month,day,hour,minute,second);  
   SM_to_GEI( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//GSE座標系からLMMへの変換
void GSE_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
  
  double tmp_x,tmp_y,tmp_z;
  
  GSE_to_SM (&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
   SM_to_LMM(     L,  mlat,   mlt,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//LMMからGSE座標系への変換
void LMM_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  L    ,  //L値
		double  mlat ,  //磁気緯度  [rad]
		double  mlt  ,  //磁気地方時[hour]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)

  double tmp_x,tmp_y,tmp_z;

  LMM_to_SM (&tmp_x,&tmp_y,&tmp_z,
	          L,  mlat,   mlt,
	      year,month,day,hour,minute,second);  
   SM_to_GSE( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//GSM座標系からLMMへの変換
void GSM_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
 
  double tmp_x,tmp_y,tmp_z;
  
  GSM_to_SM (&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
   SM_to_LMM(     L,  mlat,   mlt,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//LMMからGSM座標系への変換
void LMM_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  L    ,  //L値
		double  mlat ,  //磁気緯度  [rad]
		double  mlt  ,  //磁気地方時[hour]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)

  double tmp_x,tmp_y,tmp_z;

  LMM_to_SM (&tmp_x,&tmp_y,&tmp_z,
	          L,  mlat,   mlt,
	      year,month,day,hour,minute,second);  
   SM_to_GSM( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//MAG座標系からLMMへの変換
void MAG_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //MAG
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
 
  double tmp_x,tmp_y,tmp_z;
  
  MAG_to_SM (&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
   SM_to_LMM(     L,  mlat,   mlt,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//LMMからMAG座標系への変換
void LMM_to_MAG(double *dst_x,  //MAG
		double *dst_y,
		double *dst_z,
		double  L    ,  //L値
		double  mlat ,  //磁気緯度  [rad]
		double  mlt  ,  //磁気地方時[hour]
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)

  double tmp_x,tmp_y,tmp_z;

  LMM_to_SM (&tmp_x,&tmp_y,&tmp_z,
	          L,  mlat,   mlt,
	      year,month,day,hour,minute,second);  
   SM_to_MAG( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}
