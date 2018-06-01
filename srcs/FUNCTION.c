/***************************************************************** 
 *
 * 関数
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"FUNCTION.h"

double psi0(double x){
  double v,w;

  if(x < 0.0){
    return 0.0;
  }
  for(v = 0.0;x < 8.0;x++){
    v -= 1.0 / x;
  }
  w = 1.0 / (x * x);
  return v - (((((((-0.443259803921569  * w + 0.0833333333333333) * w
		    -0.021092796092796) * w + 0.0075757575757576) * w
		    -0.004166666666667) * w + 0.0039682539682540) * w
	            -0.008333333333333) * w + 0.0833333333333333) * w
                    -0.500000000000000  / x + log(x);
}

double psi1(double x){
  double v,w;

  if(x < 0.0){
    return 0.0;
  }
  for(v = 0.0;x < 8.0;x++){
    v += 1.0 / (x * x);
  }
  w = 1.0 / (x * x);
  return v + ((((((((-7.09215686274510  * w + 1.166666666666667) * w
		     -0.25311355311355) * w + 0.075757575757576) * w
		     -0.03333333333333) * w + 0.023809523809524) * w
		     -0.03333333333333) * w + 0.166666666666667) * w
	             +0.50000000000000  / x + 1.000000000000000) / x;
}

double psi(int n, double x){
  double t,u,v,w;
  int    k;

  if(n == 0){
    return psi0(x);
  }
  if(n == 1){
    return psi1(x);
  }
  if(x < 0.0){
    return 0.0;
  }
  u = 1.0;
  for(k = 1 - n;k < 0;k++){
    u *= k;
  }
  for(v = 0.0;x < 8.0;x++){
    v += 1.0 / pow(x,n + 1.0);
  }
  w = x * x;
  t = (((((((-7.09215686274510
	     * (n + 15.0) * (n + 14.0) / (16.0 * 15.0 * w) + 1.166666666666667)
 	     * (n + 13.0) * (n + 12.0) / (14.0 * 13.0 * w) - 0.253113553113553)
	     * (n + 11.0) * (n + 10.0) / (12.0 * 11.0 * w) + 0.075757575757576)
	     * (n +  9.0) * (n +  8.0) / (10.0 *  9.0 * w) - 0.033333333333333)
	     * (n +  7.0) * (n +  6.0) / ( 8.0 *  7.0 * w) + 0.023809523809524)
	     * (n +  5.0) * (n +  4.0) / ( 6.0 *  5.0 * w) - 0.033333333333333)
             * (n +  3.0) * (n +  2.0) / ( 4.0 *  3.0 * w) + 0.166666666666667)
             * (n +  1.0) *  n         / ( 2.0 *  1.0 * w)
             +  0.5 * n / x  +    1.0;
  return u * (t / pow(x,n) + n * v);
}

double bessi0(double x){
  double ax,ans;
  double y;

  if((ax = fabs(x)) < 3.75){
    y   = x / 3.75;
    y  *= y;
    ans = 1.0 + y * (3.5156229 + y * (3.0899424 + y * (1.2067492
	  + y * (0.2659732 + y * (0.360768e-1 + y * 0.45813e-2)))));
  }else{
    y   = 3.75 / ax;
    ans = (exp(ax) / sqrt(ax)) *     (0.39894228   + y * ( 0.1328592e-1
	  + y * ( 0.225319e-2  + y * (-0.157565e-2 + y * (  0.916281e-2 
          + y * (-0.2057706e-1 + y * (0.2635537e-1 + y * (-0.1647633e-1 
          + y *   0.392377e-2))))))));
  }
  return ans;
}

double bessi1(double x){
  double ax,ans;
  double y;

  if((ax = fabs(x)) < 3.75){
    y    = x / 3.75;
    y   *= y;
    ans  = ax * (0.5 + y * (0.87890594 + y * (0.51498869 + y * (0.15084934 
	  + y * (0.2658733e-1 + y * (0.301532e-2 + y * 0.32411e-3))))));
  }else{
    y    = 3.75 / ax;
    ans  = 0.2282967e-1 + y * (-0.2895312e-1 + y * (0.1787654e-1 
         - y * 0.420059e-2));
    ans  = 0.39894228 + y * (-0.3988024e-1 + y * (-0.362018e-2
	 + y * (0.163801e-2 + y * (-0.1031555e-1 + y * ans))));
    ans *= (exp(ax) / sqrt(ax));
  }
  return (x < 0.0) ? -ans : ans;
}

double bessk0(double x){
  double ans;
  double y;
  
  if(x <= 2.0){
    y = x * x / 4.0;
    ans = (-log(x / 2.0) * bessi0(x)) + (-0.57721566 + y * (0.42278420 
	  + y * (0.23069756 + y * (0.3488590e-1 + y * (0.262698e-2 
          + y * (0.10750e-3 + y * 0.74e-5))))));
  }else{
    y = 2.0 / x;
    ans = (exp(-x) / sqrt(x)) * (1.25331414 + y * (-0.7832358e-1
	  + y * (0.2189568e-1 + y * (-0.1062446e-1 + y * (0.587872e-2 
          + y * (-0.251540e-2 + y * 0.53208e-3))))));
  }
  return ans;
}

double bessk1(double x){
  double ans;
  double y;
  
  if(x <= 2.0){
    y = x * x / 4.0;
    ans = (log(x / 2.0) * bessi1(x)) + (1.0 / x) * (1.0 + y * (0.15443144
	+ y * (-0.67278579 + y * (-0.18156897 + y * (-0.1919402e-1 
        + y * (-0.110404e-2 + y * (-0.4686e-4)))))));
  }else{
    y = 2.0 / x;
    ans = (exp(-x) / sqrt(x)) * (1.25331414 + y * (0.23498619
	+ y * (-0.3655620e-1 + y * (0.1504268e-1 + y * (-0.780353e-2 
	+ y * (0.325614e-2   + y * (-0.68245e-3)))))));
  }
  return ans;
}

double bessi(int n,double x){
  const double ACC   =    40.0;
  const double BIGNO =  1.0e10;
  const double BIGNI = 1.0e-10;
  int    j;
  double bi,bim,bip,tox,ans;

  if(n <  0){
    fprintf(stderr,"Index n less than 0 in bessi\n");
    exit(EXIT_FAILURE);
  }
  if(n == 0){
    return bessi0(x);
  }
  if(n == 1){
    return bessi1(x);
  }
  if(x == 0.0){
    return 0.0;
  }else{
    tox = 2.0 / fabs(x);
    bip = ans = 0.0;
    bi  = 1.0;
    for(j = 2 * (n + (int)sqrt(ACC * n));j > 0;j--){
      bim = bip + j * tox * bi;
      bip = bi;
      bi  = bim;
      if(fabs(bi) > BIGNO){
	ans *= BIGNI;
	bi  *= BIGNI;
	bip *= BIGNI;
      }
      if(j == n){
	ans = bip;
      }
    }
    ans *= bessi0(x) / bi;
    return ((x < 0.0) && (n & 1)) ? -ans : ans;
  }
}

double bessk(int n,double x){
  int    j;
  double bk,bkm,bkp,tox;

  if(n <  0){
    fprintf(stderr,"Index n less than 0 in bessk\n");
    exit(EXIT_FAILURE);
  }
  if(n == 0){
    return bessk0(x);
  }
  if(n == 1){
    return bessk1(x);
  }
  tox = 2.0 / x;
  bkm = bessk0(x);
  bk  = bessk1(x);
  for(j = 1;j < n;j++){
    bkp = bkm + j * tox * bk;
    bkm = bk;
    bk  = bkp;
  }
  return bk;
}

double chebev(double a,double b,double c[],int m,double x){
  double  d  = 0.0;
  double dd  = 0.0;
  double sv, y, y2;
  int    j;

  if((x - a) * (x - b) > 0.0){
    fprintf(stderr,"Error : chebev(a,b,c,m,x)\n");
    exit(EXIT_FAILURE);
  }
  y2 = 2.0 * (y = (2.0 * x - a - b) / (b - a));
  for(j = m - 1;j >= 1;j--){
    sv = d;
    d  = y2 * d - dd + c[j];
    dd = sv;
  }
  return y  * d - dd + 0.5 * c[0];
}

void   beschb(double x,double *gam1,double *gam2,double *gampl,double *gammi){
  static double c1[] = {
    -1.142022680371172e0,   6.516511267076e-3,
        3.08709017308e-4,     -3.470626964e-6,
             6.943764e-9,          3.6780e-11,
               -1.36e-13};
  static double c2[] = {
     1.843740587300906e0,-0.076852840844786e0,
       1.271927136655e-3,     -4.971736704e-6,
           -3.3126120e-8,         2.42310e-10,
               -1.70e-13,            -1.0e-15};
  double xx;

  xx     = 8.0 * x * x - 1.0;
  *gam1  =  chebev(-1.0,1.0,c1,7,xx);
  *gam2  =  chebev(-1.0,1.0,c2,8,xx);
  *gampl = *gam2 - x * (*gam1);
  *gammi = *gam2 + x * (*gam1);
}

double lnKv_large_orders(double nu,double x){
  double z;
  double tmp;
  double eta;
  double t,t2,t3,t4,t5,t6,t7,t8,t9;
  double fact;
  double nu2,nu3;
  double u1,u2,u3;
  
  z     = x / nu;
  tmp   = sqrt(1.0 + z * z);
  t     = 1.0 / tmp;
  t2    = t * t;
  t3    = t * t2;
  t4    = t * t3;
  t5    = t * t4;
  t6    = t * t5;
  t7    = t * t6;
  t8    = t * t7;
  t9    = t * t8;
  nu2   = nu * nu;
  nu3   = nu * nu2;
  u1    = (3.0 * t - 5.0 * t3) / 24.0;
  u2    = (81.0 * t2 - 462.0 * t4 + 385.0 * t6) / 1152.0;
  u3    = (30375.0 * t3 - 369603.0 * t5 + 765765.0 * t7 - 425425.0 * t9) / 414720.0;
  eta   = tmp + log(z / (1.0 + tmp));
  fact  = 1.0 - u1 / nu + u2 / nu2 - u3 / nu3;
  return 0.5 * log(M_PI / (2.0f * nu)) - nu * eta - 0.5 * log(tmp) + log(fact);
}

double lnKv(double nu,double x){
  const double EPS   = 1.0e-16;
  const double XMIN  =     2.0;
  const int    MAXIT =   10000;

  int    k,num;
  double mu,mu_2;
  double K0,K1;
  double x_2,x_2_2,ln_2x;
  double x_2_i;
  double mu_pi,sigma;
  double gm,gp,G1,G2;
  double tmp1, tmp2 ;
  double pk,qk,fk,ck;
  double dK0,dK1;
  double ak,bk,dk,Ck,h,dh,S,dS;
  double q1,q2,a1;
  double lnKv;

  if(x <= 0.0){
    fprintf(stderr,"Error : lnKv(nu,x) x <= 0.0\n");
    exit(EXIT_FAILURE);
  }
  nu   = fabs(nu);
  if(nu >= 20.0){
    lnKv_large_orders(nu,x);
  }
  num  = (int)(nu + 0.5);
  mu   = nu - num;
  mu_2 = mu *  mu;
  if(x < XMIN){
    x_2   =    x / 2.0;
    x_2_2 =  x_2 * x_2;
    ln_2x =  -log(x_2);
    mu_pi = mu *  M_PI;
    sigma = mu * ln_2x;
    beschb(mu,&G1,&G2,&gp,&gm);
    tmp1  = (fabs(mu_pi) < EPS) ? 1.0 : (mu_pi  /  sin(mu_pi));
    tmp2  = (fabs(sigma) < EPS) ? 1.0 : (sinh(sigma) / sigma );
    fk = tmp1 * (cosh(sigma) * G1 + tmp2 * ln_2x * G2);
    ck = 1.0;
    pk = 0.5 * exp(sigma) / gp;
    qk = 0.5 / exp(sigma) / gm;
    K0 =  fk;
    K1 =  pk;
    for(k = 1;k <= MAXIT;k++){
      fk  =(k * fk + pk + qk)/(k * k - mu_2);
      ck *= (x_2_2 / k);
      pk /= (k - mu);
      qk /= (k + mu);
      dK0 =  ck * fk;
      K0 += dK0;
      dK1 = ck * (pk - k * fk);
      K1 += dK1;
      if(fabs(dK0) < fabs(K0) * EPS){
	break;
      }
    }
    if(k > MAXIT){
      fprintf(stderr,"Error : lnKv(nu,x) x <= 2.0\n");
      exit(EXIT_FAILURE);
    }
    K1   /= x_2 * K0;
    x_2_i = 2.0 /  x;
    tmp1  = x_2_i * (mu + 1);
    lnKv  = log(K0);
    for(k = 1;k <= num;k++){
      lnKv += log(K1);
      K1    = tmp1 + 1.0 / K1;
      tmp1 += x_2_i;
    }
  }else{
    bk = 2.0 * (1.0 + x);
    dk = 1.0 / bk;
    h  = dh  = dk;
    q1 =  0.0;
    q2 =  1.0;
    a1 = 0.25 - mu_2;    
    qk =  Ck  = a1;
    ak = -a1;
    S  = 1.0 + qk * dh;
    for(k = 2;k <= MAXIT;k++){
      ak  -=   2 * (k - 1);
      Ck   = -ak * Ck /  k;
      tmp1 = (q1 - bk * q2) / ak;
      q1   = q2;
      q2   = tmp1;
      qk  += tmp1 * Ck;
      bk  += 2.0;
      dk   = 1.0 / (bk + ak * dk);
      dh = (bk * dk - 1.0) * dh;
      h += dh;
      dS = qk * dh;
      S += dS;
      if(fabs(dS / S) < EPS){
	break;
      }
    }
    if(k > MAXIT){
      fprintf(stderr,"Error : lnKv(nu,x) 2.0 < x %e,%e\n",nu,x);
      exit(EXIT_FAILURE);
    }
    h     = a1  * h;
    K1    = (mu + x + 0.5 - h) / x;
    x_2_i = 2.0 / x;
    tmp1  = x_2_i * (mu + 1);
    lnKv  = 0.5 * log(M_PI / (2.0 * x)) - x - log(S);
    for(k = 1;k <= num;k++){
      lnKv += log(K1);
      K1    = tmp1 + 1.0 / K1;
      tmp1 += x_2_i;
    }
  }
  return lnKv;
}
