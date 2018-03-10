#ifndef _RMATRIX_H_INCLUDE_
#define _RMATRIX_H_INCLUDE_

#include<iostream>
#include<cmath>
#include"bmatrix.h"

using namespace std;

//Real Matrix Class
class RMatrix : public BMatrix{
 public:

  //create a ( 1  x  1 ) zero matrix
  RMatrix()                           : BMatrix(1){}

  //create a (dim x dim) zero matrix
  RMatrix(int dim)                    : BMatrix(dim){}

  //create a (row x col) zero matrix
  RMatrix(int row,int col)            : BMatrix(row,col){}

  //copy constructor
  RMatrix(const BMatrix &A);

  //operator overloading
  RMatrix &operator =(const BMatrix &);

  //create a (dim x dim) identity matrix
  static RMatrix I(int dim);

  //create a (dim x dim) gaussian random matrix
  static RMatrix random(int dim);

  //create a (row x col) gaussian random matrix
  static RMatrix random(int row,int col);

  //create a (dim x dim)  dct matrix
  static RMatrix  dct_matrix(int dim);

  //create a (dim x dim) idct matrix
  static RMatrix idct_matrix(int dim);
};

#endif
