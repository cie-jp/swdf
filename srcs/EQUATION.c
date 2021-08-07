/***************************************************************** 
 *
 * 方程式関連
 *
 *
 *                           Created  by Mamoru Ota (2018/01/25)
 * 
 *****************************************************************/

#include<stdlib.h>
#include<math.h>
#include"EQUATION.h"

INT4 EQUATION__SOLVE_DKA(COMPLEX z[],
			 COMPLEX a[],
			 INT4    n,
			 INT4    max_iteration,
			 REAL8   eps){
  void    *buf;
  COMPLEX *b;//[1 + n]
  COMPLEX *c;//[1 + n]
  REAL8   *d;//[1 + n]
  COMPLEX *e;//[n]
  COMPLEX  s;
  REAL8   Rmin,Rmax,R;
  INT4    isinit;
  REAL8   q;
  REAL8   err,err_max;
  INT4    i,j,k;

  if((buf = malloc(sizeof(COMPLEX) * (1 + n) + 
		   sizeof(COMPLEX) * (1 + n) +  
		   sizeof(REAL8)   * (1 + n) + 
		   sizeof(COMPLEX) *  n     )) == NULL){
    return EXIT_FAILURE;
  }

  b = (COMPLEX*) buf;
  c = (COMPLEX*)&b[1 + n];
  d = (REAL8  *)&c[1 + n];
  e = (COMPLEX*)&d[1 + n];

  // =================================================================================
  // 1. 最大次数の係数を1とする多項式係数を計算
  //    a_{0} + a_{1}z + a_{2}z^{2} + ... + a_{n - 1}z^{n - 1} + a_{n}z^{n} = 0 
  //    b_{0} + b_{1}z + b_{2}z^{2} + ... + b_{n - 1}z^{n - 1} +      z^{n} = 0 
  //    b_{i} = a_{i}  / a_{n}
  // =================================================================================
  for(i = 0;i <= n;i++){
    b[i] = COMPLEX__DIV(a[i],a[n]);
  }

  // =================================================================================
  // 2. Aberthの初期値計算
  // =================================================================================

  // =================================================================================
  // 2.1 解の重心(s,0)を計算
  // =================================================================================
  s = COMPLEX__MUL(COMPLEX__MAKE_REAL(-1.0 / (REAL8)n),b[n - 1]);

  // =================================================================================
  // 2.2 解の重心(s,0)を中心として全ての解を含む円の半径Rを計算する多項式の係数を算出
  // =================================================================================
  for(i = 0;i <= n;i++){
    c[i] = b[i];
  }
  for(i = 0;i <= n;i++){
    for(j = n - 1;j >= i;j--){      
      c[j] = COMPLEX__ADD(c[j],COMPLEX__MUL(s,c[j + 1]));
    }
  }
  for(i = 0;i <= n;i++){
    d[i] = COMPLEX__ABS(c[i]);
  }

  // =================================================================================
  // 2.3 Rの値範囲を推定
  // =================================================================================
  Rmin   = 0.0;
  Rmax   = 0.0;
  isinit = 0;
  for(i = 0;i <  n;i++){
    R = pow(n * d[i],1.0 / (REAL8)(n - i));
    if(!isinit){
      Rmax   = R;
      isinit = 1;
      continue;
    }
    if(R > Rmax){
      Rmax   = R;
    }
  }

  // =================================================================================
  // 2.4 Rを二分法で計算
  // =================================================================================
  for(j = 0;j < 64;j++){
    R  = (Rmin + Rmax) / 2.0;
    q  =  0.0;
    for(i = 0;i < n;i++){
      q += -d[i] * pow(R,i);
    }
    q +=  pow(R,n); 
    if(q < 0.0){
      Rmin = R;
    }else{
      Rmax = R;
    }
  }
  R = (Rmin + Rmax) / 2.0;

  // =================================================================================
  // 2.5 解の初期値を計算
  // =================================================================================
  for(i = 0;i <  n;i++){
    z[i] = COMPLEX__ADD(s,COMPLEX__MAKE_POLAR(R,2.0 * M_PI * (i + 3.0 / 4.0) / (REAL8)n));
  }

  // =================================================================================
  // 3. Durand-Kernerの公式による解の更新
  // =================================================================================
  for(k = 0;k < max_iteration;k++){
    err_max = 0.0;
    for(i = 0;i <  n;i++){
      e[i] = COMPLEX__POLYNOMIAL(z[i],b,n);    
      for(j = 0;j < n;j++){
	if(i == j){
	  continue;
	}
	e[i] = COMPLEX__DIV(e[i],COMPLEX__SUB(z[i],z[j]));
      }
      err = COMPLEX__ABS(e[i]);
      if(err_max < err){
	err_max = err;
      }
    }    
    for(i = 0;i <  n;i++){
      z[i] = COMPLEX__SUB(z[i],e[i]);
    }
    if(err_max < eps){
      break;
    }
  }

  free(buf);

  return EXIT_SUCCESS;
}