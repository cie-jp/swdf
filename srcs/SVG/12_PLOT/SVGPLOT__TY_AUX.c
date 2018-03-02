/***************************************************************** 
 *
 * SVGPLOT TY AUX
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__TY_AUX(SVGPLOT *plt,
		     INT4     tgrid1_on,
		     INT4     tgrid2_on,
		     INT4     ygrid1_on,
		     INT4     ygrid2_on,
		     INT4     ttics1_line_on,
		     INT4     ttics2_line_on,
		     INT4     ytics1_line_on,
		     INT4     ytics2_line_on,
		     INT4     ttics1_text_on,
		     INT4     ttics2_text_on,
		     INT4     ytics1_text_on,
		     INT4     ytics2_text_on,
		     INT4     border_on){
  T2000 ttics1[SVGPLOT__TICS_MAXNUM];
  INT4  ttics1num;
  T2000 ttics2[SVGPLOT__TICS_MAXNUM];
  INT4  ttics2num;

  REAL8 ytics1[SVGPLOT__TICS_MAXNUM];
  INT4  ytics1num;
  REAL8 ytics2[SVGPLOT__TICS_MAXNUM];
  INT4  ytics2num;

  if(tgrid1_on || ygrid2_on || ttics1_line_on || ttics2_line_on || ttics1_text_on || ttics2_text_on){
    SVGPLOT__AUTOTICS_TIME_TT2000(ttics1,&ttics1num,ttics2,&ttics2num,plt->tmin,plt->tmax);
    if(tgrid1_on){
      SVGPLOT_GRID__T(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,ttics1,ttics1num,plt->tgrid1style);
    }
    if(tgrid2_on){
      SVGPLOT_GRID__T(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,ttics2,ttics2num,plt->tgrid2style);
    }
    if(ttics1_line_on){
      SVGPLOT_TICS__LINE_T(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,ttics1,ttics1num,plt->ttics1len,plt->ttics1linestyle,ttics1_line_on);
    }
    if(ttics2_line_on){
      SVGPLOT_TICS__LINE_T(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->tmin,plt->tmax,ttics2,ttics2num,plt->ttics2len,plt->ttics2linestyle,ttics2_line_on);
    }
    if(ttics1_text_on || ttics2_text_on){
      SVGPLOT_TICS__TEXT_T(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,
			   plt->tmin,plt->tmax,plt->tticstextoffset1,plt->tticstextoffset2,plt->tticstextoffset3,
			   plt->ttics1font_family,plt->ttics1font_size,plt->ttics1textstyle);
    }
  }

  if(ygrid1_on || ygrid2_on || ytics1_line_on || ytics2_line_on || ytics1_text_on || ytics2_text_on){
    SVGPLOT__AUTOTICS_REAL8(ytics1,&ytics1num,ytics2,&ytics2num,plt->ymin,plt->ymax,plt->yscaletype);
    if(ygrid1_on){
      SVGPLOT_GRID__Y(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->ymin,plt->ymax,plt->yscaletype,ytics1,ytics1num,plt->ygrid1style);
    }
    if(ygrid2_on){
      SVGPLOT_GRID__Y(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->ymin,plt->ymax,plt->yscaletype,ytics2,ytics2num,plt->ygrid2style);
    }
    if(ytics1_line_on){
      SVGPLOT_TICS__LINE_Y(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->ymin,plt->ymax,plt->yscaletype,ytics1,ytics1num,plt->ytics1len,plt->ytics1linestyle,ytics1_line_on);
    }
    if(ytics2_line_on){
      SVGPLOT_TICS__LINE_Y(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->ymin,plt->ymax,plt->yscaletype,ytics2,ytics2num,plt->ytics2len,plt->ytics2linestyle,ytics2_line_on);
    }
    if(ytics1_text_on){
      SVGPLOT_TICS__TEXT_Y(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->ymin,plt->ymax,plt->yscaletype,ytics1,ytics1num,
			   plt->ytics2textoffset,plt->ytics1font_family,plt->ytics1font_size,plt->ytics1textstyle,ytics1_text_on);
    }
    if(ytics2_text_on){
      SVGPLOT_TICS__TEXT_Y(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->ymin,plt->ymax,plt->yscaletype,ytics2,ytics2num,
			   plt->ytics2textoffset,plt->ytics2font_family,plt->ytics2font_size,plt->ytics2textstyle,ytics2_text_on); 
    }
  }
  
  if(border_on){
    SVG__RECT(&plt->svg,plt->Xmin,plt->Ymin,plt->Xmax,plt->Ymax,plt->borderstyle);
  }
}
