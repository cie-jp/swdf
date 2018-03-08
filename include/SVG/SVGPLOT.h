/***************************************************************** 
 *
 * SVGPLOT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_H_INCLUDE_
#define _SVGPLOT_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<stdarg.h>
#include"SVG_BASE.h"
#include"SVGPLOT_AUTOTICS.h"
#include"SVGPLOT_GRID.h"
#include"SVGPLOT_TICS.h"
#include"SVGPLOT_AUTORANGE.h"
#include"SVGPLOT_AUTOGAP.h"
#include"SVGPLOT_PALETTE.h"
#include"SVGPLOT_2D.h"
#include"TEXT_CSV.h"
#include"STATS.h"
#include"SVGPLOT_DATA.h"
#include"SVGPLOT_DATALIST.h"

typedef struct{
  CHAR      filename[2048];
  SVG       svg;
  REAL8     Xmin;
  REAL8     Xmax;
  REAL8     Ymin;
  REAL8     Ymax;
  
  SVG_STYLE xgrid1style;
  SVG_STYLE xgrid2style;
  SVG_STYLE tgrid1style;
  SVG_STYLE tgrid2style;
  SVG_STYLE ygrid1style;
  SVG_STYLE ygrid2style;
  SVG_STYLE zgrid1style;
  SVG_STYLE zgrid2style;

  SVG_STYLE xtics1linestyle;
  SVG_STYLE xtics2linestyle;
  SVG_STYLE ttics1linestyle;
  SVG_STYLE ttics2linestyle;
  SVG_STYLE ytics1linestyle;
  SVG_STYLE ytics2linestyle;
  SVG_STYLE ztics1linestyle;
  SVG_STYLE ztics2linestyle;

  REAL8     xtics1len;
  REAL8     xtics2len;
  REAL8     ttics1len;
  REAL8     ttics2len;
  REAL8     ytics1len;
  REAL8     ytics2len;
  REAL8     ztics1len;
  REAL8     ztics2len;

  REAL8     xtics1textoffset;
  REAL8     xtics2textoffset;
  REAL8     tticstextoffset1;
  REAL8     tticstextoffset2;
  REAL8     tticstextoffset3;
  REAL8     ytics1textoffset;
  REAL8     ytics2textoffset;
  REAL8     ztics1textoffset;
  REAL8     ztics2textoffset;

  CHAR      xtics1font_family[512];
  CHAR      xtics2font_family[512];
  CHAR      ttics1font_family[512];
  CHAR      ttics2font_family[512];
  CHAR      ytics1font_family[512];
  CHAR      ytics2font_family[512];
  CHAR      ztics1font_family[512];
  CHAR      ztics2font_family[512];

  REAL8     xtics1font_size;
  REAL8     xtics2font_size;
  REAL8     ttics1font_size;
  REAL8     ttics2font_size;
  REAL8     ytics1font_size;
  REAL8     ytics2font_size;
  REAL8     ztics1font_size;
  REAL8     ztics2font_size;

  SVG_STYLE xtics1textstyle;
  SVG_STYLE xtics2textstyle;
  SVG_STYLE ttics1textstyle;
  SVG_STYLE ttics2textstyle;
  SVG_STYLE ytics1textstyle;
  SVG_STYLE ytics2textstyle;
  SVG_STYLE ztics1textstyle;
  SVG_STYLE ztics2textstyle;

  REAL8     cboffset;
  REAL8     cbwidth;
  SVG_STYLE cbborderstyle;

  SVG_STYLE borderstyle;

  CHAR      legendfont_family [512];
  REAL8     legendfont_size;
  SVG_STYLE legendstyle;

  REAL8     xlabeloffset;
  REAL8     ylabeloffset;
  REAL8     cblabeloffset;

  CHAR      xlabelfont_family [512];
  CHAR      ylabelfont_family [512];
  CHAR      cblabelfont_family[512];

  REAL8     xlabelfont_size;
  REAL8     ylabelfont_size;
  REAL8     cblabelfont_size;

  SVG_STYLE xlabelstyle;
  SVG_STYLE ylabelstyle;
  SVG_STYLE cblabelstyle;

  REAL8     titleoffset;
  CHAR      titlefont_family [512];
  REAL8     titlefont_size;
  SVG_STYLE titlestyle;

  SVGPLOT_PALETTE pal;

  // ==================================================================
  // 軸レンジ(自動・手動)・スケールタイプ(線形・対数)
  // ==================================================================
  INT4        xautorange;
  REAL8       xmin;
  REAL8       xmax;
  INT4        xscaletype;

  INT4        tautorange;
  TIME_TT2000 tmin;
  TIME_TT2000 tmax;

  INT4        yautorange;
  REAL8       ymin;
  REAL8       ymax;
  INT4        yscaletype;

  INT4        zautorange;
  REAL8       zmin;
  REAL8       zmax;
  INT4        zscaletype;

  // ==================================================================
  // プロットデータリスト
  // ==================================================================
  SVGPLOT_DATALIST list;
}SVGPLOT;

  #include"SVGPLOT_WDF.h"
  #include"SVGPLOT_HIST.h"

void SVGPLOT__INITIALIZE_001(SVGPLOT    *plt,
			     const CHAR *filename,
			     REAL8       width_cm,
			     REAL8       height_cm,
			     INT4        dpi);
void SVGPLOT__INITIALIZE_002(SVGPLOT    *plt,
			     const CHAR *filename);
void SVGPLOT__INITIALIZE_003(SVGPLOT    *plt);

void SVGPLOT__FINALIZE      (SVGPLOT    *plt);

void SVGPLOT__XLABEL     (SVGPLOT    *plt,
			  const CHAR *xlabel_bottom,
			  const CHAR *xlabel_top);
void SVGPLOT__YLABEL     (SVGPLOT    *plt,
			  const CHAR *ylabel_left,
			  const CHAR *ylabel_right);
void SVGPLOT__ZLABEL     (SVGPLOT    *plt,
			  const CHAR *zlabel);

void SVGPLOT__TITLE      (SVGPLOT    *plt,
			  const CHAR *title);

void SVGPLOT__XY_LPLOT   (SVGPLOT    *plt,
			  REAL8       x[],
			  REAL8       y[],
			  INT4        num,
			  REAL8       xgap,
			  REAL8       ygap,		       
			  REAL8       lgap,
			  INT4        mode,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin);

void SVGPLOT__TY_LPLOT   (SVGPLOT    *plt,
			  T2000       t[],
			  REAL8       y[],
			  INT4        num,
			  T2000       tgap,
			  REAL8       ygap,		       
			  INT4        mode,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin);

void SVGPLOT__XY_IPLOT   (SVGPLOT    *plt,
			  REAL8       x[],
			  REAL8       y[],
			  INT4        num,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin);

void SVGPLOT__TY_IPLOT   (SVGPLOT    *plt,
			  T2000       t[],
			  REAL8       y[],
			  INT4        num,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin);

void SVGPLOT__XY_PPLOT   (SVGPLOT    *plt,
			  REAL8       x[],
			  REAL8       y[],
			  INT4        num,
			  REAL8       pointsize,		       
			  INT4        pointtype,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin,
			  const CHAR *fill);

void SVGPLOT__TY_PPLOT   (SVGPLOT    *plt,
			  T2000       t[],
			  REAL8       y[],
			  INT4        num,
			  REAL8       pointsize,		       
			  INT4        pointtype,
			  const CHAR *opacity,
			  const CHAR *stroke,
			  const CHAR *stroke_width,
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,
			  const CHAR *stroke_linejoin,
			  const CHAR *fill);

void SVGPLOT__XYZ_CONTOUR(SVGPLOT    *plt,
			  REAL8       x[],
			  INT4        xnum,
			  REAL8       y[],
			  INT4        ynum,
			  REAL8       z[],
			  REAL8       xgap,
			  REAL8       ygap,
			  INT4        mode);

void SVGPLOT__TYZ_CONTOUR(SVGPLOT    *plt,
			  TIME_TT2000 t[],
			  INT4        tnum,
			  REAL8       y[],
			  INT4        ynum,
			  REAL8       z[],
			  T2000       tgap,
			  REAL8       ygap,
			  INT4        mode);

/*
typedef struct{
  SVG   svg;

  REAL8 Xmin,Xmax;
  REAL8 Ymin,Ymax;

  CHAR *title;
  
  INT4  dim;

  void *data;      //2D : data[n0]
  INT4  data_num;  //3D : data[n0 *  dep1_num + n1]
  INT4  data_type; //4D : data[n0 * (dep1_num * dep2_num) + n1 * dep1_num + n2]
  CHAR *data_label;  
  INT4  data_scale;
  DATA  data_min;
  DATA  data_max;

  void *dep0;      //dep0[n0] (n0 = [0:dep0_num - 1])
  INT4  dep0_num;
  INT4  dep0_type;
  CHAR *dep0_label;
  DATA  dep0_scale;
  DATA  dep0_min;
  DATA  dep0_max;

  void *dep1;      //dep1[n1] (n1 = [0:dep1_num - 1])
  INT4  dep1_num;
  INT4  dep1_type;
  CHAR *dep1_label;
  DATA  dep1_scale;
  DATA  dep1_min;
  DATA  dep1_max;
  
  void *dep2;      //dep2[n2] (n2 = [0:dep2_num - 1])
  INT4  dep2_num;
  INT4  dep2_type;
  CHAR *dep2_label;
  DATA  dep2_scale;
  DATA  dep2_min;
  DATA  dep2_max;

}SVGPLOT;
*/

