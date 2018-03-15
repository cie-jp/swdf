/***************************************************************** 
 *
 * 行列の固有値計算関係
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"MATRIX.h"

// *******************************************************************
// 2次実対称行列
//
// A = | a0 a1 |
//     | a1 a2 | 
// の二つの固有値emax,emin(emax > emin)を返す.  
// *******************************************************************
void REAL__MATRIX_EIGENVALUES_2D(REAL *emax,
                                 REAL *emin,
                                 REAL  a0,
                                 REAL  a1,
                                 REAL  a2){
  REAL mu;
  REAL d;
  
  mu    = REAL__MUL(REAL__ADD(a0,a2),REAL__TWO());
  d     = REAL__MUL(REAL__SQRT(REAL__ADD(REAL__NORM(REAL__SUB(a0,a2)),REAL__NORM(REAL__MUL(REAL__TWO(),a1)))),REAL__TWO());
  *emax = REAL__ADD(mu,d);
  *emin = REAL__SUB(mu,d);
}
