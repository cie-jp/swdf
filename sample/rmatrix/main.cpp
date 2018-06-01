#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

void hoge(){
  CMatrix s,U,V,A = CMatrix::random(4,6);
  cerr << A << endl;
  svd(s,U,V,A);
  cerr << U * diag(s) * ~V << endl;
}

int main(int argc,char *argv[]){
  /*
  RMatrix C = RMatrix::random(10,1);
  TMatrix<REAL> E;
  hilb(E,5);
  cerr << C << endl;
  cerr << diag(C) << endl;
  cerr << C.diag() << endl;
  cerr << !diag(C) << endl;
  cerr << trace(C.diag()) << endl;
  cerr << E << endl;
  */
  //hoge();
  //hist(C,-3.0,3.0,100,"test.svg");


  TMatrix<REAL> A = TMatrix<REAL>::random(6,6);
  
  cerr << A << endl;
  cerr << det(A) << endl;
  cerr << det_lu(A) << endl;
  cerr << det_bidiag(A) << endl;
  return 0;
}
