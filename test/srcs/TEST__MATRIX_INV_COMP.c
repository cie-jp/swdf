/*****************************************************************
 *
 * 複素行列の逆行列検証プログラム
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
  COMP A    [5][5];
  COMP A_inv[5][5];
  COMP B    [5][5];
  RANDOM  rnd;
  INT4    i,j,k;
  COMP    tmp;

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
      A_inv[i][j] = A[i][j];
    }
  }

  COMP__MATRIX_INV(&A_inv[0][0],5);

  COMP__MATRIX_PRINT(&A    [0][0],5,5,stderr);
  COMP__MATRIX_PRINT(&A_inv[0][0],5,5,stderr);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      tmp = COMPLEX__MAKE_ZERO();
      for(k = 0;k < 5;k++){
        tmp = COMPLEX__ADD(tmp,COMPLEX__MUL(A[i][k],A_inv[k][j]));
      }
      B[i][j] = tmp;
    }
  }

  COMP__MATRIX_PRINT(&B[0][0],5,5,stderr);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      tmp = COMPLEX__MAKE_ZERO();
      for(k = 0;k < 5;k++){
        tmp = COMPLEX__ADD(tmp,COMPLEX__MUL(A_inv[i][k],A[k][j]));
      }
      B[i][j] = tmp;
    }
  }

  COMP__MATRIX_PRINT(&B[0][0],5,5,stderr);

  return 0;
}
