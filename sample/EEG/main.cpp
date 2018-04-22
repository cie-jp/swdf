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
  RMatrix data1;
  RMatrix data2;
  RMatrix data3;
  INT4    offset1 = round((6.67 - 3.0) * samp_freq);
  INT4    offset2 = round((7.14 - 3.0) * samp_freq);
  INT4    offset3 = round((7.52 - 3.0) * samp_freq);
  INT4    frame;
  INT4    i,j;
  INT4    idx;
  REAL    t;
  
  data1 = RMatrix__fetch_csv("./data/OpenBCI-RAW-ita01.txt",", \t","%");
  data2 = RMatrix__fetch_csv("./data/OpenBCI-RAW-ita02.txt",", \t","%");
  data3 = RMatrix__fetch_csv("./data/OpenBCI-RAW-ita03.txt",", \t","%");

  // ======================================
  // EEGデータの内, 解析に用いるデータを出力する. 
  // ======================================
  for(frame = 0;frame < 45;frame++){
    for(j = 0;j < 4;j++){
      for(i = 0;i < 250;i++){
        idx = (frame * 4 + j) * 250 + i + offset1;
        t   = (idx - offset1) * dT + 45 * 4 * 250 * dT * 0;
        fprintf(stdout,"%3d %2d %3d %e %e %e %e %e %e %e %e %e\n",
                frame + 45 * 0,
                j,
                i,
                t,
                data1[idx][1],
                data1[idx][2],
                data1[idx][3],
                data1[idx][4],
                data1[idx][5],
                data1[idx][6],
                data1[idx][7],
                data1[idx][8]);
      }
    }
  }

  for(frame = 0;frame < 45;frame++){
    for(j = 0;j < 4;j++){
      for(i = 0;i < 250;i++){
        idx = (frame * 4 + j) * 250 + i + offset2;
        t   = (idx - offset2) * dT + 45 * 4 * 250 * dT * 1;
        fprintf(stdout,"%3d %2d %3d %e %e %e %e %e %e %e %e %e\n",
                frame + 45 * 1,
                j,
                i,
                t,
                data2[idx][1],
                data2[idx][2],
                data2[idx][3],
                data2[idx][4],
                data2[idx][5],
                data2[idx][6],
                data2[idx][7],
                data2[idx][8]);
      }
    }
  }

  for(frame = 0;frame < 45;frame++){
    for(j = 0;j < 4;j++){
      for(i = 0;i < 250;i++){
        idx = (frame * 4 + j) * 250 + i + offset3;
        t   = (idx - offset3) * dT + 45 * 4 * 250 * dT * 2;
        fprintf(stdout,"%3d %2d %3d %e %e %e %e %e %e %e %e %e\n",
                frame + 45 * 2,
                j,
                i,
                t,
                data3[idx][1],
                data3[idx][2],
                data3[idx][3],
                data3[idx][4],
                data3[idx][5],
                data3[idx][6],
                data3[idx][7],
                data3[idx][8]);
      }
    }
  }
  
  return 0;
}
