#ifndef _CRANDOM_H_INCLUDE_
#define _CRANDOM_H_INCLUDE_

#include<iostream>
#include<cmath>

//CRandom Class
class CRandom{
private:
  unsigned long mt[624];
  int           mi;
public:
  //initialize random generator
  CRandom(unsigned long seed = 0x00000000UL);

  double uniform();

  double uniform(double min,double max);  
  
  int    multinomial(double pi[],int K);

  void   von_mises_fisher(double &theta,double &phi,double theta0,double phi0,double kappa);

};

#endif
