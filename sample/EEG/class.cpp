/***************************************************************** 
 *
 * 脳波(EEG)データのスペクトログラムデータの作成
 *
 *
 *                           Created  by Mamoru Ota (2018/04/27)
 * 
 *****************************************************************/

// データ個数 = 45 * 3 - 2 * 3 = 129サンプル

#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

RMatrix RMatrix__fetch_csv(const CHAR *filename,
                           const CHAR *delimiters,
                           const CHAR *comment_chars){
  FILE    *fp;
  TEXT_CSV csv;
  RMatrix  ret;
  INT      i,j;
  INT      n,m;
  
  if((fp = fopen(filename,"rb")) == NULL){
    exit(EXIT_FAILURE);
  }

  m = 0;
  for(n = 0;TEXT_CSV__READ_LINE(&csv,fp,delimiters,comment_chars) == 0;n++){
    if(m < csv.num){
       m = csv.num;
    }
  }

  if(m == 0){
    exit(EXIT_FAILURE);
  }

  ret = RMatrix(n,m);
  
  fseek(fp,0L,SEEK_SET);

  for(i = 0;TEXT_CSV__READ_LINE(&csv,fp,delimiters,comment_chars) == 0;i++){
    for(j = 0;j < csv.num;j++){
      ret[i][j] = atof(TEXT_CSV__GET_DATA(&csv,j));
    }
  }
  fclose(fp);

  return ret;
}

#define SAMP_FREQ (250.0)
#define SAMP_NUM  (1000)
#define CH_NUM    (8)
#define L         (50)
#define TRAIN_DATA_NUM (45 * 2)
#define DATA_NUM       (45 * 3)
#define K              (3)

