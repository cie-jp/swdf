#ifndef _CPLASMA_H_INCLUDE_
#define _CPLASMA_H_INCLUDE_

#include<iostream>
#include<complex>
#include<cfloat>
#include"Eigen/Dense"

using namespace std;
using namespace Eigen; 

const double light_velocity = 2.99792458e+08;
const double epsilon0       =  8.8541878e-12;
const double mu0            = 1.25663706e-06;
const double Z0             =   3.767303e+02;

const double m_electron =  9.1093897e-31;           
const double m_proton   =  1.6726231e-27;           
const double m_hydrogen =  1.00794e-3 / 6.022140857e23;
const double m_helium   =  4.00260e-3 / 6.022140857e23;
const double m_oxygen   =    16.00e-3 / 6.022140857e23;

const double q_electron = -1.6021773e-19;
const double q_proton   = +1.6021773e-19;
const double q_hydrogen =  q_proton * 1; 
const double q_helium1  =  q_proton * 1; 
const double q_oxygen1  =  q_proton * 1; 

const complex<double> CJ = complex<double>(0.0,1.0);

double calc_magnetic_field_intensity(double fce);

double calc_number_density_of_electron(double fpe);

void   calc_number_density_of_ions(double ni[],
				   double ne,  
				   double qi[],
				   double ri[],
				   int    Ni); 

void   calc_frequency(double  fp[],
		      double  fc[],
		      double  m[], 
		      double  q[], 
		      double  n[], 
		      int     N,   
		      double  B0); 

void   calc_XYZ(double  X[],
		double  Y[],
		double  Z[],
		double  fp[],
		double  fc[],
		double  fv[],
		int     N,   
		double  f);  


void   calc_RLP_dRLP(complex<double> &R,    
		     complex<double> &L,    
		     complex<double> &P,    
		     complex<double> &dR,   
		     complex<double> &dL,   
		     complex<double> &dP,   
		     double           ne,   
		     double           ve,   
		     double           mi[], 
		     double           qi[], 
		     double           ri[], 
		     double           vi[], 
		     int              Ni,   
		     double           B0,   
		     double           f);   


void   calc_ABC(complex<double> &A,         
		complex<double> &B,         
		complex<double> &C,         
		complex<double> &F,         
		complex<double>  R,         
		complex<double>  L,         
		complex<double>  P,         
		double           theta);    


void   calc_refractive_index(complex<double> refractive_index[2],
			     complex<double> R,                  
			     complex<double> L,                  
			     complex<double> P,                  
			     double          theta);             

void   calc_group_refractive_index(complex<double> group_refractive_index[2],
				   complex<double> R,
				   complex<double> L,
				   complex<double> P,
				   complex<double> dR,
				   complex<double> dL,
				   complex<double> dP,
				   double          theta);  

void   calc_phase_velocity(double          vp[2][3],
			   complex<double> R,
			   complex<double> L,
			   complex<double> P,
			   double          theta,
			   double          phi);

void   calc_group_velocity(double          vg[2][3],
			   complex<double> R,
			   complex<double> L,
			   complex<double> P,
			   complex<double> dR,
			   complex<double> dL,
			   complex<double> dP,
			   double          theta,
			   double          phi);

void   calc_poynting_vector(double          q[2][3],
			    complex<double> R,
			    complex<double> L,
			    complex<double> P,
			    double          theta,
			    double          phi);

void   calc_EH_vector(complex<double> eh[2][6],
		      complex<double> R,
		      complex<double> L,
		      complex<double> P,
		      double          theta,
		      double          phi);

double calc_H_rotation(complex<double> R,
		       complex<double> L,
		       complex<double> P,
		       double          theta);

int    refractive_index_R(complex<double> &nr_R,
			  complex<double>  R,
			  complex<double>  L,
			  complex<double>  P,
			  double           theta);

int    refractive_index_L(complex<double> &nr_L,
			  complex<double>  R,
			  complex<double>  L,
			  complex<double>  P,
			  double           theta);

