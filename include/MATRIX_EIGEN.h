/***************************************************************** 
 *
 * 行列の固有値分解
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _MATRIX_EIGEN_H_INCLUDE_
#define _MATRIX_EIGEN_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

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
  // について, 3重対角行列
  //            | t0[0]  t1[0]     0      0  ...         0          0  |
  //            | t1[0]  t0[1]  t1[1]     0  ...         .          .  |
  //            |    0   t1[1]  t0[2]  t1[2] ...         .          .  |
  // B^{T}B   = |    0      0   t1[2]  t0[3] ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...  t1[n - 3]         0  | 
  //            |    0      0      0      0  ...  t0[n - 2]  t1[n - 2] | 
  //            |    0      0      0      0  ...  t1[n - 2]  t0[n - 1] |
  // のT0, T1を計算する. 
  // *******************************************************************
  void REAL__MATRIX_BTB(REAL t0[],//(out)[n]     : 3重対角行列の対角成分
                        REAL t1[],//(out)[n - 1] : 3重対角行列の非対角成分
                        REAL b0[],//(in) [n]     : 2重対角行列の対角成分
                        REAL b1[],//(in) [n - 1] : 2重対角行列の非対角成分
                        INT  n);  //(in)         : 2重対角行列の次元数

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
  // について, 3重対角行列
  //            | t0[0]  t1[0]     0      0  ...         0          0  |
  //            | t1[0]  t0[1]  t1[1]     0  ...         .          .  |
  //            |    0   t1[1]  t0[2]  t1[2] ...         .          .  |
  // BB^{T}   = |    0      0   t1[2]  t0[3] ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...  t1[n - 3]         0  | 
  //            |    0      0      0      0  ...  t0[n - 2]  t1[n - 2] | 
  //            |    0      0      0      0  ...  t1[n - 2]  t0[n - 1] |
  // のt0, t1を計算する. 
  // *******************************************************************
  void REAL__MATRIX_BBT(REAL t0[],//(out)[n]     : 3重対角行列の対角成分
                        REAL t1[],//(out)[n - 1] : 3重対角行列の非対角成分
                        REAL b0[],//(in) [n]     : 2重対角行列の対角成分
                        REAL b1[],//(in) [n - 1] : 2重対角行列の非対角成分
                        INT  n);  //(in)         : 2重対角行列の次元数

  // *******************************************************************
  // 実対称3重対角行列
  //
  //            | t0[0]  t1[0]     0      0  ...         0          0  |
  //            | t1[0]  t0[1]  t1[1]     0  ...         .          .  |
  //            |    0   t1[1]  t0[2]  t1[2] ...         .          .  |
  // T        = |    0      0   t1[2]  t0[3] ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...  t1[n - 3]         0  | 
  //            |    0      0      0      0  ...  t0[n - 2]  t1[n - 2] | 
  //            |    0      0      0      0  ...  t1[n - 2]  t0[n - 1] |
  //
  // のQR分解(T = QR)を行う. 上三角行列Rは, 
  //
  //            | r0[0]  r1[0]  r2[0]     0  ...         0          0  |
  //            |    0   r0[1]  r1[1]  r2[1] ...         .          .  |
  //            |    0      0   r0[2]  r1[2] ...         .          .  |
  // R        = |    0      0      0   r0[3] ...         .          .  |
  //            |    .      .      .      .       r2[n - 4]         0  |
  //            |    0      0      0      0  ...  r1[n - 3]  r2[n - 3] | 
  //            |    0      0      0      0  ...  r0[n - 2]  r1[n - 2] | 
  //            |    0      0      0      0  ...         0   r0[n - 1] |
  //  
  // となっており, 直交行列Qは,
  //
  // Q        = P[0]^{T}P[1]^{T}P[2]^{T}...P[n - 2]^{T}
  //
  // で与えられる. 
  // ここで, 
  //
  //            |  c[0]   s[0]     0      0  ...         0          0  |
  //            | -s[0]   c[0]     0      0  ...         .          .  |
  //            |    0      0      1      0  ...         .          .  |
  // P[0]     = |    0      0      0      1  ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...         0          0  | 
  //            |    0      0      0      0  ...         1          0  | 
  //            |    0      0      0      0  ...         0          1  |
  //
  //            |    1      0      0      0  ...         0          0  |
  //            |         c[1]   s[1]     0  ...         .          .  |
  //            |    0   -s[1]   c[1]     0  ...         .          .  |
  // P[1]     = |    0      0      0      1  ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...         0          0  | 
  //            |    0      0      0      0  ...         1          0  | 
  //            |    0      0      0      0  ...         0          1  |
  // ...
  //
  //            |    1      0      0      0  ...         0          0  |
  //            |           1      0      0  ...         .          .  |
  //            |    0      0      1      0  ...         .          .  |
  // P[n - 2] = |    0      0      0      1  ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...         0          0  | 
  //            |    0      0      0      0  ...   c[n - 2]   s[n - 2] | 
  //            |    0      0      0      0  ...  -s[n - 2]   c[n - 2] |
  //
  // である. 
  // 
  // *******************************************************************
  void REAL__MATRIX_QR_TRI(REAL c [],//(out)[n - 1] : 直交行列の情報を表すパラメータ
                           REAL s [],//(out)[n - 1] : 直交行列の情報を表すパラメータ
                           REAL r0[],//(out)[n]     : 上三角行列の対角成分
                           REAL r1[],//(out)[n - 1] : 上三角行列の非対角成分1
                           REAL r2[],//(out)[n - 2] : 上三角行列の非対角成分2 (r2の計算が不要な場合はNULLを入れる)
                           REAL t0[],//(in) [n]     : 3重対角行列の対角成分
                           REAL t1[],//(in) [n - 1] : 3重対角行列の非対角成分
                           INT  n);  //(in)         : 3重対角行列の次元数

  // *******************************************************************
  // 実対称3重対角行列
  //
  //            | t0[0]  t1[0]     0      0  ...         0          0  |
  //            | t1[0]  t0[1]  t1[1]     0  ...         .          .  |
  //            |    0   t1[1]  t0[2]  t1[2] ...         .          .  |
  // T        = |    0      0   t1[2]  t0[3] ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...  t1[n - 3]         0  | 
  //            |    0      0      0      0  ...  t0[n - 2]  t1[n - 2] | 
  //            |    0      0      0      0  ...  t1[n - 2]  t0[n - 1] |
  //
  // のQR分解(T = QR)により得られるRとQ(REAL__MATRIX_QR_TRIにより計算可能)からRQを計算する. 
  // すなわち
  //            | u0[0]  u1[0]     0      0  ...         0          0  |
  //            | u1[0]  u0[1]  u1[1]     0  ...         .          .  |
  //            |    0   u1[1]  u0[2]  u1[2] ...         .          .  |
  // RQ       = |    0      0   u1[2]  u0[3] ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...  u1[n - 3]         0  | 
  //            |    0      0      0      0  ...  u0[n - 2]  u1[n - 2] | 
  //            |    0      0      0      0  ...  u1[n - 2]  u0[n - 1] |
  // を返す. 
  // *******************************************************************
  void REAL__MATRIX_RQ_TRI(REAL u0[],//(out)[n]     : 3重対角行列RQの対角成分
                           REAL u1[],//(out)[n - 1] : 3重対角行列RQの非対角成分
                           REAL c [],//(in) [n - 1] : QR分解の直交行列Qの情報を表すパラメータ
                           REAL s [],//(in) [n - 1] : QR分解の直交行列Qの情報を表すパラメータ
                           REAL r0[],//(in) [n]     : QR分解の上三角行列Rの対角成分
                           REAL r1[],//(in) [n - 1] : QR分解の上三角行列Rの非対角成分1
                           INT  n);  //(in)         : 行列の次元数

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
                                   REAL  a2);

  // *******************************************************************
  // 実対称3重対角行列
  //
  //            | t0[0]  t1[0]     0      0  ...         0          0  |
  //            | t1[0]  t0[1]  t1[1]     0  ...         .          .  |
  //            |    0   t1[1]  t0[2]  t1[2] ...         .          .  |
  // T        = |    0      0   t1[2]  t0[3] ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...  t1[n - 3]         0  | 
  //            |    0      0      0      0  ...  t0[n - 2]  t1[n - 2] | 
  //            |    0      0      0      0  ...  t1[n - 2]  t0[n - 1] |
  //
  // の固有値分解T = U diag(l) U^{T}を減次付WilkinsonシフトQR法により計算する.
  // ここで, Uは直交行列を表し,
  // lはTの固有値からなるベクトルである. 
  // また,
  //            |  l[0]     0      0      0  ...         0          0  |
  //            |    0    l[1]     0      0  ...         .          .  |
  //            |    0      0    l[2]     0  ...         .          .  |
  // diag(l)  = |    0      0      0      0  ...         .          .  |
  //            |    .      .      .      .              0          0  |
  //            |    0      0      0      0  ...         0          0  | 
  //            |    0      0      0      0  ...   l[n - 2]         0  | 
  //            |    0      0      0      0  ...         0    l[n - 1] |
  // である. また, |l[0]| > |l[1]| > |l[2]| > ... > |l[n - 1]|である.  
  // 
  // l[k]に対応する固有ベクトルv[k]は,
  //
  //            | U[     0  * n + k] |
  //            | U[     1  * n + k] |
  //            | U[     2  * n + k] |
  // v[k]     = | U[     3  * n + k] |
  //            |           .        |
  //            | U[(n - 2) * n + k] |
  //            | U[(n - 1) * n + k] |
  //
  // であり, 大きさは1で規格化されており, 各固有ベクトルは互いに直交している. 
  //
  // *******************************************************************
  void REAL__MATRIX_EIGENVALUE_DECOMPOSITION_TRI(REAL U [],//(out)[n * n] : 直交行列
                                                 REAL t0[],//(io) [n]     : 実対称3重対角行列の対角成分   (固有値配列lが返される)
                                                 REAL t1[],//(io) [n - 1] : 実対称3重対角行列の非対角成分 (破壊される)
                                                 INT  n);  //(in)         : 行列の次元数

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
                           INT  n);  //(in)         : 2重対角行列の次元数  

  // **********************************************************
  // row行col列の実・複素行列Aに対して特異値分解を行う.
  //
  // A       = U diag(s) V^{dag} 
  //
  // A[i][j] = sum _k s[k]U[i][k]conj(V[j][k]) (成分表示)
  //
  // U^{dag} U = I_{dim}, V^{dag} V = I_{dim} 
  //
  // dim = min(row,col)
  //
  // s[0] > s[1] > ... s[dim - 1] > 0
  // **********************************************************
  void REAL__MATRIX_SVD(REAL s[], //(out)[dim]       : 特異値配列
                        REAL U[], //(out)[row * dim] : 左特異ベクトル群
                        REAL V[], //(out)[col * dim] : 右特異ベクトル群
                        REAL A[], //(in) [row * col] : 特異値分解の対象とする行列
                        INT  row, //(in)             : 行列の行数
                        INT  col);//(in)             : 行列の列数

  void COMP__MATRIX_SVD(REAL s[], //(out)[dim]       : 特異値配列
                        COMP U[], //(out)[row * dim] : 左特異ベクトル群
                        COMP V[], //(out)[col * dim] : 右特異ベクトル群
                        COMP A[], //(in) [row * col] : 特異値分解の対象とする行列
                        INT  row, //(in)             : 行列の行数
                        INT  col);//(in)             : 行列の列数
  
#ifdef __cplusplus
}
#endif
  
#endif
