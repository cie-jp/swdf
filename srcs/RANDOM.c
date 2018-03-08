/***************************************************************** 
 *
 * 乱数発生
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"RANDOM.h"

void  RANDOM__INITIALIZE_SEED (RANDOM *rnd,unsigned long seed){
  rnd->mt[0]  = seed & 0xffffffffUL;
  for(rnd->mi = 1;rnd->mi < 624;rnd->mi++){
    rnd->mt[rnd->mi] = (1812433253UL * (rnd->mt[rnd->mi - 1] ^ (rnd->mt[rnd->mi - 1] >> 30)) + rnd->mi); 
    rnd->mt[rnd->mi] &= 0xffffffffUL;
  }
}

void  RANDOM__INITIALIZE      (RANDOM *rnd){
  RANDOM__INITIALIZE_SEED(rnd,0x00000000UL);
}

REAL8 RANDOM__UNIFORM         (RANDOM *rnd,
                               REAL8   min,
                               REAL8   max){
  unsigned long yr;
  REAL8         z;
  int           i;
  
  if(rnd->mi >= 624){
    rnd->mi  = 0;
    for(i =   0;i < 227;i++){
      yr         = (rnd->mt[i] & 0x80000000UL) | (rnd->mt[i + 1] & 0x7fffffffUL);
      rnd->mt[i] =  rnd->mt[i + 397] ^ (yr >> 1) ^ ((yr & 0x1UL) ? 0x9908b0dfUL : 0x0UL);
    }
    for(i = 227;i < 623;i++){
      yr         = (rnd->mt[i] & 0x80000000UL) | (rnd->mt[i + 1] & 0x7fffffffUL);
      rnd->mt[i] =  rnd->mt[i - 227] ^ (yr >> 1) ^ ((yr & 0x1UL) ? 0x9908b0dfUL : 0x0UL);
    }
    yr           = (rnd->mt[623] & 0x80000000UL) | (rnd->mt[    0] & 0x7fffffffUL);
    rnd->mt[623] =  rnd->mt[396] ^ (yr >> 1) ^ ((yr & 0x1UL) ? 0x9908b0dfUL : 0x0UL);
  }
  yr   =  rnd->mt[rnd->mi++];
  yr  ^= (yr >> 11);
  yr  ^= (yr <<  7) &  0x9d2c5680UL;
  yr  ^= (yr << 15) &  0xefc60000UL;
  yr  ^= (yr >> 18);
  z    = (yr + 0.5) * (1.0 / 4294967296.0);
  return min + z * (max - min);
}

REAL8 RANDOM__NORMAL          (RANDOM *rnd,
                               REAL8   mu,
                               REAL8   sigma2){
  REAL8 z;
  
  z = sqrt(-2.0 * log(RANDOM__UNIFORM(rnd,0.0,1.0))) * cos(2.0 * M_PI * RANDOM__UNIFORM(rnd,0.0,1.0));
  return mu + sqrt(sigma2) * z;
}

REAL8 RANDOM__LOG_NORMAL      (RANDOM *rnd,
                               REAL8   mu,
                               REAL8   sigma2){
  return exp(RANDOM__NORMAL(rnd,mu,sigma2));
}

REAL8 RANDOM__EXPONENTIAL     (RANDOM *rnd,
                               REAL8   lambda){
  return -log(1.0 - RANDOM__UNIFORM(rnd,0.0,1.0)) / lambda;
}

REAL8 RANDOM__GAMMA           (RANDOM *rnd,
                               REAL8   alpha,
                               REAL8   beta){
  REAL8 c,d,e,f,X,Y,Z,W;
  
  if(alpha == 1.0){
    return RANDOM__EXPONENTIAL(rnd,beta);
  }
  if(alpha <  1.0){
    c = M_E / (alpha + M_E);
    do{
      X = RANDOM__UNIFORM(rnd,0.0,1.0);
      Y = RANDOM__UNIFORM(rnd,0.0,1.0);
      if(X <= c){
	X =  pow(X / c,1.0 / alpha);
	if(Y <= exp(-X)){
	  return X / beta;
	}
      }else{
	X = -log((1.0 - X) / (c * alpha));
	if(Y <= pow(X,alpha - 1.0)){
	  return X / beta;
	}
      }
    }while(1);
  }else{
    c = 1.0   / sqrt(2.0 * alpha - 1.0);
    d = alpha - log(4.0);
    e = alpha + sqrt(2.0 * alpha - 1.0);
    f = 1.0   + log(4.5);
    do{
      X = RANDOM__UNIFORM(rnd,0.0,1.0);
      Y = RANDOM__UNIFORM(rnd,0.0,1.0);
      Z = X * X * Y;
      Y = c * log(X / (1.0 - X));
      X = alpha * exp(Y);
      W = d + e * Y - X;
      if(W >= 4.5 * Z - f){
	return X / beta;
      }
      if(W >= log(Z)){
	return X / beta;
      }
    }while(1);  
  }
}

REAL8 RANDOM__INV_GAMMA       (RANDOM *rnd,
                               REAL8   alpha,
                               REAL8   beta){
  return 1.0 / RANDOM__GAMMA(rnd,alpha,beta);
}

REAL8 RANDOM__GIG2            (RANDOM *rnd,
                               REAL8   lambda,
                               REAL8   omega){
  REAL8 alpha;
  REAL8 psi_n0,psi_n1;
  REAL8 psi_p0,psi_p1;
  REAL8 s ,t ;
  REAL8 sd,td;
  REAL8 p, q, r, qr, pqr;
  REAL8 U, V, W;
  REAL8 X;
  REAL8 chi;

  alpha  = sqrt(omega * omega + lambda * lambda) - lambda;
  psi_n0 = -(-alpha * (cosh(-1.0) - 1.0) - lambda * (exp(-1.0) - (-1.0) - 1.0));
  psi_p0 = -(-alpha * (cosh(+1.0) - 1.0) - lambda * (exp(+1.0) - (+1.0) - 1.0));
  s = ((0.5 <= psi_n0) && (psi_n0 <= 2.0)) ? 1.0 : 
      (psi_n0 > 2.0)                       ? sqrt(4.0 / (alpha * cosh(1.0) + lambda)) : 
                                             fmin(1.0 / lambda, log(1.0 + 1.0 / alpha + sqrt(1.0 / (alpha * alpha) + 2.0 / alpha)));
  t = ((0.5 <= psi_p0) && (psi_p0 <= 2.0)) ? 1.0 : 
      (psi_p0 > 2.0)                       ? sqrt(2.0 / (alpha + lambda)) : 
                                             log( 4.0 / (alpha + 2.0 * lambda));
  psi_n0 = -(-alpha * (cosh(-s) - 1.0) - lambda * (exp(-s) - (-s) - 1.0));
  psi_p0 = -(-alpha * (cosh(+t) - 1.0) - lambda * (exp(+t) - (+t) - 1.0));
  psi_n1 =  (-alpha *  sinh(-s)        - lambda * (exp(-s) - 1.0));
  psi_p1 = -(-alpha *  sinh(+t)        - lambda * (exp(+t) - 1.0));
  p      = 1.0 / psi_n1;
  r      = 1.0 / psi_p1;
  sd     = s   - p * psi_n0;
  td     = t   - r * psi_p0;
  q      = sd  + td;
  qr     = q   + r;
  pqr    = p   + qr;
  do{
    U = RANDOM__UNIFORM(rnd,0.0,1.0);
    V = RANDOM__UNIFORM(rnd,0.0,1.0);
    W = RANDOM__UNIFORM(rnd,0.0,1.0);
    if(U < (q  / pqr)){
      X   = -sd + q * V;
      chi = 1.0;
    }else
      if(U < (qr / pqr)){
        X   =  td + r * log(1.0 / V);
        chi = exp(-psi_p0 - psi_p1 * (X - t));
      }else{
        X   = -sd - p * log(1.0 / V);
        chi = exp(-psi_n0 + psi_n1 * (X + s));
      }
  }while((W * chi) > exp(-alpha * (cosh(X) - 1.0) - lambda * (exp(X) - X - 1.0)));
  return (lambda / omega + sqrt(1.0 + (lambda * lambda) / (omega * omega))) * exp(X);
}

REAL8 RANDOM__GIG3            (RANDOM *rnd,
                               REAL8   a,
                               REAL8   b,
                               REAL8   p){
  REAL8 lambda;
  REAL8 omega;

  lambda = p;
  omega  = sqrt(a * b);
  if(lambda >= 0.0){
    return sqrt(b / a) * RANDOM__GIG2(rnd, lambda,omega);
  }else{
    return sqrt(b / a) / RANDOM__GIG2(rnd,-lambda,omega);
  }
}

INT4  RANDOM__MULTINOMIAL     (RANDOM *rnd,
                               REAL8   pi[],
                               INT4    K){
  REAL8 sum,val,y1,y2;
  INT4  c,k;

  sum = 0.0;
  for(c = 0;c < K;c++){
    sum += pi[c];
  }
  val = RANDOM__UNIFORM(rnd,0.0,sum);
  k   = 0;
  y1  = pi[0];
  for(c = 1;c < K;c++){
    y2 = y1 + pi[c];
    if((y1 < val) && (val <= y2)){
      k = c;
      break;
    }
    y1 = y2;
  }
  return k;
}

REAL8 RANDOM__TRUNCATED_NORMAL(RANDOM *rnd,
                               REAL8   mu,
                               REAL8   sigma2){
  REAL8 x = (mu >= 0.0) ? mu : 0.0;
  REAL8 z;
  REAL8 x_min;
  REAL8 x_max;
  INT4  n;

  //Slice Samplerによる実装
  for(n = 0;n < 5;n++){
    z     = sqrt(-2.0 * sigma2 * log(RANDOM__UNIFORM(rnd,0.0,1.0)) + (x - mu) * (x - mu));
    x_min = mu - z;
    x_max = mu + z;
    if(x_min < 0.0){
      x = RANDOM__UNIFORM(rnd,  0.0,x_max);
    }else{
      x = RANDOM__UNIFORM(rnd,x_min,x_max);
    }
  }
  return x;
}  

void  RANDOM__VON_MISES_FISHER(RANDOM *rnd,
                               REAL8  *theta,
                               REAL8  *phi,
                               REAL8   theta0,
                               REAL8   phi0,
                               REAL8   kappa){
  REAL8 u,w0;
  REAL8 tmp_theta,tmp_phi;
  REAL8 x,y,z;
  REAL8 X,Y,Z;
  
  if(kappa == 0.0){
    w0 = RANDOM__UNIFORM(rnd,-1.0,1.0);
  }else{
    u  = RANDOM__UNIFORM(rnd, 0.0,1.0);
    w0 = 1.0 + (log(u) + log(1.0 - (u - 1.0) / u * exp(-2.0 * kappa))) / kappa;
  }
  tmp_theta = acos(w0);
  tmp_phi   = RANDOM__UNIFORM(rnd,0.0,2.0 * M_PI);
  
  x = sin(tmp_theta) * cos(tmp_phi);
  y = sin(tmp_theta) * sin(tmp_phi);
  z = cos(tmp_theta);

  X =  cos(theta0) * x + sin(theta0) * z;
  Y =  y;
  Z = -sin(theta0) * x + cos(theta0) * z;

  x =  cos(phi0)   * X - sin(phi0)   * Y;
  y =  sin(phi0)   * X + cos(phi0)   * Y;
  z =  Z;

  *theta = acos (z);
  *phi   = atan2(y,x);
}
