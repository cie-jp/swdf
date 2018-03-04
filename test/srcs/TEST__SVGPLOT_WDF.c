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

int main(void){
  int    theta_num = 150;
  int    phi_num   = 130;
  double theta[theta_num];
  double phi  [  phi_num];
  double ftp  [theta_num * phi_num];
  
  int    x_num = 1000;
  int    y_num = 1000;
  double x[x_num];
  double y[y_num];
  double *fxy_north = malloc(sizeof(double) * x_num * y_num);
  double *fxy_south = malloc(sizeof(double) * x_num * y_num);
  
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

  CALCULATION__SPHERICAL_DISTRIBUTION(fxy_north,
                                      fxy_south,
                                      x,y,
                                      x_num,y_num,
                                      ftp,
                                      theta,
                                      phi,
                                      theta_num,
                                      phi_num);

  SVGPLOT plt;

  SVGPLOT__INITIALIZE_002(&plt,"test1.svg");
  double X0,Y0,W,H;
  X0 = (plt.Xmin + plt.Xmax) / 2.0;
  Y0 = (plt.Ymin + plt.Ymax) / 2.0;
  W  = (plt.Xmax - plt.Xmin);
  H  = (plt.Ymax - plt.Ymin);

  plt.Xmin = X0 - H / 2.0;
  plt.Xmax = X0 + H / 2.0; 
  
  SVGPLOT_PALETTE__Create10(&plt.pal);
  
  SVGPLOT__XYZ_CONTOUR(&plt,x,x_num,y,y_num,fxy_north,-1.0,-1.0,0);
  /*
  SVGPLOT__XY_AUX(&plt,
                  1,1,1,1,
                  1,1,1,1,
                  1,0,1,0,
                  1);
  */
  SVGPLOT_GRID__POLAR2(&plt,0);
  //SVGPLOT__XLABEL(&plt,"x",NULL);
  //SVGPLOT__YLABEL(&plt,"y",NULL);
  SVGPLOT__TITLE (&plt,"Wave Distribution Function");

  SVGPLOT__COLORBAR(&plt,
                    1,1,
                    2,2,
                    2,0,
                    1);

  SVGPLOT__FINALIZE(&plt);

  SVGPLOT__INITIALIZE_002(&plt,"test2.svg");

    X0 = (plt.Xmin + plt.Xmax) / 2.0;
  Y0 = (plt.Ymin + plt.Ymax) / 2.0;
  W  = (plt.Xmax - plt.Xmin);
  H  = (plt.Ymax - plt.Ymin);

  plt.Xmin = X0 - H / 2.0;
  plt.Xmax = X0 + H / 2.0; 

  SVGPLOT_PALETTE__Create10(&plt.pal);

  
  SVGPLOT__XYZ_CONTOUR(&plt,x,x_num,y,y_num,fxy_south,-1.0,-1.0,0);
  /*
  SVGPLOT__XY_AUX(&plt,
                  1,1,1,1,
                  1,1,1,1,
                  1,0,1,0,
                  1);
  */
  SVGPLOT_GRID__POLAR2(&plt,1);

  //SVGPLOT__XLABEL(&plt,"x",NULL);
  //SVGPLOT__YLABEL(&plt,"y",NULL);
  SVGPLOT__TITLE (&plt,"Wave Distribution Function");

  SVGPLOT__COLORBAR(&plt,
                    1,1,
                    2,2,
                    2,0,
                    1);

  SVGPLOT__FINALIZE(&plt);

  free(fxy_north);
  free(fxy_south);
  
  return 0;
}
