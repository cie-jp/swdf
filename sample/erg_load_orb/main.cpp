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

int main(int argc,char *argv[]){
  //multiplot();
  //ofa_l1_prime_download("complex");
  //wfc_l1_prime_download();
  CTensor T = CTensor::random(4,3,7);
  CTensor A = T;
  cerr << T << endl;
  cerr << T[1] << endl;
  cerr << (T[1] | 0) << endl;
  cerr << A << endl;
  cerr << ~A[0] << endl;
  return 0;
}
