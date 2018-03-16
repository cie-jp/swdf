#include<iostream>
#include<cmath>
#include"rvector.h"
#include"crandom.h"

using namespace std;

RVector::RVector(const BMatrix &A){
  if(A.col() != 1){
    cerr << "ERROR : RVector.RVector(const BMatrix &)" << endl;
    exit(EXIT_FAILURE);
  }
  W =       1;
  H = A.row();
  D = new double[H];
  for(int j = 0;j < H;j++){
    D[j] = A[j][0];
  }
}

RVector &RVector::operator  =(const BMatrix &A){
  if(A.col() != 1){
    cerr << "ERROR : RVector.=(BMatrix)"               << endl;
    exit(EXIT_FAILURE);
  }
  if(H != A.row()){ 
    delete [] D;
    W =       1;
    H = A.row();
    D = new double[H];
  }
  memcpy(D,A.ptr(),H * sizeof(double));
  return *this;
}

RVector &RVector::operator *=(const BMatrix &A){
  if(A.col() != 1 || A.row() != 1){
    cerr << "ERROR : RVector.*=(BMatrix)"              << endl;
    exit(EXIT_FAILURE);  
  }
  for(int j = 0;j < H;j++){
    D[j] *= A[0][0];
  }
  return *this;
}

RVector  RVector::random(int dim){
  RVector A(dim);
  CRandom cr(clock());
  for(int j = 0;j < A.H;j++){
    A.D[j] = cr.normal();
  }
  return A;
}

RVector  RVector::random_sparse(int dim,int K){
  RVector A(dim);
  CRandom cr(clock());
  int     idx;
  double  tmp;
  for(int j = 0;j <   K;j++){
    A.D[j] = cr.normal();
  }
  for(int j = 0;j < A.H;j++){
    idx      = (int)cr.uniform(0.0,dim);
    tmp      = A.D[j];
    A.D[j]   = A.D[idx];
    A.D[idx] = tmp;
  }
  return A;
}
