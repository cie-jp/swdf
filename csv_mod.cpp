#include<iostream>
#include<cmath>

using namespace std;

#define N (50000)

int main(int argc,const char *argv[]){
  if(argc <= 1){
    return 0;
  }
  FILE   *fp;
  double *x,*y,*z,*F;
  double  xj,yj,zj,th,ph,theta,phi;
  int     num;
  double  tau,tmp,weight,cos_ij,sum;
  char    str[255];

  x = new double[N];
  y = new double[N];
  z = new double[N];
  F = new double[N];

  for(int c = 1;c < argc;c++){
    if((fp = fopen(argv[c],"r")) == NULL){
      goto EXIT;
    }
    for(num = 0;!feof(fp);num++){
      fscanf(fp,"%lf,%lf,%lf\n",&phi,&theta,&F[num]);
      theta = (90.0 - theta) * M_PI / 180.0;
      phi  *= M_PI / 180.0;
      x[num] = sin(theta) * cos(phi);
      y[num] = sin(theta) * sin(phi);
      z[num] = cos(theta);
      if(num == N){
	goto EXIT;
      }
    }
    fclose(fp);
    
    tau = num * num  / (16.0 * (num - 1.0)) * 2.0 * 2.0;
    
    sprintf(str,"%s.mod",argv[c]);
    fp = fopen(str,"w");
    for(th = 0.5;th <= 180.0;th += 1.0){
      for(ph = 0.5;ph <= 360.0;ph += 1.0){
	theta = th * M_PI / 180.0;
	phi   = ph * M_PI / 180.0;
	xj  = sin(theta) * cos(phi);
	yj  = sin(theta) * sin(phi);
	zj  = cos(theta);
	tmp = 0.0;
	sum = 0.0;
	for(int i = 0;i < num;i++){
	  cos_ij = x[i] * xj + y[i] * yj + z[i] * zj;
	  weight = exp(tau * (cos_ij - 1.0));
	  tmp   += weight * F[i];
	  sum   += weight;
	}
	tmp /= sum;
	fprintf(fp,"%e,%e,%e\n",ph,90.0 - th,tmp);
      }
    }
    fclose(fp);
  }

 EXIT:

  delete [] x;
  delete [] y;
  delete [] z;
  delete [] F;
  
  return 0;
}
