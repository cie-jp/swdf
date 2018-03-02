/***************************************************************** 
 *
 * SVGPLOT FINALIZE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__FINALIZE      (SVGPLOT    *plt){
  SVG__FOOTER(&plt->svg);
  if(strlen(plt->filename) != 0){
     fclose(plt->svg.fp);
  }
  SVGPLOT_DATALIST__FINALIZE(&plt->list);
}
