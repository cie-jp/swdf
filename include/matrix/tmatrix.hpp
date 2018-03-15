#include<iostream>
#include<cmath>
#include"tmatrix.h"

using namespace std;

template<typename TYPE>
int LU_decomposition(TYPE *A,int P[],int n){
  int  i,j,k;
  int  buf,l;
  TYPE max,tmp;

  //引数チェック
  if((A == NULL) || (P == NULL) || (n < 1)){
    cerr << "Error : LU_decomposition - Invalid argument." << endl;
    return -1;
  }
  //置換行列の初期化
  for(i = 0;i < n;i++){
    P[i] = i;
  }
  //LU分解
  for(k = 0;k < n - 1;k++){
    //Pivot選択
    max = fabs<TYPE>(A[k * n + k]);
    l   = k;
    for(j = k + 1;j < n;j++){
      tmp = fabs<TYPE>(A[j * n + k]);
      if(tmp > max){
	 max = tmp;
	 l   = j;
      }
    }
    //行の交換
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
    //行列の更新
    for(j = k + 1;j < n;j++){
      tmp = A[k * n + k];
      if(tmp == 0.0){
	cerr << "Error : LU_decomposition - Division by zero." << endl;
	return -1;
      }
      tmp = A[j * n + k] / tmp;      
      A[j * n + k] = tmp;
      for(i = k + 1;i < n;i++){
	A[j * n + i] = fma<TYPE>(-tmp,A[k * n + i],A[j * n + i]);
      }
    }
  }
  return 0;
}

template<typename TYPE>
int inv(TYPE *A,int n){
  int     i,j,k,c;
  int    *P;
  TYPE   *LU_inv;
  TYPE    tmp,dj;

  //引数チェック
  if((A == NULL) || (n < 1)){
    cerr << "Error : inv - Invalid argument." << endl;
    return -1;
  }
  //メモリの確保と初期化
  c = sizeof(int) * n + sizeof(TYPE) * n * n;
  if((P = (int*)malloc(c)) == NULL){
    cerr << "Error : inv - Can't allocate memory." << endl;
    return -1;
  }
  memset(P,0x00,c);
  LU_inv = (TYPE*)(P + n);
  //LU分解
  if(LU_decomposition<TYPE>(A,P,n) == -1){
    free(P);
    return -1;
  }
  //Lの逆行列の計算
  for(int j = 1;j < n;j++){
    for(int k = 0;k < j;k++){
      tmp = -A[j * n + k];
      for(int i = 0;i < k;i++){
	LU_inv[j * n + i] = fma<TYPE>(tmp,LU_inv[k * n + i],LU_inv[j * n + i]);
      }
      LU_inv[j * n + k] += tmp;
    }
  }
  //Uの逆行列の計算
  LU_inv[(n - 1) * n + (n - 1)] = 1.0 / A[(n - 1) * n + (n - 1)];
  for(int j = n - 2;j >= 0;j--){
    dj = A[j * n + j];
    if(dj == 0.0){
      cerr << "Error : inv - Division by zero." << endl;
      return -1;
    }
    dj = 1.0 / dj;
    LU_inv[j * n + j] =  dj;
    for(int k = j + 1;k < n;k++){
      tmp = -A[j * n + k] * dj;
      for(int i = k;i < n;i++){
	LU_inv[j * n + i] = fma<TYPE>(tmp,LU_inv[k * n + i],LU_inv[j * n + i]);
      }
    }
  }
  //Aの逆行列の計算
  for(j = 0;j < n;j++){
    for(i = 0;i < j;i++){
      tmp = 0.0;
      for(k = j;k < n;k++){
	tmp = fma<TYPE>(LU_inv[j * n + k],LU_inv[k * n + i],tmp);
      }
      A[j * n + P[i]] = tmp;
    }
    for(i = j;i < n;i++){
      tmp = LU_inv[j * n + i];
      for(k = i + 1;k < n;k++){
	tmp = fma<TYPE>(LU_inv[j * n + k],LU_inv[k * n + i],tmp);
      }
      A[j * n + P[i]] = tmp;
    }    
  }
  free(P);
  return 0;
}

