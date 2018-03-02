/*****************************************************************
 * 
 * CDF操作関連ライブラリ
 *
 *                           Modified by Mamoru Ota (2017/12/12)
 *                           Modified by Mamoru Ota (2017/06/08)
 *                           Created  by Mamoru Ota (2017/06/03)
 *
 *****************************************************************/ 

#ifndef _CDF_COMMON_H_INCLUDE_
#define _CDF_COMMON_H_INCLUDE_

#include<stdio.h>
#include"cdf.h"
#include"DATATYPE.h"

#ifdef __cplusplus
extern "C" {
#endif

  // ***********************************
  // CDFデータ型宣言
  // ***********************************
  typedef CHAR        CDF__CHAR       ; //    1-byte,   signed character.
  typedef UCHAR       CDF__UCHAR      ; //    1-byte, unsigned character.
  typedef BYTE        CDF__BYTE       ; //    1-byte,   signed integer.
  typedef INT1        CDF__INT1       ; //    1-byte,   signed integer.
  typedef INT2        CDF__INT2       ; //    2-byte,   signed integer.
  typedef INT4        CDF__INT4       ; //    4-byte,   signed integer.
  typedef INT8        CDF__INT8       ; //    8-byte,   signed integer.
  typedef UINT1       CDF__UINT1      ; //    1-byte, unsigned integer.
  typedef UINT2       CDF__UINT2      ; //    2-byte, unsigned integer.
  typedef UINT4       CDF__UINT4      ; //    4-byte, unsigned integer.
  typedef FLOAT       CDF__FLOAT      ; //    4-byte, floating point.
  typedef DOUBLE      CDF__DOUBLE     ; //    8-byte, floating point.
  typedef REAL4       CDF__REAL4      ; //    4-byte, floating point.
  typedef REAL8       CDF__REAL8      ; //    8-byte, floating point.
  typedef EPOCH       CDF__EPOCH      ; //    8-byte, floating point.
  typedef EPOCH16     CDF__EPOCH16[2] ; //two 8-byte, floating point.
  typedef TIME_TT2000 CDF__TIME_TT2000; //    8-byte,   signed integer.

  // ***********************************
  // 新規ディレクトリを作成する 
  // ***********************************
  void CDF__Make_Directory(const char *dirname);
  
  // ***********************************
  // CDFファイル操作の各種エラーメッセージを出力する
  // ***********************************
  void CDF__Status_Handler(CDFstatus status);

  // ***********************************
  // CDFデータタイプのバイト数を検証する
  // ***********************************
  void CDF__Check_DataType();

  // ***********************************
  // CDFライブラリの基本情報を出力する
  // ***********************************
  void CDF__Show_Library_Info(FILE *fp);

  // ***********************************
  // CDFファイル操作の基本情報を出力する
  // ***********************************
  void CDF__Show_Info  (CDFid id,FILE *fp);
  
  // ***********************************
  // CDFファイルを新規作成する
  // ***********************************
  void CDF__Create     (CDFid *id_ptr,const char *filename);

  // ***********************************
  // CDFファイルを削除する
  // ***********************************
  void CDF__Delete     (CDFid *id_ptr);
  
  // ***********************************
  // CDFファイルを開く
  // ***********************************
  long CDF__Open       (CDFid *id_ptr, const char *filename);
  
  // ***********************************
  // CDFファイルを閉じる
  // ***********************************
  void CDF__Close      (CDFid *id_ptr);

  // ***********************************
  // CDFファイルのg属性attrNameを記述する
  // ***********************************
  void CDF__Set_gAttr  (CDFid id,const char *attrName,const char *text);

  // ***********************************
  // CDFファイルのg属性Generated_timeを作成する
  // ***********************************
  void CDF__Set_gAttr_Generated_time(CDFid id);

  // ***********************************
  // CDFファイルのg属性attrNameを取得する
  // ***********************************
  void CDF__Get_gAttr  (CDFid id,const char *attrName,      char *text,int num);

  // ***********************************
  // CDFファイルのg属性attrNameの内容を検証する
  // ***********************************
  int  CDF__Check_gAttr(CDFid id,const char *attrName,const char *text);
  
  // ***********************************
  // CDFファイルのv属性attrNameを記述する
  // ***********************************
  void CDF__Set_vAttr  (CDFid id,const char *attrName); 
  
  // ***********************************
  // CDFファイルのz変数varNameのv属性attrNameの格納値を記述する
  // ***********************************
  void CDF__Set_zVar_vAttr            (CDFid id,const char *varName,const char *attrName,void             *value,long dataType,long elemNum);
  void CDF__Set_zVar_vAttr_CHAR       (CDFid id,const char *varName,const char *attrName,CDF__CHAR         value);
  void CDF__Set_zVar_vAttr_CHARS      (CDFid id,const char *varName,const char *attrName,const CDF__CHAR  *value);
  void CDF__Set_zVar_vAttr_UCHAR      (CDFid id,const char *varName,const char *attrName,CDF__UCHAR        value);
  void CDF__Set_zVar_vAttr_UCHARS     (CDFid id,const char *varName,const char *attrName,const CDF__UCHAR *value);
  void CDF__Set_zVar_vAttr_BYTE       (CDFid id,const char *varName,const char *attrName,CDF__BYTE         value);
  void CDF__Set_zVar_vAttr_INT1       (CDFid id,const char *varName,const char *attrName,CDF__INT1         value);
  void CDF__Set_zVar_vAttr_INT2       (CDFid id,const char *varName,const char *attrName,CDF__INT2         value);
  void CDF__Set_zVar_vAttr_INT4       (CDFid id,const char *varName,const char *attrName,CDF__INT4         value);
  void CDF__Set_zVar_vAttr_INT8       (CDFid id,const char *varName,const char *attrName,CDF__INT8         value);
  void CDF__Set_zVar_vAttr_UINT1      (CDFid id,const char *varName,const char *attrName,CDF__UINT1        value);
  void CDF__Set_zVar_vAttr_UINT2      (CDFid id,const char *varName,const char *attrName,CDF__UINT2        value);
  void CDF__Set_zVar_vAttr_UINT4      (CDFid id,const char *varName,const char *attrName,CDF__UINT4        value);
  void CDF__Set_zVar_vAttr_FLOAT      (CDFid id,const char *varName,const char *attrName,CDF__FLOAT        value);
  void CDF__Set_zVar_vAttr_DOUBLE     (CDFid id,const char *varName,const char *attrName,CDF__DOUBLE       value);
  void CDF__Set_zVar_vAttr_REAL4      (CDFid id,const char *varName,const char *attrName,CDF__REAL4        value);
  void CDF__Set_zVar_vAttr_REAL8      (CDFid id,const char *varName,const char *attrName,CDF__REAL8        value);
  void CDF__Set_zVar_vAttr_EPOCH      (CDFid id,const char *varName,const char *attrName,CDF__EPOCH        value);
  void CDF__Set_zVar_vAttr_EPOCH16    (CDFid id,const char *varName,const char *attrName,CDF__EPOCH16      value);
  void CDF__Set_zVar_vAttr_TIME_TT2000(CDFid id,const char *varName,const char *attrName,CDF__TIME_TT2000  value);

  // ***********************************
  // CDFファイルのz変数のpadValueを取得する
  // ***********************************
  void CDF__Get_zVar_padValue         (CDFid id,const char *varName,void       *padValue); 

#ifdef __cplusplus
}
#endif

#endif
