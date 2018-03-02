/***************************************************************** 
 *
 * SVGPLOT TICS TEXT
 *
 *
 *                           Created  by Mamoru Ota (2017/12/28)
 * 
 *****************************************************************/

#include"SVGPLOT_TICS.h"

int COMPARE_REAL8(const void *a,const void *b){
  if(*(REAL8*)a < *(REAL8*)b){
    return -1;
  }
  if(*(REAL8*)a > *(REAL8*)b){
    return +1;
  }
  return 0;
}

REAL8 GET_D(REAL8 val[],
	    INT4  num){
  REAL8 *buf;
  REAL8  min = 0.0;
  REAL8  tmp;
  INT4   isinit;
  INT4   n;

  if((buf = (REAL8*)malloc(sizeof(REAL8) * num)) == NULL){
    exit(EXIT_FAILURE);
  }

  memcpy(buf,val,sizeof(REAL8) * num);
  qsort (buf,num,sizeof(REAL8),COMPARE_REAL8);

  isinit = 0;
  for(n = 1;n < num;n++){
    tmp = fabs(buf[n] - buf[n - 1]);
    if(isnan(tmp) || isinf(tmp)){
      continue;
    }
    if(!isinit){
      isinit = 1;
      min    = tmp;
    }else{
      if(min > tmp){
	 min = tmp;
      }
    }
  }
  
  free(buf);

  return isinit ? min : -1.0;
}

void SVGPLOT__GET_OPT_LINEAR_SCALE(INT4 *shift,
				   INT4 *exponent,
				   INT4 *digitnumu,
				   INT4 *digitnuml,
				   REAL8 val[],
				   INT4  num){
  REAL8 dval;
  INT8  shift0;
  INT8  shift1;
  REAL8 scale;
  INT8  tmp;

  INT8  type1shift;
  INT8  type1exponent;
  INT8  type1digitnumu;
  INT8  type1digitnuml;
  INT8  type1digitnum;
  INT8  type1strlen;

  INT8  type2shift;
  INT8  type2digitnumu;
  INT8  type2digitnuml;
  INT8  type2digitnum;
  INT8  type2exponent;
  INT8  type2strlen;
  
  INT4  n,k;

  dval   = GET_D(val,num);
  shift0 = floor(log10(dval));
  for(k = 3;k >= 0;k--){ 
    shift1 = shift0 - k;
    scale  = pow(10.0,shift1);
    for(n = 0;n < num;n++){
      if(((INT8)round(fabs(val[n] / scale)) % 10) != 0){
	goto EXIT;
      }
    }
  }
 EXIT:
  type1shift     = shift1;
  type1exponent  = 0;
  type1digitnum  = 0;
  type1digitnumu = 0;
  for(n = 0;n < num;n++){
    tmp = (int)floor(log10(fabs(val[n] / scale))) + 1;    
    if(type1digitnum  < tmp){
       type1digitnum  = tmp;
    }
    tmp = (int)floor(log10(fabs(val[n] / 1.0  ))) + 1;    
    if(type1digitnumu < tmp){
       type1digitnumu = tmp;
    }
  }
  type1digitnuml = type1digitnum - type1digitnumu;
  
  if(type1digitnumu == 0){
    type2shift      = shift1;
    type2exponent   = type1digitnuml + type2shift - 1;
    type2digitnumu  = 1;
    type2digitnuml  =    -type2shift + type2exponent ;
    type2digitnum   = type2digitnumu + type2digitnuml;
    type2strlen     = 1 + type2digitnumu;
    if(type2digitnuml != 0){
       type2strlen += 1 - type2shift + type2exponent;
    }

    type1strlen     = 1 + 1 + 1 - type1shift;
  }else 
  if(type1digitnuml <  0){
    type2shift      = shift1;
    type2exponent   = type1digitnuml + type2shift - 1 + type1digitnumu;
    type2digitnumu  = 1;
    type2digitnuml  = type1digitnum - 1;
    type2digitnum   = type2digitnumu + type2digitnuml;
    type2strlen     = 1 + type2digitnumu;
    if(type2digitnuml != 0){
       type2strlen += 1 - type2shift + type2exponent;
    }

    type1shift      = 0;
    type1digitnuml  = 0;
    type1digitnum   = type1digitnumu;
    type1strlen     = 1 + type1digitnumu;
  }else{
    *shift     = type1shift;
    *exponent  = type1exponent;
    *digitnumu = type1digitnumu;
    *digitnuml = type1digitnuml;
    return;
  }

  if((type1strlen <= 7) || (type1strlen <= type2strlen)){
    *shift     = type1shift;
    *exponent  = type1exponent;
    *digitnumu = type1digitnumu;
    *digitnuml = type1digitnuml;
  }else{
    *shift     = type2shift;
    *exponent  = type2exponent;
    *digitnumu = type2digitnumu;
    *digitnuml = type2digitnuml;
  }
  /*
    fprintf(stderr,"TMP TYPE 1 [digitnum : %ld %ld %ld] exponent : %ld shift : %ld strlen : %ld\n",
    type1digitnum,type1digitnumu,type1digitnuml,type1exponent,type1shift,type1strlen);
    fprintf(stderr,"TMP TYPE 2 [digitnum : %ld %ld %ld] exponent : %ld shift : %ld strlen : %ld\n",
    type2digitnum,type2digitnumu,type2digitnuml,type2exponent,type2shift,type2strlen);
  */
}

