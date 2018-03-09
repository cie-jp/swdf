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

void SVGPLOT_2D__XY_HISTOGRAM(SVG        *svg,        
                              REAL8       Xmin,       
                              REAL8       Xmax,       
                              REAL8       Ymin,       
                              REAL8       Ymax,       
                              REAL8       xmin,       
                              REAL8       xmax,       
                              INT4        xscaletype, 
                              REAL8       ymin,       
                              REAL8       ymax,       
                              INT4        yscaletype, 
                              REAL8       xtic_min[],
                              REAL8       xtic_max[],        
                              REAL8       y[],        
                              INT4        num,        
                              const CHAR *opacity,         
                              const CHAR *stroke,          
                              const CHAR *stroke_width,    
                              const CHAR *stroke_dasharray,
                              const CHAR *stroke_dashoffset,
                              const CHAR *stroke_linecap, 
                              const CHAR *stroke_linejoin,
                              const CHAR *fill){
  SVG_STYLE style;
  REAL8     X0,X1;
  REAL8     Y0,Y1;
  INT4      n;

  SVG_STYLE__SET_001(style,opacity,stroke,stroke_width,stroke_dasharray,stroke_dashoffset,stroke_linecap,stroke_linejoin,fill);

  fprintf(svg->fp,
	  "<g>\n");

  for(n = 0;n < num;n++){
    if((isnan(xtic_min[n]) || isinf(xtic_min[n]) || (xtic_min[n] < xmin) || (xmax < xtic_min[n])) ||
       (isnan(xtic_max[n]) || isinf(xtic_max[n]) || (xtic_max[n] < xmin) || (xmax < xtic_max[n])) ||
       (isnan(y[n]) || isinf(y[n]) || (y[n] < ymin) || (ymax < y[n])) ){
      continue;
    }

    X0 = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,xtic_min[n]);
    X1 = SVGPLOT_BASE__POSITION_REAL8(Xmin,Xmax,xmin,xmax,xscaletype,xtic_max[n]);
    Y0 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype,y[n]);
    Y1 = SVGPLOT_BASE__POSITION_REAL8(Ymin,Ymax,ymin,ymax,yscaletype, 0.0);

    if(X0 < Xmin){
      X0 = Xmin;
    }
    if(X0 > Xmax){
      X0 = Xmax;
    }

    if(X1 < Xmin){
      X1 = Xmin;
    }
    if(X1 > Xmax){
      X1 = Xmax;
    }

    if(Y1 < Ymin){
      Y1 = Ymin;
    }
    if(Y1 > Ymax){
      Y1 = Ymax;
    }

    if(isnan(X0) || isinf(X0) ||
       isnan(X1) || isinf(X1) ||
       isnan(Y0) || isinf(Y0) || isnan(Y1)){
      fprintf(stderr,"[ERROR : SVGPLOT_2D__XY_HISTOGRAM] NaN or inf\n");
      exit(EXIT_FAILURE);
    }

    SVG__RECT(svg,X0,Y0,X1,Y1,style);
  }

  fprintf(svg->fp,
	  "</g>\n");
}

void SVGPLOT__HISTOGRAM(double      x[],
                        int         num,
                        double      xmin,
                        double      xmax,
                        int         div,
                        const char *xlabel,
                        const char *ylabel,
                        const char *title,
                        const char *filename){
  void   *buf;
  double *xtic_min;//[div]
  double *xtic_max;//[div]
  double *hist;    //[div]
  FILE   *fp;
  int     n,m;
  double  xdif;
  double  ymin,ymax;
  int     xscaletype;
  int     yscaletype;
  SVGPLOT plt;
  
  if((buf = malloc(sizeof(double) * div + sizeof(double) * div + sizeof(double) * div)) == NULL){
    exit(EXIT_FAILURE);
  }
  xtic_min =  buf;
  xtic_max = &xtic_min[div];
  hist     = &xtic_max[div];
  
  if((fp = fopen(filename,"w")) == NULL){
    exit(EXIT_FAILURE);
  }

  xdif = (xmax - xmin) / (double)div;

  for(m = 0;m < div;m++){
    xtic_min[m] = xmin + m * xdif - 0.5 * xdif;
    xtic_max[m] = xmin + m * xdif + 0.5 * xdif;
  }

  for(m = 0;m < div;m++){
    hist[m] = 0.0;
  }

  for(n = 0;n < num;n++){
    for(m = 0;m < div;m++){
      if((xtic_min[m] <= x[n]) && (x[n] < xtic_max[m])){
        hist[m]++;
        break;
      }
    }
  }

  ymin = 0.0;
  ymax = 0.0;
  for(m = 0;m < div;m++){
    if(ymax < hist[m]){
       ymax = hist[m];
    }
  }

  SVGPLOT__INITIALIZE_002(&plt,filename);

  xscaletype = 0;
  yscaletype = 0;
  
  SVGPLOT__SET_SCALETYPE_X(&plt,xscaletype);
  SVGPLOT__SET_SCALETYPE_Y(&plt,yscaletype);

  SVGPLOT__SET_RANGE_X_003(&plt,xmin,xmax);
  SVGPLOT__SET_RANGE_Y_003(&plt,ymin,ymax);  

  //グラフの描画
  SVGPLOT_2D__XY_HISTOGRAM(&plt.svg,
                           plt.Xmin,
                           plt.Xmax,
                           plt.Ymin,
                           plt.Ymax,
                           xmin,xmax,
                           xscaletype,
                           ymin,ymax,
                           yscaletype,
                           xtic_min,xtic_max,
                           hist,div,
                           "1.0",    //不透明度
                           "#FFFFFF",//"#FF0000",//赤線
                           "2.0px",  //線の太さ
                           NULL,     //実線
                           NULL,
                           NULL,
                           NULL,
                           "#5555FF");//塗りつぶしの色
  
  //グラフの目盛, 枠線を描画
  SVGPLOT__XY_AUX(&plt,
		  1,1,1,1,//グリッドの有無  (横軸大目盛,横軸小目盛,縦軸大目盛,縦軸小目盛)
		  1,1,1,1,//目盛(線)  の有無
		  1,0,1,0,//目盛(数値)の有無
		  1);     //枠線の有無
    
  //x軸ラベルの設定
  SVGPLOT__XLABEL(&plt,
		  xlabel,//x軸(下)
		  NULL); //x軸(上)
  //y軸ラベルの設定
  SVGPLOT__YLABEL(&plt,
		  ylabel,//y軸(左)
		  NULL); //y軸(右)

  SVGPLOT__TITLE (&plt,
		  title);

  SVGPLOT__FINALIZE(&plt);

  free(buf);
}
