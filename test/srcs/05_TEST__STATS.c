/*****************************************************************
 *
 * 配列の最小値と最大値を取得する
 * 
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"STATS.h"

#define NUM (100)

int main(void){
  REAL8 x[NUM];
  INT4  n;

  for(n = 0;n < NUM;n++){
    x[n] = n;
  }

  fprintf(stderr,"min = %lf, max = %lf\n",STATS__MIN(x,NUM,0),STATS__MAX(x,NUM,0));

  return EXIT_SUCCESS;
}
