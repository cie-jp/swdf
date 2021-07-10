#ifndef _WDF_H_INCLUDE_
#define _WDF_H_INCLUDE_

#include<iostream>
#include"./include/cplasma.h"
#include"./include/crandom.h"
#include"Eigen/Dense"

using namespace std;
using namespace Eigen;

#define RAD_TO_DEG(rad) ((rad) * 180.0 / M_PI) 
#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0) 

#define WDF_LIST_MAX_NUM (100) 

class wdf{
private:
  double *_energy;
  double *_theta0;
  double *_phi0;  
  double *_kappa; 
  int     _num;   
public:
  wdf();
 ~wdf();
  
 void add_source(double energy,
		 double theta0,
		 double phi0,  
		 double kappa);

 void calc_spectral_matrix_R(MatrixXcd      &S,              
			     complex<double> R,
			     complex<double> L,
			     complex<double> P,
			     int             partition_number);

 void calc_spectral_matrix_L(MatrixXcd      &S,                
			     complex<double> R,
			     complex<double> L,
			     complex<double> P,
			     int             partition_number);

 void generate_waveform_R(double          *data[6], 
			  int              data_num,
			  double           freq_sam,
			  int              wave_num,
			  double           ne,       
			  double           ve,
			  double           mi[],
			  double           qi[],
			  double           ri[],
			  double           vi[],
			  int              Ni,
			  double           B0,
			  double           freq_min, 
			  double           freq_max);

 void contaminate_whitenoise(double  *data[6],
			     int      data_num,
			     double   freq_sam,
			     int      wave_num,
			     double   freq_min,
			     double   freq_max,
			     double   SNR);
 void write_csv(const char *filename,         
		int         partition_number);
};

wdf::wdf(){
  _energy  = new double[WDF_LIST_MAX_NUM];
  _theta0  = new double[WDF_LIST_MAX_NUM];
  _phi0    = new double[WDF_LIST_MAX_NUM];
  _kappa   = new double[WDF_LIST_MAX_NUM];
  _num     = 0;
}

wdf::~wdf(){
  delete[] _energy;
  delete[] _theta0;
  delete[] _phi0;
  delete[] _kappa;
}

void wdf::add_source(double energy,double theta0,double phi0,double kappa){
  _energy[_num] = energy;
  _theta0[_num] = theta0;
  _phi0[_num]   = phi0;
  _kappa[_num]  = kappa;
  _num++;
}