//void SVGPLOT__INITIALIZE(SVGPLOT *plt,FILE *fp,INT4 width,INT4 height);

//void SVGPLOT__PLOT_2D   (SVGPLOT *plt);

// =================================================================
// 
// =================================================================
/*
void SVGPLOT__SET_XTICS_MODE (SVGPLOT *plt,
			      INT4     tics_mode){//0: auto, 1: manual
  plt->tics_mode_x1 = tics_mode;
}

void SVGPLOT__SET_XTICS_VALUE(SVGPLOT *plt,
			      REAL8    tics_val1[],
			      INT4     tics_num1,
			      REAL8    tics_val2[],
			      INT4     tics_num2){
  plt->tics_mode_x1 = 1;
  for(int n = 0;n < tics_num1;n++){
    plt->tics_val1_x1[n] = tics_val1[n];
  }
  for(int n = 0;n < tics_num2;n++){
    plt->tics_val2_x1[n] = tics_val2[n];
  }
  plt->tics_num1_x1 = tics_num1;
  plt->tics_num2_x1 = tics_num2;
}

SVG__STYLE SVG__GET_LINESTYLE(const CHAR *stroke,
			      const CHAR *stroke_width,
			      const CHAR *stroke_dasharray,
			      const CHAR *opacity){
  SVG__STYLE style;

  strcpy(style,"fill:none;");

  if(stroke           != NULL){sprintf(style,"%s" "stroke"           ":%s;",style,stroke          );}
  if(stroke_width     != NULL){sprintf(style,"%s" "stroke-width"     ":%s;",style,stroke_width    );}
  if(stroke_dasharray != NULL){sprintf(style,"%s" "stroke-dasharray" ":%s;",style,stroke_dasharray);}
  if(opacity          != NULL){sprintf(style,"%s" "opacity"          ":%s;",style,opacity         );}

  return style;
}

void SVGPLOT__SET_XTICS_STYLE(SVGPLOT    *plt,
			      INT4        xb1_isactive,
			      const CHAR *xb1_stroke,
			      const CHAR *xb1_stroke_width,
			      const CHAR *xb1_stroke_dasharray,
			      const CHAR *xb1_opacity,
			      INT4        xb2_isactive,
			      const CHAR *xb2_stroke,
			      const CHAR *xb2_stroke_width,
			      const CHAR *xb2_stroke_dasharray,
			      const CHAR *xb2_opacity,
			      INT4        xt1_isactive,
			      const CHAR *xt1_stroke,
			      const CHAR *xt1_stroke_width,
			      const CHAR *xt1_stroke_dasharray,
			      const CHAR *xt1_opacity,
			      INT4        xt2_isactive,
			      const CHAR *xt2_stroke,
			      const CHAR *xt2_stroke_width,
			      const CHAR *xt2_stroke_dasharray,
			      const CHAR *xt2_opacity){
  plt->tics_xb1_isactive = xb1_isactive;
  plt->tics_xb1_style    = SVG__GET_LINESTYLE(xb1_stroke,xb1_stroke_width,xb1_stroke_dasharray,xb1_opacity);
  plt->tics_xb2_isactive = xb2_isactive;
  plt->tics_xb2_style    = SVG__GET_LINESTYLE(xb2_stroke,xb2_stroke_width,xb2_stroke_dasharray,xb2_opacity);
  plt->tics_xt1_isactive = xt1_isactive;
  plt->tics_xt1_style    = SVG__GET_LINESTYLE(xt1_stroke,xt1_stroke_width,xt1_stroke_dasharray,xt1_opacity);
  plt->tics_xt2_isactive = xt2_isactive;
  plt->tics_xt2_style    = SVG__GET_LINESTYLE(xt2_stroke,xt2_stroke_width,xt2_stroke_dasharray,xt2_opacity);  
}
			       

void SVGPLOT__SET_TICS_MODE_X2(SVGPLOT *plt,
			       INT4     tics_mode){//0: auto, 1: manual
  plt->tics_mode_x2 = tics_mode;
}

void SVGPLOT__SET_TICS_MODE_Y1(SVGPLOT *plt,
			       INT4     tics_mode){//0: auto, 1: manual
  plt->tics_mode_y1 = tics_mode;
}

void SVGPLOT__SET_TICS_MODE_Y2(SVGPLOT *plt,
			       INT4     tics_mode){//0: auto, 1: manual
  plt->tics_mode_y2 = tics_mode;
}
*/

