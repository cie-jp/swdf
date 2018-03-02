/***************************************************************** 
 *
 * SVGPLOT DATALIST
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_DATALIST_H_INCLUDE_
#define _SVGPLOT_DATALIST_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include<cdf.h>
#include"SVG_BASE.h"
#include"SVGPLOT_DATA.h"

#define SVGPLOT_DATALIST__MAXNUM (512)

  typedef struct{
    SVGPLOT_DATA dat[SVGPLOT_DATALIST__MAXNUM];
    INT4         num;
  }SVGPLOT_DATALIST;

  void SVGPLOT_DATALIST__INITIALIZE    (SVGPLOT_DATALIST *list);
  void SVGPLOT_DATALIST__FINALIZE      (SVGPLOT_DATALIST *list);
  void SVGPLOT_DATALIST__ADD_BY_DAT_XY (SVGPLOT_DATALIST *list,
					REAL8             x[],
					REAL8             y[],
					INT4              num,
					INT4              ptype,
					const CHAR       *legend);
  void SVGPLOT_DATALIST__ADD_BY_DAT_TY (SVGPLOT_DATALIST *list,
					T2000             t[],
					REAL8             y[],
					INT4              num,
					INT4              ptype,
					const CHAR       *legend);
  void SVGPLOT_DATALIST__ADD_BY_CSV_XY (SVGPLOT_DATALIST *list,
					const CHAR       *filename,
					const CHAR       *delimiters,
					const CHAR       *comment_chars,
					INT4              x_idx,
					INT4              y_idx,
					INT4              ptype,
					const CHAR       *legend);
  void SVGPLOT_DATALIST__ADD_BY_CSV_TY (SVGPLOT_DATALIST *list,
					const CHAR       *filename,
					const CHAR       *delimiters,
					const CHAR       *comment_chars,
					INT4              t_idx,
					INT4              y_idx,
					INT4              ptype,
					const CHAR       *legend);
  void SVGPLOT_DATALIST__FLUSH         (SVGPLOT_DATALIST *list);
  void SVGPLOT_DATALIST__GET_RANGE_XY  (SVGPLOT_DATALIST *list,
					REAL8            *xmin,
					REAL8            *xmax,
					REAL8            *ymin,
					REAL8            *ymax);
  void SVGPLOT_DATALIST__GET_RANGE_TY  (SVGPLOT_DATALIST *list,
					T2000            *tmin,
					T2000            *tmax,
					REAL8            *ymin,
					REAL8            *ymax);

#ifdef __cplusplus
}
#endif

#endif
