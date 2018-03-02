#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"TRANSFORM.h"

//x軸回転
void ROTATE_X(double *dst_x,
	      double *dst_y,
	      double *dst_z,
	      double  src_x,
	      double  src_y,
	      double  src_z,
	      double  rot){ //回転角[rad]
  *dst_x =  src_x;
  *dst_y =  cos(rot) * src_y + sin(rot) * src_z;
  *dst_z = -sin(rot) * src_y + cos(rot) * src_z;
}

//y軸回転
void ROTATE_Y(double *dst_x,
	      double *dst_y,
	      double *dst_z,
	      double  src_x,
	      double  src_y,
	      double  src_z,
	      double  rot){ //回転角[rad]
  *dst_x =  cos(rot) * src_x + sin(rot) * src_z;
  *dst_y =  src_y;
  *dst_z = -sin(rot) * src_x + cos(rot) * src_z;
}

//z軸回転
void ROTATE_Z(double *dst_x,
	      double *dst_y,
	      double *dst_z,
	      double  src_x,
	      double  src_y,
	      double  src_z,
	      double  rot){ //回転角[rad]
  *dst_x =  cos(rot) * src_x + sin(rot) * src_y;
  *dst_y = -sin(rot) * src_x + cos(rot) * src_y;
  *dst_z =  src_z;
}
