#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

typedef struct{
  REAL x;
  REAL y;
}VECTOR_2D;

VECTOR_2D VECTOR_2D__ADD  (VECTOR_2D a,VECTOR_2D b);
VECTOR_2D VECTOR_2D__SUB  (VECTOR_2D a,VECTOR_2D b);
REAL      VECTOR_2D__DOT  (VECTOR_2D a,VECTOR_2D b);
REAL      VECTOR_2D__CROSS(VECTOR_2D a,VECTOR_2D b);

INT       VECTOR_2D__HITTEST_POINT_TRIANGLE(VECTOR_2D p,VECTOR_2D a,VECTOR_2D b,VECTOR_2D c);

VECTOR_2D VECTOR_2D__ADD  (VECTOR_2D a,VECTOR_2D b){
  VECTOR_2D c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;

  return c;
}

VECTOR_2D VECTOR_2D__SUB  (VECTOR_2D a,VECTOR_2D b){
  VECTOR_2D c;

  c.x = a.x - b.x;
  c.y = a.y - b.y;

  return c;
}

REAL      VECTOR_2D__DOT  (VECTOR_2D a,VECTOR_2D b){
  return a.x * b.x + a.y * b.y;
}

REAL      VECTOR_2D__CROSS(VECTOR_2D a,VECTOR_2D b){
  return a.x * b.y - a.y * b.x;
}

INT       VECTOR_2D__HITTEST_POINT_TRIANGLE(VECTOR_2D p,VECTOR_2D a,VECTOR_2D b,VECTOR_2D c){
  VECTOR_2D ab = VECTOR_2D__SUB(b,a);
  VECTOR_2D bp = VECTOR_2D__SUB(p,b);
  VECTOR_2D bc = VECTOR_2D__SUB(c,b);
  VECTOR_2D cp = VECTOR_2D__SUB(p,c);
  VECTOR_2D ca = VECTOR_2D__SUB(a,c);
  VECTOR_2D ap = VECTOR_2D__SUB(p,a);
  REAL      ab_cross_bp = VECTOR_2D__CROSS(ab,bp);
  REAL      bc_cross_cp = VECTOR_2D__CROSS(bc,cp);
  REAL      ca_cross_ap = VECTOR_2D__CROSS(ca,ap);

  if((ab_cross_bp > 0.0) && (bc_cross_cp > 0.0) && (ca_cross_ap > 0.0)){
    return 1;
  }
  if((ab_cross_bp < 0.0) && (bc_cross_cp < 0.0) && (ca_cross_ap < 0.0)){
    return 1;
  }
  return 0;
}

typedef struct{
  
}CAMERA;

REAL INTERPOLATE(REAL X0,REAL Y0,
                 REAL X1,REAL Y1,
                 REAL X2,REAL Y2,
                 REAL X3,REAL Y3,
                 REAL z1,REAL z2,REAL z3){
  REAL s,t;
  REAL a11,a12,b1;
  REAL a21,a22,b2;
  REAL det;
  REAL c11,c12;
  REAL c21,c22;

  a11 = X2 - X1; a12 = X3 - X1; b1 = X0 - X1;
  a21 = Y2 - Y1; a22 = Y3 - Y1; b2 = Y0 - Y1;
  det = a11 * a22 - a12 * a21;
  c11 =  a22 / det;c12 = -a12 / det;
  c21 = -a21 / det;c22 =  a11 / det;

  s   = c11 * b1 + c12 * b2;
  t   = c21 * b1 + c22 * b2;

  return z1 + s * (z2 - z1) + t * (z3 - z1);
}

