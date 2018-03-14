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
// 実2重対角行列
//            | b0[0]  b1[0]     0      0  ...         0          0  |
//            |    0   b0[1]  b1[1]     0  ...         .          .  |
//            |    0      0   b0[2]  b1[2] ...         .          .  |
// B        = |    0      0      0   b0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0       b1[n - 3]         0  |
//            |    0      0      0      0  ...  b0[n - 2]  b1[n - 2] | 
//            |    0      0      0      0  ...         0   b0[n - 1] |
// について, その特異値分解
// B = U diag(s) V^{T}を計算する.
// ここで, sは特異値からなる配列であり, 
//            |  s[0]     0      0      0  ...         0          0  |
//            |    0    s[1]     0      0  ...         .          .  |
//            |    0      0    s[2]     0  ...         .          .  |
// diag(s)  = |    0      0      0      0  ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...         0          0  | 
//            |    0      0      0      0  ...   s[n - 2]         0  | 
//            |    0      0      0      0  ...         0    s[n - 1] |
// である. また, s[0] > s[1] > s[2] > ... > s[n - 1] > 0である.
//
// s[k]に対応する左特異ベクトルu[k]は,
//
//            | U[     0  * n + k] |
//            | U[     1  * n + k] |
//            | U[     2  * n + k] |
// u[k]     = | U[     3  * n + k] |
//            |           .        |
//            | U[(n - 2) * n + k] |
//            | U[(n - 1) * n + k] |
//
// であり, 大きさは1で規格化されており, 各左特異ベクトルは互いに直交している.
// 同様に, s[k]に対応する左特異ベクトルv[k]は,
//
//            | V[     0  * n + k] |
//            | V[     1  * n + k] |
//            | V[     2  * n + k] |
// v[k]     = | V[     3  * n + k] |
//            |           .        |
//            | V[(n - 2) * n + k] |
//            | V[(n - 1) * n + k] |
//
// であり, 大きさは1で規格化されており, 各右特異ベクトルは互いに直交している.
//
// *******************************************************************
void REAL__MATRIX_SVD_BI(REAL s [],//(out)[n]     : 特異値配列
                         REAL U [],//(out)[n * n] : 左特異ベクトル群(直交行列)
                         REAL V [],//(out)[n * n] : 右特異ベクトル群(直交行列)
                         REAL b0[],//(in) [n]     : 2重対角行列の対角成分
                         REAL b1[],//(in) [n - 1] : 2重対角行列の非対角成分
                         INT  n){  //(in)         : 2重対角行列の次元数
  void *mem;
  REAL *t0;//[n]
  REAL *t1;//[n - 1]
  INT   i,j;
  
  // ******************************************************************
  //  1. 作業変数のメモリ確保
  // ******************************************************************
  if((mem = malloc(sizeof(REAL) *  n
                 + sizeof(REAL) * (n - 1))) == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  // ******************************************************************
  //  2. メモリ割り当て
  // ******************************************************************
  t0 = (REAL*)mem;
  t1 = (REAL*)&t0[n];

  // ******************************************************************
  //  3. 2重対角行列BからB^{T}Bを計算
  // ******************************************************************
  REAL__MATRIX_BTB(t0,t1,b0,b1,n);
  
  // ******************************************************************
  //  4. 3重対角行列B^{T}Bの固有値分解を実行(Vに右特異ベクトル群が格納される)
  // ******************************************************************
  REAL__MATRIX_EIGENVALUE_DECOMPOSITION_TRI(V,t0,t1,n);

  // ******************************************************************
  //  5. 固有値から特異値を計算
  // ******************************************************************
  for(i = 0;i < n;i++){
    s[i] = REAL__SQRT(t0[i]);
  }
  
  // ******************************************************************
  //  6. 左特異ベクトル群の計算
  // ******************************************************************
  for(i = 0;i < n - 1;i++){
    for(j = 0;j < n;j++){
      U[i * n + j] = REAL__DIV(REAL__ADD(REAL__MUL(b0[i],V[i * n + j]),REAL__MUL(b1[i],V[(i + 1) * n + j])),s[j]);
    }
  }
    for(j = 0;j < n;j++){
      U[i * n + j] = REAL__DIV(          REAL__MUL(b0[i],V[i * n + j])                                     ,s[j]);
    }
  
  // ******************************************************************
  //  7. 作業変数のメモリ解放
  // ******************************************************************
  free(mem);
}
