// *************************************************
// 単項演算子(-)
// *************************************************
RMatrix  operator -(const RMatrix &A){
  RMatrix C = A;
  INT     i,j;
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = -C.dat[i * C.col + j];
    }
  }
  return C;
}

// *************************************************
// 減算演算子(行列 - 行列)
// *************************************************
RMatrix  operator -(const RMatrix &A,const RMatrix &B){
  RMatrix C = A;
  INT     i,j;
  
  if(A.row != B.row || A.col != B.col){
    ERROR__SHOW("#1");
    exit(EXIT_FAILURE);
  }
  
  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] -= B.dat[i * B.col + j];
    }
  }
  return C;
}

// *************************************************
// 減算演算子(実数 - 行列)
// *************************************************
RMatrix  operator -(const REAL     a,const RMatrix &B){
  RMatrix C = B;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = a - C.dat[i * C.col + j];
    }
  }
  return C;
}

// *************************************************
// 減算演算子(行列 - 実数)
// *************************************************
RMatrix  operator -(const RMatrix &A,const REAL     b){
  RMatrix C = A;
  INT     i,j;

  for(i = 0;i < C.row;i++){
    for(j = 0;j < C.col;j++){
      C.dat[i * C.col + j] = C.dat[i * C.col + j] - b;
    }
  }
  return C;
}
