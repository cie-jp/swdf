/***************************************************************** 
 *
 * SVGPLOT XY AUX
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__XY_AUX(SVGPLOT *plt,
		     INT4     xgrid1_on,
		     INT4     xgrid2_on,
		     INT4     ygrid1_on,
		     INT4     ygrid2_on,
		     INT4     xtics1_line_on,
		     INT4     xtics2_line_on,
		     INT4     ytics1_line_on,
		     INT4     ytics2_line_on,
		     INT4     xtics1_text_on,
		     INT4     xtics2_text_on,
		     INT4     ytics1_text_on,
		     INT4     ytics2_text_on,
		     INT4     border_on){
  REAL8 xtics1[SVGPLOT__TICS_MAXNUM];
  INT4  xtics1num;
  REAL8 xtics2[SVGPLOT__TICS_MAXNUM];
  INT4  xtics2num;

  REAL8 ytics1[SVGPLOT__TICS_MAXNUM];
  INT4  ytics1num;
  REAL8 ytics2[SVGPLOT__TICS_MAXNUM];
  INT4  ytics2num;
  
  if(xgrid1_on || xgrid2_on || xtics1_line_on || xtics2_line_on || xtics1_text_on || xtics2_text_on){
    SVGPLOT__AUTOTICS_REAL8(xtics1,&xtics1num,xtics2,&xtics2num,plt->xmin,plt->xmax,plt->xscaletype);
    if(xgrid1_on){
      SVGPLOT_GRID__X(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,xtics1,xtics1num,plt->xgrid1style);
    }
    if(xgrid2_on){
      SVGPLOT_GRID__X(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,xtics2,xtics2num,plt->xgrid2style);
    }
    if(xtics1_line_on){
      SVGPLOT_TICS__LINE_X(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,xtics1,xtics1num,plt->xtics1len,plt->xtics1linestyle,xtics1_line_on);
    }
    if(xtics2_line_on){
      SVGPLOT_TICS__LINE_X(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,xtics2,xtics2num,plt->xtics2len,plt->xtics2linestyle,xtics2_line_on);
    }
    if(xtics1_text_on){
      SVGPLOT_TICS__TEXT_X(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,xtics1,xtics1num,
			   plt->xtics1textoffset,plt->xtics1font_family,plt->xtics1font_size,plt->xtics1textstyle,xtics1_text_on);
    }
    if(xtics2_text_on){
      SVGPLOT_TICS__TEXT_X(&plt->svg,plt->Xmin,plt->Xmax,plt->Ymin,plt->Ymax,plt->xmin,plt->xmax,plt->xscaletype,xtics2,xtics2num,
			   plt->xtics2textoffset,plt->xtics2font_family,plt->xtics2font_size,plt->xtics2textstyle,xtics2_text_on);
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
