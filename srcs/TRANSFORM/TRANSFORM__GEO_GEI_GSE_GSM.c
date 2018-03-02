#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"
#include"IGRF12.h"

//GSE座標系からGSM座標系への変換
void GSE_to_GSM(double *dst_x,  //GSM
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

  ROTATE_X(dst_x,dst_y,dst_z,
	   src_x,src_y,src_z,
	  -atan2(q_y,q_z));
}

//GSM座標系からGSE座標系への変換
void GSM_to_GSE(double *dst_x,  //GSE
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

  ROTATE_X(dst_x,dst_y,dst_z,
	   src_x,src_y,src_z,
	  +atan2(q_y,q_z));
}


//GEO座標系からGSM座標系への変換
void GEO_to_GSM(double *dst_x,  //GSM
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
  
  GEO_to_GSE(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSE_to_GSM( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);  
}

//GSM座標系からGEO座標系への変換
void GSM_to_GEO(double *dst_x,  //GEO
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
 
  double tmp_x,tmp_y,tmp_z;
  
  GSM_to_GSE(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSE_to_GEO( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);  
}

//GEI座標系からGSM座標系への変換
void GEI_to_GSM(double *dst_x,  //GSM
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

  GEI_to_GSE(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSE_to_GSM( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);  
}

//GSM座標系からGEI座標系への変換
void GSM_to_GEI(double *dst_x,  //GEI
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
  
  double tmp_x,tmp_y,tmp_z;

  GSM_to_GSE(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GSE_to_GEI( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);  
}
