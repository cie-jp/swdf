#include<iostream>
#include<cmath>
#include"bmatrix.h"
#include"linear_algebra.h"
#include"simplex.h"

using namespace std;

BMatrix::BMatrix(int dim){
  if(dim <= 0){
    cerr << "ERROR : BMatrix.BMatrix(int)"     << endl;
    exit(EXIT_FAILURE);
  }
  W = dim;
  H = dim;
  D = new double[W * H];
  memset(D,0x00,W * H * sizeof(double));
}

BMatrix::BMatrix(int row, int col){
  if(col <= 0 || row <= 0){
    cerr << "ERROR : BMatrix.BMatrix(int,int)" << endl;
    exit(EXIT_FAILURE);
  }
  W = col;
  H = row;
  D = new double[W * H];
  memset(D,0x00,W * H * sizeof(double));
}

BMatrix::BMatrix(const BMatrix &A){
  W = A.W;
  H = A.H;
  D = new double[W * H];
  memcpy(D, A.D,W * H * sizeof(double));
}

BMatrix::~BMatrix(){
  delete [] D;
}

double   *BMatrix::ptr()const{
  return D;
}

int       BMatrix::col()const{
  return W;
}

int       BMatrix::row()const{
  return H;
}

BMatrix  &BMatrix::operator  =(const BMatrix &A){
  if(W != A.W || H != A.H){ 
    delete [] D;
    W = A.W;
    H = A.H;
    D = new double[W * H];
  }
  memcpy(D,A.D,W * H * sizeof(double));
  return *this;
}

double   *BMatrix::operator [](const int n)const{
  return D + n * W;
}

BMatrix  &BMatrix::operator +=(const BMatrix &A){
  return *this = *this + A;
}

BMatrix  &BMatrix::operator -=(const BMatrix &A){
  return *this = *this - A;
}

BMatrix  &BMatrix::operator +=(const double   k){
  return *this = *this + k;
}

BMatrix  &BMatrix::operator -=(const double   k){
  return *this = *this - k;
}

BMatrix  &BMatrix::operator *=(const BMatrix &A){
  return *this = *this * A;
}

BMatrix  &BMatrix::operator *=(const double   k){
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      D[j * W + i] *= k;
    }
  }
  return *this;
}

BMatrix  &BMatrix::operator /=(const double   k){
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      D[j * W + i] /= k;
    }
  }
  return *this;
}

BMatrix  &BMatrix::operator &=(const BMatrix &A){
  return *this = *this & A;
}

BMatrix  &BMatrix::operator |=(const BMatrix &A){
  return *this = *this | A;
}

BMatrix  operator ~(const BMatrix &A){
  BMatrix B(A.W,A.H);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[i * B.W + j] = A.D[j * A.W + i];
    }
  }
  return B;
}

BMatrix  operator !(const BMatrix &A){
  if(A.W != A.H){
    cerr << "ERROR : BMatrix.!(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix B = A;
  if(la_inv(B.D,B.W) == -1){
    cerr << "ERROR : BMatrix.!(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return B;
}

BMatrix  operator +(const BMatrix &A){
  return A;
}

BMatrix  operator -(const BMatrix &A){
  BMatrix B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = -A.D[j * A.W + i];
    }
  }
  return B;
}

BMatrix  operator +(const BMatrix &A,const BMatrix &B){
  if(A.W != B.W || A.H != B.H){
    cerr << "ERROR : BMatrix.+(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] + B.D[j * B.W + i];
    }
  }
  return C;
}

BMatrix  operator -(const BMatrix &A,const BMatrix &B){
  if(A.W != B.W || A.H != B.H){
    cerr << "ERROR : BMatrix.-(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] - B.D[j * B.W + i];
    }
  }
  return C;
}

BMatrix  operator +(const double   k,const BMatrix &A){
  BMatrix B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = k + A.D[j * A.W + i];
    }
  }
  return B;
}

BMatrix  operator +(const BMatrix &A,const double   k){
  return k + A;
}

BMatrix  operator -(const double   k,const BMatrix &A){
  BMatrix B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = k - A.D[j * A.W + i];
    }
  }
  return B;
}

BMatrix  operator -(const BMatrix &A,const double   k){
  BMatrix B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = A.D[j * A.W + i] - k;
    }
  }
  return B;
}

