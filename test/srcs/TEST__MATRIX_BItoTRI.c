/*****************************************************************
 *
 * 2重対角行列BからB^{T}Bを計算するプログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MATRIX.h"
#include"RANDOM.h"

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
// B^{T}B   = |    0      0   T1[2]  T0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  T1[n - 3]         0  | 
//            |    0      0      0      0  ...  T0[n - 2]  T1[n - 2] | 
//            |    0      0      0      0  ...  T1[n - 2]  T0[n - 1] |
// のT0, T1を計算する. 
// *******************************************************************
void REAL__MATRIX_BTB(REAL T0[],//(out)[n]     : 3重対角行列の対角成分
                      REAL T1[],//(out)[n - 1] : 3重対角行列の非対角成分
                      REAL B0[],//(in) [n]     : 2重対角行列の対角成分
                      REAL B1[],//(in) [n - 1] : 2重対角行列の非対角成分
                      INT  n){  //(in)         : 2重対角行列の次元数
  INT i;
  
  T0[0] = REAL__MUL(B0[0],B0[0]);
  for(i = 1;i < n    ;i++){
    T0[i] = REAL__ADD(REAL__MUL(B0[i],B0[i]),REAL__MUL(B1[i - 1],B1[i - 1]));
  }

  for(i = 0;i < n - 1;i++){
    T1[i] = REAL__MUL(B0[i],B1[i]);
  }  
}

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

#define dim (10)


int main(void){
  REAL   B[dim][dim],BT[dim][dim],BTB[dim][dim],BBT[dim][dim];
  RANDOM rnd;
  INT4   i,j;
  REAL   AMP,COS,SIN;

  REAL   B0[dim];
  REAL   B1[dim - 1];
  REAL   T0[dim];
  REAL   T1[dim - 1];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      B[i][j] = REAL__ZERO();      
    }
  }
  for(i = 0;i < dim;i++){
    B[i][i] = RANDOM__NORMAL(&rnd,0.0,1.0);
    B0[i]   = B[i][i];
  }
  for(i = 0;i < dim - 1;i++){
    B[i][i + 1] = RANDOM__NORMAL(&rnd,0.0,1.0);
    B1[i]       = B[i][i + 1];
  }
  
  REAL__MATRIX_PRINT(&B[0][0],dim,dim,stderr);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      BT[i][j] = B[j][i];
    }
  }
  REAL__MATRIX_MUL(&BTB[0][0],&BT[0][0],dim,dim,&B [0][0],dim,dim);
  REAL__MATRIX_MUL(&BBT[0][0],&B [0][0],dim,dim,&BT[0][0],dim,dim);

  REAL__MATRIX_PRINT(&BTB[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&BBT[0][0],dim,dim,stderr);

  REAL__MATRIX_BTB(T0,T1,B0,B1,dim);
  for(i = 0;i < dim - 1;i++){
    printf("%f %f\n",T0[i],T1[i]);
  }
  printf("%f\n",T0[dim - 1]);


  REAL__MATRIX_BBT(T0,T1,B0,B1,dim);
  for(i = 0;i < dim - 1;i++){
    printf("%f %f\n",T0[i],T1[i]);
  }
  printf("%f\n",T0[dim - 1]);

  return 0;
}
