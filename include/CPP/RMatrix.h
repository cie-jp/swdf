#ifndef _RMATRIX_H_INCLUDE_
#define _RMATRIX_H_INCLUDE_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

class RMatrix{
 protected:
  double *D;
  int     W,H;
 public:

  //create a ( 1  x  1 ) zero matrix
  RMatrix(int dim = 1);

  //create a (row x col) zero matrix
  RMatrix(int row, int col);

  //copy constructor
  RMatrix(const RMatrix &A);

  //destructor
 ~RMatrix();

  //get address of a matrix 
  double *ptr()const;

  //get column  of a matrix
  int     col()const;

  //get row     of a matrix
  int     row()const;

  //operator overloading
  RMatrix  &operator  =(const RMatrix &);
  double   *operator [](const int     n)const;
  RMatrix  &operator +=(const RMatrix &);
  RMatrix  &operator -=(const RMatrix &);
  RMatrix  &operator +=(const double   );
  RMatrix  &operator -=(const double   );
  RMatrix  &operator *=(const RMatrix &);
  RMatrix  &operator *=(const double   );
  RMatrix  &operator /=(const double   );
  RMatrix  &operator &=(const RMatrix &);
  RMatrix  &operator |=(const RMatrix &);
  friend RMatrix   operator  ~(const RMatrix &);                
  friend RMatrix   operator  !(const RMatrix &);                
  friend RMatrix   operator  +(const RMatrix &);                
  friend RMatrix   operator  -(const RMatrix &);                
  friend RMatrix   operator  +(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  -(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  +(const double   ,const RMatrix &);
  friend RMatrix   operator  +(const RMatrix &,const double   );
  friend RMatrix   operator  -(const double   ,const RMatrix &);
  friend RMatrix   operator  -(const RMatrix &,const double   );
  friend RMatrix   operator  *(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  *(const double   ,const RMatrix &);
  friend RMatrix   operator  *(const RMatrix &,const double   );
  friend RMatrix   operator  %(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  /(const RMatrix &,const double   );
  friend RMatrix   operator  /(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  &(const RMatrix &,const int      );
  friend RMatrix   operator  &(const int      ,const RMatrix &);
  friend RMatrix   operator  &(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  |(const RMatrix &,const int      );
  friend RMatrix   operator  |(const int      ,const RMatrix &);
  friend RMatrix   operator  |(const RMatrix &,const RMatrix &);
  friend ostream  &operator <<(ostream&       ,const RMatrix &);

  //trace(sum of diagonal elements)
  double  trace();

  //matrix determinant
  double  det();

  //vector and matrix norms
  double  norm(double p = 2.0);

  //create or extract a diagonal matrix
  RMatrix diag();

  //pseudo-inverse matrix
  RMatrix pinv();

  //equations solver
  RMatrix solve(const RMatrix &b);

  //basis pursuit
  RMatrix basis_pursuit(const RMatrix &b);

  //basis pursuit for non-negative
  RMatrix basis_pursuit_nonnegative(const RMatrix &b);  

  //iterative reweighted least squares
  RMatrix irls(const RMatrix &b);

  //eigenvalues and eigenvectors
  int eig(RMatrix &D,RMatrix &P);

  //singular value decomposition
  int svd(RMatrix &U,RMatrix &S,RMatrix &V);

  //principal component analysis
  //this = X * P' + M, L : eigenvalues
  int vpca(RMatrix &X,RMatrix &M,RMatrix &P,RMatrix &L);
  int vpca(RMatrix &X,RMatrix &M,RMatrix &P);
  int rpca(RMatrix &X,RMatrix &P,RMatrix &L);
  int rpca(RMatrix &X,RMatrix &P);

  //independent component analysis
  //this = X * P' + M
  int  ica(RMatrix &X,RMatrix &M,RMatrix &P);

  //fetch .mtx file 
  void fetch_mtx(const char *filename);
  
  //write .mtx file
  void write_mtx(const char *filename);
  
  //fetch .csv file
  void fetch_csv(const char *filename,char ch);
  
  //write .csv file
  void write_csv(const char *filename,char ch);
};

#include"RMatrix.hpp"

#endif
