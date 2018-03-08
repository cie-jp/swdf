/***************************************************************** 
 *
 * PLASMA
 *
 *
 *                           Created  by Mamoru Ota (2018/03/08)
 * 
 *****************************************************************/

#ifndef _PLASMA_H_INCLUDE_
#define _PLASMA_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include   <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include    <math.h>
#include   <float.h>
#include   <ctype.h>
#include"DATATYPE.h"
#include "COMPLEX.h"  

  // 
  // 電界0成分磁界3成分のスペクトルマトリクスから単一平面波の伝搬方向を求める.
  // # x方向は, 磁気子午面方向(地球向き), z方向は磁力線と平行(同方向)であること仮定する. 
  // # また, スペクトルマトリクスは任意単位で与えて良い.
  // # 磁界データしか用いないため, 絶対方向は定まらない.
  // # 本関数ではthetaは0 ~ 90 [deg]の範囲で返される. 
  //
  // S[0 * 3 + 0] : S_{Hx,Hx}
  // S[0 * 3 + 1] : S_{Hx,Hy}
  // S[0 * 3 + 2] : S_{Hx,Hz}
  // S[1 * 3 + 0] : S_{Hy,Hx}
  // S[1 * 3 + 1] : S_{Hy,Hy}
  // S[1 * 3 + 2] : S_{Hy,Hz}
  // S[2 * 3 + 0] : S_{Hz,Hx}
  // S[2 * 3 + 1] : S_{Hz,Hy}
  // S[2 * 3 + 2] : S_{Hz,Hz}
  void PLASMA__MEANS_METHOD_E0_H3(REAL8   *theta, //[rad]
                                  REAL8   *phi,   //[rad]
                                  COMPLEX  S[ 9]);//Spectral Matrix

  // 
  // 電界3成分磁界3成分のスペクトルマトリクスから単一平面波の伝搬方向を求める.
  // # x方向は, 磁気子午面方向(地球向き), z方向は磁力線と平行(同方向)であること仮定する. 
  // # また, スペクトルマトリクスは任意単位で与えて良い. 
  //
  // S[0 * 6 + 0] : S_{Ex,Ex}
  // S[0 * 6 + 1] : S_{Ex,Ey}
  // S[0 * 6 + 2] : S_{Ex,Ez}
  // S[0 * 6 + 3] : S_{Ex,Hx}
  // S[0 * 6 + 4] : S_{Ex,Hy}
  // S[0 * 6 + 5] : S_{Ex,Hz}
  // S[1 * 6 + 0] : S_{Ey,Ex}
  // S[1 * 6 + 1] : S_{Ey,Ey}
  // S[1 * 6 + 2] : S_{Ey,Ez}
  // S[1 * 6 + 3] : S_{Ey,Hx}
  // S[1 * 6 + 4] : S_{Ey,Hy}
  // S[1 * 6 + 5] : S_{Ey,Hz}
  // S[2 * 6 + 0] : S_{Ez,Ex}
  // S[2 * 6 + 1] : S_{Ez,Ey}
  // S[2 * 6 + 2] : S_{Ez,Ez}
  // S[2 * 6 + 3] : S_{Ez,Hx}
  // S[2 * 6 + 4] : S_{Ez,Hy}
  // S[2 * 6 + 5] : S_{Ez,Hz}
  // S[3 * 6 + 0] : S_{Hx,Ex}
  // S[3 * 6 + 1] : S_{Hx,Ey}
  // S[3 * 6 + 2] : S_{Hx,Ez}
  // S[3 * 6 + 3] : S_{Hx,Hx}
  // S[3 * 6 + 4] : S_{Hx,Hy}
  // S[3 * 6 + 5] : S_{Hx,Hz}
  // S[4 * 6 + 0] : S_{Hy,Ex}
  // S[4 * 6 + 1] : S_{Hy,Ey}
  // S[4 * 6 + 2] : S_{Hy,Ez}
  // S[4 * 6 + 3] : S_{Hy,Hx}
  // S[4 * 6 + 4] : S_{Hy,Hy}
  // S[4 * 6 + 5] : S_{Hy,Hz}
  // S[5 * 6 + 0] : S_{Hz,Ex}
  // S[5 * 6 + 1] : S_{Hz,Ey}
  // S[5 * 6 + 2] : S_{Hz,Ez}
  // S[5 * 6 + 3] : S_{Hz,Hx}
  // S[5 * 6 + 4] : S_{Hz,Hy}
  // S[5 * 6 + 5] : S_{Hz,Hz}
  void PLASMA__MEANS_METHOD_E3_H3(REAL8   *theta, //[rad]
                                  REAL8   *phi,   //[rad]
                                  COMPLEX  S[36]);//Spectral Matrix 
  
#ifdef __cplusplus
}
#endif

#endif
