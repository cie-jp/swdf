#include"CDFData.h"

class SVGPlot{
private:
  SVGPLOT plt;
 public:
  void tplot(TMatrix<REAL8>       variable,
             TMatrix<TIME_TT2000> depend_0,
             TMatrix<REAL8>       depend_1,
             INT mode = 0){
    SVGPLOT__SET_RANGE_Z_003(&plt,1.0e-6,1.0e-2);
    SVGPLOT__TYZ_CONTOUR(&plt,
                         depend_0.get_dat(),depend_0.get_row(),
                         depend_1.get_dat(),depend_1.get_col(),
                         variable.get_dat(),
                         -1.0,//tgap
                         -1.0,//ygap
                         mode);  //mode 0:最近傍 1: Bilinear補間
    
  }
public:
  SVGPlot(){
    SVGPLOT__INITIALIZE_002(&plt,"plot.svg");
    SVGPLOT_PALETTE__Create10(&plt.pal);
  }
 ~SVGPlot(){
   SVGPLOT__FINALIZE(&plt);
  }
  void add(TMatrix<TIME_TT2000> epoch,TMatrix<REAL> var,const CHAR *label){
    SVGPLOT__ADD_BY_DAT_TY(&plt,epoch.get_dat(),var.get_dat(),epoch.get_row(),
                           0,//点なし
                           label);    
  }
  void timespan(const CHAR *ts,const CHAR *te){
    SVGPLOT__SET_RANGE_T_003(&plt,
                             T2000__MAKE_FROM_TEXT(ts),
                             T2000__MAKE_FROM_TEXT(te));
  }
  void plot(STRING xlabel,STRING ylabel,STRING title){
    SVGPLOT__PLOT_TY(&plt);
    
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    1,0,1,0,
                    1);  
    SVGPLOT__XLABEL(&plt,&xlabel[0],NULL);
    SVGPLOT__YLABEL(&plt,&ylabel[0],NULL);
    SVGPLOT__TITLE (&plt,&title [0]);
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
  void output(CDFData &cdf){
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
    set_label("x",cdf.depend_0_label);
    set_label("y",cdf.depend_1_label);
    set_label("z",cdf.variable_label);

    SVGPLOT__TITLE (&plt,"CDFPLOT");
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
