#ifndef _TMATRIX_H_INCLUDE_
#define _TMATRIX_H_INCLUDE_

#define MACRO_MIN(x,y) (((x) <= (y)) ? (x) : (y))

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include"DATATYPE.h"

using namespace std;

template<typename TYPE> class TMatrix;
template<typename TYPE> ostream       &operator <<(ostream&             ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  &(const TMatrix<TYPE> &,const int            );
template<typename TYPE> TMatrix<TYPE>  operator  &(const int            ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  &(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  |(const TMatrix<TYPE> &,const int            );
template<typename TYPE> TMatrix<TYPE>  operator  |(const int            ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  |(const TMatrix<TYPE> &,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator > (const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator > (const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator >=(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator >=(const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator < (const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator < (const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<INT>   operator <=(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<INT>   operator <=(const TYPE           ,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<TYPE>  operator  +(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  +(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  +(const TYPE           ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  +(const TMatrix<TYPE> &,const TYPE           );

template<typename TYPE> TMatrix<TYPE>  operator  -(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  -(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  -(const TYPE           ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  -(const TMatrix<TYPE> &,const TYPE           );

template<typename TYPE> TMatrix<TYPE>  operator  *(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  *(const TYPE           ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  *(const TMatrix<TYPE> &,const TYPE           );

template<typename TYPE> TMatrix<TYPE>  operator  %(const TMatrix<TYPE> &,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<TYPE>  operator  /(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<TYPE>  operator  /(const TMatrix<TYPE> &,const TMatrix<TYPE> &);

template<typename TYPE> TMatrix<TYPE>  operator  ~(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  !(const TMatrix<TYPE> &);                

namespace CLDIA{
  // *************************************************
  // 縦ベクトルの場合 : 縦ベクトル要素を対角成分に持つ対角行列を返す
  // 正方行列  の場合 : 非対角成分を0にした行列を返す
  // *************************************************
  // row行col列の単位行列(対角成分に1, 非対角成分に0をもつ行列)を返す.
  void eye (TMatrix<REAL> &E,
           const INT      row,
           const INT      col);
  // dim次の単位行列を返す.
  void eye (TMatrix<REAL> &E,
           const INT      dim);
  // dim次のヒルベルト行列を返す. 
  void hilb(TMatrix<REAL> &H,
            const INT     dim);
  
  template<typename TYPE> TMatrix<TYPE> diag (const TMatrix<TYPE> &A  );

  template<typename TYPE> TYPE          trace(const TMatrix<TYPE> &A  );

  template<typename TYPE> TYPE          cond (const TMatrix<TYPE> &A  );

  template<typename TYPE> TYPE          det  (const TMatrix<TYPE> &A  );
  template<typename TYPE> TYPE          det_lu(const TMatrix<TYPE> &A  );

  void          svd  (      TMatrix<REAL> &s,
                            TMatrix<REAL> &U,
                            TMatrix<REAL> &V,
                      const TMatrix<REAL> &A);
  void          svd  (      TMatrix<COMP> &s,
                            TMatrix<COMP> &U,
                            TMatrix<COMP> &V,
                      const TMatrix<COMP> &A);
  void          lu   (      TMatrix<REAL> &L,
                            TMatrix<REAL> &U,
                      const TMatrix<REAL> &A);
}

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
  INT  is_square()const{return this->row == this->col;}
  operator TYPE                ()const{
    if((this->row != 1) || (this->col != 1)){
      ERROR__SHOW("#1");
      exit(EXIT_FAILURE);
    }
    return this->dat[0];
  }
  operator TMatrix<REAL>       ()const;
  operator TMatrix<COMP>       ()const;
  operator TMatrix<TIME_TT2000>()const;
  
  // *************************************************
  // 演算子のオーバーロード
  // *************************************************
  TMatrix<TYPE>  &operator  =(const TMatrix<TYPE> &);
  TYPE           *operator [](const INT     n)const ;
  TMatrix<TYPE>  &operator &=(const TMatrix<TYPE> &);
  TMatrix<TYPE>  &operator |=(const TMatrix<TYPE> &);

  friend ostream        &operator << <>(ostream&             ,const TMatrix<TYPE> &);
  
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
  
  TMatrix<TYPE> &operator +=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator +=(const TYPE           );

  TMatrix<TYPE> &operator -=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator -=(const TYPE           );

  TMatrix<TYPE> &operator *=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator *=(const TYPE           );

  TMatrix<TYPE> &operator %=(const TMatrix<TYPE> &);

  TMatrix<TYPE> &operator /=(const TYPE           );
  TMatrix<TYPE> &operator /=(const TMatrix<TYPE> &);

  friend TMatrix<TYPE>   operator  + <>(const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  + <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  + <>(const TYPE           ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  + <>(const TMatrix<TYPE> &,const TYPE           );

  friend TMatrix<TYPE>   operator  - <>(const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  - <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  - <>(const TYPE           ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  - <>(const TMatrix<TYPE> &,const TYPE           );

  friend TMatrix<TYPE>   operator  * <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  * <>(const TYPE           ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  * <>(const TMatrix<TYPE> &,const TYPE           );

  friend TMatrix<TYPE>   operator  % <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);

  friend TMatrix<TYPE>   operator  / <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<TYPE>   operator  / <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);

  friend TMatrix<TYPE>   operator  ~ <>(const TMatrix<TYPE> &);
  friend TMatrix<TYPE>   operator  ! <>(const TMatrix<TYPE> &);

  // *************************************************
  // 単位行列の作成(対角成分 = 1, 非対角成分 = 0)
  // *************************************************
  static TMatrix<TYPE> identity(const INT row,const INT col);

  // *************************************************
  // 標準正規分布に従う乱数を与えた行列の作成
  // *************************************************
  static TMatrix<TYPE> random  (const INT row,const INT col);
  
  // *************************************************
  // 特異値分解
  // *************************************************
  void svd(TMatrix<TYPE> &s,TMatrix<TYPE> &U,TMatrix<TYPE> &V);

  TMatrix<TYPE> diag (){return CLDIA::diag (*this);}
  TYPE          trace(){return CLDIA::trace(*this);}

  //operator CMatrix()const;
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
template<>
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
template<>
ostream &operator <<(ostream     &os,const TMatrix<REAL> &A){
  CHAR str[256];
  INT  i,j;
  
  os << "=============(" << A.row << "," << A.col << ")=============" << endl;  
  for(i = 0;i < A.row;i++){
    os << "| "; 
    for(j = 0;j < A.col;j++){
      sprintf(str,"%+10.5f ",fabs(A.dat[i * A.col + j]));
      os << str;
    }
    os << "|" << endl;
  }
  
  return os;
}

template<>
ostream &operator <<(ostream     &os,const TMatrix<COMP> &A){
  CHAR str[256];
  INT  i,j;

  os << "=============(" << A.row << "," << A.col << ")=============" << endl;  
  for(i = 0;i < A.row;i++){
    os << "| "; 
    for(j = 0;j < A.col;j++){
      sprintf(str,"(%+10.5lf,%+10.5lf) ",COMPLEX__REAL(A.dat[i * A.col + j]),COMPLEX__IMAG(A.dat[i * A.col + j]));
      os << str;
    }
    os << "|" << endl;
  }
  
  return os;
}

template<>
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
  TVector()                   : TMatrix<TYPE>(  1,1){}
  
  //create a (dim)-dimensional zero vector
  TVector(int dim)            : TMatrix<TYPE>(dim,1){}

  //copy constructor
  TVector(const TMatrix<TYPE> &A);
  
  //get dimension of a vector
  INT get_dim()const{return this->row;}

  static TVector<TYPE> random(const INT dim){
    return TMatrix<TYPE>::random(dim,1);
  }
  
  //operator overloading
  TYPE          &operator [](const int n)const{return this->dat[n];}
  TVector<TYPE> &operator  =(const TMatrix<TYPE> &);
};

template<typename TYPE> 
TVector<TYPE>::TVector(const TMatrix<TYPE> &A){  
  if(A.get_col() != 1){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE>::initialize(*this,A.get_row(),A.get_col());
  TMatrix<TYPE>::datacopy  (*this,A.get_dat());
}

template<typename TYPE> 
TVector<TYPE> &TVector<TYPE>::operator  =(const TMatrix<TYPE> &A){
  if(A.get_col() != 1){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE>::initialize(*this,A.get_row(),A.get_col());
  TMatrix<TYPE>::datacopy  (*this,A.get_dat());
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
TMatrix<REAL>::operator TMatrix<COMP>       ()const{
  TMatrix<COMP> C(this->row,this->col);
  INT           i,j;
  
  for(i = 0;i < this->row;i++){
    for(j = 0;j < this->col;j++){
      C[i][j] = COMPLEX__MAKE_REAL(this->dat[i * this->col + j]);
    }
  }
  return C;
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


template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator +=(const TMatrix<TYPE> &B){return *this = *this + B;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator +=(const TYPE           b){return *this = *this + b;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator -=(const TMatrix<TYPE> &B){return *this = *this - B;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator -=(const TYPE           b){return *this = *this - b;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator *=(const TMatrix<TYPE> &B){return *this = *this * B;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator *=(const TYPE           b){return *this = *this * b;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator %=(const TMatrix<TYPE> &B){return *this = *this % B;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator /=(const TYPE           b){return *this = *this / b;}
template<typename TYPE> TMatrix<TYPE> &TMatrix<TYPE>::operator /=(const TMatrix<TYPE> &B){return *this = *this / B;}

// *************************************************
// 符号演算子(+)
// *************************************************
template<>
TMatrix<REAL>  operator +(const TMatrix<REAL> &A){
  return A;
}

template<>
TMatrix<COMP>  operator +(const TMatrix<COMP> &A){
  return A;
}

// *************************************************
// 加算演算子(行列 + 行列)
// *************************************************
template<>
TMatrix<REAL>  operator +(const TMatrix<REAL> &A,const TMatrix<REAL> &B){
  TMatrix<REAL> C = A;
  INT           i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] += B.dat[i * B.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator +(const TMatrix<COMP> &A,const TMatrix<COMP> &B){
  TMatrix<COMP> C = A;
  INT           i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j]  = COMP__ADD(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}

// *************************************************
// 加算演算子(  数 + 行列)
// *************************************************
template<>
TMatrix<REAL>  operator +(const REAL           a,const TMatrix<REAL> &B){
  TMatrix<REAL> C = B;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = a + C.dat[i * C.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator +(const COMP           a,const TMatrix<COMP> &B){
  TMatrix<COMP> C = B;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__ADD(a,C.dat[i * C.col + j]);
    }
  }
  return C;
}

// *************************************************
// 加算演算子(行列 +   数)
// *************************************************
template<>
TMatrix<REAL>  operator +(const TMatrix<REAL> &A,const REAL           b){
  TMatrix<REAL> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = C.dat[i * C.col + j] + b;
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator +(const TMatrix<COMP> &A,const COMP           b){
  TMatrix<COMP> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__ADD(C.dat[i * C.col + j],b);
    }
  }
  return C;
}

// *************************************************
// 符号演算子(-)
// *************************************************
template<>
TMatrix<REAL>  operator -(const TMatrix<REAL> &A){
  TMatrix<REAL> C = A;
  INT           i,j;
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = -C.dat[i * C.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator -(const TMatrix<COMP> &A){
  TMatrix<COMP> C = A;
  INT           i,j;
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__NEGATIVE(C.dat[i * C.col + j]);
    }
  }
  return C;
}

// *************************************************
// 減算演算子(行列 - 行列)
// *************************************************
template<>
TMatrix<REAL>  operator -(const TMatrix<REAL> &A,const TMatrix<REAL> &B){
  TMatrix<REAL> C = A;
  INT           i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] -= B.dat[i * B.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator -(const TMatrix<COMP> &A,const TMatrix<COMP> &B){
  TMatrix<COMP> C = A;
  INT           i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__SUB(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}

// *************************************************
// 減算演算子(  数 - 行列)
// *************************************************
template<>
TMatrix<REAL>  operator -(const REAL           a,const TMatrix<REAL> &B){
  TMatrix<REAL> C = B;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = a - C.dat[i * C.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator -(const COMP           a,const TMatrix<COMP> &B){
  TMatrix<COMP> C = B;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__SUB(a,C.dat[i * C.col + j]);
    }
  }
  return C;
}

// *************************************************
// 減算演算子(行列 -   数)
// *************************************************
template<>
TMatrix<REAL>  operator -(const TMatrix<REAL> &A,const REAL           b){
  TMatrix<REAL> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = C.dat[i * C.col + j] - b;
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator -(const TMatrix<COMP> &A,const COMP           b){
  TMatrix<COMP> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__SUB(C.dat[i * C.col + j],b);
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(行列 * 行列)
// *************************************************
template<>
TMatrix<REAL>  operator *(const TMatrix<REAL> &A,const TMatrix<REAL> &B){
  TMatrix<REAL> C(A.row,B.col);
  REAL          tmp;
  INT           i,j,k;
  
  if(A.col != B.row){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      tmp = 0.0;
      for(k = 0;k < A.col;k++){
        tmp += A.dat[i * A.col + k] * B.dat[k * B.col + j];
      }
      C.dat[i * C.col + j] = tmp;
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator *(const TMatrix<COMP> &A,const TMatrix<COMP> &B){
  TMatrix<COMP> C(A.row,B.col);
  COMP          tmp;
  INT           i,j,k;
  
  if(A.col != B.row){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      tmp = COMP__ZERO();
      for(k = 0;k < A.col;k++){
        tmp = COMP__FMA(A.dat[i * A.col + k],B.dat[k * B.col + j],tmp);
      }
      C.dat[i * C.col + j] = tmp;
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(  数 * 行列)
// *************************************************
template<>
TMatrix<REAL>  operator *(const REAL           a,const TMatrix<REAL> &B){
  TMatrix<REAL> C = B;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = a * C.dat[i * C.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator *(const COMP           a,const TMatrix<COMP> &B){
  TMatrix<COMP> C = B;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__MUL(a,C.dat[i * C.col + j]);
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(行列 *   数)
// *************************************************
template<>
TMatrix<REAL>  operator *(const TMatrix<REAL> &A,const REAL           b){
  TMatrix<REAL> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = C.dat[i * C.col + j] * b;
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator *(const TMatrix<COMP> &A,const COMP           b){
  TMatrix<COMP> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__MUL(C.dat[i * C.col + j],b);
    }
  }
  return C;
}

// *************************************************
// 乗算演算子(行列 % 行列) (要素ごとの乗算)
// *************************************************
template<>
TMatrix<REAL>  operator %(const TMatrix<REAL> &A,const TMatrix<REAL> &B){
  TMatrix<REAL> C = A;
  INT           i,j;

  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] *= B.dat[i * B.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator %(const TMatrix<COMP> &A,const TMatrix<COMP> &B){
  TMatrix<COMP> C = A;
  INT           i,j;

  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j]  = COMP__MUL(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}

// *************************************************
// 除算演算子(行列 /   数)
// *************************************************
template<>
TMatrix<REAL>  operator /(const TMatrix<REAL> &A,const REAL           b){
  TMatrix<REAL> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = C.dat[i * C.col + j] / b;
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator /(const TMatrix<COMP> &A,const COMP           b){
  TMatrix<COMP> C = A;
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__DIV(C.dat[i * C.col + j],b);
    }
  }
  return C;
}

// *************************************************
// 除算演算子(行列 / 行列) (要素ごとの乗算)
// *************************************************
template<>
TMatrix<REAL>  operator /(const TMatrix<REAL> &A,const TMatrix<REAL> &B){
  TMatrix<REAL> C = A;
  INT           i,j;

  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] /= B.dat[i * B.col + j];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator /(const TMatrix<COMP> &A,const TMatrix<COMP> &B){
  TMatrix<COMP> C = A;
  INT           i,j;

  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__DIV(C.dat[i * C.col + j],B.dat[i * B.col + j]);
    }
  }
  return C;
}

// *************************************************
// 随伴演算子(~)
// *************************************************
template<>
TMatrix<REAL>  operator ~(const TMatrix<REAL> &A){
  TMatrix<REAL> C(A.col,A.row);
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = A.dat[j * A.col + i];
    }
  }
  return C;
}

template<>
TMatrix<COMP>  operator ~(const TMatrix<COMP> &A){
  TMatrix<COMP> C(A.col,A.row);
  INT           i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = COMP__CONJ(A.dat[j * A.col + i]);
    }
  }
  return C;
}

// *************************************************
// 逆元演算子(!)
// *************************************************
template<>
TMatrix<REAL>  operator !(const TMatrix<REAL> &A){
  TMatrix<REAL> C = A;

  if(A.row != A.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  if(REAL__MATRIX_INV(C.dat,C.row) == -1){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);
  }
  return C;
}

template<>
TMatrix<COMP>  operator !(const TMatrix<COMP> &A){
  TMatrix<COMP> C = A;

  if(A.row != A.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  if(COMP__MATRIX_INV(C.dat,C.row) == -1){
    ERROR__SHOW("#2");
    exit(EXIT_FAILURE);
  }
  return C;
}

template<>
TMatrix<REAL> TMatrix<REAL>::identity(const INT row,const INT col){
  TMatrix<REAL> A(row,col);
  INT           dim;
  INT           i;

  dim = (row <= col) ? row : col;
  for(i = 0;i < dim;i++){
    A.dat[i * A.col + i] = 1.0;
  }
  return A;
}

template<>
TMatrix<COMP> TMatrix<COMP>::identity(const INT row,const INT col){
  TMatrix<COMP> A(row,col);
  INT           dim;
  INT           i;

  dim = (row <= col) ? row : col;
  for(i = 0;i < dim;i++){
    A.dat[i * A.col + i] = COMP__ONE();
  }
  return A;
}

template<>
TMatrix<REAL> TMatrix<REAL>::random  (const INT row,const INT col){
  TMatrix<REAL> A(row,col);
  RANDOM        rnd;
  INT           i,j;

  RANDOM__INITIALIZE(&rnd);
  
  for(i = 0;i < A.row;i++){
    for(j = 0;j < A.col;j++){
      A.dat[i * A.col + j] = RANDOM__NORMAL(&rnd,0.0,1.0);
    }
  }
  return A;
}

template<>
TMatrix<COMP> TMatrix<COMP>::random  (const INT row,const INT col){
  TMatrix<COMP> A(row,col);
  RANDOM        rnd;
  INT           i,j;

  RANDOM__INITIALIZE(&rnd);
  
  for(i = 0;i < A.row;i++){
    for(j = 0;j < A.col;j++){
      A.dat[i * A.col + j] = COMPLEX__MAKE_RE_IM(RANDOM__NORMAL(&rnd,0.0,1.0),RANDOM__NORMAL(&rnd,0.0,1.0)); 
    }
  }
  return A;
}

template<>
void TMatrix<REAL>::svd(TMatrix<REAL> &s,TMatrix<REAL> &U,TMatrix<REAL> &V){
  CLDIA::svd(s,U,V,*this);
}

template<>
void TMatrix<COMP>::svd(TMatrix<COMP> &s,TMatrix<COMP> &U,TMatrix<COMP> &V){
  CLDIA::svd(s,U,V,*this);
}

void CLDIA::eye (TMatrix<REAL> &E,
                 const INT      row,
                 const INT      col){
  INT dim;
  INT i;

  E   = TMatrix<REAL>(row,col);  
  dim = MACRO_MIN(row,col);
  for(i = 0;i < dim;i++){
    E[i][i] = 1.0;
  }
}

void CLDIA::eye (TMatrix<REAL> &E,
                 const INT      dim){
  CLDIA::eye(E,dim,dim);
}

void CLDIA::hilb(TMatrix<REAL> &H,
                 const INT     dim){
  INT i,j;

  H = TMatrix<REAL>(dim,dim);  
  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      H[i][j] = 1.0 / (i + j + 1.0);
    }
  }
}

template<>
TMatrix<REAL> CLDIA::diag (const TMatrix<REAL> &A  ){
  TMatrix<REAL> C;
  INT           row = A.get_row();
  INT           col = A.get_col();
  INT           dim;
  INT           i;
  
  if(col == 1){
    C = TMatrix<REAL>(row,row);
    for(i = 0;i < row;i++){
      C[i][i] = A[i][0];
    }
  }else{
    dim = MACRO_MIN(row,col);
    C   = TMatrix<REAL>(dim,1);
    for(i = 0;i < dim;i++){
      C[i][0] = A[i][i];
    }
  }
  return C;
}

template<>
TMatrix<COMP> CLDIA::diag (const TMatrix<COMP> &A  ){
  TMatrix<COMP> C;
  INT           row = A.get_row();
  INT           col = A.get_col();
  INT           dim;
  INT           i;
  
  if(col == 1){
    C = TMatrix<COMP>(row,row);
    for(i = 0;i < row;i++){
      C[i][i] = A[i][0];
    }
  }else{
    dim = MACRO_MIN(row,col);
    C   = TMatrix<COMP>(dim,1);
    for(i = 0;i < dim;i++){
      C[i][0] = A[i][i];
    }
  }
  return C;
}

template<>
REAL          CLDIA::trace(const TMatrix<REAL> &A  ){
  REAL tr;
  INT  dim = A.get_row();
  INT  i;

  if(!A.is_square()){
    ERROR__SHOW("Matrix must be square.");
    exit(EXIT_FAILURE);
  }
  tr = 0.0;
  for(i = 0;i < dim;i++){
    tr += A[i][i];
  }
  return tr;
}

template<>
COMP          CLDIA::trace(const TMatrix<COMP> &A  ){
  COMP tr;
  INT  dim = A.get_row();
  INT  i;

  if(!A.is_square()){
    ERROR__SHOW("Matrix must be square.");
    exit(EXIT_FAILURE);
  }
  tr = COMP__ZERO();
  for(i = 0;i < dim;i++){
    tr = COMP__ADD(tr,A[i][i]);
  }
  return tr;
}

template<>
REAL          CLDIA::cond (const TMatrix<REAL> &A  ){
  TMatrix<REAL> s;
  TMatrix<REAL> U;
  TMatrix<REAL> V;
  
  CLDIA::svd(s,U,V,A);
  return s[0][0] / s[s.get_row() - 1][0];
}

template<>
REAL          CLDIA::det  (const TMatrix<REAL> &A  ){
  TMatrix<REAL> s;
  TMatrix<REAL> U;
  TMatrix<REAL> V;
  REAL          d;
  INT           i;
  
  CLDIA::svd(s,U,V,A);
  d = 1.0;
  for(i = 0;i < s.get_row();i++){
    d *= s[i][0];
  }
  return d;
}

template<>
REAL          CLDIA::det_lu(const TMatrix<REAL> &A  ){
  TMatrix<REAL> L,U;
  REAL          d;
  INT           i;
  
  CLDIA::lu(L,U,A);
  d = 1.0;
  for(i = 0;i < U.get_row();i++){
    d *= U[i][i];
  }
  return d;
}

void CLDIA::svd  (      TMatrix<REAL> &s,
                        TMatrix<REAL> &U,
                        TMatrix<REAL> &V,
                  const TMatrix<REAL> &A){
  INT row = A.get_row();
  INT col = A.get_col();
  
  if(row >= col){
    s = TMatrix<REAL>(col,1);
    U = TMatrix<REAL>(row,col);
    V = TMatrix<REAL>(col,col);
  }else{
    s = TMatrix<REAL>(row,1);
    U = TMatrix<REAL>(row,row);
    V = TMatrix<REAL>(col,row);
  }
  REAL__MATRIX_SVD(s.get_dat(),U.get_dat(),V.get_dat(),A.get_dat(),row,col);
}

void CLDIA::svd  (      TMatrix<COMP> &s,
                        TMatrix<COMP> &U,
                        TMatrix<COMP> &V,
                  const TMatrix<COMP> &A){
  TMatrix<REAL> q;
  INT           row = A.get_row();
  INT           col = A.get_col();
  
  if(row >= col){
    q = TMatrix<REAL>(col,1);
    U = TMatrix<COMP>(row,col);
    V = TMatrix<COMP>(col,col);
  }else{
    q = TMatrix<REAL>(row,1);
    U = TMatrix<COMP>(row,row);
    V = TMatrix<COMP>(col,row);
  }
  COMP__MATRIX_SVD(q.get_dat(),U.get_dat(),V.get_dat(),A.get_dat(),row,col);
  s = q;
}

void CLDIA::lu   (      TMatrix<REAL> &L,
                        TMatrix<REAL> &U,
                  const TMatrix<REAL> &A){
  TMatrix<REAL> LU;
  INT           i,j;
  INT           dim;
    
  if(!A.is_square()){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  dim = A.get_row();

  LU  = A;
  L   = TMatrix<REAL>(dim,dim);
  U   = TMatrix<REAL>(dim,dim);
  
  REAL__MATRIX_LU_DECOMPOSITION(&LU[0][0],dim);
    
  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      if(i >  j){
        L[i][j] = LU[i][j];
      }
      if(i == j){
        L[i][j] = 1.0;
      }
    }
  }
  
  for(i = 0;i < dim;i++){
    for(j = 0;j < dim;j++){
      if(i <= j){
        U[i][j] = LU[i][j];
      }
    }
  }
}

namespace CLDIA{
  void hist(const TMatrix<REAL> &A,
            const REAL           min,
            const REAL           max,
            const INT            div,
            const CHAR          *filename){
    SVGPLOT__HISTOGRAM(&A[0][0],A.get_row(),
                       min,max,
                       div,
                       "x label",
                       "y label",
                       "title",
                       filename);
  }

  TMatrix<REAL> linspace(const REAL x1,const REAL x2);
}

#endif
