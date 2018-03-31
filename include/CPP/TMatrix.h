#ifndef _TMATRIX_H_INCLUDE_
#define _TMATRIX_H_INCLUDE_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include"DATATYPE.h"

using namespace std;

template<typename TYPE> class TMatrix;
template<typename TYPE> TMatrix<TYPE>  operator  &(const TMatrix<TYPE> &,const int            );
template<typename TYPE> TMatrix<TYPE>  operator  &(const int            ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  &(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  |(const TMatrix<TYPE> &,const int            );
template<typename TYPE> TMatrix<TYPE>  operator  |(const int            ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  |(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> ostream       &operator <<(ostream&             ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator > (const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator > (const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator >=(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator >=(const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator < (const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator < (const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator <=(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator <=(const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> class TMatrix{
 protected:
  TYPE *dat;
  INT   row;
  INT   col;
 protected:
  static void initialize(TMatrix<TYPE> &A,
                         const INT      row,
                         const INT      col);
  static void finalize  (TMatrix<TYPE> &A);
  static void resize    (TMatrix<TYPE> &A,
                         const INT      row,
                         const INT      col);
  static void zerofill  (TMatrix<TYPE> &A);
  static void datacopy  (TMatrix<TYPE> &A,
                         const TYPE    *dat);  
 public:
  // *************************************************
  // コンストラクタ
  // *************************************************
  //row行col列の    行列を作成(0で初期化される)
  TMatrix(INT row,INT col);
  //dim行dim列の正方行列を作成(0で初期化される)
  TMatrix(TYPE  x) : TMatrix(1,1) {dat[0] = x;}
  //  1行  1列の    行列を作成(0で初期化される) 
  TMatrix()        : TMatrix(1,1) {}
  // *************************************************
  // コピーコンストラクタ
  // *************************************************
  TMatrix(const TMatrix<TYPE> &A);
  // *************************************************
  // デストラクタ
  // *************************************************
 ~TMatrix();

  // *************************************************
  // アクセッサ
  // *************************************************
  TYPE *get_dat()const{return this->dat;}//データポインタの取得
  INT   get_row()const{return this->row;}//行数          の取得
  INT   get_col()const{return this->col;}//列数          の取得

  // *************************************************
  // 確認
  // *************************************************
  INT  is_square(){return this->row == this->col;}
  operator TYPE                ()const{
    if((this->row != 1) || (this->col != 1)){
      ERROR__SHOW("#1");
      exit(EXIT_FAILURE);
    }
    return this->dat[0];
  }
  operator TMatrix<REAL>       ()const;
  operator TMatrix<TIME_TT2000>()const;
  
  // *************************************************
  // 演算子のオーバーロード
  // *************************************************
  TMatrix<TYPE>  &operator  =(const TMatrix<TYPE> &);
  TYPE           *operator [](const INT     n)const ;
  TMatrix<TYPE>  &operator &=(const TMatrix<TYPE> &);
  TMatrix<TYPE>  &operator |=(const TMatrix<TYPE> &);

  friend ostream  &operator <<(ostream&       ,const TMatrix<TYPE> &);
  
  friend TMatrix<TYPE>   operator  & <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  & <>(const TMatrix<TYPE> &,const INT            );
  friend TMatrix<TYPE>   operator  & <>(const INT            ,const TMatrix<TYPE> &);

  friend TMatrix<TYPE>   operator  | <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  | <>(const TMatrix<TYPE> &,const INT            );
  friend TMatrix<TYPE>   operator  | <>(const INT            ,const TMatrix<TYPE> &);

  friend TMatrix<INT>    operator >  <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<INT>    operator >  <>(const TYPE           ,const TMatrix<TYPE> &);

  friend TMatrix<INT>    operator >= <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<INT>    operator >= <>(const TYPE           ,const TMatrix<TYPE> &);

  friend TMatrix<INT>    operator <  <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<INT>    operator <  <>(const TYPE           ,const TMatrix<TYPE> &);

  friend TMatrix<INT>    operator <= <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<INT>    operator <= <>(const TYPE           ,const TMatrix<TYPE> &);

};

// *************************************************
// static private 関数群
// *************************************************

template<typename TYPE> 
void TMatrix<TYPE>::initialize(TMatrix<TYPE> &A,
                               const INT      row,
                               const INT      col){
  if(col <= 0 || row <= 0){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  if((A.dat = (TYPE*)malloc(sizeof(TYPE) * row * col)) == NULL){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);    
  }
  A.row = row;
  A.col = col;
}

template<typename TYPE> 
void TMatrix<TYPE>::finalize  (TMatrix<TYPE> &A){
  free(A.dat);
}

template<typename TYPE> 
void TMatrix<TYPE>::resize    (TMatrix<TYPE> &A,
                               const INT      row,
                               const INT      col){
  if(col <= 0 || row <= 0){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  if((A.row * A.col) != (row * col)){
    TMatrix<TYPE>::finalize  (A);
    TMatrix<TYPE>::initialize(A,row,col);
  }
  A.row = row;
  A.col = col;  
}

template<typename TYPE> 
void TMatrix<TYPE>::zerofill  (TMatrix<TYPE> &A){
  memset(A.dat,0x00,sizeof(TYPE) * A.row * A.col);    
}

template<typename TYPE> 
void TMatrix<TYPE>::datacopy  (TMatrix<TYPE> &A,
                               const TYPE    *dat){
  if(dat == NULL){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  memcpy(A.dat, dat,sizeof(TYPE) * A.row * A.col);  
}

// *************************************************
// コンストラクタ
// *************************************************
template<typename TYPE> 
TMatrix<TYPE>::TMatrix(INT row,INT col){
  TMatrix<TYPE>::initialize(*this,row,col);
  TMatrix<TYPE>::zerofill  (*this);
}

// *************************************************
// コピーコンストラクタ
// *************************************************
template<typename TYPE> 
TMatrix<TYPE>::TMatrix(const TMatrix<TYPE> &A){
  TMatrix<TYPE>::initialize(*this,A.row,A.col);
  TMatrix<TYPE>::datacopy  (*this,A.dat);
}

// *************************************************
// デストラクタ
// *************************************************
template<typename TYPE> 
TMatrix<TYPE>::~TMatrix(){
  TMatrix<TYPE>::finalize(*this);
}

// *************************************************
// 代入演算子
// *************************************************
template<typename TYPE> 
TMatrix<TYPE> &TMatrix<TYPE>::operator  =(const TMatrix<TYPE> &A){
  TMatrix<TYPE>::resize  (*this,A.row,A.col);
  TMatrix<TYPE>::datacopy(*this,A.dat);
  return *this;
}

// *************************************************
// 配列演算子
// *************************************************
template<typename TYPE>
TYPE          *TMatrix<TYPE>::operator [](const INT n)const{
  return &this->dat[n * this->col];
}

// *************************************************
// 縦結合演算子
// *************************************************
template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator &=(const TMatrix<TYPE> &A){
  return *this = *this & A;
}

// *************************************************
// 横結合演算子
// *************************************************
template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator |=(const TMatrix<TYPE> &A){
  return *this = *this | A;
}

template<typename TYPE>
TMatrix<INT>  operator > (const TMatrix<TYPE> &A,const TYPE     b){
  TMatrix<INT> C(A.row,A.col);
  INT          i,j;

  for(i = 0;i < C.get_row();i++){
    for(j = 0;j < C.get_col();j++){
      C[i][j] = (A.dat[i * A.col + j] >  b) ? 1 : 0;
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<INT>  operator > (const TYPE           a,const TMatrix<TYPE> &B){
  return B <  a;
}

template<typename TYPE>
TMatrix<INT>  operator >=(const TYPE           a,const TMatrix<TYPE> &B){
  return B <= a;
}

template<typename TYPE>
TMatrix<INT>  operator < (const TYPE           a,const TMatrix<TYPE> &B){
  return B >  a;
}

template<typename TYPE>
TMatrix<INT>  operator <=(const TYPE           a,const TMatrix<TYPE> &B){
  return B >= a;
}

template<typename TYPE>
TMatrix<INT>  operator >=(const TMatrix<TYPE> &A,const TYPE     b){
  TMatrix<INT> C(A.row,A.col);
  INT          i,j;

  for(i = 0;i < C.get_row();i++){
    for(j = 0;j < C.get_col();j++){
      C[i][j] = (A.dat[i * A.col + j] >= b) ? 1 : 0;
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<INT>  operator < (const TMatrix<TYPE> &A,const TYPE     b){
  TMatrix<INT> C(A.row,A.col);
  INT          i,j;

  for(i = 0;i < C.get_row();i++){
    for(j = 0;j < C.get_col();j++){
      C[i][j] = (A.dat[i * A.col + j] <  b) ? 1 : 0;
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<INT>  operator <=(const TMatrix<TYPE> &A,const TYPE     b){
  TMatrix<INT> C(A.row,A.col);
  INT          i,j;

  for(i = 0;i < C.get_row();i++){
    for(j = 0;j < C.get_col();j++){
      C[i][j] = (A.dat[i * A.col + j] <= b) ? 1 : 0;
    }
  }
  return C;
}

// *************************************************
// 出力
// *************************************************
ostream &operator <<(ostream &os,const TMatrix<INT> &A){
  CHAR str[256];
  INT  i,j;

  os << "=============(" << A.row << "," << A.col << ")=============" << endl;  
  for(i = 0;i < A.row;i++){
    os << "| "; 
    for(j = 0;j < A.col;j++){
      sprintf(str,"%5d ",A.dat[i * A.col + j]);
      os << str;
    }
    os << "|" << endl;
  }
  
  return os;
}

// *************************************************
// 縦結合演算子
// *************************************************
template<typename TYPE>
TMatrix<TYPE> operator &(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  TMatrix<TYPE> C(A.row + B.row,A.col);
  INT     i,j;
  
  if(A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < A.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[ i          * C.col + j] = A.dat[i * A.col + j];
    }
  }

  for(i = 0;i < B.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[(i + A.row) * C.col + j] = B.dat[i * B.col + j];
    }
  }
  return C;
}

// *************************************************
// i0行を抜き出す演算子
// *************************************************
template<typename TYPE>
TMatrix<TYPE>  operator &(const TMatrix<TYPE> &A,const INT     i0){
  TMatrix<TYPE> C(1,A.col);
  INT     j;
  
  if((i0 < 0) || (A.row <= i0)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(j = 0;j < C.col;j++){
    C.dat[j] = A.dat[i0 * A.col + j];
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator &(const INT     i0,const TMatrix<TYPE> &A){
  return A & i0;
}

// *************************************************
// 横結合演算子
// *************************************************
template<typename TYPE>
TMatrix<TYPE>  operator |(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  TMatrix<TYPE> C(A.row,A.col + B.col);
  INT     i,j;
  
  if(A.row != B.row){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < C.row;i++){
    for(j = 0;j < A.col;j++){
      C.dat[i * C.col +  j         ] = A.dat[i * A.col + j];
    }
    for(j = 0;j < B.col;j++){
      C.dat[i * C.col + (j + A.col)] = B.dat[i * B.col + j];
    }
  }
  return C;
}

// *************************************************
// j0列を抜き出す演算子
// *************************************************
template<typename TYPE>
TMatrix<TYPE>  operator |(const TMatrix<TYPE> &A,const INT     j0){
  TMatrix<TYPE> C(A.row,1);
  INT     i;
  
  if((j0 < 0) || (A.col <= j0)){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < A.row;i++){
    C.dat[i] = A.dat[i * A.col + j0];
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator |(const INT     j0,const TMatrix<TYPE> &A){
  return A | j0;
}

class IMatrix : public TMatrix<INT>{
 public:
  using TMatrix<INT>::TMatrix;
};

// *************************************************
// 出力
// *************************************************
ostream &operator <<(ostream     &os,const TMatrix<REAL> &A){
  CHAR str[256];
  INT  i,j;
  
  os << "=============(" << A.row << "," << A.col << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    os << "| "; 
    for(j = 0;j < A.get_col();j++){
      sprintf(str,(A[i][j] >= 0.0) ? "+%10.5lf " : "-%10.5lf ",fabs(A[i][j]));
      os << str;
    }
    os << "|" << endl;
  }
  
  return os;
}

ostream &operator <<(ostream     &os,const TMatrix<DATA> &A){
  CHAR str[256];
  INT  i,j;
  
  os << "=============(" << A.row << "," << A.col << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    os << "| "; 
    for(j = 0;j < A.get_col();j++){
      DATA__WRITE(&A[i][j],stderr);
      os << " ";
    }
    os << "|" << endl;
  }
  
  return os;
}

void show(const TMatrix<REAL> &A){
  CHAR str[256];
  INT  i,j;
  
  cerr << "=============(" << A.get_row() << "," << A.get_col() << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    cerr << "| "; 
    for(j = 0;j < A.get_col();j++){
      sprintf(str,(A[i][j] >= 0.0) ? "+%10.5lf " : "-%10.5lf ",fabs(A[i][j]));
      cerr << str;
    }
    cerr << "|" << endl;
  }  
}

void show(const TMatrix<REAL> &A,const TMatrix<INT> &M){
  CHAR str[256];
  INT  i,j;
  
  cerr << "=============(" << A.get_row() << "," << A.get_col() << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    cerr << "| "; 
    for(j = 0;j < A.get_col();j++){
      if(M[i][j] == 1){
        cerr << "\x1b[36m";
      }
      sprintf(str,(A[i][j] >= 0.0) ? "+%10.5lf " : "-%10.5lf ",fabs(A[i][j]));
      cerr << str;
      if(M[i][j] == 1){
        cerr << "\x1b[39m";
      }
    }
    cerr << "|" << endl;
  }  
}


template<typename TYPE> class TVector : public TMatrix<TYPE>{
 public:
  //create a ( 1 )-dimensional zero vector
  TVector()                   : TMatrix<TYPE>(1,1){}
  
  //create a (dim)-dimensional zero vector
  TVector(int dim)            : TMatrix<TYPE>(dim,1){}

  //copy constructor
  TVector(const TMatrix<TYPE> &A);
  
  //get dimension of a vector
  int dim()const{return this->row;}
  
  //operator overloading
  TYPE          &operator [](const int n)const{return this->dat[n];}
  TVector<TYPE> &operator  =(const TMatrix<TYPE> &);
};

template<typename TYPE> 
TVector<TYPE>::TVector(const TMatrix<TYPE> &A){
  if(A.col() != 1){
    cerr << "Error : TVector.TVector(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  this->col =       1;
  this->row = A.row();
  this->dat = new TYPE[this->row];
  memcpy(this->dat,A.get_dat(),this->row * sizeof(TYPE));
}

template<typename TYPE> 
TVector<TYPE> &TVector<TYPE>::operator  =(const TMatrix<TYPE> &A){
  if(A.get_col() != 1){
    cerr << "Error : TVector.=(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  if(this->row != A.get_row()){ 
    delete [] this->D;
    this->col =       1;
    this->row = A.row();
    this->dat = new TYPE[this->row];
  }
  memcpy(this->dat,A.get_dat(),this->row * sizeof(TYPE));
  return *this;
}

class DMatrix : public TMatrix<T2000>{
 public:
  using TMatrix<T2000>::TMatrix;
};


void show(const TMatrix<T2000> &A){
  CHAR str[256];
  INT  i,j;
  
  cerr << "=============(" << A.get_row() << "," << A.get_col() << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    cerr << "| "; 
    for(j = 0;j < A.get_col();j++){
      T2000__PRINT(A[i][j],stderr);
      cerr << " ";
    }
    cerr << "|" << endl;
  }  
}

void show(const TMatrix<DATA> &A){
  CHAR str[256];
  INT  i,j;
  
  cerr << "=============(" << A.get_row() << "," << A.get_col() << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    cerr << "| "; 
    for(j = 0;j < A.get_col();j++){
      DATA__WRITE(&A[i][j],stderr);
      cerr << " ";
    }
    cerr << "|" << endl;
  }  
}

void show(const TMatrix<T2000> &A,const TMatrix<INT> &M){
  CHAR str[256];
  INT  i,j;
  
  cerr << "=============(" << A.get_row() << "," << A.get_col() << ")=============" << endl;  
  for(i = 0;i < A.get_row();i++){
    cerr << "| "; 
    for(j = 0;j < A.get_col();j++){
      if(M[i][j] == 1){
        cerr << "\x1b[36m";
      }
      T2000__PRINT(A[i][j],stderr);
      cerr << " ";
      if(M[i][j] == 1){
        cerr << "\x1b[39m";
      }
    }
    cerr << "|" << endl;
  }  
}

DMatrix linspace(const CHAR *epoch_s,
                 const CHAR *epoch_e,
                 INT8        diff){
  DMatrix t;
  T2000   ts;
  T2000   te;
  INT4    num;
  INT4    i;

  ts  =  T2000__MAKE_FROM_TEXT(epoch_s);
  te  =  T2000__MAKE_FROM_TEXT(epoch_e);
  num = (te - ts) / diff;
  t   =  DMatrix(num,1);
  for(i = 0;i < num;i++){
    t[i][0] = ts + i * diff;
  }
  return t;
}

#define T2000__NSEC (               1LL)
#define T2000__USEC (1000 * T2000__NSEC)
#define T2000__MSEC (1000 * T2000__USEC)
#define T2000__SEC  (1000 * T2000__MSEC)
#define T2000__MIN  (  60 * T2000__SEC )
#define T2000__HOUR (  60 * T2000__MIN )
#define T2000__DAY  (  24 * T2000__HOUR)

//時刻の取得関数
void DMatrix__fetch(DMatrix    &t,
                    const char *varName,  //z変数名
                    const char *filename){//CDFファイル名  
  CDFid     id;
  CDFstatus status;
  long      varNum;
  long      numRecs;
  long      numDims;
  long      dimSizes[CDF_MAX_DIMS];
  long      numValues;
  int       i;
  
  //CDFファイルを開く
  status    = CDFopenCDF(filename,&id);
  //CDFのz変数名からz変数のIDを取得
  varNum    = CDFgetVarNum(id,(char*)varName);
  //CDFファイルに書かれたレコードの最大番号を取得
  status    = CDFgetzVarMaxWrittenRecNum(id,varNum,&numRecs);
  //z変数の次元を取得
  status    = CDFgetzVarNumDims(id,varNum,&numDims);
  //z変数の各次元の要素数を取得
  status    = CDFgetzVarDimSizes(id,varNum,dimSizes);
  //z変数の1レコード文の要素数を計算
  numValues = 1;
  for(i = 0;i < numDims;i++){
    numValues *= dimSizes[i];
  }

  //情報の表示  
  printf("numDims = %ld | numRecs = %ld\n",numDims,numRecs);
  printf("numValues = %d, numRecs = %d\n",(int)numValues,(int)numRecs);
  for(i = 0;i < numDims;i++){
    printf("%d %ld\n",i,dimSizes[i]);
  }

  //行列の初期化
  t = DMatrix((numRecs + 1) * numValues,1);
  
  status = CDFgetzVarAllRecordsByVarID(id,varNum,t.get_dat());
  
  CDFcloseCDF(id);
}


void RMatrix__fetch(TMatrix<REAL8> &A,
                    const char *varName,  //z変数名
                    const char *filename){//CDFファイル名  
  CDFid     id;
  CDFstatus status;
  long      varNum;
  long      numRecs;
  long      numDims;
  long      dimSizes[CDF_MAX_DIMS];
  long      numValues;
  int       i;

  //CDFファイルを開く
  status    = CDFopenCDF(filename,&id);
  //CDFのz変数名からz変数のIDを取得
  varNum    = CDFgetVarNum(id,(char*)varName);
  //CDFファイルに書かれたレコードの最大番号を取得
  status    = CDFgetzVarMaxWrittenRecNum(id,varNum,&numRecs);
  //z変数の次元を取得
  status    = CDFgetzVarNumDims(id,varNum,&numDims);
  //z変数の各次元の要素数を取得
  status    = CDFgetzVarDimSizes(id,varNum,dimSizes);
  //z変数の1レコード文の要素数を計算
  numValues = 1;
  for(i = 0;i < numDims;i++){
    numValues *= dimSizes[i];
  }

  //情報の表示
  printf("numDims = %ld | numRecs = %ld\n",numDims,numRecs);
  printf("numValues = %d, numRecs = %d\n",(int)numValues,(int)numRecs);
  for(i = 0;i < numDims;i++){
    printf("%d %ld\n",i,dimSizes[i]);
  }
  A = TMatrix<REAL8>(numRecs + 1,numValues);
  status = CDFgetzVarAllRecordsByVarID(id,varNum,A.get_dat());

  CDFcloseCDF(id);
}

void Matrix__fetch(TMatrix<DATA> &A,
                    const char    *varName,  //z変数名
                    const char    *filename){//CDFファイル名  
  CDFid     id;
  CDFstatus status;
  long      varNum;
  long      numRecs;
  long      numDims;
  long      dimSizes[CDF_MAX_DIMS];
  long      numValues;
  long      dataType;
  long      dataSize;
  BYTE     *buffer;
  int       i,j;

  //CDFファイルを開く
  status    = CDFopenCDF(filename,&id);
  //CDFのz変数名からz変数のIDを取得
  varNum    = CDFgetVarNum(id,(char*)varName);
  //CDFファイルに書かれたレコードの最大番号を取得
  status    = CDFgetzVarMaxWrittenRecNum(id,varNum,&numRecs);
  //z変数の次元を取得
  status    = CDFgetzVarNumDims(id,varNum,&numDims);
  //z変数の各次元の要素数を取得
  status    = CDFgetzVarDimSizes(id,varNum,dimSizes);
  //z変数の1レコード文の要素数を計算
  numValues = 1;
  for(i = 0;i < numDims;i++){
    numValues *= dimSizes[i];
  }
  status = CDFgetzVarDataType(id,varNum,&dataType);
  CDFgetDataTypeSize(dataType,&dataSize);
  //情報の表示
  printf("numDims = %ld | numRecs = %ld\n",numDims,numRecs);
  printf("numValues = %d, numRecs = %d\n",(int)numValues,(int)numRecs);
  for(i = 0;i < numDims;i++){
    printf("%d %ld\n",i,dimSizes[i]);
  }
  if((buffer = (BYTE*)malloc(dataSize * (numRecs + 1) * numValues)) == NULL){
    exit(EXIT_FAILURE);
  }
  A = TMatrix<DATA>(numRecs + 1,numValues);
  status = CDFgetzVarAllRecordsByVarID(id,varNum,buffer);
  for(i = 0;i <= numRecs;i++){
    for(j = 0;j < numValues;j++){
      DATA__COPY(&A[i][j],DATA__GET_DATATYPE(dataType),buffer + (i * numValues + j) * dataSize);
    }
  }
  free(buffer);
  
  CDFcloseCDF(id);
}

template<>
TMatrix<DATA>::operator TMatrix<REAL>       ()const{
  TMatrix<REAL> C(this->row,this->col);
  INT           i,j;
  
  for(i = 0;i < this->row;i++){
    for(j = 0;j < this->col;j++){
      C[i][j] = DATA__GET(&this->dat[i * this->col + j]);
    }
  }
  return C;
}

template<>
TMatrix<DATA>::operator TMatrix<TIME_TT2000>()const{
  TMatrix<TIME_TT2000> C(this->row,this->col);
  INT                  i,j;
  
  for(i = 0;i < this->row;i++){
    for(j = 0;j < this->col;j++){
      C[i][j] = this->dat[i * this->col + j].data._time_tt2000;
    }
  }
  return C;
}

#endif