template<typename TYPE>
int solve(TYPE x[],TYPE *A,TYPE b[],int n){
  int   i,j,c;
  int  *P;
  TYPE *y;
  TYPE *LU;
  TYPE  tmp;

  //引数チェック
  if((x == NULL) || (A == NULL) || (b == NULL) || (n < 1)){
    cerr << "Error : solve - Invalid argument." << endl;
    return -1;
  }
  //メモリの確保と初期化
  c = sizeof(int) * n + sizeof(TYPE) * (n + n * n);
  if((P = (int*)malloc(c)) == NULL){
    cerr << "Error : solve - Can't allocate memory." << endl;
    return -1;
  }
  y  = (TYPE*)(P + n);
  LU = y + n;
  memcpy(LU,A,n * n * sizeof(TYPE));
  //LU分解
  if(LU_decomposition<TYPE>(LU,P,n) == -1){
    free(P);
    return -1;
  }
  //前進代入(Ly = b)
  y[0] = b[P[0]];
  for(i = 1;i < n;i++){
    tmp = b[P[i]];
    for(j = 0;j < i;j++){
      tmp = fma<TYPE>(-LU[i * n + j],y[j],tmp);
    }
    y[i] = tmp;
  }
  //後退代入(Ux = y)
  for(i = n - 1;i >= 0;i--){
    tmp = y[i];
    for(j = i + 1;j < n;j++){
      tmp = fma<TYPE>(-LU[i * n + j],x[j],tmp);
    }
    x[i] = tmp;
    tmp  = LU[i * n + i];
    if(tmp == 0.0){
      cerr << "Error : solve - Division by zero." << endl;
      return -1;
    }
    x[i] = x[i] / tmp;
  }
  free(P);
  return 0;
}

