/***************************************************************** 
 *
 * D次元データ(サンプル数: N)を, L次元に圧縮し, K分類する. 
 * (教師ラベルが与えられる)
 * 入力信号 : D次元データ
 * 中間信号 : 次元圧縮後のL次元データ
 * 出力信号 : K分類の確率
 * (注) 学習率を高く設定すると発散する
 *
 *                           Created  by Mamoru Ota (2018/04/27)
 * 
 *****************************************************************/

#include"CLDIA.h"

using namespace std;
using namespace CLDIA;


class Classifier{

private:

  RMatrix X ;//入力データセット X(入力データ数, 入力データの次元) X[n][d]
  RMatrix Z ;//出力データセット Z(入力データ数, クラスタ数)       Z[n][k]
  INT4    N ;//入力データ数
  INT4    D ;//入力データの次元
  INT4    L ;//次元圧縮後の次元
  INT4    K ;//クラスタ数
  RMatrix W1;//入力->中間 重み行列 W1(次元圧縮後の次元,入力データの次元 + 1) W1[l][d]
  RMatrix W2;//中間->出力 重み行列 W2(クラスタ数,次元圧縮後の次元 + 1)       W2[k][l]
  RMatrix Y ;//中間データセット Y(入力データ数, 次元圧縮後の次元) Y[n][l]
  RMatrix P ;//出力データセット P(入力データ数, クラスタ数)       P[n][k]  
  REAL    a ;//学習率
public:

  RMatrix prediction(RMatrix Xtmp){
    INT4    Ntmp = Xtmp.get_row();
    RMatrix Ytmp(Ntmp,L);
    RMatrix Ptmp(Ntmp,K);
    RMatrix Ztmp(Ntmp,K);
    INT4    n,d,l,k,k0;
    REAL    tmp;
    REAL    max,sum;

    if(Xtmp.get_col() != D){
      cerr << "ERROR : 入力データの次元が一致しません. " << endl;
      exit(EXIT_FAILURE);
    }
    Ntmp = Xtmp.get_row();
    // Ytmpの計算
    for(n = 0;n < Ntmp;n++){
      for(l = 0;l < L;l++){
	tmp  = 0.0;
	for(d = 0;d < D;d++){
	  tmp += W1[l][d] * Xtmp[n][d];
	}
	tmp += W1[l][D];
	Ytmp[n][l] = tmp;
      }      
    }

    // Ptmpの計算
    for(n = 0;n < Ntmp;n++){
      for(k = 0;k < K;k++){
	tmp  = 0.0;
	for(l = 0;l < L;l++){
	  tmp += W2[k][l] * Ytmp[n][l];
	}
	tmp += W2[k][L];
	Ptmp[n][k] = tmp;
      }
      max = Ptmp[n][k];
      for(k = 1;k < K;k++){
	if(max < Ptmp[n][k]){
	   max = Ptmp[n][k];
	}
      }
      sum = 0.0;
      for(k = 0;k < K;k++){
	sum += exp(Ptmp[n][k] - max);
      }
      for(k = 0;k < K;k++){
	Ptmp[n][k] = exp(Ptmp[n][k] - max) / sum;
      }
    }

    // Ztmpの計算
    for(n = 0;n < Ntmp;n++){
      k0 = 0;
      for(k = 1;k < K;k++){
	if(Ptmp[n][k0] < Ptmp[n][k]){
	  k0 = k;
	}
      }
      Ztmp[n][k0] = 1.0;
    }
    return Ztmp;
  }

  void calculate_Y_and_P(){
    INT4 n,d,l,k;
    REAL tmp;
    REAL max,sum;

    // Yの計算
    for(n = 0;n < N;n++){
      for(l = 0;l < L;l++){
	tmp  = 0.0;
	for(d = 0;d < D;d++){
	  tmp += W1[l][d] * X[n][d];
	}
	tmp += W1[l][D];
	Y[n][l] = tmp;
      }      
    }

    // Pの計算
    for(n = 0;n < N;n++){
      for(k = 0;k < K;k++){
	tmp  = 0.0;
	for(l = 0;l < L;l++){
	  tmp += W2[k][l] * Y[n][l];
	}
	tmp += W2[k][L];
	P[n][k] = tmp;
      }
      max = P[n][k];
      for(k = 1;k < K;k++){
	if(max < P[n][k]){
	   max = P[n][k];
	}
      }
      sum = 0.0;
      for(k = 0;k < K;k++){
	sum += exp(P[n][k] - max);
      }
      for(k = 0;k < K;k++){
	P[n][k] = exp(P[n][k] - max) / sum;
      }
    }
  }

  REAL calculate_J(INT4 flag = 1){
    INT4 n,k;
    REAL tmp;
    
    if(flag){
      calculate_Y_and_P();
    }
    tmp = 0.0;
    for(n = 0;n < N;n++){
      for(k = 0;k < K;k++){
	tmp += Z[n][k] * log(P[n][k]);
      }
    }        
    return tmp;
  }