int    calc_EH_vector_R(VectorXcd      &eh,
			complex<double> R,
			complex<double> L,
			complex<double> P,
			double          theta,
			double          phi);

int    calc_EH_vector_L(VectorXcd      &eh,
			complex<double> R,
			complex<double> L,
			complex<double> P,
			double          theta,
			double          phi);

int    calc_spectral_matrix_R(MatrixXcd      &S,
			      complex<double> R,
			      complex<double> L,
			      complex<double> P,
			      double          theta,
			      double          phi);

int    calc_spectral_matrix_L(MatrixXcd      &S,
			      complex<double> R,
			      complex<double> L,
			      complex<double> P,
			      double          theta,
			      double          phi);

void   means_method(double    &theta,
		    double    &phi,
		    MatrixXcd &S);

double calc_magnetic_field_intensity(double fce){
  double wce = 2.0 * M_PI * fce;
  return wce * m_electron / q_electron;  
}

double calc_number_density_of_electron(double fpe){
  double wpe = 2.0 * M_PI * fpe;
  return m_electron * epsilon0 * (wpe * wpe) / (q_electron * q_electron);
}

void calc_number_density_of_ions(double  ni[],
				 double  ne,
				 double  qi[],
				 double  ri[],
				 int     Ni){
  double ri_sum;
  double qi_ave;
  double ni_sum;

  ri_sum = 0.0;
  for(int l = 0;l < Ni;l++){
    ri_sum += ri[l];
  }

  qi_ave = 0.0;
  for(int l = 0;l < Ni;l++){
    qi_ave += qi[l] * (ri[l] / ri_sum);
  }

  ni_sum = (-q_electron / qi_ave) * ne;

  for(int l = 0;l < Ni;l++){
    ni[l] = ni_sum * (ri[l] / ri_sum);
  }
}

void calc_frequency(double  fp[], 
		    double  fc[], 
		    double  m[],  
		    double  q[],  
		    double  n[],  
		    int     N,  
		    double  B0){
  for(int l = 0;l < N;l++){
    fp[l] = sqrt(n[l] * q[l] * q[l] / (m[l] * epsilon0)) / (2.0 * M_PI);
    fc[l] = q[l] / m[l] * B0 / (2.0 * M_PI);
  }
}

void calc_XYZ(double  X[],
	      double  Y[],
	      double  Z[],
	      double  fp[],
	      double  fc[],
	      double  v[],
	      int     N,
	      double  f){
  for(int l = 0;l < N;l++){
    X[l] = (fp[l] / f) * (fp[l] / f);
    Y[l] =  fc[l] / f;
    Z[l] =   v[l] / f;
  }
}

void calc_RLP_dRLP(complex<double> &R,
		   complex<double> &L,
		   complex<double> &P,
		   complex<double> &dR,  
		   complex<double> &dL,  
		   complex<double> &dP,  
		   double           ne,
		   double           ve,
		   double           mi[],
		   double           qi[],
		   double           ri[],
		   double           vi[],
		   int              Ni,
		   double           B0,
		   double           f){
  int     N = 1 + Ni;
  double  n[N];
  double  m[N];
  double  q[N];
  double  v[N];
  double fp[N];
  double fc[N];
  double  X[N];
  double  Y[N];
  double  Z[N];

  n[0] = ne;
  calc_number_density_of_ions(&n[1],ne,qi,ri,Ni);

  m[0]  = m_electron;
  q[0]  = q_electron;
  v[0]  = ve;
  for(int l = 0;l < Ni;l++){
    m[l + 1] = mi[l];
    q[l + 1] = qi[l];
    v[l + 1] = vi[l];
  }  

  calc_frequency(fp,fc,m,q,n,N,B0);
  calc_XYZ(X,Y,Z,fp,fc,v,N,f);

  R = L = P = 1.0;
  for(int l = 0;l < N;l++){
    R -= X[l] / complex<double>(1.0 + Y[l],-Z[l]);
    L -= X[l] / complex<double>(1.0 - Y[l],-Z[l]);
    P -= X[l] / complex<double>(1.0       ,-Z[l]);
  }

  dR =  1.0 - R;
  dL =  1.0 - L;
  dP =  1.0 - P;
  for(int l = 0;l < N;l++){
    dR += 0.5 * X[l] * (complex<double>(0.0,1.0) * Z[l] - Y[l]) / complex<double>(1.0 + Y[l],-Z[l]) / complex<double>(1.0 + Y[l],-Z[l]);
    dL += 0.5 * X[l] * (complex<double>(0.0,1.0) * Z[l] + Y[l]) / complex<double>(1.0 - Y[l],-Z[l]) / complex<double>(1.0 - Y[l],-Z[l]);
    dP += 0.5 * X[l] * (complex<double>(0.0,1.0) * Z[l]       ) / complex<double>(1.0       ,-Z[l]) / complex<double>(1.0       ,-Z[l]);
  }
}

