#ifndef _RVECTOR_H_INCLUDE_
#define _RVECTOR_H_INCLUDE_

#include<iostream>
#include<cmath>
#include"bmatrix.h"

using namespace std;

//Real Vector Class
class RVector : public BMatrix{
 public:
  
  //create a ( 1 )-dimensional zero vector
  RVector()                   : BMatrix(1){}
  
  //create a (dim)-dimensional zero vector
  RVector(int dim)            : BMatrix(dim,1){}
  
  //copy constructor
  RVector(const BMatrix &A);
  
  //get dimension of a vector
  int dim()const{return H;}
  
  //operator overloading
  double  &operator [](const int n)const{return D[n];}
  RVector &operator  =(const BMatrix &);
  RVector &operator *=(const BMatrix &);
  
  //create a (dim)-dimensional gaussian random vector
  static RVector random(int dim);

  //create a (dim)-dimensional gaussian random K-sparse vector
  static RVector random_sparse(int dim,int K);
};

#endif
