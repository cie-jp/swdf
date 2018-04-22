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
  j = 3;
  for(frame = 0;frame < 135;frame++){
    idx0 = (frame * 4 + j) * 250;
    t = data[idx0 + 250 * j][3];
    for(k = 0;k < 8;k++){
      for(i = 0;i < 250;i++){
        idx    = idx0 + i;
        window = 0.54 - 0.46 * cos(2.0 * M_PI * i / (250.0 - 1.0));
        re[i]  = data[idx][4 + k] * window;
        im[i]  = 0.0;      
      }
      FFT(re,im,250);
      t = data[idx0 + 250 * j][3];
      for(i = 0;i < 250 / 2;i++){
        p[k][i] = 10.0 * log10(re[i] * re[i] + im[i] * im[i]);
      }
    }

    for(i = 0;i < 250 / 2;i++){
      fprintf(stdout,"%e %e %e %e %e %e %e %e %e %e\n",
              t,
              1.0 * i,
              p[0][i],
              p[1][i],
              p[2][i],
              p[3][i],
              p[4][i],
              p[5][i],
              p[6][i],
              p[7][i]
              );
    }
    fprintf(stdout,"\n");
  }
  
  return 0;
}