void calc_ABC(complex<double> &A,
	      complex<double> &B,
	      complex<double> &C,
	      complex<double> &F,
	      complex<double>  R,
	      complex<double>  L,
	      complex<double>  P,
	      double           theta){
  complex<double> S           = (R + L) / 2.0;
  complex<double> D           = (R - L) / 2.0;
  complex<double> RL          =  R * L;
  complex<double> SP          =  S * P;
  double          cos_theta   = cos(theta);
  double          cos_theta_2 = cos_theta * cos_theta;
  double          sin_theta   = sin(theta);
  double          sin_theta_2 = sin_theta * sin_theta;
  complex<double> G           = (RL - SP) * sin_theta_2;
  complex<double> H           = 2.0 * D * P * cos_theta;
  complex<double> F2          = G * G + H * H;
  
  A = S  * sin_theta_2 + P  *        cos_theta_2 ;
  B = RL * sin_theta_2 + SP * (1.0 + cos_theta_2);
  C = RL * P;
  F = sqrt(F2);
}

void calc_refractive_index(complex<double> refractive_index[2],
			   complex<double> R,
			   complex<double> L,
			   complex<double> P,
			   double          theta){
  const double    zero = DBL_MIN;
  complex<double> A,B,C,F;

  calc_ABC(A,B,C,F,R,L,P,theta);
  
  if(norm(A) <= zero){
    if(norm(B) <= zero){
      refractive_index[0] = 0.0;
      refractive_index[1] = 0.0;
    }else{
      if(B.real() > 0.0){
	refractive_index[0] = 0.0;
	refractive_index[1] = sqrt(C / B);
      }else{
	refractive_index[0] = sqrt(C / B);
	refractive_index[1] = 0.0;
      }
    }
  }else{
    if(norm(F) <= zero){
      refractive_index[0] = refractive_index[1] = sqrt(B / (2.0 * A));
    }else{
      if((B.real() * F.real() + B.imag() * F.imag()) >= 0.0){
	refractive_index[0] = sqrt((2.0 * C) / (B - F));
	refractive_index[1] = sqrt((B - F) / (2.0 * A));
      }else{
	refractive_index[0] = sqrt((B + F) / (2.0 * A));
	refractive_index[1] = sqrt((2.0 * C) / (B + F));
      }
    }    
  }
}

void calc_group_refractive_index(complex<double> group_refractive_index[2],
				 complex<double> R,
				 complex<double> L,
				 complex<double> P,
				 complex<double> dR,
				 complex<double> dL,
				 complex<double> dP,
				 double          theta){  
  complex<double>  nr[2];
  complex<double>  A,B,C,F;
  complex<double>  dS,dRL,dSP,dA,dB,dC;
  
  calc_refractive_index(nr,R,L,P,theta);
  calc_ABC(A,B,C,F,R,L,P,theta);
  
  dS   = (dR + dL) / 2.0;
  dRL  =        L        * dR + dL  * R;
  dSP  = ( R +  L) / 2.0 * dP + dS  * P;
  dA   = dS * sin(theta) * sin(theta) + dP * cos(theta) * cos(theta); 
  dB   = dSP * (1.0 + cos(theta) * cos(theta)) + dRL * sin(theta) * sin(theta);
  dC   =   R *  L        * dP + dRL * P;

  group_refractive_index[0] = nr[0] * (1.0 - (dA * (nr[0] * nr[0]) - dB + dC / (nr[0] * nr[0])) / F);
  group_refractive_index[1] = nr[1] * (1.0 + (dA * (nr[1] * nr[1]) - dB + dC / (nr[1] * nr[1])) / F);
}

