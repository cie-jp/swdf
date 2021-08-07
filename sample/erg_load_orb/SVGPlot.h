#define SCALETYPE_LINEAR (0)
#define SCALETYPE_LOG    (1)

class PlotElement{
 public:
  STRING xlabel1;
  STRING xlabel2;
  STRING ylabel1;
  STRING ylabel2;
  STRING zlabel1;
  STRING zlabel2;
  DATA   xmin;
  DATA   xmax;
  DATA   ymin;
  DATA   ymax;
  DATA   zmin;
  DATA   zmax;  
};


class SVGPlot{
 private:
  //tplot用のスタック
  EVector     x[50];
  RVector     y[50];
  RMatrix     z[50];
  INT         yscaletype[50];
  INT         zscaletype[50];
  INT         dim[50];
  TIME_TT2000 xmin,xmax;
  REAL8       ymin,ymax;
  REAL8       zmin,zmax;
  INT         num;
private:
  SVGPLOT plt;
  //規定値
  REAL8 width_cm  = 14.0;
  REAL8 height_cm = width_cm / sqrt(2.0);
  INT4  dpi       = 350;
 public:
  SVGPlot(const STRING &filename);
 ~SVGPlot();
  void timespan(const STRING &ts,const STRING &te);
  void set_plot_region(const INT plot_id,const INT plot_num,const INT mode = 0);
  void draw_border();
  void set_autorange(){
    SVGPLOT__SET_RANGE_Y_001(&plt);
    SVGPLOT__SET_RANGE_Z_001(&plt);
  }
  void set_yrange(REAL ymin,REAL ymax){
    this->ymin = ymin;
    this->ymax = ymax;
    SVGPLOT__SET_RANGE_Y_003(&plt,ymin,ymax);
  }
  void set_zrange(REAL zmin,REAL zmax){
    this->zmin = zmin;
    this->zmax = zmax;
    SVGPLOT__SET_RANGE_Z_003(&plt,zmin,zmax);
  }
  void add_plot(const INT plot_id,
                const INT plot_num,
                EVector  &x,
                RVector  &y);
  void tplot(TMatrix<REAL8>       variable,
             TMatrix<TIME_TT2000> depend_0,
             TMatrix<REAL8>       depend_1,
             INT mode = 0){
    //SVGPLOT__SET_RANGE_X_001(&plt);
    SVGPLOT__TYZ_CONTOUR(&plt,
                         depend_0.get_dat(),depend_0.get_row(),
                         depend_1.get_dat(),depend_1.get_col(),
                         variable.get_dat(),
                         -1.0,//tgap
                         -1.0,//ygap
                         mode);  //mode 0:最近傍 1: Bilinear補間
    //グラフの目盛, 枠線を描画
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,//グリッドの有無  (横軸大目盛,横軸小目盛,縦軸大目盛,縦軸小目盛)
                    1,1,1,1,//目盛(線)  の有無
                    0,0,1,0,//目盛(数値)の有無
                    1);     //枠線の有無
    
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
  }
