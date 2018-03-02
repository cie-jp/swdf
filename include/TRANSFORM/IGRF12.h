/*****************************************************************
 * 
 * 国際標準地球磁場IGRF12
 *
 *                           Created  by Mamoru Ota (2017/07/18)
 *
 *****************************************************************/ 

#ifndef _IGRF12_H_INCLUDE_
#define _IGRF12_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct{
  //経年変化する規格化ガウス係数
  long double G[14][14];
  long double H[14][14];
  
  //地心距離  に依存する変数(a_r[n] = (基準球面の半径 / r)^{2 + n})
  long double a_r[14];
  
  //地心余緯度に依存する変数
  long double cos_theta;
  long double sin_theta;
  long double P[14][14];
  long double Q[14][14];
  long double R[14][14];
  
  //地理経度  に依存する変数
  long double cos_phi[14];
  long double sin_phi[14];  
  
  //前回利用時のパラメータの保存
  double prev_year      ;//計算年 (西暦)
  double prev_r         ;//地心距離  [m]
  double prev_theta     ;//地心余緯度[rad]
  double prev_phi       ;//地理経度  [rad] 東経 +   

  //計算されるパラメータ群
  long double b         ;//           磁束密度 B       [T]
  long double brr       ;//r    方向の磁束密度 B_r     [T]
  long double bth       ;//theta方向の磁束密度 B_theta [T]
  long double bph       ;//phi  方向の磁束密度 B_phi   [T]
  long double db_drr    ;//dB       / dr     [T/m]
  long double db_dth    ;//dB       / dtheta [T/rad]
  long double db_dph    ;//dB       / dphi   [T/rad]
  long double dbrr_drr  ;//dB_r     / dr     [T/m]
  long double dbth_drr  ;//dB_theta / dr     [T/m]
  long double dbph_drr  ;//dB_phi   / dr     [T/m]
  long double dbrr_dth  ;//dB_r     / dtheta [T/rad]
  long double dbth_dth  ;//dB_theta / dtheta [T/rad]
  long double dbph_dth  ;//dB_phi   / dtheta [T/rad]
  long double dbrr_dph  ;//dB_r     / dphi   [T/rad]
  long double dbth_dph  ;//dB_theta / dphi   [T/rad]
  long double dbph_dph  ;//dB_phi   / dphi   [T/rad]
  long double yrr       ;//正規化ベクトル y = b / |b| のr     成分 Y_r
  long double yth       ;//                             theta 成分 Y_theta
  long double yph       ;//                             phi   成分 Y_phi
  long double dyrr_drr  ;//dY_r     / dr      [1/m]
  long double dyth_drr  ;//dY_theta / dr      [1/m]
  long double dyph_drr  ;//dY_phi   / dr      [1/m]
  long double dyrr_dth  ;//dY_r     / dtheta  [1/rad]
  long double dyth_dth  ;//dY_theta / dtheta  [1/rad]
  long double dyph_dth  ;//dY_phi   / dtheta  [1/rad]
  long double dyrr_dph  ;//dY_r     / dphi    [1/rad]
  long double dyth_dph  ;//dY_theta / dphi    [1/rad]
  long double dyph_dph  ;//dY_phi   / dphi    [1/rad]

  long double dipole_M  ;//地磁気双極子モーメント            磁気能率 M  [A m^2]
  long double dipole_Mx ;//地磁気双極子モーメント GEO x方向の磁気能率 Mx [A m^2]
  long double dipole_My ;//地磁気双極子モーメント GEO y方向の磁気能率 My [A m^2]
  long double dipole_Mz ;//地磁気双極子モーメント GEO z方向の磁気能率 Mz [A m^2]

  long double dipole_lat;//地磁気双極子モーメント 北磁極のGEI余緯度 [rad]
  long double dipole_lon;//地磁気双極子モーメント 北磁極のGEI経度   [rad]

}IGRF12;

extern IGRF12         GLOBAL_IGRF12;
extern int    IS_INIT_GLOBAL_IGRF12;

void IGRF12__Init  (IGRF12 *igrf);

void IGRF12__Update(IGRF12 *igrf,
		    int     year,
		    int     month,
		    int     day,
		    int     hour,
		    int     minute,
		    double  second);

void IGRF12__Calc  (IGRF12 *igrf,
		    double  r,     //(in)  地心距離   r     [m]
		    double  theta, //(in)  地心余緯度 theta [rad]
		    double  phi,   //(in)  地理経度   phi   [rad] 東経 +
		    int     year,  //(in)  計算年 (西暦)
		    int     month,
		    int     day,
		    int     hour,
		    int     minute,
		    double  second);

void IGRF12__Show  (IGRF12 *igrf);
  
#ifdef __cplusplus
}
#endif

#endif
