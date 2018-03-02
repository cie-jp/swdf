/***************************************************************** 
 *
 * SVGPLOT CHECK
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_CHECK.h"

INT4  SVGPLOT_CHECK__OUT_OF_RANGE_1D(REAL8 val,
				     REAL8 min,
				     REAL8 max){
  return (val < min) || (max < val); 
}

INT4  SVGPLOT_CHECK__OUT_OF_RANGE_2D(REAL8 X,
				     REAL8 Y,
				     REAL8 Xmin,
				     REAL8 Xmax,
				     REAL8 Ymin,
				     REAL8 Ymax){
  return SVGPLOT_CHECK__OUT_OF_RANGE_1D(X,Xmin,Xmax) || SVGPLOT_CHECK__OUT_OF_RANGE_1D(Y,Ymin,Ymax);
}

INT4  SVGPLOT_CHECK__LINE_CLIPPING  (REAL8 *X1clip,
				     REAL8 *Y1clip,
				     REAL8 *X2clip,
				     REAL8 *Y2clip,
				     REAL8  X1,
				     REAL8  Y1,
				     REAL8  X2,
				     REAL8  Y2,
				     REAL8  Xmin,
				     REAL8  Xmax,
				     REAL8  Ymin,
				     REAL8  Ymax){
  INT4  f1,f2;
  REAL8 r;
  REAL8 ratio[4];
  INT4  num;

  f1 = SVGPLOT_CHECK__OUT_OF_RANGE_2D(X1,Y1,Xmin,Xmax,Ymin,Ymax);
  f2 = SVGPLOT_CHECK__OUT_OF_RANGE_2D(X2,Y2,Xmin,Xmax,Ymin,Ymax);

  if(!f1 && !f2){
    *X1clip = X1;
    *Y1clip = Y1;
    *X2clip = X2;
    *Y2clip = Y2;
    return 0;//INSIDE
  }

  if( f1 &&  f2){
    num   = 0;
    if(fabs(X2 - X1) > DBL_MIN){
      r = (Xmin - X1) / (X2 - X1);
      if((0.0 <= r) && (r <= 1.0) && !SVGPLOT_CHECK__OUT_OF_RANGE_1D(Y1 + (Y2 - Y1) * r,Ymin,Ymax)){
	ratio[num++] = r;
      }
      r = (Xmax - X1) / (X2 - X1);
      if((0.0 <= r) && (r <= 1.0) && !SVGPLOT_CHECK__OUT_OF_RANGE_1D(Y1 + (Y2 - Y1) * r,Ymin,Ymax)){
	ratio[num++] = r;
      }
    }
    if(fabs(Y2 - Y1) > DBL_MIN){
      r = (Ymin - Y1) / (Y2 - Y1);
      if((0.0 <= r) && (r <= 1.0) && !SVGPLOT_CHECK__OUT_OF_RANGE_1D(X1 + (X2 - X1) * r,Xmin,Xmax)){
	ratio[num++] = r;
      }
      r = (Ymax - Y1) / (Y2 - Y1);
      if((0.0 <= r) && (r <= 1.0) && !SVGPLOT_CHECK__OUT_OF_RANGE_1D(X1 + (X2 - X1) * r,Xmin,Xmax)){
	ratio[num++] = r;
      }
    }
    if(num == 2){
      r       = fmin(ratio[0],ratio[1]);
      *X1clip = X1 + (X2 - X1) * r;
      *Y1clip = Y1 + (Y2 - Y1) * r;
      r       = fmax(ratio[0],ratio[1]);
      *X2clip = X1 + (X2 - X1) * r;
      *Y2clip = Y1 + (Y2 - Y1) * r;
      return  3;//   INTERSECTION
    }
    *X1clip = X1;
    *Y1clip = Y1;
    *X2clip = X2;
    *Y2clip = Y2;
    if(num <  2){
      return  4;//NO INTERSECTION
    }else{
      return -1;//INVALID
    }
  }
  if(f1){
    if(X1 < Xmin){
      r  = (Xmin - X1) / (X2 - X1);
      X1 =  Xmin;
      Y1 = ( 1.0 - r ) *  Y1 + r * Y2;
    }
    if(X1 > Xmax){
      r  = (X1 - Xmax) / (X1 - X2);
      X1 =  Xmax;
      Y1 = ( 1.0 - r ) *  Y1 + r * Y2;
    }
    if(Y1 < Ymin){
      r  = (Ymin - Y1) / (Y2 - Y1);
      X1 = ( 1.0 - r ) *  X1 + r * X2;
      Y1 =  Ymin;
    }
    if(Y1 > Ymax){
      r  = (Y1 - Ymax) / (Y1 - Y2);
      X1 = ( 1.0 - r ) *  X1 + r * X2;
      Y1 =  Ymax;
    }
  }
  if(f2){
    if(X2 < Xmin){
      r  = (Xmin - X2) / (X1 - X2);
      X2 =  Xmin;
      Y2 = ( 1.0 - r ) *  Y2 + r * Y1;
    }
    if(X2 > Xmax){
      r  = (X2 - Xmax) / (X2 - X1);
      X2 =  Xmax;
      Y2 = ( 1.0 - r ) *  Y2 + r * Y1;
    }
    if(Y2 < Ymin){
      r  = (Ymin - Y2) / (Y1 - Y2);
      X2 = ( 1.0 - r ) *  X2 + r * X1;
      Y2 =  Ymin;
    }
    if(Y2 > Ymax){
      r  = (Y2 - Ymax) / (Y2 - Y1);
      X2 = ( 1.0 - r ) *  X2 + r * X1;
      Y2 =  Ymax;
    }
  }
  *X1clip = X1;
  *Y1clip = Y1;
  *X2clip = X2;
  *Y2clip = Y2;
  return (!f1 && f2) ? 1 : 2;
}
