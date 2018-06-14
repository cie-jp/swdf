/***************************************************************** 
1;95;0c *
 * Simplex法
 *
 *
 *                           Created  by Mamoru Ota (2018/03/09)
 * 
 *****************************************************************/

#include"SIMPLEX.h"
#include"LINEAR_ALGEBRA.h"

int simplex_phase1(double c[],double *A,double b[],int T[],int row,int col,double eps,int is_nonnegative){
  int     n = row;
  int     m = col;
  int     l = m - n;
  int     size;
  double *B,*BT,*N;
  double *bb,*cB,*cN,*c0,*as,*ab;
  int     s,r,buf;
  double  min,max,tmp;
  double  w,w_tmp;
  int     idx1;
  int     idx2;
  int     i, j;
  
  if((c == NULL) || (A == NULL) || (b == NULL) || (T == NULL) || (row < 1) || (col < 1) || (eps < 0.0)){
    fprintf(stderr,"Error : simplex_phase1 - Invalid argument.");
    return -1;
  }
  size = sizeof(double) * (2 * n * n + n * l + 5 * n + l);
  if((B = (double*)malloc(size)) == NULL){
    fprintf(stderr,"Error : simplex_phase1 - Can't allocate memory.");
    return -1;
  }
  memset(B,0x00,size);  
  BT    = B  + n * n;
  N     = BT + n * n;
  bb    = N  + n * l;
  cB    = bb + n;
  cN    = cB + n;
  c0    = cN + l;
  as    = c0 + n;
  ab    = as + n;  
  w_tmp = DBL_MAX;
  w     = 0.0;
  while(1){
    for(i = 0;i < m;i++){
      if(T[i] < n){
	for(j = 0;j < n;j++){
	  B[j * n + T[i]]     = A[j * m + i];
	 BT[T[i] * n + j]     = A[j * m + i];
	}
	cB[T[i]]     = c[i];
      }else{
	for(j = 0;j < n;j++){
	  N[j * l + T[i] - n] = A[j * m + i];
	}
	cN[T[i] - n] = c[i];
      }
    }
    if(la_solve(c0,BT,cB,n) == -1){
      free(B);
      return -1;
    }
    for(j = 0;j < l;j++){
      for(i = 0;i < n;i++){
	cN[j] -= N[i * l + j] * c0[i];
      }
    }
    if(la_solve(bb,B ,b ,n) == -1){
      free(B);
      return -1;
    }
    w = 0.0;
    for(i = 0;i < m;i++){
      if(T[i] < n){
	w += c[i] * bb[T[i]];
      }
    }
    if((w_tmp <= w) || (w == 0.0)){
      break;
    }
    w_tmp = w;
    min   = cN[0];
    s     = 0;
    for(j = 1;j < l;j++){
      if(min > cN[j]){
	 min = cN[j];
	 s   = j;
      }
    }
    if(min >= 0.0){  
      break;
    }
    buf = 0;
    for(i = 0;i < m;i++){
      if((s + n) == T[i]){
	buf = i;
	break;
      }
    }
    s = buf;
    for(j = 0;j < n;j++){
      as[j] = A[j * m + s];
    }  
    if(la_solve(ab,B ,as,n) == -1){
      free(B);
      return -1;
    }
    max = 0.0;
    r   = 0;
    for(j = 0;j < n;j++){
      if(max < ab[j]){
	 max = ab[j];
	 r   = j;
      }
    }
    if(max <= 0.0){
      free(B);
      fprintf(stderr,"Error : simplex_phase1 - This problem is unbounded.");
      return -1;
    }
    min = bb[r] / ab[r];
    for(j = 0;j < n;j++){
      if(ab[j] <= 0.0){
	continue;
      }
      tmp = bb[j] / ab[j];
      if(min > tmp){
	 min = tmp;
	 r   = j;
      }
    }
    buf = 0;
    for(i = 0;i < m;i++){
      if(r == T[i]){
	buf = i;
	break;
      }
    }
    r = buf;
    buf   = T[s];
    T[s]  = T[r];
    T[r]  = buf ;  
  }
  idx1 = 0;
  for(i = 0;i < l;i++){
    if(T[i] < n){
       T[i] = idx1++;
    }
  }
  idx2 = idx1;
  if(!is_nonnegative){ 
    for(i = 0;i < l;i++){
      if((T[i] < idx1) && (T[i] != -1)){
	if( i < l / 2){
	  T[i + l / 2] = -1;
	}else{
	  T[i - l / 2] = -1;
	}
      }
    }
    for(i = 0;i < l;i++){
      if(T[i] >= idx1){
	 T[i]  = idx2++;
      }
    }    
    for(i = 0;i < l;i++){
      if(T[i] == -1){
	 T[i]  = idx2++;
      }
    }
  }else{
    for(i = 0;i < l;i++){
      if(T[i] >= idx1){
	 T[i]  = idx2++;
      }
    }
  }
  for(i = l;i < m;i++){
    T[i] = idx2++;
  }
  free(B);
  if(w >= eps){
    fprintf(stderr,"Error : simplex_phase1 - This problem has no solution.");
    return -1;
  }
  return 0;
}

