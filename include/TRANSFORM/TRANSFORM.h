/*****************************************************************
 * 
 * TRANSFORM
 *
 *                           Created  by Mamoru Ota (2017/07/18)
 *
 *****************************************************************/ 

#ifndef _TRANSFORM_H_INCLUDE_
#define _TRANSFORM_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// =================================================================
// 時刻関連
// =================================================================

//西暦年から平年か閏年かを判定(平年 : 0, 閏年 : 1) 
int    IS_LEAP_YEAR(int year); //西暦年(8 ~ 2800)

//西暦年月日から年通算日(平年 : 1 ~ 365, 閏年 : 1 ~ 366)を計算
int    DATE_to_DOY (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day); //日    (1 ~ 28,29,30,31)

//西暦年月日からユリウス通日[西暦-4712年1月1日12:00UT(ユリウス暦)からの通算経過日]を計算
double DATE_to_JD  (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day); //日    (1 ~ 28,29,30,31)

//西暦年月日から修正ユリウス日[西暦1858年11月17日00:00UT(グレゴリオ暦)からの通算経過日]を計算
double DATE_to_MJD (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day); //日    (1 ~ 28,29,30,31)

//西暦年月日からユリウス世紀[元紀J2000.0(西暦2000年1月1日12:00UT(グレゴリオ暦)からの通算経過日を1ユリウス世紀(36525日)で規格化したもの]を計算
double DATE_to_JC  (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day); //日    (1 ~ 28,29,30,31)

//西暦年月日・時刻からユリウス通日[西暦-4712年1月1日12:00UT(ユリウス暦)からの通算経過日]を計算
double EPOCH_to_JD (int    year,   //西暦年(8 ~ 2800)
		    int    month,  //月    (1 ~ 12)
		    int    day,    //日    (1 ~ 28,29,30,31)
		    int    hour,   //時    (0 ~ 23)
		    int    minute, //分    (0 ~ 59)
		    double second);//秒    (0 ~ 59.999999)

//西暦年月日・時刻から修正ユリウス日[西暦1858年11月17日00:00UT(グレゴリオ暦)からの通算経過日]を計算
double EPOCH_to_MJD(int    year,   //西暦年(8 ~ 2800)
		    int    month,  //月    (1 ~ 12)
		    int    day,    //日    (1 ~ 28,29,30,31)
		    int    hour,   //時    (0 ~ 23)
		    int    minute, //分    (0 ~ 59)
		    double second);//秒    (0 ~ 59.999999)

//西暦年月日・時刻からユリウス世紀[元紀J2000.0(西暦2000年1月1日12:00UT(グレゴリオ暦)からの通算経過日を1ユリウス世紀(36525日)で規格化したもの]を計算
double EPOCH_to_JC (int    year,   //西暦年(8 ~ 2800)
		    int    month,  //月    (1 ~ 12)
		    int    day,    //日    (1 ~ 28,29,30,31)
		    int    hour,   //時    (0 ~ 23)
		    int    minute, //分    (0 ~ 59)
		    double second);//秒    (0 ~ 59.999999)

// =================================================================
// 座標回転
// =================================================================

//x軸回転
void ROTATE_X(double *dst_x,
	      double *dst_y,
	      double *dst_z,
	      double  src_x,
	      double  src_y,
	      double  src_z,
	      double  rot); //回転角[rad]

//y軸回転
void ROTATE_Y(double *dst_x,
	      double *dst_y,
	      double *dst_z,
	      double  src_x,
	      double  src_y,
	      double  src_z,
	      double  rot); //回転角[rad]

//z軸回転
void ROTATE_Z(double *dst_x,
	      double *dst_y,
	      double *dst_z,
	      double  src_x,
	      double  src_y,
	      double  src_z,
	      double  rot); //回転角[rad]

// =================================================================
// 太陽の位置情報
// =================================================================
//西暦年月日・時刻からGreenwich Mean Sidereal Time(グリニッジ平均恒星時)を計算
//(グリニッジ子午線からみた春分点方向の角度[rad]を計算(逆回転))
//GEO座標系のx,y,zの内, x軸は地心からグリニッジ子午線に伸びるベクトルである. 
//GEO座標系のxy平面上(赤道面上)で春分点の位置の方位角成分-phi[rad]を計算している. 
double GMST(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second);//秒    (0 ~ 59.999999)

//西暦年月日・時刻から平均黄道傾斜角[rad]を計算
double OBLQ(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second);//秒    (0 ~ 59.999999) 