void calc_phase_velocity(double          vp[2][3],
			 complex<double> R,
			 complex<double> L,
			 complex<double> P,
			 double          theta,
			 double          phi){  
  complex<double> nr[2];
  double          vp_abs;

  calc_refractive_index(nr,R,L,P,theta);

  if(fabs(real(nr[0])) >= 1e-10){
    vp_abs   = light_velocity / real(nr[0]);
    vp[0][0] = vp_abs * sin(theta) * cos(phi);
    vp[0][1] = vp_abs * sin(theta) * sin(phi);
    vp[0][2] = vp_abs * cos(theta);
  }else{
    vp[0][0] = 0.0;
    vp[0][1] = 0.0;
    vp[0][2] = 0.0;
  }  
  if(fabs(real(nr[0])) >= 1e-10){
    vp_abs   = light_velocity / real(nr[1]);
    vp[1][0] = vp_abs * sin(theta) * cos(phi);
    vp[1][1] = vp_abs * sin(theta) * sin(phi);
    vp[1][2] = vp_abs * cos(theta);  
  }else{
    vp[1][0] = 0.0;
    vp[1][1] = 0.0;
    vp[1][2] = 0.0;
  }
}

void calc_group_velocity(double          vg[2][3],
			 complex<double> R,
			 complex<double> L,
			 complex<double> P,
			 complex<double> dR,
			 complex<double> dL,
			 complex<double> dP,
			 double          theta,
			 double          phi){  
  complex<double>   S = (R + L) / 2.0;
  complex<double>   D = (R - L) / 2.0;
  complex<double>  nr[2];
  complex<double> gnr[2];
  double            v[3];
  complex<double>   alpha,beta,F,xi,eta,zeta,gp,gm,wb,wp,W,Pi,kappa,nr_th;
  double            vg_k,vg_th;

  calc_refractive_index(nr,R,L,P,theta);
  calc_group_refractive_index(gnr,R,L,P,dR,dL,dP,theta);

  alpha =    2.0 * D * P  * cos(theta);
  beta  = (R * L - S * P) * sin(theta) * sin(theta);
  F     = sqrt(alpha * alpha  + beta * beta);
  xi    = (alpha + CJ * beta) / F;
  eta   = xi / sqrt(norm(xi) + 1.0);
  zeta  = CJ / sqrt(norm(xi) + 1.0);

  gp    = (eta + zeta) / sqrt(2.0);
  gm    = (eta - zeta) / sqrt(2.0);

  wb    =  S  / (R * L)   - 1.0 / P;
  wp    = 0.5 * (1.0 / L  - 1.0 / R);

  W     = wb * gm * cos(theta) + CJ * wp * gp;
  Pi    = nr[0] * nr[0] * W * sin(theta);
  kappa = +CJ * alpha / (2.0 * F) / (conj(gm) * gp);
  nr_th = nr[0] * kappa * conj(gm) * Pi;

  vg_k  = light_velocity / real(gnr[0]);
  vg_th = light_velocity / real(gnr[0]) * -real(nr_th) / real(nr[0]);

  v[0]  = vg_k * sin(theta) + vg_th * cos(theta);
  v[1]  = 0.0;
  v[2]  = vg_k * cos(theta) - vg_th * sin(theta);

  vg[0][0] = cos(phi) * v[0] - sin(phi) * v[1];
  vg[0][1] = sin(phi) * v[0] + cos(phi) * v[1];
  vg[0][2] = v[2];  

  W     = wb * gp * cos(theta) + CJ * wp * gm;
  Pi    = nr[1] * nr[1] * W * sin(theta);
  kappa = -CJ * alpha / (2.0 * F) / (conj(gp) * gm);
  nr_th = nr[1] * kappa * conj(gp) * Pi;

  vg_k  = light_velocity / real(gnr[1]);
  vg_th = light_velocity / real(gnr[1]) * -real(nr_th) / real(nr[1]);

  v[0]  = vg_k * sin(theta) + vg_th * cos(theta);
  v[1]  = 0.0;
  v[2]  = vg_k * cos(theta) - vg_th * sin(theta);

  vg[1][0] = cos(phi) * v[0] - sin(phi) * v[1];
  vg[1][1] = sin(phi) * v[0] + cos(phi) * v[1];
  vg[1][2] = v[2];  
}

