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
// 実対称3重対角行列
//
//            | T0[0]  T1[0]     0      0  ...         0          0  |
//            | T1[0]  T0[1]  T1[1]     0  ...         .          .  |
//            |    0   T1[1]  T0[2]  T1[2] ...         .          .  |
// T        = |    0      0   T1[2]  T0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  T1[n - 3]         0  | 
//            |    0      0      0      0  ...  T0[n - 2]  T1[n - 2] | 
//            |    0      0      0      0  ...  T1[n - 2]  T0[n - 1] |
//
// のQR分解(T = QR)を行う. 上三角行列Rは, 
//
//            | R0[0]  R1[0]  R2[0]     0  ...         0          0  |
//            |    0   R0[1]  R1[1]  R2[1] ...         .          .  |
//            |    0      0   R0[2]  R1[2] ...         .          .  |
// R        = |    0      0      0   R0[3] ...         .          .  |
//            |    .      .      .      .       R2[n - 4]         0  |
//            |    0      0      0      0  ...  R1[n - 3]  R2[n - 3] | 
//            |    0      0      0      0  ...  R0[n - 2]  R1[n - 2] | 
//            |    0      0      0      0  ...         0   R0[n - 1] |
//  
// となっており, 直交行列Qは,
//
// Q        = P[0]^{T}P[1]^{T}P[2]^{T}...P[n - 2]^{T}
//
// で与えられる. 
// ここで, 
//
//            |  C[0]   S[0]     0      0  ...         0          0  |
//            | -S[0]   C[0]     0      0  ...         .          .  |
//            |    0      0      1      0  ...         .          .  |
// P[0]     = |    0      0      0      1  ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...         0          0  | 
//            |    0      0      0      0  ...         1          0  | 
//            |    0      0      0      0  ...         0          1  |
//
//            |    1      0      0      0  ...         0          0  |
//            |         C[1]   S[1]     0  ...         .          .  |
//            |    0   -S[1]   C[1]     0  ...         .          .  |
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
//            |    0      0      0      0  ...   C[n - 2]   S[n - 2] | 
//            |    0      0      0      0  ...  -S[n - 2]   C[n - 2] |
//
// である. 
// 
// *******************************************************************
void REAL__MATRIX_QR_TRI(REAL C [],//(out)[n - 1] : 直交行列の情報を表すパラメータ
                         REAL S [],//(out)[n - 1] : 直交行列の情報を表すパラメータ
                         REAL R0[],//(out)[n]     : 上三角行列の対角成分
                         REAL R1[],//(out)[n - 1] : 上三角行列の非対角成分1
                         REAL R2[],//(out)[n - 2] : 上三角行列の非対角成分2 (R2の計算が不要な場合はNULLを入れる)
                         REAL T0[],//(in) [n]     : 3重対角行列の対角成分
                         REAL T1[],//(in) [n - 1] : 3重対角行列の非対角成分
                         INT  n){  //(in)         : 3重対角行列の次元数
  REAL L;
  INT  i;
  
  for(i = 0;i < n    ;i++){
    R0[i] = T0[i];
  }
  for(i = 0;i < n - 1;i++){
    R1[i] = T1[i];
  }

  for(i = 0;i < n - 2;i++){
    L         = REAL__SQRT(REAL__ADD(REAL__MUL(R0[i],R0[i]),REAL__MUL(T1[i],T1[i])));
    if(REAL__EQ(L,REAL__ZERO())){
      C[i   ] = REAL__ONE ();
      S[i   ] = REAL__ZERO();
    }else{
      C[i   ] = REAL__DIV(R0[i],L);
      S[i   ] = REAL__DIV(T1[i],L);
    }
    R0[i    ] = L;
    R0[i + 1] = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[i]),R1[i]),REAL__MUL(C[i],T0[i + 1]));
    R1[i    ] = REAL__ADD(REAL__MUL(               C[i] ,R1[i]),REAL__MUL(S[i],T0[i + 1]));
    R1[i + 1] = REAL__MUL(C[i],T1[i + 1]);
  }
    L         = REAL__SQRT(REAL__ADD(REAL__MUL(R0[i],R0[i]),REAL__MUL(T1[i],T1[i])));
    if(REAL__EQ(L,REAL__ZERO())){
      C[i   ] = REAL__ONE ();
      S[i   ] = REAL__ZERO();
    }else{
      C[i   ] = REAL__DIV(R0[i],L);
      S[i   ] = REAL__DIV(T1[i],L);
    }
    R0[i    ] = L;
    R0[i + 1] = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[i]),R1[i]),REAL__MUL(C[i],T0[i + 1]));
    R1[i    ] = REAL__ADD(REAL__MUL(               C[i] ,R1[i]),REAL__MUL(S[i],T0[i + 1]));  

  if(R2 != NULL){
    for(i = 0;i < n - 2;i++){
      R2[i] = REAL__MUL(S[i],T1[i + 1]);
    }
  }
}
