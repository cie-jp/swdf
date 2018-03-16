/***************************************************************** 
 *
 * Toeplitz行列関係
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include<stdlib.h>
#include"TOEPLITZ.h"

void symmetric_toeplitz_solver(double x[],double r[],double b[],int n){
  double *y,*t;
  double  v, w, z;

  if(n <= 0){
    fprintf(stderr,"Error : symmetric_toeplitz_solver");
    exit(EXIT_FAILURE);
  }

  if((y = (double*)malloc(sizeof(double) * n)) == NULL){
    fprintf(stderr,"Error : symmetric_toeplitz_solver");
    exit(EXIT_FAILURE);
  }

  if((t = (double*)malloc(sizeof(double) * n)) == NULL){
    fprintf(stderr,"Error : symmetric_toeplitz_solver");
    exit(EXIT_FAILURE);
  }

  x[0] =  b[0] / r[0];
  if(n == 1){
    return;
  }
  y[0] = -r[1] / r[0];
  z    =  r[0] + r[1] * y[0];
  for(int i = 1;i < n;i++){
    //update v
    v = 0.0;
    for(int j = 0;j < i;j++){
      v += r[j + 1] * x[(i - 1) - j];
    }
    //update x
    x[i] =  (b[i + 0] - v) / z;
    for(int j = 0;j < i;j++){
      t[j] = x[j] + x[i] * y[(i - 1) - j];
    }
    for(int j = 0;j < i;j++){
      x[j] = t[j];
    }
    if(i >= (n - 1)){
      break;
    }
    //update w
    w = 0.0;
    for(int j = 0;j < i;j++){
      w += r[j + 1] * y[(i - 1) - j];
    }
    //update y
    y[i] = -(r[i + 1] + w) / z;
    for(int j = 0;j < i;j++){
      t[j] = y[j] + y[i] * y[(i - 1) - j];
    }
    for(int j = 0;j < i;j++){
      y[j] = t[j];
    }
    //update z
    z *= (1.0 - y[i] * y[i]);
  }

  free(y);
  free(t);
}

double symmetric_toeplitz_log_determinant(double r[],int n){
  double *y,*t;
  double  w, z;
  double  det;

  if(n <= 0){
    fprintf(stderr,"Error : symmetric_toeplitz_log_determinant");
    exit(EXIT_FAILURE);
  }

  if((y = (double*)malloc(sizeof(double) * n)) == NULL){
    fprintf(stderr,"Error : symmetric_toeplitz_log_determinant");
    exit(EXIT_FAILURE);
  }

  if((t = (double*)malloc(sizeof(double) * n)) == NULL){
    fprintf(stderr,"Error : symmetric_toeplitz_log_determinant");
    exit(EXIT_FAILURE);
  }

  det  = log(r[0]);
  if(n == 1){
    return det;
  }
  y[0] = -r[1] / r[0];
  z    =  r[0] + r[1] * y[0];
  for(int i = 1;i < n - 1;i++){
    det += log(z);
    //update w
    w = 0.0;
    for(int j = 0;j < i;j++){
      w += r[j + 1] * y[(i - 1) - j];
    }
    //update y
    y[i] = -(r[i + 1] + w) / z;
    for(int j = 0;j < i;j++){
      t[j] = y[j] + y[i] * y[(i - 1) - j];
    }
    for(int j = 0;j < i;j++){
      y[j] = t[j];
    }
    //update z
    z *= (1.0 - y[i] * y[i]);
  }
  det += log(z);

  free(y);
  free(t);

  return det;
}
