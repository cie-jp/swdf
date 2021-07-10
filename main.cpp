#include<iostream>
#include<complex>
#include<cfloat>
#include"Eigen/Dense"
#include"./include/cplasma.h"
#include"./include/wdf.h"
#include"./include/wdf_mcmc.h"

using namespace std;
using namespace Eigen;

#define ION_NUM (4)

int main(void){
  double fpe =  65e3;
  double fce = -30e3;
  double ve  =  0.0; 
  double ne;         
  double mi[ION_NUM];
  double qi[ION_NUM];
  double ri[ION_NUM];
  double vi[ION_NUM];
  double B0;         
  double f;          

  complex<double> R,L,P,dR,dL,dP;
  double          s,p;
  MatrixXcd       S(6,6),St(4,4);
  wdf             w;

  B0 = calc_magnetic_field_intensity(fce);
  ne = calc_number_density_of_electron(fpe);

  mi[0] = m_hydrogen;
  qi[0] = q_hydrogen;
  ri[0] = 0.70;
  vi[0] = 0.0;

  mi[1] = m_helium;
  qi[1] = q_helium1;
  ri[1] = 0.20;
  vi[1] = 0.0;

  mi[2] = m_oxygen;
  qi[2] = q_oxygen1;
  ri[2] = 0.05;
  vi[2] = 0.0;

  mi[3] = m_hydrogen * 2.0;
  qi[3] = q_hydrogen;
  ri[3] = 0.05;
  vi[3] = 0.0;

  f     = 20.0e3;

  calc_RLP_dRLP( R, L, P,
                dR,dL,dP,
                ne,ve,mi,qi,ri,vi,ION_NUM,
                B0,f);

  w.add_source(2.0,DEG_TO_RAD(15.0),DEG_TO_RAD( 30.0), 40.0);
  w.write_csv("wdf.csv",900);
  MatrixXcd  W_train;
  double    *data_train[6];
  int        snapshot   = 125;
  int        dnum_train = 32 * snapshot;
  int        ave_num_train;
  double     SNR = 30.0;
  
  for(int ch = 0;ch < 6;ch++){
    data_train[ch] = new double[dnum_train];
  }

  w.generate_waveform_R(data_train,dnum_train,65.0e3,1000,ne,ve,mi,qi,ri,vi,ION_NUM,B0,19.9e3,20.1e3);
  get_from_waveform(W_train,ave_num_train,
                    data_train,dnum_train,65.0e3,0.0,20.0e3,1.0,0.0,32);
  for(int ch = 0;ch < 6;ch++){
    delete [] data_train[ch];
  }
  W_train = make_spectral_matrix(W_train);
  cerr << "W_train" << endl;
  cerr <<  W_train / W_train.trace() << endl;
  WDF::WDF_MCMC wdf(R,L,P,
                    0.1,
                    100);
  fprintf(stderr,"ave_num_train = %d\n",ave_num_train);
  wdf.estimation(W_train,ave_num_train,
                 100);
  return 0;
  
}