  void update_W1_and_W2(INT4 flag = 1){
    INT4    n,d,l,k;
    REAL    tmp;
    RMatrix q;

    if(flag){
      calculate_Y_and_P();
    }    
    q = Z - P;
    // W1の更新
    for(l = 0;l < L;l++){
      for(d = 0;d <= D;d++){
	tmp = 0.0;
	for(n = 0;n < N;n++){
	  for(k = 0;k < K;k++){	    	    
	    tmp += q[n][k] * W2[k][l] * ((d != D) ? X[n][d] : 1.0);
	  }
	}
	W1[l][d] += a * tmp;
      }
    }    
    // W2の更新
    for(k = 0;k < K;k++){
      for(l = 0;l <= L;l++){
	tmp = 0.0;
	for(n = 0;n < N;n++){
	  tmp += q[n][k] * ((l != L) ? Y[n][l] : 1.0);
	}
	W2[k][l] += a * tmp;
      }
    }
  }

public:
  void show_info(INT4 flag = 1){
    INT4 k0;
    INT4 correct;
    INT4 n,k;

    if(flag){
      calculate_Y_and_P();
    }
    cerr << (P | Z)       << endl;
    cerr << calculate_J() << endl;
    
    correct = 0;
    for(n = 0;n < N;n++){
      k0 = 0;
      for(k = 1;k < K;k++){
	if(P[n][k0] < P[n][k]){
	  k0 = k;
	}
      }
      if(Z[n][k0] == 1.0){
	correct++;
      }
    }
    fprintf(stderr,"correct = %d, data num = %d, accuracy = %.3f[%%]\n",correct,N,(REAL)correct / (REAL)N * 100.0);
  }

public:
  Classifier(RMatrix &X,  //入力データセット X(入力データ数, 入力データの次元) X[n][d]
	     RMatrix &Z,  //出力データセット Z(入力データ数, クラスタ数)       Z[n][k] = 1 of K
	     INT4     L,  //次元圧縮後の次元
	     REAL     a){ //学習率
    INT4 n,k;
    REAL sum;

    if(X.get_row() != Z.get_row()){
      cerr << "ERROR : 入力と出力のデータ数が一致しません." << endl;
      exit(EXIT_FAILURE);
    }
    
    for(n = 0;n < N;n++){
      sum = 0.0;
      for(k = 0;k < K;k++){
	if((Z[n][k] != 0.0) && (Z[n][k] != 1.0)){
	  cerr << "ERROR : Z[n][k] != 0 && Z[n][k] != 1" << endl;
	  exit(EXIT_FAILURE);
	}
	sum += Z[n][k];
      }
      if(sum != 1.0){
	cerr << "ERROR : Sum_{k} Z[n][k] != 1" << endl;
	exit(EXIT_FAILURE);
      }      
    }        

    this->X  = X;
    this->Z  = Z;
    this->N  = X.get_row();
    this->D  = X.get_col();
    this->L  = L;
    this->K  = Z.get_col();    
    this->W1 = RMatrix::random(this->L,this->D + 1);
    this->W2 = RMatrix::random(this->K,this->L + 1);    
    this->Y  = RMatrix        (this->N,this->L);
    this->P  = RMatrix        (this->N,this->K);
    this->a  = a;
  }
    
};

#define D (250 * 4 * 8)
#define K (3)
#define L (3)
#define N (100)
#define a (0.0001)

#define N2 (50)

int main(int argc,char *argv[]){
  RMatrix X(N,D),X2(N2,D);
  RMatrix Z(N,K),Z2(N2,K);
  RANDOM  rnd;
  INT4    i,j;

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < N;i++){
    switch(i % K){
    case 0:
      for(j = 0;j < D;j++){
	X[i][j] = RANDOM__NORMAL(&rnd, 0.0,1.0);
      }
      break;
    case 1:
      for(j = 0;j < D;j++){
	X[i][j] = RANDOM__NORMAL(&rnd, 1.0,1.0);
      }
      break;
    case 2:
      for(j = 0;j < D;j++){
	X[i][j] = RANDOM__NORMAL(&rnd,-1.0,1.0);
      }
      break;
    }
    Z[i][i % K] = 1.0;
  }

  for(i = 0;i < N2;i++){
    switch(i % K){
    case 0:
      for(j = 0;j < D;j++){
	X2[i][j] = RANDOM__NORMAL(&rnd, 0.0,1.0);
      }
      break;
    case 1:
      for(j = 0;j < D;j++){
	X2[i][j] = RANDOM__NORMAL(&rnd, 1.0,1.0);
      }
      break;
    case 2:
      for(j = 0;j < D;j++){
	X2[i][j] = RANDOM__NORMAL(&rnd,-1.0,1.0);
      }
      break;
    }
    Z2[i][i % K] = 1.0;
  }

  cerr << (X | Z) << endl;

  Classifier cl(X,Z,L,a);
  
  cl.show_info();
  for(i = 0;i < 3000;i++){
    cl.update_W1_and_W2();
    cl.show_info();
  }

  cerr << (cl.prediction(X) | Z) << endl;
  cerr << (cl.prediction(X2) | Z2) << endl;

  INT4    count;
  INT4    n,k;
  RMatrix Z2_pred;

  Z2_pred = cl.prediction(X2);

  count = 0;
  for(n = 0;n < Z2.get_row();n++){
    for(k = 0;k < Z2.get_col();k++){
      count += Z2_pred[n][k] * Z2[n][k];
    }
  }
  fprintf(stderr,"count = %d / data num = %d, accuracy = %.2f[%%]\n",count,Z2.get_row(),(REAL)count / (REAL)Z2.get_row() * 100.0);

  return 0;
}
