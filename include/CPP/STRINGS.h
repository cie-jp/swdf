#ifndef _STRINGS_H_INCLUDE_
#define _STRINGS_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"DATATYPE.h"

#include<iostream>

using namespace std;

namespace CLDIA{

  class STRING{
  protected:
    CHAR *dat;
    CHAR  nul;
  protected:
    static void initialize(STRING &str,const INT4  num,const CHAR ch){
      if(num == 1){
        str.dat = &str.nul;
      }else{
        str.dat = (CHAR*)malloc(num);
        if(str.dat == NULL){
          ERROR__SHOW("#1");
          exit(EXIT_FAILURE);
        }
        memset(str.dat,ch,num - 1);
        str.dat[num - 1] = '\0';
      }
      str.nul = '\0';
    }
    static void initialize(STRING &str,const CHAR *fmt,va_list args){
      va_list args_tmp;
      INT4    size = 2048;
      CHAR    buf[size];
      CHAR   *tmp;
      INT4    num;
      
      va_copy(args_tmp,args);
      num = vsnprintf(buf,size,fmt,args);
      
      if(num <    0){
        ERROR__SHOW("vsnprintf failed.");
        exit(EXIT_FAILURE);
      }
      num++;
      STRING::initialize(str,num,' ');
      if(num <= size){
        if(str.dat != &str.nul){
          strcpy(str.dat,buf);
        }
        va_end(args_tmp);
        return;
      }
      if((tmp = (CHAR*)malloc(num)) == NULL){
        ERROR__SHOW("Memory allocation failed.");
        exit(EXIT_FAILURE);
      }
      if(vsnprintf(tmp,num,fmt,args_tmp) < 0){
        ERROR__SHOW("vsnprintf failed.");
        exit(EXIT_FAILURE);
      }
      if(str.dat != &str.nul){
        strcpy(str.dat,tmp);
      }
      free(tmp);
      va_end(args_tmp);
    }
    static void initialize(STRING &str,const CHAR *dat){
      STRING::initialize(str,strlen(dat) + 1,' ');
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
      STRING::initialize(*this,      1,' ');
    }
    STRING(const INT4    num,const CHAR  ch ){
      STRING::initialize(*this,num + 1, ch);
    }
    STRING(const INT4    num,const CHAR *dat){
      STRING::initialize(*this,num + 1,' ');
      memcpy(this->dat,dat,num);      
    }
    STRING(const CHAR   *fmt,...){
      va_list args;
      
      va_start(args,fmt);
      STRING::initialize(*this,    fmt,args);
      va_end  (args);
    }
    STRING(const CHAR        val) : STRING("%c",val) {}
    STRING(const INT2        val) : STRING("%d",val) {}
    STRING(const INT4        val) : STRING("%d",val) {}
    STRING(const INT8        val) : STRING("%d",val) {}
    STRING(const REAL8       val) : STRING("%e",val) {}
    STRING(const TIME_TT2000 val){
      DTIME epoch;
      
      epoch = DTIME__MAKE_FROM_T2000(val);
      STRING::initialize(*this,    30, ' ');
      sprintf(this->dat,
              "%04d-%02d-%02d %02d:%02d:%02d.%03d%03d%03d",
              epoch.YYYY,
              epoch.MM,
              epoch.DD,
              epoch.hh,
              epoch.mm,
              epoch.ss,
              epoch.msec,
              epoch.usec,
              epoch.nsec);
    }
    // *************************************************
    // コピーコンストラクタ
    // *************************************************
    STRING(const STRING  &str){
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
    bool operator==(const STRING &str){return strcmp(this->dat,str.dat) == 0;}
    bool operator!=(const STRING &str){return strcmp(this->dat,str.dat) != 0;}
    bool operator>=(const STRING &str){return strcmp(this->dat,str.dat) >= 0;}
    bool operator<=(const STRING &str){return strcmp(this->dat,str.dat) <= 0;}
    bool operator> (const STRING &str){return strcmp(this->dat,str.dat) >  0;}
    bool operator< (const STRING &str){return strcmp(this->dat,str.dat) <  0;}
    
    friend ostream  &operator <<(ostream &os,const STRING &str){
      os << str.dat;
      return os;
    }
    
    operator        CHAR()const{return             this->dat[0];}
    operator        INT4()const{return ( INT4)atof(this->dat  );}
    operator       REAL8()const{return (REAL8)atof(this->dat  );}
    operator TIME_TT2000()const{return T2000__MAKE_FROM_TEXT(this->dat);}
    STRING  &operator  =(const STRING  &str){
      STRING::finalize  (*this);
      STRING::initialize(*this,str.dat);
      return *this;
    }
    STRING  &operator  =(      STRING &&str){
      this->dat =  str.dat;
      this->nul =     '\0';
      str.dat   = &str.nul;
      str.nul   =     '\0';
      return *this;
    }
    STRING  &operator  =(const CHAR    *dat){
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
      str  = STRING(len1 + len2 + 1,' ');
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

}

namespace CLDIA{
  size_t strlen(const STRING &str){
    return std::strlen((const CHAR*)&str[0]);
  }
}


#endif
