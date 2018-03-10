#include<iostream>
#include<cmath>
#include"rmatrix.h"
#include"linear_algebra.h"
#include"crandom.h"

using namespace std;

RMatrix::RMatrix(const BMatrix &A){
  W = A.col();
  H = A.row();
  D = new double[W * H];
  memcpy(D,A.ptr(),W * H * sizeof(double));
}

RMatrix &RMatrix::operator =(const BMatrix &A){
  if(W != A.col() || H != A.row()){ 
    delete [] D;
    W = A.col();
    H = A.row();
    D = new double[W * H];
  }
  memcpy(D,A.ptr(),W * H * sizeof(double));
  return *this;
}

RMatrix  RMatrix::I(int dim){
  RMatrix A(dim);
  for(int j = 0;j < A.H;j++){
    A.D[j * A.W + j] = 1.0;
  }
  return A;
}

RMatrix  RMatrix::random(int dim){
  RMatrix A(dim,dim);
  CRandom cr(clock());

  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      A.D[j * A.W + i] = cr.normal();
    }
  }
  return A;
}

RMatrix  RMatrix::random(int row,int col){
  RMatrix A(row,col);
  CRandom cr(clock());

  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      A.D[j * A.W + i] = cr.normal();
    }
  }
  return A;
}

RMatrix  RMatrix::dct_matrix(int dim){
  RMatrix W(dim,dim);
  for(int j = 0;j < dim;j++){
    W[0][j] = 1.0 / sqrt(dim);
    for(int i = 1;i < dim;i++){
      W[i][j] = cos(M_PI / (2.0 * dim) * (2 * j + 1) * i) * sqrt(2.0 / dim);
    }
  }
  return W;
}

RMatrix  RMatrix::idct_matrix(int dim){
  RMatrix W(dim,dim);
  for(int j = 0;j < dim;j++){
    W[j][0] = 1.0 / sqrt(dim);
    for(int i = 1;i < dim;i++){
      W[j][i] = cos(M_PI / (2.0 * dim) * (2 * j + 1) * i) * sqrt(2.0 / dim);
    }
  }
  return W;
}

