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

#include"classifier.hpp"
#include"RMatrix__fetch_csv.hpp"

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
