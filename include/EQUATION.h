/***************************************************************** 
 *
 * 方程式関連
 *
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#ifndef _EQUATION_H_INCLUDE_
#define _EQUATION_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"COMPLEX.h"

// =================================================================================
// DKA法によりn次方程式の解を計算する
// f(z) = a_{0} + a_{1}z + a_{2}z^{2} + ... + a_{n - 1}z^{n - 1} + a_{n}z^{n} = 0
//       (a_{n} != 0.0)
// =================================================================================
INT4 EQUATION__SOLVE_DKA(COMPLEX z[],          //(out)複素解  [n]
			 COMPLEX a[],          //(in) 複素係数[1 + n]
			 INT4    n,            //(in) 次数
			 INT4    max_iteration,//(in) Newton法の反復回数の上限
			 REAL8   eps);         //(in) Newton法の許容絶対誤差

#ifdef __cplusplus
}
#endif

#endif
