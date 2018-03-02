/*****************************************************************
 *
 * 5次方程式の解を求める
 * 
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"EQUATION.h"

int main(int argc,const char *argv[]){
  COMPLEX a[6];
  COMPLEX z[5];
  INT4    i;

  a[0] = COMPLEX__MAKE_RE_IM(-120.0,0.0);
  a[1] = COMPLEX__MAKE_RE_IM( 274.0,0.0);
  a[2] = COMPLEX__MAKE_RE_IM(-225.0,0.0);
  a[3] = COMPLEX__MAKE_RE_IM(  85.0,0.0);
  a[4] = COMPLEX__MAKE_RE_IM( -15.0,0.0);
  a[5] = COMPLEX__MAKE_RE_IM(   3.0,0.0);

  EQUATION__SOLVE_DKA(z,a,5,1000,1.0e-10);

  fprintf(stderr,"================================================================\n");
  fprintf(stderr,"INPUT PARAMETERS\n");
  fprintf(stderr,"================================================================\n");
  fprintf(stderr,"f(z) = a[0] + a[1] z + a[2] z^2 + a[3] z^3 + a[4] z^4 + a[5] z^5\n");
  for(i = 0;i <= 5;i++){
    fprintf(stderr,"   a[%d] = (%20lf,%20lf)\n",
	    i,
	    a[i].real,
	    a[i].imag);
  }  
  fprintf(stderr,"================================================================\n");
  fprintf(stderr,"RESULTS\n");
  fprintf(stderr,"================================================================\n");
  for(i = 0;i <  5;i++){
    fprintf(stderr,"   z[%d] = (%20lf,%20lf), f(z[%d]) = (%20lf,%20lf)\n",
	    i,
	    z[i].real,
	    z[i].imag,
	    i,
	    COMPLEX__REAL(COMPLEX__POLYNOMIAL(z[i],a,5)),
	    COMPLEX__IMAG(COMPLEX__POLYNOMIAL(z[i],a,5)));
  }
  fprintf(stderr,"================================================================\n");

  return EXIT_SUCCESS;
}
