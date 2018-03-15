#ifndef _RMATRIX_H_INCLUDE_
#define _RMATRIX_H_INCLUDE_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include"CLDIA.h"

using namespace std;

class RMatrix{
 protected:
  REAL *dat;
  INT   row;
  INT   col;
 private:
  static void initialize(RMatrix    &A,
                         const INT   row,
                         const INT   col);
  static void finalize  (RMatrix    &A);
  static void resize    (RMatrix    &A,
                         const INT   row,
                         const INT   col);
  static void zerofill  (RMatrix    &A);
  static void datacopy  (RMatrix    &A,
                         const REAL *dat);
 public:
  // *************************************************
  // コンストラクタ
  // *************************************************
  //row行col列の    行列を作成(0で初期化される)
  RMatrix(INT row,INT col);
  //dim行dim列の正方行列を作成(0で初期化される)
  RMatrix(REAL  x) : RMatrix(1,1) {dat[0] = x;}
  //  1行  1列の    行列を作成(0で初期化される) 
  RMatrix()        : RMatrix(1,1) {}
  // *************************************************
  // コピーコンストラクタ
  // *************************************************
  RMatrix(const RMatrix &A);
  // *************************************************
  // デストラクタ
  // *************************************************
 ~RMatrix();

  // *************************************************
  // アクセッサ
  // *************************************************
  REAL *get_dat()const{return this->dat;}//データポインタの取得
  INT   get_row()const{return this->row;}//行数          の取得
  INT   get_col()const{return this->col;}//列数          の取得

  // *************************************************
  // 演算子のオーバーロード
  // *************************************************
  RMatrix  &operator  =(const RMatrix &);

  REAL     *operator [](const INT     n)const;

  RMatrix  &operator +=(const RMatrix &);
  RMatrix  &operator +=(const REAL     );

  RMatrix  &operator -=(const RMatrix &);
  RMatrix  &operator -=(const REAL     );

  RMatrix  &operator *=(const RMatrix &);
  RMatrix  &operator *=(const REAL     );
  RMatrix  &operator %=(const RMatrix &);

  RMatrix  &operator /=(const REAL     );
  RMatrix  &operator /=(const RMatrix &);

  RMatrix  &operator &=(const RMatrix &);

  RMatrix  &operator |=(const RMatrix &);

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

  friend RMatrix   operator  &(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  &(const RMatrix &,const INT      );
  friend RMatrix   operator  &(const INT      ,const RMatrix &);

  friend RMatrix   operator  |(const RMatrix &,const RMatrix &);
  friend RMatrix   operator  |(const RMatrix &,const INT      );
  friend RMatrix   operator  |(const INT      ,const RMatrix &);

  friend RMatrix   operator  ~(const RMatrix &);                
  friend RMatrix   operator  !(const RMatrix &);                

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

#include"RMatrix__PRIVATE.hpp"
#include"RMatrix__BASE.hpp"
#include"RMatrix__OPERATOR_MEMBER.hpp"
#include"RMatrix__OPERATOR_ADD.hpp"
#include"RMatrix__OPERATOR_SUB.hpp"
#include"RMatrix__OPERATOR_MUL.hpp"
#include"RMatrix__OPERATOR_DIV.hpp"
#include"RMatrix__OPERATOR_RESIZE.hpp"
#include"RMatrix__OPERATOR_TRANSPOSE.hpp"
#include"RMatrix__OPERATOR_INVERSE.hpp"

#endif
