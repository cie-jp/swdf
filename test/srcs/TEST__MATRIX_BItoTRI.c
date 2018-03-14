/*****************************************************************
 *
 * 2重対角行列BからB^{T}Bを計算するプログラム
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
  REAL   B[dim][dim],BT[dim][dim],BTB[dim][dim],BBT[dim][dim];
  RANDOM rnd;
  INT4   i,j;
  REAL   AMP,COS,SIN;

  REAL   B0[dim];
  REAL   B1[dim - 1];
  REAL   T0[dim];
  REAL   T1[dim - 1];
  
  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      B[i][j] = REAL__ZERO();      
    }
  }
  for(i = 0;i < dim;i++){
    B[i][i] = RANDOM__NORMAL(&rnd,0.0,1.0);
    B0[i]   = B[i][i];
  }
  for(i = 0;i < dim - 1;i++){
    B[i][i + 1] = RANDOM__NORMAL(&rnd,0.0,1.0);
    B1[i]       = B[i][i + 1];
  }
  
  REAL__MATRIX_PRINT(&B[0][0],dim,dim,stderr);

  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      BT[i][j] = B[j][i];
    }
  }
  REAL__MATRIX_MUL(&BTB[0][0],&BT[0][0],dim,dim,&B [0][0],dim,dim);
  REAL__MATRIX_MUL(&BBT[0][0],&B [0][0],dim,dim,&BT[0][0],dim,dim);

  REAL__MATRIX_PRINT(&BTB[0][0],dim,dim,stderr);
  REAL__MATRIX_PRINT(&BBT[0][0],dim,dim,stderr);

  REAL__MATRIX_BTB(T0,T1,B0,B1,dim);
  for(i = 0;i < dim - 1;i++){
    printf("%f %f\n",T0[i],T1[i]);
  }
  printf("%f\n",T0[dim - 1]);


  REAL__MATRIX_BBT(T0,T1,B0,B1,dim);
  for(i = 0;i < dim - 1;i++){
    printf("%f %f\n",T0[i],T1[i]);
  }
  printf("%f\n",T0[dim - 1]);

  return 0;
}
