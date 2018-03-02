/*****************************************************************
 * 
 * 国際標準地球磁場IGRF12
 *
 *                           Created  by Mamoru Ota (2017/07/18)
 *
 *****************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"IGRF12.h"
#include"IGRF12_COEF.h"

#include"TRANSFORM.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

IGRF12         GLOBAL_IGRF12    ;
int    IS_INIT_GLOBAL_IGRF12 = 0;

void IGRF12__Update__(IGRF12 *igrf,
		      double  year);

void IGRF12__Calc__  (IGRF12 *igrf,
		      double  r,    //(in)  地心距離   r     [m]
		      double  theta,//(in)  地心余緯度 theta [rad]
		      double  phi,  //(in)  地理経度   phi   [rad] 東経 +
		      double  year);//(in)  計算年 (西暦)

void IGRF12__Init(IGRF12 *igrf){
  igrf->prev_year  = 1899.9;
  igrf->prev_r     =    0.0;
  igrf->prev_theta =    0.0;
  igrf->prev_phi   =    0.0;
  
  igrf->b          = 0.0;
  igrf->brr        = 0.0;
  igrf->bth        = 0.0;
  igrf->bph        = 0.0;
  igrf->db_drr     = 0.0;
  igrf->db_dth     = 0.0;
  igrf->db_dph     = 0.0;
  igrf->dbrr_drr   = 0.0;
  igrf->dbth_drr   = 0.0;
  igrf->dbph_drr   = 0.0;
  igrf->dbrr_dth   = 0.0;
  igrf->dbth_dth   = 0.0;
  igrf->dbph_dth   = 0.0;
  igrf->dbrr_dph   = 0.0;
  igrf->dbth_dph   = 0.0;
  igrf->dbph_dph   = 0.0;
  igrf->yrr        = 0.0;
  igrf->yth        = 0.0;
  igrf->yph        = 0.0;
  igrf->dyrr_drr   = 0.0;
  igrf->dyth_drr   = 0.0;
  igrf->dyph_drr   = 0.0;
  igrf->dyrr_dth   = 0.0;
  igrf->dyth_dth   = 0.0;
  igrf->dyph_dth   = 0.0;
  igrf->dyrr_dph   = 0.0;
  igrf->dyth_dph   = 0.0;
  igrf->dyph_dph   = 0.0;  
  igrf->dipole_M   = 0.0;
  igrf->dipole_Mx  = 0.0;
  igrf->dipole_My  = 0.0;
  igrf->dipole_Mz  = 0.0;
  igrf->dipole_lat = 0.0;
  igrf->dipole_lon = 0.0;
}

void IGRF12__Update__(IGRF12 *igrf,
		      double  year){
  // ***************************************************************
  // year  の更新時の処理
  // ***************************************************************
  if(igrf->prev_year != year){
    
    const float *g ,*dg;
    const float *h ,*dh;
    int          y0;
    double       dy;
    long double  sf;
    long double  inv_Mx,inv_My,inv_Mz;

    if((year < 1900) || (2020 < year)){
      fprintf(stderr,"IGRF12 : ERROR [(year < 1900) || (2020 < year)]\n");
      exit(EXIT_FAILURE);
    }
      
    y0 = (2015 <= year) ? 2015 : 
	 (2010 <= year) ? 2010 : 
         (2005 <= year) ? 2005 : 
         (2000 <= year) ? 2000 : 
         (1995 <= year) ? 1995 : 
         (1990 <= year) ? 1990 : 
         (1985 <= year) ? 1985 : 
         (1980 <= year) ? 1980 : 
         (1975 <= year) ? 1975 : 
         (1970 <= year) ? 1970 : 
         (1965 <= year) ? 1965 : 
         (1960 <= year) ? 1960 : 
         (1955 <= year) ? 1955 : 
         (1950 <= year) ? 1950 : 
         (1945 <= year) ? 1945 :
         (1940 <= year) ? 1940 : 
         (1935 <= year) ? 1935 :
         (1930 <= year) ? 1930 : 
         (1925 <= year) ? 1925 : 
         (1920 <= year) ? 1920 : 
         (1915 <= year) ? 1915 : 
         (1910 <= year) ? 1910 : 
         (1905 <= year) ? 1905 : 1900;
    dy = year - y0;    

    g  = (2015 <= year) ? &IGRF12__2015_0_g [0][0] :
         (2010 <= year) ? &IGRF12__2010_0_g [0][0] :
         (2005 <= year) ? &IGRF12__2005_0_g [0][0] :
         (2000 <= year) ? &IGRF12__2000_0_g [0][0] :
         (1995 <= year) ? &IGRF12__1995_0_g [0][0] :
         (1990 <= year) ? &IGRF12__1990_0_g [0][0] :
         (1985 <= year) ? &IGRF12__1985_0_g [0][0] :
         (1980 <= year) ? &IGRF12__1980_0_g [0][0] :
         (1975 <= year) ? &IGRF12__1975_0_g [0][0] :
         (1970 <= year) ? &IGRF12__1970_0_g [0][0] :
         (1965 <= year) ? &IGRF12__1965_0_g [0][0] :
         (1960 <= year) ? &IGRF12__1960_0_g [0][0] :
         (1955 <= year) ? &IGRF12__1955_0_g [0][0] :
         (1950 <= year) ? &IGRF12__1950_0_g [0][0] :
         (1945 <= year) ? &IGRF12__1945_0_g [0][0] :
         (1940 <= year) ? &IGRF12__1940_0_g [0][0] :
         (1935 <= year) ? &IGRF12__1935_0_g [0][0] :
         (1930 <= year) ? &IGRF12__1930_0_g [0][0] :
         (1925 <= year) ? &IGRF12__1925_0_g [0][0] :
         (1920 <= year) ? &IGRF12__1920_0_g [0][0] :
         (1915 <= year) ? &IGRF12__1915_0_g [0][0] :
         (1910 <= year) ? &IGRF12__1910_0_g [0][0] :
         (1905 <= year) ? &IGRF12__1905_0_g [0][0] : &IGRF12__1900_0_g [0][0];

    h  = (2015 <= year) ? &IGRF12__2015_0_h [0][0] :
         (2010 <= year) ? &IGRF12__2010_0_h [0][0] :
         (2005 <= year) ? &IGRF12__2005_0_h [0][0] :
         (2000 <= year) ? &IGRF12__2000_0_h [0][0] :
         (1995 <= year) ? &IGRF12__1995_0_h [0][0] :
         (1990 <= year) ? &IGRF12__1990_0_h [0][0] :
         (1985 <= year) ? &IGRF12__1985_0_h [0][0] :
         (1980 <= year) ? &IGRF12__1980_0_h [0][0] :
         (1975 <= year) ? &IGRF12__1975_0_h [0][0] :
         (1970 <= year) ? &IGRF12__1970_0_h [0][0] :
         (1965 <= year) ? &IGRF12__1965_0_h [0][0] :
         (1960 <= year) ? &IGRF12__1960_0_h [0][0] :
         (1955 <= year) ? &IGRF12__1955_0_h [0][0] :
         (1950 <= year) ? &IGRF12__1950_0_h [0][0] :
         (1945 <= year) ? &IGRF12__1945_0_h [0][0] :
         (1940 <= year) ? &IGRF12__1940_0_h [0][0] :
         (1935 <= year) ? &IGRF12__1935_0_h [0][0] :
         (1930 <= year) ? &IGRF12__1930_0_h [0][0] :
         (1925 <= year) ? &IGRF12__1925_0_h [0][0] :
         (1920 <= year) ? &IGRF12__1920_0_h [0][0] :
         (1915 <= year) ? &IGRF12__1915_0_h [0][0] :
         (1910 <= year) ? &IGRF12__1910_0_h [0][0] :
         (1905 <= year) ? &IGRF12__1905_0_h [0][0] : &IGRF12__1900_0_h [0][0];

    dg = (2015 <= year) ? &IGRF12__2015_0_dg[0][0] :
         (2010 <= year) ? &IGRF12__2010_0_dg[0][0] :
         (2005 <= year) ? &IGRF12__2005_0_dg[0][0] :
         (2000 <= year) ? &IGRF12__2000_0_dg[0][0] :
         (1995 <= year) ? &IGRF12__1995_0_dg[0][0] :
         (1990 <= year) ? &IGRF12__1990_0_dg[0][0] :
         (1985 <= year) ? &IGRF12__1985_0_dg[0][0] :
         (1980 <= year) ? &IGRF12__1980_0_dg[0][0] :
         (1975 <= year) ? &IGRF12__1975_0_dg[0][0] :
         (1970 <= year) ? &IGRF12__1970_0_dg[0][0] :
         (1965 <= year) ? &IGRF12__1965_0_dg[0][0] :
         (1960 <= year) ? &IGRF12__1960_0_dg[0][0] :
         (1955 <= year) ? &IGRF12__1955_0_dg[0][0] :
         (1950 <= year) ? &IGRF12__1950_0_dg[0][0] :
         (1945 <= year) ? &IGRF12__1945_0_dg[0][0] :
         (1940 <= year) ? &IGRF12__1940_0_dg[0][0] :
         (1935 <= year) ? &IGRF12__1935_0_dg[0][0] :
         (1930 <= year) ? &IGRF12__1930_0_dg[0][0] :
         (1925 <= year) ? &IGRF12__1925_0_dg[0][0] :
         (1920 <= year) ? &IGRF12__1920_0_dg[0][0] :
         (1915 <= year) ? &IGRF12__1915_0_dg[0][0] :
         (1910 <= year) ? &IGRF12__1910_0_dg[0][0] :
         (1905 <= year) ? &IGRF12__1905_0_dg[0][0] : &IGRF12__1900_0_dg[0][0];

    dh = (2015 <= year) ? &IGRF12__2015_0_dh[0][0] :
         (2010 <= year) ? &IGRF12__2010_0_dh[0][0] :
         (2005 <= year) ? &IGRF12__2005_0_dh[0][0] :
         (2000 <= year) ? &IGRF12__2000_0_dh[0][0] :
         (1995 <= year) ? &IGRF12__1995_0_dh[0][0] :
         (1990 <= year) ? &IGRF12__1990_0_dh[0][0] :
         (1985 <= year) ? &IGRF12__1985_0_dh[0][0] :
         (1980 <= year) ? &IGRF12__1980_0_dh[0][0] :
         (1975 <= year) ? &IGRF12__1975_0_dh[0][0] :
         (1970 <= year) ? &IGRF12__1970_0_dh[0][0] :
         (1965 <= year) ? &IGRF12__1965_0_dh[0][0] :
         (1960 <= year) ? &IGRF12__1960_0_dh[0][0] :
         (1955 <= year) ? &IGRF12__1955_0_dh[0][0] :
         (1950 <= year) ? &IGRF12__1950_0_dh[0][0] :
         (1945 <= year) ? &IGRF12__1945_0_dh[0][0] :
         (1940 <= year) ? &IGRF12__1940_0_dh[0][0] :
         (1935 <= year) ? &IGRF12__1935_0_dh[0][0] :
         (1930 <= year) ? &IGRF12__1930_0_dh[0][0] :
         (1925 <= year) ? &IGRF12__1925_0_dh[0][0] :
         (1920 <= year) ? &IGRF12__1920_0_dh[0][0] :
         (1915 <= year) ? &IGRF12__1915_0_dh[0][0] :
         (1910 <= year) ? &IGRF12__1910_0_dh[0][0] :
         (1905 <= year) ? &IGRF12__1905_0_dh[0][0] : &IGRF12__1900_0_dh[0][0];
   
    for(int n = 0;n < 14;n++){
      for(int m = 0;m < 14;m++){
	igrf->G[n][m] = (g[14 * n + m] + dg[14 * n + m] * dy) * 1e-9;
	igrf->H[n][m] = (h[14 * n + m] + dh[14 * n + m] * dy) * 1e-9;
      }
    }
    
    for(int n = 0;n < 14;n++){
      sf = sqrtl(2.0);
      for(int m = 1;m < 14;m++){
	sf /= sqrtl((long double)((n + m) * (n - m + 1)));
	igrf->G[n][m] *= sf;
	igrf->H[n][m] *= sf;
      }
    }    

    inv_Mx = -igrf->G[1][1];
    inv_My = -igrf->H[1][1];
    inv_Mz = -igrf->G[1][0];

    igrf->dipole_lat = atan2l(sqrtl(inv_Mx * inv_Mx + inv_My * inv_My),inv_Mz);
    igrf->dipole_lon = atan2l(inv_My,inv_Mx);
    
  }  
}

void IGRF12__Update(IGRF12 *igrf,
		    int     year,
		    int     month,
		    int     day,
		    int     hour,
		    int     minute,
		    double  second){
  int    total_days = (year == 1582) ? 355 : (IS_LEAP_YEAR(year) ? 366 : 365);
  double dt         = (DATE_to_DOY(year,month,day) - 1) + (3600.0 * hour + 60.0 * minute + second) / 86400.0;
  double y          =  year + dt / (double)total_days;
  
  IGRF12__Update__(igrf,y);
}

void IGRF12__Calc__(IGRF12 *igrf,
		    double  r,    //(in)  地心距離   r     [m]
		    double  theta,//(in)  地心余緯度 theta [rad]
		    double  phi,  //(in)  地理経度   phi   [rad] 東経 +
		    double  year){//(in)  計算年 (西暦)
  IGRF12__Update__(igrf,year);
  // ***************************************************************
  // r     の更新時の処理
  // ***************************************************************
  const double a0 = 6371.2e3;

  if(igrf->prev_r != r){
    // a_r[n] = (基準球面の半径 / r)^{2 + n}を計算する    
    long double ratio;
    ratio  = a0  / r; 
    igrf->a_r[0] = ratio * ratio;
    for(int n = 1;n < 14;n++){
      igrf->a_r[n] = igrf->a_r[n - 1] * ratio;
    }
  }
  // ***************************************************************
  // theta の更新時の処理
  // ***************************************************************
  if(igrf->prev_theta != theta){
    
    igrf->cos_theta = cosl(theta);
    igrf->sin_theta = sinl(theta);
    // ルジャンドル陪関数を計算する      
    igrf->P[0][0] =  1.0; 
    igrf->P[1][0] =  igrf->cos_theta; 
    igrf->P[1][1] =  igrf->sin_theta;
    for(int n = 2;n < 14;n++){
      igrf->P[n][0] = ((2 * n - 1) * igrf->cos_theta * igrf->P[n - 1][0] - (n - 1) * igrf->P[n - 2][0]) / (long double)n;
      for(int m = 1;m < n;m++){
	if(igrf->sin_theta > 0.175){
	  igrf->P[n][m] = ((n + m - 1) * igrf->P[n - 1][m - 1] - (n - m + 1) * igrf->cos_theta * igrf->P[n][m - 1]) / igrf->sin_theta;
	}else{
	  igrf->P[n][m] = (              igrf->P[n - 1][m    ] + (n - m + 1) * igrf->sin_theta * igrf->P[n][m - 1]) / igrf->cos_theta;
	}
      }
      igrf->P[n][n] = (2 * n - 1) * igrf->sin_theta * igrf->P[n - 1][n - 1];
    }
    igrf->Q[0][0] =  0.0;
    igrf->Q[1][0] = -igrf->sin_theta;
    igrf->Q[1][1] =  igrf->cos_theta;
    for(int n = 2;n < 14;n++){
      igrf->Q[n][0] = -igrf->P[n][1];
      for(int m = 1;m < n;m++){
	igrf->Q[n][m] = ((n + m) * (n - m + 1) * igrf->P[n][m - 1] - igrf->P[n][m + 1]) / 2.0;
      }
      igrf->Q[n][n] = (2 * n - 1) * (igrf->cos_theta * igrf->P[n - 1][n - 1] + igrf->sin_theta * igrf->Q[n - 1][n - 1]);
    }
    igrf->R[0][0] =  0.0;
    igrf->R[1][0] = -igrf->cos_theta;
    igrf->R[1][1] = -igrf->sin_theta;
    for(int n = 2;n < 14;n++){
      igrf->R[n][0] = -igrf->Q[n][1];
      for(int m = 1;m < n;m++){
	igrf->R[n][m] = ((n + m) * (n - m + 1) * igrf->Q[n][m - 1] - igrf->Q[n][m + 1]) / 2.0;
      }
      igrf->R[n][n] = (2 * n - 1) * (2.0 * igrf->cos_theta * igrf->Q[n - 1][n - 1] + igrf->sin_theta * (igrf->R[n - 1][n - 1] - igrf->P[n - 1][n - 1]));
    }
  }
  // ***************************************************************
  // phi   の更新時の処理
  // ***************************************************************
  if(igrf->prev_phi != phi){
    
    // cos_phi[m] = cos(m * phi)
    // sin_phi[m] = sin(m * phi) を計算する
    for(int m = 0;m < 14;m++){      
      igrf->cos_phi[m] = cosl((long double)m * phi);
      igrf->sin_phi[m] = sinl((long double)m * phi);
    }
    
  }
  
  // ***************************************************************
  // 磁場の計算
  // ***************************************************************
  long double tmp_brr;
  long double tmp_bth;
  long double tmp_bph;
  long double tmp_dbrr_dth;
  long double tmp_dbth_dth;
  long double tmp_dbph_dth;
  long double tmp_dbrr_dph;
  long double tmp_dbth_dph;
  long double tmp_dbph_dph;
  long double GcHs;
  long double GsHc;
  long double a_r0;
  long double a_r1;

  igrf->brr        = 0.0;
  igrf->bth        = 0.0;
  igrf->bph        = 0.0;
  igrf->dbrr_drr   = 0.0;
  igrf->dbth_drr   = 0.0;
  igrf->dbph_drr   = 0.0;
  igrf->dbrr_dth   = 0.0;
  igrf->dbth_dth   = 0.0;
  igrf->dbph_dth   = 0.0;
  igrf->dbrr_dph   = 0.0;
  igrf->dbth_dph   = 0.0;
  igrf->dbph_dph   = 0.0;
  for(int n = 1;n < 14;n++){
    tmp_brr      = 0.0;
    tmp_bth      = 0.0;
    tmp_bph      = 0.0; 
    tmp_dbrr_dth = 0.0;
    tmp_dbth_dth = 0.0;
    tmp_dbph_dth = 0.0; 
    tmp_dbrr_dph = 0.0;
    tmp_dbth_dph = 0.0;
    tmp_dbph_dph = 0.0; 
    for(int m = 0;m <= n;m++){	
      GcHs = igrf->G[n][m] * igrf->cos_phi[m] + igrf->H[n][m] * igrf->sin_phi[m];
      GsHc = igrf->G[n][m] * igrf->sin_phi[m] - igrf->H[n][m] * igrf->cos_phi[m];
      tmp_brr      +=     GcHs * igrf->P[n][m];
      tmp_bth      +=     GcHs * igrf->Q[n][m];
      tmp_bph      += m * GsHc * igrf->P[n][m];
      tmp_dbrr_dth +=     GcHs * igrf->Q[n][m];
      tmp_dbth_dth +=     GcHs * igrf->R[n][m];
      tmp_dbph_dth += m * GsHc *(igrf->Q[n][m] * igrf->sin_theta - igrf->P[n][m] * igrf->cos_theta);
      tmp_dbrr_dph +=     GsHc * igrf->P[n][m] * -m;
      tmp_dbth_dph +=     GsHc * igrf->Q[n][m] * -m;
      tmp_dbph_dph += m * GcHs * igrf->P[n][m] *  m;
    }
    a_r0            = igrf->a_r[n]       ;
    a_r1            = a_r0 * (n + 1)     ;
    igrf->brr      += a_r1 * tmp_brr     ;
    igrf->bth      += a_r0 * tmp_bth     ;
    igrf->bph      += a_r0 * tmp_bph     ;
    igrf->dbrr_drr += a_r1 * tmp_brr     * (n + 2);
    igrf->dbth_drr += a_r0 * tmp_bth     * (n + 2);
    igrf->dbph_drr += a_r0 * tmp_bph     * (n + 2);      
    igrf->dbrr_dth += a_r1 * tmp_dbrr_dth;
    igrf->dbth_dth += a_r0 * tmp_dbth_dth;
    igrf->dbph_dth += a_r0 * tmp_dbph_dth;
    igrf->dbrr_dph += a_r1 * tmp_dbrr_dph;
    igrf->dbth_dph += a_r0 * tmp_dbth_dph;
    igrf->dbph_dph += a_r0 * tmp_dbph_dph;
  }
  igrf->bth       = -igrf->bth;
  igrf->bph      /=  igrf->sin_theta;
  igrf->dbrr_drr /=              -r;    
  igrf->dbth_drr /=               r;
  igrf->dbph_drr /=  igrf->sin_theta * -r;
  igrf->dbth_dth  = -igrf->dbth_dth;
  igrf->dbph_dth /=  igrf->sin_theta * igrf->sin_theta;
  igrf->dbth_dph  = -igrf->dbth_dph;
  igrf->dbph_dph /=  igrf->sin_theta;
  
  igrf->b         = sqrt(igrf->brr * igrf->brr + igrf->bth * igrf->bth + igrf->bph * igrf->bph);
  
  igrf->yrr       = igrf->brr / igrf->b;
  igrf->yth       = igrf->bth / igrf->b;
  igrf->yph       = igrf->bph / igrf->b;
  
  igrf->db_drr    = igrf->yrr * igrf->dbrr_drr + igrf->yth * igrf->dbth_drr + igrf->yph * igrf->dbph_drr;
  igrf->db_dth    = igrf->yrr * igrf->dbrr_dth + igrf->yth * igrf->dbth_dth + igrf->yph * igrf->dbph_dth;
  igrf->db_dph    = igrf->yrr * igrf->dbrr_dph + igrf->yth * igrf->dbth_dph + igrf->yph * igrf->dbph_dph;
  
  igrf->dyrr_drr  = (igrf->dbrr_drr - igrf->yrr * igrf->db_drr) / igrf->b;
  igrf->dyth_drr  = (igrf->dbth_drr - igrf->yth * igrf->db_drr) / igrf->b;
  igrf->dyph_drr  = (igrf->dbph_drr - igrf->yph * igrf->db_drr) / igrf->b;
  
  igrf->dyrr_dth  = (igrf->dbrr_dth - igrf->yrr * igrf->db_dth) / igrf->b;
  igrf->dyth_dth  = (igrf->dbth_dth - igrf->yth * igrf->db_dth) / igrf->b;
  igrf->dyph_dth  = (igrf->dbph_dth - igrf->yph * igrf->db_dth) / igrf->b;
  
  igrf->dyrr_dph  = (igrf->dbrr_dph - igrf->yrr * igrf->db_dph) / igrf->b;
  igrf->dyth_dph  = (igrf->dbth_dph - igrf->yth * igrf->db_dph) / igrf->b;
  igrf->dyph_dph  = (igrf->dbph_dph - igrf->yph * igrf->db_dph) / igrf->b;

  igrf->dipole_Mx = igrf->G[1][1] * (powl(a0,3.0) / 1e-7);
  igrf->dipole_My = igrf->H[1][1] * (powl(a0,3.0) / 1e-7);
  igrf->dipole_Mz = igrf->G[1][0] * (powl(a0,3.0) / 1e-7);
  igrf->dipole_M  = sqrtl(igrf->dipole_Mx * igrf->dipole_Mx + igrf->dipole_My * igrf->dipole_My + igrf->dipole_Mz * igrf->dipole_Mz);
  
  // ***************************************************************
  // パラメータの保存
  // ***************************************************************
  igrf->prev_year  = year;
  igrf->prev_r     = r;
  igrf->prev_theta = theta;
  igrf->prev_phi   = phi;
}

void IGRF12__Calc  (IGRF12 *igrf,
		    double  r,     //(in)  地心距離   r     [m]
		    double  theta, //(in)  地心余緯度 theta [rad]
		    double  phi,   //(in)  地理経度   phi   [rad] 東経 +
		    int     year,  //(in)  計算年 (西暦)
		    int     month,
		    int     day,
		    int     hour,
		    int     minute,
		    double  second){
  int    total_days = (year == 1582) ? 355 : (IS_LEAP_YEAR(year) ? 366 : 365);
  double dt         = (DATE_to_DOY(year,month,day) - 1) + (3600.0 * hour + 60.0 * minute + second) / 86400.0;
  double y          =  year + dt / (double)total_days;
  
  IGRF12__Calc__(igrf,r,theta,phi,y);
}

void IGRF12__Show(IGRF12 *igrf){
  printf("=============================================================\n");
  printf(" IGRF12                                                      \n");
  printf("=============================================================\n");
  printf("year       : %20.1f          \n",igrf->prev_year                );
  printf("r          : %20.5f  [km]    \n",igrf->prev_r     /       1000.0);
  printf("theta      : %20.5f  [deg]   \n",igrf->prev_theta / M_PI * 180.0);
  printf("phi        : %20.5f  [deg]   \n",igrf->prev_phi   / M_PI * 180.0);
  printf("b          : %20Le  [T]      \n",igrf->b         );
  printf("brr        : %20Le  [T]      \n",igrf->brr       );
  printf("bth        : %20Le  [T]      \n",igrf->bth       );
  printf("bph        : %20Le  [T]      \n",igrf->bph       );
  printf("db_drr     : %20Le  [T/m]    \n",igrf->db_drr    );
  printf("db_dth     : %20Le  [T/rad]  \n",igrf->db_dth    );
  printf("db_dph     : %20Le  [T/rad]  \n",igrf->db_dph    );
  printf("dbrr_drr   : %20Le  [T/m]    \n",igrf->dbrr_drr  );
  printf("dbth_drr   : %20Le  [T/m]    \n",igrf->dbth_drr  );
  printf("dbph_drr   : %20Le  [T/m]    \n",igrf->dbph_drr  );
  printf("dbrr_dth   : %20Le  [T/rad]  \n",igrf->dbrr_dth  );
  printf("dbth_dth   : %20Le  [T/rad]  \n",igrf->dbth_dth  );
  printf("dbph_dth   : %20Le  [T/rad]  \n",igrf->dbph_dth  );
  printf("dbrr_dph   : %20Le  [T/rad]  \n",igrf->dbrr_dph  );
  printf("dbth_dph   : %20Le  [T/rad]  \n",igrf->dbth_dph  );
  printf("dbph_dph   : %20Le  [T/rad]  \n",igrf->dbph_dph  );
  printf("yrr        : %20Le           \n",igrf->yrr       );
  printf("yth        : %20Le           \n",igrf->yth       );
  printf("yph        : %20Le           \n",igrf->yph       );
  printf("dyrr_drr   : %20Le  [1/m]    \n",igrf->dyrr_drr  );
  printf("dyth_drr   : %20Le  [1/m]    \n",igrf->dyth_drr  );
  printf("dyph_drr   : %20Le  [1/m]    \n",igrf->dyph_drr  );
  printf("dyrr_dth   : %20Le  [1/rad]  \n",igrf->dyrr_dth  );
  printf("dyth_dth   : %20Le  [1/rad]  \n",igrf->dyth_dth  );
  printf("dyph_dth   : %20Le  [1/rad]  \n",igrf->dyph_dth  );
  printf("dyrr_dph   : %20Le  [1/rad]  \n",igrf->dyrr_dph  );
  printf("dyth_dph   : %20Le  [1/rad]  \n",igrf->dyth_dph  );
  printf("dyph_dph   : %20Le  [1/rad]  \n",igrf->dyph_dph  );
  printf("dipole_M   : %20Le  [A m^2]  \n",igrf->dipole_M  );
  printf("dipole_Mx  : %20Le  [A m^2]  \n",igrf->dipole_Mx );
  printf("dipole_My  : %20Le  [A m^2]  \n",igrf->dipole_My );
  printf("dipole_Mz  : %20Le  [A m^2]  \n",igrf->dipole_Mz );
  printf("dipole_lat : %20Le  [deg]    \n",igrf->dipole_lat * 180.0 / M_PI);
  printf("dipole_lon : %20Le  [deg]    \n",igrf->dipole_lon * 180.0 / M_PI);
}

