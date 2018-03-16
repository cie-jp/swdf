/*****************************************************************
 *
 * DCT検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"CLDIA.h"

#define NUM (200)

int main(void){
  REAL8 x[NUM],x2[NUM];
  REAL8 fs =   1024.0;//[Hz]
  REAL8 f0 =    128.5;//[Hz]
  REAL8 Ts = 1.0 / fs;//[s]
  INT4  n,k;
  REAL8 DCT_x[NUM];
  
  for(n = 0;n < NUM;n++){
    x[n]  = 15.0 * cos(2.0 * M_PI * f0 * (n * Ts));
    x2[n] = x[n];
  }

  DCT (x2,NUM);
  IDCT(x2,NUM);
  for(n = 0;n < NUM;n++){
    fprintf(stderr,"%f %f %f\n",n * Ts,x[n],x2[n]);
  }
  
  for(k = 0;k < NUM;k++){
    DCT_x[k] = 0.0;
    for(n = 0;n < NUM;n++){
      DCT_x[k] += x[n] * cos(M_PI * k * (n + 0.5) / (REAL8)NUM);//DCT-II
    }
    if(k == 0){
      DCT_x[k] *= sqrt(1.0 / (REAL8)NUM);
    }else{
      DCT_x[k] *= sqrt(2.0 / (REAL8)NUM);
    }
  }

  DCT(x,NUM);

  for(k = 0;k < NUM;k++){
    printf("%f %f %f\n",k / (double)NUM * fs,x[k],DCT_x[k]);
  }

  return 0;
}