// ============================================================================
// x軸の範囲を描画時に自動決定する
// ============================================================================
  void SVGPLOT__SET_RANGE_X_001(SVGPLOT    *plt);
// ============================================================================
// x軸の範囲を与えた配列の最小値・最大値とする
// ============================================================================
  void SVGPLOT__SET_RANGE_X_002(SVGPLOT    *plt,
				REAL8       x[],
				INT4        num);
// ============================================================================
// x軸の範囲を手動で与える
// ============================================================================
  void SVGPLOT__SET_RANGE_X_003(SVGPLOT    *plt,
				REAL8       xmin,
				REAL8       xmax);

// ============================================================================
// t軸の範囲を描画時に自動決定する
// ============================================================================
  void SVGPLOT__SET_RANGE_T_001(SVGPLOT    *plt);
// ============================================================================
// t軸の範囲を与えた配列の最小値・最大値とする
// ============================================================================
  void SVGPLOT__SET_RANGE_T_002(SVGPLOT    *plt,
				TIME_TT2000 t[],
				INT4        num);
// ============================================================================
// t軸の範囲を手動で与える
// ============================================================================
  void SVGPLOT__SET_RANGE_T_003(SVGPLOT    *plt,
				TIME_TT2000 tmin,
				TIME_TT2000 tmax);

