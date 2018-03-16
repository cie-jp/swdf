/***************************************************************** 
 *
 * SVGPLOT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_HIST_H_INCLUDE_
#define _SVGPLOT_HIST_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

  #include"SVGPLOT.h"
  
  void SVGPLOT__HISTOGRAM(double      x[],
                          int         num,
                          double      xmin,
                          double      xmax,
                          int         div,
                          const char *xlabel,
                          const char *ylabel,
                          const char *title,
                          const char *filename);

#ifdef __cplusplus
}
#endif

#endif
