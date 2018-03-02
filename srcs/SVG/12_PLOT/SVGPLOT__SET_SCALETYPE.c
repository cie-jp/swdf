/***************************************************************** 
 *
 * SVGPLOT SET SCALETYPE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__SET_SCALETYPE_X(SVGPLOT    *plt,
			      INT4        xscaletype){
  plt->xscaletype = xscaletype;
}

void SVGPLOT__SET_SCALETYPE_Y(SVGPLOT    *plt,
			      INT4        yscaletype){
  plt->yscaletype = yscaletype;
}

void SVGPLOT__SET_SCALETYPE_Z(SVGPLOT    *plt,
			      INT4        zscaletype){
  plt->zscaletype = zscaletype;
}
