/***************************************************************** 
 *
 * BASE64エンコーダ
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"BASE64_ENCODER.h"

const CHAR BASE64_ENCODER__TABLE[64 + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void BASE64_ENCODER__Initialize(BASE64_ENCODER *_this,FILE *fp){
  _this->fp    =   fp;
  _this->code  = 0x00;
  _this->count =    0;
}

void BASE64_ENCODER__ReadByte  (BASE64_ENCODER *_this,UINT1 dat){
  _this->code <<= 8;
  _this->code  |= dat;
  _this->count++;
  if(_this->count %  3 == 0){
    fprintf(_this->fp,
	    "%c%c%c%c",
	    BASE64_ENCODER__TABLE[(_this->code >> 18) & 0x3F],
	    BASE64_ENCODER__TABLE[(_this->code >> 12) & 0x3F],
	    BASE64_ENCODER__TABLE[(_this->code >>  6) & 0x3F],
	    BASE64_ENCODER__TABLE[ _this->code        & 0x3F]);
    _this->code = 0x00;
  }
}

void BASE64_ENCODER__ReadBytes (BASE64_ENCODER *_this,UINT1 dat[],UINT4 num){
  INT4 n;

  for(n = 0;n < num;n++){
    BASE64_ENCODER__ReadByte(_this,dat[n]);
  }
}

void BASE64_ENCODER__Finalize  (BASE64_ENCODER *_this){
  switch(_this->count % 3){
  case 0:
    break;
  case 1:
    _this->code <<=  8;
    fprintf(_this->fp,
	    "%c%c%c%c",
	    BASE64_ENCODER__TABLE[(_this->code >> 10) & 0x3F],
	    BASE64_ENCODER__TABLE[(_this->code >>  4) & 0x3F],
	    '=',
	    '=');    
    break;
  case 2:
    _this->code <<=  8;
    fprintf(_this->fp,
	    "%c%c%c%c",
	    BASE64_ENCODER__TABLE[(_this->code >> 18) & 0x3F],
	    BASE64_ENCODER__TABLE[(_this->code >> 12) & 0x3F],
	    BASE64_ENCODER__TABLE[(_this->code >>  6) & 0x3F],
	    '=');        
    break;
  }
  _this->fp    = NULL;
  _this->code  = 0x00;
  _this->count =    0;
}
