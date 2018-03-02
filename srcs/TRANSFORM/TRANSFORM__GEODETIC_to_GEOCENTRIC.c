#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

//WGS84測地系から地心座標系(GEO)への変換
void GEODETIC_to_GEOCENTRIC(double *r,      //(out) 地心距離   [m]
			    double *theta,  //(out) 地心余緯度 [rad]
			    double *phi,    //(out) 地理経度   [rad]
			    double  h,      //(in)  標高       [m]
			    double  theta0, //(in)  測地余緯度 [rad]
			    double  phi0){  //(in)  地理経度   [rad] 東経 +
  const double Re           = 6378.13700e3;//赤道半径[m]                                               
  const double Rp           = 6356.75231e3;//  極半径[m]                                               
  const double Re2          = Re  * Re ;
  const double Re4          = Re2 * Re2;
  const double Rp2          = Rp  * Rp ;
  const double Rp4          = Rp2 * Rp2;
  long  double cos_theta0   = cosl(theta0);
  long  double sin_theta0   = sinl(theta0);
  long  double cos_theta0_2 = cos_theta0 * cos_theta0;
  long  double sin_theta0_2 = sin_theta0 * sin_theta0;
  long  double Rm2          = Re2 * sin_theta0_2 + Rp2 * cos_theta0_2;
  long  double Rm           = sqrtl(Rm2);

  *r     = sqrt((Re4 * sin_theta0_2 + Rp4 * cos_theta0_2) / Rm2 + 2.0 * h * Rm + h * h);
  *theta = acos(cos_theta0 / (*r) * (Rp2 / Rm + h));
  *phi   = phi0;
}
