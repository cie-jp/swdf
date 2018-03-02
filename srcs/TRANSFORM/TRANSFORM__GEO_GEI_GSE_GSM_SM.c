#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"
#include"IGRF12.h"

//GSM座標系から SM座標系への変換
void GSM_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)

  double p_x,p_y,p_z;
  double q_x,q_y,q_z;

  if(!IS_INIT_GLOBAL_IGRF12){IGRF12__Init(&GLOBAL_IGRF12);IS_INIT_GLOBAL_IGRF12 = 1;}
  IGRF12__Update(&GLOBAL_IGRF12,year,month,day,hour,minute,second);

  p_x = sin(GLOBAL_IGRF12.dipole_lat) * cos(GLOBAL_IGRF12.dipole_lon);
  p_y = sin(GLOBAL_IGRF12.dipole_lat) * sin(GLOBAL_IGRF12.dipole_lon);
  p_z = cos(GLOBAL_IGRF12.dipole_lat);

  GEO_to_GSE(&q_x,&q_y,&q_z,
	      p_x, p_y, p_z,
	      year,month,day,hour,minute,second);

  ROTATE_Y(dst_x,dst_y,dst_z,
	   src_x,src_y,src_z,
	  -atan2(q_x,sqrt(q_y * q_y + q_z * q_z)));  
}

// SM座標系からGSM座標系への変換
void  SM_to_GSM(double *dst_x,  //GSM
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		

  double p_x,p_y,p_z;
  double q_x,q_y,q_z;

  if(!IS_INIT_GLOBAL_IGRF12){IGRF12__Init(&GLOBAL_IGRF12);IS_INIT_GLOBAL_IGRF12 = 1;}
  IGRF12__Update(&GLOBAL_IGRF12,year,month,day,hour,minute,second);

  p_x = sin(GLOBAL_IGRF12.dipole_lat) * cos(GLOBAL_IGRF12.dipole_lon);
  p_y = sin(GLOBAL_IGRF12.dipole_lat) * sin(GLOBAL_IGRF12.dipole_lon);
  p_z = cos(GLOBAL_IGRF12.dipole_lat);

  GEO_to_GSE(&q_x,&q_y,&q_z,
	      p_x, p_y, p_z,
	      year,month,day,hour,minute,second);

  ROTATE_Y(dst_x,dst_y,dst_z,
	   src_x,src_y,src_z,
	  +atan2(q_x,sqrt(q_y * q_y + q_z * q_z)));  
}

//GEO座標系から SM座標系への変換
void GEO_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEO
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)
  
  double tmp_x,tmp_y,tmp_z;

  GEO_to_GSM(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSM_to_SM ( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);    
}

// SM座標系からGEO座標系への変換
void  SM_to_GEO(double *dst_x,  //GEO
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
  
  double tmp_x,tmp_y,tmp_z;

   SM_to_GSM(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSM_to_GEO( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);      
}

//GEI座標系から SM座標系への変換
void GEI_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GEI
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)
  
  double tmp_x,tmp_y,tmp_z;

  GEI_to_GSM(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSM_to_SM ( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);    
}

// SM座標系からGEI座標系への変換
void  SM_to_GEI(double *dst_x,  //GEI
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
  
  double tmp_x,tmp_y,tmp_z;

   SM_to_GSM(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSM_to_GEI( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);      
}

//GSE座標系から SM座標系への変換
void GSE_to_SM (double *dst_x,  // SM
		double *dst_y,
		double *dst_z,
		double  src_x,  //GSE
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)
  
  double tmp_x,tmp_y,tmp_z;

  GSE_to_GSM(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSM_to_SM ( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);    
}

// SM座標系からGSE座標系への変換
void  SM_to_GSE(double *dst_x,  //GSE
		double *dst_y,
		double *dst_z,
		double  src_x,  // SM
		double  src_y,
		double  src_z,
		int     year,   //西暦年(8 ~ 2800)
		int     month,  //月    (1 ~ 12)
		int     day,    //日    (1 ~ 28,29,30,31)
		int     hour,   //時    (0 ~ 23)
		int     minute, //分    (0 ~ 59)
		double  second){//秒    (0 ~ 59.999999)		
  
  double tmp_x,tmp_y,tmp_z;

   SM_to_GSM(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSM_to_GSE( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);      
}
