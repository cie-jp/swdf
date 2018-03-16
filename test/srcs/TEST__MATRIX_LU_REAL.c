/*****************************************************************
 *
 * 実行列のLU分解の検証プログラム
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

int main(void){
  REAL   A [5][5];
  REAL   LU[5][5];
  REAL   L [5][5];
  REAL   U [5][5];
  REAL   L_U[5][5];
    
  RANDOM rnd;
  INT4   i,j;

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      A [i][j] = RANDOM__NORMAL(&rnd,0.0,1.0);
      LU[i][j] = A[i][j];
    }
  }

  REAL__MATRIX_LU_DECOMPOSITION(&LU[0][0],5);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      L[i][j] = 0.0;
      U[i][j] = 0.0;
    }
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      if(i >  j){
        L[i][j] = LU[i][j];
      }
      if(i == j){
        L[i][j] = 1.0;
      }
    }
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      if(i <= j){
        U[i][j] = LU[i][j];
      }
    }
  }


  REAL__MATRIX_PRINT(&A[0][0],5,5,stderr);
  REAL__MATRIX_PRINT(&L[0][0],5,5,stderr);
  REAL__MATRIX_PRINT(&U[0][0],5,5,stderr);

  REAL__MATRIX_MUL(&L_U[0][0],&L[0][0],5,5,&U[0][0],5,5);

  REAL__MATRIX_PRINT(&L_U[0][0],5,5,stderr);//L U = Aであれば, 正しい. 

  return 0;
}
