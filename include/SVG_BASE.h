/***************************************************************** 
 *
 * SVG BASE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVG_BASE_H_INCLUDE_
#define _SVG_BASE_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include   <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include    <math.h>
#include   <float.h>
#include   <ctype.h>
#include"DATATYPE.h"
#include     "PNG.h"

typedef struct{
  REAL8  width;
  REAL8  height;
  FILE  *fp;
}SVG;

typedef CHAR SVG__STYLE[2048];
  typedef SVG__STYLE SVG_STYLE;

typedef enum{
  SVGPLOT__SCALETYPE_LINEAR = 0,
  SVGPLOT__SCALETYPE_LOG    = 1
} SVGPLOT__SCALETYPE;

// ========================================================================
// [SVG]描画スタイルの設定
// ========================================================================
  void SVG_STYLE__SET_001(SVG_STYLE   style,
			  const CHAR *opacity,          
			  const CHAR *stroke,           
			  const CHAR *stroke_width,			    
			  const CHAR *stroke_dasharray,
			  const CHAR *stroke_dashoffset,
			  const CHAR *stroke_linecap,   
			  const CHAR *stroke_linejoin,  
			  const CHAR *fill);

// ========================================================================
// SVGヘッダを出力
// ========================================================================
void SVG__HEADER (SVG        *svg);

// ========================================================================
// SVGフッタを出力
// ========================================================================
void SVG__FOOTER (SVG        *svg);

// ========================================================================
// [描画]始点(X1,Y1), 終点(X2,Y2)の直線
// ========================================================================
void SVG__LINE   (SVG        *svg,
		  REAL8       X1,
		  REAL8       Y1,
		  REAL8       X2,
		  REAL8       Y2,
		  SVG__STYLE  style);

// ========================================================================
// [描画]座標(X1,Y1), (X2,Y2)を頂点にもつ矩形
// ========================================================================
void SVG__RECT   (SVG        *svg,
		  REAL8       X1,
		  REAL8       Y1,
		  REAL8       X2,
		  REAL8       Y2,
		  SVG__STYLE  style);

// ========================================================================
// [描画]座標(X0,Y0)を中心とする横半径RX, 縦半径RYの楕円
// ========================================================================
void SVG__ELLIPSE(SVG        *svg,
		  REAL8       X0,
		  REAL8       Y0,
		  REAL8       RX,
		  REAL8       RY,
		  SVG__STYLE  style);

  void SVG__POINT  (SVG        *svg,
		    REAL8       X0,
		    REAL8       Y0,
		    REAL8       pointsize,
		    INT4        pointtype,
		    SVG__STYLE  style);

// ========================================================================
// [描画]座標(X0,Y0)を基準とするrot[deg]だけ回転した文字列
// ========================================================================
void SVG__TEXT   (SVG        *svg,
		  REAL8       X0,
		  REAL8       Y0,
		  REAL8       angle,
		  const CHAR *text,
		  INT4        texttype,
		  const CHAR *font_family,
		  REAL8       font_size,
		  SVG_STYLE   style,
		  INT4        halign,
		  INT4        valign);

// ========================================================================
// [描画]座標(X0,Y0)を基準とした横幅img_width, 縦幅img_heightの画像
// alignment [0: 左下基準, 1: 中央基準, 2: 右上基準]
// ========================================================================
void SVG__IMAGE1 (SVG        *svg,
		  IMAGE       img,
		  INT4        imgwidth,
		  INT4        imgheight,
		  REAL8       X0,
		  REAL8       Y0,
		  INT4        alignment);

// ========================================================================
// [描画]左下(X1,Y1), 右上(X2,Y2)の頂点をもつ矩形領域に投影された
//       横幅img_width, 縦幅img_heightの画像
// ========================================================================
void SVG__IMAGE2 (SVG        *svg,
		  IMAGE       img,
		  INT4        imgwidth,
		  INT4        imgheight,
		  REAL8       X1,
		  REAL8       Y1,
		  REAL8       X2,
		  REAL8       Y2);

#ifdef __cplusplus
}
#endif

#endif