template<typename TYPE>
void Bidiagonalization(TMatrix<TYPE> A){
  TMatrix<TYPE> B(A.row(),A.col());
  TVector<TYPE> u(A.row());
  TVector<TYPE> v(A.col());
  TYPE          len,tmp;

  if(A.row() >= A.col()){
    for(int c = 0;c < A.col();c++){
      //対象となる列ベクトルuの取得
      for(int j = c;j < A.row();j++){
	u[j] = A[j][c];
      }
      //ノルムの計算
      len = 0.0;
      for(int j = c;j < A.row();j++){
	len = fma<TYPE>(u[j],u[j],len);
      }
      if(len == 0.0){
	B[c][c] = 0.0;
      }else{
	len = sqrt<TYPE>(len);
	tmp = sqrt<TYPE>(1.0 / (2.0 * len * (len + fabs<TYPE>(u[c]))));
	if(u[c] > 0.0){
	  B[c][c] = -len;
	  u[c]   -= -len;
	}else{
	  B[c][c] = +len;
	  u[c]   -= +len;
	}
	//規格化処理
	for(int j = c;j < A.row();j++){
	  u[j] *= tmp;
	}
	//v = A'uの計算
	for(int i = c + 1;i < A.col();i++){
	  tmp = 0.0;
	  for(int j = c;j < A.row();j++){
	    tmp = fma<TYPE>(A[j][i],u[j],tmp);
	  }
	  v[i] = tmp;
	}
	//A = A - 2uv'
	for(int j = c;j < A.row();j++){
	  for(int i = c + 1;i < A.col();i++){
	    A[j][i] = fma<TYPE>(-2.0 * u[j],v[i],A[j][i]);
	  }
	}
	//uの代入
	for(int j = c;j < A.row();j++){
	  A[j][c] = u[j];
	}
      }
      if(c + 1 >= A.col()){
	break;
      }
      //対象となる行ベクトルvの取得
      for(int i = c + 1;i < A.col();i++){
	v[i] = A[c][i];
      }
      //ノルムの計算
      len = 0.0;
      for(int i = c + 1;i < A.col();i++){
	len = fma<TYPE>(v[i],v[i],len);
      }
      if(len == 0.0){
	B[c][c + 1] = 0.0;
      }else{
	len = sqrt<TYPE>(len);
	tmp = sqrt<TYPE>(1.0 / (2.0 * len * (len + fabs<TYPE>(v[c + 1]))));
	if(v[c + 1] > 0.0){
	  B[c][c + 1] = -len;
	  v[c + 1]   -= -len;
	}else{
	  B[c][c + 1] = +len;
	  v[c + 1]   -= +len;
	}
	//規格化処理
	for(int i = c + 1;i < A.col();i++){
	  v[i] *= tmp;
	}
	//u = Avの計算
	for(int j = c + 1;j < A.row();j++){
	  tmp = 0.0;
	  for(int i = c + 1;i < A.col();i++){
	    tmp = fma<TYPE>(A[j][i],v[i],tmp);
	  }
	  u[j] = tmp;
	}
	//A = A - 2uv'
	for(int j = c + 1;j < A.row();j++){
	  for(int i = c + 1;i < A.col();i++){
	    A[j][i] = fma<TYPE>(-2.0 * u[j],v[i],A[j][i]);
	  }
	}
	//vの代入
	for(int i = c + 1;i < A.col();i++){
	  A[c][i] = v[i];
	}
      }
    }
  }else{
    for(int c = 0;c < A.col();c++){
      //対象となる行ベクトルvの取得
      for(int i = c;i < A.col();i++){
	v[i] = A[c][i];
      }
      //ノルムの計算
      len = 0.0;
      for(int i = c;i < A.col();i++){
	len = fma<TYPE>(v[i],v[i],len);
      }
      if(len == 0.0){
	B[c][c] = 0.0;
      }else{
	len = sqrt<TYPE>(len);
	tmp = sqrt<TYPE>(1.0 / (2.0 * len * (len + fabs<TYPE>(v[c]))));
	if(v[c] > 0.0){
	  B[c][c] = -len;
	  v[c]   -= -len;
	}else{
	  B[c][c] = +len;
	  v[c]   -= +len;
	}
	//規格化処理
	for(int i = c;i < A.col();i++){
	  v[i] *= tmp;
	}
	//u = Avの計算
	for(int j = c + 1;j < A.row();j++){
	  tmp = 0.0;
	  for(int i = c;i < A.col();i++){
	    tmp = fma<TYPE>(A[j][i],v[i],tmp);
	  }
	  u[j] = tmp;
	}
	//A = A - 2uv'
	for(int j = c + 1;j < A.row();j++){
	  for(int i = c;i < A.col();i++){
	    A[j][i] = fma<TYPE>(-2.0 * u[j],v[i],A[j][i]);
	  }
	}
	//vの代入
	for(int i = c;i < A.col();i++){
	  A[c][i] = v[i];
	}
      }
      if(c + 1 >= A.row()){
	break;
      }
      //対象となる列ベクトルuの取得
      for(int j = c + 1;j < A.row();j++){
	u[j] = A[j][c];
      }
      //ノルムの計算
      len = 0.0;
      for(int j = c + 1;j < A.row();j++){
	len = fma<TYPE>(u[j],u[j],len);
      }
      if(len == 0.0){
	B[c][c + 1] = 0.0;
      }else{
	len = sqrt<TYPE>(len);
	tmp = sqrt<TYPE>(1.0 / (2.0 * len * (len + fabs<TYPE>(u[c + 1]))));
	if(u[c + 1] > 0.0){
	  B[c + 1][c] = -len;
	  u[c + 1]   -= -len;
	}else{
	  B[c + 1][c] = +len;
	  u[c + 1]   -= +len;
	}
	//規格化処理
	for(int j = c + 1;j < A.row();j++){
	  u[j] *= tmp;
	}
	//v = A'uの計算
	for(int i = c + 1;i < A.col();i++){
	  tmp = 0.0;
	  for(int j = c + 1;j < A.row();j++){
	    tmp = fma<TYPE>(A[j][i],u[j],tmp);
	  }
	  v[i] = tmp;
	}
	//A = A - 2uv'
	for(int j = c + 1;j < A.row();j++){
	  for(int i = c + 1;i < A.col();i++){
	    A[j][i] = fma<TYPE>(-2.0 * u[j],v[i],A[j][i]);
	  }
	}
	//uの代入
	for(int j = c + 1;j < A.row();j++){
	  A[j][c] = u[j];
	}
      }
    }    
  }
  cerr << A << endl;
  cerr << B << endl;
  cerr << B * ~B << endl;
  cerr << ~B * B << endl;
  //cerr << (B * ~B).trace() << endl;
  for(int i = 0;i < A.row();i++){
    if(i + 1 != A.row()){
      cerr << (B[i][i] * B[i][i] + B[i + 1][i] * B[i + 1][i]) << endl;
    }else{
      cerr << (B[i][i] * B[i][i]) << endl;
    }
  }
  for(int i = 0;i < A.row() - 1;i++){
    cerr << (B[i + 1][i] * B[i + 1][i + 1]) << endl;
  }
  getchar();
}

