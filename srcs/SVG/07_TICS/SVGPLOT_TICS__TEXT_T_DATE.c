/***************************************************************** 
 *
 * SVGPLOT TICS TEXT T DATE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__TEXT_T_DATE(SVG        *svg,
			       REAL8       Xmin,
			       REAL8       Xmax,
			       REAL8       Ymin,
			       REAL8       Ymax,
			       T2000       tmin,
			       T2000       tmax,
			       REAL8       offset0,
			       REAL8       offset1,
			       REAL8       offset2,
			       const CHAR *font_family,
			       REAL8       font_size,
			       SVG_STYLE   style,
			       INT4        dt){
  REAL8       year_min,month_min,day_min,hour_min,minute_min,second_min,msec_min,usec_min,nsec_min;
  REAL8       year_max,month_max,day_max,hour_max,minute_max,second_max,msec_max,usec_max,nsec_max;
  UINT1       flag;
  T2000       date,tics;
  INT4        count;
  REAL8       rX;
  REAL8       X0;
  CHAR        text[1024];
  const CHAR *textmonth[12] = {"Jan.","Feb.","Mar.","Arp.","May ","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec."};
  INT4        YYYY,MM,DD;

  CDF_TT2000_to_UTC_parts(tmin,&year_min,&month_min,&day_min,&hour_min,&minute_min,&second_min,&msec_min,&usec_min,&nsec_min);
  CDF_TT2000_to_UTC_parts(tmax,&year_max,&month_max,&day_max,&hour_max,&minute_max,&second_max,&msec_max,&usec_max,&nsec_max);

  flag = 0x06;
  
  for(YYYY = (INT4)year_min;YYYY <= (INT4)year_max;YYYY++){
    for(MM = 1;MM <= 12;MM++){
      for(DD = 1;DD <= 31;DD++){
	date = CDF_TT2000_from_UTC_parts((double)YYYY,(double)MM,(double)DD,0.0,0.0,0.0,0.0,0.0,0.0);
	if(date == ILLEGAL_TT2000_VALUE){
	  continue;
	}
	if((date < tmin) || (tmax < date)){
	  continue;
	}
	rX = (REAL8)(date - tmin) / (REAL8)(tmax - tmin);
	X0 = Xmin + (Xmax - Xmin) * rX;
	if((MM == 1) && (DD == 1)){
	  sprintf(text,"%04d %s",YYYY,textmonth[MM - 1]);
	  flag &= ~0x06;
	  SVG__TEXT(svg,
		    X0,Ymin - offset2,0.0,
		    text,1,font_family,font_size,style,1,2); 
	}else 
	if((MM != 1) && (DD == 1)){
	  sprintf(text,     "%s",     textmonth[MM - 1]);
	  flag &= ~0x02;
	  SVG__TEXT(svg,
		    X0,Ymin - offset2,0.0,
		    text,1,font_family,font_size,style,1,2); 
	}
      }
    }
  }
  if(flag == 0x06){
    sprintf(text,"%04d %s"     ,(int)year_min,textmonth[(int)month_min - 1]);      
  }
  if(flag == 0x04){
    sprintf(text,"%04d"        ,(int)year_min);      
  }
  if(flag != 0x00){
    SVG__TEXT(svg,
	      Xmin - offset0,Ymin - offset2,0.0,
	      text,1,font_family,font_size,style,1,2); 
  }

  count = 0;
  for(YYYY = (INT4)year_min;YYYY <= (INT4)year_max;YYYY++){
    for(MM = 1;MM <= 12;MM++){
      for(DD = 1;DD <= 31;DD++){
	tics = CDF_TT2000_from_UTC_parts((double)YYYY,(double)MM,(double)DD,0.0,0.0,0.0,0.0,0.0,0.0);
	if(tics == ILLEGAL_TT2000_VALUE){
	  continue;
	}
	if((tics < tmin) || (tmax < tics)){
	  continue;
	}
	if(count % dt == 0){
	  rX = (REAL8)(tics - tmin) / (REAL8)(tmax - tmin);
	  X0 = Xmin + (Xmax - Xmin) * rX;
	  sprintf(text,"%02d",DD);
	  SVG__TEXT(svg,
		    X0,Ymin - offset1,0.0,
		    text,1,font_family,font_size,style,1,2); 
	}
	count++;
      }
    }
  }
  SVG__TEXT(svg,
	    Xmin - offset0,Ymin - offset1,0.0,
	    "Date",1,font_family,font_size,style,1,2); 
}

