#include"CLDIA.h"

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

  CMatrix B(3,4),W;
  B = CMatrix::random(5,6);
  W = B + B;
  cerr << B << endl;
  cerr << W << endl;

  cerr << W - B << endl;
  cerr << COMPLEX__MAKE_RE_IM(5.0,3.0) * W / B / COMPLEX__MAKE_RE_IM(5.0,3.0) << endl;
  cerr << (W & W) << endl;

  cerr << ~(W & W) << endl;

  CMatrix Q = CMatrix::random(4,9);
  CMatrix UU,VV;

  Q.svd(s,UU,VV);
  cerr << Q << endl;
  cerr << ~UU * UU << endl;
  cerr << ~VV * VV << endl;

  cerr << UU * s.diag() * ~VV << endl;
  cerr << s << endl;
  cerr << ~s << endl;
  return 0;
}