template<typename TYPE> 
TMatrix<TYPE>::TMatrix(int dim){
  if(dim <= 0){
    cerr << "Error : TMatrix.TMatrix(int)"     << endl;
    exit(EXIT_FAILURE);
  }
  W = dim;
  H = dim;
  D = new TYPE[W * H];
  memset(D,0x00,sizeof(TYPE) * W * H);
}

template<typename TYPE> 
TMatrix<TYPE>::TMatrix(int row, int col){
  if(col <= 0 || row <= 0){
    cerr << "Error : TMatrix.TMatrix(int,int)" << endl;
    exit(EXIT_FAILURE);
  }
  W = col;
  H = row;
  D = new TYPE[W * H];
  memset(D,0x00,sizeof(TYPE) * W * H);
}

template<typename TYPE> 
TMatrix<TYPE>::TMatrix(const TMatrix<TYPE> &A){
  W = A.W;
  H = A.H;
  D = new TYPE[W * H];
  memcpy(D, A.D,W * H * sizeof(TYPE));
}

template<typename TYPE> 
TMatrix<TYPE>::~TMatrix(){
  delete [] D;
}

template<typename TYPE> 
TYPE *TMatrix<TYPE>::ptr()const{
  return D;
}

template<typename TYPE> 
int   TMatrix<TYPE>::col()const{
  return W;
}

template<typename TYPE> 
int   TMatrix<TYPE>::row()const{
  return H;
}

template<typename TYPE> 
TMatrix<TYPE>::operator TYPE(){
  if((W != 1) || (H != 1)){
    cerr << "Error : TMatrix.cast" << endl;
    exit(EXIT_FAILURE);
  }  
  return D[0];
}

template<typename TYPE> 
TMatrix<TYPE> &TMatrix<TYPE>::operator  =(const TMatrix<TYPE> &A){
  if(W != A.W || H != A.H){ 
    delete [] D;
    W = A.W;
    H = A.H;
    D = new TYPE[W * H];
  }
  memcpy(D,A.D,W * H * sizeof(TYPE));
  return *this;
}

template<typename TYPE> 
TYPE          *TMatrix<TYPE>::operator [](const int n)const{
  return D + n * W;
}

template<typename TYPE> 
TMatrix<TYPE> &TMatrix<TYPE>::operator +=(const TMatrix<TYPE> &A){
  return *this = *this + A;
}

template<typename TYPE> 
TMatrix<TYPE> &TMatrix<TYPE>::operator -=(const TMatrix<TYPE> &A){
  return *this = *this - A;
}

template<typename TYPE> 
TMatrix<TYPE> &TMatrix<TYPE>::operator +=(const TYPE k){
  return *this = *this + k;
}

template<typename TYPE> 
TMatrix<TYPE> &TMatrix<TYPE>::operator -=(const TYPE k){
  return *this = *this - k;
}

template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator *=(const TMatrix<TYPE> &A){
  return *this = *this * A;
}

template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator *=(const TYPE k){
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      D[j * W + i] *= k;
    }
  }
  return *this;
}

template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator /=(const TMatrix<TYPE> &A){
  if((A.W != 1) || (A.H != 1)){
    cerr << "Error : TMatrix./=(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return *this = *this / A.D[0];
}

template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator /=(const TYPE k){
  TYPE k_inv;
  k_inv = 1.0 / k;
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      D[j * W + i] *= k_inv;
    }
  }
  return *this;
}

template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator &=(const TMatrix<TYPE> &A){
  return *this = *this & A;
}

template<typename TYPE>
TMatrix<TYPE> &TMatrix<TYPE>::operator |=(const TMatrix<TYPE> &A){
  return *this = *this | A;
}