public:
  void add(const EVector &epoch,
           const RVector &var){
    x[num] = epoch;
    y[num] = var;
    dim[num] = 1;
    num++;
  }
  void add(const EVector &epoch,
           const RVector &var1,
           const RMatrix &var2){
    x[num] = epoch;
    y[num] = var1;
    z[num] = var2;
    dim[num] = 2;
    num++;
  }
  void newplot(int yscaletype = SCALETYPE_LINEAR,
               int zscaletype = SCALETYPE_LINEAR){
    INT isinit;

    if((xmin == 0LL) && (xmax == 0LL)){
      isinit = 0;
      for(INT i = 0;i < num;i++){
        for(INT j = 0;j < x[i].get_dim();j++){
          if(!isinit){
            xmin = x[i][j];
            xmax = x[i][j];
            isinit = 1;
          }else{
            if(xmin > x[i][j]){
              xmin = x[i][j];
            }
            if(xmax < x[i][j]){
              xmax = x[i][j];
            }
          }
        }
      }
    }

    if((ymin == 0.0) && (ymax == 0.0)){
      isinit = 0;
      for(INT i = 0;i < num;i++){
        for(INT j = 0;j < y[i].get_dim();j++){
          if(!isinit){
            ymin = y[i][j];
            ymax = y[i][j];
            isinit = 1;
          }else{
            if(ymin > y[i][j]){
              ymin = y[i][j];
            }
            if(ymax < y[i][j]){
              ymax = y[i][j];
            }
          }
        }
      }
    }

    if((zmin == 0.0) && (zmax == 0.0)){
      isinit = 0;
      for(INT i = 0;i < num;i++){
        if(dim[i] != 2){
          continue;
        }
        for(INT j = 0;j < z[i].get_row();j++){
          for(INT k = 0;k < z[i].get_col();k++){
            if(!isinit){
              zmin = z[i][j][k];
              zmax = z[i][j][k];
              isinit = 1;
            }else{
              if(zmin > z[i][j][k]){
                zmin = z[i][j][k];
              }
              if(zmax < z[i][j][k]){
                zmax = z[i][j][k];
              }
            }
          }
        }
      }
    }

    SVGPLOT__SET_RANGE_X_003(&plt,xmin,xmax);
    SVGPLOT__SET_RANGE_Y_003(&plt,ymin,ymax);
    SVGPLOT__SET_RANGE_Z_003(&plt,zmin,zmax);
    SVGPLOT__SET_SCALETYPE_Y(&plt,yscaletype);        
    SVGPLOT__SET_SCALETYPE_Z(&plt,zscaletype);

    const CHAR *lstroke;
    const CHAR *lstroke_width;
    const CHAR *lstroke_dasharray;
    REAL8       pointsize;
    INT4        pointtype;
    const CHAR *pstroke;
    const CHAR *pstroke_width;
    const CHAR *pstroke_dasharray;
    const CHAR *pfill;
    	lstroke           = "#FF2800";
	lstroke_width     = "3.0px";
	lstroke_dasharray = NULL;
	pointsize         = 4.0;
	pointtype         = 0;
	pstroke           = lstroke;
	pstroke_width     = lstroke_width;
	pstroke_dasharray = NULL;      
	pfill             = pstroke;
    
    for(INT i = 0;i < num;i++){
      if(dim[i] == 1){
        if(i == 1){
          lstroke           = "#FFFF00";//黄色
          lstroke_width     = "3.0px";
          lstroke_dasharray = NULL;
          pointsize         = 4.0;
          pointtype         = 0;
          pstroke           = lstroke;
          pstroke_width     = lstroke_width;
          pstroke_dasharray = NULL;      
          pfill             = pstroke;
        }
        if(i == 2){
          lstroke           = "#FFA5FF";//マゼンタ
          lstroke_width     = "3.0px";
          lstroke_dasharray = NULL;
          pointsize         = 4.0;
          pointtype         = 0;
          pstroke           = lstroke;
          pstroke_width     = lstroke_width;
          pstroke_dasharray = NULL;      
          pfill             = pstroke;
        }
        SVGPLOT__TY_LPLOT(&plt,
                          x[i].get_dat(),y[i].get_dat(),x[i].get_row(),-1.0,-1.0,0,
                          "1.0",lstroke,lstroke_width,lstroke_dasharray,NULL,"round","round");
        /*
        SVGPLOT__ADD_BY_DAT_TY(&plt,x[i].get_dat(),y[i].get_dat(),x[i].get_row(),
                               0,//点なし
                               "i");
        SVGPLOT__PLOT_TY(&plt);
        */
      }else{
        SVGPLOT__TYZ_CONTOUR(&plt,
                             x[i].get_dat(),x[i].get_row(),
                             y[i].get_dat(),y[i].get_col(),
                             z[i].get_dat(),
                             -1.0,//tgap
                             -1.0,//ygap
                             1);  //mode 0:最近傍 1: Bilinear補間
      }
    }
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    0,0,1,0,
                    1);
    INT flag;

    flag = 0;
    for(INT i = 0;i < num;i++){
      if(dim[i] == 2){
        flag = 1;
      }
    }
    if(flag){
      SVGPLOT__COLORBAR(&plt,
                        1,1,
                        2,2,
                        2,0,
                        1);
    }
    num  = 0;
    ymin = 0.0;
    ymax = 0.0;
    zmin = 0.0;
    zmax = 0.0;
  }

  void add(const EVector &epoch,
           const RVector &var,
           const CHAR    *label){
    SVGPLOT__ADD_BY_DAT_TY(&plt,epoch.get_dat(),var.get_dat(),epoch.get_row(),
                           0,//点なし
                           label);    
  }
  void plot(){
    SVGPLOT__PLOT_TY(&plt);    
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    0,0,1,0,
                    1);  
  }
  void draw_time(){
    SVGPLOT__TY_AUX(&plt,
                    0,0,0,0,
                    0,0,0,0,
                    1,0,0,0,
                    0);  
  }
  void set_title(const STRING &title){
    SVGPLOT__TITLE (&plt,&title [0]);    
  }
  void aux(STRING xlabel,STRING ylabel,STRING title){
    SVGPLOT__XLABEL(&plt,&xlabel[0],NULL);
    SVGPLOT__YLABEL(&plt,&ylabel[0],NULL);
  }
  //スケールタイプを設定
  void set_scaletype(STRING axis,STRING type){
    switch(axis[0]){
    case 'x':
      SVGPLOT__SET_SCALETYPE_X(&plt,(type == "log") ? 1 : 0);
      break;
    case 'y':
      SVGPLOT__SET_SCALETYPE_Y(&plt,(type == "log") ? 1 : 0);
      break;
    case 'z':
      SVGPLOT__SET_SCALETYPE_Z(&plt,(type == "log") ? 1 : 0);
      break;      
    }
  }

  //ラベルの設定
  void set_label(STRING axis,STRING label){
    switch(axis[0]){
    case 'x':
      SVGPLOT__XLABEL(&plt,&label[0],NULL);//x軸(下), x軸(上)
      break;
    case 'y':
      SVGPLOT__YLABEL(&plt,&label[0],NULL);
      break;
    case 'z':
      SVGPLOT__ZLABEL(&plt,
                      &label[0]);//z軸
      break;      
    }    
  }

  //
  void output(){
    //グラフの目盛, 枠線を描画
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,//グリッドの有無  (横軸大目盛,横軸小目盛,縦軸大目盛,縦軸小目盛)
                    1,1,1,1,//目盛(線)  の有無
                    1,0,1,0,//目盛(数値)の有無
                    1);     //枠線の有無
    
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
  }
  void output2(){
    //グラフの目盛, 枠線を描画
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,//グリッドの有無  (横軸大目盛,横軸小目盛,縦軸大目盛,縦軸小目盛)
                    1,1,1,1,//目盛(線)  の有無
                    1,0,1,0,//目盛(数値)の有無
                    1);     //枠線の有無
    
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
  }
  void cdfplot(CDFData &cdf,INT mode = 0){
    TMatrix<REAL8>       variable_real8;
    TMatrix<TIME_TT2000> depend_0_time_tt2000;
    TMatrix<REAL8>       depend_1_real8;

    variable_real8       = cdf.variable;
    depend_0_time_tt2000 = cdf.depend_0;
    depend_1_real8       = cdf.depend_1;
    
    tplot(variable_real8,
          depend_0_time_tt2000,
          depend_1_real8,
          mode);
  }

};

#include"SVGPlot.hpp"
