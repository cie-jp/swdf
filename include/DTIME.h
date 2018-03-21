/***************************************************************** 
 *
 * 時刻
 *
 *
 *                           Created  by Mamoru Ota (2018/03/22)
 * 
 *****************************************************************/

#ifndef _DTIME_H_INCLUDE_
#define _DTIME_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include"DATATYPE.h"

  typedef struct{
    INT2  YYYY;
    INT1    MM;
    INT1    DD;
    INT1    hh;
    INT1    mm;
    INT1    ss;
    INT2  msec;
    INT2  usec;
    INT2  nsec;
  }DTIME;

  void  DTIME__PRINT    (DTIME epoch,FILE *fp);
  T2000 T2000__MAKE_FROM_DTIME(DTIME epoch);
  DTIME DTIME__MAKE_FROM_T2000(T2000 t2000);
  T2000 T2000__NOW_JST();
  DTIME DTIME__NOW_JST();

  // 指定フォーマット
  //  YYYY-MM-DD hh:mm:ss.mmmuuunnn (終端文字を含めて30文字)
  //  2000-01-01 00:00:00.000000000 (規定値)
  T2000 T2000__MAKE_FROM_TEXT(const CHAR *text);
  DTIME DTIME__MAKE_FROM_TEXT(const CHAR *text);
  
#ifdef __cplusplus
}
#endif

#endif
