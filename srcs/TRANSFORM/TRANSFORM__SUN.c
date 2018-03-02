#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

//西暦年月日・時刻からGreenwich Mean Sidereal Time(グリニッジ平均恒星時)を計算
//(グリニッジ子午線からみた春分点方向の角度[rad]を計算(逆回転))
//GEO座標系のx,y,zの内, x軸は地心からグリニッジ子午線に伸びるベクトルである. 
//GEO座標系のxy平面上(赤道面上)で春分点の位置の方位角成分-phi[rad]を計算している. 
double GMST(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second){//秒    (0 ~ 59.999999)
  static int    old_year   = -99  ;
  static int    old_month  = -99  ;
  static int    old_day    = -99  ;
  static int    old_hour   = -99  ;
  static int    old_minute = -99  ;
  static double old_second = -99.0;
  static double old_gmst   = -99.0;
  
  if((old_year == year) && (old_month == month) && (old_day == day) && (old_hour == hour) && (old_minute == minute) && (old_second == second)){
    return old_gmst;
  }

  double jd    = EPOCH_to_JD(year,month,day,hour,minute,second) - EPOCH_to_JD(1899,12,31,12,0,0.0);
  double dt    = (3600.0 * hour + 60.0 * minute + second) / 86400.0;
  double angle = 279.690983 + 0.9856473354 * jd + 360.0 * dt + 180.0;//[deg]
  double c     = cos(angle * M_PI / 180.0);
  double s     = sin(angle * M_PI / 180.0);

  old_year   = year;
  old_month  = month;
  old_day    = day;
  old_hour   = hour;
  old_minute = minute;
  old_second = second;
  old_gmst   = atan2(s,c);

  return old_gmst;
}

/*
double GMST_old(int    year,   //西暦年(8 ~ 2800)
		int    month,  //月    (1 ~ 12)
		int    day,    //日    (1 ~ 28,29,30,31)
		int    hour,   //時    (0 ~ 23)
		int    minute, //分    (0 ~ 59)
		double second){//秒    (0 ~ 59.999999)
  double jc    = EPOCH_to_JC(year,month,day,hour,minute,second);
  //Algorithm from "Astronomical Algorithms" by Jean Meeus.
  double angle = 280.46061837 + 360.98564736629 * (jc * 36525.0) + 3.87933e-4 * (jc * jc) - (jc * jc * jc) / 3.871e+7;//[deg]
  double c     = cos(angle * M_PI / 180.0);
  double s     = sin(angle * M_PI / 180.0);
  return atan2(s,c);
}
*/

//西暦年月日・時刻から平均黄道傾斜角[rad]を計算
double OBLQ(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second){//秒    (0 ~ 59.999999) 
  static int    old_year   = -99  ;
  static int    old_month  = -99  ;
  static int    old_day    = -99  ;
  static int    old_hour   = -99  ;
  static int    old_minute = -99  ;
  static double old_second = -99.0;
  static double old_oblq   = -99.0;
  
  if((old_year == year) && (old_month == month) && (old_day == day) && (old_hour == hour) && (old_minute == minute) && (old_second == second)){
    return old_oblq;
  }

  double jd    = EPOCH_to_JD(year,month,day,hour,minute,second) - EPOCH_to_JD(1899,12,31,12,0,0.0);
  double jc    = jd / 36525.0;
  double angle = 23.45229 - 0.0130125 * jc;
  double c     = cos(angle * M_PI / 180.0);
  double s     = sin(angle * M_PI / 180.0);

  old_year   = year;
  old_month  = month;
  old_day    = day;
  old_hour   = hour;
  old_minute = minute;
  old_second = second;
  old_oblq   = atan2(s,c);
  return old_oblq;
}

/*
double OBLQ_old(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second){//秒    (0 ~ 59.999999) 
  double jc    = EPOCH_to_JC(year,month,day,hour,minute,second);
  double angle = (84381.406 - 46.836769 * jc - 0.00059 * (jc * jc) + 0.001813 * (jc * jc * jc)) / 3600.0;
  double c     = cos(angle * M_PI / 180.0);
  double s     = sin(angle * M_PI / 180.0);
  return atan2(s,c);
}
*/

//西暦年月日・時刻から太陽の黄経(ecliptic longitude of the Sun)[rad]を計算
double ELON(int    year,   //西暦年(8 ~ 2800)
	    int    month,  //月    (1 ~ 12)
	    int    day,    //日    (1 ~ 28,29,30,31)
	    int    hour,   //時    (0 ~ 23)
	    int    minute, //分    (0 ~ 59)
	    double second){//秒    (0 ~ 59.999999) 
  static int    old_year   = -99  ;
  static int    old_month  = -99  ;
  static int    old_day    = -99  ;
  static int    old_hour   = -99  ;
  static int    old_minute = -99  ;
  static double old_second = -99.0;
  static double old_elon   = -99.0;
  
  if((old_year == year) && (old_month == month) && (old_day == day) && (old_hour == hour) && (old_minute == minute) && (old_second == second)){
    return old_elon;
  }

  double jd    = EPOCH_to_JD(year,month,day,hour,minute,second) - EPOCH_to_JD(1899,12,31,12,0,0.0);
  double jc    = jd / 36525.0;
  double L     =  279.696678 + 0.9856473354 * jd;                //mean longitude of the Sun, corrected for the aberration of light [deg]
  double g     = (358.475845 + 0.9856002670 * jd) * M_PI / 180.0;//平均近点角 mean anomaly of the Sun                               [rad]
  double angle = L + (1.91946 - 0.004789 * jc) * sin(g) + 0.020094 * sin(2.0 * g);
  double c     = cos(angle * M_PI / 180.0);
  double s     = sin(angle * M_PI / 180.0);
  old_year   = year;
  old_month  = month;
  old_day    = day;
  old_hour   = hour;
  old_minute = minute;
  old_second = second;
  old_elon   = atan2(s,c);

  return old_elon;
}

/*
double ELON_old(int    year,   //西暦年(8 ~ 2800)
		int    month,  //月    (1 ~ 12)
		int    day,    //日    (1 ~ 28,29,30,31)
		int    hour,   //時    (0 ~ 23)
		int    minute, //分    (0 ~ 59)
		double second){//秒    (0 ~ 59.999999) 
  double jc    = EPOCH_to_JC(year,month,day,hour,minute,second);
  double L     =  280.460 + 0.9856474 * (jc * 36525.0);                //mean longitude of the Sun, corrected for the aberration of light [deg]
  double g     = (357.528 + 0.9856003 * (jc * 36525.0)) * M_PI / 180.0;//平均近点角 mean anomaly of the Sun                               [rad]
  double angle = L + 1.915 * sin(g) + 0.020 * sin(2.0 * g);
  double c     = cos(angle * M_PI / 180.0);
  double s     = sin(angle * M_PI / 180.0);
  return atan2(s,c);
}
*/
