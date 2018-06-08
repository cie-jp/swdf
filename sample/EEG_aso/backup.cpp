/***************************************************************** 
 *
 * 脳波(EEG)データによる3状態判別
 *
 *
 *                           Created  by Mamoru Ota (2018/06/07)
 * 
 *****************************************************************/

#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#include"./header/RMatrix__fetch_csv.hpp"

REAL ln_S(RVector &x,RVector &mu,RMatrix &Q,REAL f){
  INT D = x.get_row();
  return lgamma((f + D) / 2.0) - lgamma(f / 2.0) - D / 2.0 * log(M_PI * f) + 0.5 * ln_det(Q) - (f + D) / 2.0 * log(1.0 + (1.0 / f) * ~(x - mu) * Q * (x - mu));
}

#define E (4) //環境数
#define C (8) //チャンネル数
#define K (4) //動作状態数

int main(int argc,char *argv[]){
  RMatrix dat;

  RMatrix X;
  RVector c;
  RVector e;
  RVector z;

  INT    CN; //データ数
  INT     D; //次元数

  RVector xn;
  INT     n,m;
  
  RVector m0;
  REAL    beta0;
  RMatrix W0;
  REAL    nu0;
  REAL    alpha;

  REAL    N       [C][E][K];
  RVector xbar    [C][E][K];
  RMatrix S       [C][E][K];

  INT     c_idx;
  INT     e_idx;
  INT     z_idx;
  
  REAL    N_cez;
  RVector xbar_cez;
  RMatrix S_cez;
  
  RVector m_ast   [C][E][K];
  REAL    beta_ast[C][E][K];
  RMatrix W_ast   [C][E][K];
  REAL    nu_ast  [C][E][K];

  RVector mu_cez;
  RMatrix Q_cez;
  REAL    f_cez;

  // ================================================
  // データの入力
  // ================================================
  
  dat = RMatrix__fetch_csv("./data.csv",", \t,","%");
  X   = dat |  1;
  for(m = 2;m < dat.get_col() - 2;m++){
    X |= (dat | m);
  }
  c   = dat | (dat.get_col() - 3);
  e   = dat | (dat.get_col() - 2);
  z   = dat | (dat.get_col() - 1);


  cerr << dat << endl;
  cerr << (X | e | z) << endl;

  CN = X.get_row();
  D  = X.get_col();

  for(n = 0;n < CN;n++){
    c[n] = 0;
  }

  // ================================================
  // 統計量の計算
  // ================================================

  for(c_idx = 0;c_idx < C;c_idx++){
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){
        N   [c_idx][e_idx][z_idx] = 0.0;
        xbar[c_idx][e_idx][z_idx] = RVector(D);
        S   [c_idx][e_idx][z_idx] = RMatrix(D,D);
      }
    }
  }

  for(n = 0;n < CN;n++){
    xn = ~(X & n);
    N   [(INT)c[n]][(INT)e[n]][(INT)z[n]] += 1.0;
    xbar[(INT)c[n]][(INT)e[n]][(INT)z[n]] +=  xn;
    S   [(INT)c[n]][(INT)e[n]][(INT)z[n]] +=  xn * ~xn;
  }

  for(c_idx = 0;c_idx < C;c_idx++){
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){
        if(N[c_idx][e_idx][z_idx] == 0.0){
          continue;
        }        
        xbar[c_idx][e_idx][z_idx] /= N[c_idx][e_idx][z_idx];
        S   [c_idx][e_idx][z_idx] /= N[c_idx][e_idx][z_idx];
        S   [c_idx][e_idx][z_idx] -= xbar[c_idx][e_idx][z_idx] * ~xbar[c_idx][e_idx][z_idx];
      }
    }
  }

  // ================================================
  // 事前分布のハイパーパラメータ設定
  // ================================================

  for(alpha = 3.0e-3;alpha <= 1.0e+2;alpha *= 2.0){

  m0    = RVector(D);
  beta0 = 1.0e-2;
  eye(W0,D,D);
  W0   *= alpha;
  nu0   = D + 1;

  // ================================================
  // 事後分布のパラメータ計算
  // ================================================

  for(c_idx = 0;c_idx < C;c_idx++){
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){        
        N_cez    = N   [c_idx][e_idx][z_idx];
        xbar_cez = xbar[c_idx][e_idx][z_idx];
        S_cez    = S   [c_idx][e_idx][z_idx];

        m_ast   [c_idx][e_idx][z_idx] = (beta0 * m0 + N_cez * xbar_cez) / (beta0 + N_cez);
        beta_ast[c_idx][e_idx][z_idx] =  beta0 + N_cez;
        W_ast   [c_idx][e_idx][z_idx] = !( !W0 + N_cez * S_cez + beta0 * N_cez / (beta0 + N_cez) * (xbar_cez - m0) * ~(xbar_cez - m0));
        nu_ast  [c_idx][e_idx][z_idx] =    nu0 + N_cez;
        /*
          fprintf(stderr,"(c,e,z) = (%d,%d,%d)\n",c_idx,e_idx,z_idx);
          cerr << m_ast   [c_idx][e_idx][z_idx] << endl;
          cerr << beta_ast[c_idx][e_idx][z_idx] << endl;
          cerr << W_ast   [c_idx][e_idx][z_idx] << endl;
          cerr << nu_ast  [c_idx][e_idx][z_idx] << endl;
        */
      }
    }
  }

  // ================================================
  // t分布による判別
  // ================================================
  REAL ln_prob[CN][e_idx][z_idx];
  INT  e_idx_opt;
  INT  z_idx_opt;
  INT  correct;
  INT  total;
  
  correct = 0;
  total   = 0;
  for(n = 0;n < CN;n++){
    xn    = ~(X & n);
    c_idx = (INT)c[n];
    
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){        
        mu_cez =   m_ast[c_idx][e_idx][z_idx];
        Q_cez  = (nu_ast[c_idx][e_idx][z_idx] + 1.0 - D) * beta_ast[c_idx][e_idx][z_idx] / (beta_ast[c_idx][e_idx][z_idx] + 1.0) * W_ast[c_idx][e_idx][z_idx];
        f_cez  =  nu_ast[c_idx][e_idx][z_idx] + 1.0 - D;
        /*
          cerr << W_ast[c_idx][e_idx][z_idx] << endl;
          cerr << Q_cez << endl;
          cerr << beta_ast[c_idx][e_idx][z_idx] << endl;
        */
        ln_prob[n][e_idx][z_idx] = (N[c_idx][e_idx][z_idx] != 0.0) ? ln_S(xn,mu_cez,Q_cez,f_cez) : log(0.0);
      }
    }
    e_idx_opt = 0;
    z_idx_opt = 0;
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){
        if(ln_prob[n][e_idx_opt][z_idx_opt] < ln_prob[n][e_idx][z_idx]){
          e_idx_opt = e_idx;
          z_idx_opt = z_idx;
        }
      }
    }
    if((e_idx_opt == (INT)e[n]) && (z_idx_opt == (INT)z[n])){
      correct++;
    }
    total++;
  }

  fprintf(stderr,"alpha : %e | correct / total = %d / %d = %.2f\n",alpha,correct,total,(REAL)correct / (REAL)total);

  }
  
  return 0;
}
