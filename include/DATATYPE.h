/*****************************************************************
 * 
 * データ型の宣言 & マクロ定義
 *
 *
 *                           Modified by Mamoru Ota (2017/01/25)
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#ifndef _DATATYPE_H_INCLUDE_
#define _DATATYPE_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

  #include<stdio.h>
  #include"cdf.h"
  
  // ***********************************
  // データ型宣言
  // ***********************************

  typedef char               CHAR       ; //    1-byte,   signed character.
  typedef unsigned char      UCHAR      ; //    1-byte, unsigned character.
  typedef char               BYTE       ; //    1-byte,   signed integer.
  typedef char               INT1       ; //    1-byte,   signed integer.
  typedef short int          INT2       ; //    2-byte,   signed integer.
  typedef int                INT4       ; //    4-byte,   signed integer.
  typedef long int           INT8       ; //    8-byte,   signed integer.
  typedef unsigned char      UINT1      ; //    1-byte, unsigned integer.
  typedef unsigned short int UINT2      ; //    2-byte, unsigned integer.
  typedef unsigned int       UINT4      ; //    4-byte, unsigned integer.
  typedef float              FLOAT      ; //    4-byte, floating point.
  typedef double             DOUBLE     ; //    8-byte, floating point.
  typedef float              REAL4      ; //    4-byte, floating point.
  typedef double             REAL8      ; //    8-byte, floating point.
  typedef double             EPOCH      ; //    8-byte, floating point.
  typedef struct{
    double x;
    double y;
  }EPOCH16;                               //two 8-byte, floating point.
  typedef long long int      TIME_TT2000; //    8-byte,   signed integer.
  typedef TIME_TT2000        T2000      ;

  typedef struct{
    UINT1 R;
    UINT1 G;
    UINT1 B;
    UINT1 A;
  }RGBA,*IMAGE;

#define DATATYPE_NULL        (-1)
#define DATATYPE_CHAR        ( 0)
#define DATATYPE_UCHAR       ( 1)
#define DATATYPE_BYTE        ( 2)
#define DATATYPE_INT1        ( 3)
#define DATATYPE_INT2        ( 4)
#define DATATYPE_INT4        ( 5)
#define DATATYPE_INT8        ( 6)
#define DATATYPE_UINT1       ( 7)
#define DATATYPE_UINT2       ( 8)
#define DATATYPE_UINT4       ( 9)
#define DATATYPE_FLOAT       (10)
#define DATATYPE_DOUBLE      (11)
#define DATATYPE_REAL4       (12)
#define DATATYPE_REAL8       (13)
#define DATATYPE_EPOCH       (14)
#define DATATYPE_EPOCH16     (15)
#define DATATYPE_TIME_TT2000 (16)
#define DATATYPE_T2000       (DATATYPE_TIME_TT2000)

  typedef union{
    CHAR        _char;
    UCHAR       _uchar;
    BYTE        _byte;
    INT1        _int1;
    INT2        _int2;
    INT4        _int4;
    INT8        _int8;
    UINT1       _uint1;
    UINT2       _uint2;
    UINT4       _uint4;
    FLOAT       _float;
    DOUBLE      _double;
    REAL4       _real4;
    REAL8       _real8;
    EPOCH       _epoch;
    EPOCH16     _epoch16;
    TIME_TT2000 _time_tt2000;    
  }DATA_CONTENT;

  typedef struct{
    INT1         type;
    DATA_CONTENT data;
  }DATA;

  void DATA__WRITE(DATA *dat,FILE *fp);

  // ***********************************
  // マクロ定義
  // ***********************************

#define JOINT(_x_,_y_) JOIN_(_x_, _y_)
#define JOIN_(_x_,_y_)       _x_##_y_

#define TSTR(_str_)    ISTR(_str_)
#define ISTR(_str_)        #_str_  

#ifndef ILLEGAL_TT2000_VALUE
#define ILLEGAL_TT2000_VALUE    (-9223372036854775805LL)
#endif

  INT1 DATA__GET_DATATYPE(long dataType);
  REAL8 DATA__GET(DATA *dat);
  void DATA__COPY(DATA *dst,
                  INT1  type,
                  void *data_ptr);


  // ***********************************
  // CDFメタデータ
  // ***********************************
  typedef struct{
    char  attrName [CDF_ATTR_NAME_LEN256 + 1];
    char  entryType;//g/r/z  
    long  dataType;
    long  numElems;
    void *buffer;
  }CDFMETADATA;
  
  const char *CDF__DATATYPETEXT(long dataType); 
  size_t CDF__SIZEOF(long dataType);

  void CDF__DATA_SHOW_CHAR_       (CHAR        dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_UCHAR_      (UCHAR       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_BYTE_       (BYTE        dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_INT1_       (INT1        dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_INT2_       (INT2        dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_INT4_       (INT4        dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_INT8_       (INT8        dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_UINT1_      (UINT1       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_UINT2_      (UINT2       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_UINT4_      (UINT4       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_FLOAT_      (FLOAT       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_DOUBLE_     (DOUBLE      dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_REAL4_      (REAL4       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_REAL8_      (REAL8       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_EPOCH_      (EPOCH       dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_EPOCH16_    (EPOCH16     dat[],long numElems,FILE *fp);
  void CDF__DATA_SHOW_TIME_TT2000_(TIME_TT2000 dat[],long numElems,FILE *fp);

  void CDFMETADATA__SHOW      (CDFMETADATA *meta,
                               FILE        *fp);

  void CDFMETADATA__INITIALIZE(CDFMETADATA *meta,
                               CDFid        id,
                               long         attrNum,
                               long         entryNum);

  void CDFMETADATA__FINALIZE  (CDFMETADATA *meta);

  void CDF__SHOW_GATTRIBUTES(CDFid id,FILE *fp);
  void CDF__SHOW_RATTRIBUTES(CDFid id,FILE *fp);
  void CDF__SHOW_ZATTRIBUTES(CDFid id,FILE *fp);
  void CDFMETADATA__INITIALIZE_ZVAR_ATTR(CDFMETADATA *meta,
                                         CDFid        id,
                                         const CHAR  *zVarName,
                                         const CHAR  *attrName);
  
#ifdef __cplusplus
}
#endif

#endif