// ============================================================================
// y軸の範囲を描画時に自動決定する
// ============================================================================
  void SVGPLOT__SET_RANGE_Y_001(SVGPLOT    *plt);
// ============================================================================
// y軸の範囲を与えた配列の最小値・最大値とする
// ============================================================================
  void SVGPLOT__SET_RANGE_Y_002(SVGPLOT    *plt,
				REAL8       y[],
				INT4        num);
// ============================================================================
// y軸の範囲を手動で与える
// ============================================================================
  void SVGPLOT__SET_RANGE_Y_003(SVGPLOT    *plt,
				REAL8       ymin,
				REAL8       ymax);

// ============================================================================
// z軸の範囲を描画時に自動決定する
// ============================================================================
  void SVGPLOT__SET_RANGE_Z_001(SVGPLOT    *plt);
// ============================================================================
// z軸の範囲を与えた配列の最小値・最大値とする
// ============================================================================
  void SVGPLOT__SET_RANGE_Z_002(SVGPLOT    *plt,
				REAL8       z[],
				INT4        num);
// ============================================================================
// z軸の範囲を手動で与える
// ============================================================================
  void SVGPLOT__SET_RANGE_Z_003(SVGPLOT    *plt,
				REAL8       zmin,
				REAL8       zmax);

// ============================================================================
// x軸をスケールタイプ(線形/対数)を設定
// ============================================================================
  void SVGPLOT__SET_SCALETYPE_X(SVGPLOT    *plt,
				INT4        xscaletype);//0: linear, 1: log
// ============================================================================
// y軸をスケールタイプ(線形/対数)を設定
// ============================================================================
  void SVGPLOT__SET_SCALETYPE_Y(SVGPLOT    *plt,
				INT4        yscaletype);//0: linear, 1: log