void FILL(REAL cx[],INT cx_num,REAL cy[],INT cy_num,REAL contour[],REAL zbuf[],
          REAL X1,REAL Y1,REAL Z1,
          REAL X2,REAL Y2,REAL Z2,
          REAL X3,REAL Y3,REAL Z3,
          REAL z1,REAL z2,REAL z3){
  INT X1_id = (X1 - cx[0]) / (REAL)(cx[cx_num - 1] - cx[0]) * (REAL)cx_num;
  INT Y1_id = (Y1 - cy[0]) / (REAL)(cy[cy_num - 1] - cy[0]) * (REAL)cy_num;
  INT X2_id = (X2 - cx[0]) / (REAL)(cx[cx_num - 1] - cx[0]) * (REAL)cx_num;
  INT Y2_id = (Y2 - cy[0]) / (REAL)(cy[cy_num - 1] - cy[0]) * (REAL)cy_num;
  INT X3_id = (X3 - cx[0]) / (REAL)(cx[cx_num - 1] - cx[0]) * (REAL)cx_num;
  INT Y3_id = (Y3 - cy[0]) / (REAL)(cy[cy_num - 1] - cy[0]) * (REAL)cy_num;
  INT xmin,xmax;
  INT ymin,ymax;
  VECTOR_2D p,a,b,c;
  REAL Z;
  
  a.x = X1;
  a.y = Y1;
  b.x = X2;
  b.y = Y2;
  c.x = X3;
  c.y = Y3;
  
  xmin = fmin(X1_id,fmin(X2_id,X3_id));
  xmax = fmax(X1_id,fmax(X2_id,X3_id));
  ymin = fmin(Y1_id,fmin(Y2_id,Y3_id));
  ymax = fmax(Y1_id,fmax(Y2_id,Y3_id));
  if(xmin < 0){
    xmin = 0;
  }
  if(xmax >= cx_num){
    xmax = cx_num - 1;
  }
  if(ymin < 0){
    ymin = 0;
  }
  if(ymax >= cy_num){
    ymax = cy_num - 1;
  }

  //Z = (Z1 + Z2 + Z3) / 3.0;
  fprintf(stderr,"%d:%d:%d:%d\n",xmin,xmax,ymin,ymax);
  for(int n = xmin;n <= xmax;n++){
    for(int m = ymin;m <= ymax;m++){
      /*if(Z > zbuf[n * cy_num + m]){
        continue;
      }
      zbuf[n * cy_num + m] = Z;*/
      p.x = cx[n];
      p.y = cy[m];
      if(VECTOR_2D__HITTEST_POINT_TRIANGLE(p,a,b,c) != 1){
        continue;
      }
      //奥行き
      Z = INTERPOLATE(p.x,p.y,
                      a.x,a.y,
                      b.x,b.y,
                      c.x,c.y,
                      Z1,Z2,Z3);
      
      if(Z > zbuf[n * cy_num + m]){
        continue;
      }
      zbuf[n * cy_num + m] = Z;
      //contour[n * cy_num + m] = (z1 + z2 + z3) / 3.0;
      contour[n * cy_num + m] = INTERPOLATE(p.x,p.y,
                                            a.x,a.y,
                                            b.x,b.y,
                                            c.x,c.y,
                                            z1,z2,z3);
    }
  }
}

void TRANSFORM_3D_2(REAL *dst_x,
                    REAL *dst_y,
                    REAL *dst_z,
                    REAL  src_x,
                    REAL  src_y,
                    REAL  src_z){
  //カメラ位置(ワールド座標系)
  REAL r        = 20.0;  
  REAL theta    = 40.0 / 180.0 * M_PI;
  REAL phi      = 30.0 / 180.0 * M_PI;
  REAL xc       = r * sin(theta) * cos(phi);
  REAL yc       = r * sin(theta) * sin(phi);
  REAL zc       = r * cos(theta);

  //カメラ基底(ワールド座標系) : ey (カメラの上を向く) ez (視線方向)
  //カメラ座標系からワールド座標系への変換
  RMatrix Twc(4,4);
  //ワールド座標系からカメラ座標系への変換
  RMatrix Tcw(4,4);
  RMatrix world (4,1);
  RMatrix camera(4,1);
  REAL    camera_x;
  REAL    camera_y;
  REAL    camera_z;
  REAL    projection_xmin;
  REAL    projection_xmax;
  REAL    projection_ymin;
  REAL    projection_ymax;
  REAL    projection_x;
  REAL    projection_y;
  REAL    screen_xsize;
  REAL    screen_ysize;
  REAL    screen_x0;
  REAL    screen_y0;
  REAL    screen_x;
  REAL    screen_y;
  
  Twc[0][0] =  sin(phi); Twc[0][1] = -cos(theta) * cos(phi); Twc[0][2] = -sin(theta) * cos(phi); Twc[0][3] =  xc;
  Twc[1][0] = -cos(phi); Twc[1][1] = -cos(theta) * sin(phi); Twc[1][2] = -sin(theta) * sin(phi); Twc[1][3] =  yc;
  Twc[2][0] =       0.0; Twc[2][1] =  sin(theta)           ; Twc[2][2] = -cos(theta)           ; Twc[2][3] =  zc;
  Twc[3][0] =       0.0; Twc[3][1] =                    0.0; Twc[3][2] =                      r; Twc[3][3] = 1.0;

  Tcw       = ~Twc;

  world[0][0] = src_x;
  world[1][0] = src_y;
  world[2][0] = src_z;
  world[3][0] = 1.0;

  camera = Tcw * world;
  
  //カメラ座標系
  camera_x = camera[0][0];
  camera_y = camera[1][0];
  camera_z = camera[2][0];

  //射影空間
  projection_xmin = -sqrt(3.0);
  projection_xmax = +sqrt(3.0);
  projection_ymin = -sqrt(3.0);
  projection_ymax = +sqrt(3.0);

  projection_x = -1.0 + 2.0 * (camera_x - projection_xmin) / (projection_xmax - projection_xmin);
  projection_y = -1.0 + 2.0 * (camera_y - projection_ymin) / (projection_ymax - projection_ymin);
  
  //スクリーン座標系[-1,1]^2
  screen_xsize = 2.0;
  screen_ysize = 2.0; 
  screen_x0    = 0.0;
  screen_y0    = 0.0;

  screen_x = -projection_x / (projection_xmax - projection_xmin);
  screen_y =  projection_y / (projection_ymax - projection_ymin);
  
  *dst_x = screen_xsize * screen_x + screen_x0;
  *dst_y = screen_ysize * screen_y + screen_y0;
  *dst_z = camera_z;
}

