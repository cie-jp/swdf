/***************************************************************** 
 *
 * SVGPLOT PALETTE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _SVGPLOT_PALETTE_H_INCLUDE_
#define _SVGPLOT_PALETTE_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"SVG_BASE.h"

#define SVGPLOT__PALETTE_MAXNUM (1024)

typedef struct{
  RGBA  color_nan;
  RGBA  color_inf_m;
  RGBA  color_out_of_range_m;
  REAL8 value[SVGPLOT__PALETTE_MAXNUM];//value[0] = 0.0, value[num - 1] = 1.0
  RGBA  color[SVGPLOT__PALETTE_MAXNUM];
  INT4  num;
  RGBA  color_out_of_range_p;
  RGBA  color_inf_p;
  RGBA  color_gap;
}SVGPLOT_PALETTE;

void SVGPLOT_PALETTE__Create1(SVGPLOT_PALETTE *pal);//0.0 => 0x000000FF, 1.0 => 0xFFFFFFFF
void SVGPLOT_PALETTE__Create2(SVGPLOT_PALETTE *pal);//0.0 => 0xFFFFFFFF, 1.0 => 0x000000FF
void SVGPLOT_PALETTE__Create3(SVGPLOT_PALETTE *pal);
void SVGPLOT_PALETTE__Create4(SVGPLOT_PALETTE *pal);

void SVGPLOT_PALETTE__Create5(SVGPLOT_PALETTE *pal);
void SVGPLOT_PALETTE__Create6(SVGPLOT_PALETTE *pal);

RGBA SVGPLOT_PALETTE__Get_RGBA(SVGPLOT_PALETTE *pal,REAL8 zmin,REAL8 zmax,SVGPLOT__SCALETYPE zscaletype,REAL8 z);


  void SVGPLOT_PALETTE__Create10(SVGPLOT_PALETTE *pal);

#ifdef __cplusplus
}
#endif

#endif
