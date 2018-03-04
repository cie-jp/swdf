/***************************************************************** 
 *
 * SVGPLOT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/


#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include  <math.h>
#include"SVGPLOT.h"

void SVGPLOT_GRID__POLAR(SVG      *svg,
                         REAL8     Xmin,
                         REAL8     Xmax,
                         REAL8     Ymin,
                         REAL8     Ymax,
                         SVG_STYLE gridstyle,int mode){
  int    theta_deg;
  double theta;
  int    phi_deg;
  double phi;
  double r;
  double X0,Y0,RX,RY;
  SVG_STYLE mgridstyle;
  SVG_STYLE borderstyle;
  CHAR  text[2048];
  CHAR  *font_family = "Times New Roman";
  REAL8  font_size   = 20.0;
  SVG_STYLE textstyle;

  SVG_STYLE__SET_001(textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#777777");
  
  SVG_STYLE__SET_001(borderstyle,"1.0","#000000","3.0",NULL,NULL,NULL,NULL,"none");
  
  SVG_STYLE__SET_001(mgridstyle,"1.0","#AAAAAA","0.2",NULL,NULL,NULL,NULL,"none");
  
  X0 = (Xmin + Xmax) / 2.0;
  Y0 = (Ymin + Ymax) / 2.0;
  RX = (Xmax - Xmin) / 2.0;
  RY = (Ymax - Ymin) / 2.0;  
  for(theta_deg = 5;theta_deg < 90;theta_deg += 5){
    theta = theta_deg / 180.0 * M_PI;
    r     = sin(theta);
    SVG__ELLIPSE(svg,X0,Y0,r * RX,r * RY,mgridstyle);
  }

  for(theta_deg = 30;theta_deg < 90;theta_deg += 30){
    theta = theta_deg / 180.0 * M_PI;
    r     = sin(theta);
    SVG__ELLIPSE(svg,X0,Y0,r * RX,r * RY,gridstyle);
  }

  for(phi_deg = 0;phi_deg < 360;phi_deg += 15){
    phi = phi_deg / 180.0 * M_PI;
    SVG__LINE(svg,X0,Y0,X0 + RX * cos(phi),Y0 + RY * sin(phi),mgridstyle);
  }
  
  for(phi_deg = 0;phi_deg < 360;phi_deg += 45){
    phi = phi_deg / 180.0 * M_PI;
    SVG__LINE(svg,X0,Y0,X0 + RX * cos(phi),Y0 + RY * sin(phi),gridstyle);
  }

  for(theta_deg = 30;theta_deg < 90;theta_deg += 30){
    theta = theta_deg / 180.0 * M_PI;
    r     = sin(theta);    
    sprintf(text,"%d^{o}",theta_deg);
    SVG__TEXT(svg,
              X0 + r * RX,Y0 + 5.0,
              0.0,//回転しない
              text,1,font_family,font_size,textstyle,
              1, //halign
              0);//valign
  }

  SVG__TEXT(svg,
            X0 + 0.97 * RX,Y0 + 5.0,
            0.0,//回転しない
            "theta",1,
            font_family,font_size * 1.5,textstyle,
            1, //halign
            0);//valign


  for(phi_deg = 0;phi_deg < 360;phi_deg += 30){
    phi = phi_deg / 180.0 * M_PI;
    sprintf(text,"%d^{o}",phi_deg);

    SVG__TEXT(svg,
              X0 + ((mode == 0) ? +1 : -1) * 1.1 * RX * cos(phi),Y0 + 1.1 * RY * sin(phi),
              0.0,//回転しない
              text,1,
              font_family,font_size,textstyle,
              1, //halign
              1);//valign
  }

  phi_deg = 45;
  phi = phi_deg / 180.0 * M_PI;
  SVG__TEXT(svg,
            X0 + 1.2 * RX * cos(phi),Y0 + 1.2 * RY * sin(phi),  
            0.0,//回転しない
            "phi",1,font_family,
            font_size * 1.5,textstyle,
            1, //halign
            0);//valign

  SVG__ELLIPSE(svg,X0,Y0,RX,RY,borderstyle);

}

void SVGPLOT_GRID__POLAR2(SVGPLOT *plt,int mode){
  SVG_STYLE gridstyle;
  
  SVG_STYLE__SET_001(gridstyle,"1.0","#AAAAAA","0.5",NULL ,NULL,NULL,NULL,"none");

  SVGPLOT_GRID__POLAR(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,gridstyle,mode);
}

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
                                         int     p_num){     //(in)
  double  x_tmp;
  double  y_tmp;
  double  r_tmp;
  double  t_tmp;
  double  p_tmp;
  double  tkl,tku;
  double  pll,plu;
  double  dt;
  double  dp;
  double  ftp_ll;
  double  ftp_lu;
  double  ftp_ul;
  double  ftp_uu;  
  int     n,m,q;
  int     kl,ku;
  int     ll,lu;

  for(n = 0;n < x_num;n++){
    x[n] = -1.0 + 2.0 * n / (x_num - 1.0);
  }

  for(m = 0;m < y_num;m++){
    y[m] = -1.0 + 2.0 * m / (y_num - 1.0);
  }

  for(n = 0;n < x_num;n++){
    x_tmp = x[n];
    for(m = 0;m < y_num;m++){
      y_tmp = y[m];
      r_tmp = sqrt(x_tmp * x_tmp + y_tmp * y_tmp);
      if(r_tmp > 1.0){
        fxy_north[n * y_num + m] = NAN;
        fxy_south[n * y_num + m] = NAN;
      }else{

        p_tmp = atan2(y_tmp,x_tmp);
        if(p_tmp < 0.0){
           p_tmp += 2.0 * M_PI;
        }

        for(ll = 0;ll < p_num;ll++){
          pll = p[ll];
          if(ll != p_num - 1){
            lu  = ll + 1;
            plu = p[lu];
          }else{
            lu  = 0;
            plu = p[lu] + 2.0 * M_PI;
          }
          if((pll <= p_tmp) && (p_tmp <= plu)){
            break;
          }
        }        

        for(q = 0;q < 2;q++){
          t_tmp = acos(((q == 0) ? +1 : -1) * sqrt(1.0 - r_tmp * r_tmp));

          for(kl = t_num - 1;kl >= 0;kl--){
            if(t[kl] <= t_tmp){
              break;
            }
          }        
          if(kl == -1){
            kl =   0;
          }

          for(ku = 0;ku < t_num;ku++){
            if(t[ku] >= t_tmp){
              break;
            }
          }
          if(ku == t_num){
            ku =  t_num - 1;
          }
          
          tkl = t[kl];
          tku = t[ku];
          
          ftp_ll = ftp[kl * p_num + ll];
          ftp_lu = ftp[kl * p_num + lu];
          ftp_ul = ftp[ku * p_num + ll];
          ftp_uu = ftp[ku * p_num + lu];
          
          dt = (tkl != tku) ? ((t_tmp - tkl) / (tku - tkl)) : 0.5;
          dp = (pll != plu) ? ((p_tmp - pll) / (plu - pll)) : 0.5;

          if(q == 0){
            fxy_north[             n  * y_num + m] = (1.0 - dt) * (1.0 - dp) * ftp_ll + (1.0 - dt) * dp * ftp_lu + dt * (1.0 - dp) * ftp_ul + dt * dp * ftp_uu;
          }else{
            fxy_south[(x_num - 1 - n) * y_num + m] = (1.0 - dt) * (1.0 - dp) * ftp_ll + (1.0 - dt) * dp * ftp_lu + dt * (1.0 - dp) * ftp_ul + dt * dp * ftp_uu; 
          }
        }        
      }      
    }
  }
}
