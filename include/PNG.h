/***************************************************************** 
 *
 * PNGファイル操作
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _PNG_H_INCLUDE_
#define _PNG_H_INCLUDE_

#include   <stdio.h>
#include  <stdlib.h>
#include"DATATYPE.h"

IMAGE load_png(const char *path,int *width,int *height);

void  PNG__Output_File_Pointer(IMAGE img,UINT4 width,UINT4 height,FILE       *fp      );
void  PNG__Output_BASE64      (IMAGE img,UINT4 width,UINT4 height,FILE       *fp      );
void  PNG__Output_File        (IMAGE img,UINT4 width,UINT4 height,const char *filename);

#endif