void calc_poynting_vector(double          q[2][3],
			  complex<double> R,
			  complex<double> L,
			  complex<double> P,
			  double          theta,
			  double          phi){  
  complex<double>   S = (R + L) / 2.0;
  complex<double>   D = (R - L) / 2.0;
  complex<double>   nr[2];
  complex<double>   alpha,beta,F,xi,eta,zeta,gp,gm,wb,wp,W,Pi;
  double            q_k,q_th,q_phi;
  double            q_tmp[3];

  calc_refractive_index(nr,R,L,P,theta);

  alpha =    2.0 * D * P  * cos(theta);
  beta  = (R * L - S * P) * sin(theta) * sin(theta);
  F     = sqrt(alpha * alpha + beta * beta);
  xi    = (alpha + CJ * beta) / F;
  eta   = xi / sqrt(norm(xi) + 1.0);
  zeta  = CJ / sqrt(norm(xi) + 1.0);

  gp    = (eta + zeta) / sqrt(2.0);
  gm    = (eta - zeta) / sqrt(2.0);

  wb    =  S  / (R * L)   - 1.0 / P;
  wp    = 0.5 * (1.0 / L  - 1.0 / R);

  W     = wb * gm * cos(theta) + CJ * wp * gp;
  Pi    = nr[0] * nr[0] * W * sin(theta);

  q_k   = Z0 / 2.0 *  real(1.0 / nr[0]);
  q_th  = Z0 / 2.0 * -real((conj(gm) * Pi) / nr[0]);
  q_phi = Z0 / 2.0 *  real((conj(gp) * Pi) / nr[0]);

  q_tmp[0]  = q_k * sin(theta) + q_th * cos(theta);
  q_tmp[1]  = q_phi;
  q_tmp[2]  = q_k * cos(theta) - q_th * sin(theta);

  q[0][0] = cos(phi) * q_tmp[0] - sin(phi) * q_tmp[1];
  q[0][1] = sin(phi) * q_tmp[0] + cos(phi) * q_tmp[1];
  q[0][2] = q_tmp[2];  

  W     = wb * gp * cos(theta) + CJ * wp * gm;
  Pi    = nr[1] * nr[1] * W * sin(theta);

  q_k   = Z0 / 2.0 *  real(1.0 / nr[1]);
  q_th  = Z0 / 2.0 * -real((conj(gp) * Pi) / nr[1]);
  q_phi = Z0 / 2.0 *  real((conj(gm) * Pi) / nr[1]);

  q_tmp[0]  = q_k * sin(theta) + q_th * cos(theta);
  q_tmp[1]  = q_phi;
  q_tmp[2]  = q_k * cos(theta) - q_th * sin(theta);

  q[1][0] = cos(phi) * q_tmp[0] - sin(phi) * q_tmp[1];
  q[1][1] = sin(phi) * q_tmp[0] + cos(phi) * q_tmp[1];
  q[1][2] = q_tmp[2];  
}

