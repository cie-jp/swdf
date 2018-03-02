/***************************************************************** 
 *
 * SVGPLOT FUNCTION 3D
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT.h"

void SVGPLOT__FUNCTION_3D(const CHAR *filename,
			  REAL8       xmin,
			  REAL8       xmax,
			  REAL8       ymin,
			  REAL8       ymax,
			  REAL8     (*f)(REAL8 x,REAL8 y),
			  INT4        zscaletype,
			  INT4        mode){
  REAL8  *x;
  REAL8  *y;
  REAL8  *z;
  REAL8  *buf;
  INT4    xnum;
  INT4    ynum;
  SVGPLOT plt;
  INT4    n,m;

  xnum = 100;
  ynum = 100;
  if((buf = (REAL8*)malloc(sizeof(REAL8) * (xnum + ynum + xnum * ynum))) == NULL){
    return;
  }
  x = &buf[0];
  y = &buf[xnum];
  z = &buf[xnum + ynum];

  for(n = 0;n < xnum;n++){
    x[n] = xmin + n / (REAL8)(xnum - 1.0) * (xmax - xmin);
  }
  for(m = 0;m < ynum;m++){
    y[m] = ymin + m / (REAL8)(ynum - 1.0) * (ymax - ymin);
  }
  for(m = 0;m < ynum;m++){
    for(n = 0;n < xnum;n++){
      z[n * ynum + m] = f(x[n],y[m]);
    }
  }
  
  SVGPLOT__INITIALIZE_002(&plt,filename);

  //SVGPLOT__SET_SCALETYPE_X(&plt,1);

  SVGPLOT__SET_SCALETYPE_Z(&plt,zscaletype);

  SVGPLOT__XYZ_CONTOUR(&plt,x,xnum,y,ynum,z,-1.0,-1.0,mode);
  SVGPLOT__XY_AUX(&plt,
                  1,1,1,1,
                  1,1,1,1,
                  1,0,1,0,
                  1);
  SVGPLOT__COLORBAR(&plt,
                    1,1,
                    2,2,
                    2,0,
                    1);

  SVGPLOT__XY_AUX(&plt,
                  1,1,1,1,
                  1,1,1,1,
                  1,0,1,0,
                  1);
  
  SVGPLOT__XLABEL(&plt,  "x"   ,NULL);
  SVGPLOT__YLABEL(&plt,  "y"   ,NULL);
  SVGPLOT__ZLABEL(&plt,"f(x,y)");
  SVGPLOT__TITLE (&plt,"SVGPLOT__FUNCTION_3D");

  SVGPLOT__FINALIZE(&plt);  

  free(buf);
}
