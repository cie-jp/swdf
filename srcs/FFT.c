/***************************************************************** 
 *
 * 乱数発生
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"FFT.h"

INT4 FFT         (REAL8 re[],REAL8 im[],INT4 n){
  INT4   i ,L ;
  REAL8  th,tr,ti;
  void  *buf;
  REAL8 *a_re,*a_im;
  REAL8 *b_re,*b_im;
  
  if((re == NULL) || (im == NULL) || (n < 1)){
    return -1;
  }
  for(L = 1;L < n;L *= 2);
  if(L == n){
    FFT_RADIX2(re,im,L);
  }else{
    L   *= 2;
    if((buf  = malloc(sizeof(REAL8) * L * 4)) == NULL){
      return -2;
    }
    memset(buf,0x00,sizeof(REAL8) * L * 4);
    a_re    =  buf;
    a_im    = &a_re[L];
    b_re    = &a_im[L];
    b_im    = &b_re[L];
    a_re[0] = re[0];
    a_im[0] = im[0];
    b_re[0] =   1.0;
    b_im[0] =   0.0;
    for(i = 1;i < n;i++){
      th = -M_PI * i * i  / (REAL8)n;
      tr =  cos(th);
      ti =  sin(th);
      a_re[i] = re[i] * tr - im[i] * ti;
      a_im[i] = re[i] * ti + im[i] * tr;
      b_re[i] = b_re[L - i] =  tr;
      b_im[i] = b_im[L - i] = -ti;
    }
    FFT_RADIX2(a_re,a_im,L);
    FFT_RADIX2(b_re,b_im,L);
    for(i = 0;i < L;i++){
      tr = a_re[i] * b_re[i] - a_im[i] * b_im[i];
      ti = a_re[i] * b_im[i] + a_im[i] * b_re[i];
      a_re[i] = tr;
      a_im[i] = ti;
    }
    IFFT_RADIX2(a_re,a_im,L);
    re[0] = a_re[0];
    im[0] = a_im[0];
    for(i = 1;i < n;i++){
      th = -M_PI * i * i  / (REAL8)n;
      tr =  cos(th);
      ti =  sin(th);
      re[i] = a_re[i] * tr - a_im[i] * ti;
      im[i] = a_re[i] * ti + a_im[i] * tr;
    }
    free(buf);
  }
  return 0;
}

INT4 FFT_UNITARY (REAL8 re[],REAL8 im[],INT4 n){
  REAL8 scale;
  INT4  i;
  
  if(FFT(re,im,n) != 0){
    return -1;
  }
  scale = 1.0 / sqrt((REAL8)n);
  for(i = 0;i < n;i++){
    re[i] *= scale;
    im[i] *= scale;
  }
  return 0;
}

INT4 FFT_RADIX2  (REAL8 re[],REAL8 im[],INT4 n){
  REAL8 th,tr,ti,wr,wi;
  INT4   i ,j ,k ,h ,m;
  
  if((re == NULL) || (im == NULL) || (n < 1)){
    return -1;
  }  
  i = 0;
  for(j = 1;j < n - 1;j++){
    for(k = n >> 1;k > (i ^= k);k >>= 1);
    if(j < i){
      tr    = re[j];
      ti    = im[j];
      re[j] = re[i];
      im[j] = im[i];
      re[i] = tr;
      im[i] = ti;
    }
  }
  th = -2.0 * M_PI;
  for(h = 1;(m = h << 1) <= n;h = m){
    th *= 0.5;
    for(i = 0;i < h;i++){
      wr = cos(th * i);
      wi = sin(th * i);
      for(j = i;j < n;j += m){
	k      = j  + h;
	tr     = wr * re[k] - wi * im[k];
	ti     = wr * im[k] + wi * re[k];
	re[k]  = re[j] - tr;
	im[k]  = im[j] - ti;
	re[j] += tr;
	im[j] += ti;	
      }
    }
  }
  return 0;
}

INT4 IFFT        (REAL8 re[],REAL8 im[],INT4 n){
  INT4    i, L;
  REAL8  th,tr,ti;
  void  *buf;
  REAL8 *a_re,*a_im;
  REAL8 *b_re,*b_im;
  
  if((re == NULL) || (im == NULL) || (n < 1)){
    return -1;
  }  
  for(L = 1;L < n;L *= 2);
  if(L == n){
    IFFT_RADIX2(re,im,L);
  }else{
    L   *= 2;
    if((buf  = malloc(sizeof(REAL8) * L * 4)) == NULL){
      return -2;
    }
    memset(buf,0x00,sizeof(REAL8) * L * 4);
    a_re    =  buf;
    a_im    = &a_re[L];
    b_re    = &a_im[L];
    b_im    = &b_re[L];
    a_re[0] = re[0];
    a_im[0] = im[0];
    b_re[0] =   1.0;
    b_im[0] =   0.0;
    for(i = 1;i < n;i++){
      th =  M_PI * i * i  / (REAL8)n;
      tr =  cos(th);
      ti =  sin(th);
      a_re[i] = re[i] * tr - im[i] * ti;
      a_im[i] = re[i] * ti + im[i] * tr;
      b_re[i] = b_re[L - i] =  tr;
      b_im[i] = b_im[L - i] = -ti;
    }
    FFT_RADIX2(a_re,a_im,L);
    FFT_RADIX2(b_re,b_im,L);
    for(i = 0;i < L;i++){
      tr = a_re[i] * b_re[i] - a_im[i] * b_im[i];
      ti = a_re[i] * b_im[i] + a_im[i] * b_re[i];
      a_re[i] = tr;
      a_im[i] = ti;
    }
    IFFT_RADIX2(a_re,a_im,L);
    re[0] = a_re[0] / (REAL8)n;
    im[0] = a_im[0] / (REAL8)n;
    for(i = 1;i < n;i++){
      th =  M_PI * i * i  / (REAL8)n;
      tr =  cos(th);
      ti =  sin(th);
      re[i]  = a_re[i] * tr - a_im[i] * ti;
      im[i]  = a_re[i] * ti + a_im[i] * tr;
      re[i] /= (REAL8)n;
      im[i] /= (REAL8)n;
    }
    free(buf);
  }
  return 0;
}

INT4 IFFT_UNITARY(REAL8 re[],REAL8 im[],INT4 n){
  REAL8 scale;
  INT4  i;
  
  if(IFFT(re,im,n) != 0){
    return -1;
  }
  scale = sqrt((REAL8)n);
  for(i = 0;i < n;i++){
    re[i] *= scale;
    im[i] *= scale;
  }
  return 0;
}

INT4 IFFT_RADIX2 (REAL8 re[],REAL8 im[],INT4 n){
  REAL8 th,tr,ti,wr,wi;
  INT4   i ,j ,k ,h ,m;

  if((re == NULL) || (im == NULL) || (n < 1)){
    return -1;
  }  
  i = 0;
  for(j = 1;j < n - 1;j++){
    for(k = n >> 1;k > (i ^= k);k >>= 1);
    if(j < i){
      tr    = re[j];
      ti    = im[j];
      re[j] = re[i];
      im[j] = im[i];
      re[i] = tr;
      im[i] = ti;
    }
  }
  th = +2.0 * M_PI;
  for(h = 1;(m = h << 1) <= n;h = m){
    th *= 0.5;
    for(i = 0;i < h;i++){
      wr = cos(th * i);
      wi = sin(th * i);
      for(j = i;j < n;j += m){
	k      = j  + h;
	tr     = wr * re[k] - wi * im[k];
	ti     = wr * im[k] + wi * re[k];
	re[k]  = re[j] - tr;
	im[k]  = im[j] - ti;
	re[j] += tr;
	im[j] += ti;	
      }
    }
  }
  for(i = 0;i < n;i++){
    re[i] /= (REAL8)n;
    im[i] /= (REAL8)n;
  }
  return 0;
}

INT4 DCT         (REAL8 x[],INT4 n){
  void  *buf;
  REAL8 *re;
  REAL8 *im;
  INT4   i, L;
  
  if((x == NULL) || (n < 1)){
    return -1;
  }  
  L  = 4 * n;
  if((buf  = malloc(sizeof(REAL8) * L * 2)) == NULL){
    return -2;
  }
  memset(buf,0x00,sizeof(REAL8) * L * 2);
  re    =  buf;
  im    = &re[L];
  for(i = 0;i < n;i++){
    re[2 * i + 1] = re[L - 2 * i - 1] = x[i] / 2.0;
  }
  FFT(re,im,L);
  for(i = 0;i < n;i++){
    x[i] = re[i] * sqrt(2.0 / (REAL8)n);
  }
  x[0] /= sqrt(2.0);
  free(buf);
  return 0;
}

INT4 IDCT        (REAL8 x[],INT4 n){
  void  *buf;
  REAL8 *re;
  REAL8 *im;
  INT4   i, L;

  if((x == NULL) || (n < 1)){
    return -1;
  }    
  L  = 4 * n;
  if((buf  = malloc(sizeof(REAL8) * L * 2)) == NULL){
    return -2;
  }
  memset(buf,0x00,sizeof(REAL8) * L * 2);
  re    =  buf;
  im    = &re[L];
  re[    0] =  2.0 * x[0] * sqrt((REAL8)n);
  re[2 * n] = -2.0 * x[0] * sqrt((REAL8)n);  
  for(i = 1;i < n;i++){
    re[i]         = re[L - i]     =  2.0 * x[i] * sqrt((REAL8)n / 2.0);
    re[2 * n - i] = re[2 * n + i] = -2.0 * x[i] * sqrt((REAL8)n / 2.0);
  }
  IFFT(re,im,L);
  for(i = 0;i < n;i++){
    x[i] = re[2 * i + 1];
  }
  free(buf);
  return 0;
}
