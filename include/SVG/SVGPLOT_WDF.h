/***************************************************************** 
 *
 * SVGPLOT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_WDF_H_INCLUDE_
#define _SVGPLOT_WDF_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

  #include"SVGPLOT.h"
  
  void SVGPLOT_GRID__POLAR(SVG      *svg,
                           REAL8     Xmin,
                           REAL8     Xmax,
                           REAL8     Ymin,
                           REAL8     Ymax,
                           SVG_STYLE gridstyle,int mode);

  void SVGPLOT_GRID__POLAR2(SVGPLOT *plt,int mode);

  void CALCULATION__SPHERICAL_DISTRIBUTION(double  fxy_north[],//(out) fxy_north[n * y_num + m] : x_num * y_num ( 0[deg] <= theta <=  90[deg])
                                           double  fxy_south[],//(out) fxy_south[n * y_num + m] : x_num * y_num (90[deg] <= theta <= 180[deg])
                                           double  x  [],      //(out)  x  [n]                  : x_num
                                           double  y  [],      //(out)  y  [m]                  : y_num
                                           int     x_num,      //(in)
                                           int     y_num,      //(in)  
                                           double  ftp[],      //(in)  ftp[k * p_num + l]       : t_num * p_num          
                                           double  t  [],      //(in)  theta[k] [rad]           : t_num (0 ~ 180 [deg]) 単調増加 
                                           double  p  [],      //(in)  phi  [l] [rad]           : p_num (0 ~ 360 [deg]) 単調増加
                                           int     t_num,      //(in)
                                           int     p_num);     //(in)
  

  void SVGPLOT__WDF(double      ftp  [],
                    double      theta[],
                    double      phi  [],
                    int         theta_num,
                    int         phi_num,
                    const char *filename);
      
#ifdef __cplusplus
}
#endif

#endif