void calc_EH_vector(complex<double> eh[2][6],
		    complex<double> R,
		    complex<double> L,
		    complex<double> P,
		    double          theta,
		    double          phi){
  complex<double> S = (R + L) / 2.0;
  complex<double> D = (R - L) / 2.0;
  complex<double> nr[2];
  complex<double> alpha,beta,F,xi,eta,zeta,gp,gm,wb,wp,W,Pi;
  complex<double> e[3],h[3];

  alpha =    2.0 * D * P  * cos(theta);
  beta  = (R * L - S * P) * sin(theta) * sin(theta);
  F     = sqrt(alpha * alpha + beta * beta);
  xi    = (alpha + CJ * beta) / F;
  eta   = xi / sqrt(norm(xi) + 1.0);
  zeta  = CJ / sqrt(norm(xi) + 1.0);

  gp    = (eta + zeta) / sqrt(2.0);
  gm    = (eta - zeta) / sqrt(2.0);

  wb    =  S  / (R * L)   - 1.0 / P;
  wp    = 0.5 * (1.0 / L  - 1.0 / R);

  calc_refractive_index(nr,R,L,P,theta);

  W     = wb * gm * cos(theta) + CJ * wp * gp;
  Pi    = nr[0] * nr[0] * W * sin(theta);
  e[0]  = Pi * sin(theta) + gm *  cos(theta) - gp * 0.0;
  e[1]  =                   gm *  0.0        - gp * 1.0;
  e[2]  = Pi * cos(theta) + gm * -sin(theta) - gp * 0.0;
  e[0] *= Z0 / nr[0];
  e[1] *= Z0 / nr[0];
  e[2] *= Z0 / nr[0];
  h[0]  = gp *  cos(theta) + gm * 0.0;
  h[1]  = gp *  0.0        + gm * 1.0;
  h[2]  = gp * -sin(theta) + gm * 0.0;

  eh[0][0] = cos(phi) * e[0] - sin(phi) * e[1];
  eh[0][1] = sin(phi) * e[0] + cos(phi) * e[1];
  eh[0][2] = e[2];  
  eh[0][3] = cos(phi) * h[0] - sin(phi) * h[1];
  eh[0][4] = sin(phi) * h[0] + cos(phi) * h[1];
  eh[0][5] = h[2];  

  W     = wb * gp * cos(theta) + CJ * wp * gm;
  Pi    = nr[1] * nr[1] * W * sin(theta);
  e[0]  = Pi * sin(theta) + gp *  cos(theta) - gm * 0.0;
  e[1]  =                   gp *  0.0        - gm * 1.0;
  e[2]  = Pi * cos(theta) + gp * -sin(theta) - gm * 0.0;
  e[0] *= Z0 / nr[1];
  e[1] *= Z0 / nr[1];
  e[2] *= Z0 / nr[1];
  h[0]  = gm *  cos(theta) + gp * 0.0;
  h[1]  = gm *  0.0        + gp * 1.0;
  h[2]  = gm * -sin(theta) + gp * 0.0;

  eh[1][0] = cos(phi) * e[0] - sin(phi) * e[1];
  eh[1][1] = sin(phi) * e[0] + cos(phi) * e[1];
  eh[1][2] = e[2];  
  eh[1][3] = cos(phi) * h[0] - sin(phi) * h[1];
  eh[1][4] = sin(phi) * h[0] + cos(phi) * h[1];
  eh[1][5] = h[2];  
}


double calc_H_rotation(complex<double> R,
		       complex<double> L,
		       complex<double> P,
		       double          theta){
  complex<double> S = (R + L) / 2.0;
  complex<double> D = (R - L) / 2.0;
  complex<double> nr[2];
  complex<double> alpha,beta,F,xi;
  double          g_r;

  calc_refractive_index(nr,R,L,P,theta);
  
  alpha =    2.0 * D * P  * cos(theta);
  beta  = (R * L - S * P) * sin(theta) * sin(theta);
  F     = sqrt(alpha * alpha + beta * beta);
  xi    = (alpha + CJ * beta) / F;
  g_r   = real(xi) / (norm(xi) + 1.0);
  return g_r * cos(theta);
}

