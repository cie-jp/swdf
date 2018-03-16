/***************************************************************** 
 *
 * OMP
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _OMP_H_INCLUDE_
#define _OMP_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Orthogonal Matching Pursuit
//x[n]    : 原信号
//D[n][m] : 観測行列 [d1 d2 d3 ... dn]'
//y[m]    : 観測信号  y = D * x
//n       : 原信号の次元
//m       : 観測ベクトルの次元
//s       : xの非零要素の上限値
//(注意) Dの各行ベクトルは全てl2ノルムで規格化してから使用すること. 
void orthogonal_matching_pursuit(double *x,double *D,double *y,int n,int m,int s);

void orthogonal_matching_pursuit_positive(double *x,double *D,double *y,int n,int m,int s);

#ifdef __cplusplus
}
#endif
  
#endif
