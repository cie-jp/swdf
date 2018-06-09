#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(int argc,char *argv[]){
  TMatrix<REAL> A = TMatrix<REAL>::random(5,8);
  TMatrix<REAL> Q,R;
  
  qr(Q,R,A);

  cerr << A << endl;
  cerr << Q << endl;
  cerr << R << endl;
  cerr << Q * R << endl;

  /*
  TMatrix<COMP> A = TMatrix<COMP>::random(5,8);
  TMatrix<COMP> Q,R;
  
  qr(Q,R,A);

  cerr << A << endl;
  cerr << Q << endl;
  cerr << R << endl;
  cerr << Q * R << endl;
  */

  /*
  TMatrix<REAL> A = TMatrix<REAL>::random(5,5);
  TMatrix<REAL> L,U;

  lu(L,U,A);

  cerr << A << endl;
  cerr << L << endl;
  cerr << U << endl;
  cerr << L * U << endl;
  */

  /*
  TMatrix<COMP> A = TMatrix<COMP>::random(5,5);
  TMatrix<COMP> L,U;

  lu(L,U,A);

  cerr << A << endl;
  cerr << L << endl;
  cerr << U << endl;
  cerr << L * U << endl;
  */

  /*
  TMatrix<REAL> A = TMatrix<REAL>::random(5,5);
  TMatrix<REAL> B = A * ~A;
  TMatrix<REAL> L;

  choleskey(L,B);

  cerr << B << endl;
  cerr << L << endl;
  cerr << L * ~L << endl;
  */

  /*
  TMatrix<COMP> A = TMatrix<COMP>::random(5,5);
  TMatrix<COMP> B = A * ~A;
  TMatrix<COMP> L;

  choleskey(L,B);

  cerr << B << endl;
  cerr << L << endl;
  cerr << L * ~L << endl;
  */
  
  return 0;
}
