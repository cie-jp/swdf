/***************************************************************** 
 *
 * 乱数発生
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#ifndef _RANDOM_H_INCLUDE_
#define _RANDOM_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include"DATATYPE.h"

  typedef struct{
    unsigned long mt[624];
    int           mi;
  }RANDOM;
  
  void  RANDOM__INITIALIZE_SEED (RANDOM *rnd,unsigned long seed);
  void  RANDOM__INITIALIZE      (RANDOM *rnd);

  //x ~ Uniform(min,max) minとmaxは含まない開区間
  REAL8 RANDOM__UNIFORM         (RANDOM *rnd,
                                 REAL8   min,
                                 REAL8   max);
  //x ~ Normal(mu,sigma2)
  REAL8 RANDOM__NORMAL          (RANDOM *rnd,
                                 REAL8   mu,
                                 REAL8   sigma2);
  //x ~ Log-Normal(mu,sigma2)
  REAL8 RANDOM__LOG_NORMAL      (RANDOM *rnd,
                                 REAL8   mu,
                                 REAL8   sigma2);
  //x ~ Exponential(lambda)   sim               exp(-lambda * x), x > 0, lambda > 0
  REAL8 RANDOM__EXPONENTIAL     (RANDOM *rnd,
                                 REAL8   lambda);
  //x ~ Gamma(alpha,beta)     sim x^{ alpha - 1}exp(-beta   * x), x > 0, alpha  > 0, beta > 0
  REAL8 RANDOM__GAMMA           (RANDOM *rnd,
                                 REAL8   alpha,
                                 REAL8   beta);
  //x ~ Inv-Gamma(alpha,beta) sim x^{-alpha - 1}exp(-beta   / x), x > 0, alpha  > 0, beta > 0
  REAL8 RANDOM__INV_GAMMA       (RANDOM *rnd,
                                 REAL8   alpha,
                                 REAL8   beta);
  //x ~ GIG 2 parameter       sim x^{lambda - 1}exp(-omega / 2 * (x + 1 / x)), x > 0, lambda >= 0, omega > 0
  REAL8 RANDOM__GIG2            (RANDOM *rnd,
                                 REAL8   lambda,
                                 REAL8   omega);
  //x ~ GIG 3 parameter       sim x^{p-1}exp(-1/2*(ax+b/x)), x > 0, a > 0, b > 0, p in R
  REAL8 RANDOM__GIG3            (RANDOM *rnd,
                                 REAL8   a,
                                 REAL8   b,
                                 REAL8   p);
  //x ~ Multinomial(pi)
  INT4  RANDOM__MULTINOMIAL     (RANDOM *rnd,
                                 REAL8   pi[],
                                 INT4    K);
  //x ~ Truncated-Normal(mu,sigma2) (0以下の切断)
  REAL8 RANDOM__TRUNCATED_NORMAL(RANDOM *rnd,
                                 REAL8   mu,
                                 REAL8   sigma2);
  //x ~ von-mises Fisher(theta0,phi0,kappa) (球面の場合(p = 3)) sim kappa / (2pi * (exp(+kappa)-exp(-kappa))) exp(kappa * mu * x)
  //mu_x = sin(theta0) cos(phi0)
  //mu_y = sin(theta0) sin(phi0)
  //mu_z = cos(theta0)
  //x_x  = sin(theta ) cos(phi )
  //x_y  = sin(theta ) sin(phi )
  //x_z  = cos(theta ) 
 
  void  RANDOM__VON_MISES_FISHER(RANDOM *rnd,
                                 REAL8  *theta, //[rad]
                                 REAL8  *phi,   //[rad]
                                 REAL8   theta0,//[rad]
                                 REAL8   phi0,  //[rad]
                                 REAL8   kappa);
  
#ifdef __cplusplus
}
#endif

#endif
