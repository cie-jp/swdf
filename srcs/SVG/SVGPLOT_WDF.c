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

//36pt theta
void THETA(SVG  *svg,
           REAL8 x0,
           REAL8 y0){
  fprintf(svg->fp,
          "<path fill=\"#EEEEEE\" d=\"M%f,%fc-0.4,1.7-1.2,4.7-2.5,7.3c-1.3,2.4-2.6,4.2-4.2,4.2c-1.2,0-1.9-1-1.9-4.4c0-1.5,0.2-3.6,1.1-7.1L%f,%f"
          "M%f,%fc0.6-2.3,1.3-5.2,2.8-7.7c1-1.8,2.3-3.8,3.9-3.8c1.8,0,2,2.3,2,4.3c0,1.8-0.3,3.6-1.1,7.1H%fz M%f,%f"
          "c0-2.4-0.6-7.4-4.3-7.4c-5,0-10.5,10.1-10.5,18.3c0,3.4,1,7.4,4.3,7.4C%f,%f,%f,%f,%f,%fz\"/>",
          x0,y0,
          x0,y0,
          x0 - 7.1,y0 -  1.1,
          x0 - 7.1,
          x0 + 3.9,y0 -  6.0,
          x0 - 1.6,y0 + 12.3,
          x0 + 3.9,y0 +  2.0,
          x0 + 3.9,y0 -  6.0);  
  /*
  fprintf(svg->fp,
          "<path fill=\"#EEEEEE\" d=\"M%f,%fc-0.1,0.6-0.4,1.6-0.9,2.4c-0.4,0.8-0.9,1.4-1.4,1.4c-0.4,0-0.6-0.3-0.6-1.5"
          "c0-0.5,0.1-1.2,0.4-2.4H%f M%f,%fc0.2-0.8,0.5-1.7,0.9-2.6c0.3-0.6,0.7-1.3,1.3-1.3c0.6,0,0.7,0.7,0.7,1.4"
          "c0,0.6-0.1,1.2-0.4,2.4H%fz M%f,%fc0-0.8-0.2-2.4-1.4-2.4c-1.7,0-3.5,3.4-3.5,6.1c0,1.1,0.4,2.4,1.4,2.4"
          "C%f,%f,%f,%f,%f,%fz\"/>",
          x0,y0,
          x0,
          x0 - 2.4,y0 - 0.4,
          x0 - 2.4,
          x0 + 1.3,y0 - 2.0,
          x0 - 0.5,y0 + 4.1,
          x0 + 1.3,y0 + 0.7,
          x0 + 1.3,y0 - 2.0);  
  */
}

