/***************************************************************** 
 *
 * FFT関連
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _FFT_H_INCLUDE_
#define _FFT_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"DATATYPE.h"

  /**************************************************************************/
  //Fast Fourier Transform
  //re[] : real parts
  //im[] : imaginary parts
  //n    : length of array
  /**************************************************************************/
  INT4 FFT         (REAL8 re[],REAL8 im[],INT4 n);
  /**************************************************************************/
  //Fast Fourier Transform(Unitary)
  //re[] : real parts
  //im[] : imaginary parts
  //n    : length of array
  /**************************************************************************/
  INT4 FFT_UNITARY (REAL8 re[],REAL8 im[],INT4 n);
  /**************************************************************************/
  //Fast Fourier Transform with Radix 2
  //re[] : real parts
  //im[] : imaginary parts
  //n    : length of array (n must be a power of two.) 
  /**************************************************************************/
  INT4 FFT_RADIX2  (REAL8 re[],REAL8 im[],INT4 n);
  /**************************************************************************/
  //Inverse Fast Fourier Transform
  //re[] : real parts
  //im[] : imaginary parts
  //n    : length of array
  /**************************************************************************/
  INT4 IFFT        (REAL8 re[],REAL8 im[],INT4 n);
  /**************************************************************************/
  //Inverse Fast Fourier Transform(Unitary)
  //re[] : real parts
  //im[] : imaginary parts
  //n    : length of array
  /**************************************************************************/
  INT4 IFFT_UNITARY(REAL8 re[],REAL8 im[],INT4 n);  
  /**************************************************************************/
  //Inverse Fast Fourier Transform with Radix 2
  //re[] : real parts
  //im[] : imaginary parts
  //n    : length of array (n must be a power of two.) 
  /**************************************************************************/
  INT4 IFFT_RADIX2 (REAL8 re[],REAL8 im[],INT4 n);
  /**************************************************************************/
  //Discrete Cosine Transform
  //x[]  : signal
  //n    : length of array
  /**************************************************************************/
  INT4 DCT         (REAL8 x[],INT4 n);
  /**************************************************************************/
  //Inverse Discrete Cosine Transform
  //x[]  : signal
  //n    : length of array
  /**************************************************************************/
  INT4 IDCT        (REAL8 x[],INT4 n);

#endif
