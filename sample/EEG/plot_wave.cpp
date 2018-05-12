/***************************************************************** 
 *
 * 波形データを表示する. 
 *
 *                           Created  by Mamoru Ota (2018/04/27)
 * 
 *****************************************************************/

#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#include"RMatrix__fetch_csv.hpp"

void proc(RVector &wav){
  INT4 n;
  REAL ave;
  REAL re[1000];
  REAL im[1000];
  REAL re2[1000];
  REAL im2[1000];
  REAL f;
  
  ave = 0.0;
  for(n = 1000;n < 2000;n++){
    ave += wav[n];
  }
  ave /= 1000.0;
  for(n = 1000;n < 2000;n++){
    wav[n] -= ave;
  }

  for(n = 1000;n < 2000;n++){
    re[n - 1000] = wav[n] * (0.54 - 0.46 * cos(2.0 * M_PI * (n - 1000.0) / 1000.0));
    im[n - 1000] = 0.0;  
  }
  FFT(re,im,1000);

  for(n = 0;n < 1000;n++){
    re2[n] = 0.0;
    im2[n] = 0.0;
  }
  for(n = 0;n < 1000;n++){
    f = n * 0.25;
    if((3.0 <= f) && (f <= 50.0)){
      re2[n] = re[n];
      im2[n] = im[n];
      re2[1000 - n] =  re[n];
      im2[1000 - n] = -im[n];
    }
  }
  IFFT(re2,im2,1000);
  for(n = 1000;n < 2000;n++){
    wav[n] = re2[n - 1000] / (0.54 - 0.46 * cos(2.0 * M_PI * (n - 1000.0) / 1000.0));
    fprintf(stderr,"%e\n",im2[n - 1000]);
  }

}
          
int main(int argc,char *argv[]){
  RMatrix dat;
  RVector t;
  RVector ch[8];
  INT4    n;

  dat   = RMatrix__fetch_csv("./EEG_DATA.txt"," ","");
  t     = (dat |  3);
  ch[0] = (dat |  4);
  ch[1] = (dat |  5);
  ch[2] = (dat |  6);
  ch[3] = (dat |  7);
  ch[4] = (dat |  8);
  ch[5] = (dat |  9);
  ch[6] = (dat | 10);
  ch[7] = (dat | 11);

  proc(ch[0]);
  proc(ch[1]);
  proc(ch[2]);
  proc(ch[3]);
  proc(ch[4]);
  proc(ch[5]);
  proc(ch[6]);
  proc(ch[7]);

  FILE *fp;

  if((fp = fopen("wave.dat","w")) == NULL){
    exit(EXIT_FAILURE);
  }
  for(n = 1000;n < 2000;n++){
    fprintf(fp,"%e %e %e %e %e %e %e %e %e\n",
            t[n],
            ch[0][n],
            ch[1][n],
            ch[2][n],
            ch[3][n],
            ch[4][n],
            ch[5][n],
            ch[6][n],
            ch[7][n]);
  }
  fclose(fp);
  
  return 0;
}