int main(int argc,char *argv[]){
  INT4  i,j,ch,n;

  // =======================================================
  // 基本設定
  // =======================================================
  RMatrix F   (SAMP_NUM,2 * L);
  RVector time(SAMP_NUM);
  RVector freq(L);
  
  for(i = 0;i < SAMP_NUM;i++){
    time[i] = i * (1.0 / (REAL)SAMP_FREQ);
  }
  for(j = 0;j < L;j++){
    freq[j] = (j + 1 + 4 * 2) * (SAMP_FREQ / (REAL)SAMP_NUM);
  }
  
  for(i = 0;i < SAMP_NUM;i++){
    for(j = 0;j < L;j++){
      F[i][j + 0] = sqrt(2.0 / (REAL)SAMP_NUM) * cos(2.0 * M_PI * freq[j] * time[i]);
      F[i][j + L] = sqrt(2.0 / (REAL)SAMP_NUM) * sin(2.0 * M_PI * freq[j] * time[i]);
    }
  }

  // =======================================================
  // データの取得
  // =======================================================
  RMatrix dat;
  RVector v_ch[CH_NUM];
  RVector v   [CH_NUM][DATA_NUM];
  INT4    ans         [        ] = {
    1,2,0,1,1,0,2,1,2,1,2,0,2,1,0,1,2,0,1,2,1,0,1,0,2,1,0,1,2,1,0,0,1,2,1,0,2,1,0,2,1,2,0,2,1,
    1,2,0,0,2,1,2,1,2,1,0,0,2,1,2,1,2,0,2,1,0,2,1,0,1,2,0,1,0,1,2,1,0,1,0,1,2,1,2,0,0,2,0,1,0,
    1,0,2,1,0,2,2,1,2,0,1,2,0,1,2,1,0,1,0,2,1,0,2,2,1,1,0,0,1,0,2,2,0,1,2,1,2,0,1,2,0,1,2,0,1
  };

  dat = RMatrix__fetch_csv("./EEG_DATA.txt"," ","");

  for(ch = 0;ch < CH_NUM;ch++){
    v_ch[ch] = (dat |  (4 + ch));
  }

  for(ch = 0;ch < CH_NUM;ch++){
    for(n = 0;n < DATA_NUM;n++){
      v[ch][n] = RVector(SAMP_NUM);
      for(i = 0;i < SAMP_NUM;i++){
        v[ch][n][i] = v_ch[ch][n * SAMP_NUM + i];
      }
    }
  }

  // =======================================================
  // データの規格化
  // =======================================================
  RVector d[CH_NUM][DATA_NUM];
  
  for(ch = 0;ch < CH_NUM;ch++){
    for(n = 0;n < DATA_NUM;n++){
      d[ch][n]  = F * ~F * v[ch][n];
      d[ch][n] /= sqrt(~d[ch][n] * d[ch][n]);
    }
  }

  // =======================================================
  // 代表信号を計算
  // =======================================================
  RVector gamma[CH_NUM][K];
  RVector u    [CH_NUM][K];
  RVector tmp;
  INT4    k;

  for(ch = 0;ch < CH_NUM;ch++){
    for(k = 0;k < K;k++){
      tmp      = RVector(SAMP_NUM);
      for(n = 0;n < TRAIN_DATA_NUM;n++){
        if(ans[n] == k){
          tmp += d[ch][n];
        }else{
          tmp -= d[ch][n] / (K - 1.0);
        }
      }
      gamma[ch][k] = ~F * tmp;
      
      gamma[ch][k] /= sqrt(~gamma[ch][k] * gamma[ch][k]);
      u[ch][k]      = F * gamma[ch][k];
      /*
      fprintf(stderr,"ch = %d, k = %d\n",ch,k);
      cerr << ~gamma[ch][k] * gamma[ch][k] << endl;
      cerr << ~u[ch][k] * u[ch][k] << endl;
      */
    }
  }

  // =======================================================
  // 相関の計算
  // =======================================================
  RVector cor[CH_NUM][K];

  for(ch = 0;ch < CH_NUM;ch++){
    for(k = 0;k < K;k++){
      cor[ch][k] = RVector(DATA_NUM);
      for(n = 0;n < DATA_NUM;n++){
        cor[ch][k][n] = ~u[ch][k] * d[ch][n];
      }
    }
  }

  // =======================================================
  // 相関データの格納
  // =======================================================
  RVector x[DATA_NUM];

  for(n = 0;n < DATA_NUM;n++){
    x[n] = RVector(CH_NUM * K);
    for(ch = 0;ch < CH_NUM;ch++){
      for(k = 0;k < K;k++){
        x[n][ch * K + k] = cor[ch][k][n];
      }
    }
  }

  // =======================================================
  // 最適な確率(重み)を決定する. 
  // =======================================================
  RVector p(CH_NUM);
  REAL    p_sum;

  p_sum = 0.0;
  for(ch = 0;ch < CH_NUM;ch++){
    p[ch] = 0.0;
    for(n = 0;n < TRAIN_DATA_NUM;n++){
      p[ch] += x[n][ch * K + ans[n]];
    }
    if(p[ch] < 0.0){
      p[ch] = 0.0;
    }
    p_sum += p[ch];
  }

  for(ch = 0;ch < CH_NUM;ch++){
    p[ch] /= p_sum;
  }

  RVector y[DATA_NUM];

  for(n = 0;n < DATA_NUM;n++){
    y[n] = RVector(K);
    for(k = 0;k < K;k++){
      y[n][k] = 0.0;
      for(ch = 0;ch < CH_NUM;ch++){
        y[n][k] += p[ch] * x[n][ch * K + k];
      }
    }
  }

  // =======================================================
  // 平均ベクトルを求める. 
  // =======================================================
  RVector mu[K];
  INT4    co[K];

  for(k = 0;k < K;k++){
    mu[k] = RVector(CH_NUM * K);
    co[k] = 0;
  }
  for(n = 0;n < DATA_NUM;n++){
    mu[ans[n]] += x[n];
    co[ans[n]] ++;
  }  
  for(k = 0;k < K;k++){
    mu[k] /= (REAL)co[k];
    //cerr << mu[k] << endl;
  }
  //getchar();

  // =======================================================
  // 分散・共分散行列を求める. 
  // =======================================================
  RMatrix sigma[K];

  for(k = 0;k < K;k++){
    sigma[k] = RMatrix(CH_NUM * K,CH_NUM * K);
  }
  for(n = 0;n < DATA_NUM;n++){
    sigma[ans[n]] += (x[n] - mu[ans[n]]) * ~(x[n] - mu[ans[n]]);
  }  
  for(k = 0;k < K;k++){
    sigma[k] /= (REAL)(co[k] - 1.0);
    //cerr << sigma[k] << endl;
  }
  //getchar();

  RMatrix prob(DATA_NUM,K);
  RVector ln_prob(K);
  REAL    ln_prob_max;
  REAL    prob_sum;
  
  for(n = 0;n < DATA_NUM;n++){
    for(k = 0;k < K;k++){
      ln_prob[k] = -0.5 * ~(x[n] - mu[k]) * !sigma[k] * (x[n] - mu[k]) - 0.5 * log(det(sigma[k]));
    }
    ln_prob_max = ln_prob[0];
    for(k = 1;k < K;k++){
      if(ln_prob[k] > ln_prob_max){
        ln_prob_max = ln_prob[k];
      }
    }
    for(k = 0;k < K;k++){
      prob[n][k] = exp(ln_prob[k] - ln_prob_max);
    }
    prob_sum = 0.0;
    for(k = 0;k < K;k++){
      prob_sum += prob[n][k];
    }
    for(k = 0;k < K;k++){
      prob[n][k] /= prob_sum;
    }
  }  

  // =======================================================
  // 相関値の出力(前処理後のデータとみなす)
  // =======================================================
  FILE *fp;

  if((fp = fopen("cor.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 0;n < DATA_NUM;n++){
    fprintf(fp,"%d,%d",n,ans[n]);
    for(ch = 0;ch < CH_NUM;ch++){
      for(k = 0;k < K;k++){
        fprintf(fp,",%f",cor[ch][k][n]);
      }
    }
    fprintf(fp,"\n");
  }
  fclose(fp);

  // =======================================================
  // 全てのchの相関値の最大値を計算する. 
  // =======================================================
  RVector cor_max[K];

  for(k = 0;k < K;k++){
    cor_max[k] = RVector(DATA_NUM);    
  }
  for(k = 0;k < K;k++){
    for(n = 0;n < DATA_NUM;n++){
      cor_max[k][n] = -1.0;      
      for(ch = 0;ch < CH_NUM;ch++){
        if(cor_max[k][n] < cor[ch][k][n]){
          cor_max[k][n] = cor[ch][k][n];
        }
      }
    }
  }

  INT4 est_ans;
  INT4 corr_num = 0;
  INT4 data_num = 0;
  if((fp = fopen("cor_max.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 0;n < DATA_NUM;n++){
    est_ans = 0;
    for(k = 1;k < K;k++){
      if(cor_max[est_ans][n] < cor_max[k][n]){
        est_ans = k;
      }
    }
    if(est_ans == ans[n]){
      corr_num++;
    }
    data_num++;
    fprintf(fp,"%d %d %d ",n,ans[n],est_ans);
    for(k = 0;k < K;k++){
      fprintf(fp,"%f ",cor_max[k][n]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);

  fprintf(stderr,"%d/%d = %f\n",corr_num,data_num,corr_num / (REAL)data_num * 100.0);

  corr_num = 0;
  data_num = 0;

  if((fp = fopen("prob.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 0;n < DATA_NUM;n++){
    est_ans = 0;
    for(k = 1;k < K;k++){
      if(prob[n][est_ans] < prob[n][k]){
        est_ans = k;
      }
    }
    if(est_ans == ans[n]){
      corr_num++;
    }
    data_num++;
    fprintf(fp,"%d %d %d ",n,ans[n],est_ans);
    for(k = 0;k < K;k++){
      fprintf(fp,"%f ",prob[n][k]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  fprintf(stderr,"%d/%d = %f\n",corr_num,data_num,corr_num / (REAL)data_num * 100.0);
  
  corr_num = 0;
  data_num = 0;

  if((fp = fopen("y.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }

  for(n = 0;n < DATA_NUM;n++){
    est_ans = 0;
    for(k = 1;k < K;k++){
      if(y[n][est_ans] < y[n][k]){
        est_ans = k;
      }
    }
    if(est_ans == ans[n]){
      corr_num++;
    }
    data_num++;
    fprintf(fp,"%d %d %d ",n,ans[n],est_ans);
    for(k = 0;k < K;k++){
      fprintf(fp,"%f ",y[n][k]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  fprintf(stderr,"%d/%d = %f\n",corr_num,data_num,corr_num / (REAL)data_num * 100.0);

  cerr << "p" << endl;
  cerr <<  p  << endl;

  if((fp = fopen("rg.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 0;n < DATA_NUM;n++){
    if(ans[n] != 0){
      continue;
    }
    for(k = 0;k < K;k++){
      fprintf(fp,"%f ",y[n][k]);
    }
    fprintf(fp,"\n");
  }
  
  fclose(fp);

  if((fp = fopen("rt.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 0;n < DATA_NUM;n++){
    if(ans[n] != 1){
      continue;
    }
    for(k = 0;k < K;k++){
      fprintf(fp,"%f ",y[n][k]);
    }
    fprintf(fp,"\n");
  }
  
  fclose(fp);

  if((fp = fopen("rp.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 0;n < DATA_NUM;n++){
    if(ans[n] != 2){
      continue;
    }
    for(k = 0;k < K;k++){
      fprintf(fp,"%f ",y[n][k]);
    }
    fprintf(fp,"\n");
  }
  
  fclose(fp);


  // =====================================
  // 訓練データに対する判別精度
  // =====================================

  corr_num = 0;
  data_num = 0;

  for(n = 0;n < TRAIN_DATA_NUM;n++){
    est_ans = 0;
    for(k = 1;k < K;k++){
      if(y[n][est_ans] < y[n][k]){
        est_ans = k;
      }
    }
    if(est_ans == ans[n]){
      corr_num++;
    }
    data_num++;
  }
  fprintf(stderr,"training accuracy = %d/%d = %f\n",corr_num,data_num,corr_num / (REAL)data_num * 100.0);
  
  // =====================================
  // テストデータに対する判別精度
  // =====================================

  corr_num = 0;
  data_num = 0;

  for(n = TRAIN_DATA_NUM;n < DATA_NUM;n++){
    est_ans = 0;
    for(k = 1;k < K;k++){
      if(y[n][est_ans] < y[n][k]){
        est_ans = k;
      }
    }
    if(est_ans == ans[n]){
      corr_num++;
    }
    data_num++;
  }
  fprintf(stderr,"test accuracy = %d/%d = %f\n",corr_num,data_num,corr_num / (REAL)data_num * 100.0);

  return 0;
}
