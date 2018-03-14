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

void REAL__MATRIX_SVD_BI(REAL s [],//n
                         REAL U [],//n * n
                         REAL V [],//n * n
                         REAL b0[],//n
                         REAL b1[],//n-1
                         INT  n){
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
