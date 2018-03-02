/***************************************************************** 
 *
 * SVGPLOT AUTOTICS
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"cdf.h"
#include"SVGPLOT_AUTOTICS.h"

void SVGPLOT__AUTOTICS_REAL8           (REAL8              tics1[],
					INT4              *tics1num,
					REAL8              tics2[],
					INT4              *tics2num,
					REAL8              valmin,
					REAL8              valmax,
					SVGPLOT__SCALETYPE scaletype){
  REAL8 range;
  REAL8 unit;
  REAL8 dtic1,dtic2;
  REAL8 min_l,max_u;
  INT4  num;
  INT4  n,m;

  switch(scaletype){
  case SVGPLOT__SCALETYPE_LINEAR:
    // ====================================================
    // 線形スケール
    // ====================================================
    range =  valmax - valmin;
    if(range <= DBL_MIN){
      *tics1num = 0;
      *tics2num = 0;
      return;
    }
    unit  = 1.0;
    while(range >= 10.0){
      range /= 10.0;
      unit  *= 10.0;
    }
    while(range <=  1.0){
      range *= 10.0;
      unit  /= 10.0;
    }
    if(range > 8.0){
      dtic1 = 2.000 * unit;
      dtic2 = 0.500 * unit;
    }else 
    if(range > 4.0){
      dtic1 = 1.000 * unit;
      dtic2 = 0.250 * unit;
    }else 
    if(range > 2.0){
      dtic1 = 0.500 * unit;
      dtic2 = 0.100 * unit;
    }else{
      dtic1 = 0.250 * unit;
      dtic2 = 0.050 * unit;
    }

    min_l = floor(valmin / dtic1) * dtic1;
    max_u = ceil (valmax / dtic1) * dtic1;

    tics1[0] = min_l;
    for(num = 1;num < SVGPLOT__TICS_MAXNUM;num++){
      if((tics1[num] = min_l + dtic1 * num) > max_u){
	break;
      }
    }
    *tics1num = num;

    min_l = floor(valmin / dtic2) * dtic2;
    max_u = ceil (valmax / dtic2) * dtic2;

    tics2[0] = min_l;
    for(num = 1;num < SVGPLOT__TICS_MAXNUM;num++){
      if((tics2[num] = min_l + dtic2 * num) > max_u){
	break;
      }
    }
    *tics2num = num;
    break;
  case SVGPLOT__SCALETYPE_LOG:
    // ====================================================
    // 対数スケール
    // ====================================================
    if((valmin <= DBL_MIN) || (valmax <= DBL_MIN) || ((valmin + DBL_MIN) >= valmax)){
      *tics1num = 0;
      *tics2num = 0;
      return;
    }
    min_l = pow(10.0,floor(log10(valmin)));
    max_u = pow(10.0,ceil (log10(valmax)));

    range = log10(valmax / valmin);
    
    dtic1 = (range < 10.0) ? 10.0 : (range < 16.0) ? 100.0 : 1000.0;

    tics1[0] = min_l;
    for(num = 1;num < SVGPLOT__TICS_MAXNUM;num++){
      if((tics1[num] = min_l * pow(dtic1,(REAL8)num)) > max_u){
	break;
      }
    }
    *tics1num = num;

    if(dtic1 <= 10.0){
      num = 0;
      for(n = 0;;n++){
	for(m = 1;m <= 9;m++){
	  if((tics2[num] = min_l * m * pow(10.0,(REAL8)n)) > max_u){
	    goto EXIT;
	  }
	  num++;
	  if(num >= SVGPLOT__TICS_MAXNUM){
	    goto EXIT;
	  }
	}
      }
    }else{ 
      tics2[0] = min_l;
      for(num = 0;num < SVGPLOT__TICS_MAXNUM;num++){
	if((tics2[num] = min_l + pow(10.0,(REAL8)num)) > max_u){
	  break;	  
	}
      }      
    }
  EXIT:
    *tics2num = num;
    break;
  default:
    fprintf(stderr,"[WARNING : SVGPLOT__AUTOTICS] UNKNOWN SCALETYPE\n");
    exit(EXIT_FAILURE);
  }
}	

void SVGPLOT__AUTOTICS_TIME_TT2000     (TIME_TT2000        tics1[],
					INT4              *tics1num,
					TIME_TT2000        tics2[],
					INT4              *tics2num,
					TIME_TT2000        tmin,
					TIME_TT2000        tmax){
  TIME_TT2000 diff;
  INT4        dt1,dt2;
  TIME_TT2000 m  =    60000000000LL;
  TIME_TT2000 h  =  3600000000000LL;
  TIME_TT2000 d  = 86400000000000LL;
  
  diff = tmax - tmin;
  if(( 5 * m <= diff) && (diff < 10 * m)){// 5,10
    dt1 =  1;
    dt2 =  1;
  }else 
  if((10 * m <= diff) && (diff < 18 * m)){// 5, 9
    dt1 =  2;
    dt2 =  1;
  }else 
  if((18 * m <= diff) && (diff < 30 * m)){// 6,10
    dt1 =  3;
    dt2 =  1;
  }else 
  if((30 * m <= diff) && (diff <  1 * h)){// 6,12
    dt1 =  5;
    dt2 =  1;
  }else 
  if(( 1 * h <= diff) && (diff <  2 * h)){// 6,12
    dt1 = 10;
    dt2 =  2;
  }else 
  if(( 2 * h <= diff) && (diff <  3 * h)){// 6,12
    dt1 = 20;
    dt2 =  5;
  }else 
  if(( 3 * h <= diff) && (diff <  6 * h)){// 6,12
    dt1 = 30;
    dt2 = 10;
  }else 
  if(( 6 * h <= diff) && (diff < 12 * h)){// 6,12
    dt1 =  1 * 60;
    dt2 = 15;
  }else 
  if((12 * h <= diff) && (diff <  1 * d)){// 6,12
    dt1 =  2 * 60;
    dt2 = 30;
  }else 
  if(( 1 * d <= diff) && (diff <  2 * d)){// 6,12
    dt1 =  4 * 60;
    dt2 =      60;
  }else 
  if(( 2 * d <= diff) && (diff <  4 * d)){// 6,12
    dt1 =  8 * 60;
    dt2 =  2 * 60;
  }else 
  if(( 4 * d <= diff) && (diff <  6 * d)){// 8,12
    dt1 = 12 * 60;
    dt2 =  3 * 60;
  }else 
  if(( 6 * d <= diff) && (diff < 12 * d)){
    dt1 =  1;
    dt2 =  1;
  }else 
  if((12 * d <= diff) && (diff < 24 * d)){
    dt1 =  2;
    dt2 =  1;
  }else 
  if((24 * d <= diff) && (diff < 48 * d)){
    dt1 =  5;
    dt2 =  1;
  }else 
  if((48 * d <= diff) && (diff < 96 * d)){
    dt1 = 10;
    dt2 =  2;
  }else{
    dt1 = 20;
    dt2 =  2;
  }

  if(diff < 6 * d){
    SVGPLOT__AUTOTICS_TIME_TT2000_HHMM(tics1,tics1num,tics2,tics2num,tmin,tmax,dt1,dt2);
  }else{
    SVGPLOT__AUTOTICS_TIME_TT2000_DATE(tics1,tics1num,tics2,tics2num,tmin,tmax,dt1,dt2);
  }  
}

void SVGPLOT__AUTOTICS_TIME_TT2000_HHMM(TIME_TT2000        tics1[],
					INT4              *tics1num,
					TIME_TT2000        tics2[],
					INT4              *tics2num,
					TIME_TT2000        tmin,
					TIME_TT2000        tmax,
					INT4               dt1,
					INT4               dt2){//時間刻み[min]
  REAL8       year_min,month_min,day_min,hour_min,minute_min,second_min,msec_min,usec_min,nsec_min;
  REAL8       year_max,month_max,day_max,hour_max,minute_max,second_max,msec_max,usec_max,nsec_max;
  TIME_TT2000 date,tics;
  INT4        num;
  INT4        YYYY,MM,DD;
  INT4        mmmm;

  CDF_TT2000_to_UTC_parts(tmin,&year_min,&month_min,&day_min,&hour_min,&minute_min,&second_min,&msec_min,&usec_min,&nsec_min);
  CDF_TT2000_to_UTC_parts(tmax,&year_max,&month_max,&day_max,&hour_max,&minute_max,&second_max,&msec_max,&usec_max,&nsec_max);

  num = 0;
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
	  goto EXIT1;
	}
	for(mmmm = 0;mmmm < 1440;mmmm += dt1){
	  tics = date + mmmm * 60000000000LL;
	  if((tics < tmin) || (tmax < tics)){
	    continue;
	  }
	  tics1[num] = tics;
	  num++;
	  if(num >= SVGPLOT__TICS_MAXNUM){
	    goto EXIT1;
	  }
	}
      }
    }
  }
 EXIT1:
  *tics1num = num;

  num = 0;
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
	  goto EXIT2;
	}
	for(mmmm = 0;mmmm < 1440;mmmm += dt2){
	  tics = date + mmmm * 60000000000LL;
	  if((tics < tmin) || (tmax < tics)){
	    continue;
	  }
	  tics2[num] = tics;
	  num++;
	  if(num >= SVGPLOT__TICS_MAXNUM){
	    goto EXIT2;
	  }
	}
      }
    }
  }
 EXIT2:
  *tics2num = num;
}

void SVGPLOT__AUTOTICS_TIME_TT2000_DATE(TIME_TT2000        tics1[],
					INT4              *tics1num,
					TIME_TT2000        tics2[],
					INT4              *tics2num,
					TIME_TT2000        tmin,
					TIME_TT2000        tmax,
					INT4               dt1,
					INT4               dt2){//時間刻み[day]
  REAL8       year_min,month_min,day_min,hour_min,minute_min,second_min,msec_min,usec_min,nsec_min;
  REAL8       year_max,month_max,day_max,hour_max,minute_max,second_max,msec_max,usec_max,nsec_max;
  TIME_TT2000 tics;
  INT4        count;
  INT4        num;
  INT4        YYYY,MM,DD;

  CDF_TT2000_to_UTC_parts(tmin,&year_min,&month_min,&day_min,&hour_min,&minute_min,&second_min,&msec_min,&usec_min,&nsec_min);
  CDF_TT2000_to_UTC_parts(tmax,&year_max,&month_max,&day_max,&hour_max,&minute_max,&second_max,&msec_max,&usec_max,&nsec_max);

  count = 0;
  num   = 0;
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
	if(count % dt1 == 0){
	  tics1[num] = tics;
	  num++;
	  if(num >= SVGPLOT__TICS_MAXNUM){
	    goto EXIT1;
	  } 
	}
	count++;
      }
    }
  }
 EXIT1:
  *tics1num = num;

  count = 0;
  num   = 0;
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
	if(count % dt2 == 0){
	  tics2[num] = tics;
	  num++;
	  if(num >= SVGPLOT__TICS_MAXNUM){
	    goto EXIT2;
	  } 
	}
	count++;
      }
    }
  }
 EXIT2:
  *tics2num = num;
}

