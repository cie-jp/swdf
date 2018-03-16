/*****************************************************************
 *
 * 複素行列のLUP分解の検証プログラム
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
  COMP   A [5][5];
  COMP   LU[5][5];
  INT    P [5];
  COMP   L [5][5];
  COMP   U [5][5];
  COMP   R [5][5];
  COMP   L_U[5][5];
  COMP   R_L_U[5][5];
    
  RANDOM rnd;
  INT4   i,j;

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      A [i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
      LU[i][j] = A[i][j];
    }
  }

  COMP__MATRIX_LUP_DECOMPOSITION(&LU[0][0],P,5);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      L[i][j] = COMPLEX__MAKE_ZERO();
      U[i][j] = COMPLEX__MAKE_ZERO();
      R[i][j] = COMPLEX__MAKE_ZERO();
    }
  }
  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      if(i >  j){
        L[i][j] = LU[i][j];
      }
      if(i == j){
        L[i][j] = COMPLEX__MAKE_RE_IM(1.0,0.0);
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
  for(i = 0;i < 5;i++){
    R[P[i]][i] = COMPLEX__MAKE_RE_IM(1.0,0.0);
  }  

  COMP__MATRIX_PRINT(&A[0][0],5,5,stderr);
  COMP__MATRIX_PRINT(&L[0][0],5,5,stderr);
  COMP__MATRIX_PRINT(&U[0][0],5,5,stderr);
  COMP__MATRIX_PRINT(&R[0][0],5,5,stderr);

  COMP__MATRIX_MUL(&L_U[0][0],&L[0][0],5,5,&U[0][0],5,5);
  COMP__MATRIX_MUL(&R_L_U[0][0],&R[0][0],5,5,&L_U[0][0],5,5);

  COMP__MATRIX_PRINT(&R_L_U[0][0],5,5,stderr);//R L U = Aであれば, 正しい. 

  return 0;
}
