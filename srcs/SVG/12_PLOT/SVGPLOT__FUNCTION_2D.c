/***************************************************************** 
 *
 * SVGPLOT FUNCTION 2D
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__FUNCTION_2D(const CHAR *filename,
			  REAL8       xmin,
			  REAL8       xmax,
			  REAL8     (*f1)(REAL8 x),
			  ...){
  va_list args;
  INT4    num;
  REAL8  *x;
  REAL8  *y[10];
  REAL8  *buf;
  SVGPLOT plt;
  int     func_num;
  REAL8 (*func[10])(REAL8);
  CHAR   *color[10] = {
    "#FF0000",
    "#0000FF",
    "#00FF00",
    "#000000",
    "#AAAAAA",
    "#FF0000",
    "#0000FF",
    "#00FF00",
    "#000000",
    "#AAAAAA"
  };
  INT4   n,k;

  va_start(args,f1);
  func[0]  = f1;
  func_num = 1;
  for(k = 1;k < 10;k++){
    func[func_num] = va_arg(args,REAL8(*)(REAL8));
    if(func[func_num] == NULL){
      break;
    }
    func_num++;
  }
  va_end(args);
  
  num = 1000;

  if((buf = (REAL8*)malloc(sizeof(REAL8) * (num + num * func_num))) == NULL){
    return;
  }
  x = &buf[0];
  for(k = 0;k < func_num;k++){
    y[k] = &buf[num + k * num];
  }
  for(n = 0;n < num;n++){
    x[n] = xmin + n / (REAL8)(num - 1.0) * (xmax - xmin);
  }
  for(k = 0;k < func_num;k++){
    for(n = 0;n < num;n++){
      y[k][n] = func[k](x[n]);
    }
  }

  SVGPLOT__INITIALIZE_002(&plt,filename);

  SVGPLOT__SET_RANGE_X_002(&plt,x,num);
  SVGPLOT__SET_RANGE_Y_002(&plt,&y[0][0],num * func_num);

  for(k = 0;k < func_num;k++){  
    SVGPLOT__XY_LPLOT(&plt,x,y[k],num,-1.0,-1.0,-1.0,0,
		      "1.0",color[k],"3.0px",NULL,NULL,"round","round");
  }

  SVGPLOT__XY_AUX(&plt,
                  1,1,1,1,
                  1,1,1,1,
                  1,0,1,0,
                  1);
  
  SVGPLOT__XLABEL(&plt,  "x" ,NULL);
  SVGPLOT__YLABEL(&plt,"f_{1}(x), f_{2}(x), ...",NULL);
  SVGPLOT__TITLE (&plt,"SVGPLOT__FUNCTION_2D");

  SVGPLOT__FINALIZE(&plt);

  free(buf);
}

