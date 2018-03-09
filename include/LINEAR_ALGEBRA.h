/***************************************************************** 
 *
 * 線形代数
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _LINEAR_ALGEBRA_H_INCLUDE_
#define _LINEAR_ALGEBRA_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//LU matrix factorization
//Aは正方行列データ配列
//Pは要素数nの配列でLU分解でのピボット選択で行った置換の結果を格納する. 
//Pの初期化は必要ない. 
//nは正方行列の次元数 A in R(n x n)
int la_lu(double *A,int P[],int n);

//equations solver
int la_solve(double x[],double *A,double b[],int n);

//trace(sum of diagonal elements)
int la_trace(double *res,double *A,int n);

//matrix determinant  
int la_det(double *res,double *A,int n);

//inverse matrix
int la_inv(double *A,int n);

//tridiagonalize
int la_tridiagonalize(double *A,double *P,int n);

//eigenvalues and eigenvectors
int la_eig(double *A,double *P,int n);

//singular value decomposition
int la_svd(double *A,double *U,double *V,int row,int col);

/**************************************************************************/
//int  la_pca(double X[],int n,int m,double M[],double P[],double L[],int mode);
//行列Xの分散共分散行列に対して主成分分析を行う. X = X'tP + M
//     X[] : n x m 入力行列、主成分が格納される.
//     n   : 行数
//     m   : 列数
//     M[] : m次元平均ベクトル、NULLの場合は相関行列に対して実行する.
//     P[] : m x m 基底行列
//     L[] : m個の固有値を格納する.必要ない場合はNULLでよい.
//     mode: 0 : 通常の主成分分析 1 : 白色化処理を加える.
//return   : 正常終了時に行列の階数、異常終了時に-1を返す.
/**************************************************************************/
int  la_pca(double X[],int n,int m,double M[],double P[],double L[],int mode);

/**************************************************************************/
//int  la_ica(double X[],int n,int m,double M[],double P[]);
//行列Xの独立成分分析を行う. X = X'tP + M
//     X[] : n x m 入力行列
//     n   : 行数
//     m   : 列数
//     M[] : m次元平均ベクトル
//     P[] : m x m 基底行列
//return   : 正常終了時に0、異常終了時に-1を返す.
/**************************************************************************/
int  la_ica(double X[],int n,int m,double M[],double P[]);

#ifdef __cplusplus
}
#endif

#endif
