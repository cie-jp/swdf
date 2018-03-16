#ifndef _BMATRIX_H_INCLUDE_
#define _BMATRIX_H_INCLUDE_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

//Base Matrix Class
class BMatrix{
 protected:
  double *D;
  int     W,H;
 public:

  //create a ( 1  x  1 ) zero matrix
  BMatrix(int dim = 1);

  //create a (row x col) zero matrix
  BMatrix(int row, int col);

  //copy constructor
  BMatrix(const BMatrix &A);

  //destructor
 ~BMatrix();

  //get address of a matrix 
  double *ptr()const;

  //get column  of a matrix
  int     col()const;

  //get row     of a matrix
  int     row()const;

  //operator overloading
  BMatrix  &operator  =(const BMatrix &);
  double   *operator [](const int     n)const;
  BMatrix  &operator +=(const BMatrix &);
  BMatrix  &operator -=(const BMatrix &);
  BMatrix  &operator +=(const double   );
  BMatrix  &operator -=(const double   );
  BMatrix  &operator *=(const BMatrix &);
  BMatrix  &operator *=(const double   );
  BMatrix  &operator /=(const double   );
  BMatrix  &operator &=(const BMatrix &);
  BMatrix  &operator |=(const BMatrix &);
  friend BMatrix   operator  ~(const BMatrix &);                
  friend BMatrix   operator  !(const BMatrix &);                
  friend BMatrix   operator  +(const BMatrix &);                
  friend BMatrix   operator  -(const BMatrix &);                
  friend BMatrix   operator  +(const BMatrix &,const BMatrix &);
  friend BMatrix   operator  -(const BMatrix &,const BMatrix &);
  friend BMatrix   operator  +(const double   ,const BMatrix &);
  friend BMatrix   operator  +(const BMatrix &,const double   );
  friend BMatrix   operator  -(const double   ,const BMatrix &);
  friend BMatrix   operator  -(const BMatrix &,const double   );
  friend BMatrix   operator  *(const BMatrix &,const BMatrix &);
  friend BMatrix   operator  *(const double   ,const BMatrix &);
  friend BMatrix   operator  *(const BMatrix &,const double   );
  friend BMatrix   operator  %(const BMatrix &,const BMatrix &);
  friend BMatrix   operator  /(const BMatrix &,const double   );
  friend BMatrix   operator  /(const BMatrix &,const BMatrix &);
  friend BMatrix   operator  &(const BMatrix &,const int      );
  friend BMatrix   operator  &(const int      ,const BMatrix &);
  friend BMatrix   operator  &(const BMatrix &,const BMatrix &);
  friend BMatrix   operator  |(const BMatrix &,const int      );
  friend BMatrix   operator  |(const int      ,const BMatrix &);
  friend BMatrix   operator  |(const BMatrix &,const BMatrix &);
  friend ostream  &operator <<(ostream&       ,const BMatrix &);

  //trace(sum of diagonal elements)
  double  trace();

  //matrix determinant
  double  det();

  //vector and matrix norms
  double  norm(double p = 2.0);

  //create or extract a diagonal matrix
  BMatrix diag();

  //pseudo-inverse matrix
  BMatrix pinv();

  //equations solver
  BMatrix solve(const BMatrix &b);

  //basis pursuit
  BMatrix basis_pursuit(const BMatrix &b);

  //basis pursuit for non-negative
  BMatrix basis_pursuit_nonnegative(const BMatrix &b);  

  //iterative reweighted least squares
  BMatrix irls(const BMatrix &b);

  //eigenvalues and eigenvectors
  int eig(BMatrix &D,BMatrix &P);

  //singular value decomposition
  int svd(BMatrix &U,BMatrix &S,BMatrix &V);

  //principal component analysis
  //this = X * P' + M, L : eigenvalues
  int vpca(BMatrix &X,BMatrix &M,BMatrix &P,BMatrix &L);
  int vpca(BMatrix &X,BMatrix &M,BMatrix &P);
  int rpca(BMatrix &X,BMatrix &P,BMatrix &L);
  int rpca(BMatrix &X,BMatrix &P);

  //independent component analysis
  //this = X * P' + M
  int  ica(BMatrix &X,BMatrix &M,BMatrix &P);

  //fetch .mtx file 
  void fetch_mtx(const char *filename);
  
  //write .mtx file
  void write_mtx(const char *filename);
  
  //fetch .csv file
  void fetch_csv(const char *filename,char ch);
  
  //write .csv file
  void write_csv(const char *filename,char ch);
};

#endif
