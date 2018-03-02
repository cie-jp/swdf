/***************************************************************** 
 *
 * BASE64エンコーダ
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#ifndef _BASE64_ENCODER_H_INCLUDE_
#define _BASE64_ENCODER_H_INCLUDE_

#include<stdio.h>
#include"DATATYPE.h"

typedef struct{
  FILE  *fp;
  UINT4  code;
  UINT4  count;
}BASE64_ENCODER;

void BASE64_ENCODER__Initialize(BASE64_ENCODER *_this,FILE *fp );
void BASE64_ENCODER__ReadByte  (BASE64_ENCODER *_this,UINT1 dat);
void BASE64_ENCODER__ReadBytes (BASE64_ENCODER *_this,UINT1 dat[],UINT4 num);
void BASE64_ENCODER__Finalize  (BASE64_ENCODER *_this);

#endif