//36pt phi
void PHI(SVG  *svg,
         REAL8 x0,
         REAL8 y0){
  fprintf(svg->fp,
          "<path fill=\"#000000\" d=\"M%f,%fc2.7,0.2,4.8,1.8,4.8,5c0,4.3-3.1,9.4-8.5,9.8L%f,%f M%f,%fc-2.2-0.1-4.7-1.4-4.7-5"
          "c0-4.3,3.1-9.3,8.4-9.8L%f,%fz M%f,%fc0-0.1,0.1-0.5,0.1-0.5c0-0.1,0-0.4-0.5-0.4c-0.3,0-0.4,0.1-0.5,0.7l-2.1,8.3"
          "c-5.7,0.2-11,5-11,9.8c0,3.4,2.5,6.3,6.9,6.5c-0.3,1.1-0.5,2.3-0.8,3.4c-0.4,1.7-0.8,3.1-0.8,3.2c0,0.3,0.3,0.4,0.5,0.4"
          "c0.2,0,0.2-0.1,0.3-0.2c0.1-0.1,0.3-0.9,0.4-1.4l1.4-5.4c5.8-0.2,11-5,11-9.8c0-2.8-1.9-6.2-6.9-6.5L%f,%fz\"/>",
          x0,y0,
          x0,y0,
          x0 - 4.6,y0 + 14.8,
          x0 - 4.6,y0 + 14.8,
          x0 + 2.2,y0 -  8.9,
          x0 + 2.2,y0 -  8.9);
  /*
  fprintf(svg->fp,
          "<path fill=\"#EEEEEE\" d=\"M%f,%fc0.9,0.1,1.6,0.6,1.6,1.7c0,1.4-1,3.1-2.8,3.2L%f,%f M%f,%f"
          "c-0.7,0-1.6-0.5-1.6-1.6c0-1.4,1-3.1,2.8-3.3L%f,%fz M%f,%fc0,0,0.1-0.2,0.1-0.2c0,0,0-0.1-0.2-0.1"
          "c-0.1,0-0.1,0.1-0.2,0.2l-0.7,2.8c-1.9,0.1-3.6,1.6-3.6,3.2c0,1.1,0.8,2.1,2.3,2.2c-0.1,0.4-0.2,0.7-0.3,1.1"
          "c-0.1,0.6-0.2,1-0.2,1.1c0,0.1,0.1,0.1,0.1,0.1s0.1,0,0.1-0.1c0,0,0.1-0.3,0.1-0.5l0.5-1.8c1.9-0.1,3.6-1.7,3.6-3.2"
          "c0-1-0.6-2.1-2.3-2.2L%f,%fz\"/>",
          x0,y0,
          x0,y0,
          x0 - 1.5,y0 + 4.9,
          x0 - 1.5,y0 + 4.9,
          x0 + 0.7,y0 - 2.9,
          x0 + 0.7,y0 - 2.9);
  */
}

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
  REAL8  font_size   = 15.0;
  SVG_STYLE textstyle;
  double rpos = 0.94;
  SVG_STYLE__SET_001(textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#BBBBBB");
  
  SVG_STYLE__SET_001(borderstyle,"1.0","#000000","2.0",NULL,NULL,NULL,NULL,"none");
  
  SVG_STYLE__SET_001(mgridstyle,"1.0","#AAAAAA","0.2","2,2",NULL,NULL,NULL,"none");
  
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

  //仰角の目盛
  double rad;
  if(mode == 0){
    rad = -15.0 / 180.0 * M_PI;
    for(theta_deg = 0;theta_deg < 90;theta_deg += 15){
      theta = theta_deg / 180.0 * M_PI;
      r     = sin(theta);    
      sprintf(text,"%d^{o}",theta_deg);
      SVG__TEXT(svg,
                X0 + r * RX * cos(rad),Y0 + r * RX * sin(rad),
                rad / M_PI * 180.0,//回転角
                text,1,font_family,font_size,textstyle,
                1, //halign
                0);//valign
    }
  }else{
    rad = +15.0 / 180.0 * M_PI;
    for(theta_deg = 90 + 15;theta_deg <= 180;theta_deg += 15){
      theta = theta_deg / 180.0 * M_PI;
      r     = sin(theta);    
      sprintf(text,"%d^{o}",theta_deg);
      SVG__TEXT(svg,
                X0 - r * RX * cos(rad),Y0 - r * RX * sin(rad),
                rad / M_PI * 180.0,//回転しない
                text,1,font_family,font_size,textstyle,
                1, //halign
                0);//valign
    }
  }

  if(mode == 0){
    THETA(svg,X0 + 0.5 * RX,Y0 + 80);
  }
  /*
  SVG__TEXT(svg,
            X0 + 0.97 * RX,Y0 + 5.0,
            0.0,//回転しない
            "theta",1,
            font_family,font_size * 1.5,textstyle,
            1, //halign
            0);//valign
  */

  //方位角の目盛
  for(phi_deg = 0;phi_deg < 360;phi_deg += 30){
    phi = phi_deg / 180.0 * M_PI;
    sprintf(text,"%d^{o}",phi_deg);

    SVG__TEXT(svg,
              X0 + ((mode == 0) ? +1 : -1) * rpos * RX * cos(phi),Y0 + rpos * RY * sin(phi),
              0.0,//回転しない
              text,1,
              font_family,font_size,textstyle,
              1, //halign
              1);//valign
  }

  if(mode == 0){
    phi_deg = 45;
    phi = phi_deg / 180.0 * M_PI;  
    PHI(svg,X0 + 1.1 * RX * cos(phi),Y0 + 1.1 * RY * sin(phi));
  }
  //X0 + 0.8 * RX * cos(phi),
  //Y0 + 0.8 * RY * sin(phi));
  /*
  phi_deg = 45;
  phi = phi_deg / 180.0 * M_PI;
  SVG__TEXT(svg,
            X0 + 1.2 * RX * cos(phi),Y0 + 1.2 * RY * sin(phi),  
            0.0,//回転しない
            "phi",1,font_family,
            font_size * 1.5,textstyle,
            1, //halign
            0);//valign
  */
  
  SVG__ELLIPSE(svg,X0,Y0,RX,RY,borderstyle);

}