void wdf::calc_spectral_matrix_R(MatrixXcd       &S,
				 complex<double> _R,
				 complex<double> _L,
				 complex<double> _P,
				 int             partition_number){
  double    u,v,dl,ud,vd;
  double    r2;
  double   *f;
  double   *g;
  double    Z,Zf,Zg;
  double    theta;
  double    phi;
  int       L;
  int       count;
  int       u_idx,v_idx;
  MatrixXcd a;

  dl    = sqrt((4.0 * M_PI) / (double)partition_number);
  L     = ceil(sqrt(2.0) / dl);
  f     = new double[(2 * L + 1) * (2 * L + 1)];
  g     = new double[(2 * L + 1) * (2 * L + 1)];
  for(v_idx = -L;v_idx <= +L;v_idx++){
    for(u_idx = -L;u_idx <= +L;u_idx++){
      f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] = 0.0;
      g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] = 0.0;
    }
  }
  for(int wave_idx = 0;wave_idx < _num;wave_idx++){
    if(_kappa[wave_idx] < 0.0){
      if(_theta0[wave_idx] <= M_PI / 2.0){
	u = 2.0 * sin(_theta0[wave_idx] / 2.0) * cos(_phi0[wave_idx]);
	v = 2.0 * sin(_theta0[wave_idx] / 2.0) * sin(_phi0[wave_idx]);	
	u_idx = (int)(u / dl + 0.5);
	v_idx = (int)(v / dl + 0.5);
	f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx];
      }else{
	u = 2.0 * sin((M_PI - _theta0[wave_idx]) / 2.0) * cos(_phi0[wave_idx]);
	v = 2.0 * sin((M_PI - _theta0[wave_idx]) / 2.0) * sin(_phi0[wave_idx]);	
	u_idx = (int)(u / dl + 0.5);
	v_idx = (int)(v / dl + 0.5);
	g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx];
      }
    }else if(_kappa[wave_idx] == 0.0){
      count = 0;
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    count += 2;
	  }
	}
      }
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] / (double)count;
	    g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] / (double)count;    
	  }
	}
      }
    }else{
      Z = 0.0;
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    Zf    = 0.0;
	    Zg    = 0.0;
	    count = 0;
	    for(int j = -1;j <= +1;j++){
	      for(int i = -1;i <= +1;i++){
		ud = u + 0.5 * i * dl;
		vd = v + 0.5 * j * dl;
		r2 = ud * ud + vd * vd;
		if(r2 < 2.0){
		  theta = 2.0 * asin(sqrt(r2) / 2.0);
		  phi   = atan2(vd,ud);
		  Zf   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  theta = M_PI - theta;
		  Zg   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  count++;
		}
	      }
	    }
	    Zf /= (double)count;
	    Zg /= (double)count;
	    Z  += Zf + Zg;
	  }
	}
      }
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    Zf    = 0.0;
	    Zg    = 0.0;
	    count = 0;
	    for(int j = -1;j <= +1;j++){
	      for(int i = -1;i <= +1;i++){
		ud = u + 0.5 * i * dl;
		vd = v + 0.5 * j * dl;
		r2 = ud * ud + vd * vd;
		if(r2 < 2.0){
		  theta = 2.0 * asin(sqrt(r2) / 2.0);
		  phi   = atan2(vd,ud);
		  Zf   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  theta = M_PI - theta;
		  Zg   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  count++;
		}
	      }
	    }
	    Zf /= (double)count;
	    Zg /= (double)count;
	    f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] * Zf / Z;
	    g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] * Zg / Z;
	  }
	}
      }      
    }
  }
  S = MatrixXcd::Zero(6,6);  
  for(v_idx = -L;v_idx <= +L;v_idx++){
    for(u_idx = -L;u_idx <= +L;u_idx++){
      if((u_idx == 0) && (v_idx == 0)){
	continue;
      }
      u  = u_idx * dl;
      v  = v_idx * dl;
      r2 = u * u + v * v;
      if(r2 < 2.0){
	theta = 2.0 * asin(sqrt(r2) / 2.0);
	phi   = atan2(v,u);
	if(::calc_spectral_matrix_R(a,_R,_L,_P,theta,phi) == 1){
	  S += f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] * a;
	}
	theta = M_PI - theta;
	if(::calc_spectral_matrix_R(a,_R,_L,_P,theta,phi) == 1){
	  S += g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] * a;
	}
      }
    }
  }

  delete[] f;
  delete[] g;
}

