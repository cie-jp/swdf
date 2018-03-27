typedef struct{
  REAL x;
  REAL y;
}VECTOR_2D;

VECTOR_2D VECTOR_2D__INIT (REAL x,REAL y);
VECTOR_2D VECTOR_2D__ADD  (VECTOR_2D a,VECTOR_2D b);
VECTOR_2D VECTOR_2D__SUB  (VECTOR_2D a,VECTOR_2D b);
REAL      VECTOR_2D__DOT  (VECTOR_2D a,VECTOR_2D b);
REAL      VECTOR_2D__CROSS(VECTOR_2D a,VECTOR_2D b);

VECTOR_2D VECTOR_2D__INIT (REAL x,REAL y){
  VECTOR_2D c;

  c.x = x;
  c.y = y;

  return c;
}

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

typedef struct{
  REAL x;
  REAL y;
  REAL z;
}VECTOR_3D;

VECTOR_3D VECTOR_3D__INIT (REAL x,REAL y,REAL z);
VECTOR_3D VECTOR_3D__ADD  (VECTOR_3D a,VECTOR_3D b);
VECTOR_3D VECTOR_3D__SUB  (VECTOR_3D a,VECTOR_3D b);
REAL      VECTOR_3D__DOT  (VECTOR_3D a,VECTOR_3D b);

VECTOR_3D VECTOR_3D__INIT (REAL x,REAL y,REAL z){
  VECTOR_3D c;

  c.x = x;
  c.y = y;
  c.z = z;

  return c;
}

VECTOR_3D VECTOR_3D__ADD  (VECTOR_3D a,VECTOR_3D b){
  VECTOR_3D c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
  
  return c;
}

VECTOR_3D VECTOR_3D__SUB  (VECTOR_3D a,VECTOR_3D b){
  VECTOR_3D c;

  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  
  return c;
}