int main(int argc,char *argv[]){
  SVGPLOT plt;

  SVGPLOT__INITIALIZE_002(&plt,"3d.svg");

  
#define XNUM (150)
#define YNUM (150)
  
  REAL x[XNUM];
  REAL y[XNUM];
  REAL z[XNUM][YNUM];
  
  for(int n = 0;n < XNUM;n++){
    x[n] = -1.0 + 2.0 * n / (REAL)XNUM;
  }
  for(int m = 0;m < YNUM;m++){
    y[m] = -1.0 + 2.0 * m / (REAL)YNUM;
  }

  for(int n = 0;n < XNUM;n++){
    for(int m = 0;m < YNUM;m++){
      z[n][m] = exp(-2.0 * (x[n] * x[n] + y[m] * y[m])) * cos(4.0 * M_PI * sqrt(x[n] * x[n] + y[m] * y[m]));
    }
  }

  REAL x1,y1,z1,X1,Y1,Z1;
  REAL x2,y2,z2,X2,Y2,Z2;
  REAL x3,y3,z3,X3,Y3,Z3;
  REAL *cx;//[-1,+1]
  REAL *cy;//[-1,+1]
  INT   cx_num = 1000;
  INT   cy_num = 1000;
  REAL *contour;
  REAL *zbuf;

  cx = (REAL*)malloc(sizeof(REAL) * cx_num);
  cy = (REAL*)malloc(sizeof(REAL) * cy_num);
  for(int n = 0;n < cx_num;n++){
    cx[n] = -1.0 + 2.0 * n / (REAL)cx_num;
  }
  for(int m = 0;m < cy_num;m++){
    cy[m] = -1.0 + 2.0 * m / (REAL)cy_num;
  }

  contour = (REAL*)malloc(sizeof(REAL) * cx_num * cy_num);
  zbuf    = (REAL*)malloc(sizeof(REAL) * cx_num * cy_num);
  memset(contour,0x00,sizeof(REAL) * cx_num * cy_num);
  memset(zbuf   ,0x00,sizeof(REAL) * cx_num * cy_num);
  for(int n = 0;n < cx_num;n++){
    for(int m = 0;m < cy_num;m++){
      contour[n * cy_num + m] = NAN;
      zbuf   [n * cy_num + m] = 1.0e+8;
    }
  }
  
  for(int m = 0;m < YNUM - 1;m++){
    for(int n = 0;n < XNUM - 1;n++){
      x1 = x[n];
      y1 = y[m];
      z1 = z[n][m];
      x2 = x[n + 1];
      y2 = y[m];
      z2 = z[n + 1][m];
      x3 = x[n];
      y3 = y[m + 1];
      z3 = z[n][m + 1];
      TRANSFORM_3D_2(&X1,&Y1,&Z1,x1,y1,z1);
      TRANSFORM_3D_2(&X2,&Y2,&Z2,x2,y2,z2);
      TRANSFORM_3D_2(&X3,&Y3,&Z3,x3,y3,z3);
      FILL(cx,cx_num,cy,cy_num,contour,zbuf,
           X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,z[n][m],z[n + 1][m],z[n][m + 1]);

      x1 = x[n + 1];
      y1 = y[m];
      z1 = z[n + 1][m];
      x2 = x[n];
      y2 = y[m + 1];
      z2 = z[n][m + 1];
      x3 = x[n + 1];
      y3 = y[m + 1];
      z3 = z[n + 1][m + 1];
      TRANSFORM_3D_2(&X1,&Y1,&Z1,x1,y1,z1);
      TRANSFORM_3D_2(&X2,&Y2,&Z2,x2,y2,z2);
      TRANSFORM_3D_2(&X3,&Y3,&Z3,x3,y3,z3);
      FILL(cx,cx_num,cy,cy_num,contour,zbuf,
           X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,z[n + 1][m],z[n][m + 1],z[n + 1][m + 1]);

    }
  }
  
  REAL zmin,zmax;
  
  zmin = fmin(STATS__MIN(contour,cx_num * cy_num,0),
              STATS__MIN(contour,cx_num * cy_num,0));
  zmax = fmax(STATS__MAX(contour,cx_num * cy_num,0),
              STATS__MAX(contour,cx_num * cy_num,0));

  SVGPLOT_PALETTE__Create10(&plt.pal);
  SVGPLOT__SET_RANGE_Z_003(&plt,0.0,1.0);  
   
  SVGPLOT__XYZ_CONTOUR(&plt,cx,cx_num,cy,cy_num,contour,-1.0,-1.0,0);

  free(cx);
  free(cy);
  free(contour);
  free(zbuf);

  // ==============================================
  SVG_STYLE linestyle;
  //REAL      X1,Y1,Z1;
  //REAL      X2,Y2,Z2;

  //x軸
  TRANSFORM_3D_2(&X1,&Y1,&Z1,0.0,0.0,0.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,1.0,0.0,0.0);
  SVG_STYLE__SET_001(linestyle,"1.0","#FF0000","2.0",NULL,NULL,NULL,NULL,"none");
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  //y軸
  TRANSFORM_3D_2(&X1,&Y1,&Z1,0.0,0.0,0.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,0.0,1.0,0.0);
  SVG_STYLE__SET_001(linestyle,"1.0","#00FF00","2.0",NULL,NULL,NULL,NULL,"none");
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  //z軸
  TRANSFORM_3D_2(&X1,&Y1,&Z1,0.0,0.0,0.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,0.0,0.0,1.0);
  SVG_STYLE__SET_001(linestyle,"1.0","#0000FF","2.0",NULL,NULL,NULL,NULL,"none");
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  //枠線(x軸)
  SVG_STYLE__SET_001(linestyle,"1.0","#AA0000","2.0",NULL,NULL,NULL,NULL,"none");
  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,-1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,-1.0,-1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,+1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,+1.0,-1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,-1.0,+1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,-1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);
  
  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,+1.0,+1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,+1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);
  
  //枠線(y軸)
  SVG_STYLE__SET_001(linestyle,"1.0","#00AA00","2.0",NULL,NULL,NULL,NULL,"none");
  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,-1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,-1.0,+1.0,-1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,-1.0,+1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,-1.0,+1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  TRANSFORM_3D_2(&X1,&Y1,&Z1,+1.0,-1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,+1.0,-1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);
  
  TRANSFORM_3D_2(&X1,&Y1,&Z1,+1.0,-1.0,+1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,+1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  //枠線(z軸)
  SVG_STYLE__SET_001(linestyle,"1.0","#0000AA","2.0",NULL,NULL,NULL,NULL,"none");
  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,-1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,-1.0,-1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  TRANSFORM_3D_2(&X1,&Y1,&Z1,-1.0,+1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,-1.0,+1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);
  
  TRANSFORM_3D_2(&X1,&Y1,&Z1,+1.0,-1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,-1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);
  
  TRANSFORM_3D_2(&X1,&Y1,&Z1,+1.0,+1.0,-1.0);
  TRANSFORM_3D_2(&X2,&Y2,&Z2,+1.0,+1.0,+1.0);
  X1 = plt.Xmin + (X1 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y1 = plt.Ymin + (Y1 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  X2 = plt.Xmin + (X2 + 1.0) / 2.0 * (plt.Xmax - plt.Xmin);
  Y2 = plt.Ymin + (Y2 + 1.0) / 2.0 * (plt.Ymax - plt.Ymin);
  SVG__LINE(&plt.svg,X1,Y1,X2,Y2,linestyle);

  SVG__RECT(&plt.svg,plt.Xmin,plt.Ymin,plt.Xmax,plt.Ymax,plt.borderstyle);

  SVGPLOT__FINALIZE(&plt);
    
  return 0;
}
