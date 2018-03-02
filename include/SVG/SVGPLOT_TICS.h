/***************************************************************** 
 *
 * SVGPLOT TICS
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_TICS_H_INCLUDE_
#define _SVGPLOT_TICS_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<cdf.h>  
#include"SVG_BASE.h"
#include"SVGPLOT_BASE.h"
  
#define SVGPLOT__TICS_MAXNUM (512) //目盛の最大個数
  
  void SVGPLOT_TICS__LINE_X(SVG      *svg,
			    REAL8     Xmin,
			    REAL8     Xmax,
			    REAL8     Ymin,
			    REAL8     Ymax,
			    REAL8     xmin,
			    REAL8     xmax,
			    INT4      xscaletype,
			    REAL8     xtics[],
			    INT4      xticsnum,
			    REAL8     xticslen,
			    SVG_STYLE xticsstyle,
			    INT4      mode); //0: NONE  , 1: BOTTOM, 2: TOP   , 3: BOTTOM + TOP
  
  void SVGPLOT_TICS__LINE_T(SVG      *svg,
			    REAL8     Xmin,
			    REAL8     Xmax,
			    REAL8     Ymin,
			    REAL8     Ymax,
			    T2000     tmin,
			    T2000     tmax,
			    T2000     ttics[],
			    INT4      tticsnum,
			    REAL8     tticslen,
			    SVG_STYLE tticsstyle,
			    INT4      mode); //0: NONE  , 1: BOTTOM, 2: TOP   , 3: BOTTOM + TOP
  
  void SVGPLOT_TICS__LINE_Y(SVG      *svg,
			    REAL8     Xmin,
			    REAL8     Xmax,
			    REAL8     Ymin,
			    REAL8     Ymax,
			    REAL8     ymin,
			    REAL8     ymax,		
			    INT4      yscaletype,
			    REAL8     ytics[],
			    INT4      yticsnum,
			    REAL8     yticslen,
			    SVG_STYLE yticsstyle,
			    INT4      mode); //0: NONE  , 1: LEFT  , 2: RIGHT , 3: LEFT + RIGHT



  int COMPARE_REAL8(const void *a,const void *b);
  REAL8 GET_D(REAL8 val[],
	      INT4  num);
void SVGPLOT__GET_OPT_LINEAR_SCALE(INT4 *shift,
				   INT4 *exponent,
				   INT4 *digitnumu,
				   INT4 *digitnuml,
				   REAL8 val[],
				   INT4  num);

void SVGPLOT__SET_TEXT_FROM_REAL8_LINEAR(CHAR  text[2048],
					 REAL8 val,
					 INT4  shift,
					 INT4  exponent,
					 INT4  digitnumu,
					 INT4  digitnuml);

void SVGPLOT__SET_TEXT_FROM_REAL8_LOG   (CHAR  text[2048],
					 REAL8 val);


  
  void SVGPLOT_TICS__TEXT_X(SVG        *svg,
			    REAL8       Xmin,
			    REAL8       Xmax,
			    REAL8       Ymin,
			    REAL8       Ymax,
			    REAL8       xmin,
			    REAL8       xmax,
			    INT4        xscaletype,
			    REAL8       x[],
			    INT4        xnum,
			    REAL8       offset,
			    const CHAR *font_family,
			    REAL8       font_size,
			    SVG_STYLE   style,
			    INT4        mode);
  
  void SVGPLOT_TICS__TEXT_Y(SVG        *svg,
			    REAL8       Xmin,
			    REAL8       Xmax,
			    REAL8       Ymin,
			    REAL8       Ymax,
			    REAL8       ymin,
			    REAL8       ymax,
			    INT4        yscaletype,
			    REAL8       y[],
			    INT4        ynum,
			    REAL8       offset,
			    const CHAR *font_family,
			    REAL8       font_size,
			    SVG_STYLE   style,
			    INT4        mode);


  void SVGPLOT_TICS__TEXT_T(SVG        *svg,
			    REAL8       Xmin,
			    REAL8       Xmax,
			    REAL8       Ymin,
			    REAL8       Ymax,
			    T2000       tmin,
			    T2000       tmax,
			    REAL8       offset0,
			    REAL8       offset1,
			    REAL8       offset2,
			    const CHAR *font_family,
			    REAL8       font_size,
			    SVG__STYLE  style);

  void SVGPLOT_TICS__TEXT_T_HHMM(SVG        *svg,
				 REAL8       Xmin,
				 REAL8       Xmax,
				 REAL8       Ymin,
				 REAL8       Ymax,
				 T2000       tmin,
				 T2000       tmax,
				 REAL8       offset0,
				 REAL8       offset1,
				 REAL8       offset2,
				 const CHAR *font_family,
				 REAL8       font_size,
				 SVG_STYLE   style,
				 INT4        dt);

  void SVGPLOT_TICS__TEXT_T_DATE(SVG        *svg,
				 REAL8       Xmin,
				 REAL8       Xmax,
				 REAL8       Ymin,
				 REAL8       Ymax,
				 T2000       tmin,
				 T2000       tmax,
				 REAL8       offset0,
				 REAL8       offset1,
				 REAL8       offset2,
				 const CHAR *font_family,
				 REAL8       font_size,
				 SVG_STYLE   style,
				 INT4        dt);

#ifdef __cplusplus
}
#endif

#endif
