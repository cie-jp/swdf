/***************************************************************** 
 *
 * SVGPLOT TICS TEXT T HHMM
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

void SVGPLOT_TICS__TEXT_T_HHMM(SVG        *svg,
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
  REAL8       rX;
  REAL8       X0;
  CHAR        text[1024];
  const CHAR *textmonth[12] = {"Jan.","Feb.","Mar.","Arp.","May ","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec."};
  INT4        YYYY,MM,DD;
  INT4        mmmm;

  CDF_TT2000_to_UTC_parts(tmin,&year_min,&month_min,&day_min,&hour_min,&minute_min,&second_min,&msec_min,&usec_min,&nsec_min);
  CDF_TT2000_to_UTC_parts(tmax,&year_max,&month_max,&day_max,&hour_max,&minute_max,&second_max,&msec_max,&usec_max,&nsec_max);

  flag = 0x07;

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
	  sprintf(text,"%04d %s %02d",YYYY,textmonth[MM - 1],DD);
	  flag &= ~0x07;
	}else{
	  sprintf(text,     "%s %02d",     textmonth[MM - 1],DD);
	  flag &= ~0x03;
	}
	SVG__TEXT(svg,
		  X0,Ymin - offset2,0.0,
		  text,1,font_family,font_size,style,1,2);  
      }
    }
  }
  if(flag == 0x07){
    sprintf(text,"%04d %s %02d",(int)year_min,textmonth[(int)month_min - 1],(int)day_min);      
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
  
  for(YYYY = (INT4)year_min;YYYY <= (INT4)year_max;YYYY++){
    for(MM = 1;MM <= 12;MM++){
      for(DD = 1;DD <= 31;DD++){
	date = CDF_TT2000_from_UTC_parts((double)YYYY,(double)MM,(double)DD,0.0,0.0,0.0,0.0,0.0,0.0);
	if(date == ILLEGAL_TT2000_VALUE){
	  continue;
	}	
	if(tmin > (date + 86401000000000LL)){
	  continue;
	}
	if(tmax <  date){
	  break;
	}
	for(mmmm = 0;mmmm < 1440;mmmm += dt){
	  tics = date + mmmm * 60000000000LL;
	  if((tics < tmin) || (tmax < tics)){
	    continue;
	  }
	  rX = (REAL8)(tics - tmin) / (REAL8)(tmax - tmin);
	  X0 = Xmin + (Xmax - Xmin) * rX;
	  sprintf(text,"%02d:%02d",mmmm / 60,mmmm % 60);
	  SVG__TEXT(svg,
		    X0,Ymin - offset1,0.0,
		    text,1,font_family,font_size,style,1,2);  
	}    
	
      }
    }
  }
  SVG__TEXT(svg,
	    Xmin - offset0,Ymin - offset1,0.0,
	    "hh:mm",1,font_family,font_size,style,1,2); 
}
