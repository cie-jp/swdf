/***************************************************************** 
 *
 * Toeplitz行列関係
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _TOEPLITZ_H_INCLUDE_
#define _TOEPLITZ_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<math.h>

/*
T, bを与えたときに, Tx = bの解となるxをLevison-Durbin Algorithmを用いて計算する. 
Tはn x n 実数対称正定値Toeplitz行列であり, 各要素はn次元ベクトルr = [r0 r1 ... r_{n-1}]^Tで与えられる. 
    +-                                          -+
    |r0      r1      r2      ...          r_{n-1}|
    |r1      r0      r1      ...          r_{n-2}|
    |r2      r1      r0      r1           r_{n-3}|
T = |                                            |
    |r_{n-2}                 r1    r0     r1     |
    |r_{n-1}                 r2    r1     r0     |
    +-                                          -+

x, bはそれぞれn 次元実数ベクトルである. 
*/

void symmetric_toeplitz_solver(double x[],double r[],double b[],int n);

/*
Tを与えたときに, その行列式の自然対数を返す. 
Tはn x n 実数対称正定値Toeplitz行列であり, 各要素はn次元ベクトルr = [r0 r1 ... r_{n-1}]^Tで与えられる. 
    +-                                          -+
    |r0      r1      r2      ...          r_{n-1}|
    |r1      r0      r1      ...          r_{n-2}|
    |r2      r1      r0      r1           r_{n-3}|
T = |                                            |
    |r_{n-2}                 r1    r0     r1     |
    |r_{n-1}                 r2    r1     r0     |
    +-                                          -+
 */
double symmetric_toeplitz_log_determinant(double r[],int n);

#ifdef __cplusplus
}
#endif

  
#endif
