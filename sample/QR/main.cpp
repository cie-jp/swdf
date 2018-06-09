#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(int argc,char *argv[]){
  /*
  TMatrix<REAL> A = TMatrix<REAL>::random(5,8);
  TMatrix<REAL> Q,R;
  
  qr(Q,R,A);

  cerr << A << endl;
  cerr << Q << endl;
  cerr << R << endl;
  cerr << Q * R << endl;
  */
  
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

  /*
  TVector<REAL> x;
  TVector<REAL> mu    = TVector<REAL>::random(5);
  TMatrix<REAL> L     = TMatrix<REAL>::random(5,5);
  TMatrix<REAL> Sigma = L * ~L;
  TVector<REAL> xbar(5);
  TMatrix<REAL> S   (5,5);
  INT           n;
  INT           N     = 100000;
  
  Multivariate_Normal_Distribution mnd(mu,Sigma);  

  for(n = 0;n < N;n++){
    x     = mnd.sampling();
    xbar +=  x;
    S    += (x - mu) * ~(x - mu);
  }

  xbar /= (REAL)N;
  S    /= (REAL)N;

  cerr << (mu | xbar) << endl;// E[x]                    = mu
  cerr << (Sigma | S) << endl;// E[(x - mu) * ~(x - mu)] = Sigma
  */
  
  TVector<COMP> z;
  TVector<COMP> mu    = TVector<COMP>::random(5);
  TMatrix<COMP> L     = TMatrix<COMP>::random(5,5);
  TMatrix<COMP> Sigma = L * ~L;
  TVector<COMP> zbar(5);
  TMatrix<COMP> S   (5,5);
  INT           n;
  INT           N     = 100000;
  
  Multivariate_Complex_Normal_Distribution mcnd(mu,Sigma);  

  for(n = 0;n < N;n++){
    z     = mcnd.sampling();
    zbar +=  z;
    S    += (z - mu) * ~(z - mu);
  }

  zbar /= COMPLEX__MAKE_REAL((REAL)N);
  S    /= COMPLEX__MAKE_REAL((REAL)N);

  cerr << (mu | zbar) << endl;// E[x]                    = mu
  cerr << (Sigma | S) << endl;// E[(x - mu) * ~(x - mu)] = Sigma

  return 0;
}