template<typename TYPE>
TMatrix<TYPE>  operator ~(const TMatrix<TYPE> &A){
  TMatrix<TYPE> B(A.W,A.H);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[i * B.W + j] = A.D[j * A.W + i];
    }
  }
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator !(const TMatrix<TYPE> &A){
  if(A.W != A.H){
    cerr << "Error : TMatrix.!(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> B = A;
  if(inv(B.D,B.W) == -1){
    cerr << "Error : TMatrix.!(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator +(const TMatrix<TYPE> &A){
  return A;
}

template<typename TYPE>
TMatrix<TYPE>  operator -(const TMatrix<TYPE> &A){
  TMatrix<TYPE> B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = -A.D[j * A.W + i];
    }
  }
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator +(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if(A.W != B.W || A.H != B.H){
    cerr << "Error : TMatrix.+(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] + B.D[j * B.W + i];
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator -(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if(A.W != B.W || A.H != B.H){
    cerr << "Error : TMatrix.-(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] - B.D[j * B.W + i];
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator +(const TYPE k,const TMatrix<TYPE> &A){
  if((A.W != 1) || (A.H != 1)){
    cerr << "Error : TMatrix.+(Type,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> B(1,1);
  B.D[0] =  k + A.D[0];
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator +(const TMatrix<TYPE> &A,const TYPE k){
  return k + A;
}

template<typename TYPE>
TMatrix<TYPE>  operator -(const TYPE k,const TMatrix<TYPE> &A){
  if((A.W != 1) || (A.H != 1)){
    cerr << "Error : TMatrix.-(Type,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> B(1,1);
  B.D[0] =  k - A.D[0];
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator -(const TMatrix<TYPE> &A,const TYPE k){
  if((A.W != 1) || (A.H != 1)){
    cerr << "Error : TMatrix.-(TMatrix,Type)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> B(1,1);
  B.D[0] =  A.D[0] - k;
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator *(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if(A.W != B.H){
    if((A.W == 1) && (A.H == 1)){
      return A.D[0] * B;
    }
    if((B.W == 1) && (B.H == 1)){
      return A * B.D[0];
    }
    cerr << "Error : TMatrix.*(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,B.W);
  TYPE          tmp;
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < B.W;i++){
      tmp = 0.0;
      for(int k = 0;k < A.W;k++){
	//tmp = fma<TYPE>(A.D[j * A.W + k],B.D[k * B.W + i],tmp);
	tmp += A.D[j * A.W + k] * B.D[k * B.W + i];
      }
      C.D[j * C.W + i] = tmp;
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator *(const TYPE k,const TMatrix<TYPE> &A){
  TMatrix<TYPE> B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = k * A.D[j * A.W + i];
    }
  }
  return B;
}

template<typename TYPE>
TMatrix<TYPE>  operator *(const TMatrix<TYPE> &A,const TYPE k){
  return k * A;
}

template<typename TYPE>
TMatrix<TYPE>  operator %(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if((A.W != B.W) || (A.H != B.H)){
    cerr << "Error : TMatrix.%(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] * B.D[j * A.W + i];
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator /(const TMatrix<TYPE> &A,const TYPE k){
  return A * (1.0 / k);
}

template<typename TYPE>
TMatrix<TYPE>  operator /(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if((A.W != B.W) || (A.H != B.H)){
    if((B.W == 1) && (B.H == 1)){
      return A / B.D[0];
    }
    cerr << "Error : TMatrix./(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] / B.D[j * A.W + i];
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator &(const TMatrix<TYPE> &A,const int row){
  if((row < 0) || (A.H <= row)){
    cerr << "Error : TMatrix.&(TMatrix,int    )" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(1,A.W);
  for(int i = 0;i < A.W;i++){
    C.D[i] = A.D[row * A.W + i];
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator &(const int row,const TMatrix<TYPE> &A){
  return A & row;
}

template<typename TYPE>
TMatrix<TYPE>  operator &(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if(A.W != B.W){
    cerr << "Error : TMatrix.&(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H + B.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i]         = A.D[j * A.W + i];
    }
  }
  for(int j = 0;j < B.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[(j + A.H) * C.W + i] = B.D[j * B.W + i];
    }
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator |(const TMatrix<TYPE> &A,const int col){
  if((col < 0) || (A.W <= col)){
    cerr << "Error : TMatrix.|(TMatrix,int    )" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,1);
  for(int j = 0;j < A.H;j++){
    C.D[j] = A.D[j * A.W + col];
  }
  return C;
}

template<typename TYPE>
TMatrix<TYPE>  operator |(const int col,const TMatrix<TYPE> &A){
  return A | col;
}

template<typename TYPE>
TMatrix<TYPE>  operator |(const TMatrix<TYPE> &A,const TMatrix<TYPE> &B){
  if(A.H != B.H){
    cerr << "Error : TMatrix.|(TMatrix,TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> C(A.H,A.W + B.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i]       = A.D[j * A.W + i];
    }
  }
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < B.W;i++){
      C.D[j * C.W + i + A.W] = B.D[j * B.W + i];
    }
  }
  return C;
}

template<typename TYPE>
ostream &operator <<(ostream &os,const TMatrix<TYPE> &A){
  char buf[100];
  for(int i = 0;i < A.H;i++){
    os << "| "; 
    for(int j = 0;j < A.W;j++){
      if(A.D[i * A.W + j] >= 0.0){
	sprintf(buf,"+%10.5lf " ,+(double)A.D[i * A.W + j]);
      }else{
	sprintf(buf,"-%10.5lf " ,-(double)A.D[i * A.W + j]);
      }
      os << buf;
    }
    os << "|" << endl;
  }
  return os;
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::function(TYPE (*func)(TYPE)){
  TMatrix<TYPE> A(H,W);
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      A[j][i] = func(D[j * W + i]);
    }
  }  
  return A;
}


template<typename TYPE>
TYPE TMatrix<TYPE>::trace(){
  if(W != H){
    cerr << "Error : TMatrix.trace()" << endl;
    exit(EXIT_FAILURE);
  }
  TYPE  tmp;
  tmp = 0.0;
  for(int i = 0;i < W;i++){
    tmp += D[i * W + i];
  }
  return tmp;
}

template<typename TYPE>
TYPE TMatrix<TYPE>::det(){
  if(W != H){
    cerr << "Error : TMatrix.det()" << endl;
    exit(EXIT_FAILURE);
  }
  TMatrix<TYPE> LU = *this;
  int  *P;
  int   rep;
  TYPE  tmp;
  if((P = (int*)malloc(sizeof(int) * W)) == NULL){
    cerr << "Error : TMatrix.det()" << endl;
    return -1;
  }
  LU_decomposition(LU.ptr(),P,W);
  tmp = 1.0;
  for(int i = 0;i < W;i++){
    tmp *= LU.D[i * W + i];
  }
  rep = 1;
  for(int i = 0;i < W - 1;i++){
    if(P[i] != i){
      rep = -rep;
      for(int j = i + 1;j < W;j++){
	if(P[j] == i){
	   P[j] = P[i];
	   break;
	}
      }
    }
  }
  free(P);
  return (rep == 1) ? tmp : -tmp;
}

template<typename TYPE>
TYPE TMatrix<TYPE>::norm(TYPE p){
  if((p != -1.0) && (p < 0.0)){
    cerr << "Error : TMatrix.norm(TYPE)" << endl;
    exit(EXIT_FAILURE);
  }
  TYPE tmp,max;
  if(p == -1.0){
    max = fabs<TYPE>(D[0 * W + 0]);
    for(int i = 1;i < W;i++){
      tmp = fabs<TYPE>(D[0 * W + i]);
      if(max < tmp){
	 max = tmp;
      }
    }
    for(int j = 1;j < H;j++){
      for(int i = 0;i < W;i++){
	tmp = fabs<TYPE>(D[j * W + i]);
	if(max < tmp){
	   max = tmp;
	}
      }
    }
    return max;
  }else{
    tmp = 0.0;
    for(int j = 0;j < H;j++){
      for(int i = 0;i < W;i++){
	tmp += pow<TYPE>(fabs<TYPE>(D[j * W + i]),p);
      }
    }
    return pow<TYPE>(tmp,1.0 / p);
  }
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::diag(){
  if((W != H) && (W != 1)){
    cerr << "Error : TMatrix.diag()" << endl;
    exit(EXIT_FAILURE);    
  }
  TMatrix<TYPE> A(H,H);
  if(W == H){
    for(int j = 0;j < H;j++){
      A.D[j * A.W + j] = D[j * W + j];
    }
  }else{
    for(int j = 0;j < H;j++){
      A.D[j * A.W + j] = D[j];
    }
  }
  return A;
}

template<typename TYPE> 
TMatrix<TYPE> TMatrix<TYPE>::solve(const TMatrix<TYPE> &b){
  if((W != H) || (b.W != 1) || (H != b.H)){
    cerr << "ERROR : TMatrix.solve(TMatrix)" << endl;                                                                    
    exit(EXIT_FAILURE);                                                                                                  
  }
  TMatrix<TYPE> x(H,1);                                                                                                        
  if(::solve<TYPE>(x.D,D,b.D,H) == -1){                                                                                       
    cerr << "ERROR : TMatrix.solve(TMatrix)" << endl;                                                                    
    exit(EXIT_FAILURE);                                                                                                  
  }
  return x;                                                                                                              
} 

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::I(int dim){
  TMatrix<TYPE> A(dim);
  for(int j = 0;j < A.H;j++){
    A.D[j * A.W + j] = 1.0;
  }
  return A;
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::one(int dim){
  return one(dim,dim);
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::one(int row,int col){
  TMatrix<TYPE> A(row,col);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      A.D[j * A.W + i] = 1.0;
    }
  }
  return A;
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::random(int dim){
  return random(dim,dim);
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::random(int row,int col){
  TMatrix<TYPE> A(row,col);
  CRandom       cr(clock());
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      A.D[j * A.W + i] = cr.normal();
    }
  }
  return A;
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::dct_matrix(int dim){
  TMatrix<TYPE> W(dim,dim);
  for(int j = 0;j < dim;j++){
    W[0][j] = 1.0 / sqrt<TYPE>(dim);
    for(int i = 1;i < dim;i++){
      W[i][j] = cos<TYPE>(M_PI / (2.0 * dim) * (2 * j + 1) * i) * sqrt<TYPE>(2.0 / dim);
    }
  }
  return W;
}

template<typename TYPE>
TMatrix<TYPE> TMatrix<TYPE>::idct_matrix(int dim){
  TMatrix<TYPE> W(dim,dim);
  for(int j = 0;j < dim;j++){
    W[j][0] = 1.0 / sqrt<TYPE>(dim);
    for(int i = 1;i < dim;i++){
      W[j][i] = cos<TYPE>(M_PI / (2.0 * dim) * (2 * j + 1) * i) * sqrt<TYPE>(2.0 / dim);
    }
  }
  return W;
}

template<typename TYPE> 
TVector<TYPE>::TVector(const TMatrix<TYPE> &A){
  if(A.col() != 1){
    cerr << "Error : TVector.TVector(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  this->W =       1;
  this->H = A.row();
  this->D = new TYPE[this->H];
  memcpy(this->D,A.ptr(),this->H * sizeof(TYPE));
}

template<typename TYPE> 
TVector<TYPE> &TVector<TYPE>::operator  =(const TMatrix<TYPE> &A){
  if(A.col() != 1){
    cerr << "Error : TVector.=(TMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  if(this->H != A.row()){ 
    delete [] this->D;
    this->W =       1;
    this->H = A.row();
    this->D = new TYPE[this->H];
  }
  memcpy(this->D,A.ptr(),this->H * sizeof(TYPE));
  return *this;
}

template<typename TYPE>
TVector<TYPE> TVector<TYPE>::one(int dim){
  TVector<TYPE> A(dim);
  for(int j = 0;j < A.H;j++){
    A.D[j] = 1.0;
  }
  return A;
}

template<typename TYPE>
TVector<TYPE> TVector<TYPE>::random(int dim){
  TVector<TYPE> A(dim);
  CRandom       cr(clock());
  for(int j = 0;j < A.H;j++){
    A.D[j] = cr.normal();
  }
  return A;
}

template<typename TYPE>
TVector<TYPE> TVector<TYPE>::random_sparse(int dim,int K){
  TVector<TYPE> A(dim);
  CRandom       cr(clock());
  int           idx;
  TYPE          tmp;
  for(int j = 0;j <   K;j++){
    A.D[j] = cr.normal();
  }
  for(int j = 0;j < A.H;j++){
    idx      = (int)cr.uniform(0.0,dim);
    tmp      = A.D[j];
    A.D[j]   = A.D[idx];
    A.D[idx] = tmp;
  }
  return A;
}
