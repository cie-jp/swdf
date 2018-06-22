#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#define N (100)  // データ数
#define L (2)    // xの次元数
#define K (50)   // モデルパラメータ数
#define D (3)    // yの次元数

TMatrix<REAL> Phi(TVector<REAL> &x){
  static INT           isinit = 1;
  static TMatrix<REAL> res(K, D);
  static TVector<REAL> mu [D][K];
  REAL                 sigma2 = 1.0;
  
  if(isinit){
    for(int d = 0;d < D;d++){
      for(int k = 0;k < K;k++){
        mu[d][k] = TVector<REAL>::random(L);
      }
    }
    isinit = 0;
  }
  for(int k = 0;k < K;k++){
    for(int d = 0;d < D;d++){
      res[k][d] = exp(-0.5 / sigma2 * ~(x - mu[d][k]) * (x - mu[d][k]));
    }
  }
  return res;
}

int main(int argc,char *argv[]){
  TVector<REAL> x[N];
  TVector<REAL> y[N];
  TMatrix<REAL> h(K);
  TMatrix<REAL> Lambda(D,D);
  TVector<REAL> m0(K);
  TMatrix<REAL> S0(K,K);
  TMatrix<REAL> W0(D,D);
  REAL          nu0;
  TMatrix<REAL> AN(K,K);
  TVector<REAL> bN(K);
  TVector<REAL> mN(K);
  TMatrix<REAL> WN(D,D);
  REAL          nuN;
  TMatrix<REAL> AN0(K,K);
  TVector<REAL> bN0(K);
  TVector<REAL> mN0(K);
  TMatrix<REAL> WN0(D,D);
  REAL          nuN0;

  TVector<REAL> muN__0(D);
  TVector<REAL> muN0_0(D);

  for(int n = 0;n < N;n++){
    x[n] = TVector<REAL>::random(L);
    y[n] = TVector<REAL>::random(D);
  }

  /*
    for(int k = 0;k < K;k++){
    h[k] = 0.0;
    }
  */
  h = TVector<REAL>::random(K);

  /*
    for(int k = 0;k < D;k++){
    for(int l = 0;l < D;l++){
    Lambda[k][l] = (k == l) ? 1.0 : 0.0;
    }
    }
  */
  Lambda = TMatrix<REAL>::random(D,D);
  Lambda = Lambda * ~Lambda;

  /*
    for(int k = 0;k < K;k++){
    m0[k] = 0.0;
    }
  */
  m0 = TVector<REAL>::random(K);
  
  /*
    for(int k = 0;k < K;k++){
    for(int l = 0;l < K;l++){
    S0[k][l] = (k == l) ? 1.0 : 0.0;
    }
    }
  */
  S0 = TMatrix<REAL>::random(K,K);
  S0 = S0 * ~S0;

  for(int k = 0;k < D;k++){
    for(int l = 0;l < D;l++){
      W0[k][l] = (k == l) ? 1.0 : 0.0;
    }
  }

  nu0 = D;

  AN = !S0;
  for(int n = 0;n < N;n++){
    AN += Phi(x[n]) * Lambda * ~Phi(x[n]);
  }
  bN = !S0 * m0;
  for(int n = 0;n < N;n++){
    bN += Phi(x[n]) * Lambda * y[n];
  }
  mN = !AN * bN;

  WN = !W0;
  for(int n = 0;n < N;n++){
    WN += (y[n] - ~Phi(x[n]) * h) * ~(y[n] - ~Phi(x[n]) * h);
  }  
  WN = !WN;

  nuN = nu0 + N;

  AN0 = !S0;
  for(int n = 1;n < N;n++){
    AN0 += Phi(x[n]) * Lambda * ~Phi(x[n]);
  }
  bN0 = !S0 * m0;
  for(int n = 1;n < N;n++){
    bN0 += Phi(x[n]) * Lambda * y[n];
  }
  mN0 = !AN0 * bN0;

  WN0 = !W0;
  for(int n = 1;n < N;n++){
    WN0 += (y[n] - ~Phi(x[n]) * h) * ~(y[n] - ~Phi(x[n]) * h);
  }  
  WN0 = !WN0;

  nuN0 = nu0 + N - 1;

  muN__0 = ~Phi(x[0]) * mN;
  muN0_0 = ~Phi(x[0]) * mN0;

  TMatrix<REAL> SigmaN__0 = !Lambda + ~Phi(x[0]) * !AN  * Phi(x[0]);
  TMatrix<REAL> SigmaN0_0 = !Lambda + ~Phi(x[0]) * !AN0 * Phi(x[0]);
  TMatrix<REAL> VN__0 = SigmaN__0 - !Lambda;
  cerr << (muN__0 | muN0_0 | (y[0] + !Lambda * !(!Lambda - VN__0) * (muN__0 - y[0]))) << endl;
  cerr << (SigmaN__0 | SigmaN0_0 | (!Lambda + !Lambda * !(!Lambda - VN__0) * (SigmaN__0 - !Lambda)) | (!Lambda * !(2.0 * !Lambda - SigmaN__0) * !Lambda)) << endl;


  cerr << (~(y[0] - muN0_0) * !SigmaN0_0 * (y[0] - muN0_0)) << endl;
  cerr << (~(y[0] - muN__0) * !(!Lambda - VN__0) * (y[0] - muN__0)) << endl;
  /*
  Multivariate_Normal_Distribution mnd(mN,!AN);  
  
  h = mnd.sampling();

  cerr << mN << endl;
  cerr << mnd.sampling()  << endl;
  cerr << mnd.sampling()  << endl;
  cerr << mnd.sampling()  << endl;
  cerr << mnd.sampling()  << endl;
  cerr << mnd.sampling()  << endl;
  */
  /*for(int n = 0;n < N;n++){
    cerr << x[n] << endl;
    cerr << y[n] << endl;
    cerr << Phi(x[n]) << endl;
    }*/
  
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

  /*
  TMatrix<REAL> A = TMatrix<REAL>::random(6,6);
  
  cerr << A << endl;
  cerr << det(A) << endl;
  cerr << det_lu(A) << endl;
  cerr << det_bidiag(A) << endl;
  */
  return 0;
}
