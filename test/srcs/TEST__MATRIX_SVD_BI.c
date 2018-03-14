/*****************************************************************
 *
 * 実2重対角行列のSVD分解
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/14)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"MATRIX.h"
#include"RANDOM.h"

#define dim (20)

int main(void){
  REAL   B   [dim][dim];
  REAL   b0  [dim];
  REAL   b1  [dim - 1];
  REAL   s   [dim];
  REAL   S   [dim][dim];
  REAL   U   [dim][dim];
  REAL   V   [dim][dim];
  REAL   Vt  [dim][dim];
  REAL   Ut  [dim][dim];
  REAL   UUt [dim][dim];
  REAL   VVt [dim][dim];
  REAL   US  [dim][dim];
  REAL   USVt[dim][dim];
  RANDOM rnd;
  INT4   i,j;
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      B[i][j] = REAL__ZERO();      
    }
  }
  for(i = 0;i < dim;i++){
    B[i][i    ] = RANDOM__NORMAL(&rnd,0.0,1.0);
    b0[i]       = B[i][i];
  }
  for(i = 0;i < dim - 1;i++){
    B[i][i + 1] = RANDOM__NORMAL(&rnd,0.0,1.0);
    b1[i]       = B[i][i + 1];
  }

  REAL__MATRIX_PRINT(&B[0][0],dim,dim,stderr);

  REAL__MATRIX_SVD_BI(s,&U[0][0],&V[0][0],b0,b1,dim);
  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      S[i][j] = REAL__ZERO();      
    }
  }
  for(i = 0;i < dim;i++){
    S[i][i] = s[i];
  }

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      Ut[i][j] = U[j][i];
      Vt[i][j] = V[j][i];
    }
  }

  REAL__MATRIX_MUL(&US  [0][0],&U [0][0],dim,dim,&S [0][0],dim,dim);
  REAL__MATRIX_MUL(&USVt[0][0],&US[0][0],dim,dim,&Vt[0][0],dim,dim);

  REAL__MATRIX_PRINT(&USVt[0][0],dim,dim,stderr);

  REAL__MATRIX_PRINT(&U[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&S[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&V[0][0],dim,dim,stderr);
  
  REAL__MATRIX_MUL(&UUt[0][0],&U[0][0],dim,dim,&Ut[0][0],dim,dim);
  REAL__MATRIX_MUL(&VVt[0][0],&V[0][0],dim,dim,&Vt[0][0],dim,dim);

  REAL__MATRIX_PRINT(&UUt[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&VVt[0][0],dim,dim,stderr);
  
  return 0;
}
