#include"CLDIA.h"
#include"TRANSFORM/TRANSFORM.h"
#include"TRANSFORM/IGRF12.h"

using namespace std;
using namespace CLDIA;

int main(int argc,char *argv[]){
  double dst_x;
  double dst_y;
  double dst_z;
  double src_x  = 1.348;//3.549;// 3.811;
  double src_y  = 2.386;//-2.735;//-2.735;
  double src_z  = 1.470;//-1.394;// 1.085e-01;
  int    year   = 2017;
  int    month  =    9;
  int    day    =    3;
  int    hour   =   20;
  int    minute =   54;
  double second =  0.0;
  IGRF12 igrf;

  IGRF12__Init  (&igrf);
  IGRF12__Update(&igrf,
                 year,
                 month,
                 day,
                 hour,
                 minute,
                 second);
  //GEO_to_GEI(
  //GEO_to_GSE(
  //GEO_to_GSM(
  //GSM_to_GEO(
  SM_to_GEO(
             &dst_x,
             &dst_y,
             &dst_z,
             src_x,
             src_y,
             src_z,
             year,
             month,
             day,
             hour,
             minute,
             second);
  double r     = sqrt(dst_x * dst_x + dst_y * dst_y + dst_z * dst_z) * 6371.2e3;
  double theta = atan2(sqrt(dst_x * dst_x + dst_y * dst_y),dst_z);
  double phi   = atan2(dst_y,dst_x);
  IGRF12__Calc(&igrf,
               r,theta,phi,
               year,
               month,
               day,
               hour,
               minute,
               second);

  cerr << src_x << endl;
  cerr << src_y << endl;
  cerr << src_z << endl;
  cerr << endl;
  fprintf(stderr,"%10.7f\n%10.7f\n%10.7f\n",dst_x,dst_y,dst_z);
  IGRF12__Show(&igrf);

  double bx = igrf.brr * sin(theta) * cos(phi) + igrf.bth *  cos(theta) * cos(phi) + igrf.bph * -sin(phi);
  double by = igrf.brr * sin(theta) * sin(phi) + igrf.bth *  cos(theta) * sin(phi) + igrf.bph *  cos(phi);
  double bz = igrf.brr * cos(theta)            + igrf.bth * -sin(theta)            + igrf.bph *       0.0;
  cerr << bx << endl;
  cerr << by << endl;
  cerr << bz << endl;
  cerr << sqrt(bx * bx + by * by + bz * bz) << endl;
  
  //geopack_recalc, 2000, 1, 1, 12, 30, 0.0, /date
  //x0 = 5
  //y0 = 4
  //z0 = 3
  //geopack_conv_coord, x0, y0, z0, x1, y1, z1, /FROM_GEO, /TO_GEI
  //geopack_conv_coord, x0, y0, z0, x1, y1, z1, /FROM_GEO, /TO_GSE
  //geopack_conv_coord, x0, y0, z0, x1, y1, z1, /FROM_GEO, /TO_GSM
  //geopack_conv_coord, x0, y0, z0, x1, y1, z1, /FROM_GEO, /TO_SM

  //x1,y1,z1
  return 0;
}
//geopack_recalc, 2017,1,16,0,0,0,/date
//geopack_igrf_gsm,3.811,-2.735,1.085e-01,bx,by,bz
//bx,by,bz
//blocal 1.075e+02, -1.664e+02, 2.821e+02

/*
IDL> geopack_recalc, 2017,1,16,0,0,0,/date 
IDL> geopack_igrf_gsm,3.811,-2.735,1.085e-01,bx,by,bz
IDL> bx,by,bz
       107.55835656310990
      -166.49284507120421
       282.22917389390972
IDL> GEOPACK_CONV_COORD,bx,by,bz,bx1,by1,bz1,/FROM_GSM,/TO_GEO
IDL> bx1,by1,bz1
      -214.80763884803264
       105.61101310794535
       248.28605745419219
*/
//12541:[] = 2017-09-03T20:54:00.000000000
//SM : 1.348, 2.386, 1.470
//x0=1.348
//y0=2.386
//z0=1.470
//geopack_recalc, 2017,9,3,20,54,0,/date
//GEOPACK_CONV_COORD,x0,y0,z0,x1,y1,z1,/FROM_SM,/TO_GSM
//geopack_igrf_gsm,x1,y1,z1,bx,by,bz
//bx,by,bz
//1.236e+03 nT
