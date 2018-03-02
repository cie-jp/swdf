/***************************************************************** 
 *
 * SVGPLOT PALETTE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_PALETTE.h"

RGBA RGBA__Set(UINT4 rgba){
  RGBA c;

  c.R = (rgba >> 24) & 0xFF;
  c.G = (rgba >> 16) & 0xFF;
  c.B = (rgba >>  8) & 0xFF;
  c.A =  rgba        & 0xFF;

  return c;
}

void SVGPLOT_PALETTE__Create1 (SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0x000000FF);
  pal->color_inf_m          = RGBA__Set(0x000000FF);
  pal->color_out_of_range_m = RGBA__Set(0x000000FF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0x000000FF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0xFFFFFFFF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0xFFFFFFFF);
  pal->color_inf_p          = RGBA__Set(0xFFFFFFFF);
  pal->color_gap            = RGBA__Set(0xFFFFFFFF);
}

void SVGPLOT_PALETTE__Create2 (SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0xFFFFFFFF);
  pal->color_inf_m          = RGBA__Set(0xFFFFFFFF);
  pal->color_out_of_range_m = RGBA__Set(0xFFFFFFFF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0xFFFFFFFF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0x000000FF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0x000000FF);
  pal->color_inf_p          = RGBA__Set(0x000000FF);
  pal->color_gap            = RGBA__Set(0xFFFFFFFF);
}

void SVGPLOT_PALETTE__Create3 (SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0x000000FF);
  pal->color_inf_m          = RGBA__Set(0x000000FF);
  pal->color_out_of_range_m = RGBA__Set(0x000000FF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0x000000FF);pal->num++;
  pal->value[pal->num] = 0.05;pal->color[pal->num] = RGBA__Set(0x1C001AFF);pal->num++;
  pal->value[pal->num] = 0.10;pal->color[pal->num] = RGBA__Set(0x3F005DFF);pal->num++;
  pal->value[pal->num] = 0.15;pal->color[pal->num] = RGBA__Set(0x3300B3FF);pal->num++;
  pal->value[pal->num] = 0.20;pal->color[pal->num] = RGBA__Set(0x1300EFFF);pal->num++;
  pal->value[pal->num] = 0.25;pal->color[pal->num] = RGBA__Set(0x0D00FFFF);pal->num++;
  pal->value[pal->num] = 0.30;pal->color[pal->num] = RGBA__Set(0x0B60FEFF);pal->num++;
  pal->value[pal->num] = 0.35;pal->color[pal->num] = RGBA__Set(0x19C6FFFF);pal->num++;
  pal->value[pal->num] = 0.40;pal->color[pal->num] = RGBA__Set(0x21FFE9FF);pal->num++;
  pal->value[pal->num] = 0.45;pal->color[pal->num] = RGBA__Set(0x23FF80FF);pal->num++;
  pal->value[pal->num] = 0.50;pal->color[pal->num] = RGBA__Set(0x23FF30FF);pal->num++;
  pal->value[pal->num] = 0.55;pal->color[pal->num] = RGBA__Set(0x49FF06FF);pal->num++;
  pal->value[pal->num] = 0.60;pal->color[pal->num] = RGBA__Set(0xA9FF0AFF);pal->num++;
  pal->value[pal->num] = 0.65;pal->color[pal->num] = RGBA__Set(0xEFFF09FF);pal->num++;
  pal->value[pal->num] = 0.70;pal->color[pal->num] = RGBA__Set(0xFFEC0BFF);pal->num++;
  pal->value[pal->num] = 0.75;pal->color[pal->num] = RGBA__Set(0xFEA609FF);pal->num++;
  pal->value[pal->num] = 0.80;pal->color[pal->num] = RGBA__Set(0xFC5909FF);pal->num++;
  pal->value[pal->num] = 0.85;pal->color[pal->num] = RGBA__Set(0xFB2507FF);pal->num++;
  pal->value[pal->num] = 0.90;pal->color[pal->num] = RGBA__Set(0xFC0007FF);pal->num++;
  pal->value[pal->num] = 0.95;pal->color[pal->num] = RGBA__Set(0xCE0005FF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0x970003FF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0x970003FF);
  pal->color_inf_p          = RGBA__Set(0x970003FF);
  pal->color_gap            = RGBA__Set(0xFFFFFFFF);
}

void SVGPLOT_PALETTE__Create4 (SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0xFFFFFFFF);
  pal->color_inf_m          = RGBA__Set(0xFFFFFFFF);
  pal->color_out_of_range_m = RGBA__Set(0xFFFFFFFF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0xFFFFFFFF);pal->num++;
  pal->value[pal->num] = 0.10;pal->color[pal->num] = RGBA__Set(0xFFFFFFFF);pal->num++;
  pal->value[pal->num] = 0.10;pal->color[pal->num] = RGBA__Set(0xE5E5E5FF);pal->num++;
  pal->value[pal->num] = 0.20;pal->color[pal->num] = RGBA__Set(0xE5E5E5FF);pal->num++;
  pal->value[pal->num] = 0.20;pal->color[pal->num] = RGBA__Set(0xCCCCCCFF);pal->num++;
  pal->value[pal->num] = 0.30;pal->color[pal->num] = RGBA__Set(0xCCCCCCFF);pal->num++;
  pal->value[pal->num] = 0.30;pal->color[pal->num] = RGBA__Set(0xB2B2B2FF);pal->num++;
  pal->value[pal->num] = 0.40;pal->color[pal->num] = RGBA__Set(0xB2B2B2FF);pal->num++;
  pal->value[pal->num] = 0.40;pal->color[pal->num] = RGBA__Set(0x999999FF);pal->num++;
  pal->value[pal->num] = 0.50;pal->color[pal->num] = RGBA__Set(0x999999FF);pal->num++;
  pal->value[pal->num] = 0.50;pal->color[pal->num] = RGBA__Set(0x7F7F7FFF);pal->num++;
  pal->value[pal->num] = 0.60;pal->color[pal->num] = RGBA__Set(0x7F7F7FFF);pal->num++;
  pal->value[pal->num] = 0.60;pal->color[pal->num] = RGBA__Set(0x666666FF);pal->num++;
  pal->value[pal->num] = 0.70;pal->color[pal->num] = RGBA__Set(0x666666FF);pal->num++;
  pal->value[pal->num] = 0.70;pal->color[pal->num] = RGBA__Set(0x4C4C4CFF);pal->num++;
  pal->value[pal->num] = 0.80;pal->color[pal->num] = RGBA__Set(0x4C4C4CFF);pal->num++;
  pal->value[pal->num] = 0.80;pal->color[pal->num] = RGBA__Set(0x333333FF);pal->num++;
  pal->value[pal->num] = 0.90;pal->color[pal->num] = RGBA__Set(0x333333FF);pal->num++;
  pal->value[pal->num] = 0.90;pal->color[pal->num] = RGBA__Set(0x191919FF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0x191919FF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0x191919FF);
  pal->color_inf_p          = RGBA__Set(0x191919FF);
  pal->color_gap            = RGBA__Set(0xFFFFFFFF);
}

void SVGPLOT_PALETTE__Create5 (SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0xFFFFFFFF);
  pal->color_inf_m          = RGBA__Set(0xFFFFFFFF);
  pal->color_out_of_range_m = RGBA__Set(0xFFFFFFFF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0xFFFFFFFF);pal->num++;
  pal->value[pal->num] = 0.10;pal->color[pal->num] = RGBA__Set(0x9DD7FFFF);pal->num++;
  pal->value[pal->num] = 0.20;pal->color[pal->num] = RGBA__Set(0x33ADFFFF);pal->num++;
  pal->value[pal->num] = 0.30;pal->color[pal->num] = RGBA__Set(0x0085F9FF);pal->num++;
  pal->value[pal->num] = 0.40;pal->color[pal->num] = RGBA__Set(0x005BD7FF);pal->num++;
  pal->value[pal->num] = 0.50;pal->color[pal->num] = RGBA__Set(0x072DB4FF);pal->num++;
  pal->value[pal->num] = 0.60;pal->color[pal->num] = RGBA__Set(0x080092FF);pal->num++;
  pal->value[pal->num] = 0.70;pal->color[pal->num] = RGBA__Set(0x05006FFF);pal->num++;
  pal->value[pal->num] = 0.80;pal->color[pal->num] = RGBA__Set(0x02004DFF);pal->num++;
  pal->value[pal->num] = 0.90;pal->color[pal->num] = RGBA__Set(0x010027FF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0x000004FF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0x000004FF);
  pal->color_inf_p          = RGBA__Set(0x000004FF);
  pal->color_gap            = RGBA__Set(0xF0F0F0FF);
}

void SVGPLOT_PALETTE__Create6 (SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0xFFFFFFFF);
  pal->color_inf_m          = RGBA__Set(0x1800FFFF);
  pal->color_out_of_range_m = RGBA__Set(0x1800FFFF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0x1800FFFF);pal->num++;
  pal->value[pal->num] = 0.10;pal->color[pal->num] = RGBA__Set(0x3910FFFF);pal->num++;
  pal->value[pal->num] = 0.20;pal->color[pal->num] = RGBA__Set(0x695DFFFF);pal->num++;
  pal->value[pal->num] = 0.30;pal->color[pal->num] = RGBA__Set(0x9792FFFF);pal->num++;
  pal->value[pal->num] = 0.40;pal->color[pal->num] = RGBA__Set(0xCCC9FFFF);pal->num++;
  pal->value[pal->num] = 0.50;pal->color[pal->num] = RGBA__Set(0xFBFBFFFF);pal->num++;
  pal->value[pal->num] = 0.60;pal->color[pal->num] = RGBA__Set(0xFFCDCCFF);pal->num++;
  pal->value[pal->num] = 0.70;pal->color[pal->num] = RGBA__Set(0xFF9B9AFF);pal->num++;
  pal->value[pal->num] = 0.80;pal->color[pal->num] = RGBA__Set(0xFF6A69FF);pal->num++;
  pal->value[pal->num] = 0.90;pal->color[pal->num] = RGBA__Set(0xFF312EFF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0xFF0000FF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0xFF0000FF);
  pal->color_inf_p          = RGBA__Set(0xFF0000FF);
  pal->color_gap            = RGBA__Set(0xF0F0F0FF);
}

RGBA SVGPLOT_PALETTE__Get_RGBA(SVGPLOT_PALETTE *pal,REAL8 zmin,REAL8 zmax,SVGPLOT__SCALETYPE zscaletype,REAL8 z){
  REAL8 val,r;
  RGBA  c;
  INT4  n;

  switch(zscaletype){
  case SVGPLOT__SCALETYPE_LINEAR:
    val =    (z - zmin) /    (zmax - zmin);
    break;
  case SVGPLOT__SCALETYPE_LOG:
    val = log(z / zmin) / log(zmax / zmin);
    break;
  default:
    fprintf(stderr,"[WARNING : SVGPLOT_PALETTE__Get_RGBA] UNKNOWN SCALETYPE\n");
    exit(EXIT_FAILURE);
  }
  if(isnan(val)){
    return pal->color_nan;
  }
  if(isinf(val) && (val < 0.0)){
    return pal->color_inf_m;
  }
  if(isinf(val) && (val > 0.0)){
    return pal->color_inf_p;
  }
  if(val <   0.0){
    return pal->color_out_of_range_m;
  }
  if(val >  +1.0){
    return pal->color_out_of_range_p;
  }
  if(val ==  0.0){
    return pal->color[0];
  }
  for(n = 1;n < pal->num;n++){
    if((pal->value[n - 1] < val) && (val <= pal->value[n])){
      r   = (val - pal->value[n - 1]) / (pal->value[n] - pal->value[n - 1]);
      c.R = (UINT1)((1.0 - r) * pal->color[n - 1].R + r * pal->color[n].R); 
      c.G = (UINT1)((1.0 - r) * pal->color[n - 1].G + r * pal->color[n].G); 
      c.B = (UINT1)((1.0 - r) * pal->color[n - 1].B + r * pal->color[n].B); 
      c.A = (UINT1)((1.0 - r) * pal->color[n - 1].A + r * pal->color[n].A); 
      return c;
    }
  }
  return pal->color_nan;
}




void SVGPLOT_PALETTE__Create10(SVGPLOT_PALETTE *pal){
  pal->color_nan            = RGBA__Set(0x00000000);
  pal->color_inf_m          = RGBA__Set(0x00000000);
  pal->color_out_of_range_m = RGBA__Set(0x000000FF);
  pal->num = 0;
  pal->value[pal->num] = 0.00;pal->color[pal->num] = RGBA__Set(0x000000FF);pal->num++;
  pal->value[pal->num] = 0.05;pal->color[pal->num] = RGBA__Set(0x1C001AFF);pal->num++;
  pal->value[pal->num] = 0.10;pal->color[pal->num] = RGBA__Set(0x3F005DFF);pal->num++;
  pal->value[pal->num] = 0.15;pal->color[pal->num] = RGBA__Set(0x3300B3FF);pal->num++;
  pal->value[pal->num] = 0.20;pal->color[pal->num] = RGBA__Set(0x1300EFFF);pal->num++;
  pal->value[pal->num] = 0.25;pal->color[pal->num] = RGBA__Set(0x0D00FFFF);pal->num++;
  pal->value[pal->num] = 0.30;pal->color[pal->num] = RGBA__Set(0x0B60FEFF);pal->num++;
  pal->value[pal->num] = 0.35;pal->color[pal->num] = RGBA__Set(0x19C6FFFF);pal->num++;
  pal->value[pal->num] = 0.40;pal->color[pal->num] = RGBA__Set(0x21FFE9FF);pal->num++;
  pal->value[pal->num] = 0.45;pal->color[pal->num] = RGBA__Set(0x23FF80FF);pal->num++;
  pal->value[pal->num] = 0.50;pal->color[pal->num] = RGBA__Set(0x23FF30FF);pal->num++;
  pal->value[pal->num] = 0.55;pal->color[pal->num] = RGBA__Set(0x49FF06FF);pal->num++;
  pal->value[pal->num] = 0.60;pal->color[pal->num] = RGBA__Set(0xA9FF0AFF);pal->num++;
  pal->value[pal->num] = 0.65;pal->color[pal->num] = RGBA__Set(0xEFFF09FF);pal->num++;
  pal->value[pal->num] = 0.70;pal->color[pal->num] = RGBA__Set(0xFFEC0BFF);pal->num++;
  pal->value[pal->num] = 0.75;pal->color[pal->num] = RGBA__Set(0xFEA609FF);pal->num++;
  pal->value[pal->num] = 0.80;pal->color[pal->num] = RGBA__Set(0xFC5909FF);pal->num++;
  pal->value[pal->num] = 0.85;pal->color[pal->num] = RGBA__Set(0xFB2507FF);pal->num++;
  pal->value[pal->num] = 0.90;pal->color[pal->num] = RGBA__Set(0xFC0007FF);pal->num++;
  pal->value[pal->num] = 0.95;pal->color[pal->num] = RGBA__Set(0xCE0005FF);pal->num++;
  pal->value[pal->num] = 1.00;pal->color[pal->num] = RGBA__Set(0x970003FF);pal->num++;
  pal->color_out_of_range_p = RGBA__Set(0x970003FF);
  pal->color_inf_p          = RGBA__Set(0x00000000);
  pal->color_gap            = RGBA__Set(0x00000000);
}
