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
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"MEMORY.h"
#include"CDF_COMMON.h"

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

  EPOCH16breakdown(&dat,
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

void DATA__COPY(DATA *dst,
                INT1  type,
                void *data_ptr){
  dst->type = type;
  switch(type){
  case DATATYPE_NULL       :return;
  case DATATYPE_CHAR       :dst->data._char        = *(CHAR       *)data_ptr;return;
  case DATATYPE_UCHAR      :dst->data._uchar       = *(UCHAR      *)data_ptr;return;
  case DATATYPE_BYTE       :dst->data._byte        = *(BYTE       *)data_ptr;return;
  case DATATYPE_INT1       :dst->data._int1        = *(INT1       *)data_ptr;return;
  case DATATYPE_INT2       :dst->data._int2        = *(INT2       *)data_ptr;return;
  case DATATYPE_INT4       :dst->data._int4        = *(INT4       *)data_ptr;return;
  case DATATYPE_INT8       :dst->data._int8        = *(INT8       *)data_ptr;return;
  case DATATYPE_UINT1      :dst->data._uint1       = *(UINT1      *)data_ptr;return;
  case DATATYPE_UINT2      :dst->data._uint2       = *(UINT2      *)data_ptr;return;
  case DATATYPE_UINT4      :dst->data._uint4       = *(UINT4      *)data_ptr;return;
  case DATATYPE_FLOAT      :dst->data._float       = *(FLOAT      *)data_ptr;return;
  case DATATYPE_DOUBLE     :dst->data._double      = *(DOUBLE     *)data_ptr;return;
  case DATATYPE_REAL4      :dst->data._real4       = *(REAL4      *)data_ptr;return;
  case DATATYPE_REAL8      :dst->data._real8       = *(REAL8      *)data_ptr;return;
  case DATATYPE_EPOCH      :dst->data._epoch       = *(EPOCH      *)data_ptr;return;
  case DATATYPE_EPOCH16    :dst->data._epoch16     = *(EPOCH16    *)data_ptr;return;
  case DATATYPE_TIME_TT2000:dst->data._time_tt2000 = *(TIME_TT2000*)data_ptr;return;
  default                  :return;
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



const char *CDF__DATATYPETEXT(long dataType){
  switch(dataType){
  case CDF_CHAR       :return "CHAR";
  case CDF_UCHAR      :return "UCHAR";
  case CDF_BYTE       :return "BYTE";
  case CDF_INT1       :return "INT1";
  case CDF_INT2       :return "INT2";
  case CDF_INT4       :return "INT4";
  case CDF_INT8       :return "INT8";
  case CDF_UINT1      :return "UINT1";
  case CDF_UINT2      :return "UINT2";
  case CDF_UINT4      :return "UINT4";
  case CDF_FLOAT      :return "FLOAT";
  case CDF_DOUBLE     :return "DOUBLE";
  case CDF_REAL4      :return "REAL4";
  case CDF_REAL8      :return "REAL8";
  case CDF_EPOCH      :return "EPOCH";
  case CDF_EPOCH16    :return "EPOCH16";
  case CDF_TIME_TT2000:return "TIME_TT2000";
  default             :return "unknown";
  }
}

size_t CDF__SIZEOF(long dataType){
  switch(dataType){
  case CDF_CHAR       :return sizeof(CHAR);
  case CDF_UCHAR      :return sizeof(UCHAR);
  case CDF_BYTE       :return sizeof(BYTE);
  case CDF_INT1       :return sizeof(INT1);
  case CDF_INT2       :return sizeof(INT2);
  case CDF_INT4       :return sizeof(INT4);
  case CDF_INT8       :return sizeof(INT8);
  case CDF_UINT1      :return sizeof(UINT1);
  case CDF_UINT2      :return sizeof(UINT2);
  case CDF_UINT4      :return sizeof(UINT4);
  case CDF_FLOAT      :return sizeof(FLOAT);
  case CDF_DOUBLE     :return sizeof(DOUBLE);
  case CDF_REAL4      :return sizeof(REAL4);
  case CDF_REAL8      :return sizeof(REAL8);
  case CDF_EPOCH      :return sizeof(EPOCH);
  case CDF_EPOCH16    :return sizeof(EPOCH16);
  case CDF_TIME_TT2000:return sizeof(TIME_TT2000);
  default             :return 0;
  }
}

void CDF__DATA_SHOW_CHAR_       (CHAR        dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"%c" ,dat[n]);
  }
}

void CDF__DATA_SHOW_UCHAR_      (UCHAR       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"%uc",dat[n]);
  }
}

