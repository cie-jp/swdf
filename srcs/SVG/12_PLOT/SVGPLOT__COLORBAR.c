/***************************************************************** 
 *
 * SVGPLOT COLORBAR
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__COLORBAR(SVGPLOT *plt,
		       INT4     zgrid1_on,
		       INT4     zgrid2_on,
		       INT4     ztics1_line_on,
		       INT4     ztics2_line_on,
		       INT4     ztics1_text_on,
		       INT4     ztics2_text_on,
		       INT4     border_on){
  REAL8 ztics1[SVGPLOT__TICS_MAXNUM];
  INT4  ztics1num;
  REAL8 ztics2[SVGPLOT__TICS_MAXNUM];
  INT4  ztics2num;

  REAL8  r, z;
  RGBA  cb[512];

  REAL8 Xmin;
  REAL8 Xmax;
  REAL8 Ymin;
  REAL8 Ymax;

  INT4  n;

  Xmin = plt->Xmax + plt->cboffset;
  Ymin = plt->Ymin;
  Xmax = plt->Xmax + plt->cboffset + plt->cbwidth;
  Ymax = plt->Ymax;

  for(n = 0;n < 512;n++){
    r = n / (REAL8)(512 - 1);
    switch(plt->zscaletype){
    case SVGPLOT__SCALETYPE_LINEAR:
      z = plt->zmin +    (plt->zmax - plt->zmin) * r ;
      break;
    case SVGPLOT__SCALETYPE_LOG: 
      z = plt->zmin * pow(plt->zmax / plt->zmin,   r);
      break;
    default:
      fprintf(stderr,"[WARNING] UNKNOWN SCALETYPE\n");
      exit(EXIT_FAILURE);
    }
    cb[512 - 1 - n] = SVGPLOT_PALETTE__Get_RGBA(&plt->pal,plt->zmin,plt->zmax,plt->zscaletype,z);
  }

  SVG__IMAGE2(&plt->svg,cb,1,512,Xmin,Ymin,Xmax,Ymax);

  if(zgrid1_on || zgrid2_on || ztics1_line_on || ztics2_line_on || ztics1_text_on || ztics2_text_on){

    SVGPLOT__AUTOTICS_REAL8(ztics1,&ztics1num,ztics2,&ztics2num,plt->zmin,plt->zmax,plt->zscaletype);

    if(zgrid1_on){
      SVGPLOT_GRID__Y(&plt->svg,Xmin,Xmax,Ymin,Ymax,plt->zmin,plt->zmax,plt->zscaletype,ztics1,ztics1num,plt->zgrid1style);
    }

    if(zgrid2_on){
      SVGPLOT_GRID__Y(&plt->svg,Xmin,Xmax,Ymin,Ymax,plt->zmin,plt->zmax,plt->zscaletype,ztics2,ztics2num,plt->zgrid2style);
    }

    if(ztics1_line_on){
      SVGPLOT_TICS__LINE_Y(&plt->svg,Xmin,Xmax,Ymin,Ymax,plt->zmin,plt->zmax,plt->zscaletype,ztics1,ztics1num,plt->ztics1len,plt->ztics1linestyle,ztics1_line_on);
    }
    if(ztics2_line_on){
      SVGPLOT_TICS__LINE_Y(&plt->svg,Xmin,Xmax,Ymin,Ymax,plt->zmin,plt->zmax,plt->zscaletype,ztics2,ztics2num,plt->ztics2len,plt->ztics2linestyle,ztics2_line_on);
    }    
    if(ztics1_text_on){
      SVGPLOT_TICS__TEXT_Y(&plt->svg,Xmin,Xmax,Ymin,Ymax,plt->zmin,plt->zmax,plt->zscaletype,ztics1,ztics1num,
			   plt->ztics1textoffset,plt->ztics1font_family,plt->ztics1font_size,plt->ztics1textstyle,ztics1_text_on);
    }
    if(ztics2_text_on){
      SVGPLOT_TICS__TEXT_Y(&plt->svg,Xmin,Xmax,Ymin,Ymax,plt->zmin,plt->zmax,plt->zscaletype,ztics2,ztics2num,
			   plt->ztics2textoffset,plt->ztics2font_family,plt->ztics2font_size,plt->ztics2textstyle,ztics2_text_on); 
    }
  }

  if(border_on){
    SVG__RECT(&plt->svg,Xmin,Ymin,Xmax,Ymax,plt->cbborderstyle);
  }

}
