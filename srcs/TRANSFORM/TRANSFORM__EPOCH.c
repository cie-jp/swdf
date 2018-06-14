#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

//[参考資料1. 西暦と紀元前(BC)と紀元後(AD)の関係]
// ...
// 西暦-3年 => 紀元前-4年
// 西暦-2年 => 紀元前-3年
// 西暦-1年 => 紀元前-2年
// 西暦 0年 => 紀元前-1年
// 西暦 1年 => 紀元後+1年
// 西暦 2年 => 紀元後+2年
// 西暦 3年 => 紀元後+3年
// ...

//[参考資料2. ユリウス暦とグレゴリオ暦の切替]
// ...
// 西暦1582年10月 1日 (ユリウス暦)
// 西暦1582年10月 2日 (ユリウス暦)
// 西暦1582年10月 3日 (ユリウス暦)
// 西暦1582年10月 4日 (ユリウス暦)   (注: 西暦1582年10月 5日から西暦1582年10月14日は存在しない)
// 西暦1582年10月15日 (グレゴリオ暦)
// 西暦1582年10月16日 (グレゴリオ暦)
// 西暦1582年10月17日 (グレゴリオ暦)
// 西暦1582年10月18日 (グレゴリオ暦)
// ...

//[参考資料3. ユリウス暦の閏年の取り決め]
// 4年に1度閏年を設ける. 
// 西暦   8年以降では, 4で割り切れる西暦年は閏年となっている. 
// 西暦1582年は平年である. 
// 閏年の例
// 西暦   8年 
// 西暦  12年
// 西暦  80年
// 西暦1200年
// 西暦1580年

//[参考資料4. グレゴリオ暦の閏年の取り決め]
// 西暦年が100で割り切れるが400では割り切れない年は平年とする. 
// これ以外の西暦年で4で割り切れる場合は閏年とする. 
// 西暦1582年は平年である. 


//西暦年から平年か閏年かを判定(平年 : 0, 閏年 : 1) 
int    IS_LEAP_YEAR(int year){ //西暦年(8 ~ 2800)
  if((year < 8) || (2800 < year)){
    fprintf(stderr,"ERROR : IS_LEAP_YEAR\n");
    exit(EXIT_FAILURE);
  } 
  if(year < 1582){
    if((year % 4) == 0){
      return 1;
    }
  }
  if(year > 1582){
    if(((year % 100) == 0) && ((year % 400) != 0)){
      return 0;
    }
    if((year % 4) == 0){
      return 1;
    }  
  }
  return 0;
}

//西暦年月日から年通算日(平年 : 1 ~ 365, 閏年 : 1 ~ 366)を計算
int    DATE_to_DOY (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day){ //日    (1 ~ 28,29,30,31)
  static int old_year  = -99;
  static int old_month = -99;
  static int old_day   = -99;
  static int old_doy   = -99;
  int        m;
  
  if((old_year == year) && (old_month == month) && (old_day == day)){
    return old_doy;
  }

  const int days_per_month[2][12] = {
    {31,28,31,30,31,30,31,31,30,31,30,31},//common year
    {31,29,31,30,31,30,31,31,30,31,30,31} //leap   year
  };  

  int leap_year_flag = IS_LEAP_YEAR(year);
  int day_of_year    = 1;

  if((year == 1582) && (month == 10) && (4 < day) && (day < 15)){
    fprintf(stderr,"ERROR : DATE_to_DOY\n");
    exit(EXIT_FAILURE);	
  }

  if((month < 1) || (12                                        < month)){
    fprintf(stderr,"ERROR : DATE_to_DOY\n");
    exit(EXIT_FAILURE);
  }

  if((day   < 1) || (days_per_month[leap_year_flag][month - 1] < day  )){
    fprintf(stderr,"ERROR : DATE_to_DOY\n");
    exit(EXIT_FAILURE);
  }

  for(m = 1;m < month;m++){
    day_of_year  += days_per_month[leap_year_flag][m - 1];
  }
  day_of_year += (day - 1);

  old_year  = year ;
  old_month = month;
  old_day   = day  ;
  if(year != 1582){
    old_doy = day_of_year;
  }else{
    old_doy = ((month < 10) || ((month == 10) && (day <= 4))) ? day_of_year : day_of_year - 10;
  }  
  return old_doy;
}

