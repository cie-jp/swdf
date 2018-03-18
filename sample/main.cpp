#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

void lu_check(){
  RMatrix A;
  RMatrix L,U;

  A = RMatrix::random(6,6);
  lu(L,U,A);

  cerr << A << endl;
  cerr << L << endl;
  cerr << U << endl;
  cerr << L * U << endl;
}

void tmatrix_check(){
  IMatrix A(5,7),B(5,7);

  A[2][3] = 1;
  B[0][2] = 2;
  cerr << A << endl;
  cerr << B << endl;
  cerr << (A | B) << endl;

  TMatrix<REAL> C(5,6);
  for(INT i = 0;i < 5;i++){
    for(INT j = 0;j < 6;j++){
      C[i][j] = i + j;
    }
  }
  cerr << (C > 3.0) << endl;
  cerr <<  C << endl;
  show(C);
  show(C,C < 3.0);
}

int main(void){
  RMatrix A(3,3);

  A[0][0] =  1.0;A[0][1] = -2.0;A[0][2] = 4.0;
  A[1][0] = -5.0;A[1][1] =  2.0;A[1][2] = 0.0;
  A[2][0] =  1.0;A[2][1] =  0.0;A[2][2] = 3.0;

  cerr <<       A  << endl;
  cerr <<   det(A) << endl;
  cerr <<   det_lu(A) << endl;

  cerr << trace(A) << endl;

  RMatrix s,U,V;
  A.svd(s,U,V);

  cerr << U * diag(s) * ~V << endl;

  cerr << s << endl;
  cerr << U << endl;
  cerr << V << endl;

  lu_check();

  tmatrix_check();
  return 0;
}
