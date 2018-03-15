#include"CLDIA.h"
#include"CPP/RMatrix.h"

using namespace std;

int main(void){
  RMatrix A;
  RMatrix s,U,V;

  A = RMatrix::random(8,3);

  A.svd(s,U,V);

  cerr << A                 << endl;
  cerr << U * s.diag() * ~V << endl;

  cerr << s << endl;
  cerr << U << endl;
  cerr << V << endl;

  cerr << ~U * U << endl;
  cerr << ~V * V << endl;

  cerr << RMatrix::identity(5,3) << endl;
  
  return 0;
}