// ============================================================================
// z軸をスケールタイプ(線形/対数)を設定
// ============================================================================
  void SVGPLOT__SET_SCALETYPE_Z(SVGPLOT    *plt,
				INT4        zscaletype);//0: linear, 1: log

  // ============================================================================
  // XY補助情報を描画
  // ============================================================================
  void SVGPLOT__XY_AUX(SVGPLOT *plt,
		       INT4     xgrid1_on,
		       INT4     xgrid2_on,
		       INT4     ygrid1_on,
		       INT4     ygrid2_on,
		       INT4     xtics1_line_on,
		       INT4     xtics2_line_on,
		       INT4     ytics1_line_on,
		       INT4     ytics2_line_on,
		       INT4     xtics1_text_on,
		       INT4     xtics2_text_on,
		       INT4     ytics1_text_on,
		       INT4     ytics2_text_on,
		       INT4     border_on);
  
  // ============================================================================
  // TY補助情報を描画
  // ============================================================================
  void SVGPLOT__TY_AUX(SVGPLOT *plt,
		       INT4     tgrid1_on,
		       INT4     tgrid2_on,
		       INT4     ygrid1_on,
		       INT4     ygrid2_on,
		       INT4     ttics1_line_on,
		       INT4     ttics2_line_on,
		       INT4     ytics1_line_on,
		       INT4     ytics2_line_on,
		       INT4     ttics1_text_on,
		       INT4     ttics2_text_on,
		       INT4     ytics1_text_on,
		       INT4     ytics2_text_on,
		       INT4     border_on);

  // ============================================================================
  // z軸を表すカラーバーを描画
  // ============================================================================
  void SVGPLOT__COLORBAR(SVGPLOT *plt,
			 INT4     zgrid1_on,
			 INT4     zgrid2_on,
			 INT4     ztics1_line_on,
			 INT4     ztics2_line_on,
			 INT4     ztics1_text_on,
			 INT4     ztics2_text_on,
			 INT4     border_on);

  // ============================================================================
  // 関数群f1(x),f2(x),...の描画
  // ============================================================================
  void SVGPLOT__FUNCTION_2D(const CHAR *filename,
			    REAL8       xmin,
			    REAL8       xmax,
			    REAL8     (*f1)(REAL8 x),
			    ...);

  // ============================================================================
  // 関数f(x,y)の描画
  // ============================================================================
  void SVGPLOT__FUNCTION_3D(const CHAR *filename,
			    REAL8       xmin,
			    REAL8       xmax,
			    REAL8       ymin,
			    REAL8       ymax,
			    REAL8     (*f)(REAL8 x,REAL8 y),
			    INT4        zscaletype,
			    INT4        mode);

  // ============================================================================
  // CSVデータをプロット
  // ============================================================================
  void SVGPLOT__CSV_DATA(SVGPLOT    *plt,
			 FILE       *fp,
			 const CHAR *dep_entries,
			 const CHAR *var_entries,
			 const CHAR *legends,
			 INT4        mode);

  void SVGPLOT__CSV_FILE(SVGPLOT    *plt,
			 const CHAR *filename,
			 const CHAR *dep_entries,
			 const CHAR *var_entries,
			 const CHAR *legends,
			 INT4        mode);

  // ============================================================================
  // プロットデータの追加
  // ============================================================================
  void SVGPLOT__ADD_BY_DAT_XY (SVGPLOT    *plt,
			       REAL8       x[],
			       REAL8       y[],
			       INT4        num,
			       INT4        ptype,
			       const CHAR *legend);
  void SVGPLOT__ADD_BY_DAT_TY (SVGPLOT    *plt,
			       T2000       t[],
			       REAL8       y[],
			       INT4        num,
			       INT4        ptype,
			       const CHAR *legend);
  void SVGPLOT__ADD_BY_CSV_XY (SVGPLOT    *plt,
			       const CHAR *filename,
			       const CHAR *delimiters,
			       const CHAR *comment_chars,
			       INT4        x_idx,
			       INT4        y_idx,
			       INT4        ptype,
			       const CHAR *legend);
  void SVGPLOT__ADD_BY_CSV_TY (SVGPLOT    *plt,
			       const CHAR *filename,
			       const CHAR *delimiters,
			       const CHAR *comment_chars,
			       INT4        t_idx,
			       INT4        y_idx,
			       INT4        ptype,
			       const CHAR *legend);
  void SVGPLOT__PLOT          (SVGPLOT    *plt);
  void SVGPLOT__PLOT_TY       (SVGPLOT    *plt);
  
#ifdef __cplusplus
}
#endif

#endif