//西暦年月日からユリウス通日[西暦-4712年1月1日12:00UT(ユリウス暦)からの通算経過日]を計算
double DATE_to_JD  (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day){ //日    (1 ~ 28,29,30,31)
  static int    old_year  = -99  ;
  static int    old_month = -99  ;
  static int    old_day   = -99  ;
  static double old_jd    = -99.0;
  int           y;
  
  if((old_year == year) && (old_month == month) && (old_day == day)){
    return old_jd;
  }

  const double jd0 = 1723979.5;//西暦8年1月1日00:00UT(ユリウス暦)のユリウス通日
  double       jd  = jd0;

  for(y = 8;y < year;y++){
    if(y == 1582){
      jd += 355;
    }else{
      jd += IS_LEAP_YEAR(y) ? 366 : 365;
    }
  }

  old_year  = year ;
  old_month = month;
  old_day   = day  ;
  old_jd    = jd + (DATE_to_DOY(year,month,day) - 1);
  return old_jd;
}

//西暦年月日から修正ユリウス日[西暦1858年11月17日00:00UT(グレゴリオ暦)からの通算経過日]を計算
double DATE_to_MJD (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day){ //日    (1 ~ 28,29,30,31)

  const double jd0 = 2400000.5;//西暦1858年11月17日00:00UT(グレゴリオ暦)のユリウス通日

  return  DATE_to_JD(year,month,day) - jd0;
}

//西暦年月日からユリウス世紀[元紀J2000.0(西暦2000年1月1日12:00UT(グレゴリオ暦)からの通算経過日を1ユリウス世紀(36525日)で規格化したもの]を計算
double DATE_to_JC  (int  year, //西暦年(8 ~ 2800)
		    int  month,//月    (1 ~ 12)
		    int  day){ //日    (1 ~ 28,29,30,31)
  const double jd0 = 2451545.0;//元紀J2000.0のユリウス通日 

  return (DATE_to_JD(year,month,day) - jd0) / 36525.0;
}

//西暦年月日・時刻からユリウス通日[西暦-4712年1月1日12:00UT(ユリウス暦)からの通算経過日]を計算
double EPOCH_to_JD (int    year,   //西暦年(8 ~ 2800)
		    int    month,  //月    (1 ~ 12)
		    int    day,    //日    (1 ~ 28,29,30,31)
		    int    hour,   //時    (0 ~ 23)
		    int    minute, //分    (0 ~ 59)
		    double second){//秒    (0 ~ 59.999999)
  double dt = (3600.0 * hour + 60.0 * minute + second) / 86400.0;
  return DATE_to_JD (year,month,day) + dt;
}

//西暦年月日・時刻から修正ユリウス日[西暦1858年11月17日00:00UT(グレゴリオ暦)からの通算経過日]を計算
double EPOCH_to_MJD(int    year,   //西暦年(8 ~ 2800)
		    int    month,  //月    (1 ~ 12)
		    int    day,    //日    (1 ~ 28,29,30,31)
		    int    hour,   //時    (0 ~ 23)
		    int    minute, //分    (0 ~ 59)
		    double second){//秒    (0 ~ 59.999999)
  double dt = (3600.0 * hour + 60.0 * minute + second) / 86400.0;
  return DATE_to_MJD(year,month,day) + dt;
}

//西暦年月日・時刻からユリウス世紀[元紀J2000.0(西暦2000年1月1日12:00UT(グレゴリオ暦)からの通算経過日を1ユリウス世紀(36525日)で規格化したもの]を計算
double EPOCH_to_JC (int    year,   //西暦年(8 ~ 2800)
		    int    month,  //月    (1 ~ 12)
		    int    day,    //日    (1 ~ 28,29,30,31)
		    int    hour,   //時    (0 ~ 23)
		    int    minute, //分    (0 ~ 59)
		    double second){//秒    (0 ~ 59.999999)
  double dt = (3600.0 * hour + 60.0 * minute + second) / 86400.0;
  return DATE_to_JC (year,month,day) + dt / 36525.0;
}
