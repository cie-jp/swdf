/***************************************************************** 
 *
 * OMP
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"OMP.h"

void orthogonal_matching_pursuit(double *x,double *D,double *y,int n,int m,int s){
  void    *mem;
  int     *Tp;//[n]
  double **Dp;//[n]
  double **Sp;//[m]
  double  *z; //[n]
  double  *r; //[m]
  double  *v; //[m - 1]
  double  *w; //[m - 1]
  double  *S; //[m * (m + 1) / 2];
  double   max,tmp;
  double   cor,yl2,rl2;
  int      buf;

  if((mem = malloc(sizeof(int) * n
                   + sizeof(double*) * n
                   + sizeof(double*) * m
                   + sizeof(double ) * n
                   + sizeof(double ) * m
                   + sizeof(double ) * (m - 1)
                   + sizeof(double ) * (m - 1)
                   + sizeof(double ) * m * (m + 1) / 2)) == NULL){
    return;
  }
  Tp = (int*    )mem;
  Dp = (double**)&Tp[n];
  Sp = (double**)&Dp[n];
  z  = (double* )&Sp[m];
  r  = (double* )&z [n];
  v  = (double* )&r [m];
  w  = (double* )&v [m - 1];
  S  = (double* )&w [m - 1];

  //添字行列の初期化
  for(int j = 0;j < n;j++){
    Tp[j] = j;
  }
  //ポインタ初期化
  for(int j = 0;j < n;j++){
    Dp[j] = D + j * m;
  }
  for(int j = 0;j < m;j++){
    Sp[j] = S + j * (j + 1) / 2;
  }
  //返り値変数の初期化
  for(int j = 0;j < n;j++){
     x[j] = 0.0;
  }
  //内積計算
  max = 0.0;
  cor = 0.0;
  for(int j = 0;j < n;j++){
    tmp = 0.0;
    for(int i = 0;i < m;i++){
      tmp += Dp[Tp[j]][i] * y[i];
    }
    if(fabs(tmp) > max){
      buf   = Tp[0];
      Tp[0] = Tp[j];
      Tp[j] = buf;
      max   = fabs(tmp);
      cor   = tmp;
    }
  }
  z[Tp[0]] = cor;
  Sp[0][0] = 1.0;
  x[Tp[0]] = cor;
  //Step - 2
  //||y||_2^2の計算
  yl2 = 0.0;
  for(int i = 0;i < m;i++){
    yl2 += y[i] * y[i];
  }
  //s = mで誤差は0になるはず
  if(s > m){
     s = m;
  }
  for(int k = 1;k < s;k++){
    //r = y - D * x
    rl2 = 0.0;
    for(int i = 0;i < m;i++){
      r[i] = y[i];
      for(int j = 0;j < k;j++){
	r[i] -= Dp[Tp[j]][i] * x[Tp[j]];
      }
      rl2 += r[i] * r[i];
    }
    if(rl2 <= yl2 * 1e-20){
      break;
    }
    //内積計算
    max = 0.0;
    for(int j = k;j < n;j++){
      tmp = 0.0;
      for(int i = 0;i < m;i++){
	tmp += Dp[Tp[j]][i] * r[i];
      }
      if(fabs(tmp) > max){
	buf   = Tp[k];
	Tp[k] = Tp[j];
	Tp[j] = buf;
	max   = fabs(tmp);
      }
    }
    //update v
    for(int j = 0;j < k;j++){
      tmp  = 0.0;
      for(int i = 0;i < m;i++){
	tmp += Dp[Tp[j]][i] * Dp[Tp[k]][i];
      }
      v[j] = tmp;
    }    
    //update w = S * v
    for(int j = 0;j < k;j++){
      w[j] = 0.0;
    }
    for(int j = 0;j < k;j++){
      w[j] += Sp[j][j] * v[j];
      for(int i = 0;i < j;i++){
	w[j] += Sp[j][i] * v[i];
	w[i] += Sp[j][i] * v[j];
      }
    }
    //update S
    tmp = 1.0;
    for(int j = 0;j < k;j++){
      tmp -= v[j] * w[j];
    }
    tmp = 1.0 / tmp;
    for(int j = 0;j < k;j++){
      for(int i = 0;i <= j;i++){
	Sp[j][i] += tmp * w[j] * w[i];
      }
    }
    for(int i = 0;i < k;i++){
      Sp[k][i]  = 0.0;
    }
    for(int i = 0;i < k;i++){
      Sp[k][i] -= Sp[i][i] * v[i];
      for(int j = 0;j < i;j++){
	Sp[k][i] -= Sp[i][j] * v[j];
	Sp[k][j] -= Sp[i][j] * v[i];
      }
    }
    tmp = 1.0;
    for(int i = 0;i < k;i++){
      tmp -= Sp[k][i] * v[i];
    }
    Sp[k][k] = tmp;
    //update z
    tmp = 0.0;
    for(int i = 0;i < m;i++){
      tmp += Dp[Tp[k]][i] * y[i];
    }
    z[Tp[k]] = tmp;
    //update x
    for(int j = 0;j <= k;j++){
      x[Tp[j]] = 0.0;
    }
    for(int j = 0;j <= k;j++){
      x[Tp[j]] += Sp[j][j] * z[Tp[j]];
      for(int i = 0;i < j;i++){
	x[Tp[j]] += Sp[j][i] * z[Tp[i]];
	x[Tp[i]] += Sp[j][i] * z[Tp[j]];
      }
    }
    //
  }

  free(mem);
}

void orthogonal_matching_pursuit_positive(double *x,double *D,double *y,int n,int m,int s){
  void    *mem;
  int     *Tp;//[n]
  double **Dp;//[n]
  double **Sp;//[m]
  double  *z; //[n]
  double  *r; //[m]
  double  *v; //[m - 1]
  double  *w; //[m - 1]
  double  *S; //[m * (m + 1) / 2];
  double   max,tmp;
  double   cor,yl2,rl2;
  int      buf;

  if((mem = malloc(sizeof(int) * n
                   + sizeof(double*) * n
                   + sizeof(double*) * m
                   + sizeof(double ) * n
                   + sizeof(double ) * m
                   + sizeof(double ) * (m - 1)
                   + sizeof(double ) * (m - 1)
                   + sizeof(double ) * m * (m + 1) / 2)) == NULL){
    return;
  }
  Tp = (int*    )mem;
  Dp = (double**)&Tp[n];
  Sp = (double**)&Dp[n];
  z  = (double* )&Sp[m];
  r  = (double* )&z [n];
  v  = (double* )&r [m];
  w  = (double* )&v [m - 1];
  S  = (double* )&w [m - 1];

  //添字行列の初期化
  for(int j = 0;j < n;j++){
    Tp[j] = j;
  }
  //ポインタ初期化
  for(int j = 0;j < n;j++){
    Dp[j] = D + j * m;
  }
  for(int j = 0;j < m;j++){
    Sp[j] = S + j * (j + 1) / 2;
  }
  //返り値変数の初期化
  for(int j = 0;j < n;j++){
     x[j] = 0.0;
  }
  //内積計算
  max = 0.0;
  cor = 0.0;
  for(int j = 0;j < n;j++){
    tmp = 0.0;
    for(int i = 0;i < m;i++){
      tmp += Dp[Tp[j]][i] * y[i];
    }
    if(tmp > max){
      buf   = Tp[0];
      Tp[0] = Tp[j];
      Tp[j] = buf;
      max   = fabs(tmp);
      cor   = tmp;
    }
  }
  z[Tp[0]] = cor;
  Sp[0][0] = 1.0;
  x[Tp[0]] = cor;
  //Step - 2
  //||y||_2^2の計算
  yl2 = 0.0;
  for(int i = 0;i < m;i++){
    yl2 += y[i] * y[i];
  }
  //s = mで誤差は0になるはず
  if(s > m){
     s = m;
  }
  for(int k = 1;k < s;k++){
    //r = y - D * x
    rl2 = 0.0;
    for(int i = 0;i < m;i++){
      r[i] = y[i];
      for(int j = 0;j < k;j++){
	r[i] -= Dp[Tp[j]][i] * x[Tp[j]];
      }
      rl2 += r[i] * r[i];
    }
    if(rl2 <= yl2 * 1e-20){
      break;
    }
    //内積計算
    max = 0.0;
    for(int j = k;j < n;j++){
      tmp = 0.0;
      for(int i = 0;i < m;i++){
	tmp += Dp[Tp[j]][i] * r[i];
      }
      if(tmp > max){
	buf   = Tp[k];
	Tp[k] = Tp[j];
	Tp[j] = buf;
	max   = fabs(tmp);
      }
    }
    //update v
    for(int j = 0;j < k;j++){
      tmp  = 0.0;
      for(int i = 0;i < m;i++){
	tmp += Dp[Tp[j]][i] * Dp[Tp[k]][i];
      }
      v[j] = tmp;
    }    
    //update w = S * v
    for(int j = 0;j < k;j++){
      w[j] = 0.0;
    }
    for(int j = 0;j < k;j++){
      w[j] += Sp[j][j] * v[j];
      for(int i = 0;i < j;i++){
	w[j] += Sp[j][i] * v[i];
	w[i] += Sp[j][i] * v[j];
      }
    }
    //update S
    tmp = 1.0;
    for(int j = 0;j < k;j++){
      tmp -= v[j] * w[j];
    }
    tmp = 1.0 / tmp;
    for(int j = 0;j < k;j++){
      for(int i = 0;i <= j;i++){
	Sp[j][i] += tmp * w[j] * w[i];
      }
    }
    for(int i = 0;i < k;i++){
      Sp[k][i]  = 0.0;
    }
    for(int i = 0;i < k;i++){
      Sp[k][i] -= Sp[i][i] * v[i];
      for(int j = 0;j < i;j++){
	Sp[k][i] -= Sp[i][j] * v[j];
	Sp[k][j] -= Sp[i][j] * v[i];
      }
    }
    tmp = 1.0;
    for(int i = 0;i < k;i++){
      tmp -= Sp[k][i] * v[i];
    }
    Sp[k][k] = tmp;
    //update z
    tmp = 0.0;
    for(int i = 0;i < m;i++){
      tmp += Dp[Tp[k]][i] * y[i];
    }
    z[Tp[k]] = tmp;
    //update x
    /*for(int j = 0;j <= k;j++){
      x[Tp[j]] = 0.0;
    }
    for(int j = 0;j <= k;j++){
      x[Tp[j]] += Sp[j][j] * z[Tp[j]];
      for(int i = 0;i < j;i++){
	x[Tp[j]] += Sp[j][i] * z[Tp[i]];
	x[Tp[i]] += Sp[j][i] * z[Tp[j]];
      }
      }*/
    x[Tp[k]] = max;
    //
  }

  free(mem);
}
