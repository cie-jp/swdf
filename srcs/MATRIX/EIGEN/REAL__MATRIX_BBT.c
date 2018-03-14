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
//            | B0[0]  B1[0]     0      0  ...         0          0  |
//            |    0   B0[1]  B1[1]     0  ...         .          .  |
//            |    0      0   B0[2]  B1[2] ...         .          .  |
// B        = |    0      0      0   B0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0       B1[n - 3]         0  |
//            |    0      0      0      0  ...  B0[n - 2]  B1[n - 2] | 
//            |    0      0      0      0  ...         0   B0[n - 1] |
// について, 3重対角行列
//            | T0[0]  T1[0]     0      0  ...         0          0  |
//            | T1[0]  T0[1]  T1[1]     0  ...         .          .  |
//            |    0   T1[1]  T0[2]  T1[2] ...         .          .  |
// BB^{T}   = |    0      0   T1[2]  T0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  T1[n - 3]         0  | 
//            |    0      0      0      0  ...  T0[n - 2]  T1[n - 2] | 
//            |    0      0      0      0  ...  T1[n - 2]  T0[n - 1] |
// のT0, T1を計算する. 
// *******************************************************************
void REAL__MATRIX_BBT(REAL T0[],//(out)[n]     : 3重対角行列の対角成分
                      REAL T1[],//(out)[n - 1] : 3重対角行列の非対角成分
                      REAL B0[],//(in) [n]     : 2重対角行列の対角成分
                      REAL B1[],//(in) [n - 1] : 2重対角行列の非対角成分
                      INT  n){  //(in)         : 2重対角行列の次元数
  INT i;
  
  for(i = 0;i < n - 1;i++){
    T0[i] = REAL__ADD(REAL__MUL(B0[i],B0[i]),REAL__MUL(B1[i],B1[i]));
  }
  T0[n - 1] = REAL__MUL(B0[n - 1],B0[n - 1]);

  for(i = 0;i < n - 1;i++){
    T1[i] = REAL__MUL(B0[i + 1],B1[i]);
  }  
}
