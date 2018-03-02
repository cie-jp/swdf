/***************************************************************** 
 *
 * 数密度
 *
 *
 *                           Created  by Mamoru Ota (2018/02/07)
 * 
 *****************************************************************/

#ifndef _DENSITY_H_INCLUDE_
#define _DENSITY_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"DATATYPE.h"

typedef struct{
  REAL8 lnN;        //対数密度 log(N[1/m^3])
  REAL8 dlnN_dr;    //対数密度の勾配[1/m]
  REAL8 dlnN_dtheta;//対数密度の勾配[1/rad]
  REAL8 dlnN_dphi;  //対数密度の勾配[1/rad]
}DENSITY;

typedef struct{
  CHAR     filename[2048];//ファイルパス
  INT4     year;
  INT4     month;
  INT4     day;
  INT4     hour;
  INT4     minute;
  REAL8    second;
  REAL8    Kp;            //Kp指数
  REAL8    phi;           //[rad]
  REAL8    r_diff;        //グリッド間隔[m]
  REAL8    theta_diff;    //グリッド間隔[rad]
  REAL8    r_min;         //[m]
  REAL8    r_max;         //[m]
  REAL8    theta_min;     //[rad]
  REAL8    theta_max;     //[rad]
  INT4     r_num;
  INT4     theta_num;
  DENSITY *data;          //[r_num][theta_num]密度情報
}DENSITY_2D;

typedef struct{
  CHAR       dirname[2048];
  INT4       year;
  INT4       month;
  INT4       day;
  INT4       hour;
  INT4       minute;
  REAL8      second;
  REAL8      Kp;          //Kp指数
  DENSITY_2D dat1;
  INT4       phi1_deg;    //[deg]
  DENSITY_2D dat2;
  INT4       phi2_deg;    //[deg]
}DENSITY_3D;

void  DENSITY_2D__INITIALIZE(DENSITY_2D *dens,
			     const CHAR *dirname,
			     INT4        year,   //年
			     INT4        month,  //月
			     INT4        day,    //日
			     INT4        hour,   //時
			     INT4        minute, //分
			     REAL8       second, //秒
			     REAL8       Kp,     //Kp指数
			     REAL8       phi);   //[rad]

void  DENSITY_2D__FINALIZE  (DENSITY_2D *dens);

void  DENSITY_2D__GET_DATA  (DENSITY    *data,
			     DENSITY_2D *dens,
			     REAL8       r,     //地心距離  [m]
			     REAL8       theta);//地理余緯度[rad]

void  DENSITY_3D__INITIALIZE(DENSITY_3D *dens,
			     const CHAR *dirname,
			     INT4        year,   //年
			     INT4        month,  //月
			     INT4        day,    //日
			     INT4        hour,   //時
			     INT4        minute, //分
			     REAL8       second, //秒
			     REAL8       Kp);    //Kp指数

void  DENSITY_3D__FINALIZE  (DENSITY_3D *dens);

void  DENSITY_3D__GET_DATA  (DENSITY    *data,
			     DENSITY_3D *dens,
			     REAL8       r,     //地心距離  [m]
			     REAL8       theta, //地理余緯度[rad]
			     REAL8       phi);  //地理経度  [rad]
  
#ifdef __cplusplus
}
#endif

#endif
