#include"CLDIA.h"

using namespace std;
using namespace CLDIA;

#include"SVGPlot.h"
#include"ERG_mgf.h"
#include"ERG_ofa.h"

void PLOT_ERG_PWE_OFA_L1_prime(){
  SVGPlot   plt;
  CDFData   cdf("E_spectra_132","~/Desktop/erg_pwe_ofa_l1_prime_e_spec_65khz_132pts_20180323_v06.cdf");

  plt.set_scaletype("y","log");
  plt.set_scaletype("z","log");
  plt.cdfplot(cdf,1);
  plt.output(cdf);

  ERG_mgf   erg_mgf("2017-03-28","2017-03-29","l2","01");
  RMatrix   gse0,gse1,gse2,mag,fce,fce_half;

  gse0 = erg_mgf.mag_gse | 0;
  gse1 = erg_mgf.mag_gse | 1;
  gse2 = erg_mgf.mag_gse | 2;
  mag  = gse0 % gse0 + gse1 % gse1 + gse2 % gse2;
  fce  = get_fce(mag);
  fce_half = get_fce_half(mag);
  plt.add(erg_mgf.epoch,fce,"fce");
  plt.add(erg_mgf.epoch,fce_half,"fce_half");
  plt.plot("Time","MAG","MGF磁場");
}

void foo(){
  ERG_ofa   erg_ofa("2017-03-28","2017-03-29","l2","01");
  RMatrix   E_spectra;
  SVGPlot   plt;

  E_spectra = erg_ofa.E_spectra;
  
  plt.timespan("2017-03-28","2017-03-29");
  plt.set_scaletype("y","log");
  plt.set_scaletype("z","log");
  plt.tplot(E_spectra,erg_ofa.epoch,erg_ofa.freq,1);
  plt.output();
  plt.plot("Time","MAG","OFA");
}

int main(int argc,char *argv[]){
  /*
  ERG_orbit erg_orbit("2017-03-28","2017-04-03","l2","01");
  RMatrix   gsm0,gsm1,gsm2;
  SVGPlot   plt;
  
  gsm0 = erg_orbit.pos_gsm | 0;
  gsm1 = erg_orbit.pos_gsm | 1;
  gsm2 = erg_orbit.pos_gsm | 2;

  plt.add(erg_orbit.epoch,gsm0,"GSM0");
  plt.add(erg_orbit.epoch,gsm1,"GSM1");
  plt.add(erg_orbit.epoch,gsm2,"GSM2");
  plt.plot("Time","Orbit","ERG衛星確定軌道");
  */
  //PLOT_ERG_PWE_OFA_L1_prime();
  foo();
  return 0;
}