//西暦年月日・時刻から太陽の黄経(ecliptic longitude of the Sun)[rad]を計算
double ELON(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second);//秒    (0 ~ 59.999999) 

// =================================================================
// WGS84測地系 => GEO
// =================================================================

//WGS84測地系から地心座標系(GEO)への変換
void GEODETIC_to_GEOCENTRIC(double *r,      //(out) 地心距離   [m]
			    double *theta,  //(out) 地心余緯度 [rad]
			    double *phi,    //(out) 地理経度   [rad]
			    double  h,      //(in)  標高       [m]
			    double  theta0, //(in)  測地余緯度 [rad]
			    double  phi0);  //(in)  地理経度   [rad] 東経 +

// =================================================================
// GEO <=> GEI
// =================================================================

//GEO座標系からGEI座標系への変換
void GEO_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

//GEI座標系からGEO座標系への変換
void GEI_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

// =================================================================
// GEO <=> GEI <=> GSE
// =================================================================

//GEI座標系からGSE座標系への変換
void GEI_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
//GSE座標系からGEI座標系への変換
void GSE_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

//GEO座標系からGSE座標系への変換
void GEO_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
//GSE座標系からGEO座標系への変換
void GSE_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

// =================================================================
// GEO <=> GEI <=> GSE <=> GSM
// =================================================================

//GSE座標系からGSM座標系への変換
void GSE_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
//GSM座標系からGSE座標系への変換
void GSM_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GEO座標系からGSM座標系への変換
void GEO_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
//GSM座標系からGEO座標系への変換
void GSM_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GEI座標系からGSM座標系への変換
void GEI_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
//GSM座標系からGEI座標系への変換
void GSM_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

// =================================================================
// GEO <=> GEI <=> GSE <=> GSM <=> SM
// =================================================================

//GSM座標系から SM座標系への変換
void GSM_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
// SM座標系からGSM座標系への変換
void  SM_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GEO座標系から SM座標系への変換
void GEO_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
// SM座標系からGEO座標系への変換
void  SM_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GEI座標系から SM座標系への変換
void GEI_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
// SM座標系からGEI座標系への変換
void  SM_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GSE座標系から SM座標系への変換
void GSE_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)
		
// SM座標系からGSE座標系への変換
void  SM_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

// =================================================================
// GEO <=> GEI <=> GSE <=> GSM <=> SM <=> MAG
// =================================================================

//MAG座標系からGEO座標系への変換
void MAG_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  src_x,  //MAG
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GEO座標系からMAG座標系への変換
void GEO_to_MAG(double *dst_x,  //MAG
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

//MAG座標系からGEI座標系への変換
void MAG_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  src_x,  //MAG
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GEI座標系からMAG座標系への変換
void GEI_to_MAG(double *dst_x,  //MAG
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

//MAG座標系からGSE座標系への変換
void MAG_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  src_x,  //MAG
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GSE座標系からMAG座標系への変換
void GSE_to_MAG(double *dst_x,  //MAG
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

//MAG座標系からGSM座標系への変換
void MAG_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  src_x,  //MAG
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//GSM座標系からMAG座標系への変換
void GSM_to_MAG(double *dst_x,  //MAG
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

//MAG座標系から SM座標系への変換
void MAG_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //MAG
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

// SM座標系からMAG座標系への変換
void  SM_to_MAG(double *dst_x,  //MAG
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)

// =================================================================
// GEO <=> GEI <=> GSE <=> GSM <=> SM <=> MAG <=> LMM
// =================================================================

// SM座標系からLMMへの変換
void  SM_to_LMM(double *L    ,  //L値
		double *mlat ,  //磁気緯度  [rad]
		double *mlt  ,  //磁気地方時[hour]
		double  src_x,  //SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second);//秒    (0 ~ 59.999999)		

//LMMから SM座標系への変換
void LMM_to_SM (double *dst_x,  //SM
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
		double  second);//秒    (0 ~ 59.999999)

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
		double  second);//秒    (0 ~ 59.999999)		

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
		double  second);//秒    (0 ~ 59.999999)

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
		double  second);//秒    (0 ~ 59.999999)		

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
		double  second);//秒    (0 ~ 59.999999)

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
		double  second);//秒    (0 ~ 59.999999)		

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
		double  second);//秒    (0 ~ 59.999999)

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
		double  second);//秒    (0 ~ 59.999999)		

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
		double  second);//秒    (0 ~ 59.999999)

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
		double  second);//秒    (0 ~ 59.999999)		

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
		double  second);//秒    (0 ~ 59.999999)

#ifdef __cplusplus
}
#endif

#endif
