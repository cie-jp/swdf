/***************************************************************** 
 *
 * STATS 
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _STATS_H_INCLUDE_
#define _STATS_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"DATATYPE.h"

  // ========================================================
  // 配列要素の最小値を求める
  // mode = 0: min  x[n]
  // mode = 1: min  x[n]  s.t.  x[n]  >= 0.0
  // mode = 2: min  x[n]  s.t.  x[n]  >= DBL_MIN
  // mode = 3: min |x[n]|
  // mode = 4: min |x[n]| s.t. |x[n]| >= DBL_MIN
  // ========================================================
  REAL8 STATS__MIN(REAL8 x[],
		   INT4  num,
		   INT4  mode);
  
  // ========================================================
  // 配列要素の最大値を求める
  // mode = 0: max   x[n]
  // mode = 1: max  |x[n]|
  // mode = 2: max  -x[n]
  // ========================================================
  REAL8 STATS__MAX(REAL8 x[],
		   INT4  num,
		   INT4  mode);
  
  T2000 STATS__MIN_T2000(T2000 t[],
			 INT4  num);
  T2000 STATS__MAX_T2000(T2000 t[],
			 INT4  num);
  
#ifdef __cplusplus
}
#endif

#endif
