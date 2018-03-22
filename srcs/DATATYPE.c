/***************************************************************** 
 *
 * データ型
 *
 *
 *                           Created  by Mamoru Ota (2018/03/22)
 * 
 *****************************************************************/

#include"DATATYPE.h"
#include"cdf.h"
#include"math.h"

void DATA__WRITE_EPOCH_      (EPOCH       dat,FILE *fp){
  long YYYY;
  long MM;
  long DD;
  long hh;
  long mm;
  long ss;
  long msec;

  EPOCHbreakdown(dat,
                 &YYYY,
                 &MM,
                 &DD,
                 &hh,
                 &mm,
                 &ss,
                 &msec);
  fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d.%03d",
          (INT2)YYYY,
          (INT1)MM,
          (INT1)DD,
          (INT1)hh,
          (INT1)mm,
          (INT1)ss,
          (INT2)msec);
}

void DATA__WRITE_EPOCH16_    (EPOCH16     dat,FILE *fp){
  long YYYY;
  long MM;
  long DD;
  long hh;
  long mm;
  long ss;
  long msec;
  long usec;
  long nsec;
  long psec;

  EPOCH16breakdown(dat,
                   &YYYY,
                   &MM,
                   &DD,
                   &hh,
                   &mm,
                   &ss,
                   &msec,
                   &usec,
                   &nsec,
                   &psec);
  fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d%03d",
          (INT2)YYYY,
          (INT1)MM,
          (INT1)DD,
          (INT1)hh,
          (INT1)mm,
          (INT1)ss,
          (INT2)msec,
          (INT2)usec,
          (INT2)nsec,
          (INT2)psec);
}

void DATA__WRITE_TIME_TT2000_(TIME_TT2000 dat,FILE *fp){
  double YYYY;
  double MM;
  double DD;
  double hh;
  double mm;
  double ss;
  double msec;
  double usec;
  double nsec;

  CDF_TT2000_to_UTC_parts(dat,
                          &YYYY,
                          &MM,
                          &DD,
                          &hh,
                          &mm,
                          &ss,
                          &msec,
                          &usec,
                          &nsec);
  fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d",
          (INT2)YYYY,
          (INT1)MM,
          (INT1)DD,
          (INT1)hh,
          (INT1)mm,
          (INT1)ss,
          (INT2)msec,
          (INT2)usec,
          (INT2)nsec);  
}

void DATA__WRITE(DATA *dat,FILE *fp){
  double YYYY;
  double MM;
  double DD;
  double hh;
  double mm;
  double ss;
  double msec;
  double usec;
  double nsec;
  double psec;
  
  switch(dat->type){
  case DATATYPE_NULL:
    fprintf(fp,"null");
    break;
  case DATATYPE_CHAR:
    fprintf(fp,"%c",dat->data._char);
    break;
  case DATATYPE_UCHAR:
    fprintf(fp,"%uc",dat->data._uchar);
    break;
  case DATATYPE_BYTE:
    fprintf(fp,"%uc",dat->data._byte);
    break;
  case DATATYPE_INT1:
    fprintf(fp,"%d",dat->data._int1);
    break;
  case DATATYPE_INT2:
    fprintf(fp,"%d",dat->data._int2);
    break;
  case DATATYPE_INT4:
    fprintf(fp,"%d",dat->data._int4);
    break;
  case DATATYPE_INT8:
    fprintf(fp,"%ld",dat->data._int8);
    break;
  case DATATYPE_UINT1:
    fprintf(fp,"%d",dat->data._uint1);
    break;
  case DATATYPE_UINT2:
    fprintf(fp,"%d",dat->data._uint2);
    break;
  case DATATYPE_UINT4:
    fprintf(fp,"%d",dat->data._uint4);
    break;
  case DATATYPE_FLOAT:
    fprintf(fp,"%f",dat->data._float);
    break;
  case DATATYPE_DOUBLE:
    fprintf(fp,"%f",dat->data._double);
    break;
  case DATATYPE_REAL4:
    fprintf(fp,"%f",dat->data._real4);
    break;
  case DATATYPE_REAL8:
    fprintf(fp,"%f",dat->data._real8);
    break;
  case DATATYPE_EPOCH      :DATA__WRITE_EPOCH_      (dat->data._epoch      ,fp);break;
  case DATATYPE_EPOCH16    :DATA__WRITE_EPOCH16_    (dat->data._epoch16    ,fp);break;
  case DATATYPE_TIME_TT2000:DATA__WRITE_TIME_TT2000_(dat->data._time_tt2000,fp);break;
  }
}

INT1 DATA__GET_DATATYPE(long dataType){
  switch(dataType){
  case CDF_CHAR       :return DATATYPE_CHAR;
  case CDF_UCHAR      :return DATATYPE_UCHAR;
  case CDF_BYTE       :return DATATYPE_BYTE;
  case CDF_INT1       :return DATATYPE_INT1;
  case CDF_INT2       :return DATATYPE_INT2;
  case CDF_INT4       :return DATATYPE_INT4;
  case CDF_INT8       :return DATATYPE_INT8;
  case CDF_UINT1      :return DATATYPE_UINT1;
  case CDF_UINT2      :return DATATYPE_UINT2;
  case CDF_UINT4      :return DATATYPE_UINT4;
  case CDF_FLOAT      :return DATATYPE_FLOAT;
  case CDF_DOUBLE     :return DATATYPE_DOUBLE;
  case CDF_REAL4      :return DATATYPE_REAL4;
  case CDF_REAL8      :return DATATYPE_REAL8;
  case CDF_EPOCH      :return DATATYPE_EPOCH;
  case CDF_EPOCH16    :return DATATYPE_EPOCH16;
  case CDF_TIME_TT2000:return DATATYPE_TIME_TT2000;
  default             :return DATATYPE_NULL;    
  }  
}

REAL8 DATA__GET(DATA *dat){
  switch(dat->type){
  case DATATYPE_NULL       :return NAN;
  case DATATYPE_CHAR       :return (REAL8)dat->data._char  ;
  case DATATYPE_UCHAR      :return (REAL8)dat->data._uchar ;
  case DATATYPE_BYTE       :return (REAL8)dat->data._byte  ;
  case DATATYPE_INT1       :return (REAL8)dat->data._int1  ;
  case DATATYPE_INT2       :return (REAL8)dat->data._int2  ;
  case DATATYPE_INT4       :return (REAL8)dat->data._int4  ;
  case DATATYPE_INT8       :return (REAL8)dat->data._int8  ;
  case DATATYPE_UINT1      :return (REAL8)dat->data._uint1 ;
  case DATATYPE_UINT2      :return (REAL8)dat->data._uint2 ;
  case DATATYPE_UINT4      :return (REAL8)dat->data._uint4 ;
  case DATATYPE_FLOAT      :return (REAL8)dat->data._float ;
  case DATATYPE_DOUBLE     :return (REAL8)dat->data._double;
  case DATATYPE_REAL4      :return (REAL8)dat->data._real4 ;
  case DATATYPE_REAL8      :return (REAL8)dat->data._real8 ;
  case DATATYPE_EPOCH      :return NAN;
  case DATATYPE_EPOCH16    :return NAN;
  case DATATYPE_TIME_TT2000:return NAN;
  default                  :return NAN;
  }
}

//CDFgetDataTypeSize(long dataType,long *numBytes)
//status = CDFgetDataTypeSize((long)CDF_INT4, &numBytes); if (status != CDF_OK) UserStatusHandler (status);
//status = CDFgetzVarDataType (id,varNum,&dataType);
