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

  fprintf(stderr,"============ Orthogonal Matrix Q ==========\n");
  REAL__MATRIX_PRINT(&Q[0][0],dim,dim,stderr);

  double U[dim][dim],L[dim][dim],Ut[dim][dim],UL[dim][dim],ULUt[dim][dim],UtLU[dim][dim],LU[dim][dim];

  REAL__MATRIX_EIGENVALUE_DECOMPOSITION_TRI(&U[0][0],A0,A1,dim);
  REAL__MATRIX_PRINT(&U[0][0],dim,dim,stderr);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      Ut[i][j] = U[j][i];
    }
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      L[i][j] = REAL__ZERO();
    }
  }
  for(i = 0;i < dim    ;i++){
    L[i][i] = A0[i];
  }

  REAL__MATRIX_MUL(&UL[0][0],&U[0][0],dim,dim,&L[0][0],dim,dim);
  REAL__MATRIX_MUL(&LU[0][0],&L[0][0],dim,dim,&U[0][0],dim,dim);
  REAL__MATRIX_MUL(&ULUt[0][0],&UL[0][0],dim,dim,&Ut[0][0],dim,dim);

  REAL__MATRIX_MUL(&UtLU[0][0],&Ut[0][0],dim,dim,&LU[0][0],dim,dim);

  REAL__MATRIX_PRINT(&ULUt[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&UtLU[0][0],dim,dim,stderr);
  
  return 0;
}
