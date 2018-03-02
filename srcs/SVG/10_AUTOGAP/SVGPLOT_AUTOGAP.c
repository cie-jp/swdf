/***************************************************************** 
 *
 * SVGPLOT AUTOGAP
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_AUTOGAP.h"

void SVGPLOT__AUTOGAP_REAL8(REAL8 *valgap,
			    REAL8  val[],
			    INT4   num){
  REAL8 min = 0.0;
  REAL8 tmp;
  INT4  isinit;
  INT4  n;

  if(num < 2){
    *valgap = 1.0;
    return;
  }

  isinit = 0;
  for(n = 1;n < num;n++){
    tmp = fabs(val[n] - val[n - 1]);
    if(isnan(tmp) || isinf(tmp)){
      continue;
    }
    if(!isinit){
      isinit = 1;
      min  = tmp;
    }else{
      if(min > tmp){
	 min = tmp;
      }
    }
  }
  *valgap = isinit ? 1.25 * min : 1.0;
}

void SVGPLOT__AUTOGAP_TIME_TT2000(TIME_TT2000 *valgap,
				  TIME_TT2000  val[],
				  INT4         num){
  TIME_TT2000 min = ILLEGAL_TT2000_VALUE;
  TIME_TT2000 tmp;
  INT4        isinit;
  INT4        n;

  if(num < 2){
    *valgap = 1000000000LL;
    return;
  }

  isinit = 0;
  for(n = 1;n < num;n++){
    tmp = llabs(val[n] - val[n - 1]);
    if(!isinit){
      isinit = 1;
      min  = tmp;
    }else{
      if(min > tmp){
	 min = tmp;
      }
    }
  }
  *valgap = isinit ? 1.25 * min : 1000000000LL;
}
