#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(void){
  RMatrix A(3,3);

  A[0][0] =  1.0;A[0][1] = -2.0;A[0][2] = 4.0;
  A[1][0] = -5.0;A[1][1] =  2.0;A[1][2] = 0.0;
  A[2][0] =  1.0;A[2][1] =  0.0;A[2][2] = 3.0;

  cerr <<       A  << endl;
  cerr <<   det(A) << endl;
  cerr << trace(A) << endl;

  RMatrix s,U,V;
  A.svd(s,U,V);

  cerr << U * diag(s) * ~V << endl;

  cerr << s << endl;
  cerr << U << endl;
  cerr << V << endl;
  return 0;
}
