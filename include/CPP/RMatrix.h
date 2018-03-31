#ifndef _RMATRIX_H_INCLUDE_
#define _RMATRIX_H_INCLUDE_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

class CMatrix;

class RMatrix : public TMatrix<REAL>{
 public:
  // *************************************************
  // コンストラクタ
  // *************************************************
  //row行col列の    行列を作成(0で初期化される)
  RMatrix(INT row,INT col)  : TMatrix<REAL>(row,col) {}
  //dim行dim列の正方行列を作成(0で初期化される)
  RMatrix(REAL  x)          : TMatrix<REAL>(x)       {}
  //  1行  1列の    行列を作成(0で初期化される) 
  RMatrix()                 : TMatrix<REAL>()        {}

  RMatrix(const TMatrix<REAL> &A){
    TMatrix<REAL>::initialize(*this,A.get_row(),A.get_col());
    TMatrix<REAL>::datacopy  (*this,A.get_dat());
  }

  // *************************************************
  // コピーコンストラクタ
  // *************************************************
  RMatrix(const RMatrix &A) : TMatrix<REAL>(A)       {}
  // *************************************************
  // デストラクタ
  // *************************************************
 ~RMatrix(){}

  operator CMatrix()const;

  //matrix determinant
  double  det();

  //vector and matrix norms
  double  norm(double p = 2.0);

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

#include"RMatrix__STATIC.hpp"

#endif
