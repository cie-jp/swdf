#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#include"SVGPlot.h"
#include"ERG_mgf.h"
#include"ERG_ofa.h"

void ofa_l1_prime_download(const STRING &datatype = "spec"){
  INT2   YYYY = 2017;
  INT1   MM   =   04;
  INT1   DD   =   04;
  //CHAR   comptype = 'e';
  CHAR   comptype = '*';
  STRING level    = "l1_prime";
  STRING level_u  = "L1_prime";
  //STRING sfreq    = "65khz";
  STRING sfreq    = "*";
  //STRING pts      = "132pts";
  STRING pts      = "*";  
  //STRING version  = "10";
  STRING version  = "*";
  STRING filename;
  STRING remotedir;
  STRING remotepath;
  STRING localdir;
  STRING localpath;
  STRING command;

  filename   = STRING("erg_pwe_ofa_%s_%c_%s_%s_%s_%04d%02d%02d_v%s.cdf",&level[0],comptype,&datatype[0],&sfreq[0],&pts[0],YYYY,MM,DD,&version[0]);
  remotedir  = "cie.is.t.kanazawa-u.ac.jp:/remote/raid6/Arase/pwe/cdf/OFA/" + level_u + "/" + datatype + "/" + STRING("%04d",YYYY) + "/";          
  remotepath = remotedir + filename;
  localdir   = "./";
  localpath  =  localdir + filename;
  cerr << remotepath << endl;
  cerr << localpath  << endl;
  command = STRING("scp -P 22 -i %s %s@%s ./",
                   "/Users/schwarz/.ssh/id_rsa",
                   "ota",
                   &remotepath[0]);
  cerr << command    << endl;
  system(&command[0]);
}

void wfc_l1_prime_download(const STRING &datatype = "data"){
  INT2   YYYY = 2017;
  INT1   MM   =   04;
  INT1   DD   =   04;
  INT1   hh   =   03;
  //CHAR   comptype = 'e';
  CHAR   comptype = '*';
  STRING level    = "l1_prime";
  STRING level_u  = "L1_prime";
  //STRING sfreq    = "65khz";
  STRING sfreq    = "*";
  //STRING version  = "10";
  STRING version  = "*";
  STRING filename;
  STRING remotedir;
  STRING remotepath;
  STRING localdir;
  STRING localpath;
  STRING command;

  filename   = STRING("erg_pwe_wfc_%c_%s_%s_%04d%02d%02d%02d_v%s.cdf",comptype,&level[0],&sfreq[0],YYYY,MM,DD,hh,&version[0]);
  remotedir  = "cie.is.t.kanazawa-u.ac.jp:/remote/raid6/Arase/pwe/cdf/WFC/" + level_u + "/" + datatype + "/" + STRING("%04d",YYYY) + "/";          
  remotepath = remotedir + filename;
  localdir   = "./";
  localpath  =  localdir + filename;
  cerr << remotepath << endl;
  cerr << localpath  << endl;
  command = STRING("scp -P 22 -i %s %s@%s ./",
                   "/Users/schwarz/.ssh/id_rsa",
                   "ota",
                   &remotepath[0]);
  cerr << command    << endl;
  system(&command[0]);
}

void PLOT_ERG_PWE_OFA_L1_prime(SVGPlot &plt){
  CDFData   cdf("E_spectra_132","~/Desktop/erg_pwe_ofa_l1_prime_e_spec_65khz_132pts_20180323_v06.cdf");

  plt.set_scaletype("y","log");
  plt.set_scaletype("z","log");
  plt.cdfplot(cdf,1);
  plt.output2();
  //plt.aux(cdf.depend_0_label,cdf.depend_1_label,"CDFPLOT");
}

