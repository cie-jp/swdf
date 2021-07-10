#include<iostream>
#include<cmath>
#include"./include/crandom.h"

CRandom::CRandom(unsigned long seed){
  mt[0]  = seed & 0xffffffffUL;
  for(mi = 1;mi < 624;mi++){
    mt[mi] = (1812433253UL * (mt[mi - 1] ^ (mt[mi - 1] >> 30)) + mi); 
    mt[mi] &= 0xffffffffUL;
  }
}

double CRandom::uniform(){
  unsigned long  yr;

  if(mi >= 624){
    mi  = 0;
    for(int i =   0;i < 227;i++){
      yr = (mt[  i] & 0x80000000UL) | (mt[i + 1] & 0x7fffffffUL);
      mt[i] = mt[i + 397] ^ (yr >> 1) ^ ((yr & 0x1UL) ? 0x9908b0dfUL : 0x0UL);
    }
    for(int i = 227;i < 623;i++){
      yr = (mt[  i] & 0x80000000UL) | (mt[i + 1] & 0x7fffffffUL);
      mt[i] = mt[i - 227] ^ (yr >> 1) ^ ((yr & 0x1UL) ? 0x9908b0dfUL : 0x0UL);
    }
      yr = (mt[623] & 0x80000000UL) | (mt[    0] & 0x7fffffffUL);
      mt[623] = mt[  396] ^ (yr >> 1) ^ ((yr & 0x1UL) ? 0x9908b0dfUL : 0x0UL);
  }
  yr   =   mt[mi++];
  yr  ^= (yr >> 11);
  yr  ^= (yr <<  7) &  0x9d2c5680UL;
  yr  ^= (yr << 15) &  0xefc60000UL;
  yr  ^= (yr >> 18);
  return (yr + 0.5) * (1.0 / 4294967296.0); 
} 

double CRandom::uniform(double min,double max){
  return min + uniform() * (max - min);
}

int    CRandom::multinomial(double pi[],int K){
  double sum,val,y1,y2;
  int    c,k;

  sum = 0.0;
  for(c = 0;c < K;c++){
    sum += pi[c];
  }
  val = uniform(0.0,sum);
  k   = 0;
  y1  = pi[0];
  for(int c = 1;c < K;c++){
    y2 = y1 + pi[c];
    if((y1 < val) && (val <= y2)){
      k = c;
      break;
    }
    y1 = y2;
  }
  return k;
}

void CRandom::von_mises_fisher(double &theta,double &phi,double theta0,double phi0,double kappa){
  double u,w0;
  double tmp_theta,tmp_phi;
  double x,y,z;
  double X,Y,Z;
  
  if(kappa == 0.0){
    w0 = uniform(-1.0,1.0);
  }else{
    u  = uniform( 0.0,1.0);
    w0 = 1.0 + (log(u) + log(1.0 - (u - 1.0) / u * exp(-2.0 * kappa))) / kappa;
  }
  tmp_theta = acos(w0);
  tmp_phi   = uniform(0.0,2.0 * M_PI);

  x = sin(tmp_theta) * cos(tmp_phi);
  y = sin(tmp_theta) * sin(tmp_phi);
  z = cos(tmp_theta);

  X =  cos(theta0) * x + sin(theta0) * z;
  Y =  y;
  Z = -sin(theta0) * x + cos(theta0) * z;

  x =  cos(phi0)   * X - sin(phi0)   * Y;
  y =  sin(phi0)   * X + cos(phi0)   * Y;
  z =  Z;

  theta = acos(z);
  phi   = atan2(y,x);
}
