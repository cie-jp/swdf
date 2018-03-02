#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

//GEI座標系からGSE座標系への変換
void GEI_to_GSE(double *dst_x,  //GSE
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

  ROTATE_X(&tmp_x,&tmp_y,&tmp_z,
	    src_x, src_y, src_z,
	   +OBLQ(year,month,day,hour,minute,second));
  ROTATE_Z( dst_x, dst_y, dst_z,
	    tmp_x, tmp_y, tmp_z,
	   +ELON(year,month,day,hour,minute,second));
}

//GSE座標系からGEI座標系への変換
void GSE_to_GEI(double *dst_x,  //GEI
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

  ROTATE_Z(&tmp_x,&tmp_y,&tmp_z,
	    src_x, src_y, src_z,
	   -ELON(year,month,day,hour,minute,second));
  ROTATE_X( dst_x, dst_y, dst_z,
	    tmp_x, tmp_y, tmp_z,
	   -OBLQ(year,month,day,hour,minute,second));
}

//GEO座標系からGSE座標系への変換
void GEO_to_GSE(double *dst_x,  //GSE
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
  
  GEO_to_GEI(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GEI_to_GSE( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}

//GSE座標系からGEO座標系への変換
void GSE_to_GEO(double *dst_x,  //GEO
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
  
  GSE_to_GEI(&tmp_x,&tmp_y,&tmp_z,
	      src_x, src_y, src_z,
	      year,month,day,hour,minute,second);
  GEI_to_GEO( dst_x, dst_y, dst_z,
	      tmp_x, tmp_y, tmp_z,
	      year,month,day,hour,minute,second);
}
