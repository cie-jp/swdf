/*****************************************************************
 * 
 * Tsyganenko
 *
 *                           Created  by Mamoru Ota (2017/11/15)
 *
 *****************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"TRANSFORM.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define RE (6371.0e3)

extern void t04_s_(int    *iopt,
		   float   parmod[10],
		   float  *ps,
		   float  *x,
		   float  *y,
		   float  *z,
		   float  *bx,
		   float  *by,
		   float  *bz);

void Tsyganenko_2005_GSM(double *Bx, //GSM Bx[T]
			 double *By, //GSM By[T]
			 double *Bz, //GSM Bz[T]
			 double  x,  //GSM  x[m]
			 double  y,  //GSM  y[m]
			 double  z,  //GSM  z[m]
			 int     year,
			 int     month,
			 int     day,
			 int     hour,
			 int     minute,
			 double  second);

void Tsyganenko_2005(double *brr,
		     double *bth,
		     double *bph,
		     double  r,    
		     double  theta,
		     double  phi,  
		     int     year,
		     int     month,
		     int     day,
		     int     hour,
		     int     minute,
		     double  second){
  double  x_GEO, y_GEO, z_GEO;
  double  x_GSM, y_GSM, z_GSM;
  double Bx_GSM,By_GSM,Bz_GSM;
  double Bx_GEO,By_GEO,Bz_GEO;
  double ux    ,uy    ,uz;

  x_GEO = r * sin(theta) * cos(phi);
  y_GEO = r * sin(theta) * sin(phi);
  z_GEO = r * cos(theta);

  GEO_to_GSM(& x_GSM,& y_GSM,& z_GSM,
	       x_GEO,  y_GEO,  z_GEO,
	     year,month,day,hour,minute,second);

  Tsyganenko_2005_GSM(&Bx_GSM,&By_GSM,&Bz_GSM,x_GSM,y_GSM,z_GSM,year,month,day,hour,minute,second);  

  GSM_to_GEO(&Bx_GEO,&By_GEO,&Bz_GEO,
	      Bx_GSM, By_GSM, Bz_GSM,
	     year,month,day,hour,minute,second);

  ux   = sin(theta) * cos(phi);
  uy   = sin(theta) * sin(phi);
  uz   = cos(theta);
  *brr = Bx_GEO * ux + By_GEO * uy + Bz_GEO * uz;
  ux   = cos(theta) * cos(phi);
  uy   = cos(theta) * sin(phi);
  uz   =-sin(theta);
  *bth = Bx_GEO * ux + By_GEO * uy + Bz_GEO * uz;
  ux   =-sin(phi);
  uy   = cos(phi);
  uz   = 0.0;
  *bph = Bx_GEO * ux + By_GEO * uy + Bz_GEO * uz;
}

void Tsyganenko_2005_GSM(double *Bx, //GSM Bx[T]
			 double *By, //GSM By[T]
			 double *Bz, //GSM Bz[T]
			 double  x,  //GSM  x[m]
			 double  y,  //GSM  y[m]
			 double  z,  //GSM  z[m]
			 int     year,
			 int     month,
			 int     day,
			 int     hour,
			 int     minute,
			 double  second){
  static int    old_year   = -99;
  static int    old_month  = -99;
  static int    old_day    = -99;
  static int    old_hour   = -99;
  static int    old_minute = -99;
  static double old_second = -99;
  
  static int   iopt = -1;
  static float parmod[10];
  static float ps = -25.68 * M_PI / 180.0;//GEODIPOLE TILT ANGLE IN RADIANS [rad]

  float x_RE, y_RE, z_RE;
  float Bx_nT,By_nT,Bz_nT;

  int    doy_ref;

  FILE  *fp;
  char   filename[1024];
  char   buf[4096];
  int    yyyy;
  int    doy;
  int    hh;
  int    mm;
  double Bx_GSM;
  double By_GSM;
  double Bz_GSM;
  double Vx_GSE;
  double Vy_GSE;
  double Vz_GSE;
  double dens;
  double temp;
  double symh;
  int    imfflag;
  int    swflag;
  double tilt;
  double pdyn;
  double W1,W2,W3,W4,W5,W6;
  double diff_min,diff;

  if((old_year == year) && (old_month == month) && (old_day == day) && (old_hour == hour) && (old_minute == minute) && (old_second == second)){
    goto EXIT;
  }
  old_year   =  year;
  old_month  =  month;
  old_day    =  day; 
  old_hour   =  hour;
  old_minute =  minute; 
  old_second =  second;

  doy_ref = DATE_to_DOY(year,month,day);

  sprintf(filename,"/remote/raid1/usr/ota/tsyganenko_2005_parameter/" "%04d_OMNI_5m_with_TS05_variables.dat",year);
  if((fp = fopen(filename,"r")) == NULL){
    fprintf(stderr,"[ERROR TSYGANENKO] NO OMNI DATA 1\n");
    exit(EXIT_FAILURE);
  }
  diff_min  = 24 * 3600.0;
  parmod[0] = 0.0;
  parmod[1] = 0.0;
  parmod[2] = 0.0;
  parmod[3] = 0.0;
  parmod[4] = 0.0;
  parmod[5] = 0.0;
  parmod[6] = 0.0;
  parmod[7] = 0.0;
  parmod[8] = 0.0;
  parmod[9] = 0.0;
  ps        = 0.0;
  while(fgets(buf,sizeof(buf),fp) != NULL){
    sscanf(buf,
	   "%d %d %d %d " 
	   "%lf %lf %lf "
	   "%lf %lf %lf " 
	   "%lf %lf %lf " 
	   "%d %d " 
	   "%lf %lf "
	   "%lf %lf %lf %lf %lf %lf",
	   &yyyy,&doy,&hh,&mm,
	   &Bx_GSM,&By_GSM,&Bz_GSM,
	   &Vx_GSE,&Vy_GSE,&Vz_GSE,
	   &dens,&temp,&symh,
	   &imfflag,&swflag,
	   &tilt,&pdyn,
	   &W1,&W2,&W3,&W4,&W5,&W6);
    if(abs(doy - doy_ref) > 1){
      continue;
    }
    diff = fabs(24 * 3600 * (doy - doy_ref) + 3600 * hh + 60 * mm - (3600 * hour + 60 * minute + second)); 
    if(diff_min <= diff){
      continue;
    }
    diff_min  = diff  ;
    parmod[0] = pdyn  ;//太陽風動圧[nPa]
    parmod[1] = symh  ;//Dst指数[nT]
    parmod[2] = By_GSM;//IMF By [nT]
    parmod[3] = Bz_GSM;//IMF Bz [nT]
    parmod[4] = W1    ;
    parmod[5] = W2    ;
    parmod[6] = W3    ;
    parmod[7] = W4    ;
    parmod[8] = W5    ;
    parmod[9] = W6    ;
    ps        = tilt  ;//[rad]
  }
  fclose(fp);

  if(diff_min == 24 * 3600){
    fprintf(stderr,"[ERROR TSYGANENKO] NO OMNI DATA 2\n");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"[TSYGANENKO MODEL INFORMATION]\n");
  fprintf(stderr,"Epoch                    : %04d-%02d-%02d %02d:%02d:%02d\n",year,month,day,hour,minute,(int)second);
  fprintf(stderr,"Solar Wind Pressure[nPa] : %lf\n",parmod[0]);
  fprintf(stderr,"Dst Index[nT]            : %lf\n",parmod[1]);
  fprintf(stderr,"IMF By (GSM) [nT]        : %lf\n",parmod[2]);
  fprintf(stderr,"IMF Bz (GSM) [nT]        : %lf\n",parmod[3]);
  fprintf(stderr,"W1                       : %lf\n",parmod[4]);
  fprintf(stderr,"W2                       : %lf\n",parmod[5]);
  fprintf(stderr,"W3                       : %lf\n",parmod[6]);
  fprintf(stderr,"W4                       : %lf\n",parmod[7]);
  fprintf(stderr,"W5                       : %lf\n",parmod[8]);
  fprintf(stderr,"W6                       : %lf\n",parmod[9]);
  fprintf(stderr,"Dipole tilt [deg]        : %lf\n",ps * 180.0 / M_PI);
 EXIT:;
  x_RE = x / RE;
  y_RE = y / RE;
  z_RE = z / RE;

  t04_s_(&iopt,parmod,&ps,&x_RE,&y_RE,&z_RE,&Bx_nT,&By_nT,&Bz_nT);

  *Bx = Bx_nT * 1.0e-9;
  *By = By_nT * 1.0e-9;
  *Bz = Bz_nT * 1.0e-9;  
}
