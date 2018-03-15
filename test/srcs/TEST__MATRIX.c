/*****************************************************************
 *
 * 行列検証プログラム
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
  RANDOM  rnd;
  RMATRIX A;

  RMATRIX__INITIALIZE(&A,5,7);

  RMATRIX__SHOW_INFO(&A,stdout);

  RMATRIX__SET_IDENTITY(&A);
  RMATRIX__SHOW_INFO(&A,stdout);

  RMATRIX__SET_VALUE(&A,5.0);
  RMATRIX__SHOW_INFO(&A,stdout);

  RMATRIX__SET_RANDOM(&A);
  RMATRIX__SHOW_INFO(&A,stdout);

  RMATRIX__FINALIZE(&A);

  return 0;
}