REAL      VECTOR_3D__DOT  (VECTOR_3D a,VECTOR_3D b){
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

//P[0] : (x,y,z) = (xmin,ymin,zmin)
//P[1] : (x,y,z) = (xmin,ymin,zmax)
//P[2] : (x,y,z) = (xmin,ymax,zmin)
//P[3] : (x,y,z) = (xmin,ymax,zmax)
//P[4] : (x,y,z) = (xmax,ymin,zmin)
//P[5] : (x,y,z) = (xmax,ymin,zmax)
//P[6] : (x,y,z) = (xmax,ymax,zmin)
//P[7] : (x,y,z) = (xmax,ymax,zmax)

typedef struct{
  VECTOR_3D P[8];
  REAL      xmin;
  REAL      xmax;
  REAL      ymin;
  REAL      ymax;
  REAL      zmin;
  REAL      zmax;
}REGION_3D;

REGION_3D REGION_3D__INIT(REAL xmin,REAL xmax,
                          REAL ymin,REAL ymax,
                          REAL zmin,REAL zmax){
  REGION_3D plt;

  plt.P[0] = VECTOR_3D__INIT(xmin,ymin,zmin);
  plt.P[1] = VECTOR_3D__INIT(xmin,ymin,zmax);
  plt.P[2] = VECTOR_3D__INIT(xmin,ymax,zmin);
  plt.P[3] = VECTOR_3D__INIT(xmin,ymax,zmax);
  plt.P[4] = VECTOR_3D__INIT(xmax,ymin,zmin);
  plt.P[5] = VECTOR_3D__INIT(xmax,ymin,zmax);
  plt.P[6] = VECTOR_3D__INIT(xmax,ymax,zmin);
  plt.P[7] = VECTOR_3D__INIT(xmax,ymax,zmax);
  plt.xmin = xmin;
  plt.xmax = xmax;
  plt.ymin = ymin;
  plt.ymax = ymax;
  plt.zmin = zmin;
  plt.zmax = zmax;

  return plt;
}

void      REGION_3D__CALC_SIZE(REGION_3D *r){
  INT n;
  
  r->xmin = r->P[0].x;
  r->xmax = r->P[0].x;
  r->ymin = r->P[0].y;
  r->ymax = r->P[0].y;
  r->zmin = r->P[0].z;
  r->zmax = r->P[0].z;

  for(n = 1;n < 8;n++){
    if(r->xmin > r->P[n].x){
       r->xmin = r->P[n].x;
    }
    if(r->xmax < r->P[n].x){
       r->xmax = r->P[n].x;
    }
    if(r->ymin > r->P[n].y){
       r->ymin = r->P[n].y;
    }
    if(r->ymax < r->P[n].y){
       r->ymax = r->P[n].y;
    }
    if(r->zmin > r->P[n].z){
       r->zmin = r->P[n].z;
    }
    if(r->zmax < r->P[n].z){
       r->zmax = r->P[n].z;
    }
  }    
}

// 位置ベクトル(ワールド座標系)を取得
VECTOR_3D VECTOR_3D__MtoW(VECTOR_3D pm, //(in) 位置ベクトル(数学座標系)
                          REGION_3D rm, //(in) プロット領域(数学座標系)
                          REGION_3D rw){//(in) プロット領域(ワールド座標系)
  VECTOR_3D pw;

  pw = VECTOR_3D__INIT(rw.xmin + (pm.x - rm.xmin) / (rm.xmax - rm.xmin) * (rw.xmax - rw.xmin),
                       rw.ymin + (pm.y - rm.ymin) / (rm.ymax - rm.ymin) * (rw.ymax - rw.ymin),
                       rw.zmin + (pm.z - rm.zmin) / (rm.zmax - rm.zmin) * (rw.zmax - rw.zmin));

  return pw;
}

//カメラ情報
typedef struct{
  //カメラ位置(ワールド座標系)
  REAL      r;       
  REAL      theta;// [rad]
  REAL      phi;  // [rad]
  VECTOR_3D pos;
}CAMERA_3D;

CAMERA_3D CAMERA_3D__INIT(REAL r,    //(in)
                          REAL theta,//(in) [rad]
                          REAL phi){ //(in) [rad]
  CAMERA_3D ci;

  ci.r     = r;
  ci.theta = theta;
  ci.phi   = phi;
  ci.pos   = VECTOR_3D__INIT(r * sin(theta) * cos(phi),r * sin(theta) * sin(phi),r * cos(theta));
  return ci;
}

// 位置ベクトル(カメラ座標系)を取得
VECTOR_3D VECTOR_3D__WtoC(VECTOR_3D pw, //(in) 位置ベクトル(ワールド座標系)
                          CAMERA_3D ci){//(in) カメラ情報
  REAL      WtoC[3][3];
  VECTOR_3D pc;

  WtoC[0][0] =                  sin(ci.phi); WtoC[0][1] =                 -cos(ci.phi); WtoC[0][2] =            0.0;
  WtoC[1][0] = -cos(ci.theta) * cos(ci.phi); WtoC[1][1] = -cos(ci.theta) * sin(ci.phi); WtoC[1][2] =  sin(ci.theta);
  WtoC[2][0] = -sin(ci.theta) * cos(ci.phi); WtoC[2][1] = -sin(ci.theta) * sin(ci.phi); WtoC[2][2] = -cos(ci.theta);

  pc = VECTOR_3D__INIT(WtoC[0][0] * pw.x + WtoC[0][1] * pw.y + WtoC[0][2] * pw.z,
                       WtoC[1][0] * pw.x + WtoC[1][1] * pw.y + WtoC[1][2] * pw.z,
                       WtoC[2][0] * pw.x + WtoC[2][1] * pw.y + WtoC[2][2] * pw.z + ci.r);

  return pc;
}

// プロット領域(カメラ座標系)を取得
REGION_3D REGION_3D__WtoC(REGION_3D rw, //(in) プロット領域(ワールド座標系)
                          CAMERA_3D ci){//(in) カメラ情報
  REGION_3D rc;
  INT       n;
  
  for(n = 0;n < 8;n++){
    rc.P[n] = VECTOR_3D__WtoC(rw.P[n],ci);
  }  

  REGION_3D__CALC_SIZE(&rc);

  return rc;
}

// 位置ベクトル(ビュー座標系)を取得
VECTOR_3D VECTOR_3D__CtoV(VECTOR_3D pc, //(in) 位置ベクトル(カメラ座標系)
                          REGION_3D rc){//(in) プロット領域(カメラ座標系)
  REAL      r;
  REAL      z0;
  VECTOR_3D pv;

  r  = fmax(fmax(fabs(rc.xmin),fabs(rc.xmax)),
            fmax(fabs(rc.ymin),fabs(rc.ymax)));
  r  = fmax(r,(rc.zmax - rc.zmin) / 2.0);
  z0 =        (rc.zmax + rc.zmin) / 2.0 ;  

  pv = VECTOR_3D__INIT( pc.x / r,
                        pc.y / r,
                       (pc.z - z0) / r);

  return pv;
}

// プロット領域(ビュー座標系)を取得
REGION_3D REGION_3D__CtoV(REGION_3D rc){//(in) プロット領域(カメラ座標系)
  REAL      r;
  REAL      z0;
  REGION_3D rv;
  INT       n;

  r  = fmax(fmax(fabs(rc.xmin),fabs(rc.xmax)),
            fmax(fabs(rc.ymin),fabs(rc.ymax)));
  r  = fmax(r,(rc.zmax - rc.zmin) / 2.0);
  z0 =        (rc.zmax + rc.zmin) / 2.0 ;

  for(n = 0;n < 8;n++){
    rv.P[n] = VECTOR_3D__INIT( rc.P[n].x / r,
                               rc.P[n].y / r,
                              (rc.P[n].z - z0) / r);
  }  

  REGION_3D__CALC_SIZE(&rv);

  return rv;
}

// 位置ベクトル(スクリーン座標系)を取得
VECTOR_3D VECTOR_3D__VtoS(VECTOR_3D pv,     //(in) 位置ベクトル(ビュー座標系)
                          REAL      x0,
                          REAL      y0,
                          REAL      width,  //(in) スクリーンの横幅
                          REAL      height){//(in) スクリーンの縦幅
  VECTOR_3D ps;
  REAL      r;

  r  = fmin(width,height);

  ps = VECTOR_3D__INIT(pv.x / 2.0 * r + x0 + (width  / 2.0),
                       pv.y / 2.0 * r + y0 + (height / 2.0),
                       pv.z);
  return ps;
}

// プロット領域(スクリーン座標系)を取得
REGION_3D REGION_3D__VtoS(REGION_3D rv,     //(in) プロット領域(ビュー座標系)
                          REAL      x0,
                          REAL      y0,
                          REAL      width,  //(in) スクリーンの横幅
                          REAL      height){//(in) スクリーンの縦幅
  REGION_3D rs;
  REAL      r;
  INT       n;

  r  = fmin(width,height);

  for(n = 0;n < 8;n++){
    rs.P[n] = VECTOR_3D__INIT(rv.P[n].x / 2.0 * r + x0 + (width  / 2.0),
                              rv.P[n].y / 2.0 * r + y0 + (height / 2.0),
                              rv.P[n].z);
  }

  REGION_3D__CALC_SIZE(&rs);
  
  return rs;
}

// 位置ベクトル(スクリーン座標系)を取得
VECTOR_3D VECTOR_3D__MtoS(VECTOR_3D pm,
                          REAL      xmin,
                          REAL      xmax,
                          REAL      ymin,
                          REAL      ymax,
                          REAL      zmin,
                          REAL      zmax,
                          REAL      obj_xmin,
                          REAL      obj_xmax,
                          REAL      obj_ymin,
                          REAL      obj_ymax,
                          REAL      obj_zmin,
                          REAL      obj_zmax,
                          REAL      r,
                          REAL      theta,
                          REAL      phi,
                          REAL      x0,
                          REAL      y0,
                          REAL      width,
                          REAL      height){
  CAMERA_3D ci;
  REGION_3D rm;
  REGION_3D rw;
  REGION_3D rc;
  VECTOR_3D pw;
  VECTOR_3D pc;
  VECTOR_3D pv;
  VECTOR_3D ps;

  ci = CAMERA_3D__INIT(r,theta,phi);
  rm = REGION_3D__INIT(xmin,xmax,
                       ymin,ymax,
                       zmin,zmax);
  rw = REGION_3D__INIT(obj_xmin,obj_xmax,
                       obj_ymin,obj_ymax,
                       obj_zmin,obj_zmax);
  rc = REGION_3D__WtoC(rw,ci);
  pw = VECTOR_3D__MtoW(pm,rm,rw);
  pc = VECTOR_3D__WtoC(pw,ci);
  pv = VECTOR_3D__CtoV(pc,rc);
  ps = VECTOR_3D__VtoS(pv,x0,y0,width,height);

  return ps;
}

// プロット領域(スクリーン座標系)を取得
REGION_3D REGION_3D__WtoS(REAL obj_xmin,
                          REAL obj_xmax,
                          REAL obj_ymin,
                          REAL obj_ymax,
                          REAL obj_zmin,
                          REAL obj_zmax,
                          REAL r,
                          REAL theta,
                          REAL phi,
                          REAL x0,
                          REAL y0,
                          REAL width,
                          REAL height){
  REGION_3D rw;
  CAMERA_3D ci;
  REGION_3D rc;
  REGION_3D rv;
  REGION_3D rs;

  rw = REGION_3D__INIT(obj_xmin,obj_xmax,
                       obj_ymin,obj_ymax,
                       obj_zmin,obj_zmax);
  ci = CAMERA_3D__INIT(r,theta,phi);
  rc = REGION_3D__WtoC(rw,ci);
  rv = REGION_3D__CtoV(rc);
  rs = REGION_3D__VtoS(rv,x0,y0,width,height);

  return rs;
}

void DRAW_BORDER(SVGPLOT *plt){
  // プロット領域(数学    座標系)の設定
  REAL xmin     =  0.0;
  REAL xmax     =  1.0;
  REAL ymin     =  0.0;
  REAL ymax     =  1.0;
  REAL zmin     =  0.0;
  REAL zmax     =  1.0;
  // プロット領域(ワールド座標系)の設定
  REAL obj_xmin = -1.0;
  REAL obj_xmax = +1.0;
  REAL obj_ymin = -2.0;
  REAL obj_ymax = +2.0;
  REAL obj_zmin = -1.0;
  REAL obj_zmax = +1.0;
  // カメラ位置の設定
  REAL r        = 20.0;
  REAL theta    = 30.0 / 180.0 * M_PI;
  REAL phi      = 30.0 / 180.0 * M_PI;
  // スクリーンの設定
  REAL x0       = plt->Xmin;
  REAL y0       = plt->Ymin;
  REAL width    = plt->Xmax - plt->Xmin;
  REAL height   = plt->Ymax - plt->Ymin;

  REGION_3D rs;
  SVG_STYLE linestyle;

  rs = REGION_3D__WtoS(obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);

  SVG_STYLE__SET_001(linestyle,"1.0","#FF0000","4.0",NULL,NULL,NULL,NULL,"none");
  //(-1,-1,-1) - (+1,-1,-1) x軸1
  SVG__LINE(&plt->svg,
            rs.P[0].x,rs.P[0].y,
            rs.P[4].x,rs.P[4].y,
            linestyle);
  //(-1,-1,+1) - (+1,-1,+1) x軸2
  SVG__LINE(&plt->svg,
            rs.P[1].x,rs.P[1].y,
            rs.P[5].x,rs.P[5].y,
            linestyle);
  //(-1,+1,-1) - (+1,+1,-1) x軸3
  SVG__LINE(&plt->svg,
            rs.P[2].x,rs.P[2].y,
            rs.P[6].x,rs.P[6].y,
            linestyle);
  //(-1,+1,+1) - (+1,+1,+1) x軸4
  SVG__LINE(&plt->svg,
            rs.P[3].x,rs.P[3].y,
            rs.P[7].x,rs.P[7].y,
            linestyle);

  SVG_STYLE__SET_001(linestyle,"1.0","#00FF00","4.0",NULL,NULL,NULL,NULL,"none");
  //(-1,-1,-1) - (-1,+1,-1) y軸1
  SVG__LINE(&plt->svg,
            rs.P[0].x,rs.P[0].y,
            rs.P[2].x,rs.P[2].y,
            linestyle);
  //(-1,-1,+1) - (-1,+1,+1) y軸2
  SVG__LINE(&plt->svg,
            rs.P[1].x,rs.P[1].y,
            rs.P[3].x,rs.P[3].y,
            linestyle);
  //(+1,-1,-1) - (+1,+1,-1) y軸3
  SVG__LINE(&plt->svg,
            rs.P[4].x,rs.P[4].y,
            rs.P[6].x,rs.P[6].y,
            linestyle);
  //(+1,-1,+1) - (+1,+1,+1) y軸3
  SVG__LINE(&plt->svg,
            rs.P[5].x,rs.P[5].y,
            rs.P[7].x,rs.P[7].y,
            linestyle);

  SVG_STYLE__SET_001(linestyle,"1.0","#0000FF","4.0",NULL,NULL,NULL,NULL,"none");

  //(-1,-1,-1) - (-1,-1,+1) z軸1
  SVG__LINE(&plt->svg,
            rs.P[0].x,rs.P[0].y,
            rs.P[1].x,rs.P[1].y,
            linestyle);
  //(-1,+1,-1) - (-1,+1,+1) z軸2
  SVG__LINE(&plt->svg,
            rs.P[2].x,rs.P[2].y,
            rs.P[3].x,rs.P[3].y,
            linestyle);
  //(+1,-1,-1) - (+1,-1,+1) z軸3
  SVG__LINE(&plt->svg,
            rs.P[4].x,rs.P[4].y,
            rs.P[5].x,rs.P[5].y,
            linestyle);
  //(+1,+1,-1) - (+1,+1,+1) z軸4
  SVG__LINE(&plt->svg,
            rs.P[6].x,rs.P[6].y,
            rs.P[7].x,rs.P[7].y,
            linestyle);

  SVG_STYLE__SET_001(linestyle,"1.0","#000000","4.0",NULL,NULL,NULL,NULL,"none");
  VECTOR_3D ps1,ps2;


  ps1 = VECTOR_3D__MtoS(VECTOR_3D__INIT(0.0,0.5,0.0),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  ps2 = VECTOR_3D__MtoS(VECTOR_3D__INIT(1.0,0.5,0.0),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  SVG__LINE(&plt->svg,
            ps1.x,ps1.y,
            ps2.x,ps2.y,
            linestyle);

  ps1 = VECTOR_3D__MtoS(VECTOR_3D__INIT(0.0,0.5,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  ps2 = VECTOR_3D__MtoS(VECTOR_3D__INIT(1.0,0.5,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  SVG__LINE(&plt->svg,
            ps1.x,ps1.y,
            ps2.x,ps2.y,
            linestyle);  

  ps1 = VECTOR_3D__MtoS(VECTOR_3D__INIT(0.0,0.5,1.0),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  ps2 = VECTOR_3D__MtoS(VECTOR_3D__INIT(1.0,0.5,1.0),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  SVG__LINE(&plt->svg,
            ps1.x,ps1.y,
            ps2.x,ps2.y,
            linestyle);  

  ps1 = VECTOR_3D__MtoS(VECTOR_3D__INIT(0.0,0.0,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  ps2 = VECTOR_3D__MtoS(VECTOR_3D__INIT(1.0,0.0,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  SVG__LINE(&plt->svg,
            ps1.x,ps1.y,
            ps2.x,ps2.y,
            linestyle);  

  ps1 = VECTOR_3D__MtoS(VECTOR_3D__INIT(0.0,0.5,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  ps2 = VECTOR_3D__MtoS(VECTOR_3D__INIT(1.0,0.5,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  SVG__LINE(&plt->svg,
            ps1.x,ps1.y,
            ps2.x,ps2.y,
            linestyle);  

  ps1 = VECTOR_3D__MtoS(VECTOR_3D__INIT(0.0,1.0,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  ps2 = VECTOR_3D__MtoS(VECTOR_3D__INIT(1.0,1.0,0.5),xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
  SVG__LINE(&plt->svg,
            ps1.x,ps1.y,
            ps2.x,ps2.y,
            linestyle);  

}

#define XNUM (150)
#define YNUM (150)


INT       VECTOR_2D__HITTEST_POINT_TRIANGLE(VECTOR_2D p,VECTOR_2D a,VECTOR_2D b,VECTOR_2D c);

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

void aacontour(SVGPLOT *plt){
  // プロット領域(数学    座標系)の設定
  REAL xmin     = -2.0;
  REAL xmax     =  2.0;
  REAL ymin     = -2.0;
  REAL ymax     =  2.0;
  REAL zmin     = -1.0;
  REAL zmax     =  1.0;
  // プロット領域(ワールド座標系)の設定
  REAL obj_xmin = -1.0;
  REAL obj_xmax = +1.0;
  REAL obj_ymin = -2.0;
  REAL obj_ymax = +2.0;
  REAL obj_zmin = -1.0;
  REAL obj_zmax = +1.0;
  // カメラ位置の設定
  REAL r        = 20.0;
  REAL theta    = 70.0 / 180.0 * M_PI;
  REAL phi      = 30.0 / 180.0 * M_PI;
  // スクリーンの設定
  REAL x0       = plt->Xmin;
  REAL y0       = plt->Ymin;
  REAL width    = plt->Xmax - plt->Xmin;
  REAL height   = plt->Ymax - plt->Ymin;

  REAL x[XNUM];
  REAL y[XNUM];
  REAL z[XNUM][YNUM];
  
  for(int n = 0;n < XNUM;n++){
    x[n] = -2.0 + 4.0 * n / (REAL)XNUM;
  }
  for(int m = 0;m < YNUM;m++){
    y[m] = -2.0 + 4.0 * m / (REAL)YNUM;
  }

  for(int n = 0;n < XNUM;n++){
    for(int m = 0;m < YNUM;m++){
      z[n][m] = exp(-2.0 * (x[n] * x[n] + y[m] * y[m])) * cos(4.0 * M_PI * sqrt(x[n] * x[n] + y[m] * y[m]));
    }
  }

  // ===============================================
  VECTOR_3D p1,p2,p3;
  REAL *cx;//[0,width ]
  REAL *cy;//[0,height]
  INT   cx_num = 2000;
  INT   cy_num = 1000;
  REAL *contour;
  REAL *zbuf;
  
  cx = (REAL*)malloc(sizeof(REAL) * cx_num);
  cy = (REAL*)malloc(sizeof(REAL) * cy_num);
  for(int n = 0;n < cx_num;n++){
    cx[n] = 0.0 + width  * n / (REAL)cx_num;
  }
  for(int m = 0;m < cy_num;m++){
    cy[m] = 0.0 + height * m / (REAL)cy_num;
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
      p1 = VECTOR_3D__INIT(x[n    ],y[m    ],z[n    ][m    ]);
      p2 = VECTOR_3D__INIT(x[n + 1],y[m    ],z[n + 1][m    ]);
      p3 = VECTOR_3D__INIT(x[n    ],y[m + 1],z[n    ][m + 1]);
      p1 = VECTOR_3D__MtoS(p1,xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
      p2 = VECTOR_3D__MtoS(p2,xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
      p3 = VECTOR_3D__MtoS(p3,xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
      p1.x -= x0;
      p1.y -= y0;
      p2.x -= x0;
      p2.y -= y0;
      p3.x -= x0;
      p3.y -= y0;
      FILL(cx,cx_num,cy,cy_num,contour,zbuf,
           p1.x,p1.y,p1.z,
           p2.x,p2.y,p2.z,
           p3.x,p3.y,p3.z,
           z[n][m],z[n + 1][m],z[n][m + 1]);
      p1 = VECTOR_3D__INIT(x[n + 1],y[m    ],z[n + 1][m    ]);
      p2 = VECTOR_3D__INIT(x[n    ],y[m + 1],z[n    ][m + 1]);
      p3 = VECTOR_3D__INIT(x[n + 1],y[m + 1],z[n + 1][m + 1]);
      p1 = VECTOR_3D__MtoS(p1,xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
      p2 = VECTOR_3D__MtoS(p2,xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
      p3 = VECTOR_3D__MtoS(p3,xmin,xmax,ymin,ymax,zmin,zmax,obj_xmin,obj_xmax,obj_ymin,obj_ymax,obj_zmin,obj_zmax,r,theta,phi,x0,y0,width,height);
      p1.x -= x0;
      p1.y -= y0;
      p2.x -= x0;
      p2.y -= y0;
      p3.x -= x0;
      p3.y -= y0;
      FILL(cx,cx_num,cy,cy_num,contour,zbuf,
           p1.x,p1.y,p1.z,
           p2.x,p2.y,p2.z,
           p3.x,p3.y,p3.z,
           z[n + 1][m],z[n][m + 1],z[n + 1][m + 1]);
    }
  }
  
  zmin = fmin(STATS__MIN(contour,cx_num * cy_num,0),
              STATS__MIN(contour,cx_num * cy_num,0));
  zmax = fmax(STATS__MAX(contour,cx_num * cy_num,0),
              STATS__MAX(contour,cx_num * cy_num,0));

  SVGPLOT_PALETTE__Create10(&plt->pal);
  SVGPLOT__SET_RANGE_Z_003(plt,0.0,1.0);  
   
  SVGPLOT__XYZ_CONTOUR(plt,cx,cx_num,cy,cy_num,contour,-1.0,-1.0,0);

  free(cx);
  free(cy);
  free(contour);
  free(zbuf);

}
