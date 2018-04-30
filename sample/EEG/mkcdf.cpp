/***************************************************************** 
 *
 * 脳波(EEG)データのCDF作成
 *
 *
 *                           Created  by Mamoru Ota (2018/04/25)
 * 
 *****************************************************************/

#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

int main(int argc,char *argv[]){
  const CHAR *filename[] = {"./data/OpenBCI-RAW-ita01.txt",
                            "./data/OpenBCI-RAW-ita02.txt",
                            "./data/OpenBCI-RAW-ita03.txt"};
  FILE       *fp;
  REAL        samp_freq = 250.0;          //[Hz]
  REAL        dT        = 1.0 / samp_freq;//[sec]
  INT4        k;
  CHAR        line[2048];
  INT4        id;
  REAL        ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8;
  REAL        ax,ay,az;
  INT4        hh,mm,ss,ms;
  for(k = 0;k < 3;k++){
    if((fp = fopen(filename[k],"r")) == NULL){
      exit(EXIT_FAILURE);
    }
    while(fgets(line,2048,fp) != NULL){
      if((line[0] ==  '%') ||
         (line[0] == '\r') ||
         (line[0] == '\n') ){
        continue;
      }
      sscanf(line,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d:%d:%d.%d",
             &id,
             &ch1,&ch2,&ch3,&ch4,&ch5,&ch6,&ch7,&ch8,
             &ax,&ay,&az,
             &hh,&mm,&ss,&ms);
    }
    fclose(fp);
  }

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
