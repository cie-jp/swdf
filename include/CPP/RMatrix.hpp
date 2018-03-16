double  RMatrix::trace(){
  double res;
  if(W != H){
    cerr << "ERROR : RMatrix.trace()" << endl;
    exit(EXIT_FAILURE);
  }
  if(la_trace(&res,D,W) == -1){
    cerr << "ERROR : RMatrix.trace()" << endl;
    exit(EXIT_FAILURE);
  }
  return res;
}

double  RMatrix::det(){
  double res;
  if(W != H){
    cerr << "ERROR : RMatrix.det()" << endl;
    exit(EXIT_FAILURE);
  }
  if(la_det(&res,D,W) == -1){
    cerr << "ERROR : RMatrix.det()" << endl;
    exit(EXIT_FAILURE);
  }
  return res;
}

double  RMatrix::norm(double p){
  if(p < 0){
    cerr << "ERROR : RMatrix.norm(double)"  << endl;
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

RMatrix  RMatrix::pinv(){
  if(W == H){
    return !(*this);
  }
  if(W >  H){
    return ~(*this) * !((*this) * ~(*this));
  }else{
    return !(~(*this) * (*this)) * ~(*this);
  }
}

RMatrix RMatrix::solve(const RMatrix &b){
  if((W != H) || (b.W != 1) || (H != b.H)){
    cerr << "ERROR : RMatrix.solve(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  RMatrix x(H,1);
  if(la_solve(x.D,D,b.D,H) == -1){
    cerr << "ERROR : RMatrix.solve(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return x;
}

RMatrix RMatrix::basis_pursuit(const RMatrix &b){
  if((b.W != 1) || (H != b.H) || (W < H)){
    cerr << "ERROR : RMatrix.basis_pursuit(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  RMatrix x(W,1),c(W,1);
  for(int j = 0;j < c.H;j++){
    c.D[j] = 1.0;
  }
  if(reviced_simplex2(x.D,c.D,D,b.D,H,W) == -1){
    cerr << "ERROR : RMatrix.basis_pursuit(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return x;
}

RMatrix RMatrix::basis_pursuit_nonnegative(const RMatrix &b){
  if((b.W != 1) || (H != b.H) || (W < H)){
    cerr << "ERROR : RMatrix.basis_pursuit_nonnegative(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  RMatrix x(W,1),c(W,1);
  for(int j = 0;j < c.H;j++){
    c.D[j] = 1.0;
  }
  if(reviced_simplex1(x.D,c.D,D,b.D,H,W) == -1){
    cerr << "ERROR : RMatrix.basis_pursuit_nonnegative(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  return x;
}

RMatrix RMatrix::irls(const RMatrix &b){
  if((b.W != 1) || (H != b.H) || (W < H)){
    cerr << "ERROR : RMatrix.irls(RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  RMatrix u,u_tmp;
  RMatrix q(W,1);
  RMatrix T(H,H);
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

int RMatrix::eig(RMatrix &D,RMatrix &P){
  if(W != H){
    cerr << "ERROR : RMatrix.eig(RMatrix,RMatrix)" << endl;
    exit(EXIT_FAILURE);
  }
  D = *this;
  P = RMatrix(H,W);
  return la_eig(D.D,P.D,W);
}

int RMatrix::vpca(RMatrix &X,RMatrix &M,RMatrix &P,RMatrix &L){
  int     r;
  X = *this;
  M = RMatrix(1,W);
  P = RMatrix(W,W);
  L = RMatrix(1,W);
  r = la_pca(X[0],H,W,M[0],P[0],L[0],0);
  return  r;
}

int RMatrix::vpca(RMatrix &X,RMatrix &M,RMatrix &P){
  int     r;
  X = *this;
  M = RMatrix(1,W);
  P = RMatrix(W,W);
  r = la_pca(X[0],H,W,M[0],P[0],NULL,0);
  return r;
}

int RMatrix::rpca(RMatrix &X,RMatrix &P,RMatrix &L){
  int     r;
  X = *this;
  P = RMatrix(W,W);
  L = RMatrix(1,W);
  r = la_pca(X[0],H,W,NULL,P[0],L[0],0);
  return  r;
}

int RMatrix::rpca(RMatrix &X,RMatrix &P){
  int     r;
  X = *this;
  P = RMatrix(W,W);
  r = la_pca(X[0],H,W,NULL,P[0],NULL,0);
  return  r;
}

int RMatrix::ica(RMatrix &X,RMatrix &M,RMatrix &P){
  int     r;
  X = *this;
  M = RMatrix(1,W);
  P = RMatrix(W,W);
  r = la_ica(X[0],H,W,M[0],P[0]);
  return  r;
}

void RMatrix::fetch_mtx(const char *filename){
  FILE   *fp;
  int     h,w;

  if((fp = fopen(filename,"rb")) == NULL){
    cerr << "ERROR : RMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  if(fread(&h,sizeof(int),1,fp) <= 0){
    cerr << "ERROR : RMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  if(fread(&w,sizeof(int),1,fp) <= 0){
    cerr << "ERROR : RMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  *this = RMatrix(h,w);
  if(fread( D,sizeof(double),h * w,fp) <= 0){
    cerr << "ERROR : RMatrix.fetch_mtx(char*)" << endl;
    exit(EXIT_FAILURE);
  }
  fclose(fp);
}

void RMatrix::write_mtx(const char *filename){
  FILE  *fp;
  if(filename != NULL){
    if((fp = fopen(filename,"wb")) == NULL){
      cerr << "ERROR : RMatrix::write_mtx(char*)" << endl;
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

void RMatrix::fetch_csv(const char *filename,char ch){
  int     buf_size;
  FILE   *fp;
  char   *buf;
  int    *cnt;
  char   *ptr;
  int     i,n,h,H,W;
  if((fp = fopen(filename,"rb")) == NULL){
    cerr << "ERROR : RMatrix::fetch_csv(char*,char)" << endl;
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
    cerr << "ERROR : RMatrix::fetch_csv(char*,char)" << endl;
    exit(EXIT_FAILURE);
  }
  *this  = RMatrix(H,W);
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

void RMatrix::write_csv(const char *filename,char ch){
  FILE *fp;
  if(filename != NULL){
    if((fp = fopen(filename,"wb")) == NULL){
      cerr << "ERROR : RMatrix::write_csv(char*)" << endl;
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