void multiplot(){
  STRING  filename = "output.svg";
  SVGPlot plt(filename);
  INT plot_num = 3;
  STRING ts = "2017-03-28";
  STRING te = "2017-03-30";

  plt.timespan(ts,te);

  plt.set_title("ERG衛星データ");
  
  // =================================================
  // OFA
  // =================================================
  ERG_ofa erg_ofa(ts,te,"l2","01");

  plt.set_scaletype("y","log");
  plt.set_scaletype("z","log");
  plt.set_yrange(0.032,20.0);
  plt.set_zrange(1.0e-6,1.0e-2);
  plt.set_plot_region(0,3);
  plt.tplot(erg_ofa.E_spectra,
            erg_ofa.epoch,
            erg_ofa.freq,
            1);
  plt.set_label("y","OFA");
  plt.set_label("z","Spectra");

  // =================================================
  // MGF
  // =================================================
  ERG_mgf erg_mgf(ts,te,"l2","01");
  RMatrix gse0,gse1,gse2,mag,fce,fce_half;

  gse0 = erg_mgf.mag_gse | 0;
  gse1 = erg_mgf.mag_gse | 1;
  gse2 = erg_mgf.mag_gse | 2;
  mag  = sqrt(gse0 % gse0 + gse1 % gse1 + gse2 % gse2);
  fce  = get_fce(mag);
  fce_half = get_fce_half(mag);
  //fce /= 1000.0;
  //fce_half /= 1000.0;
  plt.add(erg_mgf.epoch,fce     ,"fce");
  plt.add(erg_mgf.epoch,fce_half,"fce_{half}");
  //plt.set_scaletype("y","linear");
  plt.set_plot_region(0,3);
  plt.plot();
  plt.set_label("y","MGF");

  // =================================================
  // ORBIT
  // =================================================
  ERG_orbit erg_orbit(ts,te,"l2","01");
  RVector   gsm0,gsm1,gsm2;

  gsm0 = erg_orbit.pos_gsm | 0;
  gsm1 = erg_orbit.pos_gsm | 1;
  gsm2 = erg_orbit.pos_gsm | 2;

  plt.set_autorange();
  plt.set_scaletype("y","linear");
  
  plt.add(erg_orbit.epoch,gsm0,"GSM0");
  plt.add(erg_orbit.epoch,gsm1,"GSM1");
  plt.add(erg_orbit.epoch,gsm2,"GSM2");
  plt.set_plot_region(2,3);
  plt.plot();
  plt.set_label("y","Orbit");

  // =================================================
  // 時間軸ラベルの表示
  // =================================================
  plt.draw_time();
  plt.set_label("x","Time");
}

void DTensor__fetch(TTensor<DATA> &A,
                    const char    *varName,  //z変数名
                    const char    *filename){//CDFファイル名  
  CDFid     id;
  CDFstatus status;
  long      varNum;
  long      numRecs;
  long      numDims;
  long      dimSizes[CDF_MAX_DIMS];
  long      numValues;
  long      dataType;
  long      dataSize;
  BYTE     *buffer;
  int       i,j,k;

  //CDFファイルを開く
  status    = CDFopenCDF(filename,&id);
  //CDFのz変数名からz変数のIDを取得
  varNum    = CDFgetVarNum(id,(char*)varName);
  //CDFファイルに書かれたレコードの最大番号を取得
  status    = CDFgetzVarMaxWrittenRecNum(id,varNum,&numRecs);
  //z変数の次元を取得
  status    = CDFgetzVarNumDims(id,varNum,&numDims);
  //z変数の各次元の要素数を取得
  status    = CDFgetzVarDimSizes(id,varNum,dimSizes);
  //z変数の1レコード文の要素数を計算
  numValues = 1;
  for(i = 0;i < numDims;i++){
    numValues *= dimSizes[i];
  }
  INT4 depend_0_num =  numRecs + 1;
  INT4 depend_1_num = (0 <= numDims) ? dimSizes[0] : 1;  
  INT4 depend_2_num = (1 <= numDims) ? dimSizes[1] : 1;
  status = CDFgetzVarDataType(id,varNum,&dataType);
  CDFgetDataTypeSize(dataType,&dataSize);
  //情報の表示
  printf("numDims = %ld | numRecs = %ld\n",numDims,numRecs);
  printf("numValues = %d, numRecs = %d\n",(int)numValues,(int)numRecs);
  for(i = 0;i < numDims;i++){
    printf("%d %ld\n",i,dimSizes[i]);
  }

  if((buffer = (BYTE*)malloc(dataSize * (numRecs + 1) * numValues)) == NULL){
    exit(EXIT_FAILURE);
  }
  A = TTensor<DATA>(depend_2_num,depend_0_num,depend_1_num);
  status = CDFgetzVarAllRecordsByVarID(id,varNum,buffer);
  for(i = 0;i <= numRecs;i++){
    for(j = 0;j < depend_1_num;j++){
      for(k = 0;k < depend_2_num;k++){
        DATA__COPY(&A[k][i][j],DATA__GET_DATATYPE(dataType),buffer + (i * numValues + j * depend_2_num + k) * dataSize);
      }
    }
  }
  free(buffer);
  
  CDFcloseCDF(id);
}

