/***************************************************************** 
 *
 * 時刻
 *
 *
 *                           Created  by Mamoru Ota (2018/03/22)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"cdf.h"
#include"DTIME.h"

void  T2000__PRINT    (T2000 epoch,FILE *fp){
  DTIME__PRINT(DTIME__MAKE_FROM_T2000(epoch),fp);
}

void  DTIME__PRINT    (DTIME epoch,FILE *fp){
  fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d",
          epoch.YYYY,
          epoch.MM,
          epoch.DD,
          epoch.hh,
          epoch.mm,
          epoch.ss,
          epoch.msec,
          epoch.usec,
          epoch.nsec);
}

T2000 T2000__MAKE_FROM_DTIME(DTIME epoch){
  return CDF_TT2000_from_UTC_parts((double)epoch.YYYY,
                                   (double)epoch.MM,
                                   (double)epoch.DD,
                                   (double)epoch.hh,
                                   (double)epoch.mm,
                                   (double)epoch.ss,
                                   (double)epoch.msec,
                                   (double)epoch.usec,
                                   (double)epoch.nsec);
}

DTIME DTIME__MAKE_FROM_T2000(T2000 t2000){
  double YYYY;
  double MM;
  double DD;
  double hh;
  double mm;
  double ss;
  double msec;
  double usec;
  double nsec;
  DTIME  epoch;
  
  CDF_TT2000_to_UTC_parts(t2000,
                          &YYYY,
                          &MM,
                          &DD,
                          &hh,
                          &mm,
                          &ss,
                          &msec,
                          &usec,
                          &nsec);
  epoch.YYYY = (INT2)YYYY;
  epoch.MM   = (INT1)MM;
  epoch.DD   = (INT1)DD;
  epoch.hh   = (INT1)hh;
  epoch.mm   = (INT1)mm;
  epoch.ss   = (INT1)ss;
  epoch.msec = (INT2)msec;
  epoch.usec = (INT2)usec;
  epoch.nsec = (INT2)nsec;  
  return epoch;
}

T2000 T2000__NOW_JST(){
  time_t    timer;
  struct tm gmt;

  timer =    time(NULL);
  gmt   = *gmtime(&timer);
  return CDF_TT2000_from_UTC_parts((double)(gmt.tm_year +     1900),
                                   (double)(gmt.tm_mon  +        1),
                                   (double) gmt.tm_mday,
                                   (double) gmt.tm_hour,
                                   (double) gmt.tm_min,
                                   (double)(gmt.tm_sec  + 9 * 3600),
                                   TT2000END);  
}

DTIME DTIME__NOW_JST(){
  return DTIME__MAKE_FROM_T2000(T2000__NOW_JST());
}

// 指定フォーマット
//  YYYY-MM-DD hh:mm:ss.mmmuuunnn (終端文字を含めて30文字)
//  2000-01-01 00:00:00.000000000 (規定値)
T2000 T2000__MAKE_FROM_TEXT(const CHAR *text){
  CHAR  fmt[30] = "2000-01-01 00:00:00.000000000";
  CHAR  str[30];
  CHAR  YYYY[5];
  CHAR  MM  [3];
  CHAR  DD  [3];
  CHAR  hh  [3];
  CHAR  mm  [3];
  CHAR  ss  [3];
  CHAR  msec[4];
  CHAR  usec[4];
  CHAR  nsec[4];  
  INT4  i;

  for(i = 0;i < 30;i++){
    str[i] = text[i];
    if(text[i] == '\0'){
      break;
    }
  }
  for(     ;i < 30;i++){
    str[i] = fmt [i];
  }
  
  if(!isdigit(str[ 0]) ||
     !isdigit(str[ 1]) ||
     !isdigit(str[ 2]) ||
     !isdigit(str[ 3]) ||
     !(str[ 4] == '-') ||
     !isdigit(str[ 5]) ||
     !isdigit(str[ 6]) ||
     !(str[ 7] == '-') ||
     !isdigit(str[ 8]) ||
     !isdigit(str[ 9]) ||
     !(str[10] == ' ') ||
     !isdigit(str[11]) ||
     !isdigit(str[12]) ||
     !(str[13] == ':') ||
     !isdigit(str[14]) ||
     !isdigit(str[15]) ||
     !(str[16] == ':') ||
     !isdigit(str[17]) ||
     !isdigit(str[18]) ||
     !(str[19] == '.') ||
     !isdigit(str[20]) ||
     !isdigit(str[21]) ||
     !isdigit(str[22]) ||
     !isdigit(str[23]) ||
     !isdigit(str[24]) ||
     !isdigit(str[25]) ||
     !isdigit(str[26]) ||
     !isdigit(str[27]) ||
     !isdigit(str[28]) ||
     (str[29] != '\0') ){
    return ILLEGAL_TT2000_VALUE;
  }
     
  YYYY[0] = str[ 0];
  YYYY[1] = str[ 1];
  YYYY[2] = str[ 2];
  YYYY[3] = str[ 3];
  YYYY[4] = '\0';
  MM  [0] = str[ 5];
  MM  [1] = str[ 6];
  MM  [2] = '\0';
  DD  [0] = str[ 8];
  DD  [1] = str[ 9];
  DD  [2] = '\0';
  hh  [0] = str[11];
  hh  [1] = str[12];
  hh  [2] = '\0';
  mm  [0] = str[14];
  mm  [1] = str[15];
  mm  [2] = '\0';
  ss  [0] = str[17];
  ss  [1] = str[18];
  ss  [2] = '\0';  
  msec[0] = str[20];
  msec[1] = str[21];
  msec[2] = str[22];
  msec[3] = '\0';
  usec[0] = str[23];
  usec[1] = str[24];
  usec[2] = str[25];
  usec[3] = '\0';
  nsec[0] = str[26];
  nsec[1] = str[27];
  nsec[2] = str[28];
  nsec[3] = '\0';

  return CDF_TT2000_from_UTC_parts((double)atoi(YYYY),
                                   (double)atoi(MM),
                                   (double)atoi(DD),
                                   (double)atoi(hh),
                                   (double)atoi(mm),
                                   (double)atoi(ss),
                                   (double)atoi(msec),
                                   (double)atoi(usec),
                                   (double)atoi(nsec));
}

DTIME DTIME__MAKE_FROM_TEXT(const CHAR *text){
  return DTIME__MAKE_FROM_T2000(T2000__MAKE_FROM_TEXT(text));
}