int    refractive_index_R(complex<double> &nr_R,
			  complex<double>  R,
			  complex<double>  L,
			  complex<double>  P,
			  double           theta){
  complex<double> nr[2];

  calc_refractive_index(nr,R,L,P,theta);

  if(calc_H_rotation(R,L,P,theta) >= 0.0){
    nr_R = nr[0];
  }else{
    nr_R = nr[1];
  }
  return (real(nr_R * nr_R) >= 0.0) ? 1 : 0;
}

int    refractive_index_L(complex<double> &nr_L,
			  complex<double>  R,
			  complex<double>  L,
			  complex<double>  P,
			  double           theta){
  complex<double> nr[2];

  calc_refractive_index(nr,R,L,P,theta);

  if(calc_H_rotation(R,L,P,theta) >= 0.0){
    nr_L = nr[0];
  }else{
    nr_L = nr[1];
  }
  return (real(nr_L * nr_L) >= 0.0) ? 1 : 0;
}

int    calc_EH_vector_R(VectorXcd      &eh,
			complex<double> R,
			complex<double> L,
			complex<double> P,
			double          theta,
			double          phi){
  complex<double> nr[2];
  complex<double> v[2][6];

  calc_refractive_index(nr,R,L,P,theta);
  calc_EH_vector(v,R,L,P,theta,phi);

  eh = VectorXcd::Zero(6);
  if(calc_H_rotation(R,L,P,theta) >= 0.0){
      eh(0) = v[0][0];
      eh(1) = v[0][1];
      eh(2) = v[0][2];
      eh(3) = v[0][3];
      eh(4) = v[0][4];
      eh(5) = v[0][5];
    if(real(nr[0] * nr[0]) >= 0.0){
      return 1;
    }
  }else{
      eh(0) = v[1][0];
      eh(1) = v[1][1];
      eh(2) = v[1][2];
      eh(3) = v[1][3];
      eh(4) = v[1][4];
      eh(5) = v[1][5];
    if(real(nr[1] * nr[1]) >= 0.0){
      return 1;
    }
  }
  return 0;
}

int    calc_EH_vector_L(VectorXcd      &eh,
			complex<double> R,
			complex<double> L,
			complex<double> P,
			double          theta,
			double          phi){
  complex<double> nr[2];
  complex<double> v[2][6];

  calc_refractive_index(nr,R,L,P,theta);
  calc_EH_vector(v,R,L,P,theta,phi);

  eh = VectorXcd::Zero(6);
  if(calc_H_rotation(R,L,P,theta) <= 0.0){
    eh(0) = v[0][0];
    eh(1) = v[0][1];
    eh(2) = v[0][2];
    eh(3) = v[0][3];
    eh(4) = v[0][4];
    eh(5) = v[0][5];
    if(real(nr[0] * nr[0]) >= 0.0){
      return 1;
    }
  }else{
    eh(0) = v[1][0];
    eh(1) = v[1][1];
    eh(2) = v[1][2];
    eh(3) = v[1][3];
    eh(4) = v[1][4];
    eh(5) = v[1][5];
    if(real(nr[1] * nr[1]) >= 0.0){
      return 1;
    }
  }
  return 0;
}

int    calc_spectral_matrix_R(MatrixXcd      &S,
			      complex<double> R,
			      complex<double> L,
			      complex<double> P,
			      double          theta,
			      double          phi){
  VectorXcd eh;
  int       ret;

  ret = calc_EH_vector_R(eh,R,L,P,theta,phi);
  S   = eh * eh.adjoint();
  return ret;
}

int    calc_spectral_matrix_H_R(MatrixXcd      &S,
				complex<double> R,
				complex<double> L,
				complex<double> P,
				double          theta,
				double          phi){
  VectorXcd eh,h(3);
  int       ret;

  ret  = calc_EH_vector_R(eh,R,L,P,theta,phi);
  h(0) = eh(3);
  h(1) = eh(4);
  h(2) = eh(5);
  S    = h * h.adjoint();
  return ret;
}


int    calc_spectral_matrix_L(MatrixXcd      &S,
			      complex<double> R,
			      complex<double> L,
			      complex<double> P,
			      double          theta,
			      double          phi){
  VectorXcd eh;
  int       ret;

  ret = calc_EH_vector_L(eh,R,L,P,theta,phi);
  S   = eh * eh.adjoint();
  return ret;
}

