#ifndef _TMATRIX_H_INCLUDE_
#define _TMATRIX_H_INCLUDE_

#include<iostream>
#include<cmath>
#include"crandom.h"

using namespace std;

template<typename TYPE> inline TYPE fma(TYPE x,TYPE y,TYPE z);
template<> inline float  fma<float >(float  x,float  y,float  z){return fma(x,y,z);}
template<> inline double fma<double>(double x,double y,double z){return fma(x,y,z);}
template<> inline complex<double> fma<complex<double> >(complex<double> x,complex<double> y,complex<double> z){return x * y + z;}

template<typename TYPE> inline TYPE fabs(TYPE x);
template<> inline float  fabs<float >(float  x){return fabs(x);}
template<> inline double fabs<double>(double x){return fabs(x);}

template<typename TYPE> inline TYPE sqrt(TYPE x);
template<> inline float  sqrt<float >(float  x){return sqrt(x);}
template<> inline double sqrt<double>(double x){return sqrt(x);}

template<typename TYPE> inline TYPE pow(TYPE x,TYPE y);
template<> inline float  pow<float >(float  x,float  y){return pow(x,y);}
template<> inline double pow<double>(double x,double y){return pow(x,y);}

template<typename TYPE> inline TYPE cos(TYPE x);
template<> inline float  cos<float >(float  x){return cos(x);}
template<> inline double cos<double>(double x){return cos(x);}

//n次元正方行列AのLU分解を行う. 
//Pは置換行列を与える. 
//返り値 0:正常終了, -1: 異常終了
template<typename TYPE>
int LU_decomposition(TYPE *A,int P[],int n);

//n次元正方行列Aの逆行列を求める. 
//返り値 0:正常終了, -1: 異常終了
template<typename TYPE>
int inv(TYPE *A,int n);

//n元線形連立方程式 Ax = b の解を求める. 
//返り値 0:正常終了, -1: 異常終了
template<typename TYPE>
int solve(TYPE x[],TYPE *A,TYPE b[],int n);