void wdf::calc_spectral_matrix_L(MatrixXcd       &S,
				 complex<double> _R,
				 complex<double> _L,
				 complex<double> _P,
				 int             partition_number){
  double    u,v,dl,ud,vd;
  double    r2;
  double   *f;
  double   *g;
  double    Z,Zf,Zg;
  double    theta;
  double    phi;
  int       L;
  int       count;
  int       u_idx,v_idx;
  MatrixXcd a;

  dl    = sqrt((4.0 * M_PI) / (double)partition_number);
  L     = ceil(sqrt(2.0) / dl);
  f     = new double[(2 * L + 1) * (2 * L + 1)];
  g     = new double[(2 * L + 1) * (2 * L + 1)];
  for(v_idx = -L;v_idx <= +L;v_idx++){
    for(u_idx = -L;u_idx <= +L;u_idx++){
      f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] = 0.0;
      g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] = 0.0;
    }
  }
  for(int wave_idx = 0;wave_idx < _num;wave_idx++){
    if(_kappa[wave_idx] < 0.0){
      if(_theta0[wave_idx] <= M_PI / 2.0){
	u = 2.0 * sin(_theta0[wave_idx] / 2.0) * cos(_phi0[wave_idx]);
	v = 2.0 * sin(_theta0[wave_idx] / 2.0) * sin(_phi0[wave_idx]);	
	u_idx = (int)(u / dl + 0.5);
	v_idx = (int)(v / dl + 0.5);
	f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx];
      }else{
	u = 2.0 * sin((M_PI - _theta0[wave_idx]) / 2.0) * cos(_phi0[wave_idx]);
	v = 2.0 * sin((M_PI - _theta0[wave_idx]) / 2.0) * sin(_phi0[wave_idx]);	
	u_idx = (int)(u / dl + 0.5);
	v_idx = (int)(v / dl + 0.5);
	g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx];
      }
    }else if(_kappa[wave_idx] == 0.0){
      count = 0;
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    count += 2;
	  }
	}
      }
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] / (double)count;
	    g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] / (double)count;    
	  }
	}
      }
    }else{
      Z = 0.0;
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    Zf    = 0.0;
	    Zg    = 0.0;
	    count = 0;
	    for(int j = -1;j <= +1;j++){
	      for(int i = -1;i <= +1;i++){
		ud = u + 0.5 * i * dl;
		vd = v + 0.5 * j * dl;
		r2 = ud * ud + vd * vd;
		if(r2 < 2.0){
		  theta = 2.0 * asin(sqrt(r2) / 2.0);
		  phi   = atan2(vd,ud);
		  Zf   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  theta = M_PI - theta;
		  Zg   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  count++;
		}
	      }
	    }
	    Zf /= (double)count;
	    Zg /= (double)count;
	    Z  += Zf + Zg;
	  }
	}
      }
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    Zf    = 0.0;
	    Zg    = 0.0;
	    count = 0;
	    for(int j = -1;j <= +1;j++){
	      for(int i = -1;i <= +1;i++){
		ud = u + 0.5 * i * dl;
		vd = v + 0.5 * j * dl;
		r2 = ud * ud + vd * vd;
		if(r2 < 2.0){
		  theta = 2.0 * asin(sqrt(r2) / 2.0);
		  phi   = atan2(vd,ud);
		  Zf   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  theta = M_PI - theta;
		  Zg   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  count++;
		}
	      }
	    }
	    Zf /= (double)count;
	    Zg /= (double)count;
	    f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] * Zf / Z;
	    g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] * Zg / Z;
	  }
	}
      }      
    }
  }
  S = MatrixXcd::Zero(6,6);  
  for(v_idx = -L;v_idx <= +L;v_idx++){
    for(u_idx = -L;u_idx <= +L;u_idx++){
      if((u_idx == 0) && (v_idx == 0)){
	continue;
      }
      u  = u_idx * dl;
      v  = v_idx * dl;
      r2 = u * u + v * v;
      if(r2 < 2.0){
	theta = 2.0 * asin(sqrt(r2) / 2.0);
	phi   = atan2(v,u);
	if(::calc_spectral_matrix_L(a,_R,_L,_P,theta,phi) == 1){
	  S += f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] * a;
	}
	theta = M_PI - theta;
	if(::calc_spectral_matrix_L(a,_R,_L,_P,theta,phi) == 1){
	  S += g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] * a;
	}
      }
    }
  }

  delete[] f;
  delete[] g;
}

void wdf::generate_waveform_R(double          *data[6],
			      int              data_num,
			      double           freq_sam,
			      int              wave_num,
			      double           ne,
			      double           ve,
			      double           mi[],
			      double           qi[],
			      double           ri[],
			      double           vi[],
			      int              Ni,
			      double           B0,
			      double           freq_min,
			      double           freq_max){
  FILE           *fp;
  double          theta,phi;
  CRandom         cr(time(NULL));
  double          freq,phase;
  VectorXcd       eh;
  int             idx;
  complex<double> R,L,P,dR,dL,dP;

  if((fp = fopen("waveform_dir.dat","w")) == NULL){
    cerr << "Error : wdf::get_waveform()" << endl;
    exit(EXIT_FAILURE);
  }

  for(int n = 0;n < data_num;n++){
    for(int ch = 0;ch < 6;ch++){
      data[ch][n] = 0.0;
    }
  }

  for(int c = 0;c < wave_num;c++){
    freq  = cr.uniform(freq_min,freq_max);
    calc_RLP_dRLP(R,L,P,dR,dL,dP,ne,ve,mi,qi,ri,vi,Ni,B0,freq);
    phase = cr.uniform(0.0,2.0 * M_PI);
    idx = cr.multinomial(_energy,_num);
    if(_kappa[idx] < 0.0){
      theta = _theta0[idx];
      phi   = _phi0[idx];
    }else{
      cr.von_mises_fisher(theta,phi,_theta0[idx],_phi0[idx],_kappa[idx]);
    }

    if(calc_EH_vector_R(eh,R,L,P,theta,phi) == 0){
      continue;
    }

    fprintf(fp,"%e %e %e\n",sin(theta) * cos(phi),sin(theta) * sin(phi),cos(theta));

    for(int n = 0;n < data_num;n++){
      for(int ch = 0;ch < 6;ch++){
	data[ch][n] += real(eh(ch) * polar(1.0,2.0 * M_PI * freq * (n / freq_sam) + phase)) / sqrt((double)wave_num);
      }
    }
  }
  
  fclose(fp);
}

