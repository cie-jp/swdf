#ifndef _CMATRIX_H_INCLUDE_
#define _CMATRIX_H_INCLUDE_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

class CMatrix : public TMatrix<COMP>{
 public:
  // *************************************************
  // コンストラクタ
  // *************************************************
  //row行col列の    行列を作成(0で初期化される)
  CMatrix(INT row,INT col)  : TMatrix<COMP>(row,col) {}
  //dim行dim列の正方行列を作成(0で初期化される)
  CMatrix(COMP  x)          : TMatrix<COMP>(x)       {}
  //  1行  1列の    行列を作成(0で初期化される) 
  CMatrix()                 : TMatrix<COMP>()        {}

  CMatrix(const TMatrix<COMP> &A){
    TMatrix<COMP>::initialize(*this,A.get_row(),A.get_col());
    TMatrix<COMP>::datacopy  (*this,A.get_dat());
  }

  // *************************************************
  // コピーコンストラクタ
  // *************************************************
  CMatrix(const CMatrix &A) : TMatrix<COMP>(A)       {}
  // *************************************************
  // デストラクタ
  // *************************************************
 ~CMatrix(){}

  // *************************************************
  // 縦ベクトルの場合 : 縦ベクトル要素を対角成分に持つ対角行列を返す
  // 正方行列  の場合 : 非対角成分を0にした行列を返す
  // *************************************************
  CMatrix diag ();

  //trace(sum of diagonal elements)
  double  trace();

  //matrix determinant
  double  det();

  //vector and matrix norms
  double  norm(double p = 2.0);

  //pseudo-inverse matrix
  CMatrix pinv();

  //equations solver
  CMatrix solve(const CMatrix &b);

  //basis pursuit
  CMatrix basis_pursuit(const CMatrix &b);

  //basis pursuit for non-negative
  CMatrix basis_pursuit_nonnegative(const CMatrix &b);  

  //iterative reweighted least squares
  CMatrix irls(const CMatrix &b);

  //eigenvalues and eigenvectors
  int eig(CMatrix &D,CMatrix &P);

  //principal component analysis
  //this = X * P' + M, L : eigenvalues
  int vpca(CMatrix &X,CMatrix &M,CMatrix &P,CMatrix &L);
  int vpca(CMatrix &X,CMatrix &M,CMatrix &P);
  int rpca(CMatrix &X,CMatrix &P,CMatrix &L);
  int rpca(CMatrix &X,CMatrix &P);

  //independent component analysis
  //this = X * P' + M
  int  ica(CMatrix &X,CMatrix &M,CMatrix &P);

  //fetch .mtx file 
  void fetch_mtx(const char *filename);
  
  //write .mtx file
  void write_mtx(const char *filename);
  
  //fetch .csv file
  void fetch_csv(const char *filename,char ch);
  
  //write .csv file
  void write_csv(const char *filename,char ch);
};

/*
#include"CMatrix__DIAG.hpp"
*/

RMatrix::operator CMatrix()const{
  CMatrix C(this->row,this->col);
  INT     i,j;

  for(i = 0;i < this->row;i++){
    for(j = 0;j < this->col;j++){
      C[i][j] = COMP__MAKE(this->dat[i * this->col + j]);
    }    
  }  
  return C;
}

#endif