template<typename TYPE> class TMatrix;
template<typename TYPE> TMatrix<TYPE>  operator  ~(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  !(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  +(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  -(const TMatrix<TYPE> &);                
template<typename TYPE> TMatrix<TYPE>  operator  +(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  -(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  +(const TYPE           ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  +(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<TYPE>  operator  -(const TYPE           ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  -(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<TYPE>  operator  *(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  *(const TYPE           ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  *(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<TYPE>  operator  %(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  /(const TMatrix<TYPE> &,const TYPE           );
template<typename TYPE> TMatrix<TYPE>  operator  /(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  &(const TMatrix<TYPE> &,const int            );
template<typename TYPE> TMatrix<TYPE>  operator  &(const int            ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  &(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  |(const TMatrix<TYPE> &,const int            );
template<typename TYPE> TMatrix<TYPE>  operator  |(const int            ,const TMatrix<TYPE> &);
template<typename TYPE> TMatrix<TYPE>  operator  |(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
template<typename TYPE> ostream       &operator <<(ostream&             ,const TMatrix<TYPE> &);

template<typename TYPE> class TMatrix{
 protected:
  TYPE *D;
  int   W,H;
 public:
  //create a (dim x dim) matrix
  TMatrix(int dim = 1);

  //create a (row x col) matrix
  TMatrix(int row, int col);

  //copy constructor
  TMatrix(const TMatrix<TYPE> &);

  //destructor
 ~TMatrix();

  //get address of a matrix 
  TYPE *ptr()const;

  //get column  of a matrix
  int   col()const;

  //get row     of a matrix
  int   row()const;

  //operator overloading
  operator TYPE();
  TMatrix<TYPE> &operator  =(const TMatrix<TYPE> &);
  TYPE          *operator [](const int n)const;
  TMatrix<TYPE> &operator +=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator -=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator +=(const TYPE);
  TMatrix<TYPE> &operator -=(const TYPE);
  TMatrix<TYPE> &operator *=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator *=(const TYPE);
  TMatrix<TYPE> &operator /=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator /=(const TYPE);
  TMatrix<TYPE> &operator &=(const TMatrix<TYPE> &);
  TMatrix<TYPE> &operator |=(const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  ~ <>(const TMatrix<TYPE> &);                
  friend TMatrix<TYPE>  operator  ! <>(const TMatrix<TYPE> &);                
  friend TMatrix<TYPE>  operator  + <>(const TMatrix<TYPE> &);                
  friend TMatrix<TYPE>  operator  - <>(const TMatrix<TYPE> &);                
  friend TMatrix<TYPE>  operator  + <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  - <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  + <>(const TYPE           ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  + <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<TYPE>  operator  - <>(const TYPE           ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  - <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<TYPE>  operator  * <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  * <>(const TYPE           ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  * <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<TYPE>  operator  % <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  / <>(const TMatrix<TYPE> &,const TYPE           );
  friend TMatrix<TYPE>  operator  / <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  & <>(const TMatrix<TYPE> &,const int            );
  friend TMatrix<TYPE>  operator  & <>(const int            ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  & <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  | <>(const TMatrix<TYPE> &,const int            );
  friend TMatrix<TYPE>  operator  | <>(const int            ,const TMatrix<TYPE> &);
  friend TMatrix<TYPE>  operator  | <>(const TMatrix<TYPE> &,const TMatrix<TYPE> &);
  friend ostream       &operator << <>(ostream&             ,const TMatrix<TYPE> &);

  //create a matrix Bij = func(Aij)
  TMatrix<TYPE> function(TYPE (*func)(TYPE));

  //trace(sum of diagonal elements)
  TYPE trace();
  
  //matrix determinant
  TYPE det();

  //vector and matrix norms
  TYPE norm(TYPE p = 2.0);

  //create or extract a diagonal matrix
  TMatrix<TYPE> diag();

  //equations solver
  TMatrix<TYPE> solve(const TMatrix<TYPE> &b);

  //create a (dim x dim) identity matrix
  static TMatrix<TYPE> I(int dim);

  //create a (dim x dim) matrix such that Aij = 1
  static TMatrix<TYPE> one(int dim);

  //create a (row x col) matrix such that Aij = 1
  static TMatrix<TYPE> one(int row,int col);

  //create a (dim x dim) gaussian N(0,1) random matrix
  static TMatrix<TYPE> random(int dim);

  //create a (row x col) gaussian N(0,1) random matrix
  static TMatrix<TYPE> random(int row,int col);

  //create a (dim x dim)  dct matrix
  static TMatrix<TYPE>  dct_matrix(int dim);

  //create a (dim x dim) idct matrix
  static TMatrix<TYPE> idct_matrix(int dim);
};

template<typename TYPE> class TVector : public TMatrix<TYPE>{
 public:
  //create a ( 1 )-dimensional zero vector
  TVector()                   : TMatrix<TYPE>(1){}
  
  //create a (dim)-dimensional zero vector
  TVector(int dim)            : TMatrix<TYPE>(dim,1){}

  //copy constructor
  TVector(const TMatrix<TYPE> &A);
  
  //get dimension of a vector
  int dim()const{return this->H;}
  
  //operator overloading
  TYPE          &operator [](const int n)const{return this->D[n];}
  TVector<TYPE> &operator  =(const TMatrix<TYPE> &);

  //create a (dim x dim) matrix such that Aij = 1
  static TVector<TYPE> one(int dim);
  
  //create a (dim)-dimensional gaussian N(0,1) random vector
  static TVector<TYPE> random(int dim);

  //create a (dim)-dimensional gaussian random K-sparse vector
  static TVector<TYPE> random_sparse(int dim,int K);
};

#include"tmatrix.hpp"

#endif
