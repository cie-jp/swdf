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

REAL ln_S(RVector &x,RVector &mu,RMatrix &Q,REAL ln_det_Q,REAL f){
  INT D = x.get_row();
  return lgamma((f + D) / 2.0) - lgamma(f / 2.0) - D / 2.0 * log(M_PI * f) + 0.5 * ln_det_Q - (f + D) / 2.0 * log(1.0 + (1.0 / f) * ~(x - mu) * Q * (x - mu));
}

#define E (4) //環境数      (0:Day 1, 1:Day 2,2:Day 3, 3:Day 4)
#define C (8) //チャンネル数
#define K (4) //動作状態数  (0:グー, 1:チョキ, 2:パー, 3:動作なし)

#define N_test_max (1000)

int main(int argc,char *argv[]){
  RMatrix dat;

  RVector e;
  RVector z;
  RMatrix X[C];

  RVector e_test;
  RVector z_test;
  RMatrix X_test[C];

  INT    DC; //次元数 x チャンネル数
  INT     N; //データ数(訓練)
  INT     D; //次元数

  INT     N_test;//テストデータ数

  RVector xcn;
  INT     n,m;
  
  RVector m0;
  REAL    beta0;
  RMatrix W0;
  REAL    nu0;
  REAL    alpha;

  REAL    num     [C][E][K];
  RVector xbar    [C][E][K];
  RMatrix S       [C][E][K];

  INT     c_idx;
  INT     e_idx;
  INT     z_idx;
  
  REAL    num_cez;
  RVector xbar_cez;
  RMatrix S_cez;
  
  RVector m_ast   [C][E][K];
  REAL    beta_ast[C][E][K];
  RMatrix W_ast   [C][E][K];
  REAL    nu_ast  [C][E][K];

  RVector mu      [C][E][K];
  RMatrix Q       [C][E][K];
  REAL    ln_det_Q[C][E][K];
  REAL    f       [C][E][K];

  REAL ln_prob0   [C][E][K][N_test_max];
  REAL ln_prob1      [E][K][N_test_max];//全チャンネルの情報を統合した対数確率
  
  INT  correct0;//環境が分からない場合
  INT  correct1;//環境を知っている場合
  INT  total;
  INT  e_idx_opt;
  INT  z_idx_opt;
  
  // ================================================
  // データの入力
  // ================================================
  
  dat = RMatrix__fetch_csv("./train.csv",", \t,","%");

  DC  = dat.get_col() - 2;
  N   = dat.get_row();
  D   = DC / C;

  e   = dat |  0;
  z   = dat |  1;
  
  for(c_idx = 0;c_idx < C;c_idx++){
    X[c_idx]    = dat | (2 + c_idx * D);
    for(m = 1;m < D;m++){
      X[c_idx] |= dat | (2 + c_idx * D + m);
    }
  }

  dat = RMatrix__fetch_csv("./test.csv",", \t,","%");

  N_test   = dat.get_row();
  e_test   = dat |  0;
  z_test   = dat |  1;
  
  for(c_idx = 0;c_idx < C;c_idx++){
    X_test[c_idx]    = dat | (2 + c_idx * D);
    for(m = 1;m < D;m++){
      X_test[c_idx] |= dat | (2 + c_idx * D + m);
    }
  }

  fprintf(stderr,"Data Input Completed!\n");

  // ================================================
  // 統計量の計算
  // ================================================
  for(c_idx = 0;c_idx < C;c_idx++){
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){
        num [c_idx][e_idx][z_idx] = 0.0;
        xbar[c_idx][e_idx][z_idx] = RVector(D);
        S   [c_idx][e_idx][z_idx] = RMatrix(D,D);
      }
    }
  }

  for(n = 0;n < N;n++){
    for(c_idx = 0;c_idx < C;c_idx++){
      xcn = ~(X[c_idx] & n);
      num [c_idx][(INT)e[n]][(INT)z[n]] += 1.0;
      xbar[c_idx][(INT)e[n]][(INT)z[n]] += xcn;
      S   [c_idx][(INT)e[n]][(INT)z[n]] += xcn * ~xcn;
    }
  }

  for(c_idx = 0;c_idx < C;c_idx++){
    for(e_idx = 0;e_idx < E;e_idx++){
      for(z_idx = 0;z_idx < K;z_idx++){
        if(num[c_idx][e_idx][z_idx] == 0.0){
          continue;
        }        
        xbar[c_idx][e_idx][z_idx] /= num [c_idx][e_idx][z_idx];
        S   [c_idx][e_idx][z_idx] /= num [c_idx][e_idx][z_idx];
        S   [c_idx][e_idx][z_idx] -= xbar[c_idx][e_idx][z_idx] * ~xbar[c_idx][e_idx][z_idx];
      }
    }
  }

  for(alpha = 3.0e-3;alpha <= 1.0e+2;alpha *= 2.0){
    // ================================================
    // 事前分布のハイパーパラメータ設定
    // ================================================
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
	  num_cez  = num [c_idx][e_idx][z_idx];
	  xbar_cez = xbar[c_idx][e_idx][z_idx];
	  S_cez    = S   [c_idx][e_idx][z_idx];
	  
	  m_ast   [c_idx][e_idx][z_idx] = (beta0 * m0 + num_cez * xbar_cez) / (beta0 + num_cez);
	  beta_ast[c_idx][e_idx][z_idx] =  beta0 + num_cez;
	  W_ast   [c_idx][e_idx][z_idx] = !( !W0 + num_cez * S_cez + beta0 * num_cez / (beta0 + num_cez) * (xbar_cez - m0) * ~(xbar_cez - m0));
	  nu_ast  [c_idx][e_idx][z_idx] =    nu0 + num_cez;
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
    // t分布のパラメータの計算
    // ================================================
    for(c_idx = 0;c_idx < C;c_idx++){	
      for(e_idx = 0;e_idx < E;e_idx++){
	for(z_idx = 0;z_idx < K;z_idx++){        
	  mu      [c_idx][e_idx][z_idx] =   m_ast  [c_idx][e_idx][z_idx];
	  Q       [c_idx][e_idx][z_idx] = (nu_ast  [c_idx][e_idx][z_idx] + 1.0 - D) * beta_ast[c_idx][e_idx][z_idx] / (beta_ast[c_idx][e_idx][z_idx] + 1.0) * W_ast[c_idx][e_idx][z_idx];
	  ln_det_Q[c_idx][e_idx][z_idx] =  ln_det(Q[c_idx][e_idx][z_idx]);
	  f       [c_idx][e_idx][z_idx] =  nu_ast  [c_idx][e_idx][z_idx] + 1.0 - D;
	}
      }
    }

    // ================================================
    // データごとのクラス負担率の計算
    // ================================================  
    for(n = 0;n < N_test;n++){
      for(c_idx = 0;c_idx < C;c_idx++){	
	xcn = ~(X_test[c_idx] & n);
	for(e_idx = 0;e_idx < E;e_idx++){
	  for(z_idx = 0;z_idx < K;z_idx++){        
	    ln_prob0[c_idx][e_idx][z_idx][n] = (num[c_idx][e_idx][z_idx] != 0.0) ? ln_S(xcn,mu[c_idx][e_idx][z_idx],Q[c_idx][e_idx][z_idx],ln_det_Q[c_idx][e_idx][z_idx],f[c_idx][e_idx][z_idx]) : log(0.0);
	  }
	}
      }
    }

    // ================================================
    // 全チャンネルの情報統合
    // ================================================
    for(n = 0;n < N_test;n++){
      for(e_idx = 0;e_idx < E;e_idx++){
	for(z_idx = 0;z_idx < K;z_idx++){        
	  ln_prob1[e_idx][z_idx][n] = 0.0;
	  for(c_idx = 0;c_idx < C;c_idx++){	
	    ln_prob1[e_idx][z_idx][n] += ln_prob0[c_idx][e_idx][z_idx][n];
	  }
	}
      }
    }

    // ================================================
    // 判別精度の計算
    // ================================================  
    correct0  = 0;
    correct1  = 0;
    total     = 0;

    for(n = 0;n < N_test;n++){
      // argmax _{(e,z)} P(e,z)
      e_idx_opt = 0;
      z_idx_opt = 0;
      for(e_idx = 0;e_idx < E;e_idx++){
	for(z_idx = 0;z_idx < K;z_idx++){
	  if(ln_prob1[e_idx_opt][z_idx_opt][n] < ln_prob1[e_idx][z_idx][n]){
	    e_idx_opt = e_idx;
	    z_idx_opt = z_idx;
	  }
	}
      }
      if((e_idx_opt == (INT)e_test[n]) && (z_idx_opt == (INT)z_test[n])){
	correct0++;
      }

      // argmax _{(e,z)} P(e,z) s.t. e = e_test
      e_idx_opt = (INT)e_test[n];
      z_idx_opt = 0;
      for(z_idx = 0;z_idx < K;z_idx++){
	if(ln_prob1[e_idx_opt][z_idx_opt][n] < ln_prob1[e_idx][z_idx][n]){
	  z_idx_opt = z_idx;
	}
      }
      if( z_idx_opt == (INT)z_test[n] ){
	correct1++;
      }

      total++;
    }

    // ================================================
    // 判別精度の出力(correct0よりcorrect1が精度が高ければ環境情報が判別に影響することが示唆される)
    // ================================================      
    fprintf(stderr,"alpha : %e | correct0 / total = %d / %d = %.2f | correct1 / total = %d / %d = %.2f\n",
	    alpha,
	    correct0,total,(REAL)correct0 / (REAL)total,
	    correct1,total,(REAL)correct1 / (REAL)total);

    fprintf(stdout,"%e %e %e\n",
	    alpha,
	    (REAL)correct0 / (REAL)total * 100.0,
	    (REAL)correct1 / (REAL)total * 100.0);

  }
  
  return 0;
}
