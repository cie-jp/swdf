SVGPlot:: SVGPlot(const STRING &filename){
  SVGPLOT__INITIALIZE_001(&plt,
                          &filename[0],
                          width_cm,
                          height_cm,
                          dpi);
  SVGPLOT_PALETTE__Create10(&plt.pal);
  xmin = 0LL;
  xmax = 0LL;
  ymin = 0.0;
  ymax = 0.0;
  zmin = 0.0;
  zmax = 0.0;
  num  =   0;
}

SVGPlot::~SVGPlot(){
  SVGPLOT__FINALIZE(&plt);
}

void SVGPlot::draw_border(){
  SVG__RECT(&plt.svg,plt.Xmin,plt.Ymin,plt.Xmax,plt.Ymax,plt.borderstyle);
}

void SVGPlot::set_plot_region(const INT plot_id,const INT plot_num,const INT mode){
  REAL8 Ymargin = 15.0;//[px]
  REAL8 svgwidth_px,svgheight_px;
  REAL8 pltwidth_cm,pltheight_cm;
  REAL8 pltwidth_px,pltheight_px;
  REAL8 Xmin,Xmax;
  REAL8 Ymin,Ymax;
  REAL8 Y0;
  
  //ピクセルに単位変換
  svgwidth_px  = dpi / 2.54 * width_cm ;
  svgheight_px = dpi / 2.54 * height_cm;
  
  //プロット領域の大きさの設定
  pltwidth_cm  = 0.6 * width_cm;
  pltheight_cm = pltwidth_cm / (0.5 * (1.0 + sqrt(5.0)));
  if(mode == 1){
    pltwidth_cm = pltheight_cm;//square
  }
  
  //ピクセルに単位変換
  pltwidth_px  = dpi / 2.54 * pltwidth_cm ;
  pltheight_px = dpi / 2.54 * pltheight_cm;
  
  //プロット領域の位置を設定
  Xmin         = (svgwidth_px  - pltwidth_px ) / 2.0;
  Xmax         = Xmin + pltwidth_px ;
  
  Y0           = pltheight_px * (plot_num - 1 - plot_id) / plot_num;
  Ymin         = (svgheight_px - pltheight_px) / 2.0 + Y0;
  Ymax         = Ymin + pltheight_px / plot_num;
  Ymin += Ymargin;
  Ymax -= Ymargin;

  plt.Xmin = Xmin;
  plt.Xmax = Xmax;
  plt.Ymin = Ymin;
  plt.Ymax = Ymax;
}

void SVGPlot::timespan(const STRING &ts,const STRING &te){
  xmin = T2000__MAKE_FROM_TEXT(&ts[0]);
  xmax = T2000__MAKE_FROM_TEXT(&te[0]);
  SVGPLOT__SET_RANGE_T_003(&plt,
                           T2000__MAKE_FROM_TEXT(&ts[0]),
                           T2000__MAKE_FROM_TEXT(&te[0]));
}
