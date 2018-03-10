/***************************************************************** 
 *
 * 行列計算
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include"DATATYPE.h"
#include"COMPLEX.h"
#include"MEMORY.h"
  
  typedef REAL8   REAL;//  実行列要素のデータ型
  typedef COMPLEX COMP;//複素行列要素のデータ型
  typedef INT4    INT ;//行列の添え字に用いるデータ型

  REAL REAL__ZERO    ();
  REAL REAL__ONE     ();
  REAL REAL__POSITIVE(REAL x);
  REAL REAL__NEGATIVE(REAL x);
  REAL REAL__ABS     (REAL x);
  INT  REAL__EQ      (REAL x,REAL y);
  INT  REAL__NEQ     (REAL x,REAL y);
  REAL REAL__ADD     (REAL x,REAL y);
  REAL REAL__SUB     (REAL x,REAL y);
  REAL REAL__MUL     (REAL x,REAL y);
  REAL REAL__DIV     (REAL x,REAL y);
  REAL REAL__FMA     (REAL x,REAL y,REAL z);

  void REAL__PRINT   (REAL x,FILE *fp);
  
  INT  REAL__GT      (REAL x,REAL y);
  INT  REAL__GE      (REAL x,REAL y);
  INT  REAL__LT      (REAL x,REAL y);
  INT  REAL__LE      (REAL x,REAL y);
  
  COMP COMP__ZERO    ();
  COMP COMP__ONE     ();
  COMP COMP__POSITIVE(COMP x);
  COMP COMP__NEGATIVE(COMP x);
  REAL COMP__ABS     (COMP x);
  INT  COMP__EQ      (COMP x,COMP y);
  INT  COMP__NEQ     (COMP x,COMP y);
  COMP COMP__ADD     (COMP x,COMP y);
  COMP COMP__SUB     (COMP x,COMP y);
  COMP COMP__MUL     (COMP x,COMP y);
  COMP COMP__DIV     (COMP x,COMP y);
  COMP COMP__FMA     (COMP x,COMP y,COMP z);

  void COMP__PRINT   (COMP x,FILE *fp);

  INT  REAL__MATRIX_LU_DECOMPOSITION (REAL A[],INT  n);
  INT  COMP__MATRIX_LU_DECOMPOSITION (COMP A[],INT  n);

  INT  REAL__MATRIX_LUP_DECOMPOSITION(REAL A[],INT  P[],INT  n);
  INT  COMP__MATRIX_LUP_DECOMPOSITION(COMP A[],INT  P[],INT  n);

  INT  REAL__MATRIX_INV              (REAL A[],INT  n);
  INT  COMP__MATRIX_INV              (COMP A[],INT  n);

  INT  REAL__MATRIX_SOLVE            (REAL x[],REAL A[],REAL b[],INT  n);
  INT  COMP__MATRIX_SOLVE            (COMP x[],COMP A[],COMP b[],INT  n);

  void REAL__MATRIX_PRINT            (REAL A[],INT row,INT col,FILE *fp);
  void COMP__MATRIX_PRINT            (COMP A[],INT row,INT col,FILE *fp);
  
  // ***********************************
  // 実行列の構造体宣言
  // ***********************************
  typedef struct{
    REAL   *dat;//データポインタ
    INT     row;//行数
    INT     col;//列数
  }RMATRIX;
  
  // ***********************************
  // 実行列の初期化(ゼロ埋めされる)
  // ***********************************
  void  RMATRIX__INITIALIZE(RMATRIX *mat,INT row,INT col);

  // ***********************************
  // 実行列の複製
  // ***********************************
  void  RMATRIX__CLONE     (RMATRIX *mat,RMATRIX *dst);

  // ***********************************
  // 実行列の破棄
  // ***********************************
  void  RMATRIX__FINALIZE  (RMATRIX *mat);

  // ***********************************
  // 実行列のリサイズ(ゼロ埋めされる)
  // ***********************************
  void  RMATRIX__RESIZE    (RMATRIX *mat,INT row,INT col);

  // ***********************************
  // 実行列のデータポインタの取得
  // ***********************************
  REAL *RMATRIX__GET_DATA  (RMATRIX *mat);

  // ***********************************
  // 実行列の行数の取得
  // ***********************************
  INT   RMATRIX__GET_ROW   (RMATRIX *mat);

  // ***********************************
  // 実行列の列数の取得
  // ***********************************
  INT   RMATRIX__GET_COL   (RMATRIX *mat);

  // ***********************************
  // 実行列の情報の表示
  // ***********************************
  void  RMATRIX__SHOW_INFO (RMATRIX *mat,FILE *fp);

  // ***********************************
  // 実行列のゼロ埋め処理
  // ***********************************
  void  RMATRIX__ZEROFILL  (RMATRIX *mat);

  // ***********************************
  // 実行列のデータコピー
  // ***********************************
  void  RMATRIX__DATACOPY  (RMATRIX *mat,RMATRIX *src);

  // ***********************************
  // 実行列の設定(単位行列)
  //   対角成分 : 1
  // 非対角成分 : 0
  // ***********************************
  void  RMATRIX__SET_IDENTITY(RMATRIX *mat);
  
  // ***********************************
  // 実行列の設定
  // 全成分     : val
  // ***********************************
  void  RMATRIX__SET_VALUE   (RMATRIX *mat,REAL val);

  // ***********************************
  // 実行列の設定
  // 全成分     : 標準正規分布に従う乱数
  // ***********************************
  void  RMATRIX__SET_RANDOM  (RMATRIX *mat);

  // ***********************************
  // 実行列の設定
  // DCT変換行列
  // ***********************************
  void  RMATRIX__SET_DCT     (RMATRIX *mat);  
  
  // ***********************************
  // 実行列の設定
  // IDCT変換行列(正方行列)
  // ***********************************
  void  RMATRIX__SET_IDCT    (RMATRIX *mat);  

  // ***********************************
  // Cに+Aを代入する. 
  // C_{i,j} = +A_{i,j}
  // ***********************************
  RMATRIX RMATRIX__UPLUS(RMATRIX A);

  // ***********************************
  // 実行列の要素ごとの加算結果の格納
  // C_{i,j} = A_{i,j} + B_{i,j}
  // ***********************************
  void  RMATRIX__SET_PLUS    (RMATRIX *C,RMATRIX *A,RMATRIX *B);

  // ***********************************
  // 実行列の減算結果の格納
  // C <= A - B
  // ***********************************
  void  RMATRIX__SET_MINUS(RMATRIX *C,RMATRIX *A,RMATRIX *B);
  void  RMATRIX__SET_UMINUS(RMATRIX *C,RMATRIX *A,RMATRIX *B);

  // ***********************************
  // 実行列の乗算結果の格納
  // C <= A * B
  // ***********************************
  void  RMATRIX__SET_MUL(RMATRIX *C,RMATRIX *A,RMATRIX *B);

  // ***********************************
  // 実行列の要素ごとの乗算結果の格納
  // C_{i,j} <= A_{i,j} * B_{i,j}
  // ***********************************
  void  RMATRIX__SET_TIMES(RMATRIX *C,RMATRIX *A,RMATRIX *B);

  // ***********************************
  // 実行列の要素ごとの右除算結果の格納
  // C_{i,j} <= A_{i,j} / B_{i,j}
  // ***********************************
  void RMATRIX__SET_RDIVIDE(RMATRIX *C,RMATRIX *A,RMATRIX *B);

  // ***********************************
  // 実行列の要素ごとの左除算結果の格納
  // C_{i,j} <= B_{i,j} \ A_{i,j}
  // ***********************************
  void RMATRIX__SET_LDIVIDE(RMATRIX *C,RMATRIX *B,RMATRIX *A);
  

#ifdef __cplusplus
}
#endif
  
#endif
