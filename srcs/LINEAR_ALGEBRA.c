/***************************************************************** 
 *
 * 線形代数
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/
#include<time.h>
#include"LINEAR_ALGEBRA.h"
#include"RANDOM.h"

int la_lu(double *A,int P[],int n){
  int  i,j,k;
  int  buf,l;
  double max,tmp;

  if((A == NULL) || (P == NULL) || (n < 1)){
    fprintf(stderr,"Error : la_lu - Invalid argument.");
    return -1;
  }
  for(i = 0;i < n;i++){
    P[i] = i;
  }
  for(k = 0;k < n - 1;k++){
    max = fabs(A[k * n + k]);
    l   = k;
    for(j = k + 1;j < n;j++){
      tmp = fabs(A[j * n + k]);
      if(tmp > max){
	 max = tmp;
	 l   = j;
      }
    }
    if(k != l){
      buf  = P[k];
      P[k] = P[l];
      P[l] = buf;
      for(i = 0;i < n;i++){
	tmp          = A[k * n + i];
	A[k * n + i] = A[l * n + i];
	A[l * n + i] = tmp;
      }
    }
    for(j = k + 1;j < n;j++){
      if(A[k * n + k] == 0.0){
	fprintf(stderr,"Error : la_lu - Division by zero.");
	return -1;
      }
      A[j * n + k] /= A[k * n + k];
      for(i = k + 1;i < n;i++){
	A[j * n + i] -= A[j * n + k] * A[k * n + i];
      }
    }
  }
  return 0;
}

int la_solve(double x[],double *A,double b[],int n){
  int     i,j;
  int     c;
  int    *P;
  double *y;
  double *LU;

  if((x == NULL) || (A == NULL) || (b == NULL) || (n < 1)){
    fprintf(stderr,"Error : la_solve - Invalid argument.");
    return -1;
  }
  c = sizeof(int) * n + sizeof(double) * (n + n * n);
  if((P = (int*)malloc(c)) == NULL){
    fprintf(stderr,"Error : la_solve - Can't allocate memory.");
    return -1;
  }
  y  = (double*)(P + n);
  LU = y + n;
  memcpy(LU,A,n * n * sizeof(double));
  if(la_lu(LU,P,n) == -1){
    free(P);
    return -1;
  }
  y[0] = b[P[0]];
  for(i = 1;i < n;i++){
    y[i]  = b[P[i]];
    for(j = 0;j < i;j++){
      y[i] -= LU[i * n + j] * y[j];
    }
  }
  for(i = n - 1;i >= 0;i--){
    x[i]  = y[i];
    for(j = i + 1;j < n;j++){
      x[i] -= LU[i * n + j] * x[j];
    }
    if(LU[i * n + i] == 0.0){
      fprintf(stderr,"Error : la_solve - Division by zero.");
      return -1;
    }
    x[i] /= LU[i * n + i];
  }
  free(P);
  return 0;
}

int la_trace(double *res,double *A,int n){
  int    i;
  double tr;

  if((res == NULL) || (A == NULL) || (n < 1)){
    fprintf(stderr,"Error : la_trace - Invalid argument.");
    return -1;
  }
  tr  = 0.0;
  for(i = 0;i < n;i++){
    tr += A[i * n + i];
  }  
  *res = tr;
  return 0;
}

int la_det(double *res,double *A,int n){
  int     i;
  int     c;
  int    *P;
  double *y;
  double *LU;
  double _det;

  if((res == NULL) || (A == NULL) || (n < 1)){
    fprintf(stderr,"Error : la_det - Invalid argument.");
    return -1;
  }
  c = sizeof(int) * n + sizeof(double) * (n + n * n);
  if((P = (int*)malloc(c)) == NULL){
    fprintf(stderr,"Error : la_det - Can't allocate memory.");
    return -1;
  }
  y  = (double*)(P + n);
  LU = y + n;
  memcpy(LU,A,n * n * sizeof(double));
  if(la_lu(LU,P,n) == -1){
    free(P);
    return -1;
  }
  _det = 1.0;
  for(i = 0;i < n;i++){
    _det *= LU[i * n + i]; 
  }
  *res = _det;
  free(P);
  return 0;
}

int la_inv(double *A,int n){
  int     i,j,k;
  int     c;
  int    *P;
  double *LU_inv;

  if((A == NULL) || (n < 1)){
    fprintf(stderr,"Error : la_inv - Invalid argument.");
    return -1;
  }
  c = sizeof(int) * n + sizeof(double) * n * n;
  if((P = (int*)malloc(c)) == NULL){
    fprintf(stderr,"Error : la_inv - Can't allocate memory.");
    return -1;
  }
  memset(P,0x00,c);  
  LU_inv = (double*)(P + n);
  if(la_lu(A,P,n) == -1){
    free(P);
    return -1;
  }
  for(i = 0;i < n;i++){
    LU_inv[i * n + i] = 1.0;
  }
  for(i = 0;i < n;i++){
    for(j = i + 1;j < n;j++){
      for(k = 0;k < i + 1;k++){
	LU_inv[j * n + k] -= A[j * n + i] * LU_inv[i * n + k];
      }
    }
  } 
  for(i = n - 1;i >= 0;i--){
    for(k = i;k < n;k++){
      if(A[i * n + i] == 0.0){
	fprintf(stderr,"Error : la_inv - Division by zero.");
	return -1;
      }
      LU_inv[i * n + k] /= A[i * n + i];
    }
    for(j = i - 1;j >= 0;j--){
      for(k = i;k < n;k++){
	LU_inv[j * n + k] -= A[j * n + i] * LU_inv[i * n + k];
      }
    }
  }  
  for(j = 0;j < n;j++){
    for(i = 0;i < j;i++){
      A[j * n + P[i]] = 0.0;
      for(k = j;k < n;k++){
	A[j * n + P[i]] += LU_inv[j * n + k] * LU_inv[k * n + i];
      }
    }
    for(i = j;i < n;i++){
      A[j * n + P[i]] = LU_inv[j * n + i];
      for(k = i + 1;k < n;k++){
	A[j * n + P[i]] += LU_inv[j * n + k] * LU_inv[k * n + i];
      }
    }    
  }
  free(P);
  return 0;
}

int la_tridiagonalize(double *A,double *P,int n){
  double t,c,s;
  int    i,j,k,l,m;

  if((A == NULL) || (n < 1)){
    return -1;
  }
  if( P == NULL){
    for(k = 0;k < n - 2;k++){
      l = k + 1;
      t = 0.0;
      for(i = l;i < n;i++){
	t += A[i * n + k] * A[i * n + k];
      }
      if(t == 0.0){
	continue;
      }
      s = (A[l * n + k] > 0.0) ? sqrt(t) : -sqrt(t);
      c =  1.0 / (t + A[l * n + k] * s);
      A[l * n + k] += s;
      for(i = l;i < n;i++){
	t = 0.0;
	j =   l;
	for(;j < i;j++){
	  t += A[i * n + j] * A[j * n + k];
	}
	for(;j < n;j++){
	  t += A[j * n + i] * A[j * n + k];
	}
	A[k * n + i] = t * c;
      }
      t  = 0.0;
      for(i = l;i < n;i++){
	t += A[k * n + i] * A[i * n + k];
      }
      t *= 0.5 * c;
      for(i = l;i < n;i++){
	A[k * n + i] -= t * A[i * n + k];
      }
      for(i = l;i < n;i++){
	for(j = i;j < n;j++){
	  A[j * n + i] -= A[k * n + i] * A[j * n + k];
	  A[j * n + i] -= A[k * n + j] * A[i * n + k];
	}
      }
      A[l * n + k] = -s;
    }
    for(i = 0;i < n - 1;i++){
      A[i * n + (i + 1)] = A[(i + 1) * n + i];
    }
    for(i = 0;i < n - 2;i++){
      for(j = i + 2;j < n;j++){
	A[i * n + j] = A[j * n + i] = 0.0;
      }
    }
  }else{
    for(i = 0;i < n;i++){
      P[i * n + i] = 1.0;
      for(j = i + 1;j < n;j++){
	P[i * n + j] = P[j * n + i] = 0.0;
      }
    }
    for(k = 0;k < n - 2;k++){
      l = k + 1;
      t = 0.0;
      for(i = l;i < n;i++){
	t += A[i * n + k] * A[i * n + k];
      }
      if(t == 0.0){
	continue;
      }
      s = (A[l * n + k] > 0.0) ? sqrt(t) : -sqrt(t);
      c =  1.0 / (t + A[l * n + k] * s);
      A[l * n + k] += s;
      for(i = l;i < n;i++){
	t = 0.0;
	j =   l;
	for(;j < i;j++){
	  t += A[i * n + j] * A[j * n + k];
	}
	for(;j < n;j++){
	  t += A[j * n + i] * A[j * n + k];
	}
	A[k * n + i] = t * c;
      }
      t  = 0.0;
      for(i = l;i < n;i++){
	t += A[k * n + i] * A[i * n + k];
      }
      t *= 0.5 * c;
      for(i = l;i < n;i++){
	A[k * n + i] -= t * A[i * n + k];
      }
      for(i = l;i < n;i++){
	for(j = i;j < n;j++){
	  A[j * n + i] -= A[k * n + i] * A[j * n + k];
	  A[j * n + i] -= A[k * n + j] * A[i * n + k];
	}
      }
      for(j = l;j < n;j++){
	P[j * n] = A[j * n + k] * A[j * n + k];
	for(i = j + 1;i < n;i++){
	  A[j * n + i] = A[j * n + k] * A[i * n + k];
	}
      }
      for(j = 1;j < n;j++){
	for(i = l;i < n;i++){
	  P[i] = P[j * n + i] * P[i * n];
	  m  = l;
	  for(;m < i;m++){
	    P[i] += P[j * n + m] * A[m * n + i];
	  }
	  m += 1;
	  for(;m < n;m++){
	    P[i] += P[j * n + m] * A[i * n + m];
	  }
	}
	for(i = l;i < n;i++){
	  P[j * n + i] -= P[i] * c;
	}
      }
      A[l * n + k] = -s;
    }
    for(i = 0;i < n - 1;i++){
      A[i * n + (i + 1)] = A[(i + 1) * n + i];
    }
    for(i = 0;i < n - 2;i++){
      for(j = i + 2;j < n;j++){
	A[i * n + j] = A[j * n + i] = 0.0;
      }
    }
    for(i = 1;i < n    ;i++){
        P[i] = P[i * n] = 0.0;
    }
  }
  return 0;
}

int la_eig(double *A, //入力 行列 [n][n]
           double *P,
           int     n){
  int     i,j,k,l,m,p,q,r;
  double  T[5];
  double *B;
  double *Q;
  double *R;
  double  t,a,c,s,z,d,e;
  
  if((A == NULL) || (n < 1)){
    return -1;
  }
  if( n == 2){
    if(A[0] != A[3]){
      t =  0.5 * atan(2.0 * A[1] / (A[0] - A[3]));
    }else{
      t = (A[1] > 0.0) ? M_PI / 4.0 : -M_PI / 4.0;
    }
    c = cos(t);
    s = sin(t);
    T[0] =     c;
    T[1] =     s;
    T[2] = -T[1];
    T[3] =  T[0];
    d = c * c * A[0] + s * s * A[3] + 2 * s * c * A[1];
    e = A[0]  + A[3] - d;
    A[0] =     d;
    A[1] =     e;
    A[2] =   0.0;
    A[3] =   0.0;
    if(P != NULL){
      P[0] =  T[0];
      P[1] =  T[2];
      P[2] =  T[1];
      P[3] =  T[3];
    }
  }else{
    if(  P == NULL){
      Q = (n >= 4) ? A + 2 * n : T;
    }else{
      Q = (double*)malloc(sizeof(double) * n * n);
      if(Q == NULL){
	return -1;
      }
    }
    la_tridiagonalize(A,P,n);//3重対角化
    B = A + n;
    for(i = 1;i < n;i++){
      A[i    ] = A[i * n + i    ];
      B[i - 1] = A[i * n + i - 1];
    }
    //A[0] : 対角成分(0,0)
    //A[1] : 対角成分(1,1)
    //A[2] : 対角成分(2,2)
    //A[3] : 対角成分(3,3)
    //..
    //B[0] : 非対角成分(0,1)
    
    if(P == NULL){//P 直交行列 
      R = Q + n;
      for(m = n;m >= 2;m--){
	p = m - 2;
	q = m - 1;
	d =   0.0;
	for(e = B[p];fabs(e) > 1e-17;e = B[p]){//1e-17
	  s = (A[p] + A[q]) * 0.5;
	  c =  A[p] * A[q]  - B[p] * B[p];
	  c =  s * s  - c;
	  if(c <=  0.0){
	    z = s;
	  }else{
	    a = sqrt(c);
	    c = s + a;
	    s = s - a;
	    z = (fabs(c - A[q]) < fabs(s - A[q])) ? c : s;//zはシフト量
	  }
	  for(i = 0;i < m;i++){
	    A[i] -= z;
	  }
          //QR = A
	  Q[0] =  1.0;
	  t    = B[0];
	  for(i = 0;i < q;i++){
	    if((a = sqrt(A[i] * A[i] + B[i] * B[i])) == 0.0){//振幅
	      t = B[i + 1];
	      continue;
	    }
	    j     =  i + 1;
	    c     =  A[i] /  a;//cos
	    s     =  B[i] /  a;//sin
	    A[i]  =  a;
	    B[i]  =  t * c + A[j] * s;
	    A[j]  = -t * s + A[j] * c;
	    Q[i] *=  c;
	    R[i]  =  s;
	    Q[j]  =  c;
	    t     =  c * B[j];//一時避難
	  }

          //A = RQ
          A[0]  =  A[0] * Q[0] + B[0] * R[0];
	  for(i = 1;i < m;i++){
	    j    = i - 1;
	    B[j] = A[i] * R[j];
	    A[i] = A[i] * Q[i] + B[i] * R[i];  
	  }
          
	  for(i = 0;i <  m;i++){
	    A[i] += z;//シフト修正
	  }
	  e = fabs(e - B[p]);
	  if( fabs(d - e)  <=  1e-17  * fabs(A[q])){//1e-17
	    break;
	  }
	  d = e;//以前の非対角要素
	}
      }
    }else{
      R = B + n;
      for(m = n;m >= 2;m--){
	p = m - 2;
	q = m - 1;
	d =   0.0;
	for(e = B[p];fabs(e) > 1e-17;e = B[p]){//1e-17
	  s = (A[p] + A[q]) * 0.5;
	  c =  A[p] * A[q]  - B[p] * B[p];
	  c =  s * s  - c;
	  if(c <=  0.0){
	    z = s;
	  }else{
	    a = sqrt(c);
	    c = s + a;
	    s = s - a;
	    z = (fabs(c - A[q]) < fabs(s - A[q])) ? c : s;
	  }
	  for(i = 0;i < m;i++){
	    A[i] -= z;
	  }
	  for(j = 0;j < n;j++){
	    Q[j * n + j] = 1.0;
	    for(i = j + 1;i < n;i++){
	      Q[j * n + i] = Q[i * n + j] = 0.0;
	    }
	  }
	      t = B[0];
	  for(i = 0;i < q;i++){
	    if((a = sqrt(A[i] * A[i] + B[i] * B[i])) == 0.0){
	      t = B[j];
	      continue;
	    }
	    j     =  i + 1;
	    c     =  A[i] /  a;
	    s     =  B[i] /  a;
	    A[i]  =  a;
	    B[i]  =  t * c + A[j] * s;
	    A[j]  = -t * s + A[j] * c;
	    for(k = 0;k < j;k++){
	      Q[k * n + j] = -Q[k * n + i] * s;
	      Q[k * n + i] =  Q[k * n + i] * c;
	    }
	    Q[j * n + i] = s;
	    Q[j * n + j] = c;
	    t   =   c * B[j];
	  }
	  A[0]  =  A[0] * Q[0]  + B[0] * Q[n];
	  for(i = 1;i < q;i++){
	    j    = i - 1;
	    B[j] = A[i] * Q[i * n + j];
	    A[i] = A[i] * Q[i * n + i] + B[i] * Q[(i + 1) * n + i];
	  }
	  B[p]   = A[q] * Q[q * n + p];
	  A[q]   = A[q] * Q[q * n + q];
	  for(i = 0;i <  m;i++){
	    A[i] += z;
	  }
	  if(m == n){
	    for(j = 0;j < n;j++){
	      for(i = 0;i < m;i++){
		R[i] = 0.0;
		for(k = 0;k < n;k++){
		  R[i] += P[j * n + k] * Q[k * n + i];
		}
	      }
	      for(i = 0;i < m;i++){
		P[j * n + i] = R[i];
	      }
	    }
	  }else{
	    for(j = 0;j < n;j++){
	      for(i = 0;i < m;i++){
		R[i] = 0.0;
		l  = i + 2;
		for(k = 0;k < l;k++){
		  R[i] += P[j * n + k] * Q[k * n + i];
		}
	      }
	      for(i = 0;i < m;i++){
		P[j * n + i] = R[i];
	      }
	    }
	  }
	  e = fabs(e - B[p]);
	  if( fabs(d - e) <= 1e-17 * fabs(A[q])){//1e-17
	    break;
	  }
	  d = e;
	}
      }
      free(Q);
    }
  }
  z  = 0.0;
  for(i = 0;i < n;i++){
    z += fabs(A[i]);
  }
  z *= 1e-10;
  r  = n;
  for(i = 0;i < n;i++){
    if(fabs(A[i]) <= z){
      r--;
    }
  }
  if(P == NULL){
    for(i = 0;i < n - 1;i++){
      for(j = i + 1;j < n;j++){
	if(fabs(A[i]) < fabs(A[j])){
	  a    = A[i];
	  A[i] = A[j];
	  A[j] = a;
	}
      }
    }
  }else{
    for(i = 0;i < n - 1;i++){
      for(j = i + 1;j < n;j++){
	if(fabs(A[i]) < fabs(A[j])){
	  a    = A[i];
	  A[i] = A[j];
	  A[j] = a;
	  for(k = 0;k < n;k++){
	    a            = P[k * n + i];
	    P[k * n + i] = P[k * n + j];
	    P[k * n + j] = a;
	  }
	}
      }
    }
  }
  for(i = 1;i < n;i++){
      A[i * n + i] = A[i];
  }
  for(j = 0;j < n;j++){
    for(i = j + 1;i < n;i++){
      A[i * n + j] = A[j * n + i] = 0.0;
    }
  } 
  return r;
}

int la_svd(double *A,double *U,double *V,int row,int col){
  int     n = row;
  int     m = col;
  int     i,j,k,r;
  double *S;
  double  a;
  RANDOM  rnd;

  RANDOM__INITIALIZE_SEED(&rnd,clock());

  if((A == NULL) || (U == NULL) || (V == NULL)){
    return -1;
  }
  if((n <=    0) || (m <=    0)){
    return -1;
  }
  if((S = (double*)malloc(sizeof(double) * m * m)) == NULL){
    return -1;
  }
  for(j = 0;j < m;j++){
      S[j * m + j] = 0.0;
      for(k = 0;k < n;k++){
        S[j * m + j] += A[k * m + j] * A[k * m + j];
      }
    for(i = j + 1;i < m;i++){
      S[i * m + j] = 0.0;
      for(k = 0;k < n;k++){
	S[i * m + j] += A[k * m + i] * A[k * m + j];
      }
      S[j * m + i] = S[i * m + j];
    }
  }
  r = la_eig(S,V,m);
  if(r == -1){
    free(S);
    return -1;
  }
  for(j = 0;j < r;j++){
      S[j * m + j] = sqrt(S[j * m + j]);
  }
  for(j = 0;j < n;j++){
    for(i = 0;i < r;i++){
      U[j * n + i]  = 0.0;
      for(k = 0;k < m;k++){
	U[j * n + i] += A[j * m + k] * V[k * m + i];
      }
      U[j * n + i] /= S[i * m + i];
    }
    for(i = r;i < n;i++){
      U[j * n + i] = 0.0;
    }
  }
  for(i = r;i < n;i++){
    for(j = 0;j < n;j++){
      U[j * n + i] = RANDOM__NORMAL(&rnd,0.0,1.0);
    }
    for(j = 0;j < i;j++){
      a = 0.0;
      for(k = 0;k < n;k++){
	a += U[k * n + i] * U[k * n + j];
      }
      for(k = 0;k < n;k++){
	U[k * n + i] -= a * U[k * n + j];
      }
      a = 0.0;
      for(k = 0;k < n;k++){
	a += U[k * n + i] * U[k * n + i];
      }
      a = sqrt(a);
      for(k = 0;k < n;k++){
	U[k * n + i] /= a;
      }
    }
  }
  for(j = 0;j < n;j++){
    for(i = 0;i < m;i++){
      A[j * m + i] = 0.0;
    }
  }
  for(j = 0;j < r;j++){
      A[j * m + j] = S[j * m + j];
  }
  free(S);
  return r;
}

int  la_pca(double X[],int n,int m,double M[],double P[],double L[],int mode){
  int     i,j,k,r;
  double  t;
  double *R;
  double *T;

  if((X == NULL) || (P == NULL)){
    return -1;
  }
  if((n <=    0) || (m <=    0)){
    return -1;
  }
  R = (double*)malloc(sizeof(double) * (m * m + m));
  if( R == NULL){
    return -1;
  }
  T = R + m * m;
  if( M != NULL){
    for(i = 0;i < m;i++){
      t = 0.0;
      for(j = 0;j < n;j++){
	t += X[j * m + i];
      }
      M[i] = t / (double)n;
    }
    for(j = 0;j < n;j++){
      for(i = 0;i < m;i++){
	X[j * m + i] -= M[i];
      }
    }
  }
  for(i = 0;i < m;i++){
    t = 0.0;
    for(k = 0;k < n;k++){
      t += X[k * m + i] * X[k * m + i];
    }
    R[i * m + i] = t / (double)n;
    for(j = i + 1;j < m;j++){
      t = 0.0;
      for(k = 0;k < n;k++){
	t += X[k * m + i] * X[k * m + j];
      }
      R[i * m + j] = R[j * m + i] = t / (double)n;
    }
  }
  r = la_eig(R,P,m);
  if( r == -1){
    free(R);
    return -1;
  }
  if( L != NULL){
    for(i = 0;i < m;i++){
      L[i] = R[i * m + i];
    }
  }
  if(mode ==  0){
    for(j = 0;j < n;j++){
      for(i = 0;i < m;i++){
	T[i] = 0.0;
	for(k = 0;k < m;k++){
	  T[i] += X[j * m + k] * P[k * m + i];
	}
      }
      for(i = 0;i < m;i++){
	X[j * m + i] = T[i];
      }
    }
  }else{
    for(i = 0;i < r;i++){
      R[i * m + i] = sqrt(R[i * m + i]);
    }
    for(j = 0;j < n;j++){
      for(i = 0;i < r;i++){
	T[i] = 0.0;
	for(k = 0;k < m;k++){
	  T[i] += X[j * m + k] * P[k * m + i];
	}
      }
      for(i = 0;i < r;i++){
	X[j * m + i]  =   T[i] / R[i * m + i];
      }
      for(i = r;i < m;i++){
	X[j * m + i] = 0.0;
      }
    }
    for(j = 0;j < m;j++){
      for(i = 0;i < r;i++){
	P[j * m + i]  *= R[i * m + i];
      }
      for(i = r;i < m;i++){
	P[j * m + i]   = 0.0; 
      }
    }
  }
  free(R);
  return r;
}

int  la_ica(double X[],int n,int m,double M[],double P[]){
  int     i,j,k,c;
  double *W;
  double *V;
  double *Q;
  double *e;
  double  t,g,a,s;
  
  c = 3 * m * m + m;
  if((W = (double*)malloc(sizeof(double) * c)) == NULL){
    return -1;
  }
  a = 1.0 / sqrt((double)m);
  V = W + m * m;
  Q = V + m * m;
  e = Q + m * m;
  if(la_pca(X,n,m,M,V,NULL,1) == -1){
    free(W);
    return -1;
  }
  for(j = 0;j < m;j++){
    W[j * m + j] = 1.0;
    for(i = j + 1;i < m;i++){
      W[i * m + j] = W[j * m + i] = 0.0;
    }
  }
  for(c = 0;c < 500;c++){
    for(i = 0;i < m;i++){
      for(j = 0;j < m;j++){
	e[j] = 0.0;
      }
      g = 0.0;
      for(j = 0;j < n;j++){
	t = 0.0;
	for(k = 0;k < m;k++){
	  t    += W[k * m + i] * X[j * m + k];
	}
	s  = t * t * t;
	for(k = 0;k < m;k++){
	  e[k] += X[j * m + k] * s;
	}
	g += t * t * 3.0;
      }
      for(j = 0;j < m;j++){
	e[j] /= (double)n;
      }
           g /= (double)n;
      for(j = 0;j < m;j++){
	W[j * m + i] = e[j] - g * W[j * m + i];
      }
    }
    la_pca(W,m,m,NULL,Q,NULL,1);
    for(j = 0;j < m;j++){
      for(i = 0;i < m;i++){
	W[j * m + i] *= a;
      }
    }
  }
  for(j = 0;j < n;j++){
    for(i = 0;i < m;i++){
      e[i] = 0.0;
      for(k = 0;k < m;k++){
	e[i] += X[j * m + k] * W[k * m + i];
      }
    }
    for(i = 0;i < m;i++){
      X[j * m + i] = e[i];
    }
  }
  for(j = 0;j < m;j++){
    for(i = 0;i < m;i++){
      P[j * m + i] = 0.0;
      for(k = 0;k < m;k++){
	P[j * m + i] += V[j * m + k] * W[k * m + i];
      }
    }
  }
  free(W);
  return 0;
}