int simplex_phase2(double x[],double c[],double *A,double b[],int T[],int row,int col){
  int     n = row;
  int     m = col;
  int     l = m - n;
  int     size;
  double *B,*BT,*N;
  double *bb,*cB,*cN,*c0,*as,*ab;
  int     s,r,buf;
  double  min,max,tmp;
  double  w,w_tmp;
  int     i, j;
  
  if((x == NULL) || (c == NULL) || (A == NULL) || (b == NULL) || (T == NULL) || (row < 1) || (col < 1)){
    fprintf(stderr,"Error : simplex_phase2 - Invalid argument.");
    return -1;
  }
  size = sizeof(double) * (2 * n * n + n * l + 5 * n + l);
  if((B = (double*)malloc(size)) == NULL){
    fprintf(stderr,"Error : simplex_phase2 - Can't allocate memory.");
    return -1;
  }
  memset(B,0x00,size);  
  BT    = B  + n * n;
  N     = BT + n * n;
  bb    = N  + n * l;
  cB    = bb + n;
  cN    = cB + n;
  c0    = cN + l;
  as    = c0 + n;
  ab    = as + n;  
  w_tmp = DBL_MAX;
  w     = 0.0;
  while(1){
    for(i = 0;i < m;i++){
      if(T[i] < n){
	for(j = 0;j < n;j++){
	  B[j * n + T[i]]     = A[j * m + i];
	 BT[T[i] * n + j]     = A[j * m + i];
	}
	cB[T[i]]     = c[i];
      }else{
	for(j = 0;j < n;j++){
	  N[j * l + T[i] - n] = A[j * m + i];
	}
	cN[T[i] - n] = c[i];
      }
    }
    if(la_solve(c0,BT,cB,n) == -1){
      free(B);
      return -1;
    }
    for(j = 0;j < l;j++){
      for(i = 0;i < n;i++){
	cN[j] -= N[i * l + j] * c0[i];
      }
    }
    if(la_solve(bb,B ,b ,n) == -1){
      free(B);
      return -1;
    }
    w = 0.0;
    for(i = 0;i < m;i++){
      if(T[i] < n){
	w += c[i] * bb[T[i]];
      }
    }
    if((w_tmp <= w) || (w == 0.0)){
      break;
    }
    w_tmp = w;
    min   = cN[0];
    s     = 0;
    for(j = 1;j < l;j++){
      if(min > cN[j]){
	 min = cN[j];
	 s   = j;
      }
    }
    if(min >= 0.0){
      break;
    }
    buf = 0;
    for(i = 0;i < m;i++){
      if((s + n) == T[i]){
	buf = i;
	break;
      }
    }
    s = buf;
    for(j = 0;j < n;j++){
      as[j] = A[j * m + s];
    }  
    if(la_solve(ab,B ,as,n) == -1){
      free(B);
      return -1;
    }
    max = 0.0;
    r   = 0;
    for(j = 0;j < n;j++){
      if(max < ab[j]){
	 max = ab[j];
	 r   = j;
      }
    }
    if(max <= 0.0){
      free(B);
      fprintf(stderr,"Error : simplex_phase2 - This problem is unbounded.");
      return -1;
    }
    min = bb[r] / ab[r];
    for(j = 0;j < n;j++){
      if(ab[j] <= 0.0){
	continue;
      }
      tmp = bb[j] / ab[j];
      if(min > tmp){
	 min = tmp;
	 r   = j;
      }
    }
    buf = 0;
    for(i = 0;i < m;i++){
      if(r == T[i]){
	buf = i;
	break;
      }
    }
    r = buf;
    buf   = T[s];
    T[s]  = T[r];
    T[r]  = buf ;  
  }
  for(i = 0;i < m;i++){
    x[i] = (T[i] < n) ? bb[T[i]] : 0.0;
  }  
  free(B);
  return 0;
}

