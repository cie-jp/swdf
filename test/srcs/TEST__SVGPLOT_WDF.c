/*****************************************************************
 *
 * WDF検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<SVG/SVGPLOT.h>

#define DAT_DIR "./test/dat/"

int main(void){
  int    theta_num = 150;
  int    phi_num   = 130;
  double theta[theta_num];
  double phi  [  phi_num];
  double ftp  [theta_num * phi_num];
  int    k,l;
  
  for(k = 0;k < theta_num;k++){
    theta[k] =       M_PI * k / (theta_num - 1.0);
  }
  for(l = 0;l <   phi_num;l++){
    phi  [l] = 2.0 * M_PI * l / (  phi_num - 1.0);
  }

  double theta0 = (90.0 + 25.0) / 180.0 * M_PI;
  double phi0   = 65.0 / 180.0 * M_PI;
  double x0,y0,z0,x1,y1,z1;

  x0 = sin(theta0) * cos(phi0);
  y0 = sin(theta0) * sin(phi0);
  z0 = cos(theta0);
  for(k = 0;k < theta_num;k++){
    for(l = 0;l <   phi_num;l++){
      x1 = sin(theta[k]) * cos(phi[l]);
      y1 = sin(theta[k]) * sin(phi[l]);
      z1 = cos(theta[k]);

      ftp[k * phi_num + l] = k * exp(15.0 * (x0 * x1 + y0 * y1 + z0 * z1));
    }
  }

  theta0 =  25.0 / 180.0 * M_PI;
  phi0   = 165.0 / 180.0 * M_PI;

  x0 = sin(theta0) * cos(phi0);
  y0 = sin(theta0) * sin(phi0);
  z0 = cos(theta0);
  for(k = 0;k < theta_num;k++){
    for(l = 0;l <   phi_num;l++){
      x1 = sin(theta[k]) * cos(phi[l]);
      y1 = sin(theta[k]) * sin(phi[l]);
      z1 = cos(theta[k]);

      ftp[k * phi_num + l] += k * exp(15.0 * (x0 * x1 + y0 * y1 + z0 * z1));
    }
  }
  
  SVGPLOT__WDF(ftp,
               theta,
               phi,
               theta_num,
               phi_num,
               DAT_DIR "wdf.svg");
  return 0;
}
