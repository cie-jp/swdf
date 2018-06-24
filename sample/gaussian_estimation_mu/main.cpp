#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#define N (10) // データ数
#define D (3)  // 次元数

int main(int argc,char *argv[]){
  TVector<REAL> x[N];
  TVector<REAL> mu(D);
  TMatrix<REAL> Lambda(D,D);
  TVector<REAL> m0(D);
  TMatrix<REAL> S0(D,D);
  TMatrix<REAL> W0(D,D);
  REAL          nu0;
  TMatrix<REAL> AN(D,D);
  TVector<REAL> bN(D);
  TVector<REAL> mN(D);
  TMatrix<REAL> WN(D,D);
  REAL          nuN;

  mu     = TVector<REAL>::random(D);
  Lambda = TMatrix<REAL>::random(D,D);
  Lambda = Lambda * ~Lambda;

  Multivariate_Normal_Distribution mnd(mu,!Lambda);
  
  for(int n = 0;n < N;n++){
    x[n] = mnd.sampling();
  }

  m0 = TVector<REAL>::random(D);    
  S0 = TMatrix<REAL>::random(D,D);
  S0 = S0 * ~S0;

  for(int k = 0;k < D;k++){
    for(int l = 0;l < D;l++){
      W0[k][l] = (k == l) ? 1.0 : 0.0;
    }
  }

  nu0 = D;

  AN = !S0;
  for(int n = 0;n < N;n++){
    AN += Lambda;
  }
  bN = !S0 * m0;
  for(int n = 0;n < N;n++){
    bN += Lambda * x[n];
  }
  mN = !AN * bN;

  /*
  WN = !W0;
  for(int n = 0;n < N;n++){
    WN += (y[n] - ~Phi(x[n]) * h) * ~(y[n] - ~Phi(x[n]) * h);
  }  
  WN = !WN;

  nuN = nu0 + N;
  */
  TVector<REAL> xN  = TVector<REAL>::random(D);
  TMatrix<REAL> AN2 =  AN + Lambda;
  TVector<REAL> bN2 =  bN + Lambda * xN;
  TVector<REAL> mN2 = !AN2 * bN2;
  REAL          QN  = 0.0;
  REAL          QN2 = 0.0;

  for(int n = 0;n < N;n++){
    QN += ~x[n] * Lambda * x[n];
  }
  QN2 = QN + ~xN * Lambda * xN;

  REAL lnP  =  N      / 2.0 * log(det_lu(Lambda)) - 0.5 * log(det_lu(S0)) - D *  N      / 2.0 * log(2.0 * M_PI) - 0.5 * log(det_lu(AN )) - 0.5 * (~m0 * !S0 * m0 - ~mN  * AN  * mN  + QN );
  REAL lnP2 = (N + 1) / 2.0 * log(det_lu(Lambda)) - 0.5 * log(det_lu(S0)) - D * (N + 1) / 2.0 * log(2.0 * M_PI) - 0.5 * log(det_lu(AN2)) - 0.5 * (~m0 * !S0 * m0 - ~mN2 * AN2 * mN2 + QN2);
  REAL lnp  = lnP2 - lnP;

  TMatrix<REAL> BN = AN * !(AN + Lambda) * Lambda;
  REAL lnp2 = 0.5 * log(det_lu(BN)) - 0.5 * D * log(2.0 * M_PI) - 0.5 * ~(xN - mN) * BN * (xN - mN);

  cerr << lnp  << endl;
  cerr << lnp2 << endl;
  
  return 0;
}
