/***************************************************************** 
 *
 * 脳波(EEG)データによる3状態判別
 *
 *
 *                           Created  by Mamoru Ota (2018/04/22)
 * 
 *****************************************************************/

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

int main(int argc,char *argv[]){
  // ======================================
  // EEGデータを格納する.
  // 3 (1秒) => 2 (1秒) => 1 (1秒) => 無 (1秒) を繰り返す.
  // ======================================
  REAL    samp_freq = 250.0;          //[Hz]
  REAL    dT        = 1.0 / samp_freq;//[sec]
  RMatrix data;
  INT4    frame,i,j,k;
  REAL    t;
  INT4    idx,idx0;
  REAL    re[250];
  REAL    im[250];
  REAL    window;
  REAL    p[8][250];
  RMatrix A(48 * 8,45 * 4 * 1);//1回の試行
  FILE   *fp;
  REAL    min;

  data = RMatrix__fetch_csv("./EEG_DATA.txt"," ","");

  // ======================================
  // EEGデータの内, 解析に用いるデータを出力する. 
  // ======================================
  
  /*
  for(frame = 0;frame < 135;frame++){
    for(j = 0;j < 4;j++){
      for(i = 0;i < 250;i++){
        idx = (frame * 4 + j) * 250 + i;
        t   = data[idx][3];
        fprintf(stdout,"%3d %2d %3d %e %e %e %e %e %e %e %e %e\n",
                (INT4)data[idx][0],
                (INT4)data[idx][1],
                (INT4)data[idx][2],
                data[idx][3],                
                data[idx][4],
                data[idx][5],
                data[idx][6],
                data[idx][7],
                data[idx][8],
                data[idx][9],
                data[idx][10],
                data[idx][11]                
                );
      }
    }
  }
  */
  
  // ======================================
  // 4秒インターバルであるため, 4秒の周期(0.25 Hz)の整数倍の信号のピークが現れそう.
  // ならば, 4000点FFTであれば, 250Hz / 4000点 = 0.0625 Hz分解能として扱える.
  // 0.0625Hz * 4 = 0.25であるので, 4点に一点のデータは用いないことにすることで, 学習精度を向上させることができるはず.
  // 4000点FFTデータでは, 250点 x 16回 である. 
  // まずは, 250点ごとにFFT(周波数分解能は1Hz)を行いパワースペクトルを計算する. 3,2,1,無が見えているときのスペクトログラムを表示する. 
  // ======================================
  for(frame = 0;frame < 45;frame++){
    for(j = 0;j < 4;j++){
      idx0 = (frame * 4 + j) * 250;
      for(k = 0;k < 8;k++){
	for(i = 0;i < 250;i++){
	  idx    = idx0 + i;
	  window = 0.54 - 0.46 * cos(2.0 * M_PI * i / (250.0 - 1.0));
	  re[i]  = data[idx][4 + k] * window;
	  im[i]  = 0.0;      
	}
	FFT(re,im,250);
	for(i = 0;i < 250 / 2;i++){
	  p[k][i] = 10.0 * log10(re[i] * re[i] + im[i] * im[i]);
	}
      }
      for(k = 0;k < 8;k++){      
	for(i = 0;i < 48;i++){
	  A[48 * k + i][frame * 4 + j] = p[k][i + 3];
	}
      }
    }
  }
  min = 0.0;
  for(i = 0;i < A.get_row();i++){
    for(j = 0;j < A.get_col();j++){
      if(min > A[i][j]){
	min = A[i][j];
      }
    }
  }
  for(i = 0;i < A.get_row();i++){
    for(j = 0;j < A.get_col();j++){
      A[i][j] += min;
    }
  }

  if((fp = fopen("A.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < A.get_row();i++){
    for(j = 0;j < A.get_col();j++){
      fprintf(fp,"%d %d %e\n",i,j,A[i][j]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);

  INT4    KK = 3;
  INT4    l;
  REAL    error;
  RMatrix H(384,KK),U(KK,360 / 2),A_Ut,H_U_Ut,Ht_A,Ht_H_U,H_U,E;
  RANDOM  rnd;

  RANDOM__INITIALIZE(&rnd);

  for(i = 0;i < H.get_row();i++){
    for(j = 0;j < H.get_col();j++){
      H[i][j] = RANDOM__UNIFORM(&rnd,0.0,1.0);
    }
  }
  for(i = 0;i < U.get_row();i++){
    for(j = 0;j < U.get_col();j++){
      U[i][j] = RANDOM__UNIFORM(&rnd,0.0,1.0);
    }
  }
  for(l = 0;l < 15000;l++){
    A_Ut   =  A * ~U;
    H_U_Ut =  H *  U * ~U;
    H      =  (H % A_Ut) / H_U_Ut;
    Ht_A   = ~H *  A;
    Ht_H_U = ~H *  H *  U;
    U      =  (U % Ht_A) / Ht_H_U;
    H_U    =  H *  U;
    E      =  A - H_U;
    error  =  0.0;
    for(i = 0;i < E.get_row();i++){
      for(j = 0;j < E.get_col();j++){
	error += E[i][j] * E[i][j];
      }
    }
    fprintf(stderr,"LOOP : %3d | ERROR : %e\n",l,error);
  }

  if((fp = fopen("HU.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < H_U.get_row();i++){
    for(j = 0;j < H_U.get_col();j++){
      fprintf(fp,"%d %d %e\n",i,j,H_U[i][j]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);

  if((fp = fopen("U.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(j = 0;j < U.get_col();j++){
    fprintf(fp,"%d %e %e %e\n",j,U[0][j],U[1][j],U[2][j]);
  }

  fclose(fp);


  // =============================================================
  INT4 ans[45 * 3] = {
    1,2,0,1,1,0,2,1,2,1,2,0,2,1,0,1,2,0,1,2,1,0,1,0,2,1,0,1,2,1,0,0,1,2,1,0,2,1,0,2,1,2,0,2,1,
    1,2,0,0,2,1,2,1,2,1,0,0,2,1,2,1,2,0,2,1,0,2,1,0,1,2,0,1,0,1,2,1,0,1,0,1,2,1,2,0,0,2,0,1,0,
    1,0,2,1,0,2,2,1,2,0,1,2,0,1,2,1,0,1,0,2,1,0,2,2,1,1,0,0,1,0,2,2,0,1,2,1,2,0,1,2,0,1,2,0,1
  };

  if((fp = fopen("ans_g.txt","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < 135 * 4;i++){
    fprintf(fp,"%d %d\n",i,(ans[i / 4] == 0) ? 1 : 0);
  }
  fclose(fp);

  if((fp = fopen("ans_t.txt","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < 135 * 4;i++){
    fprintf(fp,"%d %d\n",i,(ans[i / 4] == 1) ? 1 : 0);
  }
  fclose(fp);

  if((fp = fopen("ans_p.txt","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < 135 * 4;i++){
    fprintf(fp,"%d %d\n",i,(ans[i / 4] == 2) ? 1 : 0);
  }
  fclose(fp);

  return 0;
}
