#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

//GEO座標系からGEI座標系への変換
void GEO_to_GEI(double *dst_x,  //GEI
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
  ROTATE_Z(dst_x,dst_y,dst_z,
	   src_x,src_y,src_z,
	  -GMST(year,month,day,hour,minute,second));
}

//GEI座標系からGEO座標系への変換
void GEI_to_GEO(double *dst_x,  //GEO
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
  ROTATE_Z(dst_x,dst_y,dst_z,
	   src_x,src_y,src_z,
	  +GMST(year,month,day,hour,minute,second));
}
