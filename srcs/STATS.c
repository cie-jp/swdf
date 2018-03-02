/***************************************************************** 
 *
 * STATS 
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include<math.h>
#include<float.h>
#include"STATS.h"

REAL8 STATS__MIN(REAL8 x[],
		 INT4  num,
		 INT4  mode){
  INT4  isinit;
  REAL8 tmp;
  REAL8 min;
  INT4  n;

  min = NAN;
  switch(mode){
  case 0:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = x[n];
      if(isnan(tmp)){
	continue;
      }
      if(!isinit){
	min    = tmp;
	isinit = 1;
      }else{
	if(min > tmp){
	  min = tmp;
	}
      }
    }
    break;
  case 1:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = x[n];
      if(isnan(tmp) || (tmp < 0.0)){
	continue;
      }
      if(!isinit){
	min    = tmp;
	isinit = 1;
      }else{
	if(min > tmp){
	  min = tmp;
	}
      }
    }
    break;
  case 2:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = x[n];
      if(isnan(tmp) || (tmp < DBL_MIN)){	
	continue;
      }
      if(!isinit){
	min    = tmp;
	isinit = 1;
      }else{
	if(min > tmp){
	  min = tmp;
	}
      }
    }
    break;
  case 3:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = fabs(x[n]);
      if(isnan(tmp)){
	continue;
      }
      if(!isinit){
	min    = tmp;
	isinit = 1;
      }else{
	if(min > tmp){
	  min = tmp;
	}
      }
    }
    break;
  case 4:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = fabs(x[n]);
      if(isnan(tmp) || (tmp < DBL_MIN)){
	continue;
      }
      if(!isinit){
	min    = tmp;
	isinit = 1;
      }else{
	if(min > tmp){
	  min = tmp;
	}
      }
    }
    break;
  }
  return min;
}

REAL8 STATS__MAX(REAL8 x[],
		 INT4  num,
		 INT4  mode){
  INT4  isinit;
  REAL8 tmp;
  REAL8 max;
  INT4  n;

  max = NAN;
  switch(mode){
  case 0:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = x[n];
      if(isnan(tmp)){
	continue;
      }
      if(!isinit){
	max    = tmp;
	isinit = 1;
      }else{
	if(max < tmp){
	  max = tmp;
	}
      }
    }
    break;
  case 1:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = fabs(x[n]);
      if(isnan(tmp)){
	continue;
      }
      if(!isinit){
	max    = tmp;
	isinit = 1;
      }else{
	if(max < tmp){
	  max = tmp;
	}
      }
    }
    break;
  case 2:
    isinit = 0;
    for(n = 0;n < num;n++){
      tmp = -x[n];
      if(isnan(tmp)){
	continue;
      }
      if(!isinit){
	max    = tmp;
	isinit = 1;
      }else{
	if(max < tmp){
	  max = tmp;
	}
      }
    }
    break;
  }
  return max;
}

T2000 STATS__MIN_T2000(T2000 t[],
		       INT4  num){
  INT4  isinit;
  T2000 tmp;
  T2000 min;
  INT4  n;

  min    = ILLEGAL_TT2000_VALUE;
  isinit = 0;
  for(n = 0;n < num;n++){
    tmp = t[n];
    if(tmp == ILLEGAL_TT2000_VALUE){
      continue;
    }
    if(!isinit){
      min    = tmp;
      isinit = 1;
    }else{
      if(min > tmp){
	min = tmp;
      }
    }
  }
  return min;
}

T2000 STATS__MAX_T2000(T2000 t[],
		       INT4  num){
  INT4  isinit;
  T2000 tmp;
  T2000 max;
  INT4  n;

  max    = ILLEGAL_TT2000_VALUE;
  isinit = 0;
  for(n = 0;n < num;n++){
    tmp = t[n];
    if(tmp == ILLEGAL_TT2000_VALUE){
      continue;
    }
    if(!isinit){
      max    = tmp;
      isinit = 1;
    }else{
      if(max < tmp){
	max = tmp;
      }
    }
  }
  return max;
}
