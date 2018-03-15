/*****************************************************************
 *
 * dLV法の検証プログラム
 * 
 *
 *                           Created  by Mamoru Ota (2018/03/05)
 * 
 *****************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"CLDIA.h"

//1行1列
// b0          要素数 = 1 + (1 - 1)

//2行2列
// b0 b1  
//  0 b2       要素数 = 2 + (2 - 1)

//3行3列
// b0 b1  0  
//  0 b2 b3
//  0  0 b4    要素数 = 3 + (3 - 1)

//4行4列
// b0 b1  0  0
//  0 b2 b3  0
//  0  0 b4 b5
//  0  0  0 b6 要素数 = 4 + (4 - 1)

#define M (10) //次元数
#define N  500

int main(void){
  RANDOM rnd;
  int    m;
  REAL   b[2 * M - 1];
  REAL   u[2 * M - 1 + 2];
  REAL   v[2 * M - 1 + 2];
  INT    n,k;
  REAL   delta[N];
  
  RANDOM__INITIALIZE(&rnd);

  for(k = 0;k < (2 * M - 1);k++){
    b[k] = RANDOM__NORMAL(&rnd,0.0,1.0);
  }

  for(n = 0;n < N;n++){
    delta[n] = 1.0;
  }

  u[0]                   = 0.0;
  u[(2 * M - 1 + 2) - 1] = 0.0;
  v[0]                   = 0.0;
  v[(2 * M - 1 + 2) - 1] = 0.0;
  for(k = 1;k < ((2 * M - 1 + 2) - 1);k++){
    u[k] = (b[k - 1] * b[k - 1]) / (1.0 + delta[0] * u[k - 1]);
  }

  for(k = 0;k < (2 * M - 1);k++){
    fprintf(stderr,"%d %g\n",k,b[k]);
  }
  fprintf(stderr,"\n");

  for(k = 0;k < (2 * M - 1 + 2);k++){
    fprintf(stderr,"%d %g\n",k,u[k]);
  }

  for(n = 0;n < N - 1;n++){
    for(k = 1;k < ((2 * M - 1 + 2) - 1);k++){
      v[k] = u[k] * (1.0 + delta[n] * u[k + 1]) / (1.0 + delta[n + 1] * v[k - 1]);
    }

    for(k = 0;k < (2 * M - 1 + 2);k++){
      u[k] = v[k];
    }
    
    for(k = 0;k < (2 * M - 1 + 2);k++){
      fprintf(stderr,"%d %20.10f\n",k,u[k]);
    }
    fprintf(stderr,"\n");
  }

  //2重対角行列の特異値
  fprintf(stderr,"Singular Values\n");
  for(k = 1;k < (2 * M - 1 + 2);k += 2){
    fprintf(stderr,"%d %20.10f\n",k / 2,u[k]);
  }
  fprintf(stderr,"\n");

  return 0;
}