void CDF__DATA_SHOW_BYTE_       (BYTE        dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %02X",n,dat[n]);
  }
}

void CDF__DATA_SHOW_INT1_       (INT1        dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %d"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_INT2_       (INT2        dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %d"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_INT4_       (INT4        dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %d"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_INT8_       (INT8        dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %ld"  ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_UINT1_      (UINT1       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %d"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_UINT2_      (UINT2       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %d"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_UINT4_      (UINT4       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %d"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_FLOAT_      (FLOAT       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %f"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_DOUBLE_     (DOUBLE      dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %f"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_REAL4_      (REAL4       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %f"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_REAL8_      (REAL8       dat[],long numElems,FILE *fp){
  long n;
  
  for(n = 0L;n < numElems;n++){
    fprintf(fp,"[%2ld] %f"   ,n,dat[n]);
  }
}

void CDF__DATA_SHOW_EPOCH_      (EPOCH       dat[],long numElems,FILE *fp){
  long YYYY;
  long MM;
  long DD;
  long hh;
  long mm;
  long ss;
  long msec;
  long n;

  for(n = 0L;n < numElems;n++){
    EPOCHbreakdown(dat[n],
                   &YYYY,
                   &MM,
                   &DD,
                   &hh,
                   &mm,
                   &ss,
                   &msec);
    fprintf(fp,"[%2ld] %04d-%02d-%02d %02d:%02d:%02d.%03d",
            n,
            (INT2)YYYY,
            (INT1)MM,
            (INT1)DD,
            (INT1)hh,
            (INT1)mm,
            (INT1)ss,
            (INT2)msec);
  }
}

void CDF__DATA_SHOW_EPOCH16_    (EPOCH16     dat[],long numElems,FILE *fp){
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
  long n;

  for(n = 0L;n < numElems;n++){
    EPOCH16breakdown((double*)&dat[n],
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
    fprintf(fp,"[%2ld] %04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d%03d",
            n,
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
}

void CDF__DATA_SHOW_TIME_TT2000_(TIME_TT2000 dat[],long numElems,FILE *fp){
  double YYYY;
  double MM;
  double DD;
  double hh;
  double mm;
  double ss;
  double msec;
  double usec;
  double nsec;
  long   n;
  
  for(n = 0L;n < numElems;n++){
    CDF_TT2000_to_UTC_parts(dat[n],
                            &YYYY,
                            &MM,
                            &DD,
                            &hh,
                            &mm,
                            &ss,
                            &msec,
                            &usec,
                            &nsec);
    fprintf(fp,"[%2ld] %04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d",
            n,
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
}

void CDFMETADATA__SHOW      (CDFMETADATA *meta,
                             FILE        *fp){
  fprintf(fp,"attrName : %25s | entryType : %c | dataType : %15s | numElems : %ld\n",meta->attrName,meta->entryType,CDF__DATATYPETEXT(meta->dataType),meta->numElems);
  switch(meta->dataType){
  case CDF_CHAR       :CDF__DATA_SHOW_CHAR_       ((CHAR       *)meta->buffer,meta->numElems,fp);break;
  case CDF_UCHAR      :CDF__DATA_SHOW_UCHAR_      ((UCHAR      *)meta->buffer,meta->numElems,fp);break;
  case CDF_BYTE       :CDF__DATA_SHOW_BYTE_       ((BYTE       *)meta->buffer,meta->numElems,fp);break;
  case CDF_INT1       :CDF__DATA_SHOW_INT1_       ((INT1       *)meta->buffer,meta->numElems,fp);break;
  case CDF_INT2       :CDF__DATA_SHOW_INT2_       ((INT2       *)meta->buffer,meta->numElems,fp);break;
  case CDF_INT4       :CDF__DATA_SHOW_INT4_       ((INT4       *)meta->buffer,meta->numElems,fp);break;
  case CDF_INT8       :CDF__DATA_SHOW_INT8_       ((INT8       *)meta->buffer,meta->numElems,fp);break;
  case CDF_UINT1      :CDF__DATA_SHOW_UINT1_      ((UINT1      *)meta->buffer,meta->numElems,fp);break;
  case CDF_UINT2      :CDF__DATA_SHOW_UINT2_      ((UINT2      *)meta->buffer,meta->numElems,fp);break;
  case CDF_UINT4      :CDF__DATA_SHOW_UINT4_      ((UINT4      *)meta->buffer,meta->numElems,fp);break;    
  case CDF_FLOAT      :CDF__DATA_SHOW_FLOAT_      ((FLOAT      *)meta->buffer,meta->numElems,fp);break;
  case CDF_DOUBLE     :CDF__DATA_SHOW_DOUBLE_     ((DOUBLE     *)meta->buffer,meta->numElems,fp);break;
  case CDF_REAL4      :CDF__DATA_SHOW_REAL4_      ((REAL4      *)meta->buffer,meta->numElems,fp);break;
  case CDF_REAL8      :CDF__DATA_SHOW_REAL8_      ((REAL8      *)meta->buffer,meta->numElems,fp);break;
  case CDF_EPOCH      :CDF__DATA_SHOW_EPOCH_      ((EPOCH      *)meta->buffer,meta->numElems,fp);break;
  case CDF_EPOCH16    :CDF__DATA_SHOW_EPOCH16_    ((EPOCH16    *)meta->buffer,meta->numElems,fp);break;
  case CDF_TIME_TT2000:CDF__DATA_SHOW_TIME_TT2000_((TIME_TT2000*)meta->buffer,meta->numElems,fp);break;
  default:
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  fprintf(fp,"\n");
}

void CDFMETADATA__INITIALIZE(CDFMETADATA *meta,
                             CDFid        id,
                             long         attrNum,
                             long         entryNum){
  CDFstatus status;
  long      attrScope;
  
  // *************************************************************************
  // 属性名の取得
  // *************************************************************************
  status = CDFgetAttrName (id,attrNum,meta->attrName);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // 属性スコープの取得
  // *************************************************************************
  status = CDFgetAttrScope(id,attrNum,    &attrScope);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  switch(attrScope){
  case GLOBAL_SCOPE:
    // *************************************************************************
    // 属性に対応するエントリー番号のデータが存在するかを確認
    // *************************************************************************
    meta->entryType = 'g';
    status = CDFconfirmgEntryExistence  (id,attrNum,entryNum);
    if(status == NO_SUCH_ENTRY){
      CDF__Status_Handler(status);
    }
    // *************************************************************************
    // エントリーのデータ型を取得
    // *************************************************************************
    status = CDFgetAttrgEntryDataType   (id,attrNum,entryNum,&meta->dataType);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    // *************************************************************************
    // エントリーの要素数の取得
    // *************************************************************************
    status = CDFgetAttrgEntryNumElements(id,attrNum,entryNum,&meta->numElems);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    // *************************************************************************
    // メモリ確保
    // *************************************************************************
    meta->buffer = malloc(CDF__SIZEOF(meta->dataType) * meta->numElems);
    if(meta->buffer == NULL){
      ERROR__SHOW("#1");
      exit(EXIT_FAILURE);
    }
    // *************************************************************************
    // エントリーのデータの取得
    // *************************************************************************
    status = CDFgetAttrgEntry           (id,attrNum,entryNum, meta->buffer  );
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    break;
  case VARIABLE_SCOPE:
    // *************************************************************************
    // 属性に対応するエントリー番号のデータが存在するかを確認
    // *************************************************************************
    meta->entryType = 'v';
    status = CDFconfirmrEntryExistence(id,attrNum,entryNum);
    if(status != NO_SUCH_ENTRY){
      meta->entryType = 'r';
    }
    status = CDFconfirmzEntryExistence(id,attrNum,entryNum);
    if(status != NO_SUCH_ENTRY){
      meta->entryType = 'z';
    }
    switch(meta->entryType){
    case 'r':
      // *************************************************************************
      // エントリーのデータ型を取得
      // *************************************************************************
      status = CDFgetAttrrEntryDataType   (id,attrNum,entryNum,&meta->dataType);
      if(status != CDF_OK){
        CDF__Status_Handler(status);
      }
      // *************************************************************************
      // エントリーの要素数の取得
      // *************************************************************************
      status = CDFgetAttrrEntryNumElements(id,attrNum,entryNum,&meta->numElems);
      if(status != CDF_OK){
        CDF__Status_Handler(status);
      }
      // *************************************************************************
      // メモリ確保
      // *************************************************************************
      meta->buffer = malloc(CDF__SIZEOF(meta->dataType) * meta->numElems);
      if(meta->buffer == NULL){
        ERROR__SHOW("#1");
        exit(EXIT_FAILURE);
      }
      // *************************************************************************
      // エントリーのデータの取得
      // *************************************************************************
      status = CDFgetAttrrEntry           (id,attrNum,entryNum,meta->buffer);
      if(status != CDF_OK){
        CDF__Status_Handler(status);
      }        
      break;
    case 'z':
      // *************************************************************************
      // エントリーのデータ型を取得
      // *************************************************************************
      status = CDFgetAttrzEntryDataType   (id,attrNum,entryNum,&meta->dataType);
      if(status != CDF_OK){
        CDF__Status_Handler(status);
      }
      // *************************************************************************
      // エントリーの要素数の取得
      // *************************************************************************
      status = CDFgetAttrzEntryNumElements(id,attrNum,entryNum,&meta->numElems);
      if(status != CDF_OK){
        CDF__Status_Handler(status);
      }
      // *************************************************************************
      // メモリ確保
      // *************************************************************************
      meta->buffer = malloc(CDF__SIZEOF(meta->dataType) * meta->numElems);
      if(meta->buffer == NULL){
        ERROR__SHOW("#1");
        exit(EXIT_FAILURE);
      }
      // *************************************************************************
      // エントリーのデータの取得
      // *************************************************************************
      status = CDFgetAttrzEntry           (id,attrNum,entryNum,meta->buffer);
      if(status != CDF_OK){
        CDF__Status_Handler(status);
      }        
      break;
    default:
      CDF__Status_Handler(status);      
    }
    break;
  default:
    CDF__Status_Handler(status);    
  }
}

void CDFMETADATA__FINALIZE  (CDFMETADATA *meta){
  free(meta->buffer);
}

void CDF__SHOW_GATTRIBUTES(CDFid id,FILE *fp){
  CDFstatus   status;
  long        num_Attrs;//g/v属性の登録数
  long        numgAttrs;//g  属性の登録数
  long        attrNum;  //属性番号
  long        attrScope;//属性スコープ
  long        maxgEntry;//最大gEntry番号
  long        entryNum; //Entry番号
  long        numgEntry;//gEntryの登録数
  CDFMETADATA meta;

  // *************************************************************************
  // g/v属性の登録数を取得
  // *************************************************************************
  status = CDFgetNumAttributes (id,&num_Attrs);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // g  属性の登録数を取得
  // *************************************************************************
  status = CDFgetNumgAttributes(id,&numgAttrs);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // g属性登録数の出力
  // *************************************************************************
  fprintf(fp,"Global Attributes : %ld\n",numgAttrs);

  for(attrNum = 0L;attrNum < num_Attrs;attrNum++){
    // *************************************************************************
    // 属性スコープの取得
    // *************************************************************************
    status = CDFgetAttrScope(id,attrNum,&attrScope);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    if(attrScope != GLOBAL_SCOPE){
      continue;
    }
    // *************************************************************************
    // 属性を定義しているgEntryデータの最大要素番号を取得
    // *************************************************************************
    status = CDFgetAttrMaxgEntry(id,attrNum,&maxgEntry);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    // *************************************************************************
    // エントリー数の取得
    // *************************************************************************
    status = CDFgetNumAttrgEntries(id,attrNum,&numgEntry);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }

    fprintf(fp,"=== numgEntry = %ld ===\n",
            numgEntry);

    for(entryNum = 0L;entryNum <= maxgEntry;entryNum++){
      // *************************************************************************
      // 属性に対応するエントリー番号のデータが存在するかを確認
      // *************************************************************************
      status = CDFconfirmgEntryExistence(id,attrNum,entryNum);
      if(status == NO_SUCH_ENTRY){
        continue;
      }
      CDFMETADATA__INITIALIZE(&meta,id,attrNum,entryNum);
      CDFMETADATA__SHOW      (&meta,fp);
      CDFMETADATA__FINALIZE  (&meta);      
    }
  }
}

void CDF__SHOW_RATTRIBUTES(CDFid id,FILE *fp){
  CDFstatus   status;
  long        num_Attrs;//g/v属性の登録数
  long        numvAttrs;//v  属性の登録数
  long        attrNum;  //属性番号
  long        attrScope;//属性スコープ
  long        maxrEntry;//最大rEntry番号
  long        entryNum; //Entry番号
  long        numrEntry;//rEntryの登録数
  CDFMETADATA meta;

  // *************************************************************************
  // g/v属性の登録数を取得
  // *************************************************************************
  status = CDFgetNumAttributes (id,&num_Attrs);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // v  属性の登録数を取得
  // *************************************************************************
  status = CDFgetNumvAttributes(id,&numvAttrs);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // v属性登録数の出力
  // *************************************************************************
  fprintf(fp,"Variable Attributes : %ld\n",numvAttrs);

  for(attrNum = 0L;attrNum < num_Attrs;attrNum++){
    // *************************************************************************
    // 属性スコープの取得
    // *************************************************************************
    status = CDFgetAttrScope(id,attrNum,&attrScope);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    if(attrScope != VARIABLE_SCOPE){
      continue;
    }
    // *************************************************************************
    // 属性を定義しているrEntryデータの最大要素番号を取得
    // *************************************************************************
    status = CDFgetAttrMaxrEntry(id,attrNum,&maxrEntry);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    // *************************************************************************
    // エントリー数の取得
    // *************************************************************************
    status = CDFgetNumAttrrEntries(id,attrNum,&numrEntry);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }

    fprintf(fp,"=== numrEntry = %ld ===\n",
            numrEntry);

    for(entryNum = 0L;entryNum <= maxrEntry;entryNum++){
      // *************************************************************************
      // 属性に対応するエントリー番号のデータが存在するかを確認
      // *************************************************************************
      status = CDFconfirmrEntryExistence(id,attrNum,entryNum);
      if(status == NO_SUCH_ENTRY){
        continue;
      }
      CDFMETADATA__INITIALIZE(&meta,id,attrNum,entryNum);
      CDFMETADATA__SHOW      (&meta,fp);
      CDFMETADATA__FINALIZE  (&meta);      
    }
  }
}

void CDF__SHOW_ZATTRIBUTES(CDFid id,FILE *fp){
  CDFstatus   status;
  long        num_Attrs;//g/v属性の登録数
  long        numvAttrs;//v  属性の登録数
  long        attrNum;  //属性番号
  long        attrScope;//属性スコープ
  long        maxzEntry;//最大zEntry番号
  long        entryNum; //Entry番号
  long        numzEntry;//zEntryの登録数
  CDFMETADATA meta;

  // *************************************************************************
  // g/v属性の登録数を取得
  // *************************************************************************
  status = CDFgetNumAttributes (id,&num_Attrs);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // v  属性の登録数を取得
  // *************************************************************************
  status = CDFgetNumvAttributes(id,&numvAttrs);
  if(status != CDF_OK){
    CDF__Status_Handler(status);
  }
  // *************************************************************************
  // v属性登録数の出力
  // *************************************************************************
  fprintf(fp,"Variable Attributes : %ld\n",numvAttrs);

  for(attrNum = 0L;attrNum < num_Attrs;attrNum++){
    // *************************************************************************
    // 属性スコープの取得
    // *************************************************************************
    status = CDFgetAttrScope(id,attrNum,&attrScope);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    if(attrScope != VARIABLE_SCOPE){
      continue;
    }
    // *************************************************************************
    // 属性を定義しているzEntryデータの最大要素番号を取得
    // *************************************************************************
    status = CDFgetAttrMaxzEntry(id,attrNum,&maxzEntry);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }
    // *************************************************************************
    // エントリー数の取得
    // *************************************************************************
    status = CDFgetNumAttrzEntries(id,attrNum,&numzEntry);
    if(status != CDF_OK){
      CDF__Status_Handler(status);
    }

    fprintf(fp,"=== numzEntry = %ld ===\n",
            numzEntry);

    for(entryNum = 0L;entryNum <= maxzEntry;entryNum++){
      // *************************************************************************
      // 属性に対応するエントリー番号のデータが存在するかを確認
      // *************************************************************************
      status = CDFconfirmzEntryExistence(id,attrNum,entryNum);
      if(status == NO_SUCH_ENTRY){
        continue;
      }
      CDFMETADATA__INITIALIZE(&meta,id,attrNum,entryNum);
      CDFMETADATA__SHOW      (&meta,fp);
      CDFMETADATA__FINALIZE  (&meta);      
    }
  }
}

void CDFMETADATA__INITIALIZE_ZVAR_ATTR(CDFMETADATA *meta,
                                       CDFid        id,
                                       const CHAR  *zVarName,
                                       const CHAR  *attrName){
  long attrNum;
  long entryNum;

  attrNum  = CDFgetAttrNum(id,(char*)attrName);
  if(attrNum  < CDF_OK){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  entryNum = CDFgetVarNum (id,(char*)zVarName);
  if(entryNum < CDF_OK){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);
  }
  CDFMETADATA__INITIALIZE(meta,id,attrNum,entryNum);
}
