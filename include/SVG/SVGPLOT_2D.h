/***************************************************************** 
 *
 * SVGPLOT 2D
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_2D_H_INCLUDE_
#define _SVGPLOT_2D_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<cdf.h>
#include"SVG_BASE.h"
#include"SVGPLOT_BASE.h"
#include"SVGPLOT_CHECK.h"
#include"SVGPLOT_PALETTE.h"

// ========================================================================
// 折れ線グラフを描画する(横軸: REAL8, 縦軸: REAL8)
// ========================================================================
  void SVGPLOT_2D__XY_LINE   (SVG        *svg,              //SVGポインタ
			      REAL8       Xmin,             //描画範囲[(Xmin,Ymin),(Xmax,Ymax)]
			      REAL8       Xmax,             //
			      REAL8       Ymin,             //
			      REAL8       Ymax,             //
			      REAL8       xmin,             //xの最小値
			      REAL8       xmax,             //xの最大値
			      INT4        xscaletype,       //xのスケールタイプ(0: 線形, 1: 対数)
			      REAL8       ymin,             //yの最小値
			      REAL8       ymax,             //yの最大値
			      INT4        yscaletype,       //yのスケールタイプ(0: 線形, 1: 対数)
			      REAL8       x[],              //データ1
			      REAL8       y[],              //データ2
			      INT4        num,              //データ数
			      REAL8       xgap,             //横幅がxgapを超える線分を描画しない. xgap < 0のときは, この機能を無効にする.
			      REAL8       ygap,             //縦幅がygapを超える線分を描画しない. ygap < 0のときは, この機能を無効にする.
			      REAL8       lgap,             //長さがlgapを超える線分を描画しない. lgap < 0のときは, この機能を無効にする. 
			      INT4        mode,             //0: [ALL]線分の始点と終点が描画領域に含まれていない場合にも線分と描画領域が交わる場合には描画する. 
			                                    //1: [SUB]線分の始点と終点の少なくとも一方が描画領域に含まれる場合にのみ描画する. 
			      // ============================================
			      // CSSに基づく描画スタイルの指定
			      // ============================================
			      const CHAR *opacity,          //[NULL指定で規定値]線の不透明度
			      const CHAR *stroke,           //[NULL指定で規定値]線の色
			      const CHAR *stroke_width,     //[NULL指定で規定値]線の幅
			      const CHAR *stroke_dasharray, //[NULL指定で規定値]線の破線スタイル
			      const CHAR *stroke_dashoffset,//[NULL指定で規定値]線の破線オフセット
			      const CHAR *stroke_linecap,   //[NULL指定で規定値]線の始点・終点のスタイル
			      const CHAR *stroke_linejoin); //[NULL指定で規定値]線の角のスタイル

// ========================================================================
// 折れ線グラフを描画する(横軸: T2000, 縦軸: REAL8)
// ========================================================================
  void SVGPLOT_2D__TY_LINE   (SVG        *svg,              //SVGポインタ
			      REAL8       Xmin,             //描画範囲[(Xmin,Ymin),(Xmax,Ymax)]
			      REAL8       Xmax,             //
			      REAL8       Ymin,             //
			      REAL8       Ymax,             //
			      T2000       tmin,             //tの最小値
			      T2000       tmax,             //tの最大値
			      REAL8       ymin,             //yの最小値
			      REAL8       ymax,             //yの最大値
			      INT4        yscaletype,       //yのスケールタイプ(0: 線形, 1: 対数)
			      T2000       t[],              //データ1
			      REAL8       y[],              //データ2
			      INT4        num,              //データ数
			      T2000       tgap,             //横幅がtgapを超える線分を描画しない. tgap < 0のときは, この機能を無効にする.
			      REAL8       ygap,             //縦幅がygapを超える線分を描画しない. ygap < 0のときは, この機能を無効にする.
			      INT4        mode,             //0: [ALL]線分の始点と終点が描画領域に含まれていない場合にも線分と描画領域が交わる場合には描画する. 
			                                    //1: [SUB]線分の始点と終点の少なくとも一方が描画領域に含まれる場合にのみ描画する. 
			      // ============================================
			      // CSSに基づく線スタイルの指定
			      // ============================================
			      const CHAR *opacity,          //[NULL指定で規定値]線の不透明度
			      const CHAR *stroke,           //[NULL指定で規定値]線の色
			      const CHAR *stroke_width,     //[NULL指定で規定値]線の幅
			      const CHAR *stroke_dasharray, //[NULL指定で規定値]線の破線スタイル
			      const CHAR *stroke_dashoffset,//[NULL指定で規定値]線の破線オフセット
			      const CHAR *stroke_linecap,   //[NULL指定で規定値]線の始点・終点のスタイル
			      const CHAR *stroke_linejoin); //[NULL指定で規定値]線の角のスタイル

// ========================================================================
// インパルスグラフを描画する(横軸: REAL8, 縦軸: REAL8)
// ========================================================================
  void SVGPLOT_2D__XY_IMPULSE(SVG        *svg,              //SVGポインタ
			      REAL8       Xmin,             //描画範囲[(Xmin,Ymin),(Xmax,Ymax)]
			      REAL8       Xmax,             //
			      REAL8       Ymin,             //
			      REAL8       Ymax,             //
			      REAL8       xmin,             //xの最小値
			      REAL8       xmax,             //xの最大値
			      INT4        xscaletype,       //xのスケールタイプ(0: 線形, 1: 対数)
			      REAL8       ymin,             //yの最小値
			      REAL8       ymax,             //yの最大値
			      INT4        yscaletype,       //yのスケールタイプ(0: 線形, 1: 対数)
			      REAL8       x[],              //データ1
			      REAL8       y[],              //データ2
			      INT4        num,              //データ数
			      // ============================================
			      // CSSに基づく描画スタイルの指定
			      // ============================================
			      const CHAR *opacity,          //[NULL指定で規定値]線の不透明度
			      const CHAR *stroke,           //[NULL指定で規定値]線の色
			      const CHAR *stroke_width,     //[NULL指定で規定値]線の幅
			      const CHAR *stroke_dasharray, //[NULL指定で規定値]線の破線スタイル
			      const CHAR *stroke_dashoffset,//[NULL指定で規定値]線の破線オフセット
			      const CHAR *stroke_linecap,   //[NULL指定で規定値]線の始点・終点のスタイル
			      const CHAR *stroke_linejoin); //[NULL指定で規定値]線の角のスタイル

// ========================================================================
// インパルスグラフを描画する(横軸: T2000, 縦軸: REAL8)
// ========================================================================
  void SVGPLOT_2D__TY_IMPULSE(SVG        *svg,              //SVGポインタ
			      REAL8       Xmin,             //描画範囲[(Xmin,Ymin),(Xmax,Ymax)]
			      REAL8       Xmax,             //
			      REAL8       Ymin,             //
			      REAL8       Ymax,             //
			      T2000       tmin,             //tの最小値
			      T2000       tmax,             //tの最大値
			      REAL8       ymin,             //yの最小値
			      REAL8       ymax,             //yの最大値
			      INT4        yscaletype,       //yのスケールタイプ(0: 線形, 1: 対数)
			      T2000       t[],              //データ1
			      REAL8       y[],              //データ2
			      INT4        num,              //データ数
			      // ============================================
			      // CSSに基づく描画スタイルの指定
			      // ============================================
			      const CHAR *opacity,          //[NULL指定で規定値]線の不透明度
			      const CHAR *stroke,           //[NULL指定で規定値]線の色
			      const CHAR *stroke_width,     //[NULL指定で規定値]線の幅
			      const CHAR *stroke_dasharray, //[NULL指定で規定値]線の破線スタイル
			      const CHAR *stroke_dashoffset,//[NULL指定で規定値]線の破線オフセット
			      const CHAR *stroke_linecap,   //[NULL指定で規定値]線の始点・終点のスタイル
			      const CHAR *stroke_linejoin); //[NULL指定で規定値]線の角のスタイル

// ========================================================================
// 点グラフを描画する(横軸: REAL8, 縦軸: REAL8)
// ========================================================================
  void SVGPLOT_2D__XY_POINT  (SVG        *svg,              //SVGポインタ
			      REAL8       Xmin,             //描画範囲[(Xmin,Ymin),(Xmax,Ymax)]
			      REAL8       Xmax,             //
			      REAL8       Ymin,             //
			      REAL8       Ymax,             //
			      REAL8       xmin,             //xの最小値
			      REAL8       xmax,             //xの最大値
			      INT4        xscaletype,       //xのスケールタイプ(0: 線形, 1: 対数)
			      REAL8       ymin,             //yの最小値
			      REAL8       ymax,             //yの最大値
			      INT4        yscaletype,       //yのスケールタイプ(0: 線形, 1: 対数)
			      REAL8       x[],              //データ1
			      REAL8       y[],              //データ2
			      INT4        num,              //データ数
			      REAL8       pointsize,        //点の大きさ
			      INT4        pointtype,        //点の種類
			      // ============================================
			      // CSSに基づく描画スタイルの指定
			      // ============================================
			      const CHAR *opacity,          //[NULL指定で規定値]線の不透明度
			      const CHAR *stroke,           //[NULL指定で規定値]線の色
			      const CHAR *stroke_width,     //[NULL指定で規定値]線の幅
			      const CHAR *stroke_dasharray, //[NULL指定で規定値]線の破線スタイル
			      const CHAR *stroke_dashoffset,//[NULL指定で規定値]線の破線オフセット
			      const CHAR *stroke_linecap,   //[NULL指定で規定値]線の始点・終点のスタイル
			      const CHAR *stroke_linejoin,  //[NULL指定で規定値]線の角のスタイル
			      const CHAR *fill);            //[NULL指定で規定値]塗りつぶしの色

// ========================================================================
// 点グラフを描画する(横軸: T2000, 縦軸: REAL8)
// ========================================================================
  void SVGPLOT_2D__TY_POINT  (SVG        *svg,              //SVGポインタ
			      REAL8       Xmin,             //描画範囲[(Xmin,Ymin),(Xmax,Ymax)]
			      REAL8       Xmax,             //
			      REAL8       Ymin,             //
			      REAL8       Ymax,             //
			      T2000       tmin,             //tの最小値
			      T2000       tmax,             //tの最大値
			      REAL8       ymin,             //yの最小値
			      REAL8       ymax,             //yの最大値
			      INT4        yscaletype,       //yのスケールタイプ(0: 線形, 1: 対数)
			      T2000       t[],              //データ1
			      REAL8       y[],              //データ2
			      INT4        num,              //データ数
			      REAL8       pointsize,        //点の大きさ
			      INT4        pointtype,        //点の種類
			      // ============================================
			      // CSSに基づく描画スタイルの指定
			      // ============================================
			      const CHAR *opacity,          //[NULL指定で規定値]線の不透明度
			      const CHAR *stroke,           //[NULL指定で規定値]線の色
			      const CHAR *stroke_width,     //[NULL指定で規定値]線の幅
			      const CHAR *stroke_dasharray, //[NULL指定で規定値]線の破線スタイル
			      const CHAR *stroke_dashoffset,//[NULL指定で規定値]線の破線オフセット
			      const CHAR *stroke_linecap,   //[NULL指定で規定値]線の始点・終点のスタイル
			      const CHAR *stroke_linejoin,  //[NULL指定で規定値]線の角のスタイル
			      const CHAR *fill);            //[NULL指定で規定値]塗りつぶしの色

// ========================================================================
// コンターグラフを描画する(横軸: REAL8, 縦軸: REAL8, 濃淡: REAL8)
// ========================================================================
  void SVGPLOT_2D__XYZ_CONTOUR(SVG             *svg,
			       REAL8            Xmin,
			       REAL8            Xmax,
			       REAL8            Ymin,
			       REAL8            Ymax,
			       REAL8            xmin,
			       REAL8            xmax,
			       INT4             xscaletype,
			       REAL8            ymin,
			       REAL8            ymax,
			       INT4             yscaletype,
			       REAL8            zmin,
			       REAL8            zmax,
			       INT4             zscaletype,
			       REAL8            x[], //x[k]
			       INT4             xnum,
			       REAL8            y[], //y[l]
			       INT4             ynum,
			       REAL8            z[], //z[k * ynum + l]
			       REAL8            xgap,
			       REAL8            ygap,
			       INT4             mode,
			       SVGPLOT_PALETTE *pal);

// ========================================================================
// コンターグラフを描画する(横軸: T2000, 縦軸: REAL8, 濃淡: REAL8)
// ========================================================================
  void SVGPLOT_2D__TYZ_CONTOUR(SVG             *svg,
			       REAL8            Xmin,
			       REAL8            Xmax,
			       REAL8            Ymin,
			       REAL8            Ymax,
			       T2000            tmin,
			       T2000            tmax,
			       REAL8            ymin,
			       REAL8            ymax,
			       INT4             yscaletype,
			       REAL8            zmin,
			       REAL8            zmax,
			       INT4             zscaletype,
			       T2000            t[], //t[k]
			       INT4             tnum,
			       REAL8            y[], //y[l]
			       INT4             ynum,
			       REAL8            z[], //z[k * ynum + l]
			       T2000            tgap,
			       REAL8            ygap,
			       INT4             mode,
			       SVGPLOT_PALETTE *pal);


void SVGPLOT__CONTOUR_IMAGE(IMAGE              img,
			    INT4               imgwidth,
			    INT4               imgheight,
			    SVGPLOT_PALETTE   *pal,		      
			    REAL8              xmin,
			    REAL8              xmax,
			    REAL8              xgap,//[xgap < 0] => ギャップなし
			    REAL8              ymin,
			    REAL8              ymax,
			    REAL8              ygap,//[ygap < 0] => ギャップなし
			    REAL8              zmin,
			    REAL8              zmax,
			    REAL8              x[], //x[k]
			    INT4               xnum,
			    REAL8              y[], //y[l]
			    INT4               ynum,
			    REAL8              z[], //z[k * ynum + l]
			    SVGPLOT__SCALETYPE xscaletype,
			    SVGPLOT__SCALETYPE yscaletype,
			    SVGPLOT__SCALETYPE zscaletype);

void SVGPLOT__CONTOUR_IMAGE_TIME(IMAGE              img,
				 INT4               imgwidth,
				 INT4               imgheight,
				 SVGPLOT_PALETTE   *pal,		      
				 TIME_TT2000        xmin,
				 TIME_TT2000        xmax,
				 TIME_TT2000        xgap,//[xgap < 0] => ギャップなし
				 REAL8              ymin,
				 REAL8              ymax,
				 REAL8              ygap,//[ygap < 0] => ギャップなし
				 REAL8              zmin,
				 REAL8              zmax,
				 TIME_TT2000        x[], //x[k]
				 INT4               xnum,
				 REAL8              y[], //y[l]
				 INT4               ynum,
				 REAL8              z[], //z[k * ynum + l]
				 SVGPLOT__SCALETYPE yscaletype,
				 SVGPLOT__SCALETYPE zscaletype);


#ifdef __cplusplus
}
#endif

#endif
