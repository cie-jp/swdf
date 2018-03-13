/*****************************************************************
 *
 * 実対称3重対角行列のQR分解
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
    C[i     ] = REAL__DIV(R0[i],L);
    S[i     ] = REAL__DIV(T1[i],L);
    R0[i    ] = L;
    R0[i + 1] = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[i]),R1[i]),REAL__MUL(C[i],T0[i + 1]));
    R1[i    ] = REAL__ADD(REAL__MUL(               C[i] ,R1[i]),REAL__MUL(S[i],T0[i + 1]));
    R1[i + 1] = REAL__MUL(C[i],T1[i + 1]);
  }
    L         = REAL__SQRT(REAL__ADD(REAL__MUL(R0[i],R0[i]),REAL__MUL(T1[i],T1[i])));
    C[i     ] = REAL__DIV(R0[i],L);
    S[i     ] = REAL__DIV(T1[i],L);
    R0[i    ] = L;
    R0[i + 1] = REAL__ADD(REAL__MUL(REAL__NEGATIVE(S[i]),R1[i]),REAL__MUL(C[i],T0[i + 1]));
    R1[i    ] = REAL__ADD(REAL__MUL(               C[i] ,R1[i]),REAL__MUL(S[i],T0[i + 1]));  

  if(R2 != NULL){
    for(i = 0;i < n - 2;i++){
      R2[i] = REAL__MUL(S[i],T1[i + 1]);
    }
  }
}

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
// のQR分解(T = QR)により得られるRとQ(REAL__MATRIX_QR_TRIにより計算可能)からRQを計算する. 
// すなわち
//            | U0[0]  U1[0]     0      0  ...         0          0  |
//            | U1[0]  U0[1]  U1[1]     0  ...         .          .  |
//            |    0   U1[1]  U0[2]  U1[2] ...         .          .  |
// RQ       = |    0      0   U1[2]  U0[3] ...         .          .  |
//            |    .      .      .      .              0          0  |
//            |    0      0      0      0  ...  U1[n - 3]         0  | 
//            |    0      0      0      0  ...  U0[n - 2]  U1[n - 2] | 
//            |    0      0      0      0  ...  U1[n - 2]  U0[n - 1] |
// を返す. 
// *******************************************************************
void REAL__MATRIX_RQ_TRI(REAL U0[],//(out)[n]     : 3重対角行列RQの対角成分
                         REAL U1[],//(out)[n - 1] : 3重対角行列RQの非対角成分
                         REAL C [],//(in) [n - 1] : QR分解の直交行列Qの情報を表すパラメータ
                         REAL S [],//(in) [n - 1] : QR分解の直交行列Qの情報を表すパラメータ
                         REAL R0[],//(in) [n]     : QR分解の上三角行列Rの対角成分
                         REAL R1[],//(in) [n - 1] : QR分解の上三角行列Rの非対角成分1
                         INT  n){  //(in)         : 行列の次元数
  INT i;
  
    U0[0    ] = C[0]            * R0[0    ] + S[0] * R1[0];
  for(i = 1;i < n - 1;i++){
    U0[i    ] = C[i] * C[i - 1] * R0[i    ] + S[i] * R1[i];
  }
    U0[n - 1] =        C[n - 2] * R0[n - 1];
  
  for(i = 0;i < n - 1;i++){
    U1[i] = S[i] * R0[i + 1];
  }
}








#define dim (10)

int main(void){
  REAL   A[dim][dim],P[dim][dim],T[dim][dim],R[dim][dim],TMP_R[dim][dim],Q[dim][dim],TMP_P[dim][dim],I[dim][dim],QR[dim][dim],RQ[dim][dim];
  RANDOM rnd;
  INT4   i,j,k;
  REAL   AMP,COS,SIN;
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      P[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();      
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      A[i][j] = REAL__ZERO();      
    }
  }
  for(i = 0;i < dim;i++){
    A[i][i] = RANDOM__NORMAL(&rnd,0.0,1.0);    
  }
  for(i = 0;i < dim - 1;i++){
    A[i][i + 1] = RANDOM__NORMAL(&rnd,0.0,1.0);
    A[i + 1][i] = A[i][i + 1];
  }

  REAL__MATRIX_PRINT(&A[0][0],dim,dim,stderr);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      R[i][j] = A[i][j];
    }
  }

  for(k = 0;k < dim - 1;k++){
    for(i = 0;i < dim;i++){
      for(j = 0;j < dim;j++){
        T[i][j] = (i == j) ? REAL__ONE() : REAL__ZERO();      
      }
    }
    AMP = sqrt(R[k][k] * R[k][k] + R[k + 1][k] * R[k + 1][k]);
    COS = R[k    ][k] / AMP;
    SIN = R[k + 1][k] / AMP;
    T[k    ][k    ] =  COS;T[k    ][k + 1] = SIN;
    T[k + 1][k    ] = -SIN;T[k + 1][k + 1] = COS;
    
    REAL__MATRIX_MUL(&TMP_R[0][0],&T[0][0],dim,dim,&R[0][0],dim,dim);
    REAL__MATRIX_MUL(&TMP_P[0][0],&T[0][0],dim,dim,&P[0][0],dim,dim);

    for(i = 0;i < dim;i++){
      for(j = 0;j < dim;j++){
        R[i][j] = TMP_R[i][j];
        P[i][j] = TMP_P[i][j];
      }
    }

    REAL__MATRIX_PRINT(&R[0][0],dim,dim,stderr);
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      Q[i][j] = P[j][i];
    }
  }
  
  REAL__MATRIX_MUL(&I[0][0],&Q[0][0],dim,dim,&P[0][0],dim,dim);

  REAL__MATRIX_MUL(&QR[0][0],&Q[0][0],dim,dim,&R[0][0],dim,dim);
  REAL__MATRIX_MUL(&RQ[0][0],&R[0][0],dim,dim,&Q[0][0],dim,dim);

  REAL__MATRIX_PRINT(&I[0][0],dim,dim,stderr);

  REAL__MATRIX_PRINT(&QR[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&RQ[0][0],dim,dim,stderr);

  double C[dim - 1];
  double S[dim - 1];
  double A0[dim];     //A対角成分
  double A1[dim - 1]; //A非対角成分
  double R0[dim];     //R対角成分
  double R1[dim - 1]; //R非対角成分1
  double R2[dim - 2]; //R非対角成分2
  double RQ0[dim];    //QRの対角成分
  double RQ1[dim - 1];//QRの非対角成分1
  
  for(k = 0;k < dim    ;k++){
    A0[k] = A[k][k    ];
  }

  for(k = 0;k < dim - 1;k++){
    A1[k] = A[k][k + 1];
  }

  REAL__MATRIX_QR_TRI(C,S,R0,R1,R2,A0,A1,dim);
  REAL__MATRIX_RQ_TRI(RQ0,RQ1,C,S,R0,R1,dim);

  for(k = 0;k < dim - 2  ;k++){
    printf("%f %f %f\n",R0[k],R1[k],R2[k]);
  }
  printf("%f %f\n",R0[dim - 2],R1[dim - 2]);
  printf("%f\n",R0[dim - 1]);

  printf("===========");
  for(k = 0;k < dim - 1;k++){
    printf("%f %f\n",RQ0[k],RQ1[k]);
  }
  printf("%f\n",RQ0[dim - 1]);

  return 0;
}