void wdf::contaminate_whitenoise(double          *data[6],
				 int              data_num,
				 double           freq_sam,
				 int              wave_num,
				 double           freq_min,
				 double           freq_max,
				 double           SNR){
  double  sigma_s;
  double  sigma_n;
  double  sfactor;
  CRandom cr;
  double  freq[6],phase[6];
  double *noise[6];
  double tmp;

  for(int ch = 0;ch < 6;ch++){
    noise[ch] = new double[data_num];
  }
  for(int ch = 0;ch < 6;ch++){
    for(int n = 0;n < data_num;n++){
      noise[ch][n] = 0.0;
    }
  }

  for(int c = 0;c < wave_num;c++){
    for(int ch = 0;ch < 6;ch++){
      freq[ch]  = cr.uniform(freq_min,freq_max);
      phase[ch] = cr.uniform(0.0,2.0 * M_PI);
    }
    for(int n = 0;n < data_num;n++){
      noise[0][n] += cos(2.0 * M_PI * freq[0] * (n / freq_sam) + phase[0]) / sqrt((double)wave_num) * Z0;
      noise[1][n] += cos(2.0 * M_PI * freq[1] * (n / freq_sam) + phase[1]) / sqrt((double)wave_num) * Z0;
      noise[2][n] += cos(2.0 * M_PI * freq[2] * (n / freq_sam) + phase[2]) / sqrt((double)wave_num) * Z0;
      noise[3][n] += cos(2.0 * M_PI * freq[3] * (n / freq_sam) + phase[3]) / sqrt((double)wave_num);
      noise[4][n] += cos(2.0 * M_PI * freq[4] * (n / freq_sam) + phase[4]) / sqrt((double)wave_num);
      noise[5][n] += cos(2.0 * M_PI * freq[5] * (n / freq_sam) + phase[5]) / sqrt((double)wave_num);
    }
  }

  sigma_n = 0.0;
  for(int n = 0;n < data_num;n++){
    sigma_n += noise[3][n] * noise[3][n] + noise[4][n] * noise[4][n] + noise[5][n] * noise[5][n];
  }
  sigma_n = sqrt(sigma_n / (3.0 * data_num));

  sigma_s = 0.0;
  for(int n = 0;n < data_num;n++){
    sigma_s += data[3][n] * data[3][n] + data[4][n] * data[4][n] + data[5][n] * data[5][n];
  }
  sigma_s = sqrt(sigma_s / (3.0 * data_num));
  sfactor = sigma_s * pow(10.0,-SNR / 20.0) / sigma_n;

  for(int n = 0;n < data_num;n++){
    for(int ch = 0;ch < 6;ch++){    
      data[ch][n] += sfactor * noise[ch][n];
    }
  }

  for(int ch = 0;ch < 6;ch++){
    delete[] noise[ch];
  }
}

