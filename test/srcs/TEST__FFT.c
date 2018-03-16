/*****************************************************************
 *
 * FFT検証プログラム
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
  REAL8 re[NUM],re2[NUM];
  REAL8 im[NUM],im2[NUM];
  REAL8 fs =   1024.0;//[Hz]
  REAL8 f0 =    128.5;//[Hz]
  REAL8 Ts = 1.0 / fs;//[s]
  INT4  n,k;
  REAL8 DFT_re[NUM];
  REAL8 DFT_im[NUM];
  
  for(n = 0;n < NUM;n++){
    re[n] = 15.0 * cos(2.0 * M_PI * f0 * (n * Ts));
    im[n] =  2.0 * sin(2.0 * M_PI * f0 * (n * Ts));
    re2[n] = re[n];
    im2[n] = im[n];
  }

  FFT (re2,im2,NUM);
  IFFT(re2,im2,NUM);
  for(n = 0;n < NUM;n++){
    fprintf(stderr,"%f %f %f %f %f\n",n * Ts,re[n],im[n],re2[n],im2[n]);
  }
  
  for(k = 0;k < NUM;k++){
    DFT_re[k] = 0.0;
    DFT_im[k] = 0.0;    
    for(n = 0;n < NUM;n++){
      DFT_re[k] += re[n] * cos(-2.0 * M_PI * k * n / (REAL8)NUM) - im[n] * sin(-2.0 * M_PI * k * n / (REAL8)NUM);
      DFT_im[k] += re[n] * sin(-2.0 * M_PI * k * n / (REAL8)NUM) + im[n] * cos(-2.0 * M_PI * k * n / (REAL8)NUM);
    }
  }

  FFT(re,im,NUM);

  for(k = 0;k < NUM;k++){
    printf("%f %f %f %f %f\n",k / (double)NUM * fs,re[k],im[k],DFT_re[k],DFT_im[k]);
  }

  return 0;
}
