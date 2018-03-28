#ifndef _STRINGS_H_INCLUDE_
#define _STRINGS_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"DATATYPE.h"

class STRING{
protected:
  CHAR *dat;
  CHAR  nul;
protected:
  static void initialize(STRING &str,const INT4  num){
    if(num == 1){
      str.dat = &str.nul;
    }else{
      str.dat = (CHAR*)malloc(num);
      if(str.dat == NULL){
        ERROR__SHOW("#1");
        exit(EXIT_FAILURE);
      }
      memset(str.dat,' ',num - 1);
      str.dat[num - 1] = '\0';
    }
    str.nul = '\0';
  }
  static void initialize(STRING &str,const CHAR *dat){
    STRING::initialize(str,strlen(dat) + 1);
    if(str.dat != &str.nul){
      strcpy(str.dat,dat);
    }
  }
  static void finalize  (STRING &str){
    if(str.dat != &str.nul){
      free(str.dat);
      str.dat = &str.nul;
      str.nul = '\0';
    }
  }
public:
  static void show      (STRING &str,FILE *fp){
    fprintf(fp    ,"%s",str.dat);
  }
  static void show      (STRING &str){
    fprintf(stdout,"%s",str.dat);
  }
public:
  // *************************************************
  // コンストラクタ
  // *************************************************
  STRING(){
    STRING::initialize(*this,      1);
  }
  STRING(const INT4    num){
    STRING::initialize(*this,    num);
  }  
  STRING(const CHAR   *dat){
    STRING::initialize(*this,    dat);
  }  
  // *************************************************
  // コピーコンストラクタ
  // *************************************************
  STRING(const STRING &str){
    STRING::initialize(*this,str.dat);
  }
  // *************************************************
  // デストラクタ
  // *************************************************
 ~STRING(){
    STRING::finalize  (*this);
  }
  // *************************************************
  // 出力
  // *************************************************
  void show(FILE *fp){
    STRING::show      (*this,fp);
  }
  void show(){
    STRING::show      (*this);
  }

  // *************************************************
  // 演算子のオーバーロード
  // *************************************************
  STRING  &operator  =(const STRING &str){
    STRING::finalize  (*this);
    STRING::initialize(*this,str.dat);
    return *this;
  }
  STRING  &operator  =(const CHAR   *dat){
    *this = STRING(dat);
    return *this;
  }
  CHAR    &operator [](const INT n)const{
    return this->dat[n];
  }

  STRING  &operator +=(const STRING &str){
    return *this = *this + str;
  }
  STRING  &operator +=(const CHAR   *dat){
    return *this = *this + STRING(dat);
  }

  friend STRING operator +(const STRING &str1,const STRING &str2){
    STRING str;
    INT4   len1;
    INT4   len2;

    len1 = strlen(str1.dat);
    len2 = strlen(str2.dat);    
    str  = STRING(len1 + len2 + 1);
    if(str.dat != &str.nul){    
      strcpy(&str.dat[   0],str1.dat);
      strcpy(&str.dat[len1],str2.dat);
    }
    return str;
  }

  friend STRING operator +(const STRING &str1,const CHAR   *dat2){
    return        str1  + STRING(dat2);
  }

  friend STRING operator +(const CHAR   *dat1,const STRING &str2){
    return STRING(dat1) +        str2 ;
  }

};


#endif
