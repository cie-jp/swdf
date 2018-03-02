/***************************************************************** 
 *
 * SVGPLOT AUTORANGE
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"cdf.h"
#include"SVGPLOT_AUTORANGE.h"

void SVGPLOT__AUTORANGE_REAL8      (REAL8             *valmin,
				    REAL8             *valmax,
				    REAL8              val[],
				    INT4               num,
				    SVGPLOT__SCALETYPE scaletype){
  INT4  isinit;
  REAL8 min = 0.0;
  REAL8 max = 0.0;
  INT4  n;

  switch(scaletype){
  case SVGPLOT__SCALETYPE_LINEAR:
    // ====================================================
    // 線形スケール
    // ====================================================
    isinit = 0;
    for(n = 0;n < num;n++){
      if(isnan(val[n]) || isinf(val[n])){
	continue;
      }
      if(!isinit){
	isinit = 1;
	min = val[n];
	max = val[n];
      }else{
	if(min > val[n]){
	  min = val[n];
	}
	if(max < val[n]){
	  max = val[n];
	}    
      }
    }
    if(isinit){
      if(min != max){
	*valmin = min;
	*valmax = max;
      }else{
	*valmin = min - 1.0;
	*valmax = max + 1.0;
      }
    }else{
      *valmin = -1.0;
      *valmax = +1.0;
    }    
    break;
  case SVGPLOT__SCALETYPE_LOG: 
    // ====================================================
    // 対数スケール
    // ====================================================
    isinit = 0;
    for(n = 0;n < num;n++){
      if(isnan(val[n]) || isinf(val[n])){
	continue;
      }
      if(val[n] <= DBL_MIN){
	continue;
      }
      if(!isinit){
	isinit = 1;
	min = val[n];
	max = val[n];
      }else{
	if(min > val[n]){
	  min = val[n];
	}
	if(max < val[n]){
	  max = val[n];
	}    
      }
    }
    if(isinit){
      if(min != max){
	*valmin = min;
	*valmax = max;
      }else{
	*valmin = min *  0.1;
	*valmax = max * 10.0;
      }
    }else{
      *valmin =  0.1;
      *valmax = 10.0;
    }    
    break;
  default:
    fprintf(stderr,"[WARNING : SVGPLOT__AUTORANGE] UNKNOWN SCALETYPE\n");
    exit(EXIT_FAILURE);
  }
}

void SVGPLOT__AUTORANGE_TIME_TT2000(TIME_TT2000       *valmin,
				    TIME_TT2000       *valmax,
				    TIME_TT2000        val[],
				    INT4               num){
  INT4        isinit;
  TIME_TT2000 min = ILLEGAL_TT2000_VALUE;
  TIME_TT2000 max = ILLEGAL_TT2000_VALUE;
  INT4        n;

  isinit = 0;
  for(n = 0;n < num;n++){
    if(val[n] == ILLEGAL_TT2000_VALUE){
      continue;
    }
    if(!isinit){
      isinit = 1;
      min = val[n];
      max = val[n];
    }else{
      if(min > val[n]){
	min = val[n];
      }
      if(max < val[n]){
	max = val[n];
      }    
    }
  }
  if(isinit){
    if(min != max){
      *valmin = min;
      *valmax = max;
    }else{
      *valmin = min - 1000000000LL;
      *valmax = max + 1000000000LL;
    }
  }else{
    *valmin = -1000000000LL;
    *valmax = +1000000000LL;
  }      
}
