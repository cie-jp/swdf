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

#define div (5) //FFTのオーバーラップ率に関係する(オーバラップ率 = 100 / div [%])

int main(int argc,char *argv[]){
  // ======================================
  // EEGデータを格納する.
  // 3 (1秒) => 2 (1秒) => 1 (1秒) => 無 (1秒) を繰り返す.
  // ======================================
  REAL    samp_freq = 250.0;          //[Hz]
  REAL    dT        = 1.0 / samp_freq;//[sec]
  RMatrix data;
  INT4    frame,i,j,k,l;
  REAL    t;
  INT4    idx,idx0;
  REAL    re[250];
  REAL    im[250];
  REAL    window;
  REAL    p[8][250];
  RMatrix power(48 * 8,4 * div);//1サンプル(スペクトログラム) (48個の周波数成分(3Hz~51Hz), 8ch), (4 * div) スペクトログラムの時間サンプル
  FILE   *fp;
  CHAR    filename[2048];
  INT4 ans[45 * 3] = {//0: グー, 1: チョキ, 2: パー
    1,2,0,1,1,0,2,1,2,1,2,0,2,1,0,1,2,0,1,2,1,0,1,0,2,1,0,1,2,1,0,0,1,2,1,0,2,1,0,2,1,2,0,2,1,
    1,2,0,0,2,1,2,1,2,1,0,0,2,1,2,1,2,0,2,1,0,2,1,0,1,2,0,1,0,1,2,1,0,1,0,1,2,1,2,0,0,2,0,1,0,
    1,0,2,1,0,2,2,1,2,0,1,2,0,1,2,1,0,1,0,2,1,0,2,2,1,1,0,0,1,0,2,2,0,1,2,1,2,0,1,2,0,1,2,0,1
  };
  INT4 answer_label;

  data = RMatrix__fetch_csv("./EEG_DATA.txt"," ","");


  if((fp = fopen("inputdata.txt","w")) == NULL){
    exit(EXIT_FAILURE);
  }

  // ======================================
  // EEGデータの内, 解析に用いるデータを出力する. 
  // ======================================
  
  // ======================================
  // 4秒インターバル(4秒データのスペクトログラムを作成する. 
  // 250点ごとにFFT(周波数分解能は1Hz)を行う. 
  // 3,2,1,無が見えているときのスペクトログラムを作成する. 
  // ======================================
  for(frame = 0;frame < 135;frame++){
    // ====================================
    // 1. スペクトログラムの計算処理
    // ====================================
    for(l = 0;l < div;l++){
      for(j = 0;j < 4;j++){
	//信号の開始位置の算出
	idx0 = (frame * 4 + j) * 250 + l * (250 / div);
	for(k = 0;k < 8;k++){
	  //信号を0に
	  for(i = 0;i < 250;i++){
	    re[i]  = 0.0;
	    im[i]  = 0.0;
	  }
	  //信号を入力し, 窓関数を乗算
	  for(i = 0;i < 250;i++){
	    idx    = idx0 + i;
	    if((idx < 0) || (data.get_row() <= idx)){
	      continue;
	    }
	    window = 0.54 - 0.46 * cos(2.0 * M_PI * i / (250.0 - 1.0));//Hamming窓
	    re[i]  = data[idx][4 + k] * window;//data[idx][4] : ch1, data[idx][5] : ch2,...
	    im[i]  = 0.0;      
	  }
	  //FFTする. 
	  FFT(re,im,250);
	  //パワーを出力する. 
	  for(i = 0;i < 250 / 2;i++){
	    p[k][i] = 10.0 * log10(re[i] * re[i] + im[i] * im[i]);
	  }
	}
	//P[0][0]   : 時刻0で, 3Hzのch1,パワー
	//P[1][0]   : 時刻0で, 4Hzのch1,パワー
	//P[0][1]   : 時刻1で, 3Hzのch1,パワー
	//P[1][1]   : 時刻1で, 4Hzのch1,パワー
	//P[48][1]  : 時刻1で, 3Hzのch2,パワー
	//P[49][1]  : 時刻1で, 4Hzのch2,パワー
	
	for(k = 0;k < 8;k++){      
	  for(i = 0;i < 48;i++){
	    power[48 * k + i][j * div + l] = p[k][i + 3];//3Hz ~ 51 Hz
	  }
	}	

      }
    }

    // 開始・終了フレームはスペクトログラムを作成する際にデータが不足する場合があるので, 学習・判別に適さないと考える. 
    // そのために, 該当部のデータに対して処理は省くことにする. 
    if((frame ==   0) || 
       (frame ==  44) || 
       (frame ==  45) || 
       (frame ==  89) || 
       (frame ==  90) || 
       (frame == 134) ){
      continue;
    }

    // ====================================
    // 2. 教師ラベルの算出
    // ====================================
    answer_label = ans[frame];

    // ===================================================================
    // 3. サンプルデータの解析
    // ===================================================================
    // (内訳)
    // frame                            : サンプルID
    // power[48 * 8][4 * div(規定値:5)] : スペクトログラム
    // answer_label                     : 教師ラベル(0,1,2)
    // ===================================================================
    /*
      sprintf(filename,"power%d.txt",frame);
      if((fp = fopen(filename,"w")) == NULL){
      exit(EXIT_FAILURE);
      }
      fprintf(fp,"#frame        = %d\n",frame);
      fprintf(fp,"#answer_label = %d\n",answer_label);
      fprintf(fp,"#power\n");
      for(j = 0;j < 4 * div;j++){
      for(i = 0;i < 48 * 8;i++){
      fprintf(fp,"%d %d %e\n",j,i,power[i][j]);
      }
      fprintf(fp,"\n");
      }
      fclose(fp);
    */
    for(j = 0;j < 48 * 8;j++){
      for(i = 0;i < 4 * div;i++){
	fprintf(fp,"%e ",power[j][i]);
      }
      fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    // ===================================================================

  }

  fclose(fp);


  return 0;
}