void SVGPLOT_GRID__POLAR2(SVGPLOT *plt,int mode){
  SVG_STYLE gridstyle;
  
  SVG_STYLE__SET_001(gridstyle,"1.0","#AAAAAA","0.4","5,2",NULL,NULL,NULL,"none");

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

void SVGPLOT__WDF(double      ftp  [],
                  double      theta[],
                  double      phi  [],
                  int         theta_num,
                  int         phi_num,
                  const char *filename){
  int     x_num;
  int     y_num;
  void   *buf;
  double *x;        //[x_num]
  double *y;        //[y_num]
  double *fxy_north;//[x_num * y_num]
  double *fxy_south;//[x_num * y_num]
  SVGPLOT plt;
  double  X0,Y0,W,H;
  double  zmin,zmax;
  
  x_num = 1000;
  y_num = 1000;

  if((buf = malloc((x_num + y_num + x_num * y_num + x_num * y_num) * sizeof(double))) == NULL){
    fprintf(stderr,"ERROR : SVGPLOT WDF\n");
    exit(EXIT_FAILURE);
  }

  x         = buf;
  y         = x + x_num;
  fxy_north = y + y_num;
  fxy_south = fxy_north + x_num * y_num;
  
  CALCULATION__SPHERICAL_DISTRIBUTION(fxy_north,
                                      fxy_south,
                                      x,y,
                                      x_num,y_num,
                                      ftp,
                                      theta,
                                      phi,
                                      theta_num,
                                      phi_num);

  SVGPLOT__INITIALIZE_002(&plt,filename);

  X0 = (plt.Xmin + plt.Xmax) / 2.0;
  Y0 = (plt.Ymin + plt.Ymax) / 2.0;
  W  = (plt.Xmax - plt.Xmin);
  H  = (plt.Ymax - plt.Ymin);

  plt.Xmin = X0 - H / 2.0 - H / 2.0 - 5;
  plt.Xmax = X0 + H / 2.0 - H / 2.0 - 5; 
  
  SVGPLOT_PALETTE__Create10(&plt.pal);

  zmin = fmin(STATS__MIN(fxy_north,x_num * y_num,0),
              STATS__MIN(fxy_south,x_num * y_num,0));
  zmax = fmax(STATS__MAX(fxy_north,x_num * y_num,0),
              STATS__MAX(fxy_south,x_num * y_num,0));

  SVGPLOT__SET_RANGE_Z_003(&plt,zmin,zmax);  
  
  SVGPLOT__XYZ_CONTOUR(&plt,x,x_num,y,y_num,fxy_north,-1.0,-1.0,0);

  SVGPLOT_GRID__POLAR2(&plt,0);
  /*
  SVGPLOT__COLORBAR(&plt,
                    1,1,
                    2,2,
                    2,0,
                    1);
  */
  plt.Xmin = X0 - H / 2.0 + H / 2.0 + 5;
  plt.Xmax = X0 + H / 2.0 + H / 2.0 + 5; 

  SVGPLOT_PALETTE__Create10(&plt.pal);
  
  SVGPLOT__XYZ_CONTOUR(&plt,x,x_num,y,y_num,fxy_south,-1.0,-1.0,0);

  SVGPLOT_GRID__POLAR2(&plt,1);

  SVGPLOT__COLORBAR(&plt,
                    1,1,
                    2,2,
                    2,0,
                    1);

  SVGPLOT__FINALIZE(&plt);

  free(buf);
}