void wdf::write_csv(const char *filename,int partition_number){
  FILE   *fp;
  double  u,v,dl,ud,vd;
  double  r2;
  double *f;
  double *g;
  double  Z,Zf,Zg;
  double  theta;
  double  phi;
  int     L;
  int     count;
  int     u_idx,v_idx;
  
  if(filename == NULL){
    fp = stdout;
  }else{
    fp = fopen(filename,"w");
  }
  dl    = sqrt((4.0 * M_PI) / (double)partition_number);
  L     = ceil(sqrt(2.0) / dl);
  f     = new double[(2 * L + 1) * (2 * L + 1)];
  g     = new double[(2 * L + 1) * (2 * L + 1)];
  for(v_idx = -L;v_idx <= +L;v_idx++){
    for(u_idx = -L;u_idx <= +L;u_idx++){
      f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] = 0.0;
      g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] = 0.0;
    }
  }
  for(int wave_idx = 0;wave_idx < _num;wave_idx++){
    if(_kappa[wave_idx] < 0.0){
      if(_theta0[wave_idx] <= M_PI / 2.0){
	u = 2.0 * sin(_theta0[wave_idx] / 2.0) * cos(_phi0[wave_idx]);
	v = 2.0 * sin(_theta0[wave_idx] / 2.0) * sin(_phi0[wave_idx]);	
	u_idx = (int)(u / dl + 0.5);
	v_idx = (int)(v / dl + 0.5);
	f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx];
      }else{
	u = 2.0 * sin((M_PI - _theta0[wave_idx]) / 2.0) * cos(_phi0[wave_idx]);
	v = 2.0 * sin((M_PI - _theta0[wave_idx]) / 2.0) * sin(_phi0[wave_idx]);	
	u_idx = (int)(u / dl + 0.5);
	v_idx = (int)(v / dl + 0.5);
	g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx];
      }
    }else if(_kappa[wave_idx] == 0.0){
      count = 0;
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    count += 2;
	  }
	}
      }
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] / (double)count;
	    g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] / (double)count;    
	  }
	}
      }
    }else{
      Z = 0.0;
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    Zf    = 0.0;
	    Zg    = 0.0;
	    count = 0;
	    for(int j = -1;j <= +1;j++){
	      for(int i = -1;i <= +1;i++){
		ud = u + 0.5 * i * dl;
		vd = v + 0.5 * j * dl;
		r2 = ud * ud + vd * vd;
		if(r2 < 2.0){
		  theta = 2.0 * asin(sqrt(r2) / 2.0);
		  phi   = atan2(vd,ud);
		  Zf   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  theta = M_PI - theta;
		  Zg   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  count++;
		}
	      }
	    }
	    Zf /= (double)count;
	    Zg /= (double)count;
	    Z  += Zf + Zg;
	  }
	}
      }
      for(v_idx = -L;v_idx <= +L;v_idx++){
	for(u_idx = -L;u_idx <= +L;u_idx++){
	  u  = u_idx * dl;
	  v  = v_idx * dl;
	  if((u * u + v * v) < 2.0){
	    Zf    = 0.0;
	    Zg    = 0.0;
	    count = 0;
	    for(int j = -1;j <= +1;j++){
	      for(int i = -1;i <= +1;i++){
		ud = u + 0.5 * i * dl;
		vd = v + 0.5 * j * dl;
		r2 = ud * ud + vd * vd;
		if(r2 < 2.0){
		  theta = 2.0 * asin(sqrt(r2) / 2.0);
		  phi   = atan2(vd,ud);
		  Zf   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  theta = M_PI - theta;
		  Zg   += exp(_kappa[wave_idx] * (cos(_theta0[wave_idx]) * cos(theta) + sin(_theta0[wave_idx]) * sin(theta) * cos(_phi0[wave_idx] - phi) - 1.0));
		  count++;
		}
	      }
	    }
	    Zf /= (double)count;
	    Zg /= (double)count;
	    f[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] * Zf / Z;
	    g[(v_idx + L) * (2 * L + 1) + (u_idx + L)] += _energy[wave_idx] * Zg / Z;
	  }
	}
      }      
    }
  }
  for(v_idx = -L;v_idx <= +L;v_idx++){
    for(u_idx = -L;u_idx <= +L;u_idx++){
      u  = u_idx * dl;
      v  = v_idx * dl;
      r2 = u * u + v * v;
      if(r2 < 2.0){
	theta = 2.0 * asin(sqrt(r2) / 2.0);
	phi   = atan2(v,u);
	fprintf(fp,"%e,%e,%e\n",RAD_TO_DEG(phi),90.0 - RAD_TO_DEG(theta),f[(v_idx + L) * (2 * L + 1) + (u_idx + L)]);
	theta = M_PI - theta;
	fprintf(fp,"%e,%e,%e\n",RAD_TO_DEG(phi),90.0 - RAD_TO_DEG(theta),g[(v_idx + L) * (2 * L + 1) + (u_idx + L)]);
      }
    }
  }

  delete[] f;
  delete[] g;

  if(filename != NULL){
    fclose(fp);
  }
}


void get_from_waveform(MatrixXcd &S,        
		       int       &ave_num,  
		       double    *wave[6],  
		       int        data_num, 
		       double     freq_sam, 
		       double     overlap,  
		       double     freq_c,   
		       double     Wa,       
		       double     Wb,       
		       int        filt_len);

void get_from_waveform(MatrixXcd &S,
		       int       &ave_num,
		       double    *data[6], 
		       int        data_num,
		       double     freq_sam,
		       double     overlap, 
		       double     freq_c,  
		       double     Wa,       
		       double     Wb,       
		       int        filt_len){
  VectorXcd eh(6);
  double    w;
  double    theta;
  
  S = MatrixXcd::Zero(6,6);  
  ave_num = 0;
  for(int idx = 0;(idx + filt_len) <= data_num;idx += filt_len * (1.0 - overlap)){
    for(int ch = 0;ch < 6;ch++){
      eh(ch) = 0.0;
      for(int n = 0;n < filt_len;n++){
	w       = (Wa - Wb * cos(2.0 * M_PI * n / (double)(filt_len - 1))) / (Wa * filt_len - Wb);
	theta   = -2.0 * M_PI * freq_c * n / freq_sam;
	eh(ch) +=  w * polar(1.0,theta) * data[ch][idx + n];
      }
    }
    S += eh * eh.adjoint();
    ave_num++;
  }
  S /= (double)ave_num;
}

#endif