void   means_method(double    &theta,
		    double    &phi,
		    MatrixXcd &S){
  double kx,ky,kz;

  kx = imag(S(4,5));
  ky = imag(S(5,3));
  kz = imag(S(3,4));
  if(kz < 0.0){
    kx = -kx;
    ky = -ky;
    kz = -kz;
  }
  theta = atan2(sqrt(kx * kx + ky * ky),kz);
  phi   = atan2(ky,kx);
}

void   svd_method_H(double    &theta,
		    double    &phi,
		    MatrixXcd &S_H){
  MatrixXd A(6,3);
  MatrixXd V;
  double   kx,ky,kz;

  A(0,0) =  real(S_H(0,0)); A(0,1) =  real(S_H(0,1)); A(0,2) =  real(S_H(0,2));
  A(1,0) =  real(S_H(0,1)); A(1,1) =  real(S_H(1,1)); A(1,2) =  real(S_H(1,2));
  A(2,0) =  real(S_H(0,2)); A(2,1) =  real(S_H(1,2)); A(2,2) =  real(S_H(2,2));
  A(3,0) =             0.0; A(3,1) =  imag(S_H(0,1)); A(3,2) =  imag(S_H(0,2));
  A(4,0) = -imag(S_H(0,1)); A(4,1) =             0.0; A(4,2) =  imag(S_H(1,2));
  A(5,0) = -imag(S_H(0,2)); A(5,1) = -imag(S_H(1,2)); A(5,2) =             0.0;

  JacobiSVD<MatrixXd> svd(A,ComputeThinU | ComputeThinV);

  V = svd.matrixV();

  kx = V(0,2);
  ky = V(1,2);
  kz = V(2,2);
  if(kz < 0.0){
    kx = -kx;
    ky = -ky;
    kz = -kz;
  }
  theta = atan2(sqrt(kx * kx + ky * ky),kz);
  phi   = atan2(ky,kx);
}

double svd_method_full(double    &theta,
		       double    &phi,
		       MatrixXcd &S){
  MatrixXd A(36,3);
  VectorXd b(36),n;
  double   kx,ky,kz;

  for(int k = 0;k < 6;k++){
    A(k     ,0) =           0.0; A(k     ,1) =  real(S(2,k)); A(k     ,2) = -real(S(1,k));
    A(k +  6,0) = -real(S(2,k)); A(k +  6,1) =           0.0; A(k +  6,2) =  real(S(0,k));
    A(k + 12,0) =  real(S(1,k)); A(k + 12,1) = -real(S(0,k)); A(k + 12,2) =           0.0;
    b(k       ) =  Z0 * real(S(3,k));
    b(k +  6  ) =  Z0 * real(S(4,k));
    b(k + 12  ) =  Z0 * real(S(5,k));
  }
  for(int k = 0;k < 6;k++){
    A(k + 18,0) =           0.0; A(k + 18,1) =  imag(S(2,k)); A(k + 18,2) = -imag(S(1,k));
    A(k + 24,0) = -imag(S(2,k)); A(k + 24,1) =           0.0; A(k + 24,2) =  imag(S(0,k));
    A(k + 30,0) =  imag(S(1,k)); A(k + 30,1) = -imag(S(0,k)); A(k + 30,2) =           0.0;
    b(k + 18  ) =  Z0 * imag(S(3,k));
    b(k + 24  ) =  Z0 * imag(S(4,k));
    b(k + 30  ) =  Z0 * imag(S(5,k));
  }

  JacobiSVD<MatrixXd> svd(A,ComputeThinU | ComputeThinV);

  n  = svd.solve(b);

  kx    = n(0);
  ky    = n(1);
  kz    = n(2);
  theta = atan2(sqrt(kx * kx + ky * ky),kz);
  phi   = atan2(ky,kx);

  return sqrt(n(0) * n(0) + n(1) * n(1) + n(2) * n(2));
}

#endif