int reviced_simplex0(double x[],double c[],double *A,double b[],int row,int col,int is_nonnegative){
  int      n = row;  
  int      m = col + row;
  int      l = m - n;
  int     *T;
  double  *_c,*_A,*_b;
  int      size;
  int      i, j;
  
  if((x == NULL) || (c == NULL) || (A == NULL) || (b == NULL) || (row < 1) || (col < 1)){
    fprintf(stderr,"Error : reviced_simplex0 - Invalid argument.\n");
    return -1;
  }
  size = sizeof(int) * m + sizeof(double) * (m + n * m + n);
  if((T = (int*)malloc(size)) == NULL){
    fprintf(stderr,"Error : reviced_simplex0 - Can't allocate memory.\n");
    return -1;
  }
  memset(T,0x00,size);  
  _c = (double*)(T + m);
  _A = _c + m;
  _b = _A + n * m;
  for(i = 0;i < l;i++){
    T[i] = i + n;
  }
  for(i = 0;i < n;i++){
    T[i + l] = i;
  }
  for(j = 0;j < n;j++){
    if(b[j] >= 0.0){
      for(i = 0;i < l;i++){
	_A[j * m + i] = +A[j * l + i];
      }
      _b[j] = +b[j];
    }else{
      for(i = 0;i < l;i++){
	_A[j * m + i] = -A[j * l + i];
      }
      _b[j] = -b[j];
    }
    _A[j * m + j + l] = 1.0;
    _c[j + l]         = 1.0;
  }  
  if(simplex_phase1(_c,_A,_b,T,n,m,1e-10,is_nonnegative) == -1){
    free(T);
    return -1;
  }
  for(j = 0;j < n;j++){
    if(b[j] >= 0.0){
      for(i = 0;i < l;i++){
	_A[j * l + i] = +A[j * l + i];
      }
    }else{
      for(i = 0;i < l;i++){
	_A[j * l + i] = -A[j * l + i];
      }
    }
  } 
  if(simplex_phase2(x,c,_A,_b,T,n,l) == -1){
    free(T);
    return -1;
  }
  free(T);
  return 0;
}

int reviced_simplex1(double x[],double c[],double *A,double b[],int row,int col){
  return reviced_simplex0(x,c,A,b,row,col,1);
}

int reviced_simplex2(double x[],double c[],double *A,double b[],int row,int col){
  int      n  = row;  
  int      m  = col;
  int      m2 = col * 2;
  double *_x,*_c,*_A;
  int      size;
  int      i, j;
  
  if((x == NULL) || (c == NULL) || (A == NULL) || (b == NULL) || (row < 1) || (col < 1)){
    fprintf(stderr,"Error : reviced_simplex2 - Invalid argument.\n");
    return -1;
  }
  size = sizeof(double) * (2 * m2 + n * m2);
  if((_x = (double*)malloc(size)) == NULL){
    fprintf(stderr,"Error : reviced_simplex2 - Can't allocate memory.\n");
    return -1;
  }
  memset(_x,0x00,size);
  _c = _x + m2;
  _A = _c + m2;
  for(j = 0;j < m;j++){
    _c[j] = _c[j + m] = c[j];
  }
  for(j = 0;j < n;j++){
    for(i = 0;i < m;i++){
      _A[j * m2 + i]     = +A[j * m + i];
      _A[j * m2 + i + m] = -A[j * m + i];
    }
  }
  if(reviced_simplex0(_x,_c,_A,b,n,m2,0) == -1){
    free( _x);
    return -1;
  }
  for(j = 0;j < m;j++){
    x[j] = _x[j] - _x[j + m];
  }
  free(_x);
  return 0;
}
