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

  double L[dim - 1];
  double C[dim - 1];
  double S[dim - 1];
  double A_a[dim];    //A対角成分
  double A_b[dim - 1];//A非対角成分
  double R_a[dim];    //R対角成分
  double R_b[dim - 1];//R非対角成分1
  double R_c[dim - 2];//R非対角成分2
  
  for(k = 0;k < dim    ;k++){
    A_a[k] = A[k][k    ];
    R_a[k] = A_a[k];
  }

  for(k = 0;k < dim - 1;k++){
    A_b[k] = A[k][k + 1];
    R_b[k] = A_b[k];
  }

  for(k = 0;k < dim - 1;k++){
    L[k] = sqrt(R_a[k] * R_a[k] + A_b[k] * A_b[k]);
    C[k] = R_a[k] / L[k];
    S[k] = A_b[k] / L[k];
    R_a[k]     =  L[k];
    R_a[k + 1] = -S[k] * R_b[k    ] + C[k] * A_a[k + 1];
    R_b[k]     =  C[k] * R_b[k    ] + S[k] * A_a[k + 1];
    if(k != dim - 2){
      R_b[k + 1] =  C[k] * A_b[k + 1];
    }
    if(k != dim - 2){
      R_c[k]     =  S[k] * A_b[k + 1];
    }
  }

  for(k = 0;k < dim - 2  ;k++){
    printf("%f %f %f\n",R_a[k],R_b[k],R_c[k]);
  }
  printf("%f %f\n",R_a[dim - 2],R_b[dim - 2]);
  printf("%f\n",R_a[dim - 1]);

  double RQ_a[dim];    //QRの対角成分
  double RQ_b[dim - 1];//QRの非対角成分1

  RQ_a[0] = C[0] * R_a[0] + S[0] * R_b[0];
  for(k = 1;k < dim - 1;k++){
    RQ_a[k] = C[k] * C[k - 1] * R_a[k] + S[k] * R_b[k];
  }
  RQ_a[dim - 1] = C[dim - 2] * R_a[dim - 1];

  for(k = 0;k < dim - 1;k++){
    RQ_b[k] = S[k] * R_a[k + 1];
  }

  printf("===========");
  for(k = 0;k < dim - 1;k++){
    printf("%f %f\n",RQ_a[k],RQ_b[k]);
  }
  printf("%f\n",RQ_a[dim - 1]);

  return 0;
}
