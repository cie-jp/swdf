/***************************************************************** 
 *
 * SVGPLOT INITIALIZE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__INITIALIZE_001(SVGPLOT    *plt,
			     const CHAR *filename,
			     REAL8       width_cm,
			     REAL8       height_cm,
			     INT4        dpi){
  SVG   svg;
  REAL8 svgwidth_px,svgheight_px;
  REAL8 pltwidth_cm,pltheight_cm;
  REAL8 pltwidth_px,pltheight_px;
  REAL8 Xmin,Xmax;
  REAL8 Ymin,Ymax;

  svgwidth_px  = dpi / 2.54 * width_cm ;
  svgheight_px = dpi / 2.54 * height_cm;

  pltwidth_cm  = 0.6 * width_cm;
  pltheight_cm = pltwidth_cm / (0.5 * (1.0 + sqrt(5.0)));

  pltwidth_px  = dpi / 2.54 * pltwidth_cm ;
  pltheight_px = dpi / 2.54 * pltheight_cm;

  Xmin         = (svgwidth_px  - pltwidth_px ) / 2.0;
  Xmax         = Xmin + pltwidth_px ;

  Ymin         = (svgheight_px - pltheight_px) / 2.0;
  Ymax         = Ymin + pltheight_px;

  svg.width    = svgwidth_px ;
  svg.height   = svgheight_px;

  if(filename == NULL){
    svg.fp = stdout;
    strcpy(plt->filename,"");
  }else{
    if((svg.fp = fopen(filename,"w")) == NULL){
      fprintf(stderr,"[ERROR : SVGPLOT__INITIALIZE_001]\n");
      exit(EXIT_FAILURE);
    }
    strcpy(plt->filename,filename);
  }

  plt->svg  = svg;
  plt->Xmin = Xmin;
  plt->Xmax = Xmax;
  plt->Ymin = Ymin;
  plt->Ymax = Ymax;

  SVG__HEADER(&plt->svg);

  // ========================================================================
  // グリッド線設定
  // ========================================================================
  SVG_STYLE__SET_001(plt->xgrid1style,"1.0","#333333","0.5",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->xgrid2style,"1.0","#333333","0.1","2,1",NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->tgrid1style,"1.0","#333333","0.5",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->tgrid2style,"1.0","#333333","0.1","2,1",NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ygrid1style,"1.0","#333333","0.5",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ygrid2style,"1.0","#333333","0.1","2,1",NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->zgrid1style,"1.0","#333333","0.5",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->zgrid2style,"1.0","#333333","0.1","2,1",NULL,"round","round","none");
  // ========================================================================
  // 目盛設定
  // ========================================================================
  SVG_STYLE__SET_001(plt->xtics1linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->xtics2linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ttics1linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ttics2linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ytics1linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ytics2linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ztics1linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  SVG_STYLE__SET_001(plt->ztics2linestyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");
  plt->xtics1len = -20.0;
  plt->xtics2len =  -8.0;
  plt->ttics1len = -20.0;
  plt->ttics2len =  -8.0;
  plt->ytics1len = -20.0;
  plt->ytics2len =  -8.0;
  plt->ztics1len = -20.0;
  plt->ztics2len =  -8.0;

  plt->xtics1textoffset = 35.0;
  plt->xtics2textoffset = 35.0;
  plt->tticstextoffset1 =130.0;
  plt->tticstextoffset2 = 35.0;
  plt->tticstextoffset3 = 75.0;
  plt->ytics1textoffset = 35.0;
  plt->ytics2textoffset = 35.0;
  plt->ztics1textoffset = 35.0;
  plt->ztics2textoffset = 35.0;

  strcpy(plt->xtics1font_family,"Times New Roman");
  strcpy(plt->xtics2font_family,"Times New Roman");
  strcpy(plt->ttics1font_family,"Times New Roman");
  strcpy(plt->ttics2font_family,"Times New Roman");
  strcpy(plt->ytics1font_family,"Times New Roman");
  strcpy(plt->ytics2font_family,"Times New Roman");
  strcpy(plt->ztics1font_family,"Times New Roman");
  strcpy(plt->ztics2font_family,"Times New Roman");

  plt->xtics1font_size = 34.0;
  plt->xtics2font_size = 20.0;
  plt->ttics1font_size = 34.0;
  plt->ttics2font_size = 20.0;
  plt->ytics1font_size = 34.0;
  plt->ytics2font_size = 20.0;
  plt->ztics1font_size = 34.0;
  plt->ztics2font_size = 20.0;

  SVG_STYLE__SET_001(plt->xtics1textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->xtics2textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ttics1textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ttics2textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ytics1textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ytics2textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ztics1textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ztics2textstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");

  // ========================================================================
  // カラーバーの設定
  // ========================================================================
  plt->cboffset = 10.0;
  plt->cbwidth  = 30.0;
  SVG_STYLE__SET_001(plt->cbborderstyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");  

  // ========================================================================
  // 枠線設定
  // ========================================================================
  SVG_STYLE__SET_001(plt->borderstyle,"1.0","#000000","1.0",NULL ,NULL,"round","round","none");

  // ========================================================================
  // 凡例設定
  // ========================================================================
  strcpy(plt->legendfont_family ,"Times New Roman");
  plt->legendfont_size = 32.0;
  SVG_STYLE__SET_001(plt->legendstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  
  // ========================================================================
  // ラベル設定
  // ========================================================================
  plt->xlabeloffset  = 160.0;
  plt->ylabeloffset  = 220.0;
  plt->cblabeloffset = 180.0;

  strcpy(plt->xlabelfont_family ,"Times New Roman");
  strcpy(plt->ylabelfont_family ,"Times New Roman");
  strcpy(plt->cblabelfont_family,"Times New Roman");

  plt->xlabelfont_size  = 48.0;
  plt->ylabelfont_size  = 48.0;
  plt->cblabelfont_size = 48.0;

  SVG_STYLE__SET_001(plt->xlabelstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->ylabelstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  SVG_STYLE__SET_001(plt->cblabelstyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");
  
  // ========================================================================
  // タイトル設定
  // ========================================================================
  plt->titleoffset   =  80.0;  
  strcpy(plt->titlefont_family ,"Times New Roman");
  plt->titlefont_size = 56.0;
  SVG_STYLE__SET_001(plt->titlestyle,"1.0","none",NULL,NULL ,NULL,NULL,NULL,"#000000");

  // ========================================================================
  // パレット設定
  // ========================================================================
  SVGPLOT_PALETTE__Create6(&plt->pal);

  // ========================================================================
  // 軸レンジの初期設定
  // ========================================================================
  SVGPLOT__SET_RANGE_X_001(plt);
  SVGPLOT__SET_RANGE_T_001(plt);
  SVGPLOT__SET_RANGE_Y_001(plt);
  SVGPLOT__SET_RANGE_Z_001(plt);
  // ========================================================================
  // スケールタイプの初期設定
  // ========================================================================
  SVGPLOT__SET_SCALETYPE_X(plt,0);//linear scale
  SVGPLOT__SET_SCALETYPE_Y(plt,0);//linear scale
  SVGPLOT__SET_SCALETYPE_Z(plt,0);//linear scale
  // ========================================================================
  // データリストの初期化
  // ========================================================================
  SVGPLOT_DATALIST__INITIALIZE(&plt->list);
}

void SVGPLOT__INITIALIZE_002(SVGPLOT    *plt,
			     const CHAR *filename){
  REAL8 width_cm  =  14.0;
  REAL8 height_cm = width_cm / sqrt(2.0);
  INT4  dpi       = 350;
  
  SVGPLOT__INITIALIZE_001(plt,filename,width_cm,height_cm,dpi);
}

void SVGPLOT__INITIALIZE_003(SVGPLOT    *plt){
  SVGPLOT__INITIALIZE_002(plt,NULL);
}
