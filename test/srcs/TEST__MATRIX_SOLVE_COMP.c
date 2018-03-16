/*****************************************************************
 *
 * 複素行列の連立方程式の解の検証プログラム
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
  COMP   A[5][5];
  COMP   b[5];
  COMP   x[5];
  COMP   y[5];
  RANDOM rnd;
  INT4   i,j;

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < 5;i++){
    for(j = 0;j < 5;j++){
      A[i][j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0));
    }
  }
  for(i = 0;i < 5;i++){
    b[i] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0)); 
  }

  //Ax = bについて, A,bをランダムに与えて, xを求める. 
  COMP__MATRIX_SOLVE(x,&A[0][0],b,5);

  COMP__MATRIX_PRINT(&A[0][0],5,5,stderr);
  COMP__MATRIX_PRINT(x,5,1,stderr);

  //y = Axとして, これがbに合えばxが正しく計算できていることになる. 
  COMP__MATRIX_MUL(y,&A[0][0],5,5,x,5,1);

  COMP__MATRIX_PRINT(y,5,1,stderr);
  COMP__MATRIX_PRINT(b,5,1,stderr);

  return 0;
}
