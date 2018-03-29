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
  
  // *************************************************
  // 演算子のオーバーロード
  // *************************************************
  RMatrix  &operator +=(const RMatrix &);
  RMatrix  &operator +=(const REAL     );

  RMatrix  &operator -=(const RMatrix &);
  RMatrix  &operator -=(const REAL     );

  RMatrix  &operator *=(const RMatrix &);
  RMatrix  &operator *=(const REAL     );
  RMatrix  &operator %=(const RMatrix &);

  RMatrix  &operator /=(const REAL     );
  RMatrix  &operator /=(const RMatrix &);

  operator CMatrix()const;
  
  friend ostream  &operator <<(ostream&       ,const RMatrix &);

  friend RMatrix   operator  +(const RMatrix &);
  friend RMatrix   operator  +(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  +(const REAL     ,const RMatrix &);
  friend RMatrix   operator  +(const RMatrix &,const REAL     );

  friend RMatrix   operator  -(const RMatrix &);                
  friend RMatrix   operator  -(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  -(const REAL     ,const RMatrix &);
  friend RMatrix   operator  -(const RMatrix &,const REAL     );

  friend RMatrix   operator  *(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  *(const REAL     ,const RMatrix &);
  friend RMatrix   operator  *(const RMatrix &,const REAL     );
  friend RMatrix   operator  %(const RMatrix &,const RMatrix &);

  friend RMatrix   operator  /(const RMatrix &,const REAL     );
  friend RMatrix   operator  /(const RMatrix &,const RMatrix &);

  friend RMatrix   operator  ~(const RMatrix &);                
  friend RMatrix   operator  !(const RMatrix &);                

  // *************************************************
  // 単位行列の作成(対角成分 = 1, 非対角成分 = 0)
  // *************************************************
  static RMatrix identity(const INT row,const INT col);

  // *************************************************
  // 標準正規分布に従う乱数を与えた行列の作成
  // *************************************************
  static RMatrix random  (const INT row,const INT col);

  // *************************************************
  // 特異値分解
  // *************************************************
  void    svd  (RMatrix &s,RMatrix &U,RMatrix &V);

  // *************************************************
  // 縦ベクトルの場合 : 縦ベクトル要素を対角成分に持つ対角行列を返す
  // 正方行列  の場合 : 非対角成分を0にした行列を返す
  // *************************************************
  RMatrix diag ();

  //trace(sum of diagonal elements)
  REAL    trace();

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

#include"RMatrix__OPERATOR_MEMBER.hpp"
#include"RMatrix__OPERATOR_ADD.hpp"
#include"RMatrix__OPERATOR_SUB.hpp"
#include"RMatrix__OPERATOR_MUL.hpp"
#include"RMatrix__OPERATOR_DIV.hpp"
#include"RMatrix__OPERATOR_TRANSPOSE.hpp"
#include"RMatrix__OPERATOR_INVERSE.hpp"

#include"RMatrix__STATIC.hpp"
#include"RMatrix__SVD.hpp"
#include"RMatrix__DIAG.hpp"
#include"RMatrix__TRACE.hpp"

namespace CLDIA{
  void hist(const RMatrix &A,
            const REAL     min,
            const REAL     max,
            const INT      div,
            const CHAR *filename){
    SVGPLOT__HISTOGRAM(&A[0][0],A.get_row(),
                       min,max,
                       div,
                       "x label",
                       "y label",
                       "title",
                       filename);
  }

  RMatrix linspace(const REAL x1,const REAL x2);
}

#endif