void multiplot2(){
  STRING  filename = "output2.svg";
  SVGPlot plt(filename);
  INT plot_num = 3;
  STRING ts = "2017-03-28";
  STRING te = "2017-03-29";

  plt.set_plot_region(0,3);
  plt.timespan(ts,te);
  //plt.set_yrange(0.032,20.0);
  plt.set_yrange(0.032,20.0);
  plt.set_zrange(1.0e-6,1.0e-2);

  plt.set_title("ERG衛星データ");
  
  // =================================================
  // OFA
  // =================================================
  ERG_ofa erg_ofa(ts,te,"l2","01");

  //plt.set_scaletype("y","log");
  //plt.set_scaletype("z","log");
  plt.add(erg_ofa.epoch,
          erg_ofa.freq,
          erg_ofa.E_spectra);
  plt.set_label("y","OFA");
  plt.set_label("z","Spectra");

  // =================================================
  // MGF
  // =================================================
  ERG_mgf erg_mgf(ts,te,"l2","01");
  RMatrix gse0,gse1,gse2,mag,fce,fce_half;

  gse0 = erg_mgf.mag_gse | 0;
  gse1 = erg_mgf.mag_gse | 1;
  gse2 = erg_mgf.mag_gse | 2;
  mag  = sqrt(gse0 % gse0 + gse1 % gse1 + gse2 % gse2);
  fce  = get_fce(mag);
  fce_half = get_fce_half(mag);
  //fce /= 1000.0;
  //fce_half /= 1000.0;
  plt.add(erg_mgf.epoch,fce     );
  plt.add(erg_mgf.epoch,fce_half);
  //plt.set_scaletype("y","linear");
  plt.set_plot_region(0,3);
  //plt.set_label("y","MGF");
  plt.newplot();

  // =================================================
  // ORBIT
  // =================================================
  plt.set_plot_region(2,3);

  ERG_orbit erg_orbit(ts,te,"l2","01");
  RVector   gsm0,gsm1,gsm2;

  gsm0 = erg_orbit.pos_gsm | 0;
  gsm1 = erg_orbit.pos_gsm | 1;
  gsm2 = erg_orbit.pos_gsm | 2;
  
  plt.add(erg_orbit.epoch,gsm0);
  plt.add(erg_orbit.epoch,gsm1);
  plt.add(erg_orbit.epoch,gsm2);
  plt.set_label("y","Orbit");

  // =================================================
  // 時間軸ラベルの表示
  // =================================================
  plt.newplot();
  plt.draw_time();
  plt.set_label("x","Time");
}

int main(int argc,char *argv[]){
  //multiplot();
  //ofa_l1_prime_download("complex");
  //wfc_l1_prime_download();
  /*CTensor T = CTensor::random(4,3,7);
  CTensor A = T;
  cerr << T << endl;
  cerr << T[1] << endl;
  cerr << (T[1] | 0) << endl;
  cerr << A << endl;
  cerr << ~A[0] << endl;*/
  /*
  TTensor<DATA> F;
  TMatrix<DATA> dat_epoch;
  TMatrix<DATA> dat_H;
  TMatrix<DATA> dat_V;
  EVector       epoch;
  RVector       H;
  RVector       V;
  RMatrix       F0,F1;
  SVGPlot       plt("test.svg");

  Matrix__fetch(dat_epoch,"epoch","/Users/schwarz/Desktop/mrr2_l1_050_20170825_v02.cdf");
  epoch = dat_epoch;
  Matrix__fetch(dat_H,"H","/Users/schwarz/Desktop/mrr2_l1_050_20170825_v02.cdf");
  H = dat_H;
  Matrix__fetch(dat_V,"V","/Users/schwarz/Desktop/mrr2_l1_050_20170825_v02.cdf");
  V = dat_V;  
  DTensor__fetch(F,"F","/Users/schwarz/Desktop/mrr2_l1_050_20170825_v02.cdf");
  //F[depend_2_id(V)][depend_0_id(epoch)][depend_1_id(H)]
  INT V_idx = 27;
  F0 = F[V_idx];//F(epoch,H)
  INT H_idx =  4;
  F1 = F[0] | H_idx;
  for(INT i = 1;i < dat_V.get_col();i++){
    F1 |= F[i] | H_idx;
  }

  plt.timespan("2017-08-25","2017-08-26");
  plt.set_scaletype("z","log");
  plt.tplot(F0,epoch,H,1);
  plt.draw_time();
  cerr << (epoch) << endl;

  SVGPlot plt2("test2.svg");
  plt2.timespan("2017-08-25 09","2017-08-25 12");
  plt2.set_scaletype("z","log");
  plt2.tplot(F1,epoch,V,1);
  plt2.draw_time();
  */
  multiplot2();
  return 0;
}