void SVGPLOT__SET_TEXT_FROM_REAL8_LINEAR(CHAR  text[2048],
					 REAL8 val,
					 INT4  shift,
					 INT4  exponent,
					 INT4  digitnumu,
					 INT4  digitnuml){
  REAL8 scale;
  INT8  val0;
  INT8  sf;
  INT8  valu;
  INT8  vall;
  CHAR  format[2048];
  INT4  n;

  scale = pow(10.0,shift);
  val0  = (INT8)round(fabs(val / scale));
  sf    = (INT8)pow(10,digitnuml);
  valu  = val0 / sf;
  vall  = val0 % sf;

  if(digitnuml == 0){
    sprintf(format,"%%%dlld"         ,1 + digitnumu);
    sprintf(text,format,valu);
  }else{
  if(digitnumu == 0){
    sprintf(format,     " 0.%%0%dlld",              -shift + exponent);
    sprintf(text,format,     vall);
  }else{
    sprintf(format,"%%%dlld.%%0%dlld",1 + digitnumu,-shift + exponent);
    sprintf(text,format,valu,vall);
  }
  }
  for(n = 1;text[n] != '\0';n++){
    if((text[n - 1] == ' ') && isdigit(text[n])){
      if(val > 0.0){
	text[n - 1] = ' ';
	break;
      }else 
      if(val < 0.0){
	text[n - 1] = '-';
	break;
      }else{
	break;
      }
    }
  }

  if(exponent != 0){
    sprintf(text,"%sx10^{%d}",text,exponent);
  }

  /*
  if(exponent != 0){
    fprintf(stderr,"%s x10^{%d} %20.10lf %20ld %20ld\n",text,exponent,val,valu,vall);
  }else{
    fprintf(stderr,"%s %20.10lf %20ld %20ld\n",text,val,valu,vall);
  }
  */

}

void SVGPLOT__SET_TEXT_FROM_REAL8_LOG   (CHAR  text[2048],
					 REAL8 val){
  REAL8 mantissa;
  INT4  exponent;  

  exponent = (INT4)floor(log10(val));
  mantissa = val / pow(10.0,(REAL8)exponent);
  if((INT4)round(mantissa * 10.0) == 10){
    sprintf(text,      "10^{%d}",         exponent);
  }else{
    sprintf(text,"%.1lfx10^{%d}",mantissa,exponent);
  }
}
