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

#include"SVGPlot.h"

class plot{
private:
  SVGPLOT plt;
public:
  plot(){
    SVGPLOT__INITIALIZE_002(&plt,"SVG_TEST1.svg");
    SVGPLOT_PALETTE__Create10(&plt.pal);
  }
  void contour(RMatrix &variable,RVector &depend_0,RVector &depend_1){
    SVGPLOT__XYZ_CONTOUR(&plt,
                         &depend_0[0],depend_0.get_dim(),
                         &depend_1[0],depend_1.get_dim(),
                         &variable[0][0],
                         -1.0,-1.0,0);
    SVGPLOT__XY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    1,0,1,0,
                    1);
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
  }
  void contour(RMatrix &variable,EVector &depend_0,RVector &depend_1){
    SVGPLOT__TYZ_CONTOUR(&plt,
                         &depend_0[0],depend_0.get_dim(),
                         &depend_1[0],depend_1.get_dim(),
                         &variable[0][0],
                         -1.0,-1.0,0);
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    1,1,1,1,
                    1,0,1,0,
                    1);
    SVGPLOT__COLORBAR(&plt,
                      1,1,
                      2,2,
                      2,0,
                      1);
  }
  void lplot(RVector &x,RVector &y){
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__XY_LPLOT(&plt,
                      x.get_dat(),
                      y.get_dat(),
                      x.get_dim(),
                      -1.0,-1.0,-1.0,0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round");
  }
  void lplot(EVector &x,RVector &y){
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__TY_LPLOT(&plt,
                      x.get_dat(),
                      y.get_dat(),
                      x.get_dim(),
                      -1.0,-1.0,0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round");
  }

  void pplot(RVector &x,RVector &y){    
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__XY_PPLOT(&plt,
                      x.get_dat(),y.get_dat(),x.get_dim(),
                      2.0,
                      0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round","#FF0000");
  }

  void pplot(EVector &x,RVector &y){    
    if(x.get_dim() != y.get_dim()){
      ERROR__SHOW("x.dim != y.dim");
      exit(EXIT_FAILURE);
    }
    SVGPLOT__TY_PPLOT(&plt,
                      x.get_dat(),y.get_dat(),x.get_dim(),
                      2.0,
                      0,
                      "1.0","#000000","0.5px",NULL,NULL,"round","round","#FF0000");
  }

  void auxx(){
    SVGPLOT__XY_AUX(&plt,
                    1,1,1,1,
                    3,3,3,3,
                    1,2,1,2,
                    1);
  }
  void auxt(){
    SVGPLOT__TY_AUX(&plt,
                    1,1,1,1,
                    3,3,3,3,
                    1,2,1,2,
                    1);
  }

  ~plot(){
    SVGPLOT__FINALIZE(&plt);
  }
};

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
  REAL    samp_freq = 250.0;          //[Hz]
  REAL    dT        = 1.0 / samp_freq;//[sec]
  RMatrix dat;
  RVector t;
  RVector ch[8];
  
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

  REAL ave;

  //cout << (t | ch[0]) << endl;
  /*
  plot p;

  p.lplot(t,ch[0]);
  p.auxx();
  */

#define FFT_PTS  (50)
#define FFT_PTSH (FFT_PTS / 2)  
#define CH_NUM   (8)

  REAL    re[FFT_PTS];
  REAL    im[FFT_PTS];
  REAL    window;
  INT4    num = dat.get_row();
  INT4    i,j,k,l;
  RMatrix spec[CH_NUM];
  EVector epoch(num);
  RVector freq (FFT_PTSH);


  // =================================
  // DC成分の除去
  // =================================
  for(k = 0;k < CH_NUM;k++){
    for(i = 0;i < 3;i++){
      ave = 0.0;
      for(j = 0;j < 250 * 4 * 45;j++){
        ave += ch[k][i * 250 * 4 * 45 + j];
      }
      ave /= 250.0 * 4 * 45;
      for(j = 0;j < 250 * 4 * 45;j++){
        ch[k][i * 250 * 4 * 45 + j] -= ave;
      }      
    }
  }
  
  for(k = 0;k < CH_NUM;k++){
    spec[k] = RMatrix(num,FFT_PTSH);
  }
  for(k = 0;k < CH_NUM;k++){

    for(i = 0;i < num;i++){
      for(j = 0;j < FFT_PTS ;j++){
        re[j] = 0.0;
        im[j] = 0.0;
      }
      for(j = 0;j < FFT_PTS ;j++){
        l = i - FFT_PTSH + j;
        if((l < 0) || (num <= l)){
          continue;
        }
        window = 0.54 - 0.46 * cos(2.0 * M_PI * j / (REAL)FFT_PTS);//Hamming窓
        re[j]  = ch[k][l] * window;
      }
      FFT(re,im,FFT_PTS);
      for(j = 0;j < FFT_PTSH;j++){
        spec[k][i][j] = sqrt(re[j] * re[j] + im[j] * im[j]);
      }
    }

  }

  REAL    re2[1000];//FFT点数(4秒)
  REAL    im2[1000];//FFT点数(4秒)
  RMatrix mspec[CH_NUM];
  INT4    q;
  
  for(k = 0;k < CH_NUM;k++){
    mspec[k] = RMatrix(num / 1000 * 500,FFT_PTSH);
  }

  for(k = 0;k < CH_NUM;k++){
    for(i = 0;i < num / 1000;i++){

      for(j = 0;j < FFT_PTS ;j++){

        for(q = 0;q < 1000;q++){
          re2[q] = 0.0;
          im2[q] = 0.0;
        }
        for(q = 0;q < 1000;q++){
          l = 1000 * i + q;
          if((l < 0) || (num <= l)){
            continue;
          }
          window = 0.54 - 0.46 * cos(2.0 * M_PI * q / 1000.0);//Hamming窓
          re2[q] = spec[k][l][j] * window;
        }
        FFT(re2,im2,1000);
        for(q = 0;q < 1000 / 2;q++){
          mspec[k][(1000 / 2) * i + q][j] = sqrt(re2[q] * re2[q] + im2[q] * im2[q]);
        }

      }
    }

  }



  
  STRING ts = "2017-03-28 00:00:00";
  STRING te = "2017-03-28 00:00:08";

  for(i = 0;i < num;i++){
    epoch[i]  = ts;
    epoch[i] += t[i] * TIME_TT2000__SEC;
  }
  //cerr << epoch << endl;
  
  for(j = 0;j < FFT_PTSH;j++){
    freq[j] = j / (REAL)FFT_PTS * samp_freq;
  }
  freq = ~freq;
  
  //plot p;

  //p.contour(spec[0],t,f);

  STRING  filename = "spectrogram.svg";
  SVGPlot plt(filename);

  INT plot_num = 2;
  
  plt.set_plot_region(0,plot_num);
  plt.timespan(ts,te);
  plt.set_yrange(0.0,125.0);
  plt.set_zrange(0,100);
  plt.set_title("Spectrogram of EEG");

  //plt.set_scaletype("y","log");
  plt.add(epoch,freq,spec[0],0,0);
  //plt.set_scaletype("z","linear");
  plt.set_label("y","OFA");
  plt.set_label("z","Spectra");

  plt.newplot();

  //plt.newplot();

  plt.draw_time();
  plt.set_label("x","Time");

  FILE *fp;
  fp = fopen("test.dat","w");
  /*for(i = 0;i < num;i++){
    for(j = 0;j < FFT_PTSH;j++){
      fprintf(fp,"%d %d %e\n",i,j,spec[0][i][j]);
    }
    fprintf(fp,"\n");
    }*/
  for(i = 0;i < 50;i++){
    for(q = 2;q < 500;q++){
      l = 500 * i + q;
      for(k = 0;k < 1;k++){
        for(j = 1;j < FFT_PTSH;j++){
          fprintf(fp,"%d %d %e\n",l,k * FFT_PTSH + j,mspec[k][l][j]);
        }
      }
      fprintf(fp,"\n");
    }
  }

  fclose(fp);

  // ===============================================
  // 多変量データの作成
  // ===============================================
  RMatrix D(135,CH_NUM * (FFT_PTSH - 1) * (500 - 1));//100,000次元
  INT4    id,s;
  
  for(id = 0;id < 135;id++){
    for(s = 1;s < 500;s++){         //変調周波数成分の内(非変動0を除去する)
      l = 500 * id + s;
      for(k = 0;k < CH_NUM;k++){
        for(j = 1;j < FFT_PTSH;j++){//周波数成分の内(非変動成分を除去する)
          D[id][(k * (FFT_PTSH - 1) + (j - 1)) * (500 - 1) + (s - 1)] = mspec[k][l][j];
        }
      }
    }
  }
    
  return 0;
}
