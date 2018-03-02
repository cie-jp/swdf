/***************************************************************** 
 *
 * SVGPLOT DATA
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_DATA_H_INCLUDE_
#define _SVGPLOT_DATA_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<cdf.h>
#include"TEXT_CSV.h"
#include"STATS.h"
#include"SVG_BASE.h"

#define SVGPLOT_DATA__LEGEND_BUFLEN (1024)

  typedef struct{
    REAL8    *x;
    T2000    *t;
    REAL8    *y;
    REAL8    *z;
    INT4      xnum;
    INT4      tnum;
    INT4      ynum;
    INT4      znum;
    INT4      dtype;//データタイプ (0: XY, 1: TY)
    INT4      ptype;//グラフの種類 (0: line, 1: point, 2: line + point, 3: impulse)
    CHAR      legend[SVGPLOT_DATA__LEGEND_BUFLEN];
  }SVGPLOT_DATA;

  void SVGPLOT_DATA__INITIALIZE_XY        (SVGPLOT_DATA *dat,
					   INT4          num,
					   INT4          ptype,
					   const CHAR   *legend);
  void SVGPLOT_DATA__INITIALIZE_TY        (SVGPLOT_DATA *dat,
					   INT4          num,
					   INT4          ptype,
					   const CHAR   *legend);
  void SVGPLOT_DATA__INITIALIZE_BY_DAT_XY (SVGPLOT_DATA *dat,
					   REAL8         x[],
					   REAL8         y[],
					   INT4          num,
					   INT4          ptype,
					   const CHAR   *legend);
  void SVGPLOT_DATA__INITIALIZE_BY_DAT_TY (SVGPLOT_DATA *dat,
					   T2000         t[],
					   REAL8         y[],
					   INT4          num,
					   INT4          ptype,
					   const CHAR   *legend);
  void SVGPLOT_DATA__INITIALIZE_BY_CSV_XY (SVGPLOT_DATA *dat,
					   const CHAR   *filename,
					   const CHAR   *delimiters,
					   const CHAR   *comment_chars,
					   INT4          x_idx,
					   INT4          y_idx,
					   INT4          ptype,
					   const CHAR   *legend);
  void SVGPLOT_DATA__INITIALIZE_BY_CSV_TY (SVGPLOT_DATA *dat,
					   const CHAR   *filename,
					   const CHAR   *delimiters,
					   const CHAR   *comment_chars,
					   INT4          t_idx,
					   INT4          y_idx,
					   INT4          ptype,
					   const CHAR   *legend);
  void SVGPLOT_DATA__FINALIZE             (SVGPLOT_DATA *dat);
  INT4 SVGPLOT_DATA__GET_DATATYPE         (SVGPLOT_DATA *dat);
  INT4 SVGPLOT_DATA__GET_PLOTTYPE         (SVGPLOT_DATA *dat);
  void SVGPLOT_DATA__GET_RANGE_XY         (SVGPLOT_DATA *dat,
					   REAL8        *xmin,
					   REAL8        *xmax,
					   REAL8        *ymin,
					   REAL8        *ymax);
  void SVGPLOT_DATA__GET_RANGE_TY         (SVGPLOT_DATA *dat,
					   T2000        *tmin,
					   T2000        *tmax,
					   REAL8        *ymin,
					   REAL8        *ymax);

#ifdef __cplusplus
}
#endif

#endif
