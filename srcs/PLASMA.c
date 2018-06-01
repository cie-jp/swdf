/***************************************************************** 
 *
 * PLASMA
 *
 *
 *                           Created  by Mamoru Ota (2018/03/08)
 * 
 *****************************************************************/

#include"PLASMA.h"

void PLASMA__MEANS_METHOD_E0_H3(REAL8   *theta, //[rad]
                                REAL8   *phi,   //[rad]
                                COMPLEX  S[ 9]){//Spectral Matrix
  REAL8 kx,ky,kz;//伝搬ベクトル

  kx = S[1 * 3 + 2].imag;
  ky = S[2 * 3 + 0].imag;
  kz = S[0 * 3 + 1].imag;
  if(kz < 0.0){
    kx = -kx;
    ky = -ky;
    kz = -kz;
  }
  *theta = atan2(sqrt(kx * kx + ky * ky),kz);
  *phi   = atan2(ky,kx);
}

void PLASMA__MEANS_METHOD_E3_H3(REAL8   *theta, //[rad]
                                REAL8   *phi,   //[rad]
                                COMPLEX  S[36]){//Spectral Matrix
  COMPLEX S_H[9];
  REAL8   ux,uy,uz;
  REAL8   Hx,Hy,Hz;
  
  S_H[0 * 3 + 0] = S[3 * 6 + 3];
  S_H[0 * 3 + 1] = S[3 * 6 + 4];
  S_H[0 * 3 + 2] = S[3 * 6 + 5];
  S_H[1 * 3 + 0] = S[4 * 6 + 3];
  S_H[1 * 3 + 1] = S[4 * 6 + 4];
  S_H[1 * 3 + 2] = S[4 * 6 + 5];
  S_H[2 * 3 + 0] = S[5 * 6 + 3];
  S_H[2 * 3 + 1] = S[5 * 6 + 4];
  S_H[2 * 3 + 2] = S[5 * 6 + 5];

  PLASMA__MEANS_METHOD_E0_H3(theta,phi,S_H);

  ux = sin(*theta) * cos(*phi);
  uy = sin(*theta) * sin(*phi);
  uz = cos(*theta);  
}