BMatrix  operator *(const BMatrix &A,const BMatrix &B){
  if(A.W != B.H){
    cerr << "ERROR : BMatrix.*(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,B.W);
  double  tmp;
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < B.W;i++){
      tmp = 0.0;
      for(int k = 0;k < A.W;k++){
	tmp += A.D[j * A.W + k] * B.D[k * B.W + i];
      }
      C.D[j * C.W + i] = tmp;
    }
  }
  return C;
}

BMatrix  operator *(const double   k,const BMatrix &A){
  BMatrix B(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      B.D[j * B.W + i] = k * A.D[j * A.W + i];
    }
  }
  return B;
}

BMatrix  operator *(const BMatrix &A,const double   k){
  return k * A;
}

BMatrix  operator %(const BMatrix &A,const BMatrix &B){
  if((A.W != B.W) || (A.H != B.H)){
    cerr << "ERROR : BMatrix.%(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] * B.D[j * A.W + i];
    }
  }
  return C;
}

BMatrix  operator /(const BMatrix &A,const double   k){
  return A * (1.0 / k);
}

BMatrix  operator /(const BMatrix &A,const BMatrix &B){
  if((A.W != B.W) || (A.H != B.H)){
    cerr << "ERROR : BMatrix./(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,A.W);
  for(int j = 0;j < A.H;j++){
    for(int i = 0;i < A.W;i++){
      C.D[j * C.W + i] = A.D[j * A.W + i] / B.D[j * A.W + i];
    }
  }
  return C;
}

BMatrix  operator &(const BMatrix &A,const int    row){
  if((row < 0) || (A.H <= row)){
    cerr << "ERROR : BMatrix.&(BMatrix,int    )" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(1,A.W);
  for(int i = 0;i < A.W;i++){
    C.D[i] = A.D[row * A.W + i];
  }
  return C;
}

BMatrix  operator &(const int    row,const BMatrix &A){
  return A & row;
}

BMatrix  operator &(const BMatrix &A,const BMatrix &B){
  if(A.W != B.W){
    cerr << "ERROR : BMatrix.&(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H + B.H,A.W);
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

BMatrix  operator |(const BMatrix &A,const int    col){
  if((col < 0) || (A.W <= col)){
    cerr << "ERROR : BMatrix.|(BMatrix,int    )" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,1);
  for(int j = 0;j < A.H;j++){
    C.D[j] = A.D[j * A.W + col];
  }
  return C;
}

BMatrix  operator |(const int    col,const BMatrix &A){
  return A | col;
}

BMatrix  operator |(const BMatrix &A,const BMatrix &B){
  if(A.H != B.H){
    cerr << "ERROR : BMatrix.|(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix C(A.H,A.W + B.W);
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

ostream &operator <<(ostream     &os,const BMatrix &A){
  char buf[100];
  for(int i = 0;i < A.H;i++){
    os << "| "; 
    for(int j = 0;j < A.W;j++){
      if(A.D[i * A.W + j] >= 0.0){
	sprintf(buf,"+%10.5lf " ,+A.D[i * A.W + j]);
      }else{
	sprintf(buf,"-%10.5lf " ,-A.D[i * A.W + j]);
      }
      os << buf;
    }
    os << "|" << endl;
  }
  return os;
}

double  BMatrix::trace(){
  double res;
  if(W != H){
    cerr << "ERROR : BMatrix.trace()" << endl;
    exit(EXIT_FAILURE);
  }
  if(la_trace(&res,D,W) == -1){
    cerr << "ERROR : BMatrix.trace()" << endl;
    exit(EXIT_FAILURE);
  }
  return res;
}

double  BMatrix::det(){
  double res;
  if(W != H){
    cerr << "ERROR : BMatrix.det()" << endl;
    exit(EXIT_FAILURE);
  }
  if(la_det(&res,D,W) == -1){
    cerr << "ERROR : BMatrix.det()" << endl;
    exit(EXIT_FAILURE);
  }
  return res;
}

double  BMatrix::norm(double p){
  if(p < 0){
    cerr << "ERROR : BMatrix.norm(double)"  << endl;
    exit(EXIT_FAILURE);
  }
  double tmp;
  tmp  = 0.0;
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      tmp += pow(fabs(D[j * W + i]),p);
    }
  }
  return pow(tmp,1.0 / p);
}

BMatrix  BMatrix::diag(){
  if((W != H) && (W != 1)){
    cerr << "ERROR : BMatrix.diag()" << endl;
    exit(EXIT_FAILURE);    
  }
  BMatrix A(H,H);
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

BMatrix  BMatrix::pinv(){
  if(W == H){
    return !(*this);
  }
  if(W >  H){
    return ~(*this) * !((*this) * ~(*this));
  }else{
    return !(~(*this) * (*this)) * ~(*this);
  }
}

BMatrix BMatrix::solve(const BMatrix &b){
  if((W != H) || (b.W != 1) || (H != b.H)){
    cerr << "ERROR : BMatrix.solve(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix x(H,1);
  if(la_solve(x.D,D,b.D,H) == -1){
    cerr << "ERROR : BMatrix.solve(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return x;
}

BMatrix BMatrix::basis_pursuit(const BMatrix &b){
  if((b.W != 1) || (H != b.H) || (W < H)){
    cerr << "ERROR : BMatrix.basis_pursuit(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix x(W,1),c(W,1);
  for(int j = 0;j < c.H;j++){
    c.D[j] = 1.0;
  }
  if(reviced_simplex2(x.D,c.D,D,b.D,H,W) == -1){
    cerr << "ERROR : BMatrix.basis_pursuit(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return x;
}

BMatrix BMatrix::basis_pursuit_nonnegative(const BMatrix &b){
  if((b.W != 1) || (H != b.H) || (W < H)){
    cerr << "ERROR : BMatrix.basis_pursuit_nonnegative(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix x(W,1),c(W,1);
  for(int j = 0;j < c.H;j++){
    c.D[j] = 1.0;
  }
  if(reviced_simplex1(x.D,c.D,D,b.D,H,W) == -1){
    cerr << "ERROR : BMatrix.basis_pursuit_nonnegative(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return x;
}

BMatrix BMatrix::irls(const BMatrix &b){
  if((b.W != 1) || (H != b.H) || (W < H)){
    cerr << "ERROR : BMatrix.irls(BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  BMatrix u,u_tmp;
  BMatrix q(W,1);
  BMatrix T(H,H);
  double  error;

  u_tmp = ~(*this) * !((*this) * ~(*this)) * b;
  for(double epsilon = 1.0;epsilon >= 1e-8;epsilon *= 0.1){
    for(int loop = 0;loop < 50;loop++){
      for(int j = 0;j < q.H;j++){
	q.D[j] = u_tmp.D[j] * u_tmp.D[j] + epsilon;
      }
      memset(T.D,0x00,sizeof(double) * T.H * T.W);
      for(int j = 0;j < T.H;j++){
	for(int i = 0;i < T.W;i++){
	  for(int k = 0;k < q.H;k++){
	    T.D[j * T.W + i] += q.D[k] * D[j * W + k] * D[i * W + k];
	  }
	}
      }
      u = ~(*this) * (!T * b);
      for(int j = 0;j < u.H;j++){
	u.D[j] *= q.D[j];
      }
      error = (u - u_tmp).norm() / u.norm();
      u_tmp =  u;
      if(error <= sqrt(epsilon) / 100.0){
	break;
      }
    }
  }
  return u;
}

int BMatrix::eig(BMatrix &D,BMatrix &P){
  if(W != H){
    cerr << "ERROR : BMatrix.eig(BMatrix,BMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  D = *this;
  P = BMatrix(H,W);
  return la_eig(D.D,P.D,W);
}

int BMatrix::svd(BMatrix &U,BMatrix &S,BMatrix &V){
  S = *this;
  U = BMatrix(H,H);
  V = BMatrix(W,W);
  return la_svd(S.D,U.D,V.D,H,W);
}

int BMatrix::vpca(BMatrix &X,BMatrix &M,BMatrix &P,BMatrix &L){
  int     r;
  X = *this;
  M = BMatrix(1,W);
  P = BMatrix(W,W);
  L = BMatrix(1,W);
  r = la_pca(X[0],H,W,M[0],P[0],L[0],0);
  return  r;
}

int BMatrix::vpca(BMatrix &X,BMatrix &M,BMatrix &P){
  int     r;
  X = *this;
  M = BMatrix(1,W);
  P = BMatrix(W,W);
  r = la_pca(X[0],H,W,M[0],P[0],NULL,0);
  return r;
}

int BMatrix::rpca(BMatrix &X,BMatrix &P,BMatrix &L){
  int     r;
  X = *this;
  P = BMatrix(W,W);
  L = BMatrix(1,W);
  r = la_pca(X[0],H,W,NULL,P[0],L[0],0);
  return  r;
}

int BMatrix::rpca(BMatrix &X,BMatrix &P){
  int     r;
  X = *this;
  P = BMatrix(W,W);
  r = la_pca(X[0],H,W,NULL,P[0],NULL,0);
  return  r;
}

int BMatrix::ica(BMatrix &X,BMatrix &M,BMatrix &P){
  int     r;
  X = *this;
  M = BMatrix(1,W);
  P = BMatrix(W,W);
  r = la_ica(X[0],H,W,M[0],P[0]);
  return  r;
}

void BMatrix::fetch_mtx(const char *filename){
  FILE   *fp;
  int     h,w;

  if((fp = fopen(filename,"rb")) == NULL){
    cerr << "ERROR : BMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  if(fread(&h,sizeof(int),1,fp) <= 0){
    cerr << "ERROR : BMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  if(fread(&w,sizeof(int),1,fp) <= 0){
    cerr << "ERROR : BMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  *this = BMatrix(h,w);
  if(fread( D,sizeof(double),h * w,fp) <= 0){
    cerr << "ERROR : BMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  fclose(fp);
}

void BMatrix::write_mtx(const char *filename){
  FILE  *fp;
  if(filename != NULL){
    if((fp = fopen(filename,"wb")) == NULL){
      cerr << "ERROR : BMatrix::write_mtx(char*)" << endl;
      exit(EXIT_FAILURE);
    }
  }else{
    fp = stdout;
  }
  fwrite(&H,sizeof(int)   ,1    ,fp);
  fwrite(&W,sizeof(int)   ,1    ,fp);
  fwrite(D ,sizeof(double),H * W,fp);
  fclose(fp);
}

void BMatrix::fetch_csv(const char *filename,char ch){
  int     buf_size;
  FILE   *fp;
  char   *buf;
  int    *cnt;
  char   *ptr;
  int     i,n,h,H,W;
  if((fp = fopen(filename,"rb")) == NULL){
    cerr << "ERROR : BMatrix::fetch_csv(char*,char)" << endl;
    exit(EXIT_FAILURE);
  }
  fseek(fp,0L,SEEK_END);
  buf_size =  ftell(fp);
  fseek(fp,0L,SEEK_SET);
  buf = new char[buf_size]();
  cnt = new  int[buf_size]();
  H   = 0;
  while(fgets(buf,buf_size,fp) != NULL){
    if(buf[0] == ch){
       cnt[0]++;
       n = 1;
    }else{
       n = 0;
    }
    for(i = 1;buf[i] != '\0';i++){
      if( (buf[i] == ch) || (buf[i] == '\n')){
	if(buf[i - 1] != ch){
	   cnt[n]++;
	}
	n++;
      }
    }
    if(n > 0){
       H++;
    }
  }
  W = 0;
  for(i = 0;i < buf_size;i++){
    if(cnt[i] > 0){
       cnt[i] = W;
       W++;
    }
  }
  if((H == 0) || (W == 0)){
    delete[] buf;
    delete[] cnt;
    fclose(fp);
    cerr << "ERROR : BMatrix::fetch_csv(char*,char)" << endl;
    exit(EXIT_FAILURE);
  }
  *this  = BMatrix(H,W);
  fseek(fp,0L,SEEK_SET);
  h = 0;
  while(fgets(buf,buf_size,fp) != NULL){
    if(buf[0] == ch){
      n = 1;
    }else{
      n = 0;
    }
    ptr = buf;
    for(i = 1;buf[i] != '\0';i++){
      if( (buf[i] == ch) || (buf[i] == '\n')){
	if(buf[i - 1] != ch){
	  D[h * W + cnt[n]] = atof(ptr);
	}
	ptr = buf + i + 1;
	n++;
      }
    }
    h++;
  }
  delete[] buf;
  delete[] cnt;
  fclose(fp);  
}

void BMatrix::write_csv(const char *filename,char ch){
  FILE *fp;
  if(filename != NULL){
    if((fp = fopen(filename,"wb")) == NULL){
      cerr << "ERROR : BMatrix::write_csv(char*)" << endl;
      exit(EXIT_FAILURE);
    }
  }else{
    fp = stdout;
  }
  for(int j = 0;j < H;j++){
    for(int i = 0;i < W;i++){
      fprintf(fp,"%e%c",D[j * W + i],ch);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}
